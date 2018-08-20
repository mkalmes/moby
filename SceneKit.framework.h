// ==========  SceneKit.framework/Headers/SCNPhysicsWorld.h
//
//  SCNPhysicsWorld.h
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

@class SCNPhysicsContact;
@class SCNPhysicsBehavior;

//Keys for ray, contact and sweep tests
SCN_EXTERN NSString * const SCNPhysicsTestCollisionBitMaskKey NS_AVAILABLE(10_10, 8_0); //Allows to filter the objects tested by rayTest, contactTest and convexSweep. Default is SCNPhysicsCollisionCategoryAll
SCN_EXTERN NSString * const SCNPhysicsTestSearchModeKey NS_AVAILABLE(10_10, 8_0);       //Specifies how to perform the ray/contact/sweep test. Values are defined below. If not defined, then defaults to SCNPhysicsTestSearchModeAny
SCN_EXTERN NSString * const SCNPhysicsTestBackfaceCullingKey NS_AVAILABLE(10_10, 8_0);  //Specifies whether the back faces should be ignored or not. Defaults to YES.

//Values for SCNPhysicsTestSearchModeKey
SCN_EXTERN NSString * const SCNPhysicsTestSearchModeAny NS_AVAILABLE(10_10, 8_0);       //Returns the first contact found.
SCN_EXTERN NSString * const SCNPhysicsTestSearchModeClosest NS_AVAILABLE(10_10, 8_0);   //Returns the nearest contact found only.
SCN_EXTERN NSString * const SCNPhysicsTestSearchModeAll NS_AVAILABLE(10_10, 8_0);       //All contacts are returned.

/*!
 @protocol SCNPhysicsContactDelegate
 @abstract The SCNPhysicsContactDelegate protocol is to be implemented by delegates that want to be notified when a contact occured.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
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
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface SCNPhysicsWorld : NSObject <NSSecureCoding>

//A global 3D vector specifying the field force acceleration due to gravity. The unit is meter per second. Default is {0, -9.8, 0}.
@property(nonatomic) SCNVector3 gravity;

//A speed multiplier applied to the physics simulation. Default is 1.0.
//The speed can be reduced to slowdown the simulation, but beware that increasing the speed factor will decrease the accuracy of the simulation.
@property(nonatomic) CGFloat speed;

//The time step of the physics simulation. Default is 1/60s (60 Hz).
@property(nonatomic) NSTimeInterval timeStep;

//A delegate that is called when two physic bodies come in contact with each other.
@property(atomic, assign, nullable) id <SCNPhysicsContactDelegate> contactDelegate;

//Behaviors management
- (void)addBehavior:(SCNPhysicsBehavior *)behavior;
- (void)removeBehavior:(SCNPhysicsBehavior *)behavior;
- (void)removeAllBehaviors;
@property(nonatomic, readonly) NSArray<SCNPhysicsBehavior *> *allBehaviors;

//Performs a ray test on the physics bodies and their physics shapes.
- (NSArray<SCNHitTestResult *> *)rayTestWithSegmentFromPoint:(SCNVector3)origin toPoint:(SCNVector3)dest options:(nullable NSDictionary<NSString *, id> *)options;

//The methods below perform contact tests.
- (NSArray<SCNPhysicsContact *> *)contactTestBetweenBody:(SCNPhysicsBody *)bodyA andBody:(SCNPhysicsBody *)bodyB options:(nullable NSDictionary<NSString *, id> *)options;
- (NSArray<SCNPhysicsContact *> *)contactTestWithBody:(SCNPhysicsBody *)body options:(nullable NSDictionary<NSString *, id> *)options;
- (NSArray<SCNPhysicsContact *> *)convexSweepTestWithShape:(SCNPhysicsShape *)shape fromTransform:(SCNMatrix4)from toTransform:(SCNMatrix4)to options:(nullable NSDictionary<NSString *, id> *)options;

//Force the physics engine to re-evaluate collisions.
//This needs to be called if kinematic are moved and the contacts are wanted before the next simulation step.
- (void)updateCollisionPairs;

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNParticleSystem.h
//
//  SCNParticleSystem.h
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNGeometry;

// Particle Properties Name
SCN_EXTERN NSString * const SCNParticlePropertyPosition NS_AVAILABLE(10_10, 8_0);        // float3 : {x,y,z}     controller animation type : {NSValue(SCNVector3)}
SCN_EXTERN NSString * const SCNParticlePropertyAngle NS_AVAILABLE(10_10, 8_0);           // float                controller animation type : {NSNumber}
SCN_EXTERN NSString * const SCNParticlePropertyRotationAxis NS_AVAILABLE(10_10, 8_0);    // float3 : {x,y,z}     controller animation type : {NSValue(SCNVector3)}
SCN_EXTERN NSString * const SCNParticlePropertyVelocity NS_AVAILABLE(10_10, 8_0);        // float3 : {x,y,z}     controller animation type : {NSValue(SCNVector3)}
SCN_EXTERN NSString * const SCNParticlePropertyAngularVelocity NS_AVAILABLE(10_10, 8_0); // float                controller animation type : {NSNumber}
SCN_EXTERN NSString * const SCNParticlePropertyLife NS_AVAILABLE(10_10, 8_0);            // float                not controllable
SCN_EXTERN NSString * const SCNParticlePropertyColor NS_AVAILABLE(10_10, 8_0);           // float4 : {r,g,b,a}   controller animation type : {UIColor}
SCN_EXTERN NSString * const SCNParticlePropertyOpacity NS_AVAILABLE(10_10, 8_0);         // float                controller animation type : {NSNumber}
SCN_EXTERN NSString * const SCNParticlePropertySize NS_AVAILABLE(10_10, 8_0);            // float                controller animation type : {NSNumber}
SCN_EXTERN NSString * const SCNParticlePropertyFrame NS_AVAILABLE(10_10, 8_0);           // float                controller animation type : {NSNumber}
SCN_EXTERN NSString * const SCNParticlePropertyFrameRate NS_AVAILABLE(10_10, 8_0);       // float                controller animation type : {NSNumber}
SCN_EXTERN NSString * const SCNParticlePropertyBounce NS_AVAILABLE(10_10, 8_0);          // float                controller animation type : {NSNumber}
SCN_EXTERN NSString * const SCNParticlePropertyCharge NS_AVAILABLE(10_10, 8_0);          // float                controller animation type : {NSNumber}
SCN_EXTERN NSString * const SCNParticlePropertyFriction NS_AVAILABLE(10_10, 8_0);        // float                controller animation type : {NSNumber}

// These two properties are only available when handling the events of type SCNParticleEventCollision.
// They are read-only values.
SCN_EXTERN NSString * const SCNParticlePropertyContactPoint NS_AVAILABLE(10_10, 8_0);    // float3               not controllable
SCN_EXTERN NSString * const SCNParticlePropertyContactNormal NS_AVAILABLE(10_10, 8_0);   // float3               not controllable

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
typedef void (^SCNParticleEventBlock)(void * __nonnull * __nonnull data, size_t * __nonnull dataStride, uint32_t * __nullable indices, NSInteger count);

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
typedef void (^SCNParticleModifierBlock)(void * __nonnull * __nonnull data, size_t * __nonnull dataStride, NSInteger start, NSInteger end, float deltaTime);

// Particle Sorting Mode
typedef NS_ENUM(NSInteger, SCNParticleSortingMode) {
	SCNParticleSortingModeNone,                        //particles are not sorted
	SCNParticleSortingModeProjectedDepth,              //particles are sorted by depth (far rendered first)
	SCNParticleSortingModeDistance,                    //particles are sorted by distance from the point of view
	SCNParticleSortingModeOldestFirst,                 //particles are sorted by birth date - oldest first
	SCNParticleSortingModeYoungestFirst                //particles are sorted by birth date - yougest first
} NS_ENUM_AVAILABLE(10_10, 8_0);

// Particle Blend Mode
typedef NS_ENUM(NSInteger, SCNParticleBlendMode) {
	SCNParticleBlendModeAdditive,
	SCNParticleBlendModeSubtract,
	SCNParticleBlendModeMultiply,
	SCNParticleBlendModeScreen,
	SCNParticleBlendModeAlpha,
	SCNParticleBlendModeReplace
} NS_ENUM_AVAILABLE(10_10, 8_0);

// Particle Orientation Mode
typedef NS_ENUM(NSInteger, SCNParticleOrientationMode) {
	SCNParticleOrientationModeBillboardScreenAligned,  // particles are aligned on screen
	SCNParticleOrientationModeBillboardViewAligned,    // particles are perpendicular with the vector from the point of view to the particle.
	SCNParticleOrientationModeFree, 	                 // free on all axis.
    SCNParticleOrientationModeBillboardYAligned        // fixed on Y axis.
} NS_ENUM_AVAILABLE(10_10, 8_0);

// Particle Birth Location
typedef NS_ENUM(NSInteger, SCNParticleBirthLocation) {
    SCNParticleBirthLocationSurface,                   //particles are emitted on the surface of the emitter shape.
    SCNParticleBirthLocationVolume,                    //particles are emitted inside the volume of the emitter shape.
    SCNParticleBirthLocationVertex                     //particles are emitted on the vertices of the emitter shape.
} NS_ENUM_AVAILABLE(10_10, 8_0);

// Particle Birth Direction
typedef NS_ENUM(NSInteger, SCNParticleBirthDirection) {
    SCNParticleBirthDirectionConstant,                 // Z Direction of the Emitter.
    SCNParticleBirthDirectionSurfaceNormal,	        // Use the direction induced by the shape
    SCNParticleBirthDirectionRandom                    // Random direction.
} NS_ENUM_AVAILABLE(10_10, 8_0);

// Texture Animation Mode
typedef NS_ENUM(NSInteger, SCNParticleImageSequenceAnimationMode) {
    SCNParticleImageSequenceAnimationModeRepeat,             // The animation will loop.
    SCNParticleImageSequenceAnimationModeClamp,              // The animation will stop at both ends.
    SCNParticleImageSequenceAnimationModeAutoReverse         // The animation will reverse when reaching an end.
} NS_ENUM_AVAILABLE(10_10, 8_0);

// Particle Variation Mode
typedef NS_ENUM(NSInteger, SCNParticleInputMode) {
	SCNParticleInputModeOverLife,                  // The input time for the controller animation is the current life duration of the particle
	SCNParticleInputModeOverDistance,              // The input time for the controller animation is the distance from the variation origin node.
	SCNParticleInputModeOverOtherProperty,         // The input time for the controller animation is the current value of another specified property.
} NS_ENUM_AVAILABLE(10_10, 8_0);

// Particle Modifier Stage
typedef NS_ENUM(NSInteger, SCNParticleModifierStage) {
	SCNParticleModifierStagePreDynamics,
	SCNParticleModifierStagePostDynamics,
	SCNParticleModifierStagePreCollision,
	SCNParticleModifierStagePostCollision
} NS_ENUM_AVAILABLE(10_10, 8_0);

// Particle Event
typedef NS_ENUM(NSInteger, SCNParticleEvent) {
	SCNParticleEventBirth,                             // Event triggered when a new particle spawns.
	SCNParticleEventDeath,                             // Event triggered when a particle dies.
	SCNParticleEventCollision                          // Event triggered when a particle collides with a collider node.
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 @class SCNParticlePropertyController
 @abstract The SCNParticlePropertyController class controls the variation over time or over distance of a particle property.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface SCNParticlePropertyController: NSObject <NSSecureCoding, NSCopying>

// Creates and initializes a particle property controller with the specified animation.
+ (instancetype)controllerWithAnimation:(CAAnimation *)animation;

// Specifies the animation to be applied on the particle system property. The type of the animation will depend of the property controlled.
// See the documentation along property name definition.
@property(nonatomic, retain) CAAnimation *animation;

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
@property(nonatomic, copy, nullable) NSString *inputProperty;

@end


/*!
 @class SCNParticleSystem
 @abstract The SCNParticleSystem class represents a system of particles.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
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

// Specifies the looping behavior of the emission. Default to YES.
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

// Specifies the emitting direction of newly created particles, used in the SCNParticleBirthDirectionConstant mode. Default to {0, 0, 1}. Animatable.
@property(nonatomic) SCNVector3 emittingDirection;

// Specifies the acceleration applied to particles, in world coordinates.
// Allows to simulate winds or gravity. Default to {0, 0, 0}. Animatable.
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
// in degree per second. Defaults to 0. Animatable.
@property(nonatomic) CGFloat particleAngularVelocity;

// Specifies the variation of the angular velocity, in degree per second. Defaults to 0. Animatable.
@property(nonatomic) CGFloat particleAngularVelocityVariation;

// Specifies the life span of particles. Animatable.
@property(nonatomic) CGFloat particleLifeSpan;

// Specifies the life span variation of particles. Animatable.
@property(nonatomic) CGFloat particleLifeSpanVariation;

// Specifies an optional system to spawn new particles when a particle die
@property(nonatomic, retain, nullable) SCNParticleSystem *systemSpawnedOnDying;

// Specifies an optional system to spawn new particles when a particle die
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

// Specifies the texture animation mode. Default to SCNTextureAnimationModeRepeat.
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
// The keys for this directionary are listed in the "Particle Properties Name" section.
@property(nonatomic, copy, nullable) NSDictionary<NSString *, SCNParticlePropertyController *> *propertyControllers;

// Remove all the already-emitted particles and restart the simulation.
- (void)reset;

// Events handling
// "block" will be invoked for particles that trigger the specified event, with the data and dataStride that corresponds to "properties". The block should only update the particle properties reference by the "indices" passed as argument in the block.
- (void)handleEvent:(SCNParticleEvent)event forProperties:(NSArray<NSString *> *)properties withBlock:(SCNParticleEventBlock)block;

// Modifications handling
// "block" will be invoked at every simulation step at the specified stage. The data and dataStride passed to the block will corresponds to the specified "properties".
- (void)addModifierForProperties:(NSArray<NSString *> *)properties atStage:(SCNParticleModifierStage)stage withBlock:(SCNParticleModifierBlock)block;
- (void)removeModifiersOfStage:(SCNParticleModifierStage)stage;
- (void)removeAllModifiers;

@end


@interface SCNNode (SCNParticleSystemSupport)

// Add a particle system to the receiver.
- (void)addParticleSystem:(SCNParticleSystem *)system NS_AVAILABLE(10_10, 8_0);

// Remove all particle systems of the receiver.
- (void)removeAllParticleSystems NS_AVAILABLE(10_10, 8_0);

// Remove the specified particle system from the receiver.
- (void)removeParticleSystem:(SCNParticleSystem *)system NS_AVAILABLE(10_10, 8_0);

// The particle systems attached to the node.
@property(readonly, nullable) NSArray<SCNParticleSystem *> *particleSystems NS_AVAILABLE(10_10, 8_0);

@end


@interface SCNScene (SCNParticleSystemSupport)

// Add a particle system at the given location.
- (void)addParticleSystem:(SCNParticleSystem *)system withTransform:(SCNMatrix4)transform NS_AVAILABLE(10_10, 8_0);

// Remove all particle systems of the receiver.
- (void)removeAllParticleSystems NS_AVAILABLE(10_10, 8_0);

// Remove the specified particle system from the receiver.
- (void)removeParticleSystem:(SCNParticleSystem *)system NS_AVAILABLE(10_10, 8_0);

// The particle systems attached to the scene.
@property(readonly, nullable) NSArray<SCNParticleSystem *> *particleSystems NS_AVAILABLE(10_10, 8_0);

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SceneKit.h
//
//  SceneKit.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

/*! @framework SceneKit
    @abstract A high-level 3D scene framework.
    @discussion SceneKit lets you easily load, manipulate, and render 3D scenes.
 */

//base
#import <SceneKit/SCNBase.h>

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

//bridges
#import <SceneKit/SceneKit_simd.h>

//scripting
#import <SceneKit/SCNJavascript.h>

// ==========  SceneKit.framework/Headers/SCNSceneRenderer.h
//
//  SCNSceneRenderer.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

@class SCNScene;
@class SCNNode;
@class SKScene;
@class SKTransition;
@protocol SCNSceneRendererDelegate;
@protocol MTLRenderCommandEncoder;
@protocol MTLCommandBuffer;
@class MTLRenderPassDescriptor;
@class AVAudioEngine;
@class AVAudioEnvironmentNode;

/*! @group Hit test options */

/*! If set to YES, returns the first object found. This object is not necessarily the nearest. Defaults to NO. */
SCN_EXTERN NSString * const SCNHitTestFirstFoundOnlyKey;
/*! Determines whether the results should be sorted. If set to YES sorts nearest objects first. Defaults to YES. */
SCN_EXTERN NSString * const SCNHitTestSortResultsKey;
/*! If set to YES ignores the objects clipped by the zNear/zFar range of the current point of view. Defaults to YES. */
SCN_EXTERN NSString * const SCNHitTestClipToZRangeKey;
/*! If set to YES ignores the faces not facing to the camera. Defaults to YES. */
SCN_EXTERN NSString * const SCNHitTestBackFaceCullingKey;
/*!  If set to YES only tests the bounding boxes of the 3D objects. Defaults to NO. */
SCN_EXTERN NSString * const SCNHitTestBoundingBoxOnlyKey;
/*! Determines whether the child nodes are ignored. Defaults to NO. */
SCN_EXTERN NSString * const SCNHitTestIgnoreChildNodesKey;
/*! Specifies the root node to use for the hit test. Defaults to the root node of the scene. */
SCN_EXTERN NSString * const SCNHitTestRootNodeKey;
/*! Determines whether hidden nodes should be ignored. Defaults to YES. */
SCN_EXTERN NSString * const SCNHitTestIgnoreHiddenNodesKey NS_AVAILABLE(10_9, 8_0);

/*!
 @enum SCNRenderingAPI
 @abstract rendering API used by SCNView and SCNRenderer.
 @discussion Default preferred API is SCNRenderingAPIMetal on iOS and SCNRenderingAPIOpenGLLegacy on OS X.
 If Metal is requested but not available then it fallbacks to SCNRenderingAPIOpenGLES2 on iOS and to SCNRenderingAPIOpenGLLegacy on OS X.
 */
typedef NS_ENUM(NSUInteger, SCNRenderingAPI) {
    SCNRenderingAPIMetal,
    SCNRenderingAPIOpenGLES2
} NS_ENUM_AVAILABLE(10_11, 9_0);

