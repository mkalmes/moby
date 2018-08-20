// ==========  MetalPerformanceShaders.framework/Headers/MPSKernel.h
/*!
 *  @header MPSKernel.h
 *  @framework MetalPerformanceShaders.framework
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *
 *  @discussion  MPSKernel objects encode tuned image processing operations into a MTLCommandBuffer.
 */


#ifndef MPS_MPSKernel_h
#define MPS_MPSKernel_h

#include <MetalPerformanceShaders/MPSTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  MPSSupportsMTLDevice
 *  @abstract   Determine whether a MetalPerformanceShaders.framework  supports a MTLDevice.
 *  @discussion Use this function to determine whether a MTLDevice can be used with interfaces in MetalPerformanceShaders.framework.
 *  @param      device          A valid MTLDevice
 *  @return     YES             The device is supported.
 *              NO              The device is not supported
 */
BOOL    MPSSupportsMTLDevice( __nullable id <MTLDevice> device );


/*!
 *  @class      MPSKernel
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSKernel class is the base class for all MPS objects.  It defines a standard interface for
 *              MPS kernels.   You should not use the MPSKernel class directly. Instead, a  number of MPSKernel 
 *              subclasses are available in MetalPerformanceShaders.framework that define specific high-performance
 *              image processing operations.
 *
 *              The basic sequence for applying a MPSKernel to an image is as follows:
 *
 *              1.  Create a MPSKernel corresponding to the operation you wish to perform:
 *                  @code
 *                  MPSImageSobel *sobel = [[MPSImageSobel alloc] initWithDevice: mtlDevice];
 *                  @endcode
 *
 *              2.  Encode the filter into a command buffer:
 *                  @code
 *                  sobel.offset = ...;
 *                  sobel.clipRect = ...;
 *                  sobel.options = ...;
 *                  [sobel encodeToCommandBuffer: commandBuffer
 *                                 sourceTexture: inputImage
 *                            destinationTexture: resultImage ];
 *                  
 *                  if( returnVal < 0 )
 *                      MyShowError( returnVal );
 *                  @endcode
 *                  Encoding the kernel merely encodes the operation into a MTLCommandBuffer. It does not modify any pixels, yet.
 *                  All MPSKernel state has been copied to the command buffer. MPSKernels may be reused.  If the texture was previously
 *                  operated on by another command encoder (e.g. MTLRenderCommandEncoder), you should call -endEncoding on the other
 *                  encoder before encoding the filter.
 *
 *                  Some MPS filters work in place (inputImage = resultImage) even in situations where Metal might not
 *                  normally allow in place operation on textures. If in-place operation is desired, you may attempt to call
 *                  [MPSKernel encodeKernelInPlace...]. If the operation can not be completed in place, then
 *                  NO will be returned and you will have to create a new result texture and try again. To make an in-place
 *                  image filter reliable, pass a fallback MPSCopyAllocator to the method to create a new texture to write
 *                  to in the event that a filter can not operate in place.
 *
 *                  (Repeat steps 2 for more filters, as desired.)
 *
 *                      It should be self evident that step 2 may not be thread safe. That is, you can not have
 *                      multiple threads manipulating the same properties on the same MPSKernel object at the
 *                      same time and achieve coherent output. In common usage, the MPSKernel properties don't
 *                      often need to be changed from their default values, but if you need to apply the same
 *                      filter to multiple images on multiple threads with cropping / tiling, make additional
 *                      MPSKernel objects per thread. They are cheap. You can use multiple MPSKernel objects on
 *                      multiple threads, as long as only one thread is operating on any particular MPSKernel
 *                      object at a time.
 *
 *              3.  After encoding any additional work to the command buffer using other encoders, submit the MTLCommandBuffer
 *                  to your MTLCommandQueue, using:
 *                  @code
 *                  [mtlCommandBuffer commit];
 *                  @endcode
 */

NS_CLASS_AVAILABLE( NA, 9_0  )
@interface MPSKernel  : NSObject <NSCopying>

/****************
 *  Properties  *
 ****************/

/*! @property   options
 *  @abstract   The set of options used to run the kernel.
 *  @ref        subsubsection_options
 */
@property (readwrite, nonatomic) MPSKernelOptions                   options;

/*! @property device
 *  @abstract  The device on which the kernel will be used
 */
@property (readonly, retain, nonatomic, nonnull)  id <MTLDevice>    device;

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (copy, atomic, nullable)  NSString *                      label;

/*********************
 *  Object creation  *
 *********************/


/*!
 *  @abstract   Standard init with default properties per filter type
 *  @param      device      The device that the filter will be used on. May not be NULL.
 *  @result     a pointer to the newly initialized object. This will fail, returning
 *              nil if the device is not supported. Devices must be 
 *              MTLFeatureSet_iOS_GPUFamily2_v1 or later.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_DESIGNATED_INITIALIZER;


/*!
 *  @abstract   Make a copy of this MPSKernel for a new device
 *  @discussion -copyWithZone: will call this API to make a copy of the
 *              MPSKernel on the same device.  This interface may also be
 *              called directly to make a copy of the MPSKernel on a new
 *              device. Typically, the same MPSKernels should not be used
 *              to encode kernels on multiple command buffers from multiple
 *              threads. Many MPSKernels have mutable properties that might 
 *              be changed by the other thread while this one is trying to 
 *              encode. If you need to use a MPSKernel from multiple threads
 *              make a copy of it for each additional thread using -copyWithZone:
 *              or -copyWithZone:device:
 *  @param      zone        The NSZone in which to allocate the object
 *  @param      device      The device for the new MPSKernel. If nil, then use
 *                          self.device.
 *  @result     a pointer to a copy of this MPSKernel. This will fail, returning
 *              nil if the device is not supported. Devices must be
 *              MTLFeatureSet_iOS_GPUFamily2_v1 or later.
 */
- (nonnull instancetype) copyWithZone:(nullable NSZone *)zone
                               device:(nullable id <MTLDevice>) device;

@end


#ifdef __cplusplus
    }       /* extern "C" */
#endif

#endif  /* MPS_MPSKernel_h */
// ==========  MetalPerformanceShaders.framework/Headers/MPSImageThreshold.h
/*!
 *  @header MPSImageThreshold.h
 *  @framework MetalPerformanceShaders
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract Metal Image thresholding filters
 */

#ifndef MPS_MPSImageThreshold_h
#define MPS_MPSImageThreshold_h

#include <MetalPerformanceShaders/MPSImageKernel.h>

/*!
 *  @class      MPSImageThresholdBinary
 *  @discussion The MIThreshold filter applies a fixed-level threshold to each pixel in the image.
 *              The threshold functions convert a single channel image to a binary image.
 *              If the input image is not a single channel image, convert the inputimage to a single channel
 *              luminance image using the linearGrayColorTransform and then apply the threshold.
 *              The ThresholdBinary function is:
 *                  destinationPixelValue = sourcePixelValue > thresholdValue ? maximumValue : 0
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageThresholdBinary : MPSUnaryImageKernel

/*!
 *  @abstract   initialize a MPSImageThresholdBinary filter
 *  @param      device          The device the filter will run on
 *  @param      thresholdValue  The threshold value to use
 *  @param      maximumValue    The maximum value to use
 *  @param      transform       This matrix is an array of 3 floats.
 *                              The default if no transform is specifed is BT.601/JPEG: {0.299f, 0.587f, 0.114f};
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        thresholdValue: (float)thresholdValue
                          maximumValue: (float)maximumValue
              linearGrayColorTransform: (nullable const float *)transform       NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:thresholdValue:maximumValue:linearGrayColorTransform: instead */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device            NS_UNAVAILABLE;

/*! @property thresholdValue
 *  @discussion The threshold value used to init the threshold filter
 */
@property (readonly, nonatomic) float   thresholdValue;

/*! @property maximumValue
 *  @discussion The maximum value used to init the threshold filter
 */
@property (readonly, nonatomic) float   maximumValue;

/*! @property transform
 *  @discussion The color transform used to init the threshold filter
 */
@property (readonly, nonatomic, nonnull) const float *transform;


@end  /* MPSImageThresholdBinary */

/*!
 *  @class      MPSImageThresholdBinaryInverse
 *  @discussion The MPSImageThresholdBinaryInverse filter applies a fixed-level threshold to each pixel in the image.
 *              The threshold functions convert a single channel image to a binary image.
 *              If the input image is not a single channel image, convert the inputimage to a single channel
 *              luminance image using the linearGrayColorTransform and then apply the threshold.
 *              The ThresholdBinaryInverse function is:
 *                  destinationPixelValue = sourcePixelValue > thresholdValue ? 0 : maximumValue
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageThresholdBinaryInverse : MPSUnaryImageKernel

/*!
 *  @abstract   initialize a MPSImageThresholdBinaryInverse filter
 *  @param      device          The device the filter will run on
 *  @param      thresholdValue  The threshold value to use
 *  @param      maximumValue    The maximum value to use
 *  @param      transform       This matrix is an array of 3 floats.
 *                              The default if no transform is specifed is BT.601/JPEG: {0.299f, 0.587f, 0.114f};
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        thresholdValue: (float)thresholdValue
                          maximumValue: (float)maximumValue
              linearGrayColorTransform: (nullable const float *)transform       NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:thresholdValue:maximumValue:linearGrayColorTransform: instead */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device            NS_UNAVAILABLE;

/*! @property thresholdValue
 *  @discussion The threshold value used to init the threshold filter
 */
@property (readonly, nonatomic) float   thresholdValue;

/*! @property maximumValue
 *  @discussion The maximum value used to init the threshold filter
 */
@property (readonly, nonatomic) float   maximumValue;

/*! @property transform
 *  @discussion The color transform used to init the threshold filter
 */
@property (readonly, nonatomic, nonnull) const float *transform;

@end  /* MPSImageThresholdBinaryInverse */

/*!
 *  @class      MPSImageThresholdTruncate
 *  @discussion The MPSImageThresholdTruncate filter applies a fixed-level threshold to each pixel in the image:
 *              The threshold functions convert a single channel image to a binary image.
 *              If the input image is not a single channel image, convert the inputimage to a single channel
 *              luminance image using the linearGrayColorTransform and then apply the threshold.
 *              The ThresholdTruncate function is:
 *                  destinationPixelValue = sourcePixelValue > thresholdValue ? thresholdValue : sourcePixelValue
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageThresholdTruncate : MPSUnaryImageKernel

/*! 
 *  @abstract   initialize a MPSImageThresholdTruncate filter
 *  @param      device          The device the filter will run on
 *  @param      thresholdValue The threshold value to use
 *  @param      transform       This matrix is an array of 3 floats.
 *                              The default if no transform is specifed is BT.601/JPEG: {0.299f, 0.587f, 0.114f};
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        thresholdValue: (float)thresholdValue
              linearGrayColorTransform: (nullable const float *)transform       NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:thresholdValue:linearGrayColorTransform: instead */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device            NS_UNAVAILABLE;

/*! @property thresholdValue
 *  @discussion The threshold value used to init the threshold filter
 */
@property (readonly, nonatomic) float   thresholdValue;

/*! @property transform
 *  @discussion The color transform used to init the threshold filter
 */
@property (readonly, nonatomic, nonnull) const float *transform;

@end  /* MPSImageThresholdTruncate */


/*!
 *  @class      MPSImageThresholdToZero
 *  @discussion The MPSImageThresholdToZero filter applies a fixed-level threshold to each pixel in the image.
 *              The threshold functions convert a single channel image to a binary image.
 *              If the input image is not a single channel image, convert the inputimage to a single channel
 *              luminance image using the linearGrayColorTransform and then apply the threshold.
 *              The ThresholdToZero function is:
 *                  destinationPixelValue = sourcePixelValue > thresholdValue ? sourcePixelValue : 0
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageThresholdToZero : MPSUnaryImageKernel

/*!
 *  @abstract   initialize a MPSImageThresholdToZero filter
 *  @param      device          The device the filter will run on
 *  @param      thresholdValue  The threshold value to use
 *  @param      transform       This matrix is an array of 3 floats.
 *                              The default if no transform is specifed is BT.601/JPEG: {0.299f, 0.587f, 0.114f};
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        thresholdValue: (float)thresholdValue
              linearGrayColorTransform: (nullable const float *)transform       NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:thresholdValue:linearGrayColorTransform: instead */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device            NS_UNAVAILABLE;

/*! @property thresholdValue
 *  @discussion The threshold value used to init the threshold filter
 */
@property (readonly, nonatomic) float   thresholdValue;

/*! @property transform
 *  @discussion The color transform used to init the threshold filter
 */
@property (readonly, nonatomic, nonnull) const float *transform;

@end  /* MPSImageThresholdToZero */

/*!
 *  @class      MPSImageThresholdToZeroInverse
 *  @discussion The MPSImageThresholdToZeroInverse filter applies a fixed-level threshold to each pixel in the image.
 *              The threshold functions convert a single channel image to a binary image.
 *              If the input image is not a single channel image, convert the inputimage to a single channel
 *              luminance image using the linearGrayColorTransform and then apply the threshold.
 *              The ThresholdToZeroINverse function is:
 *                  destinationPixelValue = sourcePixelValue > thresholdValue ? 0 : sourcePixelValue
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageThresholdToZeroInverse : MPSUnaryImageKernel

/*!
 *  @abstract  initialize a MPSImageThresholdToZeroInverse filter
 *  @param      device          The device the filter will run on
 *  @param      thresholdValue The threshold value to use
 *  @param      transform       This matrix is an array of 3 floats.
 *                              The default if no transform is specifed is BT.601/JPEG: {0.299f, 0.587f, 0.114f};
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        thresholdValue: (float)thresholdValue
              linearGrayColorTransform: (nullable const float *)transform       NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:thresholdValue:linearGrayColorTransform: instead */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device            NS_UNAVAILABLE;

/*! @property thresholdValue
 *  @discussion The threshold value used to init the threshold filter
 */
@property (readonly, nonatomic) float   thresholdValue;

/*! @property transform
 *  @discussion The color transform used to init the threshold filter
 */
@property (readonly, nonatomic, nonnull) const float *transform;

@end  /* MPSImageThresholdToZeroInverse */

#endif  /* MPS_MSImageThreshold_h */
// ==========  MetalPerformanceShaders.framework/Headers/MetalPerformanceShaders.h
/*!
 *  @header MetalPerformanceShaders.h
 *  @framework MetalPerformanceShaders
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 */

#import <MetalPerformanceShaders/MPSImageConvolution.h>
#import <MetalPerformanceShaders/MPSImageHistogram.h>
#import <MetalPerformanceShaders/MPSImageIntegral.h>
#import <MetalPerformanceShaders/MPSImageMedian.h>
#import <MetalPerformanceShaders/MPSImageMorphology.h>
#import <MetalPerformanceShaders/MPSImageResampling.h>
#import <MetalPerformanceShaders/MPSImageThreshold.h>
#import <MetalPerformanceShaders/MPSImageTranspose.h>


