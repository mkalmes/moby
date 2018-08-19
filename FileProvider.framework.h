// ==========  FileProvider.framework/Headers/NSFileProviderEnumerating.h
//
//  NSFileProviderEnumerating.h
//  FileProvider
//
//  Copyright (c) 2014-2017 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderExtension.h>
#import <FileProvider/NSFileProviderItem.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A user-defined chunk of data that defines a starting point to enumerate changes from.

 The size of a sync anchor should not exceed a combined 500 bytes.
 */
typedef NSData *NSFileProviderSyncAnchor NS_TYPED_EXTENSIBLE_ENUM;

/**
 A user- or system-defined chunk of data that defines a page to continue the enumeration from.
 Initial enumeration is started from one of the below system-defined pages.

 The size of a page should not exceed 500 bytes.
 */
typedef NSData *NSFileProviderPage NS_TYPED_EXTENSIBLE_ENUM;

FOUNDATION_EXPORT API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
NSFileProviderPage const NSFileProviderInitialPageSortedByDate;
FOUNDATION_EXPORT API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
NSFileProviderPage const NSFileProviderInitialPageSortedByName;

@protocol NSFileProviderEnumerationObserver <NSObject>

- (void)didEnumerateItems:(NSArray <id<NSFileProviderItem>> *)updatedItems;

/**
 Call this method after enumerating a full page of items.  If you set a non-nil
 nextPage, -[NSFileProviderEnumerator enumerateItemsToObserver:startingAtPage:]
 might be called with nextPage to enumerate more items.  This is typically
 driven by the user scrolling a UIDocumentBrowserViewController presenting a
 directory containing more child items that would fit in the view.

 Page data is limited to 500 bytes.  Setting a larger nextPage interrupts the
 enumeration.
 */
- (void)finishEnumeratingUpToPage:(nullable NSFileProviderPage)nextPage NS_SWIFT_NAME(finishEnumerating(upTo:));
- (void)finishEnumeratingWithError:(NSError *)error;
@end

@protocol NSFileProviderChangeObserver <NSObject>

/**
 Send updates to existing items, or insert new items.
 */
- (void)didUpdateItems:(NSArray <id<NSFileProviderItem>> *)updatedItems;

/**
 Delete existing items.  No-op if the item was unknown.
 */
- (void)didDeleteItemsWithIdentifiers:(NSArray <NSFileProviderItemIdentifier> *)deletedItemIdentifiers;

/**
 Call the following method every so often while sending changes, particularly
 while enumerating changes to NSFileProviderWorkingSetContainerItemIdentifier.
 If the device reboots during an enumeration, it would later resume starting
 at the latest known sync anchor.

 It is expected that the sync anchor passed here be different than the sync
 anchor that the enumeration started at, unless the client was already up to
 date on all the changes on the server, and didn't have any pending updates or
 deletions.
 
 Additionally, if the client is up to date on all the changes on the server it
 should set moreComing to NO.

 Sync anchor data is limited to 500 bytes.  Setting a larger anchor has the
 same effect as calling finishEnumeratingWithError with an expired sync anchor
 error.
 */
- (void)finishEnumeratingChangesUpToSyncAnchor:(NSFileProviderSyncAnchor)anchor
                                    moreComing:(BOOL)moreComing NS_SWIFT_NAME(finishEnumeratingChanges(upTo:moreComing:));

/**
 If the enumeration fails with NSFileProviderErrorSyncAnchorExpired, we will
 drop all cached data and start the enumeration over starting with sync anchor
 nil.
 */
- (void)finishEnumeratingWithError:(NSError *)error;

@end


@protocol NSFileProviderEnumerator <NSObject>

- (void)invalidate;

/**
 Enumerate items starting from the specified page, typically
 NSFileProviderInitialPageSortedByDate or NSFileProviderInitialPageSortedByName.

 Pagination allows large collections to be enumerated in multiple batches.  The
 sort order specified in the initial page is important even if the enumeration
 results will actually be sorted again before display.  If results are sorted
 correctly across pages, then the new results will be appended at the bottom of
 the list, probably not on screen, which is the best user experience.  Otherwise
 results from the second page might be inserted in the results from the first
 page, causing bizarre animations.

 The page data should contain whatever information is needed to resume the
 enumeration after the previous page.  If a file provider sends batches of 200
 items to -[NSFileProviderEnumerationObserver didEnumerateItems:] for example,
 then successive pages might contain offsets in increments of 200.
 */
- (void)enumerateItemsForObserver:(id<NSFileProviderEnumerationObserver>)observer
                   startingAtPage:(NSFileProviderPage)page NS_SWIFT_NAME(enumerateItems(for:startingAt:));

@optional
/**
 Enumerate changes starting from a sync anchor. This should enumerate /all/
 changes (not restricted to a specific page) since the given sync anchor.

 Until the enumeration update is invalidated, a call to -[NSFileProviderManager
 signalEnumeratorForContainerItemIdentifier:completionHandler:] will trigger a call
 to enumerateFromSyncAnchor with the latest known sync anchor, giving the file
 provider (app or extension) a chance to notify about changes.

 The anchor data should contain whatever information is needed to resume
 enumerating changes from the previous synchronization point.  A naive sync
 anchor might for example be the date of the last change that was sent from the
 server to the client, meaning that at that date, the client was in sync with
 all the server changes.  A request to enumerate changes from that sync anchor
 would only return the changes that happened after that date, which are
 therefore changes that the client doesn't yet know about.

 If anchor is nil, then the system is enumerating from scratch: the system wants
 to receives changes to reconstruct the list of items in this enumeration as if
 starting from an empty list.
 */
