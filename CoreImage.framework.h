// ==========  CoreImage.framework/Headers/CIContext.h
/* CoreImage - CIContext.h

   Copyright (c) 2014 Apple, Inc.
   All rights reserved. */

#import <CoreImage/CIImage.h>
#import <CoreImage/CoreImageDefines.h>
#import <CoreVideo/CoreVideo.h>

#if TARGET_OS_IPHONE && (TARGET_OS_EMBEDDED || TARGET_OS_SIMULATOR || !0)
 #import <OpenGLES/EAGL.h>
#elif TARGET_OS_OSX
 #import <OpenGL/CGLTypes.h>
#endif 

@class CIFilter;

@protocol MTLDevice, MTLTexture, MTLCommandBuffer;

NS_ASSUME_NONNULL_BEGIN


NS_CLASS_AVAILABLE(10_4, 5_0)
@interface CIContext : NSObject
{
    void *_priv;
}

/* Keys that may be passed in the dictionary while creating contexts: */

typedef NSString * CIContextOption NS_TYPED_ENUM;

/* A CGColorSpaceRef object defining the color space that images are
 * converted to before rendering into the context. */
CORE_IMAGE_EXPORT CIContextOption const kCIContextOutputColorSpace;

/* A CGColorSpaceRef object defining the color space in which all
 * intermediate operations are performed. */
CORE_IMAGE_EXPORT CIContextOption const kCIContextWorkingColorSpace;

/* An NSNumber with a CIFormat value defining the pixel format to use for intermediate buffers.
* On iOS GPU the supported values for this key are RGBA8 and RGBAh. If not specified RGBA8 us used.
* On iOS CPU the only supported value for this key is RGBAf. If not specified RGBAf us used.
* On OSX GPU the supported values for this key are RGBA8, RGBAh and RGBAf. If not specified RGBAh us used.
* On OSX CPU the supported values for this key are RGBA8, RGBAh and RGBAf. If not specified RGBAh us used. */
CORE_IMAGE_EXPORT CIContextOption const kCIContextWorkingFormat NS_AVAILABLE(10_4,8_0);

/* A boolean NSNumber controlling the quality of affine downsample operations.
 * @YES implies that more quality is desired.
 * On iOS the default value is @NO.
 * On OSX the default value is @YES. */
CORE_IMAGE_EXPORT CIContextOption const kCIContextHighQualityDownsample NS_AVAILABLE(10_11,9_0);

/* A boolean NSNumber controlling whether output renders produce alpha-premultiplied pixels.
 * The default value is @YES. */
CORE_IMAGE_EXPORT CIContextOption const kCIContextOutputPremultiplied NS_AVAILABLE(10_4,7_0);

/* A boolean NSNumber controlling how intermediate buffers are cached.
 * If @NO, the context will empty intermediates during and after renders.
 * The default value is @YES. */
CORE_IMAGE_EXPORT CIContextOption const kCIContextCacheIntermediates NS_AVAILABLE(10_12,10_0);

/* An NSNumber with a boolean value. When @YES the context will use
 * software rendering on macOS. */
CORE_IMAGE_EXPORT CIContextOption const kCIContextUseSoftwareRenderer;

/* An NSNumber with a boolean value. When @YES the context will use 
 * low priority rendering on the GPU. */
CORE_IMAGE_EXPORT CIContextOption const kCIContextPriorityRequestLow NS_AVAILABLE(10_12, 8_0);


#pragma mark - contextWithCGLContext

/* Create a new CoreImage context object, all output will be drawn
 * into the surface attached to the OpenGL context 'cglctx'. If 'pixelFormat' is
 * non-null it should be the pixel format object used to create 'cglctx';
 * it's required to be valid for the lifetime of the CIContext.
 * The colorspace should be set to the colorspace of your target otherwise
 * CI will take the colorspace from the CGLContext if available. */
#if TARGET_OS_OSX
+ (CIContext *)contextWithCGLContext:(CGLContextObj)cglctx
						 pixelFormat:(nullable CGLPixelFormatObj)pixelFormat
						  colorSpace:(nullable CGColorSpaceRef)colorSpace
							 options:(nullable NSDictionary<CIContextOption, id> *)options
    CI_GL_DEPRECATED_MAC(10_6,10_14);
#endif

/* DEPRECATED, please use the method above or if you need this
* for backward capability, make sure that you specify the colorspace
* in the options dictionary */
#if TARGET_OS_OSX
+ (CIContext *)contextWithCGLContext:(CGLContextObj)cglctx
						 pixelFormat:(nullable CGLPixelFormatObj)pixelFormat
							 options:(nullable NSDictionary<CIContextOption, id> *)options
    CI_GL_DEPRECATED_MAC(10_4,10_6);
#endif


#pragma mark - contextWithCGContext

/* Create a context specifying a destination CGContext.
 *
 * Core Image will use an internal destination context when methods such
 * as [context render:to...] or [context createCGImage:...] are called.
 *
 * The [context drawImage:...] render methods will render to the CGContext.
 */
+ (CIContext *)contextWithCGContext:(CGContextRef)cgctx
                            options:(nullable NSDictionary<CIContextOption, id> *)options
    NS_AVAILABLE(10_4,9_0);


#pragma mark - context without specifying a destination

/* Create a context without specifying a destination CG/GL/Metal context.
 *
 * Core Image will use an internal destination context when methods such
 * as [context render:to...] or [context createCGImage:...] are called.
 *
 * The [context drawImage:...] render methods will not operate on this type
 * of context.
 */

+ (CIContext *)contextWithOptions:(nullable NSDictionary<CIContextOption, id> *)options
    NS_AVAILABLE(10_4,5_0);

+ (CIContext *)context NS_AVAILABLE(10_4,5_0);

- (instancetype)initWithOptions:(nullable NSDictionary<CIContextOption, id> *)options
NS_AVAILABLE(10_4,5_0);

- (instancetype)init NS_AVAILABLE(10_4,5_0);


#pragma mark - contextWithEAGLContext

/* Create a context specifying a destination EAGLContext.
 *
 * Core Image will use an internal destination context when methods such
 * as [context render:to...] or [context createCGImage:...] are called.
 *
 * The [context drawImage:...] render methods will render to the EAGLContext.
 */
#if TARGET_OS_IPHONE && (TARGET_OS_EMBEDDED || TARGET_OS_SIMULATOR || !0)
+ (CIContext *)contextWithEAGLContext:(EAGLContext *)eaglContext
    CI_GL_DEPRECATED_IOS(5_0,12_0);

+ (CIContext *)contextWithEAGLContext:(EAGLContext *)eaglContext
                              options:(nullable NSDictionary<CIContextOption, id> *)options
    CI_GL_DEPRECATED_IOS(5_0,12_0);
#endif


#pragma mark - contextWithMTLDevice

/* If a system has more than one MTLDevice, then you can create a CIContext
 * that uses a specific device. If a client wishes to use the default MTLDevice
 * then call [CIContext contextWithOptions:] instead. */
+ (CIContext *)contextWithMTLDevice:(id<MTLDevice>)device NS_AVAILABLE(10_11,9_0);

+ (CIContext *)contextWithMTLDevice:(id<MTLDevice>)device
                            options:(nullable NSDictionary<CIContextOption, id> *)options
    NS_AVAILABLE(10_11,9_0);


#pragma mark - properties

// The working color space of the CIContext
// The property will be null if the context was created with color management disabled.
@property (nullable, nonatomic, readonly) CGColorSpaceRef workingColorSpace NS_AVAILABLE(10_11,9_0);

// The working pixel format of the CIContext used for intermediate buffers
@property (nonatomic, readonly) CIFormat workingFormat NS_AVAILABLE(10_11,9_0);


#pragma mark - render methods

/* DEPRECATED, please use drawImage:inRect:fromRect: instead.
 * Render the subregion 'fromRect' of 'image' to point 'atPoint' in the context's destination. */
- (void)drawImage:(CIImage *)image
          atPoint:(CGPoint)atPoint
         fromRect:(CGRect)fromRect NS_DEPRECATED(10_4,10_8, 5_0,6_0);

/* Render the rectangle 'fromRect' of 'image' to the rectangle 'inRect' in the
 * context's destination. */
- (void)drawImage:(CIImage *)image
           inRect:(CGRect)inRect
         fromRect:(CGRect)fromRect;

/* Render the region 'fromRect' of image 'image' into a temporary buffer using
 * the context, then create and return a new CoreGraphics image with
 * the results. The caller is responsible for releasing the returned image.
 * The return value will be null if size is empty or too big. */
- (nullable CGImageRef)createCGImage:(CIImage *)image
                            fromRect:(CGRect)fromRect
CF_RETURNS_RETAINED;

/* Create a new CGImage from the specified subrect of the image. If
 * non-nil the new image will be created in the specified format and colorspace.
 * The CGColorSpace must be kCGColorSpaceModelRGB or kCGColorSpaceModelMonochrome
 * and must match the specified CIFormat.
 * This will return null if fromRect is empty or infinite or the format isn't supported.
 */
- (nullable CGImageRef)createCGImage:(CIImage *)image
                            fromRect:(CGRect)fromRect
                              format:(CIFormat)format
                          colorSpace:(nullable CGColorSpaceRef)colorSpace
CF_RETURNS_RETAINED;

/* Create a new CGImage from the specified subrect of the image.
 * The new CGImageRef will be created in the specified format and colorspace.
 * The return value will be null if fromRect is empty or infinite.
 * The CGColorSpace must be kCGColorSpaceModelRGB or kCGColorSpaceModelMonochrome
 * and must match the specified CIFormat.
 * This will return null if fromRect is empty or infinite or the format isn't supported.
 * If deferred is NO, then the CIImage will be rendered once when this method is called.
 * If deferred is YES, then the CIImage will be rendered whenever the CGImage is rendered.
 */
- (nullable CGImageRef)createCGImage:(CIImage *)image
                            fromRect:(CGRect)fromRect
                              format:(CIFormat)format
                          colorSpace:(nullable CGColorSpaceRef)colorSpace
                            deferred:(BOOL)deferred
CF_RETURNS_RETAINED NS_AVAILABLE(10_12,10_0);

/* Create a CoreGraphics layer object suitable for creating content for
 * subsequently rendering into this CI context. The 'info' parameter is
 * passed into CGLayerCreate () as the auxiliaryInfo dictionary.
 * This will return null if size is empty or infinite. */
- (nullable CGLayerRef)createCGLayerWithSize:(CGSize)size
                                        info:(nullable CFDictionaryRef)info
CF_RETURNS_RETAINED NS_DEPRECATED_MAC(10_4,10_11);

/* Render 'image' to the given bitmap.
 * The 'data' parameter must point to at least rowBytes*floor(bounds.size.height) bytes.
 * The 'bounds' parameter has the following behavior:
 *    The 'bounds' parameter acts to specify the region of 'image' to render.
 *    This region (regardless of its origin) is rendered at upper-left corner of 'data'.
 * Passing a 'colorSpace' value of null means:
 *   Disable output color management if app is linked against iOS SDK
 *   Disable output color management if app is linked against OSX 10.11 SDK or later
 *   Match to context's output color space if app is linked against OSX 10.10 SDK or earlier
 */
- (void)render:(CIImage *)image
	  toBitmap:(void *)data
	  rowBytes:(ptrdiff_t)rowBytes
		bounds:(CGRect)bounds
		format:(CIFormat)format
	colorSpace:(nullable CGColorSpaceRef)colorSpace;

#if !TARGET_OS_SIMULATOR
/* Render 'image' to the given IOSurface.
 * The 'bounds' parameter has the following behavior:
 *    The 'image' is rendered into 'surface' so that
 *      point (0,0) of 'image' aligns to the lower left corner of 'surface'.
 *      The 'bounds' acts like a clip rect to limit what region of 'surface' is modified.
 */
- (void)render:(CIImage *)image
   toIOSurface:(IOSurfaceRef)surface
		bounds:(CGRect)bounds
	colorSpace:(nullable CGColorSpaceRef)colorSpace NS_AVAILABLE(10_6,5_0);
#endif

/* Render 'image' into the given CVPixelBuffer. 
 * In OS X 10.11.3 and iOS 9.3 and later
 *   CI will color match to the colorspace of the buffer.
 * otherwise
 *   CI will color match to the context's output colorspace.
 */
- (void)render:(CIImage *)image 
toCVPixelBuffer:(CVPixelBufferRef)buffer NS_AVAILABLE(10_11,5_0);

/* Render 'image' to the given CVPixelBufferRef.
 * The 'bounds' parameter has the following behavior:
 *    In OS X and iOS 9 and later:  The 'image' is rendered into 'buffer' so that
 *      point (0,0) of 'image' aligns to the lower left corner of 'buffer'.
 *      The 'bounds' acts like a clip rect to limit what region of 'buffer' is modified.
 *    In iOS 8 and earlier: The 'bounds' parameter acts to specify the region of 'image' to render.
 *      This region (regardless of its origin) is rendered at upper-left corner of 'buffer'.
 * If 'colorSpace' is nil, CI will not color match to the destination.
 */
- (void)render:(CIImage *)image
toCVPixelBuffer:(CVPixelBufferRef)buffer
        bounds:(CGRect)bounds
    colorSpace:(nullable CGColorSpaceRef)colorSpace NS_AVAILABLE(10_11,5_0);

/* Render 'bounds' of 'image' to a Metal texture, optionally specifying what command buffer to use.
 * Texture type must be MTLTexture2D.
 */
- (void)render:(CIImage *)image
  toMTLTexture:(id<MTLTexture>)texture
 commandBuffer:(nullable id<MTLCommandBuffer>)commandBuffer
        bounds:(CGRect)bounds
    colorSpace:(CGColorSpaceRef)colorSpace NS_AVAILABLE(10_11,9_0);


#pragma mark -

/* Runs the context's garbage collector to reclaim any resources that
 * are no longer required (e.g. removes textures from the texture cache
 * that reference deleted images.) This method is called automatically
 * after every rendering operation. */
- (void)reclaimResources NS_AVAILABLE_MAC(10_4);

/* Frees any cached data (such as temporary images) associated with the
 * context. This also runs the garbage collector. */
- (void)clearCaches NS_AVAILABLE(10_4,10_0);

/* Returns the maximum dimension for input images that can be processed 
 * on the context. */
- (CGSize)inputImageMaximumSize NS_AVAILABLE_IOS(5_0);

/* Returns the maximum dimension for image that can be rendered 
 * on the context. */
- (CGSize)outputImageMaximumSize NS_AVAILABLE_IOS(5_0);

@end


@interface CIContext (OfflineGPUSupport)

/* Not all GPUs will be driving a display. If they are offline we can still use them
 * to do work with Core Image. This method returns the number of offline GPUs which
 * can be used for this purpose */
+(unsigned int)offlineGPUCount NS_AVAILABLE_MAC(10_10);

/* These two methods lets you create a CIContext based on an offline gpu index.
 * The first method takes only the GPU index as a parameter, the second, takes
 * an optional colorspace, options dictionary and a CGLContext which can be
 * shared with other GL resources.  The return value will be null if index is 
 * out of range (e.g. if the device has no offline GPUs).
 */
#if TARGET_OS_OSX
+ (nullable CIContext *)contextForOfflineGPUAtIndex:(unsigned int)index CI_GL_DEPRECATED_MAC(10_10,10_14);
+ (nullable CIContext *)contextForOfflineGPUAtIndex:(unsigned int)index
                                         colorSpace:(nullable CGColorSpaceRef)colorSpace
                                            options:(nullable NSDictionary<CIContextOption, id> *)options
                                      sharedContext:(nullable CGLContextObj)sharedContext CI_GL_DEPRECATED_MAC(10_10,10_14);
#endif


@end

typedef NSString * CIImageRepresentationOption NS_TYPED_ENUM; 

@interface CIContext (ImageRepresentation)

CORE_IMAGE_EXPORT CIImageRepresentationOption const kCIImageRepresentationAVDepthData NS_AVAILABLE(10_13,11_0);
CORE_IMAGE_EXPORT CIImageRepresentationOption const kCIImageRepresentationDepthImage NS_AVAILABLE(10_13,11_0);
CORE_IMAGE_EXPORT CIImageRepresentationOption const kCIImageRepresentationDisparityImage NS_AVAILABLE(10_13,11_0);

CORE_IMAGE_EXPORT CIImageRepresentationOption const kCIImageRepresentationAVPortraitEffectsMatte NS_AVAILABLE(10_14,12_0);
CORE_IMAGE_EXPORT CIImageRepresentationOption const kCIImageRepresentationPortraitEffectsMatteImage NS_AVAILABLE(10_14,12_0);

/* Render a CIImage to TIFF data. Image must have a finite non-empty extent. */
/* The CGColorSpace must be kCGColorSpaceModelRGB or kCGColorSpaceModelMonochrome */
/* and must match the specified CIFormat. */
/* No options keys are supported at this time. */
- (nullable NSData*) TIFFRepresentationOfImage:(CIImage*)image
                                        format:(CIFormat)format
                                    colorSpace:(CGColorSpaceRef)colorSpace
                                       options:(NSDictionary<CIImageRepresentationOption, id>*)options NS_AVAILABLE(10_12,10_0);

/* Render a CIImage to JPEG data. Image must have a finite non-empty extent. */
/* The CGColorSpace must be kCGColorSpaceModelRGB or kCGColorSpaceModelMonochrome. */
/* Supported options keys are kCGImageDestinationLossyCompressionQuality, */
/* kCIImageRepresentationAVDepthData, kCIImageRepresentationDepthImage, */
/* kCIImageRepresentationDisparityImage, kCIImageRepresentationAVPortraitEffectsMatte, */
/* kCIImageRepresentationPortraitEffectsMatteImage. */
- (nullable NSData*) JPEGRepresentationOfImage:(CIImage*)image
                                    colorSpace:(CGColorSpaceRef)colorSpace
                                       options:(NSDictionary<CIImageRepresentationOption, id>*)options NS_AVAILABLE(10_12,10_0);

/* Render a CIImage to HEIF data. Image must have a finite non-empty extent. */
/* The CGColorSpace must be kCGColorSpaceModelRGB or kCGColorSpaceModelMonochrome */
/* and must match the specified CIFormat. */
/* Supported options keys are kCGImageDestinationLossyCompressionQuality, */
/* kCIImageRepresentationAVDepthData, kCIImageRepresentationDepthImage, */
/* kCIImageRepresentationDisparityImage, kCIImageRepresentationAVPortraitEffectsMatte, */
/* kCIImageRepresentationPortraitEffectsMatteImage. */
- (nullable NSData*) HEIFRepresentationOfImage:(CIImage*)image
                                        format:(CIFormat)format
                                    colorSpace:(CGColorSpaceRef)colorSpace
                                       options:(NSDictionary<CIImageRepresentationOption, id>*)options NS_AVAILABLE(10_13_4,11_0);

/* Render a CIImage to PNG data. Image must have a finite non-empty extent. */
/* The CGColorSpace must be kCGColorSpaceModelRGB or kCGColorSpaceModelMonochrome */
/* and must match the specified CIFormat. */
/* No options keys are supported at this time. */
- (nullable NSData*) PNGRepresentationOfImage:(CIImage*)image
                                       format:(CIFormat)format
                                   colorSpace:(CGColorSpaceRef)colorSpace
                                      options:(NSDictionary<CIImageRepresentationOption, id>*)options NS_AVAILABLE(10_13,11_0);

/* Render a CIImage to TIFF file. Image must have a finite non-empty extent. */
/* The CGColorSpace must be kCGColorSpaceModelRGB or kCGColorSpaceModelMonochrome */
/* and must match the specified CIFormat. */
/* No options keys are supported at this time. */
- (BOOL) writeTIFFRepresentationOfImage:(CIImage*)image
                                  toURL:(NSURL*)url
                                 format:(CIFormat)format
                             colorSpace:(CGColorSpaceRef)colorSpace 
                                options:(NSDictionary<CIImageRepresentationOption, id>*)options
                                  error:(NSError **)errorPtr NS_AVAILABLE(10_12,10_0);

/* Render a CIImage to PNG file. Image must have a finite non-empty extent. */
/* The CGColorSpace must be kCGColorSpaceModelRGB or kCGColorSpaceModelMonochrome */
/* and must match the specified CIFormat. */
/* No options keys are supported at this time. */
- (BOOL) writePNGRepresentationOfImage:(CIImage*)image
                                 toURL:(NSURL*)url
                                format:(CIFormat)format
                            colorSpace:(CGColorSpaceRef)colorSpace
                               options:(NSDictionary<CIImageRepresentationOption, id>*)options
                                 error:(NSError **)errorPtr NS_AVAILABLE(10_13,11_0);

