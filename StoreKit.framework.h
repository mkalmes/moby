// ==========  StoreKit.framework/Headers/SKPaymentQueue.h
//
//  SKPaymentQueue.h
//  StoreKit
//
//  Copyright 2009-2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKDownload;
@class SKPayment;
@class SKPaymentTransaction;
@class SKProduct;
@protocol SKPaymentTransactionObserver;

NS_ASSUME_NONNULL_BEGIN

// SKPaymentQueue interacts with the server-side payment queue
SK_EXTERN_CLASS_AVAILABLE(10_7, 3_0) @interface SKPaymentQueue : NSObject {
@private
    id _internal;
}

+ (instancetype)defaultQueue NS_AVAILABLE(10_7, 3_0);

// NO if this device is not able or allowed to make payments
+ (BOOL)canMakePayments NS_AVAILABLE(10_7, 3_0);

// Asynchronous.  Add a payment to the server queue.  The payment is copied to add an SKPaymentTransaction to the transactions array.  The same payment can be added multiple times to create multiple transactions.
- (void)addPayment:(SKPayment *)payment NS_AVAILABLE(10_7, 3_0);

// Asynchronous.  Will add completed transactions for the current user back to the queue to be re-completed.  User will be asked to authenticate.  Observers will receive 0 or more -paymentQueue:updatedTransactions:, followed by either -paymentQueueRestoreCompletedTransactionsFinished: on success or -paymentQueue:restoreCompletedTransactionsFailedWithError: on failure.  In the case of partial success, some transactions may still be delivered.
- (void)restoreCompletedTransactions  NS_AVAILABLE(10_7, 3_0);
- (void)restoreCompletedTransactionsWithApplicationUsername:(nullable NSString *)username NS_AVAILABLE(10_9, 7_0);

// Asynchronous.  Remove a finished (i.e. failed or completed) transaction from the queue.  Attempting to finish a purchasing transaction will throw an exception.
- (void)finishTransaction:(SKPaymentTransaction *)transaction NS_AVAILABLE(10_7, 3_0);

// Asynchronous.  Start the given downloads (SKDownload).
- (void)startDownloads:(NSArray<SKDownload *> *)downloads NS_AVAILABLE(10_8, 6_0);

// Asynchronous.  Pause/resume downloads (SKDownload).
- (void)pauseDownloads:(NSArray<SKDownload *> *)downloads NS_AVAILABLE(10_8, 6_0);
- (void)resumeDownloads:(NSArray<SKDownload *> *)downloads NS_AVAILABLE(10_8, 6_0);

// Asynchronous.  Cancel downloads (SKDownload)
- (void)cancelDownloads:(NSArray<SKDownload *> *)downloads NS_AVAILABLE(10_8, 6_0);

// Observers are not retained.  The transactions array will only be synchronized with the server while the queue has observers.  This may require that the user authenticate.
- (void)addTransactionObserver:(id <SKPaymentTransactionObserver>)observer NS_AVAILABLE(10_7, 3_0);
- (void)removeTransactionObserver:(id <SKPaymentTransactionObserver>)observer NS_AVAILABLE(10_7, 3_0);

// Array of unfinished SKPaymentTransactions.  Only valid while the queue has observers.  Updated asynchronously.
@property(nonatomic, readonly) NSArray<SKPaymentTransaction *> *transactions NS_AVAILABLE(10_7, 3_0);

@end


@protocol SKPaymentTransactionObserver <NSObject>
@required
// Sent when the transaction array has changed (additions or state changes).  Client should check state of transactions and finish as appropriate.
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray<SKPaymentTransaction *> *)transactions NS_AVAILABLE(10_7, 3_0);

@optional
// Sent when transactions are removed from the queue (via finishTransaction:).
- (void)paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray<SKPaymentTransaction *> *)transactions NS_AVAILABLE(10_7, 3_0);

// Sent when an error is encountered while adding transactions from the user's purchase history back to the queue.
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error NS_AVAILABLE(10_7, 3_0);

// Sent when all transactions from the user's purchase history have successfully been added back to the queue.
- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue NS_AVAILABLE(10_7, 3_0);

// Sent when the download state has changed.
- (void)paymentQueue:(SKPaymentQueue *)queue updatedDownloads:(NSArray<SKDownload *> *)downloads NS_AVAILABLE(10_8, 6_0);

