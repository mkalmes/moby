// ==========  AuthenticationServices.framework/Headers/ASAuthorizationOpenIDRequest.h
//
//  ASAuthorizationOpenIDRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorization.h>
#import <AuthenticationServices/ASAuthorizationRequest.h>

NS_ASSUME_NONNULL_BEGIN

/*! @enum Operation which should be executed.
 */
typedef NSString * ASAuthorizationOpenIDOperation API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
NS_SWIFT_NAME(ASAuthorization.OpenIDOperation) NS_TYPED_EXTENSIBLE_ENUM;
AS_EXTERN ASAuthorizationOpenIDOperation const ASAuthorizationOperationImplicit API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));
AS_EXTERN ASAuthorizationOpenIDOperation const ASAuthorizationOperationLogin API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));
AS_EXTERN ASAuthorizationOpenIDOperation const ASAuthorizationOperationRefresh API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));
AS_EXTERN ASAuthorizationOpenIDOperation const ASAuthorizationOperationLogout API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASAuthorizationOpenIDRequest : ASAuthorizationRequest

/*! @abstract The contact information to be requested from the user.  Only scopes for which this app was authorized for will be returned.
 */
@property (nonatomic, copy, nullable) NSArray<ASAuthorizationScope> *requestedScopes;

/*! @abstract State to be passed to the identity provider.  This value will be returned as a part of successful ASAuthorization response.
 @note The state size may depend on the actual technology used and an error might be returned by the request execution. 
 */
@property (nonatomic, copy, nullable) NSString *state;

/*! @abstract Operation to be executed by the request. The ASAuthorizationOperationImplicit operation interpretation depends on the credential provider implementation.
 */
@property (nonatomic, copy) ASAuthorizationOpenIDOperation requestedOperation;

@end

NS_ASSUME_NONNULL_END

// ==========  AuthenticationServices.framework/Headers/ASCredentialServiceIdentifier.h
//
//  ASCredentialServiceIdentifier.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*! @enum ASCredentialServiceIdentifierType
 @abstract The type of value represented by the service identifier.
 @constant ASCredentialServiceIdentifierTypeDomain The service identifier represents a domain name that conforms to RFC 1035.
 @constant ASCredentialServiceIdentifierTypeURL The service identifier represents a URL that conforms to RFC 1738.
 */
typedef NS_ENUM(NSInteger, ASCredentialServiceIdentifierType) {
    ASCredentialServiceIdentifierTypeDomain,
    ASCredentialServiceIdentifierTypeURL,
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(uikitformac, macos, tvos, watchos) NS_SWIFT_NAME(ASCredentialServiceIdentifier.IdentifierType);

AS_EXTERN API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(uikitformac, macos, tvos, watchos)
@interface ASCredentialServiceIdentifier : NSObject <NSCopying, NSSecureCoding>

/*! @abstract Initializes an ASCredentialServiceIdentifier object.
 @param identifier string value for the service identifier.
 @param type the type that the service identifier string represents.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier type:(ASCredentialServiceIdentifierType)type;

/*! @abstract Get the identifier.
 @result The service identifier.
 */
@property (nonatomic, readonly, copy) NSString *identifier;

/*! @abstract Get the service identifier type.
 @result The service identifier type.
 */
@property (nonatomic, readonly) ASCredentialServiceIdentifierType type;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASAuthorizationProviderExtensionAuthorizationRequest.h
//
//  ASAuthorizationProviderExtensionAuthorizationRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * ASAuthorizationProviderAuthorizationOperation API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(uikitformac, watchos, tvos)
NS_SWIFT_NAME(ASAuthorizationProviderAuthorization.Operation) NS_TYPED_EXTENSIBLE_ENUM;

@class ASAuthorizationProviderExtensionAuthorizationRequest;

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(uikitformac, watchos, tvos)
@protocol ASAuthorizationProviderExtensionAuthorizationRequestHandler <NSObject>

/*! @abstract Called to begin the authorization. It’s called on the main thread.
 */
- (void)beginAuthorizationWithRequest:(ASAuthorizationProviderExtensionAuthorizationRequest *)request;

@optional

/*! @abstract Called when the authorization was canceled by authorization service. It’s called on the main thread.
 */
- (void)cancelAuthorizationWithRequest:(ASAuthorizationProviderExtensionAuthorizationRequest *)request;

@end

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(uikitformac, watchos, tvos)
@interface ASAuthorizationProviderExtensionAuthorizationRequest : NSObject

/*! @abstract Call when authorization was not handled.
 */
- (void)doNotHandle;

/*! @abstract Call when authorization needs to be canceled from some reason (for example user pressed Cancel button).
 */
- (void)cancel;

/*! @abstract Call when authorization succeeded without any output.
 */
- (void)complete;

/*! @abstract Call when authorization succeeded with an authorization tokens stored in HTTP headers.
 */
- (void)completeWithHTTPAuthorizationHeaders:(NSDictionary<NSString *, NSString *> *)httpAuthorizationHeaders NS_SWIFT_NAME(complete(httpAuthorizationHeaders:));

/*! @abstract Call when authorization succeeded with a HTTP response.
 */
- (void)completeWithHTTPResponse:(NSHTTPURLResponse *)httpResponse httpBody:(NSData *)httpBody NS_SWIFT_NAME(complete(httpResponse:httpBody:));

/*! @abstract Call when authorization failed with an error.
 */
- (void)completeWithError:(NSError *)error NS_SWIFT_NAME(complete(error:));

/*! @abstract Asks authorization service to show extension view controller. If the controller cannot be shown an error is returned.
 */
- (void)presentAuthorizationViewControllerWithCompletion:(void(^)(BOOL success, NSError * _Nullable error))completion;

/*! @abstract Request URL with all components.
 */
@property (nonatomic, readonly) NSURL *url;

/*! @abstract Operation to be executed by the extension.
 */
@property (nonatomic, readonly) ASAuthorizationProviderAuthorizationOperation requestedOperation;

/*! @abstract Request HTTP headers.
 */
@property (nonatomic, readonly) NSDictionary<NSString *, NSString *> *httpHeaders;

/*! @abstract Request body.
 */
@property (nonatomic, readonly) NSData *httpBody;

/*! @abstract Realm.
 */
@property (nonatomic, readonly, copy) NSString *realm;

/*! @abstract Extension data from extension configuration provided by MDM stored as a property-list.
 */
@property (nonatomic, readonly) NSDictionary *extensionData;

/*! @abstract Identification of the calling application.
 */
@property (nonatomic, readonly, copy) NSString *callerBundleIdentifier;

/*! @abstract Authorization options.
 */
@property (nonatomic, readonly) NSDictionary *authorizationOptions;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASAuthorizationCredential.h
//
//  ASAuthorizationCredential.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@protocol ASAuthorizationCredential <NSObject, NSCopying, NSSecureCoding>

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASCredentialProviderExtensionContext.h
//
//  ASCredentialProviderExtensionContext.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

@class ASPasswordCredential;

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(uikitformac, macos, tvos, watchos)
NSErrorDomain const ASExtensionErrorDomain;

typedef NS_ERROR_ENUM(ASExtensionErrorDomain, ASExtensionErrorCode) {
    ASExtensionErrorCodeFailed = 0,
    ASExtensionErrorCodeUserCanceled = 1,
    ASExtensionErrorCodeUserInteractionRequired = 100,
    ASExtensionErrorCodeCredentialIdentityNotFound = 101,
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(uikitformac, macos, tvos);

AS_EXTERN API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(uikitformac, macos, tvos, watchos)
@interface ASCredentialProviderExtensionContext : NSExtensionContext

/*! @abstract Complete the request by providing the user selected credential.
 @param credential the credential that the user has selected.
 @param completionHandler optionally contains any work which the extension may need to perform after the request has been completed,
 as a background-priority task. The `expired` parameter will be YES if the system decides to prematurely terminate a previous
 non-expiration invocation of the completionHandler.
 @discussion Calling this method will eventually dismiss the associated view controller.
 */
- (void)completeRequestWithSelectedCredential:(ASPasswordCredential *)credential completionHandler:(void(^ _Nullable)(BOOL expired))completionHandler;

/*! @abstract Complete the request to configure the extension.
 @discussion Calling this method will eventually dismiss the associated view controller.
 */
- (void)completeExtensionConfigurationRequest;

- (void)completeRequestReturningItems:(nullable NSArray *)items completionHandler:(void (^ _Nullable)(BOOL))completionHandler NS_UNAVAILABLE;

/*! @abstract Cancels the request.
 @param error error's domain should be ASExtensionErrorDomain and the code should be a value of type ASExtensionErrorCode.
 @discussion The extension should call this method when the user cancels the action or a failure occurs.
 */
- (void)cancelRequestWithError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASAuthorizationProvider.h
//
//  ASAuthorizationProvider.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@protocol ASAuthorizationProvider <NSObject>

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASAuthorization.h
//
//  ASAuthorization.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * ASAuthorizationScope API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0)) NS_SWIFT_NAME(ASAuthorization.Scope) NS_TYPED_EXTENSIBLE_ENUM;

AS_EXTERN ASAuthorizationScope const ASAuthorizationScopeFullName API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));
AS_EXTERN ASAuthorizationScope const ASAuthorizationScopeEmail API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));

