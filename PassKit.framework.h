// ==========  PassKit.framework/Headers/PKConstants.h
//
//  PKConstants.h
//  PassKit
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString * const PKEncryptionSchemeECC_V2 NS_AVAILABLE_IOS(9_0);

extern NSString * const PKPaymentNetworkAmex NS_AVAILABLE(NA, 8_0);
extern NSString * const PKPaymentNetworkDiscover NS_AVAILABLE(NA, 9_0);
extern NSString * const PKPaymentNetworkMasterCard NS_AVAILABLE(NA, 8_0);
extern NSString * const PKPaymentNetworkPrivateLabel NS_AVAILABLE(NA, 9_0);
extern NSString * const PKPaymentNetworkVisa NS_AVAILABLE(NA, 8_0);// ==========  PassKit.framework/Headers/PKPaymentButton.h
//
//  PKPaymentButton.h
//
//  Copyright © 2014 Apple, Inc. All rights reserved.
//
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, PKPaymentButtonStyle) {
    PKPaymentButtonStyleWhite = 0,
    PKPaymentButtonStyleWhiteOutline,
    PKPaymentButtonStyleBlack
} NS_ENUM_AVAILABLE_IOS(8_3);

typedef NS_ENUM(NSInteger, PKPaymentButtonType) {
    PKPaymentButtonTypePlain = 0,
    PKPaymentButtonTypeBuy,
    PKPaymentButtonTypeSetUp NS_ENUM_AVAILABLE_IOS(9_0)
} NS_ENUM_AVAILABLE_IOS(8_3);

// PKPaymentButton vends a number of Apple Pay related buttons for use inside of your app
// These buttons can be used to prompt the user to pay with Apple Pay, or set up cards for payment
// Refer to the Apple Pay developer documentation for more information on how to use this class
NS_CLASS_AVAILABLE(NA, 8_3) @interface PKPaymentButton : UIButton

+ (instancetype)buttonWithType:(PKPaymentButtonType)buttonType style:(PKPaymentButtonStyle)buttonStyle;

- (instancetype)initWithPaymentButtonType:(PKPaymentButtonType)type paymentButtonStyle:(PKPaymentButtonStyle)style NS_AVAILABLE_IOS(9_0) NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END// ==========  PassKit.framework/Headers/PKContact.h
//
//  PKContact.h
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/Contacts.h>

NS_CLASS_AVAILABLE(NA, 9_0)
@interface PKContact : NSObject

@property (nonatomic, retain, nullable) NSPersonNameComponents *name;

@property (nonatomic, retain, nullable) CNPostalAddress *postalAddress;
@property (nonatomic, retain, nullable) NSString        *emailAddress;
@property (nonatomic, retain, nullable) CNPhoneNumber   *phoneNumber;

@end
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
} NS_ENUM_AVAILABLE_IOS(7_0);


typedef NS_ENUM(NSUInteger, PKAutomaticPassPresentationSuppressionResult) {
    PKAutomaticPassPresentationSuppressionResultNotSupported = 0,   // Suppression is not supported for this device
    PKAutomaticPassPresentationSuppressionResultAlreadyPresenting,  // Passes are already being presented and cannot be suppressed
    PKAutomaticPassPresentationSuppressionResultDenied,             // Suppression was denied due to lack of entitlement
    PKAutomaticPassPresentationSuppressionResultCancelled,          // Suppression was cancelled before the response handler was fired
    PKAutomaticPassPresentationSuppressionResultSuccess             // Suppression of automatic pass presentation was successful
} __WATCHOS_PROHIBITED NS_ENUM_AVAILABLE_IOS(9_0);

typedef NSUInteger PKSuppressionRequestToken;

NS_CLASS_AVAILABLE_IOS(6_0)
@interface PKPassLibrary : NSObject

// The library is not available on iPad in 6.0.
+ (BOOL)isPassLibraryAvailable NS_AVAILABLE_IOS(6_0);