- (void)enumerateChangesForObserver:(id<NSFileProviderChangeObserver>)observer
                     fromSyncAnchor:(NSFileProviderSyncAnchor)syncAnchor NS_SWIFT_NAME(enumerateChanges(for:from:));

/**
 Request the current sync anchor.

 To keep an enumeration updated, the system will typically
 - request the current sync anchor (1)
 - enumerate items starting with an initial page
 - continue enumerating pages, each time from the page returned in the previous
   enumeration, until finishEnumeratingUpToPage: is called with nextPage set to
   nil
 - enumerate changes starting from the sync anchor returned in (1)
 - continue enumerating changes, each time from the sync anchor returned in the
   previous enumeration, until finishEnumeratingChangesUpToSyncAnchor: is called
   with moreComing:NO

 This method will be called again if you signal that there are more changes with
 -[NSFileProviderManager signalEnumeratorForContainerItemIdentifier:completionHandler:] and again,
 the system will enumerate changes until finishEnumeratingChangesUpToSyncAnchor:
 is called with moreComing:NO.
 */
- (void)currentSyncAnchorWithCompletionHandler:(void(^)(_Nullable NSFileProviderSyncAnchor currentAnchor))completionHandler;

@end

@interface NSFileProviderExtension (NSFileProviderEnumeration)

/**
 Create an enumerator for an item.

 When the user opens the browse tab of the UIDocumentsBrowserViewController and
 selects a file provider, this is called with
 NSFileProviderRootContainerItemIdentifier, and -[NSFileProviderEnumerator
 enumerateItemsForObserver:startingAtPage:] is immediately called to list the
 first items available under at the root level of the file provider.

 As the user navigates down into directories, new enumerators are created with
 this method, passing in the itemIdentifier of those directories.  Past
 enumerators are then invalidated.

 This method is also called with
 NSFileProviderWorkingSetContainerItemIdentifier, which is enumerated with
 -[NSFileProviderEnumerator enumerateChangesForObserver:fromSyncAnchor:].  That
 enumeration is special in that it isn't driven by the
 UIDocumentsBrowserViewController.  It happens in the background to sync the
 working set down to the device.

 This is also used to subscribe to live updates for a single document.  In that
 case, -[NSFileProviderEnumerator enumerateChangesToObserver:fromSyncAnchor:]
 will be called and the enumeration results shouldn't include items other than
 the very item that the enumeration was started on.

 If returning nil, you must set the error out parameter.
 */
- (nullable id<NSFileProviderEnumerator>)enumeratorForContainerItemIdentifier:(NSFileProviderItemIdentifier)containerItemIdentifier
                                                                        error:(NSError **)error NS_SWIFT_NAME(enumerator(for:));

@end

NS_ASSUME_NONNULL_END
// ==========  FileProvider.framework/Headers/NSFileProviderDomain.h
//
//  NSFileProviderDomain.h
//  FileProvider
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FileProvider/NSFileProviderExtension.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString *NSFileProviderDomainIdentifier NS_EXTENSIBLE_STRING_ENUM;

/**
 File provider domain.

 A file provider domain can be used to represent accounts or different locations
 exposed within a given file provider.

 Domains can be registered to the system using
 @c -[NSFileProviderMananger addDomain:completionHandler:]

 By default, a file provider extension does not have any domain.

 On the extension side, a separate instance of NSFileProviderExtension will be
 created for each @c NSFileProviderDomain registered.  In that case, the
 @c NSFileProviderExtension.domain properties will indicate which domain the
 NSFileProviderExtension belongs to (or nil if none).

 All the files on disk belonging to the same domain must be grouped inside a
 common directory. That directory path is indicated by the
 @p pathRelativeToDocumentStorage property.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NSFileProviderDomain : NSObject

/**
 Initialize a new NSFileProviderDomain

 The file provider extension implementation can pick any @c identifier as it sees
 fit to identify the group of items.

 @param displayName a user visible string representing the group of items the
 file provider extension is using.

 @param pathRelativeToDocumentStorage a path relative to
 @c NSFileProviderExtension.documentStorageURL.
 */
- (instancetype)initWithIdentifier:(NSFileProviderDomainIdentifier)identifier displayName:(NSString *)displayName pathRelativeToDocumentStorage:(NSString *)pathRelativeToDocumentStorage;

/**
 The identifier - as provided by the file provider extension.
 */
@property (readonly, copy) NSFileProviderDomainIdentifier identifier;

/**
 The display name shown by the system to represent this domain.
 */
@property (readonly, copy) NSString *displayName;

/**
 The path relative to the document storage of the file provider extension.
 Files belonging to this domains should be stored under this path.
 */
@property (readonly, copy) NSString *pathRelativeToDocumentStorage;

@end

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NSFileProviderExtension (NSFileProviderDomain)
@property(nonatomic, readonly, nullable) NSFileProviderDomain *domain;
@end

NS_ASSUME_NONNULL_END
// ==========  FileProvider.framework/Headers/NSFileProviderError.h
//
//  NSFileProviderError.h
//  FileProvider
//
//  Copyright (c) 2014-2017 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSErrorDomain const NSFileProviderErrorDomain API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

FOUNDATION_EXPORT NSString * const NSFileProviderErrorCollidingItemKey API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
FOUNDATION_EXPORT NSString * const NSFileProviderErrorNonExistentItemIdentifierKey API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

