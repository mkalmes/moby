// ==========  ARKit.framework/Headers/ARMatteGenerator.h
//
//  ARMatteGenerator.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ARFrame;

@protocol MTLTexture;
@protocol MTLCommandBuffer;
@protocol MTLDevice;

NS_ASSUME_NONNULL_BEGIN

/**
 The resolution at which the matte is to be generated.
 @discussion The matte generated per frame can be full resolution of the captured camera image or half resolution. The caller chooses one of the options from ARMatteResolution during initialization.
 */
typedef NS_ENUM(NSInteger, ARMatteResolution) {
    
    /* Matte generated at camera image resolution. */
    ARMatteResolutionFull      = 0,
    
    /* Matte generated at half the camera image resolution. */
    ARMatteResolutionHalf    = 1
    
} NS_SWIFT_NAME(ARMatteGenerator.Resolution);

/**
 An object designed to generate either full resolution or half resolution matte given the ARFrame.
 @discussion The caller initializes the object once and calls the alpha matte generation API for every ARFrame with the captured image and segmentation stencil.
 */
@interface ARMatteGenerator : NSObject

/**
 Initializes an instance of ARMatteGenerator.
 
 @discussion For efficient creation of alpha mattes in real time it is recommended to instantiate this object only once and to generate an alpha matte for every incoming frame.
 @see ARFrame
 @see -[ARMatteGenerator generateMatteFromFrame:commandBuffer:]
 @param device The device the filter will run on.
 @param matteResolution The resolution at which the matte is to be generated. Set using one of the values from 'ARMatteResolution'.
 @see ARMatteResolution
 @return Instance of ARMatteGenerator.
 */
- (instancetype)initWithDevice:(id <MTLDevice>)device matteResolution:(ARMatteResolution)matteResolution NS_DESIGNATED_INITIALIZER;

/**
 Generates alpha matte at either full resolution or half the resolution of the captured image.
 
 @param frame Current ARFrame containing camera image and segmentation stencil. The caller is to ensure that a valid segmentation buffer is present.
 @param commandBuffer Metal command buffer for encoding matting related operations. The command buffer is committed by the caller externally.
 @return Alpha matte MTLTexture for the given ARFrame at full resolution or half resolution as chosen by the  caller during initialization.
 */
- (id <MTLTexture>)generateMatteFromFrame:(ARFrame*)frame commandBuffer:(id <MTLCommandBuffer>)commandBuffer;

/**
 Generates dilated depth at the resolution of the segmentation stencil.
 @discussion The caller can use depth information when compositing a virtual object with the captured scene. This API returns the dilated linear depth to the caller. The reprojection of this depth to the caller's scene space is carried out externally.
 @param frame Current ARFrame containing camera image and estimated depth buffer. The caller is to ensure that a valid depth buffer is present.
 @param commandBuffer Metal command buffer for encoding depth dilation operations. The command buffer is committed by the caller externally.
 @return Dilated depth MTLTexture for the given ARFrame at the segmentation stencil resolution. The texture consists of a single channel and is of type float32.
 */
- (id <MTLTexture>)generateDilatedDepthFromFrame:(ARFrame*)frame commandBuffer:(id <MTLCommandBuffer>)commandBuffer;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARBody2D.h
//
//  ARBody2D.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <ARKit/ARSkeleton.h>
#import <simd/simd.h>


NS_ASSUME_NONNULL_BEGIN

/**
 Representation of a body in 2D.
 */
API_AVAILABLE(ios(13.0))
@interface ARBody2D : NSObject

/**
 The body's skeleton.
 */
@property (nonatomic, readonly) ARSkeleton2D *skeleton;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARCollaborationData.h
//
//  ARCollaborationData.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ARKit/ARSession.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Object representing data for collaborative session.
 
 @discussion This data needs to be sent to each participants in the collaborative session.
 */
API_AVAILABLE(ios(13.0))
NS_SWIFT_NAME(ARSession.CollaborationData)
@interface ARCollaborationData : NSObject

/**
 Data representation of the object.
 @discussion The data representation should be sent to other participants in the collaborative session.
 */
@property (nonatomic, readonly) NSData *data;

/**
 Initialize from data representation.
 @discussion This data is recieved from other participants in the collaborative session.
 
 @param data Data representation.
 */
- (instancetype)initWithData:(NSData *)data;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARSkeleton.h
//
//  ARSkeleton.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <ARKit/ARSkeletonDefinition.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An object representing a skeleton.
 @discussion A skeleton's structure is defined by a skeleton definition.
 @see ARSkeletonDefinition
 */
API_AVAILABLE(ios(13.0))
@interface ARSkeleton : NSObject

/**
 Skeleton definition.
 */
@property (nonatomic, readonly) ARSkeletonDefinition *definition;

/**
 The number of joints.
 */
@property (nonatomic, readonly) NSUInteger jointCount NS_REFINED_FOR_SWIFT;

/**
 Tracking state for a given joint.
 
 @param jointIndex The index of the joint.
 @return True if the joint is tracked. False otherwise.
 */
- (BOOL)isJointTracked:(NSInteger)jointIndex;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 An object representing a skeleton in 3D.
 */
API_AVAILABLE(ios(13.0))
@interface ARSkeleton3D : ARSkeleton

/**
 The model space transforms for each joint.
 */
@property (nonatomic, readonly) const simd_float4x4 *jointModelTransforms NS_REFINED_FOR_SWIFT;

/**
 The local space joint data for each joint.
 */
@property (nonatomic, readonly) const simd_float4x4 *jointLocalTransforms NS_REFINED_FOR_SWIFT;

/**
 Returns the model transform for a joint with a given name.
 
 @discussion If an invalid joint name is passed the returned matrix will be filled with NaN values.
 @param jointName The name of the joint.
 @return Model transform
 */
- (simd_float4x4)modelTransformForJointName:(ARSkeletonJointName)jointName NS_REFINED_FOR_SWIFT;

/**
 Returns the local transform for a joint with a given name.
 
 @discussion If an invalid joint name is passed the returned matrix will be filled with NaN values.
 @param jointName The name of the joint.
 @return Local transform
 */
- (simd_float4x4)localTransformForJointName:(ARSkeletonJointName)jointName NS_REFINED_FOR_SWIFT;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


/**
 An object representing a skeleton in 2D.
 */
API_AVAILABLE(ios(13.0))
@interface ARSkeleton2D : ARSkeleton

/**
 The joint landmarks in normalized coordinates.
 @discussion The joint landmarks are detected in the captured image on the ARFrame.
 @see -[ARFrame capturedImage]
 */
@property (nonatomic, readonly) const simd_float2 *jointLandmarks NS_REFINED_FOR_SWIFT;

/**
 Returns the landmark point for a joint with a given name.
 @discussion If an invalid joint name is passed the returned point will be filled with NaN values.
 
 @param jointName The name of the joint.
 @return Landmark in normalized image coordinates.
 */
- (simd_float2)landmarkForJointNamed:(ARSkeletonJointName)jointName NS_REFINED_FOR_SWIFT;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARLightEstimate.h
//
//  ARLightEstimate.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A light estimate representing the light in the scene.
 */
API_AVAILABLE(ios(11.0))
@interface ARLightEstimate : NSObject

/**
 Ambient intensity of the lighting.
 
 @discussion In a well lit environment, this value is close to 1000. It typically ranges from 0 (very dark) to around 2000 (very bright).
 */
@property (nonatomic, readonly) CGFloat ambientIntensity;

/**
 The ambient color temperature of the lighting.

 @discussion This specifies the ambient color temperature of the lighting in Kelvin (6500 corresponds to pure white).
*/
@property (nonatomic, readonly) CGFloat ambientColorTemperature;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


/**
 A directional light estimate representing the light intensity and direction in the scene.
 */
API_AVAILABLE(ios(11.0))
@interface ARDirectionalLightEstimate : ARLightEstimate

/**
 Second degree spherical harmonics coefficients representing the intensity of light.
 
 @discussion The data is an array of 27 32-bit floating-point values, containing three non-interleaved data sets
 corresponding to the red, green, and blue sets of coefficients.
 */
@property (nonatomic, copy, readonly) NSData *sphericalHarmonicsCoefficients;

/**
 The primary direction of light.
 */
@property (nonatomic, readonly) simd_float3 primaryLightDirection;

/**
 The intensity of light in the primary direction.
 */
@property (nonatomic, readonly) CGFloat primaryLightIntensity;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARFaceAnchor.h
//
//  ARFaceAnchor.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Blend shape locations of a face geometry.
 @discussion Each location defines an area of the face that can be displaced with a provided coefficient.
 */
typedef NSString *ARBlendShapeLocation NS_STRING_ENUM NS_SWIFT_NAME(ARFaceAnchor.BlendShapeLocation) API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowDownLeft           API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowDownRight          API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowInnerUp            API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowOuterUpLeft        API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowOuterUpRight       API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationCheekPuff              API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationCheekSquintLeft        API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationCheekSquintRight       API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeBlinkLeft           API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeBlinkRight          API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookDownLeft        API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookDownRight       API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookInLeft          API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookInRight         API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookOutLeft         API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookOutRight        API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookUpLeft          API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookUpRight         API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeSquintLeft          API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeSquintRight         API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeWideLeft            API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeWideRight           API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationJawForward             API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationJawLeft                API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationJawOpen                API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationJawRight               API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthClose             API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthDimpleLeft        API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthDimpleRight       API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthFrownLeft         API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthFrownRight        API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthFunnel            API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthLeft              API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthLowerDownLeft     API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthLowerDownRight    API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthPressLeft         API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthPressRight        API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthPucker            API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthRight             API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthRollLower         API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthRollUpper         API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthShrugLower        API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthShrugUpper        API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthSmileLeft         API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthSmileRight        API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthStretchLeft       API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthStretchRight      API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthUpperUpLeft       API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthUpperUpRight      API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationNoseSneerLeft          API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationNoseSneerRight         API_AVAILABLE(ios(11.0));
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationTongueOut              API_AVAILABLE(ios(12.0));

@class ARFaceGeometry;

/**
 An anchor representing a face and its geometry.
 */
API_AVAILABLE(ios(11.0))
@interface ARFaceAnchor : ARAnchor <ARTrackable>

/**
 The face geometry updated based on the computed blend shapes.
 */
@property (nonatomic, readonly) ARFaceGeometry *geometry;

/**
 The left eye’s rotation and translation relative to the anchor’s origin.
 */
@property (nonatomic, readonly) simd_float4x4 leftEyeTransform API_AVAILABLE(ios(12.0));

/**
 The right eye’s rotation and translation relative to the anchor’s origin.
 */
@property (nonatomic, readonly) simd_float4x4 rightEyeTransform API_AVAILABLE(ios(12.0));

/**
 Look-at point relative to the anchor’s origin.
 */
@property (nonatomic, readonly) simd_float3 lookAtPoint API_AVAILABLE(ios(12.0));

/**
 A dictionary of blend shape coefficients for each blend shape location.
 @discussion Blend shapes coefficients define the amount of displacement of a neutral shape at a specific location on the face.
 */
@property (nonatomic, readonly) NSDictionary<ARBlendShapeLocation, NSNumber*> *blendShapes;

/** Unavailable */
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARSKView.h
//
//  ARSKView.h
//  ARKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <SpriteKit/SpriteKit.h>
#import <ARKit/ARSession.h>
#import <ARKit/ARHitTestResult.h>

NS_ASSUME_NONNULL_BEGIN

@class ARSKView;

#pragma mark ARSKViewDelegate

API_AVAILABLE(ios(11.0))
@protocol ARSKViewDelegate <SKViewDelegate, ARSessionObserver>
@optional

/**
 Implement this to provide a custom node for the given anchor.
 
 @discussion This node will automatically be added to the scene graph.
 If this method is not implemented, a node will be automatically created.
 If nil is returned the anchor will be ignored.
 @param view The view that will render the scene.
 @param anchor The added anchor.
 @return Node that will be mapped to the anchor or nil.
 */
- (nullable SKNode *)view:(ARSKView *)view nodeForAnchor:(ARAnchor *)anchor;

/**
 Called when a new node has been mapped to the given anchor.
 
 @param view The view that will render the scene.
 @param node The node that maps to the anchor.
 @param anchor The added anchor.
 */