// These methods may be used to temporarily disable the automatic presentation of passes when a device encounters a contactless field.
// Use of these methods require an entitlement. Otherwise, requesting will always return a PKAutomaticPassPresentationSuppressionResultDenied as the result.
+ (PKSuppressionRequestToken)requestAutomaticPassPresentationSuppressionWithResponseHandler:(void(^)(PKAutomaticPassPresentationSuppressionResult result))responseHandler __WATCHOS_PROHIBITED NS_AVAILABLE_IOS(9_0) NS_EXTENSION_UNAVAILABLE("Not available to extensions");
+ (void)endAutomaticPassPresentationSuppressionWithRequestToken:(PKSuppressionRequestToken)requestToken __WATCHOS_PROHIBITED NS_AVAILABLE_IOS(9_0) NS_EXTENSION_UNAVAILABLE("Not available to extensions");
+ (BOOL)isSuppressingAutomaticPassPresentation __WATCHOS_PROHIBITED NS_AVAILABLE_IOS(9_0) NS_EXTENSION_UNAVAILABLE("Not available to extensions");

// If device supports adding payment passes, this method will return YES. Otherwise, NO will be returned.
+ (BOOL)isPaymentPassActivationAvailable NS_DEPRECATED_IOS(8_0, 9_0, "Use -[PKPassLibrary isPaymentPassActivationAvailable] instead");

// If this pass library supports activating payment passes, this method will return YES. Otherwise, NO will be returned.
- (BOOL)isPaymentPassActivationAvailable NS_AVAILABLE_IOS(9_0);

// These return only local passes the process is entitled to access.
- (NSArray<PKPass *> *)passes;
- (nullable PKPass *)passWithPassTypeIdentifier:(NSString *)identifier serialNumber:(NSString *)serialNumber;
- (NSArray<PKPass *> *)passesOfType:(PKPassType)passType NS_AVAILABLE_IOS(8_0);

// This returns the remote payment passes from attached devices
- (NSArray<PKPaymentPass *> *)remotePaymentPasses NS_AVAILABLE_IOS(9_0);

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
- (void)addPasses:(NSArray<PKPass *> *)passes withCompletionHandler:(nullable void(^)(PKPassLibraryAddPassesStatus status))completion NS_AVAILABLE_IOS(7_0);

// Opens the card setup flow (in Wallet on iPhone, Settings on iPad). Use this to direct a user to card setup directly from your app.
- (void)openPaymentSetup __WATCHOS_PROHIBITED NS_AVAILABLE_IOS(8_3);

// Returns YES if either the current device or an attached device both supports adding payment passes and does not already contain
// a payment pass with the supplied primary account identifier.
- (BOOL)canAddPaymentPassWithPrimaryAccountIdentifier:(NSString *)primaryAccountIdentifier NS_AVAILABLE_IOS(9_0);

// These methods may be utilized to activate a payment pass that is provisioned but currently in the inactive state, by providing
// either a cryptographic OTP, or an activation code.
- (void)activatePaymentPass:(PKPaymentPass *)paymentPass withActivationData:(NSData *)activationData completion:(nullable void(^)(BOOL success, NSError* error))completion __WATCHOS_PROHIBITED NS_AVAILABLE_IOS(8_0);
- (void)activatePaymentPass:(PKPaymentPass *)paymentPass withActivationCode:(NSString *)activationCode completion:(nullable void(^)(BOOL success, NSError* error))completion __WATCHOS_PROHIBITED NS_DEPRECATED_IOS(8_0, 9_0, "Use activatePaymentPass:withActivationData:completion: instead");
@end

// This notification is issued by a library instance, with that instance as the sender.  If there are no instantiated library objects,
// no notifications. There are no guarantees about what thread or queue these come in on.
extern NSString * const PKPassLibraryDidChangeNotification NS_AVAILABLE_IOS(6_0);
extern NSString * const PKPassLibraryRemotePaymentPassesDidChangeNotification NS_AVAILABLE_IOS(9_0);

// Entries in user info dictionary for PKPassLibraryDidChangeNotification.
// - PKPassLibraryAddedPassesUserInfoKey is the key for an array of passes
// - PKPassLibraryReplacementPassesUserInfoKey is the key for an array of passes
// - PKPassLibraryRemovedPassInfosUserInfoKey is the key for an array of dictionaries, each of which has keys
//   PKPassLibraryPassTypeIdentifierUserInfoKey and PKPassLibrarySerialNumberUserInfoKey mapping to strings.
extern NSString *const PKPassLibraryAddedPassesUserInfoKey NS_AVAILABLE_IOS(6_0);
extern NSString *const PKPassLibraryReplacementPassesUserInfoKey NS_AVAILABLE_IOS(6_0);
extern NSString *const PKPassLibraryRemovedPassInfosUserInfoKey NS_AVAILABLE_IOS(6_0);

