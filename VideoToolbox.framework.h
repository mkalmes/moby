// ==========  VideoToolbox.framework/Headers/VTCompressionSession.h
/*
	File:  VTCompressionSession.h
	
	Framework:  VideoToolbox
	
	Copyright 2006-2013 Apple Inc. All rights reserved.
	
	Video Toolbox client API for compressing video frames.
	
	Compression sessions convert uncompressed frames in CVImageBuffers 
	into compressed video frames in CMSampleBuffers.
*/

#ifndef VTCOMPRESSIONSESSION_H
#define VTCOMPRESSIONSESSION_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>

#include <CoreFoundation/CoreFoundation.h>
#include <CoreVideo/CoreVideo.h>
#include <CoreMedia/CMSampleBuffer.h>
#include <CoreMedia/CMFormatDescription.h>
#include <CoreMedia/CMTime.h>
#include <CoreMedia/CMTimeRange.h>

#include <VideoToolbox/VTSession.h>
#include <VideoToolbox/VTCompressionProperties.h>

#include <VideoToolbox/VTErrors.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)
	
CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@typedef	VTCompressionSessionRef
	@abstract	A reference to a Video Toolbox Compression Session.
	@discussion
		A compression session supports the compression of a sequence of video frames.
		The session reference is a reference-counted CF object.
		To create a compression session, call VTCompressionSessionCreate; 
		then you can optionally configure the session using VTSessionSetProperty;
		then to encode frames, call VTCompressionSessionEncodeFrame.
		To force completion of some or all pending frames, call VTCompressionSessionCompleteFrames.
		When you are done with the session, you should call VTCompressionSessionInvalidate
		to tear it down and CFRelease to release your object reference.
 */

typedef struct CM_BRIDGED_TYPE(id) OpaqueVTCompressionSession*  VTCompressionSessionRef;

/*!
	@typedef	VTCompressionOutputCallback
    @abstract   Prototype for callback invoked when frame compression is complete.
    @discussion 
		When you create a compression session, you pass in a callback function to be called 
		for compressed frames.  This function will be called in decode order (which is not
		necessarily the same as display order).
	@param	outputCallbackRefCon
		The callback's reference value.
	@param	sourceFrameRefCon
		The frame's reference value, copied from the sourceFrameRefCon argument to 
		VTCompressionSessionEncodeFrame.
	@param	status
		noErr if compression was successful; an error code if compression was not successful.
	@param	infoFlags
		Contains information about the encode operation.
		The kVTEncodeInfo_Asynchronous bit may be set if the encode ran asynchronously.
		The kVTEncodeInfo_FrameDropped bit may be set if the frame was dropped.
	@param	sampleBuffer
		Contains the compressed frame, if compression was successful and the frame was not dropped; 
		otherwise, NULL.
*/

typedef void (*VTCompressionOutputCallback)(
		void * CM_NULLABLE outputCallbackRefCon,
		void * CM_NULLABLE sourceFrameRefCon, 
		OSStatus status, 
		VTEncodeInfoFlags infoFlags,
		CM_NULLABLE CMSampleBufferRef sampleBuffer );
	
CM_ASSUME_NONNULL_BEGIN
		
/*!
	@constant	kVTVideoEncoderSpecification_EncoderID
	@abstract
		Specifies a particular video encoder by its ID string.
	@discussion
		To specify a particular video encoder when creating a compression session, pass an 
		encoderSpecification CFDictionary containing this key and the EncoderID as its value.
		The EncoderID CFString may be obtained from the kVTVideoEncoderList_EncoderID entry in
		the array returned by VTCopyVideoEncoderList.
*/
VT_EXPORT const CFStringRef kVTVideoEncoderSpecification_EncoderID __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_8_0); // CFString
	
CM_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED
	
/*!
	@function	VTCompressionSessionCreate
	@abstract	Creates a session for compressing video frames.
    @discussion 
		Compressed frames will be emitted through calls to outputCallback.
	@param	allocator
		An allocator for the session.  Pass NULL to use the default allocator.
	@param	width
		The width of frames, in pixels.  
		If the video encoder cannot support the provided width and height it may change them.
	@param	height
		The height of frames in pixels.
	@param	cType
		The codec type.
	@param	encoderSpecification
		Specifies a particular video encoder that must be used.  
		Pass NULL to let the video toolbox choose a encoder.
	@param	sourceImageBufferAttributes
		Required attributes for source pixel buffers, used when creating a pixel buffer pool 
		for source frames.  If you do not want the Video Toolbox to create one for you, pass NULL.
		(Using pixel buffers not allocated by the Video Toolbox may increase the chance that
		it will be necessary to copy image data.)
	@param	compressedDataAllocator
		An allocator for the compressed data.  Pass NULL to use the default allocator.
	@param	outputCallback
		The callback to be called with compressed frames.
		This function may be called asynchronously, on a different thread from the one that calls VTCompressionSessionEncodeFrame.
		Pass NULL if and only if you will be calling VTCompressionSessionEncodeFrameWithOutputHandler for encoding frames.
	@param	outputCallbackRefCon
		Client-defined reference value for the output callback.
	@param	compressionSessionOut
		Points to a variable to receive the new compression session.
	
*/
VT_EXPORT OSStatus 
VTCompressionSessionCreate(
	CM_NULLABLE CFAllocatorRef							allocator,
	int32_t												width,
	int32_t												height,
	CMVideoCodecType									codecType,
	CM_NULLABLE CFDictionaryRef							encoderSpecification,
	CM_NULLABLE CFDictionaryRef							sourceImageBufferAttributes,
	CM_NULLABLE CFAllocatorRef							compressedDataAllocator,
	CM_NULLABLE VTCompressionOutputCallback				outputCallback,
	void * CM_NULLABLE									outputCallbackRefCon,
	CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE VTCompressionSessionRef * CM_NONNULL compressionSessionOut) __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_8_0);

CF_IMPLICIT_BRIDGING_ENABLED
	
/*!
	@function	VTCompressionSessionInvalidate
	@abstract	Tears down a compression session.
    @discussion 
    	When you are done with a compression session you created, call VTCompressionSessionInvalidate 
    	to tear it down and then CFRelease to release your object reference.
    	When a compression session's retain count reaches zero, it is automatically invalidated, but 
    	since sessions may be retained by multiple parties, it can be hard to predict when this will happen.
    	Calling VTCompressionSessionInvalidate ensures a deterministic, orderly teardown.
*/
VT_EXPORT void 
VTCompressionSessionInvalidate( CM_NONNULL VTCompressionSessionRef session ) __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_8_0);

/*!
	@function VTCompressionSessionGetTypeID
	@abstract Returns the CFTypeID for compression sessions.  
*/
VT_EXPORT CFTypeID 
VTCompressionSessionGetTypeID(void) __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_8_0);

/*!
	@function	VTCompressionSessionGetPixelBufferPool
	@abstract	Returns a pool that can provide ideal source pixel buffers for a compression session.
	@discussion
		The compression session creates this pixel buffer pool based on
		the compressor's pixel buffer attributes and any pixel buffer
		attributes passed in to VTCompressionSessionCreate.  If the
		source pixel buffer attributes and the compressor pixel buffer
		attributes cannot be reconciled, the pool is based on the source
		pixel buffer attributes and the Video Toolbox converts each CVImageBuffer
		internally.
		<BR>
		While clients can call VTCompressionSessionGetPixelBufferPool once
		and retain the resulting pool, the call is cheap enough that it's OK 
		to call it once per frame.  If a change of session properties causes 
		the compressor's pixel buffer attributes to change, it's possible that
		VTCompressionSessionGetPixelBufferPool might return a different pool.
*/
VT_EXPORT CM_NULLABLE CVPixelBufferPoolRef
VTCompressionSessionGetPixelBufferPool(
	CM_NONNULL VTCompressionSessionRef		session ) __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_8_0);

/*!
	@function	VTCompressionSessionPrepareToEncodeFrames
	@abstract
		You can optionally call this function to provide the encoder with an opportunity to perform
		any necessary resource allocation before it begins encoding frames.
	@discussion
		This optional call can be used to provide the encoder an opportunity to allocate
		any resources necessary before it begins encoding frames.  If this isn't called, any
		necessary resources will be allocated on the first VTCompressionSessionEncodeFrame call.
		Extra calls to this function will have no effect.
	@param	session
		The compression session.
*/
VT_EXPORT OSStatus
VTCompressionSessionPrepareToEncodeFrames( CM_NONNULL VTCompressionSessionRef session ) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_8_0);
	
/*!
	@function	VTCompressionSessionEncodeFrame
	@abstract
		Call this function to present frames to the compression session.
		Encoded frames may or may not be output before the function returns.
	@discussion
		The client should not modify the pixel data after making this call.
		The session and/or encoder will retain the image buffer as long as necessary. 
	@param	session
		The compression session.
	@param	imageBuffer
		A CVImageBuffer containing a video frame to be compressed.  
		Must have a nonzero reference count.
	@param	presentationTimeStamp
		The presentation timestamp for this frame, to be attached to the sample buffer.
		Each presentation timestamp passed to a session must be greater than the previous one.
	@param	duration
		The presentation duration for this frame, to be attached to the sample buffer.  
		If you do not have duration information, pass kCMTimeInvalid.
	@param	frameProperties
		Contains key/value pairs specifying additional properties for encoding this frame.
		Note that some session properties may also be changed between frames.
		Such changes have effect on subsequently encoded frames.
	@param	sourceFrameRefCon
		Your reference value for the frame, which will be passed to the output callback function.
	@param	infoFlagsOut
		Points to a VTEncodeInfoFlags to receive information about the encode operation.
		The kVTEncodeInfo_Asynchronous bit may be set if the encode is (or was) running
		asynchronously.
		The kVTEncodeInfo_FrameDropped bit may be set if the frame was dropped (synchronously).
		Pass NULL if you do not want to receive this information.
*/
VT_EXPORT OSStatus
VTCompressionSessionEncodeFrame(
	CM_NONNULL VTCompressionSessionRef	session,
	CM_NONNULL CVImageBufferRef			imageBuffer,
	CMTime								presentationTimeStamp,
	CMTime								duration, // may be kCMTimeInvalid
	CM_NULLABLE CFDictionaryRef			frameProperties,
	void * CM_NULLABLE					sourceFrameRefCon,
	VTEncodeInfoFlags * CM_NULLABLE		infoFlagsOut ) __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_8_0);
	
#if __BLOCKS__
/*!
	@typedef	VTCompressionOutputHandler
	@abstract   Prototype for block invoked when frame compression is complete.
	@discussion
		When you encode a frame, you pass in a callback block to be called
		for that compressed frame.  This block will be called in decode order (which is not
		necessarily the same as display order).
	@param	status
		noErr if compression was successful; an error code if compression was not successful.
	@param	infoFlags
		Contains information about the encode operation.
		The kVTEncodeInfo_Asynchronous bit may be set if the encode ran asynchronously.
		The kVTEncodeInfo_FrameDropped bit may be set if the frame was dropped.
	@param	sampleBuffer
		Contains the compressed frame, if compression was successful and the frame was not dropped;
		otherwise, NULL.
 */
typedef void (^VTCompressionOutputHandler)(
		OSStatus status,
		VTEncodeInfoFlags infoFlags,
		CM_NULLABLE CMSampleBufferRef sampleBuffer );
	
/*!
	@function	VTCompressionSessionEncodeFrameWithOutputHandler
	@abstract
		Call this function to present frames to the compression session.
		Encoded frames may or may not be output before the function returns.
	@discussion
		The client should not modify the pixel data after making this call.
		The session and/or encoder will retain the image buffer as long as necessary.
		Cannot be called with a session created with a VTCompressionOutputCallback/
	@param	session
		The compression session.
	@param	imageBuffer
		A CVImageBuffer containing a video frame to be compressed.
		Must have a nonzero reference count.
	@param	presentationTimeStamp
		The presentation timestamp for this frame, to be attached to the sample buffer.
		Each presentation timestamp passed to a session must be greater than the previous one.
	@param	duration
		The presentation duration for this frame, to be attached to the sample buffer.
		If you do not have duration information, pass kCMTimeInvalid.
	@param	frameProperties
		Contains key/value pairs specifying additional properties for encoding this frame.
		Note that some session properties may also be changed between frames.
		Such changes have effect on subsequently encoded frames.
	@param	infoFlagsOut
		Points to a VTEncodeInfoFlags to receive information about the encode operation.
		The kVTEncodeInfo_Asynchronous bit may be set if the encode is (or was) running
		asynchronously.
		The kVTEncodeInfo_FrameDropped bit may be set if the frame was dropped (synchronously).
		Pass NULL if you do not want to receive this information.
	@param	outputHandler
		The block to be called when encoding the frame is completed.
		This block may be called asynchronously, on a different thread from the one that calls VTCompressionSessionEncodeFrameWithOutputHandler.
 */
VT_EXPORT OSStatus
VTCompressionSessionEncodeFrameWithOutputHandler(
		CM_NONNULL VTCompressionSessionRef		session,
		CM_NONNULL CVImageBufferRef				imageBuffer,
		CMTime									presentationTimeStamp,
		CMTime									duration, // may be kCMTimeInvalid
		CM_NULLABLE CFDictionaryRef				frameProperties, // may be NULL
		VTEncodeInfoFlags * CM_NULLABLE			infoFlagsOut,
		CM_NONNULL VTCompressionOutputHandler	outputHandler ) __OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);
