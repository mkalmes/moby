// ==========  LinkPresentation.framework/Headers/LPError.h
//
//  LinkPresentation
//  Copyright © 2015-2019 Apple Inc. All rights reserved.
//

#import <LinkPresentation/LPFoundation.h>

/** LPErrorDomain is used to indicate a LinkPresentation error. */
LP_EXTERN NSErrorDomain const LPErrorDomain API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0));

/** Constants used by NSError to indicate errors in the LinkPresentation domain. */
typedef NS_ERROR_ENUM(LPErrorDomain, LPErrorCode) {
    /** LPErrorUnknown indicates that an unknown error occurred. */
    LPErrorUnknown = 1,

    /** LPErrorMetadataFetchFailed indicates that a metadata fetch failed.
     This can be due to network conditions, server availability, or any number of other causes. */
    LPErrorMetadataFetchFailed,

    /** LPErrorMetadataFetchCancelled indicates that the metadata fetch was cancelled by the client. */
    LPErrorMetadataFetchCancelled,

    /** LPErrorMetadataFetchTimedOut indicates that the metadata fetch took longer than allowed. */
    LPErrorMetadataFetchTimedOut
} API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0));
// ==========  LinkPresentation.framework/Headers/LPLinkView.h
//
//  LinkPresentation
//  Copyright © 2015-2019 Apple Inc. All rights reserved.
//

#import <LinkPresentation/LPFoundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@class LPLinkMetadata;

/**
 An LPLinkView provides a rich visual representation of an LPLinkMetadata object.

 @see `LPLinkMetadata`
 @see `LPMetadataProvider`
 */
LP_EXTERN API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0))
#if TARGET_OS_IPHONE
@interface LPLinkView : UIView
#else
@interface LPLinkView : NSView
#endif

- (instancetype)initWithCoder:(NSCoder *)coder NS_UNAVAILABLE;
- (void)encodeWithCoder:(NSCoder *)coder NS_UNAVAILABLE;

- (instancetype)initWithURL:(NSURL *)URL;
- (instancetype)initWithMetadata:(LPLinkMetadata *)metadata;

/**
 The LPLinkMetadata object with which to generate a rich presentation.

 The metadata can either be generated automatically from a URL by LPMetadataProvider,
 or manually constructed with the desired data.
 */
@property (nonatomic, copy) LPLinkMetadata *metadata;

@end

NS_ASSUME_NONNULL_END
// ==========  LinkPresentation.framework/Headers/LPFoundation.h
//
//  LinkPresentation
//  Copyright © 2015-2019 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <Foundation/Foundation.h>
#import <TargetConditionals.h>

#ifdef __cplusplus
#define LP_EXTERN extern "C" __attribute__((visibility ("default")))
#define LP_EXTERN_C extern "C"
#else
#define LP_EXTERN extern __attribute__((visibility ("default")))
#define LP_EXTERN_C extern
#endif
// ==========  LinkPresentation.framework/Headers/LPMetadataProvider.h
//
//  LinkPresentation
//  Copyright © 2015-2019 Apple Inc. All rights reserved.
//

#import <LinkPresentation/LPFoundation.h>

#import <LinkPresentation/LPLinkMetadata.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An LPMetadataProvider object retrieves metadata for a given URL.

 An instance of LPMetadataProvider can only be asked to retrieve metadata once;
 a new instance should be created for each request.

 A client must have the com.apple.security.network.client entitlement
 in order to be able to use LPMetadataProvider for remote URLs.

 @see `LPLinkMetadata`
 */
LP_EXTERN API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos)
@interface LPMetadataProvider : NSObject

/**
 Fetch metadata for the given URL.

 The completion handler will be called on a non-main queue.

 File URLs returned in the resultant LPLinkMetadata will be deleted
 when the completion handler returns.

 An exception will be thrown if this is called more than once
 on a particular LPMetadataProvider instance.
 */
- (void)startFetchingMetadataForURL:(NSURL *)URL completionHandler:(void(^)(LPLinkMetadata *_Nullable metadata, NSError *_Nullable error))completionHandler;

/**
 Cancel a metadata request.

 If the request had not already completed, the completion handler will be invoked
 with the error code `LPErrorMetadataFetchCancelled`.
 */
- (void)cancel;

/**
 A boolean value indicating whether LPMetadataProvider should download secondary
 resources specified by the metadata, like the icon, image, or video. If
 shouldFetchSubresources is set to `NO`, the returned LPLinkMetadata object will
 consist only of metadata retrieved from the main resource.
 
 The default value is `YES`.
 */
@property (nonatomic) BOOL shouldFetchSubresources;

/**
 The time interval after which the request will automatically fail if it has not
 already completed.

 If the timeout is reached, no metadata is returned; the completion handler will
 be invoked with the error code `LPErrorMetadataFetchTimedOut`.

 The default timeout is 30 seconds.
*/
@property (nonatomic) NSTimeInterval timeout;

@end

NS_ASSUME_NONNULL_END
// ==========  LinkPresentation.framework/Headers/LPLinkMetadata.h
//
//  LinkPresentation
//  Copyright © 2015-2019 Apple Inc. All rights reserved.
//

#import <LinkPresentation/LPFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An LPLinkMetadata object contains metadata about a URL.
 */
LP_EXTERN API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0))
@interface LPLinkMetadata : NSObject <NSCopying, NSSecureCoding>

/** The original URL that metadata was requested from. */
@property (nonatomic, retain, nullable) NSURL *originalURL;

/**
 The URL that metadata was retrieved from.
 This takes server-side redirects into account.
 */
@property (nonatomic, retain, nullable) NSURL *URL;

/**
 A title for the URL.
 */
@property (nonatomic, copy, nullable) NSString *title;

/**
 An item provider which will return data corresponding to a representative
 icon for the URL.
 */
@property (nonatomic, retain, nullable) NSItemProvider *iconProvider;

/**
 An item provider which will return data corresponding to a representative
 image for the URL.
 */
@property (nonatomic, retain, nullable) NSItemProvider *imageProvider;

/**
 An item provider which will return data corresponding to a representative
 video for the URL that AVFoundation can play.
 */
@property (nonatomic, retain, nullable) NSItemProvider *videoProvider;

/**
 A remote URL corresponding to a representative video for the URL.

 This may point to to a remote video file that AVFoundation can stream,
 or to a YouTube video URL.
 */
@property (nonatomic, retain, nullable) NSURL *remoteVideoURL;

@end

NS_ASSUME_NONNULL_END
// ==========  LinkPresentation.framework/Headers/LinkPresentation.h
//
//  LinkPresentation
//  Copyright © 2015-2019 Apple Inc. All rights reserved.
//

#import <LinkPresentation/LPFoundation.h>

#import <LinkPresentation/LPError.h>
#import <LinkPresentation/LPLinkMetadata.h>
#import <LinkPresentation/LPLinkView.h>
#import <LinkPresentation/LPMetadataProvider.h>
