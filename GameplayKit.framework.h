// ==========  GameplayKit.framework/Headers/GKRandomDistribution.h
//
//  GKRandomDistribution.h
//  GameLogic
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
//  GameLogic
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
// ==========  GameplayKit.framework/Headers/GameplayKit.h
//
//  GameplayKit.h
//  GameLogic
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#pragma once

#import <GameplayKit/GameplayKitBase.h>

#import <GameplayKit/GKAgent.h>
#import <GameplayKit/GKBehavior.h>
#import <GameplayKit/GKComponent.h>
#import <GameplayKit/GKEntity.h>
#import <GameplayKit/GKGameModel.h>
#import <GameplayKit/GKGoal.h>
#import <GameplayKit/GKGraph.h>
#import <GameplayKit/GKGraphNode.h>
#import <GameplayKit/GKMinmaxStrategist.h>
#import <GameplayKit/GKObstacle.h>
#import <GameplayKit/GKPath.h>
#import <GameplayKit/GKRandomDistribution.h>
#import <GameplayKit/GKRuleSystem.h>
#import <GameplayKit/GKState.h>
#import <GameplayKit/GKStateMachine.h>
// ==========  GameplayKit.framework/Headers/GKStateMachine.h
//
//  GKStateMachine.h
//  GameLogic
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

// ==========  GameplayKit.framework/Headers/GKGoal.h
//
//  GKGoal.h
//  GameLogic
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameplayKitBase.h"

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
//  GameLogic
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameplayKitBase.h"

NS_ASSUME_NONNULL_BEGIN

@class GKGoal;

/**
 * A collection of GKGoals and weights that can be applied to a GKAgent
 */
GK_BASE_AVAILABILITY @interface GKBehavior : NSObject<NSFastEnumeration>

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
- (NSNumber *)objectForKeyedSubscript:(GKGoal *)goal;

@end

NS_ASSUME_NONNULL_END// ==========  GameplayKit.framework/Headers/GKAgent.h
//
//  GKAgent.h
//  GameLogic
//
//  Copyright © 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

#import <GameplayKit/GameplayKit.h>
#import "GKComponent.h"
#import "GKObstacle.h"
#import "GKBehavior.h"
#import "GKGoal.h"

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
GK_BASE_AVAILABILITY @interface GKAgent : GKComponent

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
@property (nonatomic, readonly) float speed;

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
 * A 2D specalization of an agent that moves on in a 2-axis logical coordinate system. This coordinate system does not
 * need to match the visual coordinate system of the delegate. One simple case of that is isometric 2D content where the
 * game model is on a flat 2D plane but the visuals are displayed on an angle where one of the logical axes are used for
 * simulated depth as well as some translation in the display plane.
 */
GK_BASE_AVAILABILITY @interface GKAgent2D : GKAgent

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

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKGameModel.h
//
//  GKGameModel.h
//  GameLogic
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Maximum / minimum values for GKGameModel scoreForPlayer. Values must be within these ranges.
 */
#define GKGameModelMaxScore (1 << 24)
#define GKGameModelMinScore (-(1 << 24))

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

@end


NS_ASSUME_NONNULL_END// ==========  GameplayKit.framework/Headers/GKMinmaxStrategist.h
//
//  GKMinmaxStrategist.h
//  GameLogic
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GKGameModel.h>
#import <GameplayKit/GKRandomSource.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The Minmax Strategist is a generic AI that selects a game model update for a given player that maximises 
 * potential gain, while minimising potential loss. It does this by examining all of the updates available 
 * to the player in question, extrapolating the potential moves opposing players may take, projecting out 
 * maxLookAheadDepth number of turns. The selected update will result in the greatest potential gain, balanced 
 * against the potential gain of other players.
 */
GK_BASE_AVAILABILITY @interface GKMinmaxStrategist : NSObject

/**
 * The game model that we wish to select updates for.
 */
@property (nonatomic, retain, nullable) id<GKGameModel> gameModel;

/**
 * The maximum number of future turns that will be processed when searching for a move.
 */
@property (nonatomic, assign) NSInteger maxLookAheadDepth;

/**
 * A random source to use when breaking ties between equally-strong moves when calling bestMoveForPlayer 
 * or when selecting a random move when randomMoveForPlayer is called. If set to nil, bestMoveForPlayer 
 * and randomMoveForPlayer will simply return the first best move available.
 */
@property (nonatomic, retain, nullable) id<GKRandom> randomSource;

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
//  GameLogic
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameplayKit.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * A node in a directed graph. Edges are directed and can have variable costs.
 */
GK_BASE_AVAILABILITY @interface GKGraphNode : NSObject

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
- (instancetype)initWithPoint:(vector_float2)point NS_DESIGNATED_INITIALIZER;

@end


/**
 * GKGraphNode coupled with a position on a 2D grid
 */
GK_BASE_AVAILABILITY @interface GKGridGraphNode : GKGraphNode

@property (nonatomic) vector_int2 gridPosition;