extern NSString *const PKPassLibraryPassTypeIdentifierUserInfoKey NS_AVAILABLE_IOS(6_0);
extern NSString *const PKPassLibrarySerialNumberUserInfoKey NS_AVAILABLE_IOS(6_0);

NS_ASSUME_NONNULL_END
// ==========  PassKit.framework/Headers/PKAddPassButton.h
//
//  PKAddPassButton.h
//  PassKit
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, PKAddPassButtonStyle) {
    PKAddPassButtonStyleBlack = 0,
    PKAddPassButtonStyleBlackOutline,
} NS_ENUM_AVAILABLE_IOS(9_0);

// Use PKAddPassButton to show an "Add to Apple Wallet" button. Two types are available for barcode or payment passes.
// Refer to the Apple Pay developer documentation for more information on how to use this class
NS_CLASS_AVAILABLE_IOS(9_0) @interface PKAddPassButton : UIButton

+ (instancetype)addPassButtonWithStyle:(PKAddPassButtonStyle)addPassButtonStyle;

- (instancetype)initWithAddPassButtonStyle:(PKAddPassButtonStyle)style NS_DESIGNATED_INITIALIZER;

@property (nonatomic, assign) PKAddPassButtonStyle addPassButtonStyle UI_APPEARANCE_SELECTOR;

@end

NS_ASSUME_NONNULL_END// ==========  PassKit.framework/Headers/PKObject.h
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

#endif
// ==========  PassKit.framework/Headers/PKAddPassesViewController.h
//
//  PKAddPassesViewController.h
//  PassKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@class PKPass;
@class PKAddPassesViewController;

NS_ASSUME_NONNULL_BEGIN

@protocol PKAddPassesViewControllerDelegate <NSObject>
@optional
-(void)addPassesViewControllerDidFinish:(PKAddPassesViewController *)controller; // delegate should dismiss presentation
@end

NS_CLASS_AVAILABLE(NA, 6_0)
@interface PKAddPassesViewController : UIViewController

/* controller should be presented with -presentViewController:animated:completion:
 pass should be a pass you want the user to add.
 */
- (instancetype)initWithPass:(PKPass *)pass;
- (instancetype)initWithPasses:(NSArray<PKPass *> *)passes NS_AVAILABLE_IOS(7_0);
+ (BOOL)canAddPasses NS_AVAILABLE_IOS(8_0);

@property(nonatomic,assign,nullable) id <PKAddPassesViewControllerDelegate> delegate;

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
NS_CLASS_AVAILABLE(NA, 8_0)
@interface PKPaymentToken : NSObject

// Describes the properties of the underlying payment instrument selected to fund the payment
@property (nonatomic, readonly) PKPaymentMethod *paymentMethod NS_AVAILABLE_IOS(9_0);

// A string that describes the payment instrument the user has selected to fund the payment.
// Suitable for display, e.g. "Amex 1234".
@property (nonatomic, readonly) NSString *paymentInstrumentName NS_DEPRECATED_IOS(8_0, 9_0, "Use paymentMethod instead");

// Payment network for the card that funds the payment.
@property (nonatomic, readonly) NSString *paymentNetwork NS_DEPRECATED_IOS(8_0, 9_0, "Use paymentMethod instead");

// A string that describes a globally unique identifier for this transaction that can be used
// for receipt purposes.
@property (nonatomic, readonly) NSString *transactionIdentifier;

// UTF-8 encoded JSON dictionary of encrypted payment data.  Ready for transmission to
// merchant's e-commerce backend for decryption and submission to a payment processor's
// gateway.
@property (nonatomic, readonly) NSData *paymentData;

@end

NS_ASSUME_NONNULL_END// ==========  PassKit.framework/Headers/PKPaymentPass.h
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
} NS_ENUM_AVAILABLE_IOS(8_0);


NS_CLASS_AVAILABLE_IOS(8_0)
@interface PKPaymentPass : PKPass

