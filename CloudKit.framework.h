// ==========  CloudKit.framework/Headers/CKDatabase.h
//
//  CKDatabase.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKSubscription.h>

@class CKDatabaseOperation, CKRecord, CKRecordID, CKRecordZone, CKRecordZoneID, CKQuery;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CKDatabaseScope) {
    CKDatabaseScopePublic = 1,
    CKDatabaseScopePrivate,
    CKDatabaseScopeShared,
} API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKDatabase : NSObject
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (void)addOperation:(CKDatabaseOperation *)operation;
@property (nonatomic, readonly, assign) CKDatabaseScope databaseScope API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));
@end

/*! @abstract Convenience APIs
 *
 *  @discussion These calls operate on a single item in the default zone and allow for simple operations.
 *  If you'd like to batch your requests, add dependencies between requests, set priorities, or schedule operations on your own queue, take a look at the corresponding `CKOperation`.
 *  This work is treated as having `NSQualityOfServiceUserInitiated` quality of service.
 */
@interface CKDatabase (ConvenienceMethods)

#pragma mark Record Convenience Methods
/*! `CKFetchRecordsOperation` and `CKModifyRecordsOperation` are the more configurable, `CKOperation`-based alternatives to these methods */
- (void)fetchRecordWithID:(CKRecordID *)recordID completionHandler:(void (^)(CKRecord * _Nullable record, NSError * _Nullable error))completionHandler;
- (void)saveRecord:(CKRecord *)record completionHandler:(void (^)(CKRecord * _Nullable record, NSError * _Nullable error))completionHandler;
- (void)deleteRecordWithID:(CKRecordID *)recordID completionHandler:(void (^)(CKRecordID * _Nullable recordID, NSError * _Nullable error))completionHandler;

#pragma mark Query Convenience Method
/*! @discussion `CKQueryOperation` is the more configurable, `CKOperation`-based alternative to this method
 *  Queries can potentially return a large number of records, and the server will return those records in batches. This convenience API will only fetch the first batch of results (equivalent to using `CKQueryOperationMaximumResults`).
 *  If you would like to fetch all results, use `CKQueryOperation` and its `CKQueryCursor` instead.
 *  Queries invoked within a `sharedCloudDatabase` must specify a `zoneID`.  Cross-zone queries are not supported in a `sharedCloudDatabase`
 */
- (void)performQuery:(CKQuery *)query inZoneWithID:(nullable CKRecordZoneID *)zoneID completionHandler:(void (^)(NSArray<CKRecord *> * _Nullable results, NSError * _Nullable error))completionHandler;

#pragma mark Record Zone Convenience Methods
/*! `CKFetchRecordZonesOperation` and `CKModifyRecordZonesOperation` are the more configurable, `CKOperation`-based alternatives to these methods */
- (void)fetchAllRecordZonesWithCompletionHandler:(void (^)(NSArray<CKRecordZone *> * _Nullable zones, NSError * _Nullable error))completionHandler;
- (void)fetchRecordZoneWithID:(CKRecordZoneID *)zoneID completionHandler:(void (^)(CKRecordZone * _Nullable zone, NSError * _Nullable error))completionHandler;
- (void)saveRecordZone:(CKRecordZone *)zone completionHandler:(void (^)(CKRecordZone * _Nullable zone, NSError * _Nullable error))completionHandler;
- (void)deleteRecordZoneWithID:(CKRecordZoneID *)zoneID completionHandler:(void (^)(CKRecordZoneID * _Nullable zoneID, NSError * _Nullable error))completionHandler;

#pragma mark Subscription Convenience Methods
/*! `CKFetchSubscriptionsOperation` and `CKModifySubscriptionsOperation` are the more configurable, `CKOperation`-based alternative to these methods */
- (void)fetchSubscriptionWithID:(CKSubscriptionID)subscriptionID completionHandler:(void (^)(CKSubscription * _Nullable subscription, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
- (void)fetchAllSubscriptionsWithCompletionHandler:(void (^)(NSArray<CKSubscription *> * _Nullable subscriptions, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
- (void)saveSubscription:(CKSubscription *)subscription completionHandler:(void (^)(CKSubscription * _Nullable subscription, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
- (void)deleteSubscriptionWithID:(CKSubscriptionID)subscriptionID completionHandler:(void (^)(NSString * _Nullable subscriptionID, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKFetchSubscriptionsOperation.h
//
//  CKFetchSubscriptionsOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>
#import <CloudKit/CKDefines.h>
#import <CloudKit/CKSubscription.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.10), ios(8.0), watchos(6.0))
@interface CKFetchSubscriptionsOperation : CKDatabaseOperation

+ (instancetype)fetchAllSubscriptionsOperation;

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithSubscriptionIDs:(NSArray<CKSubscriptionID> *)subscriptionIDs;

@property (nonatomic, copy, nullable) NSArray<CKSubscriptionID> *subscriptionIDs;

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The [NSOperation completionBlock] will also be called if both are set.
 *  If the error is `CKErrorPartialFailure`, the error's userInfo dictionary contains a dictionary of subscriptionID to errors keyed off of `CKPartialErrorsByItemIDKey`.
*/
@property (nonatomic, copy, nullable) void (^fetchSubscriptionCompletionBlock)(NSDictionary<CKSubscriptionID, CKSubscription *> * _Nullable subscriptionsBySubscriptionID, NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKDiscoverUserIdentitiesOperation.h
//
//  CKDiscoverUserIdentitiesOperation.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKOperation.h>

@class CKRecordID, CKUserIdentity, CKUserIdentityLookupInfo;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKDiscoverUserIdentitiesOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithUserIdentityLookupInfos:(NSArray<CKUserIdentityLookupInfo *> *)userIdentityLookupInfos;

@property (nonatomic, copy) NSArray<CKUserIdentityLookupInfo *> *userIdentityLookupInfos;

@property (nonatomic, copy, nullable) void (^userIdentityDiscoveredBlock)(CKUserIdentity *identity, CKUserIdentityLookupInfo * lookupInfo);

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The [NSOperation completionBlock] will also be called if both are set.
 */
@property (nonatomic, copy, nullable) void (^discoverUserIdentitiesCompletionBlock)(NSError * _Nullable operationError);

@end

NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKError.h
//
//  CKError.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKDefines.h>

NS_ASSUME_NONNULL_BEGIN

CK_EXTERN NSString * const CKErrorDomain API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/*! @abstract When a CKErrorPartialFailure happens this key will be set in the error's userInfo dictionary.
 *
 *  @discussion The value of this key will be a dictionary, and the values will be errors for individual items with the keys being the item IDs that failed.
 */
CK_EXTERN NSString * const CKPartialErrorsByItemIDKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/*! If the server rejects a record save because it has been modified since the last time it was read, a `CKErrorServerRecordChanged` error will be returned and it will contain versions of the record in its userInfo dictionary. Apply your custom conflict resolution logic to the server record under `CKServerRecordKey` and attempt a save of that record. */
CK_EXTERN NSString * const CKRecordChangedErrorAncestorRecordKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));
CK_EXTERN NSString * const CKRecordChangedErrorServerRecordKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));
CK_EXTERN NSString * const CKRecordChangedErrorClientRecordKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/*! On some errors, the userInfo dictionary may contain a NSNumber instance that specifies the period of time in seconds after which the client may retry the request. For example, this key will be on `CKErrorServiceUnavailable`, `CKErrorRequestRateLimited`, and other errors for which the recommended resolution is to retry after a delay.
 */
CK_EXTERN NSString * const CKErrorRetryAfterKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

typedef NS_ENUM(NSInteger, CKErrorCode) {
    /*! CloudKit.framework encountered an error.  This is a non-recoverable error. */    CKErrorInternalError                  = 1,
    
    /*! Some items failed, but the operation succeeded overall. Check CKPartialErrorsByItemIDKey in the userInfo dictionary for more details. */
    CKErrorPartialFailure                 = 2,
    
    /*! Network not available */
    CKErrorNetworkUnavailable             = 3,
    
    /*! Network error (available but CFNetwork gave us an error) */
    CKErrorNetworkFailure                 = 4,
    
    /*! Un-provisioned or unauthorized container. Try provisioning the container before retrying the operation. */
    CKErrorBadContainer                   = 5,
    
    /*! Service unavailable */
    CKErrorServiceUnavailable             = 6,
    
    /*! Client is being rate limited */
    CKErrorRequestRateLimited             = 7,
    
    /*! Missing entitlement */
    CKErrorMissingEntitlement             = 8,
    
    /*! Not authenticated (writing without being logged in, no user record) */
    CKErrorNotAuthenticated               = 9,
    
    /*! Access failure (save, fetch, or shareAccept) */
    CKErrorPermissionFailure              = 10,
    
    /*! Record does not exist */
    CKErrorUnknownItem                    = 11,
    
    /*! Bad client request (bad record graph, malformed predicate) */
    CKErrorInvalidArguments               = 12,
    
    CKErrorResultsTruncated API_DEPRECATED("Will not be returned", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0), watchos(3.0, 3.0)) = 13,
    
    /*! The record was rejected because the version on the server was different */
    CKErrorServerRecordChanged            = 14,
    
    /*! The server rejected this request. This is a non-recoverable error */
    CKErrorServerRejectedRequest          = 15,
    
    /*! Asset file was not found */
    CKErrorAssetFileNotFound              = 16,
    
    /*! Asset file content was modified while being saved */
    CKErrorAssetFileModified              = 17,
    
    /*! App version is less than the minimum allowed version */
    CKErrorIncompatibleVersion            = 18,
    
    /*! The server rejected the request because there was a conflict with a unique field. */
    CKErrorConstraintViolation            = 19,
    
    /*! A CKOperation was explicitly cancelled */
    CKErrorOperationCancelled             = 20,
    
    /*! The previousServerChangeToken value is too old and the client must re-sync from scratch */
    CKErrorChangeTokenExpired             = 21,
    
    /*! One of the items in this batch operation failed in a zone with atomic updates, so the entire batch was rejected. */
    CKErrorBatchRequestFailed             = 22,
    
    /*! The server is too busy to handle this zone operation. Try the operation again in a few seconds. */
    CKErrorZoneBusy                       = 23,
    
    /*! Operation could not be completed on the given database. Likely caused by attempting to modify zones in the public database. */
    CKErrorBadDatabase                    = 24,
    
    /*! Saving a record would exceed quota */
    CKErrorQuotaExceeded                  = 25,
    
    /*! The specified zone does not exist on the server */
    CKErrorZoneNotFound                   = 26,
    
    /*! The request to the server was too large. Retry this request as a smaller batch. */
    CKErrorLimitExceeded                  = 27,
    
    /*! The user deleted this zone through the settings UI. Your client should either remove its local data or prompt the user before attempting to re-upload any data to this zone. */
    CKErrorUserDeletedZone                = 28,
    
    /*! A share cannot be saved because there are too many participants attached to the share */
    CKErrorTooManyParticipants            API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 29,
    
    /*! A record/share cannot be saved, doing so would cause a hierarchy of records to exist in multiple shares */
    CKErrorAlreadyShared                  API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 30,
    
    /*! The target of a record's parent or share reference was not found */
    CKErrorReferenceViolation             API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 31,
    
    /*! Request was rejected due to a managed account restriction */
    CKErrorManagedAccountRestricted       API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 32,
    
    /*! Share Metadata cannot be determined, because the user is not a member of the share.  There are invited participants on the share with email addresses or phone numbers not associated with any iCloud account. The user may be able to join the share if they can associate one of those email addresses or phone numbers with their iCloud account via the system Share Accept UI. Call UIApplication's openURL on this share URL to have the user attempt to verify their information. */
    CKErrorParticipantMayNeedVerification API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 33,
    
    /*! The server received and processed this request, but the response was lost due to a network failure.  There is no guarantee that this request succeeded.  Your client should re-issue the request (if it is idempotent), or fetch data from the server to determine if the request succeeded. */
    CKErrorServerResponseLost             API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 34,
    
    /*! The file for this asset could not be accessed. It is likely your application does not have permission to open the file, or the file may be temporarily unavailable due to its data protection class. This operation can be retried after it is able to be opened in your process. */
    CKErrorAssetNotAvailable              API_AVAILABLE(macos(10.13), ios(11.3), tvos(11.3), watchos(4.3)) = 35,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKDiscoverUserInfosOperation.h
//
//  CKDiscoverUserInfosOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKOperation.h>

@class CKRecordID, CKDiscoveredUserInfo;

NS_ASSUME_NONNULL_BEGIN
API_DEPRECATED_WITH_REPLACEMENT("CKDiscoverUserIdentitiesOperation", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0), watchos(3.0, 3.0))
@interface CKDiscoverUserInfosOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithEmailAddresses:(nullable NSArray<NSString *> *)emailAddresses userRecordIDs:(nullable NSArray<CKRecordID *> *)userRecordIDs;

@property (nonatomic, copy, nullable) NSArray<NSString *> *emailAddresses;
@property (nonatomic, copy, nullable) NSArray<CKRecordID *> *userRecordIDs;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The [NSOperation completionBlock] will also be called if both are set.
 */
@property (nonatomic, copy, nullable) void (^discoverUserInfosCompletionBlock)(NSDictionary<NSString *, CKDiscoveredUserInfo *> * _Nullable emailsToUserInfos, NSDictionary<CKRecordID *, CKDiscoveredUserInfo *> * _Nullable userRecordIDsToUserInfos, NSError * _Nullable operationError);

#pragma clang diagnostic pop

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKNotification.h
//
//  CKNotification.h

//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKRecord.h>
#import <CloudKit/CKDatabase.h>

@class CKRecordID, CKRecordZoneID;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKNotificationID : NSObject <NSCopying, NSSecureCoding>
@end

/*! @enum CKNotificationType
 *
 *  @constant CKNotificationTypeQuery Generated by `CKQuerySubscriptions`
 *  @constant CKNotificationTypeRecordZone Generated by `CKRecordZoneSubscriptions`
 *  @constant CKNotificationTypeReadNotification Indicates a notification that a client had previously marked as read
 *  @constant CKNotificationTypeDatabase Generated by `CKDatabaseSubscriptions`
*/
typedef NS_ENUM(NSInteger, CKNotificationType) {
    CKNotificationTypeQuery            = 1,
    CKNotificationTypeRecordZone       = 2,
    CKNotificationTypeReadNotification = 3,
    CKNotificationTypeDatabase         API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0)) = 4,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKNotification : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

+ (nullable instancetype)notificationFromRemoteNotificationDictionary:(NSDictionary *)notificationDictionary;

/*! When you instantiate a CKNotification from a remote notification dictionary, you will get back a concrete
 subclass defined below.  Use notificationType to avoid -isKindOfClass: checks */
@property (nonatomic, readonly, assign) CKNotificationType notificationType;

@property (nonatomic, readonly, copy, nullable) CKNotificationID *notificationID;

@property (nonatomic, readonly, copy, nullable) NSString *containerIdentifier;

/*! @abstract Whether or not the notification fully represents what the server wanted to send.
 *
 * @discussion Push notifications have a limited size.  In some cases, CloudKit servers may not be able to send you a full `CKNotification`'s worth of info in one push.  In those cases, isPruned returns YES.  The order in which we'll drop properties is defined in each `CKNotification` subclass below.
 * The `CKNotification` can be obtained in full via a `CKFetchNotificationChangesOperation`
 */
@property (nonatomic, readonly, assign) BOOL isPruned;


/*! @discussion
 *  These keys are parsed out of the 'aps' payload from a remote notification dictionary.
 *  On tvOS, alerts, badges, sounds, and categories are not handled in push notifications.
 */

/*! Optional alert string to display in a push notification. */
@property (nonatomic, readonly, copy, nullable) NSString *alertBody __TVOS_PROHIBITED;
/*! Instead of a raw alert string, you may optionally specify a key for a localized string in your app's Localizable.strings file. */
@property (nonatomic, readonly, copy, nullable) NSString *alertLocalizationKey __TVOS_PROHIBITED;
/*! A list of field names to take from the matching record that is used as substitution variables in a formatted alert string. */
@property (nonatomic, readonly, copy, nullable) NSArray<NSString *> *alertLocalizationArgs __TVOS_PROHIBITED;

/*! Optional title of the alert to display in a push notification. */
@property (nonatomic, readonly, copy, nullable) NSString *title API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0)) __TVOS_PROHIBITED;
/*! Instead of a raw title string, you may optionally specify a key for a localized string in your app's Localizable.strings file. */
@property (nonatomic, readonly, copy, nullable) NSString *titleLocalizationKey API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0)) __TVOS_PROHIBITED;
/*! A list of field names to take from the matching record that is used as substitution variables in a formatted title string. */
@property (nonatomic, readonly, copy, nullable) NSArray<NSString *> *titleLocalizationArgs API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0)) __TVOS_PROHIBITED;

