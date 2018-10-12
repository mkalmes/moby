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
#import <Photos/PhotosDefines.h>

#if TARGET_OS_OSX
typedef CF_ENUM( int16_t, FigEXIFCustomRenderedValue ) {
    kFigEXIFCustomRenderedValue_NotCustom                        = 0,
    kFigEXIFCustomRenderedValue_Custom                            = 1,
    // CustomRendered values above 1 are defined in the Exif spec as "Reserved"
    kFigEXIFCustomRenderedValue_HDRImage                        = 2, // Set on the HDR sbuf metadata when "Keep Normal Photo" is off
    kFigEXIFCustomRenderedValue_HDRPlusEV0_HDRImage                = 3, // Set on the HDR sbuf metadata when "Keep Normal Photo" is on
    kFigEXIFCustomRenderedValue_HDRPlusEV0_EV0Image                = 4, // Set on the EV0 sbuf metadata when "Keep Normal Photo" is on
    // Leaving a hole here, reserved for some future HDR hotness, maybe
    kFigEXIFCustomRenderedValue_PanoramaImage                    = 6,
    kFigEXIFCustomRenderedValue_SDOFImage                        = 7, // Set on the SDOF sbuf metadata when only an SDOF is requested
    kFigEXIFCustomRenderedValue_SDOFPlusOriginal_SDOFImage        = 8, // Set on the SDOF sbuf metadata when both an SDOF and an original are requested
    kFigEXIFCustomRenderedValue_SDOFPlusOriginal_OriginalImage    = 9, // Set on the original sbuf metadata when both an SDOF and an original are requested
};
#endif

#pragma mark - PHCollectionListTypes

typedef NS_ENUM(NSInteger, PHImageContentMode) {
    PHImageContentModeAspectFit = 0,
    PHImageContentModeAspectFill = 1,
    PHImageContentModeDefault = PHImageContentModeAspectFit
} PHOTOS_ENUM_AVAILABLE_IOS_TVOS(8_0, 10_0);

typedef NS_ENUM(NSInteger, PHCollectionListType) {
    PHCollectionListTypeMomentList    = 1,
    PHCollectionListTypeFolder        = 2,
    PHCollectionListTypeSmartFolder   = 3,
} PHOTOS_ENUM_AVAILABLE_IOS_TVOS(8_0, 10_0);

typedef NS_ENUM(NSInteger, PHCollectionListSubtype) {
    
    // PHCollectionListTypeMomentList subtypes
    PHCollectionListSubtypeMomentListCluster    = 1,
    PHCollectionListSubtypeMomentListYear       = 2,
    
    // PHCollectionListTypeFolder subtypes
    PHCollectionListSubtypeRegularFolder        = 100,
    
    // PHCollectionListTypeSmartFolder subtypes
    PHCollectionListSubtypeSmartFolderEvents    = 200,
    PHCollectionListSubtypeSmartFolderFaces     = 201,
    
    // Used for fetching if you don't care about the exact subtype
    PHCollectionListSubtypeAny = NSIntegerMax
} PHOTOS_ENUM_AVAILABLE_IOS_TVOS(8_0, 10_0);

#pragma mark - PHCollection types

typedef NS_ENUM(NSInteger, PHCollectionEditOperation) {
    PHCollectionEditOperationDeleteContent    = 1, // Delete things it contains
    PHCollectionEditOperationRemoveContent    = 2, // Remove things it contains, they're not deleted from the library
    PHCollectionEditOperationAddContent       = 3, // Add things from other collection
    PHCollectionEditOperationCreateContent    = 4, // Create new things, or duplicate them from others in the same container
    PHCollectionEditOperationRearrangeContent = 5, // Change the order of things
    PHCollectionEditOperationDelete           = 6, // Deleting of the container, not the content
    PHCollectionEditOperationRename           = 7, // Renaming of the container, not the content
} PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0);

#pragma mark - PHAssetCollection types

typedef NS_ENUM(NSInteger, PHAssetCollectionType) {
    PHAssetCollectionTypeAlbum      = 1,
    PHAssetCollectionTypeSmartAlbum = 2,
    PHAssetCollectionTypeMoment     = 3,
} PHOTOS_ENUM_AVAILABLE_IOS_TVOS(8_0, 10_0);

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
    PHAssetCollectionSubtypeSmartAlbumSelfPortraits PHOTOS_AVAILABLE_IOS_TVOS(9_0, 10_0) = 210,
    PHAssetCollectionSubtypeSmartAlbumScreenshots PHOTOS_AVAILABLE_IOS_TVOS(9_0, 10_0) = 211,
    PHAssetCollectionSubtypeSmartAlbumDepthEffect PHOTOS_AVAILABLE_IOS_TVOS(10_2, 10_1) = 212,
    PHAssetCollectionSubtypeSmartAlbumLivePhotos PHOTOS_AVAILABLE_IOS_TVOS(10_3, 10_2) = 213,
    PHAssetCollectionSubtypeSmartAlbumAnimated PHOTOS_AVAILABLE_IOS_TVOS(11_0, 11_0) = 214,
    PHAssetCollectionSubtypeSmartAlbumLongExposures PHOTOS_AVAILABLE_IOS_TVOS(11_0, 11_0) = 215,
    // Used for fetching, if you don't care about the exact subtype
    PHAssetCollectionSubtypeAny = NSIntegerMax
} PHOTOS_ENUM_AVAILABLE_IOS_TVOS(8_0, 10_0);

#pragma mark - PHAsset types

typedef NS_ENUM(NSInteger, PHAssetEditOperation) {
    PHAssetEditOperationDelete     = 1,
    PHAssetEditOperationContent    = 2,
    PHAssetEditOperationProperties = 3,
} PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0);

typedef NS_ENUM(NSInteger, PHAssetPlaybackStyle) {
    PHAssetPlaybackStyleUnsupported     = 0,
    PHAssetPlaybackStyleImage           = 1,
    PHAssetPlaybackStyleImageAnimated   = 2,
    PHAssetPlaybackStyleLivePhoto       = 3,
    PHAssetPlaybackStyleVideo           = 4,
    PHAssetPlaybackStyleVideoLooping    = 5,
} PHOTOS_ENUM_AVAILABLE_IOS_TVOS(11_0, 11_0) NS_SWIFT_NAME(PHAsset.PlaybackStyle);

typedef NS_ENUM(NSInteger, PHAssetMediaType) {
    PHAssetMediaTypeUnknown = 0,
    PHAssetMediaTypeImage   = 1,
    PHAssetMediaTypeVideo   = 2,
    PHAssetMediaTypeAudio   = 3,
} PHOTOS_ENUM_AVAILABLE_IOS_TVOS(8_0, 10_0);

