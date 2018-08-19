// ==========  OpenAL.framework/Headers/oalMacOSX_OALExtensions.h
/**********************************************************************************************************************************
*
*   OpenAL cross platform audio library
*	Copyright (c) 2004-2006, Apple Computer, Inc. All rights reserved.
*	Copyright (c) 2007-2012, Apple Inc. All rights reserved.
*
*	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following 
*	conditions are met:
*
*	1.  Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 
*	2.  Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following 
*		disclaimer in the documentation and/or other materials provided with the distribution. 
*	3.  Neither the name of Apple Inc. ("Apple") nor the names of its contributors may be used to endorse or promote products derived 
*		from this software without specific prior written permission. 
*
*	THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED 
*	TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS 
*	CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
*	AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
*	ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
**********************************************************************************************************************************/

#ifndef __OAL_MAC_OSX_OAL_EXTENSIONS_H__
#define __OAL_MAC_OSX_OAL_EXTENSIONS_H__

#include <OpenAL/al.h>
#include <OpenAL/alc.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	ALC_EXT_MAC_OSX
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Retrieve functions via alGetProcAddress() by passing in strings: alcMacOSXMixerOutputRate or alcMacOSXGetMixerOutputRate

// Setting the Mixer Output Rate effectively sets the sample rate at which the mixer renders
typedef ALvoid (*alcMacOSXRenderingQualityProcPtr) (ALint value);
typedef ALvoid (*alMacOSXRenderChannelCountProcPtr) (ALint value);
typedef ALvoid (*alcMacOSXMixerMaxiumumBussesProcPtr) (ALint value);
typedef ALvoid (*alcMacOSXMixerOutputRateProcPtr) (ALdouble value);

typedef ALint (*alcMacOSXGetRenderingQualityProcPtr) (void);
typedef ALint (*alMacOSXGetRenderChannelCountProcPtr) (void);
typedef ALint (*alcMacOSXGetMixerMaxiumumBussesProcPtr) (void);
typedef ALdouble (*alcMacOSXGetMixerOutputRateProcPtr) (void);

/* Render Quality. Used with alcMacOSXRenderingQuality() */
	
	#define ALC_MAC_OSX_SPATIAL_RENDERING_QUALITY_HIGH			'rqhi'
	#define ALC_MAC_OSX_SPATIAL_RENDERING_QUALITY_LOW			'rdlo'
	
	// High Quality Spatial Algorithm suitable only for headphone use
	#define ALC_IPHONE_SPATIAL_RENDERING_QUALITY_HEADPHONES		'hdph'		

/*	
	Render Channels. Used with alMacOSXRenderChannelCount()
	Allows a user to force OpenAL to render to stereo, regardless of the audio hardware being used
*/
	#define ALC_MAC_OSX_RENDER_CHANNEL_COUNT_STEREO         'rcst'
    #define ALC_MAC_OSX_RENDER_CHANNEL_COUNT_MULTICHANNEL   'rcmc'

/* GameKit extension */

	#define AL_GAMEKIT											'gksr'


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 AL_EXT_SOURCE_SPATIALIZATION
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*
    Allows the rendering quality to be explicitly set on a source object, overriding the default
    render quality set via alcMacOSXRenderingQuality(). A subsequent call to alcMacOSXRenderingQuality()
    resets the render quality of all source objects.
 
    Uses the same render settings (defined above) as alcMacOSXRenderingQuality():
 
        ALC_MAC_OSX_SPATIAL_RENDERING_QUALITY_HIGH
        ALC_MAC_OSX_SPATIAL_RENDERING_QUALITY_LOW
        ALC_IPHONE_SPATIAL_RENDERING_QUALITY_HEADPHONES
 
    Retrieve functions via alcGetProcAddress() by passing in strings: alSourceRenderingQuality or alSourceGetRenderingQuality
 */

typedef ALvoid (*alSourceRenderingQualityProcPtr) (ALuint sid, ALint value);
typedef ALint (*alSourceGetRenderingQualityProcPtr) (ALuint sid);


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 AL_EXT_SOURCE_NOTIFICATIONS
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*
 Source Notifications
 
 Eliminates the need for continuous polling for source state by providing a
 mechanism for the application to receive source state change notifications.
 Upon receiving a notification, the application can retrieve the actual state
 corresponding to the notification ID for which the notification was sent.
 */

#define AL_QUEUE_HAS_LOOPED									0x9000

/*
 Notification Proc:	ALSourceNotificationProc
 
 sid		- source id
 notificationID	- id of state that has changed
 userData	- user data provided to alSourceAddNotification()
 */

typedef ALvoid (*alSourceNotificationProc)(ALuint sid, ALuint	notificationID, ALvoid*	__nullable userData);

/*
 API: alSourceAddNotification
 
 sid		- source id
 notificationID	- id of state for which caller wants to be notified of a change 					
 notifyProc	- notification proc
 userData	- ptr to applications user data, will be returned in the notification proc
 
 Returns AL_NO_ERROR if request is successful.
 
 Valid IDs:
 AL_SOURCE_STATE
 AL_BUFFERS_PROCESSED
 AL_QUEUE_HAS_LOOPED	- notification sent when a looping source has looped to it's start point
 */
typedef ALenum (*alSourceAddNotificationProcPtr) (ALuint sid, ALuint notificationID, alSourceNotificationProc __nonnull notifyProc, ALvoid* __nullable userData);

/*
 API: alSourceRemoveStateNotification
 
 sid		- source id
 notificationID	- id of state for which caller wants to remove an existing notification 					
 notifyProc	- notification proc
 userData	- ptr to applications user data, will be returned in the notification proc
 */
typedef ALvoid (*alSourceRemoveNotificationProcPtr) (ALuint	sid, ALuint notificationID, alSourceNotificationProc __nonnull notifyProc, ALvoid* __nullable userData);


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	ALC_EXT_ASA : Apple Spatial Audio Extension
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*
	Used with the ASA API calls: alcASAGetSource(), alcASASetSource(), alcASAGetListener(), alcASASetListener()
*/

