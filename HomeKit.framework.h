// ==========  HomeKit.framework/Headers/HMEvent.h
//
//  HMEvent.h
//  HomeKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

@class HMHome;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class is used to represent a generic HomeKit event.
 */
API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
@interface HMEvent : NSObject

/*!
 * @brief A unique identifier for the event.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier;

/*!
 * @brief Specifies whether the HMEvent can be added to HMEventTrigger on the given home.
 */
+ (BOOL)isSupportedForHome:(HMHome *)home API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMPresenceEventDefines.h
//
//  HMPresenceEventDefines.h
//  HomeKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

/*!
 * @abstract This enumeration describes the different types of presence events.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos)
typedef NS_ENUM(NSUInteger, HMPresenceEventType)
{
    /*!
     * This corresponds to trigger an event for every user entering a home.
     * This cannot be added as predicate.
     */
    HMPresenceEventTypeEveryEntry = 1,
    
    /*!
     * This corresponds to trigger an event for every user exiting a home.
     * This cannot be added as predicate.
     */
    HMPresenceEventTypeEveryExit = 2,
    
    /*!
     * This corresponds to trigger an event for the first user entering a home.
     */
    HMPresenceEventTypeFirstEntry = 3,
    
    /*!
     * This corresponds to trigger an event for the last user exiting a home.
     */
    HMPresenceEventTypeLastExit = 4,
    
    /*!
     * Convenience value for First Entry to use in predicate of HMEventTrigger.
     */
    HMPresenceEventTypeAtHome = HMPresenceEventTypeFirstEntry,
    
    /*!
     * Convenience value for Last Exit to use in predicate of HMEventTrigger.
     */
    HMPresenceEventTypeNotAtHome = HMPresenceEventTypeLastExit,
};

/*!
 * @abstract This enumeration describes the different types of user sets in presence events.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos)
typedef NS_ENUM(NSUInteger, HMPresenceEventUserType)
{
    /*!
     * Only current user's presence is used.
     */
    HMPresenceEventUserTypeCurrentUser = 1,
    
    /*!
     * Presence of all home users is used.
     */
    HMPresenceEventUserTypeHomeUsers = 2,
    
    /*!
     * Presence of custom set of home users is used.
     */
    HMPresenceEventUserTypeCustomUsers = 3,
};
// ==========  HomeKit.framework/Headers/HMCameraStream.h
//
//  HMCameraStream.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMCameraSource.h>
#import <HomeKit/HMCameraDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract Represents a camera stream.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos)
@interface HMCameraStream : HMCameraSource

/*!
 * @brief Represents the audio setting for the current stream.
 */
@property (assign, nonatomic, readonly) HMCameraAudioStreamSetting audioStreamSetting API_UNAVAILABLE(tvos);

/*!
 * @brief Sets the audio stream setting.
 *
 * @param audioStreamSetting New audio stream setting.
 *
 */
- (void)setAudioStreamSetting:(HMCameraAudioStreamSetting)audioStreamSetting  API_DEPRECATED_WITH_REPLACEMENT("updateAudioStreamSetting:completionHandler:", ios(10.0, 10.0), watchos(3.0, 3.0)) API_UNAVAILABLE(tvos);

/*!
 * @brief Updates the settings of the audio stream.
 *
 * @param audioStreamSetting New audio stream setting.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateAudioStreamSetting:(HMCameraAudioStreamSetting)audioStreamSetting completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCharacteristicDefines.h
//
//  HMCharacteristicDefines.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <HomeKit/HMDefines.h>

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
} API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

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
} API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueRotationDirection

 @constant  HMCharacteristicValueRotationDirectionClockwise             Clockwise rotation.
 @constant  HMCharacteristicValueRotationDirectionCounterClockwise      Counter-clockwise rotation.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueRotationDirection) {
    HMCharacteristicValueRotationDirectionClockwise = 0,
    HMCharacteristicValueRotationDirectionCounterClockwise,
} API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueTemperatureUnit

 @constant  HMCharacteristicValueTemperatureUnitCelsius                 Temperature unit in Celsius.
 @constant  HMCharacteristicValueTemperatureUnitFahrenheit              Temperature unit in Fahrenheit.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueTemperatureUnit) {
    HMCharacteristicValueTemperatureUnitCelsius = 0,
    HMCharacteristicValueTemperatureUnitFahrenheit,
} API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

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
} API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

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
} API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);


/*!
 @enum      HMCharacteristicValueAirParticulateSize

 @constant  HMCharacteristicValueAirParticulateSize2_5          Air particulate size of 2.5 micrometers.
 @constant  HMCharacteristicValueAirParticulateSize10           Air particulate size of 10 micrometers.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueAirParticulateSize) {
    HMCharacteristicValueAirParticulateSize2_5 = 0,
    HMCharacteristicValueAirParticulateSize10,
} API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);


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
} API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);


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
} API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);


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
} API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);


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
} API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueBatteryStatus

 @constant  HMCharacteristicValueBatteryStatusNormal        Battery status is normal.
 @constant  HMCharacteristicValueBatteryStatusLow           Battery status is low.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueBatteryStatus) {
    HMCharacteristicValueBatteryStatusNormal = 0,
    HMCharacteristicValueBatteryStatusLow,
} API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueJammedStatus

 @constant  HMCharacteristicValueJammedStatusNone               Not Jammed.
 @constant  HMCharacteristicValueJammedStatusJammed             Jammed.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueJammedStatus) {
    HMCharacteristicValueJammedStatusNone = 0,
    HMCharacteristicValueJammedStatusJammed,
} API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueTamperStatus

 @constant  HMCharacteristicValueTamperStatusNone               Accessory is not tampered with.
 @constant  HMCharacteristicValueTamperStatusTampered           Accessory is tampered with.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueTamperedStatus) {
    HMCharacteristicValueTamperedStatusNone = 0,
    HMCharacteristicValueTamperedStatusTampered,
} API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueLeakDetectionStatus

 @constant  HMCharacteristicValueLeakDetectionStatusNone        Leak is not detected.
 @constant  HMCharacteristicValueLeakDetectionStatusDetected    Leak is detected.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueLeakStatus) {
    HMCharacteristicValueLeakStatusNone = 0,
    HMCharacteristicValueLeakStatusDetected,
} API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueSmokeDetectionStatus

 @constant  HMCharacteristicValueSmokeDetectionStatusNone       Smoke is not detected.
 @constant  HMCharacteristicValueSmokeDetectionStatusDetected   Smoke is detected.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueSmokeDetectionStatus) {
    HMCharacteristicValueSmokeDetectionStatusNone = 0,
    HMCharacteristicValueSmokeDetectionStatusDetected,
} API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueChargingState

 @constant  HMCharacteristicValueChargingStateNone              Charging is not in progress.
 @constant  HMCharacteristicValueChargingStateInProgress        Charging is in progress.
 @constant  HMCharacteristicValueChargingStateNotChargeable     Charging is not supported.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueChargingState) {
    HMCharacteristicValueChargingStateNone = 0,
    HMCharacteristicValueChargingStateInProgress,
    HMCharacteristicValueChargingStateNotChargeable  API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)),  
} API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);


/*!
 @enum      HMCharacteristicValueContactState

 @constant  HMCharacteristicValueContactStateDetected           Contact is detected.
 @constant  HMCharacteristicValueContactStateNone               Contact is not detected.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueContactState) {
    HMCharacteristicValueContactStateDetected = 0,
    HMCharacteristicValueContactStateNone,
} API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueStatusFault
 
 @constant  HMCharacteristicValueStatusFaultNoFault               No Fault.
 @constant  HMCharacteristicValueStatusFaultGeneralFault          General Fault.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueStatusFault) {
    HMCharacteristicValueStatusFaultNoFault = 0,
    HMCharacteristicValueStatusFaultGeneralFault,
} API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueCarbonMonoxideDetectionStatus

 @constant  HMCharacteristicValueCarbonMonoxideDetectionStatusNotDetected       Carbon monoxide is not detected.
 @constant  HMCharacteristicValueCarbonMonoxideDetectionStatusDetected          Carbon monoxide is detected.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueCarbonMonoxideDetectionStatus) {
    HMCharacteristicValueCarbonMonoxideDetectionStatusNotDetected = 0,
    HMCharacteristicValueCarbonMonoxideDetectionStatusDetected,
} API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueCarbonDioxideDetectionStatus

 @constant  HMCharacteristicValueCarbonDioxideDetectionStatusNotDetected    Carbon dioxide is not detected.
 @constant  HMCharacteristicValueCarbonDioxideDetectionStatusDetected       Carbon dioxide is detected.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueCarbonDioxideDetectionStatus) {
    HMCharacteristicValueCarbonDioxideDetectionStatusNotDetected = 0,
    HMCharacteristicValueCarbonDioxideDetectionStatusDetected,
} API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueOccupancyStatus

 @constant  HMCharacteristicValueOccupancyStatusNotOccupied     Occupancy is not detected.
 @constant  HMCharacteristicValueOccupancyStatusOccupied        Occupancy is detected.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueOccupancyStatus) {
    HMCharacteristicValueOccupancyStatusNotOccupied = 0,
    HMCharacteristicValueOccupancyStatusOccupied,
} API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueSecuritySystemAlarmType

 @constant  HMCharacteristicValueSecuritySystemAlarmTypeNoAlarm     No alarm.
 @constant  HMCharacteristicValueSecuritySystemAlarmTypeUnknown     Unknown alarm type.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueSecuritySystemAlarmType) {
    HMCharacteristicValueSecuritySystemAlarmTypeNoAlarm = 0,
    HMCharacteristicValueSecuritySystemAlarmTypeUnknown,
} API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);


/*!
 @enum      HMCharacteristicValueLockPhysicalControlsState

 @constant  HMCharacteristicValueLockPhysicalControlsStateNotLocked     Physical controls not locked.
 @constant  HMCharacteristicValueLockPhysicalControlsStateLocked        Physical controls locked.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueLockPhysicalControlsState) {
    HMCharacteristicValueLockPhysicalControlsStateNotLocked = 0,
    HMCharacteristicValueLockPhysicalControlsStateLocked,
} API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueCurrentAirPurifierState

 @constant  HMCharacteristicValueCurrentAirPurifierStateInactive    Inactive.
 @constant  HMCharacteristicValueCurrentAirPurifierStateIdle        Idle.
 @constant  HMCharacteristicValueCurrentAirPurifierStateActive      Active.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueCurrentAirPurifierState) {
    HMCharacteristicValueCurrentAirPurifierStateInactive = 0,
    HMCharacteristicValueCurrentAirPurifierStateIdle,
    HMCharacteristicValueCurrentAirPurifierStateActive,
} API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueTargetAirPurifierState

 @constant  HMCharacteristicValueTargetAirPurifierStateManual       Air Purifier is in manual mode.
 @constant  HMCharacteristicValueTargetAirPurifierStateAutomatic    Air Purifier is in automatic mode.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueTargetAirPurifierState) {
    HMCharacteristicValueTargetAirPurifierStateManual = 0,
    HMCharacteristicValueTargetAirPurifierStateAutomatic,
} API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueCurrentSlatState

 @constant  HMCharacteristicValueCurrentSlatStateStationary         Slats are stationary.
 @constant  HMCharacteristicValueCurrentSlatStateJammed             Slats are jammed.
 @constant  HMCharacteristicValueCurrentSlatStateOscillating        Slats are oscillating.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueCurrentSlatState) {
    HMCharacteristicValueCurrentSlatStateStationary = 0,
    HMCharacteristicValueCurrentSlatStateJammed,
    HMCharacteristicValueCurrentSlatStateOscillating,
} API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueSlatType

 @constant  HMCharacteristicValueSlatTypeHorizontal          Slat type is horizontal.
 @constant  HMCharacteristicValueSlatTypeVertical            Slat type is vertical.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueSlatType) {
    HMCharacteristicValueSlatTypeHorizontal = 0,
    HMCharacteristicValueSlatTypeVertical,
} API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueFilterChange

 @constant  HMCharacteristicValueFilterChangeNotNeeded      Filter does not need to be changed.
 @constant  HMCharacteristicValueFilterChangeNeeded         Filter needs to be changed.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueFilterChange) {
    HMCharacteristicValueFilterChangeNotNeeded = 0,
    HMCharacteristicValueFilterChangeNeeded,
} API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueCurrentFanState

 @constant  HMCharacteristicValueCurrentFanStateInactive            Inactive.
 @constant  HMCharacteristicValueCurrentFanStateIdle                Idle.
 @constant  HMCharacteristicValueCurrentFanStateActive              Active.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueCurrentFanState) {
    HMCharacteristicValueCurrentFanStateInactive = 0,
    HMCharacteristicValueCurrentFanStateIdle,
    HMCharacteristicValueCurrentFanStateActive,
} API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueTargetFanState

 @constant  HMCharacteristicValueTargetFanStateManual       Fan is in manual mode.
 @constant  HMCharacteristicValueTargetFanStateAutomatic    Fan is in automatic mode.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueTargetFanState) {
    HMCharacteristicValueTargetFanStateManual = 0,
    HMCharacteristicValueTargetFanStateAutomatic,
} API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueCurrentHeaterCoolerState

 @constant  HMCharacteristicValueCurrentHeaterCoolerStateInactive   Inactive.
 @constant  HMCharacteristicValueCurrentHeaterCoolerStateIdle       Idle.
 @constant  HMCharacteristicValueCurrentHeaterCoolerStateHeating    Heating.
 @constant  HMCharacteristicValueCurrentHeaterCoolerStateCooling    Cooling.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueCurrentHeaterCoolerState) {
    HMCharacteristicValueCurrentHeaterCoolerStateInactive = 0,
    HMCharacteristicValueCurrentHeaterCoolerStateIdle,
    HMCharacteristicValueCurrentHeaterCoolerStateHeating,
    HMCharacteristicValueCurrentHeaterCoolerStateCooling,
} API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueTargetHeaterCoolerState

 @constant  HMCharacteristicValueTargetHeaterCoolerStateAutomatic       Automatic mode.
 @constant  HMCharacteristicValueTargetHeaterCoolerStateHeat            Heat mode.
 @constant  HMCharacteristicValueTargetHeaterCoolerStateCool            Cool mode.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueTargetHeaterCoolerState) {
    HMCharacteristicValueTargetHeaterCoolerStateAutomatic = 0,
    HMCharacteristicValueTargetHeaterCoolerStateHeat,
    HMCharacteristicValueTargetHeaterCoolerStateCool,
} API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueCurrentHumidifierDehumidifierState

 @constant  HMCharacteristicValueCurrentHumidifierDehumidifierStateInactive         Inactive.
 @constant  HMCharacteristicValueCurrentHumidifierDehumidifierStateIdle             Idle.
 @constant  HMCharacteristicValueCurrentHumidifierDehumidifierStateHumidifying      Humidifying.
 @constant  HMCharacteristicValueCurrentHumidifierDehumidifierStateDehumidifying    Dehumidifying.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueCurrentHumidifierDehumidifierState) {
    HMCharacteristicValueCurrentHumidifierDehumidifierStateInactive = 0,
    HMCharacteristicValueCurrentHumidifierDehumidifierStateIdle,
    HMCharacteristicValueCurrentHumidifierDehumidifierStateHumidifying,
    HMCharacteristicValueCurrentHumidifierDehumidifierStateDehumidifying,
} API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueTargetHumidifierDehumidifierState

 @constant  HMCharacteristicValueTargetHumidifierDehumidifierStateAutomatic             Automatic mode.
 @constant  HMCharacteristicValueTargetHumidifierDehumidifierStateHumidify              Humidify mode.
 @constant  HMCharacteristicValueTargetHumidifierDehumidifierStateDehumidify            Dehumidify mode.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueTargetHumidifierDehumidifierState) {
    HMCharacteristicValueTargetHumidifierDehumidifierStateAutomatic = 0,
    HMCharacteristicValueTargetHumidifierDehumidifierStateHumidify,
    HMCharacteristicValueTargetHumidifierDehumidifierStateDehumidify,
} API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueSwingMode

 @constant  HMCharacteristicValueSwingModeDisabled                  Swing mode is disabled.
 @constant  HMCharacteristicValueSwingModeEnabled                   Swing mode is enabled.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueSwingMode) {
    HMCharacteristicValueSwingModeDisabled = 0,
    HMCharacteristicValueSwingModeEnabled,
} API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueActivationState

 @constant  HMCharacteristicValueActivationStateInactive            Service is inactive.
 @constant  HMCharacteristicValueActivationStateActive              Service is active.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueActivationState) {
    HMCharacteristicValueActivationStateInactive = 0,
    HMCharacteristicValueActivationStateActive,
} API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueInputEvent

 @constant  HMCharacteristicValueInputEventSinglePress              Single tap or press.
 @constant  HMCharacteristicValueInputEventDoublePress              Double tap or press.
 @constant  HMCharacteristicValueInputEventLongPress                Long press.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueInputEvent) {
    HMCharacteristicValueInputEventSinglePress = 0,
    HMCharacteristicValueInputEventDoublePress,
    HMCharacteristicValueInputEventLongPress,
} API_AVAILABLE(ios(10.3), watchos(3.2), tvos(10.2)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueLabelNamespace

 @constant  HMCharacteristicValueLabelNamespaceDot                      Service labels are dots.
 @constant  HMCharacteristicValueLabelNamespaceNumeral                  Service labels are Arabic numerals.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueLabelNamespace) {
    HMCharacteristicValueLabelNamespaceDot = 0,
    HMCharacteristicValueLabelNamespaceNumeral,
} API_AVAILABLE(ios(10.3), watchos(3.2), tvos(10.2)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueProgramMode
 
 @constant  HMCharacteristicValueProgramModeNotScheduled                No programs scheduled.
 @constant  HMCharacteristicValueProgramModeScheduled                   Program scheduled.
 @constant  HMCharacteristicValueProgramModeScheduleOverriddenToManual  Schedule currently overridden to manual mode.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueProgramMode) {
    HMCharacteristicValueProgramModeNotScheduled = 0,
    HMCharacteristicValueProgramModeScheduled,
    HMCharacteristicValueProgramModeScheduleOverriddenToManual,
} API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueUsageState
 
 @constant  HMCharacteristicValueUsageStateNotInUse        Not in use.
 @constant  HMCharacteristicValueUsageStateInUse           Currently in use.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueUsageState) {
    HMCharacteristicValueUsageStateNotInUse = 0,
    HMCharacteristicValueUsageStateInUse,
} API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueValveType
 
 @constant  HMCharacteristicValueValveTypeGenericValve    Generic Valve.
 @constant  HMCharacteristicValueValveTypeIrrigation      Irrigation.
 @constant  HMCharacteristicValueValveTypeShowerHead      Shower Head.
 @constant  HMCharacteristicValueValveTypeWaterFaucet     Water Faucet.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueValveType) {
    HMCharacteristicValueValveTypeGenericValve = 0,
    HMCharacteristicValueValveTypeIrrigation,
    HMCharacteristicValueValveTypeShowerHead,
    HMCharacteristicValueValveTypeWaterFaucet,
} API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) API_UNAVAILABLE(macos);

/*!
 @enum      HMCharacteristicValueConfigurationState
 
 @constant  HMCharacteristicValueConfigurationStateNotConfigured   Not Configured.
 @constant  HMCharacteristicValueConfigurationStateConfigured      Configured.
 */
