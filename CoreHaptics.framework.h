// ==========  CoreHaptics.framework/Headers/CHHapticPattern.h
/*==================================================================================================
 File:       CHHapticPattern.h
 
 Contains:   API for creating haptic patterns
 
 Copyright:  (c) 2018 by Apple, Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 ==================================================================================================*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSObjCRuntime.h>

#define CH_EXPORT __attribute__((visibility("default"))) extern

NS_ASSUME_NONNULL_BEGIN

@class CHHapticEvent;
@class CHHapticDynamicParameter;
@class CHHapticParameterCurve;

/*! @enum CHHapticPatternKey
	@abstract
		Keys used to define a CHHapticPattern.
 
	@discussion
		A definition for a haptic pattern consists of a heirarchical set of key/value pairs, starting at the topmost level with
		a "Version" and a "Pattern" key.  This marks the beginning of an array of event (CHHapticPatternKeyEvent) and parameter
 		(CHHapticPatternKeyParameter) definitions.  Each of these has an associated time which indicates when the event or parameter
 		will be delivered to the haptic engine.
 
	@constant   CHHapticPatternKeyVersion
		Indicates the version of the system for which the pattern was authored.
 		Value type: Real.

	@constant   CHHapticPatternKeyPattern
		Indicates the beginning of a haptic pattern definition.
 		Value type: Array.
 
	@constant   CHHapticPatternKeyEvent
		Indicates the beginning of a haptic event definition, which will include an event type, a time, and an optional set
		of event parameters (CHHapticPatternKeyEventParameters).
 		Value type: Dictionary.
 
	@constant   CHHapticPatternKeyEventType
		The type of haptic or audio event.
 		Value type: NSString (CHHapticEventType).
 
 	@constant	CHHapticPatternKeyEventDuration
 		The duration in seconds for an event.
		Value type: Real.

	@constant   CHHapticPatternKeyEventParameters
		Indicates the beginning of an array of event parameter (CHHapticPatternKeyParameter) definitions for a specific event.
 		Value type: Array.
 
	@constant	CHHapticPatternKeyParameter
		Indicates the beginning of a parameter definition, which will include a parameter type and value, and a time.
 		Value type: Dictionary.
 
	@constant	CHHapticPatternKeyParameterID
		The ID of the parameter.
		Value type: NSString (CHHapticEventParameterID for event parameters and CHHapticDynamicParameterID for dynamic parameters).

	@constant	CHHapticPatternKeyParameterValue
		The value of the parameter.  The range will vary with the parameter.
		Value type: Real.

	@constant	CHHapticPatternKeyTime
		The relative time for any event or parameter.  Units are seconds.
		Value type: Real.

	@constant   CHHapticPatternKeyEventWaveformPath
		For events of type CHHapticEventTypeAudioCustom, the path to the local file containing the audio waveform.
		Value type: NSString.
 */

typedef NSString *CHHapticPatternKey NS_TYPED_ENUM;

CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyVersion API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyPattern API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyEvent  API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyEventType API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyTime API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyEventDuration API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyEventWaveformPath API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyEventParameters API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyParameter API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyParameterID API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyParameterValue API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyParameterCurve API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticPatternKey CHHapticPatternKeyParameterCurveControlPoints API_AVAILABLE(ios(13.0), macos(10.15));

/*!	@class CHHapticPattern
	@abstract
		A set of one or more haptic events and/or Dynamic parameters/parameter curves.
	@discussion
		The passed-in arrays' contents are not owned by the pattern object.  Changes made to those arrays
		after a CHHapticPattern object is created have no effect on that object.
 */
CH_EXPORT API_AVAILABLE(ios(13.0), macos(10.15))
@interface CHHapticPattern : NSObject

/*!	@property duration
		Pattern duration is calculated as the start time of the pattern's last event or parameter, plus that event's duration if present.
 */
@property (readonly,nonatomic) NSTimeInterval duration;

- (nullable instancetype)init NS_UNAVAILABLE;

/*! @method initWithEvents:parameters:error
	@abstract
		Initialize a new CHHapticPattern.
	@param events
		An NSArray of CHHapticEvents.  Can be empty.
	@param parameters
		An NSArray of CHHapticDynamicParameters.  Can be empty.
 */
- (nullable instancetype) initWithEvents:(NSArray<CHHapticEvent *> *)events
							  parameters:(NSArray<CHHapticDynamicParameter *> *)parameters
								   error:(NSError **)outError;

/*! @method initWithEvents:parameterCurves:error
 	@abstract
 		Initialize a new CHHapticPattern with parameters modulated by parameter curves.
 	@param events
 		An NSArray of CHHapticEvents.  Can be empty.
 	@param parameterCurves
 		An NSArray of CHHapticParameterCurves.  Can be empty.
 */
- (nullable instancetype) initWithEvents:(NSArray<CHHapticEvent *> *)events
						 parameterCurves:(NSArray<CHHapticParameterCurve *> *)parameterCurves
								   error:(NSError **)outError;

/*! @method initWithDictionary:error
	@abstract
		Initialize a new CHHapticPattern using the passed-in NSDictionary.
	@param patternDict
		NSDictionary containing a pattern property list.
 */
- (nullable instancetype)initWithDictionary:(NSDictionary<CHHapticPatternKey, id> *)patternDict
									  error:(NSError **)outError;

/*! @method exportDictionaryAndReturnError:error
    @abstract
        Returns a NSDictionary representation of the contents of the pattern.
    @discussion
        Patterns containing custom audio resource IDs cannot be exported and will return nil
        with the error code set to CHHapticErrorCodeOperationNotPermitted.
 */
- (nullable NSDictionary<CHHapticPatternKey, id> *) exportDictionaryAndReturnError:(NSError **)outError  __attribute__((swift_error(null_result)));

@end

NS_ASSUME_NONNULL_END

// ==========  CoreHaptics.framework/Headers/CHHapticErrors.h
/*==================================================================================================
 File:       CHHapticErrors.h
 
 Contains:   Definitions for error codes returned by the CoreHaptics API.
 
 Copyright:  (c) 2018 by Apple, Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 ==================================================================================================*/

#define CH_EXPORT __attribute__((visibility("default"))) extern

#import <Foundation/NSError.h>