typedef ALenum  (*alcASAGetSourceProcPtr) (ALuint property, ALuint source, ALvoid* __nonnull data, ALuint* __nonnull dataSize);
typedef ALenum  (*alcASASetSourceProcPtr) (ALuint property, ALuint source, ALvoid* __nonnull data, ALuint dataSize);
typedef ALenum  (*alcASAGetListenerProcPtr) (ALuint property, ALvoid* __nonnull data, ALuint* __nonnull dataSize);
typedef ALenum  (*alcASASetListenerProcPtr) (ALuint property, ALvoid* __nonnull data, ALuint dataSize);

	/* listener properties */
	#define ALC_ASA_REVERB_ON							'rvon'	// type ALuint
	#define ALC_ASA_REVERB_GLOBAL_LEVEL					'rvgl'	// type ALfloat	-40.0 db - 40.0 db

	#define ALC_ASA_REVERB_ROOM_TYPE					'rvrt'	// type ALint	
	
	/* reverb room type presets for the ALC_ASA_REVERB_ROOM_TYPE property */
    #define ALC_ASA_REVERB_ROOM_TYPE_SmallRoom			0
    #define ALC_ASA_REVERB_ROOM_TYPE_MediumRoom			1
    #define ALC_ASA_REVERB_ROOM_TYPE_LargeRoom			2
    #define ALC_ASA_REVERB_ROOM_TYPE_MediumHall			3
    #define ALC_ASA_REVERB_ROOM_TYPE_LargeHall			4
    #define ALC_ASA_REVERB_ROOM_TYPE_Plate				5
    #define ALC_ASA_REVERB_ROOM_TYPE_MediumChamber		6
    #define ALC_ASA_REVERB_ROOM_TYPE_LargeChamber		7
    #define ALC_ASA_REVERB_ROOM_TYPE_Cathedral			8
    #define ALC_ASA_REVERB_ROOM_TYPE_LargeRoom2			9
    #define ALC_ASA_REVERB_ROOM_TYPE_MediumHall2		10
    #define ALC_ASA_REVERB_ROOM_TYPE_MediumHall3		11
    #define ALC_ASA_REVERB_ROOM_TYPE_LargeHall2			12

	#define ALC_ASA_REVERB_EQ_GAIN						'rveg'	// type ALfloat
	#define ALC_ASA_REVERB_EQ_BANDWITH					'rveb'	// type ALfloat
	#define ALC_ASA_REVERB_EQ_FREQ						'rvef'	// type ALfloat

    /* source properties */
	#define ALC_ASA_REVERB_SEND_LEVEL					'rvsl'	// type ALfloat	0.0 (dry) - 1.0 (wet) (0-100% dry/wet mix, 0.0 default)
	#define ALC_ASA_OCCLUSION							'occl'	// type ALfloat	-100.0 db (most occlusion) - 0.0 db (no occlusion, 0.0 default)
	#define ALC_ASA_OBSTRUCTION							'obst'	// type ALfloat	-100.0 db (most obstruction) - 0.0 db (no obstruction, 0.0 default)	
							

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ALC_EXT_OUTPUT_CAPTURER
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*
 Allows an application to capture the rendered output of the current context.
 The application prepares OpenAL for capturing the context output by specifying the data format
 of the captured audio output data. Once capture has been started, the application then queries OpenAL
 for the available number of captured samples, and requests the samples by providing a buffer to fill.
 
 Retrieve functions via alcGetProcAddress() by passing in strings: alcOutputCapturerPrepare, alcOutputCapturerStart,
 alcOutputCapturerStop, alcOutputCapturerAvailableSamples and alcOutputCapturerSamples
 */

/*
 API: alcOutputCapturerPrepare
 
 Prepare output capturing of the current context by specifying the data format desired from OpenAL.
 
 frequency		- Sampling rate of the captured output.
 
 format         - Data format of the captured data. Specified as one of the native OpenAL data format types:
 AL_FORMAT_MONO8
 AL_FORMAT_MONO16
 AL_FORMAT_STEREO8
 AL_FORMAT_STEREO16
 
 maxsamplecount     - The maximum number of samples that will be requested by the application.
 */
typedef ALvoid AL_APIENTRY (*alcOutputCapturerPrepareProcPtr)   (ALCuint frequency, ALCenum format, ALCsizei maxsamplecount);

/*
 API: alcOutputCapturerStart
 
 Start capturing samples rendered by the current context to a maximum of the sample count specified when calling alcOutputCapturerPrepare.
 */
typedef ALvoid AL_APIENTRY (*alcOutputCapturerStartProcPtr) (void);

/*
 API: alcOutputCapturerStop
 
 Stop capturing samples rendered by the context. This function resets the captured audio samples to 0.
 */
typedef ALvoid AL_APIENTRY (*alcOutputCapturerStopProcPtr) (void);

/*
 API: alcOutputCapturerAvailableSamples
 
 Get the number of captured samples currently available.
 */
typedef ALint  AL_APIENTRY (*alcOutputCapturerAvailableSamplesProcPtr) (void);

/*
 API: alcOutputCapturerSamples
 
 Write captured samples to an application provided buffer.
 
 buffer         -   Application provided buffer to be filled with the requested amount of samples and must be of size
 samplecount * size of sample. i.e. 100 samples of AL_FORMAT_STEREO16 data -> 100 * 4 = 400 bytes
 The buffer must NOT be deallocated before the call to alcOutputCapturerSamples returns.
 
 samplecount    -   Number of samples to be copied to the provided buffer.
 Requesting more samples than currently available is an error.
 */
typedef ALvoid AL_APIENTRY (*alcOutputCapturerSamplesProcPtr)   (ALCvoid* __nonnull buffer, ALCsizei samplecount);


#endif // __OAL_MAC_OSX_OAL_EXTENSIONS_H__

// ==========  OpenAL.framework/Headers/oalStaticBufferExtension.h
/**********************************************************************************************************************************
*
*   OpenAL cross platform audio library
*	Copyright (c) 2004-2006, Apple Computer, Inc. All rights reserved.
*	Copyright (c) 2007-2008, Apple Inc. All rights reserved.
*
*	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following 
*	conditions are met:
*
*	1.  Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 
*	2.  Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following 
*		disclaimer in the documentation and/or other materials provided with the distribution. 
*	3.  Neither the name of Apple Inc. ("Apple") nor the names of its contributors may be used to endorse or promote products derived 
*		from this software without specific prior written permission. 
*
*	THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED 
*	TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS 
*	CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
*	AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
*	ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
**********************************************************************************************************************************/

#ifndef __OAL_STATIC_BUFFER_EXTENSION_H__
#define __OAL_STATIC_BUFFER_EXTENSION_H__

#include <OpenAL/al.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	AL_EXT_STATIC_BUFFER
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef ALvoid	AL_APIENTRY	(*alBufferDataStaticProcPtr) (ALint bid, ALenum format, const ALvoid* __nonnull data, ALsizei size, ALsizei freq);

#endif // __OAL_STATIC_BUFFER_EXTENSION_H__// ==========  OpenAL.framework/Headers/al.h
#ifndef AL_AL_H
#define AL_AL_H

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(_WIN32) && !defined(_XBOX)
 /* _OPENAL32LIB is deprecated */
 #if defined(AL_BUILD_LIBRARY) || defined (_OPENAL32LIB)
  #define AL_API __declspec(dllexport)
 #else
  #define AL_API __declspec(dllimport)
 #endif
