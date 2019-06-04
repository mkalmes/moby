// ==========  SpriteKit.framework/Headers/SKAudioNode.h
/**
 @header
 
 Node that holds an AVAudioEngine sound graph, including from a single sound source or URL.
 
 @copyright 2015 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SpriteKit.h>

#if __has_include(<AVFoundation/AVAudioEngine.h>)

@class AVAudioNode;

NS_ASSUME_NONNULL_BEGIN

/**
 * A SpriteKit scene graph audio node that provides a way to link audio graphs to a SpriteKit scene.
 * The currently presented scene is responsible for mixing the audio from nodes in the scene.
 *
 * Positional sounds will use their relative location and velocity to the scene's listener to apply distance
 * attenuation, doppler shift and pan.
 * 
 * @see AVAudio3DMixing
 * @see SKScene.listener
 */
SK_EXPORT API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11)) @interface SKAudioNode : SKNode <NSSecureCoding>

/**Creates a SpriteKit scene graph audio node from the given AVAudioNode.
 * @see AVAudioNode
 */
- (instancetype)initWithAVAudioNode:(nullable AVAudioNode *)node NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/**Convenience initializer that creates an AVAudioNode from the named audio asset in the main bundle.
 * @see initWithAVAudioNode
 */
- (instancetype)initWithFileNamed:(NSString *)name;

/**Convenience initializer that creates an AVAudioNode from the URL that contain a audio asset.
 * @see initWithAVAudioNode
 */
- (instancetype)initWithURL:(NSURL *)url;

/**Sets or gets the current AVAudioNode used by this instance.
 */
@property (nonatomic, retain, nullable) AVAudioNode *avAudioNode;

/**Specifies whether the node is to automatically play sound when added to a scene.
 * If autoplaysLooped is NO, the node and its sound must be explicitly scheduled and played using
 * the scene's engine.
 *
 * If YES, the node will automatically play sound when added to a scene.
 *
 * Defaults to YES.
 * @see SKView.paused
 */
@property (nonatomic, assign) BOOL autoplayLooped;

/**Marks the audio source as positional so that the audio mix considers relative position and velocity
 * with regards to the scene's current listener node.
 *
 * @see AVAudio3DMixing
 * @see SKScene.listener
 */
@property (nonatomic, assign, getter=isPositional) BOOL positional;

@end

/**Actions that are to be used with audio nodes.
 */
@interface SKAction (SKAudioNode)

+ (SKAction *)stereoPanTo:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)stereoPanBy:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)changeReverbTo:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)changeReverbBy:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)changeObstructionTo:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)changeObstructionBy:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)changeOcclusionTo:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)changeOcclusionBy:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

@end

NS_ASSUME_NONNULL_END

#endif
// ==========  SpriteKit.framework/Headers/SKAttribute.h
/**
 @header
 
 SKAttributes can be used to provide a per-node value to be
 used with SKShaders.
 
 @copyright 2015 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SpriteKitBase.h>
#import <simd/simd.h>

extern unsigned short floatToHalfFloat(float f);

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SKAttributeType) {
    SKAttributeTypeNone                 =    0,
    
    SKAttributeTypeFloat                =    1,
    SKAttributeTypeVectorFloat2         =    2,
    SKAttributeTypeVectorFloat3         =    3,
    SKAttributeTypeVectorFloat4         =    4,
    
    SKAttributeTypeHalfFloat            =    5,
    SKAttributeTypeVectorHalfFloat2     =    6,
    SKAttributeTypeVectorHalfFloat3     =    7,
    SKAttributeTypeVectorHalfFloat4     =    8,
    
} NS_ENUM_AVAILABLE(10_11, 9_0);

NS_CLASS_AVAILABLE(10_11, 9_0)
SK_EXPORT @interface SKAttribute : NSObject <NSSecureCoding>

+ (instancetype)attributeWithName:(NSString*)name type:(SKAttributeType)type;
- (instancetype)initWithName:(NSString*)name type:(SKAttributeType)type NS_DESIGNATED_INITIALIZER;

@property (readonly, nonatomic) NSString *name;
@property (readonly, nonatomic) SKAttributeType type;

@end



NS_CLASS_AVAILABLE(10_11, 9_0)
SK_EXPORT @interface SKAttributeValue : NSObject <NSSecureCoding>

+ (instancetype)valueWithFloat:(float)value;
+ (instancetype)valueWithVectorFloat2:(vector_float2)value;
+ (instancetype)valueWithVectorFloat3:(vector_float3)value;
+ (instancetype)valueWithVectorFloat4:(vector_float4)value;

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@property (nonatomic) float floatValue;
@property (nonatomic) vector_float2 vectorFloat2Value;
@property (nonatomic) vector_float3 vectorFloat3Value;
@property (nonatomic) vector_float4 vectorFloat4Value;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKRenderer.h
//
// SKRenderer.h
// SpriteKit
//
// Copyright (c) 2016 Apple Inc. All rights reserved
//

#import <SpriteKit/SpriteKitBase.h>
#import <SpriteKit/SKScene.h>

/* SKRenderer is not available for WatchKit apps and the iOS simulator */
#if SKVIEW_AVAILABLE && !TARGET_OS_SIMULATOR

#import <Metal/Metal.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A renderer for displaying a SpriteKit scene in an existing Metal workflow.
 */
API_AVAILABLE(ios(11.0), tvos(11.0), watchos(4.0), macos(10.13)) SK_EXPORT @interface SKRenderer : NSObject

/**
 Creates a renderer with the specified Metal device.
 
 @param device A Metal device.
 @return A new renderer object.
 */
+ (SKRenderer *)rendererWithDevice:(id<MTLDevice>)device;

/**
 Render the scene content in the specified Metal command buffer.
 
 @param viewport The pixel dimensions in which to render.
 @param commandBuffer The Metal command buffer in which SpriteKit should schedule rendering commands.
 @param renderPassDescriptor The Metal render pass descriptor describing the rendering target.
 */
- (void)renderWithViewport:(CGRect)viewport
             commandBuffer:(id <MTLCommandBuffer>)commandBuffer
      renderPassDescriptor:(MTLRenderPassDescriptor *)renderPassDescriptor;

/**
 Render the scene content using a specific Metal command encoder.
 
 @param viewport The pixel dimensions in which to render.
 @param renderCommandEncoder The Metal render command encoder that SpriteKit will use to encode rendering commands. This method will not call endEncoding.
 @param renderPassDescriptor The Metal render pass descriptor describing the rendering target.
 @param commandQueue The Metal command queue.
 */
- (void)renderWithViewport:(CGRect)viewport
      renderCommandEncoder:(id <MTLRenderCommandEncoder>)renderCommandEncoder
      renderPassDescriptor:(MTLRenderPassDescriptor *)renderPassDescriptor
              commandQueue:(id <MTLCommandQueue>)commandQueue;

/**
 Update the scene at the specified system time.
 
 @param currentTime The timestamp in seconds.
 */
- (void)updateAtTime:(NSTimeInterval)currentTime;

/**
 The currently presented scene, otherwise nil. If in a transition, the 'incoming' scene is returned.
 */
@property (nonatomic, nullable) SKScene *scene;

/**
 Ignores sibling and traversal order to sort the rendered contents of a scene into the most efficient batching possible.
 This will require zPosition to be used in the scenes to properly guarantee elements are in front or behind each other.

 This defaults to NO, meaning that sibling order overrides efficiency heuristics in the rendering of the scenes in the view.

 Setting this to YES for a complex scene may substantially increase performance, but care must be taken as only zPosition
 determines render order before the efficiency heuristics are used.
 */
@property (nonatomic) BOOL ignoresSiblingOrder;

/**
 A boolean that indicated whether non-visible nodes should be automatically culled when rendering.
 */
@property (nonatomic) BOOL shouldCullNonVisibleNodes;

/**
 Toggles display of performance stats when rendering. All default to false.
 */
@property (nonatomic) BOOL showsDrawCount;
@property (nonatomic) BOOL showsNodeCount;
@property (nonatomic) BOOL showsQuadCount;
@property (nonatomic) BOOL showsPhysics;
@property (nonatomic) BOOL showsFields;

@end

NS_ASSUME_NONNULL_END

#endif

// ==========  SpriteKit.framework/Headers/SKVideoNode.h
/**
 @header
 
 
 Node that can play a video file
 
 
 @copyright 2011 Apple, Inc. All rights reserved.
 
 */

@class AVPlayer;


#import <SpriteKit/SKSpriteNode.h>
#import <SpriteKit/SpriteKitBase.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT @interface SKVideoNode : SKNode

/**
 Create a video node from an AVPlayer. You can use the AVPlayer to control playback.
 */
+ (SKVideoNode *)videoNodeWithAVPlayer:(AVPlayer*)player;

/**
 Create a video node from a file.
 */
+ (SKVideoNode *)videoNodeWithVideoFileNamed:(NSString *)videoFile NS_DEPRECATED(10_8, 10_11, 7_0, 9_0);
+ (SKVideoNode *)videoNodeWithFileNamed:(NSString *)videoFile API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/**
 Create a video node from a URL.
 */
+ (SKVideoNode *)videoNodeWithVideoURL:(NSURL *)videoURL NS_DEPRECATED(10_8, 10_11, 7_0, 9_0);
+ (SKVideoNode *)videoNodeWithURL:(NSURL *)videoURL API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/**
 Designated Initializer.
 
 Initialize a video node from an AVPlayer. You can use the AVPlayer to control playback.
 */
- (instancetype)initWithAVPlayer:(AVPlayer*)player NS_DESIGNATED_INITIALIZER;

/**
 Initialize a video node from a file.
 */
- (instancetype)initWithVideoFileNamed:(NSString *)videoFile NS_DESIGNATED_INITIALIZER NS_DEPRECATED(10_8, 10_10, 7_0, 8_0);
- (instancetype)initWithFileNamed:(NSString *)videoFile NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

- (instancetype)initWithVideoURL:(NSURL *)url NS_DESIGNATED_INITIALIZER NS_DEPRECATED(10_8, 10_10, 7_0, 8_0);
- (instancetype)initWithURL:(NSURL *)url NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/**
 Support coding and decoding via NSKeyedArchiver.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

- (void)play;
- (void)pause;

/**
 The display size of the video (in parent's coordinate space)
 */
@property (nonatomic) CGSize size;

/**
 The location in the video that maps to its 'position' in the parent's coordinate space. (0.0-1.0)
 */
@property (nonatomic) CGPoint anchorPoint;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SK3DNode.h
/**
 @header
 
 
 3D Nodes are used to display 3D content in a SKScene.
 
 
 @copyright 2011 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SKSpriteNode.h>
#import <SpriteKit/SpriteKitBase.h>

@class SCNScene;
@class SCNNode;
@class SCNHitTestResult;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_10, 8_0)
SK_EXPORT @interface SK3DNode : SKNode


/**
 Designated initializer.
 Initialize a 3D Node with the viewport size the 3D content will be rendered with.
*/
- (instancetype)initWithViewportSize:(CGSize)viewportSize NS_DESIGNATED_INITIALIZER;

/**
 Support coding and decoding via NSKeyedArchiver.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/**
 Create a 3D Node with the viewport size the 3D content will be rendered with.
 */
+ (instancetype)nodeWithViewportSize:(CGSize)viewportSize;


/** The viewport size that the 3D content will be rendered with */
@property CGSize viewportSize;

/** A SceneKit scene  */
@property (nonatomic, retain, nullable) SCNScene *scnScene;

/** 
 @property sceneTime
 @abstract Specifies the current time to display the scene.
*/
@property(nonatomic) NSTimeInterval sceneTime;

/**
 @method hitTest:options:
 @abstract Returns an array of SCNHitTestResult for each node that contains a specified point.
 @param point A point in the coordinate system of the receiver.
 @param options Optional parameters (see the "Hit test options" group for the available options).
*/
- (NSArray<SCNHitTestResult *> *)hitTest:(CGPoint)point options:(nullable NSDictionary<NSString *, id> *)options;

/**
 @method projectPoint
 @abstract Projects a point in the world coordinate system using the receiver's current point of view and viewport.
 @param point The world position to be projected.
 @discussion A point projected from the near (resp. far) clip plane will have a z component of 0 (resp. 1).
*/
- (vector_float3)projectPoint:(vector_float3)point;

/**
 @method unprojectPoint
 @abstract Unprojects a screenspace 2D point with depth info using the receiver's current point of view and viewport.
 @param point The screenspace position to be unprojected.
 @discussion A point whose z component is 0 (resp. 1) is unprojected on the near (resp. far) clip plane.
*/
- (vector_float3)unprojectPoint:(vector_float3)point;

 /**
 @property playing
 @abstract Returns YES if the scene is playing, NO otherwise.
  */
@property(getter=isPlaying) BOOL playing;

/**
 @property loops
 @abstract Indicates whether the receiver restarts playback when it reaches the end of its content. Default: YES.
 @discussion YES when the receiver restarts playback when it finishes, NO otherwise.
*/
@property(nonatomic) BOOL loops;

/**
 @property pointOfView
 @abstract Specifies the point of view used to render the scene.
 @discussion A point of view must have either a camera or a spot light attached.
 */
@property(nonatomic, retain, nullable) SCNNode *pointOfView;

/**
 @property autoenablesDefaultLighting
 @abstract Specifies whether the receiver should automatically light up scenes that have no light source. The default is NO.
 @discussion When enabled, a diffuse light is automatically added and placed while rendering scenes that have no light or only ambient lights.
 */
@property(nonatomic) BOOL autoenablesDefaultLighting;


@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKScene.h
//
//  SKScene.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <SpriteKit/SKCameraNode.h>
#import <SpriteKit/SKEffectNode.h>
#import <SpriteKit/SpriteKitBase.h>

#if SKVIEW_AVAILABLE
@class SKView;
#endif

@class SKPhysicsWorld, AVAudioEngine;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SKSceneScaleMode) {
    SKSceneScaleModeFill,           /* Scale the SKScene to fill the entire SKView. */
    SKSceneScaleModeAspectFill,     /* Scale the SKScene to fill the SKView while preserving the scene's aspect ratio. Some cropping may occur if the view has a different aspect ratio. */
    SKSceneScaleModeAspectFit,      /* Scale the SKScene to fit within the SKView while preserving the scene's aspect ratio. Some letterboxing may occur if the view has a different aspect ratio. */
    SKSceneScaleModeResizeFill      /* Modify the SKScene's actual size to exactly match the SKView. */
} NS_ENUM_AVAILABLE(10_9, 7_0);

API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10)) @protocol SKSceneDelegate <NSObject>
@optional
- (void)update:(NSTimeInterval)currentTime forScene:(SKScene *)scene;
- (void)didEvaluateActionsForScene:(SKScene *)scene;
- (void)didSimulatePhysicsForScene:(SKScene *)scene;

- (void)didApplyConstraintsForScene:(SKScene *)scene;
- (void)didFinishUpdateForScene:(SKScene *)scene;
@end

/**
 A scene is the root node of your content. It is used to display SpriteKit content on an SKView.
 
 @see SKView
 */
SK_EXPORT @interface SKScene : SKEffectNode

/**
 A scene is infinitely large, but it has a viewport that is the frame through which you present the content of the scene.
 The passed in size defines the size of this viewport that you use to present the scene.
 
 @param size a size in points that signifies the viewport into the scene that defines your framing of the scene.
 */
- (instancetype)initWithSize:(CGSize)size;

+ (instancetype)sceneWithSize:(CGSize)size;

/* This is called once after the scene has been initialized or decoded,
 this is the recommended place to perform one-time setup */
- (void)sceneDidLoad API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

@property (nonatomic) CGSize size;

/**
 Used to determine how to scale the scene to match the SKView it is being displayed in.
 */
@property (nonatomic) SKSceneScaleMode scaleMode;

/**
 The camera that is used to obtain the view scale and translation based on where the camera is in relation to the scene.
 */
@property (nonatomic, weak, nullable) SKCameraNode *camera API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/**
 The node that is currently the listener for positional audio coming from SKAudioNodes
 @see SKAudioNode
 */
@property (nonatomic, weak, nullable) SKNode *listener API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/**
 The audio engine that the listener and the scene's audio nodes use to process their sound through.
 */
#if __has_include(<AVFoundation/AVAudioEngine.h>)
@property (nonatomic, retain, readonly) AVAudioEngine *audioEngine API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
#endif

/**
 Background color, defaults to gray
 */
@property (nonatomic, retain) SKColor *backgroundColor;

@property (nonatomic, weak, nullable) id<SKSceneDelegate> delegate API_AVAILABLE(ios(8.0), tvos(9.0), watchos(2.0), macos(10.10));

/**
 Used to choose the origin of the scene's coordinate system
 */
@property (nonatomic) CGPoint anchorPoint;

/**
 Physics simulation functionality
 */
@property (nonatomic, readonly) SKPhysicsWorld *physicsWorld;


#if SKVIEW_AVAILABLE
/**
 The SKView this scene is currently presented in, or nil if it is not being presented.
 */
@property (nonatomic, weak, readonly, nullable) SKView *view;

- (CGPoint)convertPointFromView:(CGPoint)point;
- (CGPoint)convertPointToView:(CGPoint)point;
#endif

/**
 Override this to perform per-frame game logic. Called exactly once per frame before any actions are evaluated and any physics are simulated.
 
 @param currentTime the current time in the app. This must be monotonically increasing.
 */
- (void)update:(NSTimeInterval)currentTime;

/**
 Override this to perform game logic. Called exactly once per frame after any actions have been evaluated but before any physics are simulated. Any additional actions applied is not evaluated until the next update.
 */
- (void)didEvaluateActions;

/**
 Override this to perform game logic. Called exactly once per frame after any actions have been evaluated and any physics have been simulated. Any additional actions applied is not evaluated until the next update. Any changes to physics bodies is not simulated until the next update.
 */
- (void)didSimulatePhysics;

/**
 Override this to perform game logic. Called exactly once per frame after any enabled constraints have been applied. Any additional actions applied is not evaluated until the next update. Any changes to physics bodies is not simulated until the next update. Any changes to constarints will not be applied until the next update.
 */
- (void)didApplyConstraints API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/**
 Override this to perform game logic. Called after all update logic has been completed. Any additional actions applied are not evaluated until the next update. Any changes to physics bodies are not simulated until the next update. Any changes to constarints will not be applied until the next update.
 
 No futher update logic will be applied to the scene after this call. Any values set on nodes here will be used when the scene is rendered for the current frame.
 */
- (void)didFinishUpdate API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

#if SKVIEW_AVAILABLE
- (void)didMoveToView:(SKView *)view;
- (void)willMoveFromView:(SKView *)view;
#endif

- (void)didChangeSize:(CGSize)oldSize;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKAction.h
/**
 @header
 
 Actions are executed by nodes in a scene in order to change the structure
 and/or content to which they are attached.
 
 @copyright 2011 Apple Inc. All rights reserved.
 
 */

#import <Foundation/Foundation.h>
#import <SpriteKit/SpriteKitBase.h>

@class SKNode;
@class SKTexture;

/** Adjust the timing of an action
 
 @enum SKActionTimingLinear Specifies linear pacing. Linear pacing causes an
 animation to occur evenly over its duration.
 @enum SKActionTimingEaseIn Specifies ease-in pacing. Ease-in pacing causes the
 animation to begin slowly, and then speed up as it progresses.
 @enum SKActionTimingEaseOut Specifies ease-out pacing. Ease-out pacing causes
 the animation to begin quickly, and then slow as it completes.
 @enum SKActionTimingEaseInEaseOut Specifies ease-in ease-out pacing. An
 ease-in ease-out animation begins slowly, accelerates through the middle
 of its duration, and then slows again before completing.
 */
typedef NS_ENUM(NSInteger, SKActionTimingMode) {
    SKActionTimingLinear,
    SKActionTimingEaseIn,
    SKActionTimingEaseOut,
    SKActionTimingEaseInEaseOut
} NS_ENUM_AVAILABLE(10_9, 7_0);

/**
 A custom timing function for SKActions. Input time will be linear 0.0-1.0
 over the duration of the action. Return values must be 0.0-1.0 and increasing
 and the function must return 1.0 when the input time reaches 1.0.
 */
typedef float (^SKActionTimingFunction)(float time);



/**
 An SKAction object is an action that is executed by a node in the scene.
 Actions are most often used to change the structure and content of the node to
 which they are attached, but can also make other changes to the scene. When
 the scene processes its nodes, actions associated with those nodes are evaluated.
 */

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT @interface SKAction : NSObject <NSCopying, NSSecureCoding>

/** The duration required to complete an action, in seconds. */
@property (nonatomic) NSTimeInterval duration;

/** The timing mode used to execute an action
 @see SKActionTimingMode
 */
@property (nonatomic) SKActionTimingMode timingMode;

/** When set, prodives a custom timing via a block. Applies after
 the 'timingMode' property is taken into account, defaults to nil
 @see SKActionTimingFunction
 */
@property (nonatomic) SKActionTimingFunction timingFunction API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** A speed factor that modifies how fast an action runs. Default value is 1.0 */
@property (nonatomic) CGFloat speed;

/** Creates an action that reverses the behavior of another action
 
 @return This method always returns an action object; however, not all actions
 are reversible
 */
- (SKAction *)reversedAction;

@end

@interface SKAction (SKActions)