typedef NS_OPTIONS(NSUInteger, PHAssetMediaSubtype) {
    PHAssetMediaSubtypeNone               = 0,
    
    // Photo subtypes
    PHAssetMediaSubtypePhotoPanorama      = (1UL << 0),
    PHAssetMediaSubtypePhotoHDR           = (1UL << 1),
    PHAssetMediaSubtypePhotoScreenshot PHOTOS_AVAILABLE_IOS_TVOS(9_0, 10_0) = (1UL << 2),
    PHAssetMediaSubtypePhotoLive PHOTOS_AVAILABLE_IOS_TVOS(9_1, 10_0) = (1UL << 3),
    PHAssetMediaSubtypePhotoDepthEffect PHOTOS_AVAILABLE_IOS_TVOS(10_2, 10_1) = (1UL << 4),

    // Video subtypes
    PHAssetMediaSubtypeVideoStreamed      = (1UL << 16),
    PHAssetMediaSubtypeVideoHighFrameRate = (1UL << 17),
    PHAssetMediaSubtypeVideoTimelapse     = (1UL << 18),
} PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0);

typedef NS_OPTIONS(NSUInteger, PHAssetBurstSelectionType) {
    PHAssetBurstSelectionTypeNone     = 0,
    PHAssetBurstSelectionTypeAutoPick = (1UL << 0),
    PHAssetBurstSelectionTypeUserPick = (1UL << 1),
} PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0);

typedef NS_OPTIONS(NSUInteger, PHAssetSourceType) {
    PHAssetSourceTypeNone            = 0,
    PHAssetSourceTypeUserLibrary     = (1UL << 0),
    PHAssetSourceTypeCloudShared     = (1UL << 1),
    PHAssetSourceTypeiTunesSynced    = (1UL << 2),
} PHOTOS_AVAILABLE_IOS_TVOS(9_0, 10_0);

typedef NS_ENUM(NSInteger, PHAssetResourceType) {
    PHAssetResourceTypePhoto                             = 1,
    PHAssetResourceTypeVideo                             = 2,
    PHAssetResourceTypeAudio                             = 3,
    PHAssetResourceTypeAlternatePhoto                    = 4,
    PHAssetResourceTypeFullSizePhoto                     = 5,
    PHAssetResourceTypeFullSizeVideo                     = 6,
    PHAssetResourceTypeAdjustmentData                    = 7,
    PHAssetResourceTypeAdjustmentBasePhoto               = 8,
    PHAssetResourceTypePairedVideo PHOTOS_AVAILABLE_IOS_TVOS(9_1, 10_0) = 9,
    PHAssetResourceTypeFullSizePairedVideo PHOTOS_AVAILABLE_IOS_TVOS(10_0, 10_0) = 10,
    PHAssetResourceTypeAdjustmentBasePairedVideo PHOTOS_AVAILABLE_IOS_TVOS(10_0, 10_0) = 11,
} PHOTOS_ENUM_AVAILABLE_IOS_TVOS(9_0, 10_0);

#endif
// ==========  Photos.framework/Headers/PHFetchResult.h
//
//  PHFetchResult.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PhotosTypes.h>
#import <Photos/PhotosDefines.h>

NS_ASSUME_NONNULL_BEGIN

// Accessing fetched results (fetches objects from the backing store in chunks on demand rather than all at once)
// Fetched objects will be kept in a cache and purged under memory pressure
PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHFetchResult<ObjectType> : NSObject <NSCopying, NSFastEnumeration>

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

NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHChange.h
//
//  PHChange.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PhotosDefines.h>
#import <Photos/PHFetchResult.h>

@class PHObject;
@class PHObjectChangeDetails;
@class PHFetchResultChangeDetails;

NS_ASSUME_NONNULL_BEGIN

PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHChange : NSObject

- (nullable PHObjectChangeDetails *)changeDetailsForObject:(PHObject *)object;
- (nullable PHFetchResultChangeDetails *)changeDetailsForFetchResult:(PHFetchResult *)object;

@end



PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHObjectChangeDetails<ObjectType: PHObject *> : NSObject

// the object in the state before this change (returns the object that was passed in to changeDetailsForObject:)
@property (atomic, strong, readonly) ObjectType objectBeforeChanges;

// the object in the state after this change
@property (atomic, strong, readonly, nullable) ObjectType objectAfterChanges;

// YES if the image or video content for this object has been changed
@property (atomic, readonly) BOOL assetContentChanged;

// YES if the object was deleted
@property (atomic, readonly) BOOL objectWasDeleted;

@end



PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHFetchResultChangeDetails<ObjectType: PHObject *> : NSObject

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

NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHCollectionListChangeRequest.h
//
//  PHCollectionListChangeRequest.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PhotosDefines.h>
#import <Photos/PHFetchResult.h>

@class PHCollection;
@class PHCollectionList;
@class PHObjectPlaceholder;

NS_ASSUME_NONNULL_BEGIN

// PHCollectionListChangeRequest can only be created or used within a -[PHPhotoLibrary performChanges:] or -[PHPhotoLibrary performChangesAndWait:] block.
PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHCollectionListChangeRequest : NSObject

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

NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHObject.h
//
//  PHObject.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PhotosDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class PHPhotoLibrary;


PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHObject : NSObject <NSCopying>

// Returns an identifier which persistently identifies the object on a given device
@property (nonatomic, copy, readonly) NSString *localIdentifier;

@end

// PHObjectPlaceholder represents a model object future , vended by change requests when creating a model object.  PHObjectPlaceholder is a read-only object and may be used as a proxy for the real object that will be created both inside and outside of the change block.  Will compare isEqual: to the fetched model object after the change block is performed.
PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHObjectPlaceholder : PHObject
@end

NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHAssetResource.h
//
//  PHAssetResource.h
//  Photos
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Photos/PhotosTypes.h>
#import <Photos/PhotosDefines.h>

@class PHAsset;
@class PHLivePhoto;

NS_ASSUME_NONNULL_BEGIN

PHOTOS_CLASS_AVAILABLE_IOS_TVOS(9_0, 10_0) @interface PHAssetResource : NSObject

@property (nonatomic, assign, readonly) PHAssetResourceType type;
@property (nonatomic, copy, readonly) NSString *assetLocalIdentifier;
@property (nonatomic, copy, readonly) NSString *uniformTypeIdentifier;
@property (nonatomic, copy, readonly) NSString *originalFilename;

#pragma mark - Getting resources

+ (NSArray<PHAssetResource *> *)assetResourcesForAsset:(PHAsset *)asset;
+ (NSArray<PHAssetResource *> *)assetResourcesForLivePhoto:(PHLivePhoto *)livePhoto PHOTOS_AVAILABLE_IOS_TVOS(9_1, 10_0);

