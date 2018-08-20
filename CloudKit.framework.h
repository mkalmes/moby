// ==========  CloudKit.framework/Headers/CKDatabase.h
//
//  CKDatabase.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKDatabaseOperation, CKRecord, CKRecordID, CKRecordZone, CKRecordZoneID, CKQuery, CKSubscription;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKDatabase : NSObject
- (instancetype)init NS_UNAVAILABLE;
- (void)addOperation:(CKDatabaseOperation *)operation;
@end

@interface CKDatabase (ConvenienceMethods)

/* Convenience APIs
   These calls operate on a single item in the default zone and allow for simple operations.
   If you'd like to batch your requests, add dependencies between requests, set priorities,
   or schedule operations on your own queue, take a look at the corresponding CKOperation.
   This work is treated as having NSQualityOfServiceUserInitiated quality of service.
 */

#pragma mark Record Convenience Methods
/* CKFetchRecordsOperation and CKModifyRecordsOperation are the more configurable,
 CKOperation-based alternatives to these methods */
- (void)fetchRecordWithID:(CKRecordID *)recordID completionHandler:(void (^)(CKRecord * __nullable record, NSError * __nullable error))completionHandler;
- (void)saveRecord:(CKRecord *)record completionHandler:(void (^)(CKRecord * __nullable record, NSError * __nullable error))completionHandler;
- (void)deleteRecordWithID:(CKRecordID *)recordID completionHandler:(void (^)(CKRecordID * __nullable recordID, NSError * __nullable error))completionHandler;

#pragma mark Query Convenience Method
/* CKQueryOperation is the more configurable, CKOperation-based
 alternative to this method */
- (void)performQuery:(CKQuery *)query inZoneWithID:(nullable CKRecordZoneID *)zoneID completionHandler:(void (^)(NSArray <CKRecord *> * __nullable results, NSError * __nullable error))completionHandler;

#pragma mark Record Zone Convenience Methods
/* CKFetchRecordZonesOperation and CKModifyRecordZonesOperation are the more configurable,
 CKOperation-based alternatives to these methods */
- (void)fetchAllRecordZonesWithCompletionHandler:(void (^)(NSArray <CKRecordZone *> * __nullable zones, NSError * __nullable error))completionHandler;
- (void)fetchRecordZoneWithID:(CKRecordZoneID *)zoneID completionHandler:(void (^)(CKRecordZone * __nullable zone, NSError * __nullable error))completionHandler;
- (void)saveRecordZone:(CKRecordZone *)zone completionHandler:(void (^)(CKRecordZone * __nullable zone, NSError * __nullable error))completionHandler;
- (void)deleteRecordZoneWithID:(CKRecordZoneID *)zoneID completionHandler:(void (^)(CKRecordZoneID * __nullable zoneID, NSError * __nullable error))completionHandler;

#pragma mark Subscription Convenience Methods
/* CKFetchSubscriptionsOperation and CKModifySubscriptionsOperation are the more configurable,
 CKOperation-based alternative to these methods */
- (void)fetchSubscriptionWithID:(NSString *)subscriptionID completionHandler:(void (^)(CKSubscription * __nullable subscription, NSError * __nullable error))completionHandler;
- (void)fetchAllSubscriptionsWithCompletionHandler:(void (^)(NSArray <CKSubscription *> * __nullable subscriptions, NSError * __nullable error))completionHandler;
- (void)saveSubscription:(CKSubscription *)subscription completionHandler:(void (^)(CKSubscription * __nullable subscription, NSError * __nullable error))completionHandler;
- (void)deleteSubscriptionWithID:(NSString *)subscriptionID completionHandler:(void (^)(NSString * __nullable subscriptionID, NSError * __nullable error))completionHandler;

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

@class CKSubscription;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKFetchSubscriptionsOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;

+ (instancetype)fetchAllSubscriptionsOperation;

- (instancetype)initWithSubscriptionIDs:(NSArray <NSString *> *)subscriptionIDs;

@property (nonatomic, copy, nullable) NSArray <NSString *> *subscriptionIDs;

/*  This block is called when the operation completes.
    The [NSOperation completionBlock] will also be called if both are set.
    If the error is CKErrorPartialFailure, the error's userInfo dictionary contains
    a dictionary of subscriptionID to errors keyed off of CKPartialErrorsByItemIDKey.
*/
@property (nonatomic, copy, nullable) void (^fetchSubscriptionCompletionBlock)(NSDictionary <NSString *, CKSubscription *> * __nullable subscriptionsBySubscriptionID, NSError * __nullable operationError);

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

CK_EXTERN NSString * const CKErrorDomain NS_AVAILABLE(10_10, 8_0);

CK_EXTERN NSString * const CKPartialErrorsByItemIDKey NS_AVAILABLE(10_10, 8_0);

/* If the server rejects a record save because it has been modified since the last time it was read, 
   a CKErrorServerRecordChanged error will be returned and it will contain versions of the record 
   in its userInfo dictionary. Apply your custom conflict resolution logic to the server record (CKServerRecordKey) 
   and attempt a save of that record. */
CK_EXTERN NSString * const CKRecordChangedErrorAncestorRecordKey NS_AVAILABLE(10_10, 8_0);
CK_EXTERN NSString * const CKRecordChangedErrorServerRecordKey NS_AVAILABLE(10_10, 8_0);
CK_EXTERN NSString * const CKRecordChangedErrorClientRecordKey NS_AVAILABLE(10_10, 8_0);

/* On CKErrorServiceUnavailable or CKErrorRequestRateLimited errors the userInfo dictionary 
   may contain a NSNumber instance that specifies the period of time in seconds after
   which the client may retry the request.
 */
CK_EXTERN NSString * const CKErrorRetryAfterKey NS_AVAILABLE(10_10, 8_0);