@property (nonatomic,copy,readonly) NSString                      *primaryAccountIdentifier;
@property (nonatomic,copy,readonly) NSString                      *primaryAccountNumberSuffix;
@property (readonly)                NSString                      *deviceAccountIdentifier;
@property (readonly)                NSString                      *deviceAccountNumberSuffix;
@property (nonatomic, readonly)     PKPaymentPassActivationState  activationState;

@end
NS_ASSUME_NONNULL_END

#endif
// ==========  PassKit.framework/Headers/PKPaymentRequest.h
//
//  PKPaymentRequest.h
//
//  Copyright (c) 2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AddressBook/ABRecord.h>

@class PKContact;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, PKMerchantCapability) {
    PKMerchantCapability3DS                                 = 1UL << 0,   // Merchant supports 3DS
    PKMerchantCapabilityEMV                                 = 1UL << 1,   // Merchant supports EMV
    PKMerchantCapabilityCredit NS_ENUM_AVAILABLE_IOS(9_0)   = 1UL << 2,   // Merchant supports credit
    PKMerchantCapabilityDebit  NS_ENUM_AVAILABLE_IOS(9_0)   = 1UL << 3    // Merchant supports debit
} NS_ENUM_AVAILABLE(NA, 8_0);

typedef NS_OPTIONS(NSUInteger, PKAddressField) {
    PKAddressFieldNone                              = 0UL,      // No address fields required.
    PKAddressFieldPostalAddress                     = 1UL << 0, // Full street address including name, street, city, state/province, postal code, country.
    PKAddressFieldPhone                             = 1UL << 1,
    PKAddressFieldEmail                             = 1UL << 2,
    PKAddressFieldName NS_ENUM_AVAILABLE_IOS(8_3)   = 1UL << 3,
    PKAddressFieldAll                               = (PKAddressFieldPostalAddress|PKAddressFieldPhone|PKAddressFieldEmail|PKAddressFieldName)
} NS_ENUM_AVAILABLE(NA, 8_0);

typedef NS_ENUM(NSUInteger, PKShippingType) {
    PKShippingTypeShipping,
    PKShippingTypeDelivery,
    PKShippingTypeStorePickup,
    PKShippingTypeServicePickup
} NS_ENUM_AVAILABLE(NA, 8_3);

typedef NS_ENUM(NSUInteger, PKPaymentSummaryItemType) {
    PKPaymentSummaryItemTypeFinal,      // The payment summary item's amount is known to be correct
    PKPaymentSummaryItemTypePending     // The payment summary item's amount is estimated or unknown - e.g, a taxi fare
} NS_ENUM_AVAILABLE(NA, 9_0);

// PKPaymentSummaryItem Defines a line-item for a payment such as tax, shipping, or discount.
NS_CLASS_AVAILABLE(NA, 8_0)
@interface PKPaymentSummaryItem : NSObject

+ (instancetype)summaryItemWithLabel:(NSString *)label amount:(NSDecimalNumber *)amount;
+ (instancetype)summaryItemWithLabel:(NSString *)label amount:(NSDecimalNumber *)amount type:(PKPaymentSummaryItemType)type NS_AVAILABLE(NA, 9_0);

// A short localized description of the item, e.g. "Tax" or "Gift Card".
@property (nonatomic, copy) NSString *label;

// Same currency as the enclosing PKPaymentRequest.  Negative values are permitted, for example when
// redeeming a coupon. An amount is always required unless the summary item's type is set to pending
@property (nonatomic, copy) NSDecimalNumber *amount;

// Defaults to PKPaymentSummaryItemTypeFinal
// Set to PKPaymentSummaryItemTypePending if the amount of the item is not known at this time
@property (nonatomic, assign) PKPaymentSummaryItemType type NS_AVAILABLE(NA, 9_0);

@end

// Defines a shipping method for delivering physical goods.
NS_CLASS_AVAILABLE(NA, 8_0)
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
NS_CLASS_AVAILABLE(NA, 8_0)
@interface PKPaymentRequest : NSObject

// Identifies the merchant, as previously agreed with Apple.  Must match one of the merchant
// identifiers in the application's entitlement.
@property (nonatomic, copy) NSString *merchantIdentifier;

// The merchant's ISO country code.
@property (nonatomic, copy) NSString *countryCode;