/** Creates an action that moves a node relative to its current position
 @param delta A vector that describes the change to apply to the node’s position
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)moveBy:(CGVector)delta duration:(NSTimeInterval)duration;
+ (SKAction *)moveByX:(CGFloat)deltaX y:(CGFloat)deltaY duration:(NSTimeInterval)duration;

/** Creates an action that moves a node to a new position
 @param location The coordinates for the node’s new position
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)moveTo:(CGPoint)location duration:(NSTimeInterval)duration;
+ (SKAction *)moveToX:(CGFloat)x duration:(NSTimeInterval)duration;
+ (SKAction *)moveToY:(CGFloat)y duration:(NSTimeInterval)duration;

/** Creates an action that rotates the node by a relative value
 @param radians The amount to rotate the node, in radians
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)rotateByAngle:(CGFloat)radians duration:(NSTimeInterval)duration;

/** Creates an action that rotates the node counterclockwise to an absolute angle
 @param radians The angle to rotate the node to, in radians
 @param duration The duration of the animation
 */
+ (SKAction *)rotateToAngle:(CGFloat)radians duration:(NSTimeInterval)duration;

/** Creates an action that rotates the node to an absolute value
 @param radians The angle to rotate the node to, in radians
 @param duration The duration of the animation, in seconds
 @param shortestUnitArc If YES, then the rotation is performed in whichever
 direction results in the smallest rotation. If NO, then the rotation
 is interpolated
 */
+ (SKAction *)rotateToAngle:(CGFloat)radians duration:(NSTimeInterval)duration shortestUnitArc:(BOOL)shortestUnitArc;

/** Creates an action that adjusts the size of a sprite
 @param width The amount to add to the sprite’s width
 @param height The amount to add to the sprite’s height
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)resizeByWidth:(CGFloat)width height:(CGFloat)height duration:(NSTimeInterval)duration;

/** Creates an action that changes the width and height of a sprite to a new absolute value
 @param width The new width of the sprite
 @param height The new height of the sprite
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)resizeToWidth:(CGFloat)width height:(CGFloat)height duration:(NSTimeInterval)duration;
+ (SKAction *)resizeToWidth:(CGFloat)width duration:(NSTimeInterval)duration;
+ (SKAction *)resizeToHeight:(CGFloat)height duration:(NSTimeInterval)duration;

/** Creates an action that changes the x and y scale values of a node by a relative value
 @param scale The amount to modify to the node’s x and y scale values
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)scaleBy:(CGFloat)scale duration:(NSTimeInterval)duration;
+ (SKAction *)scaleXBy:(CGFloat)xScale y:(CGFloat)yScale duration:(NSTimeInterval)duration;

/** Creates an action that changes the x and y scale values of a node by a relative value
 @param scale The new value for the node’s x and y scale values
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)scaleTo:(CGFloat)scale duration:(NSTimeInterval)duration;
+ (SKAction *)scaleXTo:(CGFloat)xScale y:(CGFloat)yScale duration:(NSTimeInterval)duration;
+ (SKAction *)scaleXTo:(CGFloat)scale duration:(NSTimeInterval)duration;
+ (SKAction *)scaleYTo:(CGFloat)scale duration:(NSTimeInterval)duration;

/**
 Adjust the sprite's xScale & yScale to achieve the desired size (in parent's coordinate space)
 @param duration The duration of the animation, in seconds
*/
+ (SKAction *)scaleToSize:(CGSize)size duration:(NSTimeInterval)duration API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

/** Creates an action that runs a collection of actions sequentially
 @param actions An array of SKAction objects
 
 @discussion When the action executes, the first action in the sequence starts
 and runs to completion. Subsequent actions in the sequence run in a
 similar fashion until all of the actions in the sequence have executed.
 The duration of the sequence action is the sum of the durations of the
 actions in the sequence.
 
 This action is reversible; it creates a new sequence action that reverses
 the order of the actions. Each action in the reversed sequence is itself
 reversed. For example, if an action sequence is {1,2,3}, the reversed
 sequence would be {3R,2R,1R}.
 */
+ (SKAction *)sequence:(NSArray<SKAction*> *)actions;

/** Creates an action that runs a collection of actions concurrently
 @param actions An array of SKAction objects
 
 @discussion When the action executes, the actions that comprise the group
 all start immediately and run in parallel. The duration of the group
 action is the longest duration among the collection of actions. If an
 action in the group has a duration less than the group’s duration, the
 action completes, then idles until the group completes the remaining
 actions. This matters most when creating a repeating action that repeats
 a group.
 */
+ (SKAction *)group:(NSArray<SKAction*> *)actions;

/** Creates an action that repeats another action a specified number of times
 @param action The action to execute
 @param count The number of times to execute the action
 */
+ (SKAction *)repeatAction:(SKAction *)action count:(NSUInteger)count;

/** Creates an action that repeats forever
 @param action The action to execute
 */
+ (SKAction *)repeatActionForever:(SKAction *)action;

/** Creates an action that changes the alpha value of the node to 1.0
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)fadeInWithDuration:(NSTimeInterval)duration;

/** Creates an action that changes the alpha value of the node to 0.0
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)fadeOutWithDuration:(NSTimeInterval)duration;

/** Creates an action that adjusts the alpha value of a node by a relative value
 @param factor The amount to modify the node’s alpha value
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)fadeAlphaBy:(CGFloat)factor duration:(NSTimeInterval)duration;

/** Creates an action that adjusts the alpha value of a node to a new value
 @param alpha The new value of the node’s alpha
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)fadeAlphaTo:(CGFloat)alpha duration:(NSTimeInterval)duration;

/** Creates an action that hides a node */
+ (SKAction *)hide API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that unhides a node */
+ (SKAction *)unhide API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that changes a sprite’s texture
 @param texture The new texture to use on the sprite
 */
+ (SKAction *)setTexture:(SKTexture *)texture API_AVAILABLE(ios(7.1), tvos(7.1), watchos(1.0), macos(10.10));
+ (SKAction *)setNormalTexture:(SKTexture *)texture API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));;

/** Creates an action that changes a sprite’s texture, possibly resizing the sprite
 @param texture The new texture to use on the sprite
 @param resize If YES, the sprite is resized to match the new texture.
 If NO, the size of the sprite is unchanged.
 */
+ (SKAction *)setTexture:(SKTexture *)texture resize:(BOOL)resize API_AVAILABLE(ios(7.1), tvos(7.1), watchos(1.0), macos(10.10));
+ (SKAction *)setNormalTexture:(SKTexture *)texture resize:(BOOL)resize API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/** Creates an action that animates changes to a sprite’s texture
 @param textures An array of textures to use when animating a sprite
 @param sec The amount of time that each texture is displayed
 */
+ (SKAction *)animateWithTextures:(NSArray<SKTexture*> *)textures timePerFrame:(NSTimeInterval)sec;
+ (SKAction *)animateWithNormalTextures:(NSArray<SKTexture*> *)textures timePerFrame:(NSTimeInterval)sec API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/** Creates an action that animates changes to a sprite’s texture
 @param textures An array of textures to use when animating a sprite
 @param sec The amount of time that each texture is displayed
 @param resize If YES, the sprite is resized to match each new texture.
 If NO, the size of the sprite remains at a constant size.
 @param restore If YES, When the action completes, the sprite’s texture is restored
 to the texture it had before the action completed. (If the
 resize parameter is YES, the sprite is resized to match the
 size of the original texture.
 If NO, when the action completes the sprite’s texture remains
 set to the final texture in the array.
 */
+ (SKAction *)animateWithTextures:(NSArray<SKTexture*> *)textures timePerFrame:(NSTimeInterval)sec resize:(BOOL)resize restore:(BOOL)restore;
+ (SKAction *)animateWithNormalTextures:(NSArray<SKTexture*> *)textures timePerFrame:(NSTimeInterval)sec resize:(BOOL)resize restore:(BOOL)restore API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/** Creates an action that plays a sound
 @param soundFile The name of a sound file in the app’s bundle
 @param wait If YES, then the duration of this action is the same
 as the length of the audio playback. If NO, the action is considered
 to have completed immediately.
 
 @discussion The file name must be the name or path of a file of a platform
 supported audio file format. Use a LinearPCM format audio file with 8 or 16 bits
 per channel for best performance */
+ (SKAction *)playSoundFileNamed:(NSString*)soundFile waitForCompletion:(BOOL)wait;

/** Creates an animation that animates a sprite’s color and blend factor
 @param color The new color for the sprite
 @param colorBlendFactor The new blend factor for the sprite
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)colorizeWithColor:(SKColor *)color colorBlendFactor:(CGFloat)colorBlendFactor duration:(NSTimeInterval)duration;
+ (SKAction *)colorizeWithColorBlendFactor:(CGFloat)colorBlendFactor duration:(NSTimeInterval)sec;

/** Creates an action that sets the falloff of a field
 @param falloff The new value for falloff
 @param duration The duration of the animation, in seconds
 @see SKFieldNode
 */
+ (SKAction *)falloffTo:(float)falloff duration:(NSTimeInterval)duration API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that sets the falloff of a field
 @param falloff The value to modify falloff by
 @param duration The duration of the animation, in seconds
 @see SKFieldNode
 */
+ (SKAction *)falloffBy:(float)falloff duration:(NSTimeInterval)duration API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));


/** Creates an action that moves the node along a relative path, orienting the
 node to the path
 
 @param path A Core Graphics path whose coordinates are relative to the node’s
 current position
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)followPath:(CGPathRef)path duration:(NSTimeInterval)duration;

/** Creates an action that moves the node along a path
 
 @param path A Core Graphics path whose coordinates are relative to the node’s
 current position
 @param offset If YES, the points in the path are relative offsets to the
 node’s starting position. If NO, the points in the node are absolute
 coordinate values.
 @param orient If YES, the node’s zRotation property animates so that
 the node turns to follow the path. If NO, the zRotation property of
 the node is unchanged.
 @param duration The duration of the animation
 */
+ (SKAction *)followPath:(CGPathRef)path asOffset:(BOOL)offset orientToPath:(BOOL)orient duration:(NSTimeInterval)duration;

/** Creates an action that moves the node along a relative path, orienting the
 node to the path
 
 @param path A Core Graphics path whose coordinates are relative to the node’s
 current position
 @param speed The speed in pixels per second to move along the path
 */
+ (SKAction *)followPath:(CGPathRef)path speed:(CGFloat)speed;
+ (SKAction *)followPath:(CGPathRef)path asOffset:(BOOL)offset orientToPath:(BOOL)orient speed:(CGFloat)speed;

/** Creates an action that changes how fast the node executes actions by a
 relative value
 @param speed amount to modify the speed by
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)speedBy:(CGFloat)speed duration:(NSTimeInterval)duration;

/** Creates an action that changes how fast the node executes actions
 @param speed The new value for the node’s speed
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)speedTo:(CGFloat)speed duration:(NSTimeInterval)duration;

/** Creates an action that performs an inverse kinematic reach.
 This action must be run on a descendent of the rootNode for animation to occur.
 Running this action on the rootNode itself will not cause any animation to occur.
 @param position The position (in screen space) to reach for
 @param root Where to start the inverse kinematic operation from
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)reachTo:(CGPoint)position rootNode:(SKNode *)root duration:(NSTimeInterval)duration API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that performs an inverse kinematic reach.
 This action must be run on a descendent of the rootNode for animation to occur.
 Running this action on the rootNode itself will not cause any animation to occur.
 @param position The position (in screen space) to reach for
 @param root Where to start the inverse kinematic operation from
 @param velocity The speed in points per second of the end node in the chain
 */
+ (SKAction *)reachTo:(CGPoint)position rootNode:(SKNode *)root velocity:(CGFloat)velocity API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that performs an inverse kinematic reach.
 This action must be run on a descendent of the rootNode for animation to occur.
 Running this action on the rootNode itself will not cause any animation to occur.
 @param node The node to reach for
 @param root Where to start the inverse kinematic operation from
 @param sec The duration of the animation, in seconds
 */
+ (SKAction *)reachToNode:(SKNode *)node rootNode:(SKNode *)root duration:(NSTimeInterval)sec API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that performs an inverse kinematic reach.
 This action must be run on a descendent of the rootNode for animation to occur.
 Running this action on the rootNode itself will not cause any animation to occur.
 @param node The node to reach for
 @param root Where to start the inverse kinematic operation from
 @param velocity The speed in points per second of the end node in the chain
 */
+ (SKAction *)reachToNode:(SKNode *)node rootNode:(SKNode *)root velocity:(CGFloat)velocity API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that sets the strength of a field
 @param strength The new value for strength
 @param duration The duration of the animation, in seconds
 @see SKFieldNode
 */
+ (SKAction *)strengthTo:(float)strength duration:(NSTimeInterval)duration API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that sets the strength of a field
 @param strength The value to modify strength by
 @param duration The duration of the animation, in seconds
 @see SKFieldNode
 */
+ (SKAction *)strengthBy:(float)strength duration:(NSTimeInterval)duration API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that idles for a specified period of time
 @param duration The duration of the idle, in seconds
 */
+ (SKAction *)waitForDuration:(NSTimeInterval)duration;

/** Creates an action that idles for a randomized period of time
 @param duration The duration of the idle, in seconds
 @param durationRange The range of possible values for the duration
 */
+ (SKAction *)waitForDuration:(NSTimeInterval)duration withRange:(NSTimeInterval)durationRange;

/** Creates an action that removes the node from its parent */
+ (SKAction *)removeFromParent;

/** Creates an action that calls a method on an object
 @param selector The selector of the method to call
 @param target The target object
 */
+ (SKAction *)performSelector:(SEL)selector onTarget:(id)target;

/** Creates an action that executes a block
 @param block The block to run
 */
+ (SKAction *)runBlock:(dispatch_block_t)block;

/** Creates an action that executes a block
 @param block The block to run
 @param queue The queue to perform the action on
 */
+ (SKAction *)runBlock:(dispatch_block_t)block queue:(dispatch_queue_t)queue;

/** Creates an action that runs an action on a named child object
 @param action the action to run
 @param name the name of a child object
 @see SKNode.name
 */
+ (SKAction *)runAction:(SKAction *)action onChildWithName:(NSString*)name;

/** Creates an action that executes a block over a duration
 @param duration The duration of the animation, in seconds
 @param block The block to run. The block takes the following parameters:
 node The node on which the action is running.
 elapsedTime The amount of time that has passed in the animation.
 */
+ (SKAction *)customActionWithDuration:(NSTimeInterval)duration actionBlock:(void (^)(SKNode *node, CGFloat elapsedTime))block;

/** Creates an action of the given name from an action file.
 @param name The name of the action
 */
+ (nullable SKAction *)actionNamed:(NSString *)name API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/** Creates an action of the given name from an action file with a new duration.
 @param name The name of the action
 @param duration The duration of the action
 */
+ (nullable SKAction *)actionNamed:(NSString *)name duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/** Creates an action of the given name from an action file.
 @param name The name of the action
 @param url The url of the file containing the action
 */
+ (nullable SKAction *)actionNamed:(NSString *)name fromURL:(NSURL *)url API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/** Creates an action of the given name from an action file with a new duration.
 @param name The name of the action
 @param url The url of the file containing the action
 @param duration The duration of the action
 */
+ (nullable SKAction *)actionNamed:(NSString *)name fromURL:(NSURL *)url duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

@end

@interface SKAction (NodeWithPhysicsBody)

+ (SKAction *)changeChargeTo:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)changeChargeBy:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)changeMassTo:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)changeMassBy:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)applyForce:(CGVector)force duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));;
+ (SKAction *)applyForce:(CGVector)force atPoint:(CGPoint)point duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)applyTorque:(CGFloat)torque duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)applyImpulse:(CGVector)impulse duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)applyImpulse:(CGVector)impulse atPoint:(CGPoint)point duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)applyAngularImpulse:(CGFloat)impulse duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));;

@end

@interface SKAction (PlaybackControl)

+ (SKAction *)play API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)pause API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)stop API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)changePlaybackRateTo:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));;
+ (SKAction *)changePlaybackRateBy:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));;

@end

@interface SKAction (MixerControl)

+ (SKAction *)changeVolumeTo:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));;
+ (SKAction *)changeVolumeBy:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKVersion.h
#define SK_VERSION 25001000
// ==========  SpriteKit.framework/Headers/SKConstraint.h
/**
 @header
 
 Constraints are used to apply restrictions to Node attributes.
 They are evaluated each frame after actions and physics.
 
 @copyright 2013 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SpriteKitBase.h>
#import <SpriteKit/SKNode.h>

NS_ASSUME_NONNULL_BEGIN

/**
 SKRange object used to define a range of allowable values 
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
SK_EXPORT @interface SKRange : NSObject <NSSecureCoding, NSCopying>

/* SKRange with a lower and upper limit. Designated initializer. */
- (instancetype)initWithLowerLimit:(CGFloat)lower upperLimit:(CGFloat)upper NS_DESIGNATED_INITIALIZER;



/* SKRange with a lower and upper limit */
+ (instancetype)rangeWithLowerLimit:(CGFloat)lower upperLimit:(CGFloat)upper;

/* SKRange with only a lower limit */
+ (instancetype)rangeWithLowerLimit:(CGFloat)lower;

/* SKRange with only a upper limit */
+ (instancetype)rangeWithUpperLimit:(CGFloat)upper;

/* SKRange representing a single value */
+ (instancetype)rangeWithConstantValue:(CGFloat)value;

/* SKRange representing a variance about a value */
+ (instancetype)rangeWithValue:(CGFloat)value variance:(CGFloat)variance;

/* SKRange with no upper or lower limit */
+ (instancetype)rangeWithNoLimits;



/* The lower limit, -1.0 * CGFLOAT_MAX means no limit */
@property CGFloat lowerLimit;

/* The upper limit, +1.0 * CGFLOAT_MAX means no limit */
@property CGFloat upperLimit;

@end




/**
 SKConstraints are evaluated each frame after actions and physics.
 The node's transform will be changed to staisfy the constarint
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
SK_EXPORT @interface SKConstraint : NSObject <NSSecureCoding, NSCopying>

/* Wether the constraint should apply. Defualts to YES */
@property BOOL enabled;

/* Reference node to transform the values to before apply the constraint limits. Defaults to nil (no transfrom). */
@property (retain, nonatomic, nullable) SKNode *referenceNode;

/**
 Constrain the node's position to a range
 */
+ (instancetype)positionX:(SKRange *)range;
+ (instancetype)positionY:(SKRange *)range;
+ (instancetype)positionX:(SKRange *)xRange Y:(SKRange *)yRange;

/**
 Constrain the node's position to be within a distance of a point or node
 */
+ (instancetype)distance:(SKRange *)range toNode:(SKNode *)node;
+ (instancetype)distance:(SKRange *)range toPoint:(CGPoint)point;
+ (instancetype)distance:(SKRange *)range toPoint:(CGPoint)point inNode:(SKNode *)node;

/**
 Constrain the node's rotation to a range
 */
+ (instancetype)zRotation:(SKRange *)zRange;

/**
 Constrain the node's rotation to orient to a point or node
 */
+ (instancetype)orientToNode:(SKNode *)node offset:(SKRange *)radians;
+ (instancetype)orientToPoint:(CGPoint)point offset:(SKRange *)radians;
+ (instancetype)orientToPoint:(CGPoint)point inNode:(SKNode *)node offset:(SKRange *)radians;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKEmitterNode.h
/**
 @header
 
 
 Particle Emitter Node
 
 
 @copyright 2011 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SKSpriteNode.h>
#import <SpriteKit/SKKeyframeSequence.h>
#import <SpriteKit/SpriteKitBase.h>
#import <SpriteKit/SKShader.h>

typedef NS_ENUM(NSUInteger, SKParticleRenderOrder) {
    SKParticleRenderOrderOldestLast,
    SKParticleRenderOrderOldestFirst,
    SKParticleRenderOrderDontCare,
} NS_ENUM_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_BEGIN

/**
 An emitter of particle sprites.
 */
SK_EXPORT @interface SKEmitterNode : SKNode

/**
 The particle simulation is stepped automatically each frame when present in the scene. This allows the user to manually advance the simulation by a fixed amount of time. Useful for pre-populating particles before adding them to the scene.
 */

- (void)advanceSimulationTime:(NSTimeInterval)sec;

/* Removes all particles and restarts the emitter */
- (void)resetSimulation;

/**
 The texture to be used for the particles.
 */
@property (nonatomic, retain, nullable) SKTexture *particleTexture;


/**
 The blend mode for each particle. Defaults to SKBlendModeAlpha.
 */
@property (nonatomic) SKBlendMode particleBlendMode;

/**
 The starting color for each particle. Defaults to clear.
 */
@property (nonatomic, retain) SKColor *particleColor;

/**
 The random variance about each color component for each particle. Defaults to 0.0.
 */
@property (nonatomic) CGFloat particleColorRedRange;
@property (nonatomic) CGFloat particleColorGreenRange;
@property (nonatomic) CGFloat particleColorBlueRange;
@property (nonatomic) CGFloat particleColorAlphaRange;

/**
 The rate at which to modify each color component for each particle (per second).
 */
@property (nonatomic) CGFloat particleColorRedSpeed;
@property (nonatomic) CGFloat particleColorGreenSpeed;
@property (nonatomic) CGFloat particleColorBlueSpeed;
@property (nonatomic) CGFloat particleColorAlphaSpeed;

@property (nonatomic, retain, nullable) SKKeyframeSequence *particleColorSequence;

/**
 The starting color blend for each particle. Behaves the same as SKSpriteNode. Defaults to 0.0.
 */
@property (nonatomic) CGFloat particleColorBlendFactor;

/**
 The random variance about the starting color blend for each particle. Defaults to 0.0.
 */
@property (nonatomic) CGFloat particleColorBlendFactorRange;

/**
 The rate at which to modify the color blend for each particle. Defaults to 0.0.
 */
@property (nonatomic) CGFloat particleColorBlendFactorSpeed;

