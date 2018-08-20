// ==========  AudioToolbox.framework/Headers/MusicPlayer.h
/*!
	@file		MusicPlayer.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2000-2015 by Apple, Inc., all rights reserved.

	@abstract	API's for Music sequencing and playing services
	
	@discussion
		The objects in this API set include:

			- Music Sequence: a container of music tracks
			- Music Track: a time ordered list of events
			- Music Track Iterator: an object to iterate over events in a track
			- Music Player: an object used to play a sequence
		
		A MusicSequence contains an arbitrary number of tracks (MusicTrack) each of which contains
		time-stamped (in units of beats) events in time-increasing order. There are various types of
		events, defined below, including the expected MIDI events, tempo, and extended events.
		
		A MusicTrack has properties which may be inspected and assigned, including support for
		looping, muting/soloing, and time-stamp interpretation. APIs exist for iterating through the
		events in a MusicTrack, and for performing editing operations on them.
		
		A MusicPlayer is used to play a sequence and provides control of playback rate and setting
		to a particular time.
		
		Each MusicSequence may have an associated AUGraph object, which represents a set of
		AudioUnits and the connections between them.  Then, each MusicTrack of the MusicSequence may
		address its events to a specific AudioUnit within the AUGraph. In such a manner, it's
		possible to automate arbitrary parameters of AudioUnits, and schedule notes to be played to
		MusicDevices (AudioUnit software synthesizers) within an arbitrary audio processing network
		(AUGraph). A MusicSequence or its tracks can also address a CoreMIDI endpoint directly.
*/

#ifndef AudioToolbox_MusicPlayer_h
#define AudioToolbox_MusicPlayer_h

#include <Availability.h>
#include <CoreFoundation/CoreFoundation.h>
#include <AudioUnit/MusicDevice.h>
#include <AudioToolbox/AUGraph.h>

#if __has_include(<CoreMIDI/MIDIServices.h>)
	#include <CoreMIDI/MIDIServices.h>
#endif

CF_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
extern "C"
{
#endif

/*!
	@enum MusicEventType
	@abstract music event types, including both MIDI and "extended" protocol
	@constant kMusicEventType_NULL	
	@constant kMusicEventType_ExtendedNote	note with variable number of arguments (non-MIDI)
	@constant kMusicEventType_ExtendedTempo	tempo change in BPM
	@constant kMusicEventType_User			user defined data
	@constant kMusicEventType_Meta			standard MIDI file meta event
	@constant kMusicEventType_MIDINoteMessage		MIDI note-on with duration (for note-off)
	@constant kMusicEventType_MIDIChannelMessage	MIDI channel messages (other than note-on/off)
	@constant kMusicEventType_MIDIRawData			for MIDI system exclusive data
	@constant kMusicEventType_Parameter		general purpose AudioUnit parameter, added in 10.2
	@constant kMusicEventType_AUPreset		the AU's user preset CFDictionaryRef (the ClassInfo property), added 10.3
*/
CF_ENUM(UInt32)
{
	kMusicEventType_NULL					= 0,
	kMusicEventType_ExtendedNote			= 1,
	kMusicEventType_ExtendedTempo			= 3,
	kMusicEventType_User					= 4,
	kMusicEventType_Meta					= 5,
	kMusicEventType_MIDINoteMessage			= 6,
	kMusicEventType_MIDIChannelMessage		= 7,
	kMusicEventType_MIDIRawData				= 8,
	kMusicEventType_Parameter				= 9,
	kMusicEventType_AUPreset				= 10
};
typedef UInt32		MusicEventType;

/*!
	@enum MusicSequenceLoadFlags
	@abstract Flags used to customise loading behaviour
 	@constant	kMusicSequenceLoadSMF_PreserveTracks
			If this flag is set the resultant Sequence will contain:
			a tempo track
			a track for each track found in the SMF
 			This is the default behavior
	@constant	kMusicSequenceLoadSMF_ChannelsToTracks
			If this flag is set the resultant Sequence will contain:
			a tempo track
			1 track for each MIDI Channel that is found in the SMF
			1 track for SysEx or MetaEvents - this will be the last track 
			in the sequence after the LoadSMFWithFlags calls
*/
typedef CF_OPTIONS(UInt32, MusicSequenceLoadFlags)
{
	kMusicSequenceLoadSMF_PreserveTracks	= 0,
	kMusicSequenceLoadSMF_ChannelsToTracks 	= (1 << 0)
};

/*!
	@enum MusicSequenceType
	@abstract	A sequence type
	@discussion Different sequence types to describe the basic mode of operation of a sequence's time line
				You cannot change a music sequence's type to samples/seconds if there are tempo events
				The type will also define how the sequence is saved to a MIDI file:
					Beats - normal midi file
					Seconds - midi file with SMPTE time
					Samples - cannot be saved to a midi file
	@constant	kMusicSequenceType_Beats
					The default/normal type of a sequence.
					Tempo track defines the number of beats per second and can have multiple tempo events
	@constant	kMusicSequenceType_Seconds
					A music sequence with a single 60bpm tempo event
	@constant	kMusicSequenceType_Samples
					A music sequence with a single tempo event that represents the audio sample rate
*/
typedef CF_ENUM(UInt32, MusicSequenceType) {
	kMusicSequenceType_Beats		= 'beat',
	kMusicSequenceType_Seconds		= 'secs',
	kMusicSequenceType_Samples		= 'samp'
};

/*!
	@enum MusicSequenceFileTypeID
	@abstract	describes different types of files that can be parsed by a music sequence
 	@constant	kMusicSequenceFile_AnyType
 					let the system read iMelody files and read and write MIDI files (and any future types)
	@constant	kMusicSequenceFile_MIDIType
					read and write MIDI files
	@constant	kMusicSequenceFile_iMelodyType
					read iMelody files
*/
typedef CF_ENUM(UInt32, MusicSequenceFileTypeID) {
	kMusicSequenceFile_AnyType			= 0,
	kMusicSequenceFile_MIDIType			= 'midi',
	kMusicSequenceFile_iMelodyType		= 'imel'
};

/*!
	@enum MusicSequenceFileFlags
	@abstract	controls the behaviour of the create file calls
	@constant	kMusicSequenceFileFlags_Default
 					Does not overwrite existing files.  Attempts to save over an existing file
 					will return kAudio_FilePermissionError
	@constant	kMusicSequenceFileFlags_EraseFile
					Erase an existing file when creating a new file
*/
typedef CF_OPTIONS(UInt32, MusicSequenceFileFlags) {
	kMusicSequenceFileFlags_Default	  = 0,
	kMusicSequenceFileFlags_EraseFile = 1
};


/*!
	@typedef	MusicTimeStamp
	@abstract	The type used to refer to time values in a music sequence
*/
typedef Float64		MusicTimeStamp;

/*!
	@struct		kMusicTimeStamp_EndOfTrack
	@abstract	used to signal end of track
	@discussion Pass this value in to indicate a time passed the last event in the track.
				In this way, it's possible to perform edits on tracks which include all events
				starting at some particular time up to and including the last event
*/
#define kMusicTimeStamp_EndOfTrack			DBL_MAX

/*!
	@struct		MIDINoteMessage
	@discussion	The parameters to specify a MIDI note
*/
typedef struct MIDINoteMessage
{
	UInt8		channel;
	UInt8		note;
	UInt8		velocity;
	UInt8		releaseVelocity;	// was "reserved". 0 is the correct value when you don't know.
	Float32		duration;
} MIDINoteMessage;

/*!
	@struct		MIDIChannelMessage
	@discussion	The parameters to specify a MIDI channel message
*/
typedef struct MIDIChannelMessage
{
	UInt8		status;		// contains message and channel
	
	// message specific data
	UInt8		data1;		
	UInt8		data2;
	UInt8		reserved;
} MIDIChannelMessage;

/*!
	@struct		MIDIRawData
	@discussion	Generally used to represent a MIDI SysEx message
*/
typedef struct MIDIRawData
{
	UInt32		length;
	UInt8		data[1];
} MIDIRawData;

/*!
	@struct		MIDIMetaEvent
	@discussion	The parameters to specify a MIDI meta event
*/
typedef struct MIDIMetaEvent
{
	UInt8		metaEventType;
	UInt8		unused1;
	UInt8		unused2;
	UInt8		unused3;
	UInt32		dataLength;
	UInt8		data[1];
} MIDIMetaEvent;

/*!
	@struct		MusicEventUserData
	@discussion	Provides a general struct for specifying a user defined event. 
	@field		length
					the size in bytes of the data
	@field		data
					size bytes of user defined event data
*/
typedef struct MusicEventUserData
{
	UInt32		length;
	UInt8		data[1];
} MusicEventUserData;

/*!
	@struct		ExtendedNoteOnEvent
	@discussion	The parameters to specify an extended note on event
*/
typedef struct ExtendedNoteOnEvent
{
	MusicDeviceInstrumentID		instrumentID;
	MusicDeviceGroupID			groupID;
	Float32						duration;
	MusicDeviceNoteParams		extendedParams;
} ExtendedNoteOnEvent;

/*!
	@struct		ParameterEvent
	@discussion	The parameters to specify a parameter event to an audio unit.
*/
typedef struct ParameterEvent
{
	AudioUnitParameterID		parameterID;
	AudioUnitScope				scope;
    AudioUnitElement			element;
	AudioUnitParameterValue		value;
} ParameterEvent;

/*!
	@struct		ExtendedTempoEvent
	@discussion	specifies the value for a tempo in beats per minute
*/
typedef struct ExtendedTempoEvent
{
	Float64		bpm;
} ExtendedTempoEvent;

/*!
	@struct		AUPresetEvent
	@discussion	The parameters to specify a preset for an audio unit.
*/
typedef struct AUPresetEvent
{
	AudioUnitScope				scope;
    AudioUnitElement			element;
	CFPropertyListRef 			preset;
} AUPresetEvent;


#if TARGET_OS_IPHONE
// CAClock is currently not supported on iOS, so we include the definition of this structure here 
// (otherwise we include the CAClock header
/*!
	@struct		CABarBeatTime
	@abstract	A display representation of a musical time in beats.
	
	@field	bar
				A measure number.
	@field	beat
				A beat number (1..n).
	@field	subbeat
				The numerator of the fractional number of beats.
	@field	subbeatDivisor
				The denominator of the fractional number of beats.
	@field	reserved
				Must be 0.
	@discussion
				A clock's internal representation of musical time is in beats based on the
				beginning of the timeline. Normally, such times should be displayed to the user
				in terms of bars, beats, and subbeats (sometimes called "units" or "parts per
				quarter" [PPQ]). This data structure is such a display representation.

				By convention, bar 1 is the beginning of the sequence. Beat 1 is the first beat
				of the measure. In 4/4 time, beat will have a value from 1 to 4. Music
				applications often use beat divisions such as 480 and 960.
*/
struct CABarBeatTime {
	SInt32				bar;
	UInt16				beat;
	UInt16				subbeat;
	UInt16				subbeatDivisor;
	UInt16				reserved;
};
typedef struct CABarBeatTime CABarBeatTime;
#else
	CF_ASSUME_NONNULL_END
	#include <AudioToolbox/CoreAudioClock.h>
	CF_ASSUME_NONNULL_BEGIN
#endif

typedef struct OpaqueMusicPlayer		*MusicPlayer;
typedef struct OpaqueMusicSequence		*MusicSequence;
typedef struct OpaqueMusicTrack			*MusicTrack;
typedef struct OpaqueMusicEventIterator *MusicEventIterator;

/*!
	@typedef MusicSequenceUserCallback
	@discussion See MusicSequenceSetUserCallback
*/
typedef void (*MusicSequenceUserCallback)(	void * __nullable			inClientData,
											MusicSequence				inSequence,
											MusicTrack					inTrack,
											MusicTimeStamp				inEventTime,
											const MusicEventUserData *	inEventData,
											MusicTimeStamp				inStartSliceBeat,
											MusicTimeStamp				inEndSliceBeat);

/*!
	@enum MusicPlayerErrors
	@constant	kAudioToolboxErr_InvalidSequenceType
	@constant	kAudioToolboxErr_TrackIndexError
	@constant	kAudioToolboxErr_TrackNotFound
	@constant	kAudioToolboxErr_EndOfTrack
	@constant	kAudioToolboxErr_StartOfTrack
    @constant	kAudioToolboxErr_IllegalTrackDestination
    @constant	kAudioToolboxErr_NoSequence
	@constant	kAudioToolboxErr_InvalidEventType
	@constant	kAudioToolboxErr_InvalidPlayerState
	@constant	kAudioToolboxErr_CannotDoInCurrentContext
*/
CF_ENUM(OSStatus)
{
	kAudioToolboxErr_InvalidSequenceType		= -10846,
	kAudioToolboxErr_TrackIndexError 			= -10859,
	kAudioToolboxErr_TrackNotFound				= -10858,
	kAudioToolboxErr_EndOfTrack					= -10857,
	kAudioToolboxErr_StartOfTrack				= -10856,
    kAudioToolboxErr_IllegalTrackDestination	= -10855,
    kAudioToolboxErr_NoSequence 				= -10854,
	kAudioToolboxErr_InvalidEventType			= -10853,
	kAudioToolboxErr_InvalidPlayerState			= -10852,
	kAudioToolboxErr_CannotDoInCurrentContext	= -10863,
	kAudioToolboxError_NoTrackDestination		= -66720
};

/*!
	@enum MusicTrackProperties
	@discussion Property values are always get and set by reference
	
	@constant	kSequenceTrackProperty_LoopInfo
		read/write	- MusicTrackLoopInfo
		The default looping behaviour is off (track plays once)
		Looping is set by specifying the length of the loop. It loops from
			(TrackLength - loop length) to Track Length
			If numLoops is set to zero, it will loop forever.
		To turn looping off, you set this with loop length equal to zero.

	@constant	kSequenceTrackProperty_OffsetTime
		read/write	- MusicTimeStamp
		offset's the track's start time to the specified beat. By default this value is zero.
		
	@constant	kSequenceTrackProperty_MuteStatus
		read/write	- Boolean
		mute state of a track. By default this value is false (not muted)
		
	@constant	kSequenceTrackProperty_SoloStatus
		read/write	- Boolean
		solo state of a track. By default this value is false (not soloed)

	@constant	kSequenceTrackProperty_AutomatedParameters
		read/write	- UInt32
		Determines whether a track is used for automating parameters.
		If set to != 0 the track is used to automate parameter events to an AUNode.
		The track can only contain parameter events and these events are interpreted 
		as points in the automation curve
		
    @constant	kSequenceTrackProperty_TrackLength
		read/write	- MusicTimeStamp
		The time of the last event in the track plus any additional time that is allowed for fading out of ending notes
		or round a loop point to musical bar, etc.
		
		If this is not set, the track length will always be adjusted to the end of the last active event in a track and 
		is adjusted dynamically as events are added or removed.
		
		The property will return the max of the user set track length, or the calculated length
	 	
    @constant	kSequenceTrackProperty_TimeResolution
		read only	- SInt16 (only valid on the Tempo track)
		
		This retrieves the time resolution value for a sequence. This time resolution can be the resolution that
		was contained within the midi file used to construct a sequence. If you want to keep a time resolution
		when writing a new file, you can retrieve this value and then specify it when creating a new file from a sequence.
		
		It has no direct baring on the rendering or notion of time of the sequence itself (just its representation in file
		formats such as MIDI files). By default this is set to either:
			480 if the sequence is created manually
			some_value based on what was in a MIDI file if the sequence was created from a MIDI file		
*/
CF_ENUM(UInt32)
{
	kSequenceTrackProperty_LoopInfo = 0,
	kSequenceTrackProperty_OffsetTime = 1,
	kSequenceTrackProperty_MuteStatus = 2,
	kSequenceTrackProperty_SoloStatus = 3,
	// added in 10.2
	kSequenceTrackProperty_AutomatedParameters = 4,
	// added in 10.3
	kSequenceTrackProperty_TrackLength = 5,
	// added in 10.5
	kSequenceTrackProperty_TimeResolution = 6
};


/*!
	@struct		MusicTrackLoopInfo
	@discussion	Used to control the looping behaviour of a track
*/
typedef struct MusicTrackLoopInfo
{
	MusicTimeStamp		loopDuration;
	SInt32				numberOfLoops;
} MusicTrackLoopInfo;


//=====================================================================================================================
#pragma mark -

//=====================================================================================================================
#pragma mark Music Player
/*! 
	@functiongroup Music Player
*/

/*!
	@function	NewMusicPlayer
	@abstract	Create a new music player
	@discussion	A music player is used to play a sequence back. This call is used to create a player
				When a sequence is to be played by a player, it can play to either an AUGraph, a MIDI Destination or a
				mixture/combination of both.
	@param		outPlayer	the newly created player
*/
extern OSStatus
NewMusicPlayer(			MusicPlayer	__nullable * __nonnull outPlayer)			__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	DisposeMusicPlayer
	@abstract	Dispose a music player
	@param		inPlayer	the player to dispose
*/
extern OSStatus
DisposeMusicPlayer(		MusicPlayer		inPlayer)								__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);


/*!
	@function	MusicPlayerSetSequence
	@abstract	Set the sequence for the player to play
	@discussion A Sequence cannot be set on a player while it is playing. Setting a sequence
				will overide the currently set sequence.
	@param		inPlayer	the player
	@param		inSequence	the sequence for the player to play
*/
extern OSStatus
MusicPlayerSetSequence(	MusicPlayer 	inPlayer,
						MusicSequence 	inSequence)								__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicPlayerGetSequence
	@abstract	Get the sequence attached to a player
	@discussion If the player does not have a sequence set, this will return the _NoSequence error
	@param		inPlayer	the player
	@param		outSequence	the sequence currently set on the player
 
*/
extern OSStatus
MusicPlayerGetSequence(	MusicPlayer 	inPlayer,
						MusicSequence __nullable * __nonnull outSequence)		__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_5_0);
								
/*!
	@function	MusicPlayerSetTime
	@abstract	Set the current time on the player
	@discussion The Get and Set Time calls take a specification of time as beats. This positions the player
				to the specified time based on the currently set sequence. No range checking on the time value
				is done. This can be set on a playing player (in which case playing will be resumed from the
				new time).
	@param		inPlayer	the player
	@param		inTime		the new time value
*/
extern OSStatus
MusicPlayerSetTime(		MusicPlayer 	inPlayer,
						MusicTimeStamp 	inTime)									__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicPlayerGetTime
	@abstract	Get the current time of the player
	@discussion The Get and Set Time calls take a specification of time as beats. This retrieves the player's
				current time. If it is playing this time is the time of the player at the time the call was made. 
	@param		inPlayer	the player
	@param		outTime		the current time value
*/
extern OSStatus
MusicPlayerGetTime(		MusicPlayer 	inPlayer,
						MusicTimeStamp	*outTime)								__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicPlayerGetHostTimeForBeats
	@abstract	Returns the host time that will be (or was) played at the specified beat.
	@discussion This call is only valid if the player is playing and will return an error if the player is not playing
				or if the starting position of the player (its "starting beat") was after the specified beat.
				For general translation of beats to time in a sequence, see the MusicSequence calls for beat<->seconds.
				
				The call uses the player's sequence's tempo map to translate a beat time from the starting time and beat
				of the player.
	@param		inPlayer	the player
	@param		inBeats		the specified beat-time value
	@param		outHostTime the corresponding host time
*/
extern OSStatus
MusicPlayerGetHostTimeForBeats(	MusicPlayer 	inPlayer,
								MusicTimeStamp	inBeats,
								UInt64 *		outHostTime)					__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_5_0);

/*!
	@function	MusicPlayerGetBeatsForHostTime
	@abstract	Returns the beat that will be (or was) played at the specified host time. 
	@discussion This call is only valid if the player is playing and will return an error if the player is not playing
				or if the starting time of the player was after the specified host time.
				For general translation of beats to time in a sequence, see the MusicSequence calls for beat<->seconds.
				
				The call uses the player's sequence's tempo map to retrieve a beat time from the starting and specified host time. 
				
	@param		inPlayer	the player
	@param		inHostTime	the specified host time value
	@param		outBeats	the corresponding beat time
*/
extern OSStatus
MusicPlayerGetBeatsForHostTime(	MusicPlayer 	inPlayer,
								UInt64			inHostTime,
								MusicTimeStamp *outBeats)						__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_5_0);

/*!
	@function	MusicPlayerPreroll
	@abstract	Prepare the player for playing
	@discussion Allows the player to prepare its state so that starting is has a lower latency. If a player is started without
				being prerolled, the player will pre-roll itself and then start.
	@param		inPlayer	the player
*/
extern OSStatus
MusicPlayerPreroll(		MusicPlayer 	inPlayer)								__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicPlayerStart
	@abstract	Start the player
	@discussion If the player has not been prerolled, it will pre-roll itself and then start.
	@param		inPlayer	the player
*/
extern OSStatus
MusicPlayerStart(		MusicPlayer 	inPlayer)								__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicPlayerStop
	@abstract	Stop the player
	@param		inPlayer	the player
*/
extern OSStatus
MusicPlayerStop(		MusicPlayer 	inPlayer)								__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

// 
/*!
	@function	MusicPlayerIsPlaying
	@abstract	Returns the playing state of the player. "Is it playing?"
	@discussion This call returns a non-zero value in outIsPlaying if the player has been
				started and not stopped. It may have "played" past the events of the attached
				MusicSequence, but it is still considered to be playing (and its time value increasing)
				until it is explicitly stopped
	@param		inPlayer		the player
	@param		outIsPlaying	false if not, true (non-zero) if is playing
*/
extern OSStatus
MusicPlayerIsPlaying(	MusicPlayer 	inPlayer,
						Boolean *		outIsPlaying)							__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_5_0);

/*!
	@function	MusicPlayerSetPlayRateScalar
	@abstract	Scale the playback rate of the player
	@param		inPlayer	the player
	@param		inScaleRate	a scalar that will be applied to the playback rate. If 2, playback is twice as fast, if
				0.5 it is half as fast. As a scalar, the value must be greater than zero.
*/
extern OSStatus
MusicPlayerSetPlayRateScalar(	MusicPlayer		inPlayer,
								Float64			inScaleRate)					__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_5_0);

/*!
	@function	MusicPlayerGetPlayRateScalar
	@abstract	Get the playback rate scalar of the player
	@param		inPlayer		the player
	@param		outScaleRate	the current scalar being applied to the player. Default value is 1.0
*/
extern OSStatus
MusicPlayerGetPlayRateScalar(	MusicPlayer		inPlayer,
								Float64 *		outScaleRate)					__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_5_0);


//=====================================================================================================================
#pragma mark -

//=====================================================================================================================
#pragma mark Music Sequence
/*! 
	@functiongroup Music Sequence
*/
/*!
	@function	NewMusicSequence
	@abstract	Create a new empty sequence
	@discussion	A new music sequence will only have a tempo track (with a default tempo of 120 bpm), 
				and the default type is beat based.

				When a sequence is to be played by a player, it can play to either an AUGraph, a MIDI Destination or a
				mixture/combination of both. See MusicSequenceSetAUGraph and MusicSequenceSetMIDIEndpoint for the generic
				destination assignments. Specific tracks can also be assigned nodes of a graph or a MIDI endpoint as targets
				for the events that they contain; see MusicTrackSetDestNode and MusicTrackSetDestMIDIEndpoint.
				
	@param		outSequence		the new sequence
*/
extern OSStatus
NewMusicSequence(	MusicSequence __nullable * __nonnull outSequence)			__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	DisposeMusicSequence
	@abstract	Dispose the sequence
	@discussion	 A sequence cannot be disposed while a MusicPlayer has it.
	@param		inSequence		the sequence
*/
extern OSStatus
DisposeMusicSequence(		MusicSequence		inSequence)						__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicSequenceNewTrack
	@abstract	Add a new (empty) track to the sequence
	@param		inSequence		the sequence
	@param		outTrack		the new track (it is always appended to any existing tracks)
*/
extern OSStatus
MusicSequenceNewTrack(		MusicSequence 		inSequence,
							MusicTrack __nullable * __nonnull outTrack)			__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);
													
/*!
	@function	MusicSequenceDisposeTrack
	@abstract	Remove and dispose a track from a sequence
	@param		inSequence		the sequence
	@param		inTrack			the track to remove and dispose
*/
extern OSStatus
MusicSequenceDisposeTrack(	MusicSequence 		inSequence,
							MusicTrack 			inTrack)						__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicSequenceGetTrackCount
	@abstract	The number of tracks in a sequence. 
				The track count and accessors exclude the tempo track (which is treated as a special case)
	@param		inSequence			the sequence
	@param		outNumberOfTracks	the number of tracks
*/
extern OSStatus
MusicSequenceGetTrackCount(	MusicSequence 		inSequence,
							UInt32 				*outNumberOfTracks)				__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);
										
/*!
	@function	MusicSequenceGetIndTrack
	@abstract	Get a track at the specified index
	@discussion Index is zero based. It will return kAudio_ParamError if index is not in the range: 0 < TrackCount
				The track count and accessors exclude the tempo track (which is treated as a special case)
	@param		inSequence		the sequence
	@param		inTrackIndex	the index
	@param		outTrack		the track at that index
*/
extern OSStatus
MusicSequenceGetIndTrack(	MusicSequence 						inSequence,
							UInt32 								inTrackIndex,
							MusicTrack __nullable * __nonnull	outTrack)		__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicSequenceGetTrackIndex
	@abstract	Get the index for a specific track
	@discussion Index is zero based. It will return an error if the track is not a member of the sequence.
				The track count and accessors exclude the tempo track (which is treated as a special case)
	@param		inSequence		the sequence
	@param		inTrack			the track
	@param		outTrackIndex	the index of the track
*/
extern OSStatus
MusicSequenceGetTrackIndex(	MusicSequence 		inSequence,
							MusicTrack 			inTrack,
							UInt32				*outTrackIndex)					__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicSequenceGetTempoTrack
	@abstract	Get the tempo track of the sequence
	@discussion	Each sequence has a single tempo track. All tempo events are placed into this tempo track (as well
				as other appropriate events (time sig for instance from a MIDI file). The tempo track, once retrieved
				can be edited and iterated upon as any other track. Non-tempo events in a tempo track are ignored.
	@param		inSequence		the sequence
	@param		outTrack		the tempo track of the sequence
*/
extern OSStatus
MusicSequenceGetTempoTrack(	MusicSequence						inSequence,
							MusicTrack __nullable * __nonnull	outTrack)		__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_5_0);


/*!
	@function	MusicSequenceSetAUGraph
	@abstract	Set the graph to be associated with the sequence
	@discussion	A sequence can be associated with an AUGraph and this graph will be used to render the events as 
				controlled by the sequence when it is played. By default, all of the tracks of a sequence will
				find the first AUNode that is an instance of an Apple MusicDevice audio unit (see MusicSequenceGetAUGraph).
				Specific nodes of the graph can be targeted for different tracks (see MusicTrackSetDestNode).  To render a
 				multi-track GM MIDI sequence on iOS, create a custom graph with a MIDISynth audio unit as the MusicDevice.
 				If inGraph is set to NULL, the sequence will reset to use the default graph.
	@param		inSequence		the sequence
	@param		inGraph			the graph
*/
extern OSStatus
MusicSequenceSetAUGraph(	MusicSequence 	   inSequence,
							AUGraph __nullable inGraph)							__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);


/*!
	@function	MusicSequenceGetAUGraph
	@abstract	Gets the graph currently associated with a sequence
	@discussion	By default if no graph is assigned to a sequence then the sequence will create a default graph. 
				This default graph contains a MusicDevice and a DynamicsProcessor and all tracks will be targeted
				to the MusicDevice.  On Mac OS X, this MusicDevice is an instance of a software synthesizer that is 
				compatible with the GM and GS MIDI standards.  On iOS, it is an instance of a monotimbral software 
				synthesizer designed to render events from a single MIDI channel.  To render multi-track GM MIDI
 				sequences on iOS, create a custom graph with a MIDISynth audio unit as the MusicDevice.
				
				This call will thus either return the graph as set by the user, or this default graph.
	@param		inSequence		the sequence
	@param		outGraph		the graph
*/
extern OSStatus
MusicSequenceGetAUGraph(	MusicSequence 					inSequence,
							AUGraph __nullable * __nonnull	outGraph)			__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

#if (TARGET_OS_MAC && !TARGET_OS_IPHONE) || TARGET_OS_IOS
/*!
	@function	MusicSequenceSetMIDIEndpoint
	@abstract	Makes the target of all of the tracks in the sequence a MIDI endpoint
	@discussion	This is a convenience function, and is equivalent to iterating through all of the tracks in a sequence
				and targeting each track to the MIDI endpoint
				
	@param		inSequence		the sequence
	@param		inEndpoint		the MIDI endpoint
*/
extern OSStatus
MusicSequenceSetMIDIEndpoint(	MusicSequence 	inSequence,
								MIDIEndpointRef	inEndpoint)						__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_5_0);
	
#endif
/*!
	@function	MusicSequenceSetSequenceType
	@abstract	Set the sequence type (the default is beats)
	@discussion
				These two calls allow you to get and set a MusicSequence type; specifying
					kMusicSequenceType_Beats		= 'beat',
					kMusicSequenceType_Seconds		= 'secs',
					kMusicSequenceType_Samples		= 'samp'

				The sequence type can be set to beats at any time. The sequence type can only be set to 
				seconds or samples if there are NO tempo events already in the sequence.
				
				For beats - it can have as many tempo events as you want
				For Samples and Seconds - you should add a single tempo event after setting the type
					Samples - the tempo is the desired sample rate - e.g. 44100 and each "beat" in the sequence will be
						interpreted as a sample count at that sample rate (so beat == 44100 is a second)
					Seconds - the tempo should be set to 60 - a beat is a second.

				Beats is the default (and is the behaviour on pre 10.5 systems)

				A meta event of interest for Seconds based MIDI files is the SMPTE Offset meta event - stored in the tempo track.
				The sequence doesn't do anything with this event (except store/write it)	
	@param		inSequence	the sequence
	@param		inType		the sequence type
*/
extern OSStatus
MusicSequenceSetSequenceType(	MusicSequence		inSequence,
							MusicSequenceType		inType)						__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_5_0);

/*!
	@function	MusicSequenceGetSequenceType
	@abstract	Get the sequence type
	@discussion	See SetSequence for a full description
	@param		inSequence		the sequence
	@param		outType			the type
*/
extern OSStatus
MusicSequenceGetSequenceType(	MusicSequence		inSequence,
							MusicSequenceType * 	outType)					__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_5_0);


/*!
	@function	MusicSequenceFileLoad
	@abstract	Load the data contained within the referenced file to the sequence
	@discussion	This function will parse the file referenced by the URL and add the events to the sequence.
	@param		inSequence		the sequence
	@param		inFileRef		a file:// URL that references a file
	@param		inFileTypeHint	provides a hint to the sequence on the file type being imported
	@param		inFlags			flags that can control how the data is parsed in the file and laid out in the tracks
								that will be created and added to the sequence in this operation
*/
extern OSStatus
MusicSequenceFileLoad (MusicSequence				inSequence,
						CFURLRef					inFileRef,
						MusicSequenceFileTypeID		inFileTypeHint, // can be zero in many cases
						MusicSequenceLoadFlags		inFlags)					__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_5_0);

/*!
	@function	MusicSequenceFileLoadData
	@abstract	Load the data to the sequence
	@discussion	This function will parse the data and add the events to the sequence. The data provided needs to 
				be of a particular file type as specified by the fileTypeHint.
	@param		inSequence		the sequence
	@param		inData			the contents of a valid file loaded into a CFData object
	@param		inFileTypeHint	provides a hint to the sequence on the file type being imported
	@param		inFlags			flags that can control how the data is parsed in the file and laid out in the tracks
								that will be created and added to the sequence in this operation
*/
extern OSStatus
MusicSequenceFileLoadData (MusicSequence			inSequence,
						CFDataRef					inData,
						MusicSequenceFileTypeID		inFileTypeHint, // can be zero in many cases
						MusicSequenceLoadFlags		inFlags)					__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_5_0);

/*!
	@function	MusicSequenceSetSMPTEResolution
	@abstract	Helper function to establish the SMPTE based MIDI file resolution for the specified ticks
	@discussion SMPTE resolution helpers for dealing with the interpretation and creation of
				tick values for standard MIDI files (see MusicSequenceFileCreate)
	@param		fps		the frames per second
	@param		ticks	the ticks per quarter note
	@result		the resolution that can be used when creating a MIDI file derived from the two parameters
*/
CF_INLINE SInt16 
MusicSequenceSetSMPTEResolution (SignedByte fps, Byte ticks) 
{
	SInt8 res8 = fps < 0 ? fps : -fps;
	SInt16 res = (SInt16) (res8 << 8);
	res += ticks;
	return res;
}

/*!
	@function	MusicSequenceGetSMPTEResolution
	@abstract	Helper function to get the fps and ticks from their representation in a SMPTE based MIDI file
	@discussion SMPTE resolution helpers for dealing with the interpretation and creation of
				tick values for standard MIDI files (see MusicSequenceFileCreate)
	@param		inRes	the resolution from a MIDI file
	@param		fps		the frames per second
	@param		ticks	the ticks per quarter note
*/
CF_INLINE void 
MusicSequenceGetSMPTEResolution (SInt16 inRes, SignedByte * fps, Byte * ticks) 
{
	*fps = (SignedByte)((0xFF00 & inRes) >> 8);
	*ticks = 0x7F & inRes;			
}

/*!
	@function	MusicSequenceFileCreate
	@abstract	Create a file from a sequence
	@discussion	This function can be (and is most commonly) used to create a MIDI file from the events in a sequence.
				Only MIDI based events are used when creating the MIDI file. MIDI files are normally beat based, but
				can also have a SMPTE (or real-time rather than beat time) representation.
				
				inResolution is relationship between "tick" and quarter note for saving to Standard MIDI File
					- pass in zero to use default - this will be the value that is currently set on the tempo track
					- see the comments for the set track property's time resolution
				
				The different Sequence types determine the kinds of files that can be created:

				Beats
					When saving a MIDI file, it saves a beats (PPQ) based axis

				Seconds
					When saving a MIDI file, it will save it as a SMPTE resolution - so you should specify this resolution
					when creating the MIDI file. 
					If zero is specified, 25 fps and 40 ticks/frame is used (a time scale of a millisecond)
			
				Samples
					You cannot save to a MIDI file with this sequence type

				The complete meaning of the 16-bit "division" field in a MIDI File's MThd chunk.

				If it is positive, then a tick represents 1/D quarter notes.

				If it negative:

				bits 14-8 are a signed 7-bit number representing the SMPTE format:
					-24, -25, -29 (drop), -30
				bits 7-0 represents the number of ticks per SMPTE frame
					typical values: 4, 10, 80, 100

				You can obtain millisecond resolution by specifying 25 frames/sec and 40 divisions/frame.

				30 fps with 80 bits (ticks) per frame: 0xE250  ((char)0xE2 == -30)

	@param		inSequence		the sequence
	@param		inFileRef		the location of the file to create
	@param		inFileType		the type of file to create
	@param		inFlags			flags to control the file creation
	@param		inResolution	the resolution (depending on file type and sequence type)
*/
extern OSStatus
MusicSequenceFileCreate (MusicSequence				inSequence,
						CFURLRef					inFileRef,
						MusicSequenceFileTypeID		inFileType,
						MusicSequenceFileFlags		inFlags,
						SInt16						inResolution)				__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_5_0);

/*!
	@function	MusicSequenceFileCreateData
	@abstract	Create a data object from a sequence
	@discussion	The same basic parameters apply to this as with the MusicSequenceFileCreate function. The difference
				being that that function will create a file on disk, whereas this one will create a CFData object
				that is a file in memory. The CFData object should be released by the caller.
	@param		inSequence		the sequence
	@param		inFileType		the type of file to create
	@param		inFlags			flags to control the file creation
	@param		inResolution	the resolution (depending on file type and sequence type)
	@param		outData			the resulting data object
*/
extern OSStatus
MusicSequenceFileCreateData (MusicSequence					inSequence,
						MusicSequenceFileTypeID				inFileType,
						MusicSequenceFileFlags				inFlags,
						SInt16								inResolution,
						CFDataRef __nullable * __nonnull	outData)			__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_5_0);


/*!
	@function	MusicSequenceReverse
	@abstract	Reverse in time all events in a sequence, including the tempo events
	@param		inSequence		the sequence
*/
extern OSStatus
MusicSequenceReverse(		MusicSequence	inSequence)							__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicSequenceGetSecondsForBeats
	@abstract	Returns a seconds value that would correspond to the supplied beats
	@discussion	Uses the sequence's tempo events 
	@param		inSequence		the sequence
	@param		inBeats			the beats
	@param		outSeconds		the seconds (time from 0 beat)
*/
extern OSStatus
MusicSequenceGetSecondsForBeats(	MusicSequence		inSequence,
									MusicTimeStamp		inBeats,
									Float64 *			outSeconds)				__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_5_0);

/*!
	@function	MusicSequenceGetBeatsForSeconds
	@abstract	Returns a beat value that would correspond to the supplied seconds from zero.
	@discussion	Uses the sequence's tempo events 
	@param		inSequence		the sequence
	@param		inSeconds		the seconds
	@param		outBeats		the corresponding beat
*/
extern OSStatus
MusicSequenceGetBeatsForSeconds(	MusicSequence		inSequence,
									Float64				inSeconds,
									MusicTimeStamp *	outBeats)				__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_5_0);

/*!
	@function	MusicSequenceSetUserCallback
	@abstract	Establish a user callback for a sequence
	@discussion	This call is used to register (or remove if inCallback is NULL) a callback
				that the MusicSequence will call for ANY UserEvents that are added to any of the
				tracks of the sequence.
				
				If there is a callback registered, then UserEvents will be chased when
				MusicPlayerSetTime is called. In that case the inStartSliceBeat and inEndSliceBeat
				will both be the same value and will be the beat that the player is chasing too.
				
				In normal cases, where the sequence data is being scheduled for playback, the
				following will apply:
					inStartSliceBeat <= inEventTime < inEndSliceBeat
				
				The only exception to this is if the track that owns the MusicEvent is looping.
				In this case the start beat will still be less than the end beat (so your callback
				can still determine that it is playing, and what beats are currently being scheduled),
				however, the inEventTime will be the original time-stamped time of the user event. 
	@param		inSequence		the sequence
	@param		inCallback		the callback
	@param		inClientData	client (user supplied) data provided back to the callback when it is called by the sequence
*/
extern OSStatus
MusicSequenceSetUserCallback(	MusicSequence							inSequence,
								MusicSequenceUserCallback __nullable	inCallback,
								void * __nullable						inClientData)		__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_5_0);

/*!
	@function	MusicSequenceBeatsToBarBeatTime
	@abstract	Convenience function to format a sequence's beat time to its bar-beat time
	@discussion	see <AudioToolbox/CAClock.h>. The sequence's tempo track Time Sig events are used to 
				to calculate the bar-beat representation. If there are no Time Sig events added to the sequence
				4/4 is assumed. A Time Sig event is a MIDI Meta Event as specified for MIDI files.
	@param		inSequence		the sequence
	@param		inBeats			the beat which should be represented by the bar-beat
	@param		inSubbeatDivisor	The denominator of the fractional number of beats.
	@param		outBarBeatTime	the formatted bar/beat time
*/
extern OSStatus
MusicSequenceBeatsToBarBeatTime(MusicSequence				inSequence,
								MusicTimeStamp				inBeats,
								UInt32						inSubbeatDivisor,
								CABarBeatTime *				outBarBeatTime)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_5_0);

/*!
	@function	MusicSequenceBarBeatTimeToBeats
	@abstract	Convenience function to format a bar-beat time to a sequence's beat time
	@discussion	see <AudioToolbox/CAClock.h>. The sequence's tempo track Time Sig events are used to 
				to calculate the bar-beat representation. If there are no Time Sig events added to the sequence
				4/4 is assumed. A Time Sig event is a MIDI Meta Event as specified for MIDI files.
	@param		inSequence		the sequence
	@param		inBarBeatTime	the bar-beat time
	@param		outBeats		the sequence's beat time for that bar-beat time
*/
extern OSStatus
MusicSequenceBarBeatTimeToBeats(MusicSequence				inSequence,
								const CABarBeatTime *		inBarBeatTime,
								MusicTimeStamp *			outBeats)			__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_5_0);

/*!
	@function	MusicSequenceGetInfoDictionary
	@abstract	Returns a dictionary containing meta-data derived from a sequence
	@discussion	The dictionary can contain one or more of the kAFInfoDictionary_* 
				keys specified in <AudioToolbox/AudioFile.h>
				
				The caller should release the returned dictionary. If the call fails it will return NULL

	@param		inSequence		the sequence
	@result		a CFDictionary or NULL if the call fails.
*/

CF_IMPLICIT_BRIDGING_ENABLED

extern CFDictionaryRef
MusicSequenceGetInfoDictionary(	MusicSequence				inSequence)			__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_5_0);

CF_IMPLICIT_BRIDGING_DISABLED

//=====================================================================================================================
#pragma mark -

//=====================================================================================================================
#pragma mark Music Track
/*! 
	@functiongroup Music Track
*/

/*!
	@function	MusicTrackGetSequence
	@abstract	Gets the sequence which the track is a member of
	@param		inTrack		the track
	@param		outSequence the track's sequence
*/
extern OSStatus
MusicTrackGetSequence(	MusicTrack 			inTrack,
						MusicSequence __nullable * __nonnull outSequence)		__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicTrackSetDestNode
	@abstract	Sets the track's target to the specified AUNode
	@discussion	The node must be a member of the graph that the track's sequence is using. When played, the track
				will send all of its events to that node.
	@param		inTrack		the track
	@param		inNode		the new node
*/
extern OSStatus
MusicTrackSetDestNode(	MusicTrack 			inTrack,
						AUNode				inNode)								__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

#if (TARGET_OS_MAC && !TARGET_OS_IPHONE) || TARGET_OS_IOS
/*!
	@function	MusicTrackSetDestMIDIEndpoint
	@abstract	Sets the track's target to the specified MIDI endpoint
	@discussion	When played, the track will send all of its events to the specified MIDI Endpoint.
	@param		inTrack		the track
	@param		inEndpoint	the new MIDI endpoint
*/
extern OSStatus
MusicTrackSetDestMIDIEndpoint(	MusicTrack			inTrack,
								MIDIEndpointRef		inEndpoint)					__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_5_0);

#endif
	
/*!
	@function	MusicTrackGetDestNode
	@abstract	Gets the track's target if it is an AUNode
	@discussion	Returns kAudioToolboxErr_IllegalTrackDestination if the track's target is a MIDIEndpointRef 
				and NOT an AUNode
	@param		inTrack		the track
	@param		outNode		the node target for the track
*/
extern OSStatus
MusicTrackGetDestNode(			MusicTrack 			inTrack,
								AUNode *			outNode)					__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_5_0);

#if (TARGET_OS_MAC && !TARGET_OS_IPHONE) || TARGET_OS_IOS
/*!
	@function	MusicTrackGetDestMIDIEndpoint
	@abstract	Gets the track's target if it is a MIDI Endpoint
	@discussion	Returns kAudioToolboxErr_IllegalTrackDestination if the track's target is an AUNode 
				and NOT a MIDI Endpoint
	@param		inTrack		the track
	@param		outEndpoint	the MIDI Endpoint target for the track
*/
extern OSStatus
MusicTrackGetDestMIDIEndpoint(	MusicTrack			inTrack,
								MIDIEndpointRef	*	outEndpoint)				__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_5_0);
#endif
	
/*!
	@function	MusicTrackSetProperty
	@abstract	Sets the specified property value
	@discussion Property values are always get and set by reference
	@param		inTrack			the track
	@param		inPropertyID	the property ID
	@param		inData			the new property value
	@param		inLength		the size of the property value being set
*/
extern OSStatus
MusicTrackSetProperty(	MusicTrack 			inTrack,
						UInt32 				inPropertyID,
						void				*inData,
						UInt32				inLength)							__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicTrackGetProperty
	@abstract	Gets the specified property value
	@discussion	If outData is NULL, then the size of the data will be passed back in ioLength
				This allows the client to allocate a buffer of the correct size (useful for variable
				length properties -- currently all properties have fixed size)
				Property values are always get and set by reference
	@param		inTrack			the track
	@param		inPropertyID	the property ID
	@param		outData			if not NULL, points to data of size ioLength
	@param		ioLength		on input the available size of outData, on output the size of the valid data that outData
								will then point too.
*/
extern OSStatus
MusicTrackGetProperty(	MusicTrack 			inTrack,
						UInt32 				inPropertyID,
						void				*outData,
						UInt32				*ioLength)							__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Editing operations on sequence tracks

/*!
	@function	MusicTrackMoveEvents
	@abstract	Move events in a track
	@discussion	Moves all of the events in the specified time range by the moveTime. MoveTime maybe negative to 
				move events backwards (towards zero).
				
				All time ranges are [starttime < endtime]
				
	@param		inTrack			the track
	@param		inStartTime		the start time for the range of events
	@param		inEndTime		the end time up to which will form the range of the events to move
	@param		inMoveTime		amount of beats to move the selected events.
*/
extern OSStatus
MusicTrackMoveEvents(	MusicTrack 			inTrack,
						MusicTimeStamp		inStartTime,
						MusicTimeStamp		inEndTime,
						MusicTimeStamp		inMoveTime)							__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicTrackClear
	@abstract	Removes all events within the specified range
	@discussion	All time ranges are [starttime < endtime]
	@param		inTrack		the track
	@param		inStartTime	the start time for the range of events
	@param		inEndTime	the end time up to which will form the range of the events to clear
*/
extern OSStatus
MusicTrackClear(		MusicTrack 			inTrack,
						MusicTimeStamp		inStartTime,
						MusicTimeStamp		inEndTime)							__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicTrackCut
	@abstract	Removes all the events within the specified range
	@discussion	Events that fall past the specified range will be moved back by the specified range time.
				
				All time ranges are [starttime < endtime]
				
	@param		inTrack		the track
	@param		inStartTime	the start time for the range of events
	@param		inEndTime	the end time up to which will form the range of the events to cut out
*/
extern OSStatus
MusicTrackCut(			MusicTrack 			inTrack,
						MusicTimeStamp		inStartTime,
						MusicTimeStamp		inEndTime)							__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicTrackCopyInsert
	@abstract	Copies events from one track and inserts them into another
	@discussion	Copies all of the events with the specified time range of the source track. It then inserts
				those events into the destination track. All events at and after inDestInsertTime in inDestTrack 
				are moved forward by the range's duration
				
				All time ranges are [starttime < endtime]
				
	@param		inSourceTrack		the source track
	@param		inSourceStartTime	the start time for the range of events
	@param		inSourceEndTime		the end time up to which will form the range of the events to copy from the source track
	@param		inDestTrack			the destination track to copy too
	@param		inDestInsertTime	the time at which the copied events will be inserted.
*/
extern OSStatus
MusicTrackCopyInsert(	MusicTrack 			inSourceTrack,
						MusicTimeStamp		inSourceStartTime,
						MusicTimeStamp		inSourceEndTime,
						MusicTrack 			inDestTrack,
						MusicTimeStamp		inDestInsertTime)					__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicTrackMerge
	@abstract	Copies events from one track and merges them into another
	@discussion	Copies all of the events with the specified time range of the source track. It then merges
				those events into the destination track starting at inDestInsertTime.
				
				All time ranges are [starttime < endtime]
				
	@param		inSourceTrack		the source track
	@param		inSourceStartTime	the start time for the range of events
	@param		inSourceEndTime		the end time up to which will form the range of the events to copy from the source track
	@param		inDestTrack			the destination track to copy too
	@param		inDestInsertTime	the time at which the copied events will be merged.
*/
extern OSStatus
MusicTrackMerge(		MusicTrack 			inSourceTrack,
						MusicTimeStamp		inSourceStartTime,
						MusicTimeStamp		inSourceEndTime,
						MusicTrack 			inDestTrack,
						MusicTimeStamp		inDestInsertTime)					__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);


//=====================================================================================================================
#pragma mark -

//=====================================================================================================================
#pragma mark Music Events
/*! 
	@functiongroup Music Events
*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// adding time-stamped events to the track

/*!
	@function	MusicTrackNewMIDINoteEvent
	@abstract	Adds a MIDINoteMessage event to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inMessage		the event
*/
extern OSStatus
MusicTrackNewMIDINoteEvent(			MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const MIDINoteMessage *		inMessage)		__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicTrackNewMIDIChannelEvent
	@abstract	Adds a MIDIChannelMessage event to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inMessage		the event
*/
extern OSStatus
MusicTrackNewMIDIChannelEvent(		MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const MIDIChannelMessage *	inMessage)		__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicTrackNewMIDIRawDataEvent
	@abstract	Adds a MIDIRawData event to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inRawData		the event
*/
extern OSStatus
MusicTrackNewMIDIRawDataEvent(		MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const MIDIRawData *			inRawData)		__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicTrackNewExtendedNoteEvent
	@abstract	Adds a ExtendedNoteOnEvent to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inInfo			the event
*/
extern OSStatus
MusicTrackNewExtendedNoteEvent(		MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const ExtendedNoteOnEvent	*inInfo)		__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);
										
/*!
	@function	MusicTrackNewParameterEvent
	@abstract	Adds a ParameterEvent to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inInfo			the event
*/
extern OSStatus
MusicTrackNewParameterEvent(		MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const ParameterEvent *		inInfo)			__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_5_0);
										
/*!
	@function	MusicTrackNewExtendedTempoEvent
	@abstract	Adds a tempo event to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inBPM			the event
*/
extern OSStatus
MusicTrackNewExtendedTempoEvent(	MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									Float64						inBPM)			__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);
										
/*!
	@function	MusicTrackNewMetaEvent
	@abstract	Adds a MIDIMetaEvent to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inMetaEvent		the event
*/
extern OSStatus
MusicTrackNewMetaEvent(				MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const MIDIMetaEvent *		inMetaEvent)	__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);
										
/*!
	@function	MusicEventUserData
	@abstract	Adds a MusicEventUserData event to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inUserData		the event
*/
extern OSStatus
MusicTrackNewUserEvent(				MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const MusicEventUserData *	inUserData)		__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicTrackNewAUPresetEvent
	@abstract	Adds a AUPresetEvent to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inPresetEvent	the event
*/
extern OSStatus
MusicTrackNewAUPresetEvent(			MusicTrack 					inTrack,
									MusicTimeStamp			 	inTimeStamp,
									const AUPresetEvent *		inPresetEvent)	__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_5_0);



//=====================================================================================================================
#pragma mark -

//=====================================================================================================================
#pragma mark Music Event Iterator
/*! 
	@functiongroup Music Event Iterator
*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// actual event representation and manipulation within a track....
//
// Here we need to be very careful to be able to deal with both SMF type of MIDI events, and
// also be upwardly compatible with an extended MPEG4-SA like paradigm!
//
// The solution is to hide the internal event representation from the client
// and allow access to the events through accessor functions.  The user, in this way, can
// examine and create standard events, or any user-defined event.


/*!
	@function	NewMusicEventIterator
	@abstract	Creates an iterator to iterator over a track's events
	@discussion	The iterator should be considered invalid if a track is edited. In that case you should create a new
				iterator and seek it to the desired position.
				
	@param		inTrack			the track upon which to iterate
	@param		outIterator		the new iterator
*/
extern OSStatus
NewMusicEventIterator(		MusicTrack 									inTrack,
							MusicEventIterator __nullable * __nonnull	outIterator)	__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);
													
/*!
	@function	DisposeMusicEventIterator
	@abstract	Dispose an iterator
	@param		inIterator		the iterator
*/
extern OSStatus
DisposeMusicEventIterator(			MusicEventIterator	inIterator)				__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicEventIteratorSeek
	@abstract	Move the iterator to an event at the specified time
	@discussion If there is no event at the specified time, the iterator will point to the first event after
				that time.
				By specifying kMusicTimeStamp_EndOfTrack you will position the iterator to the end of track
				(which is pointing to the space just AFTER the last event). You can use MusicEventIteratorPreviousEvent 
				to backup to the last event.
				By specifying 0, you will position the iterator at the first event
	@param		inIterator		the iterator
	@param		inTimeStamp		the time stamp to seek too
*/
extern OSStatus
MusicEventIteratorSeek(				MusicEventIterator 	inIterator,
									MusicTimeStamp 		inTimeStamp)			__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicEventIteratorNextEvent
	@abstract	Move the iterator to the next event
	@discussion If the iterator was at the last event, then it will move past the last event and will no longer point
				to an event. You can use check MusicEventIteratorHasCurrentEvent to see if there is an event at the 
				iterator's current position. See also MusicEventIteratorHasNextEvent.
				
				Typically this call is used to move the iterator forwards through the track's events.
	@param		inIterator		the iterator
*/
extern OSStatus
MusicEventIteratorNextEvent(		MusicEventIterator 	inIterator)				__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicEventIteratorPreviousEvent
	@abstract	Move the iterator to the previous event
	@discussion If the iterator was at the first event, then it will leave the iterator unchanged and return an error. 
				See also MusicEventIteratorHasPreviousEvent

				Typically this call is used to move the iterator backwards through the track's events.
	@param		inIterator		the iterator
*/
extern OSStatus
MusicEventIteratorPreviousEvent(	MusicEventIterator 	inIterator)				__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicEventIteratorGetEventInfo
	@abstract	Retrieves the event data at the iterator.
	@discussion Retrieves the event and other information from the iterator's current position.
	
				If you do not want specific information (eg, the time stamp) pass in NULL for that parameter.
				
	@param		inIterator		the iterator
	@param		outTimeStamp	the time stamp of the event
	@param		outEventType	one of kMusicEventType_XXX that indicates what kind of event type the iterator
								is currently pointing too
	@param		outEventData	a reference to the event data. The type of data is described by the eventType. This data
								is read only and should not be edited in place.
	@param		outEventDataSize	the size of the data referenced by outEventData
*/
extern OSStatus
MusicEventIteratorGetEventInfo(		MusicEventIterator 		inIterator,
									MusicTimeStamp *		outTimeStamp,
									MusicEventType *		outEventType,
									const void * __nullable * __nonnull outEventData,
									UInt32 *				outEventDataSize)	__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);
	
/*!
	@function	MusicEventIteratorSetEventInfo
	@abstract	Changes the type or value of an event
	@discussion Allows you to change either the event type, or the values of the event data, that the iterator is 
				currently pointing too. You cannot change the event's time (to do that you should use 
				MusicEventIteratorSetEventTime).
				
	@param		inIterator		the iterator
	@param		inEventType		the new (or existing) type of the event you are changing
	@param		inEventData		the new event data. The size and type of this event data must match the inEventType
*/
extern OSStatus
MusicEventIteratorSetEventInfo(		MusicEventIterator 		inIterator,
									MusicEventType			inEventType,
									const void *			inEventData)		__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_5_0);

/*!
	@function	MusicEventIteratorSetEventTime
	@abstract	Set a new time for an event
	@discussion The iterator will still be pointing to the same event, but as the event will have moved, 
				it may or may not have a next or previous event now (depending of course on the time
				you moved it too).
				
	@param		inIterator		the iterator
	@param		inTimeStamp		the new time stamp of the event
*/
extern OSStatus
MusicEventIteratorSetEventTime(		MusicEventIterator 		inIterator,
									MusicTimeStamp			inTimeStamp)		__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicEventIteratorDeleteEvent
	@abstract	Deletes the event pointed to by the iterator
	@discussion The iterator will reference the next event after the event has been deleted.
				
	@param		inIterator		the iterator
*/
extern OSStatus
MusicEventIteratorDeleteEvent(		MusicEventIterator	 	inIterator)			__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicEventIteratorHasPreviousEvent
	@abstract	Does the track have an event previous to the event the iterator is pointing to?
	@discussion To use the iterator going backwards through a track:
					iter = New Iterator (points at first event)
					MusicEventIteratorSeek (iter, kMusicTimeStamp_EndOfTrack) // will point it past the last event
					bool hasPreviousEvent;
					MusicEventIteratorHasPreviousEvent (iter, &hasPreviousEvent)
					while (hasPreviousEvent) {
						MusicEventIteratorPreviousEvent (iter)
						// 	do work... MusicEventIteratorGetEventInfo (iter, ...
						
						MusicEventIteratorHasPreviousEvent (iter, &hasPreviousEvent);
					}				
	@param		inIterator		the iterator
	@param		outHasPrevEvent	true if there is a previous event, false if not
*/
extern OSStatus
MusicEventIteratorHasPreviousEvent(	MusicEventIterator 	inIterator,
									Boolean	*			outHasPrevEvent)		__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicEventIteratorHasNextEvent
	@abstract	Does the track have an event past the event the iterator is pointing too?
	@discussion To use the iterator going forwards through a track:
					iter = New Iterator (points at first event)
					bool hasCurrentEvent;
					MusicEventIteratorHasCurrentEvent(iter, &hasCurrentEvent);
					while (hasCurrentEvent) {
						// do work... MusicEventIteratorGetEventInfo (iter, ...
						
						MusicEventIteratorNextEvent (iter)
						MusicEventIteratorHasCurrentEvent(iter, &hasCurrentEvent);
					}
				
	@param		inIterator		the iterator
	@param		outHasNextEvent	true if there is a next event, false if not
*/
extern OSStatus
MusicEventIteratorHasNextEvent(		MusicEventIterator	inIterator,
									Boolean	*			outHasNextEvent)		__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

/*!
	@function	MusicEventIteratorHasCurrentEvent
	@abstract	Is there an event at the iterator's current position?
	@param		inIterator		the iterator
	@param		outHasCurEvent	true if there is an event, false if not
*/
extern OSStatus
MusicEventIteratorHasCurrentEvent(	MusicEventIterator	inIterator,
									Boolean	*			outHasCurEvent)			__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_5_0);



//=====================================================================================================================
#pragma mark -

#pragma mark -- Deprecated
// standard MIDI files (SMF, and RMF)

// MusicSequenceLoadSMF() also intelligently parses an RMID file to extract SMF part
#if !__LP64__
extern OSStatus
MusicSequenceLoadSMFData(	MusicSequence	inSequence,
							CFDataRef		inData)					__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);
#endif // !__LP64__


// passing a value of zero for the flags makes this call equivalent to MusicSequenceLoadSMFData
// a kAudio_ParamError is returned if the sequence has ANY data in it and the flags value is != 0
// This will create a sequence with the first tracks containing MIDI Channel data
// IF the MIDI file had Meta events or SysEx data, then the last track in the sequence
// will contain that data.
extern OSStatus
MusicSequenceLoadSMFWithFlags(		MusicSequence			inSequence,
									const struct FSRef *			inFileRef,
									MusicSequenceLoadFlags	inFlags)	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_3,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);

extern OSStatus
MusicSequenceLoadSMFDataWithFlags(	MusicSequence	inSequence,
									CFDataRef				inData,
									MusicSequenceLoadFlags	inFlags)	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_3,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);
// inFlags must be zero
extern OSStatus
MusicSequenceSaveMIDIFile(	MusicSequence	inSequence,
							const struct FSRef *inParentDirectory,
							CFStringRef		inFileName,
							UInt16			inResolution,
							UInt32			inFlags)				__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_4,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);

extern OSStatus
MusicSequenceSaveSMFData(	MusicSequence	inSequence,
							CFDataRef __nullable * __nonnull outData,
							UInt16			inResolution)			__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);

extern OSStatus
NewMusicTrackFrom(		MusicTrack			inSourceTrack,
						MusicTimeStamp		inSourceStartTime,
						MusicTimeStamp		inSourceEndTime,
						MusicTrack __nullable * __nonnull outNewTrack)	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_6, __IPHONE_NA, __IPHONE_NA);

#if !TARGET_OS_IPHONE
enum {
	kMusicEventType_ExtendedControl			= 2
};

typedef struct ExtendedControlEvent
{
	MusicDeviceGroupID			groupID;
	AudioUnitParameterID		controlID;
	AudioUnitParameterValue		value;
} ExtendedControlEvent;

extern OSStatus
MusicTrackNewExtendedControlEvent(	MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const ExtendedControlEvent	*inInfo)		
																	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_7, __IPHONE_NA, __IPHONE_NA);
#endif

#if defined(__cplusplus)
}
#endif

CF_ASSUME_NONNULL_END

#endif // AudioToolbox_MusicPlayer_h
// ==========  AudioToolbox.framework/Headers/AudioQueue.h
/*!
	@file		AudioQueue.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2006-2015 by Apple, Inc., all rights reserved.
    @abstract   API's to record and play audio buffers.

    @discussion
    
	Audio queues are software objects you use for recording or playing audio in Mac OS X. Audio
	queues perform the following tasks:

		- Connect to audio hardware
		- Manage audio data buffers
		- Employ codecs, as necessary, for compressed audio formats
		- Mediate playback or recording

	Audio queues can record and play audio in linear PCM, in compressed formats (such as Apple
	Lossless, AAC, and MP3), and in other formats for which users have installed codecs. The API set
	includes high-level support for the use of hardware recording and playback devices, and lets you
	use sophisticated codecs without knowledge of how they work.

	Additional advanced features support scheduled playback and synchronization of multiple audio
	queues and synchronization of audio with video.
*/

#ifndef AudioToolbox_AudioQueue_h
#define AudioToolbox_AudioQueue_h

#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
    #include <CoreAudio/CoreAudioTypes.h>
    #include <CoreFoundation/CoreFoundation.h>
#else
    #include <CoreAudioTypes.h>
    #include <CoreFoundation.h>
#endif

#if defined(__BLOCKS__) && !TARGET_OS_IPHONE
    #include <dispatch/dispatch.h>
#endif

CF_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif


#pragma mark -
#pragma mark Constants


#pragma mark -
#pragma mark Types
//==================================================================================================
//  TYPES
//==================================================================================================

/*!
    @typedef    AudioQueuePropertyID
    @abstract   A value that uniquely identifies an audio queue property.
*/
typedef UInt32      AudioQueuePropertyID;

/*!
    @typedef    AudioQueueParameterID
    @abstract   A value that uniquely identifies an audio queue parameter.
*/
typedef UInt32      AudioQueueParameterID;

/*!
    @typedef    AudioQueueParameterID
    @abstract   A value for an audio queue parameter.
*/
typedef Float32     AudioQueueParameterValue;

/*!
    @typedef    AudioQueueRef
    @abstract   Defines an opaque data type that represents an audio queue.
*/
typedef struct OpaqueAudioQueue *   AudioQueueRef;

/*!
    @typedef    AudioQueueTimelineRef
    @abstract   Defines an opaque data type that represents an audio queue timeline.
    @discussion
        You can use this object to observe any overloads in the audio device associated with the
        audio queue. A timeline object receives notifications of discontinuities in the audio
        hardware's sample timeline--for instance, a period of silence when sound was expected.
        Causes of discontinuities include changes in the device state or processing overloads.
        See Technical Q & A: QA 1467 for a discussion of Core Audio overload warnings. These
        warnings indicate you are taking too long to process audio data and the system has cut
        you off. You query a timeline object by passing it as a parameter to
        AudioQueueGetCurrentTime, which means a discontinuity has occurred.
*/
typedef struct OpaqueAudioQueueTimeline *   AudioQueueTimelineRef;


//==================================================================================================
//  CONSTANTS
//==================================================================================================
/*!
    @enum Result Codes
    @abstract   The OSStatus result codes returned by Audio Queue functions.

    @constant   kAudioQueueErr_InvalidBuffer        The specified buffer does not belong to the
                                                    audio queue.
    @constant   kAudioQueueErr_BufferEmpty          The buffer is empty (that is, the
                                                    mAudioDataByteSize field = 0).
    @constant   kAudioQueueErr_DisposalPending      The function cannot act on the audio queue
                                                    because it is being asynchronously disposed of.
    @constant   kAudioQueueErr_InvalidProperty      The specified property ID is invalid.
    @constant   kAudioQueueErr_InvalidPropertySize  The size of the specified property is invalid.
    @constant   kAudioQueueErr_InvalidParameter     The specified parameter ID is invalid.
    @constant   kAudioQueueErr_CannotStart          The audio queue has encountered a problem and
                                                    cannot start.
    @constant   kAudioQueueErr_InvalidDevice        The device assigned to the queue could not
                                                    be located, or is not properly configured.
    @constant   kAudioQueueErr_BufferInQueue        The buffer cannot be disposed of when it is
                                                    enqueued.
    @constant   kAudioQueueErr_InvalidRunState      The queue is running but the function can
                                                    only operate on the queue when it is stopped,
                                                    or vice versa.
    @constant   kAudioQueueErr_InvalidQueueType     The queue is an input queue but the function can
                                                    only operate on an output queue, or vice versa.
    @constant   kAudioQueueErr_Permissions          You do not have the required permissions to call 
                                                    the function
    @constant   kAudioQueueErr_InvalidPropertyValue The specified property value is invalid.
    @constant   kAudioQueueErr_PrimeTimedOut        During Prime, the queue's AudioConverter failed to
                                                    convert the requested number of sample frames.
    @constant   kAudioQueueErr_CodecNotFound        The required audio codec was not found.
    @constant   kAudioQueueErr_InvalidCodecAccess   Access to the required codec is not permitted
                                                    (possibly due to incompatible AudioSession
                                                    settings on iPhoneOS).
    @constant   kAudioQueueErr_QueueInvalidated     On iPhoneOS, the audio server has exited, causing
                                                    this audio queue to have become invalid.
    @constant   kAudioQueueErr_TooManyTaps          There can only be one processing tap per
                                                    audio queue.
    @constant   kAudioQueueErr_InvalidTapContext    GetTapSourceAudio can only be called from the
                                                    tap's callback.
    @constant   kAudioQueueErr_InvalidTapType       GetTapQueueTime can only be called on an output queue's
                                                    tap.
    @constant   kAudioQueueErr_RecordUnderrun       During recording, data was lost because there
                                                    was no enqueued buffer into which to store it.
    @constant   kAudioQueueErr_BufferEnqueuedTwice  A buffer was enqueued twice on an input queue
                                                    (before being returned as a result of being filled
                                                    or from Reset).
    @constant   kAudioQueueErr_EnqueueDuringReset   During Reset, Stop, or Dispose, it is not
                                                    permitted to enqueue buffers.
    @constant   kAudioQueueErr_InvalidOfflineMode   The operation requires the queue to be in
                                                    offline mode but it isn't, or vice versa.
                                                    (Offline mode is entered and exited via
                                                    AudioQueueSetOfflineRenderFormat).
*/
CF_ENUM(OSStatus) {
    kAudioQueueErr_InvalidBuffer        = -66687,
    kAudioQueueErr_BufferEmpty          = -66686,
    kAudioQueueErr_DisposalPending      = -66685,
    kAudioQueueErr_InvalidProperty      = -66684,
    kAudioQueueErr_InvalidPropertySize  = -66683,
    kAudioQueueErr_InvalidParameter     = -66682,
    kAudioQueueErr_CannotStart          = -66681,
    kAudioQueueErr_InvalidDevice        = -66680,
    kAudioQueueErr_BufferInQueue        = -66679,
    kAudioQueueErr_InvalidRunState      = -66678,
    kAudioQueueErr_InvalidQueueType     = -66677,
    kAudioQueueErr_Permissions          = -66676,
    kAudioQueueErr_InvalidPropertyValue = -66675,
    kAudioQueueErr_PrimeTimedOut        = -66674,
    kAudioQueueErr_CodecNotFound        = -66673,
    kAudioQueueErr_InvalidCodecAccess   = -66672,
    kAudioQueueErr_QueueInvalidated     = -66671,
    kAudioQueueErr_TooManyTaps          = -66670,
    kAudioQueueErr_InvalidTapContext    = -66669,
    kAudioQueueErr_RecordUnderrun       = -66668,
    kAudioQueueErr_InvalidTapType       = -66667,
    kAudioQueueErr_BufferEnqueuedTwice  = -66666,
    kAudioQueueErr_EnqueueDuringReset   = -66632,
    kAudioQueueErr_InvalidOfflineMode   = -66626,
};


/*!
    @enum Audio Queue Property IDs
    @abstract   Constants that identify properties for audio queues.
    @discussion
    @constant   kAudioQueueProperty_IsRunning
        A read-only property whose value is a UInt32 that indicates whether or not the queue is
        running. A notification is sent when the audio device starts or stops, which is not
        necessarily when the start or stop function is called.
    @constant   kAudioQueueDeviceProperty_SampleRate
        A read-only property whose value is a Float64 that indicates the sampling rate of the
        associated audio device.
    @constant   kAudioQueueDeviceProperty_NumberChannels
        A read-only property whose value is a UInt32 that indicates the number of channels in
        the associated audio device.
    @constant   kAudioQueueProperty_CurrentDevice
        A read/write property whose value is a CFStringRef that contains the unique identifier
        (UID) of the associated audio device.
    @constant   kAudioQueueProperty_MagicCookie
        A read/write property whose value is an audio format magic cookie. If the audio format
        requires a magic cookie, you must set this property before enqueuing any buffers.
    @constant   kAudioQueueProperty_MaximumOutputPacketSize
        A read-only UInt32 that indicates the size in bytes of the largest single packet of
        data in the output format. This is mostly useful for recording/encoding variable bit rate
        compressed data.
    @constant   kAudioQueueProperty_StreamDescription
        A read-only AudioStreamBasicDescription that indicates the queue's recording format.
        This is useful when recording, where you may specify a sample rate of 0 during
        construction, 
    @constant   kAudioQueueProperty_ChannelLayout
        A read/write property whose value is an audio channel layout structure that describes
        the audio queue's channel layout. The number of channels must match the format of the
        queue. If more than two channels (for instance, a five-channel surround sound) exist in
        the queue, there may be a need to specify a channel layout. This layout indicates the
        specific order in which the channels do appear, such as left, then center, then right.
    @constant   kAudioQueueProperty_EnableLevelMetering
        A read-write property whose value is a UInt32 that indicates whether metering of
        audio levels is enabled for the audio queue. (0=off, 1=on).
    @constant   kAudioQueueProperty_CurrentLevelMeter
        A read-only property whose value is an array of AudioQueueLevelMeter structures, one
        array element per audio channel. The values in the AudioQueueLevelMeters are in the
        range 0-1.
    @constant   kAudioQueueProperty_CurrentLevelMeterDB
        A read-only property whose value is an array of AudioQueueLevelMeter structures, one
        array element per audio channel. The values in the AudioQueueLevelMeters are in
        decibels.
    @constant   kAudioQueueProperty_DecodeBufferSizeFrames
        A read/write property whose value is a UInt32 that is the size of the buffer into which
        an output audio queue decodes buffers. A large buffer provides more reliability and
        better long-term performance at the expense of memory and decreased responsiveness
        in some situations.
    @constant   kAudioQueueProperty_ConverterError
        A read-only property whose value is a UInt32 indicating the most recent error (if any)
        encountered by the queue's internal encoding/decoding process.
    @constant   kAudioQueueProperty_EnableTimePitch
        A read/write property whose value is a UInt32 describing whether there is a time/pitch unit
        inserted into the queue's audio signal chain. This property may only be set while
        the queue is stopped.
    @constant   kAudioQueueProperty_TimePitchAlgorithm
        A read/write property whose value is a UInt32 describing the time/pitch algorithm in use.
        This property is only valid while a time/pitch has been inserted, and may only be changed
        when the queue is not running.
    @constant   kAudioQueueProperty_TimePitchBypass
        A read/write property whose value is a UInt32 describing whether the time/pitch unit
        has been bypassed (1=bypassed, 0=not bypassed).
*/
CF_ENUM(AudioQueuePropertyID) {
    kAudioQueueProperty_IsRunning               = 'aqrn',       // value is UInt32

    kAudioQueueDeviceProperty_SampleRate        = 'aqsr',       // value is Float64
    kAudioQueueDeviceProperty_NumberChannels    = 'aqdc',       // value is UInt32
    kAudioQueueProperty_CurrentDevice           = 'aqcd',       // value is CFStringRef
    
    kAudioQueueProperty_MagicCookie             = 'aqmc',       // value is void*
    kAudioQueueProperty_MaximumOutputPacketSize = 'xops',       // value is UInt32
    kAudioQueueProperty_StreamDescription       = 'aqft',       // value is AudioStreamBasicDescription
       
    kAudioQueueProperty_ChannelLayout           = 'aqcl',       // value is AudioChannelLayout
    kAudioQueueProperty_EnableLevelMetering     = 'aqme',       // value is UInt32
    kAudioQueueProperty_CurrentLevelMeter       = 'aqmv',       // value is array of AudioQueueLevelMeterState, 1 per channel
    kAudioQueueProperty_CurrentLevelMeterDB     = 'aqmd',       // value is array of AudioQueueLevelMeterState, 1 per channel

    kAudioQueueProperty_DecodeBufferSizeFrames  = 'dcbf',       // value is UInt32
    kAudioQueueProperty_ConverterError          = 'qcve',       // value is UInt32

    kAudioQueueProperty_EnableTimePitch         = 'q_tp',       // value is UInt32, 0/1
    kAudioQueueProperty_TimePitchAlgorithm      = 'qtpa',       // value is UInt32. See values below.
    kAudioQueueProperty_TimePitchBypass         = 'qtpb',       // value is UInt32, 1=bypassed
};

/*!
    @enum       Time/Pitch algorithms
    @abstract   Constants that identify values of kAudioQueueProperty_TimePitchAlgorithm

    @constant kAudioQueueTimePitchAlgorithm_Spectral
        Highest quality, most computationally expensive. Suitable for music.
        Default algorithm on OS X.
    @constant kAudioQueueTimePitchAlgorithm_TimeDomain
        Modest quality, less expensive. Suitable for voice.
    @constant kAudioQueueTimePitchAlgorithm_Varispeed
        High quality, but pitch varies with rate.
*/
CF_ENUM(UInt32) {
    kAudioQueueTimePitchAlgorithm_Spectral      = 'spec',
    kAudioQueueTimePitchAlgorithm_TimeDomain    = 'tido',
    kAudioQueueTimePitchAlgorithm_Varispeed     = 'vspd'
};

#if TARGET_OS_IPHONE
/*!	@enum		Time/Pitch algorithms (iOS only)
    @constant kAudioQueueTimePitchAlgorithm_LowQualityZeroLatency
        Low quality, very inexpensive. Suitable for brief fast-forward/rewind effects,
        low quality voice. Default algorithm on iOS.
*/
CF_ENUM(UInt32) {
    kAudioQueueTimePitchAlgorithm_LowQualityZeroLatency = 'lqzl',
};
#endif

#if TARGET_OS_IPHONE
/*!
    @enum Audio Queue Property IDs
    @abstract Audio Queue Property IDs (iOS 3.0 or greater only)
    
    @constant   kAudioQueueProperty_HardwareCodecPolicy
        A UInt32 describing how the audio queue is to choose between a hardware or
        software version of the codec required for its audio format. Its value is one of
        the AudioQueueHardwareCodecPolicy constants below.
        
        If the chosen codec is not available, or if a hardware codec is chosen and the 
        AudioSession category does not permit use of hardware codecs, attempts to Prime or Start
        the queue will fail.

        Use kAudioFormatProperty_Encoders or kAudioFormatProperty_Decoders to determine
        whether the codec you are interested in using is available in hardware form,
        software, or both.
        
        Changing this property is not permitted while the queue is primed or running. Changing
        this property at other times may cause any properties set on the codec to be lost.
*/
CF_ENUM(AudioQueuePropertyID) {
    kAudioQueueProperty_HardwareCodecPolicy             = 'aqcp'        // value is UInt32
};

/*!
    @enum       AudioQueueHardwareCodecPolicy constants
    @abstract   Values of kAudioQueueProperty_HardwareCodecPolicy (iOS 3.0 or greater only)
    
    @constant kAudioQueueHardwareCodecPolicy_Default
        If the required codec is available in both hardware and software forms, the audio queue
        will choose a hardware codec if its AudioSession category permits, software otherwise.
        If the required codec is only available in one form, that codec is chosen.
    @constant kAudioQueueHardwareCodecPolicy_UseSoftwareOnly
        The audio queue will choose a software codec if one is available.
    @constant kAudioQueueHardwareCodecPolicy_UseHardwareOnly
        The audio queue will choose a hardware codec if one is available and its use permitted
        by the AudioSession category.
    @constant kAudioQueueHardwareCodecPolicy_PreferSoftware
        The audio queue will choose a software codec if one is available; if not, it will choose a
        hardware codec if one is available and its use permitted by the AudioSession category.
    @constant kAudioQueueHardwareCodecPolicy_PreferHardware
        The audio queue will choose a hardware codec if one is available and its use permitted
        by the AudioSession category; otherwise, it will choose a software codec if one is available.
*/
CF_ENUM(UInt32) {
    kAudioQueueHardwareCodecPolicy_Default              = 0,
    kAudioQueueHardwareCodecPolicy_UseSoftwareOnly      = 1,
    kAudioQueueHardwareCodecPolicy_UseHardwareOnly      = 2,
    kAudioQueueHardwareCodecPolicy_PreferSoftware       = 3,
    kAudioQueueHardwareCodecPolicy_PreferHardware       = 4
};

/*!
    @enum Audio Queue Property IDs
    @abstract Audio Queue Property IDs (iOS 6.0 or greater only)

    @constant   kAudioQueueProperty_ChannelAssignments
        A write-only property whose value is an array of AudioQueueChannelAssignment. There must be
        one array element for each channel of the queue's format as specified in the
        AudioStreamBasicDescription passed to AudioQueueNewOutput or AudioQueueNewInput.
        (New in iOS 6.0).
*/
CF_ENUM(AudioQueuePropertyID) {
    kAudioQueueProperty_ChannelAssignments      = 'aqca'
} __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);
#endif // TARGET_OS_IPHONE

/*!
    @enum       AudioQueueParameterID
    @abstract   Constants that identify the parameters for audio queues.
    @discussion
        You can set a parameter in one of two ways:
        
        <ul>
        <li>    Assign a parameter value to an audio queue to take effect immediately using
                AudioQueueSetParameter.</li>
        <li>    Schedule a parameter to take effect when a buffer is enqueued. You supply the
                parameter when you queue a buffer, and the new value of the parameter is applied
                when that buffer is rendered.
        </ul>
        
        AudioQueueGetParameter always returns the current value of the parameter

    @constant   kAudioQueueParam_Volume
        A value from 0.0 to 1.0 indicating the linearly scaled gain for the queue. A value of
        1.0 (the default) indicates unity gain. A value of 0.0 indicates zero gain, or silence.
    @constant   kAudioQueueParam_PlayRate
        A value from 0.5 to 2.0 indicating the rate at which the queue is to play. A value of
        1.0 (the default) indicates that the queue should play at its normal rate. Only
        applicable when the time/pitch processor has been enabled and on Mac OS X 10.6 and higher.
    @constant   kAudioQueueParam_Pitch
        A value from -2400 to 2400 indicating the number of cents to pitch-shift the queue's
        playback. (1200 cents is one octave.) Only applicable when the time/pitch processor has 
        been enabled with the spectral algorithm, and on Mac OS X 10.6 and higher.
    @constant   kAudioQueueParam_VolumeRampTime
        A value indicating the number of seconds over which subsequent volume changes will be
        ramped. For example, to fade out from full unity gain to silence over the course of 1
        second, set kAudioQueueParam_VolumeRampTime to 1 then kAudioQueueParam_Volume to 0.
    @constant   kAudioQueueParam_Pan
        A value from -1 to 1 indicating the pan position of a mono source (-1 = hard left, 0 =
        center, 1 = hard right). For a stereo source this parameter affects left/right balance.
        For multi-channel sources, this parameter has no effect.
*/
CF_ENUM(AudioQueueParameterID)
{
    kAudioQueueParam_Volume         = 1,
    kAudioQueueParam_PlayRate       = 2,
    kAudioQueueParam_Pitch          = 3,
    kAudioQueueParam_VolumeRampTime = 4,
    kAudioQueueParam_Pan            = 13
};

/*!
    @enum       AudioQueueProcessingTap flags
    @abstract   Flags used in conjunction with processing taps

    @discussion
        In the flags passed to AudioQueueProcessingTapNew, either the PreEffects
        or PostEffects flag must be set, but not both. 

    @constant   kAudioQueueProcessingTap_PreEffects
        Signifies that the processing tap is inserted before any effects.
        Passed to AudioQueueProcessingTapNew and to the callback.
    @constant   kAudioQueueProcessingTap_PostEffects
        Signifies that the processing tap is inserted after any effects.
        Passed to AudioQueueProcessingTapNew and to the callback.
    @constant   kAudioQueueProcessingTap_Siphon
        Signifies that the processing tap is a siphon; it does not call
        GetSourceAudio. The callback instead receives the source audio
        and may not modify it. Passed to AudioQueueProcessingTapNew and to the callback.
    @constant   kAudioQueueProcessingTap_StartOfStream
        Signifies that the source audio is the beginning of a continuous stream,
        i.e. following the beginning or resumption of playback or recording.
        Returned from GetSourceAudio.
    @constant   kAudioQueueProcessingTap_EndOfStream
        Signifies that the source audio is past the end of stream. This happens when
        the audio queue is being stopped asynchronously and has finished playing
        all of its data. Returned from GetSourceAudio and should be propagated
        on return from the callback.
*/
typedef CF_OPTIONS(UInt32, AudioQueueProcessingTapFlags) {
    //  these are flags that are passed to both the constructor and the callback
    kAudioQueueProcessingTap_PreEffects         = (1 << 0),     // 0x01
    kAudioQueueProcessingTap_PostEffects        = (1 << 1),     // 0x02
    kAudioQueueProcessingTap_Siphon             = (1 << 2),     // 0x04

    //  these are flags that are passed to the callback and from GetSourceAudio
    kAudioQueueProcessingTap_StartOfStream      = (1 << 8),     // 0x100
    kAudioQueueProcessingTap_EndOfStream        = (1 << 9),     // 0x200
};

#pragma mark -
#pragma mark Structs
//==================================================================================================
//  STRUCTS
//==================================================================================================

/*!
    @struct     AudioQueueBuffer
    @abstract   Defines a buffer of audio data to be managed by an audio queue.
    @discussion 
        Each audio queue has an associated set of audio queue buffers. You can request that a
        queue allocate buffers using the AudioQueueAllocateBuffer function and dispose of them
        using the AudioQueueFreeBuffer function.
        
        You may also use AudioQueueAllocateBufferWithPacketDescriptions to allocate buffers
        with space for AudioPacketDescriptions, as used in VBR formats. The 
        mPacketDescriptionCapacity, mmPacketDescriptions, and mPacketDescriptionCount
        fields may only be used with buffers allocated with this function.
        
    @field      mAudioDataBytesCapacity
        The size of the buffer, in bytes. This size is set when the buffer is allocated and
        cannot be changed.
    @field      mAudioData
       A pointer to the audio data in the buffer. Although you can write data to this buffer,
       you cannot make it point to another address.
    @field      mAudioDataByteSize
        The number of bytes of valid audio data in the buffer. You set this value when providing
        data for playback; the audio queue sets this value when recording data from a recording
        queue.
    @field      mUserData
        A value you may specify to identify the buffer when it is passed back in recording or
        playback callback functions.
    @field      mPacketDescriptionCapacity
        The maximum number of packet descriptions that can be stored in mPacketDescriptions.
    @field      mPacketDescriptions
        An array of AudioStreamPacketDescriptions associated with the buffer.
    @field      mPacketDescriptionCount
        The number of valid packet descriptions in the buffer. You set this value when providing
        buffers for playback; the audio queue sets this value when returning buffers from
        a recording queue.
*/

typedef struct AudioQueueBuffer {
    const UInt32                    mAudioDataBytesCapacity;
    void * const                    mAudioData;
    UInt32                          mAudioDataByteSize;
    void * __nullable               mUserData;

    const UInt32                    mPacketDescriptionCapacity;
    AudioStreamPacketDescription * const __nullable mPacketDescriptions;
    UInt32                          mPacketDescriptionCount;
#ifdef __cplusplus
    AudioQueueBuffer() : mAudioDataBytesCapacity(0), mAudioData(0), mPacketDescriptionCapacity(0), mPacketDescriptions(0) { }
#endif
} AudioQueueBuffer;

/*!
    @typedef    AudioQueueBufferRef
    @abstract   An pointer to an AudioQueueBuffer.
*/
typedef AudioQueueBuffer *AudioQueueBufferRef;

/*!
    @struct     AudioQueueParameterEvent
    @abstract   Specifies a value for an audio queue parameter.
    @discussion
        Two ways are available to supply an audio queue with parameters:
        
        <ul>
        <li>    Provide one or more parameters by calling the
                AudioQueueEnqueueBufferWithParameters function. In this case, the parameters are
                applied to the specified buffer when it is played.</li>
        <li>    Assign a parameter value immediately to an audio queue by calling the
                AudioQueueSetParameter function.</li>
        </ul>
        
        Note that the AudioQueueGetParameter function always returns the actual value of the
        parameter.

        In Mac OS X v10.5, audio queues have one parameter available: kAudioQueueParam_Volume,
        which controls the queue's playback volume.
        
    @field      mID
        The parameter.
    @field      mValue
        The value of the specified parameter.
*/
struct AudioQueueParameterEvent {
    AudioQueueParameterID           mID;
    AudioQueueParameterValue        mValue;
};
typedef struct AudioQueueParameterEvent AudioQueueParameterEvent;


/*!
    @struct     AudioQueueLevelMeterState
    @abstract   Specifies the current level metering information for one channel of an audio queue.
    @discussion
    @field      mAveragePower
        The audio channel's average RMS power.
    @field      mPeakPower
        The audio channel's peak RMS power
*/
typedef struct AudioQueueLevelMeterState {
    Float32     mAveragePower;
    Float32     mPeakPower;
} AudioQueueLevelMeterState;

/*!
    @typedef    AudioQueueProcessingTapRef
    @abstract   An object for intercepting and processing audio within an audio queue.
*/
typedef struct OpaqueAudioQueueProcessingTap *   AudioQueueProcessingTapRef;

#if TARGET_OS_IPHONE
/*!
    @struct     AudioQueueChannelAssignment
    @abstract   Specifies an audio device channel to which the queue will play or from which
                it will record.
    @discussion
    @field      mDeviceUID
        On iOS, this is a port UID obtained from AVAudioSession. On OS X, this is the UID
        obtained from an AudioDeviceID.
    @field      mChannelNumber
        The 1-based index of the channel.
*/
typedef struct AudioQueueChannelAssignment {
    CFStringRef     mDeviceUID;
    UInt32          mChannelNumber;
} AudioQueueChannelAssignment;
#endif

#pragma mark -
#pragma mark Callbacks
//==================================================================================================
//  CALLBACKS
//==================================================================================================

#if defined(__BLOCKS__) && !TARGET_OS_IPHONE
/*!
    @typedef    AudioQueueOutputCallbackBlock
    @abstract   Defines a pointer to a block that is called when a playback audio
                queue has finished taking data from a buffer.

    @discussion
        A playback buffer callback is invoked when the audio queue has finished with the data to
        be played and the buffer is available to your application for reuse. Your application
        might want to immediately refill and re-enqueue the completed buffer at this time.
    @param      inAQ
        The audio queue that invoked the callback.
    @param      inBuffer
        The audio queue buffer made available by the audio queue.
*/
typedef void (^AudioQueueOutputCallbackBlock)(
                                    AudioQueueRef                   inAQ,
                                    AudioQueueBufferRef             inBuffer);

/*!
    @typedef    AudioQueueInputCallbackBlock
    @abstract   Defines a pointer to a block that is called when a recording audio
                queue has finished filling a buffer.
    @discussion
        You specify a recording buffer callback when calling AudioQueueNewInput. Your callback
        is invoked each time the recording audio queue has filled a buffer with input data.
        Typically, your callback should write the audio queue buffer's data to a file or other
        buffer, and then re-queue the audio queue buffer to receive more data.
        
    @param      inAQ
        The audio queue that invoked the callback.
    @param      inBuffer
        An audio queue buffer, newly filled by the audio queue, containing the new audio data
        your callback needs to write.
    @param      inStartTime
        A pointer to an audio time stamp structure corresponding to the first sample contained
        in the buffer. This contains the sample time of the first sample in the buffer.
    @param      inNumberPacketDescriptions
        The number of audio packets contained in the data provided to the callback
    @param      inPacketDescs
        For compressed formats which require packet descriptions, the packet descriptions
        produced by the encoder for the incoming buffer.
*/
typedef void (^AudioQueueInputCallbackBlock)(
                                    AudioQueueRef                   inAQ,
                                    AudioQueueBufferRef             inBuffer,
                                    const AudioTimeStamp *          inStartTime,
                                    UInt32                          inNumberPacketDescriptions,
                                    const AudioStreamPacketDescription * __nullable inPacketDescs);
#endif // defined(__BLOCKS__) && !TARGET_OS_IPHONE

/*!
    @typedef    AudioQueueOutputCallback
    @abstract   Defines a pointer to a callback function that is called when a playback audio
                queue has finished taking data from a buffer.

    @discussion
        A playback buffer callback is invoked when the audio queue has finished with the data to
        be played and the buffer is available to your application for reuse. Your application
        might want to immediately refill and re-enqueue the completed buffer at this time.
    @param      inUserData
        The value specified by the inUserData parameter of the AudioQueueNewOutput function.
    @param      inAQ
        The audio queue that invoked the callback.
    @param      inBuffer
        The audio queue buffer made available by the audio queue.
*/
typedef void (*AudioQueueOutputCallback)(
                                    void * __nullable       inUserData,
                                    AudioQueueRef           inAQ,
                                    AudioQueueBufferRef     inBuffer);

/*!
    @typedef    AudioQueueInputCallback
    @abstract   Defines a pointer to a callback function that is called when a recording audio
                queue has finished filling a buffer.
    @discussion
        You specify a recording buffer callback when calling AudioQueueNewInput. Your callback
        is invoked each time the recording audio queue has filled a buffer with input data.
        Typically, your callback should write the audio queue buffer's data to a file or other
        buffer, and then re-queue the audio queue buffer to receive more data.
        
    @param      inUserData
        The value you've specified in the inUserData parameter of the AudioQueueNewInput
        function.
    @param      inAQ
        The audio queue that invoked the callback.
    @param      inBuffer
        An audio queue buffer, newly filled by the audio queue, containing the new audio data
        your callback needs to write.
    @param      inStartTime
        A pointer to an audio time stamp structure corresponding to the first sample contained
        in the buffer. This contains the sample time of the first sample in the buffer.
    @param      inNumberPacketDescriptions
        The number of audio packets contained in the data provided to the callback
    @param      inPacketDescs
        For compressed formats which require packet descriptions, the packet descriptions
        produced by the encoder for the incoming buffer.
*/
typedef void (*AudioQueueInputCallback)(
                                    void * __nullable               inUserData,
                                    AudioQueueRef                   inAQ,
                                    AudioQueueBufferRef             inBuffer,
                                    const AudioTimeStamp *          inStartTime,
                                    UInt32                          inNumberPacketDescriptions,
                                    const AudioStreamPacketDescription * __nullable inPacketDescs);


/*!
    @typedef    AudioQueuePropertyListenerProc
    @abstract   Defines a pointer to a callback function that is called when a specified
                property changes value.
    @discussion
        You assign a property listener callback when calling AudioQueueAddPropertyListener.
        
    @param      inUserData
        A pointer to the data specified by the inUserData parameter of the
        AudioQueueAddPropertyListener function.
    @param      inAQ
        The audio queue that invoked the callback.
    @param      inID
        The ID of the property that invoked the callback.
*/
typedef void (*AudioQueuePropertyListenerProc)(  
                                    void * __nullable       inUserData,
                                    AudioQueueRef           inAQ,
                                    AudioQueuePropertyID    inID);

/*!
@typedef    AudioQueueProcessingTapCallback
@abstract   A function called when an audio queue has data to be processed by its tap

@discussion
    A processing callback is invoked when the audio queue has data that can be processed by a given
    tap.

    The audio queue will call the processing callback when it has sufficient data to provide for
    processing.

    In the case of a siphoning tap, the callback function can inspect the audio data in ioData, but
    should not otherwise modify it. The callback should not call
    AudioQueueProcessingTapGetSourceAudio.

    A non-siphoning callback should call AudioQueueProcessingTapGetSourceAudio to request from the
    queue as much source data as it needs in order to produce the requested number of output
    samples. When the callback requests source data it may receive less data than it requests.

    In the case of a tap on an audio output queue, the tap must emit the exact number of sample
    frames that the queue requests. In normal circumstances, the tap's requests for source data will
    be satisfied (as the client running the audio queue is also providing the queue with the audio
    source material). If there is insufficient source data available (this is indicated by the
    outNumberFrames from the GetSource call), then the processing tap should deal as best as it can;
    it can either return less data than was requested or insert silence, noise, etc. itself. If it
    returns less data than requested, the hosting audio queue will fill in the remainder with
    silence.

    In the case of a tap on an audio input queue, the tap may provide back less audio data than is
    being requested. Typically this will occur because the tap will ask for source data that is not
    available at this time (the audio input hasn't arrived yet), so the tap should cache the source
    data that it needs and return as many processed samples as it can. If the processing tap falls
    behind and is not providing data quickly enough silence will be generated in the data provided
    to the client (and there is no signal about this either).

    A processing tap executes in a semi-real-time context, so the general limitations for real-time
    processing apply. Avoid using API's which may block. In particular, it is not safe to call the
    audio queue on which the tap was installed, with the exceptions of
    AudioQueueProcessingTapGetSourceAudio and AudioQueueProcessingTapGetQueueTime.

    In normal operation the source data will be continuous from the last time the callback was
    called and the processed samples should be continuous from the previous samples returned. If
    there is any discontinuity between the last samples provided for processing the audio queue will
    set the bit for kAudioQueueProcessing_StartOfStream in the inFlags. After a discontinuity the
    first sample that the processing tap outputs should correspond to the first sample that was
    provided in the source samples (so a reset and then consequent process serves to re-anchor a
    relationship between the processing tap's source and processed samples). In this case the
    processing tap will typically discard any previous state (for instance, if a processing tap was
    adding a reverb to a signal, then the discontinuity flag would act the same as AudioUnitReset;
    any previous source information in the processing tap should be discarded).

    The caller is responsible for absorbing any processing delays. For example, if the processing is
    to be done by an audio unit that reports a processing latency, then the caller should remove
    those latency samples from the audio unit's rendering and not return them to the audio queue.

    The processing tap is able to operate on the provided source data in place (that is, it can do
    "in place processing") and return pointers to that buffer rather than its own. This works in a
    similar way as AudioUnit render operations.

    When an output audio queue is being stopped asynchronously, the processing tap will see the
    kAudioQueueProcessingTap_EndOfStream bit set on return from GetSourceAudio, and is responsible
    for propagating this bit from the callback when its processing has reached this point.

    A processing tap will NEVER see the same source data again, so, it should keep its own copy if
    it needs to keep it for further reference past the duration of this call. It also cannot assume
    that the pointers to the source data that it retrieves will remain valid AFTER the processing
    tap has executed.

    The processing tap should ensure that the data pointers it provides in outProcessedData remain
    valid until the tap is executed again.

    A processing tap is destroyed implicitly when its audio queue is disposed. It may also be
    removed explicitly, via AudioQueueProcessingTapDispose.

    @param      inClientData
                    the client data pointer passed to AudioQueueProcessingTapNew
    @param      inAQ
                    The audio queue that invoked the callback.
    @param      inAQTap
                    The tap for this callback.
    @param      inNumberFrames
                    The requested number of sample frames to be rendered.
    @param      ioFlags
                    On entry, the flags passed at construction time are provided. On exit,
                    the start/end of stream flags should be set when appropriate.
    @param      ioAudioTimeStamp
                    On an input audio queue, the timestamp must be returned from this function.
                    On an output audio queue, the callback is provided a continuous timestamp.
    @param      outNumberFrames
                    The number of frames of audio data provided in the processed data. Can be 0.
    @param      ioData
                    For non-siphoning taps, on entry, the buffer pointers are null and the lengths
                    are zero. On exit, they should contain the tap's output.
                    
                    Siphoning taps receive valid buffers which they must not alter.
*/
typedef void (*AudioQueueProcessingTapCallback)(
                                    void *                          inClientData,
                                    AudioQueueProcessingTapRef      inAQTap,
                                    UInt32                          inNumberFrames,
                                    AudioTimeStamp *                ioTimeStamp,
                                    AudioQueueProcessingTapFlags *  ioFlags,
                                    UInt32 *                        outNumberFrames,
                                    AudioBufferList *               ioData);

//==================================================================================================
//  FUNCTIONS
//==================================================================================================

#pragma mark -
#pragma mark Creating/destroying queues
//=============================================================================
//  Creating/destroying queues
//=============================================================================

/*!
    @function   AudioQueueNewOutput
    @abstract   Creates a new audio queue for playing audio data.
    @discussion
        To create an playback audio queue, you allocate buffers, then queue buffers (using
        AudioQueueEnqueueBuffer). The callback receives buffers and typically queues them again.
        To schedule a buffer for playback, providing parameter and start time information, call
        AudioQueueEnqueueBufferWithParameters.
       
    @param      inFormat
        A pointer to a structure describing the format of the audio data to be played. For
        linear PCM, only interleaved formats are supported. Compressed formats are supported.
    @param      inCallbackProc
        A pointer to a callback function to be called when the audio queue has finished playing
        a buffer.
    @param      inUserData
        A value or pointer to data that you specify to be passed to the callback function.
    @param      inCallbackRunLoop
        The event loop on which inCallbackProc is to be called. If you specify NULL, the
        callback is called on one of the audio queue's internal threads.
    @param      inCallbackRunLoopMode
        The run loop mode in which to call the callback. Typically, you pass
        kCFRunLoopCommonModes. (NULL also specifies kCFRunLoopCommonModes). Other
        possibilities are implementation specific. You can choose to create your own thread with
        your own run loops. For more information on run loops, see Run Loops or CFRunLoop
        Reference.
    @param      inFlags
        Reserved for future use. Pass 0.
    @param      outAQ
        On return, this variable contains a pointer to the newly created playback audio queue
        object.
    @result     An OSStatus result code.
*/
extern OSStatus             
AudioQueueNewOutput(                const AudioStreamBasicDescription *inFormat,
                                    AudioQueueOutputCallback        inCallbackProc,
                                    void * __nullable               inUserData,
                                    CFRunLoopRef __nullable         inCallbackRunLoop,
                                    CFStringRef __nullable          inCallbackRunLoopMode,
                                    UInt32                          inFlags,
                                    AudioQueueRef __nullable * __nonnull outAQ)          __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);


/*!
    @function   AudioQueueNewInput
    @abstract   Creates a new audio queue for recording audio data.
    @discussion
        
        Outline of how to use the queue for input:
        
        - create input queue
        - allocate buffers
        - enqueue buffers (AudioQueueEnqueueBuffer, not with parameters, no packet descriptions)
        - the callback receives buffers and re-enqueues them
        
    @param      inFormat
        A pointer to a structure describing the format of the audio data to be recorded. For
        linear PCM, only interleaved formats are supported. Compressed formats are supported.
    @param      inCallbackProc
        A pointer to a callback function to be called when the audio queue has finished filling
        a buffer.
    @param      inUserData
        A value or pointer to data that you specify to be passed to the callback function.
    @param      inCallbackRunLoop
        The event loop on which inCallbackProc is to be called. If you specify NULL, the
        callback is called on one of the audio queue's internal threads.
    @param      inCallbackRunLoopMode
        The run loop mode in which to call the callback. Typically, you pass
        kCFRunLoopCommonModes. (NULL also specifies kCFRunLoopCommonModes). Other
        possibilities are implementation specific. You can choose to create your own thread with
        your own run loops. For more information on run loops, see Run Loops or CFRunLoop
        Reference.
    @param      inFlags
        Reserved for future use. Pass 0.
    @param      outAQ
        On return, this variable contains a pointer to the newly created recording audio queue
        object.
    @result     An OSStatus result code.
*/
extern OSStatus             
AudioQueueNewInput(                 const AudioStreamBasicDescription *inFormat,
                                    AudioQueueInputCallback         inCallbackProc,
                                    void * __nullable               inUserData,
                                    CFRunLoopRef __nullable         inCallbackRunLoop,
                                    CFStringRef __nullable          inCallbackRunLoopMode,
                                    UInt32                          inFlags,
                                    AudioQueueRef __nullable * __nonnull outAQ)          __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

#if defined(__BLOCKS__) && !TARGET_OS_IPHONE
/*!
    @function   AudioQueueNewOutputWithDispatchQueue
    @abstract   Creates a new audio queue for playing audio data.
    @discussion
        To create an playback audio queue, you allocate buffers, then queue buffers (using
        AudioQueueEnqueueBuffer). The callback receives buffers and typically queues them again.
        To schedule a buffer for playback, providing parameter and start time information, call
        AudioQueueEnqueueBufferWithParameters.
       
    @param      outAQ
        On return, this variable contains a pointer to the newly created playback audio queue
        object.
    @param      inFormat
        A pointer to a structure describing the format of the audio data to be played. For
        linear PCM, only interleaved formats are supported. Compressed formats are supported.
    @param      inFlags
        Reserved for future use. Pass 0.
    @param      inCallbackDispatchQueue
        The dispatch queue from which inCallbackBlock is to be called.
    @param      inCallbackBlock
        A pointer to a callback block to be called when the audio queue has finished playing
        a buffer.
    @result     An OSStatus result code.
*/
extern OSStatus             
AudioQueueNewOutputWithDispatchQueue(AudioQueueRef __nullable * __nonnull outAQ,
                                    const AudioStreamBasicDescription *inFormat,
                                    UInt32                          inFlags,
                                    dispatch_queue_t                inCallbackDispatchQueue,
                                    AudioQueueOutputCallbackBlock   inCallbackBlock)        __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*!
    @function   AudioQueueNewInputWithDispatchQueue
    @abstract   Creates a new audio queue for recording audio data.
    @discussion
        
        Outline of how to use the queue for input:
        
        - create input queue
        - allocate buffers
        - enqueue buffers (AudioQueueEnqueueBuffer, not with parameters, no packet descriptions)
        - the callback receives buffers and re-enqueues them
        
    @param      outAQ
        On return, this variable contains a pointer to the newly created recording audio queue
        object.
    @param      inFormat
        A pointer to a structure describing the format of the audio data to be recorded. For
        linear PCM, only interleaved formats are supported. Compressed formats are supported.
    @param      inFlags
        Reserved for future use. Pass 0.
    @param      inCallbackDispatchQueue
        The dispatch queue from which inCallbackBlock is to be called.
    @param      inCallbackBlock
        A pointer to a callback block to be called when the audio queue has finished filling
        a buffer.
    @result     An OSStatus result code.
*/
extern OSStatus             
AudioQueueNewInputWithDispatchQueue(AudioQueueRef __nullable * __nonnull outAQ,
                                    const AudioStreamBasicDescription *inFormat,
                                    UInt32                          inFlags,
                                    dispatch_queue_t                inCallbackDispatchQueue,
                                    AudioQueueInputCallbackBlock    inCallbackBlock)        __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
#endif // defined(__BLOCKS__) && !TARGET_OS_IPHONE

/*!
    @function   AudioQueueDispose
    @abstract   Disposes an existing audio queue.
    @discussion
        Disposing of the audio queue also disposes of all its resources, including its buffers.
    @param      inAQ
        The audio queue you want to dispose of
    @param      inImmediate
        If you pass true, the audio queue is disposed of immediately (that is, synchronously).
        If you pass false, disposal does not take place until all enqueued buffers are
        processed. Whether you call AudioQueueDispose synchronously or asynchronously, you can
        no longer interact with the queue, and the queue no longer invokes any callbacks to your
        application after the function returns.
		
		Note that if AudioQueueDispose is called from a buffer completion callback or property
		listener, you may receive further callbacks afterwards.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueDispose(                  AudioQueueRef           inAQ, 
                                    Boolean                 inImmediate)            __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

#pragma mark -
#pragma mark Buffer Management
//=============================================================================
//  Buffer Management
//=============================================================================

/*!
    @function   AudioQueueAllocateBuffer
    @abstract   Asks an audio queue to allocate a buffer.
    @discussion
        Once allocated, the pointer to the buffer and the buffer's size are fixed and cannot be
        changed. The mAudioDataByteSize field in the audio queue buffer structure,
        AudioQueueBuffer, is initially set to 0.
        
    @param      inAQ
        The audio queue you want to allocate a buffer.
    @param      inBufferByteSize
        The desired size of the new buffer, in bytes. An appropriate buffer size depends on the
        processing you will perform on the data as well as on the audio data format.
    @param      outBuffer
        On return, points to the newly created audio buffer. The mAudioDataByteSize field in the
        audio queue buffer structure, AudioQueueBuffer, is initially set to 0.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueAllocateBuffer(           AudioQueueRef           inAQ,
                                    UInt32                  inBufferByteSize,
                                    AudioQueueBufferRef __nullable * __nonnull outBuffer)              __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function   AudioQueueAllocateBuffer
    @abstract   Asks an audio queue to allocate a buffer.
    @discussion
        Once allocated, the pointer to the buffer and the buffer's size are fixed and cannot be
        changed. The mAudioDataByteSize field in the audio queue buffer structure,
        AudioQueueBuffer, is initially set to 0.
        
    @param      inAQ
        The audio queue you want to allocate a buffer.
    @param      inBufferByteSize
        The desired size of the new buffer, in bytes. An appropriate buffer size depends on the
        processing you will perform on the data as well as on the audio data format.
    @param      inNumberPacketDescriptions
        The desired capacity of the packet description array in the new buffer.
    @param      outBuffer
        On return, points to the newly created audio buffer. The mAudioDataByteSize field in the
        audio queue buffer structure, AudioQueueBuffer, is initially set to 0.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueAllocateBufferWithPacketDescriptions(
                                    AudioQueueRef           inAQ,
                                    UInt32                  inBufferByteSize,
                                    UInt32                  inNumberPacketDescriptions,
                                    AudioQueueBufferRef __nullable * __nonnull outBuffer)              __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

/*!
    @function   AudioQueueFreeBuffer
    @abstract   Disposes of an audio queue buffer.
    @discussion
        This function disposes of the buffer allocated by AudioQueueAllocateBuffer. Disposing of
        an audio queue also automatically disposes of any associated buffers and timeline
        objects. Call this function only if you want to dispose of a particular buffer while
        continuing to use an audio queue. You can dispose of buffers only when the associated
        queue is stopped (that is, not processing audio data).
    @param      inAQ
        The queue from which the buffer was allocated.
    @param      inBuffer
        The buffer to be disposed.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueFreeBuffer(               AudioQueueRef           inAQ,
                                    AudioQueueBufferRef     inBuffer)           __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);



/*!
    @function   AudioQueueEnqueueBuffer
    @abstract   Assigns a buffer to an audio queue for recording or playback.
    @discussion
        If the buffer was allocated with AudioQueueAllocateBufferWithPacketDescriptions,
        the client should provide packet descriptions in the buffer's mPacketDescriptions
        and mPacketDescriptionCount fields rather than in inPacketDescs and
        inNumPacketDescs, which should be NULL and 0, respectively, in this case.
        
        For an input queue, pass 0 and NULL for inNumPacketDescs and inPacketDescs,
        respectively. Your callback will receive packet descriptions owned by the audio queue.

    @param      inAQ
        The audio queue you are assigning the buffer to.
    @param      inBuffer
        The buffer to queue (that is, to be recorded into or played from).
    @param      inNumPacketDescs
        The number of packet descriptions pointed to by the inPacketDescs pointer. Applicable
        only for output queues and required only for variable-bit-rate (VBR) audio formats. Pass
        0 for input queues (no packet descriptions are required).
    @param      inPacketDescs
        An array of packet descriptions. Applicable only for output queues and required only for
        variable-bit-rate (VBR) audio formats. Pass NULL for input queues (no packet
        descriptions are required).
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueEnqueueBuffer(            AudioQueueRef                       inAQ,
                                    AudioQueueBufferRef                 inBuffer,
                                    UInt32                              inNumPacketDescs,
                                    const AudioStreamPacketDescription * __nullable inPacketDescs)      __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function   AudioQueueEnqueueBufferWithParameters
    @abstract   Assigns a buffer to an audio queue for playback, providing parameters
                and start time information.
    @discussion
        You can exert some control of the buffer queue by using this function. You can assign
        audio queue settings that are in effect carried by an audio queue buffer as you enqueue
        it. Hence, these changes only take effect when an audio queue buffer begins playing.
        
        This function queues a buffer for playback only, not for recording. Audio queues for
        recording have no parameters, do not support variable-bit-rate (VBR) formats (which
        might require trimming), and have a different way to handle timing. When queued for
        playback, the buffer must contain the audio data to be played back. See
        AudioQueueEnqueueBuffer for details on queuing a buffer for recording.

        If the buffer was allocated with AudioQueueAllocateBufferWithPacketDescriptions,
        the client should provide packet descriptions in the buffer's mPacketDescriptions
        and mPacketDescriptionCount fields rather than in inPacketDescs and
        inNumPacketDescs, which should be NULL and 0, respectively, in this case.
    @param      inAQ
        The audio queue associated with the buffer.
    @param      inBuffer
        The buffer to be played from.
    @param      inNumPacketDescs
        The number of packet descriptions pointed to by the inPacketDescs parameter. Required
        only for variable-bit-rate (VBR) audio formats. Pass 0 if no packet descriptions are
        required.
    @param      inPacketDescs
        A pointer to an array of audio stream packet descriptions. Required only for VBR audio
        formats. Pass NULL if no packet descriptions are required.
    @param      inTrimFramesAtStart
        The number of priming frames to skip at the start of the buffer.
    @param      inTrimFramesAtEnd
        The number of frames to skip at the end of the buffer.
    @param      inNumParamValues
        The number of parameter values pointed to by the inParamValues parameter.
    @param      inParamValues
        An array of parameter values. (In Mac OS X v10.5, there is only one parameter,
        kAudioQueueParam_Volume.) These values are set before buffer playback and cannot be
        changed while the buffer is playing. How accurately changes in parameters can be
        scheduled depends on the size of the buffer. If there are no parameters to set
        (inNumParamValues = 0), pass NULL.
    @param      inStartTime
        A pointer to a structure containing the desired start time for playing the buffer. If
        you specify the time using the mSampleTime field of the AudioTimeStamp structure, the
        sample time is relative to the time the queue started. If you pass NULL for the start
        time, the buffer starts immediately after the previously queued buffer, or as soon as
        possible if no buffers are queued ahead of it. Buffers are played in the order they are
        queued. If multiple buffers are queued, their times must be in ascending order or NULL;
        otherwise, an error occurs. The start time indicates when the actual audio data in the
        buffer is to be played (that is, the trim frames are not counted).
        
        Note: When specifying a start time for a buffer, if the buffer is not the first enqueued
        since AudioQueueStop or AudioQueueReset, it is normally necessary to call AudioQueueFlush
        before AudioQueueEnqueueBufferWithParameters.
    @param      outActualStartTime
        On return, points to an AudioTimeStamp structure indicating when the buffer will
        actually play.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueEnqueueBufferWithParameters(
                                    AudioQueueRef                                inAQ,
                                    AudioQueueBufferRef                          inBuffer,
                                    UInt32                                       inNumPacketDescs,
                                    const AudioStreamPacketDescription * __nullable inPacketDescs,
                                    UInt32                                       inTrimFramesAtStart,
                                    UInt32                                       inTrimFramesAtEnd,
                                    UInt32                                       inNumParamValues,
                                    const AudioQueueParameterEvent * __nullable  inParamValues,
                                    const AudioTimeStamp * __nullable            inStartTime,
                                    AudioTimeStamp * __nullable                  outActualStartTime)     __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

#pragma mark -
#pragma mark Queue Control
//=============================================================================
//  Queue Control
//=============================================================================

/*!
    @function   AudioQueueStart
    @abstract   Begins playing or recording audio.
    @discussion
        If the audio hardware is not already running, this function starts it.
    @param      inAQ
        The audio queue to start.
    @param      inStartTime
        A pointer to the time at which the audio queue should start. If you specify the time
        using the mSampleTime field of the AudioTimeStamp structure, the sample time is
        referenced to the sample frame timeline of the associated audio device. May be NULL.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueStart(                    AudioQueueRef                     inAQ,
                                    const AudioTimeStamp * __nullable inStartTime)        __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function   AudioQueuePrime
    @abstract   Begins decoding buffers in preparation for playback.
    @discussion
        This function begins decoding buffers in preparation for playback. It returns when at
        least the number of audio sample frames are decoded and ready to play or when all
        enqueued buffers have been completely decoded. To ensure that a buffer has been decoded
        and is completely ready for playback, before playback:
            1.  Call AudioQueueEnqueueBuffer.
            2.  Call AudioQueuePrime, which waits if you pass 0 to have a default number of
                frames decoded.
            3.  Call AudioQueueStart.

        Calls to AudioQueuePrime following AudioQueueStart/AudioQueuePrime, and before
        AudioQueueReset/AudioQueueStop, will have no useful effect. In this situation,
        outNumberOfFramesPrepared will not have a useful return value.
    @param      inAQ
        The audio queue to be primed.
    @param      inNumberOfFramesToPrepare
        The number of frames to decode before returning. Pass 0 to decode all enqueued buffers.
    @param      outNumberOfFramesPrepared
        If not NULL, on return, a pointer to the number of frames actually decoded and prepared
        for playback.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueuePrime(                    AudioQueueRef           inAQ,
                                    UInt32                  inNumberOfFramesToPrepare,
                                    UInt32 * __nullable     outNumberOfFramesPrepared)  __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function   AudioQueueStop
    @abstract   Stops playing or recording audio.
    @discussion
        This function resets the audio queue and stops the audio hardware associated with the
        queue if it is not in use by other audio services. Synchronous stops occur immediately,
        regardless of previously buffered audio data. Asynchronous stops occur after all queued
        buffers have been played or recorded.
    @param      inAQ
        The audio queue to stop.
    @param      inImmediate
        If you pass true, the stop request occurs immediately (that is, synchronously), and the
        function returns when the audio queue has stopped. Buffer callbacks are invoked during
        the stopping. If you pass false, the function returns immediately, but the queue does
        not stop until all its queued buffers are played or filled (that is, the stop occurs
        asynchronously). Buffer callbacks are invoked as necessary until the queue actually
        stops. Also, a playback audio queue callback calls this function when there is no more
        audio to play.

        Note that when stopping immediately, all pending buffer callbacks are normally invoked
        during the process of stopping. But if the calling thread is responding to a buffer
        callback, then it is possible for additional buffer callbacks to occur after
        AudioQueueStop returns.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueStop(                     AudioQueueRef           inAQ,
                                    Boolean                 inImmediate)            __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function   AudioQueuePause
    @abstract   Pauses audio playback or recording.
    @discussion
        Pausing the queue does not affect buffers or reset the audio queue. To resume playback
        or recording using the audio queue, call AudioQueueStart.
    @param      inAQ
        The queue to be paused.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueuePause(                    AudioQueueRef           inAQ)       __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function   AudioQueueFlush
    @abstract   Resets the audio queue's decoder state.
    @discussion
        After all queued buffers have been played, the function cleans up all decoder state
        information. You must call this function following a sequence of buffers of encoded
        audio; otherwise, some of the audio might not play in the next set of queued buffers.
        The only time it is not necessary to call AudioQueueFlush is following AudioQueueStop
        with inImmediate=false. (This action internally calls AudioQueueFlush.)
        
        Also, you might wish to call this function before calling AudioQueueStop depending on
        whether you want to stop immediately regardless of what has played or whether you want
        to ensure that all buffered data and all data that is in the middle of processing gets
        recorded or played before stopping.
        
    @param      inAQ
        The audio queue to be flushed.
        
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueFlush(                    AudioQueueRef           inAQ)            __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function   AudioQueueReset
    @abstract   Resets an audio queue.
    @discussion
        This function immediately resets an audio queue, flushes any queued buffer, removes all
        buffers from previously scheduled use, and resets any decoder and digital signal
        processing (DSP) state information. It also invokes callbacks for any flushed buffers.
        If you queue any buffers after calling this function, processing does not occur until
        the decoder and DSP state information is reset. Hence, a discontinuity (that is, a
        "glitch") might occur.

        Note that when resetting, all pending buffer callbacks are normally invoked
        during the process of resetting. But if the calling thread is responding to a buffer
        callback, then it is possible for additional buffer callbacks to occur after
        AudioQueueReset returns.
    @param      inAQ
        The audio queue to reset.

    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueReset(                    AudioQueueRef           inAQ)            __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

#pragma mark -
#pragma mark Parameter Management
//=============================================================================
//  Parameter Management
//=============================================================================

/*!
    @function   AudioQueueGetParameter
    @abstract   Obtains an audio queue parameter value.
    @discussion
        You can access the current parameter values for an audio queue at any time with this
        function.
    @param      inAQ
        The audio queue whose parameter value you want to obtain.
    @param      inParamID
        The ID of the parameter you want to obtain. In Mac OS X v10.5, audio queues have one
        parameter available: kAudioQueueParam_Volume, which controls the queue's playback
        volume.
    @param      outValue
        On return, points to the current value of the specified parameter.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueGetParameter(             AudioQueueRef               inAQ,
                                    AudioQueueParameterID       inParamID,
                                    AudioQueueParameterValue *  outValue)       __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function   AudioQueueSetParameter
    @abstract   Sets an audio queue parameter value.
    @discussion
    @param      inAQ
        The audio queue whose parameter value you want to set.
    @param      inParamID
        The ID of the parameter you want to set.
    @param      inValue
        The parameter value to set.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueSetParameter(             AudioQueueRef               inAQ,
                                    AudioQueueParameterID       inParamID,
                                    AudioQueueParameterValue    inValue)        __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

                                                                        
#pragma mark -
#pragma mark Property Management
//=============================================================================
//  Property Management
//=============================================================================

/*!
    @function   AudioQueueGetProperty
    @abstract   Obtains an audio queue property value.
    @discussion 
    @param      inAQ
        The audio queue whose property value you want to obtain.
    @param      inID
        The ID of the property you want to obtain. See "Audio Queue Property IDs."
    @param      outData
        On return, points to the desired property value.
    @param      ioDataSize
        A pointer to the size of the property data. On input, points to the maximum bytes of
        space the caller expects to receive. On return, points to the actual data size.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueGetProperty(              AudioQueueRef           inAQ,
                                    AudioQueuePropertyID    inID,
                                    void *                  outData,
                                    UInt32 *                ioDataSize)             __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function   AudioQueueSetProperty
    @abstract   Sets an audio queue property value.
    @discussion 
    @param      inAQ
        The audio queue whose property value you want to set.
    @param      inID
        The ID of the property you want to set. See "Audio Queue Property IDs" for the various
        audio queue properties.
    @param      inData
        A pointer to the property value to set.
    @param      inDataSize
        The size of the property data.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueSetProperty(              AudioQueueRef           inAQ,
                                    AudioQueuePropertyID    inID,
                                    const void *            inData,
                                    UInt32                  inDataSize)             __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);


/*!
    @function   AudioQueueGetPropertySize
    @abstract   Obtains the size of an audio queue property.
    @discussion 
    @param      inAQ
        The audio queue containing the property value whose size you want to obtain.
    @param      inID
        The ID of the property value whose size you want to obtain. See "Audio Queue Property
        IDs" for possible values.
    @param      outDataSize
        On return, points to the size of the specified property value.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueGetPropertySize(          AudioQueueRef           inAQ,
                                    AudioQueuePropertyID    inID,
                                    UInt32 *                outDataSize)            __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function   AudioQueueAddPropertyListener
    @abstract   Adds a listener callback for a property.
    @discussion 
        This callback is used to act upon a change in an audio queue property such as
        kAudioQueueProperty_IsRunning. For instance, if your application has a user interface
        with a Play/Stop button, and kAudioQueueProperty_IsRunning changes, you need to update
        your button.
    @param      inAQ
        The audio queue that owns the property you want to assign the listener callback to.
    @param      inID
        The ID of the property to which you want to assign a listener callback. See "Audio Queue Property IDs".
    @param      inProc
        The listener callback to be called when the property value changes.
    @param      inUserData
        A value to be passed to the listener callback when it is called.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueAddPropertyListener(      AudioQueueRef                   inAQ,
                                    AudioQueuePropertyID            inID,
                                    AudioQueuePropertyListenerProc  inProc,
                                    void * __nullable               inUserData)     __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function   AudioQueueRemovePropertyListener
    @abstract   Removes a listener callback for a property.
    @discussion 
    @param      inAQ
        The audio queue that owns the property from which you want to remove a listener.
    @param      inID
        The ID of the property from which you want to remove a listener.
    @param      inProc
        The listener being removed.
    @param      inUserData
        The same inUserData value that was previously passed to AudioQueueAddPropertyListener.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueRemovePropertyListener(   AudioQueueRef                   inAQ,
                                    AudioQueuePropertyID            inID,
                                    AudioQueuePropertyListenerProc  inProc,
                                    void * __nullable               inUserData)     __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

                                    

#pragma mark -
#pragma mark Handling Timing
//=============================================================================
//  Handling Timing
//=============================================================================

/*!
    @function   AudioQueueCreateTimeline
    @abstract   Creates a timeline object.
    @discussion
        You need to instantiate a timeline object if you want to know about any timeline
        discontinuities. See AudioQueueGetCurrentTime for more details.
    @param      inAQ
        The audio queue to associate with the new timeline object.
    @param      outTimeline
        On return, points to the newly created timeline object.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueCreateTimeline(           AudioQueueRef           inAQ,
                                    AudioQueueTimelineRef __nullable * __nonnull outTimeline)            __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function   AudioQueueDisposeTimeline
    @abstract   Disposes of a timeline object.
    @discussion
        Disposing of an audio queue automatically disposes of any associated timeline objects.
        Call this function only if you want to dispose of a timeline object and not the audio
        queue associated with it.
    @param      inAQ
        The audio queue associated with the timeline object you want to dispose of.
    @param      inTimeline
        The timeline object to dispose of.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueDisposeTimeline(          AudioQueueRef           inAQ,
                                    AudioQueueTimelineRef   inTimeline)             __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function   AudioQueueGetCurrentTime
    @abstract   Obtains the current audio queue time.
    @discussion
        You must specify a timeline object if you want to be notified about any timeline
        discontinuities in the outTimelineDiscontinuity parameter. If you don't care about
        discontinuities, pass NULL in the inTimeLine and outTimelineDiscontinuity parameters.
    @param      inAQ
        The audio queue whose current time you want to obtain.
    @param      inTimeline
        The audio queue timeline object to which any timeline discontinuities are reported. May
        be NULL.
    @param      outTimeStamp
        On return, points to an audio timestamp structure containing the current audio queue
        time. The mSampleTime field is in terms of the audio queue's sample rate, and relative
        to the time at which the queue has started or will start.
    @param      outTimelineDiscontinuity
        Can be NULL. On return, only set to true or false if the inTimeLine parameter is not
        NULL. Set to true if a discontinuity has occurred in the sample timeline of the audio
        queue. For instance, the device's sample rate changed and a gap occurred in playback or
        recording, or the audio queue was unable to prepare and playback in time because it was
        late.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueGetCurrentTime(           AudioQueueRef                    inAQ,
                                    AudioQueueTimelineRef __nullable inTimeline,
                                    AudioTimeStamp * __nullable      outTimeStamp,
                                    Boolean * __nullable             outTimelineDiscontinuity)       __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function   AudioQueueDeviceGetCurrentTime
    @abstract   Obtains the current time of the audio device associated with an audio queue.
    @discussion
        If the audio device associated with the audio queue is not running, the only valid field
        in the audio timestamp structure is mHostTime. This result differentiates the action of
        this function from that of the AudioDeviceGetCurrentTime function, (declared in
        AudioHardware.h) which returns an error if the audio device is not running.
    @param      inAQ
        The audio queue whose audio device is to be queried.
    @param      outTimeStamp
        A pointer to a structure that, on return, contains the current time of the audio device
        associated with the audio queue.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueDeviceGetCurrentTime(     AudioQueueRef           inAQ,
                                    AudioTimeStamp *        outTimeStamp)      __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function   AudioQueueDeviceTranslateTime
    @abstract   Converts the time in the time base of the associated audio device from one
                representation to another.
    @discussion
        This function converts from one time representation to another (for example, from sample
        time to host time or vice versa):
        
        <ul>
        <li>    Sample time is the absolute sample frame time.
        Sample numbers are the count of the samples on the audio device.</li>
        <li>    Host time is the
        time base of the host machine such as the time of the bus clock on the CPU.</li>
        </ul>

        The mSampleTime field in the AudioTimestamp structure (described in Core Audio Data
        Types Reference) is always in device time, not in audio queue time. Audio queue time is
        relative to the audio queue's start time. The associated audio device has to be running
        for the AudioQueueDeviceTranslateTime function to provide a result.
    @param      inAQ
        The queue whose audio device is to perform the requested time translation.
    @param      inTime
        A pointer to a structure containing the time to be translated.
    @param      outTime
        A pointer to the the translated time.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueDeviceTranslateTime(      AudioQueueRef           inAQ,
                                    const AudioTimeStamp *  inTime,
                                    AudioTimeStamp *        outTime)        __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function   AudioQueueDeviceGetNearestStartTime
    @abstract   Obtains an audio device's start time that is closest to a requested start time.
    @discussion
    @param      inAQ
        The audio queue whose device's nearest start time you want to obtain.
    @param      ioRequestedStartTime
        On entry, points to the requested start time. On return, points to the actual start time.
    @param      inFlags
        Reserved for future use. Pass 0.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueDeviceGetNearestStartTime(AudioQueueRef           inAQ,
                                    AudioTimeStamp *        ioRequestedStartTime,
                                    UInt32                  inFlags)        __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

#pragma mark -
#pragma mark Offline Rendering
//=============================================================================
//  Offline Rendering
//=============================================================================

/*!
    @function   AudioQueueSetOfflineRenderFormat
    @abstract   Specify an audio format to which the queue will perform subsequent offline rendering,
                or disable offline rendering.
    @discussion
                An output queue's audio playback can be redirected for capture to an audio file,
                to support an export function, for example. AudioQueueSetOfflineRenderFormat switches
                a queue between normal and offline rendering modes.
    @param      inAQ
        The output queue whose offline rendering mode is to be changed.
    @param      inFormat
        The desired format for offline rendering. Pass NULL to disable offline rendering and return the
        queue to normal output to an audio device. This format must be linear PCM and (if not mono)
        interleaved.
    @param      inLayout
        The desired channel layout for offline rendering; also NULL when disabling offline rendering.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueSetOfflineRenderFormat(   AudioQueueRef                                  inAQ,
                                    const AudioStreamBasicDescription * __nullable inFormat,
                                    const AudioChannelLayout * __nullable          inLayout)
																		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function   AudioQueueOfflineRender
    @abstract   Obtain a buffer of audio output from a queue in offline rendering mode.
    @discussion
    @param      inAQ
        The output queue from which to obtain output.
    @param      inTimestamp
        The point in time corresponding to the beginning of the output buffer. Only mSampleTime
        is used. mFlags must include kAudioTimeStampSampleTimeValid.
    @param      ioBuffer
        The buffer into which the queue will render.
    @param      inNumberFrames
        The number of frames of audio to render. Note that fewer frames than requested may be returned.
        This can happen if insufficient data was enqueued.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueOfflineRender(            AudioQueueRef           inAQ,
                                    const AudioTimeStamp *  inTimestamp,
                                    AudioQueueBufferRef     ioBuffer,
                                    UInt32                  inNumberFrames)     __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

#pragma mark -
#pragma mark Processing Taps
//=============================================================================
//  Processing Taps
//=============================================================================


/*!
    @function   AudioQueueProcessingTapNew
    @abstract   Create a new processing tap
    @discussion
                This function creates a processing tap on a given audio queue. A
                processing tap can only be established (or removed) on an audio queue that is
                stopped (paused is not sufficient). The processing tap will then be used to
                process either decoded data in the case of an output queue, or input data
                (before it is encoded) in the case of an input queue.

                The processing is performed on audio either before or after any effects or other
                processing (varispeed, etc) is applied by the audio queue, depending on inFlags.
    
    @param      inAQ    
                    The audio queue from which to create the processing tap
    @param      inCallback
                    A callback which the queue will call to process the audio
    @param      inClientData
                    Client data provided to the callback
    @param      inFlags
                    Flags that are used to control aspects of the processing tap.
                    Valid flags are:
                        - kAudioQueueProcessingTap_PreEffects: processing is done before any
                            further effects are applied by the audio queue to the audio
                        - kAudioQueueProcessingTap_PostEffects: processing is done after all
                            processing is done, including that of other taps.
                        - kAudioQueueProcessingTap_Siphon
    @param      outMaxFrames
                    The maximum number of sample frames that can be requested of a processing
                    tap at any one time. Typically this will be approximately 50 msec of audio
                    (2048 samples @ 44.1kHz)
    @param      outProcessingFormat
                    The format in which the client will receive the audio data to be processed.
                    This will always be the same sample rate as the client format and usually
                    the same number of channels as the client format of the audio queue. (NOTE:
                    the number of channels may be different in some cases if the client format
                    has some channel count restrictions, for instance the client provides 5.1
                    AAC, but the decoder can only produce stereo). The channel order, if the
                    same as the client format, will be the same as the client channel order. If
                    the channel count is changed, it will be to either 1 (mono) or 2 (stereo, in
                    which case the first channel is left, the second right).

                    If the data is not in a convenient format for the client to process in, then
                    the client should convert the data to and from that format. This is the most
                    efficient mechanism to use (as the audio queue can chose a format that is
                    most efficient from its playback (or recording) requirement.
    @param      outAQTap
                    The processing tap object.
                    
    @result     An OSStatus result code.
*/
extern OSStatus 
AudioQueueProcessingTapNew(         AudioQueueRef                   inAQ,
                                    AudioQueueProcessingTapCallback inCallback,
                                    void * __nullable               inClientData,
                                    AudioQueueProcessingTapFlags    inFlags,
                                    UInt32 *                        outMaxFrames,
                                    AudioStreamBasicDescription *   outProcessingFormat,
                                    AudioQueueProcessingTapRef __nullable * __nonnull outAQTap)
                                        __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_6_0);

/*!
    @function   AudioQueueProcessingTapDispose
    @abstract   Dispose a processing tap object
    @discussion 
                As with AudioQueueProcessingTapNew, this call can only be made on an
                audio queue that is stopped (paused is not sufficient)
    
    @param      inAQTap
                    The processing tap to dispose.

   @result     An OSStatus result code.
*/
extern OSStatus 
AudioQueueProcessingTapDispose(     AudioQueueProcessingTapRef      inAQTap)
                                        __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_6_0);

/*!
    @function   AudioQueueProcessingTapGetSourceAudio
    @abstract   Used by a processing tap to retrieve source audio.
    @discussion 
        This function may only be called from the processing tap's callback.
    
    @param      inAQTap
                    the processing tap
    @param      inNumberFrames
                    the number of frames the processing tap requires for its processing
    @param      ioTimeStamp
                    On an input audio queue, the timestamp is returned from this function.
                    On an output audio queue, the caller must provide a continuous timestamp.
    @param      outFlags
                    flags to describe state about the input requested, e.g.
                    discontinuity/complete
    @param      outNumberFrames
                    the number of source frames that have been provided by the parent audio
                    queue. This can be less than the number of requested frames specified in
                    inNumberFrames
    @param      ioData
                    the audio buffer list which will contain the source data. The audio queue owns
                    the buffer pointers if NULL pointers were provided (recommended). In this case
                    the source buffers are only valid for the duration of the processing tap
                    callback. If the buffer pointers are non-NULL, then they must be big enough to
                    hold inNumberFrames, and the audio queue will copy its source data into those
                    buffers.
                    
   @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueProcessingTapGetSourceAudio(
                                    AudioQueueProcessingTapRef      inAQTap,
                                    UInt32                          inNumberFrames,
                                    AudioTimeStamp *                ioTimeStamp,
                                    AudioQueueProcessingTapFlags *  outFlags,
                                    UInt32 *                        outNumberFrames,
                                    AudioBufferList *               ioData)
                                        __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_6_0);

/*!
    @function   AudioQueueProcessingTapGetQueueTime
    @abstract   Used by a processing tap to retrieve the queue's current time.
    @discussion 
        This function may only be called from the processing tap's callback, and only
        for audio output queues. It must be called after calling
        AudioQueueProcessingTapGetSourceAudio.
    
    @param      inAQTap
                    the processing tap
    @param      outQueueSampleTime
                    the current sample time of the audio queue. This will appear to be stationary
                    if the queue is paused.
    @param      outQueueFrameCount
                    the number of sample frames of queue time corresponding to the current chunk of
                    audio being processed by the tap. This will differ from the frame count passed
                    to the tap if the queue's playback rate is currently other than 1.0, due to the
                    use of time compression/expansion. The frame count can also be 0 if the queue is
                    paused.
                    
   @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueProcessingTapGetQueueTime(    AudioQueueProcessingTapRef  inAQTap,
                                        Float64 *                   outQueueSampleTime,
                                        UInt32 *                    outQueueFrameCount)
                                        __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

#ifdef __cplusplus
}
#endif

CF_ASSUME_NONNULL_END

#endif // AudioToolbox_AudioQueue_h

// ==========  AudioToolbox.framework/Headers/AUGraph.h
/*!
	@file		AUGraph.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2000-2015 by Apple, Inc., all rights reserved.
	@abstract	API's to manage graphs of AudioUnits.

	@discussion
		An AUGraph is a complete description of an audio signal processing network. The AUGraph
		API's maintain a set of AudioUnits, audio connections between their inputs and outputs, and
		any callbacks used to provide inputs. It also allows the embedding of sub-graphs within
		parent graphs to allow for a logical organization of parts of an overall signal chain. The
		graph's AudioUnits do the actual audio processing.

		The AUGraph may be introspected, in order to get complete information about all of the
		AudioUnits in the graph.  The various nodes (AUNode) in the AUGraph representing AudioUnits
		or sub graphs may be added or removed, and the interactions between them modified.

		An AUGraph's state can be manipulated in both the rendering thread and in other threads.
		Consequently, any activities that affect the state of the graph are guarded with locks and a
		messaging model between any calling thread and the thread upon which the AUGraph's output
		unit is called (the render thread).

		An AUGraph will have a single head node - what is referred to below as its output unit. The
		output unit is used to both start and stop the rendering operations of a graph, and as the
		dispatch point for the safe manipulation of the state of the graph while it is running.
*/

#ifndef AudioToolbox_AUGraph_h
#define AudioToolbox_AUGraph_h

#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreAudio/CoreAudioTypes.h>
	#include <AudioUnit/AudioUnit.h>
#else
	#include <CoreAudioTypes.h>
	#include <AudioUnit.h>
#endif

CF_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
extern "C"
{
#endif

/*!
	@typedef	AUGraph
	@abstract	A reference to an AUGraph object.
*/
typedef	struct OpaqueAUGraph	*AUGraph;

/*!
	@typedef	AUNode
	@abstract	Used to represent a member of an AUGraph
*/
typedef SInt32 	AUNode;

/*!
    @enum AUGraph error codes
    @abstract   These are the error codes returned from the AUGraph API.
    @constant   kAUGraphErr_NodeNotFound
				The specified node cannot be found
	@constant	kAUGraphErr_InvalidConnection
				The attempted connection between two nodes cannot be made
	@constant	kAUGraphErr_OutputNodeErr
				AUGraphs can only contain one OutputUnit.
				this error is returned if trying to add a second output unit
				or the graph's output unit is removed while the graph is running
	@constant	kAUGraphErr_CannotDoInCurrentContext
				To avoid spinning or waiting in the render thread (a bad idea!), many of the
				calls to AUGraph can return: kAUGraphErr_CannotDoInCurrentContext. This
				result is only generated when you call an AUGraph API from its render
				callback. It means that the lock that it required was held at that time, by
				another thread. If you see this result code, you can generally attempt the
				action again - typically the NEXT render cycle (so in the mean time the lock
				can be cleared), or you can delegate that call to another thread in your
				app. You should not spin or put-to-sleep the render thread.

	@constant	kAUGraphErr_InvalidAudioUnit
*/
CF_ENUM(OSStatus)
{
	kAUGraphErr_NodeNotFound 				= -10860,
	kAUGraphErr_InvalidConnection 			= -10861,
	kAUGraphErr_OutputNodeErr				= -10862,
	kAUGraphErr_CannotDoInCurrentContext	= -10863,
	kAUGraphErr_InvalidAudioUnit			= -10864
};

#pragma mark -
/*!
    @function	NewAUGraph
    @abstract   creates a new AUGraph
    @discussion	creates a new AUGraph
    @param		outGraph		the new AUGraph object
*/
extern OSStatus
NewAUGraph(			AUGraph	__nullable * __nonnull outGraph)		__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*!
    @function	DisposeAUGraph
    @abstract   dispose an AUGraph
    @discussion	deallocates the AUGraph along with its nodes and their resources.
    @param		inGraph		the AUGraph object to be disposed
*/
extern OSStatus
DisposeAUGraph(		AUGraph			inGraph)						__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);


#pragma mark -
#pragma mark Node State
/*! 
	@functiongroup AU Node management
*/

/*!
    @function	AUGraphAddNode
    @abstract   Add a node to an AUGraph
    @discussion	This creates a node in the graph that is an AudioUnit, using the supplied
				AudioComponentDescription to find and open that unit.
    @param		inGraph			the AUGraph object
    @param		inDescription	the AudioComponentDescription used to find and open the AudioUnit
    @param		outNode			the newly added node
*/
extern OSStatus
AUGraphAddNode(		AUGraph								inGraph,
					const AudioComponentDescription	*	inDescription,
					AUNode *	  						outNode)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function	AUGraphRemoveNode
    @abstract   Remove a node from an AUGraph
    @discussion	Nodes can be removed from any thread context. The output node of
				the AUGraph cannot be removed while the graph is running.
    @param		inGraph			the AUGraph object
    @param		inNode			the node to be removed
*/
extern OSStatus
AUGraphRemoveNode(  AUGraph			inGraph,
					AUNode			inNode)							__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*!
    @function	AUGraphGetNodeCount
    @abstract   The number of nodes in an AUGraph
    @discussion	The number of nodes in an AUGraph
    @param		inGraph				the AUGraph object
    @param		outNumberOfNodes	the number of nodes
*/
extern OSStatus
AUGraphGetNodeCount(AUGraph			inGraph,
					UInt32 			*outNumberOfNodes)				__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*!
    @function	AUGraphGetIndNode
    @abstract   Returns the node at a given index
    @discussion	By using AUGraphGetNodeCount in conjunction with this call, you can
				iterate through the nodes of an AUGraph.
    @param		inGraph				the AUGraph object
    @param		inIndex				the index of the node to retrieve
	@param		outNode				the node at that index
*/
extern OSStatus
AUGraphGetIndNode(  AUGraph			inGraph,
					UInt32 			inIndex,
					AUNode			*outNode)						__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*!
    @function	AUGraphNodeInfo
    @abstract   Returns information about a particular AUNode
    @discussion	You can pass in NULL for any of the out parameters if you're not interested
				in that value.
    @param		inGraph				the AUGraph object
	@param		inNode				the node to query
    @param		outDescription		the component description that would describe the AudioUnit of this node
	@param		outAudioUnit		the AudioUnit of this node
*/
extern OSStatus
AUGraphNodeInfo(	AUGraph									inGraph,
					AUNode									inNode,
					AudioComponentDescription * __nullable	outDescription,
					AudioUnit __nullable * __nullable		outAudioUnit)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);
			

#if !TARGET_OS_IPHONE
#pragma mark -
#pragma mark Sub Graphs
/*! 
	@functiongroup Sub Graph Nodes
*/
/*!
    @function	AUGraphNewNodeSubGraph
    @abstract   Create a node that will represent a sub graph
	@discussion	This will create a node that represents a contained or member AUGraph.
				The AUGraph can be retrieved through the GetNodeInfoSubGraph call.
				The member AUGraph is owned by the parent graph and will be disposed when
				either:
				(1) The parent graph is disposed
				(2) The node is removed from the parent AUGraph
    @param		inGraph				the AUGraph object
	@param		outNode				the node that is used to refer to the sub-graph
*/
extern OSStatus
AUGraphNewNodeSubGraph( AUGraph				inGraph,
						AUNode				*outNode)			__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);

/*!
    @function	AUGraphGetNodeInfoSubGraph
    @abstract   Return an AUGraph represented by this node
	@discussion	This will return the sub graph represented by this AUNode.
    @param		inGraph				the AUGraph object
	@param		inNode				the node to query
	@param		outSubGraph			the sub-graph
*/
extern OSStatus
AUGraphGetNodeInfoSubGraph(	const AUGraph		inGraph,
							AUNode				inNode,
							AUGraph	__nullable * __nonnull outSubGraph)	__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
								
/*!
    @function	AUGraphIsNodeSubGraph
    @abstract   Does the node represent a sub graph
	@discussion	This will return true if the specified node represents a subgraph, false if not.
    @param		inGraph				the AUGraph object
	@param		inNode				the node to query
	@param		outFlag				true if the node is a subgraph, false if not
*/
extern OSStatus
AUGraphIsNodeSubGraph(		const AUGraph		inGraph,
							AUNode				inNode,
							Boolean *			outFlag)		__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);

#endif // !TARGET_OS_IPHONE

#pragma mark -
#pragma mark Node Interactions
/*! 
	@functiongroup Node Interactions
*/
/*! 
	@enum
	@abstract	The different types of node interactions
	@discussion We use the term interaction as a general term to describe some interaction 
				of a node. Currently, the interactions of a node that the graph manages are
				described below.
	@constant	kAUNodeInteraction_Connection
				connections between 2 audio units, 
	@constant	kAUNodeInteraction_InputCallback
				input callbacks being registered to a single audio unit's input bus.
*/
CF_ENUM(UInt32) {
	kAUNodeInteraction_Connection		= 1,
	kAUNodeInteraction_InputCallback	= 2
};

/*! 
	@struct		AudioUnitNodeConnection
	@abstract	A connection between two nodes
	@field		sourceNode
	@field		sourceOutputNumber
	@field		destNode
	@field		destInputNumber
*/
struct AudioUnitNodeConnection
{
	AUNode		sourceNode;
	UInt32		sourceOutputNumber;
	AUNode		destNode;
	UInt32		destInputNumber;
};
typedef struct AudioUnitNodeConnection AudioUnitNodeConnection;
typedef struct AudioUnitNodeConnection AUNodeConnection;

/*! 
	@struct		AUNodeRenderCallback
	@abstract	A callback used to provide input to an audio unit
	@discussion	Used to contain information when a callback is used
				to provide input to the specific node's specified input
	@field		destNode
	@field		destInputNumber
	@field		cback
*/
struct AUNodeRenderCallback 
{
	AUNode					destNode;
	AudioUnitElement		destInputNumber;
	AURenderCallbackStruct	cback;
};
typedef struct AUNodeRenderCallback AUNodeRenderCallback;

/*! 
	@struct		AUNodeInteraction
	@abstract	Used to describe the interaction between/with a node
	@discussion	This structure contains information about the interaction between
				two nodes (in the case of a connection), or the input to a node
				(in the case of a callback). 
				
				The type of the interaction is used to determine how to interpret the contents 
				of the following union.

				There may be other nodal interactions in the future, so NO ASSUMPTIONS should be made
				that these are the only 2 nodal interaction types; you must always check the 
				nodeInteractionType and only act on those types you understand
	
				Arrays of these structs can be returned, the addition of new members to the
				nodeInteraction union will NOT change the size of this structure
				
	@field		nodeInteractionType		the interaction type
	@field		nodeInteraction			a union providing information about the specified interaction
*/
struct AUNodeInteraction
{
	UInt32		nodeInteractionType;
	
	union
	{
		AUNodeConnection		connection;		
		AUNodeRenderCallback	inputCallback;

	}			nodeInteraction;
};
typedef struct AUNodeInteraction AUNodeInteraction;

/*! 
	@function	AUGraphConnectNodeInput
	@abstract	connect a node's output to a node's input
*/
extern OSStatus
AUGraphConnectNodeInput(	AUGraph			inGraph,
							AUNode			inSourceNode,
							UInt32			inSourceOutputNumber,
							AUNode			inDestNode,
							UInt32			inDestInputNumber)		__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*! 
	@function	AUGraphSetNodeInputCallback
	@abstract	Set a callback for the specified node's specified input.
	@param		inGraph
	@param		inDestNode
	@param		inDestInputNumber
	@param		inInputCallback		The callback that will provide input data to the node
*/
extern OSStatus
AUGraphSetNodeInputCallback (AUGraph						inGraph,
							AUNode							inDestNode,
							UInt32							inDestInputNumber,
							const AURenderCallbackStruct *	inInputCallback) 
																	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*! 
	@function	AUGraphDisconnectNodeInput
	@abstract	disconnect a node's input
	@discussion	This can be used to disconnect either a connection or callback interaction
				to the specified node input
	@param		inGraph
	@param		inDestNode
	@param		inDestInputNumber
*/
extern OSStatus
AUGraphDisconnectNodeInput(	AUGraph			inGraph,
							AUNode			inDestNode,
							UInt32			inDestInputNumber)		__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*! 
	@function	AUGraphClearConnections
	@abstract	clear all of the interactions in a graph
	@discussion	This will clear all connections and callback interactions of the nodes of a graph
	@param		inGraph
*/
extern OSStatus
AUGraphClearConnections(	AUGraph			inGraph)				__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*! 
	@function	AUGraphGetNumberOfInteractions
	@abstract	Retrieve the number of interactions of a graph
	@discussion	The number of node interactions currently being managed by the graph
	@param		inGraph
	@param		outNumInteractions
*/
extern OSStatus
AUGraphGetNumberOfInteractions(	AUGraph				inGraph,
								UInt32 *			outNumInteractions)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*! 
	@function	AUGraphGetInteractionInfo
	@abstract	Retrieve information about a particular interaction in a graph
	@discussion	Returns information about a particular interaction. 
				inInteractionIndex is based on the outNumInteractions value and is only valid if no 
				edits to the graph's state have been made.
				
				An app can iterate through the interactions (as with the nodes) of a graph by retrieving
				the number of interactions, and then iterating an index from 0 < numInteractions
	@param		inGraph
	@param		inInteractionIndex
	@param		outInteraction		the interaction information at the specified index
*/
extern OSStatus
AUGraphGetInteractionInfo(	AUGraph					inGraph,
							UInt32					inInteractionIndex,
							AUNodeInteraction *		outInteraction)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*! 
	@function	AUGraphCountNodeInteractions
	@abstract	Retrieve the number of interactions of a graph's node
	@discussion	The number of node interactions currently being managed by the graph for the specified node
	@param		inGraph
	@param		inNode
	@param		outNumInteractions
*/
extern OSStatus
AUGraphCountNodeInteractions(	AUGraph				inGraph,
								AUNode				inNode,
								UInt32 *			outNumInteractions)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*! 
	@function	AUGraphGetNodeInteractions
	@abstract	Retrieve information about the interactions in a graph for a given node
	@discussion	Retrieve information about the interactions in a graph for a given node 
	@param		inGraph
	@param		inNode
	@param		ioNumInteractions	
					on input, specifies the number of interactions that can be returned
					on output, specifies the number of interactions returned.
	@param		outInteractions		the interactions the specified node is involved in
*/
extern OSStatus
AUGraphGetNodeInteractions(	AUGraph					inGraph,
							AUNode					inNode,
							UInt32 *				ioNumInteractions,
							AUNodeInteraction *		outInteractions)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);



#pragma mark -
/*! 
	@functiongroup Updating an AUGraph
*/
/*! 
	@function	AUGraphUpdate
	@abstract	Updates the state of a running AUGraph
	
	@discussion
	Call this after performing a series of "edits" on the AUGraph with calls 
	such as AUGraphConnectNodeInput() to finalize those edits.
	The call will be synchronous if outIsUpdated is NULL, 
	meaning it will block until the changes are incorporated
	into the graph OR an error is returned from the update process
	if outIsUpdated is non-NULL, then AUGraphUpdate() will return 
	immediately and outIsUpdated will equal "true" if the changes 
	were already made (no more changes to make) or "false" if changes are still
	outstanding.

	Calling from the AUGraphRenderNotification callback:
	Connection and Disconnection events can be completely processed
	in the render notification callback of the AUGraph
	Nodes can also be removed (except for the output node or a sub-graph of the AUGraph)
	as well. 

	Getting kAUGraphErr_CannotDoInCurrentContext as a result code:
	If AUGraphUpdate returns this result, then it means it was
	unable to process the update, due to an inability to safely
	alter the state of the graph (because another thread was accessing
	a call that relies on the graph's state having integrity).
	This result code is only a transitory state, which will pass as soon
	as your other thread's call to AUGraph (that has the lock) completes.

	If an error is encountered in the process of an update (say an invalid connection
	is attempted, a disconnection between nodes that are not connected, etc) on a running graph, 	
	then the call will return that error code. It only process events whilst it receives
	no error results. Thus, if an error is encountered, other events will not be
	processed until AUGraphUpdate is called again. This is done, in cases where
	the state of the graph could become inconsistent if further events were processed, so
	this decision is left up to you. The same applies to the "cant do" error - you have
	to explicitly call AUGraphUpdate again to have the processing of the events occur.

	@param		inGraph
	@param		outIsUpdated	if specified returns true if all of the edits were applied to the graph
*/
extern OSStatus
AUGraphUpdate(		AUGraph					inGraph,
					Boolean	 * __nullable	outIsUpdated)			__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

#pragma mark -
#pragma mark State Management
/*! 
	@functiongroup AUGraph state management
*/
/*!
	@function	AUGraphOpen
	@abstract	Open a graph
	@discussion AudioUnits are open but not initialized (no resource allocation occurs here)
	@param		inGraph
*/
extern OSStatus
AUGraphOpen(			AUGraph		inGraph)						__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*!
	@function	AUGraphClose
	@abstract	Close a graph
	@discussion all AudioUnits are closed - leaving only its nodal representation
	@param		inGraph
*/
extern OSStatus
AUGraphClose(			AUGraph		inGraph)						__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*!
	@function	AUGraphInitialize
	@abstract	Initialise a graph
	@discussion AudioUnitInitialize() is called on each opened node/AudioUnit
				(get ready to render) and SubGraph that are involved in a
				interaction. If the node is not involved, it is initialised
				after it becomes involved in an interaction.
				
				A graph must be opened before it can be initialised.
	@param		inGraph
*/
extern OSStatus
AUGraphInitialize(		AUGraph		inGraph)						__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*!
	@function	AUGraphUninitialize
	@abstract	Uninitialise a graph
	@discussion The member of the graph are uninitialised 
	@param		inGraph
*/
extern OSStatus
AUGraphUninitialize(	AUGraph		inGraph)						__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*!
	@function	AUGraphStart
	@abstract	Start a graph
	@discussion Start() is called on the "head" node(s) of the AUGraph	(now rendering starts) 
				
				The graph must be initialised before it can be started
	@param		inGraph
*/
extern OSStatus
AUGraphStart(			AUGraph		inGraph)						__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*!
	@function	AUGraphStop
	@abstract	Stop a graph
	@discussion Stop() is called on the "head" node(s) of the AUGraph	(rendering is stopped)
*/
extern OSStatus
AUGraphStop(			AUGraph		inGraph)						__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);


/*!
	@function	AUGraphIsOpen
	@abstract	Is the graph open
*/
extern OSStatus
AUGraphIsOpen(			AUGraph		inGraph,
						Boolean		*outIsOpen)						__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);
							
/*!
	@function	AUGraphIsInitialized
	@abstract	Is the graph initialised
*/
extern OSStatus
AUGraphIsInitialized(	AUGraph		inGraph,
						Boolean		*outIsInitialized)				__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);
							
/*!
	@function	AUGraphIsRunning
	@abstract	Is the graph running (has it been started)
*/
extern OSStatus
AUGraphIsRunning(		AUGraph		inGraph,
						Boolean		*outIsRunning)					__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);
						
#pragma mark -
#pragma mark Utilities
/*! 
	@functiongroup AUGraph utilities
*/
/*!
	@function	AUGraphGetCPULoad
	@abstract	The CPU load of the graph
	@discussion	Returns a short-term running average of the current CPU load
				of the graph.		
*/
extern OSStatus
AUGraphGetCPULoad(		AUGraph		inGraph,
						Float32		*outAverageCPULoad)				__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_2_0);

/*!
	@function	AUGraphGetMaxCPULoad
	@abstract	The Maximum CPU load of the graph
	@discussion	Returns the max CPU load of the graph since this call was last made 
				or the graph was last started.
*/
extern OSStatus
AUGraphGetMaxCPULoad(	AUGraph		inGraph,
						Float32		*outMaxLoad)					__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_2_0);

/*!
	@function	AUGraphAddRenderNotify
	@abstract	Add a notification callback
	@discussion	Add a callback that the graph will call every time the
				graph renders. The callback will be called once before the graph's render
				operation, and once after the render operation is complete.
*/
extern OSStatus
AUGraphAddRenderNotify(			AUGraph					inGraph,
								AURenderCallback 		inCallback,
								void * __nullable		inRefCon)		__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

/*!
	@function	AUGraphRemoveRenderNotify
	@abstract	Remove a notification callback
	@discussion	Remove a previously added callback. You must provide both the callback
				and the refCon that was used previously to add the callback.
*/
extern OSStatus
AUGraphRemoveRenderNotify(		AUGraph					inGraph,
								AURenderCallback 		inCallback,
								void * __nullable		inRefCon)		__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);
	
#pragma mark -
#pragma mark Deprecated

#if !TARGET_OS_IPHONE
struct ComponentDescription;
/*!
	@function			AUGraphNewNode
	@discussion		ClassInfo data should not be used with new nodes
	@deprecated	in 10.5, see AUGraphAddNode
*/
extern OSStatus
AUGraphNewNode(	AUGraph								inGraph,
				const struct ComponentDescription	*inDescription,
				UInt32								inClassDataSize,	// reserved: must be zero
				const void							*inClassData,
				AUNode								*outNode)				__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);


/*!
	@function	AUGraphGetNodeInfo
	@discussion		ClassInfo data should not be used with new nodes
	@deprecated	in 10.5, see AUGraphNodeInfo
*/
extern OSStatus
AUGraphGetNodeInfo(	AUGraph						inGraph,
					AUNode						inNode,
					struct ComponentDescription *outDescription,
					UInt32						*outClassDataSize,
					void * __nullable * __nullable outClassData,
					AudioUnit __nullable * __nullable outAudioUnit)				__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);

/*!
	@function			AUGraphGetNumberOfConnections
	@deprecated	in 10.5, see AUGraphGetNumberOfInteractions
*/
extern OSStatus
AUGraphGetNumberOfConnections(	AUGraph		inGraph,
								UInt32		*outNumConnections)		__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);

/*!
	@function			AUGraphGetConnectionInfo
	@deprecated	in 10.5, see AUGraphGetInteractionInfo
*/
extern OSStatus
AUGraphGetConnectionInfo(	AUGraph		inGraph,
							UInt32		inConnectionIndex,
							AUNode		*outSourceNode,
							UInt32		*outSourceOutputNumber,
							AUNode		*outDestNode,
							UInt32		*outDestInputNumber)		__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);

/*!
	@function			AUGraphCountNodeConnections
	@deprecated	in 10.5, see AUGraphCountNodeInteractions
*/
extern OSStatus
AUGraphCountNodeConnections(	AUGraph 	inGraph,
								AUNode 		inNode,
								UInt32 		*outNumConnections)		__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_3,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);

/*!
	@function			AUGraphGetNodeConnections
	@deprecated	in 10.5, see AUGraphGetNodeInteractions
*/
extern OSStatus
AUGraphGetNodeConnections(		AUGraph						inGraph,
								AUNode						inNode,
								AudioUnitNodeConnection		*outConnections,
								UInt32						*ioNumConnections)	
																	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_3,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);

#endif //!TARGET_OS_IPHONE
	
#if defined(__cplusplus)
}
#endif

CF_ASSUME_NONNULL_END

#endif // AudioToolbox_AUGraph_h


// ==========  AudioToolbox.framework/Headers/ExtendedAudioFile.h
/*!
	@file		ExtendedAudioFile.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2004-2015 by Apple, Inc., all rights reserved.
	@abstract	API's to support reading and writing files in encoded audio formats.

	@discussion

				The ExtendedAudioFile provides high-level audio file access, building
				on top of the AudioFile and AudioConverter API sets. It provides a single
				unified interface to reading and writing both encoded and unencoded files.
*/

#ifndef AudioToolbox_ExtendedAudioFile_h
#define AudioToolbox_ExtendedAudioFile_h

#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreFoundation/CoreFoundation.h>
	#include <AudioToolbox/AudioFile.h>
#else
	#include <CoreFoundation.h>
	#include <AudioFile.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

CF_ASSUME_NONNULL_BEGIN

//==================================================================================================
//	Types

/*!
	@typedef	ExtAudioFileRef
	@abstract   An extended audio file object.
*/
typedef struct OpaqueExtAudioFile *	ExtAudioFileRef;


//==================================================================================================
//	Properties

typedef UInt32						ExtAudioFilePropertyID;
/*!
    @enum           ExtAudioFilePropertyID
    @constant       kExtAudioFileProperty_FileDataFormat
                        An AudioStreamBasicDescription. Represents the file's actual
						data format. Read-only.
	@constant		kExtAudioFileProperty_FileChannelLayout
						An AudioChannelLayout.

						If writing: the channel layout is written to the file, if the format
						supports the layout. If the format does not support the layout, the channel
						layout is still interpreted as the destination layout when performing
						conversion from the client channel layout, if any.

						If reading: the specified layout overrides the one read from the file, if
						any.

						When setting this, it must be set before the client format or channel
						layout.
	@constant		kExtAudioFileProperty_ClientDataFormat
						An AudioStreamBasicDescription.

						The format must be linear PCM (kAudioFormatLinearPCM).

						You must set this in order to encode or decode a non-PCM file data format.
						You may set this on PCM files to specify the data format used in your calls
						to read/write.
	@constant		kExtAudioFileProperty_ClientChannelLayout
						An AudioChannelLayout. Specifies the channel layout of the
						AudioBufferList's passed to ExtAudioFileRead() and
						ExtAudioFileWrite(). The layout may be different from the file's
						channel layout, in which the ExtAudioFileRef's underlying AudioConverter
						performs the remapping. This must be set after ClientDataFormat, and the
						number of channels in the layout must match.
	@constant		kExtAudioFileProperty_CodecManufacturer
						A UInt32 specifying the manufacturer of the codec to be used. This must be 
						specified before setting kExtAudioFileProperty_ClientDataFormat, which
						triggers the creation of the codec. This can be used on iOS
						to choose between a hardware or software encoder, by specifying 
						kAppleHardwareAudioCodecManufacturer or kAppleSoftwareAudioCodecManufacturer.
						
						Available starting on Mac OS X version 10.7 and iOS version 4.0.
	@constant		kExtAudioFileProperty_AudioConverter
						AudioConverterRef. The underlying AudioConverterRef, if any. Read-only.
						
						Note: If you alter any properties of the AudioConverterRef, for example,
						an encoder's bit rate, you must set the kExtAudioFileProperty_ConverterConfig
						property on the ExtAudioFileRef afterwards. A NULL configuration is 
						sufficient. This will ensure that the output file's data format is consistent
						with the format being produced by the converter.
						
						<pre>
							CFArrayRef config = NULL;
							err = ExtAudioFileSetProperty(myExtAF, kExtAudioFileProperty_ConverterConfig, 
							  sizeof(config), &config);
						</pre>
	@constant		kExtAudioFileProperty_AudioFile
						The underlying AudioFileID. Read-only.
	@constant		kExtAudioFileProperty_FileMaxPacketSize
						UInt32 representing the file data format's maximum packet size in bytes.
						Read-only.
	@constant		kExtAudioFileProperty_ClientMaxPacketSize
						UInt32 representing the client data format's maximum packet size in bytes.
						Read-only.
	@constant		kExtAudioFileProperty_FileLengthFrames
						SInt64 representing the file's length in sample frames. Read-only on 
						non-PCM formats; writable for files in PCM formats.
	@constant		kExtAudioFileProperty_ConverterConfig
						CFArrayRef representing the underlying AudioConverter's configuration, as
						specified by kAudioConverterPropertySettings.
						
						This may be NULL to force resynchronization of the converter's output format
						with the file's data format.
	@constant		kExtAudioFileProperty_IOBufferSizeBytes
						UInt32 representing the size of the buffer through which the converter
						reads/writes the audio file (when there is an AudioConverter).
	@constant		kExtAudioFileProperty_IOBuffer
						void *. This is the memory buffer which the ExtAudioFileRef will use for
						disk I/O when there is a conversion between the client and file data
						formats. A client may be able to share buffers between multiple
						ExtAudioFileRef instances, in which case, it can set this property to point
						to its own buffer. After setting this property, the client must
						subsequently set the kExtAudioFileProperty_IOBufferSizeBytes property. Note
						that a pointer to a pointer should be passed to ExtAudioFileSetProperty.
	@constant		kExtAudioFileProperty_PacketTable
						This AudioFilePacketTableInfo can be used to both override the priming and
						remainder information in an audio file and to retrieve the current priming
						and remainder frames information for a given ExtAudioFile object. If the
						underlying file type does not provide packet table info, the Get call will
						return an error.
						
						If you set this, then you can override the setting for these values in the
						file to ones that you want to use. When setting this, you can use a value of
						-1 for either the priming or remainder frames to use the value that is
						currently stored in the file. If you set this to a non-negative number (or
						zero) then that value will override whatever value is stored in the file
						that you are reading. Retrieving the value of the property will always
						retrieve the value the ExtAudioFile object is using (whether this is derived
						from the file, or from your override). If you want to determine what the
						value is in the file, you should use the AudioFile property:
						kAudioFilePropertyPacketTableInfo

						When the property is set, only the remaining and priming values are used.
						You should set the mNumberValidFrames to zero.

						For example, a file encoded using AAC may have 2112 samples of priming at
						the start of the file and a remainder of 823 samples at the end. When
						ExtAudioFile returns decoded samples to you, it will trim `mPrimingFrames`
						at the start of the file, and `mRemainderFrames` at the end. It will get
						these numbers initially from the file. A common use case for overriding this
						would be to set the priming and remainder samples to 0, so in this example
						you would retrieve an additional 2112 samples of silence from the start of
						the file and 823 samples of silence at the end of the file (silence, because
						the encoders use silence to pad out these priming and remainder samples)
*/
CF_ENUM(ExtAudioFilePropertyID) {
	kExtAudioFileProperty_FileDataFormat		= 'ffmt',   // AudioStreamBasicDescription
	kExtAudioFileProperty_FileChannelLayout		= 'fclo',   // AudioChannelLayout
	kExtAudioFileProperty_ClientDataFormat		= 'cfmt',   // AudioStreamBasicDescription
	kExtAudioFileProperty_ClientChannelLayout	= 'cclo',   // AudioChannelLayout
	kExtAudioFileProperty_CodecManufacturer		= 'cman',	// UInt32
	
	// read-only:
	kExtAudioFileProperty_AudioConverter		= 'acnv',	// AudioConverterRef
	kExtAudioFileProperty_AudioFile				= 'afil',	// AudioFileID
	kExtAudioFileProperty_FileMaxPacketSize		= 'fmps',	// UInt32
	kExtAudioFileProperty_ClientMaxPacketSize	= 'cmps',	// UInt32
	kExtAudioFileProperty_FileLengthFrames		= '#frm',	// SInt64
	
	// writable:
	kExtAudioFileProperty_ConverterConfig		= 'accf',   // CFPropertyListRef
	kExtAudioFileProperty_IOBufferSizeBytes		= 'iobs',	// UInt32
	kExtAudioFileProperty_IOBuffer				= 'iobf',	// void *
	kExtAudioFileProperty_PacketTable			= 'xpti'	// AudioFilePacketTableInfo
};

CF_ENUM(OSStatus) {
	kExtAudioFileError_InvalidProperty			= -66561,
	kExtAudioFileError_InvalidPropertySize		= -66562,
	kExtAudioFileError_NonPCMClientFormat		= -66563,
	kExtAudioFileError_InvalidChannelMap		= -66564,	// number of channels doesn't match format
	kExtAudioFileError_InvalidOperationOrder	= -66565,
	kExtAudioFileError_InvalidDataFormat		= -66566,
	kExtAudioFileError_MaxPacketSizeUnknown		= -66567,
	kExtAudioFileError_InvalidSeek				= -66568,	// writing, or offset out of bounds
	kExtAudioFileError_AsyncWriteTooLarge		= -66569,
	kExtAudioFileError_AsyncWriteBufferOverflow	= -66570	// an async write could not be completed in time
};

#if TARGET_OS_IPHONE
/*!
    @enum           ExtAudioFile errors
    @constant       kExtAudioFileError_CodecUnavailableInputConsumed
						iOS only. Returned when ExtAudioFileWrite was interrupted. You must stop calling
						ExtAudioFileWrite. If the underlying audio converter can resume after an
						interruption (see kAudioConverterPropertyCanResumeFromInterruption), you must
						wait for an EndInterruption notification from AudioSession, and call AudioSessionSetActive(true)
						before resuming. In this situation, the buffer you provided to ExtAudioFileWrite was successfully
						consumed and you may proceed to the next buffer.
    @constant       kExtAudioFileError_CodecUnavailableInputNotConsumed
						iOS only. Returned when ExtAudioFileWrite was interrupted. You must stop calling
						ExtAudioFileWrite. If the underlying audio converter can resume after an
						interruption (see kAudioConverterPropertyCanResumeFromInterruption), you must
						wait for an EndInterruption notification from AudioSession, and call AudioSessionSetActive(true)
						before resuming. In this situation, the buffer you provided to ExtAudioFileWrite was not
						successfully consumed and you must try to write it again.
*/
CF_ENUM(OSStatus) {
	kExtAudioFileError_CodecUnavailableInputConsumed    = -66559,
	kExtAudioFileError_CodecUnavailableInputNotConsumed = -66560,
};
#endif


//==================================================================================================
//	Creation/Destruction
/*!
    @functiongroup  Creation/Destruction
*/

/*!
	@function   ExtAudioFileOpenURL
	
	@abstract   Opens an audio file specified by a CFURLRef.
	@param		inURL
					The audio file to read.
	@param		outExtAudioFile
					On exit, a newly-allocated ExtAudioFileRef.
	@result		An OSStatus error code.

	@discussion
				Allocates a new ExtAudioFileRef, for reading an existing audio file.
*/
extern OSStatus
ExtAudioFileOpenURL(		CFURLRef 					inURL,
							ExtAudioFileRef __nullable * __nonnull outExtAudioFile)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_1);

/*!
	@function   ExtAudioFileWrapAudioFileID
	
	@abstract   Wrap an AudioFileID in an ExtAudioFileRef.
	@param		inFileID
					The AudioFileID to wrap.
	@param		inForWriting
					True if the AudioFileID is a new file opened for writing.
	@param		outExtAudioFile
					On exit, a newly-allocated ExtAudioFileRef.
	@result		An OSStatus error code.

	@discussion
				Allocates a new ExtAudioFileRef which wraps an existing AudioFileID. The
				client is responsible for keeping the AudioFileID open until the
				ExtAudioFileRef is disposed. Disposing the ExtAudioFileRef will not close
				the AudioFileID when this Wrap API call is used, so the client is also
				responsible for closing the AudioFileID when finished with it.
*/
extern OSStatus
ExtAudioFileWrapAudioFileID(AudioFileID					inFileID,
							Boolean						inForWriting,
							ExtAudioFileRef __nullable * __nonnull outExtAudioFile)
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);

/*!
	@function   ExtAudioFileCreateWithURL
	
	@abstract   Create a new audio file.
	@param		inURL
					The URL of the new audio file.
	@param		inFileType
					The type of file to create. This is a constant from AudioToolbox/AudioFile.h, e.g.
					kAudioFileAIFFType. Note that this is not an HFSTypeCode.
	@param		inStreamDesc
					The format of the audio data to be written to the file.
	@param		inChannelLayout
					The channel layout of the audio data. If non-null, this must be consistent
					with the number of channels specified by inStreamDesc.
	@param		inFlags
					The same flags as are used with AudioFileCreateWithURL
					Can use these to control whether an existing file is overwritten (or not).
	@param		outExtAudioFile
					On exit, a newly-allocated ExtAudioFileRef.
	@result		An OSStatus error code.

	@discussion
				Creates a new audio file.
				
				If the file to be created is in an encoded format, it is permissible for the
				sample rate in inStreamDesc to be 0, since in all cases, the file's encoding
				AudioConverter may produce audio at a different sample rate than the source. The
				file will be created with the audio format actually produced by the encoder.
*/
extern OSStatus
ExtAudioFileCreateWithURL(	CFURLRef							inURL,
							AudioFileTypeID						inFileType,
							const AudioStreamBasicDescription * inStreamDesc,
							const AudioChannelLayout * __nullable inChannelLayout,
                    		UInt32								inFlags,
							ExtAudioFileRef __nullable * __nonnull outExtAudioFile)
																			__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_1);
																			
#if !TARGET_OS_IPHONE && !CA_NO_CORE_SERVICES
/*!
	@function   ExtAudioFileOpen
	
	@abstract   Opens an audio file specified by an FSRef.
	@param		inFSRef
					The audio file to read.
	@param		outExtAudioFile
					On exit, a newly-allocated ExtAudioFileRef.
	@result		An OSStatus error code.

	@discussion
				Allocates a new ExtAudioFileRef, for reading an existing audio file.
				
				This function is deprecated as of Mac OS 10.6. ExtAudioFileOpenURL is preferred.
*/
extern OSStatus
ExtAudioFileOpen(			const struct FSRef *		inFSRef,
							ExtAudioFileRef __nullable * __nonnull outExtAudioFile)	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_4,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);

/*!
	@function   ExtAudioFileCreateNew
	
	@abstract   Creates a new audio file.
	@param		inParentDir
					The directory in which to create the new file.
	@param		inFileName
					The name of the new file.
	@param		inFileType
					The type of file to create. This is a constant from AudioToolbox/AudioFile.h, e.g.
					kAudioFileAIFFType. Note that this is not an HFSTypeCode.
	@param		inStreamDesc
					The format of the audio data to be written to the file.
	@param		inChannelLayout
					The channel layout of the audio data. If non-null, this must be consistent
					with the number of channels specified by inStreamDesc.
	@param		outExtAudioFile
					On exit, a newly-allocated ExtAudioFileRef.
	@result		An OSStatus error code.

	@discussion
				If the file to be created is in an encoded format, it is permissible for the
				sample rate in inStreamDesc to be 0, since in all cases, the file's encoding
				AudioConverter may produce audio at a different sample rate than the source. The
				file will be created with the audio format actually produced by the encoder.

				This function is deprecated as of Mac OS 10.6. ExtAudioFileCreateWithURL is preferred.
*/
extern OSStatus
ExtAudioFileCreateNew(		const struct FSRef *				inParentDir,
							CFStringRef							inFileName,
							AudioFileTypeID						inFileType,
							const AudioStreamBasicDescription * inStreamDesc,
							const AudioChannelLayout * __nullable inChannelLayout,
							ExtAudioFileRef __nullable * __nonnull outExtAudioFile)
																			__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_4,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);
#endif

/*!
	@function   ExtAudioFileDispose
	
	@abstract   Close the file and dispose the object.
	@param		inExtAudioFile
					The extended audio file object.
	@result		An OSStatus error code.
	
	@discussion
				Closes the file and deletes the object.
*/
extern OSStatus
ExtAudioFileDispose(		ExtAudioFileRef				inExtAudioFile)		
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);


//==================================================================================================
//	I/O
/*!
    @functiongroup  I/O
*/

/*!
	@function   ExtAudioFileRead
	
	@abstract   Perform a synchronous sequential read.
	
	@param		inExtAudioFile
					The extended audio file object.
	@param		ioNumberFrames
					On entry, ioNumberFrames is the number of frames to be read from the file.
					On exit, it is the number of frames actually read. A number of factors may
					cause a fewer number of frames to be read, including the supplied buffers
					not being large enough, and internal optimizations. If 0 frames are
					returned, however, this indicates that end-of-file was reached.
	@param		ioData
					Buffer(s) into which the audio data is read.
	@result		An OSStatus error code.

	@discussion
				If the file has a client data format, then the audio data from the file is
				translated from the file data format to the client format, via the
				ExtAudioFile's internal AudioConverter.
				
				(Note that the use of sequential reads/writes means that an ExtAudioFile must
				not be read on multiple threads; clients wishing to do this should use the
				lower-level AudioFile API set).
*/
extern OSStatus
ExtAudioFileRead(			ExtAudioFileRef			inExtAudioFile,
							UInt32 *				ioNumberFrames,
							AudioBufferList *		ioData)					
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);

/*!
	@function   ExtAudioFileWrite
	
	@abstract   Perform a synchronous sequential write.

	@param		inExtAudioFile
					The extended audio file object.
	@param		inNumberFrames
					The number of frames to write.
	@param		ioData
					The buffer(s) from which audio data is written to the file.
	@result		An OSStatus error code.
	
	@discussion
				If the file has a client data format, then the audio data in ioData is
				translated from the client format to the file data format, via the
				ExtAudioFile's internal AudioConverter.
*/
extern OSStatus
ExtAudioFileWrite(			ExtAudioFileRef			inExtAudioFile,
							UInt32					inNumberFrames,
							const AudioBufferList * ioData)					
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);

/*!
	@function   ExtAudioFileWriteAsync
	
	@abstract   Perform an asynchronous sequential write.
	
	@param		inExtAudioFile
					The extended audio file object.
	@param		inNumberFrames
					The number of frames to write.
	@param		ioData
					The buffer(s) from which audio data is written to the file.
	@result		An OSStatus error code.
		
	@discussion
				Writes the provided buffer list to an internal ring buffer and notifies an
				internal thread to perform the write at a later time. The first time this is
				called, allocations may be performed. You can call this with 0 frames and null
				buffer in a non-time-critical context to initialize the asynchronous mechanism.
				Once initialized, subsequent calls are very efficient and do not take locks;
				thus this may be used to write to a file from a realtime thread.

				The client must not mix synchronous and asynchronous writes to the same file.

				Pending writes are not guaranteed to be flushed to disk until
				ExtAudioFileDispose is called.

				N.B. Errors may occur after this call has returned. Such errors may be returned
				from subsequent calls to this function.
*/
extern OSStatus
ExtAudioFileWriteAsync(		ExtAudioFileRef			inExtAudioFile,
							UInt32					inNumberFrames,
							const AudioBufferList * __nullable ioData)
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);

/*!
	@function   ExtAudioFileSeek

	@abstract   Seek to a specific frame position.

	@param		inExtAudioFile
					The extended audio file object.
	@param		inFrameOffset
					The desired seek position, in sample frames, relative to the beginning of
					the file. This is specified in the sample rate and frame count of the file's format
					(not the client format)
	@result		An OSStatus error code.
	
	@discussion
				Sets the file's read position to the specified sample frame number. The next call
				to ExtAudioFileRead will return samples from precisely this location, even if it
				is located in the middle of a packet.
				
				This function's behavior with files open for writing is currently undefined.
*/
extern OSStatus
ExtAudioFileSeek(			ExtAudioFileRef			inExtAudioFile,
							SInt64					inFrameOffset)			
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);

/*!
	@function   ExtAudioFileTell
	
	@abstract   Return the file's read/write position.

	@param		inExtAudioFile
					The extended audio file object.
	@param		outFrameOffset
					On exit, the file's current read/write position in sample frames. This is specified in the 
					sample rate and frame count of the file's format (not the client format)
	@result		An OSStatus error code.
	
	@discussion
*/
extern OSStatus
ExtAudioFileTell(			ExtAudioFileRef			inExtAudioFile,
							SInt64 *				outFrameOffset)			
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);

//==================================================================================================
//	Property Access
/*!
    @functiongroup  Property Access
*/

/*!
	@function   ExtAudioFileGetPropertyInfo
	@abstract   Get information about a property

	@param		inExtAudioFile
					The extended audio file object.
	@param		inPropertyID
					The property being queried.
	@param		outSize
					If non-null, on exit, this is set to the size of the property's value.
	@param		outWritable
					If non-null, on exit, this indicates whether the property value is settable.
	@result		An OSStatus error code.

	@discussion
*/
extern OSStatus
ExtAudioFileGetPropertyInfo(ExtAudioFileRef			inExtAudioFile,
							ExtAudioFilePropertyID	inPropertyID,
							UInt32 * __nullable		outSize,
							Boolean * __nullable	outWritable)
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);

/*!
	@function   ExtAudioFileGetProperty
	@abstract   Get a property value.

	@param		inExtAudioFile
					The extended audio file object.
	@param		inPropertyID
					The property being fetched.
	@param		ioPropertyDataSize
					On entry, the size (in bytes) of the memory pointed to by outPropertyData.
					On exit, the actual size of the property data returned.	
	@param		outPropertyData
					The value of the property is copied to the memory this points to.
	@result		An OSStatus error code.

	@discussion
*/
extern OSStatus
ExtAudioFileGetProperty(	ExtAudioFileRef			inExtAudioFile,
							ExtAudioFilePropertyID	inPropertyID,
							UInt32 *				ioPropertyDataSize,
							void *					outPropertyData)
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);

/*!
	@function   ExtAudioFileSetProperty
	@abstract   Set a property value.

	@param		inExtAudioFile
					The extended audio file object.
	@param		inPropertyID
					The property being set.
	@param		inPropertyDataSize
					The size of the property data, in bytes.
	@param		inPropertyData
					Points to the property's new value.
	@result		An OSStatus error code.

	@discussion
*/
extern OSStatus
ExtAudioFileSetProperty(	ExtAudioFileRef			inExtAudioFile,
							ExtAudioFilePropertyID	inPropertyID,
							UInt32					inPropertyDataSize,
							const void *			inPropertyData)			
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);

CF_ASSUME_NONNULL_END

#ifdef __cplusplus
}
#endif

#endif // AudioToolbox_ExtendedAudioFile_h
// ==========  AudioToolbox.framework/Headers/AudioFileStream.h
/*!
	@file		AudioFileStream.h
	@framework	AudioToolbox.framework
	@copyright	(c) 1985-2015 by Apple, Inc., all rights reserved.

	@brief		API's to parse streamed audio files into packets of audio data.

	@discussion

	AudioFileStream addresses situations where, in a stream of audio data, only a limited window
	of data may be available at any time.

	This case differs significantly enough from the random access file case to warrant a separate
	API rather than overload the AudioFile API with additional semantics. With a random access file,
	one can always assume that a read request for contiguous data that doesn't include EOF will
	always supply all of the data. This makes parsing straightforward and inexpensive. In the
	streaming case such an assumption cannot be made. A request by the parser for data from the
	stream may only be partially satisfied. Any partially satisfied requests must be remembered and
	retried before any other requests are satisfied, otherwise the streamed data might be lost
	forever in the past. So the parser must be able to suspend work at any point and resume parsing
	where it left off.
	
	The client provides data to the parser using AudioFileStreamParseBytes and the parser calls back
	to the client with properties or packets using the AudioFileStream_PropertyListenerProc and
	AudioFileStream_PacketsProc function pointers.
*/

#ifndef AudioToolbox_AudioFileStream_h
#define AudioToolbox_AudioFileStream_h

//=============================================================================
//	Includes
//=============================================================================

#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreAudio/CoreAudioTypes.h>
	#include <AudioToolbox/AudioFile.h>
#else
	#include <CoreAudioTypes.h>
	#include <AudioFile.h>
#endif

CF_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
extern "C"
{
#endif

//=============================================================================
//	AudioFileStream flags
//=============================================================================
#pragma mark flags

/*!
    @enum AudioFileStreamPropertyFlags
    @constant   kAudioFileStreamPropertyFlag_PropertyIsCached 
		This flag is set in a call to AudioFileStream_PropertyListenerProc when the value of the property
		can be obtained at any later time. If this flag is not set, then you should either get the value of 
		the property from within this callback or set the flag kAudioFileStreamPropertyFlag_CacheProperty in order to signal
		to the parser to begin caching the property data. Otherwise the value may not be available in the future.
		
    @constant   kAudioFileStreamPropertyFlag_CacheProperty 
		This flag can be set by a property listener in order to signal to the parser that the client is
		interested in the value of the property and that it should be cached until the full value of the property is available.
*/
typedef CF_OPTIONS(UInt32, AudioFileStreamPropertyFlags) {
	kAudioFileStreamPropertyFlag_PropertyIsCached = 1,
	kAudioFileStreamPropertyFlag_CacheProperty = 2
};

/*!	@enum	AudioFileStreamParseFlags
    @constant   kAudioFileStreamParseFlag_Discontinuity 
		This flag is passed in to AudioFileStreamParseBytes to signal a discontinuity. Any partial packet straddling a buffer
		boundary will be discarded. This is necessary to avoid being called with a corrupt packet. After a discontinuity occurs
		seeking may be approximate in some data formats.
*/
typedef CF_OPTIONS(UInt32, AudioFileStreamParseFlags) {
	kAudioFileStreamParseFlag_Discontinuity = 1
};

/*!	@enum	AudioFileStreamParseFlags
    @constant   kAudioFileStreamSeekFlag_OffsetIsEstimated 
		This flag may be returned from AudioFileStreamSeek if the byte offset is only an estimate, not exact.
*/
typedef CF_OPTIONS(UInt32, AudioFileStreamSeekFlags) {
	kAudioFileStreamSeekFlag_OffsetIsEstimated = 1
};

//=============================================================================
//	AudioFileStream Types
//=============================================================================
#pragma mark types

typedef UInt32 AudioFileStreamPropertyID;
typedef	struct OpaqueAudioFileStreamID	*AudioFileStreamID;

typedef void (*AudioFileStream_PropertyListenerProc)(
											void *							inClientData,
											AudioFileStreamID				inAudioFileStream,
											AudioFileStreamPropertyID		inPropertyID,
											AudioFileStreamPropertyFlags *	ioFlags);

typedef void (*AudioFileStream_PacketsProc)(
											void *							inClientData,
											UInt32							inNumberBytes,
											UInt32							inNumberPackets,
											const void *					inInputData,
											AudioStreamPacketDescription	*inPacketDescriptions);

//=============================================================================
//	AudioFileStream error codes
//=============================================================================
#pragma mark Error codes
/*!
    @enum AudioFileStream error codes

    @abstract   These are the error codes returned from the AudioFile API.

    @constant   kAudioFileStreamError_UnsupportedFileType 
		The file type is not supported.
    @constant   kAudioFileStreamError_UnsupportedDataFormat 
		The data format is not supported by this file type.
    @constant   kAudioFileStreamError_UnsupportedProperty 
		The property is not supported.
    @constant   kAudioFileStreamError_BadPropertySize 
		The size of the property data was not correct.
    @constant   kAudioFileStreamError_NotOptimized 
		It is not possible to produce output packets because the file's packet table or other defining 
		info is either not present or is after the audio data.
    @constant   kAudioFileStreamError_InvalidPacketOffset 
		A packet offset was less than zero, or past the end of the file,
		or a corrupt packet size was read when building the packet table. 
    @constant   kAudioFileStreamError_InvalidFile 
		The file is malformed, or otherwise not a valid instance of an audio file of its type, or 
		is not recognized as an audio file. 
    @constant   kAudioFileStreamError_ValueUnknown 
		The property value is not present in this file before the audio data.
	@constant	kAudioFileStreamError_DataUnavailable
		The amount of data provided to the parser was insufficient to produce any result.
	@constant	kAudioFileStreamError_IllegalOperation
		An illegal operation was attempted.
    @constant   kAudioFileStreamError_UnspecifiedError 
		An unspecified error has occurred.
		
*/

CF_ENUM(OSStatus)
{
	kAudioFileStreamError_UnsupportedFileType		= 'typ?',
	kAudioFileStreamError_UnsupportedDataFormat		= 'fmt?',
	kAudioFileStreamError_UnsupportedProperty		= 'pty?',
	kAudioFileStreamError_BadPropertySize			= '!siz',
	kAudioFileStreamError_NotOptimized				= 'optm',
	kAudioFileStreamError_InvalidPacketOffset		= 'pck?',
	kAudioFileStreamError_InvalidFile				= 'dta?',
	kAudioFileStreamError_ValueUnknown				= 'unk?',
	kAudioFileStreamError_DataUnavailable			= 'more',
	kAudioFileStreamError_IllegalOperation			= 'nope',
	kAudioFileStreamError_UnspecifiedError			= 'wht?',
	kAudioFileStreamError_DiscontinuityCantRecover	= 'dsc!'
};

//=============================================================================
//	AudioFileStream Properties
//=============================================================================
#pragma mark Properties

/*!
    @enum		AudioFileStream Properties
	
    @abstract   constants for AudioFileStream get property calls
    @discussion		There are currently no settable properties.

					
    @constant   kAudioFileStreamProperty_ReadyToProducePackets
					An UInt32 which is zero until the parser has parsed up to the beginning of the audio data. 
					Once it has reached the audio data, the value of this property becomes one. 
					When this value has become one, all properties that can be known about the stream are known.
					
    @constant   kAudioFileStreamProperty_FileFormat 
					An UInt32 four char code that identifies the format of the file
    @constant   kAudioFileStreamProperty_DataFormat 
					An AudioStreamBasicDescription describing the format of the audio data
    @constant   kAudioFileStreamProperty_FormatList 
					In order to support formats such as AAC SBR where an encoded data stream can be decoded to 
					multiple destination formats, this property returns an array of AudioFormatListItems 
					(see AudioFormat.h) of those formats.
					The default behavior is to return the an AudioFormatListItem that has the same 
					AudioStreamBasicDescription that kAudioFileStreamProperty_DataFormat returns.
    @constant   kAudioFileStreamProperty_MagicCookieData 
					A void * pointing to memory set up by the caller.
					Some file types require that a magic cookie be provided before packets can be written
					to the file, so this property should be set before calling 
					AudioFileWriteBytes()/AudioFileWritePackets() if a magic cookie exists.
    @constant   kAudioFileStreamProperty_AudioDataByteCount 
					a UInt64 that indicates the number of bytes of audio data contained in the file
    @constant   kAudioFileStreamProperty_AudioDataPacketCount 
					a UInt64 that indicates the number of packets of audio data contained in the file
    @constant   kAudioFileStreamProperty_MaximumPacketSize 
					a UInt32 that indicates the maximum size of a packet for the data contained in the file
    @constant   kAudioFileStreamProperty_DataOffset 
					a SInt64 that indicates the byte offset in the file of the audio data.
    @constant   kAudioFileStreamProperty_ChannelLayout 
					An AudioChannelLayout struct.
    @constant   kAudioFileStreamProperty_PacketToFrame 
					pass a AudioFramePacketTranslation with mPacket filled out and get mFrame back. 
					mFrameOffsetInPacket is ignored.
    @constant   kAudioFileStreamProperty_FrameToPacket 
					pass a AudioFramePacketTranslation with mFrame filled out and get mPacket and 
					mFrameOffsetInPacket back.
	@constant	kAudioFileStreamProperty_PacketToByte
					pass an AudioBytePacketTranslation struct with mPacket filled out and get mByte back.
					mByteOffsetInPacket is ignored. If the mByte value is an estimate then 
					kBytePacketTranslationFlag_IsEstimate will be set in the mFlags field.
	@constant	kAudioFileStreamProperty_ByteToPacket
					pass an AudioBytePacketTranslation struct with mByte filled out and get mPacket and
					mByteOffsetInPacket back. If the mPacket value is an estimate then 
					kBytePacketTranslationFlag_IsEstimate will be set in the mFlags field.
    @constant   kAudioFileStreamProperty_PacketTableInfo 
					Gets the AudioFilePacketTableInfo struct for the file types that support it.
	@constant	kAudioFileStreamProperty_PacketSizeUpperBound
					a UInt32 for the theoretical maximum packet size in the file.
	@constant	kAudioFileStreamProperty_AverageBytesPerPacket
					a Float64 of giving the average bytes per packet seen. 
					For CBR and files with packet tables, this number will be exact. Otherwise, it is a
					running average of packets parsed.
	@constant	kAudioFileStreamProperty_BitRate
					a UInt32 of the bit rate in bits per second.
    @constant	kAudioFileStreamProperty_InfoDictionary
                    a CFDictionary filled with information about the data contained in the stream.
                    See AudioFile.h for InfoDictionary key strings. Caller is responsible for releasing the CFObject.
*/
CF_ENUM(AudioFileStreamPropertyID)
{
	kAudioFileStreamProperty_ReadyToProducePackets			=	'redy',
	kAudioFileStreamProperty_FileFormat						=	'ffmt',
	kAudioFileStreamProperty_DataFormat						=	'dfmt',
	kAudioFileStreamProperty_FormatList						=	'flst',
	kAudioFileStreamProperty_MagicCookieData				=	'mgic',
	kAudioFileStreamProperty_AudioDataByteCount				=	'bcnt',
	kAudioFileStreamProperty_AudioDataPacketCount			=	'pcnt',
	kAudioFileStreamProperty_MaximumPacketSize				=	'psze',
	kAudioFileStreamProperty_DataOffset						=	'doff',
	kAudioFileStreamProperty_ChannelLayout					=	'cmap',
	kAudioFileStreamProperty_PacketToFrame					=	'pkfr',
	kAudioFileStreamProperty_FrameToPacket					=	'frpk',
	kAudioFileStreamProperty_PacketToByte					=	'pkby',
	kAudioFileStreamProperty_ByteToPacket					=	'bypk',
	kAudioFileStreamProperty_PacketTableInfo				=	'pnfo',
	kAudioFileStreamProperty_PacketSizeUpperBound  			=	'pkub',
	kAudioFileStreamProperty_AverageBytesPerPacket			=	'abpp',
	kAudioFileStreamProperty_BitRate						=	'brat',
    kAudioFileStreamProperty_InfoDictionary                 =   'info'
};

//=============================================================================
//	AudioFileStream Functions
//=============================================================================
#pragma mark Functions


/*!
	@function		AudioFileStreamOpen

	@discussion		Create a new audio file stream parser.
					The client provides the parser with data and the parser calls
					callbacks when interesting things are found in the data, such as properties and 
					audio packets.

    @param			inClientData					
						a constant that will be passed to your callbacks.
	@param			inPropertyListenerProc
						Whenever the value of a property is parsed in the data, this function will be called.
						You can then get the value of the property from in the callback. In some cases, due to 
						boundaries in the input data, the property may return kAudioFileStreamError_DataUnavailable.
						When unavailable data is requested from within the property listener, the parser will begin 
						caching the property value and will call the property listener again when the property is
						available. For property values for which kAudioFileStreamPropertyFlag_PropertyIsCached is unset, this 
						will be the only opportunity to get the value of the property, since the data will be 
						disposed upon return of the property listener callback. 
	@param			inPacketsProc
						Whenever packets are parsed in the data, a pointer to the packets is passed to the client 
						using this callback. At times only a single packet may be passed due to boundaries in the 
						input data.
    @param 			inFileTypeHint	
						For files whose type cannot be easily or uniquely determined from the data (ADTS,AC3), 
						this hint can be used to indicate the file type. 
						Otherwise if you do not know the file type, you can pass zero. 
	@param			outAudioFileStream 
						A new file stream ID for use in other AudioFileStream API calls.
*/ 
extern OSStatus	
AudioFileStreamOpen (
							void * __nullable						inClientData,
							AudioFileStream_PropertyListenerProc	inPropertyListenerProc,
							AudioFileStream_PacketsProc				inPacketsProc,
                			AudioFileTypeID							inFileTypeHint,
                			AudioFileStreamID __nullable * __nonnull outAudioFileStream)
																		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);


/*!
	@function		AudioFileStreamParseBytes

	@discussion		This call is the means for streams to supply data to the parser. 
					Data is expected to be passed in sequentially from the beginning of the file, without gaps.
					In the course of parsing, the client's property and/or packets callbacks may be called.

	@param			inAudioFileStream 
						The file stream ID
	@param			inDataByteSize 
						The number of bytes passed in for parsing.
	@param			inData 
						The data passed in to be parsed. 
	@param			inFlags 
						If there is a data discontinuity, then kAudioFileStreamParseFlag_Discontinuity should be set true. 
*/
extern OSStatus
AudioFileStreamParseBytes(	
								AudioFileStreamID				inAudioFileStream,
								UInt32							inDataByteSize,
								const void *					inData,
								AudioFileStreamParseFlags		inFlags)
																		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
	@function		AudioFileStreamSeek

	@discussion		This call is used to seek in the data stream. The client passes in a packet 
					offset to seek to and the parser passes back a byte offset from which to
					get the data to satisfy that request. The data passed to the next call to 
					AudioFileParseBytes will be assumed to be from that byte offset.
					For file formats which do not contain packet tables the byte offset may 
					be an estimate. If so, the flag kAudioFileStreamSeekFlag_OffsetIsEstimated will be true.

	@param			inAudioFileStream 
						The file stream ID
	@param			inPacketOffset 
						The offset from the beginning of the file of the packet to which to seek.
	@param			outDataByteOffset 
						The byte offset of the data from the file's data offset returned. 
						You need to add the value of kAudioFileStreamProperty_DataOffset to get an absolute byte offset in the file.
	@param			ioFlags
						If outDataByteOffset is an estimate, then kAudioFileStreamSeekFlag_OffsetIsEstimated will be set on output.
						There are currently no flags defined for passing into this call.
*/
extern OSStatus
AudioFileStreamSeek(	
								AudioFileStreamID				inAudioFileStream,
								SInt64							inPacketOffset,
								SInt64 *						outDataByteOffset,
								AudioFileStreamSeekFlags *		ioFlags)
																		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
	@function		AudioFileStreamGetPropertyInfo
 
	@discussion		Retrieve the info about the given property. The outSize argument
					will return the size in bytes of the current value of the property.
 
	@param			inAudioFileStream 
						The file stream ID
	@param			inPropertyID
						Property ID whose value should be read
	@param			outPropertyDataSize
						Size in bytes of the property
	@param			outWritable
						whether the property is writable
 
	@result			an OSStatus return code
*/
extern OSStatus
AudioFileStreamGetPropertyInfo(	
								AudioFileStreamID				inAudioFileStream,
								AudioFileStreamPropertyID		inPropertyID,
								UInt32 * __nullable				outPropertyDataSize,
								Boolean * __nullable			outWritable)
																		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);


/*!
	@function		AudioFileStreamGetProperty
 
	@discussion		Retrieve the indicated property data. 
 
	@param			inAudioFileStream 
						The file stream ID
	@param			inPropertyID
						Property ID whose value should be read
	@param			ioPropertyDataSize
						On input, the size of the buffer pointed to by outPropertyData. On output, 
						the number of bytes written.
	@param			outPropertyData
						Pointer to the property data buffer

	@result			an OSStatus return code
*/
extern OSStatus
AudioFileStreamGetProperty(	
							AudioFileStreamID					inAudioFileStream,
							AudioFileStreamPropertyID			inPropertyID,
							UInt32 *							ioPropertyDataSize,
							void *								outPropertyData)		
																		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
	@function		AudioFileStreamSetProperty
 
	@discussion		Set the value of the property. There are currently no settable properties.
 
	@param			inAudioFileStream 
						The file stream ID
	@param			inPropertyID
						Property ID whose value should be set
	@param			inPropertyDataSize
						Size in bytes of the property data
	@param			inPropertyData
						Pointer to the property data buffer

	@result			an OSStatus return code
*/
extern OSStatus
AudioFileStreamSetProperty(	
							AudioFileStreamID					inAudioFileStream,
							AudioFileStreamPropertyID			inPropertyID,
							UInt32								inPropertyDataSize,
							const void *						inPropertyData)		
																		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
	@function		AudioFileStreamClose
 
	@discussion		Close and deallocate the file stream object.

	@param			inAudioFileStream 
						The file stream ID
*/
extern OSStatus
AudioFileStreamClose(			AudioFileStreamID				inAudioFileStream)										
																		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);


#if defined(__cplusplus)
}
#endif

CF_ASSUME_NONNULL_END

#endif // AudioToolbox_AudioFileStream_h

// ==========  AudioToolbox.framework/Headers/AudioServices.h
/*!
	@file		AudioServices.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2006-2015 by Apple, Inc., all rights reserved.
    @abstract   API's for general high level audio services.

    @discussion

    AudioServices provides a means to play audio for things such as UI sound effects.
    
    The Audio Hardware Service (AHS) provides a way for applications to query and manipulate the
    aspects of an audio hardware device without incurring the overhead of loading the full audio
    HAL. AHS provides access to all the AudioObjects and their properties on the system. However,
    access is limited to only those properties that do not directly impact IO. For example, you can
    query the device's format but you can't query its IO buffer size. As such, the AHS API directly
    incorporates the various structures and constants in HAL's API, with the caveat that the
    AudioObjectIDs used in AHS cannot be used with the HAL.
*/

#ifndef AudioToolbox_AudioServices_h
#define AudioToolbox_AudioServices_h

//==================================================================================================
#pragma mark    Includes

#include <TargetConditionals.h>
#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
    #if !TARGET_OS_IPHONE
        #include <CoreAudio/AudioHardware.h>
    #elif TARGET_OS_IOS
        #include <AudioToolbox/AudioSession.h>
    #endif
    #include <CoreFoundation/CoreFoundation.h>
#else
	#include <AudioHardware.h>
    #include <CFRunLoop.h>
    #include <CFString.h>
    #include <CFURL.h>
#endif

//==================================================================================================
CF_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
extern "C"
{
#endif

//==================================================================================================
#pragma mark    AudioServices Error Constants

/*!
    @enum           AudioServices error codes
    @abstract       Error codes returned from the AudioServices portion of the API.
    @constant       kAudioServicesNoError
                        No error has occurred
    @constant       kAudioServicesUnsupportedPropertyError 
                        The property is not supported.
    @constant       kAudioServicesBadPropertySizeError 
                        The size of the property data was not correct.
    @constant       kAudioServicesBadSpecifierSizeError 
                        The size of the specifier data was not correct.
    @constant       kAudioServicesSystemSoundUnspecifiedError 
                        A SystemSound unspecified error has occurred.
    @constant       kAudioServicesSystemSoundClientTimedOutError 
                        SystemSound client message timed out
*/
CF_ENUM(OSStatus)
{
	kAudioServicesNoError									=  0,
	kAudioServicesUnsupportedPropertyError					= 'pty?',
	kAudioServicesBadPropertySizeError						= '!siz',
	kAudioServicesBadSpecifierSizeError 					= '!spc',

	kAudioServicesSystemSoundUnspecifiedError				= -1500,
	kAudioServicesSystemSoundClientTimedOutError			= -1501
};

//==================================================================================================
#pragma mark    AudioServices Types

/*!
    @typedef        SystemSoundID
    @abstract       SystemSoundIDs are created by the System Sound client application
                    for playback of a provided AudioFile.
*/
typedef UInt32      SystemSoundID;

/*!
    @typedef        AudioServicesPropertyID
    @abstract       Type used for specifying an AudioServices property.
*/
typedef UInt32      AudioServicesPropertyID;

/*!
    @typedef        AudioServicesSystemSoundCompletionProc
    @abstract       A function to be executed when a SystemSoundID finishes playing.
    @discussion     AudioServicesSystemSoundCompletionProc may be provided by client application to be
                    called when a SystemSoundID has completed playback.
    @param          ssID
                        The SystemSoundID that completed playback
    @param          userData
                        Client application user data
*/
typedef void
(*AudioServicesSystemSoundCompletionProc)(  SystemSoundID       ssID,
                                        	void* __nullable    clientData);

//==================================================================================================
#pragma mark    AudioServices Constants

#if !TARGET_OS_IPHONE
/*!
    @enum           AudioServices constants
    @abstract       Constants for use with System Sound portion of the AudioServices APIs.
    @constant       kSystemSoundID_UserPreferredAlert 
                        Use this constant with the play sound APIs to
                        playback the alert sound selected by the User in System Preferences.
    @constant       kSystemSoundID_FlashScreen
                        Use this constant with the play sound APIs to flash the screen
                        - Desktop systems only
*/
CF_ENUM(SystemSoundID)
{
    kSystemSoundID_UserPreferredAlert   = 0x00001000,
    kSystemSoundID_FlashScreen          = 0x00000FFE,
        // this has been renamed to be consistent
    kUserPreferredAlert     = kSystemSoundID_UserPreferredAlert
};

#else
/*!
    @enum           AudioServices constants
    @constant       kSystemSoundID_Vibrate
                        Use this constant with the play sound APIs to vibrate the device
                        - iOS only 
                            - on a device with no vibration capability (like iPod Touch) this will 
                            do nothing
*/
CF_ENUM(SystemSoundID)
{
    kSystemSoundID_Vibrate              = 0x00000FFF
};
#endif

//==================================================================================================
#pragma mark    AudioServices Properties

/*!
    @enum           AudioServices property codes
    @abstract       These are the property codes used with the AudioServices API.
    @constant       kAudioServicesPropertyIsUISound
                        a UInt32 where 1 means that the SystemSoundID passed in the
                        inSpecifier parameter will respect the 'Play user interface sounds effects'
                        check box in System Preferences and be silent when the user turns off UI
                        sounds. This property is set to 1 by default. Set to 0 if it is desired for
                        an SystemSoundID to always be heard when passed to AudioServicesPlaySystemSound(), 
                        regardless of user's setting in the Sound Preferences.
    @constant       kAudioServicesPropertyCompletePlaybackIfAppDies 
                        a UInt32 where 1 means that the SystemSoundID passed in the
                        inSpecifier parameter will finish playing even if the client application goes away.
*/
CF_ENUM(AudioServicesPropertyID)
{
    kAudioServicesPropertyIsUISound                   = 'isui',
    kAudioServicesPropertyCompletePlaybackIfAppDies   = 'ifdi'
};

//==================================================================================================
#pragma mark    AudioServices Functions

/*!
    @functiongroup  AudioServices
*/

/*!
    @function       AudioServicesCreateSystemSoundID
    @abstract       Allows the application to designate an audio file for playback by the System Sound server.
    @discussion     SystemSoundIDs are used passed to
                    AudioServicesPlayAlertSound() & AudioServicesPlaySystemSound(),
                    designating the audio data to be played by the System Sound server.
    @param          inFileURL
                        A CFURLRef for an AudioFile.
    @param          outSystemSoundID
                        Returns a SystemSoundID.
*/
extern OSStatus 
AudioServicesCreateSystemSoundID(   CFURLRef                    inFileURL,
                                    SystemSoundID*              outSystemSoundID)
                                                                __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);
	
/*!
    @function       AudioServicesDisposeSystemSoundID
    @abstract       Allows the System Sound server to dispose any resources needed for the provided
                    SystemSoundID.
    @discussion     Allows the application to tell the System Sound server that the resources for the
                    associated audio file are no longer required.
    @param          inSystemSoundID
                        A SystemSoundID that the application no longer needs to use.
*/
extern OSStatus 
AudioServicesDisposeSystemSoundID(SystemSoundID inSystemSoundID)                                    
                                                                __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function       AudioServicesPlayAlertSoundWithCompletion
    @abstract       Play an alert sound
    @discussion     Play the sound designated by the provided SystemSoundID with alert sound behavior.
    @param          inSystemSoundID
                        The SystemSoundID to be played. On the desktop the kSystemSoundID_UserPreferredAlert
                        constant can be passed in to play back the alert sound selected by the user
                        in System Preferences. On iOS there is no preferred user alert sound.
    @param          inCompletionBlock
                        The completion block gets executed for every attempt to play a system sound irrespective
                        of success or failure. The callbacks are issued on a serial queue and the client is
                        responsible for handling thread safety.
*/
extern void
AudioServicesPlayAlertSoundWithCompletion(  SystemSoundID inSystemSoundID,
                                            void (^__nullable inCompletionBlock)(void))
                                                                    __OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);
                                                                
/*!
    @function       AudioServicesPlaySystemSoundWithCompletion
    @abstract       Play a system sound
    @discussion     Play the sound designated by the provided SystemSoundID.
    @param          inSystemSoundID
                        The SystemSoundID to be played.
    @param          inCompletionBlock
                        The completion block gets executed for every attempt to play a system sound irrespective 
                        of success or failure. The callbacks are issued on a serial queue and the client is 
                        responsible for handling thread safety.
*/
extern void
AudioServicesPlaySystemSoundWithCompletion(     SystemSoundID inSystemSoundID,
                                                void (^__nullable inCompletionBlock)(void))
                                                                        __OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);
                                                                
/*!
    @function       AudioServicesGetPropertyInfo
    @abstract       Get information about the size of an AudioServices property and whether it can
                    be set.
    @param          inPropertyID
                        a AudioServicesPropertyID constant.
    @param          inSpecifierSize
                        The size of the specifier data.
    @param          inSpecifier
                        A specifier is a buffer of data used as an input argument to some of the
                        properties.
    @param          outPropertyDataSize
                        The size in bytes of the current value of the property. In order to get the
                        property value, you will need a buffer of this size.
    @param          outWritable
                        Will be set to 1 if writable, or 0 if read only.
    @result         returns kAudioServicesNoError if successful.
*/                            
extern OSStatus 
AudioServicesGetPropertyInfo( AudioServicesPropertyID   inPropertyID,
                              UInt32                    inSpecifierSize,
                              const void * __nullable   inSpecifier,
                              UInt32 * __nullable       outPropertyDataSize,
                              Boolean * __nullable      outWritable)
                                                                    __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function       AudioServicesGetProperty
    @abstract       Retrieve the indicated property data
    @param          inPropertyID
                        a AudioServicesPropertyID constant.
    @param          inSpecifierSize
                        The size of the specifier data.
    @param          inSpecifier
                        A specifier is a buffer of data used as an input argument to some of the
                        properties.
    @param          ioPropertyDataSize
                        On input, the size of the outPropertyData buffer. On output the number of
                        bytes written to the buffer.
    @param          outPropertyData
                        The buffer in which to write the property data. May be NULL if caller only
                        wants ioPropertyDataSize to be filled with the amount that would have been
                        written.
    @result         returns kAudioServicesNoError if successful.
*/                        
extern OSStatus 
AudioServicesGetProperty(   AudioServicesPropertyID         inPropertyID,
                            UInt32                          inSpecifierSize,
                            const void * __nullable         inSpecifier,
                            UInt32 *                        ioPropertyDataSize,
                            void * __nullable               outPropertyData)
                                                                __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function       AudioServicesSetProperty
    @abstract       Set the indicated property data
    @param          inPropertyID
                        a AudioServicesPropertyID constant.
    @param          inSpecifierSize
                        The size of the specifier data.
    @param          inSpecifier
                        A specifier is a buffer of data used as an input argument to some of the
                        properties.
    @param          inPropertyDataSize
                        The size of the inPropertyData buffer.
    @param          inPropertyData
                        The buffer containing the property data.
    @result         returns kAudioServicesNoError if successful.
*/
extern OSStatus 
AudioServicesSetProperty(   AudioServicesPropertyID             inPropertyID,
                            UInt32                              inSpecifierSize,
                            const void * __nullable             inSpecifier,
                            UInt32                              inPropertyDataSize,
                            const void *                        inPropertyData)
                                                                __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);
                                                                
/*!
    This function will be deprecated in a future release. Use AudioServicesPlayAlertSoundWithCompletion instead.
 
    @function       AudioServicesPlayAlertSound
    @abstract       Play an Alert Sound
    @discussion     Play the provided SystemSoundID with AlertSound behavior.
    @param          inSystemSoundID
                        A SystemSoundID for the System Sound server to play. On the desktop you
                        can pass the kSystemSoundID_UserPreferredAlert constant to playback the alert sound 
                        selected by the user in System Preferences. On iOS there is no preferred user alert sound.
*/
extern void 
AudioServicesPlayAlertSound(SystemSoundID inSystemSoundID)                                          
                                                                __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);
                                                                
/*!
    This function will be deprecated in a future release. Use AudioServicesPlaySystemSoundWithCompletion instead.
 
    @function       AudioServicesPlaySystemSound
    @abstract       Play the sound designated by the provided SystemSoundID.
    @discussion     A SystemSoundID indicating the desired System Sound to be played.
    @param          inSystemSoundID
                        A SystemSoundID for the System Sound server to play.
*/
extern void 
AudioServicesPlaySystemSound(SystemSoundID inSystemSoundID)                                         
                                                                __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);
                                                                
/*!
    This function will be deprecated in a future release. Use AudioServicesPlayAlertSoundWithCompletion 
    or AudioServicesPlaySystemSoundWithCompletion instead.
 
    @function       AudioServicesAddSystemSoundCompletion
    @abstract       Call the provided Completion Routine when provided SystemSoundID
                    finishes playing.
    @discussion     Once set, the System Sound server will send a message to the System Sound client
                    indicating which SystemSoundID has finished playing.
    @param          inSystemSoundID
                        The SystemSoundID to associate with the provided completion
                        routine.
    @param          inRunLoop
                        A CFRunLoopRef indicating the desired run loop the completion routine should
                        be run on. Pass NULL to use the main run loop.
    @param          inRunLoopMode
                        A CFStringRef indicating the run loop mode for the runloop where the
                        completion routine will be executed. Pass NULL to use kCFRunLoopDefaultMode.
    @param          inCompletionRoutine
                        An AudioServicesSystemSoundCompletionProc to be called when the provided
                        SystemSoundID has completed playing in the server.
    @param          inClientData
                        A void* to pass client data to the completion routine.
*/
extern OSStatus 
AudioServicesAddSystemSoundCompletion(  SystemSoundID                                       inSystemSoundID,
                                    	CFRunLoopRef __nullable                             inRunLoop,
                                    	CFStringRef __nullable                              inRunLoopMode,
                                    	AudioServicesSystemSoundCompletionProc              inCompletionRoutine,
                                    	void * __nullable                                   inClientData)
                                                                    __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    This function will be deprecated in a future release. Use AudioServicesPlayAlertSoundWithCompletion
    or AudioServicesPlaySystemSoundWithCompletion instead.
 
    @function       AudioServicesRemoveSystemSoundCompletion
    @abstract       Disassociate any completion proc for the specified SystemSoundID
    @discussion     Tells the SystemSound client to remove any completion proc associated with the
                    provided SystemSoundID
    @param          inSystemSoundID
                        The SystemSoundID for which completion routines should be
                        removed.
*/
extern void 
AudioServicesRemoveSystemSoundCompletion(SystemSoundID inSystemSoundID)                             
                                                                    __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

#if !TARGET_OS_IPHONE
//==================================================================================================
#pragma mark    Audio Hardware Service Properties

/*!
    @enum           Audio Hardware Service Properties
    @abstract       AudioObjectPropertySelector values that apply to various kinds of AudioObjects
                    only when accessed via the Audio Hardware Service API.
    @constant       kAudioHardwareServiceProperty_ServiceRestarted
                        A Float32 whose value has no meaning. Rather, this property exists so that
                        clients can be informed when the service has been reset for some reason.
                        When a reset happens, any state the client has with AHS, such as cached data
                        or added listeners, must be re-established by the client.
    @constant       kAudioHardwareServiceDeviceProperty_VirtualMasterVolume
                        A Float32 that represents the value of the volume control. The range is
                        between 0.0 and 1.0 (inclusive). This actual volume controls this property
                        manipulates depends on what the device provides. If the device has a true
                        master volume control, this property directly controls that. If the device
                        has individual channel volume controls, this property will apply to those
                        identified by the device's preferred multi-channel layout (or preferred
                        stereo pair if the device is stereo only). Note that this control maintains
                        the relative balance between all the channels it affects.
    @constant       kAudioHardwareServiceDeviceProperty_VirtualMasterBalance
                        A Float32 that represents the value of the stereo balance control. The range
                        is from 0.0 (all power to the left) to 1.0 (all power to the right) with
                        the value of 0.5 signifying that the channels have equal power. This control
                        is only present for devices that have individual channel volume controls. It
                        manipulates the relative balance between the volume controls on the channels
                        identified as the device's default stereo pair.
*/
CF_ENUM(AudioObjectPropertySelector)
{
    kAudioHardwareServiceProperty_ServiceRestarted              = 'srst',
    kAudioHardwareServiceDeviceProperty_VirtualMasterVolume     = 'vmvc',
    kAudioHardwareServiceDeviceProperty_VirtualMasterBalance    = 'vmbc'
};

//==================================================================================================
#pragma mark    Audio Hardware Service Functions

/*!
    @functiongroup  Audio Hardware Service
*/

/*!
    @function       AudioHardwareServiceHasProperty
    @abstract       Queries an AudioObject about whether or not it has the given property.
    @param          inObjectID
                        The AudioObject to query.
    @param          inAddress
                        An AudioObjectPropertyAddress indicating which property is being queried.
    @result         A Boolean indicating whether or not the AudioObject has the given property.
*/
extern Boolean
AudioHardwareServiceHasProperty(    AudioObjectID                       inObjectID,
                                    const AudioObjectPropertyAddress*   inAddress)                  
                                                            __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5,__MAC_10_11, __IPHONE_NA, __IPHONE_NA);

/*!
    @function       AudioHardwareServiceIsPropertySettable
    @abstract       Queries an AudioObject about whether or not the given property can be set using
                    AudioHardwareServiceSetPropertyData.
    @param          inObjectID
                        The AudioObject to query.
    @param          inAddress
                        An AudioObjectPropertyAddress indicating which property is being queried.
    @param          outIsSettable
                        A Boolean indicating whether or not the property can be set.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
AudioHardwareServiceIsPropertySettable( AudioObjectID                       inObjectID,
                                        const AudioObjectPropertyAddress*   inAddress,
                                        Boolean*                            outIsSettable)          
                                                            __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5,__MAC_10_11, __IPHONE_NA, __IPHONE_NA);

/*!
    @function       AudioHardwareServiceGetPropertyDataSize
    @abstract       Queries an AudioObject to find the size of the data for the given property.
    @param          inObjectID
                        The AudioObject to query.
    @param          inAddress
                        An AudioObjectPropertyAddress indicating which property is being queried.
    @param          inQualifierDataSize
                        A UInt32 indicating the size of the buffer pointed to by inQualifierData.
                        Note that not all properties require qualification, in which case this
                        value will be 0.
    @param          inQualifierData
                        A buffer of data to be used in determining the data of the property being
                        queried. Note that not all properties require qualification, in which case
                        this value will be NULL.
    @param          outDataSize
                        A UInt32 indicating how many bytes the data for the given property occupies.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
AudioHardwareServiceGetPropertyDataSize(    AudioObjectID                       inObjectID,
                                            const AudioObjectPropertyAddress*   inAddress,
                                            UInt32                              inQualifierDataSize,
                                            const void*                         inQualifierData,
                                            UInt32*                             outDataSize)        
                                                            __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5,__MAC_10_11, __IPHONE_NA, __IPHONE_NA);

/*!
    @function       AudioHardwareServiceGetPropertyData
    @abstract       Queries an AudioObject to get the data of the given property and places it in
                    the provided buffer.
    @param          inObjectID
                        The AudioObject to query.
    @param          inAddress
                        An AudioObjectPropertyAddress indicating which property is being queried.
    @param          inQualifierDataSize
                        A UInt32 indicating the size of the buffer pointed to by inQualifierData.
                        Note that not all properties require qualification, in which case this
                        value will be 0.
    @param          inQualifierData
                        A buffer of data to be used in determining the data of the property being
                        queried. Note that not all properties require qualification, in which case
                        this value will be NULL.
    @param          ioDataSize
                        A UInt32 which on entry indicates the size of the buffer pointed to by
                        outData and on exit indicates how much of the buffer was used.
    @param          outData
                        The buffer into which the AudioObject will put the data for the given
                        property.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
AudioHardwareServiceGetPropertyData(    AudioObjectID                       inObjectID,
                                        const AudioObjectPropertyAddress*   inAddress,
                                        UInt32                              inQualifierDataSize,
                                        const void*                         inQualifierData,
                                        UInt32*                             ioDataSize,
                                        void*                               outData)                
                                                        __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5,__MAC_10_11, __IPHONE_NA, __IPHONE_NA);

/*!
    @function       AudioHardwareServiceSetPropertyData
    @abstract       Tells an AudioObject to change the value of the given property using the
                    provided data.
    @discussion     Note that the value of the property should not be considered changed until the
                    HAL has called the listeners as many properties values are changed
                    asynchronously.
    @param          inObjectID
                        The AudioObject to change.
    @param          inAddress
                        An AudioObjectPropertyAddress indicating which property is being changed.
    @param          inQualifierDataSize
                        A UInt32 indicating the size of the buffer pointed to by inQualifierData.
                        Note that not all properties require qualification, in which case this
                        value will be 0.
    @param          inQualifierData
                        A buffer of data to be used in determining the data of the property being
                        queried. Note that not all properties require qualification, in which case
                        this value will be NULL.
    @param          inDataSize
                        A UInt32 indicating the size of the buffer pointed to by inData.
    @param          inData
                        The buffer containing the data to be used to change the property's value.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
AudioHardwareServiceSetPropertyData(    AudioObjectID                       inObjectID,
                                        const AudioObjectPropertyAddress*   inAddress,
                                        UInt32                              inQualifierDataSize,
                                        const void*                         inQualifierData,
                                        UInt32                              inDataSize,
                                        const void*                         inData)                 
                                                        __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5,__MAC_10_11, __IPHONE_NA, __IPHONE_NA);

/*!
    @function       AudioHardwareServiceAddPropertyListener
    @abstract       Registers the given AudioObjectPropertyListenerProc to receive notifications
                    when the given properties change.
    @param          inObjectID
                        The AudioObject to register the listener with.
    @param          inAddress
                        The AudioObjectPropertyAddresses indicating which property the listener
                        should be notified about.
    @param          inListener
                        The AudioObjectPropertyListenerProc to call.
    @param          inClientData
                        A pointer to client data that is passed to the listener when it is called.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
AudioHardwareServiceAddPropertyListener(    AudioObjectID                       inObjectID,
                                            const AudioObjectPropertyAddress*   inAddress,
                                            AudioObjectPropertyListenerProc     inListener,
                                            void*                               inClientData)       
                                                        __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5,__MAC_10_11, __IPHONE_NA, __IPHONE_NA);

/*!
    @function       AudioHardwareServiceRemovePropertyListener
    @abstract       Unregisters the given AudioObjectPropertyListenerProc from receiving
                    notifications when the given properties change.
    @param          inObjectID
                        The AudioObject to unregister the listener from.
    @param          inAddress
                        The AudioObjectPropertyAddresses indicating which property the listener
                        will stop being notified about.
    @param          inListener
                        The AudioObjectPropertyListenerProc being removed.
    @param          inClientData
                        A pointer to client data that is passed to the listener when it is called.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
AudioHardwareServiceRemovePropertyListener( AudioObjectID                       inObjectID,
                                            const AudioObjectPropertyAddress*   inAddress,
                                            AudioObjectPropertyListenerProc     inListener,
                                            void*                               inClientData)       
                                                        __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5,__MAC_10_11, __IPHONE_NA, __IPHONE_NA);

#endif //!TARGET_OS_IPHONE

CF_ASSUME_NONNULL_END
    
#ifdef __cplusplus
}
#endif

#endif /* AudioToolbox_AudioServices_h */
// ==========  AudioToolbox.framework/Headers/AudioFormat.h
/*!
	@file		AudioFormat.h
	@framework	AudioToolbox.framework
	@copyright	(c) 1985-2015 by Apple, Inc., all rights reserved.
    @abstract	API for finding things out about audio formats.
*/

#ifndef AudioToolbox_AudioFormat_h
#define AudioToolbox_AudioFormat_h

//=============================================================================
//	Includes
//=============================================================================

//	System Includes
#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreAudio/CoreAudioTypes.h>
#else
	#include <CoreAudioTypes.h>
#endif

CF_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
extern "C"
{
#endif

//=============================================================================
//	Types
//=============================================================================

/*!
    @typedef	AudioFormatPropertyID
    @abstract   A type for four char codes for property IDs
*/
typedef UInt32	AudioFormatPropertyID;

/*!
    @enum		PanningMode
    @abstract   Different panning algorithms.
    @constant   kPanningMode_SoundField
					Sound field panning algorithm
    @constant   kPanningMode_VectorBasedPanning
					Vector based panning algorithm
*/
typedef CF_ENUM(UInt32, AudioPanningMode) {
	kPanningMode_SoundField		 					= 3,
	kPanningMode_VectorBasedPanning					= 4
};

/*!
    @struct		AudioPanningInfo
    @abstract   This struct is for use with kAudioFormatProperty_PanningMatrix.
    @field      mPanningMode			the PanningMode to be used for the pan
    @field      mCoordinateFlags		the coordinates are specified as in the AudioChannelDescription struct in CoreAudioTypes.h
    @field      mCoordinates			the coordinates are specified as in the AudioChannelDescription struct in CoreAudioTypes.h
    @field      mGainScale				
					mGainScale is used to multiply the panning values.
					In typical usage you are applying an existing volume.
					value in 0 -> 1 (where 1 is unity gain) to the panned values.
					1 would give you panning at unity.
					0 would give you back a matrix of zeroes.
    @field      mOutputChannelMap				
					This is the channel map that is going to be used to determine channel volumes for this pan.
*/
struct AudioPanningInfo {
	AudioPanningMode			mPanningMode;
	UInt32						mCoordinateFlags;
	Float32						mCoordinates[3];	
	Float32						mGainScale;
	const AudioChannelLayout *	mOutputChannelMap;
};
typedef struct AudioPanningInfo AudioPanningInfo;

/*!
    @enum		AudioBalanceFadeType
    @abstract   used for mType field of AudioBalanceFade struct
    @constant   kAudioBalanceFadeType_MaxUnityGain
					the gain value never exceeds 1.0, the opposite channel fades out. 
					This can reduce overall loudness when the balance or fade is not in the center.
    @constant   kAudioBalanceFadeType_EqualPower
					The overall loudness remains constant, but gain can exceed 1.0.
					the gain value is 1.0 when the balance and fade are in the center.
					From there they can increase to +3dB (1.414) and decrease to -inf dB (0.0).
*/
typedef CF_ENUM(UInt32, AudioBalanceFadeType) {
	kAudioBalanceFadeType_MaxUnityGain = 0,
	kAudioBalanceFadeType_EqualPower = 1
};
	
/*!
    @struct		AudioBalanceFade
    @abstract   this struct is used with kAudioFormatProperty_BalanceFade
    @field      mLeftRightBalance 
					-1 is full left, 0 is center, +1 is full right
    @field      mBackFrontFade 
					-1 is full rear, 0 is center, +1 is full front
    @field      mType 
					an AudioBalanceFadeType constant
    @field      mChannelLayout 
					a pointer to an AudioChannelLayout
*/
struct AudioBalanceFade
{
	Float32						mLeftRightBalance;		// -1 is full left, 0 is center, +1 is full right
	Float32						mBackFrontFade;			// -1 is full rear, 0 is center, +1 is full front
	AudioBalanceFadeType		mType;					// max unity gain, or equal power.
	const AudioChannelLayout*	mChannelLayout;
};
typedef struct AudioBalanceFade AudioBalanceFade;

/*!
    @struct		AudioFormatInfo
    @abstract   this struct is used as a specifier for the kAudioFormatProperty_FormatList property
    @field      mASBD 
					an AudioStreamBasicDescription
    @field      mMagicCookie 
					a pointer to the decompression info for the data described in mASBD
    @field      mMagicCookieSize 
					the size in bytes of mMagicCookie
*/
struct AudioFormatInfo
{
	AudioStreamBasicDescription		mASBD;
	const void*						mMagicCookie;
	UInt32							mMagicCookieSize;
};
typedef struct AudioFormatInfo AudioFormatInfo;

/*!
    @struct		ExtendedAudioFormatInfo
    @abstract   this struct is used as a specifier for the kAudioFormatProperty_FormatList property
    @field      mASBD 
					an AudioStreamBasicDescription
    @field      mMagicCookie 
					a pointer to the decompression info for the data described in mASBD
    @field      mMagicCookieSize 
					the size in bytes of mMagicCookie
	@field		mClassDescription
					an AudioClassDescription specifying the codec to be used in answering the question.
*/
struct ExtendedAudioFormatInfo
{
	AudioStreamBasicDescription		mASBD;
	const void*						mMagicCookie;
	UInt32							mMagicCookieSize;
	AudioClassDescription			mClassDescription;
};
typedef struct ExtendedAudioFormatInfo ExtendedAudioFormatInfo;

/*!
    @struct		AudioFormatListItem
    @abstract   this struct is used as output from the kAudioFormatProperty_FormatList property
    @field      mASBD 
					an AudioStreamBasicDescription
    @field      mChannelLayoutTag 
					an AudioChannelLayoutTag
*/
struct AudioFormatListItem
{
	AudioStreamBasicDescription		mASBD;
	AudioChannelLayoutTag			mChannelLayoutTag;
};
typedef struct AudioFormatListItem AudioFormatListItem;

//=============================================================================
//	Properties - for various format structures.
//=============================================================================

/*!
    @enum		AudioFormatProperty constants
    @abstract   constants for use with AudioFormatGetPropertyInfo and AudioFormatGetProperty.
    @constant   kAudioFormatProperty_FormatInfo
					Retrieves general information about a format. The specifier is a
					magic cookie, or NULL.
					On input, the property value is an AudioStreamBasicDescription which 
					should have at least the mFormatID filled out. On output it will be filled out
					as much as possible given the information known about the format 
					and the contents of the magic cookie (if any is given).
					If multiple formats can be described by the AudioStreamBasicDescription and the associated magic cookie,
					this property will return the base level format.
    @constant   kAudioFormatProperty_FormatIsVBR
					Returns whether or not a format has a variable number of bytes per
					packet. The specifier is an AudioStreamBasicDescription describing
					the format to ask about. The value is a UInt32 where non-zero means
					the format is variable bytes per packet.
    @constant   kAudioFormatProperty_FormatIsExternallyFramed
					Returns whether or not a format requires external framing information,
					i.e. AudioStreamPacketDescriptions. 
					The specifier is an AudioStreamBasicDescription describing
					the format to ask about. The value is a UInt32 where non-zero means
					the format is externally framed. Any format which has variable byte sized packets
					requires AudioStreamPacketDescriptions.
    @constant   kAudioFormatProperty_FormatIsEncrypted
                    Returns whether or not a format is encrypted. The specifier is a UInt32 format ID.
                    The value is a UInt32 where non-zero means the format is encrypted.
    @constant   kAudioFormatProperty_EncodeFormatIDs
					No specifier needed. Must be set to NULL.
					Returns an array of UInt32 format IDs for formats that are valid output formats 
					for a converter. 
    @constant   kAudioFormatProperty_DecodeFormatIDs
					No specifier needed. Must be set to NULL.
					Returns an array of UInt32 format IDs for formats that are valid input formats 
					for a converter. 
    @constant   kAudioFormatProperty_Encoders
					The specifier is the format that you are interested in, e.g. 'aac '
					Returns an array of AudioClassDescriptions for all installed encoders for the given format 
    @constant   kAudioFormatProperty_Decoders
					The specifier is the format that you are interested in, e.g. 'aac '
					Returns an array of AudioClassDescriptions for all installed decoders for the given format 
    @constant   kAudioFormatProperty_AvailableEncodeBitRates
					The specifier is a UInt32 format ID.
					The property value is an array of AudioValueRange describing all available bit rates.
    @constant   kAudioFormatProperty_AvailableEncodeSampleRates
					The specifier is a UInt32 format ID.
					The property value is an array of AudioValueRange describing all available sample rates.
    @constant   kAudioFormatProperty_AvailableEncodeChannelLayoutTags
					The specifier is an AudioStreamBasicDescription with at least the mFormatID 
					and mChannelsPerFrame fields set.
					The property value is an array of AudioChannelLayoutTags for the format and number of
					channels specified. If mChannelsPerFrame is zero, then all layouts supported by
					the format are returned.	
    @constant   kAudioFormatProperty_AvailableEncodeNumberChannels
					The specifier is an AudioStreamBasicDescription with at least the mFormatID field set.
					The property value is an array of UInt32 indicating the number of channels that can be encoded.
					A value of 0xFFFFFFFF indicates that any number of channels may be encoded. 
    @constant   kAudioFormatProperty_FormatName
					Returns a name for a given format. The specifier is an
					AudioStreamBasicDescription describing the format to ask about.
					The value is a CFStringRef. The caller is responsible for releasing the
					returned string. For some formats (eg, Linear PCM) you will get back a
					descriptive string (e.g. 16-bit, interleaved, etc...)
    @constant   kAudioFormatProperty_ASBDFromESDS
					Returns an audio stream description for a given ESDS. The specifier is an ESDS. 
					The value is a AudioStreamBasicDescription. If multiple formats can be described 
					by the ESDS this property will return the base level format.
    @constant   kAudioFormatProperty_ChannelLayoutFromESDS
					Returns an audio channel layout for a given ESDS. The specifier is an
					ESDS. The value is a AudioChannelLayout.
    @constant   kAudioFormatProperty_ASBDFromMPEGPacket
					Returns an audio stream description for a given MPEG Packet. The specifier is an MPEG Packet. 
					The value is a AudioStreamBasicDescription.					
    @constant   kAudioFormatProperty_FormatList
					Returns a list of AudioFormatListItem structs describing the audio formats contained within the compressed bit stream
					as described by the magic cookie. The specifier is an AudioFormatInfo struct. The mFormatID member of the 
					ASBD struct must filled in. Formats are returned in order from the most to least 'rich', with 
					channel count taking the highest precedence followed by sample rate. The kAudioFormatProperty_FormatList property 
					is the preferred method for discovering format information of the audio data. If the audio data can only be described
					by a single AudioFormatListItem, this property would be equivalent to using the kAudioFormatProperty_FormatInfo property,
					which should be used by the application as a fallback case, to ensure backward compatibility with existing systems 
					when kAudioFormatProperty_FormatList is not present on the running system.
    @constant   kAudioFormatProperty_OutputFormatList
					Returns a list of AudioFormatListItem structs describing the audio formats which may be obtained by decoding the format
					described by the specifier.
					The specifier is an AudioFormatInfo struct. At a minimum formatID member of the ASBD struct must filled in. Other fields
					may be filled in. If there is no magic cookie, then the number of channels and sample rate should be filled in. 
	@constant	kAudioFormatProperty_FirstPlayableFormatFromList
					The specifier is a list of 1 or more AudioFormatListItem. Generally it is the list of these items returned from kAudioFormatProperty_FormatList. The property value retrieved is an UInt32 that specifies an index into that list. The list that the caller provides is generally sorted with the first item as the best format (most number of channels, highest sample rate), and the returned index represents the first item in that list that can be played by the system. 
					Thus, the property is typically used to determine the best playable format for a given (layered) audio stream
	@constant   kAudioFormatProperty_ValidateChannelLayout
					The specifier is an AudioChannelLayout. The property value and size are not used and must be set to NULL.
					This property validates an AudioChannelLayout. This is useful if the layout has come from an untrusted source such as a file.
					It returns noErr if the AudioChannelLayout is OK, kAudio_ParamError if there is a structural problem with the layout,
					or kAudioFormatUnknownFormatError for unrecognized layout tags or channel labels.
	@constant   kAudioFormatProperty_ChannelLayoutForTag
					Returns the channel descriptions for a standard channel layout.
					The specifier is a AudioChannelLayoutTag (the mChannelLayoutTag field 
					of the AudioChannelLayout struct) containing the layout constant. 
					The value is an AudioChannelLayout structure. In typical use a AudioChannelLayout
					can be valid with just a defined AudioChannelLayoutTag (ie, those layouts
					have predefined speaker locations and orderings).
					Returns an error if the tag is kAudioChannelLayoutTag_UseChannelBitmap 
    @constant   kAudioFormatProperty_TagForChannelLayout
					Returns an AudioChannelLayoutTag for a layout, if there is one.
					The specifier is an AudioChannelLayout containing the layout description.
					The value is an AudioChannelLayoutTag.
					This can be used to reduce a layout specified by kAudioChannelLayoutTag_UseChannelDescriptions
					or kAudioChannelLayoutTag_UseChannelBitmap to a known AudioChannelLayoutTag.
    @constant   kAudioFormatProperty_ChannelLayoutForBitmap
					Returns the channel descriptions for a standard channel layout.
					The specifier is a UInt32 (the mChannelBitmap field 
					of the AudioChannelLayout struct) containing the layout bitmap. The value
					is an AudioChannelLayout structure. In some uses, an AudioChannelLayout can be 
					valid with the layoutTag set to "use bitmap" and the bitmap set appropriately.
    @constant   kAudioFormatProperty_BitmapForLayoutTag
					Returns a bitmap for an AudioChannelLayoutTag, if there is one.
					The specifier is a AudioChannelLayoutTag  containing the layout tag.
					The value is an UInt32 bitmap. The bits are as defined in CoreAudioTypes.h.
					To go in the other direction, i.e. get a layout tag for a bitmap, 
					use kAudioFormatProperty_TagForChannelLayout where your layout tag 
					is kAudioChannelLayoutTag_UseChannelBitmap and the bitmap is filled in.
    @constant   kAudioFormatProperty_ChannelLayoutName
					Returns the a name for a particular channel layout. The specifier is
					an AudioChannelLayout containing the layout description. The value
					is a CFStringRef. The caller is responsible for releasing the
					returned string.
    @constant   kAudioFormatProperty_ChannelLayoutSimpleName
					Returns the a simpler name for a channel layout than does kAudioFormatProperty_ChannelLayoutName. 
					It omits the channel labels from the name. The specifier is
					an AudioChannelLayout containing the layout description. The value
					is a CFStringRef. The caller is responsible for releasing the
					returned string.
    @constant   kAudioFormatProperty_ChannelName
					Returns the name for a particular channel. The specifier is an
					AudioChannelDescription which has the mChannelLabel field set. The value
					is a CFStringRef. The caller is responsible for releasing the
					returned string.
    @constant   kAudioFormatProperty_ChannelShortName
					Returns an abbreviated name for a particular channel. The specifier is an
					AudioChannelDescription which has the mChannelLabel field set. The value
					is a CFStringRef. The caller is responsible for releasing the
					returned string.
    @constant   kAudioFormatProperty_MatrixMixMap
					Returns a matrix of scaling coefficients for converting audio from one channel map 
					to another in a standard way, if one is known. Otherwise an error is returned.
					The specifier is an array of two pointers to AudioChannelLayout structures. 
					The first points to the input layout, the second to the output layout.
					The value is a two dimensional array of Float32 where the first dimension (rows) 
					is the input channel and the second dimension (columns) is the output channel. 
    @constant   kAudioFormatProperty_ChannelMap
					Returns an array of SInt32 for reordering input channels.
					The specifier is an array of two pointers to AudioChannelLayout structures. 
					The first points to the input layout, the second to the output layout.
					The length of the output array is equal to the number of output channels.
    @constant   kAudioFormatProperty_NumberOfChannelsForLayout
					This is a general call for parsing a AudioChannelLayout provided as the specifier,
					to determine the number of valid channels that are represented. So, if the
					LayoutTag is specified, it returns the number of channels for that layout. If 
					the bitmap is specified, it returns the number of channels represented by that bitmap.
					If the layout tag is 'kAudioChannelLayoutTag_UseChannelDescriptions' it returns
						the number of channel descriptions.
    @constant   kAudioFormatProperty_AreChannelLayoutsEquivalent
					Returns a UInt32 which is 1 if two layouts are equivalent and 0 if they are not equivalent.
					In order to be equivalent, the layouts must describe the same channels in the same order.
					Whether the layout is represented by a bitmap, channel descriptions or a channel layout tag is not significant.
					The channel coordinates are only significant if the channel label is kAudioChannelLabel_UseCoordinates.
					The specifier is an array of two pointers to AudioChannelLayout structures. 
					The value is a pointer to the UInt32 result.
    @constant   kAudioFormatProperty_ChannelLayoutHash
					Returns a UInt32 which represents the hash of the provided channel layout.
					The specifier is a pointer to an AudioChannelLayout structure.
					The value is a pointer to the UInt32 result.
    @constant   kAudioFormatProperty_TagsForNumberOfChannels
					returns an array of AudioChannelLayoutTags for the number of channels specified.
					The specifier is a UInt32 number of channels. 
    @constant   kAudioFormatProperty_PanningMatrix
					This call will pass in an AudioPanningInfo struct that specifies one of the
					kPanningMode_ constants for the panning algorithm and an AudioChannelLayout
					to describe the destination channel layout. As in kAudioFormatProperty_MatrixMixMap
					the return value is an array of Float32 values of the number of channels
						represented by this specified channel layout. It is presumed that the source 
					being panned is mono (thus for a quad channel layout, 4 Float32 values are returned).
					The intention of this API is to provide support for panning operations that are
					strictly manipulating the respective volumes of the channels. Thus, more
					complex panners (like HRTF, distance filtering etc,) will not be represented
						by this API. The resultant volume scalars can then be applied to a mixer
					or some other processing code to adapt the individual volumes of the mixed
					output.
					The volume values will typically be presented within a 0->1 range (where 1 is unity gain)
					For stereo formats, vector based panning is equivalent to the equal-power pan mode.
    @constant   kAudioFormatProperty_BalanceFade
					get an array of coefficients for applying left/right balance and front/back fade.
					The specifier is an AudioBalanceFade struct. 
					the return value is an array of Float32 values of the number of channels
						represented by this specified channel layout.  
					The volume values will typically be presented within a 0->1 range (where 1 is unity gain)
    @constant   kAudioFormatProperty_ID3TagSize
					Returns a UInt32 indicating the ID3 tag size. 
					The specifier must begin with the ID3 tag header and be at least 10 bytes in length
    @constant   kAudioFormatProperty_ID3TagToDictionary
					Returns a CFDictionary containing key/value pairs for the frames in the ID3 tag
					The specifier is the entire ID3 tag
					Caller must call CFRelease for the returned dictionary
					
*/
CF_ENUM(AudioFormatPropertyID)
{
//=============================================================================
//	The following properties are concerned with the AudioStreamBasicDescription
//=============================================================================
	kAudioFormatProperty_FormatInfo						= 'fmti',
	kAudioFormatProperty_FormatName						= 'fnam',
	kAudioFormatProperty_EncodeFormatIDs				= 'acof',
	kAudioFormatProperty_DecodeFormatIDs				= 'acif',
	kAudioFormatProperty_FormatList						= 'flst',
    kAudioFormatProperty_ASBDFromESDS                   = 'essd',
    kAudioFormatProperty_ChannelLayoutFromESDS          = 'escl',
	kAudioFormatProperty_OutputFormatList				= 'ofls',
	kAudioFormatProperty_FirstPlayableFormatFromList	= 'fpfl',
	kAudioFormatProperty_FormatIsVBR					= 'fvbr',	
	kAudioFormatProperty_FormatIsExternallyFramed		= 'fexf',
	kAudioFormatProperty_FormatIsEncrypted				= 'cryp',
	kAudioFormatProperty_Encoders						= 'aven',	
	kAudioFormatProperty_Decoders						= 'avde',
	kAudioFormatProperty_AvailableEncodeBitRates		= 'aebr',
	kAudioFormatProperty_AvailableEncodeSampleRates		= 'aesr',
	kAudioFormatProperty_AvailableEncodeChannelLayoutTags = 'aecl',
	kAudioFormatProperty_AvailableEncodeNumberChannels		= 'avnc',
	kAudioFormatProperty_ASBDFromMPEGPacket				= 'admp',


//=============================================================================
//	The following properties concern the AudioChannelLayout struct (speaker layouts)
//=============================================================================
	kAudioFormatProperty_BitmapForLayoutTag				= 'bmtg',
	kAudioFormatProperty_MatrixMixMap					= 'mmap',
    kAudioFormatProperty_ChannelMap						= 'chmp',
	kAudioFormatProperty_NumberOfChannelsForLayout		= 'nchm',
	kAudioFormatProperty_AreChannelLayoutsEquivalent	= 'cheq',
    kAudioFormatProperty_ChannelLayoutHash              = 'chha',
	kAudioFormatProperty_ValidateChannelLayout			= 'vacl',
	kAudioFormatProperty_ChannelLayoutForTag			= 'cmpl',
	kAudioFormatProperty_TagForChannelLayout			= 'cmpt',
	kAudioFormatProperty_ChannelLayoutName				= 'lonm',
	kAudioFormatProperty_ChannelLayoutSimpleName		= 'lsnm',
	kAudioFormatProperty_ChannelLayoutForBitmap			= 'cmpb',
	kAudioFormatProperty_ChannelName					= 'cnam',
	kAudioFormatProperty_ChannelShortName				= 'csnm',

	kAudioFormatProperty_TagsForNumberOfChannels		= 'tagc',				
	kAudioFormatProperty_PanningMatrix					= 'panm',
	kAudioFormatProperty_BalanceFade					= 'balf',

//=============================================================================
//	The following properties concern the ID3 Tags
//=============================================================================

	kAudioFormatProperty_ID3TagSize						= 'id3s',
	kAudioFormatProperty_ID3TagToDictionary				= 'id3d'
};

#if TARGET_OS_IPHONE

CF_ENUM(AudioFormatPropertyID) {
	kAudioFormatProperty_HardwareCodecCapabilities		= 'hwcc',
} __attribute__((deprecated));

/*!
	@enum           AudioCodecComponentType
 
	@discussion     Collection of audio codec component types.
					(On Mac OS X these declarations are in AudioUnit/AudioCodec.h).
 
	@constant		kAudioDecoderComponentType
					A codec that translates data in some other format into linear PCM.
					The component subtype specifies the format ID of the other format.
	@constant		kAudioEncoderComponentType
					A codec that translates linear PCM data into some other format
					The component subtype specifies the format ID of the other format
*/
CF_ENUM(UInt32)
{
	kAudioDecoderComponentType								= 'adec',	
	kAudioEncoderComponentType								= 'aenc',	
};

/*!
	@enum			AudioCodecComponentManufacturer

	@discussion		Audio codec component manufacturer codes. On iPhoneOS, a codec's
					manufacturer can be used to distinguish between hardware and
					software codecs.

	@constant		kAppleSoftwareAudioCodecManufacturer
					Apple software audio codecs.
	@constant		kAppleHardwareAudioCodecManufacturer
					Apple hardware audio codecs.
*/
CF_ENUM(UInt32)
{
	kAppleSoftwareAudioCodecManufacturer					= 'appl',
	kAppleHardwareAudioCodecManufacturer					= 'aphw'
};

#endif


//=============================================================================
//	Routines
//=============================================================================

/*!
    @function	AudioFormatGetPropertyInfo
    @abstract   Retrieve information about the given property
    @param      inPropertyID		an AudioFormatPropertyID constant.
    @param      inSpecifierSize		The size of the specifier data.
    @param      inSpecifier			A specifier is a buffer of data used as an input argument to some of the properties.
    @param      outPropertyDataSize	The size in bytes of the current value of the property. In order to get the property value,
									you will need a buffer of this size.
    @result     returns noErr if successful.
*/
extern OSStatus
AudioFormatGetPropertyInfo(	AudioFormatPropertyID	inPropertyID,
							UInt32					inSpecifierSize,
							const void * __nullable	inSpecifier,
							UInt32 *				outPropertyDataSize)	__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_2_0);

/*!
    @function	AudioFormatGetProperty
    @abstract   Retrieve the indicated property data
    @param      inPropertyID		an AudioFormatPropertyID constant.
    @param      inSpecifierSize		The size of the specifier data.
    @param      inSpecifier			A specifier is a buffer of data used as an input argument to some of the properties.
    @param      ioPropertyDataSize	on input the size of the outPropertyData buffer. On output the number of bytes written to the buffer.
    @param      outPropertyData		the buffer in which to write the property data. If outPropertyData is NULL and ioPropertyDataSize is
									not, the amount that would have been written will be reported.
    @result     returns noErr if successful.
*/
extern OSStatus
AudioFormatGetProperty(	AudioFormatPropertyID	inPropertyID,
						UInt32					inSpecifierSize,
						const void * __nullable	inSpecifier,
						UInt32 * __nullable		ioPropertyDataSize,
						void * __nullable		outPropertyData)			__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_2_0);


//-----------------------------------------------------------------------------
//  AudioFormat Error Codes
//-----------------------------------------------------------------------------

CF_ENUM(OSStatus)
{
        kAudioFormatUnspecifiedError						= 'what',	// 0x77686174, 2003329396
        kAudioFormatUnsupportedPropertyError 				= 'prop',	// 0x70726F70, 1886547824
        kAudioFormatBadPropertySizeError 					= '!siz',	// 0x2173697A, 561211770
        kAudioFormatBadSpecifierSizeError 					= '!spc',	// 0x21737063, 561213539
        kAudioFormatUnsupportedDataFormatError 				= 'fmt?',	// 0x666D743F, 1718449215
        kAudioFormatUnknownFormatError 						= '!fmt'	// 0x21666D74, 560360820
};


#if defined(__cplusplus)
}
#endif

CF_ASSUME_NONNULL_END

#endif // AudioToolbox_AudioFormat_h
// ==========  AudioToolbox.framework/Headers/CAFFile.h
/*!
	@file		CAFFile.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2004-2015 by Apple, Inc., all rights reserved.
	@abstract	The data structures contained within a CAF (Core Audio Format) file.
*/

#ifndef AudioToolbox_CAFFile_h
#define AudioToolbox_CAFFile_h

#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreAudio/CoreAudioTypes.h>
#else
	#include <CoreAudioTypes.h>
#endif

#if TARGET_OS_WIN32
#define ATTRIBUTE_PACKED
#pragma pack(push, 1)
#else
#define ATTRIBUTE_PACKED __attribute__((__packed__))
#endif

// In a CAF File all of these types' byte order is big endian.
// When reading or writing these values the program will need to flip byte order to native endian

// CAF File Header
CF_ENUM(UInt32) {
	kCAF_FileType				= 'caff',
	kCAF_FileVersion_Initial	= 1
};

// CAF Chunk Types	
CF_ENUM(UInt32) {
	kCAF_StreamDescriptionChunkID   = 'desc',
	kCAF_AudioDataChunkID			= 'data',
	kCAF_ChannelLayoutChunkID		= 'chan',
	kCAF_FillerChunkID				= 'free',
	kCAF_MarkerChunkID				= 'mark',
	kCAF_RegionChunkID				= 'regn',
	kCAF_InstrumentChunkID			= 'inst',
	kCAF_MagicCookieID				= 'kuki',
	kCAF_InfoStringsChunkID			= 'info',
	kCAF_EditCommentsChunkID		= 'edct',
	kCAF_PacketTableChunkID			= 'pakt',
	kCAF_StringsChunkID				= 'strg',
	kCAF_UUIDChunkID				= 'uuid',
	kCAF_PeakChunkID				= 'peak',
	kCAF_OverviewChunkID			= 'ovvw',
	kCAF_MIDIChunkID				= 'midi',
	kCAF_UMIDChunkID				= 'umid',
	kCAF_FormatListID				= 'ldsc',
	kCAF_iXMLChunkID				= 'iXML'
};


struct CAFFileHeader
{
        UInt32          mFileType;			// 'caff'
		UInt16			mFileVersion;		//initial revision set to 1
		UInt16			mFileFlags;			//initial revision set to 0
} ATTRIBUTE_PACKED;
typedef struct CAFFileHeader CAFFileHeader;


struct CAFChunkHeader
{
        UInt32          mChunkType; // four char code
        SInt64          mChunkSize;  // size in bytes of the chunk data (not including this header).
									// mChunkSize is SInt64 not UInt64 because negative values for 
									// the data size can have a special meaning
} ATTRIBUTE_PACKED;

typedef struct CAFChunkHeader CAFChunkHeader;

struct CAF_UUID_ChunkHeader
{
        CAFChunkHeader   mHeader;
        UInt8            mUUID[16];
} ATTRIBUTE_PACKED;
typedef struct CAF_UUID_ChunkHeader CAF_UUID_ChunkHeader;


// these are the flags if the format ID is 'lpcm'
// <CoreAudio/CoreAudioTypes.h> declares some of the format constants 
// that can be used as Data Formats in a CAF file
typedef CF_OPTIONS(UInt32, CAFFormatFlags)
{
    kCAFLinearPCMFormatFlagIsFloat				= (1L << 0),
    kCAFLinearPCMFormatFlagIsLittleEndian		= (1L << 1)
};

// Every file MUST have this chunk. It MUST be the first chunk in the file
struct CAFAudioDescription
{
        Float64 mSampleRate;
        UInt32  mFormatID;
        CAFFormatFlags  mFormatFlags;
        UInt32  mBytesPerPacket;
        UInt32  mFramesPerPacket;
        UInt32  mChannelsPerFrame;
        UInt32  mBitsPerChannel;
} ATTRIBUTE_PACKED;
typedef struct CAFAudioDescription  CAFAudioDescription;


// 'ldsc'  format list chunk.
// for data formats like AAC SBR which can be decompressed to multiple formats, this chunk contains a list of
// CAFAudioFormatListItem describing those formats. The list is ordered from best to worst by number of channels 
// and sample rate in that order. mChannelLayoutTag is an AudioChannelLayoutTag as defined in CoreAudioTypes.h

struct CAFAudioFormatListItem
{
	CAFAudioDescription mFormat;
	UInt32 				mChannelLayoutTag;
} ATTRIBUTE_PACKED;

// 'chan'  Optional chunk.
// struct AudioChannelLayout  as defined in CoreAudioTypes.h.

// 'free'
// this is a padding chunk for reserving space in the file. content is meaningless.

// 'kuki'
// this is the magic cookie chunk. bag of bytes.

// 'data'    Every file MUST have this chunk.
// actual audio data can be any format as described by the 'asbd' chunk.

// if mChunkSize is < 0 then this is the last chunk in the file and the actual length 
// should be determined from the file size. 
// The motivation for this is to allow writing the files without seeking to update size fields after every 
// write in order to keep the file legal.
// The program can put a -1 in the mChunkSize field and 
// update it only once at the end of recording. 
// If the program were to crash during recording then the file is still well defined.

// 'pakt' Required if either/or mBytesPerPacket or mFramesPerPacket in the Format Description are zero
// For formats that are packetized and have variable sized packets. 
// The table is stored as an array of one or two variable length integers. 
// (a) size in bytes of the data of a given packet.
// (b) number of frames in a given packet.
// These sizes are encoded as variable length integers

// The packet description entries are either one or two values depending on the format.
// There are three possibilities
// (1)
// If the format has variable bytes per packets (desc.mBytesPerPacket == 0) and constant frames per packet
// (desc.mFramesPerPacket != 0) then the packet table contains single entries representing the bytes in a given packet
// (2)
// If the format is a constant bit rate (desc.mBytesPerPacket != 0) but variable frames per packet
// (desc.mFramesPerPacket == 0) then the packet table entries contains single entries 
// representing the number of frames in a given packet
// (3)
// If the format has variable frames per packet (asbd.mFramesPerPacket == 0) and variable bytes per packet
// (desc.mBytesPerPacket == 0) then the packet table entries are a duple of two values. The first value
// is the number of bytes in a given packet, the second value is the number of frames in a given packet

struct CAFPacketTableHeader
{
        SInt64  mNumberPackets;
        SInt64  mNumberValidFrames;
        SInt32  mPrimingFrames;
        SInt32  mRemainderFrames;
		
		UInt8   mPacketDescriptions[1]; // this is a variable length array of mNumberPackets elements
} ATTRIBUTE_PACKED;
typedef struct CAFPacketTableHeader CAFPacketTableHeader;

struct CAFDataChunk
{
		UInt32 mEditCount;
		UInt8 mData[1]; // this is a variable length data field based off the size of the data chunk
} ATTRIBUTE_PACKED;
typedef struct CAFDataChunk CAFDataChunk;

// markers types
CF_ENUM(UInt32) {
	kCAFMarkerType_Generic					= 0,
	kCAFMarkerType_ProgramStart				= 'pbeg',
	kCAFMarkerType_ProgramEnd				= 'pend',
	kCAFMarkerType_TrackStart				= 'tbeg',
	kCAFMarkerType_TrackEnd					= 'tend',
	kCAFMarkerType_Index					= 'indx',
	kCAFMarkerType_RegionStart				= 'rbeg',
	kCAFMarkerType_RegionEnd				= 'rend',
	kCAFMarkerType_RegionSyncPoint			= 'rsyc',
	kCAFMarkerType_SelectionStart			= 'sbeg',
	kCAFMarkerType_SelectionEnd				= 'send',
	kCAFMarkerType_EditSourceBegin			= 'cbeg',
	kCAFMarkerType_EditSourceEnd			= 'cend',
	kCAFMarkerType_EditDestinationBegin		= 'dbeg',
	kCAFMarkerType_EditDestinationEnd		= 'dend',
	kCAFMarkerType_SustainLoopStart			= 'slbg',
	kCAFMarkerType_SustainLoopEnd			= 'slen',
	kCAFMarkerType_ReleaseLoopStart			= 'rlbg',
	kCAFMarkerType_ReleaseLoopEnd			= 'rlen',
	kCAFMarkerType_SavedPlayPosition		= 'sply',
	kCAFMarkerType_Tempo					= 'tmpo',
	kCAFMarkerType_TimeSignature			= 'tsig',
	kCAFMarkerType_KeySignature				= 'ksig'
};

CF_ENUM(UInt32)
{
    kCAF_SMPTE_TimeTypeNone		 = 0,
    kCAF_SMPTE_TimeType24        = 1,
    kCAF_SMPTE_TimeType25        = 2,
    kCAF_SMPTE_TimeType30Drop    = 3,
    kCAF_SMPTE_TimeType30        = 4,
    kCAF_SMPTE_TimeType2997      = 5,
    kCAF_SMPTE_TimeType2997Drop  = 6,
    kCAF_SMPTE_TimeType60        = 7,
    kCAF_SMPTE_TimeType5994      = 8,
    kCAF_SMPTE_TimeType60Drop    = 9,
    kCAF_SMPTE_TimeType5994Drop  = 10,
    kCAF_SMPTE_TimeType50        = 11,
    kCAF_SMPTE_TimeType2398      = 12
};

struct CAF_SMPTE_Time
{
	SInt8 mHours;
	SInt8 mMinutes;
	SInt8 mSeconds;
	SInt8 mFrames;
	UInt32 mSubFrameSampleOffset;
} ATTRIBUTE_PACKED;
typedef struct CAF_SMPTE_Time CAF_SMPTE_Time;

struct CAFMarker
{
        UInt32               mType;
        Float64              mFramePosition;
        UInt32               mMarkerID;
        CAF_SMPTE_Time       mSMPTETime;
        UInt32               mChannel;
} ATTRIBUTE_PACKED;
typedef struct CAFMarker CAFMarker;

struct CAFMarkerChunk
{
        UInt32          mSMPTE_TimeType;
        UInt32          mNumberMarkers;
        CAFMarker       mMarkers[1]; // this is a variable length array of mNumberMarkers elements
} ATTRIBUTE_PACKED;
typedef struct CAFMarkerChunk CAFMarkerChunk;

#define kCAFMarkerChunkHdrSize		offsetof(CAFMarkerChunk, mMarkers)

typedef CF_OPTIONS(UInt32, CAFRegionFlags) {
	kCAFRegionFlag_LoopEnable = 1,
	kCAFRegionFlag_PlayForward = 2,
	kCAFRegionFlag_PlayBackward = 4
};

struct CAFRegion
{
        UInt32          mRegionID;               
        CAFRegionFlags  mFlags;
        UInt32          mNumberMarkers;
        CAFMarker       mMarkers[1]; // this is a variable length array of mNumberMarkers elements
} ATTRIBUTE_PACKED;
typedef struct CAFRegion CAFRegion;

/* because AudioFileRegions are variable length, you cannot access them as an array. Use NextAudioFileRegion to walk the list. */
#define NextCAFRegion(inCAFRegionPtr) \
        ((CAFRegion*)((char*)(inCAFRegionPtr) + offsetof(CAFRegion, mMarkers) + ((inCAFRegionPtr)->mNumberMarkers)*sizeof(CAFMarker)))


struct CAFRegionChunk
{
        UInt32          mSMPTE_TimeType;
        UInt32          mNumberRegions;
        CAFRegion       mRegions[1];  // this is a variable length array of mNumberRegions elements
} ATTRIBUTE_PACKED;
typedef struct CAFRegionChunk CAFRegionChunk;

#define kCAFRegionChunkHdrSize		offsetof(CAFRegionChunk, mRegions)

struct CAFInstrumentChunk
{
        Float32         mBaseNote;
        UInt8           mMIDILowNote;
        UInt8           mMIDIHighNote;
        UInt8           mMIDILowVelocity;
        UInt8           mMIDIHighVelocity;
        Float32         mdBGain;
        UInt32          mStartRegionID;               
        UInt32          mSustainRegionID;               
        UInt32          mReleaseRegionID;               
        UInt32          mInstrumentID;
} ATTRIBUTE_PACKED;
typedef struct CAFInstrumentChunk CAFInstrumentChunk;



struct CAFStringID {
        UInt32         mStringID;
        SInt64         mStringStartByteOffset;
} ATTRIBUTE_PACKED;
typedef struct CAFStringID CAFStringID;

struct CAFStrings
{
        UInt32         mNumEntries;
		CAFStringID    mStringsIDs[1]; // this is a variable length array of mNumEntries elements
// this struct is only fictionally described due to the variable length fields
//		UInt8          mStrings[ variable num elements ]; // null terminated UTF8 strings
} ATTRIBUTE_PACKED;
typedef struct CAFStrings CAFStrings;


struct CAFInfoStrings
{
        UInt32		mNumEntries;

// These are only fictionally defined in the struct due to the variable length fields.
//      struct {
//              UInt8   mKey[ variable num elements ];			// null terminated UTF8 string
//              UInt8   mValue[ variable num elements ];		// null terminated UTF8 string
//      } mStrings[ variable num elements ];
} ATTRIBUTE_PACKED;
typedef struct CAFInfoStrings CAFInfoStrings;


struct CAFPositionPeak
{
        Float32       mValue;
        UInt64        mFrameNumber;
} ATTRIBUTE_PACKED;
typedef struct CAFPositionPeak CAFPositionPeak;

struct CAFPeakChunk
{
	UInt32 mEditCount;
	CAFPositionPeak mPeaks[1]; // this is a variable length array of peak elements (calculated from the size of the chunk)
} ATTRIBUTE_PACKED;
typedef struct CAFPeakChunk CAFPeakChunk;


struct CAFOverviewSample
{
        SInt16       mMinValue;
        SInt16       mMaxValue;
} ATTRIBUTE_PACKED;
typedef struct CAFOverviewSample CAFOverviewSample;

struct CAFOverviewChunk
{
        UInt32                   mEditCount;
        UInt32                   mNumFramesPerOVWSample;
        CAFOverviewSample        mData[1]; // data is of variable size, calculated from the sizeo of the chunk.
} ATTRIBUTE_PACKED;
typedef struct CAFOverviewChunk CAFOverviewChunk;

struct CAFUMIDChunk
{
	UInt8 mBytes[64];
} ATTRIBUTE_PACKED;
typedef struct CAFUMIDChunk CAFUMIDChunk;

#if TARGET_OS_WIN32
#pragma pack(pop)
#endif
////////////////////////////////////////////////////////////////////////////////////////////////

#endif // AudioToolbox_CAFFile_h
// ==========  AudioToolbox.framework/Headers/AudioToolbox.h
/*!
	@file		AudioToolbox.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2002-2015 by Apple, Inc., all rights reserved.
	@abstract	Umbrella header for AudioToolbox framework.
*/

#ifndef AudioToolbox_AudioToolbox_h
#define AudioToolbox_AudioToolbox_h

#define AUDIO_TOOLBOX_VERSION 1060

#include <Availability.h>
#include <TargetConditionals.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioToolbox/AudioFile.h>
	#include <AudioToolbox/AudioFileStream.h>
	#include <AudioToolbox/AudioFormat.h>
	#include <AudioToolbox/AudioQueue.h>
	#include <AudioToolbox/AudioServices.h>
	#include <AudioToolbox/AUGraph.h>
	#include <AudioToolbox/AudioConverter.h>
	#include <AudioToolbox/ExtendedAudioFile.h>
	#include <AudioToolbox/MusicPlayer.h>
	#include <AudioToolbox/CAFFile.h>
	#if !TARGET_OS_IPHONE
		#include <AudioToolbox/AudioFileComponent.h>
		#include <AudioToolbox/AudioUnitUtilities.h>
		#include <AudioToolbox/AUMIDIController.h>
		#include <AudioToolbox/CoreAudioClock.h>
	#endif
#else
	#include <AudioConverter.h>
	#include <AudioFile.h>
	#include <AudioFileComponent.h>
	#include <AudioFileStream.h>
	#include <AudioFormat.h>
	#include <AudioQueue.h>
	#include <AudioUnitUtilities.h>
	#include <AUGraph.h>
	#include <AUMIDIController.h>
	#include <CAFFile.h>
	#include <CoreAudioClock.h>
	#include <ExtendedAudioFile.h>
	#include <MusicPlayer.h>
	#include <AudioServices.h>
#endif

#include <stdio.h>

CF_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
extern "C"
{
#endif

// prints out the internal state of an object to stdio
extern void CAShow (void* inObject) 
											__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

// prints out the internal state of an object to the supplied FILE
extern void CAShowFile (void* inObject, FILE* inFile) 
											__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);
	
#if !TARGET_OS_IPHONE
// this will return the name of a sound bank from a sound bank file
// the name should be released by the caller
struct FSRef;
extern OSStatus GetNameFromSoundBank (const struct FSRef *inSoundBankRef, CFStringRef __nullable * __nonnull outName)
											__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);
#endif

/*!
    @function		CopyNameFromSoundBank
	 
    @discussion		This will return the name of a sound bank from a DLS or SF2 bank.
					The name should be released by the caller.

    @param			inURL
						The URL for the sound bank.
    @param			outName
						A pointer to a CFStringRef to be created and returned by the function.
    @result			returns noErr if successful.
*/

extern OSStatus
CopyNameFromSoundBank (CFURLRef inURL, CFStringRef __nullable * __nonnull outName)
											__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_7_0);

/*!
    @function		CopyInstrumentInfoFromSoundBank
	 
    @discussion		This will return a CFArray of CFDictionaries, one per instrument found in the DLS or SF2 bank.
					Each dictionary will contain four items accessed via CFStringRef versions of the keys kInstrumentInfoKey_MSB,
 					kInstrumentInfoKey_LSB, kInstrumentInfoKey_Program, and kInstrumentInfoKey_Name.
 						MSB: An NSNumberRef for the most-significant byte of the bank number.  GM melodic banks will return 120 (0x78).
 							 GM percussion banks will return 121 (0x79).  Custom banks will return their literal value.
						LSB: An NSNumberRef for the least-significant byte of the bank number.  All GM banks will return
							 the bank variation number (0-127).
 						Program Number: An NSNumberRef for the program number (0-127) of an instrument within a particular bank.
 						Name: A CFStringRef containing the name of the instrument.
 
					Using these MSB, LSB, and Program values will guarantee that the correct instrument is loaded by the DLS synth
					or Sampler Audio Unit.
					The CFArray should be released by the caller.

    @param			inURL
	 					The URL for the sound bank.
    @param			outInstrumentInfo
						A pointer to a CFArrayRef to be created and returned by the function.
    @result			returns noErr if successful.
*/

extern OSStatus CopyInstrumentInfoFromSoundBank (CFURLRef inURL, CFArrayRef __nullable * __nonnull outInstrumentInfo)
														__OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_7_0);
	
#define kInstrumentInfoKey_Name		"name"
#define kInstrumentInfoKey_MSB		"MSB"
#define kInstrumentInfoKey_LSB		"LSB"
#define kInstrumentInfoKey_Program	"program"

#if defined(__cplusplus)
}
#endif

CF_ASSUME_NONNULL_END

#endif // AudioToolbox_AudioToolbox_h
// ==========  AudioToolbox.framework/Headers/AudioFile.h
/*!
	@file		AudioFile.h
	@framework	AudioToolbox.framework
	@copyright	(c) 1985-2015 by Apple, Inc., all rights reserved.
	@abstract	API's to read and write audio files in the filesystem or in memory.
*/

#ifndef AudioToolbox_AudioFile_h
#define AudioToolbox_AudioFile_h

//=============================================================================
//	Includes
//=============================================================================

#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreAudio/CoreAudioTypes.h>
	#include <CoreFoundation/CoreFoundation.h>
#else
	#include <CoreAudioTypes.h>
	#include <CoreFoundation.h>
#endif

CF_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
extern "C"
{
#endif

/*!
	@typedef	AudioFileTypeID
	@abstract	Identifier for an audio file type.
*/
typedef UInt32 AudioFileTypeID;

/*!
    @enum Audio File Types
    @abstract   Constants for the built-in audio file types.
    @discussion These constants are used to indicate the type of file to be written, or as a hint to
					what type of file to expect from data provided.
    @constant   kAudioFileAIFFType
					Audio Interchange File Format (AIFF)
    @constant   kAudioFileAIFCType
					Audio Interchange File Format Compressed (AIFF-C)
    @constant   kAudioFileWAVEType
					Microsoft WAVE
    @constant   kAudioFileSoundDesigner2Type
					Sound Designer II
    @constant   kAudioFileNextType
					NeXT / Sun
    @constant   kAudioFileMP3Type
					MPEG Audio Layer 3 (.mp3)
    @constant   kAudioFileMP2Type
					MPEG Audio Layer 2 (.mp2)
    @constant   kAudioFileMP1Type
					MPEG Audio Layer 1 (.mp1)
    @constant   kAudioFileAC3Type
					AC-3
    @constant   kAudioFileAAC_ADTSType
					Advanced Audio Coding (AAC) Audio Data Transport Stream (ADTS)
    @constant   kAudioFileMPEG4Type
    @constant   kAudioFileM4AType
    @constant   kAudioFileM4BType
    @constant   kAudioFileCAFType
					CoreAudio File Format.
*/
CF_ENUM(AudioFileTypeID) {
        kAudioFileAIFFType				= 'AIFF',
        kAudioFileAIFCType				= 'AIFC',
        kAudioFileWAVEType				= 'WAVE',
        kAudioFileSoundDesigner2Type	= 'Sd2f',
        kAudioFileNextType				= 'NeXT',
        kAudioFileMP3Type				= 'MPG3',	// mpeg layer 3
        kAudioFileMP2Type				= 'MPG2',	// mpeg layer 2
        kAudioFileMP1Type				= 'MPG1',	// mpeg layer 1
		kAudioFileAC3Type				= 'ac-3',
        kAudioFileAAC_ADTSType			= 'adts',
        kAudioFileMPEG4Type             = 'mp4f',
        kAudioFileM4AType               = 'm4af',
        kAudioFileM4BType               = 'm4bf',
		kAudioFileCAFType				= 'caff',
		kAudioFile3GPType				= '3gpp',
		kAudioFile3GP2Type				= '3gp2',		
		kAudioFileAMRType				= 'amrf'		
};

/*!
    @enum AudioFile error codes
    @abstract   These are the error codes returned from the AudioFile API.
    @constant   kAudioFileUnspecifiedError 
		An unspecified error has occurred.
    @constant   kAudioFileUnsupportedFileTypeError 
		The file type is not supported.
    @constant   kAudioFileUnsupportedDataFormatError 
		The data format is not supported by this file type.
    @constant   kAudioFileUnsupportedPropertyError 
		The property is not supported.
    @constant   kAudioFileBadPropertySizeError 
		The size of the property data was not correct.
    @constant   kAudioFilePermissionsError 
		The operation violated the file permissions. For example, trying to write to a file opened with kAudioFileReadPermission.
    @constant   kAudioFileNotOptimizedError 
		There are chunks following the audio data chunk that prevent extending the audio data chunk. 
		The file must be optimized in order to write more audio data.
    @constant   kAudioFileInvalidChunkError 
		The chunk does not exist in the file or is not supported by the file. 
    @constant   kAudioFileDoesNotAllow64BitDataSizeError 
		The a file offset was too large for the file type. AIFF and WAVE have a 32 bit file size limit. 
    @constant   kAudioFileInvalidPacketOffsetError 
		A packet offset was past the end of the file, or not at the end of the file when writing a VBR format, 
		or a corrupt packet size was read when building the packet table. 
    @constant   kAudioFileInvalidFileError 
		The file is malformed, or otherwise not a valid instance of an audio file of its type. 
    @constant   kAudioFileOperationNotSupportedError 
		The operation cannot be performed. For example, setting kAudioFilePropertyAudioDataByteCount to increase 
		the size of the audio data in a file is not a supported operation. Write the data instead.
    @constant   kAudioFileNotOpenError 
		The file is closed.
	@constant   kAudioFileEndOfFileError 
		End of file.
	@constant   kAudioFilePositionError 
		Invalid file position.
	@constant   kAudioFileFileNotFoundError 
		File not found.
 */
CF_ENUM(OSStatus) {
        kAudioFileUnspecifiedError						= 'wht?',		// 0x7768743F, 2003334207
        kAudioFileUnsupportedFileTypeError 				= 'typ?',		// 0x7479703F, 1954115647
        kAudioFileUnsupportedDataFormatError 			= 'fmt?',		// 0x666D743F, 1718449215
        kAudioFileUnsupportedPropertyError 				= 'pty?',		// 0x7074793F, 1886681407
        kAudioFileBadPropertySizeError 					= '!siz',		// 0x2173697A,  561211770
        kAudioFilePermissionsError	 					= 'prm?',		// 0x70726D3F, 1886547263
        kAudioFileNotOptimizedError						= 'optm',		// 0x6F70746D, 1869640813
        // file format specific error codes
        kAudioFileInvalidChunkError						= 'chk?',		// 0x63686B3F, 1667787583
        kAudioFileDoesNotAllow64BitDataSizeError		= 'off?',		// 0x6F66663F, 1868981823
        kAudioFileInvalidPacketOffsetError				= 'pck?',		// 0x70636B3F, 1885563711
        kAudioFileInvalidFileError						= 'dta?',		// 0x6474613F, 1685348671
		kAudioFileOperationNotSupportedError			= 0x6F703F3F, 	// 'op??', integer used because of trigraph
		// general file error codes
		kAudioFileNotOpenError							= -38,
		kAudioFileEndOfFileError						= -39,
		kAudioFilePositionError							= -40,
		kAudioFileFileNotFoundError						= -43
};

/*!
    @enum AudioFileFlags
    @abstract   These are flags that can be used with the CreateURL API call
    @constant   kAudioFileFlags_EraseFile 
		If set, then the CreateURL call will erase the contents of an existing file
		If not set, then the CreateURL call will fail if the file already exists
    @constant   kAudioFileFlags_DontPageAlignAudioData 
		Normally, newly created and optimized files will have padding added in order to page align 
		the data to 4KB boundaries. This makes reading the data more efficient. 
		When disk space is a concern, this flag can be set so that the padding will not be added.
*/
typedef CF_OPTIONS(UInt32, AudioFileFlags) {
	kAudioFileFlags_EraseFile = 1,
	kAudioFileFlags_DontPageAlignAudioData = 2
};

typedef CF_ENUM(SInt8, AudioFilePermissions) {
	kAudioFileReadPermission      = 0x01,
	kAudioFileWritePermission     = 0x02,
	kAudioFileReadWritePermission = 0x03
};

//=============================================================================
//	Types specific to the Audio File API
//=============================================================================

/*!
    @typedef	AudioFileID
    @abstract   An opaque reference to an AudioFile object.
*/
typedef	struct OpaqueAudioFileID	*AudioFileID;
/*!
    @typedef	AudioFilePropertyID
    @abstract   A constant for an AudioFile property.
*/
typedef UInt32			AudioFilePropertyID;

/*!
    @enum		AudioFileLoopDirection
    @abstract   These constants describe the playback direction of a looped segment of a file.
    @constant   kAudioFileLoopDirection_NoLooping
					The segment is not looped.
    @constant   kAudioFileLoopDirection_Forward
					play segment forward.
    @constant   kAudioFileLoopDirection_Backward
					play segment backward.
    @constant   kAudioFileLoopDirection_ForwardAndBackward
					play segment forward and backward.
*/
CF_ENUM(UInt32) {
	kAudioFileLoopDirection_NoLooping = 0,
	kAudioFileLoopDirection_Forward = 1,
	kAudioFileLoopDirection_ForwardAndBackward = 2,
	kAudioFileLoopDirection_Backward = 3
};

//=============================================================================
//	Markers, Regions
//=============================================================================


/*!
    @struct		AudioFile_SMPTE_Time
    @abstract   A struct for describing a SMPTE time.
    @field      mHours						The hours.
    @field      mMinutes					The minutes.
    @field      mSeconds					The seconds.
    @field      mFrames						The frames.
    @field      mSubFrameSampleOffset		The sample offset within a frame.
*/
struct AudioFile_SMPTE_Time
{
	SInt8 mHours;
	UInt8 mMinutes;
	UInt8 mSeconds;
	UInt8 mFrames;
	UInt32 mSubFrameSampleOffset;
};
typedef struct AudioFile_SMPTE_Time AudioFile_SMPTE_Time;


/*!
    @enum		AudioFileMarkerType
    @abstract   constants for types of markers within a file. Used in the mType field of AudioFileMarker.
    @constant   kAudioFileMarkerType_Generic		A generic marker. See CAFFile.h for marker types specific to CAF files.
*/
CF_ENUM(UInt32) {
	kAudioFileMarkerType_Generic			= 0,
};


/*!
    @struct		AudioFileMarker
    @abstract   A marker annotates a position in an audio file with additional information.
    @discussion (description)
    @field      mFramePosition	The frame in the file counting from the start of the audio data.
    @field      mName			The name of this marker.
    @field      mMarkerID		A unique ID for this marker.
    @field      mSMPTETime		The SMPTE time for this marker.
    @field      mType			The marker type.
    @field      mReserved		A reserved field. Set to zero.
    @field      mChannel		The channel number that the marker refers to. Set to zero if marker applies to all channels.
*/
struct AudioFileMarker
{
	Float64 mFramePosition;
	
	CFStringRef	__nullable	mName;
	SInt32					mMarkerID;

	AudioFile_SMPTE_Time	mSMPTETime;
	UInt32					mType;
	UInt16					mReserved;
	UInt16					mChannel;
};
typedef struct AudioFileMarker AudioFileMarker;

/*!
    @struct		AudioFileMarkerList
    @abstract   A list of AudioFileMarker.
    @field      mSMPTE_TimeType
					This defines the SMPTE timing scheme used in the marker list. See CAFFile.h for the values used here.
    @field      mNumberMarkers
					The number of markers in the mMarkers list.
    @field      mMarkers
					A list of AudioFileMarker.
*/
struct AudioFileMarkerList
{
	UInt32				mSMPTE_TimeType;
	UInt32				mNumberMarkers;
	AudioFileMarker		mMarkers[1]; // this is a variable length array of mNumberMarkers elements
};
typedef struct AudioFileMarkerList AudioFileMarkerList;

/*!
    @function	NumBytesToNumAudioFileMarkers
    @abstract   Converts a size in bytes to the number of AudioFileMarkers that can be contained in that number of bytes.
    @discussion This can be used for the kAudioFilePropertyMarkerList property when calculating the number of 
				markers that will be returned. 
    @param      inNumBytes 
					a number of bytes.
    @result     the number of AudioFileMarkers that can be contained in that number of bytes.
*/
#ifdef CF_INLINE
CF_INLINE size_t NumBytesToNumAudioFileMarkers(size_t inNumBytes)
{
	return (inNumBytes<offsetof(AudioFileMarkerList, mMarkers[0]) ? 0 : (inNumBytes - offsetof(AudioFileMarkerList, mMarkers[0])) / sizeof(AudioFileMarker));
}
#else
#define NumBytesToNumAudioFileMarkers(inNumBytes) \
	((inNumBytes)<offsetof(AudioFileMarkerList, mMarkers[0])?0:((inNumBytes) - offsetof(AudioFileMarkerList, mMarkers[0])) / sizeof(AudioFileMarker))
#endif

/*!
    @function	NumAudioFileMarkersToNumBytes
    @abstract   Converts a number of AudioFileMarkers to a size in bytes.
    @discussion This can be used for the kAudioFilePropertyMarkerList property when calculating the size required to 
				contain a number of AudioFileMarkers. 
    @param      inNumMarkers 
					a number of AudioFileMarkers.
    @result     the size in bytes required to contain that number of AudioFileMarkers.
*/
#ifdef CF_INLINE
CF_INLINE size_t NumAudioFileMarkersToNumBytes(size_t inNumMarkers)
{
	return (offsetof(AudioFileMarkerList, mMarkers) + (inNumMarkers) * sizeof(AudioFileMarker));
}
#else
#define NumAudioFileMarkersToNumBytes(inNumMarkers) \
	(offsetof(AudioFileMarkerList, mMarkers) + (inNumMarkers) * sizeof(AudioFileMarker))
#endif

/*!
    @enum		AudioFileRegionFlags
    @abstract   These are flags for an AudioFileRegion that specify a playback direction.
    @discussion One or multiple of these flags can be set. For example, if both kAudioFileRegionFlag_LoopEnable and 
				kAudioFileRegionFlag_PlayForward are set, then the region will play as a forward loop. If only 
				kAudioFileRegionFlag_PlayForward is set, then the region will be played forward once.
    @constant   kAudioFileRegionFlag_LoopEnable
					If this flag is set, the region will be looped. One or both of the following must also be set.
    @constant   kAudioFileRegionFlag_PlayForward
					If this flag is set, the region will be played forward.
    @constant   kAudioFileRegionFlag_PlayBackward
					If this flag is set, the region will be played backward.
*/
typedef CF_OPTIONS(UInt32, AudioFileRegionFlags) {
	kAudioFileRegionFlag_LoopEnable = 1,
	kAudioFileRegionFlag_PlayForward = 2,
	kAudioFileRegionFlag_PlayBackward = 4
};

/*!
    @struct		AudioFileRegion
    @abstract   An AudioFileRegion specifies a segment of audio data.
    @discussion Generally a region consists of at least two markers marking the beginning and end of the segment.
				There may also be other markers defining other meta information such as sync point.
    @field      mRegionID 
					each region must have a unique ID.
    @field      mName 
					The name of the region.
    @field      mFlags 
					AudioFileRegionFlags.
    @field      mNumberMarkers 
					The number of markers in the mMarkers array.
    @field      mMarkers 
					A variable length array of AudioFileMarkers.
*/
struct AudioFileRegion
{
	UInt32					mRegionID;
	CFStringRef				mName;
	AudioFileRegionFlags	mFlags;
	UInt32					mNumberMarkers;
	AudioFileMarker			mMarkers[1]; // this is a variable length array of mNumberMarkers elements
};
typedef struct AudioFileRegion AudioFileRegion;


/*!
    @struct		AudioFileRegionList
    @abstract   A list of the AudioFileRegions in a file.
    @discussion This is the struct used by the kAudioFilePropertyRegionList property.
    @field      mSMPTE_TimeType
					This defines the SMPTE timing scheme used in the file. See CAFFile.h for the values used here.
    @field      mNumberRegions
					The number of regions in the mRegions list.
    @field      mRegions
					A list of AudioFileRegions. Note that AudioFileMarkers are variable length, so this list cannot 
					be accessed as an array. Use the NextAudioFileRegion macro for traversing the list instead.
*/
struct AudioFileRegionList
{
	UInt32				mSMPTE_TimeType;
	UInt32				mNumberRegions;
	AudioFileRegion		mRegions[1]; // this is a variable length array of mNumberRegions elements
};
typedef struct AudioFileRegionList AudioFileRegionList;

/*!
    @function	NextAudioFileRegion
    @abstract   convenience macro for traversing the region list.
    @discussion because AudioFileRegions are variable length, you cannot access them as an array. Use NextAudioFileRegion 
				to walk the list.
    @param      inAFRegionPtr 
					a pointer to the current region.
    @result     a pointer to the region after the current region. This does not protect you from walking off the end of the list, 
				so obey mNumberRegions.
*/
#ifdef CF_INLINE
CF_INLINE AudioFileRegion *NextAudioFileRegion(const AudioFileRegion *inAFRegionPtr)
{
	return ((AudioFileRegion*)((char*)inAFRegionPtr + offsetof(AudioFileRegion, mMarkers) + (inAFRegionPtr->mNumberMarkers)*sizeof(AudioFileMarker)));
}
#else
#define NextAudioFileRegion(inAFRegionPtr) \
        ((AudioFileRegion*)((char*)(inAFRegionPtr) + offsetof(AudioFileRegion, mMarkers) + ((inAFRegionPtr)->mNumberMarkers)*sizeof(AudioFileMarker)))
#endif

/*!
    @struct		AudioFramePacketTranslation
    @abstract   used for properties kAudioFilePropertyPacketToFrame and kAudioFilePropertyFrameToPacket
    @discussion See description of kAudioFilePropertyPacketToFrame and kAudioFilePropertyFrameToPacket
    @field      mFrame		a frame number.
    @field      mPacket		a packet number.
    @field      mFrameOffsetInPacket		a frame offset in a packet.
*/
struct AudioFramePacketTranslation
{
	SInt64 mFrame;
	SInt64 mPacket;
	UInt32 mFrameOffsetInPacket;
};
typedef struct AudioFramePacketTranslation AudioFramePacketTranslation;


/*!
    @enum		AudioBytePacketTranslation Flags
	
    @abstract   flags for the AudioBytePacketTranslation mFlags field
    @discussion		There is currently only one flag.
					
    @constant   kBytePacketTranslationFlag_IsEstimate
					If the set then the result value is an estimate.
*/
typedef CF_OPTIONS(UInt32, AudioBytePacketTranslationFlags) {
	kBytePacketTranslationFlag_IsEstimate = 1
};

/*!
    @struct		AudioBytePacketTranslation
    @abstract   used for properties kAudioFileByteToPacket and kAudioFilePacketToByte
    @discussion See description of kAudioFileByteToPacket and kAudioFilePacketToByte
    @field      mByte		a byte number.
    @field      mPacket		a packet number.
    @field      mByteOffsetInPacket		a byte offset in a packet.
    @field      mFlags		if kBytePacketTranslationFlag_IsEstimate is set, then the value is an estimate.
*/
struct AudioBytePacketTranslation
{
	SInt64 mByte;
	SInt64 mPacket;
	UInt32 mByteOffsetInPacket;
	AudioBytePacketTranslationFlags mFlags;
};
typedef struct AudioBytePacketTranslation AudioBytePacketTranslation;


/*!
    @struct		AudioFilePacketTableInfo
    @abstract   This contains information about the number of valid frames in a file and where they begin and end.
    @discussion	Some data formats may have packets whose contents are not completely valid, but represent priming or remainder 
				frames that are not meant to be played. For example a file with 100 packets of AAC is nominally 1024 * 100 = 102400 frames
				of data. However the first 2112 frames of that may be priming frames and there may be some 
				number of remainder frames added to pad out to a full packet of 1024 frames. The priming and remainder frames should be 
				discarded. The total number of packets in the file times the frames per packet (or counting each packet's frames 
				individually for a variable frames per packet format) minus mPrimingFrames, minus mRemainderFrames, should 
				equal mNumberValidFrames.
    @field      mNumberValidFrames the number of valid frames in the file.
    @field      mPrimingFrames the number of invalid frames at the beginning of the file.
    @field      mRemainderFrames the number of invalid frames at the end of the file.
*/
struct AudioFilePacketTableInfo
{
        SInt64  mNumberValidFrames;
        SInt32  mPrimingFrames;
        SInt32  mRemainderFrames;
};
typedef struct AudioFilePacketTableInfo AudioFilePacketTableInfo;

//=============================================================================
//	Info String Keys
//=============================================================================

// Get key values from the InfoDictionary by making CFStrings from the following constants

#define kAFInfoDictionary_Artist                        "artist"
#define kAFInfoDictionary_Album							"album"
#define kAFInfoDictionary_Tempo							"tempo"
#define kAFInfoDictionary_KeySignature					"key signature"
#define kAFInfoDictionary_TimeSignature					"time signature"
#define kAFInfoDictionary_TrackNumber                   "track number"
#define kAFInfoDictionary_Year							"year"
#define kAFInfoDictionary_Composer						"composer"
#define kAFInfoDictionary_Lyricist						"lyricist"
#define kAFInfoDictionary_Genre							"genre"
#define kAFInfoDictionary_Title							"title"
#define kAFInfoDictionary_RecordedDate					"recorded date"
#define kAFInfoDictionary_Comments						"comments"
#define kAFInfoDictionary_Copyright						"copyright"
#define kAFInfoDictionary_SourceEncoder					"source encoder"
#define kAFInfoDictionary_EncodingApplication           "encoding application"
#define kAFInfoDictionary_NominalBitRate                "nominal bit rate"
#define kAFInfoDictionary_ChannelLayout					"channel layout"
#define kAFInfoDictionary_ApproximateDurationInSeconds  "approximate duration in seconds"
#define kAFInfoDictionary_SourceBitDepth				"source bit depth"
#define kAFInfoDictionary_ISRC							"ISRC"					// International Standard Recording Code
#define kAFInfoDictionary_SubTitle						"subtitle"

//=============================================================================
//	Routines
//=============================================================================

/*!
    @function	AudioFileCreateWithURL
    @abstract   creates a new audio file (or initialises an existing file)
    @discussion	creates a new (or initialises an existing) audio file specified by the URL.
					Upon success, an AudioFileID is returned which can be used for subsequent calls 
					to the AudioFile APIs.
    @param inFileRef		an CFURLRef fully specifying the path of the file to create/initialise
    @param inFileType		an AudioFileTypeID indicating the type of audio file to create.
    @param inFormat			an AudioStreamBasicDescription describing the data format that will be
							added to the audio file.
    @param inFlags			relevant flags for creating/opening the file. 
								if kAudioFileFlags_EraseFile is set, it will erase an existing file
								 if not set, then the Create call will fail if the URL is an existing file
    @param outAudioFile		if successful, an AudioFileID that can be used for subsequent AudioFile calls.
    @result					returns noErr if successful.
*/
extern OSStatus	
AudioFileCreateWithURL (CFURLRef						inFileRef,
                    AudioFileTypeID						inFileType,
                    const AudioStreamBasicDescription	*inFormat,
                    AudioFileFlags						inFlags,
                    AudioFileID	__nullable * __nonnull	outAudioFile)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @function				AudioFileOpenURL
    @abstract				Open an existing audio file.
    @discussion				Open an existing audio file for reading or reading and writing.
    @param inFileRef		the CFURLRef of an existing audio file.
    @param inPermissions	use the permission constants
    @param inFileTypeHint	For files which have no filename extension and whose type cannot be easily or
							uniquely determined from the data (ADTS,AC3), this hint can be used to indicate the file type. 
							Otherwise you can pass zero for this. The hint is only used on OS versions 10.3.1 or greater.
							For OS versions prior to that, opening files of the above description will fail.
    @param outAudioFile		upon success, an AudioFileID that can be used for subsequent
							AudioFile calls.
    @result					returns noErr if successful.
*/
extern OSStatus	
AudioFileOpenURL (	CFURLRef							inFileRef,
					AudioFilePermissions				inPermissions,
					AudioFileTypeID						inFileTypeHint,
					AudioFileID	__nullable * __nonnull	outAudioFile)					__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
    @typedef	AudioFile_ReadProc
    @abstract   A callback for reading data. used with AudioFileOpenWithCallbacks or AudioFileInitializeWithCallbacks.
    @discussion a function that will be called when AudioFile needs to read data.
    @param      inClientData	A pointer to the client data as set in the inClientData parameter to AudioFileXXXWithCallbacks.
    @param      inPosition		An offset into the data from which to read.
    @param      requestCount	The number of bytes to read.
    @param      buffer			The buffer in which to put the data read.
    @param      actualCount		The callback should set this to the number of bytes successfully read.
    @result						The callback should return noErr on success, or an appropriate error code on failure.
*/
typedef OSStatus (*AudioFile_ReadProc)(
								void *		inClientData,
								SInt64		inPosition, 
								UInt32		requestCount,
								void *		buffer, 
								UInt32 *	actualCount);

/*!
    @typedef	AudioFile_WriteProc
    @abstract   A callback for writing data. used with AudioFileOpenWithCallbacks or AudioFileInitializeWithCallbacks.
    @discussion a function that will be called when AudioFile needs to write data.
    @param      inClientData	A pointer to the client data as set in the inClientData parameter to AudioFileXXXWithCallbacks.
    @param      inPosition		An offset into the data from which to read.
    @param      requestCount	The number of bytes to write.
    @param      buffer			The buffer containing the data to write.
    @param      actualCount		The callback should set this to the number of bytes successfully written.
    @result						The callback should return noErr on success, or an appropriate error code on failure.
*/
typedef OSStatus (*AudioFile_WriteProc)(
								void * 		inClientData,
								SInt64		inPosition, 
								UInt32		requestCount, 
								const void *buffer, 
								UInt32    * actualCount);
								
/*!
    @typedef	AudioFile_GetSizeProc
    @abstract   A callback for getting the size of the file data. used with AudioFileOpenWithCallbacks or AudioFileInitializeWithCallbacks.
    @discussion a function that will be called when AudioFile needs to determine the size of the file data. This size is for all of the 
				data in the file, not just the audio data.
    @param      inClientData	A pointer to the client data as set in the inClientData parameter to AudioFileXXXWithCallbacks.
    @result						The callback should return the size of the data.
*/
typedef SInt64 (*AudioFile_GetSizeProc)(
								void * 		inClientData);

/*!
    @typedef	AudioFile_SetSizeProc
    @abstract   A callback for setting the size of the file data. used with AudioFileOpenWithCallbacks or AudioFileInitializeWithCallbacks.
    @discussion a function that will be called when AudioFile needs to set the size of the file data. This size is for all of the 
				data in the file, not just the audio data. This will only be called if the file is written to.
    @param      inClientData	A pointer to the client data as set in the inClientData parameter to AudioFileXXXWithCallbacks.
    @result						The callback should return the size of the data.
*/
typedef OSStatus (*AudioFile_SetSizeProc)(
								void *		inClientData,
								SInt64		inSize);

/*!
    @function	AudioFileInitializeWithCallbacks
    @abstract   Wipe clean an existing file. You provide callbacks that the AudioFile API
				will use to get the data.
    @param inClientData		a constant that will be passed to your callbacks.
	@param inReadFunc		a function that will be called when AudioFile needs to read data.
	@param inWriteFunc		a function that will be called when AudioFile needs to write data.
	@param inGetSizeFunc	a function that will be called when AudioFile needs to know the file size.
	@param inSetSizeFunc	a function that will be called when AudioFile needs to set the file size.
	
    @param inFileType 		an AudioFileTypeID indicating the type of audio file to which to initialize the file. 
    @param inFormat 		an AudioStreamBasicDescription describing the data format that will be
							added to the audio file.
    @param inFlags			flags for creating/opening the file. Currently zero.
    @param outAudioFile		upon success, an AudioFileID that can be used for subsequent
							AudioFile calls.
    @result					returns noErr if successful.
*/
extern OSStatus	
AudioFileInitializeWithCallbacks (	
						void *								inClientData, 
						AudioFile_ReadProc					inReadFunc, 
						AudioFile_WriteProc					inWriteFunc, 
						AudioFile_GetSizeProc				inGetSizeFunc,
						AudioFile_SetSizeProc				inSetSizeFunc,
                        AudioFileTypeID						inFileType,
                        const AudioStreamBasicDescription	*inFormat,
                        AudioFileFlags						inFlags,
                        AudioFileID	__nullable * __nonnull	outAudioFile)	__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_2_0);


/*!
    @function	AudioFileOpenWithCallbacks
    @abstract   Open an existing file. You provide callbacks that the AudioFile API
				will use to get the data.
    @param inClientData					a constant that will be passed to your callbacks.
	@param inReadFunc					a function that will be called when AudioFile needs to read data.
	@param inWriteFunc					a function that will be called when AudioFile needs to write data.
	@param inGetSizeFunc				a function that will be called when AudioFile needs to know the total file size.
	@param inSetSizeFunc				a function that will be called when AudioFile needs to set the file size.
	
    @param inFileTypeHint	For files which have no filename extension and whose type cannot be easily or
							uniquely determined from the data (ADTS,AC3), this hint can be used to indicate the file type. 
							Otherwise you can pass zero for this. The hint is only used on OS versions 10.3.1 or greater.
							For OS versions prior to that, opening files of the above description will fail.
    @param outAudioFile		upon success, an AudioFileID that can be used for subsequent
							AudioFile calls.
    @result					returns noErr if successful.
*/
extern OSStatus	
AudioFileOpenWithCallbacks (
				void *								inClientData,
				AudioFile_ReadProc					inReadFunc,
				AudioFile_WriteProc __nullable		inWriteFunc,
				AudioFile_GetSizeProc				inGetSizeFunc,
				AudioFile_SetSizeProc __nullable	inSetSizeFunc,
                AudioFileTypeID						inFileTypeHint,
                AudioFileID	__nullable * __nonnull	outAudioFile)				__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_2_0);
				

/*!
    @function	AudioFileClose
    @abstract   Close an existing audio file.
    @param      inAudioFile		an AudioFileID.
    @result						returns noErr if successful.
*/
extern OSStatus
AudioFileClose	(AudioFileID		inAudioFile)							__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

/*!
    @function	AudioFileOptimize
    @abstract   Move the audio data to the end of the file and other internal optimizations of the file structure.
	@discussion			Optimize the file so additional audio data can be appended to 
                        the existing data. Generally, this will place the audio data at 
                        the end of the file so additional writes can be placed to the 
                        file end. This can be a potentially expensive and time-consuming operation 
                        and should not be used during time critical operations. There is 
                        a kAudioFilePropertyIsOptimized property for checking on the optimized state 
                        of the file.
    @param      inAudioFile		an AudioFileID.
    @result						returns noErr if successful.
*/
extern OSStatus	
AudioFileOptimize (AudioFileID  	inAudioFile)							__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

/*!
    @function	AudioFileReadBytes
    @abstract   Read bytes of audio data from the audio file. 
				
    @discussion				Returns kAudioFileEndOfFileError when read encounters end of file.
    @param inAudioFile		an AudioFileID.
    @param inUseCache 		true if it is desired to cache the data upon read, else false
    @param inStartingByte	the byte offset of the audio data desired to be returned
    @param ioNumBytes 		on input, the number of bytes to read, on output, the number of
							bytes actually read.
    @param outBuffer 		outBuffer should be a void * to user allocated memory large enough for the requested bytes. 
    @result					returns noErr if successful.
*/
extern OSStatus	
AudioFileReadBytes (	AudioFileID  	inAudioFile,
                        Boolean			inUseCache,
                        SInt64			inStartingByte, 
                        UInt32			*ioNumBytes, 
                        void			*outBuffer)							__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

/*!
    @function				AudioFileWriteBytes
    @abstract				Write bytes of audio data to the audio file.
    @param inAudioFile		an AudioFileID.
    @param inUseCache 		true if it is desired to cache the data upon write, else false
    @param inStartingByte	the byte offset where the audio data should be written
    @param ioNumBytes 		on input, the number of bytes to write, on output, the number of
							bytes actually written.
    @param inBuffer 		inBuffer should be a void * containing the bytes to be written 
    @result					returns noErr if successful.
*/
extern OSStatus	
AudioFileWriteBytes (	AudioFileID  	inAudioFile,  
                        Boolean			inUseCache,
                        SInt64			inStartingByte, 
                        UInt32			*ioNumBytes, 
                        const void		*inBuffer)							__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

/*!
    @function	AudioFileReadPacketData
    @abstract   Read packets of audio data from the audio file.
    @discussion AudioFileReadPacketData reads as many of the requested number of packets
				as will fit in the buffer size given by ioNumPackets.
				Unlike the deprecated AudioFileReadPackets, ioNumPackets must be initialized.
				If the byte size of the number packets requested is 
				less than the buffer size, ioNumBytes will be reduced.
				If the buffer is too small for the number of packets 
				requested, ioNumPackets and ioNumBytes will be reduced 
				to the number of packets that can be accommodated and their byte size.
				Returns kAudioFileEndOfFileError when read encounters end of file.
				For all uncompressed formats, packets == frames.

    @param inAudioFile				an AudioFileID.
    @param inUseCache 				true if it is desired to cache the data upon read, else false
    @param ioNumBytes				on input the size of outBuffer in bytes. 
									on output, the number of bytes actually returned.
    @param outPacketDescriptions 	An array of packet descriptions describing the packets being returned. 
									The size of the array must be greater or equal to the number of packets requested. 
									On return the packet description will be filled out with the packet offsets and sizes.
									Packet descriptions are ignored for CBR data.   
    @param inStartingPacket 		The packet index of the first packet desired to be returned
    @param ioNumPackets 			on input, the number of packets to read, on output, the number of
									packets actually read.
    @param outBuffer 				outBuffer should be a pointer to user allocated memory.
    @result							returns noErr if successful.
*/
extern OSStatus	
AudioFileReadPacketData (	AudioFileID  					inAudioFile, 
                       		Boolean							inUseCache,
                       		UInt32 *						ioNumBytes,
                       		AudioStreamPacketDescription * __nullable outPacketDescriptions,
                       		SInt64							inStartingPacket, 
                       		UInt32 * 						ioNumPackets,
                       		void * __nullable				outBuffer)			__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_2);

/*!
    @function	AudioFileReadPackets
    @abstract   Read packets of audio data from the audio file.
    @discussion AudioFileReadPackets is DEPRECATED. Use AudioFileReadPacketData instead.
				READ THE HEADER DOC FOR AudioFileReadPacketData. It is not a drop-in replacement.
				In particular, for AudioFileReadPacketData ioNumBytes must be initialized to the buffer size.
				AudioFileReadPackets assumes you have allocated your buffer to ioNumPackets times the maximum packet size.
				For many compressed formats this will only use a portion of the buffer since the ratio of the maximum 
				packet size to the typical packet size can be large. Use AudioFileReadPacketData instead.
	
    @param inAudioFile				an AudioFileID.
    @param inUseCache 				true if it is desired to cache the data upon read, else false
    @param outNumBytes				on output, the number of bytes actually returned
    @param outPacketDescriptions 	on output, an array of packet descriptions describing
									the packets being returned. NULL may be passed for this
									parameter. Nothing will be returned for linear pcm data.   
    @param inStartingPacket 		the packet index of the first packet desired to be returned
    @param ioNumPackets 			on input, the number of packets to read, on output, the number of
									packets actually read.
    @param outBuffer 				outBuffer should be a pointer to user allocated memory of size: 
									number of packets requested times file's maximum (or upper bound on)
									packet size.
    @result							returns noErr if successful.
*/
extern OSStatus	
AudioFileReadPackets (	AudioFileID  					inAudioFile, 
                        Boolean							inUseCache,
                        UInt32 *						outNumBytes,
                        AudioStreamPacketDescription * __nullable outPacketDescriptions,
                        SInt64							inStartingPacket, 
                        UInt32 * 						ioNumPackets,
                        void * __nullable				outBuffer)			__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_10, __IPHONE_2_0,__IPHONE_8_0);


/*!
    @function	AudioFileWritePackets
    @abstract   Write packets of audio data to the audio file.
    @discussion For all uncompressed formats, packets == frames.
    @param inAudioFile				an AudioFileID.
    @param inUseCache 				true if it is desired to cache the data upon write, else false
    @param inNumBytes				the number of bytes being provided for write
    @param inPacketDescriptions 	an array of packet descriptions describing the packets being 
									provided. Not all formats require packet descriptions to be 
									provided. NULL may be passed if no descriptions are required.   
    @param inStartingPacket 		the packet index of where the first packet provided should be placed.
    @param ioNumPackets 			on input, the number of packets to write, on output, the number of
									packets actually written.
    @param inBuffer 				a void * to user allocated memory containing the packets to write.
    @result							returns noErr if successful.
*/
extern OSStatus	
AudioFileWritePackets (	AudioFileID							inAudioFile,  
                        Boolean								inUseCache,
                        UInt32								inNumBytes,
                        const AudioStreamPacketDescription * __nullable inPacketDescriptions,
                        SInt64								inStartingPacket, 
                        UInt32								*ioNumPackets, 
                        const void							*inBuffer)			__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);


/*!
    @function	AudioFileCountUserData
    @abstract   Get the number of user data items with a certain ID in the file
    @discussion		"User Data" refers to chunks in AIFF, CAF and WAVE files, or resources 
					in Sound Designer II files, and possibly other things in other files.
					For simplicity, referred to below as "chunks".
    @param      inAudioFile			an AudioFileID.
    @param      inUserDataID		the four char code of the chunk.
    @param      outNumberItems		on output, if successful, number of chunks of this type in the file.
    @result							returns noErr if successful.
*/
extern OSStatus	
AudioFileCountUserData (	AudioFileID			inAudioFile, 
							UInt32				inUserDataID, 
							UInt32				*outNumberItems)			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_0);

/*!
    @function	AudioFileGetUserDataSize
    @abstract   Get the size of user data in a file
    @param      inAudioFile			an AudioFileID.
    @param      inUserDataID		the four char code of the chunk.
    @param      inIndex				an index specifying which chunk if there are more than one.
    @param      outUserDataSize		on output, if successful, the size of the user data chunk.
    @result							returns noErr if successful.
*/
extern OSStatus	
AudioFileGetUserDataSize (	AudioFileID			inAudioFile, 
							UInt32				inUserDataID, 
							UInt32				inIndex, 
							UInt32				*outUserDataSize)			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_0);

/*!
    @function	AudioFileGetUserData
    @abstract   Get the data of a chunk in a file.
    @param      inAudioFile			an AudioFileID.
    @param      inUserDataID		the four char code of the chunk.
    @param      inIndex				an index specifying which chunk if there are more than one.
	@param		ioUserDataSize		the size of the buffer on input, size of bytes copied to buffer on output 
    @param      outUserData			a pointer to a buffer in which to copy the chunk data.
    @result							returns noErr if successful.
*/
extern OSStatus	
AudioFileGetUserData (	AudioFileID			inAudioFile, 
						UInt32				inUserDataID, 
						UInt32				inIndex, 
						UInt32				*ioUserDataSize, 
						void				*outUserData)					__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_0);

/*!
    @function	AudioFileSetUserData
    @abstract   Set the data of a chunk in a file.
    @param      inAudioFile			an AudioFileID.
    @param      inUserDataID		the four char code of the chunk.
    @param      inIndex				an index specifying which chunk if there are more than one.
	@param		inUserDataSize		on input the size of the data to copy, on output, size of bytes copied from the buffer  
    @param      inUserData			a pointer to a buffer from which to copy the chunk data 
									(only the contents of the chunk, not including the chunk header).
    @result							returns noErr if successful.
*/
extern OSStatus	
AudioFileSetUserData ( AudioFileID			inAudioFile, 
						UInt32				inUserDataID, 
						UInt32				inIndex, 
						UInt32				inUserDataSize, 
						const void			*inUserData)					__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_0);


/*!
    @function	AudioFileRemoveUserData
    @abstract   Remove a user chunk in a file.
    @param      inAudioFile			an AudioFileID.
    @param      inUserDataID		the four char code of the chunk.
    @param      inIndex				an index specifying which chunk if there are more than one.
    @result							returns noErr if successful.
*/

extern OSStatus	
AudioFileRemoveUserData ( AudioFileID		inAudioFile, 
						UInt32				inUserDataID, 
						UInt32				inIndex)						__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);


//=============================================================================
//	Audio File Properties
//=============================================================================

/*!
    @enum		Audio File Properties
    @abstract   constants for AudioFile get/set property calls
    @constant   kAudioFilePropertyFileFormat 
					An AudioFileTypeID that identifies the format of the file
    @constant   kAudioFilePropertyDataFormat 
					An AudioStreamBasicDescription describing the format of the audio data
    @constant   kAudioFilePropertyFormatList 
					In order to support formats such as AAC SBR where an encoded data stream can be decoded to 
					multiple destination formats, this property returns an array of AudioFormatListItems (see AudioFormat.h) of those formats.
					The default behavior is to return the an AudioFormatListItem that has the same AudioStreamBasicDescription 
					that kAudioFilePropertyDataFormat returns.
    @constant   kAudioFilePropertyIsOptimized 
					A UInt32 indicating whether an Audio File has been optimized.
					Optimized means it is ready to start having sound data written to it. 
					A value of 0 indicates the file needs to be optimized.
					A value of 1 indicates the file is currently optimized.
    @constant   kAudioFilePropertyMagicCookieData 
					A void * pointing to memory set up by the caller.
					Some file types require that a magic cookie be provided before packets can be written
					to the file, so this property should be set before calling 
					AudioFileWriteBytes()/AudioFileWritePackets() if a magic cookie exists.
    @constant   kAudioFilePropertyAudioDataByteCount 
					a UInt64 that indicates the number of bytes of audio data contained in the file
    @constant   kAudioFilePropertyAudioDataPacketCount 
					a UInt64 that indicates the number of packets of audio data contained in the file
    @constant   kAudioFilePropertyMaximumPacketSize 
					a UInt32 that indicates the maximum size of a packet for the data contained in the file
    @constant   kAudioFilePropertyDataOffset 
					a SInt64 that indicates the byte offset in the file of the audio data.
    @constant   kAudioFilePropertyChannelLayout 
					An AudioChannelLayout struct.
    @constant   kAudioFilePropertyDeferSizeUpdates 
					A UInt32. If 1, then updating the files sizes in the header is not done for every write, 
					but deferred until the file is read, optimized or closed. This is more efficient, but less safe
					since, if the application crashes before the size is updated, the file may not be readable.
					The default value is one, it doesn't update the header.
    @constant   kAudioFilePropertyDataFormatName 
					This is deprecated. Use kAudioFormatProperty_FormatName in AudioFormat.h instead.
    @constant   kAudioFilePropertyMarkerList 
					access the list of markers defined in the file. returns an AudioFileMarkerList.
					The CFStringRefs in the returned structs must be released by the client.
					(available in 10.2.4 and later)
    @constant   kAudioFilePropertyRegionList 
					access the list of regions defined in the file. returns an Array of AudioFileRegions.
					The CFStringRefs in the returned structs must be released by the client.
					(available in 10.2.4 and later)
    @constant   kAudioFilePropertyPacketToFrame 
					pass a AudioFramePacketTranslation with mPacket filled out and get mFrame back. mFrameOffsetInPacket is ignored.
    @constant   kAudioFilePropertyFrameToPacket 
					pass a AudioFramePacketTranslation with mFrame filled out and get mPacket and mFrameOffsetInPacket back.
					
	@constant	kAudioFilePropertyPacketToByte
					pass an AudioBytePacketTranslation struct with mPacket filled out and get mByte back.
					mByteOffsetInPacket is ignored. If the mByte value is an estimate then 
					kBytePacketTranslationFlag_IsEstimate will be set in the mFlags field.
	@constant	kAudioFilePropertyByteToPacket
					pass an AudioBytePacketTranslation struct with mByte filled out and get mPacket and
					mByteOffsetInPacket back. If the mPacket value is an estimate then 
					kBytePacketTranslationFlag_IsEstimate will be set in the mFlags field.
					
    @constant   kAudioFilePropertyChunkIDs 
					returns an array of OSType four char codes for each kind of chunk in the file.
    @constant   kAudioFilePropertyInfoDictionary 
					returns a CFDictionary filled with information about the data contained in the file. 
					See dictionary key constants already defined for info string types. 
					AudioFileComponents are free to add keys to the dictionaries that they return for this property...
					caller is responsible for releasing the CFObject
    @constant   kAudioFilePropertyPacketTableInfo 
					Gets or sets an AudioFilePacketTableInfo struct for the file types that support it.
					When setting, the sum of mNumberValidFrames, mPrimingFrames and mRemainderFrames must be the same as the total
					number of frames in all packets. If not you will get a kAudio_ParamError. The best way to ensure this is to get the value of
					the property and make sure the sum of the three values you set has the same sum as the three values you got.
	@constant	kAudioFilePropertyPacketSizeUpperBound
					a UInt32 for the theoretical maximum packet size in the file (without actually scanning
					the whole file to find the largest packet, as may happen with kAudioFilePropertyMaximumPacketSize).
	@constant	kAudioFilePropertyReserveDuration
					The value is a Float64 of the duration in seconds of data that is expected to be written.
					Setting this property before any data has been written reserves space in the file header for a packet table 
					and/or other information so that it can appear before the audio data. Otherwise the packet table may get written at the 
					end of the file, preventing the file from being streamable.
	@constant	kAudioFilePropertyEstimatedDuration
					The value is a Float64 representing an estimated duration in seconds. If duration can be calculated without scanning the entire file,
					or all the audio data packets have been scanned, the value will accurately reflect the duration of the audio data. 
	@constant	kAudioFilePropertyBitRate
					Returns the bit rate for the audio data as a UInt32. For some formats this will be approximate.
	@constant	kAudioFilePropertyID3Tag
					A void * pointing to memory set up by the caller to contain a fully formatted ID3 tag (get/set v2.2, v2.3, or v2.4, v1 get only).
					The ID3 tag is not manipulated in anyway either for read or write. 
					When setting, this property must be called before calling AudioFileWritePackets.
	@constant	kAudioFilePropertySourceBitDepth
					For encoded data this property returns the bit depth of the source as an SInt32, if known.
					The bit depth is expressed as a negative number if the source was floating point, e.g. -32 for float, -64 for double.
	@constant	kAudioFilePropertyAlbumArtwork
					returns a CFDataRef filled with the Album Art. Data will formatted as either JFIF (JPEG) or PNG (PNG) 
					The caller is responsible for releasing the CFObject.
    @constant	kAudioFilePropertyAudioTrackCount
                    a UInt32 that indicates the number of audio tracks contained in the file. (get property only)
    @constant	kAudioFilePropertyUseAudioTrack
                    a UInt32 that indicates the number of audio tracks contained in the file. (set property only)
 */
CF_ENUM(AudioFilePropertyID)
{
	kAudioFilePropertyFileFormat			=	'ffmt',
	kAudioFilePropertyDataFormat			=	'dfmt',
	kAudioFilePropertyIsOptimized			=	'optm',
	kAudioFilePropertyMagicCookieData		=	'mgic',
	kAudioFilePropertyAudioDataByteCount	=	'bcnt',
	kAudioFilePropertyAudioDataPacketCount	=	'pcnt',
	kAudioFilePropertyMaximumPacketSize		=	'psze',
	kAudioFilePropertyDataOffset			=	'doff',
	kAudioFilePropertyChannelLayout			=	'cmap',
	kAudioFilePropertyDeferSizeUpdates		=	'dszu',
	kAudioFilePropertyDataFormatName		=	'fnme',
	kAudioFilePropertyMarkerList			=	'mkls',
	kAudioFilePropertyRegionList			=	'rgls',
	kAudioFilePropertyPacketToFrame			=	'pkfr',
	kAudioFilePropertyFrameToPacket			=	'frpk',
	kAudioFilePropertyPacketToByte			=	'pkby',
	kAudioFilePropertyByteToPacket			=	'bypk',
	kAudioFilePropertyChunkIDs				=	'chid',
	kAudioFilePropertyInfoDictionary        =	'info',
	kAudioFilePropertyPacketTableInfo		=	'pnfo',
	kAudioFilePropertyFormatList			=	'flst',
	kAudioFilePropertyPacketSizeUpperBound  =	'pkub',
	kAudioFilePropertyReserveDuration		=	'rsrv',
	kAudioFilePropertyEstimatedDuration		=	'edur',
	kAudioFilePropertyBitRate				=	'brat',
	kAudioFilePropertyID3Tag				=	'id3t',
	kAudioFilePropertySourceBitDepth		=	'sbtd',
	kAudioFilePropertyAlbumArtwork			=	'aart',
    kAudioFilePropertyAudioTrackCount       =   'atct',
	kAudioFilePropertyUseAudioTrack			=	'uatk'
};


/*!
    @function	AudioFileGetPropertyInfo
    @abstract   Get information about the size of a property of an AudioFile  and whether it can be set.
    @param      inAudioFile			an AudioFileID.
    @param      inPropertyID		an AudioFileProperty constant.
    @param      outDataSize			the size in bytes of the current value of the property. In order to get the property value, 
									you will need a buffer of this size.
    @param      isWritable			will be set to 1 if writable, or 0 if read only.
    @result							returns noErr if successful.
*/
extern OSStatus
AudioFileGetPropertyInfo(		AudioFileID				inAudioFile,
                                AudioFilePropertyID		inPropertyID,
                                UInt32 * __nullable		outDataSize,
                                UInt32 * __nullable		isWritable)			__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);
                                
/*!
    @function	AudioFileGetProperty
    @abstract   Copies the value for a property of an AudioFile into a buffer.
    @param      inAudioFile			an AudioFileID.
    @param      inPropertyID		an AudioFileProperty constant.
    @param      ioDataSize			on input the size of the outPropertyData buffer. On output the number of bytes written to the buffer.
    @param      outPropertyData		the buffer in which to write the property data.
    @result							returns noErr if successful.
*/
extern OSStatus
AudioFileGetProperty(	AudioFileID				inAudioFile,
                        AudioFilePropertyID		inPropertyID,
                        UInt32					*ioDataSize,
                        void					*outPropertyData)			__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);
                        
/*!
    @function	AudioFileSetProperty
    @abstract   Sets the value for a property of an AudioFile .
    @param      inAudioFile			an AudioFileID.
    @param      inPropertyID		an AudioFileProperty constant.
    @param      inDataSize			the size of the property data.
    @param      inPropertyData		the buffer containing the property data.
    @result							returns noErr if successful.
*/
extern OSStatus
AudioFileSetProperty(	AudioFileID				inAudioFile,
                        AudioFilePropertyID		inPropertyID,
                        UInt32					inDataSize,
                        const void				*inPropertyData)			__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);



//=============================================================================
//	Audio File Global Info Properties
//=============================================================================

/*!
    @enum		Audio File Global Info Properties
    @abstract   constants for AudioFileGetGlobalInfo properties
    @constant   kAudioFileGlobalInfo_ReadableTypes
					No specifier needed. Must be set to NULL.
					Returns an array of UInt32 containing the file types 
					(i.e. AIFF, WAVE, etc) that can be opened for reading.
    @constant   kAudioFileGlobalInfo_WritableTypes
					No specifier needed. Must be set to NULL.
					Returns an array of UInt32 containing the file types 
					(i.e. AIFF, WAVE, etc) that can be opened for writing.
    @constant   kAudioFileGlobalInfo_FileTypeName
					Specifier is a pointer to a AudioFileTypeID containing a file type.
					Returns a CFString containing the name for the file type. 
    @constant   kAudioFileGlobalInfo_AvailableFormatIDs
					Specifier is a pointer to a AudioFileTypeID containing a file type.
					Returns a array of format IDs for formats that can be read. 
    @constant   kAudioFileGlobalInfo_AvailableStreamDescriptionsForFormat
					Specifier is a pointer to a AudioFileTypeAndFormatID struct defined below.
					Returns an array of AudioStreamBasicDescriptions which have all of the 
					formats for a particular file type and format ID. The AudioStreamBasicDescriptions
					have the following fields filled in: mFormatID, mFormatFlags, mBitsPerChannel
					writing new files.
					
					
    @constant   kAudioFileGlobalInfo_AllExtensions
					No specifier needed. Must be set to NULL.
					Returns a CFArray of CFStrings containing all file extensions 
					that are recognized. The array be used when creating an NSOpenPanel.

    @constant   kAudioFileGlobalInfo_AllHFSTypeCodes
					No specifier needed. Must be set to NULL.
					Returns an array of HFSTypeCode's containing all HFSTypeCodes
					that are recognized.

    @constant   kAudioFileGlobalInfo_AllUTIs
					No specifier needed. Must be set to NULL.
					Returns a CFArray of CFString of all Universal Type Identifiers
					that are recognized by AudioFile. 
					The caller is responsible for releasing the CFArray.

    @constant   kAudioFileGlobalInfo_AllMIMETypes
					No specifier needed. Must be set to NULL.
					Returns a CFArray of CFString of all MIME types
					that are recognized by AudioFile. 
					The caller is responsible for releasing the CFArray.


    @constant   kAudioFileGlobalInfo_ExtensionsForType
					Specifier is a pointer to a AudioFileTypeID containing a file type.
					Returns a CFArray of CFStrings containing the file extensions 
					that are recognized for this file type. 

    @constant   kAudioFileGlobalInfo_HFSTypeCodesForType
					Specifier is a pointer to an AudioFileTypeID.
					Returns an array of HFSTypeCodes corresponding to that file type.
					The first type in the array is the preferred one for use when

    @constant   kAudioFileGlobalInfo_UTIsForType
					Specifier is a pointer to an AudioFileTypeID.
					Returns a CFArray of CFString of all Universal Type Identifiers
					that are recognized by the file type. 
					The caller is responsible for releasing the CFArray.

    @constant   kAudioFileGlobalInfo_MIMETypesForType
					Specifier is a pointer to an AudioFileTypeID.
					Returns a CFArray of CFString of all MIME types
					that are recognized by the file type. 
					The caller is responsible for releasing the CFArray.

	these are inverses of the above:

    @constant   kAudioFileGlobalInfo_TypesForExtension
					Specifier is a CFStringRef containing a file extension.
					Returns an array of all AudioFileTypeIDs that support the extension. 
	
    @constant   kAudioFileGlobalInfo_TypesForHFSTypeCode
					Specifier is an HFSTypeCode.
					Returns an array of all AudioFileTypeIDs that support the HFSTypeCode. 

    @constant   kAudioFileGlobalInfo_TypesForUTI
					Specifier is a CFStringRef containing a Universal Type Identifier.
					Returns an array of all AudioFileTypeIDs that support the UTI. 

    @constant   kAudioFileGlobalInfo_TypesForMIMEType
					Specifier is a CFStringRef containing a MIME Type.
					Returns an array of all AudioFileTypeIDs that support the MIME type. 

*/
CF_ENUM(AudioFilePropertyID)
{
	kAudioFileGlobalInfo_ReadableTypes							= 'afrf',
	kAudioFileGlobalInfo_WritableTypes							= 'afwf',
	kAudioFileGlobalInfo_FileTypeName							= 'ftnm',
	kAudioFileGlobalInfo_AvailableStreamDescriptionsForFormat	= 'sdid',
	kAudioFileGlobalInfo_AvailableFormatIDs						= 'fmid',

	kAudioFileGlobalInfo_AllExtensions							= 'alxt',
	kAudioFileGlobalInfo_AllHFSTypeCodes						= 'ahfs',
	kAudioFileGlobalInfo_AllUTIs								= 'auti',
	kAudioFileGlobalInfo_AllMIMETypes							= 'amim',

	kAudioFileGlobalInfo_ExtensionsForType						= 'fext',
	kAudioFileGlobalInfo_HFSTypeCodesForType					= 'fhfs',
	kAudioFileGlobalInfo_UTIsForType							= 'futi',
	kAudioFileGlobalInfo_MIMETypesForType						= 'fmim',
	
	kAudioFileGlobalInfo_TypesForMIMEType						= 'tmim',
	kAudioFileGlobalInfo_TypesForUTI							= 'tuti',
	kAudioFileGlobalInfo_TypesForHFSTypeCode					= 'thfs',
	kAudioFileGlobalInfo_TypesForExtension						= 'text'
};


/*!
    @struct		AudioFileTypeAndFormatID
    @abstract   This is used as a specifier for kAudioFileGlobalInfo_AvailableStreamDescriptions
    @discussion This struct is used to specify a desired audio file type and data format ID  so
				that a list of stream descriptions of available formats can be obtained.
    @field      mFileType
					a four char code for the file type such as kAudioFileAIFFType, kAudioFileCAFType, etc.
    @field      mFormatID
					a four char code for the format ID such as kAudioFormatLinearPCM, kAudioFormatMPEG4AAC, etc.
*/
struct AudioFileTypeAndFormatID
{
	AudioFileTypeID  mFileType;
	UInt32			mFormatID;
};
typedef struct AudioFileTypeAndFormatID AudioFileTypeAndFormatID;


/*!
    @function	AudioFileGetGlobalInfoSize
    @abstract   Get the size of a global property.
    @param      inPropertyID		an AudioFileGlobalInfo property constant.
    @param      inSpecifierSize		The size of the specifier data.
    @param      inSpecifier			A specifier is a buffer of data used as an input argument to some of the global info properties.
    @param      outDataSize			the size in bytes of the current value of the property. In order to get the property value, 
									you will need a buffer of this size.
    @result							returns noErr if successful.
*/
extern OSStatus
AudioFileGetGlobalInfoSize(		AudioFilePropertyID		inPropertyID,
                                UInt32					inSpecifierSize,
                                void * __nullable		inSpecifier,
                                UInt32					*outDataSize)		__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_2_0);
                                
/*!
    @function	AudioFileGetGlobalInfo
    @abstract   Copies the value for a global property into a buffer.
    @param      inPropertyID		an AudioFileGlobalInfo property constant.
    @param      inSpecifierSize		The size of the specifier data.
    @param      inSpecifier			A specifier is a buffer of data used as an input argument to some of the global info properties.
    @param      ioDataSize			on input the size of the outPropertyData buffer. On output the number of bytes written to the buffer.
    @param      outPropertyData		the buffer in which to write the property data.
    @result							returns noErr if successful.
*/
extern OSStatus
AudioFileGetGlobalInfo(			AudioFilePropertyID		inPropertyID,
								UInt32					inSpecifierSize,
                                void * __nullable		inSpecifier,
                    		    UInt32					*ioDataSize,
                    		    void					*outPropertyData)	__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_2_0);

#pragma mark - Deprecated
	
#if !TARGET_OS_IPHONE
struct FSRef;
/*!
    @function	AudioFileCreate
    @abstract   creates a new audio file
    @discussion	creates a new audio file located in the parent directory 
                      provided. Upon success, an AudioFileID is returned which can
                      be used for subsequent calls to the AudioFile APIs.
    @param inParentRef		an FSRef to the directory where  the new file should be created.
    @param inFileName		a CFStringRef containing the name of the file to be created.
    @param inFileType		an AudioFileTypeID indicating the type of audio file to create.
    @param inFormat			an AudioStreamBasicDescription describing the data format that will be
							added to the audio file.
    @param inFlags			relevant flags for creating/opening the file. 
    @param outNewFileRef	if successful, the FSRef of the newly created file.
    @param outAudioFile		if successful, an AudioFileID that can be used for subsequent AudioFile calls.
    @result					returns noErr if successful.
	@deprecated				in Mac OS X 10.6, see AudioFileCreateWithURL
*/
extern OSStatus	
AudioFileCreate (	const struct FSRef					*inParentRef, 
                    CFStringRef							inFileName,
                    AudioFileTypeID						inFileType,
                    const AudioStreamBasicDescription	*inFormat,
                    AudioFileFlags						inFlags,
                    struct FSRef						*outNewFileRef,
                    AudioFileID	__nullable * __nonnull	outAudioFile)		__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);

/*!
    @function				AudioFileInitialize
    @abstract				Write over an existing audio file.
    @discussion				Use AudioFileInitialize to wipe clean an existing audio file
							and prepare it to be populated with new data.
    @param inFileRef		the FSRef of an existing audio file.
    @param inFileType		an AudioFileTypeID indicating the type of audio file to initialize the file to. 
    @param inFormat			an AudioStreamBasicDescription describing the data format that will be
							added to the audio file.
    @param inFlags			flags for creating/opening the file. Currently zero.
    @param outAudioFile		upon success, an AudioFileID that can be used for subsequent
							AudioFile calls.
    @result					returns noErr if successful.
	@deprecated				in Mac OS X 10.6, see AudioFileCreateWithURL
*/
extern OSStatus	
AudioFileInitialize (	const struct FSRef					*inFileRef,
                        AudioFileTypeID						inFileType,
                        const AudioStreamBasicDescription	*inFormat,
                        AudioFileFlags						inFlags,
                        AudioFileID	__nullable * __nonnull	outAudioFile)	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);

/*!
    @function				AudioFileOpen
    @abstract				Open an existing audio file.
    @discussion				Open an existing audio file for reading or reading and writing.
    @param inFileRef		the FSRef of an existing audio file.
    @param inPermissions	use the permission constants
    @param inFileTypeHint	For files which have no filename extension and whose type cannot be easily or
							uniquely determined from the data (ADTS,AC3), this hint can be used to indicate the file type. 
							Otherwise you can pass zero for this. The hint is only used on OS versions 10.3.1 or greater.
							For OS versions prior to that, opening files of the above description will fail.
    @param outAudioFile		upon success, an AudioFileID that can be used for subsequent
							AudioFile calls.
    @result					returns noErr if successful.
	@deprecated				in Mac OS X 10.6, see AudioFileOpenURL
*/
extern OSStatus	
AudioFileOpen (	const struct FSRef		*inFileRef,
                AudioFilePermissions	inPermissions,
                AudioFileTypeID			inFileTypeHint,
                AudioFileID	__nullable * __nonnull	outAudioFile)			__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);

#endif
	
#if defined(__cplusplus)
}
#endif

CF_ASSUME_NONNULL_END

#endif // AudioToolbox_AudioFile_h
// ==========  AudioToolbox.framework/Headers/AudioSession.h
/*==================================================================================================
 File:       AudioToolbox/AudioSession.h
 
 Contains:   API for audio session services.
 
 Copyright:  (c) 2006 - 2013 by Apple, Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 ==================================================================================================*/
#if !defined(__AudioSession_h__)
#define __AudioSession_h__

//==================================================================================================

/*!
 @header AudioSession
 This header describes the API for audio session services.
 Note: As of iOS 7, this entire API has been deprecated in favor of AVAudioSession, part of the AVFoundation framework.
 */

//==================================================================================================
#pragma mark    Includes

#include <TargetConditionals.h>
#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
#if !TARGET_OS_IPHONE
#include <CoreAudio/AudioHardware.h>
#endif
#include <CoreFoundation/CoreFoundation.h>
#else
#include <AudioHardware.h>
#include <CFRunLoop.h>
#include <CFString.h>
#include <CFURL.h>
#endif

//==================================================================================================

#if defined(__cplusplus)
extern "C"
{
#endif

	//==================================================================================================
#pragma mark -
#pragma mark    AudioSession Error Constants
	
	/*!
	 @enum           AudioSession error codes
	 @abstract       Error codes returned from the AudioSession portion of the API.
	 @constant       kAudioSessionNoError
	 No error has occurred
	 @constant       kAudioSessionNotInitialized 
	 This error is returned when the AudioSessionInitialize function
	 was not called prior to calling any other AudioSession function.
	 @constant       kAudioSessionAlreadyInitialized 
	 This error is returned when you call AudioSessionInitialize more than once.
	 @constant       kAudioSessionInitializationError 
	 This error indicates an AudioSession initialization error.
	 @constant       kAudioSessionUnsupportedPropertyError 
	 The property is not supported.  This error code can also be used to 
	 indicate that a bad property value was passed in a SetProperty call,
	 an attempt was made to set a read-only property, an attempt was made to
	 read a write-only property, an attempt was made to read a property that
	 is only available by way of a property listener, or an attempt was made 
	 to set a listener on a property for which listeners are not supported.
	 @constant       kAudioSessionBadPropertySizeError 
	 The size of the property data was not correct.
	 @constant       kAudioSessionNotActiveError 
	 The operation failed because the AudioSession is not active.
	 Calling AudioSessionSetActive(true) first will fix this error in most cases.
	 @constant       kAudioSessionNoCategorySet
	 The requested operation failed because it requires that the session have had an
	 audio category explicitly set, and none was set.
	 @constant       kAudioSessionIncompatibleCategory
	 The requested operation failed because the AudioSession has an incompatible
	 category (e.g. attempting to play or record when the category is AudioProcessing) or
	 the session is not active.
	 @constant       kAudioSessionUnspecifiedError
	 An audio session unspecified error has occurred.
	 */
	enum
	{
		kAudioSessionNoError                                =  0,
		kAudioSessionNotInitialized                         = '!ini',
		kAudioSessionAlreadyInitialized                     = 'init',
		kAudioSessionInitializationError                    = 'ini?',
		kAudioSessionUnsupportedPropertyError               = 'pty?',
		kAudioSessionBadPropertySizeError                   = '!siz',
		kAudioSessionNotActiveError                         = '!act',
		kAudioServicesNoHardwareError                       = 'nohw',
		kAudioSessionNoCategorySet                          = '?cat',
		kAudioSessionIncompatibleCategory                   = '!cat',
		kAudioSessionUnspecifiedError                       = 'what'
	};
	
	//==================================================================================================
#pragma mark -
#pragma mark    AudioSession Types
	
	/*!
	 @typedef        AudioSessionPropertyID
	 @abstract       Type used for specifying an AudioSession property.
	 */
	typedef UInt32      AudioSessionPropertyID;
	
	//==================================================================================================
#pragma mark -
#pragma mark    AudioSession Interruption States
	
	/*!
	 @enum           AudioSession interruptions states
	 @abstract       These are used with the AudioSessionInterruptionListener to indicate
	 if an interruption begins or ends.
	 @constant       kAudioSessionBeginInterruption
	 Indicates that this AudioSession has just been interrupted.
	 @constant       kAudioSessionEndInterruption 
	 Indicates the end of an interruption.
	 */
	enum {
		kAudioSessionBeginInterruption  = 1,
		kAudioSessionEndInterruption    = 0
	};
	
	//==================================================================================================
#pragma mark -
#pragma mark    AudioSession Audio Categories
	
	/*!
	 @enum           AudioSession audio categories states
	 @abstract       These are used with as values for the kAudioSessionProperty_AudioCategory property
	 to indicate the audio category of the AudioSession.
	 @constant       kAudioSessionCategory_AmbientSound 
	 Use this category for background sounds such as rain, car engine noise, etc.  
	 Mixes with other music.
	 @constant       kAudioSessionCategory_SoloAmbientSound 
	 Use this category for background sounds.  Other music will stop playing.
	 @constant       kAudioSessionCategory_MediaPlayback 
	 Use this category for music tracks.
	 @constant       kAudioSessionCategory_RecordAudio 
	 Use this category when recording audio.
	 @constant       kAudioSessionCategory_PlayAndRecord 
	 Use this category when recording and playing back audio.
	 @constant       kAudioSessionCategory_AudioProcessing
	 Use this category when using a hardware codec or signal processor while
	 not playing or recording audio.
	 */
	enum {
		kAudioSessionCategory_AmbientSound               = 'ambi',
		kAudioSessionCategory_SoloAmbientSound           = 'solo',
		kAudioSessionCategory_MediaPlayback              = 'medi',
		kAudioSessionCategory_RecordAudio                = 'reca',
		kAudioSessionCategory_PlayAndRecord              = 'plar',
		kAudioSessionCategory_AudioProcessing            = 'proc'
	};
	
#pragma mark    AudioSession Audio Category Routing Overrides
	
	/*!
	 @enum           AudioSession audio category routing overrides
	 @abstract       These are used with as values for the kAudioSessionProperty_OverrideAudioRoute property.
	 @constant       kAudioSessionOverrideAudioRoute_None
	 No override.  Return audio routing to the default state for the current audio category.
	 @constant       kAudioSessionOverrideAudioRoute_Speaker 
	 Route audio output to speaker.  Use this override with the kAudioSessionCategory_PlayAndRecord
	 category, which by default routes the output to the receiver.
	 */
	enum {
		kAudioSessionOverrideAudioRoute_None    = 0,
		kAudioSessionOverrideAudioRoute_Speaker = 'spkr'
	};
	
	//==================================================================================================
#pragma mark    AudioSession reason codes for route change
	
	/*!
	 @enum           AudioSession reason codes for route change
	 @abstract       These are codes used when the kAudioSessionProperty_AudioRoute property changes
	 @constant       kAudioSessionRouteChangeReason_Unknown
	 The reason is unknown.
	 @constant       kAudioSessionRouteChangeReason_NewDeviceAvailable
	 A new device became available (e.g. headphones have been plugged in).
	 @constant       kAudioSessionRouteChangeReason_OldDeviceUnavailable
	 The old device became unavailable (e.g. headphones have been unplugged).
	 @constant       kAudioSessionRouteChangeReason_CategoryChange
	 The audio category has changed (e.g. kAudioSessionCategory_MediaPlayback
	 has been changed to kAudioSessionCategory_PlayAndRecord).
	 @constant       kAudioSessionRouteChangeReason_Override
	 The route has been overridden (e.g. category is kAudioSessionCategory_PlayAndRecord
	 and the output has been changed from the receiver, which is the default, to the speaker).
	 @constant       kAudioSessionRouteChangeReason_WakeFromSleep
	 The device woke from sleep.
	 @constant       kAudioSessionRouteChangeReason_NoSuitableRouteForCategory
	 Returned when there is no route for the current category (for instance RecordCategory 
	 but no input device)
	 @constant		 kAudioSessionRouteChangeReason_RouteConfigurationChange
	 Indicates that the set of input and/our output ports has not changed, but some aspect of their 
	 configuration has changed.  For example, a port's selected data source has changed.
	 */
	enum {
		kAudioSessionRouteChangeReason_Unknown = 0,
		kAudioSessionRouteChangeReason_NewDeviceAvailable = 1,
		kAudioSessionRouteChangeReason_OldDeviceUnavailable = 2,
		kAudioSessionRouteChangeReason_CategoryChange = 3,
		kAudioSessionRouteChangeReason_Override = 4,
		kAudioSessionRouteChangeReason_WakeFromSleep = 6,
		kAudioSessionRouteChangeReason_NoSuitableRouteForCategory = 7,
		kAudioSessionRouteChangeReason_RouteConfigurationChange = 8
	};
	
	// see documentation for kAudioSessionProperty_AudioRouteChange
	// Note: the string refers to "OutputDevice" for historical reasons.  Audio routes may contain zero or more inputs and 
	//      zero or more outputs.
#define kAudioSession_AudioRouteChangeKey_Reason    "OutputDeviceDidChange_Reason"
    
	// CFString version of kAudioSession_AudioRouteChangeKey_Reason.  This is more convenient to use than the raw string version.
	// Available in iOS 5.0 or greater          
	extern const CFStringRef kAudioSession_RouteChangeKey_Reason                __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
	
	// CFDictionary keys for kAudioSessionProperty_AudioRouteChange
	// Available in iOS 5.0 or greater      
	extern const CFStringRef   kAudioSession_AudioRouteChangeKey_PreviousRouteDescription  __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
	extern const CFStringRef   kAudioSession_AudioRouteChangeKey_CurrentRouteDescription   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
	
	// CFDictionary keys for kAudioSessionProperty_AudioRouteDescription    
	// Available in iOS 5.0 or greater    
	extern const CFStringRef   kAudioSession_AudioRouteKey_Inputs   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
	extern const CFStringRef   kAudioSession_AudioRouteKey_Outputs  __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
	
	// key(s) for the CFDictionary associated with each entry of the CFArrays returned by kAudioSession_AudioRouteKey_Inputs
	// and kAudioSession_AudioRouteKey_Outputs.  
	// Available in iOS 5.0 or greater        
	extern const CFStringRef   kAudioSession_AudioRouteKey_Type     __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
    
    
	/*!
	 @enum           AudioSession route input types
	 @abstract       These are the strings used with the kAudioSession_AudioRouteKey_Type key for the CFDictionary associated 
	 with kAudioSession_AudioRouteKey_Inputs.
	 Available in iOS 5.0 or greater      
	 @constant       kAudioSessionInputRoute_LineIn
	 A line in input 
	 @constant       kAudioSessionInputRoute_BuiltInMic
	 A built-in microphone input.  (Note that some devices like early iPods do not have this input)
	 @constant       kAudioSessionInputRoute_HeadsetMic
	 A microphone that is part of a headset (combined microphone and headphones)
	 @constant       kAudioSessionInputRoute_BluetoothHFP
	 A microphone that is part of a Bluetooth Hands-Free Profile device
	 @constant       kAudioSessionInputRoute_USBAudio
	 A Universal Serial Bus input
	 */    
	extern const CFStringRef   kAudioSessionInputRoute_LineIn       __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
	extern const CFStringRef   kAudioSessionInputRoute_BuiltInMic   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
	extern const CFStringRef   kAudioSessionInputRoute_HeadsetMic   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
	extern const CFStringRef   kAudioSessionInputRoute_BluetoothHFP __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
	extern const CFStringRef   kAudioSessionInputRoute_USBAudio     __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
    
	/*!
	 @enum           AudioSession route output types
	 @abstract       These are strings used with the kAudioSession_AudioRouteKey_Type key for the CFDictionary associated 
	 with kAudioSession_AudioRouteKey_Outputs. 
	 Available in iOS 5.0 or greater       
	 @constant       kAudioSessionOutputRoute_LineOut
	 A line out output
	 @constant       kAudioSessionOutputRoute_Headphones
	 Speakers in a headset (mic and headphones) or simple headphones
	 @constant       kAudioSessionOutputRoute_BluetoothHFP
	 Speakers that are part of a Bluetooth Hands-Free Profile device
	 @constant       kAudioSessionOutputRoute_BluetoothA2DP
	 Speakers in a Bluetooth A2DP device
	 @constant       kAudioSessionOutputRoute_BuiltInReceiver
	 The speaker you hold to your ear when on a phone call
	 @constant       kAudioSessionOutputRoute_BuiltInSpeaker
	 The built-in speaker
	 @constant       kAudioSessionOutputRoute_USBAudio
	 Speaker(s) in a Universal Serial Bus device
	 @constant       kAudioSessionOutputRoute_HDMI
	 Output via High-Definition Multimedia Interface
	 @constant       kAudioSessionOutputRoute_AirPlay
	 Output on a remote Air Play device
	 */
	extern const CFStringRef kAudioSessionOutputRoute_LineOut           __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);        
	extern const CFStringRef kAudioSessionOutputRoute_Headphones        __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);     
	extern const CFStringRef kAudioSessionOutputRoute_BluetoothHFP      __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);   
	extern const CFStringRef kAudioSessionOutputRoute_BluetoothA2DP     __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);  
	extern const CFStringRef kAudioSessionOutputRoute_BuiltInReceiver   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
	extern const CFStringRef kAudioSessionOutputRoute_BuiltInSpeaker    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
	extern const CFStringRef kAudioSessionOutputRoute_USBAudio          __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);   
	extern const CFStringRef kAudioSessionOutputRoute_HDMI              __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
	extern const CFStringRef kAudioSessionOutputRoute_AirPlay           __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);    
	
    
	// CFDictionary keys for kAudioSessionProperty_InputSources
	extern const CFStringRef   kAudioSession_InputSourceKey_ID            __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
	extern const CFStringRef   kAudioSession_InputSourceKey_Description   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
	
	// CFDictionary keys for kAudioSessionProperty_OutputDestinations
	extern const CFStringRef   kAudioSession_OutputDestinationKey_ID            __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
	extern const CFStringRef   kAudioSession_OutputDestinationKey_Description   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_5_0,__IPHONE_7_0);
    
    
	//==================================================================================================
#pragma mark    AudioSession interruption types for end interruption events
	
	/*!
     @enum          AudioSession Interruption types
     @abstract      When an app's AudioSessionInterruptionListener is called at the end of an interruption event,
	 the app may query to see if it should resume audio or not.  The interruption type can be 
	 obtained through the kAudioSessionProperty_InterruptionType, available in iOS 4.0 and
	 greater.
     @constant      kAudioSessionInterruptionType_ShouldResume 
	 Indicates that the interruption was one where it is appropriate to resume playback
	 at the conclusion of the interruption.  (e.g.: a phone call was rejected)
     @constant      kAudioSessionInterruptionType_ShouldNotResume
	 Indicates that the interruption was one where it is not appropriate to resume playback
	 at the conclusion of the interruption.  (e.g.: interruption due to iPod playback)
	 */
	enum {  // typedef UInt32 AudioSessionInterruptionType
		kAudioSessionInterruptionType_ShouldResume                      = 'irsm',
		kAudioSessionInterruptionType_ShouldNotResume                   = '!rsm'
	};
	typedef UInt32 AudioSessionInterruptionType;	    
	
	//==================================================================================================
#pragma mark    AudioSession mode values
	/*!
     @enum          AudioSession Modes
     @abstract      Modes modify the audio category in order to introduce behavior that is tailored to the specific
	 use of audio within an application.  Available in iOS 5.0 and greater.
     @constant      kAudioSessionMode_Default 
	 The default mode.
     @constant      kAudioSessionMode_VoiceChat
	 Only valid with kAudioSessionCategory_PlayAndRecord.  Appropriate for Voice Over IP
	 (VOIP) applications.  Reduces the number of allowable audio routes to be only those
	 that are appropriate for VOIP applications and may engage appropriate system-supplied
	 signal processing.  Has the side effect of setting 
	 kAudioSessionProperty_OverrideCategoryEnableBluetoothInput to true.
     @constant      kAudioSessionMode_VideoRecording     
	 Only valid with kAudioSessionCategory_PlayAndRecord or kAudioSessionCategory_RecordAudio.
	 Modifies the audio routing options and may engage appropriate system-supplied signal processing.
     @constant      kAudioSessionMode_Measurement
	 Appropriate for applications that wish to minimize the effect of system-supplied signal
	 processing for input and/or output audio signals.
     @constant      kAudioSessionMode_GameChat
	 Set by Game Kit on behalf of an application that uses a GKVoiceChat object; valid 
	 only with the kAudioSessionCategory_PlayAndRecord category.
	 Do not set this mode directly. If you need similar behavior and are not using
	 a GKVoiceChat object, use the kAudioSessionMode_VoiceChat mode.
	 */
	enum { 
		kAudioSessionMode_Default               = 'dflt',
		kAudioSessionMode_VoiceChat             = 'vcct',
		kAudioSessionMode_VideoRecording        = 'vrcd',
		kAudioSessionMode_Measurement           = 'msmt',
		kAudioSessionMode_GameChat              = 'gmct'
	};
	
	//==================================================================================================
#pragma mark    AudioSession Properties
	
	/*!
	 @enum           AudioSession property codes
	 @abstract       These are the property codes used with the AudioSession API.
	 @constant       kAudioSessionProperty_PreferredHardwareSampleRate
	 A Float64 indicating the preferred hardware sample rate for the AudioSession.
	 The actual sample rate may be different
	 @constant       kAudioSessionProperty_PreferredHardwareIOBufferDuration 
	 A Float32 indicating the preferred hardware IO buffer duration in seconds.
	 The actual IO buffer duration may be different
	 @constant       kAudioSessionProperty_AudioCategory 
	 A UInt32 value indicating the audio category for the AudioSession (see constants above).
	 @constant       kAudioSessionProperty_AudioRouteChange 
	 The value for this property is ONLY provided with the property changed callback. You 
	 cannot get the value of this property (or set it).
	 The property changed callback provides a CFDictionaryRef with keyed values:
	 Key = kAudioSession_AudioRouteChangeKey_Reason; value is a CFNumberRef with one of the 
	 reasons listed above.
	 Key = kAudioSession_AudioRouteChangeKey_PreviousRouteDescription; value is a CFDictionaryRef containing
	 information about the previous route.  This dictionary is of exactly the same format as the 
	 dictionary associated with kAudioSessionProperty_AudioRouteDescription.  Available in iOS 5.0 or 
	 greater.
	 Key = kAudioSession_AudioRouteChangeKey_CurrentRouteDescription; value is a CFDictionaryRef containing
	 information about the new route.  This dictionary is of exactly the same format as the 
	 dictionary associated with kAudioSessionProperty_AudioRouteDescription.  Available in iOS 5.0 or 
	 greater.
	 @constant       kAudioSessionProperty_CurrentHardwareSampleRate 
	 A Float64 indicating the current hardware sample rate
	 @constant       kAudioSessionProperty_CurrentHardwareInputNumberChannels 
	 A UInt32 indicating the current number of hardware input channels
	 @constant       kAudioSessionProperty_CurrentHardwareOutputNumberChannels 
	 A UInt32 indicating the current number of hardware output channels
	 @constant       kAudioSessionProperty_CurrentHardwareOutputVolume 
	 A Float32 indicating the current output volume
	 @constant       kAudioSessionProperty_CurrentHardwareInputLatency 
	 A Float32 indicating the current hardware input latency in seconds.
	 @constant       kAudioSessionProperty_CurrentHardwareOutputLatency 
	 A Float32 indicating the current hardware output latency in seconds.
	 @constant       kAudioSessionProperty_CurrentHardwareIOBufferDuration 
	 A Float32 indicating the current hardware IO buffer duration in seconds.
	 @constant       kAudioSessionProperty_OtherAudioIsPlaying 
	 A UInt32 with a value other than zero when someone else, typically the iPod application, 
	 is playing audio
	 @constant       kAudioSessionProperty_OverrideAudioRoute 
	 A UInt32 with one of two values: kAudioSessionOverrideAudioRoute_None or 
	 kAudioSessionOverrideAudioRoute_Speaker
	 @constant       kAudioSessionProperty_AudioInputAvailable 
	 A UInt32 with a value other than zero when audio input is available.
	 Use this property, rather than the device model, to determine if audio input is available.
	 A listener will notify you when audio input becomes available.  For instance, when a headset 
	 is attached to the second generation iPod Touch, audio input becomes available via the wired 
	 microphone. 
	 @constant       kAudioSessionProperty_ServerDied
	 Available with iOS 3.0 or greater
	 The value for this property is ONLY provided with the property changed callback. You cannot get the 
	 value of this property (or set it). The property changed callback notifies you that
	 the audio server has died.
	 @constant       kAudioSessionProperty_OtherMixableAudioShouldDuck
	 Available with iOS 3.0 or greater
	 If the current session category of an application allows mixing (iPod playback in the background 
	 for example), then that other audio will be ducked when the current application makes any sound. 
	 An example of this is the Nike app that does this as it provides periodic updates to its user (it 
	 ducks any iPod music currently being played while it provides its status).
	 This defaults to off (0). Note that the other audio will be ducked for as long as the current 
	 session is active. 
	 You will need to deactivate your audio session when you want full volume playback of the other audio.
	 If your category is the Playback category and you have this set to its default (non-mixable), setting
	 this value to on, will also make your category mixable with others
	 (kAudioSessionProperty_OverrideCategoryMixWithOthers will be set to true)
	 @constant       kAudioSessionProperty_OverrideCategoryMixWithOthers
	 Available with iOS 3.0 or greater
	 This allows an application to change the default behavior of some audio session categories with regards to 
	 whether other applications can play while your session is active. The two typical cases are:
	 (1) PlayAndRecord category
	 this will default to false, but can be set to true. This would allow iPod to play in the background 
	 while an app had both audio input and output enabled
	 (2) MediaPlayback category
	 this will default to false, but can be set to true. This would allow iPod to play in the background, 
	 but an app will still be able to play regardless of the setting of the ringer switch 
	 (3) Other categories
	 this defaults to false and cannot be changed (that is, the mix with others setting of these categories 
	 cannot be overridden 
	 An application must be prepared for setting this property to fail as behaviour may change in future releases. 
	 If an application changes their category, they should reassert the override (it is not sticky across 
	 category changes)
	 @constant       kAudioSessionProperty_OverrideCategoryDefaultToSpeaker
	 Available with iOS 3.1 or greater
	 This allows an application to change the default behaviour of some audio session categories with regards to 
	 the audio route. The current category behavior is:
	 (1) PlayAndRecord category
	 this will default to false, but can be set to true. this will route to Speaker (instead of Receiver) 
	 when no other audio route is connected.
	 (2) Other categories
	 this defaults to false and cannot be changed (that is, the default to speaker setting of these 
	 categories cannot be overridden 
	 An application must be prepared for setting this property to fail as behaviour may change in future releases. 
	 If an application changes their category, they should reassert the override (it is not sticky across category changes)
	 @constant       kAudioSessionProperty_OverrideCategoryEnableBluetoothInput
	 Available with iOS 3.1 or greater
	 This allows an application to change the default behaviour of some audio session categories with regards to showing 
	 bluetooth devices as available routes. The current category behavior is:
	 (1) PlayAndRecord category
	 this will default to false, but can be set to true. This will allow a paired bluetooth device to show up as 
	 an available route for input, while playing through the category-appropriate output
	 (2) Record category
	 this will default to false, but can be set to true. This will allow a paired bluetooth device to show up 
	 as an available route for input 
	 (3) Other categories
	 this defaults to false and cannot be changed (that is, enabling bluetooth for input in these categories is 
	 not allowed) 
	 An application must be prepared for setting this property to fail as behaviour may change in future releases. 
	 If an application changes their category, they should reassert the override (it is not sticky across category changes)
	 @constant       kAudioSessionProperty_InterruptionType
	 Available with iOS 4.0 or greater
	 This is a read-only property that gives the type of the end interruption event.  Media playback apps (i.e., 
	 those apps that have a "play" button), may use this property as a guideline for when to resume playing after an 
	 interruption ends.  Apps without a "play" button, (e.g., games) should always resume audio playback when the 
	 interruption ends.  This property is only valid within the scope of the client app's AudioSessionInterruptionListener 
	 callback and only valid for the AudioSessionEndInterruption event.  Attempting to read the property at any other 
	 time is invalid.  
	 @constant       kAudioSessionProperty_Mode
	 Available with iOS 5.0 or greater
	 A UInt32 value that specifies the mode to be combined with the Audio Category.  See AudioSession mode 
	 values defined above.
	 @constant       kAudioSessionProperty_InputSources
	 Available with iOS 5.0 or greater
	 For use with certain accessories, such as some USB audio devices, that support input source selection.  
	 If the attached accessory supports source selection, provides a description of the available sources.
	 Not to be confused with kAudioSessionProperty_AudioRouteDescription, which provides a description
	 of the current audio route.  
	 A CFArray of CFDictionaries with the keys listed below.  If no input sources are 
	 available, a valid CFArray with 0 entries will be returned by a get operation.
	 Key = kAudioSession_InputSourceKey_ID; value is a CFNumberRef representing a system-defined identifier
	 for the input source.  This is the identifier to be used when setting the input source.  
	 Key = kAudioSession_InputSourceKey_Description; value is a CFStringRef description of the input source 
	 suitable for displaying in a user interface.  Examples: "Internal Mic", "External Mic", 
	 "Ext 48V Mic", "Instrument", "External Line Connector"
	 @constant       kAudioSessionProperty_OutputDestinations
	 Available with iOS 5.0 or greater
	 For use with certain accessories, such as some USB audio devices, that support output destination selection.  
	 If the attached accessory supports destination selection, provides a description of the available destinations.
	 Not to be confused with kAudioSessionProperty_AudioRouteDescription, which provides a description
	 of the current audio route. 
	 A CFArray of CFDictionaries with the keys listed below.  If no output destinations are 
	 available, a valid CFArray with 0 entries will be returned by a get operation.
	 Key = kAudioSession_OutputDestinationKey_ID; value is a CFNumberRef representing a system-defined identifier
	 for the output destination.  This is the identifier to be used when setting the destination.
	 Key = kAudioSession_OutputDestinationKey_Description; value is a CFStringRef description of the output 
	 destination suitable for displaying in a user interface. 
	 @constant       kAudioSessionProperty_InputSource
	 Available with iOS 5.0 or greater
	 For use with certain accessories, such as some USB audio devices, that support input source selection. 
	 A CFNumberRef value that specifies the input source to be selected.  The value must be one of the 
	 IDs provided by the kAudioSession_InputSourceKey_ID as part of the data associated with 
	 kAudioSessionProperty_InputSources.
	 @constant       kAudioSessionProperty_OutputDestination
	 Available with iOS 5.0 or greater
	 For use with certain accessories, such as some USB audio devices, that support output destination selection.
	 A CFNumberRef value that specifies the output destination to be selected.  The value must be one 
	 of the IDs provided by the kAudioSession_OutputDestinationKey_ID as part of the data associated with
	 kAudioSessionProperty_OutputDestinations.
	 @constant       kAudioSessionProperty_InputGainAvailable
	 Available with iOS 5.0 or greater
	 A UInt32 with a value other than zero when audio input gain is available.  Some inputs may not 
	 provide the ability to set the input gain, so check this value before attempting to set input gain.
	 @constant       kAudioSessionProperty_InputGainScalar
	 Available with iOS 5.0 or greater
	 A Float32 value defined over the range [0.0, 1.0], with 0.0 corresponding to the lowest analog 
	 gain setting and 1.0 corresponding to the highest analog gain setting.  Attempting to set values
	 outside of the defined range will result in the value being "clamped" to a valid input.  This is 
	 a global input gain setting that applies to the current input source for the entire system.  
	 When no applications are using the input gain control, the system will restore the default input
	 gain setting for the input source.  Note that some audio accessories, such as USB devices, may 
	 not have a default value.  This property is only valid if kAudioSessionProperty_InputGainAvailable
	 is true.  Note that route change events represent substantive changes to the audio system. Input 
	 gain settings are not guaranteed to persist across route changes. Application code should be aware
	 that route change events can (and likely will) cause a change to input gain settings, and so should
	 be prepared to reassess the state of input gain after the new route is established.
	 @constant       kAudioSessionProperty_AudioRouteDescription 
	 Available with iOS 5.0 or greater
	 A CFDictionaryRef with information about the current audio route; keyed values:
	 Key = kAudioSession_AudioRouteKey_Inputs; value is a CFArray of CFDictionaries with information about the 
	 inputs utilitized in the current audio route.  
	 Key = kAudioSession_AudioRouteKey_Outputs; value is a CFArray of CFDictionaries with information about the 
	 outputs utilitized in the current audio route.
	 Both kAudioSession_AudioRouteKey_Inputs and kAudioSession_AudioRouteKey_Outputs return a CFArray of
	 CFDictionaries with Key = kAudioSession_AudioRouteKey_Type; value is a CFString corresponding
	 to the input or output types documented above.
	 */
	enum { // typedef UInt32 AudioSessionPropertyID
		kAudioSessionProperty_PreferredHardwareSampleRate           = 'hwsr',   // Float64          (get/set)
		kAudioSessionProperty_PreferredHardwareIOBufferDuration     = 'iobd',   // Float32          (get/set)
		kAudioSessionProperty_AudioCategory                         = 'acat',   // UInt32           (get/set)
		kAudioSessionProperty_AudioRouteChange                      = 'roch',   // CFDictionaryRef  (property listener)
		kAudioSessionProperty_CurrentHardwareSampleRate             = 'chsr',   // Float64          (get only)
		kAudioSessionProperty_CurrentHardwareInputNumberChannels    = 'chic',   // UInt32           (get only/property listener)
		kAudioSessionProperty_CurrentHardwareOutputNumberChannels   = 'choc',   // UInt32           (get only/property listener)
		kAudioSessionProperty_CurrentHardwareOutputVolume           = 'chov',   // Float32          (get only/property listener)
		kAudioSessionProperty_CurrentHardwareInputLatency           = 'cilt',   // Float32          (get only)
		kAudioSessionProperty_CurrentHardwareOutputLatency          = 'colt',   // Float32          (get only)
		kAudioSessionProperty_CurrentHardwareIOBufferDuration       = 'chbd',   // Float32          (get only)
		kAudioSessionProperty_OtherAudioIsPlaying                   = 'othr',   // UInt32           (get only)
		kAudioSessionProperty_OverrideAudioRoute                    = 'ovrd',   // UInt32           (set only)
		kAudioSessionProperty_AudioInputAvailable                   = 'aiav',   // UInt32           (get only/property listener)
		kAudioSessionProperty_ServerDied                            = 'died',   // UInt32           (property listener)
		kAudioSessionProperty_OtherMixableAudioShouldDuck           = 'duck',   // UInt32           (get/set)
		kAudioSessionProperty_OverrideCategoryMixWithOthers         = 'cmix',   // UInt32           (get, some set)
		kAudioSessionProperty_OverrideCategoryDefaultToSpeaker      = 'cspk',   // UInt32           (get, some set)
		kAudioSessionProperty_OverrideCategoryEnableBluetoothInput  = 'cblu',   // UInt32           (get, some set)
		kAudioSessionProperty_InterruptionType                      = 'type',   // UInt32           (get only)
		kAudioSessionProperty_Mode                                  = 'mode',   // UInt32           (get/set)
		kAudioSessionProperty_InputSources                          = 'srcs',   // CFArrayRef       (get only/property listener)
		kAudioSessionProperty_OutputDestinations                    = 'dsts',   // CFArrayRef       (get only/property listener)
		kAudioSessionProperty_InputSource                           = 'isrc',   // CFNumberRef      (get/set)
		kAudioSessionProperty_OutputDestination                     = 'odst',   // CFNumberRef      (get/set)
		kAudioSessionProperty_InputGainAvailable                    = 'igav',   // UInt32           (get only/property listener)
		kAudioSessionProperty_InputGainScalar                       = 'igsc',   // Float32          (get/set/property listener)
		kAudioSessionProperty_AudioRouteDescription                 = 'crar'    // CFDictionaryRef  (get only)
	};
    
	//==================================================================================================
#pragma mark -
#pragma mark Callbacks
	/*!
	 @typedef        AudioSessionInterruptionListener
	 @abstract       A function to be called when an interruption begins or ends.
	 @discussion     AudioSessionInterruptionListener has to be provided by client applications in the
	 AudioSessionInitialize function.  It will be called when an interruption begins or ends.
	 @param          inClientData
	 The client user data to use when calling the listener.
	 @param          inInterruptionState
	 Indicates if the interruption begins (kAudioSessionBeginInterruption)
	 or ends (kAudioSessionEndInterruption)
	 */
	typedef void (*AudioSessionInterruptionListener)(
													 void *                  inClientData,
													 UInt32                  inInterruptionState);
	
	/*!
	 @typedef        AudioSessionPropertyListener
	 @abstract       A function to be executed when a property changes.
	 @discussion     AudioSessionPropertyListener may be provided by client application to be
	 called when a property changes.
	 @param          inClientData
	 The client user data to use when calling the listener.
	 @param          inID
	 The AudioSession property that changed
	 @param          inDataSize
	 The size of the payload
	 @param          inData
	 The payload of the property that changed (see data type for each property)
	 */
	typedef void (*AudioSessionPropertyListener)(
												 void *                  inClientData,
												 AudioSessionPropertyID	inID,
												 UInt32                  inDataSize,
												 const void *            inData);
	
	//==================================================================================================
#pragma mark -
#pragma mark    AudioSession Functions
	
	/*!
	 @functiongroup  AudioSession
	 */
	
	/*!
	 @function       AudioSessionInitialize
	 @abstract       Initialize the AudioSession.
	 @discussion     This function has to be called once before calling any other
	 AudioSession functions.
	 @param          inRunLoop
	 A CFRunLoopRef indicating the desired run loop the interruption routine should
	 be run on. Pass NULL to use the main run loop.
	 @param          inRunLoopMode
	 A CFStringRef indicating the run loop mode for the runloop where the
	 completion routine will be executed. Pass NULL to use kCFRunLoopDefaultMode.
	 @param          inInterruptionListener
	 An AudioSessionInterruptionListener to be called when the AudioSession
	 is interrupted.
	 @param          inClientData
	 The client user data to use when calling the interruption listener.
	 */
	extern OSStatus
	AudioSessionInitialize(             CFRunLoopRef                        inRunLoop, 
						   CFStringRef                         inRunLoopMode, 
						   AudioSessionInterruptionListener    inInterruptionListener, 
						   void                                *inClientData)              
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_7_0);
	
	/*!
	 @function       AudioSessionSetActive
	 @abstract       Activate or deactivate the AudioSession.
	 @discussion     Call this function with active set to true to activate this AudioSession (interrupt
	 the currently active AudioSession).
	 Call this function with active set to false to deactivate this AudioSession (allow
	 another interrupted AudioSession to resume).
	 When active is true this call may fail if the currently active AudioSession has a higher priority.
	 @param          active
	 A Boolean indicating if you want to make this AudioSession active or inactive.
	 */
	extern OSStatus
	AudioSessionSetActive(              Boolean                             active)                     
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_7_0);
	
	//==================================================================================================
#pragma mark    AudioSessionActivationFlags for AudioSessionSetActiveWithFlags
    
	/*!
	 @enum           Flags for AudioSessionSetActiveWithFlags
	 @abstract       These are valid bitmap flags that may be combined and passed to AudioSessionSetActiveWithFlags
	 to refine this routine's behavior.
	 @constant       kAudioSessionSetActiveFlag_NotifyOthersOnDeactivation
	 Notify an interrupted app that the interruption has ended and it may resume playback. Only
	 valid on session deactivation.
	 */
	enum {
		kAudioSessionSetActiveFlag_NotifyOthersOnDeactivation       = (1 << 0)  //  0x01
	};
    
	/*!
	 @function       AudioSessionSetActiveWithFlags
	 @abstract       Same functionality as AudioSessionSetActive, with an additional flags parameter for 
	 refining behavior.
	 @discussion     Call this function with active set to true to activate this AudioSession (interrupt
	 the currently active AudioSession).
	 Call this function with active set to false to deactivate this AudioSession (allow
	 another interrupted AudioSession to resume).
	 Pass in one or more flags to refine the behavior during activation or deactivation.
	 When active is true this call may fail if the currently active AudioSession has a 
	 higher priority.
	 @param          active
	 A Boolean indicating if you want to make this AudioSession active or inactive.
	 @param          inFlags
	 A bitmap containing one or more flags from the AudioSessionActivationFlags enum.
	 */
	extern OSStatus
	AudioSessionSetActiveWithFlags(     Boolean                             active,
								   UInt32                              inFlags)                    
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_4_0,__IPHONE_7_0);
	
	/*!
	 @function       AudioSessionGetProperty
	 @abstract       Get the value of a property.
	 @discussion     This function can be called to get the value for a property of the AudioSession.
	 Valid properties are listed in an enum above.
	 @param          inID
	 The AudioSessionPropertyID for which we want to get the value.
	 @param          ioDataSize
	 The size of the data payload.
	 On entry it should contain the size of the memory pointed to by outData.
	 On exit it will contain the actual size of the data.
	 @param          outData
	 The data for the property will be copied here.
	 @return         kAudioSessionNoError if the operation was successful.  If the property is a
	 write-only property or only available by way of property listeners, 
	 kAudioSessionUnsupportedPropertyError will be returned.  Other error codes 
	 listed under AudioSession Error Constants also apply to this function.
	 */
	extern OSStatus
	AudioSessionGetProperty(            AudioSessionPropertyID              inID,
							UInt32                              *ioDataSize,
							void                                *outData)                   
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_7_0);
	
	/*!
	 @function       AudioSessionSetProperty
	 @abstract       Set the value of a property.
	 @discussion     This function can be called to set the value for a property of the AudioSession.
	 Valid properties are listed in an enum above.
	 @param          inID
	 The AudioSessionPropertyID for which we want to set the value.
	 @param          inDataSize
	 The size of the data payload.
	 @param          inData
	 The data for the property we want to set.
	 @return         kAudioSessionNoError if the operation was successful.  If the property is a
	 read-only property or an invalid property value is passed in, 
	 kAudioSessionUnsupportedPropertyError will be returned.  Other error codes 
	 listed under AudioSession Error Constants also apply to 
	 this function.
	 */
	extern OSStatus
	AudioSessionSetProperty(            AudioSessionPropertyID              inID,
							UInt32                              inDataSize,
							const void                          *inData)                    
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_7_0);
	
	/*!
	 @function       AudioSessionGetPropertySize
	 @abstract       Get the size of the payload for a property.
	 @discussion     This function can be called to get the size for the payload of a property.
	 Valid properties are listed in an enum above.
	 @param          inID
	 The AudioSessionPropertyID for which we want to get the size of the payload.
	 @param          outDataSize
	 The size of the data payload will be copied here.
	 */
	extern OSStatus
	AudioSessionGetPropertySize(        AudioSessionPropertyID              inID,
								UInt32                              *outDataSize)               
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_7_0);
	
	/*!
	 @function       AudioSessionAddPropertyListener
	 @abstract       Add a property listener.
	 @discussion     This function can be used to add a listener to be called when a property changes.
	 If a listener and user data already exist for this property, they will be replaced.
	 Valid properties are listed above.
	 @param          inID
	 The AudioSessionPropertyID for which we want to set a listener.
	 @param          inProc
	 The listener to be called when the property changes.
	 @param          inClientData
	 The client user data to use when calling the listener.
	 @return         kAudioSessionNoError if the operation was successful.  If the property does
	 not support listeners, kAudioSessionUnsupportedPropertyError will be returned.  
	 Other error codes listed under AudioSession Error Constants also apply to 
	 this function.
	 */
	extern OSStatus
	AudioSessionAddPropertyListener(    AudioSessionPropertyID              inID,
                                    AudioSessionPropertyListener        inProc,
                                    void                                *inClientData)              
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_7_0);
	
	/*!
	 @function       AudioSessionRemovePropertyListener
	 @abstract       see AudioSessionRemovePropertyListenerWithUserData
	 @discussion     see AudioSessionRemovePropertyListenerWithUserData
	 */
	extern OSStatus
	AudioSessionRemovePropertyListener(	AudioSessionPropertyID          inID)                           
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_2_0);
	
	/*!
	 @function       AudioSessionRemovePropertyListener
	 @abstract       Remove a property listener.
	 @discussion     This function can be called to remove the listener for a property. The caller
	 provides the same proc and user data that was used to add the listener. This ensures
	 that there can be more than one listener established for a given property ID,
	 and each listener can be removed as requested.
	 Valid properties are listed above.
	 @param          inID
	 The AudioSessionPropertyID for which we want to remove the listener.
	 @param          inProc
	 The proc that was used to add the listener that needs to be removed.
	 @param          inClientData
	 The client data that was used to add the listener that needs to be removed.
	 @return         kAudioSessionNoError if the operation was successful.  If the property does
	 not support listeners, kAudioSessionUnsupportedPropertyError will be returned.  
	 Other error codes listed under AudioSession Error Constants also apply to 
	 this function.
	 */
	extern OSStatus
	AudioSessionRemovePropertyListenerWithUserData(	AudioSessionPropertyID          inID,
												   AudioSessionPropertyListener    inProc,
												   void                            *inClientData)              
	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_1,__IPHONE_7_0);
	
#pragma mark -
#pragma mark Deprecated
	
	/*!
	 @enum           AudioSession audio categories states
	 @abstract       These two session categories are deprecated in iOS 3.0 or later
	 @constant       kAudioSessionCategory_UserInterfaceSoundEffects
	 use kAudioSessionCategory_AmbientSound
	 @constant       kAudioSessionCategory_LiveAudio 
	 use kAudioSessionCategory_MediaPlayback
	 */
	enum {
		kAudioSessionCategory_UserInterfaceSoundEffects  = 'uifx',
		kAudioSessionCategory_LiveAudio                  = 'live'
	};
	
	/*!
	 @enum           AudioSession audio categories states
	 @abstract       Deprecated AudioSession properties
	 @constant       kAudioSessionProperty_AudioRoute 
	 Deprecated in iOS 5.0; Use kAudioSessionProperty_AudioRouteDescription 
	 */
	enum {
		kAudioSessionProperty_AudioRoute                            = 'rout',   // CFStringRef      (get only)        
	};
	
	// deprecated dictionary keys
    
	// Deprecated in iOS 5.0; Use kAudioSession_AudioRouteChangeKey_PreviousRouteDescription instead    
#define kAudioSession_AudioRouteChangeKey_OldRoute  "OutputDeviceDidChange_OldRoute"
	//==================================================================================================

#ifdef __cplusplus
}
#endif

#endif /* __AudioSession_h__ */

// ==========  AudioToolbox.framework/Headers/AudioConverter.h
/*!
	@file		AudioConverter.h
	@framework	AudioToolbox.framework
	@copyright	(c) 1985-2015 by Apple, Inc., all rights reserved.
    @abstract   API's to perform audio format conversions.
    
    @discussion
		AudioConverters convert between various linear PCM and compressed
		audio formats. Supported transformations include:

		- PCM float/integer/bit depth conversions
		- PCM sample rate conversion
		- PCM interleaving and deinterleaving
		- encoding PCM to compressed formats
		- decoding compressed formats to PCM

		A single AudioConverter may perform more than one
		of the above transformations.
*/

#ifndef AudioToolbox_AudioConverter_h
#define AudioToolbox_AudioConverter_h

//==================================================================================================

/*!
    @header     AudioConverter.h
    
*/

//=============================================================================
//  Includes
//=============================================================================

#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
    #include <CoreAudio/CoreAudioTypes.h>
#else
    #include <CoreAudioTypes.h>
#endif

CF_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
extern "C"
{
#endif

//=============================================================================
//  Theory of Operation
//=============================================================================

//=============================================================================
//  Types specific to the Audio Converter API
//=============================================================================

/*!
    @typedef    AudioConverterRef
    @abstract   A reference to an AudioConverter object.
*/
typedef struct OpaqueAudioConverter *   AudioConverterRef;

typedef UInt32                          AudioConverterPropertyID;

//=============================================================================
//  Standard Properties
//=============================================================================

/*!
    @enum       AudioConverterPropertyID
    @abstract   The properties of an AudioConverter, accessible via AudioConverterGetProperty()
                and AudioConverterSetProperty().
    
    @constant   kAudioConverterPropertyMinimumInputBufferSize
                    a UInt32 that indicates the size in bytes of the smallest buffer of input
                    data that can be supplied via the AudioConverterInputProc or as the input to
                    AudioConverterConvertBuffer
    @constant   kAudioConverterPropertyMinimumOutputBufferSize
                    a UInt32 that indicates the size in bytes of the smallest buffer of output
                    data that can be supplied to AudioConverterFillComplexBuffer or as the output to
                    AudioConverterConvertBuffer
    @constant   kAudioConverterPropertyMaximumInputBufferSize
                    DEPRECATED. The AudioConverter input proc may be passed any number of packets of data.
                    If fewer are packets are returned than required, then the input proc will be called again.
                    If more packets are passed than required, they will remain in the client's buffer and be 
                    consumed as needed.
    @constant   kAudioConverterPropertyMaximumInputPacketSize
                    a UInt32 that indicates the size in bytes of the largest single packet of
                    data in the input format. This is mostly useful for variable bit rate
                    compressed data (decoders).
    @constant   kAudioConverterPropertyMaximumOutputPacketSize
                    a UInt32 that indicates the size in bytes of the largest single packet of
                    data in the output format. This is mostly useful for variable bit rate
                    compressed data (encoders).
    @constant   kAudioConverterPropertyCalculateInputBufferSize
                    a UInt32 that on input holds a size in bytes that is desired for the output
                    data. On output, it will hold the size in bytes of the input buffer required
                    to generate that much output data. Note that some converters cannot do this
                    calculation.
    @constant   kAudioConverterPropertyCalculateOutputBufferSize
                    a UInt32 that on input holds a size in bytes that is desired for the input
                    data. On output, it will hold the size in bytes of the output buffer
                    required to hold the output data that will be generated. Note that some
                    converters cannot do this calculation.
    @constant   kAudioConverterPropertyInputCodecParameters
                    The value of this property varies from format to format and is considered
                    private to the format. It is treated as a buffer of untyped data.
    @constant   kAudioConverterPropertyOutputCodecParameters
                    The value of this property varies from format to format and is considered
                    private to the format. It is treated as a buffer of untyped data.
    @constant   kAudioConverterSampleRateConverterAlgorithm
                    DEPRECATED: please use kAudioConverterSampleRateConverterComplexity instead
    @constant   kAudioConverterSampleRateConverterComplexity
                    An OSType that specifies the sample rate converter algorithm to use (as defined in
                    AudioUnit/AudioUnitProperties.h)
    @constant   kAudioConverterSampleRateConverterQuality
                    A UInt32 that specifies rendering quality of the sample rate converter (see
                    enum constants below)
    @constant   kAudioConverterSampleRateConverterInitialPhase
                    A Float64 with value 0.0 <= x < 1.0 giving the initial subsample position of the 
                    sample rate converter.
    @constant   kAudioConverterCodecQuality
                    A UInt32 that specifies rendering quality of a codec (see enum constants
                    below)
    @constant   kAudioConverterPrimeMethod
                    a UInt32 specifying priming method (usually for sample-rate converter) see
                    explanation for struct AudioConverterPrimeInfo below along with enum
                    constants
    @constant   kAudioConverterPrimeInfo
                    A pointer to AudioConverterPrimeInfo (see explanation for struct
                    AudioConverterPrimeInfo below)
    @constant   kAudioConverterChannelMap
                    An array of SInt32's.  The size of the array is the number of output
                    channels, and each element specifies which input channel's data is routed to
                    that output channel (using a 0-based index of the input channels), or -1 if
                    no input channel is to be routed to that output channel.  The default
                    behavior is as follows. I = number of input channels, O = number of output
                    channels. When I > O, the first O inputs are routed to the first O outputs,
                    and the remaining puts discarded.  When O > I, the first I inputs are routed
                    to the first O outputs, and the remaining outputs are zeroed.
                    
                    A simple example for splitting mono input to stereo output (instead of routing
                    the input to only the first output channel):
                    
<pre>
   // this should be as large as the number of output channels:
  SInt32 channelMap[2] = { 0, 0 };
  AudioConverterSetProperty(theConverter, kAudioConverterChannelMap, 
    sizeof(channelMap), channelMap);
</pre>
    @constant   kAudioConverterDecompressionMagicCookie
                    A void * pointing to memory set up by the caller. Required by some formats
                    in order to decompress the input data.
    @constant   kAudioConverterCompressionMagicCookie
                    A void * pointing to memory set up by the caller. Returned by the converter
                    so that it may be stored along with the output data. It can then be passed
                    back to the converter for decompression at a later time.
    @constant   kAudioConverterEncodeBitRate
                    A UInt32 containing the number of bits per second to aim for when encoding
                    data. Some decoders will also allow you to get this property to discover the bit rate.
    @constant   kAudioConverterEncodeAdjustableSampleRate
                    For encoders where the AudioConverter was created with an output sample rate
                    of zero, and the codec can do rate conversion on its input, this provides a
                    way to set the output sample rate. The property value is a Float64.
    @constant   kAudioConverterInputChannelLayout
                    The property value is an AudioChannelLayout.
    @constant   kAudioConverterOutputChannelLayout
                    The property value is an AudioChannelLayout.
    @constant   kAudioConverterApplicableEncodeBitRates
                    The property value is an array of AudioValueRange describing applicable bit
                    rates based on current settings.
    @constant   kAudioConverterAvailableEncodeBitRates
                    The property value is an array of AudioValueRange describing available bit
                    rates based on the input format. You can get all available bit rates from
                    the AudioFormat API.
    @constant   kAudioConverterApplicableEncodeSampleRates
                    The property value is an array of AudioValueRange describing applicable
                    sample rates based on current settings.
    @constant   kAudioConverterAvailableEncodeSampleRates
                    The property value is an array of AudioValueRange describing available
                    sample rates based on the input format. You can get all available sample
                    rates from the AudioFormat API.
    @constant   kAudioConverterAvailableEncodeChannelLayoutTags
                    The property value is an array of AudioChannelLayoutTags for the format and
                    number of channels specified in the input format going to the encoder.
    @constant   kAudioConverterCurrentOutputStreamDescription
                    Returns the current completely specified output AudioStreamBasicDescription.
                    For example when encoding to AAC, your original output stream description
                    will not have been completely filled out.
    @constant   kAudioConverterCurrentInputStreamDescription
                    Returns the current completely specified input AudioStreamBasicDescription.
    @constant   kAudioConverterPropertySettings
                    Returns the a CFArray of property settings for converters.
    @constant   kAudioConverterPropertyBitDepthHint
                    An SInt32 of the source bit depth to preserve. This is a hint to some
                    encoders like lossless about how many bits to preserve in the input. The
                    converter usually tries to preserve as many as possible, but a lossless
                    encoder will do poorly if more bits are supplied than are desired in the
                    output. The bit depth is expressed as a negative number if the source was floating point,
                    e.g. -32 for float, -64 for double.
    @constant   kAudioConverterPropertyFormatList
                    An array of AudioFormatListItem structs describing all the data formats produced by the
                    encoder end of the AudioConverter. If the ioPropertyDataSize parameter indicates that
                    outPropertyData is sizeof(AudioFormatListItem), then only the best format is returned.
                    This property may be used for example to discover all the data formats produced by the AAC_HE2
                    (AAC High Efficiency vers. 2) encoder.
*/
CF_ENUM(AudioConverterPropertyID)
{
    kAudioConverterPropertyMinimumInputBufferSize       = 'mibs',
    kAudioConverterPropertyMinimumOutputBufferSize      = 'mobs',
    kAudioConverterPropertyMaximumInputBufferSize       = 'xibs',
    kAudioConverterPropertyMaximumInputPacketSize       = 'xips',
    kAudioConverterPropertyMaximumOutputPacketSize      = 'xops',
    kAudioConverterPropertyCalculateInputBufferSize     = 'cibs',
    kAudioConverterPropertyCalculateOutputBufferSize    = 'cobs',
    kAudioConverterPropertyInputCodecParameters         = 'icdp',
    kAudioConverterPropertyOutputCodecParameters        = 'ocdp',
    kAudioConverterSampleRateConverterAlgorithm         = 'srci',
    kAudioConverterSampleRateConverterComplexity        = 'srca',
    kAudioConverterSampleRateConverterQuality           = 'srcq',
    kAudioConverterSampleRateConverterInitialPhase      = 'srcp',
    kAudioConverterCodecQuality                         = 'cdqu',
    kAudioConverterPrimeMethod                          = 'prmm',
    kAudioConverterPrimeInfo                            = 'prim',
    kAudioConverterChannelMap                           = 'chmp',
    kAudioConverterDecompressionMagicCookie             = 'dmgc',
    kAudioConverterCompressionMagicCookie               = 'cmgc',
    kAudioConverterEncodeBitRate                        = 'brat',
    kAudioConverterEncodeAdjustableSampleRate           = 'ajsr',
    kAudioConverterInputChannelLayout                   = 'icl ',
    kAudioConverterOutputChannelLayout                  = 'ocl ',
    kAudioConverterApplicableEncodeBitRates             = 'aebr',
    kAudioConverterAvailableEncodeBitRates              = 'vebr',
    kAudioConverterApplicableEncodeSampleRates          = 'aesr',
    kAudioConverterAvailableEncodeSampleRates           = 'vesr',
    kAudioConverterAvailableEncodeChannelLayoutTags     = 'aecl',
    kAudioConverterCurrentOutputStreamDescription       = 'acod',
    kAudioConverterCurrentInputStreamDescription        = 'acid',
    kAudioConverterPropertySettings                     = 'acps',
    kAudioConverterPropertyBitDepthHint                 = 'acbd',
    kAudioConverterPropertyFormatList                   = 'flst'
};

#if TARGET_OS_IPHONE
/*!
    @enum       AudioConverterPropertyID (iOS only)
    @abstract   iOS-specific properties of an AudioConverter, accessible via AudioConverterGetProperty()
                and AudioConverterSetProperty().
    
    @constant   kAudioConverterPropertyCanResumeFromInterruption
                    A read-only UInt32 signifying whether the underlying codec supports resumption following
                    an interruption. If the property is unimplemented (i.e. AudioConverterGetProperty
                    returns an error), then the codec is not a hardware codec. If the property's value
                    is 1, then the codec can resume work following an interruption. If the property's
                    value is 0, then interruptions destroy the codec's state.
*/  
CF_ENUM(AudioConverterPropertyID)
{
    kAudioConverterPropertyCanResumeFromInterruption    = 'crfi'
};
#endif

#if !TARGET_OS_IPHONE
//=============================================================================
//  
//=============================================================================

/*!
    @enum       Mac OS X AudioConverter Properties

    @constant   kAudioConverterPropertyDithering
					A UInt32. Set to a value from the enum of dithering algorithms below. 
					Zero means no dithering and is the default. (Mac OS X only.)
    @constant   kAudioConverterPropertyDitherBitDepth
					A UInt32. Dither is applied at this bit depth.  (Mac OS X only.)

*/
CF_ENUM(AudioConverterPropertyID)
{
	kAudioConverterPropertyDithering					= 'dith',
	kAudioConverterPropertyDitherBitDepth				= 'dbit'
};

/*!
    @enum       Dithering algorithms

    @abstract   Constants to be used as the value for kAudioConverterPropertyDithering.

    @constant   kDitherAlgorithm_TPDF             Dither signal is generated by a white noise source with a triangular probability density function
    @constant   kDitherAlgorithm_NoiseShaping     Use a static, perceptually weighted noise shaped dither
*/
CF_ENUM(UInt32)
{
	kDitherAlgorithm_TPDF				= 1,	
	kDitherAlgorithm_NoiseShaping		= 2 
};
#endif

/*!
    @enum       Quality constants

    @abstract   Constants to be used with kAudioConverterSampleRateConverterQuality.

    @constant   kAudioConverterQuality_Max          maximum quality
    @constant   kAudioConverterQuality_High         high quality
    @constant   kAudioConverterQuality_Medium       medium quality
    @constant   kAudioConverterQuality_Low          low quality
    @constant   kAudioConverterQuality_Min          minimum quality
*/
CF_ENUM(UInt32)
{
    kAudioConverterQuality_Max                              = 0x7F,
    kAudioConverterQuality_High                             = 0x60,
    kAudioConverterQuality_Medium                           = 0x40,
    kAudioConverterQuality_Low                              = 0x20,
    kAudioConverterQuality_Min                              = 0
};


/*!
    @enum           Sample Rate Converter Complexity
    @constant       kAudioConverterSampleRateConverterComplexity_Linear
    @discussion         Linear interpolation. lowest quality, cheapest.
    @constant       kAudioConverterSampleRateConverterComplexity_Normal
    @discussion         Normal quality sample rate conversion.
    @constant       kAudioConverterSampleRateConverterComplexity_Mastering
    @discussion         Mastering quality sample rate conversion. More expensive.
*/
CF_ENUM(UInt32)
{
    kAudioConverterSampleRateConverterComplexity_Linear             = 'line',   // linear interpolation
    kAudioConverterSampleRateConverterComplexity_Normal             = 'norm',   // normal quality range, the default
    kAudioConverterSampleRateConverterComplexity_Mastering          = 'bats',   // higher quality range, more expensive
};


/*!
    @enum       Prime method constants

    @abstract   Constants to be used with kAudioConverterPrimeMethod.
    
    @constant   kConverterPrimeMethod_Pre
                    Primes with leading + trailing input frames.
    @constant   kConverterPrimeMethod_Normal
                    Only primes with trailing (zero latency). Leading frames are assumed to be
                    silence.
    @constant   kConverterPrimeMethod_None
                    Acts in "latency" mode. Both leading and trailing frames assumed to be
                    silence.
*/
CF_ENUM(UInt32)
{
    kConverterPrimeMethod_Pre       = 0,
    kConverterPrimeMethod_Normal    = 1,
    kConverterPrimeMethod_None      = 2
};

/*!
    @struct     AudioConverterPrimeInfo
    @abstract   Specifies priming information.
    
    @field      leadingFrames
        Specifies the number of leading (previous) input frames, relative to the normal/desired
        start input frame, required by the converter to perform a high quality conversion. If
        using kConverterPrimeMethod_Pre, the client should "pre-seek" the input stream provided
        through the input proc by leadingFrames. If no frames are available previous to the
        desired input start frame (because, for example, the desired start frame is at the very
        beginning of available audio), then provide "leadingFrames" worth of initial zero frames
        in the input proc.  Do not "pre-seek" in the default case of
        kConverterPrimeMethod_Normal or when using kConverterPrimeMethod_None.

    @field      trailingFrames
        Specifies the number of trailing input frames (past the normal/expected end input frame)
        required by the converter to perform a high quality conversion.  The client should be
        prepared to provide this number of additional input frames except when using
        kConverterPrimeMethod_None. If no more frames of input are available in the input stream
        (because, for example, the desired end frame is at the end of an audio file), then zero
        (silent) trailing frames will be synthesized for the client.
            
    @discussion
        When using AudioConverterFillComplexBuffer() (either a single call or a series of calls), some
        conversions, particularly involving sample-rate conversion, ideally require a certain
        number of input frames previous to the normal start input frame and beyond the end of
        the last expected input frame in order to yield high-quality results.
        
        These are expressed in the leadingFrames and trailingFrames members of the structure.
        
        The very first call to AudioConverterFillComplexBuffer(), or first call after
        AudioConverterReset(), will request additional input frames beyond those normally
        expected in the input proc callback to fulfill this first AudioConverterFillComplexBuffer()
        request. The number of additional frames requested, depending on the prime method, will
        be approximately:

        <pre>
            kConverterPrimeMethod_Pre       leadingFrames + trailingFrames
            kConverterPrimeMethod_Normal    trailingFrames
            kConverterPrimeMethod_None      0
        </pre>

        Thus, in effect, the first input proc callback(s) may provide not only the leading
        frames, but also may "read ahead" by an additional number of trailing frames depending
        on the prime method.

        kConverterPrimeMethod_None is useful in a real-time application processing live input,
        in which case trailingFrames (relative to input sample rate) of through latency will be
        seen at the beginning of the output of the AudioConverter.  In other real-time
        applications such as DAW systems, it may be possible to provide these initial extra
        audio frames since they are stored on disk or in memory somewhere and
        kConverterPrimeMethod_Pre may be preferable.  The default method is
        kConverterPrimeMethod_Normal, which requires no pre-seeking of the input stream and
        generates no latency at the output.
*/
struct AudioConverterPrimeInfo {
    UInt32      leadingFrames;
    UInt32      trailingFrames;
};
typedef struct AudioConverterPrimeInfo AudioConverterPrimeInfo;

//=============================================================================
//  Errors
//=============================================================================

CF_ENUM(OSStatus)
{
    kAudioConverterErr_FormatNotSupported       = 'fmt?',
    kAudioConverterErr_OperationNotSupported    = 0x6F703F3F, // 'op??', integer used because of trigraph
    kAudioConverterErr_PropertyNotSupported     = 'prop',
    kAudioConverterErr_InvalidInputSize         = 'insz',
    kAudioConverterErr_InvalidOutputSize        = 'otsz',
        // e.g. byte size is not a multiple of the frame size
    kAudioConverterErr_UnspecifiedError         = 'what',
    kAudioConverterErr_BadPropertySizeError     = '!siz',
    kAudioConverterErr_RequiresPacketDescriptionsError = '!pkd',
    kAudioConverterErr_InputSampleRateOutOfRange    = '!isr',
    kAudioConverterErr_OutputSampleRateOutOfRange   = '!osr'
};

#if TARGET_OS_IPHONE
/*!
    @enum       AudioConverter errors (iPhone only)
    @abstract   iPhone-specific OSStatus results for AudioConverter
    
    @constant   kAudioConverterErr_HardwareInUse
                    Returned from AudioConverterFillComplexBuffer if the underlying hardware codec has
                    become unavailable, probably due to an interruption. In this case, your application
                    must stop calling AudioConverterFillComplexBuffer. If the converter can resume from an
                    interruption (see kAudioConverterPropertyCanResumeFromInterruption), you must
                    wait for an EndInterruption notification from AudioSession, and call AudioSessionSetActive(true)
                    before resuming.
    @constant   kAudioConverterErr_NoHardwarePermission
                    Returned from AudioConverterNew if the new converter would use a hardware codec
                    which the application does not have permission to use.
*/  
CF_ENUM(OSStatus)
{
    kAudioConverterErr_HardwareInUse 		= 'hwiu',
    kAudioConverterErr_NoHardwarePermission = 'perm'
};
#endif

//=============================================================================
//  Routines
//=============================================================================

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterNew
    @abstract   Create a new AudioConverter.

    @param      inSourceFormat
                    The format of the source audio to be converted.
    @param      inDestinationFormat
                    The destination format to which the audio is to be converted.
    @param      outAudioConverter
                    On successful return, points to a new AudioConverter instance.
    @result     An OSStatus result code.
    
    @discussion
                For a pair of linear PCM formats, the following conversions
                are supported:
                
                <ul>
                <li>addition and removal of channels, when the stream descriptions'
                mChannelsPerFrame does not match. Channels may also be reordered and removed
                using the kAudioConverterChannelMap property.</li>
                <li>sample rate conversion</li>
                <li>interleaving/deinterleaving, when the stream descriptions' (mFormatFlags &
                kAudioFormatFlagIsNonInterleaved) does not match.</li>
                <li>conversion between any pair of the following formats:</li>
                    <ul>
                    <li>8 bit integer, signed or unsigned</li>
                    <li>16, 24, or 32-bit integer, big- or little-endian. Other integral
                    bit depths, if high-aligned and non-packed, are also supported</li>
                    <li>32 and 64-bit float, big- or little-endian.</li>
                    </ul>
                </ul>
                
                Also, encoding and decoding between linear PCM and compressed formats is
                supported. Functions in AudioToolbox/AudioFormat.h return information about the
                supported formats. When using a codec, you can use any supported PCM format (as
                above); the converter will perform any necessary additional conversion between
                your PCM format and the one created or consumed by the codec.
*/
extern OSStatus
AudioConverterNew(      const AudioStreamBasicDescription * inSourceFormat,
                        const AudioStreamBasicDescription * inDestinationFormat,
                        AudioConverterRef __nullable * __nonnull outAudioConverter)      __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_2_0);


//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterNewSpecific
    @abstract   Create a new AudioConverter using specific codecs.

    @param      inSourceFormat
                    The format of the source audio to be converted.
    @param      inDestinationFormat
                    The destination format to which the audio is to be converted.
    @param      inNumberClassDescriptions
                    The number of class descriptions.
    @param      inClassDescriptions
                    AudioClassDescriptions specifiying the codec to instantiate.
    @param      outAudioConverter
                    On successful return, points to a new AudioConverter instance.
    @result     An OSStatus result code.
    
    @discussion
                This function is identical to AudioConverterNew(), except that the client may
                explicitly choose which codec to instantiate if there is more than one choice.
*/
extern OSStatus
AudioConverterNewSpecific(  const AudioStreamBasicDescription * inSourceFormat,
                            const AudioStreamBasicDescription * inDestinationFormat,
                            UInt32                              inNumberClassDescriptions,
                            const AudioClassDescription *       inClassDescriptions,
                            AudioConverterRef __nullable * __nonnull outAudioConverter)
                                                                                __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_0);

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterDispose
    @abstract   Destroy an AudioConverter.

    @param      inAudioConverter
                    The AudioConverter to dispose.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioConverterDispose(  AudioConverterRef   inAudioConverter)                   __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_2_0);

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterReset
    @abstract   Reset an AudioConverter

    @param      inAudioConverter
                    The AudioConverter to reset.
    @result     An OSStatus result code.
    
    @discussion
                Should be called whenever there is a discontinuity in the source audio stream
                being provided to the converter. This will flush any internal buffers in the
                converter.
*/

extern OSStatus
AudioConverterReset(    AudioConverterRef   inAudioConverter)                   __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_2_0);

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterGetPropertyInfo
    @abstract   Returns information about an AudioConverter property.

    @param      inAudioConverter
                    The AudioConverter to query.
    @param      inPropertyID
                    The property to query.
    @param      outSize
                    If non-null, on exit, the maximum size of the property value in bytes.
    @param      outWritable
                    If non-null, on exit, indicates whether the property value is writable.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioConverterGetPropertyInfo(  AudioConverterRef           inAudioConverter,
                                AudioConverterPropertyID    inPropertyID,
                                UInt32 * __nullable         outSize,
                                Boolean * __nullable        outWritable)        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_2_0);

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterGetProperty
    @abstract   Returns an AudioConverter property value.

    @param      inAudioConverter
                    The AudioConverter to query.
    @param      inPropertyID
                    The property to fetch.
    @param      ioPropertyDataSize
                    On entry, the size of the memory pointed to by outPropertyData. On 
                    successful exit, the size of the property value.
    @param      outPropertyData
                    On exit, the property value.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioConverterGetProperty(  AudioConverterRef           inAudioConverter,
                            AudioConverterPropertyID    inPropertyID,
                            UInt32 *                    ioPropertyDataSize,
                            void *                      outPropertyData)        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_2_0);

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterSetProperty
    @abstract   Sets an AudioConverter property value.

    @param      inAudioConverter
                    The AudioConverter to modify.
    @param      inPropertyID
                    The property to set.
    @param      inPropertyDataSize
                    The size in bytes of the property value.
    @param      inPropertyData
                    Points to the new property value.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioConverterSetProperty(  AudioConverterRef           inAudioConverter,
                            AudioConverterPropertyID    inPropertyID,
                            UInt32                      inPropertyDataSize,
                            const void *                inPropertyData)         __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_2_0);

//-----------------------------------------------------------------------------
/*!
    @typedef    AudioConverterInputDataProc
    @abstract   Callback function for supplying input data to AudioConverterFillBuffer.

    @param      inAudioConverter
                    The AudioConverter requesting input.
    @param      ioDataSize
                    On entry, the minimum number of bytes of audio data the converter
                    would like in order to fulfill its current FillBuffer request.
                    On exit, the number of bytes of audio data actually being provided
                    for input, or 0 if there is no more input.
    @param      outData
                    On exit, *outData should point to the audio data being provided
                    for input.
    @param      inUserData
                    The inInputDataProcUserData parameter passed to AudioConverterFillBuffer().
    @result     An OSStatus result code.
    
    @discussion
                <b>NOTE:</b> This API is now deprecated, 
                use AudioConverterFillComplexBuffer instead.

                This callback function supplies input to AudioConverterFillBuffer.
                
                The AudioConverter requests a minimum amount of data (*ioDataSize). The callback
                may return any amount of data. If it is less than than the minimum, the callback
                will simply be called again in the near future.

                The callback supplies a pointer to a buffer of audio data. The callback is
                responsible for not freeing or altering this buffer until it is called again.
                
                If the callback returns an error, it must return zero bytes of data.
                AudioConverterFillBuffer will stop producing output and return whatever output
                has already been produced to its caller, along with the error code. This
                mechanism can be used when an input proc has temporarily run out of data, but
                has not yet reached end of stream.
*/
typedef OSStatus
(*AudioConverterInputDataProc)( AudioConverterRef           inAudioConverter,
                                UInt32 *                    ioDataSize,
                                void * __nonnull * __nonnull outData,
                                void * __nullable           inUserData);

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterFillBuffer
    @abstract   Converts data supplied by an input callback function.

    @param      inAudioConverter
                    The AudioConverter to use.
    @param      inInputDataProc
                    A callback function which supplies the input data.
    @param      inInputDataProcUserData
                    A value for the use of the callback function.
    @param      ioOutputDataSize
                    On entry, the size of the buffer pointed to by outOutputData.
                    On exit, the number of bytes written to outOutputData
    @param      outOutputData
                    The buffer into which the converted data is written.
    @result     An OSStatus result code.
    
    @discussion
                <b>NOTE:</b> This API is now deprecated, 
                use AudioConverterFillComplexBuffer instead.

                Produces a buffer of output data from an AudioConverter. The supplied input
                callback function is called whenever necessary.             
*/
#if !TARGET_OS_IPHONE
extern OSStatus
AudioConverterFillBuffer(   AudioConverterRef               inAudioConverter,
                            AudioConverterInputDataProc     inInputDataProc,
                            void * __nullable               inInputDataProcUserData,
                            UInt32 *                        ioOutputDataSize,
                            void *                          outOutputData)
                            
                                __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);
#endif // !TARGET_OS_IPHONE

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterConvertBuffer
    @abstract   Converts data from an input buffer to an output buffer.

    @param      inAudioConverter
                    The AudioConverter to use.
    @param      inInputDataSize
                    The size of the buffer inInputData.
    @param      inInputData
                    The input audio data buffer.
    @param      ioOutputDataSize
                    On entry, the size of the buffer outOutputData. On exit, the number of bytes
                    written to outOutputData.
    @param      outOutputData
                    The output data buffer.
    @result
                Produces a buffer of output data from an AudioConverter, using the supplied
                input buffer.
    @discussion
                <b>WARNING:</b> this function will fail for any conversion where there is a
                variable relationship between the input and output data buffer sizes. This
                includes sample rate conversions and most compressed formats. In these cases,
                use AudioConverterFillComplexBuffer. Generally this function is only appropriate for
                PCM-to-PCM conversions where there is no sample rate conversion.
*/
extern OSStatus
AudioConverterConvertBuffer(    AudioConverterRef               inAudioConverter,
                                UInt32                          inInputDataSize,
                                const void *                    inInputData,
                                UInt32 *                        ioOutputDataSize,
                                void *                          outOutputData)  __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_2_0);

//-----------------------------------------------------------------------------
/*!
    @typedef    AudioConverterComplexInputDataProc
    @abstract   Callback function for supplying input data to AudioConverterFillComplexBuffer.

    @param      inAudioConverter
                    The AudioConverter requesting input.
    @param      ioNumberDataPackets
                    On entry, the minimum number of packets of input audio data the converter
                    would like in order to fulfill its current FillBuffer request. On exit, the
                    number of packets of audio data actually being provided for input, or 0 if
                    there is no more input.
    @param      ioData
                    On exit, the members of ioData should be set to point to the audio data
                    being provided for input.
    @param      outDataPacketDescription
                    If non-null, on exit, the callback is expected to fill this in with
                    an AudioStreamPacketDescription for each packet of input data being provided.
    @param      inUserData
                    The inInputDataProcUserData parameter passed to AudioConverterFillComplexBuffer().
    @result     An OSStatus result code.
    
    @discussion
                This callback function supplies input to AudioConverterFillComplexBuffer.
                
                The AudioConverter requests a minimum number of packets (*ioNumberDataPackets).
                The callback may return one or more packets. If this is less than the minimum,
                the callback will simply be called again in the near future.

                The callback manipulates the members of ioData to point to one or more buffers
                of audio data (multiple buffers are used with non-interleaved PCM data). The
                callback is responsible for not freeing or altering this buffer until it is
                called again.

                If the callback returns an error, it must return zero packets of data.
                AudioConverterFillComplexBuffer will stop producing output and return whatever
                output has already been produced to its caller, along with the error code. This
                mechanism can be used when an input proc has temporarily run out of data, but
                has not yet reached end of stream.
*/
typedef OSStatus
(*AudioConverterComplexInputDataProc)(  AudioConverterRef               inAudioConverter,
                                        UInt32 *                        ioNumberDataPackets,
                                        AudioBufferList *               ioData,
                                        AudioStreamPacketDescription * __nullable * __nullable outDataPacketDescription,
                                        void * __nullable               inUserData);

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterFillComplexBuffer
    @abstract   Converts data supplied by an input callback function, supporting non-interleaved
                and packetized formats.

    @param      inAudioConverter
                    The AudioConverter to use.
    @param      inInputDataProc
                    A callback function which supplies the input data.
    @param      inInputDataProcUserData
                    A value for the use of the callback function.
    @param      ioOutputDataPacketSize
                    On entry, the capacity of outOutputData expressed in packets in the
                    converter's output format. On exit, the number of packets of converted
                    data that were written to outOutputData.
    @param      outOutputData
                    The converted output data is written to this buffer.
    @param      outPacketDescription
                    If non-null, and the converter's output uses packet descriptions, then
                    packet descriptions are written to this array. It must point to a memory
                    block capable of holding *ioOutputDataPacketSize packet descriptions.
                    (See AudioFormat.h for ways to determine whether an audio format
                    uses packet descriptions).
    @result     An OSStatus result code.

    @discussion
                Produces a buffer list of output data from an AudioConverter. The supplied input
                callback function is called whenever necessary.
*/
extern OSStatus
AudioConverterFillComplexBuffer(    AudioConverterRef                   inAudioConverter,
                                    AudioConverterComplexInputDataProc  inInputDataProc,
                                    void * __nullable                   inInputDataProcUserData,
                                    UInt32 *                            ioOutputDataPacketSize,
                                    AudioBufferList *                   outOutputData,
                                    AudioStreamPacketDescription * __nullable outPacketDescription)
                                                                                __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);


//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterConvertComplexBuffer
    @abstract   Converts PCM data from an input buffer list to an output buffer list.

    @param      inAudioConverter
                    The AudioConverter to use.
    @param      inNumberPCMFrames
                    The number of PCM frames to convert.
    @param      inInputData
                    The source audio buffer list.
    @param      outOutputData
                    The converted output data is written to this buffer list.
    @result     An OSStatus result code.
    @discussion
                <b>WARNING:</b> this function will fail for any conversion where there is a
                variable relationship between the input and output data buffer sizes. This
                includes sample rate conversions and most compressed formats. In these cases,
                use AudioConverterFillComplexBuffer. Generally this function is only appropriate for
                PCM-to-PCM conversions where there is no sample rate conversion.
*/
extern OSStatus
AudioConverterConvertComplexBuffer( AudioConverterRef               inAudioConverter,
                                    UInt32                          inNumberPCMFrames,
                                    const AudioBufferList *         inInputData,
                                    AudioBufferList *               outOutputData)
                                                                                __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_5_0);

#if defined(__cplusplus)
}
#endif

CF_ASSUME_NONNULL_END

#endif // AudioToolbox_AudioConverter_h