typedef NS_ERROR_ENUM(NSFileProviderErrorDomain, NSFileProviderErrorCode) {
    NSFileProviderErrorNotAuthenticated  = -1000, /**< The user credentials cannot be verified */
    NSFileProviderErrorFilenameCollision = -1001, /**< An item already exists with the same parentItemIdentifier and filename (or with a filename differing only in case.)
                                                       Please use -[NSError (NSFileProviderError) fileProviderErrorForCollisionWithItem:] to build an error with this code. */
    NSFileProviderErrorSyncAnchorExpired = -1002, /**< The value of the sync anchor is too old, and the system must re-sync from scratch */
    NSFileProviderErrorPageExpired        = NSFileProviderErrorSyncAnchorExpired, /**< The value of the page token is too old, and the system must re-sync from scratch */
    NSFileProviderErrorInsufficientQuota = -1003, /**< The item has not been uploaded because it would push the account over quota */
    NSFileProviderErrorServerUnreachable = -1004, /**< Connecting to the servers failed */
    NSFileProviderErrorNoSuchItem        = -1005  /**< The requested item doesn't exist
                                                       Please use -[NSError (NSFileProviderError) fileProviderErrorForNonExistentItemWithIdentifier:] to build an error with this code. */
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

@interface NSError (NSFileProviderError)
+ (instancetype)fileProviderErrorForCollisionWithItem:(NSFileProviderItem)existingItem API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
+ (instancetype)fileProviderErrorForNonExistentItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);
@end

NS_ASSUME_NONNULL_END
// ==========  FileProvider.framework/Headers/NSFileProviderManager.h
//
//  NSFileProviderManager.h
//  FileProvider
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderItem.h>

NS_ASSUME_NONNULL_BEGIN

@class NSURLSessionTask;
@class NSFileProviderDomain;

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NSFileProviderManager : NSObject

- (instancetype)init NS_UNAVAILABLE;

/**
 Call this method either in the app or in the extension.

 The file provider manager is the objects that lets you communicate with the file
 provider framework, when you have background activity (e.g when you receive a
 push or when an NSURLSessionTask starts or completes.)  The file provider
 framework will invoke your file provider extension in response to those calls if appropriate.
 */
@property (class, readonly, strong) NSFileProviderManager *defaultManager;

/**
 Call this method either in the app or in the extension to trigger an enumeration,
 typically in response to a push.

 Set the containerItemIdentifier to the identifier of the enumerated container that
 was specified in
 -[NSFileProviderExtension enumeratorForContainerItemIdentifier:error:]

 This will trigger another call to
 -[NSFileProviderEnumerator enumerateChangesForObserver:fromSyncAnchor:]

 and the UI will be refreshed, giving the user live updates on the presented
 enumeration.

 If you have a change in the working set, call this method with
 containerItemIdentifier set to NSFileProviderWorkingSetContainerItemIdentifier,
 even if there is no live enumeration for this item.  The working set is cached
 on the device and it's important to keep the cache in sync.

 In addition to using this method, your application/extension can register for pushes
 using the PKPushTypeFileProvider push type. Pushes of the form
 {
     container-identifier = "<identifier>"
 }
 with a topic of "<your application identifier>.pushkit.fileprovider" will be
 translated into a call to signalEnumeratorForContainerItemIdentifier:completionHandler:.
 */
- (void)signalEnumeratorForContainerItemIdentifier:(NSFileProviderItemIdentifier)containerItemIdentifier completionHandler:(void (^)(NSError * __nullable error))completion NS_SWIFT_NAME(signalEnumerator(for:completionHandler:));

/**
 Registers the given NSURLSessionTask to be responsible for the specified item.
 A given item can only have one task registered at a time. The task must be suspended
 at the time of calling.
 The task's progress is displayed on the item when the task is executed.
 */
- (void)registerURLSessionTask:(NSURLSessionTask *)task forItemWithIdentifier:(NSFileProviderItemIdentifier)identifier completionHandler:(void (^)(NSError * __nullable error))completion;

/**
 The purpose identifier of your file provider extension. A coordination using a
 file coordinator with this purpose identifier set will not trigger your file
 provider extension. You can use this to e.g. perform speculative work on behalf
 of the file provider from the main app.
 */
@property(nonatomic, readonly) NSString *providerIdentifier;

/**
 The root URL for provided documents. This URL is derived by consulting the
 NSExtensionFileProviderDocumentGroup property on your extension. The document
 storage URL is the folder "File Provider Storage" in the corresponding
 container.
 */
@property(nonatomic, readonly) NSURL *documentStorageURL;

/**
 Writes out a placeholder at the specified URL. The placeholder is used in place
 of the actual file for operations that do not require the file's actual data to
 be on disk:
 - if attributes are requested by an application via the
 getPromisedItemResourceValue: method on NSURL
 - or via a coordination with the
 NSFileCoordinatorReadingImmediatelyAvailableMetadataOnly flag set
 - to verify whether an application has access to a file

 Your extension should provide placeholders by implementing the
 providePlaceholderAtURL: method, but your application may choose to proactively
 write out placeholders to facilitate access to files. This is especially useful
 if your application wants to actively hand out a file URL, e.g. using
 UIActivityViewController, in which case it should ensure that either the file
 or a placeholder is present on disk first.

 The path of the placeholder is fixed and must be determined in advance by
 calling the placeholderURLForURL: method.
 */
