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
HK_CLASS_AVAILABLE_IOS(8_0)
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
//  Copyright (c) 2013-2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @constant      HKMetadataKeyUDIProductionIdentifier
 @abstract      Represents the serial number of the device that created the HKObject.
 @discussion    The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyDeviceSerialNumber NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyBodyTemperatureSensorLocation
 @abstract      Represents the location where a particular body temperature reading was taken.
 @discussion    The expected value type is an NSNumber containing a HKBodyTemperatureSensorLocation value.
 */
HK_EXTERN NSString * const HKMetadataKeyBodyTemperatureSensorLocation NS_AVAILABLE_IOS(8_0);

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
} NS_ENUM_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyHeartRateSensorLocation
 @abstract      Represents the location where a particular heart rate reading was taken.
 @discussion    The expected value type is an NSNumber containing a HKHeartRateSensorLocation value.
 */
HK_EXTERN NSString * const HKMetadataKeyHeartRateSensorLocation NS_AVAILABLE_IOS(8_0);

typedef NS_ENUM(NSInteger, HKHeartRateSensorLocation) {
    HKHeartRateSensorLocationOther = 0,
    HKHeartRateSensorLocationChest,
    HKHeartRateSensorLocationWrist,
    HKHeartRateSensorLocationFinger,
    HKHeartRateSensorLocationHand,
    HKHeartRateSensorLocationEarLobe,
    HKHeartRateSensorLocationFoot,
} NS_ENUM_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyFoodType
 @abstract      Represents the type of food that was consumed when creating an HKObject.
 @discussion    This should be a short string representing the type of food, such as 'Banana'. The expected value type
                is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyFoodType NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyUDIDeviceIdentifier
 @abstract      Represents the device identifier portion of a device's UDI (Unique Device Identifier).
 @discussion    The device identifier can be used to reference the GUDID (Globally Unique Device Identifier Database).
                The expected value type is NSString.
 
                ** Note that the use of this key is now discouraged in favor of the HKDevice class.
 */
HK_EXTERN NSString * const HKMetadataKeyUDIDeviceIdentifier NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyUDIProductionIdentifier
 @abstract      Represents the production identifier portion of a device's UDI (Unique Device Identifier).
 @discussion    While part of a device's UDI, the production identifier is not saved in the FDA's GUDID 
                (Globally Unique Device Identifier Database) and its use in HealthKit is now discouraged for
                user privacy reasons. Apps should consider handling this independently of HealthKit APIs if
                needed.
                The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyUDIProductionIdentifier NS_AVAILABLE_IOS(8_0);

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
HK_EXTERN NSString * const HKMetadataKeyDigitalSignature NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyExternalUUID
 @abstract      Represents a unique identifier for an HKObject that is set by its source. 
 @discussion    The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyExternalUUID NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyTimeZone
 @abstract      Represents the time zone that the user was in when the HKObject was created.
 @discussion    The expected value type is an NSString compatible with NSTimeZone's +timeZoneWithName:.
 */
HK_EXTERN NSString * const HKMetadataKeyTimeZone NS_AVAILABLE_IOS(8_0);


/*!
 @constant      HKMetadataKeyDeviceName
 @abstract      Represents the name of the device that took the reading.
 @discussion    The expected value type is NSString.
 
                ** Note that the use of this key is now discouraged in favor of the HKDevice class.
 */
HK_EXTERN NSString * const HKMetadataKeyDeviceName NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyDeviceManufacturerName
 @abstract      Represents the name of the manufacturer of the device that took the reading.
 @discussion    The expected value type is NSString.
 
                ** Note that the use of this key is now discouraged in favor of the HKDevice class.
 */
HK_EXTERN NSString * const HKMetadataKeyDeviceManufacturerName NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyWasTakenInLab
 @abstract      Represents whether or not the reading was taken in a lab.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyWasTakenInLab NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyReferenceRangeLowerLimit
 @abstract      Represents the lower limit of the reference range for a lab result.
 @discussion    The expected value type is an NSNumber.
 */
HK_EXTERN NSString * const HKMetadataKeyReferenceRangeLowerLimit NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyReferenceRangeUpperLimit
 @abstract      Represents the upper limit of the reference range for a lab result.
 @discussion    The expected value type is an NSNumber.
 */
HK_EXTERN NSString * const HKMetadataKeyReferenceRangeUpperLimit NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyWasUserEntered
 @abstract      Represents whether or not the reading was entered by the user.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyWasUserEntered NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyWorkoutBrandName
 @abstract      Represents the brand name of a particular workout.
 @discussion    The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyWorkoutBrandName NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyGroupFitness
 @abstract      Represents whether or not a workout was performed as part of a group fitness class.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyGroupFitness NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyIndoorWorkout
 @abstract      Represents whether or not a workout was performed indoors as opposed to outdoors.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyIndoorWorkout NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyCoachedWorkout
 @abstract      Represents whether or not a workout was performed with a coach or personal trainer.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyCoachedWorkout NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeySexualActivityProtectionUsed
 @abstract      Represents whether or not protection was used during sexual activity. This can be used to track either
                protection from STIs or protection from pregnancy.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeySexualActivityProtectionUsed NS_AVAILABLE_IOS(9_0);

/*!
 @constant      HKMetadataKeyMenstrualCycleStart
 @abstract      Indicates whether or not the sample represents the start of a menstrual cycle. This is a required
                metadata key for category samples of type HKCategorySampleMenstrualFlow.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyMenstrualCycleStart NS_AVAILABLE_IOS(9_0);

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HealthKit.h
//
//  HealthKit.h
//  HealthKit
//
//  Copyright (c) 2013-2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKAnchoredObjectQuery.h>
#import <HealthKit/HKCategorySample.h>
#import <HealthKit/HKCorrelation.h>
#import <HealthKit/HKCorrelationQuery.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKDeletedObject.h>
#import <HealthKit/HKDevice.h>
#import <HealthKit/HKHealthStore.h>
#import <HealthKit/HKMetadata.h>
#import <HealthKit/HKObject.h>
#import <HealthKit/HKObjectType.h>
#import <HealthKit/HKObserverQuery.h>
#import <HealthKit/HKQuantity.h>
#import <HealthKit/HKQuantitySample.h>
#import <HealthKit/HKQuery.h>
#import <HealthKit/HKSample.h>
#import <HealthKit/HKSampleQuery.h>
#import <HealthKit/HKSource.h>
#import <HealthKit/HKSourceQuery.h>
#import <HealthKit/HKSourceRevision.h>
#import <HealthKit/HKStatistics.h>
#import <HealthKit/HKStatisticsCollectionQuery.h>
#import <HealthKit/HKStatisticsQuery.h>
#import <HealthKit/HKTypeIdentifiers.h>
#import <HealthKit/HKUnit.h>
#import <HealthKit/HKWorkout.h>
#import <HealthKit/HKWorkoutSession.h>
// ==========  HealthKit.framework/Headers/HKHealthStore.h
//
//  HKHealthStore.h
//  HealthKit
//
//  Copyright (c) 2013-2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HKBiologicalSexObject;
@class HKBloodTypeObject;
@class HKDevice;
@class HKFitzpatrickSkinTypeObject;
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
@class HKWorkoutSession;

/*!
 @class         HKHealthStore
 @abstract      The HKHealthStore class provides an interface for accessing and storing the user's health data.
 */