// The payment networks supported by the merchant, for example @[ PKPaymentNetworkVisa,
// PKPaymentNetworkMasterCard ].  This property constrains payment cards that may fund the payment.
@property (nonatomic, copy) NSArray<NSString *> *supportedNetworks;

// The payment processing capabilities of the merchant.
@property (nonatomic, assign) PKMerchantCapability merchantCapabilities;

// Array of PKPaymentSummaryItem objects which should be presented to the user.
// The last item should be the total you wish to charge, and should not be pending
@property (nonatomic, copy) NSArray<PKPaymentSummaryItem *> *paymentSummaryItems;

// Currency code for this payment.
@property (nonatomic, copy) NSString *currencyCode;

// Indicates which billing address fields the merchant requires in order to process a transaction.
// The default is PKAddressFieldNone.
@property (nonatomic, assign) PKAddressField requiredBillingAddressFields;

// If the merchant already has a billing address on file, set it here.
@property (nonatomic, assign, nullable) ABRecordRef billingAddress NS_DEPRECATED_IOS(8_0, 9_0, "Use billingContact instead");
@property (nonatomic, retain, nullable) PKContact *billingContact NS_AVAILABLE_IOS(9_0);

// Indicates which shipping address fields the merchant requires in order to process a transaction.
// The default is PKAddressFieldNone.
@property (nonatomic, assign) PKAddressField requiredShippingAddressFields;

// If the merchant already has a shipping address on file, set it here.
@property (nonatomic, assign, nullable) ABRecordRef shippingAddress NS_DEPRECATED_IOS(8_0, 9_0, "Use shippingContact instead");
@property (nonatomic, retain, nullable) PKContact *shippingContact NS_AVAILABLE_IOS(9_0);

// Shipping methods supported by the merchant.
@property (nonatomic, copy, nullable) NSArray<PKShippingMethod *> *shippingMethods;

// Indicates the display mode for the shipping (e.g, "Pick Up", "Ship To", "Deliver To"). Localized.
// The default is PKShippingTypeShipping
@property (nonatomic, assign) PKShippingType shippingType NS_AVAILABLE_IOS(8_3);

// Optional merchant-supplied information about the payment request.  Examples of this are an order
// or cart identifier.  It will be signed and included in the resulting PKPaymentToken.
@property (nonatomic, copy, nullable) NSData *applicationData;

@end

NS_ASSUME_NONNULL_END
// ==========  PassKit.framework/Headers/PKPaymentAuthorizationViewController.h
//
//  PKPaymentAuthorizationViewController.h
//  PassKit
//
//  Copyright (c) 2014 Apple, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AddressBook/ABRecord.h>
#import <PassKit/PKPaymentRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class PKPayment;
@class PKContact;
@class PKPaymentMethod;
@class PKShippingMethod;
@class PKPaymentSummaryItem;
@class PKPaymentAuthorizationViewController;

typedef NS_ENUM(NSInteger, PKPaymentAuthorizationStatus) {
    PKPaymentAuthorizationStatusSuccess, // Merchant auth'd (or expects to auth) the transaction successfully.
    PKPaymentAuthorizationStatusFailure, // Merchant failed to auth the transaction.
    
    PKPaymentAuthorizationStatusInvalidBillingPostalAddress,  // Merchant refuses service to this billing address.
    PKPaymentAuthorizationStatusInvalidShippingPostalAddress, // Merchant refuses service to this shipping address.
    PKPaymentAuthorizationStatusInvalidShippingContact,       // Supplied contact information is insufficient.
    
} NS_ENUM_AVAILABLE(NA, 8_0);

@protocol PKPaymentAuthorizationViewControllerDelegate <NSObject>

@required

// Sent to the delegate after the user has acted on the payment request.  The application
// should inspect the payment to determine whether the payment request was authorized.
//
// If the application requested a shipping address then the full addresses is now part of the payment.
//
// The delegate must call completion with an appropriate authorization status, as may be determined
// by submitting the payment credential to a processing gateway for payment authorization.
- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                       didAuthorizePayment:(PKPayment *)payment
                                completion:(void (^)(PKPaymentAuthorizationStatus status))completion;


