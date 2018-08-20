// ==========  HomeKit.framework/Headers/HMEvent.h
//  HMEvent.h
//  HomeKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class is used to represent a generic HomeKit event.
 */
NS_CLASS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMEvent : NSObject

/*!
 * @brief A unique identifier for the event.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCharacteristicDefines.h
// HMCharacteristicDefines.h
// HomeKit
//
// Copyright (c) 2013-2015 Apple Inc. All rights reserved.

/*!
 * @group Characteristic Valid Values
 *
 * @brief These constants define valid values for characteristic types supported by the HomeKit Accessory Profile for HomeKit based accessories.
 */

/*!
 @enum      HMCharacteristicValueDoorState

 @constant  HMCharacteristicValueDoorStateOpen          Door is fully open.
 @constant  HMCharacteristicValueDoorStateClosed        Door is fully closed.
 @constant  HMCharacteristicValueDoorStateOpening       Door is actively opening.
 @constant  HMCharacteristicValueDoorStateClosing       Door is actively closed.
 @constant  HMCharacteristicValueDoorStateStopped       Door is not moving, and is not fully open nor fully closed.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueDoorState) {
    HMCharacteristicValueDoorStateOpen = 0,
    HMCharacteristicValueDoorStateClosed,
    HMCharacteristicValueDoorStateOpening,
    HMCharacteristicValueDoorStateClosing,
    HMCharacteristicValueDoorStateStopped,
} NS_ENUM_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 @enum      HMCharacteristicValueHeatingCooling

 @constant  HMCharacteristicValueHeatingCoolingOff      Heating/cooling is off.
 @constant  HMCharacteristicValueHeatingCoolingHeat     Heating/cooling is heating.
 @constant  HMCharacteristicValueHeatingCoolingCool     Heating/cooling is cooling.
 @constant  HMCharacteristicValueHeatingCoolingAuto     Heating/cooling is auto.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueHeatingCooling) {
    HMCharacteristicValueHeatingCoolingOff = 0,
    HMCharacteristicValueHeatingCoolingHeat,
    HMCharacteristicValueHeatingCoolingCool,
    HMCharacteristicValueHeatingCoolingAuto,
} NS_ENUM_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 @enum      HMCharacteristicValueRotationDirection

 @constant  HMCharacteristicValueRotationDirectionClockwise             Clockwise rotation.
 @constant  HMCharacteristicValueRotationDirectionCounterClockwise      Counter-clockwise rotation.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueRotationDirection) {
    HMCharacteristicValueRotationDirectionClockwise = 0,
    HMCharacteristicValueRotationDirectionCounterClockwise,
} NS_ENUM_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 @enum      HMCharacteristicValueTemperatureUnit

 @constant  HMCharacteristicValueTemperatureUnitCelsius                 Temperature unit in Celsius.
 @constant  HMCharacteristicValueTemperatureUnitFahrenheit              Temperature unit in Fahrenheit.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueTemperatureUnit) {
    HMCharacteristicValueTemperatureUnitCelsius = 0,
    HMCharacteristicValueTemperatureUnitFahrenheit,
} NS_ENUM_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 @enum      HMCharacteristicValueLockMechanismState

 @constant  HMCharacteristicValueLockMechanismStateUnsecured            Lock mechanism is unsecured.
 @constant  HMCharacteristicValueLockMechanismStateSecured              Lock mechanism is secured.
 @constant  HMCharacteristicValueLockMechanismStateJammed               Lock mechanism is jammed.
 @constant  HMCharacteristicValueLockMechanismStateUnknown              Lock mechanism is unknown.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueLockMechanismState) {
    HMCharacteristicValueLockMechanismStateUnsecured = 0,
    HMCharacteristicValueLockMechanismStateSecured,
    HMCharacteristicValueLockMechanismStateJammed,
    HMCharacteristicValueLockMechanismStateUnknown,
} NS_ENUM_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 @enum      HMCharacteristicValueLockMechanismLastKnownAction

 @constant  HMCharacteristicValueLockMechanismLastKnownActionSecuredUsingPhysicalMovementInterior       Last known action was secured using physical movement, interior.
 @constant  HMCharacteristicValueLockMechanismLastKnownActionUnsecuredUsingPhysicalMovementInterior     Last known action was unsecured using physical movement, interior.
 @constant  HMCharacteristicValueLockMechanismLastKnownActionSecuredUsingPhysicalMovementExterior       Last known action was secured using physical movement, exterior.
 @constant  HMCharacteristicValueLockMechanismLastKnownActionUnsecuredUsingPhysicalMovementExterior     Last known action was unsecured using physical movement, exterior.
 @constant  HMCharacteristicValueLockMechanismLastKnownActionSecuredWithKeypad                          Last known action was secured with keypad.
 @constant  HMCharacteristicValueLockMechanismLastKnownActionUnsecuredWithKeypad                        Last known action was unsecured with keypad.
 @constant  HMCharacteristicValueLockMechanismLastKnownActionSecuredRemotely                            Last known action was secured remotely.
 @constant  HMCharacteristicValueLockMechanismLastKnownActionUnsecuredRemotely                          Last known action was unsecured remotely.
 @constant  HMCharacteristicValueLockMechanismLastKnownActionSecuredWithAutomaticSecureTimeout          Last known action was secured automatically after timeout.
 @constant  HMCharacteristicValueLockMechanismLastKnownActionSecuredUsingPhysicalMovement               Last known action was secured using physical movement.
 @constant  HMCharacteristicValueLockMechanismLastKnownActionUnsecuredUsingPhysicalMovement             Last known action was unsecured using physical movement.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueLockMechanismLastKnownAction) {
    HMCharacteristicValueLockMechanismLastKnownActionSecuredUsingPhysicalMovementInterior = 0,
    HMCharacteristicValueLockMechanismLastKnownActionUnsecuredUsingPhysicalMovementInterior,
    HMCharacteristicValueLockMechanismLastKnownActionSecuredUsingPhysicalMovementExterior,
    HMCharacteristicValueLockMechanismLastKnownActionUnsecuredUsingPhysicalMovementExterior,
    HMCharacteristicValueLockMechanismLastKnownActionSecuredWithKeypad,
    HMCharacteristicValueLockMechanismLastKnownActionUnsecuredWithKeypad,
    HMCharacteristicValueLockMechanismLastKnownActionSecuredRemotely,
    HMCharacteristicValueLockMechanismLastKnownActionUnsecuredRemotely,
    HMCharacteristicValueLockMechanismLastKnownActionSecuredWithAutomaticSecureTimeout,
    HMCharacteristicValueLockMechanismLastKnownActionSecuredUsingPhysicalMovement,
    HMCharacteristicValueLockMechanismLastKnownActionUnsecuredUsingPhysicalMovement,
} NS_ENUM_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);


/*!
 @enum      HMCharacteristicValueAirParticulateSize

 @constant  HMCharacteristicValueAirParticulateSize2_5          Air particulate size of 2.5 micrometers.
 @constant  HMCharacteristicValueAirParticulateSize10           Air particulate size of 10 micrometers.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueAirParticulateSize) {
    HMCharacteristicValueAirParticulateSize2_5 = 0,
    HMCharacteristicValueAirParticulateSize10,
} NS_ENUM_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);


/*!
 @enum      HMCharacteristicValueAirQuality

 @constant  HMCharacteristicValueAirQualityUnknown              Air quality is unknown.
 @constant  HMCharacteristicValueAirQualityExcellent            Air quality is excellent.
 @constant  HMCharacteristicValueAirQualityGood                 Air quality is good.
 @constant  HMCharacteristicValueAirQualityFair                 Air quality is fair.
 @constant  HMCharacteristicValueAirQualityInferior             Air quality is inferior.
 @constant  HMCharacteristicValueAirQualityPoor                 Air quality is poor.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueAirQuality) {
    HMCharacteristicValueAirQualityUnknown = 0,
    HMCharacteristicValueAirQualityExcellent,
    HMCharacteristicValueAirQualityGood,
    HMCharacteristicValueAirQualityFair,
    HMCharacteristicValueAirQualityInferior,
    HMCharacteristicValueAirQualityPoor,
} NS_ENUM_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);


/*!
 @enum      HMCharacteristicValuePositionState

 @constant  HMCharacteristicValuePositionStateClosing           Position is moving towards minimum value.
 @constant  HMCharacteristicValuePositionStateOpening           Position is moving towards maximum value.
 @constant  HMCharacteristicValuePositionStateStopped           Position is Stopped.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValuePositionState) {
    HMCharacteristicValuePositionStateClosing = 0,
    HMCharacteristicValuePositionStateOpening,
    HMCharacteristicValuePositionStateStopped,
} NS_ENUM_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);


/*!
 @enum      HMCharacteristicValueCurrentSecuritySystemState

 @constant  HMCharacteristicValueCurrentSecuritySystemStateStayArm       Home is occupied and residents are active.
 @constant  HMCharacteristicValueCurrentSecuritySystemStateAwayArm       Home is unoccupied.
 @constant  HMCharacteristicValueCurrentSecuritySystemStateNightArm      Home is occupied and residents are sleeping.
 @constant  HMCharacteristicValueCurrentSecuritySystemStateDisarmed      SecuritySystem is disarmed.
 @constant  HMCharacteristicValueCurrentSecuritySystemStateTriggered     SecuritySystem is triggered.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueCurrentSecuritySystemState) {
    HMCharacteristicValueCurrentSecuritySystemStateStayArm = 0,
    HMCharacteristicValueCurrentSecuritySystemStateAwayArm,
    HMCharacteristicValueCurrentSecuritySystemStateNightArm,
    HMCharacteristicValueCurrentSecuritySystemStateDisarmed,
    HMCharacteristicValueCurrentSecuritySystemStateTriggered,
} NS_ENUM_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);


/*!
 @enum      HMCharacteristicValueTargetSecuritySystemState

 @constant  HMCharacteristicValueTargetSecuritySystemStateStayArm        Home is occupied and residents are active.
 @constant  HMCharacteristicValueTargetSecuritySystemStateAwayArm        Home is unoccupied.
 @constant  HMCharacteristicValueTargetSecuritySystemStateNightArm       Home is occupied and residents are sleeping.
 @constant  HMCharacteristicValueTargetSecuritySystemStateDisarm         Disarm.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueTargetSecuritySystemState) {
    HMCharacteristicValueTargetSecuritySystemStateStayArm = 0,
    HMCharacteristicValueTargetSecuritySystemStateAwayArm,
    HMCharacteristicValueTargetSecuritySystemStateNightArm,
    HMCharacteristicValueTargetSecuritySystemStateDisarm,
} NS_ENUM_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);
// ==========  HomeKit.framework/Headers/HMLocationEvent.h
//
//  HMLocationEvent.h
//  HomeKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMEvent.h>

NS_ASSUME_NONNULL_BEGIN

@class CLRegion;

/*!
 * @brief This class represents an event that is evaluated based on entry to and/or
 *        exit from a Region
 */
NS_CLASS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMLocationEvent : HMEvent

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Initializes a new location event object
 *
 * @param region - Region with at least one property of notifyOnEntry or notifyOnExit set to TRUE.
 *
 * @return Instance object representing the location event.
 */
- (instancetype)initWithRegion:(CLRegion *)region __WATCHOS_PROHIBITED;

/*!
 * @brief Region on which events are triggered based on the properties notifyOnEntry and notifyOnExit.
 *        This property will be nil when an application is not authorized for location services.
 */
@property(readonly, strong, nonatomic, nullable) CLRegion *region;

/*!
 * @brief Updates the region
 *
 * @param region - New region with at least one property of notifyOnEntry or notifyOnExit set to TRUE.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateRegion:(CLRegion *)region completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMHomeAccessControl.h
// HMHomeAccessControl.h
// HomeKit
//
// Copyright (c) 2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief Represents the access control of a user associated with a home.
 */
