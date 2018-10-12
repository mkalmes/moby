// ==========  GameplayKit.framework/Headers/GKRandomDistribution.h
//
//  GKRandomDistribution.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <GameplayKit/GKRandomSource.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A random distribution is a random source itself with a specific mapping from the input source to the output values.
 * The distribution is uniform, meaning there is no bias towards any of the possible outcomes.
 */
GK_BASE_AVAILABILITY @interface GKRandomDistribution : NSObject<GKRandom>

/**The lowest value the distribution will output.*/
@property (nonatomic, assign, readonly) NSInteger lowestValue;
/**The highest value the distribution will output.*/
@property (nonatomic, assign, readonly) NSInteger highestValue;
/**The number of unique possible outcomes, depending on the distribution type this is not always highest - lowest + 1.*/
@property (nonatomic, assign, readonly) NSUInteger numberOfPossibleOutcomes;

/**Initializes a random distribution within the range [lowest, highest] using a source to grab input values from.*/
- (instancetype)initWithRandomSource:(id<GKRandom>)source lowestValue:(NSInteger)lowestInclusive highestValue:(NSInteger)highestInclusive NS_DESIGNATED_INITIALIZER;

/**
 * Returns the next integer in the distribution sequence and moves ahead to the next one.
 * The value is in the range of [lowest, highest].
 */
- (NSInteger)nextInt;

/**
 * Returns the next unsigned value in the distribution sequence that is less than upperBound.
 * The value never equals or exceeeds upperBounds, and in this case it will also never exceed
 * the highest value of the distribution.
 */
- (NSUInteger)nextIntWithUpperBound:(NSUInteger)upperBound;

/**
 * Returns the next uniform float in the random sequence and moves ahead to the next one.
 * The value is in the range of [lowest / higest, 1.0].
 * 
 * The value is quantized to the distribution's lowest and highest bounds. Thus on a d20
 * distribution the value is quantized to 5% increments. The output value 0 is not possible
 * to get unless the lowest value bound is also 0 or below.
 *
 * @see nextInt
 */
- (float)nextUniform;

/**
 * Returns the next true or false value in the distribution sequence and moves ahead to the next one.
 * The value is either nonzero (true) or zero (false).
 * Use this for simple boolean switches in logic that don't require fuzzy evaluation.
 * For fuzzy evaluation use nextUniform.
 *
 * By default this is based on the referenced source's definition of nextBool.
 * 
 * @see GKRandomSource.nextBool
 */
- (BOOL)nextBool;


/**
 * Convenience creation of random distribution within the range [lowest, highest] using an isolated source to grab input values from.
 * This is equivalent to calling alloc followed by initWithSource:lowest:highest:, where source is [[GKRandomSource alloc] init].
 * @see initWithRandomSource:lowestValue:highestValue:
 */
+ (instancetype)distributionWithLowestValue:(NSInteger)lowestInclusive highestValue:(NSInteger)highestInclusive;

/**
 * Convenience creation of random distribution with the die like range [1, sideCount] using an isolated source to grab input values from.
 * This is equivalent to calling alloc followed by initWithSource:lowest:highest:, where source is [[GKRandomSource alloc] init].
 * @see initWithRandomSource:lowestValue:highestValue:
 */
+ (instancetype)distributionForDieWithSideCount:(NSInteger)sideCount;

/**
 * Convenience creation for the very common d6 range [1, 6] with an isolated random source
 * shielded from outside sources.
 */
+ (instancetype)d6;

/**
 * Convenience creation for the very common d20 range [1, 20] with an isolated random source
 * shielded from outside sources.
 */
+ (instancetype)d20;

@end


/**
 * A gaussian distribution is biased towards the mean value, the possible outcomes are spread out from the mean
 * with decreasing probability. Values within 1 deviation of the mean make up 68.27% of the distribution, values
 * within 2 deviations make up 95% and values within 3 deviations make up 99.7%.
 *
 * Note that a gaussian distribution's unbounded behavior beyond 3 deviations is undesired,
 * thus this distribution deviates nominally by modifying the bounds to 3 deviations.
 * Thus values within 3 deviations actually make up 100% of the distribution.
 */
GK_BASE_AVAILABILITY @interface GKGaussianDistribution : GKRandomDistribution

/**
 * The mean, or expected, value of the distribution. Values are more probable the closer to the mean they are.
 */
@property (nonatomic, assign, readonly) float mean;

/**
 * The deviation, often called 'sigma', is the deviation from the mean that would include roughly 68% of the distribution.
 * The range of the distribution is [mean - 3 * deviation, mean + 3 * deviation]. Values beyond 3 deviations
 * are considered so improbable that they are removed from the output set.
 */
@property (nonatomic, assign, readonly) float deviation;

/**
 * Initializes a Gaussian random distribution within the range [lowest, highest] using a source to grab input values from.
 * This sets the gaussian parameters to:
 *
 * mean = (highest + lowest) / 2
 * deviation = (highest - lowest) / 6
 *
 * The mean and deviation will be floating point numbers even if the distribution is meant to produce integer values.
 * @see mean
 * @see deviation
 */
- (instancetype)initWithRandomSource:(id<GKRandom>)source lowestValue:(NSInteger)lowestInclusive highestValue:(NSInteger)highestInclusive NS_DESIGNATED_INITIALIZER;

/**
 * Initializes a Gaussian random distribution within the range [mean - 3 * deviation, mean + 3 * deviation]
 * using a source to grab input values from.
 */
- (instancetype)initWithRandomSource:(id<GKRandom>)source mean:(float)mean deviation:(float)deviation NS_DESIGNATED_INITIALIZER;

@end


/**
 * A shuffled distribution tries to make sure individual samples are not clustered whilst retaining a uniform distribution of values
 * over time. This is often referred to as fair or less random, as the predicatability of the outcomes in a series is vastly increased,
 * yet the distribution of values is uniform.
 *
 * Do not use with distributions ranging more than 256 between lowest and highest as the shuffling seqeunce is stored internally in memory.
 */
GK_BASE_AVAILABILITY @interface GKShuffledDistribution : GKRandomDistribution

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKState.h
//
//  GKState.h
//  GameplayKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKit.h>

NS_ASSUME_NONNULL_BEGIN

@class GKStateMachine;

/**
 * Represents a single state in a state machine.
 * By default, states allow transitions freely to and from the states in the machine.
 *
 * If a more restricted set of valid transitions are needed in the state machine, you may override isValidNextState: where applicable.
 *
 * @see GKStateMachine
 * @see isValidNextState:
 */
GK_BASE_AVAILABILITY @interface GKState : NSObject

/**
 * The state machine that this state is associated with.
 * This is nil if this state hasn't been added to a state machine yet.
 */
@property (nullable, nonatomic, readonly, weak) GKStateMachine *stateMachine;

/**
 * Creates a new state to be used in a state machine.
 *
 * @see GKStateMachine
 */
+ (instancetype)state;
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 * Returns YES if the given class is a valid next state to enter.
 *
 * By default GKState will return YES for any class that is subclass of GKState.
 * Override this in a subclass to enforce limited edge traversals in the state machine.
 *
 * @see GKStateMachine.canEnterState:
 * @see GKStateMachine.enterState:
 *
 * @param stateClass the class to be checked
 * @return YES if the class is kind of GKState and the state transition is valid, else NO.
 */
- (BOOL)isValidNextState:(Class)stateClass;

/**
 * Called by GKStateMachine when this state is entered.
 *
 * @param previousState the state that was exited to enter this state.  This is nil if this is the state machine's first entered state.
 * @see stateMachineWithStates:initialStateClass:
 */
- (void)didEnterWithPreviousState:(nullable GKState *)previousState;

/**
 * Called by GKStateMachine when it is updated
 *
 * @param deltaTime the time, in seconds, since the last update
 */
- (void)updateWithDeltaTime:(NSTimeInterval)seconds;

/**
 * Called by GKStateMachine when this state is exited
 *
 * @param nextState the state that is being entered next
 */
- (void)willExitWithNextState:(GKState *)nextState;


@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKNoiseSource.h
//
//  GKNoiseSource.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A GKNoiseSource instance is a description of procedural noise in 3D space.  Noise sources generate values
 * between -1.0 and 1.0, inclusive, for any position in continuous 3D space.
 * Subclasses represent specific types of noise, each with their own parameters that affect the nature of the noise.
 * Noise sources are the starting point for generating and using procedural noise.  The 3D noise values may be manipulated and
 * combined with the GKNoise class.  Portions of this 3D noise can be extracted and utilized via the GKNoiseMap class.
 * Extracted portions of noise are useful in both 2D and 3D games.  Applications include creating realistic textures,
 * height maps for 2D and 3D game world terrain, tile maps for 2D games, and intentionally imperfect game object and
 * camera movements in 2D and 3D games.
 * This class is not intended to be instantiated.
 *
 * @see GKNoise
 * @see GKNoiseMap
 */
GK_BASE_AVAILABILITY_2 @interface GKNoiseSource : NSObject

@end

/**
 * Coherent noise is smoothly-changing, semi-random noise.  A given input always produces the same output.
 * A small change in input produces a small change in output.  A large change in input produces a random
 * change in output. This class is not intended to be instantiated.
 */
GK_BASE_AVAILABILITY_2 @interface GKCoherentNoiseSource : GKNoiseSource

@property (nonatomic) double frequency;
@property (nonatomic) NSInteger octaveCount;
@property (nonatomic) double lacunarity;
@property (nonatomic) int32_t seed;

@end

/**
 * Perlin noise is useful for creating natural-looking textures and realistic-looking terrain.
 */
GK_BASE_AVAILABILITY_2 @interface GKPerlinNoiseSource : GKCoherentNoiseSource

@property (nonatomic) double persistence;

+ (instancetype)perlinNoiseSourceWithFrequency:(double)frequency octaveCount:(NSInteger)octaveCount persistence:(double)persistence lacunarity:(double)lacunarity seed:(int32_t)seed;
- (instancetype)initWithFrequency:(double)frequency octaveCount:(NSInteger)octaveCount persistence:(double)persistence lacunarity:(double)lacunarity seed:(int32_t)seed NS_DESIGNATED_INITIALIZER;

@end

/**
 * Billow noise is similar to Perlin noise, with more rounded shapes and clearly-defined transitions beween values.
 */
GK_BASE_AVAILABILITY_2 @interface GKBillowNoiseSource : GKCoherentNoiseSource

@property (nonatomic) double persistence;

+ (instancetype)billowNoiseSourceWithFrequency:(double)frequency octaveCount:(NSInteger)octaveCount persistence:(double)persistence lacunarity:(double)lacunarity seed:(int32_t)seed;
- (instancetype)initWithFrequency:(double)frequency octaveCount:(NSInteger)octaveCount persistence:(double)persistence lacunarity:(double)lacunarity seed:(int32_t)seed NS_DESIGNATED_INITIALIZER;

@end

/**
 * Ridged noise is similar to Perlin noise, with sharply-defined, relatively thin peaks.
 */
GK_BASE_AVAILABILITY_2 @interface GKRidgedNoiseSource : GKCoherentNoiseSource

+ (instancetype)ridgedNoiseSourceWithFrequency:(double)frequency octaveCount:(NSInteger)octaveCount lacunarity:(double)lacunarity seed:(int32_t)seed;
- (instancetype)initWithFrequency:(double)frequency octaveCount:(NSInteger)octaveCount lacunarity:(double)lacunarity seed:(int32_t)seed NS_DESIGNATED_INITIALIZER;

@end

/**
 * Voronoi noise partitions the space into angular, polygonal "cells", which are reminiscent
 * of stained glass or crystal-like structures.
 */
GK_BASE_AVAILABILITY_2 @interface GKVoronoiNoiseSource : GKNoiseSource

@property (nonatomic) double frequency;
@property (nonatomic) double displacement;
@property (nonatomic, getter=isDistanceEnabled) BOOL distanceEnabled;
@property (nonatomic) int32_t seed;

+ (instancetype)voronoiNoiseWithFrequency:(double)frequency displacement:(double)displacement distanceEnabled:(BOOL)distanceEnabled seed:(int32_t)seed;
- (instancetype)initWithFrequency:(double)frequency displacement:(double)displacement distanceEnabled:(BOOL)distanceEnabled seed:(int32_t)seed NS_DESIGNATED_INITIALIZER;

@end

/**
 * Produces a single, constant value at all positions in the space.
 */
GK_BASE_AVAILABILITY_2 @interface GKConstantNoiseSource : GKNoiseSource

@property (nonatomic) double value;

+ (instancetype)constantNoiseWithValue:(double)value;
- (instancetype)initWithValue:(double)value NS_DESIGNATED_INITIALIZER;

@end

/**
 * Produces 3D cylindrical noise with an infinite number of cylinders-within-cyliners of constantly-increasing radius.
 */
GK_BASE_AVAILABILITY_2 @interface GKCylindersNoiseSource : GKNoiseSource

@property (nonatomic) double frequency;

+ (instancetype)cylindersNoiseWithFrequency:(double)frequency;
- (instancetype)initWithFrequency:(double)frequency NS_DESIGNATED_INITIALIZER;

@end

/**
 * Produces 3D spherical noise with an infinite number of spheres-within-spheres of constantly-increasing radius.
 */
GK_BASE_AVAILABILITY_2 @interface GKSpheresNoiseSource : GKNoiseSource

@property (nonatomic) double frequency;

+ (instancetype)spheresNoiseWithFrequency:(double)frequency;
- (instancetype)initWithFrequency:(double)frequency NS_DESIGNATED_INITIALIZER;

@end

/**
 * Produces noise in a checkerboard pattern.
 */
GK_BASE_AVAILABILITY_2 @interface GKCheckerboardNoiseSource : GKNoiseSource

@property (nonatomic) double squareSize;

+ (instancetype)checkerboardNoiseWithSquareSize:(double)squareSize;
- (instancetype)initWithSquareSize:(double)squareSize NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GameplayKit.h
//
//  GameplayKit.h
//  GameplayKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#pragma once

#import <GameplayKit/GameplayKitBase.h>

#import <GameplayKit/GKAgent.h>
#import <GameplayKit/GKBehavior.h>
#import <GameplayKit/GKComponent.h>
#import <GameplayKit/GKCompositeBehavior.h>
#import <GameplayKit/GKEntity.h>
#import <GameplayKit/GKGameModel.h>
#import <GameplayKit/GKGoal.h>
#import <GameplayKit/GKGraph.h>
#import <GameplayKit/GKGridGraph.h>
#import <GameplayKit/GKObstacleGraph.h>
#import <GameplayKit/GKGraphNode.h>
#import <GameplayKit/GKStrategist.h>
#import <GameplayKit/GKMeshGraph.h>
#import <GameplayKit/GKMinmaxStrategist.h>
#import <GameplayKit/GKMonteCarloStrategist.h>
#import <GameplayKit/GKDecisionTree.h>
#import <GameplayKit/GKNoiseSource.h>
#import <GameplayKit/GKNoise.h>
#import <GameplayKit/GKNoiseMap.h>
#import <GameplayKit/GKObstacle.h>
#import <GameplayKit/GKOctree.h>
#import <GameplayKit/GKPath.h>
#import <GameplayKit/GKPrimitives.h>
#import <GameplayKit/GKQuadtree.h>
#import <GameplayKit/GKRandomDistribution.h>
#import <GameplayKit/GKRTree.h>
#import <GameplayKit/GKRuleSystem.h>
#import <GameplayKit/GKState.h>
#import <GameplayKit/GKStateMachine.h>
#import <GameplayKit/GKScene.h>
#import <GameplayKit/GKSKNodeComponent.h>
#import <GameplayKit/SpriteKit+Additions.h>
#import <GameplayKit/GKSCNNodeComponent.h>
#import <GameplayKit/SceneKit+Additions.h>
// ==========  GameplayKit.framework/Headers/GKStateMachine.h
//
//  GKStateMachine.h
//  GameplayKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKit.h>