HK_CLASS_AVAILABLE_IOS(8_0)
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
                Info.plist file. Set the NSHealthShareUsageDescription key to customize the message for reading data. Set
                the NSHealthUpdateUsageDescription key to customize the message for writing data.
 */
- (void)requestAuthorizationToShareTypes:(nullable NSSet<HKSampleType *> *)typesToShare
                               readTypes:(nullable NSSet<HKObjectType *> *)typesToRead
                              completion:(void (^)(BOOL success, NSError * __nullable error))completion;

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
- (void)handleAuthorizationForExtensionWithCompletion:(void (^)(BOOL success, NSError * __nullable error))completion NS_AVAILABLE_IOS(9_0) __WATCHOS_UNAVAILABLE NS_EXTENSION_UNAVAILABLE("Not available to extensions") ;

/*!
 @method        earliestPermittedSampleDate
 @abstract      Samples prior to the earliestPermittedSampleDate cannot be saved or queried.
 @discussion    On some platforms, only samples with end dates newer than the value returned by earliestPermittedSampleDate
                may be saved or retreived.
 */
- (NSDate *)earliestPermittedSampleDate NS_AVAILABLE_IOS(9_0);

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
- (void)saveObject:(HKObject *)object withCompletion:(void(^)(BOOL success, NSError * __nullable error))completion;

/*!
 @method        saveObjects:withCompletion:
 @abstract      Saves an array of HKObjects.
 @discussion    See discussion of saveObject:withCompletion:.
 */
- (void)saveObjects:(NSArray<HKObject *> *)objects withCompletion:(void(^)(BOOL success, NSError * __nullable error))completion;

/*!
 @method        deleteObject:withCompletion:
 @abstract      Deletes a single HKObject from the HealthKit database.
 @discussion    See deleteObjects:withCompletion:.
 */
- (void)deleteObject:(HKObject *)object withCompletion:(void(^)(BOOL success, NSError * __nullable error))completion;

/*!
 @method        deleteObjects:withCompletion:
 @abstract      Deletes multiple HKObjects from the HealthKit database.
 @discussion    An application may only delete objects that it previously saved.  This operation is performed
                asynchronously and the completion will be executed on an arbitrary background queue.
 */
- (void)deleteObjects:(NSArray<HKObject *> *)objects withCompletion:(void(^)(BOOL success, NSError * __nullable error))completion NS_AVAILABLE_IOS(9_0);

/*!
 @method        deleteObjectsMatchingQuery:withCompletion:
 @abstract      Deletes all objects matching the given predicate from the HealthKit database.
 @discussion    An application may only delete objects that it previously saved.  This operation is performed
                asynchronously and the completion will be executed on an arbitrary background queue.
 */
- (void)deleteObjectsOfType:(HKObjectType *)objectType predicate:(NSPredicate *)predicate withCompletion:(void(^)(BOOL success, NSUInteger deletedObjectCount, NSError * __nullable error))completion NS_AVAILABLE_IOS(9_0);

/*!
 @method        executeQuery:
 @abstract      Begins executing the given query.
 @discussion    After executing a query the completion, update, and/or results handlers of that query will be invoked
                asynchronously on an arbitrary background queue as results become available.  Errors that prevent a
                query from executing will be delivered to one of the query's handlers.  Which handler the error will be
                delivered to is defined by the HKQuery subclass.  The behavior of calling this method with a query that
                is already executing is undefined.  If a query would retrieve objects with an HKObjectType property,
                then the application must request authorization to access objects of that type before executing the query.
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
                energy passed.
 @discussion    This method uses the users metrics like age, biological sex, body mass and height to determine
                their basal metabolic rate. If the application does not have authorization to access these characteristics
                or if the user has not entered their data then this method uses builtin default values.
 */
- (void)splitTotalEnergy:(HKQuantity *)totalEnergy
               startDate:(NSDate *)startDate
                 endDate:(NSDate *)endDate
          resultsHandler:(void(^)(HKQuantity * __nullable restingEnergy, HKQuantity * __nullable activeEnergy, NSError * __nullable error))resultsHandler NS_AVAILABLE_IOS(9_0);

/*!
 @method        dateOfBirthWithError:
 @abstract      Returns the user's date of birth.
 @discussion    Before calling this method, the application should request authorization to access objects with the
                HKCharacteristicType identified by HKCharacteristicTypeIdentifierDateOfBirth.
 */
- (nullable NSDate *)dateOfBirthWithError:(NSError **)error;

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
- (nullable HKFitzpatrickSkinTypeObject *)fitzpatrickSkinTypeWithError:(NSError **)error NS_AVAILABLE_IOS(9_0);

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
- (void)addSamples:(NSArray<HKSample *> *)samples toWorkout:(HKWorkout *)workout completion:(void(^)(BOOL success, NSError * __nullable error))completion;

/*!
 @method        startWorkoutSession:
 @abstract      Starts the given workout session.
 @discussion    This method will asynchronously begin a workout session. The methods on the session's delegate will be 
                called when the session has successfully started or fails to start.
 */
- (void)startWorkoutSession:(HKWorkoutSession *)workoutSession HK_AVAILABLE_WATCHOS_ONLY(2_0);

/*!
 @method        endWorkoutSession:
 @abstract      Ends the given workout session.
 @discussion    This method will end the given session if it is currently running. The state of the workout session will
                transition to HKWorkoutSessionStateEnded. Once a workout session is ended, it cannot be reused to start
                a new workout session.
 */
- (void)endWorkoutSession:(HKWorkoutSession *)workoutSession HK_AVAILABLE_WATCHOS_ONLY(2_0);

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
- (void)enableBackgroundDeliveryForType:(HKObjectType *)type frequency:(HKUpdateFrequency)frequency withCompletion:(void(^)(BOOL success, NSError * __nullable error))completion __WATCHOS_UNAVAILABLE;