NS_CLASS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMHomeAccessControl : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Specifies if the user has administrative privileges for the home.
 */
@property(readonly, getter=isAdministrator, nonatomic) BOOL administrator;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMEventTrigger.h
// HMEventTrigger.h
// HomeKit
//
// Copyright (c) 2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMTrigger.h>

NS_ASSUME_NONNULL_BEGIN

@class HMEvent;
@class HMCharacteristic;

/*!
 * @group Specifies a group of events that are deemed significant events in a day.
 *        These are also the key paths for the event in a NSPredicate.
 */

/*!
 * @brief Event corresponding to sunrise
 */
HM_EXTERN NSString * const HMSignificantEventSunrise NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Event corresponding to sunset
 */
HM_EXTERN NSString * const HMSignificantEventSunset NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Specifies the key path for a characteristic in a NSPredicate
 */
HM_EXTERN NSString * const HMCharacteristicKeyPath NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Specifies the key path for a characteristic value in a NSPredicate
 */
HM_EXTERN NSString * const HMCharacteristicValueKeyPath NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);


/*!
 * @brief Triggers based on events.
 *
 * @discussion This class represents a trigger that is based on events.
 */
NS_CLASS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMEventTrigger : HMTrigger

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Initializes a new event trigger object.
 *
 * @param name Name of the event trigger.
 *
 * @param events Array of events that can trigger the evaluation of the trigger. Note: The trigger will
 *               be evaluated if any one of the events is true.
 *
 * @param predicate The predicate to evaluate before executing any of the actions sets associated to this
 *                  event.
 *
 * @return Instance object representing the event trigger.
 */
- (instancetype)initWithName:(NSString *)name
                      events:(NSArray<HMEvent *> *)events
                   predicate:(nullable NSPredicate *)predicate NS_DESIGNATED_INITIALIZER __WATCHOS_PROHIBITED;

/*!
 * @brief The events associated with the trigger.
 */
@property(readonly, copy, nonatomic) NSArray<HMEvent *> *events;

/*!
 * @brief The predicate to evaluate before executing the action sets associated with the trigger.
 */
@property(readonly, copy, nonatomic, nullable) NSPredicate *predicate;

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred before a significant event.
 *
 * @param significantEvent The significant event to compare against.
 *                         The valid values are: HMSignificantEventSunrise and HMSignificantEventSunset.
 *
 * @param offset An offset from the time of the signficant event. To specify an offset before the significant event, the
 *               properties of the NSDateComponents must be negative value. e.g. To specify 30 mins before sunset, the
 *               'minute' property must be set to -30.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringBeforeSignificantEvent:(NSString *)significantEvent applyingOffset:(nullable NSDateComponents *)offset;

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred before a significant event.
 *
 * @param significantEvent The significant event to compare against.
 *                         The valid values are: HMSignificantEventSunrise and HMSignificantEventSunset.
 *
 * @param offset An offset from the time of the signficant event. To specify an offset after the significant event, the
 *               properties of the NSDateComponents must be positive value. e.g. To specify 30 mins after sunset, the
 *               'minute' property must be set to 30.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringAfterSignificantEvent:(NSString *)significantEvent applyingOffset:(nullable NSDateComponents *)offset;

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred before the time specified.
 *
 * @param dateComponents Date components representing the time to compare against when the event occurs.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringBeforeDateWithComponents:(NSDateComponents *)dateComponents;

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred at the time specified.
 *
 * @param dateComponents Date components representing the time to compare against when the event occurs.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringOnDateWithComponents:(NSDateComponents *)dateComponents;

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred at or after the time specified.
 *
 * @param dateComponents Date components representing the time to compare against when the event occurs.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringAfterDateWithComponents:(NSDateComponents *)dateComponents;

/*!
 * @brief Creates a predicate that will evaluate whether a characteristic value is related to the specified value.
 *
 * @param characteristic The characteristic that is evaluated as part of the predicate.
 *
 * @param operatorType The relation between the characteristic and the target value. 
 *                     This can be either Less Than, Greater Than, Less Than or Equal, Greater Than or Equal, Equal, or Not Equal.
 *                     Anything else will cause an exception to be thrown.
 *
 * @param value The value of the characteristic to compare when evaluating the predicate.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerWithCharacteristic:(HMCharacteristic *)characteristic
                                                       relatedBy:(NSPredicateOperatorType)operatorType
                                                         toValue:(id)value;

/*!
 * @brief Adds a new event to the event trigger.
 *
 * @param event Event to add to the event trigger.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addEvent:(HMEvent *)event completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Removes the specified event from the event trigger.
 *
 * @param event Event to remove from the event trigger.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeEvent:(HMEvent *)event completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief This method replaces the predicate used to evaluate execution of the action sets associated with the trigger.
 *
 * @param predicate The new predicate for the event trigger.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request,
 *                   error will be nil on success. 
 */
- (void)updatePredicate:(nullable NSPredicate *)predicate completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMError.h
// HMError.h
// HomeKit
//
// Copyright (c) 2014-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

HM_EXTERN NSString * const HMErrorDomain NS_AVAILABLE_IOS(8_0);

/*!
 * @brief This enumeration describes the possible error constants that can be
 *        returned from the the HomeKit APIs.
 */
typedef NS_ENUM(NSInteger, HMErrorCode) {
    HMErrorCodeAlreadyExists                           = 1,
    HMErrorCodeNotFound                                = 2,
    HMErrorCodeInvalidParameter                        = 3,
    HMErrorCodeAccessoryNotReachable                   = 4,
    HMErrorCodeReadOnlyCharacteristic                  = 5,
    HMErrorCodeWriteOnlyCharacteristic                 = 6,
    HMErrorCodeNotificationNotSupported                = 7,
    HMErrorCodeOperationTimedOut                       = 8,
    HMErrorCodeAccessoryPoweredOff                     = 9,
    HMErrorCodeAccessDenied                            = 10,
    HMErrorCodeObjectAssociatedToAnotherHome           = 11,
    HMErrorCodeObjectNotAssociatedToAnyHome            = 12,
    HMErrorCodeObjectAlreadyAssociatedToHome           = 13,
    HMErrorCodeAccessoryIsBusy                         = 14,
    HMErrorCodeOperationInProgress                     = 15,
    HMErrorCodeAccessoryOutOfResources                 = 16,
    HMErrorCodeInsufficientPrivileges                  = 17,
    HMErrorCodeAccessoryPairingFailed                  = 18,
    HMErrorCodeInvalidDataFormatSpecified              = 19,
    HMErrorCodeNilParameter                            = 20,
    HMErrorCodeUnconfiguredParameter                   = 21,
    HMErrorCodeInvalidClass                            = 22,
    HMErrorCodeOperationCancelled                      = 23,
    HMErrorCodeRoomForHomeCannotBeInZone               = 24,
    HMErrorCodeNoActionsInActionSet                    = 25,
    HMErrorCodeNoRegisteredActionSets                  = 26,
    HMErrorCodeMissingParameter                        = 27,
    HMErrorCodeFireDateInPast                          = 28,
    HMErrorCodeRoomForHomeCannotBeUpdated              = 29,
    HMErrorCodeActionInAnotherActionSet                = 30,
    HMErrorCodeObjectWithSimilarNameExistsInHome       = 31,
    HMErrorCodeHomeWithSimilarNameExists               = 32,
    HMErrorCodeRenameWithSimilarName                   = 33,
    HMErrorCodeCannotRemoveNonBridgeAccessory          = 34,
    HMErrorCodeNameContainsProhibitedCharacters        = 35,
    HMErrorCodeNameDoesNotStartWithValidCharacters     = 36,
    HMErrorCodeUserIDNotEmailAddress                   = 37,
    HMErrorCodeUserDeclinedAddingUser                  = 38,
    HMErrorCodeUserDeclinedRemovingUser                = 39,
    HMErrorCodeUserDeclinedInvite                      = 40,
    HMErrorCodeUserManagementFailed                    = 41,
    HMErrorCodeRecurrenceTooSmall                      = 42,
    HMErrorCodeInvalidValueType                        = 43,
    HMErrorCodeValueLowerThanMinimum                   = 44,
    HMErrorCodeValueHigherThanMaximum                  = 45,
    HMErrorCodeStringLongerThanMaximum                 = 46,
    HMErrorCodeHomeAccessNotAuthorized                 = 47,
    HMErrorCodeOperationNotSupported                   = 48,
    HMErrorCodeMaximumObjectLimitReached               = 49,
    HMErrorCodeAccessorySentInvalidResponse            = 50,
    HMErrorCodeStringShorterThanMinimum                = 51,
    HMErrorCodeGenericError                            = 52,
    HMErrorCodeSecurityFailure                         = 53,
    HMErrorCodeCommunicationFailure                    = 54,
    HMErrorCodeMessageAuthenticationFailed             = 55,
    HMErrorCodeInvalidMessageSize                      = 56,
    HMErrorCodeAccessoryDiscoveryFailed                = 57,
    HMErrorCodeClientRequestError                      = 58,
    HMErrorCodeAccessoryResponseError                  = 59,
    HMErrorCodeNameDoesNotEndWithValidCharacters       = 60,
    HMErrorCodeAccessoryIsBlocked                      = 61,
    HMErrorCodeInvalidAssociatedServiceType            = 62,
    HMErrorCodeActionSetExecutionFailed                = 63,
    HMErrorCodeActionSetExecutionPartialSuccess        = 64,
    HMErrorCodeActionSetExecutionInProgress            = 65,
    HMErrorCodeAccessoryOutOfCompliance                = 66,
    HMErrorCodeDataResetFailure                        = 67,
    HMErrorCodeNotificationAlreadyEnabled              = 68,
    HMErrorCodeRecurrenceMustBeOnSpecifiedBoundaries   = 69,
    HMErrorCodeDateMustBeOnSpecifiedBoundaries         = 70,
    HMErrorCodeCannotActivateTriggerTooFarInFuture     = 71,
    HMErrorCodeRecurrenceTooLarge                      = 72,
    HMErrorCodeReadWritePartialSuccess                 = 73,
    HMErrorCodeReadWriteFailure                        = 74,
    HMErrorCodeNotSignedIntoiCloud                     = 75,
    HMErrorCodeKeychainSyncNotEnabled                  = 76,
    HMErrorCodeCloudDataSyncInProgress                 = 77,
    HMErrorCodeNetworkUnavailable                      = 78,
    HMErrorCodeAddAccessoryFailed                      = 79,
    HMErrorCodeMissingEntitlement                      = 80,
    HMErrorCodeCannotUnblockNonBridgeAccessory         = 81,
    HMErrorCodeDeviceLocked                            = 82,
    HMErrorCodeCannotRemoveBuiltinActionSet            NS_ENUM_AVAILABLE_IOS(9_0) = 83,
    HMErrorCodeLocationForHomeDisabled                 NS_ENUM_AVAILABLE_IOS(9_0) = 84,
    HMErrorCodeNotAuthorizedForLocationServices        NS_ENUM_AVAILABLE_IOS(9_0) = 85,
} NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCharacteristicEvent.h
// HMCharacteristicEvent.h
// HomeKit
//
// Copyright (c) 2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMEvent.h>

NS_ASSUME_NONNULL_BEGIN

@class HMCharacteristic;

/*!
 * @brief This class represents an event that is evaluated based on the value of a characteristic
 *        set to a particular value.
 */
NS_CLASS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMCharacteristicEvent<TriggerValueType : id<NSCopying>> : HMEvent

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Initializes a new characteristic event object
 *
 * @param characteristic The characteristic bound to the event.
 *
 * @param triggerValue The value of the characteristic that triggers the event. 
 *                     Specifying nil as the trigger value corresponds to any change in the value of the
 *                     characteristic.
 *
 * @return Instance object representing the characteristic event.
 */
