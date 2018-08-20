// ==========  CoreVideo.framework/Headers/CVBuffer.h
/*
 *  CVBuffer.h
 *  CoreVideo
 *
 *  Copyright (c) 2004-2015 Apple Inc. All rights reserved.
 *
 */
 
 /*! @header CVBuffer.h
	@copyright 2004-2015 Apple Inc. All rights reserved.
	@availability Mac OS X 10.4 or later, and iOS 4.0 or later
    @discussion CVBufferRef types are abstract and only define ways to attach meta data to buffers (such as timestamps,
	        colorspace information, etc.).    CVBufferRefs do not imply any particular kind of data storage.  It could
		be compressed data, image data, etc.
		   
*/

#if !defined(__COREVIDEO_CVBUFFER_H__)
#define __COREVIDEO_CVBUFFER_H__ 1

#include <TargetConditionals.h>
#include <Availability.h>
#include <AvailabilityMacros.h>

#include <CoreVideo/CVBase.h>
#include <CoreVideo/CVReturn.h>
#include <CoreFoundation/CFDictionary.h>
#if TARGET_OS_MAC
#include <stddef.h>
#include <stdint.h>
#endif

#if defined(__cplusplus)
extern "C" {
#endif

#pragma mark CVBufferRef attribute keys

/* The following two keys are useful with the CoreVideo pool and texture cache APIs so that you can specify
   an initial set of default buffer attachments to automatically be attached to the buffer when it is created. */
CV_EXPORT const CFStringRef CV_NONNULL kCVBufferPropagatedAttachmentsKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVBufferNonPropagatedAttachmentsKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

#pragma mark CVBufferRef attachment keys

CV_EXPORT const CFStringRef CV_NONNULL kCVBufferMovieTimeKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);	// Generally only available for frames emitted by QuickTime; CFDictionary containing these two keys:
CV_EXPORT const CFStringRef CV_NONNULL kCVBufferTimeValueKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVBufferTimeScaleKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);


#pragma mark CVBufferRef

typedef uint32_t CVAttachmentMode;
#if COREVIDEO_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CVAttachmentMode
#else
enum
#endif
{
	kCVAttachmentMode_ShouldNotPropagate    = 0,
	kCVAttachmentMode_ShouldPropagate       = 1
};

/*!
    @typedef	CVBufferRef
    @abstract   Base type for all CoreVideo buffers

*/
typedef struct CV_BRIDGED_TYPE(id) __CVBuffer *CVBufferRef;