//
//  These headers contain doxygen formatted documentation. They are human readable as is,
//  but can be processed as such to make something a bit nicer looking.  Our version of
//  the doxygen PDF output may be found in MetalPerformanceShaders.framework/Documentation:
//
//      open `xcrun --show-sdk-path -sdk iphoneos9.0`/System/Library/Frameworks/MetalPerformanceShaders.framework/Documentation/MetalPerformanceShaders.pdf
//
//  Associated man pages are installed in the SDKROOT.
//
//      man -M `xcrun --show-sdk-path -sdk iphoneos9.0`/usr/share/man  MPSKernel
//

/*! @mainpage Metal Shaders - High Performance Kernels on Metal
 *  @section  section_introduction  Introduction
 *
 *  MetalPerformanceShaders.framework is a framework of highly optimized compute and graphics shaders that are
 *  designed to integrate easily and efficiently into your Metal application.  These data-parallel 
 *  primitives are specially tuned to take advantage of the unique hardware characteristics of each
 *  iOS GPUs to ensure optimal performance. Applications adopting MetalPerformanceShaders can be sure of achieving 
 *  optimal performance without needing to update their own hand-written shaders for each new iOS GPU 
 *  generation. MetalPerformanceShaders can be used along with the application's existing Metal resources (such as 
 *  the MTLCommandBuffer, MTLBuffer and MTLTexture objects) and shaders.
 *
 *  In iOS 9, MetalPerformanceShaders.framework provides a series of commonly-used image processing primitives for 
 *  image effects on Metal textures.
 *
 *  @section section_discussion     The MPSKernel
 *
 *  The MPSKernel is the base class for all MPS kernels. It defines baseline behavior for all MPS 
 *  kernels, declaring the device to run the kernel on, some debugging options and a user-friendly
 *  label, should one be required. From this are derived the MPSUnaryImageKernel and MPSBinaryImageKernel
 *  sub-classes which define shared behavior for most image processing kernels (filters) such as
 *  edging modes, clipping and tiling support for image operations that consume one or two source textures.
 *  Neither these or the MPSKernel are typically be used directly. They just provide API abstraction
 *  and in some cases may allow some level of polymorphic manipulation of MPS image kernel objects.
 *
 *  Subclasses of the MPSUnaryImageKernel and MPSBinaryImageKernel provide specialized -init and -encode 
 *  methods to encode various image processing primitives into your MTLCommandBuffer, and may also
 *  provide additional configurable properties on their own. Many such image filters are available:
 *  There are convolutions (generic, box, Sobel, and Gaussian) to do edge detection, sharpening and 
 *  blurring, morphological operators -- Min, Max, Dilate and Erode -- and histogram operations. 
 *  In addition, there are median, resampling filters and others. All of these run on the GPU directly 
 *  on MTLTextures and MTLBuffers.
 *
 *  As the MPSKernel/MPSUnaryImageKernel/MPSBinaryImageKernel classes serve to unify a diversity of image
 *  operations into a simple consistent interface and calling sequence to apply image filters, 
 *  subclasses implement details that diverge from the norm. For example, some filters may take a small 
 *  set of parameters (e.g. a convolution kernel) to govern how they function. However, the overall 
 *  sequence for using MPSKernel subclasses remains the same:
 *
 *  -#  Allocate the usual Metal objects: MTLDevice, MTLCommandQueue, and MTLCommandBuffer 
 *      to drive a Metal compute pipeline. If your application already uses Metal, chances are you 
 *      have most of these things already. MPS will fit right in to this workflow. It can 
 *      encode onto MTLCommandBuffers that you have already written to, using a MTLComputeCommandEncoder 
 *      that you have previously used.
 *
 *  -#  Create an appropriate MPSKernel object. For example, if you want to do a Gaussian blur, make
 *      a MPSImageGaussianBlur object.  MPSKernel objects are generally light weight but can be reused
 *      to save some setup time. They can not be used by multiple threads concurrently, so if you
 *      are using Metal from many threads concurrently, make extra MPSKernel objects.
 *
 *  -#  Call [MPSKernelSubclass  encodeToCommandBuffer:...]. Parameters for other -encodeKernel calls
 *      vary by filter type, but operate similarly. They create a MTLCommandEncoder, write commands to 
 *      run the filter into the MTLCommandBuffer and then end the MTLCommandEncoder.  This means
 *      you must call -endEncoding on your current MTLCommandEncoder before calling a MPSKernel encode
 *      method. You can at this point release the MPSKernel or keep it around to use again to save
 *      some setup cost.
 *
 *  -#  If you wish to encode futher commands of your own on the MTLCommandBuffer, you must
 *      create a new MTLCommandEncoder to do so.  
 *
 *  -#  (Standard Metal) When you are done with the MTLCommandBuffer, submit it to the device using
 *      typical Metal commands, such as [MTLCommandBuffer commit]. The MPS filter will begin
 *      running on the GPU. You can either use [MTLCommandBuffer waitUntilCompleted] or
 *      [MTLCommandBuffer addCompletedHandler:] to be notified when the work is done.
 *
 *  Each MPSKernel is allocated against a particular MTLDevice. A single filter may not be used with
 *  multiple MTLDevices. (You will need to make multiple MPSKernels for that.) This is necessary because
 *  the [MPSKernel initWithDevice:...] methods sometimes allocate MTLBuffers and MTLTextures to hold
 *  data passed in as parameters to the -init method and a MTLDevice is required to make those. MPSKernels
 *  provide a copy method that allow them to be copied for a new device.
 *
 *  MPSKernel objects are not entirely thread safe. While they may be used in a multithreaded context,
 *  you should not attempt to have multiple MPSKernel objects writing to the same MTLCommandBuffer at
 *  the same time. They share restrictions with the MTLCommandEncoder in this regard. In limited
 *  circumstances, the same MPSKernel can be used to write to multiple MTLCommandBuffers concurrently.
 *  However, that only works if the MPSKernel is treated as an immutable object. That is, if MPSKernel
 *  subclass properties of a shared filter are changed, then the change can be reflected on the other
 *  thread while the other thread is encoding its work, leading to undefined behavior. It is generally
 *  safest to just make copies of MPSKernel objects, one for each thread.
 *
 *  For more information, please see MPSTypes.h.
 *
 *  @subsection subsection_properties  MPS{Unary/Binary}ImageKernel properties
 *  The MPS{Unary/Binary}ImageKernel base classes define several properties common to all MPSKernels:
 *
 *  @subsubsection  subsubsection_clipRect  MPSKernel clipRect
 *  The clipRect property, common to MPSKernel sublcasses that write to a destination texture, describes
 *  the sub-rectangle of the destination texture overwritten by the filter. If the clipRect is larger than
 *  the destination texture, the intersection between the clipRect and destination texture bounds will be used.
 *  The clipRect may be used to avoid doing work to obscured regions of the destination image, or to
 *  manage tiling and to limit operations to parts of an image if for example, the user drew a rectangle
 *  on the screen and asked you to just apply the filter there.
 *
 *      extern MTLRegion MPSRectNoClip; //Pass this rectangle to fill the entire destination texture.
 *
 *  @subsubsection  subsubsection_MPSoffset  MPSOffset
 *  The offset (or primaryOffset or secondaryOffset) property, common to MPSKernel subclasses that 
 *  use a source texture from which pixel data is read, describes the positioning of the source image
 *  relative to the result texture. A offset of {0,0,0} indicates that the top left pixel of the source
 *  texture is the center pixel used to  create the top left corner of the destination texture clipRect.
 *  An offset of {1,2,0} positions the top left corner of the clipRect at {x=1, y=2, z=0} of the source
 *  image. The offset is the position of the top left corner of the clipRect in the source coordinate
 *  frame. It can be used for tiling and for translating an image up/down or left/right by pixel increments. 
 *  If there is no clipRect then the offset is the top left corner of the region read by the filter.
 *  If there are multiple source textures, then the primaryOffset describes the top left corner of the 
 *  region read in the primary source texture. The secondaryOffset describes the top left corner of the
 *  region read in the secondary source texture, and so forth.
 *
 *  @subsubsection  subsubsection_edgemode  MPSKernelEdgeMode
 *  The edgeMode (or primaryEdgeMode or secondaryEdgeMode)describes the behavior of texture reads that
 *  stray off the edge of the source image. This can happen if the offset is negative, meaning read
 *  off the top or left edge of the image.  It can also happen if the clipRect.size + offset
 *  is larger than the source image, meaning read off the bottom and right of the image. It is
 *  also possible for filters that have a filter window that stretches to examine neighboring pixels,
 *  such as convolution, morphology and resampling filters.  If there are multiple source textures, 
 *  then the primaryEdgeMode describes the MPSKernelEdgeMode to use with primary source texture. 
 *  The secondaryEdgeMode describes the MPSKernelEdgeMode to use with the secondary source texture, 
 *  and so forth.
 *
 *      typedef NS_ENUM(NSUInteger, MPSImageEdgeMode)
 *
 *      MPSImageEdgeModeZero       Out of bound pixels are (0,0,0,1) for image formats without
 *                                      alpha channel and (0,0,0,0) for image with pixel format with an
 *                                      alpha channel
 *
 *      MPSImageEdgeModeClamp      Out of bound pixels are clamped to nearest edge pixel
 *
 *  @subsubsection  subsubsection_options  MPSKernelOptions
 *  Each MPSKernel takes a MPSKernelOptions bit mask to indicate various options to use when running the filter:
 *
 *      typedef NS_OPTIONS(NSUInteger, MPSKernelOptions)
 *
 *      MPSKernelOptionsNone                     Use default options
 *
 *      MPSKernelOptionsSkipAPIValidation        Do not spend time looking at parameters passed to MPS
 *                                              for errors.
 *
 *      MPSKernelOptionsAllowReducedPrecision    When possible, MPSKernels use a higher precision data representation internally than
 *                                              the destination storage format to avoid excessive accumulation of computational
 *                                              rounding error in the result. MPSKernelOptionsAllowReducedPrecision advises the
 *                                              MPSKernel that the destination storage format already has too much precision for
 *                                              what is ultimately required downstream, and the MPSKernel may use reduced precision
 *                                              internally when it feels that a less precise result would yield better performance.
 *                                              The expected performance win is often small, perhaps 0-20%. When enabled, the
 *                                              precision of the result may vary by hardware and operating system.
 *
 *  @section subsection_availableFilters     Available MPSKernels
 *
 *  @subsection subsection_convolution  Image Convolution
 *  @subsubsection subsubsection_kernel The Image Convolution Kernel
 *  The convolution filter is at its simplest the weighted average of a pixel with its nearest neighbors.
 *  The weights are provided by a convolution kernel.  The number and position of the nearest neighbors 
 *  that are considered are given by the size of the convolution kernel. For example, a convolution kernel
 *  might be the following 5x5 array of weights:
 *  @code
 *              1       2       3       2       1
 *              2       4       6       4       2
 *              3       6      [9]      6       3
 *              2       4       6       4       2
 *              1       2       3       2       1
 *  @endcode
 *  In order to calculate this 5x5 convolution result, one would multiply all of the pixels in the
 *  image within (5/2=) 2 pixels of the desired pixel by its corresponding weight, add them up and divide by
 *  a divisor to renormalize the results. Then, repeat for all other pixels in the area you wish to convolve.
 *
 *  For those MPS filters where the convolution kernel is passed in, you provide the kernel as a
 *  normalized float array. That is, the kernel weights have the divisor already divided into them and
 *  as a consequence should usually sum to 1.0. In our tent example above, the sum over the area of the kernel 
 *  is 81, so one would normalize it as follows:
 *  @code
 *              1/81    2/81    3/81    2/81    1/81
 *              2/81    4/81    6/81    4/81    2/81
 *              3/81    6/81   [9/81]   6/81    3/81
 *              2/81    4/81    6/81    4/81    2/81
 *              1/81    2/81    3/81    2/81    1/81
 *  @endcode
 *  It is not strictly necessary that the filter weights add up to 1.0f.  Edge detection filters frequently add up
 *  to zero. You may decide to have the area under the filter be a bit bigger or smaller than 1.0 to increase
 *  or reduce the contrast in the result.
 *
 *  The MxN kernel is passed in as a 1-dimensional data array in row major order.
 *
 *  Some convolution filters also have a notion of a bias. This is a number to be added to the
 *  result before it is written out to result texture. A bias might be used to uniformly brighten an image,
 *  set a video range baseline (e.g. 0 might actually be encoded as 16/255) or to make negative signal
 *  representable on a unorm image. 
 *
 *          A unorm image is an image comprised of unsigned normalized samples. A typical 8-bit image (e.g. 
 *          MTLPixelFormatRGBA8Unorm) is a unorm image. It has unsigned samples that represent values between
 *          [0,1]. In the case of MTLPixelFormatRGBA8Unorm, the encoding of 0 is 0, and the encoding of 1.0f
 *          is UINT8_MAX (255).
 *
 *  @subsubsection subsubsection_box  The Box, Tent and Gaussian Filters
 *  There are many different convolution kernel shapes which can produce different results. A kernel consisting
 *  of all 1's is called a Box filter. It is very quick to calculate and may run nearly as fast as a texture
 *  copy, even for very large blur radii. The blur effect that you get, however, can be square in appearance
 *  and may not be entirely appealing under close scrutiny. A second pass of the box will lead to a Tent kernel. 
 *  (The 5x5 tent above can be reduced into two 3x3 Box filters.) Its appearance is more pleasing. Tent 
 *  operations can be found in sample code for window shadows. Both Box and Tent filters are provided by 
 *  MPS. Multiple passes of a box and/or tent  filters will tend to converge towards a gaussian line shape 
 *  and produce a smoother blur effect. MPS also provides a Gaussian blur, though it uses a different method.
 *
 *  @subsubsection subsubsection_laplacian   Laplacian and Unsharp Mask Filters
 *  One can in practice also subtract a blur from the image to produce a sharpening effect (unsharp mask). This
 *  is done by preparing a convolution kernel which is a scaled image less a blur to reduce the low frequency
 *  component of an image. This can reduce blur, but may also emphasize noise in the image.  As an example, we
 *  can do identity minus a box blur:
 *  @code
 *                  | 1   1   1 |
 *      k0 * [1] -  | 1   1   1 | * k2
 *                  | 1   1   1 |
 *  @endcode
 *  If we pick k0 = 9 and k2 = 1, so that the two kernels have equal weight, we arrive at:
 *  @code
 *      |-1  -1  -1 |
 *      |-1   8  -1 |
 *      |-1  -1  -1 |
 *  @endcode
 *  This is a Laplacian filter for calculating image gradients (including diagonals in this case).
 *
 *      Caution: because this convolution kernel has negative regions, it can produce negative 
 *      results as well as positive ones from ordinary image data. If you intend to store the 
 *      result in a unorm texture, you'll need to scale it and add a positive value to it to avoid 
 *      having the negative signal clamped off. (e.g. p' = 0.5*p+0.5).
 *
 *  An unsharp mask filter is the sum between the original image and a scaled result of the Laplacian 
 *  filter. The scaling factor (and filter size and shape) adjusts the nature of the low frequency 
 *  signal and the degree to which it is removed. This work can usually be combined into the convolution 
 *  kernel, to do the whole thing in one pass.
 *
 *  @subsubsection subsubsection_sobel   Sobel Edge detection
 *  Instead of integrating over an area, Convolution filters can also differentiate over an
 *  area by subtracting adjacent pixels.  One such  filter is the Sobel edge detection filter. 
 *  It produces bright signal where there are large differences between one pixel and the next 
 *  and black elsewhere:
 *  @code
 *      | -1  0   1 |       | 1   2   1 |
 *   Gx=| -2  0   2 |   Gy= | 0   0   0 |
 *      | -1  0   1 |       |-1  -2  -1 |
 *
 *
 *      result = sqrt( Convolve(src, Gx) * Convolve(src * Gx) +
 *                     Convolve(src, Gy) * Convolve(src * Gy))
 *  @endcode
 *
 *  @subsubsection subsubsection_otherfilters   Other Filters
 *  Other effects can be achieved as well, such as emboss:
 *  @code
 *     -1   0   0
 *      0   0   0
 *      0   0   1
 *  @endcode
 *  @subsubsection subsubsection_separability   Separable Convolution
 *  Some convolution kernels are separable. That is, the filter weights can be factored into the product
 *  of two smaller sets of weights. As an example, the tent kernel shown above can be factored into a 
 *  horizontal and vertical 1-dimensional kernel each containing [1 2 3 2 1]. In this way, what might otherwise
 *  have been a 5x5 convolution with 25 multiplies and 24 adds is instead a 5x1 and 1x5 convolution with 
 *  a total of 10 multiplies and 8 adds and possibly some extra load/store traffic for the two-pass algorithm. 
 *  The savings get bigger for bigger filter areas. MPS convolution filters will automatically separate 
 *  kernels to run faster, when possible. Some filters with fixed kernels such as Box and Guassian are inherently
 *  separable. We attempt to factor the general convolution kernel into 2 1D kernels in the -initWithDevice:...
 *  method.  If you want to factor it yourself, make two MPSImageConvolution objects with 1D kernels.
 *
 *  @subsubsection subsubsection_convolveAvailability   Convolutions in MPS
 *  Convolution filters provided by MPS include:
 *
 *      MPSImageConvolution       <MetalPerformanceShaders/MPSImageConvolution.h>        General convolution
 *      MPSImageGassianBlur       <MetalPerformanceShaders/MPSImageConvolution.h>        Gaussian blur
 *      MPSImageBox               <MetalPerformanceShaders/MPSImageConvolution.h>        Box blur
 *      MPSImageTent              <MetalPerformanceShaders/MPSImageConvolution.h>        Tent blur
 *
 * @subsection subsection_morphology  Morphology
 *  Morphological operators are similar to convolutions in that they find a result by looking at the nearest
 *  neighbors of each pixel in the image. Instead of calculating a weighted average, morphological operators
 *  scan the kernel area looking for the maximum or minimum pixel value. The MPSImageAreaMax and 
 *  MPSImageAreaMin filters return the raw maximum and minimum color channel value in the kernel area for
 *  each pixel, respectively. The MPSImageDilate and MPSImageErode filters do the same thing, except that the probe 
 *  shape need not be a rectangle, and instead can be nearly any shape you desire, such as a antialiased 
 *  oval, star or heart shape.
 *
 *  When applied, the max and dilate filters have the effect of adding their shape on to the periphery of
 *  bright objects in the image. A single bright pixel, such as might be found in a photograph of a starry
 *  night sky will become the shape of a probe -- a rectangle for max, and perhaps a 5-pointed star if
 *  that is the shape you chose for the dilate filter kernel. Larger objects will adopt more rectangular
 *  or star quality into their shape. (An oval or circular probe would round the corners of a rectangular 
 *  object, for example.)  The min and erode filters do similar things to the darker regions of the image.
 *
 *  When a dilate filter is followed by an erode filter (or max followed by min) with similar filters, the 
 *  effect is known as a close operator. Expanding bright areas only to erode them away again leaves most of
 *  the image in roughly the same shape as it started, but small dark areas that are completely removed by the 
 *  dilate operator are not replaced by the erode. Dark noise may be removed. Small enclosed dark area may
 *  be completely filled in by bright signal.  Similarly erode followed by dilate is an open operator. It 
 *  will tend to remove bright fine detail and fill in small bright areas surrounded by dark lines.
 *
 *  To make a MPS morphology filter with a text glyph draw black text on a white background. MPS
 *  morphology filters must have a center pixel with value 0.
 *
 *
 *  Morphology filters provided by MPS include:
 *
 *      MPSImageAreaMax  <MetalPerformanceShaders/MPSImageMorphology.h>       Area Max
 *      MPSImageAreaMin  <MetalPerformanceShaders/MPSImageMorphology.h>       Area Min
 *      MPSImageDilate   <MetalPerformanceShaders/MPSImageMorphology.h>       Dilate
 *      MPSImageErode    <MetalPerformanceShaders/MPSImageMorphology.h>       Erode
 *
 *  @subsection subsection_histogram     Histogram
 *  A image may be examined by taking the histogram of its pixels. This gives the distribution of the various
 *  intensities per color channel. The MPSImageHistogram filter can be used to calculate a histogram for a MTLTexture.
 *
 *  In some cases, as a result of image processing operations the very dark and light regions of the intensity
 *  spectrum can become unpopulated. Perhaps a photograph is underexposed or overexposed. The MPSImageHistogramEqualization
 *  filter will redistribute the intensities to a more uniform distribution, correcting such problems. 
 *  The MPSImageHistogramSpecification class allows you to cause an image to conform to a different histogram. 
 *
 *
 *  Histogram filters provided by MPS include:
 *
 *      MPSImageHistogram              <MetalPerformanceShaders/MPSImageHistogram.h>     Calculate the histogram of an image
 *      MPSImageHistogramEqualization  <MetalPerformanceShaders/MPSImageHistogram.h>     Redistribute intensity in an image to equalize
 *                                                                          the histogram
 *      MPSImageHistogramSpecification <MetalPerformanceShaders/MPSImageHistogram.h>     A generalized version of histogram equalization
 *                                                                          operation. Convert the image so that its histogram
 *                                                                          matches the desired histogram provided to the
 *                                                                          histogram specification filter.
 *
 * @subsection subsection_median  Image Median
 *  Median filters find the median value in a region surrounding each pixel in the source image.  It is frequently
 *  used to remove noise from the image, but may also be used to remove fine detail like a open filter. It is widely
 *  used in image processing because in many cases it can remove noise while at the same time preserving edges.
 *
 *  Median filters provided by MPS include:
 *
 *      MPSImageMedian                <MetalPerformanceShaders/MPSImageMedian.h>         Calculate the median of an image using a
 *                                                                     square filter window.
 *
 *  @subsection subsection_resampling  Image Resampling
 *  Resampling operations are used to convert one regular array of pixels to another regular array of pixels,
 *  typically along a different set of axes and/or using a different sampling period. Changing the sampling period
 *  will enlarge or reduce images and/or distort the aspect ratio. Change of axis results in rotations or arbitrary
 *  affine transforms. 
 *
 *  For most imaging work on the GPU, resampling can be quickly and simply done as part of another pass using a 
 *  Euler matrices or quaternions to transform the coordinate space followed by linear filtering to interpolate the
 *  value found there. However, this can lead to somewhat muddy images and may result in loss of signal when 
 *  downsampling by more than a factor of two unless a low pass filter is applied first. It is also prone to 
 *  the development of Moire patterns in regions of the image with regularly repeating signal, such as a picture
 *  of a masonry grid on the side of a building. 
 *
 *  The MPS resampling routines use a higher quality (but more expensive) Lanczos resampling algorithm. 
 *  Especially with photographic images, it will usually produce a much nicer result. It does not require a low pass
 *  filter be applied to the image before down sampling. However, some ringing can occur near high frequency regions 
 *  of the image, making the algorithm less suitable for vector art.
 *
 *  MetalPerformanceShaders.framework provides a MPSImageLanczosScale function to allow for simple resizing of images into the clipRect
 *  of the result image. It can operate with preservation of aspect ratio or not. 
 *
 *      MPSImageLanczosScale              <MetalPerformanceShaders/MPSResample.h>   Resize or adjust aspect ratio of an image.
 *
 *  @subsection subsection_threshold     Image Threshold
 *  Thresholding operations are commonly used to separate elements of image structure from the rest of an image. 
 *  Generally, these operate by making some sort of simple comparison test, for example color_intensity > 0.5, and
 *  then writing out 0 or 1 (actual values configurable) depending on the truth or falsehood of the result. It is 
 *  frequently used in computer vision, or to accentuate edge detection filters. 
 *
 *  A variety of thresholding operators are supported:
 *
 *      MPSImageThresholdBinary           <MetalPerformanceShaders/MPSImageThreshold.h>  srcPixel > thresholdVal ? maxVal : 0
 *      MPSImageThresholdBinaryInverse    <MetalPerformanceShaders/MPSImageThreshold.h>  srcPixel > thresholdVal ? 0 : maxVal
 *      MPSImageThresholdTruncate         <MetalPerformanceShaders/MPSImageThreshold.h>  srcPixel > thresholdVal ? thresholdVal : srcPixel
 *      MPSImageThresholdToZero           <MetalPerformanceShaders/MPSImageThreshold.h>  srcPixel > thresholdVal ? srcPixel : 0
 *      MPSImageThresholdToZeroInverse    <MetalPerformanceShaders/MPSImageThreshold.h>  srcPixel > thresholdVal ? 0 : srcPixel
 *
 *  @section  section_validation    MPS API validation
 *  MPS uses the same API validation layer that Metal uses to alert you to API mistakes while
 *  you are developing your code. While this option is turned on (Xcode: Edit Scheme: options: Metal API Validation),
 *  common programming errors will either trigger an assert or send a warning to the the debug log. Except
 *  in the case of serious errors, little or no spew should arrive in the console under standard usage. 
 *  You can also try the MPSKernel.options parameter MPSKernelOptionsSkipAPIValidation to skip most of this checking.
 *  The flag may also lead to small reductions in CPU cost.
 *
 *  Note: where APIs are tagged nonnull, MPS expects that the value is not NULL. The validation layer
 *        may do some checking and assert. If you turn that off, then undefined behavior is the result of 
 *        passing nil, and your application will likely be terminated.
 *
 *
 *  @section  section_usage         How to Add MetalPerformanceShaders.framework to your project
 *
 *  Xcode:
 *
 *      1.  Click project file at left, then appropriate target, then select Build Phases.
 *      2.  Open the "Link Binary With Libraries" disclosure triangle
 *      3.  Click the [+] button in the "Link Binary With Libraries" view to add a new library
 *      4.  Select MetalPerformanceShaders.framework from the list.
 *      5.  Click the Add button.
 *
 *  Command Line:
 *
 *      clang  -framework MetalPerformanceShaders    file.c -o file.o
 *
 *  @section  section_support   How to Determine if MPS Works on Your Device
 *  To test whether MPS works on your device, you may call MPSSupportsMTLDevice(id<MTLDevice>).
 *  It will return YES if the device is supported.
 *
 *  @section  section_inplace   In Place Operation
 *  Some MPS filters can operate in place. In-place operation means that the
 *  same texture is used to hold both the input image and the result image. Operating
 *  in place is a great way to save memory, time and energy. You can use a MPS
 *  filter in place using [MPSKernel encodeToCommandBuffer:inPlaceTexture:copyAllocator:].
 *
 *  Unfortunately, it is not always possible for MPS filters to run in place.
 *  Whether a particular MPSKernel can operate in place can vary according to the
 *  hardware it is running on, the operating system version and the parameters and 
 *  properties passed to it. You may not assume that because a MPSKernel works in place
 *  today on a particular device that it will continue to do so in the future. 
 *
 *  To simplify error handling with failed in-place operation, [MPSKernel 
 *  encodeToCommandBuffer:inPlaceTexture:fallbackCopyAllocator:] takes an optional MPSCopyAllocator
 *  parameter. It is used to create a new texture when in-place operation is not possible 
 *  so as to allow the operation to proceed out of place in a reliable fashion instead. 
 *  (When this happens the input texture is released and replaced with a new texture.) 
 *  To make use of this feature, you will need to write a MPSCopyAllocator block.
 *
 *  @subsection subsection_micopyallocator  MPSCopyAllocator
 *  Some MPSKernel objects may not be able to operate in place. When that occurs, and in-place
 *  operation is requested, MPS will call back to this block to get a new texture
 *  to overwrite instead. To avoid spending long periods of time allocating pages to back the
 *  MTLTexture, the block should attempt to reuse textures. The texture returned from the
 *  MPSCopyAllocator will be returned instead of the sourceTexture from the MPSKernel method
 *  on return. Here is a minimal MPSCopyAllocator implementation:
 *  @code
 *  // A MPSCopyAllocator to handle cases where in-place operation fails.
 *  MPSCopyAllocator myAllocator = ^id <MTLTexture>( MPSKernel * __nonnull filter,
 *                                                  __nonnull id <MTLCommandBuffer> cmdBuf,
 *                                                  __nonnull id <MTLTexture> sourceTexture)
 *  {
 *      MTLPixelFormat format = sourceTexture.pixelFormat;  // FIXME: is this format writable?
 *      MTLTextureDescriptor *d = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat: format
 *                                   width: sourceTexture.width
 *                                  height: sourceTexture.height
 *                               mipmapped: NO];
 *
 *      //FIXME: Allocating a new texture each time is slow. They take up to 1 ms each.
 *      //       There are not too many milliseconds in a video frame! You can recycle
 *      //       old textures (or MTLBuffers and make textures from them) and reuse
 *      //       the memory here.
 *      id <MTLTexture> result = [cmdBuf.device newTextureWithDescriptor: d];
 *
 *      // FIXME: If there is any metadata associated with sourceTexture such as colorspace
 *      //        information, MTLResource.label, MTLResource.cpuCacheMode mode,
 *      //        MTLResource.MTLPurgeableState, etc., it may need to be similarly associated
 *      //        with the new texture, to avoid losing your metadata.
 *
 *      // FIXME: If filter.clipRect doesn't cover the entire image, you may need to copy
 *      //        pixels from sourceTexture to result or regions of result will be
 *      //        uninitialized. You can make a MTLCommandEncoder to encode work on the
 *      //        MTLCommandBuffer here to do that work, if necessary. It will be scheduled
 *      //        to run immediately before the MPSKernel work. Do not call
 *      //        [MTLCommandBuffer enqueue/commit/waitUntilCompleted/waitUntilScheduled]
 *      //        in the MPSCopyAllocator block. Make sure to call -endEncoding on the
 *      //        MTLCommandEncoder so that the MTLCommandBuffer has no active encoder
 *      //        before returning.
 *
 *      // CAUTION: The next command placed on the MTLCommandBuffer after the MPSCopyAllocator
 *      //          returns is almost assuredly going to be encoded with a MTLComputeCommandEncoder.
 *      //          Creating any other type of encoder in the MPSCopyAllocator will probably cost
 *      //          an additional 0.5 ms of both CPU _AND_ GPU time (or more!) due to a double
 *      //          mode switch penalty.
 *
 *      return result;
 *      // d is autoreleased
 *  };
 *  @endcode
 *
 *       filter          A valid pointer to the MPSKernel that is calling the MPSCopyAllocator. From
 *                       it you can get the clipRect of the intended operation.
 *       cmdBuf          A valid MTLCommandBuffer. It can be used to obtain the device against
 *                       which to allocate the new texture. You may also enqueue operations on
 *                       the commandBuffer to initialize the texture. You may not submit, enqueue
 *                       or wait for completion of the command buffer.
 *       sourceTexture   The texture that is providing the source image for the filter. You may
 *                       wish to copy its size and MTLPixelFormat for the new texture, but it is
 *                       not requred.
 *
 *       return          A new valid MTLTexture to use as the destination for the MPSKernel.
 *                       The format of the returned texture does not need to match sourceTexture.
 *
 *
 *  @section  section_samplecode   Sample Code
 *      @code
 *       #import <MetalPerformanceShaders/MetalPerformanceShaders.h>
 *
 *       // Blur the input texture (in place if possible) on MTLCommandQueue q, and return the new texture.
 *       // This is a trivial example. It is not necessary or necessarily advised to enqueue a MPSKernel on
 *       // its own MTLCommandBuffer  or using its own MTLComputeCommandEncoder. Group work together.
 *       //
 *       // Here we assume that you have already gotten a MTLDevice using MTLCreateSystemDefaultDevice() or
 *       // MTLCopyAllDevices(), used it to create a MTLCommandQueue with MTLDevice.newCommandQueue, and 
 *       // similarly made textures with the device as needed.
 *       void  MyBlurTextureInPlace( id <MTLTexture> __strong *inTexture, float blurRadius, id <MTLCommandQueue> q)
 *       {
 *          // Create "the usual Metal objects".
 *          // MPS does not need a dedicated MTLCommandBuffer or MTLComputeCommandEncoder. 
 *          // This is a trivial example. You should reuse the MTL objects you already have, if you have them.
 *          id <MTLDevice> device = q.device;
 *          id <MTLCommandBuffer> buffer = [q commandBuffer];
 *
 *          // Create a MPS filter.
 *          MPSImageGaussianBlur *blur = [[MPSImageGaussianBlur alloc] initWithDevice: device];
 *          if( nil == blur )
 *              MyHandleError(kOutOfMemory);
 *
 *          // Set all MPSKernel properties before calling -canOperateInPlaceWithSourceTexture.
 *          blur.sigma = blurRadius;
 *          // defaults are okay here for other MPSKernel properties. (clipRect, origin, edgeMode)
 *
 *          // Attempt to do the work in place.  Since we provided a copyAllocator as an out-of-place
 *          // fallback, we don't need to check to see if it succeeded or not.
 *          [ blur encodeToCommandBuffer: commandBuffer
 *                        inPlaceTexture: inTexture         // may replace *inTexture
 *                         copyAllocator: myAllocator ];    // See MPSCopyAllocator definition for a sample myAllocator
 *          [ blur release];
 *
 *          // the usual metal enqueue process
 *          [buffer waitUntilCompleted];    // slow!  Try enqueing more work on this or the next command buffer instead of waiting.
 *
 *          return result;
 *      }
 *
 *      @endcode
 *
 *  @section section_tuning     MPS Tuning Hints
 *  MPS has been tuned for excellent performance across a diversity of devices
 *  and filter parameters. The tuning process focuses on minimizing both CPU and GPU
 *  latency for back to back calls on the same MTLCommmandBuffer.  It is possible,
 *  however, to inadvertently undo this optimization effort by introducing costly 
 *  operations into the pipeline around the MPS filter, leading to
 *  disappointing overall results.
 *
 *  Here are some elements of good practice to avoid common pitfalls:
 *
 *  -#  Don't wait for results to complete before enqueuing more work.
 *  There can be a significant delay (up to 2.5 ms) just to get
 *  an empty MTLCommandBuffer through the pipeline to where
 *  [MTLCommandBuffer  waitUntilCompleted] returns. Instead,
 *  start encoding the next command buffer(s) while you wait
 *  for the first one to complete. Enqueue them too, so they can
 *  start immediately after the previous one exits the GPU. Don't
 *  wait for the CPU kernel to notice the first command buffer
 *  is done and start taking it apart and eventually make a callback
 *  to userland before beginning work on encoding the next one.
 *  By allowing the CPU and GPU to work concurrently in this way,
 *  throughput can be enhanced by up to a factor of ten.
 *
 *  -#  There is a large cost to allocating buffers and textures.
 *  The cost can swamp the CPU, preventing you from keeping
 *  the GPU busy. Try to preallocate and reuse MTLResource
 *  objects as much as possible.
 *
 *  -#  There is a cost to switching between render and compute
 *  encoders. Each time a new render encoder is used, there
 *  can be a substantial GPU mode switch cost that may
 *  undermine your throughput. To avoid the cost, try to
 *  batch compute work together. Since making a new MTLCommandBuffer
 *  forces you to make a new MTLCommandEncoder too, try to
 *  do more work with fewer MTLCommandBuffers.
 */


