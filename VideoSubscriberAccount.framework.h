// ==========  VideoSubscriberAccount.framework/Headers/VSAccountMetadataRequest.h
//
//  VSAccountMetadataRequest.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>
#import <Foundation/NSObject.h>

NS_ASSUME_NONNULL_BEGIN

@class NSArray<ObjectType>;
@class NSString;

/// Specifies which information the app wants to obtain about the subscriber's account.
/// You should only request the information you need to fulfill your contractual obligations.
NS_CLASS_AVAILABLE_IOS(10_0) __TVOS_AVAILABLE(10.0) __WATCHOS_UNAVAILABLE
@interface VSAccountMetadataRequest : NSObject

/// Identifies who is making the request.
@property (nonatomic, copy, nullable) NSString *channelIdentifier;

/// If non-empty, limits which account providers can respond to the request.
@property (nonatomic, copy) NSArray<NSString *> *supportedAccountProviderIdentifiers;

/// A value that the account provider may use to verify the identity of the requesting app.
@property (nonatomic, copy, nullable) NSString *verificationToken;

/// Whether to request information that identifies the account provider.
@property (nonatomic, assign) BOOL includeAccountProviderIdentifier;

/// Whether to request the expiration date of the subscriber's current authentication.
@property (nonatomic, assign) BOOL includeAuthenticationExpirationDate;

/// A brief, user-presentable name for the video that the app will play if it receives a successful response.
/// For example, "What's New in Swift" or "Office Space"
/// Do not provide a value if the request will not be used to play a specific video.
@property (nonatomic, copy, nullable) NSString *localizedVideoTitle;

/// Whether the user might expect to be prompted to authenticate in order to complete this request.
@property (nonatomic, assign, getter=isInterruptionAllowed) BOOL interruptionAllowed;

/// Controls whether the request will ignore any cached credentials.
@property (nonatomic, assign) BOOL forceAuthentication;

/// Attributes to add to a SAML attributeQuery request and sent to the account provider.
@property (nonatomic, copy) NSArray<NSString *> *attributeNames;

@end

NS_ASSUME_NONNULL_END
// ==========  VideoSubscriberAccount.framework/Headers/VideoSubscriberAccountErrors.h
//
//  VideoSubscriberAccountErrors.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSError.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSString;

/// The domain of all errors returned by VideoSubscriberAccount framework.
VS_EXTERN NSErrorDomain const VSErrorDomain
NS_AVAILABLE_IOS(10_0) __TVOS_AVAILABLE(10.0) __WATCHOS_UNAVAILABLE;

/// A key that can be used to obtain the subscription provider's SAML response string from an error user info dictionary.
VS_EXTERN NSString * const VSErrorInfoKeySAMLResponse
NS_AVAILABLE_IOS(10_0) __TVOS_AVAILABLE(10.0) __WATCHOS_UNAVAILABLE;

/// A key that can be used to obtain the subscription provider's SAML status code string from an error user info dictionary.
VS_EXTERN NSString * const VSErrorInfoKeySAMLResponseStatus
NS_AVAILABLE_IOS(10_0) __TVOS_AVAILABLE(10.0) __WATCHOS_UNAVAILABLE;

/// A key that can be used to obtain the identifier string of the user's unsupported subscription provider from an error user info dictionary.
VS_EXTERN NSString * const VSErrorInfoKeyUnsupportedProviderIdentifier
NS_AVAILABLE_IOS(10_0) __TVOS_AVAILABLE(10.0) __WATCHOS_UNAVAILABLE;

typedef NS_ENUM(NSInteger, VSErrorCode)
{
    VSErrorCodeAccessNotGranted = 0, // The user has not granted the app access to their subscription information.
    VSErrorCodeUnsupportedProvider = 1, // The system does not currently support the user's subscription provider.
    VSErrorCodeUserCancelled = 2, // The request was cancelled by the user.
    VSErrorCodeServiceTemporarilyUnavailable = 3, // The request failed, but a subsequent attempt might succeed.
    VSErrorCodeProviderRejected = 4,// The user's subscription provider did not allow the request to proceed, e.g. because the subscription tier doesn't include the resource, or interactive reauthentication is required, but the request does not allow interruption.
    VSErrorCodeInvalidVerificationToken = 5,// The request's verification token was rejected by the user's subscription provider.
}
NS_ENUM_AVAILABLE_IOS(10_0) __TVOS_AVAILABLE(10.0) __WATCHOS_UNAVAILABLE;