@protocol ASAuthorizationProvider, ASAuthorizationCredential;

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASAuthorization : NSObject

/*! @abstract Provider which was used to generate this authorization response.
 */
@property (nonatomic, readonly, strong) id <ASAuthorizationProvider> provider;

/*! @abstract The credential that was returned by the authorization provider. Authorization provider type should be used to determine how to introspect the credential.
 */
@property (nonatomic, readonly, strong) id <ASAuthorizationCredential> credential;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASWebAuthenticationSessionWebBrowserSessionHandling.h
//
//  ASWebAuthenticationSessionWebBrowserSessionHandling.h
//  AuthenticationServices Framework
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>

@class ASWebAuthenticationSessionRequest;

AS_EXTERN API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos)
@protocol ASWebAuthenticationSessionWebBrowserSessionHandling
- (void)beginHandlingWebAuthenticationSessionRequest:(ASWebAuthenticationSessionRequest *)request;
- (void)cancelWebAuthenticationSessionRequest:(ASWebAuthenticationSessionRequest *)request;
@end
// ==========  AuthenticationServices.framework/Headers/ASCredentialIdentityStore.h
//
//  ASCredentialIdentityStore.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ASCredentialIdentityStoreState;
@class ASPasswordCredentialIdentity;

AS_EXTERN API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(uikitformac, macos, tvos, watchos)
NSErrorDomain const ASCredentialIdentityStoreErrorDomain;

/*! @enum ASCredentialIdentityStoreErrorCode
 @constant ASCredentialIdentityStoreErrorCodeInternalError The operation failed due to an internal error.
 @constant ASCredentialIdentityStoreErrorCodeStoreDisabled The operation failed because the credential identity store is disabled.
 @constant ASCredentialIdentityStoreErrorCodeStoreBusy The operation failed because the credential identity store is busy. Attempt the operation again at a later time.
 */
