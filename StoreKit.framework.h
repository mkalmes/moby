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
@protocol SKPaymentTransactionObserver;

NS_ASSUME_NONNULL_BEGIN

// SKPaymentQueue interacts with the server-side payment queue
SK_EXTERN_CLASS_AVAILABLE(3_0) @interface SKPaymentQueue : NSObject {
@private
    id _internal;
}

+ (instancetype)defaultQueue NS_AVAILABLE_IOS(3_0);

// NO if this device is not able or allowed to make payments
+ (BOOL)canMakePayments NS_AVAILABLE_IOS(3_0);

// Asynchronous.  Add a payment to the server queue.  The payment is copied to add an SKPaymentTransaction to the transactions array.  The same payment can be added multiple times to create multiple transactions.
- (void)addPayment:(SKPayment *)payment NS_AVAILABLE_IOS(3_0);

// Asynchronous.  Will add completed transactions for the current user back to the queue to be re-completed.  User will be asked to authenticate.  Observers will receive 0 or more -paymentQueue:updatedTransactions:, followed by either -paymentQueueRestoreCompletedTransactionsFinished: on success or -paymentQueue:restoreCompletedTransactionsFailedWithError: on failure.  In the case of partial success, some transactions may still be delivered.
- (void)restoreCompletedTransactions  NS_AVAILABLE_IOS(3_0);
- (void)restoreCompletedTransactionsWithApplicationUsername:(nullable NSString *)username NS_AVAILABLE_IOS(7_0);

// Asynchronous.  Remove a finished (i.e. failed or completed) transaction from the queue.  Attempting to finish a purchasing transaction will throw an exception.
- (void)finishTransaction:(SKPaymentTransaction *)transaction NS_AVAILABLE_IOS(3_0);

// Asynchronous.  Start the given downloads (SKDownload).
- (void)startDownloads:(NSArray<SKDownload *> *)downloads NS_AVAILABLE_IOS(6_0);

// Asynchronous.  Pause/resume downloads (SKDownload).
- (void)pauseDownloads:(NSArray<SKDownload *> *)downloads NS_AVAILABLE_IOS(6_0);
- (void)resumeDownloads:(NSArray<SKDownload *> *)downloads NS_AVAILABLE_IOS(6_0);

// Asynchronous.  Cancel downloads (SKDownload)
- (void)cancelDownloads:(NSArray<SKDownload *> *)downloads NS_AVAILABLE_IOS(6_0);

// Observers are not retained.  The transactions array will only be synchronized with the server while the queue has observers.  This may require that the user authenticate.
- (void)addTransactionObserver:(id <SKPaymentTransactionObserver>)observer NS_AVAILABLE_IOS(3_0);
- (void)removeTransactionObserver:(id <SKPaymentTransactionObserver>)observer NS_AVAILABLE_IOS(3_0);

// Array of unfinished SKPaymentTransactions.  Only valid while the queue has observers.  Updated asynchronously.
@property(nonatomic, readonly) NSArray<SKPaymentTransaction *> *transactions NS_AVAILABLE_IOS(3_0);

@end


@protocol SKPaymentTransactionObserver <NSObject>
@required
// Sent when the transaction array has changed (additions or state changes).  Client should check state of transactions and finish as appropriate.
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray<SKPaymentTransaction *> *)transactions NS_AVAILABLE_IOS(3_0);

@optional
// Sent when transactions are removed from the queue (via finishTransaction:).
- (void)paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray<SKPaymentTransaction *> *)transactions NS_AVAILABLE_IOS(3_0);

// Sent when an error is encountered while adding transactions from the user's purchase history back to the queue.
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error NS_AVAILABLE_IOS(3_0);

// Sent when all transactions from the user's purchase history have successfully been added back to the queue.
- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue NS_AVAILABLE_IOS(3_0);

// Sent when the download state has changed.
- (void)paymentQueue:(SKPaymentQueue *)queue updatedDownloads:(NSArray<SKDownload *> *)downloads NS_AVAILABLE_IOS(6_0);

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
#define SK_EXTERN_CLASS_AVAILABLE(version) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(NA, version)
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