// ==========  MetalPerformanceShaders.framework/Headers/MPSImageResampling.h
/*!
 *  @header MPSImageResampling.h
 *  @framework MetalPerformanceShaders
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract  Resampling filters for Metal Image
 */

#ifndef MPS_MPSImageResampling_h
#define MPS_MPSImageResampling_h

#include <MetalPerformanceShaders/MPSImageKernel.h>


/*!
 *  @class      MPSImageLanczosScale
 *  @abstract   Resize an image and / or change its aspect ratio
 *  @discussion The MPSImageLanczosScale filter can be used to resample an existing image
 *              using a different sampling frequency in each dimension. This can be
 *              used to enlarge or reduce the size of an image, or change the aspect
 *              ratio of an image.  The filter uses a Lanczos resampling algorithm
 *              which typically produces better quality for photographs, but is slower
 *              than linear sampling using the GPU texture units. Lanczos downsampling 
 *              does not require a low pass filter to be applied before it is used. 
 *              Because the resampling function has negative lobes, Lanczos can result 
 *              in ringing near sharp edges, making it less suitable for vector art.
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageLanczosScale : MPSUnaryImageKernel

/*! @property   scaleTransform
 *  @abstract   An optional transform that describes how to scale and translate the source image
 *  @discussion If the scaleTransform is NULL, then the MPSImageLanczosScale filter will 
 *              rescale the image so that the source image fits exactly into the destination 
 *              texture.  If the transform is not NULL, then the transform is used for determining
 *              how to map the source image to the destination. Default: NULL
 *              
 *              When the scaleTransform is set to non-NULL, the values pointed to by the new 
 *              scaleTransform are copied to object storage, and the pointer is updated to point 
 *              to internal storage. Do not attempt to free it.  You may free your copy of 
 *              the MPSScaleTransform as soon as the property set operation is complete.
 */