- (void)view:(ARSKView *)view didAddNode:(SKNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a node will be updated with data from the given anchor.
 
 @param view The view that will render the scene.
 @param node The node that will be updated.
 @param anchor The anchor that was updated.
 */
- (void)view:(ARSKView *)view willUpdateNode:(SKNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a node has been updated with data from the given anchor.
 
 @param view The view that will render the scene.
 @param node The node that was updated.
 @param anchor The anchor that was updated.
 */
- (void)view:(ARSKView *)view didUpdateNode:(SKNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a mapped node has been removed from the scene graph for the given anchor.
 
 @param view The view that will render the scene.
 @param node The node that was removed.
 @param anchor The anchor that was removed.
 */
- (void)view:(ARSKView *)view didRemoveNode:(SKNode *)node forAnchor:(ARAnchor *)anchor;

@end


#pragma mark ARSKView


/**
 A view that integrates ARSession rendering into SpriteKit.
 
 @discussion The view draws the camera background, and projects and maps anchors to nodes.
 */
API_AVAILABLE(ios(11.0))
@interface ARSKView : SKView<ARSessionProviding>

/**
 Specifies the view’s delegate.
 */
@property (nonatomic, weak, nullable) NSObject <ARSKViewDelegate> *delegate;

/**
 The session that the view uses to update the view.
 */
@property (nonatomic, strong) ARSession *session;

/**
 Searches the scene hierarchy for an anchor associated with the provided node.
 @param node A node in the view’s scene.
 */
- (nullable ARAnchor *)anchorForNode:(SKNode *)node;

/**
 Returns the node that has been mapped to a specific anchor.
 @param anchor An anchor with an existing node mapping.
 */
- (nullable SKNode *)nodeForAnchor:(ARAnchor *)anchor;

/**
 Searches the current frame for objects corresponding to a point in the view.
 
 @discussion A 2D point in the view’s coordinate space can refer to any point along a line segment
 in the 3D coordinate space. Hit-testing is the process of finding objects in the world located along this line segment.
 @param point A point in the view’s coordinate system.
 @param types The types of results to search for.
 @return An array of all hit-test results sorted from nearest to farthest.
 */
- (NSArray<ARHitTestResult *> *)hitTest:(CGPoint)point types:(ARHitTestResultType)types;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARQuickLookPreviewItem.h
//
//  ARQuickLookPreviewItem.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuickLook/QLPreviewItem.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0))
@interface ARQuickLookPreviewItem : NSObject <QLPreviewItem>

/**
 Creates an object representing the 3D content that will be previewed in AR Quick Look.
 
 @discussion This object will be previewed in AR Quick Look using the default
 behavior:
 
 - Start in Object mode without camera passthrough
 
 - Display the Share button for 3D content sharing
 
 - Allow scaling content in both Object and AR mode
 
 This is a promise to the ARQuickLookPreviewItem class that the URL points to a 3D content file. This class does not deal with the file's existence or content, and leaves it up to QuickLook to handle and process the URL.
 
 @param url A file URL to 3D content file (e.g. usdz).
 @return The preview object to display in AR Quick Look.
 */
- (instancetype)initWithFileAtURL:(NSURL *)url NS_DESIGNATED_INITIALIZER;

/**
 An optional canonical web page URL for the 3D content that will be shared.
 
 @discussion If this is supplied, the URL to the canonical web page is shared instead of the 3D content file.
 For example, providing https://developer.apple.com/arkit/gallery/ as the canonical web page URL string will be shared via the Share button. If the web page URL string is malformed or not provided, then AR Quick Look will default to sharing the 3D content.
 */
@property (nonatomic, strong, nullable) NSURL *canonicalWebPageURL;

/**
 Whether or not AR Quick Look allows content scaling in AR mode.
 Defaults to `YES` which allows scaling content in AR mode.
 */
@property (nonatomic, assign) BOOL allowsContentScaling;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARHitTestResult.h
//
//  ARHitTestResult.h
//  ARKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>
#import <simd/simd.h>

@class ARAnchor;

/**
 Option set of hit-test result types.
 */
API_AVAILABLE(ios(11.0))
typedef NS_OPTIONS(NSUInteger, ARHitTestResultType) {
    /** Result type from intersecting the nearest feature point. */
    ARHitTestResultTypeFeaturePoint                                        = (1 << 0),
    
    /** Result type from intersecting a horizontal plane estimate, determined for the current frame. */
    ARHitTestResultTypeEstimatedHorizontalPlane                            = (1 << 1),
    
    /** Result type from intersecting a vertical plane estimate, determined for the current frame. */
    ARHitTestResultTypeEstimatedVerticalPlane API_AVAILABLE(ios(11.3))     = (1 << 2),
    
    /** Result type from intersecting with an existing plane anchor. */
    ARHitTestResultTypeExistingPlane                                       = (1 << 3),
    
    /** Result type from intersecting with an existing plane anchor, taking into account the plane’s extent. */
    ARHitTestResultTypeExistingPlaneUsingExtent                            = (1 << 4),
    
    /** Result type from intersecting with an existing plane anchor, taking into account the plane’s geometry. */
    ARHitTestResultTypeExistingPlaneUsingGeometry API_AVAILABLE(ios(11.3)) = (1 << 5),
} NS_SWIFT_NAME(ARHitTestResult.ResultType);

NS_ASSUME_NONNULL_BEGIN

/**
 A result of an intersection found during a hit-test.
 */
API_AVAILABLE(ios(11.0))
@interface ARHitTestResult : NSObject

/**
 The type of the hit-test result.
 */
@property (nonatomic, readonly) ARHitTestResultType type;

/**
 The distance from the camera to the intersection in meters.
 */
@property (nonatomic, readonly) CGFloat distance;

/**
 The transformation matrix that defines the intersection’s rotation, translation and scale
 relative to the anchor or nearest feature point.
 */
@property (nonatomic, readonly) simd_float4x4 localTransform;

/**
 The transformation matrix that defines the intersection’s rotation, translation and scale
 relative to the world.
 */
@property (nonatomic, readonly) simd_float4x4 worldTransform;

/**
 The anchor that the hit-test intersected.
 
 @discussion An anchor will only be provided for existing plane result types.
 */
@property (nonatomic, strong, nullable, readonly) ARAnchor *anchor;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARTrackedRaycast.h
//
//  ARTrackedRaycast.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>
#import "ARRaycastQuery.h"

NS_ASSUME_NONNULL_BEGIN

/**
 A tracked raycast representation.
 */
API_AVAILABLE(ios(13.0))
@interface ARTrackedRaycast: NSObject

/**
 Update the raycast query.
 @discussion If raycast of the new query fails, an empty result is sent to the update handler and the query's ray will be no longer tracked.
 */
- (void)updateQuery:(ARRaycastQuery *)query;

/**
 Stop raycasting.
 @discussion The raycast will be continuously tracked until stopped.
 Resetting session's tracking, changing its configuration or deallocation of ARTrackedRaycast object cause the raycast to stop.
 */
- (void)stopTracking;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARRaycastQuery.h
//
//  ARRaycastQuery.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A value describing the target of a ray used for raycasting.
 */
API_AVAILABLE(ios(13.0))
typedef NS_ENUM(NSInteger, ARRaycastTarget) {
    
    /** Ray's target is an already detected plane, considering the plane's estimated size and shape. */
    ARRaycastTargetExistingPlaneGeometry,
    
    /** Ray's target is an already detected plane, without considering the plane's size. */
    ARRaycastTargetExistingPlaneInfinite,
    
    /**
     Ray's target is a plane that is estimated using the feature points around the ray.
     When alignment is ARRaycastTargetAlignmentAny, alignment of estimated planes is based on the normal of the real world
     surface corresponding to the estimated plane.
     */
    ARRaycastTargetEstimatedPlane,
} NS_SWIFT_NAME(ARRaycastQuery.Target);

/**
 A value describing the alignment of a target.
 */
API_AVAILABLE(ios(13.0))
typedef NS_ENUM(NSInteger, ARRaycastTargetAlignment) {
    /** A target that is horizontal with respect to gravity. */
    ARRaycastTargetAlignmentHorizontal,
    
    /** A target that is vertical with respect to gravity. */
    ARRaycastTargetAlignmentVertical,
    
    /** A target that is in any alignment, inclusive of horizontal and vertical. */
    ARRaycastTargetAlignmentAny
    
} NS_SWIFT_NAME(ARRaycastQuery.TargetAlignment);


/**
 Representation of a ray and its target which is used for raycasting.
 @discussion Represents a 3D ray and its target which is used to perform raycasting.
 */
API_AVAILABLE(ios(13.0))
@interface ARRaycastQuery : NSObject

/**
 Origin of the ray.
 */
@property (nonatomic, readonly) simd_float3 origin;

/**
 Direction of the ray.
 */
@property (nonatomic, readonly) simd_float3 direction;

/**
 Type of target where the ray should terminate.
 */
@property (nonatomic, readonly) ARRaycastTarget target;

/**
 The alignment of the target that should be considered for raycasting.
 */
@property (nonatomic, readonly) ARRaycastTargetAlignment targetAlignment;

/**
 Create a new ARRaycastQuery with the provided origin, direction, allowed target and its alignment.
 @param origin Origin of the ray.
 @param direction Direction of the ray.
 @param target Type of target where the ray is allowed to terminate.
 @param alignment Alignment of the target that should be considered for raycasting.
 */
- (instancetype)initWithOrigin:(simd_float3)origin direction:(simd_float3)direction allowingTarget:(ARRaycastTarget)target alignment:(ARRaycastTargetAlignment)alignment;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARParticipantAnchor.h
//
//  ARParticipantAnchor.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

NS_ASSUME_NONNULL_BEGIN

/**
 This anchor represents the physical position and orientation of another participant in the collaborative session.
 
 @discussion The participant anchors are automatically added to the ARSession and are updated with each frame.
           The participant can be identified by `sessionIdentifier` property of the anchor.
 */
API_AVAILABLE(ios(13.0))
@interface ARParticipantAnchor : ARAnchor

/** Unavailable */
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARBodyAnchor.h
//
//  ARBodyAnchor.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>
#import <CoreGraphics/CGGeometry.h>

NS_ASSUME_NONNULL_BEGIN

@class ARBody2D;
@class ARSkeleton3D;

/**
 An anchor representing a body in the world.
 */
API_AVAILABLE(ios(13.0))
@interface ARBodyAnchor : ARAnchor <ARTrackable>

/**
 The tracked skeleton in 3D.
 @note The default height of this skeleton is defined to be 1.8 meters.
 */
@property (nonatomic, strong, readonly) ARSkeleton3D *skeleton;

/**
 The factor between estimated physical size and default size of the skeleton.
 @see -[ARSkeletonDefinition neutralBodySkeleton3D]
 
 @discussion This value will be estimated if automaticSkeletonScaleEstimationEnabled is set to true on the ARBodyTrackingConfiguration.
 It is used to correct the transform's translation. Default value is 1.0.
 */
@property (nonatomic, readonly) CGFloat estimatedScaleFactor;

/** Unavailable */
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

// ==========  ARKit.framework/Headers/ARReferenceImage.h
//
//  ARReferenceImage.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <ImageIO/CGImageProperties.h>
#import <CoreVideo/CVPixelBuffer.h>

@class CIImage;

NS_ASSUME_NONNULL_BEGIN

/**
 A reference image to be detected in the scene.
 */
API_AVAILABLE(ios(11.3))
@interface ARReferenceImage : NSObject

/**
 An optional name used to identify the image.
 */
@property (nonatomic, copy, nullable) NSString *name;

/**
 The physical size of the image in meters.
 */
@property (nonatomic, readonly) CGSize physicalSize;

/**
 The AR resource group name for this image.
 @discussion If this image was loaded via an AR resource group in the Xcode asset catalogue this property will have the name of the resource group,
 else be set to nil.
 */
@property (nonatomic, strong, nullable, readonly) NSString *resourceGroupName API_AVAILABLE(ios(13.0));

/**
 Validate if this image can be used for image detection or tracking.
 @discussion When loading reference images from the asset catalog this verification is not needed as the same verification happens
 at compile time.
 @param completionHandler Completion handler invoked when validation is done. The completion handler takes the following parameters:
 error - An error that indicates why the image is not suitable for tracking, or nil if no error occured.
 */
- (void)validateWithCompletionHandler:(void (^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0));

/**
 Creates a new reference image.
 
 @param image The reference image as CGImage.
 @param orientation The image orientation.
 @param physicalWidth The width in meters of the physical object.
 */
- (instancetype)initWithCGImage:(CGImageRef)image orientation:(CGImagePropertyOrientation)orientation physicalWidth:(CGFloat)physicalWidth NS_SWIFT_NAME(init(_:orientation:physicalWidth:));

/**
 Creates a new reference image.
 
 @param pixelBuffer The reference image as CVPixelBuffer.
 @param physicalWidth The width in meters of the physical object.
 @param orientation The image orientation.
 */
- (instancetype)initWithPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(CGImagePropertyOrientation)orientation physicalWidth:(CGFloat)physicalWidth NS_SWIFT_NAME(init(_:orientation:physicalWidth:));

/**
 Returns the set of ARReferenceImages in the specified resource group and bundle.

 @param name The name of the resource group.
 @param bundle The bundle containing the image file or asset catalog. Specify nil to search the app’s main bundle.
 @return The set of reference images or nil on error.
 */
+ (nullable NSSet<ARReferenceImage *> *)referenceImagesInGroupNamed:(NSString *)name bundle:(nullable NSBundle *)bundle;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARVideoFormat.h
//
//  ARVideoFormat.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <AVFoundation/AVCaptureDevice.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.3))
NS_SWIFT_NAME(ARConfiguration.VideoFormat)
@interface ARVideoFormat : NSObject <NSCopying>

/**
 Indicates the physical position of an AVCaptureDevice's hardware on the system.
 */
@property (nonatomic, readonly) AVCaptureDevicePosition captureDevicePosition API_AVAILABLE(ios(13.0));

/**
 Image resolution.
 */
@property (nonatomic, readonly) CGSize imageResolution;

/**
 Frame rate.
 */
@property (nonatomic, readonly) NSInteger framesPerSecond;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARKit.h
//
//  ARKit.h
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

/** @framework ARKit
    @abstract A high-level Augmented Reality framework.
    @discussion ARKit lets you easily configure and use Augmented Reality techniques to track, detect, and render.
 */

#import <ARKit/ARError.h>

#import <ARKit/ARSession.h>
#import <ARKit/ARConfiguration.h>
#import <ARKit/ARFrame.h>
#import <ARKit/ARCamera.h>
#import <ARKit/ARHitTestResult.h>
#import <ARKit/ARLightEstimate.h>
#import <ARKit/ARPointCloud.h>
#import <ARKit/ARReferenceImage.h>
#import <ARKit/ARReferenceObject.h>
#import <ARKit/ARVideoFormat.h>
#import <ARKit/ARCollaborationData.h>
#import <ARKit/ARWorldMap.h>
#import <ARKit/ARRaycastQuery.h>
#import <ARKit/ARTrackedRaycast.h>
#import <ARKit/ARRaycastResult.h>

#import <ARKit/ARAnchor.h>
#import <ARKit/AREnvironmentProbeAnchor.h>
#import <ARKit/ARFaceAnchor.h>
#import <ARKit/ARFaceGeometry.h>
#import <ARKit/ARImageAnchor.h>
#import <ARKit/ARObjectAnchor.h>
#import <ARKit/ARParticipantAnchor.h>
#import <ARKit/ARPlaneAnchor.h>
#import <ARKit/ARPlaneGeometry.h>

#import <ARKit/ARSkeleton.h>
#import <ARKit/ARSkeletonDefinition.h>
#import <ARKit/ARBody2D.h>
#import <ARKit/ARBodyAnchor.h>

#import <ARKit/ARCoachingOverlayView.h>
#import <ARKit/ARSCNView.h>
#import <ARKit/ARSKView.h>
#import <ARKit/ARMatteGenerator.h>

#import <ARKit/ARQuickLookPreviewItem.h>
// ==========  ARKit.framework/Headers/ARCamera.h
//
//  ARCamera.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIApplication.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A value describing the camera’s tracking state.
 */
API_AVAILABLE(ios(11.0))
typedef NS_ENUM(NSInteger, ARTrackingState) {
    /** Tracking is not available. */
    ARTrackingStateNotAvailable,
    
    /** Tracking is limited. See tracking reason for details. */
    ARTrackingStateLimited,
    
    /** Tracking is Normal. */
    ARTrackingStateNormal,
} NS_REFINED_FOR_SWIFT;

/**
 A reason describing why the camera’s tracking state is limited.
 */
API_AVAILABLE(ios(11.0))
typedef NS_ENUM(NSInteger, ARTrackingStateReason) {
    /** Tracking is not limited. */
    ARTrackingStateReasonNone,
    
    /** Tracking is limited due to initialization in progress. */
    ARTrackingStateReasonInitializing,
    
    /** Tracking is limited due to a excessive motion of the camera. */
    ARTrackingStateReasonExcessiveMotion,
    
    /** Tracking is limited due to a lack of features visible to the camera. */
    ARTrackingStateReasonInsufficientFeatures,
    
    /** Tracking is limited due to a relocalization in progress. */
    ARTrackingStateReasonRelocalizing API_AVAILABLE(ios(11.3)),
} NS_REFINED_FOR_SWIFT;


/**
 A model representing the camera and its parameters.
 */
API_AVAILABLE(ios(11.0))
@interface ARCamera : NSObject <NSCopying>

/**
 The transformation matrix that defines the camera’s rotation and translation in world coordinates.
 */
@property (nonatomic, readonly) simd_float4x4 transform;

/**
 The camera’s orientation defined as Euler angles.
 
 @dicussion The order of components in this vector matches the axes of rotation:
               1. Pitch (the x component) is the rotation about the node’s x-axis (in radians)
               2. Yaw   (the y component) is the rotation about the node’s y-axis (in radians)
               3. Roll  (the z component) is the rotation about the node’s z-axis (in radians)
            ARKit applies these rotations in the following order:
               1. first roll
               2. then pitch
               3. then yaw
 */
@property (nonatomic, readonly) simd_float3 eulerAngles;

/**
 The tracking state of the camera.
 */
@property (nonatomic, readonly) ARTrackingState trackingState NS_REFINED_FOR_SWIFT;

/**
 The reason for the camera’s current tracking state.
 */
@property (nonatomic, readonly) ARTrackingStateReason trackingStateReason NS_REFINED_FOR_SWIFT;

/**
 The camera intrinsics.
 @discussion The matrix has the following contents:
 fx 0   px
 0  fy  py
 0  0   1
 fx and fy are the focal length in pixels.
 px and py are the coordinates of the principal point in pixels.
 The origin is at the center of the upper-left pixel.
 */
@property (nonatomic, readonly) simd_float3x3 intrinsics;

/**
 The camera image resolution in pixels.
 */
@property (nonatomic, readonly) CGSize imageResolution;

/**
 The camera exposure duration in seconds.
 */
@property (nonatomic, readonly) NSTimeInterval exposureDuration API_AVAILABLE(ios(13.0));

/**
 The camera exposure offset in EV (exposure value) units.
 */
@property (nonatomic, readonly) float exposureOffset API_AVAILABLE(ios(13.0));

/**
 The projection matrix of the camera.
 @discussion The projection matrix assumes no far clipping plane limit.
*/
@property (nonatomic, readonly) simd_float4x4 projectionMatrix;

/**
 Creates a projection matrix for the camera given rendering parameters.
 
 @discussion The projection matrix returned provides an aspect fill for the provided viewport size and orientation.
 If zFar is set to 0, an infinite projection matrix will be returned.
 @param orientation Viewport orientation.
 @param viewportSize Viewport size.
 @param zNear Near depth limit.
 @param zFar Far depth limit.
 */
- (simd_float4x4)projectionMatrixForOrientation:(UIInterfaceOrientation)orientation viewportSize:(CGSize)viewportSize zNear:(CGFloat)zNear zFar:(CGFloat)zFar;

/**
 Project a 3D point in world coordinate system into 2D viewport space.
 
 @param point 3D point in world coordinate system.
 @param orientation Viewport orientation.
 @param viewportSize Viewport (or image) size.
 @return 2D point in viewport coordinate system with origin at top-left.
 */
- (CGPoint)projectPoint:(simd_float3)point orientation:(UIInterfaceOrientation)orientation viewportSize:(CGSize)viewportSize;

/**
 Unproject a 2D point from the viewport onto a plane in 3D world coordinates.
 
 @discussion A 2D point in the viewport coordinate space can refer to any point along a line segment
 in the 3D coordinate space. Unprojecting calculates the 3D position of the point along this line segment that intersects the provided plane.
 @param point A point in the viewport coordinate system with origin at top-left.
 @param planeTransform The transform used to define the coordinate system of the plane.
 The coordinate system’s positive Y axis is assumed to be the normal of the plane.
 @return 3D position in world coordinates or a NAN values if unprojection is not possible.
 */
- (simd_float3)unprojectPoint:(CGPoint)point ontoPlaneWithTransform:(simd_float4x4)planeTransform orientation:(UIInterfaceOrientation)orientation viewportSize:(CGSize)viewportSize
API_AVAILABLE(ios(12.0)) NS_REFINED_FOR_SWIFT;

/**
 Returns the view matrix for the camera with a given interface orientation.
 
 @discussion The view matrix can be used to transform geometry from world space into camera space for a given orientation.
 @param orientation The interface orientation that will be used to render the camera’s view.
 */
- (simd_float4x4)viewMatrixForOrientation:(UIInterfaceOrientation)orientation;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARPlaneGeometry.h
//
//  ARPlaneGeometry.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNGeometry.h>
#import <simd/simd.h>

@protocol MTLDevice;

NS_ASSUME_NONNULL_BEGIN

/**
 Object representing the geometry of a plane.
 @discussion The plane geometry will have a growing number of triangles
 and vertices updated from frame to frame.
 */
API_AVAILABLE(ios(11.3))
@interface ARPlaneGeometry : NSObject<NSSecureCoding>

/**
 The number of mesh vertices of the geometry.
 */
@property (nonatomic, readonly) NSUInteger vertexCount NS_REFINED_FOR_SWIFT;

/**
 The mesh vertices of the geometry.
 */
@property (nonatomic, readonly) const simd_float3 *vertices NS_REFINED_FOR_SWIFT;

/**
 The number of texture coordinates of the geometry.
 */
@property (nonatomic, readonly) NSUInteger textureCoordinateCount NS_REFINED_FOR_SWIFT;

/**
 The texture coordinates of the geometry.
 */
@property (nonatomic, readonly) const simd_float2 *textureCoordinates NS_REFINED_FOR_SWIFT;

/**
 The number of triangles of the geometry.
 */
@property (nonatomic, readonly) NSUInteger triangleCount;

/**
 The triangle indices of the geometry.
 */
@property (nonatomic, readonly) const int16_t *triangleIndices NS_REFINED_FOR_SWIFT;

/**
 The number of boundary vertices of the geometry.
 */
@property (nonatomic, readonly) NSUInteger boundaryVertexCount NS_REFINED_FOR_SWIFT;

/**
 The vertices of the geometry's outermost boundary.
 */
@property (nonatomic, readonly) const simd_float3 *boundaryVertices NS_REFINED_FOR_SWIFT;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


/**
 A SceneKit geometry representing a plane.
 */
API_AVAILABLE(ios(11.3))
@interface ARSCNPlaneGeometry : SCNGeometry

/**
 Creates a new plane geometry using a Metal device.
 
 @param device A Metal device.
 @return A new plane geometry.
 */
+ (nullable instancetype)planeGeometryWithDevice:(id<MTLDevice>)device;

/**
 Updates the geometry with the vertices of a plane geometry.
 
 @param planeGeometry A plane geometry.
 */
- (void)updateFromPlaneGeometry:(ARPlaneGeometry *)planeGeometry;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARFrame.h
//
//  ARFrame.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>
#import <UIKit/UIApplication.h>
#import <simd/simd.h>
#import <ARKit/ARHitTestResult.h>
#import <ARKit/ARRaycastQuery.h>

@class ARAnchor;
@class ARCamera;
@class ARLightEstimate;
@class ARPointCloud;
@class AVDepthData;
@class ARBody2D;

@protocol MTLTexture;

NS_ASSUME_NONNULL_BEGIN

/**
 Segmentation classes which defines a pixel's semantic label.
 @discussion When running a configuration with 'ARFrameSemanticPersonSegmentation' every pixel in the
 segmentationBuffer on the ARFrame will conform to one of these classes.
 @see -[ARConfiguration setFrameSemantics:]
 @see -[ARFrame segmentationBuffer]
*/
API_AVAILABLE(ios(13.0))
typedef NS_ENUM(uint8_t, ARSegmentationClass) {

     /* Pixel has been not been classified. */
    ARSegmentationClassNone      = 0,

    /* Pixel has been classified as person. */
    ARSegmentationClassPerson    = 255

} NS_SWIFT_NAME(ARFrame.SegmentationClass);

/**
 A value describing the world mapping status for the area visible in a given frame.
 */
API_AVAILABLE(ios(12.0))
typedef NS_ENUM(NSInteger, ARWorldMappingStatus) {
    /** World mapping is not available. */
    ARWorldMappingStatusNotAvailable,
    
    /** World mapping is available but has limited features.
     For the device's current position, the session’s world map is not recommended for relocalization. */
    ARWorldMappingStatusLimited,
    
    /** World mapping is actively extending the map with the user's motion.
     The world map will be relocalizable for previously visited areas but is still being updated for the current space. */
    ARWorldMappingStatusExtending,
    
    /** World mapping has adequately mapped the visible area.
     The map can be used to relocalize for the device's current position. */
    ARWorldMappingStatusMapped
} NS_SWIFT_NAME(ARFrame.WorldMappingStatus);

/**
 An object encapsulating the state of everything being tracked for a given moment in time.
 @discussion The model provides a snapshot of all data needed to render a given frame.
 */
API_AVAILABLE(ios(11.0))
@interface ARFrame : NSObject <NSCopying>

/**
 A timestamp identifying the frame.
 */
@property (nonatomic, readonly) NSTimeInterval timestamp;

/**
 The frame’s captured image.
 */
@property (nonatomic, readonly) CVPixelBufferRef capturedImage;

/**
 A tileable texture that contains image noise matching the current camera streams
 noise properties.
 
 @discussion A camera stream depicts image noise that gives the captured image
    a grainy look and varies with light conditions.
 The variations are stored along the depth dimension of the camera grain texture
 and can be selected at runtime using the camera grain intensity of the current frame.
 */
@property (nonatomic, nullable, readonly) id<MTLTexture> cameraGrainTexture API_AVAILABLE(ios(13.0));

/**
 The frame’s camera grain intensity in range 0 to 1.
 
 @discussion A camera stream depicts image noise that gives the captured image
 a grainy look and varies with light conditions.
 The camera grain intensity can be used to select a texture slice from the frames
 camera grain texture.
 */
@property (nonatomic, readonly) float cameraGrainIntensity API_AVAILABLE(ios(13.0));

/**
 The frame’s captured depth data.
 @discussion Depth data is only provided with face tracking on frames where depth data was captured.
 */
@property (nonatomic, strong, nullable, readonly) AVDepthData *capturedDepthData;

/**
 A timestamp identifying the depth data.
 */
@property (nonatomic, readonly) NSTimeInterval capturedDepthDataTimestamp;

/**
 The camera used to capture the frame’s image.
 @discussion The camera provides the device’s position and orientation as well as camera parameters.
 */
@property (nonatomic, copy, readonly) ARCamera *camera;

/**
 A list of anchors in the scene.
 */
@property (nonatomic, copy, readonly) NSArray<ARAnchor *> *anchors;

/**
 A light estimate representing the light in the scene.
 @discussion Returns nil if there is no light estimation.
 */
@property (nonatomic, strong, nullable, readonly) ARLightEstimate *lightEstimate;

/**
 Feature points in the scene with respect to the frame’s origin.
 @discussion The feature points are only provided for configurations using world tracking.
 */
@property (nonatomic, strong, nullable, readonly) ARPointCloud *rawFeaturePoints;

/**
 The status of world mapping for the area visible to the frame.
 @discussion This can be used to identify the state of the world map for the visible area and if additional scanning
 should be done before saving a world map.
 */
@property (nonatomic, readonly) ARWorldMappingStatus worldMappingStatus API_AVAILABLE(ios(12.0));

/**
 A buffer that represents the segmented content of the capturedImage.
 @discussion In order to identify to which class a pixel has been classified one needs to compare its intensity value with the values
 found in `ARSegmentationClass`.
 @see ARSegmentationClass
 @see -[ARConfiguration setFrameSemantics:]
*/
@property (nonatomic, nullable, readonly) CVPixelBufferRef segmentationBuffer API_AVAILABLE(ios(13.0));

/**
 A buffer that represents the estimated depth values for a performed segmentation.
 @discussion For each non-background pixel in the segmentation buffer the corresponding depth value can be accessed in this buffer.
 @see -[ARConfiguration setFrameSemantics:]
 @see -[ARFrame segmentationBuffer]
 */
@property (nonatomic, nullable, readonly) CVPixelBufferRef estimatedDepthData API_AVAILABLE(ios(13.0));

/**
 A detected body in the current frame.
 @see -[ARConfiguration setFrameSemantics:]
 */
@property (nonatomic, nullable, readonly) ARBody2D *detectedBody API_AVAILABLE(ios(13.0));

/**
 Searches the frame for objects corresponding to a point in the captured image.
 
 @discussion A 2D point in the captured image’s coordinate space can refer to any point along a line segment
 in the 3D coordinate space. Hit-testing is the process of finding objects in the world located along this line segment.
 @param point A point in the image-space coordinate system of the captured image.
 Values should range from (0,0) - upper left corner to (1,1) - lower right corner.
 @param types The types of results to search for.
 @return An array of all hit-test results sorted from nearest to farthest.
 */
- (NSArray<ARHitTestResult *> *)hitTest:(CGPoint)point types:(ARHitTestResultType)types;

/**
 Creates a raycast query originating from the point on the captured image, aligned along the center of the field of view of the camera.
 @discussion A 2D point in the captured image’s coordinate space and the field of view of the frame's camera is used to create a ray in the 3D cooridnate space originating at the point.
 @param point A point in the image-space coordinate system of the captured image.
 Values should range from (0,0) - upper left corner to (1,1) - lower right corner.
 @param target Type of target where the ray should terminate.
 @param alignment Alignment of the target.
 */
- (ARRaycastQuery *)raycastQueryFromPoint:(CGPoint)point allowingTarget:(ARRaycastTarget)target alignment:(ARRaycastTargetAlignment)alignment API_AVAILABLE(ios(13.0));

/**
 Returns a display transform for the provided viewport size and orientation.
 
 @discussion The display transform can be used to convert normalized points in the image-space coordinate system
 of the captured image to normalized points in the view’s coordinate space. The transform provides the correct rotation
 and aspect-fill for presenting the captured image in the given orientation and size.
 @param orientation The orientation of the viewport.
 @param viewportSize The size of the viewport.
 */
- (CGAffineTransform)displayTransformForOrientation:(UIInterfaceOrientation)orientation viewportSize:(CGSize)viewportSize;


/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARSession.h
//
//  ARSession.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ARKit/ARConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class ARAnchor;
@class ARCamera;
@class ARFrame;
@class ARCollaborationData;
@class ARWorldMap;
@class ARRay;
@class ARRaycastQuery;
@class ARRaycastResult;
@class ARTrackedRaycast;

@protocol ARSessionDelegate;

/**
 Set of options for running the session.
 @discussion These options alter the behavior of calling run on a session.
 Providing no options will result in the default behavior of resuming tracking
 from the last known position and keeping all existing anchors.
 */
API_AVAILABLE(ios(11.0))
typedef NS_OPTIONS(NSUInteger, ARSessionRunOptions) {
    /** The session will reset tracking. */
    ARSessionRunOptionResetTracking           = (1 << 0),
    
    /** The session will remove existing anchors. */
    ARSessionRunOptionRemoveExistingAnchors   = (1 << 1)
} NS_SWIFT_NAME(ARSession.RunOptions);

/**
 The ARSession class configures and runs different Augmented Reality techniques on a device.
 */
API_AVAILABLE(ios(11.0))
@interface ARSession : NSObject

/**
 Unique identifier of the running session.
 
 @discussion The identifier may change after calling runWithConfiguration.
 */
@property (atomic, strong, readonly) NSUUID *identifier API_AVAILABLE(ios(13.0));

/**
 A delegate for receiving ARSession updates.
 */
@property (nonatomic, weak, nullable) id <ARSessionDelegate> delegate;

/**
 The dispatch queue on which the delegate calls are performed.
 @discussion If not provided or nil, delegate calls will be performed on the main queue.
 */
@property (nonatomic, strong, nullable) dispatch_queue_t delegateQueue;

/**
 The current frame of the session.
 */
@property (nonatomic, copy, nullable, readonly) ARFrame *currentFrame;

/**
 The configuration currently being used by the session.
 */
@property (nonatomic, copy, nullable, readonly) ARConfiguration *configuration;


/**
 Runs the session with the provided configuration.
 @discussion Calling run on a session that has already started will
 transition immediately to using the new configuration.
 @param configuration The configuration to use.
 */

- (void)runWithConfiguration:(ARConfiguration *)configuration NS_SWIFT_UNAVAILABLE("Use run(_:options:) instead");


/**
 Runs the session with the provided configuration and options.
 @discussion Calling run on a session that has already started will
 transition immediately to using the new configuration. Options
 can be used to alter the default behavior when transitioning configurations.
 @param configuration The configuration to use.
 @param options The run options to use.
 */

- (void)runWithConfiguration:(ARConfiguration *)configuration options:(ARSessionRunOptions)options NS_SWIFT_NAME(run(_:options:));

/**
 Pauses the session.
 @discussion Once paused, no more updates will be received from the
 session until run is called again.
 */
- (void)pause;

/**
 Adds an anchor to the session.
 @discussion The anchor will be added in the next frame update.
 @param anchor The anchor to add.
 */
- (void)addAnchor:(ARAnchor *)anchor NS_SWIFT_NAME(add(anchor:));

/**
 Removes an anchor from the session.
 @discussion The anchor will be removed from subsequent frame updates.
 @param anchor The anchor to remove.
 */
- (void)removeAnchor:(ARAnchor *)anchor NS_SWIFT_NAME(remove(anchor:));

/**
 Sets the world origin of the session to be at the position and orientation
 specified by the provided transform.
 @param relativeTransform The rotation, translation and scale from the current world origin
 to the desired world origin.
 */
- (void)setWorldOrigin:(simd_float4x4)relativeTransform NS_SWIFT_NAME(setWorldOrigin(relativeTransform:)) API_AVAILABLE(ios(11.3));

/**
 Copies the current state of the world being tracked by the session.
 @discussion A world map is only provided when running an ARWorldTrackingConfiguration.
 @param completionHandler The completion handler to call when the get has completed. This handler is executed
 on the session's delegate queue. The completion handler takes the following parameters:
 worldMap - The current world map or nil if unavailable.
 error - An error that indicates why the world map is unavailable, or nil if a world map was provided.
 */
- (void)getCurrentWorldMapWithCompletionHandler:(void (^)(ARWorldMap * _Nullable worldMap, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(12.0));

/**
 Creates a new reference object from scanned features within the provided bounds.
 
 @discussion Reference objects can be stored and used to track 3D objects from previously scanned data.
 Creation requires that an ARObjectScanningConfiguration is used so that sufficient features are scanned.
 @param transform The transformation matrix that defines the rotation and translation of the bounds in
 world coordinates. This will be used as the reference object's transform, defining its coordinate space.
 @param center The center of the object's bounds in the transform's coordinate space. A zero vector will
 define the object's origin centered within its extent.
 @param extent The extent of the object's bounds in the transform's coordinate space. This defines the bounds'
 size in each dimension.
 @param completionHandler The completion handler to call when the creation has completed. This handler is executed
 on the session's delegate queue. The completion handler takes the following parameters:
 referenceObject - The reference object created or nil if unavailable.
 error - An error that indicates why creation failed, or nil if a reference object was provided.
 */
- (void)createReferenceObjectWithTransform:(simd_float4x4)transform
                                     center:(simd_float3)center
                                     extent:(simd_float3)extent
                          completionHandler:(void (^)(ARReferenceObject * _Nullable referenceObject, NSError * _Nullable error))completionHandler
NS_SWIFT_NAME(createReferenceObject(transform:center:extent:completionHandler:)) API_AVAILABLE(ios(12.0));

#pragma mark - Raycasting

/**
 Perform a raycast.
 @param query Raycast query used for raycasting.
 @return List of raycast results, sorted from nearest to farthest (in distance from the camera). The results could be empty if raycast fails.
 */
- (NSArray<ARRaycastResult *> *)raycast:(ARRaycastQuery *)query API_AVAILABLE(ios(13.0));

/**
 Perform a tracked raycast.
 @discussion The session performs continuous raycasting and calls the update handler with the updated results.
 The ARTrackedRaycast object returned can be used to update the raycast with a new raycast query or stop raycasting.
 @param query Raycast query used for raycasting.
 @param updateHandler update handler where updated list of results, sorted from nearest to farthest (in distance from
        the camera) are delivered. updateHandler will be called on session's delegate queue.
 @return Tracked raycast object used to update or stop raycasting. This could be nil if the raycast fails or if the
         configuration is not `ARWorldTrackingConfiguration` or its subclasses.
 */
- (nullable ARTrackedRaycast *)trackedRaycast:(ARRaycastQuery *)query updateHandler:(void (^)(NSArray<ARRaycastResult *> *))updateHandler API_AVAILABLE(ios(13.0));

#pragma mark - Collaboration

/**
 Update session with collaboration data.
 
 @discussion Use this to update the session with collaboration data received from other participants.
 
 @param collaborationData Collaboration data for updating the session.
 @see ARCollaborationData
 */
- (void)updateWithCollaborationData:(ARCollaborationData *)collaborationData API_AVAILABLE(ios(13.0));

@end

#pragma mark - ARSessionObserver


API_AVAILABLE(ios(11.0))
@protocol ARSessionObserver <NSObject>

@optional

/**
 This is called when a session fails.
 
 @discussion On failure the session will be paused.
 @param session The session that failed.
 @param error The error being reported (see ARError.h).
 */
- (void)session:(ARSession *)session didFailWithError:(NSError *)error;

/**
 This is called when the camera’s tracking state has changed.
 
 @param session The session being run.
 @param camera The camera that changed tracking states.
 */
- (void)session:(ARSession *)session cameraDidChangeTrackingState:(ARCamera *)camera;

/**
 This is called when a session is interrupted.
 
 @discussion A session will be interrupted and no longer able to track when
 it fails to receive required sensor data. This happens when video capture is interrupted,
 for example when the application is sent to the background or when there are
 multiple foreground applications (see AVCaptureSessionInterruptionReason).
 No additional frame updates will be delivered until the interruption has ended.
 @param session The session that was interrupted.
 */
- (void)sessionWasInterrupted:(ARSession *)session;

/**
 This is called when a session interruption has ended.
 
 @discussion A session will continue running from the last known state once
 the interruption has ended. If the device has moved, anchors will be misaligned.
 To avoid this, some applications may want to reset tracking (see ARSessionRunOptions)
 or attempt to relocalize (see `-[ARSessionObserver sessionShouldAttemptRelocalization:]`).
 @param session The session that was interrupted.
 */
- (void)sessionInterruptionEnded:(ARSession *)session;

/**
 This is called after a session resumes from a pause or interruption to determine
 whether or not the session should attempt to relocalize.
 
 @discussion To avoid misaligned anchors, apps may wish to attempt a relocalization after
 a session pause or interruption. If YES is returned: the session will begin relocalizing
 and tracking state will switch to limited with reason relocalizing. If successful, the
 session's tracking state will return to normal. Because relocalization depends on
 the user's location, it can run indefinitely. Apps that wish to give up on relocalization
 may call run with `ARSessionRunOptionResetTracking` at any time.
 @param session The session to relocalize.
 @return Return YES to begin relocalizing.
 */
- (BOOL)sessionShouldAttemptRelocalization:(ARSession *)session API_AVAILABLE(ios(11.3));

/**
 This is called when the session outputs a new audio sample buffer.
 
 @param session The session being run.
 @param audioSampleBuffer The captured audio sample buffer.
 */
- (void)session:(ARSession *)session didOutputAudioSampleBuffer:(CMSampleBufferRef)audioSampleBuffer;

/**
 This is called when the session generated new collaboration data.
 
 @discussion This data should be sent to all participants.
 
 @param session The session that produced world tracking collaboration data.
 @param data Collaboration data to be sent to participants.
 @see ARCollaborationData
 */
- (void)session:(ARSession *)session didOutputCollaborationData:(ARCollaborationData *)data API_AVAILABLE(ios(13.0));

@end

#pragma mark - ARSessionDelegate


API_AVAILABLE(ios(11.0))
@protocol ARSessionDelegate <ARSessionObserver>

@optional

/**
 This is called when a new frame has been updated.
 
 @param session The session being run.
 @param frame The frame that has been updated.
 */
- (void)session:(ARSession *)session didUpdateFrame:(ARFrame *)frame;

/**
 This is called when new anchors are added to the session.
 
 @param session The session being run.
 @param anchors An array of added anchors.
 */
- (void)session:(ARSession *)session didAddAnchors:(NSArray<ARAnchor*>*)anchors;

/**
 This is called when anchors are updated.
 
 @param session The session being run.
 @param anchors An array of updated anchors.
 */
- (void)session:(ARSession *)session didUpdateAnchors:(NSArray<ARAnchor*>*)anchors;

/**
 This is called when anchors are removed from the session.
 
 @param session The session being run.
 @param anchors An array of removed anchors.
 */
- (void)session:(ARSession *)session didRemoveAnchors:(NSArray<ARAnchor*>*)anchors;

@end

/**
 A data source for an ARSession
 */
@protocol ARSessionProviding <NSObject>

@property (readonly) ARSession *session;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARObjectAnchor.h
//
//  ARObjectAnchor.h
//  ARKit
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

NS_ASSUME_NONNULL_BEGIN

@class ARReferenceObject;

/**
 An anchor representing an object in the world.
 */
API_AVAILABLE(ios(12.0))
@interface ARObjectAnchor : ARAnchor

/**
 Reference to the detected object.
 */
@property (nonatomic, strong, readonly) ARReferenceObject *referenceObject;

/** Unavailable */
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/AREnvironmentProbeAnchor.h
//
//  AREnvironmentProbeAnchor.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

@protocol MTLTexture;

NS_ASSUME_NONNULL_BEGIN

/**
 An object representing an environment probe in the world.
 @discussion Environment probes are used to light virtual geometry by producing environment
 textures from the probe's location in the world.
 */
API_AVAILABLE(ios(12.0))
@interface AREnvironmentProbeAnchor : ARAnchor

/**
 The environment texture of the probe.
 @discussion The texture is provided as a cube using MTLTextureTypeCube.
 */
@property (nonatomic, strong, nullable, readonly) id<MTLTexture> environmentTexture;

/**
 The extent of the probe in the anchor's coordinate space.
 @discussion This is the size of the box that is assumed when projecting the environment texture for parallax correction.
 The extent defaults to infinity for probes that do not need parallax correction.
 */
@property (nonatomic, readonly) simd_float3 extent;

/**
 Initializes a new environment probe anchor with the provided transform and extent.
 @param transform The transformation matrix that defines the anchor’s rotation, translation and scale in world coordinates.
 @param extent The extent of the probe in the anchor's coordinate space.
 */
- (instancetype)initWithTransform:(simd_float4x4)transform extent:(simd_float3)extent;

/**
 Initializes a new environment probe anchor with the provided name, transform, and extent.
 @param name A name to associate with the anchor.
 @param transform The transformation matrix that defines the anchor’s rotation, translation and scale in world coordinates.
 @param extent The extent of the probe in the anchor's coordinate space.
 */
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform extent:(simd_float3)extent;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARWorldMap.h
//
//  ARWorldMap.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

@class ARAnchor;
@class ARPointCloud;

NS_ASSUME_NONNULL_BEGIN

/**
 Object representing the mapping of a physical 3D space.
 @discussion ARWorldMap supports archiving and unarchiving across devices
 and versions with NSDecodingFailurePolicySetErrorAndReturn, providing an error
 if the map format is not supported.
 */
API_AVAILABLE(ios(12.0))
@interface ARWorldMap : NSObject <NSCopying, NSSecureCoding>

/**
 The position of the center of the mapped world in meters.
 */
@property (nonatomic, readonly) simd_float3 center;

/**
 The extent of the mapped world in meters.
 */
@property (nonatomic, readonly) simd_float3 extent;

/**
 A list of anchors in the map.
 */
@property (nonatomic, copy) NSArray<ARAnchor *> *anchors;

/**
 The feature points in the map.
 */
@property (nonatomic, strong, readonly) ARPointCloud *rawFeaturePoints;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARCoachingOverlayView.h
//
//  ARCoachingOverlayView.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class ARSession;

@protocol ARCoachingOverlayViewDelegate;
@protocol ARSessionProviding;

/**
 A value describing the context required for successful coaching
 */
API_AVAILABLE(ios(13.0))
typedef NS_ENUM(NSInteger, ARCoachingGoal) {
    /** Session requires normal tracking */
    ARCoachingGoalTracking,
    /** Session requires a horizontal plane */
    ARCoachingGoalHorizontalPlane,
    /** Session requires a vertical plane */
    ARCoachingGoalVerticalPlane,
    /** Session requires one plane of any type */
    ARCoachingGoalAnyPlane,
} NS_SWIFT_NAME(ARCoachingOverlayView.Goal);

/**
 A view that guides users through session initialization
 
 @discussion The view will use context aware messaging and animations to instruct the user on gathering required info for the AR session.
 */
API_AVAILABLE(ios(13.0))
@interface ARCoachingOverlayView : UIView

/**
 Specifies the delegate used for callbacks
 */
@property (nonatomic, weak, nullable) IBOutlet id<ARCoachingOverlayViewDelegate> delegate;

/**
 A provider of a session to use

 @discussion This property can be used to set the `session` when loading from a storyboard. Setting this property at runtime will also
 set the `session` property.
 */
@property (nonatomic, weak, nullable) IBOutlet id<ARSessionProviding> sessionProvider;

/**
 The session that the view uses to update coaching
 */
@property (nonatomic, strong, nullable) ARSession *session;

/**
 The coaching type used to resolve what messaging to display to the user while activated
 Defaults to `ARCoachingGoalTracking`
 */
@property (nonatomic, assign) ARCoachingGoal goal;

/**
 Whether or not the view should activate/deactivate automatically, depending on the current state of the session
 Defaults to `YES`
 
 @discussion When set to automatically activate, the view will transition to active when the session loses normal tracking for a set amount
 of time.
 When tracking resumes and other requirements (based on `goal`) are met, the view will deactivate.

 */
@property (nonatomic, assign) BOOL activatesAutomatically;

/**
 Whether or not the view is currently active.

 @discussion Set this to transition to the activated or deactivated state. On activation the view will check the current session, and if
 relocalization is needed it will present a modified UI with relocalization coaching and a reset button.

 @see -[ARCoachingOverlayView setActive:animated:]
 */
@property (nonatomic, assign, getter=isActive) BOOL active;

/**
 Transition the view to either an activated or deactivated state
 
 @discussion On activation the view will check the current session, and if relocalization is needed it will present a modified UI with
 relocalization coaching and a reset button.
 
 On deactivation the view will become hidden
 @param active Whether the view should activate, or deactivate
 @param animated Whether the view animated to activated/deactivated states, or transitions instantly

 @see -[ARCoachingOverlayViewDelegate coachingOverlayViewDidTriggerReset:]
 */
- (void)setActive:(BOOL)active animated:(BOOL)animated;

@end

API_AVAILABLE(ios(13.0))
@protocol ARCoachingOverlayViewDelegate <NSObject>

@optional

/**
 This is called when the user taps the reset button in the relocalization state

 @discussion By default, when the relocalization reset button is tapped, the overlay will call run on the session using the current
 `configuration`, and the `ARSessionRunOptionResetTracking` and `ARSessionRunOptionRemoveExistingAnchors` options. The delegate may
 implement this method to override this behavior. The delegate is then responsible for resetting the session.
 
 @param coachingOverlayView The view currently active
 */
- (void)coachingOverlayViewDidRequestSessionReset:(ARCoachingOverlayView *)coachingOverlayView;

/**
 This is called when the view activate, either manually or automatically
 
 @discussion The Developer may hide their application UI in in this callback, and take other appropriate actions to allow
 `ARCoachingOverlayView` to take over the full screen.
 @param coachingOverlayView The view that will be activated
 */
- (void)coachingOverlayViewWillActivate:(ARCoachingOverlayView *)coachingOverlayView;

/**
 This is called when the view deactivates, either manually or automatically
 
 @param coachingOverlayView The view that was deactivated
 */
- (void)coachingOverlayViewDidDeactivate:(ARCoachingOverlayView *)coachingOverlayView;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARPlaneAnchor.h
//
//  ARPlaneAnchor.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

NS_ASSUME_NONNULL_BEGIN

@class ARPlaneGeometry;

/**
 A value describing the alignment of a plane anchor.
 */
API_AVAILABLE(ios(11.0))
typedef NS_ENUM(NSInteger, ARPlaneAnchorAlignment) {
    /** A plane that is horizontal with respect to gravity. */
    ARPlaneAnchorAlignmentHorizontal,
    
    /** A plane that is vertical with respect to gravity. */
    ARPlaneAnchorAlignmentVertical API_AVAILABLE(ios(11.3))
} NS_SWIFT_NAME(ARPlaneAnchor.Alignment);

/**
 A value describing the classification status of a plane anchor.
 */
API_AVAILABLE(ios(12.0))
typedef NS_ENUM(NSInteger, ARPlaneClassificationStatus) {
    /** Plane classification is currently unavailable. */
    ARPlaneClassificationStatusNotAvailable = 0,
    /** ARKit has not yet determined the classification of this plane. */
    ARPlaneClassificationStatusUndetermined,
    /** ARKit is confident the plane is not any of the known classes. */
    ARPlaneClassificationStatusUnknown,
    /** ARKit has a classification for the plane it is confident in. */
    ARPlaneClassificationStatusKnown
} NS_REFINED_FOR_SWIFT;

/**
 A value describing the classification of a plane anchor.
 */
API_AVAILABLE(ios(12.0))
typedef NS_ENUM(NSInteger, ARPlaneClassification) {
    /** The classification is not any of the known classes. */
    ARPlaneClassificationNone = 0,
    ARPlaneClassificationWall,
    ARPlaneClassificationFloor,
    ARPlaneClassificationCeiling,
    ARPlaneClassificationTable,
    ARPlaneClassificationSeat,
    ARPlaneClassificationWindow,
    ARPlaneClassificationDoor
} NS_REFINED_FOR_SWIFT;

/**
 An anchor representing a planar surface in the world.
 @discussion Planes are defined in the X and Z direction, where Y is the surface’s normal.
 */
API_AVAILABLE(ios(11.0))
@interface ARPlaneAnchor : ARAnchor

/**
 Determines whether plane classification is supported on this device.
 */
@property (class, nonatomic, readonly, getter=isClassificationSupported) BOOL classificationSupported API_AVAILABLE(ios(12.0));

/**
 The alignment of the plane.
 */
@property (nonatomic, readonly) ARPlaneAnchorAlignment alignment;

/**
 The center of the plane in the anchor’s coordinate space.
 */
@property (nonatomic, readonly) simd_float3 center;

/**
 The extent of the plane in the anchor’s coordinate space.
 */
@property (nonatomic, readonly) simd_float3 extent;

/**
 Geometry of the plane in the anchor's coordinate space.
 */
@property (nonatomic, strong, readonly) ARPlaneGeometry *geometry API_AVAILABLE(ios(11.3));

/**
 Classification status of the plane.
 */
@property (nonatomic, assign, readonly) ARPlaneClassificationStatus classificationStatus API_AVAILABLE(ios(12.0)) NS_REFINED_FOR_SWIFT;

/**
 Classification of the plane.
 */
@property (nonatomic, assign, readonly) ARPlaneClassification classification API_AVAILABLE(ios(12.0)) NS_REFINED_FOR_SWIFT;

/** Unavailable */
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARSCNView.h
//
//  ARSCNView.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKit.h>
#import <ARKit/ARSession.h>
#import <ARKit/ARHitTestResult.h>
#import <ARKit/ARTrackedRaycast.h>

@protocol ARSCNViewDelegate;

NS_ASSUME_NONNULL_BEGIN

/**
 A view that integrates ARSession rendering into SceneKit.
 
 @discussion The view draws the camera background, provides and updates a camera,
 manages nodes for anchors, and updates lighting.
 */
API_AVAILABLE(ios(11.0))
@interface ARSCNView : SCNView<ARSessionProviding>

/**
 Specifies the renderer delegate.
 */
@property (nonatomic, weak, nullable) id<ARSCNViewDelegate> delegate;

/**
 The session that the view uses to update the scene.
 */
@property (nonatomic, strong) ARSession *session;

/**
 Specifies the scene of the view.
 */
@property (nonatomic, strong) SCNScene *scene;

/**
 Determines whether the view will update the scene’s lighting.
 
 @discussion When set, the view will automatically create and update lighting for 
 light estimates the session provides. Defaults to YES.
 */
@property (nonatomic, assign) BOOL automaticallyUpdatesLighting;

/**
 Determines whether view renders camera grain.
 
 @discussion When set, the view will automatically add camera grain to rendered
 content that matches the grainy noise of the camera stream. Enabled by default.
 */
@property (nonatomic, assign) BOOL rendersCameraGrain API_AVAILABLE(ios(13.0));

/**
 Determines whether view renders motion blur.
 
 @discussion When set, the view will automatically add motion blur to rendered
 content that matches the motion blur of the camera stream.
 Overwrites SCNCamera's motionBlurIntensity property. Disabled by default.
 */
@property (nonatomic, assign) BOOL rendersMotionBlur API_AVAILABLE(ios(13.0));

/**
 Searches the scene hierarchy for an anchor associated with the provided node.
 @param node A node in the view’s scene.
 */
- (nullable ARAnchor *)anchorForNode:(SCNNode *)node;

/**
 Returns the node that has been mapped to a specific anchor.
 @param anchor An anchor with an existing node mapping.
 */
- (nullable SCNNode *)nodeForAnchor:(ARAnchor *)anchor;

/**
 Searches the current frame for objects corresponding to a point in the view.
 
 @discussion A 2D point in the view’s coordinate space can refer to any point along a line segment
 in the 3D coordinate space. Hit-testing is the process of finding objects in the world located along this line segment.
 @param point A point in the view’s coordinate system.
 @param types The types of results to search for.
 @return An array of all hit-test results sorted from nearest to farthest.
 */
- (NSArray<ARHitTestResult *> *)hitTest:(CGPoint)point types:(ARHitTestResultType)types;

/**
 Unproject a 2D point from the view onto a plane in 3D world coordinates.
 
 @discussion A 2D point in the view’s coordinate space can refer to any point along a line segment
 in the 3D coordinate space. Unprojecting gets the 3D position of the point along this line segment that intersects the provided plane.
 @param point A point in the view’s coordinate system.
 @param planeTransform The transform used to define the coordinate system of the plane.
 The coordinate system’s positive Y axis is assumed to be the normal of the plane.
 @return 3D position in world coordinates or a NAN values if unprojection is not possible.
 */
- (simd_float3)unprojectPoint:(CGPoint)point ontoPlaneWithTransform:(simd_float4x4)planeTransform API_AVAILABLE(ios(12.0)) NS_REFINED_FOR_SWIFT;

/**
 Creates a raycast query originating from the point on view, aligned along the center of the field of view of the camera.
 @discussion A 2D point in the view's coordinate space and the frame camera's field of view is used to create a ray in the 3D cooridnate space originating at the point.
 @param point A point in the view’s coordinate system.
 @param target Type of target where the ray should terminate.
 @param alignment Alignment of the target.
 */
- (nullable ARRaycastQuery *)raycastQueryFromPoint:(CGPoint)point allowingTarget:(ARRaycastTarget)target alignment:(ARRaycastTargetAlignment)alignment API_AVAILABLE(ios(13.0));

@end


#pragma mark - ARSCNViewDelegate


API_AVAILABLE(ios(11.0))
@protocol ARSCNViewDelegate <SCNSceneRendererDelegate, ARSessionObserver>
@optional

/**
 Implement this to provide a custom node for the given anchor.
 
 @discussion This node will automatically be added to the scene graph.
 If this method is not implemented, a node will be automatically created.
 If nil is returned the anchor will be ignored.
 @param renderer The renderer that will render the scene.
 @param anchor The added anchor.
 @return Node that will be mapped to the anchor or nil.
 */
- (nullable SCNNode *)renderer:(id <SCNSceneRenderer>)renderer nodeForAnchor:(ARAnchor *)anchor;

/**
 Called when a new node has been mapped to the given anchor.
 
 @param renderer The renderer that will render the scene.
 @param node The node that maps to the anchor.
 @param anchor The added anchor.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didAddNode:(SCNNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a node will be updated with data from the given anchor.
 
 @param renderer The renderer that will render the scene.
 @param node The node that will be updated.
 @param anchor The anchor that was updated.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer willUpdateNode:(SCNNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a node has been updated with data from the given anchor.
 
 @param renderer The renderer that will render the scene.
 @param node The node that was updated.
 @param anchor The anchor that was updated.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didUpdateNode:(SCNNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a mapped node has been removed from the scene graph for the given anchor.
 
 @param renderer The renderer that will render the scene.
 @param node The node that was removed.
 @param anchor The anchor that was removed.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didRemoveNode:(SCNNode *)node forAnchor:(ARAnchor *)anchor;

@end


/**
 Extended debug options for an ARSCNView
 */
typedef SCNDebugOptions ARSCNDebugOptions API_AVAILABLE(ios(11.0));

/** Show the world origin in the scene. */
API_AVAILABLE(ios(11.0))
FOUNDATION_EXTERN const SCNDebugOptions ARSCNDebugOptionShowWorldOrigin NS_SWIFT_NAME(ARSCNDebugOptions.showWorldOrigin);

/** Show detected 3D feature points in the world. */
API_AVAILABLE(ios(11.0))
FOUNDATION_EXTERN const SCNDebugOptions ARSCNDebugOptionShowFeaturePoints NS_SWIFT_NAME(ARSCNDebugOptions.showFeaturePoints);

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARPointCloud.h
//
//  ARPointCloud.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0))
@interface ARPointCloud : NSObject <NSSecureCoding>

/**
 The number of points in the point cloud.
 */
@property (nonatomic, readonly) NSUInteger count NS_REFINED_FOR_SWIFT;

/**
 The 3D points comprising the point cloud.
 */
@property (nonatomic, readonly) const simd_float3 *points NS_REFINED_FOR_SWIFT;

/**
 The 3D point identifiers comprising the point cloud.
 */
@property (nonatomic, readonly) const uint64_t *identifiers NS_REFINED_FOR_SWIFT;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARConfiguration.h
//
//  ARConfiguration.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ARReferenceImage;
@class ARReferenceObject;
@class ARVideoFormat;
@class ARWorldMap;

/**
Option set indicating semantic understanding types of the image frame.
*/
API_AVAILABLE(ios(13.0))
typedef NS_OPTIONS(NSUInteger, ARFrameSemantics) {
    /** No semantic operation is run. */
    ARFrameSemanticNone                              = 0,
    
    /**
    Person segmentation.
    @discussion A pixel in the image frame that gets classified as person will have an intensity value equal to 'ARSegmentationClassPerson'.
    @see -[ARFrame segmentationBuffer]
    @see ARSegmentationClass
    */
    ARFrameSemanticPersonSegmentation                = (1 << 0),
    
    /**
     Person segmentation with depth.
     @discussion A pixel in the image frame that gets classified as person will have an intensity value equal to 'ARSegmentationClassPerson'.
     Additionally, every pixel in the image frame that gets classified as person will also have a depth value.
     @see -[ARFrame estimatedDepthData]
     @see -[ARFrame segmentationBuffer]
     */
    ARFrameSemanticPersonSegmentationWithDepth       = (1 << 1) | (1 << 0),
    
    /**
     Body detection.

     @discussion Once activated an ARFrame will contain information about a detected body.
     @see -[ARFrame detectedBody]
     @see ARBody2D
     */
    ARFrameSemanticBodyDetection                     = (1 << 2)
    
} NS_SWIFT_NAME(ARConfiguration.FrameSemantics);

/**
 Enum constants for indicating the world alignment.
 */
API_AVAILABLE(ios(11.0))
typedef NS_ENUM(NSInteger, ARWorldAlignment) {
    /** Aligns the world with gravity that is defined by vector (0, -1, 0). */
    ARWorldAlignmentGravity,
    
    /** Aligns the world with gravity that is defined by the vector (0, -1, 0)
     and heading (w.r.t. True North) that is given by the vector (0, 0, -1). */
    ARWorldAlignmentGravityAndHeading,
    
    /** Aligns the world with the camera’s orientation. */
    ARWorldAlignmentCamera
} NS_SWIFT_NAME(ARConfiguration.WorldAlignment);


/**
 Enum constants for indicating the mode of environment texturing to run.
 */
API_AVAILABLE(ios(12.0))
typedef NS_ENUM(NSInteger, AREnvironmentTexturing) {
    /** No texture information is gathered. */
    AREnvironmentTexturingNone,
    
    /** Texture information is gathered for the environment.
     Environment textures will be generated for AREnvironmentProbes added to the session. */
    AREnvironmentTexturingManual,
    
    /** Texture information is gathered for the environment and probes automatically placed in the scene. */
    AREnvironmentTexturingAutomatic
} NS_SWIFT_NAME(ARWorldTrackingConfiguration.EnvironmentTexturing);


/**
 Option set indicating the type of planes to detect.
 */
API_AVAILABLE(ios(11.0))
typedef NS_OPTIONS(NSUInteger, ARPlaneDetection) {
    /** No plane detection is run. */
    ARPlaneDetectionNone                              = 0,
    
    /** Plane detection determines horizontal planes in the scene. */
    ARPlaneDetectionHorizontal                        = (1 << 0),
    
    /** Plane detection determines vertical planes in the scene. */
    ARPlaneDetectionVertical API_AVAILABLE(ios(11.3)) = (1 << 1)
} NS_SWIFT_NAME(ARWorldTrackingConfiguration.PlaneDetection);


/**
 An object to describe and configure the Augmented Reality techniques to be used in an ARSession.
 */
API_AVAILABLE(ios(11.0))
@interface ARConfiguration : NSObject <NSCopying>

/**
 Determines whether this device supports the ARConfiguration.
 */
@property (class, nonatomic, readonly) BOOL isSupported;

/**
 A list of supported video formats for this configuration and device.
 @discussion The first element in the list is the default format for session output.
 */
@property (class, nonatomic, readonly) NSArray<ARVideoFormat *> *supportedVideoFormats API_AVAILABLE(ios(11.3));

/**
 Video format of the session output.
 */
@property (nonatomic, strong) ARVideoFormat *videoFormat API_AVAILABLE(ios(11.3));

/**
 Determines how the coordinate system should be aligned with the world.
 @discussion The default is ARWorldAlignmentGravity.
 */
@property (nonatomic, assign) ARWorldAlignment worldAlignment;

/**
 Enable or disable light estimation.
 @discussion Enabled by default.
 */
@property (nonatomic, assign, getter=isLightEstimationEnabled) BOOL lightEstimationEnabled;

/**
 Determines whether to capture and provide audio data.
 @discussion Disabled by default.
 */
@property (nonatomic, assign) BOOL providesAudioData;

/**
The type of semantic understanding to provide with each frame.

@discussion  Use `+[ARConfiguration supportsFrameSemantics:]` to check if an option is supported before setting. An exception is thrown if the
option is not supported. Defaults to ARFrameSemanticNone.
@see ARFrameSemantics
@see +[ARConfiguration supportsFrameSemantics:]
*/
@property (nonatomic, assign) ARFrameSemantics frameSemantics API_AVAILABLE(ios(13.0));

/**
 Determines whether the type of frame semantics is supported by the device and ARConfiguration class.

 @discussion Semantic frame understanding is not supported on all devices.
 @see ARFrameSemantics
*/
+ (BOOL)supportsFrameSemantics:(ARFrameSemantics)frameSemantics API_AVAILABLE(ios(13.0));


/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


/**
 A configuration for running world tracking.
 
 @discussion World tracking provides 6 degrees of freedom tracking of the device.
 By finding feature points in the scene, world tracking enables performing hit-tests against the frame.
 Tracking can no longer be resumed once the session is paused.
 */
API_AVAILABLE(ios(11.0))
@interface ARWorldTrackingConfiguration : ARConfiguration

/**
 Enable or disable continuous auto focus.
 @discussion Enabled by default.
 */
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled API_AVAILABLE(ios(11.3));

/**
 The mode of environment texturing to run.
 @discussion If set, texture information will be accumulated and updated. Adding an AREnvironmentProbeAnchor to the session
 will get the current environment texture available from that probe's perspective which can be used for lighting
 virtual objects in the scene. Defaults to AREnvironmentTexturingNone.
 */
@property (nonatomic, assign) AREnvironmentTexturing environmentTexturing API_AVAILABLE(ios(12.0));

/**
 Determines whether environment textures will be provided with high dynamic range. Enabled by default.
 */
@property (nonatomic, assign) BOOL wantsHDREnvironmentTextures API_AVAILABLE(ios(13.0));

/**
 Type of planes to detect in the scene.
 @discussion If set, new planes will continue to be detected and updated over time. Detected planes will be added to the session as
 ARPlaneAnchor objects. In the event that two planes are merged, the newer plane will be removed. Defaults to ARPlaneDetectionNone.
 */
@property (nonatomic, assign) ARPlaneDetection planeDetection;

/**
 The initial map of the physical space that world tracking will localize to and track.
 @discussion If set, the session will attempt to localize to the provided map with
 a limited tracking state until localization is successful or run is called again
 with a different (or no) initial map specified. Once localized, the map will be extended
 and can again be saved using the `getCurrentWorldMap` method on the session.
 */
@property (nonatomic, strong, nullable) ARWorldMap *initialWorldMap API_AVAILABLE(ios(12.0));

/**
 Images to detect in the scene.
 @discussion If set the session will attempt to detect the specified images. When an image is detected an ARImageAnchor will be added to the session.
 */
@property (nonatomic, copy, null_resettable) NSSet<ARReferenceImage *> *detectionImages API_AVAILABLE(ios(11.3));

/**
 Enables the estimation of a scale factor which may be used to correct the physical size of an image.
 @discussion If set to true ARKit will attempt to use the computed camera positions in order to compute the scale by which the given physical size
 differs from the estimated one. The information about the estimated scale can be found as the property estimatedScaleFactor on the ARImageAnchor.
 @note When set to true the transform of a returned ARImageAnchor will use the estimated scale factor to correct the translation. Default value is NO.
  */
@property (nonatomic, assign) BOOL automaticImageScaleEstimationEnabled API_AVAILABLE(ios(13.0));

/**
 Maximum number of images to track simultaneously.
 @discussion Setting the maximum number of tracked images will limit the number of images that can be tracked in a given frame.
 If more than the maximum is visible, only the images already being tracked will continue to track until tracking is lost or another image is removed.
 Images will continue to be detected regardless of images tracked. Default value is zero.
 */
@property (nonatomic, assign) NSInteger maximumNumberOfTrackedImages API_AVAILABLE(ios(12.0));

/**
 Objects to detect in the scene.
 @discussion If set the session will attempt to detect the specified objects. When an object is detected an ARObjectAnchor will be added to the session.
 */
@property (nonatomic, copy) NSSet<ARReferenceObject *> *detectionObjects API_AVAILABLE(ios(12.0));

/**
 Enable/disable a collaborative session. Disabled by default.
 
 @discussion When enabled, ARSession will output collaboration data for other participants using its delegate didOutputCollaborationData.
 It is the responsibility of the caller to send the data to each participant. When data is received by a participant, it
 should be passed to the ARSession by calling updateWithCollaborationData.
 */
@property (nonatomic, assign, getter=isCollaborationEnabled) BOOL collaborationEnabled API_AVAILABLE(ios(13.0));

/**
 Indicates whether user face tracking using the front facing camera can be enabled on this device.
 */
@property (class, nonatomic, readonly) BOOL supportsUserFaceTracking API_AVAILABLE(ios(13.0));

/**
 Enable or disable running Face Tracking using the front facing camera. Disabled by default.
 When enabled, ARSession detects faces (if visible in the front-facing camera image) and adds to its list of anchors,
 an ARFaceAnchor object representing each face.
 
 @discussion The transform of the ARFaceAnchor objects will be in the world coordinate space.
 @see ARFaceAnchor
 */
@property (nonatomic, assign, getter=userFaceTrackingEnabled) BOOL userFaceTrackingEnabled API_AVAILABLE(ios(13.0));

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end

/**
 A configuration for running orientation tracking.
 
 @discussion Orientation tracking provides 3 degrees of freedom tracking of the device.
 */
API_AVAILABLE(ios(11.0))
@interface AROrientationTrackingConfiguration : ARConfiguration

/**
 Enable or disable continuous auto focus.
 @discussion Enabled by default.
 */
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled API_AVAILABLE(ios(11.3));

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end


/**
 A configuration for running face tracking.
 
 @discussion Face tracking uses the front facing camera to track the face in 3D providing details on the topology and expression of the face.
 A detected face will be added to the session as an ARFaceAnchor object which contains information about head pose, mesh, eye pose, and blend shape
 coefficients. If light estimation is enabled the detected face will be treated as a light probe and used to estimate the direction of incoming light.
 */
API_AVAILABLE(ios(11.0))
@interface ARFaceTrackingConfiguration : ARConfiguration

/**
 Maximum number of faces which can be tracked simultaneously.
 */
@property (class, nonatomic, readonly) NSInteger supportedNumberOfTrackedFaces API_AVAILABLE(ios(13.0));

/**
 Maximum number of faces to track simultaneously.
 @discussion Setting the maximum number of tracked faces will limit the number of faces that can be tracked in a given frame.
 If more than the maximum is visible, only the faces already being tracked will continue to track until tracking is lost or another face is removed.
 Default value is one.
 */
@property (nonatomic, assign) NSInteger maximumNumberOfTrackedFaces API_AVAILABLE(ios(13.0));

/**
 Indicates whether world tracking can be enabled on this device.
 */
@property (class, nonatomic, readonly) BOOL supportsWorldTracking API_AVAILABLE(ios(13.0));

/**
 Enable or disable World Tracking. Disabled by default.
 
 @discussion When enabled, ARSession uses the back facing camera to track the device's orientation and position in the world. The camera transform and the ARFaceAnchor transform will be in the world coordinate space.
 */
@property (nonatomic, assign, getter=isWorldTrackingEnabled) BOOL worldTrackingEnabled API_AVAILABLE(ios(13.0));

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end


/**
 A configuration for running image tracking.
 
 @discussion Image tracking provides 6 degrees of freedom tracking of known images. Four images may be tracked simultaneously.
 */
API_AVAILABLE(ios(12.0))
@interface ARImageTrackingConfiguration : ARConfiguration

/**
 Enable or disable continuous auto focus.
 @discussion Enabled by default.
 */
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled;

/**
 Images to track in the scene.
 */
@property (nonatomic, copy) NSSet<ARReferenceImage *> *trackingImages;

/**
 Maximum number of images to track simultaneously.
 @discussion Setting the maximum number of tracked images will limit the number of images that can be tracked in a given frame.
 If more than the maximum is visible, only the images already being tracked will continue to track until tracking is lost or another image is removed.
 Default value is one.
 */
@property (nonatomic, assign) NSInteger maximumNumberOfTrackedImages;

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end


/**
 A configuration for scanning objects.
 
 @discussion The object scanning configuration runs world tracking, capturing additional detail in order to create reference objects.
 Running object scanning will consume additional power in order to provide more detailed features.
 The createReferenceObject method can be called on the session to capture a scan of an object in the world.
 */
API_AVAILABLE(ios(12.0))
@interface ARObjectScanningConfiguration : ARConfiguration

/**
 Enable or disable continuous auto focus.
 @discussion Enabled by default.
 */
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled;

/**
 Type of planes to detect in the scene.
 @discussion If set, new planes will continue to be detected and updated over time. Detected planes will be added to the session as
 ARPlaneAnchor objects. In the event that two planes are merged, the newer plane will be removed. Defaults to ARPlaneDetectionNone.
 */
@property (nonatomic, assign) ARPlaneDetection planeDetection;

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end


/**
 A configuration for running body tracking.
 
 @discussion Body tracking provides 6 degrees of freedom tracking of a detected body in the scene. By default, ARFrameSemanticBodyDetection will be
 enabled.
 @see ARBodyAnchor
 @see -[ARFrame detectedBody]
 */
API_AVAILABLE(ios(13.0))
@interface ARBodyTrackingConfiguration : ARConfiguration

/**
 Enable or disable continuous auto focus.
 @discussion Enabled by default.
 */
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled;

/**
 The initial map of the physical space that world tracking will localize to and track.
 @discussion If set, the session will attempt to localize to the provided map with
 a limited tracking state until localization is successful or run is called again
 with a different (or no) initial map specified. Once localized, the map will be extended
 and can again be saved using the `getCurrentWorldMap` method on the session.
 */
@property (nonatomic, strong, nullable) ARWorldMap *initialWorldMap;

/**
 The mode of environment texturing to run.
 @discussion If set, texture information will be accumulated and updated. Adding an AREnvironmentProbeAnchor to the session
 will get the current environment texture available from that probe's perspective which can be used for lighting
 virtual objects in the scene. Defaults to AREnvironmentTexturingNone.
 */
@property (nonatomic, assign) AREnvironmentTexturing environmentTexturing;

/**
 Determines whether environment textures will be provided with high dynamic range. Enabled by default.
 */
@property (nonatomic, assign) BOOL wantsHDREnvironmentTextures;

/**
 Type of planes to detect in the scene.
 @discussion If set, new planes will continue to be detected and updated over time. Detected planes will be added to the session as
 ARPlaneAnchor objects. In the event that two planes are merged, the newer plane will be removed. Defaults to ARPlaneDetectionNone.
 */
@property (nonatomic, assign) ARPlaneDetection planeDetection;

/**
Images to detect in the scene.
@discussion If set the session will attempt to detect the specified images. When an image is detected an ARImageAnchor will be added to the session.
*/
@property (nonatomic, copy) NSSet<ARReferenceImage *> *detectionImages;

/**
 Enables the estimation of a scale factor which may be used to correct the physical size of an image.
 @discussion If set to true ARKit will attempt to use the computed camera positions in order to compute the scale by which the given physical size
 differs from the estimated one. The information about the estimated scale can be found as the property estimatedScaleFactor on the ARImageAnchor.
 @note When set to true the transform of a returned ARImageAnchor will use the estimated scale factor to correct the translation. Default value is NO.
 */
@property (nonatomic, assign) BOOL automaticImageScaleEstimationEnabled;

/**
 Enables the estimation of a scale factor which may be used to correct the physical size of a skeleton in 3D.
 @discussion If set to true ARKit will attempt to use the computed camera positions in order to compute the scale by which the given physical size
 differs from the default one. The information about the estimated scale can be found as the property estimatedScaleFactor on the ARBodyAnchor.
 @note When set to true the transform of a returned ARBodyAnchor will use the estimated scale factor to correct the translation. Default value is YES.
 */
@property (nonatomic, assign) BOOL automaticSkeletonScaleEstimationEnabled;
/**
 Maximum number of images to track simultaneously.
 @discussion Setting the maximum number of tracked images will limit the number of images that can be tracked in a given frame.
 If more than the maximum is visible, only the images already being tracked will continue to track until tracking is lost or another image is removed.
 Images will continue to be detected regardless of images tracked. Default value is zero.
 */
@property (nonatomic, assign) NSInteger maximumNumberOfTrackedImages;

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end

/**
 A configuration for running positional tracking.
 
 @discussion Positional tracking provides 6 degrees of freedom tracking of the device by running the camera at lowest possible resolution and frame rate.
 */
API_AVAILABLE(ios(13.0))
@interface ARPositionalTrackingConfiguration : ARConfiguration

/**
 Type of planes to detect in the scene.
 @discussion If set, new planes will continue to be detected and updated over time. Detected planes will be added to the session as
 ARPlaneAnchor objects. In the event that two planes are merged, the newer plane will be removed. Defaults to ARPlaneDetectionNone.
 */
@property (nonatomic, assign) ARPlaneDetection planeDetection;

/**
 The initial map of the physical space that world tracking will localize to and track.
 @discussion If set, the session will attempt to localize to the provided map with
 a limited tracking state until localization is successful or run is called again
 with a different (or no) initial map specified. Once localized, the map will be extended
 and can again be saved using the `getCurrentWorldMap` method on the session.
 */
@property (nonatomic, strong, nullable) ARWorldMap *initialWorldMap;

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end


NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARError.h
//
//  ARError.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0))
FOUNDATION_EXTERN NSString *const ARErrorDomain;

API_AVAILABLE(ios(11.0))
typedef NS_ERROR_ENUM(ARErrorDomain, ARErrorCode) {
    /** Unsupported configuration. */
    ARErrorCodeUnsupportedConfiguration                               = 100,
    
    /** A sensor required to run the session is not available. */
    ARErrorCodeSensorUnavailable                                      = 101,
    
    /** A sensor failed to provide the required input. */
    ARErrorCodeSensorFailed                                           = 102,
    
    /** App does not have permission to use the camera. The user may change this in settings. */
    ARErrorCodeCameraUnauthorized                                     = 103,
    
    /** App does not have permission to use the microphone. The user may change this in settings. */
    ARErrorCodeMicrophoneUnauthorized                                 = 104,
    
    /** World tracking has encountered a fatal error. */
    ARErrorCodeWorldTrackingFailed                                    = 200,
    
    /** Invalid reference image */
    ARErrorCodeInvalidReferenceImage         API_AVAILABLE(ios(11.3)) = 300,

    /** Invalid reference object. */
    ARErrorCodeInvalidReferenceObject        API_AVAILABLE(ios(12.0)) = 301,
    
    /** Invalid world map. */
    ARErrorCodeInvalidWorldMap               API_AVAILABLE(ios(12.0)) = 302,
    
    /** Invalid configuration. */
    ARErrorCodeInvalidConfiguration          API_AVAILABLE(ios(12.0)) = 303,
    
    /** Collaboration data is not available. */
    ARErrorCodeCollaborationDataUnavailable  API_AVAILABLE(ios(13.0)) = 304,
    
    /** Insufficient features. */
    ARErrorCodeInsufficientFeatures          API_AVAILABLE(ios(12.0)) = 400,
    
    /** Object merge failed. */
    ARErrorCodeObjectMergeFailed             API_AVAILABLE(ios(12.0)) = 401,
    
    /** Unable to read or write to file. */
    ARErrorCodeFileIOFailed                  API_AVAILABLE(ios(12.0)) = 500,
};

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARAnchor.h
//
//  ARAnchor.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

@class ARAnchor;
/**
 An anchor object that can be copied from values of an existing anchor.
 */
API_AVAILABLE(ios(12.0))
@protocol ARAnchorCopying <NSCopying>

/**
 Initializes a new anchor object copying values from an existing anchor.
 @discussion This initializer will be called any time copy is called on anchor of this class.
 This method must be implemented for any ARAnchor subclasses that adds properties.
 @param anchor The anchor from which to copy values.
 */
- (instancetype)initWithAnchor:(ARAnchor *)anchor;

@end


/**
 Object representing a physical location and orientation in 3D space.
 */
API_AVAILABLE(ios(11.0))
@interface ARAnchor : NSObject <ARAnchorCopying, NSSecureCoding>

/**
 Unique identifier of the anchor.
 */
@property (nonatomic, readonly) NSUUID *identifier;

/**
 An optional name used to associate with the anchor.
 */
@property (nonatomic, nullable, readonly) NSString *name API_AVAILABLE(ios(12.0));

/**
 Identifier of the session that owns the anchor.
 
 @discussion The session identifier will be assigned to anchor when added to the session.
 */
@property (nonatomic, nullable, readonly) NSUUID *sessionIdentifier API_AVAILABLE(ios(13.0));

/**
 The transformation matrix that defines the anchor’s rotation, translation and scale in world coordinates.
 */
@property (nonatomic, readonly) simd_float4x4 transform;

/**
 Initializes a new anchor object.
 @param transform The transformation matrix that defines the anchor’s rotation, translation and scale in world coordinates.
 */
- (instancetype)initWithTransform:(simd_float4x4)transform;

/**
 Initializes a new anchor object with the provided identifier and name.
 @param name A name to associate with the anchor.
 @param transform The transformation matrix that defines the anchor’s rotation, translation and scale in world coordinates.
 */
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform API_AVAILABLE(ios(12.0));

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


/**
 A real world object or location in the scene that is being tracked.
 */
API_AVAILABLE(ios(11.0))
@protocol ARTrackable <NSObject>

/**
 Tracking state of the anchor
 @discussion The isTracked value is used to determine the anchor transform’s validity. When the object being tracked is no longer detected in the
 camera image, its anchor will return NO for isTracked.
 */
@property (nonatomic, readonly) BOOL isTracked;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARRaycastResult.h
//
//  ARRaycastResult.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>
#import "ARRaycastQuery.h"

@class ARAnchor;

NS_ASSUME_NONNULL_BEGIN

/**
 Result of a raycast on a single target.
 */
API_AVAILABLE(ios(13.0))
@interface ARRaycastResult : NSObject

/**
 The transformation matrix that defines the raycast result's rotation, translation and scale relative to the world.
 */
@property (nonatomic, readonly) simd_float4x4 worldTransform;

/**
 Type of the target where the ray terminated.
 */
@property (nonatomic, readonly, assign) ARRaycastTarget target;

/**
 Alignment of the target.
 */
@property (nonatomic, readonly, assign) ARRaycastTargetAlignment targetAlignment;

/**
 The anchor that the ray intersected.
 
 @discussion In case of an existing plane target, an anchor will always be provided. In case of an estimated plane target,
 an anchor may be provided if the ray hit an existing plane.
 */
@property (nonatomic, readonly, strong, nullable) ARAnchor *anchor;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARFaceGeometry.h
//
//  ARFaceGeometry.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNGeometry.h>
#import <ARKit/ARFaceAnchor.h>

@protocol MTLBuffer;
@protocol MTLDevice;
@class ARFaceAnchor;

NS_ASSUME_NONNULL_BEGIN

/**
 An object representing the geometry of a face.
 @discussion The face geometry will have a constant number of triangles
 and vertices, updating only the vertex positions from frame to frame.
 */
API_AVAILABLE(ios(11.0))
@interface ARFaceGeometry : NSObject<NSSecureCoding, NSCopying>

/**
The number of mesh vertices of the geometry.
 */
@property (nonatomic, readonly) NSUInteger vertexCount NS_REFINED_FOR_SWIFT;

/**
 The mesh vertices of the geometry.
 */
@property (nonatomic, readonly) const simd_float3 *vertices NS_REFINED_FOR_SWIFT;

/**
 The number of texture coordinates of the face geometry.
 */
@property (nonatomic, readonly) NSUInteger textureCoordinateCount NS_REFINED_FOR_SWIFT;

/**
 The texture coordinates of the geometry.
 */
@property (nonatomic, readonly) const simd_float2 *textureCoordinates NS_REFINED_FOR_SWIFT;

/**
 The number of triangles of the face geometry.
 */
@property (nonatomic, readonly) NSUInteger triangleCount;

/**
 The triangle indices of the geometry.
 */
@property (nonatomic, readonly) const int16_t *triangleIndices NS_REFINED_FOR_SWIFT;

/**
 Creates and returns a face geometry by applying a set of given blend shape coefficients.
 
 @discussion An empty dictionary can be provided to create a neutral face geometry.
 @param blendShapes A dictionary of blend shape coefficients.
 @return Face geometry after applying the blend shapes.
 */
- (nullable instancetype)initWithBlendShapes:(NSDictionary<ARBlendShapeLocation, NSNumber*> *)blendShapes;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


/**
 A SceneKit geometry representing a face.
 */
API_AVAILABLE(ios(11.0))
@interface ARSCNFaceGeometry : SCNGeometry

/**
 Creates a new face geometry using a Metal device.
 
 @param device A Metal device.
 @return A new face geometry.
 */
+ (nullable instancetype)faceGeometryWithDevice:(id<MTLDevice>)device;


/**
 Creates a new face geometry using a Metal device.
 
 @discussion By default the regions between the eye lids as well as the region
 between the lips are not covered by geometry. For using the face geometry as an
 occlusion geometry set \p fillMesh to YES. This will fill
 in additional geometry into the gaps between the eye lids as well as into the
 gap between the lips.
 @param fillMesh Whether to fill in additional geometry into the
 gaps between the eye lids as well as into the gap between the lips.
 
 @return A new face geometry.
 */
+ (nullable instancetype)faceGeometryWithDevice:(id<MTLDevice>)device
                              fillMesh:(BOOL)fillMesh;


/**
 Updates the geometry with the vertices of a face geometry.
 
 @param faceGeometry A face geometry.
 */
- (void)updateFromFaceGeometry:(ARFaceGeometry *)faceGeometry;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARSkeletonDefinition.h
//
//  ARSkeletonDefinition.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString *ARSkeletonJointName NS_TYPED_ENUM NS_SWIFT_NAME(ARSkeleton.JointName)       API_AVAILABLE(ios(13.0));
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameRoot                            API_AVAILABLE(ios(13.0));
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameHead                            API_AVAILABLE(ios(13.0));
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameLeftHand                        API_AVAILABLE(ios(13.0));
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameRightHand                       API_AVAILABLE(ios(13.0));
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameLeftFoot                        API_AVAILABLE(ios(13.0));
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameRightFoot                       API_AVAILABLE(ios(13.0));
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameLeftShoulder                    API_AVAILABLE(ios(13.0));
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameRightShoulder                   API_AVAILABLE(ios(13.0));

@class ARSkeleton2D;
@class ARSkeleton3D;

/**
 Definition of a skeleton.

 @discussion A skeleton consists of a set of labeled joints that are defined in a certain hierarchy, i.e. joints are parented to other joints.
 One may use the parentIndices property to identify the hierarchy for a given skeleton definition.
 */
API_AVAILABLE(ios(13.0))
@interface ARSkeletonDefinition : NSObject

/**
 Default skeleton definition for bodies defined in 3D.
 @note The default height of this skeleton is defined to be 1.8 meters.
 @see ARSkeleton3D
 */
@property (class, nonatomic, readonly) ARSkeletonDefinition *defaultBody3DSkeletonDefinition;

/**
 Default skeleton definition for bodies defined in 2D.
 @see ARBody2D
 */
@property (class, nonatomic, readonly) ARSkeletonDefinition *defaultBody2DSkeletonDefinition;

/**
 The joint names.
 */
@property (nonatomic, readonly) NSArray<NSString *> *jointNames;

/**
 The parent index for each joint.
 @discussion This property may be used to identify the hierarchical dependency between joints. If a line is drawn for every joint and its parent joint
 the result is a visualization of the underlying skeleton. The joint with no parent is denoted as the root joint. The root joint's parent index has
 a value of -1.
  */
@property (nonatomic, readonly) NSArray<NSNumber *> *parentIndices NS_REFINED_FOR_SWIFT;

/**
 The 3D skeleton in neutral pose.
 @discussion The neutral skeleton pose assumes a standardized size of the skeleton in meters. The neutral pose is defined as the skeleton's T-pose.
 */
@property (nonatomic, nullable, readonly) ARSkeleton3D *neutralBodySkeleton3D;

/**
 Returns the index for a given joint identifier.
 
 @param jointName Name of a given joint.
 @discussion This function returns NSNotFound if an invalid joint name is passed.
 @return Joint index.
 */
- (NSUInteger)indexForJointName:(ARSkeletonJointName)jointName NS_REFINED_FOR_SWIFT;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARReferenceObject.h
//
//  ARReferenceObject.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0))
FOUNDATION_EXTERN NSString *const ARReferenceObjectArchiveExtension NS_SWIFT_NAME(ARReferenceObject.archiveExtension);

@class ARPointCloud;

/**
 A reference object to track in the scene.
 */
API_AVAILABLE(ios(12.0))
@interface ARReferenceObject : NSObject<NSSecureCoding>

/**
 An optional name used to identify the object.
 */
@property (nonatomic, copy, nullable) NSString *name;

/**
 The center of the object in the object’s local coordinate space.
 */
@property (nonatomic, readonly) simd_float3 center;

/**
 The extent of the object in the object’s local coordinate space.
 */
@property (nonatomic, readonly) simd_float3 extent;

/**
 The scale of the object’s local coordinate space.
 @discussion Multiplying the extent by this scale will result in the physical extent of the object, measured in meters.
 */
@property (nonatomic, readonly) simd_float3 scale;

/**
 The AR resource group name for this object.
 @discussion If this object was loaded via an AR resource group in the Xcode asset catalogue this property will have the name of the resource group,
 else be set to nil.
 */
@property (nonatomic, strong, nullable, readonly) NSString *resourceGroupName API_AVAILABLE(ios(13.0));

/**
 The feature points of the object.
 */
@property (nonatomic, strong, readonly) ARPointCloud *rawFeaturePoints;

/**
 Returns the set of ARReferenceObjects in the specified resource group and bundle.
 
 @param name The name of the resource group.
 @param bundle The bundle containing the image file or asset catalog. Specify nil to search the app’s main bundle.
 @return The set of reference objects or nil on error.
 */
+ (nullable NSSet<ARReferenceObject *> *)referenceObjectsInGroupNamed:(NSString *)name bundle:(nullable NSBundle *)bundle;

/**
 Initializes a new reference object with the contents of an archive at the specified URL.
 @param url The URL from which to read data (.arobject archive).
 @param error The error to populate if the object could not be initialized.
 */
- (nullable instancetype)initWithArchiveURL:(NSURL *)url error:(NSError **)error;

/**
 Exports the object as an archive at the given URL.
 
 @discussion The URL path should use ARReferenceObjectArchiveExtension (.arobject) for the file extension.
 If serialization across devices is desired, NSKeyedArchiver should be used instead.
 @param url The URL at which to write the exported object.
 @param previewImage An optional preview image to include in the archive.
 @param error The error to populate if the write is not successful.
 @return YES if the location is written successfully, otherwise NO.
 */
- (BOOL)exportObjectToURL:(NSURL *)url previewImage:(nullable UIImage *)previewImage error:(NSError **)error;

/**
 Returns a new reference object by applying the specified transform to the object's origin.
 @discussion This can be used to change the reference object's origin with respect to the physical object. Providing
 a transform local to the current object's coordinate space will return an object with the transform's position and orientation as the origin.
 @param transform The rotation and translation to apply to the object's origin.
 @return A reference object with updated origin.
*/
- (ARReferenceObject *)referenceObjectByApplyingTransform:(simd_float4x4)transform;

/**
 Returns a new reference object by aligning and merging the provided object with this reference.
 @discussion This can be used to combine multiple scans of the same object for detection in different conditions. The object being merged
 must share similar feature points for the merge to succeed.
 @param object The reference object to align and merge.
 @param error The error to populate if the merge is not successful.
 @return A new reference object combining features of both scans or nil if the merge was not successful.
 */
- (nullable ARReferenceObject *)referenceObjectByMergingObject:(ARReferenceObject *)object error:(NSError **)error;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARImageAnchor.h
//
//  ARImageAnchor.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

@class ARReferenceImage;

NS_ASSUME_NONNULL_BEGIN

/**
 An anchor representing an image in the world.
 */
API_AVAILABLE(ios(11.3))
@interface ARImageAnchor : ARAnchor <ARTrackable>

/**
 Reference to the detected image.
 */
@property (nonatomic, strong, readonly) ARReferenceImage *referenceImage;

/**
 The factor between estimated physical size and provided size.
 
 @discussion This value will be estimated if automaticImageScaleEstimationEnabled is set to true on the ARWorldTrackingConfiguration. It is used to
 correct the transform's translation. Default value is 1.0.
 */
@property (nonatomic, readonly) CGFloat estimatedScaleFactor API_AVAILABLE(ios(13.0));

/** Unavailable */
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
