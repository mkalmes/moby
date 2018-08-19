// ==========  AssetsLibrary.framework/Headers/ALAssetRepresentation.h
//
//  ALAssetRepresentation.h
//  AssetsLibrary
//
//  Copyright 2010 Apple Inc. All rights reserved.
//
/*
 *
 * An ALAssetRepresentation encapsulates one of the representations of a given ALAsset.
 * For example: in the case of a camera shooting RAW + JPEG, the resulting asset will have two representations,
 *              one for the RAW file and one for the JPEG file.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <AssetsLibrary/AssetsLibrary.h>

#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED

NS_CLASS_DEPRECATED_IOS(4_0, 9_0, "Use PHImageRequestOptions with the PHImageManager from the Photos framework instead")
@interface ALAssetRepresentation : NSObject {
@package
    id _internal;
}

// Returns the representation's UTI.
- (NSString *)UTI NS_DEPRECATED_IOS(4_0, 9_0, "Use requestImageDataForAsset:options:resultHandler: on PHImageManager for a PHAsset to request image data from the Photos framework and check the dataUTI passed to your result handler instead");

// Returns the dimensions of this representation.  If the representation does not have valid dimensions, this method will return CGSizeZero.
- (CGSize)dimensions NS_DEPRECATED_IOS(4_0, 9_0, "Use requestImageForAsset:targetSize:contentMode:options:resultHandler: on PHImageManager to request a targetSize of image for a PHAsset from the Photos framework instead");

// Returns the size of the file for this representation. Callers can use this to allocate buffers of the right size for -getBytes:fromOffset:length:error:
- (long long)size NS_DEPRECATED_IOS(4_0, 9_0, "Use requestImageDataForAsset:options:resultHandler: on PHImageManager to request image data for a PHAsset from the Photos framework instead");

// Copies the specified range of bytes into the buffer given by the caller.
// The method returns the number of bytes actually written to the buffer. The number of bytes read will be 
// less than the requested range if the range exceeds the file's size.
// If an error occurs, the method returns 0 and upon return contains an NSError object that describes the problem. Pass NULL if you do not want error information.
- (NSUInteger)getBytes:(uint8_t *)buffer fromOffset:(long long)offset length:(NSUInteger)length error:(NSError **)error NS_DEPRECATED_IOS(4_0, 9_0, "Use requestImageDataForAsset:options:resultHandler: on PHImageManager to request image data for a PHAsset from the Photos framework instead");

// This is a convenience method for -[ALAssetRepresentation CGImageWithOptions:] where options is nil.
- (CGImageRef)fullResolutionImage NS_DEPRECATED_IOS(4_0, 9_0, "Use requestImageForAsset:targetSize:contentMode:options:resultHandler: on PHImageManager to request a targetSize PHImageManagerMaximumSize for a PHAsset from the Photos framework instead");

// This is a convenience method that returns a full resolution CGImage of the representation. It takes a dictionary
// of options as described for CGImageSourceCreateWithData() or CGImageSourceCreateWithURL()
- (CGImageRef)CGImageWithOptions:(NSDictionary *)options NS_DEPRECATED_IOS(4_0, 9_0, "Use requestImageForAsset:targetSize:contentMode:options:resultHandler: on PHImageManager to request a targetSize of image for a PHAsset from the Photos framework instead");

// Returns a CGImage of the representation that is appropriate for displaying full screen.
// The dimensions of this image will be dependent on the hardware that the application is running on and does not mean it will match the dimensions of the screen.
- (CGImageRef)fullScreenImage NS_DEPRECATED_IOS(4_0, 9_0, "Use requestImageForAsset:targetSize:contentMode:options:resultHandler: on PHImageManager to request a targetSize of image for a PHAsset from the Photos framework instead");

// Returns a persistent URL uniquely identifying the representation
- (NSURL *)url NS_DEPRECATED_IOS(4_0, 9_0, "Use PHImageRequestOptions with the PHImageManager instead");

// Returns a dictionary of dictionaries of metadata for the representation.
// If the representation is one that the system cannot interpret, nil is returned.
- (NSDictionary *)metadata NS_DEPRECATED_IOS(4_0, 9_0, "Use CGImageSourceCopyPropertiesAtIndex() to retrieve metadata from an image returned by the PHImageManager from the Photos framework instead");

// Returns the representation's orientation as defined in ALAssetOrientation.
- (ALAssetOrientation)orientation NS_DEPRECATED_IOS(4_0, 9_0, "Use the orientation of the UIImage returned for a PHAsset from the PHImageManager from the Photos framework instead");

// Returns the representation's scale.
- (float)scale NS_DEPRECATED_IOS(4_0, 9_0, "Use requestImageForAsset:targetSize:contentMode:options:resultHandler: on PHImageManager to request a targetSize of image for a PHAsset from the Photos framework instead");

// Returns a string representing the filename of the representation on disk.  
// For representations synced from iTunes, this will be the filename of the represenation on the host.
- (NSString *)filename NS_DEPRECATED_IOS(5_0, 9_0, "Use the Photos framework instead");

@end

#endif
// ==========  AssetsLibrary.framework/Headers/ALAssetsGroup.h
//
//  ALAssetsGroup.h
//  AssetsLibrary
//
//  Copyright 2010 Apple Inc. All rights reserved.
//
/*
 *
 * An ALAssetsGroup is a ordered set of assets. The order of its elements is the order that the user sees in the Photos application. 
 * Groups are synced via iTunes, created on the device, created to hold the users saved photos, or created during camera import. 
 * Synced groups cannot be directly modified using this API. Only user-created groups and the saved photos group can have assets added.
 */