@property (readwrite, nonatomic, nullable) const MPSScaleTransform *scaleTransform;



@end

#endif /* MPS_MSImageResampling_h */
// ==========  MetalPerformanceShaders.framework/Headers/MPSImageKernel.h
/*!
 *  @header MPSImageKernel.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract Metal Image filter base classes
 */

#ifndef _MPS_MPSImageKernel_
#define _MPS_MPSImageKernel_

#import <MetalPerformanceShaders/MPSKernel.h>

/*!
 *  @class      MPSUnaryImageKernel
 *  @dependency This depends on Metal.framework
 *  @discussion A MPSUnaryImageKernel consumes one MTLTexture and produces one MTLTexture.
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface MPSUnaryImageKernel : MPSKernel


/*! @property   offset
 *  @abstract   The position of the destination clip rectangle origin relative to the source buffer.
 *  @discussion The offset is defined to be the position of clipRect.origin in source coordinates.
 *              Default: {0,0,0}, indicating that the top left corners of the clipRect and source image align.
 *
 *              See Also: @ref subsubsection_mioffset
 */
@property (readwrite, nonatomic) MPSOffset                offset;

/*! @property   clipRect
 *  @abstract   An optional clip rectangle to use when writing data. Only the pixels in the rectangle will be overwritten.
 *  @discussion A MTLRegion that indicates which part of the destination to overwrite. If the clipRect does not lie
 *              completely within the destination image, the intersection between clip rectangle and destination bounds is
 *              used.   Default: MPSRectNoClip (MPSKernel::MPSRectNoClip) indicating the entire image.
 *
 *              See Also: @ref subsubsection_clipRect
 */
@property (readwrite, nonatomic) MTLRegion               clipRect;


/*! @property   edgeMode
 *  @abstract   The MPSImageEdgeMode to use when texture reads stray off the edge of an image
 *  @discussion Most MPSKernel objects can read off the edge of the source image. This can happen because of a
 *              negative offset property, because the offset + clipRect.size is larger than the
 *              source image or because the filter looks at neighboring pixels, such as a Convolution
 *              or morphology filter.   Default: usually MPSImageEdgeModeZero. (Some MPSKernel types default
 *              to MPSImageEdgeModeClamp, because MPSImageEdgeModeZero is either not supported or
 *              would produce unexpected results.)
 *
 *              See Also: @ref subsubsection_edgemode
 */
@property (readwrite, nonatomic) MPSImageEdgeMode        edgeMode;



/*!
 *  This method attempts to apply the MPSKernel in place on a texture.
 *
 *          In-place operation means that the same texture is used both to hold the input
 *          image and the results. Operating in-place can be an excellent way to reduce
 *          resource utilization, and save time and energy. While simple Metal kernels can
 *          not operate in place because textures can not be readable and writable at the
 *          same time, some MPSKernels can operate in place because they use
 *          multi-pass algorithms. Whether a MPSKernel can operate in-place can
 *          depend on current hardware, operating system revision and the parameters
 *          and properties passed to it. You should never assume that a MPSKernel will
 *          continue to work in place, even if you have observed it doing so before.
 *
 *  If the operation succeeds in-place, YES is returned.  If the in-place operation
 *  fails and no copyAllocator is provided, then NO is returned. Without a fallback
 *  MPSCopyAllocator, in neither case is the pointer held at *texture modified.
 *
 *  Failure during in-place operation is very common and will occur inconsistently across
 *  different hardware platforms and OS releases. Without a fallback MPSCopyAllocator,
 *  operating in place may require significant error handling code to accompany each
 *  call to -encodeToCommandBuffer:..., complicating your code.
 *
 *  You may find it simplifies your code to provide a fallback MPSCopyAllocator so
 *  that the operation can proceed reliably even when it can not proceed in-place.
 *  When an in-place filter fails, the MPSCopyAllocator (if any) will be
 *  invoked to create a new texture in which to write the results, allowing the
 *  filter to proceed reliably out-of-place. The original texture will be released,
 *  replaced with a pointer to the new texture and YES will be returned. If the
 *  allocator returns an invalid texture, it is released, *texture remains unmodified
 *  and NO is returned.  Please see the MPSCopyAllocator definition for a sample allocator
 *  implementation.
 *
 *  Sample usage with a copy allocator:
 *  @code
 *  id <MTLTexture> inPlaceTex = ...;
 *  MPSImageSobel *sobelFiler = [[MPSImageSobel alloc] initWithDevice: my_device];
 *
 *  // With a fallback MPSCopyAllocator, failure should only occur in exceptional
 *  // conditions such as MTLTexture allocation failure or programmer error.
 *  // That is, the operation is roughly as robust as the MPSCopyAllocator.
 *  // Depending on the quality of that, we might decide we are justified here
 *  // in not checking the return value.
 *  [sobelFilter encodeToCommandBuffer: my_command_buffer
 *                      inPlaceTexture: &inPlaceTex  // may be replaced!
 *               fallbackCopyAllocator: myAllocator];
 *
 *  // If myAllocator was not called:
 *  //
 *  //      inPlaceTex holds the original texture with the result pixels in it
 *  //
 *  // else,
 *  //
 *  //      1) myAllocator creates a new texture.
 *  //      2) The new texture pixel data is overwritten by MPSUnaryImageKernel.
 *  //      3) The old texture passed in *inPlaceTex is released once.
 *  //      4) *inPlaceTex = the new texture
 *  //
 *  // In either case, the caller should now hold one reference to the texture now held in
 *  // inPlaceTex, whether it was replaced or not. Most of the time that means that nothing
 *  // further needs to be done here, and you can proceed to the next image encoding operation.
 *  // However, if other agents held references to the original texture, they still hold them
 *  // and may need to be alerted that the texture has been replaced so that they can retain
 *  // the new texture and release the old one.
 *
 *  [sobelFilter release];  // if not ARC, clean up the MPSImageSobel object
 *  @endcode
 *
 *
 *  @abstract   Attempt to apply a MPSKernel to a texture in place.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      texture             A pointer to a valid MTLTexture containing source image.
 *                                  On success, the image contents and possibly texture itself
 *                                  will be replaced with the result image.
 *  @param      copyAllocator       An optional block to allocate a new texture to hold the
 *                                  results, in case in-place operation is not possible. The
 *                                  allocator may use a different MTLPixelFormat or size than
 *                                  the original texture. You may enqueue operations on the
 *                                  provided MTLCommandBuffer using the provided
 *                                  MTLComputeCommandEncoder to initialize the texture contents.
 *  @return     On success, YES is returned. The texture may have been replaced with a new
 *              texture if a copyAllocator was provided.  On failure, NO is returned. The
 *              texture is unmodified.
 */
-(BOOL)    encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)commandBuffer
                  inPlaceTexture: (__nonnull id <MTLTexture> __strong * __nonnull) texture
           fallbackCopyAllocator: (nullable MPSCopyAllocator) copyAllocator;


