// ==========  Vision.framework/Headers/VNRequestRevisionProviding.h
//
//  VNRequestRevisionProviding.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
@protocol VNRequestRevisionProviding
@required

/*!
	@brief	The revision of the VNRequest subclass that was used to generate the object that implements this protocol.
 */
@property (readonly, nonatomic, assign) NSUInteger requestRevision;

@end


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNDetectFaceCaptureQualityRequest.h
//
//  VNDetectFaceCaptureQualityRequest.h
//  Vision
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNFaceObservationAccepting.h>


NS_ASSUME_NONNULL_BEGIN


/*!
 @brief A request that will produce or update a VNFaceObservation's property faceCaptureQuality with a float value.
 faceCaptureQuality is a float (wrapped by a NSNumber) that represents the capture quality of a given face in a photo.
 The float will be a value between 0 and 1, with 1 being the highest face capture quality and 0 being the lowest.
 If the request fails or the face observation has never been processed, the property faceCaptureQuality will be nil.
 
 @details This request will generate VNFaceObservation objects with the face quality variable populated with information .
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNDetectFaceCaptureQualityRequest : VNImageBasedRequest <VNFaceObservationAccepting>
@end

API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNDetectFaceCaptureQualityRequestRevision1 = 1;

API_DEPRECATED_WITH_REPLACEMENT("Use VNDetectFaceCaptureQualityRequestRevision1 instead", macos(10.15, 10.15), ios(13.0, 13.0), tvos(13.0, 13.0))
static const NSUInteger VNDetectFaceQualityRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNClassifyImageRequest.h
//
//  VNClassifyImageRequest.h
//  Vision
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN


@class VNClassificationObservation;


/*!
	@brief A request for classifying an image.

	@discussion This request will produce a collection of VNClassificationObservation objects which describe an image.
*/
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNClassifyImageRequest : VNImageBasedRequest

/*!
	@brief Obtain the collection of classifications currently recognized by the Vision framework.
 
	@param	requestRevision		The revision of the request for which classifications should be reported.
 
	@param	error				The address of the variable that will be populated with the error when the call fails.

	@return the collection of classifications for the revision, or nil if an error was encountered.
*/
+ (nullable NSArray<VNClassificationObservation*>*) knownClassificationsForRevision:(NSUInteger)requestRevision error:(NSError**)error;


@end



API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNClassifyImageRequestRevision1 = 1;



NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNFaceObservationAccepting.h
//
//  VNFaceObservationAccepting.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN


@class VNFaceObservation;


/*!
	@brief A protocol that allows a user to provide an input collection of VNFaceObservations as part of a request. The protocol can be adopted by request objects that request additional information about detected faces, such as facial landmarks. 
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@protocol VNFaceObservationAccepting < NSObject >
@required

/*!
	@brief	The VNFaceObservation objects to be processed as part of the request.
*/
@property (readwrite, nonatomic, copy, nullable) NSArray<VNFaceObservation *> *inputFaceObservations;

@end


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNFaceLandmarks.h
//
//  VNFaceLandmarks.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>
#import <Vision/VNDefines.h>
#import <Vision/VNTypes.h>
#import <simd/simd.h>

#import <Vision/VNRequestRevisionProviding.h>


NS_ASSUME_NONNULL_BEGIN


/*!
 @class VNFaceLandmarkRegion
 @brief VNFaceLandmarkRegion the object acting as a collection of landmark points for defining a specific region of the face (including potentially all of the landmark points for a face). The VNFaceLandmarkRegion is an abstract base class.
 */

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNFaceLandmarkRegion : NSObject<NSCopying, NSSecureCoding, VNRequestRevisionProviding>

- (instancetype) init NS_UNAVAILABLE;

/*!
 @brief pointCount returns the amount of points in a given region. This can be zero if no points for a region could be found.
 */
@property (readonly) NSUInteger pointCount;

@end


/*!
 @class VNFaceLandmarkRegion2D
 @brief VNFaceLandmarkRegion2D gives access to the 2D landmark points for the region. The points are stored as vector_float2 and must not be modified.
 */

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNFaceLandmarkRegion2D : VNFaceLandmarkRegion

/*!
	@brief	Obtains the array of normalized landmark points.
 
	@discussion	Provides the address of a buffer containing the array of CGPoints representing the landmark points.  This buffer is owned by the target object and is guaranteed to exist as long as the VNFaceLandmarkRegion2D does.

	@return the address of the array of pointCount points.
*/
@property (readonly, assign, nullable) const CGPoint* normalizedPoints NS_RETURNS_INNER_POINTER;


/*!
	@brief	Provides the array of landmark points in the coordinate space of a specific image size.
	
	@discussion	Provides the address of a buffer containing the array of CGPoints representing the landmark points in the coordinate space of a specific image size.  This buffer is owned by the target object and is guaranteed to exist as long as the VNFaceLandmarkRegion2D does.

	@param	imageSize			The pixel dimensions of the image in which the landmark points are being presented.
	
	@return the address of the array of pointCount points, or NULL if the conversion could not take place.
*/
- (const CGPoint*) pointsInImageOfSize:(CGSize)imageSize NS_RETURNS_INNER_POINTER;


/*!
 @brief    Obtains the array of accuracy placement estimates per landmark point.
 
 @discussion    Provides the NSArray object containing landmarks accuracy placement estimates per landmark point. This property is only
                populated when VNDetectFaceLandmarksRequest object is configured with VNRequestFaceLandmarksConstellation76Points. It is
                set to nil for other constellations
 
 @return NSArray object of NSNumber(s) initialized to floating point values.
 */
@property (readonly, nullable) NSArray<NSNumber*>* precisionEstimatesPerPoint API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));


/*!
 @brief    Obtains the array of boolean occlusion flags per landmark point.
 
 @discussion    Provides the NSArray object containing landmarks occlusion flags per landmark point.  This property is only
                populated when VNDetectFaceLandmarksRequest object is configured with VNRequestFaceLandmarksConstellation76Points. It is
                set to nil for other constellations
 
 @return NSArray object of NSNumber(s) initialized to Boolean values.
 */
@property (readonly, nullable) NSArray<NSNumber*>* occlusionFlagsPerPoint API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));


@end



/*!
 @class VNFaceLandmarks
 @brief VNFaceLandmarks2D is the result of a face landmarks request. It is an abstract base class.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNFaceLandmarks : NSObject<NSCopying, NSSecureCoding, VNRequestRevisionProviding>

- (instancetype) init NS_UNAVAILABLE;

/*!
 @brief a confidence estimate for the returned landmarks.
 */
@property (readonly) VNConfidence confidence;

@end



/*!
 @class VNFaceLandmarks2D
 @brief VNFaceLandmarks2D is the result of a face landmarks 2D request, containing detected facial landmark points organized into VNFaceLandmarkRegion2D regions. The points are accessible as a full list, or as sub-gruops representing pre-defined facial regions.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNFaceLandmarks2D : VNFaceLandmarks
/*!
 @brief allPoints the region containing all face landmark points.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *allPoints;

/*!
 @brief faceContour the region containing the points that describe the face contour from cheek over chin to cheek.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *faceContour;

/*!
 @brief leftEye the region containing the points describing the outline of the left eye.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *leftEye;

/*!
 @brief rightEye the region containing the points describing the outline of the right eye.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *rightEye;

/*!
 @brief leftEyebrow the region containing the points describing the trace of the left eyebrow.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *leftEyebrow;

/*!
 @brief rightEyebrow the region containing the points describing the trace of the right eyebrow.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *rightEyebrow;

/*!
 @brief nose the region containing the points describing the outline of the nose.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *nose;

/*!
 @brief noseCrest the region containing the points describing the trace of the center crest of the nose.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *noseCrest;

/*!
 @brief medianLine the region containing the points describing the trace of the center line of the face.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *medianLine;

/*!
 @brief outer lips the region containing the points describing the outline of the outside of the lips.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *outerLips;

/*!
 @brief innerLips the region containing the points describing the outline of the space between the of the lips.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *innerLips;

/*!
 @brief leftPupil the region containing the point where the left pupil is located.  This value may be inaccurate if
 the face isBlinking.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *leftPupil;

/*!
 @brief rightPupil the region containing the point where the right pupil is located.  This value may be inaccurate if
 the face isBlinking.
 */
@property (readonly, nullable) VNFaceLandmarkRegion2D *rightPupil;


@end


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNCoreMLRequest.h
//
//  VNCoreMLRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <CoreML/CoreML.h>

#import <Vision/VNRequest.h>
#import <Vision/VNTypes.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief The VNCoreMLModel uses an CoreML based model and prepares it for use with VNCoreMLRequests.
 */

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNCoreMLModel : NSObject

- (instancetype) init  NS_UNAVAILABLE;

/*!
	@brief Create a model container to be used with VNCoreMLRequest based on a Core ML model. This can fail if the model is not supported. Examples for a model that is not supported is a model that does not take an image as any of its inputs.
 
	@param model	The MLModel from CoreML to be used.
	
	@param	error	Returns the error code and description, if the model is not supported.
 */

+ (nullable instancetype) modelForMLModel:(MLModel*)model error:(NSError**)error;

/*!
 @brief The name of the MLFeatureValue that Vision will set from the VNRequestHandler. Vision will use the first input it finds by default but it can be set to another featureName instead.
 */
@property (readwrite, nonatomic, copy) NSString *inputImageFeatureName API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));