typedef NS_ENUM(NSInteger, CKErrorCode) {
    CKErrorInternalError           = 1,  /* CloudKit.framework encountered an error.  This is a non-recoverable error. */
    CKErrorPartialFailure          = 2,  /* Some items failed, but the operation succeeded overall */
    CKErrorNetworkUnavailable      = 3,  /* Network not available */
    CKErrorNetworkFailure          = 4,  /* Network error (available but CFNetwork gave us an error) */
    CKErrorBadContainer            = 5,  /* Un-provisioned or unauthorized container. Try provisioning the container before retrying the operation. */
    CKErrorServiceUnavailable      = 6,  /* Service unavailable */
    CKErrorRequestRateLimited      = 7,  /* Client is being rate limited */
    CKErrorMissingEntitlement      = 8,  /* Missing entitlement */
    CKErrorNotAuthenticated        = 9,  /* Not authenticated (writing without being logged in, no user record) */
    CKErrorPermissionFailure       = 10, /* Access failure (save or fetch) */
    CKErrorUnknownItem             = 11, /* Record does not exist */
    CKErrorInvalidArguments        = 12, /* Bad client request (bad record graph, malformed predicate) */
    CKErrorResultsTruncated        = 13, /* Query results were truncated by the server */
    CKErrorServerRecordChanged     = 14, /* The record was rejected because the version on the server was different */
    CKErrorServerRejectedRequest   = 15, /* The server rejected this request.  This is a non-recoverable error */
    CKErrorAssetFileNotFound       = 16, /* Asset file was not found */
    CKErrorAssetFileModified       = 17, /* Asset file content was modified while being saved */
    CKErrorIncompatibleVersion     = 18, /* App version is less than the minimum allowed version */
    CKErrorConstraintViolation     = 19, /* The server rejected the request because there was a conflict with a unique field. */
    CKErrorOperationCancelled      = 20, /* A CKOperation was explicitly cancelled */
    CKErrorChangeTokenExpired      = 21, /* The previousServerChangeToken value is too old and the client must re-sync from scratch */
    CKErrorBatchRequestFailed      = 22, /* One of the items in this batch operation failed in a zone with atomic updates, so the entire batch was rejected. */
    CKErrorZoneBusy                = 23, /* The server is too busy to handle this zone operation. Try the operation again in a few seconds. */
    CKErrorBadDatabase             = 24, /* Operation could not be completed on the given database. Likely caused by attempting to modify zones in the public database. */
    CKErrorQuotaExceeded           = 25, /* Saving a record would exceed quota */
    CKErrorZoneNotFound            = 26, /* The specified zone does not exist on the server */
    CKErrorLimitExceeded           = 27, /* The request to the server was too large. Retry this request as a smaller batch. */
    CKErrorUserDeletedZone         = 28, /* The user deleted this zone through the settings UI. Your client should either remove its local data or prompt the user before attempting to re-upload any data to this zone. */
} NS_ENUM_AVAILABLE(10_10, 8_0);

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
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKDiscoverUserInfosOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithEmailAddresses:(nullable NSArray <NSString *> *)emailAddresses userRecordIDs:(nullable NSArray <CKRecordID *> *)userRecordIDs;

@property (nonatomic, copy, nullable) NSArray <NSString *> *emailAddresses;
@property (nonatomic, copy, nullable) NSArray <CKRecordID *> *userRecordIDs;

/*  This block is called when the operation completes.
    The [NSOperation completionBlock] will also be called if both are set. */
@property (nonatomic, copy, nullable) void (^discoverUserInfosCompletionBlock)(NSDictionary <NSString *, CKDiscoveredUserInfo *> * __nullable emailsToUserInfos, NSDictionary <CKRecordID *, CKDiscoveredUserInfo *> * __nullable userRecordIDsToUserInfos, NSError * __nullable operationError);

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

@class CKRecordID, CKRecordZoneID;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKNotificationID : NSObject <NSCopying, NSSecureCoding>
@end

typedef NS_ENUM(NSInteger, CKNotificationType) {
    CKNotificationTypeQuery            = 1,
    CKNotificationTypeRecordZone       = 2,
    CKNotificationTypeReadNotification = 3, /* Indicates a notification that a client had previously marked as read. */
} NS_ENUM_AVAILABLE(10_10, 8_0);

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKNotification : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)notificationFromRemoteNotificationDictionary:(NSDictionary <NSString *, NSObject *> *)notificationDictionary;

/* When you instantiate a CKNotification from a remote notification dictionary, you will get back a concrete
 subclass defined below.  Use the type of notification to avoid -isKindOfClass: checks */
@property (nonatomic, readonly, assign) CKNotificationType notificationType;

@property (nonatomic, readonly, copy, nullable) CKNotificationID *notificationID;

@property (nonatomic, readonly, copy, nullable) NSString *containerIdentifier;

/* push notifications have a limited size.  In some cases, CloudKit servers may not be able to send you a full
 CKNotification's worth of info in one push.  In those cases, isPruned returns YES.  The order in which we'll
 drop properties is defined in each CKNotification subclass below.
 The CKNotification can be obtained in full via a CKFetchNotificationChangesOperation */
@property (nonatomic, readonly, assign) BOOL isPruned;


/* These keys are parsed out of the 'aps' payload from a remote notification dictionary */

/* Optional alert string to display in a push notification. */
@property (nonatomic, readonly, copy, nullable) NSString *alertBody;
/* Instead of a raw alert string, you may optionally specify a key for a localized string in your app's Localizable.strings file. */
@property (nonatomic, readonly, copy, nullable) NSString *alertLocalizationKey;
/* A list of field names to take from the matching record that is used as substitution variables in a formatted alert string. */
@property (nonatomic, readonly, copy, nullable) NSArray <NSString *> *alertLocalizationArgs;
/* A key for a localized string to be used as the alert action in a modal style notification. */
@property (nonatomic, readonly, copy, nullable) NSString *alertActionLocalizationKey;
/* The name of an image in your app bundle to be used as the launch image when launching in response to the notification. */
@property (nonatomic, readonly, copy, nullable) NSString *alertLaunchImage;

/* The number to display as the badge of the application icon */
@property (nonatomic, readonly, copy, nullable) NSNumber *badge;
/* The name of a sound file in your app bundle to play upon receiving the notification. */
@property (nonatomic, readonly, copy, nullable) NSString *soundName;

/* The ID of the subscription that caused this notification to fire */
@property (nonatomic, readonly, copy, nullable) NSString *subscriptionID NS_AVAILABLE(10_11, 9_0);

/* The category for user-initiated actions in the notification */
@property (nonatomic, readonly, copy, nullable) NSString *category NS_AVAILABLE(10_11, 9_0);

@end

/* notificationType == CKNotificationTypeQuery
 When properties must be dropped (see isPruned), here's the order of importance.  The most important properties are first,
 they'll be the last ones to be dropped.
 - notificationID
 - badge
 - alertLocalizationKey
 - alertLocalizationArgs
 - alertBody
 - alertActionLocalizationKey
 - alertLaunchImage
 - soundName
 - desiredKeys
 - queryNotificationReason
 - recordID
 - containerIdentifier
 */

