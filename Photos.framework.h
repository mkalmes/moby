// ==========  Photos.framework/Headers/PhotosTypes.h
//
//  PhotosTypes.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#ifndef Photos_PhotosTypes_h
#define Photos_PhotosTypes_h

#import <Foundation/Foundation.h>

API_AVAILABLE_BEGIN(macos(10.11), ios(8), tvos(10))

#pragma mark - PHCollectionListTypes

typedef NS_ENUM(NSInteger, PHImageContentMode) {
    PHImageContentModeAspectFit = 0,
    PHImageContentModeAspectFill = 1,
    PHImageContentModeDefault = PHImageContentModeAspectFit
};

typedef NS_ENUM(NSInteger, PHCollectionListType) {

    PHCollectionListTypeMomentList    API_DEPRECATED("Will be removed in a future release", ios(8, 13), tvos(10, 13)) API_UNAVAILABLE(macos) = 1,

    PHCollectionListTypeFolder        = 2,
    PHCollectionListTypeSmartFolder   = 3,
};

typedef NS_ENUM(NSInteger, PHCollectionListSubtype) {
    
    // PHCollectionListTypeMomentList subtypes

    PHCollectionListSubtypeMomentListCluster    API_DEPRECATED("Will be removed in a future release", ios(8, 13), tvos(10, 13)) API_UNAVAILABLE(macos) = 1,
    PHCollectionListSubtypeMomentListYear       API_DEPRECATED("Will be removed in a future release", ios(8, 13), tvos(10, 13)) API_UNAVAILABLE(macos) = 2,

    // PHCollectionListTypeFolder subtypes
    PHCollectionListSubtypeRegularFolder        = 100,
    
    // PHCollectionListTypeSmartFolder subtypes
    PHCollectionListSubtypeSmartFolderEvents    = 200,
    PHCollectionListSubtypeSmartFolderFaces     = 201,
    
    // Used for fetching if you don't care about the exact subtype
    PHCollectionListSubtypeAny = NSIntegerMax
};

#pragma mark - PHCollection types

typedef NS_ENUM(NSInteger, PHCollectionEditOperation) {
    PHCollectionEditOperationDeleteContent    = 1, // Delete things it contains
    PHCollectionEditOperationRemoveContent    = 2, // Remove things it contains, they're not deleted from the library
    PHCollectionEditOperationAddContent       = 3, // Add things from other collection
    PHCollectionEditOperationCreateContent    = 4, // Create new things, or duplicate them from others in the same container
    PHCollectionEditOperationRearrangeContent = 5, // Change the order of things
    PHCollectionEditOperationDelete           = 6, // Deleting of the container, not the content
    PHCollectionEditOperationRename           = 7, // Renaming of the container, not the content
};

#pragma mark - PHAssetCollection types

typedef NS_ENUM(NSInteger, PHAssetCollectionType) {
    PHAssetCollectionTypeAlbum      = 1,
    PHAssetCollectionTypeSmartAlbum = 2,

    PHAssetCollectionTypeMoment     API_DEPRECATED("Will be removed in a future release", ios(8, 13), tvos(10, 13)) API_UNAVAILABLE(macos) = 3,

};

typedef NS_ENUM(NSInteger, PHAssetCollectionSubtype) {
    
    // PHAssetCollectionTypeAlbum regular subtypes
    PHAssetCollectionSubtypeAlbumRegular         = 2,
    PHAssetCollectionSubtypeAlbumSyncedEvent     = 3,
    PHAssetCollectionSubtypeAlbumSyncedFaces     = 4,
    PHAssetCollectionSubtypeAlbumSyncedAlbum     = 5,
    PHAssetCollectionSubtypeAlbumImported        = 6,
    
    // PHAssetCollectionTypeAlbum shared subtypes
    PHAssetCollectionSubtypeAlbumMyPhotoStream   = 100,
    PHAssetCollectionSubtypeAlbumCloudShared     = 101,
    
    // PHAssetCollectionTypeSmartAlbum subtypes
    PHAssetCollectionSubtypeSmartAlbumGeneric    = 200,
    PHAssetCollectionSubtypeSmartAlbumPanoramas  = 201,
    PHAssetCollectionSubtypeSmartAlbumVideos     = 202,
    PHAssetCollectionSubtypeSmartAlbumFavorites  = 203,
    PHAssetCollectionSubtypeSmartAlbumTimelapses = 204,
    PHAssetCollectionSubtypeSmartAlbumAllHidden  = 205,
    PHAssetCollectionSubtypeSmartAlbumRecentlyAdded = 206,
    PHAssetCollectionSubtypeSmartAlbumBursts     = 207,
    PHAssetCollectionSubtypeSmartAlbumSlomoVideos = 208,
    PHAssetCollectionSubtypeSmartAlbumUserLibrary = 209,
    PHAssetCollectionSubtypeSmartAlbumSelfPortraits API_AVAILABLE(ios(9)) = 210,
    PHAssetCollectionSubtypeSmartAlbumScreenshots API_AVAILABLE(ios(9)) = 211,
    PHAssetCollectionSubtypeSmartAlbumDepthEffect API_AVAILABLE(macos(10.13), ios(10.2), tvos(10.1)) = 212,
    PHAssetCollectionSubtypeSmartAlbumLivePhotos API_AVAILABLE(macos(10.13), ios(10.3), tvos(10.2)) = 213,
    PHAssetCollectionSubtypeSmartAlbumAnimated API_AVAILABLE(macos(10.15), ios(11), tvos(11)) = 214,
    PHAssetCollectionSubtypeSmartAlbumLongExposures API_AVAILABLE(macos(10.15), ios(11), tvos(11)) = 215,
    PHAssetCollectionSubtypeSmartAlbumUnableToUpload API_AVAILABLE(macos(10.15), ios(13), tvos(13)) = 216,

    // Used for fetching, if you don't care about the exact subtype
    PHAssetCollectionSubtypeAny = NSIntegerMax
};

#pragma mark - PHAsset types

typedef NS_ENUM(NSInteger, PHAssetEditOperation) {
    PHAssetEditOperationDelete     = 1,
    PHAssetEditOperationContent    = 2,
    PHAssetEditOperationProperties = 3,
};

typedef NS_ENUM(NSInteger, PHAssetPlaybackStyle) {
    PHAssetPlaybackStyleUnsupported     = 0,
    PHAssetPlaybackStyleImage           = 1,
    PHAssetPlaybackStyleImageAnimated   = 2,
    PHAssetPlaybackStyleLivePhoto       = 3,
    PHAssetPlaybackStyleVideo           = 4,
    PHAssetPlaybackStyleVideoLooping    = 5,
} API_AVAILABLE(macos(10.13), ios(11), tvos(11)) NS_SWIFT_NAME(PHAsset.PlaybackStyle);

typedef NS_ENUM(NSInteger, PHAssetMediaType) {
    PHAssetMediaTypeUnknown = 0,
    PHAssetMediaTypeImage   = 1,
    PHAssetMediaTypeVideo   = 2,
    PHAssetMediaTypeAudio   = 3,
};

typedef NS_OPTIONS(NSUInteger, PHAssetMediaSubtype) {
    PHAssetMediaSubtypeNone               = 0,
    
    // Photo subtypes
    PHAssetMediaSubtypePhotoPanorama      = (1UL << 0),
    PHAssetMediaSubtypePhotoHDR           = (1UL << 1),
    PHAssetMediaSubtypePhotoScreenshot API_AVAILABLE(ios(9)) = (1UL << 2),
    PHAssetMediaSubtypePhotoLive API_AVAILABLE(ios(9.1)) = (1UL << 3),
    PHAssetMediaSubtypePhotoDepthEffect API_AVAILABLE(macos(10.12.2), ios(10.2), tvos(10.1)) = (1UL << 4),

    // Video subtypes
    PHAssetMediaSubtypeVideoStreamed      = (1UL << 16),
    PHAssetMediaSubtypeVideoHighFrameRate = (1UL << 17),
    PHAssetMediaSubtypeVideoTimelapse     = (1UL << 18),
};

typedef NS_OPTIONS(NSUInteger, PHAssetBurstSelectionType) {
    PHAssetBurstSelectionTypeNone     = 0,
    PHAssetBurstSelectionTypeAutoPick = (1UL << 0),
    PHAssetBurstSelectionTypeUserPick = (1UL << 1),
};

typedef NS_OPTIONS(NSUInteger, PHAssetSourceType) {
    PHAssetSourceTypeNone            = 0,
    PHAssetSourceTypeUserLibrary     = (1UL << 0),
    PHAssetSourceTypeCloudShared     = (1UL << 1),
    PHAssetSourceTypeiTunesSynced    = (1UL << 2),
} API_AVAILABLE(ios(9));

typedef NS_ENUM(NSInteger, PHAssetResourceType) {
    PHAssetResourceTypePhoto                             = 1,
    PHAssetResourceTypeVideo                             = 2,
    PHAssetResourceTypeAudio                             = 3,
    PHAssetResourceTypeAlternatePhoto                    = 4,
    PHAssetResourceTypeFullSizePhoto                     = 5,
    PHAssetResourceTypeFullSizeVideo                     = 6,
    PHAssetResourceTypeAdjustmentData                    = 7,
    PHAssetResourceTypeAdjustmentBasePhoto               = 8,
    PHAssetResourceTypePairedVideo API_AVAILABLE(ios(9.1)) = 9,
    PHAssetResourceTypeFullSizePairedVideo API_AVAILABLE(macos(10.15), ios(10)) = 10,
    PHAssetResourceTypeAdjustmentBasePairedVideo API_AVAILABLE(macos(10.15), ios(10)) = 11,
} API_AVAILABLE(ios(9));