#endif // __BLOCKS__

/*!
	@function VTCompressionSessionCompleteFrames
	@abstract Forces the compression session to complete encoding frames.
	@discussion
		If completeUntilPresentationTimeStamp is numeric, frames with presentation timestamps
		up to and including this timestamp will be emitted before the function returns.
		If completeUntilPresentationTimeStamp is non-numeric, all pending frames
		will be emitted before the function returns.
*/
VT_EXPORT OSStatus
VTCompressionSessionCompleteFrames(
	CM_NONNULL VTCompressionSessionRef	session,
	CMTime								completeUntilPresentationTimeStamp) __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_8_0); // complete all frames if non-numeric
	
#pragma mark Multi-pass
	
/*
	When multi-pass encoding has been enabled by setting kVTCompressionPropertyKey_MultiPassStorage, you must call VTCompressionSessionBeginPass before each pass in which you call VTCompressionSessionEncodeFrame for source frames; you must call VTCompressionSessionEndPass to end each pass; and in each pass you must pass an identical sequence of source frames, frame properties and timestamps (except that source frames outside a pass' time ranges should be skipped).  See kVTCompressionPropertyKey_MultiPassStorage for additional rules and guidance.
*/
	
	
typedef CF_OPTIONS(uint32_t, VTCompressionSessionOptionFlags) {
	kVTCompressionSessionBeginFinalPass = 1<<0
};

/*!
	@function	VTCompressionSessionBeginPass
	@abstract	Call to announce the start of a specific compression pass.
	@discussion
		During multi-pass encoding, this function must be called before VTCompressionSessionEncodeFrame.
		It is an error to call this function when multi-pass encoding has not been enabled by setting kVTCompressionPropertyKey_MultiPassStorage.
	@param	beginPassFlags
		Pass kVTCompressionSessionBeginFinalPass to inform the encoder that the pass must be the final pass.
*/
VT_EXPORT OSStatus
VTCompressionSessionBeginPass(
	CM_NONNULL VTCompressionSessionRef	session,
	VTCompressionSessionOptionFlags		beginPassFlags,
	uint32_t * CM_NULLABLE				reserved) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
	
/*!
	@function	VTCompressionSessionEndPass
	@abstract	Call to announce the end of a pass.
	@discussion
		VTCompressionSessionEndPass can take a long time, since the video encoder may perform significant processing between passes.
		VTCompressionSessionEndPass will indicate via the furtherPassesRequestedOut argument whether the video encoder would like to perform another pass.  There is no particular bound on the number of passes the video encoder may request, but the client is free to disregard this request and use the last-emitted set of frames.
		It is an error to call this function when multi-pass encoding has not been enabled by setting kVTCompressionPropertyKey_MultiPassStorage.
	@param furtherPassesRequestedOut
		Points to a Boolean that will be set to true if the video encoder would like to perform another pass, false otherwise.
		You may pass NULL to indicate that the client is certain to use this as the final pass, in which case the video encoder can skip that evaluation step.
*/
VT_EXPORT OSStatus
VTCompressionSessionEndPass(
	CM_NONNULL VTCompressionSessionRef	session,
	Boolean * CM_NULLABLE				furtherPassesRequestedOut,
	uint32_t * CM_NULLABLE				reserved) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
	
/*!
	 @function	VTCompressionSessionGetTimeRangesForNextPass
	 @abstract	Retrieves the time ranges for the next pass.
	 @discussion
		If VTCompressionSessionEndPass sets *furtherPassesRequestedOut to true, call VTCompressionSessionGetTimeRangesForNextPass to find out the time ranges for the next pass.  Source frames outside these time ranges should be skipped.
		Each time range is considered to include any frame at its start time and not to include any frame at its end time.
		It is an error to call this function when multi-pass encoding has not been enabled by setting kVTCompressionPropertyKey_MultiPassStorage, or when VTCompressionSessionEndPass did not set *furtherPassesRequestedOut to true.
	 @param timeRangeCountOut
		Points to a CMItemCount to receive the number of CMTimeRanges.
	 @param timeRangeArrayOut
		Points to a const CMTimeRange * to receive a pointer to a C array of CMTimeRanges.
		The storage for this array belongs to the VTCompressionSession and should not be modified.
		The pointer will be valid until the next call to VTCompressionSessionEndPass, or until the VTCompressionSession is invalidated or finalized.
*/
VT_EXPORT OSStatus
VTCompressionSessionGetTimeRangesForNextPass(
	CM_NONNULL VTCompressionSessionRef				session,
	CMItemCount * CM_NONNULL						timeRangeCountOut,
	const CMTimeRange * CM_NULLABLE * CM_NONNULL	timeRangeArrayOut ) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0); /* returned pointer will be valid until next call to VTCompressionSessionEndPass */

// See VTSession.h for property access APIs on VTCompressionSessions.
// See VTCompressionProperties.h for standard property keys and values for compression sessions.
	
CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // VTCOMPRESSIONSESSION_H
// ==========  VideoToolbox.framework/Headers/VTUtilities.h
/*
	File:  VTUtilities.h
 
	Framework:  VideoToolbox
 
	Copyright � 2013-2014 Apple Inc. All rights reserved.
 
*/

#ifndef VTUTILITIES_H
#define VTUTILITIES_H

#include <VideoToolbox/VTBase.h>
#include <CoreVideo/CoreVideo.h>
#include <CoreGraphics/CoreGraphics.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

/*!
	@function VTCreateCGImageFromCVPixelBuffer
	@abstract Creates a CGImage using the provided CVPixelBuffer
	@param	pixelBuffer
		The pixelBuffer to be used as the image data source for the CGImage.
	@param	options
		no options currently.  pass NULL.
	@param	imageOut
		pointer to an address to receive the newly created CGImage.
	@discussion
		This routine creates a CGImage representation of the image data contained in
		the provided CVPixelBuffer.
		The source CVPixelBuffer may be retained for the lifetime of the CGImage.  Changes
		to the CVPixelBuffer after making this call (other than releasing it) will have 
		undefined results.
		Not all CVPixelBuffer pixel formats will support conversion into a CGImage compatible
		pixel format.
*/
VT_EXPORT OSStatus 
VTCreateCGImageFromCVPixelBuffer(
	CM_NONNULL CVPixelBufferRef			pixelBuffer,
	CM_NULLABLE CFDictionaryRef			options,
	CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CGImageRef * CM_NONNULL imageOut ) __OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);


#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // VTUTILITIES_H
// ==========  VideoToolbox.framework/Headers/VTDecompressionProperties.h
/*
	File:  VTDecompressionProperties.h
	
	Framework:  VideoToolbox
 
    Copyright 2007-2013 Apple Inc. All rights reserved.
  
	Standard Video Toolbox decompression properties.
*/

#ifndef VTDECOMPRESSIONPROPERTIES_H
#define VTDECOMPRESSIONPROPERTIES_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>

#include <CoreFoundation/CoreFoundation.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)
	
CM_ASSUME_NONNULL_BEGIN

/*!
	@header
	@abstract
		Standard Video Toolbox decompression properties
		
	@discussion
		This file defines standard properties used to describe and configure decompression 
		operations managed by the video toolbox.  
		
		The video toolbox will provide direct support for some of these properties.
		Some properties are supported by individual decoders.
		
		Clients can query supported properties by calling VTSessionCopySupportedPropertyDictionary.
*/

#pragma mark Pixel buffer pools

// Standard properties regarding buffer recycling.  
// These are implemented by the video toolbox.

/*!
	@constant	kVTDecompressionPropertyKey_PixelBufferPool
	@abstract
		A pixel buffer pool for pixel buffers being output by the decompression session.
	@discussion
		This pixel buffer pool is always compatible with the client's pixel buffer attributes
		as specified when calling VTDecompressionSessionCreate.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_PixelBufferPool __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read-only, CVPixelBufferPool

/*!
	@constant	kVTDecompressionPropertyKey_PixelBufferPoolIsShared
	@abstract
		Indicates whether a common pixel buffer pool is shared between
		the video decoder and the session client. 
	@discussion
		This is false if separate pools are used because the pixel buffer attributes specified 
		by the video decoder and the client were incompatible.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_PixelBufferPoolIsShared __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read-only, CFBoolean

/*!
	@constant	kVTDecompressionPropertyKey_OutputPoolRequestedMinimumBufferCount
	@abstract
		Requests that the VTDecompressionSession use the value provided as a minimum buffer
		count for its output CVPixelBufferPool, not releasing buffers while the number in
		use is below this level.
	@discussion
		This property effectively requests that the kCVPixelBufferPoolMinimumBufferCountKey key
		be used for the creation of the output CVPixelBufferPool.
		
		For general playback cases, standard CVPixelBufferPool age-out behaviour should be 
		sufficient and this property should not be needed.  This property should only be used in 
		unusual playback scenarios where a peak pool level is known, and the potential 
		memory overhead is an acceptable tradeoff for avoiding possible buffer reallocation.
		
		Setting this property to NULL or passing in the value 0 will clear this setting and
		remove the minimum buffer count.
		
		Setting this property while a VTDecompressionSession is in use will result in the 
		creation of a new CVPixelBufferPool. This will cause new buffers to be allocated, and 
		existing buffers to be deallocated when they are released.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_OutputPoolRequestedMinimumBufferCount __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0); // Read/Write, CFNumberRef

#pragma mark Asynchronous state

// Standard properties regarding asynchronous state.  
// These are implemented by the video toolbox.

/*!
	@constant	kVTDecompressionPropertyKey_NumberOfFramesBeingDecoded
	@abstract
		Returns the number of frames currently being decoded.
	@discussion
		This number may decrease asynchronously as frames are output.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_NumberOfFramesBeingDecoded __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read-only, CFNumber.

/*!
	@constant	kVTDecompressionPropertyKey_MinOutputPresentationTimeStampOfFramesBeingDecoded
	@abstract
		The minimum output presentation timestamp of the frames currently being decoded.
	@discussion
		This may change asynchronously as frames are output.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_MinOutputPresentationTimeStampOfFramesBeingDecoded __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read-only, CMTime as CFDictionary.

/*!
	@constant	kVTDecompressionPropertyKey_MaxOutputPresentationTimeStampOfFramesBeingDecoded
	@abstract
		The maximum output presentation timestamp of the frames currently being decoded.
	@discussion
		This may change asynchronously as frames are output.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_MaxOutputPresentationTimeStampOfFramesBeingDecoded __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read-only, CMTime as CFDictionary.
	
#pragma mark Content

// Standard properties describing content.
// Video decoders may optionally report these.

/*!
	@constant	kVTDecompressionPropertyKey_ContentHasInterframeDependencies
	@abstract
		Indicates whether the content being decoded has interframe dependencies, if the decoder knows.
	@discussion
		This is an optional property for video decoders to implement.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_ContentHasInterframeDependencies __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read-only, CFBoolean

#pragma mark Hardware acceleration
// hardware acceleration is default behavior on iOS.  no opt-in required.
#if !TARGET_OS_IPHONE
/*!
	@constant	kVTVideoDecoderSpecification_EnableHardwareAcceleratedVideoDecoder
	@abstract
		If set to kCFBooleanTrue, the VideoToolbox will use a hardware accelerated video decoder if available.  If set to
		kCFBooleanFalse, hardware decode will never be used.
	@discussion
		This key is set in the decoderSpecification passed in to VTDecompressionSessionCreate.  Set it
		to kCFBooleanTrue to allow hardware accelerated decode.  To specifically prevent hardware decode,
		this property can be set to kCFBooleanFalse.
		This is useful for clients doing realtime decode operations to allow the VideoToolbox
		to choose the optimal decode path.
*/
VT_EXPORT const CFStringRef kVTVideoDecoderSpecification_EnableHardwareAcceleratedVideoDecoder __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0); // CFBoolean, Optional

/*!
	@constant	kVTVideoDecoderSpecification_RequireHardwareAcceleratedVideoDecoder
	@abstract
		If set to kCFBooleanTrue, the VideoToolbox will try to allocate a hardware accelerated decoder and
		return an error if that isn't possible.
		Setting this key automatically implies kVTVideoDecoderSpecification_EnableHardwareAcceleratedVideoDecoder --
		there is no need to set both and the Enable key does nothing if the Require key is set.
	@discussion
		This key is set in the decoderSpecification passed in to VTDecompressionSessionCreate.  Set it
		to kCFBooleanTrue to require hardware accelerated decode.  If hardware acceleration is not
		possible, the VTDecompressionSessionCreate call will fail.
		This key is useful for clients that have their own software decode implementation or
		those that may want to configure software and hardware decode sessions differently.
		Hardware acceleration may be unavailable for a number of reasons.  A few common cases are:
			- the machine does not have hardware acceleration capabilities
			- the requested decoding format or configuration is not supported
			- the hardware decode resources on the machine are busy
*/
VT_EXPORT const CFStringRef kVTVideoDecoderSpecification_RequireHardwareAcceleratedVideoDecoder __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0); // CFBoolean, Optional

