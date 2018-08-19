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
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
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
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
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
@property (nonatomic, readonly) vector_float3 primaryLightDirection;

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
typedef NSString *ARBlendShapeLocation NS_STRING_ENUM NS_SWIFT_NAME(ARFaceAnchor.BlendShapeLocation) API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowDownLeft           API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowDownRight          API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowInnerUp            API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowOuterUpLeft        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowOuterUpRight       API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationCheekPuff              API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationCheekSquintLeft        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationCheekSquintRight       API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeBlinkLeft           API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeBlinkRight          API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookDownLeft        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookDownRight       API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookInLeft          API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookInRight         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookOutLeft         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookOutRight        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookUpLeft          API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookUpRight         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeSquintLeft          API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeSquintRight         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeWideLeft            API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeWideRight           API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationJawForward             API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationJawLeft                API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationJawOpen                API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationJawRight               API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthClose             API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthDimpleLeft        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthDimpleRight       API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthFrownLeft         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthFrownRight        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthFunnel            API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthLeft              API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthLowerDownLeft     API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthLowerDownRight    API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthPressLeft         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthPressRight        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthPucker            API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthRight             API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthRollLower         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthRollUpper         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthShrugLower        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthShrugUpper        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthSmileLeft         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthSmileRight        API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthStretchLeft       API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthStretchRight      API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthUpperUpLeft       API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthUpperUpRight      API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationNoseSneerLeft          API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationNoseSneerRight         API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

@class ARFaceGeometry;

/**
 An anchor representing a face and its geometry.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARFaceAnchor : ARAnchor <ARTrackable>

/**
 The face geometry updated based on the computed blend shapes.
 */
@property (nonatomic, readonly) ARFaceGeometry *geometry;

/**
 A dictionary of blend shape coefficients for each blend shape location.
 @discussion Blend shapes coefficients define the amount of displacement of a neutral shape at a specific location on the face.
 */
@property (nonatomic, readonly) NSDictionary<ARBlendShapeLocation, NSNumber*> *blendShapes;

/** Unavailable */
- (instancetype)initWithTransform:(matrix_float4x4)transform NS_UNAVAILABLE;

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

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
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
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARSKView : SKView

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
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_OPTIONS(NSUInteger, ARHitTestResultType) {
    /** Result type from intersecting the nearest feature point. */
    ARHitTestResultTypeFeaturePoint              = (1 << 0),
    
    /** Result type from intersecting a horizontal plane estimate, determined for the current frame. */
    ARHitTestResultTypeEstimatedHorizontalPlane  = (1 << 1),
    
    /** Result type from intersecting with an existing plane anchor. */
    ARHitTestResultTypeExistingPlane             = (1 << 3),
    
    /** Result type from intersecting with an existing plane anchor, taking into account the plane’s extent. */
    ARHitTestResultTypeExistingPlaneUsingExtent  = (1 << 4),
} NS_SWIFT_NAME(ARHitTestResult.ResultType);

NS_ASSUME_NONNULL_BEGIN

/**
 A result of an intersection found during a hit-test.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
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
@property (nonatomic, readonly) matrix_float4x4 localTransform;

/**
 The transformation matrix that defines the intersection’s rotation, translation and scale
 relative to the world.
 */
@property (nonatomic, readonly) matrix_float4x4 worldTransform;

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

#import <ARKit/ARAnchor.h>
#import <ARKit/ARPlaneAnchor.h>

#import <ARKit/ARFaceAnchor.h>
#import <ARKit/ARFaceGeometry.h>

#import <ARKit/ARSCNView.h>
#import <ARKit/ARSKView.h>
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
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
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
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_ENUM(NSInteger, ARTrackingStateReason) {
    /** Tracking is not limited. */
    ARTrackingStateReasonNone,
    
    /** Tracking is limited due to initialization in progress. */
    ARTrackingStateReasonInitializing,
    
    /** Tracking is limited due to a excessive motion of the camera. */
    ARTrackingStateReasonExcessiveMotion,
    
    /** Tracking is limited due to a lack of features visible to the camera. */
    ARTrackingStateReasonInsufficientFeatures,
} NS_REFINED_FOR_SWIFT;