NS_ASSUME_NONNULL_END
// ==========  VideoSubscriberAccount.framework/Headers/VideoSubscriberAccountDefines.h
//
//  VideoSubscriberAccountDefines.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <Foundation/NSObjCRuntime.h>

#define VS_EXPORT __attribute__((visibility ("default")))

#ifdef __cplusplus
#define VS_EXTERN extern "C" VS_EXPORT
#else
#define VS_EXTERN extern VS_EXPORT
#endif

// ==========  VideoSubscriberAccount.framework/Headers/VideoSubscriberAccount.h
//
//  VideoSubscriberAccount.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountErrors.h>
#import <VideoSubscriberAccount/VSAccountManager.h>
#import <VideoSubscriberAccount/VSAccountManagerResult.h>
#import <VideoSubscriberAccount/VSAccountMetadata.h>
#import <VideoSubscriberAccount/VSAccountMetadataRequest.h>
// ==========  VideoSubscriberAccount.framework/Headers/VSAccountManager.h
//
//  VSAccountManager.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <Foundation/NSObject.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSDictionary<KeyType, ValueType>;
@class NSError;
@class UIViewController;
@class VSAccountManagerResult;
@class VSAccountMetadata;
@class VSAccountMetadataRequest;

@protocol VSAccountManagerDelegate;

/// Represents the current state of the application's access to the user's subscription information.
typedef NS_ENUM(NSInteger, VSAccountAccessStatus)
{
    VSAccountAccessStatusNotDetermined = 0, // The user has not yet made a choice about whether to allow this access to the app.
    VSAccountAccessStatusRestricted = 1, // Restrictions, e.g. parental controls, prohibit the user from allowing access to the app.
    VSAccountAccessStatusDenied = 2, // The user has explicitly decided to not allow the app to access subscription information.
    VSAccountAccessStatusGranted = 3, // The user has currently decided to allow the app to access subscription information.
}
NS_ENUM_AVAILABLE_IOS(10_0) __TVOS_AVAILABLE(10.0) __WATCHOS_UNAVAILABLE;

/// Options that may be provided when checking access status.
typedef NSString * VSCheckAccessOption NS_STRING_ENUM
NS_AVAILABLE_IOS(10_0) __TVOS_AVAILABLE(10.0) __WATCHOS_UNAVAILABLE;

/// A boolean indicating whether the user may be prompted to grant access.
VS_EXTERN VSCheckAccessOption const VSCheckAccessOptionPrompt
NS_AVAILABLE_IOS(10_0) __TVOS_AVAILABLE(10.0) __WATCHOS_UNAVAILABLE;

/// A VSAccountManager instance coordinates access to a subscriber's account.
NS_CLASS_AVAILABLE_IOS(10_0) __TVOS_AVAILABLE(10.0) __WATCHOS_UNAVAILABLE
@interface VSAccountManager : NSObject

/// An object that can help the account manager by presenting and dismissing view controllers when needed.
/// Some requests may fail if a delegate is not provided.  For example, an account metadata request may require a delegate if it allows interruption.
@property (nonatomic, weak) id<VSAccountManagerDelegate> delegate;

/// Determine the state of the application's access to the user's subscription information.
/// @param options The only currently supported option key is VSCheckAccessOptionPrompt.
/// @param completionHandler A block to be called when the request finishes.  It will always be called exactly once.  It may be called before the method call returns.  It may be called on any queue.
/// @param accessStatus The current state the application's access to the user's subscription information.
/// @param error If the user did not grant access to the app, this will contain an error describing the result of the operation.
- (void)checkAccessStatusWithOptions:(NSDictionary<VSCheckAccessOption, id> *)options completionHandler:(void (^)(VSAccountAccessStatus accessStatus, NSError * __nullable error))completionHandler;

