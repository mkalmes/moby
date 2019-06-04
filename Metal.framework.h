// ==========  Metal.framework/Headers/MTLCaptureScope.h
//
//  MTLCaptureScope.h
//  Metal
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>


NS_ASSUME_NONNULL_BEGIN

@protocol MTLDevice;
@protocol MTLCommandQueue;

API_AVAILABLE(macos(10.13), ios(11.0))
@protocol MTLCaptureScope <NSObject>

// Remarks: only MTLCommandBuffers created after -[beginScope] and committed before -[endScope] are captured.

// Marks the begin of the capture scope. Note: This method should be invoked repeatedly per frame.
- (void)beginScope;
// Marks the end of the capture scope. Note: This method should be invoked repeatedly per frame.
- (void)endScope;

/** Scope label
    @remarks Created capture scopes are listed in Xcode when long-pressing the capture button, performing the capture over the selected scope
  */
@property (nullable, copy, atomic) NSString *label;

// Associated device: this scope will capture Metal commands from the associated device
@property (nonnull, readonly, nonatomic)  id<MTLDevice> device;
/** If set, this scope will only capture Metal commands from the associated command queue. Defaults to nil (all command queues from the associated device are captured).
 */
@property (nullable, readonly, nonatomic) id<MTLCommandQueue> commandQueue;

@end

NS_ASSUME_NONNULL_END

// ==========  Metal.framework/Headers/MTLDrawable.h
//
//  MTLDrawable.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLDrawable;

/*!
 @typedef MTLDrawablePresentedHandler
 @abstract The presented callback function protocol
 @disucssion Be careful when you use delta between this presentedTime and previous frame's presentedTime to animate next frame. If the frame was presented using presentAfterMinimumDuration or presentAtTime, the presentedTime might includes delays to meet your specified present time. If you want to measure how much frame you can achieve, use GPUStartTime in the first command buffer of your frame rendering and GPUEndTime of your last frame rendering to calculate the frame interval.
*/
typedef void (^MTLDrawablePresentedHandler)(id<MTLDrawable>);

/*!
 @protocol MTLDrawable
 @abstract All "drawable" objects (such as those coming from CAMetalLayer) are expected to conform to this protocol
 */
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLDrawable <NSObject>

/* Present this drawable as soon as possible */
- (void)present;

/* Present this drawable at the given host time */
- (void)presentAtTime:(CFTimeInterval)presentationTime;

/*!
 @method presentAfterMinimumDuration
 @abstract Present this drawable while setting a minimum duration in seconds before allowing this drawable to appear on the display.
 @param duration Duration in seconds before this drawable is allowed to appear on the display
 */
- (void)presentAfterMinimumDuration:(CFTimeInterval)duration API_AVAILABLE(ios(10.3)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @method addPresentedHandler
 @abstract Add a block to be called when this drawable is presented on screen.
 */
- (void)addPresentedHandler:(MTLDrawablePresentedHandler)block API_AVAILABLE(ios(10.3)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @property presentedTime
 @abstract The host time that this drawable was presented on screen.
 @discussion Returns 0 if a frame has not been presented or has been skipped.
 */
@property(nonatomic, readonly) CFTimeInterval presentedTime API_AVAILABLE(ios(10.3)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @property drawableID
 @abstract The monotonically incremented ID for all MTLDrawable objects created from the same CAMetalLayer object.
  @discussion The value starts from 0.
*/
@property (nonatomic, readonly) NSUInteger drawableID API_AVAILABLE(ios(10.3)) API_UNAVAILABLE(macos, uikitformac);

@end
NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLCommandEncoder.h
//
//  MTLCommandEncoder.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLDevice;

/*!
 * @brief Describes how a resource will be used by a shader through an argument buffer
 */
typedef NS_OPTIONS(NSUInteger, MTLResourceUsage)
{
	MTLResourceUsageRead   = 1 << 0,
	MTLResourceUsageWrite  = 1 << 1,
	MTLResourceUsageSample = 1 << 2
} API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 * @brief Describes the types of resources that the a barrier operates on
 */
typedef NS_OPTIONS(NSUInteger, MTLBarrierScope)
{
    MTLBarrierScopeBuffers = 1 << 0,
    MTLBarrierScopeTextures = 1 << 1,
    MTLBarrierScopeRenderTargets API_AVAILABLE(macos(10.14), uikitformac(13.0)) API_UNAVAILABLE(ios) = 1 << 2,
} API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @protocol MTLCommandEncoder
 @abstract MTLCommandEncoder is the common interface for objects that write commands into MTLCommandBuffers.
 */
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLCommandEncoder <NSObject>

/*!
 @property device
 @abstract The device this resource was created against.
 */
@property (readonly) id <MTLDevice> device;

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, copy, atomic) NSString *label;

/*!
 @method endEncoding
 @abstract Declare that all command generation from this encoder is complete, and detach from the MTLCommandBuffer.
 */
- (void)endEncoding;

/* Debug Support */

/*!
 @method insertDebugSignpost:
 @abstract Inserts a debug string into the command buffer.  This does not change any API behavior, but can be useful when debugging.
 */
- (void)insertDebugSignpost:(NSString *)string;

/*!
 @method pushDebugGroup:
 @abstract Push a new named string onto a stack of string labels.
 */
- (void)pushDebugGroup:(NSString *)string;

/*!
 @method popDebugGroup
 @abstract Pop the latest named string off of the stack.
*/
- (void)popDebugGroup;

@end
NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLTexture.h
//
//  MTLTexture.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLResource.h>
#import <Metal/MTLBuffer.h>
#import <Metal/MTLTypes.h>


#import <IOSurface/IOSurfaceRef.h>


NS_ASSUME_NONNULL_BEGIN
/*!
 @enum MTLTextureType
 @abstract MTLTextureType describes the dimensionality of each image, and if multiple images are arranged into an array or cube.
 */
typedef NS_ENUM(NSUInteger, MTLTextureType)
{
    MTLTextureType1D = 0,
    MTLTextureType1DArray = 1,
    MTLTextureType2D = 2,
    MTLTextureType2DArray = 3,
    MTLTextureType2DMultisample = 4,
    MTLTextureTypeCube = 5,
    MTLTextureTypeCubeArray API_AVAILABLE(macos(10.11), ios(11.0)) = 6,
    MTLTextureType3D = 7,
    MTLTextureType2DMultisampleArray API_AVAILABLE(macos(10.14)) API_UNAVAILABLE(ios) = 8,
    MTLTextureTypeTextureBuffer API_AVAILABLE(macos(10.14), ios(12.0)) = 9
} API_AVAILABLE(macos(10.11), ios(8.0));


typedef NS_ENUM(uint8_t, MTLTextureSwizzle) {
    MTLTextureSwizzleZero = 0,
    MTLTextureSwizzleOne = 1,
    MTLTextureSwizzleRed = 2,
    MTLTextureSwizzleGreen = 3,
    MTLTextureSwizzleBlue = 4,
    MTLTextureSwizzleAlpha = 5,
} API_AVAILABLE(macos(10.15), ios(13.0));

typedef struct
{
    MTLTextureSwizzle red;
    MTLTextureSwizzle green;
    MTLTextureSwizzle blue;
    MTLTextureSwizzle alpha;
} MTLTextureSwizzleChannels API_AVAILABLE(macos(10.15), ios(13.0));

API_AVAILABLE(macos(10.15), ios(13.0)) NS_SWIFT_UNAVAILABLE("Use MTLTextureSwizzleChannels.init instead")
MTL_INLINE MTLTextureSwizzleChannels MTLTextureSwizzleChannelsMake(MTLTextureSwizzle r, MTLTextureSwizzle g, MTLTextureSwizzle b, MTLTextureSwizzle a)
{
    MTLTextureSwizzleChannels swizzle;
    swizzle.red = r;
    swizzle.green = g;
    swizzle.blue = b;
    swizzle.alpha = a;
    return swizzle;
}

#define MTLTextureSwizzleChannelsDefault (MTLTextureSwizzleChannelsMake(MTLTextureSwizzleRed, MTLTextureSwizzleGreen, MTLTextureSwizzleBlue, MTLTextureSwizzleAlpha))




MTL_EXPORT API_AVAILABLE(macos(10.14), ios(13.0))
@interface MTLSharedTextureHandle : NSObject <NSSecureCoding>
{
    struct MTLSharedTextureHandlePrivate *_priv;
}

/*!
 @property device
 @abstract The device this texture was created against.
 @discussion This shared texture handle can only be used with this device.
 */
@property (readonly) id <MTLDevice> device;

/*!
 @property label
 @abstract A copy of the original texture's label property, if any
*/
@property (readonly, nullable) NSString *label;

@end

/*!
 @enum MTLTextureUsage
 @abstract MTLTextureUsage declares how the texture will be used over its lifetime (bitwise OR for multiple uses).
 @discussion This information may be used by the driver to make optimization decisions.
*/
typedef NS_OPTIONS(NSUInteger, MTLTextureUsage)
{
    MTLTextureUsageUnknown         = 0x0000,
    MTLTextureUsageShaderRead      = 0x0001,
    MTLTextureUsageShaderWrite     = 0x0002,
    MTLTextureUsageRenderTarget    = 0x0004,
    MTLTextureUsagePixelFormatView = 0x0010,
} API_AVAILABLE(macos(10.11), ios(9.0));

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLTextureDescriptor : NSObject <NSCopying>

/*!
 @method texture2DDescriptorWithPixelFormat:width:height:mipmapped:
 @abstract Create a TextureDescriptor for a common 2D texture.
 */
+ (MTLTextureDescriptor*)texture2DDescriptorWithPixelFormat:(MTLPixelFormat)pixelFormat width:(NSUInteger)width height:(NSUInteger)height mipmapped:(BOOL)mipmapped;

/*!
 @method textureCubeDescriptorWithPixelFormat:size:mipmapped:
 @abstract Create a TextureDescriptor for a common Cube texture.
 */
+ (MTLTextureDescriptor*)textureCubeDescriptorWithPixelFormat:(MTLPixelFormat)pixelFormat size:(NSUInteger)size mipmapped:(BOOL)mipmapped;

/*!
 @method textureBufferDescriptorWithPixelFormat:width:resourceOptions:usage:
 @abstract Create a TextureDescriptor for a common texture buffer.
 */
+ (MTLTextureDescriptor*)textureBufferDescriptorWithPixelFormat:(MTLPixelFormat)pixelFormat
                                                          width:(NSUInteger)width
                                                resourceOptions:(MTLResourceOptions)resourceOptions
                                                          usage:(MTLTextureUsage)usage API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @property type
 @abstract The overall type of the texture to be created. The default value is MTLTextureType2D.
 */
@property (readwrite, nonatomic) MTLTextureType textureType;

/*!
 @property pixelFormat
 @abstract The pixel format to use when allocating this texture. This is also the pixel format that will be used to when the caller writes or reads pixels from this texture. The default value is MTLPixelFormatRGBA8Unorm.
 */
@property (readwrite, nonatomic) MTLPixelFormat pixelFormat;

/*!
 @property width
 @abstract The width of the texture to create. The default value is 1.
 */
@property (readwrite, nonatomic) NSUInteger width;

/*!
 @property height
 @abstract The height of the texture to create. The default value is 1.
 @discussion height If allocating a 1D texture, height must be 1.
 */
@property (readwrite, nonatomic) NSUInteger height;

/*!
 @property depth
 @abstract The depth of the texture to create. The default value is 1.
 @discussion depth When allocating any texture types other than 3D, depth must be 1.
 */
@property (readwrite, nonatomic) NSUInteger depth;

/*!
 @property mipmapLevelCount
 @abstract The number of mipmap levels to allocate. The default value is 1.
 @discussion When creating Buffer and Multisample textures, mipmapLevelCount must be 1.
 */
@property (readwrite, nonatomic) NSUInteger mipmapLevelCount;

/*!
 @property sampleCount
 @abstract The number of samples in the texture to create. The default value is 1.
 @discussion When creating Buffer textures sampleCount must be 1. Implementations may round sample counts up to the next supported value.
 */
@property (readwrite, nonatomic) NSUInteger sampleCount;

/*!
 @property arrayLength
 @abstract The number of array elements to allocate. The default value is 1.
 @discussion When allocating any non-Array texture type, arrayLength has to be 1. Otherwise it must be set to something greater than 1 and less than 2048.
 */
@property (readwrite, nonatomic) NSUInteger arrayLength;

/*!
 @property resourceOptions
 @abstract Options to control memory allocation parameters, etc.
 @discussion Contains a packed set of the storageMode, cpuCacheMode and hazardTrackingMode properties.
 */
@property (readwrite, nonatomic) MTLResourceOptions resourceOptions;

/*!
 @property cpuCacheMode
 @abstract Options to specify CPU cache mode of texture resource.
 */
@property (readwrite, nonatomic) MTLCPUCacheMode cpuCacheMode API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property storageMode
 @abstract To specify storage mode of texture resource.
 */
@property (readwrite, nonatomic) MTLStorageMode storageMode API_AVAILABLE(macos(10.11), ios(9.0));


/*!
 @property hazardTrackingMode
 @abstract Set hazard tracking mode for the texture. The default value is MTLHazardTrackingModeDefault.
 @discussion
 For resources created from the device, MTLHazardTrackingModeDefault is treated as MTLHazardTrackingModeTracked.
 For resources created on a heap, MTLHazardTrackingModeDefault is treated as the hazardTrackingMode of the heap itself.
 In either case, it is possible to opt-out of hazard tracking by setting MTLHazardTrackingModeUntracked.
 It is not possible to opt-in to hazard tracking on a heap that itself is not hazard tracked.
 For optimal performance, perform hazard tracking manually through MTLFence or MTLEvent instead.
 */
@property (readwrite, nonatomic) MTLHazardTrackingMode hazardTrackingMode API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @property usage
 @abstract Description of texture usage
 */
@property (readwrite, nonatomic) MTLTextureUsage usage API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property allowGPUOptimizedContents
 @abstract Allow GPU-optimization for the contents of this texture. The default value is true.
 @discussion Useful for opting-out of GPU-optimization when implicit optimization (e.g. RT writes) is regressing CPU-read-back performance. See the documentation for optimizeContentsForGPUAccess: and optimizeContentsForCPUAccess: APIs.
 */
@property (readwrite, nonatomic) BOOL allowGPUOptimizedContents API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @property swizzle
 @abstract Channel swizzle to use when reading or sampling from the texture, the default value is MTLTextureSwizzleChannelsDefault.
 */
@property (readwrite, nonatomic) MTLTextureSwizzleChannels swizzle API_AVAILABLE(macos(10.15), ios(13.0));

@end

/*!
 @protocol MTLTexture
 @abstract MTLTexture represents a collection of 1D, 2D, or 3D images.
 @discussion
 Each image in a texture is a 1D, 2D, 2DMultisample, or 3D image. The texture contains one or more images arranged in a mipmap stack. If there are multiple mipmap stacks, each one is referred to as a slice of the texture. 1D, 2D, 2DMultisample, and 3D textures have a single slice. In 1DArray and 2DArray textures, every slice is an array element. A Cube texture always has 6 slices, one for each face. In a CubeArray texture, each set of six slices is one element in the array.
 
 Most APIs that operate on individual images in a texture address those images via a tuple of a Slice, and Mipmap Level within that slice.
 */
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLTexture <MTLResource>

/*!
 @property rootResource
 @abstract The resource this texture was created from. It may be a texture or a buffer. If this texture is not reusing storage of another MTLResource, then nil is returned.
 */
@property (nullable, readonly) id <MTLResource> rootResource API_DEPRECATED("Use parentTexture or buffer instead", macos(10.11, 10.12), ios(8.0, 10.0));

/*!
 @property parentTexture
 @abstract The texture this texture view was created from, or nil if this is not a texture view or it was not created from a texture.
 */
@property (nullable, readonly) id <MTLTexture> parentTexture API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property parentRelativeLevel
 @abstract The base level of the texture this texture view was created from, or 0 if this is not a texture view.
 */
@property (readonly) NSUInteger parentRelativeLevel API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property parentRelativeSlice
 @abstract The base slice of the texture this texture view was created from, or 0 if this is not a texture view.
 */
@property (readonly) NSUInteger parentRelativeSlice API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property buffer
 @abstract The buffer this texture view was created from, or nil if this is not a texture view or it was not created from a buffer.
 */
@property (nullable, readonly) id <MTLBuffer> buffer API_AVAILABLE(macos(10.12), ios(9.0));

/*!
 @property bufferOffset
 @abstract The offset of the buffer this texture view was created from, or 0 if this is not a texture view.
 */
@property (readonly) NSUInteger bufferOffset API_AVAILABLE(macos(10.12), ios(9.0));

/*!
 @property bufferBytesPerRow
 @abstract The bytesPerRow of the buffer this texture view was created from, or 0 if this is not a texture view.
 */
@property (readonly) NSUInteger bufferBytesPerRow API_AVAILABLE(macos(10.12), ios(9.0));


/*!
 @property iosurface
 @abstract If this texture was created from an IOSurface, this returns a reference to that IOSurface. iosurface is nil if this texture was not created from an IOSurface.
 */
@property (nullable, readonly) IOSurfaceRef iosurface API_AVAILABLE(macos(10.11), ios(11.0));

/*!
 @property iosurfacePlane
 @abstract If this texture was created from an IOSurface, this returns the plane of the IOSurface from which the texture was created. iosurfacePlane is 0 if this texture was not created from an IOSurface.
 */
@property (readonly) NSUInteger iosurfacePlane API_AVAILABLE(macos(10.11), ios(11.0));

/*!
 @property type
 @abstract The type of this texture.
 */
@property (readonly) MTLTextureType textureType;

/*!
 @property pixelFormat
 @abstract The MTLPixelFormat that is used to interpret this texture's contents.
 */
@property (readonly) MTLPixelFormat pixelFormat;

/*!
 @property width
 @abstract The width of the MTLTexture instance in pixels.
 */
@property (readonly) NSUInteger width;

/*!
 @property height
 @abstract The height of the MTLTexture instance in pixels.
 @discussion. height is 1 if the texture is 1D.
 */
@property (readonly) NSUInteger height;

/*!
 @property depth
 @abstract The depth of this MTLTexture instance in pixels.
 @discussion If this MTLTexture is not a 3D texture, the depth is 1
 */
@property (readonly) NSUInteger depth;

/*!
 @property mipmapLevelCount
 @abstract The number of mipmap levels in each slice of this MTLTexture.
 */
@property (readonly) NSUInteger mipmapLevelCount;

/*!
 @property sampleCount
 @abstract The number of samples in each pixel of this MTLTexture.
 @discussion If this texture is any type other than 2DMultisample, samples is 1.
 */
@property (readonly) NSUInteger sampleCount;

/*!
 @property arrayLength
 @abstract The number of array elements in this MTLTexture.
 @discussion For non-Array texture types, arrayLength is 1.
 */
@property (readonly) NSUInteger arrayLength;

/*!
 @property usage
 @abstract Description of texture usage.
 */
@property (readonly) MTLTextureUsage usage;

/*!
 @property shareable
 @abstract If YES, this texture can be shared with other processes.
 @discussion Texture can be shared across process addres space boundaries through use of sharedTextureHandle and XPC.
 */
@property (readonly, getter = isShareable) BOOL shareable API_AVAILABLE(macos(10.14), ios(13.0));

/*!
 @property framebufferOnly
 @abstract If YES, this texture can only be used with a MTLAttachmentDescriptor, and cannot be used as a texture argument for MTLRenderCommandEncoder, MTLBlitCommandEncoder, or MTLComputeCommandEncoder. Furthermore, when this property's value is YES, readPixels/writePixels may not be used with this texture.
 @discussion Textures obtained from CAMetalDrawables may have this property set to YES, depending on the value of frameBufferOnly passed to their parent CAMetalLayer. Textures created directly by the application will not have any restrictions.
 */
@property (readonly, getter = isFramebufferOnly) BOOL framebufferOnly;


/*!
 @property allowGPUOptimizedContents
 @abstract Allow GPU-optimization for the contents texture. The default value is true.
 @discussion Useful for opting-out of GPU-optimization when implicit optimization (e.g. RT writes) is regressing CPU-read-back performance. See the documentation for optimizeContentsForGPUAccess: and optimizeContentsForCPUAccess: APIs.
 */
@property (readonly) BOOL allowGPUOptimizedContents API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @method getBytes:bytesPerRow:bytesPerImage:fromRegion:mipmapLevel:slice:
 @abstract Copies a block of pixels from a texture slice into the application's memory.
 */
- (void)getBytes:(void *)pixelBytes bytesPerRow:(NSUInteger)bytesPerRow bytesPerImage:(NSUInteger)bytesPerImage fromRegion:(MTLRegion)region mipmapLevel:(NSUInteger)level slice:(NSUInteger)slice;

/*!
 @method replaceRegion:mipmapLevel:slice:withBytes:bytesPerRow:bytesPerImage:
 @abstract Copy a block of pixel data from the caller's pointer into a texture slice.
 */
- (void)replaceRegion:(MTLRegion)region mipmapLevel:(NSUInteger)level slice:(NSUInteger)slice withBytes:(const void *)pixelBytes bytesPerRow:(NSUInteger)bytesPerRow bytesPerImage:(NSUInteger)bytesPerImage;

/*!
 @method getBytes:bytesPerRow:fromRegion:mipmapLevel:
 @abstract Convenience for getBytes:bytesPerRow:bytesPerImage:fromRegion:mipmapLevel:slice: that doesn't require slice related arguments
 */
- (void)getBytes:(void *)pixelBytes bytesPerRow:(NSUInteger)bytesPerRow fromRegion:(MTLRegion)region mipmapLevel:(NSUInteger)level;

/*!
 @method replaceRegion:mipmapLevel:withBytes:bytesPerRow:
 @abstract Convenience for replaceRegion:mipmapLevel:slice:withBytes:bytesPerRow:bytesPerImage: that doesn't require slice related arguments
 */
- (void)replaceRegion:(MTLRegion)region mipmapLevel:(NSUInteger)level withBytes:(const void *)pixelBytes bytesPerRow:(NSUInteger)bytesPerRow;

/*!
 @method newTextureViewWithPixelFormat:
 @abstract Create a new texture which shares the same storage as the source texture, but with a different (but compatible) pixel format.
 */
- (nullable id<MTLTexture>)newTextureViewWithPixelFormat:(MTLPixelFormat)pixelFormat;

/*!
 @method newTextureViewWithPixelFormat:textureType:levels:slices:
 @abstract Create a new texture which shares the same storage as the source texture, but with a different (but compatible) pixel format, texture type, levels and slices.
 */
- (nullable id<MTLTexture>)newTextureViewWithPixelFormat:(MTLPixelFormat)pixelFormat textureType:(MTLTextureType)textureType levels:(NSRange)levelRange slices:(NSRange)sliceRange API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method newSharedTextureHandle
 @abstract Create a new texture handle, that can be shared across process addres space boundaries.
 */
- (nullable MTLSharedTextureHandle *)newSharedTextureHandle API_AVAILABLE(macos(10.14), ios(13.0));



/*!
 @property swizzle
 @abstract The channel swizzle used when reading or sampling from this texture
 */
@property (readonly, nonatomic) MTLTextureSwizzleChannels swizzle API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method newTextureViewWithPixelFormat:textureType:levels:slices:swizzle:
 @abstract Create a new texture which shares the same storage as the source texture, but with a different (but compatible) pixel format, texture type, levels, slices and swizzle. 
 */
- (nullable id<MTLTexture>)newTextureViewWithPixelFormat:(MTLPixelFormat)pixelFormat textureType:(MTLTextureType)textureType levels:(NSRange)levelRange slices:(NSRange)sliceRange swizzle:(MTLTextureSwizzleChannels)swizzle API_AVAILABLE(macos(10.15), ios(13.0));

@end
NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLDevice.h
//
//  MTLDevice.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLTypes.h>
#import <Metal/MTLPixelFormat.h>
#import <Metal/MTLResource.h>
#import <Metal/MTLLibrary.h>
#import <IOSurface/IOSurfaceRef.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLCommandQueue;
@protocol MTLDevice;
@protocol MTLBuffer;
@protocol MTLDepthStencilState;
@protocol MTLFunction;
@protocol MTLLibrary;
@protocol MTLTexture;
@protocol MTLSamplerState;
@protocol MTLRenderPipelineState;
@protocol MTLComputePipelineState;
@protocol MTLHeap;
@protocol MTLFence;
@protocol MTLArgumentEncoder;
@class MTLTileRenderPipelineDescriptor;
@class MTLTilePipelineColorAttachmentDescriptor;
@class MTLSamplerDescriptor;
@class MTLRenderPipelineColorAttachmentDescriptor;
@class MTLDepthStencilDescriptor;
@class MTLTextureDescriptor;
@class MTLCompileOptions;
@class MTLRenderPipelineDescriptor;
@class MTLRenderPassDescriptor;
@class MTLRenderPipelineReflection;
@class MTLComputePipelineDescriptor;
@class MTLComputePipelineReflection;
@class MTLCommandQueueDescriptor;
@class MTLHeapDescriptor;
@class MTLIndirectCommandBufferDescriptor;
@protocol MTLIndirectRenderCommandEncoder;
@protocol MTLIndirectComputeCommandEncoder;
@protocol MTLIndirectCommandBuffer;
@class MTLSharedTextureHandle;
@protocol MTLEvent;
@protocol MTLSharedEvent;
@class MTLSharedEventHandle;

/*!
 @brief Returns a reference to the preferred system default Metal device.
 @discussion On Mac OS X systems that support automatic graphics switching, calling
 this API to get a Metal device will cause the system to switch to the high power
 GPU.  On other systems that support more than one GPU it will return the GPU that
 is associated with the main display.
 */
MTL_EXTERN id <MTLDevice> __nullable MTLCreateSystemDefaultDevice(void) API_AVAILABLE(macos(10.11), ios(8.0)) NS_RETURNS_RETAINED;

/*!
 @brief Returns all Metal devices in the system.
 @discussion This API will not cause the system to switch devices and leaves the
 decision about which GPU to use up to the application based on whatever criteria
 it deems appropriate.
*/
MTL_EXTERN NSArray <id<MTLDevice>> *MTLCopyAllDevices(void) API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios) NS_RETURNS_RETAINED;

typedef NS_ENUM(NSUInteger, MTLFeatureSet)
{
    MTLFeatureSet_iOS_GPUFamily1_v1 API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac, tvos) = 0,
    MTLFeatureSet_iOS_GPUFamily2_v1 API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac, tvos) = 1,

    MTLFeatureSet_iOS_GPUFamily1_v2 API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, uikitformac, tvos) = 2,
    MTLFeatureSet_iOS_GPUFamily2_v2 API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, uikitformac, tvos) = 3,
    MTLFeatureSet_iOS_GPUFamily3_v1 API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, uikitformac, tvos) = 4,

    MTLFeatureSet_iOS_GPUFamily1_v3 API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, uikitformac, tvos) = 5,
    MTLFeatureSet_iOS_GPUFamily2_v3 API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, uikitformac, tvos) = 6,
    MTLFeatureSet_iOS_GPUFamily3_v2 API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, uikitformac, tvos) = 7,

    MTLFeatureSet_iOS_GPUFamily1_v4 API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac, tvos) = 8,
    MTLFeatureSet_iOS_GPUFamily2_v4 API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac, tvos) = 9,
    MTLFeatureSet_iOS_GPUFamily3_v3 API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac, tvos) = 10,
    MTLFeatureSet_iOS_GPUFamily4_v1 API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac, tvos) = 11,
    
    MTLFeatureSet_iOS_GPUFamily1_v5 API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, uikitformac, tvos) = 12,
    MTLFeatureSet_iOS_GPUFamily2_v5 API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, uikitformac, tvos) = 13,
    MTLFeatureSet_iOS_GPUFamily3_v4 API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, uikitformac, tvos) = 14,
    MTLFeatureSet_iOS_GPUFamily4_v2 API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, uikitformac, tvos) = 15,
    MTLFeatureSet_iOS_GPUFamily5_v1 API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, uikitformac, tvos) = 16,
    

    MTLFeatureSet_macOS_GPUFamily1_v1 API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios) API_UNAVAILABLE(uikitformac) = 10000,
    MTLFeatureSet_OSX_GPUFamily1_v1 API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios) = MTLFeatureSet_macOS_GPUFamily1_v1, // deprecated

    MTLFeatureSet_macOS_GPUFamily1_v2 API_AVAILABLE(macos(10.12)) API_UNAVAILABLE(ios) API_UNAVAILABLE(uikitformac) = 10001,
    MTLFeatureSet_OSX_GPUFamily1_v2 API_AVAILABLE(macos(10.12)) API_UNAVAILABLE(ios) = MTLFeatureSet_macOS_GPUFamily1_v2, // deprecated
    MTLFeatureSet_macOS_ReadWriteTextureTier2 API_AVAILABLE(macos(10.12)) API_UNAVAILABLE(ios) = 10002,
    MTLFeatureSet_OSX_ReadWriteTextureTier2 API_AVAILABLE(macos(10.12)) API_UNAVAILABLE(ios) = MTLFeatureSet_macOS_ReadWriteTextureTier2, // deprecated

    MTLFeatureSet_macOS_GPUFamily1_v3 API_AVAILABLE(macos(10.13)) API_UNAVAILABLE(ios) API_UNAVAILABLE(uikitformac) = 10003,
    
    MTLFeatureSet_macOS_GPUFamily1_v4 API_AVAILABLE(macos(10.14)) API_UNAVAILABLE(ios) API_UNAVAILABLE(uikitformac) = 10004,
    MTLFeatureSet_macOS_GPUFamily2_v1 API_AVAILABLE(macos(10.14)) API_UNAVAILABLE(ios) API_UNAVAILABLE(uikitformac) = 10005,


    MTLFeatureSet_tvOS_GPUFamily1_v1 API_AVAILABLE(tvos(9.0)) API_UNAVAILABLE(macos, ios) = 30000,
    MTLFeatureSet_TVOS_GPUFamily1_v1 API_AVAILABLE(tvos(9.0)) API_UNAVAILABLE(macos, ios) = MTLFeatureSet_tvOS_GPUFamily1_v1, // deprecated
    
    MTLFeatureSet_tvOS_GPUFamily1_v2 API_AVAILABLE(tvos(10.0)) API_UNAVAILABLE(macos, ios) = 30001,
    
    MTLFeatureSet_tvOS_GPUFamily1_v3 API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(macos, ios) = 30002,
    
    MTLFeatureSet_tvOS_GPUFamily1_v4 API_AVAILABLE(tvos(12.0)) API_UNAVAILABLE(macos, ios) = 30004,
} API_AVAILABLE(macos(10.11), ios(8.0), tvos(9.0));

typedef NS_ENUM(NSInteger, MTLGPUFamily)
{
    MTLGPUFamilyApple1 = 1001,
    MTLGPUFamilyApple2 = 1002,
    MTLGPUFamilyApple3 = 1003,
    MTLGPUFamilyApple4 = 1004,
    MTLGPUFamilyApple5 = 1005,
    
    MTLGPUFamilyMac1 = 2001,
    MTLGPUFamilyMac2 = 2002,
    
    MTLGPUFamilyCommon1 = 3001,
    MTLGPUFamilyCommon2 = 3002,
    MTLGPUFamilyCommon3 = 3003,
    
    MTLGPUFamilyiOSMac1 = 4001,
    MTLGPUFamilyiOSMac2 = 4002,
} API_AVAILABLE(macos(10.15), ios(13.0));

typedef NS_ENUM(NSInteger, MTLSoftwareVersion)
{
    MTLSoftwareVersion3_0 = 0x00030000,
} API_AVAILABLE(macos(10.15), ios(13.0));


/*!
 @enum MTLPipelineOption
 @abstract Controls the creation of the pipeline
 */
typedef NS_OPTIONS(NSUInteger, MTLPipelineOption)
{
    MTLPipelineOptionNone               = 0,
    MTLPipelineOptionArgumentInfo       = 1 << 0,
    MTLPipelineOptionBufferTypeInfo     = 1 << 1,
    
} API_AVAILABLE(macos(10.11), ios(8.0));

/*!
 @enum MTLReadWriteTextureTier
 @abstract MTLReadWriteTextureTier determines support level for read-write texture formats.
 */
typedef NS_ENUM(NSUInteger, MTLReadWriteTextureTier)
{
    MTLReadWriteTextureTierNone = 0,
    MTLReadWriteTextureTier1 = 1,
    MTLReadWriteTextureTier2 = 2,
} API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @enum MTLArgumentBuffersTier
 @abstract MTLArgumentBuffersTier determines support level for argument buffers.
 */
typedef NS_ENUM(NSUInteger, MTLArgumentBuffersTier)
{
    MTLArgumentBuffersTier1 = 0,
    MTLArgumentBuffersTier2 = 1,
} API_AVAILABLE(macos(10.13), ios(11.0));




/*!
 @abstract Represent a memory size and alignment in bytes.
 */
typedef struct {
    NSUInteger size;
    NSUInteger align;
} MTLSizeAndAlign;

/* Convenience typedefs that make it easy to declare storage for certain return types. */
typedef __autoreleasing MTLRenderPipelineReflection * __nullable MTLAutoreleasedRenderPipelineReflection;
typedef __autoreleasing MTLComputePipelineReflection * __nullable MTLAutoreleasedComputePipelineReflection;

typedef void (^MTLNewLibraryCompletionHandler)(id <MTLLibrary> __nullable library, NSError * __nullable error);

typedef void (^MTLNewRenderPipelineStateCompletionHandler)(id <MTLRenderPipelineState> __nullable renderPipelineState, NSError * __nullable error);
typedef void (^MTLNewRenderPipelineStateWithReflectionCompletionHandler)(id <MTLRenderPipelineState> __nullable renderPipelineState, MTLRenderPipelineReflection * __nullable reflection, NSError * __nullable error);

typedef void (^MTLNewComputePipelineStateCompletionHandler)(id <MTLComputePipelineState> __nullable computePipelineState, NSError * __nullable error);
typedef void (^MTLNewComputePipelineStateWithReflectionCompletionHandler)(id <MTLComputePipelineState> __nullable computePipelineState, MTLComputePipelineReflection * __nullable reflection, NSError * __nullable error);