/*! @enum CHHapticErrorCode
	@abstract
		Error codes that may be returned from CHHapticEngine methods,
		e.g. `initAndReturnError:`, `startAndReturnError:` and others.
	@discussion
		Note that this is not a comprehensive list, and the underlying components could
		return other error codes (e.g. see kAudioUnitErr_* in AudioToolbox/AUComponent.h) from these
		methods as applicable.
 
	@constant	CHHapticErrorCodeEngineNotRunning
		Pattern playback was requested when the CHHapticEngine was not running.
 
	@constant	CHHapticErrorCodeOperationNotPermitted
		The requested operation cannot be performed in the current state.
 
	@constant	CHHapticErrorCodeEngineStartTimeout
		The haptic engine timed out while starting.
 
	@constant	CHHapticErrorCodeNotSupported
		The haptic engine is not supported by this hardware.
 
	@constant	CHHapticErrorCodeServerInitFailed
		The haptic server failed to initialize.
 
	@constant	CHHapticErrorCodeServerInterrupted
		The connection to the haptic server was lost.
 
	@constant	CHHapticErrorCodeInvalidPatternPlayer
		The current pattern player is invalid due to a server error.
 
	@constant	CHHapticErrorCodeInvalidPatternData
		The data handed to the pattern player was corrupt.

	@constant	CHHapticErrorCodeInvalidPatternDictionary
		The pattern dictionary handed to the pattern player was corrupt.

 	@constant	CHHapticErrorCodeInvalidAudioSession
		The AVAudioSession used to initialize the engine was invalid.
 
 	@constant	CHHapticErrorCodeInvalidParameterType
 		A pattern dictionary or parameter array contained an unknown or invalid parameter type.

	@constant	CHHapticErrorCodeInvalidEventType
		A pattern dictionary or event array contained an unknown or invalid event type.

	@constant	CHHapticErrorCodeInvalidEventTime
		A pattern dictionary or event array contained an invalid event time.

	@constant	CHHapticErrorCodeInvalidEventDuration
		A pattern dictionary or event array contained an invalid event duration.
 
 	@constant	CHHapticErrorCodeInvalidAudioResource
 		A pattern dictionary or event array contained a reference to an invalid audio resource.
 
 	@constant	CHHapticErrorCodeResourceNotAvailable
 		The requested operation could not be completed due to a limit on available resources.
 
 	@constant	CHHapticErrorCodeBadEventEntry
 		A pattern dictionary or event array contained a reference to an invalid event entry.
 
 	@constant	CHHapticErrorCodeBadParameterEntry
 		A pattern dictionary or event array contained a reference to an invalid parameter or parameter curve entry.
 
    @constant   CHHapticErrorCodeInvalidTime
        An invalid (e.g., negative) time was passed to a method requiring an NSTimeInterval.
 
 	@constant	CHHapticErrorCodeUnknownError
 		An uncategorized error occurred.

	@constant	CHHapticErrorCodeMemoryError
		The operation failed due to lack of memory.
 */

static NSErrorDomain CoreHapticsErrorDomain = @"com.apple.CoreHaptics";
typedef NS_ERROR_ENUM(CoreHapticsErrorDomain, CHHapticErrorCode)
{
	CHHapticErrorCodeEngineNotRunning			= -4805,
	CHHapticErrorCodeOperationNotPermitted		= -4806,
	CHHapticErrorCodeEngineStartTimeout			= -4808,
	CHHapticErrorCodeNotSupported				= -4809,
	CHHapticErrorCodeServerInitFailed			= -4810,
	CHHapticErrorCodeServerInterrupted			= -4811,
    CHHapticErrorCodeInvalidPatternPlayer		= -4812,
	CHHapticErrorCodeInvalidPatternData			= -4813,
	CHHapticErrorCodeInvalidPatternDictionary	= -4814,
	CHHapticErrorCodeInvalidAudioSession		= -4815,

    CHHapticErrorCodeInvalidParameterType       = -4820,
    CHHapticErrorCodeInvalidEventType           = -4821,
    CHHapticErrorCodeInvalidEventTime           = -4822,
    CHHapticErrorCodeInvalidEventDuration       = -4823,
	CHHapticErrorCodeInvalidAudioResource		= -4824,
	CHHapticErrorCodeResourceNotAvailable		= -4825,

    CHHapticErrorCodeBadEventEntry              = -4830,
    CHHapticErrorCodeBadParameterEntry          = -4831,
    
    CHHapticErrorCodeInvalidTime                = -4840,
    
	CHHapticErrorCodeUnknownError				= -4898,
	CHHapticErrorCodeMemoryError				= -4899
} API_AVAILABLE(ios(13.0), macos(10.15));
// ==========  CoreHaptics.framework/Headers/CHHapticEvent.h
/*==================================================================================================
 File:       CHHapticEvent.h
 
 Contains:   API for creating haptic events
 
 Copyright:  (c) 2018 by Apple, Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 ==================================================================================================*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSObjCRuntime.h>

#define CH_EXPORT __attribute__((visibility("default"))) extern

NS_ASSUME_NONNULL_BEGIN

@class CHHapticEventParameter;

/*! @enum CHHapticEventType
	@abstract
		Types of haptic and audio events.
 
 	@constant   CHHapticEventTypeHapticTransient
		An event which generates a haptic with a fixed length, such as a tap.  Transient events will complete on their own.  If a duration longer than the
 		haptic is provided, the pattern containing the event will be "padded" out to the duration specified.
 
 	@constant   CHHapticEventTypeHapticContinuous
		An event which generates a haptic of arbitrary length.  The event can behave as either Transient or Continuous depending on the value
 		of the CHHapticEventParameterIDSustained parameter.  These events also include an AR or ADR gain envelope that may be controlled via Event or
 		Dynamic parameters.
		See `CHHapticEventParameterIDAttackTime`, `CHHapticEventParameterIDDecayTime`, and `CHHapticEventParameterIDReleaseTime`.

 	@constant   CHHapticEventTypeAudioContinuous
		An event which generates an audio signal.  The event can behave as either Transient or Continuous depending on the value of the
		CHHapticEventParameterIDSustained parameter.  These events also include an AR or ADR gain envelope that may be controlled via Event or
 		Dynamic parameters.
		See `CHHapticEventParameterIDAttackTime`, `CHHapticEventParameterIDDecayTime`, and `CHHapticEventParameterIDReleaseTime`.

 	@constant   CHHapticEventTypeAudioCustom
		An event which generates an audio signal using a client-supplied waveform (see `CHHapticEngine(registerAudioResource:options:error)`).
		Currently, these behave as Transient events (i.e., no looping or enveloping).
 */

typedef NSString *CHHapticEventType NS_TYPED_ENUM;

CH_EXPORT
CHHapticEventType CHHapticEventTypeHapticTransient API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticEventType CHHapticEventTypeHapticContinuous API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticEventType CHHapticEventTypeAudioContinuous API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT
CHHapticEventType CHHapticEventTypeAudioCustom API_AVAILABLE(ios(13.0), macos(10.15));

/*!	@typedef CHHapticAudioResourceID
	@abstract
		Identifier for registered, client-loaded audio data which can be used as custom event types
 		(see `CHHapticEngine(registerAudioResource:options:error)`).
 */
typedef NSUInteger	CHHapticAudioResourceID;

