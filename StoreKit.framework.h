// ==========  StoreKit.framework/Headers/SKStorefront.h
//
//  SKStorefront.h
//  StoreKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS API_AVAILABLE(ios(13.0), macos(10.15)) @interface SKStorefront : NSObject

/* The three letter country code for the current storefront */
@property(NS_NONATOMIC_IOSONLY, copy, readonly) NSString *countryCode API_AVAILABLE(ios(13.0), macos(10.15));

/* The App Store storefront identifier */
@property(NS_NONATOMIC_IOSONLY, copy, readonly) NSString *identifier API_AVAILABLE(ios(13.0), macos(10.15));

@end

NS_ASSUME_NONNULL_END
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
@class SKStorefront;
@protocol SKPaymentQueueDelegate;
@protocol SKPaymentTransactionObserver;

NS_ASSUME_NONNULL_BEGIN

// SKPaymentQueue interacts with the server-side payment queue
SK_EXTERN_CLASS API_AVAILABLE(ios(3.0), macos(10.7)) @interface SKPaymentQueue : NSObject {
@private
    id _internal;
}

@property (NS_NONATOMIC_IOSONLY, weak, nullable) id<SKPaymentQueueDelegate> delegate API_AVAILABLE(ios(13.0), macos(10.15));;

@property (NS_NONATOMIC_IOSONLY, readonly, nullable) SKStorefront *storefront API_AVAILABLE(ios(13.0), macos(10.15));

+ (instancetype)defaultQueue API_AVAILABLE(ios(3.0), macos(10.7));

// NO if this device is not able or allowed to make payments
+ (BOOL)canMakePayments API_AVAILABLE(ios(3.0), macos(10.7));

// Asynchronous.  Add a payment to the server queue.  The payment is copied to add an SKPaymentTransaction to the transactions array.  The same payment can be added multiple times to create multiple transactions.
- (void)addPayment:(SKPayment *)payment API_AVAILABLE(ios(3.0), macos(10.7));

// Asynchronous.  Will add completed transactions for the current user back to the queue to be re-completed.  User will be asked to authenticate.  Observers will receive 0 or more -paymentQueue:updatedTransactions:, followed by either -paymentQueueRestoreCompletedTransactionsFinished: on success or -paymentQueue:restoreCompletedTransactionsFailedWithError: on failure.  In the case of partial success, some transactions may still be delivered.
- (void)restoreCompletedTransactions API_AVAILABLE(ios(3.0), macos(10.7));
- (void)restoreCompletedTransactionsWithApplicationUsername:(nullable NSString *)username API_AVAILABLE(ios(7.0), macos(10.9));

// Asynchronous.  Remove a finished (i.e. failed or completed) transaction from the queue.  Attempting to finish a purchasing transaction will throw an exception.
- (void)finishTransaction:(SKPaymentTransaction *)transaction API_AVAILABLE(ios(3.0), macos(10.7));

// Asynchronous.  Start the given downloads (SKDownload).
- (void)startDownloads:(NSArray<SKDownload *> *)downloads API_AVAILABLE(ios(6.0), macos(10.8));

// Asynchronous.  Pause/resume downloads (SKDownload).
- (void)pauseDownloads:(NSArray<SKDownload *> *)downloads API_AVAILABLE(ios(6.0), macos(10.8));
- (void)resumeDownloads:(NSArray<SKDownload *> *)downloads API_AVAILABLE(ios(6.0), macos(10.8));

// Asynchronous.  Cancel downloads (SKDownload)
- (void)cancelDownloads:(NSArray<SKDownload *> *)downloads API_AVAILABLE(ios(6.0), macos(10.8));

// Observers are not retained.  The transactions array will only be synchronized with the server while the queue has observers.  This may require that the user authenticate.
- (void)addTransactionObserver:(id <SKPaymentTransactionObserver>)observer API_AVAILABLE(ios(3.0), macos(10.7));
- (void)removeTransactionObserver:(id <SKPaymentTransactionObserver>)observer API_AVAILABLE(ios(3.0), macos(10.7));

// Array of unfinished SKPaymentTransactions.  Only valid while the queue has observers.  Updated asynchronously.
@property(nonatomic, readonly) NSArray<SKPaymentTransaction *> *transactions API_AVAILABLE(ios(3.0), macos(10.7));

@end

@protocol SKPaymentQueueDelegate <NSObject>
@optional
- (BOOL)paymentQueue:(SKPaymentQueue *)paymentQueue shouldContinueTransaction:(SKPaymentTransaction *)transaction inStorefront:(SKStorefront *)newStorefront API_AVAILABLE(ios(13.0), macos(10.15));
@end


