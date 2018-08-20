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
/*!
 @protocol MTLDrawable
 @abstract All "drawable" objects (such as those coming from CAMetalLayer) are expected to conform to this protocol
 */
NS_AVAILABLE(10_11, 8_0)
@protocol MTLDrawable <NSObject>

/* Present this drawable as soon as possible */
- (void)present;

/* Present this drawable at the given host time */
- (void)presentAtTime:(CFTimeInterval)presentationTime;

@end
NS_ASSUME_NONNULL_END// ==========  Metal.framework/Headers/MTLCommandEncoder.h
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
 @protocol MTLCommandEncoder
 @abstract MTLCommandEncoder is the common interface for objects that write commands into MTLCommandBuffers.
 */
NS_AVAILABLE(10_11, 8_0)
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
    MTLTextureTypeCubeArray NS_AVAILABLE_MAC(10_11) = 6,
    MTLTextureType3D = 7,
} NS_ENUM_AVAILABLE(10_11, 8_0);

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
} NS_ENUM_AVAILABLE(10_11, 9_0);

NS_CLASS_AVAILABLE(10_11, 8_0)
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
 @discussion When creating Buffer and Array textures, sampleCount must be 1. Implementations may round sample counts up to the next supported value.
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
 */
@property (readwrite, nonatomic) MTLResourceOptions resourceOptions;

/*!
 @property cpuCacheMode
 @abstract Options to specify CPU cache mode of texture resource.
 */
@property (readwrite, nonatomic) MTLCPUCacheMode cpuCacheMode NS_AVAILABLE(10_11, 9_0);

/*!
 @property storageMode
 @abstract To specify storage mode of texture resource.
 */
@property (readwrite, nonatomic) MTLStorageMode storageMode NS_AVAILABLE(10_11, 9_0);

/*!
 @property usage
 @abstract Description of texture usage
 */
@property (readwrite, nonatomic) MTLTextureUsage usage NS_AVAILABLE(10_11, 9_0);

@end

/*!
 @protocol MTLTexture
 @abstract MTLTexture represents a collection of 1D, 2D, or 3D images.
 @discussion
 Each image in a texture is a 1D, 2D, 2DMultisample, or 3D image. The texture contains one or more images arranged in a mipmap stack. If there are multiple mipmap stacks, each one is referred to as a slice of the texture. 1D, 2D, 2DMultisample, and 3D textures have a single slice. In 1DArray and 2DArray textures, every slice is an array element. A Cube texture always has 6 slices, one for each face. In a CubeArray texture, each set of six slices is one element in the array.
 
 Most APIs that operate on individual images in a texture address those images via a tuple of a Slice, and Mipmap Level within that slice.
 */
NS_AVAILABLE(10_11, 8_0)
@protocol MTLTexture <MTLResource>

/*!
 @property rootResource
 @abstract The resource this texture was created from. It may be a texture or a buffer. If this texture is not reusing storage of another MTLResource, then nil is returned.
 */
@property (nullable, readonly) id <MTLResource> rootResource;


/*!
 @property parentTexture
 @abstract The texture this texture view was created from, or nil if this is not a texture view or it was not created from a texture.
 */
@property (nullable, readonly) id <MTLTexture> parentTexture NS_AVAILABLE(10_11, 9_0);

/*!
 @property parentRelativeLevel
 @abstract The base level of the texture this texture view was created from, or 0 if this is not a texture view.
 */
@property (readonly) NSUInteger parentRelativeLevel NS_AVAILABLE(10_11, 9_0);

/*!
 @property parentRelativeSlice
 @abstract The base slice of the texture this texture view was created from, or 0 if this is not a texture view.
 */
@property (readonly) NSUInteger parentRelativeSlice NS_AVAILABLE(10_11, 9_0);

/*!
 @property buffer
 @abstract The buffer this texture view was created from, or nil if this is not a texture view or it was not created from a buffer.
 */
@property (nullable, readonly) id <MTLBuffer> buffer NS_AVAILABLE_IOS(9_0);

/*!
 @property bufferOffset
 @abstract The offset of the buffer this texture view was created from, or 0 if this is not a texture view.
 */
@property (readonly) NSUInteger bufferOffset NS_AVAILABLE_IOS(9_0);

/*!
 @property bufferBytesPerRow
 @abstract The bytesPerRow of the buffer this texture view was created from, or 0 if this is not a texture view.
 */
@property (readonly) NSUInteger bufferBytesPerRow NS_AVAILABLE_IOS(9_0);



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
 @property framebufferOnly
 @abstract If YES, this texture can only be used with a MTLAttachmentDescriptor, and cannot be used as a texture argument for MTLRenderCommandEncoder, MTLBlitCommandEncoder, or MTLComputeCommandEncoder. Furthermore, when this property's value is YES, readPixels/writePixels may not be used with this texture.
 @discussion Textures obtained from CAMetalDrawables may have this property set to YES, depending on the value of frameBufferOnly passed to their parent CAMetalLayer. Textures created directly by the application will not have any restrictions.
 */
@property (readonly, getter = isFramebufferOnly) BOOL framebufferOnly;

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
- (id<MTLTexture>)newTextureViewWithPixelFormat:(MTLPixelFormat)pixelFormat;

/*!
 @method newTextureViewWithPixelFormat:textureType:levels:slices:
 @abstract Create a new texture which shares the same storage as the source texture, but with a different (but compatible) pixel format, texture type, levels and slices.
 */
- (id<MTLTexture>)newTextureViewWithPixelFormat:(MTLPixelFormat)pixelFormat textureType:(MTLTextureType)textureType levels:(NSRange)levelRange slices:(NSRange)sliceRange;


@end
NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLDevice.h
//
//  MTLDevice.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLTypes.h>
#import <Metal/MTLPixelFormat.h>
#import <Metal/MTLResource.h>
#import <Metal/MTLLibrary.h>

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

/*!
 @brief Returns a reference to the preferred system default Metal device.
 @discussion On Mac OS X systems that support automatic graphics switching, calling
 this API to get a Metal device will cause the system to switch to the high power
 GPU.  On other systems that support more than one GPU it will return the GPU that
 is associated with the main display.
 */
MTL_EXTERN id <MTLDevice> __nullable MTLCreateSystemDefaultDevice(void) NS_AVAILABLE(10_11, 8_0);

/*!
 @brief Returns all Metal devices in the system.
 @discussion This API will not cause the system to switch devices and leaves the
 decision about which GPU to use up to the application based on whatever criteria
 it deems appropriate.
*/
MTL_EXTERN NSArray <id<MTLDevice>> *MTLCopyAllDevices(void) NS_AVAILABLE_MAC(10_11);


typedef NS_ENUM(NSUInteger, MTLFeatureSet)
{
    MTLFeatureSet_iOS_GPUFamily1_v1 NS_ENUM_AVAILABLE_IOS(8_0) = 0,
    MTLFeatureSet_iOS_GPUFamily2_v1 NS_ENUM_AVAILABLE_IOS(8_0) = 1,
    
    MTLFeatureSet_iOS_GPUFamily1_v2 NS_ENUM_AVAILABLE_IOS(9_0) = 2,
    MTLFeatureSet_iOS_GPUFamily2_v2 NS_ENUM_AVAILABLE_IOS(9_0) = 3,
    MTLFeatureSet_iOS_GPUFamily3_v1 NS_ENUM_AVAILABLE_IOS(9_0) = 4,

    MTLFeatureSet_OSX_GPUFamily1_v1 NS_ENUM_AVAILABLE_MAC(10_11)   = 10000,
} NS_ENUM_AVAILABLE(10_11, 8_0);

/*!
 @enum MTLPipelineOption
 @abstract Controls the creation of the pipeline
 */
typedef NS_OPTIONS(NSUInteger, MTLPipelineOption)
{
    MTLPipelineOptionNone               = 0,
    MTLPipelineOptionArgumentInfo       = 1 << 0,
    MTLPipelineOptionBufferTypeInfo     = 1 << 1,
} NS_ENUM_AVAILABLE(10_11, 8_0);

/* Convenience typedefs that make it easy to declare storage for certain return types. */
typedef __autoreleasing MTLRenderPipelineReflection * __nullable MTLAutoreleasedRenderPipelineReflection;
typedef __autoreleasing MTLComputePipelineReflection * __nullable MTLAutoreleasedComputePipelineReflection;

typedef void (^MTLNewLibraryCompletionHandler)(id <MTLLibrary> __nullable library, NSError * __nullable error);

typedef void (^MTLNewRenderPipelineStateCompletionHandler)(id <MTLRenderPipelineState> __nullable renderPipelineState, NSError * __nullable error);
typedef void (^MTLNewRenderPipelineStateWithReflectionCompletionHandler)(id <MTLRenderPipelineState> __nullable renderPipelineState, MTLRenderPipelineReflection * __nullable reflection, NSError * __nullable error);

typedef void (^MTLNewComputePipelineStateCompletionHandler)(id <MTLComputePipelineState> __nullable computePipelineState, NSError * __nullable error);
typedef void (^MTLNewComputePipelineStateWithReflectionCompletionHandler)(id <MTLComputePipelineState> __nullable computePipelineState, MTLComputePipelineReflection * __nullable reflection, NSError * __nullable error);