@end

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
#import <Photos/PHContentEditingOutput.h>
#import <Photos/PhotosDefines.h>

#if TARGET_OS_OSX
@class NSImage;
#else
@class UIImage;
#endif
@class CLLocation;
@class PHAssetResource;
@class PHObjectPlaceholder;
@class PHContentEditingInputRequestOptions;

NS_ASSUME_NONNULL_BEGIN

// PHAssetChangeRequest can only be created or used within a -[PHPhotoLibrary performChanges:] or -[PHPhotoLibrary performChangesAndWait:] block.
PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHAssetChangeRequest : NSObject

#pragma mark - Creating Assets

// Basic asset creation. For finer-grained control, see PHAssetCreationRequest.
#if TARGET_OS_OSX
+ (instancetype)creationRequestForAssetFromImage:(NSImage *)image;
#else
+ (instancetype)creationRequestForAssetFromImage:(UIImage *)image;
#endif
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


typedef NSUInteger PHContentEditingInputRequestID PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0);

PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHContentEditingInputRequestOptions : NSObject

// Block to be provided by the client, used to determine if the given adjustment data can be handled (i.e. can be decoded and rendered).
@property (nonatomic, copy) BOOL (^canHandleAdjustmentData)(PHAdjustmentData *adjustmentData);

// Used if data is not available locally and needs to be retrieved from iCloud.
@property (nonatomic, assign, getter = isNetworkAccessAllowed) BOOL networkAccessAllowed;
@property (nonatomic, copy, nullable) void (^progressHandler)(double progress, BOOL *stop);

@end


@interface PHAsset (PHContentEditingInput)

// Completion and progress handlers are called on an arbitrary serial queue.
- (PHContentEditingInputRequestID)requestContentEditingInputWithOptions:(nullable PHContentEditingInputRequestOptions *)options completionHandler:(void (^)(PHContentEditingInput *__nullable contentEditingInput, NSDictionary *info))completionHandler PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0);
- (void)cancelContentEditingInputRequest:(PHContentEditingInputRequestID)requestID PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0);

@end

// Completion handler info dictionary keys
extern NSString *const PHContentEditingInputResultIsInCloudKey PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0);
extern NSString *const PHContentEditingInputCancelledKey PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0);
extern NSString *const PHContentEditingInputErrorKey PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0);


@interface PHContentEditingOutput (PHAssetChangeRequest)

// Create a PHContentEditingOutput from a newly created asset within the change request block
- (instancetype)initWithPlaceholderForCreatedAsset:(PHObjectPlaceholder *)placeholderForCreatedAsset;

@end

NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHLivePhoto.h
//
//  PHLivePhoto.h
//  PhotoKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Photos/PhotosTypes.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

typedef int32_t PHLivePhotoRequestID PHOTOS_AVAILABLE_IOS_TVOS(9_1, 10_0);
static const PHLivePhotoRequestID PHLivePhotoRequestIDInvalid = 0;

/// These keys may be found in the info dictionary delivered to a live photo request result handler block.
extern NSString * const PHLivePhotoInfoErrorKey PHOTOS_AVAILABLE_IOS_TVOS(9_1, 10_0); // key : NSError decribing an error that has occurred while creating the live photo
extern NSString * const PHLivePhotoInfoIsDegradedKey PHOTOS_AVAILABLE_IOS_TVOS(9_1, 10_0); // key : NSNumber containing a BOOL, YES whenever the deivered live photo object does not contain all content required for full playback.
extern NSString * const PHLivePhotoInfoCancelledKey PHOTOS_AVAILABLE_IOS_TVOS(9_1, 10_0); // key : NSNumber containing a BOOL, YES when the result handler is being called after the request has been cancelled.


PHOTOS_CLASS_AVAILABLE_IOS_TVOS(9_1, 10_0)
@interface PHLivePhoto : NSObject <NSCopying, NSSecureCoding>

/// The dimensions of the live photo measured in pixels.
@property (readonly, nonatomic) CGSize size;

#pragma mark - Export

/// Requests a Live Photo from the given resource URLs. The result handler will be called multiple times to deliver new PHLivePhoto instances with increasingly more content. If a placeholder image is provided, the result handler will first be invoked synchronously to deliver a live photo containing only the placeholder image. Subsequent invocations of the result handler will occur on the main queue.
//  The targetSize and contentMode parameters are used to resize the live photo content if needed. If targetSize is equal to CGRectZero, content will not be resized.
//  When using this method to provide content for a PHLivePhotoView, each live photo instance delivered via the result handler should be passed to -[PHLivePhotoView setLivePhoto:].
+ (PHLivePhotoRequestID)requestLivePhotoWithResourceFileURLs:(NSArray<NSURL *> *)fileURLs placeholderImage:(UIImage *__nullable)image targetSize:(CGSize)targetSize contentMode:(PHImageContentMode)contentMode resultHandler:(void(^)(PHLivePhoto *__nullable livePhoto, NSDictionary *info))resultHandler;

/// Cancels the loading of a PHLivePhoto. The request's completion handler will be called.
+ (void)cancelLivePhotoRequestWithRequestID:(PHLivePhotoRequestID)requestID;

@end


NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHAssetResourceManager.h
//
//  PHAssetResourceManager.h
//  Photos
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Photos/PhotosTypes.h>
#import <Photos/PhotosDefines.h>


// Uniquely identify a resource data request
typedef int32_t PHAssetResourceDataRequestID PHOTOS_AVAILABLE_IOS_TVOS(9_0, 10_0);
static const PHAssetResourceDataRequestID PHInvalidAssetResourceDataRequestID = 0;

// Progress handler, called in an arbitrary serial queue.
typedef void (^PHAssetResourceProgressHandler)(double progress) PHOTOS_AVAILABLE_IOS_TVOS(9_0, 10_0);

@class PHAssetResource;

NS_ASSUME_NONNULL_BEGIN

PHOTOS_CLASS_AVAILABLE_IOS_TVOS(9_0, 10_0) @interface PHAssetResourceRequestOptions : NSObject <NSCopying>

@property (nonatomic, assign, getter=isNetworkAccessAllowed) BOOL networkAccessAllowed;
@property (nonatomic, copy, nullable) PHAssetResourceProgressHandler progressHandler;

@end

PHOTOS_CLASS_AVAILABLE_IOS_TVOS(9_0, 10_0) @interface PHAssetResourceManager : NSObject

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
#import <Photos/PhotosDefines.h>

@class PHObject;

NS_ASSUME_NONNULL_BEGIN

PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHFetchOptions : NSObject <NSCopying>

// Some predicates / sorts may be suboptimal and we will log
@property (nonatomic, strong, nullable) NSPredicate *predicate;
@property (nonatomic, strong, nullable) NSArray<NSSortDescriptor *> *sortDescriptors;