/*!	@class CHHapticEvent
	@abstract
		The description of a single haptic/audio event, plus optional Event parameters which modify the event.
	@discussion
		CHHapticEvents have a relative time property to allow specifying the time relationship between events in a pattern.
 */
CH_EXPORT API_AVAILABLE(ios(13.0), macos(10.15))
@interface CHHapticEvent : NSObject

/*!	@property type
		The type of event.
 */
@property (readonly) CHHapticEventType type;

/*!	@property eventParameters
		NSArray of Event parameters.  Can be empty.
 */
@property (readonly) NSArray<CHHapticEventParameter *> *eventParameters;

/*!	@property relativeTime
		The relative time for this event versus the start time of the pattern.  Units are seconds.
 */
@property (readwrite) NSTimeInterval relativeTime;

/*!	@property duration
		The duration for this event.  Units are seconds.  If unset (0.0), Continuous event types will have no fixed end.
 */
@property (readwrite) NSTimeInterval duration;

- (nullable instancetype)init NS_UNAVAILABLE;

/*! @method initWithEventType:parameters:relativeTime
	@abstract
		Initialize a new CHHapticEvent.  This can only be used to create Transient event types (which do not require a duration).
	@param type
		The type of event.
	@param eventParams
		An NSArray of Event parameters.  Can be empty.
	@param time
		The relative time for this event versus the other events in the CHHapticPattern.
 */
- (instancetype)initWithEventType:(CHHapticEventType)type
					   parameters:(NSArray<CHHapticEventParameter *> *)eventParams
					 relativeTime:(NSTimeInterval)time;

/*! @method initWithEventType:parameters:relativeTime:duration
	@abstract
		Initialize a new CHHapticEvent, providing a duration.
	@param type
		The type of event.
	@param eventParams
		An NSArray of Event parameters.  Can be empty.
	@param time
		The relative time for this event versus the other events in the CHHapticPattern.
 	@param duration
 		For Continuous event types, the length of time before the event playback begins its release.
 		For Transient event types, the logical length of the event (used to determine pattern end and loop points).
 */
- (instancetype)initWithEventType:(CHHapticEventType)type
					   parameters:(NSArray<CHHapticEventParameter *> *)eventParams
					 relativeTime:(NSTimeInterval)time
						 duration:(NSTimeInterval)duration
;

/*! @method initWithAudioResourceID:parameters:relativeTime
	@abstract
		Initialize a new CHHapticEvent using a previously-loaded audio resource.
	@param resID
		A previously-registered audio resource ID (see `CHHapticEngine(registerAudioResource:options:error)`).
	@param eventParams
		An NSArray of Event parameters.  Can be empty.
	@param time
		The relative time for this event versus the other events in the CHHapticPattern.
 */
- (instancetype)initWithAudioResourceID:(CHHapticAudioResourceID)resID
							 parameters:(NSArray<CHHapticEventParameter *> *)eventParams
						   relativeTime:(NSTimeInterval)time;

/*! @method initWithAudioResourceID:parameters:relativeTime:duration
	@abstract
		Initialize a new CHHapticEvent using a previously-loaded audio resource.
	@param resID
		A previously-registered audio resource ID (see `CHHapticEngine(registerAudioResource:options:error)`).
	@param eventParams
		An NSArray of Event parameters.  Can be empty.
	@param time
		The relative time for this event versus the other events in the CHHapticPattern.
	@param duration
		The duration of this event in seconds.
 	@discussion
		If the specified duration is less than the duration of the audio resource, its playback will be truncated.  If it
		is greater, its playback will be padded with silence.  If zero, it will be ignored.
 */
- (instancetype)initWithAudioResourceID:(CHHapticAudioResourceID)resID
							 parameters:(NSArray<CHHapticEventParameter *> *)eventParams
						   relativeTime:(NSTimeInterval)time
							   duration:(NSTimeInterval)duration;

@end

NS_ASSUME_NONNULL_END

// ==========  CoreHaptics.framework/Headers/CHHapticEngine.h
/*==================================================================================================
 File:       CHHapticEngine.h
 
 Contains:   API for CHHapticEngine
 
 Copyright:  (c) 2018 by Apple, Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 ==================================================================================================*/

#import <Foundation/NSObjCRuntime.h>
#import <CoreHaptics/CHHapticEvent.h>
#import <CoreHaptics/CHHapticPatternPlayer.h>

#define CH_EXPORT __attribute__((visibility("default"))) extern

NS_ASSUME_NONNULL_BEGIN

/*! @define CHHapticTimeImmediate
    @abstract
        A floating point constant representing the time "as soon as possible". This time value should be used
        whenever an app wishes to schedule a command at the soonest possible moment without the need to
        synchronize with other media.
 */
#define CHHapticTimeImmediate (NSTimeInterval)0.0f

@class CHHapticPattern;
@class AVAudioSession;
@protocol CHHapticDeviceCapability;

/*!	@typedef CHHapticCompletionHandler
	@abstract
		A block which is called asynchronously when a call to start or stop the haptic engine completes.
	@param error
		If the call fails, this is set to a valid NSError describing the error.
	@discussion
		All callbacks are delivered on an internal queue which guarantees proper delivery order and allows reentrant calls to the API.
 */
typedef void (^CHHapticCompletionHandler)(NSError *_Nullable error);

/*!	@enum CHHapticEngineFinishedAction
	@abstract
		Constants indicating what the engine should do in response to the finished handler being called.

	@constant	CHHapticEngineFinishedActionStopEngine
 		Stop the engine.  This is useful if the client knows that the client is about to go inactive.
 
	@constant	CHHapticEngineFinishedActionLeaveEngineRunning
 		Do not stop the engine.  This is useful if the client expects more activity.
 */
typedef NS_ENUM(NSInteger, CHHapticEngineFinishedAction) {
	CHHapticEngineFinishedActionStopEngine	= 1,
	CHHapticEngineFinishedActionLeaveEngineRunning	= 2
};

/*!	@typedef CHHapticEngineFinishedHandler
	@abstract
		A block which is called asynchronously when the engine detects that all active pattern players have finished.  The
 		return value tells the system what action to take as a result of this (see `CHHapticEngineFinishedAction`).
	@param error
		If the engine detects the players have stopped due to an error, this is set to a valid NSError describing the error.
	@discussion
		All callbacks are delivered on an internal queue which guarantees proper delivery order and allows reentrant calls to the API.
 */
typedef CHHapticEngineFinishedAction (^CHHapticEngineFinishedHandler)(NSError *_Nullable error) CF_SWIFT_BRIDGED_TYPEDEF;