#import <Foundation/Foundation.h>

#import <CoreGraphics/CoreGraphics.h>

#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED

@class ALAsset;
@class ALAssetsGroup;
@class ALAssetsFilter;

// This block is executed when a result is found. The result argument passed into the block is an ALAsset that
// matches the filter set by the caller.
// The index argument indicates which asset is being returned. In the case where no asset is found, index will be set to NSNotFound and stop to YES.
// When the enumeration is done, the block will be called with result set to nil and index set to NSNotFound.
// Setting the output argument stop to YES will finish the enumeration.
typedef void (^ALAssetsGroupEnumerationResultsBlock)(ALAsset *result, NSUInteger index, BOOL *stop) NS_DEPRECATED_IOS(4_0, 9_0, "Use the PHFetchResult returned by fetchAssetsInAssetCollection:options: on PHAsset from the Photos framework to enumerate the assets in an asset collection instead");

// Groups Properties
extern NSString *const ALAssetsGroupPropertyName NS_DEPRECATED_IOS(4_0, 9_0, "Use the localizedTitle property on a PHAssetCollection from the Photos framework instead");              // An NSString with the name of the group
extern NSString *const ALAssetsGroupPropertyType NS_DEPRECATED_IOS(4_0, 9_0, "Use the assetCollectionType and assetCollectionSubtype properties on a PHAssetCollection from the Photos framework instead");              // An ALAssetsGroupType wrapped in an NSNumber
extern NSString *const ALAssetsGroupPropertyPersistentID NS_DEPRECATED_IOS(4_0, 9_0, "Use the localIdentifier property on a PHAssetCollection from the Photos framework instead");      // An NSString with the group's persistent ID. 
extern NSString *const ALAssetsGroupPropertyURL NS_DEPRECATED_IOS(5_0, 9_0, "Use the localIdentifier property on a PHAssetCollection from the Photos framework, or to lookup PHAssetCollections by a previously known ALAssetsGroupPropertyURL use fetchAssetCollectionsWithALAssetGroupURLs:options: instead");              // An NSURL that uniquely identifies the group



NS_CLASS_DEPRECATED_IOS(4_0, 9_0, "Use PHAssetCollection from the Photos framework instead")
@interface ALAssetsGroup : NSObject {
@package
    id _internal;
}

// Use this method to get information about the group.
- (id)valueForProperty:(NSString *)property NS_DEPRECATED_IOS(4_0, 9_0, "Use the class properties on a PHAssetCollection in the Photos framework instead");

// Returns a CGImage of the poster photo for the group.  The thumbnail will be in the correct orientation.
- (CGImageRef)posterImage NS_DEPRECATED_IOS(4_0, 9_0, "Use fetchKeyAssetsInAssetCollection:options: on PHAsset, then use the PHImageManager to request image data for key assets in the asset collection from the Photos framework instead");

// Set the ALAssetsFilter on the group to filter the group contents. This does not execute the filter. 
// For that, -enumerateAssetsUsingBlock:doneBlock: or -numberOfAssets needs to be called. 
// If no filter is set, the enumeration will return all the assets in the group.
// Only one filter is active at a time. Calling this method again resets the filter and does not affect any enumeration that may be in flight.
- (void)setAssetsFilter:(ALAssetsFilter *)filter NS_DEPRECATED_IOS(4_0, 9_0, "Use fetchAssetsInAssetCollection:options: on PHAsset with a predicate in the PHFetchOptions from the Photos framework to filter the assets in an asset collection instead");

// Get the number of assets in the group that match the filter.
// If no filter is set, it returns the count of all assets in the group.
- (NSInteger)numberOfAssets NS_DEPRECATED_IOS(4_0, 9_0, "Use the estimatedAssetCount on PHAssetCollection for a quick estimate of the total assets in a collection (or fetch the assets to get an exact value) from the Photos framework instead");