+ (instancetype)nodeWithGridPosition:(vector_int2)gridPosition;
- (instancetype)initWithGridPosition:(vector_int2)gridPosition NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GameplayKitBase.h
//
//  GameplayKitBase.h
//  GameLogic
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>
#import <Availability.h>
#import <TargetConditionals.h>

#ifdef __cplusplus
#define GK_EXPORT extern "C" __attribute__((visibility ("default")))
#else
#define GK_EXPORT extern __attribute__((visibility ("default")))
#endif

#define GK_BASE_AVAILABILITY NS_CLASS_AVAILABLE(10_11, 9_0)

#define GK_AVAILABLE __OSX_AVAILABLE_STARTING

#define GK_FORCE_INLINE __inline__ __attribute__((always_inline))
// ==========  GameplayKit.framework/Headers/GKRandomSource.h
//
//  GKRandomSource.h
//  GameLogic
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameplayKitBase.h"

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
//  GameLogic
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import "GameplayKit.h"

NS_ASSUME_NONNULL_BEGIN

@class GKPolygonObstacle, GKGraphNode, GKGraphNode2D, GKGridGraphNode;

/**
 * Representation of a directed graph of GKGraphNodes
 */
GK_BASE_AVAILABILITY @interface GKGraph : NSObject

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


/**
 * A collection of GKGraphNodes that are governed by a set of extruded GKPolygonObstacles
 */
GK_BASE_AVAILABILITY @interface GKObstacleGraph : GKGraph

/*
 * Array of the extruded obstacles currently represented by this graph
 */
@property (nonatomic, readonly) NSArray<GKPolygonObstacle *> *obstacles;

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
 * Connects the node to this graph by testing edge intersection with existing obstacles.
 * Same behavior as if this node had been present during initWithObstacles.
 * @param node the node to connect
 */
- (void)connectNodeUsingObstacles:(GKGraphNode2D *)node;

/**
 * Same behavior as connectNodeUsingObstacles: except you can optionally ignore certain obstacles from being tested for intersection.
 */
- (void)connectNodeUsingObstacles:(GKGraphNode2D *)node ignoringObstacles:(NSArray<GKPolygonObstacle *> *)obstaclesToIgnore;

/**
 * Same behavior as connectNodeUsingObstacles: except you can optionally ignore the bounding radius of certain obstacles from being tested for intersection
 */
- (void)connectNodeUsingObstacles:(GKGraphNode2D *)node ignoringBufferRadiusOfObstacles:(NSArray<GKPolygonObstacle *> *)obstaclesBufferRadiusToIgnore;

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
-(NSArray<GKGraphNode2D *> *)nodesForObstacle:(GKPolygonObstacle *)obstacle;

/**
 * Marks a connection as "locked", preventing this connection from being destroyed when you add obstacles that would intersect it
 * @param startNode startNode of the connection to lock
 * @param endNode endNode of the connection to lock
 */
- (void)lockConnectionFromNode:(GKGraphNode2D *)startNode toNode:(GKGraphNode2D *)endNode;

/**
 * "Unlocks" a connection, removing its protection from being destroyed when you add obstacles that would intersect it
 * @param startNode startNode of the connection to unlock
 * @param endNode endNode of the connection to unlock
 * @see lockConnection
 */
- (void)unlockConnectionFromNode:(GKGraphNode2D *)startNode toNode:(GKGraphNode2D *)endNode;

/**
 * Query if a given connection is locked
 * @param startNode startNode of the connection to query
 * @param endNode endNode of the connection to query
 * @see lockConnection
 * @see unlockConnection
 * @return YES if the connection was locked with lockConnection, NO if it was never locked or was unlocked via unlockConnection
 */
- (BOOL)isConnectionLockedFromNode:(GKGraphNode2D *)startNode toNode:(GKGraphNode2D *)endNode;

@end



/*
 * A collection of GKGraphNodes that are governed by a 2D Cartesian grid
 */
GK_BASE_AVAILABILITY @interface GKGridGraph : GKGraph

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

/**
 * Creates a bidirectional graph connecting all of the points on a 2D grid
 * @param x starting x value of the grid
 * @param y starting y value of the grid
 * @param width how wide the grid will be; the grid will continue along the positive X axis from the starting x value
 * @param height how high the grid will be; the grid will continue along the positive Y axis from the starting y value
 * @param diagonalsAllowed should diagonal connections between nodes be made?  If not, only cardinal directions will be connected.
 */
- (instancetype)initFromGridStartingAt:(vector_int2)position width:(int)width height:(int)height diagonalsAllowed:(BOOL)diagonalsAllowed;

/**
 * Returns the GKGridGraphNode at the indicated X and Y coordinate
 * Returns nil if it is outside the bounds of minCoordinates and maxCoordinates
 * @param x x coordinate of the grid node to return
 * @param y y coordinate of the grid node to return
 */
- (nullable GKGridGraphNode *)nodeAtGridPosition:(vector_int2)position;