/*!
    @function   CVBufferRetain
    @abstract   Retains a CVBuffer object
    @discussion Like CFRetain CVBufferRetain increments the retain count of a CVBuffer object. In contrast to the CF call it is NULL safe.
    @param      buffer A CVBuffer object that you want to retain.
    @result     A CVBuffer object that is the same as the passed in buffer.
*/
CV_EXPORT CVBufferRef CV_NULLABLE CVBufferRetain( CVBufferRef CV_NULLABLE buffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
/*!
    @function   CVBufferRelease
    @abstract   Release a CVBuffer object
    @discussion Like CFRetain CVBufferRetain decrements the retain count of a CVBuffer object. If that count consequently becomes zero the memory allocated to the object is deallocated and the object is destroyed. In contrast to the CF call it is NULL safe.
    @param      buffer A CVBuffer object that you want to release.
*/
CV_EXPORT void CVBufferRelease( CV_RELEASES_ARGUMENT CVBufferRef CV_NULLABLE buffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

#pragma mark CVBufferAttachment

/*!
    @function   CVBufferSetAttachment
    @abstract   Sets or adds a attachment of a CVBuffer object
    @discussion You can attach any CF object to a CVBuffer object to store additional information. CVBufferGetAttachment stores an attachement identified by a key. If the key doesn't exist, the attachment will be added. If the key does exist, the existing attachment will be replaced. In bouth cases the retain count of the attachment will be incremented. The value can be any CFType but nil has no defined behavior.
    @param      buffer  Target CVBuffer object.
    @param      key     Key in form of a CFString identifying the desired attachment.
    @param      value	Attachment in form af a CF object.
    @param      attachmentMode	Specifies which attachment mode is desired for this attachment.   A particular attachment key may only exist in
                                a single mode at a time.
*/
CV_EXPORT void	CVBufferSetAttachment( CVBufferRef CV_NONNULL buffer, CFStringRef CV_NONNULL key, CFTypeRef CV_NONNULL value, CVAttachmentMode attachmentMode ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);


/*!
    @function   CVBufferGetAttachment
    @abstract   Returns a specific attachment of a CVBuffer object
    @discussion You can attach any CF object to a CVBuffer object to store additional information. CVBufferGetAttachment retrieves an attachement identified by a key.
    @param      buffer  Target CVBuffer object.
    @param      key	Key in form of a CFString identifying the desired attachment.
    @param      attachmentMode.  Returns the mode of the attachment, if desired.  May be NULL.
    @result     If found the attachment object
*/
CV_EXPORT CFTypeRef CV_NULLABLE CVBufferGetAttachment( CVBufferRef CV_NONNULL buffer, CFStringRef CV_NONNULL key, CVAttachmentMode * CV_NULLABLE attachmentMode ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVBufferRemoveAttachment
    @abstract   Removes a specific attachment of a CVBuffer object
    @discussion CVBufferRemoveAttachment removes an attachement identified by a key. If found the attachement is removed and the retain count decremented.
    @param      buffer  Target CVBuffer object.
    @param      key	Key in form of a CFString identifying the desired attachment.
*/
CV_EXPORT void	CVBufferRemoveAttachment( CVBufferRef CV_NONNULL buffer, CFStringRef CV_NONNULL key ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVBufferRemoveAllAttachments
    @abstract   Removes all attachments of a CVBuffer object
    @discussion While CVBufferRemoveAttachment removes a specific attachement identified by a key CVBufferRemoveAllAttachments removes all attachments of a buffer and decrements their retain counts.
    @param      buffer  Target CVBuffer object.
*/
CV_EXPORT void	CVBufferRemoveAllAttachments( CVBufferRef CV_NONNULL buffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVBufferGetAttachments
    @abstract   Returns all attachments of a CVBuffer object
    @discussion CVBufferGetAttachments is a convenience call that returns all attachments with their corresponding keys in a CFDictionary.
    @param      buffer  Target CVBuffer object.
    @result     A CFDictionary with all buffer attachments identified by there keys. If no attachment is present, the dictionary is empty.  Returns NULL
		for invalid attachment mode.
*/
CV_EXPORT CFDictionaryRef CV_NULLABLE CVBufferGetAttachments( CVBufferRef CV_NONNULL buffer, CVAttachmentMode attachmentMode ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVBufferSetAttachments
    @abstract   Sets a set of attachments for a CVBuffer
    @discussion CVBufferSetAttachments is a convenience call that in turn calls CVBufferSetAttachment for each key and value in the given dictionary. All key value pairs must be in the root level of the dictionary.
    @param      buffer  Target CVBuffer object.
*/
CV_EXPORT void CVBufferSetAttachments( CVBufferRef CV_NONNULL buffer, CFDictionaryRef CV_NONNULL theAttachments, CVAttachmentMode attachmentMode ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVBufferPropagateAttachments
    @abstract   Copy all propagatable attachments from one buffer to another.
    @discussion CVBufferPropagateAttachments is a convenience call that copies all attachments with a mode of kCVAttachmentMode_ShouldPropagate from one
                buffer to another.
    @param      sourceBuffer  CVBuffer to copy attachments from.
    @param      destinationBuffer  CVBuffer to copy attachments to.
*/
CV_EXPORT void  CVBufferPropagateAttachments( CVBufferRef CV_NONNULL sourceBuffer, CVBufferRef CV_NONNULL destinationBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

#if defined(__cplusplus)
}
#endif

#endif
// ==========  CoreVideo.framework/Headers/CVOpenGLESTextureCache.h
/*
 *  CVOpenGLESTextureCache.h
 *  CoreVideo
 *
 *  Copyright 2011-2015 Apple Inc. All rights reserved.
 *
 */

/*! @header CVOpenGLESTextureCache.h
 @copyright 2011-2015 Apple Inc. All rights reserved.
 @availability iOS 5.0 or later
 @discussion A CoreVideo TextureCache is used to cache and manage CVOpenGLESTextures.
 
 */

#if !defined(__COREVIDEO__CVOPENGLESTEXTURECACHE_H__)
#define __COREVIDEO__CVOPENGLESTEXTURECACHE_H__ 1

#include <CoreVideo/CVBase.h>
#include <CoreVideo/CVReturn.h>
#include <CoreVideo/CVBuffer.h>
#include <CoreVideo/CVOpenGLESTexture.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
    @typedef	CVOpenGLESTextureCacheRef
    @abstract   CoreVideo OpenGLES Texture Cache

*/
typedef struct CV_BRIDGED_TYPE(id) __CVOpenGLESTextureCache *CVOpenGLESTextureCacheRef;

#ifndef COREVIDEO_USE_EAGLCONTEXT_CLASS_IN_API
#define COREVIDEO_USE_EAGLCONTEXT_CLASS_IN_API 1
#endif

#if defined(__OBJC__) && COREVIDEO_USE_EAGLCONTEXT_CLASS_IN_API
@class EAGLContext;
typedef EAGLContext *CVEAGLContext;
#else
typedef void *CVEAGLContext;
#endif

//
// cacheAttributes
//
// By default, textures will age out after one second.  Setting a maximum
// texture age of zero will disable the age-out mechanism completely.
// CVOpenGLESTextureCacheFlush() can be used to force eviction in either case.

CV_EXPORT const CFStringRef CV_NONNULL kCVOpenGLESTextureCacheMaximumTextureAgeKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

//
// textureAttributes - reserved for future use

CV_EXPORT CFTypeID CVOpenGLESTextureCacheGetTypeID(void) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*!
    @function   CVOpenGLESTextureCacheCreate
    @abstract   Creates a new Texture Cache.
    @param      allocator The CFAllocatorRef to use for allocating the cache.  May be NULL.
    @param      cacheAttributes A CFDictionaryRef containing the attributes of the cache itself.   May be NULL.
    @param      eaglContext The OpenGLES 2.0 context into which the texture objects will be created.  OpenGLES 1.x contexts are not supported.
    @param      textureAttributes A CFDictionaryRef containing the attributes to be used for creating the CVOpenGLESTexture objects.  May be NULL.
    @param      cacheOut   The newly created texture cache will be placed here
    @result     Returns kCVReturnSuccess on success
*/
CV_EXPORT CVReturn CVOpenGLESTextureCacheCreate(
    CFAllocatorRef CV_NULLABLE allocator,
    CFDictionaryRef CV_NULLABLE cacheAttributes,
    CVEAGLContext CV_NONNULL eaglContext,
    CFDictionaryRef CV_NULLABLE textureAttributes,
    CV_RETURNS_RETAINED_PARAMETER CVOpenGLESTextureCacheRef CV_NULLABLE * CV_NONNULL cacheOut) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*!
    @function   CVOpenGLESTextureCacheCreateTextureFromImage
    @abstract   Creates a CVOpenGLESTexture object from an existing CVImageBuffer
    @param      allocator The CFAllocatorRef to use for allocating the CVOpenGLESTexture object.  May be NULL.
    @param      textureCache The texture cache object that will manage the texture.
    @param      sourceImage The CVImageBuffer that you want to create a CVOpenGLESTexture from.
    @param      textureAttributes A CFDictionaryRef containing attributes to be used for creating the CVOpenGLESTexture objects.  May be NULL.
    @param      target Specifies the target texture.  GL_TEXTURE_2D and GL_RENDERBUFFER are the only targets currently supported.
    @param      internalFormat Specifies the number of color components in the texture.  Examples are GL_RGBA, GL_LUMINANCE, GL_RGBA8_OES, GL_RED, and GL_RG.
    @param      width Specifies the width of the texture image.
    @param      height Specifies the height of the texture image.
    @param      format Specifies the format of the pixel data.  Examples are GL_RGBA and GL_LUMINANCE.
    @param      type Specifies the data type of the pixel data.  Examples are GL_UNSIGNED_BYTE.
    @param      planeIndex Specifies the plane of the CVImageBuffer to map bind.  Ignored for non-planar CVImageBuffers.
    @param      textureOut The newly created texture object will be placed here.
    @result     Returns kCVReturnSuccess on success
    @discussion Creates or returns a cached CVOpenGLESTexture texture object mapped to the CVImageBuffer and
                associated params.  This creates a live binding between the CVImageBuffer and underlying
                CVOpenGLESTexture texture object.  The EAGLContext associated with the cache may be modified,
                to create, delete, or bind textures.  When used as a source texture or GL_COLOR_ATTACHMENT,
                the CVImageBuffer must be unlocked before rendering.  The source or render buffer texture should
                not be re-used until the rendering has completed.  This can be guaranteed by calling glFlush().

                Here are some example mappings:

                Mapping a BGRA buffer as a source texture:
                CVOpenGLESTextureCacheCreateTextureFromImage(kCFAllocatorDefault, textureCache, pixelBuffer, NULL, GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, 0, &outTexture);

                Mapping a BGRA buffer as a renderbuffer:
                CVOpenGLESTextureCacheCreateTextureFromImage(kCFAllocatorDefault, textureCache, pixelBuffer, NULL, GL_RENDERBUFFER, GL_RGBA8_OES, width, height, GL_RGBA, GL_UNSIGNED_BYTE, 0, &outTexture);

                Mapping the luma plane of a 420v buffer as a source texture:
                CVOpenGLESTextureCacheCreateTextureFromImage(kCFAllocatorDefault, textureCache, pixelBuffer, NULL, GL_TEXTURE_2D, GL_LUMINANCE, width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, 0, &outTexture);

                Mapping the chroma plane of a 420v buffer as a source texture:
                CVOpenGLESTextureCacheCreateTextureFromImage(kCFAllocatorDefault, textureCache, pixelBuffer, NULL, GL_TEXTURE_2D, GL_LUMINANCE_ALPHA, width/2, height/2, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, 1, &outTexture);

                Mapping a yuvs buffer as a source texture (note: yuvs/f and 2vuy are unpacked and resampled -- not colorspace converted)
                CVOpenGLESTextureCacheCreateTextureFromImage(kCFAllocatorDefault, textureCache, pixelBuffer, NULL, GL_TEXTURE_2D, GL_RGB_422_APPLE, width, height, GL_RGB_422_APPLE, GL_UNSIGNED_SHORT_8_8_APPLE, 1, &outTexture);
*/
CV_EXPORT CVReturn CVOpenGLESTextureCacheCreateTextureFromImage(
    CFAllocatorRef CV_NULLABLE allocator,
    CVOpenGLESTextureCacheRef CV_NONNULL textureCache,
    CVImageBufferRef CV_NONNULL sourceImage,
    CFDictionaryRef CV_NULLABLE textureAttributes,
    GLenum target,
    GLint internalFormat,
    GLsizei width,
    GLsizei height,
    GLenum format,
    GLenum type,
    size_t planeIndex,
    CV_RETURNS_RETAINED_PARAMETER CVOpenGLESTextureRef CV_NULLABLE * CV_NONNULL textureOut ) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*!
    @function   CVOpenGLESTextureCacheFlush
    @abstract   Performs internal housekeeping/recycling operations
    @discussion This call must be made periodically to give the texture cache a chance to make OpenGLES calls
                on the OpenGLES context used to create it in order to do housekeeping operations.  The EAGLContext
	            associated with the cache may be used to delete or unbind textures.
    @param      textureCache The texture cache object to flush
    @param      options Currently unused, set to 0.
*/
CV_EXPORT void CVOpenGLESTextureCacheFlush( CVOpenGLESTextureCacheRef CV_NONNULL textureCache, CVOptionFlags options ) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

#if defined(__cplusplus)
}
#endif

#endif
// ==========  CoreVideo.framework/Headers/CVBase.h
/*
 *  CVBase.h
 *  CoreVideo
 *
 *  Copyright (c) 2004-2015 Apple Inc. All rights reserved.
 *
 */
 
 /*! @header CVBase.h
	@copyright 2004-2015 Apple Inc. All rights reserved.
	@availability Mac OS X 10.4 or later, and iOS 4.0 or later
    @discussion Here you can find the type declarations for CoreVideo. CoreVideo uses a CVTimeStamp structure to store video display time stamps.
*/

 
#if !defined(__COREVIDEO_CVBASE_H__)
#define __COREVIDEO_CVBASE_H__ 1

#include <TargetConditionals.h>
#include <Availability.h>
#include <AvailabilityMacros.h>

#if TARGET_OS_WIN32
#pragma warning (disable: 4068)		// ignore unknown pragmas
#endif

#ifndef AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER
#define AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER       WEAK_IMPORT_ATTRIBUTE
#endif

#ifndef __AVAILABILITY_INTERNAL__MAC_10_7
#define __AVAILABILITY_INTERNAL__MAC_10_7        __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

#ifndef __AVAILABILITY_INTERNAL__MAC_10_8
#define __AVAILABILITY_INTERNAL__MAC_10_8        __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

#ifndef __AVAILABILITY_INTERNAL__MAC_10_9
#define __AVAILABILITY_INTERNAL__MAC_10_9        __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

#ifndef __AVAILABILITY_INTERNAL__MAC_10_10
#define __AVAILABILITY_INTERNAL__MAC_10_10        __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

#ifndef __AVAILABILITY_INTERNAL__IPHONE_8_0
#define __AVAILABILITY_INTERNAL__IPHONE_8_0        __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

#ifndef __AVAILABILITY_INTERNAL__MAC_10_11
#define __AVAILABILITY_INTERNAL__MAC_10_11        __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

#ifndef __AVAILABILITY_INTERNAL__IPHONE_9_0
#define __AVAILABILITY_INTERNAL__IPHONE_9_0        __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

#include <CoreFoundation/CFBase.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define COREVIDEO_SUPPORTS_DIRECT3D 	(TARGET_OS_WIN32)
#define COREVIDEO_SUPPORTS_OPENGL 		(TARGET_OS_MAC && ! TARGET_OS_IPHONE)
#define COREVIDEO_SUPPORTS_OPENGLES		(TARGET_OS_MAC && TARGET_OS_IPHONE)
#define COREVIDEO_SUPPORTS_COLORSPACE 	((TARGET_OS_MAC && ! TARGET_OS_IPHONE) || (TARGET_OS_WIN32))
#define COREVIDEO_SUPPORTS_DISPLAYLINK 	(TARGET_OS_MAC && ! TARGET_OS_IPHONE)
#define COREVIDEO_SUPPORTS_IOSURFACE	(TARGET_OS_IPHONE ? TARGET_OS_EMBEDDED : (TARGET_OS_MAC && ((MAC_OS_X_VERSION_MAX_ALLOWED >= 1060))))
#define COREVIDEO_SUPPORTS_IOSURFACE_PREFETCH    (TARGET_OS_EMBEDDED && (__IPHONE_OS_VERSION_MIN_REQUIRED >= 80300))
#define COREVIDEO_SUPPORTS_METAL        (COREVIDEO_SUPPORTS_IOSURFACE && (TARGET_OS_IPHONE || (MAC_OS_X_VERSION_MIN_REQUIRED >= 101100)) && (! TARGET_OS_WATCH))

#define COREVIDEO_USE_DERIVED_ENUMS_FOR_CONSTANTS	(__cplusplus && __cplusplus >= 201103L && (__has_extension(cxx_strong_enums) || __has_feature(objc_fixed_enum))) || (!__cplusplus && __has_feature(objc_fixed_enum))

#if (TARGET_OS_IPHONE || TARGET_OS_MAC) && defined(__has_feature) && __has_feature(nullability)
	#define COREVIDEO_DECLARE_NULLABILITY 1
#endif

#if (TARGET_OS_IPHONE || TARGET_OS_MAC) && defined(__has_feature) && __has_feature(attribute_cf_returns_on_parameters)
#define CV_RETURNS_RETAINED_PARAMETER		CF_RETURNS_RETAINED
#else
#define CV_RETURNS_RETAINED_PARAMETER
#endif

#if (TARGET_OS_IPHONE || TARGET_OS_MAC) && defined(__has_feature) && __has_feature(attribute_cf_consumed)
#define CV_RELEASES_ARGUMENT        CF_RELEASES_ARGUMENT
#else
#define CV_RELEASES_ARGUMENT
#endif


#if (TARGET_OS_IPHONE || TARGET_OS_MAC) && defined(__has_feature) && __has_feature(objc_bridge_id)
#define CV_BRIDGED_TYPE(type)       CF_BRIDGED_TYPE(type)
#else
#define CV_BRIDGED_TYPE(type)
#endif

#if COREVIDEO_DECLARE_NULLABILITY
#define CV_NULLABLE __nullable
#define CV_NONNULL __nonnull
#else
#define CV_NULLABLE
#define CV_NONNULL
#endif

#if TARGET_OS_WIN32 && defined(CV_BUILDING_CV) && defined(__cplusplus)
#define CV_EXPORT extern "C" __declspec(dllexport) 
#elif TARGET_OS_WIN32 && defined(CV_BUILDING_CV) && !defined(__cplusplus)
#define CV_EXPORT extern __declspec(dllexport) 
#elif TARGET_OS_WIN32 && defined(__cplusplus)
#define CV_EXPORT extern "C" __declspec(dllimport) 
#elif TARGET_OS_WIN32
#define CV_EXPORT extern __declspec(dllimport) 
#else
#define CV_EXPORT CF_EXPORT 
#endif

#define CV_INLINE CF_INLINE

#if COREVIDEO_SUPPORTS_DIRECT3D
#define CVDIRECT3DDEVICE LPDIRECT3DDEVICE9
#define CVDIRECT3DTEXTURE LPDIRECT3DTEXTURE9
#define CVDIRECT3DSURFACE LPDIRECT3DSURFACE9
#define CVDIRECT3D LPDIRECT3D9
#endif //COREVIDEO_SUPPORTS_DIRECT3D

/*!
    @typedef	CVOptionFlags
    @abstract   Flags to be used for the display and render call back functions.
    @discussion ***Values to be defined***
*/
typedef uint64_t CVOptionFlags;

/*!
    @struct         CVSMPTETime
    @abstract       A structure for holding a SMPTE time.
    @field          subframes
                        The number of subframes in the full message.
    @field          subframeDivisor
                        The number of subframes per frame (typically 80).
    @field          counter
                        The total number of messages received.
    @field          type
                        The kind of SMPTE time using the SMPTE time type constants.
    @field          flags
                        A set of flags that indicate the SMPTE state.
    @field          hours
                        The number of hours in the full message.
    @field          minutes
                        The number of minutes in the full message.
    @field          seconds
                        The number of seconds in the full message.
    @field          frames
                        The number of frames in the full message.
*/
struct CVSMPTETime
{
    SInt16  subframes;
    SInt16  subframeDivisor;
    UInt32  counter;
    UInt32  type;
    UInt32  flags;
    SInt16  hours;
    SInt16  minutes;
    SInt16  seconds;
    SInt16  frames;
};
typedef struct CVSMPTETime    CVSMPTETime;

/*!
    @enum           SMPTE Time Types
    @abstract       Constants that describe the type of SMPTE time.
    @constant       kCVSMPTETimeType24
                        24 Frame
    @constant       kCVSMPTETimeType25
                        25 Frame
    @constant       kCVSMPTETimeType30Drop
                        30 Drop Frame
    @constant       kCVSMPTETimeType30
                        30 Frame
    @constant       kCVSMPTETimeType2997
                        29.97 Frame
    @constant       kCVSMPTETimeType2997Drop
                        29.97 Drop Frame
    @constant       kCVSMPTETimeType60
                        60 Frame
    @constant       kCVSMPTETimeType5994
                        59.94 Frame
*/
enum
{
    kCVSMPTETimeType24        = 0,
    kCVSMPTETimeType25        = 1,
    kCVSMPTETimeType30Drop    = 2,
    kCVSMPTETimeType30        = 3,
    kCVSMPTETimeType2997      = 4,
    kCVSMPTETimeType2997Drop  = 5,
    kCVSMPTETimeType60        = 6,
    kCVSMPTETimeType5994      = 7
};

/*!
    @enum           SMPTE State Flags
    @abstract       Flags that describe the SMPTE time state.
    @constant       kCVSMPTETimeValid
                        The full time is valid.
    @constant       kCVSMPTETimeRunning
                        Time is running.
*/
enum
{
    kCVSMPTETimeValid     = (1L << 0),
    kCVSMPTETimeRunning   = (1L << 1)
};


enum {
    kCVTimeIsIndefinite = 1 << 0
};

typedef struct
{
    int64_t	    timeValue;
    int32_t	    timeScale;
    int32_t	    flags;
} CVTime;

/*!
    @struct CVTimeStamp
    @abstract CoreVideo uses a CVTimeStamp structure to store video display time stamps.
    @discussion This structure is purposely very similar to AudioTimeStamp defined in the CoreAudio framework. 
		Most of the CVTimeStamp struct should be fairly self-explanatory. However, it is probably worth pointing out that unlike the audio time stamps, floats are not used to represent the video equivalent of sample times. This was done partly to avoid precision issues, and partly because QuickTime still uses integers for time values and time scales. In the actual implementation it has turned out to be very convenient to use integers, and we can represent framerates like NTSC (30000/1001 fps) exactly. The mHostTime structure field uses the same Mach absolute time base that is used in CoreAudio, so that clients of the CoreVideo API can synchronize between the two subsystems.
    @field version The current CVTimeStamp is version 0.
    @field videoTimeScale The scale (in units per second) of the videoTime and videoPeriod values
    @field videoTime This represents the start of a frame (or field for interlaced)
    @field hostTime Host root timebase time
    @field rateScalar This is the current rate of the device as measured by the timestamps, divided by the nominal rate
    @field videoRefreshPeriod This is the nominal update period of the current output device
    @field smpteTime SMPTE time representation of the time stamp. 
    @field flags Possible values are:		
		kCVTimeStampVideoTimeValid
		kCVTimeStampHostTimeValid
		kCVTimeStampSMPTETimeValid
		kCVTimeStampVideoPeriodValid
		kCVTimeStampRateScalarValid
		There are flags for each field to make it easier to detect interlaced vs progressive output
		kCVTimeStampTopField
		kCVTimeStampBottomField
		Some commonly used combinations of timestamp flags
		kCVTimeStampVideoHostTimeValid
		kCVTimeStampIsInterlaced
    @field reserved Reserved. Do not use.

*/
typedef struct
{
    uint32_t			version;
    int32_t			videoTimeScale;
    int64_t			videoTime;
    uint64_t			hostTime;
    double			rateScalar;
    int64_t			videoRefreshPeriod;
    CVSMPTETime			smpteTime;
    uint64_t			flags;
    uint64_t			reserved;
} CVTimeStamp; 

// Flags for the CVTimeStamp structure
enum
{
    kCVTimeStampVideoTimeValid              = (1L << 0),
    kCVTimeStampHostTimeValid               = (1L << 1),
    kCVTimeStampSMPTETimeValid              = (1L << 2),
    kCVTimeStampVideoRefreshPeriodValid     = (1L << 3),
    kCVTimeStampRateScalarValid             = (1L << 4),
    
    // There are flags for each field to make it easier to detect interlaced vs progressive output
    kCVTimeStampTopField                    = (1L << 16),
    kCVTimeStampBottomField                 = (1L << 17)
};

//	Some commonly used combinations of timestamp flags
enum
{
    kCVTimeStampVideoHostTimeValid   = (kCVTimeStampVideoTimeValid | kCVTimeStampHostTimeValid),
    kCVTimeStampIsInterlaced	     = (kCVTimeStampTopField | kCVTimeStampBottomField)
};

CV_EXPORT const CVTime kCVZeroTime;
CV_EXPORT const CVTime kCVIndefiniteTime;

#if defined(__cplusplus)
}
#endif

#endif
// ==========  CoreVideo.framework/Headers/CVImageBuffer.h
/*
 *  CVImageBuffer.h
 *  CoreVideo
 *
 *  Copyright (c) 2004-2015 Apple Inc. All rights reserved.
 *
 */
 
 /*! @header CVImageBuffer.h
	@copyright 2004-2015 Apple Inc. All rights reserved.
	@availability Mac OS X 10.4 or later, and iOS 4.0 or later
    @discussion CVImageBufferRef types are abstract and define various attachments and convenience
		calls for retreiving image related bits of data.
		   
*/

#if !defined(__COREVIDEO_CVIMAGEBUFFER_H__)
#define __COREVIDEO_CVIMAGEBUFFER_H__ 1

#include <TargetConditionals.h>
#include <Availability.h>
#include <AvailabilityMacros.h>

#if TARGET_OS_IPHONE || TARGET_OS_WIN32
#include <CoreGraphics/CoreGraphics.h>
#else
#include <ApplicationServices/ApplicationServices.h>
#endif
#include <CoreVideo/CVBuffer.h>

#if defined(__cplusplus)
extern "C" {
#endif

#pragma mark CVImageBufferRef attachment keys

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferCGColorSpaceKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CGColorSpaceRef

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferCleanApertureKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFDictionary containing the following four keys
CV_EXPORT const CFStringRef CV_NONNULL	kCVImageBufferCleanApertureWidthKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);			// CFNumber
CV_EXPORT const CFStringRef CV_NONNULL	kCVImageBufferCleanApertureHeightKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);			// CFNumber
CV_EXPORT const CFStringRef CV_NONNULL	kCVImageBufferCleanApertureHorizontalOffsetKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		// CFNumber, horizontal offset from center of image buffer
CV_EXPORT const CFStringRef CV_NONNULL	kCVImageBufferCleanApertureVerticalOffsetKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		// CFNumber, vertical offset from center of image buffer
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferPreferredCleanApertureKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);			// CFDictionary containing same keys as kCVImageBufferCleanApertureKey

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferFieldCountKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferFieldDetailKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFString with one of the following four values
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferFieldDetailTemporalTopFirst __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		// CFString
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferFieldDetailTemporalBottomFirst __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		// CFString
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferFieldDetailSpatialFirstLineEarly __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		// CFString
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferFieldDetailSpatialFirstLineLate __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		// CFString

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferPixelAspectRatioKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFDictionary with the following two keys
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferPixelAspectRatioHorizontalSpacingKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);	// CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferPixelAspectRatioVerticalSpacingKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);	// CFNumber

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferDisplayDimensionsKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFDictionary with the following two keys
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferDisplayWidthKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferDisplayHeightKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFNumber

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferGammaLevelKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFNumber describing the gamma level, used in absence of (or ignorance of) kCVImageBufferTransferFunctionKey

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferICCProfileKey __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_4_0);				// CFData representation of the ICC profile

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferYCbCrMatrixKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFString describing the color matrix for YCbCr->RGB. This key can be one of the following values:
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferYCbCrMatrix_ITU_R_709_2 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);			// CFString
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferYCbCrMatrix_ITU_R_601_4 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);			// CFString
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferYCbCrMatrix_SMPTE_240M_1995 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		// CFString
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferYCbCrMatrix_DCI_P3 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);				// CFString
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferYCbCrMatrix_P3_D65 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);				// CFString
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferYCbCrMatrix_ITU_R_2020 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);		// CFString

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferColorPrimariesKey __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);				// CFString describing the color primaries. This key can be one of the following values
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferColorPrimaries_ITU_R_709_2 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferColorPrimaries_EBU_3213 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferColorPrimaries_SMPTE_C __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferColorPrimaries_P22 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferColorPrimaries_DCI_P3 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferColorPrimaries_P3_D65 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferColorPrimaries_ITU_R_2020 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunctionKey __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);				// CFString describing the transfer function. This key can be one of the following values
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunction_ITU_R_709_2 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunction_SMPTE_240M_1995 __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunction_UseGamma __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunction_EBU_3213 __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);			// Should not be used.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunction_SMPTE_C __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);			// Should not be used.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunction_ITU_R_2020 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);