typedef NS_ENUM(NSInteger, CKQueryNotificationReason) {
    CKQueryNotificationReasonRecordCreated = 1,
    CKQueryNotificationReasonRecordUpdated,
    CKQueryNotificationReasonRecordDeleted,
} NS_ENUM_AVAILABLE(10_10, 8_0);

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKQueryNotification : CKNotification

@property (nonatomic, readonly, assign) CKQueryNotificationReason queryNotificationReason;

/* A set of key->value pairs for creates and updates.  You request the server fill out this property via the
 "desiredKeys" property of CKNotificationInfo */
@property (nonatomic, readonly, copy, nullable) NSDictionary <NSString *, __kindof id <CKRecordValue>> *recordFields;

@property (nonatomic, readonly, copy, nullable) CKRecordID *recordID;

/* If YES, this record is in the public database.  Else, it's in the private database */
@property (nonatomic, readonly, assign) BOOL isPublicDatabase;

@end


/* notificationType == CKNotificationTypeRecordZone
 When properties must be dropped (see isPruned), here's the order of importance.  The most important properties are first,
 they'll be the last ones to be dropped.
 - notificationID
 - badge
 - alertLocalizationKey
 - alertLocalizationArgs
 - alertBody
 - alertActionLocalizationKey
 - alertLaunchImage
 - soundName
 - recordZoneID
 - containerIdentifier
 */

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKRecordZoneNotification : CKNotification

@property (nonatomic, readonly, copy, nullable) CKRecordZoneID *recordZoneID;

@end
NS_ASSUME_NONNULL_END// ==========  CloudKit.framework/Headers/CKServerChangeToken.h
//
//  CKServerChangeToken.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKServerChangeToken : NSObject <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
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

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKModifyRecordZonesOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecordZonesToSave:(nullable NSArray <CKRecordZone *> *)recordZonesToSave recordZoneIDsToDelete:(nullable NSArray <CKRecordZoneID *> *)recordZoneIDsToDelete;

@property (nonatomic, copy, nullable) NSArray <CKRecordZone *> *recordZonesToSave;
@property (nonatomic, copy, nullable) NSArray <CKRecordZoneID *> *recordZoneIDsToDelete;

/*  This block is called when the operation completes.
 The [NSOperation completionBlock] will also be called if both are set.
 If the error is CKErrorPartialFailure, the error's userInfo dictionary contains
 a dictionary of recordZoneIDs to errors keyed off of CKPartialErrorsByItemIDKey.
 This call happens as soon as the server has
 seen all record changes, and may be invoked while the server is processing the side effects
 of those changes.
 */
@property (nonatomic, copy, nullable) void (^modifyRecordZonesCompletionBlock)(NSArray <CKRecordZone *> * __nullable savedRecordZones, NSArray <CKRecordZoneID *> * __nullable deletedRecordZoneIDs, NSError * __nullable operationError);

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

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKQuery : NSObject <NSSecureCoding, NSCopying>

/*
 
 Only AND compound predicates are allowed.
 
 Key names must begin with either an upper or lower case character ([a-zA-Z]) and may be followed by characters, numbers, or underscores ([0-9a-zA-Z_]). Keypaths may only resolve to the currently evaluated object, so the '.' character is not allowed in key names.
 
 A limited subset of classes are allowed as predicate arguments:
    NSString
    NSDate
    NSData
    NSNumber
    NSArray
    CKReference
    CKRecord
    CLLocation
 
 Any other class as an argument will result in an error when executing the query.

 */

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/* Use [NSPredicate predicateWithFormat:@"TRUEPREDICATE"] if you want to query for all records of a given type. */
- (instancetype)initWithRecordType:(NSString *)recordType predicate:(NSPredicate *)predicate NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, copy) NSString *recordType;
@property (nonatomic, readonly, copy) NSPredicate *predicate;

@property (nonatomic, copy, nullable) NSArray <NSSortDescriptor *> *sortDescriptors;

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
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKFetchNotificationChangesOperation : CKOperation

/* This operation will fetch all notification changes.
   If a change anchor from a previous CKFetchNotificationChangesOperation is passed in, only the notifications that have changed
    since that anchor will be fetched.
   If this is your first fetch, pass nil for the change anchor.
   Change anchors are opaque tokens and clients should not infer any behavior based on their content. */
- (instancetype)initWithPreviousServerChangeToken:(nullable CKServerChangeToken *)previousServerChangeToken;

@property (nonatomic, copy, nullable) CKServerChangeToken *previousServerChangeToken;

@property (nonatomic, assign) NSUInteger resultsLimit;

/* Will be set before fetchNotificationChangesCompletionBlock is called. If moreComing is true then the server wasn't able to return all the changes in this response.
 Another CKFetchNotificationChangesOperation operation should be run with the updated serverChangeToken token from this operation. */
@property (nonatomic, readonly) BOOL moreComing;

@property (nonatomic, copy, nullable) void (^notificationChangedBlock)(CKNotification *notification);

/* Clients are responsible for saving the change token at the end of the operation and passing it in to the next call to CKFetchNotificationChangesOperation.
   Note that a fetch can fail partway. If that happens, an updated change token may be returned in the completion
    block so that already fetched notifications don't need to be re-downloaded on a subsequent operation.
   If the server returns a CKErrorChangeTokenExpired error, the previousServerChangeToken value was too old and the client should toss its local cache and
   re-fetch notification changes starting with a nil previousServerChangeToken. */
@property (nonatomic, copy, nullable) void (^fetchNotificationChangesCompletionBlock)(CKServerChangeToken * __nullable serverChangeToken, NSError * __nullable operationError);

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
#import <CloudKit/CKSubscription.h>
#import <CloudKit/CKDiscoveredUserInfo.h>

#import <CloudKit/CKOperation.h>
#import <CloudKit/CKDatabaseOperation.h>
#import <CloudKit/CKModifyRecordsOperation.h>
#import <CloudKit/CKDiscoverAllContactsOperation.h>
#import <CloudKit/CKDiscoverUserInfosOperation.h>
#import <CloudKit/CKFetchRecordsOperation.h>
#import <CloudKit/CKFetchRecordChangesOperation.h>
#import <CloudKit/CKQueryOperation.h>
#import <CloudKit/CKModifyBadgeOperation.h>
#import <CloudKit/CKFetchNotificationChangesOperation.h>
#import <CloudKit/CKMarkNotificationsReadOperation.h>
#import <CloudKit/CKFetchSubscriptionsOperation.h>
#import <CloudKit/CKModifySubscriptionsOperation.h>
#import <CloudKit/CKModifyRecordZonesOperation.h>
#import <CloudKit/CKFetchRecordZonesOperation.h>
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
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKMarkNotificationsReadOperation : CKOperation

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithNotificationIDsToMarkRead:(NSArray <CKNotificationID *> *)notificationIDs NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy) NSArray <CKNotificationID *> *notificationIDs;