/*!
 @brief An optional object conforming to the MLFeatureProvider protocol that is used by the model during the predict call to support inputs that are not supplied by Vision. Vision will provide the image for the inputImageFeatureName from the the VNRequestHandler. A feature provider is necessary for models that have more than one input and require those parameters to be set. Models that only have one image input will not use the feature provider as that input will be set by Vision.
 */
@property (readwrite, nonatomic, nullable) id<MLFeatureProvider> featureProvider API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

@end

/*!
	@brief   The VNCoreMLRequest uses a VNCoreMLModel, that is based on a CoreML MLModel object, to run predictions with that model. Depending on the model the returned
             observation is either a VNClassificationObservation for classifier models, VNPixelBufferObservations for image-to-image models, VNRecognizedObjectObservation for object recognition models or VNCoreMLFeatureValueObservation for everything else.
 */

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNCoreMLRequest : VNImageBasedRequest

/*!
 @brief The model from CoreML wrapped in a VNCoreMLModel.
 */
@property (readonly, nonatomic) VNCoreMLModel *model;

@property (nonatomic)VNImageCropAndScaleOption imageCropAndScaleOption;


/*!
	@brief Create a new request with a model.
 
	@param model		The VNCoreMLModel to be used.
 */
- (instancetype) initWithModel:(VNCoreMLModel *)model;

/*!
	@brief Create a new request with a model.
 
	@param model		The VNCoreMLModel to be used.
	
	@param	completionHandler	The block that is invoked when the request has been performed.
 */
- (instancetype) initWithModel:(VNCoreMLModel *)model completionHandler:(nullable VNRequestCompletionHandler)completionHandler NS_DESIGNATED_INITIALIZER;


- (instancetype) init  NS_UNAVAILABLE;
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler NS_UNAVAILABLE;


@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNCoreMLRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNTrackingRequest.h
//
//  VNTrackingRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN


@class VNDetectedObjectObservation;


/*!
 @brief    Tracking level options to favor speed or location accuracy. The VNRequestTrackingLevelFast is the default option used by trackers.   
 */
typedef NS_ENUM(NSUInteger, VNRequestTrackingLevel)
{
    VNRequestTrackingLevelAccurate = 0,
    VNRequestTrackingLevelFast
};


/*!
	@abstract	A base class for all tracking requests.
	@discussion	Since this class is not meant to be directly instantiated, no initializers are available.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNTrackingRequest : VNImageBasedRequest

/*!
 @property property inputObservation
 @abstract The observation object that defines a region to track. Providing an observation not returned from a tracker (e.g. user-defined, or from a detector) begins a new tracker for the sequence. Providing an observation that was returned from a tracker continues the use of that tracker, to track the region to the next frame. In general, unless documented in the request's documentation, the rectangle must be defined in normalized coordinates (both dimensions normalized to [0,1] with the origin at the lower-left corner).
*/
@property (readwrite, nonatomic, strong) VNDetectedObjectObservation * inputObservation;

/*!
 @property property trackingLevel
 @abstract Tracking level allows tuning tracking algorithm to prefer speed (VNRequestTrackingLevelFast) vs. tracking object location accuracy (VNRequestTrackingLevelAccurate). This property has no effect on general purpose object tracker (VNTrackObjectRequest) revision 2 (VNTrackObjectRequestRevision2)
 */
@property (readwrite, nonatomic, assign) VNRequestTrackingLevel trackingLevel;

/*!
 @property property lastFrame
 @abstract This property allows marking the last frame for tracking using current tracker. If set to YES, the results for this frame will be processed and returned and the current tracker will be released to the pool of available trackers
 */
@property (readwrite, nonatomic, assign, getter=isLastFrame) BOOL lastFrame;

- (instancetype) init   NS_UNAVAILABLE;
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler   NS_UNAVAILABLE;

@end


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNDetectTextRectanglesRequest.h
//
//  VNDetectTextRectanglesRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A request that will detect regions of text in an image.

	@details This request will generate VNTextObservation objects describing the locations of text detected in an image.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNDetectTextRectanglesRequest : VNImageBasedRequest

/*!
	@brief Specify whether or not the bounding boxes of individual characters should also be returned in the resultant VNTextObservations. Default is NO.
*/
@property (readwrite, nonatomic, assign) BOOL reportCharacterBoxes;

@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectTextRectanglesRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNDefines.h
/* Vision - VNDefines.h
 
 Copyright (c) 2015 Apple, Inc.
 All rights reserved. */

#ifndef VNDEFINES_H
#define VNDEFINES_H

#ifdef __cplusplus
#define VN_EXTERN_C_BEGIN  extern "C" {
#define VN_EXTERN_C_END  }
#else
#define VN_EXTERN_C_BEGIN
#define VN_EXTERN_C_END
#endif

#ifdef __cplusplus
# define VN_EXPORT extern "C" __attribute__((visibility("default")))
#else
# define VN_EXPORT extern __attribute__((visibility("default")))
#endif


#endif /* VNDEFINES_H */
// ==========  Vision.framework/Headers/VNDetectFaceLandmarksRequest.h
//
//  VNDetectFaceLandmarksRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNFaceObservationAccepting.h>


NS_ASSUME_NONNULL_BEGIN


/*!
 @brief    Constellation type defines how many landmark points are used to map a face. Revisions 1, 2, and 3 support 65 points, where Rev3 also supports 76 points.
 */
typedef NS_ENUM(NSUInteger, VNRequestFaceLandmarksConstellation)
{
    VNRequestFaceLandmarksConstellationNotDefined = 0,
    VNRequestFaceLandmarksConstellation65Points,
    VNRequestFaceLandmarksConstellation76Points
};


/*!
	@brief A request that will produce face landmark information.

	@details This request will generate VNFaceObservation objects with the landmarks property populated with information describing face landmarks. If VNFaceObservations are provided via the VNFaceObservationAccepting protocol without the landmarks property populated, new observations will be created as copies of the input VNFaceObservations with the landmarks property populated. If the landmarks property has already been populated, the original VNFaceObservations will be returned. If no VNFaceObservations are provided, face detection will be run first. 
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNDetectFaceLandmarksRequest : VNImageBasedRequest <VNFaceObservationAccepting>

+ (BOOL) revision:(NSUInteger)requestRevision supportsConstellation:(VNRequestFaceLandmarksConstellation)constellation;

/*!
 @property property constellation
 @abstract Constellation type defines how many landmark points are used to map a face. Revisions 1, 2, and 3 of the request support 65 points, where Revision 3 also supports 76 points.
 */
@property (readwrite, assign) VNRequestFaceLandmarksConstellation constellation API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectFaceLandmarksRequestRevision1 = 1;

API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectFaceLandmarksRequestRevision2 = 2;

API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNDetectFaceLandmarksRequestRevision3 = 3;


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNGenerateAttentionBasedSaliencyImageRequest.h
//
//  VNGenerateAttentionBasedSaliencyImageRequest.h
//  Vision
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief	Generates an image that identifies which part(s) of a given image is most interesting (i.e. something that a human is likely to look at - hence attention based).
			The resulting observation, VNSaliencyImageObservation, encodes this data as a heat map which can be used to highlight regions of interest.
*/
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNGenerateAttentionBasedSaliencyImageRequest : VNImageBasedRequest
@end


API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNGenerateAttentionBasedSaliencyImageRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNRequestHandler.h
//
//  VNRequestHandler.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//
/*!
 @header There are two types of request handlers: VNSequenceRequestHandler and VNImageRequestHandler.
 
 Each of them are for scheduling one or more @link VNRequest @/link objects for processing. The type of request may dictate which kind of request handler to use. Some VNRequests can be used with both, while others can only be used with a specific one. Please refer to the documentation of the specific request. The general distinction between the two is that requests that are specific to an image (or buffer) would use the VNImageRequestHandler. For requests that span over multiple image buffers the VNSequenceRequestHandler will hold on to past request data to allow algorithms to work on multiple buffers in a sequence, and that sequence can be dynamic.
 
 */


#import <Foundation/Foundation.h>
#import <CoreVideo/CVPixelBuffer.h>
#import <CoreImage/CoreImage.h>
#import <ImageIO/ImageIO.h>

#import <Vision/VNDefines.h>
#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN


/*!
 @brief Options keys passed into the VNImageRequestHandler creations or requests that take an auxiliary image. These are options that either describe specific properties of an image like the VNImageOptionCameraIntrinsics or how an image needs to be handled like the VNImageOptionCIContext.
*/
typedef NSString * VNImageOption NS_STRING_ENUM;

/*!
 @const      VNImageOptionProperties
 @abstract   VNImageOptionProperties is the dictionary from CGImageSourceCopyPropertiesAtIndex. This contains metadata that can be used by some algorithms like horizon detection.
 */

VN_EXPORT VNImageOption const VNImageOptionProperties API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/*!
 @brief VNImageOptionCameraIntrinsics  Specifies the camera intrinsics as an NSData or CFData representing a matrix_float3x3. See kCMSampleBufferAttachmentKey_CameraIntrinsicMatrix for details
 @discussion
     Camera intrinsic matrix is a CFData containing a matrix_float3x3, which is column-major. It has the following contents:
     fx	0	ox
     0	fy	oy
     0	0	1
     fx and fy are the focal length in pixels. For square pixels, they will have the same value.
     ox and oy are the coordinates of the principal point. The origin is the upper left of the frame.

 */