/*!
 * @class MTLArgumentDescriptor
 * @abstract Represents a member of an argument buffer
 */
MTL_EXPORT API_AVAILABLE(macos(10.13), ios(11.0))
@interface MTLArgumentDescriptor : NSObject <NSCopying>

/*!
 * @method argumentDescriptor
 * @abstract Create an autoreleased default argument descriptor
 */
+ (MTLArgumentDescriptor *)argumentDescriptor;

/*!
 * @property dataType
 * @abstract For constants, the data type. Otherwise, MTLDataTypeTexture, MTLDataTypeSampler, or
 * MTLDataTypePointer.
 */
@property (nonatomic) MTLDataType dataType;

/*!
 * @property index
 * @abstract The binding point index of the argument
 */
@property (nonatomic) NSUInteger index;

/*!
 * @property arrayLength
 * @abstract The length of an array of constants, textures, or samplers, or 0 for non-array arguments
 */
@property (nonatomic) NSUInteger arrayLength;

/*!
 * @property access
 * @abstract Access flags for the argument
 */
@property (nonatomic) MTLArgumentAccess access;

/*!
 * @property textureType
 * @abstract For texture arguments, the texture type
 */
@property (nonatomic) MTLTextureType textureType;

/*!
 @property constantBlockAlignment
 @abstract if set forces the constant block to be aligned to the given alignment
 @discussion Should only be set on the first constant of the block and is only valid if a corresponding
     explicit "alignas" is applied to the constant in the metal shader language.
 */
@property (nonatomic) NSUInteger constantBlockAlignment;

@end



/*!
 @protocol MTLDevice
 @abstract MTLDevice represents a processor capable of data parallel computations
 */
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLDevice <NSObject>

/*!
 @property name
 @abstract The full name of the vendor device.
 */
@property (nonnull, readonly) NSString *name;

/*!
 @property registryID
 @abstract Returns the IORegistry ID for the Metal device
 @discussion The registryID value for a Metal device is global to all tasks, and may be used
 to identify the GPU across task boundaries.
*/
@property (readonly) uint64_t registryID API_AVAILABLE(macos(10.13), ios(11.0)) ;

/*!
 @property maxThreadsPerThreadgroup
 @abstract The maximum number of threads along each dimension.
 */
@property (readonly) MTLSize maxThreadsPerThreadgroup API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property lowPower
 @abstract On systems that support automatic graphics switching, this will return YES for the the low power device.
 */
@property (readonly, getter=isLowPower) BOOL lowPower API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios);

/*!
 @property headless
 @abstract On systems that include more that one GPU, this will return YES for any device that does not support any displays.  Only available on Mac OS X.
 */
@property (readonly, getter=isHeadless) BOOL headless API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios);

/*!
 @property removable
 @abstract If this GPU is removable, this property will return YES.  
 @discussion If a GPU is is removed without warning, APIs may fail even with good input, even before a notification can get posted informing
 the application that the device has been removed.
 */
@property (readonly, getter=isRemovable) BOOL removable API_AVAILABLE(macos(10.13), uikitformac(13.0)) API_UNAVAILABLE(ios);

/*!
 @property hasUnifiedMemory
 @abstract Returns YES if this GPU shares its memory with the rest of the machine (CPU, etc.)
 @discussion Some GPU architectures do not have dedicated local memory and instead only use the same memory shared with the rest
 of the machine.  This property will return YES for GPUs that fall into that category.
*/
@property (readonly) BOOL hasUnifiedMemory API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @property recommendedMaxWorkingSetSize
 @abstract Returns an approximation of how much memory this device can use with good performance.
 @discussion Performance may be improved by keeping the total size of all resources (texture and buffers)
 and heaps less than this threshold, beyond which the device is likely to be overcommitted and incur a
 performance penalty. */
@property (readonly) uint64_t recommendedMaxWorkingSetSize API_AVAILABLE(macos(10.12), uikitformac(13.0)) API_UNAVAILABLE(ios);


/*!
 @property depth24Stencil8PixelFormatSupported
 @abstract If YES, device supports MTLPixelFormatDepth24Unorm_Stencil8.
 */
@property (readonly, getter=isDepth24Stencil8PixelFormatSupported) BOOL depth24Stencil8PixelFormatSupported API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios);

/*!
 @property readWriteTextureSupport
 @abstract Query support tier for read-write texture formats.
 @return MTLReadWriteTextureTier enum value.
 */
@property (readonly) MTLReadWriteTextureTier readWriteTextureSupport API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @property argumentBuffersSupport
 @abstract Query support tier for Argument Buffers.
 @return MTLArgumentBuffersTier enum value.
 */
@property (readonly) MTLArgumentBuffersTier argumentBuffersSupport API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @property rasterOrderGroupsSupported
 @abstract Query device for raster order groups support.
 @return BOOL value. If YES, the device supports raster order groups. If NO, the device does not.
 */
@property (readonly, getter=areRasterOrderGroupsSupported) BOOL rasterOrderGroupsSupported API_AVAILABLE(macos(10.13), ios(11.0));






/*!
 @property currentAllocatedSize
 @abstract The current size in bytes of all resources allocated by this device
 */
@property (readonly) NSUInteger currentAllocatedSize API_AVAILABLE(macos(10.13), ios(11.0));



/*!
 @method newCommandQueue
 @brief Create and return a new command queue.   Command Queues created via this method will only allow up to 64 non-completed command buffers.
 @return The new command queue object
 */
- (nullable id <MTLCommandQueue>)newCommandQueue;

/*!
 @method newCommandQueueWithMaxCommandBufferCount
 @brief Create and return a new command queue with a given upper bound on non-completed command buffers.
 @return The new command queue object
 */
- (nullable id <MTLCommandQueue>)newCommandQueueWithMaxCommandBufferCount:(NSUInteger)maxCommandBufferCount;

/*!
 @method heapTextureSizeAndAlignWithDescriptor:
 @abstract Determine the byte size of textures when sub-allocated from a heap.
 @discussion This method can be used to help determine the required heap size.
 */
- (MTLSizeAndAlign)heapTextureSizeAndAlignWithDescriptor:(MTLTextureDescriptor *)desc API_AVAILABLE(macos(10.13), ios(10.0));

/*!
 @method heapBufferSizeAndAlignWithLength:options:
 @abstract Determine the byte size of buffers when sub-allocated from a heap.
 @discussion This method can be used to help determine the required heap size.
 */
- (MTLSizeAndAlign)heapBufferSizeAndAlignWithLength:(NSUInteger)length options:(MTLResourceOptions)options API_AVAILABLE(macos(10.13), ios(10.0));

/*!
 @method newHeapWithDescriptor:
 @abstract Create a new heap with the given descriptor.
 */
- (nullable id <MTLHeap>)newHeapWithDescriptor:(MTLHeapDescriptor *)descriptor API_AVAILABLE(macos(10.13), ios(10.0));

/*!
 @method newBufferWithLength:options:
 @brief Create a buffer by allocating new memory.
 */
- (nullable id <MTLBuffer>)newBufferWithLength:(NSUInteger)length options:(MTLResourceOptions)options;

/*!
 @method newBufferWithBytes:length:options:
 @brief Create a buffer by allocating new memory and specifing the initial contents to be copied into it.
 */
- (nullable id <MTLBuffer>)newBufferWithBytes:(const void *)pointer length:(NSUInteger)length options:(MTLResourceOptions)options;

/*!
 @method newBufferWithBytesNoCopy:length:options:deallocator:
 @brief Create a buffer by wrapping an existing part of the address space.
 */
- (nullable id <MTLBuffer>)newBufferWithBytesNoCopy:(void *)pointer length:(NSUInteger)length options:(MTLResourceOptions)options deallocator:(void (^ __nullable)(void *pointer, NSUInteger length))deallocator;

/*!
 @method newDepthStencilStateWithDescriptor:
 @brief Create a depth/stencil test state object.
 */
- (nullable id <MTLDepthStencilState>)newDepthStencilStateWithDescriptor:(MTLDepthStencilDescriptor *)descriptor;

/*!
 @method newTextureWithDescriptor:
 @abstract Allocate a new texture with privately owned storage.
 */
- (nullable id <MTLTexture>)newTextureWithDescriptor:(MTLTextureDescriptor *)descriptor;

/*!
 @method newTextureWithDescriptor:iosurface:plane
 @abstract Create a new texture from an IOSurface.
 @param descriptor A description of the properties for the new texture.
 @param iosurface The IOSurface to use as storage for the new texture.
 @param plane The plane within the IOSurface to use.
 @return A new texture object.
 */
- (nullable id <MTLTexture>)newTextureWithDescriptor:(MTLTextureDescriptor *)descriptor iosurface:(IOSurfaceRef)iosurface plane:(NSUInteger)plane API_AVAILABLE(macos(10.11), ios(11.0));


/*!
 @method newSharedTextureWithDescriptor
 @abstract Create a new texture that can be shared across process boundaries.
 @discussion This texture can be shared between process boundaries
 but not between different GPUs, by passing its MTLSharedTextureHandle.
 @param descriptor A description of the properties for the new texture.
 @return A new texture object.
 */
- (nullable id <MTLTexture>)newSharedTextureWithDescriptor:(MTLTextureDescriptor *)descriptor API_AVAILABLE(macos(10.14), ios(13.0));

/*!
 @method newSharedTextureWithHandle
 @abstract Recreate shared texture from received texture handle.
 @discussion This texture was shared between process boundaries by other
 process using MTLSharedTextureHandle. Current process will now share
 it with other processes and will be able to interact with it (but still
 in scope of the same GPUs).
 @param sharedHandle Handle to shared texture in this process space.
 @return A new texture object.
 */
- (nullable id <MTLTexture>)newSharedTextureWithHandle:(MTLSharedTextureHandle *)sharedHandle API_AVAILABLE(macos(10.14), ios(13.0));

/*!
 @method newSamplerStateWithDescriptor:
 @abstract Create a new sampler.
*/
- (nullable id <MTLSamplerState>)newSamplerStateWithDescriptor:(MTLSamplerDescriptor *)descriptor;

/*!
 @method newDefaultLibrary
 @abstract Returns the default library for the main bundle.
 @discussion use newDefaultLibraryWithBundle:error: to get an NSError in case of failure.
 */
- (nullable id <MTLLibrary>)newDefaultLibrary;

/*
 @method newDefaultLibraryWithBundle:error:
 @abstract Returns the default library for a given bundle.
 @return A pointer to the library, nil if an error occurs.
*/
- (nullable id <MTLLibrary>)newDefaultLibraryWithBundle:(NSBundle *)bundle error:(__autoreleasing NSError **)error API_AVAILABLE(macos(10.12), ios(10.0));

/*!
 @method newLibraryWithFile:
 @abstract Load a MTLLibrary from a metallib file.
 */
- (nullable id <MTLLibrary>)newLibraryWithFile:(NSString *)filepath error:(__autoreleasing NSError **)error;

/*!
 @method newLibraryWithURL:
 @abstract Load a MTLLibrary from a metallib file.
 */
- (nullable id <MTLLibrary>)newLibraryWithURL:(NSURL *)url error:(__autoreleasing NSError **)error API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @method newLibraryWithData:
 @abstract Load a MTLLibrary from a dispatch_data_t
 @param data A metallib file already loaded as data in the form of dispatch_data_t.
 @param error An error if we fail to open the metallib data.
 */
- (nullable id <MTLLibrary>)newLibraryWithData:(dispatch_data_t)data error:(__autoreleasing NSError **)error;

/*!
 @method newLibraryWithSource:options:error:
 @abstract Load a MTLLibrary from source.
 */
- (nullable id <MTLLibrary>)newLibraryWithSource:(NSString *)source options:(nullable MTLCompileOptions *)options error:(__autoreleasing NSError **)error;

/*!
 @method newLibraryWithSource:options:completionHandler:
 @abstract Load a MTLLibrary from source.
 */
- (void)newLibraryWithSource:(NSString *)source options:(nullable MTLCompileOptions *)options completionHandler:(MTLNewLibraryCompletionHandler)completionHandler;

/*!
 @method newRenderPipelineStateWithDescriptor:error:
 @abstract Create and compile a new MTLRenderPipelineState object synchronously.
 */
- (nullable id <MTLRenderPipelineState>)newRenderPipelineStateWithDescriptor:(MTLRenderPipelineDescriptor *)descriptor error:(__autoreleasing NSError **)error;

/*!
 @method newRenderPipelineStateWithDescriptor:options:reflection:error:
 @abstract Create and compile a new MTLRenderPipelineState object synchronously and returns additional reflection information.
 */
- (nullable id <MTLRenderPipelineState>)newRenderPipelineStateWithDescriptor:(MTLRenderPipelineDescriptor *)descriptor options:(MTLPipelineOption)options reflection:(MTLAutoreleasedRenderPipelineReflection * __nullable)reflection error:(__autoreleasing NSError **)error;

/*!
 @method newRenderPipelineState:completionHandler:
 @abstract Create and compile a new MTLRenderPipelineState object asynchronously.
 */
- (void)newRenderPipelineStateWithDescriptor:(MTLRenderPipelineDescriptor *)descriptor completionHandler:(MTLNewRenderPipelineStateCompletionHandler)completionHandler;

/*!
 @method newRenderPipelineState:options:completionHandler:
 @abstract Create and compile a new MTLRenderPipelineState object asynchronously and returns additional reflection information
 */
- (void)newRenderPipelineStateWithDescriptor:(MTLRenderPipelineDescriptor *)descriptor options:(MTLPipelineOption)options completionHandler:(MTLNewRenderPipelineStateWithReflectionCompletionHandler)completionHandler;

/*!
 @method newComputePipelineStateWithDescriptor:error:
 @abstract Create and compile a new MTLComputePipelineState object synchronously.
 */
- (nullable id <MTLComputePipelineState>)newComputePipelineStateWithFunction:(id <MTLFunction>)computeFunction error:(__autoreleasing NSError **)error;

/*!
 @method newComputePipelineStateWithDescriptor:options:reflection:error:
 @abstract Create and compile a new MTLComputePipelineState object synchronously.
 */
- (nullable id <MTLComputePipelineState>)newComputePipelineStateWithFunction:(id <MTLFunction>)computeFunction options:(MTLPipelineOption)options reflection:(MTLAutoreleasedComputePipelineReflection * __nullable)reflection error:(__autoreleasing NSError **)error;

/*!
 @method newComputePipelineStateWithDescriptor:completionHandler:
 @abstract Create and compile a new MTLComputePipelineState object asynchronously.
 */
- (void)newComputePipelineStateWithFunction:(id <MTLFunction>)computeFunction completionHandler:(MTLNewComputePipelineStateCompletionHandler)completionHandler;

/*!
 @method newComputePipelineStateWithDescriptor:options:completionHandler:
 @abstract Create and compile a new MTLComputePipelineState object asynchronously.
 */
- (void)newComputePipelineStateWithFunction:(id <MTLFunction>)computeFunction options:(MTLPipelineOption)options completionHandler:(MTLNewComputePipelineStateWithReflectionCompletionHandler)completionHandler;

/*!
 @method newComputePipelineStateWithDescriptor:options:reflection:error:
 @abstract Create and compile a new MTLComputePipelineState object synchronously.
 */
- (nullable id <MTLComputePipelineState>)newComputePipelineStateWithDescriptor:(MTLComputePipelineDescriptor *)descriptor options:(MTLPipelineOption)options reflection:(MTLAutoreleasedComputePipelineReflection * __nullable)reflection error:(__autoreleasing NSError **)error API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method newComputePipelineStateWithDescriptor:options:completionHandler:
 @abstract Create and compile a new MTLComputePipelineState object asynchronously.
 */
- (void)newComputePipelineStateWithDescriptor:(MTLComputePipelineDescriptor *)descriptor options:(MTLPipelineOption)options completionHandler:(MTLNewComputePipelineStateWithReflectionCompletionHandler)completionHandler API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method newFence
 @abstract Create a new MTLFence object
 */
- (nullable id <MTLFence>)newFence API_AVAILABLE(macos(10.13), ios(10.0));

/*!
 @method supportsFeatureSet:
 @abstract Returns TRUE if the feature set is supported by this MTLDevice.
 */
- (BOOL)supportsFeatureSet:(MTLFeatureSet)featureSet;

/*!
 @method supportsFamily:
 @abstract Returns TRUE if the GPU Family is supported by this MTLDevice.
 */
- (BOOL)supportsFamily:(MTLGPUFamily)gpuFamily API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method supportsVersion
 @abstract Returns TRUE if the Metal version is supported by this MTLDevice.
 */
- (BOOL)supportsVersion:(MTLSoftwareVersion)version API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method supportsTextureSampleCount:
 @brief Query device if it support textures with a given sampleCount.
 @return BOOL value. If YES, device supports the given sampleCount for textures. If NO, device does not support the given sampleCount.
 */
- (BOOL)supportsTextureSampleCount:(NSUInteger)sampleCount API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method minimumLinearTextureAlignmentForPixelFormat:
 @abstract Returns the minimum alignment required for offset and rowBytes when creating a linear texture. An error is thrown for queries with invalid pixel formats (depth, stencil, or compressed formats).
 */
- (NSUInteger)minimumLinearTextureAlignmentForPixelFormat:(MTLPixelFormat)format API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @method minimumTextureBufferAlignmentForPixelFormat:
 @abstract Returns the minimum alignment required for offset and rowBytes when creating a texture buffer from a buffer.
 */
- (NSUInteger)minimumTextureBufferAlignmentForPixelFormat:(MTLPixelFormat)format API_AVAILABLE(macos(10.14), ios(12.0));


/*!
 @method newRenderPipelineStateWithTileDescriptor:options:reflection:error:
 @abstract Create and compile a new MTLRenderPipelineState object synchronously given a MTLTileRenderPipelineDescriptor.
 */
- (nullable id <MTLRenderPipelineState>)newRenderPipelineStateWithTileDescriptor:(MTLTileRenderPipelineDescriptor*)descriptor options:(MTLPipelineOption)options reflection:(MTLAutoreleasedRenderPipelineReflection * __nullable)reflection error:(__autoreleasing NSError **)error API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);


/*!
 @method newRenderPipelineStateWithTileDescriptor:options:completionHandler:
 @abstract Create and compile a new MTLRenderPipelineState object asynchronously given a MTLTileRenderPipelineDescriptor.
 */
- (void)newRenderPipelineStateWithTileDescriptor:(MTLTileRenderPipelineDescriptor *)descriptor options:(MTLPipelineOption)options completionHandler:(MTLNewRenderPipelineStateWithReflectionCompletionHandler)completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @property maxThreadgroupMemoryLength
 @abstract The maximum threadgroup memory available, in bytes.
 */
@property (readonly) NSUInteger maxThreadgroupMemoryLength API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @property maxArgumentBufferSamplerCount
 @abstract The maximum number of unique argument buffer samplers per app.
 @discussion This limit is only applicable to samplers that have their supportArgumentBuffers property set to true. A MTLSamplerState object is considered unique if the configuration of its originating MTLSamplerDescriptor properties is unique. For example, two samplers with equal minFilter values but different magFilter values are considered unique.
 */
@property (readonly) NSUInteger maxArgumentBufferSamplerCount API_AVAILABLE(macos(10.14), ios(12.0));


/*!
 @property programmableSaplePositionsSupported
 @abstract Query device for programmable sample position support.
 @return BOOL value. If YES, the device supports programmable sample positions. If NO, the device does not.
 */
@property (readonly, getter=areProgrammableSamplePositionsSupported) BOOL programmableSamplePositionsSupported API_AVAILABLE(macos(10.13), ios(11.0));


/*!
 @method getDefaultSamplePositions:count:
 @abstract Retrieve the default sample positions.
 @param positions The destination array for default sample position data.
 @param count Specifies the sample count for which to retrieve the default positions, the length of the positions array, and must be set to a valid sample count.
 */
- (void)getDefaultSamplePositions:(MTLSamplePosition *)positions count:(NSUInteger)count API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 * @method newArgumentEncoderWithArguments:count:
 * @abstract Creates an argument encoder for an array of argument descriptors which will be encoded sequentially.
 */
- (nullable id <MTLArgumentEncoder>)newArgumentEncoderWithArguments:(NSArray <MTLArgumentDescriptor *> *)arguments API_AVAILABLE(macos(10.13), ios(11.0));



/*!
 * @method newIndirectCommandBufferWithDescriptor:maxCommandCount:options
 * @abstract Creates a new indirect command buffer with the given descriptor and count.
 * @param descriptor The descriptor encodes the maximum logical stride of each command.
 * @param maxCount The maximum number of commands that this buffer can contain.
 * @param options The options for the indirect command buffer.
 * @discussion The returned buffer can be safely executed without first encoding into (but is wasteful).
 */
- (nullable id <MTLIndirectCommandBuffer>)newIndirectCommandBufferWithDescriptor:(MTLIndirectCommandBufferDescriptor*)descriptor maxCommandCount:(NSUInteger)maxCount options:(MTLResourceOptions)options API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @method newEvent
 @abstract Returns a new single-device non-shareable Metal event object
*/
- (nullable id <MTLEvent>)newEvent API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @method newSharedEvent
 @abstract Returns a shareable multi-device event.
 */
- (nullable id <MTLSharedEvent>)newSharedEvent API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @method newSharedEventWithHandle
 @abstract Creates a shareable multi-device event from an existing shared event handle.
*/
- (nullable id <MTLSharedEvent>)newSharedEventWithHandle:(MTLSharedEventHandle *)sharedEventHandle API_AVAILABLE(macos(10.14), ios(12.0));









@property (readonly) NSUInteger maxBufferLength API_AVAILABLE(macos(10.14), ios(12.0));



@end
NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLArgument.h
//
//  MTLArgument.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLTexture.h>


NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSUInteger, MTLDataType) {

    MTLDataTypeNone = 0,

    MTLDataTypeStruct = 1,
    MTLDataTypeArray  = 2,

    MTLDataTypeFloat  = 3,
    MTLDataTypeFloat2 = 4,
    MTLDataTypeFloat3 = 5,
    MTLDataTypeFloat4 = 6,

    MTLDataTypeFloat2x2 = 7,
    MTLDataTypeFloat2x3 = 8,
    MTLDataTypeFloat2x4 = 9,

    MTLDataTypeFloat3x2 = 10,
    MTLDataTypeFloat3x3 = 11,
    MTLDataTypeFloat3x4 = 12,

    MTLDataTypeFloat4x2 = 13,
    MTLDataTypeFloat4x3 = 14,
    MTLDataTypeFloat4x4 = 15,

    MTLDataTypeHalf  = 16,
    MTLDataTypeHalf2 = 17,
    MTLDataTypeHalf3 = 18,
    MTLDataTypeHalf4 = 19,

    MTLDataTypeHalf2x2 = 20,
    MTLDataTypeHalf2x3 = 21,
    MTLDataTypeHalf2x4 = 22,

    MTLDataTypeHalf3x2 = 23,
    MTLDataTypeHalf3x3 = 24,
    MTLDataTypeHalf3x4 = 25,

    MTLDataTypeHalf4x2 = 26,
    MTLDataTypeHalf4x3 = 27,
    MTLDataTypeHalf4x4 = 28,

    MTLDataTypeInt  = 29,
    MTLDataTypeInt2 = 30,
    MTLDataTypeInt3 = 31,
    MTLDataTypeInt4 = 32,

    MTLDataTypeUInt  = 33,
    MTLDataTypeUInt2 = 34,
    MTLDataTypeUInt3 = 35,
    MTLDataTypeUInt4 = 36,

    MTLDataTypeShort  = 37,
    MTLDataTypeShort2 = 38,
    MTLDataTypeShort3 = 39,
    MTLDataTypeShort4 = 40,

    MTLDataTypeUShort = 41,
    MTLDataTypeUShort2 = 42,
    MTLDataTypeUShort3 = 43,
    MTLDataTypeUShort4 = 44,

    MTLDataTypeChar  = 45,
    MTLDataTypeChar2 = 46,
    MTLDataTypeChar3 = 47,
    MTLDataTypeChar4 = 48,

    MTLDataTypeUChar  = 49,
    MTLDataTypeUChar2 = 50,
    MTLDataTypeUChar3 = 51,
    MTLDataTypeUChar4 = 52,

    MTLDataTypeBool  = 53,
    MTLDataTypeBool2 = 54,
    MTLDataTypeBool3 = 55,
    MTLDataTypeBool4 = 56,

    MTLDataTypeTexture API_AVAILABLE(macos(10.13), ios(11.0)) = 58,
    MTLDataTypeSampler API_AVAILABLE(macos(10.13), ios(11.0)) = 59,
    MTLDataTypePointer API_AVAILABLE(macos(10.13), ios(11.0)) = 60,

    MTLDataTypeR8Unorm         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac) = 62,
    MTLDataTypeR8Snorm         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac) = 63,
    MTLDataTypeR16Unorm        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac) = 64,
    MTLDataTypeR16Snorm        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac) = 65,
    MTLDataTypeRG8Unorm        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac) = 66,
    MTLDataTypeRG8Snorm        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac) = 67,
    MTLDataTypeRG16Unorm       API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac) = 68,
    MTLDataTypeRG16Snorm       API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac) = 69,
    MTLDataTypeRGBA8Unorm      API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac) = 70,
    MTLDataTypeRGBA8Unorm_sRGB API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac) = 71,
    MTLDataTypeRGBA8Snorm      API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac) = 72,
    MTLDataTypeRGBA16Unorm     API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac) = 73,
    MTLDataTypeRGBA16Snorm     API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac) = 74,
    MTLDataTypeRGB10A2Unorm    API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac) = 75,
    MTLDataTypeRG11B10Float    API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac) = 76,
    MTLDataTypeRGB9E5Float     API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac) = 77,
    MTLDataTypeRenderPipeline  API_AVAILABLE(macos(10.14), ios(13.0)) = 78,
    MTLDataTypeComputePipeline API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos) = 79,
    MTLDataTypeIndirectCommandBuffer   API_AVAILABLE(macos(10.14), ios(12.0)) = 80,
} API_AVAILABLE(macos(10.11), ios(8.0));

@class MTLArgument;

/*!
 @enum MTLArgumentType
 @abstract The type for an input to a MTLRenderPipelineState or a MTLComputePipelineState
 
 @constant MTLArgumentTypeBuffer
 This input is a MTLBuffer
 
 @constant MTLArgumentTypeThreadgroupMemory
 This input is a pointer to the threadgroup memory.
 
 @constant MTLArgumentTypeTexture
 This input is a MTLTexture.
 
 @constant MTLArgumentTypeSampler
 This input is a sampler.
*/
typedef NS_ENUM(NSUInteger, MTLArgumentType) {

    MTLArgumentTypeBuffer = 0,
    MTLArgumentTypeThreadgroupMemory= 1,
    MTLArgumentTypeTexture = 2,
    MTLArgumentTypeSampler = 3,

    MTLArgumentTypeImageblockData API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac)     = 16,
    MTLArgumentTypeImageblock API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac)         = 17,
} API_AVAILABLE(macos(10.11), ios(8.0));

/*!
 @enum MTLArgumentAccess
*/
typedef NS_ENUM(NSUInteger, MTLArgumentAccess) {

    MTLArgumentAccessReadOnly   = 0,
    MTLArgumentAccessReadWrite  = 1,
    MTLArgumentAccessWriteOnly  = 2,
} API_AVAILABLE(macos(10.11), ios(8.0));

@class MTLStructType;
@class MTLArrayType;
@class MTLTextureReferenceType;
@class MTLPointerType;

MTL_EXPORT API_AVAILABLE(macos(10.13), ios(11.0))
@interface MTLType : NSObject
@property (readonly) MTLDataType dataType;
@end

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLStructMember : NSObject
 
@property (readonly) NSString *name;
@property (readonly) NSUInteger offset;
@property (readonly) MTLDataType dataType;

- (nullable MTLStructType *)structType;
- (nullable MTLArrayType *)arrayType;

- (nullable MTLTextureReferenceType *)textureReferenceType  API_AVAILABLE(macos(10.13), ios(11.0));
- (nullable MTLPointerType *)pointerType  API_AVAILABLE(macos(10.13), ios(11.0));

@property (readonly) NSUInteger argumentIndex API_AVAILABLE(macos(10.13), ios(11.0));


@end
 
MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLStructType  : MTLType

@property (readonly) NSArray <MTLStructMember *> *members;

- (nullable MTLStructMember *)memberByName:(NSString *)name;

@end

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLArrayType  : MTLType

@property (readonly) MTLDataType elementType;

@property (readonly) NSUInteger arrayLength;
@property (readonly) NSUInteger stride;
@property (readonly) NSUInteger argumentIndexStride API_AVAILABLE(macos(10.13), ios(11.0));
- (nullable MTLStructType *)elementStructType;
- (nullable MTLArrayType *)elementArrayType;
- (nullable MTLTextureReferenceType *)elementTextureReferenceType  API_AVAILABLE(macos(10.13), ios(11.0));
- (nullable MTLPointerType *)elementPointerType  API_AVAILABLE(macos(10.13), ios(11.0));


@end

MTL_EXPORT API_AVAILABLE(macos(10.13), ios(11.0))
@interface MTLPointerType : MTLType

@property (readonly) MTLDataType elementType;           // MTLDataTypeFloat, MTLDataTypeFloat4, MTLDataTypeStruct, ...
@property (readonly) MTLArgumentAccess access;
@property (readonly) NSUInteger alignment;              // min alignment for the element data
@property (readonly) NSUInteger dataSize;               // sizeof(T) for T *argName

@property (readonly) BOOL elementIsArgumentBuffer API_AVAILABLE(macos(10.13), ios(11.0));

- (nullable MTLStructType *)elementStructType  API_AVAILABLE(macos(10.13), ios(11.0));
- (nullable MTLArrayType *)elementArrayType  API_AVAILABLE(macos(10.13), ios(11.0));

@end

MTL_EXPORT API_AVAILABLE(macos(10.13), ios(11.0))
@interface MTLTextureReferenceType : MTLType

@property (readonly) MTLDataType textureDataType; // half, float, int, or uint.
@property (readonly) MTLTextureType textureType;  // texture1D, texture2D...
@property (readonly) MTLArgumentAccess access;    // read, write, read-write
@property (readonly) BOOL isDepthTexture;         // true for depth textures

@end

/*!
 MTLArgument
*/
MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLArgument : NSObject

@property (readonly) NSString *name;
@property (readonly) MTLArgumentType type;
@property (readonly) MTLArgumentAccess access;
@property (readonly) NSUInteger index;

@property (readonly, getter=isActive) BOOL active;

// for buffer arguments
@property (readonly) NSUInteger      bufferAlignment;		// min alignment of starting offset in the buffer
@property (readonly) NSUInteger      bufferDataSize; 		// sizeof(T) for T *argName
@property (readonly) MTLDataType     bufferDataType; 		// MTLDataTypeFloat, MTLDataTypeFloat4, MTLDataTypeStruct, ...
@property (readonly, nullable) MTLStructType  *bufferStructType;
@property (readonly, nullable) MTLPointerType *bufferPointerType API_AVAILABLE(macos(10.13), ios(11.0));

// for threadgroup memory arguments
@property (readonly) NSUInteger     threadgroupMemoryAlignment;
@property (readonly) NSUInteger     threadgroupMemoryDataSize; // sizeof(T) for T *argName