NS_ASSUME_NONNULL_BEGIN

@class GKState;

/**
 * Models a finite state machine that has a single current state.
 */
GK_BASE_AVAILABILITY @interface GKStateMachine : NSObject

/**
 * The current state that the state machine is in.
 * Prior to the first called to enterState this is equal to nil.
 */
@property (nullable, nonatomic, readonly) GKState* currentState;

/**
 * Creates a state machine with an array of possible states and an initial state.
 *
 * @param states a list of possible states for this state machine.
 */
+ (instancetype)stateMachineWithStates:(NSArray<GKState *> *)states;
- (instancetype)initWithStates:(NSArray<GKState *> *)states NS_DESIGNATED_INITIALIZER;

/**
 * Updates the current state machine.
 *
 * @param sec the time, in seconds, since the last frame
 */
- (void)updateWithDeltaTime:(NSTimeInterval)sec;

/**
 * Gets the instance of the indicated state class from this state machine.
 * Returns nil if the state does not exist
 *
 * @param stateClass the class of the state to be retrieved
 */
- (nullable GKState*)stateForClass:(Class)stateClass NS_SWIFT_UNAVAILABLE("Exposed in Swift as stateForClass<StateType: GKState>(stateClass: StateType.Type) -> StateType?");

/**
 * Returns YES if the indicated class is a a valid next state or if currentState is nil
 *
 * @param stateClass the class of the state to be tested
 */
- (BOOL)canEnterState:(Class)stateClass;

/**
 * Calls canEnterState to check if we can enter the given state and then enters that state if so.
 * [GKState willExitWithNextState:] is called on the old current state.
 * [GKState didEnterWithPreviousState:] is called on the new state.
 *
 * @param stateClass the class of the state to switch to
 * @return YES if state was entered.  NO otherwise.
 */
- (BOOL)enterState:(Class)stateClass;

@end


NS_ASSUME_NONNULL_END

// ==========  GameplayKit.framework/Headers/GKRuleSystem.h
//
//  GKRuleSystem.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameplayKitBase.h"

NS_ASSUME_NONNULL_BEGIN

@class GKRule;

/**
 * A rule system consists of 3 things:
 * - The current state, which upon creation is considered the inital state.
 * - The current set of rules.
 * - The current set of facts.
 * 
 * Each time a fact is added to the system, the set of rules are evaluated in order and their actions executed in the system if their predicates are true.
 * Rules can be fuzzy, allowing predicates and facts to be asserted to a degree of confidence instead of just boolean on/off.
 * 
 * The facts can be any kind of objects as long as they correctly determine equality using isEqual:
 * The simplest approach is to use strings or dictionaries as they provide the most flexibility in defining
 * facts, but user defined classes work just as well and may describe the problem space better.
 *
 * The fact set is at all times a fuzzy set, as defined by fact membership in the set being modulated by their
 * grade of membership. The rules may use the grade of membership to predicate their actions and in such a
 * manner create fuzzy logic. The fuzzy logic Zadeh operators are available on the system itself in order
 * to query multiple facts for combined membership grade.
 */
GK_BASE_AVAILABILITY @interface GKRuleSystem : NSObject

/**
 * Initializes a clean rule system with no state, rules or facts.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 * Explicitly evaluate the agenda of the rule system based on the current state and the current set of facts.
 *
 * This may in turn assert or retract more facts or change the state of the system, including activating more
 * rules in the agenda.
 */
- (void)evaluate;

/**
 * The implementation-defined state. If any changes are made on this outside the system you must
 * call evaluate to have the system take account of the changes.
 *
 * @see evaluate
 */
@property (nonatomic, retain, readonly) NSMutableDictionary *state;

#pragma mark Rules
/**
 * The current set of rules that will be used to set the agenda when rules are first added to the system.
 * They will also be used to refill the agenda whenever it is set.
 *
 * This is at all times the union of the agenda and executed sets.
 *
 * @see agenda
 * @see executed
 */
@property (nonatomic, retain, readonly) NSArray<GKRule *> *rules;

/**
 * Adds a rule to the system. Also adds it to the agenda in salience order.
 */
- (void)addRule:(GKRule *)rule;

/**
 * Adds rules to the system. Also adds them to the agenda in salience order.
 */
- (void)addRulesFromArray:(NSArray<GKRule *> *)rules;

/**
 * Removes all rules from the system.  This also removes them from the agenda and executed sets.
 */
- (void)removeAllRules;

/**
 * The current set of rules to be evaluated, in salience order, where if the salience is equivalent
 * the order of insertion into the agenda is used to decide which is first.
 * Adjust salience of your rules to adjust the order the next time the agenda is reset. Changing salience
 * on a rule currently in the agenda does not change its order in the agenda.
 *
 * This is at all times the difference between the rules and executed sets.
 *
 * @see rules
 * @see executed
 * @see reset
 */
@property (nonatomic, retain, readonly) NSArray<GKRule *> *agenda;

/**
 * The current set of rules that have already executed. Rules in this set will not be executed again until
 * the system is reset.
 *
 * This is at all times the difference between the rules and agenda sets.
 *
 * @see rules
 * @see agenda
 * @see reset
 */
@property (nonatomic, retain, readonly) NSArray<GKRule *> *executed;

#pragma mark Facts

/**
 * The current set of facts. Facts have a grade of membership that is >= 0.0. Query the system for the
 * individual grades of membership with gradeForFact:
 *
 * @see gradeForFact:
 */
@property (nonatomic, retain, readonly) NSArray *facts;

#pragma mark Zadeh operators
/**
 * Returns the current membership grade for the given fact, which is 0.0 if the fact
 * is not a member of the current set of facts.
 *
 * @return The membership grade of the given fact, in the range [0.0, 1.0].
 */
- (float)gradeForFact:(id<NSObject>)fact;

/**
 * Returns the combined membership grade for the all the given facts.
 *
 * This performs the logical AND operation between the given facts.
 *
 * @return The membership grade by applying the AND operator on the given facts, in the range [0.0, 1.0].
 */
- (float)minimumGradeForFacts:(NSArray *)facts;

/**
 * Returns the maximum membership grade for the any one of the given facts.
 *
 * This performs the logical OR operation between the given facts.
 *
 * @return The membership grade by applying the OR operator on the given facts, in the range [0.0, 1.0].
 */
- (float)maximumGradeForFacts:(NSArray *)facts;

#pragma mark Asserting Facts
/**
 * Asserts a fact with membership grade of 1.0.
 *
 * This will cause the current rules to be evaluated, which may in turn assert or retract more facts
 * or change the state of the system.
 *
 * This is shorthand for calling assertFact:grade: with a grade of 1.0
 *
 * @see assertFact:grade:
 * @see evaluate
 * @see NSObject.isEqual:
 */
- (void)assertFact:(id<NSObject>)fact;

/**
 * Asserts a fact with the supplied membership grade.
 * 
 * This will cause the current rules to be evaluated, which may in turn assert or retract more facts
 * or change the state of the system.
 * 
 * @see evaluate
 */
- (void)assertFact:(id<NSObject>)fact grade:(float)grade;

#pragma mark Retracting Facts
/**
 * Retracts a fact, setting its membership grade to 0, which also removes it from the fact set.
 *
 * This will cause the current rules to be evaluated, which may in turn assert or retract more facts
 * or change the state of the system.
 *
 * This is short hand for calling retractFact:grade: with a grade of 1.0
 *
 * @see retractFact:grade:
 * @see evaluate
 */
- (void)retractFact:(id<NSObject>)fact;

/**
 * Retracts a fact, reducing its membership grade by the supplied grade. If this brings the grade to 0
 * it is also removed from the fact set.
 *
 * This will cause the current rules to be evaluated, which may in turn assert or retract more facts
 * or change the state of the system.
 *
 * @see evaluate
 */
- (void)retractFact:(id<NSObject>)fact grade:(float)grade;

#pragma mark Resetting the system

/**
 * Clears the agenda and executed sets and removes all facts currently in the system.
 * It then fills the agenda with rules from the rule set, in salience order.
 * @see rules
 * @see facts
 */
- (void)reset;

@end


/**
 * The concrete class that the GKRuleSystem uses to evaluate the current state and facts with predicated rules.
 * These are sharable between systems, so don't retain any state in the rules themselves. Use the system-provided
 * state storage.
 * 
 * @see GKRuleSystem.state
 */
GK_BASE_AVAILABILITY @interface GKRule : NSObject

/**
 * Salience defines the order in the rule agenda that the system will evaluate. A rule with higher salience will
 * be evaluated before another rule in the agenda that has a lower salience.
 *
 * Defaults to 0.
 * @see GKRuleSystem.agenda
 */
@property (nonatomic, assign) NSInteger salience;

/**
 * Called by the rule system when it is this rule's turn to be evaluated. If the predicate returns YES then
 * the action for the rule will be performed. Once the action is performed the rule will move to the system's
 * executed list until the agenda is reset.
 *
 * @see performAction
 * @see GKRuleSystem.agenda
 * @see GKRuleSystem.executed
 * @see GKRuleSystem.reset
 * @return YES is the predicate passes and the action needs to be performed, NO otherwise.
 */
- (BOOL)evaluatePredicateWithSystem:(GKRuleSystem *)system;

/**
 * Performs the action consequence for the rule. This will only be called if the predicate evaluates to YES.
 * Any facts asserted or retracted by the action on the system will cause the system to evaluate the agenda
 * rule set again once the action completes.
 */
- (void)performActionWithSystem:(GKRuleSystem *)system;

/**
 * Create a data-driven rule that uses NSPredicate and a single assert as the action.
 */
+ (instancetype)ruleWithPredicate:(NSPredicate *)predicate assertingFact:(id<NSObject>)fact grade:(float)grade;

/**
 * Short hand for data-driven rule that uses NSPredicate and a single retract as the action.
 */
+ (instancetype)ruleWithPredicate:(NSPredicate *)predicate retractingFact:(id<NSObject>)fact grade:(float)grade;

/**
 * Short hand for making a rule that uses blocks for the predicate and action. This rule is not able to be archived
 * using NSKeyedArchiver so use a subclass or NSPredicate based rule if serialization of the rule is needed.
 */
+ (instancetype)ruleWithBlockPredicate:(BOOL (^)(GKRuleSystem *))predicate action:(void (^)(GKRuleSystem *))action;

@end


/**
 * A convenient subclass of GKRule that leverages existing NSPRedicate functionality for evaluating the predicate
 * of the rule.
 */
GK_BASE_AVAILABILITY @interface GKNSPredicateRule : GKRule

/**
 * The NSPredicate that is used inside this subclass's implementation of evaluatePredicateWithSystem:
 * In order to effectively use this class you must still override performActionWithSystem:
 *
 * @see GKRule.evaluatePredicateWithSystem:
 */
@property (nonatomic, retain, readonly) NSPredicate *predicate;

/**
 * Initializes a new rule with the given NSPredicate
 */
- (instancetype)initWithPredicate:(NSPredicate *)predicate;

/**
 * Overridden here to call the predicate's evaluateWithObject:substitutionVariables:, using sys
 * as the object and the system's state dictionary as the source of the substitution variables.
 *
 * @return YES if the NSPredicate evaluation passes and the action needs to be performed, NO otherwise.
 */
- (BOOL)evaluatePredicateWithSystem:(GKRuleSystem *)system;

@end

NS_ASSUME_NONNULL_END

// ==========  GameplayKit.framework/Headers/GKScene.h
//
//  GKScene.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

@class GKEntity, GKGraph;

NS_ASSUME_NONNULL_BEGIN

/**
 Protocol that specifies the type of objects that can be used as root nodes of a GKScene.
 
 @see GKScene.rootNode
 */
@protocol GKSceneRootNodeType <NSObject>

@end

/**
 A scene stores and handles loading of data related to a particular scene.
 */
GK_BASE_AVAILABILITY_2 @interface GKScene : NSObject <NSCopying, NSSecureCoding>

/**
 Loads a scene from a file contained within the bundle.
 */
+ (nullable instancetype)sceneWithFileNamed:(NSString *)filename;

/**
 Loads a scene from a file contained within the bundle and link with the specified rootNode.
 */
+ (nullable instancetype)sceneWithFileNamed:(NSString *)filename rootNode:(id <GKSceneRootNodeType>) rootNode;

/**
 The entities of this scene.
 */
@property (nonatomic, readonly) NSArray<GKEntity *> *entities;

/**
 The root node for the scene.
 
 @see GKSceneRootNodeType
 */
@property (nonatomic, nullable) id <GKSceneRootNodeType> rootNode;

/**
 The navigational graphs of this scene.
 */
@property (nonatomic, readonly) NSDictionary<NSString*, GKGraph *> *graphs;

/**
 Adds an entity to the scene's list of entities.
 
 @param entity the entity to add.
 */
- (void)addEntity:(GKEntity *)entity;

/**
 Removes an entity from the scene's list of entities.
 
 @param entity the entity to remove.
 */
- (void)removeEntity:(GKEntity *)entity;

/**
 Adds a graph to the scene's list of graphs.
 
 @param graph the graph to add.
 */
- (void)addGraph:(GKGraph *)graph name:(NSString*)name;

/**
 Removes a graph from the scene's list of graphs.
 
 @param name the name of the corresponding graph as added via addGraph:
 */
- (void)removeGraph:(NSString*)name;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKSCNNodeComponent.h
//
//  GKSCNNodeComponent.h
//  GameplayKit
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <GameplayKit/GKComponent.h>
#import <GameplayKit/GKAgent.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;

/**
 A component that encapsulates a SceneKit node.
 */
GK_BASE_AVAILABILITY_3 @interface GKSCNNodeComponent : GKComponent <GKAgentDelegate>

/**
 * Creates a component that encapsulate the given SceneKit node. When the component is
 * added to an entity, the SCNNode's entity property will be set.
 *
 * @param node Node to associate with the component.
 * @see SCNNode.entity
 */
+ (instancetype)componentWithNode:(SCNNode *)node;

/**
 * Initializes component to encapsulate the given SceneKit node. When the component is
 * added to an entity, the SCNNode's entity property will be set.
 *
 * @param node Node to associate with the component.
 * @see SCNNode.entity
 */
- (instancetype)initWithNode:(SCNNode *)node;

/**
 * The SceneKit node this component encapsulates.
 */
@property (nonatomic, readonly) SCNNode *node;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKPrimitives.h
//
//  GKPrimitives.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#include <simd/vector_types.h>

/**
 * Representation of an axis aligned box via its min corner (lower-left) and max corner (upper-right) 
 */
struct GKBox
{
    vector_float3 boxMin;
    vector_float3 boxMax;
};
typedef struct GKBox GKBox;

/**
 * Representation of an axis aligned quad via its min corner (lower-left) and max corner (upper-right)
 */
struct GKQuad
{
    vector_float2 quadMin;
    vector_float2 quadMax;
};
typedef struct GKQuad GKQuad;

struct GKTriangle
{
    vector_float3 points[3];
};
typedef struct GKTriangle GKTriangle;
// ==========  GameplayKit.framework/Headers/GKObstacleGraph.h
//
//  GKObstacleGraph.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <GameplayKit/GKGraph.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A collection of GKGraphNodes that are governed by a set of extruded GKPolygonObstacles
 */