/* Render a CIImage to JPEG file. Image must have a finite non-empty extent. */
/* The CGColorSpace must be kCGColorSpaceModelRGB or kCGColorSpaceModelMonochrome. */
/* Supported options keys are kCGImageDestinationLossyCompressionQuality, */
/* kCIImageRepresentationAVDepthData, kCIImageRepresentationDepthImage, */
/* kCIImageRepresentationDisparityImage, kCIImageRepresentationAVPortraitEffectsMatte, */
/* kCIImageRepresentationPortraitEffectsMatteImage. */
- (BOOL) writeJPEGRepresentationOfImage:(CIImage*)image
                                  toURL:(NSURL*)url
                             colorSpace:(CGColorSpaceRef)colorSpace
                                options:(NSDictionary<CIImageRepresentationOption, id>*)options
                                  error:(NSError **)errorPtr NS_AVAILABLE(10_12,10_0);

/* Render a CIImage to HEIF file. Image must have a finite non-empty extent. */
/* The CGColorSpace must be kCGColorSpaceModelRGB or kCGColorSpaceModelMonochrome */
/* and must match the specified CIFormat. */
/* Supported options keys are kCGImageDestinationLossyCompressionQuality, */
/* kCIImageRepresentationAVDepthData, kCIImageRepresentationDepthImage, */
/* kCIImageRepresentationDisparityImage, kCIImageRepresentationAVPortraitEffectsMatte, */
/* kCIImageRepresentationPortraitEffectsMatteImage. */
- (BOOL) writeHEIFRepresentationOfImage:(CIImage*)image
                                  toURL:(NSURL*)url
                                 format:(CIFormat)format
                             colorSpace:(CGColorSpaceRef)colorSpace
                                options:(NSDictionary<CIImageRepresentationOption, id>*)options
                                  error:(NSError **)errorPtr NS_AVAILABLE(10_13_4,11_0);


@end

@interface CIContext (CIDepthBlurEffect)

/* Create and CIFilter instance for 'image' that can be used to apply the CIDepthBlurEffect.
 *
 * The receiver context is user to render the image in order to get the facial landmarks
 *
 * The 'options' parameter is a key value/pair reserved for future use.
 *
 */

- (nullable CIFilter *) depthBlurEffectFilterForImageURL:(NSURL *)url options:(nullable NSDictionary *)options NS_AVAILABLE(10_14,12_0);

/* This is the same as the method above expect it uses NSData to instantiate the image data
 * instead of the contents of a NSURL.
 *
 */

- (nullable CIFilter *) depthBlurEffectFilterForImageData:(NSData *)data options:(nullable NSDictionary *)options NS_AVAILABLE(10_14,12_0);


/* Create and CIFilter instance for 'image' that can be used to apply the CIDepthBlurEffect.
 *
 * The receiver context is user to render the image in order to get the facial landmarks
 *
 * The 'orientation' parameter should be CGImagePropertyOrientation enum value
 * as defined in the TIFF spec.
 *
 * The 'options' parameter is a key value/pair reserved for future use.
 *
 */

- (nullable CIFilter *) depthBlurEffectFilterForImage:(CIImage *)image
                                       disparityImage:(CIImage *)disparityImage
                                 portraitEffectsMatte:(nullable CIImage *)portraitEffectsMatte
                                          orientation:(CGImagePropertyOrientation)orientation
                                              options:(nullable NSDictionary *)options NS_AVAILABLE(10_14,12_0);

@end


NS_ASSUME_NONNULL_END
// ==========  CoreImage.framework/Headers/CIRenderDestination.h
/*
 CoreImage - CIRenderDestination.h
 
 Copyright (c) 2017 Apple, Inc.
 All rights reserved.
 */


#import <Foundation/Foundation.h>
#import <CoreImage/CoreImageDefines.h>
#import <CoreImage/CIImage.h>
#import <CoreImage/CIContext.h>
#import <CoreImage/CIKernel.h>
#import <CoreVideo/CoreVideo.h>
#if !TARGET_OS_SIMULATOR
#import <IOSurface/IOSurfaceObjC.h>
#endif
#import <Metal/MTLPixelFormat.h>

@protocol MTLTexture, MTLCommandBuffer;

NS_ASSUME_NONNULL_BEGIN


// This is a lightweight API to allow clients to specify all the
// attributes of a render that pertain to the render's destination.
// It is intended to be used for issuing renders that return to the
// caller as soon as all the work has been issued but before it completes/
//
NS_CLASS_AVAILABLE(10_13, 11_0)
@interface CIRenderDestination : NSObject
{
    void *_priv;
}

// MARK: PixelBuffer destinations

// Create a CIRenderDestination based on a CVPixelBufferRef object.
//
// The destination's 'colorspace' property will default a CGColorSpace created by,
// querying the CVPixelBufferRef attributes.
//
- (instancetype) initWithPixelBuffer:(CVPixelBufferRef)pixelBuffer;

// MARK: Surface destinations

#if !TARGET_OS_SIMULATOR
// Create a CIRenderDestination based on an IOSurface object.
//
// The destination's 'colorspace' property will default a CGColorSpace created by,
// querying the IOSurface attributes.
//
- (instancetype) initWithIOSurface:(IOSurface*)surface;
#endif

// MARK: Metal destinations

// A render to a MTLTexture-backed CIRenderDestination is only supported by MTLTexture-backed CIContexts.
// The texture must have a MTLTextureType of MTLTextureType2D
//
// An optional MTLCommandBuffer can be specified, with which to use for rendering to the MTLTexture.
//
// The destination's 'colorspace' property will default a CGColorSpace created with kCGColorSpaceSRGB,
// kCGColorSpaceExtendedSRGB, or kCGColorSpaceGenericGrayGamma2_2.
//
- (instancetype) initWithMTLTexture:(id<MTLTexture>)texture
                      commandBuffer:(nullable id<MTLCommandBuffer>)commandBuffer;

// Create a CIRenderDestination based on a Metal texture.
//
// Rendering to a MTLTexture-backed CIRenderDestination is only supported by MTLTexture-backed CIContexts.
// The provider 'block' will be called lazily when the destination is rendered to.
// The block must return a texture with a MTLTextureType of MTLTextureType2D.
// The 'width', 'height' and 'pixelFormat' argument values should be the same as the
// width, height and pixelFormat of the MTLTexture that will be returned by 'block'
//
// An optional MTLCommandBuffer can be specified, with which to use for rendering to the MTLTexture.
//
// The destination's 'colorspace' property will default a CGColorSpace created with kCGColorSpaceSRGB,
// kCGColorSpaceExtendedSRGB, or kCGColorSpaceGenericGrayGamma2_2.
//
- (instancetype) initWithWidth:(NSUInteger)width
                        height:(NSUInteger)height
                   pixelFormat:(MTLPixelFormat)pixelFormat
                 commandBuffer:(nullable id<MTLCommandBuffer>)commandBuffer
            mtlTextureProvider:(nullable id<MTLTexture> (^)(void))block;

// MARK: OpenGL destination

// Create a CIRenderDestination based on an OpenGL texture.
//
// Rendering to a GLTexture-backed CIRenderDestination is only supported by GLContext-backed CIContexts.
// The texture id must be bound to a GLContext that is shared with that of the GLContext-backed CIContext.
//
// The destination's 'colorspace' property will default a CGColorSpace created with kCGColorSpaceSRGB,
// kCGColorSpaceExtendedSRGB, or kCGColorSpaceGenericGrayGamma2_2.
//
- (instancetype) initWithGLTexture:(unsigned int)texture
		                    target:(unsigned int)target // GL_TEXTURE_2D or GL_TEXTURE_RECTANGLE_EXT
                             width:(NSUInteger)width
                            height:(NSUInteger)height;

// MARK: Bitmap data destination

// Create a CIRenderDestination based on client-managed buffer.
//
// The 'data' parameter must point to a buffer that is at least bytesPerRow * height bytes in size.
// 
// The destination's 'colorspace' property will default a CGColorSpace created with kCGColorSpaceSRGB,
// kCGColorSpaceExtendedSRGB, or kCGColorSpaceGenericGrayGamma2_2.
- (instancetype) initWithBitmapData:(void *)data
                              width:(NSUInteger)width
                             height:(NSUInteger)height
                        bytesPerRow:(NSUInteger)bytesPerRow
                             format:(CIFormat)format;


// MARK: Properties

@property (readonly) NSUInteger width;
@property (readonly) NSUInteger height;


typedef NS_ENUM(NSUInteger, CIRenderDestinationAlphaMode) {
    CIRenderDestinationAlphaNone            = 0,
    CIRenderDestinationAlphaPremultiplied   = 1,
    CIRenderDestinationAlphaUnpremultiplied = 2
};

// This property will defualt to an appropriate value given
// the object that the CIRenderDestination was initialized with.
// This property can be set to a different value if desired.
@property CIRenderDestinationAlphaMode alphaMode;

// The logical coordinate system of a CIRenderDestination is always cartesian:
//   (0,0) represents the lower-left corner
//   (0.5,0.5) represents the lower-left pixel center
//   (pixelsWide-0.5,pixelsHigh-0.5) represents the upper-right pixel center
//   (pixelsWide,pixelsHigh) represents the upper-right corner.
//
// The 'flipped' property controls how pixels this logical coordinate system
// are stored into the memory of the object backing the destination.
//
// If 'flipped' is false, then the base address of the backing stores the
// pixel centered on the logical coordinate (0.5,0.5)
//
// If 'flipped' is true, then the base address of the backing stores the
// pixel centered on the logical coordinate (pixelsWide-0.5,0.5)
//
@property (getter=isFlipped) BOOL flipped;

// Instructs the render to add pseudo-random luma noise given the depth of the destination.
// The magnitude of the noise is approximatly ±pow(2,-(bitPerComponent+1))
@property (getter=isDithered) BOOL dithered;

// If true, the render will clamp color channels
// to 0..alpha if 'alphaMode' is premultiplied otherwise 0..1
// This property is initialized to false if the destination's format supports extended range
@property (getter=isClamped) BOOL clamped;

// This property will defualt to an appropriate value given
// the object that the CIRenderDestination was initialized with.
// This property can be  set to a different colorSpace if desired.
// This property can be set to nil to disable color matching
// from the working space to the destination.
@property (nullable, nonatomic) CGColorSpaceRef colorSpace;

// Allow client to specify a CIBlendKernel (e.g. CIBlendKernel.sourceOver)
// to be used on the destination.
@property (nullable, nonatomic, retain) CIBlendKernel* blendKernel;

// If true, then the blendKernel is applied in the destination's colorSpace.
// If false, then the blendKernel is applied in the CIContext's working colorspace.
// This is false by default.
@property BOOL blendsInDestinationColorSpace;

@end


// An Xcode quicklook of this object will show a graph visualization of the render
// with detailed timing information.
NS_CLASS_AVAILABLE(10_13, 11_0)
@interface CIRenderInfo : NSObject
{
    void *_priv;
}

// This property will return how much time a render spent executing kernels.
@property (readonly) NSTimeInterval kernelExecutionTime;

// This property will return how many passes the render requires.
// If passCount is 1 than the render can be fully concatinated and no
// intermediate buffers will be required.
@property (readonly) NSInteger passCount;

// This property will return how many pixels a render produced executing kernels.
@property (readonly) NSInteger pixelsProcessed;

@end



// An Xcode quicklook of this object will show a graph visualization of the render
NS_CLASS_AVAILABLE(10_13, 11_0)
@interface CIRenderTask : NSObject
{
    void *_priv;
}

- (nullable CIRenderInfo*) waitUntilCompletedAndReturnError:(NSError**)error;

@end


@interface CIContext (CIRenderDestination)

// Renders a portion of image to a point of destination
// It renders as if 'image' is cropped to 'fromRect'
// and the origin of the result is placed at 'atPoint'
//
// If image.extent and fromRect are infinite, then it renders
// so that point (0,0) of image is placed at 'atPoint'
//
// MTLTexture-backed CIRenderDestinations are only supported by MTLTexture-backed CIContexts.
// GLTexture-backed CIRenderDestinations are only supported by GLContext-backed CIContexts.
//
// This call will return as soon as all the work for the render is enqueued on the
// context's device.
//
// In many situations, after issuing a render, the client can use the destination
// or its backing object without waiting for the enqueued work to complete.
// For example, after rendering a surface CIRenderDestination, the surface can be passed
// on for further processing by the GPU.
//
// In other situations, the client may need to wait for the render to be complete.
// For example, after rendering a surface CIRenderDestination, the surface can be accessed
// by CPU code by calling IOSurfaceGetBytePointer only after the render is completed.
//
// In this case the client can use the returned CIRenderTask like this:
//   CIRenderTask* task = [context render:...];
//   [task waitUntilCompletedAndReturnError:&error];
//
- (nullable CIRenderTask*) startTaskToRender:(CIImage*)image
                                    fromRect:(CGRect)fromRect
                               toDestination:(CIRenderDestination*)destination
                                     atPoint:(CGPoint)atPoint
                                       error:(NSError**)error NS_AVAILABLE(10_13, 11_0);

// Renders an image to a destination so that point (0,0) of image.
// is placed at point (0,0) of the destination.
//
- (nullable CIRenderTask*) startTaskToRender:(CIImage*)image
                               toDestination:(CIRenderDestination*)destination
                                       error:(NSError**)error NS_AVAILABLE(10_13, 11_0);


// This is an optional call which can be used to "warm up" a CIContext so that
// a subsequent call to render with the same arguments can be more efficient.
// By making this call, Core Image will ensure that
//  - any needed kernels will be compiled
//  - any intermedate buffers are allocated and marked volatile
//
- (BOOL) prepareRender:(CIImage*)image
              fromRect:(CGRect)fromRect
         toDestination:(CIRenderDestination*)destination
               atPoint:(CGPoint)atPoint
                 error:(NSError**)error NS_AVAILABLE(10_13, 11_0);

// Fill the entire destination with black (0,0,0,1) if its alphaMode is None
// or clear (0,0,0,0) if its alphaMode is Premultiplied or Unpremultiplied.
//
- (nullable CIRenderTask*) startTaskToClear:(CIRenderDestination*)destination
                                      error:(NSError**)error NS_AVAILABLE(10_13, 11_0);

@end

NS_ASSUME_NONNULL_END
// ==========  CoreImage.framework/Headers/CIFeature.h
/* CoreImage - CIFeature.h

   Copyright (c) 2011 Apple, Inc.
   All rights reserved. */

#import <CoreImage/CoreImageDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/** Generic feature found by a CIDetector. */
NS_CLASS_AVAILABLE(10_7, 5_0)
@interface CIFeature : NSObject {}

/** The type of the feature. */
@property (readonly, retain) NSString *type;
/** The bounds of the feature in the image it was detected in. */
@property (readonly, assign) CGRect bounds;

@end

/** Specifies the type of a feature that is a face. */
CORE_IMAGE_EXPORT NSString* const CIFeatureTypeFace;
/** Specifies the type of a feature that is a rectangle. */
CORE_IMAGE_EXPORT NSString* const CIFeatureTypeRectangle;
/** Specifies the type of a feature that is a QR code. */
CORE_IMAGE_EXPORT NSString* const CIFeatureTypeQRCode;
/** Specifies the type of a feature that is a text. */
CORE_IMAGE_EXPORT NSString* const CIFeatureTypeText;


/** A face feature found by a CIDetector.
 All positions are relative to the original image. */
NS_CLASS_AVAILABLE(10_7, 5_0)
@interface CIFaceFeature : CIFeature
{
    CGRect bounds;
    BOOL hasLeftEyePosition;
    CGPoint leftEyePosition;
    BOOL hasRightEyePosition;
    CGPoint rightEyePosition;
    BOOL hasMouthPosition;
    CGPoint mouthPosition;
    
    
    BOOL hasTrackingID;
    int trackingID;
    BOOL hasTrackingFrameCount;
    int trackingFrameCount;
    
    BOOL hasFaceAngle;
    float faceAngle;
    
    BOOL hasSmile;
    BOOL leftEyeClosed;
    BOOL rightEyeClosed;
}

/** coordinates of various cardinal points within a face.
 
 Note that the left eye is the eye on the left side of the face
 from the observer's perspective. It is not the left eye from
 the subject's perspective. */

@property (readonly, assign) CGRect bounds;
@property (readonly, assign) BOOL hasLeftEyePosition;
@property (readonly, assign) CGPoint leftEyePosition;
@property (readonly, assign) BOOL hasRightEyePosition;
@property (readonly, assign) CGPoint rightEyePosition;
@property (readonly, assign) BOOL hasMouthPosition;
@property (readonly, assign) CGPoint mouthPosition;

@property (readonly, assign) BOOL hasTrackingID;
@property (readonly, assign) int trackingID;
@property (readonly, assign) BOOL hasTrackingFrameCount;
@property (readonly, assign) int trackingFrameCount;

@property (readonly, assign) BOOL hasFaceAngle;
@property (readonly, assign) float faceAngle;

@property (readonly, assign) BOOL hasSmile;
@property (readonly, assign) BOOL leftEyeClosed;
@property (readonly, assign) BOOL rightEyeClosed;

@end

/** A rectangle feature found by a CIDetector
 All positions are relative to the original image. */

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CIRectangleFeature : CIFeature
{
    CGRect bounds;
    CGPoint topLeft;
    CGPoint topRight;
    CGPoint bottomLeft;
    CGPoint bottomRight;
}

@property (readonly) CGRect bounds;
@property (readonly) CGPoint topLeft;
@property (readonly) CGPoint topRight;
@property (readonly) CGPoint bottomLeft;
@property (readonly) CGPoint bottomRight;

@end

/** A QR code feature found by a CIDetector
 All positions are relative to the original image. */

@class CIQRCodeDescriptor;

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CIQRCodeFeature : CIFeature <NSSecureCoding, NSCopying>
{
    CGRect bounds;
    CGPoint topLeft;
    CGPoint topRight;
    CGPoint bottomLeft;
    CGPoint bottomRight;
    CIQRCodeDescriptor *symbolDescriptor;
}

@property (readonly) CGRect bounds;
@property (readonly) CGPoint topLeft;
@property (readonly) CGPoint topRight;
@property (readonly) CGPoint bottomLeft;
@property (readonly) CGPoint bottomRight;

@property (nullable, readonly) NSString* messageString;

@property (nullable, readonly) CIQRCodeDescriptor *symbolDescriptor NS_AVAILABLE(10_13, 11_0);

@end

/** A text feature found by a CIDetector
 All positions are relative to the original image. */

#if __OBJC2__
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CITextFeature : CIFeature
{
}

@property (readonly) CGRect bounds;
@property (readonly) CGPoint topLeft;
@property (readonly) CGPoint topRight;
@property (readonly) CGPoint bottomLeft;
@property (readonly) CGPoint bottomRight;
@property (nullable, readonly) NSArray *subFeatures;


@end
#endif // __OBJC2__

NS_ASSUME_NONNULL_END
// ==========  CoreImage.framework/Headers/CIFilter.h
/*
   CoreImage - CIFilter.h

   Copyright (c) 2015 Apple, Inc.
   All rights reserved.
*/


#import <Foundation/Foundation.h>
#import <CoreImage/CoreImageDefines.h>
#import <CoreImage/CIFilterConstructor.h>

NS_ASSUME_NONNULL_BEGIN

/* Filter attributes keys */

/** Name of the filter */
CORE_IMAGE_EXPORT NSString * const kCIAttributeFilterName;

/** Name of the filter intended for UI display (eg. localized) */
CORE_IMAGE_EXPORT NSString * const kCIAttributeFilterDisplayName;

/** Description of the filter intended for UI display (eg. localized) */
CORE_IMAGE_EXPORT NSString * const kCIAttributeDescription NS_AVAILABLE(10_5, 9_0);

/** The version of OS X and iOS a filter was first available in. */
CORE_IMAGE_EXPORT NSString * const kCIAttributeFilterAvailable_Mac NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT NSString * const kCIAttributeFilterAvailable_iOS NS_AVAILABLE(10_11, 9_0);

/** URL for the reference documentation of the filter. See localizedReferenceDocumentationForFilterName. */
CORE_IMAGE_EXPORT NSString * const kCIAttributeReferenceDocumentation NS_AVAILABLE(10_5, 9_0);

/** Array of filter category names (see below) */
CORE_IMAGE_EXPORT NSString * const kCIAttributeFilterCategories;

/** Class name of the filter. */
CORE_IMAGE_EXPORT NSString * const kCIAttributeClass;

/** The type of the attribute e.g. scalar, time, distance, etc. */
CORE_IMAGE_EXPORT NSString * const kCIAttributeType;

/** Minimum value for the attribute. */
CORE_IMAGE_EXPORT NSString * const kCIAttributeMin;

/** Maximum value for the attribute. */
CORE_IMAGE_EXPORT NSString * const kCIAttributeMax;

/** Minimum value for the slider. */
CORE_IMAGE_EXPORT NSString * const kCIAttributeSliderMin;

/** Maximum value for the slider. */
CORE_IMAGE_EXPORT NSString * const kCIAttributeSliderMax;

/** Default value for the slider. */
CORE_IMAGE_EXPORT NSString * const kCIAttributeDefault;

/** The identity value is the value at which the filter has no effect. */
CORE_IMAGE_EXPORT NSString * const kCIAttributeIdentity;