// Sent to the delegate when payment authorization is finished.  This may occur when
// the user cancels the request, or after the PKPaymentAuthorizationStatus parameter of the
// paymentAuthorizationViewController:didAuthorizePayment:completion: has been shown to the user.
//
// The delegate is responsible for dismissing the view controller in this method.
- (void)paymentAuthorizationViewControllerDidFinish:(PKPaymentAuthorizationViewController *)controller;

@optional


// Sent to the delegate before the payment is authorized, but after the user has authenticated using
// passcode or Touch ID. Optional.
- (void)paymentAuthorizationViewControllerWillAuthorizePayment:(PKPaymentAuthorizationViewController *)controller NS_AVAILABLE_IOS(8_3);


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
                                completion:(void (^)(PKPaymentAuthorizationStatus status, NSArray<PKPaymentSummaryItem *> *summaryItems))completion;

// Sent when the user has selected a new shipping address.  The delegate should inspect the
// address and must invoke the completion block with an updated array of PKPaymentSummaryItem objects.
//
// The delegate will receive no further callbacks except paymentAuthorizationViewControllerDidFinish:
// until it has invoked the completion block.
- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                  didSelectShippingAddress:(ABRecordRef)address
                                completion:(void (^)(PKPaymentAuthorizationStatus status, NSArray<PKShippingMethod *> *shippingMethods,
                                                     NSArray<PKPaymentSummaryItem *> *summaryItems))completion NS_DEPRECATED_IOS(8_0, 9_0, "Use the CNContact backed delegate method instead");

- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                  didSelectShippingContact:(PKContact *)contact
                                completion:(void (^)(PKPaymentAuthorizationStatus status, NSArray<PKShippingMethod *> *shippingMethods,
                                                     NSArray<PKPaymentSummaryItem *> *summaryItems))completion NS_AVAILABLE_IOS(9_0);


// Sent when the user has selected a new payment card.  Use this delegate callback if you need to
// update the summary items in response to the card type changing (for example, applying credit card surcharges)
//
// The delegate will receive no further callbacks except paymentAuthorizationViewControllerDidFinish:
// until it has invoked the completion block.
- (void)paymentAuthorizationViewController:(PKPaymentAuthorizationViewController *)controller
                    didSelectPaymentMethod:(PKPaymentMethod *)paymentMethod
                                completion:(void (^)(NSArray<PKPaymentSummaryItem *> *summaryItems))completion NS_AVAILABLE_IOS(9_0);

@end

// PKPaymentAuthorizationViewController prompts the user to authorize a PKPaymentRequest, funding the
// payment amount with a valid payment card.
NS_CLASS_AVAILABLE(NA, 8_0)
@interface PKPaymentAuthorizationViewController : UIViewController

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
+ (BOOL)canMakePaymentsUsingNetworks:(NSArray<NSString *> *)supportedNetworks;

// Determine whether this device can process payments using the specified networks and capabilities bitmask
// See -canMakePaymentsUsingNetworks:
+ (BOOL)canMakePaymentsUsingNetworks:(NSArray<NSString *> *)supportedNetworks capabilities:(PKMerchantCapability)capabilties NS_AVAILABLE_IOS(9_0);

// The view controller's delegate.
@property (nonatomic, assign, nullable) id<PKPaymentAuthorizationViewControllerDelegate> delegate;

// Initializes and returns a newly created view controller for the supplied payment.
// It is your responsibility to present and dismiss the view controller using the
// appropriate means for the given device idiom.
- (instancetype)initWithPaymentRequest:(PKPaymentRequest *)request NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END// ==========  PassKit.framework/Headers/PKPayment.h
//
//  PKPayment.h
//
//  Copyright (c) 2014 Apple, Inc. All rights reserved.
//

#import <AddressBook/ABRecord.h>
#import <PassKit/PKPaymentToken.h>

@class PKShippingMethod;
@class PKContact;

// PKPayment represents the result of a payment request.  Successful payments
// have a PKPaymentToken which contains a payment credential encrypted to the merchant
// identifier specified in the request, and when requested, the user's shipping address
// and chosen shipping method.
NS_CLASS_AVAILABLE(NA, 8_0)
@interface PKPayment : NSObject

// A PKPaymentToken which contains an encrypted payment credential.
@property (nonatomic, readonly, nonnull) PKPaymentToken *token;