/*!
 *  @abstract   Encode a MPSKernel into a command Buffer.  The operation shall proceed out-of-place.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceTexture       A valid MTLTexture containing the source image.
 *  @param      destinationTexture  A valid MTLTexture to be overwritten by result image. DestinationTexture may not alias sourceTexture.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                sourceTexture: (nonnull id <MTLTexture>) sourceTexture
           destinationTexture: (nonnull id <MTLTexture>) destinationTexture;


/*!
 *  sourceRegionForDestinationSize: is used to determine which region of the
 *  sourceTexture will be read by encodeToCommandBuffer:sourceTexture:destinationTexture
 *  (and similar) when the filter runs. This information may be needed if the
 *  source image is broken into multiple textures.  The size of the full
 *  (untiled) destination image is provided. The region of the full (untiled)
 *  source image that will be read is returned. You can then piece together an
 *  appropriate texture containing that information for use in your tiled context.
 *
 *  The function will consult the MPSUnaryImageKernel offset and clipRect parameters, 
 *  to determine the full region read by the function. Other parameters such as
 *  sourceClipRect, kernelHeight and kernelWidth will be consulted as necessary.
 *  All properties should be set to intended values prior to calling 
 *  sourceRegionForDestinationSize:.
 *
 *      Caution: This function operates using global image coordinates, but
 *      -encodeToCommandBuffer:... uses coordinates local to the source and
 *      destination image textures. Consequently, the offset and clipRect 
 *      attached to this object will need to be updated using a global to 
 *      local coordinate transform before -encodeToCommandBuffer:... is 
 *      called.
 *
 *  @abstract   Determine the region of the source texture that will be read for a encode operation 
 *  @param      destinationSize The size of the full virtual destination image.
 *  @return     The area in the virtual source image that will be read.
 */
-(MPSRegion) sourceRegionForDestinationSize: (MTLSize) destinationSize;

@end



/*!
 *  @class      MPSBinaryImageKernel
 *  @dependency This depends on Metal.framework
 *  @discussion A MPSBinaryImageKernel consumes two MTLTextures and produces one MTLTexture.
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface MPSBinaryImageKernel : MPSKernel

/*! @property   primaryOffset
 *  @abstract   The position of the destination clip rectangle origin relative to the primary source buffer.
 *  @discussion The offset is defined to be the position of clipRect.origin in source coordinates.
 *              Default: {0,0,0}, indicating that the top left corners of the clipRect and primary source image align.
 *
 *              See Also: @ref subsubsection_mioffset
 */
@property (readwrite, nonatomic) MPSOffset                primaryOffset;

/*! @property   secondaryOffset
 *  @abstract   The position of the destination clip rectangle origin relative to the secondary source buffer.
 *  @discussion The offset is defined to be the position of clipRect.origin in source coordinates.
 *              Default: {0,0,0}, indicating that the top left corners of the clipRect and primary source image align.
 *
 *              See Also: @ref subsubsection_mioffset
 */
@property (readwrite, nonatomic) MPSOffset                secondaryOffset;


/*! @property   primaryEdgeMode
 *  @abstract   The MPSImageEdgeMode to use when texture reads stray off the edge of the primary source image
 *  @discussion Most MPSKernel objects can read off the edge of a source image. This can happen because of a
 *              negative offset property, because the offset + clipRect.size is larger than the
 *              source image or because the filter looks at neighboring pixels, such as a Convolution
 *              or morphology filter.   Default: usually MPSImageEdgeModeZero. (Some MPSKernel types default
 *              to MPSImageEdgeModeClamp, because MPSImageEdgeModeZero is either not supported or
 *              would produce unexpected results.)
 *
 *              See Also: @ref subsubsection_edgemode
 */
@property (readwrite, nonatomic) MPSImageEdgeMode        primaryEdgeMode;

/*! @property   secondaryEdgeMode
 *  @abstract   The MPSImageEdgeMode to use when texture reads stray off the edge of the secondary source image
 *  @discussion Most MPSKernel objects can read off the edge of a source image. This can happen because of a
 *              negative offset property, because the offset + clipRect.size is larger than the
 *              source image or because the filter looks at neighboring pixels, such as a Convolution
 *              or morphology filter.   Default: usually MPSImageEdgeModeZero. (Some MPSKernel types default
 *              to MPSImageEdgeModeClamp, because MPSImageEdgeModeZero is either not supported or
 *              would produce unexpected results.)
 *
 *              See Also: @ref subsubsection_edgemode
 */
@property (readwrite, nonatomic) MPSImageEdgeMode        secondaryEdgeMode;

/*! @property   clipRect
 *  @abstract   An optional clip rectangle to use when writing data. Only the pixels in the rectangle will be overwritten.
 *  @discussion A MTLRegion that indicates which part of the destination to overwrite. If the clipRect does not lie
 *              completely within the destination image, the intersection between clip rectangle and destination bounds is
 *              used.   Default: MPSRectNoClip (MPSKernel::MPSRectNoClip) indicating the entire image.
 *
 *              See Also: @ref subsubsection_clipRect
 */
@property (readwrite, nonatomic) MTLRegion               clipRect;




/*!
 *  This method attempts to apply the MPSKernel in place on a texture.
 *
 *          In-place operation means that the same texture is used both to hold the input
 *          image and the results. Operating in-place can be an excellent way to reduce
 *          resource utilization, and save time and energy. While simple Metal kernels can
 *          not operate in place because textures can not be readable and writable at the
 *          same time, some MPSKernels can operate in place because they use
 *          multi-pass algorithms. Whether a MPSKernel can operate in-place can
 *          depend on current hardware, operating system revision and the parameters
 *          and properties passed to it. You should never assume that a MPSKernel will
 *          continue to work in place, even if you have observed it doing so before.
 *
 *  If the operation succeeds in-place, YES is returned.  If the in-place operation
 *  fails and no copyAllocator is provided, then NO is returned. In neither
 *  case is the pointer held at *texture modified.
 *
 *  Failure during in-place operation is common. You may find it simplifies your
 *  code to provide a copyAllocator. When an in-place filter fails, your
 *  copyAllocator will be invoked to create a new texture in which to write
 *  the results, allowing the filter to proceed reliably out-of-place. The
 *  original texture will be released, replaced with a pointer to the new texture
 *  and YES will be returned. If the allocator returns an invalid texture, it is
 *  released, *texture remains unmodified and NO is returned.  Please see the
 *  MPSCopyAllocator definition for a sample allocator implementation.
 *
 *  @abstract   Attempt to apply a MPSKernel to a texture in place.
 *  @param      commandBuffer           A valid MTLCommandBuffer to receive the encoded filter
 *  @param      primaryTexture          A pointer to a valid MTLTexture containing the
 *                                      primary source image. It will not be overwritten.
 *  @param      inPlaceSecondaryTexture A pointer to a valid MTLTexture containing secondary image.
 *                                      On success, the image contents and possibly texture itself
 *                                      will be replaced with the result image.
 *  @param      copyAllocator           An optional block to allocate a new texture to hold the
 *                                      results, in case in-place operation is not possible. The
 *                                      allocator may use a different MTLPixelFormat or size than
 *                                      the original texture. You may enqueue operations on the
 *                                      provided MTLCommandBuffer using the provided
 *                                      MTLComputeCommandEncoder to initialize the texture contents.
 *  @return     On success, YES is returned. The texture may have been replaced with a new
 *              texture if a copyAllocator was provided.  On failure, NO is returned. The
 *              texture is unmodified.
 */
-(BOOL)    encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)commandBuffer
                  primaryTexture: (nonnull id <MTLTexture>) primaryTexture
         inPlaceSecondaryTexture: (__nonnull id <MTLTexture> __strong * __nonnull) inPlaceSecondaryTexture
           fallbackCopyAllocator: (nullable MPSCopyAllocator) copyAllocator;

/*!
 *  This method attempts to apply the MPSKernel in place on a texture.
 *
 *          In-place operation means that the same texture is used both to hold the input
 *          image and the results. Operating in-place can be an excellent way to reduce
 *          resource utilization, and save time and energy. While simple Metal kernels can
 *          not operate in place because textures can not be readable and writable at the
 *          same time, some MPSKernels can operate in place because they use
 *          multi-pass algorithms. Whether a MPSKernel can operate in-place can
 *          depend on current hardware, operating system revision and the parameters
 *          and properties passed to it. You should never assume that a MPSKernel will
 *          continue to work in place, even if you have observed it doing so before.
 *
 *  If the operation succeeds in-place, YES is returned.  If the in-place operation
 *  fails and no copyAllocator is provided, then NO is returned. In neither
 *  case is the pointer held at *texture modified.
 *
 *  Failure during in-place operation is common. You may find it simplifies your
 *  code to provide a copyAllocator. When an in-place filter fails, your
 *  copyAllocator will be invoked to create a new texture in which to write
 *  the results, allowing the filter to proceed reliably out-of-place. The
 *  original texture will be released, replaced with a pointer to the new texture
 *  and YES will be returned. If the allocator returns an invalid texture, it is
 *  released, *texture remains unmodified and NO is returned.  Please see the
 *  MPSCopyAllocator definition for a sample allocator implementation.
 *
 *  @abstract   Attempt to apply a MPSKernel to a texture in place.
 *  @param      commandBuffer           A valid MTLCommandBuffer to receive the encoded filter
 *  @param      inPlacePrimaryTexture   A pointer to a valid MTLTexture containing secondary image.
 *                                      On success, the image contents and possibly texture itself
 *                                      will be replaced with the result image.
 *  @param      secondaryTexture        A pointer to a valid MTLTexture containing the
 *                                      primary source image. It will not be overwritten.
 *  @param      copyAllocator           An optional block to allocate a new texture to hold the
 *                                      results, in case in-place operation is not possible. The
 *                                      allocator may use a different MTLPixelFormat or size than
 *                                      the original texture. You may enqueue operations on the
 *                                      provided MTLCommandBuffer using the provided
 *                                      MTLComputeCommandEncoder to initialize the texture contents.
 *  @return     On success, YES is returned. The texture may have been replaced with a new
 *              texture if a copyAllocator was provided.  On failure, NO is returned. The
 *              texture is unmodified.
 */
-(BOOL)    encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)commandBuffer
           inPlacePrimaryTexture: (__nonnull id <MTLTexture> __strong * __nonnull) inPlacePrimaryTexture
                secondaryTexture: (nonnull id <MTLTexture>) secondaryTexture
           fallbackCopyAllocator: (nullable MPSCopyAllocator) copyAllocator;


/*!
 *  @abstract   Encode a MPSKernel into a command Buffer.  The operation shall proceed out-of-place.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      primaryTexture      A valid MTLTexture containing the primary source image.
 *  @param      secondaryTexture    A valid MTLTexture containing the secondary source image.
 *  @param      destinationTexture  A valid MTLTexture to be overwritten by result image. destinationTexture may not alias sourceTexture.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
               primaryTexture: (nonnull id <MTLTexture>) primaryTexture
             secondaryTexture: (nonnull id <MTLTexture>) secondaryTexture
           destinationTexture: (nonnull id <MTLTexture>) destinationTexture;

/*!
 *  primarySourceRegionForDestinationSize: is used to determine which region of the
 *  primaryTexture will be read by encodeToCommandBuffer:primaryTexture:secondaryTexture:destinationTexture
 *  (and in-place variants) when the filter runs. This information may be needed if the
 *  primary source image is broken into multiple textures.  The size of the full
 *  (untiled) destination image is provided. The region of the full (untiled)
 *  source image that will be read is returned. You can then piece together an
 *  appropriate texture containing that information for use in your tiled context.
 *
 *  The function will consult the MPSBinaryImageKernel primaryOffset and clipRect parameters,
 *  to determine the full region read by the function. Other parameters such as
 *  kernelHeight and kernelWidth will be consulted as necessary. All properties
 *  should be set to intended values prior to calling primarySourceRegionForDestinationSize:.
 *
 *      Caution: This function operates using global image coordinates, but
 *      -encodeToCommandBuffer:... uses coordinates local to the source and
 *      destination image textures. Consequently, the primaryOffset and clipRect
 *      attached to this object will need to be updated using a global to
 *      local coordinate transform before -encodeToCommandBuffer:... is
 *      called.
 *
 *  @abstract   Determine the region of the source texture that will be read for a encode operation
 *  @param      destinationSize     The size of the full virtual destination image.
 *  @return     The area in the virtual source image that will be read.
 */
-(MPSRegion) primarySourceRegionForDestinationSize: (MTLSize) destinationSize;

/*!
 *  secondarySourceRegionForDestinationSize: is used to determine which region of the
 *  sourceTexture will be read by encodeToCommandBuffer:primaryTexture:secondaryTexture:destinationTexture
 *  (and in-place variants) when the filter runs. This information may be needed if the
 *  secondary source image is broken into multiple textures.  The size of the full
 *  (untiled) destination image is provided. The region of the full (untiled)
 *  secondary source image that will be read is returned. You can then piece together an
 *  appropriate texture containing that information for use in your tiled context.
 *
 *  The function will consult the MPSBinaryImageKernel secondaryOffset and clipRect
 *  parameters, to determine the full region read by the function. Other parameters
 *  such as kernelHeight and kernelWidth will be consulted as necessary.  All properties
 *  should be set to intended values prior to calling secondarySourceRegionForDestinationSize:.
 *
 *      Caution: This function operates using global image coordinates, but
 *      -encodeToCommandBuffer:... uses coordinates local to the source and
 *      destination image textures. Consequently, the secondaryOffset and clipRect
 *      attached to this object will need to be updated using a global to
 *      local coordinate transform before -encodeToCommandBuffer:... is
 *      called.
 *
 *  @abstract   Determine the region of the source texture that will be read for a encode operation
 *  @param      destinationSize     The size of the full virtual destination image.
 *  @return     The area in the virtual source image that will be read.
 */
-(MPSRegion) secondarySourceRegionForDestinationSize: (MTLSize) destinationSize;



@end

#endif /* defined(_MetalSmartShaders_MSImageKernel_) */
// ==========  MetalPerformanceShaders.framework/Headers/MPSImageIntegral.h
/*!
 *  @header MPSImageIntegral.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract Metal Image integral filters
 */

#ifndef MPS_MPSImageIntegral_h
#define MPS_MPSImageIntegral_h

#include <MetalPerformanceShaders/MPSImageKernel.h>

/*!
 *  @class      MPSImageIntegral
 *  @discussion The MPSImageIntegral calculates the sum of pixels over a specified region in the image.
 *              The value at each position is the sum of all pixels in a source image rectangle, sumRect:
 *
 *                  sumRect.origin = MPSUnaryImageKernel.offset
 *                  sumRect.size = dest_position - MPSUnaryImageKernel.clipRect.origin
 *
 *              If the channels in the source image are normalized, half-float or floating values,
 *              the destination image is recommended to be a 32-bit floating-point image.
 *              If the channels in the source image are integer values, it is recommended that
 *              an appropriate 32-bit integer image destination format is used.
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageIntegral : MPSUnaryImageKernel

@end    /* MPSImageIntegral */


