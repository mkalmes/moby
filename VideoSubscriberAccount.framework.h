// ==========  VideoSubscriberAccount.framework/Headers/VSAccountMetadataRequest.h
//
//  VSAccountMetadataRequest.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <os/availability.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>
#import <VideoSubscriberAccount/VSAccountProviderResponse.h>
#import <Foundation/NSObject.h>

NS_ASSUME_NONNULL_BEGIN

@class NSArray<ObjectType>;
@class NSString;

/// Specifies which information the app wants to obtain about the subscriber's account.
/// You should only request the information you need to fulfill your contractual obligations.
VS_EXPORT API_AVAILABLE(ios(10.0), tvos(10.0))
@interface VSAccountMetadataRequest : NSObject

/// Identifies who is making the request.
@property (nonatomic, copy, nullable) NSString *channelIdentifier;

/// If non-empty, limits which account providers can respond to the request.
@property (nonatomic, copy) NSArray<NSString *> *supportedAccountProviderIdentifiers;

/// If non-empty, specifies providers which may be given more prominent placement
/// when choosing an account provider during authentication.
@property (nonatomic, copy) NSArray<NSString *> *featuredAccountProviderIdentifiers
API_AVAILABLE(ios(11.0), tvos(11.0));

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

/// The collection of authentication schemes that the app supports for this request.
/// This list may be used to determine compatibility of the app with providers.
/// Defaults to SAML.
@property (nonatomic, copy) NSArray<VSAccountProviderAuthenticationScheme> *supportedAuthenticationSchemes
API_AVAILABLE(ios(10.2), tvos(10.1));

@end

NS_ASSUME_NONNULL_END
// ==========  VideoSubscriberAccount.framework/Headers/VideoSubscriberAccountErrors.h
//
//  VideoSubscriberAccountErrors.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <os/availability.h>
#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSError.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSString;

/// The domain of all errors returned by VideoSubscriberAccount framework.
VS_EXTERN NSErrorDomain const VSErrorDomain
API_AVAILABLE(ios(10.0), tvos(10.0));

/// A key that can be used to obtain the subscription provider's SAML response string from an error user info dictionary.
VS_EXTERN NSString * const VSErrorInfoKeySAMLResponse
API_AVAILABLE(ios(10.0), tvos(10.0));

/// A key that can be used to obtain the subscription provider's SAML status code string from an error user info dictionary.
VS_EXTERN NSString * const VSErrorInfoKeySAMLResponseStatus
API_AVAILABLE(ios(10.0), tvos(10.0));

/// A key that can be used to obtain the account provider's response object from an error user info dictionary.
VS_EXTERN NSString * const VSErrorInfoKeyAccountProviderResponse
API_AVAILABLE(ios(10.2), tvos(10.1));

/// A key that can be used to obtain the identifier string of the user's unsupported subscription provider from an error user info dictionary.
VS_EXTERN NSString * const VSErrorInfoKeyUnsupportedProviderIdentifier
API_AVAILABLE(ios(10.3), tvos(10.3));

typedef NS_ENUM(NSInteger, VSErrorCode)
{
    VSErrorCodeAccessNotGranted = 0, // The user has not granted the app access to their subscription information.
    VSErrorCodeUnsupportedProvider = 1, // The system does not currently support the user's subscription provider.
    VSErrorCodeUserCancelled = 2, // The request was cancelled by the user.
    VSErrorCodeServiceTemporarilyUnavailable = 3, // The request failed, but a subsequent attempt might succeed.
    VSErrorCodeProviderRejected = 4,// The user's subscription provider did not allow the request to proceed, e.g. because the subscription tier doesn't include the resource, or interactive reauthentication is required, but the request does not allow interruption.
    VSErrorCodeInvalidVerificationToken = 5,// The request's verification token was rejected by the user's subscription provider.
}
API_AVAILABLE(ios(10.0), tvos(10.0));

NS_ASSUME_NONNULL_END
// ==========  VideoSubscriberAccount.framework/Headers/VSSubscription.h
//
//  VSSubscription.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <Foundation/NSObject.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSArray<ObjectType>;
@class NSDate;
@class NSString;