- (void)disableBackgroundDeliveryForType:(HKObjectType *)type withCompletion:(void(^)(BOOL success, NSError * __nullable error))completion __WATCHOS_UNAVAILABLE;

- (void)disableAllBackgroundDeliveryWithCompletion:(void(^)(BOOL success, NSError * __nullable error))completion __WATCHOS_UNAVAILABLE;

@end

/*!
 @constant      HKUserPreferencesDidChangeNotification
 @abstract      A notification posted every time the user updates their preferred units.
 @discussion    Each HKHealthStore posts a HKUserPreferencesDidChangeNotification notification when the preferred unit 
                for a HKQuantityType is changed by the user. To guarantee your listener will only receive a single 
                notification when this occurs, it is necessary to provide an HKHealthStore instance for the object
                parameter of NSNotificationCenter's addObserver methods.
 */
HK_EXTERN NSString * const HKUserPreferencesDidChangeNotification NS_AVAILABLE_IOS(8_2);

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
- (void)preferredUnitsForQuantityTypes:(NSSet<HKQuantityType *> *)quantityTypes completion:(void(^)(NSDictionary<HKQuantityType*, HKUnit *> *preferredUnits, NSError * __nullable error))completion NS_AVAILABLE_IOS(8_2);

@end

/*!
 @class     HKBiologicalSexObject
 @abstract  A wrapper object for HKBiologicalSex enumeration.
 */
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKBiologicalSexObject : NSObject <NSCopying, NSSecureCoding>

@property (readonly) HKBiologicalSex biologicalSex;

@end

/*!
 @class     HKBloodTypeObject
 @abstract  A wrapper object for HKBloodType enumeration.
 */
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKBloodTypeObject : NSObject <NSCopying, NSSecureCoding>

@property (readonly) HKBloodType bloodType;

@end

/*!
 @class     HKFitzpatrickSkinTypeObject
 @abstract  A wrapper object for HKFitzpatrickSkinType enumeration.
 */
HK_CLASS_AVAILABLE_IOS(9_0)
@interface HKFitzpatrickSkinTypeObject : NSObject <NSCopying, NSSecureCoding>

@property (readonly) HKFitzpatrickSkinType skinType;

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

HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKObject : NSObject <NSSecureCoding>

/*!
 @property      UUID
 @abstract      A unique identifier of the receiver in the HealthKit database.
 */
@property (readonly, strong) NSUUID *UUID;

@property (readonly, strong) HKSource *source NS_DEPRECATED_IOS(8_0, 9_0, "Use sourceRevision");

/*!
 @property      sourceRevision
 @abstract      Represents the revision of the source responsible for saving the receiver.
 */
@property (readonly, strong) HKSourceRevision *sourceRevision NS_AVAILABLE_IOS(9_0);

/*!
 @property      device
 @abstract      Represents the device that generated the data of the receiver.
 */
@property (readonly, strong, nullable) HKDevice *device NS_AVAILABLE_IOS(9_0);

/*!
 @property      metadata
 @abstract      Extra information describing properties of the receiver.
 @discussion    Keys must be NSString and values must be either NSString, NSNumber, or NSDate.
                See HKMetadata.h for potential metadata keys and values.
 */
@property (readonly, copy, nullable) NSDictionary<NSString *, id> *metadata;

- (instancetype)init NS_UNAVAILABLE;

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathUUID NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathSource NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathMetadata NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathCorrelation NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathWorkout NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathDevice NS_AVAILABLE_IOS(9_0);
HK_EXTERN NSString * const HKPredicateKeyPathSourceRevision NS_AVAILABLE_IOS(9_0);

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

HK_CLASS_AVAILABLE_IOS(8_0)
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
// fl_oz_imp (Imperial fluid ounces)    = 0.028413075 L
// pt_us     (US customary pint)        = 0.473176473 L
// pt_imp    (Imperial pint)            = 0.5682815 L
// cup_us    (US customary cup)         = 0.2365882365 L
// cup_imp   (Imperial cup)             = 0.28413075 L

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
// [Scalar]
// count = 1
// %     = 1/100


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
} NS_ENUM_AVAILABLE_IOS(8_0);

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
+ (instancetype)yardUnit NS_AVAILABLE_IOS(9_0);   // yd
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
+ (instancetype)cupUSUnit NS_AVAILABLE_IOS(9_0);       // cup_us
+ (instancetype)cupImperialUnit NS_AVAILABLE_IOS(9_0); // cup_imp
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
+ (instancetype)calorieUnit;        // cal
+ (instancetype)kilocalorieUnit;    // kcal
@end

/* Temperature Units */
@interface HKUnit (Temperature)
+ (instancetype)degreeCelsiusUnit;          // degC
+ (instancetype)degreeFahrenheitUnit;       // degF
+ (instancetype)kelvinUnit;                 // K
@end

/* Electrical Conductance Units */
@interface HKUnit(Conductance)
+ (instancetype)siemenUnitWithMetricPrefix:(HKMetricPrefix)prefix;     // S
+ (instancetype)siemenUnit; // S
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

HK_CLASS_AVAILABLE_IOS(9_0)
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
 @method        initWithSource:version:
 @abstract      Initializes a new HKSourceRevision with the given source and version.
 */
- (instancetype)initWithSource:(HKSource *)source version:(NSString *)version;

- (instancetype)init NS_UNAVAILABLE;

@end

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
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKStatisticsQuery : HKQuery

- (instancetype)initWithQuantityType:(HKQuantityType *)quantityType
             quantitySamplePredicate:(nullable NSPredicate *)quantitySamplePredicate
                             options:(HKStatisticsOptions)options
                   completionHandler:(void(^)(HKStatisticsQuery *query, HKStatistics * __nullable result, NSError * __nullable error))handler;

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
#import <HealthKit/HKWorkout.h>

NS_ASSUME_NONNULL_BEGIN

@class HKSampleType;
@class HKQuantity;
@class HKSource;

HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKQuery : NSObject

@property (readonly, strong) HKSampleType *sampleType;
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
} NS_ENUM_AVAILABLE_IOS(8_0);


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
+ (NSPredicate *)predicateForObjectsFromSourceRevisions:(NSSet<HKSourceRevision *> *)sourceRevisions NS_AVAILABLE_IOS(9_0);

/*!
 @method        predicateForObjectsFromDevices:
 @abstract      Creates a predicate for use with HKQuery subclasses.
 @discussion    Creates a query predicate that matches objects associated with any of the given devices. All properties
                of each HKDevice are considered in the query and must match exactly, including nil values. To perform 
                searches based on specific device properties, use predicateForObjectsWithDeviceProperty:allowedValues:.
 
 @param         devices     The set of devices that generated data.
 */