GK_BASE_AVAILABILITY @interface GKObstacleGraph<NodeType : GKGraphNode2D*> : GKGraph

/*
 * Array of the extruded obstacles currently represented by this graph
 */
@property (nonatomic, readonly, nonnull) NSArray<GKPolygonObstacle *> *obstacles;

/*
 * The distance by which all obstacles are extruded.
 * This is most commonly the spatial bounding radius of a potential traveler on this path
 */
@property (nonatomic, readonly) float bufferRadius;

/**
 * Creates an optimal bidirectional graph based on a list of obstacles.
 * Each vertex of each obstacle is extruded and a connection is made between each vertex that does not intersect an obstacle
 * Guaranteed not to have any edges which intersect obstacles.
 * Same effect as [[GKObstacleGraph alloc] init], setting bufferRadius, and then calling addObstacles.
 * @param obstacles a list of obstacles to create the graph from
 * @param bufferRadius the circular radius of a potential agent that will navigate this graph.  Obstacles are extruded by this amount to create the graph.  Must be positive.  Negative values are clipped to 0.0f
 */
+ (instancetype)graphWithObstacles:(NSArray<GKPolygonObstacle *> *)obstacles bufferRadius:(float)bufferRadius;
- (instancetype)initWithObstacles:(NSArray<GKPolygonObstacle *> *)obstacles  bufferRadius:(float)bufferRadius;

/**
 * Creates an optimal bidirectional graph based on a list of obstacles.
 * Each vertex of each obstacle is extruded and a connection is made between each vertex that does not intersect an obstacle
 * Guaranteed not to have any edges which intersect obstacles.
 * Same effect as [[GKObstacleGraph alloc] init], setting bufferRadius, and then calling addObstacles.
 * @param obstacles a list of obstacles to create the graph from
 * @param bufferRadius the circular radius of a potential agent that will navigate this graph.  Obstacles are extruded by this amount to create the graph.  Must be positive.  Negative values are clipped to 0.0f
 * @param nodeClass the class of the nodes that this graph should create.  Must descend from GKGraphNode2D
 */
+ (instancetype)graphWithObstacles:(NSArray<GKPolygonObstacle *> *)obstacles bufferRadius:(float)bufferRadius nodeClass:(Class)nodeClass;
- (instancetype)initWithObstacles:(NSArray<GKPolygonObstacle *> *)obstacles  bufferRadius:(float)bufferRadius nodeClass:(Class)nodeClass;


/**
 * Connects the node to this graph by testing edge intersection with existing obstacles.
 * Same behavior as if this node had been present during initWithObstacles.
 * @param node the node to connect
 */
- (void)connectNodeUsingObstacles:(NodeType)node;

/**
 * Same behavior as connectNodeUsingObstacles: except you can optionally ignore certain obstacles from being tested for intersection.
 */
- (void)connectNodeUsingObstacles:(NodeType)node ignoringObstacles:(NSArray<GKPolygonObstacle *> *)obstaclesToIgnore;

/**
 * Same behavior as connectNodeUsingObstacles: except you can optionally ignore the bounding radius of certain obstacles from being tested for intersection
 */
- (void)connectNodeUsingObstacles:(NodeType)node ignoringBufferRadiusOfObstacles:(NSArray<GKPolygonObstacle *> *)obstaclesBufferRadiusToIgnore;

/**
 * Adds obstacles to this graph.
 * Obstacle is extruded and graph nodes are generated from its vertices and then connected to this graph
 * Nothing is done if an obstacle is already present in this graph
 * Any existing connections that intersect the new obstacles are destroyed unless they are protected with [GKObstacleGraph lockConnection:]
 * @param obstacles an array of obstacles to be added
 * @see lockConnection
 */
- (void)addObstacles:(NSArray<GKPolygonObstacle *> *)obstacles;

/**
 * Removes obstacles from this graph.
 * All associated graph nodes are removed and their connections are bidirectionally removed.
 * Connections between obstacle nodes that were previously invalidated by any of these obstacles are restored.
 * Nothing is done if an obstacle is already present in this graph
 * @param obstacles an array of obstacles to be removed
 */
- (void)removeObstacles:(NSArray<GKPolygonObstacle *> *) obstacles;

/**
 * Removes all obstacles from this graph.
 */
- (void)removeAllObstacles;

/**
 * Returns an array of the graph nodes associated with a given obstacle
 * @param obstacle the obstacle who's nodes are to be retrieved
 */
-(NSArray<NodeType> *)nodesForObstacle:(GKPolygonObstacle *)obstacle;

/**
 * Marks a connection as "locked", preventing this connection from being destroyed when you add obstacles that would intersect it
 * @param startNode startNode of the connection to lock
 * @param endNode endNode of the connection to lock
 */
- (void)lockConnectionFromNode:(NodeType)startNode toNode:(NodeType)endNode;

/**
 * "Unlocks" a connection, removing its protection from being destroyed when you add obstacles that would intersect it
 * @param startNode startNode of the connection to unlock
 * @param endNode endNode of the connection to unlock
 * @see lockConnection
 */
- (void)unlockConnectionFromNode:(NodeType)startNode toNode:(NodeType)endNode;

/**
 * Query if a given connection is locked
 * @param startNode startNode of the connection to query
 * @param endNode endNode of the connection to query
 * @see lockConnection
 * @see unlockConnection
 * @return YES if the connection was locked with lockConnection, NO if it was never locked or was unlocked via unlockConnection
 */
- (BOOL)isConnectionLockedFromNode:(NodeType)startNode toNode:(NodeType)endNode;

/**
 * Returns the class of the specified generic index
 */
- (nonnull Class)classForGenericArgumentAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKDecisionTree.h
//
//  GKDecisionTreeStrategist.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>
#import <GameplayKit/GKRandomSource.h>

NS_ASSUME_NONNULL_BEGIN

GK_BASE_AVAILABILITY_2 @interface GKDecisionNode : NSObject

/**
 * Creates a numeric branch to a node containing the specified attribute
 *
 * @param branch The branch of this node for the specified value
 * @param attribute The attribute of the created node
 * @return The node lead to by the branch
 */
- (instancetype)createBranchWithValue:(NSNumber *)value attribute:(id <NSObject>)attribute;

/**
 * Creates a predicated branch to a node containing the specified attribute
 *
 * @param branch The branch of this node for the provided predicate
 * @param attribute The attribute of the created node
 * @return The node lead to by the branch
 */
- (instancetype)createBranchWithPredicate:(NSPredicate *)predicate attribute:(id <NSObject>)attribute;

/**
 * Creates a random branch to a node containing the specified attribute
 *
 * @param branch The branch of this node with the given weight (weighted for random selection)
 * @param attribute The attribute of the created node
 * @return The node lead to by the branch
 *
 * @see GKDecisionTree
 */
- (instancetype)createBranchWithWeight:(NSInteger)weight attribute:(id <NSObject>)attribute;


@end


GK_BASE_AVAILABILITY_2 @interface GKDecisionTree : NSObject <NSSecureCoding>

/**
 * The node for the decision tree that all other nodes descend from
 */
@property (nonatomic, readonly, nullable) GKDecisionNode *rootNode;

/**
 * The random source used by the decision tree when descending on a random branch
 * This must be set before creating any weighted branches
 * @see GKDecisionNode
 */
@property (copy, nonatomic) GKRandomSource *randomSource;

/**
 * Initializes the decision tree with a root node containing the provided attribute
 *
 * @param attribute The attribute to be contained at the root of the tree
 * @return GKDecisionTree with the set root
 */
- (instancetype)initWithAttribute:(id <NSObject>)attribute;

/**
 * Initializes and constructs a decision tree by learning from the provided examples & attributes
 *
 * @param examples Must be an array of examples (with each example being a collection of the various attributes at a given state)
 * @param results An array of the corresponding results for each example. Ordered such that the first result matches with the first example in examples.
 * @param attributes The list of attributes. Ordered such that the first attribute matches with the first result in each example.
 * So if we have two attributes: [distance, jump height], and two examples: [[20, 8], [15, 14]], and the resulting actions here: [Roll, Jump], we can think of this as a matrix:
 *
 *          distance| height            <-  Attributes
 *           _______|_______
 *          |       |       |
 *          |  20   |   8   |  jump
 *          |-------|-------|-------    <-  Results
 *          |  15   |   14  |  roll
 *          |_______|_______|
 *                  ^
 *                  |
 *               Examples
 *
 * @return GKDecisionTree created by learning from the provided examples for the provided attributes
 */
- (instancetype)initWithExamples:(NSArray <NSArray <id <NSObject>>*>*)examples actions:(NSArray <id <NSObject>>*)actions attributes:(NSArray <id <NSObject>>*)attributes;

/**
 * Initializes a decision tree from the contents of a file
 *
 * @param url The URL from which the contents will be loaded
 * @return The instance of the decision tree constructed
 */
- (instancetype)initWithURL:(NSURL *)url error:(NSError * _Nullable)error;

/**
 * Exports a decision tree to the given URL
 *
 * @param url The URL to which the contents will be exported
 * @return The response indicating the status of the decision tree being successfully exported
 */
- (BOOL)exportToURL:(NSURL *)url error:(NSError * _Nullable)error;

/**
 * Will branch down from the root node to find the correct action attribute for the given collection of results and their respective attributes
 *
 * @param answers The dictionary of attributes (keys) and their answers (values)
 * @return The attribute found by traversing the tree given the provided answers
 */
- (nullable id <NSObject>)findActionForAnswers:(NSDictionary <id <NSObject>, id <NSObject>>*)answers;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKMonteCarloStrategist.h
//
//  GKMonteCarloStrategist.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <GameplayKit/GKStrategist.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The Monte Carlo Strategist is a generic AI that selects a game model update for a given player that results
 * in the highest likelihood for that player to eventually win the game. It does this by sampling the updates available
 * to the player in question. In doing this it will select the update it knows to produce the best result so far, expanding on this
 * selection, simulating the rest of the game from that expansion, and then propogating the results (win or loss) upwards.
 * It will do this until the budget has been reached, then returning the choice it has deemed best suited for the player in question.
 */
GK_BASE_AVAILABILITY_2 @interface GKMonteCarloStrategist : NSObject <GKStrategist>

/**
 * The maximum number of samples that will be processed when searching for a move.
 */
@property (nonatomic, assign) NSUInteger budget;

/**
 * A weight that encourages exploration of less visited updates versus the continued exploitation of previously visited updates.
 */
@property (nonatomic, assign) NSUInteger explorationParameter;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKGoal.h
//
//  GKGoal.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

NS_ASSUME_NONNULL_BEGIN

@class GKAgent, GKPath, GKObstacle;

/**
 * Defines a spatial directive.
 * The various goals cause force to be applied to agents to try to achieve said goal.
 */
GK_BASE_AVAILABILITY @interface GKGoal : NSObject <NSCopying>

/**
 * Creates a goal to move toward the agent
 * @param agent the agent to seek
 */
+ (instancetype)goalToSeekAgent:(GKAgent *)agent;

/**
 * Creates a goal to move away from the agent
 * @param agent the agent to flee from
 */
+ (instancetype)goalToFleeAgent:(GKAgent *)agent;

/**
 * Creates a goal to avoid colliding with a group of agents without taking into account those agents' momentum
 * @param maxPredictionTime how far ahead in the future, in seconds, should we look for potential collisions
 */
+ (instancetype)goalToAvoidObstacles:(NSArray<GKObstacle *> *)obstacles maxPredictionTime:(NSTimeInterval)maxPredictionTime;

/**
 * Creates a goal to avoid colliding with a group of agents taking into account those agent's momentum
 * @param timeBeforeCollisionToAvoid how far ahead in the future, in seconds, should we look for potential collisions
 */
+ (instancetype)goalToAvoidAgents:(NSArray<GKAgent *> *)agents maxPredictionTime:(NSTimeInterval)maxPredictionTime;

/**
 * Creates a goal that tries to repel this agent away from the other agents and attempts to prevent overlap
 * @param maxDistance the distance between agents before repelling happens
 * @param maxAngle the angle, in radians, between this agent's foward and the vector toward the other agent before the repelling happens
 */
+ (instancetype)goalToSeparateFromAgents:(NSArray<GKAgent *> *)agents maxDistance:(float)maxDistance maxAngle:(float)maxAngle;

/**
 * Creates a goal to align this agent's orientation with the average orientation of the group of agents.
 * @param maxDistance the distance between agents before alignment happens
 * @param maxAngle the angle, in radians, between this agent's foward and the vector toward the other agent before alignment happens
 */
+ (instancetype)goalToAlignWithAgents:(NSArray<GKAgent *> *)agents maxDistance:(float)maxDistance maxAngle:(float)maxAngle;

/**
 * Creates a goal to seek the average position of the group of agents.
 * @param maxDistance the distance between agents before cohesion happens
 * @param maxAngle the angle between this agent's foward and the vector toward the other agent before cohesion happens
 */
+ (instancetype)goalToCohereWithAgents:(NSArray<GKAgent *> *)agents maxDistance:(float)maxDistance maxAngle:(float)maxAngle;

/**
 * Creates a goal that attempts to change our momentum to reach the target speed
 * @param targetSpeed the target speed
 */
+ (instancetype)goalToReachTargetSpeed:(float)targetSpeed;

/**
 * Creates a goal that will make the agent appear to wander, aimlessly moving forward and turning randomly
 * @param deltaTime how much time, in seconds, has elapsed since the last simulation step
 * @param speed the speed at which to wander
 */
+ (instancetype)goalToWander:(float)speed;

/**
 * Creates a goal that will attempt to intercept another target agent taking into account that agent's momentum
 * @param target agent to intercept
 * @param maxPredictionTime how far ahead in the future, in seconds, should we look for potential intercepts
 */
+ (instancetype)goalToInterceptAgent:(GKAgent *)target maxPredictionTime:(NSTimeInterval)maxPredictionTime;

/**
 * Creates a goal that will attempt to follow the given path
 * @param path the path to follow
 * @param maxPredictionTime how far ahead in the future, in seconds, should we look for potential intercepts
 * @param forward direction to follow the path. forward = NO is reverse
 */
+ (instancetype)goalToFollowPath:(GKPath *)path maxPredictionTime:(NSTimeInterval)maxPredictionTime forward:(BOOL)forward;

/**
 * Creates a goal that will attempt to stay on the given path
 * @param path the path to follow
 * @param maxPredictionTime how far ahead in the future, in seconds, should we look for potential intercepts
 */
+ (instancetype)goalToStayOnPath:(GKPath *)path maxPredictionTime:(NSTimeInterval)maxPredictionTime;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKBehavior.h
//
//  GKBehavior.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

NS_ASSUME_NONNULL_BEGIN

@class GKGoal;

/**
 * A collection of GKGoals or GKBehaviors with weights that can be applied to a GKAgent
 * The sub-goals or sub-behaviors are summed to produce a total force to be applied to an agent
 */
GK_BASE_AVAILABILITY @interface GKBehavior : NSObject<NSFastEnumeration, NSCopying>

/*
 * The number of GKGoals in this behavior
 */
@property (readonly) NSInteger goalCount;

/**
 * Creates a behavior with a single goal and weight
 */
+ (instancetype)behaviorWithGoal:(GKGoal *)goal weight:(float)weight;

/**
 * Creates a behavior with an array of goals.  All weights are set to 1.0f
 */
+ (instancetype)behaviorWithGoals:(NSArray<GKGoal *> *)goals;

/**
 * Creates a behavior with two associated arrays of goals and weights
 */
+ (instancetype)behaviorWithGoals:(NSArray<GKGoal *> *)goals andWeights:(NSArray<NSNumber*> *)weights;

