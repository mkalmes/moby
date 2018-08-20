// ==========  CoreImage.framework/Headers/CIContext.h
/* CoreImage - CIContext.h

   Copyright (c) 2014 Apple, Inc.
   All rights reserved. */

#import <CoreImage/CIImage.h>
#import <CoreImage/CoreImageDefines.h>
#import <CoreVideo/CoreVideo.h>

#if TARGET_OS_IPHONE
 #import <OpenGLES/EAGL.h>
#else
 #import <OpenGL/CGLTypes.h>
#endif 

@class CIFilter;

@protocol MTLDevice, MTLTexture, MTLCommandBuffer;

NS_ASSUME_NONNULL_BEGIN

#if __has_feature(objc_generics)
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary<KeyType, ValueType>
# define CI_ARRAY(ValueType) NSArray <ValueType>
#else
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary
# define CI_ARRAY(ValueType) NSArray
#endif


NS_CLASS_AVAILABLE(10_4, 5_0)
@interface CIContext : NSObject
{
    void *_priv;
}

/* Keys that may be passed in the dictionary while creating contexts: */

/* A CGColorSpaceRef object defining the color space that images are
 * converted to before rendering into the context. */
CORE_IMAGE_EXPORT NSString * const kCIContextOutputColorSpace;

/* A CGColorSpaceRef object defining the color space in which all
 * intermediate operations are performed. */
CORE_IMAGE_EXPORT NSString * const kCIContextWorkingColorSpace;

/* An NSNumber with a CIFormat value defining the pixel format to use for intermediate buffers.
* On iOS GPU the supported values for this key are RGBA8 and RGBAh. If not specified RGBA8 us used.
* On iOS CPU the only supported value for this key is RGBAf. If not specified RGBAf us used.
* On OSX GPU the supported values for this key are RGBA8, RGBAh and RGBAf. If not specified RGBAh us used.
* On OSX CPU the supported values for this key are RGBA8, RGBAh and RGBAf. If not specified RGBAh us used. */
CORE_IMAGE_EXPORT NSString * const kCIContextWorkingFormat NS_AVAILABLE(10_4,8_0);

/* A boolean NSNumber controlling the quality of affine downsample operations.
 * @YES imply that more quality is desired.
 * On iOS the the default value is @NO.
 * On OSX the the default value is @YES. */
CORE_IMAGE_EXPORT NSString * const kCIContextHighQualityDownsample NS_AVAILABLE(10_11,9_0);


/* An NSNumber with a boolean value. When @YES the context will use
 * software rendering. */
CORE_IMAGE_EXPORT NSString * const kCIContextUseSoftwareRenderer;

/* An NSNumber with a boolean value. When @YES the context will use 
 * low priority rendering on the GPU. */
CORE_IMAGE_EXPORT NSString * const kCIContextPriorityRequestLow NS_AVAILABLE_IOS(8_0);

/* Create a new CoreImage context object, all output will be drawn
 * into the surface attached to the OpenGL context 'cglctx'. If 'pixelFormat' is
 * non-null it should be the pixel format object used to create 'cglctx';
 * it's required to be valid for the lifetime of the CIContext.
 * The colorspace should be set to the colorspace of your target otherwise
 * CI will take the colorspace from the CGLContext if available. */
#if !TARGET_OS_IPHONE
+ (CIContext *)contextWithCGLContext:(CGLContextObj)cglctx
						 pixelFormat:(nullable CGLPixelFormatObj)pixelFormat
						  colorSpace:(nullable CGColorSpaceRef)colorSpace
							 options:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_AVAILABLE_MAC(10_6);
#endif

/* DEPRECATED, please use the method above or if you need this
* for backward capability, make sure that you specify the colorspace
* in the options dictionary */
#if !TARGET_OS_IPHONE
+ (CIContext *)contextWithCGLContext:(CGLContextObj)cglctx
						 pixelFormat:(nullable CGLPixelFormatObj)pixelFormat
							 options:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_DEPRECATED_MAC(10_4,10_6);
#endif

/* Create a new CoreImage context object, all output will be drawn
 * into the CG context 'cgctx'. */
+ (CIContext *)contextWithCGContext:(CGContextRef)cgctx
                            options:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_AVAILABLE(10_4,9_0);

+ (CIContext *)contextWithOptions:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_AVAILABLE(10_11,5_0);

#if TARGET_OS_IPHONE
/* Create a new CoreImage context object using 'eaglContext' 
 * Calls to drawImage:atPoint:fromRect: and drawImage:inRect:fromRect:
 * will draw directly though the context. */