VN_EXPORT VNImageOption const VNImageOptionCameraIntrinsics API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/*!
 @brief VNImageOptionCIContext  Specifies the CIContext to be used in Core Image operations of request handler. If this is not specified, Vision will create its own CIContext. This option is helpful when the passed in CIImage is the result of a CIFilter chain that has been executed on a CIContext or uses outputs of a CIImage on a given CIContext as they don't have to transfer to other contexts.
 */

VN_EXPORT VNImageOption const VNImageOptionCIContext API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*!
 @brief Performs requests on a single image.
 @discussion The VNImageRequestHandler is created with an image that is used to be used for the requests a client might want to schedule. The VNImageRequestHandler retains, but never modifies, the image source for its entire lifetime. The client also must not modify the content of the image source once the VNImageRequestHandler is created otherwise the results are undefined.
             The VNImageRequestHandler can choose to also cache intermediate representation of the image or other request-specific information for the purposes of runtime performance.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNImageRequestHandler : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 @brief initWithCVPixelBuffer:options creates a VNImageRequestHandler to be used for performing requests against the image passed in as buffer.
 
 @param pixelBuffer A CVPixelBuffer containing the image to be used for performing the requests. The content of the buffer cannot be modified for the lifetime of the VNImageRequestHandler.
 
 */
- (instancetype)initWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer options:(NSDictionary<VNImageOption, id> *)options;

/*!
 @brief initWithCVPixelBuffer:options creates a VNImageRequestHandler to be used for performing requests against the image passed in as buffer.
 
 @param pixelBuffer A CVPixelBuffer containing the image to be used for performing the requests. The content of the buffer cannot be modified for the lifetime of the VNImageRequestHandler.
 @param orientation The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics
 */
- (instancetype)initWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;

/*!
 @brief initWithCGImage:options creates a VNImageRequestHandler to be used for performing requests against the image passed in as a CGImageRef.
 
 @param image A CGImageRef containing the image to be used for performing the requests. The content of the image cannot be modified.
 
 */
- (instancetype)initWithCGImage:(CGImageRef)image options:(NSDictionary<VNImageOption, id> *)options;


/*!
 
 @brief initWithCGImage:options creates a VNImageRequestHandler to be used for performing requests against the image passed in as a CGImageRef.
 
 @param image A CGImageRef containing the image to be used for performing the requests. The content of the image cannot be modified.
 @param orientation The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics

 */
- (instancetype)initWithCGImage:(CGImageRef)image orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
 @brief initWithCIImage:options creates a VNImageRequestHandler to be used for performing requests against the image passed in as a CIImage.
 
 @param image A CIImage containing the image to be used for performing the requests. The content of the image cannot be modified.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics
 
 
 @note:  Request results may not be accurate in simulator due to CI's inability to render certain pixel formats in the simulator. The orientation of the original image should be applied for instance by using imageByApplyingOrientation or use the initWithCIImage:options:orientation API.
 */
- (instancetype)initWithCIImage:(CIImage *)image options:(NSDictionary<VNImageOption, id> *)options;


/*!
 @brief initWithCIImage:options:orientation creates a VNImageRequestHandler to be used for performing requests against the image passed in as a CIImage.
 
 @param image A CIImage containing the image to be used for performing the requests. The content of the image cannot be modified.
 @param orientation The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics

 
 @note:  Request results may not be accurate in simulator due to CI's inability to render certain pixel formats in the simulator
 */
- (instancetype)initWithCIImage:(CIImage *)image orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
 @brief initWithURL:options creates a VNImageRequestHandler to be used for performing requests against an image specified by it's URL
 
 @param imageURL A URL pointing at an image to be used for performing the requests. The image has to be in a format that is supported by ImageIO. The content of the image cannot be modified.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics
 
 @note:  Request results may not be accurate in simulator due to CI's inability to render certain pixel formats in the simulator
 */
- (instancetype)initWithURL:(NSURL *)imageURL options:(NSDictionary<VNImageOption, id> *)options;


/*!
 @brief initWithURL:options creates a VNImageRequestHandler to be used for performing requests against an image specified by it's URL
 
 @param imageURL A URL pointing at an image to be used for performing the requests. The image has to be in a format that is supported by ImageIO. The content of the image cannot be modified.
 @param orientation The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics

 @note:  Request results may not be accurate in simulator due to CI's inability to render certain pixel formats in the simulator
 */
- (instancetype)initWithURL:(NSURL *)imageURL orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
 @brief initWithData:options creates a VNImageRequestHandler to be used for performing requests against an image contained in an NSData object.
 
 @param imageData An NSData object containing the content of the image to be used for performing the requests. See CIImage imageWithData for supported format. The content of the image cannot be modified.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics
 
 @note:  Request results may not be accurate in simulator due to CI's inability to render certain pixel formats in the simulator
 
 */
- (instancetype)initWithData:(NSData *)imageData options:(NSDictionary<VNImageOption, id> *)options;


/*!
 @brief initWithData:options creates a VNImageRequestHandler to be used for performing requests against an image contained in an NSData object.
 
 @param imageData An NSData object containing the content of the image to be used for performing the requests. See CIImage imageWithData for supported format. The content of the image cannot be modified.
 @param orientation The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
 @param options A dictionary with options specifying auxiliary information for the buffer/image like VNImageOptionCameraIntrinsics

 @note:  Request results may not be accurate in simulator due to CI's inability to render certain pixel formats in the simulator
 
 */
- (instancetype)initWithData:(NSData *)imageData orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
 @brief performRequests schedules one or more VNRequests to be performed. The function returns once all requests have been finished.
 
 @discussion The results of the VNRequests as well any possible errors of the individual requests are reported in the VNRequests results and error properties.
 
 @param requests An NSArray of VNRequests that are to be performed.
 @param error Returns an error that happened during scheduling of the requests. Check individual requests results and errors for their respective success and failures. This parameter is optional.
 @return Returns true if all requests were scheduled and performed. Check individual requests results and errors for their respective success and failures.
 
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests error:(NSError **)error;


@end





/*!
 @brief Performs requests on a sequence of images.
 @discussion The VNSequenceRequestHandler is created without any specific image source.  The -performRequests:on<ImageSource>:error: methods will retain the image source for no longer than the lifetime of the call.
             The VNSequenceRequestHandler can choose to also cache state information related to the previously-processed image sources.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNSequenceRequestHandler : NSObject


/*!
	@brief	Creates a new object.
*/
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*!
	@brief Perform requests on an image in a CVPixelBuffer.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	pixelBuffer		The CVPixelBuffer containing the image to be processed.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onCVPixelBuffer:(CVPixelBufferRef)pixelBuffer error:(NSError **)error;

/*!
	@brief Perform requests on an image in a CVPixelBuffer.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	pixelBuffer		The CVPixelBuffer containing the image to be processed.
	
	@param	orientation		The orientation of the image as it is captured in the pixel buffer.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onCVPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(CGImagePropertyOrientation)orientation error:(NSError **)error;

/*!
	@brief Perform requests on an image in a CGImageRef.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	image			The CGImageRef containing the image to be processed.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onCGImage:(CGImageRef)image error:(NSError **)error;


/*!
	@brief Perform requests on an image in a CGImageRef.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	image			The CGImageRef containing the image to be processed.
	
	@param	orientation		The orientation of the image.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onCGImage:(CGImageRef)image orientation:(CGImagePropertyOrientation)orientation error:(NSError **)error;


/*!
	@brief Perform requests on an image in a CIImage.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	image			The CIImage containing the image to be processed.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onCIImage:(CIImage*)image error:(NSError **)error;


/*!
	@brief Perform requests on an image in a CIImage.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	image			The CIImage containing the image to be processed.
	
	@param	orientation		The orientation of the image.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onCIImage:(CIImage*)image orientation:(CGImagePropertyOrientation)orientation error:(NSError **)error;


/*!
	@brief Perform requests on an image referenced by an URL.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	imageURL		The URL of the image to be processed.  If this is not a file-based URL, the method will fail.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onImageURL:(NSURL*)imageURL error:(NSError **)error;


/*!
	@brief Perform requests on an image referenced by an URL.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	imageURL		The URL of the image to be processed.  If this is not a file-based URL, the method will fail.

	@param	orientation		The orientation of the image.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onImageURL:(NSURL*)imageURL orientation:(CGImagePropertyOrientation)orientation error:(NSError **)error;


/*!
	@brief Perform requests on an image with its source format in memory.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	imageData		The data representing the source format of the image to be processed.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onImageData:(NSData*)imageData error:(NSError **)error;


/*!
	@brief Perform requests on an image with its source format in memory.
	
	@param	requests		The VNRequests to be performed on the image.
	
	@param	imageData		The data representing the source format of the image to be processed.

	@param	orientation		The orientation of the image.
	
	@param	error			On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify NULL for this parameter if you do not want the error information.
 */
- (BOOL)performRequests:(NSArray<VNRequest *> *)requests onImageData:(NSData*)imageData orientation:(CGImagePropertyOrientation)orientation error:(NSError **)error;

@end


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/Vision.h
//
//  Vision.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>