/** The non-localized name of the attribute. */
CORE_IMAGE_EXPORT NSString * const kCIAttributeName;

/** The localized name of the attribute to be used for display to the user. */
CORE_IMAGE_EXPORT NSString * const kCIAttributeDisplayName;


/** Key to request the desired set of controls in a filter UIView. The defined values for this key are:
    CIUISetBasic, CIUISetIntermediate, CIUISetAdvanced and CIUISetDevelopment. */
CORE_IMAGE_EXPORT NSString * const kCIUIParameterSet NS_AVAILABLE(10_5, 9_0);

/** Constant for requesting controls that are appropiate in an basic user scenario, meaning the bare minimum of settings to control the filter. */
CORE_IMAGE_EXPORT NSString * const kCIUISetBasic NS_AVAILABLE(10_5, 9_0);

/** Constant for requesting controls that are appropiate in an intermediate user scenario. */
CORE_IMAGE_EXPORT NSString * const kCIUISetIntermediate NS_AVAILABLE(10_5, 9_0);

/** Constant for requesting controls that are appropiate in an advanced user scenario. */
CORE_IMAGE_EXPORT NSString * const kCIUISetAdvanced NS_AVAILABLE(10_5, 9_0);

/** Constant for requesting controls that should only be visible for development purposes. */
CORE_IMAGE_EXPORT NSString * const kCIUISetDevelopment NS_AVAILABLE(10_5, 9_0);


/* Types for numbers */
CORE_IMAGE_EXPORT NSString * const kCIAttributeTypeTime;
CORE_IMAGE_EXPORT NSString * const kCIAttributeTypeScalar;
CORE_IMAGE_EXPORT NSString * const kCIAttributeTypeDistance;
CORE_IMAGE_EXPORT NSString * const kCIAttributeTypeAngle;
CORE_IMAGE_EXPORT NSString * const kCIAttributeTypeBoolean;

/** Indicates that the key uses integer values. */
CORE_IMAGE_EXPORT NSString * const kCIAttributeTypeInteger NS_AVAILABLE(10_5, 5_0);

/** Indicates that the key uses non negative integer values. */
CORE_IMAGE_EXPORT NSString * const kCIAttributeTypeCount NS_AVAILABLE(10_5, 5_0);

/* Types for 2-element vectors */
CORE_IMAGE_EXPORT NSString * const kCIAttributeTypePosition;
CORE_IMAGE_EXPORT NSString * const kCIAttributeTypeOffset;

/* Types for 3-element vectors */
CORE_IMAGE_EXPORT NSString * const kCIAttributeTypePosition3;

/* Types for 4-element vectors */
CORE_IMAGE_EXPORT NSString * const kCIAttributeTypeRectangle;

/* Types for colors */
CORE_IMAGE_EXPORT NSString * const kCIAttributeTypeOpaqueColor NS_AVAILABLE(10_4, 9_0);
CORE_IMAGE_EXPORT NSString * const kCIAttributeTypeColor NS_AVAILABLE(10_11, 5_0);

/* Types for images */
CORE_IMAGE_EXPORT NSString * const kCIAttributeTypeGradient NS_AVAILABLE(10_4, 9_0);
CORE_IMAGE_EXPORT NSString * const kCIAttributeTypeImage NS_AVAILABLE(10_11, 5_0);

/* Types for NSValue of CGAffineTransform */
CORE_IMAGE_EXPORT NSString * const kCIAttributeTypeTransform NS_AVAILABLE(10_11, 5_0);


/* Categories */
CORE_IMAGE_EXPORT NSString * const kCICategoryDistortionEffect;
CORE_IMAGE_EXPORT NSString * const kCICategoryGeometryAdjustment;
CORE_IMAGE_EXPORT NSString * const kCICategoryCompositeOperation;
CORE_IMAGE_EXPORT NSString * const kCICategoryHalftoneEffect;
CORE_IMAGE_EXPORT NSString * const kCICategoryColorAdjustment;
CORE_IMAGE_EXPORT NSString * const kCICategoryColorEffect;
CORE_IMAGE_EXPORT NSString * const kCICategoryTransition;
CORE_IMAGE_EXPORT NSString * const kCICategoryTileEffect;
CORE_IMAGE_EXPORT NSString * const kCICategoryGenerator;
CORE_IMAGE_EXPORT NSString * const kCICategoryReduction NS_AVAILABLE(10_5, 5_0);
CORE_IMAGE_EXPORT NSString * const kCICategoryGradient;
CORE_IMAGE_EXPORT NSString * const kCICategoryStylize;
CORE_IMAGE_EXPORT NSString * const kCICategorySharpen;
CORE_IMAGE_EXPORT NSString * const kCICategoryBlur;
CORE_IMAGE_EXPORT NSString * const kCICategoryVideo;
CORE_IMAGE_EXPORT NSString * const kCICategoryStillImage;
CORE_IMAGE_EXPORT NSString * const kCICategoryInterlaced;
CORE_IMAGE_EXPORT NSString * const kCICategoryNonSquarePixels;
CORE_IMAGE_EXPORT NSString * const kCICategoryHighDynamicRange;
CORE_IMAGE_EXPORT NSString * const kCICategoryBuiltIn;
CORE_IMAGE_EXPORT NSString * const kCICategoryFilterGenerator NS_AVAILABLE(10_5, 9_0);


/* Options keys for [CIFilter apply:arguments:options:] and [CIFilter apply:...] methods. */

CORE_IMAGE_EXPORT NSString * const kCIApplyOptionExtent NS_AVAILABLE_MAC(10_4);
CORE_IMAGE_EXPORT NSString * const kCIApplyOptionDefinition NS_AVAILABLE_MAC(10_4);
CORE_IMAGE_EXPORT NSString * const kCIApplyOptionUserInfo NS_AVAILABLE_MAC(10_4);

/* If used, the value of the kCIApplyOptionColorSpace key be must be an RGB CGColorSpaceRef.
 * Using this option specifies that the output of the kernel is in this color space.
 * If not specified, the output of the kernel is in the working color space of the rendering CIContext. */
CORE_IMAGE_EXPORT NSString * const kCIApplyOptionColorSpace NS_AVAILABLE_MAC(10_4);


/* common filter parameter keys */

CORE_IMAGE_EXPORT NSString * const kCIOutputImageKey NS_AVAILABLE(10_5, 5_0);
CORE_IMAGE_EXPORT NSString * const kCIInputBackgroundImageKey NS_AVAILABLE(10_5, 5_0);
CORE_IMAGE_EXPORT NSString * const kCIInputImageKey NS_AVAILABLE(10_5, 5_0);
CORE_IMAGE_EXPORT NSString * const kCIInputDepthImageKey NS_AVAILABLE(10_13, 11_0);
CORE_IMAGE_EXPORT NSString * const kCIInputDisparityImageKey NS_AVAILABLE(10_13, 11_0);
CORE_IMAGE_EXPORT NSString * const kCIInputAmountKey NS_AVAILABLE(10_14, 12_0);
CORE_IMAGE_EXPORT NSString * const kCIInputTimeKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputTransformKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputScaleKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputAspectRatioKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputCenterKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputRadiusKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputAngleKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputRefractionKey NS_AVAILABLE(10_5, 9_0);
CORE_IMAGE_EXPORT NSString * const kCIInputWidthKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputSharpnessKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputIntensityKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputEVKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputSaturationKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputColorKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputBrightnessKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputContrastKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputBiasKey NS_AVAILABLE(10_5, 9_0);
CORE_IMAGE_EXPORT NSString * const kCIInputWeightsKey NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT NSString * const kCIInputGradientImageKey NS_AVAILABLE(10_5, 9_0);
CORE_IMAGE_EXPORT NSString * const kCIInputMaskImageKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputMatteImageKey NS_AVAILABLE(10_14, 12_0);
CORE_IMAGE_EXPORT NSString * const kCIInputShadingImageKey NS_AVAILABLE(10_5, 9_0);
CORE_IMAGE_EXPORT NSString * const kCIInputTargetImageKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputExtentKey NS_AVAILABLE(10_5, 7_0);
CORE_IMAGE_EXPORT NSString * const kCIInputVersionKey NS_AVAILABLE(10_11, 6_0);


@class CIKernel, CIImage;
@protocol CIFilterConstructor;

/** CIFilter are filter objects for Core Image that encapsulate the filter with its attributes

 The CIFilter class produces a CIImage object as output. Typically, a filter takes one or more images as input. Some filters, however, generate an image based on other types of input parameters. The parameters of a CIFilter object are set and retrieved through the use of key-value pairs. You use the CIFilter object in conjunction with the CIImage, CIContext, CIVector, CIImageAccumulator, and CIColor objects to take advantage of the built-in Core Image filters when processing images. CIFilter objects are also used along with CIKernel, CISampler, and CIFilterShape objects to create custom filters. */

NS_CLASS_AVAILABLE(10_4, 5_0)
@interface CIFilter : NSObject <NSSecureCoding, NSCopying>
{
    void *_priv[8];
}

@property (readonly, nonatomic, nullable) CIImage *outputImage NS_AVAILABLE(10_10, 5_0);

/* The name of the filter. On OSX and iOS 10, this property is read-write.
 * This can be useful when using CIFilters with CoreAnimation or SceneKit.
 * For example, to set an attribute of a filter attached to a layer,
 * a unique path such as "filters.myExposureFilter.inputEV" could be used.
 * CALayer animations may also access filter attributes via key-paths. */
@property (nonatomic, copy) NSString *name;
- (NSString *)name NS_AVAILABLE(10_5,5_0);
- (void)setName:(NSString *)aString NS_AVAILABLE(10_5,10_0);

/* The 'enabled' property is used only by CoreAnimation and is animatable.
 * In Core Animation, a CIFilter only applied to its input when this
 * property is set to true. */
@property (getter=isEnabled) BOOL enabled NS_AVAILABLE_MAC(10_5);


/** Returns an array containing the names of all inputs in the filter. */
@property (nonatomic, readonly) NSArray<NSString *> *inputKeys;

/** Returns an array containing the names of all outputs in the filter. */
@property (nonatomic, readonly) NSArray<NSString *> *outputKeys;

/** Sets all inputs to their default values (where default values are defined, other inputs are left as-is). */
- (void)setDefaults;

/** Returns a dictionary containing key/value pairs describing the filter. (see description of keys below) */
@property (nonatomic, readonly) NSDictionary<NSString *,id> *attributes;


/** Used by CIFilter subclasses to apply the array of argument values 'args' to the kernel function 'k'. The supplied arguments must be type-compatible with the function signature of the kernel.

 The key-value pairs defined by 'dict' (if non-nil) are used to control exactly how the kernel is evaluated. Valid keys include:
 kCIApplyOptionExtent: the size of the produced image. Value is a four element NSArray [X Y WIDTH HEIGHT].
 kCIApplyOptionDefinition: the Domain of Definition of the produced image. Value is either a CIFilterShape object, or a four element NSArray defining a rectangle.
 @param  k         CIKernel of the filter
 @param  args      Array of arguments that are applied to the kernel
 @param  dict      Array of additional options
*/
- (nullable CIImage *)apply:(CIKernel *)k
				  arguments:(nullable NSArray *)args
			        options:(nullable NSDictionary<NSString *,id> *)dict NS_AVAILABLE_MAC(10_4);

/** Similar to above except that all argument values and option key-value are specified inline. The list of key-value pairs must be terminated by the 'nil' object. */
- (nullable CIImage *)apply:(CIKernel *)k, ... NS_REQUIRES_NIL_TERMINATION NS_AVAILABLE_MAC(10_4) NS_SWIFT_UNAVAILABLE("");

@end


/** Methods to register a filter and get access to the list of registered filters
 Use these methods to create filters and find filters. */
@interface CIFilter (CIFilterRegistry)

/** Creates a new filter of type 'name'.
 On OSX, all input values will be undefined.
 On iOS, all input values will be set to default values. */
+ (nullable CIFilter *) filterWithName:(NSString *) name;

/** Creates a new filter of type 'name'.
 The filter's input parameters are set from the list of key-value pairs which must be nil-terminated.
 On OSX, any of the filter input parameters not specified in the list will be undefined.
 On iOS, any of the filter input parameters not specified in the list will be set to default values. */
+ (nullable CIFilter *)filterWithName:(NSString *)name
                        keysAndValues:key0, ... NS_REQUIRES_NIL_TERMINATION NS_SWIFT_UNAVAILABLE("");

/** Creates a new filter of type 'name'.
 The filter's input parameters are set from the dictionary of key-value pairs.
 On OSX, any of the filter input parameters not specified in the dictionary will be undefined.
 On iOS, any of the filter input parameters not specified in the dictionary will be set to default values. */
+ (nullable CIFilter *)filterWithName:(NSString *)name
                  withInputParameters:(nullable NSDictionary<NSString *,id> *)params NS_AVAILABLE(10_10, 8_0);

/** Returns an array containing all published filter names in a category. */
+ (NSArray<NSString *> *)filterNamesInCategory:(nullable NSString *)category;

/** Returns an array containing all published filter names that belong to all listed categories. */
+ (NSArray<NSString *> *)filterNamesInCategories:(nullable NSArray<NSString *> *)categories;


/** Publishes a new filter called 'name'.

 The constructor object 'anObject' should implement the filterWithName: method.
 That method will be invoked with the name of the filter to create.
 The class attributes must have a kCIAttributeFilterCategories key associated with a set of categories.
 @param   attributes    Dictionary of the registration attributes of the filter. See below for attribute keys.
*/
+ (void)registerFilterName:(NSString *)name
               constructor:(id<CIFilterConstructor>)anObject
           classAttributes:(NSDictionary<NSString *,id> *)attributes NS_AVAILABLE(10_4, 9_0);

/** Returns the localized name of a filter for display in the UI. */
+ (nullable NSString *)localizedNameForFilterName:(NSString *)filterName NS_AVAILABLE(10_4, 9_0);

/** Returns the localized name of a category for display in the UI. */
+ (NSString *)localizedNameForCategory:(NSString *)category NS_AVAILABLE(10_4, 9_0);

/** Returns the localized description of a filter for display in the UI. */
+ (nullable NSString *)localizedDescriptionForFilterName:(NSString *)filterName NS_AVAILABLE(10_4, 9_0);

/** Returns the URL to the localized reference documentation describing the filter.

 The URL can be a local file or a remote document on a webserver. It is possible, that this method returns nil (like filters that predate this feature). A client of this API has to handle this case gracefully. */
+ (nullable NSURL *)localizedReferenceDocumentationForFilterName:(NSString *)filterName NS_AVAILABLE(10_4, 9_0);

@end


/** Methods to serialize arrays of filters to xmp. */
@interface CIFilter (CIFilterXMPSerialization)

/* Given an array of filters, serialize the filters' parameters
   into XMP form that is suitable for embedding in to an image.
   At this time the only filters classes that are serialized
   are, CIAffineTransform, CICrop, and the filters returned by
   [CIImage autoAdjustmentFilters].
   The parameters of other filter classes will not be serialized.
   The return value will be null if none of the filters can be serialized.
 */
+ (nullable NSData*)serializedXMPFromFilters:(NSArray<CIFilter *> *)filters
                            inputImageExtent:(CGRect)extent
    NS_AVAILABLE(10_9, 6_0);

/* Return an array of CIFilters de-serialized from XMP data.
 */
+ (NSArray<CIFilter *> *)filterArrayFromSerializedXMP:(NSData *)xmpData
                                     inputImageExtent:(CGRect)extent
                                                error:(NSError **)outError
    NS_AVAILABLE(10_9, 6_0);

@end

NS_ASSUME_NONNULL_END
// ==========  CoreImage.framework/Headers/CIImageAccumulator.h
/* CoreImage - CIImageAccumulator.h

   Copyright (c) 2004 Apple, Inc.
   All rights reserved. */

#import <CoreImage/CoreImageDefines.h>
#import <CoreImage/CIImage.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_4, 9_0)
@interface CIImageAccumulator : NSObject
{
    void *_state;
}

/* Create a new accumulator object. 
   For pixel format options see CIImage.h.
   The specified color space is used to render the image. 
   If no color space is specified, no color matching is done. 
   The return values will be null if the format is unsupported or the extent is too big.
*/
+ (nullable instancetype)imageAccumulatorWithExtent:(CGRect)extent
                                             format:(CIFormat)format;

+ (nullable instancetype)imageAccumulatorWithExtent:(CGRect)extent
                                             format:(CIFormat)format
                                         colorSpace:(CGColorSpaceRef)colorSpace
NS_AVAILABLE(10_7, 9_0);

- (nullable instancetype)initWithExtent:(CGRect)extent
                                 format:(CIFormat)format;

- (nullable instancetype)initWithExtent:(CGRect)extent
                                 format:(CIFormat)format
                             colorSpace:(CGColorSpaceRef)colorSpace
NS_AVAILABLE(10_7, 9_0);

/* Return the extent of the accumulator. */
@property (readonly) CGRect extent;

/* Return the pixel format of the accumulator. */
@property (readonly) CIFormat format;

/* Return an image representing the current contents of the accumulator.
 * Rendering the image after subsequently calling setImage: has
 * undefined behavior. */
- (CIImage *)image;

/* Set the image 'im' as the current contents of the accumulator. */
- (void)setImage:(CIImage *)image;

/* Set the image 'im' as the accumulator's contents. The caller guarantees
 * that the new contents only differ from the old within the specified
 * region. */
- (void)setImage:(CIImage *)image dirtyRect:(CGRect)dirtyRect;

/* Reset the accumulator, discarding any pending updates and current content. */
- (void)clear;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreImage.framework/Headers/CIVector.h
/* 
   CoreImage - CIVector.h

   Copyright (c) 2015 Apple, Inc.
   All rights reserved.
*/

#import <CoreImage/CoreImageDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_4, 5_0)
@interface CIVector : NSObject <NSCopying, NSSecureCoding>
{
    size_t _count;
    
    union {
        CGFloat vec[4];
        CGFloat *ptr;
    }
    _u;
}

/* Create a new vector object. */

+ (instancetype)vectorWithValues:(const CGFloat *)values count:(size_t)count;

+ (instancetype)vectorWithX:(CGFloat)x;
+ (instancetype)vectorWithX:(CGFloat)x Y:(CGFloat)y;
+ (instancetype)vectorWithX:(CGFloat)x Y:(CGFloat)y Z:(CGFloat)z;
+ (instancetype)vectorWithX:(CGFloat)x Y:(CGFloat)y Z:(CGFloat)z W:(CGFloat)w;

/* the CGPoint x and y values are stored in the first X and Y values of the CIVector. */
+ (instancetype)vectorWithCGPoint:(CGPoint)p NS_AVAILABLE(10_9, 5_0);

/* the CGRect x, y, width, height values are stored in the first X, Y, Z, W values of the CIVector. */
+ (instancetype)vectorWithCGRect:(CGRect)r NS_AVAILABLE(10_9, 5_0);

/* the CGAffineTransform's six values are stored in the first six values of the CIVector. */
+ (instancetype)vectorWithCGAffineTransform:(CGAffineTransform)t NS_AVAILABLE(10_9, 5_0);

+ (instancetype)vectorWithString:(NSString *)representation;

/* Initializers. */

- (instancetype)initWithValues:(const CGFloat *)values count:(size_t)count NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithX:(CGFloat)x;
- (instancetype)initWithX:(CGFloat)x Y:(CGFloat)y;
- (instancetype)initWithX:(CGFloat)x Y:(CGFloat)y Z:(CGFloat)z;
- (instancetype)initWithX:(CGFloat)x Y:(CGFloat)y Z:(CGFloat)z W:(CGFloat)w;
- (instancetype)initWithCGPoint:(CGPoint)p NS_AVAILABLE(10_9, 5_0);
- (instancetype)initWithCGRect:(CGRect)r NS_AVAILABLE(10_9, 5_0);
- (instancetype)initWithCGAffineTransform:(CGAffineTransform)r NS_AVAILABLE(10_9, 5_0);

- (instancetype)initWithString:(NSString *)representation;

/* Return the value from the vector at position 'index' (zero-based).
 * Any 'index' value is valid, if the component would otherwise be
 * undefined, zero is returned. */
- (CGFloat)valueAtIndex:(size_t)index;

/* Return the number of values stored in the vector. */
@property (readonly) size_t count;

/* Properties. */

@property (readonly) CGFloat X;
@property (readonly) CGFloat Y;
@property (readonly) CGFloat Z;
@property (readonly) CGFloat W;
@property (readonly) CGPoint CGPointValue NS_AVAILABLE(10_9, 5_0);
@property (readonly) CGRect CGRectValue NS_AVAILABLE(10_9, 5_0);
@property (readonly) CGAffineTransform CGAffineTransformValue NS_AVAILABLE(10_9, 5_0);

/* Returns a formatted string with the components of the vector.
 * The string is suitable for passing to [CIVector vectorWithString:].
 * This property is not KVO-safe because it returns a new NSString each time.
 * The value of the NSString will be the same each time it is called. */