/*! Optional subtitle of the alert to display in a push notification. */
@property (nonatomic, readonly, copy, nullable) NSString *subtitle API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0)) __TVOS_PROHIBITED;
/*! Instead of a raw subtitle string, you may optionally specify a key for a localized string in your app's Localizable.strings file. */
@property (nonatomic, readonly, copy, nullable) NSString *subtitleLocalizationKey API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0)) __TVOS_PROHIBITED;
/*! A list of field names to take from the matching record that is used as substitution variables in a formatted subtitle string. */
@property (nonatomic, readonly, copy, nullable) NSArray<NSString *> *subtitleLocalizationArgs API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0)) __TVOS_PROHIBITED;


/*! A key for a localized string to be used as the alert action in a modal style notification. */
@property (nonatomic, readonly, copy, nullable) NSString *alertActionLocalizationKey __TVOS_PROHIBITED;
/*! The name of an image in your app bundle to be used as the launch image when launching in response to the notification. */
@property (nonatomic, readonly, copy, nullable) NSString *alertLaunchImage __TVOS_PROHIBITED;

/*! The number to display as the badge of the application icon */
@property (nonatomic, readonly, copy, nullable) NSNumber *badge API_AVAILABLE(tvos(10.0));
/*! The name of a sound file in your app bundle to play upon receiving the notification. */
@property (nonatomic, readonly, copy, nullable) NSString *soundName __TVOS_PROHIBITED;

/*! The ID of the subscription that caused this notification to fire */
@property (nonatomic, readonly, copy, nullable) CKSubscriptionID subscriptionID API_AVAILABLE(macos(10.11), ios(9.0), watchos(3.0));

/*! The category for user-initiated actions in the notification */
@property (nonatomic, readonly, copy, nullable) NSString *category API_AVAILABLE(macos(10.11), ios(9.0), watchos(3.0)) __TVOS_PROHIBITED;

@end

typedef NS_ENUM(NSInteger, CKQueryNotificationReason) {
    CKQueryNotificationReasonRecordCreated = 1,
    CKQueryNotificationReasonRecordUpdated,
    CKQueryNotificationReasonRecordDeleted,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/*! @class CKQueryNotification
 *
 *  @discussion `notificationType` == `CKNotificationTypeQuery`
 *  When properties must be dropped (see `isPruned`), here's the order of importance.  The most important properties are first, they'll be the last ones to be dropped.
 *  - notificationID
 *  - badge
 *  - alertLocalizationKey
 *  - alertLocalizationArgs
 *  - alertBody
 *  - alertActionLocalizationKey
 *  - alertLaunchImage
 *  - soundName
 *  - content-available
 *  - desiredKeys
 *  - queryNotificationReason
 *  - recordID
 *  - containerIdentifier
 *  - titleLocalizationKey
 *  - titleLocalizationArgs
 *  - title
 *  - subtitleLocalizationKey
 *  - subtitleLocalizationArgs
 *  - subtitle
 */
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKQueryNotification : CKNotification

@property (nonatomic, readonly, assign) CKQueryNotificationReason queryNotificationReason;

/*! @abstract A set of key->value pairs for creates and updates.
 *
 * @discussion You request the server fill out this property via the `desiredKeys` property of `CKNotificationInfo`
 */
@property (nonatomic, readonly, copy, nullable) NSDictionary<NSString *, id> *recordFields;

@property (nonatomic, readonly, copy, nullable) CKRecordID *recordID;

/*! If YES, this record is in the public database.  Else, it's in the private database */
@property (nonatomic, readonly, assign) BOOL isPublicDatabase API_DEPRECATED("Use databaseScope instead", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0), watchos(3.0, 3.0));

@property (nonatomic, readonly, assign) CKDatabaseScope databaseScope API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

@end


/*! @class CKRecordZoneNotification
 *
 *  @discussion `notificationType` == `CKNotificationTypeRecordZone`
 *  When properties must be dropped (see `isPruned`), here's the order of importance.  The most important properties are first, they'll be the last ones to be dropped.
 *  - notificationID
 *  - badge
 *  - alertLocalizationKey
 *  - alertLocalizationArgs
 *  - alertBody
 *  - alertActionLocalizationKey
 *  - alertLaunchImage
 *  - soundName
 *  - content-available
 *  - recordZoneID
 *  - containerIdentifier
 *  - titleLocalizationKey
 *  - titleLocalizationArgs
 *  - title
 *  - subtitleLocalizationKey
 *  - subtitleLocalizationArgs
 *  - subtitle
 */

API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKRecordZoneNotification : CKNotification

@property (nonatomic, readonly, copy, nullable) CKRecordZoneID *recordZoneID;

@property (nonatomic, readonly, assign) CKDatabaseScope databaseScope API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

@end


/*! @class CKDatabaseNotification
 *
 *  @discussion `notificationType` == `CKNotificationTypeDatabase`
 *  When properties must be dropped (see `isPruned`), here's the order of importance.  The most important properties are first, they'll be the last ones to be dropped.
 *  - notificationID
 *  - badge
 *  - alertLocalizationKey
 *  - alertLocalizationArgs
 *  - alertBody
 *  - alertActionLocalizationKey
 *  - alertLaunchImage
 *  - soundName
 *  - content-available
 *  - containerIdentifier
 *  - titleLocalizationKey
 *  - titleLocalizationArgs
 *  - title
 *  - subtitleLocalizationKey
 *  - subtitleLocalizationArgs
 *  - subtitle
 */

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKDatabaseNotification : CKNotification

@property (nonatomic, readonly, assign) CKDatabaseScope databaseScope;

@end

NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKServerChangeToken.h
//
//  CKServerChangeToken.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKServerChangeToken : NSObject <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKModifyRecordZonesOperation.h
//
//  CKModifyRecordZonesOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

@class CKRecordZone, CKRecordZoneID;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKModifyRecordZonesOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecordZonesToSave:(nullable NSArray<CKRecordZone *> *)recordZonesToSave recordZoneIDsToDelete:(nullable NSArray<CKRecordZoneID *> *)recordZoneIDsToDelete;

@property (nonatomic, copy, nullable) NSArray<CKRecordZone *> *recordZonesToSave;
@property (nonatomic, copy, nullable) NSArray<CKRecordZoneID *> *recordZoneIDsToDelete;

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The [NSOperation completionBlock] will also be called if both are set.
 *  If the error is `CKErrorPartialFailure`, the error's userInfo dictionary contains a dictionary of recordZoneIDs to errors keyed off of `CKPartialErrorsByItemIDKey`.
 *  This call happens as soon as the server has seen all record changes, and may be invoked while the server is processing the side effects of those changes.
 */
@property (nonatomic, copy, nullable) void (^modifyRecordZonesCompletionBlock)(NSArray<CKRecordZone *> * _Nullable savedRecordZones, NSArray<CKRecordZoneID *> * _Nullable deletedRecordZoneIDs, NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKQuery.h
//
//  CKQuery.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKRecord.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class CKQuery
 *
 *  @discussion Only AND compound predicates are allowed.
 *
 *  Key names must begin with either an upper or lower case character ([a-zA-Z]) and may be followed by characters, numbers, or underscores ([0-9a-zA-Z_]). Keypaths may only resolve to the currently evaluated object, so the '.' character is not allowed in key names.
 *
 *  A limited subset of classes are allowed as predicate arguments:
 *  - NSString
 *  - NSDate
 *  - NSData
 *  - NSNumber
 *  - NSArray
 *  - CKReference
 *  - CKRecord
 *  - CLLocation
 *
 * Any other class as an argument will result in an error when executing the query.
 */
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKQuery : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/*! Use `[NSPredicate predicateWithValue:YES]` / `NSPredicate(value: true)` if you want to query for all records of a given type. */
- (instancetype)initWithRecordType:(CKRecordType)recordType predicate:(NSPredicate *)predicate NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, copy) CKRecordType recordType;
@property (nonatomic, readonly, copy) NSPredicate *predicate;

@property (nonatomic, copy, nullable) NSArray<NSSortDescriptor *> *sortDescriptors;

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKFetchNotificationChangesOperation.h
//
//  CKFetchNotificationChangesOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

@class CKNotification, CKServerChangeToken;

NS_ASSUME_NONNULL_BEGIN

/*! @class CKFetchNotificationChangesOperation
 *
 *  @abstract An operation that fetches all notification changes.
 *
 *  @discussion If a change token from a previous `CKFetchNotificationChangesOperation` is passed in, only the notifications that have changed since that token will be fetched.
 *  If this is your first fetch, pass nil for the change token.
 *  Change tokens are opaque tokens and clients should not infer any behavior based on their content.
 */
API_DEPRECATED("Instead of iterating notifications to enumerate changed record zones, use CKDatabaseSubscription, CKFetchDatabaseChangesOperation, and CKFetchRecordZoneChangesOperation", macos(10.10, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0))
@interface CKFetchNotificationChangesOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithPreviousServerChangeToken:(nullable CKServerChangeToken *)previousServerChangeToken;

@property (nonatomic, copy, nullable) CKServerChangeToken *previousServerChangeToken;

@property (nonatomic, assign) NSUInteger resultsLimit;

/*! @abstract If true, then the server wasn't able to return all the changes in this response.
 *
 *  @discussion Will be set before `fetchNotificationChangesCompletionBlock` is called.
 *  Another `CKFetchNotificationChangesOperation` operation should be run with the updated `serverChangeToken` token from this operation.
 */
@property (nonatomic, readonly) BOOL moreComing;

@property (nonatomic, copy, nullable) void (^notificationChangedBlock)(CKNotification *notification);

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion Clients are responsible for saving the change token at the end of the operation and passing it in to the next call to `CKFetchNotificationChangesOperation`.
 *  Note that a fetch can fail partway. If that happens, an updated change token may be returned in the completion block so that already fetched notifications don't need to be re-downloaded on a subsequent operation.
 *  If the server returns a `CKErrorChangeTokenExpired` error, the `previousServerChangeToken` value was too old and the client should toss its local cache and re-fetch notification changes starting with a nil `previousServerChangeToken`.
 */