#else
 #if defined(AL_BUILD_LIBRARY) && defined(HAVE_GCC_VISIBILITY)
  #define AL_API __attribute__((visibility("default")))
 #else
  #define AL_API extern
 #endif
#endif

#if defined(_WIN32)
 #define AL_APIENTRY __cdecl
#else
 #define AL_APIENTRY
#endif

#if defined(TARGET_OS_MAC) && TARGET_OS_MAC
// #pragma export on
#endif

/*
 * The OPENAL, ALAPI, ALAPIENTRY, AL_INVALID, AL_ILLEGAL_ENUM, and
 * AL_ILLEGAL_COMMAND macros are deprecated, but are included for
 * applications porting code from AL 1.0
 */
#define OPENAL
#define ALAPI AL_API
#define ALAPIENTRY AL_APIENTRY
#define AL_INVALID                                (-1)
#define AL_ILLEGAL_ENUM                           AL_INVALID_ENUM
#define AL_ILLEGAL_COMMAND                        AL_INVALID_OPERATION

#define AL_VERSION_1_0
#define AL_VERSION_1_1


/** 8-bit boolean */
typedef char ALboolean;

/** character */
typedef char ALchar;

/** signed 8-bit 2's complement integer */
typedef char ALbyte;

/** unsigned 8-bit integer */
typedef unsigned char ALubyte;

/** signed 16-bit 2's complement integer */
typedef short ALshort;

/** unsigned 16-bit integer */
typedef unsigned short ALushort;

/** signed 32-bit 2's complement integer */
typedef int ALint;

/** unsigned 32-bit integer */
typedef unsigned int ALuint;

/** non-negative 32-bit binary integer size */
typedef int ALsizei;

/** enumerated 32-bit value */
typedef int ALenum;

/** 32-bit IEEE754 floating-point */
typedef float ALfloat;

/** 64-bit IEEE754 floating-point */
typedef double ALdouble;

/** void type (for opaque pointers only) */
typedef void ALvoid;


/* Enumerant values begin at column 50. No tabs. */

/* "no distance model" or "no buffer" */
#define AL_NONE                                   0

/* Boolean False. */
#define AL_FALSE                                  0

/** Boolean True. */
#define AL_TRUE                                   1

/** Indicate Source has relative coordinates. */
#define AL_SOURCE_RELATIVE                        0x202



/**
 * Directional source, inner cone angle, in degrees.
 * Range:    [0-360] 
 * Default:  360
 */
#define AL_CONE_INNER_ANGLE                       0x1001

/**
 * Directional source, outer cone angle, in degrees.
 * Range:    [0-360] 
 * Default:  360
 */
#define AL_CONE_OUTER_ANGLE                       0x1002

/**
 * Specify the pitch to be applied, either at source,
 *  or on mixer results, at listener.
 * Range:   [0.5-2.0]
 * Default: 1.0
 */
#define AL_PITCH                                  0x1003
  
/** 
 * Specify the current location in three dimensional space.
 * OpenAL, like OpenGL, uses a right handed coordinate system,
 *  where in a frontal default view X (thumb) points right, 
 *  Y points up (index finger), and Z points towards the
 *  viewer/camera (middle finger). 
 * To switch from a left handed coordinate system, flip the
 *  sign on the Z coordinate.
 * Listener position is always in the world coordinate system.
 */ 
#define AL_POSITION                               0x1004
  
/** Specify the current direction. */
#define AL_DIRECTION                              0x1005
  
/** Specify the current velocity in three dimensional space. */
#define AL_VELOCITY                               0x1006

/**
 * Indicate whether source is looping.
 * Type: ALboolean?
 * Range:   [AL_TRUE, AL_FALSE]
 * Default: FALSE.
 */
#define AL_LOOPING                                0x1007

/**
 * Indicate the buffer to provide sound samples. 
 * Type: ALuint.
 * Range: any valid Buffer id.
 */
#define AL_BUFFER                                 0x1009
  
/**
 * Indicate the gain (volume amplification) applied. 
 * Type:   ALfloat.
 * Range:  ]0.0-  ]
 * A value of 1.0 means un-attenuated/unchanged.
 * Each division by 2 equals an attenuation of -6dB.
 * Each multiplicaton with 2 equals an amplification of +6dB.
 * A value of 0.0 is meaningless with respect to a logarithmic
 *  scale; it is interpreted as zero volume - the channel
 *  is effectively disabled.
 */
#define AL_GAIN                                   0x100A

/*
 * Indicate minimum source attenuation
 * Type: ALfloat
 * Range:  [0.0 - 1.0]
 *
 * Logarthmic
 */
#define AL_MIN_GAIN                               0x100D

/**
 * Indicate maximum source attenuation
 * Type: ALfloat
 * Range:  [0.0 - 1.0]
 *
 * Logarthmic
 */
#define AL_MAX_GAIN                               0x100E

/**
 * Indicate listener orientation.
 *
 * at/up 
 */
#define AL_ORIENTATION                            0x100F

/**
 * Source state information.
 */
#define AL_SOURCE_STATE                           0x1010
#define AL_INITIAL                                0x1011
#define AL_PLAYING                                0x1012
#define AL_PAUSED                                 0x1013
#define AL_STOPPED                                0x1014

/**
 * Buffer Queue params
 */
#define AL_BUFFERS_QUEUED                         0x1015
#define AL_BUFFERS_PROCESSED                      0x1016

/**
 * Source buffer position information
 */
#define AL_SEC_OFFSET                             0x1024
#define AL_SAMPLE_OFFSET                          0x1025
#define AL_BYTE_OFFSET                            0x1026

/*
 * Source type (Static, Streaming or undetermined)
 * Source is Static if a Buffer has been attached using AL_BUFFER
 * Source is Streaming if one or more Buffers have been attached using alSourceQueueBuffers
 * Source is undetermined when it has the NULL buffer attached
 */
#define AL_SOURCE_TYPE                            0x1027
#define AL_STATIC                                 0x1028
#define AL_STREAMING                              0x1029
#define AL_UNDETERMINED                           0x1030

/** Sound samples: format specifier. */
#define AL_FORMAT_MONO8                           0x1100
#define AL_FORMAT_MONO16                          0x1101
#define AL_FORMAT_STEREO8                         0x1102
#define AL_FORMAT_STEREO16                        0x1103

/**
 * source specific reference distance
 * Type: ALfloat
 * Range:  0.0 - +inf
 *
 * At 0.0, no distance attenuation occurs.  Default is
 * 1.0.
 */
#define AL_REFERENCE_DISTANCE                     0x1020

/**
 * source specific rolloff factor
 * Type: ALfloat
 * Range:  0.0 - +inf
 *
 */