@protocol SKPaymentTransactionObserver <NSObject>
@required
// Sent when the transaction array has changed (additions or state changes).  Client should check state of transactions and finish as appropriate.
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray<SKPaymentTransaction *> *)transactions API_AVAILABLE(ios(3.0), macos(10.7));

@optional
// Sent when transactions are removed from the queue (via finishTransaction:).
- (void)paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray<SKPaymentTransaction *> *)transactions API_AVAILABLE(ios(3.0), macos(10.7));

// Sent when an error is encountered while adding transactions from the user's purchase history back to the queue.
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error API_AVAILABLE(ios(3.0), macos(10.7));

// Sent when all transactions from the user's purchase history have successfully been added back to the queue.
- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue API_AVAILABLE(ios(3.0), macos(10.7));

// Sent when the download state has changed.
- (void)paymentQueue:(SKPaymentQueue *)queue updatedDownloads:(NSArray<SKDownload *> *)downloads API_AVAILABLE(ios(6.0), macos(10.8));

// Sent when a user initiates an IAP buy from the App Store
- (BOOL)paymentQueue:(SKPaymentQueue *)queue shouldAddStorePayment:(SKPayment *)payment forProduct:(SKProduct *)product NS_SWIFT_NAME(paymentQueue(_:shouldAddStorePayment:for:)) API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

- (void)paymentQueueDidChangeStorefront:(SKPaymentQueue *)queue API_AVAILABLE(ios(13.0), macos(10.15));

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

SK_EXTERN_CLASS API_AVAILABLE(ios(7.0), macos(10.9)) @interface SKReceiptRefreshRequest : SKRequest {
@private
    NSDictionary *_properties;
}

- (instancetype)initWithReceiptProperties:(nullable NSDictionary<NSString *, id> *)properties API_AVAILABLE(ios(7.0), macos(10.9));
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *receiptProperties API_AVAILABLE(ios(7.0), macos(10.9));

@end

SK_EXTERN void SKTerminateForInvalidReceipt(void) API_AVAILABLE(ios(7.1), macos(10.14));

// Receipt properties for sandbox testing:
SK_EXTERN NSString * const SKReceiptPropertyIsExpired API_AVAILABLE(ios(7.0), macos(10.9));  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsRevoked API_AVAILABLE(ios(7.0), macos(10.9));  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsVolumePurchase API_AVAILABLE(ios(7.0), macos(10.9));  // NSNumber BOOL, defaults to NO

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
} API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos);

typedef NS_OPTIONS(NSUInteger, SKCloudServiceCapability) {
    SKCloudServiceCapabilityNone                           = 0,
    SKCloudServiceCapabilityMusicCatalogPlayback           = 1 << 0,
    SKCloudServiceCapabilityMusicCatalogSubscriptionEligible API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos)  = 1 << 1,
    SKCloudServiceCapabilityAddToCloudMusicLibrary         = 1 << 8,
} API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos);

SK_EXTERN_CLASS API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos) @interface SKCloudServiceController : NSObject

+ (SKCloudServiceAuthorizationStatus)authorizationStatus API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos);
+ (void)requestAuthorization:(void(^)(SKCloudServiceAuthorizationStatus status))handler API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos);

- (void)requestCapabilitiesWithCompletionHandler:(void(^)(SKCloudServiceCapability capabilities, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos);

- (void)requestStorefrontCountryCodeWithCompletionHandler:(void(^)(NSString * _Nullable storefrontCountryCode, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);
- (void)requestStorefrontIdentifierWithCompletionHandler:(void(^)(NSString * _Nullable storefrontIdentifier, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos);

- (void)requestUserTokenForDeveloperToken:(NSString *)developerToken completionHandler:(void(^)(NSString * _Nullable userToken, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);
- (void)requestPersonalizationTokenForClientToken:(NSString *)clientToken withCompletionHandler:(void(^)(NSString * _Nullable personalizationToken, NSError * _Nullable error))completionHandler API_DEPRECATED_WITH_REPLACEMENT("requestUserTokenForDeveloperToken:completionHandler:", ios(10.3, 11.0)) API_UNAVAILABLE(macos, uikitformac);

@end

SK_EXTERN NSNotificationName const SKCloudServiceCapabilitiesDidChangeNotification API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos);
SK_EXTERN NSNotificationName const SKStorefrontCountryCodeDidChangeNotification API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);
SK_EXTERN NSNotificationName const SKStorefrontIdentifierDidChangeNotification API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos);

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
} NS_SWIFT_NAME(SKProduct.PeriodUnit) API_AVAILABLE(ios(11.2), macos(10.13.2));

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS API_AVAILABLE(ios(11.2), macos(10.13.2)) @interface SKProductSubscriptionPeriod : NSObject {
@private
    id _internal;
}