/* Chroma siting information. For progressive images, only the TopField value is used. */
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocationTopFieldKey __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);			// CFString with one of the following CFString values
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocationBottomFieldKey __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);		// CFString with one of the following CFString values
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocation_Left __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);			    // Chroma sample is horizontally co-sited with the left column of luma samples, but centered vertically.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocation_Center __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);			    // Chroma sample is fully centered
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocation_TopLeft __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);			    // Chroma sample is co-sited with the top-left luma sample.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocation_Top __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);			    // Chroma sample is horizontally centered, but co-sited with the top row of luma samples.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocation_BottomLeft __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);		    // Chroma sample is co-sited with the bottom-left luma sample.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocation_Bottom __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);			    // Chroma sample is horizontally centered, but co-sited with the bottom row of luma samples.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocation_DV420 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);			    // Cr and Cb samples are alternately co-sited with the left luma samples of the same field.

// These describe the format of the original subsampled data before conversion to 422/2vuy.   In order to use
// these tags, the data must have been converted to 4:2:2 via simple pixel replication.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaSubsamplingKey __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);		// CFString/CFNumber with one of the following values
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaSubsampling_420 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaSubsampling_422 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaSubsampling_411 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);

// Can be set to kCFBooleanTrue as a hint that the alpha channel is fully opaque.  Not used if the pixel format type has no alpha channel.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferAlphaChannelIsOpaque __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
	
#pragma mark CVImageBufferRef

/*!
    @typedef	CVImageBufferRef
    @abstract   Base type for all CoreVideo image buffers

*/
typedef CVBufferRef CVImageBufferRef;