/*!
 @enum SCNDebugOptions
 @abstract Debug options.
 */
typedef NS_OPTIONS(NSUInteger, SCNDebugOptions) {
    SCNDebugOptionNone = 0,
    SCNDebugOptionShowPhysicsShapes   = 1 << 0,
    SCNDebugOptionShowBoundingBoxes   = 1 << 1,
    SCNDebugOptionShowLightInfluences = 1 << 2,
    SCNDebugOptionShowLightExtents    = 1 << 3,
    SCNDebugOptionShowPhysicsFields   = 1 << 4,
    SCNDebugOptionShowWireframe       = 1 << 5
} NS_ENUM_AVAILABLE(10_11, 9_0);


/*! @class SCNHitTestResult
    @abstract Results returned by the hit test methods.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNHitTestResult : NSObject

/*! The node hit. */
@property(nonatomic, readonly) SCNNode *node;

/*! Index of the geometry hit. */
@property(nonatomic, readonly) NSInteger geometryIndex;

/*! Index of the face hit. */
@property(nonatomic, readonly) NSInteger faceIndex;

/*! Intersection point in the node local coordinate system. */
@property(nonatomic, readonly) SCNVector3 localCoordinates;

/*! Intersection point in the world coordinate system. */
@property(nonatomic, readonly) SCNVector3 worldCoordinates;

/*! Intersection normal in the node local coordinate system. */
@property(nonatomic, readonly) SCNVector3 localNormal;

/*! Intersection normal in the world coordinate system. */
@property(nonatomic, readonly) SCNVector3 worldNormal;

/*! World transform of the node intersected. */
@property(nonatomic, readonly) SCNMatrix4 modelTransform;

/*! 
 @method textureCoordinatesWithMappingChannel:
 @abstract Returns the texture coordinates at the point of intersection, for a given mapping channel.
 @param channel The texture coordinates source index of the geometry to use. The channel must exists on the geometry otherwise {0,0} will be returned.
 */
- (CGPoint)textureCoordinatesWithMappingChannel:(NSInteger)channel;

@end



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
- (void)presentScene:(SCNScene *)scene withTransition:(SKTransition *)transition incomingPointOfView:(nullable SCNNode *)pointOfView completionHandler:(nullable void (^)())completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 @property sceneTime
 @abstract Specifies the current "scene time" to display the scene.
 @discussion The scene time only affect scene time based animations (see SCNAnimation.h "usesSceneTimeBase" and SCNSceneSource.h "SCNSceneSourceAnimationImportPolicyKey" for how to create scene time based animations). Scene time based animations and this property are typically used by tools and viewer to ease seeking in time while previewing a scene.
 */
@property(nonatomic) NSTimeInterval sceneTime NS_AVAILABLE(10_10, 8_0);

/*! 
 @property delegate
 @abstract Specifies the renderer delegate.
 */
@property(nonatomic, assign, nullable) id <SCNSceneRendererDelegate> delegate;

/*!
 @method hitTest:options:
 @abstract Returns an array of SCNHitTestResult for each node that contains a specified point.
 @param point A point in the coordinate system of the receiver.
 @param options Optional parameters (see the "Hit test options" group for the available options).
 */
- (NSArray<SCNHitTestResult *> *)hitTest:(CGPoint)point options:(nullable NSDictionary<NSString *, id> *)options;

/*!
 @method isNodeInsideFrustum:withPointOfView:
 @abstract Test whether node is visible from the specified point of view.
 @param node The node to test the visibility of.
 @param pointOfView The point of view used to test the visibility.
 @discussion Return YES if the node is inside or intersects the clipping planes of the point of view. This method doesn't test if 'node' is occluded by another node.
 */
- (BOOL)isNodeInsideFrustum:(SCNNode *)node withPointOfView:(SCNNode *)pointOfView NS_AVAILABLE(10_9, 8_0);

/*!
 @method nodesInsideFrustumWithPointOfView:
 @abstract Returns an array containing the nodes visible from the specified point of view.
 @param pointOfView The point of view used to test the visibility.
 @discussion Returns an array of all the nodes that are inside or intersects the clipping planes of the point of view.
 */
- (NSArray<SCNNode *> *)nodesInsideFrustumWithPointOfView:(SCNNode *)pointOfView NS_AVAILABLE(10_11, 9_0);

/*!
 @method projectPoint
 @abstract Projects a point in the world coordinate system using the receiver's current point of view and viewport.
 @param point The world position to be projected.
 @discussion A point projected from the near (resp. far) clip plane will have a z component of 0 (resp. 1).
 */
- (SCNVector3)projectPoint:(SCNVector3)point NS_AVAILABLE(10_9, 8_0);

/*!
 @method unprojectPoint
 @abstract Unprojects a screenspace 2D point with depth info using the receiver's current point of view and viewport.
 @param point The screenspace position to be unprojected.
 @discussion A point whose z component is 0 (resp. 1) is unprojected on the near (resp. far) clip plane.
 */
- (SCNVector3)unprojectPoint:(SCNVector3)point NS_AVAILABLE(10_9, 8_0);

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
- (BOOL)prepareObject:(id)object shouldAbortBlock:(nullable BOOL (^)())block NS_AVAILABLE(10_9, 8_0);

/*!
 @method prepareObjects:withCompletionHandler:
 @abstract Prepare the specified objects for drawing on the background.
 @param objects The objects to prepare. It can be one or more instances of SCNScene, SCNNode, SCNGeometry, or SCNMaterial
 @param completionHandler This block will be called when all objects has been prepared, or on failure.
 @discussion This method is observable using NSProgress.
 */
- (void)prepareObjects:(NSArray *)objects withCompletionHandler:(nullable void (^)(BOOL success))completionHandler NS_AVAILABLE(10_10, 8_0);

/*!
 @property showsStatistics
 @abstract Determines whether the receiver should display statistics info like FPS. Defaults to NO.
 @discussion  When set to YES, statistics are displayed in a overlay on top of the rendered scene.
 */
@property(nonatomic) BOOL showsStatistics NS_AVAILABLE(10_9, 8_0);

/*!
 @property debugOptions
 @abstract Specifies the debug options of the receiver. Defaults to SCNDebugOptionNone.
 */
@property(nonatomic) SCNDebugOptions debugOptions NS_AVAILABLE(10_11, 9_0);

/*!
 @property overlaySKScene
 @abstract Specifies the overlay of the receiver as a SpriteKit scene instance. Defaults to nil.
 */
@property(nonatomic, retain, nullable) SKScene *overlaySKScene NS_AVAILABLE(10_10, 8_0);

/*!
 @property renderingAPI
 @abstract Specifies the rendering API associated to the receiver.
 @discussion This is the rendering API effectively used by the receiver. You can specify a preferred rendering API when initializing a view programmatically (see SCNPreferredRenderingAPI in SCNSceneRenderer.h) or using Interface Builder's SCNView inspector.
 */
@property(nonatomic, readonly) SCNRenderingAPI renderingAPI NS_AVAILABLE(10_11, 9_0);

/*!
 @property context
 @abstract A Core OpenGL render context that is used as the render target (a CGLContextObj on OS X, an EAGLContext on iOS).
 */
@property(nonatomic, readonly, nullable) void *context;

#if SCN_ENABLE_METAL

/*!
 @property currentRenderCommandEncoder
 @abstract The current render command encoder if any. This property is only valid within the SCNSceneRendererDelegate methods and when renderering with Metal. Otherwise it is set to nil.
 */
@property(nonatomic, readonly, nullable) id <MTLRenderCommandEncoder> currentRenderCommandEncoder NS_AVAILABLE(10_11, 9_0);

/*!
 @property device
 @abstract The metal device of the renderer. This property is only valid on a renderer created with a Metal device. Otherwise it is set to nil.
 */
@property(nonatomic, readonly, nullable) id <MTLDevice> device NS_AVAILABLE(10_11, 9_0);

/*!
 @property colorPixelFormat
 @abstract The pixel format of the color attachment 0 of the renderer. This property is only valid on a renderer created with a Metal device.
 */
@property(nonatomic, readonly) MTLPixelFormat colorPixelFormat NS_AVAILABLE(10_11, 9_0);

/*!
 @property depthPixelFormat
 @abstract The pixel format of the depth attachment of the renderer. This property is only valid on a renderer created with a Metal device.
 */
@property(nonatomic, readonly) MTLPixelFormat depthPixelFormat NS_AVAILABLE(10_11, 9_0);

/*!
 @property stencilPixelFormat
 @abstract The pixel format of the stencil attachment of the renderer. This property is only valid on a renderer created with a Metal device.
 */
@property(nonatomic, readonly) MTLPixelFormat stencilPixelFormat NS_AVAILABLE(10_11, 9_0);

/*!
 @property commandQueue
 @abstract The command queue of the renderer. This property is only valid on a renderer created with a Metal device. Otherwise it is set to nil.
 */
@property(nonatomic, readonly, nullable) id <MTLCommandQueue> commandQueue NS_AVAILABLE(10_11, 9_0);

#endif

/*!
 @property audioEngine
 @abstract Contains the instance of audio engine used by the scene.
 @discussion The audio engine can be used to add custom nodes to the audio graph.
 */
@property(nonatomic, readonly) AVAudioEngine *audioEngine NS_AVAILABLE(10_11, 9_0);

/*!
 @property audioEnvironmentNode
 @abstract Contains the instance of audio environment node used by the scene to spacialize sounds.
 */
@property(nonatomic, readonly) AVAudioEnvironmentNode *audioEnvironmentNode NS_AVAILABLE(10_11, 9_0);

/*!
 @property audioListener
 @abstract Use this property to set the audio node to use as the listener position and orientation when rendering positional audio for this scene. The default is nil which means that the current point of view will be used dynamically.
 */
@property(nonatomic, retain, nullable) SCNNode *audioListener NS_AVAILABLE(10_11, 9_0);



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
 @param aRenderer The renderer that will render the scene.
 @param time The time at which to update the scene.
 @discussion All modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer updateAtTime:(NSTimeInterval)time NS_AVAILABLE(10_10, 8_0);

/*!
 @method renderer:didApplyAnimationsAtTime:
 @abstract Invoked on the delegate once the scene renderer did apply the animations.
 @param aRenderer The renderer that did render the scene.
 @param time The time at which the animations were applied.
 @discussion All modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didApplyAnimationsAtTime:(NSTimeInterval)time NS_AVAILABLE(10_10, 8_0);

/*!
 @method renderer:didSimulatePhysicsAtTime:
 @abstract Invoked on the delegate once the scene renderer did simulate the physics.
 @param aRenderer The renderer that did render the scene.
 @param time The time at which the physics were simulated.
 @discussion All modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer didSimulatePhysicsAtTime:(NSTimeInterval)time NS_AVAILABLE(10_10, 8_0);

/*!
 @method renderer:willRenderScene:atTime:
 @abstract Invoked on the delegate before the scene renderer renders the scene. At this point the openGL context and the destination framebuffer are bound.
 @param aRenderer The renderer that will render the scene.
 @param scene The scene to be rendered.
 @param time The time at which the scene is to be rendered.
 @discussion Starting in 10.10 all modifications done within this method don't go through the transaction model, they are directly applied on the presentation tree.
 */
- (void)renderer:(id <SCNSceneRenderer>)renderer willRenderScene:(SCNScene *)scene atTime:(NSTimeInterval)time;

/*!
 @method renderer:didRenderScene:atTime:
 @abstract Invoked on the delegate once the scene renderer did render the scene.
 @param aRenderer The renderer that did render the scene.
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
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNTechnique.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @group Light Types
 @abstract Describes the various light types available.
 */

/*! @constant SCNLightTypeAmbient Ambient light */
SCN_EXTERN NSString * const SCNLightTypeAmbient;
/*! @constant SCNLightTypeOmni Omnidirectional light */
SCN_EXTERN NSString * const SCNLightTypeOmni;
/*! @constant SCNLightTypeDirectional Directional light */
SCN_EXTERN NSString * const SCNLightTypeDirectional;
/*! @constant SCNLightTypeSpot Spot light */
SCN_EXTERN NSString * const SCNLightTypeSpot;


/*! @enum SCNShadowMode
 @abstract The different modes available to compute shadows.
 @discussion When the shadow mode is set to SCNShadowModeForward, shadows are computed while computing the lighting. In this mode only the alpha component of the shadow color is used to alter the lighting contribution.
 When the shadow mode is set to SCNShadowModeDeferred shadows are applied as a post process. Shadows are blend over the final image and can therefor be of any arbitrary color. However it is most of the time less effiscient as SCNShadowModeForward, except when a scene has a lot of overdraw.
 When the shadow mode is set to SCNShadowModeModulated the light doesn't illuminate the scene anymore, it only casts shadows. Therefor setting the light color has no effect. In this mode gobos act as a shadow projector: the gobo image is modulated with the shadow receiver's fragments. The typical usage is to use an image of a radial gradient (black to white) that is projected under a character (and use the categoryBitMask of the light and nodes to exclude the character from the shadow receiver).
 */
