// ==========  HealthKit.framework/Headers/HKQuantity.h
//
//  HKQuantity.h
//  HealthKit
//
//  Copyright (c) 2013-2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HKUnit;

/*!
 @class         HKQuantity
 @abstract      The HKQuantity class provides an encapsulation of a quantity value and the unit of measurement.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKQuantity : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 @method        quantityWithUnit:doubleValue:
 @abstract      Returns a new object representing a quantity measurement with the given unit.
 */
+ (instancetype)quantityWithUnit:(HKUnit *)unit doubleValue:(double)value;

/*!
 @method        isCompatibleWithUnit:
 @abstract      Returns yes if the receiver's value can be converted to a value of the given unit.
 */
- (BOOL)isCompatibleWithUnit:(HKUnit *)unit;

/*!
 @method        doubleValueForUnit:
 @abstract      Returns the quantity value converted to the given unit.
 @discussion    Throws an exception if the receiver's value cannot be converted to one of the requested unit.
 */
- (double)doubleValueForUnit:(HKUnit *)unit;

/*!
 @method        compare:
 @abstract      Returns an NSComparisonResult value that indicates whether the receiver is greater than, equal to, or 
                less than a given quantity.
 @discussion    Throws an exception if the unit of the given quantity is not compatible with the receiver's unit.
 */
- (NSComparisonResult)compare:(HKQuantity *)quantity;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKMetadata.h
//
//  HKMetadata.h
//  HealthKit
//
//  Copyright (c) 2013-2018 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @constant      HKMetadataKeyUDIProductionIdentifier
 @abstract      Represents the serial number of the device that created the HKObject.
 @discussion    The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyDeviceSerialNumber API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyBodyTemperatureSensorLocation
 @abstract      Represents the location where a particular body temperature reading was taken.
 @discussion    The expected value type is an NSNumber containing a HKBodyTemperatureSensorLocation value.
 */
HK_EXTERN NSString * const HKMetadataKeyBodyTemperatureSensorLocation API_AVAILABLE(ios(8.0), watchos(2.0));

typedef NS_ENUM(NSInteger, HKBodyTemperatureSensorLocation) {
    HKBodyTemperatureSensorLocationOther = 0,
    HKBodyTemperatureSensorLocationArmpit,
    HKBodyTemperatureSensorLocationBody,
    HKBodyTemperatureSensorLocationEar,
    HKBodyTemperatureSensorLocationFinger,
    HKBodyTemperatureSensorLocationGastroIntestinal,
    HKBodyTemperatureSensorLocationMouth,
    HKBodyTemperatureSensorLocationRectum,
    HKBodyTemperatureSensorLocationToe,
    HKBodyTemperatureSensorLocationEarDrum,
    HKBodyTemperatureSensorLocationTemporalArtery,
    HKBodyTemperatureSensorLocationForehead,
} API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyHeartRateSensorLocation
 @abstract      Represents the location where a particular heart rate reading was taken.
 @discussion    The expected value type is an NSNumber containing a HKHeartRateSensorLocation value.
 */
HK_EXTERN NSString * const HKMetadataKeyHeartRateSensorLocation API_AVAILABLE(ios(8.0), watchos(2.0));

typedef NS_ENUM(NSInteger, HKHeartRateSensorLocation) {
    HKHeartRateSensorLocationOther = 0,
    HKHeartRateSensorLocationChest,
    HKHeartRateSensorLocationWrist,
    HKHeartRateSensorLocationFinger,
    HKHeartRateSensorLocationHand,
    HKHeartRateSensorLocationEarLobe,
    HKHeartRateSensorLocationFoot,
} API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyHeartRateMotionContext
 @abstract      Represents the context in which a particular heart rate reading was taken.
 @discussion    The expected value type is an NSNumber containing a HKHeartRateMotionContext value. The value is active
                (HKHeartRateMotionContextActive) if the user is in motion or working out, sedentary if the user is
                still (HKHeartRateMotionContextSedentary), or not set (HKHeartRateMotionContextNotSet) otherwise.
 */
HK_EXTERN NSString * const HKMetadataKeyHeartRateMotionContext API_AVAILABLE(ios(11.0), watchos(4.0));

typedef NS_ENUM(NSInteger, HKHeartRateMotionContext) {
    HKHeartRateMotionContextNotSet = 0,
    HKHeartRateMotionContextSedentary,
    HKHeartRateMotionContextActive,
} API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @constant      HKMetadataKeyFoodType
 @abstract      Represents the type of food that was consumed when creating an HKObject.
 @discussion    This should be a short string representing the type of food, such as 'Banana'. The expected value type
                is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyFoodType API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyUDIDeviceIdentifier
 @abstract      Represents the device identifier portion of a device's UDI (Unique Device Identifier).
 @discussion    The device identifier can be used to reference the GUDID (Globally Unique Device Identifier Database).
                The expected value type is NSString.
 
                ** Note that the use of this key is now discouraged in favor of the HKDevice class.
 */
HK_EXTERN NSString * const HKMetadataKeyUDIDeviceIdentifier API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyUDIProductionIdentifier
 @abstract      Represents the production identifier portion of a device's UDI (Unique Device Identifier).
 @discussion    While part of a device's UDI, the production identifier is not saved in the FDA's GUDID 
                (Globally Unique Device Identifier Database) and its use in HealthKit is now discouraged for
                user privacy reasons. Apps should consider handling this independently of HealthKit APIs if
                needed.
                The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyUDIProductionIdentifier API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyDigitalSignature
 @abstract      Represents a digital signature validating the origin of an HKObject's value.
 @discussion    Intended to provide data integrity for sample data produced by trusted (tamper resistant) measuring devices.
                The digital signature format should be CMS (Cryptographic Message Syntax specified in IETF RFC 5652).
                It should be a “Signed-data” type signature containing the data items to be signed (e.g., timestamp, value, etc.)
                using ASN.1 encoding with DER (Distinguished Encoding Rules). The entire enveloping signature should be further
                encoded using base64. Recommended digest is SHA256, and recommended cipher is FIPS PUB 186-4 Digital Signature 
                Standard Elliptic Curve P-256. See documentation for details.

 */
HK_EXTERN NSString * const HKMetadataKeyDigitalSignature API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyExternalUUID
 @abstract      Represents a unique identifier for an HKObject that is set by its source.
                Uniqueness of objects with the same value of this key is not enforced by HealthKit.
 @discussion    The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyExternalUUID API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @constant      HKMetadataKeySyncIdentifier
 @abstract      Represents an identifier for an HKObject that is set by its source and is used by HealthKit to uniquely
                identify an object.
 @discussion    Saving a HKObject with a HKMetadataKeySyncIdentifier will replace an existing HKObject with the
                same HKMetadataKeySyncIdentifier value if the new HKObject has a greater HKMetadataKeySyncVersion.
                The new sample will be added to all HKWorkouts or HKCorrelations containing the replaced sample.
                HKMetadataKeySyncVersion must be provided if HKMetadataKeySyncIdentifier is provided.
                The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeySyncIdentifier API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @constant      HKMetadataKeySyncVersion
 @abstract      Represents the version of the HKObject that is set by its source and is used by HealthKit to identify an
                object's version.
 @discussion    HKMetadataKeySyncVersion may not be provided if HKMetadataKeySyncIdentifier is not provided.
                The expected value type is NSNumber.
 */
HK_EXTERN NSString * const HKMetadataKeySyncVersion API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @constant      HKMetadataKeyTimeZone
 @abstract      Represents the time zone that the user was in when the HKObject was created.
 @discussion    The expected value type is an NSString compatible with NSTimeZone's +timeZoneWithName:.
 */
HK_EXTERN NSString * const HKMetadataKeyTimeZone API_AVAILABLE(ios(8.0), watchos(2.0));


/*!
 @constant      HKMetadataKeyDeviceName
 @abstract      Represents the name of the device that took the reading.
 @discussion    The expected value type is NSString.
 
                ** Note that the use of this key is now discouraged in favor of the HKDevice class.
 */
HK_EXTERN NSString * const HKMetadataKeyDeviceName API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyDeviceManufacturerName
 @abstract      Represents the name of the manufacturer of the device that took the reading.
 @discussion    The expected value type is NSString.
 
                ** Note that the use of this key is now discouraged in favor of the HKDevice class.
 */
HK_EXTERN NSString * const HKMetadataKeyDeviceManufacturerName API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyWasTakenInLab
 @abstract      Represents whether or not the reading was taken in a lab.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyWasTakenInLab API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyReferenceRangeLowerLimit
 @abstract      Represents the lower limit of the reference range for a lab result.
 @discussion    The expected value type is an NSNumber.
 */
HK_EXTERN NSString * const HKMetadataKeyReferenceRangeLowerLimit API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyReferenceRangeUpperLimit
 @abstract      Represents the upper limit of the reference range for a lab result.
 @discussion    The expected value type is an NSNumber.
 */
HK_EXTERN NSString * const HKMetadataKeyReferenceRangeUpperLimit API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyWasUserEntered
 @abstract      Represents whether or not the reading was entered by the user.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyWasUserEntered API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyWorkoutBrandName
 @abstract      Represents the brand name of a particular workout.
 @discussion    The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyWorkoutBrandName API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyGroupFitness
 @abstract      Represents whether or not a workout was performed as part of a group fitness class.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyGroupFitness API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyIndoorWorkout
 @abstract      Represents whether or not a workout was performed indoors as opposed to outdoors.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyIndoorWorkout API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyCoachedWorkout
 @abstract      Represents whether or not a workout was performed with a coach or personal trainer.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyCoachedWorkout API_AVAILABLE(ios(8.0), watchos(2.0));

typedef NS_ENUM(NSInteger, HKWeatherCondition) {
    HKWeatherConditionNone = 0,
    HKWeatherConditionClear,
    HKWeatherConditionFair,
    HKWeatherConditionPartlyCloudy,
    HKWeatherConditionMostlyCloudy,
    HKWeatherConditionCloudy,
    HKWeatherConditionFoggy,
    HKWeatherConditionHaze,
    HKWeatherConditionWindy,
    HKWeatherConditionBlustery,
    HKWeatherConditionSmoky,
    HKWeatherConditionDust,
    HKWeatherConditionSnow,
    HKWeatherConditionHail,
    HKWeatherConditionSleet,
    HKWeatherConditionFreezingDrizzle,
    HKWeatherConditionFreezingRain,
    HKWeatherConditionMixedRainAndHail,
    HKWeatherConditionMixedRainAndSnow,
    HKWeatherConditionMixedRainAndSleet,
    HKWeatherConditionMixedSnowAndSleet,
    HKWeatherConditionDrizzle,
    HKWeatherConditionScatteredShowers,
    HKWeatherConditionShowers,
    HKWeatherConditionThunderstorms,
    HKWeatherConditionTropicalStorm,
    HKWeatherConditionHurricane,
    HKWeatherConditionTornado,
} API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @constant      HKMetadataKeyWeatherCondition
 @abstract      Represents the weather condition during the sample.
 @discussion    The expected value type is an NSNumber containing an HKWeatherCondition value. This key may be set on an
                HKWorkout object to represent the overall weather condition during the workout.
 */
HK_EXTERN NSString * const HKMetadataKeyWeatherCondition API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @constant      HKMetadataKeyWeatherTemperature
 @abstract      Represents the weather temperature during the sample.
 @discussion    The expected value type is an HKQuantity expressed in a temperature unit. This key may be set on an
                HKWorkout object to represent the overall temperature during the workout.
 */
HK_EXTERN NSString * const HKMetadataKeyWeatherTemperature API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @constant      HKMetadataKeyHumidity
 @abstract      Represents the weather humidity during the sample.
 @discussion    The expected value type is an HKQuantity expressed in percent. This key may be set on an HKWorkout
                object to represent the overall humidity during the workout.
 */
HK_EXTERN NSString * const HKMetadataKeyWeatherHumidity API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @constant      HKMetadataKeySexualActivityProtectionUsed
 @abstract      Represents whether or not protection was used during sexual activity. This can be used to track either
                protection from STIs or protection from pregnancy.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeySexualActivityProtectionUsed API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyMenstrualCycleStart
 @abstract      Indicates whether or not the sample represents the start of a menstrual cycle. This is a required
                metadata key for category samples of type HKCategoryTypeIdentifierMenstrualFlow.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyMenstrualCycleStart API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @constant      HKMetadataKeyLapLength
 @abstract      Represents the length of a lap recorded during a workout.
 @discussion    The expected value type is an HKQuantity object compatible with a length unit. This key may be set on an
                HKWorkout object to represent the length of a lap.
 */
HK_EXTERN NSString * const HKMetadataKeyLapLength API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @enum          HKWorkoutSwimmingLocationType
 @abstract      This enumerated type is used to represent the location type of a swimming workout.
 @discussion    This value indicates whether a swimming workout was performed in a pool or open water.
 */
typedef NS_ENUM(NSInteger, HKWorkoutSwimmingLocationType) {
    HKWorkoutSwimmingLocationTypeUnknown = 0,
    HKWorkoutSwimmingLocationTypePool,
    HKWorkoutSwimmingLocationTypeOpenWater,
} API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @constant      HKMetadataKeySwimmingLocationType
 @abstract      Represents the location type of a swimming workout.
 @discussion    The expected value type is an NSNumber containing an HKWorkoutSwimmingLocationType value. This key may
                be set on an HKWorkout object to represent the swimming location type.
 */
HK_EXTERN NSString * const HKMetadataKeySwimmingLocationType API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @enum          HKSwimmingStrokeStyle
 @abstract      Represents a style of stroke used during a swimming workout.
 */
typedef NS_ENUM(NSInteger, HKSwimmingStrokeStyle) {
    HKSwimmingStrokeStyleUnknown = 0,
    HKSwimmingStrokeStyleMixed,
    HKSwimmingStrokeStyleFreestyle,
    HKSwimmingStrokeStyleBackstroke,
    HKSwimmingStrokeStyleBreaststroke,
    HKSwimmingStrokeStyleButterfly,
} API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @constant      HKMetadataKeySwimmingStrokeStyle
 @abstract      Represents the predominant stroke style during a lap of a swimming workout.
 @discussion    The expected value type is an NSNumber containing an HKSwimmingStrokeStyle value. This key may be set on
                an HKWorkoutEvent object with the type HKWorkoutEventTypeLap to represent the predominant style used
                during the lap.
 */
HK_EXTERN NSString * const HKMetadataKeySwimmingStrokeStyle API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @enum          HKInsulinDeliveryReason
 @abstract      Represents a medical reason for the delivery of insulin
 
 @constant      HKInsulinDeliveryReasonBasal  Delivery for the base metabolic needs of the individual, often
                                              administered as a continuous rate from an insulin pump, or a periodic
                                              injection of slow-acting insulin.
 @constant      HKInsulinDeliveryReasonBolus  Delivery for the episodic needs of the individual, such as a meal or
                                              glucose level correction.
 */

typedef NS_ENUM(NSInteger, HKInsulinDeliveryReason) {
    HKInsulinDeliveryReasonBasal = 1,
    HKInsulinDeliveryReasonBolus,
} API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @constant      HKMetadataKeyInsulinDeliveryReason
 @abstract      Represents the medical reason for the delivery of an insulin dose. This is a required metadata key for
                samples of type HKQuantityTypeIdentifierInsulinDelivery.
 @discussion    The expected value type is an NSNumber containing a HKInsulinDeliveryReason value.
 */
HK_EXTERN NSString * const HKMetadataKeyInsulinDeliveryReason API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @enum          HKBloodGlucoseMealTime
 @abstract      Indicates how your blood glucose reading relates to a meal.

 @constant      HKBloodGlucoseMealTimePreprandial   A glucose value measured at the time just before a meal.
 @constant      HKBloodGlucoseMealTimePostprandial  A glucose value measured after a meal.
 */
typedef NS_ENUM(NSInteger, HKBloodGlucoseMealTime) {
    HKBloodGlucoseMealTimePreprandial = 1,
    HKBloodGlucoseMealTimePostprandial,
} API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @constant      HKMetadataKeyBloodGlucoseMealTime
 @abstract      Indicates the relative timing of a blood glucose reading to a meal.
 @discussion    This timing, as well as other factors like meal composition, can be used by medical professionals to
                determine the acceptable value range for a blood glucose reading. For use cases requiring the capture of
                precise timing and composition information, developers should record additional dietary samples, such as
                HKQuantityTypeIdentifierDietaryCarbohydrates. The expected value type is an NSNumber containing a
                HKBloodGlucoseMealTime value.
 */
HK_EXTERN NSString * const HKMetadataKeyBloodGlucoseMealTime API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @enum          HKVO2MaxTestType
 @abstract      Represents the test used to create a VO2 Max Sample.
 
 @constant      HKVO2MaxTestTypeMaxExercise               A user is exerted to their physical limit to evaluate and
                                                          measure actual VO2Max.
 @constant      HKVO2MaxTestTypePredictionSubMaxExercise  A specific test protocol is used to calculate and correlate a
                                                          predicted VO2Max.
 @constant      HKVO2MaxTestTypePredictionNonExercise     A non-exercise equation is used based on user metrics to
                                                          calculate a predicted VO2Max.
 */
typedef NS_ENUM(NSInteger, HKVO2MaxTestType) {
    HKVO2MaxTestTypeMaxExercise = 1,
    HKVO2MaxTestTypePredictionSubMaxExercise,
    HKVO2MaxTestTypePredictionNonExercise,
} API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @constant      HKMetadataKeyVO2MaxTestType
 @abstract      Represents the test used to create VO2 Max Sample
 @discussion    The expected value type is an NSNumber containing a HKVO2MaxTestType value.
 */
HK_EXTERN NSString * const HKMetadataKeyVO2MaxTestType API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @constant      HKMetadataKeyAverageSpeed
 @abstract      Represents the average speed for a workout segment or distance sample.
 @discussion    This represents the average speed when moving so it may not match the value of distance/time for a
 distance sample.
 
 The expected value type is an HKQuantity object compatible with a speed unit (e.g. m/s). This key may be
 set on quantity samples of type HKQuantityTypeIdentifierDistanceDownhillSnowSports or a workout segment
 representing a skiing run.
 */
HK_EXTERN NSString * const HKMetadataKeyAverageSpeed API_AVAILABLE(ios(11.2), watchos(4.2));

/*!
 @constant      HKMetadataKeyMaximumSpeed
 @abstract      Represents the maximum speed for a workout segment or distance sample.
 @discussion    The expected value type is an HKQuantity object compatible with a speed unit (e.g. m/s). This key may be
 set on quantity samples of type HKQuantityTypeIdentifierDistanceDownhillSnowSports or a workout segment
 representing a skiing run.
 */
HK_EXTERN NSString * const HKMetadataKeyMaximumSpeed API_AVAILABLE(ios(11.2), watchos(4.2));

/*!
 @constant      HKMetadataKeyAlpineSlopeGrade
 @abstract      Represents the grade of a ski run.
 @discussion    Alpine slope grade is measured in percent where 100% grade is a 45 degree slope.
 
 The expected value type is an HKQuantity object compatible with percent unit. This key may be set on
 quantity samples of type HKQuantityTypeIdentifierDistanceDownhillSnowSports or a workout segment
 representing a skiing run.
 */
HK_EXTERN NSString * const HKMetadataKeyAlpineSlopeGrade API_AVAILABLE(ios(11.2), watchos(4.2));

/*!
 @constant      HKMetadataKeyElevationAscended
 @abstract      Represents the cumulative elevation ascent during a workout.
 @discussion    The expected value type is an HKQuantity object compatible with length unit. This key may be set on a
 workout, workout segments or distance samples.
 */
HK_EXTERN NSString * const HKMetadataKeyElevationAscended API_AVAILABLE(ios(11.2), watchos(4.2));

/*!
 @constant      HKMetadataKeyElevationDescended
 @abstract      Represents the cumulative elevation descent during a workout.
 @discussion    The expected value type is an HKQuantity object compatible with length unit. This key may be set on a
 workout, workout segments or distance samples.
 */
HK_EXTERN NSString * const HKMetadataKeyElevationDescended API_AVAILABLE(ios(11.2), watchos(4.2));

/*!
 @constant      HKMetadataKeyFitnessMachineDuration
 @abstract      Represents the workout duration as displayed by a GymKit connected fitness machine.
 @discussion    The expected value type is an HKQuantity object compatible with a time unit. This key may be set on an
                HKWorkout object to represent the duration of the workout as displayed by a GymKit connected fitness
                machine.
 */
HK_EXTERN NSString * const HKMetadataKeyFitnessMachineDuration API_AVAILABLE(ios(12.0), watchos(5.0));

/*!
 @constant      HKMetadataKeyIndoorBikeDistance
 @abstract      Represents the distance covered during an indoor bike workout.
 @discussion    The expected value type is an HKQuantity object compatible with a length unit. This key may be set on an
                HKWorkout object to represent the distance covered during an indoor bike workout.
 */
HK_EXTERN NSString * const HKMetadataKeyIndoorBikeDistance API_AVAILABLE(ios(12.0), watchos(5.0));

/*!
 @constant      HKMetadataKeyCrossTrainerDistance
 @abstract      Represents the distance covered during a cross trainer workout.
 @discussion    The expected value type is an HKQuantity object compatible with a length unit. This key may be set on an
                HKWorkout object to represent the distance covered during a cross trainer workout.
 */
HK_EXTERN NSString * const HKMetadataKeyCrossTrainerDistance API_AVAILABLE(ios(12.0), watchos(5.0));

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKSeriesBuilder.h
//
//  HKSeriesBuilder.h
//  HealthKit
//
//  Copyright (c) 2015 Apple. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKSeriesBuilder
 @abstract      An HKSeriesBuilder is an abstract class for generating HKSeriesSample objects. 
                Concrete subclasses generate the actual HKSeriesSample objects.
 */
HK_EXTERN
@interface HKSeriesBuilder : NSObject

/*!
 @method        discard
 @abstract      Stop series generation and discard all collected data.
 @discussion    This method informs the receiver that no more data should be collected and all
                previously collected data should be deleted and the receiver will be considered
                invalid. Any further calls to the receiver will result in an exception.
 */
- (void)discard;


/*!
 @method        init
 @abstract      Use only subclass initializer methods.
 */
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HealthKit.h
//
//  HealthKit.h
//  HealthKit
//
//  Copyright (c) 2013-2018 Apple Inc. All rights reserved.
//

#import <HealthKit/HKActivitySummary.h>
#import <HealthKit/HKActivitySummaryQuery.h>
#import <HealthKit/HKAnchoredObjectQuery.h>
#import <HealthKit/HKCDADocumentSample.h>
#import <HealthKit/HKCategorySample.h>
#import <HealthKit/HKCharacteristicObjects.h>
#import <HealthKit/HKClinicalRecord.h>
#import <HealthKit/HKClinicalType.h>
#import <HealthKit/HKCorrelation.h>
#import <HealthKit/HKCorrelationQuery.h>
#import <HealthKit/HKCumulativeQuantitySeriesSample.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKDeletedObject.h>
#import <HealthKit/HKDevice.h>
#import <HealthKit/HKDocumentQuery.h>
#import <HealthKit/HKDocumentSample.h>
#import <HealthKit/HKFHIRResource.h>
#import <HealthKit/HKHealthStore.h>
#import <HealthKit/HKLiveWorkoutBuilder.h>
#import <HealthKit/HKLiveWorkoutDataSource.h>
#import <HealthKit/HKMetadata.h>
#import <HealthKit/HKObject.h>
#import <HealthKit/HKObjectType.h>
#import <HealthKit/HKObserverQuery.h>
#import <HealthKit/HKQuantity.h>
#import <HealthKit/HKQuantitySample.h>
#import <HealthKit/HKQuantitySeriesSampleBuilder.h>
#import <HealthKit/HKQuantitySeriesSampleQuery.h>
#import <HealthKit/HKQuery.h>
#import <HealthKit/HKSample.h>
#import <HealthKit/HKSampleQuery.h>
#import <HealthKit/HKSeriesBuilder.h>
#import <HealthKit/HKSeriesSample.h>
#import <HealthKit/HKSource.h>
#import <HealthKit/HKSourceQuery.h>
#import <HealthKit/HKSourceRevision.h>
#import <HealthKit/HKStatistics.h>
#import <HealthKit/HKStatisticsCollectionQuery.h>
#import <HealthKit/HKStatisticsQuery.h>
#import <HealthKit/HKTypeIdentifiers.h>
#import <HealthKit/HKUnit.h>
#import <HealthKit/HKWorkout.h>
#import <HealthKit/HKWorkoutBuilder.h>
#import <HealthKit/HKWorkoutConfiguration.h>
#import <HealthKit/HKWorkoutRoute.h>
#import <HealthKit/HKWorkoutRouteBuilder.h>
#import <HealthKit/HKWorkoutRouteQuery.h>
#import <HealthKit/HKWorkoutSession.h>
// ==========  HealthKit.framework/Headers/HKHealthStore.h
//
//  HKHealthStore.h
//  HealthKit
//
//  Copyright (c) 2013-2018 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>
#import <HealthKit/HKCharacteristicObjects.h>

NS_ASSUME_NONNULL_BEGIN