/*!
	@constant	kVTDecompressionPropertyKey_UsingHardwareAcceleratedVideoDecoder
	@abstract
		If set to kCFBooleanTrue, a hardware accelerated video decoder is being used.
	@discussion
		You can query this property using VTSessionCopyProperty after you have enabled hardware
		accelerated decode using kVTVideoDecoderSpecification_EnableHardwareAcceleratedVideoDecoder
		to see if a hardware accelerated decoder was selected.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_UsingHardwareAcceleratedVideoDecoder __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0) ; // CFBoolean, Read; assumed false by default
#endif // !TARGET_OS_IPHONE
	
#pragma mark Decoder behavior

// Standard properties regarding decoder behavior.
// Video decoders may report optionally report these.
	
/*!
	@constant	kVTDecompressionPropertyKey_RealTime
	@abstract
		Hints the video decoder that decompression is, or is not, being performed in real time.
	@discussion
		For non-realtime decompression, clients may set this property to kCFBooleanFalse, which indicates that
		it is OK to run this decode pipeline at a lower priority than is used for realtime decode.
		By default, the VideoToolbox will treat the VTDecompressionSession as though it is being used for
		realtime playback.  Setting the property to NULL is equivalent to setting it to kCFBooleanTrue.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_RealTime __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0); // Read/write, CFBoolean or NULL, Optional, default is true
	
/*!
	@constant	kVTDecompressionPropertyKey_ThreadCount
	@abstract
		Gets number of threads used by codec or suggests number of threads to use.
	@discussion
		This is an optional property for video decoders to implement.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_ThreadCount __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFNumber

// Standard properties about quality of service.
// By default, a decoder should completely decode every frame at full resolution.
// A decoder may support properties to modify the quality of service, using these keys and/or custom keys.

/*!
	@constant	kVTDecompressionPropertyKey_FieldMode
	@abstract
		Requests special handling of interlaced content.  
	@discussion
		This is an optional property for video decoders to implement.
		Decoders should only accept the modes that they will implement.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_FieldMode __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFString, one of
VT_EXPORT const CFStringRef kVTDecompressionProperty_FieldMode_BothFields __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTDecompressionProperty_FieldMode_TopFieldOnly __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTDecompressionProperty_FieldMode_BottomFieldOnly __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTDecompressionProperty_FieldMode_SingleField __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);  // Most appropriate of either TopFieldOnly or BottomFieldOnly
VT_EXPORT const CFStringRef kVTDecompressionProperty_FieldMode_DeinterlaceFields __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);

/*!
	@constant	kVTDecompressionPropertyKey_DeinterlaceMode
	@abstract
		Requests a specific deinterlacing technique.  
	@discussion
		This is an optional property for video decoders to implement.
		Decoders should only accept the modes that they will implement.
		This property is only applicable if kVTDecompressionPropertyKey_FieldMode 
		is set to kVTDecompressionProperty_FieldMode_DeinterlaceFields.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_DeinterlaceMode __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);   // Read/write, CFString; only applicable if kVTDecompressionPropertyKey_FieldMode is kVTDecompressionProperty_FieldMode_DeinterlaceFields; supported values may include:
VT_EXPORT const CFStringRef kVTDecompressionProperty_DeinterlaceMode_VerticalFilter __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);   // apply 0.25-0.50-0.25 vertical filter to individual interlaced frames; default mode
VT_EXPORT const CFStringRef kVTDecompressionProperty_DeinterlaceMode_Temporal __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);	// apply filter that makes use of a window of multiple frames to generate deinterlaced results, and provides a better result at the expense of a pipeline delay; this mode is only used if kVTDecodeFrame_EnableTemporalProcessing is set, otherwise a non-temporal mode (eg, VerticalFilter) will be used instead

/*!
	@constant	kVTDecompressionPropertyKey_ReducedResolutionDecode
	@abstract
		Requests decoding at a smaller resolution than full-size.  
	@discussion
		This is an optional property for video decoders to implement.
		Decoders that only support a fixed set of resolutions should pick the smallest resolution 
		greater than or equal to the requested width x height.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_ReducedResolutionDecode __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFDictionary containing width and height keys and CFNumber values:
VT_EXPORT const CFStringRef kVTDecompressionResolutionKey_Width __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // CFNumber
VT_EXPORT const CFStringRef kVTDecompressionResolutionKey_Height __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // CFNumber

/*!
	@constant	kVTDecompressionPropertyKey_ReducedCoefficientDecode
	@abstract
		Requests approximation during decoding.  
	@discussion
		This is an optional property for video decoders to implement.
		Only decoders for which such approximations make sense should implement this property.
		The meaning of the number of coefficients will be decoder-specific.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_ReducedCoefficientDecode __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFNumber

/*!
	@constant	kVTDecompressionPropertyKey_ReducedFrameDelivery
	@abstract
		Requests frame dropping.
	@discussion
		This is an optional property for video decoders to implement.
		This number is a fraction between 0.0 and 1.0 that indicates what proportion of frames 
		should be delivered -- others may be dropped.  
		For example, 0.25 would indicate that only one frame in every 4 should be delivered.  
		This is a guideline; actual selection of frames is up to the decoder, which will know 
		which frames can be skipped without harm.
		If the decoder does not support this property directly, but reports that the content has 
		no interframe dependencies, the video toolbox may step in and perform simple frame dropping.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_ReducedFrameDelivery __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFNumber in range [0.0,1.0].

/*!
	@constant	kVTDecompressionPropertyKey_OnlyTheseFrames
	@abstract
		Requests that frames be filtered by type.  
	@discussion
		This is an optional property for video decoders to implement.
		If kVTDecompressionPropertyKey_ReducedFrameDelivery is supported and used in conjunction with 
		this property, the ReducedFrameDelivery is the proportion of the frames selected by this property: 
		0.25 and IFrames would indicate that only one I frame in every four should be delivered.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_OnlyTheseFrames __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFString, supported values may include:
VT_EXPORT const CFStringRef kVTDecompressionProperty_OnlyTheseFrames_AllFrames __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTDecompressionProperty_OnlyTheseFrames_NonDroppableFrames __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTDecompressionProperty_OnlyTheseFrames_IFrames __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTDecompressionProperty_OnlyTheseFrames_KeyFrames __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);


/*!
	@constant	kVTDecompressionPropertyKey_SuggestedQualityOfServiceTiers
	@abstract
		Suggests how quality-of-service may be lowered in order to maintain realtime playback.
	@discussion
		This is an optional property for video decoders to implement.
		This property value is an array containing dictionaries of property key/value pairs.  
		The first dictionary in the array should contain the set of properties that restore the 
		default (full) quality of service; later dictionaries should contain property sets with 
		decreasing qualities of service.  Clients may work their way down these tiers until they are 
		able to keep up with the frame rate.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_SuggestedQualityOfServiceTiers __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read-only, CFArray of CFDictionaries containing property key/value pairs

/*!
	@constant	kVTDecompressionPropertyKey_SupportedPixelFormatsOrderedByQuality
	@abstract
		Provides hints about quality tradeoffs between pixel formats.
	@discussion
		This is an optional property for video decoders to implement.
		This property value is an array containing CFNumbers holding CMPixelFormatType values,
		ordered by quality from best to worse.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_SupportedPixelFormatsOrderedByQuality __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read-only, CFArray[CFNumber(CMPixelFormatType)] ordered best to worst, optional

/*!
	@constant	kVTDecompressionPropertyKey_SupportedPixelFormatsOrderedByPerformance
	@abstract
		Provides hints about speed tradeoffs between pixel formats.
	@discussion
		This is an optional property for video decoders to implement.
		This property value is an array containing CFNumbers holding CMPixelFormatType values,
		ordered by speed from fast to slow.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_SupportedPixelFormatsOrderedByPerformance __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read-only, CFArray[CFNumber(CMPixelFormatType)] ordered fast to slow, optional

/*!
	@constant	kVTDecompressionPropertyKey_PixelFormatsWithReducedResolutionSupport
	@abstract
		Indicates which pixel formats support reduced resolution decoding.
	@discussion
		This is an optional property for video decoders to implement.
		This property value is an array containing CFNumbers holding CMPixelFormatType values.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_PixelFormatsWithReducedResolutionSupport __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read-only, CFArray[CFNumber(CMPixelFormatType)], optional

#pragma mark Post-decompression processing

// Standard properties about processing to be performed after decompression.
// These are implemented by the video toolbox.

/*!
	@constant	kVTDecompressionPropertyKey_PixelTransferProperties
	@abstract
		Requests particular pixel transfer features.  
	@discussion
		This property is implemented by the video toolbox.
		This property value is a CFDictionary containing properties from VTPixelTransferProperties.h.
*/
VT_EXPORT const CFStringRef kVTDecompressionPropertyKey_PixelTransferProperties __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/Write, CFDictionary containing properties from VTPixelTransferProperties.h.

	
CM_ASSUME_NONNULL_END

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // VTDECOMPRESSIONPROPERTIES_H
// ==========  VideoToolbox.framework/Headers/VTMultiPassStorage.h
/*
	File:  VTMultiPassStorage.h
	
	Framework:  VideoToolbox
	
	Copyright 2012-2013 Apple Inc. All rights reserved.
	
	Video Toolbox object for storage of multi-pass video encoding metadata.
*/

#ifndef VTMULTIPASSSTORAGE_H
#define VTMULTIPASSSTORAGE_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>
#include <CoreMedia/CMTimeRange.h>

#include <VideoToolbox/VTErrors.h>

#include <CoreFoundation/CoreFoundation.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)    
	
CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@typedef	VTMultiPassStorageRef
	@abstract	A mechanism for storing information for each frame of a multi-pass compression session.
	@discussion
		VTMultiPassStorageRef is a CF type, so call CFRelease and CFRetain to manage objects of this type.
		The data stored in the VTMultiPassStorage is private to the video encoder.
*/
typedef struct CM_BRIDGED_TYPE(id) OpaqueVTMultiPassStorage*  VTMultiPassStorageRef; // a CF type, call CFRetain and CFRelease

VT_EXPORT CFTypeID VTMultiPassStorageGetTypeID(void) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
	
CF_IMPLICIT_BRIDGING_DISABLED

// Interface for video compression session clients:

/*!
	@function	VTMultiPassStorageCreate
	@abstract	Creates a VTMultiPassStorage object using a temporary file.
	@discussion
		The returned VTMultiPassStorage object may be used to perform multi-pass encoding; see kVTCompressionPropertyKey_MultiPassStorage.
		Call CFRelease to release your retain on the created VTMultiPassStorage object when you are done with it.
	@param fileURL
		Specifies where to put the backing file for the VTMultiPassStorage object.
		If you pass NULL for fileURL, the video toolbox will pick a unique temporary file name.
	@param timeRange
		Gives a hint to the multi pass storage about valid time stamps for data.
	@param options
		If the file did not exist when the storage was created, the file will be deleted when the VTMultiPassStorage object is finalized, unless you set the kVTMultiPassStorageCreationOption_DoNotDelete option to kCFBooleanTrue in the options dictionary.
*/
VT_EXPORT OSStatus 
VTMultiPassStorageCreate(
	CM_NULLABLE CFAllocatorRef						allocator,
	CM_NULLABLE CFURLRef							fileURL,
	CMTimeRange										timeRange,				   /* can be kCMTimeRangeInvalid */
	CM_NULLABLE CFDictionaryRef						options,
	CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE VTMultiPassStorageRef * CM_NONNULL multiPassStorageOut) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
	
CF_IMPLICIT_BRIDGING_ENABLED
	
CM_ASSUME_NONNULL_BEGIN

VT_EXPORT const CFStringRef kVTMultiPassStorageCreationOption_DoNotDelete; // CFBoolean, false by default.  Provided for use when debugging video encoders.
	
CM_ASSUME_NONNULL_END


/*!
	@function	VTMultiPassStorageClose
	@abstract	Ensures that any pending data is written to the multipass storage file and closes the file.
	@discussion
		After this function is called, all methods on the multipass storage object will fail.
		It is still necessary to release the object by calling CFRelease.
*/
VT_EXPORT OSStatus 
VTMultiPassStorageClose(
	CM_NONNULL VTMultiPassStorageRef	multiPassStorage ) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
	
CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // VTMULTIPASSSTORAGE_H
// ==========  VideoToolbox.framework/Headers/VTDecompressionSession.h
/*
	File:  VTDecompressionSession.h
	
	Framework:  VideoToolbox
 
    Copyright 2006-2013 Apple Inc. All rights reserved.
  
	Video Toolbox client API for decompressing video frames.
	
	Decompression sessions convert compressed video frames in CMSampleBuffers 
	into uncompressed frames in CVImageBuffers.
*/

#ifndef VTDECOMPRESSIONSESSION_H
#define VTDECOMPRESSIONSESSION_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>

#include <CoreFoundation/CoreFoundation.h>
#include <CoreVideo/CoreVideo.h>
#include <CoreMedia/CMSampleBuffer.h>
#include <CoreMedia/CMFormatDescription.h>
#include <CoreMedia/CMTime.h>

#include <VideoToolbox/VTSession.h>
#include <VideoToolbox/VTDecompressionProperties.h>

#include <VideoToolbox/VTErrors.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

/*!
	@typedef	VTDecompressionSessionRef
	@abstract	A reference to a Video Toolbox Decompression Session.
	@discussion
		A decompression session supports the decompression of a sequence of video frames.
		The session reference is a reference-counted CF object.
		To create a decompression session, call VTDecompressionSessionCreate; 
		then you can optionally configure the session using VTSessionSetProperty;
		then to decode frames, call VTDecompressionSessionDecodeFrame.
		When you are done with the session, you should call VTDecompressionSessionInvalidate
		to tear it down and CFRelease to release your object reference.
 */