/*!
    @function   CVImageBufferGetEncodedSize
    @abstract   Returns the full encoded dimensions of a CVImageBuffer.  For example, for an NTSC DV frame this would be 720x480
    @param      imageBuffer A CVImageBuffer that you wish to retrieve the encoded size from.
    @result     A CGSize returning the full encoded size of the buffer
		Returns zero size if called with a non-CVImageBufferRef type or NULL.
*/
CV_EXPORT CGSize CVImageBufferGetEncodedSize( CVImageBufferRef CV_NONNULL imageBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVImageBufferGetDisplaySize
    @abstract   Returns the nominal output display size (in square pixels) of a CVImageBuffer.  
                For example, for an NTSC DV frame this would be 640x480
    @param      imageBuffer A CVImageBuffer that you wish to retrieve the display size from.
    @result     A CGSize returning the nominal display size of the buffer
		Returns zero size if called with a non-CVImageBufferRef type or NULL.
*/
CV_EXPORT CGSize CVImageBufferGetDisplaySize( CVImageBufferRef CV_NONNULL imageBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVImageBufferGetCleanRect
    @abstract   Returns the source rectangle of a CVImageBuffer that represents the clean aperture
		of the buffer in encoded pixels.    For example, an NTSC DV frame would return a CGRect with an
		origin of 8,0 and a size of 704,480.		
		Note that the origin of this rect always the lower left	corner.   This is the same coordinate system as
		used by CoreImage.
    @param      imageBuffer A CVImageBuffer that you wish to retrieve the display size from.
    @result     A CGSize returning the nominal display size of the buffer
		Returns zero rect if called with a non-CVImageBufferRef type or NULL.
*/
CV_EXPORT CGRect CVImageBufferGetCleanRect( CVImageBufferRef CV_NONNULL imageBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVImageBufferIsFlipped
    @abstract   Returns whether the image is flipped vertically or not.
    @param      CVImageBuffer target
    @result     True if 0,0 in the texture is upper left, false if 0,0 is lower left.
*/
CV_EXPORT Boolean CVImageBufferIsFlipped( CVImageBufferRef CV_NONNULL imageBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);


#if COREVIDEO_SUPPORTS_COLORSPACE
/*!
    @function   CVImageBufferGetColorSpace
    @abstract   Returns the color space of a CVImageBuffer.
    @param      imageBuffer A CVImageBuffer that you wish to retrieve the color space from.
    @result     A CGColorSpaceRef representing the color space of the buffer.
		Returns NULL if called with a non-CVImageBufferRef type or NULL.
*/
CV_EXPORT CGColorSpaceRef CV_NULLABLE CVImageBufferGetColorSpace( CVImageBufferRef CV_NONNULL imageBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
   @function   CVImageBufferCreateColorSpaceFromAttachments
   @abstract   Attempts to synthesize a CGColorSpace from an image buffer's attachments.
   @param      attachments A CFDictionary of attachments for an image buffer, obtained using CVBufferGetAttachments().
   @result     A CGColorSpaceRef representing the color space of the buffer.
		Returns NULL if the attachments dictionary does not contain the information required to synthesize a CGColorSpace.
   @discussion
	To generate a CGColorSpace, the attachments dictionary should include values for either:
		1. kCVImageBufferICCProfile
		2. kCVImageBufferColorPrimariesKey, kCVImageBufferTransferFunctionKey, and kCVImageBufferYCbCrMatrixKey (and possibly kCVImageBufferGammaLevelKey)
	The client is responsible for releasing the CGColorSpaceRef when it is done with it (CGColorSpaceRelease() or CFRelease())
		
*/
CV_EXPORT CGColorSpaceRef CV_NULLABLE CVImageBufferCreateColorSpaceFromAttachments( CFDictionaryRef CV_NONNULL attachments ) __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_NA);

#endif

#if defined(__cplusplus)
}
#endif

#endif
// ==========  CoreVideo.framework/Headers/CVPixelBufferPool.h
/*
 *  CVPixelBufferPool.h
 *  CoreVideo
 *
 *  Copyright 2004-2015 Apple Inc. All rights reserved.
 *
 */

 /*! @header CVPixelBufferPool.h
	@copyright 2004-2015 Apple Inc. All rights reserved.
	@availability Mac OS X 10.4 or later, and iOS 4.0 or later
    @discussion CVPixelBufferPool is a utility object for managing a set of CVPixelBuffer objects that are going to be recycled.
		   
*/

#if !defined(__COREVIDEO__CVPIXELBUFFERPOOL_H__)
#define __COREVIDEO__CVPIXELBUFFERPOOL_H__ 1

#include <TargetConditionals.h>
#include <Availability.h>
#include <AvailabilityMacros.h>

#include <CoreVideo/CVBase.h>
#include <CoreVideo/CVReturn.h>
#include <CoreVideo/CVPixelBuffer.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct CV_BRIDGED_TYPE(id) __CVPixelBufferPool *CVPixelBufferPoolRef;

// By default, buffers will age out after one second.   If required, setting an age of zero will disable
// the age-out mechanism completely.

CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferPoolMinimumBufferCountKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferPoolMaximumBufferAgeKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);


CV_EXPORT CFTypeID CVPixelBufferPoolGetTypeID(void) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferPoolRetain
    @abstract   Retains a CVPixelBufferPoolRef object
    @discussion Equivalent to CFRetain, but NULL safe
    @param      buffer A CVPixelBufferPoolRef object that you want to retain.
    @result     A CVPixelBufferPoolRef object that is the same as the passed in buffer.
*/
CV_EXPORT CVPixelBufferPoolRef CV_NULLABLE CVPixelBufferPoolRetain( CVPixelBufferPoolRef CV_NULLABLE pixelBufferPool ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0); // NULL-safe

/*!
    @function   CVPixelBufferPoolRelease
    @abstract   Releases a CVPixelBufferPoolRef object
    @discussion Equivalent to CFRelease, but NULL safe
    @param      buffer A CVPixelBufferPoolRef object that you want to release.
*/
CV_EXPORT void CVPixelBufferPoolRelease( CV_RELEASES_ARGUMENT CVPixelBufferPoolRef CV_NULLABLE pixelBufferPool ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0); // NULL-safe

/*!
    @function   CVPixelBufferPoolCreate
    @abstract   Creates a new Pixel Buffer pool.
    @param      allocator The CFAllocatorRef to use for allocating this buffer pool.  May be NULL.
    @param      attributes   A CFDictionaryRef containing the attributes to be used for creating new PixelBuffers within the pool.
    @param      poolOut   The newly created pool will be placed here
    @result     Returns kCVReturnSuccess on success
*/
CV_EXPORT CVReturn CVPixelBufferPoolCreate(
    CFAllocatorRef CV_NULLABLE allocator,
    CFDictionaryRef CV_NULLABLE poolAttributes,
    CFDictionaryRef CV_NULLABLE pixelBufferAttributes,
    CV_RETURNS_RETAINED_PARAMETER CVPixelBufferPoolRef CV_NULLABLE * CV_NONNULL poolOut ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferPoolGetAttributes
    @abstract   Returns the pool attributes dictionary for a CVPixelBufferPool
    @param      pool  The CVPixelBufferPoolRef to retrieve the attributes from
    @result     Returns the pool attributes dictionary, or NULL on failure.
*/
CV_EXPORT CFDictionaryRef CV_NULLABLE CVPixelBufferPoolGetAttributes( CVPixelBufferPoolRef CV_NONNULL pool ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferPoolGetPixelBufferAttributes
    @abstract   Returns the attributes of pixel buffers that will be created from this pool.
    @discussion This function is provided for those cases where you may need to know some information about the buffers that
                will be created up front.
    @param      pool  The CVPixelBufferPoolRef to retrieve the attributes from
    @result     Returns the pixel buffer attributes dictionary, or NULL on failure.
*/
CV_EXPORT CFDictionaryRef CV_NULLABLE CVPixelBufferPoolGetPixelBufferAttributes( CVPixelBufferPoolRef CV_NONNULL pool ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferPoolCreatePixelBuffer
    @abstract   Creates a new PixelBuffer object from the pool.
    @discussion The function creates a new (attachment-free) CVPixelBuffer using the pixel buffer attributes specifed during pool creation.
    @param      allocator The CFAllocatorRef to use for creating the pixel buffer.  May be NULL.
    @param      pool      The CVPixelBufferPool that should create the new CVPixelBuffer.
    @param      pixelBufferOut   The newly created pixel buffer will be placed here
    @result     Returns kCVReturnSuccess on success
*/
CV_EXPORT CVReturn CVPixelBufferPoolCreatePixelBuffer(
    CFAllocatorRef CV_NULLABLE allocator,
    CVPixelBufferPoolRef CV_NONNULL pixelBufferPool,
    CV_RETURNS_RETAINED_PARAMETER CVPixelBufferRef CV_NULLABLE * CV_NONNULL pixelBufferOut ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);


/*
    @function   CVPixelBufferPoolCreatePixelBufferWithAuxAttributes
    @abstract   Creates a new PixelBuffer object from the pool.
    @discussion This function creates a new CVPixelBuffer using the pixel buffer attributes specified during pool creation and the attributes specified in the auxAttributes parameter.
    @param      allocator The CFAllocatorRef to use for creating the pixel buffer.  May be NULL.
    @param      pixelBufferPool      The CVPixelBufferPool that should create the new CVPixelBuffer.
    @param      auxAttributes	Attributes describing this specific allocation request.  May be NULL.
    @param      pixelBufferOut   The newly created pixel buffer will be placed here
    @result     Returns kCVReturnSuccess on success
*/
CV_EXPORT CVReturn CVPixelBufferPoolCreatePixelBufferWithAuxAttributes(
    CFAllocatorRef CV_NULLABLE allocator,
    CVPixelBufferPoolRef CV_NONNULL pixelBufferPool,
    CFDictionaryRef CV_NULLABLE auxAttributes,
    CV_RETURNS_RETAINED_PARAMETER CVPixelBufferRef CV_NULLABLE * CV_NONNULL pixelBufferOut ) __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

// Key for the auxiliary attributes dictionary passed to CVPixelBufferPoolCreatePixelBufferWithAuxAttributes().

// When set, indicates that a new pixel buffer should not be allocated if
// the pool already has this many or more pixel buffers allocated.
// This does not prevent already-allocated buffers from being recycled.
// If this key causes CVPixelBufferPoolCreatePixelBufferWithAuxAttributes to fail,
// it will return kCVReturnWouldExceedAllocationThreshold.
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferPoolAllocationThresholdKey __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0); // CFNumberRef -- for use only in auxAttributes

// kCVPixelBufferPoolFreeBufferNotification is posted if a buffer becomes available after
// CVPixelBufferPoolCreatePixelBufferWithAuxAttributes has failed due to kCVPixelBufferPoolAllocationThresholdKey.
// This notification will not be posted by the pool if kCVPixelBufferPoolAllocationThresholdKey 
// has never been passed to CVPixelBufferPoolCreatePixelBufferWithAuxAttributes.
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferPoolFreeBufferNotification __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);


/*!
	@enum CVPixelBufferPoolFlush flags
	@discussion Flags to pass to CVPixelBufferPoolFlush()
	@constant kCVPixelBufferPoolFlushExcessBuffers
		This flag will cause CVPixelBufferPoolFlush to flush all unused buffers regardless of age.
*/

typedef CVOptionFlags CVPixelBufferPoolFlushFlags;
#if COREVIDEO_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CVPixelBufferPoolFlushFlags
#else
enum
#endif
{
	kCVPixelBufferPoolFlushExcessBuffers = 1,
};

/*!
	@function       CVPixelBufferPoolFlush
	@abstract       Frees as many buffers from the pool as possible.
	@discussion     By default, this function will free all aged out buffers.  Setting the
            kCVPixelBufferPoolFlushExcessBuffers flag will cause this call to free all unused
            buffers regardless of age.
	@param		pool    The CVPixelBufferPool to be flushed.
	@param		options Set to kCVPixelBufferPoolFlushExcessBuffers to free all unused buffers
            regardless of their age.
*/
CV_EXPORT void CVPixelBufferPoolFlush( CVPixelBufferPoolRef CV_NONNULL pool, CVPixelBufferPoolFlushFlags options );


#if defined(__cplusplus)
}
#endif

#endif
// ==========  CoreVideo.framework/Headers/CVPixelFormatDescription.h
/*
 *  CVPixelFormatDescription.h
 *  CoreVideo
 *
 *  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
 *
 */

#if !defined(__COREVIDEO_CVPIXELFORMATDESCRIPTION_H__)
#define __COREVIDEO_CVPIXELFORMATDESCRIPTION_H__

#include <TargetConditionals.h>
#include <Availability.h>
#include <AvailabilityMacros.h>

#include <CoreVideo/CoreVideo.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFArray.h>

#if defined(__cplusplus)
extern "C" {
#endif

/* This document is influenced by Ice Floe #19: http://developer.apple.com/quicktime/icefloe/dispatch019.html */

/* The canonical name for the format.  This should bethe same as the codec name you'd use in QT */
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatName __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/* QuickTime/QuickDraw Pixel Format Type constant (OSType) */
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatConstant __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/* This is the codec type constant, i.e. '2vuy' or k422YpCbCr8CodecType */
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatCodecType __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/* This is the equivalent Microsoft FourCC code for this pixel format */
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatFourCC __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/* kCFBooleanTrue indicates that the format contains alpha and some images may be considered transparent;
   kCFBooleanFalse indicates that there is no alpha and images are always opaque. */
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatContainsAlpha __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_3);
	
/* kCFBooleanTrue indicates that the format contains YCbCr data; */
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatContainsYCbCr __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
	
/* kCFBooleanTrue indicates that the format contains RGB data; */
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatContainsRGB __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatComponentRange __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_9_0);

CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatComponentRange_VideoRange __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_9_0);

CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatComponentRange_FullRange __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_9_0);

CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatComponentRange_WideRange __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_9_0);

/* All buffers have one or more image planes.  Each plane may contain a single or an interleaved set of components */   
/* For simplicity sake, pixel formats that are not planar may place the required format keys at the top
   level dictionary. */
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatPlanes __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/* The following keys describe the requirements/layout of a a single image plane. */

/* Used to assist with allocating memory for pixel formats that don't have an integer value for
   bytes per pixel */
/* Block width is essentially the width in pixels of the smallest "byte addressable" group of pixels */
/* This works in close conjunction with BitsPerBlock */
/* Examples:
   8-bit luminance only, BlockWidth would be 1, BitsPerBlock would be 8
   16-bit 1555 RGB, BlockWidth would be 1, BitsPerBlock would be 16
   32-bit 8888 ARGB, BlockWidth would be 1, BitsPerBlock would be 32
   2vuy (CbYCrY), BlockWidth would be 2, BitsPerBlock would be 32
   1-bit bitmap, BlockWidth would be 8, BitsPerBlock would be 8
   v210, BlockWidth would be 6, BitsPerBlock would be 128 */
/* Values assumed to 1 be one if not present */
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatBlockWidth __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatBlockHeight __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/* This value must be present.  For simple pixel formats this will be equivalent to the traditional 
   bitsPerPixel value. */
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatBitsPerBlock __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/* Used to state requirements on block multiples.  v210 would be '8' here for the horizontal case, 
   to match the standard v210 row alignment value of 48.
   These may be assumed as 1 if not present. */
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatBlockHorizontalAlignment __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatBlockVerticalAlignment __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/* CFData containing the bit pattern for a block of black pixels.  If absent, black is assumed to be all zeros.
   If present, this should be bitsPerPixel bits long -- if bitsPerPixel is less than a byte, repeat the bit pattern 
   for the full byte.  */
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatBlackBlock __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_4_0);

/* Subsampling information for this plane.  Assumed to be '1' if not present. */
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatHorizontalSubsampling __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatVerticalSubsampling __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/* If present, these two keys describe the OpenGL format and type enums you would use to describe this
   image plane to OpenGL */
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatOpenGLFormat __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatOpenGLType __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatOpenGLInternalFormat __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/* CGBitmapInfo value, if required */
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatCGBitmapInfo __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/* Pixel format compatibility flags */
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatQDCompatibility __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatCGBitmapContextCompatibility __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatCGImageCompatibility __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatOpenGLCompatibility __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatOpenGLESCompatibility __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
    