@class HKDevice;
@class HKObject;
@class HKObjectType;
@class HKQuantity;
@class HKQuantityType;
@class HKQuery;
@class HKSample;
@class HKSampleType;
@class HKSource;
@class HKSourceRevision;
@class HKUnit;
@class HKWorkout;
@class HKWorkoutBuilder;
@class HKWorkoutConfiguration;
@class HKWorkoutSession;

/*!
 @class         HKHealthStore
 @abstract      The HKHealthStore class provides an interface for accessing and storing the user's health data.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKHealthStore : NSObject

/*!
 @method        isHealthDataAvailable
 @abstract      Returns YES if HealthKit is supported on the device.
 @discussion    HealthKit is not supported on all iOS devices.  Using HKHealthStore APIs on devices which are not
                supported will result in errors with the HKErrorHealthDataUnavailable code.  Call isHealthDataAvailable
                before attempting to use other parts of the framework.
 */
+ (BOOL)isHealthDataAvailable;

/*!
 @method        supportsHealthRecords
 @abstract      Returns YES if the Health Records feature is available.
 @discussion    The Health Records feature is not available in all regions but may be present in unsupported regions
                if accounts have already been configured. This can change as accounts are modified during device
                restore or synchronization.
                Call supportsHealthRecords before attempting to request authorization for any clinical types.
 */
- (BOOL)supportsHealthRecords API_AVAILABLE(ios(12.0)) __WATCHOS_PROHIBITED;

/*!
 @method        authorizationStatusForType:
 @abstract      Returns the application's authorization status for the given object type.
 */
- (HKAuthorizationStatus)authorizationStatusForType:(HKObjectType *)type;

/*!
 @method        requestAuthorizationToShareTypes:readTypes:completion:
 @abstract      Prompts the user to authorize the application for reading and saving objects of the given types.
 @discussion    Before attempting to execute queries or save objects, the application should first request authorization
                from the user to read and share every type of object for which the application may require access.
 
                The request is performed asynchronously and its completion will be executed on an arbitrary background
                queue after the user has responded.  If the user has already chosen whether to grant the application
                access to all of the types provided, then the completion will be called without prompting the user.
                The success parameter of the completion indicates whether prompting the user, if necessary, completed
                successfully and was not cancelled by the user.  It does NOT indicate whether the application was
                granted authorization.
 
                To customize the messages displayed on the authorization sheet, set the following keys in your app's
                Info.plist file. Set the NSHealthShareUsageDescription key to customize the message for reading data.
                Set the NSHealthUpdateUsageDescription key to customize the message for writing data.
 */
- (void)requestAuthorizationToShareTypes:(nullable NSSet<HKSampleType *> *)typesToShare
                               readTypes:(nullable NSSet<HKObjectType *> *)typesToRead
                              completion:(void (^)(BOOL success, NSError * _Nullable error))completion;

/*!
 @method        getRequestStatusForAuthorizationToShareTypes:readTypes:completion:
 @abstract      Determines whether requesting authorization for the given types is necessary.
 @discussion    Applications may call this method to determine whether the user would be prompted for authorization if
                the same collections of types are passed to requestAuthorizationToShareTypes:readTypes:completion:.
                This determination is performed asynchronously and its completion will be executed on an arbitrary
                background queue.
 */
- (void)getRequestStatusForAuthorizationToShareTypes:(NSSet<HKSampleType *> *)typesToShare
                                           readTypes:(NSSet<HKObjectType *> *)typesToRead
                                          completion:(void (^)(HKAuthorizationRequestStatus requestStatus, NSError * _Nullable error))completion API_AVAILABLE(ios(12.0), watchos(5.0));

/*!
 @method        handleAuthorizationForExtensionWithCompletion:
 @abstract      Prompts the user to authorize the application for reading and saving objects.
 @discussion    When an app extension calls requestAuthorizationToShareTypes:readTypes:completion:, the parent application
                is responsible for calling this method to prompt the user to authorize the app and its extensions for the
                types that the extension requested access to.
 
                The request is performed asynchronously and its completion will be executed on an arbitrary background
                queue after the user has responded.  The success parameter of the completion indicates whether prompting
                the user, if necessary, completed successfully and was not cancelled by the user.  It does NOT indicate
                whether the application was granted authorization.
 */
- (void)handleAuthorizationForExtensionWithCompletion:(void (^)(BOOL success, NSError * _Nullable error))completion API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos) NS_EXTENSION_UNAVAILABLE("Not available to extensions");

/*!
 @method        earliestPermittedSampleDate
 @abstract      Samples prior to the earliestPermittedSampleDate cannot be saved or queried.
 @discussion    On some platforms, only samples with end dates newer than the value returned by earliestPermittedSampleDate
                may be saved or retrieved.
 */
- (NSDate *)earliestPermittedSampleDate API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @method        saveObject:withCompletion:
 @abstract      Saves an HKObject.
 @discussion    After an object is saved, on subsequent retrievals the sourceRevision property of the object will be set
                to the HKSourceRevision representing the version of the application that saved it.
 
                If the object has an HKObjectType property, then in order to save an object successfully the application
                must first request authorization to share objects with that type.  Saving an object with the same unique
                identifier as another object that has already been saved will fail.  When the application attempts to
                save multiple objects, if any single object cannot be saved then none of the objects will be saved.
                The operation will fail if the objects array contains samples with endDates that are older than the date
                returned by earliestPermittedSampleDate.
 
                This operation is performed asynchronously and the completion will be executed on an arbitrary
                background queue.
 */
- (void)saveObject:(HKObject *)object withCompletion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*!
 @method        saveObjects:withCompletion:
 @abstract      Saves an array of HKObjects.
 @discussion    See discussion of saveObject:withCompletion:.
 */
- (void)saveObjects:(NSArray<HKObject *> *)objects withCompletion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*!
 @method        deleteObject:withCompletion:
 @abstract      Deletes a single HKObject from the HealthKit database.
 @discussion    See deleteObjects:withCompletion:.
 */
- (void)deleteObject:(HKObject *)object withCompletion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*!
 @method        deleteObjects:withCompletion:
 @abstract      Deletes multiple HKObjects from the HealthKit database.
 @discussion    An application may only delete objects that it previously saved.  This operation is performed
                asynchronously and the completion will be executed on an arbitrary background queue.
 */
- (void)deleteObjects:(NSArray<HKObject *> *)objects withCompletion:(void(^)(BOOL success, NSError * _Nullable error))completion API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @method        deleteObjectsOfType:predicate:withCompletion:
 @abstract      Deletes all objects matching the given predicate from the HealthKit database.
 @discussion    An application may only delete objects that it previously saved.  This operation is performed
                asynchronously and the completion will be executed on an arbitrary background queue.
 */
- (void)deleteObjectsOfType:(HKObjectType *)objectType predicate:(NSPredicate *)predicate withCompletion:(void(^)(BOOL success, NSUInteger deletedObjectCount, NSError * _Nullable error))completion API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @method        executeQuery:
 @abstract      Begins executing the given query.
 @discussion    After executing a query, the completion, update, and/or results handlers of that query will be invoked
                asynchronously on an arbitrary background queue as results become available.  Errors that prevent a
                query from executing will be delivered to one of the query's handlers.  Which handler the error will be
                delivered to is defined by the HKQuery subclass.  
 
                Each HKQuery instance may only be executed once and calling this method with a currently executing query
                or one that was previously executed will result in an exception.
                
                If a query would retrieve objects with an HKObjectType property, then the application must request
                authorization to access objects of that type before executing the query.
 */
- (void)executeQuery:(HKQuery *)query;

/*!
 @method        stopQuery:
 @abstract      Stops a query that is executing from continuing to run.
 @discussion    Calling this method will prevent the handlers of the query from being invoked in the future.  If the
                query is already stopped, this method does nothing.
 */
- (void)stopQuery:(HKQuery *)query;

/*!
 @method        splitTotalEnergy:startDate:endDate:resultsHandler:
 @abstract      For the time period specified, this method calculates the resting and active energy parts of the total
                energy provided.
 @discussion    This method uses the user's metrics like age, biological sex, body mass and height to determine
                their basal metabolic rate. If the application does not have authorization to access these characteristics
                or if the user has not entered their data then this method uses builtin default values.
 */
- (void)splitTotalEnergy:(HKQuantity *)totalEnergy
               startDate:(NSDate *)startDate
                 endDate:(NSDate *)endDate
          resultsHandler:(void(^)(HKQuantity * _Nullable restingEnergy, HKQuantity * _Nullable activeEnergy, NSError * _Nullable error))resultsHandler API_DEPRECATED("No longer supported", ios(9.0, 11.0), watchos(2.0, 4.0));

- (nullable NSDate *)dateOfBirthWithError:(NSError **)error API_DEPRECATED_WITH_REPLACEMENT("dateOfBirthComponentsWithError:", ios(8.0, 10.0), watchos(2.0, 3.0));

/*!
 @method        dateOfBirthComponentsWithError:
 @abstract      Returns the user's date of birth in the Gregorian calendar.
 @discussion    Before calling this method, the application should request authorization to access objects with the
                HKCharacteristicType identified by HKCharacteristicTypeIdentifierDateOfBirth.
 */
- (nullable NSDateComponents *)dateOfBirthComponentsWithError:(NSError **)error API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @method        biologicalSexWithError:
 @abstract      Returns an object encapsulating the user's biological sex.
 @discussion    Before calling this method, the application should request authorization to access objects with the
                HKCharacteristicType identified by HKCharacteristicTypeIdentifierBiologicalSex.
 */
- (nullable HKBiologicalSexObject *)biologicalSexWithError:(NSError **)error;

/*!
 @method        bloodTypeWithError:
 @abstract      Returns an object encapsulating the user's blood type.
 @discussion    Before calling this method, the application should request authorization to access objects with the
                HKCharacteristicType identified by HKCharacteristicTypeIdentifierBloodType.
 */
- (nullable HKBloodTypeObject *)bloodTypeWithError:(NSError **)error;

/*!
 @method        fitzpatrickSkinTypeWithError:
 @abstract      Returns an object encapsulating the user's Fitzpatrick skin type.
 @discussion    Before calling this method, the application should request authorization to access objects with the
                HKCharacteristicType identified by HKCharacteristicTypeIdentifierFitzpatrickSkinType.
 */
- (nullable HKFitzpatrickSkinTypeObject *)fitzpatrickSkinTypeWithError:(NSError **)error API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @method        wheelchairUseWithError:
 @abstract      Returns an object encapsulating the user's wheelchair use.
 @discussion    Before calling this method, the application should request authorization to access objects with the
                HKCharacteristicType identified by HKCharacteristicTypeIdentifierWheelchairUse.
 */
- (nullable HKWheelchairUseObject *)wheelchairUseWithError:(NSError **)error API_AVAILABLE(ios(10.0), watchos(3.0));

@end

@interface HKHealthStore (HKWorkout)

/*!
 @method        addSamples:toWorkout:completion:
 @abstract      Associates samples with a given workout.
 @discussion    This will associate the given samples with the given workout. These samples will then be returned by a
                query that contains this workout as a predicate. If a sample is added that is not saved yet, then it will
                be saved for you. Note that the sample will be saved without an HKDevice.
 
                The workout provided must be one that has already been saved to HealthKit.
 */
- (void)addSamples:(NSArray<HKSample *> *)samples toWorkout:(HKWorkout *)workout completion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*!
 @method        startWorkoutSession:
 @abstract      Starts the given workout session.
 @discussion    This method will asynchronously begin a workout session. The methods on the session's delegate will be 
                called when the session has successfully started or fails to start.
 */
- (void)startWorkoutSession:(HKWorkoutSession *)workoutSession API_DEPRECATED("Use HKWorkoutSession's start method", watchos(2.0, 5.0)) __IOS_PROHIBITED;

/*!
 @method        endWorkoutSession:
 @abstract      Ends the given workout session.
 @discussion    This method will end the given session if it is currently running. The state of the workout session will
                transition to HKWorkoutSessionStateEnded. Once a workout session is ended, it cannot be reused to start
                a new workout session.
 */
- (void)endWorkoutSession:(HKWorkoutSession *)workoutSession API_DEPRECATED("Use HKWorkoutSession's end method", watchos(2.0, 5.0)) __IOS_PROHIBITED;

/*!
 @method        pauseWorkoutSession:
 @abstract      Pauses the given workout session.
 @discussion    This method will pause the given session if it is currently running. The state of the workout session
                will transition to HKWorkoutSessionStatePaused. An HKWorkoutEventTypePause will be generated and
                delivered to the workout session's delegate.
 */
- (void)pauseWorkoutSession:(HKWorkoutSession *)workoutSession API_DEPRECATED("Use HKWorkoutSession's pause method", watchos(2.0, 5.0)) __IOS_PROHIBITED;

/*!
 @method        resumeWorkoutSession:
 @abstract      Resumes the given workout session.
 @discussion    This method will resume the given session if it is currently paused. The state of the workout session
                will transition to HKWorkoutSessionStateRunning. An HKWorkoutEventTypeResume will be generated and
                delivered to the workout session's delegate.
 */
- (void)resumeWorkoutSession:(HKWorkoutSession *)workoutSession API_DEPRECATED("Use HKWorkoutSession's resume method", watchos(2.0, 5.0)) __IOS_PROHIBITED;

/*!
 @method        startWatchAppWithWorkoutConfiguration:completion:
 @abstract      Launches or wakes up the WatchKit app on the watch
 @discussion    This method will launch the WatchKit app corresponding to the calling iOS application on the currently
                active Apple Watch. After launching, the handleWorkoutConfiguration: method on the WKExtensionDelegate
                protocol will be called with the HKWorkoutConfiguration as a parameter. The receiving Watch app can use
                this configuration object to create an HKWorkoutSession and start it with -startWorkoutSession:.
 */
- (void)startWatchAppWithWorkoutConfiguration:(HKWorkoutConfiguration *)workoutConfiguration completion:(void (^)(BOOL success, NSError * _Nullable error))completion API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos);

/*!
 @method        recoverActiveWorkoutSessionWithCompletion:
 @abstract      Recovers an active workout session after a client crash. If no session is available to be re-attached,
                nil will be returned. If an error occurs, session will be nil and error will be set appropriately.
 */
- (void)recoverActiveWorkoutSessionWithCompletion:(void (^)(HKWorkoutSession * _Nullable session, NSError * _Nullable error))completion API_AVAILABLE(watchos(5.0)) __IOS_PROHIBITED;

@end


@interface HKHealthStore (HKBackgroundDelivery)

/*!
 @method        enableBackgroundDeliveryForType:frequency:withCompletion:
 @abstract      This method enables activation of your app when data of the type is recorded at the cadence specified.
 @discussion    When an app has subscribed to a certain data type it will get activated at the cadence that is specified
                with the frequency parameter. The app is still responsible for creating an HKObserverQuery to know which
                data types have been updated and the corresponding fetch queries. Note that certain data types (such as
                HKQuantityTypeIdentifierStepCount) have a minimum frequency of HKUpdateFrequencyHourly. This is enforced
                transparently to the caller.
 */
- (void)enableBackgroundDeliveryForType:(HKObjectType *)type frequency:(HKUpdateFrequency)frequency withCompletion:(void(^)(BOOL success, NSError * _Nullable error))completion __WATCHOS_PROHIBITED;

- (void)disableBackgroundDeliveryForType:(HKObjectType *)type withCompletion:(void(^)(BOOL success, NSError * _Nullable error))completion __WATCHOS_PROHIBITED;

- (void)disableAllBackgroundDeliveryWithCompletion:(void(^)(BOOL success, NSError * _Nullable error))completion __WATCHOS_PROHIBITED;

@end

/*!
 @constant      HKUserPreferencesDidChangeNotification
 @abstract      A notification posted every time the user updates their preferred units.
 @discussion    Each HKHealthStore posts a HKUserPreferencesDidChangeNotification notification when the preferred unit
                for a HKQuantityType is changed by the user. To guarantee your listener will only receive a single
                notification when this occurs, it is necessary to provide an HKHealthStore instance for the object
                parameter of NSNotificationCenter's addObserver methods.
 */
HK_EXTERN NSString * const HKUserPreferencesDidChangeNotification API_AVAILABLE(ios(8.2), watchos(2.0));

@interface HKHealthStore (HKUserPreferences)

/*!
 @method        preferredUnitsForQuantityTypes:completion:
 @abstract      Calls the completion with the preferred HKUnits for a given set of HKQuantityTypes.
 @discussion    A preferred unit is either the unit that the user has chosen in Health for displaying samples of the
                given quantity type or the default unit for that type in the current locale of the device. To access the
                user's preferences it is necessary to request read or share authorization for the set of HKQuantityTypes
                provided. If neither read nor share authorization has been granted to the app, then the default unit for
                the locale is provided.
 
                An error will be returned when preferred units are inaccessible because protected health data is
                unavailable or authorization status is not determined for one or more of the provided types.
 
                The returned dictionary will map HKQuantityType to HKUnit.
 */
- (void)preferredUnitsForQuantityTypes:(NSSet<HKQuantityType *> *)quantityTypes completion:(void(^)(NSDictionary<HKQuantityType *, HKUnit *> *preferredUnits, NSError * _Nullable error))completion API_AVAILABLE(ios(8.2), watchos(2.0));

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKObject.h
//
//  HKObject.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class HKSource;
@class HKSourceRevision;
@class HKDevice;

HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKObject : NSObject <NSSecureCoding>

/*!
 @property      UUID
 @abstract      A unique identifier of the receiver in the HealthKit database.
 */
@property (readonly, strong) NSUUID *UUID;

@property (readonly, strong) HKSource *source API_DEPRECATED_WITH_REPLACEMENT("sourceRevision", ios(8.0, 9.0));

/*!
 @property      sourceRevision
 @abstract      Represents the revision of the source responsible for saving the receiver.
 */
@property (readonly, strong) HKSourceRevision *sourceRevision API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @property      device
 @abstract      Represents the device that generated the data of the receiver.
 */
@property (readonly, strong, nullable) HKDevice *device API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @property      metadata
 @abstract      Extra information describing properties of the receiver.
 @discussion    Keys must be NSString and values must be either NSString, NSNumber, NSDate, or
                HKQuantity. See HKMetadata.h for potential metadata keys and values.
 */
@property (readonly, copy, nullable) NSDictionary<NSString *, id> *metadata;

- (instancetype)init NS_UNAVAILABLE;

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathUUID API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKPredicateKeyPathSource API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKPredicateKeyPathMetadata API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKPredicateKeyPathCorrelation API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkout API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKPredicateKeyPathDevice API_AVAILABLE(ios(9.0), watchos(2.0));
HK_EXTERN NSString * const HKPredicateKeyPathSourceRevision API_AVAILABLE(ios(9.0), watchos(2.0));

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKUnit.h
//
//  HKUnit.h
//  HealthKit
//
//  Copyright (c) 2013-2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKUnit : NSObject <NSSecureCoding, NSCopying>

/// Returns a unique string representation for the unit that could be used with +unitFromString:
@property (readonly, strong) NSString *unitString;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)unitFromString:(NSString *)string;

// Unit strings are composed of the following units:
// International System of Units (SI) units:
// g                (grams)   [Mass]
// m                (meters)  [Length]
// L,l              (liters)  [Volume]
// Pa               (pascals) [Pressure]
// s                (seconds) [Time]
// J                (joules)  [Energy]
// K                (kelvin)  [Temperature]
// S                (siemens) [Electrical Conductance]
// Hz               (hertz)   [Frequency]
// mol<molar mass>  (moles)   [Mass] <molar mass> is the number of grams per mole. For example, mol<180.1558>

// SI units can be prefixed as follows:
// da   (deca-)   = 10                 d    (deci-)   = 1/10
// h    (hecto-)  = 100                c    (centi-)  = 1/100
// k    (kilo-)   = 1000               m    (milli-)  = 1/1000
// M    (mega-)   = 10^6               mc   (micro-)  = 10^-6
// G    (giga-)   = 10^9               n    (nano-)   = 10^-9
// T    (tera-)   = 10^12              p    (pico-)   = 10^-12


// Non-SI units:
//
// [Mass]
// oz   (ounces)  = 28.3495 g                           
// lb   (pounds)  = 453.592 g                           
// st   (stones)  = 6350.0 g
//
// [Length]
// in   (inches)  = 0.0254 m                            
// ft   (feet)    = 0.3048 m                            
// mi   (miles)   = 1609.34 m                           
//
// [Pressure]
// mmHg (millimeters of mercury) = 133.3224 Pa          
// cmAq (centimeters of water)   = 98.06650 Pa
// atm  (atmospheres)            = 101325.0 Pa
//
// [Volume]
// fl_oz_us  (US customary fluid ounces)= 0.0295735295625 L
// fl_oz_imp (Imperial fluid ounces)    = 0.0284130625 L
// pt_us     (US customary pint)        = 0.473176473 L
// pt_imp    (Imperial pint)            = 0.56826125 L
// cup_us    (US customary cup)         = 0.2365882365 L
// cup_imp   (Imperial cup)             = 0.284130625 L

// [Time]
// min  (minutes) = 60 s
// hr   (hours)   = 3600 s
// d    (days)    = 86400 s
//
// [Energy]
// cal  (calories)     = 4.1840 J
// kcal (kilocalories) = 4184.0 J
//
// [Temperature]
// degC (degrees Celsius)    = 1.0 K - 273.15
// degF (degrees Fahrenheit) = 1.8 K - 459.67
//
// [Conductance]
// S    (siemens)
//
// [Pharmacology]
// IU   (international unit)
//
// [Scalar]
// count = 1
// %     = 1/100
//

// Units can be combined using multiplication (. or *) and division (/), and raised to integral powers (^).
// For simplicity, only a single '/' is allowed in a unit string, and multiplication is evaluated first.
// So "kg/m.s^2" is equivalent to "kg/(m.s^2)" and "kg.m^-1.s^-2".

// The following methods convert between HKUnit and Foundation formatter units for mass, length and energy.
// When converting from Foundation formatter unit to HKUnit, if there's not a match, nil will be returned.
// When converting from HKUnit to the Foundation formatter unit, if there's not a match, an exception will be thrown.
+ (instancetype)unitFromMassFormatterUnit:(NSMassFormatterUnit)massFormatterUnit;
+ (NSMassFormatterUnit)massFormatterUnitFromUnit:(HKUnit *)unit;

+ (instancetype)unitFromLengthFormatterUnit:(NSLengthFormatterUnit)lengthFormatterUnit;
+ (NSLengthFormatterUnit)lengthFormatterUnitFromUnit:(HKUnit *)unit;

+ (instancetype)unitFromEnergyFormatterUnit:(NSEnergyFormatterUnit)energyFormatterUnit;
+ (NSEnergyFormatterUnit)energyFormatterUnitFromUnit:(HKUnit *)unit;

- (BOOL)isNull;

@end

typedef NS_ENUM(NSInteger, HKMetricPrefix) {
    HKMetricPrefixNone = 0, //10^0
    
    HKMetricPrefixPico,     //10^-12
    HKMetricPrefixNano,     //10^-9
    HKMetricPrefixMicro,    //10^-6
    HKMetricPrefixMilli,    //10^-3
    HKMetricPrefixCenti,    //10^-2
    HKMetricPrefixDeci,     //10^-1
    HKMetricPrefixDeca,     //10^1
    HKMetricPrefixHecto,    //10^2
    HKMetricPrefixKilo,     //10^3
    HKMetricPrefixMega,     //10^6
    HKMetricPrefixGiga,     //10^9
    HKMetricPrefixTera      //10^12
} API_AVAILABLE(ios(8.0), watchos(2.0));

/* Mass Units */
@interface HKUnit (Mass)
+ (instancetype)gramUnitWithMetricPrefix:(HKMetricPrefix)prefix;       // g
+ (instancetype)gramUnit;   // g
+ (instancetype)ounceUnit;  // oz
+ (instancetype)poundUnit;  // lb
+ (instancetype)stoneUnit;  // st
+ (instancetype)moleUnitWithMetricPrefix:(HKMetricPrefix)prefix molarMass:(double)gramsPerMole;   // mol<double>
+ (instancetype)moleUnitWithMolarMass:(double)gramsPerMole; // mol<double>
@end

/* Length Units */
@interface HKUnit (Length)
+ (instancetype)meterUnitWithMetricPrefix:(HKMetricPrefix)prefix;      // m
+ (instancetype)meterUnit;  // m
+ (instancetype)inchUnit;   // in
+ (instancetype)footUnit;   // ft
+ (instancetype)yardUnit API_AVAILABLE(ios(9.0), watchos(2.0));   // yd
+ (instancetype)mileUnit;   // mi
@end

/* Volume Units */
@interface HKUnit (Volume)
+ (instancetype)literUnitWithMetricPrefix:(HKMetricPrefix)prefix;      // L
+ (instancetype)literUnit;              // L
+ (instancetype)fluidOunceUSUnit;       // fl_oz_us
+ (instancetype)fluidOunceImperialUnit; // fl_oz_imp
+ (instancetype)pintUSUnit;             // pt_us
+ (instancetype)pintImperialUnit;       // pt_imp
+ (instancetype)cupUSUnit API_AVAILABLE(ios(9.0), watchos(2.0));       // cup_us
+ (instancetype)cupImperialUnit API_AVAILABLE(ios(9.0), watchos(2.0)); // cup_imp
@end