// These methods are used to retrieve the assets that match the filter.  
// The caller can specify which results are returned using an NSIndexSet. The index set's count or lastIndex cannot exceed -numberOfAssets.
// 'enumerationBlock' is used to pass back results to the caller and provide the opportunity to stop the filter.
// When the enumeration is done, 'enumerationBlock' will be called with result set to nil and index set to NSNotFound.
// If the application has not been granted access to the data, 'enumerationBlock' will be called with result set to nil, index set to NSNotFound, and stop set to YES.
- (void)enumerateAssetsUsingBlock:(ALAssetsGroupEnumerationResultsBlock)enumerationBlock NS_DEPRECATED_IOS(4_0, 9_0, "Use the PHFetchResult returned by fetchAssetsInAssetCollection:options: on PHAsset to enumerate the assets in an asset collection from the Photos framework instead");
- (void)enumerateAssetsWithOptions:(NSEnumerationOptions)options usingBlock:(ALAssetsGroupEnumerationResultsBlock)enumerationBlock NS_DEPRECATED_IOS(4_0, 9_0, "Use the PHFetchResult returned by fetchAssetsInAssetCollection:options: on PHAsset to enumerate the assets in an asset collection from the Photos framework instead");
- (void)enumerateAssetsAtIndexes:(NSIndexSet *)indexSet options:(NSEnumerationOptions)options usingBlock:(ALAssetsGroupEnumerationResultsBlock)enumerationBlock NS_DEPRECATED_IOS(4_0, 9_0, "Use the PHFetchResult returned by fetchAssetsInAssetCollection:options: on PHAsset to enumerate the assets in an asset collection from the Photos framework instead");

// Returns YES if the application is able to edit the group.  Returns NO if the application is not able to edit the group.
@property (nonatomic, readonly, getter=isEditable) BOOL editable NS_DEPRECATED_IOS(5_0, 9_0, "Use canPerformEditOperation: on a PHAssetCollection from the Photos framework instead");

// Add an existing ALAsset to the group.  An asset can belong to multiple ALAssetsGroups.
// The caller should check the editable property of the group to see if it is possible to add an asset to the group.
// Returns YES if the asset was added successfully.  Returns NO if the group is not editable, or if the asset was not able to be added to the group.
- (BOOL)addAsset:(ALAsset *)asset NS_DEPRECATED_IOS(5_0, 9_0, "Use addAssets: on a PHAssetCollectionChangeRequest: created from a PHAssetCollection in the Photos framework instead");

@end

#endif
// ==========  AssetsLibrary.framework/Headers/ALAsset.h
//
//  ALAsset.h
//  AssetsLibrary
//
//  Copyright 2010 Apple Inc. All rights reserved.
//
/*
 *
 * An ALAsset represents a photo or a video managed by the Photos application. Assets can have multiple representations, like
 * a photo which has been shot in RAW and JPG. Furthermore, representations of the same asset may have different dimensions.
 *
 */

#import <Foundation/Foundation.h>
#import <AssetsLibrary/ALAssetsLibrary.h>
#import <CoreGraphics/CoreGraphics.h>

#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED

extern NSString *const ALErrorInvalidProperty NS_DEPRECATED_IOS(4_0, 9_0, "Use PHAsset class properties from the Photos framework instead");

// Properties
extern NSString *const ALAssetPropertyType NS_DEPRECATED_IOS(4_0, 9_0, "Use the mediaType property on a PHAsset from the Photos framework instead");             // An NSString that encodes the type of asset. One of ALAssetTypePhoto, ALAssetTypeVideo or ALAssetTypeUnknown.
extern NSString *const ALAssetPropertyLocation NS_DEPRECATED_IOS(4_0, 9_0, "Use the location property on a PHAsset from the Photos framework instead");         // CLLocation object with the location information of the asset. Only available if location services are enabled for the caller.
extern NSString *const ALAssetPropertyDuration NS_DEPRECATED_IOS(4_0, 9_0, "Use the duration property on a PHAsset from the Photos framework instead");         // Play time duration of a video asset expressed as a double wrapped in an NSNumber. For photos, kALErrorInvalidProperty is returned.
extern NSString *const ALAssetPropertyOrientation NS_DEPRECATED_IOS(4_0, 9_0, "Use the orientation of the UIImage returned for a PHAsset via the PHImageManager from the Photos framework instead");      // NSNumber containing an asset's orientation as defined by ALAssetOrientation.
extern NSString *const ALAssetPropertyDate NS_DEPRECATED_IOS(4_0, 9_0, "Use the creationDate property on a PHAsset from the Photos framework instead");             // An NSDate with the asset's creation date.

// Properties related to multiple photo representations
extern NSString *const ALAssetPropertyRepresentations NS_DEPRECATED_IOS(4_0, 9_0, "Use PHImageRequestOptions with the PHImageManager from the Photos framework instead");  // Array with all the representations available for a given asset (e.g. RAW, JPEG). It is expressed as UTIs.
extern NSString *const ALAssetPropertyURLs NS_DEPRECATED_IOS(4_0, 9_0, "Use PHImageRequestOptions with the PHImageManager from the Photos framework instead");             // Dictionary that maps asset representation UTIs to URLs that uniquely identify the asset.
extern NSString *const ALAssetPropertyAssetURL NS_DEPRECATED_IOS(4_0, 9_0, "Use the localIdentifier property on a PHAsset (or to lookup PHAssets by a previously known ALAssetPropertyAssetURL use fetchAssetsWithALAssetURLs:options:) from the Photos framework instead");         // An NSURL that uniquely identifies the asset