@property (readonly) NSString *stringRepresentation;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreImage.framework/Headers/CIFilterShape.h
/* 
   CoreImage - CIFilterShape.h

   Copyright (c) 2015 Apple, Inc.
   All rights reserved. 
*/

#import <Foundation/Foundation.h>
#import <CoreImage/CoreImageDefines.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_4, 9_0)
@interface CIFilterShape : NSObject <NSCopying>
{
    @public
    uint32_t _pad;
    void *_priv;
}

/* Create a shape representing the smallest integral rect containing 'r'. */
+ (instancetype)shapeWithRect:(CGRect)r;


/* Initializer. */
- (instancetype)initWithRect:(CGRect)r;


/* Create a shape from the result of transforming the shape by 'm'. If
 * 'flag' is false the new shape will contain all pixels in the
 * transformed shape (and possibly some outside the transformed shape).
 * If 'flag' is false the new shape will contain a subset of the pixels
 * in the transformed shape (but none of those outside the transformed
 * shape). */
- (CIFilterShape *)transformBy:(CGAffineTransform)m interior:(BOOL)flag;

/* Create a shape representing the shape inset by 'delta'. */
- (CIFilterShape *)insetByX:(int)dx Y:(int)dy;

/* Create a shape representing the union of the shape and 's2'. */
- (CIFilterShape *)unionWith:(CIFilterShape *)s2;

/* Create a shape representing the union of the shape and the smallest
 * integral rect containing 'r'. */
- (CIFilterShape *)unionWithRect:(CGRect)r;

/* Create a shape representing the intersection of the shape and 's2'. */
- (CIFilterShape *)intersectWith:(CIFilterShape *)s2;

/* Create a shape representing the intersection of the shape and the smallest
 * integral rect containing 'r'. */
- (CIFilterShape *)intersectWithRect:(CGRect)r;


/* Returns an integral rect that bounds the shape. */
@property (readonly) CGRect extent;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreImage.framework/Headers/CoreImageDefines.h
/* CoreImage - CoreImageDefines.h
 
 Copyright (c) 2014 Apple, Inc.
 All rights reserved. */

#ifndef COREIMAGEDEFINES_H
#define COREIMAGEDEFINES_H


#include <TargetConditionals.h>

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#if TARGET_OS_IPHONE
#include <CoreGraphics/CoreGraphics.h>
#else
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifdef __cplusplus
 #define CI_EXTERN_C_BEGIN  extern "C" {
 #define CI_EXTERN_C_END  }
#else
 #define CI_EXTERN_C_BEGIN
 #define CI_EXTERN_C_END
#endif

#ifdef __cplusplus
# define CORE_IMAGE_EXPORT extern "C" __attribute__((visibility("default")))
#else
# define CORE_IMAGE_EXPORT extern __attribute__((visibility("default")))
#endif

#define CORE_IMAGE_CLASS_EXPORT __attribute__((visibility("default")))


#ifdef CI_SILENCE_GL_DEPRECATION
  #define CI_GL_DEPRECATED_IOS(from, to)  NS_AVAILABLE_IOS(from)
  #define CI_GL_DEPRECATED_MAC(from, to)  NS_AVAILABLE_MAC(from)
  #define CI_GL_DEPRECATED(fromM,toM, fromI,toI)  NS_AVAILABLE(fromM,fromI)
  #define CIKL_DEPRECATED(fromM,toM, fromI,toI)  NS_AVAILABLE(fromM,fromI)
#else
  #define CI_GL_DEPRECATED_IOS(from, to)  NS_DEPRECATED_IOS(from, to, "Core Image OpenGLES API deprecated. (Define CI_SILENCE_GL_DEPRECATION to silence these warnings)")
  #define CI_GL_DEPRECATED_MAC(from, to)  NS_DEPRECATED_MAC(from, to, "Core Image OpenGL API deprecated. (Define CI_SILENCE_GL_DEPRECATION to silence these warnings)")
  #define CI_GL_DEPRECATED(fromM,toM, fromI,toI)  NS_DEPRECATED(fromM,toM, fromI,toI, "Core Image OpenGL API deprecated. (Define CI_SILENCE_GL_DEPRECATION to silence these warnings)")
  #define CIKL_DEPRECATED(fromM,toM, fromI,toI)  NS_DEPRECATED(fromM,toM, fromI,toI, "Core Image Kernel Language API deprecated. (Define CI_SILENCE_GL_DEPRECATION to silence these warnings)")
#endif


#endif /* COREIMAGEDEFINES_H */
// ==========  CoreImage.framework/Headers/CIBarcodeDescriptor.h
/* CoreImage - CIBarcodeDescriptor.h

   Copyright (c) 2017 Apple, Inc.
   All rights reserved. */

#import <CoreImage/CoreImageDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class CIBarcodeDescriptor
 @abstract
    CIBarcodeDescriptor is an abstract base class that defines an abstract representation of a machine readable code's symbol attributes.
 
 @discsussion
    Each subclass is sufficient to recreate the symbol exactly as seen or to be used with a custom parser. Subclasses of CIBarcodeDescriptor are defined for each code type to contain the formal specification of each symbology.
 
 */
NS_CLASS_AVAILABLE(10_13, 11_0)
@interface CIBarcodeDescriptor : NSObject <NSSecureCoding, NSCopying>
@end

/*!
 @enum CIQRCodeErrorCorrectionLevel
 @abstract
    Constants indicating the percentage of the symbol that is dedicated to error correction.
 
 @constant CIQRCodeErrorCorrectionLevelL
    Indicates that approximately 20% of the symbol data is dedicated to error correction.
 @constant CIQRCodeErrorCorrectionLevelM
    Indicates that approximately 37% of the symbol data is dedicated to error correction.
 @constant CIQRCodeErrorCorrectionLevelQ
    Indicates that approximately 55% of the symbol data is dedicated to error correction.
 @constant CIQRCodeErrorCorrectionLevelH
    Indicates that approximately 65% of the symbol data is dedicated to error correction.
 */
typedef CF_ENUM(NSInteger, CIQRCodeErrorCorrectionLevel)
{
    CIQRCodeErrorCorrectionLevelL NS_SWIFT_NAME(levelL) = 'L',
    CIQRCodeErrorCorrectionLevelM NS_SWIFT_NAME(levelM) = 'M',
    CIQRCodeErrorCorrectionLevelQ NS_SWIFT_NAME(levelQ) = 'Q',
    CIQRCodeErrorCorrectionLevelH NS_SWIFT_NAME(levelH) = 'H',

} NS_SWIFT_NAME(CIQRCodeDescriptor.ErrorCorrectionLevel);

/*!
 @class CIQRCodeDescriptor
 @abstract
    CIQRCodeDescriptor is a concrete subclass of CIBarcodeDescriptor that defines an abstract representation of a QR code symbol. 
 */
NS_CLASS_AVAILABLE(10_13, 11_0)
@interface CIQRCodeDescriptor : CIBarcodeDescriptor
{
    NSData *errorCorrectedPayload;

    NSInteger symbolVersion;
    uint8_t maskPattern;
    CIQRCodeErrorCorrectionLevel errorCorrectionLevel;
}

/*!
 @property errorCorrectedPayload
 @abstract
 The error-corrected codewords that comprise the QR code symbol.
 
 @discussion
 QR Codes are formally specified in ISO/IEC 18004:2006(E). Section 6.4.10 "Bitstream to codeword conversion" specifies the set of 8-bit codewords in the symbol immediately prior to splitting the message into blocks and applying error correction.
 
 During decode, error correction is applied and if successful, the message is re-ordered to the state immediately following "Bitstream to codeword coversion." The errorCorrectedPayload corresponds to this sequence of 8-bit codewords.
 */
@property (readonly) NSData *errorCorrectedPayload;

/*!
 @property symbolVersion
 @abstract
    The version property corresponds to the size of the QR Code.

 @discussion
    QR Codes are square. ISO/IEC 18004 defines versions from 1 to 40, where a higher symbol version indicates a larger data carrying capacity. This field is required in order to properly interpret the error corrected payload.
 */
@property (readonly) NSInteger symbolVersion;

/*!
 @property maskPattern
 @abstract
    The data mask pattern for the QR code symbol.
 
 @discussion
    QR Codes support eight data mask patterns, which are used to avoid large black or large white areas inside the symbol body. Valid values range from 0 to 7.
 */
@property (readonly) uint8_t maskPattern;

/*!
 @property errorCorrectionLevel
 @abstract
    The error correction level of the QR code.
 
 @discussion
    QR Codes support four levels of Reed-Solomon error correction, in increasing error correction capability: L, M, Q, and H.
 */
@property (readonly) CIQRCodeErrorCorrectionLevel errorCorrectionLevel;

// Initializes a descriptor that can be used as input to CIBarcodeGenerator
- (nullable instancetype)initWithPayload:(NSData *)errorCorrectedPayload
                           symbolVersion:(NSInteger)symbolVersion
                             maskPattern:(uint8_t)maskPattern
                    errorCorrectionLevel:(CIQRCodeErrorCorrectionLevel)errorCorrectionLevel;

// Construct an autoreleased descriptor that can be used as input to CIBarcodeGenerator
+ (nullable instancetype)descriptorWithPayload:(NSData *)errorCorrectedPayload
                                 symbolVersion:(NSInteger)symbolVersion
                                   maskPattern:(uint8_t)maskPattern
                          errorCorrectionLevel:(CIQRCodeErrorCorrectionLevel)errorCorrectionLevel;

@end


/*!
 @class CIAztecCodeDescriptor
 @abstract
    CIAztecCodeDescriptor is a concrete subclass of CIBarcodeDescriptor that defines an abstract representation of an Aztec Code symbol.
 
 @discussion
    CIAztecCodeDescriptor may not be instantiated directly.
 */
NS_CLASS_AVAILABLE(10_13, 11_0)
@interface CIAztecCodeDescriptor : CIBarcodeDescriptor
{
    NSData *errorCorrectedPayload;

    BOOL isCompact;
    NSInteger layerCount;
    NSInteger dataCodewordCount;
}

/*!
 @property errorCorrectedPayload
 @abstract
 The error-corrected codewords that comprise the Aztec code symbol.
 
 @discussion
 Aztec Codes are formally specified in ISO/IEC 24778:2008(E).
 
 The error corrected payload consists of the 6-, 8-, 10-, or 12-bit message codewords produced at the end of the step described in section 7.3.1.2 "Formation of data codewords", which exists immediately prior to adding error correction. These codewords have dummy bits inserted to ensure that an entire codeword isn't all 0's or all 1's. Clients will need to remove these extra bits as part of interpreting the payload.
 */
@property (readonly) NSData *errorCorrectedPayload;

/*!
 @property isCompact
 @abstract
    A BOOL indicating whether the symbol is compact.
 
 @discussion
    Compact Aztec symbols use one-fewer ring in the central finder pattern than full-range Aztec symbols of the same number of data layers.
 */
@property (readonly) BOOL isCompact;

/*!
 @property layerCount
 @abstract
    The number of data layers in the Aztec code symbol.
 
 @discussion
    Combined with the isCompact property, the number of data layers determines the number of modules in the Aztec Code symbol. Valid values range from 1 to 32. Compact symbols can have up to 4 data layers.
 
    The number of data layers also determines the number of bits in each data codeword of the message carried by the Aztec Code symbol.
 */
@property (readonly) NSInteger layerCount;

/*!
 @property dataCodewordCount
 @abstract
    The number of non-error-correction codewords carried by the Aztec code symbol.
 
 @discussion
    Used to determine the level of error correction in conjunction with the number of data layers. Valid values are 1...2048. Compact symbols can have up to 64 message codewords.
 
    Note that this value can exceed the number of message codewords allowed by the number of data layers in this symbol. In this case, the actual number of message codewords is 1024 fewer than this value and the message payload is to be interpreted in an application-defined manner.
 */
@property (readonly) NSInteger dataCodewordCount;

// Initializes a descriptor that can be used as input to CIBarcodeGenerator
- (nullable instancetype)initWithPayload:(NSData *)errorCorrectedPayload
                               isCompact:(BOOL)isCompact
                              layerCount:(NSInteger)layerCount
                       dataCodewordCount:(NSInteger)dataCodewordCount;

// Construct an autoreleased descriptor that can be used as input to CIBarcodeGenerator
+ (nullable instancetype)descriptorWithPayload:(NSData *)errorCorrectedPayload
                                     isCompact:(BOOL)isCompact
                                    layerCount:(NSInteger)layerCount
                             dataCodewordCount:(NSInteger)dataCodewordCount;

@end

/*!
 @class CIPDF417CodeDescriptor
 @abstract
    CIPDF417CodeDescriptor is a concrete subclass of CIBarcodeDescriptor that defines an abstract representation of a PDF417 code symbol.
 
 @discussion
    Refer to the ISO/IEC 15438:2006(E) for the PDF417 symbol specification.
 
 */
NS_CLASS_AVAILABLE(10_13, 11_0)
@interface CIPDF417CodeDescriptor : CIBarcodeDescriptor
{   
    NSData *errorCorrectedPayload;
    
    BOOL isCompact;
    NSInteger rowCount;
    NSInteger columnCount;
}

/*!
 @property errorCorrectedPayload
 @abstract
 The error-corrected codewords which comprise the PDF417 symbol. The first codeword indicates the number of data codewords in the errorCorrectedPayload.
 
 @discussion
 PDF417 codes are comprised of a start character on the left and a stop character on the right. Each row begins and ends with special characters indicating the current row as well as information about the dimensions of the PDF417 symbol. The errorCorrectedPayload represents the sequence of PDF417 codewords that make up the body of the message. The first codeword indicates the number of codewords in the message. This count includes the "count" codeword and any padding codewords, but does not include the error correction codewords. Each codeword is a 16-bit value in the range of 0...928. The sequence is to be interpreted as described in the PDF417 bar code symbology specification -- ISO/IEC 15438:2006(E).
 */
@property(readonly) NSData *errorCorrectedPayload;

/*!
 @property isCompact
 @abstract
    A BOOL indicating whether the symbol is compact.
 
 @discussion
    Compact PDF417 symbols have abbreviated right-side guard bars.
 */
@property (readonly) BOOL isCompact;

/*!
 @property rowCount
 @abstract
    Indicates the number of rows in the rectangular matrix.
 
 @discussion
    rowCount values range from 3 to 90.
 */
@property (readonly) NSInteger rowCount;

/*!
 @property columnCount
 @abstract
    Indicates the number of columns in the rectangular matrix, excluding the columns used to indicate the symbol structure.
 
 @discussion
    columnCount values range from 1 to 30.
 */
@property (readonly) NSInteger columnCount;

// Initializes a descriptor that can be used as input to CIBarcodeGenerator
- (nullable instancetype)initWithPayload:(NSData *)errorCorrectedPayload
                               isCompact:(BOOL)isCompact
                                rowCount:(NSInteger)rowCount
                             columnCount:(NSInteger)columnCount;

// Construct an autoreleased descriptor that can be used as input to CIBarcodeGenerator
+ (nullable instancetype)descriptorWithPayload:(NSData *)errorCorrectedPayload
                                     isCompact:(BOOL)isCompact
                                      rowCount:(NSInteger)rowCount
                                   columnCount:(NSInteger)columnCount;

@end


/*!
 @enum CIDataMatrixCodeECCVersion
 @abstract
    Constants indicating the Data Matrix code ECC version.
 
 @discussion
    ECC 000 - 140 symbols offer five levels of error correction using convolutional code error correction. Each successive level of error correction offers more protection for the message data and increases the size of the symbol required to carry a specific message. ECC 000 symbols offer no data protection. The other modes are described in ISO/IEC 16022:2006 and enumerated in this list only for completeness.
 
    ECC 200 symbols utilize Reed-Solomon error correction. The error correction capacity for any given Data Matrix symbol is fixed by the size (in rows and columns) of the symbol. See Table 7 of ISO/IEC 16022:2006(E) for more details.
 
 @constant CIDataMatrixCodeECCVersion000
    Indicates error correction using convolutional code error correction with no data protection.
 @constant CIDataMatrixCodeECCVersion050
    Indicates 1/4 of the symbol is dedicated to convolutional code error correction.
 @constant CIDataMatrixCodeECCVersion080
    Indicates 1/3 of the symbol is dedicated to convolutional code error correction.
 @constant CIDataMatrixCodeECCVersion100
    Indicates 1/2 of the symbol is dedicated to convolutional code error correction.
 @constant CIDataMatrixCodeECCVersion140
    Indicates 3/4 of the symbol is dedicated to convolutional code error correction.
 @constant CIDataMatrixCodeECCVersion200
    Indicates error correction using Reed-Solomon error correction. Data protection overhead varies based on symbol size.
 */
typedef CF_ENUM(NSInteger, CIDataMatrixCodeECCVersion)
{
    CIDataMatrixCodeECCVersion000 NS_SWIFT_NAME(v000) =   0,
    CIDataMatrixCodeECCVersion050 NS_SWIFT_NAME(v050) =  50,
    CIDataMatrixCodeECCVersion080 NS_SWIFT_NAME(v080) =  80,
    CIDataMatrixCodeECCVersion100 NS_SWIFT_NAME(v100) = 100,
    CIDataMatrixCodeECCVersion140 NS_SWIFT_NAME(v140) = 140,
    CIDataMatrixCodeECCVersion200 NS_SWIFT_NAME(v200) = 200,

} NS_SWIFT_NAME(CIDataMatrixCodeDescriptor.ECCVersion);

/*!
 @class CIDataMatrixCodeDescriptor
 @abstract
    CIDataMatrixCodeDescriptor is a concrete subclass of CIBarcodeDescriptor that defines an abstract representation of a Data Matrix code symbol.

 */
NS_CLASS_AVAILABLE(10_13, 11_0)
@interface CIDataMatrixCodeDescriptor : CIBarcodeDescriptor
{
    NSData *errorCorrectedPayload;

    NSInteger rowCount;
    NSInteger columnCount;
    CIDataMatrixCodeECCVersion eccVersion;
}

/*!
 @property errorCorrectedPayload
 @abstract
 The error corrected payload that comprise the Data Matrix code symbol.
 
 @discussion
 DataMatrix symbols are specified bn ISO/IEC 16022:2006(E). ECC 200-type symbols will always have an even number of rows and columns.
 
 For ECC 200-type symbols, the phases of encoding data into a symbol are described in section 5.1 -- Encode procedure overview. The error corrected payload comprises the de-interleaved bits of the message described at the end of Step 1: Data encodation.
 */
@property (readonly) NSData *errorCorrectedPayload;

/*!
 @property rowCount
 @abstract
    The number of module rows.
 
 @discussion
    Refer to ISO/IEC 16022:2006(E) for valid module row and column count combinations.
 */
@property (readonly) NSInteger rowCount;

/*!
 @property columnCount
 @abstract
    The number of module columns.
 
 @discussion
    Refer to ISO/IEC 16022:2006(E) for valid module row and column count combinations.
 */
@property (readonly) NSInteger columnCount;

/*!
 @property eccVersion
 @abstract
    The Data Matrix code ECC version.

 @discussion
    Valid values are 000, 050, 080, 100, 140, and 200. Any symbol with an even number of rows and columns will be ECC 200.
 */
@property (readonly) CIDataMatrixCodeECCVersion eccVersion;

// Initializes a descriptor that can be used as input to CIBarcodeGenerator
- (nullable instancetype)initWithPayload:(NSData *)errorCorrectedPayload
                                rowCount:(NSInteger)rowCount
                             columnCount:(NSInteger)columnCount
                              eccVersion:(CIDataMatrixCodeECCVersion)eccVersion;

// Construct an autoreleased descriptor that can be used as input to CIBarcodeGenerator
+ (nullable instancetype)descriptorWithPayload:(NSData *)errorCorrectedPayload
                                      rowCount:(NSInteger)rowCount
                                   columnCount:(NSInteger)columnCount
                                    eccVersion:(CIDataMatrixCodeECCVersion)eccVersion;

@end

/*!
 @extension NSUserActivity
 @abstract
    A NSUserActivity extension for passing detected barcodes.
 */

#if __OBJC2__

@class NSUserActivity;

@interface NSUserActivity (CIBarcodeDescriptor)

/*! 
 @abstract The scanned code in the user activity passed in by system scanner.
 */
@property (nonatomic, nullable, readonly, copy) CIBarcodeDescriptor *detectedBarcodeDescriptor API_AVAILABLE(macos(10.13.4), ios(11.3), tvos(11.3));

@end

#endif // __OBJC2__

NS_ASSUME_NONNULL_END
// ==========  CoreImage.framework/Headers/CoreImage.h
/* CoreImage - CoreImage.h
 
 Copyright (c) 2014 Apple, Inc.
 All rights reserved. */

#ifdef __OBJC__

#import <CoreImage/CoreImageDefines.h>
#import <Foundation/Foundation.h>

#define UNIFIED_CORE_IMAGE 1