// for texture arguments
@property (readonly) MTLTextureType textureType; // texture1D, texture2D...
@property (readonly) MTLDataType    textureDataType; // half, float, int, or uint.
@property (readonly) BOOL           isDepthTexture API_AVAILABLE(macos(10.12), ios(10.0)); // true for depth textures
@property (readonly) NSUInteger     arrayLength API_AVAILABLE(macos(10.13), ios(10.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLComputeCommandEncoder.h
//
//  MTLComputeCommandEncoder.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLTypes.h>
#import <Metal/MTLCommandEncoder.h>
#import <Metal/MTLTexture.h>
#import <Metal/MTLCommandBuffer.h>
#import <Metal/MTLFence.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLFunction;
@protocol MTLBuffer;
@protocol MTLSamplerState;
@protocol MTLTexture;
@protocol MTLComputePipelineState;
@protocol MTLResource;
typedef struct {
    uint32_t threadgroupsPerGrid[3];
} MTLDispatchThreadgroupsIndirectArguments;

typedef struct {
	uint32_t  stageInOrigin[3];
	uint32_t  stageInSize[3];
} MTLStageInRegionIndirectArguments API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @protocol MTLComputeCommandEncoder
 @abstract A command encoder that writes data parallel compute commands.
 */
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLComputeCommandEncoder <MTLCommandEncoder>

/*!
 @property dispatchType
 @abstract The dispatch type of the compute command encoder.
 */

@property (readonly) MTLDispatchType dispatchType API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @method setComputePipelineState:
 @abstract Set the compute pipeline state that will be used.
 */
- (void)setComputePipelineState:(id <MTLComputePipelineState>)state;

/*!
 @method setBytes:length:atIndex:
 @brief Set the data (by copy) for a given buffer binding point.  This will remove any existing MTLBuffer from the binding point.
 */
- (void)setBytes:(const void *)bytes length:(NSUInteger)length atIndex:(NSUInteger)index API_AVAILABLE(macos(10.11), ios(8.3));

/*!
 @method setBuffer:offset:atIndex:
 @brief Set a global buffer for all compute kernels at the given bind point index.
 */
- (void)setBuffer:(nullable id <MTLBuffer>)buffer offset:(NSUInteger)offset atIndex:(NSUInteger)index;

/*!
 @method setBufferOffset:atIndex:
 @brief Set the offset within the current global buffer for all compute kernels at the given bind point index.
 */
- (void)setBufferOffset:(NSUInteger)offset atIndex:(NSUInteger)index API_AVAILABLE(macos(10.11), ios(8.3));

/*!
 @method setBuffers:offsets:withRange:
 @brief Set an array of global buffers for all compute kernels with the given bind point range.
 */
- (void)setBuffers:(const id <MTLBuffer> __nullable [__nonnull])buffers offsets:(const NSUInteger [__nonnull])offsets withRange:(NSRange)range;

/*!
 @method setTexture:atIndex:
 @brief Set a global texture for all compute kernels at the given bind point index.
 */
- (void)setTexture:(nullable id <MTLTexture>)texture atIndex:(NSUInteger)index;

/*!
 @method setTextures:withRange:
 @brief Set an array of global textures for all compute kernels with the given bind point range.
 */
- (void)setTextures:(const id <MTLTexture> __nullable [__nonnull])textures withRange:(NSRange)range;

/*!
 @method setSamplerState:atIndex:
 @brief Set a global sampler for all compute kernels at the given bind point index.
 */
- (void)setSamplerState:(nullable id <MTLSamplerState>)sampler atIndex:(NSUInteger)index;

/*!
 @method setSamplers:withRange:
 @brief Set an array of global samplers for all compute kernels with the given bind point range.
 */
- (void)setSamplerStates:(const id <MTLSamplerState> __nullable [__nonnull])samplers withRange:(NSRange)range;

/*!
 @method setSamplerState:lodMinClamp:lodMaxClamp:atIndex:
 @brief Set a global sampler for all compute kernels at the given bind point index.
 */
- (void)setSamplerState:(nullable id <MTLSamplerState>)sampler lodMinClamp:(float)lodMinClamp lodMaxClamp:(float)lodMaxClamp atIndex:(NSUInteger)index;

/*!
 @method setSamplers:lodMinClamps:lodMaxClamps:withRange:
 @brief Set an array of global samplers for all compute kernels with the given bind point range.
 */
- (void)setSamplerStates:(const id <MTLSamplerState> __nullable [__nonnull])samplers lodMinClamps:(const float [__nonnull])lodMinClamps lodMaxClamps:(const float [__nonnull])lodMaxClamps withRange:(NSRange)range;


/*!
 @method setThreadgroupMemoryLength:atIndex:
 @brief Set the threadgroup memory byte length at the binding point specified by the index. This applies to all compute kernels.
 */
- (void)setThreadgroupMemoryLength:(NSUInteger)length atIndex:(NSUInteger)index;



/*!
 @method setImageblockWidth:height:
 @brief Set imageblock sizes.
 */
- (void)setImageblockWidth:(NSUInteger)width height:(NSUInteger)height API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*
 @method setStageInRegion:region:
 @brief Set the region of the stage_in attributes to apply the compute kernel.
*/
- (void)setStageInRegion:(MTLRegion)region API_AVAILABLE(macos(10.12), ios(10.0));

/*
 @method setStageInRegionWithIndirectBuffer:indirectBufferOffset:
 @abstract sets the stage in region indirectly for the following indirect dispatch calls.
 @param indirectBuffer A buffer object that the device will read the stageIn region arguments from, see MTLStageInRegionIndirectArguments.
 @param indirectBufferOffset Byte offset within indirectBuffer to read arguments from. indirectBufferOffset must be a multiple of 4.
 */
- (void)setStageInRegionWithIndirectBuffer:(id <MTLBuffer>)indirectBuffer indirectBufferOffset:(NSUInteger)indirectBufferOffset API_AVAILABLE(macos(10.14), ios(12.0));

/*
 @method dispatchThreadgroups:threadsPerThreadgroup:
 @abstract Enqueue a compute function dispatch as a multiple of the threadgroup size.
 */
- (void)dispatchThreadgroups:(MTLSize)threadgroupsPerGrid threadsPerThreadgroup:(MTLSize)threadsPerThreadgroup;

/*
 @method dispatchThreadgroupsWithIndirectBuffer:indirectBufferOffset:threadsPerThreadgroup:
 @abstract Enqueue a compute function dispatch using an indirect buffer for threadgroupsPerGrid see MTLDispatchThreadgroupsIndirectArguments.
 @param indirectBuffer A buffer object that the device will read dispatchThreadgroups arguments from, see MTLDispatchThreadgroupsIndirectArguments.
 @param indirectBufferOffset Byte offset within @a indirectBuffer to read arguments from.  @a indirectBufferOffset must be a multiple of 4.
 */
- (void)dispatchThreadgroupsWithIndirectBuffer:(id <MTLBuffer>)indirectBuffer indirectBufferOffset:(NSUInteger)indirectBufferOffset threadsPerThreadgroup:(MTLSize)threadsPerThreadgroup API_AVAILABLE(macos(10.11), ios(9.0));

/*
 @method dispatchThreads:threadsPerThreadgroup:
 @abstract Enqueue a compute function dispatch using an arbitrarily-sized grid.
 @discussion threadsPerGrid does not have to be a multiple of the  threadGroup size
 */
- (void)dispatchThreads:(MTLSize)threadsPerGrid threadsPerThreadgroup:(MTLSize)threadsPerThreadgroup API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @method updateFence:
 @abstract Update the fence to capture all GPU work so far enqueued by this encoder.
 @discussion The fence is updated at kernel submission to maintain global order and prevent deadlock.
 Drivers may delay fence updates until the end of the encoder. Drivers may also wait on fences at the beginning of an encoder. It is therefore illegal to wait on a fence after it has been updated in the same encoder.
 */
- (void)updateFence:(id <MTLFence>)fence API_AVAILABLE(macos(10.13), ios(10.0));

/*!
 @method waitForFence:
 @abstract Prevent further GPU work until the fence is reached.
 @discussion The fence is evaluated at kernel submision to maintain global order and prevent deadlock.
 Drivers may delay fence updates until the end of the encoder. Drivers may also wait on fences at the beginning of an encoder. It is therefore illegal to wait on a fence after it has been updated in the same encoder.
 */
- (void)waitForFence:(id <MTLFence>)fence API_AVAILABLE(macos(10.13), ios(10.0));


/*!
 * @method useResource:usage:
 * @abstract Declare that a resource may be accessed by the command encoder through an argument buffer
 * 
 * @discussion For tracked MTLResources, this method protects against data hazards. This method must be called before encoding any dispatch commands which may access the resource through an argument buffer.
 * @warning Prior to iOS 13, macOS 10.15, this method does not protect against data hazards. If you are deploying to older versions of macOS or iOS, use fences to ensure data hazards are resolved.
 */
- (void)useResource:(id <MTLResource>)resource usage:(MTLResourceUsage)usage API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 * @method useResources:count:usage:
 * @abstract Declare that an array of resources may be accessed through an argument buffer by the command encoder
 * @discussion For tracked MTL Resources, this method protects against data hazards. This method must be called before encoding any dispatch commands which may access the resources through an argument buffer.
 * @warning Prior to iOS 13, macOS 10.15, this method does not protect against data hazards. If you are deploying to older versions of macOS or iOS, use fences to ensure data hazards are resolved.
 */
- (void)useResources:(const id <MTLResource> __nonnull[__nonnull])resources count:(NSUInteger)count usage:(MTLResourceUsage)usage API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 * @method useHeap:
 * @abstract Declare that the resources allocated from a heap may be accessed as readonly by the render pass through an argument buffer
 * @discussion For tracked MTLHeaps, this method protects against data hazards. This method must be called before encoding any dispatch commands which may access the resources allocated from the heap through an argument buffer. This method may cause all of the color attachments allocated from the heap to become decompressed. Therefore, it is recommended that the useResource:usage: or useResources:count:usage: methods be used for color attachments instead, with a minimal (i.e. read-only) usage.
 * @warning Prior to iOS 13, macOS 10.15, this method does not protect against data hazards. If you are deploying to older versions of macOS or iOS, use fences to ensure data hazards are resolved.
 */
- (void)useHeap:(id <MTLHeap>)heap API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 * @method useHeaps:count:
 * @abstract Declare that the resources allocated from an array of heaps may be accessed as readonly by the render pass through an argument buffer
 * @discussion For tracked MTLHeaps, this method protects against data hazards. This method must be called before encoding any dispatch commands which may access the resources allocated from the heaps through an argument buffer. This method may cause all of the color attachments allocated from the heaps to become decompressed. Therefore, it is recommended that the useResource:usage: or useResources:count:usage: methods be used for color attachments instead, with a minimal (i.e. read-only) usage.
 * @warning Prior to iOS 13, macOS 10.15, this method does not protect against data hazards. If you are deploying to older versions of macOS or iOS, use fences to ensure data hazards are resolved.
 */
- (void)useHeaps:(const id <MTLHeap> __nonnull[__nonnull])heaps count:(NSUInteger)count API_AVAILABLE(macos(10.13), ios(11.0));
    

/*!
 * @method executeCommandsInBuffer:withRange:
 * @abstract Execute commands in the buffer within the range specified.
 * @discussion The same indirect command buffer may be executed any number of times within the same encoder.
 */
- (void)executeCommandsInBuffer:(id<MTLIndirectCommandBuffer>)indirectCommandBuffer withRange:(NSRange)executionRange API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos);

/*!
 * @method executeCommandsInBuffer:indirectBuffer:indirectBufferOffset:
 * @abstract Execute commands in the buffer within the range specified by the indirect range buffer.
 * @param indirectRangeBuffer An indirect buffer from which the device reads the execution range parameter, as laid out in the MTLIndirectCommandBufferExecutionRange structure.
 * @param indirectBufferOffset The byte offset within indirectBuffer where the execution range parameter is located. Must be a multiple of 4 bytes.
 * @discussion The same indirect command buffer may be executed any number of times within the same encoder.
 */
- (void)executeCommandsInBuffer:(id<MTLIndirectCommandBuffer>)indirectCommandbuffer indirectBuffer:(id<MTLBuffer>)indirectRangeBuffer indirectBufferOffset:(NSUInteger)indirectBufferOffset API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos);



/*!
 *@method memoryBarrierWithScope
 *@abstract Encodes a barrier between currently dispatched kernels in a concurrent compute command encoder and any subsequent ones on a specified resource group
 *@discussion  This API ensures that all dispatches in the encoder have completed execution and their side effects are visible to subsequent dispatches in that encoder. Calling barrier on a serial encoder is allowed, but ignored.
 */
-(void)memoryBarrierWithScope:(MTLBarrierScope)scope API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 *@method memoryBarrierWithResources
 *@abstract Encodes a barrier between currently dispatched kernels in a concurrent compute command encoder and any subsequent ones on an array of resources.
 *@discussion  This API ensures that all dispatches in the encoder have completed execution and side effects on the specified resources are visible to subsequent dispatches in that encoder. Calling barrier on a serial encoder is allowed, but ignored.
 */
- (void)memoryBarrierWithResources:(const id<MTLResource> __nonnull [__nonnull])resources count:(NSUInteger)count API_AVAILABLE(macos(10.14), ios(12.0));


@end
NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLRenderPipeline.h
//
//  MTLRenderPipeline.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Metal/MTLDefines.h>
#import <Metal/MTLDevice.h>
#import <Metal/MTLRenderCommandEncoder.h>
#import <Metal/MTLRenderPass.h>
#import <Metal/MTLPixelFormat.h>
#import <Metal/MTLArgument.h>
#import <Metal/MTLFunctionConstantValues.h>
#import <Metal/MTLPipeline.h>


NS_ASSUME_NONNULL_BEGIN
@class MTLVertexDescriptor;

typedef NS_ENUM(NSUInteger, MTLBlendFactor) {
    MTLBlendFactorZero = 0,
    MTLBlendFactorOne = 1,
    MTLBlendFactorSourceColor = 2,
    MTLBlendFactorOneMinusSourceColor = 3,
    MTLBlendFactorSourceAlpha = 4,
    MTLBlendFactorOneMinusSourceAlpha = 5,
    MTLBlendFactorDestinationColor = 6,
    MTLBlendFactorOneMinusDestinationColor = 7,
    MTLBlendFactorDestinationAlpha = 8,
    MTLBlendFactorOneMinusDestinationAlpha = 9,
    MTLBlendFactorSourceAlphaSaturated = 10,
    MTLBlendFactorBlendColor = 11,
    MTLBlendFactorOneMinusBlendColor = 12,
    MTLBlendFactorBlendAlpha = 13,
    MTLBlendFactorOneMinusBlendAlpha = 14,
    MTLBlendFactorSource1Color              API_AVAILABLE(macos(10.12), ios(10.11)) = 15,
    MTLBlendFactorOneMinusSource1Color      API_AVAILABLE(macos(10.12), ios(10.11)) = 16,
    MTLBlendFactorSource1Alpha              API_AVAILABLE(macos(10.12), ios(10.11)) = 17,
    MTLBlendFactorOneMinusSource1Alpha      API_AVAILABLE(macos(10.12), ios(10.11)) = 18,
} API_AVAILABLE(macos(10.11), ios(8.0));

typedef NS_ENUM(NSUInteger, MTLBlendOperation) {
    MTLBlendOperationAdd = 0,
    MTLBlendOperationSubtract = 1,
    MTLBlendOperationReverseSubtract = 2,
    MTLBlendOperationMin = 3,
    MTLBlendOperationMax = 4,
} API_AVAILABLE(macos(10.11), ios(8.0));

typedef NS_OPTIONS(NSUInteger, MTLColorWriteMask) {
    MTLColorWriteMaskNone  = 0,
    MTLColorWriteMaskRed   = 0x1 << 3,
    MTLColorWriteMaskGreen = 0x1 << 2,
    MTLColorWriteMaskBlue  = 0x1 << 1,
    MTLColorWriteMaskAlpha = 0x1 << 0,
    MTLColorWriteMaskAll   = 0xf
} API_AVAILABLE(macos(10.11), ios(8.0));

typedef NS_ENUM(NSUInteger, MTLPrimitiveTopologyClass) {
    MTLPrimitiveTopologyClassUnspecified = 0,
    MTLPrimitiveTopologyClassPoint = 1,
    MTLPrimitiveTopologyClassLine = 2,
    MTLPrimitiveTopologyClassTriangle = 3,
} API_AVAILABLE(macos(10.11), ios(12.0));

typedef NS_ENUM(NSUInteger, MTLTessellationPartitionMode) {
    MTLTessellationPartitionModePow2 = 0,
    MTLTessellationPartitionModeInteger = 1,
    MTLTessellationPartitionModeFractionalOdd = 2,
    MTLTessellationPartitionModeFractionalEven = 3,
} API_AVAILABLE(macos(10.12), ios(10.0));

typedef NS_ENUM(NSUInteger, MTLTessellationFactorStepFunction) {
    MTLTessellationFactorStepFunctionConstant = 0,
    MTLTessellationFactorStepFunctionPerPatch = 1,
    MTLTessellationFactorStepFunctionPerInstance = 2,
    MTLTessellationFactorStepFunctionPerPatchAndPerInstance = 3,
} API_AVAILABLE(macos(10.12), ios(10.0));

typedef NS_ENUM(NSUInteger, MTLTessellationFactorFormat) {
    MTLTessellationFactorFormatHalf = 0,
} API_AVAILABLE(macos(10.12), ios(10.0));

typedef NS_ENUM(NSUInteger, MTLTessellationControlPointIndexType) {
    MTLTessellationControlPointIndexTypeNone = 0,
    MTLTessellationControlPointIndexTypeUInt16 = 1,
    MTLTessellationControlPointIndexTypeUInt32 = 2,
} API_AVAILABLE(macos(10.12), ios(10.0));

@class MTLRenderPipelineColorAttachmentDescriptorArray;

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLRenderPipelineColorAttachmentDescriptor : NSObject <NSCopying>

/*! Pixel format.  Defaults to MTLPixelFormatInvalid */
@property (nonatomic) MTLPixelFormat pixelFormat;

/*! Enable blending.  Defaults to NO. */
@property (nonatomic, getter = isBlendingEnabled) BOOL blendingEnabled;

/*! Defaults to MTLBlendFactorOne */
@property (nonatomic) MTLBlendFactor sourceRGBBlendFactor;

/*! Defaults to MTLBlendFactorZero */
@property (nonatomic) MTLBlendFactor destinationRGBBlendFactor;

/*! Defaults to MTLBlendOperationAdd */
@property (nonatomic) MTLBlendOperation rgbBlendOperation;

/*! Defaults to MTLBlendFactorOne */
@property (nonatomic) MTLBlendFactor sourceAlphaBlendFactor;

/*! Defaults to MTLBlendFactorZero */
@property (nonatomic) MTLBlendFactor destinationAlphaBlendFactor;

/*! Defaults to MTLBlendOperationAdd */
@property (nonatomic) MTLBlendOperation alphaBlendOperation;

/* Other Options */

/*! Defaults to MTLColorWriteMaskAll */
@property (nonatomic) MTLColorWriteMask writeMask;

@end


MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLRenderPipelineReflection : NSObject

@property (nullable, readonly) NSArray <MTLArgument *> *vertexArguments;
@property (nullable, readonly) NSArray <MTLArgument *> *fragmentArguments;
@property (nullable, readonly) NSArray <MTLArgument *> *tileArguments API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);
@end

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLRenderPipelineDescriptor : NSObject <NSCopying>

@property (nullable, copy, nonatomic) NSString *label;

@property (nullable, readwrite, nonatomic, strong) id <MTLFunction> vertexFunction;
@property (nullable, readwrite, nonatomic, strong) id <MTLFunction> fragmentFunction;

@property (nullable, copy, nonatomic) MTLVertexDescriptor *vertexDescriptor;

/* Rasterization and visibility state */
@property (readwrite, nonatomic) NSUInteger sampleCount; //DEPRECATED - aliases rasterSampleCount property
@property (readwrite, nonatomic) NSUInteger rasterSampleCount;
@property (readwrite, nonatomic, getter = isAlphaToCoverageEnabled) BOOL alphaToCoverageEnabled;
@property (readwrite, nonatomic, getter = isAlphaToOneEnabled) BOOL alphaToOneEnabled;
@property (readwrite, nonatomic, getter = isRasterizationEnabled) BOOL rasterizationEnabled;



@property (readonly) MTLRenderPipelineColorAttachmentDescriptorArray *colorAttachments;

@property (nonatomic) MTLPixelFormat depthAttachmentPixelFormat;
@property (nonatomic) MTLPixelFormat stencilAttachmentPixelFormat;

@property (readwrite, nonatomic) MTLPrimitiveTopologyClass inputPrimitiveTopology API_AVAILABLE(macos(10.11), ios(12.0));

@property (readwrite, nonatomic) MTLTessellationPartitionMode tessellationPartitionMode API_AVAILABLE(macos(10.12), ios(10.0));
@property (readwrite, nonatomic) NSUInteger maxTessellationFactor API_AVAILABLE(macos(10.12), ios(10.0));
@property (readwrite, nonatomic, getter = isTessellationFactorScaleEnabled) BOOL tessellationFactorScaleEnabled API_AVAILABLE(macos(10.12), ios(10.0));
@property (readwrite, nonatomic) MTLTessellationFactorFormat tessellationFactorFormat API_AVAILABLE(macos(10.12), ios(10.0));
@property (readwrite, nonatomic) MTLTessellationControlPointIndexType tessellationControlPointIndexType API_AVAILABLE(macos(10.12), ios(10.0));
@property (readwrite, nonatomic) MTLTessellationFactorStepFunction tessellationFactorStepFunction API_AVAILABLE(macos(10.12), ios(10.0));
@property (readwrite, nonatomic) MTLWinding tessellationOutputWindingOrder API_AVAILABLE(macos(10.12), ios(10.0));

@property (readonly) MTLPipelineBufferDescriptorArray *vertexBuffers API_AVAILABLE(macos(10.13), ios(11.0));
@property (readonly) MTLPipelineBufferDescriptorArray *fragmentBuffers API_AVAILABLE(macos(10.13), ios(11.0));

@property (readwrite, nonatomic) BOOL supportIndirectCommandBuffers API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @method reset
 @abstract Restore all pipeline descriptor properties to their default values.
 */
- (void)reset;

@end

/*!
 @protocol MTLRenderPipelineState
 @abstract MTLRenderPipelineState represents a compiled render pipeline
 
 @discussion MTLRenderPipelineState is a compiled render pipeline and can be set on a MTLRenderCommandEncoder.
 */
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLRenderPipelineState <NSObject>

@property (nullable, readonly) NSString *label;
@property (readonly) id <MTLDevice> device;

/*!
 @property maxTotalThreadsPerThreadgroup
 @abstract The maximum total number of threads that can be in a single threadgroup.
 */
@property (readonly) NSUInteger maxTotalThreadsPerThreadgroup API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @property threadgroupSizeMatchesTileSize
 @abstract Returns true when the pipeline state requires a threadgroup size equal to the tile size
 */
@property (readonly) BOOL threadgroupSizeMatchesTileSize API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);



/*!
 @property imageblockSampleLength
 @brief Returns imageblock memory length used by a single sample when rendered using this pipeline.
 */
@property (readonly) NSUInteger imageblockSampleLength API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @method imageblockMemoryLengthForDimensions:sampleCount:
 @brief Returns imageblock memory length for given image block dimensions. Dimensions must be valid tile dimensions.
 */
- (NSUInteger)imageblockMemoryLengthForDimensions:(MTLSize)imageblockDimensions API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);


@property (readonly) BOOL supportIndirectCommandBuffers API_AVAILABLE(macos(10.14), ios(12.0));

@end

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLRenderPipelineColorAttachmentDescriptorArray : NSObject

/* Individual attachment state access */
- (MTLRenderPipelineColorAttachmentDescriptor *)objectAtIndexedSubscript:(NSUInteger)attachmentIndex;

/* This always uses 'copy' semantics.  It is safe to set the attachment state at any legal index to nil, which resets that attachment descriptor state to default vaules. */
- (void)setObject:(nullable MTLRenderPipelineColorAttachmentDescriptor *)attachment atIndexedSubscript:(NSUInteger)attachmentIndex;

@end


MTL_EXPORT API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac)
@interface MTLTileRenderPipelineColorAttachmentDescriptor : NSObject <NSCopying>

/*! Pixel format.  Defaults to MTLPixelFormatInvalid */
@property (nonatomic) MTLPixelFormat pixelFormat;

@end

MTL_EXPORT API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac)
@interface MTLTileRenderPipelineColorAttachmentDescriptorArray : NSObject

/* Individual tile attachment state access */
- (MTLTileRenderPipelineColorAttachmentDescriptor*)objectAtIndexedSubscript:(NSUInteger)attachmentIndex;

/* This always uses 'copy' semantics.  It is safe to set the attachment state at any legal index to nil, which resets that attachment descriptor state to default vaules. */
- (void)setObject:(MTLTileRenderPipelineColorAttachmentDescriptor*)attachment atIndexedSubscript:(NSUInteger)attachmentIndex;

@end

MTL_EXPORT API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac)
@interface MTLTileRenderPipelineDescriptor : NSObject <NSCopying>

/*!
 @property label:
 @abstract The descriptor label.
 */
@property (copy, nonatomic, nullable) NSString *label;

/*!
 @property tileFunction:
 @abstract  The kernel or fragment function that serves as the tile shader for this pipeline.
 @discussion Both kernel-based and fragment-based tile pipelines dispatches will barrier against previous
 draws and other dispatches. Kernel-based pipelines will wait until all prior access to the tile completes.
 Fragment-based pipelines will only wait until all prior access to the fragment's location completes.
 */
@property (readwrite, nonatomic, strong) id <MTLFunction> tileFunction;

/* Rasterization and visibility state */
@property (readwrite, nonatomic) NSUInteger rasterSampleCount;
@property (readonly) MTLTileRenderPipelineColorAttachmentDescriptorArray *colorAttachments;

/*!
 @property threadgroupSizeMatchesTileSize:
 @abstract Whether all threadgroups associated with this pipeline will cover tiles entirely.
 @discussion Metal can optimize code generation for this case.
 */
@property (readwrite, nonatomic) BOOL threadgroupSizeMatchesTileSize;

@property (readonly) MTLPipelineBufferDescriptorArray *tileBuffers API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @property maxTotalThreadsPerThreadgroup
 @abstract Optional property. Set the maxTotalThreadsPerThreadgroup. If it is not set, returns zero.
 */
@property (readwrite, nonatomic) NSUInteger maxTotalThreadsPerThreadgroup API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, uikitformac);

- (void)reset;

@end



NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLCommandBuffer.h
//
//  MTLCommandBuffer.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLDevice;
@protocol MTLCommandQueue;
@protocol MTLBlitCommandEncoder;
@protocol MTLRenderCommandEncoder;
@protocol MTLParallelRenderCommandEncoder;
@protocol MTLComputeCommandEncoder;
@protocol MTLCommandQueue;
@protocol MTLDrawable;
@protocol MTLCommandBuffer;
@protocol MTLEvent;
@class MTLRenderPassDescriptor;

/*!
 @enum MTLCommandBufferStatus
 
 @abstract MTLCommandBufferStatus reports the current stage in the lifetime of MTLCommandBuffer, as it proceeds to enqueued, committed, scheduled, and completed.
 
 @constant MTLCommandBufferStatusNotEnqueued
 The command buffer has not been enqueued yet.
 
 @constant MTLCommandBufferStatusEnqueued
 This command buffer is enqueued, but not committed.
 
 @constant MTLCommandBufferStatusCommitted
 Commited to its command queue, but not yet scheduled for execution.
 
 @constant MTLCommandBufferStatusScheduled
 All dependencies have been resolved and the command buffer has been scheduled for execution.
 
 @constant MTLCommandBufferStatusCompleted
 The command buffer has finished executing successfully: any blocks set with -addCompletedHandler: may now be called.
 
 @constant MTLCommandBufferStatusError
 Execution of the command buffer was aborted due to an error during execution.  Check -error for more information.
 */
typedef NS_ENUM(NSUInteger, MTLCommandBufferStatus) {
    MTLCommandBufferStatusNotEnqueued = 0,
    MTLCommandBufferStatusEnqueued = 1,
    MTLCommandBufferStatusCommitted = 2,
    MTLCommandBufferStatusScheduled = 3,
    MTLCommandBufferStatusCompleted = 4,
    MTLCommandBufferStatusError = 5,
} API_AVAILABLE(macos(10.11), ios(8.0));

 /*!
 @constant MTLCommandBufferErrorDomain
 @abstract An error domain for NSError objects produced by MTLCommandBuffer
 */
API_AVAILABLE(macos(10.11), ios(8.0))
MTL_EXTERN NSErrorDomain const MTLCommandBufferErrorDomain;

/*!
 @enum MTLCommandBufferError
 @abstract Error codes that can be found in MTLCommandBuffer.error
 
 @constant MTLCommandBufferErrorInternal
 An internal error that doesn't fit into the other categories. The actual low level error code is encoded in the local description.
 
 @constant MTLCommandBufferErrorTimeout
 Execution of this command buffer took too long, execution of this command was interrupted and aborted.
 
 @constant MTLCommandBufferErrorPageFault
 Execution of this command buffer generated an unserviceable GPU page fault. This can caused by buffer read write attribute mismatch or out of boundary access.
 
 @constant MTLCommandBufferErrorBlacklisted
 Access to this device has been revoked because this client has been responsible for too many timeouts or hangs.
 
 @constant MTLCommandBufferErrorNotPermitted
 This process does not have access to use this device.
 
 @constant MTLCommandBufferErrorOutOfMemory
 Insufficient memory was available to execute this command buffer.
 
 @constant MTLCommandBufferErrorInvalidResource
 The command buffer referenced an invalid resource.  This is most commonly caused when the caller deletes a resource before executing a command buffer that refers to it.
 
 @constant MTLCommandBufferErrorMemoryless
 One or more internal resources limits reached that prevent using memoryless render pass attachments. See error string for more detail.
 
 @constant MTLCommandBufferErrorDeviceRemoved
 The device was physically removed before the command could finish execution
 */

typedef NS_ENUM(NSUInteger, MTLCommandBufferError)
{
    MTLCommandBufferErrorNone = 0,
    MTLCommandBufferErrorInternal = 1,
    MTLCommandBufferErrorTimeout = 2,
    MTLCommandBufferErrorPageFault = 3,
    MTLCommandBufferErrorBlacklisted = 4,
    MTLCommandBufferErrorNotPermitted = 7,
    MTLCommandBufferErrorOutOfMemory = 8,
    MTLCommandBufferErrorInvalidResource = 9,
    MTLCommandBufferErrorMemoryless API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, uikitformac) = 10,
    MTLCommandBufferErrorDeviceRemoved API_AVAILABLE(macos(10.13)) API_UNAVAILABLE(ios) = 11,
} API_AVAILABLE(macos(10.11), ios(8.0));

typedef void (^MTLCommandBufferHandler)(id <MTLCommandBuffer>);

/*!
 @enum MTLDispatchType
 
 @abstract MTLDispatchType Describes how a command encoder will execute dispatched work.
 
 @constant MTLDispatchTypeSerial
 Command encoder dispatches are executed in dispatched order.
 
 @constant MTLDispatchTypeConcurrent
 Command encoder dispatches are executed in parallel with each other. 
*/

typedef NS_ENUM(NSUInteger, MTLDispatchType){
    MTLDispatchTypeSerial,
    MTLDispatchTypeConcurrent,
}API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @protocol MTLCommandBuffer
 @abstract A serial list of commands for the device to execute.
 */
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLCommandBuffer <NSObject>

/*!
 @property device
 @abstract The device this resource was created against.
 */
@property (readonly) id <MTLDevice> device;

/*!
 @property commandQueue
 @abstract The command queue this command buffer was created from.
 */
@property (readonly) id <MTLCommandQueue> commandQueue;

/*!
 @property retainedReferences
 @abstract If YES, this command buffer holds strong references to objects needed to execute this command buffer.
 */
@property (readonly) BOOL retainedReferences;

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, copy, atomic) NSString *label;

@property (readonly) CFTimeInterval kernelStartTime API_AVAILABLE(macos(10.15), uikitformac(13.0), ios(10.3));
@property (readonly) CFTimeInterval kernelEndTime API_AVAILABLE(macos(10.15), uikitformac(13.0), ios(10.3));

/*!
 @property GPUStartTime
 @abstract The host time in seconds that GPU starts executing this command buffer. Returns zero if it has not started. This usually can be called in command buffer completion handler.
 */
@property (readonly) CFTimeInterval GPUStartTime API_AVAILABLE(macos(10.15), uikitformac(13.0), ios(10.3));
/*!
 @property GPUEndTime
 @abstract The host time in seconds that GPU finishes executing this command buffer. Returns zero if CPU has not received completion notification. This usually can be called in command buffer completion handler.
 */
@property (readonly) CFTimeInterval GPUEndTime API_AVAILABLE(macos(10.15), uikitformac(13.0), ios(10.3));

/*!
 @method enqueue
 @abstract Append this command buffer to the end of its MTLCommandQueue.
*/
- (void)enqueue;

/*!
 @method commit
 @abstract Commit a command buffer so it can be executed as soon as possible.
 */
- (void)commit;

/*!
 @method addScheduledHandler:block:
 @abstract Adds a block to be called when this command buffer has been scheduled for execution.
 */
- (void)addScheduledHandler:(MTLCommandBufferHandler)block;

/*!
 @method presentDrawable:
 @abstract Add a drawable present that will be invoked when this command buffer has been scheduled for execution.
 @discussion The submission thread will be lock stepped with present call been serviced by window server
 */
- (void)presentDrawable:(id <MTLDrawable>)drawable;

/*!
 @method presentDrawable:atTime:
 @abstract Add a drawable present for a specific host time that will be invoked when this command buffer has been scheduled for execution.
 @discussion The submission thread will be lock stepped with present call been serviced by window server
*/
- (void)presentDrawable:(id <MTLDrawable>)drawable atTime:(CFTimeInterval)presentationTime;

/*!
 @method presentDrawable:afterMinimumDuration:
 @abstract Add a drawable present for a specific host time that allows previous frame to be on screen for at least duration time.
 @param drawable The drawable to be presented
 @param duration The minimum time that previous frame should be displayed. The time is double preceision floating point in the unit of seconds.
 @discussion The difference of this API versus presentDrawable:atTime is that this API defers calculation of the presentation time until the previous frame's actual presentation time is known, thus to be able to maintain a more consistent and stable frame time. This also provides an easy way to set frame rate.
    The submission thread will be lock stepped with present call been serviced by window server 
 */
- (void)presentDrawable:(id <MTLDrawable>)drawable afterMinimumDuration:(CFTimeInterval)duration;

/*!
 @method waitUntilScheduled
 @abstract Synchronously wait for this command buffer to be scheduled.
 */
- (void)waitUntilScheduled;

/*!
 @method addCompletedHandler:block:
 @abstract Add a block to be called when this command buffer has completed execution.
 */
- (void)addCompletedHandler:(MTLCommandBufferHandler)block;

/*!
 @method waitUntilCompleted
 @abstract Synchronously wait for this command buffer to complete.
 */
- (void)waitUntilCompleted;

/*!
 @property status
 @abstract status reports the current stage in the lifetime of MTLCommandBuffer, as it proceeds to enqueued, committed, scheduled, and completed.
 */
@property (readonly) MTLCommandBufferStatus status;

/*!
 @property error
 @abstract If an error occurred during execution, the NSError may contain more details about the problem.
 */
@property (nullable, readonly) NSError *error;

/*!
 @method blitCommandEncoder
 @abstract returns a blit command encoder to encode into this command buffer.
 */
- (nullable id <MTLBlitCommandEncoder>)blitCommandEncoder;

/*!
 @method renderCommandEncoderWithDescriptor:
 @abstract returns a render command endcoder to encode into this command buffer.
 */
- (nullable id <MTLRenderCommandEncoder>)renderCommandEncoderWithDescriptor:(MTLRenderPassDescriptor *)renderPassDescriptor;

/*!
 @method computeCommandEncoder
 @abstract returns a compute command encoder to encode into this command buffer.
 */