@property (nonatomic, copy, nullable) void (^markNotificationsReadCompletionBlock)(NSArray <CKNotificationID *> * __nullable notificationIDsMarkedRead, NSError * __nullable operationError);

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
typedef NS_ENUM(NSUInteger, CKReferenceAction) {
    /* When the referred record is deleted, this record is unchanged, and has a dangling pointer */
    CKReferenceActionNone       = 0,
    /* When the referred record is deleted then this record is also deleted. */
    CKReferenceActionDeleteSelf = 1,
} NS_ENUM_AVAILABLE(10_10, 8_0);


NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKReference : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;

/* It is acceptable to relate two records that have not yet been uploaded to the server, but those records must be uploaded to the server in the same operation.
 If a record references a record that does not exist on the server and is not in the current save operation it will result in an error. */
- (instancetype)initWithRecordID:(CKRecordID *)recordID action:(CKReferenceAction)action NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecord:(CKRecord *)record action:(CKReferenceAction)action;

@property (nonatomic, readonly, assign) CKReferenceAction referenceAction;

@property (nonatomic, readonly, copy) CKRecordID *recordID;

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

#import <os/activity.h>

@class CKContainer;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKOperation : NSOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;

- (os_activity_t)activityStart;


/* If no container is set, [CKContainer defaultContainer] is used */
@property (nonatomic, strong, nullable) CKContainer *container;

/*
 CKOperations behave differently depending on how you set qualityOfService:

 NSQualityOfServiceUserInteractive
    Network requests are non-discretionary
 NSQualityOfServiceUserInitiated
    Network requests are non-discretionary
 NSQualityOfServiceUtility
    The system marks your network requests as discretionary when the user is not using your app
 NSQualityOfServiceBackground
    Network requests are discretionary

 CKOperations have a default qualityOfService of NSQualityOfServiceBackground.

 */

/* If set, network traffic will happen on a background NSURLSession.
 Defaults to (NSOperationQualityOfServiceBackground == self.qualityOfService) */
@property (nonatomic, assign) BOOL usesBackgroundSession NS_DEPRECATED(10_10, 10_11, 8_0, 9_0, "Set qualityOfService to NSQualityOfServiceUtility or NSQualityOfServiceBackground");

/* Defaults to YES */
@property (nonatomic, assign) BOOL allowsCellularAccess;

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

@class CKRecord, CKRecordID, CKRecordZoneID;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKFetchRecordChangesOperation : CKDatabaseOperation

/* This operation will fetch records changes in the given record zone.

   If a change anchor from a previous CKFetchRecordChangesOperation is passed in, only the records that have changed
    since that anchor will be fetched.

   If this is your first fetch or if you wish to re-fetch all records, pass nil for the change anchor.

   Change anchors are opaque tokens and clients should not infer any behavior based on their content. */
- (instancetype)initWithRecordZoneID:(CKRecordZoneID *)recordZoneID previousServerChangeToken:(nullable CKServerChangeToken *)previousServerChangeToken;

@property (nonatomic, copy) CKRecordZoneID *recordZoneID;
@property (nonatomic, copy, nullable) CKServerChangeToken *previousServerChangeToken;

@property (nonatomic, assign) NSUInteger resultsLimit;

/* Declares which user-defined keys should be fetched and added to the resulting CKRecords.  If nil, declares the entire record should be downloaded. If set to an empty array, declares that no user fields should be downloaded.  Defaults to nil. */
@property (nonatomic, copy, nullable) NSArray <NSString *> *desiredKeys;

@property (nonatomic, copy, nullable) void (^recordChangedBlock)(CKRecord *record);
@property (nonatomic, copy, nullable) void (^recordWithIDWasDeletedBlock)(CKRecordID *recordID);

/* Will be set before fetchRecordChangesCompletionBlock is called. If moreComing is true then the server wasn't able to return all the changes in this response.
    Another CKFetchRecordChangesOperation operation should be run with the updated serverChangeToken token from this operation. */
@property (nonatomic, readonly) BOOL moreComing;

/* Clients are responsible for saving the change token at the end of the operation and passing it in to the next call to CKFetchRecordChangesOperation.
   Note that a fetch can fail partway. If that happens, an updated change token may be returned in the completion
    block so that already fetched records don't need to be re-downloaded on a subsequent operation.
   The clientChangeToken from the most recent CKModifyRecordsOperation is also returned, or nil if none was provided. 
   If the server returns a CKErrorChangeTokenExpired error, the previousServerChangeToken value was too old and the client should toss its local cache and 
    re-fetch the changes in this record zone starting with a nil previousServerChangeToken. */
@property (nonatomic, copy, nullable) void (^fetchRecordChangesCompletionBlock)(CKServerChangeToken * __nullable serverChangeToken, NSData * __nullable clientChangeTokenData, NSError * __nullable operationError);

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
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKRecordZoneID : NSObject <NSSecureCoding, NSCopying>

/* Zone names must be 255 characters or less. Most UTF-8 characters are valid. */
- (instancetype)init NS_UNAVAILABLE;
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

@class CKRecord, CKRecordID;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKFetchRecordsOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecordIDs:(NSArray <CKRecordID *> *)recordIDs;

+ (instancetype)fetchCurrentUserRecordOperation;

@property (nonatomic, copy, nullable) NSArray <CKRecordID *> *recordIDs;

/* Declares which user-defined keys should be fetched and added to the resulting CKRecords.  If nil, declares the entire record should be downloaded. If set to an empty array, declares that no user fields should be downloaded.  Defaults to nil. */
@property (nonatomic, copy, nullable) NSArray <NSString *> *desiredKeys;

/* Called repeatedly during transfer. */
@property (nonatomic, copy, nullable) void (^perRecordProgressBlock)(CKRecordID *recordID, double progress);
/* Called on success or failure for each record. */
@property (nonatomic, copy, nullable) void (^perRecordCompletionBlock)(CKRecord * __nullable record, CKRecordID * __nullable recordID, NSError * __nullable error);

/*  This block is called when the operation completes.
    The [NSOperation completionBlock] will also be called if both are set.
    If the error is CKErrorPartialFailure, the error's userInfo dictionary contains
    a dictionary of recordIDs to errors keyed off of CKPartialErrorsByItemIDKey.
*/
@property (nonatomic, copy, nullable) void (^fetchRecordsCompletionBlock)(NSDictionary <CKRecordID * , CKRecord *> * __nullable recordsByRecordID, NSError * __nullable operationError);

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