API_AVAILABLE_END
#endif
// ==========  Photos.framework/Headers/PHError.h
//
//  PHError.h
//  Photos
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

API_AVAILABLE_BEGIN(macos(10.15), ios(13), tvos(13))

OS_EXPORT NSErrorDomain const PHPhotosErrorDomain;

NS_ERROR_ENUM(PHPhotosErrorDomain) {
    PHPhotosErrorInvalid = -1,
    PHPhotosErrorUserCancelled = 3072,
    PHPhotosErrorLibraryVolumeOffline = 3114,
    PHPhotosErrorRelinquishingLibraryBundleToWriter = 3142,
    PHPhotosErrorSwitchingSystemPhotoLibrary = 3143,
};

API_AVAILABLE_END
// ==========  Photos.framework/Headers/PHCloudIdentifier.h
//
//  PHCloudIdentifier.h
//  Photos
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <Photos/PHPhotoLibrary.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13))

API_UNAVAILABLE_BEGIN(ios, tvos, uikitformac)


OS_EXPORT
@interface PHCloudIdentifier : NSObject <NSSecureCoding>

/// If there is a failure to determine the global identifier for a local identifier, the notFoundIdentifier is provided in that array slot.
@property (class, nonatomic, readonly) PHCloudIdentifier *notFoundIdentifier;

@property (nonatomic, readonly) NSString *stringValue; /// For use in serialization

- (instancetype)initWithStringValue:(NSString *)stringValue; /// Deserialization

@end

@interface PHPhotoLibrary (CloudIdentifiers)

/// These two methods can be very expensive so they should be used sparingly for batch lookup of all needed identifiers. Clients should work in terms of local identifiers and call these methods only once after loading from and before saving to persistent storage.
- (NSArray<NSString *> *)localIdentifiersForCloudIdentifiers:(NSArray<PHCloudIdentifier *> *)cloudIdentifiers;
- (NSArray<PHCloudIdentifier *> *)cloudIdentifiersForLocalIdentifiers:(NSArray<NSString *> *)localIdentifiers;

@end

/// If the local object cannot be resolved from a global identifier, PHLocalIdentifierNotFound is provided in that array slot.
extern NSString * const PHLocalIdentifierNotFound;


API_UNAVAILABLE_END

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHFetchResult.h
//
//  PHFetchResult.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PhotosTypes.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13), ios(8), tvos(10))

// Accessing fetched results (fetches objects from the backing store in chunks on demand rather than all at once)
// Fetched objects will be kept in a cache and purged under memory pressure
OS_EXPORT
@interface PHFetchResult<__covariant ObjectType> : NSObject <NSCopying, NSFastEnumeration>

@property (readonly) NSUInteger count;
- (ObjectType)objectAtIndex:(NSUInteger)index;
- (ObjectType)objectAtIndexedSubscript:(NSUInteger)idx;

- (BOOL)containsObject:(ObjectType)anObject;

- (NSUInteger)indexOfObject:(ObjectType)anObject;
- (NSUInteger)indexOfObject:(ObjectType)anObject inRange:(NSRange)range;

@property (nonatomic, readonly, nullable) ObjectType firstObject;
@property (nonatomic, readonly, nullable) ObjectType lastObject;

- (NSArray<ObjectType> *)objectsAtIndexes:(NSIndexSet *)indexes;

- (void)enumerateObjectsUsingBlock:(void (^)(ObjectType obj, NSUInteger idx, BOOL *stop))block;
- (void)enumerateObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(ObjectType obj, NSUInteger idx, BOOL *stop))block;
- (void)enumerateObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts usingBlock:(void (^)(ObjectType obj, NSUInteger idx, BOOL *stop))block;

- (NSUInteger)countOfAssetsWithMediaType:(PHAssetMediaType)mediaType;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHChange.h
//
//  PHChange.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PHFetchResult.h>

@class PHObject;
@class PHObjectChangeDetails;
@class PHFetchResultChangeDetails;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13), ios(8), tvos(10))

OS_EXPORT
@interface PHChange : NSObject

- (nullable PHObjectChangeDetails *)changeDetailsForObject:(PHObject *)object;
- (nullable PHFetchResultChangeDetails *)changeDetailsForFetchResult:(PHFetchResult *)object;

@end


#pragma mark -
OS_EXPORT
@interface PHObjectChangeDetails<ObjectType: PHObject *> : NSObject

// the object in the state before this change (returns the object that was passed in to changeDetailsForObject:)
@property (atomic, strong, readonly) ObjectType objectBeforeChanges;

// the object in the state after this change
@property (atomic, strong, readonly, nullable) ObjectType objectAfterChanges;

// YES if the image or video content for this object has been changed
@property (atomic, readonly) BOOL assetContentChanged;

// YES if the object was deleted
@property (atomic, readonly) BOOL objectWasDeleted;

@end


#pragma mark -
OS_EXPORT
@interface PHFetchResultChangeDetails<ObjectType: PHObject *> : NSObject

// fetch result with the state of the fetched objects before this change (returns the fetch result passed in to changeDetailsForFetchResult:)
@property (atomic, strong, readonly) PHFetchResult<ObjectType> *fetchResultBeforeChanges;

// fetch result with the state of the fetched objects after this change
@property (atomic, strong, readonly) PHFetchResult<ObjectType> *fetchResultAfterChanges;

// YES if the changes to this fetch result are described by the removed/inserted/changed details.
// NO indicates that the scope of changes were too large and UI clients should do a full reload, incremental changes could not be provided
@property (atomic, assign, readonly) BOOL hasIncrementalChanges;

// The indexes of the removed items, relative to the 'before' state of the fetch result
// returns nil if hasIncrementalChanges is NO
@property (atomic, strong, readonly, nullable) NSIndexSet *removedIndexes;
@property (atomic, strong, readonly) NSArray<ObjectType> *removedObjects;

// The indexes of the inserted items, relative to the 'before' state of the fetch result after applying the removedIndexes
// returns nil if hasIncrementalChanges is NO
@property (atomic, strong, readonly, nullable) NSIndexSet *insertedIndexes;
@property (atomic, strong, readonly) NSArray<ObjectType> *insertedObjects;

// The indexes of the updated items, relative to the 'after' state of the fetch result
// returns nil if hasIncrementalChanges is NO
@property (atomic, strong, readonly, nullable) NSIndexSet *changedIndexes;
@property (atomic, strong, readonly) NSArray<ObjectType> *changedObjects;

// Enumerates the indexes of the moved items, relative to the 'before' state of the fetch result after applying the removedIndexes and insertedIndexes
- (void)enumerateMovesWithBlock:(void(^)(NSUInteger fromIndex, NSUInteger toIndex))handler;

// YES if there are moved items
// returns NO if hasIncrementalChanges is NO
@property (atomic, assign, readonly) BOOL hasMoves;

// Provides a "diff" between 2 PHFetchResult objects.
+ (instancetype)changeDetailsFromFetchResult:(PHFetchResult<ObjectType> *)fromResult toFetchResult:(PHFetchResult<ObjectType> *)toResult changedObjects:(NSArray<ObjectType> *)changedObjects;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHCollectionListChangeRequest.h
//
//  PHCollectionListChangeRequest.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PHChangeRequest.h>
#import <Photos/PHFetchResult.h>

@class PHCollection;
@class PHCollectionList;
@class PHObjectPlaceholder;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(8), tvos(10))

// PHCollectionListChangeRequest can only be created or used within a -[PHPhotoLibrary performChanges:] or -[PHPhotoLibrary performChangesAndWait:] block.
OS_EXPORT
@interface PHCollectionListChangeRequest : PHChangeRequest

#pragma mark - Creating Collection Lists

+ (instancetype)creationRequestForCollectionListWithTitle:(NSString *)title;

// This can be used to fetch the newly created collection list after the change block has completed by using -localIdentifier
// It can also be added directly to collection lists within the current change block
@property (nonatomic, strong, readonly) PHObjectPlaceholder *placeholderForCreatedCollectionList;

#pragma mark - Deleting Collection Lists

// requests that the specified collection lists and all their child collections (recursively) be deleted
+ (void)deleteCollectionLists:(id<NSFastEnumeration>)collectionLists;

#pragma mark - Modifying Collection Lists

// if the collection list does not allow the type of change requested, these methods will raise an exception, call canPerformEditOperation: on the collection list to determine if the type of edit operation is allowed.
+ (nullable instancetype)changeRequestForCollectionList:(PHCollectionList *)collectionList;

// to add, remove or rearrange child collections in a collection list, passing in the fetched collections in that collection list will ensure that the child collection positions are tracked correctly in the case that the collection list has been externally edited after the fetch, but before this change is applied
+ (nullable instancetype)changeRequestForCollectionList:(PHCollectionList *)collectionList childCollections:(PHFetchResult<__kindof PHCollection *> *)childCollections;

@property (nonatomic, strong, readwrite) NSString *title;

#pragma mark - Mutating child collections

// A PHCollection can only belong to a single parent PHCollection
- (void)addChildCollections:(id<NSFastEnumeration>)collections;
- (void)insertChildCollections:(id<NSFastEnumeration>)collections atIndexes:(NSIndexSet *)indexes;
- (void)removeChildCollections:(id<NSFastEnumeration>)collections;
- (void)removeChildCollectionsAtIndexes:(NSIndexSet *)indexes;
- (void)replaceChildCollectionsAtIndexes:(NSIndexSet *)indexes withChildCollections:(id<NSFastEnumeration>)collections;

// The move removes the child collections at fromIndexes first then inserts those collections at the toIndex, so toIndex should point to a location based on the updated indexes after having removed the child collections at fromIndexes
- (void)moveChildCollectionsAtIndexes:(NSIndexSet *)indexes toIndex:(NSUInteger)toIndex;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHObject.h
//
//  PHObject.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13), ios(8), tvos(10))