#import <Vision/VNDefines.h>
#import <Vision/VNTypes.h>
#import <Vision/VNError.h>
#import <Vision/VNUtils.h>
#import <Vision/VNFaceLandmarks.h>
#import <Vision/VNRequest.h>
#import <Vision/VNRequestRevisionProviding.h>
#import <Vision/VNFaceObservationAccepting.h>
#import <Vision/VNClassifyImageRequest.h>
#import <Vision/VNDetectBarcodesRequest.h>
#import <Vision/VNDetectFaceRectanglesRequest.h>
#import <Vision/VNDetectFaceLandmarksRequest.h>
#import <Vision/VNDetectFaceCaptureQualityRequest.h>
#import <Vision/VNDetectHorizonRequest.h>
#import <Vision/VNDetectRectanglesRequest.h>
#import <Vision/VNDetectTextRectanglesRequest.h>
#import <Vision/VNRecognizeTextRequest.h>
#import <Vision/VNGenerateAttentionBasedSaliencyImageRequest.h>
#import <Vision/VNGenerateObjectnessBasedSaliencyImageRequest.h>
#import <Vision/VNGenerateImageFeaturePrintRequest.h>
#import <Vision/VNCoreMLRequest.h>
#import <Vision/VNTargetedImageRequest.h>
#import <Vision/VNImageRegistrationRequest.h>
#import <Vision/VNRequestHandler.h>
#import <Vision/VNObservation.h>
#import <Vision/VNTrackingRequest.h>
#import <Vision/VNTrackObjectRequest.h>
#import <Vision/VNTrackRectangleRequest.h>
#import <Vision/VNDetectHumanRectanglesRequest.h>
#import <Vision/VNDetectAnimalRectanglesRequest.h>


/* The version of the Vision framework */
VN_EXPORT double VNVisionVersionNumber API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
// ==========  Vision.framework/Headers/VNGenerateObjectnessBasedSaliencyImageRequest.h
//
//  VNGenerateObjectnessBasedSaliencyImageRequest.h
//  Vision
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN

/*!
 @brief    Generates an image that identifies which part(s) of a given image are most likely to be objects (i.e. something that a human is likely to see as an object).
 The resulting observation, VNSaliencyImageObservation, encodes this data as a heat map which can be used highlight regions of interest.
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNGenerateObjectnessBasedSaliencyImageRequest : VNImageBasedRequest
@end

API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNGenerateObjectnessBasedSaliencyImageRequestRevision1 = 1;

NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNDetectHorizonRequest.h
//
//  VNDetectHorizonRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief Determine what the horizon tilt of an image is.
	
	@discussion If the horizon tilt is detected in an image, the request will provide a VNHorizonObservation in the results which describe how to transform the image so that the horizon line becomes level.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNDetectHorizonRequest : VNImageBasedRequest
@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectHorizonRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNDetectRectanglesRequest.h
//
//  VNDetectRectanglesRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNTypes.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A request that will detect rectangles in an image.

	@details This request will generate VNRectangleObservation objects describing the location of rectangles detected in an image.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNDetectRectanglesRequest : VNImageBasedRequest

/*!
 @brief Specifies the minimum aspect ratio of the rectangle(s) to look for, range [0.0, 1.0], default 0.5
 */
@property (readwrite, nonatomic, assign) VNAspectRatio minimumAspectRatio;

/*!
 @brief Specifies the maximum aspect ratio of the rectangle(s) to look for, range [0.0, 1.0], default 1.0
 */
@property (readwrite, nonatomic, assign) VNAspectRatio maximumAspectRatio;

/*!
 @brief Specifies the maximum number of degrees a rectangle corner angle can deviate from 90 degrees, range [0,45], default 30
 */
@property (readwrite, nonatomic, assign) VNDegrees quadratureTolerance;

/*!
 @brief Specifies the minimum size of the rectangle to be detected, as a proportion of the smallest dimension, range [0.0, 1.0], default .2. Any smaller rectangles that may have been detected will not be returned. 
 */
@property (readwrite, nonatomic, assign) float minimumSize;

/*!
 @brief Specifies a minimum confidence score, range [0.0, 1.0], default 0.0. Any rectangles with a lower confidence score will not be returned.
 */
@property (readwrite, nonatomic, assign) VNConfidence minimumConfidence;

/*!
 @brief Specifies the maximum number of rectangles to be returned.  The default is 1.  Setting this property to 0 will allow an unlimited number of observations to be returned.
 */
@property (readwrite, nonatomic, assign) NSUInteger maximumObservations;


@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectRectanglesRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNRequest.h
//
//  VNRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Metal/Metal.h>


NS_ASSUME_NONNULL_BEGIN


/*!
 @header VNRequest The VNRequest class is the object a client uses to describe any computer vision task to be performed by the Vision framework. They are submitted to a request handler in order to perform the task, and the resulting VNObservations are placed in the results property of the VNRequest.
 */
@class VNRequest;

/*!
 @abstract A block that is executed at the completion of a request.
 @param request The VNRequest that has been completed. The results of the request if no error was encountered are populated in the results array of the request.
 @param	error The error that caused the request to fail, or nil if completed successfully.
 */
typedef void (^VNRequestCompletionHandler)(VNRequest *request, NSError * _Nullable error);


/*!
@class VNRequest
@abstract VNRequest objects describe the operation to be performed as well as act as the recipient of the operation's resultant observations.
 
@discussion VNRequest objects are instantiated in a pre-configured nominal state. Prior to sending a VNRequest to a request handler to perform a desired operation, the default configuration can be changed by modifying the values of VNRequest properties. The VNRequest class itself acts as a base class and is not meant to be directly instantiated.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNRequest : NSObject <NSCopying>


/*!
 @abstract Creates a new VNRequest with no completion handler.
*/
- (instancetype) init;


/*!
 @abstract Creates a new VNRequest with an optional completion handler.

 @param completionHandler	The block to be invoked after the request has completed its processing. The completion handler gets executed on the same dispatch queue as the request being executed.
*/
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler NS_DESIGNATED_INITIALIZER;


/*!
 @abstract A hint used to minimize the resource burden of the request. Memory footprint, processing footprint and/or CPU/GPU contention will be reduced (depending on the request), at the potential cost of longer execution time. This can help, for example, with ensuring UI updates and rendering are not getting blocked by Vision processing.
*/
@property (readwrite, nonatomic, assign) BOOL preferBackgroundProcessing;


/*!
 @abstract This property, if set to YES, signifies that the request should be performed exclusively on the CPU and not on the GPU. The default value is NO, which signifies that the request is free to leverage the GPU to accelerate any work the request may require.
 */
@property (readwrite, nonatomic) BOOL usesCPUOnly;

/*!
 @property results
 @abstract The collection of VNObservations generated by the processing of the request.
 @discussion The only valid time to access this property is after the request has been processed by a request handler.  If the request failed, this property will be nil; otherwise, it will be an array of zero or more VNObservation subclasses specific to the VNRequest subclass.
 */
@property (readonly, nonatomic, copy, nullable) NSArray *results;


/*!
 @property completionHandler
 @abstract The completion handler block that will be invoked after the request has completed processing.
 */
@property (readonly, nonatomic, copy, nullable) VNRequestCompletionHandler completionHandler;


/*!
 @abstract The specific algorithm or implementation revision that is to be used to perform the request.
 */
@property (readwrite, nonatomic, assign) NSUInteger revision API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0));


/*!
 @abstract Provides the collection of currently-supported algorithm or implementation versions for the class of request.
 @discussion This method allows clients to introspect at runtime what capabilities are available for each class of VNRequest in the Vision framework.
 */
@property (class, readonly, nonatomic, copy) NSIndexSet* supportedRevisions API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0));

/*! @abstract Provides the revision of the request that was latest for the particular SDK that was linked with the client application. */
@property (class, readonly, nonatomic, assign) NSUInteger defaultRevision API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0));

/*! @abstract Provides the current revison supported by the request. */
@property (class, readonly, nonatomic, assign) NSUInteger currentRevision API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0));

/*!
 * @discussion Tries to abort the request as soon as possible. Results will be nil. The completionHandler (if present) will be called with an error of VNErrorRequestCancelled.
 */
- (void)cancel API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

@end


/*!
	@brief	A value that indicates that the request revision is either unknown or not applicable.
*/
API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNRequestRevisionUnspecified = 0;



/*!
	@brief A request that will process the contents of a reference image.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNImageBasedRequest : VNRequest

/*!
	@brief The region of the image in which the request will be performed.  The rectangle is normalized to the dimensions of the image being processed and has its origin specified relative to the image's lower-left corner.
	
	@discussion The default value for this property is { { 0, 0 }, { 1, 1 } }.  Setting this property to a rectangle that is outside of the normalized coordinate space will be accepted but result in the request failing to be performed.
*/
@property (readwrite, nonatomic, assign) CGRect regionOfInterest;

@end



/*!
 @abstract A block that is executed at intervals during the processing of a request.
 @param request The VNRequest that has been completed. The results of the request, if no error was encountered, are populated in the results array of the request.
 @param fractionCompleted When possible the request will report its progress between 0.0 and 1.0. If the requests indeterminate property is set, then this value is undefined.
 @param    error The error that caused the request to fail, or nil if completed successfully.
 @discussion The results in the request can be populated with partial results. The progressHandler can be called on a different dispatch queue than what the request was initiated from.
 */
typedef void (^VNRequestProgressHandler)(VNRequest *request, double fractionCompleted, NSError * _Nullable error);


API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@protocol VNRequestProgressProviding < NSObject >

