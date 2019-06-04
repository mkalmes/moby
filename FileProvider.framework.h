// ==========  FileProvider.framework/Headers/NSFileProviderEnumerating.h
//
//  NSFileProviderEnumerating.h
//  FileProvider
//
//  Copyright (c) 2014-2017 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderExtension.h>
#import <FileProvider/NSFileProviderItem.h>
#import <FileProvider/NSFileProviderSearchQuery.h>
#if TARGET_OS_OSX
#import <CoreGraphics/CoreGraphics.h>
#endif

NS_ASSUME_NONNULL_BEGIN

/**
 A user-defined chunk of data that defines a starting point to enumerate changes
 from.

 The size of a sync anchor should not exceed a combined 500 bytes.
 */
typedef NSData *NSFileProviderSyncAnchor NS_TYPED_EXTENSIBLE_ENUM;

/**
 A user- or system-defined chunk of data that defines a page to continue the
 enumeration from.  Initial enumeration is started from one of the below
 system-defined pages.

 The size of a page should not exceed 500 bytes.
 */
typedef NSData *NSFileProviderPage NS_TYPED_EXTENSIBLE_ENUM;

FOUNDATION_EXPORT API_AVAILABLE(ios(11.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos)
NSFileProviderPage const NSFileProviderInitialPageSortedByDate;
FOUNDATION_EXPORT API_AVAILABLE(ios(11.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos)
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
 signalEnumeratorForContainerItemIdentifier:completionHandler:] will trigger a
 call to enumerateFromSyncAnchor with the latest known sync anchor, giving the
 file provider (app or extension) a chance to notify about changes.

 The anchor data should contain whatever information is needed to resume
 enumerating changes from the previous synchronization point.  A naive sync
 anchor might for example be the date of the last change that was sent from the
 server to the client, meaning that at that date, the client was in sync with
 all the server changes.  A request to enumerate changes from that sync anchor
 would only return the changes that happened after that date, which are
 therefore changes that the client doesn't yet know about.

 NOTE that the change-based observation methods are marked optional for historical
 reasons, but are really required. System performance will be severely degraded if
 they are not implemented.
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
 -[NSFileProviderManager signalEnumeratorForContainerItemIdentifier:
 completionHandler:] and again, the system will enumerate changes until
 finishEnumeratingChangesUpToSyncAnchor: is called with moreComing:NO.

 NOTE that the change-based observation methods are marked optional for historical
 reasons, but are really required. System performance will be severely degraded if
 they are not implemented.
*/

- (void)currentSyncAnchorWithCompletionHandler:(void(^)(_Nullable NSFileProviderSyncAnchor currentAnchor))completionHandler;


#if TARGET_OS_OSX
/**
 Notify that the window that is presenting this enumerator has become frontmost.

 This method will only be called if the enumerator was instantiated to subscribe to
 live updates for a single document, as described under enumeratorForContainerItemIdentifier:error:
 below. The extension must have been granted access to presence information; see
 NSFileProviderExtension -requestPresenceAuthorization.
 */
- (void)didPresentEnumeratorInWindow:(CGWindowID)window frontmost:(BOOL)frontmost API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos) NS_SWIFT_NAME(didPresent(in:frontmost:));
#endif

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

/**
 Create an enumerator for all items matching a given search query.

 In order to be invoked to perform a remote search a provider needs to specify
 in its plist an array of supported search filters under the property name
 NSExtensionFileProviderSupportedSearchCapabilities. The allowed values are:
   - NSExtensionFileProviderSearchByFilename
   - NSExtensionFileProviderSearchByContentType
   - NSExtensionFileProviderSearchScopedToDirectory

 NSExtensionFileProviderSearchByFilename is always assumed to be available.

 The enumerator returned will be invalidated when the search results are
 discarded.

 If returning nil, you must set the error out parameter.
 */