/* Pressure Units */
@interface HKUnit (Pressure)
+ (instancetype)pascalUnitWithMetricPrefix:(HKMetricPrefix)prefix;     // Pa
+ (instancetype)pascalUnit;                 // Pa
+ (instancetype)millimeterOfMercuryUnit;    // mmHg
+ (instancetype)centimeterOfWaterUnit;      // cmAq
+ (instancetype)atmosphereUnit;             // atm
@end

/* Time Units */
@interface HKUnit (Time)
+ (instancetype)secondUnitWithMetricPrefix:(HKMetricPrefix)prefix;     // s
+ (instancetype)secondUnit; // s
+ (instancetype)minuteUnit; // min
+ (instancetype)hourUnit;   // hr
+ (instancetype)dayUnit;    // d
@end

/* Energy Units */
@interface HKUnit (Energy)
+ (instancetype)jouleUnitWithMetricPrefix:(HKMetricPrefix)prefix;      // J
+ (instancetype)jouleUnit;          // J
+ (instancetype)kilocalorieUnit;    // 1 kcal = 4184.0 J
+ (instancetype)smallCalorieUnit API_AVAILABLE(ios(11.0), watchos(4.0));    // 1 cal = 4.1840 J
+ (instancetype)largeCalorieUnit API_AVAILABLE(ios(11.0), watchos(4.0));    // 1 Cal = 4184.0 J
+ (instancetype)calorieUnit API_DEPRECATED("Use smallCalorieUnit or largeCalorieUnit, depending on which you mean", ios(8.0, 11.0), watchos(2.0, 4.0));
@end

/* Temperature Units */
@interface HKUnit (Temperature)
+ (instancetype)degreeCelsiusUnit;          // degC
+ (instancetype)degreeFahrenheitUnit;       // degF
+ (instancetype)kelvinUnit;                 // K
@end

/* Electrical Conductance Units */
@interface HKUnit (Conductance)
+ (instancetype)siemenUnitWithMetricPrefix:(HKMetricPrefix)prefix;     // S
+ (instancetype)siemenUnit; // S
@end

/* Pharmacology Units */
@interface HKUnit (Pharmacology)
+ (instancetype)internationalUnit NS_SWIFT_NAME(internationalUnit()) API_AVAILABLE(ios(11.0), watchos(4.0));  // IU
@end

/* Scalar Units */
@interface HKUnit (Scalar)
+ (instancetype)countUnit;      // count
+ (instancetype)percentUnit;    // % (0.0 - 1.0)
@end

@interface HKUnit (Math)
- (HKUnit *)unitMultipliedByUnit:(HKUnit *)unit;
- (HKUnit *)unitDividedByUnit:(HKUnit *)unit;
- (HKUnit *)unitRaisedToPower:(NSInteger)power;
- (HKUnit *)reciprocalUnit;
@end

/* Mole Constants */
#define HKUnitMolarMassBloodGlucose (180.15588000005408)

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKSourceRevision.h
//
//  HKSourceRevision.h
//  HealthKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <HealthKit/HKDefines.h>

@class HKSource;

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKSourceRevision
 @abstract      Represents a specific revision of an HKSource.
 */

HK_EXTERN API_AVAILABLE(ios(9.0), watchos(2.0))
@interface HKSourceRevision : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      source
 @abstract      The HKSource of the receiver.
 */
@property (readonly) HKSource *source;

/*!
 @property      version
 @abstract      The version of the source property.
 @discussion    This value is taken from the CFBundleVersion of the source. May be nil for older data.
 */
@property (readonly, nullable) NSString *version;

/*!
 @property      productType
 @abstract      Represents the product type of the device running HealthKit when the object was created.
 @discussion    This value may be nil for older data, which indicates an unknown product type.
 */
@property (readonly, copy, nullable) NSString *productType API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @property      operatingSystemVersion
 @abstract      Represents the operating system version of the device running HealthKit when the object was created.
 @discussion    iOS versions after 8.0 but prior to 8.2 are saved as 8.0, and iOS version after 8.2 but prior to 9.0
                are saved as 8.2.
 */
@property (readonly, assign) NSOperatingSystemVersion operatingSystemVersion API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @method        initWithSource:version:productType:operatingSystemVersion:
 @abstract      Initializes a new HKSourceRevision with the given source, version, product type, and operating system
                version.
 */
- (instancetype)initWithSource:(HKSource *)source
                       version:(nullable NSString *)version
                   productType:(nullable NSString *)productType
        operatingSystemVersion:(NSOperatingSystemVersion)operatingSystemVersion API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @method        initWithSource:version:
 @abstract      Initializes a new HKSourceRevision with the given source and version.
 */
- (instancetype)initWithSource:(HKSource *)source version:(nullable NSString *)version;

- (instancetype)init NS_UNAVAILABLE;

@end

// Constants to match on any value of that property when querying for samples from an HKSourceRevision
HK_EXTERN NSString * const HKSourceRevisionAnyVersion API_AVAILABLE(ios(11.0), watchos(4.0));
HK_EXTERN NSString * const HKSourceRevisionAnyProductType API_AVAILABLE(ios(11.0), watchos(4.0));
HK_EXTERN NSOperatingSystemVersion const HKSourceRevisionAnyOperatingSystem API_AVAILABLE(ios(11.0), watchos(4.0));

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKStatisticsQuery.h
//
//  HKStatisticsQuery.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKQuery.h>
#import <HealthKit/HKStatistics.h>

NS_ASSUME_NONNULL_BEGIN

@class HKStatistics;

/*!
 @class     HKStatisticsQuery
 @abstract  Calculates statistics on quantity samples matching the given quantity type and predicate.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKStatisticsQuery : HKQuery

- (instancetype)initWithQuantityType:(HKQuantityType *)quantityType
             quantitySamplePredicate:(nullable NSPredicate *)quantitySamplePredicate
                             options:(HKStatisticsOptions)options
                   completionHandler:(void(^)(HKStatisticsQuery *query, HKStatistics * _Nullable result, NSError * _Nullable error))handler;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKQuery.h
//
//  HKQuery.h
//  HealthKit
//
//  Copyright (c) 2013-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKFHIRResource.h>
#import <HealthKit/HKWorkout.h>

NS_ASSUME_NONNULL_BEGIN

@class HKObjectType;
@class HKQuantity;
@class HKSampleType;
@class HKSource;

HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKQuery : NSObject

@property (readonly, strong, nullable) HKObjectType *objectType API_AVAILABLE(ios(9.3), watchos(2.2));
@property (readonly, strong, nullable) HKSampleType *sampleType API_DEPRECATED_WITH_REPLACEMENT("objectType", ios(8.0, 9.3), watchos(2.0, 2.2));

@property (readonly, strong, nullable) NSPredicate *predicate;

- (instancetype)init NS_UNAVAILABLE;

@end

/**
 @enum      HKQueryOptions
 @abstract  Time interval options are used to describe how an HKSample's time period overlaps with a given time period.
 
 @constant  HKQueryOptionNone               The sample's time period must overlap with the predicate's time period.
 @constant  HKQueryOptionStrictStartDate    The sample's start date must fall in the time period (>= startDate, < endDate)
 @constant  HKQueryOptionStrictEndDate      The sample's end date must fall in the time period (>= startDate, < endDate)
 
 */
typedef NS_OPTIONS(NSUInteger, HKQueryOptions) {
    HKQueryOptionNone               = 0,
    HKQueryOptionStrictStartDate    = 1 << 0,
    HKQueryOptionStrictEndDate      = 1 << 1,
} API_AVAILABLE(ios(8.0), watchos(2.0));

@interface HKQuery (HKObjectPredicates)

/*!
 @method        predicateForObjectsWithMetadataKey:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches objects with metadata that contains a given key.
 
 @param         key     The metadata key.
 */
+ (NSPredicate *)predicateForObjectsWithMetadataKey:(NSString *)key;

/*!
 @method        predicateForObjectsWithMetadataKey:allowedValues:
 @abstract      Creates a predicate for use with HKQuery subclasses
 @discussion    Creates a query predicate that matches objects with metadata containing a value the matches one of the
                given values for the given key.
 
 @param         key             The metadata key.
 @param         allowedValues   The list of values that the metadata value can be equal to.
 */
+ (NSPredicate *)predicateForObjectsWithMetadataKey:(NSString *)key allowedValues:(NSArray *)allowedValues;

/*!
 @method        predicateForObjectsWithMetadataKey:operatorType:value:
 @abstract      Creates a predicate for use with HKQuery subclasses
 @discussion    Creates a query predicate that matches objects with a value for a given metadata key matches the given
                operator type and value.
 
 @param         key            The metadata key.
 @param         operatorType   The comparison operator type for the expression.
 @param         value          The value to be compared against.
 */
+ (NSPredicate *)predicateForObjectsWithMetadataKey:(NSString *)key operatorType:(NSPredicateOperatorType)operatorType value:(id)value;

/*!
 @method        predicateForObjectsFromSource:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches objects saved by a given source.
 
 @param         source  The source.
 */
+ (NSPredicate *)predicateForObjectsFromSource:(HKSource *)source;

/*!
 @method        predicateForObjectsFromSources:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches objects saved by any of the given sources.
 
 @param         sources The list of sources.
 */
+ (NSPredicate *)predicateForObjectsFromSources:(NSSet<HKSource *> *)sources;

/*!
 @method        predicateForObjectsFromSourceRevisions:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches objects saved by any of the specified HKSourceRevisions.
 
 @param         sourceRevisions The list of source revisions.
 */
+ (NSPredicate *)predicateForObjectsFromSourceRevisions:(NSSet<HKSourceRevision *> *)sourceRevisions API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @method        predicateForObjectsFromDevices:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches objects associated with any of the given devices. All properties
                of each HKDevice are considered in the query and must match exactly, including nil values. To perform 
                searches based on specific device properties, use predicateForObjectsWithDeviceProperty:allowedValues:.
 
 @param         devices     The set of devices that generated data.
 */
+ (NSPredicate *)predicateForObjectsFromDevices:(NSSet<HKDevice *> *)devices API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @method        predicateForObjectsWithDeviceProperty:allowedValues:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches objects associated with an HKDevice with the specified device
                property matching any value included in allowedValues. To query for samples with devices that match all 
                the properties of an HKDevice, use predicateForObjectsFromDevices.
 
 @param         key             The device property key. (See HKDevice.h)
 @param         allowedValues   The set of values for which the device property can match. An empty set will match all
                devices whose property value is nil.
 */
+ (NSPredicate *)predicateForObjectsWithDeviceProperty:(NSString *)key allowedValues:(NSSet<NSString *> *)allowedValues API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @method        predicateForObjectWithUUID:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches the object saved with a particular UUID.
 
 @param         UUID The UUID of the object.
 */
+ (NSPredicate *)predicateForObjectWithUUID:(NSUUID *)UUID;

/*!
 @method        predicateForObjectsWithUUIDs:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches the objects saved with one of the given UUIDs.
 
 @param         UUIDs The set of NSUUIDs.
 */
+ (NSPredicate *)predicateForObjectsWithUUIDs:(NSSet<NSUUID *> *)UUIDs;

/*!
 @method        predicateForObjectsNoCorrelation
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches the objects that are not associated with an HKCorrelation.
 */
+ (NSPredicate *)predicateForObjectsWithNoCorrelation;

/*!
 @method        predicateForObjectsFromWorkout:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches the objects that have been added to the given workout.
 
 @param         workout     The HKWorkout that the object was added to.
 */
+ (NSPredicate *)predicateForObjectsFromWorkout:(HKWorkout *)workout;

@end


@interface HKQuery (HKSamplePredicates)

/*!
 @method        predicateForSamplesWithStartDate:endDate:options:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches samples with a startDate and an endDate that lie inside of a
                given time interval.
 
 @param         startDate  The start date of the predicate's time interval.
 @param         endDate    The end date of the predicate's time interval.
 @param         options    The rules for how a sample's time interval overlaps with the predicate's time interval.
 */
+ (NSPredicate *)predicateForSamplesWithStartDate:(nullable NSDate *)startDate endDate:(nullable NSDate *)endDate options:(HKQueryOptions)options;

@end


@interface HKQuery (HKQuantitySamplePredicates)

/*!
 @method        predicateForQuantitySamplesWithOperatorType:quantity:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches quantity samples with values that match the expression formed by
                the given operator and quantity.
 
 @param         operatorType    The operator type for the expression.
 @param         quantity        The quantity that the sample's quantity is being compared to. It is the right hand side
                                of the expression.
 */
+ (NSPredicate *)predicateForQuantitySamplesWithOperatorType:(NSPredicateOperatorType)operatorType quantity:(HKQuantity *)quantity;

@end

@interface HKQuery (HKCategorySamplePredicates)

/*!
 @method        predicateForCategorySamplesWithOperatorType:value:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches category samples with values that match the expression formed by 
                the given operator and value.
 
 @param         operatorType    The operator type for the expression.
 @param         value           The value that the sample's value is being compared to. It is the right hand side of the
                                expression.
 */
+ (NSPredicate *)predicateForCategorySamplesWithOperatorType:(NSPredicateOperatorType)operatorType value:(NSInteger)value;

@end

@interface HKQuery (HKWorkoutPredicates)

/*!
 @method        predicateForWorkoutsWithWorkoutActivityType:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches HKWorkouts with the given HKWorkoutActivityType.
 
 @param         workoutActivityType     The HKWorkoutActivity type of the workout
 */
+ (NSPredicate *)predicateForWorkoutsWithWorkoutActivityType:(HKWorkoutActivityType)workoutActivityType;

/*!
 @method        predicateForWorkoutsWithOperatorType:duration:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches HKWorkouts by the given operator type and duration
 
 @param         operatorType    The operator type for the expression.
 @param         duration        The value that the workout's duration is being compared to. It is the right hand side of the
                                expression.
 */
+ (NSPredicate *)predicateForWorkoutsWithOperatorType:(NSPredicateOperatorType)operatorType duration:(NSTimeInterval)duration;

/*!
 @method        predicateForWorkoutsWithOperatorType:totalEnergyBurned:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches HKWorkouts by the given operator type and totalEnergyBurned
 
 @param         operatorType        The operator type for the expression.
 @param         totalEnergyBurned   The value that the workout's totalEnergyBurned is being compared to. It is the right hand side of the
                                    expression. The unit for this value should be of type Energy.
 */
+ (NSPredicate *)predicateForWorkoutsWithOperatorType:(NSPredicateOperatorType)operatorType totalEnergyBurned:(HKQuantity *)totalEnergyBurned;

/*!
 @method        predicateForWorkoutsWithOperatorType:totalDistance:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches HKWorkouts by the given operator type and totalEnergyBurned
 
 @param         operatorType    The operator type for the expression.
 @param         totalDistance   The value that the workout's totalEnergyBurned is being compared to. It is the right hand side of the
                                expression. The unit for this value should be of type Distance.
 */
+ (NSPredicate *)predicateForWorkoutsWithOperatorType:(NSPredicateOperatorType)operatorType totalDistance:(HKQuantity *)totalDistance;

/*!
 @method        predicateForWorkoutsWithOperatorType:totalSwimmingStrokeCount:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches HKWorkouts by the given operator type and totalSwimmingStrokeCount
 
 @param         operatorType                The operator type for the expression.
 @param         totalSwimmingStrokeCount    The value that the workout's totalSwimmingStrokeCount is being compared to.
                                            It is the right hand side of the expression. The unit for this value should
                                            be of type Count.
 */
+ (NSPredicate *)predicateForWorkoutsWithOperatorType:(NSPredicateOperatorType)operatorType totalSwimmingStrokeCount:(HKQuantity *)totalSwimmingStrokeCount;

/*!
 @method        predicateForWorkoutsWithOperatorType:totalFlightsClimbed:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches HKWorkouts by the given operator type and totalFlightsClimbed
 
 @param         operatorType                The operator type for the expression.
 @param         totalFlightsClimbed         The value that the workout's totalFlightsClimbed is being compared to.
                                            It is the right hand side of the expression. The unit for this value should
                                            be of type Count.
 */
+ (NSPredicate *)predicateForWorkoutsWithOperatorType:(NSPredicateOperatorType)operatorType totalFlightsClimbed:(HKQuantity *)totalFlightsClimbed API_AVAILABLE(ios(11.0), watchos(4.0));

@end

@interface HKQuery (HKActivitySummaryPredicates)

/*!
 @method        predicateForActivitySummaryWithDateComponents:
 @abstract      Creates a predicate for use with HKActivitySummaryQuery
 @discussion    Creates a query predicate that matches HKActivitySummaries with the given date components.
 
 @param         dateComponents  The date components of the activity summary. These date components should contain era, year, month,
                and day components in the gregorian calendar.
 */
+ (NSPredicate *)predicateForActivitySummaryWithDateComponents:(NSDateComponents *)dateComponents API_AVAILABLE(ios(9.3), watchos(2.2));

/*!
 @method        predicateForActivitySummariesBetweenStartDateComponents:endDateComponents:
 @abstract      Creates a predicate for use with HKActivitySummaryQuery
 @discussion    Creates a query predicate that matches HKActivitySummaries that fall between the given date components.
 
 @param         startDateComponents The date components that define the beginning of the range. These date components should contain 
                era, year, month, and day components in the gregorian calendar.
 
 @param         endDateComponents   The date components that define the end of the range. These date components should contain era, 
                year, month, and day components in the gregorian calendar.
 */
+ (NSPredicate *)predicateForActivitySummariesBetweenStartDateComponents:(NSDateComponents *)startDateComponents endDateComponents:(NSDateComponents *)endDateComponents API_AVAILABLE(ios(9.3), watchos(2.2));

@end

@interface HKQuery (HKClinicalRecordPredicates)

/*!
 @method        predicateForClinicalRecordsWithFHIRResourceType:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches HKClinicalRecords with a specific FHIR resource type.
 
 @param         resourceType    The FHIR resource type.
 */
+ (NSPredicate *)predicateForClinicalRecordsWithFHIRResourceType:(HKFHIRResourceType)resourceType API_AVAILABLE(ios(12.0)) __WATCHOS_PROHIBITED;

/*!
 @method        predicateForClinicalRecordsFromSource:withFHIRResourceType:identifier:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches HKClinicalRecords for a given source, FHIR resource type, and FHIR identifier.
 
 @param         source          The source.
 @param         resourceType    The FHIR resource type.
 @param         identifier      The FHIR identifier.
 */
+ (NSPredicate *)predicateForClinicalRecordsFromSource:(HKSource *)source
                                      FHIRResourceType:(HKFHIRResourceType)resourceType
                                            identifier:(NSString *)identifier API_AVAILABLE(ios(12.0)) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKClinicalRecord.h
//
//  HKClinicalRecord.h
//  HealthKit
//
//  Copyright (c) 2018 Apple Inc. All rights reserved.
//

#import <HealthKit/HKSample.h>

@class HKClinicalType;
@class HKFHIRResource;

NS_ASSUME_NONNULL_BEGIN

HK_EXTERN NSString * const HKPredicateKeyPathClinicalRecordFHIRResourceIdentifier API_AVAILABLE(ios(12.0)) __WATCHOS_PROHIBITED;
HK_EXTERN NSString * const HKPredicateKeyPathClinicalRecordFHIRResourceType API_AVAILABLE(ios(12.0)) __WATCHOS_PROHIBITED;

/*!
 @class		   HKClinicalRecord
 @abstract     An HKObject subclass representing a health record.
 @discussion   The startDate and endDate properties (inherited from HKSample) are set to the date the sample was
               added to Health. Unlike other HKObject subclasses, UUID is not a stable identifier
               for a given sample. Use a combination of HKSource, FHIRResource.resourceType, and
               FHIRResource.identifier instead.
*/
HK_EXTERN
API_AVAILABLE(ios(12.0))
__WATCHOS_PROHIBITED
@interface HKClinicalRecord : HKSample <NSSecureCoding, NSCopying>

@property (readonly, copy) HKClinicalType *clinicalType;

/*!
 @property     displayName
 @abstract     The primary display name used in Health.
 @discussion   The display name is not localized, and is generally expected to be US English.
 */
@property (copy, readonly) NSString *displayName;

/*!
 @property     FHIRResource
 @abstract     The FHIR resource (where applicable) backing this sample.
 */
@property (copy, readonly, nullable) HKFHIRResource *FHIRResource;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKCumulativeQuantitySeriesSample.h
//
//  HKCumulativeQuantitySeriesSample.h
//  HealthKit
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <HealthKit/HKQuantitySample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;

/*!
 @class         HKCumulativeQuantitySeriesSample
 @abstract      An HKQuantitySample subclass representing a series of cumulative quantity measurements.
 */
HK_EXTERN API_AVAILABLE(ios(12.0), watchos(5.0))
@interface HKCumulativeQuantitySeriesSample : HKQuantitySample

/*!
 @property      sum
 @abstract      The sum of quantities in the series represented by the receiver.
 */
@property (readonly, copy) HKQuantity *sum;

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathSum API_AVAILABLE(ios(12.0), watchos(5.0));

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKSampleQuery.h
//
//  HKSampleQuery.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

// The query returns all samples that match the given sampleType and predicate.
static const NSUInteger HKObjectQueryNoLimit = 0;

/*!
 @class         HKSampleQuery
 @abstract      A concrete subclass of HKQuery that provides an interface to retrieve HKSample objects.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKSampleQuery : HKQuery

/*!
 @property      limit
 @abstract      The maximum number of results the receiver will return upon completion.
 */
@property (readonly) NSUInteger limit;

/*!
 @property      sortDescriptors
 @abstract      An array of NSSortDescriptors.
 */
@property (readonly, copy, nullable) NSArray<NSSortDescriptor *> *sortDescriptors;

/*!
 @method        initWithSampleType:predicate:limit:sortDescriptors:resultsHandler:
 @abstract      Returns a query that will retrieve HKSamples matching the given predicate.
 
 @param         sampleType      The type of sample to retrieve.
 @param         predicate       The predicate which samples should match.
 @param         limit           The maximum number of samples to return.  Pass HKObjectQueryNoLimit for no limit.
 @param         sortDescriptors The sort descriptors to use to order the resulting samples.
 @param         resultsHandler  The block to invoke with results when the query has finished executing.
 */
- (instancetype)initWithSampleType:(HKSampleType *)sampleType
                         predicate:(nullable NSPredicate *)predicate
                             limit:(NSUInteger)limit
                   sortDescriptors:(nullable NSArray<NSSortDescriptor *> *)sortDescriptors
                    resultsHandler:(void(^)(HKSampleQuery *query, NSArray<__kindof HKSample *> * _Nullable results, NSError * _Nullable error))resultsHandler;


@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKCategorySample.h
//
//  HKCategorySample.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKObject.h>
#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKCategoryType;

/*!
 @class      HKCategorySample
 @abstract   An HKObject subclass representing an category measurement
 @discussion Category samples are samples that can be categorized into an enum of concrete values
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKCategorySample : HKSample

@property (readonly, strong) HKCategoryType *categoryType;

/*!
 @property   value
 @discussion The preferred enum for the value is determined by the receiver's category type.
 */
@property (readonly) NSInteger value;

- (instancetype)init NS_UNAVAILABLE;

/*!
 @method     categorySampleWithType:value:startDate:endDate:metadata:
 @abstract   Creates a new HKCategorySample.
 
 @param      type       The type of the sample.
 @param      value      The enumeration value for the sample. See HKCategoryTypeIdentifier for appropriate value.
 @param      startDate  The start date of the sample.
 @param      endDate    The end date of the sample.
 @param      metadata   Metadata for the sample (optional).
 */
+ (instancetype)categorySampleWithType:(HKCategoryType *)type
                                 value:(NSInteger)value
                             startDate:(NSDate *)startDate
                               endDate:(NSDate *)endDate
                              metadata:(nullable NSDictionary<NSString *, id> *)metadata;

/*!
 @method     categorySampleWithType:value:startDate:endDate:
 @abstract   Creates a new HKCategorySample.
 
 @param      type       The type of the sample.
 @param      value      The enumeration value for the sample. See HKCategoryTypeIdentifier for appropriate value.
 @param      startDate  The start date of the sample.
 @param      endDate    The end date of the sample.
 */
+ (instancetype)categorySampleWithType:(HKCategoryType *)type
                                 value:(NSInteger)value
                             startDate:(NSDate *)startDate
                               endDate:(NSDate *)endDate;

/*!
 @method     categorySampleWithType:value:startDate:endDate:device:metadata:
 @abstract   Creates a new HKCategorySample.
 
 @param      type       The type of the sample.
 @param      value      The enumeration value for the sample. See HKCategoryTypeIdentifier for appropriate value.
 @param      startDate  The start date of the sample.
 @param      endDate    The end date of the sample.
 @param      device     The HKDevice that generated the sample (optional).
 @param      metadata   Metadata for the sample (optional).
 */
+ (instancetype)categorySampleWithType:(HKCategoryType *)type
                                 value:(NSInteger)value
                             startDate:(NSDate *)startDate
                               endDate:(NSDate *)endDate
                                device:(nullable HKDevice *)device
                              metadata:(nullable NSDictionary<NSString *, id> *)metadata API_AVAILABLE(ios(9.0), watchos(2.0));