+ (BOOL)writePlaceholderAtURL:(NSURL *)placeholderURL
                 withMetadata:(NSFileProviderItem)metadata
                        error:(NSError **)error;

/**
 Returns the designated placeholder URL for a given file URL. Used in
 conjunction with writePlaceholderAtURL.
 */
+ (NSURL *)placeholderURLForURL:(NSURL *)url;

/**
 Register a domain in which items can be stored.
 */
+ (void)addDomain:(NSFileProviderDomain *)domain completionHandler:(void(^)(NSError *_Nullable))completionHandler;

/**
 Remove a domain.
 */
+ (void)removeDomain:(NSFileProviderDomain *)domain completionHandler:(void(^)(NSError *_Nullable))completionHandler;

/**
 Get all registered domains.
 */
+ (void)getDomainsWithCompletionHandler:(void (^)(NSArray<NSFileProviderDomain *> *domains, NSError * _Nullable error))completionHandler;

/**
 Remove all registered domains.
 */
+ (void)removeAllDomainsWithCompletionHandler:(void(^)(NSError *_Nullable))completionHandler;

+ (nullable instancetype)managerForDomain:(NSFileProviderDomain *)domain;

@end

NS_ASSUME_NONNULL_END
// ==========  FileProvider.framework/Headers/NSFileProviderDefines.h
//
//  NSFileProviderDefines.h
//  FileProvider
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

// This file intentionally left blank.
// ==========  FileProvider.framework/Headers/FileProvider.h
//
//  FileProvider.h
//  FileProvider
//
//  Copyright (c) 2014-2017 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderDomain.h>
#import <FileProvider/NSFileProviderExtension.h>
#import <FileProvider/NSFileProviderEnumerating.h>
#import <FileProvider/NSFileProviderError.h>
#import <FileProvider/NSFileProviderItem.h>
#import <FileProvider/NSFileProviderManager.h>
#import <FileProvider/NSFileProviderActions.h>
#import <FileProvider/NSFileProviderService.h>
#import <FileProvider/NSFileProviderThumbnailing.h>
// ==========  FileProvider.framework/Headers/NSFileProviderItem.h
//
//  NSFileProviderItem.h
//  FileProvider
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString *NSFileProviderItemIdentifier NS_EXTENSIBLE_STRING_ENUM;

/**
 The root of the hierarchical enumeration, i.e the container enumerated when the
 user starts browsing your file provider.
 */
FOUNDATION_EXPORT NSFileProviderItemIdentifier const NSFileProviderRootContainerItemIdentifier NS_SWIFT_NAME(NSFileProviderItemIdentifier.rootContainer) API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 The item identifier representing the working set of documents and directories.
 The working set is the set of items that is relevant to the user on this
 device and should include recently used documents, favorite directories, tagged
 documents and directories, shared items, recently deleted items.

 Items in this enumeration should not parentItemIdentifier set to
 NSFileProviderWorkingSetContainerItemIdentifier, but rather to the container
 that they actually are parented to.
 */
FOUNDATION_EXPORT NSFileProviderItemIdentifier const NSFileProviderWorkingSetContainerItemIdentifier NS_SWIFT_NAME(NSFileProviderItemIdentifier.workingSet) API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 A special value for favorite ranks, to use when no rank was set when the item
 was favorited.
 */
FOUNDATION_EXPORT unsigned long long const NSFileProviderFavoriteRankUnranked API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

typedef NS_OPTIONS(NSUInteger, NSFileProviderItemCapabilities) {
    /**
     Indicates that the file can be opened for reading.  If set on a folder
     this is equivalent to @c .allowsContentEnumerating.
     */
    NSFileProviderItemCapabilitiesAllowsReading     = 1 << 0,

    /**
     Indicates that the file can be opened for writing. If set on a folder,
     this is equivalent to @c .allowsAddingSubItems.
     */
    NSFileProviderItemCapabilitiesAllowsWriting     = 1 << 1,

    /** Indicates that the item can be moved to another folder */
    NSFileProviderItemCapabilitiesAllowsReparenting = 1 << 2,

    /** Indicates that the item can be renamed */
    NSFileProviderItemCapabilitiesAllowsRenaming    = 1 << 3,

    /** Indicates that the item can be moved to the trash */
    NSFileProviderItemCapabilitiesAllowsTrashing    = 1 << 4,

    /** Indicates that the item can be deleted */
    NSFileProviderItemCapabilitiesAllowsDeleting    = 1 << 5,

    /**
     Indicates that items can be imported to the folder. If set on a file,
     this is equivalent to @c .allowsWriting.
     */
    NSFileProviderItemCapabilitiesAllowsAddingSubItems = NSFileProviderItemCapabilitiesAllowsWriting,

    /**
     Indicates that the folder can be enumerated. If set on a file, this is
     equivalent to @c .allowsReading.
     */
    NSFileProviderItemCapabilitiesAllowsContentEnumerating = NSFileProviderItemCapabilitiesAllowsReading,

    NSFileProviderItemCapabilitiesAllowsAll =
          NSFileProviderItemCapabilitiesAllowsReading
        | NSFileProviderItemCapabilitiesAllowsWriting
        | NSFileProviderItemCapabilitiesAllowsReparenting
        | NSFileProviderItemCapabilitiesAllowsRenaming
        | NSFileProviderItemCapabilitiesAllowsTrashing
        | NSFileProviderItemCapabilitiesAllowsDeleting
};

@protocol NSFileProviderItem <NSObject>

@property (nonatomic, readonly, copy) NSFileProviderItemIdentifier itemIdentifier;