- (instancetype)initWithCharacteristic:(HMCharacteristic *)characteristic
                          triggerValue:(nullable TriggerValueType)triggerValue __WATCHOS_PROHIBITED;

/*!
 * @brief The characteristic associated with the event.
 */
@property(readonly, strong, nonatomic) HMCharacteristic *characteristic;

/*!
 * @brief The value of the characteristic that triggers the event.
 *        A value of nil corresponds to any change in the value of the characteristic.
 */
@property(readonly, copy, nonatomic, nullable) TriggerValueType triggerValue;

/*!
 * @brief This method is used to change trigger value for the characteristic.
 *
 * @param triggerValue New trigger value for the characteristic.
 *                     Specifying nil as the trigger value corresponds to any change in the value of the
 *                     characteristic.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateTriggerValue:(nullable TriggerValueType)triggerValue completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMAccessoryCategory.h
//
//  HMAccessoryCategory.h
//  HomeKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMAccessoryCategoryTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class is used to represent an accessory category.
 */
NS_CLASS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMAccessoryCategory : NSObject

/*!
 * @brief A type identifier that represents the category.
 */
@property(readonly, copy, nonatomic) NSString *categoryType;

/*!
 * @brief The localized description of the category.
 */
@property(readonly, copy, nonatomic) NSString *localizedDescription;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMRoom.h
// HMRoom.h
// HomeKit
//
// Copyright (c) 2013-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class HMAccessory;

/*!
 * @brief This class describes a room in the home.
 */
NS_CLASS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMRoom : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Name of the room.
 */
@property(readonly, copy, nonatomic) NSString *name;

/*!
 * @brief Array of HMAccessory objects that correspond to the accessories 
 *        associated with this room.
 */
@property(readonly, copy, nonatomic) NSArray<HMAccessory *> *accessories;

/*!
 * @brief A unique identifier for the room.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier NS_AVAILABLE_IOS(9_0);

/*!
 * @brief This method is used to change the name of the room.
 *
 * @param name New name for the room.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCharacteristicTypes.h
//  HMCharacteristicTypes.h
//  HomeKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This constant specifies that the characteristic supports notifications
 *        using the event connection established by the controller. The
 *        event connection provides unidirectional communication from the
 *        accessory to the controller.
 */
HM_EXTERN NSString * const HMCharacteristicPropertySupportsEventNotification NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief This constant specifies that the characteristic is readable.
 */
HM_EXTERN NSString * const HMCharacteristicPropertyReadable NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief This constant specifies that the characteristic is writable.
 */
HM_EXTERN NSString * const HMCharacteristicPropertyWritable NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);


/*!
 * @group Accessory Service Characteristic Types
 *
 * @brief These constants define the characteristic types supported by the HomeKit Accessory Profile for HomeKit based accessories.
 */

/*!
 * @brief Characteristic type for power state. The value of the characteristic is a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypePowerState NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for hue. The value of the characteristic is a float value in arc degrees.
 */
HM_EXTERN NSString * const HMCharacteristicTypeHue NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for saturation. The value of the characteristic is a float value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSaturation NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for brightness. The value of the characteristic is an int value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeBrightness NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for temperature units. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueTemperatureUnit.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTemperatureUnits NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current temperature. The value of the characteristic is a float value in Celsius.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentTemperature NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target temperature. The value of the characteristic is a float value in Celsius.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetTemperature NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for heating/cooling mode. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueHeatingCooling and indicates the current heating/cooling mode.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentHeatingCooling NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target heating/cooling mode. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueHeatingCooling and indicates the target heating/cooling mode.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetHeatingCooling NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for cooling threshold temperature. The value of the characteristic is a float value in Celsius.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCoolingThreshold NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for heating threshold temperature. The value of the characteristic is a float value in Celsius.
 */
HM_EXTERN NSString * const HMCharacteristicTypeHeatingThreshold NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current relative humidity. The value of the characteristic is a float value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentRelativeHumidity NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target relative humidity. The value of the characteristic is a float value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetRelativeHumidity NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current door state. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueDoorState and indicates the current door state.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentDoorState NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target door state. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueDoorState and indicates the target door state.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetDoorState NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for obstruction detected. The value of the characteristic is a boolean value.
 */
HM_EXTERN NSString * const HMCharacteristicTypeObstructionDetected NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for name. The value of the characteristic is a string.
 */
HM_EXTERN NSString * const HMCharacteristicTypeName NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for manufacturer. The value of the characteristic is a string.
 */
HM_EXTERN NSString * const HMCharacteristicTypeManufacturer NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for model. The value of the characteristic is a string.
 */
HM_EXTERN NSString * const HMCharacteristicTypeModel NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for serial number. The value of the characteristic is a string.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSerialNumber NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for identify. The characteristic is write-only that takes a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeIdentify NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for rotation direction. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueRotationDirection and indicates the fan rotation direction.
 */
HM_EXTERN NSString * const HMCharacteristicTypeRotationDirection NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for rotation speed. The value of the characteristic is a float representing
 *        the percentage of maximum speed.
 */
HM_EXTERN NSString * const HMCharacteristicTypeRotationSpeed NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for outlet in use. The value of the characteristic is a boolean, which is true
 *        if the outlet is in use.
 */
HM_EXTERN NSString * const HMCharacteristicTypeOutletInUse NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for version. The value of the characteristic is a string.
 */
HM_EXTERN NSString * const HMCharacteristicTypeVersion NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for logs. The value of the characteristic is TLV8 data wrapped in an NSData.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLogs NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for audio feedback. The value of the characteristic is a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeAudioFeedback NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for admin only access. The value of the characteristic is a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeAdminOnlyAccess NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for Security System Alarm Type. The value of the characteristic is a uint8.
 *        indicating the type of alarm triggered by a security system service. This characteristic has a value
 *        of 1 when the alarm type is not known and a value of 0 indicates that the alarm conditions are cleared.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSecuritySystemAlarmType NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for motion detected. The value of the characteristic is a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeMotionDetected NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current lock mechanism state. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueLockMechanismState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentLockMechanismState NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target lock mechanism state. The value of the characteristic is either
 *        HMCharacteristicValueLockMechanismStateUnsecured, or HMCharacteristicValueLockMechanismStateSecured,
 *        as defined by HMCharacteristicValueLockMechanismState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetLockMechanismState NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for the last known action for a lock mechanism. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueLockMechanismLastKnownAction.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLockMechanismLastKnownAction NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for the control point for lock management. The characteristic is write-only that takes TLV8 data wrapped in an NSData.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLockManagementControlPoint NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for the auto secure timeout for lock management. The value of the characteristic is an unsigned 
          32-bit integer representing the number of seconds.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLockManagementAutoSecureTimeout NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for density of air-particulate matter. The value of the characteristic is
 *        in units of micrograms/m^2.
 */
HM_EXTERN NSString * const HMCharacteristicTypeAirParticulateDensity NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for size of air-particulate matter. The value of the characteristic is
 *        one of the values defined for HMCharacteristicValueAirParticulateSize.
 */
HM_EXTERN NSString * const HMCharacteristicTypeAirParticulateSize NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for air quality. The value of the characteristic is
 *        one of the values defined for HMCharacteristicValueAirQuality.
 */
HM_EXTERN NSString * const HMCharacteristicTypeAirQuality NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for battery level. The value of the characteristic is an uint8
 *        value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeBatteryLevel NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for carbon dioxide detected. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates carbon dioxide levels are normal.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonDioxideDetected NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for carbon dioxide level.
 *        The value of the characteristic is a float value in units of ppm.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonDioxideLevel NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for carbon dioxide peak level.
 *        The value of the characteristic is a float value in units of ppm.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonDioxidePeakLevel NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for carbon monoxide detected. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates carbon monoxide levels are normal.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonMonoxideDetected NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for carbon monoxide level.
 *        The value of the characteristic is a float value in units of ppm.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonMonoxideLevel NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for carbon monoxide peak level.
 *        The value of the characteristic is a float value in units of ppm.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonMonoxidePeakLevel NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for Charging state. The value of the characteristic is a uint8.
 *        A value of 1 indicates charging is in progress.
 */
HM_EXTERN NSString * const HMCharacteristicTypeChargingState NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for Contact sensor state. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates that contact is detected; a value of 1 indicates no contact is detected.
 */
HM_EXTERN NSString * const HMCharacteristicTypeContactState NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current horizontal tilt angle. The value is a float representing the angle in arc degrees.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentHorizontalTilt NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current light level. The value of the characteristic in units of lux.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentLightLevel NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current position of a door/window. The value of the characteristic is an
 *        uint8 value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentPosition NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current security system state. The value of the characteristic is one of
 *        the values defined for HMCharacteristicValueCurrentSecuritySystemState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentSecuritySystemState NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current vertical tilt angle. The value is a float representing the angle in arc degrees.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentVerticalTilt NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for firmware version. The value of the characteristic is a string value
 *        describing the firmware version of the accessory.
 */
HM_EXTERN NSString * const HMCharacteristicTypeFirmwareVersion NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for hardware version. The value of the characteristic is a string value
 *        describing the hardware version of the accessory.
 */
HM_EXTERN NSString * const HMCharacteristicTypeHardwareVersion NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for Hold Position. The value of the characteristic is a boolean
 *        indicating that the current position should be held/maintained.
 */
HM_EXTERN NSString * const HMCharacteristicTypeHoldPosition NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for programmable switch input event. The value of the characteristic is an int
 *        that can change based on the type of programmable switch. For a binary programmable switch, a value of 0
 *        indicates OFF (and 1 indicates ON). For a slider programmable switch, the value indicates the level.
 */
HM_EXTERN NSString * const HMCharacteristicTypeInputEvent NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for leak detected. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates no leak is detected; a value of 1 indicates that a leak is detected.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLeakDetected NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for Occupancy Detected. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates no occupancy is detected; a value of 1 indicates that occupancy is detected.
 */
HM_EXTERN NSString * const HMCharacteristicTypeOccupancyDetected NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for programmable switch output state. This value is to be used for presentation
 *        purposes. For a binary programmable switch, a value of 1 can be used to present a state of ON.
 */
HM_EXTERN NSString * const HMCharacteristicTypeOutputState NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for Position state. The value of the characteristic is one of the
 *        one of the values defined for HMCharacteristicValuePositionState.
 */
HM_EXTERN NSString * const HMCharacteristicTypePositionState NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for Smoke Detected. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates no leak is detected; a value of 1 indicates that a leak is detected.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSmokeDetected NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for software version. The value of the characteristic is a string value
 *        describing the software version of the accessory.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSoftwareVersion NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type to indicate status of a service is active. The value of the characteristic is a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeStatusActive NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type to indicate status of a service is fault. The value of the characteristic is a uint8 value.
 */
HM_EXTERN NSString * const HMCharacteristicTypeStatusFault NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type to indicate status of a service is jammed. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates that the service is not jammed; a value of 1 indicates that the service is jammed.
 */
HM_EXTERN NSString * const HMCharacteristicTypeStatusJammed NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type to indicate status of a service is low battery. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates battery level is normal; a value of 1 indicates that battery level is low.
 */
HM_EXTERN NSString * const HMCharacteristicTypeStatusLowBattery NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type to indicate status of a service is tampered. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates no tampering has been detected; a value of 1 indicates that a tampering has been detected.
 */