typedef NS_ENUM(NSInteger, CKRecordSavePolicy) {
    CKRecordSaveIfServerRecordUnchanged = 0, /* Locally-edited keys are sent to the server. If the record on the server has been modified,
                                                fail the write and return an error. */
    CKRecordSaveChangedKeys             = 1, /* Locally-edited keys are written to the server.  Any unseen changes on the server
                                               will be overwritten to the locally-edited value. */
    CKRecordSaveAllKeys                 = 2, /* All local keys are written to the server.  Any unseen changes on the server will be
                                               overwritten to the local values.  Keys present only on the server remain unchanged.
                                               There are two common ways in which a server record will contain keys not present locally:
                                               1 - Since you've fetched this record, another client has added a new key to the record.
                                               2 - The presence of desiredKeys on the fetch / query that returned this record meant
                                               that only a portion of the record's keys were downloaded. */
} NS_ENUM_AVAILABLE(10_10, 8_0);

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKModifyRecordsOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecordsToSave:(nullable NSArray <CKRecord *> *)records recordIDsToDelete:(nullable NSArray <CKRecordID *> *)recordIDs;

@property (nonatomic, copy, nullable) NSArray <CKRecord *> *recordsToSave;
@property (nonatomic, copy, nullable) NSArray <CKRecordID *> *recordIDsToDelete;

/* The default value is CKRecordSaveIfServerRecordUnchanged. */
@property (nonatomic, assign) CKRecordSavePolicy savePolicy;

/* This property is kept by the server to identify the last known request from this client. 
 Multiple requests from the client with the same change token will be ignored by the server. */
@property (nonatomic, copy, nullable) NSData *clientChangeTokenData;

/* Determines whether the batch should fail atomically or not. YES by default.
   This only applies to zones that support CKRecordZoneCapabilityAtomic */
@property (nonatomic, assign) BOOL atomic;

/* Called repeatedly during transfer.
 It is possible for progress to regress when a retry is automatically triggered.
*/
@property (nonatomic, copy, nullable) void (^perRecordProgressBlock)(CKRecord *record, double progress);
/* Called on success or failure for each record. */
@property (nonatomic, copy, nullable) void (^perRecordCompletionBlock)(CKRecord * __nullable record, NSError * __nullable error);

/*  This block is called when the operation completes.
 The [NSOperation completionBlock] will also be called if both are set.
 If the error is CKErrorPartialFailure, the error's userInfo dictionary contains
 a dictionary of recordIDs to errors keyed off of CKPartialErrorsByItemIDKey.
 This call happens as soon as the server has
 seen all record changes, and may be invoked while the server is processing the side effects
 of those changes.
*/
@property (nonatomic, copy, nullable) void (^modifyRecordsCompletionBlock)(NSArray <CKRecord *> * __nullable savedRecords, NSArray <CKRecordID *> * __nullable deletedRecordIDs, NSError * __nullable operationError);

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

#if (TARGET_OS_MAC && !TARGET_OS_IPHONE && !TARGET_OS_SIMULATOR && !TARGET_OS_EMBEDDED) || TARGET_OS_IOS
#import <Contacts/CNContact.h>
#endif

@class CKRecordID;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKDiscoveredUserInfo : NSObject

- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, readonly, copy, nullable) CKRecordID *userRecordID;

#if (TARGET_OS_MAC && !TARGET_OS_IPHONE && !TARGET_OS_SIMULATOR && !TARGET_OS_EMBEDDED) || TARGET_OS_IOS

@property (nonatomic, readonly, copy, nullable) NSString *firstName NS_DEPRECATED(10_10, 10_11, 8_0, 9_0, "Use -[[CKDiscoveredUserInfo displayContact] givenName]");
@property (nonatomic, readonly, copy, nullable) NSString *lastName NS_DEPRECATED(10_10, 10_11, 8_0, 9_0, "Use -[[CKDiscoveredUserInfo displayContact] familyName]");

/* displayContact is not associated with the local Address Book.  It is a wrapper around
 information known to the CloudKit server, including first and last names */
@property (nonatomic, readonly, copy, nullable) CNContact *displayContact NS_AVAILABLE(10_11, 9_0);

#else // (TARGET_OS_MAC && !TARGET_OS_IPHONE && !TARGET_OS_SIMULATOR && !TARGET_OS_EMBEDDED) || TARGET_OS_IOS


@property (nonatomic, readonly, copy, nullable) NSString *firstName;
@property (nonatomic, readonly, copy, nullable) NSString *lastName;

#endif // (TARGET_OS_MAC && !TARGET_OS_IPHONE && !TARGET_OS_SIMULATOR && !TARGET_OS_EMBEDDED) || TARGET_OS_IOS


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
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKDatabaseOperation : CKOperation

/* If no database is set, [self.container privateCloudDatabase] is used. */
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
    /* This zone supports CKFetchRecordChangesOperation */
    CKRecordZoneCapabilityFetchChanges   = 1 << 0,
    /* Batched changes to this zone happen atomically */
    CKRecordZoneCapabilityAtomic         = 1 << 1,
} NS_AVAILABLE(10_10, 8_0);

/* The default zone has no capabilities */
CK_EXTERN NSString * const CKRecordZoneDefaultName NS_AVAILABLE(10_10, 8_0);

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKRecordZone : NSObject <NSSecureCoding, NSCopying>

+ (CKRecordZone *)defaultRecordZone;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithZoneName:(NSString *)zoneName;
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID;

@property (nonatomic, readonly, strong) CKRecordZoneID *zoneID;

/* Capabilities are not set until a record zone is saved */
@property (nonatomic, readonly, assign) CKRecordZoneCapabilities capabilities;

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


#if DEBUG
    #define CK_UNIT_TESTS_AVAILABLE NS_CLASS_AVAILABLE(10_10, 8_0)
    #define CK_UNIT_TESTS_EXTERN CK_EXTERN
#else
    #define CK_UNIT_TESTS_AVAILABLE NS_CLASS_AVAILABLE(10_10, 8_0)
    #define CK_UNIT_TESTS_EXTERN CK_EXTERN
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
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKRecordID : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;