// Asset types
extern NSString *const ALAssetTypePhoto NS_DEPRECATED_IOS(4_0, 9_0, "Use PHAssetMediaTypeImage from the Photos framework instead");                // The asset is a photo
extern NSString *const ALAssetTypeVideo NS_DEPRECATED_IOS(4_0, 9_0, "Use PHAssetMediaTypeVideo from the Photos framework instead");                // The asset is a video
extern NSString *const ALAssetTypeUnknown NS_DEPRECATED_IOS(4_0, 9_0, "Use PHAssetMediaTypeAudio for audio or PHAssetMediaTypeUnknown for unknown media types from the Photos framework instead");              // The asset's type cannot be determined. It could be a sound file, a video or photo file that we don't know about, or something else. This is possible only for assets imported from a camera onto the device.

@class ALAssetRepresentation;

NS_CLASS_DEPRECATED_IOS(4_0, 9_0, "Use PHAsset from the Photos framework instead")
@interface ALAsset : NSObject {
@package
    id _internal;
}

// Returns the value for a given property (as defined above). Calling it with an invalid property returns a ALErrorInvalidProperty error.
- (id)valueForProperty:(NSString *)property NS_DEPRECATED_IOS(4_0, 9_0, "Use PHAsset class properties from the Photos framework instead");

// Returns an ALAssetRepresentation object for the default representation of the ALAsset
- (ALAssetRepresentation *)defaultRepresentation NS_DEPRECATED_IOS(4_0, 9_0, "Use PHImageRequestOptions with the PHImageManager from the Photos framework instead");

// Returns an ALAssetRepresentation object for the given representation UTI. If the ALAsset does not
// support the representation, nil is returned.
- (ALAssetRepresentation *)representationForUTI:(NSString *)representationUTI NS_DEPRECATED_IOS(4_0, 9_0, "Use PHImageRequestOptions with the PHImageManager from the Photos framework instead");

// Returns a CGImage with a square thumbnail of the asset.  The size of the thumbnail is the appropriate size for the platform.  The thumbnail will be in the correct orientation.
- (CGImageRef)thumbnail NS_DEPRECATED_IOS(4_0, 9_0, "Use requestImageForAsset:targetSize:contentMode:options:resultHandler: on PHImageManager to request a thumbnail sized image for a PHAsset from the Photos framework instead");

// Returns a CGImage with an aspect ratio thumbnail of the asset.  The size of the thumbnail is the appropriate size for the platform.  The thumbnail will be in the correct orientation.
- (CGImageRef)aspectRatioThumbnail NS_DEPRECATED_IOS(5_0, 9_0, "Use the PHImageContentMode options to request thumbnail aspect ratio in PHImageRequestOptions with the PHImageManager");

// Saves image data to the saved photos album as a new ALAsset that is considered a modified version of the calling ALAsset.
- (void)writeModifiedImageDataToSavedPhotosAlbum:(NSData *)imageData metadata:(NSDictionary *)metadata completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock NS_DEPRECATED_IOS(5_0, 9_0, "Use creationRequestForAssetFromImage: on PHAssetChangeRequest from the Photos framework to create a new asset instead");

// Saves the video at the specified path to the saved photos album as a new ALAsset that is considered a modified version of the calling ALAsset.
- (void)writeModifiedVideoAtPathToSavedPhotosAlbum:(NSURL *)videoPathURL completionBlock:(ALAssetsLibraryWriteVideoCompletionBlock)completionBlock NS_DEPRECATED_IOS(5_0, 9_0, "Use creationRequestForAssetFromVideoAtFileURL: on PHAssetChangeRequest from the Photos framework to create a new asset instead");

// Returns the original asset if the caller was saved as a modified version of an asset.
// Returns nil if the caller was not saved as a modified version of an asset.
@property (nonatomic, readonly) ALAsset *originalAsset NS_DEPRECATED_IOS(5_0, 9_0, "Use the PHImageRequestOptionsVersionOriginal or PHImageRequestOptionsVersionUnadjusted option in PHImageRequestOptions with the PHImageManager from the Photos framework instead");

// Returns YES if the application is able to edit the asset.  Returns NO if the application is not able to edit the asset.
// Applications are only allowed to edit assets that they originally wrote.
@property (nonatomic, readonly, getter=isEditable) BOOL editable NS_DEPRECATED_IOS(5_0, 9_0, "Use canPerformEditOperation: on a PHAsset from the Photos framework instead");

// Replaces the image data in the calling asset with the supplied image data.
// The caller should check the editable property of the asset to see if it is possible to replace the image data.
// If the application is able to edit the asset, the completion block will return the same assetURL as the calling asset, since a new asset is not being created.
// If the application is not able to edit the asset, the completion block will return a nil assetURL and an ALAssetsLibraryWriteFailedError.
- (void)setImageData:(NSData *)imageData metadata:(NSDictionary *)metadata completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock NS_DEPRECATED_IOS(5_0, 9_0, "Use contentEditingOutput on a PHAssetChangeRequest from the Photos framework instead");