typedef NS_ENUM(NSInteger, HMCharacteristicValueConfigurationState) {
    HMCharacteristicValueConfigurationStateNotConfigured = 0,
    HMCharacteristicValueConfigurationStateConfigured,
} API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) API_UNAVAILABLE(macos);
// ==========  HomeKit.framework/Headers/HMAccessory+Camera.h
//
//  HMAccessory+Camera.h
//  HomeKit
//
//  Copyright © 2015-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMAccessory.h>

@class HMCameraProfile;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract Category implementing methods related to camera profile.
 */
@interface HMAccessory(Camera)

/*!
 * @brief Returns array of camera profiles implemented by the accessory.
 *
 * @discussion An accessory can contain one or more cameras. Each camera is represented as a 
 *             an HMCameraProfile object. If the accessory does not contain a camera, this property
 *             will be nil.
 */
@property(readonly, copy, nonatomic, nullable) NSArray<HMCameraProfile *> *cameraProfiles API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0));

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMLocationEvent.h
//
//  HMLocationEvent.h
//  HomeKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMEvent.h>

NS_ASSUME_NONNULL_BEGIN

@class CLRegion;

/*!
 * @brief This class represents an event that is evaluated based on entry to and/or
 *        exit from a Region
 */
API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
@interface HMLocationEvent : HMEvent <NSCopying, NSMutableCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Initializes a new location event object
 *
 * @param region - Region with at least one property of notifyOnEntry or notifyOnExit set to TRUE.
 *
 * @return Instance object representing the location event.
 */
- (instancetype)initWithRegion:(CLRegion *)region API_UNAVAILABLE(watchos, tvos);

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
- (void)updateRegion:(CLRegion *)region completionHandler:(void (^)(NSError * __nullable error))completion API_DEPRECATED("No longer supported.", ios(9.0, 11.0)) API_UNAVAILABLE(watchos, tvos);

@end


/*!
 * @brief This class represents an event that is evaluated based on entry to and/or
 *        exit from a Region
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos)
@interface HMMutableLocationEvent : HMLocationEvent

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Region on which events are triggered based on the properties notifyOnEntry and notifyOnExit.
 *        This property will be nil when an application is not authorized for location services.
 */
@property(readwrite, strong, nonatomic, nullable) CLRegion *region;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCameraSettingsControl.h
//
//  HMCameraSettingsControl.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <HomeKit/HMCameraControl.h>
#import <HomeKit/HMDefines.h>

@class HMCharacteristic;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract This class can be used to control the settings on a camera.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos)
@interface HMCameraSettingsControl : HMCameraControl

- (instancetype)init NS_UNAVAILABLE;

/*!
 *  Characteristic corresponding to night vision setting on the camera.
 */
@property(readonly, strong, nonatomic, nullable) HMCharacteristic *nightVision;

/*!
 * Characteristic corresponding to current horizontal tilt setting on the camera.
 */
@property(readonly, strong, nonatomic, nullable) HMCharacteristic *currentHorizontalTilt;

/*!
 * Characteristic corresponding to target horizontal tilt setting on the camera.
 */
@property(readonly, strong, nonatomic, nullable) HMCharacteristic *targetHorizontalTilt;

/*!
 * Characteristic corresponding to current vertical tilt setting on the camera.
 */
@property(readonly, strong, nonatomic, nullable) HMCharacteristic *currentVerticalTilt;

/*!
 * Characteristic corresponding to target vertical tilt setting on the camera.
 */
@property(readonly, strong, nonatomic, nullable) HMCharacteristic *targetVerticalTilt;

/*!
 * Characteristic corresponding to optical zoom setting on the camera.
 */
@property(readonly, strong, nonatomic, nullable) HMCharacteristic *opticalZoom;

/*!
 * Characteristic corresponding to digital zoom setting on the camera.
 */
@property(readonly, strong, nonatomic, nullable) HMCharacteristic *digitalZoom;

/*!
 * Characteristic corresponding to image rotation setting on the camera.
 */
@property(readonly, strong, nonatomic, nullable) HMCharacteristic *imageRotation;

/*!
 * Characteristic corresponding to image mirroring setting on the camera.
 */
@property(readonly, strong, nonatomic, nullable) HMCharacteristic *imageMirroring;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMAccessoryProfile.h
//
//  HMAccessoryProfile.h
//  HomeKit
//
//  Copyright © 2015-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

@class HMAccessory;
@class HMService;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract Represents a profile implemented by an accessory.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos)
@interface HMAccessoryProfile : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief A unique identifier for the profile.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier;

/*!
 * @brief Collection of services representing the profile.
 */
@property(readonly, strong, nonatomic) NSArray<HMService *> *services;

/*!
 * @brief Accessory implementing the profile.
 */
@property(readonly, weak, nonatomic) HMAccessory *accessory;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMHomeAccessControl.h
//
//  HMHomeAccessControl.h
//  HomeKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <HomeKit/HMDefines.h>
#import <HomeKit/HMAccessControl.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief Represents the access control of a user associated with a home.
 */
API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
@interface HMHomeAccessControl : HMAccessControl

/*!
 * @brief Specifies if the user has administrative privileges for the home.
 */
@property(readonly, getter=isAdministrator, nonatomic) BOOL administrator;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMNumberRange.h
//
//  HMNumberRange.h
//  HomeKit
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class describes a range of numbers: [min, max]
 *
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos)
@interface HMNumberRange : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Initializes a new range of numbers
 *
 * @param minValue The minimum value of the range.
 *
 * @param maxValue The maximum value of the range.
 */
+ (instancetype)numberRangeWithMinValue:(NSNumber *)minValue maxValue:(NSNumber *)maxValue;

/*!
 * @brief Initializes a new range of numbers. The maximum value is set to a large value.
 *
 * @param minValue The minimum value of the range.
 *
 */