@property (nonatomic, copy, nullable) void (^fetchNotificationChangesCompletionBlock)(CKServerChangeToken * _Nullable serverChangeToken, NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CloudKit.h
//
//  CloudKit.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

#import <CloudKit/CKContainer.h>
#import <CloudKit/CKAsset.h>
#import <CloudKit/CKDatabase.h>
#import <CloudKit/CKError.h>
#import <CloudKit/CKLocationSortDescriptor.h>
#import <CloudKit/CKNotification.h>
#import <CloudKit/CKQuery.h>
#import <CloudKit/CKRecordZone.h>
#import <CloudKit/CKRecord.h>
#import <CloudKit/CKRecordID.h>
#import <CloudKit/CKRecordZoneID.h>
#import <CloudKit/CKReference.h>
#import <CloudKit/CKServerChangeToken.h>
#import <CloudKit/CKShare.h>
#import <CloudKit/CKShareMetadata.h>
#import <CloudKit/CKShareParticipant.h>
#import <CloudKit/CKSubscription.h>
#import <CloudKit/CKDiscoveredUserInfo.h>
#import <CloudKit/CKUserIdentity.h>
#import <CloudKit/CKUserIdentityLookupInfo.h>

#import <CloudKit/CKOperationGroup.h>
#import <CloudKit/CKOperation.h>
#import <CloudKit/CKDatabaseOperation.h>
#import <CloudKit/CKModifyRecordsOperation.h>
#import <CloudKit/CKFetchRecordsOperation.h>
#import <CloudKit/CKFetchRecordChangesOperation.h>
#import <CloudKit/CKFetchRecordZoneChangesOperation.h>
#import <CloudKit/CKQueryOperation.h>
#import <CloudKit/CKModifyBadgeOperation.h>
#import <CloudKit/CKFetchNotificationChangesOperation.h>
#import <CloudKit/CKMarkNotificationsReadOperation.h>
#import <CloudKit/CKFetchSubscriptionsOperation.h>
#import <CloudKit/CKModifySubscriptionsOperation.h>
#import <CloudKit/CKModifyRecordZonesOperation.h>
#import <CloudKit/CKFetchRecordZonesOperation.h>
#import <CloudKit/CKFetchWebAuthTokenOperation.h>
#import <CloudKit/CKDiscoverUserInfosOperation.h>
#import <CloudKit/CKDiscoverAllContactsOperation.h>
#import <CloudKit/CKDiscoverUserIdentitiesOperation.h>
#import <CloudKit/CKDiscoverAllUserIdentitiesOperation.h>
#import <CloudKit/CKFetchShareParticipantsOperation.h>
#import <CloudKit/CKAcceptSharesOperation.h>
#import <CloudKit/CKFetchShareMetadataOperation.h>
#import <CloudKit/CKFetchDatabaseChangesOperation.h>
// ==========  CloudKit.framework/Headers/CKFetchShareMetadataOperation.h
//
//  CKFetchShareMetadataOperation.h
//  CloudKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <CloudKit/CKOperation.h>
#import <CloudKit/CKRecord.h>

@class CKShareMetadata, CKFetchShareMetadataOptions;

NS_ASSUME_NONNULL_BEGIN

/*! @class CKFetchShareMetadataOperation
 *
 *  @abstract Fetch the `CKShareMetadata` for a share URL.
 *
 *  @discussion Since you can't know what container this share is in before you fetch its metadata, you may run this operation in any container you have access to
 */
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKFetchShareMetadataOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithShareURLs:(NSArray<NSURL *> *)shareURLs;

@property (nonatomic, copy, nullable) NSArray<NSURL *> *shareURLs;

/*! @abstract If set to YES, the resulting `CKShareMetadata` will have a `rootRecord` object filled out.
 *
 *  @discussion Defaults to NO.
 *  The resulting `CKShareMetadata` will have a `rootRecordID` property regardless of the value of this property.
 */
@property (nonatomic, assign) BOOL shouldFetchRootRecord;

/*! @abstract Declares which user-defined keys should be fetched and added to the resulting `rootRecord`.
 *
 *  @discussion Only consulted if `shouldFetchRootRecord` is YES.
 *  If nil, declares the entire root record should be downloaded. If set to an empty array, declares that no user fields should be downloaded.
 *  Defaults to nil.
 */
@property (nonatomic, copy, nullable) NSArray<CKRecordFieldKey> *rootRecordDesiredKeys;

@property (nonatomic, copy, nullable) void (^perShareMetadataBlock)(NSURL *shareURL, CKShareMetadata * _Nullable shareMetadata, NSError * _Nullable error);

@property (nonatomic, copy, nullable) void (^fetchShareMetadataCompletionBlock)(NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKMarkNotificationsReadOperation.h
//
//  CKMarkNotificationsReadOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKOperation.h>

@class CKNotificationID;

NS_ASSUME_NONNULL_BEGIN
API_DEPRECATED("Instead of iterating notifications, consider using CKDatabaseSubscription, CKFetchDatabaseChangesOperation, and CKFetchRecordZoneChangesOperation as appropriate", macos(10.10, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0))
@interface CKMarkNotificationsReadOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithNotificationIDsToMarkRead:(NSArray<CKNotificationID *> *)notificationIDs;

@property (nonatomic, copy, nullable) NSArray<CKNotificationID *> *notificationIDs;

@property (nonatomic, copy, nullable) void (^markNotificationsReadCompletionBlock)(NSArray<CKNotificationID *> * _Nullable notificationIDsMarkedRead, NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKReference.h
//
//  CKReference.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKRecord, CKRecordID, CKAsset;

NS_ASSUME_NONNULL_BEGIN

/*! @enum CKReferenceAction
 *  @constant CKReferenceActionNone When the referred record is deleted, this record is unchanged, and has a dangling pointer
 *  @constant CKReferenceActionDeleteSelf When the referred record is deleted then this record is also deleted
 */
typedef NS_ENUM(NSUInteger, CKReferenceAction) {
    CKReferenceActionNone       = 0,
    CKReferenceActionDeleteSelf = 1,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));


API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKReference : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*! @discussion It is acceptable to relate two records that have not yet been uploaded to the server, but those records must be uploaded to the server in the same operation.
 *
 *  If a record references a record that does not exist on the server and is not in the current save operation it will result in an error.
 */
- (instancetype)initWithRecordID:(CKRecordID *)recordID action:(CKReferenceAction)action NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecord:(CKRecord *)record action:(CKReferenceAction)action;

@property (nonatomic, readonly, assign) CKReferenceAction referenceAction;

@property (nonatomic, readonly, copy) CKRecordID *recordID;

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKShareParticipant.h
//
//  CKShareParticipant.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKUserIdentity;

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSInteger, CKShareParticipantAcceptanceStatus) {
    CKShareParticipantAcceptanceStatusUnknown,
    CKShareParticipantAcceptanceStatusPending,
    CKShareParticipantAcceptanceStatusAccepted,
    CKShareParticipantAcceptanceStatusRemoved,
} API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*! These permissions determine what share participants can do with records inside that share */
typedef NS_ENUM(NSInteger, CKShareParticipantPermission) {
    CKShareParticipantPermissionUnknown,
    CKShareParticipantPermissionNone,
    CKShareParticipantPermissionReadOnly,
    CKShareParticipantPermissionReadWrite,
} API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*! @abstract The participant type determines whether a participant can modify the list of participants on a share.
 *
 *  @discussion
 *  - Owners can add private users
 *  - Private users can access the share
 *  - Public users are "self-added" when the participant accesses the shareURL.  Owners cannot add public users.
 */
typedef NS_ENUM(NSInteger, CKShareParticipantRole) {
    CKShareParticipantRoleUnknown = 0,
    CKShareParticipantRoleOwner = 1,
    CKShareParticipantRolePrivateUser = 3,
    CKShareParticipantRolePublicUser = 4,
} API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

typedef NS_ENUM(NSInteger, CKShareParticipantType) {
    CKShareParticipantTypeUnknown = 0,
    CKShareParticipantTypeOwner = 1,
    CKShareParticipantTypePrivateUser = 3,
    CKShareParticipantTypePublicUser = 4,
} API_DEPRECATED_WITH_REPLACEMENT("CKShareParticipantRole", macos(10.12, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0), watchos(3.0, 5.0));

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKShareParticipant : NSObject <NSSecureCoding, NSCopying>

/*! Use `CKFetchShareParticipantsOperation` to create a `CKShareParticipant` object */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly, strong) CKUserIdentity *userIdentity;

/*! The default participant role is `CKShareParticipantRolePrivateUser`. */
@property (nonatomic, assign) CKShareParticipantRole role API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

/*! The default participant type is `CKShareParticipantTypePrivateUser`. */
@property (nonatomic, assign) CKShareParticipantType type API_DEPRECATED_WITH_REPLACEMENT("role", macos(10.12, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0), watchos(3.0, 5.0));

@property (nonatomic, readonly, assign) CKShareParticipantAcceptanceStatus acceptanceStatus;

/*! The default permission for a new participant is `CKShareParticipantPermissionReadOnly`. */
@property (nonatomic, assign) CKShareParticipantPermission permission;

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKOperation.h
//
//  CKOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKDefines.h>

@class CKContainer, CKOperationConfiguration, CKOperationGroup;

NS_ASSUME_NONNULL_BEGIN

typedef NSString *CKOperationID;

API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKOperation : NSOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*! @abstract This defines per-operation configuration settings.
 *
 *  @discussion See the CKOperationConfiguration class description for info on how this configuration composes with CKOperationGroup.defaultConfiguration
 */
@property (nonatomic, copy, null_resettable) CKOperationConfiguration *configuration API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*! @abstract The group this operation is associated with
 */
@property (nonatomic, strong, nullable) CKOperationGroup *group API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*! @abstract This is an identifier unique to this CKOperation.
 *
 *  @discussion This value is chosen by the system, and will be unique to this instance of a CKOperation.  This identifier will be sent to Apple's servers, and can be used to identify any server-side logging associated with this operation.
 */
@property (nonatomic, readonly, copy) CKOperationID operationID API_AVAILABLE(macos(10.12), ios(9.3), tvos(9.2), watchos(3.0));

/*! @abstract This callback is called after a long lived operation has begun running and is persisted.
 *
 *  @discussion Once this callback is called the operation will continue running even if the current process exits.
 */
@property (nonatomic, strong, nullable) void (^longLivedOperationWasPersistedBlock)(void) API_AVAILABLE(macos(10.12), ios(9.3), tvos(9.2), watchos(3.0));

@end

/*! @class CKOperationConfiguration
 *
 *  @discussion An operation configuration is a set of properties that describes how your operation should behave.  All properties have a default value.  When determining what properties to apply to an operation, we consult the operation's configuration property, as well as the operation->group->defaultConfiguration property.  We combine them following these rules:
 *   Group Default Configuration Value | Operation Configuration Value |        Value Applied To Operation
 *  -----------------------------------+-------------------------------+-----------------------------------------
 *             default value           |         default value         |                  default value
 *             default value           |         explicit value        |       operation.configuration explicit value
 *             explicit value          |         default value         | operation.group.defaultConfiguration explicit value
 *             explicit value          |         explicit value        |       operation.configuration explicit value
 *
 *  For example:
 *  CKOperationGroup -> defaultConfiguration -> allowsCellularAccess explicitly set to NO
 *  + CKOperation -> configuration -> allowsCellularAccess has default value of YES
 *  = disallow cellular access
 *
 *  CKOperationGroup -> defaultConfiguration -> allowsCellularAccess explicitly set to NO
 *  + CKOperation -> configuration -> allowsCellularAccess explicitly set to YES
 *  = allow cellular access
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface CKOperationConfiguration : NSObject

/*! If no container is set, [CKContainer defaultContainer] is used */
@property (nonatomic, strong, nullable) CKContainer *container;

/*! @discussion CKOperations behave differently depending on how you set qualityOfService.
 *
 *  Quality of Service | timeoutIntervalForResource | Network Error Behavior | Discretionary Behavior
 *  -------------------+----------------------------+------------------------+-----------------------
 *  UserInteractive    | -1 (no enforcement)        | fail                   | nonDiscretionary
 *  UserInitiated      | -1 (no enforcement)        | fail                   | nonDiscretionary
 *  Default            | 1 week                     | fail                   | discretionary when app backgrounded
 *  Utility            | 1 week                     | internally retried     | discretionary when app backgrounded
 *  Background         | 1 week                     | internally retried     | discretionary
 *
 * timeoutIntervalForResource
 * - the timeout interval for any network resources retrieved by this operation
 * - this can be overridden via CKOperationConfiguration's timeoutIntervalForResource property
 *
 * Network Error Behavior
 * - when a network request in service of a CKOperation fails due to a networking error, the operation may fail with that error, or internally retry the network request.  Only a subset of networking errors are retried, and limiting factors such as timeoutIntervalForResource are still applicable.
 *
 * Discretionary Behavior
 * - network requests in service of a CKOperation may be marked as discretionary
 * - discretionary network requests are scheduled at the description of the system for optimal performance
 *
 * CKOperations have a default qualityOfService of Default.
 */
@property (nonatomic, assign) NSQualityOfService qualityOfService;


/*! Defaults to YES */
@property (nonatomic, assign) BOOL allowsCellularAccess;

/*! @discussion Long lived operations will continue running even if your process exits. If your process remains alive for the lifetime of the long lived operation its behavior is the same as a regular operation.
 *
 *  Long lived operations can be fetched and replayed from the container via the `fetchAllLongLivedOperations:` and `fetchLongLivedOperationsWithIDs:` APIs.
 *
 *  Long lived operations persist until their -[NSOperation completionBlock] returns or until the operation is cancelled.
 *  Long lived operations may be garbage collected 24 hours after they finish running if no client has replayed them.
 *
 *  The default value for longLived is NO. Changing the value of longLived on an already started operation or on an outstanding long lived operation fetched from CKContainer has no effect.
 */
@property (nonatomic, assign, getter=isLongLived) BOOL longLived;

/*! @discussion If non-zero, overrides the timeout interval for any network requests issued by this operation.
 *  The default value is 60.
 *
 * @see NSURLSessionConfiguration.timeoutIntervalForRequest
*/
@property (nonatomic, assign) NSTimeInterval timeoutIntervalForRequest;

/*! @discussion If set, overrides the timeout interval for any network resources retrieved by this operation.
 *  If not explicitly set, defaults to a value based on the operation's qualityOfService
 *
 * @see NSURLSessionConfiguration.timeoutIntervalForResource
 */
@property (nonatomic, assign) NSTimeInterval timeoutIntervalForResource;


@end

#pragma mark - Deprecated CKOperation

/*! These deprecated properties now read and write from the CKOperation's configuration */
@interface CKOperation (CKOperationDeprecated)
@property (nonatomic, strong, nullable) CKContainer *container          API_DEPRECATED("Use CKOperationConfiguration", macos(10.10, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));
@property (nonatomic, assign) BOOL allowsCellularAccess                 API_DEPRECATED("Use CKOperationConfiguration", macos(10.10, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));
@property (nonatomic, assign, getter=isLongLived) BOOL longLived        API_DEPRECATED("Use CKOperationConfiguration", macos(10.12, 10.13), ios(9.3, 11.0), tvos(9.2, 11.0), watchos(3.0, 4.0));
@property (nonatomic, assign) NSTimeInterval timeoutIntervalForRequest  API_DEPRECATED("Use CKOperationConfiguration", macos(10.12, 10.13), ios(10.0, 11.0), tvos(10.0, 11.0), watchos(3.0, 4.0));
@property (nonatomic, assign) NSTimeInterval timeoutIntervalForResource API_DEPRECATED("Use CKOperationConfiguration", macos(10.12, 10.13), ios(10.0, 11.0), tvos(10.0, 11.0), watchos(3.0, 4.0));
@end
NS_ASSUME_NONNULL_END

// ==========  CloudKit.framework/Headers/CKFetchDatabaseChangesOperation.h
//
//  CKFetchDatabaseChangesOperation.h
//  CloudKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

@class CKRecordZoneID, CKServerChangeToken;

NS_ASSUME_NONNULL_BEGIN

/*! @class CKFetchDatabaseChangesOperation
 *
 *  @abstract This operation will fetch changes to record zones within a database
 *
 *  @discussion If a change anchor from a previous `CKFetchDatabaseChangesOperation` is passed in, only the zones that have changed since that anchor will be returned.
 *  This per-database `serverChangeToken` is not to be confused with the per-recordZone `serverChangeToken` from `CKFetchRecordZoneChangesOperation`.
 *  If this is your first fetch or if you wish to re-fetch all zones, pass nil for the change token.
 *  Change token are opaque tokens and clients should not infer any behavior based on their content.
 *  `CKFetchDatabaseChangesOperation` is supported in a `privateCloudDatabase` and `sharedCloudDatabase`
 */
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKFetchDatabaseChangesOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithPreviousServerChangeToken:(nullable CKServerChangeToken *)previousServerChangeToken;

@property (nonatomic, copy, nullable) CKServerChangeToken *previousServerChangeToken;
@property (nonatomic, assign) NSUInteger resultsLimit;

/*! @discussion When set to YES, this operation will send repeated requests to the server until all record zone changes have been fetched.
 *
 *  `changeTokenUpdatedBlock` will be invoked periodically, to give clients an updated change token so that already-fetched record zone changes don't need to be re-fetched on a subsequent operation.
 *  When set to NO, it is the responsibility of the caller to issue subsequent fetch-changes operations when moreComing is YES in a `fetchDatabaseChangesCompletionBlock` invocation.
 *  `fetchAllChanges` is YES by default
 */
@property (nonatomic, assign) BOOL fetchAllChanges;

@property (nonatomic, copy, nullable) void (^recordZoneWithIDChangedBlock)(CKRecordZoneID *zoneID);
@property (nonatomic, copy, nullable) void (^recordZoneWithIDWasDeletedBlock)(CKRecordZoneID *zoneID);

/*! @abstract If this block is set it will be called instead of `recordZoneWithIDWasDeletedBlock` if the user deleted this zone via the iCloud storage UI.
 *
 *  @discussion This is an indication that the user wanted all data deleted, so local cached data should be wiped and not re-uploaded to the server.
 */
@property (nonatomic, copy, nullable) void (^recordZoneWithIDWasPurgedBlock)(CKRecordZoneID *zoneID) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@property (nonatomic, copy, nullable) void (^changeTokenUpdatedBlock)(CKServerChangeToken * serverChangeToken);

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion Clients are responsible for saving the change token at the end of the operation and passing it in to the next call to `CKFetchDatabaseChangesOperation`.
 *  If the server returns a `CKErrorChangeTokenExpired` error, the `previousServerChangeToken` value was too old and the client should toss its local cache and re-fetch the changes in this record zone starting with a nil `previousServerChangeToken`.
 *  If `moreComing` is true then the server wasn't able to return all the changes in this response. Another `CKFetchDatabaseChangesOperation` operation should be run with the `previousServerChangeToken` token from this operation.
 */