/**
 * Creates a behavior with a dictionary of goal/weight pairs
 */
+ (instancetype)behaviorWithWeightedGoals:(NSDictionary<GKGoal *, NSNumber *> *)weightedGoals;

/**
 * Adds a new goal or changes the weight of the existing goal in this behavior.
 * If the goal does not exist in this behavior, it is added.
 * @param weight the weight for this goal
 * @param goal the goal who's weight to change
 */
- (void)setWeight:(float)weight forGoal:(GKGoal *)goal;

/**
 * Gets the current weight for a given goal.
 * @return the weight of the goal, or 0 if there is no such goal on this behavior
 */
- (float)weightForGoal:(GKGoal *)goal;

/**
 * Remove the indicated goal from this behavior.
 * @param goal the goal to be removed
 */
- (void)removeGoal:(GKGoal *)goal;

/**
 * Removes all the goals on the behavior.
 */
- (void)removeAllGoals;

/**
 * Supports getting goals via a [int] subscript.
 */
- (GKGoal *)objectAtIndexedSubscript:(NSUInteger)idx;
/**
 * Supports setting a weight via a [goal] subscript.
 */
- (void)setObject:(NSNumber *)weight forKeyedSubscript:(GKGoal *)goal;

/**
 * Supports getting a weight via a [goal] subscript.
 */
- (nullable NSNumber *)objectForKeyedSubscript:(GKGoal *)goal;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKAgent.h
//
//  GKAgent.h
//  GameplayKit
//
//  Copyright © 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

#import <GameplayKit/GKComponent.h>
#import <GameplayKit/GKObstacle.h>
#import <GameplayKit/GKBehavior.h>
#import <GameplayKit/GKGoal.h>

@class GKAgent, GKBehavior, GKPath;

NS_ASSUME_NONNULL_BEGIN

/**
 * Delegate that will receive messages regarding GKAgent updates.
 */
@protocol GKAgentDelegate <NSObject>

@optional
/*
 * Called before [GKAgent updateWithDeltaTime:] is called each frame.
 */
- (void)agentWillUpdate:(GKAgent *)agent;

/*
 * Called after [GKAgent updateWithDeltaTime:] is called each frame.
 */
- (void)agentDidUpdate:(GKAgent *)agent;

@end


/**
 * An agent is a point mass whose local coordinate system is aligned to its velocity.  Agents have a variety of
 * steering functions that can be used to simulate vehicles or entities with agency.
 * The units of mass, velocity and radius are dimensionless but related. The visual representation of these values
 * are specific to each game's own situation.
 *
 * @discussion Values close to 1.0 should be canonical and are expected to yield pleasing results. When applied to visuals
 * these values should be scaled and biased into their target coordinate system and a simple filter on top ensures
 * any noise generated from the steering logic doesn't affect the visual represtentation.
 */
GK_BASE_AVAILABILITY @interface GKAgent : GKComponent <NSSecureCoding>

/**
 * Object which has agentDidUpdate called on it during this agent's behavior updatekbeha
 */
@property (nullable, nonatomic, weak) id<GKAgentDelegate> delegate;

/**
 * The behavior to apply when updateWithDeltaTime is called.
 * All forces from the goals in the behavior are summed and then applied.
 */
@property (nullable, nonatomic, retain) GKBehavior *behavior;

/**
 * Agent's mass. Used for agent impulse application purposes.
 * 
 * Defaults to 1.0
 */
@property (nonatomic) float mass;

/**
 * Radius of the agent's bounding circle.  Used by the agent avoid steering functions.
 *
 * Defaults to 0.5 for a canonical diameter of 1.0
 */
@property (nonatomic) float radius;

/**
 * Current speed of the agent along its foward direction.
 *
 * Defaults to 0.0
 */
@property (nonatomic) float speed;

/**
 * Maximum amount of acceleration that can be applied to this agent.  All applied impulses are clipped to this amount.
 *
 * Defaults to 1.0
 */
@property (nonatomic) float maxAcceleration;

/**
 * Maximum speed of this agent. Impulses cannot cause the agents speed to ever be greater than this value.
 *
 * Defaults to 1.0
 */
@property (nonatomic) float maxSpeed;

@end


/**
 * A 2D specalization of an agent that moves on a 2-axis logical coordinate system. This coordinate system does not
 * need to match the visual coordinate system of the delegate. One simple case of that is isometric 2D content where the
 * game model is on a flat 2D plane but the visuals are displayed on an angle where one of the logical axes are used for
 * simulated depth as well as some translation in the display plane.
 */
GK_BASE_AVAILABILITY @interface GKAgent2D : GKAgent <NSSecureCoding>

/**
 * Position of the agent on the logical XY plane
 */
@property (nonatomic, assign) vector_float2 position;

/**
 * Current logical velocity of the agent. The forward vector can be derived by normalizing this.
 */
@property (nonatomic, readonly) vector_float2 velocity;

/**
 * Z rotation of the agent on the logical XY plane
 */
@property (nonatomic) float rotation;

/**
 * Overridden from GKComponent.
 * Updates this agent with the current behavior, generating a force to reach its goals and applying that force.
 */
- (void)updateWithDeltaTime:(NSTimeInterval)seconds;

@end

/**
 * A 3D specialization of an agent that moves on a 3-axis logical coordinate system.
 */
GK_BASE_AVAILABILITY @interface GKAgent3D : GKAgent


/**
 * Position of the agent on the logical XYZ plane
 */
@property (nonatomic, assign) vector_float3 position;

/**
 * Current logical velocity of the agent. The forward vector can be derived by normalizing this.
 */
@property (nonatomic, readonly) vector_float3 velocity;

/**
 * Should this vehicle operate in a right-handed coordinate system? NO means it will be left-handed
 */
@property (nonatomic) BOOL rightHanded;


/**
 * The 3x3 rotation matrix that defines the orientation of this agent in 3D space
 * columns[0] is forward, columns[1] is up, columns[2] is side
 */
@property (nonatomic, assign) matrix_float3x3 rotation;


/**
 * Overridden from GKComponent.
 * Updates this agent with the current behavior, generating a force to reach its goals and applying that force.
 */
- (void)updateWithDeltaTime:(NSTimeInterval)seconds;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKGameModel.h
//
//  GKGameModel.h
//  GameplayKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Maximum / minimum values for GKGameModel scoreForPlayer. Values must be within these ranges.
 */
static const NSInteger GKGameModelMaxScore = 1 << 24;
static const NSInteger GKGameModelMinScore = -(1 << 24);

/**
 * A protocol used to encapsulate the data needed to affect an update to a game model. 
 * Typically represents an action or move performed by a player.
 */
@protocol GKGameModelUpdate <NSObject>

/**
 * Property get/set by GKMinmaxStrategist to sort GKGameModelUpdates.
 */
@property (nonatomic, assign) NSInteger value;

@end


/**
 * A protocol used to represent an individual player within a game model.
 */
@protocol GKGameModelPlayer <NSObject>

/**
 * Identifier used by GKMinmaxStrategist differentiate players from one another.
 */
@property (nonatomic, readonly) NSInteger playerId;

@end

/**
 * A protocol for abstracting a game model for use with the GKMinmaxStrategist class. The minmax
 * strategist uses the game model class, along with GKGameModelPlayer and GKGameModelUpdate to 
 * find optimal moves in an adversarial, turn-based game.
 */
@protocol GKGameModel <NSObject, NSCopying>

/**
 * Array of instances of GKGameModelPlayers representing players within this game model. When the 
 * GKMinmaxStrategist class is used to find an optimal move for a specific player, it uses this 
 * array to rate the moves of that player’s opponent(s).
 */
@property (nonatomic, readonly, nullable) NSArray<id<GKGameModelPlayer>> *players;

/**
 * The player whose turn it is to perform an update to the game model. GKMinmaxStrategist assumes 
 * that the next call to the applyGameModelUpdate: method will perform a move on behalf of this player.
 */
@property (nonatomic, readonly, nullable) id<GKGameModelPlayer> activePlayer;

/**
 * Sets the data of another game model. All data should be copied over, and should not maintain 
 * any pointers to the copied game state. This is used by the GKMinmaxStrategist to process
 * permutations of the game without needing to apply potentially destructive updates to the 
 * primary game model.
 */
- (void)setGameModel:(id<GKGameModel>)gameModel;

/**
 * Returns an array of all the GKGameModelUpdates (i.e. actions/moves) that the active
 * player can undertake, with one instance of GKGameModelUpdate for each possible move. 
 * Returns nil if the specified player is invalid, is not a part of the game model, or 
 * if there are no valid moves available.
 */
- (nullable NSArray<id<GKGameModelUpdate>> *)gameModelUpdatesForPlayer:(id <GKGameModelPlayer>)player;

/**
 * Applies a GKGameModelUpdate to the game model, potentially resulting in a new activePlayer. 
 * GKMinmaxStrategist will call this method on a copy of the primary game model to speculate 
 * about possible future moves and their effects. It is assumed that calling this method performs 
 * a move on behalf of the player identified by the activePlayer property.
 */
- (void)applyGameModelUpdate:(id<GKGameModelUpdate>)gameModelUpdate;

@optional

/**
 * Returns the score for the specified player. A higher value indicates a better position for
 * the player than a lower value. Required by GKMinmaxStrategist to determine which
 * GKGameModelUpdate is the most advantageous for a given player. If the player is invalid, or
 * not a part of the game model, returns NSIntegerMin.
 */
- (NSInteger)scoreForPlayer:(id<GKGameModelPlayer>)player;

/**
 * Returns YES if the specified player has reached a win state, NO if otherwise. Note that NO does not
 * necessarily mean that the player has lost. Optionally used by GKMinmaxStrategist to improve move selection.
 */
- (BOOL)isWinForPlayer:(id<GKGameModelPlayer>)player;

/**
 * Returns YES if the specified player has reached a loss state, NO if otherwise. Note that NO does not
 * necessarily mean that the player has won. Optionally used by GKMinmaxStrategist to improve move selection.
 */
- (BOOL)isLossForPlayer:(id<GKGameModelPlayer>)player;

- (void)unapplyGameModelUpdate:(id<GKGameModelUpdate>)gameModelUpdate;

@end


NS_ASSUME_NONNULL_END// ==========  GameplayKit.framework/Headers/SceneKit+Additions.h
/**
 @header
 
 
 SceneKit framework category additions related to GameplayKit integration.
 
 
 @copyright 2017 Apple, Inc. All rights reserve.
 
 */

#import <SceneKit/SceneKit.h>

#import <GameplayKit/GKEntity.h>
#import <GameplayKit/GKScene.h>

NS_ASSUME_NONNULL_BEGIN

@interface SCNNode (GameplayKit)

/**
 * The GKEntity associated with the node via a GKSCNNodeComponent.
 *
 * @see GKEntity
 */
@property (nonatomic, weak) GKEntity *entity NS_AVAILABLE(10_13, 11_0);

@end

/**
 * Adds conformance to GKSceneRootNodeType for usage as rootNode of GKScene 
 */
@interface SCNScene (GameplayKit) <GKSceneRootNodeType>

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKVersion.h
#define GK_VERSION 80000000
// ==========  GameplayKit.framework/Headers/GKOctree.h
//
//  GKOctree.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>
#import <GameplayKit/GKPrimitives.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The individual node(s) that make up a GKOctree.
 * Used as a hint for faster removal via [GKOctree removeData:WithNode:]
 */
GK_BASE_AVAILABILITY_2 @interface GKOctreeNode : NSObject

/* The box associated with this octree node*/
@property (readonly) struct GKBox box;

@end


/**
 * A tree data structure where each level has 8 children that subdivide a given space into the eight octants.
 * Stores arbitrary NSObject elements via points and boxes.
 */
GK_BASE_AVAILABILITY_2 @interface GKOctree <ElementType: NSObject*> : NSObject

/**
 * Creates a octree with a given bounding box and minimum allowed cell size
 *
 * @param box the bounding box of this octree.  all elements bounding boxes must be within this space.
 * @param minCellSize the minimum allowed cell size.  The octree will not create octants that have a width,height or depth smaller than this size.
 */
+(instancetype)octreeWithBoundingBox:(GKBox)box minimumCellSize:(float)minCellSize;
-(instancetype)initWithBoundingBox:(GKBox)box minimumCellSize:(float)minCellSize;

/**
 * Adds an NSObject to this octree with a given point.
 * This element will always reside in the leaf node its point is in.
 *
 * @param element the element to be stored
 * @param point the point associated with the element you want to store
 * @return the node the element was added to
 */
-(GKOctreeNode*)addElement:(ElementType)element withPoint:(vector_float3)point;

/**
 * Adds an NSObject to this octtree with a given axis-aligned box
 * This element will reside in the lowest node that it's box fits in completely.
 *
 * @param element the element to be stored
 * @param box the box associated with the element to be stored
 * @return the node that the element was added to
 */
-(GKOctreeNode*)addElement:(ElementType)element withBox:(GKBox)box;

/**
 * Returns all of the elements in the node this point would be placed in
 *
 * @param point the point to query
 * @return an NSArray of all the element found at the node this point would be placed in
 */
-(NSArray<ElementType>*)elementsAtPoint:(vector_float3)point;

/**
 * Returns all of the elements that resides in nodes which intersect the given box
 *
 * @param box the box tha specifies which elements you would like to retrieve
 * @return an NSArray of all the elements in all of the nodes that intersect the given box
 *
 */
-(NSArray<ElementType>*)elementsInBox:(GKBox)box;

/**
 * Removes the given NSObject from this octree
 * Note that this is an exhaustive search and is can be slow for larger trees.
 * Cache the relevant GKOctreeNode and use removeElement:WithNode: for better performance.
 *
 * @param element the element to be removed
 * @return returns YES if the data was removed, NO otherwise
 */
-(BOOL)removeElement:(ElementType)element;

/**
 * Removes the given NSObject from the given node
 * Note that this is not an exhaustive search and is faster than removeData:
 *
 * @param element the element to be removed
 * @param node the node in which this data resides
 * @return returns YES if the element was removed, NO otherwise
 */
-(BOOL)removeElement:(ElementType)element withNode:(GKOctreeNode*)node;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKMinmaxStrategist.h
//
//  GKMinmaxStrategist.h
//  GameplayKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GKStrategist.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The Minmax Strategist is a generic AI that selects a game model update for a given player that maximises 
 * potential gain, while minimising potential loss. It does this by examining all of the updates available 
 * to the player in question, extrapolating the potential moves opposing players may take, projecting out 
 * maxLookAheadDepth number of turns. The selected update will result in the greatest potential gain, balanced 
 * against the potential gain of other players.
 */
GK_BASE_AVAILABILITY @interface GKMinmaxStrategist : NSObject <GKStrategist>

/**
 * The maximum number of future turns that will be processed when searching for a move.
 */
@property (nonatomic, assign) NSInteger maxLookAheadDepth;

/**
 * Selects the best move for the specified player. If randomSource is not nil, it will randomly select
 * which move to use if there are one or more ties for the best. Returns nil if the player is invalid,
 * the player is not a part of the game model, or the player has no valid moves available.
 */
- (nullable id<GKGameModelUpdate>)bestMoveForPlayer:(id<GKGameModelPlayer>)player;

/**
 * Selects one move from the set of N best moves for the specified player, where N is equal to 
 * numMovesToConsider. If randomSource is nil, it will not randomly select, but will behave like 
 * bestMoveForPlayer and return the first best move. Returns nil if the player is invalid, the 
 * player is not a part of the game model, or the player has no valid moves available.
 */