typedef NS_ERROR_ENUM(ASCredentialIdentityStoreErrorDomain, ASCredentialIdentityStoreErrorCode) {
    ASCredentialIdentityStoreErrorCodeInternalError = 0,
    ASCredentialIdentityStoreErrorCodeStoreDisabled = 1,
    ASCredentialIdentityStoreErrorCodeStoreBusy = 2,
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(uikitformac, macos, tvos, watchos);

AS_EXTERN API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(uikitformac, macos, tvos, watchos)
@interface ASCredentialIdentityStore : NSObject

@property (class, nonatomic, readonly) ASCredentialIdentityStore *sharedStore;

- (instancetype)init NS_UNAVAILABLE;

/*! @abstract Get the state of the credential identity store.
 @param completion completion handler to be called with the current state of the store.
 @discussion Call this method to find out the current state of the store before attempting to call other store methods.
 Use the provided ASCredentialIdentityStoreState to find out if the store is enabled and whether it supports incremental
 updates.
 */
- (void)getCredentialIdentityStoreStateWithCompletion:(void (^)(ASCredentialIdentityStoreState *state))completion;

/*! @abstract Save the given credential identities to the store.
 @param credentialIdentities array of ASPasswordCredentialIdentity objects to save to the store.
 @param completion optional completion handler to be called after adding the credential identities.
 If the operation fails, an error with domain ASCredentialIdentityStoreErrorDomain will be provided
 and none of the objects in credentialIdentities will be saved to the store.
 @discussion If the store supports incremental updates, call this method to add new credential
 identities since the last time the store was updated. Otherwise, call this method to pass all credential
 identities.
 If some credential identities in credentialIdentities already exist in the store, they will be replaced by
 those from credentialIdentities.
 */
- (void)saveCredentialIdentities:(NSArray<ASPasswordCredentialIdentity *> *)credentialIdentities completion:(void (^ _Nullable)(BOOL success, NSError * _Nullable error))completion;

/*! @abstract Remove the given credential identities from the store.
 @param credentialIdentities array of ASPasswordCredentialIdentity objects to remove from the store.
 @param completion optional completion handler to be called after removing the credential identities.
 If the operation fails, an error with domain ASCredentialIdentityStoreErrorDomain will be provided
 and none of the objects in credentialIdentities will be removed from the store.
 @discussion Use this method only if the store supports incremental updates to remove previously added
 credentials to the store.
 */
- (void)removeCredentialIdentities:(NSArray<ASPasswordCredentialIdentity *> *)credentialIdentities completion:(void (^ _Nullable)(BOOL success, NSError * _Nullable error))completion;

/*! @abstract Remove all existing credential identities from the store.
 @param completion optional completion handler to be called after removing all existing credential identities.
 If the operation fails, an error with domain ASCredentialIdentityStoreErrorDomain will be provided and none of
 the existing credential identities will be removed from the store.
 */
- (void)removeAllCredentialIdentitiesWithCompletion:(void (^ _Nullable)(BOOL success, NSError * _Nullable error))completion;

/*! @abstract Replace existing credential identities with new credential identities.
 @param newCredentialIdentities array of new credential identity objects to replace the old ones.
 @param completion an optional completion block to be called after the operation is finished.
 @discussion This method will delete all existing credential identities that are persisted in the
 store and replace them with the provided array of credential identities. If the operation fails, an
 error with domain ASCredentialIdentityStoreErrorDomain will be provided and none of the new credential
 identities will be saved.
 */
- (void)replaceCredentialIdentitiesWithIdentities:(NSArray<ASPasswordCredentialIdentity *> *)newCredentialIdentities completion:(void (^ _Nullable)(BOOL success, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASAuthorizationAppleIDButton.h
//
//  ASAuthorizationAppleIDButton.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, ASAuthorizationAppleIDButtonType) {
    ASAuthorizationAppleIDButtonTypeDefault = 0,
    ASAuthorizationAppleIDButtonTypeSignUp = 1,
    ASAuthorizationAppleIDButtonTypeContinue = 2
} NS_SWIFT_NAME(ButtonType) API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos);


typedef NS_ENUM(NSInteger, ASAuthorizationAppleIDButtonStyle) {
    ASAuthorizationAppleIDButtonStyleWhite = 0,
    ASAuthorizationAppleIDButtonStyleWhiteOutline = 1,
    ASAuthorizationAppleIDButtonStyleBlack = 2
} NS_SWIFT_NAME(ButtonStyle) API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos);


NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos)
@interface ASAuthorizationAppleIDButton : UIControl

+ (instancetype)buttonWithType:(ASAuthorizationAppleIDButtonType)type style:(ASAuthorizationAppleIDButtonStyle)style;

- (instancetype)initWithAuthorizationButtonType:(ASAuthorizationAppleIDButtonType)type authorizationButtonStyle:(ASAuthorizationAppleIDButtonStyle)style NS_DESIGNATED_INITIALIZER;

/*! @abstract Set a custom corner radius to be used by this button.
 */
@property (nonatomic, assign) IBInspectable CGFloat cornerRadius;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASAuthorizationRequest.h
//
//  ASAuthorizationRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorizationProvider.h>
#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASAuthorizationRequest : NSObject <NSCopying, NSSecureCoding>

/*! @abstract The provider object that is being used to service this request
 */
@property (nonatomic, readonly, strong) id <ASAuthorizationProvider> provider;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASFoundation.h
//
//  ASFoundation.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#ifdef __cplusplus
#define AS_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define AS_EXTERN extern __attribute__((visibility ("default")))
#endif

#if __has_include(<UIKit/UIKit.h>)
#import <UIKit/UIKit.h>
#if __has_include(<UIKit/UIWindow.h>)
typedef UIWindow * ASPresentationAnchor;
#endif
#elif __has_include(<AppKit/AppKit.h>)
#import <AppKit/AppKit.h>
typedef NSWindow * ASPresentationAnchor;
#endif
// ==========  AuthenticationServices.framework/Headers/ASAuthorizationAppleIDCredential.h
//
//  ASAuthorizationAppleIDCredential.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorization.h>
#import <AuthenticationServices/ASAuthorizationCredential.h>
#import <Foundation/Foundation.h>

/*! @enum ASUserDetectionStatus
 @constant ASUserDetectionStatusUnsupported Not supported on current platform, ignore the value
 @constant ASUserDetectionStatusUnknown We could not determine the value.  New users in the ecosystem will get this value as well, so you should not blacklist but instead treat these users as any new user through standard email sign up flows
 @constant ASUserDetectionStatusLikelyReal A hint that we have high confidence that the user is real.
 */
typedef NS_ENUM(NSInteger, ASUserDetectionStatus) {
    ASUserDetectionStatusUnsupported,
    ASUserDetectionStatusUnknown,
    ASUserDetectionStatusLikelyReal,
};

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASAuthorizationAppleIDCredential : NSObject <ASAuthorizationCredential>

