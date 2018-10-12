// ==========  SceneKit.framework/Headers/SCNPhysicsWorld.h
//
//  SCNPhysicsWorld.h
//  SceneKit
//
//  Copyright © 2014-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNPhysicsBody;
@class SCNPhysicsShape;
@class SCNPhysicsWorld;
@class SCNPhysicsContact;
@class SCNPhysicsBehavior;
@class SCNHitTestResult;

// Keys for ray, contact and sweep tests
typedef NSString * SCNPhysicsTestOption NS_STRING_ENUM;
SCN_EXPORT SCNPhysicsTestOption const SCNPhysicsTestCollisionBitMaskKey API_AVAILABLE(macos(10.10)); // Allows to filter the objects tested by rayTest, contactTest and convexSweep. Default is SCNPhysicsCollisionCategoryAll
SCN_EXPORT SCNPhysicsTestOption const SCNPhysicsTestSearchModeKey       API_AVAILABLE(macos(10.10)); // Specifies how to perform the ray/contact/sweep test. Values are defined below. If not defined, then defaults to SCNPhysicsTestSearchModeAny
SCN_EXPORT SCNPhysicsTestOption const SCNPhysicsTestBackfaceCullingKey  API_AVAILABLE(macos(10.10)); // Specifies whether the back faces should be ignored or not. Defaults to YES.

#define SCNPhysicsTestOptionCollisionBitMask SCNPhysicsTestCollisionBitMaskKey
#define SCNPhysicsTestOptionSearchMode       SCNPhysicsTestSearchModeKey
#define SCNPhysicsTestOptionBackfaceCulling  SCNPhysicsTestBackfaceCullingKey

// Values for SCNPhysicsTestSearchModeKey
typedef NSString * SCNPhysicsTestSearchMode NS_STRING_ENUM;
SCN_EXPORT SCNPhysicsTestSearchMode const SCNPhysicsTestSearchModeAny     API_AVAILABLE(macos(10.10)); // Returns the first contact found.
SCN_EXPORT SCNPhysicsTestSearchMode const SCNPhysicsTestSearchModeClosest API_AVAILABLE(macos(10.10)); // Returns the nearest contact found only.
SCN_EXPORT SCNPhysicsTestSearchMode const SCNPhysicsTestSearchModeAll     API_AVAILABLE(macos(10.10)); // All contacts are returned.

/*!
 @protocol SCNPhysicsContactDelegate
 @abstract The SCNPhysicsContactDelegate protocol is to be implemented by delegates that want to be notified when a contact occured.
 */
API_AVAILABLE(macos(10.10))
@protocol SCNPhysicsContactDelegate <NSObject>
@optional
- (void)physicsWorld:(SCNPhysicsWorld *)world didBeginContact:(SCNPhysicsContact *)contact;
- (void)physicsWorld:(SCNPhysicsWorld *)world didUpdateContact:(SCNPhysicsContact *)contact;
- (void)physicsWorld:(SCNPhysicsWorld *)world didEndContact:(SCNPhysicsContact *)contact;
@end

/*!
 @class SCNPhysicsWorld
 @abstract The SCNPhysicsWorld class describes and allows to control the physics simulation of a 3d scene.
 @discussion The SCNPhysicsWorld class should not be allocated directly but retrieved from the SCNScene class using the physicsWorld property.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsWorld : NSObject <NSSecureCoding>

//A global 3D vector specifying the field force acceleration due to gravity. The unit is meter per second. Default is {0, -9.8, 0}.
@property(nonatomic) SCNVector3 gravity;

//A speed multiplier applied to the physics simulation. Default is 1.0.
//The speed can be reduced to slowdown the simulation, but beware that increasing the speed factor will decrease the accuracy of the simulation.
@property(nonatomic) CGFloat speed;

//The time step of the physics simulation. Default is 1/60s (60 Hz).
@property(nonatomic) NSTimeInterval timeStep;

//A delegate that is called when two physic bodies come in contact with each other.
//On iOS 11 or lower the property is unsafe_unretained and it's the responsibility of the client to set it to nil before deallocating the delegate.
//Starting in iOS12, the property is weak
@property(atomic, weak, nullable) id <SCNPhysicsContactDelegate> contactDelegate;

//Behaviors management
- (void)addBehavior:(SCNPhysicsBehavior *)behavior;
- (void)removeBehavior:(SCNPhysicsBehavior *)behavior;
- (void)removeAllBehaviors;
@property(nonatomic, readonly) NSArray<SCNPhysicsBehavior *> *allBehaviors;

//Performs a ray test on the physics bodies and their physics shapes.
- (NSArray<SCNHitTestResult *> *)rayTestWithSegmentFromPoint:(SCNVector3)origin toPoint:(SCNVector3)dest options:(nullable NSDictionary<SCNPhysicsTestOption, id> *)options;

//The methods below perform contact tests.
- (NSArray<SCNPhysicsContact *> *)contactTestBetweenBody:(SCNPhysicsBody *)bodyA andBody:(SCNPhysicsBody *)bodyB options:(nullable NSDictionary<SCNPhysicsTestOption, id> *)options;
- (NSArray<SCNPhysicsContact *> *)contactTestWithBody:(SCNPhysicsBody *)body options:(nullable NSDictionary<SCNPhysicsTestOption, id> *)options;
- (NSArray<SCNPhysicsContact *> *)convexSweepTestWithShape:(SCNPhysicsShape *)shape fromTransform:(SCNMatrix4)from toTransform:(SCNMatrix4)to options:(nullable NSDictionary<SCNPhysicsTestOption, id> *)options;

//Force the physics engine to re-evaluate collisions.
//This needs to be called if kinematic are moved and the contacts are wanted before the next simulation step.
- (void)updateCollisionPairs;

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNParticleSystem.h
//
//  SCNParticleSystem.h
//  SceneKit
//
//  Copyright © 2014-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNNode.h>
#import <SceneKit/SCNScene.h>

NS_ASSUME_NONNULL_BEGIN

@class UIColor;
@class SCNGeometry;

typedef NSString * SCNParticleProperty NS_STRING_ENUM;
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyPosition API_AVAILABLE(macos(10.10));        // float3 : {x,y,z}     controller animation type : {NSValue(SCNVector3)}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyAngle API_AVAILABLE(macos(10.10));           // float                controller animation type : {NSNumber}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyRotationAxis API_AVAILABLE(macos(10.10));    // float3 : {x,y,z}     controller animation type : {NSValue(SCNVector3)}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyVelocity API_AVAILABLE(macos(10.10));        // float3 : {x,y,z}     controller animation type : {NSValue(SCNVector3)}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyAngularVelocity API_AVAILABLE(macos(10.10)); // float                controller animation type : {NSNumber}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyLife API_AVAILABLE(macos(10.10));            // float                not controllable
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyColor API_AVAILABLE(macos(10.10));           // float4 : {r,g,b,a}   controller animation type : {UIColor}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyOpacity API_AVAILABLE(macos(10.10));         // float                controller animation type : {NSNumber}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertySize API_AVAILABLE(macos(10.10));            // float                controller animation type : {NSNumber}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyFrame API_AVAILABLE(macos(10.10));           // float                controller animation type : {NSNumber}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyFrameRate API_AVAILABLE(macos(10.10));       // float                controller animation type : {NSNumber}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyBounce API_AVAILABLE(macos(10.10));          // float                controller animation type : {NSNumber}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyCharge API_AVAILABLE(macos(10.10));          // float                controller animation type : {NSNumber}
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyFriction API_AVAILABLE(macos(10.10));        // float                controller animation type : {NSNumber}

// These two properties are only available when handling the events of type SCNParticleEventCollision.
// They are read-only values.
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyContactPoint API_AVAILABLE(macos(10.10));    // float3               not controllable
SCN_EXPORT SCNParticleProperty const SCNParticlePropertyContactNormal API_AVAILABLE(macos(10.10));   // float3               not controllable

/*!
 @typedef SCNParticleEventBlock
 @param data array of particle properties data stripes, ordered by the given NSArray of properties name in [- handleEvent:forProperties:withBlock:]
 @param dataStride array of particle properties data stripes stride, with the same ordering than data.
 @param indices optional array of count indices referencing the particles affected by the event. Only SCNParticleEventDeath and SCNParticleEventCollision provide this array. For SCNParticleEventBirth the indices are implicitely [0,1,2,..,count-1]
 @param count number of particles affected by the event
 @discussion This is a small example of usage of an event handling:
 [particleSystem handleEvent:SCNParticleEventCollision forProperties:@[SCNParticlePropertyAngle, SCNParticlePropertyRotationAxis, SCNParticlePropertyContactNormal] withBlock:^(void **data, size_t *dataStride, uint32_t *indices, NSInteger count) {
    for (NSInteger i = 0; i < count; ++i) {
        // SCNParticlePropertyAngle (float)
        float *angle = (float *)((char *)data[0] + dataStride[0] * indices[i]);
        // SCNParticlePropertyRotationAxis (float3)
        float *axis = (float *)((char *)data[1] + dataStride[1] * indices[i]);
        // SCNParticlePropertyContactNormal (float3)
        float *colNrm = (float *)((char *)data[2] + dataStride[2] * indices[i]);
     
        // rotate the particle (angle[0] and axis[0..2] based on the collision normal (colNrm[0..2])
        // ...
     }
 }];
*/
typedef void (^SCNParticleEventBlock)(void * _Nonnull * _Nonnull data, size_t * _Nonnull dataStride, uint32_t * _Nullable indices, NSInteger count);

/*!
 @typedef SCNParticleModifierBlock
 @param data array of particle properties data stripes, ordered by the given NSArray of properties name in [- handleEvent:forProperties:withBlock:]
 @param dataStride array of particle properties data stripes stride, with the same ordering than data.
 @param start index of the first particle
 @param end index of the last particle
 @param deltaTime duration of the simulation step, in seconds.
 @discussion This is a small example of usage of a modifier block:
 [self.particleSystem addModifierForProperties:@[SCNParticlePropertyPosition, SCNParticlePropertyVelocity] atStage:SCNParticleModifierStagePreCollision withBlock:^(void **data, size_t *dataStride, NSInteger start, NSInteger end, float deltaTime) {
     for (NSInteger i = start; i < end; ++i) {
        // SCNParticlePropertyPosition (float3)
        float *pos = (float *)((char *)data[0] + dataStride[0] * i);
        // SCNParticlePropertyVelocity (float3)
        float *vel = (float *)((char *)data[1] + dataStride[1] * i);
        
         // change velocity and/or position
         // ...
     }
 }];
*/
typedef void (^SCNParticleModifierBlock)(void * _Nonnull * _Nonnull data, size_t * _Nonnull dataStride, NSInteger start, NSInteger end, float deltaTime);

// Particle Sorting Mode
typedef NS_ENUM(NSInteger, SCNParticleSortingMode) {
	SCNParticleSortingModeNone,                        //particles are not sorted
	SCNParticleSortingModeProjectedDepth,              //particles are sorted by depth (far rendered first)
	SCNParticleSortingModeDistance,                    //particles are sorted by distance from the point of view
	SCNParticleSortingModeOldestFirst,                 //particles are sorted by birth date - oldest first
	SCNParticleSortingModeYoungestFirst                //particles are sorted by birth date - yougest first
} API_AVAILABLE(macos(10.10));

// Particle Blend Mode
typedef NS_ENUM(NSInteger, SCNParticleBlendMode) {
	SCNParticleBlendModeAdditive,
	SCNParticleBlendModeSubtract,
	SCNParticleBlendModeMultiply,
	SCNParticleBlendModeScreen,
	SCNParticleBlendModeAlpha,
	SCNParticleBlendModeReplace
} API_AVAILABLE(macos(10.10));

// Particle Orientation Mode
typedef NS_ENUM(NSInteger, SCNParticleOrientationMode) {
	SCNParticleOrientationModeBillboardScreenAligned,  // particles are aligned on screen
	SCNParticleOrientationModeBillboardViewAligned,    // particles are perpendicular with the vector from the point of view to the particle.
	SCNParticleOrientationModeFree, 	               // free on all axis.
    SCNParticleOrientationModeBillboardYAligned        // fixed on Y axis.
} API_AVAILABLE(macos(10.10));

// Particle Birth Location
typedef NS_ENUM(NSInteger, SCNParticleBirthLocation) {
    SCNParticleBirthLocationSurface,                   //particles are emitted on the surface of the emitter shape.
    SCNParticleBirthLocationVolume,                    //particles are emitted inside the volume of the emitter shape.
    SCNParticleBirthLocationVertex                     //particles are emitted on the vertices of the emitter shape.
} API_AVAILABLE(macos(10.10));

// Particle Birth Direction
typedef NS_ENUM(NSInteger, SCNParticleBirthDirection) {
    SCNParticleBirthDirectionConstant,                 // Z Direction of the Emitter.
    SCNParticleBirthDirectionSurfaceNormal,	           // Use the direction induced by the shape
    SCNParticleBirthDirectionRandom                    // Random direction.
} API_AVAILABLE(macos(10.10));

// Texture Animation Mode
typedef NS_ENUM(NSInteger, SCNParticleImageSequenceAnimationMode) {
    SCNParticleImageSequenceAnimationModeRepeat,             // The animation will loop.
    SCNParticleImageSequenceAnimationModeClamp,              // The animation will stop at both ends.
    SCNParticleImageSequenceAnimationModeAutoReverse         // The animation will reverse when reaching an end.
} API_AVAILABLE(macos(10.10));

// Particle Variation Mode
typedef NS_ENUM(NSInteger, SCNParticleInputMode) {
	SCNParticleInputModeOverLife,                  // The input time for the controller animation is the current life duration of the particle
	SCNParticleInputModeOverDistance,              // The input time for the controller animation is the distance from the variation origin node.
	SCNParticleInputModeOverOtherProperty,         // The input time for the controller animation is the current value of another specified property.
} API_AVAILABLE(macos(10.10));

// Particle Modifier Stage
typedef NS_ENUM(NSInteger, SCNParticleModifierStage) {
	SCNParticleModifierStagePreDynamics,
	SCNParticleModifierStagePostDynamics,
	SCNParticleModifierStagePreCollision,
	SCNParticleModifierStagePostCollision
} API_AVAILABLE(macos(10.10));

// Particle Event
typedef NS_ENUM(NSInteger, SCNParticleEvent) {
	SCNParticleEventBirth,                             // Event triggered when a new particle spawns.
	SCNParticleEventDeath,                             // Event triggered when a particle dies.
	SCNParticleEventCollision                          // Event triggered when a particle collides with a collider node.
} API_AVAILABLE(macos(10.10));

/*!
 @class SCNParticlePropertyController
 @abstract The SCNParticlePropertyController class controls the variation over time or over distance of a particle property.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNParticlePropertyController: NSObject <NSSecureCoding, NSCopying>

// Creates and initializes a particle property controller with the specified animation.
+ (instancetype)controllerWithAnimation:(CAAnimation *)animation API_UNAVAILABLE(watchos);

// Specifies the animation to be applied on the particle system property. The type of the animation will depend of the property controlled.
// See the documentation along property name definition.
@property(nonatomic, retain) CAAnimation *animation API_UNAVAILABLE(watchos);

// Specify the input mode of the receiver.
// This can be over life, over distance or over the evolution of another proprety.
// Defaults to SCNParticleInputModeOverLife.
@property(nonatomic) SCNParticleInputMode inputMode;

// Specifies the input scale and bias.
// inputScale defaults to 1 and inputBias to 0.
@property(nonatomic) CGFloat inputScale;
@property(nonatomic) CGFloat inputBias;

// Specifies an origin for the variation mode "SCNParticleInputModeOverDistance".
@property(nonatomic, weak, nullable) SCNNode *inputOrigin;

// Specifies which property to use as input for the input mode "SCNParticleInputModeOverOtherProperty".
@property(nonatomic, copy, nullable) SCNParticleProperty inputProperty;

@end


/*!
 @class SCNParticleSystem
 @abstract The SCNParticleSystem class represents a system of particles.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNParticleSystem : NSObject <NSCopying, NSSecureCoding, SCNAnimatable>

// Create an instance of a particle system
+ (instancetype)particleSystem;
+ (nullable instancetype)particleSystemNamed:(NSString *)name inDirectory:(nullable NSString *)directory;

#pragma mark Emitter properties

// Specifies the duration of the emission. Defaults to 1. Animatable.
@property(nonatomic) CGFloat emissionDuration;

// Specifies the variation of the emission duration. Defaults to 0. Animatable.
@property(nonatomic) CGFloat emissionDurationVariation;

// Specifies the idle duration between two emissions. Defaults to 0. Animatable.
@property(nonatomic) CGFloat idleDuration;

// Specifies the variation of the idle duration. Defaults to 0. Animatable.
@property(nonatomic) CGFloat idleDurationVariation;

// Specifies the looping behavior of the emission. Defaults to YES.
@property(nonatomic) BOOL loops;

// Specifies the particle rate flow, in particles per emissionDuration.
// An emissionDuration of 0 without looping means that the particles are emitted instantaneously
// 0 means that the emitter emits nothing, unless it has variation. Defaults to 1. Animatable.
@property(nonatomic) CGFloat birthRate;

// Specifies the variation of the rate flow. Defaults to 0. Animatable.
@property(nonatomic) CGFloat birthRateVariation;

// Specifies the time length during which particles are emit before the first rendering of the system.
// For example this allows to start a scene with snow that already has fallen. Defaults to 0. Animatable.
@property(nonatomic) CGFloat warmupDuration;

// Specifies the shape of the emitter. nil means a punctual emitter. Defaults to nil.
@property(nonatomic, retain, nullable) SCNGeometry *emitterShape;

// Specifies the location of newly created particles. Defaults to SCNParticleBirthLocationSurface.
@property(nonatomic) SCNParticleBirthLocation birthLocation;

// Specifies the direction of newly created particles. Defaults to SCNParticleBirthDirectionConstant.
@property(nonatomic) SCNParticleBirthDirection birthDirection;

// Specifies the spreading direction of newly created particles, in degrees. Not used in SCNParticleBirthDirectionRandom. Defaults to 0. Animatable.
@property(nonatomic) CGFloat spreadingAngle;

// Specifies the emitting direction of newly created particles, used in the SCNParticleBirthDirectionConstant mode. Defaults to {0, 0, 1}. Animatable.
@property(nonatomic) SCNVector3 emittingDirection;

// Specifies the orientation direction of newly created particles, used in the SCNParticleOrientationModeFree mode. The particle will rotate around this axis. Defaults to {0, 0, 0}, which means random. The particle will then rotate arbitraly. Animatable.
@property(nonatomic) SCNVector3 orientationDirection API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

// Specifies the acceleration applied to particles, in world coordinates.
// Allows to simulate winds or gravity. Defaults to {0, 0, 0}. Animatable.
@property(nonatomic) SCNVector3 acceleration;

// Specifies the rendering and simulation type of the system.
// If set to YES, the system is rendered with the transform of the attached node. Defaults to NO.
@property(nonatomic, getter=isLocal) BOOL local;

#pragma mark Particle properties

//  Specifies the initial angle of the particles at birth, in degrees. Defaults to 0. Animatable.
@property(nonatomic) CGFloat particleAngle;

// Specifies the variation of the initial angle of the particles at birth, in degrees. Defaults to 0. Animatable.
@property(nonatomic) CGFloat particleAngleVariation;

// Specifies the initial velocity of the particles at birth,
// in units per second. Defaults to 0. Animatable.
@property(nonatomic) CGFloat particleVelocity;

//  Specifies the variation of the velocity. Defaults to 0. Animatable.
@property(nonatomic) CGFloat particleVelocityVariation;

// Specifies the initial angular velocity of the particles at birth,
// in degrees per second. Defaults to 0. Animatable.
@property(nonatomic) CGFloat particleAngularVelocity;

// Specifies the variation of the angular velocity, in degrees per second. Defaults to 0. Animatable.
@property(nonatomic) CGFloat particleAngularVelocityVariation;

// Specifies the life span of particles. Animatable.
@property(nonatomic) CGFloat particleLifeSpan;

// Specifies the life span variation of particles. Animatable.
@property(nonatomic) CGFloat particleLifeSpanVariation;

// Specifies an optional system to spawn new particles when a particle dies
@property(nonatomic, retain, nullable) SCNParticleSystem *systemSpawnedOnDying;

// Specifies an optional system to spawn new particles when a particle dies
@property(nonatomic, retain, nullable) SCNParticleSystem *systemSpawnedOnCollision;

// Specifies an optional system to spawn new particles when a particle is alive
@property(nonatomic, retain, nullable) SCNParticleSystem *systemSpawnedOnLiving;

#pragma mark Particle Rendering

// Specifies the image of the particle.
// Can be set to an NSImage/UIImage, a path or a URL.
@property(nonatomic, retain, nullable) id particleImage;

// Specifies the number of column in the image sequence. Defaults to 1.
@property(nonatomic) NSUInteger imageSequenceColumnCount;

// Specifies the number of row in the image sequence. Defaults to 1
@property(nonatomic) NSUInteger imageSequenceRowCount;

// Specifies the texture initial frame index. Ranges from 0 to (imageSequenceColumnCount * imageSequenceRowCount - 1). Defaults to 0. Animatable.
@property(nonatomic) CGFloat imageSequenceInitialFrame;

// Specifies the texture initial frame variation. Animatable.
@property(nonatomic) CGFloat imageSequenceInitialFrameVariation;

// Specifies the texture animation frame rate, in frames per second. Defaults to 0. Animatable.
@property(nonatomic) CGFloat imageSequenceFrameRate;

// Specifies the texture animation frame rate variation, in frames per second. Defaults to 0. Animatable.
@property(nonatomic) CGFloat imageSequenceFrameRateVariation;

// Specifies the texture animation mode. Defaults to SCNTextureAnimationModeRepeat.
@property(nonatomic) SCNParticleImageSequenceAnimationMode imageSequenceAnimationMode;

// Specifies the initial color of the particle. Animatable. Defaults to opaque white.
@property(nonatomic, retain) UIColor *particleColor;

// Specifies the normalized variation of the color.
// With x : hue variation, y : saturation variation, z : brightness variation, w : alpha variation. Animatable.
@property(nonatomic) SCNVector4 particleColorVariation;

// Specifies the initial size of the particle. Animatable.
@property(nonatomic) CGFloat particleSize;

// Specifies the initial size variation of the particle. Animatable.
@property(nonatomic) CGFloat particleSizeVariation;

// Specifies the initial intensity of the particle. Animatable.
@property(nonatomic) CGFloat particleIntensity API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

// Specifies the initial intensity variation of the particle. Animatable.
@property(nonatomic) CGFloat particleIntensityVariation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

// Specifies the blend mode to use to render the particle system. Defaults to SCNParticleBlendModeAdditive.
@property(nonatomic) SCNParticleBlendMode blendMode;

// Specifies whether a black pass is required or not when rendering the particle system.
// This reinforces the contrast of additive/light systems. Defaults to NO.
@property(nonatomic, getter=isBlackPassEnabled) BOOL blackPassEnabled;

// Specifies the orientation mode of the particles. Defaults to SCNParticleOrientationModeBillboardScreenAligned.
@property(nonatomic) SCNParticleOrientationMode orientationMode;

// Specifies the sorting mode of the particles. Defaults to SCNParticleSortingModeNone.
@property(nonatomic) SCNParticleSortingMode sortingMode;

// Enables the lighting of particle systems
@property(nonatomic, getter=isLightingEnabled) BOOL lightingEnabled;

#pragma mark Particle Simulation

// Enables the use of the gravity defined in SCNPhysicsWorld
@property(nonatomic) BOOL affectedByGravity;

// Enables the effect of the physics fields added to the SCNPhysicsWorld
@property(nonatomic) BOOL affectedByPhysicsFields;

// Specifies whether particles die on collision
@property(nonatomic) BOOL particleDiesOnCollision;

// Specifies an array of SCNNode to collide with.
@property(nonatomic, copy, nullable) NSArray<SCNNode *> *colliderNodes;

// Specifies the particle mass. Animatable.
@property(nonatomic) CGFloat particleMass;

// Specifies the particle mass variation. Animatable.
@property(nonatomic) CGFloat particleMassVariation;

// Specifies the particle bounce. Animatable.
@property(nonatomic) CGFloat particleBounce;

// Specifies the particle bounce variation. Animatable.
@property(nonatomic) CGFloat particleBounceVariation;

// Specifies the particle friction. Animatable.
@property(nonatomic) CGFloat particleFriction;

// Specifies the particle friction variation. Animatable.
@property(nonatomic) CGFloat particleFrictionVariation;

// Specifies the charge on the particle. Charge determines the degree to which a particle is affected by
// electric and magnetic fields. Note that this is a unitless quantity, it is up to the developer to
// set charge and field strength appropriately. Defaults to 0.0. Animatable.
@property(nonatomic) CGFloat particleCharge;

// Specifies the particle charge variation. Animatable.
@property(nonatomic) CGFloat particleChargeVariation;

// Specifies the particle air resistance. Defaults to 0. Animatable.
@property(nonatomic) CGFloat dampingFactor;

// Specifies the simulation speed multiplier. Defaults to 1. Animatable.
@property(nonatomic) CGFloat speedFactor;

// Specifies whether particles stretch along their direction. Defaults to 0. Animatable.
@property(nonatomic) CGFloat stretchFactor;

// Specifies the receiver's fresnel exponent value. Defaults to 3. Animatable.
// Only used if the particleImage is a cube map. The bigger the amount, the more concentrated the reflection is around the edges
@property(nonatomic) CGFloat fresnelExponent;

// Property controllers.
@property(nonatomic, copy, nullable) NSDictionary<SCNParticleProperty, SCNParticlePropertyController *> *propertyControllers;

// Remove all the already-emitted particles and restart the simulation.
- (void)reset;

// Events handling
// "block" will be invoked for particles that trigger the specified event, with the data and dataStride that corresponds to "properties". The block should only update the particle properties reference by the "indices" passed as argument in the block.
- (void)handleEvent:(SCNParticleEvent)event forProperties:(NSArray<SCNParticleProperty> *)properties withBlock:(SCNParticleEventBlock)block;

// Modifications handling
// "block" will be invoked at every simulation step at the specified stage. The data and dataStride passed to the block will corresponds to the specified "properties".
- (void)addModifierForProperties:(NSArray<SCNParticleProperty> *)properties atStage:(SCNParticleModifierStage)stage withBlock:(SCNParticleModifierBlock)block;
- (void)removeModifiersOfStage:(SCNParticleModifierStage)stage;
- (void)removeAllModifiers;

@end


@interface SCNNode (SCNParticleSystemSupport)

// Add a particle system to the receiver.
- (void)addParticleSystem:(SCNParticleSystem *)system API_AVAILABLE(macos(10.10));

// Remove all particle systems of the receiver.
- (void)removeAllParticleSystems API_AVAILABLE(macos(10.10));

// Remove the specified particle system from the receiver.
- (void)removeParticleSystem:(SCNParticleSystem *)system API_AVAILABLE(macos(10.10));

// The particle systems attached to the node.
@property(readonly, nullable) NSArray<SCNParticleSystem *> *particleSystems API_AVAILABLE(macos(10.10));

@end


@interface SCNScene (SCNParticleSystemSupport)

// Add a particle system at the given location.
- (void)addParticleSystem:(SCNParticleSystem *)system withTransform:(SCNMatrix4)transform API_AVAILABLE(macos(10.10));

// Remove all particle systems in the scene.
- (void)removeAllParticleSystems API_AVAILABLE(macos(10.10));

// Remove the specified particle system from the receiver.
- (void)removeParticleSystem:(SCNParticleSystem *)system API_AVAILABLE(macos(10.10));

// The particle systems attached to the scene that are active.
@property(readonly, nullable) NSArray<SCNParticleSystem *> *particleSystems API_AVAILABLE(macos(10.10));

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SceneKit.h
//
//  SceneKit.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

/*! @framework SceneKit
    @abstract A high-level 3D scene framework.
    @discussion SceneKit lets you easily load, manipulate, and render 3D scenes.
 */

//types
#import <SceneKit/SceneKitTypes.h>

//protocols
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNBoundingVolume.h>
#import <SceneKit/SCNSceneRenderer.h>
#import <SceneKit/SCNShadable.h>

//renderers
#import <SceneKit/SCNView.h>
#import <SceneKit/SCNRenderer.h>

//classes
#import <SceneKit/SCNScene.h>
#import <SceneKit/SCNSceneSource.h>
#import <SceneKit/SCNNode.h>
#import <SceneKit/SCNLight.h>
#import <SceneKit/SCNCamera.h>
#import <SceneKit/SCNMaterial.h>
#import <SceneKit/SCNMaterialProperty.h>
#import <SceneKit/SCNGeometry.h>
#import <SceneKit/SCNParametricGeometry.h>
#import <SceneKit/SCNTransaction.h>
#import <SceneKit/SCNMorpher.h>
#import <SceneKit/SCNSkinner.h>
#import <SceneKit/SCNConstraint.h>
#import <SceneKit/SCNLevelOfDetail.h>
#import <SceneKit/SCNParticleSystem.h>
#import <SceneKit/SCNPhysicsBody.h>
#import <SceneKit/SCNPhysicsField.h>
#import <SceneKit/SCNPhysicsShape.h>
#import <SceneKit/SCNPhysicsWorld.h>
#import <SceneKit/SCNPhysicsContact.h>
#import <SceneKit/SCNPhysicsBehavior.h>
#import <SceneKit/SCNTechnique.h>
#import <SceneKit/SCNReferenceNode.h>
#import <SceneKit/SCNAudioSource.h>
#import <SceneKit/SCNHitTest.h>
#import <SceneKit/SCNCameraController.h>

//scripting
#import <SceneKit/SCNJavascript.h>
// ==========  SceneKit.framework/Headers/SCNSceneRenderer.h
//
//  SCNSceneRenderer.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNHitTest.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;
@class SCNScene;
@protocol SCNSceneRendererDelegate;
@class SKScene;
@class SKTransition;
@class MTLRenderPassDescriptor;
@protocol MTLRenderCommandEncoder;
@protocol MTLCommandBuffer;
@class AVAudioEngine;
@class AVAudioEnvironmentNode;

/*!
 @enum SCNAntialiasingMode
 @abstract antialiasing modes for scene renderers
 */
typedef NS_ENUM(NSUInteger, SCNAntialiasingMode) {
    SCNAntialiasingModeNone,
    SCNAntialiasingModeMultisampling2X,
    SCNAntialiasingModeMultisampling4X
} API_AVAILABLE(macos(10.10));

/*!
 @enum SCNRenderingAPI
 @abstract rendering API used by SCNView and SCNRenderer.
 @discussion Default preferred API is SCNRenderingAPIMetal on iOS and it depends on the configuration on macOS.
 If Metal is requested but not available then it fallbacks to SCNRenderingAPIOpenGLES2 on iOS and to SCNRenderingAPIOpenGLLegacy on macOS.
 */
typedef NS_ENUM(NSUInteger, SCNRenderingAPI) {
    SCNRenderingAPIMetal,
    SCNRenderingAPIOpenGLES2
} API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @enum SCNDebugOptions
 @abstract Debug options.
 */
typedef NS_OPTIONS(NSUInteger, SCNDebugOptions) {
    SCNDebugOptionNone                                                                               = 0,
    SCNDebugOptionShowPhysicsShapes                                                                  = 1 << 0, //show physics shape
    SCNDebugOptionShowBoundingBoxes                                                                  = 1 << 1, //show object bounding boxes
    SCNDebugOptionShowLightInfluences                                                                = 1 << 2, //show objects's light influences
    SCNDebugOptionShowLightExtents                                                                   = 1 << 3, //show light extents
    SCNDebugOptionShowPhysicsFields                                                                  = 1 << 4, //show SCNPhysicsFields forces and extents
    SCNDebugOptionShowWireframe                                                                      = 1 << 5, //show wireframe on top of objects
    SCNDebugOptionRenderAsWireframe API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 1 << 6, //render objects as wireframe
    SCNDebugOptionShowSkeletons     API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 1 << 7, //show skinning bones
    SCNDebugOptionShowCreases       API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 1 << 8, //show subdivision creases
    SCNDebugOptionShowConstraints   API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 1 << 9, //show slider constraint
    SCNDebugOptionShowCameras       API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 1 << 10, //show cameras
} API_AVAILABLE(macos(10.11), ios(9.0));

/*! @protocol SCNSceneRenderer
    @abstract Protocol adopted by the various renderers (SCNView, SCNLayer, SCNRenderer)
 */
@protocol SCNSceneRenderer <NSObject>
@required

/*!
 @property scene
 @abstract Specifies the scene of the receiver.
 */
@property(nonatomic, retain, nullable) SCNScene *scene;

/*!
 @method presentScene:withTransition:incomingPointOfView:
 @abstract Present a SCNScene in the receiver, replacing the current scene.
 @param scene The new scene to present.
 @param transition the transition to use when presenting the scene.
 @param pointOfView the point of view to use to render the new scene.
 @param completionHandler the block invoked on completion.
 */
- (void)presentScene:(SCNScene *)scene withTransition:(SKTransition *)transition incomingPointOfView:(nullable SCNNode *)pointOfView completionHandler:(nullable void (^)(void))completionHandler API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property sceneTime
 @abstract Specifies the current "scene time" to display the scene.
 @discussion The scene time only affect scene time based animations (see SCNAnimation.h "usesSceneTimeBase" and SCNSceneSource.h "SCNSceneSourceAnimationImportPolicyKey" for how to create scene time based animations). Scene time based animations and this property are typically used by tools and viewer to ease seeking in time while previewing a scene.
 */
@property(nonatomic) NSTimeInterval sceneTime API_AVAILABLE(macos(10.10));

/*! 
 @property delegate
 @abstract Specifies the renderer delegate.
 */
@property(nonatomic, weak, nullable) id <SCNSceneRendererDelegate> delegate;

/*!
 @method hitTest:options:
 @abstract Returns an array of SCNHitTestResult for each node that contains a specified point.
 @param point A point in the coordinate system of the receiver.
 @param options Optional parameters (see the "Hit test options" group for the available options).
 */
- (NSArray<SCNHitTestResult *> *)hitTest:(CGPoint)point options:(nullable NSDictionary<SCNHitTestOption, id> *)options;

/*!
 @method isNodeInsideFrustum:withPointOfView:
 @abstract Test whether node is visible from the specified point of view.
 @param node The node to test the visibility of.
 @param pointOfView The point of view used to test the visibility.
 @discussion Return YES if the node is inside or intersects the clipping planes of the point of view. This method doesn't test if 'node' is occluded by another node.
 */
- (BOOL)isNodeInsideFrustum:(SCNNode *)node withPointOfView:(SCNNode *)pointOfView API_AVAILABLE(macos(10.9));

/*!
 @method nodesInsideFrustumWithPointOfView:
 @abstract Returns an array containing the nodes visible from the specified point of view.
 @param pointOfView The point of view used to test the visibility.
 @discussion Returns an array of all the nodes that are inside or intersects the clipping planes of the point of view. Starting in macOS10.13/iOS11 this method work with the presentation tree.
 */
- (NSArray<SCNNode *> *)nodesInsideFrustumWithPointOfView:(SCNNode *)pointOfView API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method projectPoint
 @abstract Projects a point in the world coordinate system using the receiver's current point of view and viewport.
 @param point The world position to be projected.
 @discussion A point projected from the near (resp. far) clip plane will have a z component of 0 (resp. 1).
 */
- (SCNVector3)projectPoint:(SCNVector3)point API_AVAILABLE(macos(10.9));

/*!
 @method unprojectPoint
 @abstract Unprojects a screenspace 2D point with depth info using the receiver's current point of view and viewport.
 @param point The screenspace position to be unprojected.
 @discussion A point whose z component is 0 (resp. 1) is unprojected on the near (resp. far) clip plane.
 */
- (SCNVector3)unprojectPoint:(SCNVector3)point API_AVAILABLE(macos(10.9));

/*! 
 @property playing
 @abstract Returns YES if the scene is playing, NO otherwise.
 */
@property(getter=isPlaying) BOOL playing;

/*! 
 @property loops
 @abstract Indicates whether the receiver restarts playback when it reaches the end of its content. Default: YES.
 @discussion YES when the receiver restarts playback when it finishes, NO otherwise.
 */
@property(nonatomic) BOOL loops;

/*! 
 @property pointOfView
 @abstract Specifies the point of view used to render the scene. 
 @discussion A point of view must have either a camera or a spot light attached.
 */
@property(nonatomic, retain, nullable) SCNNode *pointOfView;

/*! 
 @property autoenablesDefaultLighting
 @abstract Specifies whether the receiver should automatically light up scenes that have no light source. The default is NO.
 @discussion When enabled, a diffuse light is automatically added and placed while rendering scenes that have no light or only ambient lights.
 */
@property(nonatomic) BOOL autoenablesDefaultLighting;

/*! 
 @property jitteringEnabled
 @abstract Specifies whether the receiver should jitter the rendered scene to reduce aliasing artifacts. 
 @discussion When enabled, the jittering is performed asynchronously and automatically by SCNView and SCNLayer. It is done synchronously by SCNRenderer.
 */
@property(nonatomic, getter=isJitteringEnabled) BOOL jitteringEnabled;

/*!
 @method prepareObject:shouldAbortBlock:
 @abstract Prepare the specified object for drawing.
 @param object The object to prepare. It can be an instance of SCNScene, SCNNode, SCNGeometry, or SCNMaterial
 @param block This block will be called repeatedly while the object is prepared. Return YES if you want the operation to abort.
 @discussion Returns YES if the object was prepared successfully, NO if it was canceled. This method may be triggered from a secondary thread. This method is observable using NSProgress.
 */
- (BOOL)prepareObject:(id)object shouldAbortBlock:(nullable NS_NOESCAPE BOOL (^)(void))block API_AVAILABLE(macos(10.9));

/*!
 @method prepareObjects:withCompletionHandler:
 @abstract Prepare the specified objects for drawing on the background.
 @param objects The objects to prepare. It can be one or more instances of SCNScene, SCNNode, SCNGeometry, or SCNMaterial
 @param completionHandler This block will be called when all objects has been prepared, or on failure.
 @discussion This method is observable using NSProgress.
 */
- (void)prepareObjects:(NSArray *)objects withCompletionHandler:(nullable void (^)(BOOL success))completionHandler API_AVAILABLE(macos(10.10));

/*!
 @property showsStatistics
 @abstract Determines whether the receiver should display statistics info like FPS. Defaults to NO.
 @discussion  When set to YES, statistics are displayed in a overlay on top of the rendered scene.
 */
@property(nonatomic) BOOL showsStatistics API_AVAILABLE(macos(10.9));

/*!
 @property debugOptions
 @abstract Specifies the debug options of the receiver. Defaults to SCNDebugOptionNone.
 */
@property(nonatomic) SCNDebugOptions debugOptions API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property overlaySKScene
 @abstract Specifies the overlay of the receiver as a SpriteKit scene instance. Defaults to nil.
 */
@property(nonatomic, retain, nullable) SKScene *overlaySKScene API_AVAILABLE(macos(10.10));

/*!
 @property renderingAPI
 @abstract Specifies the rendering API associated to the receiver.
 @discussion This is the rendering API effectively used by the receiver. You can specify a preferred rendering API when initializing a view programmatically (see SCNPreferredRenderingAPI in SCNSceneRenderer.h) or using Interface Builder's SCNView inspector.
 */
@property(nonatomic, readonly) SCNRenderingAPI renderingAPI API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property context
 @abstract A Core OpenGL render context that is used as the render target (a CGLContextObj on macOS, an EAGLContext on iOS).
 */
@property(nonatomic, readonly, nullable) void *context;

#if SCN_ENABLE_METAL

/*!
 @property currentRenderCommandEncoder
 @abstract The current render command encoder if any. This property is only valid within the SCNSceneRendererDelegate methods and when renderering with Metal. Otherwise it is set to nil.
 */
@property(nonatomic, readonly, nullable) id <MTLRenderCommandEncoder> currentRenderCommandEncoder API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property device
 @abstract The metal device of the renderer. This property is only valid on a renderer created with a Metal device. Otherwise it is set to nil.
 */
@property(nonatomic, readonly, nullable) id <MTLDevice> device API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property colorPixelFormat
 @abstract The pixel format of the color attachment 0 of the renderer. This property is only valid on a renderer created with a Metal device.
 */
@property(nonatomic, readonly) MTLPixelFormat colorPixelFormat API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property depthPixelFormat
 @abstract The pixel format of the depth attachment of the renderer. This property is only valid on a renderer created with a Metal device.
 */
@property(nonatomic, readonly) MTLPixelFormat depthPixelFormat API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property stencilPixelFormat
 @abstract The pixel format of the stencil attachment of the renderer. This property is only valid on a renderer created with a Metal device.
 */
@property(nonatomic, readonly) MTLPixelFormat stencilPixelFormat API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property commandQueue
 @abstract The command queue of the renderer. This property is only valid on a renderer created with a Metal device. Otherwise it is set to nil.
 */
@property(nonatomic, readonly, nullable) id <MTLCommandQueue> commandQueue API_AVAILABLE(macos(10.11), ios(9.0));

#endif

/*!
 @property audioEngine
 @abstract Contains the instance of audio engine used by the scene.
 @discussion The audio engine can be used to add custom nodes to the audio graph.
 */
@property(nonatomic, readonly) AVAudioEngine *audioEngine API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property audioEnvironmentNode
 @abstract Contains the instance of audio environment node used by the scene to spacialize sounds.
 */
@property(nonatomic, readonly) AVAudioEnvironmentNode *audioEnvironmentNode API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos);

/*!
 @property audioListener
 @abstract Use this property to set the audio node to use as the listener position and orientation when rendering positional audio for this scene. The default is nil which means that the current point of view will be used dynamically.
 */
@property(nonatomic, retain, nullable) SCNNode *audioListener API_AVAILABLE(macos(10.11), ios(9.0));



@end



/*!
 @protocol SCNSceneRendererDelegate
 @abstract Implement this protocol to perform operations at various times during the rendering
 */
@protocol SCNSceneRendererDelegate <NSObject>
@optional

/*!
 @method renderer:updateAtTime:
 @abstract Implement this to perform per-frame game logic. Called exactly once per frame before any animation and actions are evaluated and any physics are simulated.
 @param renderer The renderer that will render the scene.
 @param time The time at which to update the scene.
 @discussion All modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer updateAtTime:(NSTimeInterval)time API_AVAILABLE(macos(10.10));

/*!
 @method renderer:didApplyAnimationsAtTime:
 @abstract Invoked on the delegate once the scene renderer did apply the animations.
 @param renderer The renderer that did render the scene.
 @param time The time at which the animations were applied.
 @discussion All modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didApplyAnimationsAtTime:(NSTimeInterval)time API_AVAILABLE(macos(10.10));

/*!
 @method renderer:didSimulatePhysicsAtTime:
 @abstract Invoked on the delegate once the scene renderer did simulate the physics.
 @param renderer The renderer that did render the scene.
 @param time The time at which the physics were simulated.
 @discussion All modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didSimulatePhysicsAtTime:(NSTimeInterval)time API_AVAILABLE(macos(10.10));

/*!
 @method renderer:didApplyConstraintsAtTime:
 @abstract Invoked on the delegate once the scene renderer did apply the constraints.
 @param renderer The renderer that did render the scene.
 @param time The time at which the constraints were simulated.
 @discussion All modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didApplyConstraintsAtTime:(NSTimeInterval)time API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @method renderer:willRenderScene:atTime:
 @abstract Invoked on the delegate before the scene renderer renders the scene. At this point the openGL context and the destination framebuffer are bound.
 @param renderer The renderer that will render the scene.
 @param scene The scene to be rendered.
 @param time The time at which the scene is to be rendered.
 @discussion Starting in 10.10 all modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer willRenderScene:(SCNScene *)scene atTime:(NSTimeInterval)time;

/*!
 @method renderer:didRenderScene:atTime:
 @abstract Invoked on the delegate once the scene renderer did render the scene.
 @param renderer The renderer that did render the scene.
 @param scene The rendered scene.
 @param time The time at which the scene was rendered.
 @discussion Starting in 10.10 all modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didRenderScene:(SCNScene *)scene atTime:(NSTimeInterval)time;

@end
    
NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNLight.h
//
//  SCNLight.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNTechnique.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNMaterialProperty;

/*!
 @group Light Types
 @abstract Describes the various light types available.
 */

typedef NSString * SCNLightType NS_STRING_ENUM;
SCN_EXPORT SCNLightType const SCNLightTypeAmbient;                                                                // Ambient light
SCN_EXPORT SCNLightType const SCNLightTypeOmni;                                                                   // Omnidirectional light
SCN_EXPORT SCNLightType const SCNLightTypeDirectional;                                                            // Directional light
SCN_EXPORT SCNLightType const SCNLightTypeSpot;                                                                   // Spot light
SCN_EXPORT SCNLightType const SCNLightTypeIES   API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));               // IES light
SCN_EXPORT SCNLightType const SCNLightTypeProbe API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));               // Light probe

/*! @enum SCNShadowMode
 @abstract The different modes available to compute shadows.
 @discussion When the shadow mode is set to SCNShadowModeForward, shadows are computed while computing the lighting. In this mode only the alpha component of the shadow color is used to alter the lighting contribution.
 When the shadow mode is set to SCNShadowModeDeferred shadows are applied as a post process. Shadows are blend over the final image and can therefor be of any arbitrary color. However it is most of the time less efficient than SCNShadowModeForward, except when a scene has a lot of overdraw.
 When the shadow mode is set to SCNShadowModeModulated the light doesn't illuminate the scene anymore, it only casts shadows. Therefore setting the light color has no effect. In this mode gobos act as a shadow projector: the gobo image is modulated with the shadow receiver's fragments. The typical usage is to use an image of a radial gradient (black to white) that is projected under a character (and use the categoryBitMask of the light and nodes to exclude the character from the shadow receiver).
 */
typedef NS_ENUM(NSInteger, SCNShadowMode) {
    SCNShadowModeForward   = 0,
    SCNShadowModeDeferred  = 1,
    SCNShadowModeModulated = 2
} API_AVAILABLE(macos(10.10));

/*!
 @class SCNLight
 @abstract SCNLight represents a light that can be attached to a SCNNode. 
 */

SCN_EXPORT
@interface SCNLight : NSObject <SCNAnimatable, SCNTechniqueSupport, NSCopying, NSSecureCoding>

/*! 
 @method light
 @abstract Creates and returns a light instance.
 */
+ (instancetype)light;

/*! 
 @property type
 @abstract Specifies the receiver's type.
 @discussion Defaults to SCNLightTypeOmni on iOS 8 and later, and on macOS 10.10 and later (otherwise defaults to SCNLightTypeAmbient).
 */
@property(nonatomic, copy) SCNLightType type;

/*! 
 @property color
 @abstract Specifies the receiver's color (NSColor or CGColorRef). Animatable. Defaults to white.
 @discussion The initial value is a NSColor. The renderer multiplies the light's color is by the color derived from the light's temperature.
 */
@property(nonatomic, retain) id color;

/*!
 @property temperature
 @abstract Specifies the receiver's temperature.
 @discussion This specifies the temperature of the light in Kelvin. The renderer multiplies the light's color by the color derived from the light's temperature. Defaults to 6500 (pure white). Animatable.
 */
@property(nonatomic) CGFloat temperature API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property intensity
 @abstract Specifies the receiver's intensity.
 @discussion This intensity is used to modulate the light color. When used with a physically-based material, this corresponds to the luminous flux of the light, expressed in lumens (lm). Defaults to 1000. Animatable.
 */
@property(nonatomic) CGFloat intensity API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property name
 @abstract Determines the name of the receiver.
 */
@property(nonatomic, copy, nullable) NSString *name;


#pragma mark - Shadow

/*! 
 @property castsShadow
 @abstract Determines whether the receiver casts a shadow. Defaults to NO.
 @discussion Shadows are only supported by spot and directional lights.
 */
@property(nonatomic) BOOL castsShadow;

/*! 
 @property shadowColor
 @abstract Specifies the color (CGColorRef or NSColor) of the shadow casted by the receiver. Defaults to black. Animatable.
 @discussion On iOS 9 or earlier and macOS 10.11 or earlier, this defaults to black 50% transparent.
 */
@property(nonatomic, retain) id shadowColor;

/*!
 @property shadowRadius
 @abstract Specifies the sample radius used to render the receiver’s shadow. Default value is 3.0. Animatable.
 */
@property(nonatomic) CGFloat shadowRadius;

/*!
 @property shadowMapSize
 @abstract Specifies the size of the shadow map.
 @discussion The larger the shadow map is the more precise the shadows are but the slower the computation is. If set to {0,0} the size of the shadow map is automatically chosen. Defaults to {0,0}.
 */
@property(nonatomic) CGSize shadowMapSize API_AVAILABLE(macos(10.10));

/*!
 @property shadowSampleCount
 @abstract Specifies the number of sample per fragment to compute the shadow map. Defaults to 0.
 @discussion On macOS 10.11 or earlier, the shadowSampleCount defaults to 16. On iOS 9 or earlier it defaults to 1.0.
 On macOS 10.12, iOS 10 and greater, when the shadowSampleCount is set to 0, a default sample count is chosen depending on the platform.
 */
@property(nonatomic) NSUInteger shadowSampleCount API_AVAILABLE(macos(10.10));

/*!
 @property shadowMode
 @abstract Specified the mode to use to cast shadows. See above for the available modes and their description. Defaults to SCNShadowModeForward.
 */
@property(nonatomic) SCNShadowMode shadowMode API_AVAILABLE(macos(10.10));

/*!
 @property shadowBias
 @abstract Specifies the correction to apply to the shadow map to correct acne artefacts. It is multiplied by an implementation-specific value to create a constant depth offset. Defaults to 1.0
 */
@property(nonatomic) CGFloat shadowBias API_AVAILABLE(macos(10.10));

/*!
 @property automaticallyAdjustsShadowProjection
 @abstract Specifies if the shadow map projection should be done automatically or manually by the user. Defaults to YES.
 */
@property(nonatomic) BOOL automaticallyAdjustsShadowProjection API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property maximumShadowDistance
 @abstract Specifies the maximum distance from the viewpoint from which the shadows for the receiver light won't be computed. Defaults to 100.0.
 */
@property(nonatomic) CGFloat maximumShadowDistance API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property forcesBackFaceCasters
 @abstract Render only back faces of the shadow caster when enabled. Defaults to NO.
 This is a behavior change from previous releases.
 */
@property(nonatomic) BOOL forcesBackFaceCasters API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property sampleDistributedShadowMaps
 @abstract Use the sample distribution of the main rendering to better fit the shadow frusta. Defaults to NO.
 */
@property(nonatomic) BOOL sampleDistributedShadowMaps API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property shadowCascadeCount
 @abstract Specifies the number of distinct shadow maps that will be computed for the receiver light. Defaults to 1. Maximum is 4.
 */
@property(nonatomic) NSUInteger shadowCascadeCount API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property shadowCascadeSplittingFactor
 @abstract Specifies a factor to interpolate between linear splitting (0) and logarithmic splitting (1). Defaults to 0.15.
 */
@property(nonatomic) CGFloat shadowCascadeSplittingFactor API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));


#pragma mark - Light projection settings for shadows

/*!
 @property orthographicScale
 @abstract Specifies the orthographic scale used to render from the directional light into the shadow map. Defaults to 1.
 @discussion This is only applicable for directional lights.
 */
@property(nonatomic) CGFloat orthographicScale API_AVAILABLE(macos(10.10));

/*!
 @property zNear
 @abstract Specifies the minimal distance between the light and the surface to cast shadow on. If a surface is closer to the light than this minimal distance, then the surface won't be shadowed. The near value must be different than zero. Animatable. Defaults to 1.
 */
@property(nonatomic) CGFloat zNear API_AVAILABLE(macos(10.10));

/*!
 @property zFar
 @abstract Specifies the maximal distance between the light and a visible surface to cast shadow on. If a surface is further from the light than this maximal distance, then the surface won't be shadowed. Animatable. Defaults to 100.
 */
@property(nonatomic) CGFloat zFar API_AVAILABLE(macos(10.10));


#pragma mark - Attenuation

/*!
 @property attenuationStartDistance
 @abstract The distance at which the attenuation starts (Omni or Spot light types only). Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat attenuationStartDistance API_AVAILABLE(macos(10.10));

/*!
 @property attenuationEndDistance
 @abstract The distance at which the attenuation ends (Omni or Spot light types only). Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat attenuationEndDistance API_AVAILABLE(macos(10.10));

/*!
 @property attenuationFalloffExponent
 @abstract Specifies the attenuation between the start and end attenuation distances. 0 means a constant attenuation, 1 a linear attenuation and 2 a quadratic attenuation, but any positive value will work (Omni or Spot light types only). Animatable. Defaults to 2.
 */
@property(nonatomic) CGFloat attenuationFalloffExponent API_AVAILABLE(macos(10.10));


#pragma mark - Spot light parameters

/*!
 @property spotInnerAngle
 @abstract The angle in degrees between the spot direction and the lit element below which the lighting is at full strength. Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat spotInnerAngle API_AVAILABLE(macos(10.10));

/*!
 @property spotOuterAngle
 @abstract The angle in degrees between the spot direction and the lit element after which the lighting is at zero strength. Animatable. Defaults to 45 degrees.
 */
@property(nonatomic) CGFloat spotOuterAngle API_AVAILABLE(macos(10.10));


#pragma mark - IES light parameters

/*!
 @property IESProfileURL
 @abstract Specifies the IES file from which the shape, direction, and intensity of illumination is determined. Defaults to nil.
 */
@property(nonatomic, retain, nullable) NSURL *IESProfileURL API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));


#pragma mark - Light probes parameters

/*!
 @property sphericalHarmonicsCoefficients
 @abstract The receiver's spherical harmonics coefficients.
 @discussion Currently spherical harmonics are only supported by light probes (SCNLightTypeProbe). The data is an array of 27 32-bit floating-point values, containing three non-interleaved data sets corresponding to the red, green, and blue sets of coefficients.
 */
@property(nonatomic, copy, readonly) NSData *sphericalHarmonicsCoefficients API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));


#pragma mark - Other

/*!
 @property gobo
 @abstract Specifies the gobo (or "cookie") of the light, used to control the shape of emitted light. Defaults to nil.
 @discussion Gobos are only supported by spot lights.
 */
@property(nonatomic, readonly, nullable) SCNMaterialProperty *gobo API_AVAILABLE(macos(10.9));

/*!
 @property categoryBitMask
 @abstract Determines the node categories that will be lit by the receiver. Defaults to all bit set.
 */
@property(nonatomic) NSUInteger categoryBitMask API_AVAILABLE(macos(10.10));



@end


NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNBoundingVolume.h
//
//  SCNBoundingVolume.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

/*!
 @protocol SCNBoundingVolume
 @abstract The SCNBoundingVolume protocol is implemented by objects which can compute their bounding boxes.
 @discussion You can currently use this protocol to get the bounding boxes of nodes and geometries.
 */

NS_ASSUME_NONNULL_BEGIN

@protocol SCNBoundingVolume <NSObject>
@required

/*! 
 @method getBoundingBoxMin:max:
 @abstract Fill the min and max vectors with the min and max vertex of the bounding box.
 @param min A pointer to a SCNVector3 to store the min vertex of the bounding box into.
 @param max A pointer to a SCNVector3 to store the max vertex of the bounding box into.
 @discussion the returned bounding box is in local space of the receiver.
 */
- (BOOL)getBoundingBoxMin:(nullable SCNVector3 *)min max:(nullable SCNVector3 *)max NS_REFINED_FOR_SWIFT;

/*!
 @method setBoundingBoxMin:max:
 @abstract Override the receiver bounding box with the min and max vectors provided (in local space of the receiver).
 @param min A pointer to a SCNVector3 representing the min vertex of the desired bounding box.
 @param max A pointer to a SCNVector3 representing the max vertex of the desired bounding box.
 @discussion Passing nil as arguments will recompute the original bounding box of the receiver.
 */
- (void)setBoundingBoxMin:(nullable SCNVector3 *)min max:(nullable SCNVector3 *)max API_AVAILABLE(macos(10.9)) NS_REFINED_FOR_SWIFT;

/*!
 @method getBoundingSphereCenter:radius:
 @abstract Fill the center vector with the center of the bounding sphere and store the radius of the bounding sphere in 'radius'.
 @param center A pointer to a SCNVector3 to store the center of the bounding sphere into.
 @param radius A pointer to a CGFloat to store the radius of the bounding sphere into.
 @discussion the returned bounding sphere is in local space of the receiver.
 */
- (BOOL)getBoundingSphereCenter:(nullable SCNVector3 *)center radius:(nullable CGFloat *)radius NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNCameraController.h
//
//  SCNCameraController.h
//  SceneKit
//
//  Copyright (c) 2017-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;
@class SCNCameraController;

// SCNInteractionMode specify the behavior of the camera relative to
// screen space interactions.
typedef NS_ENUM(NSInteger, SCNInteractionMode) {
    // Relative to up vector.
    SCNInteractionModeFly,
    SCNInteractionModeOrbitTurntable,            // rotate around target with absolute orientation from angles accumulation.
    // Up vector not taken into account.
    SCNInteractionModeOrbitAngleMapping,         // rotate around target by mapping 2D screen coordinates to spherical coordinates.
    SCNInteractionModeOrbitCenteredArcball,
    SCNInteractionModeOrbitArcball,              // rotate around target by mapping 2D screen coordinates to an half sphere.
    SCNInteractionModePan,                       // camera space translation on X/Y
    SCNInteractionModeTruck,                     // camera space translation on X/Z
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@protocol SCNCameraControllerDelegate <NSObject>

@optional
- (void)cameraInertiaWillStartForController:(SCNCameraController *)cameraController;
- (void)cameraInertiaDidEndForController:(SCNCameraController *)cameraController;

@end

SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNCameraController : NSObject

@property(nonatomic, assign, nullable) id <SCNCameraControllerDelegate> delegate;

@property(nonatomic, retain, nullable) SCNNode *pointOfView;
@property(nonatomic) SCNInteractionMode interactionMode;

// The camera target in world space for orbit rotation.
@property(nonatomic) SCNVector3 target;

// Automatically update the target in beginInteraction
// Defaults to NO
@property(nonatomic) BOOL automaticTarget;

// The up vector in world space used as reference for SCNInteractionModeFly and SCNInteractionModeOrbitTurntable camera modes.
// Defaults to (0, 1, 0).
@property(nonatomic) SCNVector3 worldUp;

// Set to YES to enable inertia on endInteraction.
// Defaults to NO.
@property(nonatomic) BOOL inertiaEnabled;

// The friction coefficient applied to the inertia.
// Defaults to 0.05.
@property(nonatomic) float inertiaFriction;

// Returns YES if inertia is running.
@property(nonatomic, readonly, getter=isInertiaRunning) BOOL inertiaRunning;

// Minimum and maximum vertical view angles in degrees for SCNInteractionModeFly and SCNInteractionModeOrbitTurntable.
// The angle constraints is not enforced if both vertical angle properties values are set to 0.
// The angle constraints will not be enforced if the initial orientation is outside the given range.
// The minimum angle must be inferior to the maximum angle.
// Angles are in world space and within the range [-90, 90].
// Defaults to 0.0.
// For example: set to minimum to 0 and maximum to 90 to only allow orbit around the top hemisphere.
@property(nonatomic) float minimumVerticalAngle;
@property(nonatomic) float maximumVerticalAngle;

// Minimum and maximum horizontal view angles in degrees for SCNInteractionModeFly and SCNInteractionModeOrbitTurntable.
// The angle constraints is not enforced if both horizontal angle properties values are set to 0.
// The angle constraints will not be enforced if the initial orientation is outside the given range.
// The minimum angle must be inferior to the maximum angle.
// Angles are in world space and within the range [-180, 180].
// Defaults to 0.0.
@property(nonatomic) float minimumHorizontalAngle;
@property(nonatomic) float maximumHorizontalAngle;

// Translate the camera along the local X/Y/Z axis.
- (void)translateInCameraSpaceByX:(float)deltaX Y:(float)deltaY Z:(float)deltaX;

// Move the camera to a position where the bounding sphere of all nodes is fully visible.
// Also set the camera target as the center of the bounding sphere.
- (void)frameNodes:(NSArray<SCNNode *> *)nodes;

// Rotate delta is in degrees.
- (void)rotateByX:(float)deltaX Y:(float)deltaY;

// Rotate the camera around the given screen space point. Delta is in degrees.
- (void)rollBy:(float)delta aroundScreenPoint:(CGPoint)point viewport:(CGSize)viewport;

// Zoom by moving the camera along the axis by a screen space point.
- (void)dollyBy:(float)delta onScreenPoint:(CGPoint)point viewport:(CGSize)viewport;

// Rotate the camera around the axis from the camera position to the target.
// Delta is in degrees.
- (void)rollAroundTarget:(float)delta;

// Zoom by moving the camera along the axis from the camera position to the target.
- (void)dollyToTarget:(float)delta;

// clear the camera roll if any
- (void)clearRoll;

// Stop current inertia.
- (void)stopInertia;

// Begin/Continue/End interaction using an input location relative to viewport.
// The behavior depends on the current interactionMode.
- (void)beginInteraction:(CGPoint)location withViewport:(CGSize)viewport;
- (void)continueInteraction:(CGPoint)location withViewport:(CGSize)viewport sensitivity:(CGFloat)sensitivity;
- (void)endInteraction:(CGPoint)location withViewport:(CGSize)viewport velocity:(CGPoint)velocity;

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNAudioSource.h
//
//  SCNAudioSource.h
//  SceneKit
//
//  Copyright © 2015-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SCNNode.h>

NS_ASSUME_NONNULL_BEGIN

@class AVAudioNode;

/*!
 @class SCNAudioSource
 @abstract The SCNAudioSource class represents an audio source that can be added to a SCNNode.
 */
SCN_EXPORT API_AVAILABLE(macos(10.11), ios(9.0))
@interface SCNAudioSource : NSObject <NSCopying, NSSecureCoding>

/*!
 @method initWithFileNamed:
 @abstract Convenience initializer that creates an AVAudioNode from the named audio asset in the main bundle.
 */
- (nullable instancetype)initWithFileNamed:(NSString *)name;

/*!
 @method initWithURL:
 @abstract Convenience initializer that creates an AVAudioNode from the URL that contain a audio asset.
 */
- (nullable instancetype)initWithURL:(NSURL *)url NS_DESIGNATED_INITIALIZER;

/*!
 @method audioSourceNamed:
 @abstract Convenience class initializer that caches audioSources.
 */
+ (nullable instancetype)audioSourceNamed:(NSString *)fileName;

/*!
 @property positional
 @abstract Marks the audio source as positional so that the audio mix considers relative position and velocity with regards to the SCNSceneRenderer's current listener node. Defaults to YES.
 @discussion shouldStream must be set to false in order to get positional audio (see shouldStream).
 @see SCNSceneRenderer audioListener.
 */
@property(nonatomic, getter=isPositional) BOOL positional;

/*!
 @property volume
 @abstract The default volume for this audio buffer. Default is 1.0 (full volume).
 */
@property(nonatomic) float volume;

/*!
 @property rate
 @abstract The default rate for this audio buffer. Default is 1.0 (original rate of the audio source).
 */
@property(nonatomic) float rate;

/*!
 @property reverbBlend
 @abstract The default reverbBlend for this audio buffer. Default is 0.0 (no sound is sent to the reverb).
 */
@property(nonatomic) float reverbBlend;

/*!
 @property loops
 @abstract Specifies whether the audio source should loop or not. Defaults to NO.
 */
@property(nonatomic) BOOL loops;

/*!
 @property shouldStream
 @abstract Specifies whether the audio source should be streamed or not. Defaults to NO.
 */
@property(nonatomic) BOOL shouldStream;

/*!
 @method load
 @abstract Load and uncompress the audio source in memory. This method has no effect if "shouldStream" is set to YES or if the audio source is already loaded.
 @discussion This method let you preload your audio sources. If an audio source is not preloaded, it will be loaded anyway when playing it.
 */
- (void)load;

@end

SCN_EXPORT API_AVAILABLE(macos(10.11), ios(9.0))
@interface SCNAudioPlayer : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 @property initWithSource:
 @abstract Init an audio player with a source. Most people should use audioPlayerWithSource as it permits to recycle previous players instead of creating new ones for each instance.
 */
- (instancetype)initWithSource:(SCNAudioSource *)source NS_DESIGNATED_INITIALIZER;

/*!
 @property initWithAVAudioNode:
 @abstract Init an audio player with an AVAudioNode. Most people should use audioPlayerWithAVAudioNode as it permits to recycle previous players instead of creating new ones for each instance.
 */
- (instancetype)initWithAVAudioNode:(AVAudioNode *)audioNode NS_DESIGNATED_INITIALIZER;

/*!
 @property audioPlayerWithSource:
 @abstract Create an audio player with a source.
 */
+ (instancetype)audioPlayerWithSource:(SCNAudioSource *)source;

/*!
 @property audioPlayerWithAVAudioNode:
 @abstract Create an audio player with a custom AVAudioNode instance.
 */
+ (instancetype)audioPlayerWithAVAudioNode:(AVAudioNode *)audioNode;

/*!
 @property playbackStarted
 @abstract This block is called when the playback starts in case a valid audio source is present.
 */
@property(nonatomic, copy, nullable) void (^willStartPlayback)(void);

/*!
 @property playbackFinished
 @abstract This block is called when the playback stops in case a valid audio source is present.
 */
@property(nonatomic, copy, nullable) void (^didFinishPlayback)(void);

/*!
 @property audioNode
 @abstract The audioNode. If this player was not initialised with a custom AVAudioNode this contains the internal audio player node used by scene kit internally.
 */
@property(nonatomic, readonly, nullable) AVAudioNode *audioNode;

/*!
 @property audioSource
 @abstract The audioSource if there is one.
 */
@property(nonatomic, readonly, nullable) SCNAudioSource *audioSource;

@end


@interface SCNNode (SCNAudioSupport)

/*!
 @method addAudioPlayer:
 @abstract Add an audio player to the node and starts playing it right away.
 */
- (void)addAudioPlayer:(SCNAudioPlayer *)player API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method removeAllAudioPlayers
 @abstract Remove all audio players from this node and stop playing them.
 */
- (void)removeAllAudioPlayers API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method removeAudioPlayer:
 @abstract Remove the given audio player from this node and stop playing it.
 */
- (void)removeAudioPlayer:(SCNAudioPlayer *)player API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property audioPlayers
 @abstract Get an array with all the audio players connected and playing on this node.
 */
@property(nonatomic, readonly) NSArray<SCNAudioPlayer *> *audioPlayers API_AVAILABLE(macos(10.11), ios(9.0));

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNAnimation.h
//
//  SCNAnimation.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

#import <QuartzCore/QuartzCore.h>

@class SCNAnimation, SCNAnimationEvent, SCNAnimationPlayer;
@protocol SCNAnimatable;

@protocol SCNAnimation <NSObject>
@end

#import <SceneKit/SCNCAAnimationExtensions.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^SCNAnimationDidStartBlock)(SCNAnimation *animation, id <SCNAnimatable> receiver);
typedef void (^SCNAnimationDidStopBlock)(SCNAnimation *animation, id <SCNAnimatable> receiver, BOOL completed);

SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNTimingFunction : NSObject <NSSecureCoding>
+ (SCNTimingFunction *)functionWithTimingMode:(SCNActionTimingMode)timingMode;
+ (SCNTimingFunction *)functionWithCAMediaTimingFunction:(CAMediaTimingFunction *)caTimingFunction;
@end

/*!
 @protocol SCNAnimatable
 @abstract The SCNAnimatable protocol defines an animatable property. Objects that implement this protocol can be animated through these methods.
 */
@protocol SCNAnimatable <NSObject>

/*!
 @method addAnimation:forKey:
 @abstract Adds and runs an animation
 @param animation Added animation.
 @param key May be any string such that only one animation per unique key is added per animatable object.
 @discussion Only SCNAnimation (preferred), CABasicAnimation, CAKeyframeAnimation and CAAnimationGroup are supported.
 The animation starts playing right away. The animation is automatically removed on completion unless if removedOnCompletion is explicitly set to NO. 
 @seealso -[id <SCNAnimation> removedOnCompletion]
 */
- (void)addAnimation:(id <SCNAnimation>)animation forKey:(nullable NSString *)key;

/*!
 @method addAnimationPlayer:forKey:
 @abstract Add an animation player.
 @param player Added animation player.
 @param key May be any string such that only one animation per unique key is added per animatable object.
 @discussion The animation player is not removed automatically on completion.
 The animation doesn't start playing immediatelly. Call "play" on the player to start playing it.
 @seealso -[SCNAnimationPlayer play]
 */
- (void)addAnimationPlayer:(SCNAnimationPlayer *)player forKey:(nullable NSString *)key API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @method removeAllAnimations
 @abstract Remove all animations.
 */
- (void)removeAllAnimations;

/*!
 @method removeAnimationForKey
 @abstract Remove the animation with the given identifier.
 @param key The identifier for the animation to remove.
 */
- (void)removeAnimationForKey:(NSString *)key;

/*!
 @property animationKeys
 @abstract Returns an array containing the keys of all animations currently attached to the receiver.
 */
@property(readonly) NSArray<NSString *> *animationKeys;

/*!
 @method animationPlayerForKey:
 @abstract Returns the animation player with the given identifier
 @param key The identifier for the animation player to retrieve.
 @discussion This will return nil if no such animation player exists.
 */
- (nullable SCNAnimationPlayer *)animationPlayerForKey:(NSString *)key API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Smoothly remove the animation with the given identifier.
 @param key The identifier for the animation to remove.
 @param duration The blend out duration used to remove the animation.
 */
- (void)removeAnimationForKey:(NSString *)key blendOutDuration:(CGFloat)duration API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));


// Deprecated

/*!
 @method removeAnimationForKey:fadeOutDuration:
 @abstract Smoothly remove the animation with the given identifier.
 @param key The identifier for the animation to remove.
 @param duration The fade out duration used to remove the animation.
 */
- (void)removeAnimationForKey:(NSString *)key fadeOutDuration:(CGFloat)duration API_DEPRECATED_WITH_REPLACEMENT("-removeAnimationForKey:blendOutDuration:", macos(10.10, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @method animationForKey:
 @abstract Returns the animation with the given identifier
 @param key The identifier for the animation to retrieve.
 @discussion This will return nil if no such animation exists.
 Attempting to modify any properties of the returned object will result in undefined behavior.
 */
- (nullable CAAnimation *)animationForKey:(NSString *)key API_DEPRECATED_WITH_REPLACEMENT("-animationPlayerForKey:", macos(10.8, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0));

/*!
 @method pauseAnimationForKey:
 @abstract Pause the animation with the given identifier.
 @param key The identifier for the animation to pause.
 */
- (void)pauseAnimationForKey:(NSString *)key API_DEPRECATED("Use -[SCNAnimationPlayer setPaused:] instead", macos(10.9, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @method resumeAnimationForKey:
 @abstract Resume the animation with the given identifier.
 @param key The identifier for the animation to resume.
 */
- (void)resumeAnimationForKey:(NSString *)key API_DEPRECATED("Use -[SCNAnimationPlayer setPaused:] instead", macos(10.9, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @method setSpeed:forAnimationKey:
 @abstract Update the animation speed of the animation with the given identifier.
 @param speed The new speed of the animation.
 @param key The identifier for the animation to update.
 */
- (void)setSpeed:(CGFloat)speed forAnimationKey:(NSString *)key API_DEPRECATED("Use -[SCNAnimationPlayer setSpeed:] instead", macos(10.12, 10.13), ios(10.0, 11.0), tvos(10.0, 11.0), watchos(3.0, 4.0));

/*!
 @method isAnimationForKeyPaused:
 @abstract Returns whether the animation for the specified identifier is paused.
 @param key The identifier for the animation to query.
 */
- (BOOL)isAnimationForKeyPaused:(NSString *)key API_DEPRECATED("Use -[SCNAnimationPlayer paused] instead", macos(10.9, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

@end



/**
 SCNAnimation represents an animation that targets a specific key path.
 */
SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNAnimation : NSObject <SCNAnimation, NSCopying, NSSecureCoding>


/*!
 Initializers
 */

/**
 Loads and returns an animation loaded from the specified URL.
 
 @param animationUrl The url to load.
 */
+ (SCNAnimation *)animationWithContentsOfURL:(NSURL *)animationUrl;

/**
 Loads and returns the animation with the specified name in the current application bundle.

 @param animationName The name of the animation to load.
 */
+ (SCNAnimation *)animationNamed:(NSString *)animationName;

// bridge with Core Animation
/**
 Returns a SCNAnimation initialized from a CAAnimation.

 @param caAnimation The CAAnimation to initialize from.
 @discussion Only CABasicAnimation, CAKeyframeAnimation and CAAnimationGroup are currently supported.
 */
+ (SCNAnimation *)animationWithCAAnimation:(CAAnimation *)caAnimation;



/*!
 Basic properties
 */

/**
 The duration of the animation in seconds. Defaults to 0.
 */
@property(nonatomic) NSTimeInterval duration;

/**
 The key-path describing the property to be animated for single-property animations, nil for animations targetting multiple nodes. defaults to nil.
 The key-path uses the KVC syntax. It's also possible to target a specific sub-node with the following syntax:
    /<node-name>.property1.property2.field    (field is optional, <node-name> is the name of the targeted node).
 */
@property(nonatomic, copy, nullable) NSString *keyPath;

/**
 A timing function defining the pacing of the animation. Defaults to nil indicating linear pacing.
 */
@property(nonatomic, retain) SCNTimingFunction *timingFunction;



/*!
 Blending
 */

/**
 Determines the receiver's blend-in duration.
 @discussion When the blendInDuration is greater than zero, the effect of the animation progressively increase from 0% to 100% during the specified duration.
 */
@property(nonatomic) NSTimeInterval blendInDuration;

/**
 Determines the receiver's blend-out duration.
 @discussion When the blendOutDuration is greater than zero, the effect of the animation progressively decrease from 100% to 0% at the end of the animation duration.
 */
@property(nonatomic) NSTimeInterval blendOutDuration;



/*!
 Animation behaviors
 */

/**
 When true, the animation is removed from the render tree once its active duration has passed. Defaults to YES. 
 */
@property(nonatomic, getter=isRemovedOnCompletion) BOOL removedOnCompletion;

/**
 When true, the animation is applied to the model tree once its active duration has passed. Defaults to NO.
 */
@property(nonatomic, getter=isAppliedOnCompletion) BOOL appliedOnCompletion;



/*!
 Repeat
 */

/**
 The repeat count of the object. May be fractional. Defaults to 0.
 */
@property(nonatomic) CGFloat repeatCount;
/**
 When true, the object plays backwards after playing forwards. Defaults to NO.
 */
@property(nonatomic) BOOL autoreverses;



/*!
 Delay and offset
 */

/**
 The relative delay to start the animation, in relation to its parent animation if applicable. Defaults to 0.
 @discussion This property is bridged with CoreAnimations's beginTime. However, for top level animations, startDelay relative to the current time (unlike CAAnimation's beginTime that is absolute). So if a CAAnimation has a non-zero beginTime, startDelay is initialized as caAnimation.beginTime - CACurrentMediaTime().
 */
@property(nonatomic) NSTimeInterval startDelay;

/**
 Additional offset in active local time. i.e. to convert from parent
 time tp to active local time t: t = (tp - begin) * speed + offset.
 Defaults to 0.
 */
@property(nonatomic) NSTimeInterval timeOffset;



/*!
 Fill mode
 */

/**
 When true, the animation remains active after its active duration and evaluates to its end value. Defaults to NO.
 */
@property(nonatomic) BOOL fillsForward;

/**
 When true, the animation is active before its active duration and evaluates to its start value. Defaults to NO.
 */
@property(nonatomic) BOOL fillsBackward;

/**
 Determines whether the receiver is evaluated using the scene time or the system time. Defaults to NO.
 @discussion A scene-time based animation is evaluated using the "sceneTime" value of the renderer that renders the scene.
 The "sceneTime" base is typically used by players or editors that need to preview, edit and being able to change the evaluation time.
 @see SCNSceneSourceAnimationImportPolicyKey
 */
@property(nonatomic) BOOL usesSceneTimeBase;


/*!
 Notifications & events
 */

/**
 Called when the animation starts.
 */
@property(nonatomic, copy, nullable) SCNAnimationDidStartBlock animationDidStart;

/**
 Called when the animation either completes its active duration or
 is removed from the object it is attached to (i.e. the layer). The 'completed' argument of SCNAnimationDidStopBlock
 is true if the animation reached the end of its active duration without being removed.
 */
@property(nonatomic, copy, nullable) SCNAnimationDidStopBlock animationDidStop;

/**
 Specifies the animation events attached to the receiver.
 @see SCNAnimationEvent
 */
@property(nonatomic, copy, nullable) NSArray<SCNAnimationEvent *> *animationEvents;

/*!
 Additive and cumulative
 */

/**
 When true the value specified by the animation will be "added" to
 the current presentation value of the property to produce the new
 presentation value. The addition function is type-dependent, e.g.
 for affine transforms the two matrices are concatenated. Defaults to
 NO. */
@property(nonatomic, getter=isAdditive) BOOL additive;

/**
 The `cumulative' property affects how repeating animations produce
 their result. If true then the current value of the animation is the
 value at the end of the previous repeat cycle, plus the value of the
 current repeat cycle. If false, the value is simply the value
 calculated for the current repeat cycle. Defaults to NO. 
 */
@property(nonatomic, getter=isCumulative) BOOL cumulative;

@end



/**
 SCNAnimationPlayer let you control when and how to play and blend an animation
 */
SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNAnimationPlayer : NSObject  <SCNAnimatable, NSCopying, NSSecureCoding>

/**
 Initialize an animation player with an animation
 @param animation The animation to play
 */
+ (SCNAnimationPlayer *)animationPlayerWithAnimation:(SCNAnimation *)animation;

/**
 The played animation
 */
@property(nonatomic, readonly) SCNAnimation *animation;

/**
 The speed to play the animation at. Defaults to 1.0. Animatable
 */
@property(nonatomic) CGFloat speed;

/**
 Controls the influence of the played animation. When set to 1 the animation is applied without any blending. When set to less than 1, the animation value is blent with the current presentation value of the animated property. Defaults to 1.0. Animatable.
 */
@property(nonatomic) CGFloat blendFactor;

/**
 Specifies if the animation is paused. Defaults to NO.
 */
@property(nonatomic) BOOL paused;

/*!
 Actions
 */

/**
 Set paused to NO and restart playing from the beginning of the animation.
 */
- (void)play;

/**
 Stop the animation.
 */
- (void)stop;

/**
 Stop the animation and smoothly blend out the animation over the specified duration.
 */
- (void)stopWithBlendOutDuration:(NSTimeInterval)duration;

@end


/**
 Signature for the block executed when the animation event is triggered.
 */
typedef void (^SCNAnimationEventBlock)(id <SCNAnimation> animation, id animatedObject, BOOL playingBackward);


/**
 SCNAnimationEvent encapsulates a block to trigger at a specific time.
 */
SCN_EXPORT API_AVAILABLE(macos(10.9))
@interface SCNAnimationEvent : NSObject

/*!
 @method animationEventWithKeyTime:block:
 @abstract Returns an animation event instance
 @param time The relative time to trigger the event.
 @param eventBlock The block to call when the event is triggered.
 @discussion "time" is relative to animation duration and therefor it has to be a value in the range [0,1].
 */
+ (instancetype)animationEventWithKeyTime:(CGFloat)time block:(SCNAnimationEventBlock)eventBlock;

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNLevelOfDetail.h
//
//  SCNLevelOfDetail.h
//  SceneKit
//
//  Copyright © 2013-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNGeometry.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class SCNLevelOfDetail
 @abstract SCNLevelOfDetail represents a level of detail of a geometry.
 */
SCN_EXPORT API_AVAILABLE(macos(10.9))
@interface SCNLevelOfDetail : NSObject <NSCopying, NSSecureCoding>

/*!
 @method levelOfDetailWithGeometry:screenSpaceRadius:
 @abstract This is a convenience method to create a level of detail with a coverage radius threshold mode.
 @param geometry The geometry for this level of detail. nil is supported and indicates that no geometry should be rendered for this level of detail.
 @param radius The maximum radius in screen-space that this level of detail is suitable for. The coverage radius is calculated from the projected bounding sphere and expressed in pixels.
 */
+ (instancetype)levelOfDetailWithGeometry:(nullable SCNGeometry *)geometry screenSpaceRadius:(CGFloat)radius;

/*!
 @method levelOfDetailWithGeometry:worldSpaceDistance:
 @abstract This is a convenience method to create a level of detail with a distance threshold mode.
 @param geometry The geometry for this level of detail. nil is supported and indicates that no geometry should be rendered for this level of detail.
 @param distance The minimum distance to the current point of view that this level of detail is suitable for.
 */
+ (instancetype)levelOfDetailWithGeometry:(nullable SCNGeometry *)geometry worldSpaceDistance:(CGFloat)distance;

/*!
 @property geometry
 @abstract Returns the geometry of the receiver.
 */
@property(readonly, nullable) SCNGeometry *geometry;

/*!
 @property screenSpaceRadius
 @abstract Returns the screen space radius of the receiver if any, 0 otherwise.
 */
@property(readonly) CGFloat screenSpaceRadius;

/*!
 @property worldSpaceDistance
 @abstract Returns the world space distance of the receiver if any, 0 otherwise.
 */
@property(readonly) CGFloat worldSpaceDistance;

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNPhysicsBehavior.h
//
//  SCNPhysicsBehavior.h
//  SceneKit
//
//  Copyright © 2014-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;
@class SCNPhysicsBody;

/*!
 @class SCNPhysicsBehavior
 @abstract SCNPhysicsBehavior is an abstract class that represents a behavior in the physics world.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsBehavior : NSObject <NSSecureCoding>
@end

/*!
 @class SCNPhysicsHingeJoint
 @abstract SCNPhysicsHingeJoint makes two bodies to move like they are connected by a hinge. It is for example suitable for doors, chains...
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsHingeJoint : SCNPhysicsBehavior

//Initializes and returns a physics hinge joint.
//The hinge attaches bodyA and bodyB on anchorA and anchorB respectively. "axisA" and "axisB" specify the axis of rotation for bodyA and bodyB.
+ (instancetype)jointWithBodyA:(SCNPhysicsBody *)bodyA axisA:(SCNVector3)axisA anchorA:(SCNVector3)anchorA bodyB:(SCNPhysicsBody *)bodyB axisB:(SCNVector3)axisB anchorB:(SCNVector3)anchorB;

//Initializes and returns a physics hinge joint.
//The hinge attaches body to a specific location in 3d space specified by "anchor" and relative to the node that owns the body. "axis" specifies the axis of rotation for "body".
+ (instancetype)jointWithBody:(SCNPhysicsBody *)body axis:(SCNVector3)axis anchor:(SCNVector3)anchor;

@property(nonatomic, readonly) SCNPhysicsBody *bodyA; //the first body constrained by the hinge
@property(nonatomic) SCNVector3 axisA;                //the axis of rotation of bodyA
@property(nonatomic) SCNVector3 anchorA;              //the anchor point on which bodyA is attached

@property(nonatomic, readonly, nullable) SCNPhysicsBody *bodyB; //the second body attached to the hinge.
@property(nonatomic) SCNVector3 axisB;                          //the axis of rotation of bodyB
@property(nonatomic) SCNVector3 anchorB;                        //the anchor point on which bodyB is attached

@end

/*!
 @class SCNPhysicsBallSocketJoint
 @abstract SCNPhysicsBallSocketJoint makes two bodies to move like they are connected by a ball-and-socket joint (i.e it allows rotations around all axes).
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsBallSocketJoint : SCNPhysicsBehavior

//Initializes and returns a physics ball-and-socket joint.
//The joint attaches bodyA and bodyB on anchorA and anchorB respectively.
+ (instancetype)jointWithBodyA:(SCNPhysicsBody *)bodyA anchorA:(SCNVector3)anchorA bodyB:(SCNPhysicsBody *)bodyB anchorB:(SCNVector3)anchorB;

//Initializes and returns a physics ball-and-socket joint.
//The joint attaches "body" to the 3d location specified by "anchor" and relative to the node that owns the body.
+ (instancetype)jointWithBody:(SCNPhysicsBody *)body anchor:(SCNVector3)anchor;

@property(nonatomic, readonly) SCNPhysicsBody *bodyA; //the first body attached to the ball-and-socket joint
@property(nonatomic) SCNVector3 anchorA;              //the attach point of bodyA

@property(nonatomic, readonly, nullable) SCNPhysicsBody *bodyB; //the second body attached to the ball-and-socket joint
@property(nonatomic) SCNVector3 anchorB;                        //the attach point of bodyB

@end

/*!
 @class SCNPhysicsSliderJoint
 @abstract SCNPhysicsSliderJoint provides a linear sliding joint between two bodies.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsSliderJoint : SCNPhysicsBehavior

//Initializes and returns a physics slider joint.
//The joint attaches bodyA and bodyB on anchorA and anchorB respectively.
+ (instancetype)jointWithBodyA:(SCNPhysicsBody *)bodyA axisA:(SCNVector3)axisA anchorA:(SCNVector3)anchorA bodyB:(SCNPhysicsBody *)bodyB axisB:(SCNVector3)axisB anchorB:(SCNVector3)anchorB;

//Initializes and returns a physics slider joint.
//The joint attaches "body" to the 3d location specified by "anchor" and relative to the node that owns the body.
+ (instancetype)jointWithBody:(SCNPhysicsBody *)body axis:(SCNVector3)axis anchor:(SCNVector3)anchor;

@property(nonatomic, readonly) SCNPhysicsBody *bodyA; //the first body attached to the slider joint
@property(nonatomic) SCNVector3 axisA;                //the axis on which bodyA can slide
@property(nonatomic) SCNVector3 anchorA;              //the attach point of bodyA

@property(nonatomic, readonly, nullable) SCNPhysicsBody *bodyB; //the second body attached to the slider joint
@property(nonatomic) SCNVector3 axisB;                          //the axis on which bodyB can slide
@property(nonatomic) SCNVector3 anchorB;                        //the attach point of bodyB

//The minimum and maximum linear/angular limits in radians
@property(nonatomic) CGFloat minimumLinearLimit;
@property(nonatomic) CGFloat maximumLinearLimit;

@property(nonatomic) CGFloat minimumAngularLimit;
@property(nonatomic) CGFloat maximumAngularLimit;

//Linear and angular motors in newtons
@property(nonatomic) CGFloat motorTargetLinearVelocity;
@property(nonatomic) CGFloat motorMaximumForce;

@property(nonatomic) CGFloat motorTargetAngularVelocity;
@property(nonatomic) CGFloat motorMaximumTorque;

@end

/*!
 @class SCNPhysicsConeTwistJoint
 */
SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNPhysicsConeTwistJoint : SCNPhysicsBehavior

//Initializes and returns a physics cone-twist joint.
//The joint attaches bodyA and bodyB on frameA and frameB respectively.
+ (instancetype)jointWithBodyA:(SCNPhysicsBody *)bodyA frameA:(SCNMatrix4)frameA bodyB:(SCNPhysicsBody *)bodyB frameB:(SCNMatrix4)frameB;

//Initializes and returns a physics cone-twist joint.
//The joint attaches "body" to the 3d location specified by "frame" and relative to the node that owns the body.
+ (instancetype)jointWithBody:(SCNPhysicsBody *)body frame:(SCNMatrix4)frame;

@property(nonatomic, readonly) SCNPhysicsBody *bodyA; //the first body attached to the slider joint
@property(nonatomic) SCNMatrix4 frameA;

@property(nonatomic, readonly, nullable) SCNPhysicsBody *bodyB; //the second body attached to the slider joint
@property(nonatomic) SCNMatrix4 frameB;

//The maximum angular limits in radians in each cone tangent directions
@property(nonatomic) CGFloat maximumAngularLimit1;
@property(nonatomic) CGFloat maximumAngularLimit2;

//Maximum twist angle alon the cone axis
@property(nonatomic) CGFloat maximumTwistAngle;

@end

/*!
 @class SCNPhysicsVehicleWheel
 @abstract SCNPhysicsVehicleWheel represents a wheel that can be attached to a SCNPhysicsVehicle instance.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsVehicleWheel : NSObject <NSCopying, NSSecureCoding>

//Initializes and returns a wheel.
+ (instancetype)wheelWithNode:(SCNNode *)node;

//The node of the receiver.
@property(readonly) SCNNode *node;

//The wheel suspension stiffness. Defaults to 2.0.
@property CGFloat suspensionStiffness;

//The wheel suspension compression. Defaults to 4.4.
@property CGFloat suspensionCompression;

//The wheel suspension damping. Defaults to 2.3.
@property CGFloat suspensionDamping;

//The wheel maximum suspension travel in centimeters. Defaults to 500.
@property CGFloat maximumSuspensionTravel;

//The wheel friction slip coefficient. Defaults to 1.
@property CGFloat frictionSlip;

//The wheel maximum suspension force in newtons. Defaults to 6000.
@property CGFloat maximumSuspensionForce;

//The wheel connection point relative to the chassis. Defaults to the node position.
@property SCNVector3 connectionPosition;

//The wheel steering axis in the vehicle chassis space. Defaults to (0,-1,0).
@property SCNVector3 steeringAxis;

//The wheel axle in the vehicle chassis space. Defaults to (-1,0,0).
@property SCNVector3 axle;

//The wheel radius. Defaults to the half of the max dimension of the bounding box of the node.
@property CGFloat radius;

//The wheel suspension rest length. Defaults to 1.6.
@property CGFloat suspensionRestLength;

@end

/*!
 @class SCNPhysicsVehicle
 @abstract SCNPhysicsVehicle provides a vehicle behavior.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsVehicle : SCNPhysicsBehavior

// Initializes and returns a physics vehicle that applies on the physics body "chassisBody" with the given wheels.
//The wheel properties can be modified at anytime by calling setValue:forKeyPath: on each wheel with the format 'wheel[n].property', where n if the zero based wheel index.
//A wheel can't be shared to multiple vehicle
+ (instancetype)vehicleWithChassisBody:(SCNPhysicsBody *)chassisBody wheels:(NSArray<SCNPhysicsVehicleWheel *> *)wheels;

//The actual speed in kilometers per hour.
@property(nonatomic, readonly) CGFloat speedInKilometersPerHour;

//The wheels of the vehicle
@property(nonatomic, readonly) NSArray<SCNPhysicsVehicleWheel *> *wheels;

//The chassis of the vehicle
@property(nonatomic, readonly) SCNPhysicsBody *chassisBody;

//Applies a force on the wheel at the specified index
- (void)applyEngineForce:(CGFloat)value forWheelAtIndex:(NSInteger)index;

//Allows to control the direction of the wheel at the specified index. The steering value is expressed in radian, 0 means straight ahead.
- (void)setSteeringAngle:(CGFloat)value forWheelAtIndex:(NSInteger)index;

//Applies a brake force on the wheel at the specified index.
- (void)applyBrakingForce:(CGFloat)value forWheelAtIndex:(NSInteger)index;

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNTechnique.h
//
//  SCNTechnique.h
//  SceneKit
//
//  Copyright © 2014-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SCNShadable.h>
#import <SceneKit/SCNAnimation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class SCNTechnique
 @abstract SCNTechnique represents a rendering process that may require multiple passes.
 @discussion A technique is generally initialized from a Property List file. It can be set to any object that conforms to the SCNTechniqueSupport protocol.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNTechnique : NSObject <SCNAnimatable, NSCopying, NSSecureCoding>

/*!
 @method techniqueWithDictionary:
 @abstract Creates and returns a technique instance initialized with the specified dictionary.
 @param dictionary The dictionary representation of the technique.
 @discussion The format of the dictionary is described below. Quoted strings can be any name of your choice. Tags are defined below.
 The passes are executed sequentially as specified in the "sequence" section. The definition of each pass is within the "passes" section. A pass may have inputs/outputs that reference targets or symbols defined in the "targets" and "symbols" section. The entries of the "symbols" section can be set/get and animated with SCNTechnique's APIs below.
 
 {
   sequence: ["Pass1", "Pass2", ...],
   passes: {
     "Pass1": {
        outputs: <outputs>
        inputs: <inputs>
        draw: <draw command>
        program: <program name>
        metalVertexShader: <METAL vertex shader function name>
        metalFragmentShader: <METAL fragment shader function name>
        colorStates: <color states>               //optional
        depthStates: <depth states>               //optional
        stencilStates: <stencil states>           //optional
        cullMode: <cull mode>                     //optional
        blendStates: <blend states>               //optional
        viewport: <custom viewport>               //optional
        pointOfView: <node name>                  //optional
        samples: <sample count>                   //optional
        excludeCategoryMask: <category bitMask>   //optional
        includeCategoryMask: <category bitMask>   //optional
     },
     "Pass2" : { 
         [...]
     }
   }
   symbols: {
     "symbol A": {
        <symbol description>
     }
     [...]
   }
   targets: {
      "target A": {
         <target description>
     }
     [...]
   }
}

<outputs>:
 The possible (and optional) keys with their possible associated values are:
 color: a string referencing a color render target. See <render target reference>.
 depth: a string referencing a depth render target. See <render target reference>.
 stencil: a string referencing a stencil render target. See <render target reference>.
 
<inputs>:
The inputs are listed in a dictionary. The keys are the uniform name as specified in the program of this pass.
The values can be a single string referencing a symbol or a semantic or a target OR a dictionary with the following structure:
 
 {
   target: <render target reference>,
 
   //optional:
   minificationFilter: linear, nearest
   magnificationFilter: linear, nearest
   mipFilter: linear, nearest, none
   wrapS: clamp, repeat, clampToBorder, mirror
   wrapT: clamp, repeat, clampToBorder, mirror
   wrapP: clamp, repeat, clampToBorder, mirror
   maxAnisotropy: a number
 }
 
 (See SCNMaterialProperty for more documentation and default values of these optional parameters.)
 
<render target reference>
 A string referencing a target (i.e an entry in the top level "targets" dictionary) or one of the special strings below:
 COLOR  The render target that represents that main color fragments that will be displayed on the screen ultimately.
 DEPTH  The render target that represents that main depth fragments.
 
<draw command>
 can be one of the following strings:
 DRAW_SCENE:    render the entire scene
 DRAW_QUAD:     render a fullscreen quad
 DRAW_NODE:     render a node and its sub-tree. The node is specified by setting its name as the value for the key "node".
 
<program name>
 Name of a program (a vertex shader + a fragment shader) located in the application bundle.
 The vertex shader must have the extension "vsh" and the fragment shader "fsh".
 
<METAL vertex shader function name>
 Name of a METAL function to use as the vertex shader.

<METAL fragment shader function name>
 Name of a METAL function to use as the fragment shader.
 
<color states>
 A dictionary with the following optional keys:
 "clear" a boolean specifying whether the color target should be cleared or not
 "clearColor" a string specifying the clear color as 4 float ("red green blue alpha"), or the string "sceneBackground" to clear with the scene background color.
 
<depth states>
 A dictionary with the following optional keys:
 "clear" a boolean specifying whether the depth target should be cleared or not
 "enableWrite" a boolean specifying whether writing to depth should be enabled or not.
 "enableRead" a boolean specifying whether reading from depth should be enabled or not.
 "func" a string specifying depth function to use. See <comparison function> for the possible values.

<stencil states>
 A dictionary with the following optional keys:
 "clear" a boolean specifying whether the stencil target should be cleared or not
 "enable" a boolean specifying whether writing to stencil should be enabled or not.
 "behavior" a dictionary describing the stencil behavior of the front face, or of both faces if no backFaceBehavior is specified. See <stencil behavior> for the format of this dictionary.
 "backFaceBehavior" a dictionary describing the behavior of the back face. See <stencil behavior> for the format of this dictionary.
 
<stencil behavior>
 A dictionary with the following optional keys:
 "depthFail" a string specifying the operation to do if the depth test fails. See <stencil operation> for the possible values.
 "fail" a string specifying the operation to do if the stencil test fails. See <Stencil operation> for the possible values.
 "pass" a string specifying the operation to do if the stencil test passes. See <stencil operation> for the possible values.
 "function" a string specifying the stencil test. See <comparison function> for the possible values.
 "readMask" a uint8_t number specifying a mask that is ANDed with both the reference value and the stored stencil value when the test is done
 "writeMask" a uint8_t number specifies a bit mask to enable and disable writing of individual bits in the stencil planes
 "referenceValue" a uint8_t number specifies the reference value for the stencil test. The initial value is 0. 
 
<stencil operation>
 A string specifying a stencil operation. It can be one of the following: keep, zero, replace, increment, decrement, invert, incrementWrap, decrementWrap
 
<comparison function>
 A string specifying a comparison function. It can be one of the following: never, always, equal, notEqual, less, lessEqual, greater, greaterEqual
 
<blend states>
 A dictionary with the following optional keys:
 "enable" a boolean number specifying if the blending should be enabled or not. defaults to true.
 "colorSrc" a string specifying a blend mode. See <blend mode>
 "colorDst" a string specifying a blend mode. See <blend mode>
 "alphaSrc" a string specifying a blend mode. See <blend mode>
 "alphaDst" a string specifying a blend mode. See <blend mode>
 "colorOp" a string specifying a blend operation. See <blend operation>
 "alphaOp" a string specifying a blend operation. See <blend operation>
 In no Blend states are specified, then the blending is turned off.
 
<blend mode>
 A string specifying a blend mode. It can be one of the following: zero, one, srcColor, oneMinusSrcColor, srcAlpha, oneMinusSrcAlpha, dstColor, oneMinusDstColor, dstAlpha, oneMinusDstAlpha, constantColor, oneMinusConstantColor, constantAlpha, oneMinusConstantAlpha, alphaSaturate.
 
<blend operation>
 A string specifying a blend operation. It can be one of the following: add, substract, reverseSubstract, min, max.

<cull mode>
 A string specifying a cull mode. It can be one of the following: front, none, back.
 
<custom viewport>
 A string specifying the viewport as 4 float.

<category bitMask>
 A integer value representing a node category mask (see SCNNode's categoryBitMask).
 if the key "excludeCategoryMask" is not specified then it defaults to 0.
 if the key "includeCategoryMask" is not specified then it defaults to all bits set.
 The DRAW_SCENE command will then render nodes that validate the following test (node.categoryBitMask & includeCategoryMask) && !(excludeCategoryMask & node.categoryBitMask).

<node name>
 The name of a node, or "self" to reference the owner of the technique if any.

<sample count>
 The number of samples (multisampling) used to render the pass.
 
<symbol description>
 A dictionary with the following optional keys and their possible associated values:
 
 semantic: vertex, normal, color, texcoord, tangent, time, modelViewProjectionTransform, modelViewTransform, modelTransform, viewTransform, projectionTransform, normalTransform, modelViewProjectionInverseTransform, modelViewInverseTransform, modelInverseTransform, viewInverseTransform, projectionInverseTransform, normalInverseTransform
 
 type: float, vec2, vec3, vec4, mat4, int, ivec2, ivec3, ivec4, mat3, sampler2D, none. Every types can also be an array of the given type by adding [N] where N is the number of elements in the array.
 
 image: name of an image located in the application bundle. (only valid when type is sampler2D)
 
 if a semantic is set, no type is required.
 Note that with Metal shaders you should not provide any semantic. Instead simply declare a struct in you shader and add the members you need named as specified in SceneKit/scn_metal.
 
 For example for a per-node semantic:
 
 struct MyStruct
 {
 float4x4 modelTransform;
 float4x4 modelViewProjectionTransform;
 };
 then in your function add an argument that must be named “scn_node” to get the members automatically filed with node semantics (see the documentation in scn_metal).
 
<target description>
 A dictionary with the following optional keys and their possible associated values:
 
 type: a string specifying the type of the render target. It can be one of the following: color, depth, stencil
 format: a string specifying the format of the render target. It can be:
 - for color targets: rgba32f, r8, r16f, rg16 or rgba. If not specified defaults to the framebuffer's pixel format.
 - for depth targets: depth24, depth24stencil8
 - for stencil targets: depth24stencil8
 scaleFactor: a float value (encapsulated in a NSNumber) that controls the size of the render target. Defaults to 1, which means 1x the size of the main viewport.
 size: a string with the format %dx%d that controls the size of the render target.
 persistent: a boolean that tells if this target should persist from one frame to the next. It permits to create temporal effects suchs as motion blur. Defaults to NO.
 */
+ (nullable SCNTechnique *)techniqueWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

/*!
 @method techniqueBySequencingTechniques:
 @abstract Creates and returns a technique by sequencing the passes from the specified techniques.
 @param techniques The techniques to sequence.
 @discussion The passes from "techniques" are executed sequentially. The symbols and targets are merged. This allows to use the same uniform ad targets across multiple techniques.
 */
+ (nullable SCNTechnique *)techniqueBySequencingTechniques:(NSArray<SCNTechnique *> *)techniques;

/*!
 @method handleBindingOfSymbol:usingBlock:
 @abstract Sets the block to call at render time to bind the value for the specified symbol of the receiver. 
 @param symbol The name of the symbol to bind a value for.
 @param block The block to call to bind the specified symbol.
 @discussion The block will be called at every frame for every pass referencing the specified symbol.
 */
- (void)handleBindingOfSymbol:(NSString *)symbol usingBlock:(nullable SCNBindingBlock)block;

/*!
 @property dictionaryRepresentation
 @abstract Returns the dictionary representation of the technique.
 */
@property(readonly) NSDictionary<NSString *, id> *dictionaryRepresentation;

/*
 SCNTechnique is a key-value coding compliant class, which means that you can set values for arbitrary keys. Even if the key `myAmplitude` is not a declared property of the class, you can still set a value for it.
 If the Property List file declares the `myAmplitude` symbol, any change to the `myAmplitude` property of the receiver will make SceneKit bind the associated uniform with the new value.
 
 Symbols can be animated using explicit animations.
 
 The following GLSL types (and Objective-C counterparts) can be used to bind symbols:
 
 GLSL types    | Objective-C types
 --------------------------------------
 int           | NSNumber, NSInteger, int
 float         | NSNumber, CGFloat, float, double
 vec2          | CGPoint
 vec3          | SCNVector3
 vec4          | SCNVector4
 mat4, mat44   | SCNMatrix4
 
 On macOS 10.11 or later and iOS 9 or later you can also use the object subscripting syntax to set values to uniforms.
 For example:
 myTechnique[@"myAmplitude"] = aValue;
 */
- (nullable id)objectForKeyedSubscript:(id)key API_AVAILABLE(macos(10.11), ios(9.0));
- (void)setObject:(nullable id)obj forKeyedSubscript:(id <NSCopying>)key API_AVAILABLE(macos(10.11), ios(9.0));

@end



/*!
 @protocol SCNTechniqueSupport
 @abstract The SCNTechniqueSupport protocol describes an object that supports single or multi-pass techniques
 */
@protocol SCNTechniqueSupport <NSObject>

/*!
 @property technique
 @abstract Specifies the technique of the receiver. Defaults to nil.
 */
@property(nonatomic, copy, nullable) SCNTechnique *technique API_AVAILABLE(macos(10.10));

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNPhysicsBody.h
//
//  SCNPhysicsBody.h
//  SceneKit
//
//  Copyright © 2014-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNPhysicsShape;

//Physics Body type
typedef NS_ENUM(NSInteger, SCNPhysicsBodyType) {
	SCNPhysicsBodyTypeStatic,
	SCNPhysicsBodyTypeDynamic,
	SCNPhysicsBodyTypeKinematic
} API_AVAILABLE(macos(10.10));

//Collision default category
typedef NS_OPTIONS(NSUInteger, SCNPhysicsCollisionCategory) {
	SCNPhysicsCollisionCategoryDefault = 1 << 0,    // default collision group for dynamic and kinematic objects
	SCNPhysicsCollisionCategoryStatic  = 1 << 1,    // default collision group for static objects
	SCNPhysicsCollisionCategoryAll     = ~0UL       // default for collision mask
} API_AVAILABLE(macos(10.10));

/*!
 @class SCNPhysicsBody
 @abstract The SCNPhysicsBody class describes the physics properties (such as mass, friction...) of a node.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsBody : NSObject <NSCopying, NSSecureCoding>

//Creates an instance of a static body with default properties.
+ (instancetype)staticBody;

//Creates an instance of a dynamic body with default properties.
+ (instancetype)dynamicBody;

//Creates an instance of a kinematic body with default properties.
+ (instancetype)kinematicBody;

//Creates an instance of a rigid body with a specific shape.
+ (instancetype)bodyWithType:(SCNPhysicsBodyType)type shape:(nullable SCNPhysicsShape *)shape;

//Specifies the type of the receiver.
@property(nonatomic) SCNPhysicsBodyType type;

//Specifies the Mass of the body in kilogram. Defaults to 1 for dynamic bodies, defaults to 0 for static bodies.
@property(nonatomic) CGFloat mass;

//Specifies the moment of inertia of the body as a vector in 3D. Disable usesDefaultMomentOfInertia for this value to be used instead of the default moment of inertia that is calculated from the shape geometry.
@property(nonatomic) SCNVector3 momentOfInertia API_AVAILABLE(macos(10.11), ios(9.0));

//Permits to disable the use of the default moment of inertia in favor of the one stored in momentOfInertia.
@property(nonatomic) BOOL usesDefaultMomentOfInertia API_AVAILABLE(macos(10.11), ios(9.0));

// Specifies the charge on the body. Charge determines the degree to which a body is affected by
// electric and magnetic fields. Note that this is a unitless quantity, it is up to the developer to
// set charge and field strength appropriately. Defaults to 0.0
@property(nonatomic) CGFloat charge;

//Specifies the force resisting the relative motion of solid sliding against each other. Defaults to 0.5.
@property(nonatomic) CGFloat friction;

//Specifies the restitution of collisions. Defaults to 0.5.
@property(nonatomic) CGFloat restitution;

//Specifies the force resisting the relative motion of solid rolling against each other. Defaults to 0.
@property(nonatomic) CGFloat rollingFriction;

//Specifies the physics shape of the receiver. Leaving this nil will let the system decide and use the most efficients bounding representation of the actual geometry.
@property(nonatomic, retain, nullable) SCNPhysicsShape *physicsShape;

//If the physics simulation has determined that this body is at rest it may set the resting property to YES. Resting bodies do not participate in the simulation until some collision with a non-resting object, or an impulse is applied, that unrests it. If all bodies in the world are resting then the simulation as a whole is "at rest".
@property(nonatomic, readonly) BOOL isResting;

//Specifies if the receiver can be set at rest.
@property(nonatomic) BOOL allowsResting;

//Specifies the linear velocity of the receiver.
@property(nonatomic) SCNVector3 velocity;

//Specifies the angular velocity of the receiver as an axis angle.
@property(nonatomic) SCNVector4 angularVelocity;

//Specifies the damping factor of the receiver. Optionally reduce the body's linear velocity each frame to simulate fluid/air friction. Value should be zero or greater. Defaults to 0.1.
@property(nonatomic) CGFloat damping;

//Specifies the angular damping of the receiver. Optionally reduce the body's angular velocity each frame to simulate rotational friction. (0.0 - 1.0). Defaults to 0.1.
@property(nonatomic) CGFloat angularDamping;

//Specifies a factor applied on the translation that results from the physics simulation before applying it to the node.
@property(nonatomic) SCNVector3 velocityFactor;

//Specifies a factor applied on the rotation on each axis that results from the physics simulation before applying it to the node.
@property(nonatomic) SCNVector3 angularVelocityFactor;

//Defines what logical 'categories' this body belongs too.
//Defaults to SCNPhysicsCollisionCategoryStatic for static bodies and SCNPhysicsCollisionCategoryDefault for the other body types.
//limited to the first 15 bits on macOS 10.10 and iOS 8.
@property(nonatomic) NSUInteger categoryBitMask;

//Defines what logical 'categories' of bodies this body responds to collisions with. Defaults to all bits set (all categories).
@property(nonatomic) NSUInteger collisionBitMask;

//A mask that defines which categories of bodies cause intersection notifications with this physics body. Defaults to 0.
//On iOS 8 and macOS 10.10 and lower the intersection notifications are always sent when a collision occurs.
@property(nonatomic) NSUInteger contactTestBitMask API_AVAILABLE(macos(10.11), ios(9.0));

//If set to YES this node will be affected by gravity. The default is YES.
@property(nonatomic, getter=isAffectedByGravity) BOOL affectedByGravity API_AVAILABLE(macos(10.11), ios(9.0));

//Applies a linear force in the specified direction. The linear force is applied on the center of mass of the receiver. If impulse is set to YES then the force is applied for just one frame, otherwise it applies a continuous force.
- (void)applyForce:(SCNVector3)direction impulse:(BOOL)impulse;

//Applies a linear force with the specified position and direction. The position is relative to the node that owns the physics body.
- (void)applyForce:(SCNVector3)direction atPosition:(SCNVector3)position impulse:(BOOL)impulse;

//Applies an angular force (torque). If impulse is set to YES then the force is applied for just one frame, otherwise it applies a continuous force. The torque is specified as an axis angle.
- (void)applyTorque:(SCNVector4)torque impulse:(BOOL)impulse;

//Clears the forces applied one the receiver.
- (void)clearAllForces;

//Reset the physical transform to the node's model transform.
- (void)resetTransform;

// Sets a physics body at rest (or not)
- (void)setResting:(BOOL)resting API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

// Use discrete collision detection if the body’s distance traveled in one step is at or below this threshold, or continuous collision detection otherwise. Defaults to zero, indicating that continuous collision detection is always disabled.
@property (nonatomic) CGFloat continuousCollisionDetectionThreshold API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

// Specifies an offset for the center of mass of the body. Defaults to (0,0,0).
@property(nonatomic) SCNVector3 centerOfMassOffset API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

// Linear velocity threshold under which the body may be considered resting. Defaults to 0.1.
@property (nonatomic) CGFloat linearRestingThreshold API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

// Angular velocity threshold under which the body may be considered resting. Defaults to 0.1.
@property (nonatomic) CGFloat angularRestingThreshold API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));


@end
    
NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNShadable.h
//
//  SCNShadable.h
//  SceneKit
//
//  Copyright © 2013-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNMaterial;
@class SCNNode;
@class SCNRenderer;
@class SCNProgram;
@protocol MTLLibrary;
@protocol SCNProgramDelegate;
@protocol SCNShadable;

typedef NSString * SCNShaderModifierEntryPoint NS_STRING_ENUM;

/*! @enum SCNBufferFrequency
 @abstract The frequency at which the custom program input should be updated.
 @discussion When the frequency is set to SCNBufferFrequencyPerFrame, the binding block is invoked once per frame.
 When the frequency is set to SCNBufferFrequencyPerNode, the binding block is invoked once per SCNNode.
 When the frequency is set to SCNBufferFrequencyPerShadable, the binding block is invoked once per SCNMaterial or SCNGeometry (depending on the object that owns the SCNProgram).
 */
typedef NS_ENUM(NSInteger, SCNBufferFrequency) {
    SCNBufferFrequencyPerFrame    = 0,
    SCNBufferFrequencyPerNode     = 1,
    SCNBufferFrequencyPerShadable = 2 // SCNMaterial or SCNGeometry
} API_AVAILABLE(macos(10.11), ios(9.0));

@protocol SCNBufferStream <NSObject>
- (void)writeBytes:(void *)bytes length:(NSUInteger)length;
@end

/*!
 @typedef SCNBufferBindingBlock
 @discussion Signature for the block to execute to bind or unbind a buffer.
 @param buffer The buffer to fill.
 @param node The rendered node.
 @param shadable The rendered shadable (geometry or material).
 @param renderer The renderer that is currently rendering the scene.
 */
typedef void (^SCNBufferBindingBlock)(id <SCNBufferStream> buffer, SCNNode *node, id <SCNShadable> shadable, SCNRenderer *renderer);

/*!
 @typedef SCNBindingBlock
 @discussion Signature for the block to execute to bind or unbind a uniform of an OpenGL or OpenGLES based program.
 @param programID The id of the program object to bind/unbind values for.
 @param location The location of the symbol within the program object to bind/unbind values for.
 @param renderedNode The node currently being rendered.
 @param renderer The renderer that is currently rendering the scene.
 */
typedef void (^SCNBindingBlock)(unsigned int programID, unsigned int location, SCNNode * _Nullable renderedNode, SCNRenderer *renderer);


/*!
 @protocol SCNShadable
 @abstract The SCNShadable protocol defines an object that is rendered with shaders. 
 */
@protocol SCNShadable <NSObject>
@optional

/*!
 @property program
 @abstract Specifies a custom program used to render the receiver.
 @discussion When a program is set, it overrides all the rendering parameters such as material settings and shaderModifiers.
 */
@property(nonatomic, retain, nullable) SCNProgram *program API_UNAVAILABLE(watchos);

/*!
 @method handleBindingOfSymbol:usingBlock:
 @abstract Sets the block to call at render time to bind the value for the specified symbol of the receiver's SCNProgram. This method has no effect for symbols declared in shader modifiers.
 @param symbol The name of the symbol to bind a value for.
 @param block The block to call to bind the specified symbol.
 @discussion This method can only be used with OpenGL and OpenGLES based programs.
 */
- (void)handleBindingOfSymbol:(NSString *)symbol usingBlock:(nullable SCNBindingBlock)block API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(watchos);

/*!
 @method handleUnbindingOfSymbol:usingBlock:
 @abstract Sets the block to call at render time to unbind the value for the specified symbol of the receiver's SCNProgram. This method has no effect for symbols declared in shader modifiers.
 @param symbol The name of the symbol to unbind.
 @param block The block to call to unbind the specified symbol.
 @discussion This method can only be used with OpenGL and OpenGLES based programs.
 */
- (void)handleUnbindingOfSymbol:(NSString *)symbol usingBlock:(nullable SCNBindingBlock)block API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(watchos);

/*!
 @property shaderModifiers
 @abstract Dictionary of shader modifiers snippets, targeting entry points. The valid keys are the entry points described in the "Shader Modifier Entry Point" constants. The values are the code snippets formatted as described below.
 @discussion Shader modifiers allow you to inject shader code in the standard shaders of SceneKit. This injection is allowed in few controlled entry points, allowing specific kind of tasks in specific context. Each modifier can operate on specific structures along with access to global uniforms, that could be the standard SceneKit uniforms or its own declared uniforms.
 
 Shader modifiers can be used to tweak SceneKit rendering by adding custom code at the following entry points:
     1. vertex   (SCNShaderModifierEntryPointGeometry)
     2. surface  (SCNShaderModifierEntryPointSurface)
     3. lighting (SCNShaderModifierEntryPointLightingModel)
     4. fragment (SCNShaderModifierEntryPointFragment)
 See below for a detailed explanation of these entry points and the context they provide.
 
 Shader modifiers can be written in either GLSL or the Metal Shading Language. Metal shaders won't run on iOS 8 and macOS 10.10 or earlier.
 
 The structure of a shader modifier is:
 
     GLSL
     | uniform float myGrayAmount = 3.0; // Custom GLSL uniforms declarations are of the form `[uniform type uniformName [= defaultValue]]`
     |
     | // Optional global function definitions (for Metal: references to uniforms in global functions are not supported).
     | float mySin(float t) {
     |    return sin(t);
     | }
     |
     | [#pragma transparent | opaque]
     | [#pragma body]
     |
     | // the shader modifier code snippet itself
     | vec3 myColor = myGrayAmount;
     | _output.color.rgb += myColor;
 
     Metal Shading Language
     | #pragma arguments
     | float myGrayAmount; // Custom Metal uniforms declarations require a #pragma and are of the form `[type name]`
     |
     | // Optional global function definitions (for Metal: references to uniforms in global functions are not supported).
     | float mySin(float t) {
     |    return sin(t);
     | }
     |
     | [#pragma transparent | opaque]
     | [#pragma body]
     |
     | // the shader modifier code snippet itself
     | float3 myColor = myGrayAmount;
     | _output.color.rgb += myColor;
 
 The `#pragma body` directive
     Is only needed if you declared functions that must not be included in the shader code itself.
 
 The `#pragma transparent` directive
     Forces the rendering to be blended using the following equation:
         _output.color.rgb + (1 - _output.color.a) * dst.rgb;
     where `dst` represents the current fragment color. The rgb components must be premultiplied.
 
 The `#pragma opaque` directive
     Forces the rendering to be opaque. It then ignores the alpha component of the fragment.
 
 When using Metal, you can also transfer varying values from the vertex shader (geometry shader modifier) to the fragment shader (surface and/or fragment shader modifier):
     1. Start by declaring the varying values in at least one of the shader modifiers:
 
         Metal Shading Language
         | #pragma varyings
         | half3 myVec;
 
     2. Then write the varying values from the vertex shader (geometry shader modifier):
 
         Metal Shading Language
         | #pragma body
         | out.myVec = _geometry.normal.xyz * 0.5h + 0.5h;
 
     3. Finally read the varying values from the fragment shader (surface and/or fragment shader modifier):
 
         Metal Shading Language
         | _output.color.rgb = saturate(in.myVec);
 
  SceneKit declares the following built-in uniforms:
 
     GLSL                                        | Metal Shading Language                                |
     --------------------------------------------┼-------------------------------------------------------┤
     float u_time                                | float    scn_frame.time                               | The current time, in seconds
     vec2  u_inverseResolution                   | float2   scn_frame.inverseResolution                  | 1.0 / screen size
     --------------------------------------------┼-------------------------------------------------------┤
     mat4  u_viewTransform                       | float4x4 scn_frame.viewTransform                      | See SCNViewTransform
     mat4  u_inverseViewTransform                | float4x4 scn_frame.inverseViewTransform               |
     mat4  u_projectionTransform                 | float4x4 scn_frame.projectionTransform                | See SCNProjectionTransform
     mat4  u_inverseProjectionTransform          | float4x4 scn_frame.inverseProjectionTransform         |
     --------------------------------------------┼-------------------------------------------------------┤
     mat4  u_normalTransform                     | float4x4 scn_node.normalTransform                     | See SCNNormalTransform
     mat4  u_modelTransform                      | float4x4 scn_node.modelTransform                      | See SCNModelTransform
     mat4  u_inverseModelTransform               | float4x4 scn_node.inverseModelTransform               |
     mat4  u_modelViewTransform                  | float4x4 scn_node.modelViewTransform                  | See SCNModelViewTransform
     mat4  u_inverseModelViewTransform           | float4x4 scn_node.inverseModelViewTransform           |
     mat4  u_modelViewProjectionTransform        | float4x4 scn_node.modelViewProjectionTransform        | See SCNModelViewProjectionTransform
     mat4  u_inverseModelViewProjectionTransform | float4x4 scn_node.inverseModelViewProjectionTransform |
     --------------------------------------------┼-------------------------------------------------------┤
     mat2x3 u_boundingBox;                       | float2x3 scn_node.boundingBox                         | The bounding box of the current geometry, in model space, u_boundingBox[0].xyz and u_boundingBox[1].xyz being respectively the minimum and maximum corner of the box.
     mat2x3 u_worldBoundingBox;                  | float2x3 scn_node.worldBoundingBox                    | The bounding box of the current geometry, in world space.

     When writing shaders using the Metal Shading Language a complete description of the type of the scn_frame variable (SCNSceneBuffer) can be found in the <SceneKit/scn_metal> header file.
     The type of the scn_node variable is generated at compile time and there's no corresponding header file in the framework.
 
 In addition to these built-in uniforms, it is possible to use custom uniforms:
 
     The SCNGeometry and SCNMaterial classes are key-value coding compliant classes, which means that you can set values for arbitrary keys. Even if the key `myAmplitude` is not a declared property of the class, you can still set a value for it.
     Declaring a `myAmplitude` uniform in the shader modifier makes SceneKit observe the reveiver's `myAmplitude` key. Any change to that key will make SceneKit bind the uniform with the new value.

     The following GLSL and Metal Shading Language types (and their Objective-C counterparts) can be used to declare (and bind) custom uniforms:
 
        GLSL        | Metal Shading Language | Objective-C                           |
        ------------┼------------------------┼---------------------------------------┤
        int         | int                    | NSNumber, NSInteger, int              |
        float       | float                  | NSNumber, CGFloat, float, double      |
        vec2        | float2                 | CGPoint                               |
        vec3        | float3                 | SCNVector3                            |
        vec4        | float4                 | SCNVector4                            |
        mat4, mat44 | float4x4               | SCNMatrix4                            |
        sampler2D   | texture2d              | SCNMaterialProperty                   |
        samplerCube | texturecube            | SCNMaterialProperty (with a cube map) |
        -           | device const T*        | MTLBuffer                             | Feature introduced in macOS 10.13, iOS 11.0 and tvOS 11.0
        -           | struct {...}           | NSData                                | The entire struct can be set using NSData but it is also possible to set individual members using the member's name as a key and a value compatible with the member's type
 
     Common scalar types wrapped into a NSValue are also supported.
 
     The following prefixes are reserved by SceneKit and should not be used in custom names:
         1. u_
         2. a_
         3. v_
 
     Custom uniforms can be animated using explicit animations.
 */
@property(nonatomic, copy, nullable) NSDictionary<SCNShaderModifierEntryPoint, NSString *> *shaderModifiers API_AVAILABLE(macos(10.9));

@end


/*!
 @group Semantic options
 @abstract Valid keys for the option parameter of setSemantic:forSymbol:options:
 */
SCN_EXPORT NSString * const SCNProgramMappingChannelKey API_UNAVAILABLE(watchos); /* This key is optional and may be used in association with the SCNGeometrySourceSemanticTexcoord semantic. It allows to associate a mapping channel from the geometry to a symbol from the program source code. The mapping channel allows to plug programs that work with multiple texture coordinates. The associated value must be a NSNumber(integer) greater than zero. */

/*!
 @class SCNProgram
 @abstract A SCNProgram lets you specify custom shaders to use when rendering materials.
 */
API_UNAVAILABLE(watchos)
SCN_EXPORT
@interface SCNProgram : NSObject <NSCopying, NSSecureCoding>

/*!
 @method program
 @abstract Creates and initialize a program instance.
 */
+ (instancetype)program;

/*!
 @property vertexShader
 @abstract Determines the receiver's vertex shader.
 */
@property(nonatomic, copy, nullable) NSString *vertexShader;

/*!
 @property fragmentShader
 @abstract Determines the receiver's fragment shader.
 */
@property(nonatomic, copy, nullable) NSString *fragmentShader;


/*!
 @property vertexFunctionName
 @abstract Determines the receiver's vertex function name.
 @discussion The name of the vertex function (for Metal programs).
 */
@property(nonatomic, copy, nullable) NSString *vertexFunctionName API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property fragmentFunctionName
 @abstract Determines the receiver's fragment function name.
 @discussion The name of the fragment function (for Metal programs).
 */
@property(nonatomic, copy, nullable) NSString *fragmentFunctionName API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method handleBindingOfBufferNamed:frequency:usingBlock:
 @abstract Sets the block to call at render time to bind the buffer of the specified symbol of the receiver's program.
 @param name The name of the buffer to bind.
 @param frequency The frequency at which the block has to be invoked. Can be per frame, per node or per geometry or material. See SCNBufferBindingBlock above.
 @param block The block that binds the buffer.
 @discussion This method can only be used with Metal based programs.
 */
- (void)handleBindingOfBufferNamed:(NSString *)name frequency:(SCNBufferFrequency)frequency usingBlock:(SCNBufferBindingBlock)block API_AVAILABLE(macos(10.11), ios(9.0));


/*!
 @property opaque
 @abstract Determines the receiver's fragment are opaque or not. Defaults to YES.
 */
@property(nonatomic, getter=isOpaque) BOOL opaque API_AVAILABLE(macos(10.10));

/*!
 @method setSemantic:forSymbol:options:
 @abstract Associates a SceneKit semantic to a symbol.
 @param semantic The SceneKit semantic to associate to the specified symbol.
 @param symbol A symbol from the program source code.
 @param options An optional dictionary. See the 'Semantic options' above.
 @discussion Associates semantics handled by the SceneKit runtime to a symbol from the program. Supported semantics are listed in SCNGeometry.h and SCNNode.h.
 */
- (void)setSemantic:(nullable NSString *)semantic forSymbol:(NSString *)symbol options:(nullable NSDictionary<NSString *, id> *)options;

/*!
 @method semanticForSymbol:
 @abstract Retrieves the SceneKit semantic associated to a symbol from the program source code.
 @param symbol A symbol from the program source code.
 */
- (nullable NSString *)semanticForSymbol:(NSString *)symbol;

/*!
 @property delegate
 @abstract Determines the receiver's delegate
 */
@property(nonatomic, assign, nullable) id <SCNProgramDelegate> delegate;

/*!
 @property library
 @abstract Specifies the metal library to use to locate the function names specified above. 
 @discussion If set to nil the default library is used. Defaults to nil.
 */
@property(nonatomic, retain, nullable) id <MTLLibrary> library API_AVAILABLE(macos(10.11), ios(9.0));

@end

/*!
 @protocol SCNProgramDelegate
 @abstract The SCNProgramDelegate protocol declares the methods that an instance of SCNProgram invokes to delegate the binding of parameters.
 */
API_UNAVAILABLE(watchos)
@protocol SCNProgramDelegate <NSObject>

@optional
/*!
 @method handleError
 @abstract Invoked on the delegate whenever a compilation error occurs.
 @discussion Error domain is SCNErrorDomain.
 @param program The program that generated a compilation error.
 @param error The compilation error.
 */
- (void)program:(SCNProgram *)program handleError:(NSError *)error;

/*!
 @method programIsOpaque
 @abstract The delegate should implement this mehod and return NO if the fragments generated by the program are not opaque.
 @param program The queried program.
 @discussion This is deprecated. Use SCNProgram's opaque property instead.
 */
- (BOOL)programIsOpaque:(SCNProgram *)program API_DEPRECATED("Use SCNProgram.opaque instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos);

@end

/*!
 @group Shader Modifier Entry Point
 @abstract Entry points designing the insertion point of the shader code snippet of a shader modifiers dictionary.
 */

/*!
 @constant SCNShaderModifierEntryPointGeometry
 @abstract This is the entry point to operate on the geometry vertices, for example deforming them.
 @discussion It operates entirely in the vertex shader stage. It's input is the geometry structure:
 
 Structures available from the SCNShaderModifierEntryPointGeometry entry point:
 
 | struct SCNShaderGeometry {
 |    float4 position;
 |    float3 normal;
 |    float4 tangent;
 |    float4 color;
 |    float2 texcoords[kSCNTexcoordCount];
 | } _geometry;
 |
 | Access: ReadWrite
 | Stages: Vertex shader only
 
 kSCNTexcoordCount is a constant integer set to the number of texture coordinates used.
 
 All the geometric fields (position, normal and tangent) are in model space. You can use one of the provided automatic uniforms
 such as u_modelTransform or u_modelViewTransform if you want to operate in another space (but the results must stay in the model space, otherwise remaining computations won't be correct).
 The texture coordinates are the raw values found in the mesh, they have not been transformed yet by their optional contentsTransform. The contentsTransform if any is applied after the geometry shader modifier.
 
 Example: Simple sinusoidal deformation
 
     GLSL
     | uniform Amplitude = 0.1;
     |
     | _geometry.position.xyz += _geometry.normal * (Amplitude * _geometry.position.y * _geometry.position.x) * sin(u_time);
 
     Metal Shading Language
     | #pragma arguments
     | float Amplitude;
     |
     | _geometry.position.xyz += _geometry.normal * (Amplitude * _geometry.position.y * _geometry.position.x) * sin(u_time);
 
 */
SCN_EXPORT SCNShaderModifierEntryPoint const SCNShaderModifierEntryPointGeometry API_AVAILABLE(macos(10.9));

/*!
 @constant SCNShaderModifierEntryPointSurface
 @abstract This is the entry point to alter the surface representation of the material, before the lighting has taken place.
 
 Structures available from the SCNShaderModifierEntryPointSurface entry point:
 
 | struct SCNShaderSurface {
 |    float3 view;                     // Direction from the point on the surface toward the camera (V)
 |    float3 position;                 // Position of the fragment
 |    float3 normal;                   // Normal of the fragment (N)
 |    float3 geometryNormal;           // Geometric normal of the fragment (normal map is ignored)
 |    float3 tangent;                  // Tangent of the fragment
 |    float3 bitangent;                // Bitangent of the fragment
 |    float4 ambient;                  // Ambient property of the fragment
 |    float2 ambientTexcoord;          // Ambient texture coordinates
 |    float4 diffuse;                  // Diffuse property of the fragment. Alpha contains the opacity.
 |    float2 diffuseTexcoord;          // Diffuse texture coordinates
 |    float4 specular;                 // Specular property of the fragment
 |    float2 specularTexcoord;         // Specular texture coordinates
 |    float4 emission;                 // Emission property of the fragment
 |    float2 emissionTexcoord;         // Emission texture coordinates
 |    float4 multiply;                 // Multiply property of the fragment
 |    float2 multiplyTexcoord;         // Multiply texture coordinates
 |    float4 transparent;              // Transparent property of the fragment
 |    float2 transparentTexcoord;      // Transparent texture coordinates
 |    float4 reflective;               // Reflective property of the fragment
 |    float  metalness;                // Metalness property of the fragment
 |    float2 metalnessTexcoord;        // Metalness texture coordinates
 |    float  roughness;                // Roughness property of the fragment
 |    float2 roughnessTexcoord;        // Roughness texture coordinates
 |    float4 selfIllumination;         // Self Illumination property of the fragment. Available since macOS 10.13, iOS 11, tvOS 11 and watchOS 4. Available as `emission` in previous versions.
 |    float2 selfIlluminationTexcoord; // Self Illumination texture coordinates. Available since macOS 10.13, iOS 11, tvOS 11 and watchOS 4. Available as `emissionTexcoord` in previous versions.
 |    float  ambientOcclusion;         // Ambient Occlusion property of the fragment. Available macOS 10.13, iOS 11, tvOS 11 and watchOS 4. Available as `multiply` in previous versions.
 |    float2 ambientOcclusionTexcoord; // Ambient Occlusion texture coordinates. Available since macOS 10.13, iOS 11, tvOS 11 and watchOS 4. Available as `multiplyTexcoord` in previous versions.
 |    float  shininess;                // Shininess property of the fragment
 |    float  fresnel;                  // Fresnel property of the fragment
 | } _surface;
 |
 | Access: ReadWrite
 | Stages: Fragment shader only
 
 All geometric fields are in view space.
 All the other properties will be colors (texture have already been sampled at this stage) or floats. You can however do an extra sampling of standard textures if you want.
 In this case the naming pattern is u_<property>Texture. For example u_diffuseTexture or u_reflectiveTexture. Note that you have to be sure that the material do have a texture
 set for this property, otherwise you'll trigger a shader compilation error.
 
 Example: Procedural black and white stripes
 
     GLSL
     | uniform float Scale = 12.0;
     | uniform float Width = 0.25;
     | uniform float Blend = 0.3;
     |
     | vec2 position = fract(_surface.diffuseTexcoord * Scale);
     | float f1 = clamp(position.y / Blend, 0.0, 1.0);
     | float f2 = clamp((position.y - Width) / Blend, 0.0, 1.0);
     | f1 = f1 * (1.0 - f2);
     | f1 = f1 * f1 * 2.0 * (3. * 2. * f1);
     | _surface.diffuse = mix(vec4(1.0), vec4(0.0), f1);
 
     Metal Shading Language
     | #pragma arguments
     | float Scale;
     | float Width;
     | float Blend;
     |
     | float2 position = fract(_surface.diffuseTexcoord * Scale);
     | float f1 = clamp(position.y / Blend, 0.0, 1.0);
     | float f2 = clamp((position.y - Width) / Blend, 0.0, 1.0);
     | f1 = f1 * (1.0 - f2);
     | f1 = f1 * f1 * 2.0 * (3. * 2. * f1);
     | _surface.diffuse = mix(float4(1.0), float4(0.0), f1);
 
 */
SCN_EXPORT SCNShaderModifierEntryPoint const SCNShaderModifierEntryPointSurface API_AVAILABLE(macos(10.9));

/*!
 @constant SCNShaderModifierEntryPointLightingModel
 @abstract This is the entry point to provide custom lighting equation. The fragment will be called for each active light
 of the scene and will need to accumulate lighting contribution for the vertex or the fragment in the _lightingContribution structure, using the light structure given.
 
 Structures available from the SCNShaderModifierEntryPointLightingModel entry point:
 
 | All the structures available from the SCNShaderModifierEntryPointSurface entry point
 |
 | Access: ReadOnly
 | Stages: Vertex shader and fragment shader
 
 | struct SCNShaderLightingContribution {
 |    float3 ambient;
 |    float3 diffuse;
 |    float3 specular;
 | } _lightingContribution;
 |
 | Access: ReadWrite
 | Stages: Vertex shader and fragment shader
 
 | struct SCNShaderLight {
 |    float4 intensity;
 |    float3 direction; // Direction from the point on the surface toward the light (L)
 | } _light;
 |
 | Access: ReadOnly
 | Stages: Vertex shader and fragment shader
 
 Example: Wrap diffuse lighting
 
     GLSL
     | uniform float WrapFactor = 0.5;
     |
     | float dotProduct = (WrapFactor + max(0.0, dot(_surface.normal,_light.direction))) / (1 + WrapFactor);
     | _lightingContribution.diffuse += (dotProduct * _light.intensity.rgb);
     | vec3 halfVector = normalize(_light.direction + _surface.view);
     | dotProduct = max(0.0, pow(max(0.0, dot(_surface.normal, halfVector)), _surface.shininess));
     | _lightingContribution.specular += (dotProduct * _light.intensity.rgb);
 
     Metal Shading Language
     | #pragma arguments
     | float WrapFactor;
     |
     | float dotProduct = (WrapFactor + max(0.0, dot(_surface.normal,_light.direction))) / (1 + WrapFactor);
     | _lightingContribution.diffuse += (dotProduct * _light.intensity.rgb);
     | float3 halfVector = normalize(_light.direction + _surface.view);
     | dotProduct = max(0.0, pow(max(0.0, dot(_surface.normal, halfVector)), _surface.shininess));
     | _lightingContribution.specular += (dotProduct * _light.intensity.rgb);
 */
SCN_EXPORT SCNShaderModifierEntryPoint const SCNShaderModifierEntryPointLightingModel API_AVAILABLE(macos(10.9));

/*!
 @constant SCNShaderModifierEntryPointFragment
 @abstract This is the last entry point in the fragment shader, where you can alter the final color returned by the shader.
 @discussion You can alter the final color by reading and writing to the output color via the output structure below.
 
 Structures available from the SCNShaderModifierEntryPointFragment entry point:
 
 | All the structures available from the SCNShaderModifierEntryPointSurface entry point
 |
 | Access: ReadOnly
 | Stages: Fragment shader only
 
 | struct SCNShaderOutput {
 |    float4 color;
 | } _output;
 |
 | Access: ReadWrite
 | Stages: Fragment shader only
 
 Example: Inverse final color
 
     GLSL
     | _output.color.rgb = vec3(1.0) - _output.color.rgb;
 
     Metal Shading Language
     | _output.color.rgb = 1.0 - _output.color.rgb;
 */
SCN_EXPORT SCNShaderModifierEntryPoint const SCNShaderModifierEntryPointFragment API_AVAILABLE(macos(10.9));

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNCAAnimationExtensions.h
//
//  SCNCAAnimationExtensions.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SCNAnimation.h>

NS_ASSUME_NONNULL_BEGIN

@interface CAAnimation (SCNAnimation) <SCNAnimation>
@end

/*!
 @category CAAnimation (SceneKitAdditions)
 @abstract Extends the CAAnimation class for SceneKit explicit animations.
 */
@interface CAAnimation (SceneKitAdditions)

/*! 
 Bridge with SCNAnimation
*/
/**
 Initializes a CoreAnimation animation from a SCNAnimation
 */
+ (CAAnimation *)animationWithSCNAnimation:(SCNAnimation *)animation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/*!
 @property usesSceneTimeBase
 @abstract Determines whether the receiver is evaluated using the scene time or the system time. Defaults to NO.
 @discussion A scene-time based animation is evaluated using the "sceneTime" value of the renderer that renders the scene.
 */
@property BOOL usesSceneTimeBase;

/*!
 @property fadeInDuration
 @abstract Determines the receiver's fade-in duration.
 @discussion When the fadeInDuration is greater than zero, the effect of the animation progressively increase from 0% to 100% during the specified duration.
 */
@property CGFloat fadeInDuration API_AVAILABLE(macos(10.9));
 
/*!
 @property fadeOutDuration
 @abstract Determines the receiver's fade-out duration.
 @discussion When the fadeOutDuration is greater than zero, the effect of the animation progressively decrease from 100% to 0% at the end of the animation duration.
 */
@property CGFloat fadeOutDuration API_AVAILABLE(macos(10.9));

/*!
 @property animationEvents
 @abstract Specifies the animation events attached to the receiver.
 */
@property(nonatomic, copy, nullable) NSArray<SCNAnimationEvent *> *animationEvents API_AVAILABLE(macos(10.9));

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNGeometry.h
//
//  SCNGeometry.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNBoundingVolume.h>
#import <SceneKit/SCNShadable.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNGeometrySource;
@class SCNGeometryElement;
@class SCNGeometryTessellator;
@class SCNLevelOfDetail;
@protocol MTLBuffer;

typedef NS_ENUM(NSInteger, SCNGeometryPrimitiveType) {
	SCNGeometryPrimitiveTypeTriangles                                                  = 0,
	SCNGeometryPrimitiveTypeTriangleStrip                                              = 1,
	SCNGeometryPrimitiveTypeLine                                                       = 2,
	SCNGeometryPrimitiveTypePoint                                                      = 3,
    SCNGeometryPrimitiveTypePolygon API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 4
};

typedef NSString * SCNGeometrySourceSemantic NS_EXTENSIBLE_STRING_ENUM;

SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticVertex;
SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticNormal;
SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticColor;
SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticTexcoord;
SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticTangent API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));
SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticVertexCrease API_AVAILABLE(macos(10.10));
SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticEdgeCrease API_AVAILABLE(macos(10.10));
SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticBoneWeights API_AVAILABLE(macos(10.10));
SCN_EXPORT SCNGeometrySourceSemantic const SCNGeometrySourceSemanticBoneIndices API_AVAILABLE(macos(10.10));

// MARK: -

/*!
 @class SCNGeometry
 @abstract SCNGeometry is an abstract class that represents the geometry that can be attached to a SCNNode. 
 */

SCN_EXPORT
@interface SCNGeometry : NSObject <SCNAnimatable, SCNBoundingVolume, SCNShadable, NSCopying, NSSecureCoding>

/*!
 @method geometry
 @abstract Creates and returns an empty geometry object.
 @discussion An empty geometry may be used as the lowest level of detail of a geometry.
 */
+ (instancetype)geometry API_AVAILABLE(macos(10.9));

/*!
 @property name
 @abstract Determines the name of the receiver.
 */
@property(nonatomic, copy, nullable) NSString *name;

/*! 
 @property materials
 @abstract Specifies the receiver's materials array.
 @discussion Each geometry element can be rendered using a different material. The index of the material used for a geometry element is equal to the index of that element modulo the number of materials.
 */
@property(nonatomic, copy) NSArray<SCNMaterial *> *materials;

/*!
 @property firstMaterial
 @abstract Determines the first material of the geometry. Returns nil if the geometry has no material.
 @discussion This method is here for convenience. It is equivalent to the first object in the "materials" array above.
 */
@property(nonatomic, retain, nullable) SCNMaterial *firstMaterial;

/*! 
 @method insertMaterial:atIndex:
 @abstract Insert a material in the materials array at the specified index.
 @param material The material to insert.
 @param index Index in the materials array to insert the new material.
 */
- (void)insertMaterial:(SCNMaterial *)material atIndex:(NSUInteger)index;

/*! 
 @method removeMaterialAtIndex:
 @abstract Remove the material at the specified index from the materials array.
 @param index The index of the material to remove from the 'materials' array.
 */
- (void)removeMaterialAtIndex:(NSUInteger)index;

/*! 
 @method replaceMaterialAtIndex:withMaterial:
 @abstract Remove the material at the index 'index' from the materials array of the receiver and insert 'material' in its position.
 @param index The index of the material to replace in the materials array.
 @param material The new material that will replace the previous one.
 */
- (void)replaceMaterialAtIndex:(NSUInteger)index withMaterial:(SCNMaterial *)material;

/*! 
 @method materialWithName:
 @abstract Return the first material from the materials array of the receiver with the specified name.
 @param name The name of the material to retrieve.
 */
- (nullable SCNMaterial *)materialWithName:(NSString *)name;

/*! 
 @method geometryWithSources:elements:
 @abstract Creates and returns a new geometry built from geometry sources and geometry elements.
 @param sources An array of geometry sources. If several geometry sources have the same semantic, only the first one is taken into account.
 @param elements An array of geometry elements. The sort order in the array determines the mapping between materials and geometry elements.
 @discussion A geometry is made of geometry sources (at least vertices) and at least one geometry element. Multiple sources for texture coordinates are accepted. In that case the mappingChannel is implicitly set based on the order of the texture sources, starting at index 0.
*/
+ (instancetype)geometryWithSources:(NSArray<SCNGeometrySource *> *)sources elements:(nullable NSArray<SCNGeometryElement *> *)elements;

/*!
 @property geometrySources
 @abstract The array of geometry sources of the receiver.
 */
@property(nonatomic, readonly) NSArray<SCNGeometrySource *> *geometrySources API_AVAILABLE(macos(10.10));

/*! 
 @method geometrySourcesForSemantic:
 @abstract Returns the geometry sources for a given semantic.
 @param semantic The semantic of the geometry sources that should be retrieved.
 @discussion Returns nil if no geometry source is found for the given semantic. May return more than one source, typically for multiple texture coordinate sources.
 */
- (NSArray<SCNGeometrySource *> *)geometrySourcesForSemantic:(SCNGeometrySourceSemantic)semantic;

/*!
 @property geometryElements
 @abstract The array of geometry elements of the receiver.
 */
@property(nonatomic, readonly) NSArray<SCNGeometryElement *> *geometryElements API_AVAILABLE(macos(10.10));

/*!
 @property geometryElementCount
 @abstract Returns the number of geometry elements owned by the geometry.
 */
@property(nonatomic, readonly) NSInteger geometryElementCount;

/*!
 @method geometryElementAtIndex:
 @abstract Returns the geometry element at a given index.
 @param elementIndex The index of the geometry element.
 */
- (SCNGeometryElement *)geometryElementAtIndex:(NSInteger)elementIndex;

/*!
 @property levelsOfDetail
 @abstract Determines the receiver's levels of detail. Defaults to nil.
 */
@property(nonatomic, copy, nullable) NSArray<SCNLevelOfDetail *> *levelsOfDetail API_AVAILABLE(macos(10.9));

/*!
 @property tessellator
 @abstract Specifies how the geometry should be tessellated at render time on the GPU. Defaults to nil.
 */
#if SCN_ENABLE_METAL
@property(nonatomic, retain, nullable) SCNGeometryTessellator *tessellator API_AVAILABLE(macos(10.13), ios(11.0), tvos(12.0)) API_UNAVAILABLE(watchos);
#endif

/*!
 @property subdivisionLevel
 @abstract Specifies the subdivision level of the receiver. Defaults to 0.
 @discussion A subdivision level of 0 means no subdivision. When the `tessellator` property of the receiver is not nil, the refinement is done on the GPU.
 */
@property(nonatomic) NSUInteger subdivisionLevel API_AVAILABLE(macos(10.10));

/*!
 @property wantsAdaptiveSubdivision
 @abstract Specifies if the subdivision is adaptive or uniform. Defaults to YES.
 @discussion Adaptive subdivision requires that the `tessellator` property of the receiver is not nil.
 */
@property(nonatomic) BOOL wantsAdaptiveSubdivision API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property edgeCreasesElement
 @abstract Specifies the edges creases that control the subdivision. Defaults to nil.
 @discussion The primitive type of this geometry element must be SCNGeometryPrimitiveTypeLine. See subdivisionLevel above to control the level of subdivision. See edgeCreasesElement above to specify edges for edge creases.
 */
@property(nonatomic, retain, nullable) SCNGeometryElement *edgeCreasesElement API_AVAILABLE(macos(10.10));

/*!
 @property edgeCreasesSource
 @abstract Specifies the crease value of the edges specified by edgeCreasesElement. Defaults to nil.
 @discussion The semantic of this geometry source must be "SCNGeometrySourceSemanticEdgeCrease". The creases values are floating values between 0 and 10, where 0 means smooth and 10 means infinitely sharp. See subdivisionLevel above to control the level of subdivision. See edgeCreasesElement above to specify edges for edge creases.
 */
@property(nonatomic, retain, nullable) SCNGeometrySource *edgeCreasesSource API_AVAILABLE(macos(10.10));

@end

// MARK: -

/*!
 @class SCNGeometrySource
 @abstract A geometry source contains geometry data for a specific semantic. The data format is described by properties.
 */

SCN_EXPORT
@interface SCNGeometrySource : NSObject <NSSecureCoding>

/*! 
 @method geometrySourceWithData:semantic:vectorCount:floatComponents:componentsPerVector:bytesPerComponent:dataOffset:dataStride:
 @abstract Creates and returns a geometry source from the given data and parameters.
 @param data The geometry data.
 @param semantic The semantic of the geometry source.
 @param vectorCount The number of geometry source vectors.
 @param floatComponents A flag that indicates if vector components are floating point values.
 @param componentsPerVector The number of scalar components in a vector.
 @param bytesPerComponent The number of bytes that represent a vector component.
 @param offset The offset from the beginning of the data. In bytes.
 @param stride The number of bytes from a vector to the next one in the data.
 */
+ (instancetype)geometrySourceWithData:(NSData *)data semantic:(SCNGeometrySourceSemantic)semantic vectorCount:(NSInteger)vectorCount floatComponents:(BOOL)floatComponents componentsPerVector:(NSInteger)componentsPerVector bytesPerComponent:(NSInteger)bytesPerComponent dataOffset:(NSInteger)offset dataStride:(NSInteger)stride;

/*!
 @method geometrySourceWithVertices:count:
 @abstract Creates and returns a geometry source from vertices stored in a buffer of SCNVector3 values.
 @param vertices The buffer of vertices.
 @param count The number of vertices.
 @discussion Input vertices are copied to an optimized data format. The actual format is described by the properties of the resulting instance.
 */
+ (instancetype)geometrySourceWithVertices:(const SCNVector3 *)vertices count:(NSInteger)count;

/*!
 @method geometrySourceWithNormals:count:
 @abstract Creates and returns a geometry source from normals stored in a buffer of SCNVector3 values.
 @param normals The buffer of normals.
 @param count The number of normals.
 @discussion Input normals are copied to an optimized data format. The actual format is described by the properties of the resulting instance.
 */
+ (instancetype)geometrySourceWithNormals:(const SCNVector3 *)normals count:(NSInteger)count;

/*!
 @method geometrySourceWithTextureCoordinates:count:
 @abstract Creates and returns a geometry source from texture coordinates stored in a buffer of CGPoint values.
 @param texcoord The buffer of texture coordinates.
 @param count The number of texture coordinate points.
 @discussion Input texture coordinates are copied to an optimized data format. The actual format is described by the properties of the resulting instance.
 */
+ (instancetype)geometrySourceWithTextureCoordinates:(const CGPoint *)texcoord count:(NSInteger)count;

#if SCN_ENABLE_METAL
/*!
 @method geometrySourceWithBuffer:semantic:vectorCount:floatComponents:componentsPerVector:bytesPerComponent:dataOffset:dataStride:
 @abstract Creates and returns a geometry source from the given data and parameters.
 @param mtlBuffer A metal buffer.
 @param vertexFormat The vertex format.
 @param semantic The semantic of the geometry source.
 @param vertexCount The number of vertex.
 @param offset The offset from the beginning of the data. In bytes.
 @param stride The number of bytes from a vector to the next one in the data.
 @discussion Attempting to modify the metal buffer outside the SCNSceneRenderer delegate callbacks is undefined.
 The typical usage it to modify the MTLBuffer within the willRenderScene callback, using a compute kernel or a vertex function in the user own command buffer. So something like:

 - (void)renderer:(id <SCNSceneRenderer>)aRenderer willRenderScene:(SCNScene *)scene atTime:(NSTimeInterval)time
 {
     // ask for a new command buffer
     id <MTLCommandBuffer> myCommandBuffer = [aRenderer.commandQueue commandBuffer];

     // get a compute command encoder
     id <MTLComputeCommandEncoder> myComputeCommandEncoder = [myCommandBuffer computeCommandEncoder];

     // configure the compute command encoder's pipeline state, buffer inputs etc...
     //...

     // dispatch the
     [myComputeCommandEncoder dispatchThreadgroups:numberOfWorkingGroups threadsPerThreadgroup:numberOfThreads];
     [myComputeCommandEncoder endEncoding];

     [myCommandBuffer commit];
 }
 
 */
+ (instancetype)geometrySourceWithBuffer:(id <MTLBuffer>)mtlBuffer vertexFormat:(MTLVertexFormat)vertexFormat semantic:(SCNGeometrySourceSemantic)semantic vertexCount:(NSInteger)vertexCount dataOffset:(NSInteger)offset dataStride:(NSInteger)stride API_AVAILABLE(macos(10.11), ios(9.0));
#endif

/*! 
 @property data
 @abstract The data for the geometry source
 */
@property(nonatomic, readonly) NSData *data;

/*! 
 @property semantic
 @abstract The semantic of the geometry source
 */
@property(nonatomic, readonly) SCNGeometrySourceSemantic semantic;

/*! 
 @property vectorCount
 @abstract The number of vectors in the data.
 */
@property(nonatomic, readonly) NSInteger vectorCount;

/*! 
 @property floatComponents
 @abstract A flag that indicates if vector components are floating point values.
 */
@property(nonatomic, readonly) BOOL floatComponents;

/*! 
 @property componentsPerVector
 @abstract The number of scalar components in each vector.
 */
@property(nonatomic, readonly) NSInteger componentsPerVector;

/*! 
 @property bytesPerComponent
 @abstract The size of a vector component in bytes.
 */
@property(nonatomic, readonly) NSInteger bytesPerComponent;

/*! 
 @property dataOffset
 @abstract The offset from the beginning of the data. In bytes.
 */
@property(nonatomic, readonly) NSInteger dataOffset;

/*! 
 @property dataStride
 @abstract The number of bytes from a vector to the next one in the data.
 */
@property(nonatomic, readonly) NSInteger dataStride;

@end

// MARK: -

/*!
 @class SCNGeometryElement
 @abstract A geometry element describes how vertices from a geometry source are connected together.
 */

SCN_EXPORT
@interface SCNGeometryElement : NSObject <NSSecureCoding>

/*!
 @method geometryElementWithData:primitiveType:primitiveCount:bytesPerIndex:
 @abstract Creates and returns a geometry element from the given data and data format info.
 @param data The data that contains element indexes. You can pass nil to use an implicit vertex ordering (0,1,2...).
 @param primitiveType The primitive type, as listed in the SCNGeometryPrimitiveType enumeration.
 @param primitiveCount The number of primitives in the data.
 @param bytesPerIndex The number of bytes that represent a single index value in the data.
 */
+ (instancetype)geometryElementWithData:(nullable NSData *)data primitiveType:(SCNGeometryPrimitiveType)primitiveType primitiveCount:(NSInteger)primitiveCount bytesPerIndex:(NSInteger)bytesPerIndex;

/*!
 @property data
 @abstract The data for the geometry element
 */
@property(nonatomic, readonly) NSData *data;

/*!
 @property primitiveType
 @abstract The type of the geometry element. Possible values are listed in the SCNGeometryPrimitiveType enumeration.
 */
@property(nonatomic, readonly) SCNGeometryPrimitiveType primitiveType;

/*!
 @property primitiveCount
 @abstract The number of primitives in the data.
 */
@property(nonatomic, readonly) NSInteger primitiveCount;

/*!
 @property primitiveRange
 @abstract Specifies the subrange of primitves to render within NSMakeRange(0, primitiveCount). Defaults to NSMakeRange(NSNotFound, 0).
 @discussion When the location of the range is set to NSNotFound, the entire geometry element is rendered.
 */
@property(nonatomic) NSRange primitiveRange API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property bytesPerIndex
 @abstract The number of bytes that represent an index value
 */
@property(nonatomic, readonly) NSInteger bytesPerIndex;

/*!
 @property pointSize
 @abstract Specifies the size of the point in local space. Defaults to 1
 */
@property(nonatomic) CGFloat pointSize API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property minimumPointScreenSpaceRadius
 @abstract Specifies the minimum size in screen-space (in pixel). Defaults to 1
 */
@property(nonatomic) CGFloat minimumPointScreenSpaceRadius API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property maximumPointScreenSpaceRadius
 @abstract Specifies the maximum size in screen-space (in pixel). Defaults to 1
 */
@property(nonatomic) CGFloat maximumPointScreenSpaceRadius API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@end

// MARK: -

#if SCN_ENABLE_METAL

typedef NS_ENUM(NSInteger, SCNTessellationSmoothingMode) {
    SCNTessellationSmoothingModeNone = 0,
    SCNTessellationSmoothingModePNTriangles,
    SCNTessellationSmoothingModePhong
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(12.0)) API_UNAVAILABLE(watchos);

/*!
 @class SCNGeometryTessellator
 @abstract A geometry tessellator describes how a more detailed surface is calculated from the geometry's initial surface.
 */

SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(12.0)) API_UNAVAILABLE(watchos)
@interface SCNGeometryTessellator : NSObject <NSCopying, NSSecureCoding>

/*!
 @property tessellationFactorScale
 @abstract Specifies the scale factor applied to the per-patch tessellation factors. Defaults to 1.
 */
@property(nonatomic) CGFloat tessellationFactorScale;

/*!
 @property tessellationPartitionMode
 @abstract Specifies the tessellation partition mode. Defaults to MTLTessellationPartitionModeInteger.
 */
@property(nonatomic) MTLTessellationPartitionMode tessellationPartitionMode;

/*!
 @property adaptive
 @abstract Specifies if the tessellation should be uniform or adaptive. Defaults to NO.
 */
@property(nonatomic, getter=isAdaptive) BOOL adaptive;

/*!
 @property screenspace
 @abstract Specifies if the level of tessellation should be adapted in screenSpace. Defaults to NO.
 */
@property(nonatomic, getter=isScreenSpace) BOOL screenSpace;

/*!
 @property edgeTessellationFactor
 @abstract Specifies the edge tessellation factor. Defaults to 1.
 @discussion This has no effect for adaptive subdivision
 */
@property(nonatomic) CGFloat edgeTessellationFactor;

/*!
 @property insideTessellationFactor
 @abstract Specifies the inside tessellation factor. Defaults to 1.
 @discussion This has no effect for adaptive subdivision
 */
@property(nonatomic) CGFloat insideTessellationFactor;

/*!
 @property maximumEdgeLength
 @abstract Specifies the maximum edge length. Defaults to 1.
 @discussion This has no effect for non-adaptive subdivision
 */
@property(nonatomic) CGFloat maximumEdgeLength;

/*!
 @property smoothingMode
 @abstract Defaults to SCNTessellationSmoothingModeNone.
 */
@property(nonatomic) SCNTessellationSmoothingMode smoothingMode;

@end

#endif

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNAction.h
//
//  SCNAction.h
//  SceneKit
//
//  Copyright © 2014-2017 Apple, Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;
@class SCNAction;
@class SCNAudioSource;

/**
 A custom timing function for SCNActions. Input time will be between 0.0 and 1.0
 over the duration of the action. Return values must be 0.0-1.0 and increasing
 and the function must return 1.0 when the input time reaches 1.0.
 */
typedef float (^SCNActionTimingFunction)(float time);

@protocol SCNActionable <NSObject>

/*!
 @method runAction:
 @abstract Adds an action to the list of actions executed by the node.
 */
- (void)runAction:(SCNAction *)action API_AVAILABLE(macos(10.10));

/*!
 @method runAction:completionHandler:
 @abstract Adds an action to the list of actions executed by the node. Your block is called when the action completes.
 */
- (void)runAction:(SCNAction *)action completionHandler:(nullable void (^)(void))block API_AVAILABLE(macos(10.10));

/*!
 @method runAction:forKey:
 @abstract Adds an identifiable action to the list of actions executed by the node.
 */
- (void)runAction:(SCNAction *)action forKey:(nullable NSString *)key API_AVAILABLE(macos(10.10));

/*!
 @method runAction:forKey:completionHandler:
 @abstract Adds an identifiable action to the list of actions executed by the node. Your block is called when the action completes.
 */
- (void)runAction:(SCNAction *)action forKey:(nullable NSString *)key completionHandler:(nullable void (^)(void))block API_AVAILABLE(macos(10.10));

/*!
 @property hasActions
 @abstract Returns a Boolean value that indicates whether the node is executing actions.
 */
@property(nonatomic, readonly) BOOL hasActions API_AVAILABLE(macos(10.10));

/*!
 @method actionForKey:
 @abstract Returns an action associated with a specific key.
 */
- (nullable SCNAction *)actionForKey:(NSString *)key API_AVAILABLE(macos(10.10));

/*!
 @method removeActionForKey:
 @abstract Removes an action associated with a specific key.
 */
- (void)removeActionForKey:(NSString *)key API_AVAILABLE(macos(10.10));

/*!
 @method removeAllActions
 @abstract Ends and removes all actions from the node.
 */
- (void)removeAllActions API_AVAILABLE(macos(10.10));

/*!
 @property actionKeys
 @abstract Returns an array containing the keys of all actions currently attached to the receiver.
 */
@property(nonatomic, readonly) NSArray<NSString *> *actionKeys API_AVAILABLE(macos(10.10));

@end


SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNAction : NSObject <NSCopying, NSSecureCoding>

/*!
 @property duration
 @abstract This is the expected duration of an action’s animation. The actual time an action takes to complete is modified by the speed property of the action.
 */
@property(nonatomic) NSTimeInterval duration;

/*!
 @property timingMode
 @abstract The timing mode used to execute an action.
 */
@property(nonatomic) SCNActionTimingMode timingMode;

/** When set, prodives a custom timing via a block. Applies after
 the 'timingMode' property is taken into account, defaults to nil
 @see SCNActionTimingFunction
 */
@property(nonatomic, nullable) SCNActionTimingFunction timingFunction;

/*!
 @property speed
 @abstract A speed factor that modifies how fast an action runs. Defaults to 1.
 */
@property(nonatomic) CGFloat speed;

/*!
 @method reversedAction
 @abstract Creates an action that reverses the behavior of another action.
 */
- (SCNAction *)reversedAction;

//Creates an action that moves a node relative to its current position.
+ (SCNAction *)moveByX:(CGFloat)deltaX y:(CGFloat)deltaY z:(CGFloat)deltaZ duration:(NSTimeInterval)duration;
+ (SCNAction *)moveBy:(SCNVector3)delta duration:(NSTimeInterval)duration;

//Creates an action that moves a node to a new position.
+ (SCNAction *)moveTo:(SCNVector3)location duration:(NSTimeInterval)duration;

//Creates an action that rotates the node by a relative value in radian.
+ (SCNAction *)rotateByX:(CGFloat)xAngle y:(CGFloat)yAngle z:(CGFloat)zAngle duration:(NSTimeInterval)duration;

//Creates an action that rotates the node to an absolute angle in radian.
+ (SCNAction *)rotateToX:(CGFloat)xAngle y:(CGFloat)yAngle z:(CGFloat)zAngle duration:(NSTimeInterval)duration;
+ (SCNAction *)rotateToX:(CGFloat)xAngle y:(CGFloat)yAngle z:(CGFloat)zAngle duration:(NSTimeInterval)duration shortestUnitArc:(BOOL)shortestUnitArc;

//Creates an action that rotates the node arond an axis by the specified angle in radian
+ (SCNAction *)rotateByAngle:(CGFloat)angle aroundAxis:(SCNVector3)axis duration:(NSTimeInterval)duration;
+ (SCNAction *)rotateToAxisAngle:(SCNVector4)axisAngle duration:(NSTimeInterval)duration;

//Creates an action that changes the x, y and z scale values of a node by a relative value.
+ (SCNAction *)scaleBy:(CGFloat)scale duration:(NSTimeInterval)sec;

//Creates an action that changes the x, y and z scale values of a node.
+ (SCNAction *)scaleTo:(CGFloat)scale duration:(NSTimeInterval)sec;

//Creates an action that runs a collection of actions sequentially.
+ (SCNAction *)sequence:(NSArray<SCNAction *> *)actions;

//Creates an action that runs a collection of actions in parallel.
+ (SCNAction *)group:(NSArray<SCNAction *> *)actions;

//Creates an action that repeats another action a specified number of times.
+ (SCNAction *)repeatAction:(SCNAction *)action count:(NSUInteger)count;

//Creates an action that repeats another action forever.
+ (SCNAction *)repeatActionForever:(SCNAction *)action;

//Creates an action that changes the opacity value of the node to 1.0
+ (SCNAction *)fadeInWithDuration:(NSTimeInterval)sec;

//Creates an action that changes the opacity value of the node to 0.0
+ (SCNAction *)fadeOutWithDuration:(NSTimeInterval)sec;

//Creates an action that adjusts the opacity value of a node by a relative value.
+ (SCNAction *)fadeOpacityBy:(CGFloat)factor duration:(NSTimeInterval)sec;

//Creates an action that adjusts the opacity value of a node to a new value.
+ (SCNAction *)fadeOpacityTo:(CGFloat)opacity duration:(NSTimeInterval)sec;

//Creates an action that hides a node
+ (SCNAction *)hide API_AVAILABLE(macos(10.11), ios(9.0));

//Creates an action that unhides a node
+ (SCNAction *)unhide API_AVAILABLE(macos(10.11), ios(9.0));

//Creates an action that idles for a specified period of time.
+ (SCNAction *)waitForDuration:(NSTimeInterval)sec;

//Creates an action that idles for a randomized period of time.
+ (SCNAction *)waitForDuration:(NSTimeInterval)sec withRange:(NSTimeInterval)durationRange;

//Creates an action that removes the node from its parent node.
+ (SCNAction *)removeFromParentNode;

//Creates an action that executes a block.
+ (SCNAction *)runBlock:(void (^)(SCNNode *node))block;
+ (SCNAction *)runBlock:(void (^)(SCNNode *node))block queue:(dispatch_queue_t)queue;

//Creates an action that runs a javascript script over a duration. the node can be accessed from javascript via the "node" symbol and the elapsed time (between 0 and 1 relative to the duration) via the "elapsedTime" symbol.
+ (SCNAction *)javaScriptActionWithScript:(NSString *)script duration:(NSTimeInterval)seconds;

//Creates an action that executes a block over a duration.
+ (SCNAction *)customActionWithDuration:(NSTimeInterval)seconds actionBlock:(void (^)(SCNNode *node, CGFloat elapsedTime))block;

/** Creates an action that plays a sound
 @param source The audio source to play (see SCNAudioSource.h)
 @param wait If YES, then the duration of this action is the same
 as the length of the audio playback. If NO, the action is considered
 to have completed immediately.*/
+ (SCNAction *)playAudioSource:(SCNAudioSource *)source waitForCompletion:(BOOL)wait API_AVAILABLE(macos(10.11), ios(9.0));

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNTransaction.h
//
//  SCNTransaction.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CAMediaTimingFunction;

/* Transactions are SceneKit's mechanism for batching multiple scene graph
 * operations into atomic updates. Every
 * modification to the scene graph requires a transaction to be part of. */

SCN_EXPORT
@interface SCNTransaction : NSObject

/* Begin a new transaction for the current thread; nests. */
+ (void)begin;

/* Commit all changes made during the current transaction. */
+ (void)commit;

/* Commits any extant implicit transaction. Will delay the actual commit
 * until any nested explicit transactions have completed. */
+ (void)flush;

/* Methods to lock and unlock the global lock. */
+ (void)lock;
+ (void)unlock;

/* Accessors for the "animationDuration" per-thread transaction
 * property. Defines the default duration of animations. Defaults to 1/4s for explicit transactions, 0s for implicit transactions. */
@property(class, nonatomic) CFTimeInterval animationDuration;

/* Accessors for the "animationTimingFunction" per-thread transaction
 * property. The default value is nil, when set to a non-nil value any
 * animations added to scene graph will have this value set as their
 * "timingFunction" property. */
@property(class, nonatomic, copy, nullable) CAMediaTimingFunction *animationTimingFunction API_UNAVAILABLE(watchos);

/* Accessors for the "disableActions" per-thread transaction property.
 * Defines whether or not the implicit animations are performed. 
 * Defaults to NO, i.e. implicit animations enabled. */
@property(class, nonatomic) BOOL disableActions;

/* Accessors for the "completionBlock" per-thread transaction property.
 * Once set to a non-nil value the block is guaranteed to be called (on
 * the main thread) as soon as all animations subsequently added by
 * this transaction group have completed (or been removed). */
@property(class, nonatomic, copy, nullable) void (^completionBlock)(void);

/* Associate arbitrary keyed-data with the current transaction (i.e.
 * with the current thread).
 */
+ (nullable id)valueForKey:(NSString *)key;
+ (void)setValue:(nullable id)value forKey:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNPhysicsField.h
//
//  SCNPhysicsField.h
//  SceneKit
//
//  Copyright © 2014-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;

/*! 
 @enum SCNPhysicsFieldScope
 @abstract Specifies the domain of influence of a physics field.
 */
typedef NS_ENUM(NSInteger, SCNPhysicsFieldScope) {
    SCNPhysicsFieldScopeInsideExtent,
    SCNPhysicsFieldScopeOutsideExtent,
} API_AVAILABLE(macos(10.10));

/*!
 @class SCNPhysicsField
 @abstract SCNPhysicsField is an abstract class that describes a force field that applies in the physics world.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsField : NSObject <NSCopying, NSSecureCoding>

// The following properties control the behavior of the field
@property(nonatomic) CGFloat strength;                               // The strength factor of the force field. Defaults to 1.0.
@property(nonatomic) CGFloat falloffExponent;                        // Changes the power of the force based on the distance from the center of the field (1 / distance ^ falloffExponent). Defaults to 0.0.
@property(nonatomic) CGFloat minimumDistance;                        // Distance from the center of the field where the effect is at full strength. Defaults to 1e-6.

@property(nonatomic, getter=isActive) BOOL active;                   // Specifies whether force field is active or not. Defaults to YES.
@property(nonatomic, getter=isExclusive) BOOL exclusive;             // If YES, it suppresses any other field in its area. Defaults to NO.

// The following properties control the area of effect
@property(nonatomic) SCNVector3 halfExtent;                          // Specifies the half extent of the area of effect. Defaults to FLT_MAX.
@property(nonatomic) BOOL usesEllipsoidalExtent;                     // YES means that the area of effect is rounded within the extent. Defaults to NO.
@property(nonatomic) SCNPhysicsFieldScope scope;                     // Controls whether the force field should apply inside or outside of the area. Defaults to inside.

@property(nonatomic) SCNVector3 offset;                              // Offset of origin effect within the area.
@property(nonatomic) SCNVector3 direction;                           // Direction of the field. Only applies to linear gravity and vortex fields. Defaults to (0,-1,0).

/*!
 @property categoryBitMask
 @abstract Determines the node physicsBody's categories that will be influenced by the receiver. Defaults to all bit set.
 */
@property(nonatomic) NSUInteger categoryBitMask API_AVAILABLE(macos(10.10));


/**
 Slows an object proportionally to the object’s velocity.
 Use this to simulate effects such as friction from motion through the air.
 */
+ (SCNPhysicsField *)dragField;

/**
 Applies a force tangential to the direction from the sample point to the field's position.
 The force will be CCW to the direction. Make the strength negative to apply force in the CW direction.
 Amount is proportional to distance from center and the object's mass.
 Use this to create effects such as tornadoes.
 */
+ (SCNPhysicsField *)vortexField;

/**
 Applies a force in the direction of the origin of the field in local space. To repel objects, use a negative strength.
 The force is proportional to the distance from the field origin. Varies with the mass of the object according to F = ma
 The field node's rotation property can be used to orient the gravity in a particular direction.
 */
+ (SCNPhysicsField *)radialGravityField;

/**
 Applies a force in the direction of the "direction" vector in the local space. To repel objects, use a negative strength.
 The force is the same everywhere in the field. Varies with the mass of the object according to F = ma
 The field node's rotation property can be used to orient the gravity in a particular direction.
 */
+ (SCNPhysicsField *)linearGravityField;

/**
 A time varying differentiable Perlin simplex noise field. A smoothness of 0 means as noisy as possible.
 Use this to simulate such effects as fireflies, or snow.
 To freeze the noise in place, set animationSpeed to 0.0. Mass is ignored.
 You can change the "smoothness" and "animationSpeed" using KVC.
 */
+ (SCNPhysicsField *)noiseFieldWithSmoothness:(CGFloat)smoothness animationSpeed:(CGFloat)speed;

/**
 Just like Noise, except the strength of the noise is proportional to the velocity of the object in the field.
 */
+ (SCNPhysicsField *)turbulenceFieldWithSmoothness:(CGFloat)smoothness animationSpeed:(CGFloat)speed;

/**
 A Hooke’s law force - a force linearly proportional to distance from the center of the field. An object in this
 field will oscillate with a period proportional to the inverse of the mass.
 An example use is to keep objects confined to a particular region.
 */
+ (SCNPhysicsField *)springField;

/**
 A force proportional to the charge on the object. An example use of this field is to make objects behavior differently
 from one another when they enter a region, or to make an object's behavior different than its mass based behavior
 This field models the first part of the Lorentz equation, F = qE
 */
+ (SCNPhysicsField *)electricField;

/**
 A force proportional to the charge on the object and the object’s velocity. 
 An example use of this field is to make objects behavior differently from one another when they enter a region, or to make an object's behavior different than its mass based behavior
 This field models the second part of the Lorentz equation, F = qvB
 */
+ (SCNPhysicsField *)magneticField;

typedef SCNVector3 (^SCNFieldForceEvaluator)(SCNVector3 position, SCNVector3 velocity, float mass, float charge, NSTimeInterval time);

/**
 A field force with a custom force evaluator.
 */
+ (SCNPhysicsField *)customFieldWithEvaluationBlock:(SCNFieldForceEvaluator)block;

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/ModelIO.h
//
//  ModelIO.h
//  SceneKit
//
//  Copyright © 2015-2018 Apple Inc. All rights reserved.
//

#import <ModelIO/ModelIO.h>

#import <SceneKit/SCNNode.h>
#import <SceneKit/SCNScene.h>
#import <SceneKit/SCNLight.h>
#import <SceneKit/SCNCamera.h>
#import <SceneKit/SCNGeometry.h>
#import <SceneKit/SCNMaterial.h>

NS_ASSUME_NONNULL_BEGIN

/*! 
 @header ModelIO.h
 @abstract Bridge with the Model I/O framework
 */

@interface SCNScene (SCNModelIO)
+ (instancetype)sceneWithMDLAsset:(MDLAsset *)mdlAsset API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface MDLAsset (SCNModelIO)
+ (instancetype)assetWithSCNScene:(SCNScene *)scnScene API_AVAILABLE(macos(10.11), ios(9.0));
+ (instancetype)assetWithSCNScene:(SCNScene *)scnScene bufferAllocator:(nullable id <MDLMeshBufferAllocator>)bufferAllocator API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));
@end

@interface SCNNode (SCNModelIO)
+ (instancetype)nodeWithMDLObject:(MDLObject *)mdlObject API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface MDLObject (SCNModelIO)
+ (instancetype)objectWithSCNNode:(SCNNode *)scnNode API_AVAILABLE(macos(10.11), ios(9.0));
+ (instancetype)objectWithSCNNode:(SCNNode *)scnNode bufferAllocator:(nullable id <MDLMeshBufferAllocator>)bufferAllocator API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));
@end

@interface SCNGeometry (SCNModelIO)
+ (instancetype)geometryWithMDLMesh:(MDLMesh *)mdlMesh API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface MDLMesh (SCNModelIO)
+ (instancetype)meshWithSCNGeometry:(SCNGeometry *)scnGeometry API_AVAILABLE(macos(10.11), ios(9.0));
+ (instancetype)meshWithSCNGeometry:(SCNGeometry *)scnGeometry bufferAllocator:(nullable id <MDLMeshBufferAllocator>)bufferAllocator API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));
@end

@interface SCNGeometryElement (SCNModelIO)
+ (instancetype)geometryElementWithMDLSubmesh:(MDLSubmesh *)mdlSubMesh API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface MDLSubmesh (SCNModelIO)
+ (instancetype)submeshWithSCNGeometryElement:(SCNGeometryElement *)scnGeometryElement API_AVAILABLE(macos(10.11), ios(9.0));
+ (instancetype)submeshWithSCNGeometryElement:(SCNGeometryElement *)scnGeometryElement bufferAllocator:(nullable id <MDLMeshBufferAllocator>)bufferAllocator API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));
@end

@interface SCNMaterial (SCNModelIO)
+ (instancetype)materialWithMDLMaterial:(MDLMaterial *)mdlMaterial API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface MDLMaterial (SCNModelIO)
+ (instancetype)materialWithSCNMaterial:(SCNMaterial *)scnMaterial API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface SCNLight (SCNModelIO)
+ (instancetype)lightWithMDLLight:(MDLLight *)mdlLight API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface MDLLight (SCNModelIO)
+ (instancetype)lightWithSCNLight:(SCNLight *)scnLight API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface SCNCamera (SCNModelIO)
+ (instancetype)cameraWithMDLCamera:(MDLCamera *)mdlCamera API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface MDLCamera (SCNModelIO)
+ (instancetype)cameraWithSCNCamera:(SCNCamera *)scnCamera API_AVAILABLE(macos(10.11), ios(9.0));
@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNMorpher.h
//
//  SCNMorpher.h
//  SceneKit
//
//  Copyright © 2013-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNGeometry;

typedef NS_ENUM(NSInteger, SCNMorpherCalculationMode) {
    SCNMorpherCalculationModeNormalized = 0, // (1 - w0 - w1 - ...) * BaseMesh + w0 * Target0 + w1 * Target1 + ...
    SCNMorpherCalculationModeAdditive   = 1  // BaseMesh + w0 * Target0 + w1 * Target1 + ...
};

/*!
 @class SCNMorpher
 @abstract SCNMorpher controls the deformation of morphed geometries
 */
SCN_EXPORT API_AVAILABLE(macos(10.9))
@interface SCNMorpher : NSObject <SCNAnimatable, NSSecureCoding>

/*!
 @property targets
 @abstract Specifies the morph targets as an array of SCNGeometry.
 @discussion The target geometries must have the same number of entries in their geometry sources and the same topology as the base geometry.
 */
@property(nonatomic, copy) NSArray<SCNGeometry *> *targets;

/*!
 @property weights
 @abstract Access to all the weights of all the targets.
 */
@property(nonatomic, retain) NSArray<NSNumber *> *weights API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @method setWeight:forTargetAtIndex:
 @abstract Sets the weight for the target at the specified index. Animatable implicitly or explicitly with the keyPath "weights[index]" or "weights["targetName"]" (targetName is the name of the target geometry).
 */
- (void)setWeight:(CGFloat)weight forTargetAtIndex:(NSUInteger)targetIndex;

/*!
 @method weightForTargetAtIndex:
 @abstract Retrieves the weight for the target at the specified index.
 */
- (CGFloat)weightForTargetAtIndex:(NSUInteger)targetIndex;
    
/*!
 @method setWeight:forTargetNamed:
 @abstract Sets the weight for the target with the specified name (targetName is the name of the target geometry).
 */
- (void)setWeight:(CGFloat)weight forTargetNamed:(NSString *)targetName API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
    
/*!
 @method weightForTargetNamed:
 @abstract Retrieves the weight for the target with the specified name (targetName is the name of the target geometry).
 */
- (CGFloat)weightForTargetNamed:(NSString *)targetName API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
    
/*!
 @property calculationMode
 @abstract Specifies how the morph result is calculated by the receiver. Defaults to SCNMorpherCalculationModeNormalized.
 */
@property(nonatomic) SCNMorpherCalculationMode calculationMode;


/*!
 @property unifiesNormals
 @abstract When set to YES the normals are not morphed but are recomputed after morphing the vertex instead. When set to NO, the morpher will morph the normals if the geometry targets have normals. Defaults to NO.
 */
@property BOOL unifiesNormals API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
    
@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SceneKitAvailability.h
//
//  SceneKitAvailability.h
//  SceneKit
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#define SCN_EXPORT __attribute__((visibility("default"))) FOUNDATION_EXTERN
// ==========  SceneKit.framework/Headers/SCNParametricGeometry.h
//
//  SCNParametricGeometry.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SCNGeometry.h>

NS_ASSUME_NONNULL_BEGIN

@class UIFont;
@class UIBezierPath;
@class SCNGeometry;

/*!
 @class SCNPlane
 @abstract SCNPlane represents a rectangle with controllable width and height. The plane has one visible side.
 */

SCN_EXPORT
@interface SCNPlane : SCNGeometry

/*!
 @method planeWithWidth:height:
 @abstract Creates and returns a plane with given width and height.
 @param width The width of the plane.
 @param height The height of the plane.
 */
+ (instancetype)planeWithWidth:(CGFloat)width height:(CGFloat)height;

/*! 
 @property width
 @abstract The plane extent along the X axis. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat width;

/*! 
 @property height
 @abstract The plane extent along the Y axis. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat height;

/*! 
 @property widthSegmentCount
 @abstract The number of subdivisions along the X axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger widthSegmentCount;

/*! 
 @property heightSegmentCount
 @abstract The number of subdivisions along the Y axis. The default value is 1. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger heightSegmentCount;

/*!
 @property cornerRadius
 @abstract The corner radius. Animatable.
 @discussion If the value is strictly less than 0, the geometry is empty. The default value is 0.
 */
@property(nonatomic) CGFloat cornerRadius API_AVAILABLE(macos(10.9));

/*!
 @property cornerSegmentCount
 @abstract The number of subdivisions for the rounded corners. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 10.
 */
@property(nonatomic) NSInteger cornerSegmentCount API_AVAILABLE(macos(10.9));

@end


/*!
 @class SCNBox
 @abstract SCNBox represents a box with rectangular sides and optional chamfers.
 */

SCN_EXPORT
@interface SCNBox : SCNGeometry

/*!
 @method boxWithWidth:height:length:chamferRadius:
 @abstract Creates and returns a box with given width, height, length and chamfer radius.
 @param width The width of the box.
 @param height The height of the box.
 @param length The length of the box.
 @param chamferRadius The chamfer radius of the box.
 */
+ (instancetype)boxWithWidth:(CGFloat)width height:(CGFloat)height length:(CGFloat)length chamferRadius:(CGFloat)chamferRadius;

/*! 
 @property width
 @abstract The width of the box. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat width;

/*! 
 @property height
 @abstract The height of the box. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat height;

/*! 
 @property length
 @abstract The length of the box. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat length;

/*! 
 @property chamferRadius
 @abstract The chamfer radius. Animatable.
 @discussion If the value is strictly less than 0, the geometry is empty. The default value is 0.
 */
@property(nonatomic) CGFloat chamferRadius;

/*! 
 @property widthSegmentCount
 @abstract The number of subdivisions along the X axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger widthSegmentCount;

/*! 
 @property heightSegmentCount
 @abstract The number of subdivisions along the Y axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger heightSegmentCount;

/*! 
 @property lengthSegmentCount
 @abstract The number of subdivisions along the Z axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger lengthSegmentCount;

/*!
 @property chamferSegmentCount
 @abstract The number of chamfer subdivisions. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 5.
 */
@property(nonatomic) NSInteger chamferSegmentCount;

@end


/*!
 @class SCNPyramid
 @abstract SCNPyramid represents a right pyramid with a rectangular base.
 */

SCN_EXPORT
@interface SCNPyramid : SCNGeometry

/*!
 @method pyramidWithWidth:height:length:
 @abstract Creates and returns a pyramid with given width, height, and length.
 @param width The width of the pyramid.
 @param height The height of the pyramid.
 @param length The length of the pyramid.
 */
+ (instancetype)pyramidWithWidth:(CGFloat)width height:(CGFloat)height length:(CGFloat)length;

/*! 
 @property width
 @abstract The width of the pyramid base. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat width;

/*! 
 @property height
 @abstract The height of the pyramid. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat height;

/*! 
 @property length
 @abstract The length of the pyramid base. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat length;

/*! 
 @property widthSegmentCount
 @abstract The number of subdivisions along the X axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1. 
 */
@property(nonatomic) NSInteger widthSegmentCount;

/*! 
 @property heightSegmentCount
 @abstract The number of subdivisions along the Y axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1. 
 */
@property(nonatomic) NSInteger heightSegmentCount;

/*! 
 @property lengthSegmentCount
 @abstract The number of subdivisions along the Z axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1. 
 */
@property(nonatomic) NSInteger lengthSegmentCount;

@end


/*!
 @class SCNSphere
 @abstract SCNSphere represents a sphere with controllable radius
 */

SCN_EXPORT
@interface SCNSphere : SCNGeometry

/*!
 @method sphereWithRadius:
 @abstract Creates and returns a sphere with given radius.
 @param radius The radius of the sphere.
 */
+ (instancetype)sphereWithRadius:(CGFloat)radius;

/*! 
 @property radius
 @abstract The sphere radius. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 0.5.
 */
@property(nonatomic) CGFloat radius;

/*! 
 @property geodesic
 @abstract Indicate if the geometry is a geosphere.
 @discussion The default value is NO.
 */
@property(nonatomic, getter=isGeodesic) BOOL geodesic;

/*!
 @property segmentCount
 @abstract The number of segments along both spherical coordinates. Animatable.
 @discussion If the value is less than 3, the behavior is undefined. The default value is 24.
 */
@property(nonatomic) NSInteger segmentCount;

@end


/*!
 @class SCNCylinder
 @abstract SCNCylinder represents a cylinder with controllable height and radius.
 */

SCN_EXPORT
@interface SCNCylinder : SCNGeometry

/*!
 @method cylinderWithRadius:height:
 @abstract Creates and returns a cylinder with given radius and height.
 @param radius The radius of the cylinder.
 @param height The height of the cylinder. 
 */
+ (instancetype)cylinderWithRadius:(CGFloat)radius height:(CGFloat)height;

/*! 
 @property radius
 @abstract The radius of the cylinder. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 0.5.
 */
@property(nonatomic) CGFloat radius;

/*! 
 @property height
 @abstract The height of the cylinder. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat height;

/*! 
 @property radialSegmentCount
 @abstract The number of subdivisions along the radial coordinate. Animatable.
 @discussion If the value is less than 3, the behavior is undefined. The default value is 48.
 */
@property(nonatomic) NSInteger radialSegmentCount;

/*! 
 @property heightSegmentCount
 @abstract The number of subdivisions along the Y axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger heightSegmentCount;

@end


/*!
 @class SCNCone
 @abstract SCNCone represents a cone with controllable height, top radius and bottom radius.
 */

SCN_EXPORT
@interface SCNCone : SCNGeometry

/*!
 @method coneWithTopRadius:bottomRadius:height:
 @abstract Creates and returns a cone with given top radius, bottom radius and height.
 @param topRadius The radius at the top of the cone.
 @param bottomRadius The radius at the bottom of the cone.
 @param height The height of the cone.
 */
+ (instancetype)coneWithTopRadius:(CGFloat)topRadius bottomRadius:(CGFloat)bottomRadius height:(CGFloat)height;

/*! 
 @property topRadius
 @abstract The radius at the top of the cone. Animatable.
 @discussion If the value is less than 0, the geometry is empty. The default value is 0.
 */
@property(nonatomic) CGFloat topRadius;

/*! 
 @property bottomRadius
 @abstract The radius at the bottom of the cone. Animatable.
 @discussion If the value is less than 0, the geometry is empty. The default value is 0.5.
 */
@property(nonatomic) CGFloat bottomRadius;

/*! 
 @property height
 @abstract The height of the cone. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat height;

/*! 
 @property radialSegmentCount
 @abstract The number of subdivisions along the radial coordinate. Animatable.
 @discussion If the value is less than 3, the behavior is undefined. The default value is 48.
 */
@property(nonatomic) NSInteger radialSegmentCount;

/*! 
 @property heightSegmentCount
 @abstract The number of subdivisions along the Y axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger heightSegmentCount;

@end


/*!
 @class SCNTube
 @abstract SCNTube represents a tube with controllable height, inner radius and outer radius.
 */

SCN_EXPORT
@interface SCNTube : SCNGeometry

/*!
 @method tubeWithInnerRadius:outerRadius:height:
 @abstract Creates and returns a tube with given inner radius, outer radius and height.
 @param innerRadius The inner radius of the tube.
 @param outerRadius The outer radius of the tube.
 @param height The height of the tube.
 */
+ (instancetype)tubeWithInnerRadius:(CGFloat)innerRadius outerRadius:(CGFloat)outerRadius height:(CGFloat)height;

/*! 
 @property innerRadius
 @abstract The inner radius of the tube. Animatable.
 @discussion If the value is less than or equal to 0, or if it is greater than or equal to the outer radius, then the geometry is empty. The default value is 0.25.
 */
@property(nonatomic) CGFloat innerRadius;

/*! 
 @property outerRadius
 @abstract The outer radius of the tube. Animatable.
 @discussion If the value is less than or equal to 0, or if it is less than or equal to the inner radius, then the geometry is empty. The default value is 0.5.
 */
@property(nonatomic) CGFloat outerRadius;

/*! 
 @property height
 @abstract The height of the tube. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 1.
 */
@property(nonatomic) CGFloat height;

/*! 
 @property radialSegmentCount
 @abstract The number of subdivisions along the radial coordinate. Animatable.
 @discussion If the value is less than 3, the behavior is undefined. The default value is 48.
 */
@property(nonatomic) NSInteger radialSegmentCount;

/*! 
 @property heightSegmentCount
 @abstract The number of subdivisions along the Y axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger heightSegmentCount;

@end


/*!
 @class SCNCapsule
 @abstract SCNCapsule represents a capsule with controllable height and cap radius.
 */

SCN_EXPORT
@interface SCNCapsule : SCNGeometry

/*!
 @method capsuleWithCapRadius:height:
 @abstract Creates and returns a capsule with given radius and height.
 @param capRadius The radius of the capsule.
 @param height The height of the capsule.
 */
+ (instancetype)capsuleWithCapRadius:(CGFloat)capRadius height:(CGFloat)height;

/*! 
 @property capRadius
 @abstract The cap radius of the capsule. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 0.5.
 */
@property(nonatomic) CGFloat capRadius;

/*! 
 @property height
 @abstract The height of the capsule. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 2.
 */
@property(nonatomic) CGFloat height;

/*! 
 @property radialSegmentCount
 @abstract The number of subdivisions along the radial coordinate. Animatable.
 @discussion If the value is less than 3, the behavior is undefined. The default value is 48.
 */
@property(nonatomic) NSInteger radialSegmentCount;

/*! 
 @property heightSegmentCount
 @abstract The number of subdivisions along the Y axis. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 1.
 */
@property(nonatomic) NSInteger heightSegmentCount;

/*! 
 @property capSegmentCount
 @abstract The number of subdivisions in the cap. Animatable.
 @discussion If the value is less than 2, the behavior is undefined. The default value is 24.
 */
@property(nonatomic) NSInteger capSegmentCount;

@end


/*!
 @class SCNTorus
 @abstract SCNTorus represents a torus with controllable ring radius and pipe radius.
 */

SCN_EXPORT
@interface SCNTorus : SCNGeometry

/*!
 @method torusWithRingRadius:pipeRadius:
 @abstract Creates and returns a torus with given ring radius and pipe radius.
 @param ringRadius The radius of the ring.
 @param pipeRadius The radius of the pipe.
 */
+ (instancetype)torusWithRingRadius:(CGFloat)ringRadius pipeRadius:(CGFloat)pipeRadius;

/*! 
 @property ringRadius
 @abstract The radius of the torus ring. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 0.5.
 */
@property(nonatomic) CGFloat ringRadius;

/*! 
 @property pipeRadius
 @abstract The radius of the torus pipe. Animatable.
 @discussion If the value is less than or equal to 0, the geometry is empty. The default value is 0.25.
 */
@property(nonatomic) CGFloat pipeRadius;

/*! 
 @property ringSegmentCount
 @abstract The number of subdivisions of the ring. Animatable.
 @discussion If the value is less than 3, the behavior is undefined. The default value is 48.
 */
@property(nonatomic) NSInteger ringSegmentCount;

/*! 
 @property pipeSegmentCount
 @abstract The number of subdivisions of the pipe. Animatable.
 @discussion If the value is less than 3, the behavior is undefined. The default value is 24.
 */
@property(nonatomic) NSInteger pipeSegmentCount;

@end


/*!
 @class SCNFloor
 @abstract SCNFloor represents an infinite plane geometry. 
 */

SCN_EXPORT
@interface SCNFloor : SCNGeometry 

/*!
 @method floor
 @abstract Creates and returns a floor.
 @discussion A floor is an infinite plane.
 */
+ (instancetype)floor;

/*! 
 @property reflectivity
 @abstract Specifies the reflectivity of the floor. Animatable.
 @discussion If the value is greater than zero then the surface will reflect other objects in the scene. The default value is 0.25.
 */
@property(nonatomic) CGFloat reflectivity;

/*! 
 @property reflectionFalloffStart
 @abstract Specifies the distance from the floor where the falloff begins. Animatable.
 @discussion The default value is 0.
 */
@property(nonatomic) CGFloat reflectionFalloffStart;

/*! 
 @property reflectionFalloffEnd
 @abstract Specifies the distance from the floor where the falloff finishes. Animatable.
 @discussion If the value is 0 then there is no falloff. The default value is 0.
 */
@property(nonatomic) CGFloat reflectionFalloffEnd;

/*!
 @property reflectionCategoryBitMask
 @abstract Determines the node categories to reflect. Defaults to all bits set.
 */
@property(nonatomic) NSUInteger reflectionCategoryBitMask API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property width
 @abstract The floor extent along the X axis. Animatable.
 @discussion If the value is equal to 0, the floor is infinite on the X axis. The default value is 0.
 */
@property(nonatomic) CGFloat width API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property length
 @abstract The floor extent along the Z axis. Animatable.
 @discussion If the value is equal to 0, the floor is infinite on the Z axis. The default value is 0.
 */
@property(nonatomic) CGFloat length API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));


/*!
 @property reflectionResolutionScaleFactor
 @abstract Specifies the resolution scale factor of the buffer used to render the reflection.
 @discussion Defaults to 0.5.
#endif
*/
@property(nonatomic) CGFloat reflectionResolutionScaleFactor API_AVAILABLE(macos(10.10));

@end

/*!
 @class SCNText
 @abstract SCNText represents a block of text that has been extruded
 */

SCN_EXPORT
@interface SCNText : SCNGeometry 

/*!
 @method textWithString:extrusionDepth:
 @abstract Creates and returns a 3D representation of given text with given extrusion depth.
 @param string The text to be represented.
 @param extrusionDepth The extrusion depth.
 */
+ (instancetype)textWithString:(nullable id)string extrusionDepth:(CGFloat)extrusionDepth;

/*! 
 @property extrusionDepth
 @abstract The extrusion depth. Animatable.
 @discussion If the value is 0, we get a mono-sided, 2D version of the text.
 */
@property(nonatomic) CGFloat extrusionDepth;

/*! 
 @property string
 @abstract The text to be represented. The text must be an instance of NSString or NSAttributedString.
 @discussion The default value is nil.
 */
@property(nonatomic, copy, nullable) id string;

/*!
 @property font
 @abstract The font used to represent the text.
 @discussion The font property is only used when the string property is not an NSAttributedString. Defaults to Helvetica 36 point.
 */
@property(nonatomic, retain, null_resettable) UIFont *font;

/*!
 @property wrapped
 @abstract Determines whether the text is wrapped to fit within the bounds.
 @discussion For the text to be wrapped you first need to set its bounds, otherwise the text is not wrapped. The default value is NO.
 */
@property(nonatomic, getter=isWrapped) BOOL wrapped;

/*!
 @property containerFrame
 @abstract A container within which the text may be wrapped or truncated.
 @discussion The text will start at the top-left corner of the rect. You need to set this property for text truncation or alignment to work. Getting this property when it has never been set returns CGRectZero.
 */
@property(nonatomic) CGRect containerFrame;

/*!
 @property truncationMode
 @abstract Describes how the text is truncated to fit within the bounds.
 @discussion For the text to be truncated you first need to set its bounds, otherwise the text is not truncated. The default value is kCATruncationNone. See truncation modes in CATextLayer.h.
 */
@property(nonatomic, copy) NSString *truncationMode;

/*!
 @property alignmentMode
 @abstract Determines how individual lines of text are horizontally aligned within the bounds.
 @discussion For the text to be aligned you first need to set its bounds, otherwise the text is not aligned. The default value is kCAAlignmentNatural. See alignments in CATextLayer.h.
 */
@property(nonatomic, copy) NSString *alignmentMode;

/*! 
 @property chamferRadius
 @abstract The chamfer radius. Animatable.
 @discussion Values are clamped to the range [0, extrusionDepth / 2]. The actual chamfer radius might be different to the one here specified: large values are clipped to a per-glyph max value. The default value is 0.
 */
@property(nonatomic) CGFloat chamferRadius;

/*!
 @property chamferProfile
 @abstract Describes the profile used to when "chamferRadius" is not nil. When "chamferProfile" is nil we fallback on a path representing a quadrant.
 @discussion The profile should be a 2D curve beginning at (0,1) and ending at (1,0). The "flatness" property is also used to flatten this path. The default value is nil.
 */
@property(nonatomic, copy, nullable) UIBezierPath *chamferProfile;

/*!
 @property flatness
 @abstract Specifies the accuracy (or smoothness) with which fonts are rendered.
 @discussion Smaller numbers give smoother curves at the expense of more computation and heavier geometries in terms of vertices. The default value is 1.0, which yields smooth curves.
 */
@property(nonatomic) CGFloat flatness API_AVAILABLE(macos(10.9));

@end


typedef NS_ENUM(NSInteger, SCNChamferMode) {
    SCNChamferModeBoth,
    SCNChamferModeFront,
    SCNChamferModeBack
} API_AVAILABLE(macos(10.9));

/*!
 @class SCNShape
 @abstract SCNShape represents a 2D shape (cubic Bezier spline) than can be extruded.
 */
SCN_EXPORT API_AVAILABLE(macos(10.9))
@interface SCNShape : SCNGeometry

/*!
 @method shapeWithPath:extrusionDepth:
 @abstract Creates and returns a 3D representation of the given shape with the given extrusion depth.
 @param path The cubic Bezier spline to extrude.
 @param extrusionDepth The extrusion depth.
 */
+ (instancetype)shapeWithPath:(nullable UIBezierPath *)path extrusionDepth:(CGFloat)extrusionDepth;

/*!
 @property path
 @abstract The path defining the shape to be rendered.
 @discussion The path defines the outline of the shape. The path is filled using the even-odd rule. If the path is self-intersecting, the behavior is undefined.
 */
@property(nonatomic, copy, nullable) UIBezierPath *path;

/*!
 @property extrusionDepth
 @abstract The extrusion depth. Animatable.
 @discussion If the value is 0, we get a mono-sided, 2D version of the shape.
 */
@property(nonatomic) CGFloat extrusionDepth;

/*!
 @property chamferMode
 @abstract The sides of the text that are chamfered.
 @discussion The default value is SCNChamferModeBoth.
 */
@property(nonatomic) SCNChamferMode chamferMode;

/*!
 @property chamferRadius
 @abstract The chamfer radius. Animatable.
 @discussion Values are clamped to the range [0, extrusionDepth / 2]. The default value is 0.
 */
@property(nonatomic) CGFloat chamferRadius;

/*!
 @property chamferProfile
 @abstract Describes the profile used to when "chamferRadius" is not nil. When "chamferProfile" is nil we fallback on a path representing a quadrant.
 @discussion The profile should be a 2D curve beginning at (0,1) and ending at (1,0). The "flatness" property is also used to flatten this path. The default value is nil.
 */
@property(nonatomic, copy, nullable) UIBezierPath *chamferProfile;

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNReferenceNode.h
//
//  SCNReferenceNode.h
//  SceneKit
//
//  Copyright © 2015-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SCNNode.h>

NS_ASSUME_NONNULL_BEGIN

/*! @enum SCNReferenceLoadingPolicy
 @abstract Controls whenever to load the reference node.
 @discussion When the load policy is set to SCNReferenceLoadingPolicyImmediately, the reference is loaded immediately when the SCNReferenceNode is unarchived.
 When the load policy is set to SCNReferenceLoadingPolicyOnDemand the reference is never loaded until "load" is explicitly invoked.
 */
typedef NS_ENUM(NSInteger, SCNReferenceLoadingPolicy) {
    SCNReferenceLoadingPolicyImmediate = 0,
    SCNReferenceLoadingPolicyOnDemand  = 1
} API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @class SCNReferenceNode
 @abstract Node that references an external file.
 */
SCN_EXPORT API_AVAILABLE(macos(10.11), ios(9.0))
@interface SCNReferenceNode : SCNNode

/*!
 @method initWithURL:
 @abstract Creates a reference node with a url.
 */
- (nullable instancetype)initWithURL:(NSURL *)referenceURL NS_DESIGNATED_INITIALIZER;

/*!
 @method initWithCoder:
 @abstract Support coding and decoding via NSKeyedArchiver.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/*!
 @method referenceNodeWithURL:
 @abstract Creates a reference node with a url.
 */
+ (nullable instancetype)referenceNodeWithURL:(NSURL *)referenceURL;

/*!
 @property referenceURL
 @abstract Specifies the url to resolve.
 */
@property(copy, nonatomic) NSURL *referenceURL;

/*!
 @property loadingPolicy
 @abstract Specifies when to load the reference. see SCNReferenceLoadingPolicy above. Defaults to SCNReferenceLoadingPolicyImmediately.
 */
@property(nonatomic) SCNReferenceLoadingPolicy loadingPolicy;

/*!
 @method load
 @abstract Force the reference to be loaded if it hasn't been loaded already. The resolved nodes will be added
 as child nodes of the receiver.
 */
- (void)load;

/*!
 @method unload
 @abstract Remove the child nodes and mark as unloaded.
 */
- (void)unload;

/*!
 @property loaded
 @abstract Indicates whether the referenced URL has been loaded.
 */
@property(readonly, getter=isLoaded) BOOL loaded;

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNCamera.h
//
//  SCNCamera.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNTechnique.h>

typedef NS_ENUM(NSInteger, SCNCameraProjectionDirection) {
    SCNCameraProjectionDirectionVertical   = 0,
    SCNCameraProjectionDirectionHorizontal = 1,
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

NS_ASSUME_NONNULL_BEGIN

@class SCNMaterialProperty;

/*!
 @class SCNCamera
 @abstract SCNCamera represents a camera that can be attached to a SCNNode. 
 @discussion A node with a camera can be used as a point of view to visualize a 3D scene.
 */

SCN_EXPORT
@interface SCNCamera : NSObject <SCNAnimatable, SCNTechniqueSupport, NSCopying, NSSecureCoding>

/*! 
 @method camera
 @abstract Creates and returns a camera instance.
 */
+ (instancetype)camera;

/*! 
 @property name
 @abstract Determines the name of the receiver.
 */
@property(nonatomic, copy, nullable) NSString *name;

/*!
 @property fieldOfView
 @abstract Determines the receiver's field of view (in degree). Defaults to 60°. Animatable.
 @discussion The fieldOfView is automatically updated when the sensorHeight or focalLength are set. Setting the fieldOfView will update the focalLength according to the new fieldOfView and the current sensorHeight.
 */
@property(nonatomic) CGFloat fieldOfView API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property projectionDirection
 @abstract Determines whether the fieldOfView (or orthographicScale) is vertical or horizontal. Defaults to vertical.
 */
@property(nonatomic) SCNCameraProjectionDirection projectionDirection API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property focalLength
 @abstract Determines the receiver's focal length in millimeter. Defaults to 50mm. Animatable.
 @discussion The focalLength is automatically updated when the sensorHeight or fieldOfView are set. Setting the focalLength will update the fieldOfView according to the new focalLength and the current sensorHeight.
 */
@property(nonatomic) CGFloat focalLength API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property sensorHeight
 @abstract Determines the vertical size of the sensor in millimeter. Defaults to 24mm. Animatable.
 @discussion Setting the sensorHeight will automatically update the fieldOfView according to the new sensorHeight and the current focalLength.
 */
@property(nonatomic) CGFloat sensorHeight API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*! 
 @property zNear
 @abstract Determines the receiver's near value. Animatable.
 @discussion The near value determines the minimal distance between the camera and a visible surface. If a surface is closer to the camera than this minimal distance, then the surface is clipped. The near value must be different than zero. Defaults to 1.
 */
@property(nonatomic) double zNear;

/*! 
 @property zFar
 @abstract Determines the receiver's far value. Animatable.
 @discussion The far value determines the maximal distance between the camera and a visible surface. If a surface is further from the camera than this maximal distance, then the surface is clipped. Defaults to 100.
 */
@property(nonatomic) double zFar;

/*!
 @property automaticallyAdjustsZRange
 @abstract Determines whether the receiver automatically adjusts the zFar value. Defaults to NO.
 @discussion When set to YES, the near and far planes are automatically set to fit the bounding box of the entire scene at render time. 
 */
@property(nonatomic) BOOL automaticallyAdjustsZRange API_AVAILABLE(macos(10.9));

/*! 
 @property usesOrthographicProjection
 @abstract Determines whether the receiver uses an orthographic projection or not. Defaults to NO.
 */
@property(nonatomic) BOOL usesOrthographicProjection;

/*!
 @property orthographicScale
 @abstract Determines the receiver's orthographic scale value. Animatable. Defaults to 1.
 @discussion This setting determines the size of the camera's visible area. This is only enabled when usesOrthographicProjection is set to YES.
 */
@property(nonatomic) double orthographicScale API_AVAILABLE(macos(10.9));

/*!
 @property projectionTransform
 @abstract Determines the projection transform used by the camera to project the world onscreen. 
 */
@property(nonatomic) SCNMatrix4 projectionTransform;

// MARK: Depth of Field

/*!
 @property wantsDepthOfField
 @abstract Determines if the receiver has depth of field. Defaults to NO.
 */
@property(nonatomic) BOOL wantsDepthOfField API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property focusDistance
 @abstract Determines the receiver's focus distance. Animatable.
 @discussion Defaults to 2.5
 */
@property(nonatomic) CGFloat focusDistance API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property focalBlurSampleCount
 @abstract Determines the receiver's sample count for depth of field effect.
 @discussion Defaults to 25.
 */
@property(nonatomic) NSInteger focalBlurSampleCount API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property fStop
 @abstract Determines the receiver's fstop. Animatable.
 @discussion Defaults to 5.6.
 */
@property(nonatomic) CGFloat fStop API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property apertureBladeCount
 @abstract Determines the receiver's blade count of the aperture.
 @discussion Defaults to 6.
 */
@property(nonatomic) NSInteger apertureBladeCount API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property motionBlurIntensity
 @abstract Determines the intensity of the motion blur. Animatable. Defaults to 0.
 @discussion An intensity of zero means no motion blur. The intensity should not exceeed 1.
 */
@property(nonatomic) CGFloat motionBlurIntensity API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

// MARK: Screen Space Ambient Occlusion

/*!
 @property screenSpaceAmbientOcclusionIntensity
 @abstract Determines the intensity of the screen space ambient occlusion. Animatable.
 @discussion defaults to 0.
 */
@property(nonatomic) CGFloat screenSpaceAmbientOcclusionIntensity API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property screenSpaceAmbientOcclusionRadius
 @abstract Determines the screen space ambient occlusion radius in scene unit. Animatable.
 @discussion defaults to 5.
 */
@property(nonatomic) CGFloat screenSpaceAmbientOcclusionRadius API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property screenSpaceAmbientOcclusionBias
 @abstract Determines self occlusion bias in scene unit.
 @discussion defaults to 0.03.
 */
@property(nonatomic) CGFloat screenSpaceAmbientOcclusionBias API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property screenSpaceAmbientOcclusionDepthThreshold
 @abstract Determines the depth blur threshold in scene unit.
 @discussion defaults to 0.2.
 */
@property(nonatomic) CGFloat screenSpaceAmbientOcclusionDepthThreshold API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property screenSpaceAmbientOcclusionNormalThreshold
 @abstract Determines the normal blur threshold.
 @discussion defaults to 0.3.
 */
@property(nonatomic) CGFloat screenSpaceAmbientOcclusionNormalThreshold API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

// MARK: High Dynamic Range

/*!
 @property wantsHDR
 @abstract Determines if the receiver has a high dynamic range. Defaults to NO.
 */
@property(nonatomic) BOOL wantsHDR API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property exposureOffset
 @abstract Determines the logarithimc exposure biasing, in EV. Defaults to 0.
 */
@property(nonatomic) CGFloat exposureOffset API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property averageGray
 @abstract Determines the average gray level desired in the final image. Defaults to 0.18.
 */
@property(nonatomic) CGFloat averageGray API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property whitePoint
 @abstract Determines the smallest luminance level that will be mapped to white in the final image. Defaults to 1.
 */
@property(nonatomic) CGFloat whitePoint API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property wantsExposureAdaptation
 @abstract Determines if the receiver should simulate an eye and continuously adjust to luminance. Defaults to YES.
 */
@property(nonatomic) BOOL wantsExposureAdaptation API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property exposureAdaptationBrighteningSpeedFactor
 @abstract Determines the exposure adaptation speed when going from bright areas to dark areas. Defaults to 0.4.
 */
@property(nonatomic) CGFloat exposureAdaptationBrighteningSpeedFactor API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property exposureAdaptationBrighteningSpeedFactor
 @abstract Determines the exposure adaptation speed when going from dark areas to bright areas. Defaults to 0.6.
 */
@property(nonatomic) CGFloat exposureAdaptationDarkeningSpeedFactor API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property minimumExposure
 @abstract Determines the minimum exposure offset of the adaptation, in EV. Defaults to -15.
 */
@property(nonatomic) CGFloat minimumExposure API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property maximumExposure
 @abstract Determines the maximum exposure offset of the adaptation, in EV. Defaults to -15.
 */
@property(nonatomic) CGFloat maximumExposure API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property bloomThreshold
 @abstract Determines the luminance threshold for the bloom effect. Animatable. Defaults to 1.
 */
@property(nonatomic) CGFloat bloomThreshold API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property bloomIntensity
 @abstract Determines the intensity of the bloom effect. Animatable. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat bloomIntensity API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property bloomBlurRadius
 @abstract Determines the radius of the bloom effect in points. Animatable. Defaults to 4.
 */
@property(nonatomic) CGFloat bloomBlurRadius API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property vignettingPower
 @abstract Controls the shape of the vignetting effect. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat vignettingPower API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property vignettingIntensity
 @abstract Controls the intensity of the vignetting effect. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat vignettingIntensity API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property colorFringeStrength
 @abstract Controls the strength of the color shift effect. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat colorFringeStrength API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property colorFringeIntensity
 @abstract Controls the intensity of the color shift effect. Defaults to 1.
 */
@property(nonatomic) CGFloat colorFringeIntensity API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property saturation
 @abstract Controls the overall saturation of the scene. Defaults to 1 (no effect).
 */
@property(nonatomic) CGFloat saturation API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property contrast
 @abstract Controls the overall contrast of the scene. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat contrast API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property colorGrading
 @abstract Specifies a lookup texture to apply color grading. The contents must a 2D image representing `n` slices of a unit color cube texture, arranged in an horizontal row of `n` images. For instance, a color cube of dimension 16x16x16 should be provided as an image of size 256x16.
 */
@property(nonatomic, readonly) SCNMaterialProperty *colorGrading API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property categoryBitMask
 @abstract Determines the node categories that are visible from the receiver. Defaults to all bits set.
 */
@property(nonatomic) NSUInteger categoryBitMask API_AVAILABLE(macos(10.10));

// MARK: - Deprecated APIs

/*!
 @property focalBlurRadius
 @abstract Determines the receiver's focal radius. Animatable.
 @discussion Determines the maximum amount of blur for objects out of focus. Defaults to 0.
 */
@property(nonatomic) CGFloat focalBlurRadius API_DEPRECATED("Use fStop instead", macos(10.8, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @property xFov
 @abstract Determines the receiver's field of view on the X axis (in degree). Animatable.
 @discussion When both xFov and yFov are null an yFov of 60° is used. When both are set, the one that best fits the renderer's aspect ratio is used. When only one is set, it is used. Defaults to 0.
 */
@property(nonatomic) double xFov API_DEPRECATED("Use -[SCNCamera fieldOfView] or -[SCNCamera focalLength] instead", macos(10.8, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @property yFov
 @abstract Determines the receiver's field of view on the Y axis (in degree). Animatable.
 @discussion When both xFov and yFov are null an yFov of 60° is used. When both are set, the one that best fits the renderer's aspect ratio is used. When only one is set, it is used. Defaults to 0.
 */
@property(nonatomic) double yFov API_DEPRECATED("Use -[SCNCamera fieldOfView] or -[SCNCamera focalLength] instead", macos(10.8, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @property aperture
 @abstract Determines the receiver's aperture. Animatable.
 @discussion Defaults to 1/8.0.
 */
@property(nonatomic) CGFloat aperture API_DEPRECATED("Use -[SCNCamera fStop] instead with fStop = sensorHeight / aperture.", macos(10.8, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @property focalSize
 @abstract Determines the receiver's focal size. Animatable.
 @discussion Determines the size of the area around focalDistance where the objects are in focus. Defaults to 0.
 */
@property(nonatomic) CGFloat focalSize API_DEPRECATED_WITH_REPLACEMENT("-focusDistance", macos(10.9, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @property focalDistance
 @abstract Determines the receiver's focal distance. Animatable.
 @discussion When non zero, the focal distance determines how the camera focuses the objects in the 3d scene. Defaults to 10.0 prior to macOS 10.13, iOS 11, tvOS 11 and watchOS 4. Defaults to 2.5 otherwise.
 */
@property(nonatomic) CGFloat focalDistance API_DEPRECATED_WITH_REPLACEMENT("-focusDistance", macos(10.9, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNPhysicsContact.h
//
//  SCNPhysicsContact.h
//  SceneKit
//
//  Copyright © 2014-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;

/*!
 @class SCNPhysicsContact
 @abstract SCNPhysicsContact contains information about a physics contact.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsContact : NSObject

//The two nodes in contact
@property(nonatomic, readonly) SCNNode *nodeA;
@property(nonatomic, readonly) SCNNode *nodeB;

//The contact point, impulse and distance in world space coordinates.
@property(nonatomic, readonly) SCNVector3 contactPoint;
@property(nonatomic, readonly) SCNVector3 contactNormal;
@property(nonatomic, readonly) CGFloat    collisionImpulse; // the collision impulse on nodeA
@property(nonatomic, readonly) CGFloat    penetrationDistance;
@property(nonatomic, readonly) CGFloat    sweepTestFraction API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)); // Value between 0 and 1 giving the relative position of the physic shape when performing a convex sweep test.

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNMaterialProperty.h
//
//  SCNMaterialProperty.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNAnimation.h>

NS_ASSUME_NONNULL_BEGIN

/*! @enum SCNFilterMode
    @abstract Filtering modes
*/
typedef NS_ENUM(NSInteger, SCNFilterMode) {
    SCNFilterModeNone    = 0,
    SCNFilterModeNearest = 1,
    SCNFilterModeLinear  = 2
} API_AVAILABLE(macos(10.9));

/*! @enum SCNWrapeMode
 @abstract Wrap modes
 */
typedef NS_ENUM(NSInteger, SCNWrapMode) {
    SCNWrapModeClamp         = 1,
    SCNWrapModeRepeat        = 2,
    SCNWrapModeClampToBorder = 3,
    SCNWrapModeMirror        = 4
} API_AVAILABLE(macos(10.9));

/*! @class SCNMaterialProperty
    @abstract The contents of a SCNMaterial slot
    @discussion This can be used to specify the various properties of SCNMaterial slots such as diffuse, ambient, etc.
*/

SCN_EXPORT
@interface SCNMaterialProperty : NSObject <SCNAnimatable, NSSecureCoding>

/*!
 @method materialPropertyWithContents:
 @abstract Creates and initialize a property instance with the specified contents.
 */
+ (instancetype)materialPropertyWithContents:(id)contents API_AVAILABLE(macos(10.9));

/*! 
 @property contents
 @abstract Specifies the receiver's contents. This can be a color (NSColor, UIColor, CGColorRef), an image (NSImage, UIImage, CGImageRef), a layer (CALayer), a path (NSString or NSURL), a SpriteKit scene (SKScene), a texture (SKTexture, id<MTLTexture> or GLKTextureInfo), or a floating value between 0 and 1 (NSNumber) for metalness and roughness properties. AVCaptureDevice is supported on iOS 11 and AVPlayer is supported on macOS 10.13, iOS 11 and tvOS 11. Animatable when set to a color.
 @discussion Setting the contents to an instance of SKTexture will automatically update the wrapS, wrapT, contentsTransform, minification, magnification and mip filters according to the SKTexture settings.
             When a cube map is expected (e.g. SCNMaterial.reflective, SCNScene.background, SCNScene.lightingEnvironment) you can use
               1. A horizontal strip image                          where `6 * image.height ==     image.width`
               2. A vertical strip image                            where `    image.height == 6 * image.width`
               3. A spherical projection image (latitude/longitude) where `2 * image.height ==     image.width`
               4. A NSArray of 6 images. This array must contain images of the exact same dimensions, in the following order, in a left-handed coordinate system: +X, -X, +Y, -Y, +Z, -Z (or Right, Left, Top, Bottom, Front, Back).
 */
@property(nonatomic, retain, nullable) id contents;

/*!
 @property intensity
 @abstract Determines the receiver's intensity. This intensity is used to modulate the properties in several ways.
 It dims the diffuse, specular and emission properties, it varies the bumpiness of the normal property and the
 filter property is blended with white. Default value is 1.0. Animatable.
 */
@property(nonatomic) CGFloat intensity API_AVAILABLE(macos(10.9));

/*! 
 @property minificationFilter
 @abstract Specifies the filter type to use when rendering the contents (specified in the `contents' property).
 @discussion The minification filter is used when to reduce the size of image data. See above the list of available modes. Defaults to SCNFilterModeLinear.
 */
@property(nonatomic) SCNFilterMode minificationFilter;

/*! 
 @property magnificationFilter
 @abstract Specifies the filter type to use when rendering the the contents (specified in the `contents' property).
 @discussion The magnification filter is used when to increase the size of image data. See above the list of available modes. Defaults to SCNFilterModeLinear.
 */
@property(nonatomic) SCNFilterMode magnificationFilter;

/*! 
 @property mipFilter
 @abstract Specifies the mipmap filter to use during minification.
 @discussion Defaults to SCNFilterModeNone on macOS 10.11 or earlier and iOS 9 or earlier, SCNFilterModeNearest starting in macOS 10.12 and iOS 10.
 */
@property(nonatomic) SCNFilterMode mipFilter;

/*! 
 @property contentsTransform
 @abstract Determines the receiver's contents transform. Animatable.
 */
@property(nonatomic) SCNMatrix4 contentsTransform;

/*! 
 @property wrapS
 @abstract Determines the receiver's wrap mode for the s texture coordinate. Defaults to SCNWrapModeClamp.
 */
@property(nonatomic) SCNWrapMode wrapS;

/*! 
 @property wrapT
 @abstract Determines the receiver's wrap mode for the t texture coordinate. Defaults to SCNWrapModeClamp.
 */
@property(nonatomic) SCNWrapMode wrapT;

/*! 
 @property borderColor
 @abstract Determines the receiver's border color (CGColorRef or UIColor). Animatable.
 @discussion The border color is ignored on iOS and is always considered as clear color (0,0,0,0) when the texture has an alpha channel and opaque back (0,0,0,1) otherwise.
 */
@property(nonatomic, retain, nullable) id borderColor API_DEPRECATED("Deprecated", macos(10.8, 10.12), ios(8.0, 10.0)) API_UNAVAILABLE(watchos, tvos);

/*! 
 @property mappingChannel
 @abstract Determines the receiver's mapping channel. Defaults to 0.
 @discussion Geometries potentially have multiple sources of texture coordinates. Every source has a unique mapping channel index. The mapping channel allows to select which source of texture coordinates is used to map the content of the receiver. 
 */
@property(nonatomic) NSInteger mappingChannel;      

/*!
 @property textureComponents
 @abstract Specifies the texture components to sample in the shader. Defaults to SCNColorMaskRed for displacement property, and to SCNColorMaskAll for other properties.
 @discussion Use this property to when using a texture that combine multiple informations in the different texture components. For example if you pack the roughness in red and metalness in blue etc... You can specify what component to use from the texture for this given material property. This property is only supported by Metal renderers.
 */
@property(nonatomic) SCNColorMask textureComponents API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));


/*!
 @property maxAnisotropy
 @abstract Specifies the receiver's max anisotropy. Defaults to 1.0.
 @discussion Anisotropic filtering reduces blur and preserves detail at extreme viewing angles.
 */
@property(nonatomic) CGFloat maxAnisotropy API_AVAILABLE(macos(10.9));

@end
    
NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNPhysicsShape.h
//
//  SCNPhysicsShape.h
//  SceneKit
//
//  Copyright © 2014-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNGeometry;
@class SCNNode;

typedef NSString * SCNPhysicsShapeOption NS_STRING_ENUM;
SCN_EXPORT SCNPhysicsShapeOption const SCNPhysicsShapeTypeKey               API_AVAILABLE(macos(10.10));                        // Type of the physics shape. Default is SCNPhysicsShapeTypeConvexHull. See below for the list of shape types.
SCN_EXPORT SCNPhysicsShapeOption const SCNPhysicsShapeKeepAsCompoundKey     API_AVAILABLE(macos(10.10));                        // A boolean to decide if a hierarchy is kept as a compound of shapes or flattened as one single volume. Default is true.
SCN_EXPORT SCNPhysicsShapeOption const SCNPhysicsShapeScaleKey              API_AVAILABLE(macos(10.10));                        // Local scaling of the physics shape (as an SCNVector3 wrapped in a NSValue)
SCN_EXPORT SCNPhysicsShapeOption const SCNPhysicsShapeOptionCollisionMargin API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)); // Collision margin of the physics shape (as an NSNumber)

#define SCNPhysicsShapeOptionType           SCNPhysicsShapeTypeKey
#define SCNPhysicsShapeOptionKeepAsCompound SCNPhysicsShapeKeepAsCompoundKey
#define SCNPhysicsShapeOptionScale          SCNPhysicsShapeScaleKey

// Values for SCNPhysicsShapeOptionType
typedef NSString * SCNPhysicsShapeType NS_STRING_ENUM;
SCN_EXPORT SCNPhysicsShapeType const SCNPhysicsShapeTypeBoundingBox API_AVAILABLE(macos(10.10));
SCN_EXPORT SCNPhysicsShapeType const SCNPhysicsShapeTypeConvexHull API_AVAILABLE(macos(10.10));
SCN_EXPORT SCNPhysicsShapeType const SCNPhysicsShapeTypeConcavePolyhedron API_AVAILABLE(macos(10.10));

/*!
 @class SCNPhysicsShape
 @abstract SCNPhysicsShape represents the shape of a physics body.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsShape : NSObject <NSCopying, NSSecureCoding>

//Creates an instance of a physics shape based on a geometry. see above for the possible options.
+ (instancetype)shapeWithGeometry:(SCNGeometry *)geometry options:(nullable NSDictionary<SCNPhysicsShapeOption, id> *)options;

//Creates an instance of a physics shape based on a node hierachy. The hierarchy must contain geometries at some point to create a valid shape. see above for the possible options.
+ (instancetype)shapeWithNode:(SCNNode *)node options:(nullable NSDictionary<SCNPhysicsShapeOption, id> *)options;

//Creates an instance of a physics shape based on several sub shapes, associated with transforms. The transforms are to be passed as an array of NSValue wrapping SCNMatrix4
+ (instancetype)shapeWithShapes:(NSArray<SCNPhysicsShape *> *)shapes transforms:(nullable NSArray<NSValue *> *)transforms;

// Returns the options requested at init time
@property(readonly, nonatomic, nullable) NSDictionary<SCNPhysicsShapeOption, id> *options API_AVAILABLE(macos(10.11), ios(9.0));

// Returns the object from which this physics shape was created. It can be an SCNGeometry*, an SCNNode* or in NSArray* of subshapes.
@property(readonly, nonatomic) id sourceObject API_AVAILABLE(macos(10.11), ios(9.0));

// If the physics shape was created from an array of sub shapes, transforms contains the associated transforms as SCNMatrix4 wrapped in NSValue.
@property(readonly, nonatomic, nullable) NSArray<NSValue *> *transforms API_AVAILABLE(macos(10.11), ios(9.0));

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNHitTest.h
//
//  SCNHitTest.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;

/*! @enum SCNHitTestSearchMode
 @abstract hit test modes
 */
typedef NS_ENUM(NSInteger, SCNHitTestSearchMode) {
    SCNHitTestSearchModeClosest = 0, // The closest object found.
    SCNHitTestSearchModeAll     = 1, // All found objects sorted from nearest to farthest.
    SCNHitTestSearchModeAny     = 2  // The first object found. This object is not necessarily the nearest.
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*! @group Hit-test options */

typedef NSString * SCNHitTestOption NS_STRING_ENUM;
SCN_EXPORT SCNHitTestOption const SCNHitTestClipToZRangeKey;                                                                        // If set to YES ignores the objects clipped by the zNear/zFar range of the current point of view. Defaults to YES.
SCN_EXPORT SCNHitTestOption const SCNHitTestBackFaceCullingKey;                                                                     // If set to YES ignores the faces not facing to the camera. Defaults to YES.
SCN_EXPORT SCNHitTestOption const SCNHitTestBoundingBoxOnlyKey;                                                                     // If set to YES only tests the bounding boxes of the 3D objects. Defaults to NO.
SCN_EXPORT SCNHitTestOption const SCNHitTestIgnoreChildNodesKey;                                                                    // Determines whether the child nodes are ignored. Defaults to NO.
SCN_EXPORT SCNHitTestOption const SCNHitTestRootNodeKey;                                                                            // Specifies the root node to use for the hit test. Defaults to the root node of the scene.
SCN_EXPORT SCNHitTestOption const SCNHitTestIgnoreHiddenNodesKey  API_AVAILABLE(macos(10.9));                                       // Determines whether hidden nodes should be ignored. Defaults to YES.
SCN_EXPORT SCNHitTestOption const SCNHitTestOptionCategoryBitMask API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));               // Determines the node categories to test. Defaults to all bits set.
SCN_EXPORT SCNHitTestOption const SCNHitTestOptionSearchMode      API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)); // Determines whether the search should be exhaustive. Defaults to SCNHitTestSearchModeClosest.

SCN_EXPORT SCNHitTestOption const SCNHitTestFirstFoundOnlyKey;                                                                      // Deprecated, use SCNHitTestSearchModeAny for the SCNHitTestOptionSearchMode option instead
SCN_EXPORT SCNHitTestOption const SCNHitTestSortResultsKey;                                                                         // Deprecated, use SCNHitTestSearchModeAll for the SCNHitTestOptionSearchMode option instead

#define SCNHitTestOptionFirstFoundOnly    SCNHitTestFirstFoundOnlyKey
#define SCNHitTestOptionSortResults       SCNHitTestSortResultsKey
#define SCNHitTestOptionClipToZRange      SCNHitTestClipToZRangeKey
#define SCNHitTestOptionBackFaceCulling   SCNHitTestBackFaceCullingKey
#define SCNHitTestOptionBoundingBoxOnly   SCNHitTestBoundingBoxOnlyKey
#define SCNHitTestOptionIgnoreChildNodes  SCNHitTestIgnoreChildNodesKey
#define SCNHitTestOptionRootNode          SCNHitTestRootNodeKey
#define SCNHitTestOptionIgnoreHiddenNodes SCNHitTestIgnoreHiddenNodesKey

/*! @class SCNHitTestResult
 @abstract Results returned by the hit-test methods.
 */

SCN_EXPORT
@interface SCNHitTestResult : NSObject

/*! The hit node. */
@property(nonatomic, readonly) SCNNode *node;

/*! Index of the hit geometry element. */
@property(nonatomic, readonly) NSInteger geometryIndex;

/*! Index of the hit primitive of the geometry element. */
@property(nonatomic, readonly) NSInteger faceIndex;

/*! Intersection point in the node's local coordinate system. */
@property(nonatomic, readonly) SCNVector3 localCoordinates;

/*! Intersection point in the world coordinate system. */
@property(nonatomic, readonly) SCNVector3 worldCoordinates;

/*! Intersection normal in the node's local coordinate system. */
@property(nonatomic, readonly) SCNVector3 localNormal;

/*! Intersection normal in the world coordinate system. */
@property(nonatomic, readonly) SCNVector3 worldNormal;

/*! World transform of the hit node. */
@property(nonatomic, readonly) SCNMatrix4 modelTransform;

/*! The hit bone. Only available if the node hit has a SCNSkinner attached. */
@property(nonatomic, readonly, nullable) SCNNode *boneNode API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @method textureCoordinatesWithMappingChannel:
 @abstract Returns the texture coordinates at the point of intersection, for a given mapping channel.
 @param channel The texture coordinates source index of the geometry to use. The channel must exists on the geometry otherwise {0,0} will be returned.
 */
- (CGPoint)textureCoordinatesWithMappingChannel:(NSInteger)channel;

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SceneKitTypes.h
//
//  SceneKitTypes.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitAvailability.h>
#import <CoreGraphics/CoreGraphics.h>
#import <simd/simd.h>

#import <QuartzCore/QuartzCore.h>
#import <GLKit/GLKMathTypes.h>

/*! @header SceneKitTypes
 @abstract Various types and utility functions used throughout SceneKit
 */

#define SCN_ENABLE_METAL (!TARGET_OS_SIMULATOR)

#if SCN_ENABLE_METAL
#import <Metal/Metal.h>
#endif


// Color
#define SCNColor UIColor

/*! @enum SCNActionTimingMode
 @abstract The modes that an action can use to adjust the apparent timing of the action.
 */
typedef NS_ENUM(NSInteger, SCNActionTimingMode) {
    SCNActionTimingModeLinear,
    SCNActionTimingModeEaseIn,
    SCNActionTimingModeEaseOut,
    SCNActionTimingModeEaseInEaseOut
} API_AVAILABLE(macos(10.10), ios(8.0));

/*! @enum SCNColorComponent
 @abstract Color components
 */
typedef NS_OPTIONS(NSInteger, SCNColorMask) {
    SCNColorMaskNone   = 0,
    SCNColorMaskRed    = 0x1 << 3,
    SCNColorMaskGreen  = 0x1 << 2,
    SCNColorMaskBlue   = 0x1 << 1,
    SCNColorMaskAlpha  = 0x1 << 0,
    SCNColorMaskAll    = 0xf
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

#pragma mark - Vectors

typedef struct SCNVector3 {
    float x, y, z;
} SCNVector3;

typedef struct SCNVector4 {
    float x, y, z, w;
} SCNVector4;

/* The null vector: [0 0 0]. */
SCN_EXPORT const SCNVector3 SCNVector3Zero API_AVAILABLE(macos(10.10));

/* The null vector: [0 0 0 0]. */
SCN_EXPORT const SCNVector4 SCNVector4Zero API_AVAILABLE(macos(10.10));

/* Returns true if 'a' is exactly equal to 'b'. */
SCN_EXPORT bool SCNVector3EqualToVector3 (SCNVector3 a, SCNVector3 b);

/* Returns true if 'a' is exactly equal to 'b'. */
SCN_EXPORT bool SCNVector4EqualToVector4 (SCNVector4 a, SCNVector4 b);

/* Returns an initialized SCNVector3 */
NS_INLINE SCNVector3 SCNVector3Make(float x, float y, float z) {
    return (SCNVector3){x, y, z};
}

/* Returns an initialized SCNVector4 */
NS_INLINE SCNVector4 SCNVector4Make(float x, float y, float z, float w) {
    return (SCNVector4){x, y, z, w};
}


#pragma mark - Quaternions

typedef SCNVector4 SCNQuaternion;


#pragma mark - Matrices

typedef struct SCNMatrix4 {
    float m11, m12, m13, m14;
    float m21, m22, m23, m24;
    float m31, m32, m33, m34;
    float m41, m42, m43, m44;
} SCNMatrix4;

/* The identity matrix: [1 0 0 0; 0 1 0 0; 0 0 1 0; 0 0 0 1]. */
SCN_EXPORT const SCNMatrix4 SCNMatrix4Identity API_AVAILABLE(macos(10.10));

/* Returns true if 'm' is the identity matrix. */
SCN_EXPORT bool SCNMatrix4IsIdentity(SCNMatrix4 m) API_AVAILABLE(macos(10.10));

/* Returns true if 'a' is exactly equal to 'b'. */
SCN_EXPORT bool SCNMatrix4EqualToMatrix4(SCNMatrix4 a, SCNMatrix4 b) API_AVAILABLE(macos(10.10));

/* Returns a transform that translates by '(tx, ty, tz)':
 * m' =  [1 0 0 0; 0 1 0 0; 0 0 1 0; tx ty tz 1]. */
NS_INLINE SCNMatrix4 SCNMatrix4MakeTranslation(float tx, float ty, float tz) {
    return (SCNMatrix4){
        .m11 = 1.f, .m12 = 0.f, .m13 = 0.f, .m14 = 0.f,
        .m21 = 0.f, .m22 = 1.f, .m23 = 0.f, .m24 = 0.f,
        .m31 = 0.f, .m32 = 0.f, .m33 = 1.f, .m34 = 0.f,
        .m41 =  tx, .m42 =  ty, .m43 =  tz, .m44 = 1.f
    };
}

/* Returns a transform that scales by '(sx, sy, sz)':
 * m' = [sx 0 0 0; 0 sy 0 0; 0 0 sz 0; 0 0 0 1]. */
NS_INLINE SCNMatrix4 SCNMatrix4MakeScale(float sx, float sy, float sz) {
    return (SCNMatrix4){
        .m11 =  sx, .m12 = 0.f, .m13 = 0.f, .m14 = 0.f,
        .m21 = 0.f, .m22 =  sy, .m23 = 0.f, .m24 = 0.f,
        .m31 = 0.f, .m32 = 0.f, .m33 =  sz, .m34 = 0.f,
        .m41 = 0.f, .m42 = 0.f, .m43 = 0.f, .m44 = 1.f
    };
}

/* Returns a matrix that rotates by 'angle' radians about the vector '(x, y, z)'. */
SCN_EXPORT SCNMatrix4 SCNMatrix4MakeRotation(float angle, float x, float y, float z) API_AVAILABLE(macos(10.10));

/* Translate 'm' by '(tx, ty, tz)' and return the result:
 * m' = translate(tx, ty, tz) * m. */
NS_INLINE SCNMatrix4 SCNMatrix4Translate(SCNMatrix4 m, float tx, float ty, float tz) {
    m.m41 += tx;
    m.m42 += ty;
    m.m43 += tz;
    return m;
}

/* Scale 'm' by '(sx, sy, sz)' and return the result:
 * m' = scale(sx, sy, sz) * m. */
SCN_EXPORT SCNMatrix4 SCNMatrix4Scale(SCNMatrix4 m, float sx, float sy, float sz) API_AVAILABLE(macos(10.10));

/* Rotate 'm' by 'angle' radians about the vector '(x, y, z)' and return the result:
 * m' = rotation(angle, x, y, z) * m. */
SCN_EXPORT SCNMatrix4 SCNMatrix4Rotate(SCNMatrix4 m, float angle, float x, float y, float z) API_AVAILABLE(macos(10.10));

/* Invert 'm' and return the result. */
SCN_EXPORT SCNMatrix4 SCNMatrix4Invert(SCNMatrix4 m) API_AVAILABLE(macos(10.10));

/* Concatenate 'b' to 'a' and return the result: m' = a * b. */
SCN_EXPORT SCNMatrix4 SCNMatrix4Mult(SCNMatrix4 a, SCNMatrix4 b) API_AVAILABLE(macos(10.10));


#pragma mark - GLKit Bridge

NS_INLINE SCNVector3 SCNVector3FromGLKVector3(GLKVector3 vector) {
    return (SCNVector3){vector.v[0], vector.v[1], vector.v[2]};
}

NS_INLINE GLKVector3 SCNVector3ToGLKVector3(SCNVector3 vector) {
    return *(GLKVector3 *)&vector;
}

NS_INLINE SCNVector4 SCNVector4FromGLKVector4(GLKVector4 vector) {
    return *(SCNVector4 *)&vector;
}

NS_INLINE GLKVector4 SCNVector4ToGLKVector4(SCNVector4 vector) {
    return *(GLKVector4 *)&vector;
}

SCN_EXPORT GLKMatrix4 SCNMatrix4ToGLKMatrix4(SCNMatrix4 mat) API_AVAILABLE(macos(10.10));
SCN_EXPORT SCNMatrix4 SCNMatrix4FromGLKMatrix4(GLKMatrix4 mat) API_AVAILABLE(macos(10.10));


#pragma mark - SIMD Bridge
    
NS_INLINE simd_float3 SCNVector3ToFloat3(SCNVector3 v) {
    return simd_make_float3(v.x, v.y, v.z);
}

NS_INLINE simd_float4 SCNVector4ToFloat4(SCNVector4 v) {
    return simd_make_float4(v.x, v.y, v.z, v.w);
}

NS_INLINE simd_float4x4 SCNMatrix4ToMat4(SCNMatrix4 m) {
    return (simd_float4x4){
        .columns[0] = simd_make_float4(m.m11, m.m12, m.m13, m.m14),
        .columns[1] = simd_make_float4(m.m21, m.m22, m.m23, m.m24),
        .columns[2] = simd_make_float4(m.m31, m.m32, m.m33, m.m34),
        .columns[3] = simd_make_float4(m.m41, m.m42, m.m43, m.m44)
    };
}

NS_INLINE SCNVector3 SCNVector3FromFloat3(simd_float3 v) {
    return (SCNVector3){v.x, v.y, v.z};
}

NS_INLINE SCNVector4 SCNVector4FromFloat4(simd_float4 v) {
    return (SCNVector4){v.x, v.y, v.z, v.w};
}

NS_INLINE SCNMatrix4 SCNMatrix4FromMat4(simd_float4x4 m) {
    return *(SCNMatrix4 *)&m;
}


#pragma mark - NSValue Additions
    
#ifdef __OBJC__
    
NS_ASSUME_NONNULL_BEGIN

/*! @category NSValue(SceneKitAdditions)
 @abstract Adds methods to wrap vectors in NSValue objects.
 */

SCN_EXPORT
@interface NSValue (SceneKitAdditions)

+ (NSValue *)valueWithSCNVector3:(SCNVector3)v;
+ (NSValue *)valueWithSCNVector4:(SCNVector4)v;
+ (NSValue *)valueWithSCNMatrix4:(SCNMatrix4)v API_AVAILABLE(macos(10.10));

@property(nonatomic, readonly) SCNVector3 SCNVector3Value;
@property(nonatomic, readonly) SCNVector4 SCNVector4Value;
@property(nonatomic, readonly) SCNMatrix4 SCNMatrix4Value API_AVAILABLE(macos(10.10));

@end


#pragma mark - Errors

//domain for errors from SceneKit API.
SCN_EXPORT NSString * const SCNErrorDomain;

// NSError codes in SCNErrorDomain.
enum {
	SCNProgramCompilationError = 1
};

NS_ASSUME_NONNULL_END
    
#endif /* __OBJC__ */
// ==========  SceneKit.framework/Headers/SCNRenderer.h
//
//  SCNRenderer.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SCNSceneRenderer.h>
#import <SceneKit/SCNTechnique.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage;
@protocol MTLDevice;
@protocol MTLCommandQueue;
@protocol MTLRenderCommandEncoder;
@class MTLRenderPassDescriptor;

/*! @class SCNRenderer
	@abstract SCNRenderer lets you use the SceneKit renderer in an OpenGL context or Metal render pass descriptor of your own.
 */
API_UNAVAILABLE(watchos)
SCN_EXPORT
@interface SCNRenderer : NSObject <SCNSceneRenderer, SCNTechniqueSupport>

/*! 
 @method rendererWithContext:options:
 @abstract Creates a new renderer object.
 @param context The context to render into.
 @param options An optional dictionary for future extensions.
 */
+ (instancetype)rendererWithContext:(nullable EAGLContext *)context options:(nullable NSDictionary *)options;

/*!
 @method rendererWithDevice:options:
 @abstract Creates a new renderer object that renders using Metal.
 @param device The metal device to use. Pass nil to let SceneKit choose a default device.
 @param options An optional dictionary for future extensions.
 */
+ (instancetype)rendererWithDevice:(nullable id <MTLDevice>)device options:(nullable NSDictionary *)options API_AVAILABLE(macos(10.11), ios(9.0));

/*! 
 @property scene
 @abstract Specifies the scene of the receiver
 */
@property(nonatomic, retain, nullable) SCNScene *scene;

/*!
 @method renderAtTime:viewport:commandBuffer:passDescriptor:
 @abstract updates and renders the receiver's scene at the specified time (system time) viewport, Metal command buffer and pass descriptor.
 @discussion Use this method to render using Metal.
 */
- (void)renderAtTime:(CFTimeInterval)time viewport:(CGRect)viewport commandBuffer:(id <MTLCommandBuffer>)commandBuffer passDescriptor:(MTLRenderPassDescriptor *)renderPassDescriptor API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method renderAtTime:
 @abstract updates and renders the receiver's scene at the specified time (system time).
 @discussion This method only work if the receiver was allocated with an OpenGL context. Use renderAtTime:withEncoder:pass:commandQueue: to render with Metal.
 */
- (void)renderAtTime:(CFTimeInterval)time API_AVAILABLE(macos(10.10));

/*!
 @method updateAtTime:
 @abstract updates the receiver's scene at the specified time (system time).
 */
- (void)updateAtTime:(CFTimeInterval)time API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @method renderWithViewport:viewport:commandBuffer:passDescriptor:
 @abstract renders the receiver's scene with the specified viewport, Metal command buffer and pass descriptor.
 @discussion Use this method to render using Metal. This method doesn't update the scene's animations, physics, particles etc... It's up to you to call "updateAtTime:" to update the scene.
 */
- (void)renderWithViewport:(CGRect)viewport commandBuffer:(id <MTLCommandBuffer>)commandBuffer passDescriptor:(MTLRenderPassDescriptor *)renderPassDescriptor API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property nextFrameTime
 @abstract Returns the time at which the next update should happen. If infinite no update needs to be scheduled yet. If the current frame time, a continuous animation is running and an update should be scheduled after a "natural" delay.
 */
@property(nonatomic, readonly) CFTimeInterval nextFrameTime API_AVAILABLE(macos(10.10));

/*!
 @method snapshotAtTime:withSize:antialiasingMode:
 @abstract renders the receiver's scene at the specified time (system time) into an image.
 */
- (UIImage *)snapshotAtTime:(CFTimeInterval)time withSize:(CGSize)size antialiasingMode:(SCNAntialiasingMode)antialiasingMode API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @method updateProbes:atTime:
 @abstract Update the specified probes by computing their incoming irradiance in the receiver's scene at the specified time.
 @param lightProbes An array of nodes that must have a light probe attached.
 @param time The time used to render the scene when computing the light probes irradiance.
 @discussion Light probes are only supported with Metal. This method is observable using NSProgress.
 */
- (void)updateProbes:(NSArray<SCNNode*> *)lightProbes atTime:(CFTimeInterval)time API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));


// Deprecated
/*!
 @method render
 @abstract renders the receiver's scene at the current system time.
 @discussion This method only work if the receiver was allocated with an OpenGL context and it is deprecated (use renderAtTime: instead). Use renderAtTime:withEncoder:pass:commandQueue: to render with Metal.
 */
- (void)render API_DEPRECATED_WITH_REPLACEMENT("-renderAtTime:withEncoder:pass:commandQueue:", macos(10.8, 10.11), ios(8.0, 9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNMaterial.h
//
//  SCNMaterial.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNShadable.h>

NS_ASSUME_NONNULL_BEGIN

/*
 Constants for lightingModel
 
 For every lighting model, the final color is computed as follows:
   finalColor = (<emission> + color + <reflective>) * <multiply>
 where
   <emission> — The 'emission' property of the SCNMaterial instance
   <reflective> — The 'reflective' property of the SCNMaterial instance
   <multiply> — The 'multiply' property of the SCNMaterial instance
 and
   color - The 'color' term depends on the lighting models described below
 
 SCNLightingModelPhong:
   Produces a specularly shaded surface where the specular reflection is shaded according the Phong BRDF approximation.
   The reflected color is calculated as:
     color = <ambient> * al + <diffuse> * max(N ⋅ L, 0) + <specular> * pow(max(R ⋅ E, 0), <shininess>)
   where
     al — Sum of all ambient lights currently active (visible) in the scene
     N — Normal vector
     L — Light vector
     E — Eye vector
     R — Perfect reflection vector (reflect (L around N))
   and
     <ambient> — The 'ambient' property of the SCNMaterial instance
     <diffuse> — The 'diffuse' property of the SCNMaterial instance
     <specular> — The 'specular' property of the SCNMaterial instance
     <shininess> — The 'shininess' property of the SCNMaterial instance
 
 SCNLightingModelBlinn:
   Produces a specularly shaded surface with a Blinn BRDF approximation.
   The reflected color is calculated as:
     color = <ambient> * al + <diffuse> * max(N ⋅ L, 0) + <specular> * pow(max(H ⋅ N, 0), <shininess>)
   where
     al — Sum of all ambient lights currently active (visible) in the scene
     N — Normal vector
     L — Light vector
     E — Eye vector
     H — Half-angle vector, calculated as halfway between the unit Eye and Light vectors, using the equation H = normalize(E + L)
   and
     <ambient> — The 'ambient' property of the SCNMaterial instance
     <diffuse> — The 'diffuse' property of the SCNMaterial instance
     <specular> — The 'specular' property of the SCNMaterial instance
     <shininess> — The 'shininess' property of the SCNMaterial instance
 
 SCNLightingModelLambert:
   Produces a diffuse shaded surface with no specular reflection.
   The result is based on Lambert’s Law, which states that when light hits a rough surface, the light is reflected in all directions equally.
   The reflected color is calculated as:
     color = <ambient> * al + <diffuse> * max(N ⋅ L, 0)
   where
     al — Sum of all ambient lights currently active (visible) in the scene
     N — Normal vector
     L — Light vector
   and
     <ambient> — The 'ambient' property of the SCNMaterial instance
     <diffuse> — The 'diffuse' property of the SCNMaterial instance
 
 SCNLightingModelConstant:
   Produces a constantly shaded surface that is independent of lighting.
   The reflected color is calculated as:
     color = <ambient> * al + <diffuse>
   where
     al — Sum of all ambient lights currently active (visible) in the scene
   and
     <ambient> — The 'ambient' property of the SCNMaterial instance
     <diffuse> — The 'diffuse' property of the SCNMaterial instance
 */

typedef NSString * SCNLightingModel NS_STRING_ENUM;
SCN_EXPORT SCNLightingModel const SCNLightingModelPhong;
SCN_EXPORT SCNLightingModel const SCNLightingModelBlinn;
SCN_EXPORT SCNLightingModel const SCNLightingModelLambert;
SCN_EXPORT SCNLightingModel const SCNLightingModelConstant;
SCN_EXPORT SCNLightingModel const SCNLightingModelPhysicallyBased API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

typedef NS_ENUM(NSUInteger, SCNFillMode) {
    SCNFillModeFill  = 0,
    SCNFillModeLines = 1
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

typedef NS_ENUM(NSInteger, SCNCullMode) {
	SCNCullModeBack  = 0,
	SCNCullModeFront = 1
};

#define SCNCullBack  SCNCullModeBack
#define SCNCullFront SCNCullModeFront

typedef NS_ENUM(NSInteger, SCNTransparencyMode) {
    SCNTransparencyModeAOne                                                                         = 0, // Takes the transparency information from the alpha channel. The value 1.0 is opaque.
    SCNTransparencyModeRGBZero                                                                      = 1, // Ignores the alpha channel and takes the transparency information from the luminance of the red, green, and blue channels. The value 0.0 is opaque.
    SCNTransparencyModeSingleLayer API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 2, // Ensures that one layer of transparency is draw correctly.
    SCNTransparencyModeDualLayer   API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 3, // Ensures that two layers of transparency are ordered and drawn correctly. This should be used for transparent convex objects like cubes and spheres, when you want to see both front and back faces.
    SCNTransparencyModeDefault     API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = SCNTransparencyModeAOne
};

/*! 
 @enum SCNBlendMode
 @abstract  Blend modes that SCNMaterial uses to compose with the framebuffer to produce blended colors.
 */
typedef NS_ENUM(NSInteger, SCNBlendMode) {
    SCNBlendModeAlpha                                                                     = 0, // Blends the source and destination colors by adding the source multiplied by source alpha and the destination multiplied by one minus source alpha.
    SCNBlendModeAdd                                                                       = 1, // Blends the source and destination colors by adding them up.
    SCNBlendModeSubtract                                                                  = 2, // Blends the source and destination colors by subtracting the source from the destination.
    SCNBlendModeMultiply                                                                  = 3, // Blends the source and destination colors by multiplying them.
    SCNBlendModeScreen                                                                    = 4, // Blends the source and destination colors by multiplying one minus the source with the destination and adding the source.
    SCNBlendModeReplace                                                                   = 5, // Replaces the destination with the source (ignores alpha).
    SCNBlendModeMax      API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 6  // Max the destination with the source (ignores alpha).
} API_AVAILABLE(macos(10.11), ios(9.0));

@class SCNMaterialProperty;
@class SCNProgram;
@protocol SCNProgramDelegate;
@protocol SCNShadable;

/*!
 @class SCNMaterial
 @abstract A SCNMaterial determines how a geometry is rendered. It encapsulates the colors and textures that define the appearance of 3d geometries.
 */

SCN_EXPORT
@interface SCNMaterial : NSObject <SCNAnimatable, SCNShadable, NSCopying, NSSecureCoding>

/*! 
 @method material
 @abstract Creates and initialize a material instance.
 */
+ (instancetype)material;

/*! 
 @property name
 @abstract Determines the name of the receiver.
 */
@property(nonatomic, copy, nullable) NSString *name;

// MARK: - Material Properties

/*! 
 @property diffuse
 @abstract Specifies the receiver's diffuse property.
 @discussion The diffuse property specifies the amount of light diffusely reflected from the surface. The diffuse light is reflected equally in all directions and is therefore independent of the point of view.
 */
@property(nonatomic, readonly) SCNMaterialProperty *diffuse;

/*! 
 @property ambient
 @abstract Specifies the receiver's ambient property.
 @discussion The ambient property specifies the amount of ambient light to reflect. This property has no visual impact on scenes that have no ambient light. Setting the ambient has no effect if locksAmbientWithDiffuse is set to YES.
 */
@property(nonatomic, readonly) SCNMaterialProperty *ambient;

/*! 
 @property specular
 @abstract Specifies the receiver's specular property.
 @discussion The specular property specifies the amount of light to reflect in a mirror-like manner. The specular intensity increases when the point of view lines up with the direction of the reflected light.
 */
@property(nonatomic, readonly) SCNMaterialProperty *specular;

/*! 
 @property emission
 @abstract The emission property specifies the amount of light the material emits. This emission does not light up other surfaces in the scene.
 */
@property(nonatomic, readonly) SCNMaterialProperty *emission;

/*! 
 @property transparent
 @abstract The transparent property specifies the transparent areas of the material.
 */
@property(nonatomic, readonly) SCNMaterialProperty *transparent;

/*! 
 @property reflective
 @abstract The reflective property specifies the reflectivity of the surface. The surface will not actually reflect other objects in the scene. This property may be used as a sphere mapping to reflect a precomputed environment.
 */
@property(nonatomic, readonly) SCNMaterialProperty *reflective;

/*! 
 @property multiply
 @abstract The multiply property specifies a color or an image used to multiply the output fragments with. The computed fragments are multiplied with the multiply value to produce the final fragments. This property may be used for shadow maps, to fade out or tint 3d objects.
 */
@property(nonatomic, readonly) SCNMaterialProperty *multiply;

/*! 
 @property normal
 @abstract The normal property specifies the surface orientation. 
 @discussion When an image is set on the normal property the material is automatically lit per pixel. Setting a color has no effect.
 */
@property(nonatomic, readonly) SCNMaterialProperty *normal;

/*!
 @property displacement
 @abstract The displacement property specifies how vertex are translated in tangent space.
 @discussion Pass a grayscale image for a simple 'elevation' or rgb image for a vector displacement.
 */
@property(nonatomic, readonly) SCNMaterialProperty *displacement API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property ambientOcclusion
 @abstract The ambientOcclusion property specifies the ambient occlusion of the surface. The ambient occlusion is multiplied with the ambient light, then the result is added to the lighting contribution. This property has no visual impact on scenes that have no ambient light. When an ambient occlusion map is set, the ambient property is ignored.
 */
@property(nonatomic, readonly) SCNMaterialProperty *ambientOcclusion API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property selfIllumination
 @abstract The selfIllumination property specifies a texture or a color that is added to the lighting contribution of the surface. When a selfIllumination is set, the emission property is ignored.
 */
@property(nonatomic, readonly) SCNMaterialProperty *selfIllumination API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property metalness
 @abstract The metalness property specifies how metallic the material's surface appears. Lower values (darker colors) cause the material to appear more like a dielectric surface. Higher values (brighter colors) cause the surface to appear more metallic. This property is only used when 'lightingModelName' is 'SCNLightingModelPhysicallyBased'.
 */
@property(nonatomic, readonly) SCNMaterialProperty *metalness API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property roughness
 @abstract The roughness property specifies the apparent smoothness of the surface. Lower values (darker colors) cause the material to appear shiny, with well-defined specular highlights. Higher values (brighter colors) cause specular highlights to spread out and the diffuse property of the material to become more retroreflective. This property is only used when 'lightingModelName' is 'SCNLightingModelPhysicallyBased'.
 */
@property(nonatomic, readonly) SCNMaterialProperty *roughness API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

// MARK: -

/*! 
 @property shininess
 @abstract Specifies the receiver's shininess value. Defaults to 1.0. Animatable.
 */
@property(nonatomic) CGFloat shininess;

/*! 
 @property transparency
 @abstract Specifies the receiver's transparency value. Defaults to 1.0. Animatable.
 @discussion The color of the transparent property is multiplied by this property. The result is then used to produce the final transparency according to the rule defined by the transparencyMode property.
 */
@property(nonatomic) CGFloat transparency;

/*!
 @property lightingModelName
 @abstract Determines the receiver's lighting model. See above for the list of lighting models. Defaults to SCNLightingModelBlinn.
 */
@property(nonatomic, copy) SCNLightingModel lightingModelName;

/*! 
 @property litPerPixel
 @abstract Determines whether the receiver is lit per pixel. Defaults to YES. Animatable.
 */
@property(nonatomic, getter=isLitPerPixel) BOOL litPerPixel;

/*! 
 @property doubleSided
 @abstract Determines whether the receiver is double sided. Defaults to NO. Animatable.
 */
@property(nonatomic, getter=isDoubleSided) BOOL doubleSided;

/*!
 @property fillMode
 @abstract Determines of to how to rasterize the receiver's primitives. Defaults to SCNFillModeFill.
 */
@property(nonatomic) SCNFillMode fillMode API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*! 
 @property cullMode
 @abstract Determines the culling mode of the receiver. Defaults to SCNCullBack. Animatable.
 */
@property(nonatomic) SCNCullMode cullMode;

/*! 
 @property transparencyMode
 @abstract Determines the transparency mode of the receiver. See above for the transparency modes. Defaults to SCNTransparencyModeDefault.
 */
@property(nonatomic) SCNTransparencyMode transparencyMode;

/*! 
 @property locksAmbientWithDiffuse
 @abstract Makes the ambient property automatically match the diffuse property. Defaults to YES. Animatable.
 */
@property(nonatomic) BOOL locksAmbientWithDiffuse;

/*! 
 @property writeToDepthBuffer
 @abstract Determines whether the receiver writes to the depth buffer when rendered. Defaults to YES.
 */
@property(nonatomic) BOOL writesToDepthBuffer;

/*!
 @abstract Determines whether the receiver writes to the color buffer when rendered. Defaults to SCNColorMaskAll.
 */
@property(nonatomic) SCNColorMask colorBufferWriteMask API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property readsFromDepthBuffer
 @abstract Determines whether the receiver reads from the depth buffer when rendered. Defaults to YES.
 */
@property(nonatomic) BOOL readsFromDepthBuffer API_AVAILABLE(macos(10.9));

/*!
 @property fresnelExponent
 @abstract Specifies the receiver's fresnel exponent value. Defaults to 0.0. Animatable.
 @discussion The effect of the reflectivity property is modulated by this property. The fresnelExponent changes the exponent of the reflectance. The bigger the exponent, the more concentrated the reflection is around the edges.
 */
@property(nonatomic) CGFloat fresnelExponent API_AVAILABLE(macos(10.9));

/*!
 @property blendMode
 @abstract Specifies the receiver's blend mode. Defaults to SCNBlendModeAlpha.
 */
@property(nonatomic) SCNBlendMode blendMode API_AVAILABLE(macos(10.11), ios(9.0));

@end
    
NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNJavascript.h
//
//  SCNJavascript.h
//  SceneKit
//
//  Copyright © 2014-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class JSContext;

NS_ASSUME_NONNULL_BEGIN

/*
 @function SCNExportJavaScriptModule
 @abstract Exports SceneKit's symbols (constants and class definition) into the specified JavaScript context.
 @discussion SceneKit's classes, properties and constants are exported as global object with their original name. Selectors are exported using the rules defined in JavaScriptCore's JSExport.h.
 
 For example to instanciate a node in JavaScript:
 
 var aNode = SCNNode.node();
 
 to change its opacity:
 
 aNode.opacity = 0.5;
 
 to remove from its parent node:
 
 aNode.removeFromParentNode();
 
 to animate a node opacity:
 
 SCNTransaction.begin();
 SCNTransaction.setAnimationDuration(1.0);
 aNode.opacity = 0.5;
 SCNTransaction.commit();
 
 The following special objects are also exported:
 
 class name           constructor                                                  Objective-C class
 SCNColor             SCNColor.color(r,g,b,a)                                      NSColor
 CATimingFunction     CATimingFunction.functionWithName(name)                      CATimingFunction
 CABasicAnimation     CABasicAnimation.animationWithKeyPath(aPath)                 CABasicAnimation
 CAAnimationGroup     new CAAnimationGroup()                                       CAAnimationGroup
 CAKeyframeAnimation  CAKeyframeAnimation.animationWithKeyPath(aPath)              CAKeyframeAnimation
 SCNImage             SCNImage.imageWithURL(aURL)                                  NSImage / UIImage
                      SCNImage.imageWithPath(aPath)                                  
 
 Vectors use this syntax:
 aNode.scale = {x:2, y:2, z:2};
 
 Matrices use this syntax:
 aNode.transform = {m11:1, m12:0, m13:0 ... m44:1};
 */

SCN_EXPORT void SCNExportJavaScriptModule(JSContext *context) API_AVAILABLE(macos(10.10));

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNScene.h
//
//  SCNScene.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNSceneSource.h>
#import <SceneKit/SCNMaterialProperty.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;
@class SCNPhysicsWorld;
@protocol SCNSceneExportDelegate;

/*!
 @typedef SCNSceneSourceStatusHandler
 @discussion Signature of a block that will be called repeatedly while the scene is being exported.
 @param totalProgress is a floating-point number between 0 and 1. 0 means the loading process has just started and 1 that it is complete. 
 @param error Will contain information about the failure if any.
 @param stop Set *stop to YES if you want to abort the operation.
 */
typedef void (^SCNSceneExportProgressHandler)(float totalProgress, NSError * _Nullable error, BOOL *stop);


/*! @group Scene writing options */

/*! @constant SCNSceneExportDestinationURL
 @abstract Specifies the final destination (as a NSURL) of the scene being exported.
 @discussion The destination URL is required if the scene is exported to a temporary directory and then moved to a final destination. This enables the exported document to get correct relative paths to referenced images.
 */
SCN_EXPORT NSString * const SCNSceneExportDestinationURL API_AVAILABLE(macos(10.9));


/*! @group Scene attributes
    @abstract These keys can be used with the -[SCNScene attributeForKey:] method.
 */

typedef NSString * SCNSceneAttribute NS_STRING_ENUM;
SCN_EXPORT SCNSceneAttribute const SCNSceneStartTimeAttributeKey;                          // A floating point value, encapsulated in a NSNumber, containing the start time of the scene.
SCN_EXPORT SCNSceneAttribute const SCNSceneEndTimeAttributeKey;                            // A floating point value, encapsulated in a NSNumber, containing the end time of the scene.
SCN_EXPORT SCNSceneAttribute const SCNSceneFrameRateAttributeKey;                          // A floating point value, encapsulated in a NSNumber, containing the framerate of the scene.
SCN_EXPORT SCNSceneAttribute const SCNSceneUpAxisAttributeKey API_AVAILABLE(macos(10.10)); // A vector3 value, encapsulated in a NSValue, containing the up axis of the scene. This is just for information, setting the up axis as no effect.

#define SCNSceneAttributeStartTime SCNSceneStartTimeAttributeKey
#define SCNSceneAttributeEndTime   SCNSceneEndTimeAttributeKey
#define SCNSceneAttributeFrameRate SCNSceneFrameRateAttributeKey
#define SCNSceneAttributeUpAxis    SCNSceneUpAxisAttributeKey

/*!
 @class SCNScene
 @abstract SCNScene is the class that describes a 3d scene. It encapsulates a node hierarchy.
 */

SCN_EXPORT
@interface SCNScene : NSObject <NSSecureCoding>

+ (instancetype)scene;

/*! 
 @property root
 @abstract Specifies the root node of the node hierarchy.
 @discussion Note that we have only one root node, whereas some file formats might have many nodes
 at the root of their hierarchies. The root node(s) of the imported files will therefore be children
 of the SCNScene's root node.
 */
@property(nonatomic, readonly) SCNNode *rootNode;

/*!
 @property physicsWorld
 @abstract Specifies the physics world of the receiver.
 @discussion Every scene automatically creates a physics world object to simulate physics on nodes in the scene. You use this property to access the scene’s global physics properties, such as gravity. To add physics to a particular node, see physicsBody.
 */
@property(nonatomic, readonly) SCNPhysicsWorld *physicsWorld API_AVAILABLE(macos(10.10));

/*!
 @method attributeForKey:
 @abstract Retrieves a scene attribute.
 @discussion The available keys are listed in the "Scene attributes" group.
 @param key An NSString object that specifies the attribute to be read
 */
- (nullable id)attributeForKey:(NSString *)key;

/*! 
 @method setAttribute:forKey:
 @abstract Sets a scene attribute
 @discussion The available keys are listed in the "Scene attributes" group.
 @param attribute An object that specifies the value of the attribute to be written.
 @param key An NSString object that specifies the attribute to be written
 */
- (void)setAttribute:(nullable id)attribute forKey:(NSString *)key;

/*!
 @property background
 @abstract Specifies the background of the receiver.
 @discussion The background is rendered before the rest of the scene.
             The background can be rendered as a skybox by setting a cube map as described in SCNMaterialProperty.h
             Colors are supported starting in macOS 10.12 and iOS 10. Prior to that you can use SCNView.backgroundColor.
             MDLSkyCubeTexture is supported starting in macOS 10.13 and iOS 11.
 */
@property(nonatomic, readonly) SCNMaterialProperty *background API_AVAILABLE(macos(10.9));

/*!
 @property lightingEnvironment
 @abstract Specifies the receiver's environment for image-based lighting (IBL).
 @discussion The environment should be a cube map as described in SCNMaterialProperty.h.
             MDLSkyCubeTexture is supported starting in macOS 10.13 and iOS 11.
 */
@property(nonatomic, readonly) SCNMaterialProperty *lightingEnvironment API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));


#pragma mark - Loading

/*!
 @method sceneNamed:
 @abstract Creates and returns a scene associated with the specified filename.
 @param name The name of the file. The method looks for a file with the specified name in the application’s main bundle.
 @discussion This method initializes with no options and does not check for errors. The resulting object is not cached.
 */
+ (nullable instancetype)sceneNamed:(NSString *)name API_AVAILABLE(macos(10.9));

/*!
 @method sceneNamed:options:
 @abstract Creates and returns a scene associated with the specified filename.
 @param name The name of the file. The method looks for a file with the specified name in the application’s main bundle.
 @param directory The name of the bundle sub-directory to search into.
 @param options An options dictionary. The relevant keys are documented in the SCNSceneSource class.
 @discussion This method initializes with no options and does not check for errors. The resulting object is not cached.
 */
+ (nullable instancetype)sceneNamed:(NSString *)name inDirectory:(nullable NSString *)directory options:(nullable NSDictionary<SCNSceneSourceLoadingOption, id> *)options API_AVAILABLE(macos(10.10));

/*!
 @method sceneWithURL:options:error:
 @abstract Creates and returns a scene from the specified URL.
 @param url The URL to the 3D file.
 @param options An options dictionary. The relevant keys are documented in the SCNSceneSource class.
 @param error A NSError object passed by reference to get more information about the error when a nil is returned.
 @discussion This method is here for convenience. It is equivalent to initializing a SCNSceneSource with the specified
 url and options, and asking it for its scene with the same options.
 */
+ (nullable instancetype)sceneWithURL:(NSURL *)url options:(nullable NSDictionary<SCNSceneSourceLoadingOption, id> *)options error:(NSError **)error;

#pragma mark - Writing

/*!
 @method writeToURL:options:delegate:progressHandler:
 @abstract write the scene to the specified url.
 @param url the destination url to write the scene to.
 @param options A dictionary of options. The valid keys are described in the "Scene writing options" section.
 @param delegate an optional delegate to manage external references such as images.
 @param progressHandler an optional block to handle the progress of the operation.
 @return Returns YES if the operation succeeded, NO otherwise. Errors checking can be done via the "error"
 parameter of the 'progressHandler'.
 @discussion macOS 10.10 and lower only supports exporting to .dae files.
             Starting macOS 10.11 exporting supports .dae, .scn as well as file all formats supported by Model I/O.
             Starting iOS 10 exporting supports .scn as well as all file formats supported by Model I/O.
 */
- (BOOL)writeToURL:(NSURL *)url options:(nullable NSDictionary<NSString *, id> *)options delegate:(nullable id <SCNSceneExportDelegate>)delegate progressHandler:(nullable SCNSceneExportProgressHandler)progressHandler API_AVAILABLE(macos(10.9), ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos);

#pragma mark - Fog

/*!
 @property fogStartDistance
 @abstract Specifies the receiver's fog start distance. Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat fogStartDistance API_AVAILABLE(macos(10.10));

/*!
 @property fogEndDistance
 @abstract Specifies the receiver's fog end distance. Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat fogEndDistance API_AVAILABLE(macos(10.10));

/*!
 @property fogDensityExponent
 @abstract Specifies the receiver's fog power exponent. Animatable. Defaults to 1.
 @discussion Controls the attenuation between the start and end fog distances. 0 means a constant fog, 1 a linear fog and 2 a quadratic fog, but any positive value will work.
 */
@property(nonatomic) CGFloat fogDensityExponent API_AVAILABLE(macos(10.10));

/*!
 @property fogColor
 @abstract Specifies the receiver's fog color (NSColor or CGColorRef). Animatable. Defaults to white.
 @discussion The initial value is a NSColor.
 */
@property(nonatomic, retain) id fogColor API_AVAILABLE(macos(10.10));


#pragma mark - Pause

/*!
 @property paused
 @abstract Controls whether or not the scene is paused. Defaults to NO.
 @discussion Pausing a scene will pause animations, actions, particles and physics.
 */
@property(nonatomic, getter=isPaused) BOOL paused API_AVAILABLE(macos(10.10));


@end

API_AVAILABLE(macos(10.9), ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos)
@protocol SCNSceneExportDelegate <NSObject>
@optional
/*!
 @method writeImage:withSceneDocumentURL:originalImageURL:
 @abstract Invoked on the delegate to write the referenced image and return the destination url.
 @param image The image to write.
 @param documentURL The url where the scene is currently exported to.
 @param originalImageURL The original url for the image. May be nil if the image was not previously loaded from a url.
 @return The delegate must returns the url of the image that was exported or nil if it didn't export any image. If the returned value is nil, the image will be exported to a default destination in a default format.
 */
- (nullable NSURL *)writeImage:(UIImage *)image withSceneDocumentURL:(NSURL *)documentURL originalImageURL:(nullable NSURL *)originalImageURL API_AVAILABLE(macos(10.9), ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNSkinner.h
//
//  SCNSkinner.h
//  SceneKit
//
//  Copyright © 2013-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;
@class SCNGeometry;
@class SCNGeometrySource;

/*!
 @class SCNSkinner
 @abstract SCNSkinner controls the deformation of skinned geometries */

SCN_EXPORT API_AVAILABLE(macos(10.9))
@interface SCNSkinner : NSObject <NSSecureCoding>

/*!
 @property skeleton
 @abstract Specifies the skeleton of the receiver.
 @discussion When setting a new skeleton, the new skeleton must have the same hierarchy of joints.
 */
@property(nonatomic, weak, nullable) SCNNode *skeleton;

/*!
 @method skinnerWithBaseGeometry:bones:boneInverseBindTransforms:boneWeights:boneIndices:
 @abstract Creates and initialize a skinner instance with the specified parameters.
 @param baseGeometry Specifies the base geometry used by the skinner
 @param bones Specifies the array of bones.
 @param boneInverseBindTransforms The inverse of the bone’s bind-space transformation matrix at the time the bind shape was bound to this bone.
 @param boneWeights A buffer of weights. This contains the weights of every influence of every vertex. The number of influence per vertex is controlled by the number of component in the geometry source.
 @param boneIndices A buffer of bone indexes. This buffer contains the corresponding index in the bones array for every weight in the weights buffer.
 */
+ (instancetype)skinnerWithBaseGeometry:(nullable SCNGeometry *)baseGeometry bones:(NSArray<SCNNode *> *)bones boneInverseBindTransforms:(nullable NSArray<NSValue *> *)boneInverseBindTransforms boneWeights:(SCNGeometrySource *)boneWeights boneIndices:(SCNGeometrySource *)boneIndices API_AVAILABLE(macos(10.10));

/*!
 @property baseGeometry
 @abstract Specifies the base geometry of the receiver.
 @discussion Updating this will change the geometry of all the nodes sharing the skinner.
 Access the node's geometry if you want to update this specific skinner properties (materials for example).
 Access this property if you want a whole new geometry (which will necessarily be shared among the skinner instances), with
 different sources, for instance.
 */
@property(retain, nonatomic, nullable) SCNGeometry *baseGeometry API_AVAILABLE(macos(10.9));

/*!
 @property baseGeometryBindTransform
 @abstract Specifies the transform of the baseGeometry at the time when the mesh was bound to a skeleton. This transforms the baseGeometry from object space to a space on which the skinning then applies.
 */
@property(nonatomic) SCNMatrix4 baseGeometryBindTransform API_AVAILABLE(macos(10.10));

/*!
 @property boneInverseBindTransforms
 @abstract The inverse of the bone’s bind-space transformation matrix at the time the bind shape was bound to this bone.
 @discussion boneInverseBindTransforms is an array of SCNMatrix4 wrapped into instances of NSValue.
 */
@property(readonly, nonatomic, nullable) NSArray<NSValue *> *boneInverseBindTransforms API_AVAILABLE(macos(10.10));

/*!
 @property bones
 @abstract The bones of the skinner.
 */
@property(readonly, nonatomic) NSArray<SCNNode *> *bones API_AVAILABLE(macos(10.10));

/*!
 @property boneWeights
 @abstract The bone weights of the receiver.
 */
@property(readonly, nonatomic) SCNGeometrySource *boneWeights API_AVAILABLE(macos(10.10));

/*!
 @property boneIndices
 @abstract The bone indices of the receiver.
 */
@property(readonly, nonatomic) SCNGeometrySource *boneIndices API_AVAILABLE(macos(10.10));

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNConstraint.h
//
//  SCNConstraint.h
//  SceneKit
//
//  Copyright © 2013-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNAnimation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;

/*!
 @class SCNConstraint
 @abstract A SCNConstraint is an abstract class that represents a single constraint that can be applied to a node.
 */

SCN_EXPORT API_AVAILABLE(macos(10.9))
@interface SCNConstraint : NSObject <NSCopying, NSSecureCoding, SCNAnimatable>

/*!
 @property enable
 @abstract Determines whether the constraint is enabled or not. Defaults to YES.
 */
@property(nonatomic, getter = isEnabled) BOOL enabled API_AVAILABLE(macos(10.10));

/*!
 @property influenceFactor
 @abstract Specifies the inflence factor of the receiver. Defaults to 1. Animatable
 */
@property(nonatomic) CGFloat influenceFactor API_AVAILABLE(macos(10.10));

/*!
 @property incremental
 @abstract Specifies whether or not the contraint should applies incrementally and have it's effect being cumulated over the rendered frames. Defaults to YES on macOS 10.13, iOS 11, tvOS 11 and watchOS 4. Defaults to NO in earlier versions.
 */
@property(nonatomic, getter=isIncremental) BOOL incremental API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@end

// MARK: -

/*!
 @class SCNLookAtConstraint
 @abstract A SCNLookAtConstraint applies on a node's orientation so that it always look at another node.
 */

SCN_EXPORT API_AVAILABLE(macos(10.9))
@interface SCNLookAtConstraint : SCNConstraint

/*!
 @method lookAtConstraintWithTarget:
 @abstract Creates and returns a SCNLookAtConstraint object with the specified target.
 @param target The target node to look at.
 */
+ (instancetype)lookAtConstraintWithTarget:(nullable SCNNode *)target;

/*!
 @property target
 @abstract Defines the target node to look at.
 */
@property(nonatomic, retain, nullable) SCNNode *target;
- (nullable SCNNode *)target;
- (void)setTarget:(nullable SCNNode *)target API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property targetOffset
 @abstract Offset look at position in target space. Defaults to zero. Animatable
 */
@property(nonatomic, assign) SCNVector3 targetOffset API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property targetOffset
 @abstract Front direction in the constraint owner local space. Defaults to -[SCNNode localFront]. Animatable
 */
@property(nonatomic, assign) SCNVector3 localFront API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property worldUp
 @abstract Up reference direction in world space. Defaults to -[SCNNode localUp]. Animatable
 */
@property(nonatomic, assign) SCNVector3 worldUp API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));


/*!
 @property gimbalLockEnabled
 @abstract Specifies whether the receiver enables the gimbal lock. Defaults to NO.
 @discussion Enabling the gimbal lock prevents the receiver from rotating the constrained node around to roll axis.
 */
@property(nonatomic) BOOL gimbalLockEnabled;

@end

// MARK: -

typedef NS_OPTIONS(NSUInteger, SCNBillboardAxis) {
    SCNBillboardAxisX = 0x1 << 0,
    SCNBillboardAxisY = 0x1 << 1,
    SCNBillboardAxisZ = 0x1 << 2,
    SCNBillboardAxisAll = SCNBillboardAxisX | SCNBillboardAxisY | SCNBillboardAxisZ
};

SCN_EXPORT API_AVAILABLE(macos(10.11), ios(9.0))
@interface SCNBillboardConstraint : SCNConstraint

/*!
 @method billboardConstraint:
 @abstract Creates and returns a SCNBillboardConstraint constraint.
 @discussion A billboard constraint forces the receiver to look into the direction of the current point of view.
 */
+ (instancetype)billboardConstraint;

/*!
 @property freeAxes
 @abstract Specifies the axes on which the billboarding orientation operates. Defaults to SCNBillboardAxisAll.
 */
@property(nonatomic) SCNBillboardAxis freeAxes;

@end

// MARK: -

/*!
 @class SCNTransformConstraint
 @abstract A SCNTransformConstraint applies on the transform of a node via a custom block.
 */
SCN_EXPORT API_AVAILABLE(macos(10.9))
@interface SCNTransformConstraint : SCNConstraint

/*!
 @method transformConstraintInWorldSpace:withBlock:
 @abstract Creates and returns a SCNTransformConstraint object with the specified parameters.
 @param world Determines whether the constraint is evaluated in world or local space.
 @param block The custom block to call to evaluate the constraint.
 @discussion The node and its transform are passed to the block. The transform returned by the block will be used to render the node.
 */
+ (instancetype)transformConstraintInWorldSpace:(BOOL)world withBlock:(SCNMatrix4 (^)(SCNNode *node, SCNMatrix4 transform))block;

/*!
 @method positionConstraintInWorldSpace:withBlock:
 @abstract Creates and returns a SCNTransformConstraint object with the specified parameters.
 @param world Determines whether the constraint is evaluated in world or local space.
 @param block The custom block to call to evaluate the constraint.
 @discussion The node and its position are passed to the block. The position returned by the block will be used to render the node.
 */
+ (instancetype)positionConstraintInWorldSpace:(BOOL)world withBlock:(SCNVector3 (^)(SCNNode *node, SCNVector3 position))block API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @method orientationConstraintInWorldSpace:withBlock:
 @abstract Creates and returns a SCNTransformConstraint object with the specified parameters.
 @param world Determines whether the constraint is evaluated in world or local space.
 @param block The custom block to call to evaluate the constraint.
 @discussion The node and its quaternion are passed to the block. The quaternion returned by the block will be used to render the node.
 */
+ (instancetype)orientationConstraintInWorldSpace:(BOOL)world withBlock:(SCNQuaternion (^)(SCNNode *node, SCNQuaternion quaternion))block API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@end

// MARK: -

/*!
 @class SCNIKConstraint
 @abstract A SCNIKConstraint applies an inverse kinematics constraint
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNIKConstraint : SCNConstraint

/*!
 @method initWithChainRootNode:
 @abstract Creates and returns a SCNIKConstraint object with the specified parameter.
 @param chainRootNode The root node of the kinematic chain.
 @discussion "chainRootNode" must be an ancestor of the node on which the constraint is applied.
 */
- (instancetype)initWithChainRootNode:(SCNNode *)chainRootNode API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @method inverseKinematicsConstraintWithChainRootNode:
 @abstract Creates and returns a SCNIKConstraint object with the specified parameter.
 @param chainRootNode The root node of the kinematic chain.
 @discussion "chainRootNode" must be an ancestor of the node on which the constraint is applied.
*/
+ (instancetype)inverseKinematicsConstraintWithChainRootNode:(SCNNode *)chainRootNode;

/*!
 @property chainRootNode
 @abstract Specifies the root node of the kinematic chain.
 */
@property(nonatomic, readonly) SCNNode *chainRootNode;

/*!
 @property target
 @abstract Specifies the target position (in world space coordinates) of the end joint (i.e the node that owns the IK constraint). Defaults to (0,0,0). Animatable.
 */
@property(nonatomic) SCNVector3 targetPosition;

/*!
 @method setMaxAllowedRotationAngle:forJoint:
 @abstract Specifies the maximum rotation allowed (in degrees) for the specified joint from its initial orientation. Defaults to 180.
 */
- (void)setMaxAllowedRotationAngle:(CGFloat)angle forJoint:(SCNNode *)node;
- (CGFloat)maxAllowedRotationAngleForJoint:(SCNNode *)node;

@end

// MARK: -

/*!
 @class SCNDistanceConstraint
 @abstract A SCNDistanceConstraint ensure a minimum/maximum distance with a target node.
 */
SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNDistanceConstraint : SCNConstraint

/*!
 @method distanceConstraintWithTarget
 @abstract Creates and returns a SCNDistanceConstraint constraint.
 */
+ (instancetype)distanceConstraintWithTarget:(nullable SCNNode *)target;

/*!
 @property target
 @abstract Defines the target node to keep distance with.
 */
@property(nonatomic, retain, nullable) SCNNode *target;

/*!
 @property minimumDistance
 @abstract The minimum distance. Defaults to 0. Animatable.
 */
@property(nonatomic, assign) CGFloat minimumDistance;

/*!
 @property maximumDistance
 @abstract The minimum distance. Defaults to MAXFLOAT. Animatable.
 */
@property(nonatomic, assign) CGFloat maximumDistance;

@end

// MARK: -

/*!
 @class SCNReplicatorConstraint
 @abstract A SCNReplicatorConstraint replicates the position/orientation/scale of a target node
 */
SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNReplicatorConstraint : SCNConstraint

/*!
 @method replicatorWithTargetNode
 @abstract Creates and returns a SCNReplicatorConstraint constraint.
 */
+ (instancetype)replicatorConstraintWithTarget:(nullable SCNNode *)target;

/*!
 @property target
 @abstract Defines the target node to replicate
 */
@property(nonatomic, retain, nullable) SCNNode *target;

/*!
 @property replicatesOrientation
 @abstract Defines whether or not the constraint should replicate the target orientation. Defaults to YES.
 */
@property(nonatomic, assign) BOOL replicatesOrientation;

/*!
 @property replicatesPosition
 @abstract Defines whether or not the constraint should replicate the target position. Defaults to YES.
 */
@property(nonatomic, assign) BOOL replicatesPosition;

/*!
 @property replicatesScale
 @abstract Defines whether or not the constraint should replicate the target scale. Defaults to YES.
 */
@property(nonatomic, assign) BOOL replicatesScale;

/*!
 @property orientationOffset
 @abstract Defines an addition orientation offset. Defaults to no offset. Animatable.
 */
@property(nonatomic, assign) SCNQuaternion orientationOffset;

/*!
 @property positionOffset
 @abstract Defines an addition orientation offset. Defaults to no offset. Animatable.
 */
@property(nonatomic, assign) SCNVector3 positionOffset;

/*!
 @property scaleOffset
 @abstract Defines an addition scale offset. Defaults to no offset. Animatable.
 */
@property(nonatomic, assign) SCNVector3 scaleOffset;

@end

// MARK: -

/*!
 @class SCNAccelerationConstraint
 @abstract A SCNAccelerationConstraint caps the acceleration and velocity of a node
 */
SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNAccelerationConstraint : SCNConstraint

/*!
 @method accelerationConstraint
 @abstract Creates and returns a SCNAccelerationConstraint object.
 */
+ (instancetype)accelerationConstraint;

/*!
 @property maximumLinearAcceleration
 @abstract Controls the maximum linear acceleration. Defaults to MAXFLOAT. Animatable.
 @discussion The maximum linear acceleration is in m.s^-2
 */
@property(nonatomic, assign) CGFloat maximumLinearAcceleration;

/*!
 @property maximumLinearVelocity
 @abstract Controls the maximum linear velocity. Defaults to MAXFLOAT. Animatable.
 @discussion The maximum linear velocity is in m.s
 */
@property(nonatomic, assign) CGFloat maximumLinearVelocity;

/*!
 @property decelerationDistance
 @abstract Controls the distance at which the node should start decelerating. Defaults to 0. Animatable.
 */
@property(nonatomic, assign) CGFloat decelerationDistance;

/*!
 @property damping
 @abstract Specifies the damping factor of the receiver. Optionally reduce the body's linear velocity each frame to simulate fluid/air friction. Value should be zero or greater. Defaults to 0.1. Animatable.
 */
@property(nonatomic, assign) CGFloat damping;

@end

// MARK: -

/*!
 @class SCNSliderConstraint
 @abstract A SCNSliderConstraint constraint makes a node to collide and slide against a category of nodes
 */
SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNSliderConstraint : SCNConstraint

/*!
 @method accelerationConstraint
 @abstract Creates and returns a SCNSliderConstraint object.
 */
+ (instancetype)sliderConstraint;

/*!
 @property collisionCategoryBitMask
 @abstract Defines the category of node to collide against. Defaults to 0.
 */
@property(nonatomic, assign) NSUInteger collisionCategoryBitMask;

/*!
 @property radius
 @abstract Defines the radius of the slider. Defaults to 1.
 */
@property(nonatomic, assign) CGFloat radius;

/*!
 @property offset
 @abstract Defines the offset of the slider. Defaults to (0,0,0). 
 */
@property(nonatomic, assign) SCNVector3 offset;

@end

// MARK: -

@class SCNAvoidOccluderConstraint;

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@protocol SCNAvoidOccluderConstraintDelegate <NSObject>
@optional
- (BOOL)avoidOccluderConstraint:(SCNAvoidOccluderConstraint *)constraint shouldAvoidOccluder:(SCNNode *)occluder forNode:(SCNNode *)node;
- (void)avoidOccluderConstraint:(SCNAvoidOccluderConstraint *)constraint didAvoidOccluder:(SCNNode *)occluder forNode:(SCNNode *)node;
@end

/*!
 @class SCNAvoidOccluderConstraint
 @abstract A SCNAvoidOccluderConstraint constraints place the receiver at a position that prevent nodes with the specified category to occlude the target.
 @discussion The target node and it's children are ignored as potential occluders.
 */
SCN_EXPORT API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface SCNAvoidOccluderConstraint : SCNConstraint

/*!
 @method avoidOccluderConstraintWithTarget
 @abstract Creates and returns a SCNAvoidOccluderConstraint object.
 */
+ (instancetype)avoidOccluderConstraintWithTarget:(nullable SCNNode *)target;

/*!
 @property delegate
 @abstract The receiver's delegate
 */
@property(nonatomic, assign) id <SCNAvoidOccluderConstraintDelegate> delegate;

/*!
 @property target
 @abstract Defines the target node
 */
@property(nonatomic, retain, nullable) SCNNode *target;

/*!
 @property occluderCategoryBitMask
 @abstract Defines the category of node to consider as occluder. Defaults to 1.
 */
@property(nonatomic, assign) NSUInteger occluderCategoryBitMask;

/*!
 @property bias
 @abstract Defines the bias the apply after moving the receiver to avoid occluders. Defaults to 10e-5.
 @discussion A positive bias will move the receiver closer to the target.
 */
@property(nonatomic, assign) CGFloat bias;

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNNode.h
//
//  SCNNode.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNBoundingVolume.h>
#import <SceneKit/SCNAction.h>
#import <AvailabilityMacros.h>

NS_ASSUME_NONNULL_BEGIN

@class CIFilter;
@class SCNLight;
@class SCNCamera;
@class SCNGeometry;
@class SCNSkinner;
@class SCNMorpher;
@class SCNConstraint;
@class SCNPhysicsBody;
@class SCNPhysicsField;
@class SCNPhysicsBody;
@class SCNHitTestResult;
@class SCNRenderer;
@protocol SCNNodeRendererDelegate;

/*! @group Rendering arguments
    @discussion These keys are used for the 'semantic' argument of -[SCNProgram setSemantic:forSymbol:options:]
                Transforms are SCNMatrix4 wrapped in NSValues.
 */
SCN_EXPORT NSString * const SCNModelTransform;
SCN_EXPORT NSString * const SCNViewTransform;
SCN_EXPORT NSString * const SCNProjectionTransform;
SCN_EXPORT NSString * const SCNNormalTransform;
SCN_EXPORT NSString * const SCNModelViewTransform;
SCN_EXPORT NSString * const SCNModelViewProjectionTransform;

/*! @enum SCNMovabilityHint
 @abstract The available modes of movability.
 @discussion Movable nodes are not captured when computing light probes.
 */
typedef NS_ENUM(NSInteger, SCNMovabilityHint) {
    SCNMovabilityHintFixed,
    SCNMovabilityHintMovable,
} API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*! @enum SCNNodeFocusBehavior
 @abstract Control the focus (UIFocus) behavior.
 */
typedef NS_ENUM(NSInteger, SCNNodeFocusBehavior) {
    SCNNodeFocusBehaviorNone = 0,    // Not focusable and node has no impact on other nodes that have focus interaction enabled.
    SCNNodeFocusBehaviorOccluding,   // Not focusable, but will prevent other focusable nodes that this node visually obscures from being focusable.
    SCNNodeFocusBehaviorFocusable    // Focusable and will also prevent other focusable nodes that this node visually obscures from being focusable.
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @class SCNNode
 @abstract SCNNode is the model class for node-tree objects.
 @discussion It encapsulates the position, rotations, and other transforms of a node, which define a coordinate system.
		     The coordinate systems of all the sub-nodes are relative to the one of their parent node.
 */
SCN_EXPORT
@interface SCNNode : NSObject <NSCopying, NSSecureCoding, SCNAnimatable, SCNActionable, SCNBoundingVolume, UIFocusItem>

#pragma mark - Creating a Node

/*! 
 @method node
 @abstract Creates and initializes a node instance.
 */
+ (instancetype)node;

/*! 
 @method nodeWithGeometry:
 @abstract Creates and initializes a node instance with the specified geometry attached.
 @param geometry The geometry to attach.
 */
+ (SCNNode *)nodeWithGeometry:(nullable SCNGeometry *)geometry;



#pragma mark - Copying the Node

/*!
 @method clone
 @abstract Returns a copy of the receiver. The returned instance is autoreleased.
 @discussion The copy is recursive: every child node will be cloned, too. For a non-recursive copy, use copy instead.
 The copied nodes will share their attached objects (light, geometry, camera, ...) with the original instances;
 if you want, for example, to change the materials of the copy independently of the original object, you'll
 have to copy the geometry of the node separately.
 */
- (instancetype)clone;

/*
 @method flattenedClone
 @abstract Returns a clone of the node containing a geometry that concatenates all the geometries contained in the node hierarchy.
 The returned clone is autoreleased.
 */
- (instancetype)flattenedClone API_AVAILABLE(macos(10.9));



#pragma mark - Managing the Node Attributes

/*!
 @property name
 @abstract Determines the name of the receiver.
 */
@property(nonatomic, copy, nullable) NSString *name;

/*!
 @property light
 @abstract Determines the light attached to the receiver.
 */
@property(nonatomic, retain, nullable) SCNLight *light;

/*!
 @property camera
 @abstract Determines the camera attached to the receiver.
 */

@property(nonatomic, retain, nullable) SCNCamera *camera;

/*!
 @property geometry
 @abstract Returns the geometry attached to the receiver.
 */
@property(nonatomic, retain, nullable) SCNGeometry *geometry;

/*!
 @property skinner
 @abstract Returns the skinner attached to the receiver.
 */
@property(nonatomic, retain, nullable) SCNSkinner *skinner API_AVAILABLE(macos(10.9));

/*!
 @property morpher
 @abstract Returns the morpher attached to the receiver.
 */
@property(nonatomic, retain, nullable) SCNMorpher *morpher API_AVAILABLE(macos(10.9));



#pragma mark - Modifying the Node′s Transform

/*! 
 @property transform
 @abstract Determines the receiver's transform. Animatable.
 @discussion The transform is the combination of the position, rotation and scale defined below. So when the transform is set, the receiver's position, rotation and scale are changed to match the new transform.
 */
@property(nonatomic) SCNMatrix4 transform;

/*!
 @property worldTransform
 @abstract Determines the receiver's transform in world space (relative to the scene's root node). Animatable.
 */
@property(nonatomic, readonly) SCNMatrix4 worldTransform;
- (void)setWorldTransform:(SCNMatrix4)worldTransform API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*! 
 @property position
 @abstract Determines the receiver's position. Animatable.
 */
@property(nonatomic) SCNVector3 position;

/*!
 @property worldPosition
 @abstract Determines the receiver's position in world space (relative to the scene's root node).
 */
@property(nonatomic) SCNVector3 worldPosition API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*! 
 @property rotation
 @abstract Determines the receiver's rotation. Animatable.
 @discussion The rotation is axis angle rotation. The three first components are the axis, the fourth one is the rotation (in radian).
 */
@property(nonatomic) SCNVector4 rotation;

/*!
 @property orientation
 @abstract Determines the receiver's orientation as a unit quaternion. Animatable.
 */
@property(nonatomic) SCNQuaternion orientation API_AVAILABLE(macos(10.10));

/*!
 @property worldOrientation
 @abstract Determines the receiver's orientation in world space (relative to the scene's root node). Animatable.
 */
@property(nonatomic) SCNQuaternion worldOrientation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));


/*!
 @property eulerAngles
 @abstract Determines the receiver's euler angles. Animatable.
 @dicussion The order of components in this vector matches the axes of rotation:
               1. Pitch (the x component) is the rotation about the node's x-axis (in radians)
               2. Yaw   (the y component) is the rotation about the node's y-axis (in radians)
               3. Roll  (the z component) is the rotation about the node's z-axis (in radians)
            SceneKit applies these rotations in the reverse order of the components:
               1. first roll
               2. then yaw
               3. then pitch
 */
@property(nonatomic) SCNVector3 eulerAngles API_AVAILABLE(macos(10.10));

/*! 
 @property scale
 @abstract Determines the receiver's scale. Animatable.
 */
@property(nonatomic) SCNVector3 scale;

/*! 
 @property pivot
 @abstract Determines the receiver's pivot. Animatable.
 */
@property(nonatomic) SCNMatrix4 pivot;

#pragma mark - Modifying the Node′s Visibility

/*! 
 @property hidden
 @abstract Determines whether the receiver is displayed. Defaults to NO. Animatable.
 */
@property(nonatomic, getter=isHidden) BOOL hidden;

/*! 
 @property opacity
 @abstract Determines the opacity of the receiver. Default is 1. Animatable.
 */
@property(nonatomic) CGFloat opacity;

/*!
 @property renderingOrder
 @abstract Determines the rendering order of the receiver.
 @discussion Nodes with greater rendering orders are rendered last. Defaults to 0.
 */
@property(nonatomic) NSInteger renderingOrder;

/*!
 @property castsShadow
 @abstract Determines if the node is rendered in shadow maps. Defaults to YES.
 */
@property(nonatomic) BOOL castsShadow API_AVAILABLE(macos(10.10));

/*!
 @property movabilityHint
 @abstract Communicates to SceneKit’s rendering system about how you want to move content in your scene; it does not affect your ability to change the node’s position or add animations or physics to the node. Defaults to SCNMovabilityHintFixed.
 */
@property(nonatomic) SCNMovabilityHint movabilityHint API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));


#pragma mark - Managing the Node Hierarchy

/*! 
 @property parentNode
 @abstract Returns the parent node of the receiver.
 */
@property(nonatomic, readonly, nullable) SCNNode *parentNode;

/*! 
 @property childNodes
 @abstract Returns the child node array of the receiver.
 */
@property(nonatomic, readonly) NSArray<SCNNode *> *childNodes;

/*!
 @method addChildNode:
 @abstract Appends the node to the receiver’s childNodes array.
 @param child The node to be added to the receiver’s childNodes array.
 */
- (void)addChildNode:(SCNNode *)child;

/*!
 @method insertChildNode:atIndex:
 @abstract Insert a node in the childNodes array at the specified index.
 @param child The node to insert.
 @param index Index in the childNodes array to insert the node.
 */
- (void)insertChildNode:(SCNNode *)child atIndex:(NSUInteger)index;

/*!
 @method removeFromParentNode
 @abstract Removes the node from the childNodes array of the receiver’s parentNode.
 */
- (void)removeFromParentNode;

/*!
 @method replaceChildNode:with:
 @abstract Remove `child' from the childNode array of the receiver and insert 'child2' if non-nil in its position.
 @discussion If the parentNode of `child' is not the receiver, the behavior is undefined.
 @param oldChild The node to replace in the childNodes array.
 @param newChild The new node that will replace the previous one.
 */
- (void)replaceChildNode:(SCNNode *)oldChild with:(SCNNode *)newChild;



#pragma mark - Searching the Node Hierarchy

/*!
 @method childNodeWithName:recursively:
 @abstract Returns the first node found in the node tree with the specified name.
 @discussion The search uses a pre-order tree traversal.
 @param name The name of the node you are searching for.
 @param recursively Set to YES if you want the search to look through the sub-nodes recursively.
 */
- (nullable SCNNode *)childNodeWithName:(NSString *)name recursively:(BOOL)recursively;

/*!
 @method childNodesPassingTest:
 @abstract Returns the child nodes of the receiver that passes a test in a given Block.
 @discussion The search is recursive and uses a pre-order tree traversal.
 @param predicate The block to apply to child nodes of the receiver. The block takes two arguments: "child" is a child node and "stop" is a reference to a Boolean value. The block can set the value to YES to stop further processing of the node hierarchy. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block. The Block returns a Boolean value that indicates whether "child" passed the test.
 */
- (NSArray<SCNNode *> *)childNodesPassingTest:(NS_NOESCAPE BOOL (^)(SCNNode *child, BOOL *stop))predicate;

/*!
 @method enumerateChildNodesUsingBlock:
 @abstract Executes a given block on each child node under the receiver.
 @discussion The search is recursive and uses a pre-order tree traversal.
 @param block The block to apply to child nodes of the receiver. The block takes two arguments: "child" is a child node and "stop" is a reference to a Boolean value. The block can set the value to YES to stop further processing of the node hierarchy. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 */
- (void)enumerateChildNodesUsingBlock:(NS_NOESCAPE void (^)(SCNNode *child, BOOL *stop))block API_AVAILABLE(macos(10.10));

/*!
 @method enumerateHierarchyUsingBlock:
 @abstract Executes a given block on the receiver and its child nodes.
 @discussion The search is recursive and uses a pre-order tree traversal.
 @param block The block to apply to the receiver and its child nodes. The block takes two arguments: "node" is a node in the hierarchy of the receiver (including the receiver) and "stop" is a reference to a Boolean value. The block can set the value to YES to stop further processing of the node hierarchy. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 */
- (void)enumerateHierarchyUsingBlock:(NS_NOESCAPE void (^)(SCNNode *node, BOOL *stop))block API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));


#pragma mark - Converting Between Node Coordinate Systems

/*!
 @method convertPosition:toNode:
 @abstract Converts a position from the receiver’s coordinate system to that of the specified node.
 @param position A position specified in the local coordinate system of the receiver.
 @param node The node into whose coordinate system "position" is to be converted. If "node" is nil, this method instead converts to world coordinates.
 */
- (SCNVector3)convertPosition:(SCNVector3)position toNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.9));

/*!
 @method convertPosition:fromNode:
 @abstract Converts a position from the coordinate system of a given node to that of the receiver.
 @param position A position specified in the local coordinate system of "node".
 @param node The node from whose coordinate system "position" is to be converted. If "node" is nil, this method instead converts from world coordinates.
 */
- (SCNVector3)convertPosition:(SCNVector3)position fromNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.9));


/**
 @abstract Converts a vector from the coordinate system of a given node to that of the receiver.

 @param vector A vector specified in the local coordinate system the receiver.
 @param node The node defining the space from which the vector should be transformed. If "node" is nil, this method instead converts from world coordinates.

 @return vector transformed from receiver local space to node local space.
 */
- (SCNVector3)convertVector:(SCNVector3)vector toNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));


/**
 @abstract Converts a vector from the coordinate system of a given node to that of the receiver.

 @param vector A vector specified in the local coordinate system of "node".
 @param node The node defining the space to which the vector should be transformed to. If "node" is nil, this method instead converts from world coordinates.

 @return vector transformed from node space to reveiver local space.
 */
- (SCNVector3)convertVector:(SCNVector3)vector fromNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));


/*!
 @method convertTransform:toNode:
 @abstract Converts a transform from the receiver’s coordinate system to that of the specified node.
 @param transform A transform specified in the local coordinate system of the receiver.
 @param node The node into whose coordinate system "transform" is to be converted. If "node" is nil, this method instead converts to world coordinates.
 */
- (SCNMatrix4)convertTransform:(SCNMatrix4)transform toNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.9));

/*!
 @method convertTransform:fromNode:
 @abstract Converts a transform from the coordinate system of a given node to that of the receiver.
 @param transform A transform specified in the local coordinate system of "node".
 @param node The node from whose coordinate system "transform" is to be converted. If "node" is nil, this method instead converts from world coordinates.
 */
- (SCNMatrix4)convertTransform:(SCNMatrix4)transform fromNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.9));


#pragma mark - Managing the SCNNode′s physics body

/*!
 @property physicsBody
 @abstract The description of the physics body of the receiver.
 @discussion Default is nil.
 */
@property(nonatomic, retain, nullable) SCNPhysicsBody *physicsBody API_AVAILABLE(macos(10.10));


#pragma mark - Managing the Node′s Physics Field

/*!
 @property physicsField
 @abstract The description of the physics field of the receiver.
 @discussion Default is nil.
 */
@property(nonatomic, retain, nullable) SCNPhysicsField *physicsField API_AVAILABLE(macos(10.10));


#pragma mark - Managing the Node′s Constraints

/*!
 @property constraints
 @abstract An array of SCNConstraint that are applied to the receiver.
 @discussion Adding or removing a constraint can be implicitly animated based on the current transaction.
 */
@property(copy, nullable) NSArray<SCNConstraint *> *constraints API_AVAILABLE(macos(10.9));


#pragma mark - Accessing the Node′s Filters

/*!
 @property filters
 @abstract An array of Core Image filters that are applied to the rendering of the receiver and its child nodes. Animatable.
 @discussion Defaults to nil. Filter properties should be modified by calling setValue:forKeyPath: on each node that the filter is attached to. If the inputs of the filter are modified directly after the filter is attached to a node, the behavior is undefined.
 */
@property(nonatomic, copy, nullable) NSArray<CIFilter *> *filters API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(watchos);


#pragma mark - Accessing the Presentation Node

/*!
 @property presentationNode
 @abstract Returns the presentation node.
 @discussion Returns a copy of the node containing all the properties as they were at the start of the current transaction, with any active animations applied.
             This gives a close approximation to the version of the node that is currently displayed.
             The effect of attempting to modify the returned node in any way is undefined. The returned node has no parent and no child nodes.
 */
@property(nonatomic, readonly) SCNNode *presentationNode;


#pragma mark - Pause

/*!
 @property paused
 @abstract Controls whether or not the node's actions and animations are updated or paused. Defaults to NO.
 */
@property(nonatomic, getter=isPaused) BOOL paused API_AVAILABLE(macos(10.10));


#pragma mark - Overriding the Rendering with Custom OpenGL Code

/*!
 @property rendererDelegate
 @abstract Specifies the receiver's renderer delegate object.
 @discussion Setting a renderer delegate prevents the SceneKit renderer from drawing the node and lets you use custom OpenGL code instead.
             The preferred way to customize the rendering is to tweak the material properties of the different materials of the node's geometry. SCNMaterial conforms to the SCNShadable protocol and allows for more advanced rendering using GLSL.
             You would typically use a renderer delegate with a node that has no geometry and only serves as a location in space. An example would be attaching a particle system to that node and render it with custom OpenGL code.
 */
@property(nonatomic, assign, nullable) id <SCNNodeRendererDelegate> rendererDelegate;



#pragma mark - Hit Testing in the Node

/*!
 @method hitTestWithSegmentFromPoint:toPoint:options:
 @abstract Returns an array of SCNHitTestResult for each node in the receiver's sub tree that intersects the specified segment.
 @param pointA The first point of the segment relative to the receiver.
 @param pointB The second point of the segment relative to the receiver.
 @param options Optional parameters (see the "Hit test options" section in SCNSceneRenderer.h for the available options).
 @discussion See SCNSceneRenderer.h for a screen-space hit testing method.
 */
- (NSArray<SCNHitTestResult *> *)hitTestWithSegmentFromPoint:(SCNVector3)pointA toPoint:(SCNVector3)pointB options:(nullable NSDictionary<NSString *, id> *)options API_AVAILABLE(macos(10.9));


#pragma mark - Categories

/*!
 @property categoryBitMask
 @abstract Defines what logical 'categories' the receiver belongs too. Defaults to 1.
 @discussion Categories can be used to
                1. exclude nodes from the influence of a given light (see SCNLight.categoryBitMask)
                2. include/exclude nodes from render passes (see SCNTechnique.h)
                3. specify which nodes to use when hit-testing (see SCNHitTestOptionCategoryBitMask)
 */
@property(nonatomic) NSUInteger categoryBitMask API_AVAILABLE(macos(10.10));

#pragma mark - UIFocus support

/*!
 @property focusBehavior
 @abstract Controls the behavior of the receiver regarding the UIFocus system. Defaults to SCNNodeFocusBehaviorNone.
 */
@property(nonatomic) SCNNodeFocusBehavior focusBehavior API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@end

@interface SCNNode (Transforms)

/*!
 @property localUp
 @abstract The local unit Y axis (0, 1, 0).
 */
@property(class, readonly, nonatomic) SCNVector3 localUp API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property localRight
 @abstract The local unit X axis (1, 0, 0).
 */
@property(class, readonly, nonatomic) SCNVector3 localRight API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property localFront
 @abstract The local unit -Z axis (0, 0, -1).
 */
@property(class, readonly, nonatomic) SCNVector3 localFront API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property worldUp
 @abstract The local unit Y axis (0, 1, 0) in world space.
 */
@property(readonly, nonatomic) SCNVector3 worldUp API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property worldRight
 @abstract The local unit X axis (1, 0, 0) in world space.
 */
@property(readonly, nonatomic) SCNVector3 worldRight API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property worldFront
 @abstract The local unit -Z axis (0, 0, -1) in world space.
 */
@property(readonly, nonatomic) SCNVector3 worldFront API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/**
 Convenience for calling lookAt:up:localFront: with worldUp set to `self.worldUp`
 and localFront [SCNNode localFront].
 @param worldTarget target position in world space.
 */
- (void)lookAt:(SCNVector3)worldTarget API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/**
 Set the orientation of the node so its front vector is pointing toward a given
 target. Using a reference up vector in world space and a front vector in
 local space.

 @param worldTarget position in world space.
 @param worldUp the up vector in world space.
 @param localFront the front vector in local space.
 */
- (void)lookAt:(SCNVector3)worldTarget up:(SCNVector3)worldUp localFront:(SCNVector3)localFront API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/**
 Translate the current node position along the given vector in local space.

 @param translation the translation in local space.
 */
- (void)localTranslateBy:(SCNVector3)translation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/**
 Apply a the given rotation to the current one.

 @param rotation rotation in local space.
 */
- (void)localRotateBy:(SCNQuaternion)rotation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/**
 Apply a rotation relative to a target point in parent space.

 @param worldRotation rotation to apply in world space.
 @param worldTarget position of the target in world space.
 */
- (void)rotateBy:(SCNQuaternion)worldRotation aroundTarget:(SCNVector3)worldTarget API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@end

/*!
 @category NSObject (SCNNodeRendererDelegate)
 @abstract The SCNNodeRendererDelegate protocol declares the methods that an instance of SCNNode invokes to let a delegate customize its rendering.
 */
@protocol SCNNodeRendererDelegate <NSObject>
@optional

/*! 
 @method renderNode:renderer:arguments:
 @abstract Invoked when a node is rendered.
 @discussion The preferred way to customize the rendering is to tweak the material properties of the different materials of the node's geometry. SCNMaterial conforms to the SCNShadable protocol and allows for more advanced rendering using GLSL.
             You would typically use a renderer delegate with a node that has no geometry and only serves as a location in space. An example would be attaching a particle system to that node and render it with custom OpenGL code.
             Only drawing calls and the means to achieve them are supposed to be performed during the renderer delegate callback, any changes in the model (nodes, geometry...) would involve unexpected results.
 @param node The node to render.
 @param renderer The scene renderer to render into.
 @param arguments A dictionary whose values are SCNMatrix4 matrices wrapped in NSValue objects.
 */
- (void)renderNode:(SCNNode *)node renderer:(SCNRenderer *)renderer arguments:(NSDictionary<NSString *, id> *)arguments;

@end

@interface SCNNode (SIMD)

/*!
 @abstract Determines the receiver's transform. Animatable.
 @discussion The transform is the combination of the position, rotation and scale defined below. So when the transform is set, the receiver's position, rotation and scale are changed to match the new transform.
 */
@property(nonatomic) simd_float4x4 simdTransform API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's position. Animatable.
 */
@property(nonatomic) simd_float3 simdPosition API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's rotation. Animatable.
 @discussion The rotation is axis angle rotation. The three first components are the axis, the fourth one is the rotation (in radian).
 */
@property(nonatomic) simd_float4 simdRotation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's orientation as a unit quaternion. Animatable.
 */
@property(nonatomic) simd_quatf simdOrientation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's euler angles. Animatable.
 @dicussion The order of components in this vector matches the axes of rotation:
 1. Pitch (the x component) is the rotation about the node's x-axis (in radians)
 2. Yaw   (the y component) is the rotation about the node's y-axis (in radians)
 3. Roll  (the z component) is the rotation about the node's z-axis (in radians)
 SceneKit applies these rotations in the reverse order of the components:
 1. first roll
 2. then yaw
 3. then pitch
 */
@property(nonatomic) simd_float3 simdEulerAngles API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's scale. Animatable.
 */
@property(nonatomic) simd_float3 simdScale API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's pivot. Animatable.
 */
@property(nonatomic) simd_float4x4 simdPivot API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's position in world space (relative to the scene's root node).
 */
@property(nonatomic) simd_float3 simdWorldPosition API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's orientation in world space (relative to the scene's root node). Animatable.
 */
@property(nonatomic) simd_quatf simdWorldOrientation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @abstract Determines the receiver's transform in world space (relative to the scene's root node). Animatable.
 */
@property(nonatomic) simd_float4x4 simdWorldTransform API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

- (simd_float3)simdConvertPosition:(simd_float3)position toNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
- (simd_float3)simdConvertPosition:(simd_float3)position fromNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

- (simd_float3)simdConvertVector:(simd_float3)vector toNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
- (simd_float3)simdConvertVector:(simd_float3)vector fromNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

- (simd_float4x4)simdConvertTransform:(simd_float4x4)transform toNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
- (simd_float4x4)simdConvertTransform:(simd_float4x4)transform fromNode:(nullable SCNNode *)node API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@property(class, readonly, nonatomic) simd_float3 simdLocalUp API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
@property(class, readonly, nonatomic) simd_float3 simdLocalRight API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
@property(class, readonly, nonatomic) simd_float3 simdLocalFront API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@property(readonly, nonatomic) simd_float3 simdWorldUp API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
@property(readonly, nonatomic) simd_float3 simdWorldRight API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
@property(readonly, nonatomic) simd_float3 simdWorldFront API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

- (void)simdLookAt:(simd_float3)worldTarget API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
- (void)simdLookAt:(simd_float3)worldTarget up:(simd_float3)worldUp localFront:(simd_float3)localFront API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
- (void)simdLocalTranslateBy:(simd_float3)translation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

- (void)simdLocalRotateBy:(simd_quatf)rotation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
- (void)simdRotateBy:(simd_quatf)worldRotation aroundTarget:(simd_float3)worldTarget API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNSceneSource.h
//
//  SCNSceneSource.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNScene;

/*! @group Scene source properties */
/*! File contributors. The values are dictionaries populated with keys documented in the "Contributor dictionary keys" group. */
SCN_EXPORT NSString * const SCNSceneSourceAssetContributorsKey;
/*! When the file was created. The value is a NSDate instance. */
SCN_EXPORT NSString * const SCNSceneSourceAssetCreatedDateKey;
/*! When the file was last modified. The value is a NSDate instance. */
SCN_EXPORT NSString * const SCNSceneSourceAssetModifiedDateKey;
/*! The up axis of the file. If the file is oriented Y-up, for example, then this is the string \@"0.0 1.0 0.0" */
SCN_EXPORT NSString * const SCNSceneSourceAssetUpAxisKey;
/*! The unit used in the file. The value is a dictionary populated with keys documented in the "Unit dictionary keys" group. */
SCN_EXPORT NSString * const SCNSceneSourceAssetUnitKey;

/*! @group Contributor dictionary keys */
/*! Authoring tool used to create the file. The corresponding value is an NSString. */
SCN_EXPORT NSString * const SCNSceneSourceAssetAuthoringToolKey;
/*! The file's author. The corresponding value is an NSString. */
SCN_EXPORT NSString * const SCNSceneSourceAssetAuthorKey;

/*! @group Unit dictionary keys */
/*! The name (NSString) of the unit */
SCN_EXPORT NSString * const SCNSceneSourceAssetUnitNameKey;
/*! A NSNumber encapsulating a floating-point value indicating how many meters the unit is. For example, if the name is \@"centimeter", then this will be 0.01. */
SCN_EXPORT NSString * const SCNSceneSourceAssetUnitMeterKey;

/*! @group Scene loading options */
typedef NSString * SCNSceneSourceLoadingOption NS_STRING_ENUM;

/*! @constant SCNSceneSourceCreateNormalsIfAbsentKey
	@abstract Enable to try to guess acceptable normals for the vertices if none are given in the file
    @discussion Use this with a boolean value encapsulated in a NSNumber. The default value is NO.
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceCreateNormalsIfAbsentKey;

/*!
 @constant SCNSceneSourceCheckConsistencyKey
 @abstract Pass YES in order to perform the document validation. 
 @discussion This option can be set in the options dictionary of the SCNScene and SCNSceneSource loading methods.
 The value for this option should be a boolean NSNumber. If its boolean value is YES (the default is NO),
 SceneKit will attempt to check the document for consistency.
 If the document doesn't pass the consistency check it is then not loaded and an error is returned.
 This is slower, but for security reasons it should be set to YES if you are not sure the files you load are valid and have not been tampered with. 
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceCheckConsistencyKey;

/*!
 @constant SCNSceneSourceFlattenSceneKey
 @abstract Pass YES to flatten the scene graph when possible.
 @discussion This option can be set in the options dictionary of the SCNScene and SCNSceneSource loading methods.
 The value for this option should be a boolean NSNumber. If its boolean value is YES (the default is NO),
 SceneKit will attempt to reduce the scene graph by merging the geometries.
 This option is suitable to preview a 3D scene efficiently and when manipulating the scene graph is not needed.
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceFlattenSceneKey;

/*!
 @constant SCNSceneSourceUseSafeModeKey
 @abstract Pass YES in order to enable the safe mode.
 @discussion This option can be set in the options dictionary of the SCNScene and SCNSceneSource loading methods.
 The value for this option should be a boolean NSNumber. If its boolean value is YES (the default is NO),
 SceneKit will forbid network accesses, prevent the loading of resources from arbitrary directories, and will not execute
 any code present in the loaded files.
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceUseSafeModeKey API_DEPRECATED("No longer supported", macos(10.8, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @constant SCNSceneSourceAssetDirectoryURLsKey
 @abstract Pass an array of directory URLs where SceneKit should look for resources
 @discussion By default, SceneKit will look for the external resources it cannot find in the parent directory of the imported file.
 You can add additional directories by setting an array of URLs for this key when calling sceneWithOptions:error:.
 This is recommended if you want to construct your scene source from a data object, not from an URL,
 and need to load resources whose paths are not absolute.
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceAssetDirectoryURLsKey;

/*!
 @constant SCNSceneSourceOverrideAssetURLsKey
 @abstract Pass YES in order to override assets URLs with the directory URLs passed via SCNSceneSourceAssetDirectoryURLsKey.
 @discussion By default, SceneKit will look for the external resources using the paths/urls as described in the imported file.
 You can force SceneKit to only search for extern resources within the directories specified by the SCNSceneSourceAssetDirectoryURLsKey key.
 This can be useful to load a file and its resources from a specific bundle for instance.
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceOverrideAssetURLsKey;

/*!
 @constant SCNSceneSourceStrictConformanceKey
 @abstract Pass YES to interpret the 3D format of the file in a strict way.
 @discussion This option defaults to NO. In this case SceneKit will try to read any additional metadata present in the file to
			 enable additional features and make the rendering as close as possible to the original intent. If you pass YES,
             SceneKit will instead only consider features which are part of the file format specification.
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceStrictConformanceKey;

/*!
 @constant SCNSceneSourceConvertUnitsToMetersKey
 @abstract Pass the units you want the scene to be converted to (in meter).
 @discussion Use this with a floating value encapsulated in a NSNumber. The default value is nil which means no conversion done. Passing a non-zero value will convert the scene coordinates so that 1 unit corresponds to N meters. For example pass 0.01 for 1 unit == 1 centimeter, pass 0.3048 for 1 unit == 1 foot...
     For better physics simulation it is recommended to use 1 unit equals to 1 meter.
     This option has no effect for SCN files or if the asset is already compressed by Xcode (use the compression options instead).
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceConvertUnitsToMetersKey API_AVAILABLE(macos(10.10), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @constant SCNSceneSourceConvertToYUpKey
 @abstract Pass YES if a scene should be converted to Y up if it currently has a different up axis.
 @discussion Use this with a boolean value encapsulated in a NSNumber. The default value is NO.
 This option has no effect for SCN files or if the asset is already compressed by Xcode (use the compression options instead).
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceConvertToYUpKey API_AVAILABLE(macos(10.10), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @constant SCNSceneSourceAnimationImportPolicyKey
 @abstract Pass one of the value below to specify what to do with loaded animations.
 @discussion See below for the description of each individual key. Defaults to SCNSceneSourceAnimationImportPolicyPlayRepeatedly. On 10.9 and before the behavior is SCNSceneSourceAnimationImportPolicyPlayUsingSceneTimeBase. For compatibility reason if the application was built on 10.9 or before the default behavior is SCNSceneSourceAnimationImportPolicyPlayUsingSceneTimeBase.
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceAnimationImportPolicyKey API_AVAILABLE(macos(10.10));

/*!
 @constant SCNSceneSourceLoadingOptionPreserveOriginalTopology
 @abstract Pass YES to make SceneKit preserve the original topology instead of triangulating at load time.
 This can be useful to get better results when subdividing a geometry. Defaults to NO.
 */
SCN_EXPORT SCNSceneSourceLoadingOption const SCNSceneSourceLoadingOptionPreserveOriginalTopology API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

#define SCNSceneSourceLoadingOptionCreateNormalsIfAbsent    SCNSceneSourceCreateNormalsIfAbsentKey
#define SCNSceneSourceLoadingOptionCheckConsistency         SCNSceneSourceCheckConsistencyKey
#define SCNSceneSourceLoadingOptionFlattenScene             SCNSceneSourceFlattenSceneKey
#define SCNSceneSourceLoadingOptionUseSafeMode              SCNSceneSourceUseSafeModeKey
#define SCNSceneSourceLoadingOptionAssetDirectoryURLs       SCNSceneSourceAssetDirectoryURLsKey
#define SCNSceneSourceLoadingOptionOverrideAssetURLs        SCNSceneSourceOverrideAssetURLsKey
#define SCNSceneSourceLoadingOptionStrictConformance        SCNSceneSourceStrictConformanceKey
#define SCNSceneSourceLoadingOptionConvertUnitsToMeters     SCNSceneSourceConvertUnitsToMetersKey
#define SCNSceneSourceLoadingOptionConvertToYUp             SCNSceneSourceConvertToYUpKey
#define SCNSceneSourceLoadingOptionAnimationImportPolicy    SCNSceneSourceAnimationImportPolicyKey

/* Values for SCNSceneSourceLoadingOptionAnimationImportPolicy */
typedef NSString * SCNSceneSourceAnimationImportPolicy NS_STRING_ENUM;

/*!
 @constant SCNSceneSourceAnimationImportPolicyPlay
 @abstract Add animations to the scene and play them once (repeatCount set to 1).
 */
SCN_EXPORT SCNSceneSourceAnimationImportPolicy const SCNSceneSourceAnimationImportPolicyPlay API_AVAILABLE(macos(10.10));

/*!
 @constant SCNSceneSourceAnimationImportPolicyPlayRepeatedly
 @abstract Add animations to the scene and play them repeatedly (repeatCount set to infinity).
 */
SCN_EXPORT SCNSceneSourceAnimationImportPolicy const SCNSceneSourceAnimationImportPolicyPlayRepeatedly API_AVAILABLE(macos(10.10));

/*!
 @constant SCNSceneSourceAnimationImportPolicyDoNotPlay
 @abstract Only keep animations in the SCNSceneSource and don't add to the animatable elements of the scene.
 */
SCN_EXPORT SCNSceneSourceAnimationImportPolicy const SCNSceneSourceAnimationImportPolicyDoNotPlay API_AVAILABLE(macos(10.10));

/*!
 @constant SCNSceneSourceAnimationImportPolicyPlayUsingSceneTimeBase
 @abstract Add animations to the scene and play them using the SCNView/SCNRenderer's scene time (usesSceneTimeBase set to YES)
 */
SCN_EXPORT SCNSceneSourceAnimationImportPolicy const SCNSceneSourceAnimationImportPolicyPlayUsingSceneTimeBase API_AVAILABLE(macos(10.10));


/*!
 @constant SCNDetailedErrorsKey
 @abstract Key to access the detailed validation errors.
 @discussion This key will be present in the user info dictionary of errors created by the various sceneWithOptions: methods.
             When present, the value associated with it is an array of detailed errors found by the consistency checker
             which represent consistency errors in the 3D file. Some metadata about these detailed errors is available
             in their user info dictionary using the other keys (SCNConsistency*) defined in this file.
 */

SCN_EXPORT NSString * const SCNDetailedErrorsKey;

/*!
 @constant SCNConsistencyElementIDErrorKey
 @abstract For XML-based formats, the ID of the element where the error occurred.
 @discussion When the element does not have an ID, the ID of the closest parent element which has one is returned.
 */

SCN_EXPORT NSString * const SCNConsistencyElementIDErrorKey;

/*!
 @constant SCNConsistencyElementTypeErrorKey
 @abstract For XML-based formats, the tag name of the element where the error occurred.
 */

SCN_EXPORT NSString * const SCNConsistencyElementTypeErrorKey;

/*!
 @constant SCNConsistencyLineNumberErrorKey
 @abstract For text-based formats, the line number where an error occurred.
 */

SCN_EXPORT NSString * const SCNConsistencyLineNumberErrorKey;

/*!
 @enum SCNConsistencyErrorCode
 @abstract Error codes returned by the consistency checker
 @discussion Each of the detailed errors found in the master error's SCNDetailedErrorsKey, when present, will have an error
             code in this enumeration and some additional metadata associated with the SCNConsistency* keys.
 */
enum {
	SCNConsistencyInvalidURIError = 1000,
	SCNConsistencyInvalidCountError,
	SCNConsistencyInvalidArgumentError,
	SCNConsistencyMissingElementError,
	SCNConsistencyMissingAttributeError,
	SCNConsistencyXMLSchemaValidationError,
};

/*!
 @enum SCNSceneSourceStatus
 @abstract Represents a phase of the loading process.
 @discussion Each of these constants (except SCNSceneSourceStatusError) represents a phase of the loading process. "Parsing" means that the document is being deserialized, "validating" that it's being checked for consistency, "processing" that the resulting object is being loaded. New values might be added to this enumeration to make it more detailed; however the values will always be ordered in the same order as the corresponding phases are executed.
 */
typedef NS_ENUM(NSInteger, SCNSceneSourceStatus) {
	SCNSceneSourceStatusError      = -1,
	SCNSceneSourceStatusParsing    = 4,
	SCNSceneSourceStatusValidating = 8,
	SCNSceneSourceStatusProcessing = 12,
	SCNSceneSourceStatusComplete   = 16
};

typedef void (^SCNSceneSourceStatusHandler)(float totalProgress, SCNSceneSourceStatus status, NSError * _Nullable error, BOOL *stop);


/*!
 @class SCNSceneSource
 @abstract SCNSceneSource objects, abstract the data-reading task. A scene source can read scene data from a URL or a NSData object.
 After creating a SCNSceneSource object for the appropriate source, you can obtain scenes using SCNSceneSource methods.
 */

SCN_EXPORT
@interface SCNSceneSource : NSObject 

/*!
 @method sceneSourceWithURL:options:
 @abstract Creates and initialize a SCNSceneSource instance.
 @param url The URL to read scenes from.
 @param options An optional dictionary for future extensions. 
 */
+ (nullable instancetype)sceneSourceWithURL:(NSURL *)url options:(nullable NSDictionary<SCNSceneSourceLoadingOption, id> *)options;

/*!
 @method sceneSourceWithData:options:
 @abstract Creates and initialize a SCNSceneSource instance.
 @param data The scene data.
 @param options An optional dictionary for future extensions. 
 */
+ (nullable instancetype)sceneSourceWithData:(NSData *)data options:(nullable NSDictionary<SCNSceneSourceLoadingOption, id> *)options;

/*!
 @method initWithURL:options:
 @abstract Initialize a SCNSceneSource instance from a URL.
 @param url The URL to read scenes from.
 @param options An optional dictionary for future extensions. 
 */
- (nullable instancetype)initWithURL:(NSURL *)url options:(nullable NSDictionary<SCNSceneSourceLoadingOption, id> *)options;

/*!
 @method initWithData:options:
 @abstract Initialize a SCNSceneSource instance from a NSData object.
 @param data The data to read scenes from.
 @param options An optional dictionary for future extensions. 
 */
- (nullable instancetype)initWithData:(NSData *)data options:(nullable NSDictionary<SCNSceneSourceLoadingOption, id> *)options;

/*!
 @property url
 @abstract The receiver's URL (if any).
 */
@property(readonly, nullable) NSURL *url;

/*!
 @property data
 @abstract The receiver's data (if any).
 */
@property(readonly, nullable) NSData *data;

/*!
 @method sceneWithOptions:statusHandler:
 @abstract Creates and initializes the scene described in the 3D file with the specified options and lets you monitor the progress.
 @param options A dictionary of options. The valid keys are described in the "Scene loading options" section.
 @param statusHandler This block will be called repeatedly while the scene is being loaded.
                      - The first argument, overallProgress, is a floating-point number between 0 and 1. 0 means the loading process has just started and 1 that it is complete.
					  - The second argument, status, tells you what the source is currently doing. It takes one of the values in the SCNSceneSourceStatus enum. New values might be added to this enum in the future.
					  - If status == SCNSceneStatusError, then error will contain more information about the failure, and the method will return nil after having called the block. Otherwise error will be nil.
					  - Set *stop to YES if you want the source to abort the loading operation.
 */
- (nullable SCNScene *)sceneWithOptions:(nullable NSDictionary<SCNSceneSourceLoadingOption, id> *)options statusHandler:(nullable SCNSceneSourceStatusHandler)statusHandler;

/*!
 @method sceneWithOptions:error:
 @abstract Creates and initializes the scene described in the 3D file with the specified options.
 @param options A dictionary of options. The valid keys are described in the "Scene loading options" section.
 @param error If this method returns nil, an error providing more information is returned by reference.
 @discussion This simpler version is equivalent to providing a block to sceneWithOptions:statusHandler: and checking the "error"
 parameter of the block if the status is SCNSceneStatusError.
 */
- (nullable SCNScene *)sceneWithOptions:(nullable NSDictionary<SCNSceneSourceLoadingOption, id> *)options error:(NSError **)error;

/*!
 @method propertyForKey:
 @param key The key for which to return the corresponding property.
 @abstract Returns the property as defined in the 3D file for the given key. See keys above.
 */
- (nullable id)propertyForKey:(NSString *)key;

/*!
 @method entryWithIdentifier:classType:
 @abstract Returns the instance of "entryClass" found in the receiver's library with the id "uid".
 @param uid The id of the entry to find as specified in the source file
 @param entryClass Specifies the type of the object to be returned. It can be one of the following classes: SCNMaterial, SCNGeometry, SCNScene, SCNNode, CAAnimation, SCNLight, SCNCamera, SCNSkinner, SCNMorpher, NSImage
 @discussion Returns NULL if the receiver's library doesn't contains such an uid for the specified type.
 */
- (nullable id)entryWithIdentifier:(NSString *)uid withClass:(Class)entryClass NS_REFINED_FOR_SWIFT;

/*!
 @method identifiersOfEntriesWithClass:
 @abstract Returns the IDs found in the receiver's library for the class "entryClass".
 @param entryClass Specifies the type of the object referenced by the returned IDs. It can be one of the following classes: SCNMaterial, SCNScene, SCNGeometry, SCNNode, CAAnimation, SCNLight, SCNCamera, SCNSkinner, SCNMorpher, NSImage
 */
- (NSArray<NSString *> *)identifiersOfEntriesWithClass:(Class)entryClass;

/*!
 @method entriesPassingTest:
 @abstract Returns the entries in the receiver's library that pass a test in a given Block.
 @param predicate The block to apply to entries in the library. The block takes three arguments: "entry" is an entry in the library, "identifier" is the ID of this entry and "stop" is a reference to a Boolean value. The block can set the value to YES to stop further processing of the library. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block. The Block returns a Boolean value that indicates whether "entry" passed the test.
 @discussion The entry is an instance of one of following classes: SCNMaterial, SCNScene, SCNGeometry, SCNNode, CAAnimation, SCNLight, SCNCamera, SCNSkinner, SCNMorpher, NSImage.
 */
- (NSArray<id> *)entriesPassingTest:(NS_NOESCAPE BOOL (^)(id entry, NSString *identifier, BOOL *stop))predicate API_AVAILABLE(macos(10.9));

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNView.h
//
//  SCNView.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <SceneKit/SCNSceneRenderer.h>
#import <SceneKit/SCNTechnique.h>

@class SCNCameraController;

NS_ASSUME_NONNULL_BEGIN

typedef NSString * SCNViewOption NS_STRING_ENUM;

/*!
 @constant SCNViewOptionPreferredRenderingAPI Specifies the preferred rendering API to be used by the renderer.
 @discussion Pass it as the key in the options dictionary given to initWithFrame:options:. The value is a NSNumber wrapping a SCNRenderingAPI. You can also select the preferred rendering API directly from the SCNView inspector in InterfaceBuilder.
 */
SCN_EXPORT SCNViewOption const SCNPreferredRenderingAPIKey API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos);

/*!
 @constant SCNViewOptionPreferredDevice Specifies the preferred metal device to be used by the renderer.
 @discussion The value is directly a id <MTLDevice>.
 */
SCN_EXPORT SCNViewOption const SCNPreferredDeviceKey API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @constant SCNViewOptionPreferLowPowerDevice Specifies if the renderer should prefer a low power metal device.
 @discussion The value is a NSNumber wrapping a BOOL. Defaults to NO.
 */
SCN_EXPORT SCNViewOption const SCNPreferLowPowerDeviceKey API_AVAILABLE(macos(10.11), ios(9.0));

#define SCNViewOptionPreferredRenderingAPI SCNPreferredRenderingAPIKey
#define SCNViewOptionPreferredDevice       SCNPreferredDeviceKey
#define SCNViewOptionPreferLowPowerDevice  SCNPreferLowPowerDeviceKey

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@protocol SCNCameraControlConfiguration <NSObject>

@property(nonatomic, assign) BOOL autoSwitchToFreeCamera;
@property(nonatomic, assign) BOOL allowsTranslation;
@property(nonatomic, assign) CGFloat flyModeVelocity; // in m/s
@property(nonatomic, assign) CGFloat panSensitivity;
@property(nonatomic, assign) CGFloat truckSensitivity;
@property(nonatomic, assign) CGFloat rotationSensitivity;

@end

/*!
 @class SCNView
 @abstract A SCNView is a subclass of NSView that can display a SCNScene
 */
API_UNAVAILABLE(watchos)
SCN_EXPORT
@interface SCNView : UIView <SCNSceneRenderer, SCNTechniqueSupport>

/*! 
 @method initWithFrame:options:
 @abstract Initializes and returns a newly allocated SCNView object with a specified frame rectangle.
 @param frame The frame rectangle for the created view object.
 @param options An optional dictionary. See "View initialization options" above.
 */
- (instancetype)initWithFrame:(CGRect)frame options:(nullable NSDictionary<NSString *, id> *)options;

/*! 
 @property scene
 @abstract Specifies the scene of the receiver
 */
@property(nonatomic, retain, nullable) SCNScene *scene;

/*!
 @property rendersContinuously
 @abstract When set to YES, the view continously redraw at the display link frame rate. When set to NO the view will only redraw when something change or animates in the receiver's scene. Defaults to NO.
 */
@property(nonatomic, assign) BOOL rendersContinuously;


/*! 
 @property allowsCameraControl
 @abstract A Boolean value that determines whether the user can manipulate the point of view used to render the scene. 
 @discussion  When set to YES, a defaultCameraController is created and the view will handle UI events to pilot it so the user can manipulate the current point of view with the mouse or the trackpad. The scene graph and existing cameras won't be modified by this action. The default value of this property is NO.
     Note that the default event handling provided by the view may not suite your needs. You may want to implement you own evnet handler.
     The built-in camera controller let you:
       - pan with 1 finger to rotate the camera around the scene.
       - pan with 2 fingers to translate the camera on its local X,Y plan.
       - pan with 3 fingers vertically to move the the camera forward/backward.
       - double tap to switch to the next camera in the scene.
       - rotate with two fingers to roll the camera (rotation on the Z axis).
       - pinch to zoom-in / zoom-out (change the fov of the camera).
 */
@property(nonatomic) BOOL allowsCameraControl;

/*! 
 @property cameraControlConfiguration
 @abstract An object describing the current configuration of the event handler which pilot the default camera controller.
 @discussion This object will be used to configure the event handler when allowCameraControl is set to YES.
 */
@property(nonatomic, readonly) id <SCNCameraControlConfiguration> cameraControlConfiguration API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property defaultCameraController
 @abstract Returns the default SCNCameraController used to drive the current point of view when allowCameraController is set to YES.
 */
@property(nonnull, nonatomic, readonly) SCNCameraController* defaultCameraController API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property snapshot
 @abstract Draws the contents of the view and returns them as a new image object
 @discussion This method is thread-safe and may be called at any time.
 */
- (UIImage *)snapshot API_AVAILABLE(macos(10.10));

/*!
 @method play:
 @abstract This action method begins playing the scene at its current location.
 @param sender The object (such as a button or menu item) sending the message to play the scene.
 @discussion This method does not do anything if the scene is already playing.
 */
- (IBAction)play:(nullable id)sender;

/*! 
 @method pause:
 @abstract This action method pauses the scene playback.
 @param sender The object (such as a button or menu item) sending the message to pause the scene.
 @discussion This method does not do anything if the scene is already paused.
 */
- (IBAction)pause:(nullable id)sender;

/*! 
 @method stop:
 @abstract This action method stops the scene playback and resets the current time to the start time of the scene.
 @param sender The object (such as a button or menu item) sending the message to stop playing the scene.
 */
- (IBAction)stop:(nullable id)sender;

/*!
 @property preferredFramesPerSecond
 @abstract The rate you want the view to redraw its contents.
 @discussion When your application sets its preferred frame rate, the view chooses a frame rate as close to that as possible based on the capabilities of the screen the view is displayed on. The actual frame rate chosen is usually a factor of the maximum refresh rate of the screen to provide a consistent frame rate. For example, if the maximum refresh rate of the screen is 60 frames per second, that is also the highest frame rate the view sets as the actual frame rate. However, if you ask for a lower frame rate, it might choose 30, 20, 15 or some other factor to be the actual frame rate. Your application should choose a frame rate that it can consistently maintain.
     The default value is 0 which means the display link will fire at the native cadence of the display hardware.
 */
@property(nonatomic) NSInteger preferredFramesPerSecond API_AVAILABLE(macos(10.12));

/*!
 @property eaglContext
 @abstract Specifies the EAGL context associated with the receiver.
 @discussion This property returns nil and has no effect if the current API is Metal.
 */
@property(nonatomic, retain, nullable) EAGLContext *eaglContext;

/*!
 @property antialiasingMode
 @abstract Defaults to SCNAntialiasingModeMultisampling4X on macOS and SCNAntialiasingModeNone on iOS.
 */
@property(nonatomic) SCNAntialiasingMode antialiasingMode API_AVAILABLE(macos(10.10));



@end

NS_ASSUME_NONNULL_END