@end

/*!
 @constant     HKPredicateKeyPathCategoryValue
 */
HK_EXTERN NSString * const HKPredicateKeyPathCategoryValue API_AVAILABLE(ios(8.0), watchos(2.0));

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKSample.h
//
//  HKSample.h
//  HealthKit
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#import <HealthKit/HKObject.h>

NS_ASSUME_NONNULL_BEGIN

@class HKSampleType;

/*!
 @class         HKSample
 @abstract      An abstract class representing measurements taken over a period of time.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKSample : HKObject

@property (readonly, copy) HKSampleType *sampleType;

@property (readonly, strong) NSDate *startDate;
@property (readonly, strong) NSDate *endDate;

@end

// Sort Identifiers
HK_EXTERN NSString * const HKSampleSortIdentifierStartDate API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKSampleSortIdentifierEndDate API_AVAILABLE(ios(8.0), watchos(2.0));

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathStartDate API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKPredicateKeyPathEndDate API_AVAILABLE(ios(8.0), watchos(2.0));

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKCharacteristicObjects.h
//
//  HKCharacteristicObjects.h
//  HealthKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <HealthKit/HKDefines.h>

#import <Foundation/Foundation.h>

/*!
 @class     HKBiologicalSexObject
 @abstract  A wrapper object for HKBiologicalSex enumeration.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKBiologicalSexObject : NSObject <NSCopying, NSSecureCoding>

@property (readonly) HKBiologicalSex biologicalSex;

@end

/*!
 @class     HKBloodTypeObject
 @abstract  A wrapper object for HKBloodType enumeration.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKBloodTypeObject : NSObject <NSCopying, NSSecureCoding>

@property (readonly) HKBloodType bloodType;

@end

/*!
 @class     HKFitzpatrickSkinTypeObject
 @abstract  A wrapper object for HKFitzpatrickSkinType enumeration.
 */
HK_EXTERN API_AVAILABLE(ios(9.0), watchos(2.0))
@interface HKFitzpatrickSkinTypeObject : NSObject <NSCopying, NSSecureCoding>

@property (readonly) HKFitzpatrickSkinType skinType;

@end

/*!
 @class     HKWheelchairUseObject
 @abstract  A wrapper object for HKWheelchairUse enumeration.
 */
HK_EXTERN API_AVAILABLE(ios(10.0), watchos(3.0))
@interface HKWheelchairUseObject : NSObject <NSCopying, NSSecureCoding>

@property (readonly) HKWheelchairUse wheelchairUse;

@end
// ==========  HealthKit.framework/Headers/HKLiveWorkoutDataSource.h
//
//  HKLiveWorkoutDataSource.h
//  HealthKit
//
//  Copyright © 2017-2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKWorkoutBuilder.h>

NS_ASSUME_NONNULL_BEGIN

@class HKWorkoutConfiguration;
@class HKQuantityType;

/*!
 @class         HKLiveWorkoutDataSource
 @discussion    An HKLiveWorkoutDataSource is to be used with an HKWorkoutBuilder to automatically collect samples
 */
HK_EXTERN API_AVAILABLE(watchos(5.0)) __IOS_PROHIBITED
@interface HKLiveWorkoutDataSource : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 @property      typesToCollect
 @abstract      The quantity types the receiver is collecting.
 */
@property (copy, readonly) NSSet<HKQuantityType *> *typesToCollect;

/*!
 @method        initWithHealthStore:workoutConfiguration:
 @abstract      The designated initializer of HKLiveWorkoutDataSource.
 
 @param         healthStore     The HKHealthStore. This should match the one used to create the corresponding
                                HKWorkoutBuilder.
 @param         configuration   An optional workout configuration. typesToCollect will be populated with default
                                types for the workout configuration
 */
- (instancetype)initWithHealthStore:(HKHealthStore *)healthStore
               workoutConfiguration:(nullable HKWorkoutConfiguration *)configuration NS_DESIGNATED_INITIALIZER;

/*!
 @method        enableCollectionForType:predicate
 @abstract      Adds a new type of quantity sample to collect.
 @discussion    Calling this method for a type that is already being collected will override the predicate for that type.
 
 @param         quantityType    The type of sample to collect.
 @param         predicate       If non-nil, collected samples must match this predicate.
 */
- (void)enableCollectionForType:(HKQuantityType *)quantityType
                      predicate:(nullable NSPredicate *)predicate;

/*!
 @method        disableCollectionForType:
 @abstract      Removes the specified quantity type from the types to collect.
 
 @param         quantityType    The type of sample to no longer collect.
 */
- (void)disableCollectionForType:(HKQuantityType *)quantityType;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKCDADocumentSample.h
//
//  HKCDADocumentSample.h
//  HealthKit
//
//  Copyright © 2015 Apple. All rights reserved.
//
//  HealthKit support for storing and retrieving
//  Consolidated Clinical Document records.
//

#import <HealthKit/HKDocumentSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKCDADocument;

/*!
 @class         HKCDADocumentSample
 @abstract      A sample object representing a CDA document.
 */
HK_EXTERN API_AVAILABLE(ios(10.0)) __WATCHOS_PROHIBITED
@interface HKCDADocumentSample : HKDocumentSample

/*!
 @property      document
 @abstract      The contents of the document.
 @discussion    Access to each CDA instance must be authorized by the user in order for the document data to be
                accessible to an app.  The authorization request occurs the first time a document matches the predicate
                of an executed HKDocumentQuery.  This property will always be nil if the sample is returned by an
                HKSampleQuery or an HKAnchoredObjectQuery.
 */
@property (readonly, nullable) HKCDADocument *document;

/*!
 @method                CDADocumentSampleWithData:startDate:endDate:device:metadata:validationError:
 @abstract              Creates a new document sample with the specified attributes.
 @param documentData    Document contents in an XML format that meets the CDA standard.
 @param startDate       The start date for the document.
 @param endDate         The end date for the document.
 @param metadata        Metadata for the document.
 @param validationError The XML content will be validated against the standard for CDA content.  If that validation
                        fails, then this parameter will be set with the relavant error.  Detailed information about the
                        failure may be obtained by examining the value for the HKDetailedCDAValidationErrorKey key of
                        the NSError's userInfo dictionary.
 @return                The new instance or nil if the documentData does not pass validation.
 @discussion            Attributes of the document, such as title, patient name, etc. will be extracted automatically
                        from the document content.
 */
+ (nullable instancetype)CDADocumentSampleWithData:(NSData *)documentData
                                         startDate:(NSDate *)startDate
                                           endDate:(NSDate *)endDate
                                          metadata:(nullable NSDictionary<NSString *, id> *)metadata
                                   validationError:(NSError **)validationError __WATCHOS_UNAVAILABLE;

@end

HK_EXTERN API_AVAILABLE(ios(11.0)) __WATCHOS_PROHIBITED
@interface HKCDADocument : NSObject

/*!
 @property  documentData
 @abstract  The CDA document content in XML format as specified in the CDA standard. This may be nil if the
            includeDocumentData option in HKDocumentQuery is specified as NO.
 */
@property (readonly, copy, nullable) NSData *documentData API_AVAILABLE(ios(10.0));

/*!
 @property      title
 @abstract      The title of the document.
 @discussion    This property is extracted automatically from the document.
 */
@property (readonly, copy) NSString *title API_AVAILABLE(ios(10.0));

/*!
 @property      patientName
 @abstract      The name of the patient receiving treatment.
 @discussion    This property is extracted automatically from the document.
 */
@property (readonly, copy) NSString *patientName API_AVAILABLE(ios(10.0));

/*!
 @property      authorName
 @abstract      The person responsible for authoring the document.  Usually, this is the treating physician.
 @discussion    This property is extracted automatically from the document.
 */
@property (readonly, copy) NSString *authorName API_AVAILABLE(ios(10.0));

/*!
 @property      custodianName
 @abstract      The organization responsible for the document.  This is usually the treating institution name.
 @discussion    This property is extracted automatically from the document.
 */
@property (readonly, copy) NSString *custodianName API_AVAILABLE(ios(10.0));

@end

/*!
 @constant  HKPredicateKeyPathCDATitle
 */
HK_EXTERN NSString * const HKPredicateKeyPathCDATitle API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @constant  HKPredicateKeyPathCDAPatientName
 */
HK_EXTERN NSString * const HKPredicateKeyPathCDAPatientName API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @constant  HKPredicateKeyPathCDAAuthorName
 */
HK_EXTERN NSString * const HKPredicateKeyPathCDAAuthorName API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @constant  HKPredicateKeyPathCDACustodianName
 */
HK_EXTERN NSString * const HKPredicateKeyPathCDACustodianName API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @constant      HKDetailedCDAValidationErrorKey
 @discussion    This may be used with the validationError parameter of
                CDADocumentSampleWithData:startDate:endDate:device:metadata:validationError: to obtain a detailed
                description of the validation errors encountered when creating a CDA document.
 */
HK_EXTERN NSString * const HKDetailedCDAValidationErrorKey API_AVAILABLE(ios(10.0), watchos(3.0));

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKCorrelation.h
//
//  HKCorrelation.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKObjectType;
@class HKCorrelationType;

/*!
 @class         HKCorrelation
 @abstract      An HKCorrelation is a collection of correlated objects.
 @discussion    When multiple readings are taken together, it may be beneficial to correlate them so that they can be
                displayed together and share common metadata about how they were created.
 
                For example, systolic and diastolic blood pressure readings are typically presented together so these
                readings should be saved with a correlation of type blood pressure.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKCorrelation : HKSample

@property (readonly) HKCorrelationType *correlationType;

/*!
 @property  objects
 @abstract  A set of HKSamples containing all of the objects that were saved with the receiver.
 */
@property (readonly, copy) NSSet<__kindof HKSample *> *objects;

/*!
 @method        correlationWithType:startDate:endDate:objects:
 @abstract      Creates a new HKCorrelation with the given type, start date, end date, and objects.
 @discussion    objects must be a set of HKQuantitySamples and HKCategorySamples
 */
+ (instancetype)correlationWithType:(HKCorrelationType *)correlationType
                          startDate:(NSDate *)startDate
                            endDate:(NSDate *)endDate
                            objects:(NSSet<HKSample *> *)objects;

/*!
 @method        correlationWithType:startDate:endDate:objects:metadata:
 @abstract      Creates a new HKCorrelation with the given type, start date, end date, objects, and metadata.
 @discussion    objects must be a set of HKQuantitySamples and HKCategorySamples
 */
+ (instancetype)correlationWithType:(HKCorrelationType *)correlationType
                          startDate:(NSDate *)startDate
                            endDate:(NSDate *)endDate
                            objects:(NSSet<HKSample *> *)objects
                           metadata:(nullable NSDictionary<NSString *, id> *)metadata;

/*!
 @method        correlationWithType:startDate:endDate:objects:device:metadata:
 @abstract      Creates a new HKCorrelation with the given type, start date, end date, objects, and metadata.
 @param         correlationType The correlation type of the objects set.
 @param         startDate       The start date of the correlation.
 @param         endDate         The end date of the correlation.
 @param         device          The HKDevice that generated the samples (optional).
 @param         metadata        Metadata for the correlation (optional).
 @discussion    objects must be a set of HKQuantitySamples and HKCategorySamples
 */
+ (instancetype)correlationWithType:(HKCorrelationType *)correlationType
                          startDate:(NSDate *)startDate
                            endDate:(NSDate *)endDate
                            objects:(NSSet<HKSample *> *)objects
                             device:(nullable HKDevice *)device
                           metadata:(nullable NSDictionary<NSString *, id> *)metadata API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @method    objectsForType:
 @abstract  Returns the set of correlated objects with the specified type.
 */
- (NSSet<__kindof HKSample *> *)objectsForType:(HKObjectType *)objectType;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKAnchoredObjectQuery.h
//
//  HKAnchoredObjectQuery.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKQuery.h>

@class HKDeletedObject;

NS_ASSUME_NONNULL_BEGIN

#define HKAnchoredObjectQueryNoAnchor (0)

/*!
 @class         HKQueryAnchor
 @discussion    This object encapsulates the state of an HKAnchoredObjectQuery
 */
HK_EXTERN API_AVAILABLE(ios(9.0), watchos(2.0))
@interface HKQueryAnchor : NSObject <NSSecureCoding, NSCopying>

/*!
 @method        anchorFromValue:
 @discussion    Creates an HKQueryAnchor with an integer anchor which was previously obtained from an HKAnchoredObjectQuery prior to iOS 9.0.
 */
+ (instancetype)anchorFromValue:(NSUInteger)value;

- (instancetype)init NS_UNAVAILABLE;

@end

/*!
 @class         HKAnchoredObjectQuery
 @discussion    This query can be used by an application to find out about new or deleted samples in the HealthKit
                database.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKAnchoredObjectQuery : HKQuery

/*!
 @property      updateHandler
 @abstract      An optional handler to be called when samples matching the given predicate are added or deleted.
 @discussion    This property may not be modified once the query has been executed.  It may only be set if the query has
                no limit.
 */
@property (nonatomic, copy, nullable) void(^updateHandler)(HKAnchoredObjectQuery *query, NSArray<__kindof HKSample *> * _Nullable addedObjects, NSArray<HKDeletedObject *> * _Nullable deletedObjects, HKQueryAnchor * _Nullable newAnchor, NSError * _Nullable error) API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @method        initWithType:predicate:anchor:limit:resultsHandler:
 @abstract      Returns a query that will retrieve HKSamples and HKDeletedObjects matching the given predicate that are
                newer than the given anchor.
 @discussion    If no updateHandler is set on the query, the query will automatically stop after calling resultsHandler.
                Otherwise, the query continues to run and call updateHandler as samples matching the predicate are
                created or deleted.
 
 @param         type            The type of sample to retrieve.
 @param         predicate       The predicate which samples should match.
 @param         anchor          The anchor which was returned by a previous HKAnchoredObjectQuery result or update
                                handler.  Pass nil when querying for the first time.
 @param         limit           The maximum number of samples and deleted objects to return.  Pass HKObjectQueryNoLimit
                                for no limit.
 @param         handler         The block to invoke with results when the query has finished finding.
 */
- (instancetype)initWithType:(HKSampleType *)type
                   predicate:(nullable NSPredicate *)predicate
                      anchor:(nullable HKQueryAnchor *)anchor
                       limit:(NSUInteger)limit
              resultsHandler:(void(^)(HKAnchoredObjectQuery *query, NSArray<__kindof HKSample *> * _Nullable sampleObjects, NSArray<HKDeletedObject *> * _Nullable deletedObjects, HKQueryAnchor * _Nullable newAnchor, NSError * _Nullable error))handler API_AVAILABLE(ios(9.0), watchos(2.0));

- (instancetype)initWithType:(HKSampleType *)type
                   predicate:(nullable NSPredicate *)predicate
                      anchor:(NSUInteger)anchor
                       limit:(NSUInteger)limit
           completionHandler:(void(^)(HKAnchoredObjectQuery *query, NSArray<__kindof HKSample *> * __nullable results, NSUInteger newAnchor, NSError * __nullable error))handler API_DEPRECATED_WITH_REPLACEMENT("initWithType:predicate:anchor:limit:resultsHandler:", ios(8.0, 9.0));

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKActivitySummary.h
//
//  HKActivitySummary.h
//  HealthKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;

/*!
 @class         HKActivitySummary
 @abstract      An object that represents a summary of a user's activity for a given day.
 */
HK_EXTERN API_AVAILABLE(ios(9.3), watchos(2.2))
@interface HKActivitySummary : NSObject <NSSecureCoding, NSCopying>

/**
 @method        dateComponentsForCalendar:
 @abstract      The date components representing the day for this particular HKActivitySummary.
 @discussion    These date components will contain era, year, month, and day components in the provided calendar.
 */
- (NSDateComponents *)dateComponentsForCalendar:(NSCalendar *)calendar;

/**
  @property      activeEnergyBurned
  @abstract      The amount of active energy that the user burned.
  @discussion    This quantity is compatible with energy units.
  */
@property (nonatomic, strong) HKQuantity *activeEnergyBurned;

/**
  @property      appleExerciseTime
  @abstract      The amount of exercise time that the user performed.
  @discussion    This quantity is compatible with time units. The measurement criteria of 
                 exercise time is defined by Apple.
  */
@property (nonatomic, strong) HKQuantity *appleExerciseTime;

/**
  @property      appleStandHours
  @abstract      The number of stand hours that the user earned.
 @discussion     This quantity is compatible with the count unit. The measurement criteria of
                 stand hours is defined by Apple.
  */
@property (nonatomic, strong) HKQuantity *appleStandHours;

/**
  @property      activeEnergyBurnedGoal
  @abstract      The user's active energy goal for the day.
  @discussion    This quantity is compatible with energy units.
  */
@property (nonatomic, strong) HKQuantity *activeEnergyBurnedGoal;

/**
  @property      appleExerciseTimeGoal
  @abstract      The user's exercise time goal for the day.
  @discussion    This quantity is compatible with time units.
  */
@property (nonatomic, strong) HKQuantity *appleExerciseTimeGoal;

/**
  @property      appleStandHoursGoal
  @abstract      The user's active stand hours goal for the day.
  @discussion    This quantity is compatible with the count unit.
  */
@property (nonatomic, strong) HKQuantity *appleStandHoursGoal;

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathDateComponents API_AVAILABLE(ios(9.3), watchos(2.2));

NS_ASSUME_NONNULL_END

// ==========  HealthKit.framework/Headers/HKLiveWorkoutBuilder.h
//
//  HKLiveWorkoutBuilder.h
//  HealthKit
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <HealthKit/HealthKit.h>
#import <HealthKit/HKWorkoutBuilder.h>
#import <HealthKit/HKLiveWorkoutDataSource.h>

NS_ASSUME_NONNULL_BEGIN

@class HKLiveWorkoutBuilder;

HK_EXTERN API_AVAILABLE(watchos(5.0)) __IOS_PROHIBITED
@protocol HKLiveWorkoutBuilderDelegate <NSObject>

/*!
 @method        workoutBuilder:didCollectDataOfTypes:
 @abstract      Called every time new samples are added to the workout builder.
 @discussion    With new samples added, statistics for the collectedTypes may have changed and should be read again
 
 @param         workoutBuilder    The workout builder to which samples were added.
 @param         collectedTypes    The sample types that were added.
 */
- (void)workoutBuilder:(HKLiveWorkoutBuilder *)workoutBuilder didCollectDataOfTypes:(NSSet<HKSampleType *> *)collectedTypes;

/*!
 @method        workoutBuilderDidCollectEvent:
 @abstract      Called every time a new event is added to the workout builder.
 
 @param         workoutBuilder    The workout builder to which an event was added.
 */
- (void)workoutBuilderDidCollectEvent:(HKLiveWorkoutBuilder *)workoutBuilder;

@end

HK_EXTERN API_AVAILABLE(watchos(5.0)) __IOS_PROHIBITED
@interface HKLiveWorkoutBuilder : HKWorkoutBuilder

- (instancetype)initWithHealthStore:(HKHealthStore *)healthStore
                      configuration:(HKWorkoutConfiguration *)configuration
                             device:(nullable HKDevice *)device NS_UNAVAILABLE;

/*!
 @property      delegate
 @abstract      The delegate object which will be notified of changes to collected data and elapsed workout time.
 */
@property (weak) id<HKLiveWorkoutBuilderDelegate> delegate;

/*!
 @property      workoutSession
 @abstract      The workout session with which this builder is associated.
 */
@property (weak, readonly) HKWorkoutSession *workoutSession;

/*!
 @property      shouldCollectWorkoutEvents
 @abstract      Whether or not the builder should automatically incorporate events generated by the session.
 @discussion    YES if the builder should automatically incorporate events from the associated session. If NO, the client
                is expected to add relevant events directly to the builder and those generated by the session will be
                ignored. Defaults to YES. The result of changing this value after a call to
                beginCollectionWithStartDate:completion: is undefined.
 */
@property (assign) BOOL shouldCollectWorkoutEvents;

/*!
 @property      dataSource
 @abstract      The data source that will provide data to this workout builder.
 */
@property (strong, nullable) HKLiveWorkoutDataSource *dataSource;

/*!
 @property      elapsedTime
 @abstract      The elapsed duration of the workout as constructed thus far, considering paused time. When the builder
                is reading events from an active session, it is possible for this value to increase or decrease;
                when this occurs, the workoutBuilderDidCollectEvent: delegate method will be called.
 */
@property (assign, readonly) NSTimeInterval elapsedTime;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKObserverQuery.h
//
//  HKObserverQuery.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

typedef void(^HKObserverQueryCompletionHandler)(void);

HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKObserverQuery : HKQuery

/*!
 @method        initWithSampleType:predicate:updateHandler:
 @abstract      This method installs a handler that is called when a sample type has a new sample added.
 @discussion    If you have subscribed to background updates you must call the passed completion block
                once you have processed data from this notification. Otherwise the system will continue
                to notify you of this data.
 */

- (instancetype)initWithSampleType:(HKSampleType *)sampleType
                         predicate:(nullable NSPredicate *)predicate
                     updateHandler:(void(^)(HKObserverQuery *query, HKObserverQueryCompletionHandler completionHandler, NSError * _Nullable error))updateHandler;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKSourceQuery.h
//
//  HKSourceQuery.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKSourceQuery
 @abstract      A query that returns a set of sources that have saved objects matching certain criteria.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKSourceQuery : HKQuery

/*!
 @method        initWithSampleType:samplePredicate:completionHandler:
 @abstract      Returns a query that will retrieve HKSources that have saved samples of the given type matching the 
                given predicate.
 
 @param         sampleType          The type of sample.
 @param         objectPredicate     The predicate which samples must match.
 @param         completionHandler   The block to be called when the query has finished executing.
 */