/*! @abstract An opaque user ID associated with the AppleID used for the sign in. This identifier will be stable across the 'developer team', it can later be used as an input to @see ASAuthorizationRequest to request user contact information.

 The identifier will remain stable as long as the user is connected with the requesting client.  The value may change upon user disconnecting from the identity provider.
 */
@property (nonatomic, readonly, copy) NSString *user;

/*! @abstract A copy of the state value that was passed to ASAuthorizationRequest.
 */
@property (nonatomic, readonly, copy, nullable) NSString *state;

/*! @abstract This value will contain a list of scopes for which the user provided authorization.  These may contain a subset of the requested scopes on @see ASAuthorizationAppleIDRequest.  The application should query this value to identify which scopes were returned as it maybe different from ones requested.
 */
@property (nonatomic, readonly, copy) NSArray<ASAuthorizationScope> *authorizedScopes;

/*! @abstract A short-lived, one-time valid token that provides proof of authorization to the server component of the app. The authorization code is bound to the specific transaction using the state attribute passed in the authorization request. The server component of the app can validate the code using Apple’s identity service endpoint provided for this purpose.
 */
@property (nonatomic, readonly, copy, nullable) NSData *authorizationCode;

/*! @abstract A JSON Web Token (JWT) used to communicate information about the identity of the user in a secure way to the app. The ID token will contain the following information: Issuer Identifier, Subject Identifier, Audience, Expiry Time and Issuance Time signed by Apple's identity service.
 */
@property (nonatomic, readonly, copy, nullable) NSData *identityToken;

/*! @abstract An optional email shared by the user.  This field is populated with a value that the user authorized.
 */
@property (nonatomic, readonly, copy, nullable) NSString *email;

/*! @abstract An optional full name shared by the user.  This field is populated with a value that the user authorized.
 */
@property (nonatomic, readonly, copy, nullable) NSPersonNameComponents *fullName;

/*! @abstract Check this property for a hint as to whether the current user is a "real user".  @see ASUserDetectionStatus for guidelines on handling each status
 */
@property (nonatomic, readonly) ASUserDetectionStatus realUserStatus;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASCredentialProviderViewController.h
//
//  ASCredentialListProviderViewController.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASCredentialProviderExtensionContext.h>
#import <AuthenticationServices/ASCredentialServiceIdentifier.h>
#import <AuthenticationServices/ASFoundation.h>
#import <AuthenticationServices/ASPasswordCredentialIdentity.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(uikitformac, macos, tvos, watchos)
@interface ASCredentialProviderViewController : UIViewController

@property (nonatomic, readonly, strong) ASCredentialProviderExtensionContext *extensionContext;

/*! @abstract Prepare the view controller to show a list of credentials.
 @param serviceIdentifiers the array of service identifiers.
 @discussion This method is called by the system to prepare the extension's view controller to present the list of credentials.
 A service identifier array is passed which can be used to filter or prioritize the credentials that closely match each service.
 The service identifier array could have zero or more items. If there are more than one item in the array, items with lower indexes
 represent more specific identifiers for which a credential is being requested. For example, the array could contain identifiers
 [m.example.com, example.com] with the first item representing the more specifc service that requires a credential.
 If the array of service identifiers is empty, it is expected that the credential list should still show credentials that the user can pick from.
 */
- (void)prepareCredentialListForServiceIdentifiers:(NSArray<ASCredentialServiceIdentifier *> *)serviceIdentifiers;

/*! @abstract Attempt to provide the user-requested credential without any user interaction.
 @param credentialIdentity the credential identity for which a credential should be provided.
 @discussion After the user selects a credential identity, the system may ask your extension to provide the credential without showing any
 user interface if possible to enhance the user experience. If your extension can accomplish this (for example, the user’s passwords database is
 still unlocked from a recent interaction), call -[ASCredentialProviderExtensionContext completeRequestWithSelectedCredential:completionHandler:]
 to provide the credential.
 If an error occurs, call -[ASCredentialProviderExtensionContext cancelRequestWithError:] and pass an error with domain
 ASExtensionErrorDomain and an appropriate error code from ASExtensionErrorCode.  For example, if your extension requires user interaction
 because the passwords database needs to be unlocked, pass an error with code ASExtensionErrorCodeUserInteractionRequired.
 @note When this method is called, your extension's view controller is not present on the screen. Do not attempt or expect to show any user
 interface in this method.
 */
- (void)provideCredentialWithoutUserInteractionForIdentity:(ASPasswordCredentialIdentity *)credentialIdentity;

/*! @abstract Prepare the view controller to show user interface for providing the user-requested credential.
 @param credentialIdentity the credential identity for which a credential should be provided.
 @discussion The system calls this method when your extension cannot provide the requested credential without user interaction.
 Set up the view controller for any user interaction required to provide the requested credential only. The user interaction should
 be limited in nature to operations required for providing the requested credential. An example is showing an authentication UI to
 unlock the user's passwords database.
 Call -[ASCredentialProviderExtensionContext completeRequestWithSelectedCredential:completionHandler:] to provide the credential.
 If an error occurs, call -[ASCredentialProviderExtensionContext cancelRequestWithError:] and pass an error with domain
 ASExtensionErrorDomain and an appropriate error code from ASExtensionErrorCode. For example, if the credential identity cannot
 be found in the database, pass an error with code ASExtensionErrorCodeCredentialIdentityNotFound.
 */
- (void)prepareInterfaceToProvideCredentialForIdentity:(ASPasswordCredentialIdentity *)credentialIdentity;

/*! @abstract Prepare the view controller to show user interface when the user enables your extension.
 @discussion The system calls this method after your extension is enabled by the user in Settings. You can
 use this method to give the user a chance to configure the extension or to provide credential identities
 to the system. After the configuration is done, call -[ASCredentialProviderExtensionContext completeExtensionConfigurationRequest].
 @note This method only gets called if your extension supports this functionality by specifying
 "ASCredentialProviderExtensionShowsConfigurationUI": YES in its extension attributes.
 */