#define AL_ROLLOFF_FACTOR                         0x1021

/**
 * Directional source, outer cone gain.
 *
 * Default:  0.0
 * Range:    [0.0 - 1.0]
 * Logarithmic
 */
#define AL_CONE_OUTER_GAIN                        0x1022

/**
 * Indicate distance above which sources are not
 * attenuated using the inverse clamped distance model.
 *
 * Default: +inf
 * Type: ALfloat
 * Range:  0.0 - +inf
 */
#define AL_MAX_DISTANCE                           0x1023

/** 
 * Sound samples: frequency, in units of Hertz [Hz].
 * This is the number of samples per second. Half of the
 *  sample frequency marks the maximum significant
 *  frequency component.
 */
#define AL_FREQUENCY                              0x2001
#define AL_BITS                                   0x2002
#define AL_CHANNELS                               0x2003
#define AL_SIZE                                   0x2004

/**
 * Buffer state.
 *
 * Not supported for public use (yet).
 */
#define AL_UNUSED                                 0x2010
#define AL_PENDING                                0x2011
#define AL_PROCESSED                              0x2012


/** Errors: No Error. */
#define AL_NO_ERROR                               AL_FALSE

/** 
 * Invalid Name paramater passed to AL call.
 */
#define AL_INVALID_NAME                           0xA001

/** 
 * Invalid parameter passed to AL call.
 */
#define AL_INVALID_ENUM                           0xA002

/** 
 * Invalid enum parameter value.
 */
#define AL_INVALID_VALUE                          0xA003

/** 
 * Illegal call.
 */
#define AL_INVALID_OPERATION                      0xA004

  
/**
 * No mojo.
 */
#define AL_OUT_OF_MEMORY                          0xA005


/** Context strings: Vendor Name. */
#define AL_VENDOR                                 0xB001
#define AL_VERSION                                0xB002
#define AL_RENDERER                               0xB003
#define AL_EXTENSIONS                             0xB004

/** Global tweakage. */

/**
 * Doppler scale.  Default 1.0
 */
#define AL_DOPPLER_FACTOR                         0xC000

/**
 * Tweaks speed of propagation.
 */
#define AL_DOPPLER_VELOCITY                       0xC001

/**
 * Speed of Sound in units per second
 */
#define AL_SPEED_OF_SOUND                         0xC003

/**
 * Distance models
 *
 * used in conjunction with DistanceModel
 *
 * implicit: NONE, which disances distance attenuation.
 */
#define AL_DISTANCE_MODEL                         0xD000
#define AL_INVERSE_DISTANCE                       0xD001
#define AL_INVERSE_DISTANCE_CLAMPED               0xD002
#define AL_LINEAR_DISTANCE                        0xD003
#define AL_LINEAR_DISTANCE_CLAMPED                0xD004
#define AL_EXPONENT_DISTANCE                      0xD005
#define AL_EXPONENT_DISTANCE_CLAMPED              0xD006

/*
 * Renderer State management
 */
AL_API void AL_APIENTRY alEnable( ALenum capability );

AL_API void AL_APIENTRY alDisable( ALenum capability ); 

AL_API ALboolean AL_APIENTRY alIsEnabled( ALenum capability ); 


/*
 * State retrieval
 */
AL_API const ALchar* AL_APIENTRY alGetString( ALenum param );

AL_API void AL_APIENTRY alGetBooleanv( ALenum param, ALboolean* data );

AL_API void AL_APIENTRY alGetIntegerv( ALenum param, ALint* data );

AL_API void AL_APIENTRY alGetFloatv( ALenum param, ALfloat* data );

AL_API void AL_APIENTRY alGetDoublev( ALenum param, ALdouble* data );

AL_API ALboolean AL_APIENTRY alGetBoolean( ALenum param );

AL_API ALint AL_APIENTRY alGetInteger( ALenum param );

AL_API ALfloat AL_APIENTRY alGetFloat( ALenum param );

AL_API ALdouble AL_APIENTRY alGetDouble( ALenum param );


/*
 * Error support.
 * Obtain the most recent error generated in the AL state machine.
 */
AL_API ALenum AL_APIENTRY alGetError( void );


/* 
 * Extension support.
 * Query for the presence of an extension, and obtain any appropriate
 * function pointers and enum values.
 */
AL_API ALboolean AL_APIENTRY alIsExtensionPresent( const ALchar* extname );

AL_API void* AL_APIENTRY alGetProcAddress( const ALchar* fname );

AL_API ALenum AL_APIENTRY alGetEnumValue( const ALchar* ename );


/*
 * LISTENER
 * Listener represents the location and orientation of the
 * 'user' in 3D-space.
 *
 * Properties include: -
 *
 * Gain         AL_GAIN         ALfloat
 * Position     AL_POSITION     ALfloat[3]
 * Velocity     AL_VELOCITY     ALfloat[3]
 * Orientation  AL_ORIENTATION  ALfloat[6] (Forward then Up vectors)
*/

/*
 * Set Listener parameters
 */
AL_API void AL_APIENTRY alListenerf( ALenum param, ALfloat value );

AL_API void AL_APIENTRY alListener3f( ALenum param, ALfloat value1, ALfloat value2, ALfloat value3 );

AL_API void AL_APIENTRY alListenerfv( ALenum param, const ALfloat* values ); 

AL_API void AL_APIENTRY alListeneri( ALenum param, ALint value );

AL_API void AL_APIENTRY alListener3i( ALenum param, ALint value1, ALint value2, ALint value3 );

AL_API void AL_APIENTRY alListeneriv( ALenum param, const ALint* values );

/*
 * Get Listener parameters
 */
AL_API void AL_APIENTRY alGetListenerf( ALenum param, ALfloat* value );

AL_API void AL_APIENTRY alGetListener3f( ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3 );

AL_API void AL_APIENTRY alGetListenerfv( ALenum param, ALfloat* values );

AL_API void AL_APIENTRY alGetListeneri( ALenum param, ALint* value );

AL_API void AL_APIENTRY alGetListener3i( ALenum param, ALint *value1, ALint *value2, ALint *value3 );

AL_API void AL_APIENTRY alGetListeneriv( ALenum param, ALint* values );