/*!
 @brief Requests that support the VNRequestProgressProviding protocol would periodically call the progressHandler to report progress on longer running tasks.
 
 @discussion The progessHandler is optional allowing clients of the request to report progress to the user and/or display or process partial results when they become available. Note that the progressHandler can be called on a different dispatch queue than what the request was initiated from.
 */
@property (readwrite, nonatomic, assign) VNRequestProgressHandler progressHandler;


/*!
 @brief If a request cannot determine its progress in fractions completed, this property will be set.
 @discussion If this is set, it doesn't mean that the request will run forever just that the nature of the request is not broken down into identifiable fractions on which progress can be reported in increments. The progressHandler will nonetheless be called at suitable intervals.
 */
@property (readonly) BOOL indeterminate;

@end

NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNImageRegistrationRequest.h
//
//  VNImageRegistrationRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNTargetedImageRequest.h>
#import <Vision/VNObservation.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A request that will calculate a transformation for morphing a "floating" image onto an unchanging "reference" image.
	
	@discussion The request is created with the targeted image acting as the floating image. Processing the request will calculate the transformations that morph the floating image onto the reference image.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNImageRegistrationRequest : VNTargetedImageRequest
@end


/*!
	@brief An image registration request that will calculate a translational transformation for morphing a "floating" image onto an unchanging "reference" image.
	
	@discussion The request is created with the targeted image acting as the floating image. Processing the request will calculate the affine transformations that morph the floating image onto the reference image.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNTranslationalImageRegistrationRequest : VNImageRegistrationRequest
@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNTranslationalImageRegistrationRequestRevision1 = 1;



/*!
	@brief An image registration request that will calculate a homographic transformation for morphing a "floating" image onto an unchanging "reference" image.
	
	@discussion The request is created with the targeted image acting as the floating image. Processing the request will calculate the matrix warp transform that morph the floating image onto the reference image.
	            Note that the request will fail unless the pixel dimensions of the reference image do not exactly match the resolved region of interest of the floating image.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNHomographicImageRegistrationRequest : VNImageRegistrationRequest
@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNHomographicImageRegistrationRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNDetectFaceRectanglesRequest.h
//
//  VNDetectFaceRectanglesRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A request that will detect faces in an image.

	@details This request will generate VNFaceObservation objects with defined a boundingBox.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNDetectFaceRectanglesRequest : VNImageBasedRequest
@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectFaceRectanglesRequestRevision1 = 1;

API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectFaceRectanglesRequestRevision2 = 2;


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNObservation.h
//
//  VNObservation.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CVPixelBuffer.h>
#import <CoreML/CoreML.h>
#import <simd/simd.h>

#import <Vision/VNTypes.h>
#import <Vision/VNRequestRevisionProviding.h>


/*!
 @header VNObservation VNObservations describe the results of performing a VNRequest. The type of request determines the type of observations.
 */


NS_ASSUME_NONNULL_BEGIN


@class CIBarcodeDescriptor;
@class MLFeatureValue;
@class VNFaceLandmarks2D;



/*!
 @class VNObservation
 @brief VNObservation describes the results of performing a VNRequest. The result has a confidence score. The different types of requests will create different subclasses of VNObservation to return their results in properties of those subclasses.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNObservation : NSObject < NSCopying, NSSecureCoding, VNRequestRevisionProviding >

/*!
   @brief The unique identifier assigned to an observation.
 */
@property (readonly, nonatomic, strong) NSUUID *uuid;

/*!
 * @brief The level of confidence normalized to [0, 1] where 1 is most confident
 * @discussion Confidence can always be returned as 1.0 if confidence is not supported or has no meaning
 */
@property (readonly, nonatomic, assign) VNConfidence confidence;

@end


/*!
    @class VNDetectedObjectObservation
    @superclass VNObservation
    @brief VNDetectedObjectObservation is VNObservation in an image that has a location and/or dimension. Further attributes depend on the specific detected object.
    @discussion All result objects (faces, scene objects, shapes etc) must extend from this class.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNDetectedObjectObservation : VNObservation

/*!
 @brief create a new VNDetectedObjectObservation with a normalized bounding box and a confidence of 1.0.
 */
+ (instancetype)observationWithBoundingBox:(CGRect)boundingBox;

+ (instancetype)observationWithRequestRevision:(NSUInteger)requestRevision boundingBox:(CGRect)boundingBox API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0));

/*!
    @brief The bounding box of the detected object. The coordinates are normalized to the dimensions of the processed image, with the origin at the image's lower-left corner.
 */
@property (readonly, nonatomic, assign) CGRect boundingBox;

@end


/*!
 @class VNFaceObservation
 @superclass VNObservation
 @brief VNFaceObservation is the result of a face detection request or derivatives like a face landmark request.
 @discussion The properties filled in this obervation depend on the request being performed. For instance if just a VNDetectFaceRectanglesRequest was performed the landmarks will not be populated. VNFaceObservation are also used as inputs to other request as defined by the VNFaceObservationAccepting protocol. An example would be the VNDetectFaceLandmarksRequest. This can be helpful for instance if the face rectangles in an image are not derived from a VNDetectFaceRectanglesRequest but instead come from other sources like EXIF or other face detectors. In that case the client of the API creates a VNFaceObservation with the boundingBox (in normalized coordinates) that were based on those detected faces.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNFaceObservation: VNDetectedObjectObservation

/*!
 @brief create a new VNFaceObservation with a normalized bounding box, roll and yaw
 */
+ (instancetype)faceObservationWithRequestRevision:(NSUInteger)requestRevision boundingBox:(CGRect)boundingBox roll:(nullable NSNumber *)roll yaw:(nullable NSNumber *)yaw API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0));

/*!
 @brief The face landmarks populated by the VNDetectFaceLandmarksRequest. This is set to nil if only a VNDetectFaceRectanglesRequest was performed.
 */
@property (readonly, nonatomic, strong, nullable)  VNFaceLandmarks2D *landmarks;

/*!
 @brief The capture quality of the face as a normalized value between 0.0 and 1.0 that can be used to compare the quality of the face in terms of it capture attributes (lighting, blur, position). This score can be used to compare the capture quality of a face against other captures of the same face in a given set.
 */
@property (readonly, nonatomic, strong, nullable) NSNumber *faceCaptureQuality API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/*!
 @brief Face roll angle populated by VNDetectFaceRectanglesRequest. The roll is reported in radians, positive angle corresponds to counterclockwise direction, range [-Pi, Pi). nil value indicates that the roll angle hasn't been computed
 */
@property (readonly, nonatomic, strong, nullable) NSNumber *roll API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0));

/*!
 @brief Face yaw angle populated by VNDetectFaceRectanglesRequest. The yaw is reported in radians, positive angle corresponds to counterclockwise direction, range [-Pi/2, Pi/2). nil value indicates that the yaw angle hasn't been computed
 */
@property (readonly, nonatomic, strong, nullable) NSNumber *yaw API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0));

@end

/*!
 @class VNClassificationObservation
 @superclass VNObservation
 @brief VNClassificationObservation returns the classifcation in form of a string.
 @discussion VNClassificationObservation is the observation returned by VNCoreMLRequests that using a model that is a classifier. A classifier produces an arrary (this can be a single entry) of classifications which are labels (identifiers) and confidence scores.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNClassificationObservation : VNObservation

/*!
 @brief The is the label or identifier of a classification request. An example classification could be a string like 'cat' or 'hotdog'. The string is defined in the model that was used for the classification. Usually these are technical labels that are not localized and not meant to be used directly to be presented to an end user in the UI.
 */
@property (readonly, nonatomic, copy) NSString *identifier;

@end


/*!
 @discussion VNClassificationObservation mave have precision/recall curves which can be used to decide on an "optimal" operation point.
             Precision is a value in the range of [0..1] which represents the fraction of relevant instances among the retrieved instances.
             Recall is a value in the range of [0..1] which represents the fraction of relevant instances that have been retrieved over the total amount of relevant instances.
*/
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNClassificationObservation (PrecisionRecallAdditions)

/*!
	@brief	Determine whether or not precision/recall curves are available with the observation.
	@discussion	If this property is YES, then all other precision/recall related methods in this addition can be called.
*/
@property (readonly, nonatomic, assign) BOOL hasPrecisionRecallCurve;

/*!
	@brief	Determine whether or not the observation's operation point for a specific precision has a minimum recall value.
 
	@param minimumRecall	The minimum recall desired for an operation point.
 
	@param precision		The precision value used to select the operation point.
 
	@return YES if the recall value for the operation point specified by a precision value has the minimum value; otherwise, NO.
*/
- (BOOL) hasMinimumRecall:(float)minimumRecall forPrecision:(float)precision;

/*!
	@brief	Determine whether or not the observation's operation point for a specific recall has a minimum precision value.

	@param minimumPrecision	The minimum precision desired for an operation point.
 
	@param recall		The recall value used to select the operation point.
 
	@return YES if the precision value for the operation point specified by a recall value has the minimum value; otherwise, NO.
*/
- (BOOL) hasMinimumPrecision:(float)minimumPrecision forRecall:(float)recall;

@end



/*!
 @class VNRecognizedObjectObservation
 @superclass VNDetectedObjectObservation
 @brief VNRecognizedObjectObservation is a VNDetectedObjectObservation with an array of classifications that classify the recognized object. The confidence of the classifications sum up to 1.0. It is common practice to multiply the classification confidence with the confidence of this observation.
 */