/*!
 *  @class      MPSImageIntegralOfSquares
 *  @discussion The MPSImageIntegralOfSquares calculates the sum of squared pixels over a specified region in the image.
 *              The value at each position is the sum of all squared pixels in a source image rectangle, sumRect:
 *
 *                  sumRect.origin = MPSUnaryImageKernel.offset
 *                  sumRect.size = dest_position - MPSUnaryImageKernel.clipRect.origin
 *
 *              If the channels in the source image are normalized, half-float or floating values,
 *              the destination image is recommended to be a 32-bit floating-point image.
 *              If the channels in the source image are integer values, it is recommended that
 *              an appropriate 32-bit integer image destination format is used.
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageIntegralOfSquares : MPSUnaryImageKernel

@end    /* MPSImageIntegralOfSquares */

#endif  /* MPS_MSImageIntegral_h */

// ==========  MetalPerformanceShaders.framework/Headers/MPSTypes.h
/*!
 *  @header MPSTypes.h
 *  @framework MetalPerformanceShaders
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @discussion   Types common to MetalPerformanceShaders.framework
 */

#ifndef MPS_Types_h
#define MPS_Types_h

#ifdef __cplusplus
extern "C" {
#endif
    
#import <Foundation/NSObjCRuntime.h>
#import <Metal/Metal.h>

    
#ifndef __has_attribute          /* clang will define this. Other compilers maybe not. */
#    define __has_attribute(a)   0
#endif
#ifndef __has_feature           /* clang will define this. Other compilers maybe not. */
#    define __has_feature(f)     0
#endif
#ifndef __has_extension         /* clang will define this. Other compilers maybe not. */
#    define __has_extension(e)   0
#endif
#if __has_extension(enumerator_attributes)
#    ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
#        define MPS_ENUM_AVAILABLE_STARTING(_osx, _ios)   __AVAILABILITY_INTERNAL##_ios
#        define MPS_AVAILABLE_STARTING(_osx, _ios)        __AVAILABILITY_INTERNAL##_ios
#    elif defined(__MAC_OS_X_VERSION_MIN_REQUIRED)
#        define MPS_ENUM_AVAILABLE_STARTING(_osx, _ios)   __AVAILABILITY_INTERNAL##_osx
#        define MPS_AVAILABLE_STARTING(_osx, _ios)        __AVAILABILITY_INTERNAL##_osx
#    else
#        define MPS_ENUM_AVAILABLE_STARTING(_osx, _ios)
#        define MPS_AVAILABLE_STARTING(_osx, _ios)
#    endif
#else
#    define MPS_ENUM_AVAILABLE_STARTING( _a, _b )
#endif


/*! @typedef    MPSKernelOptions
 *  @memberof   MPSKernel
 *  @abstract   Options used when creating MPSKernel objects
 *
 *          MPSKernelOptionsNone                    Use default options
 *
 *          MPSKernelOptionsSkipAPIValidation       Most MetalImage functions will sanity check their arguments. This has a small but
 *                                                  non-zero CPU cost. Setting the MPSKernelOptionsSkipAPIValidation will skip these checks.
 *                                                  MPSKernelOptionsSkipAPIValidation does not skip checks for memory allocation failure.
 *                                                  Caution:  turning on MPSKernelOptionsSkipAPIValidation can result in undefined behavior
 *                                                  if the requested operation can not be completed for some reason. Most error states
 *                                                  will be passed through to Metal which may do nothing or abort the program if Metal
 *                                                  API validation is turned on.
 *
 *          MPSKernelOptionsAllowReducedPrecision   When possible, MPSKernels use a higher precision data representation internally than
 *                                                  the destination storage format to avoid excessive accumulation of computational
 *                                                  rounding error in the result. MPSKernelOptionsAllowReducedPrecision advises the
 *                                                  MPSKernel that the destination storage format already has too much precision for
 *                                                  what is ultimately required downstream, and the MPSKernel may use reduced precision
 *                                                  internally when it feels that a less precise result would yield better performance.  
 *                                                  The expected performance win is often small, perhaps 0-20%. When enabled, the
 *                                                  precision of the result may vary by hardware and operating system.
 */
typedef NS_OPTIONS(NSUInteger, MPSKernelOptions)
{
    MPSKernelOptionsNone                         MPS_ENUM_AVAILABLE_STARTING( __MAC_NA, __IPHONE_9_0)  = 0,
    MPSKernelOptionsSkipAPIValidation            MPS_ENUM_AVAILABLE_STARTING( __MAC_NA, __IPHONE_9_0)  = 1 << 0,
    MPSKernelOptionsAllowReducedPrecision        MPS_ENUM_AVAILABLE_STARTING( __MAC_NA, __IPHONE_9_0)  = 1 << 1,
};
    
/*! @typedef    MPSImageEdgeMode
 *  @memberof   MPSKernel
 *  @abstract   Options used to control edge behaviour of filter when filter reads beyond boundary of src image
 *
 *          MPSImageEdgeModeClamp        Out of bound pixels are clamped to nearest edge pixel
 *
 *          MPSImageEdgeModeZero         Out of bound pixels are (0,0,0,1) for image with pixel format without alpha channel
 *                                       and (0,0,0,0) for image with pixel format that has an alpha channel
 */
typedef NS_ENUM(NSUInteger, MPSImageEdgeMode)
{
    MPSImageEdgeModeZero                MPS_ENUM_AVAILABLE_STARTING(__MAC_NA, __IPHONE_9_0)  = 0,
    MPSImageEdgeModeClamp               MPS_ENUM_AVAILABLE_STARTING(__MAC_NA, __IPHONE_9_0)  = 1,
};
    
/*!
 *  @typedef    MPSOffset
 *  @memberof   MPSKernel
 *  @abstract   A signed coordinate with x, y and z components
 *  @field      x       The horizontal component of the offset. Units: pixels
 *  @field      y       The vertical component of the offset. Units: pixels
 *  @field      z       The depth component of the offset. Units: pixels
 */
typedef struct
{
    NSInteger x;    /**<    The horizontal component of the offset. Units: pixels   */
    NSInteger y;    /**<    The vertical component of the offset. Units: pixels     */
    NSInteger z;    /**<    The depth component of the offset. Units: pixels        */
}MPSOffset;

/*!
 *  @typedef    MPSOrigin
 *  @memberof   MPSKernel
 *  @abstract   A position in an image
 *  @field      x   The x coordinate of the position
 *  @field      y   The y coordinate of the position
 *  @field      z   The z coordinate of the position
 */
typedef struct
{
    double  x;
    double  y;
    double  z;
}MPSOrigin;

/*!
 *  @typedef    MPSSize
 *  @memberof   MPSKernel
 *  @abstract   A size of a region in an image
 *  @field      width       The width of the region
 *  @field      height      The height of a region
 *  @field      depth       The depth of a region (usually 1)
 */
typedef struct
{
    double  width;
    double  height;
    double  depth;
}MPSSize;

/*!
 *  @typedef    MPSRegion
 *  @memberof   MPSKernel
 *  @abstract   A region of an image
 *  @field      origin  The top left corner of the region.  Units: pixels
 *  @field      size    The size of the region.             Units: pixels
 */
typedef struct
{
    MPSOrigin       origin;                 /**< The top left corner of the region.  Units: pixels */
    MPSSize         size;                   /**< The size of the region. Units: pixels */
}MPSRegion;
    
/*!
 *  @memberof   MPSKernel
 *  @constant   MPSRectNoClip
 *  @discussion This is a special constant to indicate no clipping is to be done.
 *              The entire image will be used.
 *              This is the default clipping rectangle or the input extent for MPSKernels.
 */
extern const MTLRegion  MPSRectNoClip;
    
/*!
 *  @typedef    MPSScaleTransform
 *  @memberof   MPSImageLanczosScale
 *  @abstract   Transform matrix for explict control over resampling in MPSImageLanczosScale
 */
typedef struct MPSScaleTransform
{
    double  scaleX, scaleY;
    double  translateX, translateY;
}MPSScaleTransform;

@class MPSKernel;
    
/*!
 *  @typedef    MPSCopyAllocator
 *  @memberof   MPSKernel
 *  @abstract   A block to make a copy of sourceTexture for MPSKernels that can only execute out of place.
 *  @discussion Some MPSKernel objects may not be able to operate in place. When that occurs, and in-place
 *              operation is requested, MetalImage will call back to this block to get a new texture
 *              to return instead. To avoid spending long periods of time allocating pages to back the
 *              MTLTexture, the block should attempt to reuse textures. The texture returned from the
 *              MPSCopyAllocator will be returned instead of the sourceTexture from the MPSKernel method 
 *              on return.
 *              @code
 *              // A MPSCopyAllocator to handle cases where in-place operation fails.
 *              MPSCopyAllocator myAllocator = ^id <MTLTexture>( MPSKernel * __nonnull filter,
 *                                                              __nonnull id <MTLCommandBuffer> cmdBuf,
 *                                                              __nonnull id <MTLTexture> sourceTexture)
 *              {
 *                  MTLPixelFormat format = sourceTexture.pixelFormat;  // FIXME: is this format writable?
 *                  MTLTextureDescriptor *d = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat: format
 *                                               width: sourceTexture.width
 *                                              height: sourceTexture.height
 *                                           mipmapped: NO];
 *
 *                  //FIXME: Allocating a new texture each time is slow. They take up to 1 ms each.
 *                  //       There are not too many milliseconds in a video frame! You can recycle
 *                  //       old textures (or MTLBuffers and make textures from them) and reuse
 *                  //       the memory here.
 *                  id <MTLTexture> result = [cmdBuf.device newTextureWithDescriptor: d];
 *
 *                  // FIXME: If there is any metadata associated with sourceTexture such as colorspace
 *                  //        information, MTLResource.label, MTLResource.cpuCacheMode mode,
 *                  //        MTLResource.MTLPurgeableState, etc., it may need to be similarly associated
 *                  //        with the new texture to avoid losing your metadata.
 *
 *                  // FIXME: If filter.clipRect doesn't cover the entire image, you may need to copy
 *                  //        pixels from sourceTexture to the new texture or regions of the new texture
 *                  //        will be uninitialized. You can make a MTLCommandEncoder to encode work on
 *                  //        the MTLCommandBuffer here to do that work, if necessary. It will be
 *                  //        scheduled to run immediately before the MPSKernel work. Do may call
 *                  //        [MTLCommandBuffer enqueue/commit/waitUntilCompleted/waitUntilScheduled]
 *                  //        in the MPSCopyAllocator block. Make sure to call -endEncoding on the
 *                  //        MTLCommandEncoder so that the MTLCommandBuffer has no active encoder
 *                  //        before returning.
 *
 *                  // CAUTION: The next command placed on the MTLCommandBuffer after the MPSCopyAllocator 
 *                  //          returns is almost assuredly going to be encoded with a MTLComputeCommandEncoder. 
 *                  //          Creating any other type of encoder in the MPSCopyAllocator will probably cost
 *                  //          an additional 0.5 ms of both CPU _AND_ GPU time (or more!) due to a double 
 *                  //          mode switch penalty.
 *
 *                  // CAUTION: If other objects (in addition to the caller of -encodeToCommandBuffer:inPlaceTexture:...)
 *                  //          own a reference to sourceTexture, they may need to be notified that
 *                  //          sourceTexture has been replaced so that they can release that resource
 *                  //          and adopt the new texture. 
 *
 *                  //          The reference to sourceTexture owned by the caller of
 *                  //          -encodeToCommandBuffer:inPlaceTexture... will be released by 
 *                  //          -encodeToCommandBuffer:inPlaceTexture:... after the kernel is encoded if 
 *                  //          and only if the MPSCopyAllocator is called, and the operation is successfully 
 *                  //          encoded out of place.
 *
 *                  return result;
 *                  // d is autoreleased
 *              };
 *              @endcode
 *              If nil is returned by the allocator, NO will be returned by the calling function.
 *
 *              When the MPSCopyAllocator is called, no MTLCommandEncoder is active on the commandBuffer.
 *              You may create a MTLCommandEncoder in the block to initialize the texture. Make sure
 *              to call -endEncoding on it before returning, if you do.
 *             
 *                  The next command placed on the MTLCommandBuffer after the MPSCopyAllocator returns is
 *                  almost assuredly going to be encoded with a MTLComputeCommandEncoder. Using any other
 *                  type of encoder in the MPSCopyAllocator will probably cost you an additional 0.5 ms
 *                  of both CPU _AND_ GPU time (or more!) due to a double mode switch penalty.
 *
 *
 *  @param      filter          A valid pointer to the MPSKernel that is calling the MPSCopyAllocator. From
 *                              it you can get the clipRect of the intended operation.
 *  @param      commandBuffer   A valid MTLCommandBuffer. It can be used to obtain the device against
 *                              which to allocate the new texture. You may also enqueue operations on
 *                              the commandBuffer to initialize the texture on a encoder allocated in the
 *                              block. You may not submit, enqueue or wait for scheduling/completion of 
 *                              the command buffer.
 *  @param      sourceTexture   The texture that is providing the source image for the filter. You may
 *                              wish to use its size and MTLPixelFormat for the new texture, but it is
 *                              not requred.
 *
 *  @return     A new valid MTLTexture to use as the destination for the MPSKernel. If the calling function
 *              succeeds, its texture parameter will be overwritten with a pointer to this texture. If the
 *              calling function fails (highly unlikely, except for user error) then the texture
 *              will be released before the calling function returns.
 */
    
/* Warning here for ns_returns_retained is clang rdar://problem/20130079 */
typedef id <MTLTexture> __nonnull NS_RETURNS_RETAINED (^MPSCopyAllocator)( MPSKernel * __nonnull filter,
                                                                          id <MTLCommandBuffer> __nonnull commandBuffer,
                                                                          id <MTLTexture> __nonnull sourceTexture);
    

#ifdef __cplusplus
}
#endif


#endif /* MPS_Types_h */

// ==========  MetalPerformanceShaders.framework/Headers/MPSImageMedian.h
/*!
 *  @header MPSImageMedian.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract Metal Image median filters
 */

#ifndef MPS_MPSImageMedian_h
#define MPS_MPSImageMedian_h

#include <MetalPerformanceShaders/MPSImageKernel.h>


/*!
 *  @class      MPSImageMedian
 *  @discussion The MPSImageMedian applies a median filter to an image.  A median filter finds the 
 *              median color value for each channel within a kernelDiameter x kernelDiameter 
 *              window surrounding the pixel of interest.  It is a common means of noise reduction
 *              and also as a smoothing filter with edge preserving qualities.
 *
 *              NOTE: The MPSImageMedian filter currently only supports images with <= 8 bits/channel.
 *
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageMedian : MPSUnaryImageKernel

/*! @property   kernelDiameter
 *  @abstract   The diameter in pixels of the filter window.
 *  @discussion The median filter is applied to a kernelDiameter x kernelDiameter window
 *              of pixels centered on the corresponding source pixel for each destination
 *              pixel.  The kernel diameter must be an odd number.
 */
