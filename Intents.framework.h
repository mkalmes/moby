// ==========  Intents.framework/Headers/INRestaurantReservationBooking.h
//
//  INRestaurantReservationBooking.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Foundation/Foundation.h>
#import <Intents/INRestaurant.h>
#import <Intents/INRestaurantOffer.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
// represents a booking at a restaurant during a given time for a given party size
@interface INRestaurantReservationBooking : NSObject <NSSecureCoding, NSCopying>

- (instancetype)initWithRestaurant:(INRestaurant *)restaurant bookingDate:(NSDate *)bookingDate partySize:(NSUInteger)partySize bookingIdentifier:(NSString *)bookingIdentifier NS_DESIGNATED_INITIALIZER;

@property (copy, NS_NONATOMIC_IOSONLY) INRestaurant *restaurant;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *bookingDescription; // A nullable string describing the booking
@property (copy, NS_NONATOMIC_IOSONLY) NSDate *bookingDate;
@property (NS_NONATOMIC_IOSONLY) NSUInteger partySize;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *bookingIdentifier; // A vendor specific identifier that refers to this booking.
@property (getter = isBookingAvailable, NS_NONATOMIC_IOSONLY) BOOL bookingAvailable; // Boolean indicating whether timeslot is available for booking. Defaults to YES.
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSArray <INRestaurantOffer *> *offers;
@property (NS_NONATOMIC_IOSONLY) BOOL requiresManualRequest; // YES means restaurant must be contacted by phone before confirmation is given. Defaults to NO.
@property (NS_NONATOMIC_IOSONLY) BOOL requiresEmailAddress; // YES means an email address is required to book. Defaults to NO.
@property (NS_NONATOMIC_IOSONLY) BOOL requiresName; // YES means a name is required to book. Defaults to NO.
@property (NS_NONATOMIC_IOSONLY) BOOL requiresPhoneNumber; // YES means a phone number required to book. Defaults to NO.

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INGetAvailableRestaurantReservationBookingDefaultsIntentResponse.h
//
//  INGetAvailableRestaurantReservationBookingDefaultsIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntentResponse.h>
#import <Intents/INImage.h>

typedef NS_ENUM(NSInteger, INGetAvailableRestaurantReservationBookingDefaultsIntentResponseCode) {
    INGetAvailableRestaurantReservationBookingDefaultsIntentResponseCodeSuccess,
    INGetAvailableRestaurantReservationBookingDefaultsIntentResponseCodeFailure,
    INGetAvailableRestaurantReservationBookingDefaultsIntentResponseCodeUnspecified
};

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INGetAvailableRestaurantReservationBookingDefaultsIntentResponse : INIntentResponse

@property (readonly, NS_NONATOMIC_IOSONLY) NSUInteger defaultPartySize; // default party size for an available bookings request
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSDate *defaultBookingDate; // default booking time for an available bookings request
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *maximumPartySize;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *minimumPartySize;
@property (copy, NS_NONATOMIC_IOSONLY) INImage *providerImage;

- (instancetype)initWithDefaultPartySize:(NSUInteger)defaultPartySize defaultBookingDate:(NSDate *)defaultBookingDate code:(INGetAvailableRestaurantReservationBookingDefaultsIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INGetAvailableRestaurantReservationBookingDefaultsIntentResponseCode code;

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCancelRideIntentResponse.h
//
//  INCancelRideIntentResponse.h
//  Intents
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INCurrencyAmount;

typedef NS_ENUM(NSInteger, INCancelRideIntentResponseCode) {
    INCancelRideIntentResponseCodeUnspecified = 0,
    INCancelRideIntentResponseCodeReady,
    INCancelRideIntentResponseCodeSuccess,
    INCancelRideIntentResponseCodeFailure,
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0))
API_UNAVAILABLE(watchos, macos)
@interface INCancelRideIntentResponse : INIntentResponse

- (instancetype)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INCancelRideIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INCancelRideIntentResponseCode code;
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *cancellationFee; // Used during confirmation to warn the user about any cancellation fees
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *cancellationFeeThreshold; // The time after which canceling the ride will incur the cancellation fee

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCallRecordTypeOptionsResolutionResult.h
//
//  INCallRecordTypeOptionsResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCallRecordTypeOptions.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13))
@interface INCallRecordTypeOptionsResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INCallRecordTypeOptions. The resolvedValue can be different than the original INCallRecordTypeOptions. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedCallRecordTypeOptions:(INCallRecordTypeOptions)resolvedCallRecordTypeOptions NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INCallRecordTypeOptions)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedCallRecordTypeOptions:", ios(10.0, 11.0), watchos(3.2, 4.0), macos(10.12, 10.13));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithCallRecordTypeOptionsToConfirm:(INCallRecordTypeOptions)callRecordTypeOptionsToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INCallRecordTypeOptions)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithCallRecordTypeOptionsToConfirm:", ios(10.0, 11.0), watchos(3.2, 4.0), macos(10.12, 10.13));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INDoubleResolutionResult.h
//
//  INDoubleResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx)
@interface INDoubleResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given number. The resolvedValue can be different than the original number. This allows app extensions to apply business logic constraints. For example, the extension could precisely control rounding the value.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedValue:(double)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the double value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(nullable NSNumber *)valueToConfirm NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCarDefroster.h
//
//  INCarDefroster.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INCarDefroster_h
#define INCarDefroster_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCarDefroster) {
    INCarDefrosterUnknown = 0,
    INCarDefrosterFront,
    INCarDefrosterRear,
    INCarDefrosterAll,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

#endif // INCarDefroster_h
// ==========  Intents.framework/Headers/INVisualCodeType.h
//
//  INVisualCodeType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INVisualCodeType_h
#define INVisualCodeType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INVisualCodeType) {
    INVisualCodeTypeUnknown = 0,
    INVisualCodeTypeContact,
    INVisualCodeTypeRequestPayment,
    INVisualCodeTypeSendPayment,
    INVisualCodeTypeTransit API_AVAILABLE(ios(12.0), watchos(5.0)),
    INVisualCodeTypeBus API_AVAILABLE(ios(12.0), watchos(5.0)),
    INVisualCodeTypeSubway API_AVAILABLE(ios(12.0), watchos(5.0)),
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

#endif // INVisualCodeType_h
// ==========  Intents.framework/Headers/INMessageAttributeResolutionResult.h
//
//  INMessageAttributeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INMessageAttribute.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INMessageAttributeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INMessageAttribute. The resolvedValue can be different than the original INMessageAttribute. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedMessageAttribute:(INMessageAttribute)resolvedMessageAttribute NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INMessageAttribute)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedMessageAttribute:", ios(10.0, 11.0), watchos(3.2, 4.0));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithMessageAttributeToConfirm:(INMessageAttribute)messageAttributeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INMessageAttribute)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithMessageAttributeToConfirm:", ios(10.0, 11.0), watchos(3.2, 4.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRelevantShortcut.h
//
//  INRelevantShortcut.h
//  Intents
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Intents/INRelevanceProvider.h>
#import <Intents/INDefaultCardTemplate.h>
#import <Intents/INShortcut.h>

@class INShortcut;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, INRelevantShortcutRole) {
    INRelevantShortcutRoleAction,
    INRelevantShortcutRoleInformation,
} API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macosx);

API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macosx)
@interface INRelevantShortcut : NSObject <NSSecureCoding, NSCopying>

@property (copy, NS_NONATOMIC_IOSONLY) NSArray<INRelevanceProvider *> *relevanceProviders;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INDefaultCardTemplate *watchTemplate;
@property (NS_NONATOMIC_IOSONLY) INRelevantShortcutRole shortcutRole;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INShortcut *shortcut;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithShortcut:(INShortcut *)shortcut NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSaveProfileInCarIntentResponse.h
//
//  INSaveProfileInCarIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSaveProfileInCarIntentResponseCode) {
    INSaveProfileInCarIntentResponseCodeUnspecified = 0,
    INSaveProfileInCarIntentResponseCodeReady,
    INSaveProfileInCarIntentResponseCodeInProgress,
    INSaveProfileInCarIntentResponseCodeSuccess,
    INSaveProfileInCarIntentResponseCodeFailure,
    INSaveProfileInCarIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos, macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INSaveProfileInCarIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSaveProfileInCarIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSaveProfileInCarIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetSeatSettingsInCarIntent_Deprecated.h
//
//  INSetSeatSettingsInCarIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2018 Apple Inc. All rights reserved.
//

#import <Intents/INSetSeatSettingsInCarIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSetSeatSettingsInCarIntent (Deprecated)

- (instancetype)initWithEnableHeating:(nullable NSNumber *)enableHeating
                        enableCooling:(nullable NSNumber *)enableCooling
                        enableMassage:(nullable NSNumber *)enableMassage
                                 seat:(INCarSeat)seat
                                level:(nullable NSNumber *)level
                 relativeLevelSetting:(INRelativeSetting)relativeLevelSetting API_DEPRECATED_WITH_REPLACEMENT("-initWithEnableHeating:enableCooling:enableMassage:seat:level:relativeLevelSetting:relativeLevelSetting:carName:", ios(10.0, 12.0)) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INGetCarPowerLevelStatusIntentResponse.h
//
//  INGetCarPowerLevelStatusIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INGetCarPowerLevelStatusIntentResponseCode) {
    INGetCarPowerLevelStatusIntentResponseCodeUnspecified = 0,
    INGetCarPowerLevelStatusIntentResponseCodeReady,
    INGetCarPowerLevelStatusIntentResponseCodeInProgress,
    INGetCarPowerLevelStatusIntentResponseCodeSuccess,
    INGetCarPowerLevelStatusIntentResponseCodeFailure,
    INGetCarPowerLevelStatusIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INGetCarPowerLevelStatusIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INGetCarPowerLevelStatusIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INGetCarPowerLevelStatusIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *fuelPercentRemaining NS_REFINED_FOR_SWIFT;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *chargePercentRemaining NS_REFINED_FOR_SWIFT;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSMeasurement<NSUnitLength *> *distanceRemaining;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *charging NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(12.0), watchos(5.0));

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *minutesToFull NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(12.0), watchos(5.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INIntents.h
//
//  INIntents.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INSearchCallHistoryIntent.h>
#import <Intents/INStartAudioCallIntent.h>
#import <Intents/INStartVideoCallIntent.h>

#import <Intents/INActivateCarSignalIntent.h>
#import <Intents/INGetCarLockStatusIntent.h>
#import <Intents/INGetCarPowerLevelStatusIntent.h>
#import <Intents/INSaveProfileInCarIntent.h>
#import <Intents/INSetAudioSourceInCarIntent.h>
#import <Intents/INSetCarLockStatusIntent.h>
#import <Intents/INSetClimateSettingsInCarIntent.h>
#import <Intents/INSetDefrosterSettingsInCarIntent.h>
#import <Intents/INSetProfileInCarIntent.h>
#import <Intents/INSetSeatSettingsInCarIntent.h>

#import <Intents/INCancelWorkoutIntent.h>
#import <Intents/INEndWorkoutIntent.h>
#import <Intents/INPauseWorkoutIntent.h>
#import <Intents/INResumeWorkoutIntent.h>
#import <Intents/INStartWorkoutIntent.h>

#import <Intents/INPlayMediaIntent.h>

#import <Intents/INSetRadioStationIntent.h>

#import <Intents/INSearchForMessagesIntent.h>
#import <Intents/INSendMessageIntent.h>
#import <Intents/INSetMessageAttributeIntent.h>

#import <Intents/INAddTasksIntent.h>
#import <Intents/INAppendToNoteIntent.h>
#import <Intents/INCreateNoteIntent.h>
#import <Intents/INCreateTaskListIntent.h>
#import <Intents/INSearchForNotebookItemsIntent.h>
#import <Intents/INSetTaskAttributeIntent.h>

#import <Intents/INPayBillIntent.h>
#import <Intents/INRequestPaymentIntent.h>
#import <Intents/INSearchForAccountsIntent.h>
#import <Intents/INSearchForBillsIntent.h>
#import <Intents/INSendPaymentIntent.h>
#import <Intents/INTransferMoneyIntent.h>

#import <Intents/INSearchForPhotosIntent.h>
#import <Intents/INStartPhotoPlaybackIntent.h>

#import <Intents/INGetRideStatusIntent.h>
#import <Intents/INListRideOptionsIntent.h>
#import <Intents/INRequestRideIntent.h>
#import <Intents/INCancelRideIntent.h>
#import <Intents/INSendRideFeedbackIntent.h>

#import <Intents/INGetVisualCodeIntent.h>

// ==========  Intents.framework/Headers/INSendRideFeedbackIntentResponse.h
//
//  INSendRideFeedbackIntentResponse.h
//  Intents
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSendRideFeedbackIntentResponseCode) {
    INSendRideFeedbackIntentResponseCodeUnspecified = 0,
    INSendRideFeedbackIntentResponseCodeReady,
    INSendRideFeedbackIntentResponseCodeSuccess,
    INSendRideFeedbackIntentResponseCodeFailure,
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0))
API_UNAVAILABLE(watchos, macos)
@interface INSendRideFeedbackIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSendRideFeedbackIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSendRideFeedbackIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSearchForMessagesIntent_Deprecated.h
//
//  INRequestRideIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INSearchForMessagesIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSearchForMessagesIntent (DeprecatedSearchForMessages)

- (instancetype)initWithRecipients:(nullable NSArray<INPerson *> *)recipients
                           senders:(nullable NSArray<INPerson *> *)senders
                       searchTerms:(nullable NSArray<NSString *> *)searchTerms
                        attributes:(INMessageAttributeOptions)attributes
                     dateTimeRange:(nullable INDateComponentsRange *)dateTimeRange
                       identifiers:(nullable NSArray<NSString *> *)identifiers
           notificationIdentifiers:(nullable NSArray<NSString *> *)notificationIdentifiers
                        groupNames:(nullable NSArray<NSString *> *)groupNames API_DEPRECATED("Use the designated initializer instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

- (instancetype)initWithRecipients:(nullable NSArray<INPerson *> *)recipients
                           senders:(nullable NSArray<INPerson *> *)senders
                       searchTerms:(nullable NSArray<NSString *> *)searchTerms
                        attributes:(INMessageAttributeOptions)attributes
                     dateTimeRange:(nullable INDateComponentsRange *)dateTimeRange
                       identifiers:(nullable NSArray<NSString *> *)identifiers
           notificationIdentifiers:(nullable NSArray<NSString *> *)notificationIdentifiers
               speakableGroupNames:(nullable NSArray<INSpeakableString *> *)speakableGroupNames API_DEPRECATED("Use the designated initializer instead", ios(11.0, 12.0), watchos(4.0, 5.0), macosx(10.13, 10.14));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *groupNames API_DEPRECATED("Use speakableGroupNames instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator groupNamesOperator API_DEPRECATED("Use speakableGroupNamesOperator instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCarSeat.h
//
//  INCarSeat.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INCarSeat_h
#define INCarSeat_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCarSeat) {
    INCarSeatUnknown = 0,
    INCarSeatDriver,
    INCarSeatPassenger,
    INCarSeatFrontLeft,
    INCarSeatFrontRight,
    INCarSeatFront,
    INCarSeatRearLeft,
    INCarSeatRearRight,
    INCarSeatRear,
    INCarSeatThirdRowLeft,
    INCarSeatThirdRowRight,
    INCarSeatThirdRow,
    INCarSeatAll,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

#endif // INCarSeat_h
// ==========  Intents.framework/Headers/INSetDefrosterSettingsInCarIntentResponse.h
//
//  INSetDefrosterSettingsInCarIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSetDefrosterSettingsInCarIntentResponseCode) {
    INSetDefrosterSettingsInCarIntentResponseCodeUnspecified = 0,
    INSetDefrosterSettingsInCarIntentResponseCodeReady,
    INSetDefrosterSettingsInCarIntentResponseCodeInProgress,
    INSetDefrosterSettingsInCarIntentResponseCodeSuccess,
    INSetDefrosterSettingsInCarIntentResponseCodeFailure,
    INSetDefrosterSettingsInCarIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos, macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INSetDefrosterSettingsInCarIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSetDefrosterSettingsInCarIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSetDefrosterSettingsInCarIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INStartAudioCallIntent.h
//
//  INStartAudioCallIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCallDestinationType.h>

@class INCallDestinationTypeResolutionResult;
@class INPerson;
@class INPersonResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12))
@interface INStartAudioCallIntent : INIntent

- (instancetype)initWithDestinationType:(INCallDestinationType)destinationType
                               contacts:(nullable NSArray<INPerson *> *)contacts NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallDestinationType destinationType API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

// Recipients of the audio call.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *contacts;

@end

@class INStartAudioCallIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INStartAudioCallIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12))
@protocol INStartAudioCallIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INStartAudioCallIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INStartAudioCallIntentResponse containing the details of the result of having executed the intent

 @see  INStartAudioCallIntentResponse
 */

- (void)handleStartAudioCall:(INStartAudioCallIntent *)intent
                  completion:(void (^)(INStartAudioCallIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INStartAudioCallIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INStartAudioCallIntentResponse
 */

- (void)confirmStartAudioCall:(INStartAudioCallIntent *)intent
                   completion:(void (^)(INStartAudioCallIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveDestinationTypeForStartAudioCall:(INStartAudioCallIntent *)intent
                    withCompletion:(void (^)(INCallDestinationTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDestinationType(for:with:)) API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

- (void)resolveContactsForStartAudioCall:(INStartAudioCallIntent *)intent
                    withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveContacts(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetClimateSettingsInCarIntentResponse.h
//
//  INSetClimateSettingsInCarIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSetClimateSettingsInCarIntentResponseCode) {
    INSetClimateSettingsInCarIntentResponseCodeUnspecified = 0,
    INSetClimateSettingsInCarIntentResponseCodeReady,
    INSetClimateSettingsInCarIntentResponseCodeInProgress,
    INSetClimateSettingsInCarIntentResponseCodeSuccess,
    INSetClimateSettingsInCarIntentResponseCodeFailure,
    INSetClimateSettingsInCarIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos, macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INSetClimateSettingsInCarIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSetClimateSettingsInCarIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSetClimateSettingsInCarIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INAccountType.h
//
//  INAccountType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INAccountType_h
#define INAccountType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INAccountType) {
    INAccountTypeUnknown = 0,
    INAccountTypeChecking,
    INAccountTypeCredit,
    INAccountTypeDebit,
    INAccountTypeInvestment,
    INAccountTypeMortgage,
    INAccountTypePrepaid,
    INAccountTypeSaving,
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macosx);

#endif // INAccountType_h
// ==========  Intents.framework/Headers/INSetAudioSourceInCarIntentResponse.h
//
//  INSetAudioSourceInCarIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSetAudioSourceInCarIntentResponseCode) {
    INSetAudioSourceInCarIntentResponseCodeUnspecified = 0,
    INSetAudioSourceInCarIntentResponseCodeReady,
    INSetAudioSourceInCarIntentResponseCodeInProgress,
    INSetAudioSourceInCarIntentResponseCodeSuccess,
    INSetAudioSourceInCarIntentResponseCodeFailure,
    INSetAudioSourceInCarIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos, macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INSetAudioSourceInCarIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSetAudioSourceInCarIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSetAudioSourceInCarIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INGetUserCurrentRestaurantReservationBookingsIntentResponse.h
//
//  INGetUserCurrentRestaurantReservationBookingsIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntentResponse.h>
#import <Intents/INRestaurantReservationUserBooking.h>

typedef NS_ENUM(NSInteger, INGetUserCurrentRestaurantReservationBookingsIntentResponseCode) {
    INGetUserCurrentRestaurantReservationBookingsIntentResponseCodeSuccess,
    INGetUserCurrentRestaurantReservationBookingsIntentResponseCodeFailure,
    INGetUserCurrentRestaurantReservationBookingsIntentResponseCodeFailureRequestUnsatisfiable,
    INGetUserCurrentRestaurantReservationBookingsIntentResponseCodeUnspecified
};

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INGetUserCurrentRestaurantReservationBookingsIntentResponse : INIntentResponse

- (instancetype)initWithUserCurrentBookings:(NSArray<INRestaurantReservationUserBooking *> *)userCurrentBookings code:(INGetUserCurrentRestaurantReservationBookingsIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INGetUserCurrentRestaurantReservationBookingsIntentResponseCode code;

@property (copy, NS_NONATOMIC_IOSONLY) NSArray<INRestaurantReservationUserBooking *> *userCurrentBookings;

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPaymentMethod.h
//
//  INPaymentMethod.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INPaymentMethodType.h>

@class INImage;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INPaymentMethod : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithType:(INPaymentMethodType)type
                        name:(nullable NSString *)name
          identificationHint:(nullable NSString *)identificationHint
                        icon:(nullable INImage *)icon NS_DESIGNATED_INITIALIZER;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INPaymentMethodType type;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *name;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INImage *icon;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identificationHint;

// This payment method represents Apple Pay. Its .type will be INPaymentMethodTypeApplePay. The .name, .identificationHint and .icon properties are not significant for this type of payment method.
+ (instancetype)applePayPaymentMethod;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetRadioStationIntentResponse.h
//
//  INSetRadioStationIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSetRadioStationIntentResponseCode) {
    INSetRadioStationIntentResponseCodeUnspecified = 0,
    INSetRadioStationIntentResponseCodeReady,
    INSetRadioStationIntentResponseCodeInProgress,
    INSetRadioStationIntentResponseCodeSuccess,
    INSetRadioStationIntentResponseCodeFailure,
    INSetRadioStationIntentResponseCodeFailureRequiringAppLaunch,
    INSetRadioStationIntentResponseCodeFailureNotSubscribed,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos, macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INSetRadioStationIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSetRadioStationIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSetRadioStationIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPaymentRecord.h
//
//  INPaymentRecord.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INPaymentStatus.h>

@class INCurrencyAmount;
@class INPaymentMethod;
@class INPerson;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INPaymentRecord : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithPayee:(nullable INPerson *)payee
                                 payer:(nullable INPerson *)payer
                        currencyAmount:(nullable INCurrencyAmount *)currencyAmount
                         paymentMethod:(nullable INPaymentMethod *)paymentMethod
                                  note:(nullable NSString *)note
                                status:(INPaymentStatus)status
                             feeAmount:(nullable INCurrencyAmount *)feeAmount NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithPayee:(nullable INPerson *)payee
                                 payer:(nullable INPerson *)payer
                        currencyAmount:(nullable INCurrencyAmount *)currencyAmount
                         paymentMethod:(nullable INPaymentMethod *)paymentMethod
                                  note:(nullable NSString *)note
                                status:(INPaymentStatus)status;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *payee;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *payer;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *currencyAmount;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *note;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INPaymentStatus status;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentMethod *paymentMethod;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *feeAmount;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INTaskList.h
//
//  INTaskList.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INSpeakableString;
@class INTask;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INTaskList : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithTitle:(INSpeakableString *)title
                        tasks:(NSArray<INTask *> *)tasks
                    groupName:(nullable INSpeakableString *)groupName
        createdDateComponents:(nullable NSDateComponents *)createdDateComponents
       modifiedDateComponents:(nullable NSDateComponents *)modifiedDateComponents
                   identifier:(nullable NSString *)identifier NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INSpeakableString *title;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<INTask *> *tasks;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *groupName;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *createdDateComponents;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *modifiedDateComponents;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INStartAudioCallIntentResponse.h
//
//  INStartAudioCallIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INStartAudioCallIntentResponseCode) {
    INStartAudioCallIntentResponseCodeUnspecified = 0,
    INStartAudioCallIntentResponseCodeReady,
    INStartAudioCallIntentResponseCodeContinueInApp,
    INStartAudioCallIntentResponseCodeFailure,
    INStartAudioCallIntentResponseCodeFailureRequiringAppLaunch,
    INStartAudioCallIntentResponseCodeFailureAppConfigurationRequired,
    INStartAudioCallIntentResponseCodeFailureCallingServiceNotAvailable,
    INStartAudioCallIntentResponseCodeFailureContactNotSupportedByApp,
    INStartAudioCallIntentResponseCodeFailureNoValidNumber API_AVAILABLE(ios(11.0), macosx(10.13)),
} API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12));

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12))
@interface INStartAudioCallIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INStartAudioCallIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INStartAudioCallIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRideDriver.h
//
//  INRideDriver.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INPerson.h>

@class INImage;
@class INPersonHandle;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INRideDriver : INPerson <NSCopying, NSSecureCoding>

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *rating;
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *phoneNumber;

- (instancetype)initWithPhoneNumber:(NSString *)phoneNumber
                     nameComponents:(nullable NSPersonNameComponents *)nameComponents
                        displayName:(nullable NSString *)displayName
                              image:(nullable INImage *)image
                             rating:(nullable NSString *)rating NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);

@end
 
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRequestPaymentPayerResolutionResult.h
//
//  INRequestPaymentPayerResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INPersonResolutionResult.h>

typedef NS_ENUM(NSInteger, INRequestPaymentPayerUnsupportedReason) {
    INRequestPaymentPayerUnsupportedReasonCredentialsUnverified = 1,
    INRequestPaymentPayerUnsupportedReasonNoAccount,
    INRequestPaymentPayerUnsupportedReasonNoValidHandle API_AVAILABLE(ios(11.1), watchos(4.1)),
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INRequestPaymentPayerResolutionResult : INPersonResolutionResult

+ (instancetype)unsupportedForReason:(INRequestPaymentPayerUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithPersonResolutionResult:(INPersonResolutionResult *)personResolutionResult;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INAmountType.h
//
//  INAmountType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INAmountType_h
#define INAmountType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INAmountType) {
    INAmountTypeUnknown = 0,
    INAmountTypeMinimumDue,
    INAmountTypeAmountDue,
    INAmountTypeCurrentBalance,
    INAmountTypeMaximumTransferAmount API_AVAILABLE(ios(11.0), watchos(4.0)),
    INAmountTypeMinimumTransferAmount API_AVAILABLE(ios(11.0), watchos(4.0)),
    INAmountTypeStatementBalance API_AVAILABLE(ios(11.0), watchos(4.0)),
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macosx);

#endif // INAmountType_h
// ==========  Intents.framework/Headers/INEndWorkoutIntent.h
//
//  INEndWorkoutIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INEndWorkoutIntent : INIntent

// Designated initializer. The `workoutName` can use `INWorkoutNameIdentifier` as its `identifier` parameter.
- (instancetype)initWithWorkoutName:(nullable INSpeakableString *)workoutName NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *workoutName;

@end

@class INEndWorkoutIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INEndWorkoutIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INEndWorkoutIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INEndWorkoutIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INEndWorkoutIntentResponse containing the details of the result of having executed the intent

 @see  INEndWorkoutIntentResponse
 */

- (void)handleEndWorkout:(INEndWorkoutIntent *)intent
              completion:(void (^)(INEndWorkoutIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INEndWorkoutIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INEndWorkoutIntentResponse
 */

- (void)confirmEndWorkout:(INEndWorkoutIntent *)intent
               completion:(void (^)(INEndWorkoutIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveWorkoutNameForEndWorkout:(INEndWorkoutIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutName(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCarSeatResolutionResult.h
//
//  INCarSeatResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarSeat.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INCarSeatResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INCarSeat. The resolvedValue can be different than the original INCarSeat. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedCarSeat:(INCarSeat)resolvedCarSeat NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INCarSeat)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedCarSeat:", ios(10.0, 11.0));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithCarSeatToConfirm:(INCarSeat)carSeatToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INCarSeat)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithCarSeatToConfirm:", ios(10.0, 11.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSearchCallHistoryIntent_Deprecated.h
//
//  INSearchCallHistoryIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INCallRecordType.h>
#import <Intents/INSearchCallHistoryIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSearchCallHistoryIntent (Deprecated)

- (instancetype)initWithCallType:(INCallRecordType)callType
                     dateCreated:(nullable INDateComponentsRange *)dateCreated
                       recipient:(nullable INPerson *)recipient
                callCapabilities:(INCallCapabilityOptions)callCapabilities API_DEPRECATED("Use the designated initializer instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

// What type of call record to search for.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallRecordType callType API_DEPRECATED("Use callTypes instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INMessage.h
//
//  INMessage.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INPerson;
@class INSpeakableString;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, INMessageType) {
    INMessageTypeUnspecified = 0,
    INMessageTypeText,
    INMessageTypeAudio,
    INMessageTypeDigitalTouch,
    INMessageTypeHandwriting,
    INMessageTypeSticker,
    INMessageTypeTapbackLiked,
    INMessageTypeTapbackDisliked,
    INMessageTypeTapbackEmphasized,
    INMessageTypeTapbackLoved,
    INMessageTypeTapbackQuestioned,
    INMessageTypeTapbackLaughed,
    INMessageTypeMediaCalendar,
    INMessageTypeMediaLocation,
    INMessageTypeMediaAddressCard,
    INMessageTypeMediaImage,
    INMessageTypeMediaVideo,
    INMessageTypeMediaPass,
    INMessageTypeMediaAudio,
    INMessageTypePaymentSent API_AVAILABLE(macosx(10.14), ios(12.0), watchos(5.0)),
    INMessageTypePaymentRequest API_AVAILABLE(macosx(10.14), ios(12.0), watchos(5.0)),
    INMessageTypePaymentNote API_AVAILABLE(macosx(10.14), ios(12.0), watchos(5.0)),
    INMessageTypeAnimoji API_AVAILABLE(macosx(10.14), ios(12.0), watchos(5.0)),
    INMessageTypeActivitySnippet API_AVAILABLE(macosx(10.14), ios(12.0), watchos(5.0)),
    INMessageTypeFile API_AVAILABLE(macosx(10.14), ios(12.0), watchos(5.0)),
    INMessageTypeLink API_AVAILABLE(macosx(10.14), ios(12.0), watchos(5.0)),
} API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0));

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INMessage : NSObject <NSCopying, NSSecureCoding>

- (id)init NS_UNAVAILABLE;

- (instancetype)initWithIdentifier:(NSString *)identifier
            conversationIdentifier:(nullable NSString *)conversationIdentifier
                           content:(nullable NSString *)content
                          dateSent:(nullable NSDate *)dateSent
                            sender:(nullable INPerson *)sender
                        recipients:(nullable NSArray<INPerson *> *)recipients
                         groupName:(nullable INSpeakableString *)groupName
                       messageType:(INMessageType)messageType NS_DESIGNATED_INITIALIZER API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0));

- (instancetype)initWithIdentifier:(NSString *)identifier
            conversationIdentifier:(nullable NSString *)conversationIdentifier
                           content:(nullable NSString *)content
                          dateSent:(nullable NSDate *)dateSent
                            sender:(nullable INPerson *)sender
                        recipients:(nullable NSArray<INPerson *> *)recipients
                       messageType:(INMessageType)messageType API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0));

- (instancetype)initWithIdentifier:(NSString *)identifier
                           content:(nullable NSString *)content
                          dateSent:(nullable NSDate *)dateSent
                            sender:(nullable INPerson *)sender
                        recipients:(nullable NSArray<INPerson *> *)recipients;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *conversationIdentifier API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *content;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *dateSent;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *sender;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *recipients;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *groupName API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0));

@property (readonly, NS_NONATOMIC_IOSONLY) INMessageType messageType API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INGetVisualCodeIntentResponse.h
//
//  INGetVisualCodeIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INImage;

typedef NS_ENUM(NSInteger, INGetVisualCodeIntentResponseCode) {
    INGetVisualCodeIntentResponseCodeUnspecified = 0,
    INGetVisualCodeIntentResponseCodeReady,
    INGetVisualCodeIntentResponseCodeContinueInApp,
    INGetVisualCodeIntentResponseCodeInProgress,
    INGetVisualCodeIntentResponseCodeSuccess,
    INGetVisualCodeIntentResponseCodeFailure,
    INGetVisualCodeIntentResponseCodeFailureRequiringAppLaunch,
    INGetVisualCodeIntentResponseCodeFailureAppConfigurationRequired,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INGetVisualCodeIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INGetVisualCodeIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INGetVisualCodeIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INImage *visualCodeImage;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INShortcut.h
//
//  INShortcut.h
//  Intents
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Intents/INIntent.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract A shortcut is an action that can be suggested by the system or added to Siri.
 */
API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macosx)
@interface INShortcut : NSObject <NSSecureCoding, NSCopying>

/*!
 @abstract The intent that will be performed when this shortcut is invoked.
 @discussion Is @c nil if the shortcut was created with a @c NSUserActivity.
 */
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INIntent *intent;

/*!
 @abstract The user activity that will be performed when this shortcut is invoked.
 @discussion Is @c nil if the shortcut was created with an @c INIntent.
 */
@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) NSUserActivity *userActivity;

/*!
 @note Must be initilaized with either an intent or user activity, using those initializers.
 */
+ (instancetype)new NS_UNAVAILABLE;

/*!
 @note Must be initilaized with either an intent or user activity, using those initializers.
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Creates a shortcut with the given intent.
 @param intent Must have a title and have valid shortcut types.
 @return Will return @c nil (and log an error) if the intent isn't valid.
 */
- (nullable instancetype)initWithIntent:(INIntent *)intent;

/*!
 @abstract Creates a shortcut with the given user activity.
 */
- (instancetype)initWithUserActivity:(NSUserActivity *)userActivity;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRequestPaymentCurrencyAmountResolutionResult.h
//
//  INRequestPaymentCurrencyAmountResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INCurrencyAmountResolutionResult.h>

typedef NS_ENUM(NSInteger, INRequestPaymentCurrencyAmountUnsupportedReason) {
    INRequestPaymentCurrencyAmountUnsupportedReasonPaymentsAmountBelowMinimum = 1,
    INRequestPaymentCurrencyAmountUnsupportedReasonPaymentsAmountAboveMaximum,
    INRequestPaymentCurrencyAmountUnsupportedReasonPaymentsCurrencyUnsupported,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INRequestPaymentCurrencyAmountResolutionResult : INCurrencyAmountResolutionResult

+ (instancetype)unsupportedForReason:(INRequestPaymentCurrencyAmountUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithCurrencyAmountResolutionResult:(INCurrencyAmountResolutionResult *)currencyAmountResolutionResult;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INWorkoutNameIdentifier.h
//
//  INWorkoutNameIdentifier.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NSString *INWorkoutNameIdentifier NS_TYPED_ENUM;

INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierRun NS_SWIFT_NAME(INWorkoutNameIdentifier.run) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierSit NS_SWIFT_NAME(INWorkoutNameIdentifier.sit) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierSteps NS_SWIFT_NAME(INWorkoutNameIdentifier.steps) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierStand NS_SWIFT_NAME(INWorkoutNameIdentifier.stand) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierMove NS_SWIFT_NAME(INWorkoutNameIdentifier.move) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierWalk NS_SWIFT_NAME(INWorkoutNameIdentifier.walk) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierYoga NS_SWIFT_NAME(INWorkoutNameIdentifier.yoga) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierDance NS_SWIFT_NAME(INWorkoutNameIdentifier.dance) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierCrosstraining NS_SWIFT_NAME(INWorkoutNameIdentifier.crosstraining) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierElliptical NS_SWIFT_NAME(INWorkoutNameIdentifier.elliptical) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierRower NS_SWIFT_NAME(INWorkoutNameIdentifier.rower) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierCycle NS_SWIFT_NAME(INWorkoutNameIdentifier.cycle) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierStairs NS_SWIFT_NAME(INWorkoutNameIdentifier.stairs) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierOther NS_SWIFT_NAME(INWorkoutNameIdentifier.other) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierIndoorrun NS_SWIFT_NAME(INWorkoutNameIdentifier.indoorrun) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierIndoorcycle NS_SWIFT_NAME(INWorkoutNameIdentifier.indoorcycle) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierIndoorwalk NS_SWIFT_NAME(INWorkoutNameIdentifier.indoorwalk) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierExercise NS_SWIFT_NAME(INWorkoutNameIdentifier.exercise) API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierHike NS_SWIFT_NAME(INWorkoutNameIdentifier.hike) API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierHighIntensityIntervalTraining NS_SWIFT_NAME(INWorkoutNameIdentifier.highIntensityIntervalTraining) API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx);
INTENTS_EXTERN INWorkoutNameIdentifier const INWorkoutNameIdentifierSwim NS_SWIFT_NAME(INWorkoutNameIdentifier.swim) API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx);
// ==========  Intents.framework/Headers/INAppendToNoteIntentResponse.h
//
//  INAppendToNoteIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INNote;