@class PHPhotoLibrary;


OS_EXPORT
@interface PHObject : NSObject <NSCopying>

// Returns an identifier which persistently identifies the object on a given device
@property (nonatomic, copy, readonly) NSString *localIdentifier;

@end

// PHObjectPlaceholder represents a model object future , vended by change requests when creating a model object.  PHObjectPlaceholder is a read-only object and may be used as a proxy for the real object that will be created both inside and outside of the change block.  Will compare isEqual: to the fetched model object after the change block is performed.
OS_EXPORT API_AVAILABLE(macos(10.15))
@interface PHObjectPlaceholder : PHObject
@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHAssetResource.h
//
//  PHAssetResource.h
//  Photos
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Photos/PhotosTypes.h>

@class PHAsset;
@class PHLivePhoto;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(9), tvos(10))

OS_EXPORT
@interface PHAssetResource : NSObject

@property (nonatomic, assign, readonly) PHAssetResourceType type;
@property (nonatomic, copy, readonly) NSString *assetLocalIdentifier;
@property (nonatomic, copy, readonly) NSString *uniformTypeIdentifier;
@property (nonatomic, copy, readonly) NSString *originalFilename;

#pragma mark - Getting resources

+ (NSArray<PHAssetResource *> *)assetResourcesForAsset:(PHAsset *)asset;
+ (NSArray<PHAssetResource *> *)assetResourcesForLivePhoto:(PHLivePhoto *)livePhoto API_AVAILABLE(ios(9.1));

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHAssetChangeRequest.h
//
//  PHAssetChangeRequest.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Photos/PHAsset.h>
#import <Photos/PHChangeRequest.h>
#import <Photos/PHContentEditingOutput.h>

@class UIImage;
@class CLLocation;
@class PHAssetResource;
@class PHObjectPlaceholder;
@class PHContentEditingInputRequestOptions;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(8), tvos(10))

// PHAssetChangeRequest can only be created or used within a -[PHPhotoLibrary performChanges:] or -[PHPhotoLibrary performChangesAndWait:] block.
OS_EXPORT
@interface PHAssetChangeRequest : PHChangeRequest

#pragma mark - Creating Assets

// Basic asset creation. For finer-grained control, see PHAssetCreationRequest.
+ (instancetype)creationRequestForAssetFromImage:(UIImage *)image;
+ (nullable instancetype)creationRequestForAssetFromImageAtFileURL:(NSURL *)fileURL;
+ (nullable instancetype)creationRequestForAssetFromVideoAtFileURL:(NSURL *)fileURL;

// This can be used to fetch the newly created asset after the change block has completed by using -localIdentifier
// It can also be added directly to collections within the current change block
@property (nonatomic, strong, readonly, nullable) PHObjectPlaceholder *placeholderForCreatedAsset;

#pragma mark - Deleting Assets

+ (void)deleteAssets:(id<NSFastEnumeration>)assets;

#pragma mark - Modifying Assets

// if the asset does not allow the type of change requested, these methods will raise an exception, call canPerformEditOperation: on the asset to determine if the type of edit operation is allowed.
+ (instancetype)changeRequestForAsset:(PHAsset *)asset;

@property (nonatomic, strong, readwrite, nullable) NSDate *creationDate;
@property (nonatomic, strong, readwrite, nullable) CLLocation *location;
@property (nonatomic, assign, readwrite, getter=isFavorite) BOOL favorite;

// a hidden asset will be excluded from moment collections, but may still be included in other smart or regular album collections
@property (nonatomic, assign, readwrite, getter=isHidden) BOOL hidden;

#pragma mark - Editing Asset Contents

@property (nonatomic, strong, readwrite, nullable) PHContentEditingOutput *contentEditingOutput;

- (void)revertAssetContentToOriginal;

@end


typedef NSUInteger PHContentEditingInputRequestID;

OS_EXPORT
@interface PHContentEditingInputRequestOptions : NSObject

// Block to be provided by the client, used to determine if the given adjustment data can be handled (i.e. can be decoded and rendered).
@property (nonatomic, copy) BOOL (^canHandleAdjustmentData)(PHAdjustmentData *adjustmentData);

// Used if data is not available locally and needs to be retrieved from iCloud.
@property (nonatomic, assign, getter = isNetworkAccessAllowed) BOOL networkAccessAllowed;
@property (nonatomic, copy, nullable) void (^progressHandler)(double progress, BOOL *stop);

@end


@interface PHAsset (PHContentEditingInput)

// Completion and progress handlers are called on an arbitrary serial queue.
- (PHContentEditingInputRequestID)requestContentEditingInputWithOptions:(nullable PHContentEditingInputRequestOptions *)options completionHandler:(void (^)(PHContentEditingInput *__nullable contentEditingInput, NSDictionary *info))completionHandler;
- (void)cancelContentEditingInputRequest:(PHContentEditingInputRequestID)requestID;

@end

// Completion handler info dictionary keys
extern NSString *const PHContentEditingInputResultIsInCloudKey;
extern NSString *const PHContentEditingInputCancelledKey;
extern NSString *const PHContentEditingInputErrorKey;


@interface PHContentEditingOutput (PHAssetChangeRequest)

// Create a PHContentEditingOutput from a newly created asset within the change request block
- (instancetype)initWithPlaceholderForCreatedAsset:(PHObjectPlaceholder *)placeholderForCreatedAsset;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHLivePhoto.h
//
//  PHLivePhoto.h
//  Photos
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Photos/PhotosTypes.h>
#import <CoreGraphics/CGGeometry.h>
@class UIImage;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(9.1), tvos(10))

typedef int32_t PHLivePhotoRequestID;
static const PHLivePhotoRequestID PHLivePhotoRequestIDInvalid = 0;

/// These keys may be found in the info dictionary delivered to a live photo request result handler block.
extern NSString * const PHLivePhotoInfoErrorKey; // key : NSError decribing an error that has occurred while creating the live photo
extern NSString * const PHLivePhotoInfoIsDegradedKey; // key : NSNumber containing a BOOL, YES whenever the deivered live photo object does not contain all content required for full playback.
extern NSString * const PHLivePhotoInfoCancelledKey; // key : NSNumber containing a BOOL, YES when the result handler is being called after the request has been cancelled.


OS_EXPORT API_AVAILABLE(macos(10.12))
@interface PHLivePhoto : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

/// The dimensions of the live photo measured in pixels.
@property (readonly, nonatomic) CGSize size API_AVAILABLE(macos(10.12));

#pragma mark - Export

/// Requests a Live Photo from the given resource URLs. The result handler will be called multiple times to deliver new PHLivePhoto instances with increasingly more content. If a placeholder image is provided, the result handler will first be invoked synchronously to deliver a live photo containing only the placeholder image. Subsequent invocations of the result handler will occur on the main queue.
//  The targetSize and contentMode parameters are used to resize the live photo content if needed. If targetSize is equal to CGRectZero, content will not be resized.
//  When using this method to provide content for a PHLivePhotoView, each live photo instance delivered via the result handler should be passed to -[PHLivePhotoView setLivePhoto:].
+ (PHLivePhotoRequestID)requestLivePhotoWithResourceFileURLs:(NSArray<NSURL *> *)fileURLs placeholderImage:(nullable UIImage *)image targetSize:(CGSize)targetSize contentMode:(PHImageContentMode)contentMode resultHandler:(void(^)(PHLivePhoto *_Nullable livePhoto, NSDictionary *info))resultHandler;

/// Cancels the loading of a PHLivePhoto. The request's completion handler will be called.
+ (void)cancelLivePhotoRequestWithRequestID:(PHLivePhotoRequestID)requestID;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHAssetResourceManager.h
//
//  PHAssetResourceManager.h
//  Photos
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Photos/PhotosTypes.h>


NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(9), tvos(10))

// Uniquely identify a resource data request
typedef int32_t PHAssetResourceDataRequestID;
static const PHAssetResourceDataRequestID PHInvalidAssetResourceDataRequestID = 0;

// Progress handler, called in an arbitrary serial queue.
typedef void (^PHAssetResourceProgressHandler)(double progress);

@class PHAssetResource;

OS_EXPORT
@interface PHAssetResourceRequestOptions : NSObject <NSCopying>

@property (nonatomic, assign, getter=isNetworkAccessAllowed) BOOL networkAccessAllowed;
@property (nonatomic, copy, nullable) PHAssetResourceProgressHandler progressHandler;

@end


OS_EXPORT
@interface PHAssetResourceManager : NSObject

+ (PHAssetResourceManager *)defaultManager;

// Handlers are called on an arbitrary serial queue. The lifetime of the data is not guaranteed beyond that of the handler.
- (PHAssetResourceDataRequestID)requestDataForAssetResource:(PHAssetResource *)resource
                                                    options:(nullable PHAssetResourceRequestOptions *)options
                                        dataReceivedHandler:(void (^)(NSData *data))handler
                                          completionHandler:(void(^)(NSError *__nullable error))completionHandler;

// Handlers are called on an arbitrary serial queue.
- (void)writeDataForAssetResource:(PHAssetResource *)resource
                           toFile:(NSURL *)fileURL
                          options:(nullable PHAssetResourceRequestOptions *)options
                completionHandler:(void(^)(NSError *__nullable error))completionHandler;

- (void)cancelDataRequest:(PHAssetResourceDataRequestID)requestID;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHFetchOptions.h
//
//  PHFetchOptions.h
//  Photos
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PhotosTypes.h>

@class PHObject;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13), ios(8), tvos(10))

OS_EXPORT
@interface PHFetchOptions : NSObject <NSCopying>