/// Begins requesting information about the subscriber's account.
/// @param request This identifies what specific information the app wants to know.
/// @param completionHandler A block to be called when the request finishes.  It will always be called exactly once.  It may be called before the method call returns.  It may be called on any queue.
/// @param metadata If the request finished successfully, this will contain information about the subscriber's account.
/// @param error If the request did not finish successfully, this will contain an error describing the result of the operation.
/// @returns A result object that may be used to cancel the in-flight request.  Cancellation is advisory, and does not guarantee that the request will finish immediately.
- (VSAccountManagerResult *)enqueueAccountMetadataRequest:(VSAccountMetadataRequest *)request completionHandler:(void (^)(VSAccountMetadata * __nullable metadata, NSError * __nullable error))completionHandler;

@end


/// A VSAccountManager instance coordinates access to a subscriber's account.
VS_EXPORT NS_AVAILABLE_IOS(10_0) __TVOS_AVAILABLE(10.0) __WATCHOS_UNAVAILABLE
@protocol VSAccountManagerDelegate <NSObject>

@required

/// Called when the account manager needs user interaction to complete a request.
/// @param accountManager The account manager instance that needs to show the view controller.
/// @param viewController A view controller that needs to be presented to the user.  You must use -presentViewController:animated:completion: to begin presenting this view controller before returning from this method.
- (void)accountManager:(VSAccountManager *)accountManager presentViewController:(UIViewController *)viewController;

/// Called when the account manager is finished using the presented view controller.
/// @param accountManager The account manager instance that previously asked to show the view controller.
/// @param viewController The view controller that is being presented to the user.  You must use -dismissViewControllerAnimated:completion: to begin dismissing the view controller before returning from this method.
- (void)accountManager:(VSAccountManager *)accountManager dismissViewController:(UIViewController *)viewController;

@end

NS_ASSUME_NONNULL_END
// ==========  VideoSubscriberAccount.framework/Headers/VSAccountManagerResult.h
//
//  VSAccountManagerResult.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <Foundation/NSObject.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// Represents an in-flight request to an account manger.
NS_CLASS_AVAILABLE_IOS(10_0) __TVOS_AVAILABLE(10.0) __WATCHOS_UNAVAILABLE
@interface VSAccountManagerResult : NSObject

- (instancetype)init NS_UNAVAILABLE;

/// Advise the account manager that the app no longer needs the requested work to be done.
- (void)cancel;

@end

NS_ASSUME_NONNULL_END
// ==========  VideoSubscriberAccount.framework/Headers/VSAccountMetadata.h
//
//  VSAccountMetadata.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <Foundation/NSObject.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSDate;
@class NSString;

/// A collection of information about a subscriber's account.
NS_CLASS_AVAILABLE_IOS(10_0) __TVOS_AVAILABLE(10.0) __WATCHOS_UNAVAILABLE
@interface VSAccountMetadata : NSObject

/// A value that uniquely identifies the account provider.
/// You may use this value to brand your app.
@property (nonatomic, readonly, copy, nullable) NSString *accountProviderIdentifier;

/// Specifies when the user might need to re-authenticate with the account provider.
/// The value might be nil if the user is not currently authenticated.
@property (nonatomic, readonly, copy, nullable) NSDate *authenticationExpirationDate;

/// An opaque blob of data that can be used to cryptographically verify that the
/// SAML AttributeQuery response actually came from the account provider.
@property (nonatomic, readonly, copy, nullable) NSData *verificationData;

/// The SAML AttributeQuery response received from the account provider.
/// The value might be nil if your account metadata request did not specify any SAML attributes or if the user does not have a valid authentication.
@property (nonatomic, readonly, copy, nullable) NSString *SAMLAttributeQueryResponse;

@end

NS_ASSUME_NONNULL_END