@property(nonatomic, readonly) NSUInteger numberOfUnits API_AVAILABLE(ios(11.2), macos(10.13.2));

@property(nonatomic, readonly) SKProductPeriodUnit unit API_AVAILABLE(ios(11.2), macos(10.13.2));

@end

SK_EXTERN_CLASS API_AVAILABLE(ios(3.0), macos(10.7)) @interface SKProduct : NSObject {
@private
    id _internal;
}

@property(nonatomic, readonly) NSString *localizedDescription API_AVAILABLE(ios(3.0), macos(10.7));

@property(nonatomic, readonly) NSString *localizedTitle API_AVAILABLE(ios(3.0), macos(10.7));

@property(nonatomic, readonly) NSDecimalNumber *price API_AVAILABLE(ios(3.0), macos(10.7));

@property(nonatomic, readonly) NSLocale *priceLocale API_AVAILABLE(ios(3.0), macos(10.7));

@property(nonatomic, readonly) NSString *productIdentifier API_AVAILABLE(ios(3.0), macos(10.7));

// YES if this product has content downloadable using SKDownload
@property(nonatomic, readonly) BOOL isDownloadable API_AVAILABLE(ios(6.0), macos(10.15));
@property(nonatomic, readonly) BOOL downloadable API_DEPRECATED_WITH_REPLACEMENT("-[SKProduct isDownloadable]", macos(10.8, 10.15)) API_UNAVAILABLE(ios);

// Sizes in bytes (NSNumber [long long]) of the downloads available for this product
@property(nonatomic, readonly) NSArray<NSNumber *> *contentLengths API_DEPRECATED_WITH_REPLACEMENT("-[SKProduct downloadContentLengths]", macos(10.8, 10.14)) API_UNAVAILABLE(ios, tvos);
@property(nonatomic, readonly) NSArray<NSNumber *> *downloadContentLengths API_AVAILABLE(ios(6.0), macos(10.14));

// Version of the downloadable content
@property(nonatomic, readonly) NSString *contentVersion API_DEPRECATED_WITH_REPLACEMENT("-[SKProduct downloadContentVersion]", macos(10.8, 10.14));
@property(nonatomic, readonly) NSString *downloadContentVersion API_AVAILABLE(ios(6.0), macos(10.14));

@property(nonatomic, readonly, nullable) SKProductSubscriptionPeriod *subscriptionPeriod API_AVAILABLE(ios(11.2), macos(10.13.2));

@property(nonatomic, readonly, nullable) SKProductDiscount *introductoryPrice API_AVAILABLE(ios(11.2), macos(10.13.2));

@property(nonatomic, readonly, nullable) NSString *subscriptionGroupIdentifier API_AVAILABLE(ios(12.0), macos(10.14));

@property(nonatomic, readonly) NSArray<SKProductDiscount *> *discounts NS_AVAILABLE(10_14_4, 12_2);

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

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@protocol SKStoreProductViewControllerDelegate;

/* View controller to display iTunes Store product information */
#if TARGET_OS_OSX
SK_EXTERN_CLASS API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED @interface SKStoreProductViewController : NSViewController
#else
SK_EXTERN_CLASS API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED @interface SKStoreProductViewController : UIViewController
#endif

// Delegate for product page events
@property(nonatomic, weak, nullable) id <SKStoreProductViewControllerDelegate> delegate API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED;

// Load product view for the product with the given parameters.  See below for parameters (SKStoreProductParameter*).
// Block is invoked when the load finishes.
- (void)loadProductWithParameters:(NSDictionary<NSString *, id> *)parameters completionBlock:(nullable void(^)(BOOL result, NSError * __nullable error))block API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED;

@end


@protocol SKStoreProductViewControllerDelegate <NSObject>

@optional

// Sent if the user requests that the page be dismissed
- (void)productViewControllerDidFinish:(SKStoreProductViewController *)viewController API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED;

@end


// iTunes Store item identifier (NSNumber) of the product
SK_EXTERN NSString * const SKStoreProductParameterITunesItemIdentifier API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(macos);

// SKU for the In-App Purchase product (NSString) to render at the top of the product page
SK_EXTERN NSString * const SKStoreProductParameterProductIdentifier API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);