- (nullable id<NSFileProviderEnumerator>)enumeratorForSearchQuery:(NSFileProviderSearchQuery *)searchQuery
                                                            error:(NSError **)error API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

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
API_AVAILABLE(ios(11.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos)
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


/* If set, the domain is present, but disconnected from its extension.
 In this state, the user continues to be able to browse the domain's contents,
 but the extension doesn't receive updates on modifications to the files, nor is
 it consulted to update folder's contents.

 The disconnected state can be modified on an existing domain by recreating a domain
 with the same identifier, then passing it to addDomain.
 */
@property (readwrite, getter=isDisconnected) BOOL disconnected API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

@end

API_AVAILABLE(ios(11.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos)
@interface NSFileProviderExtension (NSFileProviderDomain)
@property(nonatomic, readonly, nullable) NSFileProviderDomain *domain;
@end

NS_ASSUME_NONNULL_END

// ==========  FileProvider.framework/Headers/NSFileProviderRequest.h
//
//  NSFileProviderRequest.h
//  FileProvider
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderExtension.h>
#import <FileProvider/NSFileProviderManager.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos)
@interface NSFileProviderRequest : NSObject
/**
 An identifier for the application. The identifier is system-specific and may
 change between different installations of the application.
 */
@property (nonatomic, readonly, strong) NSUUID *requestingApplicationIdentifier;

/**
 The following properties are available only after user opt-in, via the
 -requestPresenceAuthorization method on NSFileProviderManager.
 */
@property (nonatomic, readonly, copy, nullable) NSURL *requestingExecutable API_UNAVAILABLE(ios);

@end

@interface NSFileProviderExtension (Request)
- (nullable NSFileProviderRequest *)currentRequest API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);
@end


typedef NS_ENUM(NSUInteger, NSFileProviderPresenceAuthorizationStatus) {
    NSFileProviderPresenceAuthorizationNotDetermined,
    NSFileProviderPresenceAuthorizationRestricted,
    NSFileProviderPresenceAuthorizationDenied,
    NSFileProviderPresenceAuthorizationAllowed
};

@interface NSFileProviderManager (Presence)

@property (nonatomic, assign, readonly) NSFileProviderPresenceAuthorizationStatus presenceAuthorizationStatus API_UNAVAILABLE(ios);

/**
 If (presenceAuthorizationStatus == NSFileProviderPresenceAuthorizationNotDetermined),
 presents a dialog requesting authorization to share additional information
 about requests with the provider.

 The authorization dialog will display the contents of the
 NSFileProviderPresenceUsageDescription key.  The key must be present in the
 app's Info.plist.
 */
- (void)requestPresenceAuthorization API_UNAVAILABLE(ios);

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
#import <FileProvider/NSFileProviderItem.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSErrorDomain const NSFileProviderErrorDomain API_AVAILABLE(ios(11.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos);

FOUNDATION_EXPORT NSString * const NSFileProviderErrorCollidingItemKey API_DEPRECATED("NSFileProviderErrorItemKey", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);
FOUNDATION_EXPORT NSString * const NSFileProviderErrorItemKey API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);
FOUNDATION_EXPORT NSString * const NSFileProviderErrorNonExistentItemIdentifierKey API_AVAILABLE(ios(11.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos);

typedef NS_ERROR_ENUM(NSFileProviderErrorDomain, NSFileProviderErrorCode) {
    /** The user credentials cannot be verified */
    NSFileProviderErrorNotAuthenticated  = -1000,

    /** An item already exists with the same parentItemIdentifier and filename (or with a filename differing only in case.)

     \note Please use -[NSError (NSFileProviderError) fileProviderErrorForCollisionWithItem:] to build an error with this code.
     \see -[NSError (NSFileProviderError) fileProviderErrorForCollisionWithItem:]
     */
    NSFileProviderErrorFilenameCollision = -1001,

    /** The value of the sync anchor is too old, and the system must re-sync from scratch */
    NSFileProviderErrorSyncAnchorExpired = -1002,

    /** The value of the page token is too old, and the system must re-sync from scratch */
    NSFileProviderErrorPageExpired        = NSFileProviderErrorSyncAnchorExpired,

    /** The item has not been uploaded because it would push the account over quota */
    NSFileProviderErrorInsufficientQuota = -1003,

    /** Connecting to the servers failed */
    NSFileProviderErrorServerUnreachable = -1004,

    /** The requested item doesn't exist

     \note Please use -[NSError (NSFileProviderError) fileProviderErrorForNonExistentItemWithIdentifier:] to build an error with this code.
     \see -[NSError (NSFileProviderError) fileProviderErrorForNonExistentItemWithIdentifier:]
     */
    NSFileProviderErrorNoSuchItem        = -1005,

    /** The requested version is not the latest version of the file.

     \note Please use -[NSError (NSFileProviderError) fileProviderErrorForOutOfDateItem:] to build an error with this code.
     \see -[NSError (NSFileProviderError) fileProviderErrorForOutOfDateItem:]
     */
    NSFileProviderErrorVersionOutOfDate API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos) = -1006,

    /** We're trying to non-recursively delete a non-empty directory
     */
    NSFileProviderErrorDirectoryNotEmpty API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos) = -1007,

} API_AVAILABLE(ios(11.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos);

@interface NSError (NSFileProviderError)
+ (instancetype)fileProviderErrorForCollisionWithItem:(NSFileProviderItem)existingItem API_AVAILABLE(ios(11.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos);
+ (instancetype)fileProviderErrorForNonExistentItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier API_AVAILABLE(ios(11.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos);
+ (instancetype)fileProviderErrorForOutOfDateItem:(NSFileProviderItem)updatedVersion NS_SWIFT_NAME(fileProviderErrorForOutOfDateItem(_:)) API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

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
#import <FileProvider/NSFileProviderDomain.h>

NS_ASSUME_NONNULL_BEGIN

@class NSURLSessionTask;
@class NSFileProviderDomain;


/**
 The file provider manager allows you to communicate with the file provider
 framework for purposes that may be relevant from both the extension and
 the containing application (or sibling extensions).

 The file provider framework will invoke your file provider extension in response
 to those calls if appropriate.

 The class also provides methods to manage provider domains. Each domain has a
 corresponding manager.
 */
API_AVAILABLE(ios(11.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos)
@interface NSFileProviderManager : NSObject

- (instancetype)init NS_UNAVAILABLE;

/**
Return the manager responsible for the default domain.
 */
@property (class, readonly, strong) NSFileProviderManager *defaultManager API_UNAVAILABLE(macos);

/**
 Return the manager for the specified domain.
 */
+ (nullable instancetype)managerForDomain:(NSFileProviderDomain *)domain;

/**
 Call this method either in the app or in the extension to trigger an
 enumeration, typically in response to a push.

 Set the containerItemIdentifier to the identifier of the enumerated container
 that was specified in
 -[NSFileProviderExtension enumeratorForContainerItemIdentifier:error:]

 This will trigger another call to
 -[NSFileProviderEnumerator enumerateChangesForObserver:fromSyncAnchor:]
 and the UI will be refreshed, giving the user live updates on the presented
 enumeration.

 If you have a change in the working set, call this method with
 containerItemIdentifier set to NSFileProviderWorkingSetContainerItemIdentifier,
 even if there is no live enumeration for this item.  The working set is cached
 on the device and it's important to keep the cache in sync.

 In addition to using this method, your application/extension can register for
 pushes using the PKPushTypeFileProvider push type. Pushes of the form
 {
     container-identifier = "<identifier>"
     domain = "<domain identifier>"
 }
 with a topic of "<your application identifier>.pushkit.fileprovider" will be
 translated into a call to signalEnumeratorForContainerItemIdentifier:completionHandler:.
 */
- (void)signalEnumeratorForContainerItemIdentifier:(NSFileProviderItemIdentifier)containerItemIdentifier completionHandler:(void (^)(NSError * __nullable error))completion NS_SWIFT_NAME(signalEnumerator(for:completionHandler:));

/**
 Registers the given NSURLSessionTask to be responsible for the specified item.
 A given item can only have one task registered at a time. The task must be
 suspended at the time of calling.
 The task's progress is displayed on the item when the task is executed.
 */
- (void)registerURLSessionTask:(NSURLSessionTask *)task forItemWithIdentifier:(NSFileProviderItemIdentifier)identifier completionHandler:(void (^)(NSError * __nullable error))completion;

/**
 Return the user visible URL for an item identifier.

 Calling this method marks the calling process in such a way that accessing
 files will not trigger materialization; instead, accesses to unmd
 files will fail with EDEADLK.
 */
- (void)getUserVisibleURLForItemIdentifier:(NSFileProviderItemIdentifier)itemIdentifier completionHandler:(void (^)(NSURL * __nullable userVisibleFile, NSError * __nullable error))completionHandler API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_NAME(getUserVisibleURL(for:completionHandler:));


/**
 Return the identifier and domain for a user visible URL.

 This method returns the identifier and domain of a user visible URL if
 applicable. Calling this method on a file which doesn't reside in your
 provider/domain will return the Cocoa error NSFileNoSuchFileError.
 */
+ (void)getIdentifierForUserVisibleFileAtURL:(NSURL *)url completionHandler:(void (^)(NSFileProviderItemIdentifier __nullable itemIdentifier, NSFileProviderDomainIdentifier __nullable domainIdentifier, NSError * __nullable error))completionHandler API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);



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

 If the NSExtensionFileProviderDocumentGroup property is not set, calling this
 method will result in an error.
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
+ (void)addDomain:(NSFileProviderDomain *)domain completionHandler:(void(^)(NSError *_Nullable error))completionHandler;

/**
 Remove a domain.
 */
+ (void)removeDomain:(NSFileProviderDomain *)domain completionHandler:(void(^)(NSError *_Nullable error))completionHandler;

/**
 Get all registered domains.
 */
+ (void)getDomainsWithCompletionHandler:(void (^)(NSArray<NSFileProviderDomain *> *domains, NSError * _Nullable error))completionHandler;

/**
 Remove all registered domains.
 */
+ (void)removeAllDomainsWithCompletionHandler:(void(^)(NSError *_Nullable error))completionHandler;

@end

@interface NSFileProviderManager (Import)

/** Request the creation of a new domain that will take ownership of on-disk data that
 were previously managed without a file provider.

 You can use this method in order to migrate from a software that managed a file hierarchy
 on disk to a NSFileProviderExtension without having to redownload the data that was
 already on disk.

 The URL is expected to point to a directory. That directory will be moved away, its
 ownership being taken by the system. From this point, your extension's
 createItemFromTemplate method will be called for every item found in the directory
 with the special NSFileProviderCreateItemOptionsItemMayAlreadyExist option.

 In case a domain with the same name already exists in the file provider manager, the
 call will fail with the code NSFileWriteFileExistsError. The URL will remain untouched.
 In case the system does not allow the extension to request a migration, the call will
 fail with NSFeatureUnsupportedError.

 In case of success, the URL will become invalid and the domain will be created. The
 completion handler is called as soon as the domain is created. Your provider will
 receive calls to createItemBasedOnTemplate afterward.

 When the import of the file hierarchy is finished, the system calls
 -[NSFileProviderExtension signalDidFinishImportingItemsFromDiskWithCompletionHandler:].
 In case -[NSFileProviderManager reimportItemsBelowItemWithIdentifier:completionHandler:]
 is called before the end of the import, a single call to importDidFinishWithCompletionHandler
 will be received for both the import and the scan.
 */
+ (void)importDomain:(NSFileProviderDomain *)domain fromDirectoryAtURL:(NSURL *)url completionHandler:(void(^)(NSError * _Nullable error))completionHandler
API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

/** Notify the system that the itemIdentifiers known by the system are not valid anymore.

 This can be called by an extension in case it has lost track of its synchronisation state
 and as a consequence is not able to guarantee the stability of the itemIdentifiers anymore.
 In that case, the system will trigger a scan of any data that is cached on disk and call
 createItemBasedOnTemplate with the special NSFileProviderCreateItemOptionsItemMayAlreadyExist
 option so that the extension can specify the new itemIdentifier for those items. The provided
 item identifier is inclusive, meaning the specified item will be re-import as well as any
 children in case it is a container.

 In case the extension has lost its synchronisation state but is still able to guarantee the
 stability of the itemIdentifiers, it should make sure that querying the working set
 enumerator with an anchor that predates the synchronisation loss will cause a
 NSFileProviderErrorSyncAnchorExpired error.

 In case the extension has lost its synchronisation state and is not interested in preserving
 the data cached on disk, it can remove and re-add the affected domain.

 The completion handler is called immediately and does not reflect the end of the import.
 When the import of the file hierarchy is finished, the system calls
 -[NSFileProviderExtension importDidFinishWithCompletionHandler:].

 If this method succeeds, the system will reimport at least the requested sub-tree, but may
 import more.

 If the requested item has no on-disk representation, the completion handler will be called with
 a NSFileProviderErrorNoSuchItem error.
 */
- (void)reimportItemsBelowItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                           completionHandler:(void (^)(NSError * _Nullable error))completionHandler
    NS_SWIFT_NAME(reimportItems(below:completionHandler:))
    API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

@end

/**
 Policy regarding download and caching of an item by the system.
 */
typedef NS_ENUM(NSUInteger, NSFileProviderDownloadPolicy) {
    /**
     By default, files are downloaded on demand (e.g. when explicitely open by
     the user) and may be evicted when needed (e.g. on low disk pressure.)
     */
    NSFileProviderDownloadPolicyDefault = 0,

    /**
     Download this item when appropriate, minding shared resources like
     available disk space.

     Set this policy on files that are likely to be needed by the user in the
     near future.
     */
    NSFileProviderDownloadPolicySpeculative = 1,

    /**
     Download this item and keep it downloaded forever.

     This policy applies recursively to all the items in a directory.
     Set this policy only on files that the user must keep locally available for
     offline use; abusing this policy causes shared resources like availabe disk
     space to run out.
     */
    NSFileProviderDownloadPolicyKeepDownloaded = 2,
} API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

@interface NSFileProviderManager (DownloadAndEviction)

/**
 Trigger a download or change the download policy.
 See the documentation on the download policies for details.

 The completion handler is called to acknowledge the change of policy: the
 actual downloads are scheduled asynchronously when appropriate.
 */
- (void)downloadItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                    downloadPolicy:(NSFileProviderDownloadPolicy)downloadPolicy
                 completionHandler:(void (^)(NSError * _Nullable))completionHandler
    API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

/**
 Request that the system removes an item from its cache.

 This removes the contents of a file, or the metadata and contents of all the
 files in a directory.  It resets the download policies of all the evicted
 items back to the default policy.

 The completion handler is called when the item has been evicted from disk.
 */
- (void)evictItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
              completionHandler:(void (^)(NSError * _Nullable))completionHandler
    API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

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

/**
  @framework FileProvider
  @abstract A framework for providing files on demand.
  @discussion The FileProvider framework allows content providers
   and storage services to provide files to file browsers and applications.
 */

#import <FileProvider/NSFileProviderDomain.h>
#import <FileProvider/NSFileProviderExtension.h>
#import <FileProvider/NSFileProviderEnumerating.h>
#import <FileProvider/NSFileProviderError.h>
#import <FileProvider/NSFileProviderItem.h>
#import <FileProvider/NSFileProviderManager.h>
#import <FileProvider/NSFileProviderActions.h>
#import <FileProvider/NSFileProviderService.h>
#import <FileProvider/NSFileProviderThumbnailing.h>
#import <FileProvider/NSFileProviderMaterializedSet.h>
#import <FileProvider/NSFileProviderRequest.h>
#import <FileProvider/NSFileProviderItemDecoration.h>
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
FOUNDATION_EXPORT NSFileProviderItemIdentifier const NSFileProviderRootContainerItemIdentifier NS_SWIFT_NAME(NSFileProviderItemIdentifier.rootContainer) API_AVAILABLE(ios(11.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos);

/**
 The item identifier of the working set, a synthetic container used by the
 extension to communicate changes to the system even when the parent directories
 of these items aren't actively being enumerated.  Items in this set should have
 their parentItemIdentifier set to the identifier of their parent directory.

 The working set is the set of files and directories that should be made
 available to the system regardless of the local browsing history.  Files listed
 in the working set are indexed in the local Spotlight index and appear in
 offline search results.  They contribute to the Recents view of the Files app,
 sorted by lastUsedDate, and it is therefore important to provide a consistent
 experience across devices by including in the working set all the documents
 recently used, trashed, favorited, shared or tagged.

 The Spotlight index and the Recents view will show outdated information unless
 the file provider extension keeps the working set up to date with local and
 remote changes.  When an item in the working set is remotely modified, the
 extension calls -signalEnumeratorForContainerItemIdentifier: on the identifier
 of the working set; the system will then enumerate changes and update its caches.

 Starting in iOS 12 and macOS 10.15, the system maintains a cache on the local
 file system of files and directories previously enumerated.  The working set
 is the container used to update that set of files.  The extension may know
 whether an item is in that set by checking whether its parentItemIdentifier
 is listed in the materialized containers, see the documentation on
 -materializedItemsDidChangeWithCompletionHandler:.
 */
FOUNDATION_EXPORT NSFileProviderItemIdentifier const NSFileProviderWorkingSetContainerItemIdentifier NS_SWIFT_NAME(NSFileProviderItemIdentifier.workingSet) API_AVAILABLE(ios(11.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos);


/**
 A version blob, used for either structure or content.

 Version blobs are limited to 128 bytes in size.
 */
typedef NSData *NSFileProviderVersionData NS_TYPED_EXTENSIBLE_ENUM;

API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos)
@interface NSFileProviderItemVersion : NSObject

/**
 Items versions have two distinct components, one for the file contents and one
 for metadata.  Bumping the right component on a change allows for important
 optimizations.
 */
- (instancetype)initWithContentVersion:(NSFileProviderVersionData)contentVersion
                       metadataVersion:(NSFileProviderVersionData)metadataVersion;

/**
 Version data for the content of the file.  The system will typically ask for a
 new download of the file if this field changes and the file was already
 downloaded.

 This property is used to invalidate the thumbnail cache maintained by the system.

 Note that the resource fork of the file is considered content, so this version
 data should change when either the data fork or the resource fork changes.
 */
@property (nonatomic, readonly) NSFileProviderVersionData contentVersion;

/**
 Version data for the metadata of the item, i.e everything but the data fork and
 the resource fork.  The system will typically update a dataless representation
 of the file if this changes; but it will not ask for a new download.
 */
@property (nonatomic, readonly) NSFileProviderVersionData metadataVersion;

@end


/**
 A special value for favorite ranks, to use when no rank was set when the item
 was favorited.
 */
FOUNDATION_EXPORT unsigned long long const NSFileProviderFavoriteRankUnranked API_AVAILABLE(ios(11.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos);

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

@protocol NSFileProviderItemFlags <NSObject>

@property (nonatomic, readonly, getter=isUserExecutable) BOOL userExecutable;
@property (nonatomic, readonly, getter=isUserReadable) BOOL userReadable;
@property (nonatomic, readonly, getter=isUserWritable) BOOL userWritable;

@property (nonatomic, readonly, getter=isHidden) BOOL hidden;
@property (nonatomic, readonly, getter=isPathExtensionHidden) BOOL pathExtensionHidden;
@end

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

/**
 The flags of the item. Flags define on-disk properties of the item but are
 also taken into account by the UI to determine item actions.
 */
@property (nonatomic, readonly, strong, nullable) id <NSFileProviderItemFlags> flags API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

@property (nonatomic, readonly, copy, nullable) NSNumber *documentSize;
@property (nonatomic, readonly, copy, nullable) NSNumber *childItemCount;
@property (nonatomic, readonly, copy, nullable) NSDate *creationDate;
@property (nonatomic, readonly, copy, nullable) NSDate *contentModificationDate;

/**
 Syncable extended attributes on the file.

 The system decides which extended attributes should be synced from the device,
 based on a set of rules largely inferred from the name of the extended
 attribute.  Extended attributes named with xattr_name_with_flags(XATTR_FLAG_SYNCABLE)
 will be listed in this dictionary; some extended attributes introduced before
 this API are also whitelisted for sync.

 Syncable xattrs are capped in size to about 32KiB total for a given item.
 When the set of extended attributes on a file is larger than that, the system
 demotes some of the extended attributes to non-syncable.

 The system decides which non-syncable extended attributes should be preserved
 locally when the item is updated remotely, based on a set of rules again largely
 inferred from the name of the extended attribute.  Extended attributes named
 with xattr_name_with_flags(XATTR_FLAG_CONTENT_DEPENDENT) will be preserved only
 if itemVersion.contentVersion was not modified by the remote update.

 Some NSFileProviderItem properties (lastUsedDate, tagData...) happen to be
 stored on disk in extended attributes that won't be listed in this dictionary
 because that would be redundant.  The 32 bits of Finder info in the extended
 attribute named XATTR_FINDERINFO_NAME ("com.apple.FinderInfo") is not listed
 here for the same reason: the syncable Finder info bits are deserialized to
 other properties of NSFileProviderItem.

 The system will set extended attributes on dataless files, and will preserve
 them when a file is rendered dataless.  I.e extended attributes are considered
 metadata, not content.  The resource fork however is considered content and
 will not be included in this dictionary.  Local changes to the resource fork
 will be communicated under NSFileProviderItemFieldContents.  Remote changes to
 the resource fork should bump itemVersion.contentVersion.
 */
@property (nonatomic, readonly, strong, nullable) NSDictionary <NSString *, NSData *> *extendedAttributes API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);


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

 This flag should only be set on the top-level item: trashing a directory sets
 this flag on the directory itself, but not on its children.

 Trashed items should remain in the working set; however, children of trashed
 directories should be removed from the working set.
 */
@property (nonatomic, readonly, getter=isTrashed) BOOL trashed;

/*
 The download and upload properties below determine which of the cloud badges
 (uploading, downloading, pending) will be shown on the item.
 */
@property (nonatomic, readonly, getter=isUploaded) BOOL uploaded;
@property (nonatomic, readonly, getter=isUploading) BOOL uploading;

/**
 An error that occurred while uploading to your remote server.

 \note Typical uploading errors include:
 - NSFileProviderErrorInsufficientQuota
 - NSFileProviderErrorServerUnreachable

 \seealso NSFileProviderErrorInsufficientQuota
 \seealso NSFileProviderErrorServerUnreachable
 */
@property (nonatomic, readonly, copy, nullable) NSError *uploadingError;

@property (nonatomic, readonly, getter=isDownloaded) BOOL downloaded;
@property (nonatomic, readonly, getter=isDownloading) BOOL downloading;
@property (nonatomic, readonly, copy, nullable) NSError *downloadingError;

/**
 Indicates that the file or directory is excluded from sync, i.e that
 local changes won't be communicated to the server.

 \note This is reflected in the UI, but the actual sync semantics are left to
 the discretion of the file provider extension.
 */
@property (nonatomic, readonly, getter=isExcludedFromSync) BOOL excludedFromSync
    API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

@property (nonatomic, readonly, getter=isMostRecentVersionDownloaded) BOOL mostRecentVersionDownloaded;

@property (nonatomic, readonly, getter=isShared) BOOL shared;
@property (nonatomic, readonly, getter=isSharedByCurrentUser) BOOL sharedByCurrentUser;

/**
 ownerNameComponents should be nil when sharedByCurrentUser is equal to YES or
 when the item is not shared.
 */
@property (nonatomic, strong, readonly, nullable) NSPersonNameComponents *ownerNameComponents;
@property (nonatomic, strong, readonly, nullable) NSPersonNameComponents *mostRecentEditorNameComponents;

/**
 The versionIdentifier is used to invalidate the thumbnail in the thumbnail cache.
 A content hash would be a reasonable choice.

 Version identifiers are limited to 1000 bytes.

 This property is deprecated in favor of the "itemVersion" property.
 */
@property (nonatomic, strong, readonly, nullable) NSData *versionIdentifier API_DEPRECATED("itemVersion", ios(11.0, 13.0)) API_UNAVAILABLE(tvos, watchos) API_UNAVAILABLE(macos);

/**
 The version is used to track which version of an item has been modified when informing a provider about changes. It is also used to invalidate the thumbnail cache.
 */
@property (nonatomic, strong, readonly, nullable) NSFileProviderItemVersion *itemVersion API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

/**
 Use this dictionary to add state information to the item. It is accessible to
 FileProviderUI action predicates and user interaction predicates [1].

 All values for this dictionary must be of type String, Number, Bool or Date.

 [1] UserInteraction can be defined when a user level action occurs with a file.

  - `NSFileProviderUserInteractions` *array*
    - `ActivationRule ` *string*, the predicate.
        @parameters predicates
            - `destinationItem`: FPActionOperation destinationItem (only present for move/copy)
            - `destinationItemHierarchy` : represents destinationItem and all its parent chain to allow for search
                on first item in hierarchy that has a given value.
            - `action` : FPActionOperation action (Reparent/Trash/Download...)
            - `sourceItem` : current item that the predicate is evaluating (not present if no source items)
            - `sourceItemHierarchy` : represents sourceItem and all its parent chain to allow for search
                on first item in hierarchy that has a given value.
            - `sourceItemsCount` :
                - In userInteraction, represents the count of sourceItems of FPOperation
                - In subUserInteraction: represents the count of items that matched the previous predicate
    - `Alert` *dictionary*
        - `LocalizedTitle` *string*, title of the alert
        - `LocalizedSubTitle` *string*, sub title of the alert
            - @parameters for LocalizedTitle/LocalizedSubTitle
                - `matchingItemsCount`: count of source items that matched the predicate (only present if matchingItemsCount > 0)
                - `matchingItemsCountMinusOne`: matchingItemsCount minus one (only present if matchingItemsCount > 1)
                - `matchingItemsCountMinusTwo`: matchingItemsCount minus two (only present if matchingItemsCount > 2)
                - `firstMatchingItem`: first sourceItem that matched the predicate (only present if matchingItemsCount > 1)
                - `secondMatchingItem`: second sourceItem that matched the predicate (only present if matchingItemsCount > 2)
        - `LocalizedRecoveryOptions`
            - `Continue` *string*, the string for the continue button - default value if not specified
            - `Cancel` *string*, the string for the cancel button - default value if not specified
        - `RecoveryOptions` (optional)
            - Can only remove continue button
            - `Continue` *bool*, the boolean for whether to have a continue button - default value is YES if not specified
    - `SubInteractions `: *dictionary* (same as `NSFileProviderUserInteractions`)

 For each interaction, either Alert or SubInteractions must be specified. SubInteractions will be evaluated if the main ActivationRule evaluates to
 YES for at least once. This allows you to match a general pattern via the top-level activation rule and then select a specialized error message from a list
 of subpatterns.

 Here is a sample extension Info.plist:

 ```
 <key>NSExtension</key>
 ...
 <key>NSFileProviderUserInteractions</key>
 <array>
    <key>ActivationRule</key>
    <string>action == Move</string>
    <key>SubInteractions</key>
    <array>
        <dict>
            <key>ActivationRule</key>
            <string>sourceItem.isShared == NO AND
                    destinationItem.isShared == YES AND
                    destinationItem.isSharedByCurrentUser == YES</string>
            <key>SubInteractions</key>
            <array>
                <dict>
                    <key>ActivationRule</key>
                    <string>sourceItemsCount == 1</string>
                    <key>Alert</key>
                    <dict>
                        <key>LocalizedTitle</key>
                        <dict>
                            <key>NSStringFormat</key>
                            <string>Are you sure you want to move %@ into %@?</string>
                            <key>NSStringFormatValues</key>
                            <array>
                                <string>firstMatchingItem.filename</string>
                                <string>destinationItem.filename</string>
                            </array>
                        </dict>
                        <key>LocalizedSubTitle</key>
                        <dict>
                            <key>NSStringFormat</key>
                            <string>If you move it, people added to the shared folder “%@” will be able to access it</string>
                            <key>NSStringFormatValues</key>
                            <array>
                                <string>destinationItem.filename</string>
                            </array>
                        </dict>
                        <key>LocalizedRecoveryOptions</key>
                        <array>
                            <key>Continue</key><string>Save to shared folder</string>
                        </array>
                    </dict>
                </dict>
            </array>
        </dict>
        <dict>
            <key>ActivationRule</key>
            <string>sourceItem.isShared == YES AND
                    sourceItem.isSharedByCurrentUser == NO AND
                    destinationItem.isSharedByCurrentUser == YES</string>
            <key>SubInteractions</key>
            <array>
                <dict>
                    <key>ActivationRule</key>
                    <string>sourceItemsCount == 1</string>
                    <key>Alert</key>
                    <dict>
                        <key>LocalizedTitle</key>
                        <dict>
                            <key>NSStringFormat</key>
                            <string>This shared item can't be moved.</string>
                        </dict>
                        <key>LocalizedSubTitle</key>
                        <dict>
                            <key>NSStringFormat</key>
                            <string>Items shared with you can’t be moved to shared folders</string>
                        </dict>
                    </dict>
                    <key>RecoveryOptions</key>
                    <dict>
                        <key>Continue</key>
                        <false/>
                    </dict>
                </dict>
            </array>
        </dict>
    </array>
 </array>
 ```
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

 The system will cache the thumbnail for the item, and the cache will be
 invalidated when itemVersion.contentVersion changes.
 */
- (NSProgress *)fetchThumbnailsForItemIdentifiers:(NSArray<NSFileProviderItemIdentifier> *)itemIdentifiers
                                    requestedSize:(CGSize)size
                    perThumbnailCompletionHandler:(void (^)(NSFileProviderItemIdentifier identifier, NSData * _Nullable imageData, NSError * _Nullable error))perThumbnailCompletionHandler
                                completionHandler:(void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_NAME(fetchThumbnails(for:requestedSize:perThumbnailCompletionHandler:completionHandler:)) API_AVAILABLE(ios(11.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos);

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

API_AVAILABLE(ios(11.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos)
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

- (nullable NSArray <id <NSFileProviderServiceSource>> *)supportedServiceSourcesForItemIdentifier:(NSFileProviderItemIdentifier)itemIdentifier error:(NSError **)error NS_SWIFT_NAME(supportedServiceSources(for:)) API_AVAILABLE(ios(11.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  FileProvider.framework/Headers/NSFileProviderSearchQuery.h
//
//  NSFileProviderSearchQuery.h
//  FileProvider
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderExtension.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos)
@interface NSFileProviderSearchQuery : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Specify that all result items must have in their filename the provided string
 or some variant thereof.
 */
@property (nonatomic, copy, readonly, nullable) NSString *filename;

/**
 Specify that all result items must be conform to at least one of the provided
 UTI.

 This property will always be nil unless the capability
 NSExtensionFileProviderSearchByContentType is listed in the provider's plist
 under NSExtensionFileProviderSupportedSearchCapabilities.
 */
@property (nonatomic, copy, readonly, nullable) NSSet<NSString*> *allowedContentTypes;

/**
 Returns the extensions corresponding to the allowedContentTypes defined above.

 This property will always be nil unless the capability
 NSExtensionFileProviderSearchByContentType is listed in the provider's plist
 under NSExtensionFileProviderSupportedSearchCapabilities.
*/
@property (nonatomic, copy, readonly, nullable) NSSet<NSString *> *allowedPathExtensions;

/**
 Specify that all result items must have for parent the specified item
 identifier or be one of its descendants. In other words the scope of search is
 all items recursively parented to the provided identifier.

 This property will always be equal to NSFileProviderRootContainerItemIdentifier
 unless the capability NSExtensionFileProviderSearchScopedToDirectory is listed
 in the provider's plist under NSExtensionFileProviderSupportedSearchCapabilities.
 */
@property (nonatomic, copy, readonly) NSFileProviderItemIdentifier scopedToItemIdentifier;

#pragma mark -

/**
 A unique identifier that may be used to signal an update in the list of results
 provided by the search enumerator. This identifier is valid as long as the
 search enumeration is alive. If used afterwards, the update is ignored.

 See signalEnumeratorForContainerItemIdentifier:completionHandler:.
 */
@property (nonatomic, copy, readonly) NSFileProviderItemIdentifier searchContainerItemIdentifier;

@end

@interface NSFileProviderSearchQuery (Deprecated)

// <rdar://problem/50372998> Remove deprecated methods from NSFileProviderSearchQuery.h
@property (nonatomic, copy, readonly, nullable) NSString *searchString API_DEPRECATED("Feature removed", macos(10.15, 10.15), ios(13.0, 13.0));
@property (nonatomic, copy, readonly, nullable) NSString *content API_DEPRECATED("Feature removed", macos(10.15, 10.15), ios(13.0, 13.0));

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
#import <FileProvider/NSFileProviderExtension.h>
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

 A reasonable way of organizing files in the file provider storage is:
     <file provider storage path>/<itemIdentifier>/<filename>.<extension>
 If the item identifier was to change, you should move the file on disk to
 update its path, under coordination with NSFileCoordinatorWritingForMoving.

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
          completionHandler:(void (^)(NSFileProviderItem _Nullable importedDocumentItem, NSError * _Nullable error))completionHandler API_DEPRECATED("createItem:fields:contents:options:completionHandler:", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);

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
              completionHandler:(void (^)(NSFileProviderItem _Nullable createdDirectoryItem, NSError * _Nullable error))completionHandler API_DEPRECATED("createItem:fields:contents:options:completionHandler:", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);


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
               completionHandler:(void (^)(NSFileProviderItem _Nullable renamedItem, NSError * _Nullable error))completionHandler API_DEPRECATED("itemChanged:baseVersion:changedFields:contents:completionHandler:", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);

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
                 completionHandler:(void (^)(NSFileProviderItem _Nullable reparentedItem, NSError * _Nullable error))completionHandler API_DEPRECATED("itemChanged:baseVersion:changedFields:contents:completionHandler:", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);

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
              completionHandler:(void (^)(NSFileProviderItem _Nullable trashedItem, NSError * _Nullable error))completionHandler API_DEPRECATED("itemChanged:baseVersion:changedFields:contents:completionHandler:", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);

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
                completionHandler:(void (^)(NSFileProviderItem _Nullable untrashedItem, NSError * _Nullable error))completionHandler API_DEPRECATED("itemChanged:baseVersion:changedFields:contents:completionHandler:", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);

/**
 Delete an item forever.

 This is called when the user deletes an item that was already in the Trash and
 the item should no longer appear there after this call.  This call should
 remove the item from the working set.

 Delete is gated by the capabilities of the removed item with
 NSFileProviderItemCapabilitiesAllowsDeleting.
 */
- (void)deleteItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
               completionHandler:(void (^)(NSError * _Nullable error))completionHandler API_DEPRECATED("deleteItemWithIdentifier:baseVersion:options:completionHandler:", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);

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
      completionHandler:(void (^)(NSFileProviderItem _Nullable recentlyUsedItem, NSError * _Nullable error))completionHandler API_DEPRECATED("itemChanged:baseVersion:changedFields:contents:completionHandler:", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);

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
 completionHandler:(void (^)(NSFileProviderItem _Nullable taggedItem, NSError * _Nullable error))completionHandler API_DEPRECATED("itemChanged:baseVersion:changedFields:contents:completionHandler:", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);

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
      completionHandler:(void (^)(NSFileProviderItem _Nullable favoriteItem, NSError * _Nullable error))completionHandler API_DEPRECATED("itemChanged:baseVersion:changedFields:contents:completionHandler:", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);
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

/**
 NSFileProviderItemFieldContents corresponds to the item's contents.

 Each subsequent field corresponds to a property on NSFileProviderItem that can
 change.
 */
typedef NS_OPTIONS(NSUInteger, NSFileProviderItemField) {
    NSFileProviderItemFieldContents = 1 << 0,
    NSFileProviderItemFieldFilename = 1 << 1,
    NSFileProviderItemFieldParentItemIdentifier = 1 << 2,
    NSFileProviderItemFieldLastUsedDate = 1 << 3,
    NSFileProviderItemFieldTagData = 1 << 4,
    NSFileProviderItemFieldFavoriteRank = 1 << 5,
    NSFileProviderItemFieldCreationDate = 1 << 6,
    NSFileProviderItemFieldContentModificationDate = 1 << 7,
    NSFileProviderItemFieldFlags = 1 << 8,
    NSFileProviderItemFieldTrashed = 1 << 9,
    NSFileProviderItemFieldExtendedAttributes = 1 << 10
} API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

API_AVAILABLE(ios(8.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos)
@interface NSFileProviderExtension : NSObject

- (nullable NSFileProviderItem)itemForIdentifier:(NSFileProviderItemIdentifier)identifier error:(NSError * _Nullable *)error NS_SWIFT_NAME(item(for:)) API_AVAILABLE(ios(11.0), macos(10.14)) API_UNAVAILABLE(watchos, tvos);

/**
 Download the item for the given identifier and return it via the completion handler.

 The system learns of items through enumerations. Initially, this means that the
 system is aware that an item (with a specific version) exists on the device.

 When the user accesses the item, the system makes a request for the contents of
 the item. The provider can then fulfill the request by providing the item.

 The system takes ownership of the item and will move it out of the sandbox of
 the provider.

 The requestedVersion parameter specifies which version should be returned. A nil value
 means that the latest known version should be returned. Except for the error case, the
 version of the returned item is assumed to be identical to what was requested.
 */
- (NSProgress *)fetchContentsForItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                                           version:(nullable NSFileProviderItemVersion *)requestedVersion
                                 completionHandler:(void(^)(NSURL * _Nullable fileContents, NSFileProviderItem _Nullable item, NSError * _Nullable error))completionHandler  NS_SWIFT_NAME(fetchContents(for:version:completionHandler:)) API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

/**
 Update a previously provided item to a new version.

 If the system already has a version of an item and learns that a new version is
 available, it may call this method to update the existing version to a new
 version.

 The semantics of the requestedVersion parameter are the same as for the non-delta update method above.
 */
- (NSProgress *)fetchContentsForItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                                           version:(nullable NSFileProviderItemVersion *)requestedVersion
                        usingExistingContentsAtURL:(NSURL *)existingContents
                                   existingVersion:(NSFileProviderItemVersion *)existingVersion
                                 completionHandler:(void(^)(NSURL * _Nullable fileContents, NSFileProviderItem _Nullable item, NSError * _Nullable error))completionHandler
NS_SWIFT_NAME(fetchContents(for:version:usingExistingContentsAt:existingVersion:completionHandler:))
API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

/**
 Informs the provider that an item or its metadata have changed. More than one
 property may have changed, e.g.  an item may have been renamed, moved and also
 changed contents, in which case changedFields might contain [.contents,
 .filename, .parentItemIdentifier, .contentModificationDate].

 The provider should merge the changes into the current item state, persist them
 to disk, then call the completion callback with the updated, merged item. At a
 later point, the provider should sync the changes to the server.

 If the completion block is called with an error, the behavior of the system
 depends on the exact error: in an interactive scenario, the error will be
 presented to the user. Otherwise, depending on the error the system will either
 retry at a later time or drop the modifications.
 */
- (void)itemChanged:(NSFileProviderItem)item
        baseVersion:(NSFileProviderItemVersion *)version
      changedFields:(NSFileProviderItemField)changedFields
           contents:(nullable NSURL *)newContents
  completionHandler:(void(^)(NSFileProviderItem _Nullable item, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

@end

/**
 Options passed on item creation.
 */
typedef NS_OPTIONS(NSUInteger, NSFileProviderCreateItemOptions) {
    /**
     The imported item is issued from a disk scan following a state reset.

     The imported item was found on disk after the synchronisation state was
     lost, for example following the restoration of a backup, or the migration
     to a new device.

     The Extension should assess whether the item could actually be a disk
     representation of an already existing item.

     Since this happens only in case we have to reimport all the existing item
     from disk, it is advised that the assessment method avoids computational
     intensive tasks, such as checksumming the item.

     When all the items pending reimport have been processed, the system
     will call -[NSFileProviderExtension importDidFinishWithCompletionHandler:].
     */
    NSFileProviderCreateItemOptionsItemMayAlreadyExist = 1 << 0,
};

@interface NSFileProviderExtension (CreateItem)

/**
 Create a new item.

 This is expected to complete before doing any network.

 The itemTemplate object describes the expected state of the newly created item,
 including its location provided by parentItemIdentifier and filename. The list
 of fields to conside in that object is defined by the fields parameter. Fields
 not listed should be considered as not being defined.

 The itemIdentifier of \the itemTemplate should not be accessed and is actual
 value is not defined. Importing the item should assign a unique itemIdentifier
 to the newly imported item.

 In the completion block, the createdItem is expected to have its properties
 matching the values of the item properties with the exception of the
 itemIdentifier that should be a newly allocated identifier.

 If the item is a document, the contents should be fetched from provided
 URL. Otherwise url will be nil.

 Note that the itemIdentifier on the returned item should be assigned without a
 network call.  It doesn't have to be the final identifier.  If the identifier
 changes after talking to the server then the file provider should send a delete
 for the temporary, local identifier immediately followed by an add with the
 final identifier.

 This is expected to work offline even if there might be a collision (two items
 are at the same location) only detected when later syncing up this change to
 the server.  In that case, it is suggested that a follow up update to the item
 change its filename to something unique.  This wouldn't be considered an error
 to import.

 If the imported item is refused by the extension, it should return nil for the
 createdItem without any error. In that case, the source item will be deleted
 from disk. If the extension does not wish to synchronise the item, while still
 keeping it on disk, it should still import it locally, but not sync it to its
 server, and return a valid createItem object.

 If however you can tell right away, with no communication to your server, that
 there is a collision then this call should fail with error code
 NSFileProviderErrorFilenameCollision generated with this method:
 -[NSError (NSFileProviderError) fileProviderErrorForCollisionWithItem:].

 The existing item set in this error will be used to handle the collision, and
 ask the user if she or he would like to replace the existing item.  This takes
 into account the existing item's capabilities (particularly
 NSFileProviderItemCapabilitiesAllowsTrashing and AllowsDeleting.)

 Upload errors (such as NSFileProviderErrorInsufficientQuota) should be handled
 with a subsequent update to the item, setting its uploadingError property.
 Upload errors should not prevent creating or importing a document, because they
 can be resolved at a later date (for example, when the user has quota again.)

 Other errors will be presented to the user, but are unexpected.  If you want to
 prevent imports in a given directory, then the directory item's capacities
 should exclude NSFileProviderItemCapabilitiesAllowsAddingSubItems.
 */
- (void)createItemBasedOnTemplate:(NSFileProviderItem)itemTemplate
                           fields:(NSFileProviderItemField)fields
                         contents:(nullable NSURL *)url
                          options:(NSFileProviderCreateItemOptions)options
                completionHandler:(void (^)(NSFileProviderItem _Nullable createdItem, NSError * _Nullable error))completionHandler
    NS_SWIFT_NAME(createItem(basedOn:fields:contents:options:completionHandler:))
    API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

@end

/**
 Options passed on item deletion.
 */
typedef NS_OPTIONS(NSUInteger, NSFileProviderDeleteItemOptions) {
    NSFileProviderDeleteItemOptionsRecursive = 1 << 0
} API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

@interface NSFileProviderExtension (DeleteItem)

/**
 Delete an item forever.

 This is called when the user deletes an item that was already in the Trash and
 the item should no longer appear there after this call.  This call should
 remove the item from the working set.

 This call receives an optional baseVersion which represent the version of the
 item we are trying to delete.  The extension may fail with
 NSFileProviderErrorVersionOutOfDate if the item does not match the provided
 baseVersion.

 Unless the NSFileProviderDeleteItemOptionsRecursive options is passed, the
 deletion of a directory should be non-recursive and the call must fail with
 NSFileProviderErrorDirectoryNotEmpty if the directory contains some children.

 Delete is gated by the capabilities of the removed item with
 NSFileProviderItemCapabilitiesAllowsDeleting.
 */
- (void)deleteItemWithIdentifier:(NSFileProviderItemIdentifier)itemIdentifier
                     baseVersion:(NSFileProviderItemVersion *)version
                         options:(NSFileProviderDeleteItemOptions)options
               completionHandler:(void (^)(NSError * _Nullable))completionHandler API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

@end

@interface NSFileProviderExtension (Import)

/** Signal the end of import of on-disk items.

 This is called after an import of on-disk items has been triggered by either
 -[NSFileProviderManager reimportItemsBelowItemWithIdentifier:completionHandler:] or
 +[NSFileProviderManager importDomain:fromDirectoryAtURL:completionHandler:]. A
 reimport can also be started by the system independently from any request by the
 provider.

 During import, found items will be created via the
 -[NSFileProviderExtension createItemBasedOnTemplate:fields:contents:options:completionHandler:]
 call with the NSFileProviderCreateItemOptionsItemMayAlreadyExist flag set.
 At the end of an import the -[NSFileProviderExtension importDidFinishWithCompletionHandler:]
 is called.
 */
- (void)importDidFinishWithCompletionHandler:(void (^)(void))completionHandler
API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

@end

@interface NSFileProviderExtension (Deprecated)

/**
 Writes out a placeholder at the specified URL. The URL should be one returned
 by placeholderURLForURL:; if URL resource values are requested, the system will
 consult the placeholder before consulting your app extension.

 Metadata contains NSURLNameKey, NSURLFileSizeKey, NSURLIsPackageKey.
 */
+ (BOOL)writePlaceholderAtURL:(NSURL *)placeholderURL withMetadata:(NSDictionary <NSURLResourceKey, id> *)metadata error:(NSError **)error API_DEPRECATED("Use the corresponding method on NSFileProviderManager instead", ios(8.0, 11.0)) API_UNAVAILABLE(macos, tvos, watchos);

/**
 Returns the designated placeholder URL for a given URL. This placeholder will
 be consulted before falling back to your app extension to enhance
 performance. To write out a placeholder, use the writePlaceHolderAtURL: method
 above.
 */
+ (NSURL *)placeholderURLForURL:(NSURL *)url API_DEPRECATED_WITH_REPLACEMENT("NSFileProviderManager +placeholderURLForURL:", ios(8.0, 11.0)) API_UNAVAILABLE(macos, tvos, watchos);

/**
 An identifier unique to this provider.

 When modifying the files stored in the directory returned by
 documentStorageURL, you should pass this identifier to your file coordinator's
 setPurposeIdentifier: method.
 */
@property(nonatomic, readonly) NSString *providerIdentifier API_DEPRECATED_WITH_REPLACEMENT("NSFileProviderManager -providerIdentifier", ios(8.0, 11.0)) API_UNAVAILABLE(macos, tvos, watchos);

/**
 The root URL for provided documents. This URL is derived by consulting the
 NSExtensionFileProviderDocumentGroup property on your extension. The document
 storage URL is the folder "File Provider Storage" in the corresponding
 container.
 */
@property(nonatomic, readonly) NSURL *documentStorageURL API_DEPRECATED_WITH_REPLACEMENT("NSFileProviderManager -documentStorageURL", ios(8.0, 11.0)) API_UNAVAILABLE(macos, tvos, watchos);

/**
 Should return the URL corresponding to a specific identifier. Fail if it's not
 a subpath of documentStorageURL.

 This is a static mapping; each identifier must always return a path
 corresponding to the same file. By default, this returns the path relative to
 the path returned by documentStorageURL.
 */
- (nullable NSURL *)URLForItemWithPersistentIdentifier:(NSFileProviderItemIdentifier)identifier API_DEPRECATED("No longer called", ios(8.0, 13.0)) API_UNAVAILABLE(tvos, watchos) API_UNAVAILABLE(macos);
- (nullable NSFileProviderItemIdentifier)persistentIdentifierForItemAtURL:(NSURL *)url API_DEPRECATED("No longer called", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);

/**
 This method is called when a placeholder URL should be provided for the item at
 the given URL.

 The implementation of this method should call +[NSFileProviderManager
 writePlaceholderAtURL:withMetadata:error:] with the URL returned by
 +[NSFileProviderManager placeholderURLForURL:], then call the completion
 handler.
 */
- (void)providePlaceholderAtURL:(NSURL *)url completionHandler:(void (^)(NSError * _Nullable error))completionHandler API_DEPRECATED("No longer called", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);

/**
 Should ensure that the actual file is in the position returned by
 URLForItemWithPersistentIdentifier:, then call the completion handler.
 */
- (void)startProvidingItemAtURL:(NSURL *)url completionHandler:(void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_NAME(startProvidingItem(at:completionHandler:)) API_DEPRECATED("fetchContentsForItemWithIdentifier:version:completionHandler:", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);

/**
 Called after the last claim to the file has been released. At this point, it is
 safe for the file provider to remove the content file.

 Care should be taken that the corresponding placeholder file stays behind after
 the content file has been deleted.
 */
- (void)stopProvidingItemAtURL:(NSURL *)url NS_SWIFT_NAME(stopProvidingItem(at:)) API_DEPRECATED("No longer called", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);

/**
 Called at some point after the file has changed; the provider may then trigger
 an upload.
 */
- (void)itemChangedAtURL:(NSURL *)url API_DEPRECATED("itemChanged:baseVersion:changedFields:contents:completionHandler:", ios(8.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);

@end

NS_ASSUME_NONNULL_END
// ==========  FileProvider.framework/Headers/NSFileProviderItemDecoration.h
//
//  NSFileProviderItemDecoration.h
//  FileProvider
//
//  Created by Johannes Fortmann on 1/16/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderItem.h>

typedef NSString *NSFileProviderItemDecorationIdentifier NS_TYPED_EXTENSIBLE_ENUM;

/**
 Decorations are defined in the extension's Info.plist by adding a
 NSFileProviderDecorations key with one or many entries to the NSExtension dictionary.

    <key>NSFileProviderDecorations</key>
    <array>
    	<dict>
    		<key>Identifier</key>
    		<string>$(PRODUCT_BUNDLE_IDENTIFIER).hasComments</string>
    		<key>BadgeImageType</key>
    		<string>com.someone.item.decoration.unreadCommentIcon</string>
    		<key>Category</key>
    		<string>Badge</string>
    		<key>LocalizedTitle</key>
    		<dict>
    			<key>NSStringFormat</key>
    			<string>%@ unread comments</string>
    			<key>NSStringFormatValues</key>
    			<array>
    				<string>item.userInfo.unreadCommentCount</string>
    			</array>
    		</dict>
    	</dict>
    </array>

 The keys for each entry are defined as follows:
 Key            | Property
 ---------------|----------
 Identifier     | The identifier used to refer to this decoration in the item definition (as type `NSFileProviderItemDecorationIdentifier`).
 BadgeImageType | The overlay UTI (see below)
 Label          | A localizable title, to be used in detail views, on mouse over and for voice over
 Category       | The position of the decoration: one of 'Badge', 'Sharing', 'FolderStatus' or 'FolderBadge'

 At rendering time, the icon for the UTI specified by 'BadgeImageType' will be looked up.
 The UTI must conform to 'com.apple.icon-decoration.badge'.

 Decorations from different categories are presented in different places in the UI:

 Category     | Location
 -------------|----------
 Badge        | On top of the icon; only the first badge is displayed.
 Sharing      | Below the icon. If multiple Sharing decorations are present, the first one that fits will be shown.
 FolderStatus | On open folders, below the folders items. All FolderStatus decorations will be shown, concatenated.
 FolderBadge  | Embossed on top of the folder icon. Only the first badge is displayed. Only valid for folders.


*/

@protocol NSFileProviderItemDecorating <NSFileProviderItem>
/**
 Returns an array of decorations for the item.

 To adopt this protocol, implement the -decorations method on your NSFileProviderItem to return valid decoration identifiers
 from your Info.plist.
 */
 @property (nonatomic, nullable, readonly, strong) NSArray <NSFileProviderItemDecorationIdentifier> *decorations API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);
@end
// ==========  FileProvider.framework/Headers/NSFileProviderMaterializedSet.h
//
//  NSFileProviderMaterializedSet.h
//  FileProvider
//
//  Copyright (c) 2018 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderExtension.h>
#import <FileProvider/NSFileProviderManager.h>

@interface NSFileProviderExtension (MaterializedSet)

/**
 Called by the system if the set of materialized items changes.

 Materialized items are items that have synced to disk and are not
 dataless.  They may contain a mix of dataless and materialized files and
 directories, but in any case, all their children are represented on disk.
 Traversals of dataless directories by applications trigger an enumeration
 against the file provider extension; traversals of materialized directories
 do not.  It is the responsability of the file provider extension to notify
 the system on remote changes of these files: there is no alternative cache
 invalidation mechanism.

 If the extension doesn't keep track of the materialized set, it will have to
 notify the system of all remote changes.  In that case the working set is the
 entire dataset.  The system may drop items whose parent isn't materialized, to
 avoid unnecessary disk usage.  This saves some I/O, but isn't optimal.  The
 filtering by parentItemIdentifier is better done in the extension;  ideally,
 it would even be done server-side.  A hybrid model is possible, where some
 filtering is done server-side, and some finer filtering is done client-side.

 The file provider extension should therefore keep a list of the identifiers of
 the materialized directories.  This method is called when a new directory is
 materialized or when a materialized directory is rendered dataless.

 To enumerate the set of materialized containers,
 - Call -enumeratorForMaterializedItems on the instance of
   NSFileProviderManager corresponding to your domain;
 - Implement the NSFileProviderEnumerationObserver and
   NSFileProviderChangeObserver on an object;
 - Pass that object to the enumerator;
 - Use the identifiers of items or changes you receive to note the
   materialization status in your database.

 When an item is created, modified or deleted remotely, the file provider
 extension should check whether its parentItemIdentifier is in the materialized
 set.  If it is, the extension needs to inform the system so the system may
 create, modify or delete the file or directory (initially dataless) on disk.
 In the case when an item is reparented, the test should be that either the new
 or the old parentItemIdentifier is in the materialized set.  No need to pretend
 that the iten was deleted if the new parentItemIdentifier is no longer in the
 materialized set: the system will know what to do with an unknown parent
 identifier.

 To notify the system of this created, modified or deleted item,
 - Call -signalEnumeratorForContainerItemIdentifier: on the working set, i.e the
   container identified by NSFileProviderWorkingSetContainerItemIdentifier;
 - Include this item in the next enumeration of the working set.
 */
- (void)materializedItemsDidChangeWithCompletionHandler:(void (^)(void))completionHandler API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

@end

@interface NSFileProviderManager (MaterializedSet)

/**
 Returns an enumerator for the set of materialized containers.

 This enumerator is unlike other enumerators because the roles of the system
 and the extension are reversed:
 - The system enumerates the working set after the extension calls
   'signalEnumeratorForContainerItemIdentifier';
 - The extension enumerates the materialized set after the system calls
   'materializedContainersDidChangeWithCompletionHandler'.
 */
- (id<NSFileProviderEnumerator>)enumeratorForMaterializedItems API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

@end