/**
 * Connects the given GKGridGraphNode to this graph by connecting it to it's adjacent nodes on the grid
 * Input node must have coordinates within the rectangle specified by minCoordinates and maxCoordinates
 * @param node the node to be connected
 */
- (void)connectNodeToAdjacentNodes:(GKGridGraphNode *)node;

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKComponent.h
//
//  GKComponent.h
//  GameLogic
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameplayKitBase.h"

NS_ASSUME_NONNULL_BEGIN

@class GKEntity;

/**
 A component is the data and logic for one part of an object in an entity-component system.
 Entities have many components but components are associated with only a single entity.
 
 Components across entities are best arranged in ComponentSystems, which are homogeneous
 collections of components that the game logic updates in a deterministic order.
 
 @see GKComponentSystem
 */
GK_BASE_AVAILABILITY @interface GKComponent : NSObject <NSCopying>

/**
 * The entity that this component belongs to. Defaults to nil until the component is added to an entity.
 */
@property (nullable, nonatomic, readonly, weak) GKEntity *entity;

/**
 * Updates the component with the given delta time since the last update. Each component should
 * perform its time-based logic in this method.
 */
- (void)updateWithDeltaTime:(NSTimeInterval)seconds;

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

@end

NS_ASSUME_NONNULL_END
// ==========  GameplayKit.framework/Headers/GKPath.h
//
//  GKPath.h
//  GameLogic
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import "GameplayKitBase.h"
#import <Foundation/Foundation.h>
#import <simd/simd.h>

@class GKGraphNode2D;

NS_ASSUME_NONNULL_BEGIN

/**
 * Represents a simple polygonal chain in 2D space.
 * Followable by GKAgent's steering functions.
 */
NS_CLASS_AVAILABLE(10_11, 9_0) @interface GKPath : NSObject

/**
 * Radius of the pathway.  Defines a spatial area that the path occupies.
 * This can be though of as the union between rectangles between all points, and circles at each point
 */
@property (nonatomic, assign) float radius;

/**
 * Does this path loop back on itself, creating a cycle?
 */
@property (nonatomic, assign, getter=isCyclical) BOOL cyclical;

/**
 * Number of points in this path
 */
@property (readonly) NSUInteger numPoints;

+ (instancetype)pathWithPoints:(vector_float2 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical;
- (instancetype)initWithPoints:(vector_float2 *)points count:(size_t)count radius:(float)radius cyclical:(BOOL)cyclical NS_DESIGNATED_INITIALIZER;

/**
 * Creates a path from an array of GKGraphNode2D (often a result of pathfinding)
 * Cyclical is set to NO
 * @param graphNodes an array of graph nodes to make a path from
 * @param radius radius of the path to create
 * @see GKGraphNode
 */
+ (instancetype)pathWithGraphNodes:(NSArray<GKGraphNode2D *> *)graphNodes radius:(float)radius;
- (instancetype)initWithGraphNodes:(NSArray<GKGraphNode2D *> *)graphNodes radius:(float)radius;

/**
 * Returns the point at the given index
 */
-(vector_float2)pointAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END

// ==========  GameplayKit.framework/Headers/GKObstacle.h
//
//  GKObstacle.h
//  GameLogic
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <simd/simd.h>

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
GK_BASE_AVAILABILITY @interface GKPolygonObstacle : GKObstacle

/**
 * Number of vertices on this polygon
 */
@property (nonatomic,readonly) NSUInteger vertexCount;

/**
 * Creates a polygon obstacle with an array of points.
 * @param points array of points in counter-clockwise order that are the vertices of a convex polygon
 * @param numPoints the number of points in the array
 */
+ (instancetype)obstacleWithPoints:(vector_float2 *)points count:(size_t)numPoints;
- (instancetype)initWithPoints:(vector_float2 *)points count:(size_t)numPoints NS_DESIGNATED_INITIALIZER;;

/**
 * Returns the vertex at the indicated index
 * @param index index of the vertex to retrieve
 */
- (vector_float2)vertexAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END

// ==========  GameplayKit.framework/Headers/GKEntity.h
//
//  GKEntity.h
//  GameLogic
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKit.h>

NS_ASSUME_NONNULL_BEGIN

@class GKComponent;

/**
 * An entity is the general purpose object in an entity-component system.
 * Entites have many components but components are associated with only a single entity.
 * 
 * Note: GKEntity supports NSCopying, but your custom GKComponent's must also support NSCopying
 *
 * @see GKComponent
 * @see GKComponentSystem
 */
GK_BASE_AVAILABILITY @interface GKEntity : NSObject <NSCopying>

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
- (void)removeComponentForClass:(Class)componentClass;

/**
 * Gets the component of the indicated class.  Returns nil if entity does not have this component
 * @param componentClass the class of the component you want to get
 */
 - (nullable GKComponent *)componentForClass:(Class)componentClass NS_SWIFT_UNAVAILABLE("Exposed in Swift as componentForClass<ComponentType: GKComponent>(componentClass: ComponentType.Type) -> ComponentType?");


@end

NS_ASSUME_NONNULL_END