// iTunes Store affiliate token (NSString)
SK_EXTERN NSString * const SKStoreProductParameterAffiliateToken API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos);

// iTunes Store affiliate campaign token (NSString)
SK_EXTERN NSString * const SKStoreProductParameterCampaignToken API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos);

// Analytics provider token (NSString)
SK_EXTERN NSString * const SKStoreProductParameterProviderToken API_AVAILABLE(ios(8.3)) API_UNAVAILABLE(macos);

// Advertising partner token (NSString)
SK_EXTERN NSString * const SKStoreProductParameterAdvertisingPartnerToken API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos);
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

typedef NS_CLOSED_ENUM(NSInteger, SKProductStorePromotionVisibility) {
    SKProductStorePromotionVisibilityDefault,
    SKProductStorePromotionVisibilityShow,
    SKProductStorePromotionVisibilityHide,
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

SK_EXTERN_CLASS API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac) @interface SKProductStorePromotionController : NSObject

+ (instancetype)defaultController API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

- (void)fetchStorePromotionVisibilityForProduct:(SKProduct *)product completionHandler:(nullable void (^)(SKProductStorePromotionVisibility storePromotionVisibility, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);
- (void)updateStorePromotionVisibility:(SKProductStorePromotionVisibility)promotionVisibility forProduct:(SKProduct *)product completionHandler:(nullable void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_NAME(update(storePromotionVisibility:for:completionHandler:)) API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

- (void)fetchStorePromotionOrderWithCompletionHandler:(nullable void (^)(NSArray<SKProduct *> *storePromotionOrder, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);
- (void)updateStorePromotionOrder:(NSArray<SKProduct *> *)storePromotionOrder completionHandler:(nullable void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_NAME(update(storePromotionOrder:completionHandler:)) API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, uikitformac);

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
#import <StoreKit/SKPaymentDiscount.h>
#import <StoreKit/SKPaymentQueue.h>
#import <StoreKit/SKPaymentTransaction.h>
#import <StoreKit/SKProduct.h>
#import <StoreKit/SKProductDiscount.h>
#import <StoreKit/SKProductsRequest.h>
#import <StoreKit/SKProductStorePromotionController.h>
#import <StoreKit/SKReceiptRefreshRequest.h>
#import <StoreKit/SKRequest.h>
#import <StoreKit/SKStorefront.h>
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
SK_EXTERN_CLASS API_AVAILABLE(ios(10.3), macos(10.14)) __TVOS_PROHIBITED @interface SKStoreReviewController : NSObject

/** Request StoreKit to ask the user for an app review. This may or may not show any UI.
 *
 *  Given this may not succussfully present an alert to the user, it is not appropriate for use
 *  from a button or any other user action. For presenting a write review form, a deep link is 
 *  available to the App Store by appending the query params "action=write-review" to a product URL.
 */
+ (void)requestReview API_AVAILABLE(ios(10.3), macos(10.14)) __TVOS_PROHIBITED;

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
@class SKPaymentDiscount;

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS API_AVAILABLE(ios(3.0), macos(10.7)) @interface SKPayment : NSObject <NSCopying, NSMutableCopying> {
@private
    id _internal;
}

+ (instancetype)paymentWithProduct:(SKProduct *)product API_AVAILABLE(ios(3.0), macos(10.7));

+ (id)paymentWithProductIdentifier:(NSString *)identifier API_DEPRECATED_WITH_REPLACEMENT("+[SKPayment paymentWithProduct:]", ios(3.0, 5.0)) API_UNAVAILABLE(tvos, macos, uikitformac);

// Identifier agreed upon with the store.  Required.
@property(nonatomic, copy, readonly) NSString *productIdentifier API_AVAILABLE(ios(3.0), macos(10.7));

// Payment request data agreed upon with the store.  Optional.
@property(nonatomic, copy, readonly, nullable) NSData *requestData API_AVAILABLE(ios(3.0), macos(10.7));

// default: 1.  Must be at least 1.
@property(nonatomic, readonly) NSInteger quantity API_AVAILABLE(ios(3.0), macos(10.7));

// Application-specific user identifier.  Optional.
@property(nonatomic, copy, readonly, nullable) NSString *applicationUsername API_AVAILABLE(ios(7.0), macos(10.9));

// Force an "ask to buy" flow for this payment, in the sandbox
@property(nonatomic, readonly) BOOL simulatesAskToBuyInSandbox API_AVAILABLE(ios(8.3), macos(10.14));

// The relevant data for specifying a discount to be applied to this payment. Optional.
@property(nonatomic, copy, readonly, nullable) SKPaymentDiscount *paymentDiscount API_AVAILABLE(ios(12.2), macos(10.14.4));

@end


SK_EXTERN_CLASS API_AVAILABLE(ios(3.0), macos(10.7)) @interface SKMutablePayment : SKPayment

@property(nonatomic, copy, readwrite, nullable) NSString *applicationUsername API_AVAILABLE(ios(7.0), macos(10.9));
@property(nonatomic, copy, readwrite, nullable) SKPaymentDiscount *paymentDiscount API_AVAILABLE(ios(12.2), macos(10.14.4));
@property(nonatomic, copy, readwrite) NSString *productIdentifier API_AVAILABLE(ios(3.0), macos(10.7));
@property(nonatomic, readwrite) NSInteger quantity API_AVAILABLE(ios(3.0), macos(10.7));
@property(nonatomic, copy, readwrite, nullable) NSData *requestData API_AVAILABLE(ios(3.0), macos(10.7));
@property(nonatomic, readwrite) BOOL simulatesAskToBuyInSandbox API_AVAILABLE(ios(8.3), macos(10.14));

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
} NS_SWIFT_NAME(SKProductDiscount.PaymentMode) API_AVAILABLE(ios(11.2), macos(10.13.2));

typedef NS_ENUM(NSUInteger, SKProductDiscountType) {
    SKProductDiscountTypeIntroductory,
    SKProductDiscountTypeSubscription,
} NS_SWIFT_NAME(SKProductDiscount.Type) API_AVAILABLE(ios(12.2), macos(10.14.4));

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS API_AVAILABLE(ios(11.2), macos(10.13.2)) @interface SKProductDiscount : NSObject {
@private
    id _internal;
}

@property(nonatomic, readonly) NSDecimalNumber *price API_AVAILABLE(ios(11.2), macos(10.13.2));

@property(nonatomic, readonly) NSLocale *priceLocale API_AVAILABLE(ios(11.2), macos(10.13.2));

@property(nonatomic, readonly, nullable) NSString *identifier API_AVAILABLE(ios(12.2), macos(10.14.4));

@property(nonatomic, readonly) SKProductSubscriptionPeriod *subscriptionPeriod API_AVAILABLE(ios(11.2), macos(10.13.2));

@property(nonatomic, readonly) NSUInteger numberOfPeriods API_AVAILABLE(ios(11.2), macos(10.13.2));

@property(nonatomic, readonly) SKProductDiscountPaymentMode paymentMode API_AVAILABLE(ios(11.2), macos(10.13.2));

@property(nonatomic, readonly) SKProductDiscountType type API_AVAILABLE(ios(12.2), macos(10.14.4));

@end

NS_ASSUME_NONNULL_END
// ==========  StoreKit.framework/Headers/SKPaymentDiscount.h
//
//  SKPaymentDiscount.h
//  StoreKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS API_AVAILABLE(ios(12.2), macos(10.14.4)) @interface SKPaymentDiscount : NSObject {
@private
    id _internal;
}

- (instancetype)initWithIdentifier:(NSString *)identifier
                     keyIdentifier:(NSString *)keyIdentifier
                             nonce:(NSUUID *)nonce
                         signature:(NSString *)signature
                         timestamp:(NSNumber *)timestamp API_AVAILABLE(ios(12.2), macos(10.14.4));

// Identifier agreed upon with the App Store for a discount of your choosing.
@property(nonatomic, copy, readonly) NSString *identifier API_AVAILABLE(ios(12.2), macos(10.14.4));

// The identifier of the public/private key pair agreed upon with the App Store when the keys were generated.
@property(nonatomic, copy, readonly) NSString *keyIdentifier API_AVAILABLE(ios(12.2), macos(10.14.4));

// One-time use random entropy-adding value for security.
@property(nonatomic, copy, readonly) NSUUID *nonce API_AVAILABLE(ios(12.2), macos(10.14.4));

// The cryptographic signature generated by your private key.
@property(nonatomic, copy, readonly) NSString *signature API_AVAILABLE(ios(12.2), macos(10.14.4));

// Timestamp of when the signature is created.
@property(nonatomic, copy, readonly) NSNumber *timestamp API_AVAILABLE(ios(12.2), macos(10.14.4));

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
SK_EXTERN_CLASS API_AVAILABLE(ios(3.0), macos(10.7)) @interface SKRequest : NSObject {
@private
    id _requestInternal;
}

@property(nonatomic, weak, nullable) id <SKRequestDelegate> delegate API_AVAILABLE(ios(3.0), macos(10.7));

// Cancel the request if it has started.
- (void)cancel API_AVAILABLE(ios(3.0), macos(10.7));

// Start the request if it has not already been started.
- (void)start API_AVAILABLE(ios(3.0), macos(10.7));

@end


@protocol SKRequestDelegate <NSObject>

@optional
- (void)requestDidFinish:(SKRequest *)request API_AVAILABLE(ios(3.0), macos(10.7));
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error API_AVAILABLE(ios(3.0), macos(10.7));

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

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

typedef NSString * SKCloudServiceSetupOptionsKey NS_STRING_ENUM;
typedef NSString * SKCloudServiceSetupAction NS_STRING_ENUM;
typedef NSString * SKCloudServiceSetupMessageIdentifier NS_STRING_ENUM;

@protocol SKCloudServiceSetupViewControllerDelegate;

/// View controller to allow user to setup iTunes Store account for cloud service, such as Apple Music subscription.
#if TARGET_OS_OSX
SK_EXTERN_CLASS API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED @interface SKCloudServiceSetupViewController : NSViewController
#else
SK_EXTERN_CLASS API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED @interface SKCloudServiceSetupViewController : UIViewController
#endif

/// Optional delegate.
@property (nonatomic, nullable, weak) id <SKCloudServiceSetupViewControllerDelegate> delegate API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED;

/// Load cloud service setup view with the given options.
/// Block is invoked on the main thread when the load finishes.
- (void)loadWithOptions:(NSDictionary<SKCloudServiceSetupOptionsKey, id> *)options completionHandler:(nullable void (^)(BOOL result, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED;

@end


@protocol SKCloudServiceSetupViewControllerDelegate <NSObject>

@optional

/// Sent when the view controller was dismissed.
- (void)cloudServiceSetupViewControllerDidDismiss:(SKCloudServiceSetupViewController *)cloudServiceSetupViewController API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED;

@end


/// Action for setup entry point (of type SKCloudServiceSetupAction).
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsActionKey NS_SWIFT_NAME(action) API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos);

/// Identifier of the iTunes Store item the user is trying to access which requires cloud service setup (NSNumber).
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsITunesItemIdentifierKey NS_SWIFT_NAME(iTunesItemIdentifier) API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos);

/// iTunes Store affiliate token (NSString).
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsAffiliateTokenKey NS_SWIFT_NAME(affiliateToken) API_AVAILABLE(ios(10.3)) API_UNAVAILABLE(macos);

/// iTunes Store affiliate campaign token (NSString).
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsCampaignTokenKey NS_SWIFT_NAME(campaignToken) API_AVAILABLE(ios(10.3)) API_UNAVAILABLE(macos);

/// Identifier used to select the main message presented to the user for this setup view (SKCloudServiceSetupMessageIdentifier).
/// When missing, the setup view will be configured in a way that is equivalent to using SKCloudServiceSetupMessageIdentifierJoin.
SK_EXTERN SKCloudServiceSetupOptionsKey const SKCloudServiceSetupOptionsMessageIdentifierKey NS_SWIFT_NAME(messageIdentifier) API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);