- (void)prepareInterfaceForExtensionConfiguration;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASAuthorizationController.h
//
//  ASAuthorizationController.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ASAuthorization;
@class ASAuthorizationRequest;
@class ASAuthorizationController;

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@protocol ASAuthorizationControllerDelegate <NSObject>
@optional

- (void)authorizationController:(ASAuthorizationController *)controller didCompleteWithAuthorization:(ASAuthorization *)authorization NS_SWIFT_NAME(authorizationController(controller:didCompleteWithAuthorization:));
- (void)authorizationController:(ASAuthorizationController *)controller didCompleteWithError:(NSError *)error  NS_SWIFT_NAME(authorizationController(controller:didCompleteWithError:));

@end

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos)
@protocol ASAuthorizationControllerPresentationContextProviding <NSObject>
@required

#if !TARGET_OS_WATCH
/*! @abstract Return a view anchor that is most appropriate for athorization UI to be presented over.  This view will be used as a hint if a credential provider requires user interaction.
 */
- (ASPresentationAnchor)presentationAnchorForAuthorizationController:(ASAuthorizationController *)controller;
#endif

@end


AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASAuthorizationController : NSObject

/*! @abstract Authorization requests that are being serviced by this controller
 */
@property (nonatomic, readonly, strong) NSArray<ASAuthorizationRequest *> *authorizationRequests;

/*! @abstract This delegate will be invoked upon completion of the authorization indicating success or failure.
 Delegate is required to receive the results of authorization.
 */
@property (nonatomic, weak, nullable) id <ASAuthorizationControllerDelegate> delegate;

/*! @abstract This delegate will be invoked upon needing a presentation context to display authorization UI.
 */
@property (nonatomic, weak, nullable) id <ASAuthorizationControllerPresentationContextProviding> presentationContextProvider API_UNAVAILABLE(watchos);

/*! @abstract Initialize the controller with authorization requests.
 
 @param authorizationRequests At least one request should be provided. Requests of same type maybe honored in first in first out order
 */
- (instancetype)initWithAuthorizationRequests:(NSArray<ASAuthorizationRequest *> *)authorizationRequests NS_DESIGNATED_INITIALIZER;

/*! @abstract Initiate the authorization flows.  Upon completion, the delegate will be called with either success or failure.
 Certain authorization flows may require a presentation context, the presentationContextProvider will be called to provider it.
 
 The instance will remain retained until the user completes the flow and the delegate callback is made.
 */
- (void)performRequests;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASAuthorizationAppleIDProvider.h
//
//  ASAuthorizationAppleIDProvider.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorizationAppleIDRequest.h>
#import <AuthenticationServices/ASAuthorizationProvider.h>
#import <AuthenticationServices/ASFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/*! @enum ASAuthorizationAppleIDProviderCredentialState
 @abstract Authorization state of an Apple ID credential.
 @constant ASAuthorizationAppleIDProviderCredentialAuthorized The Opaque user ID is in good state.
 @constant ASAuthorizationAppleIDProviderCredentialRevoked The Opaque user ID was revoked by the user.
 @constant ASAuthorizationAppleIDProviderCredentialNotFound The Opaque user ID was not found.
 */
typedef NS_ENUM(NSInteger, ASAuthorizationAppleIDProviderCredentialState) {
    ASAuthorizationAppleIDProviderCredentialRevoked,
    ASAuthorizationAppleIDProviderCredentialAuthorized,
    ASAuthorizationAppleIDProviderCredentialNotFound,
} NS_SWIFT_NAME(ASAuthorizationAppleIDProvider.CredentialState) API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));

AS_EXTERN NSNotificationName const ASAuthorizationAppleIDProviderCredentialRevokedNotification API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASAuthorizationAppleIDProvider : NSObject <ASAuthorizationProvider>

/*!
 @abstract This method initializes and returns an instance of @see ASAuthorizationAppleIDRequest to be serviced by @see ASAuthorizationController.
 */
- (ASAuthorizationAppleIDRequest *)createRequest;

/*!
 @abstract This method can be used to get the current state of an opaque user ID previously given.
 @param userID Opaque user identifier that will be checked for state.
 @param completion A completion block that will return one of 3 possible states @see ASAuthorizationAppleIDProviderCredentialState.
 
 @note If credentialState is @see ASAuthorizationAppleIDProviderCredentialNotFound, an error will also be passed in the completion block.
 */