@property (nonatomic, copy, nullable) void (^fetchDatabaseChangesCompletionBlock)(CKServerChangeToken * _Nullable serverChangeToken, BOOL moreComing, NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKFetchRecordChangesOperation.h
//
//  CKFetchRecordChangesOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>
#import <CloudKit/CKServerChangeToken.h>
#import <CloudKit/CKRecord.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class CKFetchRecordChangesOperation
 *
 *  @discussion Use CKFetchRecordZoneChangesOperation instead of this class.
 *
 *  Any serverChangeTokens saved from a CKFetchRecordChangesOperation are usable as a serverRecordZoneChangeToken in CKFetchRecordZoneChangesOperation
 *
 *  This operation will fetch records changes in the given record zone.
 *
 *  If a change token from a previous `CKFetchRecordChangesOperation` is passed in, only the records that have changed since that token will be fetched.
 *  If this is your first fetch or if you wish to re-fetch all records, pass nil for the change token.
 *  Change tokens are opaque tokens and clients should not infer any behavior based on their content
 */
API_DEPRECATED_WITH_REPLACEMENT("CKFetchRecordZoneChangesOperation", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0), watchos(3.0, 3.0))
@interface CKFetchRecordChangesOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecordZoneID:(CKRecordZoneID *)recordZoneID previousServerChangeToken:(nullable CKServerChangeToken *)previousServerChangeToken;

@property (nonatomic, copy, nullable) CKRecordZoneID *recordZoneID;
@property (nonatomic, copy, nullable) CKServerChangeToken *previousServerChangeToken;

@property (nonatomic, assign) NSUInteger resultsLimit;

/*! @abstract Declares which user-defined keys should be fetched and added to the resulting CKRecords.
 *
 *  @discussion If nil, declares the entire record should be downloaded. If set to an empty array, declares that no user fields should be downloaded.
 *  Defaults to nil.
 */
@property (nonatomic, copy, nullable) NSArray<CKRecordFieldKey> *desiredKeys;

@property (nonatomic, copy, nullable) void (^recordChangedBlock)(CKRecord *record);
@property (nonatomic, copy, nullable) void (^recordWithIDWasDeletedBlock)(CKRecordID *recordID);

/*! @abstract If true, then the server wasn't able to return all the changes in this response.
 *
 *  @discussion Will be set before fetchRecordChangesCompletionBlock is called.
 *  Another CKFetchRecordChangesOperation operation should be run with the updated serverChangeToken token from this operation.
 */
@property (nonatomic, readonly) BOOL moreComing;

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion Clients are responsible for saving the change token at the end of the operation and passing it in to the next call to `CKFetchRecordChangesOperation`.
 *  Note that a fetch can fail partway. If that happens, an updated change token may be returned in the completion block so that already fetched records don't need to be re-downloaded on a subsequent operation.
 *  The `clientChangeTokenData` from the most recent `CKModifyRecordsOperation` is also returned, or nil if none was provided.
 *  If the server returns a `CKErrorChangeTokenExpired` error, the `previousServerChangeToken` value was too old and the client should toss its local cache and re-fetch the changes in this record zone starting with a nil `previousServerChangeToken`.
 */
@property (nonatomic, copy, nullable) void (^fetchRecordChangesCompletionBlock)(CKServerChangeToken * _Nullable serverChangeToken, NSData * _Nullable clientChangeTokenData, NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKRecordZoneID.h
//
//  CKRecordZoneID.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKRecordZoneID : NSObject <NSSecureCoding, NSCopying>

/*! Zone names must be 255 characters or less. Most UTF-8 characters are valid. */

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithZoneName:(NSString *)zoneName ownerName:(NSString *)ownerName NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, strong) NSString *zoneName;
@property (nonatomic, readonly, strong) NSString *ownerName;

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKFetchRecordsOperation.h
//
//  CKFetchRecordsOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>
#import <CloudKit/CKRecord.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKFetchRecordsOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecordIDs:(NSArray<CKRecordID *> *)recordIDs;

+ (instancetype)fetchCurrentUserRecordOperation;

@property (nonatomic, copy, nullable) NSArray<CKRecordID *> *recordIDs;

/*! @abstract Declares which user-defined keys should be fetched and added to the resulting CKRecords.
 *
 *  @discussion If nil, declares the entire record should be downloaded. If set to an empty array, declares that no user fields should be downloaded.
 *  Defaults to nil.
 */
@property (nonatomic, copy, nullable) NSArray<CKRecordFieldKey> *desiredKeys;

/*! Called repeatedly during transfer. */
@property (nonatomic, copy, nullable) void (^perRecordProgressBlock)(CKRecordID *recordID, double progress);
/*! Called on success or failure for each record. */
@property (nonatomic, copy, nullable) void (^perRecordCompletionBlock)(CKRecord * _Nullable record, CKRecordID * _Nullable recordID, NSError * _Nullable error);

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The [NSOperation completionBlock] will also be called if both are set.
 *  If the error is `CKErrorPartialFailure`, the error's userInfo dictionary contains a dictionary of recordIDs to errors keyed off of `CKPartialErrorsByItemIDKey`.
*/
@property (nonatomic, copy, nullable) void (^fetchRecordsCompletionBlock)(NSDictionary<CKRecordID * , CKRecord *> * _Nullable recordsByRecordID, NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKModifyRecordsOperation.h
//
//  CKModifyRecordsOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

@class CKRecord, CKRecordID;

/*! @enum CKRecordSavePolicy
 *
 *  @constant CKRecordSaveIfServerRecordUnchanged
 *  @discussion Locally-edited keys are sent to the server.
 *  If the record on the server has been modified, fail the write and return an error. A CKShare's participants array is always treated as `CKRecordSaveIfServerRecordUnchanged`, regardless of the `savePolicy` of the operation that modifies the share.
 *
 *  @constant CKRecordSaveChangedKeys
 *  @discussion Locally-edited keys are written to the server.
 *  Any unseen changes on the server will be overwritten to the locally-edited value.
 *
 *  @constant CKRecordSaveAllKeys
 *  @discussion All local keys are written to the server.
 *  Any unseen changes on the server will be overwritten to the local values.  Keys present only on the server remain unchanged. There are two common ways in which a server record will contain keys not present locally:
 *  1 - Since you've fetched this record, another client has added a new key to the record.
 *  2 - The presence of `desiredKeys` on the fetch / query that returned this record meant that only a portion of the record's keys were downloaded.
 */
typedef NS_ENUM(NSInteger, CKRecordSavePolicy) {
    CKRecordSaveIfServerRecordUnchanged = 0,
    CKRecordSaveChangedKeys             = 1,
    CKRecordSaveAllKeys                 = 2,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKModifyRecordsOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecordsToSave:(nullable NSArray<CKRecord *> *)records recordIDsToDelete:(nullable NSArray<CKRecordID *> *)recordIDs;

@property (nonatomic, copy, nullable) NSArray<CKRecord *> *recordsToSave;
@property (nonatomic, copy, nullable) NSArray<CKRecordID *> *recordIDsToDelete;

/*! The default value is `CKRecordSaveIfServerRecordUnchanged`. */
@property (nonatomic, assign) CKRecordSavePolicy savePolicy;

/*! @discussion This property is kept by the server to identify the last known request from this client.
 *  Multiple requests from the client with the same change token will be ignored by the server.
 */
@property (nonatomic, copy, nullable) NSData *clientChangeTokenData;

/*! @abstract  Determines whether the batch should fail atomically or not.
 *
 *  @discussion YES by default.
 *  Server-side write atomicity is only enforced on zones that have `CKRecordZoneCapabilityAtomic`.
 *  If `isAtomic` is YES, client-side checks are enforced regardless of the zone's capabilities.  (For example, if a record is malformed, and cannot be sent to the server, the client will forcibly fail all other records-to-be-modified in that zone)
 */
@property (nonatomic, assign) BOOL atomic NS_SWIFT_NAME(isAtomic);

/*! @discussion Called repeatedly during transfer.
 *  It is possible for progress to regress when a retry is automatically triggered.
*/
@property (nonatomic, copy, nullable) void (^perRecordProgressBlock)(CKRecord *record, double progress);
/*! Called on success or failure for each record. */
@property (nonatomic, copy, nullable) void (^perRecordCompletionBlock)(CKRecord *record, NSError * _Nullable error);

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The [NSOperation completionBlock] will also be called if both are set.
 *  If the error is `CKErrorPartialFailure`, the error's userInfo dictionary contains a dictionary of recordIDs to errors keyed off of `CKPartialErrorsByItemIDKey`.
 *  This call happens as soon as the server has seen all record changes, and may be invoked while the server is processing the side effects of those changes.
*/
@property (nonatomic, copy, nullable) void (^modifyRecordsCompletionBlock)(NSArray<CKRecord *> * _Nullable savedRecords, NSArray<CKRecordID *> * _Nullable deletedRecordIDs, NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKDiscoveredUserInfo.h
//
//  CKDiscoveredUserInfo.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#if (TARGET_OS_OSX && !defined(__i386__)) || TARGET_OS_IOS
@class CNContact;
#endif

@class CKRecordID;

NS_ASSUME_NONNULL_BEGIN
API_DEPRECATED_WITH_REPLACEMENT("CKUserIdentity", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0), watchos(3.0, 3.0))
@interface CKDiscoveredUserInfo : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly, copy, nullable) CKRecordID *userRecordID;

#if (TARGET_OS_OSX && !defined(__i386__)) || TARGET_OS_IOS

@property (nonatomic, readonly, copy, nullable) NSString *firstName API_DEPRECATED("Use CKDiscoveredUserInfo.displayContact.givenName", macos(10.10, 10.11), ios(8.0, 9.0), tvos(9.0, 9.0));
@property (nonatomic, readonly, copy, nullable) NSString *lastName API_DEPRECATED("Use CKDiscoveredUserInfo.displayContact.familyName", macos(10.10, 10.11), ios(8.0, 9.0), tvos(9.0, 9.0));

/*! Not associated with the local Address Book.  It is a wrapper around information known to the CloudKit server, including first and last names */
@property (nonatomic, readonly, copy, nullable) CNContact *displayContact API_AVAILABLE(macos(10.11), ios(9.0));

#else // (TARGET_OS_OSX && !defined(__i386__)) || TARGET_OS_IOS



@property (nonatomic, readonly, copy, nullable) NSString *firstName;
@property (nonatomic, readonly, copy, nullable) NSString *lastName;

#endif // (TARGET_OS_OSX && !defined(__i386__)) || TARGET_OS_IOS


@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKDatabaseOperation.h
//
//  CKDatabaseOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKOperation.h>

@class CKDatabase;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKDatabaseOperation : CKOperation

/*! @abstract The database on which to perform the operation.
 *
 * @discussion If no database is set, `[self.container privateCloudDatabase]` is used.
 * This will also set the container property of the operation's configuration to match the container of the passed-in database.
 */
@property (nonatomic, strong, nullable) CKDatabase *database;

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKRecordZone.h
//
//  CKRecordZone.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKDefines.h>

@class CKRecordZoneID;

NS_ASSUME_NONNULL_BEGIN
typedef NS_OPTIONS(NSUInteger, CKRecordZoneCapabilities) {
    /*! This zone supports CKFetchRecordChangesOperation */
    CKRecordZoneCapabilityFetchChanges   = 1 << 0,
    /*! Batched changes to this zone happen atomically */
    CKRecordZoneCapabilityAtomic         = 1 << 1,
    /*! Records in this zone can be shared */
    CKRecordZoneCapabilitySharing        API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 1 << 2,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

CK_EXTERN NSString * const CKRecordZoneDefaultName API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKRecordZone : NSObject <NSSecureCoding, NSCopying>

+ (CKRecordZone *)defaultRecordZone;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithZoneName:(NSString *)zoneName;
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID;

@property (nonatomic, readonly, strong) CKRecordZoneID *zoneID;

/*! Capabilities on locally-created record zones are not valid until the record zone is saved. Capabilities on record zones fetched from the server are valid. */
@property (nonatomic, readonly, assign) CKRecordZoneCapabilities capabilities;

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKFetchShareParticipantsOperation.h
//
//  CKFetchShareParticipantsOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKOperation.h>

@class CKUserIdentityLookupInfo, CKShareParticipant, CKRecordID;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKFetchShareParticipantsOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithUserIdentityLookupInfos:(NSArray<CKUserIdentityLookupInfo *> *)userIdentityLookupInfos;

@property (nonatomic, copy, nullable) NSArray<CKUserIdentityLookupInfo *> *userIdentityLookupInfos;

@property (nonatomic, copy, nullable) void (^shareParticipantFetchedBlock)(CKShareParticipant *participant);

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The [NSOperation completionBlock] will also be called if both are set.
 *  If the error is `CKErrorPartialFailure`, the error's userInfo dictionary contains a dictionary of lookup infos to errors keyed off of `CKPartialErrorsByItemIDKey`.
 */
@property (nonatomic, copy, nullable) void (^fetchShareParticipantsCompletionBlock)(NSError * _Nullable operationError);

@end

NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKDefines.h
//
//  CKDefines.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#ifndef CK_EXTERN
#ifdef __cplusplus
#define CK_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define CK_EXTERN   extern __attribute__((visibility ("default")))
#endif
#endif

#ifndef CK_HIDDEN
#define CK_HIDDEN   __attribute__((visibility("hidden")))
#endif

#ifndef CK_EXTERN_HIDDEN
#ifdef __cplusplus
#define CK_EXTERN_HIDDEN   extern "C" __attribute__((visibility ("hidden")))
#else
#define CK_EXTERN_HIDDEN   extern __attribute__((visibility ("hidden")))
#endif
#endif
// ==========  CloudKit.framework/Headers/CKRecordID.h
//
//  CKRecordID.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKRecordZoneID;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKRecordID : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*! Record names must be 255 characters or less. Most UTF-8 characters are valid. */

/*! Creates a record ID in the default zone */
- (instancetype)initWithRecordName:(NSString *)recordName;

- (instancetype)initWithRecordName:(NSString *)recordName zoneID:(CKRecordZoneID *)zoneID NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, strong) NSString *recordName;
@property (nonatomic, readonly, strong) CKRecordZoneID *zoneID;

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKOperationGroup.h
//
//  CKOperationGroup.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKDefines.h>

@class CKOperationConfiguration;

NS_ASSUME_NONNULL_BEGIN

/*! @enum CKOperationGroupTransferSize
 *  @abstract Valid values for expectedSendSize and expectedReceiveSize
 *  @constant CKOperationGroupTransferSizeUnknown Default value when you're completely unsure of your working set size.
 *  @constant CKOperationGroupTransferSizeKilobytes Less than 1MB
 *  @constant CKOperationGroupTransferSizeMegabytes 1-10MB
 *  @constant CKOperationGroupTransferSizeTensOfMegabytes 10-100MB
 *  @constant CKOperationGroupTransferSizeHundredsOfMegabytes 100MB-1GB
 *  @constant CKOperationGroupTransferSizeGigabytes 1-10GB
 *  @constant CKOperationGroupTransferSizeTensOfGigabytes 10-100GB
 *  @constant CKOperationGroupTransferSizeHundredsOfGigabytes More than 100GB
 */
typedef NS_ENUM(NSInteger, CKOperationGroupTransferSize) {
    CKOperationGroupTransferSizeUnknown,
    CKOperationGroupTransferSizeKilobytes,
    CKOperationGroupTransferSizeMegabytes,
    CKOperationGroupTransferSizeTensOfMegabytes,
    CKOperationGroupTransferSizeHundredsOfMegabytes,
    CKOperationGroupTransferSizeGigabytes,
    CKOperationGroupTransferSizeTensOfGigabytes,
    CKOperationGroupTransferSizeHundredsOfGigabytes,
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*! @class CKOperationGroup
 *
 *  @abstract A mechanism for your app to group several operations at the granularity of a user action.
 *
 *  @discussion For example, when building a Calendar application, these things might warrant being their own operation groups:
 *  - an initial fetch of data from the server, consisting of many queries, fetchChanges, and fetch operations
 *  - doing an incremental fetch of data in response to a push notification
 *  - saving several records due to a user saving a calendar event
 *
 *  You associate CKOperationGroups with CKOperations by setting the CKOperation.group property.  Create a new CKOperationGroup instance for each distinct user action.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@interface CKOperationGroup : NSObject <NSSecureCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/*! @abstract This is an identifier unique to this CKOperationGroup
 *
 *  @discussion This value is chosen by the system, and will be unique to this instance of a CKOperationGroup.  This identifier will be sent to Apple's servers, and can be used to identify any server-side logging associated with this operation group.
 */
@property (nonatomic, readonly, copy) NSString *operationGroupID;
 
/*! @abstract This is the default configuration applied to operations in this operation group.
 *
 *  @discussion If an operation associated with this operation group has its own configuration, then any explicitly-set properties in that operation's configuration will override these default configuration values.  See the example in CKOperation.h
 */
@property (atomic, copy, null_resettable) CKOperationConfiguration *defaultConfiguration;

/*! @abstract Describes the user action attributed to the operation group.
 *
 *  @discussion `name` should describe the type of work being done.  Some examples:
 *  "Initial Fetch"
 *  "Incremental Fetch"
 *  "Saving User-Entered Record"
 *  This string will be sent to Apple servers to provide aggregate reporting for CKOperationGroups and therefore must not include personally identifying data.
*/
@property (atomic, copy, nullable) NSString *name;

/*! @abstract Describes an application-specific "number of elements" associated with the operation group.
 *
 *  @discussion `quantity` is intended to show the app-specific count of items contained within the operation group.  It is your job to assign meaning to this value.  For example, if an app created an operation group to save 3 calendar events the user had created, the app might want to set this to "3".  This value is not shown to your users, it's meant to aid your development and debugging.  This value will be reported in the CloudKit Dashboard's log entries for all operations associated with this operation group.
 */
@property (atomic, assign) NSUInteger quantity;

/*! @abstract Estimated size of traffic being uploaded to the CloudKit Server
 *
 *  @discussion Inform the system how much data you plan on transferring.  Obviously, these won't be exact.  Be as accurate as possible, but even an order-of-magnitude estimate is better than no value.  The system will consult these values when scheduling discretionary network requests (see the description of CKOperationConfiguration -> qualityOfService).
 *  Overestimating your workload means that an operation group issuing discretionary network requests may be delayed until network conditions are good.
 *  Underestimating your workload may cause the system to oversaturate a constrained connection, leading to network failures.
 *  You may update after the CKOperationGroup is created.  If it is increased, then subsequent CKOperations associated with this operation group may be delayed until network conditions are good.
 *  Defaults to CKOperationGroupTransferSizeUnknown
 */
@property (atomic, assign) CKOperationGroupTransferSize expectedSendSize;

/*! @abstract Estimated size of traffic being downloaded from the CloudKit Server
 *
 *  @discussion Inform the system how much data you plan on transferring.  Obviously, these won't be exact.  Be as accurate as possible, but even an order-of-magnitude estimate is better than no value.  The system will consult these values when scheduling discretionary network requests (see the description of CKOperationConfiguration -> qualityOfService).
 *  Overestimating your workload means that an operation group issuing discretionary network requests may be delayed until network conditions are good.
 *  Underestimating your workload may cause the system to oversaturate a constrained connection, leading to network failures.
 *  You may update after the CKOperationGroup is created.  If it is increased, then subsequent CKOperations associated with this operation group may be delayed until network conditions are good.
 *  Defaults to CKOperationGroupTransferSizeUnknown
 */
@property (atomic, assign) CKOperationGroupTransferSize expectedReceiveSize;

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKFetchWebAuthTokenOperation.h
//
//  CKFetchWebAuthTokenOperation.h
//  CloudKit
//
//  Copyright © 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class CKFetchWebAuthTokenOperation
 *
 *  @abstract This operation will fetch a web auth token given an API token obtained from the CloudKit Dashboard for your container
 */
API_AVAILABLE(macos(10.11), ios(9.2), tvos(9.1), watchos(3.0))
@interface CKFetchWebAuthTokenOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithAPIToken:(NSString *)APIToken;

/*! APIToken is expected to be set before you begin this operation. */
@property (nonatomic, copy, nullable) NSString *APIToken;

@property (nonatomic, copy, nullable) void (^fetchWebAuthTokenCompletionBlock)(NSString * _Nullable webAuthToken, NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKFetchRecordZonesOperation.h
//
//  CKFetchRecordZonesOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

@class CKRecordZone, CKRecordZoneID;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKFetchRecordZonesOperation : CKDatabaseOperation

+ (instancetype)fetchAllRecordZonesOperation;

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecordZoneIDs:(NSArray<CKRecordZoneID *> *)zoneIDs;

@property (nonatomic, copy, nullable) NSArray<CKRecordZoneID *> *recordZoneIDs;

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The [NSOperation completionBlock] will also be called if both are set.
 *  If the error is `CKErrorPartialFailure`, the error's userInfo dictionary contains a dictionary of zoneIDs to errors keyed off of `CKPartialErrorsByItemIDKey`.
*/
@property (nonatomic, copy, nullable) void (^fetchRecordZonesCompletionBlock)(NSDictionary<CKRecordZoneID *, CKRecordZone *> * _Nullable recordZonesByZoneID, NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKShare.h
//
//  CKShare.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKRecord.h>
#import <CloudKit/CKShareParticipant.h>

NS_ASSUME_NONNULL_BEGIN

CK_EXTERN CKRecordType const CKRecordTypeShare API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*! Predefined keys in the `CKRecordTypeShare` schema.  They're used by the out of process UI flow to send a share, and as part of the share acceptance flow.  These are optional */

/*! Value is a string.  Example for a recipe sharing app: "Pot Roast" */
CK_EXTERN CKRecordFieldKey const CKShareTitleKey API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));
/*! Value is a data blob suitable to pass into `-[NSImage imageWithData:]` or `-[UIImage imageWithData:]` */
CK_EXTERN CKRecordFieldKey const CKShareThumbnailImageDataKey API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));
/*! Value is a string representing a UTI.  Example for a recipe sharing app: "com.mycompany.recipe" */
CK_EXTERN CKRecordFieldKey const CKShareTypeKey API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*! @class CKShare
 *
 *  @discussion Like CKRecords, CKShares can store arbitrary key-value pairs.  They are modified and fetched in the same manner.
 *  A share, its root record, and its root record's children records will only appear in a participant's CKFetchRecordChangesOperation's results after the share has been accepted by that participant.
 *  Clients have access to the share (and optionally the root record) before accepting a share, via the CKShareMetadata object.  Note that in order to access a root record before accepting a share, you must run a CKFetchShareMetadataOperation requesting the root record.
 *  A CKShare will appear in a CKFetchRecordChangesOperation's results set whenever the participant list is updated.  For that reason, you shouldn't place heavy key-value pairs in it.
 */

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKShare : CKRecord <NSSecureCoding>