// Supported actions for setup entry point.

SK_EXTERN SKCloudServiceSetupAction const SKCloudServiceSetupActionSubscribe API_AVAILABLE(ios(10.1)) API_UNAVAILABLE(macos);

// Supported message identifiers.

SK_EXTERN SKCloudServiceSetupMessageIdentifier const SKCloudServiceSetupMessageIdentifierJoin API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);
SK_EXTERN SKCloudServiceSetupMessageIdentifier const SKCloudServiceSetupMessageIdentifierConnect API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);
SK_EXTERN SKCloudServiceSetupMessageIdentifier const SKCloudServiceSetupMessageIdentifierAddMusic API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);
SK_EXTERN SKCloudServiceSetupMessageIdentifier const SKCloudServiceSetupMessageIdentifierPlayMusic API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos);

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

typedef NS_CLOSED_ENUM(NSInteger, SKDownloadState) {
    SKDownloadStateWaiting,     // Download is inactive, waiting to be downloaded
    SKDownloadStateActive,      // Download is actively downloading
    SKDownloadStatePaused,      // Download was paused by the user
    SKDownloadStateFinished,    // Download is finished, content is available
    SKDownloadStateFailed,      // Download failed
    SKDownloadStateCancelled,   // Download was cancelled
} API_AVAILABLE(ios(6.0), macos(10.8));

