// ==========  PassKit.framework/Headers/PKConstants.h
//
//  PKConstants.h
//  PassKit
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef PKCONSTANTS_H
#define PKCONSTANTS_H

typedef NSString * PKEncryptionScheme NS_STRING_ENUM;
extern PKEncryptionScheme const PKEncryptionSchemeECC_V2 API_AVAILABLE(ios(9.0));
extern PKEncryptionScheme const PKEncryptionSchemeRSA_V2 API_AVAILABLE(ios(10.0));

typedef NSString * PKPaymentNetwork NS_EXTENSIBLE_STRING_ENUM;
extern PKPaymentNetwork const PKPaymentNetworkAmex API_AVAILABLE(ios(8.0), watchos(3.0));
extern PKPaymentNetwork const PKPaymentNetworkCarteBancaire API_DEPRECATED("Use PKPaymentNetworkCartesBancaires instead.", macos(10.12, 10.13), ios(10.3, 11.0), watchos(3.2, 4.0));
extern PKPaymentNetwork const PKPaymentNetworkCarteBancaires API_DEPRECATED("Use PKPaymentNetworkCartesBancaires instead.", macos(10.13, 10.13), ios(11.0, 11.2), watchos(4.0, 4.2));
extern PKPaymentNetwork const PKPaymentNetworkCartesBancaires API_AVAILABLE(ios(11.2), watchos(4.2));
extern PKPaymentNetwork const PKPaymentNetworkChinaUnionPay API_AVAILABLE(ios(9.2), watchos(3.0));
extern PKPaymentNetwork const PKPaymentNetworkDiscover API_AVAILABLE(ios(9.0), watchos(3.0));
extern PKPaymentNetwork const PKPaymentNetworkEftpos API_AVAILABLE(ios(12.0), watchos(5.0));
extern PKPaymentNetwork const PKPaymentNetworkElectron API_AVAILABLE(ios(12.0), watchos(5.0));
extern PKPaymentNetwork const PKPaymentNetworkIDCredit API_AVAILABLE(ios(10.3), watchos(3.2));
extern PKPaymentNetwork const PKPaymentNetworkInterac API_AVAILABLE(ios(9.2), watchos(3.0));
extern PKPaymentNetwork const PKPaymentNetworkJCB API_AVAILABLE(ios(10.1), watchos(3.1));
extern PKPaymentNetwork const PKPaymentNetworkMaestro API_AVAILABLE(ios(12.0), watchos(5.0));
extern PKPaymentNetwork const PKPaymentNetworkMasterCard API_AVAILABLE(ios(8.0), watchos(3.0));
extern PKPaymentNetwork const PKPaymentNetworkPrivateLabel API_AVAILABLE(ios(9.0), watchos(3.0));
extern PKPaymentNetwork const PKPaymentNetworkQuicPay API_AVAILABLE(ios(10.3), watchos(3.2));
extern PKPaymentNetwork const PKPaymentNetworkSuica API_AVAILABLE(ios(10.1), watchos(3.1));
extern PKPaymentNetwork const PKPaymentNetworkVisa API_AVAILABLE(ios(8.0), watchos(3.0));
extern PKPaymentNetwork const PKPaymentNetworkVPay API_AVAILABLE(ios(12.0), watchos(5.0));

typedef NSString * PKContactField NS_STRING_ENUM;
extern PKContactField const PKContactFieldPostalAddress API_AVAILABLE(ios(11.0), watchos(4.0));
extern PKContactField const PKContactFieldEmailAddress  API_AVAILABLE(ios(11.0), watchos(4.0));
extern PKContactField const PKContactFieldPhoneNumber   API_AVAILABLE(ios(11.0), watchos(4.0));
extern PKContactField const PKContactFieldName          API_AVAILABLE(ios(11.0), watchos(4.0));
extern PKContactField const PKContactFieldPhoneticName  API_AVAILABLE(ios(11.0), watchos(4.0));


typedef NS_ENUM(NSInteger, PKPaymentAuthorizationStatus) {
    PKPaymentAuthorizationStatusSuccess, // Merchant auth'd (or expects to auth) the transaction successfully.
    PKPaymentAuthorizationStatusFailure, // Merchant failed to auth the transaction.

    PKPaymentAuthorizationStatusInvalidBillingPostalAddress API_DEPRECATED("Use PKPaymentAuthorizationResult with PKPaymentAuthorizationStatusFailure and include the result of -paymentBillingAddressInvalidErrorWithKey:localizedDescription: in the errors array.", ios(8.0, 11.0), watchos(3.0, 4.0)),  // Supplied billing address is insufficient or otherwise invalid
    PKPaymentAuthorizationStatusInvalidShippingPostalAddress API_DEPRECATED("Use PKPaymentAuthorizationResult with PKPaymentAuthorizationStatusFailure and include the result of -paymentShippingAddressInvalidErrorWithKey:localizedDescription: in the errors array.", ios(8.0, 11.0), watchos(3.0, 4.0)), // Supplied postal address is insufficient or otherwise invalid
    PKPaymentAuthorizationStatusInvalidShippingContact API_DEPRECATED("Use PKPaymentAuthorizationResult with PKPaymentAuthorizationStatusFailure and include the result of -paymentContactInvalidErrorWithContactField:localizedDescription: in the errors array.", ios(8.0, 11.0), watchos(3.0, 4.0)), // Supplied contact information is insufficient or otherwise invalid

    PKPaymentAuthorizationStatusPINRequired API_AVAILABLE(ios(9.2), watchos(3.0)),  // Transaction requires PIN entry.
    PKPaymentAuthorizationStatusPINIncorrect API_AVAILABLE(ios(9.2), watchos(3.0)), // PIN was not entered correctly, retry.
    PKPaymentAuthorizationStatusPINLockout API_AVAILABLE(ios(9.2), watchos(3.0)),    // PIN retry limit exceeded.
} API_AVAILABLE(ios(8.0), watchos(3.0));

typedef NS_ENUM(NSInteger, PKPaymentButtonStyle) {
    PKPaymentButtonStyleWhite = 0,
    PKPaymentButtonStyleWhiteOutline,
    PKPaymentButtonStyleBlack
} API_AVAILABLE(ios(8.3), watchos(3.0));

typedef NS_ENUM(NSInteger, PKPaymentButtonType) {
    PKPaymentButtonTypePlain = 0,
    PKPaymentButtonTypeBuy,
    PKPaymentButtonTypeSetUp API_AVAILABLE(ios(9.0), watchos(3.0)),
    PKPaymentButtonTypeInStore API_AVAILABLE(ios(10.0), watchos(3.0)),
    PKPaymentButtonTypeDonate  API_AVAILABLE(ios(10.2), watchos(3.2)),
    PKPaymentButtonTypeCheckout  API_AVAILABLE(ios(12.0), watchos(5.0)),
    PKPaymentButtonTypeBook  API_AVAILABLE(ios(12.0), watchos(5.0)),
    PKPaymentButtonTypeSubscribe  API_AVAILABLE(ios(12.0), watchos(5.0))
} API_AVAILABLE(ios(8.3), watchos(3.0));

#endif // PKCONSTANTS_H
// ==========  PassKit.framework/Headers/PKPaymentButton.h
//
//  PKPaymentButton.h
//
//  Copyright © 2014 Apple, Inc. All rights reserved.
//

#if TARGET_OS_IPHONE

#import <UIKit/UIKit.h>
#import <PassKit/PKConstants.h>
NS_ASSUME_NONNULL_BEGIN

// PKPaymentButton vends a number of Apple Pay related buttons for use inside of your app
// These buttons can be used to prompt the user to pay with Apple Pay, or set up cards for payment
// Refer to the Apple Pay developer documentation for more information on how to use this class
API_AVAILABLE(ios(8.3))
@interface PKPaymentButton : UIButton

+ (instancetype)buttonWithType:(PKPaymentButtonType)buttonType style:(PKPaymentButtonStyle)buttonStyle;

- (instancetype)initWithPaymentButtonType:(PKPaymentButtonType)type paymentButtonStyle:(PKPaymentButtonStyle)style API_AVAILABLE(ios(9.0)) NS_DESIGNATED_INITIALIZER;

@property (nonatomic, assign) CGFloat cornerRadius API_AVAILABLE(ios(12.0));

@end

NS_ASSUME_NONNULL_END

#endif
// ==========  PassKit.framework/Headers/PKContact.h
//
//  PKContact.h
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#if !TARGET_OS_TV
#import <Contacts/Contacts.h>
#endif

API_AVAILABLE(ios(9.0), watchos(3.0))
@interface PKContact : NSObject

@property (nonatomic, strong, nullable) NSPersonNameComponents *name;