HM_EXTERN NSString * const HMCharacteristicTypeStatusTampered NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target horizontal tilt angle. The value is a float representing the angle in arc degrees.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetHorizontalTilt NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target security system state. The value of the characteristic is one of
 *        the values defined for HMCharacteristicValueTargetSecuritySystemState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetSecuritySystemState NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target position of a door/window. The value of the characteristic is an
 *        uint8 value in percent. For shades/awnings, a value of 0 indicates no shade and a value of 100
 *        indicates most shade. For blinds, a value of 0 indicates most light is allowed in and 100
 *        indicates least light is allowed.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetPosition NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target vertical tilt angle. The value is a float representing the angle in arc degrees.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetVerticalTilt NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMServiceGroup.h
// HMServiceGroup.h
// HomeKit
//
// Copyright (c) 2013-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class HMService;

/*!
 * @abstract Used to describe a collection of HMService objects
 *
 * @discussion This class is used to group a collection of HMService objects.
 *             This allows for association of a set of accessory services into a group.
 *             Eg. A collection of lights can be grouped as the "Desk Lamps" service group.
 */
NS_CLASS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMServiceGroup : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Name of the service group.
 */
@property(readonly, copy, nonatomic) NSString *name;

/*!
 * @brief Array of HMService objects that correspond to the services contained in this group.
 */
@property(readonly, copy, nonatomic) NSArray<HMService *> *services;

/*!
 * @brief A unique identifier for the service group.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier NS_AVAILABLE_IOS(9_0);

/*!
 * @brief This method is used to change the name of the service group.
 *
 * @param name New name for the service group.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Adds an service to this service group. The service and the group must be part of the same
 *        home. A service can be added to multiple service groups, e.g., a light can be added
 *        to "Desk Lamps" as well as "Dimmable Lamps" service groups.
 *
 * @param service Service to add to this group.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addService:(HMService *)service completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Removes an service from this service group.
 *
 * @param service Service to remove from this group.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeService:(HMService *)service completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMAction.h
//  HMAction.h
//  HomeKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class is used to represent a generic action.
 */
NS_CLASS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMAction : NSObject

/*!
 * @brief A unique identifier for the action.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier NS_AVAILABLE_IOS(9_0);

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMZone.h
// HMZone.h
// HomeKit
//
// Copyright (c) 2013-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class HMRoom;

/*!
 * @brief Used to describe a collection of HMRoom objects
 *
 * @discussion This class is used to group a collection of rooms.
 *             This allows for association of a set of rooms into a group.
 *             Eg. "Living Room" and "Kitchen" rooms can be grouped together
 *             in the "Downstairs" zone.
 */
NS_CLASS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMZone : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Name of the zone.
 */
@property(readonly, copy, nonatomic) NSString *name;

/*!
 * @brief Array of HMRoom objects that correspond to the rooms contained in this zone.
 */
@property(readonly, copy, nonatomic) NSArray<HMRoom *> *rooms;

/*!
 * @brief A unique identifier for the zone.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier NS_AVAILABLE_IOS(9_0);

/*!
 * @brief This method is used to change the name of the zone.
 *
 * @param name New name for the zone.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Adds a room to a zone.
 *
 * @discussion Both the room and the zone should be part of the home.  A room can be added to multiple
 *             zones, e.g., a room "Kitchen" can be added to "Downstairs" as well as "Outdoor" zones.
 *
 * @param room Room to add to this zone.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addRoom:(HMRoom *)room completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Removes a room from the zone.
 *
 * @param room Room to remove from this zone.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeRoom:(HMRoom *)room completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMAccessoryCategoryTypes.h
//
//  HMAccessoryCategoryTypes.h
//  HomeKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

/*!
 * @group Accessory Category Types
 *
 * @brief These constants define the accessory category types supported for HomeKit accessories.
 */

/*!
 * @brief Category type for Other.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeOther NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Category type for Security System.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeSecuritySystem NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Category type for Bridge.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeBridge NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Category type for Door.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeDoor NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Category type for Door Lock.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeDoorLock NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Category type for Fan.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeFan NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Category type for Garage Door Opener.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeGarageDoorOpener NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Category type for Lightbulb.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeLightbulb NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Category type for Outlet.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeOutlet NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Category type for Programmable Switch.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeProgrammableSwitch NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Category type for Sensor.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeSensor NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Category type for Switch.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeSwitch NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Category type for Thermostat.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeThermostat NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Category type for Window.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeWindow NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Category type for Window Covering.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeWindowCovering NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);
// ==========  HomeKit.framework/Headers/HMAccessoryBrowser.h
// HMAccessoryBrowser.h
// HomeKit
//
// Copyright (c) 2013-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class HMHome;
@class HMAccessory;

@protocol HMAccessoryBrowserDelegate;

/*! 
 * @brief This class is used to discover new accessories in the home
 *        that have never been paired with and therefore not part of the home.
 */
NS_CLASS_AVAILABLE_IOS(8_0) __WATCHOS_PROHIBITED
@interface HMAccessoryBrowser : NSObject

/*!
 * @brief Delegate that receives updates on the state of the accessories discovered.
 */
@property(weak, nonatomic, nullable) id<HMAccessoryBrowserDelegate> delegate;

/*!
 * @brief This is the array of HMAccessory objects that represents new
 *        accessories that were discovered as part of a search session.
 *        This array is not updated when a search session is not in progress.
 */
@property(readonly, copy, nonatomic) NSArray<HMAccessory *> *discoveredAccessories;

/*!
 * @brief Starts searching for accessories that are not associated to any home.
 *
 * @discussion If any accessories are discovered, updates are sent to the delegate.
 *             This will only scan for any accessories that are already on the
 *             infrastructure IP network or any Bluetooth LE accessories.
 *             The array of discovered accessories will be updated when this method
 *             is called, so applications should clear and reload any stored copies
 *             of that array or previous new accessory objects.
 *
 */
- (void)startSearchingForNewAccessories;

/*!
 * @brief Stops searching for new accessories.
 *
 * @discussion After this method is called, updates will not be sent to the delegate
 *             if new accessories are found or removed. Scanning may continue for system
 *             reasons or if other delegates are still in active searching sessions.
 *             The array of discovered accessories will not be updated until 
 *             startSearchingForNewAccessories is called.
 */
- (void)stopSearchingForNewAccessories;

@end

/*!
 * @brief This delegate receives updates about new accessories in the home.
 */
NS_AVAILABLE_IOS(8_0) __WATCHOS_PROHIBITED
@protocol HMAccessoryBrowserDelegate <NSObject>

@optional

/*!
 * @brief Informs the delegate about new accessories discovered in the home.
 *
 * @param browser Sender of the message.
 *
 * @param accessory New accessory that was discovered.
 */
- (void)accessoryBrowser:(HMAccessoryBrowser *)browser didFindNewAccessory:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate about new accessories removed from the home.
 *
 * @param browser Sender of the message.
 *
 * @param accessory Accessory that was previously discovered but are no longer reachable.
 * 	            This method is also invoked when an accessory is added to a home.
 */
- (void)accessoryBrowser:(HMAccessoryBrowser *)browser didRemoveNewAccessory:(HMAccessory *)accessory;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMService.h
// HMService.h
// HomeKit
//
// Copyright (c) 2013-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMServiceTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class HMAccessory;
@class HMCharacteristic;

/*!
 * @brief Represents a service provided by an accessory.
 *
 * @discussion This class represents a service provided by an accessory in the home.
 *             A service is composed of one or more characteristics that can be 
 *             modified.
 */
NS_CLASS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMService : NSObject

/*!
 * @brief Accessory that provides this service.
 */
@property(readonly, weak, nonatomic) HMAccessory *accessory;

/*!
 * @brief The type of the service, e.g. HMServiceTypeLightbulb.
 */
@property(readonly, copy, nonatomic) NSString *serviceType;

/*!
 * @brief The localized description of the service.
 */
@property(readonly, copy, nonatomic) NSString *localizedDescription NS_AVAILABLE_IOS(9_0);

/*!
 * @brief Name for the service.
 *
 * @discussion Returns the service's name that is associated with HomeKit. The initial value is the value of
 *             the name characteristic of the service, if it has one.
 */
@property(readonly, copy, nonatomic) NSString *name;

/*!
 * @brief For HMServiceTypeOutlet and HMServiceTypeSwitch, this is the type of the associated service.
 *
 * @discussion This could be any of the HomeKit Accessory Profile defined services (except HMServiceTypeOutlet
 *             or HMServiceTypeSwitch) that supports HMCharacteristicTypePowerState characteristic.
 */
@property(readonly, copy, nonatomic, nullable) NSString *associatedServiceType;

/*!
 * @brief Array of HMCharacteristic objects that represents all the characteristics
 *        provided by the service.
 */
@property(readonly, copy, nonatomic) NSArray<HMCharacteristic *> *characteristics;

/*!
 * @brief A unique identifier for the service.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier NS_AVAILABLE_IOS(9_0);

/*!
 * @brief Indicates if this service supports user interaction or not.
 *
 * @discussion Applications should use this property to filter out services that the users
 *             should not directly interact with, e.g. HMServiceTypeAccessoryInformation.
 */
@property(readonly, getter=isUserInteractive, nonatomic) BOOL userInteractive NS_AVAILABLE_IOS(9_0);

/*!
 * @brief This method is used to change the name of the service.
 *
 * @param name New name for the service.
 *
 * @discussion The new name is stored in HomeKit and not on the accessory.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief This method is used to set up the service type of the device connected to a switch or an outlet.
 *
 * @param serviceType Service type of the device connected to a switch/outlet service.
 *
 * @discussion This method is only valid for services of type HMServiceTypeOutlet and HMServiceTypeSwitch.
 *             serviceType can be any of the HomeKit Accessory Profile defined services (except HMServiceTypeOutlet
 *             or HMServiceTypeSwitch) that supports HMCharacteristicTypePowerState characteristic.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateAssociatedServiceType:(nullable NSString *)serviceType completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCharacteristicWriteAction.h
// HMCharacteristicWriteAction.h
// HomeKit
//
// Copyright (c) 2014-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMAction.h>

NS_ASSUME_NONNULL_BEGIN

@class HMCharacteristic;

/*!
 * @brief This class is used to represent an entry in an action set that writes a specific
 *        value to a characteristic.
 */
NS_CLASS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMCharacteristicWriteAction<TargetValueType : id<NSCopying>> : HMAction

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Initializer method that ties the action to a particular characteristic.
 *
 * @param characteristic The characteristic bound to the action.
 *
 * @param targetValue The target value for the characteristic.
 *
 * @return Instance object representing the characteristic write action.
 */
- (instancetype)initWithCharacteristic:(HMCharacteristic *)characteristic
                           targetValue:(TargetValueType)targetValue NS_DESIGNATED_INITIALIZER __WATCHOS_PROHIBITED;

/*!
 * @brief The characteristic associated with the action.
 */
@property(readonly, strong, nonatomic) HMCharacteristic* characteristic;

/*!
 * @brief The target value for the action.
 */
@property(readonly, copy, nonatomic) TargetValueType targetValue;

/*!
 * @brief This method is used to change target value for the characteristic.
 *
 * @param targetValue New target value for the characteristic.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateTargetValue:(TargetValueType)targetValue completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMActionSet.h
// HMActionSet.h
// HomeKit
//
// Copyright (c) 2013-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMAction;
@class HMCharacteristic;

/*!
 * @brief This class represents a collection of action objects that can be executed. 
 *        The order of execution of these actions is undefined.
 */             
NS_CLASS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMActionSet : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief The name of the action set.
 */
@property(readonly, copy, nonatomic) NSString *name;

/*!
 * @brief Set of HMAction objects that represent the individual items of the action set.
 */
@property(readonly, copy, nonatomic) NSSet<HMAction *> *actions;

/*!
 * @brief Specifies whether the action set is currently executing or not.
 */
@property(readonly, getter=isExecuting, nonatomic) BOOL executing;

/*!
 * @brief Specifies the action set type - user-defined or one of the builtin types.
 *        Builtin action sets cannot be removed from the home.
 */