SK_EXTERN NSTimeInterval SKDownloadTimeRemainingUnknown API_AVAILABLE(ios(6.0), macos(10.14));

SK_EXTERN_CLASS API_AVAILABLE(ios(6.0), macos(10.8)) @interface SKDownload : NSObject {
@private
    id _internal;
}

// State of the download
@property(nonatomic, readonly) SKDownloadState state API_AVAILABLE(ios(12.0), macos(10.8));
@property(nonatomic, readonly) SKDownloadState downloadState API_DEPRECATED_WITH_REPLACEMENT("-[SKDownload state]", ios(6.0, 12.0)) API_UNAVAILABLE(macos);

// Total size of the content, in bytes
#if TARGET_OS_OSX
@property(nonatomic, copy, readonly) NSNumber *contentLength API_DEPRECATED_WITH_REPLACEMENT("-[SKDownload expectedContentLength]", macos(10.8, 10.15)) API_UNAVAILABLE(ios, tvos);
#else
@property(nonatomic, readonly) long long contentLength API_DEPRECATED_WITH_REPLACEMENT("-[SKDownload expectedContentLength]", ios(6.0, 13.0), tvos(9.0, 13.0)) API_UNAVAILABLE(macos, uikitformac);
#endif

// Total size of the content, in bytes
@property(nonatomic, readonly) long long expectedContentLength API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0));