+ (instancetype)numberRangeWithMinValue:(NSNumber *)minValue;

/*!
 * @brief Initializes a new range of numbers. The minimum value is set to a small value.
 *
 * @param maxValue The maximum value of the range.
 *
 */
+ (instancetype)numberRangeWithMaxValue:(NSNumber *)maxValue;

/*!
 * @brief The minimum value of the range.
 */
@property(nullable, readonly, strong, nonatomic) NSNumber *minValue;

/*!
 * @brief The maximum value of the range.
 */
@property(nullable, readonly, strong, nonatomic) NSNumber *maxValue;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMAccessControl.h
//
//  HMAccessControl.h
//  HomeKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @abstract   The HMAccessControl class represents a generic access control.
 */
API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) API_UNAVAILABLE(macos)
@interface HMAccessControl : NSObject

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCameraSource.h
//
//  HMCameraSource.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief Abstract class for source of data from a camera.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos)
@interface HMCameraSource : NSObject

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMEventTrigger.h
//
//  HMEventTrigger.h
//  HomeKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMTrigger.h>
#import <HomeKit/HMEventTriggerActivationState.h>
#import <HomeKit/HMSignificantTimeEvent.h>

NS_ASSUME_NONNULL_BEGIN

@class HMEvent;
@class HMCharacteristic;
@class HMPresenceEvent;


/*!
 * @group Specifies a group of events that are deemed significant events in a day.
 *        These are also the key paths for the event in a NSPredicate.
 */

/*!
 * @brief Specifies the key path for a characteristic in a NSPredicate
 */
HM_EXTERN NSString * const HMCharacteristicKeyPath API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Specifies the key path for a characteristic value in a NSPredicate
 */
HM_EXTERN NSString * const HMCharacteristicValueKeyPath API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Specifies the key path for a presence event in a NSPredicate
 */
HM_EXTERN NSString * const HMPresenceKeyPath API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos);


/*!
 * @brief Triggers based on events.
 *
 * @discussion This class represents a trigger that is based on events.
 */
API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
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
                   predicate:(nullable NSPredicate *)predicate API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Initializes a new event trigger object.
 *
 * @param name Name of the event trigger.
 *
 * @param events Array of events that can trigger the evaluation of the trigger. Note: The trigger will
 *               be evaluated if any one of the events is true.
 *
 * @param endEvents Array of end events that can trigger the restoration to the state before the scene was run.
 *
 * @param recurrences Specifies the days of the week when the trigger is to be evaluated. Only the 'weekday' property
 *                    is honored in NSDateComponents.
 *
 * @param predicate The predicate to evaluate before executing any of the actions sets associated to this
 *                  event.
 *
 * @return Instance object representing the event trigger.
 */
- (instancetype)initWithName:(NSString *)name
                      events:(NSArray<HMEvent *> *)events
                   endEvents:(nullable NSArray<HMEvent *> *)endEvents
                 recurrences:(nullable NSArray<NSDateComponents *> *)recurrences
                   predicate:(nullable NSPredicate *)predicate API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief The events associated with the trigger.
 */
@property(readonly, copy, nonatomic) NSArray<HMEvent *> *events;

/*!
 * @brief The events that correspond to executing the restore of the scene before the trigger was executed.
 *        E.g. Execute the scene for 10 mins and restore original state is achieved by specifying a corresponding
 *        HMDurationEvent in the list of endEvents. HMCharacteristicEvent or HMCharacteristicThresholdRangeEvents
 *        can also be added to end events
 */
@property(readonly, copy, nonatomic) NSArray<HMEvent *> *endEvents API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 * @brief The predicate to evaluate before executing the action sets associated with the trigger.
 */
@property(readonly, copy, nonatomic, nullable) NSPredicate *predicate;

/*!
 * @brief recurrences Specifies the recurrences for when the trigger is evaluated. This only supports days of the week.
 */
@property(readonly, copy, nonatomic, nullable) NSArray<NSDateComponents *> *recurrences API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 * @brief Specifies whether this trigger is executed only once after which the trigger is disabled.
 */
@property(readonly, nonatomic) BOOL executeOnce API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 * @brief Specifies the current activation state of the trigger.
 */
@property(readonly, assign, nonatomic) HMEventTriggerActivationState triggerActivationState API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));


/*!
 * @brief Adds a new event to the event trigger.
 *
 * @param event Event to add to the event trigger.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addEvent:(HMEvent *)event completionHandler:(void (^)(NSError * __nullable error))completion API_DEPRECATED("Use updateEvents:completionHandler: instead", ios(9.0, 11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Removes the specified event from the event trigger.
 *
 * @param event Event to remove from the event trigger.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeEvent:(HMEvent *)event completionHandler:(void (^)(NSError * __nullable error))completion API_DEPRECATED("Use updateEvents:completionHandler: instead", ios(9.0, 11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Updates the set of events in the event trigger.
 *
 * @param events Events to update in the event trigger
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateEvents:(NSArray<HMEvent *> *)events completionHandler:(void (^)(NSError * __nullable error))completion API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Updates the set of events in the event trigger.
 *
 * @param events Events to update in the event trigger
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateEndEvents:(NSArray<HMEvent *> *)endEvents completionHandler:(void (^)(NSError * __nullable error))completion API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief This method replaces the predicate used to evaluate execution of the action sets associated with the trigger.
 *
 * @param predicate The new predicate for the event trigger.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request,
 *                   error will be nil on success. 
 */
- (void)updatePredicate:(nullable NSPredicate *)predicate completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief This method replaces the recurrences which secifies the days of the week when the trigger is to be evaluated.
 *
 * @param recurrences The new recurrences for the event trigger.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request,
 *                   error will be nil on success.
 */
- (void)updateRecurrences:(nullable NSArray<NSDateComponents *> *)recurrences completionHandler:(void (^)(NSError * __nullable error))completion API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief This method is used to update whether the event trigger repeats or not.
 *
 * @param executeOnce Specifies whether the event trigger is repeated or not.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateExecuteOnce:(BOOL)executeOnce completionHandler:(void (^)(NSError * __nullable error))completion API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

@end

@interface HMEventTrigger(NSPredicate)

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
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringBeforeSignificantEvent:(NSString *)significantEvent
                                                               applyingOffset:(nullable NSDateComponents *)offset API_DEPRECATED("Use predicateForEvaluatingTriggerOccurringBeforeSignificantEvent: instead", ios(9.0, 11.0));

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred before a significant event.
 *
 * @param significantEvent The significant event to compare against.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringBeforeSignificantEvent:(HMSignificantTimeEvent *)significantEvent API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred after a significant event.
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
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringAfterSignificantEvent:(NSString *)significantEvent
                                                              applyingOffset:(nullable NSDateComponents *)offset API_DEPRECATED("Use predicateForEvaluatingTriggerOccurringAfterSignificantEvent: instead", ios(9.0, 11.0));

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred after a significant event.
 *
 * @param significantEvent The significant event to compare against.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringAfterSignificantEvent:(HMSignificantTimeEvent *)significantEvent API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred between two significant events.
 *
 * @param firstSignificantEvent The first significant event.
 *
 * @param secondSignificantEvent The second significant event.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringBetweenSignificantEvent:(HMSignificantTimeEvent *)firstSignificantEvent
                                                        secondSignificantEvent:(HMSignificantTimeEvent *)secondSignificantEvent API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

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
 * @brief Creates a predicate that will evaluate whether the event occurred between two times.
 *
 * @param firstSignificantEvent The first date component.
 *
 * @param secondSignificantEvent The second date component.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringBetweenDateWithComponents:(NSDateComponents *)firstDateComponents
                                                        secondDateWithComponents:(NSDateComponents *)secondDateWithComponents API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

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
 * @brief Creates a predicate that will evaluate based on the presence event.
 *
 * @param presenceEvent The presenceEvent that is evaluated as part of the predicate.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerWithPresence:(HMPresenceEvent *)presenceEvent API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMError.h
//
//  HMError.h
//  HomeKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

HM_EXTERN NSString * const HMErrorDomain API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos);

/*!
 * @brief This enumeration describes the possible error constants that can be
 *        returned from the the HomeKit APIs.
 */
typedef NS_ENUM(NSInteger, HMErrorCode) {
    HMErrorCodeUnexpectedError                         API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) = -1,
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
    HMErrorCodeCannotRemoveBuiltinActionSet            API_AVAILABLE(ios(9.0)) = 83,
    HMErrorCodeLocationForHomeDisabled                 API_AVAILABLE(ios(9.0)) = 84,
    HMErrorCodeNotAuthorizedForLocationServices        API_AVAILABLE(ios(9.0)) = 85,
    HMErrorCodeReferToUserManual                       API_AVAILABLE(ios(9.3)) = 86,
    HMErrorCodeInvalidOrMissingAuthorizationData       API_AVAILABLE(ios(10.0)) = 87,
    HMErrorCodeBridgedAccessoryNotReachable            API_AVAILABLE(ios(10.0)) = 88,
    HMErrorCodeNotAuthorizedForMicrophoneAccess        API_AVAILABLE(ios(10.0)) = 89,
    HMErrorCodeIncompatibleNetwork                     API_AVAILABLE(ios(10.2)) = 90,
    HMErrorCodeNoHomeHub                               API_AVAILABLE(ios(11.0)) = 91,
    HMErrorCodeNoCompatibleHomeHub                     API_AVAILABLE(ios(11.0)) = 92,
    HMErrorCodeIncompatibleAccessory                   API_AVAILABLE(ios(11.3)) = 93,
    HMErrorCodeIncompatibleHomeHub                     API_DEPRECATED_WITH_REPLACEMENT("HMErrorCodeNoCompatibleHomeHub", ios(11.0, 11.0), watchos(4.0, 4.0), tvos(11.0, 11.0)) API_UNAVAILABLE(macos) = HMErrorCodeNoCompatibleHomeHub,
    HMErrorCodeObjectWithSimilarNameExists             API_AVAILABLE(ios(12.0)) = 95,
} API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCameraAudioControl.h
//
//  HMCameraAudioControl.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <HomeKit/HMCameraControl.h>
#import <HomeKit/HMDefines.h>

@class HMCharacteristic;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos)
@interface HMCameraAudioControl : HMCameraControl

- (instancetype)init NS_UNAVAILABLE;

/*!
 * Characteristic corresponding to mute setting on the camera.
 */
@property(readonly, strong, nonatomic, nullable) HMCharacteristic *mute;

/*!
 * Characteristic corresponding to volume setting on the camera.
 */
@property(readonly, strong, nonatomic, nullable) HMCharacteristic *volume;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCharacteristicEvent.h
//
//  HMCharacteristicEvent.h
//  HomeKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMEvent.h>

NS_ASSUME_NONNULL_BEGIN

@class HMCharacteristic;

/*!
 * @brief This class represents an event that is evaluated based on the value of a characteristic
 *        set to a particular value.
 */
API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
@interface HMCharacteristicEvent<TriggerValueType : id<NSCopying>> : HMEvent <NSCopying, NSMutableCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Initializes a new characteristic event object
 *
 * @param characteristic The characteristic bound to the event. The characteristic must 
 *                       support notification. An exception will be thrown otherwise.
 *
 * @param triggerValue The value of the characteristic that triggers the event. 
 *                     Specifying nil as the trigger value corresponds to any change in the value of the
 *                     characteristic.
 *
 * @return Instance object representing the characteristic event.
 */
- (instancetype)initWithCharacteristic:(HMCharacteristic *)characteristic
                          triggerValue:(nullable TriggerValueType)triggerValue API_UNAVAILABLE(watchos, tvos);

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
- (void)updateTriggerValue:(nullable TriggerValueType)triggerValue completionHandler:(void (^)(NSError * __nullable error))completion API_DEPRECATED("No longer supported.", ios(9.0, 11.0)) API_UNAVAILABLE(watchos, tvos);

@end

/*!
 * @brief This class represents an event that is evaluated based on the value of a characteristic
 *        set to a particular value.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos)
@interface HMMutableCharacteristicEvent<TriggerValueType : id<NSCopying>> : HMCharacteristicEvent

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief The characteristic associated with the event.
 */
@property(readwrite, strong, nonatomic) HMCharacteristic *characteristic;

/*!
 * @brief The value of the characteristic that triggers the event.
 *        A value of nil corresponds to any change in the value of the characteristic.
 */
@property(readwrite, copy, nonatomic, nullable) TriggerValueType triggerValue;

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
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMAccessoryCategoryTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class is used to represent an accessory category.
 */
API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
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
//
//  HMRoom.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMAccessory;

/*!
 * @brief This class describes a room in the home.
 */
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
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
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));