- (nullable id<GKGameModelUpdate>)randomMoveForPlayer:(id<GKGameModelPlayer>)player fromNumberOfBestMoves:(NSInteger)numMovesToConsider;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKGraphNode.h
//
//  GKGraph.h
//  GameplayKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A node in a directed graph. Edges are directed and can have variable costs.
 */
GK_BASE_AVAILABILITY @interface GKGraphNode : NSObject <NSSecureCoding>

/**
 * List of other graph nodes that this node has an edge leading to.
 */
@property (nonatomic,readonly) NSArray<GKGraphNode *> *connectedNodes;

/**
 * Add a connection to a group of other nodes indicating those nodes can be reached from this node.
 * A new connection is not created if it already exists.
 * @param array of nodes that are end points for their respective connections
 * @param bidirectional should a connection also be added connecting the destination node back to this node?
 */
- (void)addConnectionsToNodes:(NSArray<GKGraphNode *> *)nodes bidirectional:(BOOL)bidirectional;

/**
 * Removes connections to a group of other nodes indicating those nodes can no longer be reached from this node.
 * Nothing happens if a particular connection does not exist.
 * @param node the end point of the edge to be removed
  * @param bidirectional should the connection also be added the destination node back to this node also be removed if it exists?
 */
- (void)removeConnectionsToNodes:(NSArray<GKGraphNode *> *)nodes bidirectional:(BOOL)bidirectional;

/**
 * Returns the estimated heuristic cost to reach the indicated node from this node
 * @param the end point of the edge who's cost is to be estimated
 */
- (float)estimatedCostToNode:(GKGraphNode *)node;

/**
 * Returns the actual cost to reach the indicated node from this node
 */
- (float)costToNode:(GKGraphNode *)node;

/**
 * Attempts to find the optimal path between this node and the indicated goal node.
 * If such a path exists, it is returned in start to end order.
 * If it doesn't exist, the array returned will be empty.
 * @param goalNode the goal node of the pathfinding attempt
 */
- (NSArray<__kindof GKGraphNode *> *)findPathToNode:(GKGraphNode*)goalNode;

/**
 * As with findPathToNode: except this node is the goal node and a startNode is specified
 * @param startNode the start node of the pathfinding attempt
 */
- (NSArray<__kindof GKGraphNode *> *)findPathFromNode:(GKGraphNode*)startNode;

@end


/**
 * GKGraphNode coupled with a 2D position
 */
GK_BASE_AVAILABILITY @interface GKGraphNode2D : GKGraphNode

@property (nonatomic) vector_float2 position;

+ (instancetype)nodeWithPoint:(vector_float2)point;
- (instancetype)initWithPoint:(vector_float2)point;

@end

/**
 * GKGraphNode coupled with a 3D position
 */
GK_BASE_AVAILABILITY_2 @interface GKGraphNode3D : GKGraphNode

@property (nonatomic) vector_float3 position;

+ (instancetype)nodeWithPoint:(vector_float3)point;
- (instancetype)initWithPoint:(vector_float3)point;

@end

/**
 * GKGraphNode coupled with a position on a 2D grid
 */
GK_BASE_AVAILABILITY @interface GKGridGraphNode : GKGraphNode

@property (nonatomic, readonly) vector_int2 gridPosition;

+ (instancetype)nodeWithGridPosition:(vector_int2)gridPosition;
- (instancetype)initWithGridPosition:(vector_int2)gridPosition;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKGridGraph.h
//
//  GKGridGraph.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#include <GameplayKit/GKGraph.h>

NS_ASSUME_NONNULL_BEGIN


@class GKGridGraphNode;

/*
 * A collection of GKGraphNodes that are governed by a 2D Cartesian grid
 */
GK_BASE_AVAILABILITY @interface GKGridGraph<NodeType : GKGridGraphNode *>  : GKGraph

/*
 * The minimum X and Y coordinates of the 2D Cartesian grid this graph represents
 */
@property (nonatomic, readonly) vector_int2 gridOrigin;

/*
 * The width of the 2D Cartesian grid this graph represents
 */
@property (nonatomic, readonly) NSUInteger gridWidth;

/*
 * The height of the 2D Cartesian grid this graph represents
 */
@property (nonatomic, readonly) NSUInteger gridHeight;

/*
 * Returns YES if this grid is also connected via it's diagonal directions rather than only it's cardinal directions
 */
@property (nonatomic, readonly) BOOL diagonalsAllowed;

/**
 * Creates a bidirectional graph connecting all of the points on a 2D grid
 * @param x starting x value of the grid
 * @param y starting y value of the grid
 * @param width how wide the grid will be; the grid will continue along the positive X axis from the starting x value
 * @param height how high the grid will be; the grid will continue along the positive Y axis from the starting y value
 * @param diagonalsAllowed should diagonal connections between nodes be made?  If not, only cardinal directions will be connected.
 */
+ (instancetype)graphFromGridStartingAt:(vector_int2)position width:(int)width height:(int)height diagonalsAllowed:(BOOL)diagonalsAllowed;
- (instancetype)initFromGridStartingAt:(vector_int2)position width:(int)width height:(int)height diagonalsAllowed:(BOOL)diagonalsAllowed;

/**
 * Creates a bidirectional graph connecting all of the points on a 2D grid
 * @param x starting x value of the grid
 * @param y starting y value of the grid
 * @param width how wide the grid will be; the grid will continue along the positive X axis from the starting x value
 * @param height how high the grid will be; the grid will continue along the positive Y axis from the starting y value
 * @param diagonalsAllowed should diagonal connections between nodes be made?  If not, only cardinal directions will be connected.
 * @param nodeClass the class of the nodes that this graph should create.  Must descend from GKGridGraphNode
 */
+ (instancetype)graphFromGridStartingAt:(vector_int2)position width:(int)width height:(int)height diagonalsAllowed:(BOOL)diagonalsAllowed nodeClass:(Class)nodeClass;
- (instancetype)initFromGridStartingAt:(vector_int2)position width:(int)width height:(int)height diagonalsAllowed:(BOOL)diagonalsAllowed nodeClass:(Class)nodeClass;

/**
 * Returns the GKGridGraphNode at the indicated X and Y coordinate
 * Returns nil if it is outside the bounds of minCoordinates and maxCoordinates
 * @param x x coordinate of the grid node to return
 * @param y y coordinate of the grid node to return
 */
- (nullable NodeType)nodeAtGridPosition:(vector_int2)position;

/**
 * Connects the given GKGridGraphNode to this graph by connecting it to it's adjacent nodes on the grid
 * Input node must have coordinates within the rectangle specified by minCoordinates and maxCoordinates
 * @param node the node to be connected
 */
- (void)connectNodeToAdjacentNodes:(GKGridGraphNode *)node;

/**
 * Returns the class of the specified generic index
 */
- (nonnull Class)classForGenericArgumentAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GameplayKitBase.h
//
//  GameplayKitBase.h
//  GameplayKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>
#import <Availability.h>
#import <TargetConditionals.h>

#import <GameplayKit/GKVersion.h>

//Exporting
#ifdef __cplusplus
#define GK_EXPORT extern "C" __attribute__((visibility ("default")))
#else
#define GK_EXPORT extern __attribute__((visibility ("default")))
#endif

//Availability
#define GK_BASE_AVAILABILITY NS_CLASS_AVAILABLE(10_11, 9_0)
#define GK_BASE_AVAILABILITY_2 NS_CLASS_AVAILABLE(10_12, 10_0)
#define GK_BASE_AVAILABILITY_3 NS_CLASS_AVAILABLE(10_13, 11_0)

#define GK_AVAILABLE __OSX_AVAILABLE_STARTING

//Inlining
#define GK_FORCE_INLINE __inline__ __attribute__((always_inline))

//Branch prediction
#define GK_LIKELY(x)    __builtin_expect(!!(x), 1)
#define GK_UNLIKELY(x)  __builtin_expect(!!(x), 0)

// Attribute annotation to parse properties from GKComponent derived component classes
#define GKInspectable __attribute__((annotate("gk_inspectable")))
// ==========  GameplayKit.framework/Headers/GKRandomSource.h
//
//  GKRandomSource.h
//  GameplayKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A protocol for random sources that can generate random numbers. This is the minimal interface needed
 * to consume random values from a source; concrete subclasses should be used for configuring the
 * production of random values.
 * The availability of deterministic random sources is critical to creating reliable gameplay mechanics.
 * Ensure that systems that should not influence each other have unique random sources and avoid sharing
 * sources unless absolutely needed.
 *
 * This protocol allows you to provide custom random sources from classes that are not able to
 * derive from GKRandomSource directly.
 */
@protocol GKRandom

@required
/**
 * Returns the next integer in the random sequence and moves ahead to the next one.
 * The value is in the range of [INT32_MIN, INT32_MAX].
 * The lower bits are not guaranteed to be random so please use another
 * property for simple choices.
 *
 * @see nextBool
 * @see nextUniform
 */
- (NSInteger)nextInt;

/**
 * Returns the next unsigned value in the random sequence that is less than upperBound.
 * The value is in the range of [0, upperBound). Thus the value never equals or exceeeds upperBound.
 * The unsigned nature and upper bound allows implementations to use logical shifts to return a
 * value whose lower bits are more random than a similar call to nextInt.
 *
 * This is used to implement nextBool and nextUniform by default.
 */
- (NSUInteger)nextIntWithUpperBound:(NSUInteger)upperBound;

/**
 * Returns the next uniform float in the random sequence and moves ahead to the next one.
 * The value is in the range of [0.0, 1.0].
 * There is no weighting across the range so remapping this with a curve may give the best
 * sampling distribution for your algorithm.
 *
 * By default this should be based on nextIntWithUpperBound:. Implementions may base it on
 * another representation if needed.
 *
 * @see nextIntWithUpperBound:
 * @see nextInt
 */
- (float)nextUniform;

/**
 * Returns the next true or false value in the random sequence and moves ahead to the next one.
 * The value is either nonzero (true) or zero (false).
 * Use this for simple boolean switches in logic that don't require fuzzy evaluation.
 * For fuzzy evaluation use nextUniform.
 *
 * By default this should be based on nextIntWithUpperBound:. Implementations may base it on
 * another representation if needed.
 *
 * @see nextIntWithUpperBound:
 * @see nextUniform
 */
- (BOOL)nextBool;

@end

/**
 * A concrete random source that can generate random numbers. The implementation details are up to the system and
 * if a particular algorithm is needed then use one of the provided subclasses.
 *
 * For certain specialized applications a shared system source may be needed and for those instances there is
 * a wrapped interface over arc4random_*, accessible via +[GKRandomSource sharedRandom].
 *
 * @see GKARC4RandomSource
 * @see GKLinearCongruentialRandomSource
 * @see GKMersenneTwisterRandomSource
 * @see GKRandomSource.systemRandom
 */
GK_BASE_AVAILABILITY @interface GKRandomSource : NSObject <GKRandom, NSSecureCoding, NSCopying>

/**
 * Creates a new random source initialized using bits from an entropy source like SecRandomCopyBytes.
 * When used directly from the base class; this source is deterministic and performant but the underlying implementation
 * details are not specified. Use a subclass with a specific algorithm implementation guaranteed if your application requires
 * very stringent random source charateristics.
 *
 * @see GKARC4RandomSource
 * @see GKLinearCongruentialRandomSource
 * @see GKMersenneTwisterRandomSource
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 * Deserializes a random source from an NSCoder. All random sources support coding for serializing and deserializing the state
 * of the random source. Each subclass has its own contract for what parts of the state is preserved when serialized but the
 * general contract is that a serialized source must generate the same sequence of values as the original source would from the
 * instant it was serialized.
 *
 * Note that the sharedRandom instance is an exception as it is explicitly seedless and a shared singleton instance.
 * When serialized and deserialized it will return the current sharedRandom instance instead.
 */
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/**
 * Returns a shared instance of a random source that uses the system's underlying random source.
 * Using this instance modifies the outcome of future calls to the arc4random family of C calls. It is
 * also affected by calls to the C apis and should not be used for sources that are intended to
 * be deterministic.
 *
 * @discussion Note that while it may seem semantically similar to a GKARC4RandomSource, this is not a drop in replacement.
 */
+ (GKRandomSource *)sharedRandom;

/**
 * Returns a shuffled instance of the given array. The objects in the array are shuffled based on a Fisher-Yates shuffle.
 *
 * Any random, be it custom, source or a distribution, that can provide a number with an upper bound of at least the
 * array.count is suitable for this shuffle.
 */
- (NSArray *)arrayByShufflingObjectsInArray:(NSArray *)array;

@end

@interface NSArray<ObjectType> (GameplayKit)

/*
 * Returns a shuffled instance of this array using the given random source.
 */
- (NSArray<ObjectType>*)shuffledArrayWithRandomSource:(GKRandomSource*)randomSource;

/*
 * Returns a shuffled instance of this array using the systems underlying random source, as with [GKRandomSource sharedRandom]
 */
- (NSArray<ObjectType>*)shuffledArray;

@end


/**
 * A deterministic pseudo-random source that generates random numbers based on an arc4 algorithm.
 * This is a deterministic random source suitable for creating reliable gameplay mechanics.
 *
 * While deterministic, this is not a cryptographic random source, however it may be useful
 * for obfuscation of gameplay data in manner similar to a stream cipher.
 */
GK_BASE_AVAILABILITY @interface GKARC4RandomSource : GKRandomSource

/**
 * The seed used to stir the arc4 random source.
 * The seed is not encoded through archiving, but the equivalent state buffers are encoded.
 */
@property (nonatomic, copy) NSData *seed;

/**
 * Initializes an arc4 random source with bits from high entropy system resource like SecRandomCopyBytes.
 */
- (instancetype)init;

/**
 * Initializes an arc4 random source with bits from the seed.
 */
- (instancetype)initWithSeed:(NSData *)seed NS_DESIGNATED_INITIALIZER;

/**
 * Arc4 based random sources have repeatable initial sequences. If used for obfuscation you should
 * drop N values from the start, where N should be any number larger than 768 to ensure the initial
 * sequence is flushed.
 */
- (void)dropValuesWithCount:(NSUInteger)count;

@end


/**
 * A deterministic pseudo-random source that generates random numbers based on a linear congruential algorithm.
 * This is a deterministic random source suitable for creating reliable gameplay mechanics.
 * It is slightly faster than an Arc4 source, but less random. In particular the lower bits
 * of the generated values are less random than the higher bits.
 *
 * While deterministic, this is not a cryptographic random source. It is also not suitable
 * for obfuscation of gameplay data.
 */
GK_BASE_AVAILABILITY @interface GKLinearCongruentialRandomSource : GKRandomSource

/**
 * The seed used to stir the linear congruential random source.
 * The seed changes each time a random value is generated from this source, as the seed is the state buffer.
 * The seed is encoded through archiving.
 */
@property (nonatomic, assign) uint64_t seed;

/**
 * Initializes a linear congruential random source with bits from high entropy system resource like SecRandomCopyBytes.
 */
- (instancetype)init;

/**
 * Initializes a linear congruential random source with bits the given 64 bit seed.
 */
- (instancetype)initWithSeed:(uint64_t)seed NS_DESIGNATED_INITIALIZER;

@end

/**
 * A deterministic pseudo-random source that generates random numbers based on a mersenne twister algorithm.
 * This is a deterministic random source suitable for creating reliable gameplay mechanics.
 * It is slightly slower than an Arc4 source, but more random, in that it has a longer period until repeating sequences.
 *
 * While deterministic, this is not a cryptographic random source. It is however suitable
 * for obfuscation of gameplay data.
 */
GK_BASE_AVAILABILITY @interface GKMersenneTwisterRandomSource : GKRandomSource