/*!	@enum CHHapticEngineStoppedReason
 	@abstract
 		Constants indicating the reason why the CHHapticEngine has stopped.
 
 	@constant	CHHapticEngineStoppedReasonAudioSessionInterrupt
		The AVAudioSession bound to this engine has been interrupted.
 
 	@constant	CHHapticEngineStoppedReasonApplicationSuspended
 		The application owning this engine has been suspended (i.e., put into the background).
 
	@constant	CHHapticEngineStoppedReasonIdleTimeout
		The engine has stopped due to an idle timeout when the engine's `autoShutdownEnabled` property was set to YES.
 
	@constant	CHHapticEngineStoppedReasonNotifyWhenFinished
 		The engine has stopped due to a call to a `CHHapticEngineFinishedHandler` returning `CHHapticEngineFinishedActionStopEngine`.
 
 	@constant	CHHapticEngineStoppedReasonSystemError
 		An error has occurred.
 */

typedef NS_ENUM(NSInteger, CHHapticEngineStoppedReason) {
	CHHapticEngineStoppedReasonAudioSessionInterrupt	= 1,
	CHHapticEngineStoppedReasonApplicationSuspended		= 2,
	CHHapticEngineStoppedReasonIdleTimeout				= 3,
	CHHapticEngineStoppedReasonNotifyWhenFinished		= 4,
	CHHapticEngineStoppedReasonSystemError				= -1
};

/*!	@typedef CHHapticEngineStoppedHandler
	@abstract
		A block which is called asynchronously when the engine has stopped due to external causes such as
 		an audio session interruption or autoShutdown.
	@param stoppedReason
		This constant indicates the reason why the engine stopped.
	@discussion
		This handler is NOT called if the client directly calls stopWithCompletionHandler:.
		All callbacks are delivered on an internal queue which guarantees proper delivery order and allows reentrant calls to the API.
 */
typedef void (^CHHapticEngineStoppedHandler)(CHHapticEngineStoppedReason stoppedReason);

/*!	@typedef CHHapticEngineResetHandler
	@abstract
		A block which is called asynchronously if the haptic engine has reset itself due a server failure.
	@discussion
		In response to this handler, the app must reload all custom audio resources and recreate all necessary
		pattern players.  The engine must of course be restarted.  CHHapticPatterns do not need to be re-created.
		All callbacks are delivered on an internal queue which guarantees proper delivery order and allows reentrant calls to the API.
 */
typedef void (^CHHapticEngineResetHandler)(void);

/*!	@class CHHapticEngine
	@abstract
		Represents the connection with the haptic server.
 */
CH_EXPORT API_AVAILABLE(ios(13.0), macos(10.15))
@interface CHHapticEngine : NSObject

/*! @method capabilitiesForHardware
 	@abstract
 		Get the protocol that describes haptic and audio capabilities on this device.
 	@discussion
 		Detailed description on the capability protocol is in CHHapticDeviceCapability.h.
 */
+ (id<CHHapticDeviceCapability>)capabilitiesForHardware;

/*!	@property currentTime
		The absolute time from which all current and future event times may be calculated.
		The units are seconds.
 */
@property (readonly) NSTimeInterval currentTime;

/*!	@property stoppedHandler
	@abstract
		The engine will call this block when it has stopped due to external causes (such as
		an audio session interruption or the app going into the background).  It will NOT be called
 		if the client calls stopWithCompletionHandler:.
	@discussion
		In general, callbacks arrive on a non-main thread and it is the client's responsibility to handle
		it in a thread-safe manner.
 */

@property (readwrite,atomic) CHHapticEngineStoppedHandler stoppedHandler;

/*!	@property resetHandler
	@abstract
		This block will called asynchronously if the haptic engine has to reset itself after a server failure.
	@discussion
 		In response to this handler being called, the client must release all haptic pattern players
 		and recreate them.  All CHHapticPattern objects and CHHapticEngine properties will have been preserved.
 		In general, callbacks arrive on a non-main thread and it is the client's responsibility to handle
		it in a thread-safe manner.
 */
@property (readwrite,atomic) CHHapticEngineResetHandler resetHandler;

/*!	@property playsHapticsOnly
		If set to YES, the CHHapticEngine will ignore all events of type CHHapticEventTypeAudio and play only haptic events.
	@discussion
		This behavior change will only take effect after the engine is stopped and restarted.
		The default is NO.
 */
@property (readwrite,nonatomic) BOOL playsHapticsOnly;

/*!	@property isMutedForAudio
 		When set to YES, the CHHapticEngine mutes audio playback from its players.
 	@discussion
 		Default is NO.
 */
@property (readwrite,nonatomic) BOOL isMutedForAudio;

/*!	@property isMutedForHaptics
 		When set to YES, the CHHapticEngine mutes haptic playback from its players.
 	@discussion
 		Default is NO.
 */
@property (readwrite,nonatomic) BOOL isMutedForHaptics;

/*! @property autoShutdownEnabled
	@abstract
		When auto shutdown is enabled, the haptic engine can start and stop the hardware dynamically,
		to conserve power.
	@discussion
		To conserve power, it is advised that the client stop the haptic engine when not in use.
		But when auto shutdown is enabled, the haptic engine will stop the hardware if it was running
		idle for a certain duration, and restart it later when required.
		Note that, because this operation is dynamic, it may affect the start times of the pattern players
		(e.g. `CHHapticPatternplayer`), if the engine has to resume from its shutdown state.

		This feature is disabled by default, but the client can enable it if needed.
 */
@property (nonatomic, getter=isAutoShutdownEnabled) BOOL autoShutdownEnabled;

- (nullable instancetype)init NS_UNAVAILABLE;

/*! @method initAndReturnError:
	@abstract
		Create an instance of the CHHapticEngine.
	@discussion
		More than one instance may exist within a process.  Each will function independently of the others.
 */
- (nullable instancetype)initAndReturnError:(NSError **)error NS_DESIGNATED_INITIALIZER;

/*! @method initWithAudioSession:error
	@abstract
		Create an instance of the CHHapticEngine and associate it with an audio session.  If 'audioSession' is nil,
 		the engine will create its own.
	@discussion
		More than one instance may exist within a process.  Each will function independently of the others, but all
 		CHHapticEngines which share an audio session will have identical audio behavior with regard to interruptions, etc.
 */
- (nullable instancetype)initWithAudioSession:(nullable AVAudioSession *)audioSession error:(NSError **)error NS_DESIGNATED_INITIALIZER;

/*! @method startWithCompletionHandler:
	@abstract
		Asynchronously start the engine. The handler will be called when the operation completes.
 	@discussion
 		The handler is guaranteed to be called on either success or failure.
 */
- (void)startWithCompletionHandler:(CHHapticCompletionHandler _Nullable)completionHandler;

/*! @method startAndReturnError:
	@abstract
		Start the engine and block until the engine has started.
 	@discussion
 		This method will return NO upon failure, and outError will be set to a valid NSError describing the error.
 */
- (BOOL)startAndReturnError:(NSError **)outError;