typedef NS_ENUM(NSInteger, INAppendToNoteIntentResponseCode) {
    INAppendToNoteIntentResponseCodeUnspecified = 0,
    INAppendToNoteIntentResponseCodeReady,
    INAppendToNoteIntentResponseCodeInProgress,
    INAppendToNoteIntentResponseCodeSuccess,
    INAppendToNoteIntentResponseCodeFailure,
    INAppendToNoteIntentResponseCodeFailureRequiringAppLaunch,
    INAppendToNoteIntentResponseCodeFailureCannotUpdatePasswordProtectedNote,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INAppendToNoteIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INAppendToNoteIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INAppendToNoteIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INNote *note;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INConditionalOperator.h
//
//  INConditionalOperator.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INConditionalOperator_h
#define INConditionalOperator_h

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, INConditionalOperator) {
    INConditionalOperatorAll = 0,
    INConditionalOperatorAny,
    INConditionalOperatorNone,
} API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));

#endif // INConditionalOperator_h
// ==========  Intents.framework/Headers/INSetRadioStationIntent.h
//
//  INSetRadioStationIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INRadioType.h>

@class INDoubleResolutionResult;
@class INIntegerResolutionResult;
@class INRadioTypeResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INSetRadioStationIntent : INIntent

- (instancetype)initWithRadioType:(INRadioType)radioType
                        frequency:(nullable NSNumber *)frequency
                      stationName:(nullable NSString *)stationName
                          channel:(nullable NSString *)channel
                     presetNumber:(nullable NSNumber *)presetNumber NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INRadioType radioType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *frequency NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *stationName;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *channel;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *presetNumber NS_REFINED_FOR_SWIFT;

@end

@class INSetRadioStationIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSetRadioStationIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@protocol INSetRadioStationIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSetRadioStationIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSetRadioStationIntentResponse containing the details of the result of having executed the intent

 @see  INSetRadioStationIntentResponse
 */