typedef struct CM_BRIDGED_TYPE(id) OpaqueVTDecompressionSession*  VTDecompressionSessionRef;

/*!
	@typedef	VTDecompressionOutputCallback
	@abstract	Prototype for callback invoked when frame decompression is complete.
	@discussion 
		When you create a decompression session, you pass in a callback function to be called 
		for decompressed frames.  This function will not necessarily be called in display order.
	@param	decompressionOutputRefCon
		The callback's reference value, copied from the decompressionOutputRefCon field of the
		VTDecompressionOutputCallbackRecord structure.
	@param	sourceFrameRefCon
		The frame's reference value, copied from the sourceFrameRefCon argument to 
		VTDecompressionSessionDecodeFrame.
	@param	status
		noErr if decompression was successful; an error code if decompression was not successful.
	@param	infoFlags
		Contains information about the decode operation.
		The kVTDecodeInfo_Asynchronous bit may be set if the decode ran asynchronously.
		The kVTDecodeInfo_FrameDropped bit may be set if the frame was dropped.
		If the kVTDecodeInfo_ImageBufferModifiable bit is set, it is safe for the client to modify the imageBuffer.
	@param	imageBuffer
		Contains the decompressed frame, if decompression was successful; otherwise, NULL.
		IMPORTANT: The video decompressor may still be referencing the imageBuffer returned in this
		callback if the kVTDecodeInfo_ImageBufferModifiable flag is not set.  Unless this flag
		is set, it is not safe to modify the returned imageBuffer.
	@param	presentationTimeStamp
		The frame's presentation timestamp, which will be determined by calling 
		CMSampleBufferGetOutputPresentationTimeStamp; kCMTimeInvalid if not available.
	@param	presentationDuration
		The frame's presentation duration, which will be determined by calling
		CMSampleBufferGetOutputDuration; kCMTimeInvalid if not available.
*/

typedef void (*VTDecompressionOutputCallback)(
		void * CM_NULLABLE decompressionOutputRefCon,
		void * CM_NULLABLE sourceFrameRefCon,
		OSStatus status, 
		VTDecodeInfoFlags infoFlags,
		CM_NULLABLE CVImageBufferRef imageBuffer,
		CMTime presentationTimeStamp, 
		CMTime presentationDuration );

struct VTDecompressionOutputCallbackRecord {
	CM_NULLABLE VTDecompressionOutputCallback  decompressionOutputCallback;
	void * CM_NULLABLE                         decompressionOutputRefCon;
};
typedef struct VTDecompressionOutputCallbackRecord VTDecompressionOutputCallbackRecord;

/*!
	@function	VTDecompressionSessionCreate
	@abstract	Creates a session for decompressing video frames.
    @discussion 
		Decompressed frames will be emitted through calls to outputCallback.
	@param	allocator
		An allocator for the session.  Pass NULL to use the default allocator.
	@param	videoFormatDescription
		Describes the source video frames.
	@param	videoDecoderSpecification
		Specifies a particular video decoder that must be used.  
		Pass NULL to let the video toolbox choose a decoder.
	@param	destinationImageBufferAttributes
		Describes requirements for emitted pixel buffers.
		Pass NULL to set no requirements.
	@param	outputCallback
		The callback to be called with decompressed frames.
		Pass NULL if and only if you will be calling VTDecompressionSessionDecodeFrameWithOutputHandler for decoding frames.
	@param	decompressionSessionOut
		Points to a variable to receive the new decompression session.
	
*/
VT_EXPORT OSStatus 
VTDecompressionSessionCreate(
	CM_NULLABLE CFAllocatorRef                              allocator,
	CM_NONNULL CMVideoFormatDescriptionRef					videoFormatDescription,
	CM_NULLABLE CFDictionaryRef								videoDecoderSpecification,
	CM_NULLABLE CFDictionaryRef                             destinationImageBufferAttributes,
	const VTDecompressionOutputCallbackRecord * CM_NULLABLE outputCallback,
	CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE VTDecompressionSessionRef * CM_NONNULL decompressionSessionOut) __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);

CF_IMPLICIT_BRIDGING_ENABLED
	
/*!
	@function	VTDecompressionSessionInvalidate
	@abstract	Tears down a decompression session.
    @discussion 
    	When you are done with a decompression session you created, call VTDecompressionSessionInvalidate 
    	to tear it down and then CFRelease to release your object reference.
    	When a decompression session's retain count reaches zero, it is automatically invalidated, but 
    	since sessions may be retained by multiple parties, it can be hard to predict when this will happen.
    	Calling VTDecompressionSessionInvalidate ensures a deterministic, orderly teardown.
*/
VT_EXPORT void 
VTDecompressionSessionInvalidate( CM_NONNULL VTDecompressionSessionRef session ) __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);

/*!
	@function VTDecompressionSessionGetTypeID
	@abstract Returns the CFTypeID for decompression sessions.  
*/
VT_EXPORT CFTypeID 
VTDecompressionSessionGetTypeID(void) __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);

/*!
	@function	VTDecompressionSessionDecodeFrame
	@abstract	Decompresses a video frame.
	@param	session
		The decompression session.
	@param	sampleBuffer
		A CMSampleBuffer containing one or more video frames.  
	@param	decodeFlags
		A bitfield of directives to the decompression session and decoder.
		The kVTDecodeFrame_EnableAsynchronousDecompression bit indicates whether the video decoder 
		may decompress the frame asynchronously.
		The kVTDecodeFrame_EnableTemporalProcessing bit indicates whether the decoder may delay calls to the output callback
		so as to enable processing in temporal (display) order.
		If both flags are clear, the decompression shall complete and your output callback function will be called 
		before VTDecompressionSessionDecodeFrame returns.
		If either flag is set, VTDecompressionSessionDecodeFrame may return before the output callback function is called.  
	@param	sourceFrameRefCon
		Your reference value for the frame.  
		Note that if sampleBuffer contains multiple frames, the output callback function will be called
		multiple times with this sourceFrameRefCon.
	@param	infoFlagsOut
		Points to a VTDecodeInfoFlags to receive information about the decode operation.
		The kVTDecodeInfo_Asynchronous bit may be set if the decode is (or was) running
		asynchronously.
		The kVTDecodeInfo_FrameDropped bit may be set if the frame was dropped (synchronously).
		Pass NULL if you do not want to receive this information.
*/
VT_EXPORT OSStatus
VTDecompressionSessionDecodeFrame(
	CM_NONNULL VTDecompressionSessionRef	session,
	CM_NONNULL CMSampleBufferRef			sampleBuffer,
	VTDecodeFrameFlags						decodeFlags, // bit 0 is enableAsynchronousDecompression
	void * CM_NULLABLE						sourceFrameRefCon,
	VTDecodeInfoFlags * CM_NULLABLE 		infoFlagsOut) __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
	
#if __BLOCKS__
/*!
	@typedef	VTDecompressionOutputHandler
	@abstract	Prototype for block invoked when frame decompression is complete.
	@discussion
		When you decode a frame, you pass in a callback block to be called
		for that decompressed frame.  This block will not necessarily be called in display order.
	@param	status
		noErr if decompression was successful; an error code if decompression was not successful.
	@param	infoFlags
		Contains information about the decode operation.
		The kVTDecodeInfo_Asynchronous bit may be set if the decode ran asynchronously.
		The kVTDecodeInfo_FrameDropped bit may be set if the frame was dropped.
		If the kVTDecodeInfo_ImageBufferModifiable bit is set, it is safe for the client to modify the imageBuffer.
	@param	imageBuffer
		Contains the decompressed frame, if decompression was successful; otherwise, NULL.
		IMPORTANT: The video decompressor may still be referencing the imageBuffer returned in this
		callback if the kVTDecodeInfo_ImageBufferModifiable flag is not set.  Unless this flag
		is set, it is not safe to modify the returned imageBuffer.
	@param	presentationTimeStamp
		The frame's presentation timestamp; kCMTimeInvalid if not available.
	@param	presentationDuration
		The frame's presentation duration; kCMTimeInvalid if not available.
 */
typedef void (^VTDecompressionOutputHandler)(
	OSStatus status,
	VTDecodeInfoFlags infoFlags,
	CM_NULLABLE CVImageBufferRef imageBuffer,
	CMTime presentationTimeStamp,
	CMTime presentationDuration );
	
/*!
	@function	VTDecompressionSessionDecodeFrameWithOutputHandler
	@abstract	Decompresses a video frame.
	@discussion
		Cannot be called with a session created with a VTDecompressionOutputCallbackRecord.
	@param	session
		The decompression session.
	@param	sampleBuffer
		A CMSampleBuffer containing one or more video frames.
	@param	decodeFlags
		A bitfield of directives to the decompression session and decoder.
		The kVTDecodeFrame_EnableAsynchronousDecompression bit indicates whether the video decoder
		may decompress the frame asynchronously.
		The kVTDecodeFrame_EnableTemporalProcessing bit indicates whether the decoder may delay calls to the output callback
		so as to enable processing in temporal (display) order.
		If both flags are clear, the decompression shall complete and your output callback function will be called
		before VTDecompressionSessionDecodeFrame returns.
		If either flag is set, VTDecompressionSessionDecodeFrame may return before the output callback function is called.
	@param	infoFlagsOut
		Points to a VTDecodeInfoFlags to receive information about the decode operation.
		The kVTDecodeInfo_Asynchronous bit may be set if the decode is (or was) running
		asynchronously.
		The kVTDecodeInfo_FrameDropped bit may be set if the frame was dropped (synchronously).
		Pass NULL if you do not want to receive this information.
	@param	outputHandler
		The block to be called when decoding the frame is completed.
 */
VT_EXPORT OSStatus
VTDecompressionSessionDecodeFrameWithOutputHandler(
	CM_NONNULL VTDecompressionSessionRef	session,
	CM_NONNULL CMSampleBufferRef			sampleBuffer,
	VTDecodeFrameFlags						decodeFlags, // bit 0 is enableAsynchronousDecompression
	VTDecodeInfoFlags * CM_NULLABLE			infoFlagsOut,
	CM_NONNULL VTDecompressionOutputHandler	outputHandler ) __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
#endif // __BLOCKS__

/*!
	@function VTDecompressionSessionFinishDelayedFrames
	@abstract Directs the decompression session to emit all delayed frames.
	@discussion
		By default, the decompression session may not delay frames indefinitely; 
		frames may only be indefinitely delayed if the client opts in via
		kVTDecodeFrame_EnableTemporalProcessing.
		IMPORTANT NOTE: This function may return before all delayed frames are emitted. 
		To wait for them, call VTDecompressionSessionWaitForAsynchronousFrames instead.
*/
VT_EXPORT OSStatus
VTDecompressionSessionFinishDelayedFrames(
	CM_NONNULL VTDecompressionSessionRef		session) __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);

/*!
	@function VTDecompressionSessionCanAcceptFormatDescription
	@abstract Indicates whether the session can decode frames with the given format description.
	@discussion
		Some video decoders are able to accommodate minor changes in format without needing to be
		completely reset in a new session.  This function can be used to test whether a format change
		is sufficiently minor.
*/
VT_EXPORT Boolean 
VTDecompressionSessionCanAcceptFormatDescription( 
	CM_NONNULL VTDecompressionSessionRef		session,
	CM_NONNULL CMFormatDescriptionRef			newFormatDesc ) __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);

/*!
	@function VTDecompressionSessionWaitForAsynchronousFrames
	@abstract Waits for any and all outstanding asynchronous and delayed frames to complete, then returns.
	@discussion
		This function automatically calls VTDecompressionSessionFinishDelayedFrames, 
		so clients don't have to call both.  
*/
VT_EXPORT OSStatus
VTDecompressionSessionWaitForAsynchronousFrames(
	CM_NONNULL VTDecompressionSessionRef       session) __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);

CF_IMPLICIT_BRIDGING_DISABLED
	
/*!
	@function	VTDecompressionSessionCopyBlackPixelBuffer
	@abstract	Copies a black pixel buffer from the decompression session.
    @discussion 
		The pixel buffer is in the same format that the session is decompressing to.
	@param	session
		The decompression session.
	@param	pixelBufferOut
		Points to a variable to receive the copied pixel buffer.
	
*/
VT_EXPORT OSStatus
VTDecompressionSessionCopyBlackPixelBuffer(
   CM_NONNULL VTDecompressionSessionRef			session,
   CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CVPixelBufferRef * CM_NONNULL pixelBufferOut ) __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
	
// See VTSession.h for property access APIs on VTDecompressionSessions.
// See VTDecompressionProperties.h for standard property keys and values for decompression sessions.

    
#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif


#endif // VTDECOMPRESSIONSESSION_H
// ==========  VideoToolbox.framework/Headers/VideoToolbox.h
/* VideoToolbox.h

   Copyright (c) 2008-2014 Apple Computer, Inc.
   All rights reserved. */