#if TARGET_OS_TV
@property (nonatomic, strong, nullable) id postalAddress;
@property (nonatomic, strong, nullable) id phoneNumber;
#else
@property (nonatomic, strong, nullable) CNPostalAddress *postalAddress;
@property (nonatomic, strong, nullable) CNPhoneNumber   *phoneNumber;
#endif

@property (nonatomic, strong, nullable) NSString        *emailAddress;


// This property is now deprecated. Use the -subLocality property on [PKContact -postalAddress] instead
@property (nonatomic, retain, nullable) NSString        *supplementarySubLocality API_DEPRECATED("Use subLocality and subAdministrativeArea on -postalAddress instead", ios(9.2, 10.3), watchos(3.0, 3.2));

@end
// ==========  PassKit.framework/Headers/PKPaymentRequestStatus.h
//
//  PKPaymentRequestStatus.h
//
//  Copyright © 2016 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PassKit/PKConstants.h>

NS_ASSUME_NONNULL_BEGIN

@class PKShippingMethod;
@class PKPaymentSummaryItem;

API_AVAILABLE(ios(11.0), watchos(4.0))
@interface PKPaymentAuthorizationResult : NSObject

- (instancetype)initWithStatus:(PKPaymentAuthorizationStatus)status
                        errors:(nullable NSArray<NSError *> *)errors NS_DESIGNATED_INITIALIZER;

// The status of the payment
@property (nonatomic, assign) PKPaymentAuthorizationStatus status;

// Any errors that applied. These errors will be displayed to the user to correct.
// Errors should be ordered from most to least serious.
// See PKError for specific NSError keys to use to enable rich error handling.
@property (null_resettable, nonatomic, copy) NSArray<NSError *> *errors;

@end

API_AVAILABLE(ios(11.0), watchos(4.0))
@interface PKPaymentRequestUpdate : NSObject

- (instancetype)initWithPaymentSummaryItems:(NSArray<PKPaymentSummaryItem *> *)paymentSummaryItems NS_DESIGNATED_INITIALIZER;

// The status of the payment request update. Set PKPaymentAuthorizationStatusSuccess for a successful update,
// and PKPaymentAuthorizationStatusFailure if you were unable to process the required changes.
// PKPaymentAuthorizationStatusSuccess by default
@property (nonatomic, assign) PKPaymentAuthorizationStatus status;

// The new payment summary items to update the payment request with
@property (nonatomic, copy) NSArray<PKPaymentSummaryItem *> *paymentSummaryItems;

@end

API_AVAILABLE(ios(11.0), watchos(4.0))
@interface PKPaymentRequestShippingContactUpdate : PKPaymentRequestUpdate

// You may optionally supply errors here. 
// See PKError for specific NSError keys to use.
- (instancetype)initWithErrors:(nullable NSArray<NSError *> *)errors
           paymentSummaryItems:(NSArray<PKPaymentSummaryItem *> *)paymentSummaryItems
               shippingMethods:(NSArray<PKShippingMethod *> *)shippingMethods NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy) NSArray<PKShippingMethod *> *shippingMethods;
@property (null_resettable, nonatomic, copy) NSArray<NSError *> *errors;

@end

API_AVAILABLE(ios(11.0), watchos(4.0))
@interface PKPaymentRequestShippingMethodUpdate : PKPaymentRequestUpdate

@end

API_AVAILABLE(ios(11.0), watchos(4.0))
@interface PKPaymentRequestPaymentMethodUpdate : PKPaymentRequestUpdate

@end

NS_ASSUME_NONNULL_END
// ==========  PassKit.framework/Headers/PKPassLibrary.h
//
//  PKPassLibrary.h
//  PassKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//
//  Threading contract: no concurrent usage.

#import <Foundation/Foundation.h>
#import <PassKit/PKPass.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, PKPassLibraryAddPassesStatus) {
    PKPassLibraryDidAddPasses,
    PKPassLibraryShouldReviewPasses,
    PKPassLibraryDidCancelAddPasses,
} API_AVAILABLE(ios(7.0), watchos(3.0));


typedef NS_ENUM(NSUInteger, PKAutomaticPassPresentationSuppressionResult) {
    PKAutomaticPassPresentationSuppressionResultNotSupported = 0,   // Suppression is not supported for this device
    PKAutomaticPassPresentationSuppressionResultAlreadyPresenting,  // Passes are already being presented and cannot be suppressed
    PKAutomaticPassPresentationSuppressionResultDenied,             // Suppression was denied due to lack of entitlement
    PKAutomaticPassPresentationSuppressionResultCancelled,          // Suppression was cancelled before the response handler was fired
    PKAutomaticPassPresentationSuppressionResultSuccess             // Suppression of automatic pass presentation was successful
} __WATCHOS_PROHIBITED API_AVAILABLE(ios(9.0));

typedef NSUInteger PKSuppressionRequestToken;

API_AVAILABLE(ios(6.0), watchos(3.0))
@interface PKPassLibrary : NSObject

// The library is not available on iPad in 6.0.
+ (BOOL)isPassLibraryAvailable API_AVAILABLE(ios(6.0), watchos(3.0));

// These methods may be used to temporarily disable the automatic presentation of passes when a device encounters a contactless field.
// Use of these methods require an entitlement. Otherwise, requesting will always return a PKAutomaticPassPresentationSuppressionResultDenied as the result.
+ (PKSuppressionRequestToken)requestAutomaticPassPresentationSuppressionWithResponseHandler:(void(^)(PKAutomaticPassPresentationSuppressionResult result))responseHandler API_AVAILABLE(ios(9.0)) __WATCHOS_PROHIBITED NS_EXTENSION_UNAVAILABLE("Not available to extensions");
+ (void)endAutomaticPassPresentationSuppressionWithRequestToken:(PKSuppressionRequestToken)requestToken API_AVAILABLE(ios(9.0)) __WATCHOS_PROHIBITED NS_EXTENSION_UNAVAILABLE("Not available to extensions");
+ (BOOL)isSuppressingAutomaticPassPresentation API_AVAILABLE(ios(9.0)) __WATCHOS_PROHIBITED NS_EXTENSION_UNAVAILABLE("Not available to extensions");

// If device supports adding payment passes, this method will return YES. Otherwise, NO will be returned.
+ (BOOL)isPaymentPassActivationAvailable API_DEPRECATED("Use -[PKPassLibrary isPaymentPassActivationAvailable] instead", ios(8.0, 9.0));

// If this pass library supports activating payment passes, this method will return YES. Otherwise, NO will be returned.
- (BOOL)isPaymentPassActivationAvailable API_AVAILABLE(ios(9.0));

// These return only local passes the process is entitled to access.
- (NSArray<PKPass *> *)passes;
- (nullable PKPass *)passWithPassTypeIdentifier:(NSString *)identifier serialNumber:(NSString *)serialNumber;
- (NSArray<PKPass *> *)passesOfType:(PKPassType)passType API_AVAILABLE(ios(8.0), watchos(3.0));

// This returns the remote payment passes from attached devices
- (NSArray<PKPaymentPass *> *)remotePaymentPasses API_AVAILABLE(ios(9.0));

- (void)removePass:(PKPass *)pass;

// This returns YES even if the process is not entitled to access the pass in the library.  An app like Mail is not entitled to get
// pass from the library, but it should avoid presenting UI for adding an email attachment pass that is already in the library.
- (BOOL)containsPass:(PKPass *)pass;

// This will fail if a pass with matching identifier and serial number is not already present in the library, or if the process
// is not entitled to access the pass. To add a completely new pass, use PKAddPassesViewController.
- (BOOL)replacePassWithPass:(PKPass *)pass;

// The user will be prompted to grant permission for the calling process to add passes to the Pass Library. The user may respond
// by allowing the passes to be added, or requesting to review the passes. The selection will be returned in the completionHandler
// as a PKPassLibraryAddPassesStatus. If PKPassLibraryPassesPresentReview is returned, you must present a PKAddPassesViewController
// initialized with the passes so that the user may review and add the passes manually. The completion handler for this method is
// called on an arbitrary queue - dispatch to the main queue if you're presenting UI.
- (void)addPasses:(NSArray<PKPass *> *)passes withCompletionHandler:(nullable void(^)(PKPassLibraryAddPassesStatus status))completion API_AVAILABLE(ios(7.0), watchos(3.0));

// Opens the card setup flow (in Wallet on iPhone, Settings on iPad). Use this to direct a user to card setup directly from your app.
- (void)openPaymentSetup API_AVAILABLE(ios(8.3)) __WATCHOS_PROHIBITED;

// Presents the pass for use above the current application. The pass must already be in the pass library for this to have effect.
- (void)presentPaymentPass:(PKPaymentPass *)pass API_AVAILABLE(ios(10.0)) __WATCHOS_PROHIBITED;