/**
 * The seed used to stir the mersenne twister random source.
 * The seed is not encoded through archiving, but the equivalent state buffers are encoded.
 */
@property (nonatomic, assign) uint64_t seed;

/**
 * Initializes a linear congruential random source with bits from a high entropy system resource like SecRandomCopyBytes.
 */
- (instancetype)init;

/**
 * Initializes a linear congruential random source with bits the given 64 bit seed.
 */
- (instancetype)initWithSeed:(uint64_t)seed NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

// ==========  GameplayKit.framework/Headers/GKGraph.h
//
//  GKGraph.m
//  GameplayKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

NS_ASSUME_NONNULL_BEGIN

@class GKPolygonObstacle, GKGraphNode, GKGraphNode2D, GKGridGraphNode;

/**
 * Representation of a directed graph of GKGraphNodes
 */
GK_BASE_AVAILABILITY @interface GKGraph : NSObject <NSCopying, NSSecureCoding>

/**
 * The list of nodes in this graph
 */
@property (nullable, nonatomic, readonly) NSArray<GKGraphNode *> *nodes;

/**
 * Creates a graph with the provided array of nodes.
 * @params nodes the nodes to create the graph with
 */
+ (instancetype)graphWithNodes:(NSArray<GKGraphNode *> *)nodes;
- (instancetype)initWithNodes:(NSArray<GKGraphNode *> *)nodes;

/**
 * Connects the node to this graph via the lowest cost node to reach in this graph
 * @param node the node to connect
 * @param bidirectional should the connection be bidirectional? Otherwise it is one way connected into the graph
 */
- (void)connectNodeToLowestCostNode:(GKGraphNode *)node bidirectional:(BOOL)bidirectional;

/**
 * Removes nodes from this graph.  
 * All connections starting and/or ending with this node are removed.
 * @param nodes an array of nodes to be removed
 */
- (void)removeNodes:(NSArray<GKGraphNode *> *)nodes;

/**
 * Adds nodes to this graph.  No new connections are added.
 * If the node already exists in this graph this does nothing.
 * @param nodes and array of nodes to be added
 */
- (void)addNodes:(NSArray<GKGraphNode *> *)nodes;

/**
 * Attempts to find the optimal path between the two nodes indicated.
 * If such a path exists, it is returned in start to end order.
 * If it doesn't exist, the array returned will be empty.
 * Asserts if neither of these nodes are in this graph.  Use [GKGraphNode findPathFromNode:] instead.
 * @param startNode node to start pathing from
 * @param toNode goal node of the pathfinding attempt
 */
- (NSArray<__kindof GKGraphNode *> *)findPathFromNode:(GKGraphNode*)startNode toNode:(GKGraphNode*)endNode;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKSKNodeComponent.h
//
//  GKSKNodeComponent.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <GameplayKit/GKComponent.h>
#import <GameplayKit/GKAgent.h>

NS_ASSUME_NONNULL_BEGIN

@class SKNode;

/**
 A component that encapsulates a SpriteKit node.
 */
GK_BASE_AVAILABILITY_2 @interface GKSKNodeComponent : GKComponent <GKAgentDelegate>

/**
 * Creates a component that encapsulate the given SpriteKit node. When the component is 
 * added to an entity, the SKNode's entity property will be set.
 *
 * @param node Node to associate with the component.
 * @see SKNode.entity
 */
+ (instancetype)componentWithNode:(SKNode *)node;

/**
 * Initializes component to encapsulate the given SpriteKit node. When the component is
 * added to an entity, the SKNode's entity property will be set.
 *
 * @param node Node to associate with the component.
 * @see SKNode.entity
 */
- (instancetype)initWithNode:(SKNode *)node;

/**
 * The SpriteKit node this component encapsulates.
 */
@property (nonatomic, strong) SKNode *node;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKMeshGraph.h
//
//  GKMeshGraph.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <GameplayKit/GKGraph.h>
#import <GameplayKit/GKPrimitives.h>

NS_ASSUME_NONNULL_BEGIN

/** Adjusts how graph nodes are created when you triangulate a GKMeshGrapk
 
 @enum GKMeshGraphTriangulationModeVertices Graph nodes will be made at all triangle vertices
 @enum GKMeshGraphTriangulationModeCenters Graph nodes will be made at all triangle centers
 @enum GKMeshGraphTriangulationModeEdgeMidpoints Graph nodes will be made at midpoint of all triangle edges
 */
typedef NS_OPTIONS(NSUInteger, GKMeshGraphTriangulationMode) {
    GKMeshGraphTriangulationModeVertices = 1 << 0,
    GKMeshGraphTriangulationModeCenters = 1 << 1,
    GKMeshGraphTriangulationModeEdgeMidpoints = 1 << 2
};

/**
 * A collection of GKGraphNodes that are governed by a mesh formed by the space between a set of GKPolygonObstacles
 */
GK_BASE_AVAILABILITY_2 @interface GKMeshGraph<NodeType : GKGraphNode2D*> : GKGraph

/**
 *  Array of the extruded obstacles currently represented by this graph
 */
@property (nonatomic, readonly, nonnull) NSArray<GKPolygonObstacle *> *obstacles;

/**
 * The distance by which all obstacles are extruded.
 * This is most commonly the spatial bounding radius of a potential traveler on this path 
 */
@property (nonatomic, readonly) float bufferRadius;

/**
 * Specifies how graph nodes are generated when you triangulate this graph.
 * You can combine triangulation modes using the | (OR) operator
 *
 * @see GKMeshGraphTriangulationMode
 */
@property (nonatomic) GKMeshGraphTriangulationMode triangulationMode;

/**
 * The number of triangles currently in this mesh graph
 */
@property (nonatomic, readonly) NSUInteger triangleCount;

/**
 * Creates a graph with a given buffer radius
 * Obstacles can then be added to this graph prior to a call to [GKMeshGraph trianglulate]
 * @param bufferRadius the circular radius of a potential agent that will navigate this graph.  Obstacles are extruded by this amount to create the graph.  Must be positive.  Negative values are clipped to 0.0f
 * @param minCoordinate the minimum coordinate (lower left corner) of the bounding box that will encapsulate this graph.  No obstacles should fall outside this bounding box.
 * @param maxCoordinate the maximum coordinate (upper right corner) of the bounding box that will encapsulate this graph.  No obstacles should fall outside this bounding box.
 * @param nodeClass the class of the nodes that this graph should create.  Must descend from GKGraphNode2D
 */
+ (instancetype)graphWithBufferRadius:(float)bufferRadius minCoordinate:(vector_float2)min maxCoordinate:(vector_float2)max nodeClass:(Class)nodeClass;
- (instancetype)initWithBufferRadius:(float)bufferRadius minCoordinate:(vector_float2)min maxCoordinate:(vector_float2)max nodeClass:(Class)nodeClass;

/**
 * Same as [GKMeshGraph graphWithBufferRadius:minCoordinate:maxCoordinate:nodeClass:] where custom node class defaults to GKGraphNode2D
 */
+ (instancetype)graphWithBufferRadius:(float)bufferRadius minCoordinate:(vector_float2)min maxCoordinate:(vector_float2)max;
- (instancetype)initWithBufferRadius:(float)bufferRadius minCoordinate:(vector_float2)min maxCoordinate:(vector_float2)max;

/**
 * Adds obstacles to this mesh graph.  Only reflected after the next triangulate call.
 */
-(void)addObstacles:(NSArray<GKPolygonObstacle*>*)obstacles;

/**
 * Removes obstacles from this graph.  Only reflected after the next triangulate call.
 */
-(void)removeObstacles:(NSArray<GKPolygonObstacle*>*)obstacles;

/**
 * Connects the node to this graph by inserting it into an existing triangle and making the appropriate connections
 * Node must be in the space defined by the min and max coordinates of this graph.
 * @param node the node to connect
 */
- (void)connectNodeUsingObstacles:(NodeType)node;

/**
 * Generates a new triangle mesh for the given obstacles.  
 * This should be called after some number of calls to addObstacle
 * The negative space between all input obstacles are triangulated to create a mesh
 * This mesh is turned into a set of connected graph nodes based on
 */
-(void)triangulate;


/**
 * Returns the triangle at the given index
 * @see numTriangles
 * @param index the index of the triangle to be returned
 * @return the triangle at the given index
 */
-(GKTriangle)triangleAtIndex:(NSUInteger)index;

/**
 * Returns the class of the specified generic index
 */
- (nonnull Class)classForGenericArgumentAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKRTree.h
//
//  GKRTree.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>
#import <GameplayKit/GKPrimitives.h>

NS_ASSUME_NONNULL_BEGIN

/** Used to adjust the way in which RTree nodes are split when they grow too large.
 
 @enum GKRTreeSplitStrategyHalve Specifies that nodes should be split in half based on insert order.
 @enum GKRTreeSplitStrategyLinear Specifies that nodes should be split along the best dividing axis.
 @enum GKRTreeSplitStrategyQuadratic Specifies that nodes should be split into groups with the least area.
 @enum GKRTreeSplitStrategyReduceOverlap Specifies that nodes should be split as to reduce overlap.
 */
typedef NS_ENUM(NSInteger, GKRTreeSplitStrategy) {
    GKRTreeSplitStrategyHalve = 0,
    GKRTreeSplitStrategyLinear = 1,
    GKRTreeSplitStrategyQuadratic = 2,
    GKRTreeSplitStrategyReduceOverlap = 3
};


/**
 * An R-tree is a data structure that partitions axis aligned bounding rectangles into groups spatially.
 * When a group goes to large, it is split according to its split strategy into two new groups.
 * Fast queries can be made on these partition bounding rectangles.
 */
GK_BASE_AVAILABILITY_2 @interface GKRTree <ElementType : NSObject*>: NSObject

/**
 * Amount of array items to reserve before a query.
 * This improves query performance at the cost of memory
 */
@property NSUInteger queryReserve;

/**
 * Creates an RTree with a given maximum number of children per node.  Nodes that grow beyond this number of children will be split.
 *
 * @param maxNumberOfChildren the maximum number of children per node before splitting
 */
+(instancetype)treeWithMaxNumberOfChildren:(NSUInteger)maxNumberOfChildren;
-(instancetype)initWithMaxNumberOfChildren:(NSUInteger)maxNumberOfChildren NS_DESIGNATED_INITIALIZER;

/**
 * Adds an element with the specified bounding rect to this RTree.  The supplied splitting strategy is used if the node this element would be added to needs to be split.
 *
 * @param element the element to be added
 * @param boundingRectMin the min point (lower left) on the bounding rect of the element to be added
 * @param boundingRectMax the min point (upper right) on the bounding rect of the element to be added
 * @param splitStrategy the splitting strategy to be used if the node this element would be added to needs to be split
 */
-(void)addElement:(ElementType)element boundingRectMin:(vector_float2)boundingRectMin boundingRectMax:(vector_float2)boundingRectMax splitStrategy:(GKRTreeSplitStrategy)splitStrategy;

/**
 * Removes an element with the specified bounding rect from this RTree.
 *
 * @param element the element to be removed
 * @param boundingRectMin the min point (lower left) on the bounding rect of the element to be removed
 * @param boundingRectMax the min point (upper right) on the bounding rect of the element to be removed
 */
-(void)removeElement:(ElementType)element boundingRectMin:(vector_float2)boundingRectMin boundingRectMax:(vector_float2)boundingRectMax;

/**
 * Queries all the elements that are in this RTree within the given bounding rect.
 *
 * @param min the min point (lower left) of the rect to query
 * @param rectMax the max point (upper right) of the rect to query
 *
 * @return an NSArray of all of the elements that fall within the query rect
 */
-(NSArray<ElementType>*)elementsInBoundingRectMin:(vector_float2)rectMin rectMax:(vector_float2)rectMax;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKComponent.h
//
//  GKComponent.h
//  GameplayKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

NS_ASSUME_NONNULL_BEGIN

@class GKEntity;

/**
 A component is the data and logic for one part of an object in an entity-component system.
 Entities have many components but components are associated with only a single entity.
 
 Components across entities are best arranged in ComponentSystems, which are homogeneous
 collections of components that the game logic updates in a deterministic order.
 
 @see GKComponentSystem
 */
GK_BASE_AVAILABILITY @interface GKComponent : NSObject <NSCopying, NSSecureCoding>

/**
 * The entity that this component belongs to. Defaults to nil until the component is added to an entity.
 */
@property (nullable, nonatomic, readonly, weak) GKEntity *entity;

/**
 * Updates the component with the given delta time since the last update. Each component should
 * perform its time-based logic in this method.
 */
- (void)updateWithDeltaTime:(NSTimeInterval)seconds;

/**
 * Override this to perform game logic when this component is added to an entity
 */
-(void)didAddToEntity;

/**
 * Override this to perform game logic before this entity is removed from it's entity
 */
-(void)willRemoveFromEntity;

@end


/**
 * A component system is a homogeneous collection of components that are intended to be called at the same time.
 * The system is homogeneous, meaning it only allows members of the same class into the system.
 */
GK_BASE_AVAILABILITY @interface GKComponentSystem<ComponentType : GKComponent *> : NSObject<NSFastEnumeration>

/**
 * The collection's component class. Any selector the component supports can be called on the system and it will be forwarded
 * to each of the components in the collection.
 */
@property (nonatomic, readonly) Class componentClass;

/**
 * The array of components currently in the system.
 */
@property (nonatomic, readonly, retain) NSArray<ComponentType> *components;

/**
 * Supports getting components via a [] subscript.
 */
- (ComponentType)objectAtIndexedSubscript:(NSUInteger)idx;

/**
 * Initializes a system for the given component class. The receiver can now only accept components of the given class.
 */
- (instancetype)initWithComponentClass:(Class)cls;

/**
 * Adds a component to the system. The component must be of the same class as the system's componentClass.
 * The component is added to the tail of the collection and will be processed after components that were added before it.
 *
 * @throws NSInvalidArgumentException if the component added is not a kind of the system's componentClass.
 */
- (void)addComponent:(ComponentType)component;

/**
 * Adds the supported component from the entity's component collection.
 * This is conceptually the same as the pseudo-code:
 *
 * for (GKComponent *component in entity.components)
 *    if (component.class == system.componentClass)
 *        [system addComponent:component]
 *
 * @see GKEntity.components
 */
- (void)addComponentWithEntity:(GKEntity *)entity;

/**
 * Removes the supported component from the entity's component collection
 * This is conceptually the same as the pseudo-code:
 *
 * for (GKComponent *component in entity.components)
 *    if (component.class == system.componentClass)
 *        [system removeComponent:component]
 */
- (void)removeComponentWithEntity:(GKEntity *)entity;

/**
 * Removes a component from the system
 *
 * Does nothing if the component is not in this system
 */
- (void)removeComponent:(ComponentType)component;


#pragma mark Component message forwarding

/**
 * Updates each component with the given delta time since the last update. Each component thus performs its time
 * based logic with a single message.
 */
- (void)updateWithDeltaTime:(NSTimeInterval)seconds;

/**
 * Returns the class of the specified generic index
 */
- (nonnull Class)classForGenericArgumentAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKPath.h
//
//  GKPath.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import "GameplayKitBase.h"
#import <Foundation/Foundation.h>
#import <simd/simd.h>

@class GKGraphNode;

NS_ASSUME_NONNULL_BEGIN

GK_BASE_AVAILABILITY @interface GKPath : NSObject

/**
 * Radius of the pathway.  Defines a spatial area that the path occupies.
 * This can be though of as the union between rectangles between all points, and circles at each point
 */
@property (nonatomic, assign) float radius;