/*!
 * @brief This method is used to change the name of the room.
 *
 * @param name New name for the room.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

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
HM_EXTERN NSString * const HMCharacteristicPropertySupportsEventNotification API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief This constant specifies that the characteristic is readable.
 */
HM_EXTERN NSString * const HMCharacteristicPropertyReadable API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief This constant specifies that the characteristic is writable.
 */
HM_EXTERN NSString * const HMCharacteristicPropertyWritable API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief This constant specifies that the characteristic should be hidden from the user.
 */
HM_EXTERN NSString * const HMCharacteristicPropertyHidden API_AVAILABLE(ios(9.3), watchos(2.2), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @group Accessory Service Characteristic Types
 *
 * @brief These constants define the characteristic types supported by the HomeKit Accessory Profile for HomeKit based accessories.
 */

/*!
 * @brief Characteristic type for power state. The value of the characteristic is a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypePowerState API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for hue. The value of the characteristic is a float value in arc degrees.
 */
HM_EXTERN NSString * const HMCharacteristicTypeHue API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for saturation. The value of the characteristic is a float value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSaturation API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for brightness. The value of the characteristic is an int value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeBrightness API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for temperature units. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueTemperatureUnit.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTemperatureUnits API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for current temperature. The value of the characteristic is a float value in Celsius.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentTemperature API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for target temperature. The value of the characteristic is a float value in Celsius.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetTemperature API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for heating/cooling mode. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueHeatingCooling and indicates the current heating/cooling mode.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentHeatingCooling API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for target heating/cooling mode. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueHeatingCooling and indicates the target heating/cooling mode.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetHeatingCooling API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for cooling threshold temperature. The value of the characteristic is a float value in Celsius.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCoolingThreshold API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for heating threshold temperature. The value of the characteristic is a float value in Celsius.
 */
HM_EXTERN NSString * const HMCharacteristicTypeHeatingThreshold API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for current relative humidity. The value of the characteristic is a float value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentRelativeHumidity API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for target relative humidity. The value of the characteristic is a float value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetRelativeHumidity API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for current door state. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueDoorState and indicates the current door state.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentDoorState API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for target door state. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueDoorState and indicates the target door state.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetDoorState API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for obstruction detected. The value of the characteristic is a boolean value.
 */
HM_EXTERN NSString * const HMCharacteristicTypeObstructionDetected API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for name. The value of the characteristic is a string.
 */
HM_EXTERN NSString * const HMCharacteristicTypeName API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for manufacturer. The value of the characteristic is a string.
 */
HM_EXTERN NSString * const HMCharacteristicTypeManufacturer API_DEPRECATED_WITH_REPLACEMENT("Use -[HMAccessory manufacturer] instead", ios(8.0, 11.0), watchos(2.0, 4.0), tvos(10.0, 11.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for model. The value of the characteristic is a string.
 */
HM_EXTERN NSString * const HMCharacteristicTypeModel API_DEPRECATED_WITH_REPLACEMENT("Use -[HMAccessory model] instead", ios(8.0, 11.0), watchos(2.0, 4.0), tvos(10.0, 11.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for serial number. The value of the characteristic is a string.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSerialNumber API_DEPRECATED("No longer supported", ios(8.0, 11.0), watchos(2.0, 4.0), tvos(10.0, 11.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for identify. The characteristic is write-only that takes a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeIdentify API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for rotation direction. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueRotationDirection and indicates the fan rotation direction.
 */
HM_EXTERN NSString * const HMCharacteristicTypeRotationDirection API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for rotation speed. The value of the characteristic is a float representing
 *        the percentage of maximum speed.
 */
HM_EXTERN NSString * const HMCharacteristicTypeRotationSpeed API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for outlet in use. The value of the characteristic is a boolean, which is true
 *        if the outlet is in use.
 */
HM_EXTERN NSString * const HMCharacteristicTypeOutletInUse API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for version. The value of the characteristic is a string.
 */
HM_EXTERN NSString * const HMCharacteristicTypeVersion API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for logs. The value of the characteristic is TLV8 data wrapped in an NSData.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLogs API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for audio feedback. The value of the characteristic is a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeAudioFeedback API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for admin only access. The value of the characteristic is a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeAdminOnlyAccess API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for Security System Alarm Type. The value of the characteristic is a uint8.
 *        indicating the type of alarm triggered by a security system service. This characteristic has a value
 *        of 1 when the alarm type is not known and a value of 0 indicates that the alarm conditions are cleared.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSecuritySystemAlarmType API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for motion detected. The value of the characteristic is a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeMotionDetected API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for current lock mechanism state. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueLockMechanismState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentLockMechanismState API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for target lock mechanism state. The value of the characteristic is either
 *        HMCharacteristicValueLockMechanismStateUnsecured, or HMCharacteristicValueLockMechanismStateSecured,
 *        as defined by HMCharacteristicValueLockMechanismState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetLockMechanismState API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for the last known action for a lock mechanism. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueLockMechanismLastKnownAction.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLockMechanismLastKnownAction API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for the control point for lock management. The characteristic is write-only that takes TLV8 data wrapped in an NSData.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLockManagementControlPoint API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for the auto secure timeout for lock management. The value of the characteristic is an unsigned 
          32-bit integer representing the number of seconds.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLockManagementAutoSecureTimeout API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for density of air-particulate matter. The value of the characteristic is
 *        in units of micrograms/m^3.
 */
HM_EXTERN NSString * const HMCharacteristicTypeAirParticulateDensity API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for size of air-particulate matter. The value of the characteristic is
 *        one of the values defined for HMCharacteristicValueAirParticulateSize.
 */
HM_EXTERN NSString * const HMCharacteristicTypeAirParticulateSize API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for air quality. The value of the characteristic is
 *        one of the values defined for HMCharacteristicValueAirQuality.
 */
HM_EXTERN NSString * const HMCharacteristicTypeAirQuality API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for battery level. The value of the characteristic is an uint8
 *        value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeBatteryLevel API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for carbon dioxide detected. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates carbon dioxide levels are normal.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonDioxideDetected API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for carbon dioxide level.
 *        The value of the characteristic is a float value in units of ppm.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonDioxideLevel API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for carbon dioxide peak level.
 *        The value of the characteristic is a float value in units of ppm.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonDioxidePeakLevel API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for carbon monoxide detected. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates carbon monoxide levels are normal.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonMonoxideDetected API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for carbon monoxide level.
 *        The value of the characteristic is a float value in units of ppm.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonMonoxideLevel API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for carbon monoxide peak level.
 *        The value of the characteristic is a float value in units of ppm.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonMonoxidePeakLevel API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for Charging state. The value of the characteristic is a uint8.
 *        A value of 1 indicates charging is in progress.
 */
HM_EXTERN NSString * const HMCharacteristicTypeChargingState API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for Contact sensor state. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates that contact is detected; a value of 1 indicates no contact is detected.
 */
HM_EXTERN NSString * const HMCharacteristicTypeContactState API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for current horizontal tilt angle. The value is a float representing the angle in arc degrees.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentHorizontalTilt API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for current light level. The value of the characteristic in units of lux.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentLightLevel API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for current position of a door/window. The value of the characteristic is an
 *        uint8 value in percent. A value of 0 indicates closed/most shade/least light allowed state and a
 *        value of 100 indicates open/no shade/most light allowed state.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentPosition API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for current security system state. The value of the characteristic is one of
 *        the values defined for HMCharacteristicValueCurrentSecuritySystemState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentSecuritySystemState API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for current vertical tilt angle. The value is a float representing the angle in arc degrees.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentVerticalTilt API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for firmware version. The value of the characteristic is a string value
 *        describing the firmware version of the accessory.
 */
HM_EXTERN NSString * const HMCharacteristicTypeFirmwareVersion API_DEPRECATED_WITH_REPLACEMENT("Use -[HMAccessory firmwareVersion] instead", ios(8.0, 11.0), watchos(2.0, 4.0), tvos(10.0, 11.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for hardware version. The value of the characteristic is a string value
 *        describing the hardware version of the accessory.
 */
HM_EXTERN NSString * const HMCharacteristicTypeHardwareVersion API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for Hold Position. The value of the characteristic is a boolean
 *        indicating that the current position should be held/maintained.
 */
HM_EXTERN NSString * const HMCharacteristicTypeHoldPosition API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for programmable switch input event. The value of the characteristic is an int
 *        that can change based on the type of programmable switch. For a binary programmable switch, a value of 0
 *        indicates OFF (and 1 indicates ON). For a slider programmable switch, the value indicates the level.
 */
HM_EXTERN NSString * const HMCharacteristicTypeInputEvent API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for leak detected. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates no leak is detected; a value of 1 indicates that a leak is detected.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLeakDetected API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for Occupancy Detected. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates no occupancy is detected; a value of 1 indicates that occupancy is detected.
 */
HM_EXTERN NSString * const HMCharacteristicTypeOccupancyDetected API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for programmable switch output state. This value is to be used for presentation
 *        purposes. For a binary programmable switch, a value of 1 can be used to present a state of ON.
 */
HM_EXTERN NSString * const HMCharacteristicTypeOutputState API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for Position state. The value of the characteristic is one of the
 *        one of the values defined for HMCharacteristicValuePositionState.
 */
HM_EXTERN NSString * const HMCharacteristicTypePositionState API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for Smoke Detected. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates no smoke is detected; a value of 1 indicates that smoke is detected.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSmokeDetected API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for software version. The value of the characteristic is a string value
 *        describing the software version of the accessory.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSoftwareVersion API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type to indicate status of a service is active. The value of the characteristic is a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeStatusActive API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type to indicate status of a service is fault. The value of the characteristic is a uint8 value.
 */
HM_EXTERN NSString * const HMCharacteristicTypeStatusFault API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type to indicate status of a service is jammed. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates that the service is not jammed; a value of 1 indicates that the service is jammed.
 */
HM_EXTERN NSString * const HMCharacteristicTypeStatusJammed API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type to indicate status of a service is low battery. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates battery level is normal; a value of 1 indicates that battery level is low.
 */
HM_EXTERN NSString * const HMCharacteristicTypeStatusLowBattery API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type to indicate status of a service is tampered. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates no tampering has been detected; a value of 1 indicates that a tampering has been detected.
 */
HM_EXTERN NSString * const HMCharacteristicTypeStatusTampered API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for target horizontal tilt angle. The value is a float representing the angle in arc degrees.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetHorizontalTilt API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for target security system state. The value of the characteristic is one of
 *        the values defined for HMCharacteristicValueTargetSecuritySystemState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetSecuritySystemState API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for target position of a door/window/window covering. The value of the
 *        characteristic is an uint8 value in percent. A value of 0 indicates closed/most shade/least
 *        light allowed state and a value of 100 indicates open/no shade/most light allowed state.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetPosition API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for target vertical tilt angle. The value is a float representing the angle in arc degrees.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetVerticalTilt API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for streaming status. The value is a tlv8 data.
 */
HM_EXTERN NSString * const HMCharacteristicTypeStreamingStatus API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for setup stream endpoint. The value is a tlv8 data.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSetupStreamEndpoint API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for supported video stream configuration. The value is a tlv8 data.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSupportedVideoStreamConfiguration API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for supported audio stream configuration. The value is a tlv8 data.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSupportedAudioStreamConfiguration API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for supported RTP stream configuration. The value is a tlv8 data.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSupportedRTPConfiguration API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for selected stream configuration. The value is a tlv8 data.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSelectedStreamConfiguration API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for volume control. The value is float.
 */
HM_EXTERN NSString * const HMCharacteristicTypeVolume API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for mute control. The value is boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeMute API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for camera night vision. The value is boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeNightVision API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for camera optical zoom. The value is float.
 */
HM_EXTERN NSString * const HMCharacteristicTypeOpticalZoom API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for camera digital zoom. The value is float.
 */
HM_EXTERN NSString * const HMCharacteristicTypeDigitalZoom API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for camera image rotation. The value is float with valid values: 0, 90, 180 and 270
 */
HM_EXTERN NSString * const HMCharacteristicTypeImageRotation API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for image mirroring. The value is boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeImageMirroring API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for label namespace used to label the services on an accessory with
 *        multiple services of the same type. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueLabelNamespace.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLabelNamespace API_AVAILABLE(ios(10.3), watchos(3.2), tvos(10.2)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type describing the index of the label for the service on accessory with multiple
 *        instances of the same service. The value is an integer and starts from 1.
 *        For a label namespace of HMCharacteristicValueLabelNamespaceDot, label index indicates the
 *        number of dots - ., .., ..., and so on.
 *        For a label namespace of HMCharacteristicValueLabelNamespaceNumeral, label index indicates the arabic
 *        numeral - 1, 2, 3, and so on.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLabelIndex API_AVAILABLE(ios(10.3), watchos(3.2), tvos(10.2)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for active status. The value is one of the
 *        values defined for HMCharacteristicValueActivationState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeActive API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for air purifier current state. The value is
 *        one of the value defined for HMCharacteristicValueCurrentAirPurifierState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentAirPurifierState API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for air purifier target state. The value is
 *        one of the value defined for HMCharacteristicValueTargetAirPurifierState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetAirPurifierState API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for current fan state. The value is
 *        one of the values defined for HMCharacteristicValueCurrentFanState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentFanState API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for heater/cooler current state. The value is
 *        one of the values defined for HMCharacteristicValueCurrentHeaterCoolerState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentHeaterCoolerState API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for humidifier/dehumidifier current state. The value is
 *        one of the values defined for HMCharacteristicValueCurrentHumidifierDehumidifierState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentHumidifierDehumidifierState API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for current slat state. The value is
 *        one of the values defined for HMCharacteristicValueCurrentSlatState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentSlatState API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for water level. The value is in percentage units.
 */
HM_EXTERN NSString * const HMCharacteristicTypeWaterLevel API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for filter change indication. The value is
 *        one of the values defined for HMCharacteristicValueFilterChange.
 */
HM_EXTERN NSString * const HMCharacteristicTypeFilterChangeIndication API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for filter life level. The value is in percentage units.
 */
HM_EXTERN NSString * const HMCharacteristicTypeFilterLifeLevel API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for resetting filter change indication. The characteristic
 *        is write-only that takes a boolean value of 1.
 */
HM_EXTERN NSString * const HMCharacteristicTypeFilterResetChangeIndication API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for locking physical controls. The value is
 *        one of the values defined for HMCharacteristicValueLockPhysicalControlsState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLockPhysicalControls API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for swing mode. The value is
 *        one of the values defined for HMCharacteristicValueSwingMode.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSwingMode API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for target heater/cooler state. The value is
 *        one of the values defined for HMCharacteristicValueTargetHeaterCoolerState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetHeaterCoolerState API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for target humidifier/dehumidifier state. The value
 *        is one of the values defined for HMCharacteristicValueTargetHumidifierDehumidifierState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetHumidifierDehumidifierState API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for target fan state. The value is
 *        one of the values defined for HMCharacteristicValueTargetFanState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetFanState API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for slat type. The value is
 *        one of the values defined for HMCharacteristicValueSlatType.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSlatType API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for current tilt angle. The value is a float representing the angle in arc degrees.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentTilt API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for target tilt angle. The value is a float representing the angle in arc degrees.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetTilt API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for density of ozone. The value of the characteristic is
 *        in units of micrograms/m^3.
 */
HM_EXTERN NSString * const HMCharacteristicTypeOzoneDensity API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for density of nitrogen dioxide. The value of the characteristic is
 *        in units of micrograms/m^3.
 */
HM_EXTERN NSString * const HMCharacteristicTypeNitrogenDioxideDensity API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for density of sulphur dioxide. The value of the characteristic is
 *        in units of micrograms/m^3.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSulphurDioxideDensity API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for density of air-particulate matter of size 2.5 micrograms. The
 *        value of the characteristic is in units of micrograms/m^3.
 */
HM_EXTERN NSString * const HMCharacteristicTypePM2_5Density API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for density of air-particulate matter of size 10 micrograms. The
 *        value of the characteristic is in units of micrograms/m^3.
 */
HM_EXTERN NSString * const HMCharacteristicTypePM10Density API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for density of volatile organic compounds. The value of the
 *        characteristic is in units of micrograms/m^3.
 */
HM_EXTERN NSString * const HMCharacteristicTypeVolatileOrganicCompoundDensity API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for dehumidifier threshold. The value of the characteristic is
 *        a float value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeDehumidifierThreshold API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for humidifier threshold. The value of the characteristic is
 *        a float value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeHumidifierThreshold API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for color temperature. The value of the characteristic is
 *        an int representing the mired value of the color temperature.
 */
HM_EXTERN NSString * const HMCharacteristicTypeColorTemperature API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for program mode. The value of the characteristic is one of the values defined
 *        for HMCharacteristicValueProgramMode.
 */
HM_EXTERN NSString * const HMCharacteristicTypeProgramMode API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for in use. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueUsageState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeInUse API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for set duration. The value of the characteristic is an int value in
 *        seconds.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSetDuration API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for remaining duration. The value of the characteristic is an int value in
 *        seconds.
 */
HM_EXTERN NSString * const HMCharacteristicTypeRemainingDuration API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for valve type. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueValveType.
 */
HM_EXTERN NSString * const HMCharacteristicTypeValveType API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) API_UNAVAILABLE(macos);

/*!
 * @brief Characteristic type for is-configured. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueConfigurationState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeIsConfigured API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMServiceGroup.h
//
//  HMServiceGroup.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMService;

/*!
 * @abstract Used to describe a collection of HMService objects
 *
 * @discussion This class is used to group a collection of HMService objects.
 *             This allows for association of a set of accessory services into a group.
 *             Eg. A collection of lights can be grouped as the "Desk Lamps" service group.
 */
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
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
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));

/*!
 * @brief This method is used to change the name of the service group.
 *
 * @param name New name for the service group.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

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
- (void)addService:(HMService *)service completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Removes an service from this service group.
 *
 * @param service Service to remove from this group.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeService:(HMService *)service completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMAction.h
//  HMAction.h
//  HomeKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class is used to represent a generic action.
 */
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
@interface HMAction : NSObject

/*!
 * @brief A unique identifier for the action.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMZone.h
//
//  HMZone.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

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
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
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
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));

/*!
 * @brief This method is used to change the name of the zone.
 *
 * @param name New name for the zone.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

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
- (void)addRoom:(HMRoom *)room completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Removes a room from the zone.
 *
 * @param room Room to remove from this zone.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeRoom:(HMRoom *)room completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

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
HM_EXTERN NSString * const HMAccessoryCategoryTypeOther API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Security System.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeSecuritySystem API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Bridge.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeBridge API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Door.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeDoor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Door Lock.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeDoorLock API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Fan.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeFan API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Garage Door Opener.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeGarageDoorOpener API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*
* @brief Category type for IP Camera.
*/
HM_EXTERN NSString * const HMAccessoryCategoryTypeIPCamera API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Lightbulb.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeLightbulb API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Outlet.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeOutlet API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Programmable Switch.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeProgrammableSwitch API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Range Extender
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeRangeExtender API_AVAILABLE(ios(9.3), watchos(2.2)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Sensor.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Switch.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeSwitch API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Thermostat.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeThermostat API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Video Doorbell.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeVideoDoorbell API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Window.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeWindow API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Window Covering.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeWindowCovering API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Air Purifier.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeAirPurifier API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Air Heater.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeAirHeater API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Air Conditioner.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeAirConditioner API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Air Humidifier.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeAirHumidifier API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Air Dehumidifier.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeAirDehumidifier API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Sprinkler.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeSprinkler API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Faucet.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeFaucet API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) API_UNAVAILABLE(macos);

/*!
 * @brief Category type for Shower Head.
 */
HM_EXTERN NSString * const HMAccessoryCategoryTypeShowerHead API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) API_UNAVAILABLE(macos);
// ==========  HomeKit.framework/Headers/HMCameraDefines.h
//
//  HMCameraDefines.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

/*!
 * @abstract This enumeration describes the different states of a camera stream.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos)
typedef NS_ENUM(NSUInteger, HMCameraStreamState)
{
    /*!
     * Start stream request is in progress.
     */
    HMCameraStreamStateStarting = 1,

    /*!
     * Streaming is in progress.
     */
    HMCameraStreamStateStreaming = 2,

    /*!
     * Stop stream request is in progress.
     */
    HMCameraStreamStateStopping = 3,

    /*!
     * No streaming is in progress.
     */
    HMCameraStreamStateNotStreaming = 4
};

/*!
 * @abstract This enumeration describes the setting for audio on the recipient of the camera stream.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos)
typedef NS_ENUM(NSUInteger, HMCameraAudioStreamSetting)
{
    /*!
     * Muted for incoming and outgoing audio.
     */
    HMCameraAudioStreamSettingMuted = 1,

    /*!
     * Only incoming audio is allowed.
     */
    HMCameraAudioStreamSettingIncomingAudioAllowed = 2,

    /*!
     * Bidirectional audio is allowed.
     */
    HMCameraAudioStreamSettingBidirectionalAudioAllowed = 3,
};


// ==========  HomeKit.framework/Headers/HMAccessoryBrowser.h
//
//  HMAccessoryBrowser.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMHome;
@class HMAccessory;

@protocol HMAccessoryBrowserDelegate;

/*! 
 * @brief This class is used to discover new accessories in the home
 *        that have never been paired with and therefore not part of the home.
 */
API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, watchos, tvos) 
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
 *             This will scan for the following types of accessories:
 *                 Accessories supporting HomeKit Wireless Accessory Configuration profile
 *                 Accessories supporting HomeKit Accessory Protocol and are already on
 *                     the same infrastructure IP network
 *                 Accessories supporting HomeKit Accessory Protocol on Bluetooth LE transport
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
 *             The contents of the array of discovered accessories will not be updated until 
 *             startSearchingForNewAccessories is called.
 */
- (void)stopSearchingForNewAccessories;

@end

/*!
 * @brief This delegate receives updates about new accessories in the home.
 */
API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, watchos, tvos) 
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
//
//  HMService.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

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
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
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
@property(readonly, copy, nonatomic) NSString *localizedDescription API_AVAILABLE(ios(9.0));

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
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));

/*!
 * @brief Indicates if this service supports user interaction or not.
 *
 * @discussion Applications should use this property to filter out services that the users
 *             should not directly interact with, e.g. HMServiceTypeAccessoryInformation.
 */
@property(readonly, getter=isUserInteractive, nonatomic) BOOL userInteractive API_AVAILABLE(ios(9.0));

/*!
 * @brief Indicates if this services is the primary service.
 *
 * @discussion Applications should use this property to show the primary service on the accessory.
 */
@property(readonly, getter=isPrimaryService, nonatomic) BOOL primaryService API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0));