- (void)handleSetRadioStation:(INSetRadioStationIntent *)intent
                   completion:(void (^)(INSetRadioStationIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSetRadioStationIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetRadioStationIntentResponse
 */

- (void)confirmSetRadioStation:(INSetRadioStationIntent *)intent
                    completion:(void (^)(INSetRadioStationIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveRadioTypeForSetRadioStation:(INSetRadioStationIntent *)intent
                    withCompletion:(void (^)(INRadioTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRadioType(for:with:));

- (void)resolveFrequencyForSetRadioStation:(INSetRadioStationIntent *)intent
                    withCompletion:(void (^)(INDoubleResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveFrequency(for:with:));

- (void)resolveStationNameForSetRadioStation:(INSetRadioStationIntent *)intent
                    withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveStationName(for:with:));

- (void)resolveChannelForSetRadioStation:(INSetRadioStationIntent *)intent
                    withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveChannel(for:with:));

- (void)resolvePresetNumberForSetRadioStation:(INSetRadioStationIntent *)intent
                    withCompletion:(void (^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePresetNumber(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INDefaultCardTemplate.h
//
//  INDefaultCardTemplate.h
//  Intents
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Intents/INImage.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx)
@interface INDefaultCardTemplate : NSObject <NSCopying, NSSecureCoding>

@property (copy, NS_NONATOMIC_IOSONLY) NSString *title;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *subtitle;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INImage *image;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithTitle:(NSString *)title NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSpeakableStringResolutionResult.h
//
//  INSpeakableStringResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INSpeakableString;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INSpeakableStringResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INSpeakableString. The resolvedString can be different than the original INSpeakableString. This allows app extensions to add a pronunciationHint, or otherwise tweak the string.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedString:(INSpeakableString *)resolvedString NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided strings.
+ (instancetype)disambiguationWithStringsToDisambiguate:(NSArray<INSpeakableString *> *)stringsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the string with which the user wants to continue.
+ (instancetype)confirmationRequiredWithStringToConfirm:(nullable INSpeakableString *)stringToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INStartAudioCallIntent_Deprecated.h
//
//  INStartAudioCallIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INStartAudioCallIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INStartAudioCallIntent (Deprecated)

- (instancetype)initWithContacts:(nullable NSArray<INPerson *> *)contacts API_DEPRECATED("Use the designated initializer instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCallCapability.h
//
//  INCallCapability.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INCallCapability_h
#define INCallCapability_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCallCapability) {
    INCallCapabilityUnknown = 0,
    INCallCapabilityAudioCall,
    INCallCapabilityVideoCall,
} API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12));

#endif // INCallCapability_h
// ==========  Intents.framework/Headers/INGetCarPowerLevelStatusIntent.h
//
//  INGetCarPowerLevelStatusIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INGetCarPowerLevelStatusIntent : INIntent

- (instancetype)initWithCarName:(nullable INSpeakableString *)carName NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *carName;

@end

@class INGetCarPowerLevelStatusIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INGetCarPowerLevelStatusIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INGetCarPowerLevelStatusIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INGetCarPowerLevelStatusIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INGetCarPowerLevelStatusIntentResponse containing the details of the result of having executed the intent

 @see  INGetCarPowerLevelStatusIntentResponse
 */

- (void)handleGetCarPowerLevelStatus:(INGetCarPowerLevelStatusIntent *)intent
                          completion:(void (^)(INGetCarPowerLevelStatusIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INGetCarPowerLevelStatusIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INGetCarPowerLevelStatusIntentResponse
 */

- (void)confirmGetCarPowerLevelStatus:(INGetCarPowerLevelStatusIntent *)intent
                           completion:(void (^)(INGetCarPowerLevelStatusIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveCarNameForGetCarPowerLevelStatus:(INGetCarPowerLevelStatusIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCarName(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INResumeWorkoutIntent.h
//
//  INResumeWorkoutIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INResumeWorkoutIntent : INIntent

// Designated initializer. The `workoutName` can use `INWorkoutNameIdentifier` as its `identifier` parameter.
- (instancetype)initWithWorkoutName:(nullable INSpeakableString *)workoutName NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *workoutName;

@end

@class INResumeWorkoutIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INResumeWorkoutIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INResumeWorkoutIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INResumeWorkoutIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INResumeWorkoutIntentResponse containing the details of the result of having executed the intent

 @see  INResumeWorkoutIntentResponse
 */

- (void)handleResumeWorkout:(INResumeWorkoutIntent *)intent
                 completion:(void (^)(INResumeWorkoutIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INResumeWorkoutIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INResumeWorkoutIntentResponse
 */

- (void)confirmResumeWorkout:(INResumeWorkoutIntent *)intent
                  completion:(void (^)(INResumeWorkoutIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveWorkoutNameForResumeWorkout:(INResumeWorkoutIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutName(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INVoiceShortcut.h
//
//  INVoiceShortcut.h
//  Intents
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INShortcut;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract A shortcut that has been added to Siri
 */
API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macosx)
@interface INVoiceShortcut : NSObject <NSSecureCoding, NSCopying>

/*!
 @abstract The unique identifier for this voice shortcut
 */
@property (readonly, strong, NS_NONATOMIC_IOSONLY) NSUUID *identifier;

/*!
 @abstract The phrase the user speaks to invoke this shortcut; set by the user when they add it to Siri.
 */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *invocationPhrase;

/*!
 @abstract The shortcut that will be performed when this voice shortcut is invoked via Siri.
 */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) INShortcut *shortcut;

/*!
 An @c INVoiceShortcut cannot be created directly. Instead, create an @c INShortcut, and add it using @c INUIAddVoiceShortcutViewController.
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 An @c INVoiceShortcut cannot be created directly. Instead, create an @c INShortcut, and add it using @c INUIAddVoiceShortcutViewController.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INVocabulary.h
//
//  INVocabulary.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol INSpeakable;

typedef NS_ENUM(NSInteger, INVocabularyStringType) {
    /// The name of a contact as a person will say it, for example “Jon Smith”, “Apple”.
    INVocabularyStringTypeContactName = 1,

    /// The name of a group of contacts as a person will say it, for example "Tahoe Trip".
    INVocabularyStringTypeContactGroupName,

    /// A keyword associated with an image or images, for example "food", "Vacation".
    INVocabularyStringTypePhotoTag = 100,

    /// The name for a photograph album, for example "WWDC 2015 Karaoke".
    /// You may find that INVocabularyStringTypePhotoTag is a better match for concepts that are similar to, but not exactly, albums.
    INVocabularyStringTypePhotoAlbumName,

    /// The name a user has created for a workout, for example  “Half Marathon”, “Kettlebell exercise”
    INVocabularyStringTypeWorkoutActivityName = 200,

    /// The name of a vehicle configuration profile, for example "Roadtrip", "Rally", "Good Weather".
    /// For use by automaker apps that are enabled to work with CarPlay <https://developer.apple.com/carplay/>.
    INVocabularyStringTypeCarProfileName = 300,
    
    /// The name of a vehicle as a person will say it, for example “BMW”, “My Convertible”.
    INVocabularyStringTypeCarName API_AVAILABLE(ios(10.3)),
    
    /// The name of an organization to pay as a person will say it, for example “PG&E”, “Comcast”.
    INVocabularyStringTypePaymentsOrganizationName API_AVAILABLE(ios(10.3)) = 400,
    
    /// The name of an account nick name as a person will say it, for example “Checking”, “Rainy day savings”.
    INVocabularyStringTypePaymentsAccountNickname API_AVAILABLE(ios(10.3)),
    
    /// The title of a note, task, or task list as a person will say it; for example, "Grocery list" or "Weekly meeting minutes".
    INVocabularyStringTypeNotebookItemTitle API_AVAILABLE(ios(11.0)) = 500,
    
    /// The name of the note or task list's group (folder, directory, account); for example, "iCloud" or "Shopping"
    INVocabularyStringTypeNotebookItemGroupName API_AVAILABLE(ios(11.0)),
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos, tvos, macosx);

API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos, tvos, macosx)
@interface INVocabulary : NSObject

+ (instancetype)sharedVocabulary;

/// Replaces all vocabulary strings already set for the given type.
/// Strings should be sorted by their expected importance to the user, in descending order.
/// There is no guarantee that every provided string will be used, but preference is given to strings at the beginning of the set.
/// Any strings larger than 1024 bytes when encoded as UTF-16 (roughly 500 characters) will be discarded.
- (void)setVocabularyStrings:(NSOrderedSet<NSString *> *)vocabulary ofType:(INVocabularyStringType)type NS_EXTENSION_UNAVAILABLE("INVocabulary is not available to extensions. The main app is responsible for providing all vocabulary.");

- (void)setVocabulary:(NSOrderedSet<id<INSpeakable>> *)vocabulary ofType:(INVocabularyStringType)type API_AVAILABLE(ios(11.0)) NS_EXTENSION_UNAVAILABLE("INVocabulary is not available to extensions. The main app is responsible for providing all vocabulary.");

/// Removes all vocabulary strings for every INVocabularyStringType the calling app has previously registered.
- (void)removeAllVocabularyStrings NS_EXTENSION_UNAVAILABLE("INVocabulary is not available to extensions. The main app is responsible for providing all vocabulary.");

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRelevantShortcutStore.h
//
//  INRelevantShortcutStore.h
//  Intents
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INRelevantShortcut;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macosx)
@interface INRelevantShortcutStore : NSObject

@property (class, readonly, strong) INRelevantShortcutStore *defaultStore;

- (void)setRelevantShortcuts:(NSArray<INRelevantShortcut *> *)shortcuts completionHandler:(void (^ __nullable)(NSError * __nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INAccountTypeResolutionResult.h
//
//  INAccountTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INAccountType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INAccountTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INAccountType. The resolvedValue can be different than the original INAccountType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedAccountType:(INAccountType)resolvedAccountType NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INAccountType)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedAccountType:", ios(10.3, 11.0), watchos(3.2, 4.0));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithAccountTypeToConfirm:(INAccountType)accountTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INAccountType)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithAccountTypeToConfirm:", ios(10.3, 11.0), watchos(3.2, 4.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INListRideOptionsIntent.h
//
//  INListRideOptionsIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class CLPlacemark;
@class INPlacemarkResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INListRideOptionsIntent : INIntent

- (instancetype)initWithPickupLocation:(nullable CLPlacemark *)pickupLocation
                       dropOffLocation:(nullable CLPlacemark *)dropOffLocation NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *pickupLocation;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *dropOffLocation;

@end

@class INListRideOptionsIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INListRideOptionsIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INListRideOptionsIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INListRideOptionsIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INListRideOptionsIntentResponse containing the details of the result of having executed the intent

 @see  INListRideOptionsIntentResponse
 */

- (void)handleListRideOptions:(INListRideOptionsIntent *)intent
                   completion:(void (^)(INListRideOptionsIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INListRideOptionsIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INListRideOptionsIntentResponse
 */

- (void)confirmListRideOptions:(INListRideOptionsIntent *)intent
                    completion:(void (^)(INListRideOptionsIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolvePickupLocationForListRideOptions:(INListRideOptionsIntent *)intent
                    withCompletion:(void (^)(INPlacemarkResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePickupLocation(for:with:));

- (void)resolveDropOffLocationForListRideOptions:(INListRideOptionsIntent *)intent
                    withCompletion:(void (^)(INPlacemarkResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDropOffLocation(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INBillDetails.h
//
//  INBillDetails.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INBillType.h>
#import <Intents/INPaymentStatus.h>

@class INBillPayee;
@class INCurrencyAmount;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INBillDetails : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithBillType:(INBillType)billType
                            paymentStatus:(INPaymentStatus)paymentStatus
                                billPayee:(nullable INBillPayee *)billPayee
                                amountDue:(nullable INCurrencyAmount *)amountDue
                               minimumDue:(nullable INCurrencyAmount *)minimumDue
                                  lateFee:(nullable INCurrencyAmount *)lateFee
                                  dueDate:(nullable NSDateComponents *)dueDate
                              paymentDate:(nullable NSDateComponents *)paymentDate NS_DESIGNATED_INITIALIZER;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INBillPayee *billPayee;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *amountDue;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *minimumDue;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *lateFee;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *dueDate;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *paymentDate;

@property (readwrite, assign, NS_NONATOMIC_IOSONLY) INBillType billType;

@property (readwrite, assign, NS_NONATOMIC_IOSONLY) INPaymentStatus paymentStatus;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INTemperatureResolutionResult.h
//
//  INTemperatureResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INTemperature;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx)
@interface INTemperatureResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given temperature. The resolvedTemperature can be different than the original temperature. This allows app extensions to apply business logic constraints to the temperature. For example, constraining it to a maximum or minimum value.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedTemperature:(NSMeasurement<NSUnitTemperature *> *)resolvedTemperature NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided temperatures.
+ (instancetype)disambiguationWithTemperaturesToDisambiguate:(NSArray<NSMeasurement<NSUnitTemperature *> *> *)temperaturesToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the temperature with which the user wants to continue.
+ (instancetype)confirmationRequiredWithTemperatureToConfirm:(nullable NSMeasurement<NSUnitTemperature *> *)temperatureToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSaveProfileInCarIntent.h
//
//  INSaveProfileInCarIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INIntegerResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INSaveProfileInCarIntent : INIntent

- (instancetype)initWithProfileNumber:(nullable NSNumber *)profileNumber
                          profileName:(nullable NSString *)profileName NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(10.2));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *profileNumber NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *profileName API_AVAILABLE(ios(10.2));

@end

@class INSaveProfileInCarIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSaveProfileInCarIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@protocol INSaveProfileInCarIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSaveProfileInCarIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSaveProfileInCarIntentResponse containing the details of the result of having executed the intent

 @see  INSaveProfileInCarIntentResponse
 */

- (void)handleSaveProfileInCar:(INSaveProfileInCarIntent *)intent
                    completion:(void (^)(INSaveProfileInCarIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSaveProfileInCarIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSaveProfileInCarIntentResponse
 */

- (void)confirmSaveProfileInCar:(INSaveProfileInCarIntent *)intent
                     completion:(void (^)(INSaveProfileInCarIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveProfileNumberForSaveProfileInCar:(INSaveProfileInCarIntent *)intent
                    withCompletion:(void (^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveProfileNumber(for:with:));

- (void)resolveProfileNameForSaveProfileInCar:(INSaveProfileInCarIntent *)intent
                    withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveProfileName(for:with:)) API_AVAILABLE(ios(10.2));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INBookRestaurantReservationIntent.h
//
//  INBookRestaurantReservationIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>
#import <Intents/INRestaurant.h>
#import <Intents/INRestaurantOffer.h>
#import <Intents/INRestaurantGuest.h>
#import <Intents/INRestaurantResolutionResult.h>
#import <Intents/INIntegerResolutionResult.h>
#import <Intents/INRestaurantGuestResolutionResult.h>
#import <Intents/INStringResolutionResult.h>
#import <Intents/INDateComponentsResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INBookRestaurantReservationIntent : INIntent <NSCopying>

- (instancetype)initWithRestaurant:(INRestaurant *)restaurant
             bookingDateComponents:(NSDateComponents *)bookingDateComponents
                         partySize:(NSUInteger)partySize
                 bookingIdentifier:(nullable NSString *)bookingIdentifier
                             guest:(nullable INRestaurantGuest *)guest
                     selectedOffer:(nullable INRestaurantOffer *)selectedOffer
   guestProvidedSpecialRequestText:(nullable NSString *)guestProvidedSpecialRequestText API_AVAILABLE(ios(11.0));

@property (copy, NS_NONATOMIC_IOSONLY) INRestaurant *restaurant;
@property (copy, NS_NONATOMIC_IOSONLY) NSDateComponents *bookingDateComponents;
@property (NS_NONATOMIC_IOSONLY) NSUInteger partySize;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *bookingIdentifier; // unique identifier supplied by vendor to this booking
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurantGuest *guest; // model object containing contact information
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurantOffer *selectedOffer; // offer selected by user, if one exists
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *guestProvidedSpecialRequestText; // text captured in UI from user for special requests

@end

@class INBookRestaurantReservationIntentResponse;

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@protocol INBookRestaurantReservationIntentHandling <NSObject>

/*!
 @abstract Handling method - Execute the task represented by the INBookRestaurantReservationIntent that's passed in
 @discussion This method is called to actually execute the intent, the app must return a response for this intent and an NSUserActivity capturing the state that the app must be restored to at the end of handling this intent
 
 @param  intent The input intent
 @param  completion The response handling block to invoke with the response to handling the intent.
 
 @see  INBookRestaurantReservationIntentResponse
 
 */

- (void)handleBookRestaurantReservation:(INBookRestaurantReservationIntent *)intent completion:(void (^)(INBookRestaurantReservationIntentResponse *response))completion  NS_SWIFT_NAME(handle(bookRestaurantReservation:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.
 
 @param  intent The input intent
 @param  completion The response block contains an INBookRestaurantReservationIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.
 
 @see INEndWorkoutIntentResponse
 
 */

- (void)confirmBookRestaurantReservation:(INBookRestaurantReservationIntent *)intent completion:(void (^)(INBookRestaurantReservationIntentResponse *response))completion  NS_SWIFT_NAME(confirm(bookRestaurantReservation:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.
 
 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved
 
 @see INIntentResolutionResult
 
 */

- (void)resolveRestaurantForBookRestaurantReservation:(INBookRestaurantReservationIntent *)intent withCompletion:(void(^)(INRestaurantResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRestaurant(for:completion:));
- (void)resolveBookingDateComponentsForBookRestaurantReservation:(INBookRestaurantReservationIntent *)intent withCompletion:(void(^)(INDateComponentsResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveBookingDateComponents(for:completion:));
- (void)resolvePartySizeForBookRestaurantReservation:(INBookRestaurantReservationIntent *)intent withCompletion:(void(^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePartySize(for:completion:));
- (void)resolveGuestForBookRestaurantReservation:(INBookRestaurantReservationIntent *)intent withCompletion:(void(^)(INRestaurantGuestResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveGuest(for:completion:));
- (void)resolveGuestProvidedSpecialRequestTextForBookRestaurantReservation:(INBookRestaurantReservationIntent *)intent withCompletion:(void(^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveGuestProvidedSpecialRequestText(for:completion:));

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRestaurantGuestDisplayPreferences.h
//
//  INRestaurantGuestDisplayPreferences.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Foundation/Foundation.h>

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INRestaurantGuestDisplayPreferences : NSObject <NSSecureCoding, NSCopying>

@property (NS_NONATOMIC_IOSONLY) BOOL nameFieldFirstNameOptional; // indicates whether first name field is marked optional, defaults to NO
@property (NS_NONATOMIC_IOSONLY) BOOL nameFieldLastNameOptional; // indicates whether last name field is marked optional, defaults to NO

@property (NS_NONATOMIC_IOSONLY) BOOL nameFieldShouldBeDisplayed; // indicates whether name input field should be displayed, defaults to YES
@property (NS_NONATOMIC_IOSONLY) BOOL emailAddressFieldShouldBeDisplayed; // indicates whether email address input field should be displayed, defaults to YES
@property (NS_NONATOMIC_IOSONLY) BOOL phoneNumberFieldShouldBeDisplayed; // indicates whether phone number field should be displayed, defaults to YES

@property (NS_NONATOMIC_IOSONLY) BOOL nameEditable; // indicates whether the name field should be user editable, defaults to YES
@property (NS_NONATOMIC_IOSONLY) BOOL emailAddressEditable; // indicates whether the email address field should be user editable, defaults to YES
@property (NS_NONATOMIC_IOSONLY) BOOL phoneNumberEditable; // indicates whether the phone number field should be user editable, defaults to YES

@end
// ==========  Intents.framework/Headers/INDateSearchTypeResolutionResult.h
//
//  INDateSearchTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INDateSearchType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INDateSearchTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INDateSearchType. The resolvedValue can be different than the original INDateSearchType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedDateSearchType:(INDateSearchType)resolvedDateSearchType NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithDateSearchTypeToConfirm:(INDateSearchType)dateSearchTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INTransferMoneyIntent.h
//
//  INTransferMoneyIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INPaymentAccount;
@class INPaymentAccountResolutionResult;
@class INPaymentAmount;
@class INPaymentAmountResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INTransferMoneyIntent : INIntent

- (instancetype)initWithFromAccount:(nullable INPaymentAccount *)fromAccount
                          toAccount:(nullable INPaymentAccount *)toAccount
                  transactionAmount:(nullable INPaymentAmount *)transactionAmount
           transactionScheduledDate:(nullable INDateComponentsRange *)transactionScheduledDate
                    transactionNote:(nullable NSString *)transactionNote NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAccount *fromAccount;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAccount *toAccount;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAmount *transactionAmount;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *transactionScheduledDate;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *transactionNote;

@end

@class INTransferMoneyIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INTransferMoneyIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@protocol INTransferMoneyIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INTransferMoneyIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INTransferMoneyIntentResponse containing the details of the result of having executed the intent

 @see  INTransferMoneyIntentResponse
 */

- (void)handleTransferMoney:(INTransferMoneyIntent *)intent
                 completion:(void (^)(INTransferMoneyIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INTransferMoneyIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INTransferMoneyIntentResponse
 */

- (void)confirmTransferMoney:(INTransferMoneyIntent *)intent
                  completion:(void (^)(INTransferMoneyIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveFromAccountForTransferMoney:(INTransferMoneyIntent *)intent
                    withCompletion:(void (^)(INPaymentAccountResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveFromAccount(for:with:));

- (void)resolveToAccountForTransferMoney:(INTransferMoneyIntent *)intent
                    withCompletion:(void (^)(INPaymentAccountResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveToAccount(for:with:));

- (void)resolveTransactionAmountForTransferMoney:(INTransferMoneyIntent *)intent
                    withCompletion:(void (^)(INPaymentAmountResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTransactionAmount(for:with:));

- (void)resolveTransactionScheduledDateForTransferMoney:(INTransferMoneyIntent *)intent
                    withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTransactionScheduledDate(for:with:));

- (void)resolveTransactionNoteForTransferMoney:(INTransferMoneyIntent *)intent
                    withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTransactionNote(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INBalanceAmount.h
//
//  INBalanceAmount.h
//  Intents
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INBalanceType.h>


NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx)
@interface INBalanceAmount : NSObject <NSCopying, NSSecureCoding>

- (id)init NS_UNAVAILABLE;

- (nullable instancetype)initWithAmount:(NSDecimalNumber *)amount
                            balanceType:(INBalanceType)balanceType NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithAmount:(NSDecimalNumber *)amount
                           currencyCode:(NSString *)currencyCode NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDecimalNumber *amount;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INBalanceType balanceType;

// The ISO 4217 currency code that applies to the monetary amount.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *currencyCode;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INIntentResponses.h
//
//  INIntentResponses.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INSearchCallHistoryIntentResponse.h>
#import <Intents/INStartAudioCallIntentResponse.h>
#import <Intents/INStartVideoCallIntentResponse.h>

#import <Intents/INActivateCarSignalIntentResponse.h>
#import <Intents/INGetCarLockStatusIntentResponse.h>
#import <Intents/INGetCarPowerLevelStatusIntentResponse.h>
#import <Intents/INSaveProfileInCarIntentResponse.h>
#import <Intents/INSetAudioSourceInCarIntentResponse.h>
#import <Intents/INSetCarLockStatusIntentResponse.h>
#import <Intents/INSetClimateSettingsInCarIntentResponse.h>
#import <Intents/INSetDefrosterSettingsInCarIntentResponse.h>
#import <Intents/INSetProfileInCarIntentResponse.h>
#import <Intents/INSetSeatSettingsInCarIntentResponse.h>

#import <Intents/INCancelWorkoutIntentResponse.h>
#import <Intents/INEndWorkoutIntentResponse.h>
#import <Intents/INPauseWorkoutIntentResponse.h>
#import <Intents/INResumeWorkoutIntentResponse.h>
#import <Intents/INStartWorkoutIntentResponse.h>

#import <Intents/INPlayMediaIntentResponse.h>

#import <Intents/INSetRadioStationIntentResponse.h>

#import <Intents/INSearchForMessagesIntentResponse.h>
#import <Intents/INSendMessageIntentResponse.h>
#import <Intents/INSetMessageAttributeIntentResponse.h>

#import <Intents/INAddTasksIntentResponse.h>
#import <Intents/INAppendToNoteIntentResponse.h>
#import <Intents/INCreateNoteIntentResponse.h>
#import <Intents/INCreateTaskListIntentResponse.h>
#import <Intents/INSearchForNotebookItemsIntentResponse.h>
#import <Intents/INSetTaskAttributeIntentResponse.h>

#import <Intents/INPayBillIntentResponse.h>
#import <Intents/INRequestPaymentIntentResponse.h>
#import <Intents/INSearchForAccountsIntentResponse.h>
#import <Intents/INSearchForBillsIntentResponse.h>
#import <Intents/INSendPaymentIntentResponse.h>
#import <Intents/INTransferMoneyIntentResponse.h>

#import <Intents/INSearchForPhotosIntentResponse.h>
#import <Intents/INStartPhotoPlaybackIntentResponse.h>

#import <Intents/INGetRideStatusIntentResponse.h>
#import <Intents/INListRideOptionsIntentResponse.h>
#import <Intents/INRequestRideIntentResponse.h>
#import <Intents/INCancelRideIntentResponse.h>
#import <Intents/INSendRideFeedbackIntentResponse.h>

#import <Intents/INGetVisualCodeIntentResponse.h>

// ==========  Intents.framework/Headers/INSearchForMessagesIntentResponse.h
//
//  INSearchForMessagesIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INMessage;

typedef NS_ENUM(NSInteger, INSearchForMessagesIntentResponseCode) {
    INSearchForMessagesIntentResponseCodeUnspecified = 0,
    INSearchForMessagesIntentResponseCodeReady,
    INSearchForMessagesIntentResponseCodeInProgress,
    INSearchForMessagesIntentResponseCodeSuccess,
    INSearchForMessagesIntentResponseCodeFailure,
    INSearchForMessagesIntentResponseCodeFailureRequiringAppLaunch,
    INSearchForMessagesIntentResponseCodeFailureMessageServiceNotAvailable,
    INSearchForMessagesIntentResponseCodeFailureMessageTooManyResults,
} API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12));

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12))
@interface INSearchForMessagesIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSearchForMessagesIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSearchForMessagesIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INMessage *> *messages;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRidePartySizeOption.h
//
//  INRidePartySizeOption.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INPriceRange;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.0))
API_UNAVAILABLE(macosx)
@interface INRidePartySizeOption : NSObject <NSCopying, NSSecureCoding>

// A single party size in a set of party size selections. Each size may have a different price range.
- (instancetype)initWithPartySizeRange:(NSRange)partySizeRange sizeDescription:(NSString *)sizeDescription priceRange:(nullable INPriceRange *)priceRange NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

@property (readonly, NS_NONATOMIC_IOSONLY) NSRange partySizeRange; // The number of people allowed, e.g. NSMakeRange(1, 0) for one person, or NSMakeRange(1, 2) for 1 to 3 people.
@property (readonly, NS_NONATOMIC_IOSONLY) NSString *sizeDescription; // e.g. "1 passenger" or "1-3 passengers".
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) INPriceRange *priceRange; // the price range for this party size, which may be different from the indicative price range for the ride. If nil, the price range for the associated ride is valid instead.

@end

NS_ASSUME_NONNULL_END

// ==========  Intents.framework/Headers/INCallRecord.h
//
//  INCallRecord.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INCallCapability.h>
#import <Intents/INCallRecordType.h>

@class INPerson;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13))
@interface INCallRecord : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithIdentifier:(NSString *)identifier
                       dateCreated:(nullable NSDate *)dateCreated
                            caller:(nullable INPerson *)caller
                    callRecordType:(INCallRecordType)callRecordType
                    callCapability:(INCallCapability)callCapability
                      callDuration:(nullable NSNumber *)callDuration
                            unseen:(nullable NSNumber *)unseen NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *dateCreated;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *caller;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallRecordType callRecordType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *callDuration NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *unseen NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallCapability callCapability;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetDefrosterSettingsInCarIntent_Deprecated.h
//
//  INSetDefrosterSettingsInCarIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2018 Apple Inc. All rights reserved.
//

#import <Intents/INSetDefrosterSettingsInCarIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSetDefrosterSettingsInCarIntent (Deprecated)

- (instancetype)initWithEnable:(nullable NSNumber *)enable
                     defroster:(INCarDefroster)defroster API_DEPRECATED_WITH_REPLACEMENT("-initWithEnable:defroster:carName:", ios(10.0, 12.0)) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/NSString+Intents.h
//
//  NSString+Intents.h
//  Intents
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14))
@interface NSString (Intents)

// Reads the string from the Localizable.strings file in the main app's bundle
+ (NSString *)deferredLocalizedIntentsStringWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);

// Reads the string from the provided table file in the main app's bundle
+ (NSString *)deferredLocalizedIntentsStringWithFormat:(NSString *)format fromTable:(nullable NSString *)table, ... NS_FORMAT_FUNCTION(1,3);

// Reads the string from the provided table file in the main app's bundle
+ (NSString *)deferredLocalizedIntentsStringWithFormat:(NSString *)format fromTable:(nullable NSString *)table arguments:(va_list)arguments NS_FORMAT_FUNCTION(1,0) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPlayMediaIntent.h
//
//  INPlayMediaIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INPlaybackRepeatMode.h>

@class INMediaItem;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), watchos(5.0))
API_UNAVAILABLE(macosx)
@interface INPlayMediaIntent : INIntent

- (instancetype)initWithMediaItems:(nullable NSArray<INMediaItem *> *)mediaItems
                    mediaContainer:(nullable INMediaItem *)mediaContainer
                      playShuffled:(nullable NSNumber *)playShuffled
                playbackRepeatMode:(INPlaybackRepeatMode)playbackRepeatMode
                    resumePlayback:(nullable NSNumber *)resumePlayback NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INMediaItem *> *mediaItems;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INMediaItem *mediaContainer;

// An NSNumber representing a boolean value where true indicates that the media should be shuffled
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *playShuffled NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INPlaybackRepeatMode playbackRepeatMode;

// An NSNumber representing a boolean value where true indicates that the media should be resumed
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *resumePlayback NS_REFINED_FOR_SWIFT;

@end

@class INPlayMediaIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INPlayMediaIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(12.0), watchos(5.0))
API_UNAVAILABLE(macosx)
@protocol INPlayMediaIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INPlayMediaIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INPlayMediaIntentResponse containing the details of the result of having executed the intent

 @see  INPlayMediaIntentResponse
 */

- (void)handlePlayMedia:(INPlayMediaIntent *)intent
             completion:(void (^)(INPlayMediaIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INPlayMediaIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INPlayMediaIntentResponse
 */

- (void)confirmPlayMedia:(INPlayMediaIntent *)intent
              completion:(void (^)(INPlayMediaIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INStartPhotoPlaybackIntent.h
//
//  INStartPhotoPlaybackIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INConditionalOperator.h>
#import <Intents/INPhotoAttributeOptions.h>

@class CLPlacemark;
@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INPerson;
@class INPersonResolutionResult;
@class INPlacemarkResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INStartPhotoPlaybackIntent : INIntent

- (instancetype)initWithDateCreated:(nullable INDateComponentsRange *)dateCreated
                    locationCreated:(nullable CLPlacemark *)locationCreated
                          albumName:(nullable NSString *)albumName
                        searchTerms:(nullable NSArray<NSString *> *)searchTerms
                 includedAttributes:(INPhotoAttributeOptions)includedAttributes
                 excludedAttributes:(INPhotoAttributeOptions)excludedAttributes
                      peopleInPhoto:(nullable NSArray<INPerson *> *)peopleInPhoto NS_DESIGNATED_INITIALIZER;

// Include photos created in the specified date interval.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dateCreated;

// Include photos taken at the specified location.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *locationCreated;

// Include photos contained in albums matching this name.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *albumName;

// Include photos with keywords, names, descriptions, etc. that match these search terms.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *searchTerms;

// Describes how to combine the contents of the searchTerm array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator searchTermsOperator;

// When specified, only match photos of the given types.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INPhotoAttributeOptions includedAttributes;

// When specified, do not match photos of the given types.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INPhotoAttributeOptions excludedAttributes;

// INPerson objects that should be present in the included photos, dependent on the peopleInPhotoOperator.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *peopleInPhoto;

// Describes how to combine the contents of the peopleInPhoto array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator peopleInPhotoOperator;

@end

@class INStartPhotoPlaybackIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INStartPhotoPlaybackIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INStartPhotoPlaybackIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INStartPhotoPlaybackIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INStartPhotoPlaybackIntentResponse containing the details of the result of having executed the intent

 @see  INStartPhotoPlaybackIntentResponse
 */

- (void)handleStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                      completion:(void (^)(INStartPhotoPlaybackIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INStartPhotoPlaybackIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INStartPhotoPlaybackIntentResponse
 */

- (void)confirmStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                       completion:(void (^)(INStartPhotoPlaybackIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveDateCreatedForStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                    withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDateCreated(for:with:));

- (void)resolveLocationCreatedForStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                    withCompletion:(void (^)(INPlacemarkResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveLocationCreated(for:with:));

- (void)resolveAlbumNameForStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                    withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAlbumName(for:with:));

- (void)resolvePeopleInPhotoForStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                    withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolvePeopleInPhoto(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INGetCarLockStatusIntentResponse.h
//
//  INGetCarLockStatusIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INGetCarLockStatusIntentResponseCode) {
    INGetCarLockStatusIntentResponseCodeUnspecified = 0,
    INGetCarLockStatusIntentResponseCodeReady,
    INGetCarLockStatusIntentResponseCodeInProgress,
    INGetCarLockStatusIntentResponseCodeSuccess,
    INGetCarLockStatusIntentResponseCodeFailure,
    INGetCarLockStatusIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INGetCarLockStatusIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INGetCarLockStatusIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INGetCarLockStatusIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *locked NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPlayMediaIntentResponse.h
//
//  INPlayMediaIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INPlayMediaIntentResponseCode) {
    INPlayMediaIntentResponseCodeUnspecified = 0,
    INPlayMediaIntentResponseCodeReady,
    INPlayMediaIntentResponseCodeContinueInApp,
    INPlayMediaIntentResponseCodeInProgress,
    INPlayMediaIntentResponseCodeSuccess,
    INPlayMediaIntentResponseCodeHandleInApp API_UNAVAILABLE(watchos),
    INPlayMediaIntentResponseCodeFailure,
    INPlayMediaIntentResponseCodeFailureRequiringAppLaunch,
    INPlayMediaIntentResponseCodeFailureUnknownMediaType,
    INPlayMediaIntentResponseCodeFailureNoUnplayedContent,
    INPlayMediaIntentResponseCodeFailureRestrictedContent,
} API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), watchos(5.0))
API_UNAVAILABLE(macosx)
@interface INPlayMediaIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INPlayMediaIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INPlayMediaIntentResponseCode code;

// This dictionary should be populated using the keys from MPNowPlayingInfoCenter
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSDictionary<NSString *, id> *nowPlayingInfo;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/CLPlacemark+IntentsAdditions.h
//
//  CLPlacemark+IntentsAdditions.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CLPlacemark.h>

@class CNPostalAddress;

NS_ASSUME_NONNULL_BEGIN

@interface CLPlacemark (INIntentsAdditions)

+ (instancetype)placemarkWithLocation:(CLLocation *)location
                                 name:(nullable NSString *)name
                        postalAddress:(nullable CNPostalAddress *)postalAddress API_AVAILABLE(ios(10.0), watchos(3.2));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCarAudioSourceResolutionResult.h
//
//  INCarAudioSourceResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarAudioSource.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INCarAudioSourceResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INCarAudioSource. The resolvedValue can be different than the original INCarAudioSource. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedCarAudioSource:(INCarAudioSource)resolvedCarAudioSource NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INCarAudioSource)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedCarAudioSource:", ios(10.0, 11.0));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithCarAudioSourceToConfirm:(INCarAudioSource)carAudioSourceToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INCarAudioSource)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithCarAudioSourceToConfirm:", ios(10.0, 11.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetDefrosterSettingsInCarIntent.h
//
//  INSetDefrosterSettingsInCarIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarDefroster.h>

@class INBooleanResolutionResult;
@class INCarDefrosterResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INSetDefrosterSettingsInCarIntent : INIntent

- (instancetype)initWithEnable:(nullable NSNumber *)enable
                     defroster:(INCarDefroster)defroster
                       carName:(nullable INSpeakableString *)carName NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(12.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *enable NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCarDefroster defroster;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *carName API_AVAILABLE(ios(12.0));

@end

@class INSetDefrosterSettingsInCarIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSetDefrosterSettingsInCarIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@protocol INSetDefrosterSettingsInCarIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSetDefrosterSettingsInCarIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSetDefrosterSettingsInCarIntentResponse containing the details of the result of having executed the intent

 @see  INSetDefrosterSettingsInCarIntentResponse
 */

- (void)handleSetDefrosterSettingsInCar:(INSetDefrosterSettingsInCarIntent *)intent
                             completion:(void (^)(INSetDefrosterSettingsInCarIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSetDefrosterSettingsInCarIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetDefrosterSettingsInCarIntentResponse
 */

- (void)confirmSetDefrosterSettingsInCar:(INSetDefrosterSettingsInCarIntent *)intent
                              completion:(void (^)(INSetDefrosterSettingsInCarIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveEnableForSetDefrosterSettingsInCar:(INSetDefrosterSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnable(for:with:));

- (void)resolveDefrosterForSetDefrosterSettingsInCar:(INSetDefrosterSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INCarDefrosterResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDefroster(for:with:));

- (void)resolveCarNameForSetDefrosterSettingsInCar:(INSetDefrosterSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCarName(for:with:)) API_AVAILABLE(ios(12.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPaymentAmount.h
//
//  INPaymentAmount.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INAmountType.h>

@class INCurrencyAmount;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INPaymentAmount : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithAmountType:(INAmountType)amountType
                            amount:(INCurrencyAmount *)amount NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *amount;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INAmountType amountType;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCancelWorkoutIntentResponse.h
//
//  INCancelWorkoutIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INCancelWorkoutIntentResponseCode) {
    INCancelWorkoutIntentResponseCodeUnspecified = 0,
    INCancelWorkoutIntentResponseCodeReady,
    INCancelWorkoutIntentResponseCodeContinueInApp API_AVAILABLE(watchos(3.2)) API_DEPRECATED("INCancelWorkoutIntentResponseCodeContinueInApp is deprecated on iOS. Please use INCancelWorkoutIntentResponseCodeHandleInApp instead", ios(10.0, 11.0)),
    INCancelWorkoutIntentResponseCodeFailure,
    INCancelWorkoutIntentResponseCodeFailureRequiringAppLaunch,
    INCancelWorkoutIntentResponseCodeFailureNoMatchingWorkout,
    INCancelWorkoutIntentResponseCodeHandleInApp API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos),
    INCancelWorkoutIntentResponseCodeSuccess NS_EXTENSION_UNAVAILABLE("INCancelWorkoutIntentResponseCodeSuccess is not available to extensions. This can only be returned from the app.") API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos),
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INCancelWorkoutIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INCancelWorkoutIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INCancelWorkoutIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetClimateSettingsInCarIntent.h
//
//  INSetClimateSettingsInCarIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarAirCirculationMode.h>
#import <Intents/INCarSeat.h>
#import <Intents/INRelativeSetting.h>

@class INBooleanResolutionResult;
@class INCarAirCirculationModeResolutionResult;
@class INCarSeatResolutionResult;
@class INDoubleResolutionResult;
@class INIntegerResolutionResult;
@class INRelativeSettingResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;
@class INTemperatureResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INSetClimateSettingsInCarIntent : INIntent

- (instancetype)initWithEnableFan:(nullable NSNumber *)enableFan
             enableAirConditioner:(nullable NSNumber *)enableAirConditioner
             enableClimateControl:(nullable NSNumber *)enableClimateControl
                   enableAutoMode:(nullable NSNumber *)enableAutoMode
               airCirculationMode:(INCarAirCirculationMode)airCirculationMode
                    fanSpeedIndex:(nullable NSNumber *)fanSpeedIndex
               fanSpeedPercentage:(nullable NSNumber *)fanSpeedPercentage
          relativeFanSpeedSetting:(INRelativeSetting)relativeFanSpeedSetting
                      temperature:(nullable NSMeasurement<NSUnitTemperature *> *)temperature
       relativeTemperatureSetting:(INRelativeSetting)relativeTemperatureSetting
                      climateZone:(INCarSeat)climateZone
                          carName:(nullable INSpeakableString *)carName NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(12.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *enableFan NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *enableAirConditioner NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *enableClimateControl NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *enableAutoMode NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCarAirCirculationMode airCirculationMode;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *fanSpeedIndex NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *fanSpeedPercentage NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INRelativeSetting relativeFanSpeedSetting;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSMeasurement<NSUnitTemperature *> *temperature;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INRelativeSetting relativeTemperatureSetting;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCarSeat climateZone;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *carName API_AVAILABLE(ios(12.0));

@end

@class INSetClimateSettingsInCarIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSetClimateSettingsInCarIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@protocol INSetClimateSettingsInCarIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSetClimateSettingsInCarIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSetClimateSettingsInCarIntentResponse containing the details of the result of having executed the intent

 @see  INSetClimateSettingsInCarIntentResponse
 */

- (void)handleSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                           completion:(void (^)(INSetClimateSettingsInCarIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSetClimateSettingsInCarIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetClimateSettingsInCarIntentResponse
 */

- (void)confirmSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                            completion:(void (^)(INSetClimateSettingsInCarIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveEnableFanForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableFan(for:with:));

- (void)resolveEnableAirConditionerForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableAirConditioner(for:with:));

- (void)resolveEnableClimateControlForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableClimateControl(for:with:));

- (void)resolveEnableAutoModeForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableAutoMode(for:with:));

- (void)resolveAirCirculationModeForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INCarAirCirculationModeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAirCirculationMode(for:with:));

- (void)resolveFanSpeedIndexForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveFanSpeedIndex(for:with:));

- (void)resolveFanSpeedPercentageForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INDoubleResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveFanSpeedPercentage(for:with:));

- (void)resolveRelativeFanSpeedSettingForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INRelativeSettingResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRelativeFanSpeedSetting(for:with:));

- (void)resolveTemperatureForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INTemperatureResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTemperature(for:with:));

- (void)resolveRelativeTemperatureSettingForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INRelativeSettingResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRelativeTemperatureSetting(for:with:));

- (void)resolveClimateZoneForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INCarSeatResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveClimateZone(for:with:));

- (void)resolveCarNameForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCarName(for:with:)) API_AVAILABLE(ios(12.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCarAirCirculationModeResolutionResult.h
//
//  INCarAirCirculationModeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarAirCirculationMode.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INCarAirCirculationModeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INCarAirCirculationMode. The resolvedValue can be different than the original INCarAirCirculationMode. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedCarAirCirculationMode:(INCarAirCirculationMode)resolvedCarAirCirculationMode NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INCarAirCirculationMode)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedCarAirCirculationMode:", ios(10.0, 11.0));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithCarAirCirculationModeToConfirm:(INCarAirCirculationMode)carAirCirculationModeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INCarAirCirculationMode)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithCarAirCirculationModeToConfirm:", ios(10.0, 11.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRequestPaymentIntentResponse.h
//
//  INRequestPaymentIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INPaymentRecord;

typedef NS_ENUM(NSInteger, INRequestPaymentIntentResponseCode) {
    INRequestPaymentIntentResponseCodeUnspecified = 0,
    INRequestPaymentIntentResponseCodeReady,
    INRequestPaymentIntentResponseCodeInProgress,
    INRequestPaymentIntentResponseCodeSuccess,
    INRequestPaymentIntentResponseCodeFailure,
    INRequestPaymentIntentResponseCodeFailureRequiringAppLaunch,
    INRequestPaymentIntentResponseCodeFailureCredentialsUnverified,
    INRequestPaymentIntentResponseCodeFailurePaymentsAmountBelowMinimum,
    INRequestPaymentIntentResponseCodeFailurePaymentsAmountAboveMaximum,
    INRequestPaymentIntentResponseCodeFailurePaymentsCurrencyUnsupported,
    INRequestPaymentIntentResponseCodeFailureNoBankAccount,
    INRequestPaymentIntentResponseCodeFailureNotEligible API_AVAILABLE(ios(11.0), watchos(4.0)),
    INRequestPaymentIntentResponseCodeFailureTermsAndConditionsAcceptanceRequired API_AVAILABLE(ios(11.1), watchos(4.1)),
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INRequestPaymentIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INRequestPaymentIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INRequestPaymentIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentRecord *paymentRecord;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCarSignalOptionsResolutionResult.h
//
//  INCarSignalOptionsResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarSignalOptions.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INCarSignalOptionsResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INCarSignalOptions. The resolvedValue can be different than the original INCarSignalOptions. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedCarSignalOptions:(INCarSignalOptions)resolvedCarSignalOptions NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INCarSignalOptions)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedCarSignalOptions:", ios(10.3, 11.0), watchos(3.2, 4.0));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithCarSignalOptionsToConfirm:(INCarSignalOptions)carSignalOptionsToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INCarSignalOptions)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithCarSignalOptionsToConfirm:", ios(10.3, 11.0), watchos(3.2, 4.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSendMessageRecipientResolutionResult.h
//
//  INSendMessageRecipientResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INPersonResolutionResult.h>

typedef NS_ENUM(NSInteger, INSendMessageRecipientUnsupportedReason) {
    INSendMessageRecipientUnsupportedReasonNoAccount = 1,
    INSendMessageRecipientUnsupportedReasonOffline,
    INSendMessageRecipientUnsupportedReasonMessagingServiceNotEnabledForRecipient,
    INSendMessageRecipientUnsupportedReasonNoValidHandle API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14)),
    INSendMessageRecipientUnsupportedReasonRequestedHandleInvalid API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14)),
    INSendMessageRecipientUnsupportedReasonNoHandleForLabel API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14)),
} API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13))
@interface INSendMessageRecipientResolutionResult : INPersonResolutionResult

+ (instancetype)unsupportedForReason:(INSendMessageRecipientUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithPersonResolutionResult:(INPersonResolutionResult *)personResolutionResult;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INImage.h
//
//  INImage.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class NSData;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INImage : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)imageNamed:(NSString *)name;
+ (instancetype)imageWithImageData:(NSData *)imageData;
+ (nullable instancetype)imageWithURL:(NSURL *)URL;
+ (nullable instancetype)imageWithURL:(NSURL *)URL width:(double)width height:(double)height API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetProfileInCarIntent.h
//
//  INSetProfileInCarIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INIntegerResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;
@class INStringResolutionResult;
@class INBooleanResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INSetProfileInCarIntent : INIntent

- (instancetype)initWithProfileNumber:(nullable NSNumber *)profileNumber
                          profileName:(nullable NSString *)profileName
                       defaultProfile:(nullable NSNumber *)defaultProfile
                              carName:(nullable INSpeakableString *)carName NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(12.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *profileNumber NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *profileName API_AVAILABLE(ios(10.2));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *defaultProfile NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *carName API_AVAILABLE(ios(12.0));

@end

@class INSetProfileInCarIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSetProfileInCarIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@protocol INSetProfileInCarIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSetProfileInCarIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSetProfileInCarIntentResponse containing the details of the result of having executed the intent

 @see  INSetProfileInCarIntentResponse
 */

- (void)handleSetProfileInCar:(INSetProfileInCarIntent *)intent
                   completion:(void (^)(INSetProfileInCarIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSetProfileInCarIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetProfileInCarIntentResponse
 */

- (void)confirmSetProfileInCar:(INSetProfileInCarIntent *)intent
                    completion:(void (^)(INSetProfileInCarIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveProfileNumberForSetProfileInCar:(INSetProfileInCarIntent *)intent
                    withCompletion:(void (^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveProfileNumber(for:with:));

- (void)resolveProfileNameForSetProfileInCar:(INSetProfileInCarIntent *)intent
                    withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveProfileName(for:with:)) API_AVAILABLE(ios(10.2));

- (void)resolveCarNameForSetProfileInCar:(INSetProfileInCarIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCarName(for:with:)) API_AVAILABLE(ios(12.0));

- (void)resolveDefaultProfileForSetProfileInCar:(INSetProfileInCarIntent *)intent
                                 withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDefaultProfile(forSetProfileInCar:with:)) API_DEPRECATED("The property doesn't need to be resolved", ios(10.0, 11.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRidePhase.h
//
//  INRidePhase.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INRidePhase_h
#define INRidePhase_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INRidePhase) {
    INRidePhaseUnknown = 0,
    INRidePhaseReceived,
    INRidePhaseConfirmed,
    INRidePhaseOngoing,
    INRidePhaseCompleted,
    INRidePhaseApproachingPickup,
    INRidePhasePickup,
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

#endif // INRidePhase_h
// ==========  Intents.framework/Headers/INRideFareLineItem.h
//
//  INRideFareLineItem.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

API_AVAILABLE(ios(10.0), watchos(3.0))
API_UNAVAILABLE(macosx)
@interface INRideFareLineItem : NSObject <NSCopying, NSSecureCoding>

// A single line item in a set of pricing line items that describes
- (instancetype)initWithTitle:(NSString *)title price:(NSDecimalNumber *)price currencyCode:(NSString *)currencyCode NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

@property (readonly, nonatomic) NSString *title; // e.g. "Base fare", or "+ per mile"
@property (readonly, nonatomic) NSDecimalNumber *price; // e.g. '4.50'
@property (readonly, nonatomic) NSString *currencyCode; // the ISO currency code for the currency for this price, e.g. "USD" for U.S. Dollar.

@end
// ==========  Intents.framework/Headers/INWorkoutLocationType.h
//
//  INWorkoutLocationType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INWorkoutLocationType_h
#define INWorkoutLocationType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INWorkoutLocationType) {
    INWorkoutLocationTypeUnknown = 0,
    INWorkoutLocationTypeOutdoor,
    INWorkoutLocationTypeIndoor,
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

#endif // INWorkoutLocationType_h
// ==========  Intents.framework/Headers/INGetRestaurantGuestIntent.h
//
//  INGetRestaurantGuestIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntent.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INGetRestaurantGuestIntent : INIntent

@end

@class INGetRestaurantGuestIntentResponse;

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@protocol INGetRestaurantGuestIntentHandling <NSObject>

/*!
 @abstract Handling method - Execute the task represented by the INGetRestaurantGuestIntent that's passed in
 @discussion This method is called to actually execute the intent, the app must return a response for this intent and an NSUserActivity capturing the state that the app must be restored to at the end of handling this intent
 
 @param  intent The input intent
 @param  completion The response handling block to invoke with the response to handling the intent.
 
 @see  INGetRestaurantGuestIntentResponse
 
 */
- (void)handleGetRestaurantGuest:(INGetRestaurantGuestIntent *)intent completion:(void (^)(INGetRestaurantGuestIntentResponse *response))completion NS_SWIFT_NAME(handle(getRestaurantGuest:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.
 
 @param  guestIntent The input intent
 @param  completion The response block contains an INGetRestaurantGuestIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.
 
 @see INGetRestaurantGuestIntentResponse
 
 */

- (void)confirmGetRestaurantGuest:(INGetRestaurantGuestIntent *)guestIntent completion:(void (^)(INGetRestaurantGuestIntentResponse *response))completion NS_SWIFT_NAME(confirm(getRestaurantGuest:completion:));

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRelativeSettingResolutionResult.h
//
//  INRelativeSettingResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INRelativeSetting.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INRelativeSettingResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INRelativeSetting. The resolvedValue can be different than the original INRelativeSetting. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedRelativeSetting:(INRelativeSetting)resolvedRelativeSetting NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INRelativeSetting)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedRelativeSetting:", ios(10.0, 11.0));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithRelativeSettingToConfirm:(INRelativeSetting)relativeSettingToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INRelativeSetting)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithRelativeSettingToConfirm:", ios(10.0, 11.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INMediaItemType.h
//
//  INMediaItemType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INMediaItemType_h
#define INMediaItemType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INMediaItemType) {
    INMediaItemTypeUnknown = 0,
    INMediaItemTypeSong,
    INMediaItemTypeAlbum,
    INMediaItemTypeArtist,
    INMediaItemTypeGenre,
    INMediaItemTypePlaylist,
    INMediaItemTypePodcastShow,
    INMediaItemTypePodcastEpisode,
    INMediaItemTypePodcastPlaylist,
    INMediaItemTypeMusicStation,
    INMediaItemTypeAudioBook,
    INMediaItemTypeMovie,
    INMediaItemTypeTVShow,
    INMediaItemTypeTVShowEpisode,
    INMediaItemTypeMusicVideo,
} API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx);

#endif // INMediaItemType_h
// ==========  Intents.framework/Headers/Intents.h
//
//  Intents.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

//! Project version number for Intents.
FOUNDATION_EXPORT double IntentsVersionNumber;

//! Project version string for Intents.
FOUNDATION_EXPORT const unsigned char IntentsVersionString[];

#ifndef __INTENTS_INDIRECT__
#define __INTENTS_INDIRECT__
#endif

// Base
#import <Intents/INIntent.h>
#import <Intents/INIntentErrors.h>
#import <Intents/INIntentHandlerProviding.h>
#import <Intents/INIntentIdentifiers.h>
#import <Intents/INIntentResponse.h>
#import <Intents/INIntentResolutionResult.h>
#import <Intents/INDomainHandling.h>
#import <Intents/INInteraction.h>
#import <Intents/INSpeakable.h>
#import <Intents/INParameter.h>

// Intents & Intent Responses
#import <Intents/INIntents.h>
#import <Intents/INIntentResponses.h>

// Generated
#import <Intents/Intents_Generated.h>

// Extension
#import <Intents/INExtension.h>

// Common Types
#import <Intents/INPersonHandle.h>
#import <Intents/INCurrencyAmount.h>
#import <Intents/INDateComponentsRange.h>
#import <Intents/INImage.h>
#import <Intents/INObject.h>
#import <Intents/INPerson.h>
#import <Intents/INRecurrenceRule.h>
#import <Intents/INSpeakableString.h>

// Common Resolution Results
#import <Intents/INBooleanResolutionResult.h>
#import <Intents/INDateComponentsRangeResolutionResult.h>
#import <Intents/INDoubleResolutionResult.h>
#import <Intents/INIntegerResolutionResult.h>
#import <Intents/INPersonResolutionResult.h>
#import <Intents/INPlacemarkResolutionResult.h>
#import <Intents/INSpeakableStringResolutionResult.h>
#import <Intents/INStringResolutionResult.h>
#import <Intents/INTemperatureResolutionResult.h>
#import <Intents/INDateComponentsResolutionResult.h>
#import <Intents/INRestaurantResolutionResult.h>
#import <Intents/INRestaurantGuestResolutionResult.h>

// Messages Domain
#import <Intents/INMessage.h>

// Payments Domain
#import <Intents/INBalanceAmount.h>

// Ridesharing Domain
#import <Intents/INPriceRange.h>
#import <Intents/INRideOption.h>
#import <Intents/INRideStatus.h>
#import <Intents/INRideDriver.h>
#import <Intents/INRideVehicle.h>
#import <Intents/INRideFareLineItem.h>
#import <Intents/INRidePartySizeOption.h>
#import <Intents/INRideCompletionStatus.h>

// Restaurant Booking
#import <Intents/INIntentRestaurantReservation.h>

// User Vocabulary
#import <Intents/INVocabulary.h>

#import <Intents/INUpcomingMediaManager.h>

// Utilities
#import <Intents/INSiriAuthorizationStatus.h>
#import <Intents/INPreferences.h>
#import <Intents/CLPlacemark+IntentsAdditions.h>
#import <Intents/NSUserActivity+IntentsAdditions.h>
#import <Intents/INPerson+SiriAdditions.h>
#import <Intents/NSString+Intents.h>

// Notes
#import <Intents/INNoteContent.h>
#import <Intents/INTextNoteContent.h>
#import <Intents/INImageNoteContent.h>

// Shortcuts
#import <Intents/INRelevantShortcut.h>
#import <Intents/INRelevantShortcutStore.h>
#import <Intents/INShortcut.h>
#import <Intents/INVoiceShortcut.h>
#import <Intents/INVoiceShortcutCenter.h>

// Deprecated
#import <Intents/INPerson_Deprecated.h>
#import <Intents/INRequestRideIntent_Deprecated.h>
#import <Intents/INRideDriver_Deprecated.h>
#import <Intents/INSaveProfileInCarIntent_Deprecated.h>
#import <Intents/INSearchCallHistoryIntent_Deprecated.h>
#import <Intents/INStartAudioCallIntent_Deprecated.h>
#import <Intents/INSearchForMessagesIntent_Deprecated.h>
#import <Intents/INSendMessageIntent_Deprecated.h>
#import <Intents/INSetProfileInCarIntent_Deprecated.h>
#import <Intents/INSetClimateSettingsInCarIntent_Deprecated.h>
#import <Intents/INSetDefrosterSettingsInCarIntent_Deprecated.h>
#import <Intents/INSetSeatSettingsInCarIntent_Deprecated.h>
#import <Intents/INSearchForNotebookItemsIntent_Deprecated.h>
// ==========  Intents.framework/Headers/INCreateTaskListIntent.h
//
//  INCreateTaskListIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INCreateTaskListIntent : INIntent

- (instancetype)initWithTitle:(nullable INSpeakableString *)title
                   taskTitles:(nullable NSArray<INSpeakableString *> *)taskTitles
                    groupName:(nullable INSpeakableString *)groupName NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *title;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INSpeakableString *> *taskTitles;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *groupName;

@end

@class INCreateTaskListIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INCreateTaskListIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@protocol INCreateTaskListIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INCreateTaskListIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INCreateTaskListIntentResponse containing the details of the result of having executed the intent

 @see  INCreateTaskListIntentResponse
 */

- (void)handleCreateTaskList:(INCreateTaskListIntent *)intent
                  completion:(void (^)(INCreateTaskListIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INCreateTaskListIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INCreateTaskListIntentResponse
 */

- (void)confirmCreateTaskList:(INCreateTaskListIntent *)intent
                   completion:(void (^)(INCreateTaskListIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveTitleForCreateTaskList:(INCreateTaskListIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTitle(for:with:));

- (void)resolveTaskTitlesForCreateTaskList:(INCreateTaskListIntent *)intent
                    withCompletion:(void (^)(NSArray<INSpeakableStringResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveTaskTitles(for:with:));

- (void)resolveGroupNameForCreateTaskList:(INCreateTaskListIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveGroupName(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSendPaymentIntent.h
//
//  INSendPaymentIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INCurrencyAmount;
@class INCurrencyAmountResolutionResult;
@class INPerson;
@class INPersonResolutionResult;
@class INSendPaymentCurrencyAmountResolutionResult;
@class INSendPaymentPayeeResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INSendPaymentIntent : INIntent

- (instancetype)initWithPayee:(nullable INPerson *)payee
               currencyAmount:(nullable INCurrencyAmount *)currencyAmount
                         note:(nullable NSString *)note NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *payee;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *currencyAmount;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *note;

@end

@class INSendPaymentIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSendPaymentIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INSendPaymentIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSendPaymentIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSendPaymentIntentResponse containing the details of the result of having executed the intent

 @see  INSendPaymentIntentResponse
 */

- (void)handleSendPayment:(INSendPaymentIntent *)intent
               completion:(void (^)(INSendPaymentIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSendPaymentIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSendPaymentIntentResponse
 */

- (void)confirmSendPayment:(INSendPaymentIntent *)intent
                completion:(void (^)(INSendPaymentIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolvePayeeForSendPayment:(INSendPaymentIntent *)intent
                    withCompletion:(void (^)(INPersonResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePayee(for:with:)) API_DEPRECATED("resolvePayeeForSendPayment:withCompletion: is deprecated. Use resolvePayeeForSendPayment:completion: instead", ios(10.0, 11.0), watchos(3.2, 4.0));

- (void)resolvePayeeForSendPayment:(INSendPaymentIntent *)intent
                    completion:(void (^)(INSendPaymentPayeeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePayee(for:with:)) API_AVAILABLE(ios(11.0), watchos(4.0));

- (void)resolveCurrencyAmountForSendPayment:(INSendPaymentIntent *)intent
                    withCompletion:(void (^)(INCurrencyAmountResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCurrencyAmount(for:with:)) API_DEPRECATED("resolveCurrencyAmountForSendPayment:withCompletion: is deprecated. Use resolveCurrencyAmountForSendPayment:completion: instead", ios(10.0, 11.0), watchos(3.2, 4.0));

- (void)resolveCurrencyAmountForSendPayment:(INSendPaymentIntent *)intent
                    completion:(void (^)(INSendPaymentCurrencyAmountResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCurrencyAmount(for:with:)) API_AVAILABLE(ios(11.0), watchos(4.0));

- (void)resolveNoteForSendPayment:(INSendPaymentIntent *)intent
                    withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveNote(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRideStatus.h
//
//  INRideStatus.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INRidePhase.h>

@class CLPlacemark;
@class INDateComponentsRange;
@class INRideVehicle;
@class INRideDriver;
@class INRideOption;
@class INRideCompletionStatus;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.0))
API_UNAVAILABLE(macosx)
@interface INRideStatus : NSObject <NSCopying, NSSecureCoding>

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *rideIdentifier;

@property (readwrite, assign, NS_NONATOMIC_IOSONLY) INRidePhase phase;

// This property should be set if the phase is INRidePhaseCompleted.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INRideCompletionStatus *completionStatus;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INRideVehicle *vehicle;
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INRideDriver *driver;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *estimatedPickupDate;
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *estimatedDropOffDate;

// This is the date after arrival at the pickup location after which the ride may stop waiting for the passenger to be picked up.
// The passenger is expected to arrive at pickup before this date.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *estimatedPickupEndDate;

// Time range for the scheduled pickup.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *scheduledPickupTime API_AVAILABLE(ios(10.3), watchos(3.2));

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *pickupLocation;
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<CLPlacemark *> *waypoints;
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *dropOffLocation;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INRideOption *rideOption;

@property (readwrite, strong, nullable, NS_NONATOMIC_IOSONLY) NSUserActivity *userActivityForCancelingInApplication; // If set, and the ride hasn't completed or been canceled yet, the system may open the containing application and request continuation of this activity to request that the ride be canceled. It is appropriate to show confirmation UI to the user when this happens.

// These actions may be available for the user to choose during the ride.
// When shown, the .title of each activity will presented to the user. Selecting an activity will open your application to continue it.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSUserActivity *> *additionalActionActivities;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INMessageAttributeOptions.h
//
//  INMessageAttributeOptions.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INMessageAttributeOptions_h
#define INMessageAttributeOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INMessageAttributeOptions) {
    INMessageAttributeOptionRead = (1UL << 0),
    INMessageAttributeOptionUnread = (1UL << 1),
    INMessageAttributeOptionFlagged = (1UL << 2),
    INMessageAttributeOptionUnflagged = (1UL << 3),
    INMessageAttributeOptionPlayed API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13)) = (1UL << 4),
} API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12));

#endif // INMessageAttributeOptions_h
// ==========  Intents.framework/Headers/INIntentResponse.h
//
//  INIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INIntentResponse : NSObject <NSCopying, NSSecureCoding>

// This user activity will be used to launch the containing application when host application finds appropriate or when users request so.
// The containing application should implement the continuity app delegate method(s) to consume this user activity.
@property (copy, readwrite, nullable, NS_NONATOMIC_IOSONLY) NSUserActivity *userActivity;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSpeakable.h
//
//  INSpeakable.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol INSpeakable <NSObject>

@property (readonly, strong, nonnull, NS_NONATOMIC_IOSONLY) NSString *spokenPhrase;
@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) NSString *pronunciationHint;
@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) NSString *vocabularyIdentifier;

@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) NSArray<id<INSpeakable>> *alternativeSpeakableMatches;

@optional

@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier API_DEPRECATED("Please use vocabularyIdentifier", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

@end
// ==========  Intents.framework/Headers/INGetVisualCodeIntent.h
//
//  INGetVisualCodeIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INVisualCodeType.h>

@class INVisualCodeTypeResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INGetVisualCodeIntent : INIntent

- (instancetype)initWithVisualCodeType:(INVisualCodeType)visualCodeType NS_DESIGNATED_INITIALIZER;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INVisualCodeType visualCodeType;

@end

@class INGetVisualCodeIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INGetVisualCodeIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@protocol INGetVisualCodeIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INGetVisualCodeIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INGetVisualCodeIntentResponse containing the details of the result of having executed the intent

 @see  INGetVisualCodeIntentResponse
 */

- (void)handleGetVisualCode:(INGetVisualCodeIntent *)intent
                 completion:(void (^)(INGetVisualCodeIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INGetVisualCodeIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INGetVisualCodeIntentResponse
 */

- (void)confirmGetVisualCode:(INGetVisualCodeIntent *)intent
                  completion:(void (^)(INGetVisualCodeIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveVisualCodeTypeForGetVisualCode:(INGetVisualCodeIntent *)intent
                    withCompletion:(void (^)(INVisualCodeTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveVisualCodeType(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INImageNoteContent.h
//
//  INImageNoteContent.h
//  Intents
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Intents/INNoteContent.h>

@class INImage;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0))
@interface INImageNoteContent : INNoteContent <NSSecureCoding, NSCopying>

- (instancetype)initWithImage:(INImage *)image;

// The image that comprises the note content
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INImage *image;

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSendPaymentCurrencyAmountResolutionResult.h
//
//  INSendPaymentCurrencyAmountResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INCurrencyAmountResolutionResult.h>

typedef NS_ENUM(NSInteger, INSendPaymentCurrencyAmountUnsupportedReason) {
    INSendPaymentCurrencyAmountUnsupportedReasonPaymentsAmountBelowMinimum = 1,
    INSendPaymentCurrencyAmountUnsupportedReasonPaymentsAmountAboveMaximum,
    INSendPaymentCurrencyAmountUnsupportedReasonPaymentsCurrencyUnsupported,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INSendPaymentCurrencyAmountResolutionResult : INCurrencyAmountResolutionResult

+ (instancetype)unsupportedForReason:(INSendPaymentCurrencyAmountUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithCurrencyAmountResolutionResult:(INCurrencyAmountResolutionResult *)currencyAmountResolutionResult;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INGetCarLockStatusIntent.h
//
//  INGetCarLockStatusIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INGetCarLockStatusIntent : INIntent

- (instancetype)initWithCarName:(nullable INSpeakableString *)carName NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *carName;

@end

@class INGetCarLockStatusIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INGetCarLockStatusIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INGetCarLockStatusIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INGetCarLockStatusIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INGetCarLockStatusIntentResponse containing the details of the result of having executed the intent

 @see  INGetCarLockStatusIntentResponse
 */

- (void)handleGetCarLockStatus:(INGetCarLockStatusIntent *)intent
                    completion:(void (^)(INGetCarLockStatusIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INGetCarLockStatusIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INGetCarLockStatusIntentResponse
 */

- (void)confirmGetCarLockStatus:(INGetCarLockStatusIntent *)intent
                     completion:(void (^)(INGetCarLockStatusIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveCarNameForGetCarLockStatus:(INGetCarLockStatusIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCarName(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCallDestinationTypeResolutionResult.h
//
//  INCallDestinationTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCallDestinationType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13))
@interface INCallDestinationTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INCallDestinationType. The resolvedValue can be different than the original INCallDestinationType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedCallDestinationType:(INCallDestinationType)resolvedCallDestinationType NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithCallDestinationTypeToConfirm:(INCallDestinationType)callDestinationTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRequestRideIntentResponse.h
//
//  INRequestRideIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INRideStatus;

typedef NS_ENUM(NSInteger, INRequestRideIntentResponseCode) {
    INRequestRideIntentResponseCodeUnspecified = 0,
    INRequestRideIntentResponseCodeReady,
    INRequestRideIntentResponseCodeInProgress API_DEPRECATED("INRequestRideIntentResponseCodeInProgress is deprecated.", ios(10.0, 11.0), watchos(3.2, 4.0)),
    INRequestRideIntentResponseCodeSuccess,
    INRequestRideIntentResponseCodeFailure,
    INRequestRideIntentResponseCodeFailureRequiringAppLaunch,
    INRequestRideIntentResponseCodeFailureRequiringAppLaunchMustVerifyCredentials,
    INRequestRideIntentResponseCodeFailureRequiringAppLaunchNoServiceInArea,
    INRequestRideIntentResponseCodeFailureRequiringAppLaunchServiceTemporarilyUnavailable,
    INRequestRideIntentResponseCodeFailureRequiringAppLaunchPreviousRideNeedsCompletion,
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INRequestRideIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INRequestRideIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INRequestRideIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INRideStatus *rideStatus;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INNote.h
//
//  INNote.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INNoteContent;
@class INSpeakableString;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INNote : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithTitle:(INSpeakableString *)title
                     contents:(NSArray<INNoteContent *> *)contents
                    groupName:(nullable INSpeakableString *)groupName
        createdDateComponents:(nullable NSDateComponents *)createdDateComponents
       modifiedDateComponents:(nullable NSDateComponents *)modifiedDateComponents
                   identifier:(nullable NSString *)identifier NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INSpeakableString *title;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<INNoteContent *> *contents;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *groupName;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *createdDateComponents;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *modifiedDateComponents;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPlaybackRepeatMode.h
//
//  INPlaybackRepeatMode.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INPlaybackRepeatMode_h
#define INPlaybackRepeatMode_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INPlaybackRepeatMode) {
    INPlaybackRepeatModeUnknown = 0,
    INPlaybackRepeatModeNone,
    INPlaybackRepeatModeAll,
    INPlaybackRepeatModeOne,
} API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx);

#endif // INPlaybackRepeatMode_h
// ==========  Intents.framework/Headers/INPayBillIntentResponse.h
//
//  INPayBillIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INBillDetails;
@class INDateComponentsRange;
@class INPaymentAccount;
@class INPaymentAmount;

typedef NS_ENUM(NSInteger, INPayBillIntentResponseCode) {
    INPayBillIntentResponseCodeUnspecified = 0,
    INPayBillIntentResponseCodeReady,
    INPayBillIntentResponseCodeInProgress,
    INPayBillIntentResponseCodeSuccess,
    INPayBillIntentResponseCodeFailure,
    INPayBillIntentResponseCodeFailureRequiringAppLaunch,
    INPayBillIntentResponseCodeFailureCredentialsUnverified,
    INPayBillIntentResponseCodeFailureInsufficientFunds,
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INPayBillIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INPayBillIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INPayBillIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAccount *fromAccount;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INBillDetails *billDetails;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAmount *transactionAmount;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *transactionScheduledDate;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *transactionNote;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPersonHandle.h
//
//  INPersonHandle.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INPersonHandleLabel.h>

typedef NS_ENUM(NSInteger, INPersonHandleType) {
    INPersonHandleTypeUnknown = 0,
    INPersonHandleTypeEmailAddress,
    INPersonHandleTypePhoneNumber,
} API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INPersonHandle : NSObject <NSCopying, NSSecureCoding>

@property (readonly, nullable, copy, NS_NONATOMIC_IOSONLY) NSString *value;
@property (readonly, NS_NONATOMIC_IOSONLY) INPersonHandleType type;
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) INPersonHandleLabel label API_AVAILABLE(ios(10.2), macosx(10.12.2));

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithValue:(nullable NSString *)value type:(INPersonHandleType)type label:(nullable INPersonHandleLabel)label NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(10.2), macosx(10.12.2));
- (instancetype)initWithValue:(nullable NSString *)value type:(INPersonHandleType)type;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSendRideFeedbackIntent.h
//
//  INSendRideFeedbackIntent.h
//  Intents
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>

@class INSendRideFeedbackIntentResponse, INCurrencyAmount;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0))
API_UNAVAILABLE(watchos, macos)
@interface INSendRideFeedbackIntent : INIntent

- (id)init NS_UNAVAILABLE;

- (instancetype)initWithRideIdentifier:(NSString *)rideIdentifier NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *rideIdentifier; // Specifies the identifier of the ride to send feedback for.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *rating; // Will be between 0 and 10 inclusive.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *tip;

@end

/*!
 @abstract Protocol to declare support for handling an INSendRideFeedbackIntent. By implementing this protocol, a class can provide logic for confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The handling method is always called last, after confirming the intent.
 */

API_AVAILABLE(ios(11.0))
API_UNAVAILABLE(watchos, macos)
@protocol INSendRideFeedbackIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSendRideFeedbackIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.
 
 @param  sendRideFeedbackintent The input intent
 @param  completion The response handling block takes a INSendRideFeedbackIntentResponse containing the details of the result of having executed the intent
 
 @see  INSendRideFeedbackIntentResponse
 */

- (void)handleSendRideFeedback:(INSendRideFeedbackIntent *)sendRideFeedbackintent
                    completion:(void (^)(INSendRideFeedbackIntentResponse *response))completion NS_SWIFT_NAME(handle(sendRideFeedback:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will not allow calling of the handle method.
 
 @param  sendRideFeedbackIntent The input intent
 @param  completion The response block contains an INSendRideFeedbackIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.
 
 @see INSendRideFeedbackIntentResponse
 
 */

- (void)confirmSendRideFeedback:(INSendRideFeedbackIntent *)sendRideFeedbackIntent
                     completion:(void (^)(INSendRideFeedbackIntentResponse *response))completion NS_SWIFT_NAME(confirm(sendRideFeedback:completion:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSearchForBillsIntentResponse.h
//
//  INSearchForBillsIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INBillDetails;

typedef NS_ENUM(NSInteger, INSearchForBillsIntentResponseCode) {
    INSearchForBillsIntentResponseCodeUnspecified = 0,
    INSearchForBillsIntentResponseCodeReady,
    INSearchForBillsIntentResponseCodeInProgress,
    INSearchForBillsIntentResponseCodeSuccess,
    INSearchForBillsIntentResponseCodeFailure,
    INSearchForBillsIntentResponseCodeFailureRequiringAppLaunch,
    INSearchForBillsIntentResponseCodeFailureCredentialsUnverified,
    INSearchForBillsIntentResponseCodeFailureBillNotFound,
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INSearchForBillsIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSearchForBillsIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSearchForBillsIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INBillDetails *> *bills;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetAudioSourceInCarIntent.h
//
//  INSetAudioSourceInCarIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarAudioSource.h>
#import <Intents/INRelativeReference.h>

@class INCarAudioSourceResolutionResult;
@class INRelativeReferenceResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INSetAudioSourceInCarIntent : INIntent

- (instancetype)initWithAudioSource:(INCarAudioSource)audioSource
       relativeAudioSourceReference:(INRelativeReference)relativeAudioSourceReference NS_DESIGNATED_INITIALIZER;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCarAudioSource audioSource;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INRelativeReference relativeAudioSourceReference;

@end

@class INSetAudioSourceInCarIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSetAudioSourceInCarIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@protocol INSetAudioSourceInCarIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSetAudioSourceInCarIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSetAudioSourceInCarIntentResponse containing the details of the result of having executed the intent

 @see  INSetAudioSourceInCarIntentResponse
 */

- (void)handleSetAudioSourceInCar:(INSetAudioSourceInCarIntent *)intent
                       completion:(void (^)(INSetAudioSourceInCarIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSetAudioSourceInCarIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetAudioSourceInCarIntentResponse
 */

- (void)confirmSetAudioSourceInCar:(INSetAudioSourceInCarIntent *)intent
                        completion:(void (^)(INSetAudioSourceInCarIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveAudioSourceForSetAudioSourceInCar:(INSetAudioSourceInCarIntent *)intent
                    withCompletion:(void (^)(INCarAudioSourceResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAudioSource(for:with:));

- (void)resolveRelativeAudioSourceReferenceForSetAudioSourceInCar:(INSetAudioSourceInCarIntent *)intent
                    withCompletion:(void (^)(INRelativeReferenceResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRelativeAudioSourceReference(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INLocationSearchTypeResolutionResult.h
//
//  INLocationSearchTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INLocationSearchType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INLocationSearchTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INLocationSearchType. The resolvedValue can be different than the original INLocationSearchType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedLocationSearchType:(INLocationSearchType)resolvedLocationSearchType NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithLocationSearchTypeToConfirm:(INLocationSearchType)locationSearchTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INExtension.h
//
//  INExtension.h
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INIntentHandlerProviding.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INExtension : NSObject <INIntentHandlerProviding>
@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INNoteContentType.h
//
//  INNoteContentType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INNoteContentType_h
#define INNoteContentType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INNoteContentType) {
    INNoteContentTypeUnknown = 0,
    INNoteContentTypeText,
    INNoteContentTypeImage,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

#endif // INNoteContentType_h
// ==========  Intents.framework/Headers/INCreateNoteIntent.h
//
//  INCreateNoteIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INNoteContent;
@class INNoteContentResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INCreateNoteIntent : INIntent

- (instancetype)initWithTitle:(nullable INSpeakableString *)title
                      content:(nullable INNoteContent *)content
                    groupName:(nullable INSpeakableString *)groupName NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *title;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INNoteContent *content;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *groupName;

@end

@class INCreateNoteIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INCreateNoteIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@protocol INCreateNoteIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INCreateNoteIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INCreateNoteIntentResponse containing the details of the result of having executed the intent

 @see  INCreateNoteIntentResponse
 */

- (void)handleCreateNote:(INCreateNoteIntent *)intent
              completion:(void (^)(INCreateNoteIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INCreateNoteIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INCreateNoteIntentResponse
 */

- (void)confirmCreateNote:(INCreateNoteIntent *)intent
               completion:(void (^)(INCreateNoteIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveTitleForCreateNote:(INCreateNoteIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTitle(for:with:));

- (void)resolveContentForCreateNote:(INCreateNoteIntent *)intent
                    withCompletion:(void (^)(INNoteContentResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveContent(for:with:));

- (void)resolveGroupNameForCreateNote:(INCreateNoteIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveGroupName(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCancelWorkoutIntent.h
//
//  INCancelWorkoutIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INCancelWorkoutIntent : INIntent

// Designated initializer. The `workoutName` can use `INWorkoutNameIdentifier` as its `identifier` parameter.
- (instancetype)initWithWorkoutName:(nullable INSpeakableString *)workoutName NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *workoutName;

@end

@class INCancelWorkoutIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INCancelWorkoutIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INCancelWorkoutIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INCancelWorkoutIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INCancelWorkoutIntentResponse containing the details of the result of having executed the intent

 @see  INCancelWorkoutIntentResponse
 */

- (void)handleCancelWorkout:(INCancelWorkoutIntent *)intent
                 completion:(void (^)(INCancelWorkoutIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INCancelWorkoutIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INCancelWorkoutIntentResponse
 */

- (void)confirmCancelWorkout:(INCancelWorkoutIntent *)intent
                  completion:(void (^)(INCancelWorkoutIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveWorkoutNameForCancelWorkout:(INCancelWorkoutIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutName(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPaymentStatus.h
//
//  INPaymentStatus.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INPaymentStatus_h
#define INPaymentStatus_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INPaymentStatus) {
    INPaymentStatusUnknown = 0,
    INPaymentStatusPending,
    INPaymentStatusCompleted,
    INPaymentStatusCanceled,
    INPaymentStatusFailed,
    INPaymentStatusUnpaid,
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

#endif // INPaymentStatus_h
// ==========  Intents.framework/Headers/INMediaItem.h
//
//  INMediaItem.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INMediaItemType.h>

@class INImage;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), watchos(5.0))
API_UNAVAILABLE(macosx)
@interface INMediaItem : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                             title:(nullable NSString *)title
                              type:(INMediaItemType)type
                           artwork:(nullable INImage *)artwork NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *title;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INMediaItemType type;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INImage *artwork;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPerson+SiriAdditions.h
//
//  INPerson+SiriAdditions.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INPerson.h>

#import <Intents/INSpeakable.h>

NS_ASSUME_NONNULL_BEGIN

@interface INPerson (SiriAdditions) <INSpeakable>

// This property is filled in with what Siri thinks are close matches to what the user said
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *siriMatches API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macosx);

// This property is set to YES when the user says things like "Search for messages from me", etc.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) BOOL isMe API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INTemporalEventTriggerResolutionResult.h
//
//  INTemporalEventTriggerResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INTemporalEventTrigger;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INTemporalEventTriggerResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INTemporalEventTrigger. The resolvedTemporalEventTrigger can be different than the original INTemporalEventTrigger. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedTemporalEventTrigger:(INTemporalEventTrigger *)resolvedTemporalEventTrigger NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INTemporalEventTrigger.
+ (instancetype)disambiguationWithTemporalEventTriggersToDisambiguate:(NSArray<INTemporalEventTrigger *> *)temporalEventTriggersToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the temporalEventTrigger with which the user wants to continue.
+ (instancetype)confirmationRequiredWithTemporalEventTriggerToConfirm:(nullable INTemporalEventTrigger *)temporalEventTriggerToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetTaskAttributeIntentResponse.h
//
//  INSetTaskAttributeIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INTask;

typedef NS_ENUM(NSInteger, INSetTaskAttributeIntentResponseCode) {
    INSetTaskAttributeIntentResponseCodeUnspecified = 0,
    INSetTaskAttributeIntentResponseCodeReady,
    INSetTaskAttributeIntentResponseCodeInProgress,
    INSetTaskAttributeIntentResponseCodeSuccess,
    INSetTaskAttributeIntentResponseCodeFailure,
    INSetTaskAttributeIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INSetTaskAttributeIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSetTaskAttributeIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSetTaskAttributeIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INTask *modifiedTask;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRideFeedbackTypeOptions.h
//
//  INRideFeedbackTypeOptions.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INRideFeedbackTypeOptions_h
#define INRideFeedbackTypeOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INRideFeedbackTypeOptions) {
    INRideFeedbackTypeOptionRate = (1UL << 0),
    INRideFeedbackTypeOptionTip = (1UL << 1),
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

#endif // INRideFeedbackTypeOptions_h
// ==========  Intents.framework/Headers/INTaskStatus.h
//
//  INTaskStatus.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INTaskStatus_h
#define INTaskStatus_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INTaskStatus) {
    INTaskStatusUnknown = 0,
    INTaskStatusNotCompleted,
    INTaskStatusCompleted,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

#endif // INTaskStatus_h
// ==========  Intents.framework/Headers/INAddTasksIntent.h
//
//  INAddTasksIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INSpatialEventTrigger;
@class INSpatialEventTriggerResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;
@class INTaskList;
@class INTaskListResolutionResult;
@class INTemporalEventTrigger;
@class INTemporalEventTriggerResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INAddTasksIntent : INIntent

- (instancetype)initWithTargetTaskList:(nullable INTaskList *)targetTaskList
                            taskTitles:(nullable NSArray<INSpeakableString *> *)taskTitles
                   spatialEventTrigger:(nullable INSpatialEventTrigger *)spatialEventTrigger
                  temporalEventTrigger:(nullable INTemporalEventTrigger *)temporalEventTrigger NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INTaskList *targetTaskList;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INSpeakableString *> *taskTitles;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpatialEventTrigger *spatialEventTrigger;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INTemporalEventTrigger *temporalEventTrigger;

@end

@class INAddTasksIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INAddTasksIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@protocol INAddTasksIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INAddTasksIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INAddTasksIntentResponse containing the details of the result of having executed the intent

 @see  INAddTasksIntentResponse
 */

- (void)handleAddTasks:(INAddTasksIntent *)intent
            completion:(void (^)(INAddTasksIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INAddTasksIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INAddTasksIntentResponse
 */

- (void)confirmAddTasks:(INAddTasksIntent *)intent
             completion:(void (^)(INAddTasksIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveTargetTaskListForAddTasks:(INAddTasksIntent *)intent
                    withCompletion:(void (^)(INTaskListResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTargetTaskList(for:with:));

- (void)resolveTaskTitlesForAddTasks:(INAddTasksIntent *)intent
                    withCompletion:(void (^)(NSArray<INSpeakableStringResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveTaskTitles(for:with:));

- (void)resolveSpatialEventTriggerForAddTasks:(INAddTasksIntent *)intent
                    withCompletion:(void (^)(INSpatialEventTriggerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveSpatialEventTrigger(for:with:));

- (void)resolveTemporalEventTriggerForAddTasks:(INAddTasksIntent *)intent
                    withCompletion:(void (^)(INTemporalEventTriggerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTemporalEventTrigger(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INAddTasksIntentResponse.h
//
//  INAddTasksIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INTask;
@class INTaskList;

typedef NS_ENUM(NSInteger, INAddTasksIntentResponseCode) {
    INAddTasksIntentResponseCodeUnspecified = 0,
    INAddTasksIntentResponseCodeReady,
    INAddTasksIntentResponseCodeInProgress,
    INAddTasksIntentResponseCodeSuccess,
    INAddTasksIntentResponseCodeFailure,
    INAddTasksIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INAddTasksIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INAddTasksIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INAddTasksIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INTaskList *modifiedTaskList;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INTask *> *addedTasks;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INResumeWorkoutIntentResponse.h
//
//  INResumeWorkoutIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INResumeWorkoutIntentResponseCode) {
    INResumeWorkoutIntentResponseCodeUnspecified = 0,
    INResumeWorkoutIntentResponseCodeReady,
    INResumeWorkoutIntentResponseCodeContinueInApp API_AVAILABLE(watchos(3.2)) API_DEPRECATED("INResumeWorkoutIntentResponseCodeContinueInApp is deprecated on iOS. Please use INResumeWorkoutIntentResponseCodeHandleInApp instead", ios(10.0, 11.0)),
    INResumeWorkoutIntentResponseCodeFailure,
    INResumeWorkoutIntentResponseCodeFailureRequiringAppLaunch,
    INResumeWorkoutIntentResponseCodeFailureNoMatchingWorkout,
    INResumeWorkoutIntentResponseCodeHandleInApp API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos),
    INResumeWorkoutIntentResponseCodeSuccess NS_EXTENSION_UNAVAILABLE("INResumeWorkoutIntentResponseCodeSuccess is not available to extensions. This can only be returned from the app.") API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos),
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INResumeWorkoutIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INResumeWorkoutIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INResumeWorkoutIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INNotebookItemTypeResolutionResult.h
//
//  INNotebookItemTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INNotebookItemType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INNotebookItemTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INNotebookItemType. The resolvedValue can be different than the original INNotebookItemType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedNotebookItemType:(INNotebookItemType)resolvedNotebookItemType NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided values.
+ (instancetype)disambiguationWithNotebookItemTypesToDisambiguate:(NSArray<NSNumber *> *)notebookItemTypesToDisambiguate NS_REFINED_FOR_SWIFT;

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithNotebookItemTypeToConfirm:(INNotebookItemType)notebookItemTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRadioType.h
//
//  INRadioType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INRadioType_h
#define INRadioType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INRadioType) {
    INRadioTypeUnknown = 0,
    INRadioTypeAM,
    INRadioTypeFM,
    INRadioTypeHD,
    INRadioTypeSatellite,
    INRadioTypeDAB,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

#endif // INRadioType_h
// ==========  Intents.framework/Headers/INPaymentAccount.h
//
//  INPaymentAccount.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INAccountType.h>

@class INBalanceAmount;
@class INSpeakableString;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INPaymentAccount : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithNickname:(INSpeakableString *)nickname
                          number:(nullable NSString *)number
                     accountType:(INAccountType)accountType
                organizationName:(nullable INSpeakableString *)organizationName
                         balance:(nullable INBalanceAmount *)balance
                secondaryBalance:(nullable INBalanceAmount *)secondaryBalance NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(11.0), watchos(4.0));

- (nullable instancetype)initWithNickname:(INSpeakableString *)nickname
                                   number:(nullable NSString *)number
                              accountType:(INAccountType)accountType
                         organizationName:(nullable INSpeakableString *)organizationName API_DEPRECATED("Please use 'initWithNickname:number:accountType:organizationName:balance:secondaryBalance:' instead", ios(10.3, 11.0), watchos(3.2, 4.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *nickname;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *accountNumber;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INAccountType accountType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *organizationName;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INBalanceAmount *balance API_AVAILABLE(ios(11.0), watchos(4.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INBalanceAmount *secondaryBalance API_AVAILABLE(ios(11.0), watchos(4.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INIntentIdentifiers.h
//
//  INIntentIdentifiers.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/IntentsDefines.h>

// Identifier for INStartAudioCallIntent class.
INTENTS_EXTERN NSString *const INStartAudioCallIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));

// Identifier for INStartVideoCallIntent class.
INTENTS_EXTERN NSString *const INStartVideoCallIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos);

// Identifier for INSearchCallHistoryIntent class.
INTENTS_EXTERN NSString *const INSearchCallHistoryIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));

// Identifier for INSetAudioSourceInCarIntent class.
INTENTS_EXTERN NSString *const INSetAudioSourceInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos);

// Identifier for INSetClimateSettingsInCarIntent class.
INTENTS_EXTERN NSString *const INSetClimateSettingsInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos);

// Identifier for INSetDefrosterSettingsInCarIntent class.
INTENTS_EXTERN NSString *const INSetDefrosterSettingsInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos);

// Identifier for INSetSeatSettingsInCarIntent class.
INTENTS_EXTERN NSString *const INSetSeatSettingsInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos);

// Identifier for INSetProfileInCarIntent class.
INTENTS_EXTERN NSString *const INSetProfileInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos);

// Identifier for INSaveProfileInCarIntent class.
INTENTS_EXTERN NSString *const INSaveProfileInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos);

// Identifier for INStartWorkoutIntent class.
INTENTS_EXTERN NSString *const INStartWorkoutIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INPauseWorkoutIntent class.
INTENTS_EXTERN NSString *const INPauseWorkoutIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INEndWorkoutIntent class.
INTENTS_EXTERN NSString *const INEndWorkoutIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INCancelWorkoutIntent class.
INTENTS_EXTERN NSString *const INCancelWorkoutIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INResumeWorkoutIntent class.
INTENTS_EXTERN NSString *const INResumeWorkoutIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INSetRadioStationIntent class.
INTENTS_EXTERN NSString *const INSetRadioStationIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos);

// Identifier for INSendMessageIntent class.
INTENTS_EXTERN NSString *const INSendMessageIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));

// Identifier for INSearchForMessagesIntent class.
INTENTS_EXTERN NSString *const INSearchForMessagesIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));

// Identifier for INSetMessageAttributeIntent class.
INTENTS_EXTERN NSString *const INSetMessageAttributeIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos);

// Identifier for INSendPaymentIntent class.
INTENTS_EXTERN NSString *const INSendPaymentIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INRequestPaymentIntent class.
INTENTS_EXTERN NSString *const INRequestPaymentIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INSearchForPhotosIntent class.
INTENTS_EXTERN NSString *const INSearchForPhotosIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INStartPhotoPlaybackIntent class.
INTENTS_EXTERN NSString *const INStartPhotoPlaybackIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INListRideOptionsIntent class.
INTENTS_EXTERN NSString *const INListRideOptionsIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INRequestRideIntent class.
INTENTS_EXTERN NSString *const INRequestRideIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

// Identifier for INGetRideStatusIntent class.
INTENTS_EXTERN NSString *const INGetRideStatusIntentIdentifier API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);
// ==========  Intents.framework/Headers/INBillTypeResolutionResult.h
//
//  INBillTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INBillType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INBillTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INBillType. The resolvedValue can be different than the original INBillType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedBillType:(INBillType)resolvedBillType NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INBillType)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedBillType:", ios(10.3, 11.0), watchos(3.2, 4.0));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithBillTypeToConfirm:(INBillType)billTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INBillType)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithBillTypeToConfirm:", ios(10.3, 11.0), watchos(3.2, 4.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INListRideOptionsIntentResponse.h
//
//  INListRideOptionsIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INPaymentMethod;
@class INRideOption;

typedef NS_ENUM(NSInteger, INListRideOptionsIntentResponseCode) {
    INListRideOptionsIntentResponseCodeUnspecified = 0,
    INListRideOptionsIntentResponseCodeReady,
    INListRideOptionsIntentResponseCodeInProgress API_DEPRECATED("INListRideOptionsIntentResponseCodeInProgress is deprecated.", ios(10.0, 11.0), watchos(3.2, 4.0)),
    INListRideOptionsIntentResponseCodeSuccess,
    INListRideOptionsIntentResponseCodeFailure,
    INListRideOptionsIntentResponseCodeFailureRequiringAppLaunch,
    INListRideOptionsIntentResponseCodeFailureRequiringAppLaunchMustVerifyCredentials,
    INListRideOptionsIntentResponseCodeFailureRequiringAppLaunchNoServiceInArea,
    INListRideOptionsIntentResponseCodeFailureRequiringAppLaunchServiceTemporarilyUnavailable,
    INListRideOptionsIntentResponseCodeFailureRequiringAppLaunchPreviousRideNeedsCompletion,
    INListRideOptionsIntentResponseCodeFailurePreviousRideNeedsFeedback API_AVAILABLE(ios(11.0), watchos(4.0)),
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INListRideOptionsIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INListRideOptionsIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INListRideOptionsIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INRideOption *> *rideOptions;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPaymentMethod *> *paymentMethods;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *expirationDate;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSearchCallHistoryIntentResponse.h
//
//  INSearchCallHistoryIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INCallRecord;

typedef NS_ENUM(NSInteger, INSearchCallHistoryIntentResponseCode) {
    INSearchCallHistoryIntentResponseCodeUnspecified = 0,
    INSearchCallHistoryIntentResponseCodeReady,
    INSearchCallHistoryIntentResponseCodeContinueInApp,
    INSearchCallHistoryIntentResponseCodeFailure,
    INSearchCallHistoryIntentResponseCodeFailureRequiringAppLaunch,
    INSearchCallHistoryIntentResponseCodeFailureAppConfigurationRequired,
    INSearchCallHistoryIntentResponseCodeInProgress API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13)),
    INSearchCallHistoryIntentResponseCodeSuccess API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13)),
} API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12));

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12))
@interface INSearchCallHistoryIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSearchCallHistoryIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSearchCallHistoryIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INCallRecord *> *callRecords API_AVAILABLE(ios(11.0), macosx(10.13));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCallRecordTypeResolutionResult.h
//
//  INCallRecordTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCallRecordType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12))
@interface INCallRecordTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INCallRecordType. The resolvedValue can be different than the original INCallRecordType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedCallRecordType:(INCallRecordType)resolvedCallRecordType NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INCallRecordType)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedCallRecordType:", ios(10.0, 11.0), watchos(3.2, 4.0), macos(10.12, 10.13));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithCallRecordTypeToConfirm:(INCallRecordType)callRecordTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INCallRecordType)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithCallRecordTypeToConfirm:", ios(10.0, 11.0), watchos(3.2, 4.0), macos(10.12, 10.13));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSendPaymentIntentResponse.h
//
//  INSendPaymentIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INPaymentRecord;

typedef NS_ENUM(NSInteger, INSendPaymentIntentResponseCode) {
    INSendPaymentIntentResponseCodeUnspecified = 0,
    INSendPaymentIntentResponseCodeReady,
    INSendPaymentIntentResponseCodeInProgress,
    INSendPaymentIntentResponseCodeSuccess,
    INSendPaymentIntentResponseCodeFailure,
    INSendPaymentIntentResponseCodeFailureRequiringAppLaunch,
    INSendPaymentIntentResponseCodeFailureCredentialsUnverified,
    INSendPaymentIntentResponseCodeFailurePaymentsAmountBelowMinimum,
    INSendPaymentIntentResponseCodeFailurePaymentsAmountAboveMaximum,
    INSendPaymentIntentResponseCodeFailurePaymentsCurrencyUnsupported,
    INSendPaymentIntentResponseCodeFailureInsufficientFunds,
    INSendPaymentIntentResponseCodeFailureNoBankAccount,
    INSendPaymentIntentResponseCodeFailureNotEligible API_AVAILABLE(ios(11.0), watchos(4.0)),
    INSendPaymentIntentResponseCodeFailureTermsAndConditionsAcceptanceRequired API_AVAILABLE(ios(11.1), watchos(4.1)),
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INSendPaymentIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSendPaymentIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSendPaymentIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentRecord *paymentRecord;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSaveProfileInCarIntent_Deprecated.h
//
//  INSaveProfileInCarIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INSaveProfileInCarIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSaveProfileInCarIntent (Deprecated)

- (instancetype)initWithProfileNumber:(nullable NSNumber *)profileNumber
                         profileLabel:(nullable NSString *)profileLabel API_DEPRECATED("Use `-initWithProfileNumber:profileName:` method instead.", ios(10.0, 10.2)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *profileLabel API_DEPRECATED("Use `profileName` property instead.", ios(10.0, 10.2)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetClimateSettingsInCarIntent_Deprecated.h
//
//  INSetClimateSettingsInCarIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2018 Apple Inc. All rights reserved.
//

#import <Intents/INSetClimateSettingsInCarIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSetClimateSettingsInCarIntent (Deprecated)

- (instancetype)initWithEnableFan:(nullable NSNumber *)enableFan
             enableAirConditioner:(nullable NSNumber *)enableAirConditioner
             enableClimateControl:(nullable NSNumber *)enableClimateControl
                   enableAutoMode:(nullable NSNumber *)enableAutoMode
               airCirculationMode:(INCarAirCirculationMode)airCirculationMode
                    fanSpeedIndex:(nullable NSNumber *)fanSpeedIndex
               fanSpeedPercentage:(nullable NSNumber *)fanSpeedPercentage
          relativeFanSpeedSetting:(INRelativeSetting)relativeFanSpeedSetting
                      temperature:(nullable NSMeasurement<NSUnitTemperature *> *)temperature
       relativeTemperatureSetting:(INRelativeSetting)relativeTemperatureSetting
                      climateZone:(INCarSeat)climateZone API_DEPRECATED_WITH_REPLACEMENT("-initWithEnableFan:enableAirConditioner:enableClimateControl:enableAutoMode:airCirculationMode:fanSpeedIndex:fanSpeedPercentage:relativeFanSpeedSetting:temperature:relativeTemperatureSetting:", ios(10.0, 12.0)) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INBalanceTypeResolutionResult.h
//
//  INBalanceTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INBalanceType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INBalanceTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INBalanceType. The resolvedValue can be different than the original INBalanceType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedBalanceType:(INBalanceType)resolvedBalanceType NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithBalanceTypeToConfirm:(INBalanceType)balanceTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSearchCallHistoryIntent.h
//
//  INSearchCallHistoryIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCallCapabilityOptions.h>
#import <Intents/INCallRecordType.h>
#import <Intents/INCallRecordTypeOptions.h>

@class INBooleanResolutionResult;
@class INCallRecordTypeOptionsResolutionResult;
@class INCallRecordTypeResolutionResult;
@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INPerson;
@class INPersonResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12))
@interface INSearchCallHistoryIntent : INIntent

- (instancetype)initWithDateCreated:(nullable INDateComponentsRange *)dateCreated
                          recipient:(nullable INPerson *)recipient
                   callCapabilities:(INCallCapabilityOptions)callCapabilities
                          callTypes:(INCallRecordTypeOptions)callTypes
                             unseen:(nullable NSNumber *)unseen NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

// Date of the call to search for in the call history.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dateCreated;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *recipient;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallCapabilityOptions callCapabilities;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallRecordTypeOptions callTypes API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *unseen NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

@end

@class INSearchCallHistoryIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSearchCallHistoryIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12))
@protocol INSearchCallHistoryIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSearchCallHistoryIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSearchCallHistoryIntentResponse containing the details of the result of having executed the intent

 @see  INSearchCallHistoryIntentResponse
 */

- (void)handleSearchCallHistory:(INSearchCallHistoryIntent *)intent
                     completion:(void (^)(INSearchCallHistoryIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSearchCallHistoryIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSearchCallHistoryIntentResponse
 */

- (void)confirmSearchCallHistory:(INSearchCallHistoryIntent *)intent
                      completion:(void (^)(INSearchCallHistoryIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveCallTypeForSearchCallHistory:(INSearchCallHistoryIntent *)intent
                    withCompletion:(void (^)(INCallRecordTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCallType(for:with:)) API_DEPRECATED("resolveCallTypeForSearchCallHistory:withCompletion: is deprecated. Use resolveCallTypesForSearchCallHistory:withCompletion: instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

- (void)resolveDateCreatedForSearchCallHistory:(INSearchCallHistoryIntent *)intent
                    withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDateCreated(for:with:));

- (void)resolveRecipientForSearchCallHistory:(INSearchCallHistoryIntent *)intent
                    withCompletion:(void (^)(INPersonResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRecipient(for:with:));

- (void)resolveCallTypesForSearchCallHistory:(INSearchCallHistoryIntent *)intent
                    withCompletion:(void (^)(INCallRecordTypeOptionsResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCallTypes(for:with:)) API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

- (void)resolveUnseenForSearchCallHistory:(INSearchCallHistoryIntent *)intent
                    withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveUnseen(for:with:)) API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INActivateCarSignalIntentResponse.h
//
//  INActivateCarSignalIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

#import <Intents/INCarSignalOptions.h>

typedef NS_ENUM(NSInteger, INActivateCarSignalIntentResponseCode) {
    INActivateCarSignalIntentResponseCodeUnspecified = 0,
    INActivateCarSignalIntentResponseCodeReady,
    INActivateCarSignalIntentResponseCodeInProgress,
    INActivateCarSignalIntentResponseCodeSuccess,
    INActivateCarSignalIntentResponseCodeFailure,
    INActivateCarSignalIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INActivateCarSignalIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INActivateCarSignalIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INActivateCarSignalIntentResponseCode code;

@property (readwrite, assign, NS_NONATOMIC_IOSONLY) INCarSignalOptions signals;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetSeatSettingsInCarIntentResponse.h
//
//  INSetSeatSettingsInCarIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSetSeatSettingsInCarIntentResponseCode) {
    INSetSeatSettingsInCarIntentResponseCodeUnspecified = 0,
    INSetSeatSettingsInCarIntentResponseCodeReady,
    INSetSeatSettingsInCarIntentResponseCodeInProgress,
    INSetSeatSettingsInCarIntentResponseCodeSuccess,
    INSetSeatSettingsInCarIntentResponseCodeFailure,
    INSetSeatSettingsInCarIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos, macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INSetSeatSettingsInCarIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSetSeatSettingsInCarIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSetSeatSettingsInCarIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INGetAvailableRestaurantReservationBookingDefaultsIntent.h
//
//  INGetAvailableRestaurantReservationBookingDefaultsIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>
#import <Intents/INRestaurant.h>
#import <Intents/INRestaurantResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INGetAvailableRestaurantReservationBookingDefaultsIntent : INIntent

- (instancetype)initWithRestaurant:(nullable INRestaurant *)restaurant API_AVAILABLE(ios(11.0));

@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurant *restaurant; // an optional restaurant that the extension may or may not use to tailor reservation defaults

@end

@class INGetAvailableRestaurantReservationBookingDefaultsIntentResponse;

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@protocol INGetAvailableRestaurantReservationBookingDefaultsIntentHandling <NSObject>

/*!
 @abstract Handling method - Execute the task represented by the INGetAvailableRestaurantReservationBookingDefaultsIntent that's passed in
 @discussion This method is called to actually execute the intent, the app must return a response for this intent and an NSUserActivity capturing the state that the app must be restored to at the end of handling this intent
 
 @param  intent The input intent
 @param  completion The response handling block to invoke with the response to handling the intent.
 
 @see  INGetAvailableRestaurantReservationBookingDefaultsIntentResponse
 
 */

- (void)handleGetAvailableRestaurantReservationBookingDefaults:(INGetAvailableRestaurantReservationBookingDefaultsIntent *)intent completion:(void (^)(INGetAvailableRestaurantReservationBookingDefaultsIntentResponse *response))completion NS_SWIFT_NAME(handle(getAvailableRestaurantReservationBookingDefaults:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.
 
 @param  intent The input intent
 @param  completion The response block contains an INGetAvailableRestaurantReservationBookingDefaultsIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.
 
 @see INGetAvailableRestaurantReservationBookingDefaultsIntentResponse
 
 */

- (void)confirmGetAvailableRestaurantReservationBookingDefaults:(INGetAvailableRestaurantReservationBookingDefaultsIntent *)intent completion:(void (^)(INGetAvailableRestaurantReservationBookingDefaultsIntentResponse *response))completion NS_SWIFT_NAME(confirm(getAvailableRestaurantReservationBookingDefaults:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.
 
 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved
 
 @see INGetAvailableRestaurantReservationBookingDefaultsIntentResponse
 
 */

- (void)resolveRestaurantForGetAvailableRestaurantReservationBookingDefaults:(INGetAvailableRestaurantReservationBookingDefaultsIntent *)intent withCompletion:(void(^)(INRestaurantResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRestaurant(for:completion:));

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INBillPayee.h
//
//  INBillPayee.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INSpeakableString;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INBillPayee : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithNickname:(INSpeakableString *)nickname
                                   number:(nullable NSString *)number
                         organizationName:(nullable INSpeakableString *)organizationName NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *nickname;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *accountNumber;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *organizationName;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRecurrenceRule.h
//
//  INRecurrenceRule.h
//  Intents
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INRecurrenceFrequency.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0))
@interface INRecurrenceRule : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithInterval:(NSUInteger)interval frequency:(INRecurrenceFrequency)frequency;

@property (readonly) NSUInteger interval;
@property (readonly) INRecurrenceFrequency frequency;

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPerson.h
//
//  INPerson.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INPersonRelationship.h>

@class INImage;
@class INPersonHandle;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INPerson : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithPersonHandle:(INPersonHandle *)personHandle
                      nameComponents:(nullable NSPersonNameComponents *)nameComponents
                         displayName:(nullable NSString *)displayName
                               image:(nullable INImage *)image
                   contactIdentifier:(nullable NSString *)contactIdentifier
                    customIdentifier:(nullable NSString *)customIdentifier;

- (instancetype)initWithPersonHandle:(INPersonHandle *)personHandle
                      nameComponents:(nullable NSPersonNameComponents *)nameComponents
                         displayName:(nullable NSString *)displayName
                               image:(nullable INImage *)image
                   contactIdentifier:(nullable NSString *)contactIdentifier
                    customIdentifier:(nullable NSString *)customIdentifier
                                isMe:(BOOL)isMe NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14));

// The identity of the person in the application
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPersonHandle *personHandle;

// Returns the person's name components if this was initialized with them
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSPersonNameComponents *nameComponents;

// This will return either the displayName if non-nil, else the formatted nameComponents, else the handle, else an empty string
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *displayName;

// Returns an image for the person.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INImage *image;

// Reference to this person, if present in the system's Contacts store
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *contactIdentifier;

// This property can be set to the app's identifier for this person
// It is also used as the vocabulary identifier for this person
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *customIdentifier;

// This person's relationship to the user
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPersonRelationship relationship API_AVAILABLE(ios(10.2), macosx(10.12.2));

@end

typedef NS_ENUM(NSInteger, INPersonSuggestionType) {
    INPersonSuggestionTypeNone API_AVAILABLE(macosx(10.14), ios(12.0), watchos(5.0)) = 0,
    INPersonSuggestionTypeSocialProfile,
    INPersonSuggestionTypeInstantMessageAddress
};

@interface INPerson (INInteraction)

// If your application has other representations for the person's handle, you can supply it for INInteraction donation
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPersonHandle *> *aliases;

// What Contact property this INInteraction donation should be suggested as when this person is matched to a contact in the system's Contacts store.
@property (readonly, NS_NONATOMIC_IOSONLY) INPersonSuggestionType suggestionType;

- (instancetype)initWithPersonHandle:(INPersonHandle *)personHandle
                      nameComponents:(nullable NSPersonNameComponents *)nameComponents
                         displayName:(nullable NSString *)displayName
                               image:(nullable INImage *)image
                   contactIdentifier:(nullable NSString *)contactIdentifier
                    customIdentifier:(nullable NSString *)customIdentifier
                             aliases:(nullable NSArray<INPersonHandle *> *)aliases
                      suggestionType:(INPersonSuggestionType)suggestionType;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INStartVideoCallIntent.h
//
//  INStartVideoCallIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INPerson;
@class INPersonResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), macosx(10.12))
API_UNAVAILABLE(watchos)
@interface INStartVideoCallIntent : INIntent

- (instancetype)initWithContacts:(nullable NSArray<INPerson *> *)contacts NS_DESIGNATED_INITIALIZER;

// Recipients of the video call.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *contacts;

@end

@class INStartVideoCallIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INStartVideoCallIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), macosx(10.12))
API_UNAVAILABLE(watchos)
@protocol INStartVideoCallIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INStartVideoCallIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INStartVideoCallIntentResponse containing the details of the result of having executed the intent

 @see  INStartVideoCallIntentResponse
 */

- (void)handleStartVideoCall:(INStartVideoCallIntent *)intent
                  completion:(void (^)(INStartVideoCallIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INStartVideoCallIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INStartVideoCallIntentResponse
 */

- (void)confirmStartVideoCall:(INStartVideoCallIntent *)intent
                   completion:(void (^)(INStartVideoCallIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveContactsForStartVideoCall:(INStartVideoCallIntent *)intent
                    withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveContacts(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INDateComponentsRange.h
//
//  INDateComponentsRange.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class EKRecurrenceRule;
@class INRecurrenceRule;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INDateComponentsRange : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithStartDateComponents:(nullable NSDateComponents *)startDateComponents
                          endDateComponents:(nullable NSDateComponents *)endDateComponents;

- (instancetype)initWithStartDateComponents:(nullable NSDateComponents *)startDateComponents
                          endDateComponents:(nullable NSDateComponents *)endDateComponents
                             recurrenceRule:(nullable INRecurrenceRule *)recurrenceRule NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

@property (copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *startDateComponents;

@property (copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *endDateComponents;

@property (copy, readonly, nullable, NS_NONATOMIC_IOSONLY) INRecurrenceRule *recurrenceRule API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

- (instancetype)initWithEKRecurrenceRule:(EKRecurrenceRule *)recurrenceRule API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));
- (nullable EKRecurrenceRule *)EKRecurrenceRule API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSearchForPhotosIntent.h
//
//  INSearchForPhotosIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INConditionalOperator.h>
#import <Intents/INPhotoAttributeOptions.h>

@class CLPlacemark;
@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INPerson;
@class INPersonResolutionResult;
@class INPlacemarkResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INSearchForPhotosIntent : INIntent

- (instancetype)initWithDateCreated:(nullable INDateComponentsRange *)dateCreated
                    locationCreated:(nullable CLPlacemark *)locationCreated
                          albumName:(nullable NSString *)albumName
                        searchTerms:(nullable NSArray<NSString *> *)searchTerms
                 includedAttributes:(INPhotoAttributeOptions)includedAttributes
                 excludedAttributes:(INPhotoAttributeOptions)excludedAttributes
                      peopleInPhoto:(nullable NSArray<INPerson *> *)peopleInPhoto NS_DESIGNATED_INITIALIZER;

// Search for photos created in the specified date interval.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dateCreated;

// Search for photos taken at the specified location.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *locationCreated;

// Search for photos contained in albums matching this name.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *albumName;

// Search for photos with keywords, names, descriptions, etc. that match these search terms.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *searchTerms;

// Describes how to combine the contents of the searchTerm array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator searchTermsOperator;

// When specified, only match photos of the given types.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INPhotoAttributeOptions includedAttributes;

// When specified, do not match photos of the given types.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INPhotoAttributeOptions excludedAttributes;

// INPerson objects that should be present in the matched photos, dependent on the peopleInPhotoOperator.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *peopleInPhoto;

// Describes how to combine the contents of the peopleInPhoto array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator peopleInPhotoOperator;

@end

@class INSearchForPhotosIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSearchForPhotosIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INSearchForPhotosIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSearchForPhotosIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSearchForPhotosIntentResponse containing the details of the result of having executed the intent

 @see  INSearchForPhotosIntentResponse
 */

- (void)handleSearchForPhotos:(INSearchForPhotosIntent *)intent
                   completion:(void (^)(INSearchForPhotosIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSearchForPhotosIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSearchForPhotosIntentResponse
 */

- (void)confirmSearchForPhotos:(INSearchForPhotosIntent *)intent
                    completion:(void (^)(INSearchForPhotosIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveDateCreatedForSearchForPhotos:(INSearchForPhotosIntent *)intent
                    withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDateCreated(for:with:));

- (void)resolveLocationCreatedForSearchForPhotos:(INSearchForPhotosIntent *)intent
                    withCompletion:(void (^)(INPlacemarkResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveLocationCreated(for:with:));

- (void)resolveAlbumNameForSearchForPhotos:(INSearchForPhotosIntent *)intent
                    withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAlbumName(for:with:));

- (void)resolveSearchTermsForSearchForPhotos:(INSearchForPhotosIntent *)intent
                    withCompletion:(void (^)(NSArray<INStringResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveSearchTerms(for:with:)) API_AVAILABLE(ios(11.0), watchos(4.0));

- (void)resolvePeopleInPhotoForSearchForPhotos:(INSearchForPhotosIntent *)intent
                    withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolvePeopleInPhoto(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INGetUserCurrentRestaurantReservationBookingsIntent.h
//
//  INGetUserCurrentRestaurantReservationBookingsIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>
#import <Intents/INRestaurant.h>
#import <Intents/INRestaurantResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INGetUserCurrentRestaurantReservationBookingsIntent : INIntent <NSCopying>

- (instancetype)initWithRestaurant:(nullable INRestaurant *)restaurant
             reservationIdentifier:(nullable NSString *)reservationIdentifier
            maximumNumberOfResults:(nullable NSNumber *)maximumNumberOfResults
     earliestBookingDateForResults:(nullable NSDate *)earliestBookingDateForResults API_AVAILABLE(ios(11.0));

@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurant *restaurant; // optional filter to just reservations at restaurant
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *reservationIdentifier; // optional filter to reservation with exact ID

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *maximumNumberOfResults; // if the caller has a preferred maximum number of results, one can optionally be specified. a nil here leaves it up to the extension
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *earliestBookingDateForResults; // specifies the earliest booking date desired for results, including dates in the past

@end

@class INGetUserCurrentRestaurantReservationBookingsIntentResponse;

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@protocol INGetUserCurrentRestaurantReservationBookingsIntentHandling <NSObject>

/*!
 @abstract Handling method - Execute the task represented by the INGetUserCurrentRestaurantReservationBookingsIntent that's passed in
 @discussion This method is called to actually execute the intent, the app must return a response for this intent and an NSUserActivity capturing the state that the app must be restored to at the end of handling this intent
 
 @param  intent The input intent
 @param  completion The response handling block to invoke with the response to handling the intent.
 
 @see  INGetUserCurrentRestaurantReservationBookingsIntentResponse
 
 */

- (void)handleGetUserCurrentRestaurantReservationBookings:(INGetUserCurrentRestaurantReservationBookingsIntent *)intent completion:(void (^)(INGetUserCurrentRestaurantReservationBookingsIntentResponse *response))completion NS_SWIFT_NAME(handle(getUserCurrentRestaurantReservationBookings:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.
 
 @param  intent The input intent
 @param  completion The response block contains an INGetUserCurrentRestaurantReservationBookingsIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.
 
 @see INGetUserCurrentRestaurantReservationBookingsIntentResponse
 
 */

- (void)confirmGetUserCurrentRestaurantReservationBookings:(INGetUserCurrentRestaurantReservationBookingsIntent *)intent completion:(void (^)(INGetUserCurrentRestaurantReservationBookingsIntentResponse *response))completion NS_SWIFT_NAME(confirm(getUserCurrentRestaurantReservationBookings:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.
 
 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved
 
 @see INGetUserCurrentRestaurantReservationBookingsIntentResponse
 
 */

- (void)resolveRestaurantForGetUserCurrentRestaurantReservationBookings:(INGetUserCurrentRestaurantReservationBookingsIntent *)intent withCompletion:(void(^)(INRestaurantResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRestaurant(for:completion:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INActivateCarSignalIntent.h
//
//  INActivateCarSignalIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarSignalOptions.h>

@class INCarSignalOptionsResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INActivateCarSignalIntent : INIntent

- (instancetype)initWithCarName:(nullable INSpeakableString *)carName
                        signals:(INCarSignalOptions)signals NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *carName;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCarSignalOptions signals;

@end

@class INActivateCarSignalIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INActivateCarSignalIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INActivateCarSignalIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INActivateCarSignalIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INActivateCarSignalIntentResponse containing the details of the result of having executed the intent

 @see  INActivateCarSignalIntentResponse
 */

- (void)handleActivateCarSignal:(INActivateCarSignalIntent *)intent
                     completion:(void (^)(INActivateCarSignalIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INActivateCarSignalIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INActivateCarSignalIntentResponse
 */

- (void)confirmActivateCarSignal:(INActivateCarSignalIntent *)intent
                      completion:(void (^)(INActivateCarSignalIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveCarNameForActivateCarSignal:(INActivateCarSignalIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCarName(for:with:));

- (void)resolveSignalsForActivateCarSignal:(INActivateCarSignalIntent *)intent
                    withCompletion:(void (^)(INCarSignalOptionsResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveSignals(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPersonRelationship.h
//
//  INPersonRelationship.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NSString *INPersonRelationship NS_TYPED_EXTENSIBLE_ENUM;

INTENTS_EXTERN INPersonRelationship const INPersonRelationshipFather NS_SWIFT_NAME(INPersonRelationship.father) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipMother NS_SWIFT_NAME(INPersonRelationship.mother) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipParent NS_SWIFT_NAME(INPersonRelationship.parent) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipBrother NS_SWIFT_NAME(INPersonRelationship.brother) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipSister NS_SWIFT_NAME(INPersonRelationship.sister) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipChild NS_SWIFT_NAME(INPersonRelationship.child) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipFriend NS_SWIFT_NAME(INPersonRelationship.friend) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipSpouse NS_SWIFT_NAME(INPersonRelationship.spouse) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipPartner NS_SWIFT_NAME(INPersonRelationship.partner) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipAssistant NS_SWIFT_NAME(INPersonRelationship.assistant) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonRelationship const INPersonRelationshipManager NS_SWIFT_NAME(INPersonRelationship.manager) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
// ==========  Intents.framework/Headers/INRecurrenceFrequency.h
//
//  INRecurrenceFrequency.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INRecurrenceFrequency_h
#define INRecurrenceFrequency_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INRecurrenceFrequency) {
    INRecurrenceFrequencyUnknown = 0,
    INRecurrenceFrequencyMinute,
    INRecurrenceFrequencyHourly,
    INRecurrenceFrequencyDaily,
    INRecurrenceFrequencyWeekly,
    INRecurrenceFrequencyMonthly,
    INRecurrenceFrequencyYearly,
} API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

#endif // INRecurrenceFrequency_h
// ==========  Intents.framework/Headers/INMessageAttributeOptionsResolutionResult.h
//
//  INMessageAttributeOptionsResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INMessageAttributeOptions.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12))
@interface INMessageAttributeOptionsResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INMessageAttributeOptions. The resolvedValue can be different than the original INMessageAttributeOptions. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedMessageAttributeOptions:(INMessageAttributeOptions)resolvedMessageAttributeOptions NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INMessageAttributeOptions)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedMessageAttributeOptions:", ios(10.0, 11.0), watchos(3.2, 4.0), macos(10.12, 10.13));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithMessageAttributeOptionsToConfirm:(INMessageAttributeOptions)messageAttributeOptionsToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INMessageAttributeOptions)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithMessageAttributeOptionsToConfirm:", ios(10.0, 11.0), watchos(3.2, 4.0), macos(10.12, 10.13));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INWorkoutGoalUnitTypeResolutionResult.h
//
//  INWorkoutGoalUnitTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INWorkoutGoalUnitType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INWorkoutGoalUnitTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INWorkoutGoalUnitType. The resolvedValue can be different than the original INWorkoutGoalUnitType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedWorkoutGoalUnitType:(INWorkoutGoalUnitType)resolvedWorkoutGoalUnitType NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INWorkoutGoalUnitType)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedWorkoutGoalUnitType:", ios(10.0, 11.0), watchos(3.2, 4.0));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithWorkoutGoalUnitTypeToConfirm:(INWorkoutGoalUnitType)workoutGoalUnitTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INWorkoutGoalUnitType)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithWorkoutGoalUnitTypeToConfirm:", ios(10.0, 11.0), watchos(3.2, 4.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INNoteContent.h
//
//  INNoteContent.h
//  Intents
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0))
@interface INNoteContent : NSObject <NSSecureCoding, NSCopying>

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INBookRestaurantReservationIntentResponse.h
//
//  INBookRestaurantReservationIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntentResponse.h>
#import <Intents/INRestaurantReservationUserBooking.h>

typedef NS_ENUM(NSInteger, INBookRestaurantReservationIntentCode) {
    INBookRestaurantReservationIntentCodeSuccess = 0,
    INBookRestaurantReservationIntentCodeDenied,
    INBookRestaurantReservationIntentCodeFailure,
    INBookRestaurantReservationIntentCodeFailureRequiringAppLaunch,
    INBookRestaurantReservationIntentCodeFailureRequiringAppLaunchMustVerifyCredentials,
    INBookRestaurantReservationIntentCodeFailureRequiringAppLaunchServiceTemporarilyUnavailable
};

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INBookRestaurantReservationIntentResponse : INIntentResponse

- (instancetype)initWithCode:(INBookRestaurantReservationIntentCode)code userActivity:(nullable NSUserActivity *)userActivity;

@property (readonly, NS_NONATOMIC_IOSONLY) INBookRestaurantReservationIntentCode code;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurantReservationUserBooking *userBooking; // the userBooking that has been confirmed

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRideDriver_Deprecated.h
//
//  INRideDriver_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INRideDriver.h>

NS_ASSUME_NONNULL_BEGIN

@interface INRideDriver (Deprecated)

- (instancetype)initWithPersonHandle:(INPersonHandle *)personHandle
                      nameComponents:(nullable NSPersonNameComponents *)nameComponents
                         displayName:(nullable NSString *)displayName
                               image:(nullable INImage *)image
                              rating:(nullable NSString *)rating
                         phoneNumber:(nullable NSString *)phoneNumber API_DEPRECATED("Use the designated initializer instead", ios(10.0, 10.2));

- (instancetype)initWithHandle:(NSString *)handle
                   displayName:(nullable NSString *)displayName
                         image:(nullable INImage *)image
                        rating:(nullable NSString *)rating
                   phoneNumber:(nullable NSString *)phoneNumber API_DEPRECATED("Use the designated initializer instead", ios(10.0, 10.0));

- (instancetype)initWithHandle:(NSString *)handle
                nameComponents:(NSPersonNameComponents *)nameComponents
                         image:(nullable INImage *)image
                        rating:(nullable NSString *)rating
                   phoneNumber:(nullable NSString *)phoneNumber API_DEPRECATED("Use the designated initializer instead", ios(10.0, 10.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSearchForBillsIntent.h
//
//  INSearchForBillsIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INBillType.h>
#import <Intents/INPaymentStatus.h>

@class INBillPayee;
@class INBillPayeeResolutionResult;
@class INBillTypeResolutionResult;
@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INPaymentStatusResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INSearchForBillsIntent : INIntent

- (instancetype)initWithBillPayee:(nullable INBillPayee *)billPayee
                 paymentDateRange:(nullable INDateComponentsRange *)paymentDateRange
                         billType:(INBillType)billType
                           status:(INPaymentStatus)status
                     dueDateRange:(nullable INDateComponentsRange *)dueDateRange NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INBillPayee *billPayee;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *paymentDateRange;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INBillType billType;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INPaymentStatus status;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dueDateRange;

@end

@class INSearchForBillsIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSearchForBillsIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INSearchForBillsIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSearchForBillsIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSearchForBillsIntentResponse containing the details of the result of having executed the intent

 @see  INSearchForBillsIntentResponse
 */

- (void)handleSearchForBills:(INSearchForBillsIntent *)intent
                  completion:(void (^)(INSearchForBillsIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSearchForBillsIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSearchForBillsIntentResponse
 */

- (void)confirmSearchForBills:(INSearchForBillsIntent *)intent
                   completion:(void (^)(INSearchForBillsIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveBillPayeeForSearchForBills:(INSearchForBillsIntent *)intent
                    withCompletion:(void (^)(INBillPayeeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveBillPayee(for:with:));

- (void)resolvePaymentDateRangeForSearchForBills:(INSearchForBillsIntent *)intent
                    withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePaymentDateRange(for:with:));

- (void)resolveBillTypeForSearchForBills:(INSearchForBillsIntent *)intent
                    withCompletion:(void (^)(INBillTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveBillType(for:with:));

- (void)resolveStatusForSearchForBills:(INSearchForBillsIntent *)intent
                    withCompletion:(void (^)(INPaymentStatusResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveStatus(for:with:));

- (void)resolveDueDateRangeForSearchForBills:(INSearchForBillsIntent *)intent
                    withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDueDateRange(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/NSUserActivity+IntentsAdditions.h
//
//  NSUserActivity+IntentsAdditions.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INInteraction;

NS_ASSUME_NONNULL_BEGIN

@interface NSUserActivity (IntentsAdditions)

@property (readonly, nullable, NS_NONATOMIC_IOSONLY) INInteraction *interaction API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));

// A human-understandable string that can be used to suggest a voice shortcut phrase to the user
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *suggestedInvocationPhrase API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetSeatSettingsInCarIntent.h
//
//  INSetSeatSettingsInCarIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarSeat.h>
#import <Intents/INRelativeSetting.h>

@class INBooleanResolutionResult;
@class INCarSeatResolutionResult;
@class INIntegerResolutionResult;
@class INRelativeSettingResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INSetSeatSettingsInCarIntent : INIntent

- (instancetype)initWithEnableHeating:(nullable NSNumber *)enableHeating
                        enableCooling:(nullable NSNumber *)enableCooling
                        enableMassage:(nullable NSNumber *)enableMassage
                                 seat:(INCarSeat)seat
                                level:(nullable NSNumber *)level
                 relativeLevelSetting:(INRelativeSetting)relativeLevelSetting
                              carName:(nullable INSpeakableString *)carName NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(12.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *enableHeating NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *enableCooling NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *enableMassage NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCarSeat seat;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *level NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INRelativeSetting relativeLevelSetting;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *carName API_AVAILABLE(ios(12.0));

@end

@class INSetSeatSettingsInCarIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSetSeatSettingsInCarIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@protocol INSetSeatSettingsInCarIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSetSeatSettingsInCarIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSetSeatSettingsInCarIntentResponse containing the details of the result of having executed the intent

 @see  INSetSeatSettingsInCarIntentResponse
 */

- (void)handleSetSeatSettingsInCar:(INSetSeatSettingsInCarIntent *)intent
                        completion:(void (^)(INSetSeatSettingsInCarIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSetSeatSettingsInCarIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetSeatSettingsInCarIntentResponse
 */

- (void)confirmSetSeatSettingsInCar:(INSetSeatSettingsInCarIntent *)intent
                         completion:(void (^)(INSetSeatSettingsInCarIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveEnableHeatingForSetSeatSettingsInCar:(INSetSeatSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableHeating(for:with:));

- (void)resolveEnableCoolingForSetSeatSettingsInCar:(INSetSeatSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableCooling(for:with:));

- (void)resolveEnableMassageForSetSeatSettingsInCar:(INSetSeatSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableMassage(for:with:));

- (void)resolveSeatForSetSeatSettingsInCar:(INSetSeatSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INCarSeatResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveSeat(for:with:));

- (void)resolveLevelForSetSeatSettingsInCar:(INSetSeatSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveLevel(for:with:));

- (void)resolveRelativeLevelSettingForSetSeatSettingsInCar:(INSetSeatSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INRelativeSettingResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRelativeLevelSetting(for:with:));

- (void)resolveCarNameForSetSeatSettingsInCar:(INSetSeatSettingsInCarIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCarName(for:with:)) API_AVAILABLE(ios(12.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/Intents_Generated.h
//
//  Intents_Generated.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INAccountType.h>
#import <Intents/INAccountTypeResolutionResult.h>
#import <Intents/INAmountType.h>
#import <Intents/INBalanceType.h>
#import <Intents/INBalanceTypeResolutionResult.h>
#import <Intents/INBillDetails.h>
#import <Intents/INBillPayee.h>
#import <Intents/INBillPayeeResolutionResult.h>
#import <Intents/INBillType.h>
#import <Intents/INBillTypeResolutionResult.h>
#import <Intents/INCallCapability.h>
#import <Intents/INCallCapabilityOptions.h>
#import <Intents/INCallDestinationType.h>
#import <Intents/INCallDestinationTypeResolutionResult.h>
#import <Intents/INCallRecord.h>
#import <Intents/INCallRecordType.h>
#import <Intents/INCallRecordTypeOptions.h>
#import <Intents/INCallRecordTypeOptionsResolutionResult.h>
#import <Intents/INCallRecordTypeResolutionResult.h>
#import <Intents/INCarAirCirculationMode.h>
#import <Intents/INCarAirCirculationModeResolutionResult.h>
#import <Intents/INCarAudioSource.h>
#import <Intents/INCarAudioSourceResolutionResult.h>
#import <Intents/INCarDefroster.h>
#import <Intents/INCarDefrosterResolutionResult.h>
#import <Intents/INCarSeat.h>
#import <Intents/INCarSeatResolutionResult.h>
#import <Intents/INCarSignalOptions.h>
#import <Intents/INCarSignalOptionsResolutionResult.h>
#import <Intents/INCurrencyAmountResolutionResult.h>
#import <Intents/INDateSearchType.h>
#import <Intents/INDateSearchTypeResolutionResult.h>
#import <Intents/INLocationSearchType.h>
#import <Intents/INLocationSearchTypeResolutionResult.h>
#import <Intents/INMediaItem.h>
#import <Intents/INMediaItemType.h>
#import <Intents/INMessageAttribute.h>
#import <Intents/INMessageAttributeOptions.h>
#import <Intents/INMessageAttributeOptionsResolutionResult.h>
#import <Intents/INMessageAttributeResolutionResult.h>
#import <Intents/INNote.h>
#import <Intents/INNoteContentResolutionResult.h>
#import <Intents/INNoteContentType.h>
#import <Intents/INNoteContentTypeResolutionResult.h>
#import <Intents/INNoteResolutionResult.h>
#import <Intents/INNotebookItemType.h>
#import <Intents/INNotebookItemTypeResolutionResult.h>
#import <Intents/INObject.h>
#import <Intents/INPaymentAccount.h>
#import <Intents/INPaymentAccountResolutionResult.h>
#import <Intents/INPaymentAmount.h>
#import <Intents/INPaymentAmountResolutionResult.h>
#import <Intents/INPaymentMethod.h>
#import <Intents/INPaymentMethodType.h>
#import <Intents/INPaymentRecord.h>
#import <Intents/INPaymentStatus.h>
#import <Intents/INPaymentStatusResolutionResult.h>
#import <Intents/INPersonHandleLabel.h>
#import <Intents/INPersonRelationship.h>
#import <Intents/INPhotoAttributeOptions.h>
#import <Intents/INPlaybackRepeatMode.h>
#import <Intents/INRadioType.h>
#import <Intents/INRadioTypeResolutionResult.h>
#import <Intents/INRecurrenceFrequency.h>
#import <Intents/INRelativeReference.h>
#import <Intents/INRelativeReferenceResolutionResult.h>
#import <Intents/INRelativeSetting.h>
#import <Intents/INRelativeSettingResolutionResult.h>
#import <Intents/INRequestPaymentCurrencyAmountResolutionResult.h>
#import <Intents/INRequestPaymentPayerResolutionResult.h>
#import <Intents/INRideFeedbackTypeOptions.h>
#import <Intents/INRidePhase.h>
#import <Intents/INSendMessageRecipientResolutionResult.h>
#import <Intents/INSendPaymentCurrencyAmountResolutionResult.h>
#import <Intents/INSendPaymentPayeeResolutionResult.h>
#import <Intents/INSortType.h>
#import <Intents/INSpatialEvent.h>
#import <Intents/INSpatialEventTrigger.h>
#import <Intents/INSpatialEventTriggerResolutionResult.h>
#import <Intents/INTask.h>
#import <Intents/INTaskList.h>
#import <Intents/INTaskListResolutionResult.h>
#import <Intents/INTaskResolutionResult.h>
#import <Intents/INTaskStatus.h>
#import <Intents/INTaskStatusResolutionResult.h>
#import <Intents/INTaskType.h>
#import <Intents/INTemporalEventTrigger.h>
#import <Intents/INTemporalEventTriggerResolutionResult.h>
#import <Intents/INVisualCodeType.h>
#import <Intents/INVisualCodeTypeResolutionResult.h>
#import <Intents/INWorkoutGoalUnitType.h>
#import <Intents/INWorkoutGoalUnitTypeResolutionResult.h>
#import <Intents/INWorkoutLocationType.h>
#import <Intents/INWorkoutLocationTypeResolutionResult.h>
#import <Intents/INWorkoutNameIdentifier.h>
// ==========  Intents.framework/Headers/INGetRideStatusIntent.h
//
//  INGetRideStatusIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INGetRideStatusIntent : INIntent

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

@class INGetRideStatusIntentResponse;

@protocol INGetRideStatusIntentResponseObserver;

/*!
 @abstract Protocol to declare support for handling an INGetRideStatusIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INGetRideStatusIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INGetRideStatusIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INGetRideStatusIntentResponse containing the details of the result of having executed the intent

 @see  INGetRideStatusIntentResponse
 */

- (void)handleGetRideStatus:(INGetRideStatusIntent *)intent
                 completion:(void (^)(INGetRideStatusIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

- (void)startSendingUpdatesForGetRideStatus:(INGetRideStatusIntent *)intent
                                 toObserver:(id<INGetRideStatusIntentResponseObserver>)observer NS_SWIFT_NAME(startSendingUpdates(for:to:));

- (void)stopSendingUpdatesForGetRideStatus:(INGetRideStatusIntent *)intent NS_SWIFT_NAME(stopSendingUpdates(for:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INGetRideStatusIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INGetRideStatusIntentResponse
 */

- (void)confirmGetRideStatus:(INGetRideStatusIntent *)intent
                  completion:(void (^)(INGetRideStatusIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

@end

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INGetRideStatusIntentResponseObserver <NSObject>

- (void)getRideStatusResponseDidUpdate:(INGetRideStatusIntentResponse *)response NS_SWIFT_NAME(didUpdate(getRideStatus:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSendMessageIntent.h
//
//  INSendMessageIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INPerson;
@class INPersonResolutionResult;
@class INSendMessageRecipientResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12))
@interface INSendMessageIntent : INIntent

- (instancetype)initWithRecipients:(nullable NSArray<INPerson *> *)recipients
                           content:(nullable NSString *)content
                speakableGroupName:(nullable INSpeakableString *)speakableGroupName
            conversationIdentifier:(nullable NSString *)conversationIdentifier
                       serviceName:(nullable NSString *)serviceName
                            sender:(nullable INPerson *)sender NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

// Contacts to whom the message should be sent.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *recipients;

// Body text of the message.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *content;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *speakableGroupName API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *conversationIdentifier API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

// Specified service for the message.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *serviceName;

// The person, or account, sending the message.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *sender;

@end

@class INSendMessageIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSendMessageIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12))
@protocol INSendMessageIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSendMessageIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSendMessageIntentResponse containing the details of the result of having executed the intent

 @see  INSendMessageIntentResponse
 */

- (void)handleSendMessage:(INSendMessageIntent *)intent
               completion:(void (^)(INSendMessageIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSendMessageIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSendMessageIntentResponse
 */

- (void)confirmSendMessage:(INSendMessageIntent *)intent
                completion:(void (^)(INSendMessageIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveRecipientsForSendMessage:(INSendMessageIntent *)intent
                    withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveRecipients(for:with:)) API_DEPRECATED("resolveRecipientsForSendMessage:withCompletion: is deprecated. Use resolveRecipientsForSendMessage:completion: instead", ios(10.0, 11.0), watchos(3.2, 4.0));

- (void)resolveRecipientsForSendMessage:(INSendMessageIntent *)intent
                    completion:(void (^)(NSArray<INSendMessageRecipientResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveRecipients(for:with:)) API_AVAILABLE(ios(11.0), watchos(4.0));

- (void)resolveGroupNameForSendMessage:(INSendMessageIntent *)intent
                    withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveGroupName(for:with:)) API_DEPRECATED("resolveGroupNameForSendMessage:withCompletion: is deprecated. Use resolveSpeakableGroupNameForSendMessage:withCompletion: instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

- (void)resolveContentForSendMessage:(INSendMessageIntent *)intent
                    withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveContent(for:with:));

- (void)resolveSpeakableGroupNameForSendMessage:(INSendMessageIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveSpeakableGroupName(for:with:)) API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCancelRideIntent.h
//
//  INCancelRideIntent.h
//  Intents
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0))
API_UNAVAILABLE(watchos, macos)
@interface INCancelRideIntent : INIntent

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithRideIdentifier:(NSString *)rideIdentifier NS_DESIGNATED_INITIALIZER;
// Specifies the identifier of the ride to cancel.
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *rideIdentifier;

@end

@class INCancelRideIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INCancelRideIntent. By implementing this protocol, a class can provide logic for confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to confirm and handle the intent. The handling method is always called last, after confirming the intent.
 */

API_AVAILABLE(ios(11.0))
API_UNAVAILABLE(watchos, macos)
@protocol INCancelRideIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INCancelRideIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.
 
 @param  intent The input intent
 @param  completion The response handling block takes a INCancelRideIntentResponse containing the details of the result of having executed the intent
 
 @see  INCancelRideIntentResponse
 */

- (void)handleCancelRide:(INCancelRideIntent *)intent
              completion:(void (^)(INCancelRideIntentResponse *response))completion NS_SWIFT_NAME(handle(cancelRide:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system may not use the cancel ride intent.
 
 @param  intent The input intent
 @param  completion The response block contains an INCancelRideIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.
 
 @see INCancelRideIntentResponse
 
 */

- (void)confirmCancelRide:(INCancelRideIntent *)intent
               completion:(void (^)(INCancelRideIntentResponse *response))completion NS_SWIFT_NAME(confirm(cancelRide:completion:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPriceRange.h
//
//  INPriceRange.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx)
@interface INPriceRange : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

// "(min amount) to (max amount)"
- (instancetype)initWithRangeBetweenPrice:(NSDecimalNumber *)firstPrice andPrice:(NSDecimalNumber *)secondPrice currencyCode:(NSString *)currencyCode NS_SWIFT_NAME(init(firstPrice:secondPrice:currencyCode:)) NS_DESIGNATED_INITIALIZER;

// "Up to (amount)."
- (instancetype)initWithMaximumPrice:(NSDecimalNumber *)maximumPrice currencyCode:(NSString *)currencyCode NS_SWIFT_NAME(init(maximumPrice:currencyCode:)) NS_DESIGNATED_INITIALIZER;

// "Starting from (amount)."
- (instancetype)initWithMinimumPrice:(NSDecimalNumber *)minimumPrice currencyCode:(NSString *)currencyCode NS_SWIFT_NAME(init(minimumPrice:currencyCode:)) NS_DESIGNATED_INITIALIZER;

// "(amount)". Convenience initializer.
- (instancetype)initWithPrice:(NSDecimalNumber *)price currencyCode:(NSString *)currencyCode NS_SWIFT_NAME(init(price:currencyCode:));

// If a value is nil, the interval is open in that direction. Only one of these properties may be nil.
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSDecimalNumber *minimumPrice; // The lowest of the two prices used to construct this range.

@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSDecimalNumber *maximumPrice; // The highest of the two prices used to construct this range.

@property (readonly, NS_NONATOMIC_IOSONLY) NSString *currencyCode; // A ISO 4217 currency code. For a list of currency codes, see +[NSLocale ISOCurrencyCodes].

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INNoteContentResolutionResult.h
//
//  INNoteContentResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INNoteContent;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INNoteContentResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INNoteContent. The resolvedNoteContent can be different than the original INNoteContent. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedNoteContent:(INNoteContent *)resolvedNoteContent NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INNoteContent.
+ (instancetype)disambiguationWithNoteContentsToDisambiguate:(NSArray<INNoteContent *> *)noteContentsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the noteContent with which the user wants to continue.
+ (instancetype)confirmationRequiredWithNoteContentToConfirm:(nullable INNoteContent *)noteContentToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INBillType.h
//
//  INBillType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INBillType_h
#define INBillType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INBillType) {
    INBillTypeUnknown = 0,
    INBillTypeAutoInsurance,
    INBillTypeCable,
    INBillTypeCarLease,
    INBillTypeCarLoan,
    INBillTypeCreditCard,
    INBillTypeElectricity,
    INBillTypeGas,
    INBillTypeGarbageAndRecycling,
    INBillTypeHealthInsurance,
    INBillTypeHomeInsurance,
    INBillTypeInternet,
    INBillTypeLifeInsurance,
    INBillTypeMortgage,
    INBillTypeMusicStreaming,
    INBillTypePhone,
    INBillTypeRent,
    INBillTypeSewer,
    INBillTypeStudentLoan,
    INBillTypeTrafficTicket,
    INBillTypeTuition,
    INBillTypeUtilities,
    INBillTypeWater,
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macosx);

#endif // INBillType_h
// ==========  Intents.framework/Headers/INSearchForAccountsIntentResponse.h
//
//  INSearchForAccountsIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INPaymentAccount;

typedef NS_ENUM(NSInteger, INSearchForAccountsIntentResponseCode) {
    INSearchForAccountsIntentResponseCodeUnspecified = 0,
    INSearchForAccountsIntentResponseCodeReady,
    INSearchForAccountsIntentResponseCodeInProgress,
    INSearchForAccountsIntentResponseCodeSuccess,
    INSearchForAccountsIntentResponseCodeFailure,
    INSearchForAccountsIntentResponseCodeFailureRequiringAppLaunch,
    INSearchForAccountsIntentResponseCodeFailureCredentialsUnverified,
    INSearchForAccountsIntentResponseCodeFailureAccountNotFound,
    INSearchForAccountsIntentResponseCodeFailureTermsAndConditionsAcceptanceRequired API_AVAILABLE(ios(12.0), watchos(5.0)),
    INSearchForAccountsIntentResponseCodeFailureNotEligible API_AVAILABLE(ios(12.0), watchos(5.0)),
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INSearchForAccountsIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSearchForAccountsIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSearchForAccountsIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPaymentAccount *> *accounts;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSpatialEvent.h
//
//  INSpatialEvent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INSpatialEvent_h
#define INSpatialEvent_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INSpatialEvent) {
    INSpatialEventUnknown = 0,
    INSpatialEventArrive,
    INSpatialEventDepart,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

#endif // INSpatialEvent_h
// ==========  Intents.framework/Headers/INPerson_Deprecated.h
//
//  INPerson_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INPerson.h>

NS_ASSUME_NONNULL_BEGIN

@interface INPerson (Deprecated)

// The identity of the person in the application (e.g. email address, phone number, user handle, etc.)
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *handle  API_DEPRECATED("Use personHandle instead", ios(10.0, 10.0), macosx(10.12, 10.12));

//  This is the preferred convenience initializer if the app knows the name components of the person (e.g. given name, family name, etc).
- (instancetype)initWithHandle:(NSString *)handle
                nameComponents:(NSPersonNameComponents *)nameComponents
             contactIdentifier:(nullable NSString *)contactIdentifier API_DEPRECATED("Use the designated initializer instead", ios(10.0, 10.0), macosx(10.12, 10.12));

// Use this convenience initializer if the person's name is unknown
- (instancetype)initWithHandle:(NSString *)handle
                   displayName:(nullable NSString *)displayName
             contactIdentifier:(nullable NSString *)contactIdentifier API_DEPRECATED("Use the designated initializer instead", ios(10.0, 10.0), macosx(10.12, 10.12));

- (instancetype)initWithHandle:(NSString *)handle
                nameComponents:(nullable NSPersonNameComponents *)nameComponents
                   displayName:(nullable NSString *)displayName
                         image:(nullable INImage *)image
             contactIdentifier:(nullable NSString *)contactIdentifier API_DEPRECATED("Use the designated initializer instead", ios(10.0, 10.0), macosx(10.12, 10.12));




@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INTaskType.h
//
//  INTaskType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INTaskType_h
#define INTaskType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INTaskType) {
    INTaskTypeUnknown = 0,
    INTaskTypeNotCompletable,
    INTaskTypeCompletable,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

#endif // INTaskType_h
// ==========  Intents.framework/Headers/INPaymentAmountResolutionResult.h
//
//  INPaymentAmountResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INPaymentAmount;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INPaymentAmountResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INPaymentAmount. The resolvedPaymentAmount can be different than the original INPaymentAmount. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedPaymentAmount:(INPaymentAmount *)resolvedPaymentAmount NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INPaymentAmount.
+ (instancetype)disambiguationWithPaymentAmountsToDisambiguate:(NSArray<INPaymentAmount *> *)paymentAmountsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the paymentAmount with which the user wants to continue.
+ (instancetype)confirmationRequiredWithPaymentAmountToConfirm:(nullable INPaymentAmount *)paymentAmountToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPaymentAccountResolutionResult.h
//
//  INPaymentAccountResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INPaymentAccount;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INPaymentAccountResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INPaymentAccount. The resolvedPaymentAccount can be different than the original INPaymentAccount. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedPaymentAccount:(INPaymentAccount *)resolvedPaymentAccount NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INPaymentAccount.
+ (instancetype)disambiguationWithPaymentAccountsToDisambiguate:(NSArray<INPaymentAccount *> *)paymentAccountsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the paymentAccount with which the user wants to continue.
+ (instancetype)confirmationRequiredWithPaymentAccountToConfirm:(nullable INPaymentAccount *)paymentAccountToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRadioTypeResolutionResult.h
//
//  INRadioTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INRadioType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INRadioTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INRadioType. The resolvedValue can be different than the original INRadioType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedRadioType:(INRadioType)resolvedRadioType NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INRadioType)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedRadioType:", ios(10.0, 11.0));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithRadioTypeToConfirm:(INRadioType)radioTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INRadioType)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithRadioTypeToConfirm:", ios(10.0, 11.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPauseWorkoutIntentResponse.h
//
//  INPauseWorkoutIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INPauseWorkoutIntentResponseCode) {
    INPauseWorkoutIntentResponseCodeUnspecified = 0,
    INPauseWorkoutIntentResponseCodeReady,
    INPauseWorkoutIntentResponseCodeContinueInApp API_AVAILABLE(watchos(3.2)) API_DEPRECATED("INPauseWorkoutIntentResponseCodeContinueInApp is deprecated on iOS. Please use INPauseWorkoutIntentResponseCodeHandleInApp instead", ios(10.0, 11.0)),
    INPauseWorkoutIntentResponseCodeFailure,
    INPauseWorkoutIntentResponseCodeFailureRequiringAppLaunch,
    INPauseWorkoutIntentResponseCodeFailureNoMatchingWorkout,
    INPauseWorkoutIntentResponseCodeHandleInApp API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos),
    INPauseWorkoutIntentResponseCodeSuccess NS_EXTENSION_UNAVAILABLE("INPauseWorkoutIntentResponseCodeSuccess is not available to extensions. This can only be returned from the app.") API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos),
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INPauseWorkoutIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INPauseWorkoutIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INPauseWorkoutIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INStartWorkoutIntentResponse.h
//
//  INStartWorkoutIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INStartWorkoutIntentResponseCode) {
    INStartWorkoutIntentResponseCodeUnspecified = 0,
    INStartWorkoutIntentResponseCodeReady,
    INStartWorkoutIntentResponseCodeContinueInApp API_AVAILABLE(watchos(3.2)) API_DEPRECATED("INStartWorkoutIntentResponseCodeContinueInApp is deprecated on iOS. Please use INStartWorkoutIntentResponseCodeHandleInApp instead", ios(10.0, 11.0)),
    INStartWorkoutIntentResponseCodeFailure,
    INStartWorkoutIntentResponseCodeFailureRequiringAppLaunch,
    INStartWorkoutIntentResponseCodeFailureOngoingWorkout,
    INStartWorkoutIntentResponseCodeFailureNoMatchingWorkout,
    INStartWorkoutIntentResponseCodeHandleInApp API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos),
    INStartWorkoutIntentResponseCodeSuccess NS_EXTENSION_UNAVAILABLE("INStartWorkoutIntentResponseCodeSuccess is not available to extensions. This can only be returned from the app.") API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos),
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INStartWorkoutIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INStartWorkoutIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INStartWorkoutIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCarSignalOptions.h
//
//  INCarSignalOptions.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INCarSignalOptions_h
#define INCarSignalOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INCarSignalOptions) {
    INCarSignalOptionAudible = (1UL << 0),
    INCarSignalOptionVisible = (1UL << 1),
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macosx);

#endif // INCarSignalOptions_h
// ==========  Intents.framework/Headers/INDomainHandling.h
//
//  INDomainHandling.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntents.h>

#if !TARGET_OS_WATCH
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macosx)
@protocol INCallsDomainHandling <INStartAudioCallIntentHandling, INStartVideoCallIntentHandling, INSearchCallHistoryIntentHandling>
@end
#else
API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx)
@protocol INCallsDomainHandling <INStartAudioCallIntentHandling, INSearchCallHistoryIntentHandling>
@end
#endif

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INCarCommandsDomainHandling <INActivateCarSignalIntentHandling, INSetCarLockStatusIntentHandling, INGetCarLockStatusIntentHandling, INGetCarPowerLevelStatusIntentHandling>
@end

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@protocol INCarPlayDomainHandling <INSetAudioSourceInCarIntentHandling, INSetClimateSettingsInCarIntentHandling, INSetDefrosterSettingsInCarIntentHandling, INSetSeatSettingsInCarIntentHandling, INSetProfileInCarIntentHandling, INSaveProfileInCarIntentHandling>
@end

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INWorkoutsDomainHandling <INStartWorkoutIntentHandling, INPauseWorkoutIntentHandling, INEndWorkoutIntentHandling, INCancelWorkoutIntentHandling, INResumeWorkoutIntentHandling>
@end

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@protocol INRadioDomainHandling <INSetRadioStationIntentHandling>
@end

#if !TARGET_OS_WATCH
API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx)
@protocol INMessagesDomainHandling <INSendMessageIntentHandling, INSearchForMessagesIntentHandling, INSetMessageAttributeIntentHandling>
@end
#else
API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx)
@protocol INMessagesDomainHandling <INSendMessageIntentHandling, INSearchForMessagesIntentHandling>
@end
#endif

#if TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MIN_REQUIRED >= 110000

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@protocol INPaymentsDomainHandling <INSendPaymentIntentHandling, INRequestPaymentIntentHandling, INPayBillIntentHandling, INSearchForBillsIntentHandling, INSearchForAccountsIntentHandling, INTransferMoneyIntentHandling>
@end

#elif TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MIN_REQUIRED >= 100300

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INPaymentsDomainHandling <INSendPaymentIntentHandling, INRequestPaymentIntentHandling, INPayBillIntentHandling, INSearchForBillsIntentHandling>
@end

#else

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INPaymentsDomainHandling <INSendPaymentIntentHandling, INRequestPaymentIntentHandling>
@end

#endif

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INPhotosDomainHandling <INSearchForPhotosIntentHandling, INStartPhotoPlaybackIntentHandling>
@end

#if !TARGET_OS_WATCH
#if TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MIN_REQUIRED >= 110000

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@protocol INRidesharingDomainHandling <INListRideOptionsIntentHandling, INRequestRideIntentHandling, INGetRideStatusIntentHandling, INCancelRideIntentHandling, INSendRideFeedbackIntentHandling>
@end

#else

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INRidesharingDomainHandling <INListRideOptionsIntentHandling, INRequestRideIntentHandling, INGetRideStatusIntentHandling>
@end

#endif
#else
API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INRidesharingDomainHandling <INListRideOptionsIntentHandling, INRequestRideIntentHandling, INGetRideStatusIntentHandling>
@end
#endif

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@protocol INNotebookDomainHandling <INCreateNoteIntentHandling, INAppendToNoteIntentHandling, INAddTasksIntentHandling, INCreateTaskListIntentHandling, INSetTaskAttributeIntentHandling, INSearchForNotebookItemsIntentHandling>
@end

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@protocol INVisualCodeDomainHandling <INGetVisualCodeIntentHandling>
@end

// ==========  Intents.framework/Headers/INTermsAndConditions.h
//
//  INTermsAndConditions.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INTermsAndConditions : NSObject <NSSecureCoding, NSCopying>

- (instancetype)initWithLocalizedTermsAndConditionsText:(NSString *)localizedTermsAndConditionsText privacyPolicyURL:(nullable NSURL*)privacyPolicyURL termsAndConditionsURL:(nullable NSURL *)termsAndConditionsURL NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) NSString *localizedTermsAndConditionsText; // A string that contains a summary of the vendor's terms and conditions.
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSURL *privacyPolicyURL; // An optional URL that links to the vendor's privacy policy.
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSURL *termsAndConditionsURL; // An optional URL that links to the vendor's full terms and conditions.

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INIntentRestaurantReservation.h
//
//  INIntentRestaurantReservation.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INRestaurantGuest.h>
#import <Intents/INTermsAndConditions.h>
#import <Intents/INRestaurantGuestDisplayPreferences.h>
#import <Intents/INRestaurantReservationBooking.h>
#import <Intents/INRestaurantReservationUserBooking.h>
#import <Intents/INBookRestaurantReservationIntent.h>
#import <Intents/INGetAvailableRestaurantReservationBookingsIntent.h>
#import <Intents/INGetUserCurrentRestaurantReservationBookingsIntent.h>
#import <Intents/INGetAvailableRestaurantReservationBookingDefaultsIntent.h>
#import <Intents/INBookRestaurantReservationIntentResponse.h>
#import <Intents/INGetAvailableRestaurantReservationBookingsIntentResponse.h>
#import <Intents/INGetUserCurrentRestaurantReservationBookingsIntentResponse.h>
#import <Intents/INGetAvailableRestaurantReservationBookingDefaultsIntentResponse.h>
#import <Intents/INRestaurant.h>
#import <Intents/INRestaurantOffer.h>
#import <Intents/INGetRestaurantGuestIntent.h>
#import <Intents/INGetRestaurantGuestIntentResponse.h>
// ==========  Intents.framework/Headers/INRequestRideIntent_Deprecated.h
//
//  INRequestRideIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INRequestRideIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INRequestRideIntent (Deprecated)

- (instancetype)initWithPickupLocation:(nullable CLPlacemark *)pickupLocation
                       dropOffLocation:(nullable CLPlacemark *)dropOffLocation
                        rideOptionName:(nullable INSpeakableString *)rideOptionName
                             partySize:(nullable NSNumber *)partySize
                         paymentMethod:(nullable INPaymentMethod *)paymentMethod NS_REFINED_FOR_SWIFT API_DEPRECATED("Use the designated initializer instead", ios(10.0, 10.3));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPauseWorkoutIntent.h
//
//  INPauseWorkoutIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INPauseWorkoutIntent : INIntent

// Designated initializer. The `workoutName` can use `INWorkoutNameIdentifier` as its `identifier` parameter.
- (instancetype)initWithWorkoutName:(nullable INSpeakableString *)workoutName NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *workoutName;

@end

@class INPauseWorkoutIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INPauseWorkoutIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INPauseWorkoutIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INPauseWorkoutIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INPauseWorkoutIntentResponse containing the details of the result of having executed the intent

 @see  INPauseWorkoutIntentResponse
 */

- (void)handlePauseWorkout:(INPauseWorkoutIntent *)intent
                completion:(void (^)(INPauseWorkoutIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INPauseWorkoutIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INPauseWorkoutIntentResponse
 */

- (void)confirmPauseWorkout:(INPauseWorkoutIntent *)intent
                 completion:(void (^)(INPauseWorkoutIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveWorkoutNameForPauseWorkout:(INPauseWorkoutIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutName(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INTemporalEventTrigger.h
//
//  INTemporalEventTrigger.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INDateComponentsRange;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INTemporalEventTrigger : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithDateComponentsRange:(INDateComponentsRange *)dateComponentsRange NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dateComponentsRange;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INBooleanResolutionResult.h
//
//  INBooleanResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx)
@interface INBooleanResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedValue:(BOOL)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the boolean value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(nullable NSNumber *)valueToConfirm NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INTaskListResolutionResult.h
//
//  INTaskListResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INTaskList;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INTaskListResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INTaskList. The resolvedTaskList can be different than the original INTaskList. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedTaskList:(INTaskList *)resolvedTaskList NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INTaskList.
+ (instancetype)disambiguationWithTaskListsToDisambiguate:(NSArray<INTaskList *> *)taskListsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the taskList with which the user wants to continue.
+ (instancetype)confirmationRequiredWithTaskListToConfirm:(nullable INTaskList *)taskListToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INWorkoutLocationTypeResolutionResult.h
//
//  INWorkoutLocationTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INWorkoutLocationType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INWorkoutLocationTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INWorkoutLocationType. The resolvedValue can be different than the original INWorkoutLocationType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedWorkoutLocationType:(INWorkoutLocationType)resolvedWorkoutLocationType NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INWorkoutLocationType)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedWorkoutLocationType:", ios(10.0, 11.0), watchos(3.2, 4.0));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithWorkoutLocationTypeToConfirm:(INWorkoutLocationType)workoutLocationTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INWorkoutLocationType)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithWorkoutLocationTypeToConfirm:", ios(10.0, 11.0), watchos(3.2, 4.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetProfileInCarIntent_Deprecated.h
//
//  INSetProfileInCarIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INSetProfileInCarIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSetProfileInCarIntent (Deprecated)

- (instancetype)initWithProfileNumber:(nullable NSNumber *)profileNumber
                         profileLabel:(nullable NSString *)profileLabel
                       defaultProfile:(nullable NSNumber *)defaultProfile API_DEPRECATED_WITH_REPLACEMENT("-initWithProfileNumber:profileName:defaultProfile:", ios(10.0, 10.2)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

- (instancetype)initWithProfileNumber:(nullable NSNumber *)profileNumber
                          profileName:(nullable NSString *)profileName
                       defaultProfile:(nullable NSNumber *)defaultProfile API_DEPRECATED_WITH_REPLACEMENT("-initWithProfileNumber:profileName:defaultProfile:carName:", ios(10.2, 12.0)) NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *profileLabel API_DEPRECATED_WITH_REPLACEMENT("profileName", ios(10.0, 10.2)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INGetRideStatusIntentResponse.h
//
//  INGetRideStatusIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INRideStatus;

typedef NS_ENUM(NSInteger, INGetRideStatusIntentResponseCode) {
    INGetRideStatusIntentResponseCodeUnspecified = 0,
    INGetRideStatusIntentResponseCodeReady,
    INGetRideStatusIntentResponseCodeInProgress API_DEPRECATED("INGetRideStatusIntentResponseCodeInProgress is deprecated.", ios(10.0, 11.0), watchos(3.2, 4.0)),
    INGetRideStatusIntentResponseCodeSuccess,
    INGetRideStatusIntentResponseCodeFailure,
    INGetRideStatusIntentResponseCodeFailureRequiringAppLaunch,
    INGetRideStatusIntentResponseCodeFailureRequiringAppLaunchMustVerifyCredentials,
    INGetRideStatusIntentResponseCodeFailureRequiringAppLaunchServiceTemporarilyUnavailable,
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INGetRideStatusIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INGetRideStatusIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INGetRideStatusIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INRideStatus *rideStatus;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPersonResolutionResult.h
//
//  INPersonResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INPerson;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INPersonResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INPerson. The resolvedPerson can be different than the original INPerson. This allows app extensions to add and correct attributes of the INPerson. For example, an extension may add a nickname from the app.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedPerson:(INPerson *)resolvedPerson NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided people.
+ (instancetype)disambiguationWithPeopleToDisambiguate:(NSArray<INPerson *> *)peopleToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the person with which the user wants to continue.
+ (instancetype)confirmationRequiredWithPersonToConfirm:(nullable INPerson *)personToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRelativeSetting.h
//
//  INRelativeSetting.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INRelativeSetting_h
#define INRelativeSetting_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INRelativeSetting) {
    INRelativeSettingUnknown = 0,
    INRelativeSettingLowest,
    INRelativeSettingLower,
    INRelativeSettingHigher,
    INRelativeSettingHighest,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

#endif // INRelativeSetting_h
// ==========  Intents.framework/Headers/INPaymentStatusResolutionResult.h
//
//  INPaymentStatusResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INPaymentStatus.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INPaymentStatusResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INPaymentStatus. The resolvedValue can be different than the original INPaymentStatus. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedPaymentStatus:(INPaymentStatus)resolvedPaymentStatus NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INPaymentStatus)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedPaymentStatus:", ios(10.0, 11.0), watchos(3.2, 4.0));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithPaymentStatusToConfirm:(INPaymentStatus)paymentStatusToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INPaymentStatus)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithPaymentStatusToConfirm:", ios(10.0, 11.0), watchos(3.2, 4.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetTaskAttributeIntent.h
//
//  INSetTaskAttributeIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INTaskStatus.h>

@class INSpatialEventTrigger;
@class INSpatialEventTriggerResolutionResult;
@class INTask;
@class INTaskResolutionResult;
@class INTaskStatusResolutionResult;
@class INTemporalEventTrigger;
@class INTemporalEventTriggerResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INSetTaskAttributeIntent : INIntent

- (instancetype)initWithTargetTask:(nullable INTask *)targetTask
                            status:(INTaskStatus)status
               spatialEventTrigger:(nullable INSpatialEventTrigger *)spatialEventTrigger
              temporalEventTrigger:(nullable INTemporalEventTrigger *)temporalEventTrigger NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INTask *targetTask;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INTaskStatus status;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpatialEventTrigger *spatialEventTrigger;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INTemporalEventTrigger *temporalEventTrigger;

@end

@class INSetTaskAttributeIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSetTaskAttributeIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@protocol INSetTaskAttributeIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSetTaskAttributeIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSetTaskAttributeIntentResponse containing the details of the result of having executed the intent

 @see  INSetTaskAttributeIntentResponse
 */

- (void)handleSetTaskAttribute:(INSetTaskAttributeIntent *)intent
                    completion:(void (^)(INSetTaskAttributeIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSetTaskAttributeIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetTaskAttributeIntentResponse
 */

- (void)confirmSetTaskAttribute:(INSetTaskAttributeIntent *)intent
                     completion:(void (^)(INSetTaskAttributeIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveTargetTaskForSetTaskAttribute:(INSetTaskAttributeIntent *)intent
                    withCompletion:(void (^)(INTaskResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTargetTask(for:with:));

- (void)resolveStatusForSetTaskAttribute:(INSetTaskAttributeIntent *)intent
                    withCompletion:(void (^)(INTaskStatusResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveStatus(for:with:));

- (void)resolveSpatialEventTriggerForSetTaskAttribute:(INSetTaskAttributeIntent *)intent
                    withCompletion:(void (^)(INSpatialEventTriggerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveSpatialEventTrigger(for:with:));

- (void)resolveTemporalEventTriggerForSetTaskAttribute:(INSetTaskAttributeIntent *)intent
                    withCompletion:(void (^)(INTemporalEventTriggerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTemporalEventTrigger(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCarAirCirculationMode.h
//
//  INCarAirCirculationMode.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INCarAirCirculationMode_h
#define INCarAirCirculationMode_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCarAirCirculationMode) {
    INCarAirCirculationModeUnknown = 0,
    INCarAirCirculationModeFreshAir,
    INCarAirCirculationModeRecirculateAir,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

#endif // INCarAirCirculationMode_h
// ==========  Intents.framework/Headers/INSetProfileInCarIntentResponse.h
//
//  INSetProfileInCarIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSetProfileInCarIntentResponseCode) {
    INSetProfileInCarIntentResponseCodeUnspecified = 0,
    INSetProfileInCarIntentResponseCodeReady,
    INSetProfileInCarIntentResponseCodeInProgress,
    INSetProfileInCarIntentResponseCodeSuccess,
    INSetProfileInCarIntentResponseCodeFailure,
    INSetProfileInCarIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos, macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INSetProfileInCarIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSetProfileInCarIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSetProfileInCarIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRestaurantOffer.h
//
//  INRestaurantOffer.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntent.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INRestaurantOffer : NSObject <NSSecureCoding, NSCopying>

@property (copy, NS_NONATOMIC_IOSONLY) NSString *offerTitleText;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *offerDetailText;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *offerIdentifier;

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSendMessageIntentResponse.h
//
//  INSendMessageIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INMessage;

typedef NS_ENUM(NSInteger, INSendMessageIntentResponseCode) {
    INSendMessageIntentResponseCodeUnspecified = 0,
    INSendMessageIntentResponseCodeReady,
    INSendMessageIntentResponseCodeInProgress,
    INSendMessageIntentResponseCodeSuccess,
    INSendMessageIntentResponseCodeFailure,
    INSendMessageIntentResponseCodeFailureRequiringAppLaunch,
    INSendMessageIntentResponseCodeFailureMessageServiceNotAvailable,
} API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12));

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12))
@interface INSendMessageIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSendMessageIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSendMessageIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INMessage *sentMessage API_AVAILABLE(ios(10.3), watchos(3.2), macosx(10.13));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRestaurant.h
//
//  INRestaurant.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntent.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INRestaurant : NSObject <NSSecureCoding, NSCopying>

- (instancetype)initWithLocation:(CLLocation *)location name:(NSString *)name vendorIdentifier:(NSString *)vendorIdentifier restaurantIdentifier:(NSString *)restaurantIdentifier NS_DESIGNATED_INITIALIZER;

@property (copy, NS_NONATOMIC_IOSONLY) CLLocation *location;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *name;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *vendorIdentifier; // provider's vendor identifier
@property (copy, NS_NONATOMIC_IOSONLY) NSString *restaurantIdentifier; // vendor specific restaurant identifier. should match what Maps is ingesting through its data pipeline for the vendor.

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INTransferMoneyIntentResponse.h
//
//  INTransferMoneyIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INCurrencyAmount;
@class INDateComponentsRange;
@class INPaymentAccount;
@class INPaymentAmount;

typedef NS_ENUM(NSInteger, INTransferMoneyIntentResponseCode) {
    INTransferMoneyIntentResponseCodeUnspecified = 0,
    INTransferMoneyIntentResponseCodeReady,
    INTransferMoneyIntentResponseCodeInProgress,
    INTransferMoneyIntentResponseCodeSuccess,
    INTransferMoneyIntentResponseCodeFailure,
    INTransferMoneyIntentResponseCodeFailureRequiringAppLaunch,
    INTransferMoneyIntentResponseCodeFailureCredentialsUnverified,
    INTransferMoneyIntentResponseCodeFailureInsufficientFunds,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INTransferMoneyIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INTransferMoneyIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INTransferMoneyIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAccount *fromAccount;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAccount *toAccount;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAmount *transactionAmount;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *transactionScheduledDate;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *transactionNote;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *transferFee;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INMessageAttribute.h
//
//  INMessageAttribute.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INMessageAttribute_h
#define INMessageAttribute_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INMessageAttribute) {
    INMessageAttributeUnknown = 0,
    INMessageAttributeRead,
    INMessageAttributeUnread,
    INMessageAttributeFlagged,
    INMessageAttributeUnflagged,
    INMessageAttributePlayed API_AVAILABLE(ios(11.0), watchos(4.0)),
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

#endif // INMessageAttribute_h
// ==========  Intents.framework/Headers/INRideVehicle.h
//
//  INRideVehicle.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CLLocation;
@class INImage;

API_AVAILABLE(ios(10.0), watchos(3.0))
API_UNAVAILABLE(macosx)
@interface INRideVehicle : NSObject <NSCopying, NSSecureCoding>

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) CLLocation *location; // The course of this location is significant; see below.

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *registrationPlate;
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *manufacturer;
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *model;
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INImage *mapAnnotationImage; // An image suitable for display as a map annotation. Will be centered at the coordinate provided through the .vehicleLocation property, and rotated to match that location's course.

@end
// ==========  Intents.framework/Headers/INRideCompletionStatus.h
//
//  INRideCompletionStatus.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Intents/INRideFeedbackTypeOptions.h>


NS_ASSUME_NONNULL_BEGIN

@class INCurrencyAmount;

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INRideCompletionStatus: NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

// The ride completed.
+ (instancetype)completed;

// The ride completed. The fare in the provided amount was successfully paid; this amount may be displayed to the user.
+ (instancetype)completedWithSettledPaymentAmount:(INCurrencyAmount *)settledPaymentAmount NS_SWIFT_NAME(completed(settled:));

// The ride completed but there is a payment outstanding that the user needs to settle in the application.
// The .completionUserActivity should be set, and will be continued in your application to perform payment tasks.
+ (instancetype)completedWithOutstandingPaymentAmount:(INCurrencyAmount *)outstandingPaymentAmount NS_SWIFT_NAME(completed(outstanding:));

// The ride completed but there is feedback outstanding that the user may provide to the system. See INSendRideFeedbackIntent.
// If feedbackType includes INRideFeedbackTypeOptionTip, the .defaultTippingOptions should be set.
+ (instancetype)completedWithOutstandingFeedbackType:(INRideFeedbackTypeOptions)feedbackType API_AVAILABLE(ios(11.0), watchos(4.0)) NS_SWIFT_NAME(completed(feedbackType:));

// The ride was canceled by the service (e.g. because the driver asked to cancel)
+ (instancetype)canceledByService;

// The ride was canceled by the user (e.g. by doing so through your application)
+ (instancetype)canceledByUser;

// The ride was canceled by the service because the passenger was not present for pickup and the vehicle maximum wait time elapsed.
+ (instancetype)canceledMissedPickup;

// If this property is set, UI may be shown to the user to complete post-ride tasks (e.g. for settling outstanding payment). Acting on that UI will continue this activity in your application.
@property (readwrite, strong, nullable, NS_NONATOMIC_IOSONLY) NSUserActivity *completionUserActivity;

// YES if the ride was completed.
@property (readonly, NS_NONATOMIC_IOSONLY, getter=isCompleted) BOOL completed;

// YES if the ride was canceled.
@property (readonly, NS_NONATOMIC_IOSONLY, getter=isCanceled) BOOL canceled;

// YES if the user missed the pickup. This is only YES if .canceled is YES.
@property (readonly, NS_NONATOMIC_IOSONLY, getter=isMissedPickup) BOOL missedPickup;

// The payment amount, if any.
@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *paymentAmount;

// The type of feedback requested, if any.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INRideFeedbackTypeOptions feedbackType API_AVAILABLE(ios(11.0), watchos(4.0));

// Whether the payment is outstanding (YES) or settled (NO).
@property (readonly, NS_NONATOMIC_IOSONLY, getter=isOutstanding) BOOL outstanding;

// Default options the user can choose from when adding a tip.
@property (readwrite, strong, nullable, NS_NONATOMIC_IOSONLY) NSSet<INCurrencyAmount *> *defaultTippingOptions API_AVAILABLE(ios(11.0), watchos(4.0));
                                                                                                           
@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INLocationSearchType.h
//
//  INLocationSearchType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INLocationSearchType_h
#define INLocationSearchType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INLocationSearchType) {
    INLocationSearchTypeUnknown = 0,
    INLocationSearchTypeByLocationTrigger,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

#endif // INLocationSearchType_h
// ==========  Intents.framework/Headers/INIntent.h
//
//  INIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class INImage;
@class INParameter;
@class INParameterImage;

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INIntent : NSObject <NSCopying, NSSecureCoding>

// Returns the identifier of the receiver.
// Could be used to keep track of the entire transaction for resolve, confirm and handleIntent
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

// A human-understandable string representation of the intent's user-facing behavior
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *intentDescription API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

// A human-understandable string that can be shown to the user as an suggestion of the phrase they might want to use when adding intent as a shortcut to Siri.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *suggestedInvocationPhrase API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx);

// Set an image associated with a parameter on the receiver. This image will be used in display of the receiver throughout the system.
- (void)setImage:(INImage * _Nullable)image forParameterNamed:(NSString *)parameterName API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14)) NS_REFINED_FOR_SWIFT;
- (INImage * _Nullable)imageForParameterNamed:(NSString *)parameterName API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14)) NS_REFINED_FOR_SWIFT;

// The image most relevant for display to the receiver, accounting for both parameter-associated images and other images defined in the receiver.
- (INImage * _Nullable)keyImage;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCurrencyAmount.h
//
//  INCurrencyAmount.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx)
@interface INCurrencyAmount : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithAmount:(NSDecimalNumber *)amount
                  currencyCode:(NSString *)currencyCode NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDecimalNumber *amount;

// The ISO 4217 currency code that applies to the monetary amount.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *currencyCode;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSearchForNotebookItemsIntentResponse.h
//
//  INSearchForNotebookItemsIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

#import <Intents/INSortType.h>

@class INNote;
@class INTask;
@class INTaskList;

typedef NS_ENUM(NSInteger, INSearchForNotebookItemsIntentResponseCode) {
    INSearchForNotebookItemsIntentResponseCodeUnspecified = 0,
    INSearchForNotebookItemsIntentResponseCodeReady,
    INSearchForNotebookItemsIntentResponseCodeInProgress,
    INSearchForNotebookItemsIntentResponseCodeSuccess,
    INSearchForNotebookItemsIntentResponseCodeFailure,
    INSearchForNotebookItemsIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INSearchForNotebookItemsIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSearchForNotebookItemsIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSearchForNotebookItemsIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INNote *> *notes;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INTaskList *> *taskLists;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INTask *> *tasks;

@property (readwrite, assign, NS_NONATOMIC_IOSONLY) INSortType sortType;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INBalanceType.h
//
//  INBalanceType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INBalanceType_h
#define INBalanceType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INBalanceType) {
    INBalanceTypeUnknown = 0,
    INBalanceTypeMoney,
    INBalanceTypePoints,
    INBalanceTypeMiles,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

#endif // INBalanceType_h
// ==========  Intents.framework/Headers/IntentsDefines.h
//
//  IntentsDefines.h
//  Intents
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Availability.h>

#ifndef INTENTS_EXTERN
#ifdef __cplusplus
#define INTENTS_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define INTENTS_EXTERN extern __attribute__((visibility ("default")))
#endif
#endif
// ==========  Intents.framework/Headers/INTask.h
//
//  INTask.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INTaskStatus.h>
#import <Intents/INTaskType.h>

@class INSpatialEventTrigger;
@class INSpeakableString;
@class INTemporalEventTrigger;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INTask : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithTitle:(INSpeakableString *)title
                       status:(INTaskStatus)status
                     taskType:(INTaskType)taskType
          spatialEventTrigger:(nullable INSpatialEventTrigger *)spatialEventTrigger
         temporalEventTrigger:(nullable INTemporalEventTrigger *)temporalEventTrigger
        createdDateComponents:(nullable NSDateComponents *)createdDateComponents
       modifiedDateComponents:(nullable NSDateComponents *)modifiedDateComponents
                   identifier:(nullable NSString *)identifier NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INSpeakableString *title;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INTaskStatus status;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpatialEventTrigger *spatialEventTrigger;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INTemporalEventTrigger *temporalEventTrigger;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *createdDateComponents;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *modifiedDateComponents;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INTaskType taskType;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSearchForNotebookItemsIntent.h
//
//  INSearchForNotebookItemsIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INDateSearchType.h>
#import <Intents/INLocationSearchType.h>
#import <Intents/INNotebookItemType.h>
#import <Intents/INTaskStatus.h>

@class CLPlacemark;
@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INDateSearchTypeResolutionResult;
@class INLocationSearchTypeResolutionResult;
@class INNotebookItemTypeResolutionResult;
@class INPlacemarkResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;
@class INStringResolutionResult;
@class INTaskStatusResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INSearchForNotebookItemsIntent : INIntent

- (instancetype)initWithTitle:(nullable INSpeakableString *)title
                      content:(nullable NSString *)content
                     itemType:(INNotebookItemType)itemType
                       status:(INTaskStatus)status
                     location:(nullable CLPlacemark *)location
           locationSearchType:(INLocationSearchType)locationSearchType
                     dateTime:(nullable INDateComponentsRange *)dateTime
               dateSearchType:(INDateSearchType)dateSearchType
       notebookItemIdentifier:(nullable NSString *)notebookItemIdentifier NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(11.2), watchos(4.2));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *title;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *content;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INNotebookItemType itemType;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INTaskStatus status;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *location;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INLocationSearchType locationSearchType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dateTime;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INDateSearchType dateSearchType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *notebookItemIdentifier API_AVAILABLE(ios(11.2), watchos(4.2));

@end

@class INSearchForNotebookItemsIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSearchForNotebookItemsIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@protocol INSearchForNotebookItemsIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSearchForNotebookItemsIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSearchForNotebookItemsIntentResponse containing the details of the result of having executed the intent

 @see  INSearchForNotebookItemsIntentResponse
 */

- (void)handleSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                          completion:(void (^)(INSearchForNotebookItemsIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSearchForNotebookItemsIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSearchForNotebookItemsIntentResponse
 */

- (void)confirmSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                           completion:(void (^)(INSearchForNotebookItemsIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveTitleForSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTitle(for:with:));

- (void)resolveContentForSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                    withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveContent(for:with:));

- (void)resolveItemTypeForSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                    withCompletion:(void (^)(INNotebookItemTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveItemType(for:with:));

- (void)resolveStatusForSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                    withCompletion:(void (^)(INTaskStatusResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveStatus(for:with:));

- (void)resolveLocationForSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                    withCompletion:(void (^)(INPlacemarkResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveLocation(for:with:));

- (void)resolveLocationSearchTypeForSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                    withCompletion:(void (^)(INLocationSearchTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveLocationSearchType(for:with:));

- (void)resolveDateTimeForSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                    withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDateTime(for:with:));

- (void)resolveDateSearchTypeForSearchForNotebookItems:(INSearchForNotebookItemsIntent *)intent
                    withCompletion:(void (^)(INDateSearchTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDateSearchType(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSearchForNotebookItemsIntent_Deprecated.h
//
//  INSearchForNotebookItemsIntent_Deprecated.h
//  Intents
//
//  Created by Kyle Zhao on 9/18/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Intents/INSearchForNotebookItemsIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSearchForNotebookItemsIntent (Deprecated)

- (instancetype)initWithTitle:(nullable INSpeakableString *)title
                      content:(nullable NSString *)content
                     itemType:(INNotebookItemType)itemType
                       status:(INTaskStatus)status
                     location:(nullable CLPlacemark *)location
           locationSearchType:(INLocationSearchType)locationSearchType
                     dateTime:(nullable INDateComponentsRange *)dateTime
               dateSearchType:(INDateSearchType)dateSearchType API_DEPRECATED("Use the designated initializer instead", ios(11.0, 11.2), watchos(4.0, 4.2));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetCarLockStatusIntentResponse.h
//
//  INSetCarLockStatusIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSetCarLockStatusIntentResponseCode) {
    INSetCarLockStatusIntentResponseCodeUnspecified = 0,
    INSetCarLockStatusIntentResponseCodeReady,
    INSetCarLockStatusIntentResponseCodeInProgress,
    INSetCarLockStatusIntentResponseCodeSuccess,
    INSetCarLockStatusIntentResponseCodeFailure,
    INSetCarLockStatusIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INSetCarLockStatusIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSetCarLockStatusIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSetCarLockStatusIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPlacemarkResolutionResult.h
//
//  INPlacemarkResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class CLPlacemark;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INPlacemarkResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given CLPlacemark. The resolvedPlacemark can be different than the original CLPlacemark. This allows app extensions to dynamically fill-in details about the CLPlacemark, as appropriate. To make a new CLPlacemark, see <Intents/CLPlacemark+IntentsAdditions.h>. 
// Use +notRequired to continue with a 'nil' value.

+ (instancetype)successWithResolvedPlacemark:(CLPlacemark *)resolvedPlacemark NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided placemarks.
+ (instancetype)disambiguationWithPlacemarksToDisambiguate:(NSArray<CLPlacemark *> *)placemarksToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the placemark with which the user wants to continue.
+ (instancetype)confirmationRequiredWithPlacemarkToConfirm:(nullable CLPlacemark *)placemarkToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCallCapabilityOptions.h
//
//  INCallCapabilityOptions.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INCallCapabilityOptions_h
#define INCallCapabilityOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INCallCapabilityOptions) {
    INCallCapabilityOptionAudioCall = (1UL << 0),
    INCallCapabilityOptionVideoCall = (1UL << 1),
} API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12));

#endif // INCallCapabilityOptions_h
// ==========  Intents.framework/Headers/INSearchForAccountsIntent.h
//
//  INSearchForAccountsIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INAccountType.h>
#import <Intents/INBalanceType.h>

@class INAccountTypeResolutionResult;
@class INBalanceTypeResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INSearchForAccountsIntent : INIntent

- (instancetype)initWithAccountNickname:(nullable INSpeakableString *)accountNickname
                            accountType:(INAccountType)accountType
                       organizationName:(nullable INSpeakableString *)organizationName
                   requestedBalanceType:(INBalanceType)requestedBalanceType NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *accountNickname;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INAccountType accountType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *organizationName;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INBalanceType requestedBalanceType;

@end

@class INSearchForAccountsIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSearchForAccountsIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@protocol INSearchForAccountsIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSearchForAccountsIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSearchForAccountsIntentResponse containing the details of the result of having executed the intent

 @see  INSearchForAccountsIntentResponse
 */

- (void)handleSearchForAccounts:(INSearchForAccountsIntent *)intent
                     completion:(void (^)(INSearchForAccountsIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSearchForAccountsIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSearchForAccountsIntentResponse
 */

- (void)confirmSearchForAccounts:(INSearchForAccountsIntent *)intent
                      completion:(void (^)(INSearchForAccountsIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveAccountNicknameForSearchForAccounts:(INSearchForAccountsIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAccountNickname(for:with:));

- (void)resolveAccountTypeForSearchForAccounts:(INSearchForAccountsIntent *)intent
                    withCompletion:(void (^)(INAccountTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAccountType(for:with:));

- (void)resolveOrganizationNameForSearchForAccounts:(INSearchForAccountsIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveOrganizationName(for:with:));

- (void)resolveRequestedBalanceTypeForSearchForAccounts:(INSearchForAccountsIntent *)intent
                    withCompletion:(void (^)(INBalanceTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRequestedBalanceType(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INDateComponentsRangeResolutionResult.h
//
//  INDateComponentsRangeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INDateComponentsRange;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INDateComponentsRangeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INDateComponentsRange. The resolvedDateComponentsRange can be different than the original INDateComponentsRange. This allows app extensions to pick a suitable range.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedDateComponentsRange:(INDateComponentsRange *)resolvedDateComponentsRange NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided date components ranges.
+ (instancetype)disambiguationWithDateComponentsRangesToDisambiguate:(NSArray<INDateComponentsRange *> *)dateComponentsRangesToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the date components range with which the user wants to continue.
+ (instancetype)confirmationRequiredWithDateComponentsRangeToConfirm:(nullable INDateComponentsRange *)dateComponentsRangeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRequestPaymentIntent.h
//
//  INRequestPaymentIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INCurrencyAmount;
@class INCurrencyAmountResolutionResult;
@class INPerson;
@class INPersonResolutionResult;
@class INRequestPaymentCurrencyAmountResolutionResult;
@class INRequestPaymentPayerResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INRequestPaymentIntent : INIntent

- (instancetype)initWithPayer:(nullable INPerson *)payer
               currencyAmount:(nullable INCurrencyAmount *)currencyAmount
                         note:(nullable NSString *)note NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *payer;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *currencyAmount;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *note;

@end

@class INRequestPaymentIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INRequestPaymentIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INRequestPaymentIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INRequestPaymentIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INRequestPaymentIntentResponse containing the details of the result of having executed the intent

 @see  INRequestPaymentIntentResponse
 */

- (void)handleRequestPayment:(INRequestPaymentIntent *)intent
                  completion:(void (^)(INRequestPaymentIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INRequestPaymentIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INRequestPaymentIntentResponse
 */

- (void)confirmRequestPayment:(INRequestPaymentIntent *)intent
                   completion:(void (^)(INRequestPaymentIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolvePayerForRequestPayment:(INRequestPaymentIntent *)intent
                    withCompletion:(void (^)(INPersonResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePayer(for:with:)) API_DEPRECATED("resolvePayerForRequestPayment:withCompletion: is deprecated. Use resolvePayerForRequestPayment:completion: instead", ios(10.0, 11.0), watchos(3.2, 4.0));

- (void)resolvePayerForRequestPayment:(INRequestPaymentIntent *)intent
                    completion:(void (^)(INRequestPaymentPayerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePayer(for:with:)) API_AVAILABLE(ios(11.0), watchos(4.0));

- (void)resolveCurrencyAmountForRequestPayment:(INRequestPaymentIntent *)intent
                    withCompletion:(void (^)(INCurrencyAmountResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCurrencyAmount(for:with:)) API_DEPRECATED("resolveCurrencyAmountForRequestPayment:withCompletion: is deprecated. Use resolveCurrencyAmountForRequestPayment:completion: instead", ios(10.0, 11.0), watchos(3.2, 4.0));

- (void)resolveCurrencyAmountForRequestPayment:(INRequestPaymentIntent *)intent
                    completion:(void (^)(INRequestPaymentCurrencyAmountResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCurrencyAmount(for:with:)) API_AVAILABLE(ios(11.0), watchos(4.0));

- (void)resolveNoteForRequestPayment:(INRequestPaymentIntent *)intent
                    withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveNote(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSendPaymentPayeeResolutionResult.h
//
//  INSendPaymentPayeeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INPersonResolutionResult.h>

typedef NS_ENUM(NSInteger, INSendPaymentPayeeUnsupportedReason) {
    INSendPaymentPayeeUnsupportedReasonCredentialsUnverified = 1,
    INSendPaymentPayeeUnsupportedReasonInsufficientFunds,
    INSendPaymentPayeeUnsupportedReasonNoAccount,
    INSendPaymentPayeeUnsupportedReasonNoValidHandle API_AVAILABLE(ios(11.1), watchos(4.1)),
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INSendPaymentPayeeResolutionResult : INPersonResolutionResult

+ (instancetype)unsupportedForReason:(INSendPaymentPayeeUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithPersonResolutionResult:(INPersonResolutionResult *)personResolutionResult;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSpeakableString.h
//
//  INSpeakableString.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INSpeakable.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INSpeakableString : NSObject <INSpeakable, NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithVocabularyIdentifier:(NSString *)vocabularyIdentifier
                                spokenPhrase:(NSString *)spokenPhrase
                           pronunciationHint:(nullable NSString *)pronunciationHint NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithIdentifier:(NSString *)identifier
                      spokenPhrase:(NSString *)spokenPhrase
                 pronunciationHint:(nullable NSString *)pronunciationHint API_DEPRECATED("Please use -initWithVocabularyIdentifier:spokenPhrase:pronunciationHint:", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

- (instancetype)initWithSpokenPhrase:(NSString *)spokenPhrase API_AVAILABLE(ios(10.2), macosx(10.12.2));

@end

NS_ASSUME_NONNULL_END

// ==========  Intents.framework/Headers/INIntentResolutionResult.h
//
//  INIntentResolution.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INIntentResolutionResult<ObjectType> : NSObject

- (instancetype)init NS_UNAVAILABLE;

// This result is to tell Siri that the user must provide a non-nil value for this parameter in order to continue
+ (instancetype)needsValue NS_SWIFT_NAME(needsValue());

// This result is to tell Siri to continue regardless of whether the user has provided a value for this parameter or not
+ (instancetype)notRequired NS_SWIFT_NAME(notRequired());

// This result is for informing Siri that this value is unsupported
+ (instancetype)unsupported NS_SWIFT_NAME(unsupported());

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCreateTaskListIntentResponse.h
//
//  INCreateTaskListIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INTaskList;

typedef NS_ENUM(NSInteger, INCreateTaskListIntentResponseCode) {
    INCreateTaskListIntentResponseCodeUnspecified = 0,
    INCreateTaskListIntentResponseCodeReady,
    INCreateTaskListIntentResponseCodeInProgress,
    INCreateTaskListIntentResponseCodeSuccess,
    INCreateTaskListIntentResponseCodeFailure,
    INCreateTaskListIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INCreateTaskListIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INCreateTaskListIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INCreateTaskListIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INTaskList *createdTaskList;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INGetAvailableRestaurantReservationBookingsIntentResponse.h
//
//  INGetAvailableRestaurantReservationBookingsIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntentResponse.h>
#import <Intents/INRestaurantReservationBooking.h>
#import <Intents/INTermsAndConditions.h>

typedef NS_ENUM(NSInteger, INGetAvailableRestaurantReservationBookingsIntentCode) {
    INGetAvailableRestaurantReservationBookingsIntentCodeSuccess,
    INGetAvailableRestaurantReservationBookingsIntentCodeFailure,
    INGetAvailableRestaurantReservationBookingsIntentCodeFailureRequestUnsatisfiable,
    INGetAvailableRestaurantReservationBookingsIntentCodeFailureRequestUnspecified
};

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INGetAvailableRestaurantReservationBookingsIntentResponse : INIntentResponse

- (instancetype)initWithAvailableBookings:(NSArray<INRestaurantReservationBooking *> *)availableBookings code:(INGetAvailableRestaurantReservationBookingsIntentCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INGetAvailableRestaurantReservationBookingsIntentCode code;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *localizedRestaurantDescriptionText; // An optional string to be displayed in UI that allows the vendor to specify details or history about the restaurant.
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *localizedBookingAdvisementText; // An optional string to be displayed in UI that allows the vendor to detail things like specials or incentives.
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INTermsAndConditions *termsAndConditions; // An optional object allowing the vendor to display terms of use for its service
@property (readonly, NS_NONATOMIC_IOSONLY) NSArray<INRestaurantReservationBooking *> *availableBookings;

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetMessageAttributeIntent.h
//
//  INSetMessageAttributeIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INMessageAttribute.h>

@class INMessageAttributeResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INSetMessageAttributeIntent : INIntent

- (instancetype)initWithIdentifiers:(nullable NSArray<NSString *> *)identifiers
                          attribute:(INMessageAttribute)attribute NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *identifiers;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INMessageAttribute attribute;

@end

@class INSetMessageAttributeIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSetMessageAttributeIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@protocol INSetMessageAttributeIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSetMessageAttributeIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSetMessageAttributeIntentResponse containing the details of the result of having executed the intent

 @see  INSetMessageAttributeIntentResponse
 */

- (void)handleSetMessageAttribute:(INSetMessageAttributeIntent *)intent
                       completion:(void (^)(INSetMessageAttributeIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSetMessageAttributeIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetMessageAttributeIntentResponse
 */

- (void)confirmSetMessageAttribute:(INSetMessageAttributeIntent *)intent
                        completion:(void (^)(INSetMessageAttributeIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveAttributeForSetMessageAttribute:(INSetMessageAttributeIntent *)intent
                    withCompletion:(void (^)(INMessageAttributeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAttribute(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRestaurantGuestResolutionResult.h
//
//  INRestaurantGuestResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
//  This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
//  http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntentResolutionResult.h>

@class INRestaurantGuest;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INRestaurantGuestResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to proceed, with a given restaurant guest. The resolvedRestaurantGuest can be different than the original restaurant guest. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedRestaurantGuest:(INRestaurantGuest *)resolvedRestaurantGuest NS_SWIFT_NAME(success(with:));

// This resolution result is to disambiguate between the provided restaurant guests.
+ (instancetype)disambiguationWithRestaurantGuestsToDisambiguate:(NSArray<INRestaurantGuest *> *)restaurantGuestsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to confirm if this is the restaurant guest with which the user wants to continue.
+ (instancetype)confirmationRequiredWithRestaurantGuestToConfirm:(nullable INRestaurantGuest *)restaurantGuestToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INIntentHandlerProviding.h
//
//  INIntentHandlerProviding.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INIntent;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INIntentHandlerProviding <NSObject>

// Override this function to provide classes other than the extension's principal class to handle a given intent
- (nullable id)handlerForIntent:(INIntent *)intent;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INVisualCodeTypeResolutionResult.h
//
//  INVisualCodeTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INVisualCodeType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INVisualCodeTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INVisualCodeType. The resolvedValue can be different than the original INVisualCodeType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedVisualCodeType:(INVisualCodeType)resolvedVisualCodeType NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithVisualCodeTypeToConfirm:(INVisualCodeType)visualCodeTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCurrencyAmountResolutionResult.h
//
//  INCurrencyAmountResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INCurrencyAmount;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INCurrencyAmountResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INCurrencyAmount. The resolvedCurrencyAmount can be different than the original INCurrencyAmount. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedCurrencyAmount:(INCurrencyAmount *)resolvedCurrencyAmount NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INCurrencyAmount.
+ (instancetype)disambiguationWithCurrencyAmountsToDisambiguate:(NSArray<INCurrencyAmount *> *)currencyAmountsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the currencyAmount with which the user wants to continue.
+ (instancetype)confirmationRequiredWithCurrencyAmountToConfirm:(nullable INCurrencyAmount *)currencyAmountToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INEndWorkoutIntentResponse.h
//
//  INEndWorkoutIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INEndWorkoutIntentResponseCode) {
    INEndWorkoutIntentResponseCodeUnspecified = 0,
    INEndWorkoutIntentResponseCodeReady,
    INEndWorkoutIntentResponseCodeContinueInApp API_AVAILABLE(watchos(3.2)) API_DEPRECATED("INEndWorkoutIntentResponseCodeContinueInApp is deprecated on iOS. Please use INEndWorkoutIntentResponseCodeHandleInApp instead", ios(10.0, 11.0)),
    INEndWorkoutIntentResponseCodeFailure,
    INEndWorkoutIntentResponseCodeFailureRequiringAppLaunch,
    INEndWorkoutIntentResponseCodeFailureNoMatchingWorkout,
    INEndWorkoutIntentResponseCodeHandleInApp API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos),
    INEndWorkoutIntentResponseCodeSuccess NS_EXTENSION_UNAVAILABLE("INEndWorkoutIntentResponseCodeSuccess is not available to extensions. This can only be returned from the app.") API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos),
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INEndWorkoutIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INEndWorkoutIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INEndWorkoutIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCreateNoteIntentResponse.h
//
//  INCreateNoteIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INNote;

typedef NS_ENUM(NSInteger, INCreateNoteIntentResponseCode) {
    INCreateNoteIntentResponseCodeUnspecified = 0,
    INCreateNoteIntentResponseCodeReady,
    INCreateNoteIntentResponseCodeInProgress,
    INCreateNoteIntentResponseCodeSuccess,
    INCreateNoteIntentResponseCodeFailure,
    INCreateNoteIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INCreateNoteIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INCreateNoteIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INCreateNoteIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INNote *createdNote;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSearchForPhotosIntentResponse.h
//
//  INSearchForPhotosIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSearchForPhotosIntentResponseCode) {
    INSearchForPhotosIntentResponseCodeUnspecified = 0,
    INSearchForPhotosIntentResponseCodeReady,
    INSearchForPhotosIntentResponseCodeContinueInApp,
    INSearchForPhotosIntentResponseCodeFailure,
    INSearchForPhotosIntentResponseCodeFailureRequiringAppLaunch,
    INSearchForPhotosIntentResponseCodeFailureAppConfigurationRequired,
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INSearchForPhotosIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSearchForPhotosIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSearchForPhotosIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *searchResultsCount NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INTaskResolutionResult.h
//
//  INTaskResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INTask;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INTaskResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INTask. The resolvedTask can be different than the original INTask. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedTask:(INTask *)resolvedTask NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INTask.
+ (instancetype)disambiguationWithTasksToDisambiguate:(NSArray<INTask *> *)tasksToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the task with which the user wants to continue.
+ (instancetype)confirmationRequiredWithTaskToConfirm:(nullable INTask *)taskToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INTaskStatusResolutionResult.h
//
//  INTaskStatusResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INTaskStatus.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INTaskStatusResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INTaskStatus. The resolvedValue can be different than the original INTaskStatus. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedTaskStatus:(INTaskStatus)resolvedTaskStatus NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithTaskStatusToConfirm:(INTaskStatus)taskStatusToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSpatialEventTrigger.h
//
//  INSpatialEventTrigger.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INSpatialEvent.h>

@class CLPlacemark;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INSpatialEventTrigger : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithPlacemark:(CLPlacemark *)placemark
                            event:(INSpatialEvent)event NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) CLPlacemark *placemark;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INSpatialEvent event;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRequestRideIntent.h
//
//  INRequestRideIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class CLPlacemark;
@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INIntegerResolutionResult;
@class INPaymentMethod;
@class INPlacemarkResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INRequestRideIntent : INIntent

- (instancetype)initWithPickupLocation:(nullable CLPlacemark *)pickupLocation
                       dropOffLocation:(nullable CLPlacemark *)dropOffLocation
                        rideOptionName:(nullable INSpeakableString *)rideOptionName
                             partySize:(nullable NSNumber *)partySize
                         paymentMethod:(nullable INPaymentMethod *)paymentMethod
                   scheduledPickupTime:(nullable INDateComponentsRange *)scheduledPickupTime NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(10.3), watchos(3.2));

// Specifies the location to to begin the ride.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *pickupLocation;

// Specifies where the ride should end.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *dropOffLocation;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *rideOptionName;

// Defines the number of people in the party requesting the ride.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *partySize NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentMethod *paymentMethod;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *scheduledPickupTime API_AVAILABLE(ios(10.3), watchos(3.2));

@end

@class INRequestRideIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INRequestRideIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INRequestRideIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INRequestRideIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INRequestRideIntentResponse containing the details of the result of having executed the intent

 @see  INRequestRideIntentResponse
 */

- (void)handleRequestRide:(INRequestRideIntent *)intent
               completion:(void (^)(INRequestRideIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INRequestRideIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INRequestRideIntentResponse
 */

- (void)confirmRequestRide:(INRequestRideIntent *)intent
                completion:(void (^)(INRequestRideIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolvePickupLocationForRequestRide:(INRequestRideIntent *)intent
                    withCompletion:(void (^)(INPlacemarkResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePickupLocation(for:with:));

- (void)resolveDropOffLocationForRequestRide:(INRequestRideIntent *)intent
                    withCompletion:(void (^)(INPlacemarkResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDropOffLocation(for:with:));

- (void)resolveRideOptionNameForRequestRide:(INRequestRideIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRideOptionName(for:with:));

- (void)resolvePartySizeForRequestRide:(INRequestRideIntent *)intent
                    withCompletion:(void (^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePartySize(for:with:));

- (void)resolveScheduledPickupTimeForRequestRide:(INRequestRideIntent *)intent
                    withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveScheduledPickupTime(for:with:)) API_AVAILABLE(ios(10.3), watchos(3.2));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INStringResolutionResult.h
//
//  INStringResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INStringResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given string. The resolvedString can be different than the original string. This allows app extensions to apply business logic constraints to the string.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedString:(NSString *)resolvedString NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided strings.
+ (instancetype)disambiguationWithStringsToDisambiguate:(NSArray<NSString *> *)stringsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the string with which the user wants to continue.
+ (instancetype)confirmationRequiredWithStringToConfirm:(nullable NSString *)stringToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INGetRestaurantGuestIntentResponse.h
//
//  INGetRestaurantGuestIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntentResponse.h>
#import <Intents/INRestaurantGuest.h>
#import <Intents/INRestaurantGuestDisplayPreferences.h>

typedef NS_ENUM(NSInteger, INGetRestaurantGuestIntentResponseCode) {
    INGetRestaurantGuestIntentResponseCodeSuccess,
    INGetRestaurantGuestIntentResponseCodeFailure,
};

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INGetRestaurantGuestIntentResponse : INIntentResponse

- (instancetype)initWithCode:(INGetRestaurantGuestIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurantGuest *guest;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurantGuestDisplayPreferences *guestDisplayPreferences;

@property (readonly, NS_NONATOMIC_IOSONLY) INGetRestaurantGuestIntentResponseCode code;

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INObject.h
//
//  INObject.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INSpeakable.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), watchos(5.0))
API_UNAVAILABLE(macosx)
@interface INObject : NSObject <INSpeakable, NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                     displayString:(NSString *)displayString
                 pronunciationHint:(nullable NSString *)pronunciationHint NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                     displayString:(NSString *)displayString;

@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *displayString;

@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) NSString *pronunciationHint;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INUpcomingMediaManager.h
//
//  INUpcomingMediaManager.h
//  Intents
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Intents/INPlayMediaIntent.h>
#import <Intents/INMediaItemType.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, INUpcomingMediaPredictionMode) {
    INUpcomingMediaPredictionModeDefault = 0,
    INUpcomingMediaPredictionModeOnlyPredictSuggestedIntents = 1,
} API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(tvos, macosx);

API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(tvos, macosx)
@interface INUpcomingMediaManager : NSObject

@property (class, readonly, NS_NONATOMIC_IOSONLY) INUpcomingMediaManager *sharedManager;

- (void)setSuggestedMediaIntents:(NSOrderedSet<INPlayMediaIntent *> *)intents;

- (void)setPredictionMode:(INUpcomingMediaPredictionMode)mode forType:(INMediaItemType)type;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INGetAvailableRestaurantReservationBookingsIntent.h
//
//  INGetAvailableRestaurantReservationBookingsIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>
#import <Intents/INRestaurant.h>
#import <Intents/INRestaurantResolutionResult.h>
#import <Intents/INIntegerResolutionResult.h>
#import <Intents/INDateComponentsResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INGetAvailableRestaurantReservationBookingsIntent : INIntent <NSCopying>

- (instancetype)initWithRestaurant:(INRestaurant *)restaurant
                         partySize:(NSUInteger)partySize
    preferredBookingDateComponents:(nullable NSDateComponents *)preferredBookingDateComponents
            maximumNumberOfResults:(nullable NSNumber *)maximumNumberOfResults
     earliestBookingDateForResults:(nullable NSDate *)earliestBookingDateForResults
       latestBookingDateForResults:(nullable NSDate *)latestBookingDateForResults API_AVAILABLE(ios(11.0));

@property (copy, NS_NONATOMIC_IOSONLY) INRestaurant *restaurant;
@property (NS_NONATOMIC_IOSONLY) NSUInteger partySize;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *preferredBookingDateComponents;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *maximumNumberOfResults; // if the caller has a preferred maximum number of results, one can optionally be specified. a nil here leaves it up to the extension

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *earliestBookingDateForResults;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *latestBookingDateForResults;

@end

@class INGetAvailableRestaurantReservationBookingsIntentResponse;

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@protocol INGetAvailableRestaurantReservationBookingsIntentHandling <NSObject>

/*!
 @abstract Handling method - Execute the task represented by the INGetAvailableRestaurantReservationBookingsIntent that's passed in
 @discussion This method is called to actually execute the intent, the app must return a response for this intent and an NSUserActivity capturing the state that the app must be restored to at the end of handling this intent
 
 @param  intent The input intent
 @param  completion The response handling block to invoke with the response to handling the intent.
 
 @see  INGetAvailableRestaurantReservationBookingsIntentResponse
 
 */

- (void)handleGetAvailableRestaurantReservationBookings:(INGetAvailableRestaurantReservationBookingsIntent *)intent completion:(void (^)(INGetAvailableRestaurantReservationBookingsIntentResponse *response))completion NS_SWIFT_NAME(handle(getAvailableRestaurantReservationBookings:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.
 
 @param  intent The input intent
 @param  completion The response block contains an INGetAvailableRestaurantReservationBookingDefaultsIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.
 
 @see INGetAvailableRestaurantReservationBookingsIntentResponse
 
 */

- (void)confirmGetAvailableRestaurantReservationBookings:(INGetAvailableRestaurantReservationBookingsIntent *)intent completion:(void (^)(INGetAvailableRestaurantReservationBookingsIntentResponse *response))completion NS_SWIFT_NAME(confirm(getAvailableRestaurantReservationBookings:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.
 
 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved
 
 @see INGetAvailableRestaurantReservationBookingsIntentResponse
 
 */

- (void)resolveRestaurantForGetAvailableRestaurantReservationBookings:(INGetAvailableRestaurantReservationBookingsIntent *)intent withCompletion:(void(^)(INRestaurantResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRestaurant(for:completion:));
- (void)resolvePartySizeForGetAvailableRestaurantReservationBookings:(INGetAvailableRestaurantReservationBookingsIntent *)intent withCompletion:(void(^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePartySize(for:completion:));
- (void)resolvePreferredBookingDateComponentsForGetAvailableRestaurantReservationBookings:(INGetAvailableRestaurantReservationBookingsIntent *)intent withCompletion:(void(^)(INDateComponentsResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePreferredBookingDateComponents(for:completion:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRestaurantReservationUserBooking.h
//
//  INRestaurantReservationUserBooking.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntent.h>
#import <Intents/INRestaurantReservationBooking.h>
#import <Intents/INRestaurantGuest.h>
#import <Intents/INRestaurantOffer.h>

typedef NS_ENUM (NSUInteger, INRestaurantReservationUserBookingStatus) {
    INRestaurantReservationUserBookingStatusPending,
    INRestaurantReservationUserBookingStatusConfirmed,
    INRestaurantReservationUserBookingStatusDenied
};

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
NS_ASSUME_NONNULL_BEGIN
@interface INRestaurantReservationUserBooking : INRestaurantReservationBooking <NSCopying>

- (instancetype)initWithRestaurant:(INRestaurant *)restaurant bookingDate:(NSDate *)bookingDate partySize:(NSUInteger)partySize bookingIdentifier:(NSString *)bookingIdentifier guest:(INRestaurantGuest *)guest status:(INRestaurantReservationUserBookingStatus)status dateStatusModified:(NSDate *)dateStatusModified;

@property (copy, NS_NONATOMIC_IOSONLY) INRestaurantGuest *guest;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *advisementText; // a string representing restaurant specific information related to the reservation: things like late policies, parking instructions, or specials
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurantOffer *selectedOffer; // an offer, if any, attached to the booking
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *guestProvidedSpecialRequestText; // any user-specified special request text submitted with the reservation
@property (NS_NONATOMIC_IOSONLY) INRestaurantReservationUserBookingStatus status; // an enum indicating whether a booking was denied, pending, or confirmed
@property (copy, NS_NONATOMIC_IOSONLY) NSDate *dateStatusModified; // date indicating when the status was updated to its current value

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRelativeReference.h
//
//  INRelativeReference.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INRelativeReference_h
#define INRelativeReference_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INRelativeReference) {
    INRelativeReferenceUnknown = 0,
    INRelativeReferenceNext,
    INRelativeReferencePrevious,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

#endif // INRelativeReference_h
// ==========  Intents.framework/Headers/INSpatialEventTriggerResolutionResult.h
//
//  INSpatialEventTriggerResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INSpatialEventTrigger;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INSpatialEventTriggerResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INSpatialEventTrigger. The resolvedSpatialEventTrigger can be different than the original INSpatialEventTrigger. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedSpatialEventTrigger:(INSpatialEventTrigger *)resolvedSpatialEventTrigger NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INSpatialEventTrigger.
+ (instancetype)disambiguationWithSpatialEventTriggersToDisambiguate:(NSArray<INSpatialEventTrigger *> *)spatialEventTriggersToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the spatialEventTrigger with which the user wants to continue.
+ (instancetype)confirmationRequiredWithSpatialEventTriggerToConfirm:(nullable INSpatialEventTrigger *)spatialEventTriggerToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INNotebookItemType.h
//
//  INNotebookItemType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INNotebookItemType_h
#define INNotebookItemType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INNotebookItemType) {
    INNotebookItemTypeUnknown = 0,
    INNotebookItemTypeNote,
    INNotebookItemTypeTaskList,
    INNotebookItemTypeTask,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

#endif // INNotebookItemType_h
// ==========  Intents.framework/Headers/INNoteContentTypeResolutionResult.h
//
//  INNoteContentTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INNoteContentType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INNoteContentTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INNoteContentType. The resolvedValue can be different than the original INNoteContentType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedNoteContentType:(INNoteContentType)resolvedNoteContentType NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithNoteContentTypeToConfirm:(INNoteContentType)noteContentTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INAppendToNoteIntent.h
//
//  INAppendToNoteIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INNote;
@class INNoteContent;
@class INNoteContentResolutionResult;
@class INNoteResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INAppendToNoteIntent : INIntent

- (instancetype)initWithTargetNote:(nullable INNote *)targetNote
                           content:(nullable INNoteContent *)content NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INNote *targetNote;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INNoteContent *content;

@end

@class INAppendToNoteIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INAppendToNoteIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@protocol INAppendToNoteIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INAppendToNoteIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INAppendToNoteIntentResponse containing the details of the result of having executed the intent

 @see  INAppendToNoteIntentResponse
 */

- (void)handleAppendToNote:(INAppendToNoteIntent *)intent
                completion:(void (^)(INAppendToNoteIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INAppendToNoteIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INAppendToNoteIntentResponse
 */

- (void)confirmAppendToNote:(INAppendToNoteIntent *)intent
                 completion:(void (^)(INAppendToNoteIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveTargetNoteForAppendToNote:(INAppendToNoteIntent *)intent
                    withCompletion:(void (^)(INNoteResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTargetNote(for:with:));

- (void)resolveContentForAppendToNote:(INAppendToNoteIntent *)intent
                    withCompletion:(void (^)(INNoteContentResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveContent(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INIntentErrors.h
//
//  INIntentErrors.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/IntentsDefines.h>

INTENTS_EXTERN NSString * const INIntentErrorDomain API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));

typedef NS_ENUM(NSInteger, INIntentErrorCode) {
    // Interactions
    INIntentErrorInteractionOperationNotSupported = 1900,
    INIntentErrorDonatingInteraction = 1901,
    INIntentErrorDeletingAllInteractions = 1902,
    INIntentErrorDeletingInteractionWithIdentifiers = 1903,
    INIntentErrorDeletingInteractionWithGroupIdentifier = 1904,
    
    // Extension discovery / info plist validation
    INIntentErrorIntentSupportedByMultipleExtension = 2001,
    INIntentErrorRestrictedIntentsNotSupportedByExtension = 2002,
    INIntentErrorNoHandlerProvidedForIntent = 2003,
    INIntentErrorInvalidIntentName = 2004,
    INIntentErrorNoAppAvailable = 2005,
    
    // Requests
    INIntentErrorRequestTimedOut = 3001,
    
    // User Vocabulary Sync
    INIntentErrorInvalidUserVocabularyFileLocation = 4000,
    
    // Extension connection
    INIntentErrorExtensionLaunchingTimeout = 5000,
    INIntentErrorExtensionBringUpFailed = 5001,
    
    // Image loading, storage, and retrieval
    INIntentErrorImageGeneric = 6000,
    INIntentErrorImageNoServiceAvailable = 6001,
    INIntentErrorImageStorageFailed = 6002,
    INIntentErrorImageLoadingFailed = 6003,
    INIntentErrorImageRetrievalFailed = 6004,
    INIntentErrorImageProxyLoop = 6005,
    INIntentErrorImageProxyInvalid = 6006,
    INIntentErrorImageProxyTimeout = 6007,
    INIntentErrorImageServiceFailure = 6008,
    INIntentErrorImageScalingFailed = 6009,
    INIntentErrorPermissionDenied = 6010,

    // Voice Shortcuts
    INIntentErrorVoiceShortcutCreationFailed = 7000,
    INIntentErrorVoiceShortcutGetFailed = 7001,
    INIntentErrorVoiceShortcutDeleteFailed = 7002,
    
    // Encoding
    INIntentErrorEncodingGeneric = 8000,
    INIntentErrorEncodingFailed = 8001,
    
    // Decoding
    INIntentErrorDecodingGeneric = 9000,
    
} API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));
// ==========  Intents.framework/Headers/INCallRecordTypeOptions.h
//
//  INCallRecordTypeOptions.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INCallRecordTypeOptions_h
#define INCallRecordTypeOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INCallRecordTypeOptions) {
    INCallRecordTypeOptionOutgoing = (1UL << 0),
    INCallRecordTypeOptionMissed = (1UL << 1),
    INCallRecordTypeOptionReceived = (1UL << 2),
    INCallRecordTypeOptionLatest API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13)) = (1UL << 3),
    INCallRecordTypeOptionVoicemail API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13)) = (1UL << 4),
} API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12));

#endif // INCallRecordTypeOptions_h
// ==========  Intents.framework/Headers/INSiriAuthorizationStatus.h
//
//  INSiriAuthorizationStatus.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INSiriAuthorizationStatus_h
#define INSiriAuthorizationStatus_h

#import <Foundation/Foundation.h>

/*
 *  INSiriAuthorizationStatus
 *
 *  Discussion:
 *      Represents the current authorization state of the application.
 *
 */
typedef NS_ENUM(NSInteger, INSiriAuthorizationStatus) {
    // User has not yet made a choice with regards to this application.
    INSiriAuthorizationStatusNotDetermined = 0,
    
    // This application is not authorized to use Siri services.  Due
    // to active restrictions on Siri services, the user cannot change
    // this status, and may not have personally denied authorization.
    INSiriAuthorizationStatusRestricted,
    
    // User has explicitly denied authorization for this application, or
    // Siri services are disabled in Settings.
    INSiriAuthorizationStatusDenied,
    
    // User has authorized this application to use Siri services.
    INSiriAuthorizationStatusAuthorized
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

#endif /* INSiriAuthorizationStatus_h */
// ==========  Intents.framework/Headers/INRelativeReferenceResolutionResult.h
//
//  INRelativeReferenceResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INRelativeReference.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INRelativeReferenceResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INRelativeReference. The resolvedValue can be different than the original INRelativeReference. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedRelativeReference:(INRelativeReference)resolvedRelativeReference NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INRelativeReference)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedRelativeReference:", ios(10.0, 11.0));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithRelativeReferenceToConfirm:(INRelativeReference)relativeReferenceToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INRelativeReference)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithRelativeReferenceToConfirm:", ios(10.0, 11.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INWorkoutGoalUnitType.h
//
//  INWorkoutGoalUnitType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INWorkoutGoalUnitType_h
#define INWorkoutGoalUnitType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INWorkoutGoalUnitType) {
    INWorkoutGoalUnitTypeUnknown = 0,
    INWorkoutGoalUnitTypeInch,
    INWorkoutGoalUnitTypeMeter,
    INWorkoutGoalUnitTypeFoot,
    INWorkoutGoalUnitTypeMile,
    INWorkoutGoalUnitTypeYard,
    INWorkoutGoalUnitTypeSecond,
    INWorkoutGoalUnitTypeMinute,
    INWorkoutGoalUnitTypeHour,
    INWorkoutGoalUnitTypeJoule,
    INWorkoutGoalUnitTypeKiloCalorie,
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

#endif // INWorkoutGoalUnitType_h
// ==========  Intents.framework/Headers/INSetMessageAttributeIntentResponse.h
//
//  INSetMessageAttributeIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSetMessageAttributeIntentResponseCode) {
    INSetMessageAttributeIntentResponseCodeUnspecified = 0,
    INSetMessageAttributeIntentResponseCodeReady,
    INSetMessageAttributeIntentResponseCodeInProgress,
    INSetMessageAttributeIntentResponseCodeSuccess,
    INSetMessageAttributeIntentResponseCodeFailure,
    INSetMessageAttributeIntentResponseCodeFailureRequiringAppLaunch,
    INSetMessageAttributeIntentResponseCodeFailureMessageNotFound,
    INSetMessageAttributeIntentResponseCodeFailureMessageAttributeNotSet,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos, macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INSetMessageAttributeIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSetMessageAttributeIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSetMessageAttributeIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPhotoAttributeOptions.h
//
//  INPhotoAttributeOptions.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INPhotoAttributeOptions_h
#define INPhotoAttributeOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INPhotoAttributeOptions) {
    INPhotoAttributeOptionPhoto = (1UL << 0),
    INPhotoAttributeOptionVideo = (1UL << 1),
    INPhotoAttributeOptionGIF = (1UL << 2),
    INPhotoAttributeOptionFlash = (1UL << 3),
    INPhotoAttributeOptionLandscapeOrientation = (1UL << 4),
    INPhotoAttributeOptionPortraitOrientation = (1UL << 5),
    INPhotoAttributeOptionFavorite = (1UL << 6),
    INPhotoAttributeOptionSelfie = (1UL << 7),
    INPhotoAttributeOptionFrontFacingCamera = (1UL << 8),
    INPhotoAttributeOptionScreenshot = (1UL << 9),
    INPhotoAttributeOptionBurstPhoto = (1UL << 10),
    INPhotoAttributeOptionHDRPhoto = (1UL << 11),
    INPhotoAttributeOptionSquarePhoto = (1UL << 12),
    INPhotoAttributeOptionPanoramaPhoto = (1UL << 13),
    INPhotoAttributeOptionTimeLapseVideo = (1UL << 14),
    INPhotoAttributeOptionSlowMotionVideo = (1UL << 15),
    INPhotoAttributeOptionNoirFilter = (1UL << 16),
    INPhotoAttributeOptionChromeFilter = (1UL << 17),
    INPhotoAttributeOptionInstantFilter = (1UL << 18),
    INPhotoAttributeOptionTonalFilter = (1UL << 19),
    INPhotoAttributeOptionTransferFilter = (1UL << 20),
    INPhotoAttributeOptionMonoFilter = (1UL << 21),
    INPhotoAttributeOptionFadeFilter = (1UL << 22),
    INPhotoAttributeOptionProcessFilter = (1UL << 23),
    INPhotoAttributeOptionPortraitPhoto API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14)) = (1UL << 24),
    INPhotoAttributeOptionLivePhoto API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14)) = (1UL << 25),
    INPhotoAttributeOptionLoopPhoto API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14)) = (1UL << 26),
    INPhotoAttributeOptionBouncePhoto API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14)) = (1UL << 27),
    INPhotoAttributeOptionLongExposurePhoto API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14)) = (1UL << 28),
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

#endif // INPhotoAttributeOptions_h
// ==========  Intents.framework/Headers/INSendMessageIntent_Deprecated.h
//
//  INRequestRideIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INSendMessageIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSendMessageIntent (Deprecated)

- (instancetype)initWithRecipients:(nullable NSArray<INPerson *> *)recipients
                           content:(nullable NSString *)content
                         groupName:(nullable NSString *)groupName
                       serviceName:(nullable NSString *)serviceName
                            sender:(nullable INPerson *)sender API_DEPRECATED("Use the designated initializer instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *groupName API_DEPRECATED("Use speakableGroupNames instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INDateSearchType.h
//
//  INDateSearchType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INDateSearchType_h
#define INDateSearchType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INDateSearchType) {
    INDateSearchTypeUnknown = 0,
    INDateSearchTypeByDueDate,
    INDateSearchTypeByModifiedDate,
    INDateSearchTypeByCreatedDate,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

#endif // INDateSearchType_h
// ==========  Intents.framework/Headers/INSortType.h
//
//  INSortType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INSortType_h
#define INSortType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INSortType) {
    INSortTypeUnknown = 0,
    INSortTypeAsIs,
    INSortTypeByDate,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

#endif // INSortType_h
// ==========  Intents.framework/Headers/INIntegerResolutionResult.h
//
//  INIntegerResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx)
@interface INIntegerResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given integer. The resolvedValue can be different than the original integer. This allows app extensions to apply business logic constraints. For example, the extension could constrain the value to some maximum.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedValue:(NSInteger)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the integer value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(nullable NSNumber *)valueToConfirm NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INStartPhotoPlaybackIntentResponse.h
//
//  INStartPhotoPlaybackIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INStartPhotoPlaybackIntentResponseCode) {
    INStartPhotoPlaybackIntentResponseCodeUnspecified = 0,
    INStartPhotoPlaybackIntentResponseCodeReady,
    INStartPhotoPlaybackIntentResponseCodeContinueInApp,
    INStartPhotoPlaybackIntentResponseCodeFailure,
    INStartPhotoPlaybackIntentResponseCodeFailureRequiringAppLaunch,
    INStartPhotoPlaybackIntentResponseCodeFailureAppConfigurationRequired,
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INStartPhotoPlaybackIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INStartPhotoPlaybackIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INStartPhotoPlaybackIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *searchResultsCount NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRelevanceProvider.h
//
//  INRelevanceProvider.h
//  Intents
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, INDailyRoutineSituation) {
    INDailyRoutineSituationMorning,
    INDailyRoutineSituationEvening,
    INDailyRoutineSituationHome,
    INDailyRoutineSituationWork,
    INDailyRoutineSituationSchool,
    INDailyRoutineSituationGym,
} NS_SWIFT_NAME(INDailyRoutineRelevanceProvider.Situation) API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx);

API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx)
@interface INRelevanceProvider : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx)
@interface INDateRelevanceProvider : INRelevanceProvider

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSDate *startDate;
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *endDate;

- (instancetype)initWithStartDate:(NSDate *)startDate endDate:(nullable NSDate *)endDate NS_DESIGNATED_INITIALIZER;

@end

API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx)
@interface INLocationRelevanceProvider : INRelevanceProvider

@property (readonly, copy, NS_NONATOMIC_IOSONLY) CLRegion *region;

- (instancetype)initWithRegion:(CLRegion *)region NS_DESIGNATED_INITIALIZER;

@end

API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx)
@interface INDailyRoutineRelevanceProvider : INRelevanceProvider

@property (readonly, NS_NONATOMIC_IOSONLY) INDailyRoutineSituation situation;

- (instancetype)initWithSituation:(INDailyRoutineSituation)situation NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INInteraction.h
//
//  INInteraction.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INIntent;
@class INIntentResponse;

typedef NS_ENUM(NSInteger, INIntentHandlingStatus) {
    INIntentHandlingStatusUnspecified = 0,
    INIntentHandlingStatusReady,
    INIntentHandlingStatusInProgress,
    INIntentHandlingStatusSuccess,
    INIntentHandlingStatusFailure,
    INIntentHandlingStatusDeferredToApplication,
    INIntentHandlingStatusUserConfirmationRequired API_AVAILABLE(macosx(10.14), ios(12.0), watchos(5.0)),
} API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));

typedef NS_ENUM(NSInteger, INInteractionDirection) {
    INInteractionDirectionUnspecified = 0,
    INInteractionDirectionOutgoing,
    INInteractionDirectionIncoming,
} API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));

NS_ASSUME_NONNULL_BEGIN

/*
 An app can use an INInteraction to donate an action (represented as an intent) and its state to the system.

 The system may also launch the app with an NSUserActivity containing an INInteraction such that the app can perform the action if it chooses.
*/

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INInteraction : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithIntent:(INIntent *)intent response:(nullable INIntentResponse *)response NS_DESIGNATED_INITIALIZER;

// donate this interaction to the system
- (void)donateInteractionWithCompletion:(void(^_Nullable)(NSError * _Nullable error))completion NS_SWIFT_NAME(donate(completion:));

// delete all the interactions ever donated by the calling app
+ (void)deleteAllInteractionsWithCompletion:(void (^_Nullable)(NSError * _Nullable error))completion NS_SWIFT_NAME(deleteAll(completion:));

// delete the interactions with the specified identifiers that were donated by this app
+ (void)deleteInteractionsWithIdentifiers:(nonnull NSArray<NSString *> *)identifiers completion:(void(^_Nullable)(NSError * _Nullable error))completion NS_SWIFT_NAME(delete(with:completion:));

// delete this app's interactions with the specified group identifier
+ (void)deleteInteractionsWithGroupIdentifier:(nonnull NSString *)groupIdentifier completion:(void(^_Nullable)(NSError * _Nullable error))completion NS_SWIFT_NAME(delete(with:completion:));

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INIntent *intent;
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INIntentResponse *intentResponse;

// Indicates the state of execution of the intent
// This is consistent with the response state of the intentResponse, if specified
@property (readonly, NS_NONATOMIC_IOSONLY) INIntentHandlingStatus intentHandlingStatus;

// Indicates the direction of the interaction
@property (assign, NS_NONATOMIC_IOSONLY) INInteractionDirection direction;

// The time the interaction started/occurred and its duration. The app can override with their own timestamp but it defaults to the time of creation of this interaction object
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDateInterval *dateInterval;

// A unique identifier for the interaction. It defaults to a globally unique identifier.
// The app can override with their own identifier that is unique in the app's domain
@property (copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

// A user-defined identifier for the interaction group, this is handy during deletion time
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *groupIdentifier;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSearchForMessagesIntent.h
//
//  INSearchForMessagesIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INConditionalOperator.h>
#import <Intents/INMessageAttributeOptions.h>

@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INMessageAttributeOptionsResolutionResult;
@class INPerson;
@class INPersonResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12))
@interface INSearchForMessagesIntent : INIntent

- (instancetype)initWithRecipients:(nullable NSArray<INPerson *> *)recipients
                           senders:(nullable NSArray<INPerson *> *)senders
                       searchTerms:(nullable NSArray<NSString *> *)searchTerms
                        attributes:(INMessageAttributeOptions)attributes
                     dateTimeRange:(nullable INDateComponentsRange *)dateTimeRange
                       identifiers:(nullable NSArray<NSString *> *)identifiers
           notificationIdentifiers:(nullable NSArray<NSString *> *)notificationIdentifiers
               speakableGroupNames:(nullable NSArray<INSpeakableString *> *)speakableGroupNames
           conversationIdentifiers:(nullable NSArray<NSString *> *)conversationIdentifiers NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14));

// Contact that received the messages to be found.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *recipients;

// Describes how to combine the contents of the recipient array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator recipientsOperator;

// Sender of the messages to be found.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *senders;

// Describes how to combine the contents of the sender array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator sendersOperator;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *searchTerms;

// Describes how to combine the contents of the searchTerm array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator searchTermsOperator;

// Attributes of the message to be found.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INMessageAttributeOptions attributes;

// Time range in which to search for the message.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dateTimeRange;

// If available, the identifier of a particular message to be found.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *identifiers;

// Describes how to combine the contents of the identifier array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator identifiersOperator;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *notificationIdentifiers;

// Describes how to combine the contents of the notificationIdentifier array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator notificationIdentifiersOperator;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INSpeakableString *> *speakableGroupNames API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

// Describes how to combine the contents of the speakableGroupName array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator speakableGroupNamesOperator API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *conversationIdentifiers API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14));

// Describes how to combine the contents of the conversationIdentifier array.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator conversationIdentifiersOperator API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14));

@end

@class INSearchForMessagesIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSearchForMessagesIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12))
@protocol INSearchForMessagesIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSearchForMessagesIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSearchForMessagesIntentResponse containing the details of the result of having executed the intent

 @see  INSearchForMessagesIntentResponse
 */

- (void)handleSearchForMessages:(INSearchForMessagesIntent *)intent
                     completion:(void (^)(INSearchForMessagesIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSearchForMessagesIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSearchForMessagesIntentResponse
 */

- (void)confirmSearchForMessages:(INSearchForMessagesIntent *)intent
                      completion:(void (^)(INSearchForMessagesIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveRecipientsForSearchForMessages:(INSearchForMessagesIntent *)intent
                    withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveRecipients(for:with:));

- (void)resolveSendersForSearchForMessages:(INSearchForMessagesIntent *)intent
                    withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveSenders(for:with:));

- (void)resolveAttributesForSearchForMessages:(INSearchForMessagesIntent *)intent
                    withCompletion:(void (^)(INMessageAttributeOptionsResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAttributes(for:with:));

- (void)resolveDateTimeRangeForSearchForMessages:(INSearchForMessagesIntent *)intent
                    withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDateTimeRange(for:with:));

- (void)resolveGroupNamesForSearchForMessages:(INSearchForMessagesIntent *)intent
                    withCompletion:(void (^)(NSArray<INStringResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveGroupNames(for:with:)) API_DEPRECATED("resolveGroupNamesForSearchForMessages:withCompletion: is deprecated. Use resolveSpeakableGroupNamesForSearchForMessages:withCompletion: instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

- (void)resolveSpeakableGroupNamesForSearchForMessages:(INSearchForMessagesIntent *)intent
                    withCompletion:(void (^)(NSArray<INSpeakableStringResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveSpeakableGroupNames(for:with:)) API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRestaurantResolutionResult.h
//
//  INRestaurantResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
//  This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
//  http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntentResolutionResult.h>

@class INRestaurant;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INRestaurantResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to proceed, with a given restaurant. The resolvedRestaurant can be different than the original restaurant. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedRestaurant:(INRestaurant *)resolvedRestaurant NS_SWIFT_NAME(success(with:));

// This resolution result is to disambiguate between the provided restaurants.
+ (instancetype)disambiguationWithRestaurantsToDisambiguate:(NSArray<INRestaurant *> *)restaurantsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to confirm if this is the restaurant with which the user wants to continue.
+ (instancetype)confirmationRequiredWithRestaurantToConfirm:(nullable INRestaurant *)restaurantToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INParameter.h
//
//  INParameter.h
//  Intents
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Intents/INInteraction.h>

@class INParameter;

NS_ASSUME_NONNULL_BEGIN

@interface INInteraction ()

- (nullable id)parameterValueForParameter:(INParameter *)parameter API_AVAILABLE(ios(11.0));

@end

API_AVAILABLE(ios(11.0))
@interface INParameter : NSObject <NSSecureCoding, NSCopying>

+ (instancetype)parameterForClass:(Class)aClass keyPath:(NSString *)keyPath;

@property (nonatomic, readonly) Class parameterClass;
@property (nonatomic, copy, readonly) NSString *parameterKeyPath;

- (BOOL)isEqualToParameter:(INParameter *)parameter;

- (void)setIndex:(NSUInteger)index forSubKeyPath:(NSString *)subKeyPath;
- (NSUInteger)indexForSubKeyPath:(NSString *)subKeyPath;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetCarLockStatusIntent.h
//
//  INSetCarLockStatusIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INBooleanResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INSetCarLockStatusIntent : INIntent

- (instancetype)initWithLocked:(nullable NSNumber *)locked
                       carName:(nullable INSpeakableString *)carName NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *locked NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *carName;

@end

@class INSetCarLockStatusIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSetCarLockStatusIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INSetCarLockStatusIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSetCarLockStatusIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSetCarLockStatusIntentResponse containing the details of the result of having executed the intent

 @see  INSetCarLockStatusIntentResponse
 */

- (void)handleSetCarLockStatus:(INSetCarLockStatusIntent *)intent
                    completion:(void (^)(INSetCarLockStatusIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSetCarLockStatusIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetCarLockStatusIntentResponse
 */

- (void)confirmSetCarLockStatus:(INSetCarLockStatusIntent *)intent
                     completion:(void (^)(INSetCarLockStatusIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveLockedForSetCarLockStatus:(INSetCarLockStatusIntent *)intent
                    withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveLocked(for:with:));

- (void)resolveCarNameForSetCarLockStatus:(INSetCarLockStatusIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCarName(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INTextNoteContent.h
//
//  INTextNoteContent.h
//  Intents
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Intents/INNoteContent.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0))
@interface INTextNoteContent : INNoteContent <NSSecureCoding, NSCopying>

- (instancetype)initWithText:(NSString *)text;

// The text that comprises the note content
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *text;

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INBillPayeeResolutionResult.h
//
//  INBillPayeeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INBillPayee;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INBillPayeeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INBillPayee. The resolvedBillPayee can be different than the original INBillPayee. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedBillPayee:(INBillPayee *)resolvedBillPayee NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INBillPayee.
+ (instancetype)disambiguationWithBillPayeesToDisambiguate:(NSArray<INBillPayee *> *)billPayeesToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the billPayee with which the user wants to continue.
+ (instancetype)confirmationRequiredWithBillPayeeToConfirm:(nullable INBillPayee *)billPayeeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPaymentMethodType.h
//
//  INPaymentMethodType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INPaymentMethodType_h
#define INPaymentMethodType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INPaymentMethodType) {
    INPaymentMethodTypeUnknown = 0,
    INPaymentMethodTypeChecking,
    INPaymentMethodTypeSavings,
    INPaymentMethodTypeBrokerage,
    INPaymentMethodTypeDebit,
    INPaymentMethodTypeCredit,
    INPaymentMethodTypePrepaid,
    INPaymentMethodTypeStore,
    INPaymentMethodTypeApplePay,
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

#endif // INPaymentMethodType_h
// ==========  Intents.framework/Headers/INRestaurantGuest.h
//
//  INRestaurantGuest.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INPerson.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INRestaurantGuest : INPerson

- (instancetype)initWithNameComponents:(nullable NSPersonNameComponents *)nameComponents phoneNumber:(nullable NSString *)phoneNumber emailAddress:(nullable NSString *)emailAddress NS_DESIGNATED_INITIALIZER;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *phoneNumber;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *emailAddress;

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INStartWorkoutIntent.h
//
//  INStartWorkoutIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INWorkoutGoalUnitType.h>
#import <Intents/INWorkoutLocationType.h>

@class INBooleanResolutionResult;
@class INDoubleResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;
@class INWorkoutGoalUnitTypeResolutionResult;
@class INWorkoutLocationTypeResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INStartWorkoutIntent : INIntent

// Designated initializer. The `workoutName` can use `INWorkoutNameIdentifier` as its `identifier` parameter.
- (instancetype)initWithWorkoutName:(nullable INSpeakableString *)workoutName
                          goalValue:(nullable NSNumber *)goalValue
                workoutGoalUnitType:(INWorkoutGoalUnitType)workoutGoalUnitType
                workoutLocationType:(INWorkoutLocationType)workoutLocationType
                        isOpenEnded:(nullable NSNumber *)isOpenEnded NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *workoutName;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *goalValue NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INWorkoutGoalUnitType workoutGoalUnitType;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INWorkoutLocationType workoutLocationType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *isOpenEnded NS_REFINED_FOR_SWIFT;

@end

@class INStartWorkoutIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INStartWorkoutIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INStartWorkoutIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INStartWorkoutIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INStartWorkoutIntentResponse containing the details of the result of having executed the intent

 @see  INStartWorkoutIntentResponse
 */

- (void)handleStartWorkout:(INStartWorkoutIntent *)intent
                completion:(void (^)(INStartWorkoutIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INStartWorkoutIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INStartWorkoutIntentResponse
 */

- (void)confirmStartWorkout:(INStartWorkoutIntent *)intent
                 completion:(void (^)(INStartWorkoutIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveWorkoutNameForStartWorkout:(INStartWorkoutIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutName(for:with:));

- (void)resolveGoalValueForStartWorkout:(INStartWorkoutIntent *)intent
                    withCompletion:(void (^)(INDoubleResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveGoalValue(for:with:));

- (void)resolveWorkoutGoalUnitTypeForStartWorkout:(INStartWorkoutIntent *)intent
                    withCompletion:(void (^)(INWorkoutGoalUnitTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutGoalUnitType(for:with:));

- (void)resolveWorkoutLocationTypeForStartWorkout:(INStartWorkoutIntent *)intent
                    withCompletion:(void (^)(INWorkoutLocationTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutLocationType(for:with:));

- (void)resolveIsOpenEndedForStartWorkout:(INStartWorkoutIntent *)intent
                    withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveIsOpenEnded(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCallDestinationType.h
//
//  INCallDestinationType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INCallDestinationType_h
#define INCallDestinationType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCallDestinationType) {
    INCallDestinationTypeUnknown = 0,
    INCallDestinationTypeNormal,
    INCallDestinationTypeEmergency,
    INCallDestinationTypeVoicemail,
    INCallDestinationTypeRedial,
    INCallDestinationTypeNormalDestination API_DEPRECATED("Use INCallDestinationTypeNormal instead", ios(11.0, 11.0), watchos(4.0, 4.0), macosx(10.13, 10.13)) = 1,
    INCallDestinationTypeEmergencyDestination API_DEPRECATED("Use INCallDestinationTypeEmergency instead", ios(11.0, 11.0), watchos(4.0, 4.0), macosx(10.13, 10.13)) = 2,
    INCallDestinationTypeVoicemailDestination API_DEPRECATED("Use INCallDestinationTypeVoicemail instead", ios(11.0, 11.0), watchos(4.0, 4.0), macosx(10.13, 10.13)) = 3,
    INCallDestinationTypeRedialDestination API_DEPRECATED("Use INCallDestinationTypeRedial instead", ios(11.0, 11.0), watchos(4.0, 4.0), macosx(10.13, 10.13)) = 4,
} API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

#endif // INCallDestinationType_h
// ==========  Intents.framework/Headers/INCarDefrosterResolutionResult.h
//
//  INCarDefrosterResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarDefroster.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos, macosx)
@interface INCarDefrosterResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INCarDefroster. The resolvedValue can be different than the original INCarDefroster. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedCarDefroster:(INCarDefroster)resolvedCarDefroster NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INCarDefroster)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedCarDefroster:", ios(10.0, 11.0));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithCarDefrosterToConfirm:(INCarDefroster)carDefrosterToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INCarDefroster)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithCarDefrosterToConfirm:", ios(10.0, 11.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPersonHandleLabel.h
//
//  INPersonHandleLabel.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NSString *INPersonHandleLabel NS_TYPED_EXTENSIBLE_ENUM;

INTENTS_EXTERN INPersonHandleLabel const INPersonHandleLabelHome NS_SWIFT_NAME(INPersonHandleLabel.home) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonHandleLabel const INPersonHandleLabelWork NS_SWIFT_NAME(INPersonHandleLabel.work) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonHandleLabel const INPersonHandleLabeliPhone NS_SWIFT_NAME(INPersonHandleLabel.iPhone) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonHandleLabel const INPersonHandleLabelMobile NS_SWIFT_NAME(INPersonHandleLabel.mobile) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonHandleLabel const INPersonHandleLabelMain NS_SWIFT_NAME(INPersonHandleLabel.main) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonHandleLabel const INPersonHandleLabelHomeFax NS_SWIFT_NAME(INPersonHandleLabel.homeFax) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonHandleLabel const INPersonHandleLabelWorkFax NS_SWIFT_NAME(INPersonHandleLabel.workFax) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonHandleLabel const INPersonHandleLabelPager NS_SWIFT_NAME(INPersonHandleLabel.pager) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
INTENTS_EXTERN INPersonHandleLabel const INPersonHandleLabelOther NS_SWIFT_NAME(INPersonHandleLabel.other) API_AVAILABLE(ios(10.2), watchos(3.2), macosx(10.12.2));
// ==========  Intents.framework/Headers/INDateComponentsResolutionResult.h
//
//  INDateComponentsResolutionResult.m
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
@interface INDateComponentsResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given NSDateComponents. The resolvedDateComponents can be different than the original NSDateComponents. This allows app extensions to apply business logic constraints. For example, the extension could round the interval to the nearest day.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedDateComponents:(NSDateComponents *)resolvedDateComponents NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided dateComponentss.
+ (instancetype)disambiguationWithDateComponentsToDisambiguate:(NSArray<NSDateComponents *> *)dateComponentsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the dateComponents with which the user wants to continue.
+ (instancetype)confirmationRequiredWithDateComponentsToConfirm:(nullable NSDateComponents *)dateComponentsToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INVoiceShortcutCenter.h
//
//  INVoiceShortcutCenter.h
//  Intents
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INIntent;
@class INShortcut;
@class INVoiceShortcut;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Lets you access shortcuts that have been added to Siri
 @seealso INVoiceShortcut
 */
API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macosx)
@interface INVoiceShortcutCenter : NSObject

@property (class, strong, readonly) INVoiceShortcutCenter *sharedCenter;

/*!
 @note Use the @c sharedCenter singleton.
 */
+ (instancetype)new NS_UNAVAILABLE;

/*!
 @note Use the @c sharedCenter singleton.
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Get all of the shortcuts associated with this app that have been added to Siri.
 These could have either been added with `INUIAddVoiceShortcutViewController`, or separately by the user, in the Settings app.
 */
- (void)getAllVoiceShortcutsWithCompletion:(void(^)(NSArray<INVoiceShortcut *> * _Nullable voiceShortcuts, NSError * _Nullable error))completionHandler;

/*!
 @abstract Get a single shortcut (associated with this app) that has been added to Siri, by its identifier.
 */
- (void)getVoiceShortcutWithIdentifier:(NSUUID *)identifier completion:(void(^)(INVoiceShortcut * _Nullable voiceShortcut, NSError * _Nullable error))completionHandler NS_SWIFT_NAME(getVoiceShortcut(with:completion:));

/*!
 @abstract Set some shortcuts that should be suggested to the user to add to Siri.
 @discussion These suggestions are shown to the user in the Settings app.
 */
- (void)setShortcutSuggestions:(NSArray<INShortcut *> *)suggestions;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INNoteResolutionResult.h
//
//  INNoteResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INNote;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INNoteResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INNote. The resolvedNote can be different than the original INNote. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedNote:(INNote *)resolvedNote NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INNote.
+ (instancetype)disambiguationWithNotesToDisambiguate:(NSArray<INNote *> *)notesToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the note with which the user wants to continue.
+ (instancetype)confirmationRequiredWithNoteToConfirm:(nullable INNote *)noteToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INStartVideoCallIntentResponse.h
//
//  INStartVideoCallIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INStartVideoCallIntentResponseCode) {
    INStartVideoCallIntentResponseCodeUnspecified = 0,
    INStartVideoCallIntentResponseCodeReady,
    INStartVideoCallIntentResponseCodeContinueInApp,
    INStartVideoCallIntentResponseCodeFailure,
    INStartVideoCallIntentResponseCodeFailureRequiringAppLaunch,
    INStartVideoCallIntentResponseCodeFailureAppConfigurationRequired,
    INStartVideoCallIntentResponseCodeFailureCallingServiceNotAvailable,
    INStartVideoCallIntentResponseCodeFailureContactNotSupportedByApp,
    INStartVideoCallIntentResponseCodeFailureInvalidNumber API_AVAILABLE(ios(11.0), macosx(10.13)),
} API_AVAILABLE(ios(10.0), macosx(10.12)) API_UNAVAILABLE(watchos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), macosx(10.12))
API_UNAVAILABLE(watchos)
@interface INStartVideoCallIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INStartVideoCallIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INStartVideoCallIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCallRecordType.h
//
//  INCallRecordType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INCallRecordType_h
#define INCallRecordType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCallRecordType) {
    INCallRecordTypeUnknown = 0,
    INCallRecordTypeOutgoing,
    INCallRecordTypeMissed,
    INCallRecordTypeReceived,
    INCallRecordTypeLatest API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13)),
    INCallRecordTypeVoicemail API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13)),
} API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12));

#endif // INCallRecordType_h
// ==========  Intents.framework/Headers/INPayBillIntent.h
//
//  INPayBillIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INBillType.h>

@class INBillPayee;
@class INBillPayeeResolutionResult;
@class INBillTypeResolutionResult;
@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INPaymentAccount;
@class INPaymentAccountResolutionResult;
@class INPaymentAmount;
@class INPaymentAmountResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INPayBillIntent : INIntent

- (instancetype)initWithBillPayee:(nullable INBillPayee *)billPayee
                      fromAccount:(nullable INPaymentAccount *)fromAccount
                transactionAmount:(nullable INPaymentAmount *)transactionAmount
         transactionScheduledDate:(nullable INDateComponentsRange *)transactionScheduledDate
                  transactionNote:(nullable NSString *)transactionNote
                         billType:(INBillType)billType
                          dueDate:(nullable INDateComponentsRange *)dueDate NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INBillPayee *billPayee;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAccount *fromAccount;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAmount *transactionAmount;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *transactionScheduledDate;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *transactionNote;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INBillType billType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dueDate;

@end

@class INPayBillIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INPayBillIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INPayBillIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INPayBillIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INPayBillIntentResponse containing the details of the result of having executed the intent

 @see  INPayBillIntentResponse
 */

- (void)handlePayBill:(INPayBillIntent *)intent
           completion:(void (^)(INPayBillIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INPayBillIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INPayBillIntentResponse
 */

- (void)confirmPayBill:(INPayBillIntent *)intent
            completion:(void (^)(INPayBillIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveBillPayeeForPayBill:(INPayBillIntent *)intent
                    withCompletion:(void (^)(INBillPayeeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveBillPayee(for:with:));

- (void)resolveFromAccountForPayBill:(INPayBillIntent *)intent
                    withCompletion:(void (^)(INPaymentAccountResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveFromAccount(for:with:));

- (void)resolveTransactionAmountForPayBill:(INPayBillIntent *)intent
                    withCompletion:(void (^)(INPaymentAmountResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTransactionAmount(for:with:));

- (void)resolveTransactionScheduledDateForPayBill:(INPayBillIntent *)intent
                    withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTransactionScheduledDate(for:with:));

- (void)resolveTransactionNoteForPayBill:(INPayBillIntent *)intent
                    withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTransactionNote(for:with:));

- (void)resolveBillTypeForPayBill:(INPayBillIntent *)intent
                    withCompletion:(void (^)(INBillTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveBillType(for:with:));

- (void)resolveDueDateForPayBill:(INPayBillIntent *)intent
                    withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDueDate(for:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRideOption.h
//
//  INRideOption.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INPriceRange;
@class INRidePartySizeOption;
@class INRideFareLineItem;
@class INImage;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.0))
API_UNAVAILABLE(macosx)
@interface INRideOption : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithName:(NSString *)name
         estimatedPickupDate:(NSDate *)estimatedPickupDate NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithCoder:(NSCoder *)decoder NS_DESIGNATED_INITIALIZER;

@property (readwrite, copy, NS_NONATOMIC_IOSONLY) NSString *name; // a name for the ride option.

@property (readwrite, copy, NS_NONATOMIC_IOSONLY) NSDate *estimatedPickupDate; // used for providing an ETA to the user.

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INPriceRange *priceRange; // The indicative range of prices for this option.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *usesMeteredFare NS_REFINED_FOR_SWIFT; // If true, the fare will be metered by the driver, and price range information will be noted as unavailable.

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *disclaimerMessage; // A message that includes warnings or disclaimers shown to the user before they confirm the request. For example: "This ride may make multiple stops", or "This ride may be shared with other passengers".

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INRidePartySizeOption *> *availablePartySizeOptions; // Possible party size options for this ride. An empty array indicates selecting a party size is not required.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *availablePartySizeOptionsSelectionPrompt; // A message that is shown besides the available party sizes for the user.

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *specialPricing; // eg "47.5x Surge" or "Sale"
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INImage *specialPricingBadgeImage; // a vendor-specific badge image that represents special pricing.

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INRideFareLineItem *> *fareLineItems; // A set of line items for fare pricing.
@property (readwrite, strong, nullable, NS_NONATOMIC_IOSONLY) NSUserActivity *userActivityForBookingInApplication; // If set, the user will be asked to open the ride booking application to book for this ride option. (When the user selects this option, the system will open your application and continue this NSUserActivity in it.) Leave this set to nil to allow an Apple client (e.g. Siri, Maps) to instead book the ride on your app's behalf, which is preferred where possible.

@end

#pragma mark - Deprecated

@interface INRideOption (Deprecated)

@property (nonatomic, copy, nullable) NSString *identifier; // a unique identifier for this ride.

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPreferences.h
//
//  INPreferences.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INSiriAuthorizationStatus.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx)
@interface INPreferences : NSObject

+ (INSiriAuthorizationStatus)siriAuthorizationStatus NS_EXTENSION_UNAVAILABLE("siriAuthorizationStatus is not available to extensions. The main app is responsible for Siri authorization.") API_UNAVAILABLE(watchos);
+ (void)requestSiriAuthorization:(void (^)(INSiriAuthorizationStatus status))handler NS_EXTENSION_UNAVAILABLE("requestSiriAuthorization is not available to extensions. The main app is responsible for Siri authorization.") API_UNAVAILABLE(watchos);
+ (NSString *)siriLanguageCode;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCarAudioSource.h
//
//  INCarAudioSource.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INCarAudioSource_h
#define INCarAudioSource_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCarAudioSource) {
    INCarAudioSourceUnknown = 0,
    INCarAudioSourceCarPlay,
    INCarAudioSourceiPod,
    INCarAudioSourceRadio,
    INCarAudioSourceBluetooth,
    INCarAudioSourceAUX,
    INCarAudioSourceUSB,
    INCarAudioSourceMemoryCard,
    INCarAudioSourceOpticalDrive,
    INCarAudioSourceHardDrive,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

#endif // INCarAudioSource_h