// Some predicates / sorts may be suboptimal and we will log
@property (nonatomic, strong, nullable) NSPredicate *predicate;
@property (nonatomic, strong, nullable) NSArray<NSSortDescriptor *> *sortDescriptors;

// Whether hidden assets are included in fetch results. Defaults to NO
@property (nonatomic, assign) BOOL includeHiddenAssets;

// Whether hidden burst assets are included in fetch results. Defaults to NO
@property (nonatomic, assign) BOOL includeAllBurstAssets API_AVAILABLE(macos(10.15));

// The asset source types included in the fetch results.  Defaults to PHAssetSourceTypeNone.
// If set to PHAssetSourceTypeNone the asset source types included in the fetch results are inferred from the type of query performed (see PHAsset fetchAssetsWithOptions:)
@property (nonatomic, assign) PHAssetSourceType includeAssetSourceTypes API_AVAILABLE(ios(9));

// Limits the maximum number of objects returned in the fetch result, a value of 0 means no limit.  Defaults to 0.
@property (nonatomic, assign, readwrite) NSUInteger fetchLimit API_AVAILABLE(ios(9));

// Whether the owner of this object is interested in incremental change details for the results of this fetch (see PHChange)
// Defaults to YES
@property (nonatomic, assign) BOOL wantsIncrementalChangeDetails;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHImageManager.h
//
//  PHImageManager.h
//  Photos
//
//  Copyright (c) 2013-2014 Apple Inc. All rights reserved.
//

#import <TargetConditionals.h>
#import <AVFoundation/AVFoundation.h>
#import <Photos/PhotosTypes.h>
#import <ImageIO/CGImageProperties.h>

@class UIImage;
@class PHAsset;
@class PHLivePhoto;

#ifdef __cplusplus
typedef NS_ENUM(NSInteger, UIImageOrientation);
#endif

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(ios(8), tvos(10))
API_AVAILABLE_BEGIN(macos(10.13))

#pragma mark - PHImageRequestOptions - Configuration

typedef NS_ENUM(NSInteger, PHImageRequestOptionsVersion) {
    PHImageRequestOptionsVersionCurrent = 0, // version with edits (aka adjustments) rendered or unadjusted version if there is no edits
    PHImageRequestOptionsVersionUnadjusted, // original version without any adjustments
    PHImageRequestOptionsVersionOriginal // original version, in the case of a combined format the highest fidelity format will be returned (e.g. RAW for a RAW+JPG source image)
};

typedef NS_ENUM(NSInteger, PHImageRequestOptionsDeliveryMode) {
    PHImageRequestOptionsDeliveryModeOpportunistic = 0, // client may get several image results when the call is asynchronous or will get one result when the call is synchronous
    PHImageRequestOptionsDeliveryModeHighQualityFormat = 1, // client will get one result only and it will be as asked or better than asked
    PHImageRequestOptionsDeliveryModeFastFormat = 2 // client will get one result only and it may be degraded
};

typedef NS_ENUM(NSInteger, PHImageRequestOptionsResizeMode) {
    PHImageRequestOptionsResizeModeNone = 0, // no resize
    PHImageRequestOptionsResizeModeFast, // use targetSize as a hint for optimal decoding when the source image is a compressed format (i.e. subsampling), the delivered image may be larger than targetSize
    PHImageRequestOptionsResizeModeExact, // same as above but also guarantees the delivered image is exactly targetSize (must be set when a normalizedCropRect is specified)
};

// Progress handler, called in an arbitrary serial queue. Only called when the data is not available locally and is retrieved from iCloud.
typedef void (^PHAssetImageProgressHandler)(double progress, NSError *__nullable error, BOOL *stop, NSDictionary *__nullable info);


#pragma mark -
OS_EXPORT
@interface PHImageRequestOptions : NSObject <NSCopying>

@property (nonatomic, assign) PHImageRequestOptionsVersion version; // version
@property (nonatomic, assign) PHImageRequestOptionsDeliveryMode deliveryMode; // delivery mode. Defaults to PHImageRequestOptionsDeliveryModeOpportunistic
@property (nonatomic, assign) PHImageRequestOptionsResizeMode resizeMode; // resize mode. Does not apply when size is PHImageManagerMaximumSize. Defaults to PHImageRequestOptionsResizeModeFast
@property (nonatomic, assign) CGRect normalizedCropRect; // specify crop rectangle in unit coordinates of the original image, such as a face. Defaults to CGRectZero (not applicable)
@property (nonatomic, assign, getter=isNetworkAccessAllowed) BOOL networkAccessAllowed; // if necessary will download the image from iCloud (client can monitor or cancel using progressHandler). Defaults to NO (see start/stopCachingImagesForAssets)
@property (nonatomic, assign, getter=isSynchronous) BOOL synchronous; // return only a single result, blocking until available (or failure). Defaults to NO
@property (nonatomic, copy, nullable) PHAssetImageProgressHandler progressHandler; // provide caller a way to be told how much progress has been made prior to delivering the data when it comes from iCloud. Defaults to nil, shall be set by caller

@end

API_AVAILABLE_END // macos(10.13)
API_AVAILABLE_BEGIN(macos(10.15))

#pragma mark -
OS_EXPORT
@interface PHLivePhotoRequestOptions : NSObject <NSCopying>

@property (nonatomic, assign) PHImageRequestOptionsVersion version; // version
@property (nonatomic, assign) PHImageRequestOptionsDeliveryMode deliveryMode;
@property (nonatomic, assign, getter=isNetworkAccessAllowed) BOOL networkAccessAllowed;
@property (nonatomic, copy, nullable) PHAssetImageProgressHandler progressHandler;

@end


#pragma mark - PHVideoRequestOptions - Configuration

typedef NS_ENUM(NSInteger, PHVideoRequestOptionsVersion) {
    PHVideoRequestOptionsVersionCurrent = 0, // version with edits (aka adjustments) rendered or unadjusted version if there is no edits
    PHVideoRequestOptionsVersionOriginal // original version
};

typedef NS_ENUM(NSInteger, PHVideoRequestOptionsDeliveryMode) { // only apply with PHVideoRequestOptionsVersionCurrent
    PHVideoRequestOptionsDeliveryModeAutomatic = 0, // let us pick the quality (typ. PHVideoRequestOptionsDeliveryModeMediumQualityFormat for streamed AVPlayerItem or AVAsset, or PHVideoRequestOptionsDeliveryModeHighQualityFormat for AVAssetExportSession)
    PHVideoRequestOptionsDeliveryModeHighQualityFormat = 1, // best quality
    PHVideoRequestOptionsDeliveryModeMediumQualityFormat = 2, // medium quality (typ. 720p), currently only supported for AVPlayerItem or AVAsset when streaming from iCloud (will systematically default to PHVideoRequestOptionsDeliveryModeHighQualityFormat if locally available)
    PHVideoRequestOptionsDeliveryModeFastFormat = 3 // fastest available (typ. 360p MP4), currently only supported for AVPlayerItem or AVAsset when streaming from iCloud (will systematically default to PHVideoRequestOptionsDeliveryModeHighQualityFormat if locally available)
};

// Progress handler, called in an arbitrary serial queue: only called when the data is not available locally and is retrieved from iCloud
typedef void (^PHAssetVideoProgressHandler)(double progress, NSError *__nullable error, BOOL *stop, NSDictionary *__nullable info);

OS_EXPORT
@interface PHVideoRequestOptions : NSObject

@property (nonatomic, assign, getter=isNetworkAccessAllowed) BOOL networkAccessAllowed;
@property (nonatomic, assign) PHVideoRequestOptionsVersion version;
@property (nonatomic, assign) PHVideoRequestOptionsDeliveryMode deliveryMode;
@property (nonatomic, copy, nullable) PHAssetVideoProgressHandler progressHandler;

@end

API_AVAILABLE_END // macos(10.15)
API_AVAILABLE_BEGIN(macos(10.13))

#pragma mark - PHImageManager - Fetching

// Uniquely identify a cancellable async request
typedef int32_t PHImageRequestID;
static const PHImageRequestID PHInvalidImageRequestID = 0;

// Size to pass when requesting the original image or the largest rendered image available (resizeMode will be ignored)
extern CGSize const PHImageManagerMaximumSize;

// Result's handler info dictionary keys
extern NSString *const PHImageResultIsInCloudKey; // key (NSNumber): result is in iCloud, meaning a new request will need to get issued (with networkAccessAllowed set) to get the result
extern NSString *const PHImageResultIsDegradedKey; // key (NSNumber): result  is a degraded image (only with async requests), meaning other images will be sent unless the request is cancelled in the meanwhile (note that the other request may fail if, for example, data is not available locally and networkAccessAllowed was not specified)
extern NSString *const PHImageResultRequestIDKey; // key (NSNumber): Request ID of the request for this result
extern NSString *const PHImageCancelledKey; // key (NSNumber): result is not available because the request was cancelled
extern NSString *const PHImageErrorKey; // key (NSError): NSFileManager or iCloud Photo Library errors


// Note that all sizes are in pixels
OS_EXPORT
@interface PHImageManager : NSObject

+ (PHImageManager *)defaultManager;


#pragma mark - Image