+ (NSPredicate *)predicateForObjectsFromDevices:(NSSet<HKDevice *> *)devices NS_AVAILABLE_IOS(9_0);

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
+ (NSPredicate *)predicateForObjectsWithDeviceProperty:(NSString *)key allowedValues:(NSSet<NSString *> *)allowedValues NS_AVAILABLE_IOS(9_0);

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
                                expression. The unit for this value should be of type Distance
 */
+ (NSPredicate *)predicateForWorkoutsWithOperatorType:(NSPredicateOperatorType)operatorType totalDistance:(HKQuantity *)totalDistance;
@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKSampleQuery.h
//
//  HKSampleQuery.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HealthKit.h>
#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

// The query returns all samples that match the given sampleType and predicate.
#define HKObjectQueryNoLimit (0)

/*!
 @class         HKSampleQuery
 @abstract      A concrete subclass of HKQuery that provides an interface to retrieve HKSample objects.
 */
HK_CLASS_AVAILABLE_IOS(8_0)
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
                    resultsHandler:(void(^)(HKSampleQuery *query, NSArray<__kindof HKSample *> * __nullable results, NSError * __nullable error))resultsHandler;


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
HK_CLASS_AVAILABLE_IOS(8_0)
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
                              metadata:(nullable NSDictionary<NSString *, id> *)metadata NS_AVAILABLE_IOS(9_0);

@end

/*!
 @constant     HKPredicateKeyPathCategoryValue
 */
HK_EXTERN NSString * const HKPredicateKeyPathCategoryValue NS_AVAILABLE_IOS(8_0);

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKSample.h
//
//  HKSample.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKObject.h>

NS_ASSUME_NONNULL_BEGIN

@class HKSampleType;

/*!
 @class         HKSample
 @abstract      An abstract class representing measurements taken over a period of time.
 */
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKSample : HKObject

@property (readonly, strong) HKSampleType *sampleType;

@property (readonly, strong) NSDate *startDate;
@property (readonly, strong) NSDate *endDate;

@end

// Sort Identifiers
HK_EXTERN NSString * const HKSampleSortIdentifierStartDate NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKSampleSortIdentifierEndDate NS_AVAILABLE_IOS(8_0);

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathStartDate NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathEndDate NS_AVAILABLE_IOS(8_0);

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
HK_CLASS_AVAILABLE_IOS(8_0)
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
 @param         type        The correlation type of the objects set.
 @param         startDate   The start date of the correlation.
 @param         endDate     The end date of the correlation.
 @param         device      The HKDevice that generated the samples (optional).
 @param         metadata    Metadata for the correlation (optional).
 @discussion    objects must be a set of HKQuantitySamples and HKCategorySamples
 */
+ (instancetype)correlationWithType:(HKCorrelationType *)correlationType
                          startDate:(NSDate *)startDate
                            endDate:(NSDate *)endDate
                            objects:(NSSet<HKSample *> *)objects
                             device:(nullable HKDevice *)device
                           metadata:(nullable NSDictionary<NSString *, id> *)metadata NS_AVAILABLE_IOS(9_0);

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
HK_CLASS_AVAILABLE_IOS(9_0)
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
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKAnchoredObjectQuery : HKQuery

/*!
 @property      updateHandler
 @abstract      An optional handler to be called when samples matching the given predicate are added or deleted.
 @discussion    This property may not be modified once the query has been executed.  It may only be set if the query has
                no limit.
 */
@property (nonatomic, copy, nullable) void(^updateHandler)(HKAnchoredObjectQuery *query, NSArray<__kindof HKSample *> * __nullable addedObjects, NSArray<HKDeletedObject *> * __nullable deletedObjects, HKQueryAnchor * __nullable newAnchor, NSError * __nullable error) NS_AVAILABLE_IOS(9_0);

- (instancetype)initWithType:(HKSampleType *)type
                   predicate:(nullable NSPredicate *)predicate
                      anchor:(NSUInteger)anchor
                       limit:(NSUInteger)limit
           completionHandler:(void(^)(HKAnchoredObjectQuery *query, NSArray<__kindof HKSample *> * __nullable results, NSUInteger newAnchor, NSError * __nullable error))handler NS_DEPRECATED_IOS(8_0, 9_0);

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
 @param         resultsHandler  The block to invoke with results when the query has finished finding.
 */
- (instancetype)initWithType:(HKSampleType *)type
                   predicate:(nullable NSPredicate *)predicate
                      anchor:(nullable HKQueryAnchor *)anchor
                       limit:(NSUInteger)limit
              resultsHandler:(void(^)(HKAnchoredObjectQuery *query, NSArray<__kindof HKSample *> * __nullable sampleObjects, NSArray<HKDeletedObject *> * __nullable deletedObjects, HKQueryAnchor * __nullable newAnchor, NSError * __nullable error))handler NS_AVAILABLE_IOS(9_0);

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

HK_CLASS_AVAILABLE_IOS(8_0)
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
                     updateHandler:(void(^)(HKObserverQuery *query, HKObserverQueryCompletionHandler completionHandler, NSError * __nullable error))updateHandler;

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
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKSourceQuery : HKQuery

/*!
 @method        initWithSampleType:samplePredicate:completionHandler:
 @abstract      Returns a query that will retrieve HKSources that have saved samples of the given type matching the 
                given predicate.
 
 @param         sampleType          The type of sample.
 @param         samplePredicate     The predicate which samples must match.
 @param         completionHandler   The block to be called when the query has finished executing.
 */