/// Describes the level of access to content.
typedef NS_ENUM(NSInteger, VSSubscriptionAccessLevel)
{
    VSSubscriptionAccessLevelUnknown,/// The default access level.
    VSSubscriptionAccessLevelFreeWithAccount, /// The customer has access to content that is offered for free to users with a valid account.  This value corresponds content in your availability feed with the "account" offering type.
    VSSubscriptionAccessLevelPaid, /// The customer also has access to content that is offered as part of a paid subscription.  The value corresponds content in your availability feed with the "subscription" offering type.
}
#if TARGET_OS_IPHONE
API_AVAILABLE(ios(11.0), tvos(11.0));
#else
;
#endif // TARGET_OS_IPHONE

/// A VSSubscription instance describes the extent to which a subscriber has
/// access to content.
#if TARGET_OS_IPHONE
VS_EXPORT API_AVAILABLE(ios(11.0), tvos(11.0))
#else
VS_EXPORT
#endif // #if TARGET_OS_IPHONE
@interface VSSubscription : NSObject

/// After this point in time, the subscription will be considered inactive.
///
/// If the current subscription becomes inactive, the system will behave as
/// though the user is not subscribed at all, i.e. as though the registration
/// center's current subscription had been set to nil.
///
/// Defaults to distantFuture.
///
/// Providing a value is useful in a limited number of scenarios, e.g. when the
/// a subscriber decides not to renew their subscription, you should provide an
/// expiration date that corresponds to the point in time when the final billing
/// cycle will end.
///
/// This might also be useful if the subscription only grants access to content
/// that is time-limited, e.g. a single season of games for a sports league.
@property (nonatomic, copy, null_resettable) NSDate *expirationDate;

/// Describes the level of access the subscriber has to your catalog of content.
///
/// It is an error to provide a subscription with an unknown access level as
/// the current subscription.  Instead, choose the access level that describes
/// the content that the subscriber can play.
@property (nonatomic, assign) VSSubscriptionAccessLevel accessLevel;

/// Identifies a subset of content from your catalog that subscriber can play.
///
/// Only provide values that are used in your availability feed's tier restrictions.
@property (nonatomic, copy, null_resettable) NSArray<NSString *> *tierIdentifiers;

/// Identifies the billing group associated with the subscription.  May be used,
/// for example, to restrict content availability based on the proximity of the
/// billing address to a specific venue.
@property (nonatomic, copy, nullable) NSString *billingIdentifier
#if TARGET_OS_IPHONE
API_AVAILABLE(ios(11.3), tvos(11.3));
#else
;
#endif // TARGET_OS_IPHONE

@end

NS_ASSUME_NONNULL_END
// ==========  VideoSubscriberAccount.framework/Headers/VideoSubscriberAccountDefines.h
//
//  VideoSubscriberAccountDefines.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <os/availability.h>
#import <Foundation/NSObjCRuntime.h>

#define VS_EXPORT __attribute__((visibility ("default")))

#ifdef __cplusplus
#define VS_EXTERN extern "C" VS_EXPORT
#else
#define VS_EXTERN extern VS_EXPORT
#endif
// ==========  VideoSubscriberAccount.framework/Headers/VSSubscriptionRegistrationCenter.h
//
//  VSSubscriptionRegistrationCenter.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <Foundation/NSObject.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VSSubscription;

/// VSSubscriptionRegistrationCenter stores subscription information.
#if TARGET_OS_IPHONE
VS_EXPORT API_AVAILABLE(ios(11.0), tvos(11.0))
#else
VS_EXPORT
#endif // #if TARGET_OS_IPHONE
@interface VSSubscriptionRegistrationCenter : NSObject

/// Use the default subscription registration center to tell the system about
/// the customer's ability to access content within your app.
+ (VSSubscriptionRegistrationCenter *)defaultSubscriptionRegistrationCenter;