- (void)getCredentialStateForUserID:(NSString *)userID completion:(void (^)(ASAuthorizationAppleIDProviderCredentialState credentialState, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASWebAuthenticationSession.h
//
//  ASWebAuthenticationSession.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol ASWebAuthenticationPresentationContextProviding;

AS_EXTERN API_AVAILABLE(ios(12.0), uikitformac(13.0), macos(10.15)) API_UNAVAILABLE(tvos, watchos)
NSErrorDomain const ASWebAuthenticationSessionErrorDomain;

/*! @enum ASWebAuthenticationSessionErrorCode
 @abstract Error code of the NSError object passed in by ASWebAuthenticationSessionCompletionHandler.
 @constant ASWebAuthenticationSessionErrorCodeCanceledLogin The user has canceled login by cancelling the
 alert asking for permission to log in to this app, or by dismissing the view controller for loading the
 authentication webpage.
 @constant ASWebAuthenticationSessionErrorCodePresentationContextNotProvided A valid presentationContextProvider
 was not found when -start was called. Ensure this property was not nil when -start was called.
 @constant ASWebAuthenticationSessionErrorCodePresentationContextInvalid The presentation context returned
 was not elligible to show the authentication UI. For iOS, validate that the UIWindow is in a foreground scene.
 */
typedef NS_ERROR_ENUM(ASWebAuthenticationSessionErrorDomain, ASWebAuthenticationSessionErrorCode) {
    ASWebAuthenticationSessionErrorCodeCanceledLogin = 1,
    ASWebAuthenticationSessionErrorCodePresentationContextNotProvided API_AVAILABLE(ios(13.0), macos(10.15)) = 2,
    ASWebAuthenticationSessionErrorCodePresentationContextInvalid API_AVAILABLE(ios(13.0), macos(10.15)) = 3,
} API_AVAILABLE(ios(12.0), uikitformac(13.0), macos(10.15)) API_UNAVAILABLE(tvos, watchos);

typedef void (^ASWebAuthenticationSessionCompletionHandler)(NSURL *_Nullable callbackURL, NSError *_Nullable error) NS_SWIFT_NAME(ASWebAuthenticationSession.CompletionHandler);

/*!
 @class ASWebAuthenticationSession
 An ASWebAuthenticationSession object can be used to authenticate a user with a web service, even if the web service is run
 by a third party. ASWebAuthenticationSession puts the user in control of whether they want to use their existing logged-in
 session from Safari. The app provides a URL that points to the authentication webpage. The page will be loaded in a secure
 view controller. From the webpage, the user can authenticate herself and grant access to the app.
 On completion, the service will send a callback URL with an authentication token, and this URL will be passed to the app by
 ASWebAuthenticationSessionCompletionHandler.

 The callback URL usually has a custom URL scheme. For the app to receive the callback URL, it needs to either register the
 custom URL scheme in its Info.plist, or set the scheme to callbackURLScheme argument in the initializer.

 If the user has already logged into the web service in Safari or other apps via ASWebAuthenticationSession, it is possible to
 share the existing login information. An alert will be presented to get the user's consent for sharing their existing login
 information. If the user cancels the alert, the session will be canceled, and the completion handler will be called with
 the error code ASWebAuthenticationSessionErrorCodeCanceledLogin.

 If the user taps Cancel when showing the login webpage for the web service, the session will be canceled, and the completion
 handler will be called with the error code ASWebAuthenticationSessionErrorCodeCanceledLogin.

 The app can cancel the session by calling -[ASWebAuthenticationSession cancel]. This will also dismiss the view controller that
 is showing the web service's login page.
 */
AS_EXTERN API_AVAILABLE(ios(12.0), uikitformac(13.0), macos(10.15)) API_UNAVAILABLE(tvos, watchos)
@interface ASWebAuthenticationSession : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*! @abstract Returns an ASWebAuthenticationSession object.
 @param URL the initial URL pointing to the authentication webpage. Only supports URLs with http:// or https:// schemes.
 @param callbackURLScheme the custom URL scheme that the app expects in the callback URL.
 @param completionHandler the completion handler which is called when the session is completed successfully or canceled by user.
 */
- (instancetype)initWithURL:(NSURL *)URL callbackURLScheme:(nullable NSString *)callbackURLScheme completionHandler:(ASWebAuthenticationSessionCompletionHandler)completionHandler;

/*! @abstract Provides context to target where in an application's UI the authorization view should be shown. A provider
 must be set prior to calling -start, otherwise the authorization view cannot be displayed. If deploying to iOS prior to
 13.0, the desired window is inferred by the application's key window.
 */
@property (nonatomic, weak) id <ASWebAuthenticationPresentationContextProviding> presentationContextProvider API_AVAILABLE(ios(13.0), macos(10.15));

/*! @abstract Indicates whether this session should ask the browser for an ephemeral session.
 @discussion Ephemeral web browser sessions do not not share cookies or other browsing data with a user's normal browser session.
 This value is NO by default. Setting this property after calling -[ASWebAuthenticationSession start] has no effect.
 */
@property (nonatomic) BOOL prefersEphemeralWebBrowserSession API_AVAILABLE(ios(13.0), macos(10.15));

/*! @abstract Starts the ASWebAuthenticationSession instance after it is instantiated.
 @discussion start can only be called once for an ASWebAuthenticationSession instance. This also means calling start on a
 canceled session will fail.
 @result Returns YES if the session starts successfully.
 */
- (BOOL)start;

/*! @abstract Cancel an ASWebAuthenticationSession. If the view controller is already presented to load the webpage for
 authentication, it will be dismissed. Calling cancel on an already canceled session will have no effect.
 */
- (void)cancel;

@end

/*! @abstract Provides context to target where in an application's UI the authorization view should be shown.
 */
API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(tvos, watchos)
@protocol ASWebAuthenticationPresentationContextProviding <NSObject>

/*! @abstract Return the ASPresentationAnchor in the closest proximity to where a user interacted with your app to trigger
 authentication. If starting an ASWebAuthenticationSession on first launch, use the application's main window.
 @param session The session requesting a presentation anchor.
 @result The ASPresentationAnchor most closely associated with the UI used to trigger authentication.
 */
- (ASPresentationAnchor)presentationAnchorForWebAuthenticationSession:(ASWebAuthenticationSession *)session;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASAuthorizationSingleSignOnProvider.h
//
//  ASAuthorizationSingleSignOnProvider.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <AuthenticationServices/ASAuthorizationProvider.h>
#import <AuthenticationServices/ASAuthorizationSingleSignOnRequest.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(tvos, watchos)
@interface ASAuthorizationSingleSignOnProvider : NSObject <ASAuthorizationProvider>

/*! @abstract To get the right extension the identity provider main URL has to be provided. The URL is even part of the extension using assosiated domains mechanism or can be configured by MDM profile.
 */
+ (instancetype)authorizationProviderWithIdentityProviderURL:(NSURL *)url NS_SWIFT_NAME(init(identityProvider:));

- (ASAuthorizationSingleSignOnRequest *)createRequest;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, readonly) NSURL *url;

/*! @abstract Returns YES if the configured provider is capable of performing authorization within a given configuration.
 */
@property (nonatomic, readonly, assign) BOOL canPerformAuthorization;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASAuthorizationError.h
//
//  ASAuthorizationError.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN NSErrorDomain const ASAuthorizationErrorDomain API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));

typedef NS_ERROR_ENUM(ASAuthorizationErrorDomain, ASAuthorizationError) {
    ASAuthorizationErrorUnknown = 1000,
    ASAuthorizationErrorCanceled = 1001,
    ASAuthorizationErrorInvalidResponse = 1002,
    ASAuthorizationErrorNotHandled = 1003,
    ASAuthorizationErrorFailed = 1004,
} API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASAuthorizationAppleIDRequest.h
//
//  ASAuthorizationAppleIDRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorization.h>
#import <AuthenticationServices/ASAuthorizationOpenIDRequest.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASAuthorizationAppleIDRequest : ASAuthorizationOpenIDRequest

/*! @abstract If you have been previously vended a 'user' value through ASAuthorization response, you may set it here to provide additional context to identity provider.
 
 @see ASAuthorizationAppleIDCredential doc for the description of this property in context of response.
 */
@property (nonatomic, copy, nullable) NSString *user;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASCredentialIdentityStoreState.h
//
//  ASCredentialIdentityStoreState.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(uikitformac, macos, tvos, watchos)
@interface ASCredentialIdentityStoreState : NSObject

/*! @abstract Get the enabled state of the credential identity store.
 @result YES if the credential identity store is enabled.
 @dicussion You can only modify the credential identity store when it is enabled.
 */
@property (nonatomic, readonly, getter=isEnabled) BOOL enabled;

/*! @abstract Get whether the credential identity store supports incremental updates.
 @result YES if the credential identity store supports incremental updates.
 @discussion You should examine the value returned by this property to find out if
 the credential identity store can accept incremental updates. If incremental updates
 are supported, you can update the credential identity store with only the new changes
 since the last time it was updated. Otherwise, you should update the credential identity
 store by adding all credential identities.
 */
@property (nonatomic, readonly) BOOL supportsIncrementalUpdates;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASWebAuthenticationSessionWebBrowserSessionManager.h
//
//  ASWebAuthenticationSessionWebBrowserSessionManager.h
//  AuthenticationServices Framework
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import "ASWebAuthenticationSessionWebBrowserSessionHandling.h"
#import "ASFoundation.h"

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos)
@interface ASWebAuthenticationSessionWebBrowserSessionManager : NSObject