@property (nonatomic, retain, nullable) SKKeyframeSequence *particleColorBlendFactorSequence;

/**
 The starting position for each particle in the emitter's coordinate space. Defaults to (0.0, 0,0).
 */
@property (nonatomic) CGPoint particlePosition;

/**
 The random variance about the starting position for each particle in the emitter's coordinate space. Defaults to (0.0, 0,0).
 */
@property (nonatomic) CGVector particlePositionRange;


/**
 The starting speed for each particle along its emission vector. Defaults to 0.0.
 */
@property (nonatomic) CGFloat particleSpeed;

/**
 The random variance about the starting speed for each particle along its emission vector. Defaults to 0.0.
 */
@property (nonatomic) CGFloat particleSpeedRange;

/**
 The angle at which to emit each new particle, in radians. Defaults to 0.0.
 */
@property (nonatomic) CGFloat emissionAngle;

/**
 The random variance about the angle at which to emit each new particle, in radians. Defaults to 0.0.
 */
@property (nonatomic) CGFloat emissionAngleRange;

/**
 The acceleration to apply to each particles velocity. Useful for simulating effects such as wind or gravity. Defaults to 0.0.
 */
@property (nonatomic) CGFloat xAcceleration;
@property (nonatomic) CGFloat yAcceleration;


/**
 The rate at which new particles are generated, in particles per second. Defaults to 0.0.
 */
@property (nonatomic) CGFloat particleBirthRate;


/**
 The number of particles that will be emitted. If set to 0, there is no limit. Defaults to 0.
 */
@property (nonatomic) NSUInteger numParticlesToEmit;

/**
 The lifetime of each particle, in seconds. Defaults to 0.0.
 */
@property (nonatomic) CGFloat particleLifetime;

/**
 The random variance about the lifetime of each particle, in seconds. Defaults to 0.0.
 */
@property (nonatomic) CGFloat particleLifetimeRange;


/**
 The starting z-rotation for each particle. Defaults to 0.0.
 */
@property (nonatomic) CGFloat particleRotation;

/**
 The random variance about the starting z-rotation for each particle. Defaults to 0.0.
 */
@property (nonatomic) CGFloat particleRotationRange;

/**
 The rate at which to modify the z-rotation for each particle. Defaults to 0.0.
 */
@property (nonatomic) CGFloat particleRotationSpeed;

/**
 The starting size for each particle. If set to CGSizeZero (the default) the particles will start at the size of the texture assigned to particleTexture. Note that particleScale and particleScaleRange will also have an effect on the effective size of each new particle.
 */
@property (nonatomic) CGSize particleSize;

/**
 The starting scale for each particle. Defaults to 1.0.
 */
@property (nonatomic) CGFloat particleScale;

/**
 The random variance about the starting scale for each particle. Defaults to 0.0.
 */
@property (nonatomic) CGFloat particleScaleRange;

/**
 The rate at which to modify the scale for each particle. Defaults to 0.0.
 */
@property (nonatomic) CGFloat particleScaleSpeed;

@property (nonatomic, retain, nullable) SKKeyframeSequence *particleScaleSequence;

/**
 The starting alpha for each particle. Defaults to 1.0.
 */
@property (nonatomic) CGFloat particleAlpha;

/**
 The random variance about the starting alpha for each particle. Defaults to 1.0.
 */
@property (nonatomic) CGFloat particleAlphaRange;

/**
 The rate at which to modify the alpha for each particle. Defaults to 1.0.
 */
@property (nonatomic) CGFloat particleAlphaSpeed;

@property (nonatomic, retain, nullable) SKKeyframeSequence *particleAlphaSequence;

/**
 Specifies an action executed by new particles.
 */
@property (nonatomic, copy, nullable) SKAction *particleAction;

/**
 Defines what logical 'categories' of fields this particles emitted respond to. Defaults to all bits set (all categories).
 Can be forced off via affectedByGravity.
 */
@property (nonatomic, assign) uint32_t fieldBitMask;

/**
 Normally the particles are rendered as if they were a child of the SKEmitterNode, they can also be rendered as if they were a child of any other node in the scene by setting the targetNode property. Defaults to nil (standard behavior).
 */
@property (nonatomic, weak, nullable) SKNode *targetNode;

@property (nonatomic, retain, nullable) SKShader *shader;

/**
 Optional dictionary of SKAttributeValues
 Attributes can be used with custom SKShaders.
 */
@property (nonatomic, nonnull, copy) NSDictionary<NSString *, SKAttributeValue *> *attributeValues API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

- (nullable SKAttributeValue*)valueForAttributeNamed:(nonnull NSString *)key API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
- (void)setValue:(SKAttributeValue*)value forAttributeNamed:(nonnull NSString *)key NS_SWIFT_NAME(setValue(_:forAttribute:)) API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));


/**
 The starting z-position for each particle. Defaults to 0.0.
 */
@property (nonatomic) CGFloat particleZPosition;

/**
 The order in which particles will be rendered. Defaults to SKParticleRenderOrderOldestLast.
 */
@property (nonatomic) SKParticleRenderOrder particleRenderOrder API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));


/**
 The random variance about the starting z-position for each particle. Defaults to 0.0.
 */
@property (nonatomic) CGFloat particleZPositionRange NS_DEPRECATED(10_8, 10_10, 7_0, 8_0);

/**
 The rate at which to modify the z-position for each particle. Defaults to 0.0.
 */
@property (nonatomic) CGFloat particleZPositionSpeed NS_DEPRECATED(10_8, 10_10, 7_0, 8_0);



@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SpriteKitBase.h
//
//  SpriteKitBase.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//
#ifndef PHYSICSKIT_MINUS_GL_IMPORTS
#define PHYSICSKIT_MINUS_GL_IMPORTS 1
#endif

#import <Availability.h>
#import <TargetConditionals.h>
#import <CoreGraphics/CGGeometry.h>
#import <Foundation/Foundation.h>

#import <SpriteKit/SKVersion.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif


#if TARGET_OS_IPHONE && !__has_include(<UIKit/UIView.h>)
#define SKVIEW_AVAILABLE 0
#else
#define SKVIEW_AVAILABLE 1
#endif

#ifdef __cplusplus
#define SK_EXPORT extern "C" __attribute__((visibility ("default")))
#else
#define SK_EXPORT extern __attribute__((visibility ("default")))
#endif
#define SK_AVAILABLE __OSX_AVAILABLE_STARTING
#define SK_WEAK_LINK __attribute__((weak_import))

#if TARGET_OS_IPHONE
#define SKColor UIColor
#else
#define SKColor NSColor
#endif

typedef float vector_float3 __attribute__((__ext_vector_type__(3)));

#ifndef CGVECTOR_DEFINED
#define CGVECTOR_DEFINED 1
struct CGVector {
    CGFloat dx;
    CGFloat dy;
};

typedef struct CGVector CGVector;

CG_INLINE CGVector CGVectorMake(CGFloat dx, CGFloat dy) {
    CGVector vector; vector.dx = dx; vector.dy = dy; return vector;
}
#endif

// ==========  SpriteKit.framework/Headers/SKReferenceNode.h
/**
 @header
 
 Node that references an external serialized node graph
 
 @copyright 2015 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SpriteKit.h>
@class SKReferenceNode;

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11)) @interface SKReferenceNode : SKNode

/** Create a reference node with a url */
- (instancetype)initWithURL:(nullable NSURL *)url NS_DESIGNATED_INITIALIZER;

/** Create a reference node with a url */
- (instancetype)initWithFileNamed:(nullable NSString *)fileName NS_DESIGNATED_INITIALIZER;

/**
 Support coding and decoding via NSKeyedArchiver.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;


/** Create a reference node with a url */
+ (instancetype)referenceNodeWithFileNamed:(NSString *)fileName;

/** Create a reference node with a url */
+ (instancetype)referenceNodeWithURL:(NSURL *)referenceURL;


/** called each time the url is loaded, after it has been added as a child */
- (void)didLoadReferenceNode:(nullable SKNode *)node;

/** Force the reference to be reloaded. The resolved node will added
 as a child of this node. If the resolved node has not yet been loaded,
 it will be automatically loaded when the resolved node is queryed or
 the refenece node is rendered. */
- (void)resolveReferenceNode;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKShader.h
/**
 @header
 
 SKShader defines the custom fragment shader which can be set on a supported Sprite Kit node.
 
 @copyright 2013 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SpriteKitBase.h>
@class SKUniform, SKAttribute;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_10, 8_0)
SK_EXPORT @interface SKShader : NSObject <NSCopying, NSSecureCoding>

/**
 Create a custom shader with source code.
 
 @param source the source code for the custom fragment shader.
 */
- (instancetype)initWithSource:(NSString *)source;

/**
 Create a custom shader with source code and uniforms.
 
 @param source the source code for the custom fragment shader.
 @param uniforms the array of uniforms supplied to this shader
 */
- (instancetype)initWithSource:(NSString *)source uniforms:(NSArray<SKUniform*> *)uniforms;

+ (instancetype)shader;
+ (instancetype)shaderWithSource:(NSString *)source;
+ (instancetype)shaderWithSource:(NSString *)source uniforms:(NSArray<SKUniform*> *)uniforms;

/**
 Loads a shader source file named 'name' from the main bundle. This is simpler yet functionally equivalent to the following code
 
 [SKShader shaderWithSource:[NSString stringWithContentsOfFile:[[NSBundle mainBundle] pathForResource:name ofType:@"fsh"]
                   encoding:NSUTF8StringEncoding
                      error:NULL]];
 
 The encoding is assumed to be NSUTF8StringEncoding.
 */
+ (instancetype)shaderWithFileNamed:(NSString *)name;

/**
 Shader source must define the 'main' method of the fragment shader
 
 Your shader must assign a premultipled fragment value to 'gl_FragColor'
 
 The following implicit uniforms are available:
 
    1. sampler2D u_texture  (the primary texuture attached the the sprite)
 
 The following varyings are available:
 
    1. vec2 v_tex_coord  (normalized texture coordiantes for the primary texture)
    2. vec4 v_color_mix  (premultiplied color value based on color & alpha)
 
 
 The following functions are available:
 
    1. vec4 SKDefaultShading()  (returns the fragment value that would have been output if no shader was used)
 
 
 
 Sample shader source that produces the same result are SpriteKit's normal rendering:
 
 "void main() { gl_FragColor = SKDefaultShading(); }"
 
 */

@property (copy, nullable) NSString *source;


/**
 You may define additional uniforms to be used in your shader here.
 There is no need to declare them in you source, just use them by name.
 
 All uniforms declared must be used within the source.
 */
@property (copy) NSArray<SKUniform*> *uniforms;

- (void)addUniform:(SKUniform *)uniform;
- (nullable SKUniform *)uniformNamed:(NSString *)name;
- (void)removeUniformNamed:(NSString *)name;

@property (nonatomic, copy, nonnull) NSArray<SKAttribute*> *attributes API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKLightNode.h
/**
 @header
 
 Light Nodes are used to light or shadow a scene.
 
 @copyright 2013 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SKSpriteNode.h>
#import <SpriteKit/SpriteKitBase.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10)) @interface SKLightNode : SKNode

/**
 Enables or disables lighting contribution from this light node.
 
 Set to YES; sprites using this light will be lit with the ambient color and
 the light color, with a falloff in intensity according to the falloff property.
 
 Set to NO; this light does not contribute any lighting.
 
 If no lights are active on a sprite it will be drawn normally, as if not lit.
 
 The default value is YES.
 
 @see lightColor
 @see falloff
 @see categoryBitMask
 */
@property (nonatomic, getter = isEnabled) BOOL enabled;

/**
 Diffuse and Specular color of the light source, defaults to opaque white.
 
 The alpha component of the color is ignored.
 
 If using shaders bind a uniform to this property to use scene based custom lighting.
 
 @see SKUniform
 @see falloff
 */
@property (nonatomic) SKColor *lightColor;

/**
 Ambient color of the light source, defaults to black.
 
 If you had only a single light in the scene with an ambient color
 of opaque white and a light color of black,
 it would appear as if the scene was rendered without lighting.
 
 The alpha component of the color is ignored. The color is not
 affected by falloff or surface normals.
 
 @see lightColor
 */
@property (nonatomic) SKColor *ambientColor;

/**
 Color of the shadow casted on occluded objects, defaults to half opacity black.
 
 The alpha component of the color is used for blending with the regions that are in shadow.
 
 @see SKSpriteNode.shadowCastBitMask
 @see SKSpriteNode.shadowedBitMask
 */
@property (nonatomic) SKColor *shadowColor;

/**
 Falloff in intensity of the light over distance, defaults to 1.
 The falloff does not affect the ambient color nor the shadow color.
 
 @see lightColor
 */
@property (nonatomic) CGFloat falloff;

/**
 The category of the light, which determines the group(s) a light belongs to.
 Any node that has its corresponding light and shadow bitmasks set to an overlapping value
 will be lit, shadow casting or shadowed by this light.

 @see SKSpriteNode.lightingBitMask
 @see SKSpriteNode.shadowCastBitMask
 @see SKSpriteNode.shadowedBitMask
 */
@property (nonatomic) uint32_t categoryBitMask;


@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKShapeNode.h
/**
 @header
 
 
 Shape Nodes are used to stroke or fill a CGPath
 

 @copyright 2011 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SKNode.h>
#import <SpriteKit/SKShader.h>
#import <SpriteKit/SpriteKitBase.h>


NS_ASSUME_NONNULL_BEGIN

/**
 A SpriteKit Node used to stroke or fill a shape. CGPaths are used to supply the path.
 
 See CGPath <a href="http://developer.apple.com/library/mac/#documentation/GraphicsImaging/Reference/CGPath/Reference/reference.html">reference pages</a> for details on how to construct a CGPath.
 */
SK_EXPORT @interface SKShapeNode : SKNode

/* Create a Shape Node using a CGPathRef, optionally centered at the Node's origin. */
+ (instancetype)shapeNodeWithPath:(CGPathRef)path API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));
+ (instancetype)shapeNodeWithPath:(CGPathRef)path centered:(BOOL)centered API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/* Create a Shape Node representing a Rect. */
+ (instancetype)shapeNodeWithRect:(CGRect)rect API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/* Create a Shape Node representing a rect centered at the Node's origin. */
+ (instancetype)shapeNodeWithRectOfSize:(CGSize)size API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));


/* Create a Shape Node representing a rounded rect with a corner radius */
+ (instancetype)shapeNodeWithRect:(CGRect)rect cornerRadius:(CGFloat)cornerRadius API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/* Create a Shape Node representing a rounded rect with a corner radius centered at the Node's origin. */
+ (instancetype)shapeNodeWithRectOfSize:(CGSize)size cornerRadius:(CGFloat)cornerRadius API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));


/* Create a Shape Node representing an circle centered at the Node's origin. */
+ (instancetype)shapeNodeWithCircleOfRadius:(CGFloat)radius API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));


/* Create a Shape Node representing an Ellipse inscribed within a Rect */
+ (instancetype)shapeNodeWithEllipseInRect:(CGRect)rect API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/* Create a Shape Node representing an Ellipse inscribed within a Rect centered at the Node's origin. */
+ (instancetype)shapeNodeWithEllipseOfSize:(CGSize)size API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));


/* Create a Shape Node representing an a series of Points interpreted as line segments */
+ (instancetype)shapeNodeWithPoints:(CGPoint *)points count:(size_t)numPoints API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/* Create a Shape Node representing a smoothed spline that passes through a series of Points */
+ (instancetype)shapeNodeWithSplinePoints:(CGPoint *)points count:(size_t)numPoints API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/**
 The CGPath to be drawn (in the Node's coordinate space)
 */
@property (nonatomic, nullable) CGPathRef path;

/**
 The color to draw the path with. (for no stroke use [SKColor clearColor]). Defaults to [SKColor whiteColor].
 */
@property (nonatomic, retain) SKColor *strokeColor;

/**
 The color to fill the path with. Defaults to [SKColor clearColor] (no fill).
 */
@property (nonatomic, retain) SKColor *fillColor;

/**
 Sets the blend mode to use when composing the shape with the final framebuffer.
 @see SKNode.SKBlendMode
 */
@property (nonatomic) SKBlendMode blendMode;

/**
 If set to YES, the path stroke edges and caps is smoothed (antialiased) when drawn.
 */
@property (nonatomic, getter = isAntialiased) BOOL antialiased;

/**
 The width used to stroke the path. Widths larger than 2.0 may result in artifacts. Defaults to 1.0.
 */
@property (nonatomic) CGFloat lineWidth;

/**
 Add a glow to the path stroke of the specified width. Defaults to 0.0 (no glow)
 */
@property (nonatomic) CGFloat glowWidth;

/**
 The cap type that should be used when stroking a non-closed path
 */
@property (nonatomic) CGLineCap lineCap;

/**
 The join type that should be used when stroking a path
 */
@property (nonatomic) CGLineJoin lineJoin;

/**
 When a miter join is used, the maximum ratio of miter length to line with to be used
 */
@property (nonatomic) CGFloat miterLimit;

/**
 The length of the node's path if it were to be stroked
 */
@property (nonatomic, readonly) CGFloat lineLength;

/* An optional Texture used for the filling the Shape */
@property (nonatomic, retain, nullable) SKTexture *fillTexture API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/* An optional SKShader used for the filling the Shape */
@property (nonatomic, retain, nullable) SKShader *fillShader API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));


/* An optional Texture used for the Shape's stroke. */
@property (nonatomic, retain, nullable) SKTexture *strokeTexture API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/* An optional SKShader used for the Shape's Stroke. */
@property (nonatomic, retain, nullable) SKShader *strokeShader API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/**
 Optional dictionary of SKAttributeValues
 Attributes can be used with custom SKShaders.
 */
@property (nonatomic, nonnull, copy) NSDictionary<NSString *, SKAttributeValue *> *attributeValues API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

- (nullable SKAttributeValue*)valueForAttributeNamed:(nonnull NSString *)key API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
- (void)setValue:(SKAttributeValue*)value forAttributeNamed:(nonnull NSString *)key NS_SWIFT_NAME(setValue(_:forAttribute:)) API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKReachConstraints.h
/**
 @header
 
 Reach contraints are used to control the degree of freedom when solving using inverse kinematics actions.
 
 @copyright 2013 Apple, Inc. All rights reserved.
 
 */

#import <Foundation/Foundation.h>
#import <SpriteKit/SpriteKitBase.h>

SK_EXPORT API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10)) @interface SKReachConstraints : NSObject <NSSecureCoding>

/**
 Lower angle limit in radians
 */
@property (nonatomic, assign) CGFloat lowerAngleLimit;

/**
 Upper angle limit in radians
 */
@property (nonatomic, assign) CGFloat upperAngleLimit;

- (instancetype)initWithLowerAngleLimit:(CGFloat)lowerAngleLimit upperAngleLimit:(CGFloat)upperAngleLimit NS_DESIGNATED_INITIALIZER;

@end
// ==========  SpriteKit.framework/Headers/SKTextureAtlas.h
//
//  SKTextureAtlas.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpriteKit/SKTexture.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT @interface SKTextureAtlas : NSObject <NSSecureCoding>


/* Atlas with .png and .plist file name*/
+ (instancetype)atlasNamed:(NSString *)name;

/* Create a texture atlas on the fly */
+ (instancetype)atlasWithDictionary:(NSDictionary<NSString*, id> *)properties API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/* Individual texture for image name within the atlas */
- (SKTexture *)textureNamed:(NSString *)name;

/**
 Start a texture atlas preload operation on an array of texture atlas
 
 @param textureAtlases an array of SKTextureAtlas to be preloaded
 @param completionHandler will be called upon the preload completion
 
 */
+ (void)preloadTextureAtlases:(NSArray<SKTextureAtlas*> *)textureAtlases withCompletionHandler:(void(^)(void))completionHandler;

/** 
 Start a texture atlas preload operation on an array of texture atlas identifiers, error == nil if all atlases were found,
 else an NSError is returned and the user info will contain a list of the atlases that couldn't be found
 the ones that could be found are looked up and prefetched.

 @param atlasNames is an array of the SKTextureAtlas, that were located and preloaded.
 @param completionHandler will be called upon the preload completion.
 */
+ (void)preloadTextureAtlasesNamed:(NSArray<NSString *> *)atlasNames withCompletionHandler:(void (^)(NSError * __nullable error, NSArray<SKTextureAtlas *> *foundAtlases))completionHandler API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/**
 Request that this texture atlas be loaded into vram on the next render update, with a callback handler.
 */
- (void)preloadWithCompletionHandler:(void(^)(void))completionHandler;

/* Returns the array of valid textures in the atlas */
@property (nonatomic, readonly) NSArray<NSString*> *textureNames;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKCameraNode.h
/**
 @header
 
 Node that controls camera movement, zoom and rotation.
 
 @copyright 2015 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SKNode.h>

NS_ASSUME_NONNULL_BEGIN

/**A Camera node is a full fledged SKNode that can have actions and physics applied to it.
 * It also uses the standard SKNode transform system so modifying the camera node's position
 * is how you translate the camera's viewport. Applying a scale to the node would zoom
 * the viewport in or out etc. As an added benefit you can now rotate the viewport by
 * applying a zRotation to the camera node, just as you would with any other SKNode.
 *
 * The camera viewport is centered on the camera's position. It uses the scene's frame
 * and scale mode along with the node transforms to determine the size, origin and
 * rotation of the viewport.
 *
 * There are some convenience functions included for testing if nodes are contained
 * within the camera viewport. It can be used to determine if objects are no longer
 * visible on the display.
 *
 * In order to use a camera; set it on the scene that contains the camera.
 * @see SKScene.camera
 */
