// ==========  Accounts.framework/Headers/AccountsDefines.h
//
//  AccountsDefines.h
//  Accounts
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//


#ifdef __cplusplus
#define ACCOUNTS_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define ACCOUNTS_EXTERN extern __attribute__((visibility ("default")))
#endif
// ==========  Accounts.framework/Headers/ACError.h
//
//  ACError.h
//  Accounts
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accounts/AccountsDefines.h>

ACCOUNTS_EXTERN NSString * const ACErrorDomain API_AVAILABLE(ios(5.0), macos(10.8));

typedef enum ACErrorCode {
    ACErrorUnknown = 1,
    ACErrorAccountMissingRequiredProperty,  // Account wasn't saved because it is missing a required property.
    ACErrorAccountAuthenticationFailed,     // Account wasn't saved because authentication of the supplied credential failed.
    ACErrorAccountTypeInvalid,              // Account wasn't saved because the account type is invalid.
    ACErrorAccountAlreadyExists,            // Account wasn't added because it already exists.
    ACErrorAccountNotFound,                 // Account wasn't deleted because it could not be found.
    ACErrorPermissionDenied,                // The operation didn't complete because the user denied permission.
    ACErrorAccessInfoInvalid,               // The client's access info dictionary has incorrect or missing values.
    ACErrorClientPermissionDenied,          // Your client does not have access to the requested data.
    ACErrorAccessDeniedByProtectionPolicy,  // Due to the current protection policy in effect, we couldn't fetch a credential
    ACErrorCredentialNotFound,              // Yo, I tried to find your credential, but it must have run off!
    ACErrorFetchCredentialFailed,           // Something bad happened on the way to the keychain
    ACErrorStoreCredentialFailed,           // Unable to store credential
    ACErrorRemoveCredentialFailed,          // Unable to remove credential
    ACErrorUpdatingNonexistentAccount,      // Account save failed because the account being updated has been removed.
    ACErrorInvalidClientBundleID,           // The client making the request does not have a valid bundle ID.
    ACErrorDeniedByPlugin,                  // A plugin prevented the expected action to occur.
    ACErrorCoreDataSaveFailed,              // Something broke below us when we tried to the CoreData store.
    ACErrorFailedSerializingAccountInfo,
    ACErrorInvalidCommand,
    ACErrorMissingTransportMessageID,
    ACErrorCredentialItemNotFound,          // Credential item wasn't saved because it could not be found.
    ACErrorCredentialItemNotExpired,        // Credential item wasn't removed because it has not yet expired.
} ACErrorCode;
// ==========  Accounts.framework/Headers/ACAccountCredential.h
//
//  ACAccountCredential.h
//  Accounts
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accounts/AccountsDefines.h>

// An existing credential may be provided when creating an account.
// For example, to create a system Twitter account using an existing OAuth token/secret pair:
//
// 1. Create the new account instance.
// 2. Set the account type.
// 3. Create an ACAccountCredential using your existing OAuth token/secret and set the account's credential property.
// 4. Save the account.
//
// The account will be validated and saved as a system account.

API_AVAILABLE(ios(5.0), macos(10.8))
@interface ACAccountCredential : NSObject

- (instancetype)initWithOAuthToken:(NSString *)token tokenSecret:(NSString *)secret;

- (instancetype)initWithOAuth2Token:(NSString *)token 
                       refreshToken:(NSString *)refreshToken
                         expiryDate:(NSDate *)expiryDate;

// This property is only valid for OAuth2 credentials
@property (copy, nonatomic) NSString *oauthToken;

@end
// ==========  Accounts.framework/Headers/Accounts.h
//
//  Accounts.h
//  Accounts
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <Accounts/AccountsDefines.h>
#import <Accounts/ACAccount.h>
#import <Accounts/ACAccountType.h>
#import <Accounts/ACAccountCredential.h>
#import <Accounts/ACAccountStore.h>
#import <Accounts/ACError.h>
// ==========  Accounts.framework/Headers/ACAccountType.h
//
//  ACAccountType.h
//  Accounts
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accounts/AccountsDefines.h>

// The identifiers for supported system account types are listed here:
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierTwitter API_DEPRECATED("Use Twitter SDK instead", ios(5.0, 11.0), macos(10.8, 10.13));
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierFacebook API_DEPRECATED("Use Facebook SDK instead", ios(6.0, 11.0), macos(10.8, 10.13));
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierSinaWeibo API_DEPRECATED("Use Sina Weibo SDK instead", ios(6.0, 11.0), macos(10.8, 10.13));
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierTencentWeibo API_DEPRECATED("Use Tencent Weibo SDK instead", ios(7.0, 11.0), macos(10.9, 10.13));
ACCOUNTS_EXTERN NSString * const ACAccountTypeIdentifierLinkedIn API_DEPRECATED("Use LinkedIn SDK instead", macos(10.9, 10.13)) API_UNAVAILABLE(ios);