/**
 * SOURCE
 * Sources represent individual sound objects in 3D-space.
 * Sources take the PCM data provided in the specified Buffer,
 * apply Source-specific modifications, and then
 * submit them to be mixed according to spatial arrangement etc.
 * 
 * Properties include: -
 *
 * Gain                              AL_GAIN                 ALfloat
 * Min Gain                          AL_MIN_GAIN             ALfloat
 * Max Gain                          AL_MAX_GAIN             ALfloat
 * Position                          AL_POSITION             ALfloat[3]
 * Velocity                          AL_VELOCITY             ALfloat[3]
 * Direction                         AL_DIRECTION            ALfloat[3]
 * Head Relative Mode                AL_SOURCE_RELATIVE      ALint (AL_TRUE or AL_FALSE)
 * Reference Distance                AL_REFERENCE_DISTANCE   ALfloat
 * Max Distance                      AL_MAX_DISTANCE         ALfloat
 * RollOff Factor                    AL_ROLLOFF_FACTOR       ALfloat
 * Inner Angle                       AL_CONE_INNER_ANGLE     ALint or ALfloat
 * Outer Angle                       AL_CONE_OUTER_ANGLE     ALint or ALfloat
 * Cone Outer Gain                   AL_CONE_OUTER_GAIN      ALint or ALfloat
 * Pitch                             AL_PITCH                ALfloat
 * Looping                           AL_LOOPING              ALint (AL_TRUE or AL_FALSE)
 * MS Offset                         AL_MSEC_OFFSET          ALint or ALfloat
 * Byte Offset                       AL_BYTE_OFFSET          ALint or ALfloat
 * Sample Offset                     AL_SAMPLE_OFFSET        ALint or ALfloat
 * Attached Buffer                   AL_BUFFER               ALint
 * State (Query only)                AL_SOURCE_STATE         ALint
 * Buffers Queued (Query only)       AL_BUFFERS_QUEUED       ALint
 * Buffers Processed (Query only)    AL_BUFFERS_PROCESSED    ALint
 */

/* Create Source objects */
AL_API void AL_APIENTRY alGenSources( ALsizei n, ALuint* sources ); 

/* Delete Source objects */
AL_API void AL_APIENTRY alDeleteSources( ALsizei n, const ALuint* sources );

/* Verify a handle is a valid Source */ 
AL_API ALboolean AL_APIENTRY alIsSource( ALuint sid ); 

/*
 * Set Source parameters
 */
AL_API void AL_APIENTRY alSourcef( ALuint sid, ALenum param, ALfloat value ); 

AL_API void AL_APIENTRY alSource3f( ALuint sid, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3 );

AL_API void AL_APIENTRY alSourcefv( ALuint sid, ALenum param, const ALfloat* values ); 

AL_API void AL_APIENTRY alSourcei( ALuint sid, ALenum param, ALint value ); 

AL_API void AL_APIENTRY alSource3i( ALuint sid, ALenum param, ALint value1, ALint value2, ALint value3 );

AL_API void AL_APIENTRY alSourceiv( ALuint sid, ALenum param, const ALint* values );

/*
 * Get Source parameters
 */
AL_API void AL_APIENTRY alGetSourcef( ALuint sid, ALenum param, ALfloat* value );

AL_API void AL_APIENTRY alGetSource3f( ALuint sid, ALenum param, ALfloat* value1, ALfloat* value2, ALfloat* value3);

AL_API void AL_APIENTRY alGetSourcefv( ALuint sid, ALenum param, ALfloat* values );

AL_API void AL_APIENTRY alGetSourcei( ALuint sid,  ALenum param, ALint* value );

AL_API void AL_APIENTRY alGetSource3i( ALuint sid, ALenum param, ALint* value1, ALint* value2, ALint* value3);

AL_API void AL_APIENTRY alGetSourceiv( ALuint sid,  ALenum param, ALint* values );


/*
 * Source vector based playback calls
 */

/* Play, replay, or resume (if paused) a list of Sources */
AL_API void AL_APIENTRY alSourcePlayv( ALsizei ns, const ALuint *sids );

/* Stop a list of Sources */
AL_API void AL_APIENTRY alSourceStopv( ALsizei ns, const ALuint *sids );

/* Rewind a list of Sources */
AL_API void AL_APIENTRY alSourceRewindv( ALsizei ns, const ALuint *sids );

/* Pause a list of Sources */
AL_API void AL_APIENTRY alSourcePausev( ALsizei ns, const ALuint *sids );

/*
 * Source based playback calls
 */

/* Play, replay, or resume a Source */
AL_API void AL_APIENTRY alSourcePlay( ALuint sid );

/* Stop a Source */
AL_API void AL_APIENTRY alSourceStop( ALuint sid );

/* Rewind a Source (set playback postiton to beginning) */
AL_API void AL_APIENTRY alSourceRewind( ALuint sid );

/* Pause a Source */
AL_API void AL_APIENTRY alSourcePause( ALuint sid );

/*
 * Source Queuing 
 */
AL_API void AL_APIENTRY alSourceQueueBuffers( ALuint sid, ALsizei numEntries, const ALuint *bids );

AL_API void AL_APIENTRY alSourceUnqueueBuffers( ALuint sid, ALsizei numEntries, ALuint *bids );


/**
 * BUFFER
 * Buffer objects are storage space for sample data.
 * Buffers are referred to by Sources. One Buffer can be used
 * by multiple Sources.
 *
 * Properties include: -
 *
 * Frequency (Query only)    AL_FREQUENCY      ALint
 * Size (Query only)         AL_SIZE           ALint
 * Bits (Query only)         AL_BITS           ALint
 * Channels (Query only)     AL_CHANNELS       ALint
 */

/* Create Buffer objects */
AL_API void AL_APIENTRY alGenBuffers( ALsizei n, ALuint* buffers );

/* Delete Buffer objects */
AL_API void AL_APIENTRY alDeleteBuffers( ALsizei n, const ALuint* buffers );

/* Verify a handle is a valid Buffer */
AL_API ALboolean AL_APIENTRY alIsBuffer( ALuint bid );

/* Specify the data to be copied into a buffer */
AL_API void AL_APIENTRY alBufferData( ALuint bid, ALenum format, const ALvoid* data, ALsizei size, ALsizei freq );

/*
 * Set Buffer parameters
 */
AL_API void AL_APIENTRY alBufferf( ALuint bid, ALenum param, ALfloat value );

AL_API void AL_APIENTRY alBuffer3f( ALuint bid, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3 );

AL_API void AL_APIENTRY alBufferfv( ALuint bid, ALenum param, const ALfloat* values );

AL_API void AL_APIENTRY alBufferi( ALuint bid, ALenum param, ALint value );

AL_API void AL_APIENTRY alBuffer3i( ALuint bid, ALenum param, ALint value1, ALint value2, ALint value3 );

AL_API void AL_APIENTRY alBufferiv( ALuint bid, ALenum param, const ALint* values );

/*
 * Get Buffer parameters
 */
AL_API void AL_APIENTRY alGetBufferf( ALuint bid, ALenum param, ALfloat* value );

AL_API void AL_APIENTRY alGetBuffer3f( ALuint bid, ALenum param, ALfloat* value1, ALfloat* value2, ALfloat* value3);