/*! @method stopWithCompletionHandler:
	@abstract
		Asynchronously stop the engine.  The handler will be called when the operation completes.
	@discussion
		The handler is guaranteed to be called on either success or failure.
 */
- (void)stopWithCompletionHandler:(CHHapticCompletionHandler _Nullable)completionHandler;

/*!	@method notifyWhenPlayersFinished:
 	@abstract
 		Tell the engine to asynchronously call the passed-in handler when all active pattern players associated
 		with this engine have stopped.
 	@param finishedHandler
 		The block that will be called asynchronously.  The return value of this block determines the action the
 		engine will take when the block finishes (see `CHHapticEngineFinishedHandler`).
 	@discussion
 		If additional players are started after this call is made, they will delay the callback.
 		If no players are active or the engine is stopped, the callback will happen immediately.
 */
- (void)notifyWhenPlayersFinished:(CHHapticEngineFinishedHandler)finishedHandler;

/*! @method createPlayerWithPattern:error
	@abstract
		Factory method for creating a CHHapticPatternPlayer from a CHHapticPattern.
	@param pattern
		The pattern to be played.
 */
- (nullable id<CHHapticPatternPlayer>)createPlayerWithPattern:(CHHapticPattern *)pattern
																	error:(NSError **)outError;

/*! @method createAdvancedPlayerWithPattern:error
	@abstract
		Factory method for creating a CHHapticAdvancedPatternPlayer from a CHHapticPattern.
	@param pattern
		The pattern to be played.
 */
- (nullable id<CHHapticAdvancedPatternPlayer>)createAdvancedPlayerWithPattern:(CHHapticPattern *)pattern
																		error:(NSError **)outError;

/*! @method registerAudioResource:options:error
	@abstract
		Register an external audio file for use as a custom waveform.
	@param resourceURL
 		A URL referencing the location of the audio file to be registered.
 	@param options
 		A dictionary containing key/value pairs describing how this resource should be played.
 	@param outError
 		If register operation fails, this will be set to a valid NSError describing the error.
 */
- (CHHapticAudioResourceID)registerAudioResource:(NSURL *)resourceURL
										 options:(NSDictionary *)options
										   error:(NSError **)outError __attribute__((swift_error(zero_result)));

/*!	@method unregisterAudioResource:error
 	@abstract
 		Unregister and remove a previously-registered audio resource.
 	@param resourceID
 		The resource ID that was returned when the resource was registered.
 	@param outError
 		If the unregister operation fails, this will be set to a valid NSError describing the error.
 */
- (BOOL)unregisterAudioResource:(CHHapticAudioResourceID)resourceID
						  error:(NSError **)outError;

/*! @method playPatternFromURL:error
	@abstract
		Simple one-shot call to play a pattern specified by a URL.
 	@param fileURL
 		The URL of the file containing a haptic/audio pattern dictionary.
 	@param outError
 		If the operation fails, this will be set to a valid NSError describing the error.
 	@discussion
 		The engine should be started prior to calling this method if low latency is desired. If this is not done,
 		this method will start it, which can cause a significant delay.
 */
- (BOOL)playPatternFromURL:(NSURL *)fileURL
					 error:(NSError **)outError;

/*! @method playPatternFromData:error
 	@abstract
 		Simple one-shot call to play a pattern specified by NSData.
	@param data
 		The NSData containing a haptic/audio pattern dictionary.
 	@param outError
 		If the operation fails, this will be set to a valid NSError describing the error.
 	@discussion
 		The engine should be started prior to calling this method if low latency is desired. If this is not done,
 		this method will start it, which can cause a significant delay.
 */
- (BOOL)playPatternFromData:(NSData *)data
					  error:(NSError **)outError;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreHaptics.framework/Headers/CHHapticDeviceCapability.h
/*==================================================================================================
 File:       CHHapticDeviceCapability.h
 
 Contains:   API for determining haptic and audio capabilities of the current device.
 
 Copyright:  (c) 2018 by Apple, Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 ==================================================================================================*/

#import <CoreHaptics/CHHapticParameter.h>
#import <CoreHaptics/CHHapticEvent.h>

NS_ASSUME_NONNULL_BEGIN

/*!	@protocol CHHapticParameterAttributes
 	@abstract
 		A protocol for querying mininum, maximum, and default values for a CHHapticEventParameter or CHHapticDynamicParameter.
 */
CH_EXPORT API_AVAILABLE(ios(13.0), macos(10.15))
@protocol CHHapticParameterAttributes <NSObject>

/*! @property minValue
 	@abstract
 		The minimum value for the parameter.
 */
@property (readonly) float minValue;

/*! @property maxValue
 	@abstract
 		The maximum value for the parameter.
 */
@property (readonly) float maxValue;

/*! @property maxValue
 	@abstract
 		The default value for the parameter.
 */
@property (readonly) float defaultValue;

@end

/*!	@protocol CHHapticDeviceCapability
	@abstract
		A protocol which defines properties describing haptics and audio capabilities for a particular device.
		These properties include limitations and ranges of parameters.
 */
CH_EXPORT API_AVAILABLE(ios(13.0))
@protocol CHHapticDeviceCapability

/*! @property supportsHaptics
	@abstract
		Returns YES if the hardware supports haptic event playback.
 */
@property (readonly) BOOL supportsHaptics;

/*! @property supportsAudio
	@abstract
		Returns YES if the hardware supports audio event playback.
 */
@property (readonly) BOOL supportsAudio;

/*! @method attributesForEventParameter:
 	@abstract
 		Return information about the given CHHapticEventParameter as it applies to the specified event type.
 	@param inParameter
 		A CHHapticEventParameter to be queried.
 	@param type
 		A CHHapticEventType to be queried.
 	@param outError
 		If the operation fails, this will be set to a valid NSError describing the error.
 	@discussion
 		These values may vary across different device types.
 */
- (nullable id<CHHapticParameterAttributes>) attributesForEventParameter:(CHHapticEventParameterID)inParameter
															   eventType:(CHHapticEventType)type
																   error:(NSError**)outError;

/*! @method attributesForEventParameter:
 	@abstract
 		Return information about the given CHHapticDynamicParameter.
 	@param inParameter
 		A CHHapticDynamicParameter to be queried.
 	@param outError
 		If the operation fails, this will be set to a valid NSError describing the error.
 	@discussion
 		These values may vary across different device types.
 */
- (nullable id<CHHapticParameterAttributes>) attributesForDynamicParameter:(CHHapticDynamicParameterID)inParameter
																	 error:(NSError**)outError;
@end

NS_ASSUME_NONNULL_END
// ==========  CoreHaptics.framework/Headers/CoreHaptics.h
/*==================================================================================================
 File:       CoreHaptics.h

 Contains:   umbrella header for CoreHaptics API

 Copyright:  (c) 2018 by Apple, Inc., all rights reserved.

 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:

 http://developer.apple.com/bugreporter/

 ==================================================================================================*/