+ (CIContext *)contextWithEAGLContext:(EAGLContext *)eaglContext
    NS_AVAILABLE_IOS(5_0);

+ (CIContext *)contextWithEAGLContext:(EAGLContext *)eaglContext
                              options:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_AVAILABLE_IOS(5_0);
#endif

/* If a system has more than one MTLDevice, then you can create a CIContext
 * that uses a specific device. If a client wishes to use the default MTLDevice
 * then call [CIContext contextWithOptions:] instead. */
+ (CIContext *)contextWithMTLDevice:(id<MTLDevice>)device NS_AVAILABLE(10_11,9_0);

+ (CIContext *)contextWithMTLDevice:(id<MTLDevice>)device
                            options:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_AVAILABLE(10_11,9_0);

// The working color space of the CIContext
@property (nonatomic, readonly) CGColorSpaceRef workingColorSpace NS_AVAILABLE(10_11,9_0);


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
 * the results. The caller is responsible for releasing the returned
 * image. */
- (CGImageRef)createCGImage:(CIImage *)image
                   fromRect:(CGRect)fromRect
CF_RETURNS_RETAINED;

/* Create a new CGImage from the specified subrect of the image. If
 * non-nil the new image will be created in the specified format and
 * colorspace. */
- (CGImageRef)createCGImage:(CIImage *)image
                   fromRect:(CGRect)fromRect
                     format:(CIFormat)format
                 colorSpace:(nullable CGColorSpaceRef)colorSpace
CF_RETURNS_RETAINED;

/* Create a CoreGraphics layer object suitable for creating content for
 * subsequently rendering into this CI context. The 'info' parameter is
 * passed into CGLayerCreate () as the auxiliaryInfo dictionary. */
- (CGLayerRef)createCGLayerWithSize:(CGSize)size
                               info:(nullable CFDictionaryRef)info
CF_RETURNS_RETAINED NS_DEPRECATED_MAC(10_4,10_11);

/* Render 'image' to the given bitmap.
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

#if !TARGET_OS_IPHONE
/* Render 'image' to the given IOSurface.
 * The 'bounds' parameter has the following behavior:
 *    The 'image' is rendered into 'surface' so that
 *      point (0,0) of 'image' aligns to the lower left corner of 'surface'.
 *      The 'bounds' acts like a clip rect to limit what region of 'surface' is modified.
 */
- (void)render:(CIImage *)image
   toIOSurface:(IOSurfaceRef)surface
		bounds:(CGRect)bounds
	colorSpace:(nullable CGColorSpaceRef)colorSpace NS_AVAILABLE_MAC(10_6);
#endif

/* Render 'image' into the given CVPixelBuffer. */
- (void)render:(CIImage *)image 
toCVPixelBuffer:(CVPixelBufferRef)buffer NS_AVAILABLE(10_11,5_0);

/* Render 'image' to the given CVPixelBufferRef.
 * The 'bounds' parameter has the following behavior:
 *    In OS X and iOS 9 and later:  The 'image' is rendered into 'buffer' so that
 *      point (0,0) of 'image' aligns to the lower left corner of 'buffer'.
 *      The 'bounds' acts like a clip rect to limit what region of 'buffer' is modified.
 *    In iOS 8 and earlier: The 'bounds' parameter acts to specify the region of 'image' to render.
 *      This region (regarless of its origin) is rendered at upper-left corner of 'buffer'.
 */
- (void)render:(CIImage *)image
toCVPixelBuffer:(CVPixelBufferRef)buffer
        bounds:(CGRect)bounds
    colorSpace:(nullable CGColorSpaceRef)colorSpace NS_AVAILABLE(10_11,5_0);

/* Render 'bounds' of 'image' to a Metal texture
 * optionally specifying what command buffer to use. */
- (void)render:(CIImage *)image
  toMTLTexture:(id<MTLTexture>)texture
 commandBuffer:(nullable id<MTLCommandBuffer>)commandBuffer
        bounds:(CGRect)bounds
    colorSpace:(CGColorSpaceRef)colorSpace NS_AVAILABLE(10_11,9_0);

/* Runs the context's garbage collector to reclaim any resources that
 * are no longer required (e.g. removes textures from the texture cache
 * that reference deleted images.) This method is called automatically
 * after every rendering operation. */
- (void)reclaimResources NS_AVAILABLE_MAC(10_4);

/* Frees any cached data (such as temporary images) associated with the
 * context. This also runs the garbage collector. */
- (void)clearCaches NS_AVAILABLE_MAC(10_4);

/* Returns the maximum dimension for input images that can be processed 
 * on the currect context. */
- (CGSize)inputImageMaximumSize NS_AVAILABLE_IOS(5_0);