SK_EXPORT API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11)) @interface SKCameraNode : SKNode

/**Checks if the node is contained inside the viewport of the camera.
 * The camera and node must both be in the same scene and presented on a view in order
 * to determine if the node is inside the camera viewport rectangle.
 *
 * @return YES if the node is inside the viewport. NO if node is nil or the node is outside the viewport.
 */
- (BOOL)containsNode:(SKNode *)node;

/**Returns the set of nodes in the same scene as the camera that are contained within its viewport.
 * @return the set of nodes contained
 */
- (NSSet<SKNode*> *)containedNodeSet;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKWarpGeometry.h

/**
 SKWarpGeometry.h
 
 Nodes that conform to the SKWarpable protocol can be warped and animated by defining distortions via a SKWarpGeometry objects.

  @copyright 2016 Apple, Inc. All rights reserved.
 */

#import <SpriteKit/SpriteKitBase.h>
#import <SpriteKit/SKAction.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

@class SKTexture, SKShader, SKWarpGeometry, SKWarpGeometryGrid;


SK_EXPORT API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12)) @protocol SKWarpable <NSObject>

/* Warp geometry used to define the distortion */
@property (nonatomic, nullable) SKWarpGeometry *warpGeometry;

/* maximum number of subdivision iterations used to generate the final vertices */
@property (nonatomic) NSInteger subdivisionLevels;

@end




/* Base class for future expansion */
SK_EXPORT API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12)) @interface SKWarpGeometry : NSObject <NSCopying, NSSecureCoding>
@end

SK_EXPORT API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12)) @interface SKWarpGeometryGrid : SKWarpGeometry <NSSecureCoding>

- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/* 1x1 grid with no distortion */
+ (instancetype)grid;

/* grid of the specified dimensions and no distortion */
+ (instancetype)gridWithColumns:(NSInteger)cols
                           rows:(NSInteger)rows;

/*
 Create a grid of the specified dimensions, source and dest positions.
 
 Grid dimensions (cols and rows) refer to the number of faces in each dimension. The
 number of vertices required for a given dimension is equal to (cols + 1) * (rows + 1).
 
 SourcePositions are normalized (0.0 - 1.0) coordinates to determine the source content.
 
 DestPositions are normalized (0.0 - 1.0) positional coordinates with respect to
 the node's native size. Values outside the (0.0-1.0) range are perfectly valid and
 correspond to positions outside of the native undistorted bounds.
 
 Source and dest positions are provided in row-major order staring from the top-left.
 For example the indices for a 2x2 grid would be as follows:
 
 [6]---[7]---[8]
  |     |     |
 [3]---[4]---[5]
  |     |     |
 [0]---[1]---[2]
 
 */
#if (defined(SWIFT_SDK_OVERLAY_SPRITEKIT_EPOCH) && SWIFT_SDK_OVERLAY_SPRITEKIT_EPOCH >= 1)
+ (instancetype)gridWithColumns:(NSInteger)cols
                           rows:(NSInteger)rows
                sourcePositions:(nullable const vector_float2 *)sourcePositions
                  destPositions:(nullable const vector_float2 *)destPositions NS_REFINED_FOR_SWIFT;

/* init with the specified dimensions, source and dest positions. */
- (instancetype)initWithColumns:(NSInteger)cols
                           rows:(NSInteger)rows
                sourcePositions:(nullable const vector_float2 *)sourcePositions
                  destPositions:(nullable const vector_float2 *)destPositions NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;
#else
+ (instancetype)gridWithColumns:(NSInteger)cols
                           rows:(NSInteger)rows
                sourcePositions:(nullable const vector_float2 *)sourcePositions
                  destPositions:(nullable const vector_float2 *)destPositions;

/* init with the specified dimensions, source and dest positions. */
- (instancetype)initWithColumns:(NSInteger)cols
                           rows:(NSInteger)rows
                sourcePositions:(nullable const vector_float2 *)sourcePositions
                  destPositions:(nullable const vector_float2 *)destPositions NS_DESIGNATED_INITIALIZER;
#endif

/* the number of columns in this grid */
@property (nonatomic, readonly) NSInteger numberOfColumns;

/* the number of rows in this grid */
@property (nonatomic, readonly) NSInteger numberOfRows;


/* the total number of (sourcePosition + destPosition) pairs that define this grid.
 For a given dimension this is equal to (numberOfColumns + 1) * (numberOfRows + 1). */
@property (nonatomic, readonly) NSInteger vertexCount;

- (vector_float2)sourcePositionAtIndex:(NSInteger)index;
- (vector_float2)destPositionAtIndex:(NSInteger)index;

#if (defined(SWIFT_SDK_OVERLAY_SPRITEKIT_EPOCH) && SWIFT_SDK_OVERLAY_SPRITEKIT_EPOCH >= 1)
- (instancetype)gridByReplacingSourcePositions:(const vector_float2 *)sourcePositions NS_REFINED_FOR_SWIFT;
- (instancetype)gridByReplacingDestPositions:(const vector_float2 *)destPositions NS_REFINED_FOR_SWIFT;
#else
- (instancetype)gridByReplacingSourcePositions:(const vector_float2 *)sourcePositions;
- (instancetype)gridByReplacingDestPositions:(const vector_float2 *)destPositions;
#endif
@end




@interface SKAction (SKWarpable)

/* Animate from the node's current warpGeometry to a new one over the specified duration.
 
 If the numberOfColumns and numberOfRows match, a smooth interpolation will be performed
 from the node current warp.
 */
+ (nullable SKAction *)warpTo:(SKWarpGeometry *)warp
                     duration:(NSTimeInterval)duration API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

/* Animate through an array of warps
 
 The numberOfColumns and numberOfRows must match for all warps.
 Times are specified in seconds and must be increasing values.
 */
+ (nullable SKAction *)animateWithWarps:(NSArray<SKWarpGeometry *> *)warps
                                  times:(NSArray<NSNumber *> *)times API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

/* Animate through an array of warps
 
 The numberOfColumns and numberOfRows must match for all warps.
 Times are specified in seconds and must be increasing values.
 Optionally restore the original node's warpGeometry from before the action.
 */
+ (nullable SKAction *)animateWithWarps:(NSArray<SKWarpGeometry *> *)warps
                                  times:(NSArray<NSNumber *> *)times
                                restore:(BOOL)restore API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKMutableTexture.h
/**
 @header
 
 Mutable texture is a dervied SKTexture whose pixel data can be modified after creation.
 
 @copyright 2013 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SpriteKitBase.h>
#import <SpriteKit/SKTexture.h>

/* SKMutableTextures are not currently supported in the simulator */

SK_EXPORT API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10)) @interface SKMutableTexture : SKTexture

/**
 Create a mutable texture with a specfic size.
 
 @param size the dimension to use when creating the given texture.
 */
- (instancetype)initWithSize:(CGSize)size;

+ (instancetype)mutableTextureWithSize:(CGSize)size;

/**
 Create a mutable texture with a specfic size and type.
 
 @param size the dimension to use when creating the given texture.
 @param format the CoreVideo format type.  supported types include 'RGBA', 'RGhA', and 'RGfA' for byte, half-float, and float components.
 */
- (instancetype)initWithSize:(CGSize)size pixelFormat:(int)format;

/**
 Modify the created mutable texture.
 */
- (void)modifyPixelDataWithBlock:(void (^)(void *pixelData, size_t lengthInBytes))block;

@end
// ==========  SpriteKit.framework/Headers/SKKeyframeSequence.h
//
//  SKKeyframeSequence.h
//  SpriteKit
//
//  Created by Tim Oriol on 2/25/13.
//
//

#import <SpriteKit/SpriteKitBase.h>

typedef NS_ENUM(NSInteger, SKInterpolationMode) {
    SKInterpolationModeLinear   = 1,
    SKInterpolationModeSpline   = 2,
    SKInterpolationModeStep     = 3,
};

typedef NS_ENUM(NSInteger, SKRepeatMode) {
    SKRepeatModeClamp   = 1,
    SKRepeatModeLoop    = 2,
};

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT @interface SKKeyframeSequence : NSObject <NSSecureCoding, NSCopying>

/* Designated initializer */
- (instancetype)initWithKeyframeValues:(NSArray*)values times:(NSArray<NSNumber*> *)times NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithCapacity:(NSUInteger)numItems;

/**
 Support coding and decoding via NSKeyedArchiver.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

- (NSUInteger)count;

- (void)addKeyframeValue:(id)value time:(CGFloat)time;

- (void)removeLastKeyframe;
- (void)removeKeyframeAtIndex:(NSUInteger)index;

- (void)setKeyframeValue:(id)value forIndex:(NSUInteger)index;
- (void)setKeyframeTime:(CGFloat)time forIndex:(NSUInteger)index;

- (void)setKeyframeValue:(id)value time:(CGFloat)time forIndex:(NSUInteger)index;

- (id)getKeyframeValueForIndex:(NSUInteger)index;
- (CGFloat)getKeyframeTimeForIndex:(NSUInteger)index;

- (nullable id)sampleAtTime:(CGFloat)time;

/* defaults to SKInterpolationModeLinear */
@property (nonatomic) SKInterpolationMode interpolationMode;

/* defaults to SKRepeatModeClamp */
@property (nonatomic) SKRepeatMode repeatMode;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKPhysicsContact.h
//
//  SKPhysicsContact.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpriteKit/SKPhysicsBody.h>
#import <SpriteKit/SpriteKitBase.h>


NS_ASSUME_NONNULL_BEGIN

SK_EXPORT @interface SKPhysicsContact : NSObject

@property (nonatomic, readonly) SKPhysicsBody *bodyA;
@property (nonatomic, readonly) SKPhysicsBody *bodyB;
@property (nonatomic, readonly) CGPoint contactPoint;
@property (nonatomic, readonly) CGVector contactNormal;
@property (nonatomic, readonly) CGFloat collisionImpulse;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKPhysicsWorld.h
//
//  SKPhysicsWorld.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpriteKit/SKPhysicsContact.h>
#import <SpriteKit/SpriteKitBase.h>

@class SKPhysicsJoint;
@class SKFieldNode;

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT @protocol SKPhysicsContactDelegate<NSObject>
@optional
- (void)didBeginContact:(SKPhysicsContact *)contact;
- (void)didEndContact:(SKPhysicsContact *)contact;
@end

SK_EXPORT @interface SKPhysicsWorld : NSObject<NSSecureCoding>

/**
 A global 2D vector specifying the field force acceleration due to gravity. The unit is meters per second so standard earth gravity would be { 0.0, +/-9.8 }.
 */
@property (nonatomic) CGVector gravity;
@property (nonatomic) CGFloat speed;

@property (nonatomic, assign, nullable) id<SKPhysicsContactDelegate> contactDelegate;

- (void)addJoint:(SKPhysicsJoint *)joint;
- (void)removeJoint:(SKPhysicsJoint *)joint;
- (void)removeAllJoints;

- (vector_float3)sampleFieldsAt:(vector_float3)position API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

- (nullable SKPhysicsBody *)bodyAtPoint:(CGPoint)point;
- (nullable SKPhysicsBody *)bodyInRect:(CGRect)rect;
- (nullable SKPhysicsBody *)bodyAlongRayStart:(CGPoint)start end:(CGPoint)end;

- (void)enumerateBodiesAtPoint:(CGPoint)point usingBlock:(void (^)(SKPhysicsBody *body, BOOL *stop))block;
- (void)enumerateBodiesInRect:(CGRect)rect usingBlock:(void (^)(SKPhysicsBody *body, BOOL *stop))block;
- (void)enumerateBodiesAlongRayStart:(CGPoint)start end:(CGPoint)end
                          usingBlock:(void (^)(SKPhysicsBody *body, CGPoint point, CGVector normal, BOOL *stop))block;

@end

NS_ASSUME_NONNULL_END


// ==========  SpriteKit.framework/Headers/SKView.h
//
//  SKView.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//


#import <SpriteKit/SpriteKitBase.h>


/* SKView is not available on WatchOS, please see WKInterfaceSpriteKit */
#if SKVIEW_AVAILABLE

@class SKScene, SKTransition, SKTexture, SKNode;
@protocol SKViewDelegate;

/**
 The view to present your SKScene nodes in.
 
 Present your scenes using the presentScene: and presentScene:transition:
 
 NOTE: Subclassing of SKView is not allowed.
 */

#if TARGET_OS_IPHONE

#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN
SK_EXPORT @interface SKView : UIView

#else

#import <Cocoa/Cocoa.h>
NS_ASSUME_NONNULL_BEGIN
SK_EXPORT @interface SKView : NSView <NSSecureCoding>

#endif

/**
 Pause the entire view
 */
@property (nonatomic, getter = isPaused) BOOL paused;

/**
 Toggles display of performance stats in the view. All default to false.
 */
@property (nonatomic) BOOL showsFPS;
@property (nonatomic) BOOL showsDrawCount;
@property (nonatomic) BOOL showsNodeCount;
@property (nonatomic) BOOL showsQuadCount API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));
@property (nonatomic) BOOL showsPhysics API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));
@property (nonatomic) BOOL showsFields API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));


/**
 Toggles whether the view updates is rendered asynchronously or aligned with Core Animation updates. Defaults to YES.
 */
@property (nonatomic, getter=isAsynchronous) BOOL asynchronous;

/**
 Toggles whether the view allows transparent rendering. This allows content under the view to show through if
 a non-opaque backgroundColor is set on the scene. Defaults to NO.
 */
@property (nonatomic) BOOL allowsTransparency API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/**
 Ignores sibling and traversal order to sort the rendered contents of a scene into the most efficient batching possible.
 This will require zPosition to be used in the scenes to properly guarantee elements are in front or behind each other.
 
 This defaults to NO, meaning that sibling order overrides efficiency heuristics in the rendering of the scenes in the view.
 
 Setting this to YES for a complex scene may substantially increase performance, but care must be taken as only zPosition
 determines render order before the efficiency heuristics are used.
 */
@property (nonatomic) BOOL ignoresSiblingOrder;


@property (nonatomic) BOOL shouldCullNonVisibleNodes API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));


/* Defines the desired rate for this SKView to it's content. 
 Actual rate maybe be limited by hardware or other software. */
@property (nonatomic) NSInteger preferredFramesPerSecond API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));


/**
 Optional view delegate, see SKViewDelegate.
 */
@property (nonatomic, weak, nullable) NSObject<SKViewDelegate> *delegate API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));


/* Deprecated, please use preferredFramesPerSecond.
 Number of frames to skip between renders, defaults to 1 (render every frame)
 Actual requested rate will be preferredFramesPerSecond / frameInterval.  */
@property (nonatomic) NSInteger frameInterval NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);

/* Deprecated, please use preferredFramesPerSecond. */
/* FIXME: remove from public headers once all clinets adopt preferredFramesPerSecond. */
@property(nonatomic) float preferredFrameRate NS_DEPRECATED(10_12, 10_12, 10_0, 10_0);


/**
 Present an SKScene in the view, replacing the current scene.
 
 @param scene the scene to present.
 */
- (void)presentScene:(nullable SKScene *)scene;

/**
 Present an SKScene in the view, replacing the current scene.
 
 If there is currently a scene being presented in the view, the transition is used to swap between them.
 
 @param scene the scene to present.
 @param transition the transition to use when presenting the scene.
 */
- (void)presentScene:(SKScene *)scene transition:(SKTransition *)transition;

/**
 The currently presented scene, otherwise nil. If in a transition, the 'incoming' scene is returned.
 */
@property (nonatomic, readonly, nullable) SKScene *scene;

/**
 Create an SKTexture containing a snapshot of how it would have been rendered in this view.
 The texture is tightly cropped to the size of the node.
 @param node the node subtree to render to the texture.
 */
- (nullable SKTexture *)textureFromNode:(SKNode *)node;

/**
 Create an SKTexture containing a snapshot of how it would have been rendered in this view.
 The texture is cropped to the specified rectangle
 @param node the node subtree to render to the texture.
 @param crop the crop
 */
- (nullable SKTexture *)textureFromNode:(SKNode *)node crop:(CGRect)crop;

/**
 Converts a point from view space to scene space.
 
 @param point the point to convert.
 @param scene the scene to convert the point into.
 */
- (CGPoint)convertPoint:(CGPoint)point toScene:(SKScene *)scene;

/**
 Converts a point from scene space to view space.
 
 @param point the point to convert.
 @param scene the scene to convert the point into.
 */
- (CGPoint)convertPoint:(CGPoint)point fromScene:(SKScene *)scene;

@end



SK_EXPORT API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12)) @protocol SKViewDelegate <NSObject>
@optional
/**
 Allows the client to dynamically control the render rate.
 
 return YES to initiate an update and render for the target time.
 return NO to skip update and render for this target time.
 */
- (BOOL)view:(SKView *)view shouldRenderAtTime:(NSTimeInterval)time;
@end


NS_ASSUME_NONNULL_END

#endif
// ==========  SpriteKit.framework/Headers/SKSpriteNode.h
/**
 @header
 
 
 Sprites display textured rectangles in the SpriteKit scene graph.
 
 A Sprite as defined in this Framework is a textured and colored rectangle. It is a quick and easy way to display 2D images on screen and includes the basic components needed to allow many of these to interact on screen at once.
 
 A SpriteNode is a node that displays a Sprite. As it is a Node it can be transformed, be included as a child in another node and have child nodes of its own.
 
 
 
 @copyright 2011 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SKNode.h>
#import <SpriteKit/SKShader.h>
#import <SpriteKit/SKWarpGeometry.h>
#import <SpriteKit/SpriteKitBase.h>

NS_ASSUME_NONNULL_BEGIN

@class  SKLightNode;

/**
 A Sprite is a textured 2D node. It can be placed, rotated, scaled and animated like any other node except it draws a textured rectangle specified by the bounds and anchor point.
 
 Sprites are used to define quad primitives with color and/or textures applied to them.
 See <a href="http://en.wikipedia.org/wiki/Sprite_(computer_graphics)">wiki</a> for a definition of a Sprite.
 
 */
SK_EXPORT @interface SKSpriteNode : SKNode <SKWarpable>

/**
 Create a sprite with an SKTexture and the specified size.
 @param texture the texture to reference for size and content
 @param size the size of the sprite in points
 */
+ (instancetype)spriteNodeWithTexture:(nullable SKTexture *)texture size:(CGSize)size;

/**
 Create a sprite with an SKTexture and set its size to the SKTexture's pixel width/height.
 @param texture the texture to reference for size and content
 */
+ (instancetype)spriteNodeWithTexture:(nullable SKTexture *)texture;

+ (instancetype)spriteNodeWithTexture:(nullable SKTexture *)texture normalMap:(nullable SKTexture *)normalMap;

/**
 Create a sprite with an image from your app bundle (An SKTexture is created for the image and set on the sprite. Its size is set to the SKTexture's pixel width/height)
 The position of the sprite is (0, 0) and the texture anchored at (0.5, 0.5), so that it is offset by half the width and half the height.
 Thus the sprite has the texture centered about the position. If you wish to have the texture anchored at a different offset set the anchorPoint to another pair of values in the interval from 0.0 up to and including 1.0.
 @param name is the name of an image file stored in the app bundle.
 */
+ (instancetype)spriteNodeWithImageNamed:(NSString *)name;

+ (instancetype)spriteNodeWithImageNamed:(NSString *)name normalMapped:(BOOL)generateNormalMap;

/**
 Create a sprite with a color and the specified bounds.
 @param color the color to use for tinting the sprite.
 @param size the size of the sprite in points
 */
+ (instancetype)spriteNodeWithColor:(SKColor *)color size:(CGSize)size;

/**
 Designated Initializer
 Initialize a sprite with a color and the specified bounds.
 @param texture the texture to use (can be nil for colored sprite)
 @param color the color to use for tinting the sprite.
 @param size the size of the sprite in points
 */
- (instancetype)initWithTexture:(nullable SKTexture *)texture color:(SKColor *)color size:(CGSize)size NS_DESIGNATED_INITIALIZER;

/**
 Initialize a sprite with an SKTexture and set its size to the SKTexture's width/height.
 @param texture the texture to reference for size and content
 */
- (instancetype)initWithTexture:(nullable SKTexture *)texture;

/**
 Initialize a sprite with an image from your app bundle (An SKTexture is created for the image and set on the sprite. Its size is set to the SKTexture's pixel width/height)
 The position of the sprite is (0, 0) and the texture anchored at (0.5, 0.5), so that it is offset by half the width and half the height.
 Thus the sprite has the texture centered about the position. If you wish to have the texture anchored at a different offset set the anchorPoint to another pair of values in the interval from 0.0 up to and including 1.0.
 @param name the name or path of the image to load.
 */
- (instancetype)initWithImageNamed:(NSString *)name;

/**
 Initialize a sprite with a color and the specified bounds.
 @param color the color to use for tinting the sprite.
 @param size the size of the sprite in points
 */
- (instancetype)initWithColor:(SKColor *)color size:(CGSize)size;

/**
 Support coding and decoding via NSKeyedArchiver.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/**
 Texture to be drawn (is stretched to fill the sprite)
 */
@property (nonatomic, retain, nullable) SKTexture *texture;

/**
 Texture to use for generating normals that lights use to light this sprite.
 
 This will only be used if the sprite is lit by at least one light.
 
 @see SKLightNode
 @see lightingBitMask
 */
@property (nonatomic, retain, nullable) SKTexture *normalTexture API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));


/**
 Bitmask to indicate being lit by a set of lights using overlapping lighting categories.
 
 A light whose category is set to a value that masks to non-zero using this mask will
 apply light to this sprite.
 
 When used together with a normal texture, complex lighting effects can be used.
 */