SK_EXTERN_CLASS_AVAILABLE(7_0) @interface SKReceiptRefreshRequest : SKRequest

- (instancetype)initWithReceiptProperties:(nullable NSDictionary<NSString *, id> *)properties NS_AVAILABLE_IOS(7_0);
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *receiptProperties NS_AVAILABLE_IOS(7_0);

@end

SK_EXTERN void SKTerminateForInvalidReceipt(void) NS_AVAILABLE_IOS(7_1);

// Receipt properties for sandbox testing:
SK_EXTERN NSString * const SKReceiptPropertyIsExpired NS_AVAILABLE_IOS(7_0);  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsRevoked NS_AVAILABLE_IOS(7_0);  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsVolumePurchase NS_AVAILABLE_IOS(7_0);  // NSNumber BOOL, defaults to NO

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

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS_AVAILABLE(3_0) @interface SKProduct : NSObject {
@private
    id _internal;
}

@property(nonatomic, readonly) NSString *localizedDescription NS_AVAILABLE_IOS(3_0);

@property(nonatomic, readonly) NSString *localizedTitle NS_AVAILABLE_IOS(3_0);

@property(nonatomic, readonly) NSDecimalNumber *price NS_AVAILABLE_IOS(3_0);

@property(nonatomic, readonly) NSLocale *priceLocale NS_AVAILABLE_IOS(3_0);

@property(nonatomic, readonly) NSString *productIdentifier NS_AVAILABLE_IOS(3_0);

// YES if this product has content downloadable using SKDownload
@property(nonatomic, readonly, getter=isDownloadable) BOOL downloadable NS_AVAILABLE_IOS(6_0);

// Sizes in bytes (NSNumber [long long]) of the downloads available for this product
@property(nonatomic, readonly) NSArray<NSNumber *> *downloadContentLengths NS_AVAILABLE_IOS(6_0);

// Version of the downloadable content
@property(nonatomic, readonly) NSString *downloadContentVersion NS_AVAILABLE_IOS(6_0);

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
SK_EXTERN_CLASS_AVAILABLE(6_0) @interface SKStoreProductViewController : UIViewController

// Delegate for product page events
@property(nonatomic, assign, nullable) id <SKStoreProductViewControllerDelegate> delegate NS_AVAILABLE_IOS(6_0);

// Load product view for the product with the given parameters.  See below for parameters (SKStoreProductParameter*).
// Block is invoked when the load finishes.
- (void)loadProductWithParameters:(NSDictionary<NSString *, id> *)parameters completionBlock:(nullable void(^)(BOOL result, NSError * __nullable error))block NS_AVAILABLE_IOS(6_0);

@end


@protocol SKStoreProductViewControllerDelegate <NSObject>

@optional

// Sent if the user requests that the page be dismissed
- (void)productViewControllerDidFinish:(SKStoreProductViewController *)viewController NS_AVAILABLE_IOS(6_0);

@end


// iTunes Store item identifier (NSNumber) of the product
SK_EXTERN NSString * const SKStoreProductParameterITunesItemIdentifier NS_AVAILABLE_IOS(6_0);

// iTunes Store affiliate token (NSString)
SK_EXTERN NSString * const SKStoreProductParameterAffiliateToken NS_AVAILABLE_IOS(8_0);

// iTunes Store affiliate campaign token (NSString)
SK_EXTERN NSString * const SKStoreProductParameterCampaignToken NS_AVAILABLE_IOS(8_0);

// Analytics provider token (NSString)
SK_EXTERN NSString * const SKStoreProductParameterProviderToken NS_AVAILABLE_IOS(8_3);

NS_ASSUME_NONNULL_END
// ==========  StoreKit.framework/Headers/StoreKit.h
//
//  StoreKit.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <StoreKit/SKDownload.h>
#import <StoreKit/SKError.h>
#import <StoreKit/SKPayment.h>
#import <StoreKit/SKPaymentQueue.h>
#import <StoreKit/SKPaymentTransaction.h>
#import <StoreKit/SKProduct.h>
#import <StoreKit/SKProductsRequest.h>
#import <StoreKit/SKReceiptRefreshRequest.h>
#import <StoreKit/SKRequest.h>
#import <StoreKit/SKStoreProductViewController.h>
#import <StoreKit/StoreKitDefines.h>
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