- (nullable id <MTLComputeCommandEncoder>)computeCommandEncoder;
/*! 
 @method computeCommandEncoderWithDispatchType
 @abstract returns a compute command encoder to encode into this command buffer. Optionally allow this command encoder to execute dispatches concurrently.
 @discussion On devices that do not support concurrent command encoders, this call is equivalent to computeCommandEncoder
 */

 - (nullable id<MTLComputeCommandEncoder>)computeCommandEncoderWithDispatchType:(MTLDispatchType) dispatchType API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @method encodeWaitForEvent:value:
 @abstract Encodes a command that pauses execution of this command buffer until the specified event reaches a given value.
 @discussion This method may only be called if there is no current command encoder on the receiver.
*/
- (void)encodeWaitForEvent:(id <MTLEvent>)event value:(uint64_t)value API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @method encodeSignalEvent:value:
 @abstract Encodes a command that signals an event with a given value.
 @discussion This method may only be called if there is no current command encoder on the receiver.
 */
- (void)encodeSignalEvent:(id <MTLEvent>)event value:(uint64_t)value API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @method parallelRenderCommandEncoderWithDescriptor:
 @abstract returns a parallel render pass encoder to encode into this command buffer.
 */
- (nullable id <MTLParallelRenderCommandEncoder>)parallelRenderCommandEncoderWithDescriptor:(MTLRenderPassDescriptor *)renderPassDescriptor;


/*!
 @method pushDebugGroup:
 @abstract Push a new named string onto a stack of string labels.
 */
- (void)pushDebugGroup:(NSString *)string API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @method popDebugGroup
 @abstract Pop the latest named string off of the stack.
 */
- (void)popDebugGroup API_AVAILABLE(macos(10.13), ios(11.0));


@end
NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLPixelFormat.h
//
//  MTLPixelFormat.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSUInteger, MTLPixelFormat)
{
    MTLPixelFormatInvalid = 0,

    /* Normal 8 bit formats */
    
    MTLPixelFormatA8Unorm      = 1,
    
    MTLPixelFormatR8Unorm                            = 10,
    MTLPixelFormatR8Unorm_sRGB API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 11,

    MTLPixelFormatR8Snorm      = 12,
    MTLPixelFormatR8Uint       = 13,
    MTLPixelFormatR8Sint       = 14,
    
    /* Normal 16 bit formats */

    MTLPixelFormatR16Unorm     = 20,
    MTLPixelFormatR16Snorm     = 22,
    MTLPixelFormatR16Uint      = 23,
    MTLPixelFormatR16Sint      = 24,
    MTLPixelFormatR16Float     = 25,

    MTLPixelFormatRG8Unorm                            = 30,
    MTLPixelFormatRG8Unorm_sRGB API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 31,
    MTLPixelFormatRG8Snorm                            = 32,
    MTLPixelFormatRG8Uint                             = 33,
    MTLPixelFormatRG8Sint                             = 34,

    /* Packed 16 bit formats */
    
    MTLPixelFormatB5G6R5Unorm API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 40,
    MTLPixelFormatA1BGR5Unorm API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 41,
    MTLPixelFormatABGR4Unorm  API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 42,
    MTLPixelFormatBGR5A1Unorm API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 43,

    /* Normal 32 bit formats */

    MTLPixelFormatR32Uint  = 53,
    MTLPixelFormatR32Sint  = 54,
    MTLPixelFormatR32Float = 55,

    MTLPixelFormatRG16Unorm  = 60,
    MTLPixelFormatRG16Snorm  = 62,
    MTLPixelFormatRG16Uint   = 63,
    MTLPixelFormatRG16Sint   = 64,
    MTLPixelFormatRG16Float  = 65,

    MTLPixelFormatRGBA8Unorm      = 70,
    MTLPixelFormatRGBA8Unorm_sRGB = 71,
    MTLPixelFormatRGBA8Snorm      = 72,
    MTLPixelFormatRGBA8Uint       = 73,
    MTLPixelFormatRGBA8Sint       = 74,
    
    MTLPixelFormatBGRA8Unorm      = 80,
    MTLPixelFormatBGRA8Unorm_sRGB = 81,

    /* Packed 32 bit formats */

    MTLPixelFormatRGB10A2Unorm = 90,
    MTLPixelFormatRGB10A2Uint  = 91,

    MTLPixelFormatRG11B10Float = 92,
    MTLPixelFormatRGB9E5Float = 93,

    MTLPixelFormatBGR10A2Unorm  API_AVAILABLE(macos(10.13), ios(11.0)) = 94,

    MTLPixelFormatBGR10_XR      API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, uikitformac) = 554,
    MTLPixelFormatBGR10_XR_sRGB API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, uikitformac) = 555,

    /* Normal 64 bit formats */

    MTLPixelFormatRG32Uint  = 103,
    MTLPixelFormatRG32Sint  = 104,
    MTLPixelFormatRG32Float = 105,

    MTLPixelFormatRGBA16Unorm  = 110,
    MTLPixelFormatRGBA16Snorm  = 112,
    MTLPixelFormatRGBA16Uint   = 113,
    MTLPixelFormatRGBA16Sint   = 114,
    MTLPixelFormatRGBA16Float  = 115,

    MTLPixelFormatBGRA10_XR      API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, uikitformac) = 552,
    MTLPixelFormatBGRA10_XR_sRGB API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, uikitformac) = 553,

    /* Normal 128 bit formats */

    MTLPixelFormatRGBA32Uint  = 123,
    MTLPixelFormatRGBA32Sint  = 124,
    MTLPixelFormatRGBA32Float = 125,

    /* Compressed formats. */

    /* S3TC/DXT */
    MTLPixelFormatBC1_RGBA              API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios) = 130,
    MTLPixelFormatBC1_RGBA_sRGB         API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios) = 131,
    MTLPixelFormatBC2_RGBA              API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios) = 132,
    MTLPixelFormatBC2_RGBA_sRGB         API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios) = 133,
    MTLPixelFormatBC3_RGBA              API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios) = 134,
    MTLPixelFormatBC3_RGBA_sRGB         API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios) = 135,

    /* RGTC */
    MTLPixelFormatBC4_RUnorm            API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios) = 140,
    MTLPixelFormatBC4_RSnorm            API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios) = 141,
    MTLPixelFormatBC5_RGUnorm           API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios) = 142,
    MTLPixelFormatBC5_RGSnorm           API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios) = 143,

    /* BPTC */
    MTLPixelFormatBC6H_RGBFloat         API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios) = 150,
    MTLPixelFormatBC6H_RGBUfloat        API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios) = 151,
    MTLPixelFormatBC7_RGBAUnorm         API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios) = 152,
    MTLPixelFormatBC7_RGBAUnorm_sRGB    API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios) = 153,

    /* PVRTC */
    MTLPixelFormatPVRTC_RGB_2BPP        API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 160,
    MTLPixelFormatPVRTC_RGB_2BPP_sRGB   API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 161,
    MTLPixelFormatPVRTC_RGB_4BPP        API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 162,
    MTLPixelFormatPVRTC_RGB_4BPP_sRGB   API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 163,
    MTLPixelFormatPVRTC_RGBA_2BPP       API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 164,
    MTLPixelFormatPVRTC_RGBA_2BPP_sRGB  API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 165,
    MTLPixelFormatPVRTC_RGBA_4BPP       API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 166,
    MTLPixelFormatPVRTC_RGBA_4BPP_sRGB  API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 167,

    /* ETC2 */
    MTLPixelFormatEAC_R11Unorm          API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 170,
    MTLPixelFormatEAC_R11Snorm          API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 172,
    MTLPixelFormatEAC_RG11Unorm         API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 174,
    MTLPixelFormatEAC_RG11Snorm         API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 176,
    MTLPixelFormatEAC_RGBA8             API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 178,
    MTLPixelFormatEAC_RGBA8_sRGB        API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 179,

    MTLPixelFormatETC2_RGB8             API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 180,
    MTLPixelFormatETC2_RGB8_sRGB        API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 181,
    MTLPixelFormatETC2_RGB8A1           API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 182,
    MTLPixelFormatETC2_RGB8A1_sRGB      API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 183,

    /* ASTC */
    MTLPixelFormatASTC_4x4_sRGB         API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 186,
    MTLPixelFormatASTC_5x4_sRGB         API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 187,
    MTLPixelFormatASTC_5x5_sRGB         API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 188,
    MTLPixelFormatASTC_6x5_sRGB         API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 189,
    MTLPixelFormatASTC_6x6_sRGB         API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 190,
    MTLPixelFormatASTC_8x5_sRGB         API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 192,
    MTLPixelFormatASTC_8x6_sRGB         API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 193,
    MTLPixelFormatASTC_8x8_sRGB         API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 194,
    MTLPixelFormatASTC_10x5_sRGB        API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 195,
    MTLPixelFormatASTC_10x6_sRGB        API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 196,
    MTLPixelFormatASTC_10x8_sRGB        API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 197,
    MTLPixelFormatASTC_10x10_sRGB       API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 198,
    MTLPixelFormatASTC_12x10_sRGB       API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 199,
    MTLPixelFormatASTC_12x12_sRGB       API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 200,

    MTLPixelFormatASTC_4x4_LDR          API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 204,
    MTLPixelFormatASTC_5x4_LDR          API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 205,
    MTLPixelFormatASTC_5x5_LDR          API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 206,
    MTLPixelFormatASTC_6x5_LDR          API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 207,
    MTLPixelFormatASTC_6x6_LDR          API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 208,
    MTLPixelFormatASTC_8x5_LDR          API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 210,
    MTLPixelFormatASTC_8x6_LDR          API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 211,
    MTLPixelFormatASTC_8x8_LDR          API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 212,
    MTLPixelFormatASTC_10x5_LDR         API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 213,
    MTLPixelFormatASTC_10x6_LDR         API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 214,
    MTLPixelFormatASTC_10x8_LDR         API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 215,
    MTLPixelFormatASTC_10x10_LDR        API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 216,
    MTLPixelFormatASTC_12x10_LDR        API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 217,
    MTLPixelFormatASTC_12x12_LDR        API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, uikitformac) = 218,
    
    
    /*!
     @constant MTLPixelFormatGBGR422
     @abstract A pixel format where the red and green channels are subsampled horizontally.  Two pixels are stored in 32 bits, with shared red and blue values, and unique green values.
     @discussion This format is equivalent to YUY2, YUYV, yuvs, or GL_RGB_422_APPLE/GL_UNSIGNED_SHORT_8_8_REV_APPLE.   The component order, from lowest addressed byte to highest, is Y0, Cb, Y1, Cr.  There is no implicit colorspace conversion from YUV to RGB, the shader will receive (Cr, Y, Cb, 1).  422 textures must have a width that is a multiple of 2, and can only be used for 2D non-mipmap textures.  When sampling, ClampToEdge is the only usable wrap mode.
     */
    MTLPixelFormatGBGR422 = 240,

    /*!
     @constant MTLPixelFormatBGRG422
     @abstract A pixel format where the red and green channels are subsampled horizontally.  Two pixels are stored in 32 bits, with shared red and blue values, and unique green values.
     @discussion This format is equivalent to UYVY, 2vuy, or GL_RGB_422_APPLE/GL_UNSIGNED_SHORT_8_8_APPLE. The component order, from lowest addressed byte to highest, is Cb, Y0, Cr, Y1.  There is no implicit colorspace conversion from YUV to RGB, the shader will receive (Cr, Y, Cb, 1).  422 textures must have a width that is a multiple of 2, and can only be used for 2D non-mipmap textures.  When sampling, ClampToEdge is the only usable wrap mode.
     */
    MTLPixelFormatBGRG422 = 241,

    /* Depth */

    MTLPixelFormatDepth16Unorm          API_AVAILABLE(macos(10.12), ios(13.0)) = 250,
    MTLPixelFormatDepth32Float  = 252,

    /* Stencil */

    MTLPixelFormatStencil8        = 253,

    /* Depth Stencil */
    
    MTLPixelFormatDepth24Unorm_Stencil8  API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios) = 255,
    MTLPixelFormatDepth32Float_Stencil8  API_AVAILABLE(macos(10.11), ios(9.0)) = 260,

    MTLPixelFormatX32_Stencil8  API_AVAILABLE(macos(10.12), ios(10.0)) = 261,
    MTLPixelFormatX24_Stencil8  API_AVAILABLE(macos(10.12), uikitformac(13.0)) API_UNAVAILABLE(ios) = 262,

} API_AVAILABLE(macos(10.11), ios(8.0));

NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLBlitCommandEncoder.h
//
//  MTLBlitCommandEncoder.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLTypes.h>
#import <Metal/MTLCommandEncoder.h>
#import <Metal/MTLBuffer.h>
#import <Metal/MTLTexture.h>
#import <Metal/MTLFence.h>
#import <Metal/MTLRenderPass.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 @header MTLBlitCommandEncoder.h
 @discussion Header file for MTLBlitCommandEncoder
 */

/*!
 @enum MTLBlitOption
 @abstract Controls the blit operation
 */
typedef NS_OPTIONS(NSUInteger, MTLBlitOption)
{
    MTLBlitOptionNone                       = 0,
    MTLBlitOptionDepthFromDepthStencil      = 1 << 0,
    MTLBlitOptionStencilFromDepthStencil    = 1 << 1,
    MTLBlitOptionRowLinearPVRTC API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, uikitformac) = 1 << 2,
} API_AVAILABLE(macos(10.11), ios(9.0));


/*!
 @protocol MTLBlitCommandEncoder
 @abstract A command encoder that performs basic copies and blits between buffers and textures.
 */
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLBlitCommandEncoder <MTLCommandEncoder>

/*!
 @method synchronizeResource:
 @abstract Flush any copy of this resource from the device's caches, and invalidate any CPU caches if needed.
 @param resource The resource to page off.
 @discussion When the device writes to a resource with a storage mode of MTLResourceStorageModeManaged, those writes may be cached (for example, in VRAM or on chip renderer cache),
 making any CPU access (either MTLBuffer.contents or -[MTLTexture getBytes:...] and -[MTLTexture replaceRegion:]) produce undefined results.  To allow the CPU to see what the device
 has written, a CommandBuffer containing this synchronization must be executed.  After completion of the CommandBuffer, the CPU can access the contents of the resource safely.
 */
- (void)synchronizeResource:(id<MTLResource>)resource API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios);

/*!
 @method synchronizeTexture:slice:mipmapLevel:
 @abstract Flush any copy of this image from the device's caches, and invalidate CPU caches if needed.
 @param texture The texture to page off.
 @param slice The slice of the texture to page off.
 @param level The mipmap level of the texture to flush.
 @discussion
 See the discussion of -synchronizeResource.   -synchronizeTexture:slice:mipmapLevel performs the same role, except it may flush only a subset of the texture storage, rather than the entire texture.
 */
- (void)synchronizeTexture:(id<MTLTexture>)texture slice:(NSUInteger)slice level:(NSUInteger)level API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios);

/*!
 @method copyFromTexture:sourceSlice:sourceLevel:sourceOrigin:sourceSize:toTexture:destinationSlice:destinationLevel:destinationOrigin:
 @abstract Copy a rectangle of pixels between textures.
 */
- (void)copyFromTexture:(id<MTLTexture>)sourceTexture sourceSlice:(NSUInteger)sourceSlice sourceLevel:(NSUInteger)sourceLevel sourceOrigin:(MTLOrigin)sourceOrigin sourceSize:(MTLSize)sourceSize toTexture:(id<MTLTexture>)destinationTexture destinationSlice:(NSUInteger)destinationSlice destinationLevel:(NSUInteger)destinationLevel destinationOrigin:(MTLOrigin)destinationOrigin;

/*!
 @method copyFromBuffer:sourceOffset:sourceBytesPerRow:sourceBytesPerImage:sourceSize:toTexture:destinationSlice:destinationLevel:destinationOrigin:
 @abstract Copy an image from a buffer into a texture.
 */
- (void)copyFromBuffer:(id<MTLBuffer>)sourceBuffer sourceOffset:(NSUInteger)sourceOffset sourceBytesPerRow:(NSUInteger)sourceBytesPerRow sourceBytesPerImage:(NSUInteger)sourceBytesPerImage sourceSize:(MTLSize)sourceSize toTexture:(id<MTLTexture>)destinationTexture destinationSlice:(NSUInteger)destinationSlice destinationLevel:(NSUInteger)destinationLevel destinationOrigin:(MTLOrigin)destinationOrigin;

/*!
 @method copyFromBuffer:sourceOffset:sourceBytesPerRow:sourceBytesPerImage:sourceSize:toTexture:destinationSlice:destinationLevel:destinationOrigin:options:
 @abstract Copy an image from a buffer into a texture.
 */
- (void)copyFromBuffer:(id<MTLBuffer>)sourceBuffer sourceOffset:(NSUInteger)sourceOffset sourceBytesPerRow:(NSUInteger)sourceBytesPerRow sourceBytesPerImage:(NSUInteger)sourceBytesPerImage sourceSize:(MTLSize)sourceSize toTexture:(id<MTLTexture>)destinationTexture destinationSlice:(NSUInteger)destinationSlice destinationLevel:(NSUInteger)destinationLevel destinationOrigin:(MTLOrigin)destinationOrigin options:(MTLBlitOption)options API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method copyFromTexture:sourceSlice:sourceLevel:sourceOrigin:sourceSize:toBuffer:destinationOffset:destinationBytesPerRow:destinationBytesPerImage:
 @abstract Copy an image from a texture into a buffer.
 */
- (void)copyFromTexture:(id<MTLTexture>)sourceTexture sourceSlice:(NSUInteger)sourceSlice sourceLevel:(NSUInteger)sourceLevel sourceOrigin:(MTLOrigin)sourceOrigin sourceSize:(MTLSize)sourceSize toBuffer:(id<MTLBuffer>)destinationBuffer destinationOffset:(NSUInteger)destinationOffset destinationBytesPerRow:(NSUInteger)destinationBytesPerRow destinationBytesPerImage:(NSUInteger)destinationBytesPerImage;

/*!
 @method copyFromTexture:sourceSlice:sourceLevel:sourceOrigin:sourceSize:sourceOptions:toBuffer:destinationOffset:destinationBytesPerRow:destinationBytesPerImage:options:
 @abstract Copy an image from a texture into a buffer.
 */
- (void)copyFromTexture:(id<MTLTexture>)sourceTexture sourceSlice:(NSUInteger)sourceSlice sourceLevel:(NSUInteger)sourceLevel sourceOrigin:(MTLOrigin)sourceOrigin sourceSize:(MTLSize)sourceSize toBuffer:(id<MTLBuffer>)destinationBuffer destinationOffset:(NSUInteger)destinationOffset destinationBytesPerRow:(NSUInteger)destinationBytesPerRow destinationBytesPerImage:(NSUInteger)destinationBytesPerImage options:(MTLBlitOption)options API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method generateMipmapsForTexture:
 @abstract Generate mipmaps for a texture from the base level up to the max level.
 */
- (void)generateMipmapsForTexture:(id<MTLTexture>)texture;

/*!
 @method fillBuffer:range:value:
 @abstract Fill a buffer with a fixed value in each byte.
 */
- (void)fillBuffer:(id<MTLBuffer>)buffer range:(NSRange)range value:(uint8_t)value;


/*!
 @method copyFromTexture:sourceSlice:sourceLevel:toTexture:destinationSlice:destinationLevel:sliceCount:levelCount:
 @abstract Copy whole surfaces between textures.
 @discussion Convenience function to copy sliceCount * levelCount whole surfaces between textures
 The source and destination pixel format must be identical.
 The source and destination sample count must be identical.
 The sourceLevel mip in sourceTexture must have the same dimension as the destinationLevel mip in destinationTexture.
 The sourceTexture must have at least sourceLevel + levelCount mips
 The destinationTexture must have at least destinationLevel + levelCount mips
 The sourceTexture must have at least sourceSlice + sliceCount array slices
 The destinationTexture must have at least destinationSlice + sliceCount array slices
 */
- (void)copyFromTexture:(id<MTLTexture>)sourceTexture sourceSlice:(NSUInteger)sourceSlice sourceLevel:(NSUInteger)sourceLevel
              toTexture:(id<MTLTexture>)destinationTexture destinationSlice:(NSUInteger)destinationSlice destinationLevel:(NSUInteger)destinationLevel
             sliceCount:(NSUInteger)sliceCount levelCount:(NSUInteger)levelCount API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method copyFromTexture:toTexture:
 @abstract Copy as many whole surfaces as possible between textures.
 @discussion Convenience function that calls copyFromTexture:sourceSlice:sourceLevel:toTexture:destinationSlice:destinationLevel:sliceCount:levelCount:
 The source and destination pixel format must be identical.
 The source and destination sample count must be identical.
 Either:
 - sourceTexture must have a mip M with identical dimensions as the first mip of destinationTexture: sourceLevel = M, destinationLevel = 0
 - destinationTexture must have a mip M with identical dimensions as the first mip of sourceTexture: sourceLevel = 0, destinationLevel = M
 Computes: levelCount = min(sourceTexture.mipmapLevelCount - sourceLevel, destinationTexture.mipmapLevelCount - destinationLevel)
           sliceCount = min(sourceTexture.arrayLength, destinationTexture.arrayLength)
 Then invokes the method above using the computed parameters.
 */
- (void)copyFromTexture:(id<MTLTexture>)sourceTexture toTexture:(id<MTLTexture>)destinationTexture API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method copyFromBuffer:sourceOffset:toBuffer:destinationOffset:size:
 @abstract Basic memory copy between buffers.
 */
- (void)copyFromBuffer:(id <MTLBuffer>)sourceBuffer sourceOffset:(NSUInteger)sourceOffset toBuffer:(id <MTLBuffer>)destinationBuffer destinationOffset:(NSUInteger)destinationOffset size:(NSUInteger)size;

/*!
 @method updateFence:
 @abstract Update the fence to capture all GPU work so far enqueued by this encoder.
 @discussion The fence is updated at kernel submission to maintain global order and prevent deadlock.
 Drivers may delay fence updates until the end of the encoder. Drivers may also wait on fences at the beginning of an encoder. It is therefore illegal to wait on a fence after it has been updated in the same encoder.
 */
- (void)updateFence:(id <MTLFence>)fence API_AVAILABLE(macos(10.13), ios(10.0));

/*!
 @method waitForFence:
 @abstract Prevent further GPU work until the fence is reached.
 @discussion The fence is evaluated at kernel submision to maintain global order and prevent deadlock.
 Drivers may delay fence updates until the end of the encoder. Drivers may also wait on fences at the beginning of an encoder. It is therefore illegal to wait on a fence after it has been updated in the same encoder.
 */
- (void)waitForFence:(id <MTLFence>)fence API_AVAILABLE(macos(10.13), ios(10.0));





/*!
 @method optimizeContentsForGPUAccess:
 @abstract Optimizes the texture data to ensure the best possible performance when accessing content on the GPU at the expense of CPU-access performance.
 */
- (void)optimizeContentsForGPUAccess:(id<MTLTexture>)texture API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @method optimizeContentsForGPUAccess:slice:level:
 @abstract Optimizes a subset of the texture data to ensure the best possible performance when accessing content on the GPU at the expense of CPU-access performance.
 */
- (void)optimizeContentsForGPUAccess:(id<MTLTexture>)texture slice:(NSUInteger)slice level:(NSUInteger)level API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @method optimizeContentsForCPUAccess:
 @abstract Optimizes the texture data to ensure the best possible performance when accessing content on the CPU at the expense of GPU-access performance.
 */
- (void)optimizeContentsForCPUAccess:(id<MTLTexture>)texture API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @method optimizeContentsForCPUAccess:slice:level:
 @abstract Optimizes a subset of the texture data to ensure the best possible performance when accessing content on the CPU at the expense of GPU-access performance.
 */
- (void)optimizeContentsForCPUAccess:(id<MTLTexture>)texture slice:(NSUInteger)slice level:(NSUInteger)level API_AVAILABLE(macos(10.14), ios(12.0));


/*!
 @method resetCommandsInBuffer:buffer:withRange:
 @abstract reset commands in a indirect command buffer using the GPU
 */
- (void) resetCommandsInBuffer: (id<MTLIndirectCommandBuffer>)buffer withRange:(NSRange)range API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @method copyIndirectCommandBuffer:source:sourceRange:destination:destinationIndex
 @abstract copy a region of a buffer into a destination buffer starting at destinationIndex using the GPU
 */
- (void)copyIndirectCommandBuffer:(id <MTLIndirectCommandBuffer>)source sourceRange:(NSRange)sourceRange
                      destination:(id <MTLIndirectCommandBuffer>)destination destinationIndex:(NSUInteger)destinationIndex API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 @method optimizeIndirectCommandBuffer:indirectCommandBuffer:range:
 @abstract Optimizes a subset of the texture data to ensure the best possible performance when accessing content on the CPU at the expense of GPU-access performance.
 */
- (void)optimizeIndirectCommandBuffer:(id <MTLIndirectCommandBuffer>)indirectCommandBuffer withRange:(NSRange)range API_AVAILABLE(macos(10.14), ios(12.0));


@end
NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLFunctionConstantValues.h
//
//  MTLFunctionConstantValues.h
//  Metal
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLArgument.h>


NS_ASSUME_NONNULL_BEGIN

MTL_EXPORT API_AVAILABLE(macos(10.12), ios(10.0))
@interface MTLFunctionConstantValues : NSObject <NSCopying>

// using indices
- (void)setConstantValue:(const void *)value type:(MTLDataType)type atIndex:(NSUInteger)index;
- (void)setConstantValues:(const void *)values type:(MTLDataType)type withRange:(NSRange)range;

// using names
- (void)setConstantValue:(const void *)value type:(MTLDataType)type withName:(NSString *)name;

// delete all the constants
- (void)reset;

@end

NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLVertexDescriptor.h
//
//  MTLVertexDescriptor.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Metal/MTLDefines.h>
#import <Metal/MTLDevice.h>


NS_ASSUME_NONNULL_BEGIN

/*!
 @enum MTLVertexFormat
 @abstract specifies how the vertex attribute data is laid out in memory.
*/
typedef NS_ENUM(NSUInteger, MTLVertexFormat)
{
    MTLVertexFormatInvalid = 0,
    
    MTLVertexFormatUChar2 = 1,
    MTLVertexFormatUChar3 = 2,
    MTLVertexFormatUChar4 = 3,
    
    MTLVertexFormatChar2 = 4,
    MTLVertexFormatChar3 = 5,
    MTLVertexFormatChar4 = 6,
    
    MTLVertexFormatUChar2Normalized = 7,
    MTLVertexFormatUChar3Normalized = 8,
    MTLVertexFormatUChar4Normalized = 9,
    
    MTLVertexFormatChar2Normalized = 10,
    MTLVertexFormatChar3Normalized = 11,
    MTLVertexFormatChar4Normalized = 12,
    
    MTLVertexFormatUShort2 = 13,
    MTLVertexFormatUShort3 = 14,
    MTLVertexFormatUShort4 = 15,
    
    MTLVertexFormatShort2 = 16,
    MTLVertexFormatShort3 = 17,
    MTLVertexFormatShort4 = 18,
    
    MTLVertexFormatUShort2Normalized = 19,
    MTLVertexFormatUShort3Normalized = 20,
    MTLVertexFormatUShort4Normalized = 21,
    
    MTLVertexFormatShort2Normalized = 22,
    MTLVertexFormatShort3Normalized = 23,
    MTLVertexFormatShort4Normalized = 24,
    
    MTLVertexFormatHalf2 = 25,
    MTLVertexFormatHalf3 = 26,
    MTLVertexFormatHalf4 = 27,
    
    MTLVertexFormatFloat = 28,
    MTLVertexFormatFloat2 = 29,
    MTLVertexFormatFloat3 = 30,
    MTLVertexFormatFloat4 = 31,
    
    MTLVertexFormatInt = 32,
    MTLVertexFormatInt2 = 33,
    MTLVertexFormatInt3 = 34,
    MTLVertexFormatInt4 = 35,
    
    MTLVertexFormatUInt = 36,
    MTLVertexFormatUInt2 = 37,
    MTLVertexFormatUInt3 = 38,
    MTLVertexFormatUInt4 = 39,
    
    MTLVertexFormatInt1010102Normalized = 40,
    MTLVertexFormatUInt1010102Normalized = 41,
    
    MTLVertexFormatUChar4Normalized_BGRA API_AVAILABLE(macos(10.13), ios(11.0)) = 42,
    
    MTLVertexFormatUChar API_AVAILABLE(macos(10.13), ios(11.0)) = 45,
    MTLVertexFormatChar API_AVAILABLE(macos(10.13), ios(11.0)) = 46,
    MTLVertexFormatUCharNormalized API_AVAILABLE(macos(10.13), ios(11.0)) = 47,
    MTLVertexFormatCharNormalized API_AVAILABLE(macos(10.13), ios(11.0)) = 48,
    
    MTLVertexFormatUShort API_AVAILABLE(macos(10.13), ios(11.0)) = 49,
    MTLVertexFormatShort API_AVAILABLE(macos(10.13), ios(11.0)) = 50,
    MTLVertexFormatUShortNormalized API_AVAILABLE(macos(10.13), ios(11.0)) = 51,
    MTLVertexFormatShortNormalized API_AVAILABLE(macos(10.13), ios(11.0)) = 52,
    
    MTLVertexFormatHalf API_AVAILABLE(macos(10.13), ios(11.0)) = 53,
    
} API_AVAILABLE(macos(10.11), ios(8.0));

typedef NS_ENUM(NSUInteger, MTLVertexStepFunction)
{
    MTLVertexStepFunctionConstant = 0,
    MTLVertexStepFunctionPerVertex = 1,
    MTLVertexStepFunctionPerInstance = 2,
    MTLVertexStepFunctionPerPatch API_AVAILABLE(macos(10.12), ios(10.0)) = 3,
    MTLVertexStepFunctionPerPatchControlPoint API_AVAILABLE(macos(10.12), ios(10.0)) = 4,
} API_AVAILABLE(macos(10.11), ios(8.0));

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLVertexBufferLayoutDescriptor : NSObject <NSCopying>
@property (assign, nonatomic) NSUInteger stride;
@property (assign, nonatomic) MTLVertexStepFunction stepFunction;
@property (assign, nonatomic) NSUInteger stepRate;
@end

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLVertexBufferLayoutDescriptorArray : NSObject
- (MTLVertexBufferLayoutDescriptor *)objectAtIndexedSubscript:(NSUInteger)index;
- (void)setObject:(nullable MTLVertexBufferLayoutDescriptor *)bufferDesc atIndexedSubscript:(NSUInteger)index;
@end

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLVertexAttributeDescriptor : NSObject <NSCopying>
@property (assign, nonatomic) MTLVertexFormat format;
@property (assign, nonatomic) NSUInteger offset;
@property (assign, nonatomic) NSUInteger bufferIndex;
@end

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLVertexAttributeDescriptorArray : NSObject
- (MTLVertexAttributeDescriptor *)objectAtIndexedSubscript:(NSUInteger)index;
- (void)setObject:(nullable MTLVertexAttributeDescriptor *)attributeDesc atIndexedSubscript:(NSUInteger)index;
@end

/*
 MTLVertexDescriptor
 */
MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLVertexDescriptor : NSObject <NSCopying>

+ (MTLVertexDescriptor *)vertexDescriptor;

@property (readonly) MTLVertexBufferLayoutDescriptorArray *layouts;
@property (readonly) MTLVertexAttributeDescriptorArray *attributes;

- (void)reset;

@end
NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLFence.h
//
//  MTLFence.h
//  Metal
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLDevice.h>

API_AVAILABLE(macos(10.13), ios(10.0))
@protocol MTLFence <NSObject>
@property (nonnull, readonly) id <MTLDevice> device;

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, copy, atomic) NSString *label;

@end
// ==========  Metal.framework/Headers/MTLTypes.h
//
//  MTLTypes.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>

/*!
 @struct MTLOrigin
 @abstract Identify a pixel in an image. MTLOrigin is ususally used as the upper-left corner of a region of a texture.
 */
typedef struct {
    NSUInteger x, y, z;
} MTLOrigin;

MTL_INLINE MTLOrigin MTLOriginMake(NSUInteger x, NSUInteger y, NSUInteger z)
{
    MTLOrigin origin = {x, y, z};
    return origin;
}

/*!
 @typedef MTLSize
 @abstract A set of dimensions to declare the size of an object, such as an image, texture, threadgroup, or grid.
 */
typedef struct {
    NSUInteger width, height, depth;
} MTLSize;

MTL_INLINE MTLSize MTLSizeMake(NSUInteger width, NSUInteger height, NSUInteger depth)
{
    MTLSize size = {width, height, depth};
    return size;
}

/*!
 @struct MTLRegion
 @abstract Identify a region in an image or texture.
 */

typedef struct
{
    MTLOrigin origin;
    MTLSize   size;
} MTLRegion;

MTL_INLINE MTLRegion MTLRegionMake1D(NSUInteger x, NSUInteger width)
{
    MTLRegion region;
    region.origin.x = x; region.origin.y = 0; region.origin.z = 0;
    region.size.width = width; region.size.height = 1; region.size.depth = 1;
    return region;
}

MTL_INLINE MTLRegion MTLRegionMake2D(NSUInteger x, NSUInteger y, NSUInteger width, NSUInteger height)
{
    MTLRegion region;
    region.origin.x = x; region.origin.y = y; region.origin.z = 0;
    region.size.width = width; region.size.height = height; region.size.depth = 1;
    return region;
}

MTL_INLINE MTLRegion MTLRegionMake3D(NSUInteger x, NSUInteger y, NSUInteger z, NSUInteger width, NSUInteger height, NSUInteger depth)
{
    MTLRegion region;
    region.origin.x = x; region.origin.y = y; region.origin.z = z;
    region.size.width = width; region.size.height = height; region.size.depth = depth;
    return region;
}

/*!
 @struct MTLSamplePosition
 @abstract Identify a sample within a pixel. Origin is top-left with a range [0,1) for both x and y.
 */

typedef struct {
    float x, y;
} MTLSamplePosition;

MTL_INLINE MTLSamplePosition MTLSamplePositionMake(float x, float y) API_AVAILABLE(macos(10.13), ios(11.0))
{
    MTLSamplePosition position = {x, y};
    return position;
}