/// Provide a subscription when the subscriber first authenticates, and when the
/// subscription changes.
///
/// When the subscriber signs out or otherwise loses access to subscription
/// content, invoke this method with nil.
///
/// You might also want to call this method opportunistically, if you happen to
/// have just confirmed the validity of the subscription, or in response to app
/// lifecycle events, e.g. when your app becomes active.  The system may use
/// this activity as a hint that the user is actively using the subscription.
///
/// It is an error to provide a current subscription with an unknown access
/// level; you should not provide a subscription if the user only has access to
/// content that is offered for free without any account requirements.
- (void)setCurrentSubscription:(nullable VSSubscription *)currentSubscription;

@end

NS_ASSUME_NONNULL_END
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
#import <VideoSubscriberAccount/VSAccountProviderResponse.h>
#import <VideoSubscriberAccount/VSSubscription.h>
#import <VideoSubscriberAccount/VSSubscriptionRegistrationCenter.h>
// ==========  VideoSubscriberAccount.framework/Headers/VSAccountManager.h
//
//  VSAccountManager.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <os/availability.h>
#import <Foundation/NSObject.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSDictionary<KeyType, ValueType>;
@class NSString;
@class NSError;
@class UIViewController;
@class VSAccountManagerResult;
@class VSAccountMetadata;
@class VSAccountMetadataRequest;

@protocol VSAccountManagerDelegate;

// The URL string used to deep link to the system TV Provider settings.
VS_EXTERN NSString * const VSOpenTVProviderSettingsURLString API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, uikitformac);

/// Represents the current state of the application's access to the user's subscription information.
typedef NS_ENUM(NSInteger, VSAccountAccessStatus)
{
    VSAccountAccessStatusNotDetermined = 0, // The user has not yet made a choice about whether to allow this access to the app.
    VSAccountAccessStatusRestricted = 1, // Restrictions, e.g. parental controls, prohibit the user from allowing access to the app.
    VSAccountAccessStatusDenied = 2, // The user has explicitly decided to not allow the app to access subscription information.
    VSAccountAccessStatusGranted = 3, // The user has currently decided to allow the app to access subscription information.
}
API_AVAILABLE(ios(10.0), tvos(10.0));

/// Options that may be provided when checking access status.
typedef NSString * VSCheckAccessOption NS_STRING_ENUM
API_AVAILABLE(ios(10.0), tvos(10.0));

/// A boolean indicating whether the user may be prompted to grant access.
VS_EXTERN VSCheckAccessOption const VSCheckAccessOptionPrompt
API_AVAILABLE(ios(10.0), tvos(10.0));

/// A VSAccountManager instance coordinates access to a subscriber's account.
VS_EXPORT API_AVAILABLE(ios(10.0), tvos(10.0))
@interface VSAccountManager : NSObject

/// An object that can help the account manager by presenting and dismissing view controllers when needed, and deciding whether to allow authentication with the selected provider.
/// Some requests may fail if a delegate is not provided.  For example, an account metadata request may require a delegate if it allows interruption.
@property (nonatomic, weak) id<VSAccountManagerDelegate> delegate;

/// Determine the state of the application's access to the user's subscription information.
/// @param options The only currently supported option key is VSCheckAccessOptionPrompt.
/// @param completionHandler A block to be called when the request finishes.  It will always be called exactly once.  It may be called before the method call returns.  It may be called on any queue.
/// @param accessStatus The current state the application's access to the user's subscription information.
/// @param error If the user did not grant access to the app, this will contain an error describing the result of the operation.
- (void)checkAccessStatusWithOptions:(NSDictionary<VSCheckAccessOption, id> *)options completionHandler:(void (^)(VSAccountAccessStatus accessStatus, NSError * _Nullable error))completionHandler  API_UNAVAILABLE(macos, uikitformac);