/*!
 @protocol MTLDevice
 @abstract MTLDevice represents a processor capable of data parallel computations
 */
NS_AVAILABLE(10_11, 8_0)
@protocol MTLDevice <NSObject>

/*!
 @property name
 @abstract The full name of the vendor device.
 */
@property (nullable, readonly) NSString *name;

/*!
 @property maxThreadsPerThreadgroup
 @abstract The maximum number of threads along each dimension.
 */
@property (readonly) MTLSize maxThreadsPerThreadgroup NS_AVAILABLE(10_11, 9_0);

/*!
 @property lowPower
 @abstract On systems that support automatic graphics switching, this will return YES for the the low power device.
 */
@property (readonly, getter=isLowPower) BOOL lowPower NS_AVAILABLE_MAC(10_11);

/*!
 @property headless
 @abstract On systems that include more that one GPU, this will return YES for any device that does not support any displays.  Only available on Mac OS X.
 */
@property (readonly, getter=isHeadless) BOOL headless NS_AVAILABLE_MAC(10_11);

/*!
 @property depth24Stencil8PixelFormatSupported
 @abstract If YES, device supports MTLPixelFormatDepth24Unorm_Stencil8.
 */
@property (readonly, getter=isDepth24Stencil8PixelFormatSupported) BOOL depth24Stencil8PixelFormatSupported NS_AVAILABLE_MAC(10_11);

/*!
 @method newCommandQueue
 @brief Create and return a new command queue.   Command Queues created via this method will only allow up to 64 non-completed command buffers.
 @return The new command queue object
 */
- (id <MTLCommandQueue>)newCommandQueue;

/*!
 @method newCommandQueueWithMaxCommandBufferCount
 @brief Create and return a new command queue with a given upper bound on non-completed command buffers.
 @return The new command queue object
 */
- (id <MTLCommandQueue>)newCommandQueueWithMaxCommandBufferCount:(NSUInteger)maxCommandBufferCount;

/*!
 @method newBufferWithLength:options:
 @brief Create a buffer by allocating new memory.
 */
- (id <MTLBuffer>)newBufferWithLength:(NSUInteger)length options:(MTLResourceOptions)options;

/*!
 @method newBufferWithBytes:length:options:
 @brief Create a buffer by allocating new memory and specifing the initial contents to be copied into it.
 */
- (id <MTLBuffer>)newBufferWithBytes:(const void *)pointer length:(NSUInteger)length options:(MTLResourceOptions)options;

/*!
 @method newBufferWithBytesNoCopy:length:options:deallocator:
 @brief Create a buffer by wrapping an existing part of the address space.
 */
- (id <MTLBuffer>)newBufferWithBytesNoCopy:(void *)pointer length:(NSUInteger)length options:(MTLResourceOptions)options deallocator:(void (^ __nullable)(void *pointer, NSUInteger length))deallocator;

/*!
 @method newDepthStencilStateWithDescriptor:
 @brief Create a depth/stencil test state object.
 */
- (id <MTLDepthStencilState>)newDepthStencilStateWithDescriptor:(MTLDepthStencilDescriptor *)descriptor;

/*!
 @method newTextureWithDescriptor:
 @abstract Allocate a new texture with privately owned storage.
 */
- (id <MTLTexture>)newTextureWithDescriptor:(MTLTextureDescriptor *)descriptor;

/*!
 @method newSamplerStateWithDescriptor:
 @abstract Create a new sampler.
*/
- (id <MTLSamplerState>)newSamplerStateWithDescriptor:(MTLSamplerDescriptor *)descriptor;

/*!
 @method newDefaultLibrary
 @abstract Returns the default library for the main bundle.
 */
- (nullable id <MTLLibrary>)newDefaultLibrary;

/*!
 @method newLibraryWithFile:
 @abstract Load a MTLLibrary from a metallib file.
 */
- (nullable id <MTLLibrary>)newLibraryWithFile:(NSString *)filepath error:(__autoreleasing NSError **)error;

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
- (nullable id <MTLComputePipelineState>)newComputePipelineStateWithDescriptor:(MTLComputePipelineDescriptor *)descriptor options:(MTLPipelineOption)options reflection:(MTLAutoreleasedComputePipelineReflection * __nullable)reflection error:(__autoreleasing NSError **)error NS_AVAILABLE(10_11, 9_0);

/*!
 @method newComputePipelineStateWithDescriptor:options:completionHandler:
 @abstract Create and compile a new MTLComputePipelineState object asynchronously.
 */
- (void)newComputePipelineStateWithDescriptor:(MTLComputePipelineDescriptor *)descriptor options:(MTLPipelineOption)options completionHandler:(MTLNewComputePipelineStateWithReflectionCompletionHandler)completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 @method supportsFeatureSet:
 @abstract Returns TRUE if the feature set is supported by this MTLDevice.
 */
- (BOOL)supportsFeatureSet:(MTLFeatureSet)featureSet;

/*!
 @method supportsTextureSampleCount:
 @brief Query device if it support textures with a given sampleCount.
 @return BOOL value. If YES, device supports the given sampleCount for textures. If NO, device does not support the given sampleCount.
 */
- (BOOL)supportsTextureSampleCount:(NSUInteger)sampleCount NS_AVAILABLE(10_11, 9_0);

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
typedef NS_ENUM(NSUInteger, MTLDataType){
    
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
} NS_ENUM_AVAILABLE(10_11, 8_0);

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
    
} NS_ENUM_AVAILABLE(10_11, 8_0);

/*!
 @enum MTLArgumentAccess
*/
typedef NS_ENUM(NSUInteger, MTLArgumentAccess) {
    
    MTLArgumentAccessReadOnly   = 0,
    MTLArgumentAccessReadWrite  = 1,
    MTLArgumentAccessWriteOnly  = 2,
    
} NS_ENUM_AVAILABLE(10_11, 8_0);

@class MTLStructType;
@class MTLArrayType;

NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLStructMember : NSObject
 
@property (readonly) NSString *name;
@property (readonly) NSUInteger offset;
@property (readonly) MTLDataType dataType;
 
- (nullable MTLStructType *)structType;
- (nullable MTLArrayType *)arrayType;
 
@end
 
NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLStructType  : NSObject

@property (readonly) NSArray <MTLStructMember *> *members;

- (nullable MTLStructMember *)memberByName:(NSString *)name;
@end
 
NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLArrayType  : NSObject
 
@property (readonly) NSUInteger arrayLength;
 
@property (readonly) MTLDataType elementType;
@property (readonly) NSUInteger stride;
 
- (nullable MTLStructType *)elementStructType;
- (nullable MTLArrayType *)elementArrayType;
@end

/*!
 MTLArgument
*/
NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLArgument : NSObject

@property (readonly) NSString *name;
@property (readonly) MTLArgumentType type;
@property (readonly) MTLArgumentAccess access;
@property (readonly) NSUInteger index;

@property (readonly, getter=isActive) BOOL active;

// for buffer arguments
@property (readonly) NSUInteger     bufferAlignment;		// min alignment of starting offset in the buffer
@property (readonly) NSUInteger     bufferDataSize; 		// sizeof(T) for T *argName
@property (readonly) MTLDataType    bufferDataType; 		// MTLDataTypeFloat, MTLDataTypeFloat4, MTLDataTypeStruct, ...
@property (readonly) MTLStructType *bufferStructType;

// for threadgroup memory arguments
@property (readonly) NSUInteger     threadgroupMemoryAlignment;
@property (readonly) NSUInteger     threadgroupMemoryDataSize; // sizeof(T) for T *argName

// for texture arguments
@property (readonly) MTLTextureType textureType; // texture1D, texture2D...
@property (readonly) MTLDataType    textureDataType; // half, float, int, or uint.

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

NS_ASSUME_NONNULL_BEGIN
@protocol MTLFunction;
@protocol MTLBuffer;
@protocol MTLSamplerState;
@protocol MTLTexture;
@protocol MTLComputePipelineState;

typedef struct {
    uint32_t threadgroupsPerGrid[3];
} MTLDispatchThreadgroupsIndirectArguments;


/*!
 @protocol MTLComputeCommandEncoder
 @abstract A command encoder that writes data parallel compute commands.
 */
NS_AVAILABLE(10_11, 8_0)
@protocol MTLComputeCommandEncoder <MTLCommandEncoder>

/*!
 @method setComputePipelineState:
 @abstract Set the compute pipeline state that will be used.
 */
- (void)setComputePipelineState:(id <MTLComputePipelineState>)state;

/*!
 @method setBytes:length:atIndex:
 @brief Set the data (by copy) for a given buffer binding point.  This will remove any existing MTLBuffer from the binding point.
 */
- (void)setBytes:(const void *)bytes length:(NSUInteger)length atIndex:(NSUInteger)index NS_AVAILABLE(10_11, 8_3);

/*!
 @method setBuffer:offset:atIndex:
 @brief Set a global buffer for all compute kernels at the given bind point index.
 */
- (void)setBuffer:(nullable id <MTLBuffer>)buffer offset:(NSUInteger)offset atIndex:(NSUInteger)index;