// ==========  Metal.framework/Headers/MTLComputePipeline.h
//
//  MTLComputePipeline.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Metal/MTLDefines.h>
#import <Metal/MTLDevice.h>
#import <Metal/MTLArgument.h>
#import <Metal/MTLStageInputOutputDescriptor.h>
#import <Metal/MTLPipeline.h>
NS_ASSUME_NONNULL_BEGIN

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLComputePipelineReflection : NSObject

@property (readonly) NSArray <MTLArgument *> *arguments;


@end

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(9.0))
@interface MTLComputePipelineDescriptor : NSObject <NSCopying>

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, copy, nonatomic) NSString *label;

/*!
 @property computeFunction
 @abstract The function to use with the MTLComputePipelineState
 */
@property (nullable, readwrite, nonatomic, strong) id <MTLFunction> computeFunction;

/*!
 @property threadGroupSizeIsMultipleOfThreadExecutionWidth
 @abstract An optimization flag, set if the thread group size will always be a multiple of thread execution width
 */
@property (readwrite, nonatomic) BOOL threadGroupSizeIsMultipleOfThreadExecutionWidth;

/*!
 @property maxTotalThreadsPerThreadgroup
 @abstract Optional property. Set the maxTotalThreadsPerThreadgroup. If it is not set, returns zero.
 */
@property (readwrite, nonatomic) NSUInteger maxTotalThreadsPerThreadgroup API_AVAILABLE(macos(10.14), ios(12.0));


/*!
 @property computeDataDescriptor
 @abstract An MTLStageInputOutputDescriptor to fetch data from buffers
 */
@property (nullable, copy, nonatomic) MTLStageInputOutputDescriptor *stageInputDescriptor API_AVAILABLE(macos(10.12), ios(10.0));

/*!
 @property buffers
 @abstract Optional properties for each buffer binding used by the compute function.
 */
@property (readonly) MTLPipelineBufferDescriptorArray *buffers API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @property supportIndirectCommandBuffers
 @abstract This flag makes this pipeline usable with indirect command buffers.
 */
@property (readwrite, nonatomic) BOOL supportIndirectCommandBuffers API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos);
/*!
 @method reset
 @abstract Restore all compute pipeline descriptor properties to their default values.
 */
- (void)reset;

@end

/*!
 @protocol MTLComputePipelineState
 @abstract A handle to compiled code for a compute function.
 @discussion MTLComputePipelineState is a single compute function.  It can only be used with the device that it was created against.
*/
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLComputePipelineState <NSObject>

@property (nullable, readonly) NSString *label API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @property device
 @abstract The device this resource was created against.  This resource can only be used with this device.
 */
@property (readonly) id <MTLDevice> device;

/*!
 @property maxTotalThreadsPerThreadgroup
 @abstract The maximum total number of threads that can be in a single compute threadgroup.
 */
@property (readonly) NSUInteger maxTotalThreadsPerThreadgroup;

/*!
 @property threadExecutionWidth
 @abstract For most efficient execution, the threadgroup size should be a multiple of this when executing the kernel.
 */
@property (readonly) NSUInteger threadExecutionWidth;


/*!
 @property staticThreadgroupMemoryLength
 @abstract The length in bytes of threadgroup memory that is statically allocated.
 */
@property (readonly) NSUInteger staticThreadgroupMemoryLength API_AVAILABLE(macos(10.13), ios(11.0));


/*!
 @method imageblockMemoryLengthForDimensions:
 @brief Returns imageblock memory length for given image block dimensions.
 */
- (NSUInteger)imageblockMemoryLengthForDimensions:(MTLSize)imageblockDimensions API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);


/*!
 @property supportIndirectCommandBuffers
 @abstract Tells whether this pipeline state is usable through an Indirect Command Buffer.
 */
@property (readonly) BOOL supportIndirectCommandBuffers API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos);

@end

NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLEvent.h
//
//  MTLEvent.h
//  Metal
//
//  Copyright © 2018 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLDevice.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.14), ios(12.0))
@protocol MTLEvent <NSObject>

/*!
 @property device
 @abstract The device this event can be used with. Will be nil when the event is shared across devices (i.e. MTLSharedEvent).
 */
@property (nullable, readonly) id <MTLDevice> device;

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, copy, atomic) NSString *label;

@end

/*!
 @class MTLSharedEventListener
 @abstract This class provides a simple interface for handling the dispatching of MTLSharedEvent notifications from Metal.
*/
MTL_EXPORT API_AVAILABLE(macos(10.14), ios(12.0))
@interface MTLSharedEventListener : NSObject
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithDispatchQueue:(dispatch_queue_t)dispatchQueue NS_DESIGNATED_INITIALIZER;
@property (nonnull, readonly) dispatch_queue_t dispatchQueue;
@end

@class MTLSharedEventHandle;
@protocol MTLSharedEvent;

typedef void (^MTLSharedEventNotificationBlock)(id <MTLSharedEvent>, uint64_t value);

API_AVAILABLE(macos(10.14), ios(12.0))
@protocol MTLSharedEvent <MTLEvent>

// When the event's signaled value reaches value or higher, invoke the block on the dispatch queue owned by the listener.
- (void)notifyListener:(MTLSharedEventListener *)listener atValue:(uint64_t)value block:(MTLSharedEventNotificationBlock)block;

// Convenience method for creating a shared event handle that may be passed to other processes via XPC.
- (MTLSharedEventHandle *)newSharedEventHandle;

@property (readwrite) uint64_t signaledValue; // Read or set signaled value

@end


// MTLSharedEventHandle objects may be passed between processes via XPC connections and then used to recreate
// a MTLSharedEvent via an existing MTLDevice.
MTL_EXPORT API_AVAILABLE(macos(10.14), ios(12.0))
@interface MTLSharedEventHandle : NSObject <NSSecureCoding>
{
    struct MTLSharedEventHandlePrivate *_priv;
}
@property (readonly, nullable) NSString *label;
@end

NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLRenderPass.h
//
//  MTLRenderPass.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>




#import <Metal/MTLTypes.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLDevice;


typedef NS_ENUM(NSUInteger, MTLLoadAction) {
    MTLLoadActionDontCare = 0,
    MTLLoadActionLoad = 1,
    MTLLoadActionClear = 2,
} API_AVAILABLE(macos(10.11), ios(8.0));

typedef NS_ENUM(NSUInteger, MTLStoreAction) {
    MTLStoreActionDontCare = 0,
    MTLStoreActionStore = 1,
    MTLStoreActionMultisampleResolve = 2,
    MTLStoreActionStoreAndMultisampleResolve API_AVAILABLE(macos(10.12), ios(10.0)) = 3,
    MTLStoreActionUnknown API_AVAILABLE(macos(10.12), ios(10.0)) = 4,
    MTLStoreActionCustomSampleDepthStore API_AVAILABLE(macos(10.13), ios(11.0)) = 5,
} API_AVAILABLE(macos(10.11), ios(8.0));

typedef NS_OPTIONS(NSUInteger, MTLStoreActionOptions) {
    MTLStoreActionOptionNone                  = 0,
    MTLStoreActionOptionCustomSamplePositions = 1 << 0,
} API_AVAILABLE(macos(10.13), ios(11.0));

typedef struct
{
    double red;
    double green;
    double blue;
    double alpha;
} MTLClearColor;

MTL_INLINE MTLClearColor MTLClearColorMake(double red, double green, double blue, double alpha);

@protocol MTLTexture;
@protocol MTLBuffer;

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLRenderPassAttachmentDescriptor : NSObject <NSCopying>

/*!
 @property texture
 @abstract The MTLTexture object for this attachment.
 */
@property (nullable, nonatomic, strong) id <MTLTexture> texture;

/*!
 @property level
 @abstract The mipmap level of the texture to be used for rendering.  Default is zero.
 */
@property (nonatomic) NSUInteger level;

/*!
 @property slice
 @abstract The slice of the texture to be used for rendering.  Default is zero.
 */
@property (nonatomic) NSUInteger slice;

/*!
 @property depthPlane
 @abstract The depth plane of the texture to be used for rendering.  Default is zero.
 */
@property (nonatomic) NSUInteger depthPlane;

/*!
 @property resolveTexture
 @abstract The texture used for multisample resolve operations.  Only used (and required)
 if the store action is set to MTLStoreActionMultisampleResolve.
 */
@property (nullable, nonatomic, strong) id <MTLTexture> resolveTexture;

/*!
 @property resolveLevel
 @abstract The mipmap level of the resolve texture to be used for multisample resolve.  Defaults to zero.
 */
@property (nonatomic) NSUInteger resolveLevel;

/*!
 @property resolveLevel
 @abstract The texture slice of the resolve texture to be used for multisample resolve.  Defaults to zero.
 */
@property (nonatomic) NSUInteger resolveSlice;

/*!
 @property resolveDepthPlane
 @abstract The texture depth plane of the resolve texture to be used for multisample resolve.  Defaults to zero.
 */
@property (nonatomic) NSUInteger resolveDepthPlane;

/*!
 @property loadAction
 @abstract The action to be performed with this attachment at the beginning of a render pass.  Default is
 MTLLoadActionDontCare unless specified by a creation or init method.
 */
@property (nonatomic) MTLLoadAction loadAction;

/*!
 @property storeAction
 @abstract The action to be performed with this attachment at the end of a render pass.  Default is
 MTLStoreActionDontCare unless specified by a creation or init method.
 */
@property (nonatomic) MTLStoreAction storeAction;

/*!
 @property storeActionOptions
 @abstract Optional configuration for the store action performed with this attachment at the end of a render pass.  Default is
 MTLStoreActionOptionNone.
 */
@property (nonatomic) MTLStoreActionOptions storeActionOptions API_AVAILABLE(macos(10.13), ios(11.0));

@end

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLRenderPassColorAttachmentDescriptor : MTLRenderPassAttachmentDescriptor

/*!
 @property clearColor
 @abstract The clear color to be used if the loadAction property is MTLLoadActionClear
 */
@property (nonatomic) MTLClearColor clearColor;

@end

/*!
 @enum MTLMultisampleDepthResolveFilter
 @abstract Controls the MSAA depth resolve operation. Supported on iOS GPU Family 3 and later.
 */
typedef NS_ENUM(NSUInteger, MTLMultisampleDepthResolveFilter)
{
    MTLMultisampleDepthResolveFilterSample0 = 0,
    MTLMultisampleDepthResolveFilterMin = 1,
    MTLMultisampleDepthResolveFilterMax = 2,
} API_AVAILABLE(macos(10.14), ios(9.0));

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLRenderPassDepthAttachmentDescriptor : MTLRenderPassAttachmentDescriptor

/*!
 @property clearDepth
 @abstract The clear depth value to be used if the loadAction property is MTLLoadActionClear
 */
@property (nonatomic) double clearDepth;

/*!
 @property resolveFilter
 @abstract The filter to be used for depth multisample resolve.  Defaults to MTLMultisampleDepthResolveFilterSample0.
 */
@property (nonatomic) MTLMultisampleDepthResolveFilter depthResolveFilter API_AVAILABLE(macos(10.14), ios(9.0));

@end



/*!
 @enum MTLMultisampleStencilResolveFilter
 @abstract Controls the MSAA stencil resolve operation.
 */
typedef NS_ENUM(NSUInteger, MTLMultisampleStencilResolveFilter)
{
    /*!
     @constant MTLMultisampleStencilResolveFilterSample0
     @abstract The stencil sample corresponding to sample 0. This is the default behavior.
     */
    MTLMultisampleStencilResolveFilterSample0               = 0,

    /*!
     @constant MTLMultisampleStencilResolveFilterDepthResolvedSample
     @abstract The stencil sample corresponding to whichever depth sample is selected by the depth resolve filter. If depth resolve is not enabled, the stencil sample is chosen based on what a depth resolve filter would have selected.
     */
    MTLMultisampleStencilResolveFilterDepthResolvedSample   = 1,
} API_AVAILABLE(macos(10.14), ios(12.0));



MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLRenderPassStencilAttachmentDescriptor : MTLRenderPassAttachmentDescriptor

/*!
 @property clearStencil
 @abstract The clear stencil value to be used if the loadAction property is MTLLoadActionClear
 */
@property (nonatomic) uint32_t clearStencil;

/*!
 @property stencilResolveFilter
 @abstract The filter to be used for stencil multisample resolve. Defaults to MTLMultisampleStencilResolveFilterSample0.
 */
@property (nonatomic) MTLMultisampleStencilResolveFilter stencilResolveFilter API_AVAILABLE(macos(10.14), ios(12.0));

@end



MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLRenderPassColorAttachmentDescriptorArray : NSObject
/* Individual attachment state access */
- (MTLRenderPassColorAttachmentDescriptor *)objectAtIndexedSubscript:(NSUInteger)attachmentIndex;

/* This always uses 'copy' semantics.  It is safe to set the attachment state at any legal index to nil, which resets that attachment descriptor state to default vaules. */
- (void)setObject:(nullable MTLRenderPassColorAttachmentDescriptor *)attachment atIndexedSubscript:(NSUInteger)attachmentIndex;

@end


/*!
 @class MTLRenderPassDescriptor
 @abstract MTLRenderPassDescriptor represents a collection of attachments to be used to create a concrete render command encoder
 */
MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLRenderPassDescriptor : NSObject <NSCopying>

/*!
 @method renderPassDescriptor
 @abstract Create an autoreleased default frame buffer descriptor
 */
+ (MTLRenderPassDescriptor *)renderPassDescriptor;

@property (readonly) MTLRenderPassColorAttachmentDescriptorArray *colorAttachments;

@property (copy, nonatomic, null_resettable) MTLRenderPassDepthAttachmentDescriptor *depthAttachment;

@property (copy, nonatomic, null_resettable) MTLRenderPassStencilAttachmentDescriptor *stencilAttachment;

/*!
 @property visibilityResultBuffer:
 @abstract Buffer into which samples passing the depth and stencil tests are counted.
 */
@property (nullable, nonatomic, strong) id <MTLBuffer> visibilityResultBuffer;

/*!
 @property renderTargetArrayLength:
 @abstract The number of active layers
 */
@property (nonatomic) NSUInteger renderTargetArrayLength API_AVAILABLE(macos(10.11), ios(12.0));


/*!
 @property imageblockSampleLength:
 @abstract The per sample size in bytes of the largest explicit imageblock layout in the renderPass.
 */
@property (nonatomic) NSUInteger imageblockSampleLength API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @property threadgroupMemoryLength:
 @abstract The per tile size in bytes of the persistent threadgroup memory allocation.
 */
@property (nonatomic) NSUInteger threadgroupMemoryLength API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @property tileWidth:
 @abstract The width in pixels of the tile.
 @discssion Defaults to 0. Zero means Metal chooses a width that fits within the local memory.
 */
@property (nonatomic) NSUInteger tileWidth API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @property tileHeight:
 @abstract The height in pixels of the tile.
 @discssion Defaults to 0. Zero means Metal chooses a height that fits within the local memory.
 */
@property (nonatomic) NSUInteger tileHeight API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @property defaultRasterSampleCount:
 @abstract The raster sample count for the render pass when no attachments are given.
 */
@property (nonatomic) NSUInteger defaultRasterSampleCount API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @property renderTargetWidth:
 @abstract The width in pixels to constrain the render target to.
 @discussion Defaults to 0. If non-zero the value must be smaller than or equal to the minimum width of all attachments.
 */
@property (nonatomic) NSUInteger renderTargetWidth API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @property renderTargetHeight:
 @abstract The height in pixels to constrain the render target to.
 @discussion Defaults to 0. If non-zero the value must be smaller than or equal to the minimum height of all attachments.
 */
@property (nonatomic) NSUInteger renderTargetHeight API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @method setSamplePositions:count:
 @abstract Configure the custom sample positions, to be used in MSAA rendering (i.e. when sample count > 1).
 @param positions The source array for custom sample position data.
 @param count Specifies the length of the positions array, and must be a valid sample count or 0 (to disable custom sample positions).
 */
- (void)setSamplePositions:(const MTLSamplePosition * _Nullable)positions count:(NSUInteger)count API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @method getSamplePositions:count:
 @abstract Retrieve the previously configured custom sample positions. The positions input array will only be modified when count specifies a length sufficient for the number of previously configured positions.
 @param positions The destination array for custom sample position data.
 @param count Specifies the length of the positions array, which must be large enough to hold all configured sample positions.
 @return The number of previously configured custom sample positions.
 */
- (NSUInteger)getSamplePositions:(MTLSamplePosition * _Nullable)positions count:(NSUInteger)count API_AVAILABLE(macos(10.13), ios(11.0));




@end

// Inline definitions
MTL_INLINE MTLClearColor MTLClearColorMake(double red, double green, double blue, double alpha)
{
    MTLClearColor result;
    result.red = red;
    result.green = green;
    result.blue = blue;
    result.alpha = alpha;
    return result;
}

NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLResource.h
//
//  MTLResource.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 @enum MTLPurgeableOption
 @abstract Options for setPurgeable call.
 
 @constant MTLPurgeableStateNonVolatile
 The contents of this resource may not be discarded.

 @constant MTLPurgeableStateVolatile
 The contents of this resource may be discarded.

 @constant MTLPurgeableStateEmpty
 The contents of this are discarded.
 
 @constant MTLPurgeableStateKeepCurrent
 The purgeabelity state is not changed.
 */
typedef NS_ENUM(NSUInteger, MTLPurgeableState)
{
    MTLPurgeableStateKeepCurrent = 1,
    
    MTLPurgeableStateNonVolatile = 2,
    MTLPurgeableStateVolatile = 3,
    MTLPurgeableStateEmpty = 4,
} API_AVAILABLE(macos(10.11), ios(8.0));

/*!
 @enum MTLCPUCacheMode
 @abstract Describes what CPU cache mode is used for the CPU's mapping of a texture resource.
 @constant MTLCPUCacheModeDefaultCache
 The default cache mode for the system.
 
 @constant MTLCPUCacheModeWriteCombined
 Write combined memory is optimized for resources that the CPU will write into, but never read.  On some implementations, writes may bypass caches avoiding cache pollution, and reads perform very poorly.
 
 @discussion
 Applications should only investigate changing the cache mode if writing to normally cached buffers is known to cause performance issues due to cache pollution, as write combined memory can have surprising performance pitfalls.  Another approach is to use non-temporal stores to normally cached memory (STNP on ARMv8, _mm_stream_* on x86_64).
 */
typedef NS_ENUM(NSUInteger, MTLCPUCacheMode)
{
    MTLCPUCacheModeDefaultCache = 0,
    MTLCPUCacheModeWriteCombined = 1,
} API_AVAILABLE(macos(10.11), ios(8.0));

/*!
 @enum MTLStorageMode
 @abstract Describes location and CPU mapping of MTLTexture.
 @constant MTLStorageModeShared
 In this mode, CPU and device will nominally both use the same underlying memory when accessing the contents of the texture resource.
 However, coherency is only guaranteed at command buffer boundaries to minimize the required flushing of CPU and GPU caches.
 This is the default storage mode for iOS Textures.

 @constant MTLStorageModeManaged
 This mode relaxes the coherency requirements and requires that the developer make explicit requests to maintain
 coherency between a CPU and GPU version of the texture resource.  In order for CPU to access up to date GPU results,
 first, a blit synchronizations must be completed (see synchronize methods of MTLBlitCommandEncoder).
 Blit overhead is only incurred if GPU has modified the resource.
 This is the default storage mode for OS X Textures.

 @constant MTLStorageModePrivate
 This mode allows the texture resource data to be kept entirely to GPU (or driver) private memory that will never be accessed by the CPU directly, so no
 conherency of any kind must be maintained.
 
 @constant MTLStorageModeMemoryless
 This mode allows creation of resources that do not have a GPU or CPU memory backing, but do have on-chip storage for TBDR
 devices. The contents of the on-chip storage is undefined and does not persist, but its configuration is controlled by the
 MTLTexture descriptor. Textures created with MTLStorageModeMemoryless dont have an IOAccelResource at any point in their
 lifetime. The only way to populate such resource is to perform rendering operations on it. Blit operations are disallowed.
*/
typedef NS_ENUM(NSUInteger, MTLStorageMode)
{
    MTLStorageModeShared  = 0,
    MTLStorageModeManaged API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios) = 1,
    MTLStorageModePrivate = 2,
    MTLStorageModeMemoryless API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, uikitformac) = 3,
} API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @enum MTLHazardTrackingMode
 @abstract Describes how hazard tracking is performed.
 @constant MTLHazardTrackingModeDefault The default hazard tracking mode for the context. Refer to the usage of the field for semantics.
 @constant MTLHazardTrackingModeUntracked Do not perform hazard tracking.
 @constant MTLHazardTrackingModeTracked Do perform hazard tracking.
*/
typedef NS_ENUM(NSUInteger, MTLHazardTrackingMode)
{
    MTLHazardTrackingModeDefault = 0,
    MTLHazardTrackingModeUntracked = 1,
    MTLHazardTrackingModeTracked = 2,
} API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @enum MTLResourceOptions
 @abstract A set of optional arguments to influence the creation of a MTLResource (MTLTexture or MTLBuffer)

 @constant MTLResourceCPUCacheModeDefault
 The default CPU cache mode for the resource.
 Applications should only investigate changing the cache mode if writing to normally cached buffers is known to
 cause performance issues due to cache pollution, as write combined memory can have surprising performance pitfalls.
 Another approach is to use non-temporal stores to normally cached memory (STNP on ARMv8, _mm_stream_* on x86_64).
 
 @constant MTLResourceCPUCacheModeWriteCombined
 Write combined memory is optimized for resources that the CPU will write into, but never read.
 On some implementations, writes may bypass caches avoiding cache pollution, and reads perform very poorly.
 
 @constant MTLResourceStorageModeShared
 In this mode, CPU and device will nominally both use the same underlying memory when accessing the contents of the resource.
 However, coherency is only guaranteed at command buffer boundaries to minimize the required flushing of CPU and GPU caches.
 This is the default storage mode for iOS Textures.

 @constant MTLResourceStorageModeManaged
 This mode relaxes the coherency requirements and requires that the developer make explicit requests to maintain
 coherency between a CPU and GPU version of the resource.  Changes due to CPU stores outside of the Metal API must be
 indicated to Metal via MTLBuffer::didModifyRange:(NSRange)range.  In order for CPU to access up to date GPU results,
 first, a blit synchronizations must be completed (see synchronize methods of MTLBlitCommandEncoder).
 Blit overhead is only incurred if GPU has modified the resource.
 This storage mode is only defined for OS X.
 This is the default storage mode for OS X Textures.

 @constant MTLResourceStorageModePrivate
 This mode allows the data to be kept entirely to GPU (or driver) private memory that will never be accessed by the CPU directly, so no
 conherency of any kind must be maintained.

 @constant MTLResourceStorageModeMemoryless
 This mode allows creation of resources that do not have a GPU or CPU memory backing, but do have on-chip storage for TBDR
 devices. The contents of the on-chip storage is undefined and does not persist, but its configuration is controlled by the
 MTLTexture descriptor. Textures created with MTLStorageModeMemoryless dont have an IOAccelResource at any point in their
 lifetime. The only way to populate such resource is to perform rendering operations on it. Blit operations are disallowed.
 
 @constant MTLResourceHazardTrackingModeDefault
 This mode is the default for the context in which it is specified,
 which may be either MTLResourceHazardTrackingModeUntracked or MTLResourceHazardTrackingModeTracked.
 Refer to the point of use to determing the meaning of this flag.
 
 @constant MTLResourceHazardTrackingModeUntracked
 In this mode, command encoder dependencies for this resource are tracked manually with MTLFence.
 This value is the default for MTLHeap and resources sub-allocated from a MTLHeap,
 and may optionally be specified for non-heap resources.

 @constant MTLResourceHazardTrackingModeTracked
 In this mode, command encoder dependencies for this resource are tracked automatically.
 This value is the default for resources allocated from a MTLDevice,
 and may optionally be specified for MTLHeap and resources sub-allocated from such heaps.
 
 @discussion
 Note that resource options are a property of MTLTextureDescriptor (resourceOptions), so apply to texture creation.
 they are also passed directly into MTLBuffer creation methods.
*/

#define MTLResourceCPUCacheModeShift            0
#define MTLResourceCPUCacheModeMask             (0xfUL << MTLResourceCPUCacheModeShift)

#define MTLResourceStorageModeShift             4
#define MTLResourceStorageModeMask              (0xfUL << MTLResourceStorageModeShift)

#define MTLResourceHazardTrackingModeShift      8
#define MTLResourceHazardTrackingModeMask       (0x3UL << MTLResourceHazardTrackingModeShift)

typedef NS_OPTIONS(NSUInteger, MTLResourceOptions)
{
    MTLResourceCPUCacheModeDefaultCache  = MTLCPUCacheModeDefaultCache  << MTLResourceCPUCacheModeShift,
    MTLResourceCPUCacheModeWriteCombined = MTLCPUCacheModeWriteCombined << MTLResourceCPUCacheModeShift,

    MTLResourceStorageModeShared     API_AVAILABLE(macos(10.11), ios(9.0))  = MTLStorageModeShared     << MTLResourceStorageModeShift,
    MTLResourceStorageModeManaged    API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios)   = MTLStorageModeManaged    << MTLResourceStorageModeShift,
    MTLResourceStorageModePrivate    API_AVAILABLE(macos(10.11), ios(9.0))  = MTLStorageModePrivate    << MTLResourceStorageModeShift,
    MTLResourceStorageModeMemoryless API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, uikitformac) = MTLStorageModeMemoryless << MTLResourceStorageModeShift,    
    
    MTLResourceHazardTrackingModeDefault API_AVAILABLE(macos(10.13), ios(10.0)) = MTLHazardTrackingModeDefault << MTLResourceHazardTrackingModeShift,
    MTLResourceHazardTrackingModeUntracked API_AVAILABLE(macos(10.13), ios(10.0)) = MTLHazardTrackingModeUntracked << MTLResourceHazardTrackingModeShift,
    MTLResourceHazardTrackingModeTracked API_AVAILABLE(macos(10.15), ios(13.0)) = MTLHazardTrackingModeTracked << MTLResourceHazardTrackingModeShift,
    
    // Deprecated spellings
    MTLResourceOptionCPUCacheModeDefault       = MTLResourceCPUCacheModeDefaultCache,
    MTLResourceOptionCPUCacheModeWriteCombined = MTLResourceCPUCacheModeWriteCombined,
} API_AVAILABLE(macos(10.11), ios(8.0));

@protocol MTLDevice;

@protocol MTLHeap;

/*!
 @protocol MTLResource
 @abstract Common APIs available for MTLBuffer and MTLTexture instances
 */
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLResource <NSObject>

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, copy, atomic) NSString *label;

/*!
 @property device
 @abstract The device this resource was created against.  This resource can only be used with this device.
 */
@property (readonly) id <MTLDevice> device;

/*!
 @property cpuCacheMode
 @abstract The cache mode used for the CPU mapping for this resource
 */
@property (readonly) MTLCPUCacheMode cpuCacheMode;

/*!
 @property storageMode
 @abstract The resource storage mode used for the CPU mapping for this resource
 */
@property (readonly) MTLStorageMode storageMode API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property hazardTrackingMode
 @abstract Whether or not the resource is hazard tracked.
 @discussion This value can be either MTLHazardTrackingModeUntracked or MTLHazardTrackingModeTracked.
 Resources created from heaps are by default untracked, whereas resources created from the device are by default tracked.
 */
@property (readonly) MTLHazardTrackingMode hazardTrackingMode API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @property resourceOptions
 @abstract A packed tuple of the storageMode, cpuCacheMode and hazardTrackingMode properties.
 */
@property (readonly) MTLResourceOptions resourceOptions API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method setPurgeableState
 @abstract Set (or query) the purgeability state of a resource
 @discussion Synchronously set the purgeability state of a resource and return what the prior (or current) state is.
 FIXME: If the device is keeping a cached copy of the resource, both the shared copy and cached copy are made purgeable.  Any access to the resource by either the CPU or device will be undefined.
 */
- (MTLPurgeableState)setPurgeableState:(MTLPurgeableState)state;

/*!
 @property heap
 @abstract The heap from which this resouce was created.
 @discussion Nil when this resource is not backed by a heap.
 */
@property (readonly, nullable) id <MTLHeap> heap API_AVAILABLE(macos(10.13), ios(10.0));

/*!
 @property heapOffset
 @abstract The offset inside the heap at which this resource was created.
 @discussion Zero when this resource was not created on a heap with MTLHeapTypePlacement.
 */
@property (readonly) NSUInteger heapOffset API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @property allocatedSize
 @abstrace The size in bytes occupied by this resource
*/
@property (readonly) NSUInteger allocatedSize API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @method makeAliasable
 @abstract Allow future heap sub-allocations to alias against this resource's memory.
 @discussion It is illegal to call this method on a non heap-based resource. 
 It is also illegal to call this method on texture views created from heap-based textures.
 The debug layer will raise an exception. Calling this method on textures sub-allocated
 from Buffers backed by heap memory has no effect.
 Once a resource is made aliasable, the decision cannot be reverted.
 */
-(void) makeAliasable API_AVAILABLE(macos(10.13), ios(10.0));

/*!
 @method isAliasable
 @abstract Returns whether future heap sub-allocations may alias against this resource's memory.
 @return YES if <st>makeAliasable</st> was previously successfully called on this resource. NO otherwise.
 If resource is sub-allocated from other resource created on the heap, isAliasable returns 
 aliasing state of that base resource. Also returns NO when storage mode is memoryless.
 */
-(BOOL) isAliasable API_AVAILABLE(macos(10.13), ios(10.0));

@end


NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLIndirectCommandBuffer.h
//
//  MTLIndirectCommandBuffer.h
//  Metal
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLIndirectCommandEncoder.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 @abstract
 A bitfield of commands that may be performed indirectly.
 */
typedef NS_OPTIONS(NSUInteger, MTLIndirectCommandType) {
    MTLIndirectCommandTypeDraw                = (1 << 0),
    MTLIndirectCommandTypeDrawIndexed         = (1 << 1),
    MTLIndirectCommandTypeDrawPatches         = (1 << 2),
    MTLIndirectCommandTypeDrawIndexedPatches  = (1 << 3) ,

    MTLIndirectCommandTypeDispatch            API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos) = (1 << 4), /* Traditional compute semantics */
    MTLIndirectCommandTypeConcurrentDispatch  API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos) = (1 << 5), /* Dispatch threadgroups with concurrent execution */
     MTLIndirectCommandTypeConcurrentDispatchThreads  API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos) = (1 << 6), /* Dispatch threads with concurrent execution */
} API_AVAILABLE(macos(10.14), ios(12.0));


/*!
 @abstract The data layout required for specifying an indirect command buffer execution range.
 */
typedef struct
{
    uint32_t location;
    uint32_t length;
}  MTLIndirectCommandBufferExecutionRange API_AVAILABLE(macos(10.14), uikitformac(13.0), ios(13.0));

MTL_INLINE MTLIndirectCommandBufferExecutionRange MTLIndirectCommandBufferExecutionRangeMake(uint32_t location, uint32_t length) API_AVAILABLE(macos(10.14), uikitformac(13.0), ios(13.0))
{
    MTLIndirectCommandBufferExecutionRange icbRange = {location, length};
    return icbRange;
}

/*!
 @abstract
 Describes the limits and features that can be used in an indirect command
 */
MTL_EXPORT API_AVAILABLE(macos(10.14), ios(12.0))
@interface MTLIndirectCommandBufferDescriptor : NSObject

/*!
 @abstract
 A bitfield of the command types that be encoded.
 @discussion
 MTLCommandTypeDispatch cannot be mixed with any other command type.
 */
@property (readwrite, nonatomic) MTLIndirectCommandType commandTypes;

/*!
 @abstract
 Whether the render or compute pipeline are inherited from the encoder
 */
@property (readwrite, nonatomic) BOOL inheritPipelineState API_AVAILABLE(macos(10.14), ios(13.0));

/*!
 @abstract
 Whether the render or compute pipeline can set arguments.
 */
@property (readwrite, nonatomic) BOOL inheritBuffers;

/*!
 @abstract
 The maximum bind index of vertex argument buffers that can be set per command.
 */
@property (readwrite, nonatomic) NSUInteger maxVertexBufferBindCount;

/*!
 @absract
 The maximum bind index of fragment argument buffers that can be set per command.
 */
@property (readwrite, nonatomic) NSUInteger maxFragmentBufferBindCount;

/*!
 @absract
 The maximum bind index of kernel (or tile) argument buffers that can be set per command.
 */
@property (readwrite, nonatomic) NSUInteger maxKernelBufferBindCount API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos);


@end


API_AVAILABLE(macos(10.14), ios(12.0))
@protocol MTLIndirectCommandBuffer <MTLResource>

@property (readonly) NSUInteger size;

-(void)resetWithRange:(NSRange)range;

- (id <MTLIndirectRenderCommand>)indirectRenderCommandAtIndex:(NSUInteger)commandIndex;
- (id <MTLIndirectComputeCommand>)indirectComputeCommandAtIndex:(NSUInteger)commandIndex API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos);

@end

NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLDefines.h
//
//  MTLDefines.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <os/availability.h>
#import <TargetConditionals.h>

#define MTL_EXPORT __attribute__((visibility ("default")))
#ifdef __cplusplus
#define MTL_EXTERN extern "C" MTL_EXPORT
#else
#define MTL_EXTERN extern MTL_EXPORT
#endif

#ifdef __cplusplus
#define MTL_EXTERN_NO_EXPORT extern "C"
#else
#define MTL_EXTERN_NO_EXPORT extern
#endif

/* Definition of 'MTL_INLINE'. */

#if !defined(MTL_INLINE)
# if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#  define MTL_INLINE static inline
# elif defined(__cplusplus)
#  define MTL_INLINE static inline
# elif defined(__GNUC__)
#  define MTL_INLINE static __inline__
# else
#  define MTL_INLINE static
# endif
#endif

// ==========  Metal.framework/Headers/MTLArgumentEncoder.h
//
//  MTLArgumentEncoder.h
//  Metal
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLDevice;
@protocol MTLBuffer;
@protocol MTLTexture;
@protocol MTLSamplerState;
@protocol MTLRenderPipelineState;
@protocol MTLComputePipelineState;
@protocol MTLIndirectCommandBuffer;