// Replaces the video data in the calling asset with the video at the specified path.
// The caller should check the editable property of the asset to see if it is possible to replace the video data.
// If the application is able to edit the asset, the completion block will return the same assetURL as the calling asset, since a new asset is not being created.
// If the application is not able to edit the asset (see the editable property on ALAsset), the completion block will return a nil assetURL and an ALAssetsLibraryWriteFailedError.
- (void)setVideoAtPath:(NSURL *)videoPathURL completionBlock:(ALAssetsLibraryWriteVideoCompletionBlock)completionBlock NS_DEPRECATED_IOS(5_0, 9_0, "Use contentEditingOutput on a PHAssetChangeRequest from the Photos framework instead");

@end

#endif
// ==========  AssetsLibrary.framework/Headers/AssetsLibrary.h
/*
 *  AssetsLibrary.h
 *  AssetsLibrary
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#import <AssetsLibrary/ALAsset.h>
#import <AssetsLibrary/ALAssetsFilter.h>
#import <AssetsLibrary/ALAssetsGroup.h>
#import <AssetsLibrary/ALAssetsLibrary.h>
#import <AssetsLibrary/ALAssetRepresentation.h>
// ==========  AssetsLibrary.framework/Headers/ALAssetsLibrary.h
//
//  ALAssetsLibrary.h
//  AssetsLibrary
//
//  Copyright 2010 Apple Inc. All rights reserved.
//
/*
 *
 * This class represents the set of all videos and photos that are under the control of the Photos application. This includes
 * those that are in the saved photos album and those coming from iTunes.
 * It is used to retrieve the list of all asset groups and to save images and videos into the Saved Photos album.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED

@class ALAsset;
@class ALAssetsGroup;

typedef NS_ENUM(NSInteger, ALAssetOrientation) {
    ALAssetOrientationUp NS_ENUM_DEPRECATED_IOS(4_0, 9_0),            // default orientation
    ALAssetOrientationDown NS_ENUM_DEPRECATED_IOS(4_0, 9_0),          // 180 deg rotation
    ALAssetOrientationLeft NS_ENUM_DEPRECATED_IOS(4_0, 9_0),          // 90 deg CCW
    ALAssetOrientationRight NS_ENUM_DEPRECATED_IOS(4_0, 9_0),         // 90 deg CW
    ALAssetOrientationUpMirrored NS_ENUM_DEPRECATED_IOS(4_0, 9_0),    // as above but image mirrored along other axis. horizontal flip
    ALAssetOrientationDownMirrored NS_ENUM_DEPRECATED_IOS(4_0, 9_0),  // horizontal flip
    ALAssetOrientationLeftMirrored NS_ENUM_DEPRECATED_IOS(4_0, 9_0),  // vertical flip
    ALAssetOrientationRightMirrored NS_ENUM_DEPRECATED_IOS(4_0, 9_0), // vertical flip
} NS_DEPRECATED_IOS(4_0, 9_0, "Use UIImageOrientation in the Photos framework instead");

enum {
    ALAssetsGroupLibrary     NS_ENUM_DEPRECATED_IOS(4_0, 9_0) = (1 << 0),         // The Library group that includes all assets.
    ALAssetsGroupAlbum       NS_ENUM_DEPRECATED_IOS(4_0, 9_0) = (1 << 1),         // All the albums synced from iTunes or created on the device.
    ALAssetsGroupEvent       NS_ENUM_DEPRECATED_IOS(4_0, 9_0) = (1 << 2),         // All the events synced from iTunes.
    ALAssetsGroupFaces       NS_ENUM_DEPRECATED_IOS(4_0, 9_0) = (1 << 3),         // All the faces albums synced from iTunes.
    ALAssetsGroupSavedPhotos NS_ENUM_DEPRECATED_IOS(4_0, 9_0) = (1 << 4),         // The Saved Photos album.
#if __IPHONE_5_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    ALAssetsGroupPhotoStream NS_ENUM_DEPRECATED_IOS(5_0, 9_0) = (1 << 5),         // The PhotoStream album.
#endif
    ALAssetsGroupAll         NS_ENUM_DEPRECATED_IOS(4_0, 9_0) = 0xFFFFFFFF,       // The same as ORing together all the available group types,
};
typedef NSUInteger ALAssetsGroupType NS_DEPRECATED_IOS(4_0, 9_0, "Use PHAssetCollectionType and PHAssetCollectionSubtype in the Photos framework instead");

typedef NS_ENUM(NSInteger, ALAuthorizationStatus) {
    ALAuthorizationStatusNotDetermined NS_ENUM_DEPRECATED_IOS(6_0, 9_0) = 0, // User has not yet made a choice with regards to this application
    ALAuthorizationStatusRestricted NS_ENUM_DEPRECATED_IOS(6_0, 9_0),        // This application is not authorized to access photo data.
                                            // The user cannot change this application’s status, possibly due to active restrictions
                                            //  such as parental controls being in place.
    ALAuthorizationStatusDenied NS_ENUM_DEPRECATED_IOS(6_0, 9_0),            // User has explicitly denied this application access to photos data.
    ALAuthorizationStatusAuthorized NS_ENUM_DEPRECATED_IOS(6_0, 9_0)        // User has authorized this application to access photos data.
} NS_DEPRECATED_IOS(6_0, 9_0, "Use PHAuthorizationStatus in the Photos framework instead");


// This block is executed when a match is found during enumeration. The match is passed to the block in the group argument.
// When the enumeration is done, the block will be called with group set to nil.
// Setting the output argument stop to YES will finish the enumeration.
typedef void (^ALAssetsLibraryGroupsEnumerationResultsBlock)(ALAssetsGroup *group, BOOL *stop) NS_DEPRECATED_IOS(4_0, 9_0, "Use the PHFetchResult returned by fetchAssetCollectionsInCollectionList:options: on PHAssetCollection from the Photos framework to enumerate the asset collections in a collection list instead");

// This block is executed if the user has granted access to the caller to access the data managed by the framework.
// If the asset is not found, asset is nil.
typedef void (^ALAssetsLibraryAssetForURLResultBlock)(ALAsset *asset) NS_DEPRECATED_IOS(4_0, 9_0, "Use fetchAssetsWithLocalIdentifiers:options: on PHAsset to fetch assets by local identifier (or to lookup PHAssets by a previously known ALAssetPropertyAssetURL use fetchAssetsWithALAssetURLs:options:) from the Photos framework instead");

// This block is executed if the user has granted access to the caller to access the data managed by the framework.
// If the group is not found, group is nil.
typedef void (^ALAssetsLibraryGroupResultBlock)(ALAssetsGroup *group) NS_DEPRECATED_IOS(5_0, 9_0, "Use fetchAssetCollectionsWithLocalIdentifiers:options: on PHAssetCollection to fetch the asset collections by local identifier (or to lookup PHAssetCollections by a previously known ALAssetsGroupPropertyURL use fetchAssetCollectionsWithALAssetGroupURLs:options:) from the Photos framework instead");

// This block is executed if the user does not grant access to the caller to access the data managed by the framework or if the data is currently unavailable.
typedef void (^ALAssetsLibraryAccessFailureBlock)(NSError *error) NS_DEPRECATED_IOS(4_0, 9_0, "Use the Photos framework instead");

// This block is executed when saving an image by -writeImageToSavedPhotosAlbum:completionBlock: finishes. The assetURL can later be used to reference the saved image.
typedef void (^ALAssetsLibraryWriteImageCompletionBlock)(NSURL *assetURL, NSError *error) NS_DEPRECATED_IOS(4_0, 9_0, "Use performChanges:completionHandler: or performChangesAndWait: on the shared PHPhotoLibrary with a PHAssetChangeRequest from the Photos framework instead");
// This block is executed when saving a video by -writeVideoAtPathToSavedPhotosAlbum:completionBlock: finishes. The assetURL can later be used to reference the saved video.
typedef void (^ALAssetsLibraryWriteVideoCompletionBlock)(NSURL *assetURL, NSError *error) NS_DEPRECATED_IOS(4_0, 9_0, "Use performChanges:completionHandler: or performChangesAndWait: on the shared PHPhotoLibrary with a PHAssetChangeRequest from the Photos framework instead");


NS_CLASS_DEPRECATED_IOS(4_0, 9_0, "Use PHPhotoLibrary from the Photos framework instead")
@interface ALAssetsLibrary : NSObject {
@package
    id _internal;
    
}

// Get the list of groups that match the given types. Multiple types can be ORed together. The results are passed one by one to the caller by executing the enumeration block.
// When the enumeration is done, 'enumerationBlock' will be called with group set to nil.
// When groups are enumerated, the user may be asked to confirm the application's access to the data. If the user denies access to the application or if no application is allowed to access the data, the failure block will be called.
// If the data is currently unavailable, the failure block will be called.
- (void)enumerateGroupsWithTypes:(ALAssetsGroupType)types usingBlock:(ALAssetsLibraryGroupsEnumerationResultsBlock)enumerationBlock failureBlock:(ALAssetsLibraryAccessFailureBlock)failureBlock NS_DEPRECATED_IOS(4_0, 9_0, "Use the PHFetchResult returned by one of the fetch... methods on PHAssetCollection from the Photos framework to enumerate asset collections instead");

// Returns an ALAsset object in the result block for a URL previously retrieved from an ALAsset object.
// When the ALAsset is requested, the user may be asked to confirm the application's access to the data. If the user denies access to the application or if no application is allowed to access the data, the failure block will be called.
// If the data is currently unavailable, the failure block will be called.
- (void)assetForURL:(NSURL *)assetURL resultBlock:(ALAssetsLibraryAssetForURLResultBlock)resultBlock failureBlock:(ALAssetsLibraryAccessFailureBlock)failureBlock NS_DEPRECATED_IOS(4_0, 9_0, "Use fetchAssetsWithLocalIdentifiers:options: on PHAsset to fetch assets by local identifier (or to lookup PHAssets by a previously known ALAssetPropertyAssetURL use fetchAssetsWithALAssetURLs:options:) from the Photos framework instead");

// Returns an ALAssetsGroup object in the result block for a URL previously retrieved from an ALAssetsGroup object.
// When the ALAssetsGroup is requested, the user may be asked to confirm the application's access to the data.  If the user denies access to the application or if no application is allowed to access the data, the failure block will be called.
// If the data is currently unavailable, the failure block will be called.
- (void)groupForURL:(NSURL *)groupURL resultBlock:(ALAssetsLibraryGroupResultBlock)resultBlock failureBlock:(ALAssetsLibraryAccessFailureBlock)failureBlock NS_DEPRECATED_IOS(5_0, 9_0, "Use fetchAssetCollectionsWithLocalIdentifiers:options: on PHAssetCollection to fetch the asset collections by local identifier (or to lookup PHAssetCollections by a previously known ALAssetsGroupPropertyURL use fetchAssetCollectionsWithALAssetGroupURLs:options:) from the Photos framework instead");

// Add a new ALAssetsGroup to the library.
// The name of the ALAssetsGroup is name and the type is ALAssetsGroupAlbum.  The editable property of this ALAssetsGroup returns YES.
// If name conflicts with another ALAssetsGroup with the same name, then the group is not created and the result block returns a nil group.
// When the ALAssetsGroup is added, the user may be asked to confirm the application's access to the data.  If the user denies access to the application or if no application is allowed to access the data, the failure block will be called.
// If the data is currently unavailable, the failure block will be called.
- (void)addAssetsGroupAlbumWithName:(NSString *)name resultBlock:(ALAssetsLibraryGroupResultBlock)resultBlock failureBlock:(ALAssetsLibraryAccessFailureBlock)failureBlock NS_DEPRECATED_IOS(5_0, 9_0, "Use creationRequestForAssetCollectionWithTitle: on PHAssetCollectionChangeRequest from the Photos framework to create a new asset collection instead");

// These methods can be used to add photos or videos to the saved photos album.

// With a UIImage, the API user can use -[UIImage CGImage] to get a CGImageRef, and cast -[UIImage imageOrientation] to ALAssetOrientation.
- (void)writeImageToSavedPhotosAlbum:(CGImageRef)imageRef orientation:(ALAssetOrientation)orientation completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock NS_DEPRECATED_IOS(4_0, 9_0, "Use creationRequestForAssetFromImage: on PHAssetChangeRequest from the Photos framework to create a new asset instead");

// The API user will have to specify the orientation key in the metadata dictionary to preserve the orientation of the image
- (void)writeImageToSavedPhotosAlbum:(CGImageRef)imageRef metadata:(NSDictionary *)metadata completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock NS_DEPRECATED_IOS(4_1, 9_0, "Use creationRequestForAssetFromImage: on PHAssetChangeRequest from the Photos framework to create a new asset instead");

// If there is a conflict between the metadata in the image data and the metadata dictionary, the image data metadata values will be overwritten
- (void)writeImageDataToSavedPhotosAlbum:(NSData *)imageData metadata:(NSDictionary *)metadata completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock NS_DEPRECATED_IOS(4_1, 9_0, "Use creationRequestForAssetFromImageData: on PHAssetChangeRequest from the Photos framework to create a new asset instead");

- (void)writeVideoAtPathToSavedPhotosAlbum:(NSURL *)videoPathURL completionBlock:(ALAssetsLibraryWriteVideoCompletionBlock)completionBlock NS_DEPRECATED_IOS(4_0, 9_0, "Use creationRequestForAssetFromVideoAtFilePath: on PHAssetChangeRequest from the Photos framework to create a new asset instead");
- (BOOL)videoAtPathIsCompatibleWithSavedPhotosAlbum:(NSURL *)videoPathURL NS_DEPRECATED_IOS(5_0, 9_0, "Use isCompatibleWithSavedPhotosAlbum on AVAsset instead");

// Returns photo data authorization status for this application
+ (ALAuthorizationStatus)authorizationStatus NS_DEPRECATED_IOS(6_0, 9_0, "Use authorizationStatus on the shared PHPhotoLibrary from the Photos framework instead");

// Disable retrieval and notifications for Shared Photo Streams
+ (void)disableSharedPhotoStreamsSupport NS_DEPRECATED_IOS(6_0, 9_0, "Use the Photos framework instead");

@end

// Notifications

// This notification will be sent when the contents of the ALAssetsLibrary have changed from under the app that is using the data.
// The API user should retain the library object to receive this notification.
// The userInfo may include the keys listed below, which identify specific ALAssets or ALAssetGroups that have become invalid and should be discarded. The values are NSSets of NSURLs which match the ALAssetPropertyURL and ALAssetsGroupPropertyURL properties. 
// If the userInfo is nil, all ALAssets and ALAssetGroups should be considered invalid and discarded.
// Modified ALAssets will be identified by the ALAssetLibraryUpdatedAssetsKey, but inserted or deleted ALAssets are identified by invalidating the containing ALAssetGroups.
extern NSString *const ALAssetsLibraryChangedNotification NS_DEPRECATED_IOS(4_0, 9_0, "Use photoLibraryDidChange: notification from the Photos framework instead");

extern NSString *const ALAssetLibraryUpdatedAssetsKey NS_DEPRECATED_IOS(6_0, 9_0, "Use changeDetailsForFetchResult: and changeDetailsForObject: to get change details via the PHChange object included on photoLibraryDidChange: from the Photos framework instead");
extern NSString *const ALAssetLibraryInsertedAssetGroupsKey NS_DEPRECATED_IOS(6_0, 9_0, "Use changeDetailsForFetchResult: and changeDetailsForObject: to get change details via the PHChange object included on photoLibraryDidChange: from the Photos framework instead");
extern NSString *const ALAssetLibraryUpdatedAssetGroupsKey NS_DEPRECATED_IOS(6_0, 9_0, "Use changeDetailsForFetchResult: and changeDetailsForObject: to get change details via the PHChange object included on photoLibraryDidChange: from the Photos framework instead");
extern NSString *const ALAssetLibraryDeletedAssetGroupsKey NS_DEPRECATED_IOS(6_0, 9_0, "Use changeDetailsForFetchResult: and changeDetailsForObject: to get change details via the PHChange object included on photoLibraryDidChange: from the Photos framework instead");

// Errors

// Constant used by NSError to distinguish errors belonging to the AssetsLibrary domain
extern NSString *const ALAssetsLibraryErrorDomain NS_DEPRECATED_IOS(4_0, 9_0, "Use the Photos framework instead");

// AssetsLibrary-related error codes
enum {
    ALAssetsLibraryUnknownError =                 -1,      // Error (reason unknown)
    
    // These errors would be returned in the ALAssetsLibraryWriteImageCompletionBlock and ALAssetsLibraryWriteVideoCompletionBlock completion blocks,
    // as well as in the completion selector for UIImageWriteToSavedPhotosAlbum() and UISaveVideoAtPathToSavedPhotosAlbum()
    ALAssetsLibraryWriteFailedError =           -3300,      // Write error (write failed)
    ALAssetsLibraryWriteBusyError =             -3301,      // Write error (writing is busy, try again)
    ALAssetsLibraryWriteInvalidDataError =      -3302,      // Write error (invalid data)
    ALAssetsLibraryWriteIncompatibleDataError = -3303,      // Write error (incompatible data)
    ALAssetsLibraryWriteDataEncodingError =     -3304,      // Write error (data has invalid encoding)
    ALAssetsLibraryWriteDiskSpaceError =        -3305,      // Write error (out of disk space)

    // This error would be returned in the ALAssetsLibraryAccessFailureBlock, ALAssetsLibraryWriteImageCompletionBlock, and ALAssetsLibraryWriteVideoCompletionBlock completion blocks,
    // as well as in the completion selector for UIImageWriteToSavedPhotosAlbum() and UISaveVideoAtPathToSavedPhotosAlbum()
    ALAssetsLibraryDataUnavailableError =       -3310,      // Data unavailable (data currently unavailable)    
    
    // These errors would be returned in the ALAssetsLibraryAccessFailureBlock
    ALAssetsLibraryAccessUserDeniedError =      -3311,      // Access error (user denied access request)
    ALAssetsLibraryAccessGloballyDeniedError =  -3312,      // Access error (access globally denied)
} NS_DEPRECATED_IOS(4_0, 9_0, "Use the Photos framework instead");

#endif
// ==========  AssetsLibrary.framework/Headers/ALAssetsFilter.h
//
//  ALAssetsFilter.h
//  AssetsLibrary
//
//  Copyright 2010 Apple Inc. All rights reserved.
//
/*
 *
 * This class encapsulates filtering criteria to be used when retrieving assets from a group.
 *
 */

#import <Foundation/Foundation.h>

#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED

NS_CLASS_DEPRECATED_IOS(4_0, 9_0, "Use fetchAssetsInAssetCollection:options: on PHAsset and set a mediaType predicate on the PHFetchOptions from the Photos framework instead")
@interface ALAssetsFilter : NSObject {
@package
    id _internal;
}

// Get all photos assets in the assets group.
+ (ALAssetsFilter *)allPhotos;
// Get all video assets in the assets group.
+ (ALAssetsFilter *)allVideos;
// Get all assets in the group.
+ (ALAssetsFilter *)allAssets;

@end

#endif