/*!
 * @brief Array of HMService objects that represents all the services that the service links to.
 *  
 * @discussion Applications should use this property to show logical grouping of services on the accessory.
 *             linkedServices will be nil when the service does not link to any other services.
 */
@property(readonly, copy, nonatomic) NSArray<HMService *> * __nullable linkedServices API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0));

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
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief This method is used to set up the service type of the device connected to a contact sensor, switch or an outlet.
 *
 * @param serviceType Service type of the device connected to a contact sensor/switch/outlet service.
 *
 * @discussion This method is only valid for the services of the following types:
 *                 HMServiceTypeOutlet, HMServiceTypeContactSensor and HMServiceTypeSwitch
 *
 *             For services of type HMServiceTypeOutlet and HMServiceTypeSwitch, serviceType can be one of the
 *             HomeKit Accessory Profile defined services (except HMServiceTypeOutlet or HMServiceTypeSwitch)
 *             that supports HMCharacteristicTypePowerState characteristic.
 *
 *             For services of type HMServiceTypeContactSensor, serviceType can be one of the following services:
 *                 HMServiceTypeDoor, HMServiceTypeGarageDoorOpener, HMServiceTypeWindow and HMServiceTypeWindowCovering
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateAssociatedServiceType:(nullable NSString *)serviceType completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCharacteristicWriteAction.h
//
//  HMCharacteristicWriteAction.h
//  HomeKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMAction.h>

NS_ASSUME_NONNULL_BEGIN

@class HMCharacteristic;

/*!
 * @brief This class is used to represent an entry in an action set that writes a specific
 *        value to a characteristic.
 */
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
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
                           targetValue:(TargetValueType)targetValue NS_DESIGNATED_INITIALIZER API_UNAVAILABLE(watchos, tvos);

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
- (void)updateTargetValue:(TargetValueType)targetValue completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMSignificantEvents.h
//
//  HMSignificantEvents.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief Type corresponding to significant events.
 */
typedef NSString * HMSignificantEvent NS_EXTENSIBLE_STRING_ENUM API_UNAVAILABLE(macos);

/*!
 * @brief Event corresponding to sunrise
 */
HM_EXTERN HMSignificantEvent const HMSignificantEventSunrise API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Event corresponding to sunset
 */
HM_EXTERN HMSignificantEvent const HMSignificantEventSunset API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_END