// Returns YES if either the current device or an attached device both supports adding payment passes and does not already contain
// a payment pass with the supplied primary account identifier.
- (BOOL)canAddPaymentPassWithPrimaryAccountIdentifier:(NSString *)primaryAccountIdentifier API_AVAILABLE(ios(9.0));

// If the library can add Felica passes, this method will return YES. Otherwise, NO will be returned.
- (BOOL)canAddFelicaPass API_AVAILABLE(ios(10.1), watchos(3.1));

// These methods may be utilized to activate a payment pass that is provisioned but currently in the inactive state, by providing
// either a cryptographic OTP, or an activation code.
- (void)activatePaymentPass:(PKPaymentPass *)paymentPass withActivationData:(NSData *)activationData completion:(nullable void(^)(BOOL success, NSError* error))completion API_AVAILABLE(ios(8.0)) __WATCHOS_PROHIBITED;
- (void)activatePaymentPass:(PKPaymentPass *)paymentPass withActivationCode:(NSString *)activationCode completion:(nullable void(^)(BOOL success, NSError* error))completion API_DEPRECATED("Use activatePaymentPass:withActivationData:completion: instead", ios(8.0, 9.0)) __WATCHOS_PROHIBITED;
@end

// This notification is issued by a library instance, with that instance as the sender.  If there are no instantiated library objects,
// no notifications. There are no guarantees about what thread or queue these come in on.
typedef NSString * PKPassLibraryNotificationName NS_EXTENSIBLE_STRING_ENUM;
extern PKPassLibraryNotificationName const PKPassLibraryDidChangeNotification API_AVAILABLE(ios(6.0), watchos(3.0));
extern PKPassLibraryNotificationName const PKPassLibraryRemotePaymentPassesDidChangeNotification API_AVAILABLE(ios(9.0), watchos(3.0));

// Entries in user info dictionary for PKPassLibraryDidChangeNotification.
// - PKPassLibraryAddedPassesUserInfoKey is the key for an array of passes
// - PKPassLibraryReplacementPassesUserInfoKey is the key for an array of passes
// - PKPassLibraryRemovedPassInfosUserInfoKey is the key for an array of dictionaries, each of which has keys
//   PKPassLibraryPassTypeIdentifierUserInfoKey and PKPassLibrarySerialNumberUserInfoKey mapping to strings.
typedef NSString * PKPassLibraryNotificationKey NS_STRING_ENUM;
extern PKPassLibraryNotificationKey const PKPassLibraryAddedPassesUserInfoKey API_AVAILABLE(ios(6.0), watchos(3.0));
extern PKPassLibraryNotificationKey const PKPassLibraryReplacementPassesUserInfoKey API_AVAILABLE(ios(6.0), watchos(3.0));
extern PKPassLibraryNotificationKey const PKPassLibraryRemovedPassInfosUserInfoKey API_AVAILABLE(ios(6.0), watchos(3.0));

extern PKPassLibraryNotificationKey const PKPassLibraryPassTypeIdentifierUserInfoKey API_AVAILABLE(ios(6.0), watchos(3.0));
extern PKPassLibraryNotificationKey const PKPassLibrarySerialNumberUserInfoKey API_AVAILABLE(ios(6.0), watchos(3.0));

NS_ASSUME_NONNULL_END
// ==========  PassKit.framework/Headers/PKAddPassButton.h
//
//  PKAddPassButton.h
//  PassKit
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//
#if TARGET_OS_IOS

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, PKAddPassButtonStyle) {
    PKAddPassButtonStyleBlack = 0,
    PKAddPassButtonStyleBlackOutline,
} API_AVAILABLE(ios(9.0));

// Use PKAddPassButton to show an "Add to Apple Wallet" button. Two types are available for barcode or payment passes.
// Refer to the Apple Pay developer documentation for more information on how to use this class
API_AVAILABLE(ios(9.0))
@interface PKAddPassButton : UIButton

+ (instancetype)addPassButtonWithStyle:(PKAddPassButtonStyle)addPassButtonStyle;

- (instancetype)initWithAddPassButtonStyle:(PKAddPassButtonStyle)style NS_DESIGNATED_INITIALIZER;

@property (nonatomic, assign) PKAddPassButtonStyle addPassButtonStyle UI_APPEARANCE_SELECTOR;

@end

NS_ASSUME_NONNULL_END

#endif
// ==========  PassKit.framework/Headers/PKLabeledValue.h
//
//  PKLabeledValue.h
//  PassKit
//
//  Copyright © 2016 Apple, Inc. All rights reserved.
//
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.1))
@interface PKLabeledValue : NSObject

- (instancetype)initWithLabel:(NSString *)label
                        value:(NSString *)value NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, readonly) NSString *label;
@property (nonatomic, copy, readonly) NSString *value;

@end

NS_ASSUME_NONNULL_END
// ==========  PassKit.framework/Headers/PKObject.h
//
//  PKObject.h
//  PassKit
//
//  Copyright (c) 2013 Apple, Inc. All rights reserved.
//

#ifndef __PKOBJECT_H
#define __PKOBJECT_H

#import <Foundation/Foundation.h>
#import <PassKit/PKError.h>

@interface PKObject : NSObject

@end

#endif // __PKOBJECT_H
// ==========  PassKit.framework/Headers/PKAddPassesViewController.h
//
//  PKAddPassesViewController.h
//  PassKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#if TARGET_OS_IPHONE

#import <UIKit/UIKit.h>

@class PKPass;
@class PKAddPassesViewController;

NS_ASSUME_NONNULL_BEGIN

@protocol PKAddPassesViewControllerDelegate <NSObject>
@optional
-(void)addPassesViewControllerDidFinish:(PKAddPassesViewController *)controller; // delegate should dismiss presentation
@end

API_AVAILABLE(ios(6.0))
@interface PKAddPassesViewController : UIViewController

/* controller should be presented with -presentViewController:animated:completion:
 pass should be a pass you want the user to add.
 */
- (nullable instancetype)initWithPass:(PKPass *)pass;
- (nullable instancetype)initWithPasses:(NSArray<PKPass *> *)passes API_AVAILABLE(ios(7.0));
+ (BOOL)canAddPasses API_AVAILABLE(ios(8.0));

@property(nonatomic,assign,nullable) id <PKAddPassesViewControllerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END

#endif
// ==========  PassKit.framework/Headers/PKSuicaPassProperties.h
//
//  PKSuicaPassProperties.h
//  PassKit
//
//  Copyright (c) 2016 Apple, Inc. All rights reserved.
//
//

#import <PassKit/PKTransitPassProperties.h>

@class PKPass;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.1), watchos(3.1))
@interface PKSuicaPassProperties : PKTransitPassProperties

/// Properties for a given pass, or nil if the pass doesn’t support the set of properties being requested
+ (nullable instancetype)passPropertiesForPass:(PKPass *)pass;

@property (nonatomic, copy, readonly) NSDecimalNumber *transitBalance;
@property (nonatomic, copy, readonly) NSString *transitBalanceCurrencyCode;

@property (nonatomic, assign, readonly, getter=isInStation) BOOL inStation;
/// Note: isInShinkansenStation is not a subset of isInStation.
@property (nonatomic, assign, readonly, getter=isInShinkansenStation) BOOL inShinkansenStation;

@property (nonatomic, assign, getter=isBalanceAllowedForCommute, readonly) BOOL balanceAllowedForCommute API_AVAILABLE(ios(11.3), watchos(4.3));
@property (nonatomic, assign, getter=isLowBalanceGateNotificationEnabled, readonly) BOOL lowBalanceGateNotificationEnabled API_AVAILABLE(ios(11.3), watchos(4.3));

@property (nonatomic, assign, readonly, getter=isGreenCarTicketUsed) BOOL greenCarTicketUsed;
@property (nonatomic, assign, readonly, getter=isBlacklisted) BOOL blacklisted;

@end

NS_ASSUME_NONNULL_END
// ==========  PassKit.framework/Headers/PKPaymentToken.h
//
//  PKPaymentToken.h
//
//  Copyright (c) 2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PKPaymentMethod;

// Contains the user's payment credentials, encrypted to the merchant.
NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(ios(8.0), watchos(3.0))
@interface PKPaymentToken : NSObject

// Describes the properties of the underlying payment instrument selected to fund the payment
@property (nonatomic, strong, readonly) PKPaymentMethod *paymentMethod API_AVAILABLE(ios(9.0), watchos(3.0));

// A string that describes the payment instrument the user has selected to fund the payment.
// Suitable for display, e.g. "Amex 1234".
@property (nonatomic, copy, readonly) NSString *paymentInstrumentName API_DEPRECATED("Use paymentMethod instead", ios(8.0, 9.0)) __WATCHOS_PROHIBITED;