/* Returns the maximum dimension for image that can be rendered 
 * on the currect context. */
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
 * shared with other GL resources.
 */
#if !TARGET_OS_IPHONE
+(CIContext *)contextForOfflineGPUAtIndex:(unsigned int)index NS_AVAILABLE_MAC(10_10);
+(CIContext *)contextForOfflineGPUAtIndex:(unsigned int)index
                               colorSpace:(nullable CGColorSpaceRef)colorSpace
                                  options:(nullable CI_DICTIONARY(NSString*,id) *)options
                            sharedContext:(nullable CGLContextObj)sharedContext NS_AVAILABLE_MAC(10_10);
#endif


@end

#undef CI_DICTIONARY
#undef CI_ARRAY

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

/** A barcode feature found by a CIDetector
 All positions are relative to the original image. */

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CIQRCodeFeature : CIFeature
{
    CGRect bounds;
    CGPoint topLeft;
    CGPoint topRight;
    CGPoint bottomLeft;
    CGPoint bottomRight;
    NSString* messageString;
}

@property (readonly) CGRect bounds;
@property (readonly) CGPoint topLeft;
@property (readonly) CGPoint topRight;
@property (readonly) CGPoint bottomLeft;
@property (readonly) CGPoint bottomRight;
@property (readonly) NSString* messageString;


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
@property (readonly) NSArray *subFeatures;


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

#if __has_feature(objc_generics)
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary<KeyType, ValueType>
# define CI_ARRAY(ValueType) NSArray <ValueType>
#else
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary
# define CI_ARRAY(ValueType) NSArray
#endif

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

/* name of the filter */
#if TARGET_OS_IPHONE
@property (nonatomic, readonly) NSString *name NS_AVAILABLE_IOS(5_0);
#else
/* On OSX this property is read-write.  This can be useful when
 * using CIFilters with CALayers to construct unique keypaths.
 * For example, to set an attribute of a filter attached to a layer,
 * a path such as "filters.myExposureFilter.inputEV" could be used. 
 * CALayer animations may also access filter attributes via key-paths. */
@property (nonatomic, copy) NSString *name NS_AVAILABLE_MAC(10_5);

/* The 'enabled' property is used only by CoreAnimation and is animatable.
 * In Core Animation, a CIFilter only applied to its input when this 
 * property is set to true. */
@property (getter=isEnabled) BOOL enabled NS_AVAILABLE_MAC(10_5);
#endif


/** Returns an array containing the names of all inputs in the filter. */
@property (nonatomic, readonly) CI_ARRAY(NSString*) *inputKeys;

/** Returns an array containing the names of all outputs in the filter. */
@property (nonatomic, readonly) CI_ARRAY(NSString*) *outputKeys;

/** Sets all inputs to their default values (where default values are defined, other inputs are left as-is). */
- (void)setDefaults;

/** Returns a dictionary containing key/value pairs describing the filter. (see description of keys below) */
@property (nonatomic, readonly) CI_DICTIONARY(NSString*,id) *attributes;


/** Used by CIFilter subclasses to apply the array of argument values 'args' to the kernel function 'k'. The supplied arguments must be type-compatible with the function signature of the kernel.
 
 The key-value pairs defined by 'dict' (if non-nil) are used to control exactly how the kernel is evaluated. Valid keys include:
 kCIApplyOptionExtent: the size of the produced image. Value is a four element NSArray [X Y WIDTH HEIGHT].
 kCIApplyOptionDefinition: the Domain of Definition of the produced image. Value is either a CIFilterShape object, or a four element NSArray defining a rectangle.
 @param  k         CIKernel of the filter
 @param  args      Array of arguments that are applied to the kernel
 @param  options   Array of additional options
*/
- (nullable CIImage *)apply:(CIKernel *)k
				  arguments:(nullable NSArray *)args
			        options:(nullable CI_DICTIONARY(NSString*,id) *)dict NS_AVAILABLE_MAC(10_4);

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
                  withInputParameters:(nullable CI_DICTIONARY(NSString*,id) *)params NS_AVAILABLE(10_10, 8_0);

/** Returns an array containing all published filter names in a category. */
+ (CI_ARRAY(NSString*) *)filterNamesInCategory:(nullable NSString *)category;

/** Returns an array containing all published filter names that belong to all listed categories. */
+ (CI_ARRAY(NSString*) *)filterNamesInCategories:(nullable CI_ARRAY(NSString*) *)categories;