// ==========  HomeKit.framework/Headers/HMDurationEvent.h
//  HMDurationEvent.h
//  HomeKit
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMTimeEvent.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class is used to represent a duration of time.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos)
@interface HMDurationEvent : HMTimeEvent <NSCopying, NSMutableCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Creates a duration time event.
 *
 * @param duration The duration of time in seconds.
 *
 * @return Instance object representing the duration event.
 */
- (instancetype)initWithDuration:(NSTimeInterval)duration;

/*!
 * @brief duration The duration of time in seconds.
 */
@property(readonly, nonatomic, assign) NSTimeInterval duration;

@end


/*!
 * @brief This class is used to represent a duration of time.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos)
@interface HMMutableDurationEvent : HMDurationEvent

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief duration The duration of time in seconds.
 */
@property(readwrite, nonatomic, assign) NSTimeInterval duration;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMPresenceEvent.h
//  HMPresenceEvent.h
//  HomeKit
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMEvent.h>
#import <HomeKit/HMPresenceEventDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class is used to represent the presence of users in a home.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos)
@interface HMPresenceEvent : HMEvent <NSCopying, NSMutableCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Creates a presence based event.
 *
 * @param presenceEventType The event type desired for the event.
 *
 * @param presenceUserType The user type whose presence will trigger the event.
 *
 * @return Instance object representing the presence event.
 */
- (instancetype)initWithPresenceEventType:(HMPresenceEventType)presenceEventType presenceUserType:(HMPresenceEventUserType)presenceUserType;

/*!
 * @brief presenceEventType The event type that will trigger the event.
 */
@property(readonly, nonatomic) HMPresenceEventType presenceEventType;

/*!
 * @brief presenceUserType The user type whose presence will trigger the event.
 */
@property(readonly, nonatomic) HMPresenceEventUserType presenceUserType;

@end


/*!
 * @brief This class is used to represent the presence of users in a home.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos)
@interface HMMutablePresenceEvent : HMPresenceEvent

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief presenceEventType The event type that will trigger the event.
 */
@property(readwrite, nonatomic) HMPresenceEventType presenceEventType;

/*!
 * @brief presenceUserType The user type whose presence will trigger the event.
 */
@property(readwrite, nonatomic) HMPresenceEventUserType presenceUserType;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMActionSet.h
//
//  HMActionSet.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMAction;
@class HMCharacteristic;

/*!
 * @brief This class represents a collection of action objects that can be executed. 
 *        The order of execution of these actions is undefined.
 */             
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
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
 * @brief Specifies the action set type - user-defined, trigger-owned or one of the builtin types.
 *        Builtin action sets cannot be removed from the home. trigger-owned action sets cannot
 *        be executed, renamed or associated with another trigger.
 */
@property(readonly, copy, nonatomic) NSString *actionSetType API_AVAILABLE(ios(9.0));

/*!
 * @brief A unique identifier for the action set.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));

/*!
 * @brief Specifies the last execution date for the action set.
 */
@property(readonly, copy, nonatomic, nullable) NSDate *lastExecutionDate API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0));

/*!
 * @brief This method is used to change the name of the action set.
 *
 * @param name New name for the action set.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Adds an action to the action set.
 *
 * @param action Action object to add to the action set.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addAction:(HMAction *)action completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Removes an existing action from the action set.
 *
 * @param action Action object to remove from the action set.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeAction:(HMAction *)action completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end

/*!
 * @brief Builtin action set type for WakeUp.
 */

HM_EXTERN NSString * const HMActionSetTypeWakeUp API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Type for builtin action set Sleep.
 */
HM_EXTERN NSString * const HMActionSetTypeSleep API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Type for builtin action set HomeDeparture.
 */
HM_EXTERN NSString * const HMActionSetTypeHomeDeparture API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Type for builtin action set HomeArrival.
 */
HM_EXTERN NSString * const HMActionSetTypeHomeArrival API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Type for user-defined action sets.
 */
HM_EXTERN NSString * const HMActionSetTypeUserDefined API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Type for trigger-owned action sets.
 *
 * @discussion An action set of this type is owned by a trigger and is not listed
 *             as part of the home. An action set of this type cannot be executed,
 *             renamed, or associated with a different trigger.
 */
HM_EXTERN NSString * const HMActionSetTypeTriggerOwned API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HomeKit.h
//
//  HomeKit.h
//  HomeKit
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

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
#import <HomeKit/HMCalendarEvent.h>
#import <HomeKit/HMCalendarEvent.h>

#import <HomeKit/HMEventTrigger.h>
#import <HomeKit/HMError.h>
#import <HomeKit/HMAccessoryProfile.h>
#import <HomeKit/HMSignificantTimeEvent.h>
#import <HomeKit/HMDurationEvent.h>
#import <HomeKit/HMCharacteristicThresholdRangeEvent.h>
#import <HomeKit/HMPresenceEvent.h>
#import <HomeKit/HMNumberRange.h>
#import <HomeKit/HMEventTriggerActivationState.h>
#import <HomeKit/HMSignificantEvents.h>
#import <HomeKit/HMPresenceEventDefines.h>
#import <HomeKit/HMAccessorySetupPayload.h>

#import <HomeKit/HMCameraView.h>

#import <HomeKit/HMAccessory+Camera.h>
#import <HomeKit/HMCameraProfile.h>
#import <HomeKit/HMCameraControl.h>

#import <HomeKit/HMCameraStreamControl.h>
#import <HomeKit/HMCameraStream.h>

#import <HomeKit/HMCameraSnapshotControl.h>
#import <HomeKit/HMCameraSnapshot.h>

#import <HomeKit/HMCameraSettingsControl.h>
#import <HomeKit/HMCameraAudioControl.h>

// ==========  HomeKit.framework/Headers/HMCharacteristicThresholdRangeEvent.h
//
//  HMCharacteristicNumberRangeEvent.h
//  HomeKit
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMEvent.h>

NS_ASSUME_NONNULL_BEGIN

@class HMCharacteristic;
@class HMNumberRange;

/*!
 * @brief This class represents an event when a characteristic's value falls within the specified 
 * number range.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos)
@interface HMCharacteristicThresholdRangeEvent : HMEvent <NSCopying, NSMutableCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Initializes a new characteristic number range event object
 *
 * @param characteristic The characteristic bound to the event. The characteristic must
 *                       support notification. An exception will be thrown otherwise.
 *
 * @param numberRange The range for the characteristic value to trigger the event.
 *
 * @return Instance object representing the characteristic event.
 */
- (instancetype)initWithCharacteristic:(HMCharacteristic *)characteristic
                        thresholdRange:(HMNumberRange *)thresholdRange;

/*!
 * @brief The characteristic associated with the event.
 */
@property(readonly, strong, nonatomic) HMCharacteristic *characteristic;

/*!
 * @brief The range of the characteristic value that triggers the event.
 */
@property(readonly, copy, nonatomic) HMNumberRange *thresholdRange;

@end


/*!
 * @brief This class represents an event when a characteristic's value falls within the specified
 * number range.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos)
@interface HMMutableCharacteristicThresholdRangeEvent : HMCharacteristicThresholdRangeEvent

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief The characteristic associated with the event.
 */
@property(readwrite, strong, nonatomic) HMCharacteristic *characteristic;

/*!
 * @brief The range of the characteristic value that triggers the event.
 */
@property(readwrite, copy, nonatomic) HMNumberRange *thresholdRange;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMTimeEvent.h
//
//  HMTimeEvent.h
//  HomeKit
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMEvent.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class is used to represent a generic time event.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos)
@interface HMTimeEvent : HMEvent

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMAccessory.h
//
//  HMAccessory.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMHome;
@class HMRoom;
@class HMService;
@class HMCharacteristic;
@class HMAccessoryCategory;
@class HMAccessoryProfile;
@protocol HMAccessoryDelegate;

/*!
 * @abstract Represent an accessory in the home.
 *
 * @discussion This class represents an accessory in the home. There is a one to
 *             one relationship between a physical accessory and an object of this
 *             class. An accessory is composed of one or more services.
 */
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
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
@property(readonly, copy, nonatomic) NSUUID *identifier API_DEPRECATED("No longer supported.", ios(8.0, 9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief A unique identifier for the accessory.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));

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
@property(readonly, copy, nonatomic, nullable) NSArray<NSUUID *> *identifiersForBridgedAccessories API_DEPRECATED("No longer supported.", ios(8.0, 9.0)) API_UNAVAILABLE(watchos, tvos);

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
@property(readonly, copy, nonatomic, nullable) NSArray<NSUUID *> *uniqueIdentifiersForBridgedAccessories API_AVAILABLE(ios(9.0));

/*!
 * @brief Category information for the accessory. 
 */
@property(readonly, strong, nonatomic) HMAccessoryCategory *category API_AVAILABLE(ios(9.0));

/*!
 * @brief Room containing the accessory.
 */
@property(readonly, weak, nonatomic) HMRoom *room;

/*!
 * @brief Array of HMService objects that represent all the services provided by the accessory.
 */
@property(readonly, copy, nonatomic) NSArray<HMService *> *services;

/*!
 *  @abstract   Accessory profiles of the receiver.
 */
@property(readonly, copy) NSArray<HMAccessoryProfile *> *profiles API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 * @brief TRUE if the accessory is blocked, FALSE otherwise.
 */

@property(readonly, getter=isBlocked, nonatomic) BOOL blocked;

/*!
 *  @abstract   Model of the accessory.
 */
@property (nullable, readonly, copy, nonatomic) NSString *model API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 *  @abstract   Manufacturer of the accessory.
 */
@property (nullable, readonly, copy, nonatomic) NSString *manufacturer API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 *  @abstract   Accessory's firmware version.
 */
@property (nullable, readonly, copy, nonatomic) NSString *firmwareVersion API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 *  @abstract   Indicates if the accessory supports the identify action.
 */
@property (readonly) BOOL supportsIdentify API_AVAILABLE(ios(11.3), watchos(4.3), tvos(11.3));

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
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

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
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
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
 *  @abstract   Informs the delegate when a profile is added to an accessory.
 *
 *  @param      accessory   Sender of the message.
 *  @param      profile     The added profile.
 */
- (void)accessory:(HMAccessory *)accessory didAddProfile:(HMAccessoryProfile *)profile API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 *  @abstract   Informs the delegate when a profile is removed from an accessory.
 *
 *  @param      accessory   Sender of the message.
 *  @param      profile     The removed profile.
 */
- (void)accessory:(HMAccessory *)accessory didRemoveProfile:(HMAccessoryProfile *)profile API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 * @brief Informs the delegate when the reachability of the accessory changes.
 *
 * @param accessory Sender of the message.
 */
- (void)accessoryDidUpdateReachability:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate of a change in value of a characteristic. 
 *
 * @param accessory Sender of this message
 *
 * @param service HMService that contains the characteristic whose value was modified.
 *
 * @param characteristic The characteristic whose value was changed.
 */
- (void)accessory:(HMAccessory *)accessory service:(HMService *)service didUpdateValueForCharacteristic:(HMCharacteristic *)characteristic;

/*!
 * @brief Informs the delegate when firmwareVersion has been changed for an accessory.
 *
 * @param accessory Sender of the message.
 *
 * @param firmwareVersion The newly updated firmwareVersion.
 */
- (void)accessory:(HMAccessory *)accessory didUpdateFirmwareVersion:(NSString *)firmwareVersion API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

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
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
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

/*!
 * @brief The subset of valid values supported by the characteristic when the format is unsigned integral type.
 */
@property(readonly, copy, nonatomic, nullable) NSArray<NSNumber *> *validValues API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0));

@end

/*!
 * @group HMCharacteristicMetadataFormat constants
 */

/*!
 * @brief Describes that the value format is boolean.
 *
 * @discussion The value is an NSNumber containing the boolean value.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatBool API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is an integer.
 *
 * @discussion The value is an NSNumber containing a signed 32-bit integer with a range [-2147483648, 2147483647].
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatInt API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is a float.
 *
 * @discussion The value is an NSNumber containing a 32-bit float.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatFloat API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is a string.
 *
 * @discussion The value is an NSString.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatString API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is an array.
 *
 * @discussion The value is an NSArray.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatArray API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is a dictionary.
 *
 * @discussion The value is an NSDictionary.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatDictionary API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is an unsigned 8-bit integer.
 *
 * @discussion The value is an NSNumber containing an unsigned 8-bit integer with a range [0, 255].
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatUInt8 API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is an unsigned 16-bit integer.
 *
 * @discussion The value is an NSNumber containing an unsigned 16-bit integer with a range [0, 65535].
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatUInt16 API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is an unsigned 32-bit integer.
 *
 * @discussion The value is an NSNumber containing an unsigned 32-bit integer with a range [0, 4294967295].
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatUInt32 API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is an unsigned 64-bit integer.
 *
 * @discussion The value is an NSNumber containing an unsigned 64-bit integer with a range [0, 18446744073709551615].
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatUInt64 API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is a data blob.
 *
 * @discussion The value is an NSData containing the bytes of data.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatData API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the value format is a TLV8.
 *
 * @discussion The value is an NSData containing a set of one or more TLV8's, which are packed type-length-value items with an 8-bit type, 8-bit length, and N-byte value.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataFormatTLV8 API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);


/*!
 * @group HMCharacteristicMetadataUnits constants
 */