#include <VideoToolbox/VTCompressionProperties.h>
#include <VideoToolbox/VTCompressionSession.h>
#include <VideoToolbox/VTDecompressionProperties.h>
#include <VideoToolbox/VTDecompressionSession.h>
#include <VideoToolbox/VTErrors.h>
#include <VideoToolbox/VTSession.h>
#include <VideoToolbox/VTFrameSilo.h>
#include <VideoToolbox/VTMultiPassStorage.h>
#include <VideoToolbox/VTVideoEncoderList.h>
#include <VideoToolbox/VTUtilities.h>
#if !TARGET_OS_IPHONE
#include <VideoToolbox/VTPixelTransferProperties.h>
#include <VideoToolbox/VTPixelTransferSession.h>
#include <VideoToolbox/VTProfessionalVideoWorkflow.h>
#endif // !TARGET_OS_IPHONE
// ==========  VideoToolbox.framework/Headers/VTSession.h
/*
	File:  VTSession.h
	
	Framework:  VideoToolbox
 
    Copyright 2006-2013 Apple Inc. All rights reserved.
  
	Client APIs common to all Video Toolbox session types.
*/

#ifndef VTSESSION_H
#define VTSESSION_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>

#include <CoreFoundation/CoreFoundation.h>
#include <VideoToolbox/VTErrors.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

/*!
	@typedef	VTSessionRef
	@abstract	A reference to either a Video Toolbox Decompression Session, 
				Compression Session or Pixel Transfer Session.
 */

typedef CM_BRIDGED_TYPE(id) CFTypeRef  VTSessionRef;

/*!
	@function	VTSessionCopySupportedPropertyDictionary
	@abstract	Returns a dictionary enumerating all the supported properties of a video toolbox session.  
	@discussion	
		The keys of the returned dictionary are the supported property keys.
		The values are themselves dictionaries, each containing the following optional fields:
		<OL>
		<LI> the type of value, (kVTPropertyTypeKey)
		<LI> the read/write status of the property (kVTPropertyReadWriteStatusKey),
		<LI> whether the property is suitable for serialization (kVTPropertyShouldBeSerializedKey),
		<LI> a range or list of the supported values, if appropriate, and
		<LI> developer-level documentation for the property (kVTPropertyDocumentationKey).
		</OL>
		The caller must release the returned dictionary.
*/

VT_EXPORT OSStatus 
VTSessionCopySupportedPropertyDictionary(
  CM_NONNULL VTSessionRef					session,
  CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CFDictionaryRef * CM_NONNULL supportedPropertyDictionaryOut ) __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);

CF_IMPLICIT_BRIDGING_ENABLED

CM_ASSUME_NONNULL_BEGIN
	
VT_EXPORT const CFStringRef kVTPropertyTypeKey __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // value is CFStringRef, one of the following:
	VT_EXPORT const CFStringRef kVTPropertyType_Enumeration __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // value is one of a list of CFStrings
	VT_EXPORT const CFStringRef kVTPropertyType_Boolean __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // value is a CFBoolean
	VT_EXPORT const CFStringRef kVTPropertyType_Number __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // value is a CFNumber
VT_EXPORT const CFStringRef kVTPropertyReadWriteStatusKey __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
	VT_EXPORT const CFStringRef kVTPropertyReadWriteStatus_ReadOnly __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
	VT_EXPORT const CFStringRef kVTPropertyReadWriteStatus_ReadWrite __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTPropertyShouldBeSerializedKey __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // CFBoolean, false by default
VT_EXPORT const CFStringRef kVTPropertySupportedValueMinimumKey __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // CFNumber
VT_EXPORT const CFStringRef kVTPropertySupportedValueMaximumKey __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // CFNumber
VT_EXPORT const CFStringRef kVTPropertySupportedValueListKey __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // CFArray of appropriate values
VT_EXPORT const CFStringRef kVTPropertyDocumentationKey __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // a CFString for developer eyes only

	
CM_ASSUME_NONNULL_END

/*!
	@function	VTSessionSetProperty
	@abstract	Sets a property on a video toolbox session.
	@discussion
		Setting a property value to NULL restores the default value.
*/
VT_EXPORT OSStatus 
VTSessionSetProperty(
  CM_NONNULL VTSessionRef       session,
  CM_NONNULL CFStringRef        propertyKey,
  CM_NONNULL CFTypeRef          propertyValue ) __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
	
CF_IMPLICIT_BRIDGING_DISABLED

/*!
	@function	VTSessionCopyProperty
	@abstract	Retrieves a property on a video toolbox session.  
	@discussion	
		The caller must release the retrieved property value.
		<BR>
		Note: for most types of property, the returned values should be considered immutable.
		In particular, for CFPropertyList types, sharing of mutable property value 
		objects between the client, session and codec should be avoided.
		However, some properties will be used for exchanging service objects that are inherently 
		mutable (eg, CVPixelBufferPool).
	@param	propertyKey
		The key for the property to retrieve.
	@param	allocator
		An allocator suitable for use when copying property values.
	@param propertyValueOut
		Points to a variable to receive the property value, which must be a CF-registered type --
		the caller may call CFGetTypeID() on it to identify which specific type.
		The caller must release the this property value.
	@result
		noErr if successful; kVTPropertyNotSupportedErr for unrecognized or unsupported properties.
*/
VT_EXPORT OSStatus 
VTSessionCopyProperty(
  CM_NONNULL VTSessionRef		session,
  CM_NONNULL CFStringRef		propertyKey,
  CM_NULLABLE CFAllocatorRef	allocator,
  void * CM_NULLABLE			propertyValueOut ) __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);

CF_IMPLICIT_BRIDGING_ENABLED
/*!
	@function	VTSessionSetProperties
	@abstract	Sets multiple properties at once.
	@discussion
		Sets the properties specified by keys in propertyDictionary to the corresponding values.
*/
VT_EXPORT OSStatus 
VTSessionSetProperties(
  CM_NONNULL VTSessionRef		session,
  CM_NONNULL CFDictionaryRef	propertyDictionary ) __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
	
CF_IMPLICIT_BRIDGING_DISABLED

/*!
	@function	VTSessionCopySerializableProperties
	@abstract	Retrieves the set of serializable property keys and their current values.
	@discussion	
		The serializable properties are those which can be saved and applied to a different session.
		The caller must release the returned dictionary.
*/
VT_EXPORT OSStatus
VTSessionCopySerializableProperties(
  CM_NONNULL VTSessionRef					session,
  CM_NULLABLE CFAllocatorRef				allocator,
  CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CFDictionaryRef * CM_NONNULL	dictionaryOut ) __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);


#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // VTSESSION_H
// ==========  VideoToolbox.framework/Headers/VTErrors.h
/*
	File:  VTErrors.h
	
	Framework:  VideoToolbox
 
    Copyright 2006-2013 Apple Inc. All rights reserved.
  
*/

#ifndef VTERRORS_H
#define VTERRORS_H

#include <CoreMedia/CMBase.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

// Error codes
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif // COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
	{
	kVTPropertyNotSupportedErr				= -12900,
	kVTPropertyReadOnlyErr					= -12901,
	kVTParameterErr							= -12902,
	kVTInvalidSessionErr					= -12903,
	kVTAllocationFailedErr					= -12904,
	kVTPixelTransferNotSupportedErr			= -12905, // c.f. -8961
	kVTCouldNotFindVideoDecoderErr			= -12906,
	kVTCouldNotCreateInstanceErr			= -12907,
	kVTCouldNotFindVideoEncoderErr			= -12908,
	kVTVideoDecoderBadDataErr				= -12909, // c.f. -8969
	kVTVideoDecoderUnsupportedDataFormatErr	= -12910, // c.f. -8970
	kVTVideoDecoderMalfunctionErr			= -12911, // c.f. -8960
	kVTVideoEncoderMalfunctionErr			= -12912,
	kVTVideoDecoderNotAvailableNowErr		= -12913,
	kVTImageRotationNotSupportedErr			= -12914,
	kVTVideoEncoderNotAvailableNowErr		= -12915,
	kVTFormatDescriptionChangeNotSupportedErr	= -12916,
	kVTInsufficientSourceColorDataErr		= -12917,
	kVTCouldNotCreateColorCorrectionDataErr	= -12918,
	kVTColorSyncTransformConvertFailedErr	= -12919,
	kVTVideoDecoderAuthorizationErr			= -12210,
	kVTVideoEncoderAuthorizationErr			= -12211,
	kVTColorCorrectionPixelTransferFailedErr	= -12212,
	kVTMultiPassStorageIdentifierMismatchErr	= -12213,
	kVTMultiPassStorageInvalidErr			= -12214,
	kVTFrameSiloInvalidTimeStampErr			= -12215,
	kVTFrameSiloInvalidTimeRangeErr			= -12216,
	kVTCouldNotFindTemporalFilterErr		= -12217,
	kVTPixelTransferNotPermittedErr			= -12218,
};

/*!
	@enum		VTDecodeFrameFlags
	@abstract	Directives for the decompression session and the video decoder, passed into
				decodeFlags parameter of VTDecompressionSessionDecodeFrame.

	@constant	kVTDecodeFrame_EnableAsynchronousDecompression
		With the kVTDecodeFrame_EnableAsynchronousDecompression bit clear, the video decoder 
		is compelled to emit every frame before it returns.  With the bit set, the decoder may 
		process frames asynchronously, but it is not compelled to do so.  
	@constant	kVTDecodeFrame_DoNotOutputFrame
		A hint to the decompression session and video decoder that a CVImageBuffer should not
		be emitted for this frame.  NULL will be returned instead. 
	@constant	kVTDecodeFrame_1xRealTimePlayback
		A hint to the video decoder that it would be OK to use a low-power mode that can not decode faster than 1x realtime.
	@constant	kVTDecodeFrame_EnableTemporalProcessing
		With the kVTDecodeFrame_EnableTemporalProcessing bit clear, the video decoder should emit 
		every frame once that frame's decoding is done -- frames may not be delayed indefinitely.  With 
		the bit set, it is legal for the decoder to delay frames indefinitely -- at least 
		until VTDecompressionSessionFinishDelayedFrames or VTDecompressionSessionInvalidate is called.
*/
typedef CF_OPTIONS(uint32_t, VTDecodeFrameFlags) {
	kVTDecodeFrame_EnableAsynchronousDecompression = 1<<0,
	kVTDecodeFrame_DoNotOutputFrame = 1<<1,
	kVTDecodeFrame_1xRealTimePlayback = 1<<2, 
	kVTDecodeFrame_EnableTemporalProcessing = 1<<3,
};

// Informational status for decoding -- non-error flags 
typedef CF_OPTIONS(UInt32, VTDecodeInfoFlags) {
	kVTDecodeInfo_Asynchronous = 1UL << 0,
	kVTDecodeInfo_FrameDropped = 1UL << 1,
	kVTDecodeInfo_ImageBufferModifiable = 1UL << 2,
};

// Informational status for encoding -- non-error flags 
typedef CF_OPTIONS(UInt32, VTEncodeInfoFlags) {
	kVTEncodeInfo_Asynchronous = 1UL << 0,
	kVTEncodeInfo_FrameDropped = 1UL << 1,
};

#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // VTERRORS_H
// ==========  VideoToolbox.framework/Headers/VTVideoEncoderList.h
/*
	File:  VTVideoEncoderList.h
 
	Framework:  VideoToolbox
 
	Copyright 2012-2013 Apple Inc. All rights reserved.
 
*/

#ifndef VTVIDEOENCODERLIST_H
#define VTVIDEOENCODERLIST_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>
#include <CoreMedia/CMFormatDescription.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

/*!
	@function	VTCopyVideoEncoderList
	@abstract	Builds a list of available video encoders.
	@discussion
		The caller must CFRelease the returned list.
*/
VT_EXPORT OSStatus VTCopyVideoEncoderList( 
	CM_NULLABLE CFDictionaryRef			options,
	CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CFArrayRef * CM_NONNULL listOfVideoEncodersOut ) __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
	
CM_ASSUME_NONNULL_BEGIN

// returns CFArray of CFDictionaries with following keys:
VT_EXPORT const CFStringRef kVTVideoEncoderList_CodecType __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // CFNumber for four-char-code (eg, 'avc1')
VT_EXPORT const CFStringRef kVTVideoEncoderList_EncoderID __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // CFString, reverse-DNS-style unique identifier for this encoder; may be passed as kVTVideoEncoderSpecification_EncoderID
VT_EXPORT const CFStringRef kVTVideoEncoderList_CodecName __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // CFString, for display to user (eg, "H.264")
VT_EXPORT const CFStringRef kVTVideoEncoderList_EncoderName __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // CFString, for display to user (eg, "Apple H.264")
VT_EXPORT const CFStringRef kVTVideoEncoderList_DisplayName __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // CFString (same as CodecName if there is only one encoder for that format, otherwise same as EncoderName)

CM_ASSUME_NONNULL_END

#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // VTVIDEOENCODERLIST_H
// ==========  VideoToolbox.framework/Headers/VTBase.h
/*
	File:  VTBase.h

	Framework:  VideoToolbox

	Copyright 2013 Apple Inc. All rights reserved.

*/

#ifndef VTBASE_H
#define VTBASE_H

#include <Availability.h>