/*!
 * @protocol MTLArgumentEncoder
 * @discussion MTLArgumentEncoder encodes buffer, texture, sampler, and constant data into a buffer.
 */
API_AVAILABLE(macos(10.13), ios(11.0))
@protocol MTLArgumentEncoder <NSObject>

/*!
 @property device
 @abstract The device this argument encoder was created against.
 */
@property (readonly) id <MTLDevice> device;

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, copy, atomic) NSString *label;

/*!
 * @property encodedLength
 * @abstract The number of bytes required to store the encoded resource bindings.
 */
@property (readonly) NSUInteger encodedLength;

/*!
 * @property alignment
 * @abstract The alignment in bytes required to store the encoded resource bindings.
 */
@property (readonly) NSUInteger alignment;

/*!
 * @method setArgumentBuffer:offset:
 * @brief Sets the destination buffer and offset at which the arguments will be encoded.
 */
- (void)setArgumentBuffer:(nullable id <MTLBuffer>)argumentBuffer offset:(NSUInteger)offset;

/*!
 * @method setArgumentBuffer:offset:arrayElement:
 * @brief Sets the destination buffer, starting offset and specific array element arguments will be encoded into. arrayElement represents
          the desired element of IAB array targetted by encoding
 */
- (void)setArgumentBuffer:(nullable id <MTLBuffer>)argumentBuffer startOffset:(NSUInteger)startOffset arrayElement:(NSUInteger)arrayElement;

/*!
 * @method setBuffer:offset:atIndex:
 * @brief Set a buffer at the given bind point index.
 */
- (void)setBuffer:(nullable id <MTLBuffer>)buffer offset:(NSUInteger)offset atIndex:(NSUInteger)index;

/*!
 * @method setBuffers:offsets:withRange:
 * @brief Set an array of buffers at the given bind point index range.
 */
- (void)setBuffers:(const id <MTLBuffer> __nullable [__nonnull])buffers offsets:(const NSUInteger [__nonnull])offsets withRange:(NSRange)range;

/*!
 * @method setTexture:atIndex:
 * @brief Set a texture at the given bind point index.
 */
- (void)setTexture:(nullable id <MTLTexture>)texture atIndex:(NSUInteger)index;

/*!
 * @method setTextures:withRange:
 * @brief Set an array of textures at the given bind point index range.
 */
- (void)setTextures:(const id <MTLTexture> __nullable [__nonnull])textures withRange:(NSRange)range;

/*!
 * @method setSamplerState:atIndex:
 * @brief Set a sampler at the given bind point index.
 */
- (void)setSamplerState:(nullable id <MTLSamplerState>)sampler atIndex:(NSUInteger)index;

/*!
 * @method setSamplerStates:withRange:
 * @brief Set an array of samplers at the given bind point index range.
 */
- (void)setSamplerStates:(const id <MTLSamplerState> __nullable [__nonnull])samplers withRange:(NSRange)range;

/*!
 * @method constantDataAtIndex:
 * @brief Returns a pointer to the constant data at the given bind point index.
 */
- (void*)constantDataAtIndex:(NSUInteger)index;


/*!
 * @method setRenderPipelineState:atIndex
 * @brief Sets a render pipeline state at a given bind point index
 */
- (void)setRenderPipelineState:(nullable id <MTLRenderPipelineState>)pipeline atIndex:(NSUInteger)index API_AVAILABLE(macos(10.14), uikitformac(13.0), ios(13.0));

/*!
 * @method setRenderPipelineStates:withRange
 * @brief Set an array of render pipeline states at a given bind point index range
 */
- (void)setRenderPipelineStates:(const id <MTLRenderPipelineState> __nullable [__nonnull])pipelines withRange:(NSRange)range API_AVAILABLE(macos(10.14), uikitformac(13.0), ios(13.0));

/*!
 * @method setComputePipelineState:atIndex
 * @brief Sets a compute pipeline state at a given bind point index
 */
- (void)setComputePipelineState:(nullable id <MTLComputePipelineState>)pipeline atIndex:(NSUInteger)index API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos);

/*!
 * @method setComputePipelineStates:withRange
 * @brief Set an array of compute pipeline states at a given bind point index range
 */
- (void)setComputePipelineStates:(const id <MTLComputePipelineState> __nullable [__nonnull])pipelines withRange:(NSRange)range API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos);

/*!
 * @method setIndirectCommandBuffer:atIndex
 * @brief Sets an indirect command buffer at a given bind point index
 */
- (void)setIndirectCommandBuffer:(nullable id <MTLIndirectCommandBuffer>)indirectCommandBuffer atIndex:(NSUInteger)index API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 * @method setIndirectCommandBuffers:withRange:
 * @brief Set an array of indirect command buffers at the given bind point index range.
 */
- (void)setIndirectCommandBuffers:(const id <MTLIndirectCommandBuffer> __nullable [__nonnull])buffers withRange:(NSRange)range API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 * @method newArgumentEncoderForBufferAtIndex:
 * @brief Returns a pointer to a new MTLArgumentEncoder that can be used to encode the an argument buffer
 * in the buffer associated with a given index.
 * Returns nil if the resource at the given index is not an argument buffer.
 */
- (nullable id<MTLArgumentEncoder>)newArgumentEncoderForBufferAtIndex:(NSUInteger)index API_AVAILABLE(macos(10.13), ios(11.0));

@end

NS_ASSUME_NONNULL_END

// ==========  Metal.framework/Headers/MTLBuffer.h
//
//  MTLBuffer.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLPixelFormat.h>
#import <Metal/MTLResource.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 @header MTLBuffer.h
 @discussion Header file for MTLBuffer
 */

@class MTLTextureDescriptor;
@protocol MTLTexture;
@protocol MTLResource;

/*!
 @protocol MTLBuffer
 @abstract A typeless allocation accessible by both the CPU and the GPU (MTLDevice) or by only the GPU when the storage mode is
 MTLResourceStorageModePrivate.
 
 @discussion
 Unlike in OpenGL and OpenCL, access to buffers is not synchronized.  The caller may use the CPU to modify the data at any time
 but is also responsible for ensuring synchronization and coherency.
 
 The contents become undefined if both the CPU and GPU write to the same buffer without a synchronizing action between those writes.
 This is true even when the regions written do not overlap.
 */
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLBuffer <MTLResource>

/*!
 @property length
 @abstract The length of the buffer in bytes.
 */
@property (readonly) NSUInteger length;

/*!
 @method contents
 @abstract Returns the data pointer of this buffer's shared copy.
 */
- (void*)contents NS_RETURNS_INNER_POINTER;

/*!
 @method didModifyRange:
 @abstract Inform the device of the range of a buffer that the CPU has modified, allowing the implementation to invalidate 
 its caches of the buffer's content.
 @discussion When the application writes to a buffer's sysmem copy via @a contents, that range of the buffer immediately 
 becomes undefined for any accesses by the GPU (MTLDevice).  To restore coherency, the buffer modification must be followed
 by -didModifyRange:, and then followed by a commit of the MTLCommandBuffer that will access the buffer.
 -didModifyRange does not make the contents coherent for any previously committed command buffers.
 Note: This method is only required if buffer is created with a storage mode of MTLResourceStorageModeManaged.
 It is not valid to invoke this method on buffers of other storage modes.
 @param range The range of bytes that have been modified.
 */
- (void)didModifyRange:(NSRange)range API_AVAILABLE(macos(10.11), uikitformac(13.0)) API_UNAVAILABLE(ios);

/*!
 @method newTextureWithDescriptor:offset:bytesPerRow:
 @abstract Create a 2D texture or texture buffer that shares storage with this buffer.
 */
- (nullable id <MTLTexture>)newTextureWithDescriptor:(MTLTextureDescriptor*)descriptor offset:(NSUInteger)offset bytesPerRow:(NSUInteger)bytesPerRow API_AVAILABLE(macos(10.13), ios(8.0));

/*!
 @method addDebugMarker:range:
 @abstract Adds a marker to a specific range in the buffer.
 When inspecting a buffer in the GPU debugging tools the marker will be shown.
 @param marker A label used for the marker.
 @param range The range of bytes the marker is using.
 */
- (void)addDebugMarker:(NSString*)marker range:(NSRange)range API_AVAILABLE(macos(10.12), ios(10.0));

/*!
 @method removeAllDebugMarkers
 @abstract Removes all debug markers from a buffer.
 */
- (void)removeAllDebugMarkers API_AVAILABLE(macos(10.12), ios(10.0));


@end
NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLStageInputOutputDescriptor.h
//
//  MTLStageInputOutputDescriptor.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Metal/MTLDefines.h>
#import <Metal/MTLDevice.h>



NS_ASSUME_NONNULL_BEGIN

/*
 MTLAttributeFormat
*/
typedef NS_ENUM(NSUInteger, MTLAttributeFormat)
{
    MTLAttributeFormatInvalid = 0,
    
    MTLAttributeFormatUChar2 = 1,
    MTLAttributeFormatUChar3 = 2,
    MTLAttributeFormatUChar4 = 3,
    
    MTLAttributeFormatChar2 = 4,
    MTLAttributeFormatChar3 = 5,
    MTLAttributeFormatChar4 = 6,
    
    MTLAttributeFormatUChar2Normalized = 7,
    MTLAttributeFormatUChar3Normalized = 8,
    MTLAttributeFormatUChar4Normalized = 9,
    
    MTLAttributeFormatChar2Normalized = 10,
    MTLAttributeFormatChar3Normalized = 11,
    MTLAttributeFormatChar4Normalized = 12,
    
    MTLAttributeFormatUShort2 = 13,
    MTLAttributeFormatUShort3 = 14,
    MTLAttributeFormatUShort4 = 15,
    
    MTLAttributeFormatShort2 = 16,
    MTLAttributeFormatShort3 = 17,
    MTLAttributeFormatShort4 = 18,
    
    MTLAttributeFormatUShort2Normalized = 19,
    MTLAttributeFormatUShort3Normalized = 20,
    MTLAttributeFormatUShort4Normalized = 21,
    
    MTLAttributeFormatShort2Normalized = 22,
    MTLAttributeFormatShort3Normalized = 23,
    MTLAttributeFormatShort4Normalized = 24,
    
    MTLAttributeFormatHalf2 = 25,
    MTLAttributeFormatHalf3 = 26,
    MTLAttributeFormatHalf4 = 27,
    
    MTLAttributeFormatFloat = 28,
    MTLAttributeFormatFloat2 = 29,
    MTLAttributeFormatFloat3 = 30,
    MTLAttributeFormatFloat4 = 31,
    
    MTLAttributeFormatInt = 32,
    MTLAttributeFormatInt2 = 33,
    MTLAttributeFormatInt3 = 34,
    MTLAttributeFormatInt4 = 35,
    
    MTLAttributeFormatUInt = 36,
    MTLAttributeFormatUInt2 = 37,
    MTLAttributeFormatUInt3 = 38,
    MTLAttributeFormatUInt4 = 39,
    
    MTLAttributeFormatInt1010102Normalized = 40,
    MTLAttributeFormatUInt1010102Normalized = 41,
    
    MTLAttributeFormatUChar4Normalized_BGRA API_AVAILABLE(macos(10.13), ios(11.0)) = 42,
    
    MTLAttributeFormatUChar API_AVAILABLE(macos(10.13), ios(11.0)) = 45,
    MTLAttributeFormatChar API_AVAILABLE(macos(10.13), ios(11.0)) = 46,
    MTLAttributeFormatUCharNormalized API_AVAILABLE(macos(10.13), ios(11.0)) = 47,
    MTLAttributeFormatCharNormalized API_AVAILABLE(macos(10.13), ios(11.0)) = 48,
    
    MTLAttributeFormatUShort API_AVAILABLE(macos(10.13), ios(11.0)) = 49,
    MTLAttributeFormatShort API_AVAILABLE(macos(10.13), ios(11.0)) = 50,
    MTLAttributeFormatUShortNormalized API_AVAILABLE(macos(10.13), ios(11.0)) = 51,
    MTLAttributeFormatShortNormalized API_AVAILABLE(macos(10.13), ios(11.0)) = 52,
    
    MTLAttributeFormatHalf API_AVAILABLE(macos(10.13), ios(11.0)) = 53,
    
} API_AVAILABLE(macos(10.12), ios(10.0));


typedef NS_ENUM(NSUInteger, MTLIndexType) {
    MTLIndexTypeUInt16 = 0,
    MTLIndexTypeUInt32 = 1,
} API_AVAILABLE(macos(10.11), ios(8.0));


typedef NS_ENUM(NSUInteger, MTLStepFunction)
{
    MTLStepFunctionConstant = 0,

    // vertex functions only
    MTLStepFunctionPerVertex = 1,
    MTLStepFunctionPerInstance = 2,
    MTLStepFunctionPerPatch API_AVAILABLE(macos(10.12), ios(10.0)) = 3,
    MTLStepFunctionPerPatchControlPoint API_AVAILABLE(macos(10.12), ios(10.0)) = 4,

    // compute functions only
    MTLStepFunctionThreadPositionInGridX = 5,
    MTLStepFunctionThreadPositionInGridY = 6,
    MTLStepFunctionThreadPositionInGridXIndexed = 7,
    MTLStepFunctionThreadPositionInGridYIndexed = 8,
} API_AVAILABLE(macos(10.12), ios(10.0));


MTL_EXPORT API_AVAILABLE(macos(10.12), ios(10.0))
@interface MTLBufferLayoutDescriptor : NSObject <NSCopying>
@property (assign, nonatomic) NSUInteger stride;
@property (assign, nonatomic) MTLStepFunction stepFunction;
@property (assign, nonatomic) NSUInteger stepRate;
@end

MTL_EXPORT API_AVAILABLE(macos(10.12), ios(10.0))
@interface MTLBufferLayoutDescriptorArray : NSObject
- (MTLBufferLayoutDescriptor *)objectAtIndexedSubscript:(NSUInteger)index;
- (void)setObject:(nullable MTLBufferLayoutDescriptor *)bufferDesc atIndexedSubscript:(NSUInteger)index;
@end

MTL_EXPORT API_AVAILABLE(macos(10.12), ios(10.0))
@interface MTLAttributeDescriptor : NSObject <NSCopying>
@property (assign, nonatomic) MTLAttributeFormat format;
@property (assign, nonatomic) NSUInteger offset;
@property (assign, nonatomic) NSUInteger bufferIndex;
@end

MTL_EXPORT API_AVAILABLE(macos(10.12), ios(10.0))
@interface MTLAttributeDescriptorArray : NSObject
- (MTLAttributeDescriptor *)objectAtIndexedSubscript:(NSUInteger)index;
- (void)setObject:(nullable MTLAttributeDescriptor *)attributeDesc atIndexedSubscript:(NSUInteger)index;
@end

/*
 MTLStageInputOutputDescriptor
 */
MTL_EXPORT API_AVAILABLE(macos(10.12), ios(10.0))
@interface MTLStageInputOutputDescriptor : NSObject <NSCopying>

+ (MTLStageInputOutputDescriptor *)stageInputOutputDescriptor;

@property (readonly) MTLBufferLayoutDescriptorArray *layouts;
@property (readonly) MTLAttributeDescriptorArray *attributes;

/* only used for compute with MTLStepFunction...Indexed */
@property (assign, nonatomic) MTLIndexType indexType;
@property (assign, nonatomic) NSUInteger indexBufferIndex;

- (void)reset;

@end
NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLDepthStencil.h
//
//  MTLDepthStencil.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Metal/MTLDefines.h>
#import <Metal/MTLDevice.h>


NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSUInteger, MTLCompareFunction) {
    MTLCompareFunctionNever = 0,
    MTLCompareFunctionLess = 1,
    MTLCompareFunctionEqual = 2,
    MTLCompareFunctionLessEqual = 3,
    MTLCompareFunctionGreater = 4,
    MTLCompareFunctionNotEqual = 5,
    MTLCompareFunctionGreaterEqual = 6,
    MTLCompareFunctionAlways = 7,
} API_AVAILABLE(macos(10.11), ios(8.0));

typedef NS_ENUM(NSUInteger, MTLStencilOperation) {
    MTLStencilOperationKeep = 0,
    MTLStencilOperationZero = 1,
    MTLStencilOperationReplace = 2,
    MTLStencilOperationIncrementClamp = 3,
    MTLStencilOperationDecrementClamp = 4,
    MTLStencilOperationInvert = 5,
    MTLStencilOperationIncrementWrap = 6,
    MTLStencilOperationDecrementWrap = 7,
} API_AVAILABLE(macos(10.11), ios(8.0));

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLStencilDescriptor : NSObject <NSCopying>

@property (nonatomic) MTLCompareFunction stencilCompareFunction;

/*! Stencil is tested first.  stencilFailureOperation declares how the stencil buffer is updated when the stencil test fails. */
@property (nonatomic) MTLStencilOperation stencilFailureOperation;

/*! If stencil passes, depth is tested next.  Declare what happens when the depth test fails. */
@property (nonatomic) MTLStencilOperation depthFailureOperation;

/*! If both the stencil and depth tests pass, declare how the stencil buffer is updated. */
@property (nonatomic) MTLStencilOperation depthStencilPassOperation;

@property (nonatomic) uint32_t readMask;
@property (nonatomic) uint32_t writeMask;

@end

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLDepthStencilDescriptor : NSObject <NSCopying>

/* Defaults to MTLCompareFuncAlways, which effectively skips the depth test */
@property (nonatomic) MTLCompareFunction depthCompareFunction;

/* Defaults to NO, so no depth writes are performed */
@property (nonatomic, getter=isDepthWriteEnabled) BOOL depthWriteEnabled;

/* Separate stencil state for front and back state.  Both front and back can be made to track the same state by assigning the same MTLStencilDescriptor to both. */
@property (copy, nonatomic, null_resettable) MTLStencilDescriptor *frontFaceStencil;
@property (copy, nonatomic, null_resettable) MTLStencilDescriptor *backFaceStencil;

/*!
 @property label
 @abstract A string to help identify the created object.
 */
@property (nullable, copy, nonatomic) NSString *label;

@end


/* Device-specific compiled depth/stencil state object */
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLDepthStencilState <NSObject>

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, readonly) NSString *label;

/*!
 @property device
 @abstract The device this resource was created against.  This resource can only be used with this device.
 */
@property (readonly) id <MTLDevice> device;

@end
NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/Metal.h
//
//  Metal.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Metal/MTLDefines.h>
#import <Metal/MTLTypes.h>
#import <Metal/MTLBlitCommandEncoder.h>
#import <Metal/MTLBuffer.h>
#import <Metal/MTLCommandBuffer.h>
#import <Metal/MTLComputeCommandEncoder.h>
#import <Metal/MTLCommandQueue.h>
#import <Metal/MTLDevice.h>
#import <Metal/MTLDepthStencil.h>
#import <Metal/MTLDrawable.h>
#import <Metal/MTLRenderPass.h>
#import <Metal/MTLComputePipeline.h>
#import <Metal/MTLLibrary.h>
#import <Metal/MTLPixelFormat.h>
#import <Metal/MTLRenderPipeline.h>
#import <Metal/MTLVertexDescriptor.h>
#import <Metal/MTLParallelRenderCommandEncoder.h>
#import <Metal/MTLRenderCommandEncoder.h>
#import <Metal/MTLSampler.h>
#import <Metal/MTLTexture.h>
#import <Metal/MTLHeap.h>
#import <Metal/MTLArgumentEncoder.h>
#import <Metal/MTLCaptureManager.h>
#import <Metal/MTLCaptureScope.h>
#import <Metal/MTLIndirectCommandBuffer.h>
#import <Metal/MTLIndirectCommandEncoder.h>
#import <Metal/MTLFence.h>
#import <Metal/MTLEvent.h>
// ==========  Metal.framework/Headers/MTLIndirectCommandEncoder.h
//
//  MTLIndirectCommandEncoder.h
//  Metal
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//


#import <Metal/MTLStageInputOutputDescriptor.h>
#import <Metal/MTLRenderPipeline.h>

NS_ASSUME_NONNULL_BEGIN

/*
 @abstract
 Describes a CPU-recorded indirect render command
 */
API_AVAILABLE(macos(10.14), ios(12.0))
@protocol MTLIndirectRenderCommand <NSObject>
- (void)setRenderPipelineState:(id <MTLRenderPipelineState>)pipelineState API_AVAILABLE(macos(10.14), uikitformac(13.0), ios(13.0));

- (void)setVertexBuffer:(id <MTLBuffer>)buffer offset:(NSUInteger)offset atIndex:(NSUInteger)index;
- (void)setFragmentBuffer:(id <MTLBuffer>)buffer offset:(NSUInteger)offset atIndex:(NSUInteger)index;


- (void)        drawPatches:(NSUInteger)numberOfPatchControlPoints patchStart:(NSUInteger)patchStart patchCount:(NSUInteger)patchCount patchIndexBuffer:(nullable id <MTLBuffer>)patchIndexBuffer
     patchIndexBufferOffset:(NSUInteger)patchIndexBufferOffset instanceCount:(NSUInteger)instanceCount baseInstance:(NSUInteger)baseInstance
   tessellationFactorBuffer:(id <MTLBuffer>)buffer tessellationFactorBufferOffset:(NSUInteger)offset tessellationFactorBufferInstanceStride:(NSUInteger)instanceStride;



- (void)drawIndexedPatches:(NSUInteger)numberOfPatchControlPoints  patchStart:(NSUInteger)patchStart patchCount:(NSUInteger)patchCount patchIndexBuffer:(nullable id <MTLBuffer>)patchIndexBuffer
    patchIndexBufferOffset:(NSUInteger)patchIndexBufferOffset controlPointIndexBuffer:(id <MTLBuffer>)controlPointIndexBuffer
controlPointIndexBufferOffset:(NSUInteger)controlPointIndexBufferOffset instanceCount:(NSUInteger)instanceCount
              baseInstance:(NSUInteger)baseInstance tessellationFactorBuffer:(id <MTLBuffer>)buffer
tessellationFactorBufferOffset:(NSUInteger)offset tessellationFactorBufferInstanceStride:(NSUInteger)instanceStride;

- (void)drawPrimitives:(MTLPrimitiveType)primitiveType vertexStart:(NSUInteger)vertexStart vertexCount:(NSUInteger)vertexCount instanceCount:(NSUInteger)instanceCount baseInstance:(NSUInteger)baseInstance;
- (void)drawIndexedPrimitives:(MTLPrimitiveType)primitiveType indexCount:(NSUInteger)indexCount indexType:(MTLIndexType)indexType indexBuffer:(id <MTLBuffer>)indexBuffer indexBufferOffset:(NSUInteger)indexBufferOffset instanceCount:(NSUInteger)instanceCount baseVertex:(NSInteger)baseVertex baseInstance:(NSUInteger)baseInstance;

- (void)reset;


@end

API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos)
@protocol MTLIndirectComputeCommand <NSObject>
- (void)setComputePipelineState:(id <MTLComputePipelineState>)pipelineState API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos);

- (void)setKernelBuffer:(id <MTLBuffer>)buffer offset:(NSUInteger)offset atIndex:(NSUInteger)index;


- (void)concurrentDispatchThreadgroups:(MTLSize)threadgroupsPerGrid
                 threadsPerThreadgroup:(MTLSize)threadsPerThreadgroup;
- (void)concurrentDispatchThreads:(MTLSize)threadsPerGrid
            threadsPerThreadgroup:(MTLSize)threadsPerThreadgroup;

- (void)setBarrier;

- (void)clearBarrier;

- (void)setImageBlockWidth:(NSUInteger)width height:(NSUInteger)height API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, uikitformac);

- (void)dispatchThreadgroups:(MTLSize)threadgroupsPerGrid
       threadsPerThreadgroup:(MTLSize)threadsPerThreadgroup;
- (void)reset;


- (void)setThreadgroupMemoryLength:(NSUInteger)length atIndex:(NSUInteger)index;
- (void)setStageInRegion:(MTLRegion)region;
@end

NS_ASSUME_NONNULL_END

// ==========  Metal.framework/Headers/MTLParallelRenderCommandEncoder.h
//
//  MTLParallelRenderCommandEncoder.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Metal/MTLDefines.h>
#import <Metal/MTLTypes.h>
#import <Metal/MTLRenderPass.h>
#import <Metal/MTLCommandEncoder.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLDevice;
@protocol MTLRenderCommandEncoder;

/*!
 @protocol MTLParallelRenderCommandEncoder
 @discussion The MTLParallelRenderCommandEncoder protocol is designed to allow a single render to texture operation to be efficiently (and safely) broken up across multiple threads.
 */
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLParallelRenderCommandEncoder <MTLCommandEncoder>

/*!
 @method renderCommandEncoder
 @abstract Return a new autoreleased object that conforms to <MTLRenderCommandEncoder> that may be used to encode on a different thread.
 */
- (nullable id <MTLRenderCommandEncoder>)renderCommandEncoder;

/*!
 @method setColorStoreAction:atIndex:
 @brief If the the store action for a given color attachment was set to MTLStoreActionUnknown when the render command encoder was created,
 setColorStoreAction:atIndex: must be used to finalize the store action before endEncoding is called.
 @param storeAction The desired store action for the given color attachment.  This may be set to any value other than MTLStoreActionUnknown.
 @param colorAttachmentIndex The index of the color attachment
*/
- (void)setColorStoreAction:(MTLStoreAction)storeAction atIndex:(NSUInteger)colorAttachmentIndex API_AVAILABLE(macos(10.12), ios(10.0));

/*!
 @method setDepthStoreAction:
 @brief If the the store action for the depth attachment was set to MTLStoreActionUnknown when the render command encoder was created,
 setDepthStoreAction: must be used to finalize the store action before endEncoding is called.
*/
- (void)setDepthStoreAction:(MTLStoreAction)storeAction API_AVAILABLE(macos(10.12), ios(10.0));

/*!
 @method setStencilStoreAction:
 @brief If the the store action for the stencil attachment was set to MTLStoreActionUnknown when the render command encoder was created,
 setStencilStoreAction: must be used to finalize the store action before endEncoding is called.
*/
- (void)setStencilStoreAction:(MTLStoreAction)storeAction API_AVAILABLE(macos(10.12), ios(10.0));

/*!
 @method setColorStoreActionOptions:atIndex:
 @brief If the the store action for a given color attachment was set to MTLStoreActionUnknown when the render command encoder was created,
 setColorStoreActionOptions:atIndex: may be used to finalize the store action options before endEncoding is called.
 @param storeActionOptions The desired store action options for the given color attachment.
 @param colorAttachmentIndex The index of the color attachment
 */
- (void)setColorStoreActionOptions:(MTLStoreActionOptions)storeActionOptions atIndex:(NSUInteger)colorAttachmentIndex API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @method setDepthStoreActionOptions:
 @brief If the the store action for the depth attachment was set to MTLStoreActionUnknown when the render command encoder was created,
 setDepthStoreActionOptions: may be used to finalize the store action options before endEncoding is called.
 */
- (void)setDepthStoreActionOptions:(MTLStoreActionOptions)storeActionOptions API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @method setStencilStoreActionOptions:
 @brief If the the store action for the stencil attachment was set to MTLStoreActionUnknown when the render command encoder was created,
 setStencilStoreActionOptions: may be used to finalize the store action options before endEncoding is called.
 */
- (void)setStencilStoreActionOptions:(MTLStoreActionOptions)storeActionOptions API_AVAILABLE(macos(10.13), ios(11.0));

@end
NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLPipeline.h
//
//  MTLPipeline.h
//  Metal
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Metal/MTLDevice.h>


NS_ASSUME_NONNULL_BEGIN

/*!
 * @enum MTLMutability
 * @abstract Specifies whether a buffer will be modified between the time it is bound and a compute
 * or render pipeline is executed in a draw or dispatch.
 */
typedef NS_ENUM(NSUInteger, MTLMutability)
{
    MTLMutabilityDefault   = 0,
    MTLMutabilityMutable   = 1,
    MTLMutabilityImmutable = 2,
} API_AVAILABLE(macos(10.13), ios(11.0));

MTL_EXPORT API_AVAILABLE(macos(10.13), ios(11.0))
@interface MTLPipelineBufferDescriptor : NSObject <NSCopying>

/*! Buffer mutability. Defaults to MTLMutabilityDefault: mutable for standard buffers, immutable for argument buffers */
@property (nonatomic) MTLMutability mutability;

@end

MTL_EXPORT API_AVAILABLE(macos(10.13), ios(11.0))
@interface MTLPipelineBufferDescriptorArray : NSObject
/* Individual buffer descriptor access */
- (MTLPipelineBufferDescriptor *)objectAtIndexedSubscript:(NSUInteger)bufferIndex;

/* This always uses 'copy' semantics. It is safe to set the buffer descriptor at any legal index to nil, which resets that buffer descriptor to default vaules. */
- (void)setObject:(nullable MTLPipelineBufferDescriptor *)buffer atIndexedSubscript:(NSUInteger)bufferIndex;

@end

NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLSampler.h
//
//  MTLSampler.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLDevice.h>
#import <Metal/MTLDepthStencil.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 @enum MTLSamplerMinMagFilter
 @abstract Options for filtering texels within a mip level.
 
 @constant MTLSamplerMinMagFilterNearest
 Select the single texel nearest to the sample point.
 
 @constant MTLSamplerMinMagFilterLinear
 Select two texels in each dimension, and interpolate linearly between them.  Not all devices support linear filtering for all formats.  Integer textures can not use linear filtering on any device, and only some devices support linear filtering of Float textures.
 */
typedef NS_ENUM(NSUInteger, MTLSamplerMinMagFilter) {
    MTLSamplerMinMagFilterNearest = 0,
    MTLSamplerMinMagFilterLinear = 1,
} API_AVAILABLE(macos(10.11), ios(8.0));

/*!
 @enum MTLSamplerMipFilter
 @abstract Options for selecting and filtering between mipmap levels
 @constant MTLSamplerMipFilterNotMipmapped The texture is sampled as if it only had a single mipmap level.  All samples are read from level 0.
 @constant MTLSamplerMipFilterNearest The nearst mipmap level is selected.
 @constant MTLSamplerMipFilterLinear If the filter falls between levels, both levels are sampled, and their results linearly interpolated between levels.
 */
typedef NS_ENUM(NSUInteger, MTLSamplerMipFilter) {
    MTLSamplerMipFilterNotMipmapped = 0,
    MTLSamplerMipFilterNearest = 1,
    MTLSamplerMipFilterLinear = 2,
} API_AVAILABLE(macos(10.11), ios(8.0));

/*!
 @enum MTLSamplerAddressMode
 @abstract Options for what value is returned when a fetch falls outside the bounds of a texture.
 
 @constant MTLSamplerAddressModeClampToEdge
 Texture coordinates will be clamped between 0 and 1.

 @constant MTLSamplerAddressModeMirrorClampToEdge
 Mirror the texture while coordinates are within -1..1, and clamp to edge when outside.

 @constant MTLSamplerAddressModeRepeat
 Wrap to the other side of the texture, effectively ignoring fractional parts of the texture coordinate.
 
 @constant MTLSamplerAddressModeMirrorRepeat
 Between -1 and 1 the texture is mirrored across the 0 axis.  The image is repeated outside of that range.
 
 @constant MTLSamplerAddressModeClampToZero
 ClampToZero returns transparent zero (0,0,0,0) for images with an alpha channel, and returns opaque zero (0,0,0,1) for images without an alpha channel.
 
 @constant MTLSamplerAddressModeClampToBorderColor
 Clamp to border color returns the value specified by the borderColor variable of the MTLSamplerDesc.
*/
typedef NS_ENUM(NSUInteger, MTLSamplerAddressMode) {
    MTLSamplerAddressModeClampToEdge = 0,
    MTLSamplerAddressModeMirrorClampToEdge API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios) = 1,
    MTLSamplerAddressModeRepeat = 2,
    MTLSamplerAddressModeMirrorRepeat = 3,
    MTLSamplerAddressModeClampToZero = 4,
    MTLSamplerAddressModeClampToBorderColor API_AVAILABLE(macos(10.12)) API_UNAVAILABLE(ios) = 5,
} API_AVAILABLE(macos(10.11), ios(8.0));

/*!
 @enum MTLSamplerBorderColor
 @abstract Specify the color value that will be clamped to when the sampler address mode is MTLSamplerAddressModeClampToBorderColor.
 
 @constant MTLSamplerBorderColorTransparentBlack
 Transparent black returns {0,0,0,0} for clamped texture values.
 
 @constant MTLSamplerBorderColorOpaqueBlack
 OpaqueBlack returns {0,0,0,1} for clamped texture values.
 
 @constant MTLSamplerBorderColorOpaqueWhite
 OpaqueWhite returns {1,1,1,1} for clamped texture values.
 */
typedef NS_ENUM(NSUInteger, MTLSamplerBorderColor) {
    MTLSamplerBorderColorTransparentBlack = 0,  // {0,0,0,0}
    MTLSamplerBorderColorOpaqueBlack = 1,       // {0,0,0,1}
    MTLSamplerBorderColorOpaqueWhite = 2,       // {1,1,1,1}
} API_AVAILABLE(macos(10.12)) API_UNAVAILABLE(ios);

/*!
 @class MTLSamplerDescriptor
 @abstract A mutable descriptor used to configure a sampler.  When complete, this can be used to create an immutable MTLSamplerState.
 */
MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLSamplerDescriptor : NSObject <NSCopying>

/*!
 @property minFilter
 @abstract Filter option for combining texels within a mipmap level the sample footprint is larger than a pixel (minification).
 @discussion The default value is MTLSamplerMinMagFilterNearest.
 */
@property (nonatomic) MTLSamplerMinMagFilter minFilter;

/*!
 @property magFilter
 @abstract Filter option for combining texels within a mipmap level the sample footprint is smaller than a pixel (magnification).
 @discussion The default value is MTLSamplerMinMagFilterNearest.
 */
@property (nonatomic) MTLSamplerMinMagFilter magFilter;