/*!
 @method setBufferOffset:atIndex:
 @brief Set the offset within the current global buffer for all compute kernels at the given bind point index.
 */
- (void)setBufferOffset:(NSUInteger)offset atIndex:(NSUInteger)index NS_AVAILABLE(10_11, 8_3);

/*!
 @method setBuffers:offsets:withRange:
 @brief Set an array of global buffers for all compute kernels with the given bind point range.
 */
- (void)setBuffers:(const id <MTLBuffer> __nullable [__nullable])buffers offsets:(const NSUInteger [__nullable])offsets withRange:(NSRange)range;

/*!
 @method setTexture:atIndex:
 @brief Set a global texture for all compute kernels at the given bind point index.
 */
- (void)setTexture:(nullable id <MTLTexture>)texture atIndex:(NSUInteger)index;

/*!
 @method setTextures:withRange:
 @brief Set an array of global textures for all compute kernels with the given bind point range.
 */
- (void)setTextures:(const id <MTLTexture> __nullable [__nullable])textures withRange:(NSRange)range;

/*!
 @method setSamplerState:atIndex:
 @brief Set a global sampler for all compute kernels at the given bind point index.
 */
- (void)setSamplerState:(nullable id <MTLSamplerState>)sampler atIndex:(NSUInteger)index;

/*!
 @method setSamplers:withRange:
 @brief Set an array of global samplers for all compute kernels with the given bind point range.
 */
- (void)setSamplerStates:(const id <MTLSamplerState> __nullable [__nullable])samplers withRange:(NSRange)range;

/*!
 @method setSamplerState:lodMinClamp:lodMaxClamp:atIndex:
 @brief Set a global sampler for all compute kernels at the given bind point index.
 */
- (void)setSamplerState:(nullable id <MTLSamplerState>)sampler lodMinClamp:(float)lodMinClamp lodMaxClamp:(float)lodMaxClamp atIndex:(NSUInteger)index;

/*!
 @method setSamplers:lodMinClamps:lodMaxClamps:withRange:
 @brief Set an array of global samplers for all compute kernels with the given bind point range.
 */
- (void)setSamplerStates:(const id <MTLSamplerState> __nullable [__nullable])samplers lodMinClamps:(const float [__nullable])lodMinClamps lodMaxClamps:(const float [__nullable])lodMaxClamps withRange:(NSRange)range;

/*!
 @method setThreadgroupMemoryLength:atIndex:
 @brief Set the threadgroup memory byte length at the binding point specified by the index. This applies to all compute kernels.
 */
- (void)setThreadgroupMemoryLength:(NSUInteger)length atIndex:(NSUInteger)index;

/*
 @method dispatchThreadgroups:threadsPerThreadgroup:
 @abstract Enqueue a compute function dispatch.
 */
- (void)dispatchThreadgroups:(MTLSize)threadgroupsPerGrid threadsPerThreadgroup:(MTLSize)threadsPerThreadgroup;

/*
 @method dispatchThreadgroupsWithIndirectBuffer:indirectBufferOffset:threadsPerThreadgroup:
 @abstract Enqueue a compute function dispatch using an indirect buffer for threadgroupsPerGrid see MTLDispatchThreadgroupsIndirectArguments.
 @param indirectBuffer A buffer object that the device will read dispatchThreadgroups arguments from, see MTLDispatchThreadgroupsIndirectArguments.
 @param indirectBufferOffset Byte offset within @a indirectBuffer to read arguments from.  @a indirectBufferOffset must be a multiple of 4.
 */
- (void)dispatchThreadgroupsWithIndirectBuffer:(id <MTLBuffer>)indirectBuffer indirectBufferOffset:(NSUInteger)indirectBufferOffset threadsPerThreadgroup:(MTLSize)threadsPerThreadgroup NS_AVAILABLE(10_11, 9_0);


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
#import <Metal/MTLRenderPass.h>
#import <Metal/MTLPixelFormat.h>
#import <Metal/MTLArgument.h>

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
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef NS_ENUM(NSUInteger, MTLBlendOperation) {
    MTLBlendOperationAdd = 0,
    MTLBlendOperationSubtract = 1,
    MTLBlendOperationReverseSubtract = 2,
    MTLBlendOperationMin = 3,
    MTLBlendOperationMax = 4,
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef NS_OPTIONS(NSUInteger, MTLColorWriteMask) {
    MTLColorWriteMaskNone  = 0,
    MTLColorWriteMaskRed   = 0x1 << 3,
    MTLColorWriteMaskGreen = 0x1 << 2,
    MTLColorWriteMaskBlue  = 0x1 << 1,
    MTLColorWriteMaskAlpha = 0x1 << 0,
    MTLColorWriteMaskAll   = 0xf
} NS_ENUM_AVAILABLE(10_11, 8_0);


@class MTLRenderPipelineColorAttachmentDescriptorArray;

NS_CLASS_AVAILABLE(10_11, 8_0)
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


NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLRenderPipelineReflection : NSObject

@property (nullable, readonly) NSArray <MTLArgument *> *vertexArguments;
@property (nullable, readonly) NSArray <MTLArgument *> *fragmentArguments;

@end

NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLRenderPipelineDescriptor : NSObject <NSCopying>

@property (nullable, copy, nonatomic) NSString *label;

@property (nullable, readwrite, nonatomic, strong) id <MTLFunction> vertexFunction;
@property (nullable, readwrite, nonatomic, strong) id <MTLFunction> fragmentFunction;

@property (nullable, copy, nonatomic) MTLVertexDescriptor *vertexDescriptor;

/* Rasterization and visibility state */
@property (readwrite, nonatomic) NSUInteger sampleCount;
@property (readwrite, nonatomic, getter = isAlphaToCoverageEnabled) BOOL alphaToCoverageEnabled;
@property (readwrite, nonatomic, getter = isAlphaToOneEnabled) BOOL alphaToOneEnabled;
@property (readwrite, nonatomic, getter = isRasterizationEnabled) BOOL rasterizationEnabled;

@property (readonly) MTLRenderPipelineColorAttachmentDescriptorArray *colorAttachments;

@property (nonatomic) MTLPixelFormat depthAttachmentPixelFormat;
@property (nonatomic) MTLPixelFormat stencilAttachmentPixelFormat;


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
NS_AVAILABLE(10_11, 8_0)
@protocol MTLRenderPipelineState <NSObject>

@property (nullable, readonly) NSString *label;
@property (readonly) id <MTLDevice> device;

@end

NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLRenderPipelineColorAttachmentDescriptorArray : NSObject

/* Individual attachment state access */
- (MTLRenderPipelineColorAttachmentDescriptor *)objectAtIndexedSubscript:(NSUInteger)attachmentIndex;

/* This always uses 'copy' semantics.  It is safe to set the attachment state at any legal index to nil, which resets that attachment descriptor state to default vaules. */
- (void)setObject:(nullable MTLRenderPipelineColorAttachmentDescriptor *)attachment atIndexedSubscript:(NSUInteger)attachmentIndex;

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
} NS_ENUM_AVAILABLE(10_11, 8_0);

 /*!
 @constant MTLCommandBufferErrorDomain
 @abstract An error domain for NSError objects produced by MTLCommandBuffer
 */
NS_AVAILABLE(10_11, 8_0)
MTL_EXTERN NSString *const MTLCommandBufferErrorDomain;

/*!
 @enum MTLCommandBufferError
 @abstract Error codes that can be found in MTLCommandBuffer.error
 @constant MTLCommandBufferErrorInternal An internal error that doesn't fit into the other categories. The actual low level error code is encoded in the local description.
 @constant MTLCommandBufferErrorTimeout Execution of this command buffer took too long, execution of this command was interrupted and aborted.
 @constant MTLCommandBufferErrorPageFault Execution of this command buffer generated an unserviceable GPU page fault. This can caused by buffer read write attribute mismatch or out of boundary access.
 @constant MTLCommandBufferErrorBlacklisted Access to this device has been revoked because this client has been responsible for too many timeouts or hangs.
 @constant MTLCommandBufferErrorNotPermitted This process does not have access to use this device.
 @constant MTLCommandBufferErrorOutOfMemory Insufficient memory was available to execute this command buffer.
 @constant MTLCommandBufferErrorInvalidResource The command buffer referenced an invalid resource.  This is most commonly caused when the caller deletes a resource before executing a command buffer that refers to it.
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
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef void (^MTLCommandBufferHandler)(id <MTLCommandBuffer>);

/*!
 @protocol MTLCommandBuffer
 @abstract A serial list of commands for the device to execute.
 */
NS_AVAILABLE(10_11, 8_0)
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
 */
- (void)presentDrawable:(id <MTLDrawable>)drawable;

/*!
 @method presentDrawable:atTime:
 @abstract Add a drawable present for a specific host time that will be invoked when this command buffer has been scheduled for execution.
 */
- (void)presentDrawable:(id <MTLDrawable>)drawable atTime:(CFTimeInterval)presentationTime;

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
- (id <MTLBlitCommandEncoder>)blitCommandEncoder;

/*!
 @method renderCommandEncoderWithFramebuffer:
 @abstract returns a render command endcoder to encode into this command buffer.
 */