@property (nonatomic) uint32_t lightingBitMask API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

@property (nonatomic) uint32_t shadowCastBitMask API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

@property (nonatomic) uint32_t shadowedBitMask API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));



/**
 Controls how the texture is stretched to fill the SKSpriteNode. Stretching is performed via a 9-part algorithm where the upper & lower middle parts are scaled horizontally, the left and right middle parts are scaled vertically, the center is scaled in both directions, and the corners are preserved. The centerRect defines the center region in a (0.0 - 1.0) coordinate space. Defaults to {(0,0) (1,1)} (the entire texture is stretched).
 */
@property (nonatomic) CGRect centerRect;

/**
 Controls the blending between the texture and the sprite's color. The valid interval of values is from 0.0 up to and including 1.0. A value above or below that interval is clamped to the minimum (0.0) if below or the maximum (1.0) if above.
 */
@property (nonatomic) CGFloat colorBlendFactor;

/**
 Base color for the sprite (If no texture is present, the color still is drawn)
 */
@property (nonatomic, retain) SKColor *color;

/**
 Sets the blend mode to use when composing the sprite with the final framebuffer.
 @see SKNode.SKBlendMode
 */
@property (nonatomic) SKBlendMode blendMode;

/**
 Used to choose the location in the sprite that maps to its 'position' in the parent's coordinate space. The valid interval for each input is from 0.0 up to and including 1.0.
 */
@property (nonatomic) CGPoint anchorPoint;

/**
 Set the size of the sprite (in parent's coordinate space)
 */
@property (nonatomic) CGSize size;

/**
 Adjust the sprite's xScale & yScale to achieve the desired size (in parent's coordinate space)
 */
- (void)scaleToSize:(CGSize)size API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

@property (nonatomic, retain, nullable) SKShader *shader API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/**
 Optional dictionary of SKAttributeValues
 Attributes can be used with custom SKShaders.
 */
@property (nonatomic, nonnull, copy) NSDictionary<NSString *, SKAttributeValue *> *attributeValues API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

- (nullable SKAttributeValue*)valueForAttributeNamed:(nonnull NSString *)key API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
- (void)setValue:(SKAttributeValue*)value forAttributeNamed:(nonnull NSString *)key NS_SWIFT_NAME(setValue(_:forAttribute:)) API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKNode.h
/**
 @header
 
 
 Nodes are the base scene graph nodes used in the SpriteKit scene graph.
 
 
 @copyright 2011 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SpriteKitBase.h>

NS_ASSUME_NONNULL_BEGIN

@class SKAction, SKScene, SKTexture, SKPhysicsBody, SKFieldNode;
@class SKReachConstraints, SKConstraint, SKAttributeValue, SKWarpGeometry;
@protocol UIFocusItem;

/**
 Blend modes that the SKNode uses to compose with the framebuffer to produce blended colors.
 */
typedef NS_ENUM(NSInteger, SKBlendMode) {
    SKBlendModeAlpha         = 0,    // Blends the source and destination colors by multiplying the source alpha value.
    SKBlendModeAdd           = 1,    // Blends the source and destination colors by adding them up.
    SKBlendModeSubtract      = 2,    // Blends the source and destination colors by subtracting the source from the destination.
    SKBlendModeMultiply      = 3,    // Blends the source and destination colors by multiplying them.
    SKBlendModeMultiplyX2    = 4,    // Blends the source and destination colors by multiplying them and doubling the result.
    SKBlendModeScreen        = 5,    // Blends the source and destination colors by multiplying one minus the source with the destination and adding the source.
    SKBlendModeReplace       = 6,    // Replaces the destination with the source (ignores alpha).
    SKBlendModeMultiplyAlpha = 7     // Blends the source and destination colors by multiplying them (with alpha).
} NS_ENUM_AVAILABLE(10_9, 7_0);

typedef NS_ENUM(NSInteger, SKNodeFocusBehavior) {
    SKNodeFocusBehaviorNone = 0,    // Not focusable and node has no impact on other nodes that have focus interaction enabled.  This is the default.
    SKNodeFocusBehaviorOccluding,   // Not focusable, but will prevent other focusable nodes that this node visually obscures from being focusable.
    SKNodeFocusBehaviorFocusable    // Focusable and will also prevent other focusable nodes that this node visually obscures from being focusable.
} API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(macos, watchos);

/**
 A SpriteKit scene graph node. These are the branch nodes that together with geometric leaf nodes make up the directed acyclic graph that is the SpriteKit scene graph tree.
 
 All nodes have one and exactly one parent unless they are the root node of a graph tree. Leaf nodes have no children and contain some sort of sharable data that guarantee the DAG condition.
 */
#if TARGET_OS_IPHONE
#if SKVIEW_AVAILABLE
SK_EXPORT @interface SKNode : UIResponder <NSCopying, NSSecureCoding, UIFocusItem>
#else
SK_EXPORT @interface SKNode : NSObject <NSCopying, NSSecureCoding>
#endif
#else
SK_EXPORT @interface SKNode : NSResponder <NSCopying, NSSecureCoding>
#endif

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 Support coding and decoding via NSKeyedArchiver.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

+ (instancetype)node;

+ (nullable instancetype)nodeWithFileNamed:(NSString*)filename;

+ (nullable instancetype)nodeWithFileNamed:(NSString *)filename securelyWithClasses:(NSSet<Class> *)classes andError:(NSError **)error API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

@property (nonatomic, readonly) CGRect frame;

/**
 Calculates the bounding box including all child nodes in parents coordinate system.
 */
- (CGRect)calculateAccumulatedFrame;

/**
 The position of the node in the parent's coordinate system
 */
@property (nonatomic) CGPoint position;

/**
 The z-order of the node (used for ordering). Negative z is "into" the screen, Positive z is "out" of the screen. A greater zPosition will sort in front of a lesser zPosition.
 */
@property (nonatomic) CGFloat zPosition;

/**
 The Euler rotation about the z axis (in radians)
 */
@property (nonatomic) CGFloat zRotation;

/**
 The scaling in the X axis
 */
@property (nonatomic) CGFloat xScale;
/**
 The scaling in the Y axis
 */
@property (nonatomic) CGFloat yScale;

/**
 The speed multiplier applied to all actions run on this node. Inherited by its children.
 */
@property (nonatomic) CGFloat speed;

/**
 Alpha of this node (multiplied by the output color to give the final result)
 */
@property (nonatomic) CGFloat alpha;

/**
 Controls whether or not the node's actions is updated or paused.
 */
@property (nonatomic, getter = isPaused) BOOL paused;

/**
 Controls whether or not the node and its children are rendered.
 */
@property (nonatomic, getter = isHidden) BOOL hidden;

/**
 Controls whether or not the node receives touch events
 */
@property (nonatomic, getter=isUserInteractionEnabled) BOOL userInteractionEnabled;

/**
 Determines how this node participates in the focus system.  The default is SKNodeFocusBehaviorNone.
 */
@property (nonatomic) SKNodeFocusBehavior focusBehavior API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(macos, watchos);

/**
 The parent of the node.
 
 If this is nil the node has not been added to another group and is thus the root node of its own graph.
 */
@property (nonatomic, readonly, nullable) SKNode *parent;

/**
 The children of this node.
 
 */
@property (nonatomic, readonly) NSArray<SKNode*> *children;


/**
 The client assignable name.
 
 In general, this should be unique among peers in the scene graph.
 */
@property (nonatomic, copy, nullable) NSString *name;

/**
 The scene that the node is currently in.
 */
@property (nonatomic, readonly, nullable) SKScene* scene;

/**
 Physics body attached to the node, with synchronized scale, rotation, and position
 */
@property (nonatomic, retain, nullable) SKPhysicsBody *physicsBody;

/**
 An optional dictionary that can be used to store your own data in a node. Defaults to nil.
 */
@property (nonatomic, retain, nullable) NSMutableDictionary *userData;

/**
 Kinematic constraints, used in IK solving
 */
@property (nonatomic, copy, nullable) SKReachConstraints *reachConstraints;


/**
 Optional array of SKConstraints
 Constraints are evaluated each frame after actions and physics.
 The node's transform will be changed to satisfy the constraint.
 */
@property (nonatomic, copy, nullable) NSArray<SKConstraint*> *constraints;

/**
 Optional dictionary of SKAttributeValues
 Attributes can be used with custom SKShaders.
 DEPRECATED: Attributes are only available for node classes supporting SKShader (see SKSpriteNode etc.).
 */
@property (nonatomic, nonnull, copy) NSDictionary<NSString *, SKAttributeValue *> *attributeValues NS_DEPRECATED(10_12, 10_12, 10_0, 10_0);

- (nullable SKAttributeValue*)valueForAttributeNamed:(nonnull NSString *)key NS_DEPRECATED(10_12, 10_12, 10_0, 10_0);
- (void)setValue:(SKAttributeValue*)value forAttributeNamed:(nonnull NSString *)key NS_SWIFT_NAME(setValue(_:forAttribute:)) NS_DEPRECATED(10_12, 10_12, 10_0, 10_0);

/**
 Sets both the x & y scale
 
 @param scale the uniform scale to set.
 */
- (void)setScale:(CGFloat)scale;

/**
 Adds a node as a child node of this node
 
 The added node must not have a parent.
 
 @param node the child node to add.
 */
- (void)addChild:(SKNode *)node;

- (void)insertChild:(SKNode *)node atIndex:(NSInteger)index;

- (void)removeChildrenInArray:(NSArray<SKNode*> *)nodes;
- (void)removeAllChildren;

- (void)removeFromParent;
- (void)moveToParent:(SKNode *)parent API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

- (nullable SKNode *)childNodeWithName:(NSString *)name;

- (void)enumerateChildNodesWithName:(NSString *)name usingBlock:(void (^)(SKNode *node, BOOL *stop))block;

/**
 * Simplified shorthand for enumerateChildNodesWithName that returns an array of the matching nodes.
 * This allows subscripting of the form:
 *      NSArray *childrenMatchingName = node[@"name"]
 *
 * or even complex like:
 *      NSArray *siblingsBeginningWithA = node[@"../a*"]
 *
 * @param name An Xpath style path that can include simple regular expressions for matching node names.
 * @see enumerateChildNodesWithName:usingBlock:
 */
- (NSArray<SKNode*> *)objectForKeyedSubscript:(NSString *)name API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/* Returns true if the specified parent is in this node's chain of parents */

- (BOOL)inParentHierarchy:(SKNode *)parent;

- (void)runAction:(SKAction *)action;
- (void)runAction:(SKAction *)action completion:(void (^)(void))block;
- (void)runAction:(SKAction *)action withKey:(NSString *)key;

- (BOOL)hasActions;
- (nullable SKAction *)actionForKey:(NSString *)key;

- (void)removeActionForKey:(NSString *)key;
- (void)removeAllActions;

- (BOOL)containsPoint:(CGPoint)p;

/**Returns the node itself or a child node at the point given.
 * If the receiver is returned there is no child node at the given point.
 * @return a child node or self at the given location.
 */
- (SKNode *)nodeAtPoint:(CGPoint)p;

- (NSArray<SKNode*> *)nodesAtPoint:(CGPoint)p;

- (CGPoint)convertPoint:(CGPoint)point fromNode:(SKNode *)node;
- (CGPoint)convertPoint:(CGPoint)point toNode:(SKNode *)node;

/* Returns true if the bounds of this node intersects with the transformed bounds of the other node, otherwise false */

- (BOOL)intersectsNode:(SKNode *)node;

/* Returns true if this node has equivalent content to the other object, otherwise false */

- (BOOL)isEqualToNode:(SKNode *)node;

@end


/**
 Provided for easy transformation of UITouches coordinates to SKNode coordinates should you choose to handle touch events natively.
 */
#if TARGET_OS_IPHONE
#if __has_include(<UIKit/UITouch.h>)
//Allow conversion of UITouch coordinates to scene-space
@interface UITouch (SKNodeTouches)
- (CGPoint)locationInNode:(SKNode *)node;
- (CGPoint)previousLocationInNode:(SKNode *)node;
@end
#endif
#else
@interface NSEvent (SKNodeEvent)
- (CGPoint)locationInNode:(SKNode *)node;
@end
#endif

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SpriteKit.h
//
//  SpriteKit.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#import <SpriteKit/SKScene.h>
#import <SpriteKit/SKCameraNode.h>
#import <SpriteKit/SKNode.h>
#import <SpriteKit/SKSpriteNode.h>
#import <SpriteKit/SKEmitterNode.h>
#import <SpriteKit/SKShapeNode.h>
#import <SpriteKit/SKEffectNode.h>
#import <SpriteKit/SKFieldNode.h>
#import <SpriteKit/SKLabelNode.h>
#import <SpriteKit/SKVideoNode.h>
#import <SpriteKit/SKAudioNode.h>
#import <SpriteKit/SKCropNode.h>
#import <SpriteKit/SKLightNode.h>
#import <SpriteKit/SKReferenceNode.h>
#import <SpriteKit/SK3DNode.h>
#import <SpriteKit/SKTransformNode.h>
#import <SpriteKit/SKRegion.h>
#import <SpriteKit/SKView.h>
#import <SpriteKit/SKTransition.h>
#import <SpriteKit/SKShader.h>
#import <SpriteKit/SKUniform.h>
#import <SpriteKit/SKAttribute.h>
#import <SpriteKit/SKWarpGeometry.h>
#import <SpriteKit/SKRenderer.h>

#import <SpriteKit/SKTileDefinition.h>
#import <SpriteKit/SKTileSet.h>
#import <SpriteKit/SKTileMapNode.h>

#import <SpriteKit/SKTexture.h>
#import <SpriteKit/SKMutableTexture.h>
#import <SpriteKit/SKTextureAtlas.h>

#import <SpriteKit/SKConstraint.h>
#import <SpriteKit/SKReachConstraints.h>

#import <SpriteKit/SKAction.h>

#import <SpriteKit/SKPhysicsBody.h>
#import <SpriteKit/SKPhysicsJoint.h>
#import <SpriteKit/SKPhysicsWorld.h>

#if !TARGET_OS_IPHONE
#import <SpriteKit/SKNode+NSAccessibility.h>
#endif
// ==========  SpriteKit.framework/Headers/SKTransformNode.h
//
//  SKTransformNode.h
//  SpriteKit
//
//

#import <SpriteKit/SpriteKit.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

#if !defined(__MAC_10_13) && !defined(__IPHONE_11_0) && !defined(__WATCHOS_4_0) && !defined(__TVOS_11_0)
typedef struct {  vector_float4 vector; } simd_quatf;
#endif

/**
 * An SKTransformNode can be applied a 3D rotation that will affect
 * the visual aspect of its children.
 * The physics and constraints of the children will behave as if none
 * of them were transformed.
 */
API_AVAILABLE(ios(11.0), tvos(11.0), watchos(4.0), macos(10.13)) SK_EXPORT @interface SKTransformNode : SKNode

@property (nonatomic) CGFloat xRotation;
@property (nonatomic) CGFloat yRotation;

/**
 * Rotation specific setter/getter
 */

- (void)setEulerAngles:(vector_float3)euler;
- (vector_float3)eulerAngles;

- (void)setRotationMatrix:(matrix_float3x3)rotationMatrix;
- (matrix_float3x3)rotationMatrix;

- (void)setQuaternion:(simd_quatf)quaternion;
- (simd_quatf)quaternion;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKFieldNode.h
/**
 @header
 
 Field Nodes apply force to physics bodies and particles.
 
 @copyright 2014 Apple Inc. All rights reserved.
 
*/

#import <SpriteKit/SpriteKitBase.h>
#import <SpriteKit/SKAction.h>
#import <SpriteKit/SKNode.h>
#import <Foundation/Foundation.h>

@class SKTexture, SKRegion;

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10)) @interface SKFieldNode : SKNode

/** The region property is the domain of the field's effect. No force is applied to objects outside the region.
 */
@property (nonatomic, retain, nullable) SKRegion *region;

/** strength scaling value. default 1.0 */
@property (nonatomic) float strength;

/** The falloff exponent used to calculate field strength at a distance.
    Falloff starts at the minimum radius.

    The default exponent is zero, which results in a uniform field with no falloff.
 
    @see minimumRadius
 */
@property (nonatomic) float falloff;

/** minimum radius of effect. Default is very small. */
@property (nonatomic) float minimumRadius;

/** If enabled, a field has an effect.
    
    default YES
 */
@property (nonatomic, getter = isEnabled) BOOL enabled;

/** If a field is exclusive, it suppresses any other field in its region of effect.
    If two or more exclusive fields overlap, it is undefined which one of them will take effect
 
    @see region
 */
@property (nonatomic, getter = isExclusive) BOOL exclusive;

/** Logical categories the field belongs to. Default is all categories.
    These categories correspond to fieldBitMasks, and can be used to enforce that a particular field applies
    to a particular category of objects.
 
    @see SKPhysicsBody.fieldBitMask
    @see SKEmitterNode.fieldBitMask
 */
@property (nonatomic) uint32_t categoryBitMask;

/** directed fields' directions can be accessed here. If the field is non-directional, a zero vector will be returned
 
 @see linearGravityFieldWithVector:direction
 @see velocityFieldWithVector:direction
 */
@property (nonatomic) vector_float3 direction;

/** fields without a smoothness component will return 0
 
    @see noiseFieldWithSmoothness:smoothness:animationSpeed
    @see turbulenceFieldWithSmoothness:smoothness:animationSpeed
 */
@property (nonatomic) float smoothness;

/** fields that can be animated can have non zero values.
 
    A value of 2 will animated twice as fast as a value of 1.
 
   @see noiseFieldWithSmoothness:smoothness:animationSpeed
   @see turbulenceFieldWithSmoothness:smoothness:animationSpeed
 */
@property (nonatomic) float animationSpeed;

/** fields constructed with a texture can be uppdated by assigning a new texture
 
    @see velocityFieldWithTexture:velocityTexture
 */
@property (nonatomic, retain, nullable) SKTexture* texture;

/**
 Slows an object proportionally to the object’s velocity.
 Use this to simulate effects such as friction from motion through the air.
 */
+ (SKFieldNode *)dragField;

/**
 Applies a force tangential to the direction from the sample point to the field's position.
 The force will be CCW to the direction. Make the strength negative to apply force in the CW direction.
 Amount is proportional to distance from center and the object's mass.
 Use this to create effects such as tornadoes.
 */
+ (SKFieldNode *)vortexField;

/**
 Applies a force in the direction of the origin of the field in local space. To repel objects, use a negative strength.
 The force is proportional to the distance from the field origin. Varies with the mass of the object according to F = ma
 The field node's rotation property can be used to orient the gravity in a particular direction.
 */
+ (SKFieldNode *)radialGravityField;

/**
 Applies a force in the direction of the vector in the local space. To repel objects, use a negative strength.
 The force is the same everywhere in the field. Varies with the mass of the object according to F = ma
 The field node's rotation property can be used to orient the gravity in a particular direction.
 @param direction The direction the force is applied in the x,y plane. The length of the direction vector is multiplied by the field's strength property to get the final calculated force. All three components of the direction vector are used to calculate the length.
 
 @see direction
 */
+ (SKFieldNode *)linearGravityFieldWithVector:(vector_float3)direction;

/**
 Uses the supplied velocity vector for any object entering the field’s area of effect.
 Velocity fields override the effect of any other acceleration applied to the body.
 Velocity fields are typically used for such effects as advection, for example, a velocity field
 might describe the velocity on the surface of a river. An object placed in the river would then follow the river.

 @param direction The directed velocity that will be applied to the body. The z component is ignored.

 @see direction
 */
+ (SKFieldNode *)velocityFieldWithVector:(vector_float3)direction;

/**
 The supplied texture contains velocity values for any object entering the field’s area of effect.
 If no texture is supplied, the direction property is used instead.
 Velocity fields override the effect of any other acceleration applied to the body.
 Velocity fields are typically used for such effects as advection, for example, a velocity field
 might describe the velocity on the surface of a river. An object placed in the river would then follow the river.

 @param velocityTexture The R and G channels of the supplied texture become x and y components of velocity. B and A, if present in the SKTexture, are ignored.
 
 @see texture
 */
+ (SKFieldNode *)velocityFieldWithTexture:(SKTexture *)velocityTexture;

/**
 A time varying differentiable Perlin simplex noise field. By default a smooth noise is calculated,
 and the field is time varying. Use this to simulate such effects as fireflies, or snow.
 To freeze the noise in place, set animationSpeed to 0.0. Mass is ignored.

 @param smoothness value of 0 means as noisy as possible, 1 means as smooth as possible
 @param speed is the general rate in Hz that any particular texel changes to a different value
 
 @see smoothness
 @see animationSpeed
 */
+ (SKFieldNode *)noiseFieldWithSmoothness:(CGFloat)smoothness animationSpeed:(CGFloat)speed;

/**
 Just like Noise, except the strength of the noise is proportional to the velocity of the object in the field.
 
 @param smoothness value of 0 means as noisy as possible, 1 means as smooth as possible
 @param speed is the general rate in Hz that any particular texel changes to a different value
 
 @see smoothness
 @see animationSpeed
 */
+ (SKFieldNode *)turbulenceFieldWithSmoothness:(CGFloat)smoothness animationSpeed:(CGFloat)speed;

/**
 A Hooke’s law force - a force linearly proportional to distance from the center of the field. An object in this
 field will oscillate with a period proportional to the inverse of the mass.
 An example use is to keep objects confined to a particular region.
 */
+ (SKFieldNode *)springField;

/**
 A force proportional to the charge on the object. A charge property has been
 added to SKPhysicsBodies to accomplish this. An example use of this field is to make objects behavior differently
 from one another when they enter a region, or to make an object's behavior different than its mass based behavior
 This field models the first part of the Lorentz equation, F = qE
 */