// Payment network for the card that funds the payment.
@property (nonatomic, copy, readonly) NSString *paymentNetwork API_DEPRECATED("Use paymentMethod instead", ios(8.0, 9.0)) __WATCHOS_PROHIBITED;

// A string that describes a globally unique identifier for this transaction that can be used
// for receipt purposes.
@property (nonatomic, copy, readonly) NSString *transactionIdentifier;

// UTF-8 encoded JSON dictionary of encrypted payment data.  Ready for transmission to
// merchant's e-commerce backend for decryption and submission to a payment processor's
// gateway.
@property (nonatomic, copy, readonly) NSData *paymentData;

@end

NS_ASSUME_NONNULL_END
// ==========  PassKit.framework/Headers/PKPaymentAuthorizationController.h
//
//  PKPaymentAuthorizationController.h
//  PassKit
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//
#if TARGET_OS_IPHONE

#import <PassKit/PKConstants.h>
#import <PassKit/PKPaymentRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class PKPayment;
@class PKContact;
@class PKPaymentMethod;
@class PKShippingMethod;
@class PKPaymentSummaryItem;
@class PKPaymentAuthorizationResult;
@class PKPaymentAuthorizationController;
@class PKPaymentRequestPaymentMethodUpdate;
@class PKPaymentRequestShippingMethodUpdate;
@class PKPaymentRequestShippingContactUpdate;

@protocol PKPaymentAuthorizationControllerDelegate <NSObject>

@required

// Sent to the delegate when payment authorization is finished.  This may occur when
// the user cancels the request, or after the PKPaymentAuthorizationStatus parameter of the
// paymentAuthorizationController:didAuthorizePayment:completion: has been shown to the user.
//
// The delegate is responsible for dismissing and releasing the controller in this method.
- (void)paymentAuthorizationControllerDidFinish:(PKPaymentAuthorizationController *)controller;

@optional

// Sent to the delegate after the user has acted on the payment request.  The application
// should inspect the payment to determine whether the payment request was authorized.
//
// If the application requested a shipping contact then the full contact is now part of the payment.
//
// The delegate must call completion with an appropriate authorization status, as may be determined
// by submitting the payment credential to a processing gateway for payment authorization.
- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
                   didAuthorizePayment:(PKPayment *)payment
                               handler:(void (^)(PKPaymentAuthorizationResult *result))completion API_AVAILABLE(ios(11.0), watchos(4.0));

- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
                   didAuthorizePayment:(PKPayment *)payment
                            completion:(void (^)(PKPaymentAuthorizationStatus status))completion API_DEPRECATED("Use paymentAuthorizationController:didAuthorizePayment:handler: instead to provide more granular errors", ios(10.0, 11.0), watchos(3.0, 4.0));

// Sent to the delegate before the payment is authorized, but after the user has authenticated using
// the side button. Optional.
- (void)paymentAuthorizationControllerWillAuthorizePayment:(PKPaymentAuthorizationController *)controller;


// Sent when the user has selected a new shipping method.  The delegate should determine
// shipping costs based on the shipping method and either the shipping address contact in the original
// PKPaymentRequest or the contact provided by the last call to paymentAuthorizationController:
// didSelectShippingContact:completion:.
//
// The delegate must invoke the completion block with an updated array of PKPaymentSummaryItem objects.
//
// The delegate will receive no further callbacks except paymentAuthorizationControllerDidFinish:
// until it has invoked the completion block.
- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
               didSelectShippingMethod:(PKShippingMethod *)shippingMethod
                               handler:(void (^)(PKPaymentRequestShippingMethodUpdate *requestUpdate))completion API_AVAILABLE(ios(11.0), watchos(4.0));

- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
              didSelectShippingContact:(PKContact *)contact
                               handler:(void (^)(PKPaymentRequestShippingContactUpdate *requestUpdate))completion API_AVAILABLE(ios(11.0), watchos(4.0));


// Sent when the user has selected a new payment card.  Use this delegate callback if you need to
// update the summary items in response to the card type changing (for example, applying credit card surcharges)
//
// The delegate will receive no further callbacks except paymentAuthorizationControllerDidFinish:
// until it has invoked the completion block.

- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
                didSelectPaymentMethod:(PKPaymentMethod *)paymentMethod
                               handler:(void (^)(PKPaymentRequestPaymentMethodUpdate *requestUpdate))completion API_AVAILABLE(ios(11.0), watchos(4.0));

// These delegate methods are deprecated and have been replaced with new callbacks that allow more granular
// and comprehensive errors to be surfaced to users
- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
               didSelectShippingMethod:(PKShippingMethod *)shippingMethod
                            completion:(void (^)(PKPaymentAuthorizationStatus status, NSArray<PKPaymentSummaryItem *> *summaryItems))completion API_DEPRECATED("Use paymentAuthorizationController:didSelectShippingMethod:handler: instead to provide more granular errors", ios(10.0, 11.0), watchos(3.0, 4.0));

- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
              didSelectShippingContact:(PKContact *)contact
                            completion:(void (^)(PKPaymentAuthorizationStatus status, NSArray<PKShippingMethod *> *shippingMethods,
                                                 NSArray<PKPaymentSummaryItem *> *summaryItems))completion API_DEPRECATED("Use paymentAuthorizationController:didSelectShippingContact:handler: instead to provide more granular errors", ios(10.0, 11.0), watchos(3.0, 4.0));

- (void)paymentAuthorizationController:(PKPaymentAuthorizationController *)controller
                didSelectPaymentMethod:(PKPaymentMethod *)paymentMethod
                            completion:(void (^)(NSArray<PKPaymentSummaryItem *> *summaryItems))completion API_DEPRECATED("Use paymentAuthorizationController:didSelectPaymentMethod:handler: instead to provide more granular errors", ios(10.0, 11.0), watchos(3.0, 4.0));

@end

// PKPaymentAuthorizationController prompts the user to authorize a PKPaymentRequest, funding the
// payment amount with a valid payment card.
API_AVAILABLE(ios(10.0), watchos(3.0))
@interface PKPaymentAuthorizationController : NSObject

// Determine whether this device can process payment requests.
// YES if the device is generally capable of making in-app payments.
// NO if the device cannot make in-app payments or if the user is restricted from authorizing payments.
+ (BOOL)canMakePayments;

// Determine whether this device can process payment requests using specific payment network brands.
// Your application should confirm that the user can make payments before attempting to authorize a payment.
// Your application may also want to alter its appearance or behavior when the user is not allowed
// to make payments.
// YES if the user can authorize payments on this device using one of the payment networks supported
// by the merchant.
// NO if the user cannot authorize payments on these networks or if the user is restricted from
// authorizing payments.
+ (BOOL)canMakePaymentsUsingNetworks:(NSArray<PKPaymentNetwork> *)supportedNetworks;

// Determine whether this device can process payments using the specified networks and capabilities bitmask
// See +canMakePaymentsUsingNetworks:
+ (BOOL)canMakePaymentsUsingNetworks:(NSArray<PKPaymentNetwork> *)supportedNetworks capabilities:(PKMerchantCapability)capabilties;

// The controller's delegate.
@property (nonatomic, weak, nullable) id<PKPaymentAuthorizationControllerDelegate> delegate;

// Initialize the controller with a payment request.
- (instancetype)initWithPaymentRequest:(PKPaymentRequest *)request NS_DESIGNATED_INITIALIZER;

// Presents the Apple Pay UI modally over your app. You are responsible for dismissal
- (void)presentWithCompletion:(nullable void(^)(BOOL success))completion;

// Dismisses the Apple Pay UI. Call this when you receive the paymentAuthorizationControllerDidFinish delegate
// callback, or otherwise wish a dismissal to occur
- (void)dismissWithCompletion:(nullable void(^)(void))completion;

@end

NS_ASSUME_NONNULL_END

#endif
// ==========  PassKit.framework/Headers/PKPaymentPass.h
//
//  PKPaymentPass.h
//  PassKit
//
//  Copyright (c) 2014 Apple, Inc. All rights reserved.
//

#ifndef __PKPAYMENTPASS_H
#define __PKPAYMENTPASS_H

#import <PassKit/PKPass.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, PKPaymentPassActivationState) {
    PKPaymentPassActivationStateActivated,
    PKPaymentPassActivationStateRequiresActivation,
    PKPaymentPassActivationStateActivating,
    PKPaymentPassActivationStateSuspended,
    PKPaymentPassActivationStateDeactivated
} API_AVAILABLE(ios(8.0), watchos(3.0));


API_AVAILABLE(ios(8.0), watchos(3.0))
@interface PKPaymentPass : PKPass