/** Publishes a new filter called 'name'.
 
 The constructor object 'anObject' should implement the filterWithName: method.
 That method will be invoked with the name of the filter to create.
 The class attributes must have a kCIAttributeFilterCategories key associated with a set of categories.
 @param   attributes    Dictionary of the registration attributes of the filter. See below for attribute keys.
*/
+ (void)registerFilterName:(NSString *)name
			   constructor:(id<CIFilterConstructor>)anObject
		   classAttributes:(CI_DICTIONARY(NSString*,id) *)attributes NS_AVAILABLE(10_4, 9_0);

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
 */
+ (NSData*)serializedXMPFromFilters:(CI_ARRAY(CIFilter*) *)filters
                   inputImageExtent:(CGRect)extent
    NS_AVAILABLE(10_9, 6_0);

/* Return an array of CIFilters de-serialized from XMP data.
 */
+ (CI_ARRAY(CIFilter*) *)filterArrayFromSerializedXMP:(NSData *)xmpData
                                      inputImageExtent:(CGRect)extent
                                                 error:(NSError **)outError
    NS_AVAILABLE(10_9, 6_0);

@end

#undef CI_DICTIONARY
#undef CI_ARRAY

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
    __strong void *_state;
}

/* Create a new accumulator object. 
   For pixel format options see CIImage.h.
   The specified color space is used to render the image. 
   If no color space is specified, no color matching is done. */
+ (instancetype)imageAccumulatorWithExtent:(CGRect)extent
                                    format:(CIFormat)format;

+ (instancetype)imageAccumulatorWithExtent:(CGRect)extent
                                    format:(CIFormat)format
                                colorSpace:(CGColorSpaceRef)colorSpace
NS_AVAILABLE(10_7, 9_0);

- (instancetype)initWithExtent:(CGRect)extent format:(CIFormat)format;

- (instancetype)initWithExtent:(CGRect)extent
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


#endif /* COREIMAGEDEFINES_H */
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
#import <CoreImage/CIImageAccumulator.h>
#import <CoreImage/CIFilterConstructor.h>
#import <CoreImage/CIFilterShape.h>
#import <CoreImage/CISampler.h>
#if !TARGET_OS_IPHONE
#import <CoreImage/CIFilterGenerator.h>
#import <CoreImage/CIPlugIn.h>
#import <CoreImage/CIRAWFilter.h>
#endif

#endif /* __OBJC__ */
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

@end

NS_ASSUME_NONNULL_END
// ==========  CoreImage.framework/Headers/CIKernel.h
/* CoreImage - CIKernel.h

   Copyright (c) 2014 Apple, Inc.
   All rights reserved. */

#import <CoreImage/CoreImageDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#if __has_feature(objc_generics)
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary<KeyType, ValueType>
# define CI_ARRAY(ValueType) NSArray <ValueType>
#else
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary
# define CI_ARRAY(ValueType) NSArray
#endif

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
 * General kernels functions are declared akin to this example:
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
+ (nullable CI_ARRAY(CIKernel*) *)kernelsWithString:(NSString *)string  NS_AVAILABLE(10_4, 8_0);

/* The string argument should contain a program with one kernel.
 * On OSX 10.10 and before, this returns a CIKernel object.
 * On OSX after 10.10, this returns a CIKernel, CIColorKernel, or CIWarpKernel object.
 * On iOS this returns a CIKernel, CIColorKernel, or CIWarpKernel object.
 */
+ (nullable instancetype)kernelWithString:(NSString *)string  NS_AVAILABLE(10_10, 8_0);

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
                            arguments:(nullable CI_ARRAY(id) *)args  NS_AVAILABLE(10_11, 8_0);
@end



/*
 * CIColorKernel is an object that encapsulates a Core Image Kernel Language
 * routine that processes only the color information in images.
 *
 * Color kernels functions are declared akin to this example:
 *   kernel vec4 myColorKernel (__sample fore, __sample back, vec4 params)
 *
 * The function must take a __sample argument for each input image.
 * Additional arguments can be of type float, vec2, vec3, vec4, or __color.
 * The destination pixel location is obtained by calling destCoord().
 * The kernel should not call sample(), sampleCoord(), or samplerTransform().
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
+ (nullable instancetype)kernelWithString:(NSString *)string  NS_AVAILABLE(10_10, 8_0);

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
                            arguments:(nullable CI_ARRAY(id) *)args  NS_AVAILABLE(10_11, 8_0);
@end


/*
 * CIWarpKernel is an object that encapsulates a Core Image Kernel Language
 * function that processes only the geometry of an image.
 *
 * Warp kernels functions are declared akin to this example:
 *   kernel vec2 myWarpKernel (vec4 params)
 *
 * Additional arguments can be of type float, vec2, vec3, vec4.
 * The destination pixel location is obtained by calling destCoord().
 * The kernel should not call sample(), sampleCoord(), or samplerTransform().
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
+ (nullable instancetype)kernelWithString:(NSString *)string  NS_AVAILABLE(10_10, 8_0);

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
                            arguments:(nullable CI_ARRAY(id) *)args  NS_AVAILABLE(10_11, 8_0);
@end

#undef CI_DICTIONARY
#undef CI_ARRAY

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
// ==========  CoreImage.framework/Headers/CIDetector.h
/* CoreImage - CIDetector.h

   Copyright (c) 2011 Apple, Inc.
   All rights reserved. */