/*! When saving a newly created CKShare, you must save the share and its rootRecord in the same CKModifyRecordsOperation batch. */
- (instancetype)initWithRootRecord:(CKRecord *)rootRecord;
- (instancetype)initWithRootRecord:(CKRecord *)rootRecord shareID:(CKRecordID *)shareID NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/*! @abstract Defines what permission a user has when not explicitly added to the share.
 *
 *  @discussion Shares with `publicPermission` more permissive than `CKShareParticipantPermissionNone` can be joined by any user with access to the share's shareURL.
 *  By default, public permission is `CKShareParticipantPermissionNone`.
 *  Changing the public permission to `CKShareParticipantPermissionReadOnly` or `CKShareParticipantPermissionReadWrite` will result in all pending participants being removed.  Already-accepted participants will remain on the share.
 *  Changing the public permission to `CKShareParticipantPermissionNone` will result in all participants being removed from the share.  You may subsequently choose to call `addParticipant:` before saving the share, those participants will be added to the share.
 */
@property (nonatomic, assign) CKShareParticipantPermission publicPermission;

/*! @abstract A URL that can be used to invite participants to this share.
 *
 *  @discussion Only available after share record has been saved to the server.  This url is stable, and is tied to the rootRecord.  That is, if you share a rootRecord, delete the share, and re-share the same rootRecord via a newly created share, that newly created share's url will be identical to the prior share's url
 */
@property (nonatomic, readonly, copy, nullable) NSURL *URL;

/*! @abstract All participants on the share that the current user has permissions to see.
 *
 *  @discussion At the minimum that will include the owner and the current user.
 */
@property (nonatomic, readonly, strong) NSArray<CKShareParticipant *> *participants;

/*! Convenience methods for fetching special users from the participant array */
@property (nonatomic, readonly, strong) CKShareParticipant *owner;
@property (nonatomic, readonly, strong, nullable) CKShareParticipant *currentUserParticipant;

/*! @discussion If a participant with a matching userIdentity already exists, then that existing participant's properties will be updated; no new participant will be added.
 *  In order to modify the list of participants, a share must have publicPermission set to `CKShareParticipantPermissionNone`.  That is, you cannot mix-and-match private users and public users in the same share.
 *  Only certain participant types may be added via this API
 *  @see CKShareParticipantRole
 */
- (void)addParticipant:(CKShareParticipant *)participant;
- (void)removeParticipant:(CKShareParticipant *)participant;

/*! These superclass-provided initializers are not allowed for CKShare */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithRecordType:(CKRecordType)recordType NS_UNAVAILABLE;
- (instancetype)initWithRecordType:(CKRecordType)recordType recordID:(CKRecordID *)recordID NS_UNAVAILABLE;
- (instancetype)initWithRecordType:(CKRecordType)recordType zoneID:(CKRecordZoneID *)zoneID NS_UNAVAILABLE;

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKLocationSortDescriptor.h
//
//  CKLocationSortDescriptor.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CLLocation;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKLocationSortDescriptor : NSSortDescriptor <NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithKey:(NSString *)key relativeLocation:(CLLocation *)relativeLocation NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, copy) CLLocation *relativeLocation;

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKQueryOperation.h
//
//  CKQueryOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDefines.h>
#import <CloudKit/CKDatabaseOperation.h>
#import <CloudKit/CKRecord.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKQueryCursor : NSObject <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

@class CKQuery, CKRecord, CKRecordZoneID;

/*! @discussion Query operations have a dynamically defined maximum number of results.  If the results of a query exceed this max, your completion block will invoked with a cursor.
 *  Issue a new query with that cursor to fetch the next batch of results.
 */
CK_EXTERN const NSUInteger CKQueryOperationMaximumResults API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKQueryOperation : CKDatabaseOperation

/*! Queries invoked within a sharedCloudDatabase must specify a zoneID.  Cross-zone queries are not supported in a sharedCloudDatabase */
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithQuery:(CKQuery *)query;
- (instancetype)initWithCursor:(CKQueryCursor *)cursor;

@property (nonatomic, copy, nullable) CKQuery *query;
@property (nonatomic, copy, nullable) CKQueryCursor *cursor;

/*! @abstract Indicates which record zone to query.
 *
 *  @discussion For query operations constructed using a cursor, this property is ignored and instead will be evaluated in the record zone in which the cursor was originally created.
 */
@property (nonatomic, copy, nullable) CKRecordZoneID *zoneID;

/*! @discussion Defaults to `CKQueryOperationMaximumResults`.
 *  Queries may return fewer than `resultsLimit` in some scenarios:
 *  - There are legitimately fewer than `resultsLimit` number of records matching the query (and visible to the current user).
 *  - During the process of querying and fetching the results, some records were deleted, or became un-readable by the current user.
 *  When determining if there are more records to fetch, always check for the presence of a cursor in `queryCompletionBlock`.
 */
@property (nonatomic, assign) NSUInteger resultsLimit;

/*! @abstract Declares which user-defined keys should be fetched and added to the resulting CKRecords.
 *
 *  @discussion If nil, declares the entire record should be downloaded. If set to an empty array, declares that no user fields should be downloaded.
 *  Defaults to nil.
 */
@property (nonatomic, copy, nullable) NSArray<CKRecordFieldKey> *desiredKeys;

/*! @abstract This block will be called once for every record that is returned as a result of the query.
 *
 *  @discussion The callbacks will happen in the order that the results were sorted in.
 */
@property (nonatomic, copy, nullable) void (^recordFetchedBlock)(CKRecord *record);

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The [NSOperation completionBlock] will also be called if both are set.
 */
@property (nonatomic, copy, nullable) void (^queryCompletionBlock)(CKQueryCursor * _Nullable cursor, NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKDiscoverAllContactsOperation.h
//
//  CKDiscoverAllContactsOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKOperation.h>

@class CKDiscoveredUserInfo;

NS_ASSUME_NONNULL_BEGIN

/*! @class CKDiscoverAllContactsOperation
 *
 *  @abstract Finds all discoverable users in the device's address book. No Contacts access dialog will be displayed
 */
API_DEPRECATED_WITH_REPLACEMENT("CKDiscoverAllUserIdentitiesOperation", macos(10.10, 10.12), ios(8.0, 10.0), watchos(3.0, 3.0))
API_UNAVAILABLE(tvos)
@interface CKDiscoverAllContactsOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

@property (nonatomic, copy, nullable) void (^discoverAllContactsCompletionBlock)(NSArray<CKDiscoveredUserInfo *> * _Nullable userInfos, NSError * _Nullable operationError);

#pragma clang diagnostic pop

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKSubscription.h
//
//  CKSubscription.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKDefines.h>
#import <CloudKit/CKRecord.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CKSubscriptionType) {
    CKSubscriptionTypeQuery                                     = 1,
    CKSubscriptionTypeRecordZone                                = 2,
    CKSubscriptionTypeDatabase API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))   = 3,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(6.0));

@class CKNotificationInfo, CKRecordZoneID;

typedef NSString *CKSubscriptionID;

API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKSubscription : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly, copy) CKSubscriptionID subscriptionID API_AVAILABLE(watchos(6.0));
@property (nonatomic, readonly, assign) CKSubscriptionType subscriptionType API_AVAILABLE(watchos(6.0));

