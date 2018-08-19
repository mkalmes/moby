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
} API_AVAILABLE(ios(12.0))  NS_SWIFT_NAME(ASCredentialServiceIdentifier.IdentifierType);

AS_EXTERN API_AVAILABLE(ios(12.0)) 
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

AS_EXTERN API_AVAILABLE(ios(12.0)) 
NSErrorDomain const ASExtensionErrorDomain;

typedef NS_ERROR_ENUM(ASExtensionErrorDomain, ASExtensionErrorCode) {
    ASExtensionErrorCodeFailed = 0,
    ASExtensionErrorCodeUserCanceled = 1,
    ASExtensionErrorCodeUserInteractionRequired = 100,
    ASExtensionErrorCodeCredentialIdentityNotFound = 101,
} API_AVAILABLE(ios(12.0)) ;

AS_EXTERN API_AVAILABLE(ios(12.0)) 
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

AS_EXTERN API_AVAILABLE(ios(12.0)) 
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
} API_AVAILABLE(ios(12.0)) ;

AS_EXTERN API_AVAILABLE(ios(12.0)) 
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

AS_EXTERN API_AVAILABLE(ios(12.0)) 
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

AS_EXTERN API_AVAILABLE(ios(12.0))
NSErrorDomain const ASWebAuthenticationSessionErrorDomain;

/*! @enum ASWebAuthenticationSessionErrorCode
 @abstract Error code of the NSError object passed in by ASWebAuthenticationSessionCompletionHandler.
 @constant ASWebAuthenticationSessionErrorCodeCanceledLogin The user has canceled login by cancelling the
 alert asking for permission to log in to this app, or by dismissing the view controller for loading the
 authentication webpage.
 */
typedef NS_ERROR_ENUM(ASWebAuthenticationSessionErrorDomain, ASWebAuthenticationSessionErrorCode) {
    ASWebAuthenticationSessionErrorCodeCanceledLogin = 1,
} API_AVAILABLE(ios(12.0));

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
AS_EXTERN API_AVAILABLE(ios(12.0))
@interface ASWebAuthenticationSession : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*! @abstract Returns an ASWebAuthenticationSession object.
 @param URL the initial URL pointing to the authentication webpage. Only supports URLs with http:// or https:// schemes.
 @param callbackURLScheme the custom URL scheme that the app expects in the callback URL.
 @param completionHandler the completion handler which is called when the session is completed successfully or canceled by user.
 */
- (instancetype)initWithURL:(NSURL *)URL callbackURLScheme:(nullable NSString *)callbackURLScheme completionHandler:(ASWebAuthenticationSessionCompletionHandler)completionHandler;

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

AS_EXTERN API_AVAILABLE(ios(12.0)) 
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
// ==========  AuthenticationServices.framework/Headers/AuthenticationServices.h
//
//  AuthenticationServices.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASCredentialIdentityStore.h>
#import <AuthenticationServices/ASCredentialIdentityStoreState.h>
#import <AuthenticationServices/ASCredentialProviderExtensionContext.h>
#import <AuthenticationServices/ASCredentialProviderViewController.h>
#import <AuthenticationServices/ASCredentialServiceIdentifier.h>
#import <AuthenticationServices/ASFoundation.h>
#import <AuthenticationServices/ASPasswordCredential.h>
#import <AuthenticationServices/ASPasswordCredentialIdentity.h>
#import <AuthenticationServices/ASWebAuthenticationSession.h>
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
AS_EXTERN API_AVAILABLE(ios(12.0)) 
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
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(12.0)) 
@interface ASPasswordCredential : NSObject <NSCopying, NSSecureCoding>

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