- (instancetype)initWithSampleType:(HKSampleType *)sampleType
                   samplePredicate:(nullable NSPredicate *)objectPredicate
                 completionHandler:(void(^)(HKSourceQuery *query, NSSet<HKSource *> * _Nullable sources, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKWorkoutBuilder.h
//
//  HKWorkoutBuilder.h
//  HealthKit
//
//  Copyright © 2017-2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKObjectType.h>
#import <HealthKit/HKWorkout.h>

NS_ASSUME_NONNULL_BEGIN

@class HKHealthStore;
@class HKSeriesBuilder;
@class HKStatistics;
@class HKWorkoutConfiguration;

/*!
 @class         HKWorkoutBuilder
 @discussion    An HKWorkoutBuilder is used to incrementally create new workouts in the HealthKit database. Samples,
                events, and metadata may be added to a builder either during a live workout session or to create a
                workout that occurred in the past. Calling finishWorkoutWithCompletion: will create a new workout
                with samples, events, and metadata that have been provided.
 */
HK_EXTERN API_AVAILABLE(ios(12.0), watchos(5.0))
@interface HKWorkoutBuilder : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 @property      device
 @abstract      The HKDevice to be associated with the workout.
 */
@property (copy, nullable, readonly) HKDevice *device;

/*!
 @property      startDate
 @abstract      The start date for the workout, as provided by beginCollectionWithStartDate:completion:
 */
@property (copy, nullable, readonly) NSDate *startDate;

/*!
 @property      endDate
 @abstract      The end date for the workout, as provided by endCollectionWithEndDate:completion:
 */
@property (copy, nullable, readonly) NSDate *endDate;

/*!
 @property      workoutConfiguration
 @abstract      The configuration for the workout being built.
 */
@property (copy, readonly) HKWorkoutConfiguration *workoutConfiguration;

/*!
 @property      metadata
 @abstract      The metadata that will be used when the workout is finished.
 */
@property (copy, readonly) NSDictionary<NSString *, id> *metadata;

/*!
 @property      workoutEvents
 @abstract      Workout events that have been added to the builder.
 @discussion    New events that are added using addWorkoutEvents:completion: will be appended to this array once the
                completion is called.
 */
@property (copy, readonly) NSArray<HKWorkoutEvent *> *workoutEvents;

/*!
 @method        initWithHealthStore:configuration:device:
 @abstract      The designated initializer to create an HKWorkoutBuilder.
 @discussion    Creates a new HKWorkoutBuilder unconnected to any HKWorkoutSession or any sources of data.

 @param         healthStore     Specifies the HKHealthStore object to use for building the workout. The store is retained
                                until the builder is finished and a workout has been saved or discarded.
 @param         configuration   The workout configuration to be used.
 @param         device          The HKDevice to attach to the resulting HKWorkout.
 */
- (instancetype)initWithHealthStore:(HKHealthStore *)healthStore
                      configuration:(HKWorkoutConfiguration *)configuration
                             device:(nullable HKDevice *)device;

/*!
 @method        beginCollectionWithStartDate:error:
 @abstract      Sets the workout start date and activates the workout builder.
 @discussion    Calling this method is required before any samples, events or metadata can be added to the builder.
 
 @param         startDate   The start date of the workout.
 @param         completion  Called once data collection has started or has failed to start.
 */
- (void)beginCollectionWithStartDate:(NSDate *)startDate completion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*!
 @method        addSamples:completion:
 @discussion    Adds new samples to the builder instance. This method can be called multiple times to add samples
                incrementally to the builder. The samples will be saved to the database if they have not already been
                saved. The constraints of -[HKHealthStore saveObject:withCompletion:] apply to this method as well.
                The start date of the samples must be later than the start date of the receiver. It is an error to call
                this method after finishWorkoutWithCompletion: has been called. This operation is performed
                asynchronously and the completion will be executed on an arbitrary background queue.

 @param         samples     The samples to add to the workout.
 @param         completion  Block to be called when the insertion is complete. If success is YES, the samples were added
                            to the builder successfully. If success is NO, error will be non-nil and contain the error
                            encountered while adding the new samples.
 */
- (void)addSamples:(NSArray<HKSample *> *)samples completion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*!
 @method        addWorkoutEvents:completion:
 @discussion    Adds new workout events to the builder instance. This method can be called many times to add workout
                events incrementally to the builder. It is an error to call this method after
                finishWorkoutWithCompletion: has been called. This operation is performed asynchronously and the
                completion will be executed on an arbitrary background queue.

 @param         workoutEvents   The events to add to the builder.
 @param         completion      Block to be called when the addition of events to the builder is complete. If success is
                                YES, the events were added to the builder successfully. If success is NO, error will be
                                non-null and will contain the error encountered during the insertion operation.
 */
- (void)addWorkoutEvents:(NSArray<HKWorkoutEvent *> *)workoutEvents completion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*!
 @method        addMetadata:completion:
 @discussion    Adds new metadata to the builder instance. This method can be called more than once; each time the newly
                provided metadata will be merged with previously added metadata in the same manner as
                -[NSMutableDictionary addEntriesFromDictionary:]. This operation is performed asynchronously and the
                completion will be executed on an arbitrary background queue.

 @param         metadata    The metadata to add to the workout.
 @param         completion  Block to be called when the addition of metadata to the builder is complete. If success is
                            YES, the metadata has been added to the builder successfully. If success is NO, error will
                            be non-null and will contain the error encountered during the insertion operation. When an
                            error occurs, the builder's metadata property will remain unchanged.
 */
- (void)addMetadata:(NSDictionary<NSString *, id> *)metadata completion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*!
 @method        endCollectionWithEndDate:error:
 @abstract      Sets the workout end date and deactivates the workout builer.
 @discussion    Calling this method is required before you finish a workout builder.
 
 @param         endDate     The end date of the workout.
 @param         completion  Called once data collection has stopped or has failed to stop.
 */
- (void)endCollectionWithEndDate:(NSDate *)endDate completion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*!
 @method        finishWorkoutWithCompletion:
 @discussion    Creates and saves an HKWorkout using samples and events that have been added to workout previously.
 
 @param         completion  Block to be called after the HKWorkout object has been created and saved. If success is NO,
                            then error will be the error encountered during the operation.
 */
- (void)finishWorkoutWithCompletion:(void(^)(HKWorkout * _Nullable workout, NSError * _Nullable error))completion;

/*!
 @method        discardWorkout
 @discussion    Finishes building the workout and discards ther result instead of saving it. Samples that were added to
                the workout will not be deleted. Adding samples, events, and metadata to the receiver after
                discardWorkout has been called is an error.
 */
- (void)discardWorkout;

/*!
 @method        elapsedTimeAtDate:
 @abstract      The elapsed duration of the workout evaluated at the specified date. The duration does not include
                periods when the workout was paused, which are the intervals between pause and resume events.
 */
- (NSTimeInterval)elapsedTimeAtDate:(NSDate *)date;

/*!
 @method        statisticsForType:
 @discussion    Returns an HKStatistics object containing the statistics for all the samples of the given type that
                have been added to the receiver. If there are no samples of the given type then nil is returned.
 
 @param         quantityType    The quantity type to gather statistics about.
 */
- (nullable HKStatistics *)statisticsForType:(HKQuantityType *)quantityType;

/*!
 @method        seriesBuilderForType:
 @abstract      Retrieves the associated series builder for the specified type.
 @discussion    Retrieves, and creates if it does not already exist, the series builder for the specified type. The
                series constructed with the returned builder will be associated with the workout when it is finished.
 
 @param         seriesType  The series type for which the builder should be retrieved.
 */
- (nullable __kindof HKSeriesBuilder *)seriesBuilderForType:(HKSeriesType *)seriesType;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKDocumentSample.h
//
//  HKDocumentSample.h
//  HealthKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKDocumentType;

/*!
 @class         HKDocumentSample
 @abstract      An abstract class representing a health document.
 */
HK_EXTERN API_AVAILABLE(ios(10.0), watchos(3.0))
@interface HKDocumentSample : HKSample

@property (readonly, strong) HKDocumentType *documentType;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKQuantitySample.h
//
//  HKQuantitySample.h
//  HealthKit
//
//  Copyright (c) 2013-2018 Apple Inc. All rights reserved.
//

#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;
@class HKQuantityType;

/*!
 @class         HKQuantitySample
 @abstract      An HKObject subclass representing a quantity measurement.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKQuantitySample : HKSample

@property (readonly, copy) HKQuantityType *quantityType;
@property (readonly, copy) HKQuantity *quantity;

/*!
 @property      count
 @abstract      The number of individual values making up the receiver's quantity.
 @discussion    Requests for the individual series quantities can be made using HKQuantitySeriesSampleQuery.
 */
@property (readonly, assign) NSInteger count API_AVAILABLE(ios(12.0), watchos(5.0));

/*!
 @method        quantitySampleWithType:quantity:startDate:endDate:
 @abstract      Creates a new HKQuantitySample with the given type, quantity, start date, and end date.
 @discussion    The quantity must have a unit that is compatible with the given quantity type.
                See -[HKQuantityType isCompatibleWithUnit:].
 */
+ (instancetype)quantitySampleWithType:(HKQuantityType *)quantityType
                              quantity:(HKQuantity *)quantity
                             startDate:(NSDate *)startDate
                               endDate:(NSDate *)endDate;

/*!
 @method        quantitySampleWithType:quantity:startDate:endDate:metadata:
 @abstract      Creates a new HKQuantitySample with the given type, quantity, start date, end date, and metadata.
 @discussion    The quantity must have a unit that is compatible with the given quantity type.
                See -[HKQuantityType isCompatibleWithUnit:].
 */
+ (instancetype)quantitySampleWithType:(HKQuantityType *)quantityType
                              quantity:(HKQuantity *)quantity
                             startDate:(NSDate *)startDate
                               endDate:(NSDate *)endDate
                              metadata:(nullable NSDictionary<NSString *, id> *)metadata;

/*!
 @method        quantitySampleWithType:quantity:startDate:endDate:device:metadata:
 @abstract      Creates a new HKQuantitySample with the given type, quantity, start date, end date, and metadata.
 @param         quantityType    The type of the sample.
 @param         startDate       The start date of the sample.
 @param         endDate         The end date of the sample.
 @param         device          The HKDevice that generated the sample (optional).
 @param         metadata        Metadata for the sample (optional).
 @discussion    The quantity must have a unit that is compatible with the given quantity type.
                See -[HKQuantityType isCompatibleWithUnit:].
 */
+ (instancetype)quantitySampleWithType:(HKQuantityType *)quantityType
                              quantity:(HKQuantity *)quantity
                             startDate:(NSDate *)startDate
                               endDate:(NSDate *)endDate
                                device:(nullable HKDevice *)device
                              metadata:(nullable NSDictionary<NSString *, id> *)metadata API_AVAILABLE(ios(9.0), watchos(2.0));

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathQuantity API_AVAILABLE(ios(8.0), watchos(2.0));

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKDefines.h
//
//  HKDefines.h
//  HealthKit
//
//  Copyright (c) 2013-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#if !defined(__cplusplus)
#define HK_EXTERN extern __attribute__((visibility("default")))
#else
#define HK_EXTERN extern "C" __attribute__((visibility("default")))
#endif

HK_EXTERN NSString * const HKErrorDomain API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @enum      HKErrorCode
 
 @constant  HKNoError                           No error.
 @constant  HKErrorHealthDataUnavailable        HealthKit is not available on this device.
 @constant  HKErrorHealthDataRestricted         HealthKit is restricted on this device.
 @constant  HKErrorInvalidArgument              An invalid argument was provided to the API.
 @constant  HKErrorAuthorizationDenied          The application is not authorized to perform the requested operation.
 @constant  HKErrorAuthorizationNotDetermined   The user has not yet chosen whether the application is authorized to
                                                perform the requested operation.
 @constant  HKErrorDatabaseInaccessible         Protected health data is inaccessible because the device is locked.
 @constant  HKErrorUserCanceled                 The user canceled the operation.
 @constant  HKErrorAnotherWorkoutSessionStarted Another workout session was started by this or another application.
 @constant  HKErrorUserExitedWorkoutSession     User exited the application while a workout session was running.
 @constant  HKErrorRequiredAuthorizationDenied  The user has not granted the application authorization to access
                                                required data types.
 */
typedef NS_ENUM(NSInteger, HKErrorCode) {
    HKNoError = 0,
    HKErrorHealthDataUnavailable,
    HKErrorHealthDataRestricted,
    HKErrorInvalidArgument,
    HKErrorAuthorizationDenied,
    HKErrorAuthorizationNotDetermined,
    HKErrorDatabaseInaccessible,
    HKErrorUserCanceled,
    HKErrorAnotherWorkoutSessionStarted     API_AVAILABLE(ios(9.0), watchos(2.0)),
    HKErrorUserExitedWorkoutSession         API_AVAILABLE(ios(9.0), watchos(2.0)),
    HKErrorRequiredAuthorizationDenied      API_AVAILABLE(ios(12.0), watchos(5.0)),
} API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @enum      HKUpdateFrequency
 */
typedef NS_ENUM(NSInteger, HKUpdateFrequency) {
    HKUpdateFrequencyImmediate = 1,
    HKUpdateFrequencyHourly,
    HKUpdateFrequencyDaily,
    HKUpdateFrequencyWeekly,
} API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @enum      HKAuthorizationStatus
 @abstract  This enumerated type is used to indicate the currently granted authorization status for a specific
            HKObjectType.
 
 @constant  HKAuthorizationStatusNotDetermined      The user has not yet made a choice regarding whether this 
                                                    application may save objects of the specified type.
 @constant  HKAuthorizationStatusSharingDenied      This application is not allowed to save objects of the specified type.
 @constant  HKAuthorizationStatusSharingAuthorized  This application is authorized to save objects of the specified type.
 */
typedef NS_ENUM(NSInteger, HKAuthorizationStatus) {
    HKAuthorizationStatusNotDetermined = 0,
    HKAuthorizationStatusSharingDenied,
    HKAuthorizationStatusSharingAuthorized,
} API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @enum      HKAuthorizationRequestStatus
 @abstract  This enumerated type is used to indicate whether it is necessary to request authorization from the user.
 
 @constant  HKAuthorizationRequestStatusUnknown         The authorization request status could not be determined because
                                                        an error occurred.
 @constant  HKAuthorizationRequestStatusShouldRequest   The application should request authorization from the user.
 @constant  HKAuthorizationRequestStatusUnnecessary     Requesting authorization from the user is unnecessary.
 */
typedef NS_ENUM(NSInteger, HKAuthorizationRequestStatus) {
    HKAuthorizationRequestStatusUnknown = 0,
    HKAuthorizationRequestStatusShouldRequest,
    HKAuthorizationRequestStatusUnnecessary,
} API_AVAILABLE(ios(12.0), watchos(5.0));

/*!
 @enum       HKBiologicalSex
 @abstract   This enumerated type is used to represent the biological sex of an individual.
 */
typedef NS_ENUM(NSInteger, HKBiologicalSex) {
    HKBiologicalSexNotSet = 0,
    HKBiologicalSexFemale,
    HKBiologicalSexMale,
    HKBiologicalSexOther API_AVAILABLE(ios(8.2), watchos(2.0)),
} API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @enum       HKBloodType
 @abstract   This enumerated type is used to represent the blood type of an individual.
 */
typedef NS_ENUM(NSInteger, HKBloodType) {
    HKBloodTypeNotSet = 0,
    HKBloodTypeAPositive,
    HKBloodTypeANegative,
    HKBloodTypeBPositive,
    HKBloodTypeBNegative,
    HKBloodTypeABPositive,
    HKBloodTypeABNegative,
    HKBloodTypeOPositive,
    HKBloodTypeONegative,
} API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @enum          HKCategoryValueSleepAnalysis
 @abstract      Set of values that may be used for HKCategorySamples with the HKCategoryTypeIdentifierSleepAnalysis type.
 @discussion    To represent the user being both in bed and asleep, use two or more samples with overlapping times. By comparing the 
                start and end times of these samples, it is possible to calculate a number of secondary statistics: 
                1) The amount of time it took for the user to fall asleep
                2) The percentage of time in bed that the user actually spent sleeping,
                3) The number of times the user woke while in bed
                4) The total amount of time spent both in bed and asleep.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueSleepAnalysis) {
    HKCategoryValueSleepAnalysisInBed,
    HKCategoryValueSleepAnalysisAsleep,
    HKCategoryValueSleepAnalysisAwake API_AVAILABLE(ios(10.0), watchos(3.0)),
} API_AVAILABLE(ios(8.0), watchos(2.0));


/*!
 @enum          HKCategoryValueAppleStandHour
 @abstract      Set of values that may be used for HKCategorySamples with the HKCategoryTypeIdentifierAppleStandHour type.
 
 @constant      HKCategoryValueAppleStandHourStood  The user stood up and moved a little for at least one minute during
                                                    the sample.
 @constant      HKCategoryValueAppleStandHourIdle   The user did not stand up and move a little for at least one
                                                    continuous minute during the sample.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueAppleStandHour) {
    HKCategoryValueAppleStandHourStood = 0,
    HKCategoryValueAppleStandHourIdle,
} API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @enum          HKFitzpatrickSkinType
 @abstract      This enumerated type is used to represent the skin type of an individual based on the Fitzpatrick scale.
 @discussion    The Fitzpatrick scale is a numerical classification for skin color based on the skin's response to sun
                exposure in terms of the degree of burning and tanning.

 @constant      HKFitzpatrickSkinTypeI      Pale white skin that always burns easily in the sun and never tans.
 @constant      HKFitzpatrickSkinTypeII     White skin that burns easily and tans minimally.
 @constant      HKFitzpatrickSkinTypeIII    White to light brown skin that burns moderately and tans uniformly.
 @constant      HKFitzpatrickSkinTypeIV     Beige-olive, lightly tanned skin that burns minimally and tans moderately.
 @constant      HKFitzpatrickSkinTypeV      Brown skin that rarely burns and tans profusely.
 @constant      HKFitzpatrickSkinTypeVI     Dark brown to black skin that never burns and tans profusely.
 */
typedef NS_ENUM(NSInteger, HKFitzpatrickSkinType) {
    HKFitzpatrickSkinTypeNotSet = 0,
    HKFitzpatrickSkinTypeI,
    HKFitzpatrickSkinTypeII,
    HKFitzpatrickSkinTypeIII,
    HKFitzpatrickSkinTypeIV,
    HKFitzpatrickSkinTypeV,
    HKFitzpatrickSkinTypeVI,
} API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @enum          HKWheelchairUse
 @abstract      This enumerated type is used to represent whether the user uses a wheelchair.
 
 @constant      HKWheelchairUseNo      The user does not use a wheelchair.
 @constant      HKWheelchairUseYes     The user does use a wheelchair.
 */
typedef NS_ENUM(NSInteger, HKWheelchairUse) {
    HKWheelchairUseNotSet = 0,
    HKWheelchairUseNo,
    HKWheelchairUseYes,
} API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @enum          HKCategoryValueCervicalMucusQuality
 @abstract      Set of values that may be used for HKCategorySamples with the HKCategoryValueCervicalMucusQuality type.
 @discussion    These cervical mucus quality values are ordered from least-fertile (Dry) to most-fertile (EggWhite).
 */
typedef NS_ENUM(NSInteger, HKCategoryValueCervicalMucusQuality) {
    HKCategoryValueCervicalMucusQualityDry = 1,
    HKCategoryValueCervicalMucusQualitySticky,
    HKCategoryValueCervicalMucusQualityCreamy,
    HKCategoryValueCervicalMucusQualityWatery,
    HKCategoryValueCervicalMucusQualityEggWhite,
} API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @enum          HKCategoryValueOvulationTestResult
 @abstract      Set of values that may be used for HKCategorySamples with the HKCategoryValueOvulationTestResult type.
 @discussion    This category value tracks the result of a home ovulation test that use surges in luteinizing hormone 
                levels to indicate fertility.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueOvulationTestResult) {
    HKCategoryValueOvulationTestResultNegative = 1,
    HKCategoryValueOvulationTestResultPositive,
    HKCategoryValueOvulationTestResultIndeterminate,
} API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @enum          HKCategoryValueMenstrualFlow
 @abstract      Set of values to indicate the type of menstrual flow.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueMenstrualFlow) {
    HKCategoryValueMenstrualFlowUnspecified = 1,
    HKCategoryValueMenstrualFlowLight,
    HKCategoryValueMenstrualFlowMedium,
    HKCategoryValueMenstrualFlowHeavy,
    HKCategoryValueMenstrualFlowNone API_AVAILABLE(ios(12.0), watchos(5.0)),
} API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @enum          HKCategoryValue
 @abstract      This category value is to be used for types which don't have a specific value defined.
 */
typedef NS_ENUM(NSInteger, HKCategoryValue) {
    HKCategoryValueNotApplicable = 0,
} API_AVAILABLE(ios(9.0), watchos(2.0));

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKSeriesSample.h
//
//  HKSeriesSample.h
//  HealthKit
//
//  Copyright (c) 2015 Apple. All rights reserved.
//

#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 @class         HKSeriesSample
 @abstract      This class represents a type of HKSample that references a series of data.
 */
HK_EXTERN
@interface HKSeriesSample : HKSample

/*!
 @property      count
 @abstract      The number of individual series datum represented by the receiver and accessible
                through the appropriate HKQuery series subclass.
 */
@property (readonly) NSUInteger count;

@end


NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKDevice.h
//
//  HKDevice.h
//  HealthKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @constant      HKDevicePropertyKeyName
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a device name.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyName API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @constant      HKDevicePropertyKeyManufacturer
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a device manufacturer.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyManufacturer API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @constant      HKDevicePropertyKeyModel
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a device model.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyModel API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @constant      HKDevicePropertyKeyHardwareVersion
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a hardware version.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyHardwareVersion API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @constant      HKDevicePropertyKeyFirmwareVersion
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a firmware version.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyFirmwareVersion API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @constant      HKDevicePropertyKeySoftwareVersion
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a software version.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeySoftwareVersion API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @constant      HKDevicePropertyKeyLocalIdentifier
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a local identifier.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyLocalIdentifier API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @constant      HKDevicePropertyKeyUDIDeviceIdentifier
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a UDI device identifier.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyUDIDeviceIdentifier API_AVAILABLE(ios(9.0), watchos(2.0));



HK_EXTERN API_AVAILABLE(ios(9.0), watchos(2.0))
@interface HKDevice : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      name
 @abstract      The name of the receiver.
 @discussion    The user-facing name, such as the one displayed in the Bluetooth Settings for a BLE device.
 */
@property (readonly, nullable) NSString *name;

/*!
 @property      manufacturer
 @abstract      The manufacturer of the receiver.
 */
@property (readonly, nullable) NSString *manufacturer;

/*!
 @property      model
 @abstract      The model of the receiver.
 */
@property (readonly, nullable) NSString *model;

/*!
 @property      hardwareVersion
 @abstract      The hardware revision of the receiver.
 */
@property (readonly, nullable) NSString *hardwareVersion;

/*!
 @property      firmwareVersion
 @abstract      The firmware revision of the receiver.
 */
@property (readonly, nullable) NSString *firmwareVersion;

/*!
 @property      softwareVersion
 @abstract      The software revision of the receiver.
 */
@property (readonly, nullable) NSString *softwareVersion;

/*!
 @property      localIdentifier
 @abstract      A unique identifier for the receiver.
 @discussion    This property is available to clients for a local identifier.
                For example, Bluetooth peripherals managed by HealthKit use this
                for the CoreBluetooth UUID which is valid only on the local
                device and thus distinguish the same Bluetooth peripheral used
                between multiple devices.
 */
@property (readonly, nullable) NSString *localIdentifier;

/*!
 @property      UDIDeviceIdentifier
 @abstract      Represents the device identifier portion of a device's FDA UDI (Unique Device Identifier).
 @discussion    The device identifier can be used to reference the FDA's GUDID (Globally Unique Device
                Identifier Database). Note that for user privacy concerns this field should not be used to
                persist the production identifier portion of the device UDI. HealthKit clients should manage
                the production identifier independently, if needed.
                See http://www.fda.gov/MedicalDevices/DeviceRegulationandGuidance/UniqueDeviceIdentification/ for more information.
 */
@property (readonly, nullable) NSString *UDIDeviceIdentifier;


/*!
 @method        initWithName:manufacturer:model:hardwareVersion:firmwareVersion:softwareVersion:localIdentifier:UDIDeviceIdentifier:
 @abstract      Initialize a new HKDevice with the specified values.
 @discussion    This allows initialization of an HKDevice object based on the
                information provided.
 */
- (instancetype)initWithName:(nullable NSString *)name
                manufacturer:(NSString * _Nullable)manufacturer
                       model:(NSString * _Nullable)model
             hardwareVersion:(NSString * _Nullable)hardwareVersion
             firmwareVersion:(NSString * _Nullable)firmwareVersion
             softwareVersion:(NSString * _Nullable)softwareVersion
             localIdentifier:(NSString * _Nullable)localIdentifier
         UDIDeviceIdentifier:(NSString * _Nullable)UDIDeviceIdentifier;

- (instancetype)init NS_UNAVAILABLE;

/*!
 @method        localDevice
 @abstract      Returns a device representing the host.
 @discussion    If an app chooses to save samples that were retrieved from the local device, e.g. an HKWorkout with a 
                totalDistance HKQuantity gathered from CoreLocation GPS distances, then this would be an appropriate 
                HKDevice to use.
 */
+ (HKDevice *)localDevice;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKWorkoutSession.h
//
//  HKWorkoutSession.h
//  HealthKit
//
//  Copyright (c) 2015-2018 Apple. All rights reserved.
//

#import <HealthKit/HKLiveWorkoutBuilder.h>
#import <HealthKit/HKMetadata.h>
#import <HealthKit/HKWorkout.h>
#import <HealthKit/HKWorkoutBuilder.h>
#import <HealthKit/HKWorkoutConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class HKHealthStore;
@class HKLiveWorkoutBuilder;
@protocol HKWorkoutSessionDelegate;

/*!
 @enum          HKWorkoutSessionState
 @abstract      This enumerated type is used to represent the state of a workout session.
 */
typedef NS_ENUM(NSInteger, HKWorkoutSessionState) {
    HKWorkoutSessionStateNotStarted = 1,
    HKWorkoutSessionStateRunning,
    HKWorkoutSessionStateEnded,
    HKWorkoutSessionStatePaused API_AVAILABLE(watchos(3.0)),
    HKWorkoutSessionStatePrepared API_AVAILABLE(watchos(5.0)),
    HKWorkoutSessionStateStopped API_AVAILABLE(watchos(5.0)),
} API_AVAILABLE(watchos(2.0)) __IOS_PROHIBITED;


/*!
 @class         HKWorkoutSession
 @abstract      An HKWorkoutSession is an object describing the properties of a workout activity session.
 */
HK_EXTERN API_AVAILABLE(watchos(2.0)) __IOS_PROHIBITED
@interface HKWorkoutSession : NSObject <NSSecureCoding>

/*!
 @property      activityType
 @abstract      Indicates the type of workout that will be performed during the session.
 */
@property (readonly) HKWorkoutActivityType activityType API_DEPRECATED_WITH_REPLACEMENT("workoutConfiguration", watchos(2.0, 3.0));

/*!
 @property      locationType
 @abstract      Indicates the type of location (indoors vs. outdoors) where the workout will take place.
 @discussion    Knowing the location type allows for more accurate measurements and better performance.
 */
@property (readonly) HKWorkoutSessionLocationType locationType API_DEPRECATED_WITH_REPLACEMENT("workoutConfiguration", watchos(2.0, 3.0));

/*!
 @property      workoutConfiguration
 @abstract      The configuration object describing the workout.
 @discussion    This returns a copy of the configuration passed when creating the HKWorkoutSession. Changes made to
                the returned object have no impact on the HKWorkoutSession.
 */
@property (readonly, copy) HKWorkoutConfiguration *workoutConfiguration API_AVAILABLE(watchos(3.0));

/*!
 @property      delegate
 @abstract      The session delegate, which receives
 @discussion    The session delegate object is the one implementing the methods that get called when the session
                state changes or a failure occurs in the session.
 */
@property (weak, nullable) id<HKWorkoutSessionDelegate> delegate;

/*!
 @property      state
 @abstract      Indicates the current state of the workout session.
 @discussion    Each time this value is updated, the delegate method workoutSession:didChangeToState:fromState:date:
                will be called.
 */
@property (readonly) HKWorkoutSessionState state;