/**
 * Number of points in this path
 */
@property (readonly) NSUInteger numPoints;

/**
 * Does this path loop back on itself, creating a cycle?
 */
@property (nonatomic, assign, getter=isCyclical) BOOL cyclical;

/**
 * Creates a path from an array of points
 * @param points an array of points to make a path from
 * @param radius radius of the path to create
 * @param cyclical is the path a cycle that loops back on itself?
 */
#if (defined(SWIFT_SDK_OVERLAY_GAMEPLAYKIT_EPOCH) && SWIFT_SDK_OVERLAY_GAMEPLAYKIT_EPOCH >= 1)
+ (instancetype)pathWithPoints:(vector_float2 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical NS_REFINED_FOR_SWIFT;
- (instancetype)initWithPoints:(vector_float2 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical NS_REFINED_FOR_SWIFT;
+ (instancetype)pathWithFloat3Points:(vector_float3 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical NS_AVAILABLE(10_12, 10_0) NS_REFINED_FOR_SWIFT;
- (instancetype)initWithFloat3Points:(vector_float3 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical NS_AVAILABLE(10_12, 10_0) NS_REFINED_FOR_SWIFT;
#else
+ (instancetype)pathWithPoints:(vector_float2 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical;
- (instancetype)initWithPoints:(vector_float2 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical;
+ (instancetype)pathWithFloat3Points:(vector_float3 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical NS_AVAILABLE(10_12, 10_0);
- (instancetype)initWithFloat3Points:(vector_float3 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical NS_AVAILABLE(10_12, 10_0);
#endif

/**
 * Creates a path from an array of graph nodes (often a result of pathfinding)
 * Accepts GKGraphNode2D and GKGraphNode3D
 * Cyclical is set to NO
 * @param graphNodes an array of graph nodes to make a path from
 * @param radius radius of the path to create
 * @see GKGraphNode
 */
+ (instancetype)pathWithGraphNodes:(NSArray<GKGraphNode*> *)graphNodes radius:(float)radius;
- (instancetype)initWithGraphNodes:(NSArray<GKGraphNode*> *)graphNodes radius:(float)radius;

/*
 * Returns the 2D point at the given index.  Returns (x,y,0) if the underlying points are (x,y)
 */
-(vector_float2)pointAtIndex:(NSUInteger)index NS_DEPRECATED(10_11, 10_12, 9_0, 10_0);
-(vector_float2)float2AtIndex:(NSUInteger)index NS_AVAILABLE(10_12, 10_0);

/*
 * Returns the 3D point at the given index.  Returns (x,y,0) if the underlying points are (x,y)
 */
-(vector_float3)float3AtIndex:(NSUInteger)index NS_AVAILABLE(10_12, 10_0);

@end

NS_ASSUME_NONNULL_END

// ==========  GameplayKit.framework/Headers/GKNoiseMap.h
//
//  GKNoiseMap.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

@class GKNoiseSource;
@class GKNoise;

NS_ASSUME_NONNULL_BEGIN

/**
 * GKNoiseMap represents an extracted portion of sampled points from continuous 3D noise.  Extracted values are useful
 * for 2D and 3D games.  Noise values may be queried, set to explicit values or used as input for other uses,
 * including textures and tile maps.
 *
 * @see GKNoiseSource
 * @see GKNoise
 * @see SKTexture
 * @see SKTileMapNode
 */
GK_BASE_AVAILABILITY_2 @interface GKNoiseMap : NSObject

/**
 * The size of the 2D plane to extract from the 3D noise space, in noise space coordinates.  Used together
 * with origin to determine the bounds of the extracted plane.  A smaller size captures a more "zoomed in"
 * view of the noise, and vice versa.
 *
 * @see origin
 */
@property (nonatomic, readonly) vector_double2 size;

/**
 * The origin of the 2D plane to extract from the 3D noise space, in noise space coordinates.  Used together
 * with size to determine the bounds of the extracted plane.
 *
 * @see size
 */
@property (nonatomic, readonly) vector_double2 origin;

/**
 * The number of equally-spaced samples to make across the 2D plane.  A higher number of samples produces finer
 * resolution at the expense of increased memory.
 */
@property (nonatomic, readonly) vector_int2 sampleCount;

/**
 * Whether the values at the edges of the 2D plane are modified to allow seamless tiling of the extracted noise map.
 */
@property (nonatomic, readonly, getter=isSeamless) BOOL seamless;

/**
 * Initializes a noise map with constant noise of 0.0 at all positions.
 */
- (instancetype)init;

/**
 * Initializes a noise map with specified noise.
 *
 * @param noise The 3D noise from which to sample a 2D plane.
 */
+ (instancetype)noiseMapWithNoise:(GKNoise *)noise;

/**
 * Initializes a noise map with specified noise and parameters.
 *
 * @param noise The 3D noise from which to sample a 2D plane.
 * @param size The size of the 2D plane to extract from the 3D noise space, in noise space coordinates.
 * @param origin The origin of the 2D plane to extract from the 3D noise space, in noise space coordinates.
 * @param sampleCount The number of equally-spaced samples to make across the 2D plane.
 * @param seamless Whether the values at the edges of the 2D plane are modified to allow seamless tiling of the extracted noise map.
 */
+ (instancetype)noiseMapWithNoise:(GKNoise *)noise size:(vector_double2)size origin:(vector_double2)origin sampleCount:(vector_int2)sampleCount seamless:(BOOL)seamless;

/**
 * Initializes a noise map with specified noise.
 *
 * @param noise The 3D noise from which to sample a 2D plane.
 */
- (instancetype)initWithNoise:(GKNoise *)noise;

/**
 * Initializes a noise map with specified noise and parameters.
 *
 * @param noise The 3D noise from which to sample a 2D plane.
 * @param size The size of the 2D plane to extract from the 3D noise space, in noise space coordinates.
 * @param origin The origin of the 2D plane to extract from the 3D noise space, in noise space coordinates.
 * @param sampleCount The number of equally-spaced samples to make across the 2D plane.
 * @param seamless Whether the values at the edges of the 2D plane are modified to allow seamless tiling of the extracted noise map.
 */
- (instancetype)initWithNoise:(GKNoise *)noise size:(vector_double2)size origin:(vector_double2)origin sampleCount:(vector_int2)sampleCount seamless:(BOOL)seamless NS_DESIGNATED_INITIALIZER;

/**
 * The noise map value at the specified sample index of the 2D plane.
 *
 * @param position Sample index of the extracted 2D plane at which to query the value.  Valid range
 * is from 0 to sampleCount-1, inclusive.
 *
 * @return The noise map value at the specified sample index.
 */
- (float)valueAtPosition:(vector_int2)position;

/**
 * The noise map value at the specified sample point of the 2D plane.  Returns an interpolated value for
 * points not aligned on integer boundaries.
 *
 * @param position Sample point of the extracted 2D plane at which to query the value.  Valid range
 * is from 0.0 to sampleCount-1.0, inclusive.
 *
 * @return The noise map value at the specified sample index. Returns an interpolated value for points not
 * aligned on integer boundaries.
 */
- (float)interpolatedValueAtPosition:(vector_float2)position;

/**
 * Sets the specified value to the noise map at the specified sample index of the 2D plane.
 *
 * @param value The noise map value to assign to the specified position.
 * @param position Sample index of the extracted 2D plane at which to set the value.  Valid range
 * is from 0 to sampleCount-1, inclusive.
 *
 * @return The noise map value at the specified sample index.
 */
- (void)setValue:(float)value atPosition:(vector_int2)position;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKNoise.h
//
//  GKNoise.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>
#import <SpriteKit/SpriteKitBase.h>

@class GKNoiseSource;

NS_ASSUME_NONNULL_BEGIN

/**
 * GKNoise is the object used to manipulate and combine noise in continuous 3D space.  It takes a GKNoiseSource as input.
 * To extract and use a portion of the noise within the 3D space use the GKNoiseMap class.
 *
 * @see GKNoiseSource
 * @see GKNoiseMap
 */
GK_BASE_AVAILABILITY_2 @interface GKNoise : NSObject

/**
 * Color gradient of this noise, represented as 'value : color' pairs.  Utilized when this noise is rendered to a texture.
 */
@property (nonatomic, copy) NSDictionary<NSNumber *, SKColor *> *gradientColors;

/**
 * Initializes a constant noise of 0.0 at all positions.
 */
- (instancetype)init;

/**
 * Initializes a noise with the specified noise source.
 *
 * @param noiseSource The noise source to use to initially populate the 3D noise space.
 */
+ (instancetype)noiseWithNoiseSource:(GKNoiseSource *)noiseSource;

/**
 * Initializes a noise with the specified noise source and parameters.
 *
 * @param noiseSource The noise source to use to initially populate the 3D noise space.
 * @param gradientColors The color gradient to use for this noise in 'value : color' pairs.
 */
+ (instancetype)noiseWithNoiseSource:(GKNoiseSource *)noiseSource gradientColors:(NSDictionary<NSNumber *, SKColor *> *)gradientColors;

/**
 * Initializes a noise with the specified noise source.
 *
 * @param noiseSource The noise source to use to initially populate the 3D noise space.
 */
- (instancetype)initWithNoiseSource:(GKNoiseSource *)noiseSource;

/**
 * Initializes a noise with the specified noise source and parameters.
 *
 * @param noiseSource The noise source to use to initially populate the 3D noise space.
 * @param gradientColors The color gradient to use for this noise in 'value : color' pairs.
 */
- (instancetype)initWithNoiseSource:(GKNoiseSource *)noiseSource gradientColors:(NSDictionary<NSNumber *, SKColor *> *)gradientColors NS_DESIGNATED_INITIALIZER;

/**
 * Initializes a composite noise from one or more component noises.  Useful for combining and layering noises together.
 *
 * @param noises The component noises to combine.
 * @param selectionNoise The noise that governs which component noise is chosen for each position of the resulting noise.
 * The range of values is equally-subdivided for each component noise.
 */
+ (instancetype)noiseWithComponentNoises:(NSArray<GKNoise *> *)noises selectionNoise:(GKNoise *)selectionNoise;

/**
 * Initializes a composite noise from one or more component noises.  Useful for combining and layering noises together.
 *
 * @param noises The component noises to combine.
 * @param selectionNoise The noise that governs which component noise is chosen for each position of the resulting noise.
 * The range of values is equally-subdivided for each component noise.
 * @param componentBoundaries The noise value boundaries of the selection noise to use for the component noises.  Specify
 * one less boundary than the number of component noises.  This is a parallel array to blendDistances.
 * @param blendDistances The size of smoothing that is applied to boundaries where two component noises meet.  Specify
 * one less blend distance than the number of component noises.  This is a parallel array to componentBoundaries.
 */
+ (instancetype)noiseWithComponentNoises:(NSArray<GKNoise *> *)noises selectionNoise:(GKNoise *)selectionNoise componentBoundaries:(NSArray<NSNumber *> *)componentBoundaries boundaryBlendDistances:(NSArray<NSNumber *> *)blendDistances;

/**
 * The noise value at the specified sample index of the 2D plane.
 *
 * @param position Sample index of the extracted 2D plane at which to query the value
 *
 * @return The noise map value at the specified position.
 */
- (float)valueAtPosition:(vector_float2)position;

/**
 * Takes the absoltue value of all noise positions.
 */
- (void)applyAbsoluteValue;

/**
 * Clamps all noise values to the specified bounds.
 *
 * @param lowerBound The noise value lower bound.
 * @param upperBound The noise value upper bound.
 */
- (void)clampWithLowerBound:(double)lowerBound upperBound:(double)upperBound;

/**
 * Raises all noise values to the specified power.
 *
 * @param power The power to which to raise all noise values.
 */
- (void)raiseToPower:(double)power;

/**
 * Inverts all noise values, from positive to negative and vice versa.
 */
- (void)invert;

/**
 * Applies a turbulent displacement to all noise values.
 */
- (void)applyTurbulenceWithFrequency:(double)frequency power:(double)power roughness:(int)roughness seed:(int32_t)seed;

/**
 * Remaps all noise values to a smooth curve that passes through the specified control points.
 *
 * @param controlPoints Pairs of 'input : output' values to use as control points for the smooth remapping curve.
 * Duplicate input values are not permitted.
 */
- (void)remapValuesToCurveWithControlPoints:(NSDictionary<NSNumber *, NSNumber *> *)controlPoints;

/**
 * Remaps all noise values to one or more terraces with peaks.  Useful for creating valleys and trenches.
 *
 * @param peakInputValues Inputs positions of terrace peaks.
 * @param inverted Governs the curve direction from peak to peak.
 */
- (void)remapValuesToTerracesWithPeaks:(NSArray<NSNumber *> *)peakInputValues terracesInverted:(BOOL)inverted;

/**
 * Translates all noise values by the specified amount.
 *
 * @param delta The amount by which to move all noise values.
 */
- (void)moveBy:(vector_double3)delta;

/**
 * Scales all noise values by the specified amount.
 *
 * @param factor The factor by which to scale all noise values.
 */
- (void)scaleBy:(vector_double3)factor;

/**
 * Rotates all noise values by the specified amount.
 *
 * @param radians The number of radians in x-, y- and z-axes by which to rotate all noise values.
 */
- (void)rotateBy:(vector_double3)radians;

/**
 * Adds all noise values by the noise values at the same position in specified noise.
 *
 * @param noise The noise from which to add values to this noise.
 */
- (void)addWithNoise:(GKNoise *)noise;

/**
 * Multiplies all noise values by the noise values at the same position in specified noise.
 *
 * @param noise The noise from which to multiply values to this noise.
 */
- (void)multiplyWithNoise:(GKNoise *)noise;

/**
 * Takes the minimum value between this noise and the specified noise at each position.
 *
 * @param noise The noise to compare against this noise at each position in determining which to take the minimum value from.
 */
- (void)minimumWithNoise:(GKNoise *)noise;

/**
 * Takes the maximum value between this noise and the specified noise at each position.
 *
 * @param noise The noise to compare against this noise at each position in determining which to take the maximum value from.
 */
- (void)maximumWithNoise:(GKNoise *)noise;

/**
 * Raises all noise values to the power of the value at the same position of the specified noise.
 *
 * @param noise The noise from which to raise this noise's values by.
 */
- (void)raiseToPowerWithNoise:(GKNoise *)noise;

/**
 * Displaces all noise values by the values at the same positions of the specified noises.
 *
 * @param xDisplacementNoise The noise from which to displace along the x-axis this noise's values at the same positions.
 * @param yDisplacementNoise The noise from which to displace along the y-axis this noise's values at the same positions.
 * @param zDisplacementNoise The noise from which to displace along the z-axis this noise's values at the same positions.
 */
- (void)displaceXWithNoise:(GKNoise *)xDisplacementNoise yWithNoise:(GKNoise *)yDisplacementNoise zWithNoise:(GKNoise *)zDisplacementNoise;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKStrategist.h
//
//  GKStrategist.h
//  GameplayKit
//
//  Copyright (c) 2015 Apple. All rights reserved.
//

#import <GameplayKit/GKGameModel.h>
#import <GameplayKit/GKRandomSource.h>

NS_ASSUME_NONNULL_BEGIN

@protocol GKStrategist <NSObject>

/**
 * The game model that we wish to select updates for.
 */
@property (nonatomic, retain, nullable) id<GKGameModel> gameModel;

/**
 * A random source to use when breaking ties between equally-strong moves when calling bestMoveForPlayer
 * or when selecting a random move when randomMoveForPlayer is called. If set to nil, bestMoveForPlayer
 * and randomMoveForPlayer will simply return the first best move available.
 */
@property (nonatomic, retain, nullable) id<GKRandom> randomSource;

- (nullable id<GKGameModelUpdate>)bestMoveForActivePlayer;

@end

NS_ASSUME_NONNULL_END// ==========  GameplayKit.framework/Headers/GKObstacle.h
//
//  GKObstacle.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

NS_ASSUME_NONNULL_BEGIN


/**
 * Represents an impassible area in 2D space.
 * Able to be avoided by GKAgent's steering functions
 * GKGraph can generate navigation graphs from a list of obstacles
 */
GK_BASE_AVAILABILITY @interface GKObstacle : NSObject

@end


/**
 * An obstacle with an impassible radius
 */
GK_BASE_AVAILABILITY @interface GKCircleObstacle : GKObstacle

/**
 * Radius of the impassible circle
 */
@property (nonatomic, assign) float radius;

/**
 * Position of the center of the circle in 2D space.
 */
@property (nonatomic, assign) vector_float2 position;

+ (instancetype)obstacleWithRadius:(float)radius;
- (instancetype)initWithRadius:(float)radius NS_DESIGNATED_INITIALIZER;

@end


/**
 * An obstacle with an impassible closed polygon
 */
GK_BASE_AVAILABILITY @interface GKPolygonObstacle : GKObstacle <NSSecureCoding>

/**
 * Number of vertices on this polygon
 */
@property (nonatomic,readonly) NSUInteger vertexCount;

/**
 * Creates a polygon obstacle with an array of points.
 * @param points array of points in counter-clockwise order that are the vertices of a convex polygon
 * @param numPoints the number of points in the array
 */
#if (defined(SWIFT_SDK_OVERLAY_GAMEPLAYKIT_EPOCH) && SWIFT_SDK_OVERLAY_GAMEPLAYKIT_EPOCH >= 1)
+ (instancetype)obstacleWithPoints:(vector_float2 *)points count:(size_t)numPoints NS_REFINED_FOR_SWIFT;
- (instancetype)initWithPoints:(vector_float2 *)points count:(size_t)numPoints NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;
#else
+ (instancetype)obstacleWithPoints:(vector_float2 *)points count:(size_t)numPoints;
- (instancetype)initWithPoints:(vector_float2 *)points count:(size_t)numPoints NS_DESIGNATED_INITIALIZER;
#endif

/**
 * Returns the vertex at the indicated index
 * @param index index of the vertex to retrieve
 */
- (vector_float2)vertexAtIndex:(NSUInteger)index;

@end

/**
 * An obstacle with an impassible radius in 3D space
 * For use with GKAgent3D.  Using this with a GKAgent2D is no different than using GKCircleObstacle.
 */
GK_BASE_AVAILABILITY_2 @interface GKSphereObstacle : GKObstacle

/**
 * Radius of the impassible circle
 */
@property (nonatomic, assign) float radius;

/**
 * Position of the center of the circle in 3D space.
 */
@property (nonatomic, assign) vector_float3 position;

+ (instancetype)obstacleWithRadius:(float)radius;
- (instancetype)initWithRadius:(float)radius NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

// ==========  GameplayKit.framework/Headers/GKEntity.h
//
//  GKEntity.h
//  GameplayKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

NS_ASSUME_NONNULL_BEGIN

@class GKComponent;

/**
 * An entity is the general purpose object in an entity-component system.
 * Entites have many components but components are associated with only a single entity.
 * 
 * Note: GKEntity supports NSCopying and NSSecureCoding, but your custom GKComponent's must also support NSCopying and NSSecureCoding
 *
 * @see GKComponent
 * @see GKComponentSystem
 */
GK_BASE_AVAILABILITY @interface GKEntity : NSObject <NSCopying, NSSecureCoding>

/**
 * Creates a new entity ready to have components added to it.
 */
+ (instancetype)entity;

/**
 * Creates a new entity ready to have components added to it.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 * General update loop for this entity, which also updates all components in this entity that are not currently
 * in a dedicated component system.
 *
 * Per-entity component updates is a simpler and less flexible option to using per-component updates,
 * however both can not be allowed to occur at the same time for a component. Thus components that are
 * added to dedicated component systems will not be updated here as they have opted for the more powerful
 * feature of per-component systems. Update those components via their system instead.
 *
 * @see GKComponentSystem
 * @param seconds elapsed time, in seconds, since last frame
 */
- (void)updateWithDeltaTime:(NSTimeInterval)seconds;

/**
 * Access the current set of components as an array.
 * Note: this is not the internal array of components, but rather a newly created array of the current component mapping.
 */
@property (nonatomic, readonly, retain) NSArray<GKComponent *> *components;

/**
 * Adds a component to this entity.  If a component of the same class already exists it is overwritten with the new component.
 * @param component the component to be added
 * @see GKComponent
 */
- (void)addComponent:(GKComponent *)component;

/**
 * Removes the component of the indicates class from this entity
 * @param componentClass the class of the component you want to remove
 */
#if (defined(SWIFT_SDK_OVERLAY_GAMEPLAYKIT_EPOCH) && SWIFT_SDK_OVERLAY_GAMEPLAYKIT_EPOCH >= 1)
- (void)removeComponentForClass:(Class)componentClass NS_REFINED_FOR_SWIFT;
#else
- (void)removeComponentForClass:(Class)componentClass;
#endif

/**
 * Gets the component of the indicated class.  Returns nil if entity does not have this component
 * @param componentClass the class of the component you want to get
 */
#if (defined(SWIFT_SDK_OVERLAY_GAMEPLAYKIT_EPOCH) && SWIFT_SDK_OVERLAY_GAMEPLAYKIT_EPOCH >= 1)
- (nullable GKComponent *)componentForClass:(Class)componentClass NS_REFINED_FOR_SWIFT;
#else
 - (nullable GKComponent *)componentForClass:(Class)componentClass NS_SWIFT_UNAVAILABLE("Exposed in Swift as componentForClass<ComponentType: GKComponent>(componentClass: ComponentType.Type) -> ComponentType?");
#endif

@end

NS_ASSUME_NONNULL_END

// ==========  GameplayKit.framework/Headers/SpriteKit+Additions.h
/**
 @header
 
 
 SpriteKit framework category additions related to GameplayKit integration.
 
 
 @copyright 2016 Apple, Inc. All rights reserve.
 
 */

#import <SpriteKit/SpriteKit.h>

#import <GameplayKit/GKEntity.h>
#import <GameplayKit/GKNoiseMap.h>
#import <GameplayKit/GKObstacle.h>
#import <GameplayKit/GKScene.h>

NS_ASSUME_NONNULL_BEGIN

@interface SKNode (GameplayKit)

/**
 * Returns an array of GKPolygonObstacles from a group of SKSpriteNode's textures in scene space.
 *
 * @see GKObstacleGraph
 */
+ (NSArray<GKPolygonObstacle*> *)obstaclesFromSpriteTextures:(NSArray<SKNode*>*)sprites accuracy:(float)accuracy;

/**
 * Returns an array of GKPolygonObstacles from a group of SKNode's transformed bounds in scene space.
 *
 * @see GKObstacleGraph
 */
+ (NSArray<GKPolygonObstacle*> *)obstaclesFromNodeBounds:(NSArray<SKNode*>*)nodes;

/**
 * Returns an array of GKPolygonObstacles from a group of SKNode's physics bodies in scene space.
 *
 * @see GKObstacleGraph
 */
+ (NSArray<GKPolygonObstacle*> *)obstaclesFromNodePhysicsBodies:(NSArray<SKNode*>*)nodes;

/**
 * The GKEntity associated with the node via a GKSKNodeComponent.
 *
 * @see GKEntity
 */
@property (nonatomic, weak) GKEntity *entity NS_AVAILABLE(10_12, 10_0);

@end

/**
 * Adds conformance to GKSceneRootNodeType for usage as rootNode of GKScene 
 */
@interface SKScene (GameplayKit) <GKSceneRootNodeType>

@end

@interface SKTileMapNode (GameplayKit)

/**
 * Create a set of layered tile map nodes with the specified tile set and dimensions, and fill each layer based on the provided noise map. Each 
 * layer will be partially filled with a tile group using values from the noise map that fall below the corresponding values in the thresholds 
 * array. The values in the noise map range from -1 to 1, and the provided threshold values are implicitly bounded with the values -1.0 and 1.0. 
 * Each threshold value corresponds with a tile group in the tile set, starting with the first tile group in the set. If, for example, we passed 
 * in a thresholds array with the values [-0.5, 0.0, 0.5], this method would return an array of four tile maps. The first tile map would contain 
 * the first tile group (i.e., tileSet.tileGroups[0]) within tiles that fall between the threshold values -1.0 and -0.5 in the noise map. The 
 * second tile map would contain the second tile group (i.e., tileSet.tileGroups[1]) within tiles that fall between the threshold values -0.5 and 
 * 0.0 in the noise map. The third tile map would contain the third tile group (i.e., tileSet.tileGroups[2]) within tiles that fall between the 
 * threshold values 0.0 and 0.5 in the noise map. And finally, the fourth tile map would contain the fourth tile group 
 * (i.e., tileSet.tileGroups[3]) within tiles that fall between the threshold values 0.5 and 1.0.
 *
 * @param tileSet the tile set that is used to render the tiles
 * @param columns the number of columns in each map that can hold tiles
 * @param rows the number of rows in each map that can hold tiles
 * @param tileSize the size of each tile in points
 * @param noiseMap the noise map we wish to use to fill each layer
 * @param thresholds the thresholds for each tile group in the tile set
 */
+ (NSArray<SKTileMapNode *> *)tileMapNodesWithTileSet:(SKTileSet *)tileSet columns:(NSUInteger)columns rows:(NSUInteger)rows tileSize:(CGSize)tileSize fromNoiseMap:(GKNoiseMap *)noiseMap tileTypeNoiseMapThresholds:(NSArray<NSNumber *> *)thresholds;

@end


@interface SKTexture (GameplayKit)

/**
 * Create a texture from a GKNoiseMap.
 *
 * @param noiseMap the GKNoiseMap from which to create the texture.
 */
+ (instancetype)textureWithNoiseMap:(GKNoiseMap *)noiseMap NS_AVAILABLE(10_12, 10_0);

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKQuadtree.h
//
//  GKQuadTree.h
//  GKQuadTreeTest
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>
#import <GameplayKit/GKPrimitives.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The individual node(s) that make up a GKQuadtree.
 * Used as a hint for faster removal via [GKQuadtree removeData:WithNode:]
 */
GK_BASE_AVAILABILITY_2 @interface GKQuadtreeNode : NSObject

/* The quad associated with this quad tree node */
@property (nonatomic, readonly) GKQuad quad;

@end


/**
 * A tree data structure where each level has 4 children that subdivide a given space into the four quadrants.
 * Stores arbitrary NSObject data via points and quads.
 */
GK_BASE_AVAILABILITY_2 @interface GKQuadtree <ElementType : NSObject*>: NSObject

/**
 * Creates a quadtree with a bounding quad and minimum allowed cell size
 *
 * @param quad the quad that specifies of the bounds of this quadtree. Elements must only be within these bounds.
 * @param minimumCellSize the minimum allowed cell size.  The quadtree will not create quadrants that have a width or height smaller than this size.
 */
+(instancetype)quadtreeWithBoundingQuad:(GKQuad)quad minimumCellSize:(float)minCellSize;
-(instancetype)initWithBoundingQuad:(GKQuad)quad minimumCellSize:(float)minCellSize NS_DESIGNATED_INITIALIZER;

/**
 * Adds an NSObject to this quadtree with a given point.
 * This data will always reside in the leaf node its point is in.
 *
 * @param element the element to store
 * @param point the point associated with the element you want to store
 * @return the quadtree node the element was added to
 */
-(GKQuadtreeNode*)addElement:(ElementType)element withPoint:(vector_float2)point;

/**
 * Adds an NSObject to this quadtree with a given quad.
 * This data will reside in the lowest node that its quad fits in completely.
 *
 * @param data the data to store
 * @param quad the quad associated with the element you want to store
 * @return the quad tree node the element was added to
 */
-(GKQuadtreeNode*)addElement:(ElementType)element withQuad:(GKQuad)quad;

/**
 * Returns all of the elements in the quadtree node this point would be placed in
 *
 * @param point the point to query
 * @return an NSArray of all the data found at the quad tree node this point would be placed in
 */
-(NSArray<ElementType>*)elementsAtPoint:(vector_float2)point;

/**
 * Returns all of the elements that resides in quad tree nodes which intersect the given quad
 *
 * @param quadOrigin the quad you want to test
 * @return an NSArray of all the elements in all of the nodes that intersect the given quad
 *
 */
-(NSArray<ElementType>*)elementsInQuad:(GKQuad)quad;

/**
 * Removes the given NSObject from this quad tree.
 * Note that this is an exhaustive search and is slow.
 * Cache the relevant GKQuadTreeNode and use removeElement:WithNode: for better performance.
 *
 * @param element the data to be removed
 * @return returns YES if the data was removed, NO otherwise
 */
-(BOOL)removeElement:(ElementType)element;

/**
 * Removes the given NSObject from the given quadtree node
 * Note that this is not an exhaustive search and is faster than removeData:
 *
 * @param element the element to be removed
 * @param node the node in which this data resides
 * @return returns YES if the data was removed, NO otherwise
 */
-(BOOL)removeElement:(ElementType)data withNode:(GKQuadtreeNode*)node;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKCompositeBehavior.h
//
//  GKCompositeBehavior.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <GameplayKit/GKBehavior.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * A GKBehavior that can also contain a number of sub-behaviors
 * Sub-behaviors and goals are both weighted and produce a force to apply to a GKAGENT
 */
@interface GKCompositeBehavior : GKBehavior

/**
 * Number of sub-behaviors in this behavior
 **/
@property (readonly) NSInteger behaviorCount;

/**
 * Creates a behavior with an array of sub-behaviors
 */
+ (instancetype)behaviorWithBehaviors:(NSArray<GKBehavior *> *)behaviors;

/**
 * Creates a behavior with two associated arrays of sub-behaviors and weights
 */
+ (instancetype)behaviorWithBehaviors:(NSArray<GKBehavior *> *)behaviors andWeights:(NSArray<NSNumber*> *)weights;


/**
 * Adds a new sub-behavior or changes the weight of the existing sub-behavior in this behavior.
 * If the sub-behavior  does not exist in this behavior, it is added.
 * @param weight the weight for this goal
 * @param behavior the sub-behavior who's weight to change
 */
- (void)setWeight:(float)weight forBehavior:(GKBehavior *)behavior;

/**
 * Gets the current weight for a given sub-behavior.
 * @return the weight of the sub-behavior, or 0 if there is no such sub-behavior on this behavior
 */
- (float)weightForBehavior:(GKBehavior *)behavior;

/**
 * Remove the indicated sub-behavior from this behavior.
 * @param behavior the sub-behavior to be removed
 */
- (void)removeBehavior:(GKBehavior *)behavior;

/**
 * Removes all the sub-behavior on the behavior.
 */
- (void)removeAllBehaviors;

/**
 * Supports getting behaviors via a [int] subscript.
 */
- (GKBehavior *)objectAtIndexedSubscript:(NSUInteger)idx;

/**
 * Supports setting a weight via a [behavior] subscript.
 */
- (void)setObject:(NSNumber *)weight forKeyedSubscript:(GKBehavior *)behavior;

/**
 * Supports getting a weight via a [behavior] subscript.
 */
- (NSNumber *)objectForKeyedSubscript:(GKBehavior *)behavior;

@end

NS_ASSUME_NONNULL_END