+ (SKFieldNode *)electricField;

/**
 A force proportional to the charge on the object and the object’s velocity. A charge property has been
 added to SKPhysicsBodies to accomplish this. An example use of this field is to make objects behavior differently
 from one another when they enter a region, or to make an object's behavior different than its mass based behavior
 This field models the second part of the Lorentz equation, F = qvB
 */
+ (SKFieldNode *)magneticField;


/**
 A field force with a custom force evaluator.
 
 @param position The location to evaluate the force at
 @param velocity The velocity to be considered during force evaluation. Useful for calculating drag.
 @param mass The mass to be taken into account during force evaluation
 @param charge The charge to be taken into accoutn during force evaluation
 @param deltaTime The current time step
 */
typedef vector_float3 (^SKFieldForceEvaluator)(vector_float3 position, vector_float3 velocity, float mass, float charge, NSTimeInterval deltaTime);
+ (SKFieldNode *)customFieldWithEvaluationBlock:(SKFieldForceEvaluator)block;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKRegion.h
//
//  SKRegion.h
//  SpriteKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <SpriteKit/SpriteKit.h>
#import <CoreGraphics/CGPath.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10)) @interface SKRegion : NSObject <NSCopying, NSSecureCoding>

@property (nonatomic, readonly, nullable) CGPathRef path;

/** A shared infinite region
  */
+ (instancetype)infiniteRegion;

/** Create a circular region with radius
 */
- (instancetype)initWithRadius:(float)radius;

/** Create a rectangular region of size
 */
- (instancetype)initWithSize:(CGSize)size;

/** Create a region bounded by a CGPath. Note that this option can be
    costly to evaluate.
 */
- (instancetype)initWithPath:(CGPathRef)path;

/** Create a new region that is the inverse of the current region.
    The inverse of the infiniteRegion is an empty region.
    Subclasses of SKRegion need to provide an implementation of inverseRegion.
 */
- (instancetype)inverseRegion;

/** Create a new region that is the original region plus the supplied region
 */
- (instancetype)regionByUnionWithRegion:(SKRegion *)region;

/** Create a new region that is the original region minus the supplied region
 */
- (instancetype)regionByDifferenceFromRegion:(SKRegion *)region;

/** Create a new region that is the region covered by the original region and the supplied region
 */
- (instancetype)regionByIntersectionWithRegion:(SKRegion *)region;

/** Test for containment
 */
- (BOOL)containsPoint:(CGPoint)point;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKTexture.h
//
//  SKTexture.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpriteKit/SpriteKitBase.h>

#if __has_include(<CoreImage/CIFilter.h>)
@class CIFilter;
#endif

typedef NS_ENUM(NSInteger, SKTextureFilteringMode) {
    SKTextureFilteringNearest,
    SKTextureFilteringLinear,
} NS_ENUM_AVAILABLE(10_9, 7_0);

NS_ASSUME_NONNULL_BEGIN

/**
 A texture to be mapped onto SKSpriteNode instances.
 */
SK_EXPORT @interface SKTexture : NSObject <NSCopying, NSSecureCoding>

/**
 Create a texture from an image file. Behaves similar to imageNamed: in UIImage or NSImage
 
 @param name the name or path of the image to load.
 */
+ (instancetype)textureWithImageNamed:(NSString *)name;

/**
 Create a texture that is a subrect of an existing texture. See textureRect property for details.
 
 @param rect the source rectangle to use in creating a logical copy of the given texture.
 @param texture the existing texture to reference in the copy.
 */
+ (instancetype)textureWithRect:(CGRect)rect inTexture:(SKTexture *)texture;


/**
 Create a texture containing directional noise. The RGBA values in this
 texture can be used as a normal map or as direction possibly with length. XYZ are a three dimensional direction, and A is a magnitude.
 
 @param size the size of the resulting texture.
 @param smoothness how similar neighboring pixels are. A value of zero is like static, one is smooth.
 */
+ (instancetype)textureVectorNoiseWithSmoothness:(CGFloat)smoothness size:(CGSize)size API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));


/**
 Create a texture containing colored noise. The noise texture is tileable with itself.
 
 @param size the size of the resulting texture.
 @param smoothness how similar neighboring pixels are. A value of zero is like static, one is smooth.
 @param grayscale if YES, RGB and A will all be the same. If no, RGB and A will all be different. A is not pre-multiplied, because the intent is that if you read a texel in a shader, all four values will be exactly the same value if grayscale, or four different, uncorrelated values if not grayscale.
 */
+ (instancetype)textureNoiseWithSmoothness:(CGFloat)smoothness size:(CGSize)size grayscale:(BOOL)grayscale API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));


/**
 Create a texture from a CGImageRef.
 
 @param image the CGImageRef to create the texture from
 */
+ (instancetype)textureWithCGImage:(CGImageRef)image;

#if TARGET_OS_IPHONE
+ (instancetype)textureWithImage:(UIImage *)image;
#else
+ (instancetype)textureWithImage:(NSImage *)image;
#endif

/**
 Create new texture with bitmap RGBA data in unsigned bytes. Data is copied once, additional changes to the data does not affect the texture. All pixel data is assumed to be premultiplied alpha.
 
 @param pixelData the pixelData to read in creating the texture.
 @param size the dimensions of the pixelData given.
 */
+ (instancetype)textureWithData:(NSData *)pixelData size:(CGSize)size;
+ (instancetype)textureWithData:(NSData *)pixelData size:(CGSize)size flipped:(BOOL)flipped;

/**
 Create new texture with bitmap RGBA data in unsigned bytes using a custom row length and row alignment. Data is copied once, additional changes to the data does not affect the texture. All pixel data is assumed to be premultiplied alpha.
 
 @param pixelData the data to use
 @param size the size in texels
 @param rowLength the length of each row in pixels (allows byte row pitches greater than the width for aligned data)
 @param alignment the byte alignment of the data, provide 0 for tightly packed data.

 */
+ (instancetype)textureWithData:(NSData *)pixelData size:(CGSize)size rowLength:(unsigned int)rowLength alignment:(unsigned int)alignment;


#if __has_include(<CoreImage/CIFilter.h>)
/**
 Create new texture by applying a CIFilter to an existing one. Any CIFilter that requires only a single "inputImage" and produces an "outputImage" is allowed.
 
 @param filter the CI filter to apply in the copy.
 */
- (instancetype)textureByApplyingCIFilter:(CIFilter *)filter;
#endif


/**
 Create new texture by generating a normal map texture.
  */
- (instancetype)textureByGeneratingNormalMap API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));


/**
 Create new texture by generating a normal map texture.
 
 @param smoothness the smooth level of the generated normal map.
 @param contrast  the scale applied to the generated normal map.
 */
- (instancetype)textureByGeneratingNormalMapWithSmoothness:(CGFloat)smoothness contrast:(CGFloat)contrast API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/**
 Used to choose the area of the texture you want to display. The origin and size should both be in the range 0.0 - 1.0, values outside of this range produces unpredictable results. Defaults to the entire texture {(0,0) (1,1)}.
 */
- (CGRect)textureRect;

/**
 The size of the texture's bitmap data in points.
 */
- (CGSize)size;

/**
 The filtering mode the texture should use when not drawn at native size. Defaults to SKTextureFilteringLinear.
 */
@property (nonatomic) SKTextureFilteringMode filteringMode;


/**
 Request that the texture have mipmaps generated if possible. Only supported for power of 2 texture sizes.
 */
@property (nonatomic) BOOL usesMipmaps;


/**
 Convert the current SKTexture into a CGImageRef object
 */
- (CGImageRef)CGImage CF_RETURNS_RETAINED API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/**
 Start a texture preload operation on an array of textures
 
 @param textures an array of SKTextures to be preloaded
 @param completionHandler will be called upon the preload completion
 
 */
+ (void)preloadTextures:(NSArray<SKTexture*> *)textures withCompletionHandler:(void(^)(void))completionHandler;

/**
 Request that this texture be loaded into vram on the next render update, with a callback handler.
 */
- (void)preloadWithCompletionHandler:(void(^)(void))completionHandler;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKTileSet.h
//
//  SKTileSet.h
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <SpriteKit/SKTileDefinition.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The tile set type is used to describe how the tiles will be arranged in a tile map.
 
 @enum SKTileSetTypeGrid Specifies that the tiles will be axis-alligned rectangles that are placed in rows and columns at right angles to one another. This is the default type.
 @enum SKTileSetTypeIsometric Specifies that the tiles will be rectangles that are rotated and scaled to give the appearance of 3/4 perspective.
 @enum SKTileSetTypeHexagonalFlat Specifies that the tiles will be flat bottomed hexagons.
 @enum SKTileSetTypeHexagonalPointy Specifies that the tiles will be "pointy" bottomed hexagons.
*/
typedef NS_ENUM(NSUInteger, SKTileSetType) {
    SKTileSetTypeGrid,
    SKTileSetTypeIsometric,
    SKTileSetTypeHexagonalFlat,
    SKTileSetTypeHexagonalPointy,
} NS_ENUM_AVAILABLE(10_12, 10_0);

/**
 The adjacency mask is used to specify which neighboring tiles need to be filled in for a rule to go into effect.
 */
typedef NS_OPTIONS(NSUInteger, SKTileAdjacencyMask) {
    
    SKTileAdjacencyUp         = 1 << 0, // The above neighboring tile
    SKTileAdjacencyUpperRight = 1 << 1, // The neighboring tile to the upper right
    SKTileAdjacencyRight      = 1 << 2, // The neighboring tile to the right
    SKTileAdjacencyLowerRight = 1 << 3, // The neighboring tile to the lower right
    SKTileAdjacencyDown       = 1 << 4, // The below neighboring tile
    SKTileAdjacencyLowerLeft  = 1 << 5, // The neighboring tile to the lower left
    SKTileAdjacencyLeft       = 1 << 6, // The neighboring tile to the left
    SKTileAdjacencyUpperLeft  = 1 << 7, // The neighboring tile to the upper left
    
    SKTileAdjacencyAll = SKTileAdjacencyUp | SKTileAdjacencyUpperRight | SKTileAdjacencyRight | SKTileAdjacencyLowerRight | SKTileAdjacencyDown | SKTileAdjacencyLowerLeft | SKTileAdjacencyLeft | SKTileAdjacencyUpperLeft,
    
    SKTileHexFlatAdjacencyUp         = 1 << 0,
    SKTileHexFlatAdjacencyUpperRight = 1 << 1,
    SKTileHexFlatAdjacencyLowerRight = 1 << 2,
    SKTileHexFlatAdjacencyDown       = 1 << 3,
    SKTileHexFlatAdjacencyLowerLeft  = 1 << 4,
    SKTileHexFlatAdjacencyUpperLeft  = 1 << 5,
    
    SKTileHexFlatAdjacencyAll = SKTileHexFlatAdjacencyUp | SKTileHexFlatAdjacencyUpperRight | SKTileHexFlatAdjacencyLowerRight | SKTileHexFlatAdjacencyDown | SKTileHexFlatAdjacencyLowerLeft | SKTileHexFlatAdjacencyUpperLeft,
    
    SKTileHexPointyAdjacencyUpperLeft  = 1 << 0,
    SKTileHexPointyAdjacencyUpperRight = 1 << 1,
    SKTileHexPointyAdjacencyRight      = 1 << 2,
    SKTileHexPointyAdjacencyLowerRight = 1 << 3,
    SKTileHexPointyAdjacencyLowerLeft  = 1 << 4,
    SKTileHexPointyAdjacencyLeft       = 1 << 5,
    
    SKTileHexPointyAdjacencyAdd = SKTileHexPointyAdjacencyUpperLeft | SKTileHexPointyAdjacencyUpperRight | SKTileHexPointyAdjacencyRight | SKTileHexPointyAdjacencyLowerRight | SKTileHexPointyAdjacencyLowerLeft | SKTileHexPointyAdjacencyLeft,
    
    // The enumerators below are pre-defined values for common tile configurations
    
    // Pre-defined values for an upwards-facing edge tile.
    SKTileAdjacencyUpEdge = SKTileAdjacencyRight | SKTileAdjacencyLowerRight | SKTileAdjacencyDown | SKTileAdjacencyLowerLeft | SKTileAdjacencyLeft,
    
    // Pre-defined values for an upper right-facing edge tile.
    SKTileAdjacencyUpperRightEdge = SKTileAdjacencyDown | SKTileAdjacencyLowerLeft | SKTileAdjacencyLeft,
    
    // Pre-defined values for a right-facing edge tile.
    SKTileAdjacencyRightEdge = SKTileAdjacencyDown | SKTileAdjacencyLowerLeft | SKTileAdjacencyLeft | SKTileAdjacencyUpperLeft | SKTileAdjacencyUp,
    
    // Pre-defined values for a lower right-facing edge tile.
    SKTileAdjacencyLowerRightEdge = SKTileAdjacencyLeft | SKTileAdjacencyUpperLeft | SKTileAdjacencyUp,
    
    // Pre-defined values for a downwards-facing edge tile.
    SKTileAdjacencyDownEdge = SKTileAdjacencyUp | SKTileAdjacencyUpperRight | SKTileAdjacencyRight | SKTileAdjacencyLeft | SKTileAdjacencyUpperLeft,
    
    // Pre-defined values for a lower left-facing edge tile.
    SKTileAdjacencyLowerLeftEdge = SKTileAdjacencyUp | SKTileAdjacencyUpperRight | SKTileAdjacencyRight,
    
    // Pre-defined values for a left-facing edge tile.
    SKTileAdjacencyLeftEdge = SKTileAdjacencyUp | SKTileAdjacencyUpperRight | SKTileAdjacencyRight | SKTileAdjacencyLowerRight | SKTileAdjacencyDown,
    
    // Pre-defined values for a upper left-facing edge tile.
    SKTileAdjacencyUpperLeftEdge = SKTileAdjacencyRight | SKTileAdjacencyLowerRight | SKTileAdjacencyDown,
    
    // Pre-defined values for an upper right-facing corner tile.
    SKTileAdjacencyUpperRightCorner = SKTileAdjacencyUp | SKTileAdjacencyUpperRight | SKTileAdjacencyRight | SKTileAdjacencyLowerRight | SKTileAdjacencyDown | SKTileAdjacencyLeft | SKTileAdjacencyUpperLeft,
    
    // Pre-defined values for a lower right-facing corner tile.
    SKTileAdjacencyLowerRightCorner = SKTileAdjacencyUp | SKTileAdjacencyUpperRight | SKTileAdjacencyRight | SKTileAdjacencyLowerRight | SKTileAdjacencyDown | SKTileAdjacencyLowerLeft | SKTileAdjacencyLeft,
    
    // Pre-defined values for a lower left-facing corner tile.
    SKTileAdjacencyLowerLeftCorner = SKTileAdjacencyUp | SKTileAdjacencyRight | SKTileAdjacencyLowerRight | SKTileAdjacencyDown | SKTileAdjacencyLowerLeft | SKTileAdjacencyLeft | SKTileAdjacencyUpperLeft,
    
    // Pre-defined values for an upper left-facing corner tile.
    SKTileAdjacencyUpperLeftCorner = SKTileAdjacencyUp | SKTileAdjacencyUpperRight | SKTileAdjacencyRight | SKTileAdjacencyDown | SKTileAdjacencyLowerLeft | SKTileAdjacencyLeft | SKTileAdjacencyUpperLeft,
} NS_ENUM_AVAILABLE(10_12, 10_0);

@class SKTileGroup, SKTileGroupRule;

/**
 A tile set contains all of the tile definitions that are available for use in a tile map. In addition, it also contains tile groups, which define collections of related tile definitions and the rules that govern their placement.
 */
SK_EXPORT API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12)) @interface SKTileSet : NSObject <NSCopying, NSSecureCoding>

/**
 Create a tile set with the specified tile groups.
 @param tileGroups the tile groups that will be available for use with this set
 */
+ (instancetype)tileSetWithTileGroups:(NSArray<SKTileGroup *> *)tileGroups;

/**
 Create a tile set with the specified tile groups and tile set type.
 @param tileGroups the tile groups that will be available for use with this set
 @param tileSetType the type of tile set this will be
 */
+ (instancetype)tileSetWithTileGroups:(NSArray<SKTileGroup *> *)tileGroups tileSetType:(SKTileSetType)tileSetType;

/**
 Initilize a tile set with the specified tile groups.
 @param tileGroups the tile groups that will be available for use with this set
 */
- (instancetype)initWithTileGroups:(NSArray<SKTileGroup *> *)tileGroups;

/**
 Initilize a tile set with the specified tile groups and tile set type.
 @param tileGroups the tile groups that will be available for use with this set
 @param tileSetType the type of tile set this will be
 */
- (instancetype)initWithTileGroups:(NSArray<SKTileGroup *> *)tileGroups tileSetType:(SKTileSetType)tileSetType;

/**
 Gets the tile set with the specified name from the SpriteKit resource bundle. Returns nil if a tile set with a matching name cannot be found.
 @param name the name of the tile set to search for
 */
+ (nullable instancetype)tileSetNamed:(NSString *)name;

/**
 Creates a tile set from the specified tile set file. Returns nil if the URL doesn't point to a valid tile set file.
 @param url the URL of the tile set file
 */
+ (nullable instancetype)tileSetFromURL:(NSURL *)url;

/**
 The tile groups that this set provides for use.
 */
@property (nonatomic, copy) NSArray<SKTileGroup *> *tileGroups;

/**
 Client-assignable name for the tile set. Defaults to nil.
 */
@property (nonatomic, copy, nullable) NSString *name;

/**
 The tile set type specifies how the tiles in the set will be arranged when placed in a tile map. Defaults to SKTileSetTypeGrid.
 */
@property (nonatomic) SKTileSetType type;

@property (nonatomic, nullable) SKTileGroup *defaultTileGroup;

/**
 The default tile size is the value an SKTileMapNode will use for it's tiles when the tile set is assigned to it.
 */
@property (nonatomic) CGSize defaultTileSize;

@end

/**
 A tile group encapsulates a collection of related tile definitions that are designed to be pieced together within a tile map. How those tiles are pieced together is governed by the set of rules. When a tile group is placed in a tile map, the map evaluates the rules to determine which tiles should be placed to achieve the desired outcome.
 */
SK_EXPORT API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12)) @interface SKTileGroup : NSObject <NSCopying, NSSecureCoding>

/**
 Create a simple tile group for a single tile definition. This creates and initializes the SKTileGroupRule necessary to place the provided tile definition in a tile map.
 @param tileDefinition the tile definition we wish to place in a tile map
 */
+ (instancetype)tileGroupWithTileDefinition:(SKTileDefinition *)tileDefinition;

/**
 Create a tile group with the specified rules.
 @param rules the rules the group will use to determine tile placement
 */
+ (instancetype)tileGroupWithRules:(NSArray<SKTileGroupRule *> *)rules;

/**
 Create an empty tile group. Placing this in a tile map will erase the existing tile at that location.
 */
+ (instancetype)emptyTileGroup;

/**
 Initilize a simple tile group for a single tile definition. This creates and initializes the SKTileGroupRule necessary to place the provided tile definition in a tile map.
 @param tileDefinition tile definition we wish to place in a tile map
 */
- (instancetype)initWithTileDefinition:(SKTileDefinition *)tileDefinition;

/**
 Initilize a tile group with the specified rules.
 @param rules the rules the group will use to determine tile placement
 */
- (instancetype)initWithRules:(NSArray<SKTileGroupRule *> *)rules;

/**
 The rules that govern which tiles are placed when this group is used, and where in the map they'll be placed.
 */
@property (nonatomic, copy) NSArray<SKTileGroupRule *> *rules;

/**
 Client-assignable name for the tile group. Defaults to nil.
 */
@property (nonatomic, copy, nullable) NSString *name;

@end

/**
 A tile group rule defines how a certain type of tile should be placed on the map. These tiles are like puzzle pieces, and the rules define how they should be pieced together. This is accomplished by defining which neighboring spaces need to be filled with tiles that belong to the same group, and which tiles are required to be empty. The required pattern of neighboring tiles is defined using the SKTileAdjacencyMask.
 */
SK_EXPORT API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12)) @interface SKTileGroupRule : NSObject <NSCopying, NSSecureCoding>

/**
 Create a tile group rule with the specified adjacency and tile definitions.
 @param adjacency the adjacency requirements for this rule; use the mask that covers the adjacent spaces that must be filled with tiles belonging to the same group; tiles not masked out must be empty
 @param tileDefinitions the tile definitions used for this rule
 */
+ (instancetype)tileGroupRuleWithAdjacency:(SKTileAdjacencyMask)adjacency tileDefinitions:(NSArray<SKTileDefinition*>*)tileDefinitions;

/**
 Initilize a tile group rule with the specified adjacency and tile definitions.
 @param adjacency the adjacency requirements for this rule; use the mask that covers the adjacent spaces that must be filled with tiles belonging to the same group; tiles not masked out must be empty
 @param tileDefinitions the tile definitions used for this rule
 */
- (instancetype)initWithAdjacency:(SKTileAdjacencyMask)adjacency tileDefinitions:(NSArray<SKTileDefinition *> *)tileDefinitions;

/**
 The adjacency mask used by this rule. Set this to the mask that covers the adjacent spaces that must be filled with tiles belonging to the same group for this rule met.
 */
@property (nonatomic) SKTileAdjacencyMask adjacency;


/**
 The tile definitions used by this rule. If the rule is evaluated and its conditions are met, one of the tile definitions within this array will be randomly selected for placement within the tile map. Each tile definitions' placement weight is taken into consideration to determine how likely each is to be selected; tile definitions with higher placement weights will be selected more frequently than those with lower placement weights.
 */