AL_API void AL_APIENTRY alGetBufferfv( ALuint bid, ALenum param, ALfloat* values );

AL_API void AL_APIENTRY alGetBufferi( ALuint bid, ALenum param, ALint* value );

AL_API void AL_APIENTRY alGetBuffer3i( ALuint bid, ALenum param, ALint* value1, ALint* value2, ALint* value3);

AL_API void AL_APIENTRY alGetBufferiv( ALuint bid, ALenum param, ALint* values );


/*
 * Global Parameters
 */
AL_API void AL_APIENTRY alDopplerFactor( ALfloat value );

AL_API void AL_APIENTRY alDopplerVelocity( ALfloat value );

AL_API void AL_APIENTRY alSpeedOfSound( ALfloat value );

AL_API void AL_APIENTRY alDistanceModel( ALenum distanceModel );

/*
 * Pointer-to-function types, useful for dynamically getting AL entry points.
 */
typedef void           (AL_APIENTRY *LPALENABLE)( ALenum capability );
typedef void           (AL_APIENTRY *LPALDISABLE)( ALenum capability ); 
typedef ALboolean      (AL_APIENTRY *LPALISENABLED)( ALenum capability ); 
typedef const ALchar*  (AL_APIENTRY *LPALGETSTRING)( ALenum param );
typedef void           (AL_APIENTRY *LPALGETBOOLEANV)( ALenum param, ALboolean* data );
typedef void           (AL_APIENTRY *LPALGETINTEGERV)( ALenum param, ALint* data );
typedef void           (AL_APIENTRY *LPALGETFLOATV)( ALenum param, ALfloat* data );
typedef void           (AL_APIENTRY *LPALGETDOUBLEV)( ALenum param, ALdouble* data );
typedef ALboolean      (AL_APIENTRY *LPALGETBOOLEAN)( ALenum param );
typedef ALint          (AL_APIENTRY *LPALGETINTEGER)( ALenum param );
typedef ALfloat        (AL_APIENTRY *LPALGETFLOAT)( ALenum param );
typedef ALdouble       (AL_APIENTRY *LPALGETDOUBLE)( ALenum param );
typedef ALenum         (AL_APIENTRY *LPALGETERROR)( void );
typedef ALboolean      (AL_APIENTRY *LPALISEXTENSIONPRESENT)(const ALchar* extname );
typedef void*          (AL_APIENTRY *LPALGETPROCADDRESS)( const ALchar* fname );
typedef ALenum         (AL_APIENTRY *LPALGETENUMVALUE)( const ALchar* ename );
typedef void           (AL_APIENTRY *LPALLISTENERF)( ALenum param, ALfloat value );
typedef void           (AL_APIENTRY *LPALLISTENER3F)( ALenum param, ALfloat value1, ALfloat value2, ALfloat value3 );
typedef void           (AL_APIENTRY *LPALLISTENERFV)( ALenum param, const ALfloat* values );
typedef void           (AL_APIENTRY *LPALLISTENERI)( ALenum param, ALint value );
typedef void           (AL_APIENTRY *LPALLISTENER3I)( ALenum param, ALint value1, ALint value2, ALint value3 );
typedef void           (AL_APIENTRY *LPALLISTENERIV)( ALenum param, const ALint* values );
typedef void           (AL_APIENTRY *LPALGETLISTENERF)( ALenum param, ALfloat* value );
typedef void           (AL_APIENTRY *LPALGETLISTENER3F)( ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3 );
typedef void           (AL_APIENTRY *LPALGETLISTENERFV)( ALenum param, ALfloat* values );
typedef void           (AL_APIENTRY *LPALGETLISTENERI)( ALenum param, ALint* value );
typedef void           (AL_APIENTRY *LPALGETLISTENER3I)( ALenum param, ALint *value1, ALint *value2, ALint *value3 );
typedef void           (AL_APIENTRY *LPALGETLISTENERIV)( ALenum param, ALint* values );
typedef void           (AL_APIENTRY *LPALGENSOURCES)( ALsizei n, ALuint* sources ); 
typedef void           (AL_APIENTRY *LPALDELETESOURCES)( ALsizei n, const ALuint* sources );
typedef ALboolean      (AL_APIENTRY *LPALISSOURCE)( ALuint sid ); 
typedef void           (AL_APIENTRY *LPALSOURCEF)( ALuint sid, ALenum param, ALfloat value); 
typedef void           (AL_APIENTRY *LPALSOURCE3F)( ALuint sid, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3 );
typedef void           (AL_APIENTRY *LPALSOURCEFV)( ALuint sid, ALenum param, const ALfloat* values );
typedef void           (AL_APIENTRY *LPALSOURCEI)( ALuint sid, ALenum param, ALint value); 
typedef void           (AL_APIENTRY *LPALSOURCE3I)( ALuint sid, ALenum param, ALint value1, ALint value2, ALint value3 );
typedef void           (AL_APIENTRY *LPALSOURCEIV)( ALuint sid, ALenum param, const ALint* values );
typedef void           (AL_APIENTRY *LPALGETSOURCEF)( ALuint sid, ALenum param, ALfloat* value );
typedef void           (AL_APIENTRY *LPALGETSOURCE3F)( ALuint sid, ALenum param, ALfloat* value1, ALfloat* value2, ALfloat* value3);
typedef void           (AL_APIENTRY *LPALGETSOURCEFV)( ALuint sid, ALenum param, ALfloat* values );
typedef void           (AL_APIENTRY *LPALGETSOURCEI)( ALuint sid, ALenum param, ALint* value );
typedef void           (AL_APIENTRY *LPALGETSOURCE3I)( ALuint sid, ALenum param, ALint* value1, ALint* value2, ALint* value3);
typedef void           (AL_APIENTRY *LPALGETSOURCEIV)( ALuint sid, ALenum param, ALint* values );
typedef void           (AL_APIENTRY *LPALSOURCEPLAYV)( ALsizei ns, const ALuint *sids );
typedef void           (AL_APIENTRY *LPALSOURCESTOPV)( ALsizei ns, const ALuint *sids );
typedef void           (AL_APIENTRY *LPALSOURCEREWINDV)( ALsizei ns, const ALuint *sids );
typedef void           (AL_APIENTRY *LPALSOURCEPAUSEV)( ALsizei ns, const ALuint *sids );
typedef void           (AL_APIENTRY *LPALSOURCEPLAY)( ALuint sid );
typedef void           (AL_APIENTRY *LPALSOURCESTOP)( ALuint sid );
typedef void           (AL_APIENTRY *LPALSOURCEREWIND)( ALuint sid );
typedef void           (AL_APIENTRY *LPALSOURCEPAUSE)( ALuint sid );
typedef void           (AL_APIENTRY *LPALSOURCEQUEUEBUFFERS)(ALuint sid, ALsizei numEntries, const ALuint *bids );
typedef void           (AL_APIENTRY *LPALSOURCEUNQUEUEBUFFERS)(ALuint sid, ALsizei numEntries, ALuint *bids );
typedef void           (AL_APIENTRY *LPALGENBUFFERS)( ALsizei n, ALuint* buffers );
typedef void           (AL_APIENTRY *LPALDELETEBUFFERS)( ALsizei n, const ALuint* buffers );
typedef ALboolean      (AL_APIENTRY *LPALISBUFFER)( ALuint bid );
typedef void           (AL_APIENTRY *LPALBUFFERDATA)( ALuint bid, ALenum format, const ALvoid* data, ALsizei size, ALsizei freq );
typedef void           (AL_APIENTRY *LPALBUFFERF)( ALuint bid, ALenum param, ALfloat value);
typedef void           (AL_APIENTRY *LPALBUFFER3F)( ALuint bid, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3 );
typedef void           (AL_APIENTRY *LPALBUFFERFV)( ALuint bid, ALenum param, const ALfloat* values );
typedef void           (AL_APIENTRY *LPALBUFFERI)( ALuint bid, ALenum param, ALint value);
typedef void           (AL_APIENTRY *LPALBUFFER3I)( ALuint bid, ALenum param, ALint value1, ALint value2, ALint value3 );
typedef void           (AL_APIENTRY *LPALBUFFERIV)( ALuint bid, ALenum param, const ALint* values );
typedef void           (AL_APIENTRY *LPALGETBUFFERF)( ALuint bid, ALenum param, ALfloat* value );
typedef void           (AL_APIENTRY *LPALGETBUFFER3F)( ALuint bid, ALenum param, ALfloat* value1, ALfloat* value2, ALfloat* value3);
typedef void           (AL_APIENTRY *LPALGETBUFFERFV)( ALuint bid, ALenum param, ALfloat* values );
typedef void           (AL_APIENTRY *LPALGETBUFFERI)( ALuint bid, ALenum param, ALint* value );
typedef void           (AL_APIENTRY *LPALGETBUFFER3I)( ALuint bid, ALenum param, ALint* value1, ALint* value2, ALint* value3);
typedef void           (AL_APIENTRY *LPALGETBUFFERIV)( ALuint bid, ALenum param, ALint* values );
typedef void           (AL_APIENTRY *LPALDOPPLERFACTOR)( ALfloat value );
typedef void           (AL_APIENTRY *LPALDOPPLERVELOCITY)( ALfloat value );
typedef void           (AL_APIENTRY *LPALSPEEDOFSOUND)( ALfloat value );
typedef void           (AL_APIENTRY *LPALDISTANCEMODEL)( ALenum distanceModel );