/**
 @abstract Request an image representation for the specified asset.
 @param asset The asset whose image data is to be loaded.
 @param targetSize The target size of image to be returned.
 @param contentMode An option for how to fit the image to the aspect ratio of the requested size.
     If the asset's aspect ratio does not match that of the given targetSize, contentMode determines how the image will be resized.
       PHImageContentModeAspectFit: Fit the asked size by maintaining the aspect ratio, the delivered image may not necessarily be the asked targetSize (see PHImageRequestOptionsDeliveryMode and PHImageRequestOptionsResizeMode)
       PHImageContentModeAspectFill: Fill the asked size, some portion of the content may be clipped, the delivered image may not necessarily be the asked targetSize (see PHImageRequestOptionsDeliveryMode and PHImageRequestOptionsResizeMode)
       PHImageContentModeDefault: Use PHImageContentModeDefault when size is PHImageManagerMaximumSize (though no scaling/cropping will be done on the result)
 @param options Options specifying how Photos should handle the request, format the requested image, and notify your app of progress or errors.
     If -[PHImageRequestOptions isSynchronous] returns NO (or options is nil), resultHandler may be called 1 or more times. Typically in this case, resultHandler will be called asynchronously on the main thread with the requested results. However, if deliveryMode = PHImageRequestOptionsDeliveryModeOpportunistic, resultHandler may be called synchronously on the calling thread if any image data is immediately available. If the image data returned in this first pass is of insufficient quality, resultHandler will be called again, asychronously on the main thread at a later time with the "correct" results. If the request is cancelled, resultHandler may not be called at all.
     If -[PHImageRequestOptions isSynchronous] returns YES, resultHandler will be called exactly once, synchronously and on the calling thread. Synchronous requests cannot be cancelled.
 @param resultHandler A block that is called one or more times either synchronously on the current thread or asynchronously on the main thread depending on the options specified in the PHImageRequestOptions options parameter.
 @return A numeric identifier for the request. If you need to cancel the request before it completes, pass this identifier to the cancelImageRequest: method.
 */
- (PHImageRequestID)requestImageForAsset:(PHAsset *)asset targetSize:(CGSize)targetSize contentMode:(PHImageContentMode)contentMode options:(nullable PHImageRequestOptions *)options resultHandler:(void (^)(UIImage *_Nullable result, NSDictionary *_Nullable info))resultHandler;

/**
 @abstract Request largest represented image as data bytes for the specified asset.
 @param asset The asset whose image data is to be loaded.
 @param options Options specifying how Photos should handle the request, format the requested image, and notify your app of progress or errors.
      If PHImageRequestOptionsVersionCurrent is requested and the asset has adjustments then the largest rendered image data is returned. In all other cases then the original image data is returned.
 @param resultHandler A block that is called exactly once either synchronously on the current thread or asynchronously on the main thread depending on the synchronous option specified in the PHImageRequestOptions options parameter (deliveryMode is ignored).
 */
#ifdef __cplusplus
- (PHImageRequestID)requestImageDataForAsset:(PHAsset *)asset options:(nullable PHImageRequestOptions *)options resultHandler:(void (^)(NSData *_Nullable imageData, NSString *_Nullable dataUTI, UIImageOrientation orientation, NSDictionary *_Nullable info))resultHandler API_DEPRECATED_WITH_REPLACEMENT("-requestImageDataAndOrientationForAsset:options:resultHandler:", ios(8, 13), tvos(8, 13)) API_UNAVAILABLE(macos);
#else
- (PHImageRequestID)requestImageDataForAsset:(PHAsset *)asset options:(nullable PHImageRequestOptions *)options resultHandler:(void (^)(NSData *_Nullable imageData, NSString *_Nullable dataUTI, NSInteger/*UIImageOrientation*/ orientation, NSDictionary *_Nullable info))resultHandler API_DEPRECATED_WITH_REPLACEMENT("-requestImageDataAndOrientationForAsset:options:resultHandler:", ios(8, 13), tvos(8, 13)) API_UNAVAILABLE(macos);
#endif

/**
 @abstract Request largest represented image as data bytes and EXIF orientation for the specified asset.
 @param asset The asset whose image data is to be loaded.
 @param options Options specifying how Photos should handle the request, format the requested image, and notify your app of progress or errors.
 If PHImageRequestOptionsVersionCurrent is requested and the asset has adjustments then the largest rendered image data is returned. In all other cases then the original image data is returned.
 @param resultHandler A block that is called exactly once either synchronously on the current thread or asynchronously on the main thread depending on the synchronous option specified in the PHImageRequestOptions options parameter (deliveryMode is ignored). Orientation is an EXIF orientation as an CGImagePropertyOrientation. For iOS or tvOS, convert this to an UIImageOrientation.
 */ 
- (PHImageRequestID)requestImageDataAndOrientationForAsset:(PHAsset *)asset options:(nullable PHImageRequestOptions *)options resultHandler:(void (^)(NSData *_Nullable imageData, NSString *_Nullable dataUTI, CGImagePropertyOrientation orientation, NSDictionary *_Nullable info))resultHandler API_AVAILABLE(macos(10.15), ios(13), tvos(13));

- (void)cancelImageRequest:(PHImageRequestID)requestID;


#pragma mark - Live Photo

/// Requests a live photo representation of the asset. With PHImageRequestOptionsDeliveryModeOpportunistic (or if no options are specified), the resultHandler block may be called more than once (the first call may occur before the method returns). The PHImageResultIsDegradedKey key in the result handler's info parameter indicates when a temporary low-quality live photo is provided.
- (PHImageRequestID)requestLivePhotoForAsset:(PHAsset *)asset targetSize:(CGSize)targetSize contentMode:(PHImageContentMode)contentMode options:(nullable PHLivePhotoRequestOptions *)options resultHandler:(void (^)(PHLivePhoto *__nullable livePhoto, NSDictionary *__nullable info))resultHandler API_AVAILABLE(macos(10.15), ios(9.1));


#pragma mark - Video

// Playback only. The result handler is called on an arbitrary queue.
- (PHImageRequestID)requestPlayerItemForVideo:(PHAsset *)asset options:(nullable PHVideoRequestOptions *)options resultHandler:(void (^)(AVPlayerItem *__nullable playerItem, NSDictionary *__nullable info))resultHandler API_AVAILABLE(macos(10.15));

// Export. The result handler is called on an arbitrary queue.
- (PHImageRequestID)requestExportSessionForVideo:(PHAsset *)asset options:(nullable PHVideoRequestOptions *)options exportPreset:(NSString *)exportPreset resultHandler:(void (^)(AVAssetExportSession *__nullable exportSession, NSDictionary *__nullable info))resultHandler API_AVAILABLE(macos(10.15));

// Everything else. The result handler is called on an arbitrary queue.
- (PHImageRequestID)requestAVAssetForVideo:(PHAsset *)asset options:(nullable PHVideoRequestOptions *)options resultHandler:(void (^)(AVAsset *__nullable asset, AVAudioMix *__nullable audioMix, NSDictionary *__nullable info))resultHandler API_AVAILABLE(macos(10.15));

@end

API_AVAILABLE_END // macos(10.13)
API_AVAILABLE_BEGIN(macos(10.15))

#pragma mark - PHCachingImageManager - Preheating

OS_EXPORT
@interface PHCachingImageManager : PHImageManager

// During fast scrolling clients should set this to improve responsiveness
@property (nonatomic, assign) BOOL allowsCachingHighQualityImages; // Defaults to YES

// Asynchronous image preheating (aka caching), note that only image sources are cached (no crop or exact resize is ever done on them at the time of caching, only at the time of delivery when applicable).
// The options values shall exactly match the options values used in loading methods. If two or more caching requests are done on the same asset using different options or different targetSize the first
// caching request will have precedence (until it is stopped)
- (void)startCachingImagesForAssets:(NSArray<PHAsset *> *)assets targetSize:(CGSize)targetSize contentMode:(PHImageContentMode)contentMode options:(nullable PHImageRequestOptions *)options;
- (void)stopCachingImagesForAssets:(NSArray<PHAsset *> *)assets targetSize:(CGSize)targetSize contentMode:(PHImageContentMode)contentMode options:(nullable PHImageRequestOptions *)options;
- (void)stopCachingImagesForAllAssets;

@end

API_AVAILABLE_END // macos(10.15)
API_AVAILABLE_END // ios(8), tvos(10)
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHChangeRequest.h
//
//  PHChangeRequest.h
//  PhotoKit
//
//  Copyright (c) 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

OS_EXPORT API_AVAILABLE(macos(10.15), ios(13), tvos(13))
@interface PHChangeRequest : NSObject
@end
// ==========  Photos.framework/Headers/PHContentEditingInput.h
//
//  PHContentEditingInput.h
//  Photos
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PhotosTypes.h>

@class PHAdjustmentData;
@class AVAsset;
@class CLLocation;
@class PHLivePhoto;
@class UIImage;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.11), ios(8), tvos(10))

OS_EXPORT
@interface PHContentEditingInput : NSObject

@property (readonly, assign) PHAssetMediaType mediaType;
@property (readonly, assign) PHAssetMediaSubtype mediaSubtypes;
@property (readonly, copy, nullable) NSDate *creationDate;
@property (readonly, copy, nullable) CLLocation *location;
@property (readonly, copy, nullable) NSString *uniformTypeIdentifier;

// Playback style describes how the content should be presented to the user.  Use this value to choose the type of view and the appropriate APIs on the content editing input to display this content.
// When editing a live photo with a PHAssetPlaybackStyleLoopingVideo, you should provide an updated video that includes the looping video metadata on the PHContentEditingOutput's renderedContentURL.
@property (nonatomic, assign, readonly) PHAssetPlaybackStyle playbackStyle API_AVAILABLE(macos(10.13), ios(11), tvos(11));

// Adjustments to be applied onto the provided input image or video.
@property (readonly, strong, nullable) PHAdjustmentData *adjustmentData;

// Input image:
@property (readonly, strong, nullable) UIImage *displaySizeImage;
@property (readonly, copy, nullable) NSURL *fullSizeImageURL;
@property (readonly, assign) int fullSizeImageOrientation; // EXIF value