API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
@interface VNRecognizedObjectObservation : VNDetectedObjectObservation

@property (readonly, nonatomic, copy) NSArray<VNClassificationObservation *> *labels;

@end

/*!
 @class VNCoreMLFeatureValueObservation
 @superclass VNObservation
 @brief VNCoreMLFeatureValueObservation returns the prediction of a model as an MLFeatureValue.
 @discussion This is the returned observations for models that are not classifiers and that do not return an image as a prediction. The confidence for these observations is always 1.0.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNCoreMLFeatureValueObservation : VNObservation

/*!
 @brief The result VNCoreMLRequest where the model produces an MLFeatureValue that is neither a classification or image. Refer to the Core ML documentation and the model itself for the handling of the content of the featureValue.
 
 */
@property (readonly, nonatomic, copy) MLFeatureValue *featureValue;

/*!
 @brief The name used in the model description of the CoreML model that produced this observation allowing to correlate the observation back to the output of the model.
 
 */
@property (readonly, nonatomic, copy) NSString *featureName API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

@end

/*!
 @class VNPixelBufferObservation
 @superclass VNObservation
 @brief VNPixelBufferObservation returns the prediction of a model as a CVPixelBufferRef.
 @discussion This is the returned observations for models that are not classifiers and return an image as a prediction. The confidence for these observations is always 1.0.
 
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNPixelBufferObservation : VNObservation

/*!
 @brief The resulting image from a request like VNCoreMLRequest where the model produces an image as an output.
 
 */
@property (readonly, nonatomic) CVPixelBufferRef pixelBuffer;

/*!
 @brief The name used in the model description of the CoreML model that produced this observation allowing to correlate the observation back to the output of the model. This can be nil if the observation is not the result of a VNCoreMLRequest operation.
 
 */
@property (readonly, nonatomic, copy, nullable) NSString *featureName API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

@end


/*!
 @class VNRectangleObservation
 @superclass VNObservation
 @brief VNRectangleObservation is the result of a rectangle detector
 @discussion The VNRectangleObservation has a bounding box that encompasses the rectangle found in the image. The rectangle itself is defined by the four corner point properties. The rectangle can be rotated in or even out of plane. A common use case is to use the CIPerspectiveTransform filter to correct a detected rectangle to its 'flat upright' representation. All coordinates are normalized and the coordinates can be outside the image.

 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNRectangleObservation : VNDetectedObjectObservation

+ (instancetype)rectangleObservationWithRequestRevision:(NSUInteger)requestRevision topLeft:(CGPoint)topLeft bottomLeft:(CGPoint)bottomLeft bottomRight:(CGPoint)bottomRight topRight:(CGPoint)topRight API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

@property (readonly, nonatomic, assign) CGPoint topLeft;
@property (readonly, nonatomic, assign) CGPoint topRight;
@property (readonly, nonatomic, assign) CGPoint bottomLeft;
@property (readonly, nonatomic, assign) CGPoint bottomRight;

@end


/*!
 @class VNTextObservation
 @superclass VNDetectedObjectObservation
 @brief VNTextObservation Describes a text area detected by the VNRequestNameDetectTextRectangles request.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNTextObservation : VNRectangleObservation

/*!
	@brief		Array of individual character bounding boxes found within the observation's boundingBox.
	@discussion	If the associated request indicated that it is interested in character boxes by setting the VNRequestOptionReportCharacterBoxes option to @YES, this property will be non-nil (but may still be empty, depending on the detection results).
*/
@property (readonly, nonatomic, copy, nullable) NSArray<VNRectangleObservation *> *characterBoxes;

@end

/*!
 @class VNRecognizedText
 @brief VNRecognizedText A block of recognized text. There can be multiple VNRecognizedText objects returned in a VNRecognizedTextObservation - one for each candidate.
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNRecognizedText : NSObject < NSCopying, NSSecureCoding >

/*!
 @brief        Field that contains recognized text.
 @discussion   This is the top candidate of the recognized text.
 */
@property (readonly, nonatomic, copy) NSString *string;

/*!
 * @brief The level of confidence normalized to [0.0, 1.0] where 1.0 is most confident
 */
@property (readonly, nonatomic, assign) VNConfidence confidence;

/*!
 * @brief Calculate the bounding box around the characters in the range of the string.
 * @discussion The bounding boxes are not guaranteed to be an exact fit around the characters and are purely meant for UI purposes and not for image processing.
 */
- (nullable VNRectangleObservation *)boundingBoxForRange:(NSRange)range error:(NSError**)error;

@end

/*!
 @class VNRecognizedTextObservation
 @superclass VNDetectedObjectObservation
 @brief VNRecognizedTextObservation Describes a text area detected and recognized by the VNRecognizeTextRequest request.
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNRecognizedTextObservation : VNRectangleObservation


/*!
 * @brief Returns the top N candidates sorted by decreasing confidence score
 * @discussion This will return no more than N but can be less than N candidates. The maximum number of candidates returned cannot exceed 10 candidates.
 */
- (NSArray<VNRecognizedText*>*) topCandidates:(NSUInteger)maxCandidateCount;


@end


/*!
 @class VNBarcodeObservation
 @superclass VNRectangleObservation
 @brief VNBarcodeObservation Describes an area containing a barcode detected by the VNRequestNameDetectBarcodes request.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNBarcodeObservation : VNRectangleObservation

/*!
	@brief The symbology of the detected barcode.
*/
@property (readonly, nonatomic, copy) VNBarcodeSymbology symbology;


/*!
	@brief An object that provides symbology-specific data for the barcode.
*/
@property (readonly, nonatomic, strong, nullable) CIBarcodeDescriptor* barcodeDescriptor;


/*!
	@brief The string representation of the barcode's payload.  Depending on the symbology of the barcode and/or the payload data itself, a string representation of the payload may not be available.
*/
@property (readonly, nonatomic, copy, nullable) NSString* payloadStringValue;

@end



/*!
 @class VNHorizonObservation
 @superclass VNObservation
 @brief VNHorizonObservation is the result of a VNDetectHorizonRequest
 @discussion Use the transform or angle to upright the image and make the detected horizon level.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNHorizonObservation : VNObservation

@property (readonly, nonatomic, assign) CGAffineTransform transform;
@property (readonly, nonatomic, assign) CGFloat angle;

@end



/*!
 @class VNImageAlignmentObservation
 @superclass VNObservation
 @brief VNImageAlignmentObservation is generated from an image registration. This is an abstract base class. The type of registration request used defines which subclass describes the result.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNImageAlignmentObservation : VNObservation
@end


/*!
 @class VNImageTranslationAlignmentObservation
 @superclass VNImageAlignmentObservation
 @brief An observation describing the results of performing a translational image alignment.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNImageTranslationAlignmentObservation : VNImageAlignmentObservation
@property (readwrite, nonatomic, assign) CGAffineTransform alignmentTransform;
@end


/*!
 @class VNImageHomographicAlignmentObservation
 @superclass VNImageAlignmentObservation
 @brief An observation describing the results of performing a homographic image alignment.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNImageHomographicAlignmentObservation : VNImageAlignmentObservation
@property (readwrite, nonatomic, assign) matrix_float3x3 warpTransform;
@end

/*!
 @class VNSaliencyImageObservation
 @superclass VNPixelBufferObservation
 @brief VNSaliencyImageObservation provides a grayscale "heat" map of important areas of an image.
 @discussion In the revision1, the "heat" map is a OneComponent32Float pixel format CVPixelBuffer.
 
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNSaliencyImageObservation : VNPixelBufferObservation

/*!
 @brief An array of bounds of salient objects within the image. Each box represents a distinct mode of the heat map.
*/
@property (readonly, nonatomic, nullable) NSArray<VNRectangleObservation*>* salientObjects;

@end


/*!
*/
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNFeaturePrintObservation : VNObservation

/*!
	@brief The type of each element in the data.
*/
@property (readonly, atomic, assign) VNElementType elementType;

/*!
	@brief The total number of elements in the data.
*/
@property (readonly, atomic, assign) NSUInteger elementCount;

/*!
	@brief The feature print data.
*/
@property (readonly, atomic, strong) NSData* data;

/*!
 @brief Computes the distance between two observations.
 @discussion The larger the distance the more dissimlar the feature prints are. In case of an error this method returns false with an error describing the error condition, for instance comparing two non-comparable feature prints.
 */
- (BOOL)computeDistance:(float *)outDistance toFeaturePrintObservation:(VNFeaturePrintObservation *)featurePrint error:(NSError **)error;

@end


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNTrackObjectRequest.h
//
//  VNTrackObjectRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNTrackingRequest.h>


NS_ASSUME_NONNULL_BEGIN


@class VNDetectedObjectObservation;


/*!
 @brief VNTrackObjectRequest tracks an object in a sequence of images.
 @discussion The VNTrackObjectRequest is a general purpose object tracker. This tracker is used when the tracked entity does not have a special tracker, like VNTrackRectangleRequest. The VNTrackObjectRequest is initialized with VNDetectedObjectObservation that contains bounding box for the object of interest. This tracker is processed using one of the [VNSequenceRequestHandler performRequests:...] methods.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNTrackObjectRequest : VNTrackingRequest

/*!
 @brief Create a new request with detected object observation.
 
 @param    observation          Detected object observation with bounding box info.
 */
- (instancetype) initWithDetectedObjectObservation:(VNDetectedObjectObservation *)observation;