@property(readonly, copy, nonatomic) NSString *actionSetType NS_AVAILABLE_IOS(9_0);

/*!
 * @brief A unique identifier for the action set.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier NS_AVAILABLE_IOS(9_0);

/*!
 * @brief This method is used to change the name of the action set.
 *
 * @param name New name for the action set.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Adds an action to the action set.
 *
 * @param action Action object to add to the action set.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addAction:(HMAction *)action completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Removes an existing action from the action set.
 *
 * @param action Action object to remove from the action set.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeAction:(HMAction *)action completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;


@end

/*!
 * @brief Builtin action set type for WakeUp
 */
HM_EXTERN NSString * const HMActionSetTypeWakeUp NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Type for builtin action set Sleep
 */
HM_EXTERN NSString * const HMActionSetTypeSleep NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Type for builtin action set HomeDeparture
 */
HM_EXTERN NSString * const HMActionSetTypeHomeDeparture NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Type for builtin action set HomeArrival
 */
HM_EXTERN NSString * const HMActionSetTypeHomeArrival NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Type for user-defined action sets
 */
HM_EXTERN NSString * const HMActionSetTypeUserDefined NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);


NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HomeKit.h
// HomeKit.h
// HomeKit
//
// Copyright (c) 2014-2015 Apple Inc. All rights reserved.

#import <HomeKit/HMHomeManager.h>
#import <HomeKit/HMAccessoryBrowser.h>
#import <HomeKit/HMHome.h>
#import <HomeKit/HMRoom.h>
#import <HomeKit/HMZone.h>
#import <HomeKit/HMServiceGroup.h>
#import <HomeKit/HMAccessory.h>
#import <HomeKit/HMService.h>
#import <HomeKit/HMCharacteristic.h>
#import <HomeKit/HMCharacteristicDefines.h>
#import <HomeKit/HMCharacteristicMetadata.h>
#import <HomeKit/HMAction.h>
#import <HomeKit/HMCharacteristicWriteAction.h>
#import <HomeKit/HMActionSet.h>
#import <HomeKit/HMTrigger.h>
#import <HomeKit/HMTimerTrigger.h>
#import <HomeKit/HMUser.h>
#import <HomeKit/HMHomeAccessControl.h>
#import <HomeKit/HMAccessoryCategory.h>
#import <HomeKit/HMEvent.h>
#import <HomeKit/HMCharacteristicEvent.h>
#import <HomeKit/HMLocationEvent.h>
#import <HomeKit/HMEventTrigger.h>
#import <HomeKit/HMError.h>
// ==========  HomeKit.framework/Headers/HMAccessory.h
// HMAccessory.h
// HomeKit
//
// Copyright (c) 2013-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMHome;
@class HMRoom;
@class HMService;
@class HMCharacteristic;
@class HMAccessoryCategory;
@protocol HMAccessoryDelegate;

/*!
 * @abstract Represent an accessory in the home.
 *
 * @discussion This class represents an accessory in the home. There is a one to
 *             one relationship between a physical accessory and an object of this
 *             class. An accessory is composed of one or more services.
 */
NS_CLASS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMAccessory : NSObject

/*!
 * @brief The name of the accessory.
 *
 * @discussion Returns the accessory's name that is associated with HomeKit. The initial value is the name
 *             provided by the accessory information service of the accessory.
 */
@property(readonly, copy, nonatomic) NSString *name;

/*!
 * @brief A unique identifier for the accessory.
 *
 * @discussion Use uniqueIdentifier to obtain the identifier for this object.
 */
@property(readonly, copy, nonatomic) NSUUID *identifier NS_DEPRECATED_IOS(8_0, 9_0) __WATCHOS_PROHIBITED;

/*!
 * @brief A unique identifier for the accessory.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier NS_AVAILABLE_IOS(9_0);

/*!
 * @brief Delegate object that receives updates on the state of the accessory.
 */
@property(weak, nonatomic, nullable) id<HMAccessoryDelegate> delegate;

/*!
 * @brief TRUE if the accessory is currently reachable, FALSE otherwise.
 */
@property(readonly, getter=isReachable, nonatomic) BOOL reachable;

/*!
 * @brief This property indicates whether this accessory is behind a bridge. If it is TRUE,
 *        the accessory cannot be removed from the home directly. Only the bridge that owns
 *        this accessory can be removed and removing the bridge will remove this accessory
 *        from the home.
 */
@property(readonly, getter=isBridged, nonatomic) BOOL bridged;

/*!
 * @brief If this accessory is a bridge, this property is an array of NSUUID objects that,
 *        each of which represents the 'uniqueIdentifier' of the accessory vended by the bridge.
 *
 * @discussion Use uniqueIdentifiersForBridgedAccessories to obtain the identifiers for the
 *             bridged accessories.
 */
@property(readonly, copy, nonatomic, nullable) NSArray<NSUUID *> *identifiersForBridgedAccessories NS_DEPRECATED_IOS(8_0, 9_0) __WATCHOS_PROHIBITED;

/*!
 * @brief If this accessory is a bridge, this property is an array of NSUUID objects that,
 *        each of which represents the 'uniqueIdentifier' of the accessory vended by the bridge.
 *
 * @discussion An accessory can be standalone, a bridge, or hosted behind a bridge.
 *                  - A standalone accessory would have its 'bridged' property set to FALSE and
 *                    its 'uniqueIdentifiersForBridgedAccessories' property set to nil.
 *                  - An accessory that is a bridge would have its 'bridged' property set to FALSE,
 *                    but have a non-empty 'uniqueIdentifiersForBridgedAccessories' property.
 *                  - An accessory behind a bridge would have its 'bridged' property set to TRUE and
 *                    its 'uniqueIdentifiersForBridgedAccessories' property set to nil.
 */
@property(readonly, copy, nonatomic, nullable) NSArray<NSUUID *> *uniqueIdentifiersForBridgedAccessories NS_AVAILABLE_IOS(9_0);

/*!
 * @brief Category information for the accessory. 
 */
@property(readonly, strong, nonatomic) HMAccessoryCategory *category NS_AVAILABLE_IOS(9_0);

/*!
 * @brief Room containing the accessory.
 */
@property(readonly, weak, nonatomic) HMRoom *room;

/*!
 * @brief Array of HMService objects that represent all the services provided by the accessory.
 */
@property(readonly, copy, nonatomic) NSArray<HMService *> *services;

/*!
 * @brief TRUE if the accessory is blocked, FALSE otherwise.
 */

@property(readonly, getter=isBlocked, nonatomic) BOOL blocked;

/*!
 * @brief This method is used to change the name of the accessory.
 *
 * @param name New name for the accessory.
 *
 * @discussion The new name is stored in HomeKit and not on the accessory.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief This method is used to have an accessory identify itself.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)identifyWithCompletionHandler:(void (^)(NSError * __nullable error))completion;

@end


/*!
 * @brief This defines the protocol for a delegate to receive updates about
 *        different aspects of an accessory
 */
NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@protocol HMAccessoryDelegate <NSObject>

@optional

/*!
 * @brief Informs the delegate when the name of the accessory is modified.
 *
 * @param accessory Sender of the message.
 */
- (void)accessoryDidUpdateName:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate when the name of a service is modfied.
 *
 * @param accessory Sender of the message.
 *
 * @param service Service whose name was modified.
 */
- (void)accessory:(HMAccessory *)accessory didUpdateNameForService:(HMService *)service;

/*!
 * @brief Informs the delegate when the associated service type of a service is modified.
 *
 * @param accessory Sender of the message.
 *
 * @param service Service whose associated service type was modified.
 */
- (void)accessory:(HMAccessory *)accessory didUpdateAssociatedServiceTypeForService:(HMService *)service;

/*!
 * @brief Informs the delegate when the services on the accessory have been dynamically updated.
 *        The services discovered are accessible via the 'services' property of the accessory.
 *
 * @param accessory Sender of the message.
 */
- (void)accessoryDidUpdateServices:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate when the reachability of the accessory changes.
 *
 * @param accessory Sender of the message.
 */
- (void)accessoryDidUpdateReachability:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate of a change in value of a characteristic. 
 *
 * @param accessory Sender of this messqage
 *
 * @param service HMService that contains the characteristic whose value was modified.
 *
 * @param characteristic The characteristic whose value was changed.
 */
- (void)accessory:(HMAccessory *)accessory service:(HMService *)service didUpdateValueForCharacteristic:(HMCharacteristic *)characteristic;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCharacteristicMetadata.h
//
//  HMCharacteristicMetadata.h
//  HomeKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class defines the metadata for a characteristic. Metadata provides
 *		  further information about a characteristic’s value, which can be used
 * 		  for presentation purposes.
 */
NS_CLASS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMCharacteristicMetadata : NSObject

/*!
 * @brief The minimum value for the characteristic if it has a format of "int" or "float".
 */
@property(readonly, nonatomic, nullable) NSNumber *minimumValue;

/*!
 * @brief The maximum value for the characteristic if it has a format of "int" or "float".
 */
@property(readonly, nonatomic, nullable) NSNumber *maximumValue;

/*!
 * @brief Step value for the characteristic that indicates the minimum step value allowed if it has a format of "int" or "float".
 */
@property(readonly, nonatomic, nullable) NSNumber *stepValue;

/*!
 * @brief Max length value for the characteristic that indicates the maximum number of UTF-8 characters allowed if it has a format of "string".
 */
@property(readonly, nonatomic, nullable) NSNumber *maxLength;

/*!
 * @brief The format of the value. Refer to HMCharacteristicMetadataFormat constants for supported units.
 */
@property(readonly, copy, nonatomic, nullable) NSString *format;

/*!
 * @brief The units of the value. Refer to HMCharacteristicMetadataUnits constants for supported units.
 */
@property(readonly, copy, nonatomic, nullable) NSString *units;

/*!
 * @brief Manufacturer provided description for the characteristic to present to the user.
 */
@property(readonly, copy, nonatomic, nullable) NSString *manufacturerDescription;

@end

/*!
 * @group HMCharacteristicMetadataFormat constants
 */

/*!
 * @brief Describes that the value format is boolean.
 *
 * @discussion The value is an NSNumber containing the boolean value.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatBool NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Describes that the value format is an integer.
 *
 * @discussion The value is an NSNumber containing a signed 32-bit integer with a range [-2147483648, 2147483647].
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatInt NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Describes that the value format is a float.
 *
 * @discussion The value is an NSNumber containing a 32-bit float.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatFloat NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Describes that the value format is a string.
 *
 * @discussion The value is an NSString.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatString NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Describes that the value format is an array.
 *
 * @discussion The value is an NSArray.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatArray NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Describes that the value format is a dictionary.
 *
 * @discussion The value is an NSDictionary.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatDictionary NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Describes that the value format is an unsigned 8-bit integer.
 *
 * @discussion The value is an NSNumber containing an unsigned 8-bit integer with a range [0, 255].
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatUInt8 NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Describes that the value format is an unsigned 16-bit integer.
 *
 * @discussion The value is an NSNumber containing an unsigned 16-bit integer with a range [0, 65535].
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatUInt16 NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Describes that the value format is an unsigned 32-bit integer.
 *
 * @discussion The value is an NSNumber containing an unsigned 32-bit integer with a range [0, 4294967295].
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatUInt32 NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Describes that the value format is an unsigned 64-bit integer.
 *
 * @discussion The value is an NSNumber containing an unsigned 64-bit integer with a range [0, 18446744073709551615].
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatUInt64 NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Describes that the value format is a data blob.
 *
 * @discussion The value is an NSData containing the bytes of data.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatData NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Describes that the value format is a TLV8.
 *
 * @discussion The value is an NSData containing a set of one or more TLV8's, which are packed type-length-value items with an 8-bit type, 8-bit length, and N-byte value.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatTLV8 NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);


/*!
 * @group HMCharacteristicMetadataUnits constants
 */