#import <CoreHaptics/CHHapticDeviceCapability.h>
#import <CoreHaptics/CHHapticErrors.h>
#import <CoreHaptics/CHHapticEngine.h>
#import <CoreHaptics/CHHapticEvent.h>
#import <CoreHaptics/CHHapticParameter.h>
#import <CoreHaptics/CHHapticPattern.h>
#import <CoreHaptics/CHHapticPatternPlayer.h>
// ==========  CoreHaptics.framework/Headers/CHHapticParameter.h
/*==================================================================================================
 File:       CHHapticParameter.h
 
 Contains:   API for creating event and dynamic parameters
 
 Copyright:  (c) 2018 by Apple, Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 ==================================================================================================*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSObjCRuntime.h>

#define CH_EXPORT __attribute__((visibility("default"))) extern

NS_ASSUME_NONNULL_BEGIN

/*! @enum CHHapticEventParameterID
	@abstract
		Parameters used to modify individual haptic and/or audio events.
	@discussion
		Event parameters are specified as part of the creation of a CHHapticEvent or in an event definition in a haptic pattern.
 		The combination of Event parameters will determine the character of the haptic or audio event.

	@constant   CHHapticEventParameterIDHapticIntensity
		The perceived intensity (volume) of a haptic event.
 		Range: 0.0 (maximum attenuation) to 1.0 (no attenuation).
 
	@constant   CHHapticEventParameterIDHapticSharpness
		Depending on the event's signal content, this may map to frequency, frequency content (i.e., filtering),
 		or some other signal processing.
		Range: 0.0 (least sharp) to 1.0 (most sharp).

 	@constant	CHHapticEventParameterIDAttackTime
		The attack time adjuster for an event's envelope.
		Range: 0.0 to 1.0, with default: 0.0 (shortest attack time).  Higher values increase the time exponentially.
		Not all event types respond to this parameter.
 
	@constant	CHHapticEventParameterIDDecayTime
		The decay time adjuster for a Transient event's envelope.
		Range: 0.0 to 1.0, with default: 0.0 (shortest decay time).  Higher values increase the time exponentially.
		Not all Transient event types respond to this parameter.
 
	@constant	CHHapticEventParameterIDReleaseTime
		The release time adjuster for a Continuous event's envelope.
 		Range: 0.0 to 1.0, with default: 0.0 (shortest release time).  Higher values increase the time exponentially.
		Not all Continuous event types respond to this parameter.
 
	@constant	CHHapticEventParameterIDSustained
		A boolean (1.0 or 0.0) which indicates whether a Continuous event sustains for its specified duration
		(using an Attack/Release envelope) or whether the event ends when its envelope decay segment reaches its minimum
		(i.e., using an Attack/Decay envelope with no sustain).  Default: 1.0 (sustained, Attack/Release).
 
	@constant   CHHapticEventParameterIDAudioVolume
		The volume of an audio event.
		Range: 0.0 (maximum attenuation) to 1.0 (no attenuation).
 
	@constant	CHHapticEventParameterIDAudioPitch
		The pitch adjuster for audio events.
		Range: -1.0 (lowest pitch) to 1.0 (highest pitch).
 
	@constant   CHHapticEventParameterIDAudioPan
		The stereo panning for an audio event.
		Range: -1.0 (panned full left) to 1.0 (panned full right).  Default: 0.0 (panned center).
 
	@constant	CHHapticEventParameterIDAudioBrightness
		The high frequency content an audio event.
		Range: 0.0 (frequency content reduced the most) to 1.0 (no reduction of frequency content).  Default: 1.0.
*/

typedef NSString *CHHapticEventParameterID NS_TYPED_ENUM;

CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDHapticIntensity API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDHapticSharpness API_AVAILABLE(ios(13.0), macos(10.15));

CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDAttackTime API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDDecayTime API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDReleaseTime API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDSustained API_AVAILABLE(ios(13.0), macos(10.15));

CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDAudioVolume API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDAudioPitch API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDAudioPan API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticEventParameterID CHHapticEventParameterIDAudioBrightness API_AVAILABLE(ios(13.0), macos(10.15));

/*!	@enum CHHapticDynamicParameterID
	@abstract
		Parameters used to dynamically modify all haptic or audio events within a pattern.
	@discussion
		Dynamic parameters are not tied to specific events; each dynamic parameter modifies (modulates) the
		effect of the corresponding event parameter for events which respond to the parameter.
 
		The CHHapticDynamicParameterIDHaptic types only affect haptic event types, and the CHHapticDynamicParameterIDAudio
		types only affect audio event types.  Not all CHHapticDynamicParameterIDs will have an effect on every CHHapticEventType.
 
	@constant   CHHapticDynamicParameterIDHapticIntensityControl
		Adjusts the intensity of all active and future haptic events.
		Range: 0.0 (event intensities reduced by the maximum amount) to 1.0 (no effect on event intensities).
 		Default: 1.0.
 
	@constant   CHHapticDynamicParameterIDHapticSharpnessControl
		This will adjust the frequency, frequency content (i.e., filtering), or other aspects of all active and future haptic events.
		Range: -1.0 (less sharp) to 1.0 (more sharp).  Default: 0.0 (no effect).
 
	@constant	CHHapticDynamicParameterIDHapticAttackTimeControl
		Adjusts the envelope attack time of all active and future haptic events.
		Range: -1.0 (event attacks shorter) to 1.0 (event attacks longer).  Default: 0.0 (no effect).
		Not all haptic event types respond to this parameter.
 
	@constant	CHHapticDynamicParameterIDHapticDecayTimeControl
 		Adjusts the envelope decay time of all active and future Transient haptic events.
		Range: -1.0 (event decays shorter) to 1.0 (event decays longer).  Default: 0.0 (no effect).
		Not all haptic event types respond to this parameter.

	@constant	CHHapticDynamicParameterIDHapticReleaseTimeControl
		Adjusts the envelope release time of all active and future Continuous haptic events.
		Range: -1.0 (event releases shorter) to 1.0 (event releases longer).  Default: 0.0 (no effect).
		Not all haptic event types respond to this parameter.

	@constant	CHHapticDynamicParameterIDAudioVolumeControl
		Adjusts the volume of all active and future audio events.
		Range: 0.0 (event intensities reduced by the maximum amount) to 1.0 (no effect).
		Default: 1.0.

	@constant	CHHapticDynamicParameterIDAudioPanControl
		Adjusts the panning of all active and future audio events.
		Range: -1.0 (events panned more left) to 1.0 (event panned more right).  Default: 0.0 (no effect).

	@constant	CHHapticDynamicParameterIDAudioBrightnessControl
		Adjusts the high frequency content of all active and future audio events.
		Range: -1.0 (more filtering) to 1.0 (less filtering).  Default: 0.0 (no effect).

	@constant	CHHapticDynamicParameterIDAudioPitchControl
		Adjusts the transposition of the audio event.
		Range: -1.0 to 1.0.  Negative values decrease pitch; positive values increase pitch.
 		Default: 0.0 (no effect).

	@constant	CHHapticDynamicParameterIDAudioAttackTimeControl
		Adjusts the envelope attack time of all active and future audio events.
		Range: -1.0 (event attacks shorter) to 1.0 (event attacks longer).  Default: 0.0 (no effect).
		Not all audio event types respond to this parameter.

	@constant	CHHapticDynamicParameterIDAudioDecayTimeControl
		Adjusts the envelope decay time of all active and future Transient audio events.
		Range: -1.0 (event decays shorter) to 1.0 (event decays longer).  Default: 0.0 (no effect).
		Not all audio event types respond to this parameter.

	@constant	CHHapticDynamicParameterIDAudioReleaseTimeControl
		Adjusts the envelope release time of all active and future Continuous audio events.
		Range: -1.0 (event releases shorter) to 1.0 (event releases longer).  Default: 0.0 (no effect).
		Not all audio event types respond to this parameter.
 */