// Sent when a user initiates an IAP buy from the App Store
- (BOOL)paymentQueue:(SKPaymentQueue *)queue shouldAddStorePayment:(SKPayment *)payment forProduct:(SKProduct *)product NS_SWIFT_NAME(paymentQueue(_:shouldAddStorePayment:for:)) NS_AVAILABLE_IOS(11_0);

@end

NS_ASSUME_NONNULL_END
// ==========  StoreKit.framework/Headers/StoreKitDefines.h
//
//  StoreKitDefines.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#ifdef __cplusplus
#define SK_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define SK_EXTERN   extern __attribute__((visibility ("default")))
#endif

#define	SK_EXTERN_CLASS	__attribute__((visibility("default")))
#define SK_EXTERN_CLASS_AVAILABLE(_mac, _ios) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(_mac, _ios)
#define SK_EXTERN_CLASS_AVAILABLE_MAC(version) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE_MAC(version)
#define SK_EXTERN_CLASS_AVAILABLE_IOS(version) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE_IOS(version)
// ==========  StoreKit.framework/Headers/SKReceiptRefreshRequest.h
//
//  SKReceiptRefreshRequest.h
//  StoreKit
//
//  Copyright (c) 2013 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/SKRequest.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS_AVAILABLE(10_9, 7_0) @interface SKReceiptRefreshRequest : SKRequest {
@private
    NSDictionary *_properties;
}

- (instancetype)initWithReceiptProperties:(nullable NSDictionary<NSString *, id> *)properties NS_AVAILABLE(10_9, 7_0);
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *receiptProperties NS_AVAILABLE(10_9, 7_0);

@end

SK_EXTERN void SKTerminateForInvalidReceipt(void) NS_AVAILABLE(10_14, 7_1);

// Receipt properties for sandbox testing:
SK_EXTERN NSString * const SKReceiptPropertyIsExpired NS_AVAILABLE(10_9, 7_0);  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsRevoked NS_AVAILABLE(10_9, 7_0);  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsVolumePurchase NS_AVAILABLE(10_9, 7_0);  // NSNumber BOOL, defaults to NO

NS_ASSUME_NONNULL_END
// ==========  StoreKit.framework/Headers/SKCloudServiceController.h
//
//  SKCloudServiceController.h
//  StoreKit
//
//  Copyright © 2015-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SKCloudServiceAuthorizationStatus) {
    SKCloudServiceAuthorizationStatusNotDetermined,
    SKCloudServiceAuthorizationStatusDenied,
    SKCloudServiceAuthorizationStatusRestricted,
    SKCloudServiceAuthorizationStatusAuthorized,
} NS_ENUM_AVAILABLE_IOS(9_3);

typedef NS_OPTIONS(NSUInteger, SKCloudServiceCapability) {
    SKCloudServiceCapabilityNone                           = 0,
    SKCloudServiceCapabilityMusicCatalogPlayback           = 1 << 0,
    SKCloudServiceCapabilityMusicCatalogSubscriptionEligible    NS_ENUM_AVAILABLE_IOS(10_1)  = 1 << 1,
    SKCloudServiceCapabilityAddToCloudMusicLibrary         = 1 << 8,
} NS_AVAILABLE_IOS(9_3);

SK_EXTERN_CLASS_AVAILABLE_IOS(9_3) @interface SKCloudServiceController : NSObject

+ (SKCloudServiceAuthorizationStatus)authorizationStatus;
+ (void)requestAuthorization:(void(^)(SKCloudServiceAuthorizationStatus status))handler;

- (void)requestCapabilitiesWithCompletionHandler:(void(^)(SKCloudServiceCapability capabilities, NSError * _Nullable error))completionHandler;

- (void)requestStorefrontCountryCodeWithCompletionHandler:(void(^)(NSString * _Nullable storefrontCountryCode, NSError * _Nullable error))completionHandler NS_AVAILABLE_IOS(11_0);
- (void)requestStorefrontIdentifierWithCompletionHandler:(void(^)(NSString * _Nullable storefrontIdentifier, NSError * _Nullable error))completionHandler;

- (void)requestUserTokenForDeveloperToken:(NSString *)developerToken completionHandler:(void(^)(NSString * _Nullable userToken, NSError * _Nullable error))completionHandler NS_AVAILABLE_IOS(11_0);
- (void)requestPersonalizationTokenForClientToken:(NSString *)clientToken withCompletionHandler:(void(^)(NSString * _Nullable personalizationToken, NSError * _Nullable error))completionHandler API_DEPRECATED_WITH_REPLACEMENT("requestUserTokenForDeveloperToken:completionHandler:", ios(10.3, 11.0));

@end