// Input video:
@property (readonly, strong, nullable) AVAsset *avAsset API_DEPRECATED_WITH_REPLACEMENT("-audiovisualAsset", ios(8,9)) API_UNAVAILABLE(macos);
@property (readonly, strong, nullable) AVAsset *audiovisualAsset API_AVAILABLE(macos(10.11), ios(9));

// Input Live Photo:
@property (readonly, strong, nullable) PHLivePhoto *livePhoto API_AVAILABLE(macos(10.12), ios(10));

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHProject.h
//
//  PHProject.h
//  Photos
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Photos/PHObject.h>
#import <Photos/PHCollection.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13))

API_UNAVAILABLE_BEGIN(ios, tvos, uikitformac)


OS_EXPORT
@interface PHProject : PHAssetCollection

@property (nonatomic, readonly) NSData *projectExtensionData;

/**
 Property to determine if a project preview was previously set.
 Use -[PHProjectChangeRequest setProjectPreviewImage:] to set a project preview.
 */
@property (nonatomic, readonly) BOOL hasProjectPreview;

@end


API_UNAVAILABLE_END

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHPhotoLibrary.h
//
//  PHPhotoLibrary.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PhotosTypes.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13), ios(8), tvos(10))

@class PHChange;
@class PHPhotoLibrary;

typedef NS_ENUM(NSInteger, PHAuthorizationStatus) {
    PHAuthorizationStatusNotDetermined = 0, // User has not yet made a choice with regards to this application
    PHAuthorizationStatusRestricted,        // This application is not authorized to access photo data.
                                            // The user cannot change this application’s status, possibly due to active restrictions
                                            //   such as parental controls being in place.
    PHAuthorizationStatusDenied,            // User has explicitly denied this application access to photos data.
    PHAuthorizationStatusAuthorized         // User has authorized this application to access photos data.
};

#pragma mark -
@protocol PHPhotoLibraryChangeObserver <NSObject>
// This callback is invoked on an arbitrary serial queue. If you need this to be handled on a specific queue, you should redispatch appropriately
- (void)photoLibraryDidChange:(PHChange *)changeInstance;

@end

#pragma mark -
API_AVAILABLE(macos(10.15), ios(13), tvos(13))
@protocol PHPhotoLibraryAvailabilityObserver <NSObject>
// This notification is posted on a private queue.
- (void)photoLibraryDidBecomeUnavailable:(PHPhotoLibrary *)photoLibrary API_AVAILABLE(macos(10.15), ios(13), tvos(13));
@end

/*!
 @class        PHPhotoLibrary
 @abstract     A PHPhotoLibrary provides access to the metadata and image data for the photos, videos and related content in the user's photo library, including content from the Camera Roll, iCloud Shared, Photo Stream, imported, and synced from iTunes.
 @discussion   ...
 */
#pragma mark -
OS_EXPORT
@interface PHPhotoLibrary : NSObject

+ (PHPhotoLibrary *)sharedPhotoLibrary;

+ (PHAuthorizationStatus)authorizationStatus;
+ (void)requestAuthorization:(void(^)(PHAuthorizationStatus status))handler;

#pragma mark - Library availability

@property (readonly, atomic, nullable, strong) NSError *unavailabilityReason API_AVAILABLE(macos(10.15), ios(13), tvos(13));

- (void)registerAvailabilityObserver:(id<PHPhotoLibraryAvailabilityObserver>)observer API_AVAILABLE(macos(10.15), ios(13), tvos(13));
- (void)unregisterAvailabilityObserver:(id<PHPhotoLibraryAvailabilityObserver>)observer API_AVAILABLE(macos(10.15), ios(13), tvos(13));

#pragma mark - Applying Changes

// handlers are invoked on an arbitrary serial queue
// Nesting change requests will throw an exception
- (void)performChanges:(dispatch_block_t)changeBlock completionHandler:(nullable void(^)(BOOL success, NSError *__nullable error))completionHandler;
- (BOOL)performChangesAndWait:(dispatch_block_t)changeBlock error:(NSError *__autoreleasing *)error;

#pragma mark - Change Handling

- (void)registerChangeObserver:(id<PHPhotoLibraryChangeObserver>)observer;
- (void)unregisterChangeObserver:(id<PHPhotoLibraryChangeObserver>)observer;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHContentEditingOutput.h
//
//  PHContentEditingOutput.h
//  Photos
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PHContentEditingInput, PHAdjustmentData;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.11), ios(8), tvos(10))

OS_EXPORT
@interface PHContentEditingOutput : NSObject

- (instancetype)initWithContentEditingInput:(PHContentEditingInput *)contentEditingInput;

@property (readwrite, strong, nullable) PHAdjustmentData *adjustmentData;

// File URL where the rendered output, with adjustments baked-in, needs to be written to.
@property (readonly, copy) NSURL *renderedContentURL;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHAdjustmentData.h
//
//  PHAdjustmentData.h
//  Photos
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.11), ios(8), tvos(10))

OS_EXPORT
@interface PHAdjustmentData : NSObject

- (instancetype)initWithFormatIdentifier:(NSString *)formatIdentifier formatVersion:(NSString *)formatVersion data:(NSData *)data;

// Used to identify the format of the data blob (e.g. identifier "com.apple.myapp" and version "1.0")
@property (readonly, copy) NSString *formatIdentifier;
@property (readonly, copy) NSString *formatVersion;

// Binary blob that describes the adjustments applied to the asset.
@property (readonly, strong) NSData *data;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHAsset.h
//
//  PHAsset.h
//  Photos
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Photos/PHObject.h>
#import <Photos/PhotosTypes.h>
#import <Photos/PHFetchResult.h>
#import <Photos/PHPhotoLibrary.h>

#import <ImageIO/ImageIO.h>
#import <CoreLocation/CLLocation.h>


@class PHFetchOptions;
@class PHAssetCollection;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13), ios(8), tvos(10))

OS_EXPORT
@interface PHAsset : PHObject

#pragma mark - Properties

// Playback style describes how the asset should be presented to the user (regardless of the backing media for that asset).  Use this value to choose the type of view and the appropriate APIs on the PHImageManager to display this asset
@property (nonatomic, assign, readonly) PHAssetPlaybackStyle playbackStyle API_AVAILABLE(macos(10.15), ios(11), tvos(11));

@property (nonatomic, assign, readonly) PHAssetMediaType mediaType;
@property (nonatomic, assign, readonly) PHAssetMediaSubtype mediaSubtypes;

@property (nonatomic, assign, readonly) NSUInteger pixelWidth;
@property (nonatomic, assign, readonly) NSUInteger pixelHeight;

@property (nonatomic, strong, readonly, nullable) NSDate *creationDate;
@property (nonatomic, strong, readonly, nullable) NSDate *modificationDate;

@property (nonatomic, strong, readonly, nullable) CLLocation *location;

@property (nonatomic, assign, readonly) NSTimeInterval duration;

// a hidden asset will be excluded from moment collections, but may still be included in other smart or regular album collections
@property (nonatomic, assign, readonly, getter=isHidden) BOOL hidden;

@property (nonatomic, assign, readonly, getter=isFavorite) BOOL favorite;

@property (nonatomic, strong, readonly, nullable) NSString *burstIdentifier API_AVAILABLE(macos(10.15));
@property (nonatomic, assign, readonly) PHAssetBurstSelectionType burstSelectionTypes API_AVAILABLE(macos(10.15));
@property (nonatomic, assign, readonly) BOOL representsBurst API_AVAILABLE(macos(10.15));

@property (nonatomic, assign, readonly) PHAssetSourceType sourceType API_AVAILABLE(ios(9));

#pragma mark - Capabilities

- (BOOL)canPerformEditOperation:(PHAssetEditOperation)editOperation API_AVAILABLE(macos(10.15));

#pragma mark - Fetching assets

+ (PHFetchResult<PHAsset *> *)fetchAssetsInAssetCollection:(PHAssetCollection *)assetCollection options:(nullable PHFetchOptions *)options;
+ (PHFetchResult<PHAsset *> *)fetchAssetsWithLocalIdentifiers:(NSArray<NSString *> *)identifiers options:(nullable PHFetchOptions *)options; // includes hidden assets by default
+ (nullable PHFetchResult<PHAsset *> *)fetchKeyAssetsInAssetCollection:(PHAssetCollection *)assetCollection options:(nullable PHFetchOptions *)options;
+ (PHFetchResult<PHAsset *> *)fetchAssetsWithBurstIdentifier:(NSString *)burstIdentifier options:(nullable PHFetchOptions *)options API_AVAILABLE(macos(10.15));

// Fetches PHAssetSourceTypeUserLibrary assets by default (use includeAssetSourceTypes option to override)
+ (PHFetchResult<PHAsset *> *)fetchAssetsWithOptions:(nullable PHFetchOptions *)options API_AVAILABLE(macos(10.15));
+ (PHFetchResult<PHAsset *> *)fetchAssetsWithMediaType:(PHAssetMediaType)mediaType options:(nullable PHFetchOptions *)options API_AVAILABLE(macos(10.15));

// assetURLs are URLs retrieved from ALAsset's ALAssetPropertyAssetURL
+ (PHFetchResult<PHAsset *> *)fetchAssetsWithALAssetURLs:(NSArray<NSURL *> *)assetURLs options:(nullable PHFetchOptions *)options API_DEPRECATED("Will be removed in a future release", ios(8, 11), tvos(8, 11)) API_UNAVAILABLE(uikitformac, macos);

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHCollection.h
//
//  PHCollection.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Photos/PHObject.h>
#import <Photos/PHFetchResult.h>
#import <Photos/PhotosTypes.h>

@class PHAsset, PHCollectionList, PHFetchResult, PHFetchOptions;
@class CLLocation;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(8), tvos(10))

OS_EXPORT API_AVAILABLE(macos(10.13))
@interface PHCollection : PHObject