/**
 The parent identifier specifies the parent of the item in the hierarchy.

 Set to NSFileProviderRootContainerItemIdentifier for an item at the root of the
 user's storage.  Set to the itemIdentifier of the item's parent otherwise.

 When enumerating the root container or a generic container, the
 parentItemIdentifier of the enumerated items is expected to match the
 enumerated item's identifier.  When enumerating the working set, the
 parentItemIdentifier is expected to match the actual parent of the item in the
 hierarchy (ie. it is not NSFileProviderWorkingSetContainerItemIdentifier).

 The parents of trashed items and of the root item are ignored.
 */
@property (nonatomic, readonly, copy) NSFileProviderItemIdentifier parentItemIdentifier;

/**
 The file or directory name, complete with its file extension.
 */
@property (nonatomic, readonly, copy) NSString *filename;

/**
 Uniform type identifier (UTI) for the item
 */
@property (nonatomic, readonly, copy) NSString *typeIdentifier;

@optional

/**
 The capabilities of the item.  This controls the list of actions that the UI
 will allow for the item.
 */
@property (nonatomic, readonly) NSFileProviderItemCapabilities capabilities;

@property (nonatomic, readonly, copy, nullable) NSNumber *documentSize;
@property (nonatomic, readonly, copy, nullable) NSNumber *childItemCount;
@property (nonatomic, readonly, copy, nullable) NSDate *creationDate;
@property (nonatomic, readonly, copy, nullable) NSDate *contentModificationDate;

/*
 The three properties below (lastUsedDate, tagData and favoriteRank) are
 indications that the item is part of the working set.
 */

/**
 The date this item was last used.  This is neither the modification date nor
 the last access date exposed in traditional file system APIs, and indicates a
 very clear user intent to use the document.  For example, this is set when the
 document is open full screen on a device.

 This is the system's cue that the document is recent and should appear in the
 recent list of the UIDocumentBrowserViewController.

 This property must not be shared between users, even if the item is.
 */
@property (nonatomic, readonly, copy, nullable) NSDate *lastUsedDate;

/**
 An abstract data blob reprenting the tags associated with the item.  The same
 tags that are available via -[NSURL getResourceValue:forKey:error:] with key
 NSURLTagNamesKey on macOS, except that this data blob may transport more
 information than just the tag names.

 This property must not be shared between users, even if the item is.
 */
@property (nonatomic, readonly, copy, nullable) NSData *tagData;

/**
 The presence of a favorite rank indicates that a directory is a favorite.
 Favorite ranks are 64-bit unsigned integers.  The initial value for the first
 item is the time since the unix epoch in milliseconds, but subsequent items are
 simply placed relative to that.  Favorite ranks are modified when the user
 reorders favorites.

 When favoriting folders on other platforms, set the rank to the time since the
 unix epoch in milliseconds.  Special value @(NSFileProviderFavoriteRankUnranked)
 may be used if no rank is available: the system will then figure out the best
 rank and set it.  Please persist and sync the new value.

 This property must not be shared between users, even if the item is.
 */
@property (nonatomic, readonly, copy, nullable) NSNumber *favoriteRank;

/**
 Set on a directory or a document if it should appear in the trash.
 */
@property (nonatomic, readonly, getter=isTrashed) BOOL trashed;

/*
 The download and upload properties below determine which of the cloud badges
 (uploading, downloading, pending) will be shown on the item.
 */
@property (nonatomic, readonly, getter=isUploaded) BOOL uploaded;
@property (nonatomic, readonly, getter=isUploading) BOOL uploading;

/**
 Typical uploading errors include
 - NSFileProviderErrorInsufficientQuota
 - NSFileProviderErrorServerUnreachable
 */
@property (nonatomic, readonly, copy, nullable) NSError *uploadingError;

@property (nonatomic, readonly, getter=isDownloaded) BOOL downloaded;
@property (nonatomic, readonly, getter=isDownloading) BOOL downloading;
@property (nonatomic, readonly, copy, nullable) NSError *downloadingError;

@property (nonatomic, readonly, getter=isMostRecentVersionDownloaded) BOOL mostRecentVersionDownloaded;

@property (nonatomic, readonly, getter=isShared) BOOL shared;
@property (nonatomic, readonly, getter=isSharedByCurrentUser) BOOL sharedByCurrentUser;

/**
 ownerNameComponents should be nil when sharedByCurrentUser is or the item is not shared.
 */
@property (nonatomic, strong, readonly, nullable) NSPersonNameComponents *ownerNameComponents;
@property (nonatomic, strong, readonly, nullable) NSPersonNameComponents *mostRecentEditorNameComponents;

/**
 The versionIdentifier is used to invalidate the thumbnail in the thumbnail cache.
 A content hash would be a reasonable choice.

 Version identifiers are limited to 1000 bytes.
 */
@property (nonatomic, strong, readonly, nullable) NSData *versionIdentifier;

/**
 This dictionary can be used add state information to the item.  FileProviderUI
 action predicates can access this dictionary.
 
 All values for this dictionary must be of type String, Number or Date.
 */
@property (nonatomic, strong, readonly, nullable) NSDictionary *userInfo;

@end


typedef id<NSFileProviderItem> NSFileProviderItem;