#import <CoreImage/CIVector.h>
#import <CoreImage/CIColor.h>
#import <CoreImage/CIImage.h>
#import <CoreImage/CIContext.h>
#import <CoreImage/CIFilter.h>
#import <CoreImage/CIKernel.h>
#import <CoreImage/CIDetector.h>
#import <CoreImage/CIFeature.h>
#import <CoreImage/CIImageProvider.h>
#import <CoreImage/CIImageProcessor.h>
#import <CoreImage/CIImageAccumulator.h>
#import <CoreImage/CIFilterConstructor.h>
#import <CoreImage/CIFilterShape.h>
#import <CoreImage/CISampler.h>
#import <CoreImage/CIRAWFilter.h>
#import <CoreImage/CIRenderDestination.h>
#import <CoreImage/CIBarcodeDescriptor.h>
#if !TARGET_OS_IPHONE
#import <CoreImage/CIFilterGenerator.h>
#import <CoreImage/CIPlugIn.h>
#endif

#endif /* __OBJC__ */

#import <CoreImage/CIKernelMetalLib.h>
// ==========  CoreImage.framework/Headers/CIColor.h
/* 
   CoreImage - CIColor.h

   Copyright (c) 2015 Apple, Inc.
   All rights reserved. 
*/

#import <CoreImage/CoreImageDefines.h>
#import <Foundation/Foundation.h>
#import <CoreImage/CIVector.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_4, 5_0)
@interface CIColor : NSObject <NSSecureCoding, NSCopying>
{
    void *_priv;
    void *_pad[3];
}

/* Create a new color object. */
+ (instancetype)colorWithCGColor:(CGColorRef)c;

/* Create a new color object in CI's default RGB colorspace
   which is kCGColorSpaceSRGB or, if running on OSX before 10.10,
   kCGColorSpaceGenericRGB. */
+ (instancetype)colorWithRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b alpha:(CGFloat)a;
+ (instancetype)colorWithRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b;

/* Create a new color object in a given colorspace. 
 * Will return null if the colorspace is not kCGColorSpaceModelRGB. */
+ (nullable instancetype)colorWithRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b alpha:(CGFloat)a colorSpace:(CGColorSpaceRef)colorSpace NS_AVAILABLE(10_12, 10_0);
+ (nullable instancetype)colorWithRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b colorSpace:(CGColorSpaceRef)colorSpace NS_AVAILABLE(10_12, 10_0);

/* Create a new color object, 'representation' should be a string in one of
 * the formats returned by the stringRepresentation method. */
+ (instancetype)colorWithString:(NSString *)representation;


/* Initialize a new color object. */
- (instancetype)initWithCGColor:(CGColorRef)c NS_DESIGNATED_INITIALIZER;

/* Initialize a new color object in CI's default RGB colorspace
   which is kCGColorSpaceSRGB or, if running on OSX before 10.10,
   kCGColorSpaceGenericRGB. */
- (instancetype)initWithRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b alpha:(CGFloat)a;
- (instancetype)initWithRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b NS_AVAILABLE(10_11, 9_0);

/* Initialize a new color object in a given colorspace.
 * Will return null if the colorspace is not kCGColorSpaceModelRGB. */
- (nullable instancetype)initWithRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b alpha:(CGFloat)a colorSpace:(CGColorSpaceRef)colorSpace NS_AVAILABLE(10_12, 10_0);
- (nullable instancetype)initWithRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b colorSpace:(CGColorSpaceRef)colorSpace NS_AVAILABLE(10_12, 10_0);

/* Return the number of color components (including alpha). */
@property (readonly) size_t numberOfComponents;

/* Return the color components (including alpha). */
@property (readonly) const CGFloat *components NS_RETURNS_INNER_POINTER;

/* Return the alpha value of the color. */
@property (readonly) CGFloat alpha;

/* Return the color space object associated with the color. */
@property (readonly) CGColorSpaceRef colorSpace CF_RETURNS_NOT_RETAINED;

/* Return the (unpremultiplied) red, green or blue components of the color. */
@property (readonly) CGFloat red;
@property (readonly) CGFloat green;
@property (readonly) CGFloat blue;

/* Returns a formatted string with the components of the color.
 * The string is suitable for passing to [CIColor colorWithString:].
 * This property is not KVO-safe because it returns a new NSString each time.
 * The value of the NSString will be the same each time it is called. */
@property (readonly) NSString *stringRepresentation;

/* Convenience constant CIColors in the sRGB colorspace. */
@property (class, strong, readonly) CIColor *blackColor   NS_AVAILABLE(10_12, 10_0);
@property (class, strong, readonly) CIColor *whiteColor   NS_AVAILABLE(10_12, 10_0);
@property (class, strong, readonly) CIColor *grayColor    NS_AVAILABLE(10_12, 10_0);
@property (class, strong, readonly) CIColor *redColor     NS_AVAILABLE(10_12, 10_0);
@property (class, strong, readonly) CIColor *greenColor   NS_AVAILABLE(10_12, 10_0);
@property (class, strong, readonly) CIColor *blueColor    NS_AVAILABLE(10_12, 10_0);
@property (class, strong, readonly) CIColor *cyanColor    NS_AVAILABLE(10_12, 10_0);
@property (class, strong, readonly) CIColor *magentaColor NS_AVAILABLE(10_12, 10_0);
@property (class, strong, readonly) CIColor *yellowColor  NS_AVAILABLE(10_12, 10_0);
@property (class, strong, readonly) CIColor *clearColor   NS_AVAILABLE(10_12, 10_0);

@end

NS_ASSUME_NONNULL_END
// ==========  CoreImage.framework/Headers/CIKernel.h
/* CoreImage - CIKernel.h

   Copyright (c) 2014 Apple, Inc.
   All rights reserved. */

#import <CoreImage/CoreImageDefines.h>
#import <CoreImage/CIImage.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/* Block callback used by Core Image to ask what rectangles of a kernel's input images
 * are needed to produce a desired rectangle of the kernel's output image.
 *
 * 'index' is the 0-based index specifying which of the kernel's input images is being queried.
 * 'destRect' is the extent rectangle of kernel's output image being queried.
 *
 * Returns the rectangle of the index'th input image that is needed to produce destRect.
 * Returning CGRectNull indicates that the index'th input image is not needed to produce destRect.
 * The returned rectangle need not be contained by the extent of the index'th input image.
 */
typedef CGRect (^CIKernelROICallback)(int index, CGRect destRect);


@class CIImage;


/*
 * CIKernel is an object that encapsulates a Core Image Kernel Language
 * routine that generates a new images based on input images and agruments.
 *
 * General kernel functions are declared akin to this example:
 *   kernel vec4 myColorKernel (sampler fore, sampler back, vec4 params)
 *
 * The function must take a sampler argument for each input image.
 * Additional arguments can be of type float, vec2, vec3, vec4, or __color.
 * The destination pixel location is obtained by calling destCoord().
 * The kernel should call sample() with coordinates based on either
 * samplerCoord() or samplerTransform() to read pixel values from input images.
 * The function must return a vec4 pixel color.
 */
NS_CLASS_AVAILABLE(10_4, 8_0)
@interface CIKernel : NSObject
{
    void *_priv;
}

/* The string argument should contain a program in the Core Image Kernel Language.
 * All the kernel functions in the program are converted to instances of a CIKernel objects
 * and returned in an array.
 * On OSX 10.10 and before, the array will contain instances of CIKernel class.
 * On OSX after 10.10, the array will contain instances of CIKernel, CIColorKernel or CIWarpKernel classes.
 * On iOS, the array will contain instances of CIKernel, CIColorKernel or CIWarpKernel classes.
 */
+ (nullable NSArray<CIKernel *> *)kernelsWithString:(NSString *)string  CIKL_DEPRECATED(10_4,10_14, 8_0,12_0);

/* The string argument should contain a program with one kernel.
 * On OSX 10.10 and before, this returns a CIKernel object.
 * On OSX after 10.10, this returns a CIKernel, CIColorKernel, or CIWarpKernel object.
 * On iOS this returns a CIKernel, CIColorKernel, or CIWarpKernel object.
 */
+ (nullable instancetype)kernelWithString:(NSString *)string  CIKL_DEPRECATED(10_10,10_14, 8_0,12_0);

/* The data argument should represent a metallib file compiled with the Core Image Standard Library
 * and contain the given function written in the Metal Shading Language.
 *
 * An optional output pixel format can be specified, and would be used if the output of the kernel
 * needs to be written to an intermediate texture.
 */
+ (nullable instancetype)kernelWithFunctionName:(NSString *)name
                           fromMetalLibraryData:(NSData *)data
                                          error:(NSError **)error NS_AVAILABLE(10_13, 11_0);

+ (nullable instancetype)kernelWithFunctionName:(NSString *)name
                           fromMetalLibraryData:(NSData *)data
                              outputPixelFormat:(CIFormat)format
                                          error:(NSError **)error NS_AVAILABLE(10_13, 11_0);

/* The name of the kernel. */
@property (atomic, readonly) NSString *name  NS_AVAILABLE(10_4, 8_0);

/* Sets the selector used by Core Image to ask what rectangles of a kernel's input images
 * are needed to produce a desired rectangle of the kernel's output image.
 *
 * Using setROISelector: is suppoted but not recommended.
 * The selector is only used if one the [CIFilter apply:...] methods is used.
 * Instead, use one of the [CIKernel applyWithExtent:roiCallback:...] methods.
 *
 * The method should have one of the following signatures:
 *  - (CGRect)regionOf:(int)samplerIndex destRect:(CGRect)r userInfo:obj;
 *  - (CGRect)regionOf:(int)samplerIndex destRect:(CGRect)r;
 *
 * 'samplerIndex' is the 0-based index specifying which of the kernel's input images is being queried.
 * 'destRect' is the extent rectangle of kernel's output image being queried.
 * 'userInfo' is the object associated with the kCIApplyOptionUserInfo when the kernel was applied.
 *
 * The method should return the rectangle of the index'th input image that is needed to produce destRect.
 * Returning CGRectNull indicates that the index'th input image is not needed to produce destRect.
 */
- (void)setROISelector:(SEL)method  NS_AVAILABLE(10_4, 9_0);

/* Apply the receiver CIKernel to produce a new CIImage object.
 *
 * The 'extent' is the bounding box of all non-clear pixels produced by the kernel.
 *
 * The 'callback' is a block that should return the rectangle of each input image
 * that is needed to produce a given rectangle in the coordinate space of the
 * new image.
 *
 * The 'args' is an array of parameters needed to describe the new image.
 * The object types of the items in the array correspond to the argument types of the
 * kernel function.  For example, if the first argument in the kernel is a sampler,
 * then the first object in the array must be a CIImage.
 */
- (nullable CIImage *)applyWithExtent:(CGRect)extent
                          roiCallback:(CIKernelROICallback)callback
                            arguments:(nullable NSArray<id> *)args  NS_AVAILABLE(10_11, 8_0);
@end



/*
 * CIColorKernel is an object that encapsulates a Core Image Kernel Language
 * routine that processes only the color information in images.
 *
 * Color kernel functions are declared akin to this example:
 *   kernel vec4 myColorKernel (__sample fore, __sample back, vec4 params)
 *
 * The function must take a __sample argument for each input image.
 * Additional arguments can be of type float, vec2, vec3, vec4, or __color.
 * The destination pixel location is obtained by calling destCoord().
 * The kernel should not call sample(), samplerCoord(), or samplerTransform().
 * The function must return a vec4 pixel color.
 */
NS_CLASS_AVAILABLE(10_11, 8_0)
@interface CIColorKernel : CIKernel
{
}

/* The string argument should contain a program with one color kernel.
 * On iOS8 [CIColorKernel kernelWithString:] can return a CIKernel, CIColorKernel, or CIWarpKernel object.
 * On iOS9 [CIColorKernel kernelWithString:] will return a CIColorKernel object or nil.
 * On OS X [CIColorKernel kernelWithString:] will return a CIColorKernel object or nil.
 */
+ (nullable instancetype)kernelWithString:(NSString *)string  CIKL_DEPRECATED(10_10,10_14, 8_0,12_0);

/* Apply the receiver CIColorKernel to produce a new CIImage object.
 *
 * The 'extent' is the bounding box of all non-clear pixels produced by the kernel.
 *
 * The 'args' is an array of parameters needed to describe the new image.
 * The object types of the items in the array correspond to the argument types of the
 * kernel function.  For example, if the first argument in the kernel is a __sample,
 * then the first object in the array must be a CIImage.
 */
- (nullable CIImage *)applyWithExtent:(CGRect)extent
                            arguments:(nullable NSArray<id> *)args;
@end


/*
 * CIWarpKernel is an object that encapsulates a Core Image Kernel Language
 * function that processes only the geometry of an image.
 *
 * Warp kernel functions are declared akin to this example:
 *   kernel vec2 myWarpKernel (vec4 params)
 *
 * Additional arguments can be of type float, vec2, vec3, vec4.
 * The destination pixel location is obtained by calling destCoord().
 * The kernel should not call sample(), samplerCoord(), or samplerTransform().
 * The function must return a vec2 source location.
 */
NS_CLASS_AVAILABLE(10_11, 8_0)
@interface CIWarpKernel : CIKernel
{
}

/* The string argument should contain a program with one warp kernel.
 * On iOS8 [CIWarpKernel kernelWithString:] can return a CIKernel, CIColorKernel, or CIWarpKernel object.
 * On iOS9 [CIWarpKernel kernelWithString:] will return a CIWarpKernel object or nil.
 * On OS X [CIWarpKernel kernelWithString:] will return a CIWarpKernel object or nil.
 */
+ (nullable instancetype)kernelWithString:(NSString *)string  CIKL_DEPRECATED(10_10,10_14, 8_0,12_0);

/* Apply the receiver CIWarpKernel to produce a new CIImage object.
 *
 * The 'extent' is the bounding box of all pixel coordinates that are warped by the
 * kernel to fall within the extent of 'image'.
 *
 * The 'image' is the input image that will be warped into a new image.
 *
 * The 'callback' is a block that should return the rectangle of the input image
 * that is needed to produce a given rectangle in the coordinate space of the
 * new image.
 *
 * The 'args' is an array of parameters needed to describe the warping function.
 * The object types of the items in the array correspond to the argument types of the
 * kernel function.  For example, if the first argument in the kernel is a vec3,
 * then the first object in the array must be a CIVector of count 3.
 */
- (nullable CIImage *)applyWithExtent:(CGRect)extent
                          roiCallback:(CIKernelROICallback)callback
                           inputImage:(CIImage*)image
                            arguments:(nullable NSArray<id> *)args;
@end


/* CIBlendKernel is a special type of color kernel that blends two images. 
 *
 * Blend kernel functions are declared akin to this example:
 *   kernel vec4 myBlendKernel (__sample fore, __sample back)
 *
 * A blend kernel function must have exactly two arguments of type __sample.
 * The first argument represents the value of the source pixel and the second 
 * represents that of the old destination. The vec4 returned by the kernel will 
 * be the new destination color.
 * The kernel should not call sample(), samplerCoord(), or samplerTransform().
 * The function must return a vec4 pixel color.
 */
NS_CLASS_AVAILABLE(10_13, 11_0)
@interface CIBlendKernel : CIColorKernel
{
}

/* The string argument should contain a program with one custom blend kernel. */
+ (nullable instancetype)kernelWithString:(NSString *)string  CIKL_DEPRECATED(10_10,10_14, 8_0,12_0);

/* Apply the receiver CIBlendKernel to produce a new CIImage object
 * by blending a foreground and background images.
 *
 * The 'extent' of the result image will be determined by the reciver and
 * the extent of the forground and background images.  For most of the
 * builtin blend kernels (as well as custom blend kernels) the result image
 * extent will be the union of the forground and background image
 * extents.
 */
- (nullable CIImage *)applyWithForeground:(CIImage*)foreground
                               background:(CIImage*)background;

@end

@interface CIBlendKernel (BuiltIn)

/* Core Image builtin blend kernels */

/* Component-wise operators */

@property (class, strong, readonly) CIBlendKernel *componentAdd;
@property (class, strong, readonly) CIBlendKernel *componentMultiply;
@property (class, strong, readonly) CIBlendKernel *componentMin;
@property (class, strong, readonly) CIBlendKernel *componentMax;

/* Porter Duff
 * http://dl.acm.org/citation.cfm?id=808606
 */
@property (class, strong, readonly) CIBlendKernel *clear;
@property (class, strong, readonly) CIBlendKernel *source;
@property (class, strong, readonly) CIBlendKernel *destination;
@property (class, strong, readonly) CIBlendKernel *sourceOver;
@property (class, strong, readonly) CIBlendKernel *destinationOver;
@property (class, strong, readonly) CIBlendKernel *sourceIn;
@property (class, strong, readonly) CIBlendKernel *destinationIn;
@property (class, strong, readonly) CIBlendKernel *sourceOut;
@property (class, strong, readonly) CIBlendKernel *destinationOut;
@property (class, strong, readonly) CIBlendKernel *sourceAtop;
@property (class, strong, readonly) CIBlendKernel *destinationAtop;
@property (class, strong, readonly) CIBlendKernel *exclusiveOr;

/* PDF 1.7 blend modes
 * http://wwwimages.adobe.com/content/dam/Adobe/en/devnet/pdf/pdfs/PDF32000_2008.pdf
 */

/* Standard separable blend modes */
@property (class, strong, readonly) CIBlendKernel *multiply;
@property (class, strong, readonly) CIBlendKernel *screen;
@property (class, strong, readonly) CIBlendKernel *overlay;
@property (class, strong, readonly) CIBlendKernel *darken;
@property (class, strong, readonly) CIBlendKernel *lighten;
@property (class, strong, readonly) CIBlendKernel *colorDodge;
@property (class, strong, readonly) CIBlendKernel *colorBurn;
@property (class, strong, readonly) CIBlendKernel *hardLight;
@property (class, strong, readonly) CIBlendKernel *softLight;
@property (class, strong, readonly) CIBlendKernel *difference;
@property (class, strong, readonly) CIBlendKernel *exclusion;

/* Standard nonseparable blend modes */
@property (class, strong, readonly) CIBlendKernel *hue;
@property (class, strong, readonly) CIBlendKernel *saturation;
@property (class, strong, readonly) CIBlendKernel *color;
@property (class, strong, readonly) CIBlendKernel *luminosity;

/* Additional blend modes */
@property (class, strong, readonly) CIBlendKernel *subtract;
@property (class, strong, readonly) CIBlendKernel *divide;
@property (class, strong, readonly) CIBlendKernel *linearBurn;
@property (class, strong, readonly) CIBlendKernel *linearDodge;
@property (class, strong, readonly) CIBlendKernel *vividLight;
@property (class, strong, readonly) CIBlendKernel *linearLight;
@property (class, strong, readonly) CIBlendKernel *pinLight;
@property (class, strong, readonly) CIBlendKernel *hardMix;
@property (class, strong, readonly) CIBlendKernel *darkerColor;
@property (class, strong, readonly) CIBlendKernel *lighterColor;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreImage.framework/Headers/CISampler.h
/* 
   CoreImage - CISampler.h

   Copyright (c) 2015 Apple, Inc.
   All rights reserved.
*/

#import <CoreImage/CoreImageDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CIFilterShape, CIImage;

NS_CLASS_AVAILABLE(10_4, 9_0)
@interface CISampler : NSObject <NSCopying>
{
    void *_priv;
}

/* Creates a new sampler object refencing 'im'. */
+ (instancetype)samplerWithImage:(CIImage *)im;

/* Creates a new sampler object from 'im' specifying key/value option
 * pairs. Each key is an NSString. Supported keys include:
 *
 * kCISamplerAffineMatrix: An NSArray [a b c d tx ty] defining the
 * transformation to be applied to the sampler.
 *
 * kCISamplerWrapMode: An NSString defining how pixels outside the
 * sampler's extent are produced. Options include kCISamplerWrapBlack
 * (pixels are transparent black, the default) and kCISamplerWrapClamp
 * (coordinates are clamped to the extent).
 *
 * kCISamplerFilterMode: An NSString defining the filter to use when
 * sampling the image. One of kCISamplerFilterNearest (point sampling)
 * or kCISamplerFilterLinear (bilinear interpolation, the default). 
 */
+ (instancetype)samplerWithImage:(CIImage *)im keysAndValues:key0, ... NS_REQUIRES_NIL_TERMINATION;
+ (instancetype)samplerWithImage:(CIImage *)im options:(nullable NSDictionary *)dict;

/* Initializers. */

- (instancetype)initWithImage:(CIImage *)im;
- (instancetype)initWithImage:(CIImage *)im keysAndValues:key0, ...;
- (instancetype)initWithImage:(CIImage *)im options:(nullable NSDictionary *)dict NS_DESIGNATED_INITIALIZER;

/* Returns the shape containing the Domain Of Definition (DOD) of the
 * sampler. The DOD is defined such that it contains all non-transparent
 * pixels produced by referencing the sampler. 
 * This property is KVO-safe 
 */