typedef NS_ENUM(NSInteger, SCNShadowMode) {
    SCNShadowModeForward   = 0,
    SCNShadowModeDeferred  = 1,
    SCNShadowModeModulated = 2
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 @class SCNLight
 @abstract SCNLight represents a light that can be attached to a SCNNode. 
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNLight : NSObject <SCNAnimatable, SCNTechniqueSupport, NSCopying, NSSecureCoding>

/*! 
 @method light
 @abstract Creates and returns a light instance.
 */
+ (instancetype)light;

/*! 
 @property type
 @abstract Specifies the receiver's type.
 @discussion A light type can be one of the "Light Types" constants. Defaults to SCNLightTypeOmni on iOS 8 and later, and on OSX 10.10 and later (otherwise defaults to SCNLightTypeAmbient).
 */
@property(nonatomic, copy) NSString *type;

/*! 
 @property color
 @abstract Specifies the receiver's color (NSColor or CGColorRef). Animatable. Defaults to white.
 @discussion The initial value is a NSColor.
 */
@property(nonatomic, retain) id color;

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
 @abstract Specifies the color (CGColorRef or NSColor) of the shadow casted by the receiver. Default is 50% transparent black. Animatable.
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
@property(nonatomic) CGSize shadowMapSize NS_AVAILABLE(10_10, 8_0);

/*!
 @property shadowSampleCount
 @abstract Specifies the number of sample per fragment to compute the shadow map. Defaults to 1.
 */
@property(nonatomic) NSUInteger shadowSampleCount NS_AVAILABLE(10_10, 8_0);

/*!
 @property shadowMode
 @abstract Specified the mode to use to cast shadows. See above for the available modes and their description. Defaults to SCNShadowModeForward.
 */
@property(nonatomic) SCNShadowMode shadowMode NS_AVAILABLE(10_10, 8_0);

/*!
 @property shadowBias
 @abstrat Specifies the correction to apply to the shadow map to correct acne artefacts. It is multiplied by an implementation-specific value to create a constant depth offset. Defaults to 1.0
 */
@property(nonatomic) CGFloat shadowBias NS_AVAILABLE(10_10, 8_0);


#pragma mark - Light projection settings for shadows

/*!
 @property orthographicScale
 @abstract Specifies the orthographic scale used to render from the directional light into the shadow map. Defaults to 1.
 @discussion This is only applicable for directional lights.
 */
@property(nonatomic) CGFloat orthographicScale NS_AVAILABLE(10_10, 8_0);

/*!
 @property zNear
 @abstract Specifies the minimal distance between the light and the surface to cast shadow on.  If a surface is closer to the light than this minimal distance, then the surface won't be shadowed. The near value must be different than zero. Animatable. Defaults to 1.
 */
@property(nonatomic) CGFloat zNear NS_AVAILABLE(10_10, 8_0);

/*!
 @property zFar
 @abstract Specifies the maximal distance between the light and a visible surface to cast shadow on. If a surface is further from the light than this maximal distance, then the surface won't be shadowed. Animatable. Defaults to 100.
 */
@property(nonatomic) CGFloat zFar NS_AVAILABLE(10_10, 8_0);


#pragma mark - Attenuation

/*!
 @property attenuationStartDistance
 @abstract The distance at which the attenuation starts (Omni or Spot light types only). Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat attenuationStartDistance NS_AVAILABLE(10_10, 8_0);

/*!
 @property attenuationEndDistance
 @abstract The distance at which the attenuation ends (Omni or Spot light types only). Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat attenuationEndDistance NS_AVAILABLE(10_10, 8_0);

/*!
 @property attenuationFalloffExponent
 @abstract Specifies the attenuation between the start and end attenuation distances. 0 means a constant attenuation, 1 a linear attenuation and 2 a quadratic attenuation, but any positive value will work (Omni or Spot light types only). Animatable. Defaults to 2.
 */
@property(nonatomic) CGFloat attenuationFalloffExponent NS_AVAILABLE(10_10, 8_0);


#pragma mark - Spot parameters

/*!
 @property spotInnerAngle
 @abstract The angle in degrees between the spot direction and the lit element below which the lighting is at full strength. Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat spotInnerAngle  NS_AVAILABLE(10_10, 8_0);

/*!
 @property spotOuterAngle
 @abstract The angle in degrees between the spot direction and the lit element after which the lighting is at zero strength. Animatable. Defaults to 45 degrees.
 */
@property(nonatomic) CGFloat spotOuterAngle  NS_AVAILABLE(10_10, 8_0);


#pragma mark - Other

/*!
 @property gobo
 @abstract Specifies the gobo (or "cookie") of the light, used to control the shape of emitted light. Defaults to nil.
 @discussion Gobos are only supported by spot lights.
 */
@property(nonatomic, readonly, nullable) SCNMaterialProperty *gobo NS_AVAILABLE(10_9, 8_0);

/*!
 @property categoryBitMask
 @abstract Determines the node categories that will be lit by the receiver. Defaults to all bit set.
 */
@property(nonatomic) NSUInteger categoryBitMask NS_AVAILABLE(10_10, 8_0);


@end


NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNBoundingVolume.h
//
//  SCNBoundingVolume.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

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
 */
- (BOOL)getBoundingBoxMin:(nullable SCNVector3 *)min max:(nullable SCNVector3 *)max;

/*!
 @method getBoundingSphereCenter:radius:
 @abstract Fill the center vector with the center of the bounding sphere and store the radius of the bounding sphere in 'radius'.
 @param center A pointer to a SCNVector3 to store the center of the bounding sphere into.
 @param radius A pointer to a CGFloat to store the radius of the bounding sphere into.
 */
- (BOOL)getBoundingSphereCenter:(nullable SCNVector3 *)center radius:(nullable CGFloat *)radius;

/*!
 @method setBoundingBoxMin:max:
 @abstract Override the receiver bounding box with the min and max vectors provided.
 @param min A pointer to a SCNVector3 representing the min vertex of the desired bounding box.
 @param max A pointer to a SCNVector3 representing the max vertex of the desired bounding box.
 @discussion Passing nil as arguments will recompute the original bounding box of the receiver.
 */
- (void)setBoundingBoxMin:(nullable SCNVector3 *)min max:(nullable SCNVector3 *)max NS_AVAILABLE(10_9, 8_0);

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNAudioSource.h
//
//  SCNAudioSource.h
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVAudioNode;

/*!
 @class SCNAudioSource
 @abstract The SCNAudioSource class represents an audio source that can be added to a SCNNode.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
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
 @abstract Specifies whether the audio source should loop or not. Default to NO.
 */
@property(nonatomic) BOOL loops;

/*!
 @property shouldStream
 @abstract Specifies whether the audio source should be streamed or not. Default to NO.
 */
@property(nonatomic) BOOL shouldStream;

/*!
 @method load
 @abstract Load and uncompress the audio source in memory. This method has no effect if "shouldStream" is set to YES or if the audio source is already loaded.
 @discussion This method let you preload your audio sources. If an audio source is not preloaded, it will be loaded anyway when playing it.
 */
- (void)load;

@end

NS_CLASS_AVAILABLE(10_11, 9_0)
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
@property(nonatomic, copy, nullable) void (^willStartPlayback)();

/*!
 @property playbackFinished
 @abstract This block is called when the playback stops in case a valid audio source is present.
 */
@property(nonatomic, copy, nullable) void (^didFinishPlayback)();

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
- (void)addAudioPlayer:(SCNAudioPlayer *)player NS_AVAILABLE(10_11, 9_0);

/*!
 @method removeAllAudioPlayers
 @abstract Remove all audio players from this node and stop playing them.
 */
- (void)removeAllAudioPlayers NS_AVAILABLE(10_11, 9_0);

/*!
 @method removeAudioPlayer:
 @abstract Remove the given audio player from this node and stop playing it.
 */
- (void)removeAudioPlayer:(SCNAudioPlayer *)player NS_AVAILABLE(10_11, 9_0);

/*!
 @property audioPlayers
 @abstract Get an array with all the audio players connected and playing on this node.
 */
@property(nonatomic, readonly) NSArray<SCNAudioPlayer *> *audioPlayers NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNAnimation.h
//
//  SCNAnimation.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @typedef SCNAnimationEventBlock
 @discussion Signature for the block executed when the animation event is triggered.
 */
typedef void (^SCNAnimationEventBlock)(CAAnimation *animation, id animatedObject, BOOL playingBackward);

/*!
 @class SCNAnimationEvent
 @abstract SCNAnimationEvent encapsulate a block to trigger at a specific time.
 */

NS_CLASS_AVAILABLE(10_9, 8_0)
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

/*!
 @protocol SCNAnimatable
 @abstract The SCNAnimatable protocol defines an animatable property. Objects that implement this protocol can be animated through these methods.
*/
@protocol SCNAnimatable <NSObject>

/*!
 @method addAnimation:forKey:
 @abstract Add an animation.
 @param animation Added animation.
 @param key May be any string such that only one animation per unique key is added per animatable object.
 */
- (void)addAnimation:(CAAnimation *)animation forKey:(nullable NSString *)key;

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
 @method animationKeys
 @abstract Returns an array containing the keys of all animations currently attached to the receiver.
 */
@property(readonly) NSArray<NSString *> *animationKeys;

/*!
 @method animationForKey:
 @abstract Returns the animation with the given identifier
 @param key The identifier for the animation to retrieve.
 @discussion This will return nil if no such animation exists.
			 Attempting to modify any properties of the returned object will result in undefined behavior.
 */
- (nullable CAAnimation *)animationForKey:(NSString *)key;

/*!
 @method pauseAnimationForKey:
 @abstract Pause the animation with the given identifier.
 @param key The identifier for the animation to pause.
 */
- (void)pauseAnimationForKey:(NSString *)key NS_AVAILABLE(10_9, 8_0);

/*!
 @method resumeAnimationForKey:
 @abstract Resume the animation with the given identifier.
 @param key The identifier for the animation to resume.
 */
- (void)resumeAnimationForKey:(NSString *)key NS_AVAILABLE(10_9, 8_0);

/*!
 @method isAnimationForKeyPaused:
 @abstract Returns whether the animation for the specified identifier is paused.
 @param key The identifier for the animation to query.
 */
- (BOOL)isAnimationForKeyPaused:(NSString *)key NS_AVAILABLE(10_9, 8_0);

/*!
 @method removeAnimationForKey:fadeOutDuration:
 @abstract Smoothly remove the animation with the given identifier.
 @param key The identifier for the animation to remove.
 @param duration The fade out duration used to remove the animation.
 */
- (void)removeAnimationForKey:(NSString *)key fadeOutDuration:(CGFloat)duration NS_AVAILABLE(10_10, 8_0);

@end

/*!
 @category CAAnimation (CAAnimation)
 @abstract Extends the CAAnimation class for SceneKit explicit animations.
 */
@interface CAAnimation (SceneKitAdditions)

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
@property CGFloat fadeInDuration NS_AVAILABLE(10_9, 8_0);
 
/*!
 @property fadeOutDuration
 @abstract Determines the receiver's fade-out duration.
 @discussion When the fadeOutDuration is greater than zero, the effect of the animation progressively decrease from 100% to 0% at the end of the animation duration.
 */
@property CGFloat fadeOutDuration NS_AVAILABLE(10_9, 8_0);

/*!
 @property animationEvents
 @abstract Specifies the animation events attached to the receiver.
 */
@property(nonatomic, copy, nullable) NSArray<SCNAnimationEvent *> *animationEvents NS_AVAILABLE(10_9, 8_0);

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNLevelOfDetail.h
//
//  SCNLevelOfDetail.h
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNGeometry.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class SCNLevelOfDetail
 @abstract SCNLevelOfDetail represents a level of detail of a geometry.
 */
NS_CLASS_AVAILABLE(10_9, 8_0)
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
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

/*!
 @class SCNPhysicsBehavior
 @abstract SCNPhysicsBehavior is an abstract class that represents a behavior in the physics world.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface SCNPhysicsBehavior : NSObject <NSSecureCoding>
@end

/*!
 @class SCNPhysicsHingeJoint
 @abstract SCNPhysicsHingeJoint makes two bodies to move like they are connected by a hinge. It is for example suitable for doors, chains...
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
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
NS_CLASS_AVAILABLE(10_10, 8_0)
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
NS_CLASS_AVAILABLE(10_10, 8_0)
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
 @class SCNPhysicsVehicleWheel
 @abstract SCNPhysicsVehicleWheel represents a wheel that can be attached to a SCNPhysicsVehicle instance.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
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
NS_CLASS_AVAILABLE(10_10, 8_0)
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
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class SCNTechnique
 @abstract SCNTechnique represents a rendering process that may require multiple passes.
 @discussion A technique is generally initialized from a Property List file. It can be set to any object that conforms to the SCNTechniqueSupport protocol.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
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
 "clearColor" a string specifying the clear color as 4 float (red, green, blue, alpha), or the string "sceneBackground" to clear with the scene background color.
 
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
 
 semantic: vertex, normal, color, texcoord, time, modelViewProjectionTransform, modelViewTransform, modelTransform, viewTransform, projectionTransform, normalTransform, modelViewProjectionInverseTransform, modelViewInverseTransform, modelInverseTransform, viewInverseTransform, projectionInverseTransform, normalInverseTransform
 
 type: float, vec2, vec3, vec4, mat4, int, ivec2, ivec3, ivec4, mat3, sampler2D, none. Every types can also be an array of the given type by adding [N] where N is the number of elements in the array.
 
 image: name of an image located in the application bundle. (only valid when type is sampler2D)
 
 if a semantic is set, no type is required.
 
<target description>
 A dictionary with the following optional keys and their possible associated values:
 
 type: a string specifying the type of the render target. It can be one of the following: color, depth, stencil
 format: a string specifying the format of the render target. It can be:
 - for color targets: rgba32f, r8, r16, rgba(default)
 - for depth targets: depth24, depth24stencil8
 - for stencil targets: depth24stencil8
 scaleFactor: a float value (encapsulated in a NSNumber) that controls the size of the render target. default to 1, which means 1x the size of the main viewport.
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
 
 On OS X 10.11 or later and iOS 9 or later you can also use the object subscripting syntax to set values to uniforms.
 For example:
 myTechnique[@"myAmplitude"] = aValue;
 */
- (nullable id)objectForKeyedSubscript:(id)key NS_AVAILABLE(10_11, 9_0);
- (void)setObject:(nullable id)obj forKeyedSubscript:(id <NSCopying>)key NS_AVAILABLE(10_11, 9_0);

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
@property(nonatomic, copy, nullable) SCNTechnique *technique NS_AVAILABLE(10_10, 8_0);

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNPhysicsBody.h
//
//  SCNPhysicsBody.h
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

@class SCNPhysicsShape;

//Physics Body type
typedef NS_ENUM(NSInteger, SCNPhysicsBodyType) {
	SCNPhysicsBodyTypeStatic,
	SCNPhysicsBodyTypeDynamic,
	SCNPhysicsBodyTypeKinematic
} NS_ENUM_AVAILABLE(10_10, 8_0);

//Collision default category
typedef NS_OPTIONS(NSUInteger, SCNPhysicsCollisionCategory) {
	SCNPhysicsCollisionCategoryDefault = 1 << 0,    // default collision group for dynamic and kinematic objects
	SCNPhysicsCollisionCategoryStatic  = 1 << 1,    // default collision group for static objects
	SCNPhysicsCollisionCategoryAll     = ~0UL       // default for collision mask
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 @class SCNPhysicsBody
 @abstract The SCNPhysicsBody class describes the physics properties (such as mass, friction...) of a node.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
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
@property(nonatomic) SCNVector3 momentOfInertia NS_AVAILABLE(10_11, 9_0);

//Permits to disable the use of the default moment of inertia in favor of the one stored in momentOfInertia.
@property(nonatomic) BOOL usesDefaultMomentOfInertia NS_AVAILABLE(10_11, 9_0);

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
//limited to the first 15 bits on OS X 10.10 and iOS 8.
@property(nonatomic) NSUInteger categoryBitMask;

//Defines what logical 'categories' of bodies this body responds to collisions with. Defaults to all bits set (all categories).
@property(nonatomic) NSUInteger collisionBitMask;

//A mask that defines which categories of bodies cause intersection notifications with this physics body. Defaults to 0.
//On iOS 8 and OS X 10.10 and lower the intersection notifications are always sent when a collision occurs.
@property(nonatomic) NSUInteger contactTestBitMask NS_AVAILABLE(10_11, 9_0);

//If set to YES this node will be affected by gravity. The default is YES.
@property(nonatomic, getter=isAffectedByGravity) BOOL affectedByGravity NS_AVAILABLE(10_11, 9_0);

//Applies a linear force in the specified direction. The linear force is applied on the center of mass of the receiver. If impulse is set to YES then the force is applied for just one frame, otherwise it applies a continuous force.
- (void)applyForce:(SCNVector3)direction impulse:(BOOL)impulse;

//Applies a linear force with the specified position and direction. The position is relative to the node that owns the physics body.
- (void)applyForce:(SCNVector3)direction atPosition:(SCNVector3)position impulse:(BOOL)impulse;

//Applies an angular force (torque). If impulse is set to YES then the force is applied for just one frame, otherwise it applies a continuous force.
- (void)applyTorque:(SCNVector4)torque impulse:(BOOL)impulse;

//Clears the forces applied one the receiver.
- (void)clearAllForces;

//Reset the physical transform to the node's model transform.
- (void)resetTransform;

@end
    
NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNShadable.h
//
//  SCNShadable.h
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
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
} NS_ENUM_AVAILABLE(10_11, 9_0);

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
typedef void (^SCNBindingBlock)(unsigned int programID, unsigned int location, SCNNode *renderedNode, SCNRenderer *renderer);


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
@property(nonatomic, retain, nullable) SCNProgram *program;

/*!
 @method handleBindingOfSymbol:usingBlock:
 @abstract Sets the block to call at render time to bind the value for the specified symbol of the receiver's SCNProgram. This method has no effect for symbols declared in shader modifiers.
 @param symbol The name of the symbol to bind a value for.
 @param block The block to call to bind the specified symbol.
 @discussion This method can only be used with OpenGL and OpenGLES based programs.
 */
- (void)handleBindingOfSymbol:(NSString *)symbol usingBlock:(nullable SCNBindingBlock)block NS_AVAILABLE(10_9, 8_0);

/*!
 @method handleUnbindingOfSymbol:usingBlock:
 @abstract Sets the block to call at render time to unbind the value for the specified symbol of the receiver's SCNProgram. This method has no effect for symbols declared in shader modifiers.
 @param symbol The name of the symbol to unbind.
 @param block The block to call to unbind the specified symbol.
 @discussion This method can only be used with OpenGL and OpenGLES based programs.
 */
- (void)handleUnbindingOfSymbol:(NSString *)symbol usingBlock:(nullable SCNBindingBlock)block NS_AVAILABLE(10_9, 8_0);

/*!
 @property shaderModifiers
 @abstract Dictionary of shader modifiers snippets, targeting entry points. The valid keys are the entry points described in the "Shader Modifier Entry Point" constants. The values are the code snippets formatted as described below.
 @discussion Shader modifiers allow you to inject shader code in the standard shaders of SceneKit. This injection is allowed in few controlled entry points, allowing specific kind of tasks in specific context. Each modifier can operate on specific structures along with access to global uniforms, that could be the standard SceneKit uniforms or its own declared uniforms.
 
 The structure of a shader modifier is:
 
 | // Custom uniforms declarations of the form:
 | // for GLSL: [uniform type uniformName [= defaultValue]]
 | uniform float myGrayAmount = 3.0;
 |
 | //for Metal a pragma is required and arguments have the form [type name]
 | #pragma arguments
 | float myGrayAmount;
 |
 | // Optional global function definitions (for Metal: references to arguments from global functions are not supported).
 | float mySin(float t) {
 |    return sin(t);
 | }
 |
 | [#pragma transparent | opaque]
 | [#pragma body]
 |
 | // the shader modifier code snippet itself
 | vec3 myColor = vec3(myGrayAmount);
 | _output.color.rgb += myColor;
 
 The `#pragma body` directive
 Is only needed if you declared functions that must not be included in the shader code itself.
 
 The `#pragma transparent` directive
 Forces the rendering to be blended using the following equation:
 _output.color.rgb + (1 - _output.color.a) * dst.rgb;
 where `dst` represents the current fragment color. The rgb components must be premultiplied.
 
 The `#pragma opaque` directive
 Forces the rendering to be opaque. It then ignores the alpha component of the fragment.
 
 The SCNGeometry and SCNMaterial classes are key-value coding compliant classes, which means that you can set values for arbitrary keys. Even if the key `myAmplitude` is not a declared property of the class, you can still set a value for it.
 Declaring a `myAmplitude` uniform in the shader modifier makes SceneKit observe the reveiver's `myAmplitude` key. Any change to that key will make SceneKit bind the uniform with the new value.
 
 Custom uniforms can be animated using explicit animations.
 
 The following GLSL types (and Objective-C counterparts) can be used to declare (and bind) custom uniforms:
 Example: uniform float myAmplitude = 0.5;
 
 GLSL types    | Objective-C types
 --------------------------------------
 int           | NSNumber, NSInteger, int
 float         | NSNumber, CGFloat, float, double
 vec2          | CGPoint
 vec3          | SCNVector3
 vec4          | SCNVector4
 mat4, mat44   | SCNMatrix4
 sampler2D     | SCNMaterialProperty
 samplerCube   | SCNMaterialProperty (with a cube map)
 
 The following prefixes are reserved by SceneKit and should not be used in custom names:
 u_
 a_
 v_
 
 SceneKit declares the following built-in uniforms:
 float u_time;                               // The current time, in seconds
 vec2  u_inverseResolution;                 // 1./screen size (available on iOS 9 and OS X 10.11)
 -------------------------------------------------------------------------------------
 mat4  u_modelTransform                      // See SCNModelTransform
 mat4  u_viewTransform                       // See SCNViewTransform
 mat4  u_projectionTransform                 // See SCNProjectionTransform
 mat4  u_normalTransform                     // See SCNNormalTransform
 mat4  u_modelViewTransform                  // See SCNModelViewTransform
 mat4  u_modelViewProjectionTransform        // See SCNModelViewProjectionTransform
 -------------------------------------------------------------------------------------
 mat4  u_inverseModelTransform               // The inverse matrix of u_modelTransform
 mat4  u_inverseViewTransform                // The inverse matrix of u_viewTransform
 mat4  u_inverseProjectionTransform          // The inverse matrix of u_projectionTransform
 mat4  u_inverseModelViewTransform           // The inverse matrix of u_modelViewTransform
 mat4  u_inverseModelViewProjectionTransform // The inverse matrix of u_modelViewProjectionTransform
 -------------------------------------------------------------------------------------
 mat2x3 u_boundingBox;                       // The bounding box of the current geometry, in model space, u_boundingBox[0].xyz and u_boundingBox[1].xyz being respectively the minimum and maximum corner of the box.
 
 Shader modifiers can be used to tweak SceneKit rendering by adding custom code at the following entry points:
 1. vertex
 2. surface
 3. lighting
 4. fragment
 See below for a detailed explanation of these entry points and the context they provide.
 
 Shader modifiers can be written in GLSL or Metal. Metal shaders won't run on iOS8 and OS X 10.10 or below.
 */
@property(nonatomic, copy, nullable) NSDictionary<NSString *, NSString *> *shaderModifiers NS_AVAILABLE(10_9, 8_0);

@end


/*!
 @group Semantic options
 @abstract Valid keys for the option parameter of setSemantic:forSymbol:options:
 */
SCN_EXTERN NSString * const SCNProgramMappingChannelKey;  /* This key is optional and may be used in association with the SCNGeometrySourceSemanticTexcoord semantic. It allows to associate a mapping channel from the geometry to a symbol from the program source code. The mapping channel allows to plug programs that work with multiple texture coordinates. The associated value must be a NSNumber(integer) greater than zero. */

/*!
 @class SCNProgram
 @abstract A SCNProgram lets you specify custom shaders to use when rendering materials.
 */
NS_CLASS_AVAILABLE(10_8, 8_0)
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
@property(nonatomic, copy, nullable) NSString *vertexFunctionName NS_AVAILABLE(10_11, 9_0);

/*!
 @property fragmentFunctionName
 @abstract Determines the receiver's fragment function name.
 @discussion The name of the fragment function (for Metal programs).
 */
@property(nonatomic, copy, nullable) NSString *fragmentFunctionName NS_AVAILABLE(10_11, 9_0);

/*!
 @method handleBindingOfBufferNamed:frequency:usingBlock:
 @abstract Sets the block to call at render time to bind the buffer of the specified symbol of the receiver's program.
 @param name The name of the buffer to bind.
 @param frequency The frequency at which the block has to be invoked. Can be per frame, per node or per geometry or material. See SCNBufferBindingBlock above.
 @param block The block that binds the buffer.
 @discussion This method can only be used with Metal based programs.
 */
- (void)handleBindingOfBufferNamed:(NSString *)name frequency:(SCNBufferFrequency)frequency usingBlock:(SCNBufferBindingBlock)block NS_AVAILABLE(10_11, 9_0);


/*!
 @property opaque
 @abstract Determines the receiver's fragment are opaque or not. Defaults to YES.
 */
@property(nonatomic, getter=isOpaque) BOOL opaque NS_AVAILABLE(10_10, 8_0);

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
 @method library
 @abstract Specifies the metal library to use to locate the function names specified above. 
 @discussion If set to nil the default library is used. Defaults to nil.
 */
@property(nonatomic, retain, nullable) id <MTLLibrary> library NS_AVAILABLE(10_11, 9_0);

@end

/*!
 @protocol SCNProgramDelegate
 @abstract The SCNProgramDelegate protocol declares the methods that an instance of SCNProgram invokes to delegate the binding of parameters.
 */
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
- (BOOL)programIsOpaque:(SCNProgram *)program NS_DEPRECATED(10_8, 10_10, NA, NA);

@end

/*!
 @group Shader Modifier Entry Point
 @abstract Entry points designing the insertion point of the shader code snippet of a shader modifiers dictionary.
 */
/*!
 @constant SCNShaderModifierEntryPointGeometry
 @abstract This is the entry point to operate on the geometry vertices, for example deforming them.
 @discussion It operates entirely in the vertex shader stage. It's input is the geometry structure:
 
 Structures available from this entry point:
 
 | struct SCNShaderGeometry {
 |    vec4 position;
 |    vec3 normal;
 |    vec4 tangent;
 |    vec4 color;
 |    vec2 texcoords[kSCNTexcoordCount];
 | } _geometry;
 |
 | Access: ReadWrite
 | Stages: Vertex shader only
 
 kSCNTexcoordCount is a constant integer set to the number of texture coordinates used.
 
 All the geometric fields (position, normal and tangent) are in model space. You can use one of the provided automatic uniforms
 such as u_modelTransform or u_modelViewTransform if you want to operate in another space (but the results must stay in the model space, otherwise remaining computations won't be correct).
 The texture coordinates are the raw values found in the mesh, they have not been transformed yet by their optional contentsTransform. The contentsTransform if any is applied after the geometry shader modifier.
 
 Example: Simple sinusoidal deformation
 
 uniform float Amplitude = 0.1
 _geometry.position.xyz += _geometry.normal * (Amplitude*_geometry.position.y*_geometry.position.x) * sin(u_time);
 */
SCN_EXTERN NSString * const SCNShaderModifierEntryPointGeometry NS_AVAILABLE(10_9, 8_0);

/*!
 @constant SCNShaderModifierEntryPointSurface
 @abstract This is the entry point to alter the surface representation of the material, before the lighting has taken place.
 @discussion
 
 Structures available from this entry point:
 
 | struct SCNShaderSurface {
 |    vec3 view;                // Direction from the point on the surface toward the camera (V)
 |    vec3 position;            // Position of the fragment
 |    vec3 normal;              // Normal of the fragment (N)
 |    vec3 tangent;             // Tangent of the fragment
 |    vec3 bitangent;           // Bitangent of the fragment
 |    vec4 ambient;             // Ambient property of the fragment
 |    vec2 ambientTexcoord;     // Ambient texture coordinates
 |    vec4 diffuse;             // Diffuse property of the fragment. Alpha contains the opacity.
 |    vec2 diffuseTexcoord;     // Diffuse texture coordinates
 |    vec4 specular;            // Specular property of the fragment
 |    vec2 specularTexcoord;    // Specular texture coordinates
 |    vec4 emission;            // Emission property of the fragment
 |    vec2 emissionTexcoord;    // Emission texture coordinates
 |    vec4 multiply;            // Multiply property of the fragment
 |    vec2 multiplyTexcoord;    // Multiply texture coordinates
 |    vec4 transparent;         // Transparent property of the fragment
 |    vec2 transparentTexcoord; // Transparent texture coordinates
 |    vec4 reflective;          // Reflective property of the fragment
 |    float shininess;          // Shininess property of the fragment.
 |    float fresnel;            // Fresnel property of the fragment.
 | } _surface;
 |
 | Access: ReadWrite
 | Stages: Fragment shader only
 
 All geometric fields are in view space.
 All the other properties will be colors (texture have already been sampled at this stage) or floats. You can however do an extra sampling of standard textures if you want.
 In this case the naming pattern is u_<property>Texture. For example u_diffuseTexture or u_reflectiveTexture. Note that you have to be sure that the material do have a texture
 set for this property, otherwise you'll trigger a shader compilation error.
 
 Example: Procedural black and white stripes
 
 uniform float Scale = 12.0;
 uniform float Width = 0.25;
 uniform float Blend = 0.3;
 vec2 position = fract(_surface.diffuseTexcoord * Scale);
 float f1 = clamp(position.y / Blend, 0.0, 1.0);
 float f2 = clamp((position.y - Width) / Blend, 0.0, 1.0);
 f1 = f1 * (1.0 - f2);
 f1 = f1 * f1 * 2.0 * (3. * 2. * f1);
 _surface.diffuse = mix(vec4(1.0), vec4(0.0), f1);
 */
SCN_EXTERN NSString * const SCNShaderModifierEntryPointSurface NS_AVAILABLE(10_9, 8_0);

/*!
 @constant SCNShaderModifierEntryPointLightingModel
 @abstract This is the entry point to provide custom lighting equation. The fragment will be called for each active light
 of the scene and will need to accumulate lighting contribution for the vertex or the fragment in the _lightingContribution structure, using the light structure given.
 @discussion
 
 Structures available from the this entry point:
 
 | All the structures available from the SCNShaderModifierEntryPointSurface entry point
 |
 | Access: ReadOnly
 | Stages: Vertex shader and fragment shader
 
 | struct SCNShaderLightingContribution {
 |    vec3 ambient;
 |    vec3 diffuse;
 |    vec3 specular;
 | } _lightingContribution;
 |
 | Access: ReadWrite
 | Stages: Vertex shader and fragment shader
 
 | struct SCNShaderLight {
 |    vec4 intensity;
 |    vec3 direction; // Direction from the point on the surface toward the light (L)
 | } _light;
 |
 | Access: ReadOnly
 | Stages: Vertex shader and fragment shader
 
 Example: wrap diffuse lighting
 
 uniform float WrapFactor = 0.5;
 float dotProduct = (WrapFactor + max(0.0, dot(_surface.normal,_light.direction))) / (1 + WrapFactor);
 _lightingContribution.diffuse += (dotProduct * _light.intensity.rgb);
 vec3 halfVector = normalize(_light.direction + _surface.view);
 dotProduct = max(0.0, pow(max(0.0, dot(_surface.normal, halfVector)), _surface.shininess));
 _lightingContribution.specular += (dotProduct * _light.intensity.rgb);
 */
SCN_EXTERN NSString * const SCNShaderModifierEntryPointLightingModel NS_AVAILABLE(10_9, 8_0);

/*!
 @constant SCNShaderModifierEntryPointFragment
 @abstract This is the last entry point in the fragment shader, where you can alter the final color returned by the shader.
 @discussion You can alter the final color by reading and writing to the output color via the output structure below.
 
 Structures available from the this entry point:
 
 | All the structures available from the SCNShaderModifierEntryPointSurface entry point
 |
 | Access: ReadOnly
 | Stages: Fragment shader only
 
 | struct SCNShaderOutput {
 |    vec4 color;
 | } _output;
 |
 | Access: ReadWrite
 | Stages: Fragment shader only
 
 Example: inverse final color
 
 _output.color.rgb = vec3(1.0) - _output.color.rgb;
 */
SCN_EXTERN NSString * const SCNShaderModifierEntryPointFragment NS_AVAILABLE(10_9, 8_0);

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNGeometry.h
//
//  SCNGeometry.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNBoundingVolume.h>
#import <SceneKit/SCNShadable.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNGeometrySource;
@class SCNGeometryElement;
@class SCNLevelOfDetail;
@protocol MTLBuffer;

typedef NS_ENUM(NSInteger, SCNGeometryPrimitiveType) {
	SCNGeometryPrimitiveTypeTriangles     = 0,
	SCNGeometryPrimitiveTypeTriangleStrip = 1,
	SCNGeometryPrimitiveTypeLine          = 2,
	SCNGeometryPrimitiveTypePoint         = 3
};

SCN_EXTERN NSString * const SCNGeometrySourceSemanticVertex;
SCN_EXTERN NSString * const SCNGeometrySourceSemanticNormal;
SCN_EXTERN NSString * const SCNGeometrySourceSemanticColor;
SCN_EXTERN NSString * const SCNGeometrySourceSemanticTexcoord;
SCN_EXTERN NSString * const SCNGeometrySourceSemanticVertexCrease NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN NSString * const SCNGeometrySourceSemanticEdgeCrease NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN NSString * const SCNGeometrySourceSemanticBoneWeights NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN NSString * const SCNGeometrySourceSemanticBoneIndices NS_AVAILABLE(10_10, 8_0);

/*!
 @class SCNGeometry
 @abstract SCNGeometry is an abstract class that represents the geometry that can be attached to a SCNNode. 
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNGeometry : NSObject <SCNAnimatable, SCNBoundingVolume, SCNShadable, NSCopying, NSSecureCoding>

/*!
 @method geometry
 @abstract Creates and returns an empty geometry object.
 @discussion An empty geometry may be used as the lowest level of detail of a geometry.
 */
+ (instancetype)geometry NS_AVAILABLE(10_9, 8_0);

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
+ (instancetype)geometryWithSources:(NSArray<SCNGeometrySource *> *)sources elements:(NSArray<SCNGeometryElement *> *)elements;

/*!
 @property geometrySources
 @abstract The array of geometry sources of the receiver.
 */
@property(nonatomic, readonly) NSArray<SCNGeometrySource *> *geometrySources NS_AVAILABLE(10_10, 8_0);

/*! 
 @method geometrySourcesForSemantic:
 @abstract Returns the geometry sources for a given semantic.
 @param semantic The semantic of the geometry sources that should be retrieved.
 @discussion Returns nil if no geometry source is found for the given semantic. May return more than one source, typically for multiple texture coordinate sources.
 */
- (NSArray<SCNGeometrySource *> *)geometrySourcesForSemantic:(NSString *)semantic;

/*!
 @property geometryElements
 @abstract The array of geometry elements of the receiver.
 */
@property(nonatomic, readonly) NSArray<SCNGeometryElement *> *geometryElements NS_AVAILABLE(10_10, 8_0);

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
@property(nonatomic, copy, nullable) NSArray<SCNLevelOfDetail *> *levelsOfDetail NS_AVAILABLE(10_9, 8_0);

/*!
 @property subdivisionLevel
 @abstract Specifies the subdivision level of the receiver. Defaults to 0.
 @discussion A subdivision level of 0 means no subdivision.
 */
@property(nonatomic) NSUInteger subdivisionLevel NS_AVAILABLE(10_10, 8_0);

/*!
 @property edgeCreasesElement
 @abstract Specifies the edges creases that control the subdivision. Defaults to nil.
 @discussion The primitive type of this geometry element must be SCNGeometryPrimitiveTypeLine. See subdivisionLevel above to control the level of subdivision. See edgeCreasesElement above to specify edges for edge creases.
 */
@property(nonatomic, retain, nullable) SCNGeometryElement *edgeCreasesElement NS_AVAILABLE(10_10, 8_0);

/*!
 @property edgeCreasesSource
 @abstract Specifies the crease value of the edges specified by edgeCreasesElement. Defaults to nil.
 @discussion The semantic of this geometry source must be "SCNGeometrySourceSemanticEdgeCrease". The creases values are floating values between 0 and 10, where 0 means smooth and 10 means infinitely sharp. See subdivisionLevel above to control the level of subdivision. See edgeCreasesElement above to specify edges for edge creases.
 */
@property(nonatomic, retain, nullable) SCNGeometrySource *edgeCreasesSource NS_AVAILABLE(10_10, 8_0);

@end


/*!
 @class SCNGeometrySource
 @abstract A geometry source contains geometry data for a specific semantic. The data format is described by properties.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
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
+ (instancetype)geometrySourceWithData:(NSData *)data semantic:(NSString *)semantic vectorCount:(NSInteger)vectorCount floatComponents:(BOOL)floatComponents componentsPerVector:(NSInteger)componentsPerVector bytesPerComponent:(NSInteger)bytesPerComponent dataOffset:(NSInteger)offset dataStride:(NSInteger)stride;

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
 @param buffer A metal buffer.
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
     id<MTLCommandBuffer> myCommandBuffer = [aRenderer.commandQueue commandBuffer];

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
+ (instancetype)geometrySourceWithBuffer:(id <MTLBuffer>)mtlBuffer vertexFormat:(MTLVertexFormat)vertexFormat semantic:(NSString *)semantic vertexCount:(NSInteger)vertexCount dataOffset:(NSInteger)offset dataStride:(NSInteger)stride NS_AVAILABLE(10_11, 9_0);
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
@property(nonatomic, readonly) NSString *semantic;

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


/*!
 @class SCNGeometryElement
 @abstract A geometry element describes how vertices from a geometry source are connected together.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
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
 @property bytesPerIndex
 @abstract The number of bytes that represent an index value
 */
@property(nonatomic, readonly) NSInteger bytesPerIndex;

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNBase.h
//
//  SCNBase.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

/*! @header SCNBase
    @abstract Various defines used throughout SceneKit
 */

#define SCN_EXTERN FOUNDATION_EXTERN

#ifndef __has_feature      // Optional.
#define __has_feature(x) 0 // Compatibility with non-clang compilers.
#endif
// ==========  SceneKit.framework/Headers/SCNAction.h
//
//  SCNAction.h
//
//  Copyright (c) 2014-2015 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;
@class SCNAction;
@class SCNAudioSource;

/*! @enum SCNActionTimingMode
 @abstract The modes that an action can use to adjust the apparent timing of the action.
 */
typedef NS_ENUM(NSInteger, SCNActionTimingMode) {
    SCNActionTimingModeLinear,
    SCNActionTimingModeEaseIn,
    SCNActionTimingModeEaseOut,
    SCNActionTimingModeEaseInEaseOut
} NS_ENUM_AVAILABLE(10_10, 8_0);

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
- (void)runAction:(SCNAction *)action NS_AVAILABLE(10_10, 8_0);

/*!
 @method runAction:completionHandler:
 @abstract Adds an action to the list of actions executed by the node. Your block is called when the action completes.
 */
- (void)runAction:(SCNAction *)action completionHandler:(nullable void (^)())block NS_AVAILABLE(10_10, 8_0);

/*!
 @method runAction:forKey:
 @abstract Adds an identifiable action to the list of actions executed by the node.
 */
- (void)runAction:(SCNAction *)action forKey:(nullable NSString *)key NS_AVAILABLE(10_10, 8_0);

/*!
 @method runAction:forKey:completionHandler:
 @abstract Adds an identifiable action to the list of actions executed by the node. Your block is called when the action completes.
 */
- (void)runAction:(SCNAction *)action forKey:(nullable NSString *)key completionHandler:(nullable void (^)())block NS_AVAILABLE(10_10, 8_0);

/*!
 @method hasActions
 @abstract Returns a Boolean value that indicates whether the node is executing actions.
 */
@property(nonatomic, readonly) BOOL hasActions NS_AVAILABLE(10_10, 8_0);

/*!
 @method actionForKey:
 @abstract Returns an action associated with a specific key.
 */
- (nullable SCNAction *)actionForKey:(NSString *)key NS_AVAILABLE(10_10, 8_0);

/*!
 @method removeActionForKey:
 @abstract Removes an action associated with a specific key.
 */
- (void)removeActionForKey:(NSString *)key NS_AVAILABLE(10_10, 8_0);

/*!
 @method removeAllActions
 @abstract Ends and removes all actions from the node.
 */
- (void)removeAllActions NS_AVAILABLE(10_10, 8_0);

/*!
 @method actionKeys
 @abstract Returns an array containing the keys of all actions currently attached to the receiver.
 */
@property(nonatomic, readonly) NSArray<NSString *> *actionKeys NS_AVAILABLE(10_10, 8_0);

@end


NS_CLASS_AVAILABLE(10_10, 8_0)
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

//Creates an action that rotates the node by a relative value.
+ (SCNAction *)rotateByX:(CGFloat)xAngle y:(CGFloat)yAngle z:(CGFloat)zAngle duration:(NSTimeInterval)duration;

//Creates an action that rotates the node to an absolute angle.
+ (SCNAction *)rotateToX:(CGFloat)xAngle y:(CGFloat)yAngle z:(CGFloat)zAngle duration:(NSTimeInterval)duration;
+ (SCNAction *)rotateToX:(CGFloat)xAngle y:(CGFloat)yAngle z:(CGFloat)zAngle duration:(NSTimeInterval)duration shortestUnitArc:(BOOL)shortestUnitArc;

//Creates an action that rotates the node arond an axis by the specified angle
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
+ (SCNAction *)hide NS_AVAILABLE(10_11, 9_0);

//Creates an action that unhides a node
+ (SCNAction *)unhide NS_AVAILABLE(10_11, 9_0);

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
 @param waitForCompletion If YES, then the duration of this action is the same
 as the length of the audio playback. If NO, the action is considered
 to have completed immediately.*/
+ (SCNAction *)playAudioSource:(SCNAudioSource *)source waitForCompletion:(BOOL)wait NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNTransaction.h
//
//  SCNTransaction.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/* Transactions are SceneKit's mechanism for batching multiple scene graph
 * operations into atomic updates. Every
 * modification to the scene graph requires a transaction to be part of. */

NS_CLASS_AVAILABLE(10_8, 8_0)
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
+ (CFTimeInterval)animationDuration;
+ (void)setAnimationDuration:(CFTimeInterval)duration;

/* Accessors for the "animationTimingFunction" per-thread transaction
 * property. The default value is nil, when set to a non-nil value any
 * animations added to scene graph will have this value set as their
 * "timingFunction" property. */
+ (nullable CAMediaTimingFunction *)animationTimingFunction;
+ (void)setAnimationTimingFunction:(nullable CAMediaTimingFunction *)animationTimingFunction;

/* Accessors for the "disableActions" per-thread transaction property.
 * Defines whether or not the implicit animations are performed. 
 * Defaults to NO, i.e. implicit animations enabled. */
+ (BOOL)disableActions;
+ (void)setDisableActions:(BOOL)flag;

/* Accessors for the "completionBlock" per-thread transaction property.
 * Once set to a non-nil value the block is guaranteed to be called (on
 * the main thread) as soon as all animations subsequently added by
 * this transaction group have completed (or been removed). */
#if __BLOCKS__
+ (nullable void (^)(void))completionBlock;
+ (void)setCompletionBlock:(nullable void (^)(void))block;
#endif

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
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;

/*! 
 @enum SCNPhysicsFieldScope
 @abstract Specifies the domain of influence of a physics field.
 */
typedef NS_ENUM(NSInteger, SCNPhysicsFieldScope) {
    SCNPhysicsFieldScopeInsideExtent,
    SCNPhysicsFieldScopeOutsideExtent,
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 @class SCNPhysicsField
 @abstract SCNPhysicsField is an abstract class that describes a force field that applies in the physics world.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface SCNPhysicsField : NSObject <NSCopying, NSSecureCoding>

// The following properties control the behavior of the field
@property(nonatomic) CGFloat strength;                               // The strength factor of the force field. default 1.0.
@property(nonatomic) CGFloat falloffExponent;                        // Changes the power of the force based on the distance from the center of the field (1 / distance ^ falloffExponent). Defaults to 0.0.
@property(nonatomic) CGFloat minimumDistance;                        // Distance from the center of the field where the effect is at full strength. Defaults to 1e-6.

@property(nonatomic, getter=isActive) BOOL active;                   // Specifies whether force field is active or not. Defaults to YES.
@property(nonatomic, getter=isExclusive) BOOL exclusive;             // If YES, it suppresses any other field in its area. Defaults to NO.

// The following properties control the area of effect
@property(nonatomic) SCNVector3 halfExtent;                          // Specifies the half extent of the area of effect. default is FLT_MAX.
@property(nonatomic) BOOL usesEllipsoidalExtent;                     // YES means that the area of effect is rounded within the extent. Defaults to NO.
@property(nonatomic) SCNPhysicsFieldScope scope;                     // Controls whether the force field should apply inside or outside of the area. Defaults to inside.

@property(nonatomic) SCNVector3 offset;                              // Offset of origin effect within the area
@property(nonatomic) SCNVector3 direction;                           // Direction of the field. Only applies to linear gravity and vortex fields. Defaults to (0,-1,0)

/*!
 @property categoryBitMask
 @abstract Determines the node categories that will be influenced by the receiver. Defaults to all bit set.
 */
@property(nonatomic) NSUInteger categoryBitMask NS_AVAILABLE(10_10, 8_0);


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
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <ModelIO/ModelIO.h>

NS_ASSUME_NONNULL_BEGIN

/*! 
 @header ModelIO.h
 @abstract Bridge with the Model I/O framework
 */

@interface SCNScene (SCNModelIO)
+ (instancetype)sceneWithMDLAsset:(MDLAsset *)mdlAsset NS_AVAILABLE(10_11, 9_0);
@end

@interface MDLAsset (SCNModelIO)
+ (instancetype)assetWithSCNScene:(SCNScene *)scnScene NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNNode (SCNModelIO)
+ (instancetype)nodeWithMDLObject:(MDLObject *)mdlObject NS_AVAILABLE(10_11, 9_0);
@end

@interface MDLObject (SCNModelIO)
+ (instancetype)objectWithSCNNode:(SCNNode *)scnNode NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNGeometry (SCNModelIO)
+ (instancetype)geometryWithMDLMesh:(MDLMesh *)mdlMesh NS_AVAILABLE(10_11, 9_0);
@end

@interface MDLMesh (SCNModelIO)
+ (instancetype)meshWithSCNGeometry:(SCNGeometry *)scnGeometry NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNGeometryElement (SCNModelIO)
+ (instancetype)geometryElementWithMDLSubmesh:(MDLSubmesh *)mdlSubMesh NS_AVAILABLE(10_11, 9_0);
@end

@interface MDLSubmesh (SCNModelIO)
+ (instancetype)submeshWithSCNGeometryElement:(SCNGeometryElement *)scnGeometryElement NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNMaterial (SCNModelIO)
+ (instancetype)materialWithMDLMaterial:(MDLMaterial *)mdlMaterial NS_AVAILABLE(10_11, 9_0);
@end

@interface MDLMaterial (SCNModelIO)
+ (instancetype)materialWithSCNMaterial:(SCNMaterial *)scnMaterial NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNLight (SCNModelIO)
+ (instancetype)lightWithMDLLight:(MDLLight *)mdlLight NS_AVAILABLE(10_11, 9_0);
@end

@interface MDLLight (SCNModelIO)
+ (instancetype)lightWithSCNLight:(SCNLight *)scnLight NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNCamera (SCNModelIO)
+ (instancetype)cameraWithMDLCamera:(MDLCamera *)mdlCamera NS_AVAILABLE(10_11, 9_0);
@end

@interface MDLCamera (SCNModelIO)
+ (instancetype)cameraWithSCNCamera:(SCNCamera *)scnCamera NS_AVAILABLE(10_11, 9_0);
@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNMorpher.h
//
//  SCNMorpher.h
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class SCNMorpher
 @abstract SCNMorpher controls the deformation of morphed geometries
 */

typedef NS_ENUM(NSInteger, SCNMorpherCalculationMode) {
    SCNMorpherCalculationModeNormalized, // (1 - w0 - w1 - ...) * BaseMesh + w0 * Target0 + w1 * Target1 + ...
    SCNMorpherCalculationModeAdditive    // BaseMesh + w0 * Target0 + w1 * Target1 + ...
};

NS_CLASS_AVAILABLE(10_9, 8_0)
@interface SCNMorpher : NSObject <SCNAnimatable, NSSecureCoding>

/*!
 @property targets
 @abstract Specifies the morph targets as an array of SCNGeometry.
 @discussion The target geometries must have the same number of entries in their geometry sources and the same topology as the base geometry.
 */
@property(nonatomic, copy) NSArray<SCNGeometry *> *targets;

/*!
 @method setWeight:forTargetAtIndex:
 @abstract Sets the weight for the target at the specified index. Animatable implicitly or explicitly with the keyPath "weights[index]".
 */
- (void)setWeight:(CGFloat)weight forTargetAtIndex:(NSUInteger)targetIndex;

/*!
 @method weightForTargetAtIndex:
 @abstract Retrieves the weight for the target at the specified index.
 */
- (CGFloat)weightForTargetAtIndex:(NSUInteger)targetIndex;

/*!
 @property calculationMode
 @abstract Specifies how the morph result is calculated by the receiver. Defaults to SCNMorpherCalculationModeNormalized.
 */
@property(nonatomic) SCNMorpherCalculationMode calculationMode;

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SceneKit_simd.h
//
//  SceneKit_simd.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <simd/simd.h>

/*! @header SceneKit_simd.h
    @abstract Bridge with the SIMD math library
 */

/* vector_ext bridge */
NS_INLINE vector_float3 SCNVector3ToFloat3(SCNVector3 v) {
    vector_float3 vec = {(float)v.x, (float)v.y, (float)v.z};
    return vec;
}

NS_INLINE vector_float4 SCNVector4ToFloat4(SCNVector4 v) {
    vector_float4 vec = {(float)v.x, (float)v.y, (float)v.z, (float)v.w};
    return vec;
}

NS_INLINE matrix_float4x4 SCNMatrix4ToMat4(SCNMatrix4 m) {
    matrix_float4x4 mat;
    mat.columns[0] = (vector_float4){(float)m.m11, (float)m.m12, (float)m.m13, (float)m.m14};
    mat.columns[1] = (vector_float4){(float)m.m21, (float)m.m22, (float)m.m23, (float)m.m24};
    mat.columns[2] = (vector_float4){(float)m.m31, (float)m.m32, (float)m.m33, (float)m.m34};
    mat.columns[3] = (vector_float4){(float)m.m41, (float)m.m42, (float)m.m43, (float)m.m44};
    return mat;
}
    
NS_INLINE SCNVector3 SCNVector3FromFloat3(vector_float3 v) {
    SCNVector3 vec = {v.x, v.y, v.z } ;
    return vec;
}

NS_INLINE SCNVector4 SCNVector4FromFloat4(vector_float4 v) {
    SCNVector4 vec = {v.x, v.y, v.z, v.z } ;
    return vec;
}

NS_INLINE SCNMatrix4 SCNMatrix4FromMat4(matrix_float4x4 m) {
    SCNMatrix4 mat;
    mat.m11 = m.columns[0].x; mat.m12 = m.columns[0].y; mat.m13 = m.columns[0].z; mat.m14 = m.columns[0].w;
    mat.m21 = m.columns[1].x; mat.m22 = m.columns[1].y; mat.m23 = m.columns[1].z; mat.m24 = m.columns[1].w;
    mat.m31 = m.columns[2].x; mat.m32 = m.columns[2].y; mat.m33 = m.columns[2].z; mat.m34 = m.columns[2].w;
    mat.m41 = m.columns[3].x; mat.m42 = m.columns[3].y; mat.m43 = m.columns[3].z; mat.m44 = m.columns[3].w;
    return mat;
}

// ==========  SceneKit.framework/Headers/SCNParametricGeometry.h
//
//  SCNParametricGeometry.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNGeometry;

/*!
 @class SCNPlane
 @abstract SCNPlane represents a rectangle with controllable width and height. The plane has one visible side.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
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
@property(nonatomic) CGFloat cornerRadius NS_AVAILABLE(10_9, 8_0);

/*!
 @property cornerSegmentCount
 @abstract The number of subdivisions for the rounded corners. Animatable.
 @discussion If the value is less than 1, the behavior is undefined. The default value is 10.
 */
@property(nonatomic) NSInteger cornerSegmentCount NS_AVAILABLE(10_9, 8_0);

@end


/*!
 @class SCNBox
 @abstract SCNBox represents a box with rectangular sides and optional chamfers.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
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

NS_CLASS_AVAILABLE(10_8, 8_0)
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

NS_CLASS_AVAILABLE(10_8, 8_0)
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

NS_CLASS_AVAILABLE(10_8, 8_0)
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

NS_CLASS_AVAILABLE(10_8, 8_0)
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

NS_CLASS_AVAILABLE(10_8, 8_0)
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

NS_CLASS_AVAILABLE(10_8, 8_0)
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

NS_CLASS_AVAILABLE(10_8, 8_0)
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

NS_CLASS_AVAILABLE(10_8, 8_0)
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
 @property reflectionResolutionScaleFactor
 @abstract Specifies the resolution scale factor of the buffer used to render the reflection.
 @discussion Defaults to 0.5.
*/
@property(nonatomic) CGFloat reflectionResolutionScaleFactor NS_AVAILABLE(10_10, 8_0);

@end

/*!
 @class SCNText
 @abstract SCNText represents a block of text that has been extruded
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
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
 @discussion The font property is only used when the string property is not an NSAttributedString. The default value is Helvetica size 36.
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
@property(nonatomic) CGFloat flatness NS_AVAILABLE(10_9, 8_0);

@end

/*!
 @class SCNShape
 @abstract SCNShape represents a 2D shape (cubic Bezier spline) than can be extruded.
 */

typedef NS_ENUM(NSInteger, SCNChamferMode) {
    SCNChamferModeBoth,
    SCNChamferModeFront,
    SCNChamferModeBack
} NS_ENUM_AVAILABLE(10_9, 8_0);

NS_CLASS_AVAILABLE(10_9, 8_0)
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
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

/*! @enum SCNReferenceLoadingPolicy
 @abstract Controls whenever to load the reference node.
 @discussion When the load policy is set to SCNReferenceLoadingPolicyImmediately, the reference is loaded immediately when the SCNReferenceNode is unarchived.
 When the load policy is set to SCNReferenceLoadingPolicyOnDemand the reference is never loaded until "load" is explicitly invoked.
 */
typedef NS_ENUM(NSInteger, SCNReferenceLoadingPolicy) {
    SCNReferenceLoadingPolicyImmediate = 0,
    SCNReferenceLoadingPolicyOnDemand  = 1
} NS_ENUM_AVAILABLE(10_11, 9_0);

/*!
 @class SCNReferenceNode
 @abstract Node that references an external file.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
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
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNTechnique.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class SCNCamera
 @abstract SCNCamera represents a camera that can be attached to a SCNNode. 
 @discussion A node with a camera can be used as a point of view to visualize a 3D scene.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
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
 @property xFov
 @abstract Determines the receiver's field of view on the X axis (in degree). Animatable.
 @discussion When both xFov and yFov are null an yFov of 60° is used. When both are set, the one that best fits the renderer's aspect ratio is used. When only one is set, it is used. Defaults to 0.
 */
@property(nonatomic) double xFov;

/*! 
 @property yFov
 @abstract Determines the receiver's field of view on the Y axis (in degree). Animatable.
 @discussion When both xFov and yFov are null an yFov of 60° is used. When both are set, the one that best fits the renderer's aspect ratio is used. When only one is set, it is used. Defaults to 0.
 */
@property(nonatomic) double yFov;

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
 @abstract Determines whether the receiver automatically adjusts the zNear and zFar values. Defaults to NO.
 @discussion When set to YES, the near and far planes are automatically set to fit the bounding box of the entire scene at render time. Setting the property zNear or zFar automatically resets this property to NO.
 */
@property(nonatomic) BOOL automaticallyAdjustsZRange NS_AVAILABLE(10_9, 8_0);

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
@property(nonatomic) double orthographicScale NS_AVAILABLE(10_9, 8_0);

/*!
 @method projectionTransform
 @abstract Determines the projection transform used by the camera to project the world onscreen. 
 */
- (SCNMatrix4)projectionTransform;
- (void)setProjectionTransform:(SCNMatrix4)projectionTransform NS_AVAILABLE(10_9, 8_0);

/*!
 @functiongroup Depth of field
 */
/*!
 @property focalDistance
 @abstract Determines the receiver's focal distance. Animatable.
 @discussion When non zero, the focal distance determines how the camera focuses the objects in the 3d scene. Defaults to 10.0
 */
@property(nonatomic) CGFloat focalDistance NS_AVAILABLE(10_9, 8_0);

/*!
 @property focalSize
 @abstract Determines the receiver's focal size. Animatable.
 @discussion Determines the size of the area around focalDistance where the objects are in focus. Defaults to 0.
 */
@property(nonatomic) CGFloat focalSize NS_AVAILABLE(10_9, 8_0);

/*!
 @property focalBlurRadius
 @abstract Determines the receiver's focal radius. Animatable.
 @discussion Determines the maximum amount of blur for objects out of focus. Defaults to 0.
 */
@property(nonatomic) CGFloat focalBlurRadius NS_AVAILABLE(10_9, 8_0);

/*!
 @property aperture
 @abstract Determines the receiver's aperture. Animatable.
 @discussion Determines how fast the transition between in-focus and out-of-focus areas is. The greater the aperture is the faster the transition is. Defaults to 1/8.
 */
@property(nonatomic) CGFloat aperture NS_AVAILABLE(10_9, 8_0);

/*!
 @property categoryBitMask
 @abstract Determines the node categories that are visible from the receiver. Defaults to all bits set.
 */
@property(nonatomic) NSUInteger categoryBitMask NS_AVAILABLE(10_10, 8_0);

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNPhysicsContact.h
//
//  SCNPhysicsContact.h
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

/*!
 @class SCNPhysicsContact
 @abstract SCNPhysicsContact contains information about a physics contact.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface SCNPhysicsContact : NSObject

//The two nodes in contact
@property(nonatomic, readonly) SCNNode *nodeA;
@property(nonatomic, readonly) SCNNode *nodeB;

//The contact point, impulse and distance in world space coordinates.
@property(nonatomic, readonly) SCNVector3 contactPoint;
@property(nonatomic, readonly) SCNVector3 contactNormal;
@property(nonatomic, readonly) CGFloat    collisionImpulse; // the collision impulse on nodeA
@property(nonatomic, readonly) CGFloat    penetrationDistance; 

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNMaterialProperty.h
//
//  SCNMaterialProperty.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*! @enum SCNFilterMode
    @abstract Filtering modes
*/
typedef NS_ENUM(NSInteger, SCNFilterMode) {
    SCNFilterModeNone    NS_ENUM_AVAILABLE(10_9, 8_0) = 0,
    SCNFilterModeNearest NS_ENUM_AVAILABLE(10_9, 8_0) = 1,
    SCNFilterModeLinear  NS_ENUM_AVAILABLE(10_9, 8_0) = 2
};

/*! @enum SCNWrapeMode
 @abstract Wrap modes
 */
typedef NS_ENUM(NSInteger, SCNWrapMode) {
    SCNWrapModeClamp NS_ENUM_AVAILABLE(10_9, 8_0) = 1,
    SCNWrapModeRepeat NS_ENUM_AVAILABLE(10_9, 8_0) = 2,
    SCNWrapModeClampToBorder NS_ENUM_AVAILABLE(10_9, 9_0) = 3,
    SCNWrapModeMirror NS_ENUM_AVAILABLE(10_9, 8_0) = 4,
};

/*! @class SCNMaterialProperty
    @abstract The contents of a SCNMaterial slot
    @discussion This can be used to specify the various properties of SCNMaterial slots such as diffuse, ambient, etc.
*/

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNMaterialProperty : NSObject <SCNAnimatable, NSSecureCoding>

/*!
 @method materialPropertyWithContents:
 @abstract Creates and initialize a property instance with the specified contents.
 */
+ (instancetype)materialPropertyWithContents:(id)contents NS_AVAILABLE(10_9, 8_0);

/*! 
 @property contents
 @abstract Specifies the receiver's contents. This can be a color (NSColor/UIColor), an image (NSImage/CGImageRef), a layer (CALayer), a path (NSString or NSURL), a SpriteKit scene (SKScene) or a texture (SKTexture, id<MTLTexture> or GLKTextureInfo). Animatable when set to a color.
 @discussion CGColorRef and CGImageRef can also be set. An array (NSArray) of 6 images is allowed for cube maps, only for reflective property. This array must contain images of the exact same dimensions, in the following order, in a left-handed coordinate system : +X, -X, +Y, -Y, +Z, -Z or if you prefer Right, Left, Top, Bottom, Front, Back. 
     Setting the contents to an instance of SKTexture will automatically update the wrapS, wrapT, contentsTransform, minification, magnification and mip filters according to the SKTexture settings.
 */
@property(nonatomic, retain, nullable) id contents;

/*!
 @property intensity
 @abstract Determines the receiver's intensity. This intensity is used to modulate the properties in several ways.
 It dims the diffuse, specular and emission properties, it varies the bumpiness of the normal property and the
 filter property is blended with white. Default value is 1.0. Animatable.
 */
@property(nonatomic) CGFloat intensity NS_AVAILABLE(10_9, 8_0);

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
 @discussion Defaults to SCNFilterModeNone.
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
@property(nonatomic, retain, nullable) id borderColor;

/*! 
 @property mappingChannel
 @abstract Determines the receiver's mapping channel. Defaults to 0.
 @discussion Geometries potentially have multiple sources of texture coordinates. Every source has a unique mapping channel index. The mapping channel allows to select which source of texture coordinates is used to map the content of the receiver. 
 */
@property(nonatomic) NSInteger mappingChannel;      

/*!
 @property maxAnisotropy
 @abstract Specifies the receiver's max anisotropy. Defaults to 1.0.
 @discussion Anisotropic filtering reduces blur and preserves detail at extreme viewing angles.
 */
@property(nonatomic) CGFloat maxAnisotropy NS_AVAILABLE(10_9, 8_0);

@end
    
NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNPhysicsShape.h
//
//  SCNPhysicsShape.h
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

@class SCNGeometry;
@class SCNNode;

//Type of the physics shape. Default is SCNPhysicsShapeTypeConvexHull.
//See below for the list of shape types.
SCN_EXTERN NSString * const SCNPhysicsShapeTypeKey NS_AVAILABLE(10_10, 8_0);

//The possible values for the key SCNPhysicsShapeGeometryTypeKey
SCN_EXTERN NSString * const SCNPhysicsShapeTypeBoundingBox NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN NSString * const SCNPhysicsShapeTypeConvexHull NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN NSString * const SCNPhysicsShapeTypeConcavePolyhedron NS_AVAILABLE(10_10, 8_0);

//A boolean to decide if a hierarchy is kept as a compound of shapes or flattened as one single volume. Default is true.
SCN_EXTERN NSString * const SCNPhysicsShapeKeepAsCompoundKey NS_AVAILABLE(10_10, 8_0);

//Local scaling of the physics shape (as an SCNVector3 wrapped in a NSValue)
SCN_EXTERN NSString * const SCNPhysicsShapeScaleKey NS_AVAILABLE(10_10, 8_0);

/*!
 @class SCNPhysicsShape
 @abstract SCNPhysicsShape represents the shape of a physics body.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface SCNPhysicsShape : NSObject <NSCopying, NSSecureCoding>

//Creates an instance of a physics shape based on a geometry. see above for the possible options.
+ (instancetype)shapeWithGeometry:(SCNGeometry *)geometry options:(nullable NSDictionary<NSString *, id> *)options;

//Creates an instance of a physics shape based on a node hierachy. The hierarchy must contain geometries at some point to create a valid shape. see above for the possible options.
+ (instancetype)shapeWithNode:(SCNNode *)node options:(nullable NSDictionary<NSString *, id> *)options;

//Creates an instance of a physics shape based on several sub shapes, associated with transforms. The transforms are to be passed as an array of NSValue wrapping SCNMatrix4
+ (instancetype)shapeWithShapes:(NSArray<SCNPhysicsShape *> *)shapes transforms:(nullable NSArray<NSValue *> *)transforms;

// Returns the options requested at init time
@property(readonly, nonatomic, nullable) NSDictionary<NSString *, id> *options NS_AVAILABLE(10_11, 9_0);

// Returns the object from which this physics shape was created. It can be an SCNGeometry*, an SCNNode* or in NSArray* of subshapes.
@property(readonly, nonatomic) id sourceObject NS_AVAILABLE(10_11, 9_0);

// If the physics shape was created from an array of sub shapes, transforms contains the associated transforms as SCNMatrix4 wrapped in NSValue.
@property(readonly, nonatomic, nullable) NSArray<NSValue *> *transforms NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SceneKitTypes.h
//
//  SceneKitTypes.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import <GLKit/GLKMathTypes.h>


/*! @header SceneKitTypes
 @abstract Various types and utility functions used throughout SceneKit
 */

#define SCN_ENABLE_METAL (!TARGET_IPHONE_SIMULATOR)

#if SCN_ENABLE_METAL
#import <Metal/Metal.h>
#endif

typedef struct SCNVector3 {
    float x, y, z;
} SCNVector3;

typedef struct SCNVector4 {
    float x, y, z, w;
} SCNVector4;

typedef struct SCNMatrix4 {
    float m11, m12, m13, m14;
    float m21, m22, m23, m24;
    float m31, m32, m33, m34;
    float m41, m42, m43, m44;
} SCNMatrix4;

typedef SCNVector4 SCNQuaternion;

SCN_EXTERN const SCNMatrix4 SCNMatrix4Identity NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN const SCNVector3 SCNVector3Zero NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN const SCNVector4 SCNVector4Zero NS_AVAILABLE(10_10, 8_0);

/*! Returns true if 'a' is exactly equal to 'b'. */
SCN_EXTERN bool SCNVector3EqualToVector3 (SCNVector3 a, SCNVector3 b);

/*! Returns true if 'a' is exactly equal to 'b'. */
SCN_EXTERN bool SCNVector4EqualToVector4 (SCNVector4 a, SCNVector4 b);

/*! Returns an initialized SCNVector3 */
NS_INLINE SCNVector3 SCNVector3Make(float x, float y, float z) {
    SCNVector3 v = {x, y, z};
    return v;
}

/*! Returns an initialized SCNVector4 */
NS_INLINE SCNVector4 SCNVector4Make(float x, float y, float z, float w) {
    SCNVector4 v = {x, y, z, w};
    return v;
}

NS_INLINE SCNMatrix4 SCNMatrix4MakeTranslation(float x, float y, float z) {
    SCNMatrix4 m = SCNMatrix4Identity;
    m.m41 = x;
    m.m42 = y;
    m.m43 = z;
    return m;
}

NS_INLINE SCNMatrix4 SCNMatrix4MakeScale(float sx, float sy, float sz) {
    SCNMatrix4 m = SCNMatrix4Identity;
    m.m11 = sx;
    m.m22 = sy;
    m.m33 = sz;
    return m;
}

NS_INLINE SCNMatrix4 SCNMatrix4Translate(SCNMatrix4 mat, float x, float y, float z) {
    mat.m41 += x;
    mat.m42 += y;
    mat.m43 += z;
    return mat;
}

SCN_EXTERN SCNMatrix4 SCNMatrix4MakeRotation(float angle, float x, float y, float z) NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN SCNMatrix4 SCNMatrix4Scale(SCNMatrix4 mat, float x, float y, float z) NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN SCNMatrix4 SCNMatrix4Rotate(SCNMatrix4 mat, float angle, float x, float y, float z) NS_AVAILABLE(10_10, 8_0);

SCN_EXTERN SCNMatrix4 SCNMatrix4Invert(SCNMatrix4 mat) NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN SCNMatrix4 SCNMatrix4Mult(SCNMatrix4 matA, SCNMatrix4 matB) NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN bool       SCNMatrix4IsIdentity(SCNMatrix4 mat) NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN bool       SCNMatrix4EqualToMatrix4(SCNMatrix4 matA, SCNMatrix4 matB) NS_AVAILABLE(10_10, 8_0);

/* GLKit bridge */
NS_INLINE SCNVector3 SCNVector3FromGLKVector3(GLKVector3 vector) {
    SCNVector3 v = (SCNVector3){vector.v[0], vector.v[1], vector.v[2]};
    return v;
}

NS_INLINE GLKVector3 SCNVector3ToGLKVector3(SCNVector3 vector) {
    GLKVector3 v = {{(float)vector.x, (float)vector.y, (float)vector.z}};
    return v;
}

NS_INLINE SCNVector4 SCNVector4FromGLKVector4(GLKVector4 vector) {
    SCNVector4 v = (SCNVector4){vector.v[0], vector.v[1], vector.v[2], vector.v[3]};
    return v;
}

NS_INLINE GLKVector4 SCNVector4ToGLKVector4(SCNVector4 vector) {
    GLKVector4 v = {{vector.x, vector.y, vector.z, vector.w}};
    return v;
}

SCN_EXTERN GLKMatrix4 SCNMatrix4ToGLKMatrix4(SCNMatrix4 mat) NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN SCNMatrix4 SCNMatrix4FromGLKMatrix4(GLKMatrix4 mat) NS_AVAILABLE(10_10, 8_0);
    
//SIMD bridge
#import <SceneKit/SceneKit_simd.h>
    
#ifdef __OBJC__
    
NS_ASSUME_NONNULL_BEGIN

/*! @category NSValue(SceneKitAdditions)
 @abstract Adds methods to wrap vectors in NSValue objects.
 */

@interface NSValue (SceneKitAdditions)

+ (NSValue *)valueWithSCNVector3:(SCNVector3)v;
+ (NSValue *)valueWithSCNVector4:(SCNVector4)v;
+ (NSValue *)valueWithSCNMatrix4:(SCNMatrix4)v NS_AVAILABLE(10_10, 8_0);

@property(nonatomic, readonly) SCNVector3 SCNVector3Value;
@property(nonatomic, readonly) SCNVector4 SCNVector4Value;
@property(nonatomic, readonly) SCNMatrix4 SCNMatrix4Value NS_AVAILABLE(10_10, 8_0);

@end

//domain for errors from SceneKit API.
SCN_EXTERN NSString * const SCNErrorDomain;

// NSError codes in SCNErrorDomain.
enum {
	SCNProgramCompilationError = 1
};

NS_ASSUME_NONNULL_END
    
#endif /* __OBJC__ */
// ==========  SceneKit.framework/Headers/SCNRenderer.h
//
//  SCNRenderer.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <SceneKit/SCNSceneRenderer.h>
#import <SceneKit/SCNTechnique.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MTLDevice;
@protocol MTLCommandQueue;
@protocol MTLRenderCommandEncoder;
@class MTLRenderPassDescriptor;

/*! @class SCNRenderer
	@abstract SCNRenderer lets you use the SceneKit renderer in an OpenGL context or Metal render pass descriptor of your own.
 */
NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNRenderer : NSObject <SCNSceneRenderer, SCNTechniqueSupport>

/*! 
 @method rendererWithContext:options:
 @abstract Creates a new renderer object.
 @param context The context to render into.
 @param options An optional dictionary for future extensions.
 */
+ (instancetype)rendererWithContext:(EAGLContext *)context options:(nullable NSDictionary *)options;

/*!
 @method rendererWithDevice:options:
 @abstract Creates a new renderer object that renders using Metal.
 @param device The metal device to use. Pass nil to let SceneKit choose a default device.
 @param options An optional dictionary for future extensions.
 */
+ (instancetype)rendererWithDevice:(nullable id <MTLDevice>)device options:(nullable NSDictionary *)options NS_AVAILABLE(10_11, 9_0);

/*! 
 @property scene
 @abstract Specifies the scene of the receiver
 */
@property(nonatomic, retain, nullable) SCNScene *scene;

/*!
 @method renderAtTime:
 @abstract renders the receiver's scene at the specified time (system time).
 @discussion This method only work if the receiver was allocated with an OpenGL context. Use renderAtTime:withEncoder:pass:commandQueue: to render with Metal.
 */
- (void)renderAtTime:(CFTimeInterval)time NS_AVAILABLE(10_10, 8_0);

/*!
 @method renderAtTime:viewport:commandBuffer:passDescriptor:
 @abstract renders the receiver's scene at the specified time (system time) viewport, metal command buffer and pass descriptor.
 @discussion Use this method to render using Metal.
 */
- (void)renderAtTime:(CFTimeInterval)time viewport:(CGRect)viewport commandBuffer:(id <MTLCommandBuffer>)commandBuffer passDescriptor:(MTLRenderPassDescriptor *)renderPassDescriptor NS_AVAILABLE(10_11, 9_0);

/*!
 @property nextFrameTime
 @abstract Returns the time at which the next update should happen. If infinite no update needs to be scheduled yet. If the current frame time, a continuous animation is running and an update should be scheduled after a "natural" delay.
 */
@property(nonatomic, readonly) CFTimeInterval nextFrameTime NS_AVAILABLE(10_10, 8_0);

/*!
 @method render
 @abstract renders the receiver's scene at the current system time.
 @discussion This method only work if the receiver was allocated with an OpenGL context and it is deprecated (use renderAtIme: instead). Use renderAtTime:withEncoder:pass:commandQueue: to render with Metal.
 */
- (void)render NS_DEPRECATED(10_8, 10_11, 8_0, 9_0);

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNMaterial.h
//
//  SCNMaterial.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
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
     color = <ambient> * al + <diffuse> * max(N . L, 0) + <specular> * pow(max(R . E, 0), <shininess>)
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
     color = <ambient> * al + <diffuse> * max(N . L, 0) + <specular> * pow(max(H . N, 0), <shininess>)
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
     color = <ambient> * al + <diffuse> * max(N . L, 0)
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

SCN_EXTERN NSString * const SCNLightingModelPhong;
SCN_EXTERN NSString * const SCNLightingModelBlinn;
SCN_EXTERN NSString * const SCNLightingModelLambert;
SCN_EXTERN NSString * const SCNLightingModelConstant;

typedef NS_ENUM(NSInteger, SCNCullMode) {
	SCNCullBack  = 0,
	SCNCullFront = 1,
};

typedef NS_ENUM(NSInteger, SCNTransparencyMode) {
	SCNTransparencyModeAOne    = 0, 
	SCNTransparencyModeRGBZero = 1, 
};

/*! 
 @enum SCNBlendMode
 @abstract  Blend modes that SCNMaterial uses to compose with the framebuffer to produce blended colors.
 */
typedef NS_ENUM(NSInteger, SCNBlendMode) {
    SCNBlendModeAlpha        = 0, // Blends the source and destination colors by adding the source multiplied by source alpha and the destination multiplied by one minus source alpha.
    SCNBlendModeAdd          = 1, // Blends the source and destination colors by adding them up.
    SCNBlendModeSubtract     = 2, // Blends the source and destination colors by subtracting the source from the destination.
    SCNBlendModeMultiply     = 3, // Blends the source and destination colors by multiplying them.
    SCNBlendModeScreen       = 4, // Blends the source and destination colors by multiplying one minus the source with the destination and adding the source.
    SCNBlendModeReplace      = 5  // Replaces the destination with the source (ignores alpha).
} NS_ENUM_AVAILABLE(10_11, 9_0);

@class SCNMaterialProperty;
@class SCNProgram;
@protocol SCNProgramDelegate;
@protocol SCNShadable;

/*!
 @class SCNMaterial
 @abstract A SCNMaterial determines how a geometry is rendered. It encapsulates the colors and textures that define the appearance of 3d geometries.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
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
 @property ambientOcclusion
 @abstract The ambientOcclusion property specifies the ambient occlusion of the surface. The ambient occlusion is multiplied with the ambient light, then the result is added to the lighting contribution. This property has no visual impact on scenes that have no ambient light. When an ambient occlusion map is set, the ambient property is ignored.
 */
@property(nonatomic, readonly) SCNMaterialProperty *ambientOcclusion NS_ENUM_AVAILABLE(10_11, 9_0);

/*!
 @property selfIllumination
 @abstract The selfIllumination property specifies a texture or a color that is added to the lighting contribution of the surface. When a selfIllumination is set, the emission property is ignored.
 */
@property(nonatomic, readonly) SCNMaterialProperty *selfIllumination NS_ENUM_AVAILABLE(10_11, 9_0);

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
@property(nonatomic, copy) NSString *lightingModelName;

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
 @property cullMode
 @abstract Determines the culling mode of the receiver. Defaults to SCNCullBack. Animatable.
 */
@property(nonatomic) SCNCullMode cullMode;

/*! 
 @property transparencyMode
 @abstract Determines the transparency mode of the receiver. See above for the transparency modes. Defaults to SCNTransparencyModeAOne.
 @discussion SCNTransparencyModeAOne takes the transparency information from the color's alpha channel. The value 1.0 is opaque. 
 SCNTransparencyModeRGBZero takes the transparency information from the color's red, green, and blue channels. The value 0.0 is opaque, with each channel modulated independently. With SCNTransparencyModeRGBZero, the alpha value of the transparent property is ignored.
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
 @property readsFromDepthBuffer
 @abstract Determines whether the receiver reads from the depth buffer when rendered. Defaults to YES.
 */
@property(nonatomic) BOOL readsFromDepthBuffer NS_AVAILABLE(10_9, 8_0);

/*!
 @property fresnelExponent
 @abstract Specifies the receiver's fresnel exponent value. Defaults to 0.0. Animatable.
 @discussion The effect of the reflectivity property is modulated by this property. The fresnelExponent changes the exponent of the reflectance. The bigger the exponent, the more concentrated the reflection is around the edges.
 */
@property(nonatomic) CGFloat fresnelExponent NS_AVAILABLE(10_9, 8_0);

/*!
 @property blendMode
 @abstract Specifies the receiver's blend mode. Defaults to SCNBlendModeAlpha.
 */
@property(nonatomic) SCNBlendMode blendMode NS_AVAILABLE(10_11, 9_0);

@end
    
NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNJavascript.h
//
//  SCNJavascript.h
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JavaScriptCore/JavaScriptCore.h>

NS_ASSUME_NONNULL_BEGIN

#if JSC_OBJC_API_ENABLED

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

SCN_EXTERN void SCNExportJavaScriptModule(JSContext *context) NS_AVAILABLE(10_10, 8_0);

#endif

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNScene.h
//
//  SCNScene.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>
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
typedef void (^SCNSceneExportProgressHandler)(float totalProgress, NSError * __nullable error, BOOL *stop);


/*! @group Scene writing options */

/*! @constant SCNSceneExportDestinationURL
 @abstract Specifies the final destination (as a NSURL) of the scene being exported.
 @discussion The destination URL is required if the scene is exported to a temporary directory and then moved to a final destination. This enables the exported document to get correct relative paths to referenced images.
 */
SCN_EXTERN NSString * const SCNSceneExportDestinationURL NS_AVAILABLE(10_9, 8_0);


/*! @group Scene attributes
    @abstract These keys can be used with the -[SCNScene attributeForKey:] method.
 */

/*! A floating point value, encapsulated in a NSNumber, containing the start time of the scene. */
SCN_EXTERN NSString * const SCNSceneStartTimeAttributeKey;
/*! A floating point value, encapsulated in a NSNumber, containing the end time of the scene. */
SCN_EXTERN NSString * const SCNSceneEndTimeAttributeKey;
/*! A floating point value, encapsulated in a NSNumber, containing the framerate of the scene. */
SCN_EXTERN NSString * const SCNSceneFrameRateAttributeKey;
/*! A vector3 value, encapsulated in a NSValue, containing the up axis of the scene. This is just for information, setting the up axis as no effect */
SCN_EXTERN NSString * const SCNSceneUpAxisAttributeKey NS_AVAILABLE(10_10, 8_0);

/*!
 @class SCNScene
 @abstract SCNScene is the class that describes a 3d scene. It encapsulates a node hierarchy.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
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
@property(nonatomic, readonly) SCNPhysicsWorld *physicsWorld NS_AVAILABLE(10_10, 8_0);

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
 @discussion The background is rendered before the rest of the scene. The background can be rendered as a skybox by setting a NSArray of six images to its contents (see SCNMaterialProperty.h). Setting a color will have no effect (use SCNView's backgroundColor instead).
 */
@property(nonatomic, readonly) SCNMaterialProperty *background NS_AVAILABLE(10_9, 8_0);


#pragma mark - Loading

/*!
 @method sceneNamed:
 @abstract Creates and returns a scene associated with the specified filename.
 @param name The name of the file. The method looks for a file with the specified name in the application’s main bundle.
 @discussion This method initializes with no options and does not check for errors. The resulting object is not cached.
 */
+ (nullable instancetype)sceneNamed:(NSString *)name NS_AVAILABLE(10_9, 8_0);

/*!
 @method sceneNamed:options:
 @abstract Creates and returns a scene associated with the specified filename.
 @param name The name of the file. The method looks for a file with the specified name in the application’s main bundle.
 @param directory The name of the bundle sub-directory to search into.
 @param options An options dictionary. The relevant keys are documented in the SCNSceneSource class.
 @discussion This method initializes with no options and does not check for errors. The resulting object is not cached.
 */
+ (nullable instancetype)sceneNamed:(NSString *)name inDirectory:(nullable NSString *)directory options:(nullable NSDictionary<NSString *, id> *)options NS_AVAILABLE(10_10, 8_0);

/*!
 @method sceneWithURL:options:error:
 @abstract Creates and returns a scene from the specified URL.
 @param url The URL to the 3D file.
 @param options An options dictionary. The relevant keys are documented in the SCNSceneSource class.
 @param error A NSError object passed by reference to get more information about the error when a nil is returned.
 @discussion This method is here for convenience. It is equivalent to initializing a SCNSceneSource with the specified
 url and options, and asking it for its scene with the same options.
 */
+ (nullable instancetype)sceneWithURL:(NSURL *)url options:(nullable NSDictionary<NSString *, id> *)options error:(NSError **)error;


#pragma mark - Fog

/*!
 @property fogStartDistance
 @abstract Specifies the receiver's fog start distance. Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat fogStartDistance NS_AVAILABLE(10_10, 8_0);

/*!
 @property fogEndDistance
 @abstract Specifies the receiver's fog end distance. Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat fogEndDistance NS_AVAILABLE(10_10, 8_0);

/*!
 @property fogDensityExponent
 @abstract Specifies the receiver's fog power exponent. Animatable. Defaults to 1.
 @discussion Controls the attenuation between the start and end fog distances. 0 means a constant fog, 1 a linear fog and 2 a quadratic fog, but any positive value will work.
 */
@property(nonatomic) CGFloat fogDensityExponent NS_AVAILABLE(10_10, 8_0);

/*!
 @property fogColor
 @abstract Specifies the receiver's fog color (NSColor or CGColorRef). Animatable. Defaults to white.
 @discussion The initial value is a NSColor.
 */
@property(nonatomic, retain) id fogColor NS_AVAILABLE(10_10, 8_0);


#pragma mark - Pause

/*!
 @property paused
 @abstract Controls whether or not the scene is paused. Defaults to NO.
 @discussion Pausing a scene will pause animations, actions, particles and physics.
 */
@property(nonatomic, getter=isPaused) BOOL paused NS_AVAILABLE(10_10, 8_0);


@end


NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNSkinner.h
//
//  SCNSkinner.h
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class SCNSkinner
 @abstract SCNSkinner controls the deformation of skinned geometries */

NS_CLASS_AVAILABLE(10_9, 8_0)
@interface SCNSkinner : NSObject <NSSecureCoding>

/*!
 @property skeleton
 @abstract Specifies the skeleton of the receiver.
 @discussion When setting a new skeleton, the new skeleton must have the same hierarchy of joints.
 */
@property(nonatomic, retain, nullable) SCNNode *skeleton;

/*!
 @method skinnerWithBaseGeometry:bones:boneInverseBindTransforms:boneWeights:boneIndices:
 @abstract Creates and initialize a skinner instance with the specified parameters.
 @param baseGeometry Specifies the base geometry used by the skinner
 @param bones Specifies the array of bones.
 @param boneInverseBindTransforms The inverse of the bone’s bind-space transformation matrix at the time the bind shape was bound to this bone.
 @param boneWeights A buffer of weights. This contains the weights of every influence of every vertex. The number of influence per vertex is controlled by the number of component in the geometry source.
 @param boneIndices A buffer of bone indexes. This buffer contains the corresponding index in the bones array for every weight in the weights buffer.
 */
+ (instancetype)skinnerWithBaseGeometry:(nullable SCNGeometry *)baseGeometry bones:(NSArray<SCNNode *> *)bones boneInverseBindTransforms:(nullable NSArray<NSValue *> *)boneInverseBindTransforms boneWeights:(SCNGeometrySource *)boneWeights boneIndices:(SCNGeometrySource *)boneIndices NS_AVAILABLE(10_10, 8_0);

/*!
 @property baseGeometry
 @abstract Specifies the base geometry of the receiver.
 @discussion Updating this will change the geometry of all the nodes sharing the skinner.
 Access the node's geometry if you want to update this specific skinner properties (materials for example).
 Access this property if you want a whole new geometry (which will necessarily be shared among the skinner instances), with
 different sources, for instance.
 */
@property(retain, nonatomic, nullable) SCNGeometry *baseGeometry NS_AVAILABLE(10_9, 8_0);

/*!
 @property baseGeometryBindTransform
 @abstract Specifies the transform of the baseGeometry at the time when the mesh was bound to a skeleton. This transforms the baseGeometry from object space to a space on which the skinning then applies.
 */
@property(nonatomic) SCNMatrix4 baseGeometryBindTransform NS_AVAILABLE(10_10, 8_0);

/*!
 @property boneInverseBindTransforms
 @abstract The inverse of the bone’s bind-space transformation matrix at the time the bind shape was bound to this bone.
 @discussion boneInverseBindTransforms is an array of SCNMatrix4 wrapped into instances of NSValue.
 */
@property(readonly, nonatomic, nullable) NSArray<NSValue *> *boneInverseBindTransforms NS_AVAILABLE(10_10, 8_0);

/*!
 @property bones
 @abstract The bones of the skinner.
 */
@property(readonly, nonatomic) NSArray<SCNNode *> *bones NS_AVAILABLE(10_10, 8_0);

/*!
 @property boneWeights
 @abstract The bone weights of the receiver.
 */
@property(readonly, nonatomic) SCNGeometrySource *boneWeights NS_AVAILABLE(10_10, 8_0);

/*!
 @property boneIndices
 @abstract The bone indices of the receiver.
 */
@property(readonly, nonatomic) SCNGeometrySource *boneIndices NS_AVAILABLE(10_10, 8_0);

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNConstraint.h
//
//  SCNConstraint.h
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

/*!
 @class SCNConstraint
 @abstract A SCNConstraint is an abstract class that represents a single constraint that can be applied to a node.
 */

NS_CLASS_AVAILABLE(10_9, 8_0)
@interface SCNConstraint : NSObject <NSCopying, NSSecureCoding, SCNAnimatable>

/*!
 @property influenceFactor
 @abstract Specifies the inflence factor of the receiver. Defaults to 1. Animatable
 */
@property(nonatomic) CGFloat influenceFactor NS_AVAILABLE(10_10, 8_0);

@end

/*!
 @class SCNLookAtConstraint
 @abstract A SCNLookAtConstraint applies on a node's orientation so that it always look at another node.
 */

NS_CLASS_AVAILABLE(10_9, 8_0)
@interface SCNLookAtConstraint : SCNConstraint

/*!
 @method lookAtConstraintWithTarget:
 @abstract Creates and returns a SCNLookAtConstraint object with the specified target.
 @param target The target node to look at.
 */
+ (instancetype)lookAtConstraintWithTarget:(SCNNode *)target;

/*!
 @property target
 @abstract Defines the target node to look at.
 */
@property(nonatomic, readonly) SCNNode *target;

/*!
 @property gimbalLockEnabled
 @abstract Specifies whether the receiver enables the gimbal lock. Defaults to NO.
 @discussion Enabling the gimbal lock prevents the receiver from rotating the constrained node around to roll axis.
 */
@property(nonatomic) BOOL gimbalLockEnabled;

@end

typedef NS_OPTIONS(NSUInteger, SCNBillboardAxis) {
    SCNBillboardAxisX = 0x1 << 0,
    SCNBillboardAxisY = 0x1 << 1,
    SCNBillboardAxisZ = 0x1 << 2,
    SCNBillboardAxisAll = SCNBillboardAxisX | SCNBillboardAxisY | SCNBillboardAxisZ
};

NS_CLASS_AVAILABLE(10_11, 9_0)
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

/*!
 @class SCNTransformConstraint
 @abstract A SCNTransformConstraint applies on the transform of a node via a custom block.
 */
NS_CLASS_AVAILABLE(10_9, 8_0)
@interface SCNTransformConstraint : SCNConstraint

/*!
 @method transformConstraintInWorldSpace:withBlock:
 @abstract Creates and returns a SCNTransformConstraint object with the specified parameters.
 @param world Determines whether the constraint is evaluated in world or local space.
 @param block The custom block to call to evaluate the constraint.
 @discussion The node and its transform are passed to the block. The transform returned by the block will be used to render the node.
 */
+ (instancetype)transformConstraintInWorldSpace:(BOOL)world withBlock:(SCNMatrix4 (^)(SCNNode *node, SCNMatrix4 transform))block;

@end


/*!
 @class SCNIKConstraint
 @abstract A SCNIKConstraint applies an inverse kinematics constraint
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface SCNIKConstraint : SCNConstraint

/*!
 @method initWithChainRootNode:
 @abstract Creates and returns a SCNIKConstraint object with the specified parameter.
 @param chainRootNode The root node of the kinematic chain.
 @discussion "chainRootNode" must be an ancestor of the node on which the constraint is applied.
 */
- (instancetype)initWithChainRootNode:(SCNNode *)chainRootNode NS_AVAILABLE(10_11, 9_0);

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

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNNode.h
//
//  SCNNode.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNBoundingVolume.h>
#import <SceneKit/SCNAction.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNLight;
@class SCNCamera;
@class SCNGeometry;
@class SCNSkinner;
@class SCNMorpher;
@class SCNConstraint;
@class SCNPhysicsBody;
@class SCNPhysicsField;
@class SCNPhysicsBody;

@protocol SCNNodeRendererDelegate;

/*! @group Rendering arguments
    @discussion These keys are used in the 'arguments' dictionary of renderNode:renderer:arguments:
				and in the 'semantic' argument of -[SCNProgram setSemantic:forSymbol:options:].
                Transforms are SCNMatrix4 wrapped in NSValues.
 */
SCN_EXTERN NSString * const SCNModelTransform;
SCN_EXTERN NSString * const SCNViewTransform;
SCN_EXTERN NSString * const SCNProjectionTransform;
SCN_EXTERN NSString * const SCNNormalTransform;
SCN_EXTERN NSString * const SCNModelViewTransform;
SCN_EXTERN NSString * const SCNModelViewProjectionTransform;

/*!
 @class SCNNode
 @abstract SCNNode is the model class for node-tree objects.
 @discussion It encapsulates the position, rotations, and other transforms of a node, which define a coordinate system.
		     The coordinate systems of all the sub-nodes are relative to the one of their parent node.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNNode : NSObject <NSCopying, NSSecureCoding, SCNAnimatable, SCNActionable, SCNBoundingVolume>

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
- (instancetype)flattenedClone NS_AVAILABLE(10_9, 8_0);



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
@property(nonatomic, retain, nullable) SCNSkinner *skinner NS_AVAILABLE(10_9, 8_0);

/*!
 @property morpher
 @abstract Returns the morpher attached to the receiver.
 */
@property(nonatomic, retain, nullable) SCNMorpher *morpher NS_AVAILABLE(10_9, 8_0);



#pragma mark - Modifying the Node's Transform

/*! 
 @property transform
 @abstract Determines the receiver's transform. Animatable.
 @discussion The transform is the combination of the position, rotation and scale defined below. So when the transform is set, the receiver's position, rotation and scale are changed to match the new transform.
 */
@property(nonatomic) SCNMatrix4 transform;

/*! 
 @property position
 @abstract Determines the receiver's position. Animatable.
 */
@property(nonatomic) SCNVector3 position;

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
@property(nonatomic) SCNQuaternion orientation NS_AVAILABLE(10_10, 8_0);

/*!
 @property eulerAngles
 @abstract Determines the receiver's euler angles. Animatable.
 @dicussion Specify the intrinsic euler angles (in radians). It represents a sequence of 3 rotations about the x, y, and z axis with the following order: z, y, x (or roll, yaw, pitch).
 */
@property(nonatomic) SCNVector3 eulerAngles NS_AVAILABLE(10_10, 8_0);

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

/*! 
 @property worldTransform
 @abstract Returns the receiver's world transform.
 @discussion A world transform is the transform relative to the scene. 
 */
@property(nonatomic, readonly) SCNMatrix4 worldTransform;



#pragma mark - Modifying the Node's Visibility

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
@property(nonatomic) BOOL castsShadow NS_AVAILABLE(10_10, 8_0);


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
- (NSArray<SCNNode *> *)childNodesPassingTest:(BOOL (^)(SCNNode *child, BOOL *stop))predicate;

/*!
 @method enumerateChildNodesUsingBlock:
 @abstract Executes a given block using each child node under the receiver.
 @discussion The search is recursive and uses a pre-order tree traversal.
 @param block The block to apply to child nodes of the receiver. The block takes two arguments: "child" is a child node and "stop" is a reference to a Boolean value. The block can set the value to YES to stop further processing of the node hierarchy. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 */
- (void)enumerateChildNodesUsingBlock:(void (^)(SCNNode *child, BOOL *stop))block NS_AVAILABLE(10_10, 8_0);


#pragma mark - Converting Between Node Coordinate Systems

/*!
 @method convertPosition:toNode:
 @abstract Converts a position from the receiver’s coordinate system to that of the specified node.
 @param position A position specified in the local coordinate system of the receiver.
 @param node The node into whose coordinate system "position" is to be converted. If "node" is nil, this method instead converts to world coordinates.
 */
- (SCNVector3)convertPosition:(SCNVector3)position toNode:(nullable SCNNode *)node NS_AVAILABLE(10_9, 8_0);

/*!
 @method convertPosition:fromNode:
 @abstract Converts a position from the coordinate system of a given node to that of the receiver.
 @param position A position specified in the local coordinate system of "node".
 @param node The node from whose coordinate system "position" is to be converted. If "node" is nil, this method instead converts from world coordinates.
 */
- (SCNVector3)convertPosition:(SCNVector3)position fromNode:(nullable SCNNode *)node NS_AVAILABLE(10_9, 8_0);

/*!
 @method convertTransform:toNode:
 @abstract Converts a transform from the receiver’s coordinate system to that of the specified node.
 @param transform A transform specified in the local coordinate system of the receiver.
 @param node The node into whose coordinate system "transform" is to be converted. If "node" is nil, this method instead converts to world coordinates.
 */
- (SCNMatrix4)convertTransform:(SCNMatrix4)transform toNode:(nullable SCNNode *)node NS_AVAILABLE(10_9, 8_0);

/*!
 @method convertTransform:fromNode:
 @abstract Converts a transform from the coordinate system of a given node to that of the receiver.
 @param transform A transform specified in the local coordinate system of "node".
 @param node The node from whose coordinate system "transform" is to be converted. If "node" is nil, this method instead converts from world coordinates.
 */
- (SCNMatrix4)convertTransform:(SCNMatrix4)transform fromNode:(nullable SCNNode *)node NS_AVAILABLE(10_9, 8_0);


#pragma mark - Managing the SCNNode's physics body

/*!
 @property physicsBody
 @abstract The description of the physics body of the receiver.
 @discussion Default is nil.
 */
@property(nonatomic, retain, nullable) SCNPhysicsBody *physicsBody NS_AVAILABLE(10_10, 8_0);


#pragma mark - Managing the Node's Physics Field

/*!
 @property physicsField
 @abstract The description of the physics field of the receiver.
 @discussion Default is nil.
 */
@property(nonatomic, retain, nullable) SCNPhysicsField *physicsField NS_AVAILABLE(10_10, 8_0);


#pragma mark - Managing the Node's Constraints

/*!
 @property constraints
 @abstract An array of SCNConstraint that are applied to the receiver.
 @discussion Adding or removing a constraint can be implicitly animated based on the current transaction.
 */
@property(copy, nullable) NSArray<SCNConstraint *> *constraints NS_AVAILABLE(10_9, 8_0);



#pragma mark - Accessing the Node's Filters

/*!
 @property filters
 @abstract An array of Core Image filters that are applied to the rendering of the receiver and its child nodes. Animatable.
 @discussion Defaults to nil. Filter properties should be modified by calling setValue:forKeyPath: on each node that the filter is attached to. If the inputs of the filter are modified directly after the filter is attached to a node, the behavior is undefined.
 */
@property(nonatomic, copy, nullable) NSArray<CIFilter *> *filters NS_AVAILABLE(10_9, 8_0);



#pragma mark - Accessing the Presentation Node

/*!
 @method presentationNode
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
@property(nonatomic, getter=isPaused) BOOL paused NS_AVAILABLE(10_10, 8_0);


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
- (NSArray<SCNHitTestResult *> *)hitTestWithSegmentFromPoint:(SCNVector3)pointA toPoint:(SCNVector3)pointB options:(nullable NSDictionary<NSString *, id> *)options NS_AVAILABLE(10_9, 8_0);


#pragma mark - Categories

/*!
 @property categoryBitMask
 @abstract Defines what logical 'categories' the receiver belongs too. Defaults to 1.
 @discussion Categories can be used to exclude nodes from the influence of a given light (see SCNLight's categoryBitMask). It can also be used to include/exclude nodes from render passes (see SCNTechnique.h).
 */
@property(nonatomic) NSUInteger categoryBitMask NS_AVAILABLE(10_10, 8_0);

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
 @param arguments A dictionary that can have any of the entries described at the beginning of this file.
 */
- (void)renderNode:(SCNNode *)node renderer:(SCNRenderer *)renderer arguments:(NSDictionary<NSString *, NSValue *> *)arguments;

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNSceneSource.h
//
//  SCNSceneSource.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNScene;

/*! @group Scene source properties */
/*! File contributors. The values are dictionaries populated with keys documented in the "Contributor dictionary keys" group. */
SCN_EXTERN NSString * const SCNSceneSourceAssetContributorsKey;
/*! When the file was created. The value is a NSDate instance. */
SCN_EXTERN NSString * const SCNSceneSourceAssetCreatedDateKey;
/*! When the file was last modified. The value is a NSDate instance. */
SCN_EXTERN NSString * const SCNSceneSourceAssetModifiedDateKey;
/*! The up axis of the file. If the file is oriented Y-up, for example, then this is the string \@"0.0 1.0 0.0" */
SCN_EXTERN NSString * const SCNSceneSourceAssetUpAxisKey;
/*! The unit used in the file. The value is a dictionary populated with keys documented in the "Unit dictionary keys" group. */
SCN_EXTERN NSString * const SCNSceneSourceAssetUnitKey;

/*! @group Contributor dictionary keys */
/*! Authoring tool used to create the file. The corresponding value is an NSString. */
SCN_EXTERN NSString * const SCNSceneSourceAssetAuthoringToolKey;
/*! The file's author. The corresponding value is an NSString. */
SCN_EXTERN NSString * const SCNSceneSourceAssetAuthorKey;

/*! @group Unit dictionary keys */
/*! The name (NSString) of the unit */
SCN_EXTERN NSString * const SCNSceneSourceAssetUnitNameKey;
/*! A NSNumber encapsulating a floating-point value indicating how many meters the unit is. For example, if the name is \@"centimeter", then this will be 0.01. */
SCN_EXTERN NSString * const SCNSceneSourceAssetUnitMeterKey;

/*! @group Scene loading options */

/*! @constant SCNSceneSourceCreateNormalsIfAbsentKey
	@abstract Enable to try to guess acceptable normals for the vertices if none are given in the file
    @discussion Use this with a boolean value encapsulated in a NSNumber. The default value is NO.
 */
SCN_EXTERN NSString * const SCNSceneSourceCreateNormalsIfAbsentKey;

/*!
 @constant SCNSceneSourceCheckConsistencyKey
 @abstract Pass YES in order to perform the document validation. 
 @discussion This option can be set in the options dictionary of the SCNScene and SCNSceneSource loading methods.
 The value for this option should be a boolean NSNumber. If its boolean value is YES (the default is NO),
 SceneKit will attempt to check the document for consistency.
 If the document doesn't pass the consistency check it is then not loaded and an error is returned.
 This is slower, but for security reasons it should be set to YES if you are not sure the files you load are valid and have not been tampered with. 
 */
SCN_EXTERN NSString * const SCNSceneSourceCheckConsistencyKey;

/*!
 @constant SCNSceneSourceFlattenSceneKey
 @abstract Pass YES to flatten the scene graph when possible.
 @discussion This option can be set in the options dictionary of the SCNScene and SCNSceneSource loading methods.
 The value for this option should be a boolean NSNumber. If its boolean value is YES (the default is NO),
 SceneKit will attempt to reduce the scene graph by merging the geometries.
 This option is suitable to preview a 3D scene efficiently and when manipulating the scene graph is not needed.
 */
SCN_EXTERN NSString * const SCNSceneSourceFlattenSceneKey;

/*!
 @constant SCNSceneSourceUseSafeModeKey
 @abstract Pass YES in order to enable the safe mode.
 @discussion This option can be set in the options dictionary of the SCNScene and SCNSceneSource loading methods.
 The value for this option should be a boolean NSNumber. If its boolean value is YES (the default is NO),
 SceneKit will forbid network accesses, prevent the loading of resources from arbitrary directories, and will not execute
 any code present in the loaded files.
 */
SCN_EXTERN NSString * const SCNSceneSourceUseSafeModeKey;

/*!
 @constant SCNSceneSourceAssetDirectoryURLsKey
 @abstract Pass an array of directory URLs where SceneKit should look for resources
 @discussion By default, SceneKit will look for the external resources it cannot find in the parent directory of the imported file.
 You can add additional directories by setting an array of URLs for this key when calling sceneWithOptions:error:.
 This is recommended if you want to construct your scene source from a data object, not from an URL,
 and need to load resources whose paths are not absolute.
 */
SCN_EXTERN NSString * const SCNSceneSourceAssetDirectoryURLsKey;

/*!
 @constant SCNSceneSourceOverrideAssetURLsKey
 @abstract Pass YES in order to override assets URLs with the directory URLs passed via SCNSceneSourceAssetDirectoryURLsKey.
 @discussion By default, SceneKit will look for the external resources using the paths/urls as described in the imported file.
 You can force SceneKit to only search for extern resources within the directories specified by the SCNSceneSourceAssetDirectoryURLsKey key.
 This can be useful to load a file and its resources from a specific bundle for instance.
 */
SCN_EXTERN NSString * const SCNSceneSourceOverrideAssetURLsKey;

/*!
 @constant SCNSceneSourceStrictConformanceKey
 @abstract Pass YES to interpret the 3D format of the file in a strict way.
 @discussion This option defaults to NO. In this case SceneKit will try to read any additional metadata present in the file to
			 enable additional features and make the rendering as close as possible to the original intent. If you pass YES,
             SceneKit will instead only consider features which are part of the file format specification.
 */
SCN_EXTERN NSString * const SCNSceneSourceStrictConformanceKey;

/*!
 @constant SCNSceneSourceConvertUnitsToMetersKey
 @abstract Pass the units you want the scene to be converted to (in meter).
 @discussion Use this with a floating value encapsulated in a NSNumber. The default value is nil which means no conversion done. Passing a non-zero value will convert the scene coordinates so that 1 unit corresponds to N meters. For example pass 0.01 for 1 unit == 1 centimeter, pass 0.3048 for 1 unit == 1 foot...
     For better physics simulation it is recommended to use 1 unit equals to 1 meter.
     This option has no effect if the asset is already compressed by Xcode (use the compression options instead).
 */
SCN_EXTERN NSString * const SCNSceneSourceConvertUnitsToMetersKey NS_AVAILABLE(10_10, NA);

/*!
 @constant SCNSceneSourceConvertToYUpKey
 @abstract Pass YES if a scene should be converted to Y up if it currently has a different up axis.
 @discussion Use this with a boolean value encapsulated in a NSNumber. The default value is NO.
 This option has no effect if the asset is already compressed by Xcode (use the compression options instead).
 */
SCN_EXTERN NSString * const SCNSceneSourceConvertToYUpKey NS_AVAILABLE(10_10, NA);

/*!
 @constant SCNSceneSourceAnimationImportPolicyKey
 @abstract Pass one of the value below to specify what to do with loaded animations.
 @discussion See below for the description of each individual key. Defaults to SCNSceneSourceAnimationImportPolicyPlayRepeatedly. On 10.9 and before the behavior is SCNSceneSourceAnimationImportPolicyPlayUsingSceneTimeBase. For compatibility reason if the application was built on 10.9 or before the default behavior is SCNSceneSourceAnimationImportPolicyPlayUsingSceneTimeBase.
 */
SCN_EXTERN NSString * const SCNSceneSourceAnimationImportPolicyKey NS_AVAILABLE(10_10, 8_0);

/* values for SCNSceneSourceAnimationImportPolicyKey */
/*!
 @constant SCNSceneSourceAnimationImportPolicyPlay
 @abstract Add animations to the scene and play them once (repeatCount set to 1).
 */
SCN_EXTERN NSString * const SCNSceneSourceAnimationImportPolicyPlay NS_AVAILABLE(10_10, 8_0);
/*!
 @constant SCNSceneSourceAnimationImportPolicyPlayRepeatedly
 @abstract Add animations to the scene and play them repeatedly (repeatCount set to infinity).
 */
SCN_EXTERN NSString * const SCNSceneSourceAnimationImportPolicyPlayRepeatedly NS_AVAILABLE(10_10, 8_0);
/*!
 @constant SCNSceneSourceAnimationImportPolicyDoNotPlay
 @abstract Only keep animations in the SCNSceneSource and don't add to the animatable elements of the scene.
 */
SCN_EXTERN NSString * const SCNSceneSourceAnimationImportPolicyDoNotPlay NS_AVAILABLE(10_10, 8_0);
/*!
 @constant SCNSceneSourceAnimationImportPolicyPlayUsingSceneTimeBase
 @abstract Add animations to the scene and play them using the SCNView/SCNRenderer's scene time (usesSceneTimeBase set to YES)
 */
SCN_EXTERN NSString * const SCNSceneSourceAnimationImportPolicyPlayUsingSceneTimeBase NS_AVAILABLE(10_10, 8_0);

/*!
 @constant SCNDetailedErrorsKey
 @abstract Key to access the detailed validation errors.
 @discussion This key will be present in the user info dictionary of errors created by the various sceneWithOptions: methods.
             When present, the value associated with it is an array of detailed errors found by the consistency checker
             which represent consistency errors in the 3D file. Some metadata about these detailed errors is available
             in their user info dictionary using the other keys (SCNConsistency*) defined in this file.
 */

SCN_EXTERN NSString * const SCNDetailedErrorsKey;

/*!
 @constant SCNConsistencyElementIDErrorKey
 @abstract For XML-based formats, the ID of the element where the error occurred.
 @discussion When the element does not have an ID, the ID of the closest parent element which has one is returned.
 */

SCN_EXTERN NSString * const SCNConsistencyElementIDErrorKey;

/*!
 @constant SCNConsistencyElementTypeErrorKey
 @abstract For XML-based formats, the tag name of the element where the error occurred.
 */

SCN_EXTERN NSString * const SCNConsistencyElementTypeErrorKey;

/*!
 @constant SCNConsistencyLineNumberErrorKey
 @abstract For text-based formats, the line number where an error occurred.
 */

SCN_EXTERN NSString * const SCNConsistencyLineNumberErrorKey;

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

typedef void (^SCNSceneSourceStatusHandler)(float totalProgress, SCNSceneSourceStatus status, NSError * __nullable error, BOOL *stop);


/*!
 @class SCNSceneSource
 @abstract SCNSceneSource objects, abstract the data-reading task. A scene source can read scene data from a URL or a NSData object.
 After creating a SCNSceneSource object for the appropriate source, you can obtain scenes using SCNSceneSource methods.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNSceneSource : NSObject 

/*!
 @method sceneSourceWithURL:options:
 @abstract Creates and initialize a SCNSceneSource instance.
 @param url The URL to read scenes from.
 @param options An optional dictionary for future extensions. 
 */
+ (nullable instancetype)sceneSourceWithURL:(NSURL *)url options:(nullable NSDictionary<NSString *, id> *)options;

/*!
 @method sceneSourceWithData:options:
 @abstract Creates and initialize a SCNSceneSource instance.
 @param data The scene data.
 @param options An optional dictionary for future extensions. 
 */
+ (nullable instancetype)sceneSourceWithData:(NSData *)data options:(nullable NSDictionary<NSString *, id> *)options;

/*!
 @method initWithURL:options:
 @abstract Initialize a SCNSceneSource instance from a URL.
 @param url The URL to read scenes from.
 @param options An optional dictionary for future extensions. 
 */
- (nullable instancetype)initWithURL:(NSURL *)url options:(nullable NSDictionary<NSString *, id> *)options;

/*!
 @method initWithData:options:
 @abstract Initialize a SCNSceneSource instance from a NSData object.
 @param data The data to read scenes from.
 @param options An optional dictionary for future extensions. 
 */
- (nullable instancetype)initWithData:(NSData *)data options:(nullable NSDictionary<NSString *, id> *)options;

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
- (nullable SCNScene *)sceneWithOptions:(nullable NSDictionary<NSString *, id> *)options statusHandler:(nullable SCNSceneSourceStatusHandler)statusHandler;

/*!
 @method sceneWithOptions:error:
 @abstract Creates and initializes the scene described in the 3D file with the specified options.
 @param options A dictionary of options. The valid keys are described in the "Scene loading options" section.
 @param error If this method returns nil, an error providing more information is returned by reference.
 @discussion This simpler version is equivalent to providing a block to sceneWithOptions:statusHandler: and checking the "error"
 parameter of the block if the status is SCNSceneStatusError.
 */
- (nullable SCNScene *)sceneWithOptions:(nullable NSDictionary<NSString *, id> *)options error:(NSError **)error;

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
#if defined(SWIFT_SDK_OVERLAY2_SCENEKIT_EPOCH) && SWIFT_SDK_OVERLAY2_SCENEKIT_EPOCH >= 1
- (nullable id)entryWithIdentifier:(NSString *)uid withClass:(Class)entryClass NS_REFINED_FOR_SWIFT;
#else
- (nullable id)entryWithIdentifier:(NSString *)uid withClass:(Class)entryClass;
#endif

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
- (NSArray<id> *)entriesPassingTest:(BOOL (^)(id entry, NSString *identifier, BOOL *stop))predicate NS_AVAILABLE(10_9, 8_0);

@end

NS_ASSUME_NONNULL_END
// ==========  SceneKit.framework/Headers/SCNView.h
//
//  SCNView.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <SceneKit/SCNSceneRenderer.h>
#import <SceneKit/SCNTechnique.h>

NS_ASSUME_NONNULL_BEGIN

/*! 
 @enum SCNAntialiasingMode
 @abstract antialiasing modes for SCNView
 */
typedef NS_ENUM(NSUInteger, SCNAntialiasingMode) {
    SCNAntialiasingModeNone,
    SCNAntialiasingModeMultisampling2X,
    SCNAntialiasingModeMultisampling4X
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*! @group View initialization options
 @constant SCNPreferredRenderingAPIKey Specifies the preferred rendering API to be used by the renderer.
 @discussion Pass it as the key in the options dictionary given to initWithFrame:options:. The value is a NSNumber wrapping a SCNRenderingAPI. You can also select the preferred rendering API directly from the SCNView inspector in InterfaceBuilder.
 */
SCN_EXTERN NSString * const SCNPreferredRenderingAPIKey NS_AVAILABLE(10_11, 9_0);

/*!
 @constant SCNPreferredDeviceKey Specifies the preferred metal device to be used by the renderer.
 @discussion The value is directly a id <MTLDevice>.
 */
SCN_EXTERN NSString * const SCNPreferredDeviceKey NS_AVAILABLE(10_11, 9_0);

/*!
 @constant SCNPreferLowPowerDeviceKey Specifies if the renderer should prefer a low power metal device.
 @discussion The value is a NSNumber wrapping a BOOL. Defaults to NO.
 */
SCN_EXTERN NSString * const SCNPreferLowPowerDeviceKey NS_AVAILABLE(10_11, 9_0);

/*!
 @class SCNView
 @abstract A SCNView is a subclass of NSView that can display a SCNScene
 */
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
 @property allowsCameraControl
 @abstract A Boolean value that determines whether the user can manipulate the point of view used to render the scene. 
 @discussion  When set to YES, the user can manipulate the current point of view with the mouse or the trackpad. The scene graph and existing cameras won't be modified by this action. The default value of this property is NO.
     Note that the primary purpose of this property is to aid in debugging your application. You may want to implement you own camera controller suitable for your application.
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
 @property snapshot
 @abstract Draws the contents of the view and returns them as a new image object
 @discussion This method is thread-safe and may be called at any time.
 */
- (UIImage *)snapshot NS_AVAILABLE(10_10, 8_0);

/*! 
 @functiongroup Actions
 */
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
 The default value is 60 frames per second.
 */
@property(nonatomic) NSInteger preferredFramesPerSecond;

/*!
 @property eaglContext
 @abstract Specifies the EAGL context associated with the receiver.
 @discussion This property returns nil and has no effect if the current API is Metal.
 */
@property(nonatomic, retain, nullable) EAGLContext *eaglContext;


/*!
 @property antialiasingMode
 @abstract Defaults to SCNAntialiasingModeMultisampling4X on OSX and SCNAntialiasingModeNone on iOS.
 */
@property(nonatomic) SCNAntialiasingMode antialiasingMode NS_AVAILABLE(10_10, 8_0);


@end

NS_ASSUME_NONNULL_END