@property (nonatomic, copy, readonly) NSString *primaryAccountIdentifier;
@property (nonatomic, copy, readonly) NSString *primaryAccountNumberSuffix;
@property (weak, readonly) NSString *deviceAccountIdentifier;
@property (weak, readonly) NSString *deviceAccountNumberSuffix;
@property (nonatomic, readonly) PKPaymentPassActivationState activationState;

@end
NS_ASSUME_NONNULL_END

#endif // End __PKPAYMENTPASS_H
// ==========  PassKit.framework/Headers/PKPaymentRequest.h
//
//  PKPaymentRequest.h
//
//  Copyright (c) 2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PassKit/PKConstants.h>

#if TARGET_OS_IOS
#import <AddressBook/ABRecord.h>
#endif // TARGET_OS_IOS

#import <PassKit/PKConstants.h>

#ifndef __PKPAYMENTREQUEST_H__
#define __PKPAYMENTREQUEST_H__

@class PKContact;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, PKMerchantCapability) {
    PKMerchantCapability3DS                                  = 1UL << 0,   // Merchant supports 3DS
    PKMerchantCapabilityEMV                                  = 1UL << 1,   // Merchant supports EMV
    PKMerchantCapabilityCredit NS_ENUM_AVAILABLE_IOS(9_0) = 1UL << 2,   // Merchant supports credit
    PKMerchantCapabilityDebit  NS_ENUM_AVAILABLE_IOS(9_0) = 1UL << 3    // Merchant supports debit
} API_AVAILABLE(ios(8.0), watchos(3.0));

typedef NS_OPTIONS(NSUInteger, PKAddressField) {
    PKAddressFieldNone                               = 0UL,      // No address fields required.
    PKAddressFieldPostalAddress                      = 1UL << 0, // Full street address including name, street, city, state/province, postal code, country.
    PKAddressFieldPhone                              = 1UL << 1,
    PKAddressFieldEmail                              = 1UL << 2,
    PKAddressFieldName NS_ENUM_AVAILABLE_IOS(8_3) = 1UL << 3,
    PKAddressFieldAll                                = (PKAddressFieldPostalAddress|PKAddressFieldPhone|PKAddressFieldEmail|PKAddressFieldName)
} API_DEPRECATED("Use PKContactField and -requiredShippingContactFields / -requiredBillingContactFields", ios(8.0, 11.0), watchos(3.0, 4.0));

typedef NS_ENUM(NSUInteger, PKShippingType) {
    PKShippingTypeShipping,
    PKShippingTypeDelivery,
    PKShippingTypeStorePickup,
    PKShippingTypeServicePickup
}  API_AVAILABLE(ios(8.3), watchos(3.0));

typedef NS_ENUM(NSUInteger, PKPaymentSummaryItemType) {
    PKPaymentSummaryItemTypeFinal,      // The payment summary item's amount is known to be correct
    PKPaymentSummaryItemTypePending     // The payment summary item's amount is estimated or unknown - e.g, a taxi fare
}  API_AVAILABLE(ios(9.0), watchos(3.0));

// PKPaymentSummaryItem Defines a line-item for a payment such as tax, shipping, or discount.
API_AVAILABLE(ios(8.0), watchos(3.0))
@interface PKPaymentSummaryItem : NSObject

+ (instancetype)summaryItemWithLabel:(NSString *)label amount:(NSDecimalNumber *)amount;
+ (instancetype)summaryItemWithLabel:(NSString *)label amount:(NSDecimalNumber *)amount type:(PKPaymentSummaryItemType)type API_AVAILABLE(ios(9.0), watchos(3.0));

// A short localized description of the item, e.g. "Tax" or "Gift Card".
@property (nonatomic, copy) NSString *label;

// Same currency as the enclosing PKPaymentRequest.  Negative values are permitted, for example when
// redeeming a coupon. An amount is always required unless the summary item's type is set to pending
@property (nonatomic, copy) NSDecimalNumber *amount;

// Defaults to PKPaymentSummaryItemTypeFinal
// Set to PKPaymentSummaryItemTypePending if the amount of the item is not known at this time
@property (nonatomic, assign) PKPaymentSummaryItemType type API_AVAILABLE(ios(9.0), watchos(3.0));

@end

// Defines a shipping method for delivering physical goods.
API_AVAILABLE(ios(8.0), watchos(3.0))
@interface PKShippingMethod : PKPaymentSummaryItem

// Application-defined unique identifier for this shipping method.  The application will receive this
// in paymentAuthorizationViewController:didAuthorizePayment:completion:.
@property (nonatomic, copy, nullable) NSString *identifier;

// Additional localized information about the shipping method, e.g. "Ships in 24 hours" or
// "Arrives Friday April 4."
@property (nonatomic, copy, nullable) NSString *detail;

@end

// PKPaymentRequest defines an application's request to produce a payment instrument for the
// purchase of goods and services. It encapsulates information about the selling party's payment
// processing capabilities, an amount to pay, and the currency code.
API_AVAILABLE(ios(8.0), watchos(3.0))
@interface PKPaymentRequest : NSObject

// The payment networks and platforms supported for in-app payment
+ (NSArray<PKPaymentNetwork> *)availableNetworks API_AVAILABLE(ios(10.0), watchos(3.0));

// Convenience method to create a payment contact error with the supplied field
// You may optionally provide a localized description to be displayed to the user.
// Available display space for descriptions may be limited, so you should keep your messages concise
+ (NSError *)paymentContactInvalidErrorWithContactField:(PKContactField)field
                                   localizedDescription:(nullable NSString *)localizedDescription API_AVAILABLE(ios(11.0), watchos(4.0));

// Convenience method to create a payment shipping address error with the supplied CNPostalAddressKey and description
+ (NSError *)paymentShippingAddressInvalidErrorWithKey:(NSString *)postalAddressKey
                                  localizedDescription:(nullable NSString *)localizedDescription API_AVAILABLE(ios(11.0), watchos(4.0));

// Convenience method to create a payment billing address error with the supplied CNPostalAddressKey and description
+ (NSError *)paymentBillingAddressInvalidErrorWithKey:(NSString *)postalAddressKey
                                 localizedDescription:(nullable NSString *)localizedDescription API_AVAILABLE(ios(11.0), watchos(4.0));

// Convenience method to create a payment shipping address service error with the supplied description
+ (NSError *)paymentShippingAddressUnserviceableErrorWithLocalizedDescription:(nullable NSString *)localizedDescription API_AVAILABLE(ios(11.0), watchos(4.0));

// Identifies the merchant, as previously agreed with Apple.  Must match one of the merchant
// identifiers in the application's entitlement.
@property (nonatomic, copy) NSString *merchantIdentifier;

// The merchant's ISO country code.
@property (nonatomic, copy) NSString *countryCode;

// The payment networks supported by the merchant, for example @[ PKPaymentNetworkVisa,
// PKPaymentNetworkMasterCard ].  This property constrains payment cards that may fund the payment.
@property (nonatomic, copy) NSArray<PKPaymentNetwork> *supportedNetworks;

// The payment processing capabilities of the merchant.
@property (nonatomic, assign) PKMerchantCapability merchantCapabilities;

// Array of PKPaymentSummaryItem objects which should be presented to the user.
// The last item should be the total you wish to charge, and should not be pending
@property (nonatomic, copy) NSArray<PKPaymentSummaryItem *> *paymentSummaryItems;

// Currency code for this payment.
@property (nonatomic, copy) NSString *currencyCode;

// Indicates which billing contact fields the merchant requires in order to process a transaction.
// Currently only postal address may be requested for billing contact. For all other fields use -requiredShippingContactFields
@property (nonatomic, strong) NSSet<PKContactField> *requiredBillingContactFields API_AVAILABLE(ios(11.0), watchos(4.0));

// Indicates which billing address fields are required. The default is PKAddressFieldNone.
// This property is deprecated and should not be used.
@property (nonatomic, assign) PKAddressField requiredBillingAddressFields API_DEPRECATED_WITH_REPLACEMENT("requiredBillingContactFields", ios(8.0, 11.0), watchos(2.0, 4.0));

// If the merchant already has a billing address on file, set it here.
@property (nonatomic, strong, nullable) PKContact *billingContact API_AVAILABLE(ios(9.0), watchos(3.0));

// Indicates which shipping contact fields the merchant requires in order to process a transactions
//
@property (nonatomic, strong) NSSet<PKContactField> *requiredShippingContactFields API_AVAILABLE(ios(11.0), watchos(4.0));

// Indicates which shipping address fields are required. The default is PKAddressFieldNone.
// This property is deprecated and should not be used
@property (nonatomic, assign) PKAddressField requiredShippingAddressFields API_DEPRECATED_WITH_REPLACEMENT("requiredShippingContactFields", ios(8.0, 11.0), watchos(2.0, 4.0));