/**
 A model representing the camera and its parameters.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARCamera : NSObject <NSCopying>

/**
 The transformation matrix that defines the camera’s rotation and translation in world coordinates.
 */
@property (nonatomic, readonly) matrix_float4x4 transform;

/**
 The camera’s orientation defined as Euler angles.
 
 @dicussion The order of components in this vector matches the axes of rotation:
               1. Pitch (the x component) is the rotation about the node’s x-axis (in radians)
               2. Yaw   (the y component) is the rotation about the node’s y-axis (in radians)
               3. Roll  (the z component) is the rotation about the node’s z-axis (in radians)
            ARKit applies these rotations in the reverse order of the components:
               1. first roll
               2. then yaw
               3. then pitch
 */
@property (nonatomic, readonly) vector_float3 eulerAngles;

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
@property (nonatomic, readonly) matrix_float3x3 intrinsics;

/**
 The camera image resolution in pixels.
 */
@property (nonatomic, readonly) CGSize imageResolution;

/**
 The projection matrix of the camera.
*/
@property (nonatomic, readonly) matrix_float4x4 projectionMatrix;

/**
 Project a 3D point in world coordinate system into 2D viewport space.
 
 @param point 3D point in world coordinate system.
 @param orientation Viewport orientation.
 @param viewportSize Viewport (or image) size.
 @return 2D point in viewport coordinate system with origin at top-left.
 */
- (CGPoint)projectPoint:(vector_float3)point orientation:(UIInterfaceOrientation)orientation viewportSize:(CGSize)viewportSize;

/**
 Creates a projection matrix for the camera given rendering parameters.
 
 @discussion The projection matrix returned provides an aspect fill for the provided viewport size and orientation.
 @param orientation Viewport orientation.
 @param viewportSize Viewport size.
 @param zNear Near depth limit.
 @param zFar Far depth limit.
 */
- (matrix_float4x4)projectionMatrixForOrientation:(UIInterfaceOrientation)orientation viewportSize:(CGSize)viewportSize zNear:(CGFloat)zNear zFar:(CGFloat)zFar;

/**
 Creates a view matrix for the camera given an interface orientation.
 
 @discussion The view matrix can be used to transform geometry into camera space for a given orientation
 @param orientation The interface orientation that will be used to render the camera’s view.
 */
- (matrix_float4x4)viewMatrixForOrientation:(UIInterfaceOrientation)orientation;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

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

@class ARAnchor;
@class ARCamera;
@class ARLightEstimate;
@class ARPointCloud;
@class AVDepthData;

NS_ASSUME_NONNULL_BEGIN

/**
 An object encapsulating the state of everything being tracked for a given moment in time.
 @discussion The model provides a snapshot of all data needed to render a given frame.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
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
 The frame’s captured depth data.
 
 @discussion Depth data is only provided with face tracking on frames where depth data was captured.
 */
@property (nonatomic, strong, readonly, nullable) AVDepthData *capturedDepthData;

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
@protocol ARSessionDelegate;

/**
 Set of options for running the session.
 @discussion These options alter the behavior of calling run on a session.
 Providing no options will result in the default behavior of resuming tracking
 from the last known position and keeping all existing anchors.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_OPTIONS(NSUInteger, ARSessionRunOptions) {
    /** The session will reset tracking. */
    ARSessionRunOptionResetTracking           = (1 << 0),
    
    /** The session will remove existing anchors. */
    ARSessionRunOptionRemoveExistingAnchors   = (1 << 1)
} NS_SWIFT_NAME(ARSession.RunOptions);

/**
 The ARSession class configures and runs different Augmented Reality techniques on a device.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARSession : NSObject

/**
 A delegate for receiving ARSession updates.
 */
@property (nonatomic, weak) id <ARSessionDelegate> delegate;

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

@end


#pragma mark - ARSessionObserver


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
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
 To avoid this, some applications may want to reset tracking (see ARSessionRunOptions).
 @param session The session that was interrupted.
 */
- (void)sessionInterruptionEnded:(ARSession *)session;