#if defined(__cplusplus)
extern "C"
{
#endif

#pragma pack(push, 4)


#if TARGET_OS_IPHONE
#define VT_AVAILABLE_STARTING(_ver) 
#else
#define VT_AVAILABLE_STARTING(_ver) __OSX_AVAILABLE_STARTING(__MAC_##_ver, __IPHONE_NA)
#endif


#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // VTBASE_H
// ==========  VideoToolbox.framework/Headers/VTCompressionProperties.h
/*
	File:  VTCompressionProperties.h
	
	Framework:  VideoToolbox
	
	Copyright 2007-2013 Apple Inc. All rights reserved.
	
	Standard Video Toolbox compression properties.
*/

#ifndef VTCOMPRESSIONPROPERTIES_H
#define VTCOMPRESSIONPROPERTIES_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>

#include <CoreFoundation/CoreFoundation.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)    
	
CM_ASSUME_NONNULL_BEGIN

/*!
	@header
	@abstract
		Standard Video Toolbox compression properties
		
	@discussion
		This file defines standard properties used to describe and configure compression 
		operations managed by the video toolbox.  
		
		The video toolbox will provide direct support for some of these properties.
		Some properties are supported by individual encoders.
		
		Clients can query supported properties by calling VTSessionCopySupportedPropertyDictionary.
*/

#pragma mark Buffers

// Standard properties regarding buffer recycling.  
// These are implemented by the video toolbox.

/*!
	@constant	kVTCompressionPropertyKey_NumberOfPendingFrames
	@abstract
		The number of pending frames in the compression session. 
	@discussion
		This number may decrease asynchronously.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_NumberOfPendingFrames __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read-only, CFNumber<int>
	
/*!
	@constant	kVTCompressionPropertyKey_PixelBufferPoolIsShared
	@abstract
		Indicates whether the a common pixel buffer pool is shared between
		the video encoder and the session client. 
	@discussion
		This is false if separate pools are used because the video encoder's 
		and the client's pixel buffer attributes were incompatible.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_PixelBufferPoolIsShared __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read-only, CFBoolean

/*!
	@constant	kVTCompressionPropertyKey_VideoEncoderPixelBufferAttributes
	@abstract
		The video encoder's pixel buffer attributes for the compression session. 
	@discussion
		You can use these to create a pixel buffer pool for source pixel buffers. 
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_VideoEncoderPixelBufferAttributes __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read-only, CFDictionary

// Standard properties describing content.

// Standard properties regarding encoder behavior.
// Video encoders may report optionally report these.

#pragma mark Frame dependency

/*!
	@constant	kVTCompressionPropertyKey_MaxKeyFrameInterval
	@abstract
		The maximum interval between key frames, also known as the key frame rate. 
	@discussion
		Key frames, also known as sync frames, reset inter-frame
		dependencies; decoding a key frame is sufficient to prepare a
		decoder for correctly decoding the difference frames that
		follow. 
		Video encoders are allowed to generate key frames more frequently if
		this would result in more efficient compression. 
		The default key frame interval is 0, which indicates that the
		video encoder should choose where to place all key frames. A key
		frame interval of 1 indicates that every frame must be a key
		frame, 2 indicates that at least every other frame must be a key
		frame, etc.
		See also kVTCompressionPropertyKey_AllowTemporalCompression.
		
		This key can be set in conjunction with 
		kVTCompressionPropertyKey_MaxKeyFrameIntervalDuration,
		and both limits will be enforced - requiring a keyframe every X
		frames or every Y seconds, whichever comes first.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaxKeyFrameInterval __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFNumber<int>, Optional

/*!
	@constant	kVTCompressionPropertyKey_MaxKeyFrameIntervalDuration
	@abstract
		The maximum duration from one key frame to the next in seconds. 
	@discussion
		Zero by default, which means no limit.  
		This property is particularly useful when the frame rate is variable.
		See kVTCompressionPropertyKey_MaxKeyFrameInterval for more discussion
		of key frames.
		
		This key can be set in conjunction with 
		kVTCompressionPropertyKey_MaxKeyFrameInterval,
		and both limits will be enforced - requiring a keyframe every X
		frames or every Y seconds, whichever comes first.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaxKeyFrameIntervalDuration __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFNumber<seconds>, Optional


/*!
	@constant	kVTCompressionPropertyKey_AllowTemporalCompression
	@abstract
		Enables temporal compression.
	@discussion
		True by default.  Set this to false to require key-frame-only compression.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AllowTemporalCompression __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/Write, CFBoolean, Optional, defaults to true

/*!
	@constant	kVTCompressionPropertyKey_AllowFrameReordering
	@abstract
		Enables frame reordering. 
	@discussion
		In order to encode B frames, a video encoder must reorder frames,
		which means that the order in which they will be emitted and
		stored (the decode order) is different from the order in which
		they were presented to the video encoder (the display order). 
		True by default.  Set this to false to prevent frame reordering.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AllowFrameReordering __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/Write, CFBoolean, Optional, defaults to true

#pragma mark Rate control

/*!
	@constant	kVTCompressionPropertyKey_AverageBitRate
	@abstract
		The long-term desired average bit rate in bits per second. 
	@discussion
		This is not a hard limit; the bit rate may peak above this. 
		The default bit rate is zero, which indicates that the video encoder 
		should determine the size of compressed data. 
		Note that bit rate settings only have an effect when timing
		information is provided for source frames, and that some codecs do
		not support limiting to specified bit rates.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AverageBitRate __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFNumber<SInt32>, Optional

/*!
	@constant	kVTCompressionPropertyKey_DataRateLimits
	@abstract
		Zero, one or two hard limits on data rate.
	@discussion
		Each hard limit is described by a data size in bytes and a
		duration in seconds, and requires that the total size of
		compressed data for any contiguous segment of that duration (in
		decode time) must not exceed the data size. 
		By default, no data rate limits are set. 
		The property is a CFArray of an even number of CFNumbers,
		alternating between bytes and seconds.
		Note that data rate settings only have an effect when timing
		information is provided for source frames, and that some codecs do
		not support limiting to specified data rates.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_DataRateLimits __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFArray[CFNumber], [bytes, seconds, bytes, seconds...], Optional

/*!
	@constant	kVTCompressionPropertyKey_Quality
	@abstract
		The desired compression quality.
	@discussion
		Some encoders, such as JPEG, describe the compression level of each
		image with a quality value.  This value should be specified as a
		number in the range of 0.0 to 1.0, where low = 0.25, normal = 0.50,
		high = 0.75, and 1.0 implies lossless compression for encoders that
		support it.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_Quality __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFNumber<Float>, Optional

/*!
	@constant	kVTCompressionPropertyKey_MoreFramesBeforeStart
	@abstract
		Indicates whether and how a compression session's frames will be
		concatenated with other compressed frames to form a longer series.
	@discussion
		True if frames compressed in a separate session will be
		concatenated before the beginning of this one.  False if this is a
		stand-alone session, or if this session will encode the first
		segment of a multi-segment compression. By default, false.
		
		This information enables video encoders to ensure that compressed
		segments can be concatenated smoothly -- for example, avoiding
		data rate spikes where segments are joined. 
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MoreFramesBeforeStart __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFBoolean, Optional

/*!
	@constant	kVTCompressionPropertyKey_MoreFramesAfterEnd
	@abstract
		Indicates whether and how a compression session's frames will be
		concatenated with other compressed frames to form a longer series.
	@discussion
		True if frames compressed in a separate session will be
		concatenated following the end of this one. False if this is a
		stand-alone session, or if this session will encode the last
		segment of a multi-segment compression. By default, false.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MoreFramesAfterEnd __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFBoolean, Optional

#pragma mark Bitstream configuration

/*!
	@constant	kVTCompressionPropertyKey_ProfileLevel
	@abstract
		Specifies the profile and level for the encoded bitstream.
	@discussion
		Available profiles and levels vary across formats and between video encoders.
		Video encoders should use standard keys where available, and follow standard patterns where not.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ProfileLevel __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFString (enumeration), Optional

VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_1_3 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_3_0 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_3_1 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_3_2 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_4_0 __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_4_1 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_4_2 __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_5_0 __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_5_1 __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_5_2 __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_AutoLevel __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_3_0 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_3_1 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_3_2 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_4_0 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_4_1 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_4_2 __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_5_0 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_5_1 __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_5_2 __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_AutoLevel __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Extended_5_0 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_Extended_AutoLevel __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_3_0 __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_3_1 __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_3_2 __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_4_0 __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_4_1 __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_4_2 __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_5_0 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_5_1 __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_5_2 __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_AutoLevel __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);

VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Simple_L0 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Simple_L1 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Simple_L2 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Simple_L3 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Main_L2 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Main_L3 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Main_L4 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L0 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L1 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L2 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L3 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L4 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);

VT_EXPORT const CFStringRef kVTProfileLevel_H263_Profile0_Level10 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H263_Profile0_Level45 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTProfileLevel_H263_Profile3_Level45 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0);


/*!
	 @constant	kVTCompressionPropertyKey_H264EntropyMode
	 @abstract
		The entropy encoding mode for H.264 compression.
	 @discussion
		If supported by an H.264 encoder, this property controls whether the encoder should use
		Context-based Adaptive Variable Length Coding (CAVLC) or Context-based Adaptive Binary Arithmetic Coding (CABAC).
		CABAC generally gives better compression at the expense of higher computational overhead.
		The default value is encoder-specific and may change depending on other encoder settings.
		Care should be taken when using this property -- changes may result in a configuration
		which is not compatible with a requested Profile and Level.  Results in this case are undefined,
		and could include encode errors or a non-compliant output stream.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_H264EntropyMode __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);	// Read/write, CFString, optional
VT_EXPORT const CFStringRef kVTH264EntropyMode_CAVLC __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
VT_EXPORT const CFStringRef kVTH264EntropyMode_CABAC __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0);
	

/*!
	@constant	kVTCompressionPropertyKey_Depth
	@abstract
		The pixel depth of the encoded video.
	@discussion
		This property is only supported by video encoders for formats that are 
		tied to particular pixel formats (eg, 16-bit RGB, 24-bit RGB).
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_Depth __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFNumber (CMPixelFormatType), Optional

#pragma mark Runtime restrictions

/*!
	@constant	kVTCompressionPropertyKey_MaxFrameDelayCount
	@abstract
		The maximum frame delay count is the maximum number of frames that
		a compressor is allowed to hold before it must output a compressed
		frame.
	@discussion
		It limits the number of frames that may be held in the
		"compression window". If the maximum frame delay count is M, then
		before the call to encode frame N returns, frame N-M must have
		been emitted. 
		The default is kVTUnlimitedFrameDelayCount, which sets no limit
		on the compression window.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaxFrameDelayCount __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFNumber, Optional
enum { kVTUnlimitedFrameDelayCount = -1 };
	
/*!
	@constant	kVTCompressionPropertyKey_MaxH264SliceBytes
	@abstract
		Specifies the maximum slice size for H.264 encoding
	@discussion
		If supported by an H.264 encoder, the value limits the size in bytes of 
		slices produced by the encoder, where possible.
		By default, no limit is specified.  A value of zero implies default behavior.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaxH264SliceBytes __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFNumber<SInt32>, Optional

/*!
	@constant	kVTCompressionPropertyKey_RealTime
	@abstract
		Hints the video encoder that compression is, or is not, being performed in real time.
	@discussion
		For offline compression, clients may set this property to kCFBooleanFalse, which indicates that 
		it is OK for the video encoder to work slower than real time in order to produce a better result.
		For real-time compression, clients may set this property to kCFBooleanTrue to recommend that encoding stay timely.
		By default, this property is NULL, indicating unknown.  
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_RealTime __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0); // Read/write, CFBoolean or NULL, Optional, default NULL


#pragma mark Hints

/*!
	@constant	kVTCompressionPropertyKey_SourceFrameCount
	@abstract
		Indicates the number of source frames, if known.
	@discussion
		This property allows a client to give the video encoder advance guidance as to how 
		many frames will be encoded.
		If nonzero, this should be the exact number of times that the client calls
		VTCompressionSessionEncodeFrame in each pass. 
		The default is 0, which indicates that the number of source frames
		is not known.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_SourceFrameCount __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFNumber, Optional

/*!
	@constant	kVTCompressionPropertyKey_ExpectedFrameRate
	@abstract
		Indicates the expected frame rate, if known.
	@discussion
		The frame rate is measured in frames per second. 
		This is not used to control the frame rate; it is provided as a hint to the 
		video encoder so that it can set up internal configuration before compression begins. 
		The actual frame rate will depend on frame durations and may vary. 
		By default, this is zero, indicating "unknown".
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ExpectedFrameRate __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFNumber, Optional

/*!
	@constant	kVTCompressionPropertyKey_ExpectedDuration
	@abstract
		Indicates the expected total duration for the compression session, if known.
	@discussion
		By default, this is zero, indicating "unknown".
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ExpectedDuration __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFNumber(seconds), Optional


#pragma mark Hardware acceleration
// hardware acceleration is default behavior on iOS.  no opt-in required.
#if !TARGET_OS_IPHONE
/*!
	@constant	kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder
	@abstract
		If set to kCFBooleanTrue, use a hardware accelerated video encoder if available.  If set to
		kCFBooleanFalse, hardware encode will never be used.
	@discussion
		This key is set in the encoderSpecification passed in to VTCompressionSessionCreate.  Set it
		to kCFBooleanTrue to allow hardware accelerated encode.  To specifically prevent hardware encode,
		this property can be set to kCFBooleanFalse.
		This is useful for clients doing realtime encode operations to allow the VideoToolbox
		to choose the optimal encode path.
*/
VT_EXPORT const CFStringRef kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0); // CFBoolean, Optional

