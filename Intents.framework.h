// ==========  Intents.framework/Headers/INRestaurantReservationBooking.h
//
//  INRestaurantReservationBooking.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Foundation/Foundation.h>
#import <Intents/INRestaurant.h>
#import <Intents/INRestaurantOffer.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
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
//  Copyright © 2016 Apple. All rights reserved.
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
API_UNAVAILABLE(macosx)
@interface INGetAvailableRestaurantReservationBookingDefaultsIntentResponse : INIntentResponse

@property (readonly, NS_NONATOMIC_IOSONLY) NSUInteger defaultPartySize; // default party size for an available bookings request
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSDate *defaultBookingDate; // default booking time for an available bookings request
@property (nullable, NS_NONATOMIC_IOSONLY) NSNumber *maximumPartySize;
@property (nullable, NS_NONATOMIC_IOSONLY) NSNumber *minimumPartySize;
@property (copy, NS_NONATOMIC_IOSONLY) INImage *providerImage;

- (instancetype)initWithDefaultPartySize:(NSUInteger)defaultPartySize defaultBookingDate:(NSDate *)defaultBookingDate code:(INGetAvailableRestaurantReservationBookingDefaultsIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INGetAvailableRestaurantReservationBookingDefaultsIntentResponseCode code;

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INDoubleResolutionResult.h
//
//  INDoubleResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx)
@interface INDoubleResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
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
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INCarDefroster_h
#define INCarDefroster_h

#import <Foundation/Foundation.h>

#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCarDefroster) {
    INCarDefrosterUnknown = 0,
    INCarDefrosterFront,
    INCarDefrosterRear,
};

#endif // INCarDefroster_h
// ==========  Intents.framework/Headers/INMessageAttributeResolutionResult.h
//
//  INMessageAttributeResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INMessageAttribute.h>

NS_ASSUME_NONNULL_BEGIN

@interface INMessageAttributeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedValue:(INMessageAttribute)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(INMessageAttribute)valueToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSaveProfileInCarIntentResponse.h
//
//  INSaveProfileInCarIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSaveProfileInCarIntentResponseCode) {
    INSaveProfileInCarIntentResponseCodeUnspecified = 0,
    INSaveProfileInCarIntentResponseCodeReady,
    INSaveProfileInCarIntentResponseCodeInProgress,
    INSaveProfileInCarIntentResponseCodeSuccess,
    INSaveProfileInCarIntentResponseCodeFailure,
    INSaveProfileInCarIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INSaveProfileInCarIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSaveProfileInCarIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSaveProfileInCarIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INIntents.h
//
//  INIntents.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

// Calls Intents
#import <Intents/INStartAudioCallIntent.h>
#import <Intents/INStartVideoCallIntent.h>
#import <Intents/INSearchCallHistoryIntent.h>

// CarPlay Intents
#import <Intents/INSetAudioSourceInCarIntent.h>
#import <Intents/INSetClimateSettingsInCarIntent.h>
#import <Intents/INSetDefrosterSettingsInCarIntent.h>
#import <Intents/INSetSeatSettingsInCarIntent.h>
#import <Intents/INSetProfileInCarIntent.h>
#import <Intents/INSaveProfileInCarIntent.h>

// Messages Intents
#import <Intents/INSendMessageIntent.h>
#import <Intents/INSearchForMessagesIntent.h>
#import <Intents/INSetMessageAttributeIntent.h>

// Radio Intents
#import <Intents/INSetRadioStationIntent.h>

// Payments Intents
#import <Intents/INSendPaymentIntent.h>
#import <Intents/INRequestPaymentIntent.h>

// Photos Intents
#import <Intents/INSearchForPhotosIntent.h>
#import <Intents/INStartPhotoPlaybackIntent.h>

// Ridesharing Intents
#import <Intents/INListRideOptionsIntent.h>
#import <Intents/INRequestRideIntent.h>
#import <Intents/INGetRideStatusIntent.h>

// Workouts Intents
#import <Intents/INStartWorkoutIntent.h>
#import <Intents/INPauseWorkoutIntent.h>
#import <Intents/INEndWorkoutIntent.h>
#import <Intents/INCancelWorkoutIntent.h>
#import <Intents/INResumeWorkoutIntent.h>
// ==========  Intents.framework/Headers/INCarSeat.h
//
//  INCarSeat.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
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
};

#endif // INCarSeat_h
// ==========  Intents.framework/Headers/INSetDefrosterSettingsInCarIntentResponse.h
//
//  INSetDefrosterSettingsInCarIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSetDefrosterSettingsInCarIntentResponseCode) {
    INSetDefrosterSettingsInCarIntentResponseCodeUnspecified = 0,
    INSetDefrosterSettingsInCarIntentResponseCodeReady,
    INSetDefrosterSettingsInCarIntentResponseCodeInProgress,
    INSetDefrosterSettingsInCarIntentResponseCodeSuccess,
    INSetDefrosterSettingsInCarIntentResponseCodeFailure,
    INSetDefrosterSettingsInCarIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
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
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INPerson;
@class INPersonResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INStartAudioCallIntent : INIntent

- (instancetype)initWithContacts:(nullable NSArray<INPerson *> *)contacts NS_DESIGNATED_INITIALIZER;

// Recipients of the audio call.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *contacts;

@end

@class INStartAudioCallIntentResponse;

/*!
 @brief Protocol to declare support for handling an INStartAudioCallIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(macosx(10.12), ios(10.0))
@protocol INStartAudioCallIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INStartAudioCallIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  startAudioCallIntent The input intent
 @param  completion The response handling block takes a INStartAudioCallIntentResponse containing the details of the result of having executed the intent

 @see  INStartAudioCallIntentResponse
 */