// Whether hidden assets are included in fetch results. Defaults to NO
@property (nonatomic, assign) BOOL includeHiddenAssets;

// Whether hidden burst assets are included in fetch results. Defaults to NO
@property (nonatomic, assign) BOOL includeAllBurstAssets;

// The asset source types included in the fetch results.  Defaults to PHAssetSourceTypeNone.
// If set to PHAssetSourceTypeNone the asset source types included in the fetch results are inferred from the type of query performed (see PHAsset fetchAssetsWithOptions:)
@property (nonatomic, assign) PHAssetSourceType includeAssetSourceTypes PHOTOS_AVAILABLE_IOS_TVOS(9_0, 10_0);

// Limits the maximum number of objects returned in the fetch result, a value of 0 means no limit.  Defaults to 0.
@property (nonatomic, assign, readwrite) NSUInteger fetchLimit PHOTOS_AVAILABLE_IOS_TVOS(9_0, 10_0);

// Whether the owner of this object is interested in incremental change details for the results of this fetch (see PHChange)
// Defaults to YES
@property (nonatomic, assign) BOOL wantsIncrementalChangeDetails;

@end

NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHImageManager.h
//
//  PHImageManager.h
//  Photos
//
//  Copyright (c) 2013-2014 Apple Inc. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <Photos/PhotosTypes.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

@class PHAsset;
@class PHLivePhoto;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - PHImageRequestOptions - Configuration

typedef NS_ENUM(NSInteger, PHImageRequestOptionsVersion) {
    PHImageRequestOptionsVersionCurrent = 0, // version with edits (aka adjustments) rendered or unadjusted version if there is no edits
    PHImageRequestOptionsVersionUnadjusted, // original version without any adjustments
    PHImageRequestOptionsVersionOriginal // original version, in the case of a combined format the highest fidelity format will be returned (e.g. RAW for a RAW+JPG source image)
} PHOTOS_ENUM_AVAILABLE_IOS_TVOS(8_0, 10_0);

typedef NS_ENUM(NSInteger, PHImageRequestOptionsDeliveryMode) {
    PHImageRequestOptionsDeliveryModeOpportunistic = 0, // client may get several image results when the call is asynchronous or will get one result when the call is synchronous
    PHImageRequestOptionsDeliveryModeHighQualityFormat = 1, // client will get one result only and it will be as asked or better than asked (sync requests are automatically processed this way regardless of the specified mode)
    PHImageRequestOptionsDeliveryModeFastFormat = 2 // client will get one result only and it may be degraded
} PHOTOS_ENUM_AVAILABLE_IOS_TVOS(8_0, 10_0);

typedef NS_ENUM(NSInteger, PHImageRequestOptionsResizeMode) {
    PHImageRequestOptionsResizeModeNone = 0, // no resize
    PHImageRequestOptionsResizeModeFast, // use targetSize as a hint for optimal decoding when the source image is a compressed format (i.e. subsampling), the delivered image may be larger than targetSize
    PHImageRequestOptionsResizeModeExact, // same as above but also guarantees the delivered image is exactly targetSize (must be set when a normalizedCropRect is specified)
} PHOTOS_ENUM_AVAILABLE_IOS_TVOS(8_0, 10_0);

// Progress handler, called in an arbitrary serial queue. Only called when the data is not available locally and is retrieved from iCloud.
typedef void (^ PHAssetImageProgressHandler)(double progress, NSError *__nullable error, BOOL *stop, NSDictionary *__nullable info) PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0);

PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHImageRequestOptions : NSObject <NSCopying>

@property (nonatomic, assign) PHImageRequestOptionsVersion version; // version
@property (nonatomic, assign) PHImageRequestOptionsDeliveryMode deliveryMode; // delivery mode. Defaults to PHImageRequestOptionsDeliveryModeOpportunistic
@property (nonatomic, assign) PHImageRequestOptionsResizeMode resizeMode; // resize mode. Does not apply when size is PHImageManagerMaximumSize. Defaults to PHImageRequestOptionsResizeModeNone (or no resize)
@property (nonatomic, assign) CGRect normalizedCropRect; // specify crop rectangle in unit coordinates of the original image, such as a face. Defaults to CGRectZero (not applicable)
@property (nonatomic, assign, getter=isNetworkAccessAllowed) BOOL networkAccessAllowed; // if necessary will download the image from iCloud (client can monitor or cancel using progressHandler). Defaults to NO (see start/stopCachingImagesForAssets)
@property (nonatomic, assign, getter=isSynchronous) BOOL synchronous; // return only a single result, blocking until available (or failure). Defaults to NO
@property (nonatomic, copy, nullable) PHAssetImageProgressHandler progressHandler; // provide caller a way to be told how much progress has been made prior to delivering the data when it comes from iCloud. Defaults to nil, shall be set by caller

@end


PHOTOS_CLASS_AVAILABLE_IOS_TVOS(9_1, 10_0) @interface PHLivePhotoRequestOptions : NSObject <NSCopying>

@property (nonatomic, assign) PHImageRequestOptionsVersion version; // version
@property (nonatomic, assign) PHImageRequestOptionsDeliveryMode deliveryMode;
@property (nonatomic, assign, getter=isNetworkAccessAllowed) BOOL networkAccessAllowed;
@property (nonatomic, copy, nullable) PHAssetImageProgressHandler progressHandler;

@end


#pragma mark - PHVideoRequestOptions - Configuration

typedef NS_ENUM(NSInteger, PHVideoRequestOptionsVersion) {
    PHVideoRequestOptionsVersionCurrent = 0, // version with edits (aka adjustments) rendered or unadjusted version if there is no edits
    PHVideoRequestOptionsVersionOriginal // original version
} PHOTOS_ENUM_AVAILABLE_IOS_TVOS(8_0, 10_0);

typedef NS_ENUM(NSInteger, PHVideoRequestOptionsDeliveryMode) { // only apply with PHVideoRequestOptionsVersionCurrent
    PHVideoRequestOptionsDeliveryModeAutomatic = 0, // let us pick the quality (typ. PHVideoRequestOptionsDeliveryModeMediumQualityFormat for streamed AVPlayerItem or AVAsset, or PHVideoRequestOptionsDeliveryModeHighQualityFormat for AVAssetExportSession)
    PHVideoRequestOptionsDeliveryModeHighQualityFormat = 1, // best quality
    PHVideoRequestOptionsDeliveryModeMediumQualityFormat = 2, // medium quality (typ. 720p), currently only supported for AVPlayerItem or AVAsset when streaming from iCloud (will systematically default to PHVideoRequestOptionsDeliveryModeHighQualityFormat if locally available)
    PHVideoRequestOptionsDeliveryModeFastFormat = 3 // fastest available (typ. 360p MP4), currently only supported for AVPlayerItem or AVAsset when streaming from iCloud (will systematically default to PHVideoRequestOptionsDeliveryModeHighQualityFormat if locally available)
} PHOTOS_ENUM_AVAILABLE_IOS_TVOS(8_0, 10_0);