// If the merchant already has a shipping address on file, set it here.
@property (nonatomic, strong, nullable) PKContact *shippingContact API_AVAILABLE(ios(9.0), watchos(3.0));

// Shipping methods supported by the merchant.
@property (nonatomic, copy, nullable) NSArray<PKShippingMethod *> *shippingMethods;

// Indicates the display mode for the shipping (e.g, "Pick Up", "Ship To", "Deliver To"). Localized.
// The default is PKShippingTypeShipping
@property (nonatomic, assign) PKShippingType shippingType API_AVAILABLE(ios(8.3), watchos(3.0));

// Optional merchant-supplied information about the payment request.  Examples of this are an order
// or cart identifier.  It will be signed and included in the resulting PKPaymentToken.
@property (nonatomic, copy, nullable) NSData *applicationData;

// Set of two-letter ISO 3166 country codes. When provided will filter the selectable payment passes to those
// issued in the supported countries.
@property (nonatomic, copy, nullable) NSSet<NSString *> *supportedCountries API_AVAILABLE(ios(11.0), watchos(4.0));

#if TARGET_OS_IOS
// These properties have been deprecated and should not be used.
@property (nonatomic, assign, nullable) ABRecordRef shippingAddress __WATCHOS_PROHIBITED API_DEPRECATED("ABRecordRef has been deprecated, and does not support all available address properties. You should migrate to shippingContact.", ios(8.0, 9.0));

@property (nonatomic, assign, nullable) ABRecordRef billingAddress __WATCHOS_PROHIBITED API_DEPRECATED("ABRecordRef has been deprecated, and does not support all available address properties. You should migrate to billingContact.", ios(8.0, 9.0));
#endif

@end

NS_ASSUME_NONNULL_END

#endif // __PKPAYMENTREQUEST_H__
// ==========  PassKit.framework/Headers/PKPaymentAuthorizationViewController.h
//
//  PKPaymentAuthorizationViewController.h
//  PassKit
//
//  Copyright (c) 2014 Apple, Inc. All rights reserved.
//
#if !TARGET_OS_WATCH && !TARGET_OS_TV

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#import <AddressBook/ABRecord.h>
#else
#import <AppKit/AppKit.h>
#import <AddressBook/ABAddressBookC.h>
#endif

#import <PassKit/PKConstants.h>
#import <PassKit/PKPaymentRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class PKPayment;
@class PKContact;
@class PKPaymentMethod;
@class PKShippingMethod;
@class PKPaymentSummaryItem;
@class PKPaymentAuthorizationResult;
@class PKPaymentRequestPaymentMethodUpdate;
@class PKPaymentAuthorizationViewController;
@class PKPaymentRequestShippingMethodUpdate;
@class PKPaymentRequestShippingContactUpdate;

@protocol PKPaymentAuthorizationViewControllerDelegate <NSObject>

@required

// Sent to the delegate when payment authorization is finished.  This may occur when
// the user cancels the request, or after the PKPaymentAuthorizationStatus parameter of the
// paymentAuthorizationViewController:didAuthorizePayment:completion: has been shown to the user.
//
// The delegate is responsible for dismissing the view controller in this method.
- (void)paymentAuthorizationViewControllerDidFinish:(PKPaymentAuthorizationViewController *)controller;

@optional

// Sent to the delegate after the user has acted on the payment request.  The application
// should inspect the payment to determine whether the payment request was authorized.
//
// If the application requested a shipping address then the full addresses is now part of the payment.
//
// The delegate must call completion with an appropriate authorization status, as may be determined
// by submitting the payment credential to a processing gateway for payment authorization.
- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                       didAuthorizePayment:(PKPayment *)payment
                                   handler:(void (^)(PKPaymentAuthorizationResult *result))completion API_AVAILABLE(ios(11.0), watchos(4.0));

// Sent to the delegate before the payment is authorized, but after the user has authenticated using
// passcode or Touch ID. Optional.
- (void)paymentAuthorizationViewControllerWillAuthorizePayment:(PKPaymentAuthorizationViewController *)controller API_AVAILABLE(ios(8.3), watchos(3.0));


// Sent when the user has selected a new shipping method.  The delegate should determine
// shipping costs based on the shipping method and either the shipping address supplied in the original
// PKPaymentRequest or the address fragment provided by the last call to paymentAuthorizationViewController:
// didSelectShippingAddress:completion:.
//
// The delegate must invoke the completion block with an updated array of PKPaymentSummaryItem objects.
//
// The delegate will receive no further callbacks except paymentAuthorizationViewControllerDidFinish:
// until it has invoked the completion block.
- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                   didSelectShippingMethod:(PKShippingMethod *)shippingMethod
                                   handler:(void (^)(PKPaymentRequestShippingMethodUpdate *update))completion API_AVAILABLE(ios(11.0), watchos(4.0));

// Sent when the user has selected a new shipping address.  The delegate should inspect the
// address and must invoke the completion block with an updated array of PKPaymentSummaryItem objects.
//
// The delegate will receive no further callbacks except paymentAuthorizationViewControllerDidFinish:
// until it has invoked the completion block.

- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                  didSelectShippingContact:(PKContact *)contact
                                   handler:(void (^)(PKPaymentRequestShippingContactUpdate *update))completion API_AVAILABLE(ios(11.0), watchos(4.0));

// Sent when the user has selected a new payment card.  Use this delegate callback if you need to
// update the summary items in response to the card type changing (for example, applying credit card surcharges)
//
// The delegate will receive no further callbacks except paymentAuthorizationViewControllerDidFinish:
// until it has invoked the completion block.

- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                    didSelectPaymentMethod:(PKPaymentMethod *)paymentMethod
                                   handler:(void (^)(PKPaymentRequestPaymentMethodUpdate *update))completion API_AVAILABLE(ios(11.0), watchos(4.0));

// Deprecated delegate methods
// These methods are deprecated. Please migrate away from them to their replacements.
- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                       didAuthorizePayment:(PKPayment *)payment
                                completion:(void (^)(PKPaymentAuthorizationStatus status))completion API_DEPRECATED("Use paymentAuthorizationViewController:didAuthorizePayment:handler: instead to provide more granular errors", ios(8.0, 11.0));

- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                   didSelectShippingMethod:(PKShippingMethod *)shippingMethod
                                completion:(void (^)(PKPaymentAuthorizationStatus status, NSArray<PKPaymentSummaryItem *> *summaryItems))completion API_DEPRECATED("Use paymentAuthorizationViewController:didSelectShippingMethod:handler: instead to provide more granular errors", ios(8.0, 11.0));

- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                  didSelectShippingAddress:(ABRecordRef)address
                                completion:(void (^)(PKPaymentAuthorizationStatus status, NSArray<PKShippingMethod *> *shippingMethods,
                                                     NSArray<PKPaymentSummaryItem *> *summaryItems))completion API_DEPRECATED("ABRecordRef has been deprecated. Please migrate away from this delegate callback as soon as possible.", ios(8.0, 9.0));

- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                  didSelectShippingContact:(PKContact *)contact
                                completion:(void (^)(PKPaymentAuthorizationStatus status, NSArray<PKShippingMethod *> *shippingMethods,
                                                     NSArray<PKPaymentSummaryItem *> *summaryItems))completion API_DEPRECATED("Use paymentAuthorizationViewController:didSelectShippingContact:handler: instead to provide more granular errors", ios(8.0, 11.0));

- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                    didSelectPaymentMethod:(PKPaymentMethod *)paymentMethod
                                completion:(void (^)(NSArray<PKPaymentSummaryItem *> *summaryItems))completion API_DEPRECATED("Use paymentAuthorizationViewController:didSelectPaymentMethod:handler: instead to provide more granular errors", ios(8.0, 11.0));

@end

// PKPaymentAuthorizationViewController prompts the user to authorize a PKPaymentRequest, funding the
// payment amount with a valid payment card.
#if TARGET_OS_IPHONE
API_AVAILABLE(ios(8.0))
@interface PKPaymentAuthorizationViewController : UIViewController
#else
NS_CLASS_AVAILABLE_MAC(10_12)
@interface PKPaymentAuthorizationViewController : NSViewController
#endif

// Determine whether this device can process payment requests.
// YES if the device is generally capable of making in-app payments.
// NO if the device cannot make in-app payments or if the user is restricted from authorizing payments.
+ (BOOL)canMakePayments;

// Determine whether this device can process payment requests using specific payment network brands.
// Your application should confirm that the user can make payments before attempting to authorize a payment.
// Your application may also want to alter its appearance or behavior when the user is not allowed
// to make payments.
// YES if the user can authorize payments on this device using one of the payment networks supported
// by the merchant.
// NO if the user cannot authorize payments on these networks or if the user is restricted from
// authorizing payments.
+ (BOOL)canMakePaymentsUsingNetworks:(NSArray<PKPaymentNetwork> *)supportedNetworks;