- (id <MTLRenderCommandEncoder>)renderCommandEncoderWithDescriptor:(MTLRenderPassDescriptor *)renderPassDescriptor;

/*!
 @method computeCommandEncoder
 @abstract returns a compute command encoder to encode into this command buffer.
 */
- (id <MTLComputeCommandEncoder>)computeCommandEncoder;

/*!
 @method parallelRenderCommandEncoderWithFramebuffer:
 @abstract returns a parallel render pass encoder to encode into this command buffer.
 */
- (id <MTLParallelRenderCommandEncoder>)parallelRenderCommandEncoderWithDescriptor:(MTLRenderPassDescriptor *)renderPassDescriptor;

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
    MTLPixelFormatR8Unorm_sRGB NS_AVAILABLE_IOS(8_0) = 11,

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
    MTLPixelFormatRG8Unorm_sRGB NS_AVAILABLE_IOS(8_0) = 31,
    MTLPixelFormatRG8Snorm                            = 32,
    MTLPixelFormatRG8Uint                             = 33,
    MTLPixelFormatRG8Sint                             = 34,

    /* Packed 16 bit formats */
    
    MTLPixelFormatB5G6R5Unorm NS_AVAILABLE_IOS(8_0) = 40,
    MTLPixelFormatA1BGR5Unorm NS_AVAILABLE_IOS(8_0) = 41,
    MTLPixelFormatABGR4Unorm  NS_AVAILABLE_IOS(8_0) = 42,
    MTLPixelFormatBGR5A1Unorm NS_AVAILABLE_IOS(8_0) = 43,

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

    /* Normal 64 bit formats */

    MTLPixelFormatRG32Uint  = 103,
    MTLPixelFormatRG32Sint  = 104,
    MTLPixelFormatRG32Float = 105,

    MTLPixelFormatRGBA16Unorm  = 110,
    MTLPixelFormatRGBA16Snorm  = 112,
    MTLPixelFormatRGBA16Uint   = 113,
    MTLPixelFormatRGBA16Sint   = 114,
    MTLPixelFormatRGBA16Float  = 115,

    /* Normal 128 bit formats */

    MTLPixelFormatRGBA32Uint  = 123,
    MTLPixelFormatRGBA32Sint  = 124,
    MTLPixelFormatRGBA32Float = 125,

    /* Compressed formats. */

    /* S3TC/DXT */
    MTLPixelFormatBC1_RGBA              NS_AVAILABLE_MAC(10_11) = 130,
    MTLPixelFormatBC1_RGBA_sRGB         NS_AVAILABLE_MAC(10_11) = 131,
    MTLPixelFormatBC2_RGBA              NS_AVAILABLE_MAC(10_11) = 132,
    MTLPixelFormatBC2_RGBA_sRGB         NS_AVAILABLE_MAC(10_11) = 133,
    MTLPixelFormatBC3_RGBA              NS_AVAILABLE_MAC(10_11) = 134,
    MTLPixelFormatBC3_RGBA_sRGB         NS_AVAILABLE_MAC(10_11) = 135,

    /* RGTC */
    MTLPixelFormatBC4_RUnorm            NS_AVAILABLE_MAC(10_11) = 140,
    MTLPixelFormatBC4_RSnorm            NS_AVAILABLE_MAC(10_11) = 141,
    MTLPixelFormatBC5_RGUnorm           NS_AVAILABLE_MAC(10_11) = 142,
    MTLPixelFormatBC5_RGSnorm           NS_AVAILABLE_MAC(10_11) = 143,

    /* BPTC */
    MTLPixelFormatBC6H_RGBFloat         NS_AVAILABLE_MAC(10_11) = 150,
    MTLPixelFormatBC6H_RGBUfloat        NS_AVAILABLE_MAC(10_11) = 151,
    MTLPixelFormatBC7_RGBAUnorm         NS_AVAILABLE_MAC(10_11) = 152,
    MTLPixelFormatBC7_RGBAUnorm_sRGB    NS_AVAILABLE_MAC(10_11) = 153,

    /* PVRTC */
    MTLPixelFormatPVRTC_RGB_2BPP        NS_AVAILABLE_IOS(8_0) = 160,
    MTLPixelFormatPVRTC_RGB_2BPP_sRGB   NS_AVAILABLE_IOS(8_0) = 161,
    MTLPixelFormatPVRTC_RGB_4BPP        NS_AVAILABLE_IOS(8_0) = 162,
    MTLPixelFormatPVRTC_RGB_4BPP_sRGB   NS_AVAILABLE_IOS(8_0) = 163,
    MTLPixelFormatPVRTC_RGBA_2BPP       NS_AVAILABLE_IOS(8_0) = 164,
    MTLPixelFormatPVRTC_RGBA_2BPP_sRGB  NS_AVAILABLE_IOS(8_0) = 165,
    MTLPixelFormatPVRTC_RGBA_4BPP       NS_AVAILABLE_IOS(8_0) = 166,
    MTLPixelFormatPVRTC_RGBA_4BPP_sRGB  NS_AVAILABLE_IOS(8_0) = 167,

    /* ETC2 */
    MTLPixelFormatEAC_R11Unorm          NS_AVAILABLE_IOS(8_0) = 170,
    MTLPixelFormatEAC_R11Snorm          NS_AVAILABLE_IOS(8_0) = 172,
    MTLPixelFormatEAC_RG11Unorm         NS_AVAILABLE_IOS(8_0) = 174,
    MTLPixelFormatEAC_RG11Snorm         NS_AVAILABLE_IOS(8_0) = 176,
    MTLPixelFormatEAC_RGBA8             NS_AVAILABLE_IOS(8_0) = 178,
    MTLPixelFormatEAC_RGBA8_sRGB        NS_AVAILABLE_IOS(8_0) = 179,

    MTLPixelFormatETC2_RGB8             NS_AVAILABLE_IOS(8_0) = 180,
    MTLPixelFormatETC2_RGB8_sRGB        NS_AVAILABLE_IOS(8_0) = 181,
    MTLPixelFormatETC2_RGB8A1           NS_AVAILABLE_IOS(8_0) = 182,
    MTLPixelFormatETC2_RGB8A1_sRGB      NS_AVAILABLE_IOS(8_0) = 183,

    /* ASTC */
    MTLPixelFormatASTC_4x4_sRGB         NS_AVAILABLE_IOS(8_0) = 186,
    MTLPixelFormatASTC_5x4_sRGB         NS_AVAILABLE_IOS(8_0) = 187,
    MTLPixelFormatASTC_5x5_sRGB         NS_AVAILABLE_IOS(8_0) = 188,
    MTLPixelFormatASTC_6x5_sRGB         NS_AVAILABLE_IOS(8_0) = 189,
    MTLPixelFormatASTC_6x6_sRGB         NS_AVAILABLE_IOS(8_0) = 190,
    MTLPixelFormatASTC_8x5_sRGB         NS_AVAILABLE_IOS(8_0) = 192,
    MTLPixelFormatASTC_8x6_sRGB         NS_AVAILABLE_IOS(8_0) = 193,
    MTLPixelFormatASTC_8x8_sRGB         NS_AVAILABLE_IOS(8_0) = 194,
    MTLPixelFormatASTC_10x5_sRGB        NS_AVAILABLE_IOS(8_0) = 195,
    MTLPixelFormatASTC_10x6_sRGB        NS_AVAILABLE_IOS(8_0) = 196,
    MTLPixelFormatASTC_10x8_sRGB        NS_AVAILABLE_IOS(8_0) = 197,
    MTLPixelFormatASTC_10x10_sRGB       NS_AVAILABLE_IOS(8_0) = 198,
    MTLPixelFormatASTC_12x10_sRGB       NS_AVAILABLE_IOS(8_0) = 199,
    MTLPixelFormatASTC_12x12_sRGB       NS_AVAILABLE_IOS(8_0) = 200,

    MTLPixelFormatASTC_4x4_LDR          NS_AVAILABLE_IOS(8_0) = 204,
    MTLPixelFormatASTC_5x4_LDR          NS_AVAILABLE_IOS(8_0) = 205,
    MTLPixelFormatASTC_5x5_LDR          NS_AVAILABLE_IOS(8_0) = 206,
    MTLPixelFormatASTC_6x5_LDR          NS_AVAILABLE_IOS(8_0) = 207,
    MTLPixelFormatASTC_6x6_LDR          NS_AVAILABLE_IOS(8_0) = 208,
    MTLPixelFormatASTC_8x5_LDR          NS_AVAILABLE_IOS(8_0) = 210,
    MTLPixelFormatASTC_8x6_LDR          NS_AVAILABLE_IOS(8_0) = 211,
    MTLPixelFormatASTC_8x8_LDR          NS_AVAILABLE_IOS(8_0) = 212,
    MTLPixelFormatASTC_10x5_LDR         NS_AVAILABLE_IOS(8_0) = 213,
    MTLPixelFormatASTC_10x6_LDR         NS_AVAILABLE_IOS(8_0) = 214,
    MTLPixelFormatASTC_10x8_LDR         NS_AVAILABLE_IOS(8_0) = 215,
    MTLPixelFormatASTC_10x10_LDR        NS_AVAILABLE_IOS(8_0) = 216,
    MTLPixelFormatASTC_12x10_LDR        NS_AVAILABLE_IOS(8_0) = 217,
    MTLPixelFormatASTC_12x12_LDR        NS_AVAILABLE_IOS(8_0) = 218,

    /*!
     @constant MTLPixelFormatGBGR422
     @abstract A pixel format where the red and green channels are subsampled horizontally.  Two pixels are stored in 32 bits, with shared red and blue values, and unique green values.
     @discussion This format is equivelent to YUY2, YUYV, yuvs, or GL_RGB_422_APPLE/GL_UNSIGNED_SHORT_8_8_REV_APPLE.   The component order, from lowest addressed byte to highest, is Y0, Cb, Y1, Cr.  There is no implicit colorspace conversion from YUV to RGB, the shader will receive (Cr, Y, Cb, 1).  422 textures must have a width that is a multiple of 2, and can only be used for 2D non-mipmap textures.  When sampling, ClampToEdge is the only usable wrap mode.
     */
    MTLPixelFormatGBGR422 = 240,

    /*!
     @constant MTLPixelFormatBGRG422
     @abstract A pixel format where the red and green channels are subsampled horizontally.  Two pixels are stored in 32 bits, with shared red and blue values, and unique green values.
     @discussion This format is equivelent to UYVY, 2vuy, or GL_RGB_422_APPLE/GL_UNSIGNED_SHORT_8_8_APPLE. The component order, from lowest addressed byte to highest, is Cb, Y0, Cr, Y1.  There is no implicit colorspace conversion from YUV to RGB, the shader will receive (Cr, Y, Cb, 1).  422 textures must have a width that is a multiple of 2, and can only be used for 2D non-mipmap textures.  When sampling, ClampToEdge is the only usable wrap mode.
     */
    MTLPixelFormatBGRG422 = 241,

    /* Depth */

    MTLPixelFormatDepth32Float  = 252,

    /* Stencil */

    MTLPixelFormatStencil8        = 253,

    /* Depth Stencil */
    
    MTLPixelFormatDepth24Unorm_Stencil8  NS_AVAILABLE_MAC(10_11) = 255,
    MTLPixelFormatDepth32Float_Stencil8  NS_AVAILABLE(10_11, 9_0) = 260,

} NS_ENUM_AVAILABLE(10_11, 8_0);
NS_ASSUME_NONNULL_END// ==========  Metal.framework/Headers/MTLBlitCommandEncoder.h
//
//  MTLBlitCommandEncoder.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLCommandEncoder.h>
#import <Metal/MTLBuffer.h>
#import <Metal/MTLTexture.h>

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
    MTLBlitOptionRowLinearPVRTC NS_AVAILABLE_IOS(9_0) = 1 << 2,
} NS_ENUM_AVAILABLE(10_11, 9_0);