/* This callback routine implements code to handle the functionality of CVPixelBufferFillExtendedPixels.  
   For custom pixel formats where you will never need to use that call, this is not required. */
typedef Boolean (*CVFillExtendedPixelsCallBack)(CVPixelBufferRef CV_NONNULL pixelBuffer, void * CV_NULLABLE refCon);
typedef struct {
    CFIndex version;
    CVFillExtendedPixelsCallBack CV_NULLABLE fillCallBack;
    void * CV_NULLABLE refCon;
} CVFillExtendedPixelsCallBackData;

/* The value for this key is a CFData containing a CVFillExtendedPixelsCallBackData struct */
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatFillExtendedPixelsCallback __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/* Create a description of a pixel format from a provided OSType */
CV_EXPORT CFDictionaryRef CV_NULLABLE CVPixelFormatDescriptionCreateWithPixelFormatType(CFAllocatorRef CV_NULLABLE allocator, OSType pixelFormat) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/* Get a CFArray of CFNumbers containing all known pixel formats as OSTypes */
CV_EXPORT CFArrayRef CV_NULLABLE CVPixelFormatDescriptionArrayCreateWithAllPixelFormatTypes(CFAllocatorRef CV_NULLABLE allocator) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/* Register a new pixel format with CoreVideo */
CV_EXPORT void CVPixelFormatDescriptionRegisterDescriptionWithPixelFormatType(CFDictionaryRef CV_NONNULL description, OSType pixelFormat) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

#if COREVIDEO_SUPPORTS_DIRECT3D
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatDirect3DFormat;
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatDirect3DType;
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatDirect3DInternalFormat;
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelFormatDirect3DCompatibility;	
#endif

#if defined(__cplusplus)
}
#endif

#endif

// ==========  CoreVideo.framework/Headers/CVPixelBuffer.h
/*
 *  CVPixelBuffer.h
 *  CoreVideo
 *
 *  Copyright (c) 2004-2015 Apple Inc. All rights reserved.
 *
 */
 
  /*! @header CVPixelBuffer.h
	@copyright 2004-2015 Apple Inc. All rights reserved.
	@availability Mac OS X 10.4 or later, and iOS 4.0 or later
    @discussion CVPixelBuffers are CVImageBuffers that hold the pixels in main memory
		   
*/

#if !defined(__COREVIDEO_CVPIXELBUFFER_H__)
#define __COREVIDEO_CVPIXELBUFFER_H__ 1

#include <TargetConditionals.h>
#include <Availability.h>
#include <AvailabilityMacros.h>

#include <CoreVideo/CVImageBuffer.h>
#include <CoreFoundation/CFArray.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*
CoreVideo pixel format type constants.
CoreVideo does not provide support for all of these formats; this list just defines their names.
*/
#if COREVIDEO_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSType
#else
enum
#endif
{
  kCVPixelFormatType_1Monochrome    = 0x00000001, /* 1 bit indexed */
  kCVPixelFormatType_2Indexed       = 0x00000002, /* 2 bit indexed */
  kCVPixelFormatType_4Indexed       = 0x00000004, /* 4 bit indexed */
  kCVPixelFormatType_8Indexed       = 0x00000008, /* 8 bit indexed */
  kCVPixelFormatType_1IndexedGray_WhiteIsZero = 0x00000021, /* 1 bit indexed gray, white is zero */
  kCVPixelFormatType_2IndexedGray_WhiteIsZero = 0x00000022, /* 2 bit indexed gray, white is zero */
  kCVPixelFormatType_4IndexedGray_WhiteIsZero = 0x00000024, /* 4 bit indexed gray, white is zero */
  kCVPixelFormatType_8IndexedGray_WhiteIsZero = 0x00000028, /* 8 bit indexed gray, white is zero */
  kCVPixelFormatType_16BE555        = 0x00000010, /* 16 bit BE RGB 555 */
  kCVPixelFormatType_16LE555        = 'L555',     /* 16 bit LE RGB 555 */
  kCVPixelFormatType_16LE5551       = '5551',     /* 16 bit LE RGB 5551 */
  kCVPixelFormatType_16BE565        = 'B565',     /* 16 bit BE RGB 565 */
  kCVPixelFormatType_16LE565        = 'L565',     /* 16 bit LE RGB 565 */
  kCVPixelFormatType_24RGB          = 0x00000018, /* 24 bit RGB */
  kCVPixelFormatType_24BGR          = '24BG',     /* 24 bit BGR */
  kCVPixelFormatType_32ARGB         = 0x00000020, /* 32 bit ARGB */
  kCVPixelFormatType_32BGRA         = 'BGRA',     /* 32 bit BGRA */
  kCVPixelFormatType_32ABGR         = 'ABGR',     /* 32 bit ABGR */
  kCVPixelFormatType_32RGBA         = 'RGBA',     /* 32 bit RGBA */
  kCVPixelFormatType_64ARGB         = 'b64a',     /* 64 bit ARGB, 16-bit big-endian samples */
  kCVPixelFormatType_48RGB          = 'b48r',     /* 48 bit RGB, 16-bit big-endian samples */
  kCVPixelFormatType_32AlphaGray    = 'b32a',     /* 32 bit AlphaGray, 16-bit big-endian samples, black is zero */
  kCVPixelFormatType_16Gray         = 'b16g',     /* 16 bit Grayscale, 16-bit big-endian samples, black is zero */
  kCVPixelFormatType_30RGB          = 'R10k',     /* 30 bit RGB, 10-bit big-endian samples, 2 unused padding bits (at least significant end). */
  kCVPixelFormatType_422YpCbCr8     = '2vuy',     /* Component Y'CbCr 8-bit 4:2:2, ordered Cb Y'0 Cr Y'1 */
  kCVPixelFormatType_4444YpCbCrA8   = 'v408',     /* Component Y'CbCrA 8-bit 4:4:4:4, ordered Cb Y' Cr A */
  kCVPixelFormatType_4444YpCbCrA8R  = 'r408',     /* Component Y'CbCrA 8-bit 4:4:4:4, rendering format. full range alpha, zero biased YUV, ordered A Y' Cb Cr */
  kCVPixelFormatType_4444AYpCbCr8   = 'y408',     /* Component Y'CbCrA 8-bit 4:4:4:4, ordered A Y' Cb Cr, full range alpha, video range Y'CbCr. */
  kCVPixelFormatType_4444AYpCbCr16  = 'y416',     /* Component Y'CbCrA 16-bit 4:4:4:4, ordered A Y' Cb Cr, full range alpha, video range Y'CbCr, 16-bit little-endian samples. */
  kCVPixelFormatType_444YpCbCr8     = 'v308',     /* Component Y'CbCr 8-bit 4:4:4 */
  kCVPixelFormatType_422YpCbCr16    = 'v216',     /* Component Y'CbCr 10,12,14,16-bit 4:2:2 */
  kCVPixelFormatType_422YpCbCr10    = 'v210',     /* Component Y'CbCr 10-bit 4:2:2 */
  kCVPixelFormatType_444YpCbCr10    = 'v410',     /* Component Y'CbCr 10-bit 4:4:4 */
  kCVPixelFormatType_420YpCbCr8Planar = 'y420',   /* Planar Component Y'CbCr 8-bit 4:2:0.  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrPlanar struct */
  kCVPixelFormatType_420YpCbCr8PlanarFullRange    = 'f420',   /* Planar Component Y'CbCr 8-bit 4:2:0, full range.  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrPlanar struct */
  kCVPixelFormatType_422YpCbCr_4A_8BiPlanar = 'a2vy', /* First plane: Video-range Component Y'CbCr 8-bit 4:2:2, ordered Cb Y'0 Cr Y'1; second plane: alpha 8-bit 0-255 */
  kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange = '420v', /* Bi-Planar Component Y'CbCr 8-bit 4:2:0, video-range (luma=[16,235] chroma=[16,240]).  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrBiPlanar struct */
  kCVPixelFormatType_420YpCbCr8BiPlanarFullRange  = '420f', /* Bi-Planar Component Y'CbCr 8-bit 4:2:0, full-range (luma=[0,255] chroma=[1,255]).  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrBiPlanar struct */ 
  kCVPixelFormatType_422YpCbCr8_yuvs = 'yuvs',     /* Component Y'CbCr 8-bit 4:2:2, ordered Y'0 Cb Y'1 Cr */
  kCVPixelFormatType_422YpCbCr8FullRange = 'yuvf', /* Component Y'CbCr 8-bit 4:2:2, full range, ordered Y'0 Cb Y'1 Cr */
  kCVPixelFormatType_OneComponent8  = 'L008',     /* 8 bit one component, black is zero */
  kCVPixelFormatType_TwoComponent8  = '2C08',     /* 8 bit two component, black is zero */
  kCVPixelFormatType_OneComponent16Half  = 'L00h',     /* 16 bit one component IEEE half-precision float, 16-bit little-endian samples */
  kCVPixelFormatType_OneComponent32Float = 'L00f',     /* 32 bit one component IEEE float, 32-bit little-endian samples */
  kCVPixelFormatType_TwoComponent16Half  = '2C0h',     /* 16 bit two component IEEE half-precision float, 16-bit little-endian samples */
  kCVPixelFormatType_TwoComponent32Float = '2C0f',     /* 32 bit two component IEEE float, 32-bit little-endian samples */
  kCVPixelFormatType_64RGBAHalf          = 'RGhA',     /* 64 bit RGBA IEEE half-precision float, 16-bit little-endian samples */
  kCVPixelFormatType_128RGBAFloat        = 'RGfA',     /* 128 bit RGBA IEEE float, 32-bit little-endian samples */
};

	
/*!
	@enum Pixel Buffer Locking Flags
	@discussion Flags to pass to CVPixelBufferLockBaseAddress() / CVPixelBufferUnlockBaseAddress()
	@constant kCVPixelBufferLock_ReadOnly
		If you are not going to modify the data while you hold the lock, you should set this flag
		to avoid potentially invalidating any existing caches of the buffer contents.  This flag
		should be passed both to the lock and unlock functions.  Non-symmetrical usage of this
		flag will result in undefined behavior.
*/
typedef CVOptionFlags CVPixelBufferLockFlags;
#if COREVIDEO_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CVPixelBufferLockFlags
#else
enum
#endif
{
	kCVPixelBufferLock_ReadOnly = 0x00000001,
};

/*
Planar pixel buffers have the following descriptor at their base address.  
Clients should generally use CVPixelBufferGetBaseAddressOfPlane, 
CVPixelBufferGetBytesPerRowOfPlane, etc. instead of accessing it directly.
*/
struct CVPlanarComponentInfo {
  int32_t             offset;    /* offset from main base address to base address of this plane, big-endian */
  uint32_t            rowBytes;  /* bytes per row of this plane, big-endian */
};
typedef struct CVPlanarComponentInfo      CVPlanarComponentInfo;
struct CVPlanarPixelBufferInfo {
  CVPlanarComponentInfo  componentInfo[1];
};
typedef struct CVPlanarPixelBufferInfo         CVPlanarPixelBufferInfo;
struct CVPlanarPixelBufferInfo_YCbCrPlanar {
  CVPlanarComponentInfo  componentInfoY;
  CVPlanarComponentInfo  componentInfoCb;
  CVPlanarComponentInfo  componentInfoCr;
};
typedef struct CVPlanarPixelBufferInfo_YCbCrPlanar   CVPlanarPixelBufferInfo_YCbCrPlanar;
struct CVPlanarPixelBufferInfo_YCbCrBiPlanar {
  CVPlanarComponentInfo  componentInfoY;
  CVPlanarComponentInfo  componentInfoCbCr;
};
typedef struct CVPlanarPixelBufferInfo_YCbCrBiPlanar   CVPlanarPixelBufferInfo_YCbCrBiPlanar;

#pragma mark BufferAttributeKeys
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferPixelFormatTypeKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		    // A single CFNumber or a CFArray of CFNumbers (OSTypes)
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferMemoryAllocatorKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		    // CFAllocatorRef
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferWidthKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);			    // CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferHeightKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);			    // CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferExtendedPixelsLeftKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);	    // CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferExtendedPixelsTopKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		    // CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferExtendedPixelsRightKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);	    // CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferExtendedPixelsBottomKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);	    // CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferBytesPerRowAlignmentKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);	    // CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferCGBitmapContextCompatibilityKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);  // CFBoolean
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferCGImageCompatibilityKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);	    // CFBoolean
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferOpenGLCompatibilityKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);	    // CFBoolean
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferPlaneAlignmentKey __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_4_0);		    // CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferIOSurfacePropertiesKey __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_4_0);     // CFDictionary; presence requests buffer allocation via IOSurface
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferOpenGLESCompatibilityKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);	    // CFBoolean
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferMetalCompatibilityKey __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_8_0);	    // CFBoolean
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferOpenGLTextureCacheCompatibilityKey __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_NA);
CV_EXPORT const CFStringRef CV_NONNULL kCVPixelBufferOpenGLESTextureCacheCompatibilityKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_9_0);    