// Determine whether this device can process payments using the specified networks and capabilities bitmask
// See -canMakePaymentsUsingNetworks:
+ (BOOL)canMakePaymentsUsingNetworks:(NSArray<PKPaymentNetwork> *)supportedNetworks capabilities:(PKMerchantCapability)capabilties API_AVAILABLE(ios(9.0));

// The view controller's delegate.
@property (nonatomic, weak, nullable) id<PKPaymentAuthorizationViewControllerDelegate> delegate;

// Initializes and returns a newly created view controller for the supplied payment.
// It is your responsibility to present and dismiss the view controller using the
// appropriate means for the given device idiom.
- (nullable instancetype)initWithPaymentRequest:(PKPaymentRequest *)request NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

#endif
// ==========  PassKit.framework/Headers/PKPayment.h
//
//  PKPayment.h
//
//  Copyright (c) 2014 Apple, Inc. All rights reserved.
//

#if TARGET_OS_IOS
#import <AddressBook/ABRecord.h>
#endif // TARGET_OS_IOS
#import <PassKit/PKPaymentToken.h>

@class PKShippingMethod;
@class PKContact;

// PKPayment represents the result of a payment request.  Successful payments
// have a PKPaymentToken which contains a payment credential encrypted to the merchant
// identifier specified in the request, and when requested, the user's shipping address
// and chosen shipping method.
API_AVAILABLE(ios(8.0), watchos(3.0))
@interface PKPayment : NSObject

// A PKPaymentToken which contains an encrypted payment credential.
@property (nonatomic, strong, readonly, nonnull) PKPaymentToken *token;

// The full billing address that the user selected for this transaction.  Fields are
// constrained to those specified in the requiredBillingAddressFields property of the original
// PKPaymentRequest object.  This property is only set when the application has set
// the requiredBillingAddressFields property of the PKPaymentRequest.
@property (nonatomic, strong, readonly, nullable) PKContact *billingContact API_AVAILABLE(ios(9.0), watchos(3.0));

#if TARGET_OS_IOS
@property (nonatomic, assign, readonly, nullable) ABRecordRef billingAddress API_DEPRECATED("Use billingContact instead", ios(8.0, 9.0)) __WATCHOS_PROHIBITED;
#endif // TARGET_OS_IOS

// The full shipping address that the user selected for this transaction.  Fields are
// constrained to those specified in the requiredShippingAddressFields property of the original
// PKPaymentRequest object.  This property is only set when the application has set
// the requiredShippingAddressFields property of the PKPaymentRequest.
@property (nonatomic, strong, readonly, nullable) PKContact *shippingContact API_AVAILABLE(ios(9.0), watchos(3.0));

#if TARGET_OS_IOS
@property (nonatomic, assign, readonly, nullable) ABRecordRef shippingAddress API_DEPRECATED("Use shippingContact instead", ios(8.0, 9.0)) __WATCHOS_PROHIBITED;
#endif // TARGET_OS_IOS

// The shipping method that the user chose.  This property is only set when the
// application has set the shippingMethods property of the PKPaymentRequest.
@property (nonatomic, strong, readonly, nullable) PKShippingMethod *shippingMethod;

@end

// ==========  PassKit.framework/Headers/PKTransitPassProperties.h
//
//  PKTransitPassProperties.h
//  PassKit
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class PKPass;

API_AVAILABLE(ios(11.3), watchos(4.3))
@interface PKTransitPassProperties : NSObject

+ (nullable instancetype)passPropertiesForPass:(PKPass *)pass;

@property (nonatomic, copy, readonly) NSDecimalNumber *transitBalance;
@property (nonatomic, copy, readonly) NSString *transitBalanceCurrencyCode;

@property (nonatomic, assign, readonly, getter=isInStation) BOOL inStation;
@property (nonatomic, assign, readonly, getter=isBlacklisted) BOOL blacklisted;

@property (nonatomic, nullable, copy, readonly) NSDate *expirationDate; // nil if pass does not expire

@end

NS_ASSUME_NONNULL_END
// ==========  PassKit.framework/Headers/PKError.h
//
//  PKError.h
//  PassKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#ifndef __PKERROR_H
#define __PKERROR_H

#import <PassKit/PKConstants.h>

NS_ASSUME_NONNULL_BEGIN

// PKPassKitErrorDomain is used for generic errors with PassKit, such as
// adding or removing passes from the user's pass library. PassKit returns these errors to you.
extern NSString * const PKPassKitErrorDomain API_AVAILABLE(ios(6.0), watchos(3.0));


typedef NS_ERROR_ENUM(PKPassKitErrorDomain, PKPassKitErrorCode) {
    PKUnknownError = -1,
    PKInvalidDataError = 1,
    PKUnsupportedVersionError,
    PKInvalidSignature,
    PKNotEntitledError
} API_AVAILABLE(ios(6.0), watchos(3.0));


// PKPaymentErrorDomain is used for errors with in-app or web payments.
// You create your own PKPaymentErrors and return them to indicate problems with a purchase
extern NSString * const PKPaymentErrorDomain API_AVAILABLE(ios(11.0), watchos(4.0));

typedef NS_ERROR_ENUM(PKPaymentErrorDomain, PKPaymentErrorCode) {
    PKPaymentUnknownError = -1,                        // there was an unknown error processing the payment. The user should try again.
    PKPaymentShippingContactInvalidError = 1,          // the user's contact information has an error. Use the PKPaymentErrorKeys in the userInfo to detail the problem.
    PKPaymentBillingContactInvalidError,               // the user's billing contact information has an error. Use the PKPaymentErrorKeys in the userInfo to detail the problem.
    PKPaymentShippingAddressUnserviceableError,         // the user's shipping address is otherwise valid but not serviceable. For example, the address is in Canada and you only ship to the United States, or you don't deliver to PO Boxes.
    
} API_AVAILABLE(ios(11.0), watchos(4.0));

typedef NSString * PKPaymentErrorKey NS_STRING_ENUM;
extern PKPaymentErrorKey const PKPaymentErrorContactFieldUserInfoKey  API_AVAILABLE(ios(11.0), watchos(4.0)); // a PKContactField the error relates to. Use with PKPaymentShippingContactInvalidError
extern PKPaymentErrorKey const PKPaymentErrorPostalAddressUserInfoKey API_AVAILABLE(ios(11.0), watchos(4.0)); // if the error relates to PKContactFieldPostalAddress you may set the specific key here

NS_ASSUME_NONNULL_END
#endif // __PKERROR_H
// ==========  PassKit.framework/Headers/PKPaymentMethod.h
//
//  PKPaymentMethod.h
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#ifndef __PKPAYMENTMETHOD_H
#define __PKPAYMENTMETHOD_H

#import <Foundation/Foundation.h>
#import <PassKit/PKConstants.h>

@class PKPaymentPass;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(ios(9.0), watchos(3.0))
@interface PKPaymentMethod : NSObject

typedef NS_ENUM(NSUInteger, PKPaymentMethodType) {
    PKPaymentMethodTypeUnknown = 0,
    PKPaymentMethodTypeDebit,
    PKPaymentMethodTypeCredit,
    PKPaymentMethodTypePrepaid,
    PKPaymentMethodTypeStore
} API_AVAILABLE(ios(9.0), watchos(3.0));

// A string describing the instrument that's suitable for display
// This property will be nil prior to the user authorizing the payment
@property (nonatomic, copy, readonly, nullable) NSString *displayName;

// The payment network that backs the instrument. Suitable for display.
// This property will be nil prior to the user authorizing the payment
@property (nonatomic, copy, readonly, nullable) PKPaymentNetwork network;

// The underlying instrument type (Credit, Debit, etc)
@property (nonatomic, readonly) PKPaymentMethodType type;

// The payment pass - will only be provided if your app is entitled to view the pass in question
@property (nonatomic, copy, readonly, nullable) PKPaymentPass *paymentPass;

@end

NS_ASSUME_NONNULL_END

#endif // End __PKPAYMENTMETHOD_H