/*!
 @protocol MTLBlitCommandEncoder
 @abstract A command encoder that performs basic copies and blits between buffers and textures.
 */
NS_AVAILABLE(10_11, 8_0)
@protocol MTLBlitCommandEncoder <MTLCommandEncoder>

/*!
 @method synchronizeResource:
 @abstract Flush any copy of this resource from the device's caches, and invalidate any CPU caches if needed.
 @param resource The resource to page off.
 @discussion When the device writes to a resource with a storage mode of MTLResourceStorageModeManaged, those writes may be cached (for example, in VRAM or on chip renderer cache),
 making any CPU access (either MTLBuffer.contents or -[MTLTexture getBytes:...] and -[MTLTexture replaceRegion:]) produce undefined results.  To allow the CPU to see what the device
 has written, a CommandBuffer containing this synchronization must be executed.  After completion of the CommandBuffer, the CPU can access the contents of the resource safely.
 */
- (void)synchronizeResource:(id<MTLResource>)resource NS_AVAILABLE_MAC(10_11);

/*!
 @method synchronizeTexture:slice:mipmapLevel:
 @abstract Flush any copy of this image from the device's caches, and invalidate CPU caches if needed.
 @param texture The texture to page off.
 @param slice The slice of the texture to page off.
 @param level The mipmap level of the texture to flush.
 @discussion
 See the discussion of -synchronizeResource.   -synchronizeTexture:slice:mipmapLevel performs the same role, except it may flush only a subset of the texture storage, rather than the entire texture.
 */
- (void)synchronizeTexture:(id<MTLTexture>)texture slice:(NSUInteger)slice level:(NSUInteger)level NS_AVAILABLE_MAC(10_11);

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
- (void)copyFromBuffer:(id<MTLBuffer>)sourceBuffer sourceOffset:(NSUInteger)sourceOffset sourceBytesPerRow:(NSUInteger)sourceBytesPerRow sourceBytesPerImage:(NSUInteger)sourceBytesPerImage sourceSize:(MTLSize)sourceSize toTexture:(id<MTLTexture>)destinationTexture destinationSlice:(NSUInteger)destinationSlice destinationLevel:(NSUInteger)destinationLevel destinationOrigin:(MTLOrigin)destinationOrigin options:(MTLBlitOption)options NS_AVAILABLE(10_11, 9_0);

/*!
 @method copyFromTexture:sourceSlice:sourceLevel:sourceOrigin:sourceSize:toBuffer:destinationOffset:destinationBytesPerRow:destinationBytesPerImage:
 @abstract Copy an image from a texture into a buffer.
 */
- (void)copyFromTexture:(id<MTLTexture>)sourceTexture sourceSlice:(NSUInteger)sourceSlice sourceLevel:(NSUInteger)sourceLevel sourceOrigin:(MTLOrigin)sourceOrigin sourceSize:(MTLSize)sourceSize toBuffer:(id<MTLBuffer>)destinationBuffer destinationOffset:(NSUInteger)destinationOffset destinationBytesPerRow:(NSUInteger)destinationBytesPerRow destinationBytesPerImage:(NSUInteger)destinationBytesPerImage;

/*!
 @method copyFromTexture:sourceSlice:sourceLevel:sourceOrigin:sourceSize:sourceOptions:toBuffer:destinationOffset:destinationBytesPerRow:destinationBytesPerImage:options:
 @abstract Copy an image from a texture into a buffer.
 */
- (void)copyFromTexture:(id<MTLTexture>)sourceTexture sourceSlice:(NSUInteger)sourceSlice sourceLevel:(NSUInteger)sourceLevel sourceOrigin:(MTLOrigin)sourceOrigin sourceSize:(MTLSize)sourceSize toBuffer:(id<MTLBuffer>)destinationBuffer destinationOffset:(NSUInteger)destinationOffset destinationBytesPerRow:(NSUInteger)destinationBytesPerRow destinationBytesPerImage:(NSUInteger)destinationBytesPerImage options:(MTLBlitOption)options NS_AVAILABLE(10_11, 9_0);

/*!
 @method generateMipmapsForTexture:
 @abstract Generate mipmaps for a texture from the base level up to the max level.
 */
- (void)generateMipmapsForTexture:(id<MTLTexture>)texture;

/*!
 @method fillBuffer:range:value:
 @abstract Fill a buffer with a fixed value in each byte.
 */
- (void)fillBuffer:(id <MTLBuffer>)buffer range:(NSRange)range value:(uint8_t)value;

/*!
 @method copyFromBuffer:sourceOffset:toBuffer:destinationOffset:size:
 @abstract Basic memory copy between buffers.
 */
- (void)copyFromBuffer:(id <MTLBuffer>)sourceBuffer sourceOffset:(NSUInteger)sourceOffset toBuffer:(id <MTLBuffer>)destinationBuffer destinationOffset:(NSUInteger)destinationOffset size:(NSUInteger)size;

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
/*
 MTLVertexFormat
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
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef NS_ENUM(NSUInteger, MTLVertexStepFunction)
{
    MTLVertexStepFunctionConstant = 0,
    MTLVertexStepFunctionPerVertex = 1,
    MTLVertexStepFunctionPerInstance = 2,
} NS_ENUM_AVAILABLE(10_11, 8_0);

NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLVertexBufferLayoutDescriptor : NSObject <NSCopying>
@property (assign, nonatomic) NSUInteger stride;
@property (assign, nonatomic) MTLVertexStepFunction stepFunction;
@property (assign, nonatomic) NSUInteger stepRate;
@end

NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLVertexBufferLayoutDescriptorArray : NSObject
- (MTLVertexBufferLayoutDescriptor *)objectAtIndexedSubscript:(NSUInteger)index;
- (void)setObject:(nullable MTLVertexBufferLayoutDescriptor *)bufferDesc atIndexedSubscript:(NSUInteger)index;
@end

NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLVertexAttributeDescriptor : NSObject <NSCopying>
@property (assign, nonatomic) MTLVertexFormat format;
@property (assign, nonatomic) NSUInteger offset;
@property (assign, nonatomic) NSUInteger bufferIndex;
@end

NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLVertexAttributeDescriptorArray : NSObject
- (MTLVertexAttributeDescriptor *)objectAtIndexedSubscript:(NSUInteger)index;
- (void)setObject:(nullable MTLVertexAttributeDescriptor *)attributeDesc atIndexedSubscript:(NSUInteger)index;
@end

/*
 MTLVertexDescriptor
 */
NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLVertexDescriptor : NSObject <NSCopying>

+ (MTLVertexDescriptor *)vertexDescriptor;

@property (readonly) MTLVertexBufferLayoutDescriptorArray *layouts;
@property (readonly) MTLVertexAttributeDescriptorArray *attributes;

- (void)reset;

@end
NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLTypes.h
//
//  MTLTypes.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

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
 @abstract A set of dimensions to declare the size of an object such as a compute kernel work group or grid.
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

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLComputePipelineReflection : NSObject

@property (readonly) NSArray <MTLArgument *> *arguments;


@end

NS_CLASS_AVAILABLE(10_11, 9_0)
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
NS_AVAILABLE(10_11, 8_0)
@protocol MTLComputePipelineState <NSObject>

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

NS_ASSUME_NONNULL_BEGIN
@protocol MTLDevice;

typedef NS_ENUM(NSUInteger, MTLLoadAction) {
    MTLLoadActionDontCare = 0,
    MTLLoadActionLoad = 1,
    MTLLoadActionClear = 2,
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef NS_ENUM(NSUInteger, MTLStoreAction) {
    MTLStoreActionDontCare = 0,
    MTLStoreActionStore = 1,
    MTLStoreActionMultisampleResolve = 2,
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef struct
{
    double red;
    double green;
    double blue;
    double alpha;
} MTLClearColor;

// Should we provide a set of APIs similar to the old methods below?
MTL_INLINE MTLClearColor MTLClearColorMake(double red, double green, double blue, double alpha);

@protocol MTLTexture;
@protocol MTLBuffer;

NS_CLASS_AVAILABLE(10_11, 8_0)
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

@end

NS_CLASS_AVAILABLE(10_11, 8_0)
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
} NS_ENUM_AVAILABLE_IOS(9_0);

NS_CLASS_AVAILABLE(10_11, 8_0)
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
@property (nonatomic) MTLMultisampleDepthResolveFilter depthResolveFilter NS_AVAILABLE_IOS(9_0);

@end

NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLRenderPassStencilAttachmentDescriptor : MTLRenderPassAttachmentDescriptor

/*!
 @property clearStencil
 @abstract The clear stencil value to be used if the loadAction property is MTLLoadActionClear
 */
@property (nonatomic) uint32_t clearStencil;

@end

NS_CLASS_AVAILABLE(10_11, 8_0)
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
NS_CLASS_AVAILABLE(10_11, 8_0)
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

 @constant MTLPurgeableStateNoVolatile
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
} NS_ENUM_AVAILABLE(10_11, 8_0);

/*!
 @enum MTLCPUCacheMode
 @abstract Describes what CPU cache mode is used for the CPU's mapping of a resource.
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
} NS_ENUM_AVAILABLE(10_11, 8_0);

/*!
 @enum MTLStorageMode
 @abstract Describes location and CPU mapping of MTLResource (MTLTexture or MTLBuffer).
 @constant MTLStorageModeShared
 In this mode, CPU and device will nominally both use the same underlying memory when accessing the contents of the resource.
 However, coherency is only guaranteed at command buffer boundaries to minimize the required flushing of CPU and GPU caches.
 This is the default storage mode for iOS Textures.

 @constant MTLStorageModeManaged
 This mode relaxes the coherency requirements and requires that the developer make explicit requests to maintain
 coherency between a CPU and GPU version of the resource.  Changes due to CPU stores outside of the Metal API must be
 indicated to Metal via MTLBuffer::didModifyRange:(NSRange)range.  In order for CPU to access up to date GPU results,
 first, a blit synchronizations must be completed (see synchronize methods of MTLBlitCommandEncoder).
 Blit overhead is only incurred if GPU has modified the resource.
 This is the default storage mode for OS X Textures.

 @constant MTLStorageModePrivate
 This mode allows the data to be kept entirely to GPU (or driver) private memory that will never be accessed by the CPU directly, so no
 conherency of any kind must be maintained.
*/
typedef NS_ENUM(NSUInteger, MTLStorageMode)
{
    MTLStorageModeShared  = 0,
    MTLStorageModeManaged NS_ENUM_AVAILABLE(10_11, NA) = 1,
    MTLStorageModePrivate = 2,
} NS_ENUM_AVAILABLE(10_11, 9_0);

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

 @constant MTLResourceStorageModeManaged
 This mode relaxes the coherency requirements and requires that the developer make explicit requests to maintain
 coherency between a CPU and GPU version of the resource.  Changes due to CPU stores outside of the Metal API must be
 indicated to Metal via MTLBuffer::didModifyRange:(NSRange)range.  In order for CPU to access up to date GPU results,
 first, a blit synchronizations must be completed (see synchronize methods of MTLBlitCommandEncoder).
 Blit overhead is only incurred if GPU has modified the resource.
 This storage mode is only defined for OS X.

 @constant MTLResourceStorageModePrivate
 This mode allows the data to be kept entirely to GPU (or driver) private memory that will never be accessed by the CPU directly, so no
 conherency of any kind must be maintained.

 @discussion
 Note that resource options are a property of MTLTextureDescriptor (resourceOptions), so apply to texture creation.
 they are also passed directly into MTLBuffer creation methods.
*/

#define MTLResourceCPUCacheModeShift 0
#define MTLResourceCPUCacheModeMask  (0xfUL << MTLResourceCPUCacheModeShift)
#define MTLResourceStorageModeShift  4
#define MTLResourceStorageModeMask   (0xfUL << MTLResourceStorageModeShift)

typedef NS_OPTIONS(NSUInteger, MTLResourceOptions)
{
    MTLResourceCPUCacheModeDefaultCache  = MTLCPUCacheModeDefaultCache  << MTLResourceCPUCacheModeShift,
    MTLResourceCPUCacheModeWriteCombined = MTLCPUCacheModeWriteCombined << MTLResourceCPUCacheModeShift,

    MTLResourceStorageModeShared  NS_ENUM_AVAILABLE(10_11, 9_0) = MTLStorageModeShared  << MTLResourceStorageModeShift,
    MTLResourceStorageModeManaged NS_ENUM_AVAILABLE(10_11, NA)  = MTLStorageModeManaged << MTLResourceStorageModeShift,
    MTLResourceStorageModePrivate NS_ENUM_AVAILABLE(10_11, 9_0) = MTLStorageModePrivate << MTLResourceStorageModeShift,

    // Deprecated spellings
    MTLResourceOptionCPUCacheModeDefault       = MTLResourceCPUCacheModeDefaultCache,
    MTLResourceOptionCPUCacheModeWriteCombined = MTLResourceCPUCacheModeWriteCombined,
} NS_ENUM_AVAILABLE(10_11, 8_0);

@protocol MTLDevice;

/*!
 @protocol MTLResource
 @abstract Common APIs available for MTLBuffer and MTLTexture instances
 */
NS_AVAILABLE(10_11, 8_0)
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
@property (readonly) MTLStorageMode storageMode NS_AVAILABLE(10_11, 9_0);
 
/*!
 @method setPurgeableState
 @abstract Set (or query) the purgeability state of a resource
 @discussion Synchronously set the purgeability state of a resource and return what the prior (or current) state is.
 FIXME: If the device is keeping a cached copy of the resource, both the shared copy and cached copy are made purgeable.  Any access to the resource by either the CPU or device will be undefined.
 */
- (MTLPurgeableState)setPurgeableState:(MTLPurgeableState)state;
 
@end
NS_ASSUME_NONNULL_END
// ==========  Metal.framework/Headers/MTLDefines.h
//
//  MTLDefines.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Availability.h>
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


#define MTL_DEPRECATED __attribute__((deprecated))
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
 @abstract A typeless allocation accessible by both the CPU and the GPU (MTLDevice).
 
 @discussion
 Unlike in OpenGL and OpenCL, access to buffers is not synchronized.  The caller may use the CPU to modify the data at any time
 but is also responsible for ensuring synchronization and coherency.
 
 The contents become undefined if both the CPU and GPU write to the same buffer without a synchronizing action between those writes.
 This is true even when the regions written do not overlap.
 */
NS_AVAILABLE(10_11, 8_0)
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
- (void)didModifyRange:(NSRange)range NS_AVAILABLE_MAC(10_11);

/*!
 @method newTextureWithDescriptor:offset:bytesPerRow:
 @abstract Create a 2D texture that shares storage with this buffer.
*/
- (id <MTLTexture>)newTextureWithDescriptor:(MTLTextureDescriptor*)descriptor offset:(NSUInteger)offset bytesPerRow:(NSUInteger)bytesPerRow NS_AVAILABLE_IOS(8_0);

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
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef NS_ENUM(NSUInteger, MTLStencilOperation) {
    MTLStencilOperationKeep = 0,
    MTLStencilOperationZero = 1,
    MTLStencilOperationReplace = 2,
    MTLStencilOperationIncrementClamp = 3,
    MTLStencilOperationDecrementClamp = 4,
    MTLStencilOperationInvert = 5,
    MTLStencilOperationIncrementWrap = 6,
    MTLStencilOperationDecrementWrap = 7,
} NS_ENUM_AVAILABLE(10_11, 8_0);

NS_CLASS_AVAILABLE(10_11, 8_0)
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