@property (nonatomic, assign, readonly) BOOL canContainAssets;
@property (nonatomic, assign, readonly) BOOL canContainCollections;
@property (nonatomic, strong, readonly, nullable) NSString *localizedTitle API_AVAILABLE(macos(10.13));

#pragma mark - Capabilities

- (BOOL)canPerformEditOperation:(PHCollectionEditOperation)anOperation;


#pragma mark - Fetching collections

+ (PHFetchResult<PHCollection *> *)fetchCollectionsInCollectionList:(PHCollectionList *)collectionList options:(nullable PHFetchOptions *)options;
+ (PHFetchResult<PHCollection *> *)fetchTopLevelUserCollectionsWithOptions:(nullable PHFetchOptions *)options;

@end


#pragma mark -
OS_EXPORT API_AVAILABLE(macos(10.13))
@interface PHAssetCollection : PHCollection

@property (nonatomic, assign, readonly) PHAssetCollectionType assetCollectionType;
@property (nonatomic, assign, readonly) PHAssetCollectionSubtype assetCollectionSubtype;

// These counts are just estimates; the actual count of objects returned from a fetch should be used if you care about accuracy. Returns NSNotFound if a count cannot be quickly returned.
@property (nonatomic, assign, readonly) NSUInteger estimatedAssetCount;

@property (nonatomic, strong, readonly, nullable) NSDate *startDate;
@property (nonatomic, strong, readonly, nullable) NSDate *endDate;

@property (nonatomic, strong, readonly, nullable) CLLocation *approximateLocation;
@property (nonatomic, strong, readonly) NSArray<NSString *> *localizedLocationNames;


#pragma mark - Fetching asset collections

// Fetch asset collections of a single type matching the provided local identifiers (type is inferred from the local identifiers)
+ (PHFetchResult<PHAssetCollection *> *)fetchAssetCollectionsWithLocalIdentifiers:(NSArray<NSString *> *)identifiers options:(nullable PHFetchOptions *)options;

// Fetch asset collections of a single type and subtype provided (use PHAssetCollectionSubtypeAny to match all subtypes)
+ (PHFetchResult<PHAssetCollection *> *)fetchAssetCollectionsWithType:(PHAssetCollectionType)type subtype:(PHAssetCollectionSubtype)subtype options:(nullable PHFetchOptions *)options;

// Smart Albums are not supported, only Albums and Moments
+ (PHFetchResult<PHAssetCollection *> *)fetchAssetCollectionsContainingAsset:(PHAsset *)asset withType:(PHAssetCollectionType)type options:(nullable PHFetchOptions *)options;

// assetGroupURLs are URLs retrieved from ALAssetGroup's ALAssetsGroupPropertyURL
+ (PHFetchResult<PHAssetCollection *> *)fetchAssetCollectionsWithALAssetGroupURLs:(NSArray<NSURL *> *)assetGroupURLs options:(nullable PHFetchOptions *)options;


#pragma mark - Fetching moment asset collections (Deprecated)


+ (PHFetchResult<PHAssetCollection *> *)fetchMomentsInMomentList:(PHCollectionList *)momentList options:(nullable PHFetchOptions *)options API_DEPRECATED("Will be removed in a future release", ios(8, 13), tvos(10, 13)) API_UNAVAILABLE(macos);
+ (PHFetchResult<PHAssetCollection *> *)fetchMomentsWithOptions:(nullable PHFetchOptions *)options API_DEPRECATED("Will be removed in a future release", ios(8, 13), tvos(10, 13)) API_UNAVAILABLE(macos);



#pragma mark - Transient asset collections
// These asset collections are only in-memory and are not persisted to disk

+ (PHAssetCollection *)transientAssetCollectionWithAssets:(NSArray<PHAsset *> *)assets title:(nullable NSString *)title;
+ (PHAssetCollection *)transientAssetCollectionWithAssetFetchResult:(PHFetchResult<PHAsset *> *)fetchResult title:(nullable NSString *)title;


@end


#pragma mark -
OS_EXPORT API_AVAILABLE(macos(10.13))
@interface PHCollectionList : PHCollection

@property (nonatomic, assign, readonly) PHCollectionListType collectionListType;
@property (nonatomic, assign, readonly) PHCollectionListSubtype collectionListSubtype;

@property (nonatomic, strong, readonly, nullable) NSDate *startDate;
@property (nonatomic, strong, readonly, nullable) NSDate *endDate;

@property (nonatomic, strong, readonly) NSArray<NSString *> *localizedLocationNames;


#pragma mark - Fetching collection lists

// A PHAssetCollectionTypeMoment will be contained by a PHCollectionListSubtypeMomentListCluster and a PHCollectionListSubtypeMomentListYear
// Non-moment PHAssetCollections will only be contained by a single collection list
+ (PHFetchResult<PHCollectionList *> *)fetchCollectionListsContainingCollection:(PHCollection *)collection options:(nullable PHFetchOptions *)options;

// Fetch collection lists of a single type matching the provided local identifiers (type is inferred from the local identifiers)
+ (PHFetchResult<PHCollectionList *> *)fetchCollectionListsWithLocalIdentifiers:(NSArray<NSString *> *)identifiers options:(nullable PHFetchOptions *)options;

// Fetch asset collections of a single type and subtype provided (use PHCollectionListSubtypeAny to match all subtypes)
+ (PHFetchResult<PHCollectionList *> *)fetchCollectionListsWithType:(PHCollectionListType)collectionListType subtype:(PHCollectionListSubtype)subtype options:(nullable PHFetchOptions *)options;


#pragma mark - Fetching moment collection lists (Deprecated)


+ (PHFetchResult<PHCollectionList *> *)fetchMomentListsWithSubtype:(PHCollectionListSubtype)momentListSubtype containingMoment:(PHAssetCollection *)moment options:(nullable PHFetchOptions *)options API_DEPRECATED("Will be removed in a future release", ios(8, 13), tvos(10, 13)) API_UNAVAILABLE(macos);
+ (PHFetchResult<PHCollectionList *> *)fetchMomentListsWithSubtype:(PHCollectionListSubtype)momentListSubtype options:(nullable PHFetchOptions *)options API_DEPRECATED("Will be removed in a future release", ios(8, 13), tvos(10, 13)) API_UNAVAILABLE(macos);



#pragma mark - Transient collection lists

// These collection lists are only in-memory and are not persisted to disk
+ (PHCollectionList *)transientCollectionListWithCollections:(NSArray<PHCollection *> *)collections title:(nullable NSString *)title;
+ (PHCollectionList *)transientCollectionListWithCollectionsFetchResult:(PHFetchResult<PHCollection *> *)fetchResult title:(nullable NSString *)title;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHLivePhotoEditingContext.h
//
//  PHLivePhotoEditingContext.h
//  Photos
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Photos/PHLivePhoto.h>
#import <CoreImage/CIImage.h>
#import <CoreMedia/CMTime.h>
#import <ImageIO/CGImageProperties.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.12), ios(10), tvos(10))

@protocol PHLivePhotoFrame;
@class PHContentEditingInput;
@class PHContentEditingOutput;

/// A block callback for processing frames of a live photo, including the still image
typedef CIImage * _Nullable (^PHLivePhotoFrameProcessingBlock)(id <PHLivePhotoFrame> _Nonnull frame, NSError * _Nullable * _Nonnull error);

typedef NSString * const PHLivePhotoEditingOption NS_STRING_ENUM;

OS_EXPORT
@interface PHLivePhotoEditingContext : NSObject

/// Initializer from the specified live photo input
/// Return nil if the specified input is not for a live photo
- (nullable instancetype)initWithLivePhotoEditingInput:(PHContentEditingInput *)livePhotoInput NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

// ------------------------------------------------------------------------
// Read-only properties
// ------------------------------------------------------------------------

/// The original full-size image from the input live photo
@property (readonly) CIImage *fullSizeImage;

/// The duration of the live photo
@property (readonly) CMTime duration;

/// The time of the still image within the live photo
@property (readonly) CMTime photoTime;

// ------------------------------------------------------------------------
// Editable properties
// ------------------------------------------------------------------------

/// A block that can be set to process each frame of the live photo
/// Note that the context uses a copy of the processor block during processing
@property (nullable, copy) PHLivePhotoFrameProcessingBlock frameProcessor;

/// Specify the audio volume of the edited live photo
/// Must be between 0.0 and 1.0
/// Default to 1.0
@property float audioVolume;

// The orientation of the live photo
@property (readonly) CGImagePropertyOrientation orientation;

// ------------------------------------------------------------------------
// Processing
// ------------------------------------------------------------------------

/// Asynchronously generate a new live photo suitable for playback in a PHLivePhotoView of the specified target size
/// The options dictionary can contain additional options, see below
- (void)prepareLivePhotoForPlaybackWithTargetSize:(CGSize)targetSize options:(nullable NSDictionary<PHLivePhotoEditingOption, id> *)options completionHandler:(void(^)(PHLivePhoto * _Nullable livePhoto, NSError * _Nullable error))handler;

/// Asynchronously process and save the edited live photo to the specified content editing output
/// Options dictionary should be nil, reserved for future expansion
- (void)saveLivePhotoToOutput:(PHContentEditingOutput *)output options:(nullable NSDictionary<PHLivePhotoEditingOption, id> *)options completionHandler:(void(^)(BOOL success, NSError * _Nullable error))handler;

/// Cancel the current asynchronous operation
/// This is implicitly called whenever prepare or save is called
/// A canceled operation will call its completion handler with an appropriate error code
- (void)cancel;

@end

/// The type of frame in the Live Photo
typedef NS_ENUM(NSInteger, PHLivePhotoFrameType) {
    /// Indicates the still image
    PHLivePhotoFrameTypePhoto,
    
    /// Indicates a video frame
    PHLivePhotoFrameTypeVideo,
};