// ==========  PassKit.framework/Headers/PassKit.h
//
//  PassKit.h
//  PassKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#import <PassKit/PKConstants.h>
#import <PassKit/PKObject.h>
#import <PassKit/PKPass.h>
#import <PassKit/PKPaymentPass.h>
#import <PassKit/PKError.h>
#import <PassKit/PKPassLibrary.h>
#if __has_include(<PassKit/PKLabeledValue.h>)
#import <PassKit/PKLabeledValue.h>
#endif
#import <PassKit/PKContact.h>
#if __has_include(<PassKit/PKTransitPassProperties.h>)
#import <PassKit/PKTransitPassProperties.h>
#endif
#if __has_include(<PassKit/PKSuicaPassProperties.h>)
#import <PassKit/PKSuicaPassProperties.h>
#endif
#if __has_include(<PassKit/PKPaymentRequest.h>)
#import <PassKit/PKPaymentRequest.h>
#endif
#if __has_include(<PassKit/PKPaymentRequestStatus.h>)
#import <PassKit/PKPaymentRequestStatus.h>
#endif
#if __has_include(<PassKit/PKPayment.h>)
#import <PassKit/PKPayment.h>
#endif
#if __has_include(<PassKit/PKPaymentMethod.h>)
#import <PassKit/PKPaymentMethod.h>
#endif
#if __has_include(<PassKit/PKPaymentToken.h>)
#import <PassKit/PKPaymentToken.h>
#endif
#if TARGET_OS_IPHONE || TARGET_OS_OSX
#if __has_include(<PassKit/PKPaymentAuthorizationViewController.h>)
#import <PassKit/PKPaymentAuthorizationViewController.h>
#endif
#if __has_include(<PassKit/PKPaymentAuthorizationController.h>)
#import <PassKit/PKPaymentAuthorizationController.h>
#endif
#if __has_include(<PassKit/PKAddPassButton.h>)
#import <PassKit/PKAddPassButton.h>
#endif
#if __has_include(<PassKit/PKPaymentButton.h>)
#import <PassKit/PKPaymentButton.h>
#endif
#if __has_include(<PassKit/PKAddPassesViewController.h>)
#import <PassKit/PKAddPassesViewController.h>
#endif
#if __has_include(<PassKit/PKAddPaymentPassViewController.h>)
#import <PassKit/PKAddPaymentPassViewController.h>
#endif
#endif // TARGET_OS_IPHONE
// ==========  PassKit.framework/Headers/PKAddPaymentPassViewController.h
//
//  PKAddPaymentPassViewController.h
//  PassKit
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#if TARGET_OS_IPHONE

#import <UIKit/UIKit.h>
#import <PassKit/PKConstants.h>
NS_ASSUME_NONNULL_BEGIN

@class PKAddPaymentPassViewController, PKPaymentPass, PKLabeledValue;

typedef NS_ENUM(NSInteger, PKAddPaymentPassError) {
    PKAddPaymentPassErrorUnsupported,
    PKAddPaymentPassErrorUserCancelled,
    PKAddPaymentPassErrorSystemCancelled
} API_AVAILABLE(ios(9.0));

typedef NS_ENUM(NSInteger, PKAddPaymentPassStyle) {
    PKAddPaymentPassStylePayment,
    PKAddPaymentPassStyleAccess
} API_AVAILABLE(ios(12.0));

API_AVAILABLE(ios(9.0))
@interface PKAddPaymentPassRequestConfiguration : NSObject

/* Schemes defined in PKConstants.h.
 * Supported Schemes:
 *  PKEncryptionSchemeECC_V2:
 *      ephemeralPublicKey
 *  PKEncryptionSchemeRSA_V2:
 *      wrappedKey
 */
- (nullable instancetype)initWithEncryptionScheme:(PKEncryptionScheme)encryptionScheme NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, readonly) PKEncryptionScheme encryptionScheme;

/* Display Properties:
 *  At least one of cardholder name or primary account suffix must be supplied.
 */
@property (nonatomic, assign) PKAddPaymentPassStyle style API_AVAILABLE(ios(12.0));
@property (nonatomic, copy, nullable) NSString *cardholderName;
@property (nonatomic, copy, nullable) NSString *primaryAccountSuffix;

@property (nonatomic, copy) NSArray<PKLabeledValue *> *cardDetails API_AVAILABLE(ios(10.1));

@property (nonatomic, copy, nullable) NSString *localizedDescription;

/* Pass Library Filters:
 *  If the filtered set is empty, then all filter will be ignored.
 */
@property (nonatomic, copy, nullable) NSString *primaryAccountIdentifier;

/* Filters introduction page to a specific network - does not function as a restriction.
 */
@property (nonatomic, copy, nullable) PKPaymentNetwork paymentNetwork;

@property (nonatomic, assign) BOOL requiresFelicaSecureElement API_AVAILABLE(ios(10.1));

@end

NS_CLASS_AVAILABLE_IOS(9_0) @interface PKAddPaymentPassRequest : NSObject

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, nullable) NSData *encryptedPassData;
@property (nonatomic, copy, nullable) NSData *activationData;

/* Scheme dependent properties:
 */
@property (nonatomic, copy, nullable) NSData *ephemeralPublicKey;
@property (nonatomic, copy, nullable) NSData *wrappedKey;

@end

@protocol PKAddPaymentPassViewControllerDelegate<NSObject>

/* Certificates is an array of NSData, each a DER encoded X.509 certificate, with the leaf first and root last.
 * The continuation handler must be called within 20 seconds or an error will be displayed. 
 * Subsequent to timeout, the continuation handler is invalid and invocations will be ignored.
 */
- (void)addPaymentPassViewController:(PKAddPaymentPassViewController *)controller
 generateRequestWithCertificateChain:(NSArray<NSData *> *)certificates
                               nonce:(NSData *)nonce
                      nonceSignature:(NSData *)nonceSignature
                   completionHandler:(void(^)(PKAddPaymentPassRequest *request))handler;

/* Error parameter will use codes from the PKAddPaymentPassError enumeration, using the PKPassKitErrorDomain domain.
 */
- (void)addPaymentPassViewController:(PKAddPaymentPassViewController *)controller didFinishAddingPaymentPass:(nullable PKPaymentPass *)pass error:(nullable NSError *)error;

@end

API_AVAILABLE(ios(9.0))
@interface PKAddPaymentPassViewController : UIViewController

+ (BOOL)canAddPaymentPass;

/* This controller should be presented with -[UIViewController presentViewController:animated:completion:].
 */
- (nullable instancetype)initWithRequestConfiguration:(PKAddPaymentPassRequestConfiguration *)configuration
                                             delegate:(nullable id<PKAddPaymentPassViewControllerDelegate>)delegate NS_DESIGNATED_INITIALIZER;

@property (nonatomic, weak, nullable) id<PKAddPaymentPassViewControllerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END

#endif
// ==========  PassKit.framework/Headers/PKPass.h
//
//  PKPass.h
//  PassKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#ifndef __PKPASS_H
#define __PKPASS_H

#import <PassKit/PKObject.h>

typedef NS_ENUM(NSUInteger, PKPassType) {
    PKPassTypeBarcode,
    PKPassTypePayment,
    PKPassTypeAny = ~(NSUInteger)0
} API_AVAILABLE(ios(8.0), watchos(3.0));

@class PKPaymentPass;

#if TARGET_OS_IPHONE
@class UIImage;
#endif

NS_ASSUME_NONNULL_BEGIN
@interface PKPass : PKObject

- (nullable instancetype)initWithData:(NSData *)data error:(NSError **)error;

@property (nonatomic, assign, readonly) PKPassType           passType API_AVAILABLE(ios(8.0), watchos(3.0));
@property (nonatomic, readonly, nullable) PKPaymentPass      *paymentPass API_AVAILABLE(ios(8.0), watchos(3.0));

@property (nonatomic, copy, readonly) NSString               *serialNumber;
@property (nonatomic, copy, readonly) NSString               *passTypeIdentifier;
@property (nonatomic, copy, readonly,nullable) NSURL         *webServiceURL;
@property (nonatomic, copy, readonly,nullable) NSString      *authenticationToken;

#if TARGET_OS_IPHONE
@property (nonatomic, copy, readonly) UIImage                *icon __WATCHOS_PROHIBITED;
#endif

@property (nonatomic, copy, readonly) NSString               *localizedName; // e.g. "Boarding Pass"
@property (nonatomic, copy, readonly) NSString               *localizedDescription; // e.g. "SFO -> LHR"
@property (nonatomic, copy, readonly) NSString               *organizationName; // e.g. "Great Airways"
@property (nonatomic, copy, readonly, nullable) NSDate       *relevantDate; // may be useful for sorting
@property (nonatomic, copy, readonly, nullable) NSDictionary *userInfo API_AVAILABLE(ios(7.0), watchos(3.0));

@property (nonatomic, copy, readonly, nullable) NSURL *passURL; // open to view pass in Wallet app

@property (nonatomic, assign, readonly, getter=isRemotePass)   BOOL       remotePass API_AVAILABLE(ios(9.0), watchos(3.0));
@property (nonatomic, copy, readonly)                          NSString   *deviceName API_AVAILABLE(ios(9.0), watchos(3.0));

- (nullable id)localizedValueForFieldKey:(NSString *)key; // IBOutlet-like; allows access to field data from pass file format

@end
NS_ASSUME_NONNULL_END

#endif // __PKPASS_H