NS_CLASS_AVAILABLE(10_11, 8_0)
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
NS_AVAILABLE(10_11, 8_0)
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
// ==========  Metal.framework/Headers/MTLParallelRenderCommandEncoder.h
//
//  MTLParallelRenderCommandEncoder.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Metal/MTLDefines.h>
#import <Metal/MTLRenderPass.h>
#import <Metal/MTLCommandEncoder.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLDevice;
@protocol MTLRenderCommandEncoder;

/*!
 @protocol MTLParallelRenderCommandEncoder
 @discussion The MTLParallelRenderCommandEncoder protocol is designed to allow a single render to texture operation to be efficiently (and safely) broken up across multiple threads.
 */
NS_AVAILABLE(10_11, 8_0)
@protocol MTLParallelRenderCommandEncoder <MTLCommandEncoder>

/*!
 @method renderCommandEncoder
 @abstract Return a new autoreleased object that conforms to <MTLRenderCommandEncoder> that may be used to encode on a different thread.
 */
- (id <MTLRenderCommandEncoder>)renderCommandEncoder;

@end
NS_ASSUME_NONNULL_END// ==========  Metal.framework/Headers/MTLSampler.h
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
} NS_ENUM_AVAILABLE(10_11, 8_0);

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
} NS_ENUM_AVAILABLE(10_11, 8_0);

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
 */
typedef NS_ENUM(NSUInteger, MTLSamplerAddressMode) {
    MTLSamplerAddressModeClampToEdge = 0,
    MTLSamplerAddressModeMirrorClampToEdge NS_AVAILABLE_MAC(10_11) = 1,
    MTLSamplerAddressModeRepeat = 2,
    MTLSamplerAddressModeMirrorRepeat = 3,
    MTLSamplerAddressModeClampToZero = 4,
} NS_ENUM_AVAILABLE(10_11, 8_0);

/*!
 @class MTLSamplerDescriptor
 @abstract A mutable descriptor used to configure a sampler.  When complete, this can be used to create an immutable MTLSamplerState.
 */
NS_CLASS_AVAILABLE(10_11, 8_0)
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
@property (nonatomic) BOOL lodAverage NS_AVAILABLE_IOS(9_0);

/*!
 @property compareFunction
 @abstract Set the comparison function used when sampling shadow maps. The default value is MTLCompareFunctionNever.
 */
@property (nonatomic) MTLCompareFunction compareFunction NS_AVAILABLE(10_11, 9_0);

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
NS_AVAILABLE(10_11, 8_0)
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
NS_ASSUME_NONNULL_END// ==========  Metal.framework/Headers/MTLLibrary.h
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

NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLVertexAttribute : NSObject
 
@property (nullable, readonly) NSString *name;
@property (readonly) NSUInteger                   attributeIndex;
@property (readonly) MTLDataType                  attributeType NS_AVAILABLE(10_11, 8_3);
@property (readonly, getter=isActive) BOOL        active;
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
} NS_ENUM_AVAILABLE(10_11, 8_0);

/*!
 @protocol MTLFunction
 @abstract A handle to to intermediate code used as inputs for either a MTLComputePipelineState or a MTLRenderPipelineState.
 @discussion MTLFunction is a single vertex shader, fragment shader, or compute function.  A Function can only be used with the device that it was created against.
*/
NS_AVAILABLE(10_11, 8_0)
@protocol MTLFunction <NSObject>

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

@property (nullable, readonly) NSArray <MTLVertexAttribute *> *vertexAttributes;

/*!
 @property name
 @abstract The name of the function in the shading language.
 */
@property (readonly) NSString *name;

@end

typedef NS_ENUM(NSUInteger, MTLLanguageVersion) {

    MTLLanguageVersion1_0 NS_ENUM_AVAILABLE(NA, 9_0) = (1 << 16),
    MTLLanguageVersion1_1 = (1 << 16) + 1,
} NS_ENUM_AVAILABLE(10_11, 9_0);


NS_CLASS_AVAILABLE(10_11, 8_0)
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
@property (readwrite, nonatomic) MTLLanguageVersion languageVersion NS_AVAILABLE(10_11, 9_0);

@end

/*!
 @constant MTLLibraryErrorDomain
 @abstract NSErrors raised when creating a library.
 */
NS_AVAILABLE(10_11, 8_0)
MTL_EXTERN NSString *const MTLLibraryErrorDomain;

/*!
 @enum MTLLibraryError
 @abstract NSErrors raised when creating a library.
 */
typedef NS_ENUM(NSUInteger, MTLLibraryError) {
    MTLLibraryErrorUnsupported      = 1,
    MTLLibraryErrorInternal         = 2,
    MTLLibraryErrorCompileFailure   = 3,
    MTLLibraryErrorCompileWarning   = 4,
} NS_ENUM_AVAILABLE(10_11, 8_0);

MTL_EXTERN NSString *const MTLRenderPipelineErrorDomain;

/*!
 @enum MTLRenderPipelineError
 @abstract NSErrors raised when creating a pipeline or kernel.
 */
typedef NS_ENUM(NSUInteger, MTLRenderPipelineError) {
    MTLRenderPipelineErrorInternal          = 1,    
    MTLRenderPipelineErrorUnsupported       = 2,
    MTLRenderPipelineErrorInvalidInput      = 3,
} NS_ENUM_AVAILABLE(10_11, 8_0);


NS_AVAILABLE(10_11, 8_0)
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
NS_AVAILABLE(10_11, 8_0)
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
- (id <MTLCommandBuffer>)commandBuffer;

/*!
 @method commandBufferWithUnretainedReferences
 @abstract Returns a new autoreleased command buffer used to encode work into this queue that 
 does not maintain strong references to resources used within the command buffer.
*/
- (id <MTLCommandBuffer>)commandBufferWithUnretainedReferences;

/*!
 @method insertDebugCaptureBoundary
 @abstract Inform Xcode about when debug capture should start and stop.
 */
- (void)insertDebugCaptureBoundary;