- (instancetype)initWithSampleType:(HKSampleType *)sampleType
                   samplePredicate:(nullable NSPredicate *)objectPredicate
                 completionHandler:(void(^)(HKSourceQuery *query, NSSet<HKSource *> * __nullable sources, NSError * __nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
// ==========  HealthKit.framework/Headers/HKQuantitySample.h
//
//  HKQuantitySample.h
//  HealthKit
//
//  Copyright (c) 2013-2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;
@class HKQuantityType;

/*!
 @class         HKQuantitySample
 @abstract      An HKObject subclass representing a quantity measurement.
 */
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKQuantitySample : HKSample

@property (readonly, strong) HKQuantityType *quantityType;
@property (readonly, strong) HKQuantity *quantity;

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
 @param         type        The type of the sample.
 @param         startDate   The start date of the sample.
 @param         endDate     The end date of the sample.
 @param         device      The HKDevice that generated the sample (optional).
 @param         metadata    Metadata for the sample (optional).
 @discussion    The quantity must have a unit that is compatible with the given quantity type.
                See -[HKQuantityType isCompatibleWithUnit:].
 */
+ (instancetype)quantitySampleWithType:(HKQuantityType *)quantityType
                              quantity:(HKQuantity *)quantity
                             startDate:(NSDate *)startDate
                               endDate:(NSDate *)endDate
                                device:(nullable HKDevice *)device
                              metadata:(nullable NSDictionary<NSString *, id> *)metadata NS_AVAILABLE_IOS(9_0);

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathQuantity NS_AVAILABLE_IOS(8_0);

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

#define HK_EXTERN   extern __attribute__((visibility("default")))
#define HK_CLASS_AVAILABLE_IOS(_iOSIntro)    NS_CLASS_AVAILABLE_IOS(_iOSIntro)
#define HK_AVAILABLE_WATCHOS_ONLY(_watchOSIntro)    __WATCHOS_AVAILABLE(_watchOSIntro) __IOS_UNAVAILABLE
#define HK_CLASS_AVAILABLE_WATCHOS_ONLY(_watchOSIntro)    HK_EXTERN HK_AVAILABLE_WATCHOS_ONLY(_watchOSIntro)

HK_EXTERN NSString * const HKErrorDomain NS_AVAILABLE_IOS(8_0);

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
    HKErrorAnotherWorkoutSessionStarted NS_ENUM_AVAILABLE_IOS(9_0),
    HKErrorUserExitedWorkoutSession     NS_ENUM_AVAILABLE_IOS(9_0),
} NS_ENUM_AVAILABLE_IOS(8_0);

/*!
 @enum      HKUpdateFrequency
 */
typedef NS_ENUM(NSInteger, HKUpdateFrequency) {
    HKUpdateFrequencyImmediate = 1,
    HKUpdateFrequencyHourly,
    HKUpdateFrequencyDaily,
    HKUpdateFrequencyWeekly,
} NS_ENUM_AVAILABLE_IOS(8_0);

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
} NS_ENUM_AVAILABLE_IOS(8_0);

/*!
 @enum       HKBiologicalSex
 @abstract   This enumerated type is used to represent the biological sex of an individual.
 */
typedef NS_ENUM(NSInteger, HKBiologicalSex) {
    HKBiologicalSexNotSet = 0,
    HKBiologicalSexFemale NS_ENUM_AVAILABLE_IOS(8_0),
    HKBiologicalSexMale NS_ENUM_AVAILABLE_IOS(8_0),
    HKBiologicalSexOther NS_ENUM_AVAILABLE_IOS(8_2),
};

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
} NS_ENUM_AVAILABLE_IOS(8_0);

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
} NS_ENUM_AVAILABLE_IOS(8_0);


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
} NS_ENUM_AVAILABLE_IOS(9_0);

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
} NS_ENUM_AVAILABLE_IOS(9_0);

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
} NS_ENUM_AVAILABLE_IOS(9_0);

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
} NS_ENUM_AVAILABLE_IOS(9_0);

/*!
 @enum          HKCategoryValueMenstrualFlow
 @abstract      Set of values to indicate the type of menstrual flow.
 */
typedef NS_ENUM(NSInteger, HKCategoryValueMenstrualFlow) {
    HKCategoryValueMenstrualFlowUnspecified = 1,
    HKCategoryValueMenstrualFlowLight,
    HKCategoryValueMenstrualFlowMedium,
    HKCategoryValueMenstrualFlowHeavy
} NS_ENUM_AVAILABLE_IOS(9_0);

/*!
 @enum          HKCategoryValue
 @abstract      This category value is to be used for types which don't have a specific value defined.
 */
typedef NS_ENUM(NSInteger, HKCategoryValue) {
    HKCategoryValueNotApplicable = 0,
} NS_ENUM_AVAILABLE_IOS(9_0);

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
HK_EXTERN NSString * const HKDevicePropertyKeyName NS_AVAILABLE_IOS(9_0);

/*!
 @constant      HKDevicePropertyKeyManufacturer
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a device manufacturer.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyManufacturer NS_AVAILABLE_IOS(9_0);

/*!
 @constant      HKDevicePropertyKeyModel
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a device model.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyModel NS_AVAILABLE_IOS(9_0);

/*!
 @constant      HKDevicePropertyKeyHardwareVersion
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a hardware version.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyHardwareVersion NS_AVAILABLE_IOS(9_0);

/*!
 @constant      HKDevicePropertyKeyFirmwareVersion
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a firmware version.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyFirmwareVersion NS_AVAILABLE_IOS(9_0);

/*!
 @constant      HKDevicePropertyKeySoftwareVersion
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a software version.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeySoftwareVersion NS_AVAILABLE_IOS(9_0);

/*!
 @constant      HKDevicePropertyKeyLocalIdentifier
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a local identifier.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyLocalIdentifier NS_AVAILABLE_IOS(9_0);

/*!
 @constant      HKDevicePropertyKeyUDIDeviceIdentifier
 @abstract      Used with predicateForObjectsWithDeviceProperty to specify a UDI device identifier.
 @discussion    The expected value type is an NSString.
 */
HK_EXTERN NSString * const HKDevicePropertyKeyUDIDeviceIdentifier NS_AVAILABLE_IOS(9_0);



HK_CLASS_AVAILABLE_IOS(9_0)
@interface HKDevice : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      name
 @abstract      The name of the receiver.
 @discussion    The user-facing name, such as the one displayed in the Bluetooth Settings for a BLE device.
 */
@property (readonly) NSString *name;

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
- (instancetype)initWithName:(NSString * __nullable)name
                manufacturer:(NSString * __nullable)manufacturer
                       model:(NSString * __nullable)model
             hardwareVersion:(NSString * __nullable)hardwareVersion
             firmwareVersion:(NSString * __nullable)firmwareVersion
             softwareVersion:(NSString * __nullable)softwareVersion
             localIdentifier:(NSString * __nullable)localIdentifier
         UDIDeviceIdentifier:(NSString * __nullable)UDIDeviceIdentifier;

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
//  Copyright (c) 2015 Apple. All rights reserved.
//

#import <HealthKit/HKWorkout.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum          HKWorkoutSessionState
 @abstract      This enumerated type is used to represent the state of a workout session.
 */
typedef NS_ENUM(NSInteger, HKWorkoutSessionState) {
    HKWorkoutSessionStateNotStarted = 1,
    HKWorkoutSessionStateRunning,
    HKWorkoutSessionStateEnded,
} HK_AVAILABLE_WATCHOS_ONLY(2_0);