/* Record names must be 255 characters or less. Most UTF-8 characters are valid. */
/* This creates a record ID in the default zone */
- (instancetype)initWithRecordName:(NSString *)recordName;
- (instancetype)initWithRecordName:(NSString *)recordName zoneID:(CKRecordZoneID *)zoneID NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, strong) NSString *recordName;
@property (nonatomic, readonly, strong) CKRecordZoneID *zoneID;

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
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKFetchRecordZonesOperation : CKDatabaseOperation

+ (instancetype)fetchAllRecordZonesOperation;

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithRecordZoneIDs:(NSArray <CKRecordZoneID *> *)zoneIDs;

@property (nonatomic, copy, nullable) NSArray <CKRecordZoneID *> *recordZoneIDs;

/*  This block is called when the operation completes.
    The [NSOperation completionBlock] will also be called if both are set.
    If the error is CKErrorPartialFailure, the error's userInfo dictionary contains
    a dictionary of zoneIDs to errors keyed off of CKPartialErrorsByItemIDKey.
*/
@property (nonatomic, copy, nullable) void (^fetchRecordZonesCompletionBlock)(NSDictionary <CKRecordZoneID *, CKRecordZone *> * __nullable recordZonesByZoneID, NSError * __nullable operationError);

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
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKLocationSortDescriptor : NSSortDescriptor <NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
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

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKQueryCursor : NSObject <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
@end

@class CKQuery, CKRecord, CKRecordZoneID;

/* Query operations have a dynamically defined maximum number of results.  If the results of a query
 trip this max, your completion block will invoked with a cursor.  Issue a new query with that cursor
 to fetch the next batch of results. */
CK_EXTERN const NSUInteger CKQueryOperationMaximumResults NS_AVAILABLE(10_10, 8_0);

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKQueryOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithQuery:(CKQuery *)query;
- (instancetype)initWithCursor:(CKQueryCursor *)cursor;

@property (nonatomic, copy, nullable) CKQuery *query;
@property (nonatomic, copy, nullable) CKQueryCursor *cursor;

/* This property indicates which record zone to query. For query operations constructed using a cursor, this
 property is ignored and instead will be evaluated in the record zone in which the cursor was originally created. */
@property (nonatomic, copy, nullable) CKRecordZoneID *zoneID;

/* Defaults to CKQueryOperationMaximumResults.
 Queries may return fewer than resultsLimit in some scenarios:
 - There are legitimately fewer than 'resultsLimit' number of records matching the query (and visible to the current user).
 - During the process of querying and fetching the results, some records were deleted, or became un-readable by the current user. 
 When determining if there are more records to fetch, always check for the presence of a cursor in queryCompletionBlock. */
@property (nonatomic, assign) NSUInteger resultsLimit;

/* Declares which user-defined keys should be fetched and added to the resulting CKRecords.  If nil, declares the entire record should be downloaded. If set to an empty array, declares that no user fields should be downloaded.  Defaults to nil. */
@property (nonatomic, copy, nullable) NSArray <NSString *> *desiredKeys;

/* This block will be called once for every record that is returned as a result of the query. The callbacks will happen in the order that the results were sorted in. */
@property (nonatomic, copy, nullable) void (^recordFetchedBlock)(CKRecord *record);

/*  This block is called when the operation completes.
 The [NSOperation completionBlock] will also be called if both are set. */
@property (nonatomic, copy, nullable) void (^queryCompletionBlock)(CKQueryCursor * __nullable cursor, NSError * __nullable operationError);

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

/* Finds all discoverable users in the device's address book. No Address Book access dialog will be displayed */
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)

@interface CKDiscoverAllContactsOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, nullable) void (^discoverAllContactsCompletionBlock)(NSArray <CKDiscoveredUserInfo *> * __nullable userInfos, NSError * __nullable operationError);

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

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CKSubscriptionType) {
    CKSubscriptionTypeQuery      = 1,
    CKSubscriptionTypeRecordZone = 2,
} NS_ENUM_AVAILABLE(10_10, 8_0);

typedef NS_OPTIONS(NSUInteger, CKSubscriptionOptions) {
    CKSubscriptionOptionsFiresOnRecordCreation     = 1 << 0, // Applies to CKSubscriptionTypeQuery
    CKSubscriptionOptionsFiresOnRecordUpdate       = 1 << 1, // Applies to CKSubscriptionTypeQuery
    CKSubscriptionOptionsFiresOnRecordDeletion     = 1 << 2, // Applies to CKSubscriptionTypeQuery
    CKSubscriptionOptionsFiresOnce                 = 1 << 3, // Applies to CKSubscriptionTypeQuery
} NS_ENUM_AVAILABLE(10_10, 8_0);

@class CKNotificationInfo, CKRecordZoneID;

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKSubscription : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithRecordType:(NSString *)recordType predicate:(NSPredicate *)predicate options:(CKSubscriptionOptions)subscriptionOptions;

- (instancetype)initWithRecordType:(NSString *)recordType predicate:(NSPredicate *)predicate subscriptionID:(NSString *)subscriptionID options:(CKSubscriptionOptions)subscriptionOptions NS_DESIGNATED_INITIALIZER;

/* This subscription fires whenever any change happens in the indicated RecordZone.
 The RecordZone must have the capability CKRecordZoneCapabilityFetchChanges */
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID options:(CKSubscriptionOptions)subscriptionOptions;
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID subscriptionID:(NSString *)subscriptionID options:(CKSubscriptionOptions)subscriptionOptions NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, copy) NSString *subscriptionID;

@property (nonatomic, readonly, assign) CKSubscriptionType subscriptionType;

/* The record type that this subscription watches. This property is only used by query subscriptions, and must be set. */
@property (nonatomic, readonly, copy, nullable) NSString *recordType;

/* A predicate that determines when the subscription fires. This property is only used by query subscriptions, and must be set */
@property (nonatomic, readonly, copy, nullable) NSPredicate *predicate;

/* Options flags describing the firing behavior subscription. For query subscriptions, one of CKSubscriptionOptionsFiresOnRecordCreation, CKSubscriptionOptionsFiresOnRecordUpdate, or CKSubscriptionOptionsFiresOnRecordDeletion must be specified or an NSInvalidArgumentException will be thrown. */
@property (nonatomic, readonly, assign) CKSubscriptionOptions subscriptionOptions;

/* Optional property describing the notification that will be sent when the subscription fires. */
@property (nonatomic, copy, nullable) CKNotificationInfo *notificationInfo;

/* Query subscriptions: Optional property.  If set, a query subscription is scoped to only record changes in the indicated zone.
   RecordZone subscriptions: */
@property (nonatomic, copy, nullable) CKRecordZoneID *zoneID;