/*!
 @property      startDate
 @abstract      Indicates the date when the workout session started running.
 @discussion    This value is nil when a workout session is initialized. It is set when the workout session state
                changes to HKWorkoutSessionStateRunning.
 */
@property (readonly, nullable) NSDate *startDate;

/*!
 @property      endDate
 @abstract      Indicates the date when the workout session ended.
 @discussion    This value is nil when a workout session is initialized. It is set when the workout session state
                changes to HKWorkoutSessionStateEnded.
 */
@property (readonly, nullable) NSDate *endDate;

/*!
 @method        initWithActivityType:locationType:

 @param         activityType    The activity type of the workout session.
 @param         locationType    The type of location where the workout will be performed.
 */
- (instancetype)initWithActivityType:(HKWorkoutActivityType)activityType
                        locationType:(HKWorkoutSessionLocationType)locationType API_DEPRECATED_WITH_REPLACEMENT("initWithHealthStore:configuration:error:", watchos(2.0, 3.0));

/*!
 @method        initWithConfiguration:error:
 
 @param         workoutConfiguration Configuration object describing the various properties of a workout.
 @param         error                If the configuration does not specify valid configuration properties, an
                                     an NSError describing the error is set and nil is returned.
 */
- (nullable instancetype)initWithConfiguration:(HKWorkoutConfiguration *)workoutConfiguration error:(NSError **)error API_DEPRECATED_WITH_REPLACEMENT("initWithHealthStore:configuration:error:", watchos(3.0, 5.0));

/*!
 @method        initWithHealthStore:configuration:error:
 
 @param         healthStore          Specifies the HKHealthStore object to use.
 @param         workoutConfiguration Configuration object describing the various properties of a workout.
 @param         error                If the configuration does not specify valid configuration properties, an
                                     an NSError describing the error is set and nil is returned.
 */
- (nullable instancetype)initWithHealthStore:(HKHealthStore *)healthStore
                               configuration:(HKWorkoutConfiguration *)workoutConfiguration
                                       error:(NSError **)error API_AVAILABLE(watchos(5.0));

- (instancetype)init NS_UNAVAILABLE;

/*!
 @method        prepare
 @abstract      Prepares the workout session for starting.
 @discussion    This method will asynchronously prepare the workout session for starting. The state of the workout session
                will transition to HKWorkoutSessionStatePrepared. A prepared session will put the system in session mode,
                but will not start the session activity.
                You might call this methods, for example, prior to displaying a countdown on your application while waiting
                for the activity to start.
 */
- (void)prepare API_AVAILABLE(watchos(5.0));

/*!
 @method        startActivityWithDate:

 @param         date                Start date for the workout session activity
 @abstract      Starts the workout session activity.
 @discussion    This method will asynchronously begin the workout session activity. The state of the workout session will
                transition to HKWorkoutSessionStateRunning. Once a session activity is started the system will be in session
                mode and sensor algorithms will be applied to generate data for the workout activity.
 */
- (void)startActivityWithDate:(nullable NSDate *)date API_AVAILABLE(watchos(5.0));

/*!
 @method        stopActivityWithDate:
 @param         date                Stop date for the workout session activity
 @abstract      Stops the workout session activity.
 @discussion    This method will asynchronously stop the session activity if it is currently running. The state of the workout
                session will transition to HKWorkoutSessionStateStopped. Once a workout session is stopped, it cannot be reused to
                start a new workout session. Sensor algorithms will be stopped and no new data will be generated for this session.
                However, the system will remain in session mode.
 */
- (void)stopActivityWithDate:(nullable NSDate *)date API_AVAILABLE(watchos(5.0));

/*!
 @method        end
 @abstract      Ends the workout session.
 @discussion    This method will end the session if it is currently running or stopped. The state of the workout session will
                transition to HKWorkoutSessionStateEnded. Once a workout session is ended, it cannot be reused to start a new
                workout session. Sensor algorithms will be stopped, no new data will be generated for this session, and the
                system will exit session mode.
 */
- (void)end API_AVAILABLE(watchos(5.0));

/*!
 @method        pause
 @abstract      Pauses the workout session.
 @discussion    This method will pause the session if it is currently running. The state of the workout session
                will transition to HKWorkoutSessionStatePaused. An HKWorkoutEventTypePause will be generated and
                delivered to the workout session's delegate.
 */
- (void)pause API_AVAILABLE(watchos(5.0));

/*!
 @method        resume
 @abstract      Resumes the workout session.
 @discussion    This method will resume the session if it is currently paused. The state of the workout session
                will transition to HKWorkoutSessionStateRunning. An HKWorkoutEventTypeResume will be generated and
                delivered to the workout session's delegate.
 */
- (void)resume API_AVAILABLE(watchos(5.0));

/*!
 @method        associatedWorkoutBuilder
 @abstract      Retrieves (and creates if necessary) an HKLiveWorkoutBuilder associated with this session.
 @discussion    A session may have associated with it an HKLiveWorkoutBuilder that will be used to record the workout
                for this session. This method will return the session's associated builder, creating it if needed.
                Calling this method more than once will return the previously-created builder. If this session was not
                initialized with initWithHealthStore:configuration:error:, an exception will be thrown.
 */
- (HKLiveWorkoutBuilder *)associatedWorkoutBuilder API_AVAILABLE(watchos(5.0));

@end


/*!
 @enum          HKWorkoutSessionStateDelegate
 @abstract      This protocol should be implemented to be notified when a workout session's state changes.
 @discussion    The methods on this protocol are called on an anonymous serial background queue.
 */
API_AVAILABLE(watchos(2.0)) __IOS_PROHIBITED
@protocol HKWorkoutSessionDelegate <NSObject>

/*!
 @method        workoutSession:didChangeToState:fromState:date:
 @abstract      This method is called when a workout session transitions to a new state.
 @discussion    The date is provided to indicate when the state change actually happened.  If your application is
                suspended then the delegate will receive this call once the application resumes, which may be much later
                than when the original state change ocurred.
 */
- (void)workoutSession:(HKWorkoutSession *)workoutSession
      didChangeToState:(HKWorkoutSessionState)toState
             fromState:(HKWorkoutSessionState)fromState
                  date:(NSDate *)date;

/*!
 @method        workoutSession:didFailWithError:
 @abstract      This method is called when an error occurs that stops a workout session.
 @discussion    When the state of the workout session changes due to an error occurring, this method is always called
                before workoutSession:didChangeToState:fromState:date:.
 */
- (void)workoutSession:(HKWorkoutSession *)workoutSession didFailWithError:(NSError *)error;

@optional

/*!
 @method        workoutSession:didGenerateEvent:
 @abstract      This method is called whenever the system generates a workout event.
 @discussion    Whenever a workout event is generated, such as pause or resume detection, the event will be passed
                to the session delegate via this method. Clients may save the generated events to use when creating an
                HKWorkout object.
 */
- (void)workoutSession:(HKWorkoutSession *)workoutSession didGenerateEvent:(HKWorkoutEvent *)event API_AVAILABLE(ios(10.0), watchos(3.0));

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKWorkoutRouteBuilder.h
//
//  HKWorkoutRouteBuilder.h
//  HealthKit
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <HealthKit/HKSeriesBuilder.h>
#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HKHealthStore;
@class HKDevice;
@class HKWorkout;
@class HKWorkoutRoute;
@class CLLocation;

/*!
 @class              HKWorkoutRouteBuilder
 @abstract           An HKWorkoutRouteBuilder is used to generate an HKWorkoutRoute.
 @discussion         This class is intended for generating long-running location data collection such as
                     might be associated with a workout. If the discard method is called, collected data will be deleted.
                     Calling finishRouteWithWorkout:metadata: will stop and complete the route. If the builder is deleted,
                     or the client goes away before calling the finish method, data will be lost.
 */
HK_EXTERN API_AVAILABLE(ios(11.0), watchos(4.0))
@interface HKWorkoutRouteBuilder : HKSeriesBuilder

/*!
 @method             initWithHealthStore:device:
 @abstract           The designated initializer to create an HKWorkoutRouteBuilder. If you are using an HKWorkoutBuilder , you
                     should not create an HKWorkoutRouteBuilder, instead use -[HKWorkoutBuilder seriesBuilderForType:]
 @discussion         The HKHealthStore is retained during the life of the object for the saving of the series data and final
                     return of the series sample.
 
 @param healthStore  Specifies the HKHealthStore object to use for building the series.
 @param device       The optional device represents the HKDevice from which the data is provided.
 */
- (instancetype)initWithHealthStore:(HKHealthStore *)healthStore
                             device:(nullable HKDevice *)device;

/*!
 @method             insertRouteData:completion:
 @abstract           Associate CLLocation with the receiver.
 @discussion         Use this method to asynchronously add one or more CLLocation to the
                     series. Note that CLLocation may be inserted in any order but will be
                     sorted according to date when the series is finalized.
 
 @param routeData    An array of one or more CLLocation.
 @param completion   The completion callback handler returns the status of the save. If the completion handler success is
                     NO, then error is non-nil. An error here is considered fatal and the series builder will be complete.
                     If data was previously saved, then the HKWorkoutRoute may be retrieved by the
                     finishRouteWithMetadata: method.
 */
- (void)insertRouteData:(NSArray<CLLocation *> *)routeData
             completion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*!
 @method             addMetadata:completion:
 @discussion         Adds new metadata to the builder instance. This method can be called more than once; each time
                     the newly provided metadata will be incorporated in the same manner as
                     -[NSMutableDictionary addEntriesFromDictionary:].
                     This operation is performed asynchronously and the completion will be executed on an arbitrary
                     background queue.
 
 @param metadata     The metadata to add to the builder.
 @param completion   Block to be called when the addition of metadata to the builder is complete. If success is YES, the
                     metadata has been added to the builder successfully. If success is NO, error will be non-null and
                     will contain the error encountered during the insertion operation. When an error occurs, the builder's
                     metadata will remain unchanged.
 */
- (void)addMetadata:(NSDictionary<NSString *, id> *)metadata completion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*!
 @method             finishRouteWithWorkout:Metadata:completion:
 @abstract           Method to stop data collection and return the associated HKWorkoutRoute. If you are using this route
                     builder with a workout builder, you should never call this method. The route will be finished when you
                     finish the workout builder.
 @discussion         Call this method when the route has been completed. The completion handler will return the saved
 HKWorkoutRoute.     If no series data was added, then workoutRoute will be nil and an error returned. The
                     receiver will be considered invalid afterwards and any further calls to it will result in an error.
 
 @param workout      The HKWorkout object to which the route will be associated. Must be saved to HealthKit
 @param metadata     Optional metadata may be added to associate with the series. Predefined keys are found in
                     HKMetadata.h, or private NSString keys used by the client are allowed. Acceptable metadata value
                     types are NSString, NSDate, NSNumber and HKQuantity
 @param completion   The completion callback handler returns the saved HKWorkoutRoute object. If workoutRoute is nil, an
                     error will indicate why the series could not be returned including database inaccessibility during
                     device lock. Subsequent requests for the HKWorkoutRoute can be made through HKSampleQuery or similar
                     queries. workoutRoute cannot be associated to another workout.
 */