@property (nonatomic, copy) NSArray<SKTileDefinition *> *tileDefinitions;

/**
 Client-assignable name for the tile group rule. Defaults to nil.
 */
@property (nonatomic, copy, nullable) NSString *name;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKTileMapNode.h
//
//  SKTileMapNode.h
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <SpriteKit/SKNode.h>
#import <SpriteKit/SKShader.h>
#import <SpriteKit/SpriteKitBase.h>

#import <SpriteKit/SKTileSet.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A SpriteKit node used to render a 2D array of textured sprites. Uses SKTileSet to determine what textures it can use to render. Separate tile map nodes can be layered on top of one another to achieve various effects, such as parallax scrolling.
 */
SK_EXPORT API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12)) @interface SKTileMapNode : SKNode <NSCopying, NSSecureCoding>

/**
 Create a tile map node with the specified tile set and dimensions. The tiles of the map will be empty, equivalent to the nil tile definition/group.
 @param tileSet the tile set that is used to render the tiles
 @param columns the number of columns in the map that can hold tiles
 @param rows the number of rows in the map that can hold tiles
 @param tileSize the size of each tile in points
 */
+ (instancetype)tileMapNodeWithTileSet:(SKTileSet *)tileSet columns:(NSUInteger)columns rows:(NSUInteger)rows tileSize:(CGSize)tileSize;

/**
 Create a tile map node with the specified tile set and dimensions, and fill it with the specified tile group.
 @param tileSet the tile set that is used to render the tiles
 @param columns the number of columns in the map that can hold tiles
 @param rows the number of rows in the map that can hold tiles
 @param tileSize the size of each tile in points
 @param tileGroup the tile group we wish to fill the tile map with
 */
+ (instancetype)tileMapNodeWithTileSet:(SKTileSet *)tileSet columns:(NSUInteger)columns rows:(NSUInteger)rows tileSize:(CGSize)tileSize fillWithTileGroup:(SKTileGroup *)tileGroup;

/**
 Create a tile map node with the specified tile set and dimensions, and fill it with a specific layout of tile groups that belong to the provided tile set. The tileGroupLayout array should match the dimensions of the tile map (i.e., the number of elements should be equal to columns * rows). Index 0 of the array maps to column 0, row 0 of the tile map. Index 1 is column 1, row 0, and so on, wrapping around to the next row once the index passes the number of columns in the tile map. If the array has fewer elements than the number of tiles in the map, the remaining tiles are initialized with the nil tile group. If the array has more elements than the number of tiles in the map, the extra tile groups are ignored.
 @param tileSet the tile set that is used to render the tiles
 @param columns the number of columns in the map that can hold tiles
 @param rows the number of rows in the map that can hold tiles
 @param tileSize the size of each tile in points
 @param tileGroupLayout an array of tile groups that we want to use to fill the tile map
 */
+ (instancetype)tileMapNodeWithTileSet:(SKTileSet *)tileSet columns:(NSUInteger)columns rows:(NSUInteger)rows tileSize:(CGSize)tileSize tileGroupLayout:(NSArray<SKTileGroup *> *)tileGroupLayout;

/**
 Initialize a tile map node with the specified tile set and dimensions. The tiles of the map will be empty, equivalent to the nil tile definition/group.
 @param tileSet the tile set that is used to render the tiles
 @param columns the number of columns in the map that can hold tiles
 @param rows the number of rows in the map that can hold tiles
 @param tileSize the size of each tile in points
 */
- (instancetype)initWithTileSet:(SKTileSet *)tileSet columns:(NSUInteger)columns rows:(NSUInteger)rows tileSize:(CGSize)tileSize;

/**
 Initialize a tile map node with the specified tile set and dimensions, and fill it with the specified tile group.
 @param tileSet the tile set that is used to render the tiles
 @param columns the number of columns in the map that can hold tiles
 @param rows the number of rows in the map that can hold tiles
 @param tileSize the size of each tile in points
 @param tileGroup the tile group we wish to fill the tile map with
 */
- (instancetype)initWithTileSet:(SKTileSet *)tileSet columns:(NSUInteger)columns rows:(NSUInteger)rows tileSize:(CGSize)tileSize fillWithTileGroup:(SKTileGroup *)tileGroup;

/**
 Initialize a tile map node with the specified tile set and dimensions, and fill it with a specific layout of tile groups that belong to the provided tile set. The tileGroupLayout array should match the dimensions of the tile map (i.e., the number of elements should be equal to columns * rows). Index 0 of the array maps to column 0, row 0 of the tile map. Index 1 is column 1, row 0, and so on, wrapping around to the next row once the index passes the number of columns in the tile map. If the array has fewer elements than the number of tiles in the map, the remaining tiles are initialized with the nil tile group. If the array has more elements than the number of tiles in the map, the extra tile groups are ignored.
 @param tileSet the tile set that is used to render the tiles
 @param columns the number of columns in the map that can hold tiles
 @param rows the number of rows in the map that can hold tiles
 @param tileSize the size of each tile in points
 @param tileGroupLayout an array of tile groups that we want to use to fill the tile map
 */
- (instancetype)initWithTileSet:(SKTileSet *)tileSet columns:(NSUInteger)columns rows:(NSUInteger)rows tileSize:(CGSize)tileSize tileGroupLayout:(NSArray<SKTileGroup *> *)tileGroupLayout;

/**
 The number of columns in the tile map.
 */
@property (nonatomic) NSUInteger numberOfColumns;

/**
 The number of rows in the tile map.
 */
@property (nonatomic) NSUInteger numberOfRows;

/**
 The size of each tile in the map.
 */
@property (nonatomic) CGSize tileSize;

/**
 The size of the tile map. This is dependent on the tileSize, the number of columns and rows in the map, and the tile set type.
 */
@property (nonatomic, readonly) CGSize mapSize;

/**
 The tile set being used by this tile map.
 */
@property (nonatomic) SKTileSet *tileSet;

/**
 Controls the blending between the texture and the tile map color. The valid interval of values is from 0.0 up to and including 1.0. A value above or below that interval is clamped to the minimum (0.0) if below or the maximum (1.0) if above.
 */
@property (nonatomic) CGFloat colorBlendFactor;

/**
 Base color for the tile map (If no texture is present, the color still is drawn).
 */
@property (nonatomic, retain) SKColor *color;

/**
 Sets the blend mode to use when composing the tile map with the final framebuffer.
 @see SKNode.SKBlendMode
 */
@property (nonatomic) SKBlendMode blendMode;

/**
 Used to choose the location in the tile map that maps to its 'position' in the parent's coordinate space. The valid interval for each input is from 0.0 up to and including 1.0.
 */
@property (nonatomic) CGPoint anchorPoint;

/**
 A property that determines whether the tile map is rendered using a custom shader.
 */
@property (nonatomic, retain, nullable) SKShader *shader;

/**
 Optional dictionary of SKAttributeValues
 Attributes can be used with custom SKShaders.
 */
@property (nonatomic, nonnull, copy) NSDictionary<NSString *, SKAttributeValue *> *attributeValues API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

- (nullable SKAttributeValue*)valueForAttributeNamed:(nonnull NSString *)key API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
- (void)setValue:(SKAttributeValue*)value forAttributeNamed:(nonnull NSString *)key NS_SWIFT_NAME(setValue(_:forAttribute:)) API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

/**
 Bitmask to indicate being lit by a set of lights using overlapping lighting categories.

 A light whose category is set to a value that masks to non-zero using this mask will
 apply light to this sprite.

 When used together with a normal texture, complex lighting effects can be used.
 */
@property (nonatomic) uint32_t lightingBitMask;

@property (nonatomic) BOOL enableAutomapping;

/**
 Fill the entire tile map with the provided tile group.
 @param tileGroup the tile group that will be used to fill the map
 */
- (void)fillWithTileGroup:(nullable SKTileGroup *)tileGroup;

/**
 Look up the tile definition at the specified tile index.
 @param column the column index of the tile
 @param row the row index of the tile
 */
- (nullable SKTileDefinition *)tileDefinitionAtColumn:(NSUInteger)column row:(NSUInteger)row;

/**
 Look up the tile group at the specified tile index.
 @param column the column index of the tile
 @param row the row index of the tile
 */
- (nullable SKTileGroup *)tileGroupAtColumn:(NSUInteger)column row:(NSUInteger)row;

/**
 Set the tile group at the specified tile index. When automapping is enabled, the appropriate tile definitions will automatically be selected and placed, possibly modifying neighboring tiles. When automapping is disabled, it will simply place the default center tile definition for the group, and will not modify any of the neihboring tiles.
 @param tileGroup the tile group we want to place in the map
 @param column the column index of the tile
 @param row the row index of the tile
 */
- (void)setTileGroup:(nullable SKTileGroup *)tileGroup forColumn:(NSUInteger)column row:(NSUInteger)row;

/**
 Set the tile group and tile defintion at the specified tile index. When automapping is enabled, it will attempt to resolve the surrounding tiles to allow the specified tile definition to be placed. When automapping is disabled, it will simply place the tile definition and not modify any of the neighboring tiles.
 @param tileGroup the tile group we want to place in the map
 @param tileDefinition the tile definition we want to place in the map
 @param column the column index of the tile
 @param row the row index of the tile
 */
- (void)setTileGroup:(SKTileGroup *)tileGroup andTileDefinition:(SKTileDefinition *)tileDefinition forColumn:(NSUInteger)column row:(NSUInteger)row;

/**
 Returns the column index of the tile that lies under the specified position. Returns NSUIntegerMax if the position does not fall within the tile map.
 @param position the position we want to check against the tile map
 */
- (NSUInteger)tileColumnIndexFromPosition:(CGPoint)position;

/**
 Returns the row index of the tile that lies under the specified position. Returns NSUIntegerMax if the position does not fall within the tile map.
 @param position the position we want to check against the tile map
 */
- (NSUInteger)tileRowIndexFromPosition:(CGPoint)position;

/**
 Returns the position of the center of the tile at the specified column and row.
 @param column the column index of the tile
 @param row the row index of the tile
 */
- (CGPoint)centerOfTileAtColumn:(NSUInteger)column row:(NSUInteger)row;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKCropNode.h
/**
 @header
 
 
 Node that can crop its children's contents with a mask
 
 
 @copyright 2011 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SKNode.h>
#import <SpriteKit/SpriteKitBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A SpriteKit node that masks child nodes using another node's alpha component
 */
SK_EXPORT @interface SKCropNode : SKNode

/**
 SKNode to be used as the mask.
 
 The SKNode supplied as the mask must not be a child of another node, but it may have children. Anywhere the mask's output alpha component is less than 0.05 masks out that area for the SKCropNode's children. If the mask is nil, nothing is masked out.
 */
@property (nonatomic, retain, nullable) SKNode *maskNode;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKLabelNode.h
//
//  SKLabelNode.h
//  SpriteKit
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <SpriteKit/SKSpriteNode.h>
#import <SpriteKit/SpriteKitBase.h>

typedef NS_ENUM(NSInteger, SKLabelVerticalAlignmentMode) {
    SKLabelVerticalAlignmentModeBaseline    = 0,
    SKLabelVerticalAlignmentModeCenter      = 1,
    SKLabelVerticalAlignmentModeTop         = 2,
    SKLabelVerticalAlignmentModeBottom      = 3,
} NS_ENUM_AVAILABLE(10_9, 7_0);

typedef NS_ENUM(NSInteger, SKLabelHorizontalAlignmentMode) {
    SKLabelHorizontalAlignmentModeCenter    = 0,
    SKLabelHorizontalAlignmentModeLeft      = 1,
    SKLabelHorizontalAlignmentModeRight     = 2,
} NS_ENUM_AVAILABLE(10_9, 7_0);

NS_ASSUME_NONNULL_BEGIN

/**
 A node that displays a text label with a given font.
 */
SK_EXPORT @interface SKLabelNode : SKNode

+ (instancetype)labelNodeWithText:(nullable NSString *)text;
+ (instancetype)labelNodeWithAttributedText:(nullable NSAttributedString *)attributedText API_AVAILABLE(ios(11.0), tvos(11.0), watchos(4.0), macos(10.13));
+ (instancetype)labelNodeWithFontNamed:(nullable NSString *)fontName;

- (instancetype)initWithFontNamed:(nullable NSString *)fontName;

@property (nonatomic) SKLabelVerticalAlignmentMode verticalAlignmentMode;
@property (nonatomic) SKLabelHorizontalAlignmentMode horizontalAlignmentMode;

/**Determines the number of lines to draw. The default value is 1 (single line). A value of 0 means no limit.
   If the height of the text reaches the # of lines the text will be truncated using the line break mode.
 */
@property(nonatomic) NSInteger numberOfLines API_AVAILABLE(ios(11.0), tvos(11.0), macos(10.13), watchos(4.0));

/**Determines the line break mode for multiple lines.
   Default is NSLineBreakByTruncatingTail
 */
@property(nonatomic) NSLineBreakMode lineBreakMode API_AVAILABLE(ios(11.0), tvos(11.0), macos(10.13), watchos(4.0));

/**If nonzero, this is used when determining layout width for multiline labels.
   Default is zero.
 */
@property(nonatomic) CGFloat preferredMaxLayoutWidth API_AVAILABLE(ios(11.0), tvos(11.0), macos(10.13), watchos(4.0));

@property (nonatomic, copy, nullable) NSString *fontName;
@property (nonatomic, copy, nullable) NSString *text;
@property (nonatomic, copy, nullable) NSAttributedString *attributedText API_AVAILABLE(ios(11.0), tvos(11.0), macos(10.13), watchos(4.0));
@property (nonatomic) CGFloat fontSize;


/**
 Base color that the text is rendered with (if supported by the font)
 */
@property (nonatomic, retain, nullable) SKColor *fontColor;

/**
 Controls the blending between the rendered text and a color. The valid interval of values is from 0.0 up to and including 1.0. A value above or below that interval is clamped to the minimum (0.0) if below or the maximum (1.0) if above.
 */
@property (nonatomic) CGFloat colorBlendFactor;

/**
 Color to be blended with the text based on the colorBlendFactor
 */
@property (nonatomic, retain, nullable) SKColor *color;

/**
 Sets the blend mode to use when composing the sprite with the final framebuffer.
 @see SKNode.SKBlendMode
 */
@property (nonatomic) SKBlendMode blendMode;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKPhysicsJoint.h
//
//  SKPhysicsJoint.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpriteKit/SKPhysicsBody.h>
#import <SpriteKit/SpriteKitBase.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT @interface SKPhysicsJoint : NSObject <NSSecureCoding>

@property (nonatomic, retain) SKPhysicsBody *bodyA;
@property (nonatomic, retain) SKPhysicsBody *bodyB;

// Instantaneous directed reaction force, in Newtons at anchor point
@property (nonatomic, readonly) CGVector reactionForce;

// Instantaneous reaction torque, in Newton-meters, at anchor point
@property (nonatomic, readonly) CGFloat reactionTorque;

@end


SK_EXPORT @interface SKPhysicsJointPin : SKPhysicsJoint

+ (SKPhysicsJointPin *)jointWithBodyA:(SKPhysicsBody *)bodyA bodyB:(SKPhysicsBody *)bodyB anchor:(CGPoint)anchor;

@property (nonatomic) BOOL shouldEnableLimits;
@property (nonatomic) CGFloat lowerAngleLimit;
@property (nonatomic) CGFloat upperAngleLimit;
@property (nonatomic) CGFloat frictionTorque;
@property (nonatomic) CGFloat rotationSpeed;     // in radians/sec

@end

SK_EXPORT @interface SKPhysicsJointSpring : SKPhysicsJoint

+ (SKPhysicsJointSpring *)jointWithBodyA:(SKPhysicsBody *)bodyA bodyB:(SKPhysicsBody *)bodyB anchorA:(CGPoint)anchorA anchorB:(CGPoint)anchorB;

@property (nonatomic) CGFloat damping;
@property (nonatomic) CGFloat frequency;

@end

SK_EXPORT @interface SKPhysicsJointFixed : SKPhysicsJoint

+ (SKPhysicsJointFixed *)jointWithBodyA:(SKPhysicsBody *)bodyA bodyB:(SKPhysicsBody *)bodyB anchor:(CGPoint)anchor;

@end

SK_EXPORT @interface SKPhysicsJointSliding : SKPhysicsJoint

+ (SKPhysicsJointSliding *)jointWithBodyA:(SKPhysicsBody *)bodyA bodyB:(SKPhysicsBody *)bodyB anchor:(CGPoint)anchor axis:(CGVector)axis;

@property (nonatomic) BOOL shouldEnableLimits;
@property (nonatomic) CGFloat lowerDistanceLimit;
@property (nonatomic) CGFloat upperDistanceLimit;

@end

SK_EXPORT @interface SKPhysicsJointLimit : SKPhysicsJoint

@property (nonatomic) CGFloat maxLength;

+ (SKPhysicsJointLimit *)jointWithBodyA:(SKPhysicsBody *)bodyA bodyB:(SKPhysicsBody *)bodyB anchorA:(CGPoint)anchorA anchorB:(CGPoint)anchorB;

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKEffectNode.h
/**
 @header
 
 
 Node that can apply an effect to its children
 
 
 @copyright 2011 Apple, Inc. All rights reserved.
 
 */

#if __has_include(<CoreImage/CIFilter.h>)
@class CIFilter;
#endif

#import <SpriteKit/SKNode.h>
#import <SpriteKit/SpriteKitBase.h>
#import <SpriteKit/SKShader.h>
#import <SpriteKit/SKWarpGeometry.h>

NS_ASSUME_NONNULL_BEGIN
/**
 A SpriteKit node that applies frame buffer effects to the rendered results of its child nodes. This is done continuously on live content and is not a simple snapshot of the rendered result at one instant of time.
 */
SK_EXPORT @interface SKEffectNode : SKNode <SKWarpable>

#if __has_include(<CoreImage/CIFilter.h>)
/**
 A CIFilter to be used as an effect
 
 Any CIFilter that requires only a single "inputImage" and produces an "outputImage" is allowed. The filter is applied to all children of the SKEffectNode. If the filter is nil, the children of this node is flattened before being drawn as long as the SKEffectNode is enabled.
 */
@property (nonatomic, retain, nullable) CIFilter *filter;
#endif

/* Controls whether the filter's "inputCenter" (if it exists) should automatically be set to the center of the effect area. Defaults to YES. */
@property (nonatomic) BOOL shouldCenterFilter;

/**
 Enable the SKEffectNode.
 
 The SKEffectNode has no effect when appliesEffects is not enabled, this is useful for setting up an effect to use later on. Defaults to YES.
 */
@property (nonatomic) BOOL shouldEnableEffects;

/**
 Enable the rasterization on the SKEffectNode.
 
 The SKEffectNode's output is rasterized and cached internally. This cache is reused when rendering. When the SKEffectNode's children change, the cache is updated, but changing properties on the CIFilter does *not* cause an update (you must disable rasterization and then re-enable it for the changes to apply). This is more expensive than not rasterizing if the node's children change frequently, only enable this option if you know the children is largely static.
 */
@property (nonatomic) BOOL shouldRasterize;

/**
 Sets the blend mode to use when composing the effect with the final framebuffer.
 @see SKNode.SKBlendMode
 */
@property (nonatomic) SKBlendMode blendMode;

@property (nonatomic, retain, nullable) SKShader *shader;

/**
 Optional dictionary of SKAttributeValues
 Attributes can be used with custom SKShaders.
 */
@property (nonatomic, nonnull, copy) NSDictionary<NSString *, SKAttributeValue *> *attributeValues API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

- (nullable SKAttributeValue*)valueForAttributeNamed:(nonnull NSString *)key API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
- (void)setValue:(SKAttributeValue*)value forAttributeNamed:(nonnull NSString *)key NS_SWIFT_NAME(setValue(_:forAttribute:)) API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKTransition.h
//
//  SKTransition.h
//  SpriteKitMac
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <SpriteKit/SpriteKitBase.h>

NS_ASSUME_NONNULL_BEGIN

#if __has_include(<CoreImage/CIFilter.h>)
@class CIFilter;
#endif

typedef NS_ENUM(NSInteger, SKTransitionDirection) {
    SKTransitionDirectionUp,
    SKTransitionDirectionDown,
    SKTransitionDirectionRight,
    SKTransitionDirectionLeft
} NS_ENUM_AVAILABLE(10_9, 7_0);

/**
 A transition style from one scene to another.
 */
SK_EXPORT @interface SKTransition : NSObject <NSCopying>

+ (SKTransition *)crossFadeWithDuration:(NSTimeInterval)sec;

+ (SKTransition *)fadeWithDuration:(NSTimeInterval)sec;

+ (SKTransition *)fadeWithColor:(SKColor *)color duration:(NSTimeInterval)sec;

+ (SKTransition *)flipHorizontalWithDuration:(NSTimeInterval)sec;
+ (SKTransition *)flipVerticalWithDuration:(NSTimeInterval)sec;

+ (SKTransition *)revealWithDirection:(SKTransitionDirection)direction duration:(NSTimeInterval)sec;
+ (SKTransition *)moveInWithDirection:(SKTransitionDirection)direction duration:(NSTimeInterval)sec;
+ (SKTransition *)pushWithDirection:(SKTransitionDirection)direction duration:(NSTimeInterval)sec;

+ (SKTransition *)doorsOpenHorizontalWithDuration:(NSTimeInterval)sec;
+ (SKTransition *)doorsOpenVerticalWithDuration:(NSTimeInterval)sec;
+ (SKTransition *)doorsCloseHorizontalWithDuration:(NSTimeInterval)sec;
+ (SKTransition *)doorsCloseVerticalWithDuration:(NSTimeInterval)sec;