- (void)handleStartAudioCall:(INStartAudioCallIntent *)intent
                  completion:(void (^)(INStartAudioCallIntentResponse *response))completion NS_SWIFT_NAME(handle(startAudioCall:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  startAudioCallIntent The input intent
 @param  completion The response block contains an INStartAudioCallIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INStartAudioCallIntentResponse

 */

- (void)confirmStartAudioCall:(INStartAudioCallIntent *)intent
                   completion:(void (^)(INStartAudioCallIntentResponse *response))completion NS_SWIFT_NAME(confirm(startAudioCall:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  startAudioCallIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveContactsForStartAudioCall:(INStartAudioCallIntent *)intent
                          withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveContacts(forStartAudioCall:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetClimateSettingsInCarIntentResponse.h
//
//  INSetClimateSettingsInCarIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSetClimateSettingsInCarIntentResponseCode) {
    INSetClimateSettingsInCarIntentResponseCodeUnspecified = 0,
    INSetClimateSettingsInCarIntentResponseCodeReady,
    INSetClimateSettingsInCarIntentResponseCodeInProgress,
    INSetClimateSettingsInCarIntentResponseCodeSuccess,
    INSetClimateSettingsInCarIntentResponseCodeFailure,
    INSetClimateSettingsInCarIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INSetClimateSettingsInCarIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSetClimateSettingsInCarIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSetClimateSettingsInCarIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetAudioSourceInCarIntentResponse.h
//
//  INSetAudioSourceInCarIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSetAudioSourceInCarIntentResponseCode) {
    INSetAudioSourceInCarIntentResponseCodeUnspecified = 0,
    INSetAudioSourceInCarIntentResponseCodeReady,
    INSetAudioSourceInCarIntentResponseCodeInProgress,
    INSetAudioSourceInCarIntentResponseCodeSuccess,
    INSetAudioSourceInCarIntentResponseCodeFailure,
    INSetAudioSourceInCarIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
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
//  Copyright © 2016 Apple. All rights reserved.
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
API_UNAVAILABLE(macosx)
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
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INPaymentMethodType.h>

@class INImage;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx)
@interface INPaymentMethod : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithType:(INPaymentMethodType)type
                        name:(nullable NSString *)name
          identificationHint:(nullable NSString *)identificationHint
                        icon:(nullable INImage *)icon NS_DESIGNATED_INITIALIZER;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INPaymentMethodType type;

// The name of this payment method, e.g. "Flyover Rewards".
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *name;

// The identification hint for this payment method, e.g. "(···· 1259)"
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identificationHint;

// An image that represents this payment method (e.g. the card's brand).
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INImage *icon;

// This payment method represents Apple Pay. Its .type will be INPaymentMethodTypeApplePay. The .name, .identificationHint and .icon properties are not significant for this type of payment method.
+ (instancetype)applePayPaymentMethod;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetRadioStationIntentResponse.h
//
//  INSetRadioStationIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
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
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
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
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INPaymentStatus.h>

NS_ASSUME_NONNULL_BEGIN

@class INCurrencyAmount;
@class INImage;
@class INPaymentMethod;
@class INPerson;

API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx)
@interface INPaymentRecord : NSObject <NSCopying, NSSecureCoding>

- (id)init NS_UNAVAILABLE;

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

// The currency amount of the payment being sent or received.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *currencyAmount;

// The payment method being used.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentMethod *paymentMethod;

// Note of the payment being sent or received.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *note;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INPaymentStatus status;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *feeAmount;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INStartAudioCallIntentResponse.h
//
//  INStartAudioCallIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INStartAudioCallIntentResponseCode) {
    INStartAudioCallIntentResponseCodeUnspecified = 0,
    INStartAudioCallIntentResponseCodeReady,
    INStartAudioCallIntentResponseCodeContinueInApp,
    INStartAudioCallIntentResponseCodeFailure,
    INStartAudioCallIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(macosx(10.12), ios(10.0));

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
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
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INPerson.h>

@class INImage;
@class INPersonHandle;

NS_ASSUME_NONNULL_BEGIN

@interface INRideDriver : INPerson <NSCopying, NSSecureCoding>

- (instancetype)initWithPersonHandle:(INPersonHandle *)personHandle
                nameComponents:(nullable NSPersonNameComponents *)nameComponents
                   displayName:(nullable NSString *)displayName
                         image:(nullable INImage *)image
                        rating:(nullable NSString *)rating
                   phoneNumber:(nullable NSString *)phoneNumber NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithHandle:(NSString *)handle
                   displayName:(nullable NSString *)displayName
                         image:(nullable INImage *)image
                        rating:(nullable NSString *)rating
                   phoneNumber:(nullable NSString *)phoneNumber NS_DEPRECATED(10_12, 10_12, 10_0, 10_0, "Use the designated initializer instead");

- (instancetype)initWithHandle:(NSString *)handle
                nameComponents:(NSPersonNameComponents *)nameComponents
                         image:(nullable INImage *)image
                        rating:(nullable NSString *)rating
                   phoneNumber:(nullable NSString *)phoneNumber NS_DEPRECATED(10_12, 10_12, 10_0, 10_0, "Use the designated initializer instead");

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *rating;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *phoneNumber;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INEndWorkoutIntent.h
//
//  INEndWorkoutIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INEndWorkoutIntent : INIntent

- (instancetype)initWithWorkoutName:(nullable INSpeakableString *)workoutName NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *workoutName;

@end

@class INEndWorkoutIntentResponse;

/*!
 @brief Protocol to declare support for handling an INEndWorkoutIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INEndWorkoutIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INEndWorkoutIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  endWorkoutIntent The input intent
 @param  completion The response handling block takes a INEndWorkoutIntentResponse containing the details of the result of having executed the intent

 @see  INEndWorkoutIntentResponse
 */

- (void)handleEndWorkout:(INEndWorkoutIntent *)intent
              completion:(void (^)(INEndWorkoutIntentResponse *response))completion NS_SWIFT_NAME(handle(endWorkout:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  endWorkoutIntent The input intent
 @param  completion The response block contains an INEndWorkoutIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INEndWorkoutIntentResponse

 */

- (void)confirmEndWorkout:(INEndWorkoutIntent *)intent
               completion:(void (^)(INEndWorkoutIntentResponse *response))completion NS_SWIFT_NAME(confirm(endWorkout:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  endWorkoutIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveWorkoutNameForEndWorkout:(INEndWorkoutIntent *)intent
                         withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutName(forEndWorkout:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCarSeatResolutionResult.h
//
//  INCarSeatResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarSeat.h>

NS_ASSUME_NONNULL_BEGIN

@interface INCarSeatResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedValue:(INCarSeat)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(INCarSeat)valueToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INMessage.h
//
//  INMessage.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INPerson;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INMessage : NSObject <NSCopying, NSSecureCoding>

- (id)init NS_UNAVAILABLE;

- (instancetype)initWithIdentifier:(NSString *)identifier
                           content:(nullable NSString *)content
                          dateSent:(nullable NSDate *)dateSent
                            sender:(nullable INPerson *)sender
                        recipients:(nullable NSArray<INPerson *> *)recipients NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *content;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *dateSent;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *sender;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *recipients;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INConditionalOperator.h
//
//  INConditionalOperator.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INConditionalOperator_h
#define INConditionalOperator_h

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, INConditionalOperator) {
    INConditionalOperatorAll = 0,
    INConditionalOperatorAny,
    INConditionalOperatorNone,
} API_AVAILABLE(macosx(10.12), ios(10.0));

#endif // INConditionalOperator_h
// ==========  Intents.framework/Headers/INSetRadioStationIntent.h
//
//  INSetRadioStationIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INRadioType.h>

@class INRadioTypeResolutionResult;
@class INDoubleResolutionResult;
@class INStringResolutionResult;
@class INIntegerResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
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
 @brief Protocol to declare support for handling an INSetRadioStationIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INSetRadioStationIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INSetRadioStationIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  setRadioStationIntent The input intent
 @param  completion The response handling block takes a INSetRadioStationIntentResponse containing the details of the result of having executed the intent

 @see  INSetRadioStationIntentResponse
 */

- (void)handleSetRadioStation:(INSetRadioStationIntent *)intent
                   completion:(void (^)(INSetRadioStationIntentResponse *response))completion NS_SWIFT_NAME(handle(setRadioStation:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  setRadioStationIntent The input intent
 @param  completion The response block contains an INSetRadioStationIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetRadioStationIntentResponse

 */

- (void)confirmSetRadioStation:(INSetRadioStationIntent *)intent
                    completion:(void (^)(INSetRadioStationIntentResponse *response))completion NS_SWIFT_NAME(confirm(setRadioStation:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  setRadioStationIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveRadioTypeForSetRadioStation:(INSetRadioStationIntent *)intent
                            withCompletion:(void (^)(INRadioTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRadioType(forSetRadioStation:with:));

- (void)resolveFrequencyForSetRadioStation:(INSetRadioStationIntent *)intent
                            withCompletion:(void (^)(INDoubleResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveFrequency(forSetRadioStation:with:));

- (void)resolveStationNameForSetRadioStation:(INSetRadioStationIntent *)intent
                              withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveStationName(forSetRadioStation:with:));

- (void)resolveChannelForSetRadioStation:(INSetRadioStationIntent *)intent
                          withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveChannel(forSetRadioStation:with:));

- (void)resolvePresetNumberForSetRadioStation:(INSetRadioStationIntent *)intent
                               withCompletion:(void (^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePresetNumber(forSetRadioStation:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSpeakableStringResolutionResult.h
//
//  INSpeakableStringResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INSpeakableString;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INSpeakableStringResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given string. The resolvedString need not be identical to the input string. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedString:(INSpeakableString *)resolvedString NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided strings.
+ (instancetype)disambiguationWithStringsToDisambiguate:(NSArray<INSpeakableString *> *)stringsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the string with which the user wants to continue.
+ (instancetype)confirmationRequiredWithStringToConfirm:(nullable INSpeakableString *)stringToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INResumeWorkoutIntent.h
//
//  INResumeWorkoutIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INResumeWorkoutIntent : INIntent

- (instancetype)initWithWorkoutName:(nullable INSpeakableString *)workoutName NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *workoutName;

@end

@class INResumeWorkoutIntentResponse;

/*!
 @brief Protocol to declare support for handling an INResumeWorkoutIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INResumeWorkoutIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INResumeWorkoutIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  resumeWorkoutIntent The input intent
 @param  completion The response handling block takes a INResumeWorkoutIntentResponse containing the details of the result of having executed the intent

 @see  INResumeWorkoutIntentResponse
 */

- (void)handleResumeWorkout:(INResumeWorkoutIntent *)intent
                 completion:(void (^)(INResumeWorkoutIntentResponse *response))completion NS_SWIFT_NAME(handle(resumeWorkout:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  resumeWorkoutIntent The input intent
 @param  completion The response block contains an INResumeWorkoutIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INResumeWorkoutIntentResponse

 */

- (void)confirmResumeWorkout:(INResumeWorkoutIntent *)intent
                  completion:(void (^)(INResumeWorkoutIntentResponse *response))completion NS_SWIFT_NAME(confirm(resumeWorkout:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  resumeWorkoutIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveWorkoutNameForResumeWorkout:(INResumeWorkoutIntent *)intent
                            withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutName(forResumeWorkout:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INVocabulary.h
//
//  INVocabulary.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

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
};

API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos, tvos)
@interface INVocabulary : NSObject

+ (instancetype)sharedVocabulary;

/// Replaces all vocabulary strings already set for the given type.
/// Strings should be sorted by their expected importance to the user, in descending order.
/// There is no guarantee that every provided string will be used, but preference is given to strings at the beginning of the set.
/// Any strings larger than 1024 bytes when encoded as UTF-16 (roughly 500 characters) will be discarded.
- (void)setVocabularyStrings:(NSOrderedSet<NSString *> *)vocabulary ofType:(INVocabularyStringType)type NS_EXTENSION_UNAVAILABLE("INVocabulary is not available to extensions. The main app is responsible for providing all vocabulary.");

/// Removes all vocabulary strings for every INVocabularyStringType the calling app has previously registered.
- (void)removeAllVocabularyStrings NS_EXTENSION_UNAVAILABLE("INVocabulary is not available to extensions. The main app is responsible for providing all vocabulary.");

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INListRideOptionsIntent.h
//
//  INListRideOptionsIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class CLPlacemark;
@class INPlacemarkResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INListRideOptionsIntent : INIntent

- (instancetype)initWithPickupLocation:(nullable CLPlacemark *)pickupLocation
                       dropOffLocation:(nullable CLPlacemark *)dropOffLocation NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *pickupLocation;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *dropOffLocation;

@end

@class INListRideOptionsIntentResponse;

/*!
 @brief Protocol to declare support for handling an INListRideOptionsIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INListRideOptionsIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INListRideOptionsIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  listRideOptionsIntent The input intent
 @param  completion The response handling block takes a INListRideOptionsIntentResponse containing the details of the result of having executed the intent

 @see  INListRideOptionsIntentResponse
 */

- (void)handleListRideOptions:(INListRideOptionsIntent *)intent
                   completion:(void (^)(INListRideOptionsIntentResponse *response))completion NS_SWIFT_NAME(handle(listRideOptions:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  listRideOptionsIntent The input intent
 @param  completion The response block contains an INListRideOptionsIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INListRideOptionsIntentResponse

 */

- (void)confirmListRideOptions:(INListRideOptionsIntent *)intent
                    completion:(void (^)(INListRideOptionsIntentResponse *response))completion NS_SWIFT_NAME(confirm(listRideOptions:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  listRideOptionsIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolvePickupLocationForListRideOptions:(INListRideOptionsIntent *)intent
                                 withCompletion:(void (^)(INPlacemarkResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePickupLocation(forListRideOptions:with:));

- (void)resolveDropOffLocationForListRideOptions:(INListRideOptionsIntent *)intent
                                  withCompletion:(void (^)(INPlacemarkResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDropOffLocation(forListRideOptions:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INTemperatureResolutionResult.h
//
//  INTemperatureResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INTemperature;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx)
@interface INTemperatureResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given temperature. The resolvedTemperature need not be identical to the input temperature. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
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
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INIntegerResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INSaveProfileInCarIntent : INIntent

- (instancetype)initWithProfileNumber:(nullable NSNumber *)profileNumber
                         profileLabel:(nullable NSString *)profileLabel NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *profileNumber NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *profileLabel;

@end

@class INSaveProfileInCarIntentResponse;

/*!
 @brief Protocol to declare support for handling an INSaveProfileInCarIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INSaveProfileInCarIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INSaveProfileInCarIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  saveProfileInCarIntent The input intent
 @param  completion The response handling block takes a INSaveProfileInCarIntentResponse containing the details of the result of having executed the intent

 @see  INSaveProfileInCarIntentResponse
 */

- (void)handleSaveProfileInCar:(INSaveProfileInCarIntent *)intent
                    completion:(void (^)(INSaveProfileInCarIntentResponse *response))completion NS_SWIFT_NAME(handle(saveProfileInCar:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  saveProfileInCarIntent The input intent
 @param  completion The response block contains an INSaveProfileInCarIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSaveProfileInCarIntentResponse

 */

- (void)confirmSaveProfileInCar:(INSaveProfileInCarIntent *)intent
                     completion:(void (^)(INSaveProfileInCarIntentResponse *response))completion NS_SWIFT_NAME(confirm(saveProfileInCar:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  saveProfileInCarIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveProfileNumberForSaveProfileInCar:(INSaveProfileInCarIntent *)intent
                                 withCompletion:(void (^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveProfileNumber(forSaveProfileInCar:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INBookRestaurantReservationIntent.h
//
//  INBookRestaurantReservationIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
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
API_UNAVAILABLE(macosx)
@interface INBookRestaurantReservationIntent : INIntent <NSCopying>

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
API_UNAVAILABLE(macosx)
@protocol INBookRestaurantReservationIntentHandling <NSObject>

/*!
 @brief handling method
 
 @abstract Execute the task represented by the INBookRestaurantReservationIntent that's passed in
 @discussion This method are called to actually execute the intent, the app must return a response for this intent and an NSUserActivity capturing the state that the app must be restored to at the end of handling this intent
 
 @param  bookingIntent The input intent
 @param  completion The response handling block to invoke with the response to handling the intent.
 
 @see  INBookRestaurantReservationIntentResponse
 
 */

- (void)handleBookRestaurantReservation:(INBookRestaurantReservationIntent *)intent completion:(void (^)(INBookRestaurantReservationIntentResponse *response))completion  NS_SWIFT_NAME(handle(bookRestaurantReservation:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.
 
 @param  bookingIntent The input intent
 @param  completion The response block contains an INBookRestaurantReservationIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.
 
 @see INEndWorkoutIntentResponse
 
 */

- (void)confirmBookRestaurantReservation:(INBookRestaurantReservationIntent *)intent completion:(void (^)(INBookRestaurantReservationIntentResponse *response))completion  NS_SWIFT_NAME(confirm(bookRestaurantReservation:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.
 
 @param  bookingIntent The input intent
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
//  Copyright © 2016 Apple. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
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
// ==========  Intents.framework/Headers/INIntentResponses.h
//
//  INIntentResponses.h
//  Intent Responses
//
//  Copyright © 2016 Apple. All rights reserved.
//

// Calls Intent Responses
#import <Intents/INStartAudioCallIntentResponse.h>
#import <Intents/INStartVideoCallIntentResponse.h>
#import <Intents/INSearchCallHistoryIntentResponse.h>

// CarPlay Intent Responses
#import <Intents/INSetAudioSourceInCarIntentResponse.h>
#import <Intents/INSetClimateSettingsInCarIntentResponse.h>
#import <Intents/INSetDefrosterSettingsInCarIntentResponse.h>
#import <Intents/INSetSeatSettingsInCarIntentResponse.h>
#import <Intents/INSetProfileInCarIntentResponse.h>
#import <Intents/INSaveProfileInCarIntentResponse.h>

// Messages Intent Responses
#import <Intents/INSendMessageIntentResponse.h>
#import <Intents/INSearchForMessagesIntentResponse.h>
#import <Intents/INSetMessageAttributeIntentResponse.h>

// Radio Intent Responses
#import <Intents/INSetRadioStationIntentResponse.h>

// Payments Intent Responses
#import <Intents/INSendPaymentIntentResponse.h>
#import <Intents/INRequestPaymentIntentResponse.h>

// Photos Intent Responses
#import <Intents/INSearchForPhotosIntentResponse.h>
#import <Intents/INStartPhotoPlaybackIntentResponse.h>

// Ridesharing Intent Responses
#import <Intents/INListRideOptionsIntentResponse.h>
#import <Intents/INRequestRideIntentResponse.h>
#import <Intents/INGetRideStatusIntentResponse.h>

// Workouts Intent Responses
#import <Intents/INStartWorkoutIntentResponse.h>
#import <Intents/INPauseWorkoutIntentResponse.h>
#import <Intents/INEndWorkoutIntentResponse.h>
#import <Intents/INCancelWorkoutIntentResponse.h>
#import <Intents/INResumeWorkoutIntentResponse.h>
// ==========  Intents.framework/Headers/INSearchForMessagesIntentResponse.h
//
//  INSearchForMessagesIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
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
} API_AVAILABLE(macosx(10.12), ios(10.0));

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
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
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INPriceRange;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(NA, 10_0) __TVOS_PROHIBITED __WATCHOS_AVAILABLE(3_0)
@interface INRidePartySizeOption : NSObject <NSCopying, NSSecureCoding>

// A single party size in a set of party size selections. Each size may have a different price range.
- (instancetype)initWithPartySizeRange:(NSRange)partySizeRange sizeDescription:(NSString *)sizeDescription priceRange:(nullable INPriceRange *)priceRange NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

@property (readonly, NS_NONATOMIC_IOSONLY) NSRange partySizeRange; // The number of people allowed, e.g. NSMakeRange(1, 0) for one person, or NSMakeRange(1, 2) for 1 to 3 people.
@property (readonly, NS_NONATOMIC_IOSONLY) NSString *sizeDescription; // e.g. "1 passenger" or "1-3 passengers".
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) INPriceRange *priceRange; // the price range for this party size, which may be different from the indicative price range for the ride. If nil, the price range for the associated ride is valid instead.

@end

NS_ASSUME_NONNULL_END

// ==========  Intents.framework/Headers/INStartPhotoPlaybackIntent.h
//
//  INStartPhotoPlaybackIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INConditionalOperator.h>
#import <Intents/INPhotoAttributeOptions.h>

@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class CLPlacemark;
@class INPlacemarkResolutionResult;
@class INStringResolutionResult;
@class INPerson;
@class INPersonResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
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

// Describes how to combine the contents of the searchTerm array.";
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
 @brief Protocol to declare support for handling an INStartPhotoPlaybackIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INStartPhotoPlaybackIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INStartPhotoPlaybackIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  startPhotoPlaybackIntent The input intent
 @param  completion The response handling block takes a INStartPhotoPlaybackIntentResponse containing the details of the result of having executed the intent

 @see  INStartPhotoPlaybackIntentResponse
 */

- (void)handleStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                      completion:(void (^)(INStartPhotoPlaybackIntentResponse *response))completion NS_SWIFT_NAME(handle(startPhotoPlayback:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  startPhotoPlaybackIntent The input intent
 @param  completion The response block contains an INStartPhotoPlaybackIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INStartPhotoPlaybackIntentResponse

 */

- (void)confirmStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                       completion:(void (^)(INStartPhotoPlaybackIntentResponse *response))completion NS_SWIFT_NAME(confirm(startPhotoPlayback:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  startPhotoPlaybackIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveDateCreatedForStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                                 withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDateCreated(forStartPhotoPlayback:with:));

- (void)resolveLocationCreatedForStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                                     withCompletion:(void (^)(INPlacemarkResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveLocationCreated(forStartPhotoPlayback:with:));

- (void)resolveAlbumNameForStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                               withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAlbumName(forStartPhotoPlayback:with:));

- (void)resolvePeopleInPhotoForStartPhotoPlayback:(INStartPhotoPlaybackIntent *)intent
                                   withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolvePeopleInPhoto(forStartPhotoPlayback:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/CLPlacemark+IntentsAdditions.h
//
//  CLPlacemark+IntentsAdditions.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CLPlacemark.h>

@class CNPostalAddress;

NS_ASSUME_NONNULL_BEGIN

@interface CLPlacemark (INIntentsAdditions)

+ (instancetype)placemarkWithLocation:(CLLocation *)location
                                 name:(nullable NSString *)name
                        postalAddress:(nullable CNPostalAddress *)postalAddress API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx, watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCarAudioSourceResolutionResult.h
//
//  INCarAudioSourceResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarAudioSource.h>

NS_ASSUME_NONNULL_BEGIN

@interface INCarAudioSourceResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedValue:(INCarAudioSource)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(INCarAudioSource)valueToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetDefrosterSettingsInCarIntent.h
//
//  INSetDefrosterSettingsInCarIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarDefroster.h>

@class INBooleanResolutionResult;
@class INCarDefrosterResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INSetDefrosterSettingsInCarIntent : INIntent

- (instancetype)initWithEnable:(nullable NSNumber *)enable
                     defroster:(INCarDefroster)defroster NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *enable NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCarDefroster defroster;

@end

@class INSetDefrosterSettingsInCarIntentResponse;

/*!
 @brief Protocol to declare support for handling an INSetDefrosterSettingsInCarIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INSetDefrosterSettingsInCarIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INSetDefrosterSettingsInCarIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  setDefrosterSettingsInCarIntent The input intent
 @param  completion The response handling block takes a INSetDefrosterSettingsInCarIntentResponse containing the details of the result of having executed the intent

 @see  INSetDefrosterSettingsInCarIntentResponse
 */

- (void)handleSetDefrosterSettingsInCar:(INSetDefrosterSettingsInCarIntent *)intent
                             completion:(void (^)(INSetDefrosterSettingsInCarIntentResponse *response))completion NS_SWIFT_NAME(handle(setDefrosterSettingsInCar:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  setDefrosterSettingsInCarIntent The input intent
 @param  completion The response block contains an INSetDefrosterSettingsInCarIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetDefrosterSettingsInCarIntentResponse

 */

- (void)confirmSetDefrosterSettingsInCar:(INSetDefrosterSettingsInCarIntent *)intent
                              completion:(void (^)(INSetDefrosterSettingsInCarIntentResponse *response))completion NS_SWIFT_NAME(confirm(setDefrosterSettingsInCar:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  setDefrosterSettingsInCarIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveEnableForSetDefrosterSettingsInCar:(INSetDefrosterSettingsInCarIntent *)intent
                                   withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnable(forSetDefrosterSettingsInCar:with:));

- (void)resolveDefrosterForSetDefrosterSettingsInCar:(INSetDefrosterSettingsInCarIntent *)intent
                                      withCompletion:(void (^)(INCarDefrosterResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDefroster(forSetDefrosterSettingsInCar:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCancelWorkoutIntentResponse.h
//
//  INCancelWorkoutIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INCancelWorkoutIntentResponseCode) {
    INCancelWorkoutIntentResponseCodeUnspecified = 0,
    INCancelWorkoutIntentResponseCodeReady,
    INCancelWorkoutIntentResponseCodeContinueInApp,
    INCancelWorkoutIntentResponseCodeFailure,
    INCancelWorkoutIntentResponseCodeFailureRequiringAppLaunch,
    INCancelWorkoutIntentResponseCodeFailureNoMatchingWorkout,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
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
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarAirCirculationMode.h>
#import <Intents/INCarSeat.h>
#import <Intents/INRelativeSetting.h>

@class INBooleanResolutionResult;
@class INCarAirCirculationModeResolutionResult;
@class INIntegerResolutionResult;
@class INDoubleResolutionResult;
@class INRelativeSettingResolutionResult;
@class INTemperatureResolutionResult;
@class INCarSeatResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
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
                      climateZone:(INCarSeat)climateZone NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

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

@end

@class INSetClimateSettingsInCarIntentResponse;

/*!
 @brief Protocol to declare support for handling an INSetClimateSettingsInCarIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INSetClimateSettingsInCarIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INSetClimateSettingsInCarIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  setClimateSettingsInCarIntent The input intent
 @param  completion The response handling block takes a INSetClimateSettingsInCarIntentResponse containing the details of the result of having executed the intent

 @see  INSetClimateSettingsInCarIntentResponse
 */

- (void)handleSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                           completion:(void (^)(INSetClimateSettingsInCarIntentResponse *response))completion NS_SWIFT_NAME(handle(setClimateSettingsInCar:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  setClimateSettingsInCarIntent The input intent
 @param  completion The response block contains an INSetClimateSettingsInCarIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetClimateSettingsInCarIntentResponse

 */

- (void)confirmSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                            completion:(void (^)(INSetClimateSettingsInCarIntentResponse *response))completion NS_SWIFT_NAME(confirm(setClimateSettingsInCar:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  setClimateSettingsInCarIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveEnableFanForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                    withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableFan(forSetClimateSettingsInCar:with:));

- (void)resolveEnableAirConditionerForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                               withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableAirConditioner(forSetClimateSettingsInCar:with:));

- (void)resolveEnableClimateControlForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                               withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableClimateControl(forSetClimateSettingsInCar:with:));

- (void)resolveEnableAutoModeForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                         withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableAutoMode(forSetClimateSettingsInCar:with:));

- (void)resolveAirCirculationModeForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                             withCompletion:(void (^)(INCarAirCirculationModeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAirCirculationMode(forSetClimateSettingsInCar:with:));

- (void)resolveFanSpeedIndexForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                        withCompletion:(void (^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveFanSpeedIndex(forSetClimateSettingsInCar:with:));

- (void)resolveFanSpeedPercentageForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                             withCompletion:(void (^)(INDoubleResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveFanSpeedPercentage(forSetClimateSettingsInCar:with:));

- (void)resolveRelativeFanSpeedSettingForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                                  withCompletion:(void (^)(INRelativeSettingResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRelativeFanSpeedSetting(forSetClimateSettingsInCar:with:));

- (void)resolveTemperatureForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                      withCompletion:(void (^)(INTemperatureResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTemperature(forSetClimateSettingsInCar:with:));

- (void)resolveRelativeTemperatureSettingForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                                     withCompletion:(void (^)(INRelativeSettingResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRelativeTemperatureSetting(forSetClimateSettingsInCar:with:));

- (void)resolveClimateZoneForSetClimateSettingsInCar:(INSetClimateSettingsInCarIntent *)intent
                                      withCompletion:(void (^)(INCarSeatResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveClimateZone(forSetClimateSettingsInCar:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCarAirCirculationModeResolutionResult.h
//
//  INCarAirCirculationModeResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarAirCirculationMode.h>

NS_ASSUME_NONNULL_BEGIN

@interface INCarAirCirculationModeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedValue:(INCarAirCirculationMode)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(INCarAirCirculationMode)valueToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRequestPaymentIntentResponse.h
//
//  INRequestPaymentIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
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
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
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
// ==========  Intents.framework/Headers/INImage.h
//
//  INImage.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class NSData;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INImage : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)imageNamed:(NSString *)name;
+ (instancetype)imageWithImageData:(NSData *)imageData;
+ (instancetype)imageWithURL:(NSURL *)URL;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetProfileInCarIntent.h
//
//  INSetProfileInCarIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INIntegerResolutionResult;
@class INBooleanResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INSetProfileInCarIntent : INIntent

- (instancetype)initWithProfileNumber:(nullable NSNumber *)profileNumber
                         profileLabel:(nullable NSString *)profileLabel
                       defaultProfile:(nullable NSNumber *)defaultProfile NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *profileNumber NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *profileLabel;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *defaultProfile NS_REFINED_FOR_SWIFT;

@end

@class INSetProfileInCarIntentResponse;

/*!
 @brief Protocol to declare support for handling an INSetProfileInCarIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INSetProfileInCarIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INSetProfileInCarIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  setProfileInCarIntent The input intent
 @param  completion The response handling block takes a INSetProfileInCarIntentResponse containing the details of the result of having executed the intent

 @see  INSetProfileInCarIntentResponse
 */

- (void)handleSetProfileInCar:(INSetProfileInCarIntent *)intent
                   completion:(void (^)(INSetProfileInCarIntentResponse *response))completion NS_SWIFT_NAME(handle(setProfileInCar:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  setProfileInCarIntent The input intent
 @param  completion The response block contains an INSetProfileInCarIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetProfileInCarIntentResponse

 */

- (void)confirmSetProfileInCar:(INSetProfileInCarIntent *)intent
                    completion:(void (^)(INSetProfileInCarIntentResponse *response))completion NS_SWIFT_NAME(confirm(setProfileInCar:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  setProfileInCarIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveProfileNumberForSetProfileInCar:(INSetProfileInCarIntent *)intent
                                withCompletion:(void (^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveProfileNumber(forSetProfileInCar:with:));

- (void)resolveDefaultProfileForSetProfileInCar:(INSetProfileInCarIntent *)intent
                                 withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDefaultProfile(forSetProfileInCar:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRidePhase.h
//
//  INRidePhase.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
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
};

#endif // INRidePhase_h
// ==========  Intents.framework/Headers/INRideFareLineItem.h
//
//  INRideFareLineItem.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_CLASS_AVAILABLE(NA, 10_0) __TVOS_PROHIBITED __WATCHOS_AVAILABLE(3_0)
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
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INWorkoutLocationType_h
#define INWorkoutLocationType_h

#import <Foundation/Foundation.h>

#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INWorkoutLocationType) {
    INWorkoutLocationTypeUnknown = 0,
    INWorkoutLocationTypeOutdoor,
    INWorkoutLocationTypeIndoor,
};

#endif // INWorkoutLocationType_h
// ==========  Intents.framework/Headers/INGetRestaurantGuestIntent.h
//
//  INGetRestaurantGuestIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INGetRestaurantGuestIntent : INIntent

@end

@class INGetRestaurantGuestIntentResponse;

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INGetRestaurantGuestIntentHandling <NSObject>

/*!
 @brief handling method
 
 @abstract Execute the task represented by the INGetRestaurantGuestIntent that's passed in
 @discussion This method are called to actually execute the intent, the app must return a response for this intent and an NSUserActivity capturing the state that the app must be restored to at the end of handling this intent
 
 @param  guestIntent The input intent
 @param  completion The response handling block to invoke with the response to handling the intent.
 
 @see  INGetRestaurantGuestIntentResponse
 
 */
- (void)handleGetRestaurantGuest:(INGetRestaurantGuestIntent *)intent completion:(void (^)(INGetRestaurantGuestIntentResponse *response))completion NS_SWIFT_NAME(handle(getRestaurantGuest:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
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
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INRelativeSetting.h>

NS_ASSUME_NONNULL_BEGIN

@interface INRelativeSettingResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedValue:(INRelativeSetting)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(INRelativeSetting)valueToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/Intents.h
//
//  Intents.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
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

// Intents & Intent Responses
#import <Intents/INIntents.h>
#import <Intents/INIntentResponses.h>

// Extension
#import <Intents/INExtension.h>

// Common Types
#import <Intents/INPersonHandle.h>
#import <Intents/INCurrencyAmount.h>
#import <Intents/INDateComponentsRange.h>
#import <Intents/INImage.h>
#import <Intents/INPaymentMethod.h>
#import <Intents/INPaymentMethodType.h>
#import <Intents/INPerson.h>
#import <Intents/INSpeakableString.h>

// Common Resolution Results
#import <Intents/INBooleanResolutionResult.h>
#import <Intents/INCurrencyAmountResolutionResult.h>
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

// Calls Domain
#import <Intents/INSearchCallHistoryIntent.h>
#import <Intents/INSearchCallHistoryIntentResponse.h>
#import <Intents/INStartAudioCallIntent.h>
#import <Intents/INStartAudioCallIntentResponse.h>
#import <Intents/INStartVideoCallIntent.h>
#import <Intents/INStartVideoCallIntentResponse.h>

#import <Intents/INCallRecordType.h>
#import <Intents/INCallRecordTypeResolutionResult.h>
#import <Intents/INCallCapabilityOptions.h>

// CarPlay & Radio Domains
#import <Intents/INSetAudioSourceInCarIntent.h>
#import <Intents/INSetAudioSourceInCarIntentResponse.h>
#import <Intents/INSetClimateSettingsInCarIntent.h>
#import <Intents/INSetClimateSettingsInCarIntentResponse.h>
#import <Intents/INSetDefrosterSettingsInCarIntent.h>
#import <Intents/INSetDefrosterSettingsInCarIntentResponse.h>
#import <Intents/INSetSeatSettingsInCarIntent.h>
#import <Intents/INSetSeatSettingsInCarIntentResponse.h>
#import <Intents/INSetProfileInCarIntent.h>
#import <Intents/INSetProfileInCarIntentResponse.h>
#import <Intents/INSaveProfileInCarIntent.h>
#import <Intents/INSaveProfileInCarIntentResponse.h>
#import <Intents/INSetRadioStationIntent.h>
#import <Intents/INSetRadioStationIntentResponse.h>

#import <Intents/INCarAudioSource.h>
#import <Intents/INCarAudioSourceResolutionResult.h>
#import <Intents/INCarAirCirculationMode.h>
#import <Intents/INCarAirCirculationModeResolutionResult.h>
#import <Intents/INCarDefroster.h>
#import <Intents/INCarDefrosterResolutionResult.h>
#import <Intents/INCarSeat.h>
#import <Intents/INCarSeatResolutionResult.h>
#import <Intents/INRadioType.h>
#import <Intents/INRadioTypeResolutionResult.h>
#import <Intents/INRelativeReference.h>
#import <Intents/INRelativeReferenceResolutionResult.h>
#import <Intents/INRelativeSetting.h>
#import <Intents/INRelativeSettingResolutionResult.h>

// Messages Domain
#import <Intents/INSearchForMessagesIntent.h>
#import <Intents/INSearchForMessagesIntentResponse.h>
#import <Intents/INSendMessageIntent.h>
#import <Intents/INSendMessageIntentResponse.h>
#import <Intents/INSetMessageAttributeIntent.h>
#import <Intents/INSetMessageAttributeIntentResponse.h>

#import <Intents/INMessage.h>
#import <Intents/INMessageAttribute.h>
#import <Intents/INMessageAttributeResolutionResult.h>
#import <Intents/INMessageAttributeOptions.h>
#import <Intents/INMessageAttributeOptionsResolutionResult.h>

// Payments Domain
#import <Intents/INSendPaymentIntent.h>
#import <Intents/INSendPaymentIntentResponse.h>
#import <Intents/INRequestPaymentIntent.h>
#import <Intents/INRequestPaymentIntentResponse.h>

#import <Intents/INPaymentRecord.h>
#import <Intents/INPaymentStatus.h>

// Photos Domain
#import <Intents/INSearchForPhotosIntent.h>
#import <Intents/INSearchForPhotosIntentResponse.h>
#import <Intents/INStartPhotoPlaybackIntent.h>
#import <Intents/INStartPhotoPlaybackIntentResponse.h>

#import <Intents/INPhotoAttributeOptions.h>

// Ridesharing Domain
#import <Intents/INListRideOptionsIntent.h>
#import <Intents/INListRideOptionsIntentResponse.h>
#import <Intents/INRequestRideIntent.h>
#import <Intents/INRequestRideIntentResponse.h>
#import <Intents/INGetRideStatusIntent.h>
#import <Intents/INGetRideStatusIntentResponse.h>

#import <Intents/INPriceRange.h>
#import <Intents/INRideOption.h>
#import <Intents/INRideStatus.h>
#import <Intents/INRidePhase.h>
#import <Intents/INRideDriver.h>
#import <Intents/INRideVehicle.h>
#import <Intents/INRideFareLineItem.h>
#import <Intents/INRidePartySizeOption.h>
#import <Intents/INRideCompletionStatus.h>

// Workouts Domain
#import <Intents/INStartWorkoutIntent.h>
#import <Intents/INStartWorkoutIntentResponse.h>
#import <Intents/INPauseWorkoutIntent.h>
#import <Intents/INPauseWorkoutIntentResponse.h>
#import <Intents/INEndWorkoutIntent.h>
#import <Intents/INEndWorkoutIntentResponse.h>
#import <Intents/INCancelWorkoutIntent.h>
#import <Intents/INCancelWorkoutIntentResponse.h>
#import <Intents/INResumeWorkoutIntent.h>
#import <Intents/INResumeWorkoutIntentResponse.h>

#import <Intents/INWorkoutGoalUnitType.h>
#import <Intents/INWorkoutGoalUnitTypeResolutionResult.h>
#import <Intents/INWorkoutLocationType.h>
#import <Intents/INWorkoutLocationTypeResolutionResult.h>

// Restaurant Booking
#import <Intents/INIntentRestaurantReservation.h>

// User Vocabulary
#import <Intents/INVocabulary.h>

// Utilities
#import <Intents/INSiriAuthorizationStatus.h>
#import <Intents/INPreferences.h>
#import <Intents/CLPlacemark+IntentsAdditions.h>
#import <Intents/NSUserActivity+IntentsAdditions.h>
#import <Intents/INPerson+SiriAdditions.h>
// ==========  Intents.framework/Headers/INSendPaymentIntent.h
//
//  INSendPaymentIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INPerson;
@class INPersonResolutionResult;
@class INCurrencyAmount;
@class INCurrencyAmountResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
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
 @brief Protocol to declare support for handling an INSendPaymentIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INSendPaymentIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INSendPaymentIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  sendPaymentIntent The input intent
 @param  completion The response handling block takes a INSendPaymentIntentResponse containing the details of the result of having executed the intent

 @see  INSendPaymentIntentResponse
 */

- (void)handleSendPayment:(INSendPaymentIntent *)intent
               completion:(void (^)(INSendPaymentIntentResponse *response))completion NS_SWIFT_NAME(handle(sendPayment:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  sendPaymentIntent The input intent
 @param  completion The response block contains an INSendPaymentIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSendPaymentIntentResponse

 */

- (void)confirmSendPayment:(INSendPaymentIntent *)intent
                completion:(void (^)(INSendPaymentIntentResponse *response))completion NS_SWIFT_NAME(confirm(sendPayment:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  sendPaymentIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolvePayeeForSendPayment:(INSendPaymentIntent *)intent
                    withCompletion:(void (^)(INPersonResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePayee(forSendPayment:with:));

- (void)resolveCurrencyAmountForSendPayment:(INSendPaymentIntent *)intent
                             withCompletion:(void (^)(INCurrencyAmountResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCurrencyAmount(forSendPayment:with:));

- (void)resolveNoteForSendPayment:(INSendPaymentIntent *)intent
                   withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveNote(forSendPayment:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRideStatus.h
//
//  INRideStatus.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INRidePhase.h>

@class CLPlacemark;
@class INRideVehicle;
@class INRideDriver;
@class INRideOption;
@class INRideCompletionStatus;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(NA, 10_0) __TVOS_PROHIBITED __WATCHOS_AVAILABLE(3_0)
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
//  Copyright © 2016 Apple. All rights reserved.
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
};

#endif // INMessageAttributeOptions_h
// ==========  Intents.framework/Headers/INIntentResponse.h
//
//  INIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INIntentResponse : NSObject <NSCopying, NSSecureCoding>

// This user activity will be used to launch the containing application when host application finds appropriate or when users request so.
// The containing application should implement the continuity app delegate method(s) to consume this user activity.
@property (copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSUserActivity *userActivity;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSpeakable.h
//
//  INSpeakable.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol INSpeakable <NSObject>

@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *spokenPhrase;
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *pronunciationHint;
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

@end
// ==========  Intents.framework/Headers/INRequestRideIntentResponse.h
//
//  INRequestRideIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INRideStatus;

typedef NS_ENUM(NSInteger, INRequestRideIntentResponseCode) {
    INRequestRideIntentResponseCodeUnspecified = 0,
    INRequestRideIntentResponseCodeReady,
    INRequestRideIntentResponseCodeInProgress,
    INRequestRideIntentResponseCodeSuccess,
    INRequestRideIntentResponseCodeFailure,
    INRequestRideIntentResponseCodeFailureRequiringAppLaunch,
    INRequestRideIntentResponseCodeFailureRequiringAppLaunchMustVerifyCredentials,
    INRequestRideIntentResponseCodeFailureRequiringAppLaunchNoServiceInArea,
    INRequestRideIntentResponseCodeFailureRequiringAppLaunchServiceTemporarilyUnavailable,
    INRequestRideIntentResponseCodeFailureRequiringAppLaunchPreviousRideNeedsCompletion,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
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
// ==========  Intents.framework/Headers/INPersonHandle.h
//
//  INPersonHandle.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, INPersonHandleType) {
    INPersonHandleTypeUnknown = 0,
    INPersonHandleTypeEmailAddress,
    INPersonHandleTypePhoneNumber,
} API_AVAILABLE(macosx(10.12), ios(10.0));

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INPersonHandle : NSObject <NSCopying, NSSecureCoding>

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *value;
@property (readonly, NS_NONATOMIC_IOSONLY) INPersonHandleType type;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithValue:(NSString *)value type:(INPersonHandleType)type NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetAudioSourceInCarIntent.h
//
//  INSetAudioSourceInCarIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarAudioSource.h>
#import <Intents/INRelativeReference.h>

@class INCarAudioSourceResolutionResult;
@class INRelativeReferenceResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INSetAudioSourceInCarIntent : INIntent

- (instancetype)initWithAudioSource:(INCarAudioSource)audioSource
       relativeAudioSourceReference:(INRelativeReference)relativeAudioSourceReference NS_DESIGNATED_INITIALIZER;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCarAudioSource audioSource;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INRelativeReference relativeAudioSourceReference;

@end

@class INSetAudioSourceInCarIntentResponse;

/*!
 @brief Protocol to declare support for handling an INSetAudioSourceInCarIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INSetAudioSourceInCarIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INSetAudioSourceInCarIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  setAudioSourceInCarIntent The input intent
 @param  completion The response handling block takes a INSetAudioSourceInCarIntentResponse containing the details of the result of having executed the intent

 @see  INSetAudioSourceInCarIntentResponse
 */

- (void)handleSetAudioSourceInCar:(INSetAudioSourceInCarIntent *)intent
                       completion:(void (^)(INSetAudioSourceInCarIntentResponse *response))completion NS_SWIFT_NAME(handle(setAudioSourceInCar:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  setAudioSourceInCarIntent The input intent
 @param  completion The response block contains an INSetAudioSourceInCarIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetAudioSourceInCarIntentResponse

 */

- (void)confirmSetAudioSourceInCar:(INSetAudioSourceInCarIntent *)intent
                        completion:(void (^)(INSetAudioSourceInCarIntentResponse *response))completion NS_SWIFT_NAME(confirm(setAudioSourceInCar:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  setAudioSourceInCarIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveAudioSourceForSetAudioSourceInCar:(INSetAudioSourceInCarIntent *)intent
                                  withCompletion:(void (^)(INCarAudioSourceResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAudioSource(forSetAudioSourceInCar:with:));

- (void)resolveRelativeAudioSourceReferenceForSetAudioSourceInCar:(INSetAudioSourceInCarIntent *)intent
                                                   withCompletion:(void (^)(INRelativeReferenceResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRelativeAudioSourceReference(forSetAudioSourceInCar:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INExtension.h
//
//  INExtension.h
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INIntentHandlerProviding.h>

NS_ASSUME_NONNULL_BEGIN

@interface INExtension : NSObject <INIntentHandlerProviding>
@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCancelWorkoutIntent.h
//
//  INCancelWorkoutIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INCancelWorkoutIntent : INIntent

- (instancetype)initWithWorkoutName:(nullable INSpeakableString *)workoutName NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *workoutName;

@end

@class INCancelWorkoutIntentResponse;

/*!
 @brief Protocol to declare support for handling an INCancelWorkoutIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INCancelWorkoutIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INCancelWorkoutIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  cancelWorkoutIntent The input intent
 @param  completion The response handling block takes a INCancelWorkoutIntentResponse containing the details of the result of having executed the intent

 @see  INCancelWorkoutIntentResponse
 */

- (void)handleCancelWorkout:(INCancelWorkoutIntent *)intent
                 completion:(void (^)(INCancelWorkoutIntentResponse *response))completion NS_SWIFT_NAME(handle(cancelWorkout:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  cancelWorkoutIntent The input intent
 @param  completion The response block contains an INCancelWorkoutIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INCancelWorkoutIntentResponse

 */

- (void)confirmCancelWorkout:(INCancelWorkoutIntent *)intent
                  completion:(void (^)(INCancelWorkoutIntentResponse *response))completion NS_SWIFT_NAME(confirm(cancelWorkout:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  cancelWorkoutIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveWorkoutNameForCancelWorkout:(INCancelWorkoutIntent *)intent
                            withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutName(forCancelWorkout:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPaymentStatus.h
//
//  INPaymentStatus.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
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
};

#endif // INPaymentStatus_h
// ==========  Intents.framework/Headers/INPerson+SiriAdditions.h
//
//  INPerson+SiriAdditions.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INPerson.h>

#import <Intents/INSpeakable.h>

NS_ASSUME_NONNULL_BEGIN

@interface INPerson (SiriAdditions) <INSpeakable>
@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INResumeWorkoutIntentResponse.h
//
//  INResumeWorkoutIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INResumeWorkoutIntentResponseCode) {
    INResumeWorkoutIntentResponseCodeUnspecified = 0,
    INResumeWorkoutIntentResponseCodeReady,
    INResumeWorkoutIntentResponseCodeContinueInApp,
    INResumeWorkoutIntentResponseCodeFailure,
    INResumeWorkoutIntentResponseCodeFailureRequiringAppLaunch,
    INResumeWorkoutIntentResponseCodeFailureNoMatchingWorkout,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
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
// ==========  Intents.framework/Headers/INRadioType.h
//
//  INRadioType.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
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
};

#endif // INRadioType_h
// ==========  Intents.framework/Headers/INIntentIdentifiers.h
//
//  INIntentIdentifiers.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/IntentsDefines.h>

// Identifier for INStartAudioCallIntent class.
INTENTS_EXTERN NSString *const INStartAudioCallIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0));

// Identifier for INStartVideoCallIntent class.
INTENTS_EXTERN NSString *const INStartVideoCallIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0));

// Identifier for INSearchCallHistoryIntent class.
INTENTS_EXTERN NSString *const INSearchCallHistoryIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0));

// Identifier for INSetAudioSourceInCarIntent class.
INTENTS_EXTERN NSString *const INSetAudioSourceInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INSetClimateSettingsInCarIntent class.
INTENTS_EXTERN NSString *const INSetClimateSettingsInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INSetDefrosterSettingsInCarIntent class.
INTENTS_EXTERN NSString *const INSetDefrosterSettingsInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INSetSeatSettingsInCarIntent class.
INTENTS_EXTERN NSString *const INSetSeatSettingsInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INSetProfileInCarIntent class.
INTENTS_EXTERN NSString *const INSetProfileInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INSaveProfileInCarIntent class.
INTENTS_EXTERN NSString *const INSaveProfileInCarIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INStartWorkoutIntent class.
INTENTS_EXTERN NSString *const INStartWorkoutIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INPauseWorkoutIntent class.
INTENTS_EXTERN NSString *const INPauseWorkoutIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INEndWorkoutIntent class.
INTENTS_EXTERN NSString *const INEndWorkoutIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INCancelWorkoutIntent class.
INTENTS_EXTERN NSString *const INCancelWorkoutIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INResumeWorkoutIntent class.
INTENTS_EXTERN NSString *const INResumeWorkoutIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INSetRadioStationIntent class.
INTENTS_EXTERN NSString *const INSetRadioStationIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INSendMessageIntent class.
INTENTS_EXTERN NSString *const INSendMessageIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0));

// Identifier for INSearchForMessagesIntent class.
INTENTS_EXTERN NSString *const INSearchForMessagesIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0));

// Identifier for INSetMessageAttributeIntent class.
INTENTS_EXTERN NSString *const INSetMessageAttributeIntentIdentifier API_AVAILABLE(macosx(10.12), ios(10.0));

// Identifier for INSendPaymentIntent class.
INTENTS_EXTERN NSString *const INSendPaymentIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INRequestPaymentIntent class.
INTENTS_EXTERN NSString *const INRequestPaymentIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INSearchForPhotosIntent class.
INTENTS_EXTERN NSString *const INSearchForPhotosIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INStartPhotoPlaybackIntent class.
INTENTS_EXTERN NSString *const INStartPhotoPlaybackIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INListRideOptionsIntent class.
INTENTS_EXTERN NSString *const INListRideOptionsIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INRequestRideIntent class.
INTENTS_EXTERN NSString *const INRequestRideIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

// Identifier for INGetRideStatusIntent class.
INTENTS_EXTERN NSString *const INGetRideStatusIntentIdentifier API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);
// ==========  Intents.framework/Headers/INListRideOptionsIntentResponse.h
//
//  INListRideOptionsIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INRideOption;
@class INPaymentMethod;

typedef NS_ENUM(NSInteger, INListRideOptionsIntentResponseCode) {
    INListRideOptionsIntentResponseCodeUnspecified = 0,
    INListRideOptionsIntentResponseCodeReady,
    INListRideOptionsIntentResponseCodeInProgress,
    INListRideOptionsIntentResponseCodeSuccess,
    INListRideOptionsIntentResponseCodeFailure,
    INListRideOptionsIntentResponseCodeFailureRequiringAppLaunch,
    INListRideOptionsIntentResponseCodeFailureRequiringAppLaunchMustVerifyCredentials,
    INListRideOptionsIntentResponseCodeFailureRequiringAppLaunchNoServiceInArea,
    INListRideOptionsIntentResponseCodeFailureRequiringAppLaunchServiceTemporarilyUnavailable,
    INListRideOptionsIntentResponseCodeFailureRequiringAppLaunchPreviousRideNeedsCompletion,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
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
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSearchCallHistoryIntentResponseCode) {
    INSearchCallHistoryIntentResponseCodeUnspecified = 0,
    INSearchCallHistoryIntentResponseCodeReady,
    INSearchCallHistoryIntentResponseCodeContinueInApp,
    INSearchCallHistoryIntentResponseCodeFailure,
    INSearchCallHistoryIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(macosx(10.12), ios(10.0));

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INSearchCallHistoryIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSearchCallHistoryIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSearchCallHistoryIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCallRecordTypeResolutionResult.h
//
//  INCallRecordTypeResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCallRecordType.h>

NS_ASSUME_NONNULL_BEGIN

@interface INCallRecordTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedValue:(INCallRecordType)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(INCallRecordType)valueToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSendPaymentIntentResponse.h
//
//  INSendPaymentIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
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
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
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
// ==========  Intents.framework/Headers/INSearchCallHistoryIntent.h
//
//  INSearchCallHistoryIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCallCapabilityOptions.h>
#import <Intents/INCallRecordType.h>

@class INCallRecordTypeResolutionResult;
@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INPerson;
@class INPersonResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INSearchCallHistoryIntent : INIntent

- (instancetype)initWithCallType:(INCallRecordType)callType
                     dateCreated:(nullable INDateComponentsRange *)dateCreated
                       recipient:(nullable INPerson *)recipient
                callCapabilities:(INCallCapabilityOptions)callCapabilities NS_DESIGNATED_INITIALIZER;

// What type of call record to search for.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallRecordType callType;

// Date of the call to search for in the call history.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dateCreated;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *recipient;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallCapabilityOptions callCapabilities;

@end

@class INSearchCallHistoryIntentResponse;

/*!
 @brief Protocol to declare support for handling an INSearchCallHistoryIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(macosx(10.12), ios(10.0))
@protocol INSearchCallHistoryIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INSearchCallHistoryIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  searchCallHistoryIntent The input intent
 @param  completion The response handling block takes a INSearchCallHistoryIntentResponse containing the details of the result of having executed the intent

 @see  INSearchCallHistoryIntentResponse
 */

- (void)handleSearchCallHistory:(INSearchCallHistoryIntent *)intent
                     completion:(void (^)(INSearchCallHistoryIntentResponse *response))completion NS_SWIFT_NAME(handle(searchCallHistory:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  searchCallHistoryIntent The input intent
 @param  completion The response block contains an INSearchCallHistoryIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSearchCallHistoryIntentResponse

 */

- (void)confirmSearchCallHistory:(INSearchCallHistoryIntent *)intent
                      completion:(void (^)(INSearchCallHistoryIntentResponse *response))completion NS_SWIFT_NAME(confirm(searchCallHistory:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  searchCallHistoryIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveCallTypeForSearchCallHistory:(INSearchCallHistoryIntent *)intent
                             withCompletion:(void (^)(INCallRecordTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCallType(forSearchCallHistory:with:));

- (void)resolveDateCreatedForSearchCallHistory:(INSearchCallHistoryIntent *)intent
                                withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDateCreated(forSearchCallHistory:with:));

- (void)resolveRecipientForSearchCallHistory:(INSearchCallHistoryIntent *)intent
                              withCompletion:(void (^)(INPersonResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRecipient(forSearchCallHistory:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetSeatSettingsInCarIntentResponse.h
//
//  INSetSeatSettingsInCarIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSetSeatSettingsInCarIntentResponseCode) {
    INSetSeatSettingsInCarIntentResponseCodeUnspecified = 0,
    INSetSeatSettingsInCarIntentResponseCodeReady,
    INSetSeatSettingsInCarIntentResponseCodeInProgress,
    INSetSeatSettingsInCarIntentResponseCodeSuccess,
    INSetSeatSettingsInCarIntentResponseCodeFailure,
    INSetSeatSettingsInCarIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
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
//  Copyright © 2016 Apple. All rights reserved.
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
API_UNAVAILABLE(macosx)
@interface INGetAvailableRestaurantReservationBookingDefaultsIntent : INIntent

@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurant *restaurant; // an optional restaurant that the extension may or may not use to tailor reservation defaults

@end

@class INGetAvailableRestaurantReservationBookingDefaultsIntentResponse;

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INGetAvailableRestaurantReservationBookingDefaultsIntentHandling <NSObject>

/*!
 @brief handling method
 
 @abstract Execute the task represented by the INGetAvailableRestaurantReservationBookingDefaultsIntent that's passed in
 @discussion This method are called to actually execute the intent, the app must return a response for this intent and an NSUserActivity capturing the state that the app must be restored to at the end of handling this intent
 
 @param  bookingDefaultsIntent The input intent
 @param  completion The response handling block to invoke with the response to handling the intent.
 
 @see  INGetAvailableRestaurantReservationBookingDefaultsIntentResponse
 
 */

- (void)handleGetAvailableRestaurantReservationBookingDefaults:(INGetAvailableRestaurantReservationBookingDefaultsIntent *)intent completion:(void (^)(INGetAvailableRestaurantReservationBookingDefaultsIntentResponse *response))completion NS_SWIFT_NAME(handle(getAvailableRestaurantReservationBookingDefaults:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.
 
 @param  bookingDefaultsIntent The input intent
 @param  completion The response block contains an INGetAvailableRestaurantReservationBookingDefaultsIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.
 
 @see INGetAvailableRestaurantReservationBookingDefaultsIntentResponse
 
 */

- (void)confirmGetAvailableRestaurantReservationBookingDefaults:(INGetAvailableRestaurantReservationBookingDefaultsIntent *)intent completion:(void (^)(INGetAvailableRestaurantReservationBookingDefaultsIntentResponse *response))completion NS_SWIFT_NAME(confirm(getAvailableRestaurantReservationBookingDefaults:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.
 
 @param  bookingDefaultsIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved
 
 @see INGetAvailableRestaurantReservationBookingDefaultsIntentResponse
 
 */

- (void)resolveRestaurantForGetAvailableRestaurantReservationBookingDefaults:(INGetAvailableRestaurantReservationBookingDefaultsIntent *)intent withCompletion:(void(^)(INRestaurantResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRestaurant(for:completion:));

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPerson.h
//
//  INPerson.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INImage;
@class INPersonHandle;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INPerson : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithPersonHandle:(INPersonHandle *)personHandle
                nameComponents:(nullable NSPersonNameComponents *)nameComponents
                   displayName:(nullable NSString *)displayName
                         image:(nullable INImage *)image
             contactIdentifier:(nullable NSString *)contactIdentifier
              customIdentifier:(nullable NSString *)customIdentifier NS_DESIGNATED_INITIALIZER;

// The identity of the person in the application (e.g. email address, phone number, user handle, etc.)
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *handle  NS_DEPRECATED(10_12, 10_12, 10_0, 10_0, "Use personHandle instead");

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
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *customIdentifier;

@end

@interface INPerson (INPersonCreation)

//  This is the preferred convenience initializer if the app knows the name components of the person (e.g. given name, family name, etc).
- (instancetype)initWithHandle:(NSString *)handle
                nameComponents:(NSPersonNameComponents *)nameComponents
             contactIdentifier:(nullable NSString *)contactIdentifier NS_DEPRECATED(10_12, 10_12, 10_0, 10_0, "Use the designated initializer instead");

// Use this convenience initializer if the person's name is unknown
- (instancetype)initWithHandle:(NSString *)handle
                   displayName:(nullable NSString *)displayName
             contactIdentifier:(nullable NSString *)contactIdentifier NS_DEPRECATED(10_12, 10_12, 10_0, 10_0, "Use the designated initializer instead");

- (instancetype)initWithHandle:(NSString *)handle
                nameComponents:(nullable NSPersonNameComponents *)nameComponents
                   displayName:(nullable NSString *)displayName
                         image:(nullable INImage *)image
             contactIdentifier:(nullable NSString *)contactIdentifier NS_DEPRECATED(10_12, 10_12, 10_0, 10_0, "Use the designated initializer instead");

@end

typedef NS_ENUM(NSInteger, INPersonSuggestionType) {
    INPersonSuggestionTypeSocialProfile = 1,
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
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INPerson;
@class INPersonResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INStartVideoCallIntent : INIntent

- (instancetype)initWithContacts:(nullable NSArray<INPerson *> *)contacts NS_DESIGNATED_INITIALIZER;

// Recipients of the video call.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *contacts;

@end

@class INStartVideoCallIntentResponse;

/*!
 @brief Protocol to declare support for handling an INStartVideoCallIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(macosx(10.12), ios(10.0))
@protocol INStartVideoCallIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INStartVideoCallIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  startVideoCallIntent The input intent
 @param  completion The response handling block takes a INStartVideoCallIntentResponse containing the details of the result of having executed the intent

 @see  INStartVideoCallIntentResponse
 */

- (void)handleStartVideoCall:(INStartVideoCallIntent *)intent
                  completion:(void (^)(INStartVideoCallIntentResponse *response))completion NS_SWIFT_NAME(handle(startVideoCall:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  startVideoCallIntent The input intent
 @param  completion The response block contains an INStartVideoCallIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INStartVideoCallIntentResponse

 */

- (void)confirmStartVideoCall:(INStartVideoCallIntent *)intent
                   completion:(void (^)(INStartVideoCallIntentResponse *response))completion NS_SWIFT_NAME(confirm(startVideoCall:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  startVideoCallIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveContactsForStartVideoCall:(INStartVideoCallIntent *)intent
                          withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveContacts(forStartVideoCall:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INDateComponentsRange.h
//
//  INDateComponentsRange.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INDateComponentsRange : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithStartDateComponents:(nullable NSDateComponents *)startDateComponents
                          endDateComponents:(nullable NSDateComponents *)endDateComponents NS_DESIGNATED_INITIALIZER;

@property (copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *startDateComponents;

@property (copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *endDateComponents;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSearchForPhotosIntent.h
//
//  INSearchForPhotosIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INConditionalOperator.h>
#import <Intents/INPhotoAttributeOptions.h>

@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class CLPlacemark;
@class INPlacemarkResolutionResult;
@class INStringResolutionResult;
@class INPerson;
@class INPersonResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
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
 @brief Protocol to declare support for handling an INSearchForPhotosIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INSearchForPhotosIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INSearchForPhotosIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  searchForPhotosIntent The input intent
 @param  completion The response handling block takes a INSearchForPhotosIntentResponse containing the details of the result of having executed the intent

 @see  INSearchForPhotosIntentResponse
 */

- (void)handleSearchForPhotos:(INSearchForPhotosIntent *)intent
                   completion:(void (^)(INSearchForPhotosIntentResponse *response))completion NS_SWIFT_NAME(handle(searchForPhotos:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  searchForPhotosIntent The input intent
 @param  completion The response block contains an INSearchForPhotosIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSearchForPhotosIntentResponse

 */

- (void)confirmSearchForPhotos:(INSearchForPhotosIntent *)intent
                    completion:(void (^)(INSearchForPhotosIntentResponse *response))completion NS_SWIFT_NAME(confirm(searchForPhotos:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  searchForPhotosIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveDateCreatedForSearchForPhotos:(INSearchForPhotosIntent *)intent
                              withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDateCreated(forSearchForPhotos:with:));

- (void)resolveLocationCreatedForSearchForPhotos:(INSearchForPhotosIntent *)intent
                                  withCompletion:(void (^)(INPlacemarkResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveLocationCreated(forSearchForPhotos:with:));

- (void)resolveAlbumNameForSearchForPhotos:(INSearchForPhotosIntent *)intent
                            withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAlbumName(forSearchForPhotos:with:));

- (void)resolvePeopleInPhotoForSearchForPhotos:(INSearchForPhotosIntent *)intent
                                withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolvePeopleInPhoto(forSearchForPhotos:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INGetUserCurrentRestaurantReservationBookingsIntent.h
//
//  INGetUserCurrentRestaurantReservationBookingsIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
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
API_UNAVAILABLE(macosx)
@interface INGetUserCurrentRestaurantReservationBookingsIntent : INIntent <NSCopying>

@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurant *restaurant; // optional filter to just reservations at restaurant
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *reservationIdentifier; // optional filter to reservation with exact ID

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *maximumNumberOfResults; // if the caller has a preferred maximum number of results, one can optionally be specified. a nil here leaves it up to the extension
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *earliestBookingDateForResults; // specifies the earliest booking date desired for results, including dates in the past

@end

@class INGetUserCurrentRestaurantReservationBookingsIntentResponse;

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INGetUserCurrentRestaurantReservationBookingsIntentHandling <NSObject>

/*!
 @brief handling method
 
 @abstract Execute the task represented by the INGetUserCurrentRestaurantReservationBookingsIntent that's passed in
 @discussion This method are called to actually execute the intent, the app must return a response for this intent and an NSUserActivity capturing the state that the app must be restored to at the end of handling this intent
 
 @param  showCurrentBookingsIntent The input intent
 @param  completion The response handling block to invoke with the response to handling the intent.
 
 @see  INGetUserCurrentRestaurantReservationBookingsIntentResponse
 
 */

- (void)handleGetUserCurrentRestaurantReservationBookings:(INGetUserCurrentRestaurantReservationBookingsIntent *)intent completion:(void (^)(INGetUserCurrentRestaurantReservationBookingsIntentResponse *response))completion NS_SWIFT_NAME(handle(getUserCurrentRestaurantReservationBookings:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.
 
 @param  showCurrentBookingsIntent The input intent
 @param  completion The response block contains an INGetUserCurrentRestaurantReservationBookingsIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.
 
 @see INGetUserCurrentRestaurantReservationBookingsIntentResponse
 
 */

- (void)confirmGetUserCurrentRestaurantReservationBookings:(INGetUserCurrentRestaurantReservationBookingsIntent *)intent completion:(void (^)(INGetUserCurrentRestaurantReservationBookingsIntentResponse *response))completion NS_SWIFT_NAME(confirm(getUserCurrentRestaurantReservationBookings:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.
 
 @param  showCurrentBookingsIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved
 
 @see INGetUserCurrentRestaurantReservationBookingsIntentResponse
 
 */

- (void)resolveRestaurantForGetUserCurrentRestaurantReservationBookings:(INGetUserCurrentRestaurantReservationBookingsIntent *)intent withCompletion:(void(^)(INRestaurantResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRestaurant(for:completion:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INMessageAttributeOptionsResolutionResult.h
//
//  INMessageAttributeOptionsResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INMessageAttributeOptions.h>

NS_ASSUME_NONNULL_BEGIN

@interface INMessageAttributeOptionsResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedValue:(INMessageAttributeOptions)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(INMessageAttributeOptions)valueToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INWorkoutGoalUnitTypeResolutionResult.h
//
//  INWorkoutGoalUnitTypeResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INWorkoutGoalUnitType.h>

NS_ASSUME_NONNULL_BEGIN

@interface INWorkoutGoalUnitTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedValue:(INWorkoutGoalUnitType)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(INWorkoutGoalUnitType)valueToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INBookRestaurantReservationIntentResponse.h
//
//  INBookRestaurantReservationIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
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
API_UNAVAILABLE(macosx)
@interface INBookRestaurantReservationIntentResponse : INIntentResponse

- (instancetype)initWithCode:(INBookRestaurantReservationIntentCode)code userActivity:(nullable NSUserActivity *)userActivity;

@property (readonly, NS_NONATOMIC_IOSONLY) INBookRestaurantReservationIntentCode code;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurantReservationUserBooking *userBooking; // the userBooking that has been confirmed

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/NSUserActivity+IntentsAdditions.h
//
//  NSUserActivity+IntentsAdditions.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INInteraction;

NS_ASSUME_NONNULL_BEGIN

@interface NSUserActivity (IntentsAdditions)

@property (readonly, nullable, NS_NONATOMIC_IOSONLY) INInteraction *interaction API_AVAILABLE(macosx(10.12), ios(10.0));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSetSeatSettingsInCarIntent.h
//
//  INSetSeatSettingsInCarIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarSeat.h>
#import <Intents/INRelativeSetting.h>

@class INBooleanResolutionResult;
@class INCarSeatResolutionResult;
@class INIntegerResolutionResult;
@class INRelativeSettingResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INSetSeatSettingsInCarIntent : INIntent

- (instancetype)initWithEnableHeating:(nullable NSNumber *)enableHeating
                        enableCooling:(nullable NSNumber *)enableCooling
                        enableMassage:(nullable NSNumber *)enableMassage
                                 seat:(INCarSeat)seat
                                level:(nullable NSNumber *)level
                 relativeLevelSetting:(INRelativeSetting)relativeLevelSetting NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *enableHeating NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *enableCooling NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *enableMassage NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCarSeat seat;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *level NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INRelativeSetting relativeLevelSetting;

@end

@class INSetSeatSettingsInCarIntentResponse;

/*!
 @brief Protocol to declare support for handling an INSetSeatSettingsInCarIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INSetSeatSettingsInCarIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INSetSeatSettingsInCarIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  setSeatSettingsInCarIntent The input intent
 @param  completion The response handling block takes a INSetSeatSettingsInCarIntentResponse containing the details of the result of having executed the intent

 @see  INSetSeatSettingsInCarIntentResponse
 */

- (void)handleSetSeatSettingsInCar:(INSetSeatSettingsInCarIntent *)intent
                        completion:(void (^)(INSetSeatSettingsInCarIntentResponse *response))completion NS_SWIFT_NAME(handle(setSeatSettingsInCar:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  setSeatSettingsInCarIntent The input intent
 @param  completion The response block contains an INSetSeatSettingsInCarIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetSeatSettingsInCarIntentResponse

 */

- (void)confirmSetSeatSettingsInCar:(INSetSeatSettingsInCarIntent *)intent
                         completion:(void (^)(INSetSeatSettingsInCarIntentResponse *response))completion NS_SWIFT_NAME(confirm(setSeatSettingsInCar:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  setSeatSettingsInCarIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveEnableHeatingForSetSeatSettingsInCar:(INSetSeatSettingsInCarIntent *)intent
                                     withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableHeating(forSetSeatSettingsInCar:with:));

- (void)resolveEnableCoolingForSetSeatSettingsInCar:(INSetSeatSettingsInCarIntent *)intent
                                     withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableCooling(forSetSeatSettingsInCar:with:));

- (void)resolveEnableMassageForSetSeatSettingsInCar:(INSetSeatSettingsInCarIntent *)intent
                                     withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnableMassage(forSetSeatSettingsInCar:with:));

- (void)resolveSeatForSetSeatSettingsInCar:(INSetSeatSettingsInCarIntent *)intent
                            withCompletion:(void (^)(INCarSeatResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveSeat(forSetSeatSettingsInCar:with:));

- (void)resolveLevelForSetSeatSettingsInCar:(INSetSeatSettingsInCarIntent *)intent
                             withCompletion:(void (^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveLevel(forSetSeatSettingsInCar:with:));

- (void)resolveRelativeLevelSettingForSetSeatSettingsInCar:(INSetSeatSettingsInCarIntent *)intent
                                            withCompletion:(void (^)(INRelativeSettingResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRelativeLevelSetting(forSetSeatSettingsInCar:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INGetRideStatusIntent.h
//
//  INGetRideStatusIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INGetRideStatusIntent : INIntent

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

@class INGetRideStatusIntentResponse;

@protocol INGetRideStatusIntentResponseObserver;

/*!
 @brief Protocol to declare support for handling an INGetRideStatusIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INGetRideStatusIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INGetRideStatusIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  getRideStatusIntent The input intent
 @param  completion The response handling block takes a INGetRideStatusIntentResponse containing the details of the result of having executed the intent

 @see  INGetRideStatusIntentResponse
 */

- (void)handleGetRideStatus:(INGetRideStatusIntent *)intent
                 completion:(void (^)(INGetRideStatusIntentResponse *response))completion NS_SWIFT_NAME(handle(getRideStatus:completion:));

- (void)startSendingUpdatesForGetRideStatus:(INGetRideStatusIntent *)intent
                                 toObserver:(id<INGetRideStatusIntentResponseObserver>)observer NS_SWIFT_NAME(startSendingUpdates(forGetRideStatus:to:));

- (void)stopSendingUpdatesForGetRideStatus:(INGetRideStatusIntent *)intent NS_SWIFT_NAME(stopSendingUpdates(forGetRideStatus:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  getRideStatusIntent The input intent
 @param  completion The response block contains an INGetRideStatusIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INGetRideStatusIntentResponse

 */

- (void)confirmGetRideStatus:(INGetRideStatusIntent *)intent
                  completion:(void (^)(INGetRideStatusIntentResponse *response))completion NS_SWIFT_NAME(confirm(getRideStatus:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  getRideStatusIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

@end

API_AVAILABLE(ios(10.0))
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
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INPerson;
@class INPersonResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INSendMessageIntent : INIntent

- (instancetype)initWithRecipients:(nullable NSArray<INPerson *> *)recipients
                           content:(nullable NSString *)content
                         groupName:(nullable NSString *)groupName
                       serviceName:(nullable NSString *)serviceName
                            sender:(nullable INPerson *)sender NS_DESIGNATED_INITIALIZER;

// Contacts to whom the message should be sent.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *recipients;

// Body text of the message.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *content;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *groupName;

// Specified service for the message.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *serviceName;

// The person, or account, sending the message.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *sender;

@end

@class INSendMessageIntentResponse;

/*!
 @brief Protocol to declare support for handling an INSendMessageIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(macosx(10.12), ios(10.0))
@protocol INSendMessageIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INSendMessageIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  sendMessageIntent The input intent
 @param  completion The response handling block takes a INSendMessageIntentResponse containing the details of the result of having executed the intent

 @see  INSendMessageIntentResponse
 */

- (void)handleSendMessage:(INSendMessageIntent *)intent
               completion:(void (^)(INSendMessageIntentResponse *response))completion NS_SWIFT_NAME(handle(sendMessage:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  sendMessageIntent The input intent
 @param  completion The response block contains an INSendMessageIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSendMessageIntentResponse

 */

- (void)confirmSendMessage:(INSendMessageIntent *)intent
                completion:(void (^)(INSendMessageIntentResponse *response))completion NS_SWIFT_NAME(confirm(sendMessage:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  sendMessageIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveRecipientsForSendMessage:(INSendMessageIntent *)intent
                         withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveRecipients(forSendMessage:with:));

- (void)resolveContentForSendMessage:(INSendMessageIntent *)intent
                      withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveContent(forSendMessage:with:));

- (void)resolveGroupNameForSendMessage:(INSendMessageIntent *)intent
                        withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveGroupName(forSendMessage:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPriceRange.h
//
//  INPriceRange.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx)
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
// ==========  Intents.framework/Headers/INRadioTypeResolutionResult.h
//
//  INRadioTypeResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INRadioType.h>

NS_ASSUME_NONNULL_BEGIN

@interface INRadioTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedValue:(INRadioType)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(INRadioType)valueToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPauseWorkoutIntentResponse.h
//
//  INPauseWorkoutIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INPauseWorkoutIntentResponseCode) {
    INPauseWorkoutIntentResponseCodeUnspecified = 0,
    INPauseWorkoutIntentResponseCodeReady,
    INPauseWorkoutIntentResponseCodeContinueInApp,
    INPauseWorkoutIntentResponseCodeFailure,
    INPauseWorkoutIntentResponseCodeFailureRequiringAppLaunch,
    INPauseWorkoutIntentResponseCodeFailureNoMatchingWorkout,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
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
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INStartWorkoutIntentResponseCode) {
    INStartWorkoutIntentResponseCodeUnspecified = 0,
    INStartWorkoutIntentResponseCodeReady,
    INStartWorkoutIntentResponseCodeContinueInApp,
    INStartWorkoutIntentResponseCodeFailure,
    INStartWorkoutIntentResponseCodeFailureRequiringAppLaunch,
    INStartWorkoutIntentResponseCodeFailureOngoingWorkout,
    INStartWorkoutIntentResponseCodeFailureNoMatchingWorkout,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
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
// ==========  Intents.framework/Headers/INDomainHandling.h
//
//  INDomainHandling.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntents.h>

API_AVAILABLE(macosx(10.12),ios(10.0))
@protocol INCallsDomainHandling <INStartAudioCallIntentHandling, INStartVideoCallIntentHandling, INSearchCallHistoryIntentHandling>
@end

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INCarPlayDomainHandling <INSetAudioSourceInCarIntentHandling, INSetClimateSettingsInCarIntentHandling, INSetDefrosterSettingsInCarIntentHandling, INSetSeatSettingsInCarIntentHandling, INSetProfileInCarIntentHandling, INSaveProfileInCarIntentHandling>
@end

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INWorkoutsDomainHandling <INStartWorkoutIntentHandling, INPauseWorkoutIntentHandling, INEndWorkoutIntentHandling, INCancelWorkoutIntentHandling, INResumeWorkoutIntentHandling>
@end

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INRadioDomainHandling <INSetRadioStationIntentHandling>
@end

API_AVAILABLE(macosx(10.12), ios(10.0))
@protocol INMessagesDomainHandling <INSendMessageIntentHandling, INSearchForMessagesIntentHandling, INSetMessageAttributeIntentHandling>
@end

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INPaymentsDomainHandling <INSendPaymentIntentHandling, INRequestPaymentIntentHandling>
@end

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INPhotosDomainHandling <INSearchForPhotosIntentHandling, INStartPhotoPlaybackIntentHandling>
@end

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INRidesharingDomainHandling <INListRideOptionsIntentHandling, INRequestRideIntentHandling, INGetRideStatusIntentHandling>
@end
// ==========  Intents.framework/Headers/INTermsAndConditions.h
//
//  INTermsAndConditions.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
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
//  Copyright © 2016 Apple. All rights reserved.
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
// ==========  Intents.framework/Headers/INPauseWorkoutIntent.h
//
//  INPauseWorkoutIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INPauseWorkoutIntent : INIntent

- (instancetype)initWithWorkoutName:(nullable INSpeakableString *)workoutName NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *workoutName;

@end

@class INPauseWorkoutIntentResponse;

/*!
 @brief Protocol to declare support for handling an INPauseWorkoutIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INPauseWorkoutIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INPauseWorkoutIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  pauseWorkoutIntent The input intent
 @param  completion The response handling block takes a INPauseWorkoutIntentResponse containing the details of the result of having executed the intent

 @see  INPauseWorkoutIntentResponse
 */

- (void)handlePauseWorkout:(INPauseWorkoutIntent *)intent
                completion:(void (^)(INPauseWorkoutIntentResponse *response))completion NS_SWIFT_NAME(handle(pauseWorkout:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  pauseWorkoutIntent The input intent
 @param  completion The response block contains an INPauseWorkoutIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INPauseWorkoutIntentResponse

 */

- (void)confirmPauseWorkout:(INPauseWorkoutIntent *)intent
                 completion:(void (^)(INPauseWorkoutIntentResponse *response))completion NS_SWIFT_NAME(confirm(pauseWorkout:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  pauseWorkoutIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveWorkoutNameForPauseWorkout:(INPauseWorkoutIntent *)intent
                           withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutName(forPauseWorkout:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INBooleanResolutionResult.h
//
//  INBooleanResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx)
@interface INBooleanResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedValue:(BOOL)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the boolean value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(nullable NSNumber *)valueToConfirm NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INWorkoutLocationTypeResolutionResult.h
//
//  INWorkoutLocationTypeResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INWorkoutLocationType.h>

NS_ASSUME_NONNULL_BEGIN

@interface INWorkoutLocationTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedValue:(INWorkoutLocationType)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(INWorkoutLocationType)valueToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INGetRideStatusIntentResponse.h
//
//  INGetRideStatusIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INRideStatus;

typedef NS_ENUM(NSInteger, INGetRideStatusIntentResponseCode) {
    INGetRideStatusIntentResponseCodeUnspecified = 0,
    INGetRideStatusIntentResponseCodeReady,
    INGetRideStatusIntentResponseCodeInProgress,
    INGetRideStatusIntentResponseCodeSuccess,
    INGetRideStatusIntentResponseCodeFailure,
    INGetRideStatusIntentResponseCodeFailureRequiringAppLaunch,
    INGetRideStatusIntentResponseCodeFailureRequiringAppLaunchMustVerifyCredentials,
    INGetRideStatusIntentResponseCodeFailureRequiringAppLaunchServiceTemporarilyUnavailable,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
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
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INPerson;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INPersonResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given person. The resolvedPerson need not be identical to the input person. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
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
//  Copyright © 2016 Apple. All rights reserved.
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
};

#endif // INRelativeSetting_h
// ==========  Intents.framework/Headers/INCarAirCirculationMode.h
//
//  INCarAirCirculationMode.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INCarAirCirculationMode_h
#define INCarAirCirculationMode_h

#import <Foundation/Foundation.h>

#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCarAirCirculationMode) {
    INCarAirCirculationModeUnknown = 0,
    INCarAirCirculationModeFreshAir,
    INCarAirCirculationModeRecirculateAir,
};

#endif // INCarAirCirculationMode_h
// ==========  Intents.framework/Headers/INSetProfileInCarIntentResponse.h
//
//  INSetProfileInCarIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSetProfileInCarIntentResponseCode) {
    INSetProfileInCarIntentResponseCodeUnspecified = 0,
    INSetProfileInCarIntentResponseCodeReady,
    INSetProfileInCarIntentResponseCodeInProgress,
    INSetProfileInCarIntentResponseCodeSuccess,
    INSetProfileInCarIntentResponseCodeFailure,
    INSetProfileInCarIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
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
//  Copyright © 2016 Apple. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntent.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
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
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSendMessageIntentResponseCode) {
    INSendMessageIntentResponseCodeUnspecified = 0,
    INSendMessageIntentResponseCodeReady,
    INSendMessageIntentResponseCodeInProgress,
    INSendMessageIntentResponseCodeSuccess,
    INSendMessageIntentResponseCodeFailure,
    INSendMessageIntentResponseCodeFailureRequiringAppLaunch,
    INSendMessageIntentResponseCodeFailureMessageServiceNotAvailable,
} API_AVAILABLE(macosx(10.12), ios(10.0));

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INSendMessageIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INSendMessageIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INSendMessageIntentResponseCode code;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRestaurant.h
//
//  INRestaurant.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntent.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INRestaurant : NSObject <NSSecureCoding, NSCopying>

- (instancetype)initWithLocation:(CLLocation *)location name:(NSString *)name vendorIdentifier:(NSString *)vendorIdentifier restaurantIdentifier:(NSString *)restaurantIdentifier NS_DESIGNATED_INITIALIZER;

@property (copy, NS_NONATOMIC_IOSONLY) CLLocation *location;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *name;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *vendorIdentifier; // provider's vendor identifier
@property (copy, NS_NONATOMIC_IOSONLY) NSString *restaurantIdentifier; // vendor specific restaurant identifier. should match what Maps is ingesting through its data pipeline for the vendor.

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INMessageAttribute.h
//
//  INMessageAttribute.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
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
};

#endif // INMessageAttribute_h
// ==========  Intents.framework/Headers/INRideVehicle.h
//
//  INRideVehicle.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CLLocation;
@class INImage;

NS_CLASS_AVAILABLE(NA, 10_0) __TVOS_PROHIBITED __WATCHOS_AVAILABLE(3_0)
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
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INCurrencyAmount;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(NA, 10_0) __TVOS_PROHIBITED __WATCHOS_PROHIBITED
@interface INRideCompletionStatus: NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

// The ride completed.
+ (instancetype)completed;

// The ride completed. The fare in the provided amount was successfully paid; this amount may be displayed to the user.
+ (instancetype)completedWithSettledPaymentAmount:(INCurrencyAmount *)settledPaymentAmount NS_SWIFT_NAME(completed(settled:));

// The ride completed but there is a payment outstanding that the user needs to settle in the application.
// The .completionUserActivity should be set, and will be continued in your application to perform payment tasks.
+ (instancetype)completedWithOutstandingPaymentAmount:(INCurrencyAmount *)outstandingPaymentAmount NS_SWIFT_NAME(completed(outstanding:));

// The ride was canceled by the service (e.g. because the driver asked to cancel)
+ (instancetype)canceledByService;

// The ride was canceled by the user (e.g. by doing so through your application)
+ (instancetype)canceledByUser;

// The ride was canceled by the service because the passenger was not present for pickup and the vehicle maximum wait time elapsed.
+ (instancetype)canceledMissedPickup;

// If this property is set, UI may be shown to the user to complete post-ride tasks (e.g. for feedback or settling outstanding payment). Acting on that UI will continue this activity in your application.
@property (readwrite, strong, nullable, NS_NONATOMIC_IOSONLY) NSUserActivity *completionUserActivity;

// YES if the ride was completed.
@property (readonly, NS_NONATOMIC_IOSONLY, getter=isCompleted) BOOL completed;

// YES if the ride was canceled.
@property (readonly, NS_NONATOMIC_IOSONLY, getter=isCanceled) BOOL canceled;

// YES if the user missed the pickup. This is only YES if .canceled is YES.
@property (readonly, NS_NONATOMIC_IOSONLY, getter=isMissedPickup) BOOL missedPickup;

// The payment amount, if any.
@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *paymentAmount;

// Whether the payment is outstanding (YES) or settled (NO).
@property (readonly, NS_NONATOMIC_IOSONLY, getter=isOutstanding) BOOL outstanding;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INIntent.h
//
//  INIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INIntent : NSObject <NSCopying, NSSecureCoding>

// Returns the identifier of the receiver.
// Could be used to keep track of the entire transaction for resolve, confirm and handleIntent
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCurrencyAmount.h
//
//  INCurrencyAmount.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx)
@interface INCurrencyAmount : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithAmount:(NSDecimalNumber *)amount
                  currencyCode:(NSString *)currencyCode NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDecimalNumber *amount;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *currencyCode;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/IntentsDefines.h
//
//  IntentsDefines.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Availability.h>

#ifdef __cplusplus
#define INTENTS_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define INTENTS_EXTERN extern __attribute__((visibility ("default")))
#endif
// ==========  Intents.framework/Headers/INPlacemarkResolutionResult.h
//
//  INPlacemarkResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class CLPlacemark;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INPlacemarkResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given placemark. The resolvedPlacemark need not be identical to the input placemark. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
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
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INCallCapabilityOptions_h
#define INCallCapabilityOptions_h

#import <Foundation/Foundation.h>

#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INCallCapabilityOptions) {
    INCallCapabilityOptionAudioCall = (1UL << 0),
    INCallCapabilityOptionVideoCall = (1UL << 1),
};

#endif // INCallCapabilityOptions_h
// ==========  Intents.framework/Headers/INDateComponentsRangeResolutionResult.h
//
//  INDateComponentsRangeResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INDateComponentsRange;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INDateComponentsRangeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given date components range. The resolvedDateComponentsRange need not be identical to the input date components range. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
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
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INPerson;
@class INPersonResolutionResult;
@class INCurrencyAmount;
@class INCurrencyAmountResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
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
 @brief Protocol to declare support for handling an INRequestPaymentIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INRequestPaymentIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INRequestPaymentIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  requestPaymentIntent The input intent
 @param  completion The response handling block takes a INRequestPaymentIntentResponse containing the details of the result of having executed the intent

 @see  INRequestPaymentIntentResponse
 */

- (void)handleRequestPayment:(INRequestPaymentIntent *)intent
                  completion:(void (^)(INRequestPaymentIntentResponse *response))completion NS_SWIFT_NAME(handle(requestPayment:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  requestPaymentIntent The input intent
 @param  completion The response block contains an INRequestPaymentIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INRequestPaymentIntentResponse

 */

- (void)confirmRequestPayment:(INRequestPaymentIntent *)intent
                   completion:(void (^)(INRequestPaymentIntentResponse *response))completion NS_SWIFT_NAME(confirm(requestPayment:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  requestPaymentIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolvePayerForRequestPayment:(INRequestPaymentIntent *)intent
                       withCompletion:(void (^)(INPersonResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePayer(forRequestPayment:with:));

- (void)resolveCurrencyAmountForRequestPayment:(INRequestPaymentIntent *)intent
                                withCompletion:(void (^)(INCurrencyAmountResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCurrencyAmount(forRequestPayment:with:));

- (void)resolveNoteForRequestPayment:(INRequestPaymentIntent *)intent
                      withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveNote(forRequestPayment:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INSpeakableString.h
//
//  INSpeakableString.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INSpeakable.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INSpeakableString : NSObject <INSpeakable>

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithIdentifier:(NSString *)identifier
                   spokenPhrase:(NSString *)spokenPhrase
                   pronunciationHint:(nullable NSString *)pronunciationHint NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

// ==========  Intents.framework/Headers/INIntentResolutionResult.h
//
//  INIntentResolution.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INIntentResolutionResult<ObjectType> : NSObject

- (instancetype)init NS_UNAVAILABLE;

// This result is to tell Siri that the user must provide a non-nil value for this parameter in order to continue
+ (instancetype)needsValue NS_SWIFT_NAME(needsValue());

// This result is to tell Siri to continue whether or the user has provided a value for this parameter
+ (instancetype)notRequired NS_SWIFT_NAME(notRequired());

// This result is for informing Siri that this value is unsupported
+ (instancetype)unsupported NS_SWIFT_NAME(unsupported());

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INGetAvailableRestaurantReservationBookingsIntentResponse.h
//
//  INGetAvailableRestaurantReservationBookingsIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
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
API_UNAVAILABLE(macosx)
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
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INMessageAttribute.h>

@class INStringResolutionResult;
@class INMessageAttributeResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INSetMessageAttributeIntent : INIntent

- (instancetype)initWithIdentifiers:(nullable NSArray<NSString *> *)identifiers
                          attribute:(INMessageAttribute)attribute NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *identifiers;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INMessageAttribute attribute;

@end

@class INSetMessageAttributeIntentResponse;

/*!
 @brief Protocol to declare support for handling an INSetMessageAttributeIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(macosx(10.12), ios(10.0))
@protocol INSetMessageAttributeIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INSetMessageAttributeIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  setMessageAttributeIntent The input intent
 @param  completion The response handling block takes a INSetMessageAttributeIntentResponse containing the details of the result of having executed the intent

 @see  INSetMessageAttributeIntentResponse
 */

- (void)handleSetMessageAttribute:(INSetMessageAttributeIntent *)intent
                       completion:(void (^)(INSetMessageAttributeIntentResponse *response))completion NS_SWIFT_NAME(handle(setMessageAttribute:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  setMessageAttributeIntent The input intent
 @param  completion The response block contains an INSetMessageAttributeIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetMessageAttributeIntentResponse

 */

- (void)confirmSetMessageAttribute:(INSetMessageAttributeIntent *)intent
                        completion:(void (^)(INSetMessageAttributeIntentResponse *response))completion NS_SWIFT_NAME(confirm(setMessageAttribute:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  setMessageAttributeIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveAttributeForSetMessageAttribute:(INSetMessageAttributeIntent *)intent
                                withCompletion:(void (^)(INMessageAttributeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAttribute(forSetMessageAttribute:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRestaurantGuestResolutionResult.h
//
//  INRestaurantGuestResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//
//  This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
//  http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntentResolutionResult.h>

@class INRestaurantGuest;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
@interface INRestaurantGuestResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given restaurant guest. The resolvedRestaurantGuest need not be identical to the input restaurant. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedRestaurantGuest:(INRestaurantGuest *)resolvedRestaurantGuest NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided restaurant guests.
+ (instancetype)disambiguationWithRestaurantGuestsToDisambiguate:(NSArray<INRestaurantGuest *> *)restaurantGuestsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the restaurant guest with which the user wants to continue.
+ (instancetype)confirmationRequiredWithRestaurantGuestToConfirm:(nullable INRestaurantGuest *)restaurantGuestToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INIntentHandlerProviding.h
//
//  INIntentHandlerProviding.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INIntent;

NS_ASSUME_NONNULL_BEGIN

@protocol INIntentHandlerProviding <NSObject>

// Override this function to provide classes other than the extension's principal class to handle a given intent
- (nullable id)handlerForIntent:(INIntent *)intent;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCurrencyAmountResolutionResult.h
//
//  INCurrencyAmountResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INCurrencyAmount;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx)
@interface INCurrencyAmountResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given currency amount. The resolvedCurrencyAmount need not be identical to the input currency amount. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedCurrencyAmount:(INCurrencyAmount *)resolvedCurrencyAmount NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided currency amounts.
+ (instancetype)disambiguationWithCurrencyAmountsToDisambiguate:(NSArray<INCurrencyAmount *> *)currencyAmountsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the currency amount with which the user wants to continue.
+ (instancetype)confirmationRequiredWithCurrencyAmountToConfirm:(nullable INCurrencyAmount *)currencyAmountToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INEndWorkoutIntentResponse.h
//
//  INEndWorkoutIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INEndWorkoutIntentResponseCode) {
    INEndWorkoutIntentResponseCodeUnspecified = 0,
    INEndWorkoutIntentResponseCodeReady,
    INEndWorkoutIntentResponseCodeContinueInApp,
    INEndWorkoutIntentResponseCodeFailure,
    INEndWorkoutIntentResponseCodeFailureRequiringAppLaunch,
    INEndWorkoutIntentResponseCodeFailureNoMatchingWorkout,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
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
// ==========  Intents.framework/Headers/INSearchForPhotosIntentResponse.h
//
//  INSearchForPhotosIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INSearchForPhotosIntentResponseCode) {
    INSearchForPhotosIntentResponseCodeUnspecified = 0,
    INSearchForPhotosIntentResponseCodeReady,
    INSearchForPhotosIntentResponseCodeContinueInApp,
    INSearchForPhotosIntentResponseCodeFailure,
    INSearchForPhotosIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
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
// ==========  Intents.framework/Headers/INRequestRideIntent.h
//
//  INRequestRideIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class CLPlacemark;
@class INPlacemarkResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;
@class INIntegerResolutionResult;
@class INPaymentMethod;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INRequestRideIntent : INIntent

- (instancetype)initWithPickupLocation:(nullable CLPlacemark *)pickupLocation
                       dropOffLocation:(nullable CLPlacemark *)dropOffLocation
                        rideOptionName:(nullable INSpeakableString *)rideOptionName
                             partySize:(nullable NSNumber *)partySize
                         paymentMethod:(nullable INPaymentMethod *)paymentMethod NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

// Specifies the location to to begin the ride.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *pickupLocation;

// Specifies where the ride should end.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *dropOffLocation;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *rideOptionName;

// Defines the number of people in the party requesting the ride.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *partySize NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentMethod *paymentMethod;

@end

@class INRequestRideIntentResponse;

/*!
 @brief Protocol to declare support for handling an INRequestRideIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INRequestRideIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INRequestRideIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  requestRideIntent The input intent
 @param  completion The response handling block takes a INRequestRideIntentResponse containing the details of the result of having executed the intent

 @see  INRequestRideIntentResponse
 */

- (void)handleRequestRide:(INRequestRideIntent *)intent
               completion:(void (^)(INRequestRideIntentResponse *response))completion NS_SWIFT_NAME(handle(requestRide:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  requestRideIntent The input intent
 @param  completion The response block contains an INRequestRideIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INRequestRideIntentResponse

 */

- (void)confirmRequestRide:(INRequestRideIntent *)intent
                completion:(void (^)(INRequestRideIntentResponse *response))completion NS_SWIFT_NAME(confirm(requestRide:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  requestRideIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolvePickupLocationForRequestRide:(INRequestRideIntent *)intent
                             withCompletion:(void (^)(INPlacemarkResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePickupLocation(forRequestRide:with:));

- (void)resolveDropOffLocationForRequestRide:(INRequestRideIntent *)intent
                              withCompletion:(void (^)(INPlacemarkResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDropOffLocation(forRequestRide:with:));

- (void)resolveRideOptionNameForRequestRide:(INRequestRideIntent *)intent
                             withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRideOptionName(forRequestRide:with:));

- (void)resolvePartySizeForRequestRide:(INRequestRideIntent *)intent
                        withCompletion:(void (^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePartySize(forRequestRide:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INStringResolutionResult.h
//
//  INStringResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INStringResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given string. The resolvedString need not be identical to the input string. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
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
//  Copyright © 2016 Apple. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/Intents.h>
#import <Intents/INRestaurantGuest.h>
#import <Intents/INRestaurantGuestDisplayPreferences.h>

typedef NS_ENUM(NSInteger, INGetRestaurantGuestIntentResponseCode) {
    INGetRestaurantGuestIntentResponseCodeSuccess,
    INGetRestaurantGuestIntentResponseCodeFailure,
};

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INGetRestaurantGuestIntentResponse : INIntentResponse

- (instancetype)initWithCode:(INGetRestaurantGuestIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurantGuest *guest;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurantGuestDisplayPreferences *guestDisplayPreferences;

@property (readonly, NS_NONATOMIC_IOSONLY) INGetRestaurantGuestIntentResponseCode code;

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INGetAvailableRestaurantReservationBookingsIntent.h
//
//  INGetAvailableRestaurantReservationBookingsIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
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
API_UNAVAILABLE(macosx)
@interface INGetAvailableRestaurantReservationBookingsIntent : INIntent <NSCopying>

@property (copy, NS_NONATOMIC_IOSONLY) INRestaurant *restaurant;
@property (NS_NONATOMIC_IOSONLY) NSUInteger partySize;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *preferredBookingDateComponents;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *maximumNumberOfResults; // if the caller has a preferred maximum number of results, one can optionally be specified. a nil here leaves it up to the extension

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *earliestBookingDateForResults;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *latestBookingDateForResults;

@end

@class INGetAvailableRestaurantReservationBookingsIntentResponse;

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INGetAvailableRestaurantReservationBookingsIntentHandling <NSObject>

/*!
 @brief handling method
 
 @abstract Execute the task represented by the INGetAvailableRestaurantReservationBookingsIntent that's passed in
 @discussion This method are called to actually execute the intent, the app must return a response for this intent and an NSUserActivity capturing the state that the app must be restored to at the end of handling this intent
 
 @param  showBookingsIntent The input intent
 @param  completion The response handling block to invoke with the response to handling the intent.
 
 @see  INGetAvailableRestaurantReservationBookingsIntentResponse
 
 */

- (void)handleGetAvailableRestaurantReservationBookings:(INGetAvailableRestaurantReservationBookingsIntent *)intent completion:(void (^)(INGetAvailableRestaurantReservationBookingsIntentResponse *response))completion NS_SWIFT_NAME(handle(getAvailableRestaurantReservationBookings:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.
 
 @param  bookingDefaultsIntent The input intent
 @param  completion The response block contains an INGetAvailableRestaurantReservationBookingDefaultsIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.
 
 @see INGetAvailableRestaurantReservationBookingsIntentResponse
 
 */

- (void)confirmGetAvailableRestaurantReservationBookings:(INGetAvailableRestaurantReservationBookingsIntent *)intent completion:(void (^)(INGetAvailableRestaurantReservationBookingsIntentResponse *response))completion NS_SWIFT_NAME(confirm(getAvailableRestaurantReservationBookings:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.
 
 @param  bookingDefaultsIntent The input intent
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
//  Copyright © 2016 Apple. All rights reserved.
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
API_UNAVAILABLE(macosx)
NS_ASSUME_NONNULL_BEGIN
@interface INRestaurantReservationUserBooking : INRestaurantReservationBooking <NSCopying>

- (instancetype)initWithRestaurant:(INRestaurant *)restaurant bookingDate:(NSDate *)bookingDate partySize:(NSUInteger)partySize bookingIdentifier:(NSString *)bookingIdentifier guest:(INRestaurantGuest *)guest status:(INRestaurantReservationUserBookingStatus)status dateStatusModified:(NSDate *)dateStatusModified;

@property (copy, NS_NONATOMIC_IOSONLY) INRestaurantGuest *guest;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *advisementText; // a string representing restaurant specific information related to the reservation: things like late policies, parking instructions, or specials
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurantOffer *selectedOffer; // an offer, if any, attached to the booking
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *guestProvidedSpecialRequestText; // any user-specified special request text submitted with the reservation
@property (NS_NONATOMIC_IOSONLY) INRestaurantReservationUserBookingStatus status; // an enum indicating whether a booking was denied, pending, or confirmed
@property (NS_NONATOMIC_IOSONLY) NSDate *dateStatusModified; // date indicating when the status was updated to its current value

@end
NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRelativeReference.h
//
//  INRelativeReference.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INRelativeReference_h
#define INRelativeReference_h

#import <Foundation/Foundation.h>

#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INRelativeReference) {
    INRelativeReferenceUnknown = 0,
    INRelativeReferenceNext,
    INRelativeReferencePrevious,
};

#endif // INRelativeReference_h
// ==========  Intents.framework/Headers/INIntentErrors.h
//
//  INIntentErrors.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/IntentsDefines.h>

INTENTS_EXTERN NSString * const INIntentErrorDomain API_AVAILABLE(macosx(10.12), ios(10.0));

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
    
    // Requests
    INIntentErrorRequestTimedOut = 3001,
    
    // User Vocabulary Sync
    INIntentErrorInvalidUserVocabularyFileLocation = 4000,
} API_AVAILABLE(macosx(10.12), ios(10.0));
// ==========  Intents.framework/Headers/INSiriAuthorizationStatus.h
//
//  INSiriAuthorizationStatus.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INSiriAuthorizationStatus_h
#define INSiriAuthorizationStatus_h

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
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

#endif /* INSiriAuthorizationStatus_h */
// ==========  Intents.framework/Headers/INRelativeReferenceResolutionResult.h
//
//  INRelativeReferenceResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INRelativeReference.h>

NS_ASSUME_NONNULL_BEGIN

@interface INRelativeReferenceResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedValue:(INRelativeReference)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(INRelativeReference)valueToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INWorkoutGoalUnitType.h
//
//  INWorkoutGoalUnitType.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
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
};

#endif // INWorkoutGoalUnitType_h
// ==========  Intents.framework/Headers/INSetMessageAttributeIntentResponse.h
//
//  INSetMessageAttributeIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
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
} API_AVAILABLE(macosx(10.12), ios(10.0));

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
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
//  Copyright © 2016 Apple. All rights reserved.
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
};

#endif // INPhotoAttributeOptions_h
// ==========  Intents.framework/Headers/INIntegerResolutionResult.h
//
//  INIntegerResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx)
@interface INIntegerResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
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
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INStartPhotoPlaybackIntentResponseCode) {
    INStartPhotoPlaybackIntentResponseCodeUnspecified = 0,
    INStartPhotoPlaybackIntentResponseCodeReady,
    INStartPhotoPlaybackIntentResponseCodeContinueInApp,
    INStartPhotoPlaybackIntentResponseCodeFailure,
    INStartPhotoPlaybackIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
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
// ==========  Intents.framework/Headers/INInteraction.h
//
//  INInteraction.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
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
} API_AVAILABLE(macosx(10.12), ios(10.0));

typedef NS_ENUM(NSInteger, INInteractionDirection) {
    INInteractionDirectionUnspecified = 0,
    INInteractionDirectionOutgoing,
    INInteractionDirectionIncoming,
} API_AVAILABLE(macosx(10.12), ios(10.0));

NS_ASSUME_NONNULL_BEGIN

/*
 An app can use an INInteraction to donate an action (represented as an intent) and its state to the system.

 The system may also launch the app with an NSUserActivity containing an INInteraction such that the app can perform the action if it chooses.
*/

API_AVAILABLE(macosx(10.12), ios(10.0))
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
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INConditionalOperator.h>
#import <Intents/INMessageAttributeOptions.h>

@class INPerson;
@class INPersonResolutionResult;
@class INMessageAttributeOptionsResolutionResult;
@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INSearchForMessagesIntent : INIntent

- (instancetype)initWithRecipients:(nullable NSArray<INPerson *> *)recipients
                           senders:(nullable NSArray<INPerson *> *)senders
                       searchTerms:(nullable NSArray<NSString *> *)searchTerms
                        attributes:(INMessageAttributeOptions)attributes
                     dateTimeRange:(nullable INDateComponentsRange *)dateTimeRange
                       identifiers:(nullable NSArray<NSString *> *)identifiers
           notificationIdentifiers:(nullable NSArray<NSString *> *)notificationIdentifiers
                        groupNames:(nullable NSArray<NSString *> *)groupNames NS_DESIGNATED_INITIALIZER;

// Contact that received the messages to be found.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *recipients;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator recipientsOperator;

// Sender of the messages to be found.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *senders;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator sendersOperator;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *searchTerms;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator searchTermsOperator;

// Attributes of the message to be found.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INMessageAttributeOptions attributes;

// Time range in which to search for the message.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dateTimeRange;

// If available, the identifier of a particular message to be found.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *identifiers;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator identifiersOperator;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *notificationIdentifiers;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator notificationIdentifiersOperator;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *groupNames;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator groupNamesOperator;

@end

@class INSearchForMessagesIntentResponse;

/*!
 @brief Protocol to declare support for handling an INSearchForMessagesIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(macosx(10.12), ios(10.0))
@protocol INSearchForMessagesIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INSearchForMessagesIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  searchForMessagesIntent The input intent
 @param  completion The response handling block takes a INSearchForMessagesIntentResponse containing the details of the result of having executed the intent

 @see  INSearchForMessagesIntentResponse
 */

- (void)handleSearchForMessages:(INSearchForMessagesIntent *)intent
                     completion:(void (^)(INSearchForMessagesIntentResponse *response))completion NS_SWIFT_NAME(handle(searchForMessages:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  searchForMessagesIntent The input intent
 @param  completion The response block contains an INSearchForMessagesIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSearchForMessagesIntentResponse

 */

- (void)confirmSearchForMessages:(INSearchForMessagesIntent *)intent
                      completion:(void (^)(INSearchForMessagesIntentResponse *response))completion NS_SWIFT_NAME(confirm(searchForMessages:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  searchForMessagesIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveRecipientsForSearchForMessages:(INSearchForMessagesIntent *)intent
                               withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveRecipients(forSearchForMessages:with:));

- (void)resolveSendersForSearchForMessages:(INSearchForMessagesIntent *)intent
                            withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveSenders(forSearchForMessages:with:));

- (void)resolveAttributesForSearchForMessages:(INSearchForMessagesIntent *)intent
                               withCompletion:(void (^)(INMessageAttributeOptionsResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAttributes(forSearchForMessages:with:));

- (void)resolveDateTimeRangeForSearchForMessages:(INSearchForMessagesIntent *)intent
                                  withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDateTimeRange(forSearchForMessages:with:));

- (void)resolveGroupNamesForSearchForMessages:(INSearchForMessagesIntent *)intent
                               withCompletion:(void (^)(NSArray<INStringResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveGroupNames(forSearchForMessages:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INRestaurantResolutionResult.h
//
//  INRestaurantResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//
//  This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
//  http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntentResolutionResult.h>

@class INRestaurant;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
@interface INRestaurantResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given restaurant. The resolvedRestaurant need not be identical to the input restaurant. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedRestaurant:(INRestaurant *)resolvedRestaurant NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided restaurants.
+ (instancetype)disambiguationWithRestaurantsToDisambiguate:(NSArray<INRestaurant *> *)restaurantsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the restaurant with which the user wants to continue.
+ (instancetype)confirmationRequiredWithRestaurantToConfirm:(nullable INRestaurant *)restaurantToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INPaymentMethodType.h
//
//  INPaymentMethodType.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
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
};

#endif // INPaymentMethodType_h
// ==========  Intents.framework/Headers/INRestaurantGuest.h
//
//  INRestaurantGuest.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INPerson.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
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
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INWorkoutGoalUnitType.h>
#import <Intents/INWorkoutLocationType.h>

@class INSpeakableString;
@class INSpeakableStringResolutionResult;
@class INDoubleResolutionResult;
@class INWorkoutGoalUnitTypeResolutionResult;
@class INWorkoutLocationTypeResolutionResult;
@class INBooleanResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@interface INStartWorkoutIntent : INIntent

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
 @brief Protocol to declare support for handling an INStartWorkoutIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INStartWorkoutIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INStartWorkoutIntent that's passed in
 @discussion This method is called to actually execute the intent. The app must return a response for this intent.

 @param  startWorkoutIntent The input intent
 @param  completion The response handling block takes a INStartWorkoutIntentResponse containing the details of the result of having executed the intent

 @see  INStartWorkoutIntentResponse
 */

- (void)handleStartWorkout:(INStartWorkoutIntent *)intent
                completion:(void (^)(INStartWorkoutIntentResponse *response))completion NS_SWIFT_NAME(handle(startWorkout:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  startWorkoutIntent The input intent
 @param  completion The response block contains an INStartWorkoutIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INStartWorkoutIntentResponse

 */

- (void)confirmStartWorkout:(INStartWorkoutIntent *)intent
                 completion:(void (^)(INStartWorkoutIntentResponse *response))completion NS_SWIFT_NAME(confirm(startWorkout:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  startWorkoutIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveWorkoutNameForStartWorkout:(INStartWorkoutIntent *)intent
                           withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutName(forStartWorkout:with:));

- (void)resolveGoalValueForStartWorkout:(INStartWorkoutIntent *)intent
                         withCompletion:(void (^)(INDoubleResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveGoalValue(forStartWorkout:with:));

- (void)resolveWorkoutGoalUnitTypeForStartWorkout:(INStartWorkoutIntent *)intent
                                   withCompletion:(void (^)(INWorkoutGoalUnitTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutGoalUnitType(forStartWorkout:with:));

- (void)resolveWorkoutLocationTypeForStartWorkout:(INStartWorkoutIntent *)intent
                                   withCompletion:(void (^)(INWorkoutLocationTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveWorkoutLocationType(forStartWorkout:with:));

- (void)resolveIsOpenEndedForStartWorkout:(INStartWorkoutIntent *)intent
                           withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveIsOpenEnded(forStartWorkout:with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCarDefrosterResolutionResult.h
//
//  INCarDefrosterResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarDefroster.h>

NS_ASSUME_NONNULL_BEGIN

@interface INCarDefrosterResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedValue:(INCarDefroster)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(INCarDefroster)valueToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INDateComponentsResolutionResult.h
//
//  INDateComponentsResolutionResult.m
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
@interface INDateComponentsResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given dateComponents. The resolvedDateComponents need not be identical to the input dateComponents. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedDateComponents:(NSDateComponents *)resolvedDateComponents NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided dateComponentss.
+ (instancetype)disambiguationWithDateComponentsToDisambiguate:(NSArray<NSDateComponents *> *)dateComponentsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the dateComponents with which the user wants to continue.
+ (instancetype)confirmationRequiredWithDateComponentsToConfirm:(nullable NSDateComponents *)dateComponentsToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INStartVideoCallIntentResponse.h
//
//  INStartVideoCallIntentResponse.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

typedef NS_ENUM(NSInteger, INStartVideoCallIntentResponseCode) {
    INStartVideoCallIntentResponseCodeUnspecified = 0,
    INStartVideoCallIntentResponseCodeReady,
    INStartVideoCallIntentResponseCodeContinueInApp,
    INStartVideoCallIntentResponseCodeFailure,
    INStartVideoCallIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(macosx(10.12), ios(10.0));

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
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
//  Copyright © 2016 Apple. All rights reserved.
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
};

#endif // INCallRecordType_h
// ==========  Intents.framework/Headers/INRideOption.h
//
//  INRideOption.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INPriceRange;
@class INRidePartySizeOption;
@class INRideFareLineItem;
@class INImage;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(NA, 10_0) __TVOS_PROHIBITED __WATCHOS_AVAILABLE(3_0)
@interface INRideOption : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithName:(NSString *)name
         estimatedPickupDate:(NSDate *)estimatedPickupDate NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithCoder:(NSCoder *)decoder NS_DESIGNATED_INITIALIZER;

@property (readwrite, copy, NS_NONATOMIC_IOSONLY) NSString *name; // a name for the ride option.

@property (readwrite, copy, NS_NONATOMIC_IOSONLY) NSDate *estimatedPickupDate; // used for providing an ETA to the user.

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INPriceRange *priceRange; // The indicative range of prices for this option.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *usesMeteredFare; // If @YES, the fare will be metered by the driver, and price range information will be noted as unavailable.

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
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INSiriAuthorizationStatus.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx)
@interface INPreferences : NSObject

+ (INSiriAuthorizationStatus)siriAuthorizationStatus;
+ (void)requestSiriAuthorization:(void (^)(INSiriAuthorizationStatus status))handler;
+ (NSString *)siriLanguageCode;

@end

NS_ASSUME_NONNULL_END
// ==========  Intents.framework/Headers/INCarAudioSource.h
//
//  INCarAudioSource.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
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
};

#endif // INCarAudioSource_h