/*!
 @brief Create a new request with detected object observation.
 
 @param    observation          Detected object observation with bounding box info.
 @param    completionHandler    The block that is invoked when the request has been performed.
 */
- (instancetype) initWithDetectedObjectObservation:(VNDetectedObjectObservation *)observation completionHandler:(nullable VNRequestCompletionHandler)completionHandler;

- (instancetype) init NS_UNAVAILABLE;
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler NS_UNAVAILABLE;

@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNTrackObjectRequestRevision1 = 1;

API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNTrackObjectRequestRevision2 = 2;


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNGenerateImageFeaturePrintRequest.h
//
//  VNGenerateImageFeaturePrintRequest.h
//  Vision
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Vision/VNTypes.h>
#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A request for generating a feature print of an image.

	@discussion This request will produce a VNFeaturePrintObservation object.
*/
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNGenerateImageFeaturePrintRequest : VNImageBasedRequest

/*!
	@brief Determine what type of croping and scaling action should be applied to the image before generating the feature print.
 
	@discussion The default value for this property is VNImageCropAndScaleOptionScaleFill.
*/
@property (nonatomic, readwrite, assign) VNImageCropAndScaleOption imageCropAndScaleOption;

@end


API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNGenerateImageFeaturePrintRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNDetectHumanRectanglesRequest.h
//
//  VNDetectHumanRectanglesRequest.h
//  Vision
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN


/*!
 @brief A request that will detect human Torsos in an image.
 
 @details This request will generate VNDetectedObjectObservation objects with defined a boundingBox and confidence score.
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNDetectHumanRectanglesRequest : VNImageBasedRequest
@end


API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNDetectHumanRectanglesRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNDetectBarcodesRequest.h
//
//  VNDetectBarcodesRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNTypes.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A request that detects barcodes in an image.
	
	@discussion This request will return zero or more VNBarcodeObservation objects objects which describe the barcodes detected in an image.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNDetectBarcodesRequest : VNImageBasedRequest

/*!
	@brief Obtain the collection of barcode symbologies currently recognized by the Vision framework.
	
	@discussion	Calling this method could be a potentially expensive operation.

	@return An array of VNBarcodeSymbology objects describing the symbologies currently supported by the Vision framework.
*/
@property (class, nonatomic, readonly, copy) NSArray<VNBarcodeSymbology> *supportedSymbologies;


/*!
	@discussion The collection of barcode symbologies that are to be detected in the image.  The default is to scan for all possible symbologies.
*/
@property (readwrite, nonatomic, copy) NSArray<VNBarcodeSymbology> *symbologies;

@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectBarcodesRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNTargetedImageRequest.h
//
//  VNTargetedImageRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <CoreVideo/CVPixelBuffer.h>
#import <CoreImage/CoreImage.h>

#import <Vision/VNRequest.h>
#import <Vision/VNRequestHandler.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A request that requires an initial image as a starting point for its work.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNTargetedImageRequest : VNImageBasedRequest

- (instancetype) init  NS_UNAVAILABLE;
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler NS_UNAVAILABLE;



#pragma mark • Targeting CVPixelBuffer


/*!
	@brief Create a new request that targets an image in a pixel buffer.
	
	@param	pixelBuffer			The pixel buffer containing the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedCVPixelBuffer:(CVPixelBufferRef)pixelBuffer options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request that targets an image in a pixel buffer.
	
	@param	pixelBuffer			The pixel buffer containing the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedCVPixelBuffer:(CVPixelBufferRef)pixelBuffer options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;


/*!
	@brief Create a new request that targets an image in a pixel buffer.
	
	@param	pixelBuffer			The pixel buffer containing the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedCVPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request that targets an image in a pixel buffer.
	
	@param	pixelBuffer			The pixel buffer containing the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedCVPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;




#pragma mark • Targeting CGImage


/*!
	@brief Create a new request with a targeted CGImage.
	
	@param	cgImage				The CGImageRef of the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedCGImage:(CGImageRef)cgImage options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request with a targeted CGImage.
	
	@param	cgImage				The CGImageRef of the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedCGImage:(CGImageRef)cgImage options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;


/*!
	@brief Create a new request with a targeted CGImage.
	
	@param	cgImage				The CGImageRef of the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedCGImage:(CGImageRef)cgImage orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request with a targeted CGImage.
	
	@param	cgImage				The CGImageRef of the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedCGImage:(CGImageRef)cgImage orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;




#pragma mark • Targeting CIImage


/*!
	@brief Create a new request with a targeted CIImage.
	
	@param	ciImage				The CIImage of the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedCIImage:(CIImage *)ciImage options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request with a targeted CIImage.
	
	@param	ciImage				The CIImage of the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedCIImage:(CIImage *)ciImage options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;


/*!
	@brief Create a new request with a targeted CIImage.
	
	@param	ciImage				The CIImage of the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedCIImage:(CIImage *)ciImage orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request with a targeted CIImage.
	
	@param	ciImage				The CIImage of the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedCIImage:(CIImage *)ciImage orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;




#pragma mark • Targeting NSURL


/*!
	@brief Create a new request with a targeted image URL.
	
	@param	imageURL			The URL of the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedImageURL:(NSURL *)imageURL options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request with a targeted image URL.
	
	@param	imageURL			The URL of the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedImageURL:(NSURL *)imageURL options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;


/*!
	@brief Create a new request with a targeted image URL.
	
	@param	imageURL			The URL of the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedImageURL:(NSURL *)imageURL orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request with a targeted image URL.
	
	@param	imageURL			The URL of the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedImageURL:(NSURL *)imageURL orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;




#pragma mark • Targeting NSData


/*!
	@brief Create a new request with a targeted image data.
	
	@param imageData			The data of the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedImageData:(NSData *)imageData options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request with a targeted image data.
	
	@param imageData			The data of the targeted image.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedImageData:(NSData *)imageData options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;


/*!
	@brief Create a new request with a targeted image data.
	
	@param imageData			The data of the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
*/
- (instancetype) initWithTargetedImageData:(NSData *)imageData orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options;


/*!
	@brief Create a new request with a targeted image data.
	
	@param imageData			The data of the targeted image.
	@param	orientation			The orientation of the image/buffer based on the EXIF specification. For details see kCGImagePropertyOrientation. The value has to be an integer from 1 to 8. This supersedes every other orientation information.
	@param	options				A dictionary with options specifying auxiliary information for the image.
	@param	completionHandler	The block that is invoked when the request has been performed.
*/
- (instancetype) initWithTargetedImageData:(NSData *)imageData orientation:(CGImagePropertyOrientation)orientation options:(NSDictionary<VNImageOption, id> *)options completionHandler:(nullable VNRequestCompletionHandler)completionHandler;


@end



NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNTrackRectangleRequest.h
//
//  VNTrackRectangleRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNTrackingRequest.h>


NS_ASSUME_NONNULL_BEGIN


@class VNRectangleObservation;


/*!
 @brief VNTrackRectangleRequest tracks a rectangle in a sequence of images.
 @discussion The VNTrackRectangleRequest is a special tracker to track rectangular shape objects. The VNTrackRectangleRequest is initialized with a VNRectangleObservation object that contains a rectangle bounding box and four corners locations. VNRectangleObservation can be obtained by running rectangle detector  (VNDetectRectanglesRequest). The VNTrackRectangleRequest is processed using one of the [VNSequenceRequestHandler performRequests:...] methods.
 @note The rectangular object doesn't have to look like a rectangle when projected into the plane of the image of interest. For example, it may look like trapezoid.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNTrackRectangleRequest : VNTrackingRequest

/*!
 @property property inputObservation
 @abstract Rectangle observation, coming from rectangle detector (VNDetectRectanglesRequest), for initial tracker setup or returned from previous rectangle tracking iteration. The rectangle must be defined in normalized coordinates (size and origin between [0,1] with origin at lower left corner).
 */


/*!
 @brief Create a new rectangle tracking request with rectangle observation.
 
 @param    observation          Rectangle observation with bounding box and rectangle corners location info.
 */
- (instancetype) initWithRectangleObservation:(VNRectangleObservation *)observation;

/*!
 @brief Create a new rectangle tracking request with rectangle observation.
 
 @param    observation          Rectangle observation with bounding box and rectangle corners location info.
 @param    completionHandler    The block that is invoked when the request has been performed.
 */
- (instancetype) initWithRectangleObservation:(VNRectangleObservation *)observation completionHandler:(nullable VNRequestCompletionHandler)completionHandler  NS_DESIGNATED_INITIALIZER;

- (instancetype) init   NS_UNAVAILABLE;
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler   NS_UNAVAILABLE;

@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNTrackRectangleRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNDetectAnimalRectanglesRequest.h
//
//  VNDetectAnimalRectanglesRequest.h
//  Vision
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNDefines.h>


NS_ASSUME_NONNULL_BEGIN


typedef NSString *VNAnimalDetector NS_STRING_ENUM;

VN_EXPORT VNAnimalDetector const VNAnimalDetectorDog API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));
VN_EXPORT VNAnimalDetector const VNAnimalDetectorCat API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));


/*!
	@brief A request that will detect various animals in an image. The list of animals supported by detection algorithm can be queried by +(NSArray *)knownAnimalDetectorsForRevision

	@details This request will generate VNRecognizedObjectObservation objects with defined a boundingBox, label and confidence level.
*/
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNDetectAnimalRectanglesRequest : VNImageBasedRequest