/*!
 * @brief Describes that the unit of the characteristic is in Celsius.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsCelsius API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the unit of the characteristic is in Fahrenheit.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsFahrenheit API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the unit of the characteristic is a percentage.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsPercentage API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the unit of the characteristic is arc degree.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsArcDegree API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the unit of the characteristic is seconds.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsSeconds API_AVAILABLE(ios(8.3), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the unit of the characteristic is Lux (illuminance).
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsLux API_AVAILABLE(ios(9.3), watchos(2.2), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the unit of the characteristic is parts per million.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsPartsPerMillion API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Describes that the unit of the characteristic is micrograms per cubic meter.
 */
HM_EXTERN NSString * const HMCharacteristicMetadataUnitsMicrogramsPerCubicMeter API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);


NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCameraSnapshotControl.h
//
//  HMCameraSnapshotControl.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMCameraControl.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMCameraSnapshot;
@protocol HMCameraSnapshotControlDelegate;

/*!
 * @abstract This class can be used to take an image snapshot from a camera.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos)
@interface HMCameraSnapshotControl : HMCameraControl

/*!
 * @brief Delegate that receives updates on the camera snapshot changes.
 */
@property(weak, nonatomic) id<HMCameraSnapshotControlDelegate> delegate;

/*!
 * @brief Represents the most recent snapshot taken from the camera.
 */
@property(readonly, strong, nonatomic, nullable) HMCameraSnapshot *mostRecentSnapshot;

/*!
 * @brief Takes an image snapshot.
 */
- (void)takeSnapshot;

@end


/*!
 * @brief This delegate receives updates on the camera snapshot.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos)
@protocol HMCameraSnapshotControlDelegate <NSObject>

@optional

/*!
 * @brief Informs the delegate that the snapshot was taken.
 *
 * @param cameraStreamControl Sender of this message.
 *
 * @param snapshot Snapshot will be valid if snapshot was successfully taken.
 *
 * @param error Error will be populated if the snapshot could not be taken.
 */
- (void)cameraSnapshotControl:(HMCameraSnapshotControl *)cameraSnapshotControl
              didTakeSnapshot:(HMCameraSnapshot *__nullable)snapshot
                        error:(NSError *__nullable)error;

/*!
 * @brief Informs the delegate that the mostRecentSnapshot was updated.
 *
 * @param cameraStreamControl Sender of this message.
 */
- (void)cameraSnapshotControlDidUpdateMostRecentSnapshot:(HMCameraSnapshotControl *)cameraSnapshotControl;

@end

NS_ASSUME_NONNULL_END

// ==========  HomeKit.framework/Headers/HMDefines.h
//
//  HMDefines.h
//  HomeKit
//
//      Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#ifndef HM_EXTERN
#ifdef __cplusplus
#define HM_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define HM_EXTERN   extern __attribute__((visibility ("default")))
#endif
#endif

// ==========  HomeKit.framework/Headers/HMAccessorySetupPayload.h
//
//  HMAccessorySetupPayload.h
//  HomeKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos, watchos, tvos) 
@interface HMAccessorySetupPayload : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Creates a new accessory setup payload to add an accessory to the home.
 *
 * @param setupPayloadURL The HomeKit setup payload for the accessory being added to the home.
 *
 * @return Returns an accessory setup payload object if successful or nil on error.
 */
- (instancetype)initWithURL:(NSURL *)setupPayloadURL;

@end
// ==========  HomeKit.framework/Headers/HMUser.h
//
//  HMUser.h
//  HomeKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMHomeAccessControl;

/*!
 * @brief This class describes a user in the home.
 */
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
@interface HMUser : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Name of the user.
 */
@property(readonly, copy, nonatomic) NSString *name;

/*!
 * @brief A unique identifier for the user.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCameraProfile.h
//
//  HMCameraProfile.h
//  HomeKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMAccessoryProfile.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMCameraStreamControl;
@class HMCameraSnapshotControl;
@class HMCameraSettingsControl;
@class HMCameraAudioControl;


/*!
 * @abstract Represents a camera profile the accessory implements.
 *
 * @discussion Provides an interface to interact with a Camera in an Accessory.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos)
@interface HMCameraProfile : HMAccessoryProfile

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Object that can be used to control the camera stream.
 */
@property(readonly, strong, nonatomic, nullable) HMCameraStreamControl *streamControl;

/*!
 * @brief Object that can be used to take image snapshots from the camera.
 */
@property(readonly, strong, nonatomic, nullable) HMCameraSnapshotControl *snapshotControl;

/*!
 * @brief Object that can be used to control the settings on the camera.
 */
@property(readonly, strong, nonatomic, nullable) HMCameraSettingsControl *settingsControl;

/*!
 * @brief Object that can be used to control the speaker settings on the camera.
 */
@property(readonly, strong, nonatomic, nullable) HMCameraAudioControl *speakerControl;

/*!
 * @brief Object that can be used to control the microphone settings on the camera.
 */
@property(readonly, strong, nonatomic, nullable) HMCameraAudioControl *microphoneControl;

@end


NS_ASSUME_NONNULL_END

// ==========  HomeKit.framework/Headers/HMHome.h
//
//  HMHome.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

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
@class HMAccessorySetupPayload;

@protocol HMHomeDelegate;

/*!
 @enum      HMHomeHubState

 @constant  HMHomeHubStateNotAvailable      No home hub is present.
 @constant  HMHomeHubStateConnected         Home hub is connected.
 @constant  HMHomeHubStateDisconnected      No home hub is connected.
 */