/**
 This is called when the session outputs a new audio sample buffer.
 
 @param session The session being run.
 @param audioSampleBuffer The captured audio sample buffer.
 */
- (void)session:(ARSession *)session didOutputAudioSampleBuffer:(CMSampleBufferRef)audioSampleBuffer;

@end

#pragma mark - ARSessionDelegate


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
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

NS_ASSUME_NONNULL_END
// ==========  ARKit.framework/Headers/ARPlaneAnchor.h
//
//  ARPlaneAnchor.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A value describing the alignment of a plane anchor.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_ENUM(NSInteger, ARPlaneAnchorAlignment) {
    /** A plane that is horizontal with respect to gravity. */
    ARPlaneAnchorAlignmentHorizontal

} NS_SWIFT_NAME(ARPlaneAnchor.Alignment);

/**
 An anchor representing a planar surface in the world.
 @discussion Planes are defined in the X and Z direction, where Y is the surface’s normal.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARPlaneAnchor : ARAnchor

/**
 The alignment of the plane.
 */
@property (nonatomic, readonly) ARPlaneAnchorAlignment alignment;

/**
 The center of the plane in the anchor’s coordinate space.
 */
@property (nonatomic, readonly) vector_float3 center;

/**
 The extent of the plane in the anchor’s coordinate space.
 */
@property (nonatomic, readonly) vector_float3 extent;

/** Unavailable */
- (instancetype)initWithTransform:(matrix_float4x4)transform NS_UNAVAILABLE;

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

@protocol ARSCNViewDelegate;

NS_ASSUME_NONNULL_BEGIN

/**
 A view that integrates ARSession rendering into SceneKit.
 
 @discussion The view draws the camera background, provides and updates a camera,
 manages nodes for anchors, and updates lighting.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARSCNView : SCNView

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
@property(nonatomic, strong) SCNScene *scene;

/**
 Determines whether the view will update the scene’s lighting.
 
 @discussion When set, the view will automatically create and update lighting for 
 light estimates the session provides. Defaults to YES.
 */
@property(nonatomic) BOOL automaticallyUpdatesLighting;

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

@end


#pragma mark - ARSCNViewDelegate


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
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
struct ARSCNDebugOptions {} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/** Show the world origin in the scene. */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
FOUNDATION_EXTERN const SCNDebugOptions ARSCNDebugOptionShowWorldOrigin NS_SWIFT_NAME(ARSCNDebugOptions.showWorldOrigin);

/** Show detected 3D feature points in the world. */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
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

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARPointCloud : NSObject

/**
 The number of points in the point cloud.
 */
@property (nonatomic, readonly) NSUInteger count NS_REFINED_FOR_SWIFT;

/**
 The 3D points comprising the point cloud.
 */
@property (nonatomic, readonly) const vector_float3 *points NS_REFINED_FOR_SWIFT;

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

/**
 Enum constants for indicating the world alignment.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
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
 Option set indicating the type of planes to detect.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_OPTIONS(NSUInteger, ARPlaneDetection) {
    /** No plane detection is run. */
    ARPlaneDetectionNone        = 0,
    
    /** Plane detection determines horizontal planes in the scene. */
    ARPlaneDetectionHorizontal  = (1 << 0),
} NS_SWIFT_NAME(ARWorldTrackingConfiguration.PlaneDetection);


/**
 An object to describe and configure the Augmented Reality techniques to be used in an ARSession.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARConfiguration : NSObject <NSCopying>

/**
 Determines whether this device supports the ARConfiguration.
 */
@property(class, nonatomic, readonly) BOOL isSupported;

/**
 Determines how the coordinate system should be aligned with the world.
 @discussion The default is ARWorldAlignmentGravity.
 */
@property (nonatomic, readwrite) ARWorldAlignment worldAlignment;

/**
 Enable or disable light estimation.
 @discussion Enabled by default.
 */
@property (nonatomic, readwrite, getter=isLightEstimationEnabled) BOOL lightEstimationEnabled;

/**
 Determines whether to capture and provide audio data.
 @discussion Disabled by default.
 */
@property (nonatomic, readwrite) BOOL providesAudioData;

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
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARWorldTrackingConfiguration : ARConfiguration