// Progress handler, called in an arbitrary serial queue: only called when the data is not available locally and is retrieved from iCloud
typedef void (^PHAssetVideoProgressHandler)(double progress, NSError *__nullable error, BOOL *stop, NSDictionary *__nullable info) PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0);

PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHVideoRequestOptions : NSObject

@property (nonatomic, assign, getter=isNetworkAccessAllowed) BOOL networkAccessAllowed;
@property (nonatomic, assign) PHVideoRequestOptionsVersion version;
@property (nonatomic, assign) PHVideoRequestOptionsDeliveryMode deliveryMode;
@property (nonatomic, copy, nullable) PHAssetVideoProgressHandler progressHandler;

@end



#pragma mark - PHImageManager - Fetching

// Uniquely identify a cancellable async request
typedef int32_t PHImageRequestID PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0);
static const PHImageRequestID PHInvalidImageRequestID = 0;

// Size to pass when requesting the original image or the largest rendered image available (resizeMode will be ignored)
extern CGSize const PHImageManagerMaximumSize PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0);

// Result's handler info dictionary keys
extern NSString *const PHImageResultIsInCloudKey PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0); // key (NSNumber): result is in iCloud, meaning a new request will need to get issued (with networkAccessAllowed set) to get the result
extern NSString *const PHImageResultIsDegradedKey PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0); // key (NSNumber): result  is a degraded image (only with async requests), meaning other images will be sent unless the request is cancelled in the meanwhile (note that the other request may fail if, for example, data is not available locally and networkAccessAllowed was not specified)
extern NSString *const PHImageResultRequestIDKey PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0); // key (NSNumber): Request ID of the request for this result
extern NSString *const PHImageCancelledKey PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0); // key (NSNumber): result is not available because the request was cancelled
extern NSString *const PHImageErrorKey PHOTOS_AVAILABLE_IOS_TVOS(8_0, 10_0); // key (NSError): NSFileManager or iCloud Photo Library errors


// Note that all sizes are in pixels
PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHImageManager : NSObject

+ (PHImageManager *)defaultManager;


#pragma mark - Image

// If the asset's aspect ratio does not match that of the given targetSize, contentMode determines how the image will be resized.
//      PHImageContentModeAspectFit: Fit the asked size by maintaining the aspect ratio, the delivered image may not necessarily be the asked targetSize (see PHImageRequestOptionsDeliveryMode and PHImageRequestOptionsResizeMode)
//      PHImageContentModeAspectFill: Fill the asked size, some portion of the content may be clipped, the delivered image may not necessarily be the asked targetSize (see PHImageRequestOptionsDeliveryMode && PHImageRequestOptionsResizeMode)
//      PHImageContentModeDefault: Use PHImageContentModeDefault when size is PHImageManagerMaximumSize (though no scaling/cropping will be done on the result)
// If -[PHImageRequestOptions isSynchronous] returns NO (or options is nil), resultHandler may be called 1 or more times.
//     Typically in this case, resultHandler will be called asynchronously on the main thread with the requested results.
//     However, if deliveryMode = PHImageRequestOptionsDeliveryModeOpportunistic, resultHandler may be called synchronously on the calling thread if any image data is immediately available. If the image data returned in this first pass is of insufficient quality, resultHandler will be called again, asychronously on the main thread at a later time with the "correct" results.
//     If the request is cancelled, resultHandler may not be called at all.
// If -[PHImageRequestOptions isSynchronous] returns YES, resultHandler will be called exactly once, synchronously and on the calling thread. Synchronous requests cannot be cancelled. 
// resultHandler for asynchronous requests, always called on main thread
- (PHImageRequestID)requestImageForAsset:(PHAsset *)asset targetSize:(CGSize)targetSize contentMode:(PHImageContentMode)contentMode options:(nullable PHImageRequestOptions *)options resultHandler:(void (^)(UIImage *__nullable result, NSDictionary *__nullable info))resultHandler;

// Request largest represented image as data bytes, resultHandler is called exactly once (deliveryMode is ignored).
//     If PHImageRequestOptionsVersionCurrent is requested and the asset has adjustments then the largest rendered image data is returned
//     In all other cases then the original image data is returned
// resultHandler for asynchronous requests, always called on main thread
- (PHImageRequestID)requestImageDataForAsset:(PHAsset *)asset options:(nullable PHImageRequestOptions *)options resultHandler:(void(^)(NSData *__nullable imageData, NSString *__nullable dataUTI, UIImageOrientation orientation, NSDictionary *__nullable info))resultHandler;

- (void)cancelImageRequest:(PHImageRequestID)requestID;


#pragma mark - Live Photo

/// Requests a live photo representation of the asset. With PHImageRequestOptionsDeliveryModeOpportunistic (or if no options are specified), the resultHandler block may be called more than once (the first call may occur before the method returns). The PHImageResultIsDegradedKey key in the result handler's info parameter indicates when a temporary low-quality live photo is provided.
- (PHImageRequestID)requestLivePhotoForAsset:(PHAsset *)asset targetSize:(CGSize)targetSize contentMode:(PHImageContentMode)contentMode options:(nullable PHLivePhotoRequestOptions *)options resultHandler:(void (^)(PHLivePhoto *__nullable livePhoto, NSDictionary *__nullable info))resultHandler PHOTOS_AVAILABLE_IOS_TVOS(9_1, 10_0);


#pragma mark - Video

// Playback only. The result handler is called on an arbitrary queue.
- (PHImageRequestID)requestPlayerItemForVideo:(PHAsset *)asset options:(nullable PHVideoRequestOptions *)options resultHandler:(void (^)(AVPlayerItem *__nullable playerItem, NSDictionary *__nullable info))resultHandler;

// Export. The result handler is called on an arbitrary queue.
- (PHImageRequestID)requestExportSessionForVideo:(PHAsset *)asset options:(nullable PHVideoRequestOptions *)options exportPreset:(NSString *)exportPreset resultHandler:(void (^)(AVAssetExportSession *__nullable exportSession, NSDictionary *__nullable info))resultHandler;

// Everything else. The result handler is called on an arbitrary queue.
- (PHImageRequestID)requestAVAssetForVideo:(PHAsset *)asset options:(nullable PHVideoRequestOptions *)options resultHandler:(void (^)(AVAsset *__nullable asset, AVAudioMix *__nullable audioMix, NSDictionary *__nullable info))resultHandler;

@end


#pragma mark - PHCachingImageManager - Preheating

PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHCachingImageManager : PHImageManager

// During fast scrolling clients should set this to improve responsiveness
@property (nonatomic, assign) BOOL allowsCachingHighQualityImages; // Defaults to YES

// Asynchronous image preheating (aka caching), note that only image sources are cached (no crop or exact resize is ever done on them at the time of caching, only at the time of delivery when applicable).
// The options values shall exactly match the options values used in loading methods. If two or more caching requests are done on the same asset using different options or different targetSize the first
// caching request will have precedence (until it is stopped)
- (void)startCachingImagesForAssets:(NSArray<PHAsset *> *)assets targetSize:(CGSize)targetSize contentMode:(PHImageContentMode)contentMode options:(nullable PHImageRequestOptions *)options;
- (void)stopCachingImagesForAssets:(NSArray<PHAsset *> *)assets targetSize:(CGSize)targetSize contentMode:(PHImageContentMode)contentMode options:(nullable PHImageRequestOptions *)options;
- (void)stopCachingImagesForAllAssets;

@end

NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PhotosDefines.h
//
//  PhotosDefines.h
//  PhotoKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Availability.h>

#ifdef __cplusplus
#define PHOTOS_EXTERN            extern "C" __attribute__((visibility ("default")))
#else
#define PHOTOS_EXTERN	        extern __attribute__((visibility ("default")))
#endif

#define PHOTOS_STATIC_INLINE	static inline

#define PHOTOS_AVAILABLE_IOS_ONLY(vers)                 __IOS_AVAILABLE(vers) __WATCHOS_UNAVAILABLE __TVOS_UNAVAILABLE
#define PHOTOS_AVAILABLE_WATCHOS_ONLY(vers)             __IOS_UNAVAILABLE __WATCHOS_AVAILABLE(vers) __TVOS_UNAVAILABLE
#define PHOTOS_AVAILABLE_TVOS_ONLY(vers)                __IOS_UNAVAILABLE __WATCHOS_UNAVAILABLE __TVOS_AVAILABLE(vers)
#define PHOTOS_AVAILABLE_IOS_TVOS(_ios, _tvos)          __IOS_AVAILABLE(_ios) __TVOS_AVAILABLE(_tvos)
#define PHOTOS_AVAILABLE_IOS_TVOS_OSX(_ios, _tvos, _osx)            __IOS_AVAILABLE(_ios) __TVOS_AVAILABLE(_tvos) __OSX_AVAILABLE(_osx)
#define PHOTOS_AVAILABLE_IOS_WATCHOS_TVOS(_ios, _watchos, _tvos)    __IOS_AVAILABLE(_ios) __WATCHOS_AVAILABLE(_watchos) __TVOS_AVAILABLE(_tvos)

#define PHOTOS_CLASS_AVAILABLE_IOS_ONLY(vers)           PHOTOS_EXTERN __IOS_AVAILABLE(vers) __WATCHOS_UNAVAILABLE __TVOS_UNAVAILABLE
#define PHOTOS_CLASS_AVAILABLE_WATCHOS_ONLY(vers)       PHOTOS_EXTERN __IOS_UNAVAILABLE __WATCHOS_AVAILABLE(vers) __TVOS_UNAVAILABLE
#define PHOTOS_CLASS_AVAILABLE_TVOS_ONLY(vers)          PHOTOS_EXTERN __IOS_UNAVAILABLE __WATCHOS_UNAVAILABLE __TVOS_AVAILABLE(vers)
#define PHOTOS_CLASS_AVAILABLE_IOS_TVOS(_ios, _tvos)    PHOTOS_EXTERN __IOS_AVAILABLE(_ios) __TVOS_AVAILABLE(_tvos)
#define PHOTOS_CLASS_AVAILABLE_IOS_TVOS_OSX(_ios, _tvos, _osx)          PHOTOS_EXTERN __IOS_AVAILABLE(_ios) __TVOS_AVAILABLE(_tvos) __OSX_AVAILABLE(_osx)
#define PHOTOS_CLASS_AVAILABLE_IOS_WATCHOS_TVOS(_ios, _watchos, _tvos)  PHOTOS_EXTERN __IOS_AVAILABLE(_ios) __WATCHOS_AVAILABLE(_watchos) __TVOS_AVAILABLE(_tvos)

#define PHOTOS_ENUM_AVAILABLE_IOS_ONLY(vers)            PHOTOS_AVAILABLE_IOS_ONLY(vers)
#define PHOTOS_ENUM_AVAILABLE_WATCHOS_ONLY(vers)        PHOTOS_AVAILABLE_WATCHOS_ONLY(vers)
#define PHOTOS_ENUM_AVAILABLE_TVOS_ONLY(vers)           PHOTOS_AVAILABLE_TVOS_ONLY(vers)
#define PHOTOS_ENUM_AVAILABLE_IOS_TVOS(_ios, _tvos)     PHOTOS_AVAILABLE_IOS_TVOS(_ios, _tvos)
#define PHOTOS_ENUM_AVAILABLE_IOS_TVOS_OSX(_ios, _tvos, _osx)          PHOTOS_AVAILABLE_IOS_TVOS_OSX(_ios, _tvos, _osx)
#define PHOTOS_ENUM_AVAILABLE_IOS_WATCHOS_TVOS(_ios, _watchos, _tvos)  PHOTOS_AVAILABLE_IOS_WATCHOS_TVOS(_ios, _watchos, _tvos)

// ==========  Photos.framework/Headers/PHContentEditingInput.h
//
//  PHContentEditingInput.h
//  Photos
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#if !TARGET_OS_OSX
#import <UIKit/UIImage.h>
#endif
#import <Photos/PhotosTypes.h>
#import <Photos/PhotosDefines.h>

@class PHAdjustmentData;
@class AVAsset, AVAudioMix, AVVideoComposition;
@class CLLocation;
@class PHLivePhoto;

NS_ASSUME_NONNULL_BEGIN

PHOTOS_CLASS_AVAILABLE_IOS_TVOS_OSX(8_0, 10_0, 10_12) @interface PHContentEditingInput : NSObject

@property (readonly, assign) PHAssetMediaType mediaType;
@property (readonly, assign) PHAssetMediaSubtype mediaSubtypes;
@property (readonly, copy, nullable) NSDate *creationDate;
@property (readonly, copy, nullable) CLLocation *location;
@property (readonly, copy, nullable) NSString *uniformTypeIdentifier;

// Playback style describes how the content should be presented to the user.  Use this value to choose the type of view and the appropriate APIs on the content editing input to display this content.
// When editing a live photo with a PHAssetPlaybackStyleLoopingVideo, you should provide an updated video that includes the looping video metadata on the PHContentEditingOutput's renderedContentURL.
@property (nonatomic, assign, readonly) PHAssetPlaybackStyle playbackStyle PHOTOS_AVAILABLE_IOS_TVOS(11_0, 11_0);