/*!
 * @brief Describes that the unit of the characteristic is in Celsius.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsCelsius NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Describes that the unit of the characteristic is in Fahrenheit.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsFahrenheit NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Describes that the unit of the characteristic is a percentage.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsPercentage NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Describes that the unit of the characteristic is an arc degree.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsArcDegree NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Describes that the unit of the characteristic is in seconds.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsSeconds NS_AVAILABLE_IOS(8_3) __WATCHOS_AVAILABLE(__WATCHOS_2_0);


NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMDefines.h
//
// HMDefines.h
// HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#ifndef HM_EXTERN
#ifdef __cplusplus
#define HM_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define HM_EXTERN   extern __attribute__((visibility ("default")))
#endif
#endif
// ==========  HomeKit.framework/Headers/HMUser.h
//
//  HMUser.h
//  HomeKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class HMHomeAccessControl;

/*!
 * @brief This class describes a user in the home.
 */
NS_CLASS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMUser : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Name of the user.
 */
@property(readonly, copy, nonatomic) NSString *name;

/*!
 * @brief A unique identifier for the user.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier NS_AVAILABLE_IOS(9_0);

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMHome.h
// HMHome.h
// HomeKit
//
// Copyright (c) 2013-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMHomeManager;
@class HMAccessory;
@class HMRoom;
@class HMZone;
@class HMService;
@class HMServiceGroup;
@class HMActionSet;
@class HMTrigger;
@class HMUser;
@class HMHomeAccessControl;

@protocol HMHomeDelegate;

/*!
 * @brief Represents a home.
 *
 * @discussion This class represents a home and is the entry point to communicate and
 *             configure different accessories in the home. This is also used to manage
 *             all the rooms, zones, service groups, users, triggers, and action sets in
 *             the home.
 */
NS_CLASS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMHome : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Delegate that receives updates on the state of the home.
 */
@property(weak, nonatomic, nullable) id<HMHomeDelegate> delegate;

/*!
 * @brief The name of the home.
 */
@property(readonly, copy, nonatomic) NSString *name;

/*!
 * @brief Specifies whether this home is the primary home.
 */
@property(readonly, getter=isPrimary, nonatomic) BOOL primary;

/*!
 * @brief A unique identifier for the home.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier NS_AVAILABLE_IOS(9_0);

/*!
 * @brief This method is used to change the name of the home.
 *
 * @param name New name for the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end


@interface HMHome(HMAccessory)

/*!
 * @brief Array of HMAccessory objects that represents all accessories added to the home. 
 */
@property(readonly, copy, nonatomic) NSArray<HMAccessory *> *accessories;

/*!
 * @brief Adds a new accessory to the home.
 *
 * @param accessory Accessory to add to the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addAccessory:(HMAccessory *)accessory completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Removes an accessory from the home.
 *
 * @param accessory Accessory to remove from the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeAccessory:(HMAccessory *)accessory completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Assigns a new room for the accessory.
 *
 * @discussion When an accessory is added to a home, it is automatically assigned the room corresponding to
 *             + [HMHome roomForEntireHome]. This method is used to change the room assigned to an accessory.
 *
 * @param accessory Accessory whose rooms needs to modified
 *
 * @param room New room for the accessory.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)assignAccessory:(HMAccessory *)accessory toRoom:(HMRoom *)room completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Queries all services that match the specified types.
 *
 * @param serviceTypes Array of NSString objects that specifies the service types to match.
 *
 * @return Array of HMService objects that match the specified service types, 
 *         nil if no matching services were found.
 */
- (nullable NSArray<HMService *> *)servicesWithTypes:(NSArray<NSString *> *)serviceTypes;

/*!
 * @brief unblock a blocked accessory.
 *
 * @discussion A misbehaving accessory will automatically be blocked.  After that all requests to
 *              the accessory will fail.  This API must be used to explicitly unblock the accessory
 *
 * @param accessory accessory to be unblocked
 *
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)unblockAccessory:(HMAccessory *)accessory completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end


@interface HMHome(HMUser)

/*!
 * @brief HMUser object representing the current user of the home.
 */
@property(readonly, strong, nonatomic) HMUser *currentUser NS_AVAILABLE_IOS(9_0);

/*!
 * @brief Array of HMUser objects that represent all users associated with the home.
 */
@property(readonly, copy, nonatomic) NSArray<HMUser *> *users NS_DEPRECATED_IOS(8_0, 9_0) __WATCHOS_PROHIBITED;

/*!
 * @brief Presents a view controller to manage users of the home.
 *
 * @discussion This API is available only for users that have administrator access to the home.
 *
 * @param completion Block that is invoked once user management is completed.
 *                   The completion block is fired to allow clients to know when the user has dismissed the view.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success. If the user does not have administrator privileges the error code will be set to
 *                   HMErrorCodeInsufficientPrivileges.
 */
- (void)manageUsersWithCompletionHandler:(void (^)(NSError * __nullable error))completion NS_AVAILABLE_IOS(9_0) __WATCHOS_PROHIBITED;

/*!
 * @brief Adds a user to the home.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The HMUser object provides a reference to the user that was added to the home.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success. The userInfo dictionary will contain the HMUserFailedAccessoriesKey which provides
 *                   more details on the accessories that failed to add the user.
 */
- (void)addUserWithCompletionHandler:(void (^)(HMUser * __nullable user, NSError * __nullable error))completion NS_DEPRECATED_IOS(8_0, 9_0) __WATCHOS_PROHIBITED;

/*!
 * @brief Removes a user from the home.
 *
 * @param user HMUser whose access is being revoked.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success. The userInfo dictionary will contain the HMUserFailedAccessoriesKey which provides
 *                   more details on the accessories that failed to remove the user.
 */
- (void)removeUser:(HMUser *)user completionHandler:(void (^)(NSError * __nullable error))completion NS_DEPRECATED_IOS(8_0, 9_0) __WATCHOS_PROHIBITED;

/*!
 * @brief Retrieve the access level of the user associated with the home.
 */
- (HMHomeAccessControl *)homeAccessControlForUser:(HMUser *)user NS_AVAILABLE_IOS(9_0);

@end


@interface HMHome(HMRoom)

/*!
 * @brief Array of HMRoom objects that represents all rooms in the home.
 */
@property(readonly, copy, nonatomic) NSArray<HMRoom *> *rooms;

/*!
 * @brief Adds a room to the home.
 *
 * @param roomName Name of the room to add to the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 * 	                 The HMRoom is the new room added to the home.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addRoomWithName:(NSString *)roomName completionHandler:(void (^)(HMRoom * __nullable room, NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Removes a room from the home. 
 * @discussion Any references to this room will be removed from all properties
 *             of the home. For example, the room will be removed from the zone.
 *             Any accessories associated contained by this room will be moved to
 *             the room provided by - [HMHome roomForEntireHome].
 *
 * @param room Room to remove from the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeRoom:(HMRoom *)room completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief This method returns a room that represents the entire home. This can be used to assign a room
 *        to a service that is not necessarily located in one particular room.
 *
 * @return HMRoom that represents the home.
 */
- (HMRoom *)roomForEntireHome;

@end


@interface HMHome(HMZone)

/*!
 * @brief Array of HMZone objects that represents all the zones in the home.
 */
@property(readonly, copy, nonatomic) NSArray<HMZone *> *zones;

/*!
 * @brief Adds a zone to the home.
 *
 * @param zoneName Name of the zone to add to the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 * 	                 The HMZone is the new zone added to the home.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addZoneWithName:(NSString *)zoneName completionHandler:(void (^)(HMZone * __nullable zone, NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Removes a zone from the home.
 *
 * @param zone Zone to remove from the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeZone:(HMZone *)zone completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end


@interface HMHome(HMServiceGroup)

/*!
 * @brief Array of HMServiceGroup objects that represents all service groups in the home.
 */
@property(readonly, copy, nonatomic) NSArray<HMServiceGroup *> *serviceGroups;

/*!
 * @brief Adds a service group to the home.
 *
 * @param serviceGroupName Name of the service group to add to the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 * 	                 The HMServiceGroup is the new service group added to the home.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addServiceGroupWithName:(NSString *)serviceGroupName completionHandler:(void (^)(HMServiceGroup * __nullable group, NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Removes a service group from the home.
 *
 * @param group Service group to remove from the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeServiceGroup:(HMServiceGroup *)group completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end


@interface HMHome(HMActionSet)

/*!
 * @brief Array of HMActionSet objects that represents all the action sets in the home.
 */
@property(readonly, copy, nonatomic) NSArray<HMActionSet *> *actionSets;

/*!
 * @brief Adds a new action set to the home.
 *
 * @param actionSetName Name of the action set to add to the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 * 	                 The HMActionSet parameter is the new action set added to the home.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addActionSetWithName:(NSString *)actionSetName completionHandler:(void (^)(HMActionSet * __nullable actionSet, NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Removes an existing action set from the home.
 *
 * @param actionSet Action set to remove from the home. A builtin action set cannot be removed.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeActionSet:(HMActionSet *)actionSet completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Executes all the actions within an action set.
 *
 * @param actionSet Action set to execute.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)executeActionSet:(HMActionSet *)actionSet completionHandler:(void (^)(NSError * __nullable error))completion;

/*!
 * @brief Retrieve a built-in action set for the home.
 *
 * @param type Type of the builtin action set. Supported action set types are HMActionSetTypeWakeUp,
 *             HMActionSetTypeSleep, HMActionSetTypeHomeDeparture and HMActionSetTypeHomeArrival.
 *
 * @return Reference to the built-in action set corresponding to type argument,
 *         nil if no matching action set is found.
 */
- (nullable HMActionSet *)builtinActionSetOfType:(NSString *)actionSetType NS_AVAILABLE_IOS(9_0);

@end


@interface HMHome(HMTrigger)

/*!
 * @brief Array of HMTrigger objects that represents all the triggers in the home.
 */
@property(readonly, copy, nonatomic) NSArray<HMTrigger *> *triggers;

/*!
 * @brief Adds a trigger to the home. Unless the trigger object is added to the home, it cannot be 
 *        activated.
 *
 * @discussion  Triggers are specific to an iOS device and are not synced across multiple devices to
 *              ensure that the action sets are executed only once.
 *
 * @param trigger Trigger to add to the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 * 	                 The HMTrigger parameter is the new trigger added to the home.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addTrigger:(HMTrigger *)trigger completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Removes a trigger from the home. If the trigger is active, they are automatically deactivated.
 *
 * @param trigger Trigger to remove from the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeTrigger:(HMTrigger *)trigger completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end


/*!
 * @brief This delegate receives update on the various accessories, action sets, groups and triggers 
 *        managed in the home.
 */
NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@protocol HMHomeDelegate <NSObject>

@optional

/*!
 * @brief Informs the delegate of a change in the name of a home.
 *
 * @param home Sender of this message.
 */
- (void)homeDidUpdateName:(HMHome *)home;

/*!
 * @brief Informs the delegate of addition of an accessory to the home.
 *
 * @param home Sender of the message.
 *
 * @param accessory Accessory that was added to the home.
 */
- (void)home:(HMHome *)home didAddAccessory:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate of removal of an accessory from the home.
 *
 * @param home Sender of the message.
 *
 * @param accessory Accessory that was removed from the home.
 */
- (void)home:(HMHome *)home didRemoveAccessory:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate that a user was added to the home.
 *
 * @param home Sender of this message.
 *
 * @param user User who was granted access to the home.
 */
- (void)home:(HMHome *)home didAddUser:(HMUser *)user;

/*!
 * @brief Informs the delegate that a user was removed from the home.
 *
 * @param home Sender of this message.
 *
 * @param user User whose access was revoked from the home.
 */