@property (class, readonly, nonatomic) ASWebAuthenticationSessionWebBrowserSessionManager *sharedManager;
@property (nonatomic) id<ASWebAuthenticationSessionWebBrowserSessionHandling> sessionHandler;
@property (nonatomic, readonly) BOOL wasLaunchedByAuthenticationServices;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASWebAuthenticationSessionRequest.h
//
//  ASWebAuthenticationSessionRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ASWebAuthenticationSessionRequest;

AS_EXTERN API_AVAILABLE(uikitformac(13.0), macos(10.15)) API_UNAVAILABLE(ios, tvos)
@protocol ASWebAuthenticationSessionRequestDelegate <NSObject>
@optional
- (void)authenticationSessionRequest:(ASWebAuthenticationSessionRequest *)authenticationSessionRequest didCompleteWithCallbackURL:(NSURL *)callbackURL;
- (void)authenticationSessionRequest:(ASWebAuthenticationSessionRequest *)authenticationSessionRequest didCancelWithError:(NSError *)error;
@end

AS_EXTERN API_AVAILABLE(uikitformac(13.0), macos(10.15)) API_UNAVAILABLE(ios, tvos)
@interface ASWebAuthenticationSessionRequest : NSObject <NSSecureCoding, NSCopying>

@property (readonly, nonatomic) NSUUID *UUID;
@property (readonly, nonatomic) NSURL *URL;
@property (nullable, readonly, nonatomic, copy) NSString *callbackURLScheme;
@property (readonly, nonatomic) BOOL shouldUseEphemeralSession;
@property (nullable, nonatomic, weak) id<ASWebAuthenticationSessionRequestDelegate> delegate;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (void)cancelWithError:(NSError *)error;
- (void)completeWithCallbackURL:(NSURL *)url;
@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASAuthorizationPasswordRequest.h
//
//  ASAuthorizationPasswordRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorizationRequest.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASAuthorizationPasswordRequest : ASAuthorizationRequest

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASAuthorizationSingleSignOnCredential.h
//
//  ASAuthorizationSingleSignOnCredential.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorization.h>
#import <AuthenticationServices/ASAuthorizationCredential.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(tvos, watchos)
@interface ASAuthorizationSingleSignOnCredential : NSObject <ASAuthorizationCredential>

/*! @abstract A state returned from the AuthenticationServices extension.
 */
@property (nonatomic, readonly, copy, nullable) NSString *state;

/*! @abstract An access token used to access other systems with the authorized scopes.
 */
@property (nonatomic, readonly, copy, nullable) NSData *accessToken;

/*! @abstract A JSON Web Token (JWT) used to communicate information about the identity of the user in a secure way to the app.
 */
@property (nonatomic, readonly, copy, nullable) NSData *identityToken;

/*! @abstract This value will contain a list of scopes for which the user provided authorization.  These may contain a subset of the requested scopes on @see ASAuthorizationOpenIDRequest.  The application should query this value to identify which scopes were returned as it maybe different from ones requested.
 */
@property (nonatomic, readonly, copy) NSArray<ASAuthorizationScope> *authorizedScopes;

/*! @abstract The complete AuthenticationServices extension response with the additional outputs used by the specific technology used by the Authorization Server instance and AuthenticationServices Extension.
 @note for some operations all properties can be null and the response will indicate just successful result of the operation.
 */
@property (nonatomic, copy, readonly, nullable) NSHTTPURLResponse *authenticatedResponse;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASAuthorizationPasswordProvider.h
//
//  ASAuthorizationPasswordProvider.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorizationPasswordRequest.h>
#import <AuthenticationServices/ASAuthorizationProvider.h>
#import <AuthenticationServices/ASFoundation.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASAuthorizationPasswordProvider : NSObject <ASAuthorizationProvider>

- (ASAuthorizationPasswordRequest *)createRequest;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/AuthenticationServices.h
//
//  AuthenticationServices.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <AuthenticationServices/ASWebAuthenticationSession.h>
#import <AuthenticationServices/ASWebAuthenticationSessionRequest.h>
#import <AuthenticationServices/ASWebAuthenticationSessionWebBrowserSessionHandling.h>
#import <AuthenticationServices/ASWebAuthenticationSessionWebBrowserSessionManager.h>