- (void)finishRouteWithWorkout:(HKWorkout *)workout
                      metadata:(nullable NSDictionary<NSString *, id> *)metadata
                    completion:(void(^)(HKWorkoutRoute * _Nullable workoutRoute, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKQuantitySeriesSampleBuilder.h
//
//  HKQuantitySeriesSampleBuilder.h
//  HealthKit
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HKDevice;
@class HKHealthStore;
@class HKQuantity;
@class HKQuantitySample;
@class HKQuantityType;

/*!
 @class         HKQuantitySeriesSampleBuilder
 @abstract      An HKQuantitySeriesSampleBuilder is used to generate HKQuantitySample(s) with multiple
                quantities.
 @discussion    An HKQuantitySeriesSampleBuilder is used to incrementally create a new quantity series
                sample in the HealthKit database. This class may be used to create long-running quantity
                series samples that are associated with an activity like a workout. After inserting each
                of the quantities that make up the series, the series may be finalized by calling
                -finishSeriesWithMetadata:completion:. Calling -discard invalidates the series and
                discards any data that was previously associated with it.
 */
HK_EXTERN API_AVAILABLE(ios(12.0), watchos(5.0))
@interface HKQuantitySeriesSampleBuilder : NSObject

/*!
 @method        initWithHealthStore:quantityType:device:
 @abstract      The designated initializer to create an HKQuantitySeriesSampleBuilder.
 @discussion    The HKHealthStore is retained during the life of the object for the saving of the
                series data and final return of the series sample.

 @param         healthStore     Specifies the HKHealthStore object to use for building the series.
 @param         quantityType    Specifies the quantity type for which to build the series.
                                The type can be any HKQuantityType with aggregationStyle
                                HKQuantityAggregationStyleCumulative.
 @param         startDate       The date from which the produced sample(s) start.
 @param         device          The optional device represents the HKDevice from which the data is
                                provided.
 */
- (instancetype)initWithHealthStore:(HKHealthStore *)healthStore
                       quantityType:(HKQuantityType *)quantityType
                          startDate:(NSDate *)startDate
                             device:(nullable HKDevice *)device NS_SWIFT_NAME(init(healthStore:quantityType:startDate:device:));

- (instancetype)init NS_UNAVAILABLE;

/*!
 @property      quantityType
 */
@property (readonly, copy) HKQuantityType *quantityType;

/*!
 @property      startDate
 */
@property (readonly, copy) NSDate *startDate;

/*!
 @property      device
 */
@property (readonly, copy, nullable) HKDevice *device;


/*!
 @method            insertQuantity:date:completion:
 @abstract          Associate a new quantity with the receiver at a specific date.
 @discussion        Use this method to add a quantity to the series. The quantity must have a unit
                    that is compatible with the receiver's quantity type.
                    See -[HKQuantityType isCompatibleWithUnit:].
                    Note that quantities may be inserted in any order, but will be sorted according
                    to date when the series is finished.

 @param             quantity    The quantity to insert.
 @param             date        The date associated with the quantity. If this is the same date
                                as a previously-provided quantity, the new value will replace
                                the old value. An HKErrorInvalidArgument will be returned if date
                                is earlier than the receiver's startDate.
 */
- (BOOL)insertQuantity:(HKQuantity *)quantity
                  date:(NSDate *)date
                 error:(NSError **)error NS_SWIFT_NAME(insert(_:at:));

/*!
 @method            finishSeriesWithMetadata:completion:
 @abstract          Finalizes the series and returns the resulting HKQuantitySample(s).
 @discussion        Call this method when all quantities for the series have been inserted.
                    The completion handler will return the resulting HKQuantitySample(s)
                    Note that it is possible for a single HKQuantitySeriesSampleBuilder to produce
                    multiple samples. If no quantity data was added, then samples will be nil and
                    an error will be returned. After calling this method, the receiver will be
                    considered invalid and calling any other method will result in an error.

 @param             metadata    Optional metadata may be added to associate with the series.
                                Predefined keys are found in HKMetadata.h, or custom NSString
                                keys used by the client are allowed. Acceptable metadata value types
                                are NSString, NSDate, NSNumber and HKQuantity.
 @param             completion  The completion handler will return the resulting HKQuantitySample(s)
                                for the series. Note that it is possible for a single
                                HKQuantitySeriesSampleBuilder to produce multiple samples.
                                If data could not be inserted because of an authorization failure,
                                samples will be nil and and an error with code
                                HKErrorAuthorizationDenied or HKErrorAuthorizationNotDetermined
                                will be returned. If the resulting sample(s) could not be accessed
                                after they have been created, then samples will be nil and an error
                                with code HKErrorDatabaseInaccessible will be returned. Any other
                                error indicates the resulting samples could not be returned.
                                After calling this method, the receiver will be considered invalid
                                and calling any other method will result in an error.
 */
- (void)finishSeriesWithMetadata:(nullable NSDictionary<NSString *, id> *)metadata
                      completion:(void(^)(NSArray<__kindof HKQuantitySample *> * _Nullable samples, NSError * _Nullable error))completion NS_SWIFT_NAME(finishSeries(metadata:completion:));

/*!
 @method            discard
 @abstract          Discards all previously inserted data and invalidates the series.
 @discussion        Calling this method will delete all quantities that were previously inserted into
                    the series and invalidate the receiver. Calling other methods on the receiver
                    after calling -discard will result in an exception.
 */
- (void)discard;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKCorrelationQuery.h
//
//  HKCorrelationQuery.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

@class HKCorrelationType;
@class HKCorrelation;

/*!
 @class         HKCorrelationQuery
 @abstract      A query to find HKCorrelations
 @discussion    Correlations are HKSamples that contain a set of correlated samples. HKCorrelationQuery
                accepts a predicate to filter HKCorrelations and a dictionary of predicates to filter the
                correlated samples.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKCorrelationQuery : HKQuery

@property (readonly, copy) HKCorrelationType *correlationType;
/*!
 @property      samplePredicates
 @abstract      A dictionary of predicates for the HKCorrelation's objects
 @discussion    samplePredicates maps HKSampleTypes to NSPredicates. The predicate value will apply
                to objects of the key type. 
 
 */
@property (readonly, copy, nullable) NSDictionary<__kindof HKSampleType *, NSPredicate *> *samplePredicates;

/*!
 @method    initWithTypes:predicate:samplePredicate:completion:
 @abstract  The designated initializer for HKCorrelationQuery.

 @param     correlationType     The type of correlation that is being queried for

 @param     predicate           The predicate for scoping which HKCorrelations are returned

 @param     samplePredicates    A dictionary mapping HKSampleTypes to NSPredicates. If no predicate for a particular type
                                is provided, it is assumed to be a nil predicate and objects of that type will not be
                                filtered.
 */
- (instancetype)initWithType:(HKCorrelationType *)correlationType
                   predicate:(nullable NSPredicate *)predicate
            samplePredicates:(nullable NSDictionary<HKSampleType *, NSPredicate *> *)samplePredicates
                  completion:(void(^)(HKCorrelationQuery *query, NSArray<HKCorrelation *> * _Nullable correlations, NSError * _Nullable error))completion;
@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKFHIRResource.h
//
//  HKFHIRResource.h
//  HealthKit
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * HKFHIRResourceType NS_TYPED_ENUM API_AVAILABLE(ios(12.0)) __WATCHOS_PROHIBITED;

HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeAllergyIntolerance API_AVAILABLE(ios(12.0)) __WATCHOS_PROHIBITED;
HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeCondition API_AVAILABLE(ios(12.0)) __WATCHOS_PROHIBITED;
HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeImmunization API_AVAILABLE(ios(12.0)) __WATCHOS_PROHIBITED;
HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeMedicationDispense API_AVAILABLE(ios(12.0)) __WATCHOS_PROHIBITED;
HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeMedicationOrder API_AVAILABLE(ios(12.0)) __WATCHOS_PROHIBITED;
HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeMedicationStatement API_AVAILABLE(ios(12.0)) __WATCHOS_PROHIBITED;
HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeObservation API_AVAILABLE(ios(12.0)) __WATCHOS_PROHIBITED;
HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeProcedure API_AVAILABLE(ios(12.0)) __WATCHOS_PROHIBITED;

/*!
 @class         HKFHIRResource
 @abstract      The HKFHIRResource class encapsulates a FHIR (Fast Healthcare Interoperability Resources) resource.
 */
HK_EXTERN API_AVAILABLE(ios(12.0)) __WATCHOS_PROHIBITED
@interface HKFHIRResource : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      resourceType
 @abstract      The resource type, corresponding to the 'resourceType' field in the resource's JSON representation.
 @discussion    May be one of 8 FHIR resource types supported within HealthKit: AllergyIntolerance, Condition,
                Immunization, MedicationDispense, MedicationOrder, MedicationStatement, Observation, and Procedure.
 */
@property (readonly, copy) HKFHIRResourceType resourceType;

/*!
 @property      identifier
 @abstract      The identifier of the resource, corresponding to the 'id' field in the resource's JSON representation.
 @discussion    Unique within a given resource type and FHIR end-point, as represented by an HKSource.
 */
@property (readonly, copy) NSString *identifier;

/*!
 @property      data
 @abstract      The JSON representation of the FHIR resource.
 @discussion    Conforms to the HL7 Argonaut Project resource type definitions.
 */
@property (readonly, copy) NSData *data;

/*!
 @property      sourceURL
 @abstract      The fully specified source URL of the FHIR resource.
 @discussion    This URL can be used to help determine the provenance of the resource. Direct access is protected by
                OAuth: querying without suitable authorization will result in an authorization error.
 */
@property (readonly, copy, nullable) NSURL *sourceURL;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKDeletedObject.h
//
//  HKDeletedObject.h
//  HealthKit
//
//  Copyright (c) 2015 Apple. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKDeletedObject
 @abstract      A class representing an HKObject that was deleted from the HealtKit database.
 */
HK_EXTERN API_AVAILABLE(ios(9.0), watchos(2.0))
@interface HKDeletedObject : NSObject <NSSecureCoding>

/*!
 @property      UUID
 @abstract      The unique identifier of the HKObject that was deleted from the HealthKit database.
 */
@property (readonly, strong) NSUUID *UUID;

/*!
 @property      metadata
 @abstract      Extra information describing properties of the receiver.
 @discussion    Metadata retained from the deleted HKObject.
                Available keys: HKMetadataKeySyncIdentifier, HKMetadataKeySyncVersion
 */
@property (readonly, copy, nullable) NSDictionary<NSString *, id> *metadata API_AVAILABLE(ios(11.0), watchos(4.0));

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKStatistics.h
//
//  HKStatistics.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;
@class HKQuantityType;
@class HKSource;

/*!
 @enum          HKStatisticsOptions
 @abstract      Options for specifying which statistics to calculate
 @discussion    When querying for HKStatistics objects, an options bitmask will specify which statistics will be 
                calculated.
 
                Statistics are classified as discrete or cumulative.  If a discrete statistics option is specified for a
                cumulative HKQuantityType, an exception will be thrown.  If a cumulative statistics options is specified
                for a discrete HKQuantityType, an exception will also be thrown.
 
 @constant      HKStatisticsOptionNone
 @constant      HKStatisticsOptionSeparateBySource
 @constant      HKStatisticsOptionDiscreteAverage      Calculate averageQuantity when creating statistics.
 @constant      HKStatisticsOptionDiscreteMin          Calculate minQuantity when creating statistics.
 @constant      HKStatisticsOptionDiscreteMax          Calculate maxQuantity when creating statistics.
 @constant      HKStatisticsOptionCumulativeSum        Calculate sumQuantity when creating statistics.
 @constant      HKStatisticsOptionDiscreteMostRecent   Calculate mostRecentQuantity when creating statistics.
 */
typedef NS_OPTIONS(NSUInteger, HKStatisticsOptions) {
    HKStatisticsOptionNone              		= 0,
    HKStatisticsOptionSeparateBySource          = 1 << 0,
    HKStatisticsOptionDiscreteAverage           = 1 << 1,
    HKStatisticsOptionDiscreteMin               = 1 << 2,
    HKStatisticsOptionDiscreteMax               = 1 << 3,
    HKStatisticsOptionCumulativeSum             = 1 << 4,
    HKStatisticsOptionDiscreteMostRecent API_AVAILABLE(ios(12.0), watchos(5.0))  = 1 << 5,
} API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @class         HKStatistics
 @abstract      Represents statistics for quantity samples over a period of time.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKStatistics : NSObject <NSSecureCoding, NSCopying>

@property (readonly, strong) HKQuantityType *quantityType;
@property (readonly, strong) NSDate *startDate;
@property (readonly, strong) NSDate *endDate;
@property (readonly, strong, nullable) NSArray<HKSource *> *sources;

- (instancetype)init NS_UNAVAILABLE;

/* Discrete Quantities */

/*!
 @method        averageQuantityForSource:
 @abstract      Returns the average quantity for the given source in the time period represented by the receiver.
 @discussion    If HKStatisticsOptionSeparateBySource is not specified, then this will always be nil.
 */
- (nullable HKQuantity *)averageQuantityForSource:(HKSource *)source;

/*!
 @method        averageQuantity
 @abstract      Returns the average quantity in the time period represented by the receiver.
 */
- (nullable HKQuantity *)averageQuantity;

/*!
 @method        minimumQuantityForSource:
 @abstract      Returns the minimum quantity for the given source in the time period represented by the receiver.
 @discussion    If HKStatisticsOptionSeparateBySource is not specified, then this will always be nil.
 */
- (nullable HKQuantity *)minimumQuantityForSource:(HKSource *)source;

/*!
 @method        minimumQuantity
 @abstract      Returns the minimum quantity in the time period represented by the receiver.
 */
- (nullable HKQuantity *)minimumQuantity;

/*!
 @method        maximumQuantityForSource:
 @abstract      Returns the maximum quantity for the given source in the time period represented by the receiver.
 @discussion    If HKStatisticsOptionSeparateBySource is not specified, then this will always be nil.
 */
- (nullable HKQuantity *)maximumQuantityForSource:(HKSource *)source;

/*!
 @method        maximumQuantity
 @abstract      Returns the maximum quantity in the time period represented by the receiver.
 */
- (nullable HKQuantity *)maximumQuantity;

/*!
 @method        mostRecentQuantityForSource:
 @abstract      Returns the most recent quantity for the given source in the time period represented by the receiver.
 @discussion    If HKStatisticsOptionSeparateBySource is not specified, then this will always be nil.
 */
- (nullable HKQuantity *)mostRecentQuantityForSource:(HKSource *)source API_AVAILABLE(ios(12.0), watchos(5.0));

/*!
 @method        mostRecentQuantity
 @abstract      Returns the most recent quantity in the time period represented by the receiver.
 */
- (nullable HKQuantity *)mostRecentQuantity API_AVAILABLE(ios(12.0), watchos(5.0));

/*!
 @method        mostRecentQuantityDateIntervalForSource:
 @abstract      Returns the date interval of the most recent quantity for the given source in the time period
                represented by the receiver.
 @discussion    If HKStatisticsOptionSeparateBySource is not specified, then this will always be nil.
 */
- (nullable NSDateInterval *)mostRecentQuantityDateIntervalForSource:(HKSource *)source API_AVAILABLE(ios(12.0), watchos(5.0));

/*!
 @method        mostRecentQuantityDateInterval
 @abstract      Returns the date interval of the most recent quantity in the time period represented by the receiver.
 */
- (nullable NSDateInterval *)mostRecentQuantityDateInterval API_AVAILABLE(ios(12.0), watchos(5.0));

/* Cumulative Quantities */

/*!
 @method        sumQuantityForSource:
 @abstract      Returns the sum quantity for the given source in the time period represented by the receiver.
 @discussion    If HKStatisticsOptionSeparateBySource is not specified, then this will always be nil.
 */
- (nullable HKQuantity *)sumQuantityForSource:(HKSource *)source;

/*!
 @method        sumQuantity
 @abstract      Returns the sum of quantities in the time period represented by the receiver.
 */
- (nullable HKQuantity *)sumQuantity;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKWorkoutRoute.h
//
//  HKWorkoutRoute.h
//  HealthKit
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <HealthKit/HKSeriesSample.h>

NS_ASSUME_NONNULL_BEGIN

HK_EXTERN API_AVAILABLE(ios(11.0), watchos(4.0))
@interface HKWorkoutRoute : HKSeriesSample
@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKSource.h
//
//  HKSource.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class     HKSource
 @abstract  Represents the entity that created an object stored by HealthKit.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKSource : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      name
 @abstract      The name of the source represented by the receiver.  If the source is an app, then the name is the
                localized name of the app.
 */
@property (readonly, strong) NSString *name;

/*!
 @property  bundleIdentifier
 @abstract  The bundle identifier of the source represented by the receiver.
 */
@property (readonly, strong) NSString *bundleIdentifier;

/*!
 @method    defaultSource
 @abstract  Returns the source representing the calling application.
 */
+ (HKSource *)defaultSource;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKWorkoutConfiguration.h
//
//  HKWorkoutConfiguration.h
//  HealthKit
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <HealthKit/HKMetadata.h>
#import <HealthKit/HKWorkout.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum          HKWorkoutSessionLocationType
 @abstract      This enumerated type is used to represent the location type of a workout session.
 @discussion    This value represents whether a workout is performed indoors or outdoors.
 */
typedef NS_ENUM(NSInteger, HKWorkoutSessionLocationType) {
    HKWorkoutSessionLocationTypeUnknown = 1,
    HKWorkoutSessionLocationTypeIndoor,
    HKWorkoutSessionLocationTypeOutdoor,
} API_AVAILABLE(ios(10.0), watchos(2.0));

/*!
 @class         HKWorkoutConfiguration
 @abstract      An HKWorkoutConfiguration is an object that can be used to describe the a workout activity.
 */
HK_EXTERN API_AVAILABLE(ios(10.0), watchos(3.0))
@interface HKWorkoutConfiguration : NSObject <NSCopying, NSSecureCoding>

/*!
 @property      activityType
 @abstract      Indicates the type of workout for the configuration.
 */
@property (assign) HKWorkoutActivityType activityType;

/*!
 @property      locationType
 @abstract      Indicates the type of location (indoors vs. outdoors) for the configuration.
 */
@property (assign) HKWorkoutSessionLocationType locationType;

/*!
 @property      swimmingLocationType
 @abstract      Indicates the type of swimming location (pool vs. open water) where the workout will take place.
 */
@property (assign) HKWorkoutSwimmingLocationType swimmingLocationType;

/*!
 @property      lapLength
 @abstract      Indicates the length of the pool, when the workout location type is pool.
 @discussion    This metric represents the length of the pool where the workout takes place. It should be a quantity with
                a unit representing length.
 */
@property (copy, nullable) HKQuantity *lapLength;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKObjectType.h
//
//  HKObjectType.h
//  HealthKit
//
//  Copyright (c) 2013-2017 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>
#import <HealthKit/HKTypeIdentifiers.h>
#import <HealthKit/HKQuantityAggregationStyle.h>

NS_ASSUME_NONNULL_BEGIN

@class HKActivitySummaryType;
@class HKCategoryType;
@class HKCharacteristicType;
@class HKCorrelationType;
@class HKDocumentType;
@class HKQuantityType;
@class HKSeriesType;
@class HKUnit;
@class HKWorkoutType;

/*!
 @class         HKObjectType
 @abstract      An abstract class representing a type of object that can be stored by HealthKit.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKObjectType : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      identifier
 @abstract      A unique string identifying a type of health object.
 @discussion    See HKTypeIdentifiers.h for possible values.
 */
@property (readonly, strong) NSString *identifier;

- (instancetype)init NS_UNAVAILABLE;

+ (nullable HKQuantityType *)quantityTypeForIdentifier:(HKQuantityTypeIdentifier)identifier;
+ (nullable HKCategoryType *)categoryTypeForIdentifier:(HKCategoryTypeIdentifier)identifier;
+ (nullable HKCharacteristicType *)characteristicTypeForIdentifier:(HKCharacteristicTypeIdentifier)identifier;
+ (nullable HKCorrelationType *)correlationTypeForIdentifier:(HKCorrelationTypeIdentifier)identifier;
+ (nullable HKDocumentType *)documentTypeForIdentifier:(HKDocumentTypeIdentifier)identifier API_AVAILABLE(ios(10.0), watchos(3.0));
+ (nullable HKSeriesType *)seriesTypeForIdentifier:(NSString *)identifier API_AVAILABLE(ios(11.0), watchos(4.0));
+ (HKWorkoutType *)workoutType;
+ (HKActivitySummaryType *)activitySummaryType API_AVAILABLE(ios(9.3), watchos(2.2));

@end

/*!
 @class         HKCharacteristicType
 @abstract      Represents a type of object that describes a characteristic of the user (such as date of birth).
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKCharacteristicType : HKObjectType
@end

/*!
 @class         HKSampleType
 @abstract      Represents a type of HKSample.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKSampleType : HKObjectType
@end

/*!
 @class         HKCategoryType
 @abstract      Represent a type of HKCategorySample.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKCategoryType : HKSampleType
@end

/*!
 @class         HKCorrelationType
 @abstract      Represents a type of HKCorrelation
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKCorrelationType : HKSampleType
@end

/*!
 @class         HKDocumentType
 @abstract      Represents a type of HKDocument.
 */
HK_EXTERN API_AVAILABLE(ios(10.0))
@interface HKDocumentType : HKSampleType
@end

/*!
 @class         HKQuantityType
 @abstract      Represents types of HKQuantitySamples.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKQuantityType : HKSampleType

@property (readonly) HKQuantityAggregationStyle aggregationStyle;

/*!
 @method        isCompatibleWithUnit:
 @abstract      Returns YES if the type of HKQuantitySample represented by the receiver can be created with quantities 
                of the given unit.
 */
- (BOOL)isCompatibleWithUnit:(HKUnit *)unit;

@end

/*!
 @class         HKWorkoutType
 @abstract      Represents a workout or exercise
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKWorkoutType : HKSampleType
@end

/*!
 @class         HKSeriesType
 @abstract      Represents a type of HKSeriesSample
 */
HK_EXTERN API_AVAILABLE(ios(11.0), watchos(4.0))
@interface HKSeriesType : HKSampleType

+ (instancetype)workoutRouteType;

@end

/*!
 @class         HKActivitySummaryType
 @abstract      Represents an HKActivitySummary
 */
HK_EXTERN API_AVAILABLE(ios(9.3), watchos(2.2))
@interface HKActivitySummaryType : HKObjectType
@end


NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKClinicalType.h
//
//  HKClinicalType.h
//  HealthKit
//
//  Copyright (c) 2018 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>
#import <HealthKit/HKObjectType.h>

NS_ASSUME_NONNULL_BEGIN

@class HKClinicalType;

typedef NSString *HKClinicalTypeIdentifier NS_TYPED_ENUM API_AVAILABLE(ios(12.0), watchos(5.0));

HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierAllergyRecord API_AVAILABLE(ios(12.0), watchos(5.0));
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierConditionRecord API_AVAILABLE(ios(12.0), watchos(5.0));
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierImmunizationRecord API_AVAILABLE(ios(12.0), watchos(5.0));
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierLabResultRecord API_AVAILABLE(ios(12.0), watchos(5.0));
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierMedicationRecord API_AVAILABLE(ios(12.0), watchos(5.0));
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierProcedureRecord API_AVAILABLE(ios(12.0), watchos(5.0));
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierVitalSignRecord API_AVAILABLE(ios(12.0), watchos(5.0));

@interface HKObjectType (ClinicalType)
+ (nullable HKClinicalType *)clinicalTypeForIdentifier:(HKClinicalTypeIdentifier)identifier API_AVAILABLE(ios(12.0), watchos(5.0));
@end

HK_EXTERN
API_AVAILABLE(ios(12.0), watchos(5.0))
@interface HKClinicalType : HKSampleType
@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKDocumentQuery.h
//
//  HKDocumentQuery.h
//  HealthKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#include <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

@class HKDocumentSample;
@class HKDocumentType;

/*!
 @class         HKDocumentQuery
 @abstract      A concrete subclass of HKQuery that provides an interface to retrieve documents from the Health store.
 
 */
HK_EXTERN API_AVAILABLE(ios(10.0))
@interface HKDocumentQuery : HKQuery

/*!
 @property      limit
 @abstract      The maximum number of documents the receiver will return upon completion.
 */
@property (readonly) NSUInteger limit;

/*!
 @property      sortDescriptors
 @abstract      An array of NSSortDescriptors.
 */
@property (readonly, copy, nullable) NSArray<NSSortDescriptor *> *sortDescriptors;

/*!
 @property      includeDocumentData
 @abstract      The XML content for documents may be large.  This property can be used to control whether the query
                returns the XML content for each record.
 */
@property (readonly) BOOL includeDocumentData;

/*!
 @method        initWithDocumentType:predicate:limit:sortDescriptors:includeDocumentData:resultsHandler:
 @abstract      Returns a query that will retrieve HKDocumentSamples matching the given predicate.
 
 @param         documentType        The type of document to retreive.
 @param         predicate           The predicate which documents should match.
 @param         limit               The maximum number of documents to return.  Pass HKObjectQueryNoLimit for no limit.
 @param         sortDescriptors     The sort descriptors to use to order the resulting documents.
 @param         includeDocumentData If true, the document content will be returned with the HKDocumentSample instance.
                                    This option can be used to limit the size of the content returned since the content
                                    may be large.
 @param         resultsHandler      The block that will receive query results.  Results will be returned incrementally
                                    through several calls to this block.  When there are no more results, the done 
                                    parameter will be YES and the results array will be empty.  If results is nil, then
                                    an error has occurred and the error parameter will be set.  Delivery of results can
                                    be stopped by calling HKHealthStore's stopQuery: method.

 @discussion    Health documents may contain sensitive data that a user may want to control explicitly. HKDocumentSample
                objects returned by HKSampleQuery and HKAnchoredObjectQuery do not include this data (i.e., the document
                property is nil).  This query can be used to retrieve fully populated HKDocumentSample instances.  The 
                query will prompt the user to authorize your app to read individual documents.  The query will then
                return the documents that your app is authorized to read. The user will only be asked to authorize your
                app to read documents that are new since the last time an HKDocumentQuery was executed.
 */
- (instancetype)initWithDocumentType:(HKDocumentType *)documentType
                           predicate:(nullable NSPredicate *)predicate
                               limit:(NSUInteger)limit
                     sortDescriptors:(nullable NSArray<NSSortDescriptor *> *)sortDescriptors
                 includeDocumentData:(BOOL)includeDocumentData
                      resultsHandler:(void(^)(HKDocumentQuery *query,
                                              NSArray<__kindof HKDocumentSample *> * _Nullable results,
                                              BOOL done,
                                              NSError * _Nullable error))resultsHandler;


@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKWorkoutRouteQuery.h
//
//  HKWorkoutRouteQuery.h
//  HealthKit
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

@class HKWorkoutRoute;
@class CLLocation;

/*!
 @class         HKWorkoutRouteQuery
 @abstract      An HKWorkoutRouteQuery is used to access data associated with an HKWorkoutRoute.
 @discussion    Once instantiated, call HKHealthStore executeQuery to begin enumerating the route data. Call
                HKHealthStore stopQuery to discontinue further route data reporting.
 */
HK_EXTERN API_AVAILABLE(ios(11.0), watchos(4.0))
@interface HKWorkoutRouteQuery : HKQuery

/*!
 @method        initWithRoute:handler:
 @abstract      Returns a query that will retrieve CLLocation objects for the specified
 workoutRoute.
 
 @param workoutRoute    The HKWorkoutRoute for which the location data will be returned.
 @param dataHandler     The block to invoke with results from the query. It is called repeatedly with an array of
                        CLLocation objects until all data is returned and the done parameter is YES or if HKHealthStore
                        stopQuery: is called. The stopQuery call can be made within the dataHandler block. The number of
                        objects returned in routeData per dataHandler call is unspecified. Once done is YES, or
                        stopQuery called, the query is complete and no more calls to the handler will be made.
 */
- (instancetype)initWithRoute:(HKWorkoutRoute *)workoutRoute
                  dataHandler:(void(^)(HKWorkoutRouteQuery *query, NSArray<CLLocation *> * _Nullable routeData, BOOL done, NSError * _Nullable error))dataHandler NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKWorkout.h
//
//  HKWorkout.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;

/*!
 @enum          HKWorkoutActivityType
 @abstract      Represents a particular type of workout or exercise
 */
typedef NS_ENUM(NSUInteger, HKWorkoutActivityType) {
    HKWorkoutActivityTypeAmericanFootball = 1,
    HKWorkoutActivityTypeArchery,
    HKWorkoutActivityTypeAustralianFootball,
    HKWorkoutActivityTypeBadminton,
    HKWorkoutActivityTypeBaseball,
    HKWorkoutActivityTypeBasketball,
    HKWorkoutActivityTypeBowling,
    HKWorkoutActivityTypeBoxing, // See also HKWorkoutActivityTypeKickboxing.
    HKWorkoutActivityTypeClimbing,
    HKWorkoutActivityTypeCricket,
    HKWorkoutActivityTypeCrossTraining, // Any mix of cardio and/or strength training. See also HKWorkoutActivityTypeCoreTraining and HKWorkoutActivityTypeFlexibility.
    HKWorkoutActivityTypeCurling,
    HKWorkoutActivityTypeCycling,
    HKWorkoutActivityTypeDance,
    HKWorkoutActivityTypeDanceInspiredTraining API_DEPRECATED("Use HKWorkoutActivityTypeDance, HKWorkoutActivityTypeBarre or HKWorkoutActivityTypePilates", ios(8.0, 10.0), watchos(2.0, 3.0)), // This enum remains available to access older data.
    HKWorkoutActivityTypeElliptical,
    HKWorkoutActivityTypeEquestrianSports, // Polo, Horse Racing, Horse Riding, etc.
    HKWorkoutActivityTypeFencing,
    HKWorkoutActivityTypeFishing,
    HKWorkoutActivityTypeFunctionalStrengthTraining, // Primarily free weights and/or body weight and/or accessories
    HKWorkoutActivityTypeGolf,
    HKWorkoutActivityTypeGymnastics,
    HKWorkoutActivityTypeHandball,
    HKWorkoutActivityTypeHiking,
    HKWorkoutActivityTypeHockey, // Ice Hockey, Field Hockey, etc.
    HKWorkoutActivityTypeHunting,
    HKWorkoutActivityTypeLacrosse,
    HKWorkoutActivityTypeMartialArts,
    HKWorkoutActivityTypeMindAndBody, // Qigong, meditation, etc.
    HKWorkoutActivityTypeMixedMetabolicCardioTraining API_DEPRECATED("Use HKWorkoutActivityTypeMixedCardio or HKWorkoutActivityTypeHighIntensityIntervalTraining", ios(8.0, 11.0), watchos(2.0, 4.0)), // This enum remains available to access older data.
    HKWorkoutActivityTypePaddleSports, // Canoeing, Kayaking, Outrigger, Stand Up Paddle Board, etc.
    HKWorkoutActivityTypePlay, // Dodge Ball, Hopscotch, Tetherball, Jungle Gym, etc.
    HKWorkoutActivityTypePreparationAndRecovery, // Foam rolling, stretching, etc.
    HKWorkoutActivityTypeRacquetball,
    HKWorkoutActivityTypeRowing,
    HKWorkoutActivityTypeRugby,
    HKWorkoutActivityTypeRunning,
    HKWorkoutActivityTypeSailing,
    HKWorkoutActivityTypeSkatingSports, // Ice Skating, Speed Skating, Inline Skating, Skateboarding, etc.
    HKWorkoutActivityTypeSnowSports, // Sledding, Snowmobiling, Building a Snowman, etc. See also HKWorkoutActivityTypeCrossCountrySkiing, HKWorkoutActivityTypeSnowboarding, and HKWorkoutActivityTypeDownhillSkiing.
    HKWorkoutActivityTypeSoccer,
    HKWorkoutActivityTypeSoftball,
    HKWorkoutActivityTypeSquash,
    HKWorkoutActivityTypeStairClimbing, // See also HKWorkoutActivityTypeStairs and HKWorkoutActivityTypeStepTraining.
    HKWorkoutActivityTypeSurfingSports, // Traditional Surfing, Kite Surfing, Wind Surfing, etc.
    HKWorkoutActivityTypeSwimming,
    HKWorkoutActivityTypeTableTennis,
    HKWorkoutActivityTypeTennis,
    HKWorkoutActivityTypeTrackAndField, // Shot Put, Javelin, Pole Vaulting, etc.
    HKWorkoutActivityTypeTraditionalStrengthTraining, // Primarily machines and/or free weights
    HKWorkoutActivityTypeVolleyball,
    HKWorkoutActivityTypeWalking,
    HKWorkoutActivityTypeWaterFitness,
    HKWorkoutActivityTypeWaterPolo,
    HKWorkoutActivityTypeWaterSports, // Water Skiing, Wake Boarding, etc.
    HKWorkoutActivityTypeWrestling,
    HKWorkoutActivityTypeYoga,
    
    HKWorkoutActivityTypeBarre              API_AVAILABLE(ios(10.0), watchos(3.0)),    // HKWorkoutActivityTypeDanceInspiredTraining
    HKWorkoutActivityTypeCoreTraining       API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeCrossCountrySkiing API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeDownhillSkiing     API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeFlexibility        API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeHighIntensityIntervalTraining    API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeJumpRope           API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeKickboxing         API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypePilates            API_AVAILABLE(ios(10.0), watchos(3.0)),    // HKWorkoutActivityTypeDanceInspiredTraining
    HKWorkoutActivityTypeSnowboarding       API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeStairs             API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeStepTraining       API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeWheelchairWalkPace API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeWheelchairRunPace  API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutActivityTypeTaiChi             API_AVAILABLE(ios(11.0), watchos(4.0)),
    HKWorkoutActivityTypeMixedCardio        API_AVAILABLE(ios(11.0), watchos(4.0)),    // HKWorkoutActivityTypeMixedMetabolicCardioTraining
    HKWorkoutActivityTypeHandCycling        API_AVAILABLE(ios(11.0), watchos(4.0)),
    
    HKWorkoutActivityTypeOther = 3000,
} API_AVAILABLE(ios(8.0), watchos(2.0));

typedef NS_ENUM(NSInteger, HKWorkoutEventType) {
    HKWorkoutEventTypePause = 1,
    HKWorkoutEventTypeResume,
    HKWorkoutEventTypeLap           API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutEventTypeMarker        API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutEventTypeMotionPaused  API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutEventTypeMotionResumed API_AVAILABLE(ios(10.0), watchos(3.0)),
    HKWorkoutEventTypeSegment       API_AVAILABLE(ios(11.0), watchos(4.0)),
    HKWorkoutEventTypePauseOrResumeRequest API_AVAILABLE(ios(11.0), watchos(4.0)),
} API_AVAILABLE(ios(8.0), watchos(2.0));

/*!
 @class         HKWorkoutEvent
 @abstract      Represents a particular event that occurred during a workout.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKWorkoutEvent : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      workoutEventType
 @abstract      Represents the type of event that occurred during a workout.
 */
@property (readonly, assign) HKWorkoutEventType type;

@property (readonly, copy) NSDate *date API_DEPRECATED_WITH_REPLACEMENT("dateInterval", ios(8.0, 11.0), watchos(2.0, 4.0));

/*!
 @property      dateInterval
 @abstract      Date interval representing the time period for which the event is valid.
 @discussion    Most event types only support date intervals with zero duration. Events of type HKWorkoutEventTypeLap
                and HKWorkoutEventTypeSegment are currently the only events that support a nonzero duration.
 */
@property (readonly, copy) NSDateInterval *dateInterval API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @property      metadata
 @abstract      Extra information describing properties of the receiver.
 @discussion    Keys must be NSString and values must be either NSString, NSNumber, NSDate, or
                HKQuantity. See HKMetadata.h for potential metadata keys and values.
 */
@property (readonly, copy, nullable) NSDictionary<NSString *, id> *metadata API_AVAILABLE(ios(10.0), watchos(3.0));

+ (instancetype)workoutEventWithType:(HKWorkoutEventType)type date:(NSDate *)date API_DEPRECATED_WITH_REPLACEMENT("workoutEventWithType:dateInterval:metadata:", ios(8.0, 11.0), watchos(2.0, 4.0));

+ (instancetype)workoutEventWithType:(HKWorkoutEventType)type date:(NSDate *)date metadata:(NSDictionary<NSString *, id> *)metadata API_DEPRECATED_WITH_REPLACEMENT("workoutEventWithType:dateInterval:metadata:", ios(10.0, 11.0), watchos(3.0, 4.0));

/*!
 @method        workoutEventWithType:dateInterval:metadata:
 @discussion    Creates an event with a date interval with or without a duration.
 @param         type                    The type of event to create
 @param         dateInterval            The dateInterval over which the event occurs
 @param         metadata                Dictionary of metadata associated with the event, nullable
 */
+ (instancetype)workoutEventWithType:(HKWorkoutEventType)type dateInterval:(NSDateInterval *)dateInterval metadata:(nullable NSDictionary<NSString *, id> *)metadata API_AVAILABLE(ios(11.0), watchos(4.0));

- (instancetype)init NS_UNAVAILABLE;

@end

/*!
 @class         HKWorkout
 @abstract      An HKObject subclass representing a workout or activity
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKWorkout : HKSample

/*!
 @property      workoutActivityType
 @abstract      Represents the activity that the user was performing during a workout
 */
@property (readonly, assign) HKWorkoutActivityType workoutActivityType;

/*!
 @property      workoutEvents
 @abstract      An array of HKWorkoutEvents that occurred during a workout.
 @discussion    These events will be ordered by date in ascending order. All events must take place
                between the start date and end date of the workout. The first workout event should always be a pause event
                because it is assumed that the workout begins in a running state. A pause event can only be followed by
                a resume event, and a resume event can only be followed by a pause event.
 */
@property (readonly, copy, nullable) NSArray<HKWorkoutEvent *> *workoutEvents;

/*!
 @property      duration
 @abstract      The length of time that a workout was recording
 @discussion    The duration is derived from the start and end dates of the workout and takes into account periods that the
                workout was paused. Periods that the workout was paused are based off of the workoutEvents property.
 */
@property (readonly, assign) NSTimeInterval duration;

/*!
 @property      totalEnergyBurned
 @abstract      The amount of energy that was burned during a workout
 @discussion    This metric should represent the total active energy burned during the course of the workout. It should be a
                quantity with a unit representing energy.
 */
@property (readonly, strong, nullable) HKQuantity *totalEnergyBurned;
/*!
 @property      totalDistance
 @abstract      The total distance that was traveled during a workout
 @discussion    This metric should represent the total distance traveled during the course of the workout. It should be a
                quantity with a unit representing length.
 */
@property (readonly, strong, nullable) HKQuantity *totalDistance;

/*!
 @property      totalSwimmingStrokeCount
 @abstract      The total count of swimming strokes that was accumulated during a workout
 @discussion    This metric should represent the total count of swimming strokes accumulated during the course of the
                workout. It should be a quantity with a unit representing count.
 */
@property (readonly, strong, nullable) HKQuantity *totalSwimmingStrokeCount API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @property      totalFlightsClimbed
 @abstract      The total count of flights climbed during a workout
 @discussion    This metric should represent the total count of flights accumulated during the course of the
 workout. It should be a quantity with a unit representing count.
 */
@property (readonly, strong, nullable) HKQuantity *totalFlightsClimbed API_AVAILABLE(ios(11.0), watchos(4.0));

/*!
 @method        workoutWithActivityType:startDate:endDate:

 @param         workoutActivityType     The activity type of the workout
 @param         startDate               The point in time that the workout was started
 @param         endDate                 The point in time that the workout was ended
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate;

/*!
 @method        workoutWithActivityType:startDate:endDate:workoutEvents:totalEnergyBurned:totalDistance:metadata
 @discussion    If the optional total parameters are specified, matching samples that add up to the calculated total quantities
                should be associated with this workout using addSamples:toWorkout:completion: in HKHealthStore.
 
 @param         workoutActivityType     The activity type of the workout
 @param         startDate               The point in time that the workout was started
 @param         endDate                 The point in time that the workout was ended
 @param         workoutEvents           An array of HKWorkoutEvents. The workout's duration is derived from these events. (Optional)
 @param         totalEnergyBurned       The amount of energy that was burned during the workout. (Optional)
 @param         totalDistance           The total distance that was traveled during the workout. (Optional)
 @param         metadata                Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                          workoutEvents:(nullable NSArray<HKWorkoutEvent *> *)workoutEvents
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata;

/*!
 @method        workoutWithActivityType:startDate:endDate:workoutEvents:totalEnergyBurned:totalDistance:metadata
 @discussion    If the optional total parameters are specified, matching samples that add up to the calculated total quantities
                should be associated with this workout using addSamples:toWorkout:completion: in HKHealthStore.
 
 @param         workoutActivityType     The activity type of the workout
 @param         startDate               The point in time that the workout was started
 @param         endDate                 The point in time that the workout was ended
 @param         workoutEvents           An array of HKWorkoutEvents. The workout's duration is derived from these events. (Optional)
 @param         totalEnergyBurned       The amount of energy that was burned during the workout. (Optional)
 @param         totalDistance           The total distance that was traveled during the workout. (Optional)
 @param         device                  The HKDevice associated with the workout. (Optional)
 @param         metadata                Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                          workoutEvents:(nullable NSArray<HKWorkoutEvent *> *)workoutEvents
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                                 device:(nullable HKDevice *)device
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @method        workoutWithActivityType:startDate:endDate:duration:totalEnergyBurned:totalDistance:metadata:
 @discussion    If the optional total parameters are specified, matching samples that add up to the calculated total quantities
                should be associated with this workout using addSamples:toWorkout:completion: in HKHealthStore.
 
 @param         workoutActivityType     The activity type of the workout
 @param         startDate               The point in time that the workout was started
 @param         endDate                 The point in time that the workout was ended
 @param         duration                The duration of the workout. If 0, the difference between startDate and endDate is used.
 @param         totalEnergyBurned       The amount of energy that was burned during the workout. (Optional)
 @param         totalDistance           The total distance that was traveled during the workout. (Optional)
 @param         metadata                Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                               duration:(NSTimeInterval)duration
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata;

/*!
 @method        workoutWithActivityType:startDate:endDate:duration:totalEnergyBurned:totalDistance:device:metadata:
 @discussion    If the optional total parameters are specified, matching samples that add up to the calculated total quantities
                should be associated with this workout using addSamples:toWorkout:completion: in HKHealthStore.
 
 @param         workoutActivityType     The activity type of the workout
 @param         startDate               The point in time that the workout was started
 @param         endDate                 The point in time that the workout was ended
 @param         duration                The duration of the workout. If 0, the difference between startDate and endDate is used.
 @param         totalEnergyBurned       The amount of energy that was burned during the workout. (Optional)
 @param         totalDistance           The total distance that was traveled during the workout. (Optional)
 @param         device                  The HKDevice associated with the workout. (Optional)
 @param         metadata                Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                               duration:(NSTimeInterval)duration
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                                 device:(nullable HKDevice *)device
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata API_AVAILABLE(ios(9.0), watchos(2.0));

/*!
 @method        workoutWithActivityType:startDate:endDate:workoutEvents:totalEnergyBurned:totalDistance:totalSwimmingStrokeCount:device:metadata:
 @discussion    If the optional total parameters are specified, matching samples that add up to the calculated total quantities
                should be associated with this workout using addSamples:toWorkout:completion: in HKHealthStore.
 
 @param         workoutActivityType         The activity type of the workout
 @param         startDate                   The point in time that the workout was started
 @param         endDate                     The point in time that the workout was ended
 @param         workoutEvents               An array of HKWorkoutEvents. The workout's duration is derived from these events. (Optional)
 @param         totalEnergyBurned           The amount of energy that was burned during the workout. (Optional)
 @param         totalDistance               The total distance that was traveled during the workout. (Optional)
 @param         totalSwimmingStrokeCount    The total count of swimming strokes that was accumulated during the workout. (Optional)
 @param         device                      The HKDevice associated with the workout. (Optional)
 @param         metadata                    Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                          workoutEvents:(nullable NSArray<HKWorkoutEvent *> *)workoutEvents
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
               totalSwimmingStrokeCount:(nullable HKQuantity *)totalSwimmingStrokeCount
                                 device:(nullable HKDevice *)device
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @method        workoutWithActivityType:startDate:endDate:workoutEvents:totalEnergyBurned:totalDistance:totalFlightsClimbed:device:metadata:
 @discussion    If the optional total parameters are specified, matching samples that add up to the calculated total
                quantities should be associated with this workout using addSamples:toWorkout:completion: in
                HKHealthStore.
 
 @param         workoutActivityType         The activity type of the workout
 @param         startDate                   The point in time that the workout was started
 @param         endDate                     The point in time that the workout was ended
 @param         workoutEvents               An array of HKWorkoutEvents. The workout's duration is derived from these events. (Optional)
 @param         totalEnergyBurned           The amount of energy that was burned during the workout. (Optional)
 @param         totalDistance               The total distance that was traveled during the workout. (Optional)
 @param         totalFlightsClimbed         The total count of flights climbed that was accumulated during the workout. (Optional)
 @param         device                      The HKDevice associated with the workout. (Optional)
 @param         metadata                    Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                          workoutEvents:(nullable NSArray<HKWorkoutEvent *> *)workoutEvents
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                    totalFlightsClimbed:(nullable HKQuantity *)totalFlightsClimbed
                                 device:(nullable HKDevice *)device
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata API_AVAILABLE(ios(11.0), watchos(4.0));

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutDuration API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutTotalDistance API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutTotalEnergyBurned API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutType API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutTotalSwimmingStrokeCount API_AVAILABLE(ios(10.0), watchos(3.0));
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutTotalFlightsClimbed API_AVAILABLE(ios(11.0), watchos(4.0));


// Sort Identifiers
HK_EXTERN NSString * const HKWorkoutSortIdentifierDuration API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKWorkoutSortIdentifierTotalDistance API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKWorkoutSortIdentifierTotalEnergyBurned API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN NSString * const HKWorkoutSortIdentifierTotalSwimmingStrokeCount API_AVAILABLE(ios(10.0), watchos(3.0));
HK_EXTERN NSString * const HKWorkoutSortIdentifierTotalFlightsClimbed API_AVAILABLE(ios(11.0), watchos(4.0));

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKStatisticsCollectionQuery.h
//
//  HKStatisticsCollectionQuery.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKStatistics.h>
#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

@class HKStatistics;

HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKStatisticsCollection : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 @method        statisticsForDate:
 @abstract      Returns the statistics object that this date is inside of
 @discussion    If there are no samples for the given date, an HKStatistics instance with nil quantities will be returned.
 */
- (nullable HKStatistics *)statisticsForDate:(NSDate *)date;

/*!
 @method        enumerateStatisticsFromDate:toDate:withBlock:
 @abstract      Enumerates all statistics objects from startDate to endDate.
 @discussion    Statistics objects will be enumerated in chronological order. If there are no samples for an interval
                between the start and end date, then the HKStatistics object for that interval will have nil quantities.
 */
- (void)enumerateStatisticsFromDate:(NSDate *)startDate toDate:(NSDate *)endDate withBlock:(void(^)(HKStatistics *result, BOOL *stop))block;

/*!
 @method        statistics
 @abstract      Returns a copy of the populated statistics objects.
 @discussion    The statistics objects are ordered chronologically.
 */
- (NSArray<HKStatistics *> *)statistics;

/*!
 @method        sources
 @abstract      Returns all HKSources found in the contained HKStatistics objects.
 @discussion    Sources will be empty unless HKStatisticsOptionSeparateBySource is specified in the
                HKStatisticsCollectionQuery options.
 */
- (NSSet<HKSource *> *)sources;

@end

HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKStatisticsCollectionQuery : HKQuery

@property (readonly, strong) NSDate *anchorDate;
@property (readonly) HKStatisticsOptions options;
@property (readonly, copy) NSDateComponents *intervalComponents;

@property (nonatomic, copy, nullable) void(^initialResultsHandler)(HKStatisticsCollectionQuery *query, HKStatisticsCollection * _Nullable result, NSError * _Nullable error);
@property (nonatomic, copy, nullable) void(^statisticsUpdateHandler)(HKStatisticsCollectionQuery *query, HKStatistics * _Nullable statistics, HKStatisticsCollection * _Nullable collection, NSError * _Nullable error);

- (instancetype)initWithQuantityType:(HKQuantityType *)quantityType
             quantitySamplePredicate:(nullable NSPredicate *)quantitySamplePredicate
                             options:(HKStatisticsOptions)options
                          anchorDate:(NSDate *)anchorDate
                  intervalComponents:(NSDateComponents *)intervalComponents;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKQuantityAggregationStyle.h
//
//  HKQuantityAggregationStyle.h
//  HealthKit
//
//  Copyright (c) 2013-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 @enum          HKQuantityAggregationStyle
 @discussion    Describes how quantities can be aggregated over time.
 
 @constant      HKQuantityAggregationStyleCumulative    Samples may be summed over a time interval.
 @constant      HKQuantityAggregationStyleDiscrete      Samples may be averaged over a time interval.
 */
typedef NS_ENUM(NSInteger, HKQuantityAggregationStyle) {
    HKQuantityAggregationStyleCumulative = 0,
    HKQuantityAggregationStyleDiscrete,
} API_AVAILABLE(ios(8.0), watchos(2.0));
// ==========  HealthKit.framework/Headers/HKQuantitySeriesSampleQuery.h
//
//  HKQuantitySeriesSampleQuery.h
//  HealthKit
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;
@class HKQuantitySample;

/*!
 @class         HKQuantitySeriesSampleQuery
 @abstract      An HKQuantitySeriesSampleQuery is used to access series data associated with an
                HKQuantitySample.
 @discussion    Once instantiated, call -[HKHealthStore executeQuery:] to begin enumerating the series data.
                Call -[HKHealthStore stopQuery:] to discontinue further quantity data reporting.
 */
HK_EXTERN API_AVAILABLE(ios(12.0), watchos(5.0))
@interface HKQuantitySeriesSampleQuery : HKQuery

/*!
 @method        initWithSample:dataHandler:
 @abstract      Returns a query that will retrieve HKQuantity objects for the specified sample.
 
 @param         quantitySample      The HKQuantitySample for which the quantity data will
                                    be returned.
 @param         quantityHandler     The block to invoke with results from the query. It will be
                                    called repeatedly with HKQuantity and NSDate objects,
                                    in ascending date order, until all quantities are returned and
                                    the done parameter is YES or -[HKHealthStore stopQuery:] is called.
                                    The stopQuery call can be made within the quantityHandler block.
                                    Once done is YES, or stopQuery has been called, the query is
                                    complete and no more calls to quantityHandler will be made.
 */
- (instancetype)initWithSample:(HKQuantitySample *)quantitySample
               quantityHandler:(void(^)(HKQuantitySeriesSampleQuery *query, HKQuantity * _Nullable quantity, NSDate * _Nullable date, BOOL done, NSError * _Nullable error))quantityHandler NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKActivitySummaryQuery.h
//
//  HKActivitySummaryQuery.h
//  HealthKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <HealthKit/HKQuery.h>

@class HKActivitySummary;

NS_ASSUME_NONNULL_BEGIN

HK_EXTERN API_AVAILABLE(ios(9.3), watchos(2.2))
@interface HKActivitySummaryQuery : HKQuery

/**
  @property      updateHandler
  @abstract      An optional handler to be called when activity summaries matching the given predicate are updated.
  @discussion    This property may not be modified once the query has been executed. If this property is nonnull, then
                 the query must be manually stopped.
  */
@property (nonatomic, copy, nullable) void(^updateHandler)(HKActivitySummaryQuery *query, NSArray<HKActivitySummary *> * _Nullable updatedActivitySummaries, NSError * _Nullable error);

/*!
  @method        initWithPredicate:resultsHandler:
  @abstract      Returns a query that will retrieve HKActivitySummaries matching the given predicate.
  @discussion    If no updateHandler is set on the query, the query will automatically stop after calling resultsHandler.
                 Otherwise, the query continues to run and calls the updateHandler as HKActivitySummaries matching the
                 predicate are updated.
  
  @param         predicate  The predicate which HKActivitySummaries should match.
  @param         handler    The block to invoke with results when the query has finished.
  */
- (instancetype)initWithPredicate:(nullable NSPredicate *)predicate
                   resultsHandler:(void(^)(HKActivitySummaryQuery *query, NSArray<HKActivitySummary *> * _Nullable activitySummaries, NSError * _Nullable error))handler;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKTypeIdentifiers.h
//
//  HKTypeIdentifiers
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>
#import <objc/NSObjCRuntime.h>

NS_ASSUME_NONNULL_BEGIN

/*--------------------------------*/
/*   HKQuantityType Identifiers   */
/*--------------------------------*/

typedef NSString * HKQuantityTypeIdentifier NS_STRING_ENUM;

// Body Measurements
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBodyMassIndex API_AVAILABLE(ios(8.0), watchos(2.0));               // Scalar(Count),               Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBodyFatPercentage API_AVAILABLE(ios(8.0), watchos(2.0));           // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierHeight API_AVAILABLE(ios(8.0), watchos(2.0));                      // Length,                      Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBodyMass API_AVAILABLE(ios(8.0), watchos(2.0));                    // Mass,                        Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierLeanBodyMass API_AVAILABLE(ios(8.0), watchos(2.0));                // Mass,                        Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierWaistCircumference API_AVAILABLE(ios(11.0), watchos(4.0));         // Length,                      Discrete

// Fitness
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierStepCount API_AVAILABLE(ios(8.0), watchos(2.0));                   // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceWalkingRunning API_AVAILABLE(ios(8.0), watchos(2.0));      // Length,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceCycling API_AVAILABLE(ios(8.0), watchos(2.0));             // Length,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceWheelchair API_AVAILABLE(ios(10.0), watchos(3.0));         // Length,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBasalEnergyBurned API_AVAILABLE(ios(8.0), watchos(2.0));           // Energy,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierActiveEnergyBurned API_AVAILABLE(ios(8.0), watchos(2.0));          // Energy,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierFlightsClimbed API_AVAILABLE(ios(8.0), watchos(2.0));              // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierNikeFuel API_AVAILABLE(ios(8.0), watchos(2.0));                    // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierAppleExerciseTime API_AVAILABLE(ios(9.3), watchos(2.2));           // Time                         Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierPushCount API_AVAILABLE(ios(10.0), watchos(3.0));                  // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceSwimming API_AVAILABLE(ios(10.0), watchos(3.0));           // Length,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierSwimmingStrokeCount API_AVAILABLE(ios(10.0), watchos(3.0));        // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierVO2Max API_AVAILABLE(ios(11.0), watchos(4.0));                     // ml/(kg*min)                  Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceDownhillSnowSports API_AVAILABLE(ios(11.2), watchos(4.2)); // Length,                      Cumulative

// Vitals
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierHeartRate API_AVAILABLE(ios(8.0), watchos(2.0));                   // Scalar(Count)/Time,          Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBodyTemperature API_AVAILABLE(ios(8.0), watchos(2.0));             // Temperature,                 Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBasalBodyTemperature API_AVAILABLE(ios(9.0), watchos(2.0));        // Basal Body Temperature,      Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBloodPressureSystolic API_AVAILABLE(ios(8.0), watchos(2.0));       // Pressure,                    Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBloodPressureDiastolic API_AVAILABLE(ios(8.0), watchos(2.0));      // Pressure,                    Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierRespiratoryRate API_AVAILABLE(ios(8.0), watchos(2.0));             // Scalar(Count)/Time,          Discrete
// Beats per minute estimate of a user's lowest heart rate while at rest
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierRestingHeartRate API_AVAILABLE(ios(11.0), watchos(4.0));           // Scalar(Count)/Time,          Discrete
// Average heartbeats per minute captured by an Apple Watch while a user is walking
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierWalkingHeartRateAverage API_AVAILABLE(ios(11.0), watchos(4.0));    // Scalar(Count)/Time,          Discrete
// The standard deviation of heart beat-to-beat intevals (Standard Deviation of Normal to Normal)
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierHeartRateVariabilitySDNN API_AVAILABLE(ios(11.0), watchos(4.0));   // Time (ms),                   Discrete

// Results
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierOxygenSaturation API_AVAILABLE(ios(8.0), watchos(2.0));            // Scalar (Percent, 0.0 - 1.0,  Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierPeripheralPerfusionIndex API_AVAILABLE(ios(8.0), watchos(2.0));    // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBloodGlucose API_AVAILABLE(ios(8.0), watchos(2.0));                // Mass/Volume,                 Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierNumberOfTimesFallen API_AVAILABLE(ios(8.0), watchos(2.0));         // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierElectrodermalActivity API_AVAILABLE(ios(8.0), watchos(2.0));       // Conductance,                 Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierInhalerUsage API_AVAILABLE(ios(8.0), watchos(2.0));                // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierInsulinDelivery API_AVAILABLE(ios(11.0), watchos(4.0));            // Pharmacology (IU)            Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBloodAlcoholContent API_AVAILABLE(ios(8.0), watchos(2.0));         // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierForcedVitalCapacity API_AVAILABLE(ios(8.0), watchos(2.0));         // Volume,                      Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierForcedExpiratoryVolume1 API_AVAILABLE(ios(8.0), watchos(2.0));     // Volume,                      Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierPeakExpiratoryFlowRate API_AVAILABLE(ios(8.0), watchos(2.0));      // Volume/Time,                 Discrete

// Nutrition
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFatTotal API_AVAILABLE(ios(8.0), watchos(2.0));             // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFatPolyunsaturated API_AVAILABLE(ios(8.0), watchos(2.0));   // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFatMonounsaturated API_AVAILABLE(ios(8.0), watchos(2.0));   // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFatSaturated API_AVAILABLE(ios(8.0), watchos(2.0));         // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCholesterol API_AVAILABLE(ios(8.0), watchos(2.0));          // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietarySodium API_AVAILABLE(ios(8.0), watchos(2.0));               // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCarbohydrates API_AVAILABLE(ios(8.0), watchos(2.0));        // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFiber API_AVAILABLE(ios(8.0), watchos(2.0));                // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietarySugar API_AVAILABLE(ios(8.0), watchos(2.0));                // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryEnergyConsumed API_AVAILABLE(ios(8.0), watchos(2.0));       // Energy, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryProtein API_AVAILABLE(ios(8.0), watchos(2.0));              // Mass,   Cumulative

HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminA API_AVAILABLE(ios(8.0), watchos(2.0));             // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminB6 API_AVAILABLE(ios(8.0), watchos(2.0));            // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminB12 API_AVAILABLE(ios(8.0), watchos(2.0));           // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminC API_AVAILABLE(ios(8.0), watchos(2.0));             // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminD API_AVAILABLE(ios(8.0), watchos(2.0));             // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminE API_AVAILABLE(ios(8.0), watchos(2.0));             // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminK API_AVAILABLE(ios(8.0), watchos(2.0));             // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCalcium API_AVAILABLE(ios(8.0), watchos(2.0));              // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryIron API_AVAILABLE(ios(8.0), watchos(2.0));                 // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryThiamin API_AVAILABLE(ios(8.0), watchos(2.0));              // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryRiboflavin API_AVAILABLE(ios(8.0), watchos(2.0));           // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryNiacin API_AVAILABLE(ios(8.0), watchos(2.0));               // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFolate API_AVAILABLE(ios(8.0), watchos(2.0));               // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryBiotin API_AVAILABLE(ios(8.0), watchos(2.0));               // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryPantothenicAcid API_AVAILABLE(ios(8.0), watchos(2.0));      // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryPhosphorus API_AVAILABLE(ios(8.0), watchos(2.0));           // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryIodine API_AVAILABLE(ios(8.0), watchos(2.0));               // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryMagnesium API_AVAILABLE(ios(8.0), watchos(2.0));            // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryZinc API_AVAILABLE(ios(8.0), watchos(2.0));                 // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietarySelenium API_AVAILABLE(ios(8.0), watchos(2.0));             // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCopper API_AVAILABLE(ios(8.0), watchos(2.0));               // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryManganese API_AVAILABLE(ios(8.0), watchos(2.0));            // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryChromium API_AVAILABLE(ios(8.0), watchos(2.0));             // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryMolybdenum API_AVAILABLE(ios(8.0), watchos(2.0));           // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryChloride API_AVAILABLE(ios(8.0), watchos(2.0));             // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryPotassium API_AVAILABLE(ios(8.0), watchos(2.0));            // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCaffeine API_AVAILABLE(ios(8.0), watchos(2.0));             // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryWater API_AVAILABLE(ios(9.0), watchos(2.0));                // Volume, Cumulative

HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierUVExposure API_AVAILABLE(ios(9.0), watchos(2.0));                  // Scalar (Count), Discrete

/*--------------------------------*/
/*   HKCategoryType Identifiers   */
/*--------------------------------*/

typedef NSString * HKCategoryTypeIdentifier NS_STRING_ENUM;

HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierSleepAnalysis API_AVAILABLE(ios(8.0), watchos(2.0));               // HKCategoryValueSleepAnalysis
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierAppleStandHour API_AVAILABLE(ios(9.0), watchos(2.0));              // HKCategoryValueAppleStandHour
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierCervicalMucusQuality API_AVAILABLE(ios(9.0), watchos(2.0));        // HKCategoryValueCervicalMucusQuality
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierOvulationTestResult API_AVAILABLE(ios(9.0), watchos(2.0));         // HKCategoryValueOvulationTestResult
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierMenstrualFlow API_AVAILABLE(ios(9.0), watchos(2.0));               // HKCategoryValueMenstrualFlow
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierIntermenstrualBleeding API_AVAILABLE(ios(9.0), watchos(2.0));      // (Spotting) HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierSexualActivity API_AVAILABLE(ios(9.0), watchos(2.0));              // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierMindfulSession API_AVAILABLE(ios(10.0), watchos(3.0));             // HKCategoryValue

/*--------------------------------------*/
/*   HKCharacteristicType Identifiers   */
/*--------------------------------------*/

typedef NSString * HKCharacteristicTypeIdentifier NS_STRING_ENUM;

HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierBiologicalSex API_AVAILABLE(ios(8.0), watchos(2.0));           // HKBiologicalSexObject
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierBloodType API_AVAILABLE(ios(8.0), watchos(2.0));               // HKBloodTypeObject
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierDateOfBirth API_AVAILABLE(ios(8.0), watchos(2.0));             // NSDateComponents
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierFitzpatrickSkinType API_AVAILABLE(ios(9.0), watchos(2.0));     // HKFitzpatrickSkinTypeObject
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierWheelchairUse API_AVAILABLE(ios(10.0), watchos(3.0));          // HKWheelchairUseObject

/*-----------------------------------*/
/*   HKCorrelationType Identifiers   */
/*-----------------------------------*/

typedef NSString * HKCorrelationTypeIdentifier NS_STRING_ENUM;

HK_EXTERN HKCorrelationTypeIdentifier const HKCorrelationTypeIdentifierBloodPressure API_AVAILABLE(ios(8.0), watchos(2.0));
HK_EXTERN HKCorrelationTypeIdentifier const HKCorrelationTypeIdentifierFood API_AVAILABLE(ios(8.0), watchos(2.0));

/*--------------------------------*/
/*   HKDocumentType Identifiers   */
/*--------------------------------*/

typedef NSString * HKDocumentTypeIdentifier NS_STRING_ENUM;

HK_EXTERN HKDocumentTypeIdentifier const HKDocumentTypeIdentifierCDA API_AVAILABLE(ios(10.0), watchos(3.0));

/*------------------------------*/
/*   HKWorkoutType Identifier   */
/*------------------------------*/

HK_EXTERN NSString * const HKWorkoutTypeIdentifier API_AVAILABLE(ios(8.0), watchos(2.0));

/*--------------------------------*/
/*   HKSeriesSample Identifiers   */
/*--------------------------------*/

HK_EXTERN NSString * const HKWorkoutRouteTypeIdentifier API_AVAILABLE(ios(11.0), watchos(4.0));

NS_ASSUME_NONNULL_END