/*!
	@constant	kVTVideoEncoderSpecification_RequireHardwareAcceleratedVideoEncoder
	@abstract
		If set to kCFBooleanTrue, only use hardware encode and return an error if this isn't possible.
		Setting this key automatically implies kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder -- 
		there is no need to set both and the Enable key does nothing if the Require key is set.
	@discussion
		This key is set in the encoderSpecification passed in to VTCompressionSessionCreate.  Set it
		to kCFBooleanTrue to require hardware accelerated encode.  If hardware acceleration is not
		possible, the VTCompressionSessionCreate call will fail.
		This key is useful for clients that have their own software encode implementation or
		those that may want to configure software and hardware encode sessions differently.
		Hardware acceleration may be unavailable for a number of reasons.  A few common cases are:
			- the machine does not have hardware acceleration capabilities
			- the requested encoding format or encoding configuration is not supported
			- the hardware encoding resources on the machine are busy
*/
VT_EXPORT const CFStringRef kVTVideoEncoderSpecification_RequireHardwareAcceleratedVideoEncoder __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0); // CFBoolean, Optional

/*!
	@constant	kVTCompressionPropertyKey_UsingHardwareAcceleratedVideoEncoder
	@abstract
		If set to kCFBooleanTrue, a hardware accelerated video encoder is being used.
	@discussion
		You can query this property using VTSessionCopyProperty after you have enabled hardware
		accelerated encode using kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder
		to see if a hardware accelerated encoder was selected.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_UsingHardwareAcceleratedVideoEncoder __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_8_0); // CFBoolean, Read; assumed false by default
#endif // !TARGET_OS_IPHONE
	
#pragma mark Per-frame configuration
	
/*!
	@constant	kVTEncodeFrameOptionKey_ForceKeyFrame
	@abstract
		CFBoolean forcing the current frame to be a key frame
	@discussion
		This value is set in the frameProperties CFDictionary passed to 
		VTCompressionSessionEncodeFrame to force the current frame to be a 
		keyframe or not.  
		Note that it may not be possible for the encoder to accomodate all
		requests.
*/
VT_EXPORT const CFStringRef kVTEncodeFrameOptionKey_ForceKeyFrame __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); //  CFBoolean


#pragma mark Clean aperture and pixel aspect ratio

/*!
	@constant	kVTCompressionPropertyKey_CleanAperture
	@abstract
		Describes the clean aperture for encoded frames.
	@discussion
		Some video encoders may enforce specific clean apertures; 
		in those cases this property will be read-only (SetProperty will return kVTPropertyReadOnlyErr).
		The clean aperture will be set on the format description for output samples,
		and may affect source frame scaling.
		NULL is a valid value for this property, meaning that the clean aperture is the full width and height.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_CleanAperture __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFDictionary (see CMFormatDescription.h), Optional

/*!
	@constant	kVTCompressionPropertyKey_PixelAspectRatio
	@abstract
		Describes the pixel aspect ratio for encoded frames.
	@discussion
		Some video encoders may enforce specific pixel aspect ratios; 
		in those cases this property will be read-only (SetProperty will return kVTPropertyReadOnlyErr).
		The pixel aspect ratio will be set on the format description for output samples,
		and may affect source frame scaling.
		NULL is a valid value for this property, meaning square pixels (1:1).
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_PixelAspectRatio __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFDictionary (see CMFormatDescription.h), Optional

/*!
	@constant	kVTCompressionPropertyKey_FieldCount
	@abstract
		Indicates whether the frames should be encoded progressive (1) or interlaced (2).
	@discussion
		The field count will be set on the format description for output samples,
		and may affect source frame scaling.
		NULL is a valid value for this property.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_FieldCount __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFNumber (see kCMFormatDescriptionExtension_FieldCount), Optional

/*!
	@constant	kVTCompressionPropertyKey_FieldDetail
	@abstract
		Indicates field ordering for encoded interlaced frames.
	@discussion
		Some video encoders may enforce specific field ordering; 
		in those cases this property will be read-only (SetProperty will return kVTPropertyReadOnlyErr).
		The field detail will be set on the format description for output samples,
		and may affect source frame scaling.
		NULL is a valid value for this property.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_FieldDetail __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFString (see kCMFormatDescriptionExtension_FieldDetail), Optional

/*!
	@constant	kVTCompressionPropertyKey_AspectRatio16x9
	@abstract
		Indicates that the DV video stream should have the 16x9 flag set.
	@discussion
		This property is supported by the DV25/50 family of encoders.
		When false, the picture aspect ratio is 4:3.  
		When true, the picture aspect ratio is 16:9.
		Either way, a fixed PixelAspectRatio is used (the specific value depends on whether the format is NTSC or PAL).
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AspectRatio16x9 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFBoolean, Optional

/*!
	@constant	kVTCompressionPropertyKey_ProgressiveScan
	@abstract
		Indicates that the DV video stream should have the progressive flag set.
	@discussion
		This property is supported by the DV25/50 family of encoders.
		If false, content is encoded as interlaced.
		If true, content is encoded as progressive.
		The value of this property fixes the FieldCount and FieldDetail properties.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ProgressiveScan __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFBoolean, Optional

#pragma mark Color

/*!
	@constant	kVTCompressionPropertyKey_ColorPrimaries
	@abstract
		Indicates color primaries for compressed content.
	@discussion
		Some video encoders may enforce specific colorimetry; 
		in those cases this property will be read-only (SetProperty will return kVTPropertyReadOnlyErr).
		The value will be set on the format description for output sample buffers.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ColorPrimaries __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFString (see kCMFormatDescriptionExtension_ColorPrimaries), Optional

/*!
	@constant	kVTCompressionPropertyKey_TransferFunction
	@abstract
		Indicates transfer function for compressed content.
	@discussion
		Some video encoders may enforce specific colorimetry; 
		in those cases this property will be read-only (SetProperty will return kVTPropertyReadOnlyErr).
		The value will be set on the format description for output sample buffers.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_TransferFunction __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFString (see kCMFormatDescriptionExtension_TransferFunction), Optional

/*!
	@constant	kVTCompressionPropertyKey_YCbCrMatrix
	@abstract
		Indicates YCbCr matrix for compressed content.
	@discussion
		Some video encoders may enforce specific colorimetry; 
		in those cases this property will be read-only (SetProperty will return kVTPropertyReadOnlyErr).
		The value will be set on the format description for output sample buffers.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_YCbCrMatrix __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFString (see kCMFormatDescriptionExtension_YCbCrMatrix), Optional

/*!
	@constant	kVTCompressionPropertyKey_ICCProfile
	@abstract
		Indicates ICC profile for compressed content.
	@discussion
		Some video encoders may enforce specific colorimetry; 
		in those cases this property will be read-only (SetProperty will return kVTPropertyReadOnlyErr).
		If this property and any of the previous three are all set, they should be set to consistent values, 
		or undefined behavior may occur.
		The value will be set on the format description for output sample buffers.
		NULL can be a valid value for this property.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ICCProfile __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/write, CFData (see kCMFormatDescriptionExtension_ICCProfile), Optional

#pragma mark Pre-compression processing

// Standard properties about processing to be performed before compression.
// These are implemented by the video toolbox.

/*!
	@constant	kVTCompressionPropertyKey_PixelTransferProperties
	@abstract
		Specifies properties to configure a VTPixelTransferSession used to transfer source frames
		from the client's image buffers to the video encoder's image buffers, if necessary.
	@discussion
		Setting this property alone does not necessarily guarantee that a VTPixelTransferSession will be created.
		See VTPixelTransferProperties.h.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_PixelTransferProperties __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_8_0); // Read/Write, CFDictionary containing properties from VTPixelTransferProperties.h.
	
#pragma mark Multi-pass
	
/*!
	@const		kVTCompressionPropertyKey_MultiPassStorage
	@abstract	Enables multi-pass compression and provides storage for encoder-private data.
	@discussion
	Some video encoders support multi-pass encoding.  To determine whether a VTCompressionSession supports multi-pass encoding, you can inspect the dictionary returned by VTSessionCopySupportedPropertyDictionary to see if it contains kVTCompressionPropertyKey_MultiPassStorage.
	 
	To enable multi-pass encoding, set the kVTCompressionPropertyKey_MultiPassStorage property to a VTMultiPassStorage object, which you can create by calling VTMultiPassStorageCreate.  Then make one or more passes over the source frames.  Bracket each pass with a call to VTCompressionSessionBeginPass at the beginning and VTCompressionSessionEndPass at the end.
	 
	In the first pass of multi-pass encoding, call VTCompressionSessionEncodeFrame for every source frame (just as in single-pass encoding).  At the end of every pass, call VTCompressionSessionEndPass.  This may take some time as the video encoder determines whether it can improve the encoding by performing another pass.  If the user cancels encoding during this time, call VTCompressionSessionInvalidate to interrupt the processing.  VTCompressionSessionEndPass will indicate via the furtherPassesRequestedOut argument whether the video encoder would like to perform another pass.  There is no particular bound on the number of passes the video encoder may request, but the client is free to disregard this request and use the last-emitted set of frames.
	 
	If *furtherPassesRequestedOut is set to true and you want to perform another pass, call VTCompressionSessionGetTimeRangesForNextPass to determine the time ranges for the next pass.  Only the source frames within these time ranges need to be passed to VTCompressionSessionEncodeFrame; the video encoder is satisfied with the already-emitted compressed frames outside these ranges and they can be kept for the final output.
	 
	In second and successive passes, you must pass identical source frames, frame properties and timestamps to VTCompressionSessionEncodeFrame as in the first pass, with the exception that frames not in the requested time ranges should be skipped.
	 
	You can create and use a VTFrameSilo object to merge sequences of compressed frames across passes during multi-pass encoding.
*/
VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MultiPassStorage __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0); // VTMultiPassStorage, optional, default is NULL

	
CM_ASSUME_NONNULL_END

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // VTCOMPRESSIONPROPERTIES_H
// ==========  VideoToolbox.framework/Headers/VTFrameSilo.h
/*
	File:  VTFrameSilo.h
	
	Framework:  VideoToolbox
	
	Copyright 2012-2013 Apple Inc. All rights reserved.
	
	A VTFrameSilo stores a large number of sample buffers, as produced by a multi-pass compression session.
*/

#ifndef VTFRAMESILO_H
#define VTFRAMESILO_H

#include <CoreMedia/CMBase.h>
#include <CoreMedia/CMTimeRange.h>
#include <CoreMedia/CMSampleBuffer.h>

#include <VideoToolbox/VTErrors.h>

#include <CoreFoundation/CoreFoundation.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)    

CF_IMPLICIT_BRIDGING_ENABLED
/*!
	@typedef	VTFrameSilo
	@abstract	A VTFrameSilo stores a large number of sample buffers, as produced by a multi-pass compression session.
	@discussion
		The sample buffers are ordered by decode timestamp. 
		A VTFrameSilo starts out empty and is populated by calls to VTFrameSiloAddSampleBuffer to add sample buffers in ascending decode order.
		After the first full pass, additional passes may be performed to replace sample buffers.
		Each such pass must begin with a call to VTFrameSiloSetTimeRangesForNextPass, which takes a list of time ranges.
		Samples in these time ranges are deleted, and calls to VTFrameSiloAddSampleBuffer can then be made to provide replacements.
		Call VTFrameSiloCallFunctionForEachSampleBuffer or VTFrameSiloCallBlockForEachSampleBuffer to retrieve sample buffers.
		The VTFrameSilo may write sample buffers and data to the backing file between addition and retrieval; 
		do not expect to get identical object pointers back.
*/

typedef struct CM_BRIDGED_TYPE(id) OpaqueVTFrameSilo *VTFrameSiloRef; // a CF type, call CFRetain and CFRelease

VT_EXPORT CFTypeID VTFrameSiloGetTypeID(void) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

CF_IMPLICIT_BRIDGING_DISABLED
/*!
	@function	VTFrameSiloCreate
	@abstract	Creates a VTFrameSilo object using a temporary file.
	@discussion
		The returned VTFrameSilo object may be used to gather frames produced by multi-pass encoding.
	@param fileURL
		Specifies where to put the backing file for the VTFrameSilo object.
		If you pass NULL for fileURL, the video toolbox will pick a unique temporary file name.
	@param options
		Reserved, pass NULL.
	@param timeRange
		The valid time range for the frame silo. Must be valid for progress reporting.
	@param siloOut
		Points to a VTFrameSiloRef to receive the newly created object.
		Call CFRelease to release your retain on the created VTFrameSilo object when you are done with it.
*/
VT_EXPORT OSStatus
VTFrameSiloCreate( 
	CM_NULLABLE CFAllocatorRef				allocator,
	CM_NULLABLE CFURLRef					fileURL,
	CMTimeRange								timeRange, /* can be kCMTimeRangeInvalid */
	CM_NULLABLE CFDictionaryRef				options,
	CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE VTFrameSiloRef * CM_NONNULL siloOut ) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@function	VTFrameSiloAddSampleBuffer
	@abstract	Adds a sample buffer to a VTFrameSilo object.
	@discussion
		Within each pass, sample buffers must have strictly increasing decode timestamps.
		Passes after the first pass are begun with a call to VTFrameSiloSetTimeRangesForNextPass.
		After a call to VTFrameSiloSetTimeRangesForNextPass, sample buffer decode timestamps must also be within 
		the stated time ranges.
		Note that CMTimeRanges are considered to contain their start times but not their end times.
	@return
		Returns kVTFrameSiloInvalidTimeStampErr if an attempt is made to add a sample buffer with an inappropriate decode timestamp.