@property (readonly, nonatomic) NSUInteger kernelDiameter;


/*! @abstract   Initialize a filter for a particular kernel size and device
 *  @param      device          The device the filter will run on
 *  @param      kernelDiameter  Diameter of the median filter. Must be an odd number.
 *  @return     A valid object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        kernelDiameter: (NSUInteger)kernelDiameter   NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:kernelDiameter: instead. */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device    NS_UNAVAILABLE;


/*! @abstract   The maximum diameter in pixels of the filter window supported by the median filter.
 */
+(NSUInteger) maxKernelDiameter;

/*! @abstract   The minimum diameter in pixels of the filter window supported by the median filter.
 */
+(NSUInteger) minKernelDiameter;

@end  /* MPSImageMedian */

#endif  /* MPS_MSImageMedian_h */

// ==========  MetalPerformanceShaders.framework/Headers/MPSImageMorphology.h
/*!
 *  @header MPSImageMorphology.h
 *  @framework MetalPerformanceShaders
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract Metal Image morphological operators
 */

#ifndef MPS_MPSImageMorphology_h
#define MPS_MPSImageMorphology_h

#include <MetalPerformanceShaders/MPSImageKernel.h>


/*!
 *  @class      MPSImageAreaMax
 *  @discussion The MPSImageAreaMax kernel finds the maximum pixel value in a rectangular region centered around each pixel
 *              in the source image. If there are multiple channels in the source image, each channel is processed independently.
 *              The edgeMode property is assumed to always be MPSImageEdgeModeClamp for this filter.
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageAreaMax : MPSUnaryImageKernel

/*! @property kernelHeight
 *  @abstract  The height of the filter window. Must be an odd number.
 */
@property (readonly, nonatomic)   NSUInteger  kernelHeight;

/*! @property kernelWidth
 *  @abstract  The width of the filter window. Must be an odd number.
 */
@property (readonly, nonatomic)   NSUInteger  kernelWidth;

/*!
 *  @abstract Set the kernel height and width
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel. Must be an odd number.
 *  @param      kernelHeight        The height of the kernel. Must be an odd number.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger)kernelWidth
                          kernelHeight: (NSUInteger)kernelHeight            NS_DESIGNATED_INITIALIZER;


/* You must use initWithDevice:kernelWidth:kernelHeight: instead. */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device        NS_UNAVAILABLE;

@end  /* MPSImageAreaMax */

/*!
 *  @class      MPSImageAreaMin
 *  @discussion The MPSImageAreaMin finds the minimum pixel value in a rectangular region centered around each pixel in the
 *               source image. If there are multiple channels in the source image, each channel is processed independently.
 *               It has the same methods as MPSImageAreaMax
 *               The edgeMode property is assumed to always be MPSImageEdgeModeClamp for this filter.
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageAreaMin : MPSImageAreaMax

@end  /* MPSImageAreaMin */

/*!
 *  @class      MPSImageDilate
 *  @discussion The MIDilateFilter finds the maximum pixel value in a rectangular region centered around each pixel in the
 *              source image. It is like the MPSImageAreaMax, except that the intensity at each position is calculated relative
 *              to a different value before determining which is the maximum pixel value, allowing for shaped, non-rectangular
 *              morphological probes.
 *  @code
 *          for each pixel in the filter window:
 *              value =  pixel[filterY][filterX] - filter[filterY*filter_width+filterX]
 *              if( value > bestValue ){
 *                   result = value
 *                   bestValue = value;
 *              }
 *  @endcode
 *              A filter that contains all zeros and is identical to a MPSImageAreaMax filter.  The center filter element
 *              is assumed to be 0 to avoid causing a general darkening of the image.
 *
 *              The edgeMode property is assumed to always be MPSImageEdgeModeClamp for this filter.
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageDilate : MPSUnaryImageKernel
/*! @property kernelHeight
 *  @abstract  The height of the filter window. Must be an odd number.
 */
@property (readonly, nonatomic)   NSUInteger  kernelHeight;

/*! @property kernelWidth
 *  @abstract  The width of the filter window. Must be an odd number.
 */
@property (readonly, nonatomic)   NSUInteger  kernelWidth;


/*!
 *  @abstract   Init a object with kernel height, width and weight values.
 *  @discussion Each dilate shape probe defines a 3D surface of values.
 *              These are arranged in order left to right, then top to bottom
 *              in a 1D array. (values[kernelWidth*y+x] = probe[y][x])
 *              Values should be generally be in the range [0,1] with the center 
 *              pixel tending towards 0 and edges towards 1. However, any numerical
 *              value is allowed. Calculations are subject to the usual floating-point
 *              rounding error.
 *
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel. Must be an odd number.
 *  @param      kernelHeight        The height of the kernel. Must be an odd number.
 *  @param      values              The set of values to use as the dilate probe.
 *                                  The values are copied into the filter. To avoid 
 *                                  image ligthening or darkening, the center value should
 *                                  be 0.0f.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger)kernelWidth
                          kernelHeight: (NSUInteger)kernelHeight
                                values: (nonnull const float*) values       NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:kernelWidth:kernelHeight:values: instead. */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device        NS_UNAVAILABLE;

@end  /* MPSImageDilate */


/*!
 *  @class      MPSImageErode
 *  @discussion The MPSImageErode filter finds the minimum pixel value in a rectangular region centered around each pixel in the
 *              source image. It is like the MPSImageAreaMin, except that the intensity at each position is calculated relative
 *              to a different value before determining which is the maximum pixel value, allowing for shaped, non-rectangular
 *              morphological probes.
 *  @code
 *          for each pixel in the filter window:
 *              value =  pixel[filterY][filterX] + filter[filterY*filter_width+filterX]
 *              if( value < bestValue ){
 *                   result = value
 *                   bestValue = value;
 *              }
 *  @endcode
 *              A filter that contains all zeros is identical to a MPSImageAreaMin filter. The center filter element
 *              is assumed to be 0, to avoid causing a general lightening of the image.
 *
 *              The definition of the filter for MPSImageErode is different from vImage. (MIErode_filter_value = 1.0f-vImageErode_filter_value.)
 *              This allows MPSImageDilate and MPSImageErode to use the same filter, making open and close operators easier to write.
 *              The edgeMode property is assumed to always be MPSImageEdgeModeClamp for this filter.
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageErode : MPSImageDilate
@end

#endif  /* MPS_MSImageMorphology_h */
// ==========  MetalPerformanceShaders.framework/Headers/MPSImageTranspose.h
/*!
 *  @header MPSImageTranspose.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract Metal Image transpose filters
 */

#ifndef MPS_MPSImageTranspose_h
#define MPS_MPSImageTranspose_h

#include <MetalPerformanceShaders/MPSImageKernel.h>

/*!
 *  @class      MPSImageTranspose
 *  @discussion The MPSImageTranspose transposes an image
 *
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageTranspose : MPSUnaryImageKernel

@end    /* MPSImageTranspose */


#endif  /* MPS_MSImageTranspose_h */

// ==========  MetalPerformanceShaders.framework/Headers/MPSImageConvolution.h
/*!
 *  @header MPSImageConvolution.h
 *  @framework MetalPerformanceShaders
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *
 *  @abstract MetalPerformanceShaders Convolution Filters
 */

#ifndef MPS_MSImageConvolution_h
#define MPS_MSImageConvolution_h

#include <MetalPerformanceShaders/MPSImageKernel.h>

/*!
 *  @class      MPSImageConvolution
 *  @discussion The MPSImageConvolution convolves an image with given filter of odd width and height.
 *              Filter width/height can be either 3,5,7 or 9.
 *              For a separable filter, it will be more performant to run this filter as a 1-dimensional
 *              filter in each dimension separately.
 *              If there are multiple channels in the source image, each channel is processed independently.
 *  
 *  @performance Separable convolution filters may perform better when done in two passes. A convolution filter
 *              is separable if the ratio of filter values between all rows is constant over the whole row. For
 *              example, this edge detection filter:
 *                  @code
 *                      -1      0       1
 *                      -2      0       2
 *                      -1      0       1
 *                  @endcode
 *              can be separated into the product of two vectors:
 *                  @code
 *                      1
 *                      2      x    [-1  0   1]
 *                      1
 *                  @endcode
 *              and consequently can be done as two, one-dimensional convolution passes back to back on the same image. 
 *              In this way, the number of multiplies (ignoring the fact that we could skip zeros here) is reduced from
 *              3*3=9 to 3+3 = 6. There are similar savings for addition. For large filters, the savings can be profound.
 *
 */

NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageConvolution : MPSUnaryImageKernel

/*! @property kernelHeight
 *  @abstract  The height of the filter window. Must be an odd number.
 */
@property (readonly, nonatomic)   NSUInteger  kernelHeight;

/*! @property kernelWidth
 *  @abstract  The width of the filter window. Must be an odd number.
 */
@property (readonly, nonatomic)   NSUInteger  kernelWidth;


/*! @property    bias
 *  @discussion  The bias is a value to be added to convolved pixel before it is converted back to the storage format.
 *               It can be used to convert negative values into a representable range for a unsigned MTLPixelFormat.
 *               For example, many edge detection filters produce results in the range [-k,k]. By scaling the filter
 *               weights by 0.5/k and adding 0.5, the results will be in range [0,1] suitable for use with unorm formats. 
 *               It can be used in combination with renormalization of the filter weights to do video ranging as part 
 *               of the convolution effect. It can also just be used to increase the brightness of the image.
 *
 *               Default value is 0.0f.
 */
@property (readwrite, nonatomic) float bias;

/*!
 *  @abstract  Initialize a convolution filter
 *  @param      device          The device the filter will run on
 *  @param      kernelWidth     the width of the kernel
 *  @param      kernelHeight    the height of the kernel
 *  @param      kernelWeights   A pointer to an array of kernelWidth * kernelHeight values to be used as the kernel.
 *                              These are in row major order.
 *  @return     A valid MPSImageConvolution object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger)kernelWidth
                          kernelHeight: (NSUInteger)kernelHeight
                               weights: (nonnull const float*)kernelWeights     NS_DESIGNATED_INITIALIZER;


@end


/*!
 *  @class      MPSImageBox
 *  @discussion The MPSImageBox convolves an image with given filter of odd width and height. The kernel elements
 *              all have equal weight, achieving a blur effect. (Each result is the unweighted average of the
 *              surrounding pixels.) This allows for much faster algorithms, espcially for for larger blur radii.
 *              The box height and width must be odd numbers. The box blur is a separable filter. The implementation 
 *              is aware of this and will act accordingly to give best performance for multi-dimensional blurs.
 */

NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageBox : MPSUnaryImageKernel


/*! @property kernelHeight
 *  @abstract  The height of the filter window.
 */
@property (readonly, nonatomic)   NSUInteger  kernelHeight;

/*! @property kernelWidth
 *  @abstract  The width of the filter window.
 */
@property (readonly, nonatomic)   NSUInteger  kernelWidth;

/*! @abstract   Initialize a filter for a particular kernel size and device
 *  @param      device  The device the filter will run on
 *  @param      kernelWidth  the width of the kernel.  Must be an odd number.
 *  @param      kernelHeight the height of the kernel. Must be an odd number.
 *  @return     A valid object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger)kernelWidth
                          kernelHeight: (NSUInteger)kernelHeight        NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:kernelWidth:kernelHeight: instead. */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device    NS_UNAVAILABLE;
@end

/*!
 *  @class      MPSImageTent
 *  @discussion The box filter, while fast, may yield square-ish looking blur effects. However, multiple
 *              passes of the box filter tend to smooth out with each additional pass. For example, two 3-wide
 *              box blurs produces the same effective convolution as a 5-wide tent blur:
 *              @code
 *                      1   1   1
 *                          1   1   1
 *                      +       1   1   1
 *                      =================
 *                      1   2   3   2   1
 *              @endcode
 *              Addition passes tend to approximate a gaussian line shape.
 *
 *              The MPSImageTent convolves an image with a tent filter. These form a tent shape with incrementally
 *              increasing sides, for example:
 *
 *                  1   2   3   2   1
 *
 *
 *                  1   2   1
 *                  2   4   2
 *                  1   2   1
 *
 *              Like the box filter, this arrangement allows for much faster algorithms, espcially for for larger blur
 *              radii but with a more pleasing appearance.
 *
 *              The tent blur is a separable filter. The implementation is aware of this and will act accordingly
 *              to give best performance for multi-dimensional blurs.
 */
@interface MPSImageTent : MPSImageBox

@end

/*!
 *  @class      MPSImageGaussianBlur
 *  @discussion The MPSImageGaussianBlur convolves an image with gaussian of given sigma in both x and y direction.
 *
 *                  The MPSImageGaussianBlur utilizes a very fast algorith that typically runs at approximately
 *                  1/2 of copy speeds. Notably, it is faster than either the tent or box blur except perhaps
 *                  for very large filter windows. Mathematically, it is an approximate gaussian. Some
 *                  non-gaussian behavior may be detectable with advanced analytical methods such as FFT.  
 *                  If a analytically clean gaussian filter is required, please use the MPSImageConvolution 
 *                  filter instead with an appropriate set of weights. The MPSImageGaussianBlur is intended
 *                  to be suitable for all common image processing needs demanding ~10 bits of precision or
 *                  less.
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageGaussianBlur : MPSUnaryImageKernel

/*! @abstract   Initialize a gaussian blur filter for a particular sigma and device
 *  @param      device  The device the filter will run on
 *  @param      sigma   The standard deviation of gaussian blur filter. 
 *                      Gaussian weight, centered at 0, at integer grid i is given as 
 *                            w(i) = 1/sqrt(2*pi*sigma) * exp(-i^2/2*sigma^2)
 *                      If we take cut off at 1% of w(0) (max weight) beyond which weights
 *                      are considered 0, we have 
 *                              ceil (sqrt(-log(0.01)*2)*sigma) ~ ceil(3.7*sigma) 
 *                      as rough estimate of filter width
 *  @return     A valid object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                 sigma: (float)sigma                   NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:sigma: instead. */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device    NS_UNAVAILABLE;

/*! @property sigma
 *  @abstract Read-only sigma value with which filter was created
 */
@property (readonly, nonatomic) float sigma;

@end