SK_EXTERN NSNotificationName const SKCloudServiceCapabilitiesDidChangeNotification NS_AVAILABLE_IOS(9_3);
SK_EXTERN NSNotificationName const SKStorefrontCountryCodeDidChangeNotification NS_AVAILABLE_IOS(11_0);
SK_EXTERN NSNotificationName const SKStorefrontIdentifierDidChangeNotification NS_AVAILABLE_IOS(9_3);

NS_ASSUME_NONNULL_END
// ==========  StoreKit.framework/Headers/SKProduct.h
//
//  SKProduct.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKProductDiscount;

typedef NS_ENUM(NSUInteger, SKProductPeriodUnit) {
    SKProductPeriodUnitDay,
    SKProductPeriodUnitWeek,
    SKProductPeriodUnitMonth,
    SKProductPeriodUnitYear
} NS_SWIFT_NAME(SKProduct.PeriodUnit) NS_AVAILABLE(10_13_2, 11_2);

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS_AVAILABLE(10_13_2, 11_2) @interface SKProductSubscriptionPeriod : NSObject {
@private
    id _internal;
}

@property(nonatomic, readonly) NSUInteger numberOfUnits;

@property(nonatomic, readonly) SKProductPeriodUnit unit;

@end

SK_EXTERN_CLASS_AVAILABLE(10_7, 3_0) @interface SKProduct : NSObject {
@private
    id _internal;
}

@property(nonatomic, readonly) NSString *localizedDescription NS_AVAILABLE(10_7, 3_0);

@property(nonatomic, readonly) NSString *localizedTitle NS_AVAILABLE(10_7, 3_0);

@property(nonatomic, readonly) NSDecimalNumber *price NS_AVAILABLE(10_7, 3_0);

@property(nonatomic, readonly) NSLocale *priceLocale NS_AVAILABLE(10_7, 3_0);

@property(nonatomic, readonly) NSString *productIdentifier NS_AVAILABLE(10_7, 3_0);

// YES if this product has content downloadable using SKDownload
#if TARGET_OS_OSX
@property(nonatomic, readonly) BOOL downloadable NS_AVAILABLE_MAC(10_8);
#else
@property(nonatomic, readonly, getter=isDownloadable) BOOL downloadable NS_AVAILABLE_IOS(6_0);
#endif

// Sizes in bytes (NSNumber [long long]) of the downloads available for this product
@property(nonatomic, readonly) NSArray<NSNumber *> *contentLengths NS_DEPRECATED_MAC(10_8, 10_14, "Use [SKProduct downloadContentLengths] instead");
@property(nonatomic, readonly) NSArray<NSNumber *> *downloadContentLengths NS_AVAILABLE(10_14, 6_0);

// Version of the downloadable content
@property(nonatomic, readonly) NSString *contentVersion NS_DEPRECATED_MAC(10_8, 10_14, "Use [SKProduct downloadContentVersion] instead");
@property(nonatomic, readonly) NSString *downloadContentVersion NS_AVAILABLE(10_14, 6_0);

@property(nonatomic, readonly, nullable) SKProductSubscriptionPeriod *subscriptionPeriod NS_AVAILABLE(10_13_2, 11_2);

@property(nonatomic, readonly, nullable) SKProductDiscount *introductoryPrice NS_AVAILABLE(10_13_2, 11_2);

@property(nonatomic, readonly, nullable) NSString *subscriptionGroupIdentifier NS_AVAILABLE(10_14, 12_0);

@end

NS_ASSUME_NONNULL_END
// ==========  StoreKit.framework/Headers/SKStoreProductViewController.h
//
//  SKStoreProductViewController.h
//  StoreKit
//
//  Copyright (c) 2012 Apple, Inc. All rights reserved.
//

#import <StoreKit/StoreKitDefines.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol SKStoreProductViewControllerDelegate;

/* View controller to display iTunes Store product information */
SK_EXTERN_CLASS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED @interface SKStoreProductViewController : UIViewController

// Delegate for product page events
@property(nonatomic, weak, nullable) id <SKStoreProductViewControllerDelegate> delegate NS_AVAILABLE_IOS(6_0);

// Load product view for the product with the given parameters.  See below for parameters (SKStoreProductParameter*).
// Block is invoked when the load finishes.
- (void)loadProductWithParameters:(NSDictionary<NSString *, id> *)parameters completionBlock:(nullable void(^)(BOOL result, NSError * __nullable error))block NS_AVAILABLE_IOS(6_0);

@end


@protocol SKStoreProductViewControllerDelegate <NSObject>