typedef NSString *CHHapticDynamicParameterID NS_TYPED_ENUM;

CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDHapticIntensityControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDHapticSharpnessControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDHapticAttackTimeControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDHapticDecayTimeControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDHapticReleaseTimeControl API_AVAILABLE(ios(13.0), macos(10.15));

CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDAudioVolumeControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDAudioPanControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDAudioBrightnessControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDAudioPitchControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDAudioAttackTimeControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDAudioDecayTimeControl API_AVAILABLE(ios(13.0), macos(10.15));
CH_EXPORT CHHapticDynamicParameterID CHHapticDynamicParameterIDAudioReleaseTimeControl API_AVAILABLE(ios(13.0), macos(10.15));

/*!
	@class CHHapticEventParameter
	@abstract
		A CHHapticEventParameter contains a CHHapticEventParameterID/value pair which helps determine the initial character
		of a haptic or audio event.
 */
CH_EXPORT API_AVAILABLE(ios(13.0), macos(10.15))
@interface CHHapticEventParameter : NSObject

/*!
	@property parameterID
		The ID of the event parameter to use.
 */
@property (readonly) CHHapticEventParameterID parameterID;

/*!
	@property value
		The value of the event parameter.
 */
@property (readwrite) float value;

- (nullable instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithParameterID:(CHHapticEventParameterID)parameterID
							  value:(float)value NS_DESIGNATED_INITIALIZER;

@end

/*!	@class CHHapticDynamicParameter
	@abstract
		A CHHapticDynamicParameter contains a CHHapticDynamicParameterID/value pair which will modify (modulate) the ongoing character
		of a haptic or audio event.
	@discussion
		CHHapticDynamicParameters have a relative time property to allow specifying the time relationship between parameters in a pattern.
 */

CH_EXPORT API_AVAILABLE(ios(13.0), macos(10.15))
@interface CHHapticDynamicParameter : NSObject

/*!	@property parameterID
		The ID of the dynamic parameter to use.
 */
@property (readonly) CHHapticDynamicParameterID parameterID;

/*!	@property value
		The value of the parameter.
 */
@property (readwrite) float value;

/*!	@property relativeTime
		The time at which the parameter should be applied, relative to the start time for the pattern.
 */
@property (readwrite) NSTimeInterval relativeTime;

- (nullable instancetype)init NS_UNAVAILABLE;

/*! @method initWithParameterID:value:relativeTime
	@abstract
		Initialize a CHHapticDynamicParameter with a parameter ID, value, and relative time.
	@param parameterID
		The CHHapticDynamicParameterID for the desired parameter change.
	@param value
		The value for that parameter.
	@param time
		The time at which this parameter should be applied, relative to the start time of the pattern.
 */
- (instancetype)initWithParameterID:(CHHapticDynamicParameterID)parameterID
							  value:(float)value
					   relativeTime:(NSTimeInterval)time NS_DESIGNATED_INITIALIZER;
@end

/*!	@class CHHapticParameterCurveControlPoint
 	@abstract
 		A CHHapticParameterCurveControlPoint contains a time/value pair for a single control point within a CHHapticParameterCurve.
 	@discussion
 		The relativeTime property specifies the amount of time elapsed since the start of the CHHapticParameterCurve before the
 		value is reached.
 */
CH_EXPORT API_AVAILABLE(ios(13.0), macos(10.15))
@interface CHHapticParameterCurveControlPoint : NSObject

@property (readwrite) NSTimeInterval	relativeTime;
@property (readwrite) float 			value;

- (nullable instancetype)init NS_UNAVAILABLE;

/*! @method initWithRelativeTime:value
 	@abstract
 		Initialize a CHHapticParameterCurveControlPoint with a relative time and value.
 	@param value
 		The value of the associated parameter.
 	@param time
 		The time at which the associated parameter will reach this value, relative to the start time of the parameter curve.
 */
- (instancetype)initWithRelativeTime:(NSTimeInterval)time
							   value:(float)value NS_DESIGNATED_INITIALIZER;
@end


/*!	@class CHHapticParameterCurve
 	@abstract
 		A CHHapticParameterCurve is a set of CHHapticParameterCurveControlPoints which describe the control (inflection) points
 		for the parameter values to be applied to the associated pattern.
 	@discussion
 		The CHHapticParameterCurve generates an interpolated value output which passed through each control point at its
 		associated relative time.  These times will all be relative to the start time of the CHHapticParameterCurve within the
 		playing pattern.
 */
@interface CHHapticParameterCurve : NSObject

@property (readonly) CHHapticDynamicParameterID						parameterID;
@property (readwrite) NSTimeInterval									relativeTime;
@property (readonly)  NSArray<CHHapticParameterCurveControlPoint*> * controlPoints;

- (nullable instancetype)init NS_UNAVAILABLE;

/*! @method initWithParameterID:controlPoints:relativeTime
 	@abstract
 		Initialize a CHHapticParameterCurve with a parameter ID, time, and an array of CHHapticParameterCurveControlPoint.
 	@param parameterID
 		The CHHapticDynamicParameterID for the desired parameter.
	@param controlPoints
		An array of CHHapticParameterCurveControlPoints.
 	@param relativeTime
 		The time at which this parameter curve should start, relative to the start time of the CHHapticPattern to which this
 		parameter curve belongs.
 */
- (instancetype)initWithParameterID:(CHHapticDynamicParameterID)parameterID
					  controlPoints:(NSArray<CHHapticParameterCurveControlPoint *> *)controlPoints
					   relativeTime:(NSTimeInterval)relativeTime NS_DESIGNATED_INITIALIZER;

@end
NS_ASSUME_NONNULL_END

// ==========  CoreHaptics.framework/Headers/CHHapticPatternPlayer.h
/*==================================================================================================
 File:       CHHapticPatternPlayer.h
 
 Contains:   API for playing haptic patterns
 
 Copyright:  (c) 2018 by Apple, Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 ==================================================================================================*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSObjCRuntime.h>

#define CH_EXPORT __attribute__((visibility("default"))) extern

@class CHHapticDynamicParameter;
@class CHHapticParameterCurve;

NS_ASSUME_NONNULL_BEGIN

/*!	@protocol CHHapticPatternPlayer
	@abstract
		A protocol which defines operations for starting, stopping, and sending parameters to a pattern player.
	@discussion
		Instances of these objects are created via the factory methods such as
        `CHHapticEngine(createPlayerWithPattern:error)`.
 */
CH_EXPORT API_AVAILABLE(ios(13.0), macos(10.15))
@protocol CHHapticPatternPlayer <NSObject>

/*! @method startAtTime:error
	@abstract
		Start playing the pattern at the specified time (see `CHHapticEngine(currentTime)`).
		If 'time' is set to `CHHapticTimeImmediate`, the pattern is started as soon as possible.
 */
- (BOOL)startAtTime:(NSTimeInterval)time error:(NSError **)outError;

/*! @method stopAtTime:error
	@abstract
		Stop playing the pattern at the specified time (see `CHHapticEngine(currentTime)`).
		If 'time' is set to `CHHapticTimeImmediate`, the pattern is stopped as soon as possible.
 */
- (BOOL)stopAtTime:(NSTimeInterval)time error:(NSError **)outError;

/*! @method sendParameters:atTime:error
	@abstract
		Send an array of CHHapticDynamicParameters, starting at the specified time (see `CHHapticEngine(currentTime)`).
		If 'time' is set to `CHHapticTimeImmediate`, the parameters are sent as soon as possible.
 */
- (BOOL)sendParameters:(NSArray<CHHapticDynamicParameter *> *)parameters
				atTime:(NSTimeInterval)time
				 error:(NSError **)outError;

/*! @method scheduleParameterCurve:atTime:error
 	@abstract
 		Schedule a CHHapticParameterCurve, starting at the specified time (see `CHHapticEngine(currentTime)`).
 		If 'time' is set to `CHHapticTimeImmediate`, the parameter curve is scheduled as soon as possible.
 	@discussion
 		This method overrides the relativeTime property of the passed-in CHHapticParameterCurve,
 		setting it to this method's 'time' argument. All the curve's control point times will then be
 		calculated relative to that time.
 */

- (BOOL)scheduleParameterCurve:(CHHapticParameterCurve *)parameterCurve
						atTime:(NSTimeInterval)time
						 error:(NSError **)outError;

/*! @method cancelAndReturnError:
	@abstract
		Removes all pending commands and stops the player as soon as possible.
 */

- (BOOL)cancelAndReturnError:(NSError **)outError;

/*! @property isMuted
	@abstract
		When set to YES, the player's audio and haptic output will be silenced.
 */
@property (readwrite) BOOL isMuted;

@end

/*!	@typedef CHHapticAdvancedPatternPlayerCompletionHandler
	@abstract
		Block which is called asynchronously when a CHHapticAdvancedPatternPlayer finishes playing.
	@param error
		If the call to start the player fails, this is set to a valid NSError describing the error.
	@discussion
		In general, callbacks arrive on a non-main thread and it is the client's responsibility to handle them
		in a thread-safe manner.
 */
typedef void (^CHHapticAdvancedPatternPlayerCompletionHandler)(NSError *_Nullable error);

/*!	@protocol CHHapticAdvancedPatternPlayer
	@abstract
		A protocol which defines operations for pausing, resuming, seeking, and sending parameters to a pattern player.
	@discussion
		Instances of these objects are created via the factory methods such as `CHHapticEngine(createAdvancedPlayerWithPattern:error)`.
 */
CH_EXPORT API_AVAILABLE(ios(13.0), macos(10.15))
@protocol CHHapticAdvancedPatternPlayer<CHHapticPatternPlayer>

/*! @method pauseAtTime:error
	@abstract
		Pause playback of the pattern at the specified time (see `CHHapticEngine(currentTime)`).
    @discussion
		If 'time' is set to `CHHapticTimeImmediate`, the pattern will be paused immediately.
 */
- (BOOL)pauseAtTime:(NSTimeInterval)time error:(NSError **)outError;

/*! @method resumeAtTime:error
	@abstract
		Resume playback on a previously-paused player at the specified time (see `CHHapticEngine(currentTime)`).
    @discussion
        If 'time' is set to `CHHapticTimeImmediate`, the pattern is resumed as soon as possible.
		Playback will resume at the time offset in the pattern at which it was paused.
 */
- (BOOL)resumeAtTime:(NSTimeInterval)time error:(NSError **)outError;

/*! @method seekToOffset:error
	@abstract
		Set the playback position on an active player to the specified offset time.
    @discussion
		If 'offsetTime' is set to 0.0, the pattern will start from the beginning.  If
		set to >= the duration of the pattern, playback will terminate as soon as possible
        unless the player is looped, in which case playback will start at the beginning of
        the loop.
 */
- (BOOL)seekToOffset:(NSTimeInterval)offsetTime error:(NSError **)outError;

/*! @property loopEnabled
	@abstract
		When set to YES, the player will loop back to the beginning of the pattern whenever playback
		reaches the `loopEnd` time.
 */
@property (readwrite) BOOL loopEnabled;

/*! @property loopEnd
	@abstract
 		The time in seconds at which the pattern will loop back if looping is enabled.
    @discussion
        If set to 0.0, the loop length will be set to the end of the last event in the pattern.
 */
@property (readwrite) NSTimeInterval loopEnd;

/*! @property playbackRate
	@abstract
		Allows a pattern to be played back at any multiple of its normal rate.  The rate can be adjusted
		at any point before or during pattern playback.
    @discussion
        This rate factor scales the relative times of all events and parameters as they are played, as well as the
        durations of Continuous events.  It does not affect the pitches of the events.  Any value greater than
        0.0 is valid; all others are ignored.
 */
@property (readwrite) float playbackRate;

/*! @property isMuted
	@abstract
		When set to YES, all audio and haptic output will be silenced.
 */
@property (readwrite) BOOL isMuted;

/*! @property completionHandler
	@abstract
		The block or enclosure that will be called when the player finishes.
 */
@property (readwrite) CHHapticAdvancedPatternPlayerCompletionHandler completionHandler;

@end

NS_ASSUME_NONNULL_END