#if defined(TARGET_OS_MAC) && TARGET_OS_MAC
// #pragma export off
#endif

#if defined(__cplusplus)
}  /* extern "C" */
#endif

#endif /* AL_AL_H */
// ==========  OpenAL.framework/Headers/alc.h
#ifndef AL_ALC_H
#define AL_ALC_H

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(_WIN32) && !defined(_XBOX)
 /* _OPENAL32LIB is deprecated */
 #if defined(AL_BUILD_LIBRARY) || defined (_OPENAL32LIB)
  #define ALC_API __declspec(dllexport)
 #else
  #define ALC_API __declspec(dllimport)
 #endif
#else
 #if defined(AL_BUILD_LIBRARY) && defined(HAVE_GCC_VISIBILITY)
  #define ALC_API __attribute__((visibility("default")))
 #else
  #define ALC_API extern
 #endif
#endif

#if defined(_WIN32)
 #define ALC_APIENTRY __cdecl
#else
 #define ALC_APIENTRY
#endif

#if defined(TARGET_OS_MAC) && TARGET_OS_MAC
// #pragma export on
#endif

/*
 * The ALCAPI, ALCAPIENTRY, and ALC_INVALID macros are deprecated, but are
 * included for applications porting code from AL 1.0
 */
#define ALCAPI ALC_API
#define ALCAPIENTRY ALC_APIENTRY
#define ALC_INVALID 0


#define ALC_VERSION_0_1         1

typedef struct ALCdevice_struct ALCdevice;
typedef struct ALCcontext_struct ALCcontext;


/** 8-bit boolean */
typedef char ALCboolean;

/** character */
typedef char ALCchar;

/** signed 8-bit 2's complement integer */
typedef char ALCbyte;

/** unsigned 8-bit integer */
typedef unsigned char ALCubyte;

/** signed 16-bit 2's complement integer */
typedef short ALCshort;

/** unsigned 16-bit integer */
typedef unsigned short ALCushort;

/** signed 32-bit 2's complement integer */
typedef int ALCint;

/** unsigned 32-bit integer */
typedef unsigned int ALCuint;

/** non-negative 32-bit binary integer size */
typedef int ALCsizei;

/** enumerated 32-bit value */
typedef int ALCenum;

/** 32-bit IEEE754 floating-point */
typedef float ALCfloat;

/** 64-bit IEEE754 floating-point */
typedef double ALCdouble;

/** void type (for opaque pointers only) */
typedef void ALCvoid;


/* Enumerant values begin at column 50. No tabs. */

/* Boolean False. */
#define ALC_FALSE                                0

/* Boolean True. */
#define ALC_TRUE                                 1

/**
 * followed by <int> Hz
 */
#define ALC_FREQUENCY                            0x1007

/**
 * followed by <int> Hz
 */
#define ALC_REFRESH                              0x1008

/**
 * followed by AL_TRUE, AL_FALSE
 */
#define ALC_SYNC                                 0x1009

/**
 * followed by <int> Num of requested Mono (3D) Sources
 */
#define ALC_MONO_SOURCES                         0x1010

/**
 * followed by <int> Num of requested Stereo Sources
 */
#define ALC_STEREO_SOURCES                       0x1011

/**
 * errors
 */

/**
 * No error
 */
#define ALC_NO_ERROR                             ALC_FALSE

/**
 * No device
 */
#define ALC_INVALID_DEVICE                       0xA001

/**
 * invalid context ID
 */
#define ALC_INVALID_CONTEXT                      0xA002

/**
 * bad enum
 */
#define ALC_INVALID_ENUM                         0xA003

/**
 * bad value
 */
#define ALC_INVALID_VALUE                        0xA004

/**
 * Out of memory.
 */
#define ALC_OUT_OF_MEMORY                        0xA005


/**
 * The Specifier string for default device
 */
#define ALC_DEFAULT_DEVICE_SPECIFIER             0x1004
#define ALC_DEVICE_SPECIFIER                     0x1005
#define ALC_EXTENSIONS                           0x1006