typedef NS_ENUM(NSUInteger, HMHomeHubState)
{
    HMHomeHubStateNotAvailable = 0,
    HMHomeHubStateConnected,
    HMHomeHubStateDisconnected
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Represents a home.
 *
 * @discussion This class represents a home and is the entry point to communicate and
 *             configure different accessories in the home. This is also used to manage
 *             all the rooms, zones, service groups, users, triggers, and action sets in
 *             the home.
 */
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
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
 * @brief Specifies the state of the home hub.
 */
@property(readonly, nonatomic) HMHomeHubState homeHubState API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

/*!
 * @brief A unique identifier for the home.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));

/*!
 * @brief This method is used to change the name of the home.
 *
 * @param name New name for the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

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
- (void)addAccessory:(HMAccessory *)accessory completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Removes an accessory from the home.
 *
 * @param accessory Accessory to remove from the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeAccessory:(HMAccessory *)accessory completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

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
- (void)assignAccessory:(HMAccessory *)accessory toRoom:(HMRoom *)room completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

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
- (void)unblockAccessory:(HMAccessory *)accessory completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Find nearby accessories and add them to the home. During this process, each of the accessories added
 *        to the home is assigned to a room and its services are configured.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addAndSetupAccessoriesWithCompletionHandler:(void (^)(NSError * __nullable error))completion API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Add accessory with the given setup payload to the home.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   Accessories provides the list of added accessories.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addAndSetupAccessoriesWithPayload:(HMAccessorySetupPayload *)payload completionHandler:(void (^)(NSArray<HMAccessory *>* __nullable accessories, NSError * __nullable error))completion API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(watchos, tvos);

@end


@interface HMHome(HMUser)

/*!
 * @brief HMUser object representing the current user of the home.
 */
@property(readonly, strong, nonatomic) HMUser *currentUser API_AVAILABLE(ios(9.0));

/*!
 * @brief Array of HMUser objects that represent all users associated with the home.
 */
@property(readonly, copy, nonatomic) NSArray<HMUser *> *users API_DEPRECATED("No longer supported.", ios(8.0, 9.0)) API_UNAVAILABLE(watchos, tvos);

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
- (void)manageUsersWithCompletionHandler:(void (^)(NSError * __nullable error))completion API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Adds a user to the home.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The HMUser object provides a reference to the user that was added to the home.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success. The userInfo dictionary will contain the HMUserFailedAccessoriesKey which provides
 *                   more details on the accessories that failed to add the user.
 */
- (void)addUserWithCompletionHandler:(void (^)(HMUser * __nullable user, NSError * __nullable error))completion API_DEPRECATED_WITH_REPLACEMENT("-manageUsersWithCompletionHandler:", ios(8.0, 9.0)) API_UNAVAILABLE(macos, watchos, tvos);

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
- (void)removeUser:(HMUser *)user completionHandler:(void (^)(NSError * __nullable error))completion API_DEPRECATED_WITH_REPLACEMENT("-manageUsersWithCompletionHandler:", ios(8.0, 9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @brief Retrieve the access level of the user associated with the home.
 */
- (HMHomeAccessControl *)homeAccessControlForUser:(HMUser *)user API_AVAILABLE(ios(9.0));

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
- (void)addRoomWithName:(NSString *)roomName completionHandler:(void (^)(HMRoom * __nullable room, NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

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
- (void)removeRoom:(HMRoom *)room completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

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
- (void)addZoneWithName:(NSString *)zoneName completionHandler:(void (^)(HMZone * __nullable zone, NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Removes a zone from the home.
 *
 * @param zone Zone to remove from the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeZone:(HMZone *)zone completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

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
- (void)addServiceGroupWithName:(NSString *)serviceGroupName completionHandler:(void (^)(HMServiceGroup * __nullable group, NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Removes a service group from the home.
 *
 * @param group Service group to remove from the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeServiceGroup:(HMServiceGroup *)group completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

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
- (void)addActionSetWithName:(NSString *)actionSetName completionHandler:(void (^)(HMActionSet * __nullable actionSet, NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Removes an existing action set from the home.
 *
 * @param actionSet Action set to remove from the home. A builtin action set cannot be removed.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeActionSet:(HMActionSet *)actionSet completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

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
 * @param actionSetType Type of the builtin action set. Supported action set types are HMActionSetTypeWakeUp,
 *                      HMActionSetTypeSleep, HMActionSetTypeHomeDeparture and HMActionSetTypeHomeArrival.
 *
 * @return Reference to the built-in action set corresponding to type argument,
 *         nil if no matching action set is found.
 */
- (nullable HMActionSet *)builtinActionSetOfType:(NSString *)actionSetType API_AVAILABLE(ios(9.0));

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
- (void)addTrigger:(HMTrigger *)trigger completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Removes a trigger from the home. If the trigger is active, they are automatically deactivated.
 *
 * @param trigger Trigger to remove from the home.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeTrigger:(HMTrigger *)trigger completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end


/*!
 * @brief This delegate receives update on the various accessories, action sets, groups and triggers 
 *        managed in the home.
 */
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
@protocol HMHomeDelegate <NSObject>

@optional

/*!
 * @brief Informs the delegate of a change in the name of a home.
 *
 * @param home Sender of this message.
 */
- (void)homeDidUpdateName:(HMHome *)home;

/*!
 * @brief Informs the delegate when the access control for current user has been updated.
 *
 * @param home Sender of the message.
 */
- (void)homeDidUpdateAccessControlForCurrentUser:(HMHome *)home API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

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

/*!
 * @brief Informs the delegate when state of the home hub changes.
 *
 * @param home Sender of the message.
 *
 * @param homeHubState The new home hub state.
 */
- (void)home:(HMHome *)home didUpdateHomeHubState:(HMHomeHubState)homeHubState API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

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
HM_EXTERN NSString * const HMUserFailedAccessoriesKey API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCharacteristic.h
//
//  HMCharacteristic.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

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
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
@interface HMCharacteristic : NSObject

/*!
 * @brief The type of the characteristic, e.g. HMCharacteristicTypePowerState.
 */
@property(readonly, copy, nonatomic) NSString *characteristicType;

/*!
 * @brief The localized description of the characteristic.
 */
@property(readonly, copy, nonatomic) NSString *localizedDescription API_AVAILABLE(ios(9.0));

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
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));


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
 * @param enable A Boolean value indicating whether you wish to receive notifications or
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
- (void)updateAuthorizationData:(nullable NSData *)data completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCameraSnapshot.h
//
//  HMCameraSnapshot.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMCameraSource.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract Represents a camera snapshot.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos)
@interface HMCameraSnapshot : HMCameraSource

/*!
 * @brief Time corresponding to the snapshot request.
 */
@property(readonly, copy, nonatomic) NSDate *captureDate;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMSignificantTimeEvent.h
//  HMSignificantTimeEvent.h
//  HomeKit
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMTimeEvent.h>
#import <HomeKit/HMSignificantEvents.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class is used to represent a significant time event.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos)
@interface HMSignificantTimeEvent : HMTimeEvent <NSCopying, NSMutableCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Creates a significant time event.
 *
 * @param significantEvent The significant event for the trigger.
 *
 * @param offset An offset from the time of the signficant event. To specify an offset before the significant event, the
 *               properties of the NSDateComponents must be negative value. e.g. To specify 30 mins before sunset, the
 *               'minute' property must be set to -30.
 *
 * @return Instance object representing the significant event.
 */
- (instancetype)initWithSignificantEvent:(HMSignificantEvent)significantEvent
                                  offset:(nullable NSDateComponents *)offset;

/*!
 * @brief significantEvent The significant event for the trigger.
 */
@property(readonly, strong, nonatomic) HMSignificantEvent significantEvent;

/*!
 * @param offset An offset from the time of the signficant event. To specify an offset before the significant event, the
 *               properties of the NSDateComponents must be negative value. e.g. To specify 30 mins before sunset, the
 *               'minute' property must be set to -30.
 */
@property(readonly, strong, nonatomic, nullable) NSDateComponents *offset;

@end




/*!
 * @brief This class is used to represent a significant time event.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos)
@interface HMMutableSignificantTimeEvent : HMSignificantTimeEvent

/*!
 * @brief significantEvent The significant event for the trigger.
 */
@property(readwrite, strong, nonatomic) HMSignificantEvent significantEvent;

/*!
 * @param offset An offset from the time of the signficant event. To specify an offset before the significant event, the
 *               properties of the NSDateComponents must be negative value. e.g. To specify 30 mins before sunset, the
 *               'minute' property must be set to -30.
 */
@property(readwrite, strong, nonatomic) NSDateComponents *offset;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCameraControl.h
//
//  HMCameraControl.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract Represents a generic camera control.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos)
@interface HMCameraControl : NSObject

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCameraView.h
//
//  HMCameraView.h
//  HomeKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

#if __has_include(<UIKit/UIView.h>)

@class HMCameraSource;

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract This view can render a camera source.
 */

API_AVAILABLE(ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos)
@interface HMCameraView : UIView

/*!
 * @brief Represents the camera source.
 */
@property (strong, nonatomic, nullable) HMCameraSource *cameraSource;

@end

NS_ASSUME_NONNULL_END

#endif
// ==========  HomeKit.framework/Headers/HMCameraStreamControl.h
//
//  HMCameraStreamControl.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <HomeKit/HMDefines.h>
#import <HomeKit/HMCameraControl.h>
#import <HomeKit/HMCameraDefines.h>

#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@protocol HMCameraStreamControlDelegate;
@class HMCameraStream;

/*!
 * @abstract This class can be used to control the stream from a camera.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos)
@interface HMCameraStreamControl : HMCameraControl

/*!
 * @brief Delegate that receives updates on the camera stream changes.
 */
@property(weak, nonatomic) id<HMCameraStreamControlDelegate> delegate;

/*!
 * @brief Represents the current streaming state.
 */
@property(readonly, assign, nonatomic) HMCameraStreamState streamState;

/*!
 * @brief Represents the current camera stream.
 */
@property(readonly, strong, nonatomic, nullable) HMCameraStream *cameraStream;

/*!
 * @brief Starts the camera stream. 'currentCameraStream' will be updated upon 
 *        successfully starting the stream.
 */
- (void)startStream;

/*!
 * @brief Stops the camera stream.
 * */
- (void)stopStream;

@end

/*!
 * @brief This delegate receives updates on the camera stream.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos)
@protocol HMCameraStreamControlDelegate <NSObject>

@optional

/*!
 * @brief Informs the delegate that the stream has started.
 *
 * @param cameraStreamControl Sender of this message.
 */
- (void)cameraStreamControlDidStartStream:(HMCameraStreamControl *)cameraStreamControl;

/*!
 * @brief Informs the delegate that the stream has stopped.
 *
 * @param cameraStreamControl Sender of this message.
 *
 * @param error When stream stops because of an error, 'error' will be populated.
 */
- (void)cameraStreamControl:(HMCameraStreamControl *)cameraStreamControl didStopStreamWithError:(NSError *__nullable)error;

@end

NS_ASSUME_NONNULL_END

// ==========  HomeKit.framework/Headers/HMTimerTrigger.h
//
//  HMTimerTrigger.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMTrigger.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief Timer based trigger.
 *
 * @discussion This class represents a trigger that is based on timers.
 */
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
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
          recurrenceCalendar:(nullable NSCalendar *)recurrenceCalendar NS_DESIGNATED_INITIALIZER API_UNAVAILABLE(watchos, tvos);

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
- (void)updateFireDate:(NSDate *)fireDate completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

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
- (void)updateTimeZone:(nullable NSTimeZone *)timeZone completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

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
- (void)updateRecurrence:(nullable NSDateComponents *)recurrence
       completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMCalendarEvent.h
//  HMCalendarEvent.h
//  HomeKit
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMTimeEvent.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class is used to represent a calendar event.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos)
@interface HMCalendarEvent : HMTimeEvent <NSCopying, NSMutableCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Creates a calendar event
 *
 * @param fireDateComponents The date component that specifies the time when the event is fired
 *
 * @return Instance object representing the event trigger.
 */
- (instancetype)initWithFireDateComponents:(NSDateComponents *)fireDateComponents;


/*!
 * @brief The date component that specifies the time when the event is fired
 */
@property(readonly, strong, nonatomic) NSDateComponents *fireDateComponents;

@end





/*!
 * @brief This class is used to represent a calendar event.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos)
@interface HMMutableCalendarEvent : HMCalendarEvent

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief The date component that specifies the time when the event is fired
 */
@property(readwrite, strong, nonatomic) NSDateComponents *fireDateComponents;

@end

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMEventTriggerActivationState.h
//
//  HMEventTriggerActivationState.h
//  HomeKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract This enumeration describes the current activation state of the event trigger.
 */
API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos)
typedef NS_ENUM(NSUInteger, HMEventTriggerActivationState)
{
    /*!
     * Trigger is not active because it is disabled
     */
    HMEventTriggerActivationStateDisabled = 0,
    
    /*!
     * Trigger is not active because there is no HomeHub
     */
    HMEventTriggerActivationStateDisabledNoHomeHub = 1,
    
    /*!
     * Trigger is not active because there is no compatible HomeHub
     */
    HMEventTriggerActivationStateDisabledNoCompatibleHomeHub = 2,
    
    /*!
     * Trigger is not active because Location Authorization has been turned off by user
     */
    HMEventTriggerActivationStateDisabledNoLocationServicesAuthorization = 3,
    
    /*!
     * Trigger is currently active
     */
    HMEventTriggerActivationStateEnabled = 4,
};

NS_ASSUME_NONNULL_END


// ==========  HomeKit.framework/Headers/HMHomeManager.h
//
//  HMHomeManager.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

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
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
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
- (void)updatePrimaryHome:(HMHome *)home completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

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
- (void)addHomeWithName:(NSString *)homeName completionHandler:(void (^)(HMHome * __nullable home, NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Removes an existing home from the collection.
 *
 * @param home Home object that needs to be removed from the collection.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeHome:(HMHome *)home completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end

/*!
 * @brief This delegate receives updates on homes being managed via the home manager.
 */
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
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
HM_EXTERN NSString * const HMServiceTypeLightbulb API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for switch.
 */
HM_EXTERN NSString * const HMServiceTypeSwitch API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for thermostat.
 */
HM_EXTERN NSString * const HMServiceTypeThermostat API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for garage door opener.
 */
HM_EXTERN NSString * const HMServiceTypeGarageDoorOpener API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for accessory information.
 */
HM_EXTERN NSString * const HMServiceTypeAccessoryInformation API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for fan.
 */
HM_EXTERN NSString * const HMServiceTypeFan API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for outlet.
 */
HM_EXTERN NSString * const HMServiceTypeOutlet API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for lock mechanism.
 */
HM_EXTERN NSString * const HMServiceTypeLockMechanism API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for lock management.
 */
HM_EXTERN NSString * const HMServiceTypeLockManagement API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for air quality sensor.
 */
HM_EXTERN NSString * const HMServiceTypeAirQualitySensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for battery.
 */
HM_EXTERN NSString * const HMServiceTypeBattery API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for carbon dioxide sensor.
 */
HM_EXTERN NSString * const HMServiceTypeCarbonDioxideSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for carbon monoxide sensor.
 */
HM_EXTERN NSString * const HMServiceTypeCarbonMonoxideSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for contact sensor.
 */
HM_EXTERN NSString * const HMServiceTypeContactSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for door.
 */
HM_EXTERN NSString * const HMServiceTypeDoor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for doorbell.
 */
HM_EXTERN NSString * const HMServiceTypeDoorbell API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for humidity sensor.
 */
HM_EXTERN NSString * const HMServiceTypeHumiditySensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for leak sensor.
 */
HM_EXTERN NSString * const HMServiceTypeLeakSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for light sensor.
 */
HM_EXTERN NSString * const HMServiceTypeLightSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for motion sensor.
 */
HM_EXTERN NSString * const HMServiceTypeMotionSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for occupancy sensor.
 */
HM_EXTERN NSString * const HMServiceTypeOccupancySensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for security system.
 */
HM_EXTERN NSString * const HMServiceTypeSecuritySystem API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for stateful programmable switch.
 */
HM_EXTERN NSString * const HMServiceTypeStatefulProgrammableSwitch API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for stateless programmable switch.
 */
HM_EXTERN NSString * const HMServiceTypeStatelessProgrammableSwitch API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for smoke sensor.
 */
HM_EXTERN NSString * const HMServiceTypeSmokeSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for temperature sensor.
 */
HM_EXTERN NSString * const HMServiceTypeTemperatureSensor API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for window.
 */
HM_EXTERN NSString * const HMServiceTypeWindow API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for window covering.
 */
HM_EXTERN NSString * const HMServiceTypeWindowCovering API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for stream management.
 */
HM_EXTERN NSString * const HMServiceTypeCameraRTPStreamManagement API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for camera control.
 */
HM_EXTERN NSString * const HMServiceTypeCameraControl API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for microphone.
 */
HM_EXTERN NSString * const HMServiceTypeMicrophone API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for speaker.
 */
HM_EXTERN NSString * const HMServiceTypeSpeaker API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for air purifier.
 */
HM_EXTERN NSString * const HMServiceTypeAirPurifier API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for ventilation fan.
 */
HM_EXTERN NSString * const HMServiceTypeVentilationFan API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for filter maintenance.
 */
HM_EXTERN NSString * const HMServiceTypeFilterMaintenance API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for heater/cooler.
 */
HM_EXTERN NSString * const HMServiceTypeHeaterCooler API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for humidifier/dehumidifier.
 */
HM_EXTERN NSString * const HMServiceTypeHumidifierDehumidifier API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for slats.
 */
HM_EXTERN NSString * const HMServiceTypeSlats API_AVAILABLE(ios(10.2), watchos(3.1.1), tvos(10.1)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for label namespace when accessory supports multiple services of the same type.
 */
HM_EXTERN NSString * const HMServiceTypeLabel API_AVAILABLE(ios(10.3), watchos(3.2), tvos(10.2)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for irrigation system.
 */
HM_EXTERN NSString * const HMServiceTypeIrrigationSystem API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for valve.
 */
HM_EXTERN NSString * const HMServiceTypeValve API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) API_UNAVAILABLE(macos);

/*!
 * @brief Service type for faucet.
 */
HM_EXTERN NSString * const HMServiceTypeFaucet API_AVAILABLE(ios(11.2), watchos(4.2), tvos(11.2)) API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_END
// ==========  HomeKit.framework/Headers/HMTrigger.h
//
//  HMTrigger.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

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
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0)) API_UNAVAILABLE(macos)
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
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));

/*!
 * @brief This method is used to change the name of the trigger.
 *
 * @param name New name for the trigger.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief Registers an action set to be executed when the trigger is fired.
 *
 * @param actionSet HMActionSet to execute when the trigger fires. The order of execution of the
 *                  action set is not guaranteed.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request.
 */
- (void)addActionSet:(HMActionSet *)actionSet completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 * @brief De-registers an action set from the trigger.
 *
 * @param actionSet The HMActionSet to disassociate from the trigger. 
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request.
 */
- (void)removeActionSet:(HMActionSet *)actionSet completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

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
- (void)enable:(BOOL)enable completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