// Adjustments to be applied onto the provided input image or video.
@property (readonly, strong, nullable) PHAdjustmentData *adjustmentData;

// Input image:
#if TARGET_OS_OSX
@property (readonly, strong, nullable) NSImage *displaySizeImage;
#else
@property (readonly, strong, nullable) UIImage *displaySizeImage;
#endif
@property (readonly, copy, nullable) NSURL *fullSizeImageURL;
@property (readonly, assign) int fullSizeImageOrientation; // EXIF value

// Input video:
@property (readonly, strong, nullable) AVAsset *avAsset NS_DEPRECATED_IOS(8_0, 9_0);
@property (readonly, strong, nullable) AVAsset *audiovisualAsset PHOTOS_AVAILABLE_IOS_TVOS_OSX(9_0, 10_0, 10_13);

// Input Live Photo:
@property (readonly, strong, nullable) PHLivePhoto *livePhoto PHOTOS_AVAILABLE_IOS_TVOS_OSX(10_0, 10_0, 10_12);

@end

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

@class PHChange;

typedef NS_ENUM(NSInteger, PHAuthorizationStatus) {
    PHAuthorizationStatusNotDetermined = 0, // User has not yet made a choice with regards to this application
    PHAuthorizationStatusRestricted,        // This application is not authorized to access photo data.
                                            // The user cannot change this application’s status, possibly due to active restrictions
                                            //   such as parental controls being in place.
    PHAuthorizationStatusDenied,            // User has explicitly denied this application access to photos data.
    PHAuthorizationStatusAuthorized         // User has authorized this application to access photos data.
} PHOTOS_AVAILABLE_IOS_TVOS_OSX(8_0, 10_0, 10_13);


PHOTOS_CLASS_AVAILABLE_IOS_TVOS_OSX(8_0, 10_0, 10_13) @protocol PHPhotoLibraryChangeObserver <NSObject>
// This callback is invoked on an arbitrary serial queue. If you need this to be handled on a specific queue, you should redispatch appropriately
- (void)photoLibraryDidChange:(PHChange *)changeInstance;

@end

/*!
 @class        PHPhotoLibrary
 @abstract     A PHPhotoLibrary provides access to the metadata and image data for the photos, videos and related content in the user's photo library, including content from the Camera Roll, iCloud Shared, Photo Stream, imported, and synced from iTunes.
 @discussion   ...
 */
PHOTOS_CLASS_AVAILABLE_IOS_TVOS_OSX(8_0, 10_0, 10_13) @interface PHPhotoLibrary : NSObject

+ (PHPhotoLibrary *)sharedPhotoLibrary;

+ (PHAuthorizationStatus)authorizationStatus;
+ (void)requestAuthorization:(void(^)(PHAuthorizationStatus status))handler;

#pragma mark - Applying Changes

// handlers are invoked on an arbitrary serial queue
// Nesting change requests will throw an exception
- (void)performChanges:(dispatch_block_t)changeBlock completionHandler:(nullable void(^)(BOOL success, NSError *__nullable error))completionHandler;
- (BOOL)performChangesAndWait:(dispatch_block_t)changeBlock error:(NSError *__autoreleasing *)error;

#pragma mark - Change Handling

- (void)registerChangeObserver:(id<PHPhotoLibraryChangeObserver>)observer;
- (void)unregisterChangeObserver:(id<PHPhotoLibraryChangeObserver>)observer;

@end

NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHContentEditingOutput.h
//
//  PHContentEditingOutput.h
//  Photos
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PhotosDefines.h>

@class PHContentEditingInput, PHAdjustmentData;

NS_ASSUME_NONNULL_BEGIN

PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHContentEditingOutput : NSObject

- (instancetype)initWithContentEditingInput:(PHContentEditingInput *)contentEditingInput;

@property (readwrite, strong, nullable) PHAdjustmentData *adjustmentData;

// File URL where the rendered output, with adjustments baked-in, needs to be written to.
@property (readonly, copy) NSURL *renderedContentURL;

@end

NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHAdjustmentData.h
//
//  PHAdjustmentData.h
//  Photos
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PhotosDefines.h>

NS_ASSUME_NONNULL_BEGIN

PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHAdjustmentData : NSObject

- (instancetype)initWithFormatIdentifier:(NSString *)formatIdentifier formatVersion:(NSString *)formatVersion data:(NSData *)data;

// Used to identify the format of the data blob (e.g. identifier "com.apple.myapp" and version "1.0")
@property (readonly, copy) NSString *formatIdentifier;
@property (readonly, copy) NSString *formatVersion;

// Binary blob that describes the adjustments applied to the asset.
@property (readonly, strong) NSData *data;

@end

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
#import <Photos/PhotosDefines.h>

#import <ImageIO/ImageIO.h>
#import <CoreLocation/CLLocation.h>


@class PHFetchOptions;
@class PHAssetCollection;
@class PHPerson;

NS_ASSUME_NONNULL_BEGIN

PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHAsset : PHObject

#pragma mark - Properties

// Playback style describes how the asset should be presented to the user (regardless of the backing media for that asset).  Use this value to choose the type of view and the appropriate APIs on the PHImageManager to display this asset
@property (nonatomic, assign, readonly) PHAssetPlaybackStyle playbackStyle PHOTOS_AVAILABLE_IOS_TVOS(11_0, 11_0);

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

@property (nonatomic, strong, readonly, nullable) NSString *burstIdentifier;
@property (nonatomic, assign, readonly) PHAssetBurstSelectionType burstSelectionTypes;
@property (nonatomic, assign, readonly) BOOL representsBurst;

@property (nonatomic, assign, readonly) PHAssetSourceType sourceType PHOTOS_AVAILABLE_IOS_TVOS(9_0, 10_0);

#pragma mark - Capabilities

- (BOOL)canPerformEditOperation:(PHAssetEditOperation)editOperation;

#pragma mark - Fetching assets

+ (PHFetchResult<PHAsset *> *)fetchAssetsInAssetCollection:(PHAssetCollection *)assetCollection options:(nullable PHFetchOptions *)options;
+ (PHFetchResult<PHAsset *> *)fetchAssetsWithLocalIdentifiers:(NSArray<NSString *> *)identifiers options:(nullable PHFetchOptions *)options; // includes hidden assets by default
+ (nullable PHFetchResult<PHAsset *> *)fetchKeyAssetsInAssetCollection:(PHAssetCollection *)assetCollection options:(nullable PHFetchOptions *)options;
+ (PHFetchResult<PHAsset *> *)fetchAssetsWithBurstIdentifier:(NSString *)burstIdentifier options:(nullable PHFetchOptions *)options;