#import <CoreImage/CoreImageDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#if __has_feature(objc_generics)
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary<KeyType, ValueType>
# define CI_ARRAY(ValueType) NSArray <ValueType>
#else
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary
# define CI_ARRAY(ValueType) NSArray
#endif


@class CIImage;
@class CIContext;
@class CIFeature;


/** Detects features in images.
 
 This class potentially holds onto a lot of state. Hence it may be beneficial from a performance perspective to re-use the same CIDetector instance. Specifying a CIContext when creating a detector may have an impact on performance since this context may be used when analyzing an image.
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
@interface CIDetector : NSObject {}

/** Returns a new detector instance of the given type.
 
 The type is used to specify the usage intent.
 
 The context argument specifies the CIContext to be used to operate on the image. May be nil.
 
 If the input image to -featuresInImage: is the output of a CoreImage operation, it may improve performance to specify the same context that was used to operate on that image.
 
 The detector may do image processing in this context and if the image is on the GPU and the specified context is a GPU context this may avoid additional upload to / download from the GPU. If the input image is on the CPU (or the output from a CPU based context) specifying a GPU based context (or vice versa) may reduce performance.
 
 The options parameter lets you optinally specify a accuracy / performance tradeoff. Can be nil or an empty dictionary. */
+ (CIDetector *)detectorOfType:(NSString*)type
                       context:(nullable CIContext *)context
                       options:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_AVAILABLE(10_7, 5_0);

/** Returns an array of CIFeature instances in the given image.
 The array is sorted by confidence, highest confidence first. */
- (CI_ARRAY(CIFeature*) *)featuresInImage:(CIImage *)image
    NS_AVAILABLE(10_7, 5_0);

/** Returns an array of CIFeature instances in the given image.
 The array is sorted by confidence, highest confidence first. 
 The options dictionary can contain a CIDetectorImageOrientation key value. */
- (CI_ARRAY(CIFeature*) *)featuresInImage:(CIImage *)image
                                  options:(nullable CI_DICTIONARY(NSString*,id) *)options
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



#undef CI_DICTIONARY
#undef CI_ARRAY

NS_ASSUME_NONNULL_END
// ==========  CoreImage.framework/Headers/CIImage.h
/* 
   CoreImage - CIImage.h

   Copyright (c) 2015 Apple, Inc.
   All rights reserved. 
*/

#import <Foundation/Foundation.h>
#import <CoreImage/CoreImageDefines.h>
#import <CoreVideo/CoreVideo.h>
#if !TARGET_OS_IPHONE
#import <IOSurface/IOSurface.h>
#endif

NS_ASSUME_NONNULL_BEGIN

#if __has_feature(objc_generics)
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary<KeyType, ValueType>
# define CI_ARRAY(ValueType) NSArray <ValueType>
#else
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary
# define CI_ARRAY(ValueType) NSArray
#endif

@class CIContext, CIFilterShape, CIColor, CIFilter;

@protocol MTLTexture;

NS_CLASS_AVAILABLE(10_4, 5_0)
@interface CIImage : NSObject <NSSecureCoding, NSCopying>
{
#if !TARGET_OS_IPHONE
    void *_state;
#endif
	void *_priv;
}

/* Pixel formats. */

typedef int CIFormat;