/*!
 @enum          HKWorkoutSessionLocationType
 @abstract      This enumerated type is used to represent the location type of a workout session.
 @discussion    This value represents whether a workout is performed indoors or outdoors.
 */
typedef NS_ENUM(NSInteger, HKWorkoutSessionLocationType) {
    HKWorkoutSessionLocationTypeUnknown = 1,
    HKWorkoutSessionLocationTypeIndoor,
    HKWorkoutSessionLocationTypeOutdoor,
} HK_AVAILABLE_WATCHOS_ONLY(2_0);


@protocol HKWorkoutSessionDelegate;

/*!
 @class         HKWorkoutSession
 @abstract      An HKWorkoutSession is an object describing the properties of a workout activity session.
 */
HK_CLASS_AVAILABLE_WATCHOS_ONLY(2_0)
@interface HKWorkoutSession : NSObject <NSSecureCoding>

/*!
 @property      activityType
 @abstract      Indicates the type of workout that will be performed during the session.
 */
@property (readonly) HKWorkoutActivityType activityType;

/*!
 @property      locationType
 @abstract      Indicates the type of location (indoors vs. outdoors) where the workout will take place.
 @discussion    Knowing the location type allows for more accurate measurements and better performance.
 */
@property (readonly) HKWorkoutSessionLocationType locationType;

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
                        locationType:(HKWorkoutSessionLocationType)locationType;

- (instancetype)init NS_UNAVAILABLE;

@end


/*!
 @enum          HKWorkoutSessionStateDelegate
 @abstract      This protocol should be implemented to be notified when a workout session's state changes.
 @discussion    The methods on this protocol are called on an anonymous serial background queue.
 */
HK_AVAILABLE_WATCHOS_ONLY(2_0)
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
HK_CLASS_AVAILABLE_IOS(8_0)
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
                  completion:(void(^)(HKCorrelationQuery *query, NSArray<HKCorrelation *> * __nullable correlations, NSError * __nullable error))completion;
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
HK_CLASS_AVAILABLE_IOS(9_0)
@interface HKDeletedObject : NSObject <NSSecureCoding>

/*!
 @property      UUID
 @abstract      The unique identifier of the HKObject that was deleted from the HealthKit database.
 */
@property (readonly, strong) NSUUID *UUID;

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
 @constant      HKStatisticsOptionDiscreteAverage   Calculate averageQuantity when creating statistics.
 @constant      HKStatisticsOptionDiscreteMin       Calculate minQuantity when creating statistics.
 @constant      HKStatisticsOptionDiscreteMax       Calculate maxQuantity when creating statistics.
 @constant      HKStatisticsOptionCumulativeSum     Calculate sumQuantity when creating statistics.
 */
typedef NS_OPTIONS(NSUInteger, HKStatisticsOptions) {
    HKStatisticsOptionNone              		= 0,
    HKStatisticsOptionSeparateBySource          = 1 << 0,
    HKStatisticsOptionDiscreteAverage           = 1 << 1,
    HKStatisticsOptionDiscreteMin               = 1 << 2,
    HKStatisticsOptionDiscreteMax               = 1 << 3,
    HKStatisticsOptionCumulativeSum             = 1 << 4,
} NS_ENUM_AVAILABLE_IOS(8_0);

/*!
 @class         HKStatistics
 @abstract      Represents statistics for quantity samples over a period of time.
 */
HK_CLASS_AVAILABLE_IOS(8_0)
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
HK_CLASS_AVAILABLE_IOS(8_0)
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
// ==========  HealthKit.framework/Headers/HKObjectType.h
//
//  HKObjectType.h
//  HealthKit
//
//  Copyright (c) 2013-2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>
#import <HealthKit/HKTypeIdentifiers.h>

NS_ASSUME_NONNULL_BEGIN

@class HKUnit;
@class HKQuantityType;
@class HKCategoryType;
@class HKWorkoutType;
@class HKCharacteristicType;
@class HKCorrelationType;

/*!
 @class         HKObjectType
 @abstract      An abstract class representing a type of object that can be stored by HealthKit.
 */
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKObjectType : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      identifier
 @abstract      A unique string identifying a type of health object.
 @discussion    See HKTypeIdentifiers.h for possible values.
 */
@property (readonly, strong) NSString *identifier;

- (instancetype)init NS_UNAVAILABLE;

+ (nullable HKQuantityType *)quantityTypeForIdentifier:(NSString *)identifier;
+ (nullable HKCategoryType *)categoryTypeForIdentifier:(NSString *)identifier;
+ (nullable HKCharacteristicType *)characteristicTypeForIdentifier:(NSString *)identifier;
+ (nullable HKCorrelationType *)correlationTypeForIdentifier:(NSString *)identifier;
+ (HKWorkoutType *)workoutType;

@end

/*!
 @class         HKCharacteristicType
 @abstract      Represents a type of object that desribes a characteristic of the user (such as date of birth).
 */
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKCharacteristicType : HKObjectType
@end

/*!
 @class         HKSampleType
 @abstract      Represents a type of HKSample.
 */
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKSampleType : HKObjectType
@end

/*!
 @class         HKCategoryType
 @abstract      Represent a type of HKCategorySample.
 */
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKCategoryType : HKSampleType
@end

/*!
 @class         HKCorrelationType
 @abstract      Represents a type of HKCorrelation
 */
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKCorrelationType : HKSampleType
@end

/*!
 @enum          HKQuantityAggregationStyle
 @discussion    Describes how quantities can be aggregated over time.
 
 @constant      HKQuantityAggregationStyleCumulative    Samples may be summed over a time interval.
 @constant      HKQuantityAggregationStyleDiscrete      Samples may be averaged over a time interval.
 */
typedef NS_ENUM(NSInteger, HKQuantityAggregationStyle) {
    HKQuantityAggregationStyleCumulative = 0,
    HKQuantityAggregationStyleDiscrete,
} NS_ENUM_AVAILABLE_IOS(8_0);

/*!
 @class         HKQuantityType
 @abstract      Represents types of HKQuantitySamples.
 */