+ (SKTransition *)doorwayWithDuration:(NSTimeInterval)sec;

#if __has_include(<CoreImage/CIFilter.h>)
/* Create a transition with a CIFilter. The filter must be a transition filter which requires only two images (inputImage, inputTargetImage) and generates a single image (outputImage). SpriteKit sets the inputImage, inputTargetImage, and inputTime properties when rendering, all others must be setup beforehand. */

+ (SKTransition *)transitionWithCIFilter:(CIFilter*)filter duration:(NSTimeInterval)sec;
#endif

/**
 Pause the incoming Scene during the transition, defaults to YES.
 */
@property (nonatomic) BOOL pausesIncomingScene;

/**
 Pause the outgoing Scene during the transition, defaults to YES.
 */
@property (nonatomic) BOOL pausesOutgoingScene;


@end

NS_ASSUME_NONNULL_END
// ==========  SpriteKit.framework/Headers/SKTileDefinition.h
//
//  SKTileDefinition.h
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <SpriteKit/SKNode.h>
#import <SpriteKit/SpriteKitBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Adjust the rotation of the tile definition image, in 90 degree increments.
 */
typedef NS_ENUM(NSUInteger, SKTileDefinitionRotation) {
    SKTileDefinitionRotation0 = 0,
    SKTileDefinitionRotation90,
    SKTileDefinitionRotation180,
    SKTileDefinitionRotation270
} NS_ENUM_AVAILABLE(10_12, 10_0);

/**
 A tile definition contains the information needed to represent a single type of tile within a tile map.
 */
SK_EXPORT API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12)) @interface SKTileDefinition : NSObject <NSCopying, NSSecureCoding>

/**
 Create a tile definition with an SKTexture, and set its size to the SKTexture's width/height.
 @param texture the texture to reference for size and content
 */
+ (instancetype)tileDefinitionWithTexture:(SKTexture *)texture;

/**
 Create a tile definition with an SKTexture and the specified size.
 @param texture the texture to reference for content
 @param size the size of the tile in points
 */
+ (instancetype)tileDefinitionWithTexture:(SKTexture *)texture size:(CGSize)size;

/**
 Create a tile definition with an SKTexture and the specified size.
 @param texture the texture to reference for content
 @param normalTexture the normal texture to use for generating normals for lighting
 @param size the size of the tile in points
 */
+ (instancetype)tileDefinitionWithTexture:(SKTexture *)texture normalTexture:(SKTexture *)normalTexture size:(CGSize)size;

/**
 Create an animated tile definition with an array of SKTextures, the specified size, and the length of time each texture should be displayed for in the animation.
 @param textures the textures to reference for animated content
 @param size the size of the tile in points
 @param timePerFrame the duration, in seconds, that each texture in the textures array is displayed before switching to the next texture in the sequence
 */
+ (instancetype)tileDefinitionWithTextures:(NSArray<SKTexture *> *)textures size:(CGSize)size timePerFrame:(CGFloat)timePerFrame;

/**
 Create an animated tile definition with an array of SKTextures, the specified size, and the length of time each texture should be displayed for in the animation.
 @param textures the textures to reference for animated content
 @param normalTextures the normal textures to use for generating normals for lighting
 @param size the size of the tile in points
 @param timePerFrame the duration, in seconds, that each texture in the textures array is displayed before switching to the next texture in the sequence
 */
+ (instancetype)tileDefinitionWithTextures:(NSArray<SKTexture *> *)textures normalTextures:(NSArray<SKTexture *> *)normalTextures size:(CGSize)size timePerFrame:(CGFloat)timePerFrame;

/**
 Initilize a tile definition with an SKTexture, and set its size to the SKTexture's width/height.
 @param texture the texture to reference for size and content
 */
- (instancetype)initWithTexture:(SKTexture *)texture;

/**
 Initilize a tile definition with an SKTexture and the specified size.
 @param texture the texture to reference for content
 @param size the size of the tile in points
 */
- (instancetype)initWithTexture:(SKTexture *)texture size:(CGSize)size;

/**
 Initilize a tile definition with an SKTexture and the specified size.
 @param texture the texture to reference for content
 @param normalTexture the normal texture to use for generating normals for lighting
 @param size the size of the tile in points
 */
- (instancetype)initWithTexture:(SKTexture *)texture normalTexture:(SKTexture *)normalTexture size:(CGSize)size;

/**
 Initilize an animated tile definition with an array of SKTextures, the specified size, and the length of time each texture should be displayed for in the animation.
 @param textures the textures to reference for animated content
 @param size the size of the tile in points
 @param timePerFrame the duration, in seconds, that each texture in the textures array is displayed before switching to the next texture in the sequence
 */
- (instancetype)initWithTextures:(NSArray<SKTexture *>*)textures size:(CGSize)size timePerFrame:(CGFloat)timePerFrame;

/**
 Initilize an animated tile definition with an array of SKTextures, the specified size, and the length of time each texture should be displayed for in the animation.
 @param textures the textures to reference for animated content
 @param normalTextures the normal textures to use for generating normals for lighting
 @param size the size of the tile in points
 @param timePerFrame the duration, in seconds, that each texture in the textures array is displayed before switching to the next texture in the sequence
 */
- (instancetype)initWithTextures:(NSArray<SKTexture *>*)textures normalTextures:(NSArray<SKTexture *> *)normalTextures size:(CGSize)size timePerFrame:(CGFloat)timePerFrame;

/**
 The textures used to draw the tile. Non-animated tiles use only one texture. When more than one texture is present, the tile will swap through them in sequence, showing each for the duration specified in the timePerFrame property. After displaying the last texture in the array, the sequence is repeated from the first texture.
 */
@property (nonatomic, copy) NSArray<SKTexture *> *textures;

/**
 The textures to use for generating normals that lights use to light this tile. These will only be used if the tile is lit by at least one light. Each normal texture corresponds to a texture in the textures property.
 */
@property (nonatomic, copy) NSArray<SKTexture *> *normalTextures;

/**
 An optional dictionary that can be used to store your own data for each tile definition. Defaults to nil.
 */
@property (nonatomic, retain, nullable) NSMutableDictionary *userData;

/**
 Client-assignable name for the tile definition. Defaults to nil.
 */
@property (nonatomic, copy, nullable) NSString *name;

/**
 The size of the tile in points.
 */
@property (nonatomic) CGSize size;

/**
 The duration, in seconds, that each texture in the textures array is displayed before switching to the next texture in the sequence. Only used when there is more than one texture available.
 */
@property (nonatomic) CGFloat timePerFrame;

/**
 This value is used to determine how likely this tile definition is to be chosen for placement when a SKTileGroupRule has mulitple tile definitions assigned to it. A higher value relative to the other definitions assigned to the rule make it more likely for this definition to be selected; lower values make it less likely. Defaults to 1. When set to 0, the definition will never be chosen as long as there is at least one other definition with a placementWeight above 0.
 */
@property (nonatomic) NSUInteger placementWeight;

/**
 The rotation of the tile definition's images can be set in 90 degree increments. Defaults to SKTileDefinitionRotation0.
 */
@property (nonatomic) SKTileDefinitionRotation rotation;

/**
 When set to YES, the tile definition's images will be flipped vertically (i.e., the top of the image becomes the bottom). Defaults to NO.
 */
@property (nonatomic) BOOL flipVertically;

/**
 When set to YES, the tile definition's images will be flipped horizontally (i.e., the left of the image becomes the right). Defaults to NO.
 */
@property (nonatomic) BOOL flipHorizontally;

@end

NS_ASSUME_NONNULL_END


// ==========  SpriteKit.framework/Headers/SKPhysicsBody.h
//
//  SKPhysicsBody.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpriteKit/SpriteKitBase.h>

@class SKPhysicsBody;
@class SKNode;
@class SKTexture;
@class SKPhysicsJoint;

/**
 A SpriteKit physics body. These are the physical representations of your nodes. These specify the area and mass and any collision masking needed.
 
 All bodies have zero, one or more shapes that define its area. A body with no shapes is ethereal and does not collide with other bodies.
 */

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT @interface SKPhysicsBody : NSObject <NSCopying, NSSecureCoding>

/**
 Creates a circle of radius r centered at the node's origin.
 @param r the radius in points
 */
+ (SKPhysicsBody *)bodyWithCircleOfRadius:(CGFloat)r;

/**
 Creates a circle of radius r centered at a point in the node's coordinate space.
 @param r the radius in points
 */
+ (SKPhysicsBody *)bodyWithCircleOfRadius:(CGFloat)r center:(CGPoint)center;

/**
 Creates a rectangle of the specified size centered at the node's origin.
 @param s the size in points
 */
+ (SKPhysicsBody *)bodyWithRectangleOfSize:(CGSize)s;

/**
 Creates a rectangle of the specified size centered at a point in the node's coordinate space.
 @param s the size in points
 */
+ (SKPhysicsBody *)bodyWithRectangleOfSize:(CGSize)s center:(CGPoint)center;

/**
 The path must represent a convex or concave polygon with counter clockwise winding and no self intersection. Positions are relative to the node's origin.
 @param path the path to use
 */
+ (SKPhysicsBody *)bodyWithPolygonFromPath:(CGPathRef)path;

/**
 Creates an edge from p1 to p2. Edges have no volume and are intended to be used to create static environments. Edges can collide with bodies of volume, but not with each other.
 @param p1 start point
 @param p2 end point
 */
+ (SKPhysicsBody *)bodyWithEdgeFromPoint:(CGPoint)p1 toPoint:(CGPoint)p2;

/**
 Creates an edge chain from a path. The path must have no self intersection. Edges have no volume and are intended to be used to create static environments. Edges can collide with bodies of volume, but not with each other.
 @param path the path to use
 */
+ (SKPhysicsBody *)bodyWithEdgeChainFromPath:(CGPathRef)path;

/**
 Creates an edge loop from a path. A loop is automatically created by joining the last point to the first. The path must have no self intersection. Edges have no volume and are intended to be used to create static environments. Edges can collide with body's of volume, but not with each other.
 @param path the path to use
 */
+ (SKPhysicsBody *)bodyWithEdgeLoopFromPath:(CGPathRef)path;

/**
 Creates an edge loop from a CGRect. Edges have no volume and are intended to be used to create static environments. Edges can collide with body's of volume, but not with each other.
 @param rect the CGRect to use
 */
+ (SKPhysicsBody *)bodyWithEdgeLoopFromRect:(CGRect)rect;

/**
 Creates a body from the alpha values in the supplied texture.
 @param texture the texture to be interpreted
 @param size of the generated physics body
 */
+ (SKPhysicsBody *)bodyWithTexture:(SKTexture*)texture size:(CGSize)size API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/**
 Creates a body from the alpha values in the supplied texture.
 @param texture the texture to be interpreted
 @param alphaThreshold the alpha value above which a pixel is interpreted as opaque
 @param size of the generated physics body
 */
+ (SKPhysicsBody *)bodyWithTexture:(SKTexture*)texture alphaThreshold:(float)alphaThreshold size:(CGSize)size API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));


/**
 Creates an compound body that is the union of the bodies used to create it.
 */
+ (SKPhysicsBody *)bodyWithBodies:(NSArray<SKPhysicsBody*> *)bodies;

@property (nonatomic, getter = isDynamic) BOOL dynamic;
@property (nonatomic) BOOL usesPreciseCollisionDetection;
@property (nonatomic) BOOL allowsRotation;
@property (nonatomic) BOOL pinned API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));


/**
 If the physics simulation has determined that this body is at rest it may set the resting property to YES. Resting bodies do not participate
 in the simulation until some collision with a non-resting  object, or an impulse is applied, that unrests it. If all bodies in the world are resting
 then the simulation as a whole is "at rest".
 */
@property (nonatomic, getter = isResting) BOOL resting;

/**
 Determines the 'roughness' for the surface of the physics body (0.0 - 1.0). Defaults to 0.2
 */
@property (nonatomic) CGFloat friction;

/**
 Specifies the charge on the body. Charge determines the degree to which a body is affected by
 electric and magnetic fields. Note that this is a unitless quantity, it is up to the developer to
 set charge and field strength appropriately. Defaults to 0.0
 */
@property (nonatomic) CGFloat charge API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/**
 Determines the 'bounciness' of the physics body (0.0 - 1.0). Defaults to 0.2
 */
@property (nonatomic) CGFloat restitution;

/**
 Optionally reduce the body's linear velocity each frame to simulate fluid/air friction. Value should be zero or greater. Defaults to 0.1.
 Used in conjunction with per frame impulses, an object can be made to move at a constant speed. For example, if an object 64 points in size
 and default density and a linearDamping of 25 will slide across the screen in a few seconds if an impulse of magnitude 10 is applied every update.
 */
@property (nonatomic, assign) CGFloat linearDamping;

/**
 Optionally reduce the body's angular velocity each frame to simulate rotational friction. (0.0 - 1.0). Defaults to 0.1
 */
@property (nonatomic, assign) CGFloat angularDamping;

/**
 The density of the body.
 @discussion
 The unit is arbitrary, as long as the relative densities are consistent throughout the application. Note that density and mass are inherently related (they are directly proportional), so changing one also changes the other. Both are provided so either can be used depending on what is more relevant to your usage.
 */
@property (nonatomic) CGFloat density;

/**
 The mass of the body.
 @discussion
 The unit is arbitrary, as long as the relative masses are consistent throughout the application. Note that density and mass are inherently related (they are directly proportional), so changing one also changes the other. Both are provided so either can be used depending on what is more relevant to your usage.
 */
@property (nonatomic) CGFloat mass;

/**
 The area of the body.
 @discussion
 The unit is arbitrary, as long as the relative areas are consistent throughout the application.
 */
@property (nonatomic, readonly) CGFloat area;

/**
 Bodies are affected by field forces such as gravity if this property is set and the field's category mask is set appropriately. The default value is YES.
 @discussion
 If this is set a force is applied to the object based on the mass. Set the field force vector in the scene to modify the strength of the force.
 */
@property (nonatomic, assign) BOOL affectedByGravity;

/**
 Defines what logical 'categories' of fields this body responds to. Defaults to all bits set (all categories).
 Can be forced off via affectedByGravity.
 */
@property (nonatomic, assign) uint32_t fieldBitMask API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/**
 Defines what logical 'categories' this body belongs to. Defaults to all bits set (all categories).
 */
@property (nonatomic, assign) uint32_t categoryBitMask;

/**
 Defines what logical 'categories' of bodies this body responds to collisions with. Defaults to all bits set (all categories).
 */
@property (nonatomic, assign) uint32_t collisionBitMask;

/**
 Defines what logical 'categories' of bodies this body generates intersection notifications with. Defaults to all bits cleared (no categories).
 */
@property (nonatomic, assign) uint32_t contactTestBitMask;


@property (nonatomic, readonly) NSArray<SKPhysicsJoint*> *joints;

/**
 The representedObject this physicsBody is currently bound to, or nil if it is not.
 */
@property (nonatomic, readonly, weak, nullable) SKNode *node;


@property (nonatomic) CGVector velocity;
@property (nonatomic) CGFloat angularVelocity;

- (void)applyForce:(CGVector)force;
- (void)applyForce:(CGVector)force atPoint:(CGPoint)point;

- (void)applyTorque:(CGFloat)torque;

- (void)applyImpulse:(CGVector)impulse;
- (void)applyImpulse:(CGVector)impulse atPoint:(CGPoint)point;

- (void)applyAngularImpulse:(CGFloat)impulse;

/* Returns an array of all SKPhysicsBodies currently in contact with this one */
- (NSArray<SKPhysicsBody*> *)allContactedBodies;

@end

NS_ASSUME_NONNULL_END

// ==========  SpriteKit.framework/Headers/SKUniform.h
/**
 @header
 
 Uniform defines the type and data associated with a custom fragment shader, SKShader.
 
 @copyright 2013 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SpriteKitBase.h>
#import <SpriteKit/SKTexture.h>
#import <simd/simd.h>

#if !TARGET_OS_UIKITFORMAC && __has_include(<GLKit/GLKMath.h>)
#import <GLKit/GLKMath.h>
#endif

typedef NS_ENUM(NSInteger, SKUniformType) {
    SKUniformTypeNone               =    0,
    SKUniformTypeFloat              =    1,
    SKUniformTypeFloatVector2       =    2,
    SKUniformTypeFloatVector3       =    3,
    SKUniformTypeFloatVector4       =    4,
    SKUniformTypeFloatMatrix2       =    5,
    SKUniformTypeFloatMatrix3       =    6,
    SKUniformTypeFloatMatrix4       =    7,
    SKUniformTypeTexture            =    8,
} NS_ENUM_AVAILABLE(10_10, 8_0);


NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_10, 8_0)
SK_EXPORT @interface SKUniform : NSObject <NSCopying, NSSecureCoding>

/**
 Create a shader uniform with a given name.
 
 @param name the name of the shader uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name;

/**
 Create a shader uniform with a given name, and texture data
 
 @param name the name of the shader uniform.
 @param texture the texture data associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name texture:(nullable SKTexture*)texture;

/**
 Create a shader uniform with a given name, and a float value
 
 @param name the name of the shader uniform.
 @param value the floating point value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name float:(float)value;

/**
 Create a shader uniform with a given name, and a float vector2 value
 
 @param name the name of the shader uniform.
 @param value the float vector2 value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name vectorFloat2:(vector_float2)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

/**
 Create a shader uniform with a given name, and a float vector3 value
 
 @param name the name of the shader uniform.
 @param value the float vector3 value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name vectorFloat3:(vector_float3)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

/**
 Create a shader uniform with a given name, and a float vector4 value
 
 @param name the name of the shader uniform.
 @param value the float vector4 value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name vectorFloat4:(vector_float4)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

/**
 Create a shader uniform with a given name, and a 2x2 matrix value
 
 @param name the name of the shader uniform.
 @param value the 2x2 matrix value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name matrixFloat2x2:(matrix_float2x2)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

/**
 Create a shader uniform with a given name, and a 3x3 matrix value
 
 @param name the name of the shader uniform.
 @param value the 3x3 matrix value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name matrixFloat3x3:(matrix_float3x3)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

/**
 Create a shader uniform with a given name, and a 4x4 matrix value
 
 @param name the name of the shader uniform.
 @param value the 4x4 matrix value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name matrixFloat4x4:(matrix_float4x4)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

/* The name by which this uniform will be referenced in a shader */
@property (nonatomic, readonly) NSString *name;

/* Once created, a uniform is locked to a specific type, you may only access the property of this type */
@property (nonatomic, readonly) SKUniformType uniformType;

/* Access to the texture data associated with the current uniform */
@property (nonatomic, retain, nullable) SKTexture *textureValue;

/* Access to the value associated with the uniform */
@property (nonatomic) float floatValue;
@property (nonatomic) vector_float2 vectorFloat2Value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
@property (nonatomic) vector_float3 vectorFloat3Value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
@property (nonatomic) vector_float4 vectorFloat4Value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
@property (nonatomic) matrix_float2x2 matrixFloat2x2Value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
@property (nonatomic) matrix_float3x3 matrixFloat3x3Value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
@property (nonatomic) matrix_float4x4 matrixFloat4x4Value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

- (instancetype)initWithName:(NSString *)name;
- (instancetype)initWithName:(NSString *)name texture:(nullable SKTexture*)texture;
- (instancetype)initWithName:(NSString *)name float:(float)value;
- (instancetype)initWithName:(NSString *)name vectorFloat2:(vector_float2)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
- (instancetype)initWithName:(NSString *)name vectorFloat3:(vector_float3)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
- (instancetype)initWithName:(NSString *)name vectorFloat4:(vector_float4)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
- (instancetype)initWithName:(NSString *)name matrixFloat2x2:(matrix_float2x2)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
- (instancetype)initWithName:(NSString *)name matrixFloat3x3:(matrix_float3x3)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
- (instancetype)initWithName:(NSString *)name matrixFloat4x4:(matrix_float4x4)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

#if !TARGET_OS_UIKITFORMAC && __has_include(<GLKit/GLKMath.h>)
@property GLKVector2 floatVector2Value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
@property GLKVector3 floatVector3Value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
@property GLKVector4 floatVector4Value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
@property GLKMatrix2 floatMatrix2Value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
@property GLKMatrix3 floatMatrix3Value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
@property GLKMatrix4 floatMatrix4Value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);

+ (instancetype)uniformWithName:(NSString *)name floatVector2:(GLKVector2)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
+ (instancetype)uniformWithName:(NSString *)name floatVector3:(GLKVector3)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
+ (instancetype)uniformWithName:(NSString *)name floatVector4:(GLKVector4)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
+ (instancetype)uniformWithName:(NSString *)name floatMatrix2:(GLKMatrix2)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
+ (instancetype)uniformWithName:(NSString *)name floatMatrix3:(GLKMatrix3)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
+ (instancetype)uniformWithName:(NSString *)name floatMatrix4:(GLKMatrix4)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);

- (instancetype)initWithName:(NSString *)name floatVector2:(GLKVector2)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
- (instancetype)initWithName:(NSString *)name floatVector3:(GLKVector3)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
- (instancetype)initWithName:(NSString *)name floatVector4:(GLKVector4)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
- (instancetype)initWithName:(NSString *)name floatMatrix2:(GLKMatrix2)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
- (instancetype)initWithName:(NSString *)name floatMatrix3:(GLKMatrix3)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
- (instancetype)initWithName:(NSString *)name floatMatrix4:(GLKMatrix4)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
#endif

@end

NS_ASSUME_NONNULL_END