@end

/* The payload of a push notification delivered in the UIApplication application:didReceiveRemoteNotification: delegate method contains information about the firing subscription.   Use
   +[CKNotification notificationFromRemoteNotificationDictionary:] to parse that payload. */

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKNotificationInfo : NSObject <NSSecureCoding, NSCopying>

/* Optional alert string to display in a push notification. */
@property (nonatomic, copy, nullable) NSString *alertBody;

/* Instead of a raw alert string, you may optionally specify a key for a localized string in your app's Localizable.strings file. */
@property (nonatomic, copy, nullable) NSString *alertLocalizationKey;

/* A list of field names to take from the matching record that is used as substitution variables in a formatted alert string. */
@property (nonatomic, copy, nullable) NSArray <NSString *> *alertLocalizationArgs;

/* A key for a localized string to be used as the alert action in a modal style notification. */
@property (nonatomic, copy, nullable) NSString *alertActionLocalizationKey;

/* The name of an image in your app bundle to be used as the launch image when launching in response to the notification. */
@property (nonatomic, copy, nullable) NSString *alertLaunchImage;

/* The name of a sound file in your app bundle to play upon receiving the notification. */
@property (nonatomic, copy, nullable) NSString *soundName;

/* A list of keys from the matching record to include in the notification payload.
 Only some keys are allowed.  The value types associated with those keys on the server must be one of these classes:
     CKReference
     CLLocation
     NSDate
     NSNumber
     NSString */
@property (nonatomic, copy, nullable) NSArray <NSString *> *desiredKeys;

/* Indicates that the notification should increment the app's badge count. Default value is NO. */
@property (nonatomic, assign) BOOL shouldBadge;

/* Indicates that the notification should be sent with the "content-available" flag to allow for background downloads in the application. 
   Default value is NO. */
@property (nonatomic, assign) BOOL shouldSendContentAvailable;

/* Optional property for the category to be sent with the push when this subscription fires. Categories allow you to present custom actions to the user on your push notifications. See UIMutableUserNotificationCategory for more information. */
@property (nonatomic, copy, nullable) NSString *category NS_AVAILABLE(10_11, 9_0);

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

@class CKSubscription;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKModifySubscriptionsOperation : CKDatabaseOperation

- (instancetype)initWithSubscriptionsToSave:(nullable NSArray <CKSubscription *> *)subscriptionsToSave subscriptionIDsToDelete:(nullable NSArray <NSString *> *)subscriptionIDsToDelete NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, nullable) NSArray <CKSubscription *> *subscriptionsToSave;
@property (nonatomic, copy, nullable) NSArray <NSString *> *subscriptionIDsToDelete;

/*  This block is called when the operation completes.
    The [NSOperation completionBlock] will also be called if both are set.
    If the error is CKErrorPartialFailure, the error's userInfo dictionary contains
    a dictionary of subscriptionIDs to errors keyed off of CKPartialErrorsByItemIDKey.
*/
@property (nonatomic, copy, nullable) void (^modifySubscriptionsCompletionBlock)(NSArray <CKSubscription *> * __nullable savedSubscriptions, NSArray <NSString *> * __nullable deletedSubscriptionIDs, NSError * __nullable operationError);

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

/* Use this constant for the recordType parameter when fetching User Records. */
CK_EXTERN NSString * const CKRecordTypeUserRecord NS_AVAILABLE(10_10, 8_0);

@protocol CKRecordValue <NSObject>
@end

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKRecord : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;

/* These create the record in the default zone. */
- (instancetype)initWithRecordType:(NSString *)recordType;
- (instancetype)initWithRecordType:(NSString *)recordType recordID:(CKRecordID *)recordID;

- (instancetype)initWithRecordType:(NSString *)recordType zoneID:(CKRecordZoneID *)zoneID;

@property (nonatomic, readonly, copy) NSString *recordType;
@property (nonatomic, readonly, copy) CKRecordID *recordID;

/* Change tags are updated by the server to a unique value every time a record is modified.
   A different change tag necessarily means that the contents of the record are different. */
@property (nonatomic, readonly, copy, nullable) NSString *recordChangeTag;

/* This is a User Record recordID, identifying the user that created this record. */
@property (nonatomic, readonly, copy, nullable) CKRecordID *creatorUserRecordID;
@property (nonatomic, readonly, copy, nullable) NSDate *creationDate;

/* This is a User Record recordID, identifying the user that last modified this record. */
@property (nonatomic, readonly, copy, nullable) CKRecordID *lastModifiedUserRecordID;
@property (nonatomic, readonly, copy, nullable) NSDate *modificationDate;

/* 
    In addition to objectForKey: and setObject:forKey:, dictionary-style subscripting (record[key] and record[key] = value) can be used to get and set values.
    Acceptable value object classes are:
        CKReference
        CKAsset
        CLLocation
        NSData
        NSDate
        NSNumber
        NSString
        NSArray containing objects of any of the types above
 
    Any other classes will result in an exception with name NSInvalidArgumentException.

    Derived field keys are prefixed with '_'. Attempting to set a key prefixed with a '_' will result in an error.
 
    Key names roughly match C variable name restrictions. They must begin with an ASCII letter and can contain ASCII
     letters and numbers and the underscore character.
    The maximum key length is 255 characters.
*/
- (nullable __kindof id <CKRecordValue>)objectForKey:(NSString *)key;
- (void)setObject:(nullable __kindof id <CKRecordValue>)object forKey:(NSString *)key;
- (NSArray <NSString *> *)allKeys;

/* A special property that returns an array of token generated from all the string field values in the record.
   These tokens have been normalized for the current locale, so they are suitable for performing full-text searches. */
- (NSArray <NSString *> *)allTokens;

- (nullable __kindof id <CKRecordValue>)objectForKeyedSubscript:(NSString *)key;
- (void)setObject:(nullable __kindof id <CKRecordValue>)object forKeyedSubscript:(NSString *)key;

/* A list of keys that have been modified on the local CKRecord instance */
- (NSArray <NSString *> *)changedKeys;

/* CKRecord supports NSSecureCoding.  When you invoke
 -encodeWithCoder: on a CKRecord, it encodes all its values.  Including the record values you've set.
 If you want to store a CKRecord instance locally, AND you're already storing the record values locally,
 that's overkill.  In that case, you can use
 -encodeSystemFieldsWithCoder:.  This will encode all parts of a CKRecord except the record keys / values you
 have access to via the -changedKeys and -objectForKey: methods.
 If you use initWithCoder: to reconstitute a CKRecord you encoded via encodeSystemFieldsWithCoder:, then be aware that
 - any record values you had set on the original instance, but had not saved, will be lost
 - the reconstituted CKRecord's changedKeys will be empty
 */