/*!
    @typedef	CVPixelBufferRef
    @abstract   Based on the image buffer type. The pixel buffer implements the memory storage for an image buffer.

*/
typedef CVImageBufferRef CVPixelBufferRef;

CV_EXPORT CFTypeID CVPixelBufferGetTypeID(void) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferRetain
    @abstract   Retains a CVPixelBuffer object
    @discussion Equivalent to CFRetain, but NULL safe
    @param      buffer A CVPixelBuffer object that you want to retain.
    @result     A CVPixelBuffer object that is the same as the passed in buffer.
*/
CV_EXPORT CVPixelBufferRef CV_NULLABLE CVPixelBufferRetain( CVPixelBufferRef CV_NULLABLE texture ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferRelease
    @abstract   Releases a CVPixelBuffer object
    @discussion Equivalent to CFRelease, but NULL safe
    @param      buffer A CVPixelBuffer object that you want to release.
*/
CV_EXPORT void CVPixelBufferRelease( CV_RELEASES_ARGUMENT CVPixelBufferRef CV_NULLABLE texture ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferCreateResolvedAttributesDictionary
    @abstract   Takes a CFArray of CFDictionary objects describing various pixel buffer attributes and tries to resolve them into a
                single dictionary.
    @discussion This is useful when you need to resolve multiple requirements between different potential clients of a buffer.
    @param      attributes CFArray of CFDictionaries containing kCVPixelBuffer key/value pairs.
    @param      resolvedDictionaryOut The resulting dictionary will be placed here.
    @result     Return value that may be useful in discovering why resolution failed.
*/
CV_EXPORT CVReturn CVPixelBufferCreateResolvedAttributesDictionary(
    CFAllocatorRef CV_NULLABLE allocator,
    CFArrayRef CV_NULLABLE attributes,
    CV_RETURNS_RETAINED_PARAMETER CFDictionaryRef CV_NULLABLE * CV_NONNULL resolvedDictionaryOut) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);


/*!
    @function   CVPixelBufferCreate
    @abstract   Call to create a single PixelBuffer for a given size and pixelFormatType.
    @discussion Creates a single PixelBuffer for a given size and pixelFormatType. It allocates the necessary memory based on the pixel dimensions, pixelFormatType and extended pixels described in the pixelBufferAttributes. Not all parameters of the pixelBufferAttributes will be used here.
    @param      width   Width of the PixelBuffer in pixels.
    @param      height  Height of the PixelBuffer in pixels.
    @param	pixelFormatType		Pixel format indentified by its respective OSType.
    @param	pixelBufferAttributes      A dictionary with additional attributes for a pixel buffer. This parameter is optional. See BufferAttributeKeys for more details.
    @param      pixelBufferOut          The new pixel buffer will be returned here
    @result	returns kCVReturnSuccess on success.
*/    
CV_EXPORT CVReturn CVPixelBufferCreate(
    CFAllocatorRef CV_NULLABLE allocator,
    size_t width,
    size_t height,
    OSType pixelFormatType,
    CFDictionaryRef CV_NULLABLE pixelBufferAttributes,
    CV_RETURNS_RETAINED_PARAMETER CVPixelBufferRef CV_NULLABLE * CV_NONNULL pixelBufferOut) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

typedef void (*CVPixelBufferReleaseBytesCallback)( void * CV_NULLABLE releaseRefCon, const void * CV_NULLABLE baseAddress );

/*!
    @function   CVPixelBufferCreateWithBytes
    @abstract   Call to create a single PixelBuffer for a given size and pixelFormatType based on a passed in piece of memory.
    @discussion Creates a single PixelBuffer for a given size and pixelFormatType. Not all parameters of the pixelBufferAttributes will be used here. It requires a release callback function that will be called, when the PixelBuffer gets destroyed so that the owner of the pixels can free the memory.
    @param      width   Width of the PixelBuffer in pixels
    @param      height  Height of the PixelBuffer in pixels
    @param      pixelFormatType		Pixel format indentified by its respective OSType.
    @param      baseAddress		Address of the memory storing the pixels.
    @param      bytesPerRow		Row bytes of the pixel storage memory.
    @param      releaseCallback         CVPixelBufferReleaseBytePointerCallback function that gets called when the PixelBuffer gets destroyed.
    @param      releaseRefCon           User data identifying the PixelBuffer for the release callback.
    @param      pixelBufferAttributes      A dictionary with additional attributes for a a pixel buffer. This parameter is optional. See PixelBufferAttributes for more details.
    @param      pixelBufferOut          The new pixel buffer will be returned here
    @result	returns kCVReturnSuccess on success.
*/
CV_EXPORT CVReturn CVPixelBufferCreateWithBytes(
    CFAllocatorRef CV_NULLABLE allocator,
    size_t width,
    size_t height,
    OSType pixelFormatType,
    void * CV_NONNULL baseAddress,
    size_t bytesPerRow,
    CVPixelBufferReleaseBytesCallback CV_NULLABLE releaseCallback,
    void * CV_NULLABLE releaseRefCon,
    CFDictionaryRef CV_NULLABLE pixelBufferAttributes,
    CV_RETURNS_RETAINED_PARAMETER CVPixelBufferRef CV_NULLABLE * CV_NONNULL pixelBufferOut) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

typedef void (*CVPixelBufferReleasePlanarBytesCallback)( void * CV_NULLABLE releaseRefCon, const void * CV_NULLABLE dataPtr, size_t dataSize, size_t numberOfPlanes, const void * CV_NULLABLE planeAddresses[] );

/*!
    @function   CVPixelBufferCreateWithPlanarBytes
    @abstract   Call to create a single PixelBuffer in planar format for a given size and pixelFormatType based on a passed in piece of memory.
    @discussion Creates a single PixelBuffer for a given size and pixelFormatType. Not all parameters of the pixelBufferAttributes will be used here. It requires a release callback function that will be called, when the PixelBuffer gets destroyed so that the owner of the pixels can free the memory.
    @param      width			Width of the PixelBuffer in pixels
    @param      height			Height of the PixelBuffer in pixels
    @param      pixelFormatType		Pixel format indentified by its respective OSType.
    @param	dataPtr			Pass a pointer to a plane descriptor block, or NULL.
    @param	dataSize		pass size if planes are contiguous, NULL if not.
    @param	numberOfPlanes		Number of planes.
    @param	planeBaseAddress	Array of base addresses for the planes.
    @param	planeWidth		Array of plane widths.
    @param	planeHeight		Array of plane heights.
    @param	planeBytesPerRow	Array of plane bytesPerRow values.
    @param	releaseCallback		CVPixelBufferReleaseBytePointerCallback function that gets called when the PixelBuffer gets destroyed.
    @param	releaseRefCon		User data identifying the PixelBuffer for the release callback.
    @param	pixelBufferAttributes      A dictionary with additional attributes for a a pixel buffer. This parameter is optional. See PixelBufferAttributes for more details.
    @param      pixelBufferOut          The new pixel buffer will be returned here
    @result	returns kCVReturnSuccess on success.
*/
CV_EXPORT CVReturn CVPixelBufferCreateWithPlanarBytes(
    CFAllocatorRef CV_NULLABLE allocator,
    size_t width,
    size_t height,
    OSType pixelFormatType,
    void * CV_NULLABLE dataPtr, // pass a pointer to a plane descriptor block, or NULL
    size_t dataSize, // pass size if planes are contiguous, NULL if not
    size_t numberOfPlanes,
    void * CV_NULLABLE planeBaseAddress[],
    size_t planeWidth[],
    size_t planeHeight[],
    size_t planeBytesPerRow[],
    CVPixelBufferReleasePlanarBytesCallback CV_NULLABLE releaseCallback,
    void * CV_NULLABLE releaseRefCon,
    CFDictionaryRef CV_NULLABLE pixelBufferAttributes,
    CV_RETURNS_RETAINED_PARAMETER CVPixelBufferRef CV_NULLABLE * CV_NONNULL pixelBufferOut) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);