/*!
 *  @class      MPSImageSobel
 *  @discussion The MPSImageSobel implements the Sobel filter.
 *              When the color model (e.g. RGB, two-channel, grayscale, etc.) of source 
 *              and destination textures match, the filter is applied to each channel 
 *              separately. If the destination is monochrome (single channel) but source 
 *              multichannel, the pixel values are converted to grayscale before applying Sobel
 *              operator using the linear gray color transform vector (v).
 *
 *                  Luminance = v[0] * pixel.x + v[1] * pixel.y + v[2] * pixel.z;
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageSobel : MPSUnaryImageKernel

/*! @abstract   Initialize a Sobel filter on a given device using the default color 
 *              transform. Default: BT.601/JPEG {0.299f, 0.587f, 0.114f}
 *
 *              For non-default conversion matrices, use -initWithDevice:linearGrayColorTransform:
 *
 *  @param      device  The device the filter will run on
 *  @return     A valid object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device;

/*! @abstract   Initialize a Sobel filter on a given device with a non-default color transform
 *  @param      device          The device the filter will run on
 *  @param      transform       Array of three floats describing the rgb to gray scale color transform.
 *
 *                          Luminance = transform[0] * pixel.x + transform[1] * pixel.y + transform[2] * pixel.z;
 *
 *  @return     A valid object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
              linearGrayColorTransform: (nonnull const float *) transform      NS_DESIGNATED_INITIALIZER;

/*! @property    colorTransform
 *  @discussion  Returns a pointer to the array of three floats used to convert RGBA, RGB or RG images
 *               to the destination format when the destination is monochrome.
 */
@property (readonly, nonatomic, nonnull) const float* colorTransform;

@end  /* MPSImageSobel */

#endif    /* MPS_MSImageConvolution_h */
// ==========  MetalPerformanceShaders.framework/Headers/MPSImageHistogram.h
/*!
 *  @header MPSImageHistogram.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract Metal Image histogram filters
 */

#ifndef MPS_MPSImageHistogram_h
#define MPS_MPSImageHistogram_h

#include <MetalPerformanceShaders/MPSImageKernel.h>
#include <simd/simd.h>

/*!
 *  @brief      Specifies information to compute the histogram for channels of an image.
 */
typedef struct
{
    NSUInteger      numberOfHistogramEntries;   /**<  Specifies the number of histogram entries, or "bins" for each channel.  For example, if you want 256 histogram bins then numberOfHistogramEntries must be set to 256.  The value stored in each histogram bin is a 32-bit unsigned integer.  The size of the histogram buffer in which these bins will be stored should be >= numberOfHistogramEntries * sizeof(uint32_t) * number of channels in the image. numberOfHistogramEntries must be a power of 2 and is a minimum of 256 bins.   */
    BOOL            histogramForAlpha;          /**<  Specifies whether the histogram for the alpha channel should be computed or not. */
    vector_float4   minPixelValue;              /**<  Specifies the minimum pixel value.  Any pixel value less than this will be clipped to this value (for the purposes of histogram calculation), and assigned to the first histogram entry. This minimum value is applied to each of the four channels separately. */
    vector_float4   maxPixelValue;              /**<  Specifies the maximum pixel value.  Any pixel value greater than this will be clipped to this value (for the purposes of histogram calculation), and assigned to the first histogram entry. This maximum value is applied to each of the four channels separately. */
} MPSImageHistogramInfo;

/*!
 *  @class      MPSImageHistogram
 *  @discussion The MPSImageHistogram computes the histogram of an image.
 *              
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageHistogram : MPSKernel

/*! @property   clipRectSource
 *  @abstract   The source rectangle to use when reading data.
 *  @discussion A MTLRegion that indicates which part of the source to read. If the clipRectSource does not lie
 *              completely within the source image, the intersection of the image bounds and clipRectSource will
 *              be used. The clipRectSource replaces the MPSUnaryImageKernel origin parameter for this filter.
 *              The latter is ignored.   Default: MPSRectNoClip, use the entire source texture.
 */
@property (readwrite, nonatomic) MTLRegion clipRectSource;

/*! @property   zeroHistogram
 *  @abstract   Zero-initalize the histogram results
 *  @discussion Indicates that the memory region in which the histogram results are to be written in the
 *              histogram buffer are to be zero-initialized or not. Default: YES.
 */
@property (readwrite, nonatomic) BOOL zeroHistogram;

/*! @property   histogramInfo
 *  @abstract   Return a structure describing the histogram content
 *  @discussion Returns a MPSImageHistogramInfo structure describing the format of the
 *              histogram.
 */
@property (readonly, nonatomic)  MPSImageHistogramInfo histogramInfo;

/*!
 *  @abstract Specifies information to compute the histogram for channels of an image.
 *  @param    device            The device the filter will run on
 *  @param    histogramInfo     Pointer to the MPSHistogramInfo struct
 *  @return     A valid MPSImageHistogram object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                         histogramInfo: (nonnull const MPSImageHistogramInfo *) histogramInfo     NS_DESIGNATED_INITIALIZER;


/*!
 *  @abstract Encode the filter to a command buffer using a MTLComputeCommandEncoder.
 *  @discussion The filter will not begin to execute until after the command
 *  buffer has been enqueued and committed.
 *
 *
 *  @param  commandBuffer           A valid MTLCommandBuffer.
 *  @param  source                  A valid MTLTexture containing the source image for the filter
 *  @param  histogram               A valid MTLBuffer to receive the histogram results.
 *  @param  histogramOffset         Byte offset into histogram buffer at which to write the histogram results. Must be a multiple of 32 bytes.
 *                                  The histogram results / channel are stored together.  The number of channels for which
 *                                  histogram results are stored is determined by the number of channels in the image.
 *                                  If histogramInfo.histogramForAlpha is false and the source image is RGBA then only histogram
 *                                  results for RGB channels are stored.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                sourceTexture: (nonnull id <MTLTexture>) source
                    histogram: (nonnull id <MTLBuffer>) histogram
              histogramOffset: (NSUInteger) histogramOffset;


/*!
 *  @abstract   The amount of space in the output MTLBuffer the histogram will take up.
 *  @discussion This convenience function calculates the minimum amount of space
 *              needed in the output histogram for the results.  The MTLBuffer should
 *              be at least this length, longer if histogramOffset is non-zero.
 *  @param      sourceFormat      The MTLPixelFormat of the source image. This is
 *                                the source parameter of -encodeToCommandBuffer:
 *                                sourceTexture:histogram:histogramOffset
 *  @return     The number of bytes needed to store the result histograms.
 */
-(size_t) histogramSizeForSourceFormat: (MTLPixelFormat) sourceFormat;


@end  /* MPSImageHistogram */

/*!
 *  @class      MPSImageHistogramEqualization
 *  @discussion The MPSImageHistogramEqualization performs equalizes the histogram of an image.
 *              The process is divided into three steps. 
 *
 *              -# Call -initWithDevice:histogramInfo:   This creates a MPSImageHistogramEqualization
 *              object.   It is done when the method returns.
 *  
 *              -# Call -encodeTransform:sourceTexture:histogram:histogramOffset:  This creates a privately held
 *              image transform (i.e. a cumulative distribution function of the histogram) which will be used to 
 *              equalize the distribution of the histogram of the source image. This process runs on a MTLCommandBuffer
 *              when it is committed to a MTLCommandQueue. It must complete before the next step can be run.
 *              It may be performed on the same MTLCommandBuffer.  The histogram argument specifies the histogram
 *              buffer which contains the histogram values for sourceTexture.  The sourceTexture argument is used by
 *              encodeTransform to determine the number of channels and therefore which histogram data in histogram 
 *              buffer to use. The histogram for sourceTexture must have been computed either on the CPU or using 
 *              the MPSImageHistogram kernel
 *
 *              -# Call -encodeToCommandBuffer:sourceTexture:destinationTexture: to read data from
 *              sourceTexture, apply the equalization transform to it and write to destination texture.
 *              This step is also done on the GPU on a MTLCommandQueue.
 *
 *              You can reuse the same equalization transform on other images to perform the
 *              same transform on those images. (Since their distribution is probably different,
 *              they will probably not be equalized by it.) This filter usually will not be able 
 *              to work in place.
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageHistogramEqualization : MPSUnaryImageKernel

/*! @property   histogramInfo
 *  @abstract   Return a structure describing the histogram content
 *  @discussion Returns a MPSImageHistogramInfo structure describing the format of the
 *              histogram.
 */
@property (readonly, nonatomic)  MPSImageHistogramInfo histogramInfo;

/*!
 *  @abstract Specifies information about the histogram for the channels of an image.
 *  @param    device            The device the filter will run on
 *  @param    histogramInfo     Pointer to the MPSHistogramInfo struct
 *  @return     A valid MPSImageHistogramEqualization object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                         histogramInfo: (nonnull const MPSImageHistogramInfo *) histogramInfo     NS_DESIGNATED_INITIALIZER;

/*!
 *  @abstract Encode the transform function to a command buffer using a MTLComputeCommandEncoder.
 *            The transform function computes the equalization lookup table.
 *  @discussion The transform function will not begin to execute until after the command
 *              buffer has been enqueued and committed.  This step will need to be repeated
 *              with the new MPSKernel if -copyWithZone:device or -copyWithZone: is called.
 *              The transform is stored as internal state to the object. You still need to 
 *              call -encodeToCommandBuffer:sourceTexture:destinationTexture: afterward
 *              to apply the transform to produce a result texture.
 *
 *  @param  commandBuffer   A valid MTLCommandBuffer.
 *  @param  source          A valid MTLTexture containing the source image for the filter.
 *  @param  histogram       A valid MTLBuffer containing the histogram results for an image.  This filter
 *                          will use these histogram results to generate the cumulative histogram for equalizing
 *                          the image.  The histogram results / channel are stored together.  The number of channels
 *                          for which histogram results are stored is determined by the number of channels in the image.
 *                          If histogramInfo.histogramForAlpha is false and the source image is RGBA then only histogram
 *                          results for RGB channels are stored.
 *  @param  histogramOffset A byte offset into the histogram MTLBuffer where the histogram starts. Must conform to
 *                          alignment requirements for [MTLComputeCommandEncoder setBuffer:offset:atIndex:] offset
 *                          parameter.
 */
 -(void) encodeTransformToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                          sourceTexture: (nonnull id <MTLTexture>) source
                              histogram: (nonnull id <MTLBuffer>) histogram
                        histogramOffset: (NSUInteger) histogramOffset;



@end  /* MPSImageHistogramEqualization */

/*!
 *  @class      MPSImageHistogramSpecification
 *  @discussion The MPSImageHistogramSpecification performs a histogram specification operation on an image.
 *              It is a generalized version of histogram equalization operation.  The histogram specificaiton filter
 *              converts the image so that its histogram matches the desired histogram.
 *
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageHistogramSpecification : MPSUnaryImageKernel

/*! @property   histogramInfo
 *  @abstract   Return a structure describing the histogram content
 *  @discussion Returns a MPSImageHistogramInfo structure describing the format of the
 *              histogram.
 */
@property (readonly, nonatomic)  MPSImageHistogramInfo histogramInfo;

/*!
 *  @abstract Specifies information about the histogram for the channels of an image.
 *  @discussion The MPSImageHistogramSpecification applies a transfor to convert the histogram 
 *              to a specified histogram. The process is divided into three steps:
 *
 *              -# Call -initWithDevice:histogramInfo:   This creates a MPSImageHistogramSpecification
 *              object.  It is done when the method returns.
 *
 *              -# Call -encodeTransform:sourceTexture:sourceHistogram:sourceHistogramOffset:desiredHistogram:
 *              desiredHistogramOffset: This creates a privately held image transform which will convert the
 *              the distribution of the source histogram to the desired histogram. This process runs on a 
 *              MTLCommandBuffer when it is committed to a MTLCommandQueue. It must complete before the next 
 *              step can be run. It may be performed on the same MTLCommandBuffer.  The sourceTexture argument 
 *              is used by encodeTransform to determine the number of channels and therefore which histogram data 
 *              in sourceHistogram buffer to use. The sourceHistogram and desiredHistogram must have been computed 
 *              either on the CPU or using the MPSImageHistogram kernel
 *
 *              -# Call -encodeToCommandBuffer:sourceTexture:destinationTexture: to read data from
 *              sourceTexture, apply the transform to it and write to destination texture.
 *              This step is also done on the GPU on a MTLCommandQueue.
 *
 *              You can reuse the same specification transform on other images to perform the
 *              same transform on those images. (Since their starting distribution is probably
 *              different, they will probably not arrive at the same distribution as the desired
 *              histogram.) This filter usually will not be able to work in place.
 *
 *  @param    device            The device the filter will run on
 *  @param    histogramInfo     Pointer to the MPSHistogramInfo struct
 *  @return     A valid MPSImageHistogramSpecification object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                         histogramInfo: (nonnull const MPSImageHistogramInfo *) histogramInfo     NS_DESIGNATED_INITIALIZER;


/*!
 *  @abstract Encode the transform function to a command buffer using a MTLComputeCommandEncoder.
 *            The transform function computes the specification lookup table.
 *  @discussion The transform function will not begin to execute until after the command
 *              buffer has been enqueued and committed. This step will need to be repeated
 *              with the new MPSKernel if -copyWithZone:device or -copyWithZone: is called.
 *
 *  @param  commandBuffer   A valid MTLCommandBuffer.
 *  @param  source          A valid MTLTexture containing the source image for the filter.
 *  @param  sourceHistogram A valid MTLBuffer containing the histogram results for the source image.  This filter
 *                          will use these histogram results to generate the cumulative histogram for equalizing
 *                          the image.  The histogram results / channel are stored together.  The number of channels
 *                          for which histogram results are stored is determined by the number of channels in the image.
 *                          If histogramInfo.histogramForAlpha is false and the source image is RGBA then only histogram
 *                          results for RGB channels are stored.
 *  @param  sourceHistogramOffset   A byte offset into the sourceHistogram MTLBuffer where the histogram starts. Must conform to
 *                                  alignment requirements for [MTLComputeCommandEncoder setBuffer:offset:atIndex:] offset
 *                                  parameter.
 *  @param  desiredHistogram    A valid MTLBuffer containing the desired histogram results for the source image.
 *                          The histogram results / channel are stored together.  The number of channels
 *                          for which histogram results are stored is determined by the number of channels in the image.
 *                          If histogramInfo.histogramForAlpha is false and the source image is RGBA then only histogram
 *                          results for RGB channels are stored.
 *  @param  desiredHistogramOffset  A byte offset into the desiredHistogram MTLBuffer where the histogram starts. Must conform to
 *                                  alignment requirements for [MTLComputeCommandEncoder setBuffer:offset:atIndex:] offset
 *                                  parameter.
 */
-(void) encodeTransformToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                         sourceTexture: (nonnull id <MTLTexture>) source
                       sourceHistogram: (nonnull id <MTLBuffer>) sourceHistogram
                 sourceHistogramOffset: (NSUInteger) sourceHistogramOffset
                      desiredHistogram: (nonnull id <MTLBuffer>) desiredHistogram
                desiredHistogramOffset: (NSUInteger) desiredHistogramOffset;



@end  /* MPSImageHistogramSpecification */

#endif  /* MPS_MSImageHistogram_h */