- (void)encodeSystemFieldsWithCoder:(NSCoder *)coder;

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

NS_ASSUME_NONNULL_BEGIN

@class CKDatabase, CKOperation, CKRecordID, CKDiscoveredUserInfo;

// This constant represents the current user's ID for zone ID
CK_EXTERN NSString * const CKOwnerDefaultName NS_AVAILABLE(10_10, 8_0);

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKContainer : NSObject

- (instancetype)init NS_UNAVAILABLE;

/* These calls return a CKContainer initialized with a containerIdentifier of
  [NSString stringWithFormat:@"iCloud.%@", applicationIdentifier], where application identifier
   is the calling process' application-identifier (com.apple.application-identifier on OS X) entitlement.
   If the application is in production mode (aka,
   com.apple.developer.icloud-container-environment
   is set to Production in your entitlements plist, and you have no override in
   com.apple.developer.icloud-container-development-container-identifiers
   ), then the production environment is used. */
+ (CKContainer *)defaultContainer;
+ (CKContainer *)containerWithIdentifier:(NSString *)containerIdentifier;

@property (nonatomic, readonly, nullable) NSString *containerIdentifier;

- (void)addOperation:(CKOperation *)operation;

@end

@interface CKContainer (Database)

/* Public vs. Private databases:
 Records in a public database
 - By default are world readable, owner writable.
 - Can be locked down by Roles, a process done in the Developer Portal, a web interface.  Roles are not present in the client API.
 - Are visible to the application developer via the Developer Portal.
 - Do not contribute to the owner's iCloud account storage quota.
 Records in a private database
 - By default are only owner readable and owner writable.
 - Are not visible to the application developer via the Developer Portal.
 - Are counted towards the owner's iCloud account storage quota.
 */
@property (nonatomic, readonly) CKDatabase *privateCloudDatabase;
@property (nonatomic, readonly) CKDatabase *publicCloudDatabase;

@end

typedef NS_ENUM(NSInteger, CKAccountStatus) {
    /* An error occurred when getting the account status, consult the corresponding NSError */
    CKAccountStatusCouldNotDetermine                   = 0,
    /* The iCloud account credentials are available for this application */
    CKAccountStatusAvailable                           = 1,
    /* Parental Controls / Device Management has denied access to iCloud account credentials */
    CKAccountStatusRestricted                          = 2,
    /* No iCloud account is logged in on this device */
    CKAccountStatusNoAccount                           = 3,
} NS_ENUM_AVAILABLE(10_10, 8_0);

/* This local notification is posted when there has been any change to the logged in 
   iCloud account. On receipt, an updated account status should be obtained by calling
   accountStatusWithCompletionHandler:
 */
CK_EXTERN NSString * const CKAccountChangedNotification NS_AVAILABLE(10_11, 9_0);

@interface CKContainer (AccountStatus)

- (void)accountStatusWithCompletionHandler:(void (^)(CKAccountStatus accountStatus, NSError * __nullable error))completionHandler;

@end

typedef NS_OPTIONS(NSUInteger, CKApplicationPermissions) {
    /* Allows the user's record in CloudKit to be discoverable via the user's email address */
    CKApplicationPermissionUserDiscoverability         = 1 << 0,
} NS_AVAILABLE(10_10, 8_0);

typedef NS_ENUM(NSInteger, CKApplicationPermissionStatus) {
    /* The user has not made a decision for this application permission. */
    CKApplicationPermissionStatusInitialState          = 0,
    /* An error occurred when getting or setting the application permission status, consult the corresponding NSError */
    CKApplicationPermissionStatusCouldNotComplete      = 1,
    /* The user has denied this application permission */
    CKApplicationPermissionStatusDenied                = 2,
    /* The user has granted this application permission */
    CKApplicationPermissionStatusGranted               = 3,
} NS_ENUM_AVAILABLE(10_10, 8_0);

typedef void(^CKApplicationPermissionBlock)(CKApplicationPermissionStatus applicationPermissionStatus, NSError * __nullable error);

@interface CKContainer (ApplicationPermission)

- (void)statusForApplicationPermission:(CKApplicationPermissions)applicationPermission completionHandler:(CKApplicationPermissionBlock)completionHandler;
- (void)requestApplicationPermission:(CKApplicationPermissions)applicationPermission completionHandler:(CKApplicationPermissionBlock)completionHandler;

@end

@interface CKContainer (UserRecords)

/* If there is no iCloud account configured, or if access is restricted, a CKErrorNotAuthenticated error will be returned. 
   This work is treated as having NSQualityOfServiceUserInitiated quality of service.
 */
- (void)fetchUserRecordIDWithCompletionHandler:(void (^)(CKRecordID * __nullable recordID, NSError * __nullable error))completionHandler;

/* This fetches all user records that match an entry in the user's address book.
 CKDiscoverAllContactsOperation and CKDiscoverUserInfosOperation are the more configurable,
 CKOperation-based alternatives to these methods */
- (void)discoverAllContactUserInfosWithCompletionHandler:(void (^)(NSArray <CKDiscoveredUserInfo *> * __nullable userInfos, NSError * __nullable error))completionHandler;
- (void)discoverUserInfoWithEmailAddress:(NSString *)email completionHandler:(void (^)(CKDiscoveredUserInfo * __nullable userInfo, NSError * __nullable error))completionHandler;
- (void)discoverUserInfoWithUserRecordID:(CKRecordID *)userRecordID completionHandler:(void (^)(CKDiscoveredUserInfo * __nullable userInfo, NSError * __nullable error))completionHandler;

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
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKAsset : NSObject

- (instancetype)init NS_UNAVAILABLE;

/* Initialize an asset to be saved with the content at the given file URL */
- (instancetype)initWithFileURL:(NSURL *)fileURL;

/* Local file URL where fetched records are cached and saved records originate from. */
@property (nonatomic, readonly, copy) NSURL *fileURL;

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
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKModifyBadgeOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithBadgeValue:(NSUInteger)badgeValue;

@property (nonatomic, assign) NSUInteger badgeValue;

/*  This block is called when the operation completes.
    The [NSOperation completionBlock] will also be called if both are set. */
@property (nonatomic, copy, nullable) void (^modifyBadgeCompletionBlock)(NSError * __nullable operationError);

@end
NS_ASSUME_NONNULL_END