*/
VT_EXPORT OSStatus
VTFrameSiloAddSampleBuffer( 
	CM_NONNULL VTFrameSiloRef			silo,
	CM_NONNULL CMSampleBufferRef		sampleBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	VTFrameSiloSetTimeRangesForNextPass
	@abstract	Begins a new pass of samples to be added to a VTFrameSilo object.
	@discussion
		Previously-added sample buffers with decode timestamps within the time ranges will be deleted from the VTFrameSilo.
		It is not necessary to call VTFrameSiloSetTimeRangesForNextPass before adding the first pass' sample buffers.
	@return
		Returns kVTFrameSiloInvalidTimeRangeErr if any time ranges are non-numeric, overlap or are not in ascending order.
*/
VT_EXPORT OSStatus
VTFrameSiloSetTimeRangesForNextPass( 
	CM_NONNULL VTFrameSiloRef		silo,
	CMItemCount						timeRangeCount,
	const CMTimeRange * CM_NONNULL	timeRangeArray ) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	VTFrameSiloGetProgressOfCurrentPass
	@abstract	Gets the progress of the current pass.
	@discussion
		Calculates the current progress based on the most recent sample buffer added and the current pass time ranges.
	@return
		Returns kVTFrameSiloInvalidTimeRangeErr if any time ranges are non-numeric, overlap or are not in ascending order.
*/
VT_EXPORT OSStatus
VTFrameSiloGetProgressOfCurrentPass(
	CM_NONNULL VTFrameSiloRef	silo,
	Float32 * CM_NONNULL		progressOut ) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	VTFrameSiloCallFunctionForEachSampleBuffer
	@abstract	Retrieves sample buffers from a VTFrameSilo object.
	@discussion
		You call this function to retrieve sample buffers at the end of a multi-pass compression session.
	@param timeRange
		The decode time range of sample buffers to retrieve.
		Pass kCMTimeRangeInvalid to retrieve all sample buffers from the VTFrameSilo.
	@param callback
		A function to be called, in decode order, with each sample buffer that was added.
		To abort iteration early, return a nonzero status.
		The VTFrameSilo may write sample buffers and data to the backing file between addition and retrieval; 
		do not expect to get identical object pointers back.
	@return
		Returns kVTFrameSiloInvalidTimeRangeErr if any time ranges are non-numeric, overlap or are not in ascending order.
		Returns any nonzero status returned by the callback function.
*/
VT_EXPORT OSStatus
VTFrameSiloCallFunctionForEachSampleBuffer( 
	CM_NONNULL VTFrameSiloRef	silo,
	CMTimeRange					timeRange,
	void * CM_NULLABLE			callbackInfo,
	OSStatus	(* CM_NONNULL callback)( void * CM_NULLABLE callbackInfo, CM_NONNULL CMSampleBufferRef sampleBuffer ) ) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0); // return nonzero to abort iteration

#if __BLOCKS__
/*!
	@function	VTFrameSiloCallBlockForEachSampleBuffer
	@abstract	Retrieves sample buffers from a VTFrameSilo object.
	@discussion
		You call this function to retrieve sample buffers at the end of a multi-pass compression session.
	@param timeRange
		The decode time range of sample buffers to retrieve.
		Pass kCMTimeRangeInvalid to retrieve all sample buffers from the VTFrameSilo.
	@param handler
		A block to be called, in decode order, with each sample buffer that was added.
		To abort iteration early, return a nonzero status.
		The VTFrameSilo may write sample buffers and data to the backing file between addition and retrieval; 
		do not expect to get identical object pointers back.
	@return
		Returns kVTFrameSiloInvalidTimeRangeErr if any time ranges are non-numeric, overlap or are not in ascending order.
		Returns any nonzero status returned by the handler block.
*/
VT_EXPORT OSStatus
VTFrameSiloCallBlockForEachSampleBuffer( 
	CM_NONNULL VTFrameSiloRef			silo,
	CMTimeRange							timeRange,
	OSStatus (^ CM_NONNULL handler)( CM_NONNULL CMSampleBufferRef sampleBuffer ) ) __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0); // return nonzero to abort iteration
#endif // __BLOCKS__

CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // VTFRAMESILO_H
// ==========  VideoToolbox.framework/Headers/VTPixelTransferProperties.h
/*
	File:  VTPixelTransferProperties.h
	
	Framework:  VideoToolbox
 
    Copyright 2006-2013 Apple Inc. All rights reserved.
  
	Standard Video Toolbox pixel transfer properties.
*/

#ifndef VTPIXELTRANSFERPROPERTIES_H
#define VTPIXELTRANSFERPROPERTIES_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>

#include <CoreFoundation/CoreFoundation.h>

#ifndef VT_SUPPORT_COLORSYNC_PIXEL_TRANSFER
#define VT_SUPPORT_COLORSYNC_PIXEL_TRANSFER ( TARGET_OS_MAC && ! TARGET_OS_IPHONE && ( MAC_OS_X_VERSION_MIN_REQUIRED >= 1080 ) )
#endif // VT_SUPPORT_COLORSYNC_PIXEL_TRANSFER

#if defined(__cplusplus)
extern "C"
{
#endif

#pragma pack(push, 4)
	
CM_ASSUME_NONNULL_BEGIN
    
/*!
	@header
	@abstract
		Standard Video Toolbox pixel transfer properties
		
	@discussion
		This file defines standard properties used to describe and configure pixel transfer 
		operations managed by the video toolbox.  
		
		Clients can query supported properties by calling VTSessionCopySupportedPropertyDictionary.
*/

// Properties for various scaling and cropping configurations

/*!
	@constant	kVTPixelTransferPropertyKey_ScalingMode
	@abstract
		Indicates how images should be scaled.
	@discussion
		Depending on the scaling mode, scaling may take into account:
		the full image buffer width and height of the source and destination, 
		the clean aperture attachment (kCVImageBufferCleanApertureKey) on the source image buffer, 
		the pixel aspect ratio attachment (kCVImageBufferPixelAspectRatioKey) on the source image buffer,
		the destination clean aperture (kVTPixelTransferPropertyKey_DestinationCleanAperture), and/or
		the destination pixel aspect ratio (kVTPixelTransferPropertyKey_DestinationPixelAspectRatio).
		The destination image buffer's clean aperture and pixel aspect ratio attachments are not
		taken into account, and will be overwritten.
	
	@constant	kVTScalingMode_Normal
	@abstract
		The full width and height of the source image buffer is stretched to the full width 
		and height of the destination image buffer.
	@discussion
		The source image buffer's clean aperture and pixel aspect ratio attachments are stretched 
		the same way as the image with the image, and attached to the destination image buffer.
		This is the default scaling mode.
	
	@constant	kVTScalingMode_CropSourceToCleanAperture
	@abstract
		The source image buffer's clean aperture is scaled to the destination clean aperture.
	@discussion
		The destination pixel aspect ratio is set on the destination image buffer.
	
	@constant	kVTScalingMode_Letterbox
	@abstract
		The source image buffer's clean aperture is scaled to a rectangle fitted inside the 
		destination clean aperture that preserves the source picture aspect ratio.
	@discussion
		The remainder of the destination image buffer is filled with black.
		If a destination pixel aspect ratio is not set, the source image's pixel aspect ratio is used.
		The pixel aspect ratio used is set on the destination image buffer.
	
	@constant	kVTScalingMode_Trim
	@abstract
		The source image buffer's clean aperture is scaled to a rectangle that completely fills the 
		destination clean aperture and preserves the source picture aspect ratio.
	@discussion
		If a destination pixel aspect ratio is not set, the source image's pixel aspect ratio is used.
		The pixel aspect ratio used is set on the destination image buffer.
*/
VT_EXPORT const CFStringRef kVTPixelTransferPropertyKey_ScalingMode __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_9_0); // Read/write, CFStringRef, one of:
VT_EXPORT const CFStringRef kVTScalingMode_Normal __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_9_0); // Copy full width and height.  Write adjusted clean aperture and pixel aspect ratios to compensate for any change in dimensions.
VT_EXPORT const CFStringRef kVTScalingMode_CropSourceToCleanAperture __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_9_0); // Crop to remove edge processing region; scale remainder to destination clean aperture.
VT_EXPORT const CFStringRef kVTScalingMode_Letterbox __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_9_0); // Preserve aspect ratio of the source, and fill remaining areas with black in to fit destination dimensions
VT_EXPORT const CFStringRef kVTScalingMode_Trim __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_9_0); // Preserve aspect ratio of the source, and crop picture to fit destination dimensions

/*!
	@constant	kVTPixelTransferPropertyKey_DestinationCleanAperture
	@abstract
		Specifies the clean aperture for destination image buffers.  
	@discussion
		The value of this property is a CFDictionary with same keys as used in the 
		kCVImageBufferCleanApertureKey dictionary.  
		This property is ignored in kVTScalingMode_Normal.  
		This property defaults to NULL, meaning the clean aperture is the full width and height.
*/
VT_EXPORT const CFStringRef kVTPixelTransferPropertyKey_DestinationCleanAperture __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_9_0); // Read/write, CFDictionary with same keys as used in kCVImageBufferCleanApertureKey dictionary.  Used as applicable to current kVTPixelTransferPropertyKey_ScalingMode value.

/*!
	@constant	kVTPixelTransferPropertyKey_DestinationPixelAspectRatio
	@abstract
		Specifies the pixel aspect ratio for destination image buffers.  
	@discussion
		The value of this property is a CFDictionary with same keys as used in the
		kCVImageBufferPixelAspectRatioKey dictionary.
		This property is ignored in kVTScalingMode_Normal.  
		This property defaults to NULL, meaning 1:1 (for kVTScalingMode_CropSourceToCleanAperture) 
		or no change in pixel aspect ratio (for kVTScalingMode_Letterbox and kVTScalingMode_Trim).
*/
VT_EXPORT const CFStringRef kVTPixelTransferPropertyKey_DestinationPixelAspectRatio __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_9_0); // Read/write, CFDictionary with same keys as used in kCVImageBufferPixelAspectRatioKey dictionary.  Used as applicable to current kVTPixelTransferPropertyKey_ScalingMode value.

// Properties for configuring up/down sampling

/*!
	@constant	kVTPixelTransferPropertyKey_DownsamplingMode
	@abstract
		Requests a specific chroma downsampling technique be used.
	@discussion
		This property is ignored if chroma downsampling is not performed.
*/
VT_EXPORT const CFStringRef kVTPixelTransferPropertyKey_DownsamplingMode __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_9_0); // Read/write, CFStringRef, one of:
VT_EXPORT const CFStringRef kVTDownsamplingMode_Decimate __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_9_0); // Default, decimate extra samples
VT_EXPORT const CFStringRef kVTDownsamplingMode_Average __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_9_0); // Average missing samples (default center)

// Properties for color information

#if VT_SUPPORT_COLORSYNC_PIXEL_TRANSFER

/*!
	@constant	kVTPixelTransferPropertyKey_DestinationColorPrimaries
	@abstract
		Specifies the color primaries to be used for destination image buffers.  
	@discussion
		Specifying this value may lead to performance degradation, as a color
		matching operation may need to be performed between the source and
		the destination.
*/
VT_EXPORT const CFStringRef kVTPixelTransferPropertyKey_DestinationColorPrimaries __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_9_0); // Read/write, CFString (see kCMFormatDescriptionExtension_ColorPrimaries), Optional

/*!
	@constant	kVTPixelTransferPropertyKey_DestinationTransferFunction
	@abstract
		Specifies the color transfer function to be used for destination image buffers.  
	@discussion
		Specifying this value may lead to performance degradation, as a color
		matching operation may need to be performed between the source and
		the destination.
*/
VT_EXPORT const CFStringRef kVTPixelTransferPropertyKey_DestinationTransferFunction __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_9_0); // Read/write, CFString (see kCMFormatDescriptionExtension_TransferFunction), Optional

/*!
	@constant	kVTPixelTransferPropertyKey_DestinationICCProfile
	@abstract
		Specifies the ICC profile for destination image buffers.  
	@discussion
		Specifying this value may lead to performance degradation, as a color
		matching operation may need to be performed between the source and
		the destination.
*/
VT_EXPORT const CFStringRef kVTPixelTransferPropertyKey_DestinationICCProfile __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_9_0); // Read/write, CFData (see kCMFormatDescriptionExtension_ICCProfile), Optional

#endif // VT_SUPPORT_COLORSYNC_PIXEL_TRANSFER
    
/*!
	@constant	kVTPixelTransferPropertyKey_DestinationYCbCrMatrix
	@abstract
		Specifies the color matrix to be used for YCbCr->RGB conversions
		involving the destination image buffers.
	@discussion
		Specifying this value may lead to performance degradation, as a color
		matching operation may need to be performed between the source and
		the destination.
*/
VT_EXPORT const CFStringRef kVTPixelTransferPropertyKey_DestinationYCbCrMatrix __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_9_0); // Read/write, CFString (see kCMFormatDescriptionExtension_YCbCrMatrix), Optional

	
CM_ASSUME_NONNULL_END

#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // VTPIXELTRANSFERPROPERTIES_H