SK_EXTERN_CLASS_AVAILABLE(3_0) @interface SKPayment : NSObject <NSCopying, NSMutableCopying> {
@private
    id _internal;
}

+ (instancetype)paymentWithProduct:(SKProduct *)product NS_AVAILABLE_IOS(3_0);

+ (id)paymentWithProductIdentifier:(NSString *)identifier NS_DEPRECATED_IOS(3_0, 5_0, "Use +paymentWithProduct: after fetching the available products using SKProductsRequest");

// Identifier agreed upon with the store.  Required.
@property(nonatomic, copy, readonly) NSString *productIdentifier NS_AVAILABLE_IOS(3_0);

// Payment request data agreed upon with the store.  Optional.
@property(nonatomic, copy, readonly, nullable) NSData *requestData NS_AVAILABLE_IOS(3_0);

// default: 1.  Must be at least 1.
@property(nonatomic, readonly) NSInteger quantity NS_AVAILABLE_IOS(3_0);

// Application-specific user identifier.  Optional.
@property(nonatomic, copy, readonly, nullable) NSString *applicationUsername NS_AVAILABLE_IOS(7_0);

// Force an "ask to buy" flow for this payment, in the sandbox
@property(nonatomic, readonly) BOOL simulatesAskToBuyInSandbox NS_AVAILABLE_IOS(8_3);

@end


SK_EXTERN_CLASS_AVAILABLE(3_0) @interface SKMutablePayment : SKPayment

@property(nonatomic, copy, readwrite) NSString *applicationUsername NS_AVAILABLE_IOS(7_0);
@property(nonatomic, copy, readwrite) NSString *productIdentifier NS_AVAILABLE_IOS(3_0);
@property(nonatomic, readwrite) NSInteger quantity NS_AVAILABLE_IOS(3_0);
@property(nonatomic, copy, readwrite, nullable) NSData *requestData NS_AVAILABLE_IOS(3_0);
@property(nonatomic, readwrite) BOOL simulatesAskToBuyInSandbox NS_AVAILABLE_IOS(8_3);

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
SK_EXTERN_CLASS_AVAILABLE(3_0) @interface SKRequest : NSObject {
@private
    id _requestInternal;
}

@property(nonatomic, assign, nullable) id <SKRequestDelegate> delegate NS_AVAILABLE_IOS(3_0);

// Cancel the request if it has started.
- (void)cancel NS_AVAILABLE_IOS(3_0);

// Start the request if it has not already been started.
- (void)start NS_AVAILABLE_IOS(3_0);

@end


@protocol SKRequestDelegate <NSObject>

@optional
- (void)requestDidFinish:(SKRequest *)request NS_AVAILABLE_IOS(3_0);
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error NS_AVAILABLE_IOS(3_0);

@end

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
} NS_AVAILABLE_IOS(6_0);

SK_EXTERN NSTimeInterval SKDownloadTimeRemainingUnknown NS_AVAILABLE_IOS(6_0);

SK_EXTERN_CLASS_AVAILABLE(6_0) @interface SKDownload : NSObject

// State of the download
@property(nonatomic, readonly) SKDownloadState downloadState NS_AVAILABLE_IOS(6_0);

// Total size of the content, in bytes
@property(nonatomic, readonly) long long contentLength NS_AVAILABLE_IOS(6_0);

// Identifier for this content
@property(nonatomic, readonly) NSString *contentIdentifier NS_AVAILABLE_IOS(6_0);

// Location of the content data, if downloadState is SKDownloadStateFinished
@property(nonatomic, readonly, nullable) NSURL *contentURL NS_AVAILABLE_IOS(6_0);

// Content version
@property(nonatomic, readonly) NSString *contentVersion NS_AVAILABLE_IOS(6_0);

// Failure error, if downloadState is SKDownloadStateFailed
@property(nonatomic, readonly, nullable) NSError *error NS_AVAILABLE_IOS(6_0);