/*!
 @property mipFilter
 @abstract Filter options for filtering between two mipmap levels.
 @discussion The default value is MTLSamplerMipFilterNotMipmapped
 */
@property (nonatomic) MTLSamplerMipFilter mipFilter;

/*!
 @property maxAnisotropy
 @abstract The number of samples that can be taken to improve quality of sample footprints that are anisotropic.
 @discussion The default value is 1.
 */
@property (nonatomic) NSUInteger maxAnisotropy;

/*!
 @property sAddressMode
 @abstract Set the wrap mode for the S texture coordinate.  The default value is MTLSamplerAddressModeClampToEdge.
 */
@property (nonatomic) MTLSamplerAddressMode sAddressMode;

/*!
 @property tAddressMode
 @abstract Set the wrap mode for the T texture coordinate.  The default value is MTLSamplerAddressModeClampToEdge.
 */
@property (nonatomic) MTLSamplerAddressMode tAddressMode;

/*!
 @property rAddressMode
 @abstract Set the wrap mode for the R texture coordinate.  The default value is MTLSamplerAddressModeClampToEdge.
 */
@property (nonatomic) MTLSamplerAddressMode rAddressMode;

/*!
 @property borderColor
 @abstract Set the color for the MTLSamplerAddressMode to one of the predefined in the MTLSamplerBorderColor enum.
 */
@property (nonatomic) MTLSamplerBorderColor borderColor API_AVAILABLE(macos(10.12)) API_UNAVAILABLE(ios);

/*!
 @property normalizedCoordinates.
 @abstract If YES, texture coordates are from 0 to 1.  If NO, texture coordinates are 0..width, 0..height.
 @discussion normalizedCoordinates defaults to YES.  Non-normalized coordinates should only be used with 1D and 2D textures with the ClampToEdge wrap mode, otherwise the results of sampling are undefined.
 */
@property (nonatomic) BOOL normalizedCoordinates;

/*!
 @property lodMinClamp
 @abstract The minimum level of detail that will be used when sampling from a texture.
 @discussion The default value of lodMinClamp is 0.0.  Clamp values are ignored for texture sample variants that specify an explicit level of detail.
 */
@property (nonatomic) float lodMinClamp;

/*!
 @property lodMaxClamp
 @abstract The maximum level of detail that will be used when sampling from a texture.
 @discussion The default value of lodMaxClamp is FLT_MAX.  Clamp values are ignored for texture sample variants that specify an explicit level of detail.
 */
@property (nonatomic) float lodMaxClamp;

/*!
 @property lodAverage
 @abstract If YES, an average level of detail will be used when sampling from a texture. If NO, no averaging is performed.
 @discussion lodAverage defaults to NO. This option is a performance hint. An implementation is free to ignore this property.
 */
@property (nonatomic) BOOL lodAverage API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @property compareFunction
 @abstract Set the comparison function used when sampling shadow maps. The default value is MTLCompareFunctionNever.
 */
@property (nonatomic) MTLCompareFunction compareFunction API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property supportArgumentBuffers
 @abstract true if the sampler can be used inside an argument buffer
*/
@property (nonatomic) BOOL supportArgumentBuffers API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @property label
 @abstract A string to help identify the created object.
 */
@property (nullable, copy, nonatomic) NSString *label;

@end

/*!
 @protocol MTLSamplerState
 @abstract An immutable collection of sampler state compiled for a single device.
 */
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLSamplerState <NSObject>

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, readonly) NSString *label;

/*!
 @property device
 @abstract The device this resource was created against.  This resource can only be used with this device.
 */
@property (readonly) id <MTLDevice> device;

@end
NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLLibrary.h
//
//  MTLLibrary.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLResource.h>
#import <Metal/MTLArgument.h>


NS_ASSUME_NONNULL_BEGIN
@protocol MTLDevice;
@protocol MTLFunction;
@protocol MTLLibrary;
@class MTLCompileOptions;
@class MTLFunctionConstantValues;


@protocol MTLArgumentEncoder;

typedef __autoreleasing MTLArgument *__nullable MTLAutoreleasedArgument;

typedef NS_ENUM(NSUInteger, MTLPatchType) {
    MTLPatchTypeNone = 0,
    MTLPatchTypeTriangle = 1,
    MTLPatchTypeQuad = 2,
} API_AVAILABLE(macos(10.12), ios(10.0));

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLVertexAttribute : NSObject

@property (readonly) NSString                    *name;
@property (readonly) NSUInteger                   attributeIndex;
@property (readonly) MTLDataType                  attributeType API_AVAILABLE(macos(10.11), ios(8.3));
@property (readonly, getter=isActive) BOOL        active;
@property (readonly, getter=isPatchData) BOOL              patchData API_AVAILABLE(macos(10.12), ios(10.0));
@property (readonly, getter=isPatchControlPointData) BOOL  patchControlPointData API_AVAILABLE(macos(10.12), ios(10.0));

@end

MTL_EXPORT API_AVAILABLE(macos(10.12), ios(10.0))
@interface MTLAttribute : NSObject

@property (readonly) NSString                    *name;
@property (readonly) NSUInteger                   attributeIndex;
@property (readonly) MTLDataType                  attributeType;
@property (readonly, getter=isActive) BOOL        active;
@property (readonly, getter=isPatchData) BOOL              patchData API_AVAILABLE(macos(10.12), ios(10.0));
@property (readonly, getter=isPatchControlPointData) BOOL  patchControlPointData API_AVAILABLE(macos(10.12), ios(10.0));

@end

/*!
 @enum MTLFunctionType
 @abstract An identifier for a top-level Metal function.
 @discussion Each location in the API where a program is used requires a function written for that specific usage.
 
 @constant MTLFunctionTypeVertex
 A vertex shader, usable for a MTLRenderPipelineState.
 
 @constant MTLFunctionTypeFragment
 A fragment shader, usable for a MTLRenderPipelineState.
 
 @constant MTLFunctionTypeKernel
 A compute kernel, usable to create a MTLComputePipelineState.
 */
typedef NS_ENUM(NSUInteger, MTLFunctionType) {
    MTLFunctionTypeVertex = 1,
    MTLFunctionTypeFragment = 2,
    MTLFunctionTypeKernel = 3,
} API_AVAILABLE(macos(10.11), ios(8.0));


/*!
 @interface MTLFunctionConstant
 @abstract describe an uberShader constant used by the function
 */
MTL_EXPORT API_AVAILABLE(macos(10.12), ios(10.0))
@interface MTLFunctionConstant : NSObject

@property (readonly) NSString *name;
@property (readonly) MTLDataType type;
@property (readonly) NSUInteger index;
@property (readonly) BOOL required;

@end

/*!
 @protocol MTLFunction
 @abstract A handle to to intermediate code used as inputs for either a MTLComputePipelineState or a MTLRenderPipelineState.
 @discussion MTLFunction is a single vertex shader, fragment shader, or compute function.  A Function can only be used with the device that it was created against.
*/
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLFunction <NSObject>

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, copy, atomic) NSString *label  API_AVAILABLE(macos(10.12), ios(10.0));

/*!
 @property device
 @abstract The device this resource was created against.  This resource can only be used with this device.
 */
@property (readonly) id <MTLDevice> device;

/*!
 @property functionType
 @abstract The overall kind of entry point: compute, vertex, or fragment.
 */
@property (readonly) MTLFunctionType functionType;

/*!
 @property patchType
 @abstract Returns the patch type. MTLPatchTypeNone if it is not a post tessellation vertex shader.
 */
@property (readonly) MTLPatchType patchType API_AVAILABLE(macos(10.12), ios(10.0));

/*!
 @property patchControlPointCount
 @abstract Returns the number of patch control points if it was specified in the shader. Returns -1 if it
 was not specified.
 */
@property (readonly) NSInteger patchControlPointCount API_AVAILABLE(macos(10.12), ios(10.0));

@property (nullable, readonly) NSArray <MTLVertexAttribute *> *vertexAttributes;

/*!
 @property stageInputAttributes
 @abstract Returns an array describing the attributes
 */
@property (nullable, readonly) NSArray <MTLAttribute *> *stageInputAttributes API_AVAILABLE(macos(10.12), ios(10.0));

/*!
 @property name
 @abstract The name of the function in the shading language.
 */
@property (readonly) NSString *name;

/*!
 @property functionConstantsDictionary
 @abstract A dictionary containing information about all function contents, keyed by the constant names.
 */
@property (readonly) NSDictionary<NSString *, MTLFunctionConstant *> *functionConstantsDictionary API_AVAILABLE(macos(10.12), ios(10.0));


/*!
 * @method newArgumentEncoderWithBufferIndex:
 * @abstract Creates an argument encoder which will encode arguments matching the layout of the argument buffer at the given bind point index.
 */
- (id <MTLArgumentEncoder>)newArgumentEncoderWithBufferIndex:(NSUInteger)bufferIndex API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 * @method newArgumentEncoderWithBufferIndex:
 * @abstract Creates an argument encoder which will encode arguments matching the layout of the argument buffer at the given bind point index.
 */
- (id <MTLArgumentEncoder>)newArgumentEncoderWithBufferIndex:(NSUInteger)bufferIndex
                                                                  reflection:(MTLAutoreleasedArgument * __nullable)reflection API_AVAILABLE(macos(10.13), ios(11.0));


@end

typedef NS_ENUM(NSUInteger, MTLLanguageVersion) {

    MTLLanguageVersion1_0 API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, uikitformac) = (1 << 16),
    MTLLanguageVersion1_1 API_AVAILABLE(macos(10.11), ios(9.0)) = (1 << 16) + 1,
    MTLLanguageVersion1_2 API_AVAILABLE(macos(10.12), ios(10.0)) = (1 << 16) + 2,
    MTLLanguageVersion2_0 API_AVAILABLE(macos(10.13), ios(11.0)) = (2 << 16),
    MTLLanguageVersion2_1 API_AVAILABLE(macos(10.14), ios(12.0)) = (2 << 16) + 1,
    MTLLanguageVersion2_2 API_AVAILABLE(macos(10.15), ios(13.0)) = (2 << 16) + 2,
} API_AVAILABLE(macos(10.11), ios(9.0));

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLCompileOptions : NSObject <NSCopying>

// Pre-processor options

/*!
 @property preprocessorNames
 @abstract List of preprocessor macros to consider to when compiling this program. Specified as key value pairs, using a NSDictionary. The keys must be NSString objects and values can be either NSString or NSNumber objects.
 @discussion The default value is nil.
 */
@property (nullable, readwrite, copy, nonatomic) NSDictionary <NSString *, NSObject *> *preprocessorMacros;

// Math intrinsics options

/*!
 @property fastMathEnabled
 @abstract If YES, enables the compiler to perform optimizations for floating-point arithmetic that may violate the IEEE 754 standard. It also enables the high precision variant of math functions for single precision floating-point scalar and vector types. fastMathEnabled defaults to YES.
 */
@property (readwrite, nonatomic) BOOL fastMathEnabled;

/*!
 @property languageVersion
 @abstract set the metal language version used to interpret the source.
 */
@property (readwrite, nonatomic) MTLLanguageVersion languageVersion API_AVAILABLE(macos(10.11), ios(9.0));

@end

/*!
 @constant MTLLibraryErrorDomain
 @abstract NSErrors raised when creating a library.
 */
API_AVAILABLE(macos(10.11), ios(8.0))
MTL_EXTERN NSErrorDomain const MTLLibraryErrorDomain;

/*!
 @enum MTLLibraryError
 @abstract NSErrors raised when creating a library.
 */
typedef NS_ENUM(NSUInteger, MTLLibraryError) {
    MTLLibraryErrorUnsupported      = 1,
    MTLLibraryErrorInternal         = 2,
    MTLLibraryErrorCompileFailure   = 3,
    MTLLibraryErrorCompileWarning   = 4,
    MTLLibraryErrorFunctionNotFound API_AVAILABLE(macos(10.12), ios(10.0)) = 5,
    MTLLibraryErrorFileNotFound API_AVAILABLE(macos(10.12), ios(10.0)) = 6,
} API_AVAILABLE(macos(10.11), ios(8.0));

API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLLibrary <NSObject>

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, copy, atomic) NSString *label;

/*!
 @property device
 @abstract The device this resource was created against.  This resource can only be used with this device.
 */
@property (readonly) id <MTLDevice> device;

/*!
 @method newFunctionWithName
 @abstract Returns a pointer to a function object, return nil if the function is not found in the library.
 */
- (nullable id <MTLFunction>) newFunctionWithName:(NSString *)functionName;

/*!
 @method newFunctionWithName:constantValues:error:
 @abstract Returns a pointer to a function object obtained by applying the constant values to the named function.
 @discussion This method will call the compiler. Use newFunctionWithName:constantValues:completionHandler: to
 avoid waiting on the compiler.
 */
- (nullable id <MTLFunction>) newFunctionWithName:(NSString *)name constantValues:(MTLFunctionConstantValues *)constantValues
					error:(__autoreleasing NSError **)error API_AVAILABLE(macos(10.12), ios(10.0));


/*!
 @method newFunctionWithName:constantValues:completionHandler:
 @abstract Returns a pointer to a function object obtained by applying the constant values to the named function.
 @discussion This method is asynchronous since it is will call the compiler.
 */