HK_CLASS_AVAILABLE_IOS(8_0)
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
 @class         HKCategoryType
 @abstract      Represents a workout or exercise
 */
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKWorkoutType : HKSampleType
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
@class HKWorkoutEvent;

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
    HKWorkoutActivityTypeBoxing, // Kickboxing, Boxing, etc.
    HKWorkoutActivityTypeClimbing,
    HKWorkoutActivityTypeCricket,
    HKWorkoutActivityTypeCrossTraining, // Any mix of cardio and/or strength and/or flexibility
    HKWorkoutActivityTypeCurling,
    HKWorkoutActivityTypeCycling,
    HKWorkoutActivityTypeDance,
    HKWorkoutActivityTypeDanceInspiredTraining, // Pilates, Barre, Feldenkrais, etc.
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
    HKWorkoutActivityTypeMindAndBody, // Tai chi, meditation, etc.
    HKWorkoutActivityTypeMixedMetabolicCardioTraining, // Any mix of cardio-focused exercises
    HKWorkoutActivityTypePaddleSports, // Canoeing, Kayaking, Outrigger, Stand Up Paddle Board, etc.
    HKWorkoutActivityTypePlay, // Dodge Ball, Hopscotch, Tetherball, Jungle Gym, etc.
    HKWorkoutActivityTypePreparationAndRecovery, // Foam rolling, stretching, etc.
    HKWorkoutActivityTypeRacquetball,
    HKWorkoutActivityTypeRowing,
    HKWorkoutActivityTypeRugby,
    HKWorkoutActivityTypeRunning,
    HKWorkoutActivityTypeSailing,
    HKWorkoutActivityTypeSkatingSports, // Ice Skating, Speed Skating, Inline Skating, Skateboarding, etc.
    HKWorkoutActivityTypeSnowSports, // Skiing, Snowboarding, Cross-Country Skiing, etc.
    HKWorkoutActivityTypeSoccer,
    HKWorkoutActivityTypeSoftball,
    HKWorkoutActivityTypeSquash,
    HKWorkoutActivityTypeStairClimbing,
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
    
    HKWorkoutActivityTypeOther = 3000,
} NS_ENUM_AVAILABLE_IOS(8_0);

typedef NS_ENUM(NSInteger, HKWorkoutEventType) {
    HKWorkoutEventTypePause = 1,
    HKWorkoutEventTypeResume
} NS_ENUM_AVAILABLE_IOS(8_0);

/*!
 @class         HKWorkoutEvent
 @abstract      Represents a particular event that occurred during a workout
 */
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKWorkoutEvent : NSObject <NSSecureCoding>

@property (readonly, assign) HKWorkoutEventType type;
@property (readonly, copy) NSDate *date;

+ (instancetype)workoutEventWithType:(HKWorkoutEventType)type date:(NSDate *)date;
- (instancetype)init NS_UNAVAILABLE;

@end

/*!
 @class         HKWorkout
 @abstract      An HKObject subclass representing a workout or activity
 */
HK_CLASS_AVAILABLE_IOS(8_0)
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
 @discussion    The duration is derived from the start an end date of the workout, and takes into account periods that the 
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
 @param         device                  The HKDevice associated with the workout (optional).
 @param         metadata                Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                          workoutEvents:(nullable NSArray<HKWorkoutEvent *> *)workoutEvents
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                                 device:(nullable HKDevice *)device
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata NS_AVAILABLE_IOS(9_0);

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
 @param         device                  The HKDevice associated with the workout (optional).
 @param         metadata                Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                               duration:(NSTimeInterval)duration
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                                 device:(nullable HKDevice *)device
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata NS_AVAILABLE_IOS(9_0);

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutDuration NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutTotalDistance NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutTotalEnergyBurned NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutType NS_AVAILABLE_IOS(8_0);

// Sort Identifiers
HK_EXTERN NSString * const HKWorkoutSortIdentifierDuration NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKWorkoutSortIdentifierTotalDistance NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKWorkoutSortIdentifierTotalEnergyBurned NS_AVAILABLE_IOS(8_0);

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

HK_CLASS_AVAILABLE_IOS(8_0)
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

HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKStatisticsCollectionQuery : HKQuery

@property (readonly, strong) NSDate *anchorDate;
@property (readonly) HKStatisticsOptions options;
@property (readonly, copy) NSDateComponents *intervalComponents;

@property (nonatomic, copy, nullable) void(^initialResultsHandler)(HKStatisticsCollectionQuery *query, HKStatisticsCollection * __nullable result, NSError * __nullable error);
@property (nonatomic, copy, nullable) void(^statisticsUpdateHandler)(HKStatisticsCollectionQuery *query, HKStatistics * __nullable statistics, HKStatisticsCollection * __nullable collection, NSError * __nullable error);

- (instancetype)initWithQuantityType:(HKQuantityType *)quantityType
             quantitySamplePredicate:(nullable NSPredicate *)quantitySamplePredicate
                             options:(HKStatisticsOptions)options
                          anchorDate:(NSDate *)anchorDate
                  intervalComponents:(NSDateComponents *)intervalComponents;

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

NS_ASSUME_NONNULL_BEGIN

/*--------------------------------*/
/*   HKQuantityType Identifiers   */
/*--------------------------------*/

// Body Measurements
HK_EXTERN NSString * const HKQuantityTypeIdentifierBodyMassIndex NS_AVAILABLE_IOS(8_0);             // Scalar(Count),               Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierBodyFatPercentage NS_AVAILABLE_IOS(8_0);         // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierHeight NS_AVAILABLE_IOS(8_0);                    // Length,                      Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierBodyMass NS_AVAILABLE_IOS(8_0);                  // Mass,                        Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierLeanBodyMass NS_AVAILABLE_IOS(8_0);              // Mass,                        Discrete

// Fitness
HK_EXTERN NSString * const HKQuantityTypeIdentifierStepCount NS_AVAILABLE_IOS(8_0);                 // Scalar(Count),               Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDistanceWalkingRunning NS_AVAILABLE_IOS(8_0);    // Length,                      Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDistanceCycling NS_AVAILABLE_IOS(8_0);           // Length,                      Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierBasalEnergyBurned NS_AVAILABLE_IOS(8_0);         // Energy,                      Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierActiveEnergyBurned NS_AVAILABLE_IOS(8_0);        // Energy,                      Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierFlightsClimbed NS_AVAILABLE_IOS(8_0);            // Scalar(Count),               Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierNikeFuel NS_AVAILABLE_IOS(8_0);                  // Scalar(Count),               Cumulative

// Vitals
HK_EXTERN NSString * const HKQuantityTypeIdentifierHeartRate NS_AVAILABLE_IOS(8_0);                 // Scalar(Count)/Time,          Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierBodyTemperature NS_AVAILABLE_IOS(8_0);           // Temperature,                 Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierBasalBodyTemperature NS_AVAILABLE_IOS(9_0);      // Basal Body Temperature,      Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierBloodPressureSystolic NS_AVAILABLE_IOS(8_0);     // Pressure,                    Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierBloodPressureDiastolic NS_AVAILABLE_IOS(8_0);    // Pressure,                    Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierRespiratoryRate NS_AVAILABLE_IOS(8_0);           // Scalar(Count)/Time,          Discrete