// Fetches PHAssetSourceTypeUserLibrary assets by default (use includeAssetSourceTypes option to override)
+ (PHFetchResult<PHAsset *> *)fetchAssetsWithOptions:(nullable PHFetchOptions *)options;
+ (PHFetchResult<PHAsset *> *)fetchAssetsWithMediaType:(PHAssetMediaType)mediaType options:(nullable PHFetchOptions *)options;

// assetURLs are URLs retrieved from ALAsset's ALAssetPropertyAssetURL
+ (PHFetchResult<PHAsset *> *)fetchAssetsWithALAssetURLs:(NSArray<NSURL *> *)assetURLs options:(nullable PHFetchOptions *)options API_DEPRECATED("Will be removed in a future release", ios(8.0, 11.0), tvos(8.0, 11.0));

@end

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
#import <Photos/PhotosDefines.h>

@class PHAsset, PHCollectionList, PHFetchResult, PHFetchOptions;
@class CLLocation;

NS_ASSUME_NONNULL_BEGIN

PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHCollection : PHObject

@property (nonatomic, assign, readonly) BOOL canContainAssets;
@property (nonatomic, assign, readonly) BOOL canContainCollections;
@property (nonatomic, strong, readonly, nullable) NSString *localizedTitle;

#pragma mark - Capabilities

- (BOOL)canPerformEditOperation:(PHCollectionEditOperation)anOperation;


#pragma mark - Fetching collections

+ (PHFetchResult<PHCollection *> *)fetchCollectionsInCollectionList:(PHCollectionList *)collectionList options:(nullable PHFetchOptions *)options;
+ (PHFetchResult<PHCollection *> *)fetchTopLevelUserCollectionsWithOptions:(nullable PHFetchOptions *)options;

@end


PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHAssetCollection : PHCollection

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


#pragma mark - Fetching moment asset collections

+ (PHFetchResult<PHAssetCollection *> *)fetchMomentsInMomentList:(PHCollectionList *)momentList options:(nullable PHFetchOptions *)options;
+ (PHFetchResult<PHAssetCollection *> *)fetchMomentsWithOptions:(nullable PHFetchOptions *)options;


#pragma mark - Transient asset collections
// These asset collections are only in-memory and are not persisted to disk

+ (PHAssetCollection *)transientAssetCollectionWithAssets:(NSArray<PHAsset *> *)assets title:(nullable NSString *)title;
+ (PHAssetCollection *)transientAssetCollectionWithAssetFetchResult:(PHFetchResult<PHAsset *> *)fetchResult title:(nullable NSString *)title;


@end


PHOTOS_CLASS_AVAILABLE_IOS_TVOS(8_0, 10_0) @interface PHCollectionList : PHCollection

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


#pragma mark - Fetching moment collection lists

+ (PHFetchResult<PHCollectionList *> *)fetchMomentListsWithSubtype:(PHCollectionListSubtype)momentListSubtype containingMoment:(PHAssetCollection *)moment options:(nullable PHFetchOptions *)options;
+ (PHFetchResult<PHCollectionList *> *)fetchMomentListsWithSubtype:(PHCollectionListSubtype)momentListSubtype options:(nullable PHFetchOptions *)options;


#pragma mark - Transient collection lists

// These collection lists are only in-memory and are not persisted to disk
+ (PHCollectionList *)transientCollectionListWithCollections:(NSArray<PHCollection *> *)collections title:(nullable NSString *)title;
+ (PHCollectionList *)transientCollectionListWithCollectionsFetchResult:(PHFetchResult<PHCollection *> *)fetchResult title:(nullable NSString *)title;

@end

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

@protocol PHLivePhotoFrame;
@class PHContentEditingInput;
@class PHContentEditingOutput;

/// A block callback for processing frames of a live photo, including the still image
typedef CIImage * _Nullable (^PHLivePhotoFrameProcessingBlock)(id <PHLivePhotoFrame> _Nonnull frame, NSError * _Nullable * _Nonnull error);

typedef NSString * const PHLivePhotoEditingOption NS_STRING_ENUM;

NS_AVAILABLE(10_12, 10_0)
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
} NS_ENUM_AVAILABLE(10_12, 10_0);

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
extern PHLivePhotoEditingOption PHLivePhotoShouldRenderAtPlaybackTime NS_AVAILABLE(10_12, 11_0);

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
#import <Photos/PhotosDefines.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

PHOTOS_CLASS_AVAILABLE_IOS_TVOS(9_0, 10_0) @interface PHAssetResourceCreationOptions : NSObject <NSCopying>

// The filename for the resource. If not specified, one will be inferred from a fileURL if available, or else generated.
@property (nonatomic, copy, nullable) NSString *originalFilename;

// The uniform type identifier for the resource. If not specified, one will be inferred from the PHAssetResourceType.
@property (nonatomic, copy, nullable) NSString *uniformTypeIdentifier;

// When enabled, the file passed to the creation request will be moved into the photo library without duplicating the file data (the original file is removed if the asset is created successfully), otherwise a copy of the file is created from the original. Defaults to NO.  Attempting to move a file that is open or hardlinked will fail.
@property (nonatomic, assign) BOOL shouldMoveFile;

@end


// PHAssetCreationRequest can only be created or used within a -[PHPhotoLibrary performChanges:] or -[PHPhotoLibrary performChangesAndWait:] block.
PHOTOS_CLASS_AVAILABLE_IOS_TVOS(9_0, 10_0) @interface PHAssetCreationRequest : PHAssetChangeRequest

+ (instancetype)creationRequestForAsset;

// Whether we support a given combination of PHAssetResourceTypes.
// Note: Adding resources to a creation request always succeeds; validation of the request is performed later, and any errors are reported after the performChanges block.
+ (BOOL)supportsAssetResourceTypes:(NSArray<NSNumber *> *)types;

- (void)addResourceWithType:(PHAssetResourceType)type fileURL:(NSURL *)fileURL options:(nullable PHAssetResourceCreationOptions *)options;

- (void)addResourceWithType:(PHAssetResourceType)type data:(NSData *)data options:(nullable PHAssetResourceCreationOptions *)options;

@end

NS_ASSUME_NONNULL_END
// ==========  Photos.framework/Headers/PHAssetCollectionChangeRequest.h
//
//  PHAssetCollectionChangeRequest.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PHFetchResult.h>

@class PHAsset;
@class PHAssetCollection;
@class PHObjectPlaceholder;

NS_ASSUME_NONNULL_BEGIN

// PHAssetCollectionChangeRequest can only be created or used within a -[PHPhotoLibrary performChanges:] or -[PHPhotoLibrary performChangesAndWait:] block.
@interface PHAssetCollectionChangeRequest : NSObject

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

#endif