@property (readonly) CIFilterShape * definition;

/* Returns the extent of the sampler. Sampling outside the extent will
 * bring the sampler's wrap mode into action. 
 */
@property (readonly) CGRect extent;

@end


/* Sampler options. */

CORE_IMAGE_EXPORT NSString *const kCISamplerAffineMatrix NS_AVAILABLE(10_4, 9_0);
CORE_IMAGE_EXPORT NSString *const kCISamplerWrapMode NS_AVAILABLE(10_4, 9_0);
CORE_IMAGE_EXPORT NSString *const kCISamplerFilterMode NS_AVAILABLE(10_4, 9_0);

CORE_IMAGE_EXPORT NSString *const kCISamplerWrapBlack NS_AVAILABLE(10_4, 9_0);
CORE_IMAGE_EXPORT NSString *const kCISamplerWrapClamp NS_AVAILABLE(10_4, 9_0);
CORE_IMAGE_EXPORT NSString *const kCISamplerFilterNearest NS_AVAILABLE(10_4, 9_0);
CORE_IMAGE_EXPORT NSString *const kCISamplerFilterLinear NS_AVAILABLE(10_4, 9_0);

/* If used, the value of the kCISamplerColorSpace key be must be an RGB CGColorSpaceRef.
 * Using this option specifies that samples should be converted to this color space before being passed to a kernel. 
 * If not specified, samples will be passed to the kernel in the working color space of the rendering CIContext. */
CORE_IMAGE_EXPORT NSString *const kCISamplerColorSpace NS_AVAILABLE(10_4, 9_0);

NS_ASSUME_NONNULL_END
// ==========  CoreImage.framework/Headers/CIImageProcessor.h
/* 
   CoreImage - CIImageProcessor.h

   Copyright (c) 2016 Apple Inc.
   All rights reserved. 
*/

#import <CoreImage/CIImage.h>

#if TARGET_OS_OSX
#import <IOSurface/IOSurface.h>
#elif !TARGET_OS_SIMULATOR
#import <IOSurface/IOSurfaceRef.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@protocol MTLTexture, MTLCommandBuffer;

@protocol CIImageProcessorInput;
@protocol CIImageProcessorOutput;

// In order to use a CIImageProcessorInput & CIImageProcessorOutput you must
// subclass from a CIImageProcessorKernel and override the methods you need to
// produce the desired output.


NS_CLASS_AVAILABLE(10_12, 10_0)
@interface CIImageProcessorKernel : NSObject

// Override this class method to implement your processor's subclass of CIImageProcessorKernel.
// The class method will be called to produce the requested region of the output image
// given the required regions of the input images and other arguments.
//
// The class method is passed two objects:
//     'inputs’  An array of id<CIImageProcessorInput> that the block consumes to produces output.
//               The input.region may be larger than the rect returned by 'roiForInputAtIndex'.
//     'output'  The id<CIImageProcessorOutput> that the block must provide results to.
//     ‘arguments’ The arguments dictionary passed to applyWithExtent:inputs:arguments:error:
// The contents of these objects are not valid outside the scope of this method.
//
// Note that since this is a class method you cannot use or capture any state by accident.
// All the parameters that affect the output results must be passed in ‘inputs’ and ‘arguments'.
// This supports 0, 1, 2 or more input images.
//
+ (BOOL)processWithInputs:(nullable NSArray<id<CIImageProcessorInput>> *)inputs
                arguments:(nullable NSDictionary<NSString*,id> *)arguments
                   output:(id <CIImageProcessorOutput>)output
                    error:(NSError **)error;

// Override this class method to implement your processor’s ROI callback, the default implementation would return outputRect.
// This will be called one or more times per render to determine what portion
// of the input images are needed to render a given 'outputRect' of the output.
// This will not be called if there are 0 input images.
//
// Note that since this is a class method you cannot use or capture any state by accident.
// All the parameters that affect the output results must be passed in ‘inputs’ and ‘arguments’.
//
+ (CGRect)roiForInput:(int)input
            arguments:(nullable NSDictionary<NSString*,id> *)arguments
           outputRect:(CGRect)outputRect;

// Override this class method if you want your any of the inputs to be in a specific supported CIPixelFormat.
// The format must be one of kCIFormatBGRA8, kCIFormatRGBAh, kCIFormatRGBAf or kCIFormatR8.
// On iOS 12 and macOS 10.14, the formats kCIFormatRh and kCIFormatRf are also supported.
// If the requested inputFormat is 0, then the input will be a supported format that best
// matches the rendering context's workingFormat.
//
// If a processor wants data in a colorspace other than the context workingspace,
// then call imageByColorMatchingWorkingSpaceToColorSpace on the processor input.
// If a processor wants it input as alpha-unpremultiplied RGBA data, then call
// imageByUnpremultiplyingAlpha on the processor input.
//
+ (CIFormat)formatForInputAtIndex:(int)input;

// Override this class property if you want your processor's output to be in a specific supported CIPixelFormat.
// The format must be one of kCIFormatBGRA8, kCIFormatRGBAh, kCIFormatRGBAf or kCIFormatR8.
// On iOS 12 and macOS 10.14, the formats kCIFormatRh and kCIFormatRf are also supported.
// If the outputFormat is 0, then the output will be a supported format that best
// matches the rendering context's workingFormat.
//
// If a processor returns data in a colorspace other than the context workingspace,
// then call imageByColorMatchingColorSpaceToWorkingSpace on the processor output.
// If a processor returns data as alpha-unpremultiplied RGBA data, then call,
// imageByPremultiplyingAlpha on the processor output.
//
#if __has_feature(objc_class_property)
@property (class, readonly) CIFormat outputFormat;
#else
+(CIFormat)outputFormat;
#endif

// Override this class property if your processor's output stores 1.0 into the
// alpha channel of all pixels within the output extent.
// If not overridden, false is returned.
//
#if __has_feature(objc_class_property)
@property (class, readonly) bool outputIsOpaque NS_AVAILABLE(10_13, 11_0);
#else
+ (bool)outputIsOpaque NS_AVAILABLE(10_13, 11_0);
#endif

// Override this class property to return false if you want your processor to be given
// CIImageProcessorInput objects that have not been synchonized for CPU access.
//
// Generally, if your subclass uses the GPU your should override this method to return false.
// If not overridden, true is returned.
//
#if __has_feature(objc_class_property)
@property (class, readonly) bool synchronizeInputs;
#else
+(bool)synchronizeInputs;
#endif


// Call this method on your CIImageProcessorKernel subclass to create a new CIImage of the specified extent.
// The inputs and arguments will be retained so that your subclass can be called when the image is drawn.
// Arguments is a dictionary containing inmutable objects of type NSData, NSString, NSNumber,
// CIVector or CIColor.
//
// This method will return [CIImage emptyImage] if extent is empty.
//
// This method will return nil and an error if:
// * calling outputFormat on your subclass returns an unsupported format
// * calling formatForInputAtIndex: on your subclass returns an unsupported format
// * your subclass does not implement processWithInputs:arguments:output:error:
//
+ (nullable CIImage *)applyWithExtent:(CGRect)extent
                               inputs:(nullable NSArray<CIImage*> *)inputs
                            arguments:(nullable NSDictionary<NSString*,id> *)args
                                error:(NSError **)error;
@end


NS_CLASS_AVAILABLE(10_12, 10_0)
@protocol CIImageProcessorInput

// The rectangular region of the input image that the processor block can use to provide the output.
// This will be contain (but may be larger than) the rect returned by 'roiCallback'.
@property (nonatomic, readonly) CGRect region;


// The bytes per row of the input buffer that the processor block can read from.
@property (nonatomic, readonly) size_t bytesPerRow;

// The pixel format of the input buffer that the processor block can read from.
@property (nonatomic, readonly) CIFormat format;

// The base address of the input buffer that the processor block can read from.
// This memory must not be modified by the block.
@property (readonly, nonatomic) const void *baseAddress NS_RETURNS_INNER_POINTER;

#if !TARGET_OS_SIMULATOR
// An input IOSurface that the processor block can read from.
// This surface must not be modified by the block.
@property (nonatomic, readonly) IOSurfaceRef surface;
#endif

// An input CVPixelBuffer that the processor block can read from.
// This buffer must not be modified by the block.
@property (nonatomic, readonly, nullable) CVPixelBufferRef pixelBuffer;


// A MTLTexture object that can be bound as input (if processing using Metal).
// This texture must not be modified by the block.
@property (nonatomic, readonly, nullable) id<MTLTexture> metalTexture;

@end


NS_CLASS_AVAILABLE(10_12, 10_0)
@protocol CIImageProcessorOutput

// The rectangular region of the output image that the processor block must provide.
@property (nonatomic, readonly) CGRect region;


// The bytes per row of the output buffer that the processor block can write to.
@property (nonatomic, readonly) size_t bytesPerRow;

// The pixel format of the output buffer that the processor block can write to.
@property (nonatomic, readonly) CIFormat format;

// The base address of the output buffer that the processor block can write output pixels to.
@property (readonly, nonatomic) void *baseAddress NS_RETURNS_INNER_POINTER;

#if !TARGET_OS_SIMULATOR
// An output IOSurface that the processor block can write to.
@property (nonatomic, readonly) IOSurfaceRef surface;
#endif

// A output CVPixelBuffer that the processor block can write to.
@property (nonatomic, readonly, nullable) CVPixelBufferRef pixelBuffer;


// A MTLTexture object that can be bound as output (if processing using Metal).
@property (nonatomic, readonly, nullable) id<MTLTexture> metalTexture;

// Returns a MTLCommandBuffer that can be used for encoding commands (if rendering using Metal).
@property (nonatomic, readonly, nullable) id<MTLCommandBuffer> metalCommandBuffer;

@end


NS_ASSUME_NONNULL_END
// ==========  CoreImage.framework/Headers/CIDetector.h
/* CoreImage - CIDetector.h

   Copyright (c) 2011 Apple, Inc.
   All rights reserved. */


#import <CoreImage/CoreImageDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CIImage;
@class CIContext;
@class CIFeature;

/** Detects features in images.

 This class potentially holds onto a lot of state. Hence it may be beneficial from a performance perspective to re-use the same CIDetector instance. Specifying a CIContext when creating a detector may have an impact on performance since this context may be used when analyzing an image.
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
@interface CIDetector : NSObject {}

/** Returns a new detector instance of the given type.

 The type is used to specify the detection intent.
 This will return value if the detector type is not supported.

 The context argument specifies the CIContext to be used to operate on the image. May be nil.

 If the input image to -featuresInImage: is the output of a CoreImage operation, it may improve performance to specify the same context that was used to operate on that image.

 The detector may do image processing in this context and if the image is on the GPU and the specified context is a GPU context this may avoid additional upload to / download from the GPU. If the input image is on the CPU (or the output from a CPU based context) specifying a GPU based context (or vice versa) may reduce performance.

 The options parameter lets you optinally specify a accuracy / performance tradeoff. Can be nil or an empty dictionary. */
+ (nullable CIDetector *)detectorOfType:(NSString*)type
                                context:(nullable CIContext *)context
                                options:(nullable NSDictionary<NSString *,id> *)options
    NS_AVAILABLE(10_7, 5_0);

/** Returns an array of CIFeature instances in the given image.
 The array is sorted by confidence, highest confidence first. */
- (NSArray<CIFeature *> *)featuresInImage:(CIImage *)image
    NS_AVAILABLE(10_7, 5_0);

/** Returns an array of CIFeature instances in the given image.
 The array is sorted by confidence, highest confidence first.
 The options dictionary can contain a CIDetectorImageOrientation key value. */
- (NSArray<CIFeature *> *)featuresInImage:(CIImage *)image
                                  options:(nullable NSDictionary<NSString *,id> *)options
    NS_AVAILABLE(10_8, 5_0);

@end


// Types to be used for +[CIDetector detectorOfType:context:options:]

/* Specifies a detector type for face recognition. */
CORE_IMAGE_EXPORT NSString* const CIDetectorTypeFace NS_AVAILABLE(10_7, 5_0);

/* Specifies a detector type for rectangle detection. */
CORE_IMAGE_EXPORT NSString* const CIDetectorTypeRectangle NS_AVAILABLE(10_10, 8_0);

/* Specifies a detector type for barcode detection. */
CORE_IMAGE_EXPORT NSString* const CIDetectorTypeQRCode NS_AVAILABLE(10_10, 8_0);

/* Specifies a detector type for text detection. */
#if __OBJC2__
CORE_IMAGE_EXPORT NSString* const CIDetectorTypeText NS_AVAILABLE(10_11, 9_0);
#endif

// Options that can be used with +[CIDetector detectorOfType:context:options:]

/* The key in the options dictionary used to specify a accuracy / performance tradeoff to be used. */
CORE_IMAGE_EXPORT NSString* const CIDetectorAccuracy NS_AVAILABLE(10_7, 5_0);

/* These are values to be used with the CIDetectorAccuracy key when created a CIDetector.
 There is a performance / accuracy tradeoff to be made. The default value will work well for most
 situations, but using these the detector will favour performance over accuracy or
 accuracy over performance. */
CORE_IMAGE_EXPORT NSString* const CIDetectorAccuracyLow NS_AVAILABLE(10_7, 5_0); /* Lower accuracy, higher performance */
CORE_IMAGE_EXPORT NSString* const CIDetectorAccuracyHigh NS_AVAILABLE(10_7, 5_0); /* Lower performance, higher accuracy */

/*The key in the options dictionary used to specify that feature tracking should be used. */
CORE_IMAGE_EXPORT NSString* const CIDetectorTracking NS_AVAILABLE(10_8, 6_0);

/* The key in the options dictionary used to specify the minimum size that the
 detector will recognize as a feature. */

/* For face detector, the value for this key is an float NSNumber
 from 0.0 ... 1.0 that represents a percentage of shorter edge of an input image.
 valid values range: 0.01 <= CIDetectorMinFeatureSize <= 0.5.
 Setting a higher value for this parameter is used for performance gain only. The default value is 0.15. */

/* For rectangle detector, the value for this key is an float NSNumber
 from 0.0 ... 1.0 that represents a percentage of shorter edge of an input image.
 valid values range: 0.2 <= CIDetectorMinFeatureSize <= 1.0 The default value is 0.2. */

/* For text detector, the value for this key is an float NSNumber
 from 0.0 ... 1.0 that represents a percentage of height of an input image.
 valid values range: 0.0 <= CIDetectorMinFeatureSize <= 1.0. The default value is 10/(height of input image). */
CORE_IMAGE_EXPORT NSString* const CIDetectorMinFeatureSize NS_AVAILABLE(10_8, 6_0);

/* For rectangle detector, the value for this key is an integer NSNumber
 from 1 ... 256 that represents the maximum number of features to return. 
 valid value range: 1 <= CIDetectorMaxFeatureCount <= 256. The default value is 1.
 */
CORE_IMAGE_EXPORT NSString* const CIDetectorMaxFeatureCount NS_AVAILABLE(10_12, 10_0);

/* The key in the options dictionary used to specify number of angles, the value for this key is one of 1, 3, 5, 7, 9, 11.*/
CORE_IMAGE_EXPORT NSString* const CIDetectorNumberOfAngles NS_AVAILABLE(10_11, 9_0);

// Options that can be used with -[CIDetector featuresInImage:options:]

/* The value for this key is an integer NSNumber from 1..8 such as that
 found in kCGImagePropertyOrientation.  If present, the detection will be done
 based on that orientation but the coordinates in the returned features will
 still be based on those of the image. */
CORE_IMAGE_EXPORT NSString *const CIDetectorImageOrientation NS_AVAILABLE(10_8, 5_0);

/* The value for this key is a bool NSNumber. If true, facial expressions, such as blinking and closed eyes are extracted */
CORE_IMAGE_EXPORT NSString *const CIDetectorEyeBlink NS_AVAILABLE(10_9, 7_0);


/* The value for this key is a bool NSNumber. If true, facial expressions, such as smile are extracted */
CORE_IMAGE_EXPORT NSString *const CIDetectorSmile NS_AVAILABLE(10_9, 7_0);

/* The value for this key is a float NSNumber. Specifies the per frame focal length.  */
CORE_IMAGE_EXPORT NSString* const CIDetectorFocalLength NS_AVAILABLE(10_10, 8_0);

/* The value for this key is a float NSNumber. Specifies the aspect ratio of the rectangle detected.  */
CORE_IMAGE_EXPORT NSString* const CIDetectorAspectRatio NS_AVAILABLE(10_10, 8_0);

#if __OBJC2__
/* The value for this key is a bool NSNumber. Controls whether the text detector should detect subfeatures or not. The default value is NO */
CORE_IMAGE_EXPORT NSString* const CIDetectorReturnSubFeatures __OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);
#endif

NS_ASSUME_NONNULL_END
// ==========  CoreImage.framework/Headers/CIKernelMetalLib.h
//
//  Extensions to Metal Shading Language for Core Image Kernels
//
//  Copyright (c) 2017 Apple, Inc. All rights reserved.
//

#if __METAL_MACOS__ || __METAL_IOS__

#ifndef CIKERNELMETALLIB_H
#define CIKERNELMETALLIB_H

#ifndef __CIKERNEL_METAL_VERSION__ // if not explicitly defined already
    #if (__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ >= 101400 || __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 120000 || __ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__ >= 120000)
        #define __CIKERNEL_METAL_VERSION__ 200 // compatible w/ macOS 10.14/iOS 12.0/tvOS 12.0 or later
    #else
        #define __CIKERNEL_METAL_VERSION__ 100 // compatible w/ macOS 10.13/iOS 11.0/tvOS 11.0 or later
    #endif
#endif

#include <metal_stdlib>

namespace coreimage
{
    using namespace metal;
    
    typedef float4 sample_t;
    
#if __CIKERNEL_METAL_VERSION__ >= 200
    typedef half4 sample_h;
#endif
    
    //MARK: - Sampler
    
    typedef struct
    {
        // Returns the pixel value produced from sampler at the position p, where p is specified in sampler space.
        float4 sample(float2 p) const;
        
        // Returns the position in the coordinate space of the source that is associated with the position defined in working-space coordinates.
        float2 transform(float2 p) const;
        
        // Returns the position, in sampler space, of the sampler that is associated with the current output pixel (that is, after any transformation matrix
        // associated with sampler is applied). The sample space refers to the coordinate space of that you are texturing from. Note that if your source data is tiled,
        // the sample coordinate will have an offset (dx/dy). You can convert a destination location to the sampler location using the transform function.
        float2 coord() const;
        
        // Returns the extent of the sampler in world coordinates, as a four-element vector [x, y, width, height].
        float4 extent() const;
        
        inline float2 origin() const { return extent().xy; }
        inline float2 size() const { return extent().zw; }
        
#if __CIKERNEL_METAL_VERSION__ >= 200
        // Returns four samples (placed in CCW order starting with sample to the lower left) that would be used for bilinear interpolation when sampling at the position p,
        // where p is specified in sampler space.
        float4 gatherX(float2 p) const;
        float4 gatherY(float2 p) const;
        float4 gatherZ(float2 p) const;
        float4 gatherW(float2 p) const;
        
        // Returns four (unordered) samples that would be used for bilinear interpolation when sampling at the position p, where p is specified in sampler space.
        float4 gatherX_unordered(float2 p) const;
        float4 gatherY_unordered(float2 p) const;
        float4 gatherZ_unordered(float2 p) const;
        float4 gatherW_unordered(float2 p) const;
#endif
        
    private:
        texture2d<float, access::sample> t;
        sampler s;
        constant float4x4& m;
        float2 dc;
        
    } sampler;
    
#if __CIKERNEL_METAL_VERSION__ >= 200
    typedef struct
    {
        // Returns the pixel value produced from sampler at the position p, where p is specified in sampler space.
        half4 sample(float2 p) const;
        
        // Returns the position in the coordinate space of the source that is associated with the position defined in working-space coordinates.
        float2 transform(float2 p) const;
        
        // Returns the position, in sampler space, of the sampler that is associated with the current output pixel (that is, after any transformation matrix
        // associated with sampler is applied). The sample space refers to the coordinate space of that you are texturing from. Note that if your source data is tiled,
        // the sample coordinate will have an offset (dx/dy). You can convert a destination location to the sampler location using the transform function.
        float2 coord() const;
        
        // Returns the extent of the sampler in world coordinates, as a four-element vector [x, y, width, height].
        float4 extent() const;
        
        inline float2 origin() const { return extent().xy; }
        inline float2 size() const { return extent().zw; }
        
        // Returns four samples (placed in CCW order starting with sample to the lower left) that would be used for bilinear interpolation when sampling at the position p,
        // where p is specified in sampler space.
        half4 gatherX(float2 p) const;
        half4 gatherY(float2 p) const;
        half4 gatherZ(float2 p) const;
        half4 gatherW(float2 p) const;
        
        // Returns four (unordered) samples that would be used for bilinear interpolation when sampling at the position p, where p is specified in sampler space.
        half4 gatherX_unordered(float2 p) const;
        half4 gatherY_unordered(float2 p) const;
        half4 gatherZ_unordered(float2 p) const;
        half4 gatherW_unordered(float2 p) const;
        
    private:
        texture2d<half, access::sample> t;
        metal::sampler s;
        constant float4x4& m;
        float2 dc;
        
    } sampler_h;
#endif
    