- (void)home:(HMHome *)home didRemoveUser:(HMUser *)user;

/*!
 * @brief Informs the delegate when a new room is assigned to an accessory
 *
 * @param home Sender of the message.
 *
 * @param room New room for the accessory.
 *
 * @param accessory Accessory that was assigned a new room.
 */
- (void)home:(HMHome *)home didUpdateRoom:(HMRoom *)room forAccessory:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate of addition of a room to the home.
 *
 * @param home Sender of the message.
 *
 * @param room Room that was added to the home.
 */
- (void)home:(HMHome *)home didAddRoom:(HMRoom *)room;

/*!
 * @brief Informs the delegate of removal of a room from the home.
 *
 * @param home Sender of the message.
 *
 * @param room Room that was removed from the home.
 */
- (void)home:(HMHome *)home didRemoveRoom:(HMRoom *)room;

/*!
 * @brief Informs the delegate that the name of a room was modified
 *
 * @param home Sender of this message.
 *
 * @param room Room that was modified.
 */
- (void)home:(HMHome *)home didUpdateNameForRoom:(HMRoom *)room;

/*!
 * @brief Informs the delegate of addition of a zone to the home.
 *
 * @param home Sender of the message.
 *
 * @param zone Zone that was added to the home.
 */
- (void)home:(HMHome *)home didAddZone:(HMZone *)zone;

/*!
 * @brief Informs the delegate of removal of a zone from the home.
 *
 * @param home Sender of the message.
 *
 * @param zone Zone that was removed from the home.
 */
- (void)home:(HMHome *)home didRemoveZone:(HMZone *)zone;

/*!
 * @brief Informs the delegate that the name of a zone was modified.
 *
 * @param home Sender of this message.
 *
 * @param zone Zone that was modified.
 */
- (void)home:(HMHome *)home didUpdateNameForZone:(HMZone *)zone;

/*!
 * @brief Informs the delegate that the room was added to a zone.
 *
 * @param home Sender of this message.
 *
 * @param room Room that was added to the zone.
 *
 * @param zone Zone that was modified.
 */
- (void)home:(HMHome *)home didAddRoom:(HMRoom *)room toZone:(HMZone *)zone;

/*!
 * @brief Informs the delegate that the room was removed from a zone.
 *
 * @param home Sender of this message.
 *
 * @param room Room that was removed from the zone.
 *
 * @param zone Zone that was modified.
 */
- (void)home:(HMHome *)home didRemoveRoom:(HMRoom *)room fromZone:(HMZone *)zone;

/*!
 * @brief Informs the delegate that a service group was added to the home.
 *
 * @param home Sender of the message.
 *
 * @param group Service group that was added to the home.
 */
- (void)home:(HMHome *)home didAddServiceGroup:(HMServiceGroup *)group;

/*!
 * @brief Informs the delegate that a service group was removed from the home.
 *
 * @param home Sender of the message.
 *
 * @param group Service group that was removed from the home.
 */
- (void)home:(HMHome *)home didRemoveServiceGroup:(HMServiceGroup *)group;

/*!
 * @brief Informs the delegate that the name of a service group was modified.
 *
 * @param home Sender of this message.
 *
 * @param group The service group that was modfied.
 */
- (void)home:(HMHome *)home didUpdateNameForServiceGroup:(HMServiceGroup *)group;

/*!
 * @brief Informs the delegate that a service was added to a service group.
 *
 * @param home Sender of this message.
 *
 * @param service Service that was added to the service group.
 *
 * @param group Service group that was modified.
 */
- (void)home:(HMHome *)home didAddService:(HMService *)service toServiceGroup:(HMServiceGroup *)group;

/*!
 * @brief Informs the delegate that a service was removed from a service group.
 *
 * @param home Sender of this message.
 *
 * @param service Service that was removed from the service group.
 *
 * @param group Service group that was modified.
 */
- (void)home:(HMHome *)home didRemoveService:(HMService *)service fromServiceGroup:(HMServiceGroup *)group;

/*!
 * @brief Informs the delegate that an action set was added to the home.
 *
 * @param home Sender of this message.
 *
 * @param actionSet Action set that was added to the home.
 */
- (void)home:(HMHome *)home didAddActionSet:(HMActionSet *)actionSet;

/*!
 * @brief Informs the delegate that an action set was removed from the home.
 *
 * @param home Sender of this message.
 *
 * @param actionSet Action set that was removed from the home.
 */
- (void)home:(HMHome *)home didRemoveActionSet:(HMActionSet *)actionSet;

/*!
 * @brief Informs the delegate that the name of an action set was modified.
 *
 * @param home Sender of this message.
 *
 * @param actionSet Action set that was modified.
 */
- (void)home:(HMHome *)home didUpdateNameForActionSet:(HMActionSet *)actionSet;

/*!
 * @brief Informs the delegate that the actions of an action set was modified.
 * This indicates that an action was added/removed or modified (value replaced)
 *
 * @param home Sender of this message.
 *
 * @param actionSet Action set that was modified.
 */
- (void)home:(HMHome *)home didUpdateActionsForActionSet:(HMActionSet *)actionSet;

/*!
 * @brief Informs the delegate of the addition of a trigger to the home.
 *
 * @param home Sender of the message.
 *
 * @param trigger Trigger that was added to the home.
 */
- (void)home:(HMHome *)home didAddTrigger:(HMTrigger *)trigger;

/*!
 * @brief Informs the delegate of removal of a trigger from the home.
 *
 * @param home Sender of the message.
 *
 * @param trigger Trigger that was removed from the home.
 */
- (void)home:(HMHome *)home didRemoveTrigger:(HMTrigger *)trigger;

/*!
 * @brief Informs the delegate that the name of the trigger was modified.
 *
 * @param home Sender of this message.
 *
 * @param trigger Trigger that was modified.
 */
- (void)home:(HMHome *)home didUpdateNameForTrigger:(HMTrigger *)trigger;

/*!
 * @brief Informs the delegate whenever a trigger is updated. For example, this method may be
 *        invoked when a trigger is activated, when a trigger fires, or when the action sets 
 *        associated with a trigger are modified.
 *
 * @param home Sender of this message.
 *
 * @param trigger The trigger that was updated.
 */
- (void)home:(HMHome *)home didUpdateTrigger:(HMTrigger *)trigger;


/*!
 * @brief Informs the delegate that an accessory has been unblocked
 *
 * @param home Sender of this message.
 *
 * @param accessory Accessory that was unblocked
 */
- (void)home:(HMHome *)home didUnblockAccessory:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate that a configured accessory encountered an error. The 
 *        delegate should check the blocked state of the accessory
 *
 * @param home Sender of this message.
 *
 * @param error Error encountered by accessory.
 *
 * @param accessory Accessory that encountered the error
 */

- (void)home:(HMHome *)home didEncounterError:(NSError*)error forAccessory:(HMAccessory *)accessory;

@end

/*!
 * @brief Key that provides more details on the accessories that failed during an 
 *        addUser:completionHandler: or removeUser:completionHandler: call. 
 *
 * @discussion The value associated with this key is an NSArray of NSDictionary objects. Each dictionary
 *             contains the UUID of the accessory that failed to the added/removed and the value
 *             corresponding to the dictionary key is an NSError that provides more details on the
 *             underlying error for that accessory.
 */
HM_EXTERN NSString * const HMUserFailedAccessoriesKey NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCharacteristic.h
// HMCharacteristic.h
// HomeKit
//
// Copyright (c) 2013-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMCharacteristicTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class HMAccessory;
@class HMService;
@class HMCharacteristicMetadata;

/*!
 * @brief Represent a characteristic on a service of an accessory.
 */
NS_CLASS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMCharacteristic : NSObject

/*!
 * @brief The type of the characteristic, e.g. HMCharacteristicTypePowerState.
 */
@property(readonly, copy, nonatomic) NSString *characteristicType;

/*!
 * @brief The localized description of the characteristic.
 */
@property(readonly, copy, nonatomic) NSString *localizedDescription NS_AVAILABLE_IOS(9_0);

/*!
 * @brief Service that contains this characteristic.
 */
@property(weak, readonly, nonatomic) HMService *service;

/*!
 * @brief Array that describes the properties of the characteristic.
 *
 * @discussion This value corresponds to the properties associated with this characteristic.
 *             The contents of the array are one or more HMCharacteristicProperty constants.
 */
@property(readonly, copy, nonatomic) NSArray<NSString *> *properties;

/*!
 * @brief Meta data associated with the characteristic.
 */
@property(readonly, strong, nonatomic, nullable) HMCharacteristicMetadata *metadata;

/*!
 * @brief The value of the characteristic.
 *
 * @discussion The value is a cached value that may have been updated as a result of prior
 *             interaction with the accessory.
 */
@property(readonly, copy, nonatomic, nullable) id value;

/*!
 * @brief Specifies whether the characteristic has been enabled to send notifications.
 *
 * @discussion This property is reset to NO if the reachability of the accessory is NO.
 */
@property(readonly, getter=isNotificationEnabled, nonatomic) BOOL notificationEnabled;

/*!
 * @brief A unique identifier for the characteristic.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier NS_AVAILABLE_IOS(9_0);


/*!
 * @brief Modifies the value of the characteristic.
 *
 * @param value The value to be written.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 *
 * @discussion The value being written is validated against the metadata, format and permissions.
 *             The value written may be bounded by metadata for characteristics with int and 
 *             float format. If validation fails, the error provided to the completion handler
 *             indicates the type of failure.
 */
- (void)writeValue:(nullable id)value completionHandler:(void (^)(NSError * __nullable error))completion;

/*!
 * @brief Reads the value of the characteristic. The updated value can be read from the 'value' property of the characteristic.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)readValueWithCompletionHandler:(void (^)(NSError * __nullable error))completion;

/*!
 * @brief Enables/disables notifications or indications for the value of a specified characteristic.
 *
 * @param enabled A Boolean value indicating whether you wish to receive notifications or 
 *                indications whenever the characteristic’s value changes.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)enableNotification:(BOOL)enable completionHandler:(void (^)(NSError * __nullable error))completion;

/*!
 * @brief Sets/clears authorization data used when writing to the characteristic.
 *
 * @param data New authorization data to use. Specify nil to remove authorization data.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateAuthorizationData:(nullable NSData *)data completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMTimerTrigger.h
// HMTimerTrigger.h
// HomeKit
//
// Copyright (c) 2013-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMTrigger.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief Timer based trigger.
 *
 * @discussion This class represents a trigger that is based on timers.
 */
NS_CLASS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMTimerTrigger : HMTrigger

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Initialize a new HMTimerTrigger object.
 *
 * @param name Name for the trigger.
 *
 * @param fireDate The initial fire date for the timer trigger. The seconds value must be zero.
 *                 HMErrorCodeDateMustBeOnSpecifiedBoundaries will be returned when adding the trigger
 *                 to a home if the fireDate includes a seconds value other than 0.
 *
 * @param timeZone The time zone of the initial fire date. A value of nil indicates default timezone.
 *
 * @param recurrence The recurrence interval to fire the trigger. A value of nil indicates that the
 *                   trigger is non-repeating. The minimum reccurence interval is 5 minutes, maximum
 *                   recurrence interval is 5 weeks and the recurrence interval must be specified in
 *                   multiples of whole minutes.
 *
 * @param recurrenceCalendar The calendar corresponding to a recurring timer trigger. May be nil.
 *
 * @discussion Validity checks are performed when the trigger is added to the home and the NSError in
 *             the completion block for addTrigger: method indicates the reason for the failure:
 *             HMErrorCodeDateMustBeOnSpecifiedBoundaries is returned if the seconds/nanoseconds fields
 *             in recurrence interval or seconds field in fireDate have a value other than 0.
 *             HMErrorCodeRecurrenceTooSmall is returned if recurrence interval is less than 5 minutes.
 *             HMErrorCodeRecurrenceTooLarge is returned if recurrence interval is greater than 5 weeks.
 *             HMErrorCodeFireDateInPast is returned if recurrence is nil and fireDate is in the past.
 */