// The full billing address that the user selected for this transaction.  Fields are
// constrained to those specified in the requiredBillingAddressFields property of the original
// PKPaymentRequest object.  This property is only set when the application has set
// the requiredBillingAddressFields property of the PKPaymentRequest.
@property (nonatomic, readonly, nullable) ABRecordRef billingAddress NS_DEPRECATED_IOS(8_0, 9_0, "Use billingContact instead");
@property (nonatomic, readonly, nullable) PKContact *billingContact NS_AVAILABLE_IOS(9_0);

// The full shipping address that the user selected for this transaction.  Fields are
// constrained to those specified in the requiredShippingAddressFields property of the original
// PKPaymentRequest object.  This property is only set when the application has set
// the requiredShippingAddressFields property of the PKPaymentRequest.
@property (nonatomic, readonly, nullable) ABRecordRef shippingAddress NS_DEPRECATED_IOS(8_0, 9_0, "Use shippingContact instead");;
@property (nonatomic, readonly, nullable) PKContact *shippingContact NS_AVAILABLE_IOS(9_0);

// The shipping method that the user chose.  This property is only set when the
// application has set the shippingMethods property of the PKPaymentRequest.
@property (nonatomic, readonly, nullable) PKShippingMethod *shippingMethod;

@end

// ==========  PassKit.framework/Headers/PKError.h
//
//  PKError.h
//  PassKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#ifndef __PKERROR_H
#define __PKERROR_H

// Domain for NSError
extern NSString * const PKPassKitErrorDomain NS_AVAILABLE_IOS(6_0);

typedef NS_ENUM(NSInteger, PKPassKitErrorCode) {
    PKUnknownError = -1,
    PKInvalidDataError = 1,
    PKUnsupportedVersionError,
    PKInvalidSignature,
    PKNotEntitledError
} NS_ENUM_AVAILABLE_IOS(6_0);

#endif
// ==========  PassKit.framework/Headers/PKPaymentMethod.h
//
//  PKPaymentMethod.h
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#ifndef __PKPAYMENTMETHOD_H
#define __PKPAYMENTMETHOD_H

#import <Foundation/Foundation.h>

@class PKPaymentPass;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(NA, 9_0)
@interface PKPaymentMethod : NSObject

typedef NS_OPTIONS(NSUInteger, PKPaymentMethodType) {
    PKPaymentMethodTypeUnknown = 0,
    PKPaymentMethodTypeDebit,
    PKPaymentMethodTypeCredit,
    PKPaymentMethodTypePrepaid,
    PKPaymentMethodTypeStore,
} NS_ENUM_AVAILABLE(NA, 9_0);

// A string describing the instrument that's suitable for display
@property (nonatomic, readonly, nullable) NSString *displayName;

// The payment network that backs the instrument. Suitable for display.
@property (nonatomic, readonly, nullable) NSString *network;

// The underlying instrument type (Credit, Debit, etc)
@property (nonatomic, readonly) PKPaymentMethodType type;

// The payment pass - will only be provided if your app is entitled to view the pass in question
@property (nonatomic, readonly, nullable) PKPaymentPass *paymentPass;

@end

NS_ASSUME_NONNULL_END

#endif

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
#import <PassKit/PKContact.h>
#if __has_include(<PassKit/PKAddPassesViewController.h>)
#import <PassKit/PKAddPassesViewController.h>
#endif
#if __has_include(<PassKit/PKAddPaymentPassViewController.h>)
#import <PassKit/PKAddPaymentPassViewController.h>
#endif
#if __has_include(<PassKit/PKPaymentRequest.h>)
#import <PassKit/PKPaymentRequest.h>
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
#if __has_include(<PassKit/PKPaymentAuthorizationViewController.h>)
#import <PassKit/PKPaymentAuthorizationViewController.h>
#endif
#if __has_include(<PassKit/PKAddPassButton.h>)
#import <PassKit/PKAddPassButton.h>
#endif
#if __has_include(<PassKit/PKPaymentButton.h>)
#import <PassKit/PKPaymentButton.h>
#endif
// ==========  PassKit.framework/Headers/PKAddPaymentPassViewController.h
//
//  PKAddPaymentPassViewController.h
//  PassKit
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN

@class PKAddPaymentPassViewController, PKPaymentPass;