    // Global equivalents of sampler struct member functions, to facilitate porting of non-Metal legacy CI kernels.
    
    // Equivalent to src.sample(p)
    float4 sample (sampler src, float2 p);
    
    // Equivalent to src.transform(p)
    float2 samplerTransform (sampler src, float2 p);
    
    // Equivalent to src.coord()
    float2 samplerCoord (sampler src);
    
    // Equivalent to src.extent()
    float4 samplerExtent (sampler src);
    
    // Equivalent to src.origin()
    float2 samplerOrigin (sampler src);
    
    // Equivalent to src.size()
    float2 samplerSize (sampler src);
    
    //MARK: - Destination
    
    typedef struct
    {
        // Returns the position, in working space coordinates, of the pixel currently being computed.
        // The destination space refers to the coordinate space of the image you are rendering.
        inline float2 coord() const { return c; }
        
    private:
        float2 c;
        
    } destination;
    
#if __CIKERNEL_METAL_VERSION__ >= 200
    namespace group
    {
        typedef struct
        {
            // Returns the position, in working space coordinates, of the pixel currently being computed.
            // The destination space refers to the coordinate space of the image you are rendering.
            inline float2 coord() const { return c; }
            
            // Writes 4 color values to the destination texture for the current 2x2 group of pixels.
            void write(float4 v0, float4 v1, float4 v2, float4 v3);
            
        private:
            float2 c;
            uint2 gid;
            float4 r;
            float4x4 m;
            texture2d<float, access::write> t;
            
        } __attribute__((packed)) destination;
        
        typedef struct
        {
            // Returns the position, in working space coordinates, of the pixel currently being computed.
            // The destination space refers to the coordinate space of the image you are rendering.
            inline float2 coord() const { return c; }
            
            // Writes 4 color values to the destination texture for the current 2x2 group of pixels.
            void write(half4 v0, half4 v1, half4 v2, half4 v3);
            
        private:
            float2 c;
            uint2 gid;
            float4 r;
            float4x4 m;
            texture2d<half, access::write> t;
            
        } __attribute__((packed)) destination_h;
    }
#endif
    
    //MARK: - Common Functions
    
    float4 premultiply(float4 s);
    float4 unpremultiply(float4 s);
    
    float3 srgb_to_linear(float3 s);
    float3 linear_to_srgb(float3 s);
    
#if __CIKERNEL_METAL_VERSION__ >= 200
    half4 premultiply(half4 s);
    half4 unpremultiply(half4 s);

    half3 srgb_to_linear(half3 s);
    half3 linear_to_srgb(half3 s);
#endif
    
    //MARK: - Relational Functions
    
    // for each component, returns x < 0 ? y : z
    float  compare(float  x, float  y, float  z);
    float2 compare(float2 x, float2 y, float2 z);
    float3 compare(float3 x, float3 y, float3 z);
    float4 compare(float4 x, float4 y, float4 z);
    
#if __CIKERNEL_METAL_VERSION__ >= 200
    half   compare(half   x, half   y, half   z);
    half2  compare(half2  x, half2  y, half2  z);
    half3  compare(half3  x, half3  y, half3  z);
    half4  compare(half4  x, half4  y, half4  z);
#endif
    
    //MARK: - Math Functions
    
    float2 cossin(float x);
    float2 sincos(float x);
}

namespace ci = coreimage;

#endif /* CIKERNELMETALLIB_H */

#endif /* __METAL_MACOS__ || __METAL_IOS__ */
// ==========  CoreImage.framework/Headers/CIImage.h
/*
   CoreImage - CIImage.h

   Copyright (c) 2015 Apple, Inc.
   All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <CoreImage/CoreImageDefines.h>
#import <CoreVideo/CoreVideo.h>
#import <ImageIO/ImageIO.h>

#if TARGET_OS_OSX
#import <IOSurface/IOSurface.h>
#elif !TARGET_OS_SIMULATOR
#import <IOSurface/IOSurfaceRef.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@class CIContext, CIFilterShape, CIColor, CIFilter;
@class AVDepthData;
@class AVPortraitEffectsMatte;

@protocol MTLTexture;

NS_CLASS_AVAILABLE(10_4, 5_0)
@interface CIImage : NSObject <NSSecureCoding, NSCopying>
{
#if TARGET_OS_OSX || 0
    void *_state;
#endif
	void *_priv;
}

/* Pixel formats. */

typedef int CIFormat NS_TYPED_ENUM;