@optional

// Sent if the user requests that the page be dismissed
- (void)productViewControllerDidFinish:(SKStoreProductViewController *)viewController __TVOS_PROHIBITED NS_AVAILABLE_IOS(6_0);

@end


// iTunes Store item identifier (NSNumber) of the product
SK_EXTERN NSString * const SKStoreProductParameterITunesItemIdentifier NS_AVAILABLE_IOS(6_0);

// SKU for the In-App Purchase product (NSString) to render at the top of the product page
SK_EXTERN NSString * const SKStoreProductParameterProductIdentifier NS_AVAILABLE_IOS(11_0);

// iTunes Store affiliate token (NSString)
SK_EXTERN NSString * const SKStoreProductParameterAffiliateToken NS_AVAILABLE_IOS(8_0);

// iTunes Store affiliate campaign token (NSString)
SK_EXTERN NSString * const SKStoreProductParameterCampaignToken NS_AVAILABLE_IOS(8_0);

// Analytics provider token (NSString)
SK_EXTERN NSString * const SKStoreProductParameterProviderToken NS_AVAILABLE_IOS(8_3);

// Advertising partner token (NSString)
SK_EXTERN NSString * const SKStoreProductParameterAdvertisingPartnerToken NS_AVAILABLE_IOS(9_3);

NS_ASSUME_NONNULL_END
// ==========  StoreKit.framework/Headers/SKProductStorePromotionController.h
//
//  SKProductStorePromotionController.h
//  StoreKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class SKProduct;

typedef NS_ENUM(NSInteger, SKProductStorePromotionVisibility) {
    SKProductStorePromotionVisibilityDefault,
    SKProductStorePromotionVisibilityShow,
    SKProductStorePromotionVisibilityHide,
} NS_ENUM_AVAILABLE_IOS(11_0);

SK_EXTERN_CLASS_AVAILABLE_IOS(11_0) @interface SKProductStorePromotionController : NSObject

+ (instancetype)defaultController NS_AVAILABLE_IOS(11_0);