- (void) newFunctionWithName:(NSString *)name constantValues:(MTLFunctionConstantValues *)constantValues
			completionHandler:(void (^)(id<MTLFunction> __nullable function, NSError* __nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(10.0));

/*!
 @property functionNames
 @abstract The array contains NSString objects, with the name of each function in library.
 */
@property (readonly) NSArray <NSString *> *functionNames;

@end
NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLCommandQueue.h
//
//  MTLCommandQueue.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Metal/MTLDefines.h>
#import <Metal/Metal.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLDevice;
@protocol MTLCommandBuffer;

/*!
 @protocol MTLCommandQueue
 @brief A serial queue of command buffers to be executed by the device.
 */
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLCommandQueue <NSObject>

/*! @brief A string to help identify this object */
@property (nullable, copy, atomic) NSString *label;

/*! @brief The device this queue will submit to */
@property (readonly) id <MTLDevice> device;

/*! 
 @method commandBuffer
 @abstract Returns a new autoreleased command buffer used to encode work into this queue that 
 maintains strong references to resources used within the command buffer.
*/
- (nullable id <MTLCommandBuffer>)commandBuffer;


/*!
 @method commandBufferWithUnretainedReferences
 @abstract Returns a new autoreleased command buffer used to encode work into this queue that 
 does not maintain strong references to resources used within the command buffer.
*/
- (nullable id <MTLCommandBuffer>)commandBufferWithUnretainedReferences;

/*!
 @method insertDebugCaptureBoundary
 @abstract Inform Xcode about when debug capture should start and stop.
 */
- (void)insertDebugCaptureBoundary API_DEPRECATED("Use MTLCaptureScope instead", macos(10.11, 10.13), ios(8.0, 11.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLHeap.h
//
//  MTLHeap.h
//  Metal
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLResource.h>
#import <Metal/MTLBuffer.h>
#import <Metal/MTLTexture.h>
#import <Metal/MTLTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum MTLHeapType
 @abstract Describes the mode of operation for an MTLHeap.
 @constant MTLHeapTypeAutomatic
 In this mode, resources are placed in the heap automatically.
 Automatically placed resources have optimal GPU-specific layout, and may perform better than MTLHeapTypePlacement.
 This heap type is recommended when the heap primarily contains temporary write-often resources.
 @constant MTLHeapTypePlacement
 In this mode, the app places resources in the heap.
 Manually placed resources allow the app to control memory usage and heap fragmentation directly.
 This heap type is recommended when the heap primarily contains persistent write-rarely resources.
 */
typedef NS_ENUM(NSInteger, MTLHeapType)
{
    MTLHeapTypeAutomatic = 0,
    MTLHeapTypePlacement = 1,
} API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @class MTLHeapDescriptor
 */
MTL_EXPORT API_AVAILABLE(macos(10.13), ios(10.0))
@interface MTLHeapDescriptor : NSObject <NSCopying>

/*!
 @property size
 @abstract Requested size of the heap's backing memory.
 @discussion The size may be rounded up to GPU page granularity.
 */
@property (readwrite, nonatomic) NSUInteger size;

/*!
 @property storageMode
 @abstract Storage mode for the heap. Default is MTLStorageModePrivate.
 @discussion All resources created from this heap share the same storage mode.
 MTLStorageModeManaged and MTLStorageModeMemoryless are disallowed.
 */
@property (readwrite, nonatomic) MTLStorageMode storageMode;

/*!
 @property cpuCacheMode
 @abstract CPU cache mode for the heap. Default is MTLCPUCacheModeDefaultCache.
 @discussion All resources created from this heap share the same cache mode.
 CPU cache mode is ignored for MTLStorageModePrivate.
 */
@property (readwrite, nonatomic) MTLCPUCacheMode cpuCacheMode;

/*!
 @property hazardTrackingMode
 @abstract Set hazard tracking mode for the heap. The default value is MTLHazardTrackingModeDefault.
 @discussion For heaps, MTLHazardTrackingModeDefault is treated as MTLHazardTrackingModeUntracked.
 Setting hazardTrackingMode to MTLHazardTrackingModeTracked causes hazard tracking to be enabled heap.
 When a resource on a hazard tracked heap is modified, reads and writes from all resources suballocated on that heap will be delayed until the modification is complete.
 Similarly, modifying heap resources will be delayed until all in-flight reads and writes from all resources suballocated on that heap have completed.
 For optimal performance, perform hazard tracking manually through MTLFence or MTLEvent instead.
 All resources created from this heap shared the same hazard tracking mode.
 */
@property (readwrite, nonatomic) MTLHazardTrackingMode hazardTrackingMode API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @property resourceOptions
 @abstract A packed tuple of the storageMode, cpuCacheMode and hazardTrackingMode properties.
 @discussion Modifications to this property are reflected in the other properties and vice versa.
 */
@property (readwrite, nonatomic) MTLResourceOptions resourceOptions API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @property type
 @abstract The type of the heap. The default value is MTLHeapTypeAutomatic.
 @discussion This constrains the resource creation functions that are available.
 */
@property (readwrite, nonatomic) MTLHeapType type API_AVAILABLE(macos(10.15), ios(13.0));

@end


/*!
 @protocol MTLHeap
 */
API_AVAILABLE(macos(10.13), ios(10.0))
@protocol MTLHeap <NSObject>

/*!
 @property label
 @abstract A string to help identify this heap.
 */
@property (nullable, copy, atomic) NSString *label;

/*!
 @property device
 @abstract The device this heap was created against. This heap can only be used with this device.
 */
@property (readonly) id <MTLDevice> device;

/*!
 @property storageMode
 @abstract Current heap storage mode, default is MTLStorageModePrivate.
 @discussion All resources created from this heap share the same storage mode.
 */
@property (readonly) MTLStorageMode storageMode;

/*!
 @property cpuCacheMode
 @abstract CPU cache mode for the heap. Default is MTLCPUCacheModeDefaultCache.
 @discussion All resources created from this heap share the same cache mode.
 */
@property (readonly) MTLCPUCacheMode cpuCacheMode;

/*!
 @property hazardTrackingMode
 @abstract Whether or not the heap is hazard tracked.
 @discussion
 When a resource on a hazard tracked heap is modified, reads and writes from any other resource on that heap will be delayed until the modification is complete.
 Similarly, modifying heap resources will be delayed until all in-flight reads and writes from resources suballocated on that heap have completed.
 For optimal performance, perform hazard tracking manually through MTLFence or MTLEvent instead.
 Resources on the heap may opt-out of hazard tracking individually when the heap is hazard tracked,
 however resources cannot opt-in to hazard tracking when the heap is not hazard tracked.
 */
@property (readonly) MTLHazardTrackingMode hazardTrackingMode API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @property resourceOptions
 @abstract A packed tuple of the storageMode, cpuCacheMode and hazardTrackingMode properties.
 */
@property (readonly) MTLResourceOptions resourceOptions API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @property size
 @abstract Heap size in bytes, specified at creation time and rounded up to device specific alignment.
 */
@property (readonly) NSUInteger size;


/*!
 @property usedSize
 @abstract The size in bytes, of all resources allocated from the heap.
 */
@property (readonly) NSUInteger usedSize;

/*!
 @property currentAllocatedSize
 @abstract The size in bytes of the current heap allocation.
 */
@property (readonly) NSUInteger currentAllocatedSize API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @method maxAvailableSizeWithAlignment:
 @abstract The maximum size that can be successfully allocated from the heap in bytes, taking into notice given alignment. Alignment needs to be zero, or power of two.
 @discussion Provides a measure of fragmentation within the heap.
 */
- (NSUInteger)maxAvailableSizeWithAlignment:(NSUInteger)alignment;

/*!
 @method newBufferWithLength:options:
 @abstract Create a new buffer backed by heap memory.
 @discussion The requested storage and CPU cache modes must match the storage and CPU cache modes of the heap.
 @return The buffer or nil if heap is full.
 */
- (nullable id <MTLBuffer>)newBufferWithLength:(NSUInteger)length
                                       options:(MTLResourceOptions)options;

/*!
 @method newTextureWithDescriptor:
 @abstract Create a new texture backed by heap memory.
 @discussion The requested storage and CPU cache modes must match the storage and CPU cache modes of the heap, with the exception that the requested storage mode can be MTLStorageModeMemoryless. 
 @return The texture or nil if heap is full.
 */
- (nullable id <MTLTexture>)newTextureWithDescriptor:(MTLTextureDescriptor *)desc;

/*!
 @method setPurgeabilityState:
 @abstract Set or query the purgeability state of the heap.
 */
- (MTLPurgeableState)setPurgeableState:(MTLPurgeableState)state;

/*!
 @property type
 @abstract The type of the heap. The default value is MTLHeapTypeAutomatic.
 @discussion This constrains the resource creation functions that are available on the heap.
 */
@property (readonly) MTLHeapType type API_AVAILABLE(macos(10.15), ios(13.0));
 
/*!
 @method newBufferWithLength:options:offset:
 @abstract Create a new buffer backed by heap memory at the specified placement offset.
 @discussion This method can only be used when heapType is set to MTLHeapTypePlacement.
 Use "MTLDevice heapBufferSizeAndAlignWithLength:options:" to determine requiredSize and requiredAlignment.
 Any resources that exist in this heap at overlapping half-open range [offset, offset + requiredSize) are implicitly aliased with the new resource.
 @param length The requested size of the buffer, in bytes.
 @param options The requested options of the buffer, of which the storage and CPU cache mode must match these of the heap.
 @param offset The requested offset of the buffer inside the heap, in bytes. Behavior is undefined if "offset + requiredSize > heap.size" or "offset % requiredAlignment != 0".
 @return The buffer, or nil if the heap is not a placement heap
 */
- (nullable id<MTLBuffer>)newBufferWithLength:(NSUInteger)length
                                      options:(MTLResourceOptions)options
                                       offset:(NSUInteger)offset API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @method newTextureWithDescriptor:offset:
 @abstract Create a new texture backed by heap memory at the specified placement offset.
 @discussion This method can only be used when heapType is set to MTLHeapTypePlacement.
 Use "MTLDevice heapTextureSizeAndAlignWithDescriptor:" to determine requiredSize and requiredAlignment.
 Any resources that exist in this heap at overlapping half-open range [offset, offset + requiredSize) are implicitly aliased with the new resource.
 @param descriptor The requested properties of the texture, of which the storage and CPU cache mode must match those of the heap.
 @param offset The requested offset of the texture inside the heap, in bytes. Behavior is undefined if "offset + requiredSize > heap.size" and "offset % requiredAlignment != 0".
 @return The texture, or nil if the heap is not a placement heap.
 */
- (nullable id<MTLTexture>)newTextureWithDescriptor:(MTLTextureDescriptor *)descriptor
                                             offset:(NSUInteger)offset API_AVAILABLE(macos(10.15), ios(13.0));
@end

NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLCaptureManager.h
//
//  MTLCaptureManager.h
//  Metal
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>


NS_ASSUME_NONNULL_BEGIN

@protocol MTLCaptureScope;
@protocol MTLCommandQueue;
@protocol MTLDevice;

API_AVAILABLE(macos(10.15), ios(13.0))
MTL_EXTERN NSErrorDomain const MTLCaptureErrorDomain;

typedef NS_ENUM(NSInteger, MTLCaptureError)
{
    /// Capturing is not supported, maybe the destination is not supported.
    MTLCaptureErrorNotSupported = 1,
    /// A capture is already in progress.
    MTLCaptureErrorAlreadyCapturing,
    /// The MTLCaptureDescriptor contains an invalid parameters.
    MTLCaptureErrorInvalidDescriptor,
} API_AVAILABLE(macos(10.15), ios(13.0));

/// The destination where you want the GPU trace to be captured to.
typedef NS_ENUM(NSInteger, MTLCaptureDestination)
{
    /// Capture to Developer Tools (Xcode) and stop the execution after capturing.
    MTLCaptureDestinationDeveloperTools = 1,
    /// Capture to a GPU Trace document and continue execution after capturing.
    MTLCaptureDestinationGPUTraceDocument,
} API_AVAILABLE(macos(10.15), ios(13.0));

MTL_EXTERN API_AVAILABLE(macos(10.15), ios(13.0))
@interface MTLCaptureDescriptor: NSObject <NSCopying>
{
@private
    id _captureObject;
    MTLCaptureDestination _destination;
    NSURL *_outputURL;
}

/**
    @brief The object that is captured.

    Must be one of the following:
 
    MTLDevice captures all command queues of the device.
 
    MTLCommandQueue captures a single command queue.
 
    MTLCaptureScope captures between the next begin and end of the scope.
 */
@property (nonatomic, strong, nullable) id captureObject;

/// The destination you want the GPU trace to be captured to.
@property (nonatomic, assign) MTLCaptureDestination destination;

/// URL the GPU Trace document will be captured to.
/// Must be specified when destiation is MTLCaptureDestinationGPUTraceDocument.
@property (nonatomic, copy, nullable) NSURL *outputURL;

@end


MTL_EXTERN API_AVAILABLE(macos(10.13), ios(11.0))
@interface MTLCaptureManager : NSObject
{
@private
    BOOL _isCapturing;
    id<MTLCaptureScope> _defaultCaptureScope;
}

/** Retrieves the shared capture manager for this process. There is only one capture manager per process.
    The capture manager allows the user to create capture scopes and trigger captures from code.
    When a capture has been completed, it will be displayed in Xcode and the application will be paused.
    @remarks: only MTLCommandBuffers created after starting a capture and committed before stopping it are captured. 
 */
+ (MTLCaptureManager*)sharedCaptureManager;

// Use +[sharedCaptureManager]
- (instancetype)init API_UNAVAILABLE(macos, ios);

// Creates a new capture scope for the given capture device
- (id<MTLCaptureScope>)newCaptureScopeWithDevice:(id<MTLDevice>)device;
// Creates a new capture scope for the given command queue
- (id<MTLCaptureScope>)newCaptureScopeWithCommandQueue:(id<MTLCommandQueue>)commandQueue;

// Checks if a given capture destination is supported.
- (BOOL)supportsDestination:(MTLCaptureDestination)destination API_AVAILABLE(macos(10.15), ios(13.0));

/// Start capturing until stopCapture is called.
/// @param descriptor MTLCaptureDescriptor specifies the parameters.
/// @param error Optional error output to check why a capture could not be started.
/// @return true if the capture was successfully started, otherwise false.
/// @remarks Only MTLCommandBuffer​s created after starting and committed before stopping it are captured.
- (BOOL)startCaptureWithDescriptor:(MTLCaptureDescriptor *)descriptor error:(__autoreleasing NSError **)error API_AVAILABLE(macos(10.15), ios(13.0));

// Starts capturing, for all queues of the given device, new MTLCommandBuffer's until -[stopCapture] or Xcode’s stop capture button is pressed
- (void)startCaptureWithDevice:(id<MTLDevice>)device API_DEPRECATED("Use startCaptureWithDescriptor:error: instead", macos(10.13, 10.15), ios(11.0, 13.0));
// Starts capturing, for the given command queue, command buffers that are created after invoking this method and committed before invoking -[stopCapture] or clicking Xcode’s stop capture button.
- (void)startCaptureWithCommandQueue:(id<MTLCommandQueue>)commandQueue API_DEPRECATED("Use startCaptureWithDescriptor:error: instead", macos(10.13, 10.15), ios(11.0, 13.0));
// Start a capture with the given scope: from the scope's begin until its end, restricting the capture to the scope's device(s) and, if selected, the scope's command queue
- (void)startCaptureWithScope:(id<MTLCaptureScope>)captureScope API_DEPRECATED("Use startCaptureWithDescriptor:error: instead", macos(10.13, 10.15), ios(11.0, 13.0));

// Stops a capture started from startCaptureWithDevice:/startCaptureWithCommandQueue:/startCaptureWithScope: or from Xcode’s capture button
- (void)stopCapture;

// Default scope to be captured when a capture is initiated from Xcode’s capture button. When nil, it’ll fall back to presentDrawable:, presentDrawable:atTime:, presentDrawable:afterMinimumDuration: in MTLCommandBuffer or present:, present:atTime:, present:afterMinimumDuration: in MTLDrawable.
@property (nullable, readwrite, strong, atomic) id<MTLCaptureScope> defaultCaptureScope;

// Query if a capture is currently in progress
@property (readonly) BOOL isCapturing;

@end

NS_ASSUME_NONNULL_END

// ==========  Metal.framework/Headers/MTLRenderCommandEncoder.h
//
//  MTLRenderCommandEncoder.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLTypes.h>
#import <Metal/MTLCommandEncoder.h>
#import <Metal/MTLCommandBuffer.h>
#import <Metal/MTLRenderPass.h>
#import <Metal/MTLFence.h>
#import <Metal/MTLStageInputOutputDescriptor.h>


NS_ASSUME_NONNULL_BEGIN
@protocol MTLDevice;
@protocol MTLFunction;
@protocol MTLBuffer;
@protocol MTLSamplerState;

@protocol MTLDepthStencilState;
@protocol MTLTexture;
@protocol MTLRenderPipelineState;

typedef NS_ENUM(NSUInteger, MTLPrimitiveType) {
    MTLPrimitiveTypePoint = 0,
    MTLPrimitiveTypeLine = 1,
    MTLPrimitiveTypeLineStrip = 2,
    MTLPrimitiveTypeTriangle = 3,
    MTLPrimitiveTypeTriangleStrip = 4,
} API_AVAILABLE(macos(10.11), ios(8.0));

typedef NS_ENUM(NSUInteger, MTLVisibilityResultMode) {
    MTLVisibilityResultModeDisabled = 0,
    MTLVisibilityResultModeBoolean = 1,
    MTLVisibilityResultModeCounting API_AVAILABLE(macos(10.11), ios(9.0)) = 2,
} API_AVAILABLE(macos(10.11), ios(8.0));

typedef struct {
    NSUInteger x, y, width, height;
} MTLScissorRect;

typedef struct {
    double originX, originY, width, height, znear, zfar;
} MTLViewport;

typedef NS_ENUM(NSUInteger, MTLCullMode) {
    MTLCullModeNone = 0,
    MTLCullModeFront = 1,
    MTLCullModeBack = 2,
} API_AVAILABLE(macos(10.11), ios(8.0));

typedef NS_ENUM(NSUInteger, MTLWinding) {
    MTLWindingClockwise = 0,
    MTLWindingCounterClockwise = 1,
} API_AVAILABLE(macos(10.11), ios(8.0));

typedef NS_ENUM(NSUInteger, MTLDepthClipMode) {
    MTLDepthClipModeClip = 0,
    MTLDepthClipModeClamp = 1,
} API_AVAILABLE(macos(10.11), ios(9.0));

typedef NS_ENUM(NSUInteger, MTLTriangleFillMode) {
    MTLTriangleFillModeFill = 0,
    MTLTriangleFillModeLines = 1,
} API_AVAILABLE(macos(10.11), ios(8.0));

typedef struct {
    uint32_t vertexCount;
    uint32_t instanceCount;
    uint32_t vertexStart;
    uint32_t baseInstance;
} MTLDrawPrimitivesIndirectArguments;

typedef struct {
    uint32_t indexCount;
    uint32_t instanceCount;
    uint32_t indexStart;
    int32_t  baseVertex;
    uint32_t baseInstance;
} MTLDrawIndexedPrimitivesIndirectArguments;


typedef struct {
    uint32_t patchCount;
    uint32_t instanceCount;
    uint32_t patchStart;
    uint32_t baseInstance;
} MTLDrawPatchIndirectArguments;

typedef struct {
    /* NOTE: edgeTessellationFactor and insideTessellationFactor are interpreted as half (16-bit floats) */
    uint16_t edgeTessellationFactor[4];
    uint16_t insideTessellationFactor[2];
} MTLQuadTessellationFactorsHalf;

typedef struct {
    /* NOTE: edgeTessellationFactor and insideTessellationFactor are interpreted as half (16-bit floats) */
    uint16_t edgeTessellationFactor[3];
    uint16_t insideTessellationFactor;
} MTLTriangleTessellationFactorsHalf;

/*!
 @abstract Points at which a fence may be waited on or signaled.
 @constant MTLRenderStageVertex   All vertex work prior to rasterization has completed.
 @constant MTLRenderStageFragment All rendering work has completed.
 */
typedef NS_OPTIONS(NSUInteger, MTLRenderStages)
{
    MTLRenderStageVertex   = (1UL << 0),
    MTLRenderStageFragment = (1UL << 1),
} API_AVAILABLE(macos(10.13), ios(10.0));

/*!
 @protocol MTLRenderCommandEncoder
 @discussion MTLRenderCommandEncoder is a container for graphics rendering state and the code to translate the state into a command format that the device can execute. 
 */
API_AVAILABLE(macos(10.11), ios(8.0))

@protocol MTLRenderCommandEncoder <MTLCommandEncoder>

/*!
 @method setRenderPipelineState
 @brief Sets the current render pipeline state object.
 */
- (void)setRenderPipelineState:(id <MTLRenderPipelineState>)pipelineState;

/* Vertex Resources */

/*!
 @method setVertexBytes:length:atIndex:
 @brief Set the data (by copy) for a given vertex buffer binding point.  This will remove any existing MTLBuffer from the binding point.
 */
- (void)setVertexBytes:(const void *)bytes length:(NSUInteger)length atIndex:(NSUInteger)index API_AVAILABLE(macos(10.11), ios(8.3));

/*!
 @method setVertexBuffer:offset:atIndex:
 @brief Set a global buffer for all vertex shaders at the given bind point index.
 */
- (void)setVertexBuffer:(nullable id <MTLBuffer>)buffer offset:(NSUInteger)offset atIndex:(NSUInteger)index;

/*!
 @method setVertexBufferOffset:atIndex:
 @brief Set the offset within the current global buffer for all vertex shaders at the given bind point index.
 */
- (void)setVertexBufferOffset:(NSUInteger)offset atIndex:(NSUInteger)index API_AVAILABLE(macos(10.11), ios(8.3));

/*!
 @method setVertexBuffers:offsets:withRange:
 @brief Set an array of global buffers for all vertex shaders with the given bind point range.
 */
- (void)setVertexBuffers:(const id <MTLBuffer> __nullable [__nonnull])buffers offsets:(const NSUInteger [__nonnull])offsets withRange:(NSRange)range;

/*!
 @method setVertexTexture:atIndex:
 @brief Set a global texture for all vertex shaders at the given bind point index.
 */
- (void)setVertexTexture:(nullable id <MTLTexture>)texture atIndex:(NSUInteger)index;

/*!
 @method setVertexTextures:withRange:
 @brief Set an array of global textures for all vertex shaders with the given bind point range.
 */
- (void)setVertexTextures:(const id <MTLTexture> __nullable [__nonnull])textures withRange:(NSRange)range;

/*!
 @method setVertexSamplerState:atIndex:
 @brief Set a global sampler for all vertex shaders at the given bind point index.
 */
- (void)setVertexSamplerState:(nullable id <MTLSamplerState>)sampler atIndex:(NSUInteger)index;

/*!
 @method setVertexSamplerStates:withRange:
 @brief Set an array of global samplers for all vertex shaders with the given bind point range.
 */
- (void)setVertexSamplerStates:(const id <MTLSamplerState> __nullable [__nonnull])samplers withRange:(NSRange)range;

/*!
 @method setVertexSamplerState:lodMinClamp:lodMaxClamp:atIndex:
 @brief Set a global sampler for all vertex shaders at the given bind point index.
 */
- (void)setVertexSamplerState:(nullable id <MTLSamplerState>)sampler lodMinClamp:(float)lodMinClamp lodMaxClamp:(float)lodMaxClamp atIndex:(NSUInteger)index;

/*!
 @method setVertexSamplerStates:lodMinClamps:lodMaxClamps:withRange:
 @brief Set an array of global samplers for all vertex shaders with the given bind point range.
 */
- (void)setVertexSamplerStates:(const id <MTLSamplerState> __nullable [__nonnull])samplers lodMinClamps:(const float [__nonnull])lodMinClamps lodMaxClamps:(const float [__nonnull])lodMaxClamps withRange:(NSRange)range;

/*!
 @method setViewport:
 @brief Set the viewport, which is used to transform vertexes from normalized device coordinates to window coordinates.  Fragments that lie outside of the viewport are clipped, and optionally clamped for fragments outside of znear/zfar.
 */
- (void)setViewport:(MTLViewport)viewport;


/*!
 @method setViewports:
 @brief Specifies an array of viewports, which are used to transform vertices from normalized device coordinates to window coordinates based on [[ viewport_array_index ]] value specified in the vertex shader.
 */
- (void)setViewports:(const MTLViewport [__nonnull])viewports count:(NSUInteger)count API_AVAILABLE(macos(10.13), ios(12.0));

/*!
 @method setFrontFacingWinding:
 @brief The winding order of front-facing primitives.
 */
- (void)setFrontFacingWinding:(MTLWinding)frontFacingWinding;


/*!
 @method setCullMode:
 @brief Controls if primitives are culled when front facing, back facing, or not culled at all.
 */
- (void)setCullMode:(MTLCullMode)cullMode;

/*!
@method setDepthClipMode:
@brief Controls what is done with fragments outside of the near or far planes.
*/
- (void)setDepthClipMode:(MTLDepthClipMode)depthClipMode API_AVAILABLE(macos(10.11), ios(11.0));

/*!
 @method setDepthBias:slopeScale:clamp:
 @brief Depth Bias.
 */
- (void)setDepthBias:(float)depthBias slopeScale:(float)slopeScale clamp:(float)clamp;

/*!
 @method setScissorRect:
 @brief Specifies a rectangle for a fragment scissor test.  All fragments outside of this rectangle are discarded.
 */
- (void)setScissorRect:(MTLScissorRect)rect;


/*!
 @method setScissorRects:
 @brief Specifies an array of rectangles for a fragment scissor test. The specific rectangle used is based on the [[ viewport_array_index ]] value output by the vertex shader. Fragments that lie outside the scissor rectangle are discarded.
 */
- (void)setScissorRects:(const MTLScissorRect [__nonnull])scissorRects count:(NSUInteger)count API_AVAILABLE(macos(10.13), ios(12.0));

/*!
 @method setTriangleFillMode:
 @brief Set how to rasterize triangle and triangle strip primitives.
 */
- (void)setTriangleFillMode:(MTLTriangleFillMode)fillMode;

/* Fragment Resources */

/*!
 @method setFragmentBytes:length:atIndex:
 @brief Set the data (by copy) for a given fragment buffer binding point.  This will remove any existing MTLBuffer from the binding point.
 */
- (void)setFragmentBytes:(const void *)bytes length:(NSUInteger)length atIndex:(NSUInteger)index API_AVAILABLE(macos(10.11), ios(8.3));

/*!
 @method setFragmentBuffer:offset:atIndex:
 @brief Set a global buffer for all fragment shaders at the given bind point index.
 */
- (void)setFragmentBuffer:(nullable id <MTLBuffer>)buffer offset:(NSUInteger)offset atIndex:(NSUInteger)index;

/*!
 @method setFragmentBufferOffset:atIndex:
 @brief Set the offset within the current global buffer for all fragment shaders at the given bind point index.
 */
- (void)setFragmentBufferOffset:(NSUInteger)offset atIndex:(NSUInteger)index API_AVAILABLE(macos(10.11), ios(8.3));

/*!
 @method setFragmentBuffers:offsets:withRange:
 @brief Set an array of global buffers for all fragment shaders with the given bind point range.
 */
- (void)setFragmentBuffers:(const id <MTLBuffer> __nullable [__nonnull])buffers offsets:(const NSUInteger [__nonnull])offsets withRange:(NSRange)range;

/*!
 @method setFragmentTexture:atIndex:
 @brief Set a global texture for all fragment shaders at the given bind point index.
 */
- (void)setFragmentTexture:(nullable id <MTLTexture>)texture atIndex:(NSUInteger)index;

/*!
 @method setFragmentTextures:withRange:
 @brief Set an array of global textures for all fragment shaders with the given bind point range.
 */
- (void)setFragmentTextures:(const id <MTLTexture> __nullable [__nonnull])textures withRange:(NSRange)range;

/*!
 @method setFragmentSamplerState:atIndex:
 @brief Set a global sampler for all fragment shaders at the given bind point index.
 */
- (void)setFragmentSamplerState:(nullable id <MTLSamplerState>)sampler atIndex:(NSUInteger)index;

/*!
 @method setFragmentSamplerStates:withRange:
 @brief Set an array of global samplers for all fragment shaders with the given bind point range.
 */
- (void)setFragmentSamplerStates:(const id <MTLSamplerState> __nullable [__nonnull])samplers withRange:(NSRange)range;

/*!
 @method setFragmentSamplerState:lodMinClamp:lodMaxClamp:atIndex:
 @brief Set a global sampler for all fragment shaders at the given bind point index.
 */
- (void)setFragmentSamplerState:(nullable id <MTLSamplerState>)sampler lodMinClamp:(float)lodMinClamp lodMaxClamp:(float)lodMaxClamp atIndex:(NSUInteger)index;

/*!
 @method setFragmentSamplerStates:lodMinClamps:lodMaxClamps:withRange:
 @brief Set an array of global samplers for all fragment shaders with the given bind point range.
 */
- (void)setFragmentSamplerStates:(const id <MTLSamplerState> __nullable [__nonnull])samplers lodMinClamps:(const float [__nonnull])lodMinClamps lodMaxClamps:(const float [__nonnull])lodMaxClamps withRange:(NSRange)range;


/* Constant Blend Color */
/*!
 @method setBlendColorRed:green:blue:alpha:
 @brief Set the constant blend color used across all blending on all render targets
 */
- (void)setBlendColorRed:(float)red green:(float)green blue:(float)blue alpha:(float)alpha;

/*! 
 @method setDepthStencilState:
 @brief Set the DepthStencil state object.
 */
- (void)setDepthStencilState:(nullable id <MTLDepthStencilState>)depthStencilState;

/*! 
 @method setStencilReferenceValue:
 @brief Set the stencil reference value for both the back and front stencil buffers.
 */
- (void)setStencilReferenceValue:(uint32_t)referenceValue;

/*!
 @method setStencilFrontReferenceValue:backReferenceValue:
 @brief Set the stencil reference value for the back and front stencil buffers independently.
 */
- (void)setStencilFrontReferenceValue:(uint32_t)frontReferenceValue backReferenceValue:(uint32_t)backReferenceValue API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method setVisibilityResultMode:offset:
 @abstract Monitor if samples pass the depth and stencil tests.
 @param mode Controls if the counter is disabled or moniters passing samples.
 @param offset The offset relative to the occlusion query buffer provided when the command encoder was created.  offset must be a multiple of 8.
 */
- (void)setVisibilityResultMode:(MTLVisibilityResultMode)mode offset:(NSUInteger)offset;

/*!
 @method setColorStoreAction:atIndex:
 @brief If the the store action for a given color attachment was set to MTLStoreActionUnknown when the render command encoder was created,
 setColorStoreAction:atIndex: must be used to finalize the store action before endEncoding is called.
 @param storeAction The desired store action for the given color attachment.  This may be set to any value other than MTLStoreActionUnknown.
 @param colorAttachmentIndex The index of the color attachment
*/
- (void)setColorStoreAction:(MTLStoreAction)storeAction atIndex:(NSUInteger)colorAttachmentIndex API_AVAILABLE(macos(10.12), ios(10.0));

/*!
 @method setDepthStoreAction:
 @brief If the the store action for the depth attachment was set to MTLStoreActionUnknown when the render command encoder was created,
 setDepthStoreAction: must be used to finalize the store action before endEncoding is called.
*/
- (void)setDepthStoreAction:(MTLStoreAction)storeAction API_AVAILABLE(macos(10.12), ios(10.0));

/*!
 @method setStencilStoreAction:
 @brief If the the store action for the stencil attachment was set to MTLStoreActionUnknown when the render command encoder was created,
 setStencilStoreAction: must be used to finalize the store action before endEncoding is called.
*/
- (void)setStencilStoreAction:(MTLStoreAction)storeAction API_AVAILABLE(macos(10.12), ios(10.0));

/*!
 @method setColorStoreActionOptions:atIndex:
 @brief If the the store action for a given color attachment was set to MTLStoreActionUnknown when the render command encoder was created,
 setColorStoreActionOptions:atIndex: may be used to finalize the store action options before endEncoding is called.
 @param storeActionOptions The desired store action options for the given color attachment.
 @param colorAttachmentIndex The index of the color attachment
 */
- (void)setColorStoreActionOptions:(MTLStoreActionOptions)storeActionOptions atIndex:(NSUInteger)colorAttachmentIndex API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @method setDepthStoreActionOptions:
 @brief If the the store action for the depth attachment was set to MTLStoreActionUnknown when the render command encoder was created,
 setDepthStoreActionOptions: may be used to finalize the store action options before endEncoding is called.
 */
- (void)setDepthStoreActionOptions:(MTLStoreActionOptions)storeActionOptions API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @method setStencilStoreActionOptions:
 @brief If the the store action for the stencil attachment was set to MTLStoreActionUnknown when the render command encoder was created,
 setStencilStoreActionOptions: may be used to finalize the store action options before endEncoding is called.
 */
- (void)setStencilStoreActionOptions:(MTLStoreActionOptions)storeActionOptions API_AVAILABLE(macos(10.13), ios(11.0));

/* Drawing */

/*!
 @method drawPrimitives:vertexStart:vertexCount:instanceCount:
 @brief Draw primitives without an index list.
 @param primitiveType The type of primitives that elements are assembled into.
 @param vertexStart For each instance, the first index to draw
 @param vertexCount For each instance, the number of indexes to draw
 @param instanceCount The number of instances drawn.
 */
- (void)drawPrimitives:(MTLPrimitiveType)primitiveType vertexStart:(NSUInteger)vertexStart vertexCount:(NSUInteger)vertexCount instanceCount:(NSUInteger)instanceCount;

/*!
 @method drawPrimitives:vertexStart:vertexCount:
 @brief Draw primitives without an index list.
 @param primitiveType The type of primitives that elements are assembled into.
 @param vertexStart For each instance, the first index to draw
 @param vertexCount For each instance, the number of indexes to draw
 */
- (void)drawPrimitives:(MTLPrimitiveType)primitiveType vertexStart:(NSUInteger)vertexStart vertexCount:(NSUInteger)vertexCount;

/*!
 @method drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:instanceCount:
 @brief Draw primitives with an index list.
 @param primitiveType The type of primitives that elements are assembled into.
 @param indexCount The number of indexes to read from the index buffer for each instance.
 @param indexType The type if indexes, either 16 bit integer or 32 bit integer.
 @param indexBuffer A buffer object that the device will read indexes from.
 @param indexBufferOffset Byte offset within @a indexBuffer to start reading indexes from.  @a indexBufferOffset must be a multiple of the index size.
 @param instanceCount The number of instances drawn.
 */
- (void)drawIndexedPrimitives:(MTLPrimitiveType)primitiveType indexCount:(NSUInteger)indexCount indexType:(MTLIndexType)indexType indexBuffer:(id <MTLBuffer>)indexBuffer indexBufferOffset:(NSUInteger)indexBufferOffset instanceCount:(NSUInteger)instanceCount;

/*!
 @method drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:
 @brief Draw primitives with an index list.
 @param primitiveType The type of primitives that elements are assembled into.
 @param indexCount The number of indexes to read from the index buffer for each instance.
 @param indexType The type if indexes, either 16 bit integer or 32 bit integer.
 @param indexBuffer A buffer object that the device will read indexes from.
 @param indexBufferOffset Byte offset within @a indexBuffer to start reading indexes from.  @a indexBufferOffset must be a multiple of the index size.
 */
- (void)drawIndexedPrimitives:(MTLPrimitiveType)primitiveType indexCount:(NSUInteger)indexCount indexType:(MTLIndexType)indexType indexBuffer:(id <MTLBuffer>)indexBuffer indexBufferOffset:(NSUInteger)indexBufferOffset;

/*!
 @method drawPrimitives:vertexStart:vertexCount:instanceCount:baseInstance:
 @brief Draw primitives without an index list.
 @param primitiveType The type of primitives that elements are assembled into.
 @param vertexStart For each instance, the first index to draw
 @param vertexCount For each instance, the number of indexes to draw
 @param instanceCount The number of instances drawn.
 @param baseInstance Offset for instance_id.
 */
- (void)drawPrimitives:(MTLPrimitiveType)primitiveType vertexStart:(NSUInteger)vertexStart vertexCount:(NSUInteger)vertexCount instanceCount:(NSUInteger)instanceCount baseInstance:(NSUInteger)baseInstance API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:instanceCount:baseVertex:baseInstance:
 @brief Draw primitives with an index list.
 @param primitiveType The type of primitives that elements are assembled into.
 @param indexCount The number of indexes to read from the index buffer for each instance.
 @param indexType The type if indexes, either 16 bit integer or 32 bit integer.
 @param indexBuffer A buffer object that the device will read indexes from.
 @param indexBufferOffset Byte offset within @a indexBuffer to start reading indexes from.  @a indexBufferOffset must be a multiple of the index size.
 @param instanceCount The number of instances drawn.
 @param baseVertex Offset for vertex_id. NOTE: this can be negative
 @param baseInstance Offset for instance_id.
 */
- (void)drawIndexedPrimitives:(MTLPrimitiveType)primitiveType indexCount:(NSUInteger)indexCount indexType:(MTLIndexType)indexType indexBuffer:(id <MTLBuffer>)indexBuffer indexBufferOffset:(NSUInteger)indexBufferOffset instanceCount:(NSUInteger)instanceCount baseVertex:(NSInteger)baseVertex baseInstance:(NSUInteger)baseInstance API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method drawPrimitives:indirectBuffer:indirectBufferOffset:
 @brief Draw primitives without an index list using an indirect buffer see MTLDrawPrimitivesIndirectArguments.
 @param primitiveType The type of primitives that elements are assembled into.
 @param indirectBuffer A buffer object that the device will read drawPrimitives arguments from, see MTLDrawPrimitivesIndirectArguments.
 @param indirectBufferOffset Byte offset within @a indirectBuffer to start reading indexes from.  @a indirectBufferOffset must be a multiple of 4.
 */
- (void)drawPrimitives:(MTLPrimitiveType)primitiveType indirectBuffer:(id <MTLBuffer>)indirectBuffer indirectBufferOffset:(NSUInteger)indirectBufferOffset API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method drawIndexedPrimitives:indexType:indexBuffer:indexBufferOffset:indirectBuffer:indirectBufferOffset:
 @brief Draw primitives with an index list using an indirect buffer see MTLDrawIndexedPrimitivesIndirectArguments.
 @param primitiveType The type of primitives that elements are assembled into.
 @param indexType The type if indexes, either 16 bit integer or 32 bit integer.
 @param indexBuffer A buffer object that the device will read indexes from.
 @param indexBufferOffset Byte offset within @a indexBuffer to start reading indexes from.  @a indexBufferOffset must be a multiple of the index size.
 @param indirectBuffer A buffer object that the device will read drawIndexedPrimitives arguments from, see MTLDrawIndexedPrimitivesIndirectArguments.
 @param indirectBufferOffset Byte offset within @a indirectBuffer to start reading indexes from.  @a indirectBufferOffset must be a multiple of 4.
 */
- (void)drawIndexedPrimitives:(MTLPrimitiveType)primitiveType indexType:(MTLIndexType)indexType indexBuffer:(id <MTLBuffer>)indexBuffer indexBufferOffset:(NSUInteger)indexBufferOffset indirectBuffer:(id <MTLBuffer>)indirectBuffer indirectBufferOffset:(NSUInteger)indirectBufferOffset API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method textureBarrier
 @brief Ensure that following fragment shaders can read textures written by previous draw calls (in particular the framebuffer)
 */
- (void)textureBarrier API_DEPRECATED_WITH_REPLACEMENT("memoryBarrierWithScope:MTLBarrierScopeRenderTargets", macos(10.11, 10.14)) API_UNAVAILABLE(ios);

/*!
 @method updateFence:afterStages:
 @abstract Update the fence to capture all GPU work so far enqueued by this encoder for the given stages.
 @discussion Unlike <st>updateFence:</st>, this method will update the fence when the given stage(s) complete, allowing for commands to overlap in execution.
 On iOS, render command encoder fence updates are always delayed until the end of the encoder.
 */
- (void)updateFence:(id <MTLFence>)fence afterStages:(MTLRenderStages)stages API_AVAILABLE(macos(10.13), ios(10.0));

/*!
 @method waitForFence:beforeStages:
 @abstract Prevent further GPU work until the fence is reached for the given stages.
 @discussion Unlike <st>waitForFence:</st>, this method will only block commands assoicated with the given stage(s), allowing for commands to overlap in execution.
 On iOS, render command encoder fence waits always occur the beginning of the encoder.
 */
- (void)waitForFence:(id <MTLFence>)fence beforeStages:(MTLRenderStages)stages API_AVAILABLE(macos(10.13), ios(10.0));

-(void)setTessellationFactorBuffer:(nullable id <MTLBuffer>)buffer offset:(NSUInteger)offset instanceStride:(NSUInteger)instanceStride API_AVAILABLE(macos(10.12), ios(10.0));

-(void)setTessellationFactorScale:(float)scale API_AVAILABLE(macos(10.12), ios(10.0));

-(void)drawPatches:(NSUInteger)numberOfPatchControlPoints patchStart:(NSUInteger)patchStart patchCount:(NSUInteger)patchCount patchIndexBuffer:(nullable id <MTLBuffer>)patchIndexBuffer patchIndexBufferOffset:(NSUInteger)patchIndexBufferOffset instanceCount:(NSUInteger)instanceCount baseInstance:(NSUInteger)baseInstance API_AVAILABLE(macos(10.12), ios(10.0));

-(void)drawPatches:(NSUInteger)numberOfPatchControlPoints patchIndexBuffer:(nullable id <MTLBuffer>)patchIndexBuffer patchIndexBufferOffset:(NSUInteger)patchIndexBufferOffset indirectBuffer:(id <MTLBuffer>)indirectBuffer indirectBufferOffset:(NSUInteger)indirectBufferOffset API_AVAILABLE(macos(10.12), ios(12.0));

-(void)drawIndexedPatches:(NSUInteger)numberOfPatchControlPoints patchStart:(NSUInteger)patchStart patchCount:(NSUInteger)patchCount patchIndexBuffer:(nullable id <MTLBuffer>)patchIndexBuffer patchIndexBufferOffset:(NSUInteger)patchIndexBufferOffset controlPointIndexBuffer:(id <MTLBuffer>)controlPointIndexBuffer controlPointIndexBufferOffset:(NSUInteger)controlPointIndexBufferOffset instanceCount:(NSUInteger)instanceCount baseInstance:(NSUInteger)baseInstance API_AVAILABLE(macos(10.12), ios(10.0));

-(void)drawIndexedPatches:(NSUInteger)numberOfPatchControlPoints patchIndexBuffer:(nullable id <MTLBuffer>)patchIndexBuffer patchIndexBufferOffset:(NSUInteger)patchIndexBufferOffset controlPointIndexBuffer:(id <MTLBuffer>)controlPointIndexBuffer controlPointIndexBufferOffset:(NSUInteger)controlPointIndexBufferOffset indirectBuffer:(id <MTLBuffer>)indirectBuffer indirectBufferOffset:(NSUInteger)indirectBufferOffset API_AVAILABLE(macos(10.12), ios(12.0));

/*!
 @property tileWidth:
 @abstract The width of the tile for this render pass.
 */
@property (readonly) NSUInteger tileWidth API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @property tileHeight:
 @abstract The height of the tile for this render pass.
 */
@property (readonly) NSUInteger tileHeight API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/* Tile Resources */

/*!
 @method setTileBytes:length:atIndex:
 @brief Set the data (by copy) for a given tile buffer binding point.  This will remove any existing MTLBuffer from the binding point.
 */
- (void)setTileBytes:(const void *)bytes length:(NSUInteger)length atIndex:(NSUInteger)index API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @method setTileBuffer:offset:atIndex:
 @brief Set a global buffer for all tile shaders at the given bind point index.
 */
- (void)setTileBuffer:(nullable id <MTLBuffer>)buffer offset:(NSUInteger)offset atIndex:(NSUInteger)index API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @method setTileBufferOffset:atIndex:
 @brief Set the offset within the current global buffer for all tile shaders at the given bind point index.
 */
- (void)setTileBufferOffset:(NSUInteger)offset atIndex:(NSUInteger)index API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @method setTileBuffers:offsets:withRange:
 @brief Set an array of global buffers for all tile shaders with the given bind point range.
 */
- (void)setTileBuffers:(const id <MTLBuffer> __nullable [__nonnull])buffers offsets:(const NSUInteger [__nonnull])offsets withRange:(NSRange)range API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @method setTileTexture:atIndex:
 @brief Set a global texture for all tile shaders at the given bind point index.
 */
- (void)setTileTexture:(nullable id <MTLTexture>)texture atIndex:(NSUInteger)index API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @method setTileTextures:withRange:
 @brief Set an array of global textures for all tile shaders with the given bind point range.
 */
- (void)setTileTextures:(const id <MTLTexture> __nullable [__nonnull])textures withRange:(NSRange)range API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @method setTileSamplerState:atIndex:
 @brief Set a global sampler for all tile shaders at the given bind point index.
 */
- (void)setTileSamplerState:(nullable id <MTLSamplerState>)sampler atIndex:(NSUInteger)index API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @method setTileSamplerStates:withRange:
 @brief Set an array of global samplers for all fragment shaders with the given bind point range.
 */
- (void)setTileSamplerStates:(const id <MTLSamplerState> __nullable [__nonnull])samplers withRange:(NSRange)range API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @method setTileSamplerState:lodMinClamp:lodMaxClamp:atIndex:
 @brief Set a global sampler for all tile shaders at the given bind point index.
 */
- (void)setTileSamplerState:(nullable id <MTLSamplerState>)sampler lodMinClamp:(float)lodMinClamp lodMaxClamp:(float)lodMaxClamp atIndex:(NSUInteger)index API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

/*!
 @method setTileSamplerStates:lodMinClamps:lodMaxClamps:withRange:
 @brief Set an array of global samplers for all tile shaders with the given bind point range.
 */
- (void)setTileSamplerStates:(const id <MTLSamplerState> __nullable [__nonnull])samplers lodMinClamps:(const float [__nonnull])lodMinClamps lodMaxClamps:(const float [__nonnull])lodMaxClamps withRange:(NSRange)range;

/*!
 @method dispatchThreadsPerTile:
 @brief dispatch threads to perform a mid-render compute operation.
 */
- (void)dispatchThreadsPerTile:(MTLSize)threadsPerTile;

/*!
 @method setThreadgroupMemoryLength:offset:atIndex:
 @brief Set the size of the threadgroup memory argument at the given bind point index and offset.
 */
- (void)setThreadgroupMemoryLength:(NSUInteger)length offset:(NSUInteger)offset atIndex:(NSUInteger)index;


/*!
 * @method useResource:usage:
 * @abstract Declare that a resource may be accessed by the render pass through an argument buffer
 * @discussion This method does not protect against data hazards; these hazards must be addressed using an MTLFence. This method must be called before encoding any draw commands which may access the resource through an argument buffer. However, this method may cause color attachments to become decompressed. Therefore, this method should be called until as late as possible within a render command encoder. Declaring a minimal usage (i.e. read-only) may prevent color attachments from becoming decompressed on some devices.
 
     Note that calling useResource does not retain the resource. It is the responsiblity of the user to retain the resource until
     the command buffer has been executed.
 */
- (void)useResource:(id <MTLResource>)resource usage:(MTLResourceUsage)usage API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 * @method useResources:count:usage:
 * @abstract Declare that an array of resources may be accessed through an argument buffer by the render pass
 * @discussion This method does not protect against data hazards; these hazards must be addressed using an MTLFence. This method must be called before encoding any draw commands which may access the resources through an argument buffer. However, this method may cause color attachments to become decompressed. Therefore, this method should be called until as late as possible within a render command encoder. Declaring a minimal usage (i.e. read-only) may prevent color attachments from becoming decompressed on some devices.
 
   Note that calling useResources does not retain the resources. It is the responsiblity of the user to retain the resources until
   the command buffer has been executed.
*/
- (void)useResources:(const id <MTLResource> __nonnull[__nonnull])resources count:(NSUInteger)count usage:(MTLResourceUsage)usage API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 * @method useResources:usage:stage
 * @abstract Declare that a resource may be accessed by the render pass through an argument buffer
 * @For hazard tracked resources, this method protects against data hazards. This method must be called before encoding any draw commands which may access the resource through an argument buffer. However, this method may cause color attachments to become decompressed. Therefore, this method should be called until as late as possible within a render command encoder. Declaring a minimal usage (i.e. read-only) may prevent color attachments from becoming decompressed on some devices.
 
    Note that calling useResource does not retain the resource. It is the responsiblity of the user to retain the resource until
    the command buffer has been executed.
*/
- (void)useResource:(id <MTLResource>)resource usage:(MTLResourceUsage)usage stages:(MTLRenderStages) stages API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 * @method useResources:count:usage:stages
 * @abstract Declare that an array of resources may be accessed through an argument buffer by the render pass
 * @discussion For hazard tracked resources, this method protects against data hazards.  This method must be called before encoding any draw commands which may access the resources through an argument buffer. However, this method may cause color attachments to become decompressed. Therefore, this method should be called until as late as possible within a render command encoder. Declaring a minimal usage (i.e. read-only) may prevent color attachments from becoming decompressed on some devices.
 
   Note that calling useResources does not retain the resources. It is the responsiblity of the user to retain the resources until
   the command buffer has been executed.
*/
- (void)useResources:(const id <MTLResource> __nonnull[__nonnull])resources count:(NSUInteger)count usage:(MTLResourceUsage)usage stages:(MTLRenderStages)stages API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 * @method useHeap:
 * @abstract Declare that the resources allocated from a heap may be accessed by the render pass through an argument buffer
 * @discussion This method does not protect against data hazards; these hazards must be addressed using an MTLFence. This method must be called before encoding any draw commands which may access the resources allocated from the heap through an argument buffer. This method may cause all of the color attachments allocated from the heap to become decompressed. Therefore, it is recommended that the useResource:usage: or useResources:count:usage: methods be used for color attachments instead, with a minimal (i.e. read-only) usage.
 */
- (void)useHeap:(id <MTLHeap>)heap API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 * @method useHeaps:count:
 * @abstract Declare that the resources allocated from an array of heaps may be accessed by the render pass through an argument buffer
 * @discussion This method does not protect against data hazards; these hazards must be addressed using an MTLFence. This method must be called before encoding any draw commands which may access the resources allocated from the heaps through an argument buffer. This method may cause all of the color attachments allocated from the heaps to become decompressed. Therefore, it is recommended that the useResource:usage: or useResources:count:usage: methods be used for color attachments instead, with a minimal (i.e. read-only) usage.
 */
- (void)useHeaps:(const id <MTLHeap> __nonnull[__nonnull])heaps count:(NSUInteger)count API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 * @method useHeap:stages
 * @abstract Declare that the resources allocated from a heap may be accessed by the render pass through an argument buffer
 * @discussion If the heap is tracked, this method protects against hazard tracking; these hazards must be addressed using an MTLFence. This method must be called before encoding any draw commands which may access the resources allocated from the heap through an argument buffer. This method may cause all of the color attachments allocated from the heap to become decompressed. Therefore, it is recommended that the useResource:usage: or useResources:count:usage: methods be used for color attachments instead, with a minimal (i.e. read-only) usage.
 */
- (void)useHeap:(id <MTLHeap>)heap stages:(MTLRenderStages)stages API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 * @method useHeaps:count:stages
 * @abstract Declare that the resources allocated from an array of heaps may be accessed by the render pass through an argument buffer
 * @discussion This method does not protect against data hazards; these hazards must be addressed using an MTLFence. This method must be called before encoding any draw commands which may access the resources allocated from the heaps through an argument buffer. This method may cause all of the color attachments allocated from the heaps to become decompressed. Therefore, it is recommended that the useResource:usage: or useResources:count:usage: methods be used for color attachments instead, with a minimal (i.e. read-only) usage.
 */
- (void)useHeaps:(const id <MTLHeap> __nonnull[__nonnull])heaps count:(NSUInteger)count stages:(MTLRenderStages)stages API_AVAILABLE(macos(10.15), ios(13.0));


/*!
 * @method executeCommandsInBuffer:withRange:
 * @abstract Execute commands in the buffer within the range specified.
 * @discussion The same indirect command buffer may be executed any number of times within the same encoder.
 */
- (void)executeCommandsInBuffer:(id<MTLIndirectCommandBuffer>)indirectCommandBuffer withRange:(NSRange)executionRange API_AVAILABLE(macos(10.14), ios(12.0));

/*!
 * @method executeCommandsInBuffer:indirectBuffer:indirectBufferOffset:
 * @abstract Execute commands in the buffer within the range specified by the indirect range buffer.
 * @param indirectRangeBuffer An indirect buffer from which the device reads the execution range parameter, as laid out in the MTLIndirectCommandBufferExecutionRange structure.
 * @param indirectBufferOffset The byte offset within indirectBuffer where the execution range parameter is located. Must be a multiple of 4 bytes.
 * @discussion The same indirect command buffer may be executed any number of times within the same encoder.
 */
- (void)executeCommandsInBuffer:(id<MTLIndirectCommandBuffer>)indirectCommandbuffer indirectBuffer:(id<MTLBuffer>)indirectRangeBuffer indirectBufferOffset:(NSUInteger)indirectBufferOffset API_AVAILABLE(macos(10.14), uikitformac(13.0), ios(13.0));


/*!
 * @method memoryBarrierWithScope:afterStages:beforeStages:
 * @abstract Make stores to memory encoded before the barrier coherent with loads from memory encoded after the barrier.
 * @discussion The barrier makes stores coherent that 1) are to a resource with a type in the given scope, and 2) happen at (or before) the stage given by afterStages. Only affects loads that happen at (or after) the stage given by beforeStages.
 */
-(void)memoryBarrierWithScope:(MTLBarrierScope)scope afterStages:(MTLRenderStages)after beforeStages:(MTLRenderStages)before API_AVAILABLE(macos(10.14), uikitformac(13.0)) API_UNAVAILABLE(ios);

/*!
 * @method memoryBarrierWithResources:count:afterStages:beforeStages:
 * @abstract Make stores to memory encoded before the barrier coherent with loads from memory encoded after the barrier.
 * @discussion The barrier makes stores coherent that 1) are to resources in given array, and 2) happen at (or before) the stage given by afterStages. Only affects loads that happen at (or after) the stage give by beforeStages.
 */
-(void)memoryBarrierWithResources:(const id<MTLResource> __nonnull[__nonnull])resources count:(NSUInteger)count afterStages:(MTLRenderStages)after beforeStages:(MTLRenderStages)before API_AVAILABLE(macos(10.14), uikitformac(13.0)) API_UNAVAILABLE(ios);



@end
NS_ASSUME_NONNULL_END