- (instancetype)initWithName:(NSString *)name
                    fireDate:(NSDate *)fireDate
                    timeZone:(nullable NSTimeZone *)timeZone
                  recurrence:(nullable NSDateComponents *)recurrence
          recurrenceCalendar:(nullable NSCalendar *)recurrenceCalendar NS_DESIGNATED_INITIALIZER __WATCHOS_PROHIBITED;

/*!
 * @brief Specifies when, in an absolute time, the trigger should fire the first time.
 *
 * @discussion Timer triggers are only set at the top of the minute. When the timer trigger fires,
 *             it will typically fire within 1 minute of the scheduled fire date or calculated
 *             recurrence fire date, depending on how the system is managing its resources.
 */
@property(readonly, copy, nonatomic) NSDate *fireDate;

/*!
 * @brief Set the time zone to interpret the fire date in. 
 * 
 * @discussion If this value is nil and the user switches time zones, the time the trigger is
 *             fired will be adjusted to account for the time zone change. If this value is
 *             non-nil, the trigger will fire at the specified time in the specific time zone.
 */
@property(readonly, copy, nonatomic, nullable) NSTimeZone *timeZone;

/*!
 * @brief The date components that specify how a trigger is to be repeated. 
 *
 * @discussion This value must be nil if the trigger should not repeat. The date component
 *             values are relative to the initial fire date of the trigger. If the
 *             calendar value of the recurrence is nil, the current calendar
 *             will be used to calculate the recurrence interval. Recurrence example: if a
 *             trigger should repeat every hour, set the 'hour' property of the
 *             recurrence to 1. The minimum recurrence interval is 5 minutes, maximum recurrence
 *             interval is 5 weeks and the recurrence interval must be specified in multiples of
 *             whole minutes. Examples are 5 minutes, 6 minutes, 1 day, 2 weeks.
 *
 */
@property(readonly, copy, nonatomic, nullable) NSDateComponents *recurrence;

 /*!
  * @brief The calendar corresponding to a recurring timer trigger.
  */
@property(readonly, copy, nonatomic, nullable) NSCalendar *recurrenceCalendar;

/*!
 * @brief This method is used to change the fire date of a timer trigger.
 *
 * @param fireDate New fire date for the trigger. The seconds value must be zero.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request,
 *                   error will be nil on success. HMErrorCodeDateMustBeOnSpecifiedBoundaries will
 *                   be returned if the fireDate includes a seconds value other than 0.
 */
- (void)updateFireDate:(NSDate *)fireDate completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief This method is used to change the time zone of the fire date of a timer trigger.
 *
 * @param timeZone New time zone for the trigger. Passing a nil indicates that the default
 *                 (system) timezone is used.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request,
 *                   error will be nil on success.
 */
- (void)updateTimeZone:(nullable NSTimeZone *)timeZone completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief This method is used to change the recurrence interval for a timer trigger.
 *
 * @param recurrence New recurrence interval for the trigger. Passing a nil indicates that
 *                   the trigger is non-repeating. The minimum recurrence interval is 5 minutes,
 *                   maximum recurrence interval is 5 weeks and the recurrence interval must be specified
 *                   in multiples of whole minutes.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request:
 *                   HMErrorCodeDateMustBeOnSpecifiedBoundaries is returned if the seconds/nanoseconds
 *                   fields have a value other than 0;
 *                   HMErrorCodeRecurrenceTooSmall is returned if the recurrence interval is less than
 *                   5 minutes;
 *                   HMErrorCodeRecurrenceTooLarge is returned if the recurrence interval is
 *                   greater than 5 weeks. *                   error will be nil on success.
 */
- (void)updateRecurrence:(nullable NSDateComponents *)recurrence completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMHomeManager.h
// HMHomeManager.h
// HomeKit
//
// Copyright (c) 2013-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMHome;

@protocol HMHomeManagerDelegate;

/*!
 * @brief Manages collection of one or more homes.
 *
 * @discussion This class is responsible for managing a collection of homes. 
 */
NS_CLASS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMHomeManager : NSObject

/*!
 * @brief Delegate that receives updates on the collection of homes.
 */
@property(weak, nonatomic, nullable) id<HMHomeManagerDelegate> delegate;

/*!
 * @brief The primary home for this collection.
 */
@property(readonly, strong, nonatomic, nullable) HMHome *primaryHome;

/*!
 * @brief Array of HMHome objects that represents the homes associated with the home manager.
 *
 * @discussion When a new home manager is created, this array is inialized as an empty array. It is
 *             not guaranteed to be filled with the list of homes, represented as HMHome objects,
 *             until the homeManagerDidUpdateHomes: delegate method has been invoked.
 */
@property(readonly, copy, nonatomic) NSArray<HMHome *> *homes;

/*!
 * @brief This method is used to change the primary home.
 *
 * @param home New primary home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updatePrimaryHome:(HMHome *)home completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Adds a new home to the collection.
 *
 * @param homeName Name of the  home to create and add to the collection.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 *
 */
- (void)addHomeWithName:(NSString *)homeName completionHandler:(void (^)(HMHome * __nullable home, NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Removes an existing home from the collection.
 *
 * @param home Home object that needs to be removed from the collection.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeHome:(HMHome *)home completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end

/*!
 * @brief This delegate receives updates on homes being managed via the home manager.
 */
NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@protocol HMHomeManagerDelegate <NSObject>

@optional

/*!
 * @brief Informs the delegate when homes configured by the user have been detected by the system.
 *
 * @discussion This delegate method is also invoked to inform an application of significant changes
 *             to the home configuration. Applications should use this as a cue to invalidate their
 *             current references to HomeKit objects and refresh their views with the new list of homes.
 *
 * @param manager Sender of this message.
 */
- (void)homeManagerDidUpdateHomes:(HMHomeManager *)manager;

/*!
 * @brief Informs the delegate when the primary home is modified.
 *
 * @param manager Sender of this message.
 */
- (void)homeManagerDidUpdatePrimaryHome:(HMHomeManager *)manager;

/*!
 * @brief Informs the delegate when a new home is added.
 *
 * @param manager Sender of this message.
 *
 * @param home New home that was added.
 */
- (void)homeManager:(HMHomeManager *)manager didAddHome:(HMHome *)home;

/*!
 * @brief Informs the delegate when an existing home is removed.
 *
 * @param manager Sender of this message.
 *
 * @param home Home that was removed.
 */
- (void)homeManager:(HMHomeManager *)manager didRemoveHome:(HMHome *)home;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMServiceTypes.h
//  HMServiceTypes.h
//  HomeKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

/*!
 * @group Accessory Service Types
 *
 * @brief These constants define the service types supported by the HomeKit Accessory Profile for HomeKit based accessories.
 */

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief Service type for lightbulb.
 */
HM_EXTERN NSString * const HMServiceTypeLightbulb NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for switch.
 */
HM_EXTERN NSString * const HMServiceTypeSwitch NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for thermostat.
 */
HM_EXTERN NSString * const HMServiceTypeThermostat NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for garage door opener.
 */
HM_EXTERN NSString * const HMServiceTypeGarageDoorOpener NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for accessory information.
 */
HM_EXTERN NSString * const HMServiceTypeAccessoryInformation NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for fan.
 */
HM_EXTERN NSString * const HMServiceTypeFan NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for outlet.
 */
HM_EXTERN NSString * const HMServiceTypeOutlet NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for lock mechanism.
 */
HM_EXTERN NSString * const HMServiceTypeLockMechanism NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for lock management.
 */
HM_EXTERN NSString * const HMServiceTypeLockManagement NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for air quality sensor.
 */
HM_EXTERN NSString * const HMServiceTypeAirQualitySensor NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for battery.
 */
HM_EXTERN NSString * const HMServiceTypeBattery NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for carbon dioxide sensor.
 */
HM_EXTERN NSString * const HMServiceTypeCarbonDioxideSensor NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for carbon monoxide sensor.
 */
HM_EXTERN NSString * const HMServiceTypeCarbonMonoxideSensor NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for contact sensor.
 */
HM_EXTERN NSString * const HMServiceTypeContactSensor NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for door.
 */
HM_EXTERN NSString * const HMServiceTypeDoor NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for humidity sensor.
 */
HM_EXTERN NSString * const HMServiceTypeHumiditySensor NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for leak sensor.
 */
HM_EXTERN NSString * const HMServiceTypeLeakSensor NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for light sensor.
 */
HM_EXTERN NSString * const HMServiceTypeLightSensor NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for motion sensor.
 */
HM_EXTERN NSString * const HMServiceTypeMotionSensor NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for occupancy sensor.
 */
HM_EXTERN NSString * const HMServiceTypeOccupancySensor NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for security system.
 */
HM_EXTERN NSString * const HMServiceTypeSecuritySystem NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for stateful programmable switch.
 */
HM_EXTERN NSString * const HMServiceTypeStatefulProgrammableSwitch NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for stateless programmable switch.
 */
HM_EXTERN NSString * const HMServiceTypeStatelessProgrammableSwitch NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for smoke sensor.
 */
HM_EXTERN NSString * const HMServiceTypeSmokeSensor NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for temperature sensor.
 */
HM_EXTERN NSString * const HMServiceTypeTemperatureSensor NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for window.
 */
HM_EXTERN NSString * const HMServiceTypeWindow NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Service type for window covering.
 */
HM_EXTERN NSString * const HMServiceTypeWindowCovering NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMTrigger.h
// HMTrigger.h
// HomeKit
//
// Copyright (c) 2013-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMActionSet;

/*!
 * @brief Represents a trigger event.
 *
 * @discussion This class describes a trigger which is an event that can
 *             be used to execute one or more action sets when the event fires.
 */
NS_CLASS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMTrigger : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Name of the trigger.
 */
@property(readonly, copy, nonatomic) NSString *name;

/*!
 * @brief State of the trigger.
 *
 * @discussion TRUE if the trigger is enable, FALSE otherwise.
 */
@property(readonly, getter=isEnabled, nonatomic) BOOL enabled;

/*!
 * @abstract Array of HMActionSet objects that represent all the action sets associated
 *           with this trigger.
 */
@property(readonly, copy, nonatomic) NSArray<HMActionSet *> *actionSets;

/*!
 * @brief The date that this trigger was most recently fired.
 */
@property(readonly, copy, nonatomic, nullable) NSDate *lastFireDate;

/*!
 * @brief A unique identifier for the trigger.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier NS_AVAILABLE_IOS(9_0);

/*!
 * @brief This method is used to change the name of the trigger.
 *
 * @param name New name for the trigger.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Registers an action set to be executed when the trigger is fired.
 *
 * @param actionSet HMActionSet to execute when the trigger fires. The order of execution of the
 *                  action set is not guaranteed.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request.
 */
- (void)addActionSet:(HMActionSet *)actionSet completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief De-registers an action set from the trigger.
 *
 * @param actionSet The HMActionSet to disassociate from the trigger. 
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request.
 */
- (void)removeActionSet:(HMActionSet *)actionSet completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Enables or disables the trigger. 
 * @discussion In order for the trigger to be enabled the following criteria must be met:
 *             1. The trigger must be added to a home.
 *             2. The trigger must have at least one action set associated with it.
 *             3. Each action set added to the trigger must have at least one action.
 *             4. For HMTimerTrigger: The next fire date of the timer trigger must be less
 *                than 5 weeks in the future. The fire date of a one-shot timer trigger
 *                must be in the future.
 *
 * @param enable Setting this to TRUE will enable the trigger, FALSE will disable it.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request.
 */
- (void)enable:(BOOL)enable completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