NS_ASSUME_NONNULL_END
// ==========  FileProvider.framework/Headers/NSFileProviderThumbnailing.h
//
//  NSFileProviderThumbnailing.h
//  FileProvider
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderDefines.h>
#import <CoreGraphics/CoreGraphics.h>
#import <FileProvider/NSFileProviderExtension.h>
#import <FileProvider/NSFileProviderItem.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSFileProviderExtension (NSFileProviderThumbnailing)

/**
 The system calls this method to fetch thumbnails.

 The @p perThumbnailCompletionHandler should be called for each thumbnail, and
 @p completionHandler only after all the per thumbnail completion blocks.

 In the event of a global error, the implementation is allowed to skip calling
 the @p perThumbnailCompletionHandler for individual thumbnails. In that case,
 the @p completionHandler's error parameter would apply to all item identifiers
 for which @p perThumbnailCompletionHandler had not been called.

 If there is no thumbnail for a given item, the @p perThumbnailCompletionHandler
 should be called with its @p imageData and @p error parameters both
 set to nil.

 If the system decides that an in-flight thumbnail request is not needed anymore,
 it will call the returned @p NSProgress object's @p -cancel method,
 at which time the implementation should clean up any held resources.
 */
- (NSProgress *)fetchThumbnailsForItemIdentifiers:(NSArray<NSFileProviderItemIdentifier> *)itemIdentifiers
                                    requestedSize:(CGSize)size
                    perThumbnailCompletionHandler:(void (^)(NSFileProviderItemIdentifier identifier, NSData * _Nullable imageData, NSError * _Nullable error))perThumbnailCompletionHandler
                                completionHandler:(void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_NAME(fetchThumbnails(for:requestedSize:perThumbnailCompletionHandler:completionHandler:)) API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  FileProvider.framework/Headers/NSFileProviderService.h
//
//  NSFileProviderService.h
//  FileProvider
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderExtension.h>
#import <FileProvider/NSFileProviderItem.h>

NS_ASSUME_NONNULL_BEGIN

@class NSXPCListenerEndpoint;

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol NSFileProviderServiceSource

/**
 The service name that uniquely identifies the service (using reverse domain
 name notation for you service name is recommended).
 */
@property (readonly, copy, nonatomic) NSFileProviderServiceName serviceName;

/**
 Return an endpoint object to allow the client application to connect to the
 file provider.
 The endpoint is retrieved from an anonymous @c NSXPCListener that the file
 provider creates. The file provider is in charge of accepting incoming
 @c NSXPCConnection's via @c -[NSXPCListenerDelegate listener:shouldAcceptNewConnection:],
 and setting up properties on the new connection, like its exported object and
 interfaces (that both the file provider and the client application have agreed
 on).
 */
- (nullable NSXPCListenerEndpoint *)makeListenerEndpointAndReturnError:(NSError **)error;

@end

/**
 A file provider can override the method in this category to return service
 sources that provide custom communication channels to client applications.
 The service sources must be tied to the item identified by @c itemIdentifier.
 Client applications can retrieve the list of supported services by calling
 @c -[NSFileManager getFileProviderServicesForItemAtURL:] for a specific item URL.
 */
@interface NSFileProviderExtension (NSFileProviderService)

- (nullable NSArray <id <NSFileProviderServiceSource>> *)supportedServiceSourcesForItemIdentifier:(NSFileProviderItemIdentifier)itemIdentifier error:(NSError **)error NS_SWIFT_NAME(supportedServiceSources(for:)) API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end

NS_ASSUME_NONNULL_END

// ==========  FileProvider.framework/Headers/NSFileProviderActions.h
//
//  NSFileProviderActions.h
//  FileProvider
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 This category encapsulates common user-driven actions on FileProvider's items.
 */
@interface NSFileProviderExtension (NSFileProviderActions)

/**
 Import a document.

 The file or package at fileURL should be moved on disk into the file provider's
 own storage, where it will later be uploaded.  The completion block should be
 executed after the move on disk, but before the upload.  Before doing any
 network, actually.

 In the completion block, importedDocumentItem should have these properties set:
   - itemIdentifier
   - parentItemIdentifier (to the value passed in to this method)
   - filename (to fileURL's resource value for key NSURLNameKey)
   - creationDate (to NSURLCreationDateKey)
   - contentModificationDate (to NSURLContentModificationDateKey)
   - typeIdentifier (to NSURLTypeIdentifierKey)
   - documentSize (to NSURLTotalFileSizeKey on a flat file, or to the sum of the
     files sizes for a package)
   - capabilities

 [fileURL startAccessingSecurityScopedResource] needs to be called prior to
 accessing this security scoped URL, and stopAccessingSecurityScopedResource
 needs to be called when done.

 Note that itemIdentifier should be set with no network call.  It doesn't have
 to be the final identifier.  If the identifier changes after talking to the
 server then the file provider should send a delete for the temporary, local
 identifier immediately followed by an add with the final identifier.

 This is expected to work offline even if there might be a collision (another
 item with the same filename and parentItemIdentifier) only detected when later
 syncing up this change to the server.  In that case, it is suggested that a
 follow up update to the item change its filename to something unique.  This
 wouldn't be considered an error to import.

 If however you can tell right away, with no communication to your server, that
 there is a collision then this call should fail with error code
 NSFileProviderErrorFilenameCollision generated with this method:
   -[NSError (NSFileProviderError) fileProviderErrorForCollisionWithItem:].

 The existing item set in this error will be used to handle the collision, and
 ask the user if she or he would like to replace the existing item.  This takes
 into account the existing item's capabilities (particularly
 NSFileProviderItemCapabilitiesAllowsTrashing and AllowsDeleting.)

 Collision checks should be case insensitive even if the filesystem or file
 provider might allow two coexisting filenames differing only by their case.

 Upload errors (such as NSFileProviderErrorInsufficientQuota) should be handled
 with a subsequent update to the item, setting its uploadingError property.
 Upload errors should not prevent creating or importing a document, because they
 can be resolved at a later date (for example, when the user has quota again.)

 Other errors will be presented to the user, but are unexpected.  If you want to
 prevent imports in a given directory, then the directory item's capacities
 should exclude NSFileProviderItemCapabilitiesAllowsAddingSubItems.
 */
- (void)importDocumentAtURL:(NSURL *)fileURL
     toParentItemIdentifier:(NSFileProviderItemIdentifier)parentItemIdentifier
          completionHandler:(void (^)(NSFileProviderItem _Nullable importedDocumentItem, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 Create a directory.

 This is expected to complete before doing any network.

 In the completion block, createdDirectoryItem should have these properties set:
 - itemIdentifier
 - parentItemIdentifier (to the value passed in to this method)
 - filename (to directoryName)
 - creationDate (to the current date and time)
 - typeIdentifier (to "public.folder")
 - childItemCount (to 0)
 - capabilities

 Errors (including collision errors) are handled as documented for the import
 method above.  Directory creation is gated by the capabilities of the
 destination directory, with NSFileProviderItemCapabilitiesAllowsAddingSubItems.
 */
- (void)createDirectoryWithName:(NSString *)directoryName
         inParentItemIdentifier:(NSFileProviderItemIdentifier)parentItemIdentifier
              completionHandler:(void (^)(NSFileProviderItem _Nullable createdDirectoryItem, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 Rename a document or a directory.

 This is expected to complete before doing any network.

 itemName is the full file or directory name, complete with its file extension.
 In the completion block, property renamedItem.filename should change to
 itemName.  Property renamedItem.displayName should also be updated if you
 chose to overwrite that method.

 Errors (including collision errors) are handled as documented for the import
 method above.  Renames are gated by the capabilities of the renamed item, with
 NSFileProviderItemCapabilitiesAllowsRenaming.
 */
- (void)renameItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                          toName:(NSString *)itemName
               completionHandler:(void (^)(NSFileProviderItem _Nullable renamedItem, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 Move an item to a new directory.

 This is expected to complete before doing any network.

 If newName is non null, the moved item should be renamed to newName.

 Errors (including collision errors) are handled as documented for the import
 method above.  Moves are gated by the capabilities of both the moved item with
 NSFileProviderItemCapabilitiesAllowsReparenting, and the destination directory
 with NSFileProviderItemCapabilitiesAllowsAddingSubItems.
 */
- (void)reparentItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
        toParentItemWithIdentifier:(NSFileProviderItemIdentifier)parentItemIdentifier
                           newName:(nullable NSString *)newName
                 completionHandler:(void (^)(NSFileProviderItem _Nullable reparentedItem, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 Move an item to the trash.

 In the completion block, property trashedItem.isTrashed should be set to YES.
 You should keep track of the original parentItemIdentifier of the item before
 it was moved to trash, so you can move the item back where it used to be in the
 untrash method.  You could use the trashedItem.parentItemIdentifier property
 for that.

 The trashed item should continue to belong to the working set of documents
 cached on the device and visible offline to the user.  But if it is a
 directory, then all of its children should be removed from the working set and
 the file provider extension should send deletion events to make sure that they
 no longer appear in the recent lists.

 It is also suggested that shared documents be unshared when trashed.

 Trash is gated by the capabilities of the trashed item with
 NSFileProviderItemCapabilitiesAllowsTrashing.
 */
- (void)trashItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
              completionHandler:(void (^)(NSFileProviderItem _Nullable trashedItem, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 Move an item out of the trash.

 If parentItemIdentifier is nil, the file provider should attempt to put the
 item back where it was when it was moved to the trash; otherwise it should move
 it to this new parent.

 If the item is a directory, then the file provider extension should enumerate
 the children and send addition events in the working set so that the documents
 in the now untrashed directory may be reindexed.

 Untrash is gated by the capabilities of the destination directory, with
 NSFileProviderItemCapabilitiesAllowsAddingSubItems.
 */
- (void)untrashItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
           toParentItemIdentifier:(nullable NSFileProviderItemIdentifier)parentItemIdentifier
                completionHandler:(void (^)(NSFileProviderItem _Nullable untrashedItem, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 Delete an item forever.

 This is called when the user deletes an item that was already in the Trash and
 the item should no longer appear there after this call.  This call should
 remove the item from the working set.

 Delete is gated by the capabilities of the removed item with
 NSFileProviderItemCapabilitiesAllowsDeleting.
 */
- (void)deleteItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
               completionHandler:(void (^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 Mark an item as recently used, or clear its lastUsedDate if nil.

 This last used date is the sort key for the recent lists.  It is the primary
 hint that an item must belong to the working set cached and indexed on the
 user's device.

 The file provider is asked to persist the new last used date on disk, then call
 the completion callback with the updated last used date.  At a later point, the
 file provider should sync the new last used date to their server.

 The error parameter is here for debugging purposes alone; it won't be presented
 to the user or otherwise handled, but it will be logged.
 */
- (void)setLastUsedDate:(nullable NSDate *)lastUsedDate
      forItemIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
      completionHandler:(void (^)(NSFileProviderItem _Nullable recentlyUsedItem, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 Tag an item, or untag it if tagData is nil.

 The file provider is asked to persist the new tag data on disk, then call the
 completion callback with the updated tagged data.  At a later point, the file
 provider should sync the new tag data to their server.

 Tagged items are relevant to the user and should be in the working set even if
 they haven't been used recently.

 If set, the error will be immediately presented to the user and the item just
 won't be tagged.

 On shared items, tags should sync across the devices of any one participant but
 shouldn't sync across users.
 */
- (void)setTagData:(nullable NSData *)tagData
 forItemIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
 completionHandler:(void(^)(NSFileProviderItem _Nullable taggedItem, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 Mark a directory as favorite (or no longer favorite if favoriteRank is nil.)

 The favorite rank is used to represent the relative order of two favorite
 directories in the UI.  It is a 64 bit unsigned integer.  It needs to be synced.

 Favorite directories are relevant to the user and should be in the working set
 even if they haven't been used recently.  The documents and directories in the
 favorite directory however don't all have to be in the working set, and don't
 all have to be made accessible offline.

 The file provider is asked to persist the new favorite rank on disk, then call
 the completion callback with the updated favorite rank.  At a later point, the
 file provider should sync the new favorite rank to their server.
 */
- (void)setFavoriteRank:(nullable NSNumber *)favoriteRank
      forItemIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
      completionHandler:(void (^)(NSFileProviderItem _Nullable favoriteItem, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  FileProvider.framework/Headers/NSFileProviderExtension.h
//
//  NSFileProviderExtension.h
//
//  Copyright (c) 2014-2017 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderItem.h>

NS_ASSUME_NONNULL_BEGIN

@class NSFileProviderDomain;

API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NSFileProviderExtension : NSObject

/**
 Should return the URL corresponding to a specific identifier. Fail if it's not a subpath of documentStorageURL.

 This is a static mapping; each identifier must always return a path corresponding to the same file. By default, this returns the path relative to the path returned by documentStorageURL.
 */
- (nullable NSURL *)URLForItemWithPersistentIdentifier:(NSFileProviderItemIdentifier)identifier;
- (nullable NSFileProviderItemIdentifier)persistentIdentifierForItemAtURL:(NSURL *)url;

- (nullable NSFileProviderItem)itemForIdentifier:(NSFileProviderItemIdentifier)identifier error:(NSError * _Nullable *)error NS_SWIFT_NAME(item(for:)) API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/**
 This method is called when a placeholder URL should be provided for the item at the given URL.

 The implementation of this method should call +[NSFileProviderManager writePlaceholderAtURL:withMetadata:error:] with the URL returned by +[NSFileProviderManager placeholderURLForURL:], then call the completion handler.
 */
- (void)providePlaceholderAtURL:(NSURL *)url completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/** Should ensure that the actual file is in the position returned by URLForItemWithPersistentIdentifier:, then call the completion handler */
- (void)startProvidingItemAtURL:(NSURL *)url completionHandler:(void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_NAME(startProvidingItem(at:completionHandler:));

/**
 Called after the last claim to the file has been released. At this point, it is safe for the file provider to remove the content file.

 Care should be taken that the corresponding placeholder file stays behind after the content file has been deleted.
 */
- (void)stopProvidingItemAtURL:(NSURL *)url NS_SWIFT_NAME(stopProvidingItem(at:));

/** Called at some point after the file has changed; the provider may then trigger an upload */
- (void)itemChangedAtURL:(NSURL *)url;

@end

@interface NSFileProviderExtension (Deprecated)

// Writes out a placeholder at the specified URL. The URL should be one returned by placeholderURLForURL:; if URL resource values are
// requested, the system will consult the placeholder before consulting your app extension.
// Metadata contains NSURLNameKey, NSURLFileSizeKey, NSURLIsPackageKey
+ (BOOL)writePlaceholderAtURL:(NSURL *)placeholderURL withMetadata:(NSDictionary <NSURLResourceKey, id> *)metadata error:(NSError **)error API_DEPRECATED("Use the corresponding method on NSFileProviderManager instead", ios(8.0, 11.0)) API_UNAVAILABLE(macos, tvos, watchos);

// Returns the designated placeholder URL for a given URL. This placeholder will be consulted before falling back to your app extension to
// enhance performance. To write out a placeholder, use the writePlaceHolderAtURL: method above.
+ (NSURL *)placeholderURLForURL:(NSURL *)url API_DEPRECATED_WITH_REPLACEMENT("NSFileProviderManager +placeholderURLForURL:", ios(8.0, 11.0)) API_UNAVAILABLE(macos, tvos, watchos);

// An identifier unique to this provider.
// When modifying the files stored in the directory returned by documentStorageURL, you should pass this identifier
// to your file coordinator's setPurposeIdentifier: method.
@property(nonatomic, readonly) NSString *providerIdentifier API_DEPRECATED_WITH_REPLACEMENT("NSFileProviderManager -providerIdentifier", ios(8.0, 11.0)) API_UNAVAILABLE(macos, tvos, watchos);

// The root URL for provided documents. This URL is derived by consulting the NSExtensionFileProviderDocumentGroup property on your extension. The document
// storage URL is the folder "File Provider Storage" in the corresponding container.
@property(nonatomic, readonly) NSURL *documentStorageURL API_DEPRECATED_WITH_REPLACEMENT("NSFileProviderManager -documentStorageURL", ios(8.0, 11.0)) API_UNAVAILABLE(macos, tvos, watchos);

@end

NS_ASSUME_NONNULL_END