CORE_IMAGE_EXPORT CIFormat kCIFormatARGB8 NS_AVAILABLE(10_4, 6_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatBGRA8;
CORE_IMAGE_EXPORT CIFormat kCIFormatRGBA8;
CORE_IMAGE_EXPORT CIFormat kCIFormatABGR8 NS_AVAILABLE(10_11, 9_0);

CORE_IMAGE_EXPORT CIFormat kCIFormatRGBAh NS_AVAILABLE(10_4, 6_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatRGBA16 NS_AVAILABLE(10_4, 10_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatRGBAf NS_AVAILABLE(10_4, 7_0);

CORE_IMAGE_EXPORT CIFormat kCIFormatA8 NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatA16 NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatAh NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatAf NS_AVAILABLE(10_11, 9_0);

CORE_IMAGE_EXPORT CIFormat kCIFormatR8 NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatR16 NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatRh NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatRf NS_AVAILABLE(10_11, 9_0);

CORE_IMAGE_EXPORT CIFormat kCIFormatRG8 NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatRG16 NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatRGh NS_AVAILABLE(10_11, 9_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatRGf NS_AVAILABLE(10_11, 9_0);

CORE_IMAGE_EXPORT CIFormat kCIFormatL8 NS_AVAILABLE(10_12, 10_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatL16 NS_AVAILABLE(10_12, 10_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatLh NS_AVAILABLE(10_12, 10_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatLf NS_AVAILABLE(10_12, 10_0);

CORE_IMAGE_EXPORT CIFormat kCIFormatLA8 NS_AVAILABLE(10_12, 10_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatLA16 NS_AVAILABLE(10_12, 10_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatLAh NS_AVAILABLE(10_12, 10_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatLAf NS_AVAILABLE(10_12, 10_0);


/* Image options dictionary keys.
   These keys can be passed with appropriate values to the methods:
     + [CIImage imageWith... options:]
     - [CIImage initWith... options:]
   to modify the default behavior of how CIImages are created.
*/

typedef NSString * CIImageOption NS_TYPED_ENUM;

/* A CGColorSpaceRef defining the color space of the image. This value
 * overrides the image's implicit color space.
 * If [NSNull null] then dont color manage the image. */
CORE_IMAGE_EXPORT CIImageOption const kCIImageColorSpace;

/* A boolean value specifying whether the image should sampled using "nearest neighbor" 
 * behavior.  If not specified, the image will be sampled using "linear sampling" */
CORE_IMAGE_EXPORT CIImageOption const kCIImageNearestSampling NS_AVAILABLE(10_13, 11_0);


/* A NSDictionary of metadata properties to pass to CIImage initialization methods.
 * When used with imageWithCGImage:options:, initWithCGImage:options:, imageWithData:options:, initWithData:options:
 *   If this option is not specified, the properties will be set to CGImageSourceCopyPropertiesAtIndex.
 *   If this option is [NSNull null], the properties will be set to nil.
 */
CORE_IMAGE_EXPORT CIImageOption const kCIImageProperties NS_AVAILABLE(10_8, 5_0);


/* A boolean value specifying whether the image should transformed according to orientation metadata properties.
 * This can be used with imageWithContentsOfURL: or initWithData: when the image contains orientation metadata
 * or with any of the initWith:options: method if the kCIImageProperties option is also provided.
 *   If this option value is @YES, the image will transformed according to the orientation metadata
 *   and the orientation metadata will be be removed.
 *   If this option not present or the value is @NO, then the image will not be transformed
 *   and the orientation metadata will left unaltered.
 */
CORE_IMAGE_EXPORT CIImageOption const kCIImageApplyOrientationProperty NS_AVAILABLE(10_13, 11_0);


CORE_IMAGE_EXPORT CIImageOption const kCIImageTextureTarget CI_GL_DEPRECATED_MAC(10_9,10_14);
CORE_IMAGE_EXPORT CIImageOption const kCIImageTextureFormat CI_GL_DEPRECATED_MAC(10_9,10_14);


/* The kCIImageAuxiliaryDepth or kCIImageAuxiliaryDisparity or kCIImageAuxiliaryPortraitEffectsMatte keys can be passed to the methods:
 + [CIImage imageWithContentsOfURL:options:]
 + [CIImage imageWithData:options:]
 If the value of one of these keys is @YES, the auxiliary image be returned instead of the primary image.
 If an auxiliary image is not present, then nil will be returned.
 The returned image will be a half float monochrome image.
 */
CORE_IMAGE_EXPORT CIImageOption const kCIImageAuxiliaryDepth NS_AVAILABLE(10_13, 11_0);
CORE_IMAGE_EXPORT CIImageOption const kCIImageAuxiliaryDisparity NS_AVAILABLE(10_13, 11_0);
CORE_IMAGE_EXPORT CIImageOption const kCIImageAuxiliaryPortraitEffectsMatte NS_AVAILABLE(10_14, 12_0);


/* Creates a new image from the contents of 'image'. */
+ (CIImage *)imageWithCGImage:(CGImageRef)image;
+ (CIImage *)imageWithCGImage:(CGImageRef)image
                      options:(nullable NSDictionary<CIImageOption, id> *)options;

/* Creates a new image from the contents of 'layer'. */
+ (CIImage *)imageWithCGLayer:(CGLayerRef)layer NS_DEPRECATED_MAC(10_4,10_11);
+ (CIImage *)imageWithCGLayer:(CGLayerRef)layer
                      options:(nullable NSDictionary<CIImageOption, id> *)options NS_DEPRECATED_MAC(10_4,10_11);

/* Creates a new image whose bitmap data is from 'data'. Each row contains 'bytesPerRow'
 * bytes. The dimensions of the image are defined by 'size'. 'format' defines
 * the format and size of each pixel. 'colorSpace' defines the color space
 * that the image is defined in, if nil, the image is not color matched. */
+ (CIImage *)imageWithBitmapData:(NSData *)data
                     bytesPerRow:(size_t)bytesPerRow
                            size:(CGSize)size
                          format:(CIFormat)format
                      colorSpace:(nullable CGColorSpaceRef)colorSpace;

/* Creates a new image referencing the contents of the GL texture object
 * with identifier 'name'. The texture should have dimensions as defined
 * by 'size'. If 'flipped' is true, then the contents of the texture are
 * flipped vertically when referenced. 'colorSpace' defines the color space
 * that the image is defined in, if nil, the texture is not color matched.*/
+ (CIImage *)imageWithTexture:(unsigned int)name
                         size:(CGSize)size
                      flipped:(BOOL)flipped
                   colorSpace:(nullable CGColorSpaceRef)colorSpace CI_GL_DEPRECATED(10_4,10_14, 6_0,12_0);

/* In the options dictionary you can specify the following:
 * - kCIImageColorSpace which should be a CGColorSpaceRef or [NSNull null]
 * - kCIImageTextureTarget which should be a NSNumber with either GL_TEXTURE_2D or GL_TEXTURE_RECTANGLE_ARB.
 * - kCIImageTextureFormat which should be a NSNumber with a CIFormat value
 */
+ (CIImage *)imageWithTexture:(unsigned int)name
                         size:(CGSize)size
                      flipped:(BOOL)flipped
                      options:(nullable NSDictionary<CIImageOption, id> *)options CI_GL_DEPRECATED_MAC(10_9,10_14);

/* Creates a new image referencing the contents of the Metal texture object.
 * The texture type must be MTLTextureType2D and the texture format must be unsigned normalized or floating-point.
 * When rendering a CIImage referencing this Metal texture, there should not be any uncommitted Metal comand buffers writing to the texture. */
+ (nullable CIImage *)imageWithMTLTexture:(id<MTLTexture>)texture
                                  options:(nullable NSDictionary<CIImageOption, id> *)options NS_AVAILABLE(10_11, 9_0);

+ (nullable CIImage *)imageWithContentsOfURL:(NSURL *)url;
+ (nullable CIImage *)imageWithContentsOfURL:(NSURL *)url
                                     options:(nullable NSDictionary<CIImageOption, id> *)options;

+ (nullable CIImage *)imageWithData:(NSData *)data;
+ (nullable CIImage *)imageWithData:(NSData *)data
                            options:(nullable NSDictionary<CIImageOption, id> *)options;

/* Creates a new image whose data is from the contents of a CVImageBuffer. */
+ (CIImage *)imageWithCVImageBuffer:(CVImageBufferRef)imageBuffer NS_AVAILABLE(10_4, 9_0);
+ (CIImage *)imageWithCVImageBuffer:(CVImageBufferRef)imageBuffer
                            options:(nullable NSDictionary<CIImageOption, id> *)options NS_AVAILABLE(10_4, 9_0);

/* Creates a new image whose data is from the contents of a CVPixelBufferRef. */
+ (CIImage *)imageWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer NS_AVAILABLE(10_11, 5_0);
+ (CIImage *)imageWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer
                            options:(nullable NSDictionary<CIImageOption, id> *)options NS_AVAILABLE(10_11, 5_0);

#if !TARGET_OS_SIMULATOR
/* Creates a new image from the contents of an IOSurface. */
+ (CIImage *)imageWithIOSurface:(IOSurfaceRef)surface NS_AVAILABLE(10_6, 5_0);
+ (CIImage *)imageWithIOSurface:(IOSurfaceRef)surface
                        options:(nullable NSDictionary<CIImageOption, id> *)options NS_AVAILABLE(10_6, 5_0);
#endif

/* Return or initialize a new image with an infinite amount of the color
 * 'color'. */
+ (CIImage *)imageWithColor:(CIColor *)color;

/* Create an empty Image. */
+ (CIImage *)emptyImage;

/* Initializers. */

- (instancetype)initWithCGImage:(CGImageRef)image;
- (instancetype)initWithCGImage:(CGImageRef)image
                        options:(nullable NSDictionary<CIImageOption, id> *)options;

- (instancetype)initWithCGLayer:(CGLayerRef)layer
    NS_DEPRECATED_MAC(10_4,10_11,"Use initWithCGImage: instead.");
- (instancetype)initWithCGLayer:(CGLayerRef)layer
                        options:(nullable NSDictionary<CIImageOption, id> *)options
    NS_DEPRECATED_MAC(10_4,10_11,"Use initWithCGImage:options instead.");

- (nullable instancetype)initWithData:(NSData *)data;
- (nullable instancetype)initWithData:(NSData *)data
                              options:(nullable NSDictionary<CIImageOption, id> *)options;

- (instancetype)initWithBitmapData:(NSData *)data
                       bytesPerRow:(size_t)bytesPerRow
                              size:(CGSize)size
                            format:(CIFormat)format
                        colorSpace:(nullable CGColorSpaceRef)colorSpace;

- (instancetype)initWithTexture:(unsigned int)name
                           size:(CGSize)size
                        flipped:(BOOL)flipped
                     colorSpace:(nullable CGColorSpaceRef)colorSpace CI_GL_DEPRECATED(10_4,10_14, 6_0,12_0);

- (instancetype)initWithTexture:(unsigned int)name
                           size:(CGSize)size
                        flipped:(BOOL)flipped
                        options:(nullable NSDictionary<CIImageOption, id> *)options CI_GL_DEPRECATED_MAC(10_9,10_14);

// initWithMTLTexture will return nil if textureType is not MTLTextureType2D.
- (nullable instancetype)initWithMTLTexture:(id<MTLTexture>)texture
                                    options:(nullable NSDictionary<CIImageOption, id> *)options NS_AVAILABLE(10_11, 9_0);

- (nullable instancetype)initWithContentsOfURL:(NSURL *)url;
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url
                                       options:(nullable NSDictionary<CIImageOption, id> *)options;

#if !TARGET_OS_SIMULATOR
- (instancetype)initWithIOSurface:(IOSurfaceRef)surface NS_AVAILABLE(10_6, 5_0);

- (instancetype)initWithIOSurface:(IOSurfaceRef)surface
                          options:(nullable NSDictionary<CIImageOption, id> *)options NS_AVAILABLE(10_6, 5_0);
#endif

#if TARGET_OS_OSX
- (instancetype)initWithIOSurface:(IOSurfaceRef)surface
                            plane:(size_t)plane
                           format:(CIFormat)format
                          options:(nullable NSDictionary<CIImageOption, id> *)options NS_DEPRECATED_MAC(10_9,10_11);
#endif

- (instancetype)initWithCVImageBuffer:(CVImageBufferRef)imageBuffer NS_AVAILABLE(10_4, 9_0);
- (instancetype)initWithCVImageBuffer:(CVImageBufferRef)imageBuffer
                              options:(nullable NSDictionary<CIImageOption, id> *)options NS_AVAILABLE(10_4, 9_0);

- (instancetype)initWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer NS_AVAILABLE(10_11, 5_0);
- (instancetype)initWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer
                              options:(nullable NSDictionary<CIImageOption, id> *)options NS_AVAILABLE(10_11, 5_0);

- (instancetype)initWithColor:(CIColor *)color;

/* Returns a new image representing the original image with the transform
 * 'matrix' appended to it. */
- (CIImage *)imageByApplyingTransform:(CGAffineTransform)matrix;

/* Returns a new image representing the original image with a transform applied to it based on an orientation value.
 * CGImagePropertyOrientation enum values from 1 to 8 as defined in the TIFF spec are supported.
 * Returns original image if the image is of infinite extent. */
- (CIImage *)imageByApplyingOrientation:(int)orientation NS_AVAILABLE(10_10, 8_0);

/* Returns a CGAffineTransform for an orientation value that can be applied to an image.
 * CGImagePropertyOrientation enum values from 1 to 8 as defined in the TIFF spec are supported.
 * Returns CGAffineTransformIdentity if the image is of infinite extent.*/
- (CGAffineTransform)imageTransformForOrientation:(int)orientation NS_AVAILABLE(10_10, 8_0);

/* Returns a new image representing the original image transformeded for the given CGImagePropertyOrientation */
- (CIImage *)imageByApplyingCGOrientation:(CGImagePropertyOrientation)orientation NS_AVAILABLE(10_13, 11_0);

/* Returns a CGAffineTransform for the CGImagePropertyOrientation value that can be applied to an image.*/
- (CGAffineTransform)imageTransformForCGOrientation:(CGImagePropertyOrientation)orientation NS_AVAILABLE(10_13, 11_0);

/* Return a new image formed by compositing the receiver image over 'dest'.
 * This is equivalent to the CISourceOverCompositing filter. */
- (CIImage *)imageByCompositingOverImage:(CIImage *)dest NS_AVAILABLE(10_4, 8_0);

/* Return a new image cropped to a rectangle. */
- (CIImage *)imageByCroppingToRect:(CGRect)rect;

/* Return a new infinite image by replicating the edge pixels of the receiver image. */
- (CIImage *)imageByClampingToExtent NS_AVAILABLE(10_10, 8_0);

/* Return a new infinite image by replicating the edge pixels of a rectangle.
 * This is equivalent to the CICrop filter. */
- (CIImage *)imageByClampingToRect:(CGRect)rect NS_AVAILABLE(10_12, 10_0);

/* A convenience method for applying a filter to an image.
 * The method returns outputImage of the filter after setting the
 * filter's inputImage to the method receiver and other parameters
 * from the key/value pairs of 'params'. */
- (CIImage *)imageByApplyingFilter:(NSString *)filterName
               withInputParameters:(nullable NSDictionary<NSString *,id> *)params NS_AVAILABLE(10_10, 8_0);

/* A convenience method for applying a filter to an image.
 * The method returns outputImage of the filter after setting the
 * filter's inputImage to the method receiver and any other parameters
 * from the filter's defaults. */
- (CIImage *)imageByApplyingFilter:(NSString *)filterName NS_AVAILABLE(10_13, 11_0);


/* Return a new image by color matching from the colorSpace to the context's working space.
 * This method will return nil if the CGColorSpace is not kCGColorSpaceModelRGB. */
- (nullable CIImage *)imageByColorMatchingColorSpaceToWorkingSpace:(CGColorSpaceRef)colorSpace NS_AVAILABLE(10_12, 10_0);

/* Return a new image by color matching from the context's working space to the colorSpace.
 * This method will return nil if the CGColorSpace is not kCGColorSpaceModelRGB. */
- (nullable CIImage *)imageByColorMatchingWorkingSpaceToColorSpace:(CGColorSpaceRef)colorSpace NS_AVAILABLE(10_12, 10_0);

/* Return a new image by multiplying the receiver's RGB values by its alpha. */
- (CIImage *)imageByPremultiplyingAlpha NS_AVAILABLE(10_12, 10_0);

/* Return a new image by dividing the receiver's RGB values by its alpha. */
- (CIImage *)imageByUnpremultiplyingAlpha NS_AVAILABLE(10_12, 10_0);

/* Return a new image with alpha set to 1 within the rectangle and 0 outside. */
- (CIImage *)imageBySettingAlphaOneInExtent:(CGRect)extent NS_AVAILABLE(10_12, 10_0);

/* Return a new image by applying a gaussian blur to the receiver. */
- (CIImage *)imageByApplyingGaussianBlurWithSigma:(double)sigma NS_AVAILABLE(10_12, 10_0);

/* Return a new image by changing the recevier's properties. */
- (CIImage *)imageBySettingProperties:(NSDictionary*)properties NS_AVAILABLE(10_12, 10_0);

/* Returns a new image by changing the receiver's sample mode to bilinear interpolation. */
- (CIImage *)imageBySamplingLinear NS_AVAILABLE(10_13, 11_0);

/* Returns a new image by changing the receiver's sample mode to nearest neighbor. */
- (CIImage *)imageBySamplingNearest NS_AVAILABLE(10_13, 11_0);

/* Returns a new image that inserts a intermediate that is cacheable
 * according to the CIContext's kCIContextCacheIntermediates option.  */
- (CIImage *)imageByInsertingIntermediate NS_AVAILABLE(10_14, 12_0);

/* Returns a new image that inserts a intermediate that is cacheable
 * independent of the CIContext's kCIContextCacheIntermediates option.  */
- (CIImage *)imageByInsertingIntermediate:(BOOL)cache NS_AVAILABLE(10_14, 12_0);

/* Return a rect the defines the bounds of non-(0,0,0,0) pixels */
@property (NS_NONATOMIC_IOSONLY, readonly) CGRect extent;

/* Returns the metadata properties of an image. If the image is the
 * output of one or more CIFilters, then the metadata of the root inputImage
 * will be returned. See also kCIImageProperties. */
@property (atomic, readonly) NSDictionary<NSString *,id> *properties NS_AVAILABLE(10_8, 5_0);

/* Return the Domain of Definition of the image. */
@property (atomic, readonly) CIFilterShape *definition NS_AVAILABLE_MAC(10_4);

/* Returns the URL of the image when the image was created using the imageWithContentsOfURL APIs.
 * This method will return nil, if the URL cannot be determined. */
@property (atomic, readonly, nullable) NSURL *url NS_AVAILABLE(10_4, 9_0);

/* Returns if possible the color space of the image it was defined in.
 * This method will return nil, if the color space cannot be determined. */
@property (atomic, readonly, nullable) CGColorSpaceRef colorSpace NS_AVAILABLE(10_4, 9_0) CF_RETURNS_NOT_RETAINED;

/* Returns a CVPixelBufferRef if the CIImage was created with [CIImage imageWithCVPixelBuffer] and no options.
 * Otherwise this property will be nil and calling [CIContext render:toCVPixelBuffer:] is recommended.
 * Modifying the contents of this pixelBuffer will cause the CIImage to render with undefined results. */
@property (nonatomic, readonly, nullable) CVPixelBufferRef pixelBuffer NS_AVAILABLE(10_12, 10_0);

/* Returns a CGImageRef if the CIImage was created with [CIImage imageWithCGImage] or [CIImage imageWithContentsOfURL] and no options.
 * Otherwise this property will be nil and calling [CIContext createCGImage:fromRect:] is recommended. */
@property (nonatomic, readonly, nullable) CGImageRef CGImage NS_AVAILABLE(10_12,10_0);

/* Returns the rectangle of 'image' that is required to render the
 * rectangle 'rect' of the receiver.  This may return a null rect. */
- (CGRect)regionOfInterestForImage:(CIImage *)image
                            inRect:(CGRect)rect NS_AVAILABLE(10_11, 6_0);

@end


@interface CIImage (AutoAdjustment)

/* Image auto adjustment keys. */

typedef NSString * CIImageAutoAdjustmentOption NS_TYPED_ENUM;

/* These are the options dictionary keys which can be specified when calling
 * the autoAdjustmentFiltersWithOptions: method.
 */

/* If CFBoolean value is false then dont attempt to apply enhancement filters.
 * If not specified, the option is assumed to be present and true.
 */
CORE_IMAGE_EXPORT CIImageAutoAdjustmentOption const kCIImageAutoAdjustEnhance NS_AVAILABLE(10_8, 5_0);

/* If CFBoolean value is false then dont attempt to apply red eye filter.
 * If not specified, the option is assumed to be present and true.
 */
CORE_IMAGE_EXPORT CIImageAutoAdjustmentOption const kCIImageAutoAdjustRedEye NS_AVAILABLE(10_8, 5_0);

/* If value is an array of detected CIFeatures, then use these features
 * to determine the AutoAdjustEnhance and or AutoAdjustRedEye filters.
 * If not specified, receiver will call CIDetector.
 */
CORE_IMAGE_EXPORT CIImageAutoAdjustmentOption const kCIImageAutoAdjustFeatures NS_AVAILABLE(10_8, 5_0);

/* If CFBoolean value is false then don't attempt to apply crop filter.
 * If not specified, the option is assumed to be present and false.
 */
CORE_IMAGE_EXPORT CIImageAutoAdjustmentOption const kCIImageAutoAdjustCrop NS_AVAILABLE(10_10, 8_0);

/* If CFBoolean value is false then don't attempt to apply auto-level.
 * If not specified, the option is assumed to be present and false.
 */
CORE_IMAGE_EXPORT CIImageAutoAdjustmentOption const kCIImageAutoAdjustLevel NS_AVAILABLE(10_10, 8_0);


/* Return an array of filters to apply to an image to improve its
 * skin tones, saturation, contrast, shadows and repair red-eyes or LED-eyes.
 *
 * The options dictionary can contain a CIDetectorImageOrientation key value.
 * The value for this key is an integer NSNumber from 1..8 such as that
 * found in kCGImagePropertyOrientation.  If present, the adjustment will be done
 * based on that orientation but any coordinates in the returned filters will
 * still be based on those of the sender image.
 */
- (NSArray<CIFilter *> *)autoAdjustmentFilters NS_AVAILABLE(10_8, 5_0);
- (NSArray<CIFilter *> *)autoAdjustmentFiltersWithOptions:(nullable NSDictionary<CIImageAutoAdjustmentOption, id> *)options
    NS_AVAILABLE(10_8, 5_0);

@end

@interface CIImage (AVDepthData)

/* Returns a AVDepthData if the CIImage was created with [CIImage imageWithData] or [CIImage imageWithContentsOfURL] and.
 * one the options kCIImageAuxiliaryDepth or kCIImageAuxiliaryDisparity. */
@property (nonatomic, readonly, nullable) AVDepthData *depthData NS_AVAILABLE(10_13,11_0);

-(nullable instancetype) initWithDepthData:(AVDepthData *)data
                                   options:(nullable NSDictionary<NSString *,id> *)options NS_AVAILABLE(10_13, 11_0);

-(nullable instancetype)initWithDepthData:(AVDepthData *)data NS_AVAILABLE(10_13, 11_0);

+(nullable instancetype)imageWithDepthData:(AVDepthData *)data
                                   options:(nullable NSDictionary<NSString *,id> *)options NS_AVAILABLE(10_13, 11_0);

+(nullable instancetype)imageWithDepthData:(AVDepthData *)data NS_AVAILABLE(10_13, 11_0);

@end


@interface CIImage (AVPortraitEffectsMatte)

/* Returns a AVPortraitEffectsMatte if the CIImage was created with [CIImage imageWithData] or [CIImage imageWithContentsOfURL] and.
 * one the options kCIImageAuxiliaryPortraitEffectsMatte. */
@property (nonatomic, readonly, nullable) AVPortraitEffectsMatte *portraitEffectsMatte NS_AVAILABLE(10_14,12_0);

-(nullable instancetype) initWithPortaitEffectsMatte:(AVPortraitEffectsMatte *)matte
                                             options:(nullable NSDictionary<CIImageOption,id> *)options NS_AVAILABLE(10_14, 12_0);

-(nullable instancetype)initWithPortaitEffectsMatte:(AVPortraitEffectsMatte *)matte NS_AVAILABLE(10_13, 11_0);

+(nullable instancetype)imageWithPortaitEffectsMatte:(AVPortraitEffectsMatte *)matte
                                            options:(nullable NSDictionary<CIImageOption,id> *)options NS_AVAILABLE(10_14, 12_0);

+(nullable instancetype)imageWithPortaitEffectsMatte:(AVPortraitEffectsMatte *)matte NS_AVAILABLE(10_14, 12_0);

@end

NS_ASSUME_NONNULL_END
// ==========  CoreImage.framework/Headers/CIRAWFilter.h
/* CoreImage - CIKernel.h
 
 Copyright (c) 2006 Apple, Inc.
 All rights reserved. */


#import <CoreImage/CIFilter.h>
#import <CoreImage/CoreImageDefines.h>
#import <CoreVideo/CoreVideo.h>


@class NSURL;
@class NSDictionary;
@class NSData;

typedef NSString * CIRAWFilterOption NS_TYPED_ENUM;

/** CIRAWFilter is a category of CIFilter which returns a CIFilter initialized with a RAW image. It allows the user to influence key aspects of the raw processing, such as white balance, exposure, sharpening or boost. */

@interface CIFilter (CIRAWFilter)

/** Returns a CIFilter that will in turn return a properly processed CIImage as "outputImage". */
+ (CIFilter *)filterWithImageURL:(NSURL *)url options:(NSDictionary<CIRAWFilterOption, id> *)options NS_AVAILABLE(10_5, 10_0);

/** Returns a CIFilter that will in turn return a properly processed CIImage as "outputImage".

 Note that when using this initializer, you should pass in a source type identifier hint (kCGImageSourceTypeIdentifierHint) key/value pair in order to help the decoder determine the file type, as otherwise confusion and incorrect results are possible. */
+ (CIFilter *)filterWithImageData:(NSData *)data options:(NSDictionary<CIRAWFilterOption, id> *)options NS_AVAILABLE(10_5, 10_0);

/** Returns a CIFilter that will in turn return a properly processed CIImage as "outputImage".
 
 Note that when using this initializer, you should pass in a CVPixelBufferRef with one of the following Raw pixel format types
    kCVPixelFormatType_14Bayer_GRBG, kCVPixelFormatType_14Bayer_RGGB, kCVPixelFormatType_14Bayer_BGGR, kCVPixelFormatType_14Bayer_GBRG
 as well as the root properties attachment from the CMSampleBufferRef. */
+ (CIFilter *)filterWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer properties:(NSDictionary *)properties options:(NSDictionary<CIRAWFilterOption, id> *)options NS_AVAILABLE(10_12, 10_0);

/** NSNumber (BOOL) : Setting Draft Mode to YES can improve image decoding speed without minimal loss of quality.
    The default value is NO. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputAllowDraftModeKey NS_AVAILABLE(10_5, 10_0);

/** NSString: Version string representing the decoder version to be used. A newly initialized object defaults to the newest available decoder version for the given image type. User can request an alternative, older version in order to maintain compatibility with older releases. Must be one of kCISupportedDecoderVersions (below), otherwise a nil output image will be generated. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputDecoderVersionKey NS_AVAILABLE(10_5, 10_0);

/** NSArray : Array of all supported decoder versions for the given image type, sorted in increasingly newer order. Each entry is a NSString. All entries would represent a valid version identifier to be passed in for kCIInputDecoderVersion. This value can be only read; setting this value will raise an exception.*/
CORE_IMAGE_EXPORT CIRAWFilterOption const kCISupportedDecoderVersionsKey NS_AVAILABLE(10_5, 10_0);



/** @const      kCIInputEVKey
 NSNumber (float) : Exposure adjustment, default = 0.0. Declared in CIFilter.h */

/** NSNumber (float) : A value controlling the amount of baseline exposure applied to the image.
 A value of 0 indicates no baseline exposure, i.e. linear response. Default varies from with camera settings. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputBaselineExposureKey NS_AVAILABLE(10_12, 10_0);

/** NSNumber (float) : A value in the range of 0...1, controlling the amount of boost applied to the image.
    A value of 0 indicates no boost, i.e. linear response. Default is 1, full boost. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputBoostKey NS_AVAILABLE(10_5, 10_0);

/** NSNumber (float) : The amount to boost the shadow areas of the image. Can be used to lighten details in shadows. 
    Has no effect if the image used for initialization was not RAW. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputBoostShadowAmountKey NS_AVAILABLE(10_5, 10_0);

/** NSNumber (BOOL) : Setting DisableGamutMap to YES disables gamut mapping.
    The default value is NO. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputDisableGamutMapKey NS_AVAILABLE(10_12, 10_0);

/** NSNumber (float): The X value of the chromaticity. You can always query this value and you'll get the current X value for neutral X,Y. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputNeutralChromaticityXKey NS_AVAILABLE(10_5, 10_0);

/** NSNumber (float): The Y value of the chromaticity. You can always query this value and you'll get the current Y value for neutral X,Y. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputNeutralChromaticityYKey NS_AVAILABLE(10_5, 10_0);

/** NSNumber (float) : The color temperature to be considered neutral. You can always query this value and you'll get the current value for temperature. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputNeutralTemperatureKey NS_AVAILABLE(10_5, 10_0);

/** NSNumber (float) : The tint to be considered neutral. You can always query this value and you'll get the current value for tint. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputNeutralTintKey NS_AVAILABLE(10_5, 10_0);

/** CIVector : (x, y) location in geometric coordinates of the unrotated output image that should be used as neutral. 
    You can't query this value - it's undefined for reading. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputNeutralLocationKey NS_AVAILABLE(10_5, 10_0);

/** NSNumber (float) : The desired scale factor at which the image will be eventually drawn. Setting this value can greatly improve the drawing performance. A value of 1 would mean identity, values smaller than 1 will result in a smaller output image. Changing the Scale Factor with enabled Draft Mode may also improve performance. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputScaleFactorKey NS_AVAILABLE(10_5, 10_0);




/** NSNumber (BOOL) : Normally, an image is loaded in its proper orientation, given the associated metadata gives an indication about the orientation. For special purposes it may be useful to load the image in its physical orientation. The exact meaning of this is dependent on the image in question. The default value is NO. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputIgnoreImageOrientationKey NS_AVAILABLE(10_5, 10_0);


/** NSNumber (int) : Overriding this value allows the user to change the orientation of the image. The valid values are in range 1...8 and follow the EXIF specification. Changing this value makes for instance rotation in 90-degree increments easy. The value is disregarded when the kCIInputIgnoreImageOrientationKey flag is set.
 */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputImageOrientationKey NS_AVAILABLE(10_5, 10_0);



/** NSNumber (BOOL) : Determines if the default sharpening should be on. default = YES. Has no effect if the image used for initialization was not RAW. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputEnableSharpeningKey NS_AVAILABLE(10_5, 10_0);

/** NSNumber (BOOL) : Determines if progressive chromatic noise tracking (based on ISO and exposure time) should be used. default = YES. Has no effect if the image used for initialization was not RAW. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputEnableChromaticNoiseTrackingKey NS_AVAILABLE(10_5, 10_0);

/** NSNumber (double) : The amount of noise reduction applied. Range is 0 to 1. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputNoiseReductionAmountKey NS_AVAILABLE(10_7, 10_0);

/** NSNumber (double) : The amount of moire reduction applied. Range is 0 to 1. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputMoireAmountKey NS_AVAILABLE(10_13, 11_0);

/** NSNumber (BOOL) : Determines if the default vendor lens correction be on. default = YES if raw image used for initialization contains lens distortion parameters. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputEnableVendorLensCorrectionKey NS_AVAILABLE(10_10, 10_0);

/** NSNumber (double) : The amount of luminance noise reduction applied. Range is 0 to 1. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputLuminanceNoiseReductionAmountKey NS_AVAILABLE(10_10, 10_0);

/** NSNumber (double) : The amount of color noise reduction applied. Range is 0 to 1. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputColorNoiseReductionAmountKey NS_AVAILABLE(10_10, 10_0);

/** NSNumber (double) : The amount of noise reduction sharpness applied. Range is 0 to 1. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputNoiseReductionSharpnessAmountKey NS_AVAILABLE(10_10, 10_0);

/** NSNumber (double) : The amount of noise reduction contrast applied. Range is 0 to 1. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputNoiseReductionContrastAmountKey NS_AVAILABLE(10_10, 10_0);

/** NSNumber (double) : The amount of noise reduction detail applied. Range is 0 to 1. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputNoiseReductionDetailAmountKey NS_AVAILABLE(10_10, 10_0);




/** CIFilter (id) : CIFilter to be applied to the RAW image while it is in linear space. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIInputLinearSpaceFilter NS_AVAILABLE(10_7, 10_0);

/** CIVector containing the full native size of the unscaled image. The vector's X value is the width, Y is the height. 
    This is not affected by changing either kCIInputIgnoreImageOrientationKey or kCIInputImageOrientationKey. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIOutputNativeSizeKey NS_AVAILABLE(10_5, 10_0);

/** Read-only NSSet containing a list of keys that affect the output image. 
    Depending on the RAW decoder version (kCIInputDecoderVersionKey) and the input image type, 
    some input keys might have no effect. */
CORE_IMAGE_EXPORT CIRAWFilterOption const kCIActiveKeys NS_AVAILABLE(10_7, 10_0);

@end
// ==========  CoreImage.framework/Headers/CIFilterConstructor.h
/* CoreImage - CIFilterConstructor.h
 
 Copyright (c) 2014 Apple, Inc.
 All rights reserved. */


@class NSString;
@class CIFilter;

// Used by +[CIFilter registerFilterName:constructor:classAttributes:]

NS_ASSUME_NONNULL_BEGIN

@protocol CIFilterConstructor
- (nullable CIFilter *)filterWithName:(NSString *)name;
@end

NS_ASSUME_NONNULL_END
// ==========  CoreImage.framework/Headers/CIImageProvider.h
/*
   CoreImage - CIImageProvider.h

   Copyright (c) 2015 Apple, Inc.
   All rights reserved.
*/

#import <CoreImage/CIImage.h>

NS_ASSUME_NONNULL_BEGIN

@interface CIImage (CIImageProvider)

/* Create a new CIImage populated when rendered with  data provided by 'p'.
 * The provider object 'p' is retained until the image is deallocated. 
 * The 'options' dictionary supports kCIImageProviderTileSize as well as
 * other options defined in CIImage.h 
 */
+ (CIImage *)imageWithImageProvider:(id)p
							   size:(size_t)width
                                   :(size_t)height
							 format:(CIFormat)f
						 colorSpace:(nullable CGColorSpaceRef)cs
                            options:(nullable NSDictionary<NSString *,id> *)options
    NS_AVAILABLE(10_4, 9_0);

- (instancetype)initWithImageProvider:(id)p
                                 size:(size_t)width
                                     :(size_t)height
                               format:(CIFormat)f
                           colorSpace:(nullable CGColorSpaceRef)cs
                              options:(nullable NSDictionary<NSString *,id> *)options
    NS_AVAILABLE(10_4, 9_0);

@end

/** Informal protocol used to lazily supply image data. */
@interface NSObject (CIImageProvider)

/* Callee should initialize the given bitmap with the subregion x,y
 * width,height of the image. (this subregion is defined in the image's
 * local coordinate space, i.e. the origin is the top left corner of
 * the image).
 *
 * By default, this method will be called to requests the full image
 * data regardless of what subregion is needed for the current render.
 * All of the image is loaded or none of it is.
 *
 * If the kCIImageProviderTileSize option is specified, then only the
 * tiles that are needed are requested.
 *
 * Changing the virtual memory mapping of the supplied buffer (e.g. using
 * vm_copy () to modify it) will give undefined behavior.
 */
- (void)provideImageData:(void *)data
			 bytesPerRow:(size_t)rowbytes
				  origin:(size_t)x
                        :(size_t)y
					size:(size_t)width
                        :(size_t)height
				userInfo:(nullable id)info;

@end

/* Options that may be supplied to image providers through the dictionary. */

/* Specifies the the tile size that the provideImageData: method will be called for.
 * If the value is:
 *   An NSNumber, then the value specifies a square tile size.
 *
 *   An NSArray or CIVector with two values, then it specifies a rectangular tile width and height.
 *
 *   Not specified, then provideImageData: will be called for the entire image.
 *
 *   NSNull, then provideImageData: can be called for any possible origin and size.
 */
CORE_IMAGE_EXPORT NSString * const kCIImageProviderTileSize NS_AVAILABLE(10_4, 9_0);

/* The object passed when the provideImageData: method is called.
 * It is retained until the image is deallocated.
 */
CORE_IMAGE_EXPORT NSString * const kCIImageProviderUserInfo NS_AVAILABLE(10_4, 9_0);

NS_ASSUME_NONNULL_END