CORE_IMAGE_EXPORT CIFormat kCIFormatARGB8 NS_AVAILABLE(10_4, 6_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatBGRA8;
CORE_IMAGE_EXPORT CIFormat kCIFormatRGBA8;
CORE_IMAGE_EXPORT CIFormat kCIFormatABGR8 NS_AVAILABLE(10_11, 9_0);

CORE_IMAGE_EXPORT CIFormat kCIFormatRGBA16 NS_AVAILABLE_MAC(10_4);
CORE_IMAGE_EXPORT CIFormat kCIFormatRGBAf NS_AVAILABLE(10_4, 7_0);

/* RGBA values that are IEEE 754-2008 half float compliant. */
CORE_IMAGE_EXPORT CIFormat kCIFormatRGBAh NS_AVAILABLE(10_4, 6_0);


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


/* Image options dictionary keys. 
   These keys can be passed with appropriate values to the methods:
     + [CIImage imageWith... options:]
     - [CIImage initWith... options:]
   to modify the default behavior of how CIImages are created.
*/

/* A CGColorSpaceRef defining the color space of the image. This value 
 * overrides the image's implicit color space. 
 * If [NSNull null] then dont color manage the image. */
CORE_IMAGE_EXPORT NSString * const kCIImageColorSpace;


/* A NSDictionary of metadata properties to pass to CIImage initialization methods.
 * When used with imageWithCGImage:options:, initWithCGImage:options:, imageWithData:options:, initWithData:options:
 *   If this option is not specified, the properties will be set to CGImageSourceCopyPropertiesAtIndex.
 *   If this option is [NSNull null], the properties will be set to nil.
 */
CORE_IMAGE_EXPORT NSString * const kCIImageProperties NS_AVAILABLE(10_8, 5_0);

CORE_IMAGE_EXPORT NSString * const kCIImageTextureTarget NS_AVAILABLE_MAC(10_9);
CORE_IMAGE_EXPORT NSString * const kCIImageTextureFormat NS_AVAILABLE_MAC(10_9);


/* Creates a new image from the contents of 'image'. */
+ (CIImage *)imageWithCGImage:(CGImageRef)image;
+ (CIImage *)imageWithCGImage:(CGImageRef)image
                      options:(nullable CI_DICTIONARY(NSString*,id) *)options;

/* Creates a new image from the contents of 'layer'. */
+ (CIImage *)imageWithCGLayer:(CGLayerRef)layer NS_DEPRECATED_MAC(10_4,10_11);
+ (CIImage *)imageWithCGLayer:(CGLayerRef)layer
                      options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_DEPRECATED_MAC(10_4,10_11);

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
                   colorSpace:(nullable CGColorSpaceRef)colorSpace NS_AVAILABLE(10_4, 6_0);

/* In the options dictionary you can specify the following:
 * - kCIImageColorSpace which should be a CGColorSpaceRef or [NSNull null]
 * - kCIImageTextureTarget which should be a NSNumber with either GL_TEXTURE_2D or GL_TEXTURE_RECTANGLE_ARB.
 * - kCIImageTextureFormat which should be a NSNumber with a CIFormat value
 */
+ (CIImage *)imageWithTexture:(unsigned int)name
                         size:(CGSize)size
					  flipped:(BOOL)flipped
                      options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE_MAC(10_9);

+ (CIImage *)imageWithMTLTexture:(id<MTLTexture>)texture
                         options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE(10_11, 9_0);

+ (nullable CIImage *)imageWithContentsOfURL:(NSURL *)url;
+ (nullable CIImage *)imageWithContentsOfURL:(NSURL *)url
                                     options:(nullable CI_DICTIONARY(NSString*,id) *)options;

+ (nullable CIImage *)imageWithData:(NSData *)data;
+ (nullable CIImage *)imageWithData:(NSData *)data
                            options:(nullable CI_DICTIONARY(NSString*,id) *)options;

/* Creates a new image whose data is from the contents of a CVImageBuffer. */
+ (CIImage *)imageWithCVImageBuffer:(CVImageBufferRef)imageBuffer NS_AVAILABLE(10_4, 9_0);
+ (CIImage *)imageWithCVImageBuffer:(CVImageBufferRef)imageBuffer
                            options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE(10_4, 9_0);

/* Creates a new image whose data is from the contents of a CVPixelBufferRef. */
+ (CIImage *)imageWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer NS_AVAILABLE(10_11, 5_0);
+ (CIImage *)imageWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer
                            options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE(10_11, 5_0);

/* Creates a new image from the contents of an IOSurface. */
#if !TARGET_OS_IPHONE
+ (CIImage *)imageWithIOSurface:(IOSurfaceRef)surface NS_AVAILABLE_MAC(10_6);
+ (CIImage *)imageWithIOSurface:(IOSurfaceRef)surface
                        options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE_MAC(10_6);
#endif

/* Return or initialize a new image with an infinite amount of the color
 * 'color'. */
+ (CIImage *)imageWithColor:(CIColor *)color;

/* Create an empty Image. */
+ (CIImage *)emptyImage;

/* Initializers. */

- (instancetype)initWithCGImage:(CGImageRef)image;
- (instancetype)initWithCGImage:(CGImageRef)image
                        options:(nullable CI_DICTIONARY(NSString*,id) *)options;

- (instancetype)initWithCGLayer:(CGLayerRef)layer
    NS_DEPRECATED_MAC(10_4,10_11,"Use initWithCGImage: instead.");
- (instancetype)initWithCGLayer:(CGLayerRef)layer
                        options:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_DEPRECATED_MAC(10_4,10_11,"Use initWithCGImage:options instead.");

- (nullable instancetype)initWithData:(NSData *)data;
- (nullable instancetype)initWithData:(NSData *)data
                              options:(nullable CI_DICTIONARY(NSString*,id) *)options;

- (instancetype)initWithBitmapData:(NSData *)data
                       bytesPerRow:(size_t)bytesPerRow
                              size:(CGSize)size
                            format:(CIFormat)format
                        colorSpace:(nullable CGColorSpaceRef)colorSpace;

- (instancetype)initWithTexture:(unsigned int)name
                           size:(CGSize)size
                        flipped:(BOOL)flipped
                     colorSpace:(nullable CGColorSpaceRef)colorSpace NS_AVAILABLE(10_4, 6_0);

- (instancetype)initWithTexture:(unsigned int)name
                           size:(CGSize)size
                        flipped:(BOOL)flipped
                        options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE_MAC(10_9);

- (instancetype)initWithMTLTexture:(id<MTLTexture>)texture
                           options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE(10_11, 9_0);

- (nullable instancetype)initWithContentsOfURL:(NSURL *)url;
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url
                                       options:(nullable CI_DICTIONARY(NSString*,id) *)options;

#if !TARGET_OS_IPHONE
- (instancetype)initWithIOSurface:(IOSurfaceRef)surface NS_AVAILABLE_MAC(10_6);

- (instancetype)initWithIOSurface:(IOSurfaceRef)surface
                          options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE_MAC(10_6);

- (instancetype)initWithIOSurface:(IOSurfaceRef)surface
                            plane:(size_t)plane
                           format:(CIFormat)format
                          options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_DEPRECATED_MAC(10_9,10_11);
#endif

- (instancetype)initWithCVImageBuffer:(CVImageBufferRef)imageBuffer NS_AVAILABLE(10_4, 9_0);
- (instancetype)initWithCVImageBuffer:(CVImageBufferRef)imageBuffer
                              options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE(10_4, 9_0);

- (instancetype)initWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer NS_AVAILABLE(10_11, 5_0);
- (instancetype)initWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer
                              options:(nullable CI_DICTIONARY(NSString*,id) *)options NS_AVAILABLE(10_11, 5_0);

- (instancetype)initWithColor:(CIColor *)color;

/* Returns a new image representing the original image with the transform
 * 'matrix' appended to it. */
- (CIImage *)imageByApplyingTransform:(CGAffineTransform)matrix;

/* Returns a new image representing the original image with a transform
 * appied to it based on an orientation value.
 * Orientation values from 1 to 8 as defined in the TIFF spec are supported.
 * Returns original image if the image is of infinite extent. */
- (CIImage *)imageByApplyingOrientation:(int)orientation NS_AVAILABLE(10_10, 8_0);

/* Returns a CGAffineTransform for an orientation value that can be appied to an image.
 * Orientation values from 1 to 8 as defined in the TIFF spec are supported.
 * Returns CGAffineTransformIdentity if the image is of infinite extent.*/
- (CGAffineTransform)imageTransformForOrientation:(int)orientation NS_AVAILABLE(10_10, 8_0);

/* Return a new image formed by compositing the receiver image over 'dest'. */
- (CIImage *)imageByCompositingOverImage:(CIImage *)dest NS_AVAILABLE(10_4, 8_0);

/* Return a new image cropped to a rectangle. */
- (CIImage *)imageByCroppingToRect:(CGRect)rect;

/* Return a new infinte image by replicating the pixels of the receiver image's extent. */
- (CIImage *)imageByClampingToExtent NS_AVAILABLE(10_10, 8_0);

/* A convenience method for applying a filter to an image.
 * The method returns outputImage of the filter after setting the
 * filter's inputImage to the method receiver and other parameters
 * from from the key/value pairs of 'params'. */
- (CIImage *)imageByApplyingFilter:(NSString *)filterName
               withInputParameters:(nullable CI_DICTIONARY(NSString*,id) *)params NS_AVAILABLE(10_10, 8_0);


/* Return a rect the defines the bounds of non-(0,0,0,0) pixels */
@property (NS_NONATOMIC_IOSONLY, readonly) CGRect extent;

/* Returns the metadata properties of an image. If the image is the
 * output of one or more CIFilters, then the metadata of the root inputImage
 * will be returned. See also kCIImageProperties. */
@property (atomic, readonly) CI_DICTIONARY(NSString*,id) *properties NS_AVAILABLE(10_8, 5_0);

/* Return the Domain of Definition of the image. */
@property (atomic, readonly) CIFilterShape *definition NS_AVAILABLE_MAC(10_4);

/* Returns the URL of the image when the image was created using the imageWithContentsOfURL APIs.
 * This method will return nil, if the URL cannot be determined. */
@property (atomic, readonly, nullable) NSURL *url NS_AVAILABLE(10_4, 9_0);

/* Returns if possible the color space of the image it was defined in.
 * This method will return nil, if the color space cannot be determined. */
@property (atomic, readonly, nullable) CGColorSpaceRef colorSpace NS_AVAILABLE(10_4, 9_0) CF_RETURNS_NOT_RETAINED;

/* Returns the rectangle of 'image' that is required to render the
 * rectangle 'rect' of the receiver.  This may return a null rect. */
- (CGRect)regionOfInterestForImage:(CIImage *)image
                            inRect:(CGRect)rect NS_AVAILABLE(10_11, 6_0);

@end


@interface CIImage (AutoAdjustment)

/* Image auto adjustment keys. */

/* These are the options dictionary keys which can be specified when calling 
 * the autoAdjustmentFiltersWithOptions: method.
 */

/* If CFBoolean value is false then dont attempt to apply enhancement filters.
 * If not specified, the option is assumed to be present and true.
 */
CORE_IMAGE_EXPORT NSString * const kCIImageAutoAdjustEnhance NS_AVAILABLE(10_8, 5_0);

/* If CFBoolean value is false then dont attempt to apply red eye filter.
 * If not specified, the option is assumed to be present and true.
 */
CORE_IMAGE_EXPORT NSString * const kCIImageAutoAdjustRedEye NS_AVAILABLE(10_8, 5_0);

/* If value is an array of detected CIFeatures, then use these features
 * to determine the AutoAdjustEnhance and or AutoAdjustRedEye filters.
 * If not specified, receiver will call CIDetector.
 */
CORE_IMAGE_EXPORT NSString * const kCIImageAutoAdjustFeatures NS_AVAILABLE(10_8, 5_0);

/* If CFBoolean value is false then don't attempt to apply crop filter.
 * If not specified, the option is assumed to be present and false.
 */
CORE_IMAGE_EXPORT NSString * const kCIImageAutoAdjustCrop NS_AVAILABLE(10_10, 8_0);

/* If CFBoolean value is false then don't attempt to apply auto-level.
 * If not specified, the option is assumed to be present and false.
 */
CORE_IMAGE_EXPORT NSString * const kCIImageAutoAdjustLevel NS_AVAILABLE(10_10, 8_0);


/* Return an array of filters to apply to an image to improve its
 * skin tones, saturation, contrast, shadows and repair red-eyes or LED-eyes.
 *
 * The options dictionary can contain a CIDetectorImageOrientation key value. 
 * The value for this key is an integer NSNumber from 1..8 such as that
 * found in kCGImagePropertyOrientation.  If present, the adjustment will be done
 * based on that orientation but any coordinates in the returned filters will
 * still be based on those of the sender image.
 */
- (CI_ARRAY(CIFilter *) *)autoAdjustmentFiltersWithOptions:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_AVAILABLE(10_8, 5_0);

@end

#undef CI_DICTIONARY
#undef CI_ARRAY

NS_ASSUME_NONNULL_END
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

#if __has_feature(objc_generics)
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary<KeyType, ValueType>
# define CI_ARRAY(ValueType) NSArray <ValueType>
#else
# define CI_DICTIONARY(KeyType, ValueType) NSDictionary
# define CI_ARRAY(ValueType) NSArray
#endif


@interface CIImage (CIImageProvider)

/* Create a new CIImage lazily populated with with data provided by 'p' when
 * required. 'p' is retained until the image is deallocated. */
+ (CIImage *)imageWithImageProvider:(id)p
							   size:(size_t)width
                                   :(size_t)height
							 format:(CIFormat)f
						 colorSpace:(nullable CGColorSpaceRef)cs
                            options:(nullable CI_DICTIONARY(NSString*,id) *)options
    NS_AVAILABLE(10_4, 9_0);

- (instancetype)initWithImageProvider:(id)p
                                 size:(size_t)width
                                     :(size_t)height
                               format:(CIFormat)f
                           colorSpace:(nullable CGColorSpaceRef)cs
                              options:(nullable CI_DICTIONARY(NSString*,id) *)options
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

#undef CI_DICTIONARY
#undef CI_ARRAY

NS_ASSUME_NONNULL_END