// Overall progress for the download [0..1]
@property(nonatomic, readonly) float progress NS_AVAILABLE_IOS(6_0);

// Estimated time remaining to complete the download, in seconds.  Value is SKDownloadTimeRemainingUnknown if estimate is unknownxx.
@property(nonatomic, readonly) NSTimeInterval timeRemaining NS_AVAILABLE_IOS(6_0);

// Transaction for this download
@property(nonatomic, readonly) SKPaymentTransaction *transaction NS_AVAILABLE_IOS(6_0);

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
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response NS_AVAILABLE_IOS(3_0);

@end


// request information about products for your application
SK_EXTERN_CLASS_AVAILABLE(3_0) @interface SKProductsRequest : SKRequest {
@private
    id _productsRequestInternal;
}

// Set of string product identifiers
- (instancetype)initWithProductIdentifiers:(NSSet<NSString *> *)productIdentifiers NS_AVAILABLE_IOS(3_0);

@property(nonatomic, assign, nullable) id <SKProductsRequestDelegate> delegate NS_AVAILABLE_IOS(3_0);

@end


SK_EXTERN_CLASS_AVAILABLE(3_0) @interface SKProductsResponse : NSObject {
@private
    id _internal;
}

// Array of SKProduct instances.
@property(nonatomic, readonly) NSArray<SKProduct *> *products NS_AVAILABLE_IOS(3_0);

// Array of invalid product identifiers.
@property(nonatomic, readonly) NSArray<NSString *> *invalidProductIdentifiers NS_AVAILABLE_IOS(3_0);

@end

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

SK_EXTERN NSString * const SKErrorDomain NS_AVAILABLE_IOS(3_0);

// error codes for the SKErrorDomain
enum {
    SKErrorUnknown,
    SKErrorClientInvalid,               // client is not allowed to issue the request, etc.
    SKErrorPaymentCancelled,            // user cancelled the request, etc.
    SKErrorPaymentInvalid,              // purchase identifier was invalid, etc.
    SKErrorPaymentNotAllowed,           // this device is not allowed to make the payment
    SKErrorStoreProductNotAvailable,    // Product is not available in the current storefront
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
    SKPaymentTransactionStateDeferred NS_ENUM_AVAILABLE_IOS(8_0),   // The transaction is in the queue, but its final status is pending external action.
} NS_AVAILABLE_IOS(3_0);

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS_AVAILABLE(3_0) @interface SKPaymentTransaction : NSObject {
@private
    id _internal;
}

// Only set if state is SKPaymentTransactionFailed
@property(nonatomic, readonly, nullable) NSError *error NS_AVAILABLE_IOS(3_0);

// Only valid if state is SKPaymentTransactionStateRestored.
@property(nonatomic, readonly, nullable) SKPaymentTransaction *originalTransaction NS_AVAILABLE_IOS(3_0);

@property(nonatomic, readonly) SKPayment *payment NS_AVAILABLE_IOS(3_0);

// Available downloads (SKDownload) for this transaction
@property(nonatomic, readonly) NSArray<SKDownload *> *downloads NS_AVAILABLE_IOS(6_0);

// The date when the transaction was added to the server queue.  Only valid if state is SKPaymentTransactionStatePurchased or SKPaymentTransactionStateRestored.
@property(nonatomic, readonly, nullable) NSDate *transactionDate NS_AVAILABLE_IOS(3_0);

// The unique server-provided identifier.  Only valid if state is SKPaymentTransactionStatePurchased or SKPaymentTransactionStateRestored.
@property(nonatomic, readonly, nullable) NSString *transactionIdentifier NS_AVAILABLE_IOS(3_0);

// Only valid if state is SKPaymentTransactionStatePurchased.
@property(nonatomic, readonly, nullable) NSData *transactionReceipt NS_DEPRECATED_IOS(3_0, 7_0, "Use -[NSBundle appStoreReceiptURL]");

@property(nonatomic, readonly) SKPaymentTransactionState transactionState NS_AVAILABLE_IOS(3_0);

@end

NS_ASSUME_NONNULL_END