/*!
 @brief This class method returns a list of all animals supported by detection algorithm
 
 @details This request will generate a collection of names for supported animals by current detector.
 */
+ (NSArray<VNAnimalDetector> *)knownAnimalDetectorsForRevision:(NSUInteger)requestRevision;

@end


API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNDetectAnimalRectanglesRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNTypes.h
//
//  VNTypes.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Vision/VNDefines.h>


typedef float VNConfidence;

typedef float VNAspectRatio;

typedef float VNDegrees;

typedef NS_ENUM(NSUInteger, VNImageCropAndScaleOption)
{
    VNImageCropAndScaleOptionCenterCrop = 0,  // scale image maintaining aspect ratio to fit on the short side and crop centered on the long side
    VNImageCropAndScaleOptionScaleFit = 1,    // scale to size required by algorithm
    VNImageCropAndScaleOptionScaleFill = 2
};

/*!
	@brief Barcode symbologies that are supported by the Vision framework.
	
	@discussion The actual set of barcode symbologies that can actually be recognized by a specific version of the Vision framework should be determined by using the VNRequestNameSupportedBarcodeSymbologies request.
*/
typedef NSString *VNBarcodeSymbology NS_STRING_ENUM;

VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyAztec API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode39 API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode39Checksum API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode39FullASCII API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode39FullASCIIChecksum API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode93 API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode93i API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode128 API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyDataMatrix API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyEAN8 API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyEAN13 API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyI2of5 API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyI2of5Checksum API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyITF14 API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyPDF417 API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyQR API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyUPCE API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
typedef NS_ENUM(NSUInteger, VNElementType)
{
	VNElementTypeUnknown = 0,
	VNElementTypeFloat   = 1,		// IEEE 754 single-precision floating point value
	VNElementTypeDouble  = 2,		// IEEE 754 double-precision floating point value
};
// ==========  Vision.framework/Headers/VNRecognizeTextRequest.h
//
//  VNRecognizeTextRequest.h
//  Vision
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN

/*!
 @brief    Text recognition level options to favor speed over recognition accuracy. The VNRequestTextRecognitionLevelAccurate is the default option used by VNRecognizeTextRequest.
 */
typedef NS_ENUM(NSInteger, VNRequestTextRecognitionLevel)
{
    VNRequestTextRecognitionLevelAccurate = 0,
    VNRequestTextRecognitionLevelFast
};



/*!
 @brief A request that will detect regions of text and recognize the containing text in an image.
 
 @details This request will generate VNRecognizedTextObservation objects describing the locations of text and the actual text recognized.
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNRecognizeTextRequest : VNImageBasedRequest <VNRequestProgressProviding>

/*!
 @brief Returns all the supported languages for a given text recognition level. Note that a language supported in one recognition level might not be available in another.
 */
+ (nullable NSArray<NSString *> *)supportedRecognitionLanguagesForTextRecognitionLevel:(VNRequestTextRecognitionLevel)recognitionLevel revision:(NSUInteger)requestRevision error:(NSError**)error;

/*!
 @brief Specify the languages used for the detection. The order of the languages in the array defines the order in which languages will be used during the language processing.
 The languages are specified as ISO language codes.
 */
@property (readwrite, nonatomic, copy) NSArray<NSString *> *recognitionLanguages;

/*!
 @brief An array of strings that will be used at the word recognition stage in addition to the recognition languages. The customWords list takes precedence over the standard lexicon.
 */
@property (readwrite, nonatomic, copy) NSArray<NSString *> *customWords;

/*!
 @brief The recognition level selects which techniques will be used during the text recognition. There are trade-offs between performance and accuracy.
 */
@property (readwrite, nonatomic, assign) VNRequestTextRecognitionLevel recognitionLevel;

/*!
 @brief Determines whether language correction should be applied during the recognition process. Disabling this will return the raw recognition results providing performance benefits but less accurate results.
 */
@property (readwrite, nonatomic, assign) BOOL usesLanguageCorrection;

/*
 @brief Minimum height of the text expected to be recognized, relative to the image height (e.g. for half of the image height, use 0.5). Increasing the size will reduce the memory consumption and speed up the recognition with the trade-off that text smaller than the minimum height may not be recognized properly. If the minimum height is set to 0.0 the image gets processed at the highest possible resolution with no downscaling. With that the processing time will be the longest and the memory usage the highest but the smallest technically readable text will be recognized. The default value for this is 0.0.
 */
@property (readwrite, nonatomic, assign) float minimumTextHeight;



@end

API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNRecognizeTextRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
// ==========  Vision.framework/Headers/VNError.h
//
//  VNError.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


extern NSString* const VNErrorDomain API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


typedef NS_ENUM(NSInteger, VNErrorCode)
{
    VNErrorOK = 0,
    VNErrorRequestCancelled,
    VNErrorInvalidFormat,
    VNErrorOperationFailed,
    VNErrorOutOfBoundsError,
    VNErrorInvalidOption,
    VNErrorIOError,
    VNErrorMissingOption,
    VNErrorNotImplemented,
    VNErrorInternalError,
    VNErrorOutOfMemory,
    VNErrorUnknownError,
    VNErrorInvalidOperation,
    VNErrorInvalidImage,
    VNErrorInvalidArgument,
    VNErrorInvalidModel,
    VNErrorUnsupportedRevision API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0)),
    VNErrorDataUnavailable  API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
};
// ==========  Vision.framework/Headers/VNUtils.h
//
//  VNUtils.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <simd/simd.h>

#import <Vision/VNDefines.h>
#import <Vision/VNTypes.h>



NS_ASSUME_NONNULL_BEGIN


/*!
	@brief	The normalized identity rect of { {0, 0}, {1, 1} }.
*/
VN_EXPORT const CGRect VNNormalizedIdentityRect API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*!
	@discussion	Determines whether or not the normalized rect describes the identity rect of { {0, 0}, {1, 1} }.

	@param	normalizedRect			The rectangle in the normalized coordinate space of [0..1].
	
	@return YES if the rect is the identity rect; otherwise, NO.
*/
VN_EXPORT bool VNNormalizedRectIsIdentityRect(CGRect normalizedRect) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*!
	@discussion	Returns a point in (possibly non-integral) image coordinates that is projected from a point in a normalized coordinate space.

	@param	normalizedPoint			The point in the normalized coordinate space of [0..1].
	
	@param	imageWidth				The pixel width of the image.

	@param	imageHeight				The pixel height of the image.

	@return the point in normalized coordinates.
*/
VN_EXPORT CGPoint VNImagePointForNormalizedPoint(CGPoint normalizedPoint, size_t imageWidth, size_t imageHeight) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*!
	@discussion	Returns a rectangle in (possibly non-integral) image coordinates that is projected from a rectangle in a normalized coordinate space.

	@param	normalizedRect			The rectangle in the normalized coordinate space of [0..1].
	
	@param	imageWidth				The pixel width of the image.

	@param	imageHeight				The pixel height of the image.

	@return the rectangle in pixel coordinates.
*/
VN_EXPORT CGRect VNImageRectForNormalizedRect(CGRect normalizedRect, size_t imageWidth, size_t imageHeight) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*!
	@discussion	Returns an image rectangle in normalized coordinates.

	@param	imageRect				The rectangle in image coordinate space.
	
	@param	imageWidth				The pixel width of the image.

	@param	imageHeight				The pixel height of the image.

	@return the normalized rectangle.
*/
VN_EXPORT CGRect VNNormalizedRectForImageRect(CGRect imageRect, size_t imageWidth, size_t imageHeight) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*!
	@discussion Returns the cooridnate of a given face landmark point relative to a face bounding box.
	
	@param	faceLandmarkPoint		A face landmark point obtained from a VNFaceLandmarkRegion2D instance.
	
	@param	faceBoundingBox			The normalized bounding box of a face obtaining from a VNFaceObservation.
	
	@param	imageWidth				The pixel width of the image from which the VNFaceObservation was generated.
	
	@param	imageHeight				The pixel height of the image from which the VNFaceObservation was generated.

	@return	the face landmark point in face bounding box coordinates.
*/
VN_EXPORT CGPoint VNNormalizedFaceBoundingBoxPointForLandmarkPoint(vector_float2 faceLandmarkPoint, CGRect faceBoundingBox, size_t imageWidth, size_t imageHeight) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*!
	@discussion Returns the (possibly non-integral) image cooridnate of a given face landmark point.
	
	@param	faceLandmarkPoint		A face landmark point obtained from a VNFaceLandmarkRegion2D instance.
	
	@param	faceBoundingBox			The normalized bounding box of a face obtaining from a VNFaceObservation.
	
	@param	imageWidth				The pixel width of the image from which the VNFaceObservation was generated.
	
	@param	imageHeight				The pixel height of the image from which the VNFaceObservation was generated.

	@return	the face landmark point in image coordinates.
*/
VN_EXPORT CGPoint VNImagePointForFaceLandmarkPoint(vector_float2 faceLandmarkPoint, CGRect faceBoundingBox, size_t imageWidth, size_t imageHeight) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*!
	@brief Obtain the size, in bytes, of a given element type.
 
	@param	elementType		The element type.
 
	@return a byte count, or 0 if the element type is unknown.
*/
VN_EXPORT NSUInteger VNElementTypeSize(VNElementType elementType) API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));


NS_ASSUME_NONNULL_END