@end
NS_ASSUME_NONNULL_END// ==========  Metal.framework/Headers/MTLRenderCommandEncoder.h
//
//  MTLRenderCommandEncoder.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLCommandEncoder.h>
#import <Metal/MTLCommandBuffer.h>

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
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef NS_ENUM(NSUInteger, MTLIndexType) {
    MTLIndexTypeUInt16 = 0,
    MTLIndexTypeUInt32 = 1,
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef NS_ENUM(NSUInteger, MTLVisibilityResultMode) {
    MTLVisibilityResultModeDisabled = 0,
    MTLVisibilityResultModeBoolean = 1,
    MTLVisibilityResultModeCounting NS_ENUM_AVAILABLE(10_11, 9_0) = 2,
} NS_ENUM_AVAILABLE(10_11, 8_0);

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
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef NS_ENUM(NSUInteger, MTLWinding) {
    MTLWindingClockwise = 0,
    MTLWindingCounterClockwise = 1,
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef NS_ENUM(NSUInteger, MTLDepthClipMode) {
    MTLDepthClipModeClip = 0,
    MTLDepthClipModeClamp = 1,
} NS_ENUM_AVAILABLE(10_11, 9_0);

typedef NS_ENUM(NSUInteger, MTLTriangleFillMode) {
    MTLTriangleFillModeFill = 0,
    MTLTriangleFillModeLines = 1,
} NS_ENUM_AVAILABLE(10_11, 8_0);

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

/*!
 @protocol MTLRenderCommandEncoder
 @discussion MTLRenderCommandEncoder is a container for graphics rendering state and the code to translate the state into a command format that the device can execute. 
 */
NS_AVAILABLE(10_11, 8_0)
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
- (void)setVertexBytes:(const void *)bytes length:(NSUInteger)length atIndex:(NSUInteger)index NS_AVAILABLE(10_11, 8_3);

/*!
 @method setVertexBuffer:offset:atIndex:
 @brief Set a global buffer for all vertex shaders at the given bind point index.
 */
- (void)setVertexBuffer:(nullable id <MTLBuffer>)buffer offset:(NSUInteger)offset atIndex:(NSUInteger)index;

/*!
 @method setVertexBufferOffset:atIndex:
 @brief Set the offset within the current global buffer for all vertex shaders at the given bind point index.
 */
- (void)setVertexBufferOffset:(NSUInteger)offset atIndex:(NSUInteger)index NS_AVAILABLE(10_11, 8_3);

/*!
 @method setVertexBuffers:offsets:withRange:
 @brief Set an array of global buffers for all vertex shaders with the given bind point range.
 */
- (void)setVertexBuffers:(const id <MTLBuffer> __nullable [__nullable])buffers offsets:(const NSUInteger [__nullable])offsets withRange:(NSRange)range;

/*!
 @method setVertexTexture:atIndex:
 @brief Set a global texture for all vertex shaders at the given bind point index.
 */
- (void)setVertexTexture:(nullable id <MTLTexture>)texture atIndex:(NSUInteger)index;

/*!
 @method setVertexTextures:withRange:
 @brief Set an array of global textures for all vertex shaders with the given bind point range.
 */
- (void)setVertexTextures:(const id <MTLTexture> __nullable [__nullable])textures withRange:(NSRange)range;

/*!
 @method setVertexSamplerState:atIndex:
 @brief Set a global sampler for all vertex shaders at the given bind point index.
 */
- (void)setVertexSamplerState:(nullable id <MTLSamplerState>)sampler atIndex:(NSUInteger)index;

/*!
 @method setVertexSamplerStates:withRange:
 @brief Set an array of global samplers for all vertex shaders with the given bind point range.
 */
- (void)setVertexSamplerStates:(const id <MTLSamplerState> __nullable [__nullable])samplers withRange:(NSRange)range;

/*!
 @method setVertexSamplerState:lodMinClamp:lodMaxClamp:atIndex:
 @brief Set a global sampler for all vertex shaders at the given bind point index.
 */
- (void)setVertexSamplerState:(nullable id <MTLSamplerState>)sampler lodMinClamp:(float)lodMinClamp lodMaxClamp:(float)lodMaxClamp atIndex:(NSUInteger)index;

/*!
 @method setVertexSamplerStates:lodMinClamps:lodMaxClamps:withRange:
 @brief Set an array of global samplers for all vertex shaders with the given bind point range.
 */
- (void)setVertexSamplerStates:(const id <MTLSamplerState> __nullable [__nullable])samplers lodMinClamps:(const float [__nullable])lodMinClamps lodMaxClamps:(const float [__nullable])lodMaxClamps withRange:(NSRange)range;

/* Vertex Shaders */

/*!
 @method setViewport:
 @brief Set the viewport, which is used to transform vertexes from normalized device coordinates to window coordinates.  Fragments that lie outside of the viewport are clipped, and optionally clamped for fragments outside of znear/zfar.
 */
- (void)setViewport:(MTLViewport)viewport;

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
- (void)setDepthClipMode:(MTLDepthClipMode)depthClipMode NS_AVAILABLE(10_11, 9_0);

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
 @method setTriangleFillMode:
 @brief Set how to rasterize triangle and triangle strip primitives.
 */
- (void)setTriangleFillMode:(MTLTriangleFillMode)fillMode;

/* Fragment Resources */

/*!
 @method setFragmentBytes:length:atIndex:
 @brief Set the data (by copy) for a given fragment buffer binding point.  This will remove any existing MTLBuffer from the binding point.
 */
- (void)setFragmentBytes:(const void *)bytes length:(NSUInteger)length atIndex:(NSUInteger)index NS_AVAILABLE(10_11, 8_3);

/*!
 @method setFragmentBuffer:offset:atIndex:
 @brief Set a global buffer for all fragment shaders at the given bind point index.
 */
- (void)setFragmentBuffer:(nullable id <MTLBuffer>)buffer offset:(NSUInteger)offset atIndex:(NSUInteger)index;

/*!
 @method setFragmentBufferOffset:atIndex:
 @brief Set the offset within the current global buffer for all fragment shaders at the given bind point index.
 */
- (void)setFragmentBufferOffset:(NSUInteger)offset atIndex:(NSUInteger)index NS_AVAILABLE(10_11, 8_3);

/*!
 @method setFragmentBuffers:offsets:withRange:
 @brief Set an array of global buffers for all fragment shaders with the given bind point range.
 */
- (void)setFragmentBuffers:(const id <MTLBuffer> __nullable [__nullable])buffers offsets:(const NSUInteger [__nullable])offset withRange:(NSRange)range;

/*!
 @method setFragmentTexture:atIndex:
 @brief Set a global texture for all fragment shaders at the given bind point index.
 */
- (void)setFragmentTexture:(nullable id <MTLTexture>)texture atIndex:(NSUInteger)index;

/*!
 @method setFragmentTextures:withRange:
 @brief Set an array of global textures for all fragment shaders with the given bind point range.
 */
- (void)setFragmentTextures:(const id <MTLTexture> __nullable [__nullable])textures withRange:(NSRange)range;

/*!
 @method setFragmentSamplerState:atIndex:
 @brief Set a global sampler for all fragment shaders at the given bind point index.
 */
- (void)setFragmentSamplerState:(nullable id <MTLSamplerState>)sampler atIndex:(NSUInteger)index;

/*!
 @method setFragmentSamplerStates:withRange:
 @brief Set an array of global samplers for all fragment shaders with the given bind point range.
 */
- (void)setFragmentSamplerStates:(const id <MTLSamplerState> __nullable [__nullable])samplers withRange:(NSRange)range;

/*!
 @method setFragmentSamplerState:lodMinClamp:lodMaxClamp:atIndex:
 @brief Set a global sampler for all fragment shaders at the given bind point index.
 */
- (void)setFragmentSamplerState:(nullable id <MTLSamplerState>)sampler lodMinClamp:(float)lodMinClamp lodMaxClamp:(float)lodMaxClamp atIndex:(NSUInteger)index;

/*!
 @method setFragmentSamplerStates:lodMinClamps:lodMaxClamps:withRange:
 @brief Set an array of global samplers for all fragment shaders with the given bind point range.
 */
- (void)setFragmentSamplerStates:(const id <MTLSamplerState> __nullable [__nullable])samplers lodMinClamps:(const float [__nullable])lodMinClamps lodMaxClamps:(const float [__nullable])lodMaxClamps withRange:(NSRange)range;

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
- (void)setStencilFrontReferenceValue:(uint32_t)frontReferenceValue backReferenceValue:(uint32_t)backReferenceValue NS_AVAILABLE(10_11, 9_0);

/*!
 @method setVisibilityResultMode:offset:
 @abstract Monitor if samples pass the depth and stencil tests.
 @param mode Controls if the counter is disabled or moniters passing samples.
 @param offset The offset relative to the occlusion query buffer provided when the command encoder was created.  offset must be a multiple of 8.
 */
- (void)setVisibilityResultMode:(MTLVisibilityResultMode)mode offset:(NSUInteger)offset;

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
 @method drawPrimitives:vertexStart:vertexCount:instanceCount:
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
 @method drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:instanceCount:
 @brief Draw primitives with an index list.
 @param primitiveType The type of primitives that elements are assembled into.
 @param indexCount The number of indexes to read from the index buffer for each instance.
 @param indexType The type if indexes, either 16 bit integer or 32 bit integer.
 @param indexBuffer A buffer object that the device will read indexes from.
 @param indexBufferOffset Byte offset within @a indexBuffer to start reading indexes from.  @a indexBufferOffset must be a multiple of the index size.
 */
- (void)drawIndexedPrimitives:(MTLPrimitiveType)primitiveType indexCount:(NSUInteger)indexCount indexType:(MTLIndexType)indexType indexBuffer:(id <MTLBuffer>)indexBuffer indexBufferOffset:(NSUInteger)indexBufferOffset;

/*!
 @method drawPrimitives:vertexStart:vertexCount:instanceCount:
 @brief Draw primitives without an index list.
 @param primitiveType The type of primitives that elements are assembled into.
 @param vertexStart For each instance, the first index to draw
 @param vertexCount For each instance, the number of indexes to draw
 @param instanceCount The number of instances drawn.
 @param baseInstance Offset for instance_id.
 */
- (void)drawPrimitives:(MTLPrimitiveType)primitiveType vertexStart:(NSUInteger)vertexStart vertexCount:(NSUInteger)vertexCount instanceCount:(NSUInteger)instanceCount baseInstance:(NSUInteger)baseInstance NS_AVAILABLE(10_11, 9_0);

/*!
 @method drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:instanceCount:
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
- (void)drawIndexedPrimitives:(MTLPrimitiveType)primitiveType indexCount:(NSUInteger)indexCount indexType:(MTLIndexType)indexType indexBuffer:(id <MTLBuffer>)indexBuffer indexBufferOffset:(NSUInteger)indexBufferOffset instanceCount:(NSUInteger)instanceCount baseVertex:(NSInteger)baseVertex baseInstance:(NSUInteger)baseInstance NS_AVAILABLE(10_11, 9_0);

/*!
 @method drawPrimitives:indirectBuffer:indirectBufferOffset:
 @brief Draw primitives without an index list using an indirect buffer see MTLDrawPrimitivesIndirectArguments.
 @param primitiveType The type of primitives that elements are assembled into.
 @param indirectBuffer A buffer object that the device will read drawPrimitives arguments from, see MTLDrawPrimitivesIndirectArguments.
 @param indirectBufferOffset Byte offset within @a indirectBuffer to start reading indexes from.  @a indirectBufferOffset must be a multiple of 4.
 */
- (void)drawPrimitives:(MTLPrimitiveType)primitiveType indirectBuffer:(id <MTLBuffer>)indirectBuffer indirectBufferOffset:(NSUInteger)indirectBufferOffset NS_AVAILABLE(10_11, 9_0);

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
- (void)drawIndexedPrimitives:(MTLPrimitiveType)primitiveType indexType:(MTLIndexType)indexType indexBuffer:(id <MTLBuffer>)indexBuffer indexBufferOffset:(NSUInteger)indexBufferOffset indirectBuffer:(id <MTLBuffer>)indirectBuffer indirectBufferOffset:(NSUInteger)indirectBufferOffset NS_AVAILABLE(10_11, 9_0);


@end
NS_ASSUME_NONNULL_END