#define ALC_MAJOR_VERSION                        0x1000
#define ALC_MINOR_VERSION                        0x1001

#define ALC_ATTRIBUTES_SIZE                      0x1002
#define ALC_ALL_ATTRIBUTES                       0x1003

/**
 * ALC_ENUMERATE_ALL_EXT enums
 */
#define ALC_DEFAULT_ALL_DEVICES_SPECIFIER        0x1012
#define ALC_ALL_DEVICES_SPECIFIER                0x1013

/**
 * Capture extension
 */
#define ALC_CAPTURE_DEVICE_SPECIFIER             0x310
#define ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER     0x311
#define ALC_CAPTURE_SAMPLES                      0x312


/*
 * Context Management
 */
ALC_API ALCcontext *    ALC_APIENTRY alcCreateContext( ALCdevice *device, const ALCint* attrlist );

ALC_API ALCboolean      ALC_APIENTRY alcMakeContextCurrent( ALCcontext *context );

ALC_API void            ALC_APIENTRY alcProcessContext( ALCcontext *context );

ALC_API void            ALC_APIENTRY alcSuspendContext( ALCcontext *context );

ALC_API void            ALC_APIENTRY alcDestroyContext( ALCcontext *context );

ALC_API ALCcontext *    ALC_APIENTRY alcGetCurrentContext( void );

ALC_API ALCdevice*      ALC_APIENTRY alcGetContextsDevice( ALCcontext *context );


/*
 * Device Management
 */
ALC_API ALCdevice *     ALC_APIENTRY alcOpenDevice( const ALCchar *devicename );

ALC_API ALCboolean      ALC_APIENTRY alcCloseDevice( ALCdevice *device );


/*
 * Error support.
 * Obtain the most recent Context error
 */
ALC_API ALCenum         ALC_APIENTRY alcGetError( ALCdevice *device );


/* 
 * Extension support.
 * Query for the presence of an extension, and obtain any appropriate
 * function pointers and enum values.
 */
ALC_API ALCboolean      ALC_APIENTRY alcIsExtensionPresent( ALCdevice *device, const ALCchar *extname );

ALC_API void  *         ALC_APIENTRY alcGetProcAddress( ALCdevice *device, const ALCchar *funcname );

ALC_API ALCenum         ALC_APIENTRY alcGetEnumValue( ALCdevice *device, const ALCchar *enumname );


/*
 * Query functions
 */
ALC_API const ALCchar * ALC_APIENTRY alcGetString( ALCdevice *device, ALCenum param );

ALC_API void            ALC_APIENTRY alcGetIntegerv( ALCdevice *device, ALCenum param, ALCsizei size, ALCint *data );


/*
 * Capture functions
 */
ALC_API ALCdevice*      ALC_APIENTRY alcCaptureOpenDevice( const ALCchar *devicename, ALCuint frequency, ALCenum format, ALCsizei buffersize );

ALC_API ALCboolean      ALC_APIENTRY alcCaptureCloseDevice( ALCdevice *device );

ALC_API void            ALC_APIENTRY alcCaptureStart( ALCdevice *device );

ALC_API void            ALC_APIENTRY alcCaptureStop( ALCdevice *device );

ALC_API void            ALC_APIENTRY alcCaptureSamples( ALCdevice *device, ALCvoid *buffer, ALCsizei samples );

/*
 * Pointer-to-function types, useful for dynamically getting ALC entry points.
 */
typedef ALCcontext *   (ALC_APIENTRY *LPALCCREATECONTEXT) (ALCdevice *device, const ALCint *attrlist);
typedef ALCboolean     (ALC_APIENTRY *LPALCMAKECONTEXTCURRENT)( ALCcontext *context );
typedef void           (ALC_APIENTRY *LPALCPROCESSCONTEXT)( ALCcontext *context );
typedef void           (ALC_APIENTRY *LPALCSUSPENDCONTEXT)( ALCcontext *context );
typedef void           (ALC_APIENTRY *LPALCDESTROYCONTEXT)( ALCcontext *context );
typedef ALCcontext *   (ALC_APIENTRY *LPALCGETCURRENTCONTEXT)( void );
typedef ALCdevice *    (ALC_APIENTRY *LPALCGETCONTEXTSDEVICE)( ALCcontext *context );
typedef ALCdevice *    (ALC_APIENTRY *LPALCOPENDEVICE)( const ALCchar *devicename );
typedef ALCboolean     (ALC_APIENTRY *LPALCCLOSEDEVICE)( ALCdevice *device );
typedef ALCenum        (ALC_APIENTRY *LPALCGETERROR)( ALCdevice *device );
typedef ALCboolean     (ALC_APIENTRY *LPALCISEXTENSIONPRESENT)( ALCdevice *device, const ALCchar *extname );
typedef void *         (ALC_APIENTRY *LPALCGETPROCADDRESS)(ALCdevice *device, const ALCchar *funcname );
typedef ALCenum        (ALC_APIENTRY *LPALCGETENUMVALUE)(ALCdevice *device, const ALCchar *enumname );
typedef const ALCchar* (ALC_APIENTRY *LPALCGETSTRING)( ALCdevice *device, ALCenum param );
typedef void           (ALC_APIENTRY *LPALCGETINTEGERV)( ALCdevice *device, ALCenum param, ALCsizei size, ALCint *dest );
typedef ALCdevice *    (ALC_APIENTRY *LPALCCAPTUREOPENDEVICE)( const ALCchar *devicename, ALCuint frequency, ALCenum format, ALCsizei buffersize );
typedef ALCboolean     (ALC_APIENTRY *LPALCCAPTURECLOSEDEVICE)( ALCdevice *device );
typedef void           (ALC_APIENTRY *LPALCCAPTURESTART)( ALCdevice *device );
typedef void           (ALC_APIENTRY *LPALCCAPTURESTOP)( ALCdevice *device );
typedef void           (ALC_APIENTRY *LPALCCAPTURESAMPLES)( ALCdevice *device, ALCvoid *buffer, ALCsizei samples );

#if defined(TARGET_OS_MAC) && TARGET_OS_MAC
// #pragma export off
#endif

#if defined(__cplusplus)
}
#endif

#endif /* AL_ALC_H */
// ==========  OpenAL.framework/Headers/OpenAL.h
/*!
	@file		OpenAL.h
	@framework	OpenAL.framework
	@copyright	(c) 2002-2015 by Apple, Inc., all rights reserved.
	@abstract	Umbrella header for OpenAL framework.
*/

#ifndef OpenAL_OpenAL_h
#define OpenAL_OpenAL_h

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <OpenAL/oalStaticBufferExtension.h>
#include <OpenAL/oalMacOSX_OALExtensions.h>

#endif /* defined(OpenAL_OpenAL_h) */