/*!
	@function   CVPixelBufferLockBaseAddress
	@abstract   Description Locks the BaseAddress of the PixelBuffer to ensure that the memory is accessible.
	@discussion This API ensures that the CVPixelBuffer is accessible in system memory. This should only be called if the base address is going to be used and the pixel data will be accessed by the CPU.
	@param      pixelBuffer Target PixelBuffer.
	@param      lockFlags See CVPixelBufferLockFlags.
	@result     kCVReturnSuccess if the lock succeeded, or error code on failure
*/
CV_EXPORT CVReturn CVPixelBufferLockBaseAddress( CVPixelBufferRef CV_NONNULL pixelBuffer, CVPixelBufferLockFlags lockFlags ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
	@function   CVPixelBufferUnlockBaseAddress
	@abstract   Description Unlocks the BaseAddress of the PixelBuffer.
	@param      pixelBuffer Target PixelBuffer.
	@param      unlockFlags See CVPixelBufferLockFlags.
	@result     kCVReturnSuccess if the unlock succeeded, or error code on failure
*/
CV_EXPORT CVReturn CVPixelBufferUnlockBaseAddress( CVPixelBufferRef CV_NONNULL pixelBuffer, CVPixelBufferLockFlags unlockFlags ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetWidth
    @abstract   Returns the width of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     Width in pixels.
*/
CV_EXPORT size_t CVPixelBufferGetWidth( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetHeight
    @abstract   Returns the height of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     Height in pixels.
*/
CV_EXPORT size_t CVPixelBufferGetHeight( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetPixelFormatType
    @abstract   Returns the PixelFormatType of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     OSType identifying the pixel format by its type.
*/
CV_EXPORT OSType CVPixelBufferGetPixelFormatType( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetBaseAddress
    @abstract   Returns the base address of the PixelBuffer.
    @discussion Retrieving the base address for a PixelBuffer requires that the buffer base address be locked
                via a successful call to CVPixelBufferLockBaseAddress.
    @param      pixelBuffer Target PixelBuffer.
    @result     Base address of the pixels.
		For chunky buffers, this will return a pointer to the pixel at 0,0 in the buffer
		For planar buffers this will return a pointer to a PlanarComponentInfo struct (defined in QuickTime).
*/
CV_EXPORT void * CV_NULLABLE CVPixelBufferGetBaseAddress( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetBytesPerRow
    @abstract   Returns the rowBytes of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     Bytes per row of the image data.   For planar buffers this will return a rowBytes value such that bytesPerRow * height
                will cover the entire image including all planes.
*/
CV_EXPORT size_t CVPixelBufferGetBytesPerRow( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetDataSize
    @abstract   Returns the data size for contigous planes of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     Data size used in CVPixelBufferCreateWithPlanarBytes.
*/
CV_EXPORT size_t CVPixelBufferGetDataSize( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferIsPlanar
    @abstract   Returns if the PixelBuffer is planar.
    @param      pixelBuffer Target PixelBuffer.
    @result     True if the PixelBuffer was created using CVPixelBufferCreateWithPlanarBytes.
*/
CV_EXPORT Boolean CVPixelBufferIsPlanar( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetPlaneCount
    @abstract   Returns number of planes of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     Number of planes.  Returns 0 for non-planar CVPixelBufferRefs.
*/
CV_EXPORT size_t CVPixelBufferGetPlaneCount( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetWidthOfPlane
    @abstract   Returns the width of the plane at planeIndex in the PixelBuffer.
    @discussion On OSX 10.10 and earlier, or iOS 8 and earlier, calling this 
                function with a non-planar buffer will have undefined behavior.
    @param      pixelBuffer Target PixelBuffer.
    @param      planeIndex  Identifying the plane.
    @result     Width in pixels, or 0 for non-planar CVPixelBufferRefs.
*/
CV_EXPORT size_t CVPixelBufferGetWidthOfPlane( CVPixelBufferRef CV_NONNULL pixelBuffer, size_t planeIndex ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetHeightOfPlane
    @abstract   Returns the height of the plane at planeIndex in the PixelBuffer.
    @discussion On OSX 10.10 and earlier, or iOS 8 and earlier, calling this
                function with a non-planar buffer will have undefined behavior.
    @param      pixelBuffer Target PixelBuffer.
    @param      planeIndex  Identifying the plane.
    @result     Height in pixels, or 0 for non-planar CVPixelBufferRefs.
*/
CV_EXPORT size_t CVPixelBufferGetHeightOfPlane( CVPixelBufferRef CV_NONNULL pixelBuffer, size_t planeIndex ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetBaseAddressOfPlane
    @abstract   Returns the base address of the plane at planeIndex in the PixelBuffer.
    @discussion Retrieving the base address for a PixelBuffer requires that the buffer base address be locked
                via a successful call to CVPixelBufferLockBaseAddress. On OSX 10.10 and earlier, or iOS 8 and
                earlier, calling this function with a non-planar buffer will have undefined behavior.
    @param      pixelBuffer Target PixelBuffer.
    @param      planeIndex  Identifying the plane.
    @result     Base address of the plane, or NULL for non-planar CVPixelBufferRefs.
*/
CV_EXPORT void * CV_NULLABLE CVPixelBufferGetBaseAddressOfPlane( CVPixelBufferRef CV_NONNULL pixelBuffer, size_t planeIndex ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetBytesPerRowOfPlane
    @abstract   Returns the row bytes of the plane at planeIndex in the PixelBuffer.
    @discussion On OSX 10.10 and earlier, or iOS 8 and earlier, calling this
                function with a non-planar buffer will have undefined behavior.
    @param      pixelBuffer Target PixelBuffer.
    @param      planeIndex  Identifying the plane.
    @result     Row bytes of the plane, or NULL for non-planar CVPixelBufferRefs.
*/
CV_EXPORT size_t CVPixelBufferGetBytesPerRowOfPlane( CVPixelBufferRef CV_NONNULL pixelBuffer, size_t planeIndex ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferGetExtendedPixels
    @abstract   Returns the size of extended pixels of the PixelBuffer.
    @discussion On OSX 10.10 and earlier, or iOS 8 and earlier, calling this
                function with a non-planar buffer will have undefined behavior.
    @param      pixelBuffer Target PixelBuffer.
    @param      extraColumnsOnLeft Returns the pixel row padding to the left.  May be NULL.
    @param      extraRowsOnTop Returns the pixel row padding to the top.  May be NULL. 
    @param      extraColumnsOnRight Returns the pixel row padding to the right. May be NULL.
    @param      extraRowsOnBottom Returns the pixel row padding to the bottom. May be NULL.
*/
CV_EXPORT void CVPixelBufferGetExtendedPixels(
						  CVPixelBufferRef CV_NONNULL pixelBuffer,
						  size_t * CV_NULLABLE extraColumnsOnLeft,
						  size_t * CV_NULLABLE extraColumnsOnRight,
						  size_t * CV_NULLABLE extraRowsOnTop,
						  size_t * CV_NULLABLE extraRowsOnBottom ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVPixelBufferFillExtendedPixels
    @abstract   Fills the extended pixels of the PixelBuffer.   This function replicates edge pixels to fill the entire extended region of the image.
    @param      pixelBuffer Target PixelBuffer.
*/
CV_EXPORT CVReturn CVPixelBufferFillExtendedPixels( CVPixelBufferRef CV_NONNULL pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);


#if defined(__cplusplus)
}
#endif

#if (COREVIDEO_SUPPORTS_IOSURFACE && ! TARGET_OS_IPHONE && ! TARGET_OS_EMBEDDED)
#include <CoreVideo/CVPixelBufferIOSurface.h>
#endif

#endif
// ==========  CoreVideo.framework/Headers/CVOpenGLESTexture.h
/*
 *  CVOpenGLESTexture.h
 *  CoreVideo
 *
 *  Copyright (c) 2011-2015 Apple Inc. All rights reserved.
 *
 */
 
 /*! @header CVOpenGLESTexture.h
	@copyright 2011-2015 Apple Inc. All rights reserved.
	@availability iOS 5.0 or later
    @discussion A CoreVideo Texture derives from an ImageBuffer, and is used for supplying source image data to OpenGL.
    		   
*/

#if !defined(__COREVIDEO_CVOPENGLESTEXTURE_H__)
#define __COREVIDEO_CVOPENGLESTEXTURE_H__ 1

#include <CoreVideo/CVBase.h>
#include <CoreVideo/CVReturn.h>
#include <CoreVideo/CVImageBuffer.h>
#include <CoreFoundation/CoreFoundation.h>
#include <OpenGLES/gltypes.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

#pragma mark CVOpenGLESTexture

/*!
    @typedef	CVOpenGLESTextureRef
    @abstract   OpenGLES texture based image buffer

*/
typedef CVImageBufferRef CVOpenGLESTextureRef;

CV_EXPORT CFTypeID CVOpenGLESTextureGetTypeID(void) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*!
    @function   CVOpenGLESTextureGetTarget
    @abstract   Returns the texture target (eg. 2D vs. rect texture extension) of the CVOpenGLESTexture
    @param      image Target CVOpenGLESTexture
    @result     OpenGLES texture target
*/
CV_EXPORT GLenum CVOpenGLESTextureGetTarget( CVOpenGLESTextureRef CV_NONNULL image ) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*!
    @function   CVOpenGLESTextureGetName
    @abstract   Returns the texture target name of the CVOpenGLESTexture
    @param      image Target CVOpenGLESTexture
    @result     OpenGLES texture target name
*/
CV_EXPORT GLuint CVOpenGLESTextureGetName( CVOpenGLESTextureRef CV_NONNULL image ) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*!
    @function   CVOpenGLESTextureIsFlipped
    @abstract   Returns whether the image is flipped vertically or not.
    @param      image Target CVOpenGLESTexture
    @result     True if 0,0 in the texture is upper left, false if 0,0 is lower left
*/
CV_EXPORT Boolean CVOpenGLESTextureIsFlipped( CVOpenGLESTextureRef CV_NONNULL image ) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*!
    @function   CVOpenGLESTextureGetCleanTexCoords 
    @abstract   Returns convenient normalized texture coordinates for the part of the image that should be displayed
    @discussion This function automatically takes into account whether or not the texture is flipped.
    @param      image Target CVOpenGLESTexture
    @param      lowerLeft  - array of two GLfloats where the s and t normalized texture coordinates of the lower left corner of the image will be stored
    @param      lowerRight - array of two GLfloats where the s and t normalized texture coordinates of the lower right corner of the image will be stored
    @param      upperRight - array of two GLfloats where the s and t normalized texture coordinates of the upper right corner of the image will be stored
    @param      upperLeft  - array of two GLfloats where the s and t normalized texture coordinates of the upper right corner of the image will be stored
*/
CV_EXPORT void CVOpenGLESTextureGetCleanTexCoords( CVOpenGLESTextureRef CV_NONNULL image, 
                                                   GLfloat lowerLeft[2], 
                                                   GLfloat lowerRight[2], 
                                                   GLfloat upperRight[2],
                                                   GLfloat upperLeft[2] ) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

#if defined(__cplusplus)
}
#endif

#endif
// ==========  CoreVideo.framework/Headers/CoreVideo.h
/*
 *  CoreVideo.h
 *  CoreVideo
 *
 *  Copyright (c) 2004-2015 Apple Inc. All rights reserved.
 *
 */
/*!
    @header CoreVideo
	@copyright 2004-2014 Apple Inc. All rights reserved.
	@availability Mac OS X 10.4 or later, and iOS 4.0 or later
    @abstract   Umbrella header for the CoreVideo framework
    @discussion This header includes all necesssary headers for the CoreVideo API
*/

#include <TargetConditionals.h>
#include <Availability.h>
#include <AvailabilityMacros.h>

#include <CoreVideo/CVReturn.h>
#include <CoreVideo/CVBase.h>

#if COREVIDEO_SUPPORTS_DISPLAYLINK
#include <CoreVideo/CVHostTime.h>
#include <CoreVideo/CVDisplayLink.h>
#endif

#include <CoreVideo/CVBuffer.h>
#include <CoreVideo/CVPixelBuffer.h>
#include <CoreVideo/CVPixelBufferPool.h>

#if COREVIDEO_SUPPORTS_OPENGL
#include <CoreVideo/CVOpenGLBuffer.h>
#include <CoreVideo/CVOpenGLBufferPool.h>
#include <CoreVideo/CVOpenGLTexture.h>
#include <CoreVideo/CVOpenGLTextureCache.h>
#endif // COREVIDEO_SUPPORTS_OPENGL
#if COREVIDEO_SUPPORTS_OPENGLES
#include <CoreVideo/CVOpenGLESTexture.h>
#include <CoreVideo/CVOpenGLESTextureCache.h>
#endif // COREVIDEO_SUPPORTS_OPENGLES
#include <CoreVideo/CVPixelFormatDescription.h>

#if COREVIDEO_SUPPORTS_DIRECT3D
#include <CoreVideo/CVDirect3DBuffer.h>
#include <CoreVideo/CVDirect3DBufferPool.h>
#include <CoreVideo/CVDirect3DTexture.h>
#include <CoreVideo/CVDirect3DTextureCache.h>
#endif

#if COREVIDEO_SUPPORTS_METAL
#include <CoreVideo/CVMetalTexture.h>
#include <CoreVideo/CVMetalTextureCache.h>
#endif
// ==========  CoreVideo.framework/Headers/CVMetalTexture.h
/*
 *  CVMetalTexture.h
 *  CoreVideo
 *
 *  Copyright (c) 2011-2015 Apple Inc. All rights reserved.
 *
 */
 
 /*! @header CVMetalTexture.h
	@copyright 2011-2015 Apple Inc. All rights reserved.
	@availability iOS 8.0 or later. Mac OS X 10.11 or later.
    @discussion A CoreVideo Metal Texture derives from an ImageBuffer, and is used for supplying source image data to Metal.
    		   
*/

#if !defined(__COREVIDEO_CVMETALTEXTURE_H__)
#define __COREVIDEO_CVMETALTEXTURE_H__ 1

#include <CoreVideo/CVBase.h>
#include <CoreVideo/CVReturn.h>
#include <CoreVideo/CVImageBuffer.h>
#include <CoreFoundation/CoreFoundation.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif
    
/* CVMetalTextureRef is only available to Objective C code */
#if defined(__OBJC__) && COREVIDEO_SUPPORTS_METAL
@protocol MTLTexture;
    
#pragma mark CVMetalTexture

/*!
    @typedef	CVMetalTextureRef
    @abstract   Metal texture based image buffer

*/
typedef CVImageBufferRef CVMetalTextureRef;

CV_EXPORT CFTypeID CVMetalTextureGetTypeID(void) __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_8_0);

/*!
    @function   CVMetalTextureGetTexture
    @abstract   Returns the Meta MTLTexture object of the CVMetalTextureRef
    @param      image Target CVMetalTexture
    @result     Metal texture
*/
CV_EXPORT id <MTLTexture> CV_NULLABLE CVMetalTextureGetTexture( CVMetalTextureRef CV_NONNULL image ) __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_8_0);

/*!
    @function   CVMetalTextureIsFlipped
    @abstract   Returns whether the image is flipped vertically or not.
    @param      image Target CVMetalTexture
    @result     True if 0,0 in the texture is upper left, false if 0,0 is lower left
*/
CV_EXPORT Boolean CVMetalTextureIsFlipped( CVMetalTextureRef CV_NONNULL image ) __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_8_0);

/*!
    @function   CVMetalTextureGetCleanTexCoords 
    @abstract   Returns convenient normalized texture coordinates for the part of the image that should be displayed
    @discussion This function automatically takes into account whether or not the texture is flipped.
    @param      image Target CVMetalTexture
    @param      lowerLeft  - array of two floats where the s and t normalized texture coordinates of the lower left corner of the image will be stored
    @param      lowerRight - array of two floats where the s and t normalized texture coordinates of the lower right corner of the image will be stored
    @param      upperRight - array of two floats where the s and t normalized texture coordinates of the upper right corner of the image will be stored
    @param      upperLeft  - array of two floats where the s and t normalized texture coordinates of the upper right corner of the image will be stored
*/
CV_EXPORT void CVMetalTextureGetCleanTexCoords( CVMetalTextureRef CV_NONNULL image,
                                                   float lowerLeft[2],
                                                   float lowerRight[2],
                                                   float upperRight[2],
                                                   float upperLeft[2] ) __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_8_0);
    
#endif
    
#if defined(__cplusplus)
}
#endif

#endif
// ==========  CoreVideo.framework/Headers/CVReturn.h
/*
 *  CVReturn.h
 *  CoreVideo
 *
 *  Copyright (c) 2004-2014 Apple Inc. All rights reserved.
 *
 */
 
 /*! @header CVReturn.h
	@copyright 2004-2014 Apple Inc. All rights reserved.
	@availability Mac OS X 10.4 or later, and iOS 4.0 or later
    @discussion Here you can find all the CoreVideo specific error codes. 
		   
*/

#if !defined(__COREVIDEO_CVRETURN_H__)
#define __COREVIDEO_CVRETURN_H__ 1

#include <TargetConditionals.h>

#include <CoreVideo/CVBase.h>

#if defined(__cplusplus)
extern "C" {
#endif
/*!
    @enum	CVReturn
    @abstract   CoreVideo specific error codes

    @constant   kCVReturnSuccess Function executed successfully without errors.
    @constant   kCVReturnFirst Placeholder to mark the beginning of the range of CVReturn codes.
    @constant   kCVReturnLast Placeholder to mark the end of the range of CVReturn codes.
 
    @constant   kCVReturnInvalidArgument At least one of the arguments passed in is not valid. Either out of range or the wrong type.
    @constant   kCVReturnAllocationFailed The allocation for a buffer or buffer pool failed. Most likely because of lack of resources.

    @constant   kCVReturnInvalidDisplay A CVDisplayLink cannot be created for the given DisplayRef.
    @constant   kCVReturnDisplayLinkAlreadyRunning The CVDisplayLink is already started and running.
    @constant   kCVReturnDisplayLinkNotRunning The CVDisplayLink has not been started.
    @constant   kCVReturnDisplayLinkCallbacksNotSet The output callback is not set.

    @constant   kCVReturnInvalidPixelFormat The requested pixelformat is not supported for the CVBuffer type.
    @constant   kCVReturnInvalidSize The requested size (most likely too big) is not supported for the CVBuffer type.
    @constant   kCVReturnInvalidPixelBufferAttributes A CVBuffer cannot be created with the given attributes.
    @constant   kCVReturnPixelBufferNotOpenGLCompatible The Buffer cannot be used with OpenGL as either its size, pixelformat or attributes are not supported by OpenGL.
    @constant   kCVReturnPixelBufferNotMetalCompatible The Buffer cannot be used with Metal as either its size, pixelformat or attributes are not supported by Metal.
 
    @constant   kCVReturnWouldExceedAllocationThreshold The allocation request failed because it would have exceeded a specified allocation threshold (see kCVPixelBufferPoolAllocationThresholdKey).
    @constant   kCVReturnPoolAllocationFailed The allocation for the buffer pool failed. Most likely because of lack of resources. Check if your parameters are in range.
    @constant   kCVReturnInvalidPoolAttributes A CVBufferPool cannot be created with the given attributes.
*/

typedef int32_t CVReturn;
#if COREVIDEO_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CVReturn
#else
enum _CVReturn
#endif
{
    kCVReturnSuccess                         = 0,
    
    kCVReturnFirst                           = -6660,
    
    kCVReturnError                           = kCVReturnFirst,
    kCVReturnInvalidArgument                 = -6661,
    kCVReturnAllocationFailed                = -6662,
	kCVReturnUnsupported                     = -6663,
    
    // DisplayLink related errors
    kCVReturnInvalidDisplay                  = -6670,
    kCVReturnDisplayLinkAlreadyRunning       = -6671,
    kCVReturnDisplayLinkNotRunning           = -6672,
    kCVReturnDisplayLinkCallbacksNotSet      = -6673,
    
    // Buffer related errors
    kCVReturnInvalidPixelFormat              = -6680,
    kCVReturnInvalidSize                     = -6681,
    kCVReturnInvalidPixelBufferAttributes    = -6682,
    kCVReturnPixelBufferNotOpenGLCompatible  = -6683,
    kCVReturnPixelBufferNotMetalCompatible   = -6684,
    
    // Buffer Pool related errors
    kCVReturnWouldExceedAllocationThreshold  = -6689,
    kCVReturnPoolAllocationFailed            = -6690,
    kCVReturnInvalidPoolAttributes           = -6691,
	
    kCVReturnLast                            = -6699
    
};

#if defined(__cplusplus)
}
#endif

#endif
// ==========  CoreVideo.framework/Headers/CVHostTime.h
/*
 *  CVHostTime.h
 *  CoreVideo
 *
 *  Copyright (c) 2004-2014 Apple Inc. All rights reserved.
 *
 */
 
 /*! @header CVHostTime.h
	@copyright 2004-2014 Apple Inc. All rights reserved.
	@availability Mac OS X 10.4 or later, and iOS 4.0 or later
    @discussion Utility functions for retrieving and working with the host time.
*/

#if !defined(__COREVIDEO_CVHOSTTIME_H__)
#define __COREVIDEO_CVHOSTTIME_H__ 1

#include <TargetConditionals.h>
#include <Availability.h>
#include <AvailabilityMacros.h>

#include <CoreVideo/CVBase.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
    @function   CVGetCurrentHostTime
    @abstract   Retrieve the current value of the host time base.
    @discussion On Mac OS X, the host time base for CoreVideo and CoreAudio are identical, and the values returned from either API
                may be used interchangeably.
    @result     The current host time.
*/
CV_EXPORT uint64_t CVGetCurrentHostTime() __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVGetHostClockFrequency
    @abstract   Retrieve the frequency of the host time base.
    @discussion On Mac OS X, the host time base for CoreVideo and CoreAudio are identical, and the values returned from either API
                may be used interchangeably.
    @result     The current host frequency.
*/
CV_EXPORT double   CVGetHostClockFrequency() __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVGetHostClockMinimumTimeDelta
    @abstract   Retrieve the smallest possible increment in the host time base.
    @result     The smallest valid increment in the host time base.
*/
CV_EXPORT uint32_t CVGetHostClockMinimumTimeDelta() __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

#if defined(__cplusplus)
}
#endif

#endif
// ==========  CoreVideo.framework/Headers/CVMetalTextureCache.h
/*
 *  CVMetalTextureCache.h
 *  CoreVideo
 *
 *  Copyright 2011-2015 Apple Inc. All rights reserved.
 *
 */

/*! @header CVMetalTextureCache.h
 @copyright 2011-2015 Apple Inc. All rights reserved.
 @availability iOS 8.0 or later. Mac OS X 10.11 or later.
 @discussion A CoreVideo Metal TextureCache is used to cache and manage CVMetalTextures.
 
 */

#if !defined(__COREVIDEO__CVMETALTEXTURECACHE_H__)
#define __COREVIDEO__CVMETALTEXTURECACHE_H__ 1

#include <CoreVideo/CVBase.h>
#include <CoreVideo/CVReturn.h>
#include <CoreVideo/CVBuffer.h>
#include <CoreVideo/CVMetalTexture.h>

#if defined(__cplusplus)
extern "C" {
#endif

//
// cacheAttributes
//
// By default, textures will age out after one second.  Setting a maximum
// texture age of zero will disable the age-out mechanism completely.
// CVMetalTextureCacheFlush() can be used to force eviction in either case.

CV_EXPORT const CFStringRef CV_NONNULL kCVMetalTextureCacheMaximumTextureAgeKey __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_8_0);

//
// textureAttributes - reserved for future use
    
/* CVMetalTextureCacheRef is only available to Objective C code */
#if defined(__OBJC__) && COREVIDEO_SUPPORTS_METAL
#import <Metal/MTLPixelFormat.h>

@protocol MTLDevice;
    
/*!
    @typedef	CVMetalTextureCacheRef
    @abstract   CoreVideo Metal Texture Cache

*/
typedef struct CV_BRIDGED_TYPE(id) __CVMetalTextureCache *CVMetalTextureCacheRef;


CV_EXPORT CFTypeID CVMetalTextureCacheGetTypeID(void) __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_8_0);

/*!
    @function   CVMetalTextureCacheCreate
    @abstract   Creates a new Texture Cache.
    @param      allocator The CFAllocatorRef to use for allocating the cache.  May be NULL.
    @param      cacheAttributes A CFDictionaryRef containing the attributes of the cache itself.   May be NULL.
    @param      metalDevice The Metal device for which the texture objects will be created.
    @param      textureAttributes A CFDictionaryRef containing the attributes to be used for creating the CVMetalTexture objects.  May be NULL.
    @param      cacheOut   The newly created texture cache will be placed here
    @result     Returns kCVReturnSuccess on success
*/
CV_EXPORT CVReturn CVMetalTextureCacheCreate(
					CFAllocatorRef CV_NULLABLE allocator,
					CFDictionaryRef CV_NULLABLE cacheAttributes,
					id <MTLDevice> CV_NONNULL metalDevice,
					CFDictionaryRef CV_NULLABLE textureAttributes,
					CVMetalTextureCacheRef CV_NULLABLE * CV_NONNULL cacheOut ) __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_8_0);

/*!
    @function   CVMetalTextureCacheCreateTextureFromImage
    @abstract   Creates a CVMetalTexture object from an existing CVImageBuffer
    @param      allocator The CFAllocatorRef to use for allocating the CVMetalTexture object.  May be NULL.
    @param      textureCache The texture cache object that will manage the texture.
    @param      sourceImage The CVImageBuffer that you want to create a CVMetalTexture from.
    @param      textureAttributes A CFDictionaryRef containing attributes to be used for creating the CVMetalTexture objects.  May be NULL.
    @param      pixelFormat Specifies the Metal pixel format.
    @param      width Specifies the width of the texture image.
    @param      height Specifies the height of the texture image.
    @param      planeIndex Specifies the plane of the CVImageBuffer to map bind.  Ignored for non-planar CVImageBuffers.
    @param      textureOut The newly created texture object will be placed here.
    @result     Returns kCVReturnSuccess on success
    @discussion Creates or returns a cached CVMetalTexture texture object mapped to the CVImageBuffer and
                associated params.  This creates a live binding between the CVImageBuffer and underlying
                CVMetalTexture texture object.
 
                Note that CoreVideo does not explicitly declare any pixel format types to be Metal compatible.  The assumption
                is that if the CVPixelBufferMetalCompatibilityKey has been specified, all buffers will be Metal compatible
                (IOSurface backed), and thus it is the developer's responsibility to choose an appropriate Metal pixel format
                for the CVPixelBuffers.
 
                Here are some example mappings:

                Mapping a BGRA buffer:
                CVMetalTextureCacheCreateTextureFromImage(kCFAllocatorDefault, textureCache, pixelBuffer, NULL, MTLPixelFormatBGRA8Unorm, width, height, 0, &outTexture);

                Mapping the luma plane of a 420v buffer:
                CVMetalTextureCacheCreateTextureFromImage(kCFAllocatorDefault, textureCache, pixelBuffer, NULL, MTLPixelFormatR8Unorm, width, height, 0, &outTexture);

                Mapping the chroma plane of a 420v buffer as a source texture:
                CVMetalTextureCacheCreateTextureFromImage(kCFAllocatorDefault, textureCache, pixelBuffer, NULL, MTLPixelFormatRG8Unorm width/2, height/2, 1, &outTexture);

                Mapping a yuvs buffer as a source texture (note: yuvs/f and 2vuy are unpacked and resampled -- not colorspace converted)
                CVMetalTextureCacheCreateTextureFromImage(kCFAllocatorDefault, textureCache, pixelBuffer, NULL, MTLPixelFormatGBGR422, width, height, 1, &outTexture);
*/
CV_EXPORT CVReturn CVMetalTextureCacheCreateTextureFromImage(
									   CFAllocatorRef CV_NULLABLE allocator,
									   CVMetalTextureCacheRef CV_NONNULL textureCache,
									   CVImageBufferRef CV_NONNULL sourceImage,
									   CFDictionaryRef CV_NULLABLE textureAttributes,
								       MTLPixelFormat pixelFormat,
								       size_t width,
								       size_t height,
								       size_t planeIndex,
									   CVMetalTextureRef CV_NULLABLE * CV_NONNULL textureOut ) __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_8_0);

/*!
    @function   CVMetalTextureCacheFlush
    @abstract   Performs internal housekeeping/recycling operations
    @discussion This call must be made periodically to give the texture cache a chance to do internal housekeeping operations.
    @param      textureCache The texture cache object to flush
    @param      options Currently unused, set to 0.
*/
CV_EXPORT void CVMetalTextureCacheFlush(CVMetalTextureCacheRef CV_NONNULL textureCache, CVOptionFlags options) __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_8_0);
    
#endif
    
#if defined(__cplusplus)
}
#endif

#endif