/// Begins requesting information about the subscriber's account.
/// @param request This identifies what specific information the app wants to know.
/// @param completionHandler A block to be called when the request finishes.  It will always be called exactly once.  It may be called before the method call returns.  It may be called on any queue.
/// @param metadata If the request finished successfully, this will contain information about the subscriber's account.
/// @param error If the request did not finish successfully, this will contain an error describing the result of the operation.
/// @returns A result object that may be used to cancel the in-flight request.  Cancellation is advisory, and does not guarantee that the request will finish immediately.
- (VSAccountManagerResult *)enqueueAccountMetadataRequest:(VSAccountMetadataRequest *)request completionHandler:(void (^)(VSAccountMetadata * _Nullable metadata, NSError * _Nullable error))completionHandler  API_UNAVAILABLE(macos, uikitformac);

@end


/// A VSAccountManager instance coordinates access to a subscriber's account.
API_AVAILABLE(ios(10.0), tvos(10.0))
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

@optional

/// This method can be used to temporarily refrain from authenticating with an
/// otherwise-supported provider during a transient outage.
/// This method will be called when the user chooses a supported provider from
/// the list of providers.
/// If you do not implement this method, the user will be able to authenticate
/// with all supported providers.
/// @param accountManager The account manager instance that received a metadata request.
/// @param accountProviderIdentifier Identifies the otherwise-supported account provider.
/// @returns Returning NO will cause the request will fail with an unsupported provider error.
- (BOOL)accountManager:(VSAccountManager *)accountManager shouldAuthenticateAccountProviderWithIdentifier:(NSString *)accountProviderIdentifier;

@end

NS_ASSUME_NONNULL_END
// ==========  VideoSubscriberAccount.framework/Headers/VSAccountManagerResult.h
//
//  VSAccountManagerResult.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <os/availability.h>
#import <Foundation/NSObject.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// Represents an in-flight request to an account manger.
VS_EXPORT API_AVAILABLE(ios(10.0), tvos(10.0))
@interface VSAccountManagerResult : NSObject

- (instancetype)init NS_UNAVAILABLE;

/// Advise the account manager that the app no longer needs the requested work to be done.
- (void)cancel;

@end

NS_ASSUME_NONNULL_END
// ==========  VideoSubscriberAccount.framework/Headers/VSAccountProviderResponse.h
//
//  VSAccountProviderResponse.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/NSObject.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// An opaque protocol name, to be coordinated with specific account providers.
typedef NSString *VSAccountProviderAuthenticationScheme NS_EXTENSIBLE_STRING_ENUM;

/// The authentication scheme for responses that use the SAML protocol.
VS_EXTERN VSAccountProviderAuthenticationScheme const VSAccountProviderAuthenticationSchemeSAML
NS_SWIFT_NAME(saml)
API_AVAILABLE(ios(10.2), tvos(10.1));

/// A value object that encapsulates the response given by an account provider.
VS_EXPORT API_AVAILABLE(ios(10.2), tvos(10.1))
@interface VSAccountProviderResponse : NSObject

/// Identifies the protocol used in constructing this response.
@property (nonatomic, readonly, copy) VSAccountProviderAuthenticationScheme authenticationScheme;

/// The status code for this response.
/// May be nil if there is no meaningful value for this type of response.
@property (nonatomic, readonly, copy, nullable) NSString *status;

/// The raw response from the provider.
/// May be nil if the response contained security-sensitive information.
@property (nonatomic, readonly, copy, nullable) NSString *body;

@end

NS_ASSUME_NONNULL_END
// ==========  VideoSubscriberAccount.framework/Headers/VSAccountMetadata.h
//
//  VSAccountMetadata.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <os/availability.h>
#import <Foundation/NSObject.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSDate;
@class NSString;
@class VSAccountProviderResponse;

/// A collection of information about a subscriber's account.
VS_EXPORT API_AVAILABLE(ios(10.0), tvos(10.0))
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

/// The response received from the account provider.
/// The value might be nil if your account metadata request did not specify any
/// attributes, or if the user does not have a valid authentication.
@property (nonatomic, readonly, strong, nullable) VSAccountProviderResponse *accountProviderResponse
API_AVAILABLE(ios(10.2), tvos(10.1));

@end

NS_ASSUME_NONNULL_END