// Options dictionary keys for Facebook access, for use with [ACAccountStore requestAccessToAccountsWithType:options:completion:]
ACCOUNTS_EXTERN NSString * const ACFacebookAppIdKey API_DEPRECATED("Use Facebook SDK instead", ios(6.0, 11.0), macos(10.8, 10.13)); // Your Facebook App ID, as it appears on the Facebook website.
ACCOUNTS_EXTERN NSString * const ACFacebookPermissionsKey API_DEPRECATED("Use Facebook SDK instead", ios(6.0, 11.0), macos(10.8, 10.13)); // An array of of the permissions you're requesting.
ACCOUNTS_EXTERN NSString * const ACFacebookAudienceKey API_DEPRECATED("Use Facebook SDK instead", ios(6.0, 11.0), macos(10.8, 10.13)); // Only required when posting permissions are requested.

// Options dictionary values for Facebook access, for use with [ACAccountStore requestAccessToAccountsWithType:options:completion:]
ACCOUNTS_EXTERN NSString * const ACFacebookAudienceEveryone API_DEPRECATED("Use Facebook SDK instead", ios(6.0, 11.0), macos(10.8, 10.13)); // Posts from your app are visible to everyone.
ACCOUNTS_EXTERN NSString * const ACFacebookAudienceFriends API_DEPRECATED("Use Facebook SDK instead", ios(6.0, 11.0), macos(10.8, 10.13)); // Posts are visible only to friends.
ACCOUNTS_EXTERN NSString * const ACFacebookAudienceOnlyMe API_DEPRECATED("Use Facebook SDK instead", ios(6.0, 11.0), macos(10.8, 10.13)); // Posts are visible to the user only.

// Options dictionary keys for LinkedIn access, for use with [ACAccountStore requestAccessToAccountsWithType:options:completion:]
ACCOUNTS_EXTERN NSString * const ACLinkedInAppIdKey API_DEPRECATED("Use LinkedIn SDK instead", macos(10.9, 10.13)) API_UNAVAILABLE(ios); // Your LinkedIn App ID (or API Key), as it appears on the LinkedIn website.
ACCOUNTS_EXTERN NSString * const ACLinkedInPermissionsKey API_DEPRECATED("Use LinkedIn SDK instead", macos(10.9, 10.13)) API_UNAVAILABLE(ios); // An array of of the LinkedIn permissions you're requesting.

ACCOUNTS_EXTERN NSString * const ACTencentWeiboAppIdKey API_DEPRECATED("Use Tencent Weibo SDK instead", ios(7.0, 11.0), macos(10.9, 10.13)); // Tencent App ID

// Each account has an associated account type, containing information relevant to all the accounts of that type.
// ACAccountType objects are obtained by using the [ACAccountStore accountTypeWithIdentifier:] method
// or accessing the accountType property for a particular account object. They may also be used to find
// all the accounts of a particular type using [ACAccountStore accountsWithAccountType:]

API_AVAILABLE(ios(5.0), macos(10.8))
@interface ACAccountType : NSObject

// A human readable description of the account type.
@property (readonly, nonatomic) NSString *accountTypeDescription;

// A unique identifier for the account type. Well known system account type identifiers are listed above.
@property (readonly, nonatomic) NSString *identifier;

// A boolean indicating whether the user has granted access to accounts of this type for your application.
@property (readonly, nonatomic) BOOL     accessGranted;

@end
// ==========  Accounts.framework/Headers/ACAccount.h
//
//  ACAccount.h
//  Accounts
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accounts/AccountsDefines.h>

@class ACAccountType, ACAccountCredential;

// The ACAccount class represents an account stored on the system.
// Accounts are created not bound to any store. Once an account is saved it belongs
// to the store it was saved into.

API_AVAILABLE(ios(5.0), macos(10.8))
@interface ACAccount : NSObject

// Creates a new account object with a specified account type.
- (instancetype)initWithAccountType:(ACAccountType *)type NS_DESIGNATED_INITIALIZER;

// This identifier can be used to look up the account using [ACAccountStore accountWithIdentifier:].
@property (readonly, weak, NS_NONATOMIC_IOSONLY) NSString      *identifier;

// Accounts are stored with a particular account type. All available accounts of a particular type
// can be looked up using [ACAccountStore accountsWithAccountType:]. When creating new accounts
// this property is required.
@property (strong, NS_NONATOMIC_IOSONLY)   ACAccountType       *accountType;

// A human readable description of the account.
// This property is only available to applications that have been granted access to the account by the user.
@property (copy, NS_NONATOMIC_IOSONLY)     NSString            *accountDescription;

// The username for the account. This property can be set and saved during account creation. The username is
// only available to applications that have been granted access to the account by the user.
@property (copy, NS_NONATOMIC_IOSONLY)     NSString            *username;

// For accounts that support it (currently only Facebook accounts), you can get the user's full name for display
// purposes without having to talk to the network.
@property (readonly, NS_NONATOMIC_IOSONLY)  NSString           *userFullName API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(macos);

// The credential for the account. This property can be set and saved during account creation. It is
// inaccessible once the account has been saved.
@property (strong, NS_NONATOMIC_IOSONLY)   ACAccountCredential *credential;