// Identifier for this content
@property(nonatomic, readonly) NSString *contentIdentifier API_AVAILABLE(ios(6.0), macos(10.8));

// Location of the content data, if state is SKDownloadStateFinished
@property(nonatomic, readonly, nullable) NSURL *contentURL API_AVAILABLE(ios(6.0), macos(10.8));

// Content version
@property(nonatomic, readonly) NSString *contentVersion API_AVAILABLE(ios(6.0), macos(10.8));

// Failure error, if state is SKDownloadStateFailed
@property(nonatomic, readonly, nullable) NSError *error API_AVAILABLE(ios(6.0), macos(10.8));

// Overall progress for the download [0..1]
@property(nonatomic, readonly) float progress API_AVAILABLE(ios(6.0), macos(10.8));

// Estimated time remaining to complete the download, in seconds.  Value is SKDownloadTimeRemainingUnknown if estimate is unknownxx.
@property(nonatomic, readonly) NSTimeInterval timeRemaining API_AVAILABLE(ios(6.0), macos(10.8));

// Transaction for this download
@property(nonatomic, readonly) SKPaymentTransaction *transaction API_AVAILABLE(ios(6.0), macos(10.11));


+ (nullable NSURL *)contentURLForProductID:(NSString *)productID API_AVAILABLE(macos(10.8), uikitformac(13.0)) API_UNAVAILABLE(ios, tvos);

// Deletes the content for that identifier from disk
+ (void)deleteContentForProductID:(NSString *)productID API_AVAILABLE(macos(10.8), uikitformac(13.0)) API_UNAVAILABLE(ios, tvos);
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
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response API_AVAILABLE(ios(3.0), macos(10.7));

@end


// request information about products for your application
SK_EXTERN_CLASS API_AVAILABLE(ios(3.0), macos(10.7)) @interface SKProductsRequest : SKRequest {
@private
    id _productsRequestInternal;
}

// Set of string product identifiers
- (instancetype)initWithProductIdentifiers:(NSSet<NSString *> *)productIdentifiers API_AVAILABLE(ios(3.0), macos(10.7));

@property(nonatomic, weak, nullable) id <SKProductsRequestDelegate> delegate API_AVAILABLE(ios(3.0), macos(10.7)) ;

@end


SK_EXTERN_CLASS API_AVAILABLE(ios(3.0), macos(10.7)) @interface SKProductsResponse : NSObject {
@private
    id _internal;
}

// Array of SKProduct instances.
@property(nonatomic, readonly) NSArray<SKProduct *> *products API_AVAILABLE(ios(3.0), macos(10.7)) ;

// Array of invalid product identifiers.
@property(nonatomic, readonly) NSArray<NSString *> *invalidProductIdentifiers API_AVAILABLE(ios(3.0), macos(10.7)) ;

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

SK_EXTERN_CLASS API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED @interface SKAdNetwork : NSObject

// Participating apps should call this on launch to complete the install+open action associated with a product view
+ (void)registerAppForAdNetworkAttribution API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos) __TVOS_PROHIBITED;

@end

// Constants for use with SKStoreProductViewController to associate a product view with an install+open

// Advertising network's cryptographic signature for the atribution params (NSString)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkAttributionSignature API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos);

// Advertising network campaign identifier (NSNumber)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkCampaignIdentifier API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos);

// Advertising network identifier (NSString)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkIdentifier API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos);