/*! @abstract Describes the notification that will be sent when the subscription fires.
 *
 *  @discussion This property must be set to a non-nil value before saving the `CKSubscription`.
 */
@property (nonatomic, copy, nullable) CKNotificationInfo *notificationInfo API_AVAILABLE(watchos(6.0));

@end


typedef NS_OPTIONS(NSUInteger, CKQuerySubscriptionOptions) {
    CKQuerySubscriptionOptionsFiresOnRecordCreation     = 1 << 0,
    CKQuerySubscriptionOptionsFiresOnRecordUpdate       = 1 << 1,
    CKQuerySubscriptionOptionsFiresOnRecordDeletion     = 1 << 2,
    CKQuerySubscriptionOptionsFiresOnce                 = 1 << 3,
} API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(6.0));

/*! @class CKQuerySubscription
 *
 *  @abstract A subscription that fires whenever a change matching the predicate occurs.
 *
 *  @discussion `CKQuerySubscriptions` are not supported in a `sharedCloudDatabase`
 */
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(6.0))
@interface CKQuerySubscription : CKSubscription <NSSecureCoding, NSCopying>

- (instancetype)initWithRecordType:(CKRecordType)recordType predicate:(NSPredicate *)predicate options:(CKQuerySubscriptionOptions)querySubscriptionOptions;
- (instancetype)initWithRecordType:(CKRecordType)recordType predicate:(NSPredicate *)predicate subscriptionID:(CKSubscriptionID)subscriptionID options:(CKQuerySubscriptionOptions)querySubscriptionOptions NS_DESIGNATED_INITIALIZER;

/*! The record type that this subscription watches */
@property (nonatomic, readonly, copy) CKRecordType recordType;

/*! A predicate that determines when the subscription fires. */
@property (nonatomic, readonly, copy) NSPredicate *predicate;

/*! Optional property.  If set, a query subscription is scoped to only record changes in the indicated zone. */
@property (nonatomic, copy, nullable) CKRecordZoneID *zoneID;

/*! @abstract Options flags describing the firing behavior subscription.
 *
 *  @discussion One of
 *  `CKQuerySubscriptionOptionsFiresOnRecordCreation`,
 *  `CKQuerySubscriptionOptionsFiresOnRecordUpdate`, or
 *  `CKQuerySubscriptionOptionsFiresOnRecordDeletion` must be specified or an `NSInvalidArgumentException` will be thrown.
 */
@property (nonatomic, readonly, assign) CKQuerySubscriptionOptions querySubscriptionOptions;

@end


/*! @class CKRecordZoneSubscription
 *
 *  @abstract A subscription that fires whenever any change happens in the indicated Record Zone.
 *
 *  @discussion The RecordZone must have the capability `CKRecordZoneCapabilityFetchChanges`
 *  `CKRecordZoneSubscriptions` are not supported in a `sharedCloudDatabase`
 */
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(6.0))
@interface CKRecordZoneSubscription : CKSubscription <NSSecureCoding, NSCopying>

- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID;
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID subscriptionID:(CKSubscriptionID)subscriptionID NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, copy) CKRecordZoneID *zoneID;

/*! Optional property. If set, a zone subscription is scoped to record changes for this record type */
@property (nonatomic, copy, nullable) CKRecordType recordType;

@end


/*! @class CKDatabaseSubscription
 *
 *  @abstract A subscription fires whenever any change happens in the database that this subscription was saved in.
 *
 *  @discussion `CKDatabaseSubscription` is only supported in the Private and Shared databases.
 */
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(6.0))
@interface CKDatabaseSubscription : CKSubscription <NSSecureCoding, NSCopying>

- (instancetype)init;
+ (instancetype)new OBJC_SWIFT_UNAVAILABLE("use object initializers instead");
- (instancetype)initWithSubscriptionID:(CKSubscriptionID)subscriptionID NS_DESIGNATED_INITIALIZER;

/*! Optional property. If set, a database subscription is scoped to record changes for this record type */
@property (nonatomic, copy, nullable) CKRecordType recordType;

@end


/*! @class CKNotificationInfo
 *
 *  @discussion The payload of a push notification delivered in the UIApplication `application:didReceiveRemoteNotification:` delegate method contains information about the firing subscription.
 *
 *  Use `+[CKNotification notificationFromRemoteNotificationDictionary:]` to parse that payload.
 *  On tvOS, alerts, badges, sounds, and categories are not handled in push notifications. However, CKSubscriptions remain available to help you avoid polling the server.
 */
API_AVAILABLE(macos(10.10), ios(8.0), watchos(6.0))
@interface CKNotificationInfo : NSObject <NSSecureCoding, NSCopying>

/*! Optional alert string to display in a push notification. */
@property (nonatomic, copy, nullable) NSString *alertBody __TVOS_PROHIBITED;

/*! Instead of a raw alert string, you may optionally specify a key for a localized string in your app's Localizable.strings file. */
@property (nonatomic, copy, nullable) NSString *alertLocalizationKey __TVOS_PROHIBITED;

/*! A list of field names to take from the matching record that is used as substitution variables in a formatted alert string. */
@property (nonatomic, copy, nullable) NSArray<CKRecordFieldKey> *alertLocalizationArgs __TVOS_PROHIBITED;

/*! Optional title of the alert to display in a push notification. */
@property (nonatomic, copy, nullable) NSString *title API_AVAILABLE(macos(10.13), ios(11.0)) __TVOS_PROHIBITED;

/*! Instead of a raw title string, you may optionally specify a key for a localized string in your app's Localizable.strings file. */
@property (nonatomic, copy, nullable) NSString *titleLocalizationKey API_AVAILABLE(macos(10.13), ios(11.0)) __TVOS_PROHIBITED;

/*! A list of field names to take from the matching record that is used as substitution variables in a formatted title string. */
@property (nonatomic, copy, nullable) NSArray<CKRecordFieldKey> *titleLocalizationArgs API_AVAILABLE(macos(10.13), ios(11.0)) __TVOS_PROHIBITED;

/*! Optional subtitle of the alert to display in a push notification. */
@property (nonatomic, copy, nullable) NSString *subtitle API_AVAILABLE(macos(10.13), ios(11.0)) __TVOS_PROHIBITED;

/*! Instead of a raw subtitle string, you may optionally specify a key for a localized string in your app's Localizable.strings file. */
@property (nonatomic, copy, nullable) NSString *subtitleLocalizationKey API_AVAILABLE(macos(10.13), ios(11.0)) __TVOS_PROHIBITED;

/*! A list of field names to take from the matching record that is used as substitution variables in a formatted subtitle string. */
@property (nonatomic, copy, nullable) NSArray<CKRecordFieldKey> *subtitleLocalizationArgs API_AVAILABLE(macos(10.13), ios(11.0)) __TVOS_PROHIBITED;

/*! A key for a localized string to be used as the alert action in a modal style notification. */
@property (nonatomic, copy, nullable) NSString *alertActionLocalizationKey __TVOS_PROHIBITED;

/*! The name of an image in your app bundle to be used as the launch image when launching in response to the notification. */
@property (nonatomic, copy, nullable) NSString *alertLaunchImage __TVOS_PROHIBITED;

/*! The name of a sound file in your app bundle to play upon receiving the notification. */
@property (nonatomic, copy, nullable) NSString *soundName __TVOS_PROHIBITED;

/*! @abstract A list of keys from the matching record to include in the notification payload.
 *
 *  @discussion Only some keys are allowed.  The value types associated with those keys on the server must be one of these classes:
 *  - CKReference
 *  - CLLocation
 *  - NSDate
 *  - NSNumber
 *  - NSString
 */
@property (nonatomic, copy, nullable) NSArray<CKRecordFieldKey> *desiredKeys;

/*! Indicates that the notification should increment the app's badge count. Default value is NO. */
@property (nonatomic, assign) BOOL shouldBadge API_AVAILABLE(tvos(10.0));

/*! @abstract Indicates that the notification should be sent with the "content-available" flag to allow for background downloads in the application.
 *
 *  @discussion Default value is NO.
 */
@property (nonatomic, assign) BOOL shouldSendContentAvailable;

/*! @abstract Indicates that the notification should be sent with the "mutable-content" flag to allow a Notification Service app extension to modify or replace the push payload.
 *
 *  @discussion Default value is NO.
 */
@property (nonatomic, assign) BOOL shouldSendMutableContent API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*! @abstract Optional property for the category to be sent with the push when this subscription fires.
 *
 *  @discussion Categories allow you to present custom actions to the user on your push notifications.
 *
 *  @see UIMutableUserNotificationCategory
 */
@property (nonatomic, copy, nullable) NSString *category API_AVAILABLE(macos(10.11), ios(9.0)) __TVOS_PROHIBITED;

/*! @abstract Optional property specifying a field name to take from the matching record whose value is used as the apns-collapse-id header.
 *
 *  @see APNs Notification API documentation
 */
@property (nonatomic, copy, nullable) NSString *collapseIDKey API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

@end

#pragma mark - Deprecated CKSubscription

/*! Replaced with CKQuerySubscriptionOptions */
typedef NS_OPTIONS(NSUInteger, CKSubscriptionOptions) {
    CKSubscriptionOptionsFiresOnRecordCreation     = 1 << 0,
    CKSubscriptionOptionsFiresOnRecordUpdate       = 1 << 1,
    CKSubscriptionOptionsFiresOnRecordDeletion     = 1 << 2,
    CKSubscriptionOptionsFiresOnce                 = 1 << 3,
} API_DEPRECATED("Use CKQuerySubscriptionOptions instead", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0)) __WATCHOS_PROHIBITED;

@interface CKSubscription (CKSubscriptionDeprecated)

- (instancetype)initWithCoder:(NSCoder *)aDecoder API_DEPRECATED("Init the appropriate CKSubscription subclass", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0)) __WATCHOS_PROHIBITED;

/*! Replaced with CKQuerySubscription */
- (instancetype)initWithRecordType:(CKRecordType)recordType predicate:(NSPredicate *)predicate options:(CKSubscriptionOptions)subscriptionOptions API_DEPRECATED("Use CKQuerySubscription instead", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0)) __WATCHOS_PROHIBITED;
- (instancetype)initWithRecordType:(CKRecordType)recordType predicate:(NSPredicate *)predicate subscriptionID:(CKSubscriptionID)subscriptionID options:(CKSubscriptionOptions)subscriptionOptions API_DEPRECATED("Use CKQuerySubscription instead", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0)) __WATCHOS_PROHIBITED;
@property (nonatomic, readonly, copy, nullable) CKRecordType recordType API_DEPRECATED("Use CKQuerySubscription instead", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0), watchos(6.0, 6.0));
@property (nonatomic, readonly, copy, nullable) NSPredicate *predicate API_DEPRECATED("Use CKQuerySubscription instead", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0)) __WATCHOS_PROHIBITED;

/*! Replaced with CKQuerySubscriptionOptions */
@property (nonatomic, readonly, assign) CKSubscriptionOptions subscriptionOptions API_DEPRECATED("Use CKQuerySubscriptionOptions instead", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0)) __WATCHOS_PROHIBITED;

/*! Replaced with CKRecordZoneSubscription */
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID options:(CKSubscriptionOptions)subscriptionOptions API_DEPRECATED("Use CKRecordZoneSubscription instead", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0)) __WATCHOS_PROHIBITED;
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID subscriptionID:(CKSubscriptionID)subscriptionID options:(CKSubscriptionOptions)subscriptionOptions API_DEPRECATED("Use CKRecordZoneSubscription instead", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0)) __WATCHOS_PROHIBITED;
@property (nonatomic, copy, nullable) CKRecordZoneID *zoneID API_DEPRECATED("Use CKRecordZoneSubscription instead", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0)) __WATCHOS_PROHIBITED;

@end


NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKAcceptSharesOperation.h
//
//  CKAcceptSharesOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKDatabaseOperation.h>

@class CKShare, CKShareMetadata;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKAcceptSharesOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithShareMetadatas:(NSArray<CKShareMetadata *> *)shareMetadatas;

@property (nonatomic, copy, nullable) NSArray<CKShareMetadata *> *shareMetadatas;

/*! Called once for each share metadata that the server processed. If error is nil then the share was successfully accepted. */
@property (nonatomic, copy, nullable) void (^perShareCompletionBlock)(CKShareMetadata *shareMetadata, CKShare * _Nullable acceptedShare, NSError * _Nullable error);

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The [NSOperation completionBlock] will also be called if both are set.
 *  If the error is `CKErrorPartialFailure`, the error's userInfo dictionary contains a dictionary of shareURLs to errors keyed off of `CKPartialErrorsByItemIDKey`.
 *  This call happens as soon as the server has seen all record changes, and may be invoked while the server is processing the side effects of those changes.
 */
@property (nonatomic, copy, nullable) void (^acceptSharesCompletionBlock)(NSError * _Nullable operationError);
@end

NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKModifySubscriptionsOperation.h
//
//  CKModifySubscriptionOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>
#import <CloudKit/CKSubscription.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.10), ios(8.0), watchos(6.0))
@interface CKModifySubscriptionsOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithSubscriptionsToSave:(nullable NSArray<CKSubscription *> *)subscriptionsToSave subscriptionIDsToDelete:(nullable NSArray<CKSubscriptionID> *)subscriptionIDsToDelete;

@property (nonatomic, copy, nullable) NSArray<CKSubscription *> *subscriptionsToSave;
@property (nonatomic, copy, nullable) NSArray<CKSubscriptionID> *subscriptionIDsToDelete;

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The [NSOperation completionBlock] will also be called if both are set.
 *  If the error is `CKErrorPartialFailure`, the error's userInfo dictionary contains a dictionary of subscriptionIDs to errors keyed off of `CKPartialErrorsByItemIDKey`.
*/
@property (nonatomic, copy, nullable) void (^modifySubscriptionsCompletionBlock)(NSArray<CKSubscription *> * _Nullable savedSubscriptions, NSArray<CKSubscriptionID> * _Nullable deletedSubscriptionIDs, NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKShareMetadata.h
//
//  CKShareMetadata.h
//  CloudKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <CloudKit/CKShareParticipant.h>

@class CKShare, CKRecord, CKRecordID;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKShareMetadata : NSObject <NSCopying, NSSecureCoding>

@property (nonatomic, readonly, copy) NSString *containerIdentifier;
@property (nonatomic, readonly, strong) CKShare *share;
@property (nonatomic, readonly, copy) CKRecordID *rootRecordID;

/*! These properties reflect the participant properties of the user invoking CKFetchShareMetadataOperation */
@property (nonatomic, readonly, assign) CKShareParticipantRole participantRole API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));
@property (nonatomic, readonly, assign) CKShareParticipantType participantType API_DEPRECATED_WITH_REPLACEMENT("participantRole", macos(10.12, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0), watchos(3.0, 5.0));
@property (nonatomic, readonly, assign) CKShareParticipantAcceptanceStatus participantStatus;
@property (nonatomic, readonly, assign) CKShareParticipantPermission participantPermission;

@property (nonatomic, readonly, strong) CKUserIdentity *ownerIdentity;