/// Protocol that describes a single frame of a live photo
@protocol PHLivePhotoFrame

/// Input image for the frame
@property (readonly) CIImage *image;

/// The time of the frame relative to the beginning of the live photo
@property (readonly) CMTime time;

/// The type of frame
@property (nonatomic, readonly) PHLivePhotoFrameType type;

/// The scale of the frame relative to the full-size image
@property (readonly) CGFloat renderScale;

@end

// ------------------------------------------------------------------------
// Options that can be set during processing
// ------------------------------------------------------------------------

/// Indicates whether processing should happen at playback time
/// If set to NO (the default) the live photo will always be rendered before playback
/// If set to YES, the editing context might still choose to render first for performance reasons
/// This option is ignored by the saveLivePhotoToOutput method
extern PHLivePhotoEditingOption PHLivePhotoShouldRenderAtPlaybackTime API_AVAILABLE(ios(11), tvos(11));

// ------------------------------------------------------------------------
// Errors
// ------------------------------------------------------------------------

/// The error domain for all Live Photo Editing errors (Deprecated).
extern NSString * const PHLivePhotoEditingErrorDomain API_DEPRECATED_WITH_REPLACEMENT("PHPhotosErrorDomain", macos(10.12, 10.15)) API_UNAVAILABLE(ios, tvos, uikitformac);

/// Error code for Live Photo Editing errors (Deprecated)
typedef NS_ENUM(NSInteger, PHLivePhotoEditingErrorCode) {
    PHLivePhotoEditingErrorCodeUnknown API_DEPRECATED_WITH_REPLACEMENT("PHPhotosErrorInvalid", macos(10.12, 10.15)),
    PHLivePhotoEditingErrorCodeAborted API_DEPRECATED_WITH_REPLACEMENT("PHPhotosErrorUserCancelled", macos(10.12, 10.15)),
} API_UNAVAILABLE(ios, tvos, uikitformac);

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHAssetCreationRequest.h
//
//  PHAssetCreationRequest.h
//  PhotoKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Photos/PhotosTypes.h>
#import <Photos/PHAssetChangeRequest.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(9), tvos(10))

OS_EXPORT
@interface PHAssetResourceCreationOptions : NSObject <NSCopying>

// The filename for the resource. If not specified, one will be inferred from a fileURL if available, or else generated.
@property (nonatomic, copy, nullable) NSString *originalFilename;

// The uniform type identifier for the resource. If not specified, one will be inferred from the PHAssetResourceType.
@property (nonatomic, copy, nullable) NSString *uniformTypeIdentifier;

// When enabled, the file passed to the creation request will be moved into the photo library without duplicating the file data (the original file is removed if the asset is created successfully), otherwise a copy of the file is created from the original. Defaults to NO.  Attempting to move a file that is open or hardlinked will fail.
@property (nonatomic, assign) BOOL shouldMoveFile;

@end


// PHAssetCreationRequest can only be created or used within a -[PHPhotoLibrary performChanges:] or -[PHPhotoLibrary performChangesAndWait:] block.
OS_EXPORT
@interface PHAssetCreationRequest : PHAssetChangeRequest

+ (instancetype)creationRequestForAsset;

// Whether we support a given combination of PHAssetResourceTypes.
// Note: Adding resources to a creation request always succeeds; validation of the request is performed later, and any errors are reported after the performChanges block.
+ (BOOL)supportsAssetResourceTypes:(NSArray<NSNumber *> *)types;

- (void)addResourceWithType:(PHAssetResourceType)type fileURL:(NSURL *)fileURL options:(nullable PHAssetResourceCreationOptions *)options;

- (void)addResourceWithType:(PHAssetResourceType)type data:(NSData *)data options:(nullable PHAssetResourceCreationOptions *)options;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHProjectChangeRequest.h
//
//  PHProjectChangeRequest.h
//  Photos
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PHChangeRequest.h>

@class UIImage;
@class PHAsset;
@class PHProject;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13))

API_UNAVAILABLE_BEGIN(ios, tvos, uikitformac)


OS_EXPORT
@interface PHProjectChangeRequest : PHChangeRequest

- (instancetype)initWithProject:(PHProject *)project;

@property (nonatomic, copy, readwrite) NSString *title;

/**
 The projectExtensionData property is intended for storage of compressed, project specific data
 only. Do not include things like rasterized images that can be locally cached in this data. The
 total size of stored data is limited to 1 MB. Attempting to store more data than allowed will result
 in an error.
 */
@property (nonatomic, copy, readwrite) NSData *projectExtensionData;

/**
 Sets the key asset representing the project.
 Deprecated in macOS 10.14, please use -[PHProjectChangeRequest setProjectPreviewImage:] to provide a rendered preview instead.
 */
- (void)setKeyAsset:(nullable PHAsset *)keyAsset API_DEPRECATED_WITH_REPLACEMENT("-setProjectPreviewImage:", macos(10.13, 10.14)) API_UNAVAILABLE(ios, uikitformac, tvos);

/**
 Use this method to update the project preview visible in Photos.
 Extensions are expected to set a project preview:
 - In or after -[id<PHProjectExtensionController> beginProjectWithExtensionContext:projectInfo:].
 - In or after -[id<PHProjectExtensionController> resumeProjectWithExtensionContext:projectInfo:]
 if -[PHProject hasProjectPreview] returns NO.
 - Whenever the project changes in a way that a new preview is needed.
 @param previewImage A rendered project preview, expected dimensions are 1024x1024.
 */
- (void)setProjectPreviewImage:(UIImage *)previewImage;

/**
 Removes the specified assets from the project.
 @param assets A collection of PHAsset objects to be removed from the project.
 */
- (void)removeAssets:(id<NSFastEnumeration>)assets API_AVAILABLE(macos(10.14)) NS_REFINED_FOR_SWIFT;

@end


API_UNAVAILABLE_END

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHAssetCollectionChangeRequest.h
//
//  PHAssetCollectionChangeRequest.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PHChangeRequest.h>
#import <Photos/PHFetchResult.h>

@class PHAsset;
@class PHAssetCollection;
@class PHObjectPlaceholder;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(8), tvos(10))

// PHAssetCollectionChangeRequest can only be created or used within a -[PHPhotoLibrary performChanges:] or -[PHPhotoLibrary performChangesAndWait:] block.
OS_EXPORT
@interface PHAssetCollectionChangeRequest : PHChangeRequest

#pragma mark - Creating Asset Collections

+ (instancetype)creationRequestForAssetCollectionWithTitle:(NSString *)title;

// This can be used to fetch the newly created asset collection after the change block has completed by using -localIdentifier
// It can also be added directly to collection lists within the current change block
@property (nonatomic, strong, readonly) PHObjectPlaceholder *placeholderForCreatedAssetCollection;

#pragma mark - Deleting Asset Collections

// requests that the specified asset collections be deleted
+ (void)deleteAssetCollections:(id<NSFastEnumeration>)assetCollections;

#pragma mark - Modifying Asset Collections

// if the asset collection does not allow the type of change requested, these methods will raise an exception, call canPerformEditOperation: on the asset collection to determine if the type of edit operation is allowed.
+ (nullable instancetype)changeRequestForAssetCollection:(PHAssetCollection *)assetCollection;

// to add, remove or rearrange assets in a collection, passing in the fetched assets in that collection will ensure that the asset positions are tracked correctly in the case that the collection has been externally edited after the fetch, but before this change is applied
+ (nullable instancetype)changeRequestForAssetCollection:(PHAssetCollection *)assetCollection assets:(PHFetchResult<PHAsset *> *)assets;

@property (nonatomic, strong, readwrite) NSString *title;

- (void)addAssets:(id<NSFastEnumeration>)assets;
- (void)insertAssets:(id<NSFastEnumeration>)assets atIndexes:(NSIndexSet *)indexes;
- (void)removeAssets:(id<NSFastEnumeration>)assets;
- (void)removeAssetsAtIndexes:(NSIndexSet *)indexes;
- (void)replaceAssetsAtIndexes:(NSIndexSet *)indexes withAssets:(id<NSFastEnumeration>)assets;

// The move removes the assets at fromIndexes first then inserts those assets at the toIndex, so toIndex should point to a location based on the updated indexes after having removed the assets at fromIndexes
- (void)moveAssetsAtIndexes:(NSIndexSet *)fromIndexes toIndex:(NSUInteger)toIndex;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/Photos.h
//
//  Photos.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#ifndef Photos_Photos_h
#define Photos_Photos_h

#import <Photos/PHPhotoLibrary.h>
#import <Photos/PhotosTypes.h>
#import <Photos/PHError.h>

#import <Photos/PHObject.h>
#import <Photos/PHAsset.h>
#import <Photos/PHLivePhoto.h>
#import <Photos/PHCollection.h>

#import <Photos/PHFetchOptions.h>
#import <Photos/PHFetchResult.h>

#import <Photos/PHChange.h>

#import <Photos/PHAssetChangeRequest.h>
#import <Photos/PHAssetCreationRequest.h>
#import <Photos/PHAssetCollectionChangeRequest.h>
#import <Photos/PHCollectionListChangeRequest.h>
#import <Photos/PHLivePhotoEditingContext.h>

#import <Photos/PHImageManager.h>

#import <Photos/PHAssetResourceManager.h>
#import <Photos/PHAssetResource.h>

#import <Photos/PHAdjustmentData.h>
#import <Photos/PHContentEditingInput.h>
#import <Photos/PHContentEditingOutput.h>

#import <Photos/PHProject.h>
#import <Photos/PHProjectChangeRequest.h>
#import <Photos/PHCloudIdentifier.h>

#endif