/**
 Type of planes to detect in the scene.
 @discussion If set, new planes will continue to be detected and updated over time. Detected planes will be added to the session as
 ARPlaneAnchor objects. In the event that two planes are merged, the newer plane will be removed. Defaults to ARPlaneDetectionNone.
 */
@property (nonatomic, readwrite) ARPlaneDetection planeDetection;

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end


/**
 A configuration for running orientation tracking.
 
 @discussion Orientation tracking provides 3 degrees of freedom tracking of the device.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface AROrientationTrackingConfiguration : ARConfiguration

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end

/**
 A configuration for running face tracking.
 
 @discussion Face tracking uses the front facing camera to track the face in 3D providing details on the topology and expression of the face.
 A detected face will be added to the session as an ARFaceAnchor object which contains information about head pose, mesh, eye pose, and blend shape
 coefficients. If light estimation is enabled the detected face will be treated as a light probe and used to estimate the direction of incoming light.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARFaceTrackingConfiguration : ARConfiguration

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

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
FOUNDATION_EXTERN NSString *const ARErrorDomain;

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_ERROR_ENUM(ARErrorDomain, ARErrorCode) {
    /** Unsupported configuration. */
    ARErrorCodeUnsupportedConfiguration   = 100,
    
    /** A sensor required to run the session is not available. */
    ARErrorCodeSensorUnavailable          = 101,
    
    /** A sensor failed to provide the required input. */
    ARErrorCodeSensorFailed               = 102,
    
    /** App does not have permission to use the camera. The user may change this in settings. */
    ARErrorCodeCameraUnauthorized         = 103,
    
    /** World tracking has encountered a fatal error. */
    ARErrorCodeWorldTrackingFailed        = 200,
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

/**
 Object representing a physical location and orientation in 3D space.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARAnchor : NSObject <NSCopying>

/**
 Unique identifier of the anchor.
 */
@property (nonatomic, readonly) NSUUID *identifier;

/**
 The transformation matrix that defines the anchor’s rotation, translation and scale in world coordinates.
 */
@property (nonatomic, readonly) matrix_float4x4 transform;

/**
 Initializes a new anchor object.
 @param transform The transformation matrix that defines the anchor’s rotation, translation and scale in world coordinates.
 */
- (instancetype)initWithTransform:(matrix_float4x4)transform;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 A real world object or location in the scene that is being tracked.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol ARTrackable <NSObject>

/**
 Tracking state of the anchor
 @discussion The isTracked value is used to determine the anchor transform’s validity. When the object being tracked is no longer detected in the
 camera image, its anchor will return NO for isTracked.
 */
@property (nonatomic, readonly) BOOL isTracked;

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
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARFaceGeometry : NSObject<NSCopying>

/**
The number of mesh vertices of the geometry.
 */
@property (nonatomic, readonly) NSUInteger vertexCount NS_REFINED_FOR_SWIFT;

/**
 The mesh vertices of the geometry.
 */
@property (nonatomic, readonly) const vector_float3 *vertices NS_REFINED_FOR_SWIFT;

/**
 The number of texture coordinates of the face geometry.
 */
@property (nonatomic, readonly) NSUInteger textureCoordinateCount NS_REFINED_FOR_SWIFT;

/**
 The texture coordinates of the geometry.
 */
@property (nonatomic, readonly) const vector_float2 *textureCoordinates NS_REFINED_FOR_SWIFT;

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
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARSCNFaceGeometry : SCNGeometry

/**
 Creates a new face geometry using a metal device.
 
 @param device A metal device.
 @return A new face geometry
 */
+ (nullable instancetype)faceGeometryWithDevice:(id<MTLDevice>)device;


/**
 Creates a new face geometry using a metal device.
 
 @discussion By default the regions between the eye lids as well as the region
 between the lips are not covered by geometry. For using the face geometry as an
 occlusion geometry set \p fillMesh to YES. This will fill
 in additional geometry into the gaps between the eye lids as well as into the
 gap between the lips.
 @param fillMesh Whether to fill in additional geometry into the
 gaps between the eye lids as well as into the gap between the lips.
 
 @return A new face geometry
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