/*! This is only present if the share metadata was returned from a CKFetchShareMetadataOperation with shouldFetchRootRecord set to YES */  
@property (nonatomic, readonly, strong, nullable) CKRecord *rootRecord;

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKRecord.h
//
//  CKRecord.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>
#import <CloudKit/CKAsset.h>
#import <CloudKit/CKReference.h>
#import <CloudKit/CKDefines.h>

@class CKRecordID, CKRecordZoneID;

NS_ASSUME_NONNULL_BEGIN

typedef NSString *CKRecordType;
typedef NSString *CKRecordFieldKey;

/*! Use this constant for the recordType parameter when fetching User Records. */
CK_EXTERN CKRecordType const CKRecordTypeUserRecord API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/*! Use these keys in queries to match on the record's parent or share reference */
CK_EXTERN CKRecordFieldKey const CKRecordParentKey API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));
CK_EXTERN CKRecordFieldKey const CKRecordShareKey API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

@protocol CKRecordValue <NSObject>
@end

API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKRecord : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*! This creates the record in the default zone. */
- (instancetype)initWithRecordType:(CKRecordType)recordType;

- (instancetype)initWithRecordType:(CKRecordType)recordType recordID:(CKRecordID *)recordID;
- (instancetype)initWithRecordType:(CKRecordType)recordType zoneID:(CKRecordZoneID *)zoneID;

@property (nonatomic, readonly, copy) CKRecordType recordType;
@property (nonatomic, readonly, copy) CKRecordID *recordID;

/*! Change tags are updated by the server to a unique value every time a record is modified.  A different change tag necessarily means that the contents of the record are different. */
@property (nonatomic, readonly, copy, nullable) NSString *recordChangeTag;

/*! This is a User Record recordID, identifying the user that created this record. */
@property (nonatomic, readonly, copy, nullable) CKRecordID *creatorUserRecordID;
@property (nonatomic, readonly, copy, nullable) NSDate *creationDate;

/*! This is a User Record recordID, identifying the user that last modified this record. */
@property (nonatomic, readonly, copy, nullable) CKRecordID *lastModifiedUserRecordID;
@property (nonatomic, readonly, copy, nullable) NSDate *modificationDate;

/*! @discussion In addition to `objectForKey:` and `setObject:forKey:`, dictionary-style subscripting (`record[key]` and `record[key] = value`) can be used to get and set values.
 *  Acceptable value object classes are:
 *  - CKReference
 *  - CKAsset
 *  - CLLocation
 *  - NSData
 *  - NSDate
 *  - NSNumber
 *  - NSString
 *  - NSArray containing objects of any of the types above
 *
 *  Any other classes will result in an exception with name `NSInvalidArgumentException`.
 *
 *  Field keys starting with '_' are reserved. Attempting to set a key prefixed with a '_' will result in an error.
 *
 *  Key names roughly match C variable name restrictions. They must begin with an ASCII letter and can contain ASCII letters and numbers and the underscore character.
 *  The maximum key length is 255 characters.
 */
- (nullable __kindof id<CKRecordValue>)objectForKey:(CKRecordFieldKey)key;
- (void)setObject:(nullable __kindof id<CKRecordValue>)object forKey:(CKRecordFieldKey)key;
- (NSArray<CKRecordFieldKey> *)allKeys;

/*! @abstract A special property that returns an array of token generated from all the string field values in the record.
 *
 *  @discussion These tokens have been normalized for the current locale, so they are suitable for performing full-text searches.
 */
- (NSArray<NSString *> *)allTokens;

- (nullable __kindof id<CKRecordValue>)objectForKeyedSubscript:(CKRecordFieldKey)key;
- (void)setObject:(nullable __kindof id<CKRecordValue>)object forKeyedSubscript:(CKRecordFieldKey)key;

/*! A list of keys that have been modified on the local CKRecord instance */
- (NSArray<CKRecordFieldKey> *)changedKeys;

/*! @discussion `CKRecord` supports `NSSecureCoding`.  When you invoke `encodeWithCoder:` on a `CKRecord`, it encodes all its values.  Including the record values you've set.
 *  If you want to store a `CKRecord` instance locally, AND you're already storing the record values locally, that's overkill.  In that case, you can use `encodeSystemFieldsWithCoder:`.  This will encode all parts of a `CKRecord` except the record keys / values you have access to via the `changedKeys` and `objectForKey:` methods.
 *  If you use `initWithCoder:` to reconstitute a `CKRecord` you encoded via `encodeSystemFieldsWithCoder:`, then be aware that
 *  - any record values you had set on the original instance, but had not saved, will be lost
 *  - the reconstituted CKRecord's `changedKeys` will be empty
 */
- (void)encodeSystemFieldsWithCoder:(NSCoder *)coder;

/*! @discussion The share property on a record can be set by creating a share using `-[CKShare initWithRootRecord:]`.
 *
 *  The share property on a record will be removed when the corresponding CKShare is deleted from the server. Send this record in the same batch as the share delete and this record's share property will be updated.
 *
 *  Sharing is only supported in zones with the `CKRecordZoneCapabilitySharing` capability. The default zone does not support sharing.
 *
 *  If any records have a parent reference to this record, they are implicitly shared alongside this record.
 *
 *  Note that records in a parent chain must only exist within one share. If a child record already has a share reference set then you will get a `CKErrorAlreadyShared` error if you try to share any of that record's parents.
 *
 *  Child records can be shared independently, even if they have a common parent.  For example:
 *  Record A has two child records, Record B and Record C.
 *      A
 *     / \
 *    B   C
 *
 *  These configurations are supported:
 *  - Record A part of Share 1, or
 *  - Record B part of Share 1, or
 *  - Record C part of Share 1, or
 *  - Record B part of Share 1, Record C part of Share 2
 *
 *  These configurations are not supported:
 *  Record A part of Share 1, Record B part of Share 2, or
 *    -- This is not allowed because Record B would then be in two shares; Share 1 by being Record A's child, and Share 2
 *  Record A part of Share 1, Record C part of Share 2, or
 *    -- This is not allowed because Record C would then be in two shares; Share 1 by being Record A's child, and Share 2
 *  Record A part of Share 1, Record B part of Share 2, Record C part of Share 3
 *    -- This is not allowed because both Record B and Record C would then each be in two shares.
 *
 *  Whenever possible, it is suggested that you construct your parent hierarchies such that you will only need to share the topmost record of that hierarchy.
 */
@property (nonatomic, readonly, copy, nullable) CKReference *share API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*! @abstract Use a parent reference to teach CloudKit about the hierarchy of your records.
 *
 *  @discussion When a record is shared, all children of that record are also shared.
 *
 *  A parent record reference must have `CKReferenceActionNone` set. You can create a separate reference with `CKReferenceActionDeleteSelf` if you would like your hierarchy cleaned up when the parent record is deleted.
 *
 *  The target of a parent reference must exist at save time - either already on the server, or part of the same `CKModifyRecordsOperation` batch.
 *
 *  You are encouraged to set up the `parent` relationships as part of normal record saves, even if you're not planning on sharing records at this time.
 *  This allows you to share and unshare a hierarchy of records at a later date by only modifying the "top level" record, setting or clearing its `share` reference.
 */
@property (nonatomic, copy, nullable) CKReference *parent API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*! Convenience wrappers around creating a `CKReference` to a parent record. The resulting `CKReference` will have action = `CKReferenceActionNone` */
- (void)setParentReferenceFromRecord:(nullable CKRecord *)parentRecord API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));
- (void)setParentReferenceFromRecordID:(nullable CKRecordID *)parentRecordID API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

@end

@interface NSString (CKRecordValue) <CKRecordValue>
@end

@interface NSNumber (CKRecordValue) <CKRecordValue>
@end

@interface NSArray (CKRecordValue) <CKRecordValue>
@end

@interface NSDate (CKRecordValue) <CKRecordValue>
@end

@interface NSData (CKRecordValue) <CKRecordValue>
@end

@interface CKReference (CKRecordValue) <CKRecordValue>
@end

@interface CKAsset (CKRecordValue) <CKRecordValue>
@end

@interface CLLocation (CKRecordValue) <CKRecordValue>
@end

/*! Formalizes a protocol for getting and setting keys on a CKRecord.  Not intended to be used directly by client code */
API_AVAILABLE(macos(10.11), ios(9.0), watchos(3.0))
@protocol CKRecordKeyValueSetting <NSObject>
- (nullable __kindof id<CKRecordValue>)objectForKey:(CKRecordFieldKey)key;
- (void)setObject:(nullable __kindof id<CKRecordValue>)object forKey:(CKRecordFieldKey)key;
- (nullable __kindof id<CKRecordValue>)objectForKeyedSubscript:(CKRecordFieldKey)key;
- (void)setObject:(nullable __kindof id<CKRecordValue>)object forKeyedSubscript:(CKRecordFieldKey)key;
- (NSArray<CKRecordFieldKey> *)allKeys;
- (NSArray<CKRecordFieldKey> *)changedKeys;
@end

API_AVAILABLE(macos(10.11), ios(9.0), watchos(3.0))
@interface CKRecord(CKRecordKeyValueSettingConformance) <CKRecordKeyValueSetting>
@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKContainer.h
//
//  CKContainer.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKDefines.h>
#import <CloudKit/CKDatabase.h>
#import <CloudKit/CKOperation.h>

NS_ASSUME_NONNULL_BEGIN

@class CKDatabase, CKRecordID, CKUserIdentity, CKShareParticipant, CKDiscoveredUserInfo, CKShare, CKShareMetadata;

/*! Stand-in for the current user's ID; most often used in RecordZoneID->ownerName */
CK_EXTERN NSString * const CKCurrentUserDefaultName API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

CK_EXTERN NSString * const CKOwnerDefaultName API_DEPRECATED_WITH_REPLACEMENT("CKCurrentUserDefaultName", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0), watchos(3.0, 3.0));

/*! @class CKContainer
 *
 *  @abstract A CKContainer, and its CKDatabases, are the main entry points into the CloudKit framework.
 *
 *  @discussion
 *  Several methods in CloudKit accept completion handlers to indicate when they're completed.
 *  All CKOperation subclasses include progress and completion blocks to report significant events in their lifecycles.
 *  Each of these handlers and blocks is invoked on a non-main serial queue.  The receiver is responsible for handling the message on a different queue or thread if it is required.
 */
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKContainer : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*! @abstract Convenience method that uses the calling process' "iCloud.\(application-identifier)" as the container identifier
 *
 *  @discussion
 *  application-identifier is the calling process' `application-identifier` entitlement on iOS / tvOS / watchOS.
 *  application-identifier is the calling process' `com.apple.application-identifier` entitlement on macOS.
 *  On all OSes, if an `com.apple.developer.associated-application-identifier` entitlement is present, its value will be preferred over the `application-identifier` variants.
 */
+ (CKContainer *)defaultContainer;

/*! @abstract Obtain a CKContainer for the given containerIdentifier
 *
 *  @discussion If the application is in production mode (aka, `com.apple.developer.icloud-container-environment` is set to Production in your entitlements plist, and you have no override in `com.apple.developer.icloud-container-development-container-identifiers`), then the production environment is used.
 */
+ (CKContainer *)containerWithIdentifier:(NSString *)containerIdentifier;

@property (nonatomic, readonly, nullable) NSString *containerIdentifier;

- (void)addOperation:(CKOperation *)operation;

@end

/*! @discussion
 *  Database properties:
 *  Records in a public database
 *  - By default are world readable, owner writable.
 *  - Can be locked down by Roles, a process done in the Developer Portal, a web interface.  Roles are not present in the client API.
 *  - Are visible to the application developer via the Developer Portal.
 *  - Do not contribute to the owner's iCloud account storage quota.
 *  Records in a private database
 *  - By default are only owner readable and owner writable.
 *  - Are not visible to the application developer via the Developer Portal.
 *  - Are counted towards the owner's iCloud account storage quota.
 *  Records in a shared database
 *  - Are available to share participants based on the permissions of the enclosing CKShare
 *  - Are not visible to the application developer via the Developer Portal.
 *  - Are counted towards the originating owner's iCloud account storage quota.
 */
@interface CKContainer (Database)

@property (nonatomic, readonly) CKDatabase *privateCloudDatabase;
@property (nonatomic, readonly) CKDatabase *publicCloudDatabase;
@property (nonatomic, readonly) CKDatabase *sharedCloudDatabase API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*! @abstract Convenience methods
 *
 *  @return a database that's pointer-equal to one of the above properties@enum 
 */
- (CKDatabase *)databaseWithDatabaseScope:(CKDatabaseScope)databaseScope API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

@end

/*! @enum CKAccountStatus
 *  @constant CKAccountStatusCouldNotDetermine An error occurred when getting the account status, consult the corresponding NSError.
 *  @constant CKAccountStatusAvailable The iCloud account credentials are available for this application
 *  @constant Parental Controls / Device Management has denied access to iCloud account credentials
 *  @constant No iCloud account is logged in on this device
 */