// Results
HK_EXTERN NSString * const HKQuantityTypeIdentifierOxygenSaturation NS_AVAILABLE_IOS(8_0);          // Scalar (Percent, 0.0 - 1.0,  Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierPeripheralPerfusionIndex NS_AVAILABLE_IOS(8_0);  // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierBloodGlucose NS_AVAILABLE_IOS(8_0);              // Mass/Volume,                 Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierNumberOfTimesFallen NS_AVAILABLE_IOS(8_0);       // Scalar(Count),               Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierElectrodermalActivity NS_AVAILABLE_IOS(8_0);     // Conductance,                 Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierInhalerUsage NS_AVAILABLE_IOS(8_0);              // Scalar(Count),               Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierBloodAlcoholContent NS_AVAILABLE_IOS(8_0);       // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierForcedVitalCapacity NS_AVAILABLE_IOS(8_0);       // Volume,                      Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierForcedExpiratoryVolume1 NS_AVAILABLE_IOS(8_0);   // Volume,                      Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierPeakExpiratoryFlowRate NS_AVAILABLE_IOS(8_0);    // Volume/Time,                 Discrete

// Nutrition
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryFatTotal NS_AVAILABLE_IOS(8_0);           // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryFatPolyunsaturated NS_AVAILABLE_IOS(8_0); // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryFatMonounsaturated NS_AVAILABLE_IOS(8_0); // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryFatSaturated NS_AVAILABLE_IOS(8_0);       // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryCholesterol NS_AVAILABLE_IOS(8_0);        // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietarySodium NS_AVAILABLE_IOS(8_0);             // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryCarbohydrates NS_AVAILABLE_IOS(8_0);      // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryFiber NS_AVAILABLE_IOS(8_0);              // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietarySugar NS_AVAILABLE_IOS(8_0);              // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryEnergyConsumed NS_AVAILABLE_IOS(8_0);     // Energy, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryProtein NS_AVAILABLE_IOS(8_0);            // Mass,   Cumulative

HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryVitaminA NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryVitaminB6 NS_AVAILABLE_IOS(8_0);          // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryVitaminB12 NS_AVAILABLE_IOS(8_0);         // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryVitaminC NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryVitaminD NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryVitaminE NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryVitaminK NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryCalcium NS_AVAILABLE_IOS(8_0);            // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryIron NS_AVAILABLE_IOS(8_0);               // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryThiamin NS_AVAILABLE_IOS(8_0);            // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryRiboflavin NS_AVAILABLE_IOS(8_0);         // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryNiacin NS_AVAILABLE_IOS(8_0);             // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryFolate NS_AVAILABLE_IOS(8_0);             // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryBiotin NS_AVAILABLE_IOS(8_0);             // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryPantothenicAcid NS_AVAILABLE_IOS(8_0);    // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryPhosphorus NS_AVAILABLE_IOS(8_0);         // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryIodine NS_AVAILABLE_IOS(8_0);             // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryMagnesium NS_AVAILABLE_IOS(8_0);          // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryZinc NS_AVAILABLE_IOS(8_0);               // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietarySelenium NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryCopper NS_AVAILABLE_IOS(8_0);             // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryManganese NS_AVAILABLE_IOS(8_0);          // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryChromium NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryMolybdenum NS_AVAILABLE_IOS(8_0);         // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryChloride NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryPotassium NS_AVAILABLE_IOS(8_0);          // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryCaffeine NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryWater NS_AVAILABLE_IOS(9_0);              // Volume, Cumulative

HK_EXTERN NSString * const HKQuantityTypeIdentifierUVExposure NS_AVAILABLE_IOS(9_0);                // Scalar (Count), Discrete

/*--------------------------------*/
/*   HKCategoryType Identifiers   */
/*--------------------------------*/

HK_EXTERN NSString * const HKCategoryTypeIdentifierSleepAnalysis NS_AVAILABLE_IOS(8_0);             // HKCategoryValueSleepAnalysis
HK_EXTERN NSString * const HKCategoryTypeIdentifierAppleStandHour NS_AVAILABLE_IOS(9_0);            // HKCategoryValueAppleStandHour
HK_EXTERN NSString * const HKCategoryTypeIdentifierCervicalMucusQuality NS_AVAILABLE_IOS(9_0);      // HKCategoryValueCervicalMucusQuality
HK_EXTERN NSString * const HKCategoryTypeIdentifierOvulationTestResult NS_AVAILABLE_IOS(9_0);       // HKCategoryValueOvulationTestResult
HK_EXTERN NSString * const HKCategoryTypeIdentifierMenstrualFlow NS_AVAILABLE_IOS(9_0);             // HKCategoryValueMenstrualFlow
HK_EXTERN NSString * const HKCategoryTypeIdentifierIntermenstrualBleeding NS_AVAILABLE_IOS(9_0);    // (Spotting) HKCategoryValue
HK_EXTERN NSString * const HKCategoryTypeIdentifierSexualActivity NS_AVAILABLE_IOS(9_0);            // HKCategoryValue


/*--------------------------------------*/
/*   HKCharacteristicType Identifiers   */
/*--------------------------------------*/

HK_EXTERN NSString * const HKCharacteristicTypeIdentifierBiologicalSex NS_AVAILABLE_IOS(8_0); // NSNumber (HKCharacteristicBiologicalSex)
HK_EXTERN NSString * const HKCharacteristicTypeIdentifierBloodType NS_AVAILABLE_IOS(8_0);     // NSNumber (HKCharacteristicBloodType)
HK_EXTERN NSString * const HKCharacteristicTypeIdentifierDateOfBirth NS_AVAILABLE_IOS(8_0);   // NSDate
HK_EXTERN NSString * const HKCharacteristicTypeIdentifierFitzpatrickSkinType NS_AVAILABLE_IOS(9_0); // HKFitzpatrickSkinType

/*-----------------------------------*/
/*   HKCorrelationType Identifiers   */
/*-----------------------------------*/

HK_EXTERN NSString * const HKCorrelationTypeIdentifierBloodPressure NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKCorrelationTypeIdentifierFood NS_AVAILABLE_IOS(8_0);

/*------------------------------*/
/*   HKWorkoutType Identifier   */
/*------------------------------*/

HK_EXTERN NSString * const HKWorkoutTypeIdentifier NS_AVAILABLE_IOS(8_0);

NS_ASSUME_NONNULL_END