#import <AuthenticationServices/ASCredentialIdentityStore.h>
#import <AuthenticationServices/ASCredentialIdentityStoreState.h>
#import <AuthenticationServices/ASCredentialProviderExtensionContext.h>
#import <AuthenticationServices/ASCredentialServiceIdentifier.h>
#import <AuthenticationServices/ASPasswordCredential.h>
#import <AuthenticationServices/ASPasswordCredentialIdentity.h>

#import <AuthenticationServices/ASAuthorization.h>
#import <AuthenticationServices/ASAuthorizationAppleIDCredential.h>
#import <AuthenticationServices/ASAuthorizationAppleIDProvider.h>
#import <AuthenticationServices/ASAuthorizationAppleIDRequest.h>
#import <AuthenticationServices/ASAuthorizationController.h>
#import <AuthenticationServices/ASAuthorizationCredential.h>
#import <AuthenticationServices/ASAuthorizationError.h>
#import <AuthenticationServices/ASAuthorizationOpenIDRequest.h>
#import <AuthenticationServices/ASAuthorizationPasswordProvider.h>
#import <AuthenticationServices/ASAuthorizationProvider.h>
#import <AuthenticationServices/ASAuthorizationRequest.h>
#import <AuthenticationServices/ASAuthorizationSingleSignOnCredential.h>
#import <AuthenticationServices/ASAuthorizationSingleSignOnProvider.h>
#import <AuthenticationServices/ASAuthorizationSingleSignOnRequest.h>
#import <AuthenticationServices/ASAuthorizationProviderExtensionAuthorizationRequest.h>

#if TARGET_OS_IOS && !(defined(TARGET_OS_UIKITFORMAC) && TARGET_OS_UIKITFORMAC)
#import <AuthenticationServices/ASCredentialProviderViewController.h>
#endif

#if !TARGET_OS_OSX
#import <AuthenticationServices/ASAuthorizationAppleIDButton.h>
#endif
// ==========  AuthenticationServices.framework/Headers/ASAuthorizationSingleSignOnRequest.h
//
//  ASAuthorizationSingleSignOnRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorizationOpenIDRequest.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15), uikitformac(13.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASAuthorizationSingleSignOnRequest : ASAuthorizationOpenIDRequest

/*! @abstract Parameters required by the specific Authorization Server which should be used by the selected Authorization Services extension for authorization.
 */
@property(nonatomic, copy) NSArray<NSURLQueryItem *> *authorizationOptions;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASPasswordCredentialIdentity.h
//
//  ASPasswordCredentialIdentity.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ASCredentialServiceIdentifier;

/*! @class ASPasswordCredentialIdentity
 An ASPasswordCredentialIdentity is used to describe an identity that can use a service upon successful password based authentication.
 Use this class to save entries into ASCredentialIdentityStore.
 */
AS_EXTERN API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(uikitformac, macos, tvos, watchos)
@interface ASPasswordCredentialIdentity : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

/*! @abstract Initializes an instance of ASPasswordCredentialIdentity.
 @param serviceIdentifier the service identifier for which this credential identity is valid.
 @param user the user that can authenticate into the service indicated by the serviceIdentifier.
 @param recordIdentifier an optional string to uniquely identify this record in your local database.
 */
- (instancetype)initWithServiceIdentifier:(ASCredentialServiceIdentifier *)serviceIdentifier user:(NSString *)user recordIdentifier:(nullable NSString *)recordIdentifier NS_DESIGNATED_INITIALIZER;

/*! @abstract Creates and initializes an instance of ASPasswordCredentialIdentity.
 @param serviceIdentifier the service identifier for which this credential identity is valid.
 @param user the user that can authenticate into the service indicated by the serviceIdentifier.
 @param recordIdentifier an optional string to uniquely identify this record in your local database.
 */
+ (instancetype)identityWithServiceIdentifier:(ASCredentialServiceIdentifier *)serviceIdentifier user:(NSString *)user recordIdentifier:(nullable NSString *)recordIdentifier;

/*! @abstract Get the service identifier.
 @result The service identifier for this credential identity.
 */
@property (nonatomic, readonly, strong) ASCredentialServiceIdentifier *serviceIdentifier;

/*! @abstract Get the user.
 @result The user string.
 */
@property (nonatomic, readonly, copy) NSString *user;

/*! @abstract Get the record identifier.
 @result The record identifier.
 @discussion You can utilize the record identifier to uniquely identify the credential identity in your local database.
 */
@property (nonatomic, readonly, copy, nullable) NSString *recordIdentifier;

/*! @abstract Get or set the rank of the credential identity object.
 @discussion The system may utilize the rank to decide which credential identity precedes the other
 if two identities have the same service identifier. A credential identity with a larger rank value
 precedes one with a smaller value if both credential identities have the same service identifier.
 The default value of this property is 0.
 */
@property (nonatomic) NSInteger rank;

@end

NS_ASSUME_NONNULL_END
// ==========  AuthenticationServices.framework/Headers/ASPasswordCredential.h
//
//  ASPasswordCredential.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <AuthenticationServices/ASAuthorizationCredential.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(12.0), macos(10.15), tvos(13.0), watchos(6.0))
@interface ASPasswordCredential : NSObject <ASAuthorizationCredential>

/*! @abstract Initializes an ASPasswordCredential object.
 @param user the user.
 @param password the password.
 */
- (instancetype)initWithUser:(NSString *)user password:(NSString *)password;

/*! @abstract Creates and initializes a new ASPasswordCredential object.
 @param user the user.
 @param password the password.
 */
+ (instancetype)credentialWithUser:(NSString *)user password:(NSString *)password;

/*! @abstract The user name of this credential.
 @result The user string.
 */
@property (nonatomic, copy, readonly) NSString *user;

/*! @abstract The password of this credential.
 @result The password string.
 */
@property (nonatomic, copy, readonly) NSString *password;

@end

NS_ASSUME_NONNULL_END