typedef NS_ENUM(NSInteger, CKAccountStatus) {
    CKAccountStatusCouldNotDetermine                   = 0,
    CKAccountStatusAvailable                           = 1,
    CKAccountStatusRestricted                          = 2,
    CKAccountStatusNoAccount                           = 3,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/*! @abstract This local notification is posted when there has been any change to the logged in iCloud account.
 *
 *  @discussion On receipt, an updated account status should be obtained by calling `accountStatusWithCompletionHandler:`
 */
CK_EXTERN NSString * const CKAccountChangedNotification API_AVAILABLE(macos(10.11), ios(9.0), watchos(3.0));

@interface CKContainer (AccountStatus)

- (void)accountStatusWithCompletionHandler:(void (^)(CKAccountStatus accountStatus, NSError * _Nullable error))completionHandler;

@end

typedef NS_OPTIONS(NSUInteger, CKApplicationPermissions) {
    /*! Allows the user's record in CloudKit to be discoverable via the user's email address */
    CKApplicationPermissionUserDiscoverability         = 1 << 0,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/*! @enum CKApplicationPermissionStatus
 *  @constant CKApplicationPermissionStatusInitialState The user has not made a decision for this application permission.
 *  @constant CKApplicationPermissionStatusCouldNotComplete An error occurred when getting or setting the application permission status, consult the corresponding NSError
 *  @constant CKApplicationPermissionStatusDenied The user has denied this application permission
 *  @constant CKApplicationPermissionStatusGranted The user has granted this application permission
 */
typedef NS_ENUM(NSInteger, CKApplicationPermissionStatus) {
    CKApplicationPermissionStatusInitialState          = 0,
    CKApplicationPermissionStatusCouldNotComplete      = 1,
    CKApplicationPermissionStatusDenied                = 2,
    CKApplicationPermissionStatusGranted               = 3,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

typedef void(^CKApplicationPermissionBlock)(CKApplicationPermissionStatus applicationPermissionStatus, NSError * _Nullable error);

@interface CKContainer (ApplicationPermission)

- (void)statusForApplicationPermission:(CKApplicationPermissions)applicationPermission completionHandler:(CKApplicationPermissionBlock)completionHandler;
- (void)requestApplicationPermission:(CKApplicationPermissions)applicationPermission completionHandler:(CKApplicationPermissionBlock)completionHandler;

@end

@interface CKContainer (UserRecords)

/*! @discussion If there is no iCloud account configured, or if access is restricted, a `CKErrorNotAuthenticated` error will be returned.
 *
 *  This work is treated as having `NSQualityOfServiceUserInitiated` quality of service.
 */
- (void)fetchUserRecordIDWithCompletionHandler:(void (^)(CKRecordID * _Nullable recordID, NSError * _Nullable error))completionHandler;

/*! @abstract Fetches all user records that match an entry in the user's address book.
 *
 *  @discussion `CKDiscoverAllContactsOperation` and `CKDiscoverUserIdentityOperation` are the more configurable, CKOperation-based alternatives to these methods
 */
- (void)discoverAllIdentitiesWithCompletionHandler:(void (^)(NSArray<CKUserIdentity *> * _Nullable userIdentities, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0)) API_UNAVAILABLE(tvos);
- (void)discoverUserIdentityWithEmailAddress:(NSString *)email completionHandler:(void (^)(CKUserIdentity * _Nullable userInfo, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));
- (void)discoverUserIdentityWithPhoneNumber:(NSString *)phoneNumber completionHandler:(void (^)(CKUserIdentity * _Nullable userInfo, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));
- (void)discoverUserIdentityWithUserRecordID:(CKRecordID *)userRecordID completionHandler:(void (^)(CKUserIdentity * _Nullable userInfo, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

- (void)discoverAllContactUserInfosWithCompletionHandler:(void (^)(NSArray<CKDiscoveredUserInfo *> * _Nullable userInfos, NSError * _Nullable error))completionHandler API_DEPRECATED("Use -[CKContainer discoverAllIdentitiesWithCompletionHandler:]", macos(10.10, 10.12), ios(8.0, 10.0), watchos(3.0, 3.0));
- (void)discoverUserInfoWithEmailAddress:(NSString *)email completionHandler:(void (^)(CKDiscoveredUserInfo * _Nullable userInfo, NSError * _Nullable error))completionHandler API_DEPRECATED("Use -[CKContainer discoverUserIdentityWithEmailAddress:completionHandler:]", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0), watchos(3.0, 3.0));
- (void)discoverUserInfoWithUserRecordID:(CKRecordID *)userRecordID completionHandler:(void (^)(CKDiscoveredUserInfo * _Nullable userInfo, NSError * _Nullable error))completionHandler API_DEPRECATED("Use -[CKContainer discoverUserIdentityWithUserRecordID:completionHandler:]", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0), watchos(3.0, 3.0));

@end

@interface CKContainer (Sharing)

/*! @abstract Fetches share participants matching the provided info.
 *
 *  @discussion `CKFetchShareParticipantsOperation` is the more configurable, `CKOperation`-based alternative to these methods.
 */
- (void)fetchShareParticipantWithEmailAddress:(NSString *)emailAddress completionHandler:(void (^)(CKShareParticipant * _Nullable shareParticipant, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));
- (void)fetchShareParticipantWithPhoneNumber:(NSString *)phoneNumber completionHandler:(void (^)(CKShareParticipant * _Nullable shareParticipant, NSError *_Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));
- (void)fetchShareParticipantWithUserRecordID:(CKRecordID *)userRecordID completionHandler:(void (^)(CKShareParticipant *_Nullable shareParticipant, NSError *_Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

- (void)fetchShareMetadataWithURL:(NSURL *)url completionHandler:(void (^)(CKShareMetadata *_Nullable metadata, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));
- (void)acceptShareMetadata:(CKShareMetadata *)metadata completionHandler:(void (^)(CKShare *_Nullable acceptedShare, NSError *_Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

@end

@interface CKContainer (CKLongLivedOperations)
/*! @discussion Long lived CKOperations returned by this call must be started on an operation queue.
 *  Remember to set the callback blocks before starting the operation.
 *  If an operation has already completed against the server, and is subsequently resumed, that operation will replay all of its callbacks from the start of the operation, but the request will not be re-sent to the server.
 *  If a long lived operation is cancelled or finishes completely it is no longer returned by these calls.
 */
- (void)fetchAllLongLivedOperationIDsWithCompletionHandler:(void (^)(NSArray<CKOperationID> * _Nullable outstandingOperationIDs, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(9.3), tvos(9.2), watchos(3.0));
- (void)fetchLongLivedOperationWithID:(CKOperationID)operationID completionHandler:(void (^)(CKOperation * _Nullable outstandingOperation, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(9.3), tvos(9.2), watchos(3.0));
@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKAsset.h
//
//  CKAsset.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKAsset : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*! Initialize an asset to be saved with the content at the given file URL */
- (instancetype)initWithFileURL:(NSURL *)fileURL;

/*! Local file URL where fetched records are cached and saved records originate from. */
@property (nonatomic, readonly, copy, nullable) NSURL *fileURL;

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKUserIdentityLookupInfo.h
//
//  CKUserIdentityLookupInfo.h
//  CloudKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKRecordID;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKUserIdentityLookupInfo : NSObject <NSSecureCoding, NSCopying>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithEmailAddress:(NSString *)emailAddress;
- (instancetype)initWithPhoneNumber:(NSString *)phoneNumber;
- (instancetype)initWithUserRecordID:(CKRecordID *)userRecordID;

+ (NSArray<CKUserIdentityLookupInfo *> *)lookupInfosWithEmails:(NSArray<NSString *> *)emails;
+ (NSArray<CKUserIdentityLookupInfo *> *)lookupInfosWithPhoneNumbers:(NSArray<NSString *> *)phoneNumbers;
+ (NSArray<CKUserIdentityLookupInfo *> *)lookupInfosWithRecordIDs:(NSArray<CKRecordID *> *)recordIDs;

@property (nonatomic, readonly, copy, nullable) NSString *emailAddress;
@property (nonatomic, readonly, copy, nullable) NSString *phoneNumber;
@property (nonatomic, readonly, copy, nullable) CKRecordID *userRecordID;
@end

NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKUserIdentity.h
//
//  CKUserIdentity.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKRecordID, CKUserIdentityLookupInfo;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKUserIdentity : NSObject <NSSecureCoding, NSCopying>
/*! Use `CKDiscoverUserIdentitiesOperation` or `CKFetchShareParticipantsOperation` to create a `CKUserIdentity` */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*! This is the `lookupInfo` you passed in to `CKDiscoverUserIdentitiesOperation` or `CKFetchShareParticipantsOperation` */
@property (nonatomic, readonly, copy, nullable) CKUserIdentityLookupInfo *lookupInfo;

@property (nonatomic, readonly, copy, nullable) NSPersonNameComponents *nameComponents;
@property (nonatomic, readonly, copy, nullable) CKRecordID *userRecordID;

/*! @abstract Link to the Contacts database.
 *
 *  @discussion Identities discovered via `CKDiscoverAllUserIdentitiesOperation` correspond to entries in the local Contacts database.  These identities will have `contactIdentifiers` filled out, which your app may use to get additional information about the contacts that were discovered.  Multiple `contactIdentifiers` may exist for a single discovered user, as multiple contacts may contain the same email addresses or phone numbers.
 *
 *  @return individual, non-unified contacts.
 *
 *  @discussion To transform these identifiers into an array of unified contact identifiers, pass a `CNContact.predicateForContacts(withIdentifiers:)` predicate into `CNContactStore.unifiedContacts(matching:keysToFetch:)`
 *
 *  @see Contacts.framework and CNContact.identifier
 */
@property (nonatomic, readonly, copy) NSArray<NSString *> *contactIdentifiers API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0)) API_UNAVAILABLE(tvos);


@property (nonatomic, readonly, assign) BOOL hasiCloudAccount;

@end

NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKModifyBadgeOperation.h
//
//  CKModifyBadgeOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKOperation.h>

NS_ASSUME_NONNULL_BEGIN
API_DEPRECATED("No longer supported, will cease working at some point in the future", macos(10.10, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0))
@interface CKModifyBadgeOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithBadgeValue:(NSUInteger)badgeValue;

@property (nonatomic, assign) NSUInteger badgeValue;

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The [NSOperation completionBlock] will also be called if both are set.
 */
@property (nonatomic, copy, nullable) void (^modifyBadgeCompletionBlock)(NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKDiscoverAllUserIdentitiesOperation.h
//
//  CKDiscoverAllUserIdentitiesOperation.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKOperation.h>

@class CKUserIdentity;

NS_ASSUME_NONNULL_BEGIN

/*! @class CKDiscoverAllUserIdentitiesOperation
 *
 *  @abstract Finds all discoverable users in the device's contacts database. No Contacts access dialog will be displayed.
 *
 *  @discussion This operation scales linearly with the number of email addresses and phone numbers in the device's address book.  It may take some time to complete.
 */
API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0))
API_UNAVAILABLE(tvos)
@interface CKDiscoverAllUserIdentitiesOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, nullable) void (^userIdentityDiscoveredBlock)(CKUserIdentity *identity);
@property (nonatomic, copy, nullable) void (^discoverAllUserIdentitiesCompletionBlock)(NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
// ==========  CloudKit.framework/Headers/CKFetchRecordZoneChangesOperation.h
//
//  CKFetchRecordZoneChangesOperation.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>
#import <CloudKit/CKServerChangeToken.h>
#import <CloudKit/CKRecord.h>

@class CKFetchRecordZoneChangesConfiguration, CKFetchRecordZoneChangesOptions;

NS_ASSUME_NONNULL_BEGIN

/*! @abstract This operation will fetch records changes across the given record zones
 *
 *  @discussion For each `previousServerChangeToken` passed in with a `CKFetchRecordZoneChangesConfiguration`, only records that have changed since that anchor will be fetched.
 *  If this is your first fetch of a zone or if you wish to re-fetch all records within a zone, do not include a `previousServerChangeToken`.
 *  Change tokens are opaque tokens and clients should not infer any behavior based on their content.
 */
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKFetchRecordZoneChangesOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecordZoneIDs:(NSArray<CKRecordZoneID *> *)recordZoneIDs configurationsByRecordZoneID:(nullable NSDictionary<CKRecordZoneID *, CKFetchRecordZoneChangesConfiguration *> *)configurationsByRecordZoneID;

@property (nonatomic, copy, nullable) NSArray<CKRecordZoneID *> *recordZoneIDs;
@property (nonatomic, copy, nullable) NSDictionary<CKRecordZoneID *, CKFetchRecordZoneChangesConfiguration *> *configurationsByRecordZoneID;

/*! @abstract Determines if the opertaion should fetch all changes from the server before completing.
 *
 *  @discussion When set to YES, this operation will send repeated requests to the server until all record changes have been fetched. `recordZoneChangeTokensUpdatedBlock` will be invoked periodically, to give clients an updated change token so that already-fetched record changes don't need to be re-fetched on a subsequent operation. `recordZoneFetchCompletionBlock` will only be called once and `moreComing` will always be NO.
 *
 *  When set to NO, it is the responsibility of the caller to issue subsequent fetch-changes operations when `moreComing` is YES in a `recordZoneFetchCompletionBlock` invocation.
 *
 *  `fetchAllChanges` is YES by default
 */
@property (nonatomic, assign) BOOL fetchAllChanges;

@property (nonatomic, copy, nullable) void (^recordChangedBlock)(CKRecord *record);
@property (nonatomic, copy, nullable) void (^recordWithIDWasDeletedBlock)(CKRecordID *recordID, CKRecordType recordType);

/*! @discussion Clients are responsible for saving this per-recordZone `serverChangeToken` and passing it in to the next call to `CKFetchRecordZoneChangesOperation`.
 *  Note that a fetch can fail partway. If that happens, an updated change token may be returned in this block so that already fetched records don't need to be re-downloaded on a subsequent operation.
 *  `recordZoneChangeTokensUpdatedBlock` will not be called after the last batch of changes in a zone; the `recordZoneFetchCompletionBlock` block will be called instead.
 *  The `clientChangeTokenData` from the most recent `CKModifyRecordsOperation` issued on this zone is also returned, or nil if none was provided.
 *  If the server returns a `CKErrorChangeTokenExpired` error, the `serverChangeToken` used for this record zone when initting this operation was too old and the client should toss its local cache and re-fetch the changes in this record zone starting with a nil `serverChangeToken`.
 *  `recordZoneChangeTokensUpdatedBlock` will not be called if `fetchAllChanges` is NO.
 */
@property (nonatomic, copy, nullable) void (^recordZoneChangeTokensUpdatedBlock)(CKRecordZoneID *recordZoneID, CKServerChangeToken * _Nullable serverChangeToken, NSData * _Nullable clientChangeTokenData);
@property (nonatomic, copy, nullable) void (^recordZoneFetchCompletionBlock)(CKRecordZoneID *recordZoneID, CKServerChangeToken * _Nullable serverChangeToken, NSData * _Nullable clientChangeTokenData, BOOL moreComing, NSError * _Nullable recordZoneError);

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion `serverChangeToken`s previously returned via a `recordZoneChangeTokensUpdatedBlock` or `recordZoneFetchCompletionBlock` invocation, along with the record changes that preceded it, are valid even if there is a subsequent `operationError`
 */
@property (nonatomic, copy, nullable) void (^fetchRecordZoneChangesCompletionBlock)(NSError * _Nullable operationError);

@end

@interface CKFetchRecordZoneChangesOperation(Deprecated)

- (instancetype)initWithRecordZoneIDs:(NSArray<CKRecordZoneID *> *)recordZoneIDs optionsByRecordZoneID:(nullable NSDictionary<CKRecordZoneID *, CKFetchRecordZoneChangesOptions *> *)optionsByRecordZoneID
API_DEPRECATED_WITH_REPLACEMENT("initWithRecordZoneIDs:configurationsByRecordZoneID:", macos(10.12, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0), watchos(3.0, 5.0));

@property (nonatomic, copy, nullable) NSDictionary<CKRecordZoneID *, CKFetchRecordZoneChangesOptions *> *optionsByRecordZoneID
API_DEPRECATED_WITH_REPLACEMENT("configurationsByRecordZoneID", macos(10.12, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0), watchos(3.0, 5.0));
@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0))
@interface CKFetchRecordZoneChangesConfiguration : NSObject <NSSecureCoding, NSCopying>

@property (nonatomic, copy, nullable) CKServerChangeToken *previousServerChangeToken;

@property (nonatomic, assign) NSUInteger resultsLimit;

/*! @abstract Declares which user-defined keys should be fetched and added to the resulting CKRecords.
 *
 *  @discussion If nil, declares the entire record should be downloaded. If set to an empty array, declares that no user fields should be downloaded.
 *  Defaults to nil.
 */
@property (nonatomic, copy, nullable) NSArray<CKRecordFieldKey> *desiredKeys;
@end



API_DEPRECATED_WITH_REPLACEMENT("CKFetchRecordZoneChangesConfiguration", macos(10.12, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0), watchos(3.0, 5.0))
@interface CKFetchRecordZoneChangesOptions : NSObject <NSSecureCoding, NSCopying>
@property (nonatomic, copy, nullable) CKServerChangeToken *previousServerChangeToken;
@property (nonatomic, assign) NSUInteger resultsLimit;
@property (nonatomic, copy, nullable) NSArray<CKRecordFieldKey> *desiredKeys;
@end
NS_ASSUME_NONNULL_END