- (void)fetchStorePromotionVisibilityForProduct:(SKProduct *)product completionHandler:(nullable void (^)(SKProductStorePromotionVisibility storePromotionVisibility, NSError * _Nullable error))completionHandler NS_AVAILABLE_IOS(11_0);
- (void)updateStorePromotionVisibility:(SKProductStorePromotionVisibility)promotionVisibility forProduct:(SKProduct *)product completionHandler:(nullable void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_NAME(update(storePromotionVisibility:for:completionHandler:)) NS_AVAILABLE_IOS(11_0);

- (void)fetchStorePromotionOrderWithCompletionHandler:(nullable void (^)(NSArray<SKProduct *> *storePromotionOrder, NSError * _Nullable error))completionHandler NS_AVAILABLE_IOS(11_0);
- (void)updateStorePromotionOrder:(NSArray<SKProduct *> *)storePromotionOrder completionHandler:(nullable void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_NAME(update(storePromotionOrder:completionHandler:)) NS_AVAILABLE_IOS(11_0);

@end

NS_ASSUME_NONNULL_END
// ==========  StoreKit.framework/Headers/StoreKit.h
//
//  StoreKit.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <StoreKit/SKAdNetwork.h>
#import <StoreKit/SKCloudServiceController.h>
#import <StoreKit/SKCloudServiceSetupViewController.h>
#import <StoreKit/SKDownload.h>
#import <StoreKit/SKError.h>
#import <StoreKit/SKPayment.h>
#import <StoreKit/SKPaymentQueue.h>
#import <StoreKit/SKPaymentTransaction.h>
#import <StoreKit/SKProduct.h>
#import <StoreKit/SKProductDiscount.h>
#import <StoreKit/SKProductsRequest.h>
#import <StoreKit/SKProductStorePromotionController.h>
#import <StoreKit/SKReceiptRefreshRequest.h>
#import <StoreKit/SKRequest.h>
#import <StoreKit/SKStoreProductViewController.h>
#import <StoreKit/SKStoreReviewController.h>
#import <StoreKit/StoreKitDefines.h>
// ==========  StoreKit.framework/Headers/SKStoreReviewController.h
//
//  SKStoreReviewController.h
//  StoreKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/** Controller class to request a review from the current user */
SK_EXTERN_CLASS_AVAILABLE(10_14, 10_3) __TVOS_UNAVAILABLE @interface SKStoreReviewController : NSObject

/** Request StoreKit to ask the user for an app review. This may or may not show any UI.
 *
 *  Given this may not succussfully present an alert to the user, it is not appropriate for use
 *  from a button or any other user action. For presenting a write review form, a deep link is 
 *  available to the App Store by appending the query params "action=write-review" to a product URL.
 */
+ (void)requestReview;

@end

NS_ASSUME_NONNULL_END
// ==========  StoreKit.framework/Headers/SKPayment.h
//
//  SKPayment.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKProduct;

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS_AVAILABLE(10_7, 3_0) @interface SKPayment : NSObject <NSCopying, NSMutableCopying> {
@private
    id _internal;
}

+ (instancetype)paymentWithProduct:(SKProduct *)product NS_AVAILABLE(10_7, 3_0);

+ (id)paymentWithProductIdentifier:(NSString *)identifier NS_DEPRECATED_IOS(3_0, 5_0, "Use +paymentWithProduct: after fetching the available products using SKProductsRequest");

// Identifier agreed upon with the store.  Required.
@property(nonatomic, copy, readonly) NSString *productIdentifier NS_AVAILABLE(10_7, 3_0);

// Payment request data agreed upon with the store.  Optional.
@property(nonatomic, copy, readonly, nullable) NSData *requestData NS_AVAILABLE(10_7, 3_0);

// default: 1.  Must be at least 1.
@property(nonatomic, readonly) NSInteger quantity NS_AVAILABLE(10_7, 3_0);

// Application-specific user identifier.  Optional.
@property(nonatomic, copy, readonly, nullable) NSString *applicationUsername NS_AVAILABLE(10_9, 7_0);

// Force an "ask to buy" flow for this payment, in the sandbox
@property(nonatomic, readonly) BOOL simulatesAskToBuyInSandbox NS_AVAILABLE(10_14, 8_3);

@end


SK_EXTERN_CLASS_AVAILABLE(10_7, 3_0) @interface SKMutablePayment : SKPayment

@property(nonatomic, copy, readwrite, nullable) NSString *applicationUsername NS_AVAILABLE(10_9, 7_0);
@property(nonatomic, copy, readwrite) NSString *productIdentifier NS_AVAILABLE(10_7, 3_0);
@property(nonatomic, readwrite) NSInteger quantity NS_AVAILABLE(10_7, 3_0);
@property(nonatomic, copy, readwrite, nullable) NSData *requestData NS_AVAILABLE(10_7, 3_0);
@property(nonatomic, readwrite) BOOL simulatesAskToBuyInSandbox NS_AVAILABLE(10_14, 8_3);

@end

NS_ASSUME_NONNULL_END
// ==========  StoreKit.framework/Headers/SKProductDiscount.h
//
//  SKProductDiscount.h
//  StoreKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKProductSubscriptionPeriod;

typedef NS_ENUM(NSUInteger, SKProductDiscountPaymentMode) {
    SKProductDiscountPaymentModePayAsYouGo,
    SKProductDiscountPaymentModePayUpFront,
    SKProductDiscountPaymentModeFreeTrial
} NS_SWIFT_NAME(SKProductDiscount.PaymentMode) NS_AVAILABLE(10_13_2, 11_2);

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS_AVAILABLE(10_13_2, 11_2) @interface SKProductDiscount : NSObject {
@private
    id _internal;
}

@property(nonatomic, readonly) NSDecimalNumber *price NS_AVAILABLE(10_13_2, 11_2);

@property(nonatomic, readonly) NSLocale *priceLocale NS_AVAILABLE(10_13_2, 11_2);

@property(nonatomic, readonly) SKProductSubscriptionPeriod *subscriptionPeriod NS_AVAILABLE(10_13_2, 11_2);

@property(nonatomic, readonly) NSUInteger numberOfPeriods NS_AVAILABLE(10_13_2, 11_2);

@property(nonatomic, readonly) SKProductDiscountPaymentMode paymentMode NS_AVAILABLE(10_13_2, 11_2);

@end

NS_ASSUME_NONNULL_END
// ==========  StoreKit.framework/Headers/SKRequest.h
//
//  SKRequest.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@protocol SKRequestDelegate;

// Base class used to fetch data from the store.  Should not be used directly.
SK_EXTERN_CLASS_AVAILABLE(10_7, 3_0) @interface SKRequest : NSObject {
@private
    id _requestInternal;
}

@property(nonatomic, weak, nullable) id <SKRequestDelegate> delegate NS_AVAILABLE(10_7, 3_0);

// Cancel the request if it has started.
- (void)cancel NS_AVAILABLE(10_7, 3_0);

// Start the request if it has not already been started.
- (void)start NS_AVAILABLE(10_7, 3_0);

@end


@protocol SKRequestDelegate <NSObject>

@optional
- (void)requestDidFinish:(SKRequest *)request NS_AVAILABLE(10_7, 3_0);
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error NS_AVAILABLE(10_7, 3_0);

@end

NS_ASSUME_NONNULL_END
// ==========  StoreKit.framework/Headers/SKCloudServiceSetupViewController.h
//
//  SKCloudServiceSetupViewController.h
//  StoreKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <StoreKit/StoreKitDefines.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * SKCloudServiceSetupOptionsKey NS_STRING_ENUM;
typedef NSString * SKCloudServiceSetupAction NS_STRING_ENUM;
typedef NSString * SKCloudServiceSetupMessageIdentifier NS_STRING_ENUM;

@protocol SKCloudServiceSetupViewControllerDelegate;

/// View controller to allow user to setup iTunes Store account for cloud service, such as Apple Music subscription.
SK_EXTERN_CLASS_AVAILABLE_IOS(10_1) __TVOS_PROHIBITED @interface SKCloudServiceSetupViewController : UIViewController

/// Optional delegate.
@property (nonatomic, nullable, weak) id <SKCloudServiceSetupViewControllerDelegate> delegate;

/// Load cloud service setup view with the given options.
/// Block is invoked on the main thread when the load finishes.
- (void)loadWithOptions:(NSDictionary<SKCloudServiceSetupOptionsKey, id> *)options completionHandler:(nullable void (^)(BOOL result, NSError * _Nullable error))completionHandler;

@end


@protocol SKCloudServiceSetupViewControllerDelegate <NSObject>

@optional

/// Sent when the view controller was dismissed.
- (void)cloudServiceSetupViewControllerDidDismiss:(SKCloudServiceSetupViewController *)cloudServiceSetupViewController __TVOS_PROHIBITED NS_AVAILABLE_IOS(10_1);

@end


/// Action for setup entry point (of type SKCloudServiceSetupAction).
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsActionKey NS_SWIFT_NAME(action) NS_AVAILABLE_IOS(10_1);

/// Identifier of the iTunes Store item the user is trying to access which requires cloud service setup (NSNumber).
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsITunesItemIdentifierKey NS_SWIFT_NAME(iTunesItemIdentifier) NS_AVAILABLE_IOS(10_1);

/// iTunes Store affiliate token (NSString).
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsAffiliateTokenKey NS_SWIFT_NAME(affiliateToken) NS_AVAILABLE_IOS(10_3);

/// iTunes Store affiliate campaign token (NSString).
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsCampaignTokenKey NS_SWIFT_NAME(campaignToken) NS_AVAILABLE_IOS(10_3);

/// Identifier used to select the main message presented to the user for this setup view (SKCloudServiceSetupMessageIdentifier).
/// When missing, the setup view will be configured in a way that is equivalent to using SKCloudServiceSetupMessageIdentifierJoin.
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsMessageIdentifierKey NS_SWIFT_NAME(messageIdentifier) NS_AVAILABLE_IOS(11_0);

// Supported actions for setup entry point.

SK_EXTERN SKCloudServiceSetupAction const SKCloudServiceSetupActionSubscribe NS_AVAILABLE_IOS(10_1);

// Supported message identifiers.

SK_EXTERN SKCloudServiceSetupMessageIdentifier const SKCloudServiceSetupMessageIdentifierJoin NS_AVAILABLE_IOS(11_0);
SK_EXTERN SKCloudServiceSetupMessageIdentifier const SKCloudServiceSetupMessageIdentifierConnect NS_AVAILABLE_IOS(11_0);
SK_EXTERN SKCloudServiceSetupMessageIdentifier const SKCloudServiceSetupMessageIdentifierAddMusic NS_AVAILABLE_IOS(11_0);
SK_EXTERN SKCloudServiceSetupMessageIdentifier const SKCloudServiceSetupMessageIdentifierPlayMusic NS_AVAILABLE_IOS(11_0);

NS_ASSUME_NONNULL_END
// ==========  StoreKit.framework/Headers/SKDownload.h
//
//  SKDownload.h
//  StoreKit
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class SKPaymentTransaction;

typedef NS_ENUM(NSInteger, SKDownloadState) {
    SKDownloadStateWaiting,     // Download is inactive, waiting to be downloaded
    SKDownloadStateActive,      // Download is actively downloading
    SKDownloadStatePaused,      // Download was paused by the user
    SKDownloadStateFinished,    // Download is finished, content is available
    SKDownloadStateFailed,      // Download failed
    SKDownloadStateCancelled,   // Download was cancelled
} NS_AVAILABLE(10_8, 6_0);

SK_EXTERN NSTimeInterval SKDownloadTimeRemainingUnknown NS_AVAILABLE(10_14, 6_0);

SK_EXTERN_CLASS_AVAILABLE(10_8, 6_0) @interface SKDownload : NSObject {
@private
    id _internal;
}

// State of the download
@property(nonatomic, readonly) SKDownloadState state NS_AVAILABLE(10_8, 12_0);
@property(nonatomic, readonly) SKDownloadState downloadState NS_DEPRECATED_IOS(6_0, 12_0, "Use [SKDownload state] instead");

// Total size of the content, in bytes
#if TARGET_OS_OSX
@property(nonatomic, copy, readonly) NSNumber *contentLength NS_AVAILABLE_MAC(10_8);
#else
@property(nonatomic, readonly) long long contentLength NS_AVAILABLE_IOS(6_0);
#endif

// Identifier for this content
@property(nonatomic, readonly) NSString *contentIdentifier NS_AVAILABLE(10_8, 6_0);

// Location of the content data, if state is SKDownloadStateFinished
@property(nonatomic, readonly, nullable) NSURL *contentURL NS_AVAILABLE(10_8, 6_0);

// Content version
@property(nonatomic, readonly) NSString *contentVersion NS_AVAILABLE(10_8, 6_0);

// Failure error, if state is SKDownloadStateFailed
@property(nonatomic, readonly, nullable) NSError *error NS_AVAILABLE(10_8, 6_0);

// Overall progress for the download [0..1]
@property(nonatomic, readonly) float progress NS_AVAILABLE(10_8, 6_0);

// Estimated time remaining to complete the download, in seconds.  Value is SKDownloadTimeRemainingUnknown if estimate is unknownxx.
@property(nonatomic, readonly) NSTimeInterval timeRemaining NS_AVAILABLE(10_8, 6_0);

// Transaction for this download
@property(nonatomic, readonly) SKPaymentTransaction *transaction NS_AVAILABLE(10_11, 6_0);


+ (nullable NSURL *)contentURLForProductID:(NSString *)productID NS_AVAILABLE_MAC(10_8);

// Deletes the content for that identifier from disk
+ (void)deleteContentForProductID:(NSString *)productID NS_AVAILABLE_MAC(10_8);
@end

NS_ASSUME_NONNULL_END
// ==========  StoreKit.framework/Headers/SKProductsRequest.h
//
//  SKProductsRequest.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <StoreKit/SKRequest.h>

@class SKProduct, SKProductsRequest, SKProductsResponse;

NS_ASSUME_NONNULL_BEGIN

@protocol SKProductsRequestDelegate <SKRequestDelegate>

@required
// Sent immediately before -requestDidFinish:
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response NS_AVAILABLE(10_7, 3_0);

@end


// request information about products for your application
SK_EXTERN_CLASS_AVAILABLE(10_7, 3_0) @interface SKProductsRequest : SKRequest {
@private
    id _productsRequestInternal;
}

// Set of string product identifiers
- (instancetype)initWithProductIdentifiers:(NSSet<NSString *> *)productIdentifiers NS_AVAILABLE(10_7, 3_0);

@property(nonatomic, weak, nullable) id <SKProductsRequestDelegate> delegate NS_AVAILABLE(10_7, 3_0);

@end


SK_EXTERN_CLASS_AVAILABLE(10_7, 3_0) @interface SKProductsResponse : NSObject {
@private
    id _internal;
}

// Array of SKProduct instances.
@property(nonatomic, readonly) NSArray<SKProduct *> *products NS_AVAILABLE(10_7, 3_0);

// Array of invalid product identifiers.
@property(nonatomic, readonly) NSArray<NSString *> *invalidProductIdentifiers NS_AVAILABLE(10_7, 3_0);

@end

NS_ASSUME_NONNULL_END
// ==========  StoreKit.framework/Headers/SKAdNetwork.h
//
//  SKAdNetwork.h
//  StoreKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS_AVAILABLE_IOS(11_3) __TVOS_PROHIBITED @interface SKAdNetwork : NSObject

// Participating apps should call this on launch to complete the install+open action associated with a product view
+ (void)registerAppForAdNetworkAttribution NS_AVAILABLE_IOS(11_3);

@end

// Constants for use with SKStoreProductViewController to associate a product view with an install+open

// Advertising network's cryptographic signature for the atribution params (NSString)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkAttributionSignature NS_AVAILABLE_IOS(11_3);

// Advertising network campaign identifier (NSNumber)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkCampaignIdentifier NS_AVAILABLE_IOS(11_3);

// Advertising network identifier (NSString)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkIdentifier NS_AVAILABLE_IOS(11_3);

// Random entropy value for security (NSUUID)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkNonce NS_AVAILABLE_IOS(11_3);

// Timestamp for this ad impression (NSNumber)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkTimestamp NS_AVAILABLE_IOS(11_3);

NS_ASSUME_NONNULL_END
// ==========  StoreKit.framework/Headers/SKError.h
//
//  SKError.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN NSString * const SKErrorDomain NS_AVAILABLE(10_7, 3_0);

// error codes for the SKErrorDomain
typedef NS_ENUM(NSInteger,SKErrorCode) {
    SKErrorUnknown,
    SKErrorClientInvalid,                                                     // client is not allowed to issue the request, etc.
    SKErrorPaymentCancelled,                                                  // user cancelled the request, etc.
    SKErrorPaymentInvalid,                                                    // purchase identifier was invalid, etc.
    SKErrorPaymentNotAllowed,                                                 // this device is not allowed to make the payment
    SKErrorStoreProductNotAvailable NS_ENUM_AVAILABLE(NA, 3_0),               // Product is not available in the current storefront
    SKErrorCloudServicePermissionDenied NS_ENUM_AVAILABLE(NA, 9_3),           // user has not allowed access to cloud service information
    SKErrorCloudServiceNetworkConnectionFailed NS_ENUM_AVAILABLE(NA, 9_3),    // the device could not connect to the nework
    SKErrorCloudServiceRevoked NS_ENUM_AVAILABLE(NA, 10_3),                   // user has revoked permission to use this cloud service
};

NS_ASSUME_NONNULL_END
// ==========  StoreKit.framework/Headers/SKPaymentTransaction.h
//
//  SKPaymentTransaction.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKDownload;
@class SKPayment;

typedef NS_ENUM(NSInteger, SKPaymentTransactionState) {
    SKPaymentTransactionStatePurchasing,    // Transaction is being added to the server queue.
    SKPaymentTransactionStatePurchased,     // Transaction is in queue, user has been charged.  Client should complete the transaction.
    SKPaymentTransactionStateFailed,        // Transaction was cancelled or failed before being added to the server queue.
    SKPaymentTransactionStateRestored,      // Transaction was restored from user's purchase history.  Client should complete the transaction.
    SKPaymentTransactionStateDeferred NS_ENUM_AVAILABLE(10_10, 8_0),   // The transaction is in the queue, but its final status is pending external action.
} NS_AVAILABLE(10_7, 3_0);

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS_AVAILABLE(10_7, 3_0) @interface SKPaymentTransaction : NSObject {
@private
    id _internal;
}

// Only set if state is SKPaymentTransactionFailed
@property(nonatomic, readonly, nullable) NSError *error NS_AVAILABLE(10_7, 3_0);

// Only valid if state is SKPaymentTransactionStateRestored.
@property(nonatomic, readonly, nullable) SKPaymentTransaction *originalTransaction NS_AVAILABLE(10_7, 3_0);

@property(nonatomic, readonly) SKPayment *payment NS_AVAILABLE(10_7, 3_0);

// Available downloads (SKDownload) for this transaction
@property(nonatomic, readonly) NSArray<SKDownload *> *downloads NS_AVAILABLE(10_8, 6_0);

// The date when the transaction was added to the server queue.  Only valid if state is SKPaymentTransactionStatePurchased or SKPaymentTransactionStateRestored.
@property(nonatomic, readonly, nullable) NSDate *transactionDate NS_AVAILABLE(10_7, 3_0);

// The unique server-provided identifier.  Only valid if state is SKPaymentTransactionStatePurchased or SKPaymentTransactionStateRestored.
@property(nonatomic, readonly, nullable) NSString *transactionIdentifier NS_AVAILABLE(10_7, 3_0);

// Only valid if state is SKPaymentTransactionStatePurchased.
@property(nonatomic, readonly, nullable) NSData *transactionReceipt NS_DEPRECATED_IOS(3_0, 7_0, "Use -[NSBundle appStoreReceiptURL]");

@property(nonatomic, readonly) SKPaymentTransactionState transactionState NS_AVAILABLE(10_7, 3_0);

@end

NS_ASSUME_NONNULL_END