// Random entropy value for security (NSUUID)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkNonce API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos);

// Timestamp for this ad impression (NSNumber)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkTimestamp API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos);

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

SK_EXTERN NSString * const SKErrorDomain API_AVAILABLE(ios(3.0), macos(10.7));

// error codes for the SKErrorDomain
typedef NS_ENUM(NSInteger,SKErrorCode) {
    SKErrorUnknown,
    SKErrorClientInvalid,                                                                         // client is not allowed to issue the request, etc.
    SKErrorPaymentCancelled,                                                                      // user cancelled the request, etc.
    SKErrorPaymentInvalid,                                                                        // purchase identifier was invalid, etc.
    SKErrorPaymentNotAllowed,                                                                     // this device is not allowed to make the payment
    SKErrorStoreProductNotAvailable API_AVAILABLE(ios(3.0), macos(10.15)),                        // Product is not available in the current storefront
    SKErrorCloudServicePermissionDenied API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos),           // user has not allowed access to cloud service information
    SKErrorCloudServiceNetworkConnectionFailed API_AVAILABLE(ios(9.3)) API_UNAVAILABLE(macos),    // the device could not connect to the nework
    SKErrorCloudServiceRevoked API_AVAILABLE(ios(10.3)) API_UNAVAILABLE(macos),                   // user has revoked permission to use this cloud service
    SKErrorPrivacyAcknowledgementRequired API_AVAILABLE(ios(12.2), macos(10.14.4)),               // The user needs to acknowledge Apple's privacy policy
    SKErrorUnauthorizedRequestData API_AVAILABLE(ios(12.2), macos(10.14.4)),                      // The app is attempting to use SKPayment's requestData property, but does not have the appropriate entitlement
    SKErrorInvalidOfferIdentifier API_AVAILABLE(ios(12.2), macos(10.14.4)),                       // The specified subscription offer identifier is not valid
    SKErrorInvalidSignature API_AVAILABLE(ios(12.2), macos(10.14.4)),                             // The cryptographic signature provided is not valid
    SKErrorMissingOfferParams API_AVAILABLE(ios(12.2), macos(10.14.4)),                           // One or more parameters from SKPaymentDiscount is missing
    SKErrorInvalidOfferPrice API_AVAILABLE(ios(12.2), macos(10.14.4))                             // The price of the selected offer is not valid (e.g. lower than the current base subscription price)
} API_AVAILABLE(ios(3.0), macos(10.7));

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
    SKPaymentTransactionStateDeferred API_AVAILABLE(ios(8.0), macos(10.10)),   // The transaction is in the queue, but its final status is pending external action.
} API_AVAILABLE(ios(3.0), macos(10.7));

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS API_AVAILABLE(ios(3.0), macos(10.7)) @interface SKPaymentTransaction : NSObject {
@private
    id _internal;
}

// Only set if state is SKPaymentTransactionFailed
@property(nonatomic, readonly, nullable) NSError *error API_AVAILABLE(ios(3.0), macos(10.7));

// Only valid if state is SKPaymentTransactionStateRestored.
@property(nonatomic, readonly, nullable) SKPaymentTransaction *originalTransaction API_AVAILABLE(ios(3.0), macos(10.7));

@property(nonatomic, readonly) SKPayment *payment API_AVAILABLE(ios(3.0), macos(10.7));

// Available downloads (SKDownload) for this transaction
@property(nonatomic, readonly) NSArray<SKDownload *> *downloads API_AVAILABLE(ios(6.0), macos(10.8));

// The date when the transaction was added to the server queue.  Only valid if state is SKPaymentTransactionStatePurchased or SKPaymentTransactionStateRestored.
@property(nonatomic, readonly, nullable) NSDate *transactionDate API_AVAILABLE(ios(3.0), macos(10.7));

// The unique server-provided identifier.  Only valid if state is SKPaymentTransactionStatePurchased or SKPaymentTransactionStateRestored.
@property(nonatomic, readonly, nullable) NSString *transactionIdentifier API_AVAILABLE(ios(3.0), macos(10.7));

// Only valid if state is SKPaymentTransactionStatePurchased.
@property(nonatomic, readonly, nullable) NSData *transactionReceipt API_DEPRECATED_WITH_REPLACEMENT("-[NSBundle appStoreReceiptURL]", ios(3.0, 7.0)) API_UNAVAILABLE(macos, uikitformac);

@property(nonatomic, readonly) SKPaymentTransactionState transactionState API_AVAILABLE(ios(3.0), macos(10.7));

@end

NS_ASSUME_NONNULL_END