@end
// ==========  Accounts.framework/Headers/ACAccountStore.h
//
//  ACAccountStore.h
//  Accounts
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accounts/AccountsDefines.h>

typedef NS_ENUM(NSInteger, ACAccountCredentialRenewResult) {
    ACAccountCredentialRenewResultRenewed,  // A new credential was obtained and is now associated with the account.
    ACAccountCredentialRenewResultRejected, // Renewal failed because of a user-initiated action.
    ACAccountCredentialRenewResultFailed,   // A non-user-initiated cancel of the prompt. 
};

typedef void(^ACAccountStoreSaveCompletionHandler)(BOOL success, NSError *error);
typedef void(^ACAccountStoreRemoveCompletionHandler)(BOOL success, NSError *error);
typedef void(^ACAccountStoreRequestAccessCompletionHandler)(BOOL granted, NSError *error);
typedef void(^ACAccountStoreCredentialRenewalHandler)(ACAccountCredentialRenewResult renewResult, NSError *error);

@class ACAccount, ACAccountType;

// The ACAccountStore class provides an interface for accessing and manipulating
// accounts. You must create an ACAccountStore object to retrieve, add and delete
// accounts from the Accounts database.
//
// IMPORTANT NOTE: You MUST keep the account store around for as long as you have
// any objects fetched from that store if you expect other 'sub-fetches' to work,
// most notably being fetching credentials. If you really just want to open the
// store to grab credentials, just be sure to grab the credential object and then
// you can release the owning account and store, e.g.

API_AVAILABLE(ios(5.0), macos(10.8))
@interface ACAccountStore : NSObject

// An array of all the accounts in an account database
@property (readonly, weak, NS_NONATOMIC_IOSONLY) NSArray *accounts;

// Returns the account matching the given account identifier
- (ACAccount *)accountWithIdentifier:(NSString *)identifier;

// Returns the account type object matching the account type identifier. See
// ACAccountType.h for well known account type identifiers
- (ACAccountType *)accountTypeWithAccountTypeIdentifier:(NSString *)typeIdentifier;

// Returns the accounts matching a given account type.
- (NSArray *)accountsWithAccountType:(ACAccountType *)accountType;

// Saves the account to the account database. If the account is unauthenticated and the associated account
// type supports authentication, the system will attempt to authenticate with the credentials provided.
// Assuming a successful authentication, the account will be saved to the account store. The completion handler
// for this method is called on an arbitrary queue.
- (void)saveAccount:(ACAccount *)account withCompletionHandler:(ACAccountStoreSaveCompletionHandler)completionHandler;

// DEPRECATED: Please use requestAccessToAccountsWithType:options:completion: instead.
- (void)requestAccessToAccountsWithType:(ACAccountType *)accountType withCompletionHandler:(ACAccountStoreRequestAccessCompletionHandler)handler API_DEPRECATED_WITH_REPLACEMENT("-requestAccessToAccountsWithType:options:completion:", ios(5.0, 6.0)) API_UNAVAILABLE(macos);

// Obtains permission, if necessary, from the user to access protected properties, and utilize accounts
// of a particular type in protected operations, for example OAuth signing. The completion handler for 
// this method is called on an arbitrary queue.
// Certain account types (such as Facebook) require an options dictionary. A list of the required keys
// appears in ACAccountType.h. This method will throw an NSInvalidArgumentException if the options
// dictionary is not provided for such account types. Conversely, if the account type does not require
// an options dictionary, the options parameter must be nil.
- (void)requestAccessToAccountsWithType:(ACAccountType *)accountType options:(NSDictionary *)options completion:(ACAccountStoreRequestAccessCompletionHandler)completion;

// Call this if you discover that an ACAccount's credential is no longer valid.
// For Twitter and Sina Weibo accounts, this method will prompt the user to go to Settings to re-enter their password.
// For Facebook accounts, if your access token became invalid due to regular expiration, this method will obtain a new one.
// However, if the user has deauthorized your app, this renewal request will return ACAccountCredentialRenewResultRejected.
- (void)renewCredentialsForAccount:(ACAccount *)account completion:(ACAccountStoreCredentialRenewalHandler)completionHandler;

// Removes an account from the account store. The completion handler for this method is called on an arbitrary queue.
// This call will fail if you don't have sufficient rights to remove the account in question.
- (void)removeAccount:(ACAccount *)account withCompletionHandler:(ACAccountStoreRemoveCompletionHandler)completionHandler;

@end

// Notification name sent out when the database is changed by an external process, another account store
// in the same process or by calling saveAccount: or removeAccount: on a store you are managing. When this
// notification is received, you should consider all ACAccount instances you have to be invalid. Purge current
// instances of ACAccount and obtain new instances using the account store. You may need to deal with accounts
// being removed by an external process while you are using them.
ACCOUNTS_EXTERN NSString * const ACAccountStoreDidChangeNotification API_AVAILABLE(ios(5.0), macos(10.8));