typedef NS_ENUM(NSInteger, PKAddPaymentPassError) {
    PKAddPaymentPassErrorUnsupported,
    PKAddPaymentPassErrorUserCancelled,
    PKAddPaymentPassErrorSystemCancelled
} NS_ENUM_AVAILABLE_IOS(9_0);

NS_CLASS_AVAILABLE_IOS(9_0) @interface PKAddPaymentPassRequestConfiguration : NSObject

/* Schemes defined in PKConstants.h.
 * Supported Schemes:
 *  PKEncryptionSchemeECC_V2:
 *      ephemeralPublicKey
 */
- (nullable instancetype)initWithEncryptionScheme:(NSString *)encryptionScheme NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, readonly) NSString *encryptionScheme;

/* Display Properties:
 *  At least one of cardholder name or primary account suffix must be supplied.
 */
@property (nonatomic, copy, nullable) NSString *cardholderName;
@property (nonatomic, copy, nullable) NSString *primaryAccountSuffix;
@property (nonatomic, copy, nullable) NSString *localizedDescription;

/* Pass Library Filters:
 *  If the filtered set is empty, then all filter will be ignored.
 */
@property (nonatomic, copy, nullable) NSString *primaryAccountIdentifier;

/* Filters introduction page to a specific network - does not function as a restriction.
 */
@property (nonatomic, copy, nullable) NSString *paymentNetwork;

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
 * The continuation handler must be called within 20 seconds, or the flow will terminate with
 * PKAddPaymentPassErrorInvalidRequest.
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

NS_CLASS_AVAILABLE_IOS(9_0) @interface PKAddPaymentPassViewController : UIViewController

+ (BOOL)canAddPaymentPass;

/* This controller should be presented with -[UIViewController presentViewController:animated:completion:].
 */
- (nullable instancetype)initWithRequestConfiguration:(PKAddPaymentPassRequestConfiguration *)configuration
                                             delegate:(nullable id<PKAddPaymentPassViewControllerDelegate>)delegate NS_DESIGNATED_INITIALIZER;

@property (nonatomic, weak, nullable) id<PKAddPaymentPassViewControllerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END// ==========  PassKit.framework/Headers/PKPass.h
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
    PKPassTypeAny = ~0
} NS_ENUM_AVAILABLE_IOS(8_0);

@class PKPaymentPass;
@class UIImage;

NS_ASSUME_NONNULL_BEGIN
@interface PKPass : PKObject

- (instancetype)initWithData:(NSData *)data error:(NSError **)error;

@property (nonatomic,assign,readonly) PKPassType                passType NS_AVAILABLE_IOS(8_0);
@property (nonatomic,assign,readonly,nullable) PKPaymentPass    *paymentPass NS_AVAILABLE_IOS(8_0);

@property (nonatomic,copy,readonly) NSString                *serialNumber;
@property (nonatomic,copy,readonly) NSString                *passTypeIdentifier;
@property (nonatomic,copy,readonly,nullable) NSURL          *webServiceURL;
@property (nonatomic,copy,readonly,nullable) NSString       *authenticationToken;

@property (nonatomic,copy,readonly) UIImage                 *icon __WATCHOS_PROHIBITED;
@property (nonatomic,copy,readonly) NSString                *localizedName; // e.g. "Boarding Pass"
@property (nonatomic,copy,readonly) NSString                *localizedDescription; // e.g. "SFO -> LHR"
@property (nonatomic,copy,readonly) NSString                *organizationName; // e.g. "Great Airways"
@property (nonatomic,copy,readonly,nullable) NSDate         *relevantDate; // may be useful for sorting
@property (nonatomic,copy,readonly,nullable) NSDictionary   *userInfo NS_AVAILABLE_IOS(7_0);

@property (nonatomic,copy,readonly) NSURL *passURL; // open to view pass in Passbook.app

@property (nonatomic,assign,readonly,getter=isRemotePass)   BOOL        remotePass NS_AVAILABLE_IOS(9_0);
@property (nonatomic,copy,readonly)                         NSString    *deviceName NS_AVAILABLE_IOS(9_0);

- (nullable id)localizedValueForFieldKey:(NSString *)key; // IBOutlet-like; allows access to field data from pass file format

@end
NS_ASSUME_NONNULL_END

#endif
