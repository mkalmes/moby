// ==========  QuickLookThumbnailing.framework/Headers/QLThumbnailRequest.h
//
//  QLThumbnailRequest.h
//  Mobile Quick Look
//
//  Copyright 2016 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @abstract This class contains information about the thumbnail that should be provided.
 */
API_AVAILABLE(ios(11.0), macos(10.15)) API_UNAVAILABLE(watchos,tvos)  __attribute__((visibility("default")))
@interface QLFileThumbnailRequest : NSObject

/**
The maximum size of the generated thumbnail that will be accepted. This is also the preferred size, ideally either the width or the height will match the maximumSize's width or height respectively.
 */
@property (nonatomic, readonly) CGSize maximumSize;

/**
 The minimum size of the generated thumbnail that will be accepted.
 */
@property (nonatomic, readonly) CGSize minimumSize;

/**
 The scale of the requested thumbnail.
 */
@property (nonatomic, readonly) CGFloat scale;

/**
 The url of the file for which a thumbnail is being requested.
 */
@property (nonatomic, copy, readonly) NSURL* fileURL;

@end

NS_ASSUME_NONNULL_END
// ==========  QuickLookThumbnailing.framework/Headers/QLThumbnailGenerator.h
//
//  QLThumbnailGenerator.h
//  Quick Look Thumbnailing
//
//  Copyright (c) 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuickLookThumbnailing/QLThumbnailGenerationRequest.h>
#import <QuickLookThumbnailing/QLThumbnailGeneratorErrors.h>
#import <QuickLookThumbnailing/QLThumbnailRepresentation.h>
#import <QuickLookThumbnailing/QLThumbnailingBase.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos,tvos)
QLT_EXPORT @interface QLThumbnailGenerator : NSObject

@property (class, readonly) QLThumbnailGenerator *sharedGenerator NS_SWIFT_NAME(shared);

/**
 @param completionHandler
 Always called when the thumbnail generation is over.
 The thumbnail passed to this handler is the most representative version of the thumbnail that was successfully generated (if any).
 If set, the error contains information about the issue that occurred while trying to generate the thumbnail.
 QLThumbnailGenerator error codes can be found in <QuickLookThumbnailing/QLThumbnailGeneratorErrors.h>.
 */
- (void)generateBestRepresentationForRequest:(QLThumbnailGenerationRequest *)request
                           completionHandler:(void (^)(QLThumbnailRepresentation * _Nullable thumbnail, NSError * _Nullable error))completionHandler NS_SWIFT_NAME(generateBestRepresentation(for:completion:));

/**
 @param updateHandler
 Called for the successive requested representations of a thumbnail.
 If a representation was not successfully generated, this may be called with a nil representation.
 If a requested more representative version was successfully generated before a less representative one, this handler will be called only for the more representative version, skipping the less representative one.
 This handler is guaranteed to be called at least once, for the requested most representative version, whether a representation could be successfully generated or not.
 If set, the error contains information about the issue that occurred while trying to generate the representation of the given type.
 QLThumbnailGenerator error codes can be found in <QuickLookThumbnailing/QLThumbnailGeneratorErrors.h>.
 */
- (void)generateRepresentationsForRequest:(QLThumbnailGenerationRequest *)request
                            updateHandler:(void (^ _Nullable)(QLThumbnailRepresentation * _Nullable thumbnail, QLThumbnailRepresentationType type, NSError * _Nullable error))updateHandler
                            NS_SWIFT_NAME(generateRepresentations(for:update:));

/**
 Cancels the given QLThumbnailGenerationRequest.
 @param request The request that should be cancelled.
 */
- (void)cancelRequest:(QLThumbnailGenerationRequest *)request;

/**
 Saves a thumbnail for the request on disk at fileURL.
 The file saved at fileURL has to be deleted when it is not used anymore.
 This is primarily intended for file provider extensions which need to upload thumbnails and have a small memory limit.

 @param contentType An image content type to save the thumbnail as, supported by CGImageDestination, such as kUTTypePNG or kUTTypeJPEG
 @param completionHandler
 Always called when the thumbnail generation is over. Will contain an error if the thumbnail could not be successfully saved to disk at fileURL.
 */
- (void)saveBestRepresentationForRequest:(QLThumbnailGenerationRequest *)request
                             toFileAtURL:(NSURL*)fileURL
                         withContentType:(NSString*)contentType
                       completionHandler:(void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_NAME(saveBestRepresentation(for:toFileAt:contentType:completion:));

@end

NS_ASSUME_NONNULL_END
// ==========  QuickLookThumbnailing.framework/Headers/QLThumbnailingBase.h
/*
 *  QLBase.h
 *  Quick Look
 *
 *  Copyright 2007 Apple Inc.
 *  All rights reserved.
 *
 */

#if !defined(__QUICKLOOK_QLTHUMBNAILINGBASE__)
#define __QUICKLOOK_QLTHUMBNAILINGBASE__

#ifdef __cplusplus
    #define QLT_EXTERN_C_BEGIN extern "C" {
    #define QLT_EXTERN_C_END }
#else
    #define QLT_EXTERN_C_BEGIN
    #define QLT_EXTERN_C_END
#endif

#define QLT_EXPORT __attribute__((visibility("default")))
#define QLT_WEAK_EXPORT __attribute__((weak_import, visibility("default")))
#define QLT_PRIVATE_EXPORT __attribute__((visibility("hidden")))
#define QLT_INLINE static __inline__ __attribute__((always_inline))
#define QLT_NOINLINE __attribute__((noinline))
#define QLT_DEPRECATED __attribute__((deprecated))
#define QLT_FORMAT_ARG(F, A) __attribute__((format(CFString, F, A)))

#define QLT_LIKELY(T) __builtin_expect(T, 1);
#define QLT_UNLIKELY(T) __builtin_expect(T, 0)

#endif
// ==========  QuickLookThumbnailing.framework/Headers/QLThumbnailGeneratorErrors.h
//
//  QLThumbnailGeneratorErrors.h
//  Quick Look Thumbnailing
//
//  Copyright (c) 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuickLookThumbnailing/QLThumbnailingBase.h>

QLT_EXPORT extern NSErrorDomain const QLThumbnailGeneratorErrorDomain NS_SWIFT_NAME(QLThumbnailGenerator.ErrorDomain) API_AVAILABLE(macos(10.15), ios(13.0));

typedef NS_ERROR_ENUM(QLThumbnailGeneratorErrorDomain, QLThumbnailGeneratorError) {
    QLThumbnailGeneratorErrorGenerationFailed,
    QLThumbnailGeneratorErrorSavingToURLFailed,
    QLThumbnailGeneratorErrorNoCachedThumbnail,
    QLThumbnailGeneratorErrorNoCloudThumbnail,
    QLThumbnailGeneratorErrorRequestInvalid,
    QLThumbnailGeneratorErrorRequestCancelled,
} NS_SWIFT_NAME(QLThumbnailGenerator.Error) API_AVAILABLE(macos(10.15), ios(13.0));
// ==========  QuickLookThumbnailing.framework/Headers/QLThumbnailRepresentation.h
//
//  QLThumbnailRepresentation.h
//  Quick Look Thumbnailing
//
//  Copyright (c) 2019 Apple. All rights reserved.
//

#import <TargetConditionals.h>

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <QuickLookThumbnailing/QLThumbnailingBase.h>

@class UIImage;
@class NSImage;

typedef NS_ENUM (NSInteger, QLThumbnailRepresentationType) {
    QLThumbnailRepresentationTypeIcon = 0,                      // Icon of the file type of the thumbnail request, provided by the system, that may not satisfy the parameters of the request.
    QLThumbnailRepresentationTypeLowQualityThumbnail = 1,       // A version of the thumbnail that was retrieved from a cache or low quality generation but not satisfying the parameters of the request.
    QLThumbnailRepresentationTypeThumbnail = 2,                 // Final version of the thumbnail for the given request, satisfying the parameters of the request.
} API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_NAME(QLThumbnailRepresentation.RepresentationType);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos)
QLT_EXPORT @interface QLThumbnailRepresentation : NSObject

@property (nonatomic, readonly) QLThumbnailRepresentationType type;

/// Returns the CGImage representation of the thumbnail.
@property (nonatomic, readonly) CGImageRef CGImage;

/// Returns the UIImage representation of the thumbnail. You need to explicitly link against UIKit to use this property.
@property (nonatomic, readonly, strong) UIImage *UIImage API_UNAVAILABLE(macos);

/// Returns the NSImage representation of the thumbnail. You need to explicitly link against AppKit to use this property.
@property (nonatomic, readonly, strong) NSImage *NSImage API_UNAVAILABLE(ios);

@end

NS_ASSUME_NONNULL_END
// ==========  QuickLookThumbnailing.framework/Headers/QLThumbnailGenerationRequest.h
//
//  QLThumbnailGenerationRequest.h
//  Quick Look Thumbnailing
//
//  Copyright (c) 2019 Apple. All rights reserved.
//

#import <TargetConditionals.h>

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <QuickLookThumbnailing/QLThumbnailingBase.h>


@class QLThumbnailRepresentation;

typedef NS_OPTIONS (NSUInteger, QLThumbnailGenerationRequestRepresentationTypes) {
    QLThumbnailGenerationRequestRepresentationTypeIcon                      = 1 << 0,       // Request an icon, that is an image that represents the file type of the request. The size of an icon may not satisfy the parameters of the request (can be larger or smaller).
    QLThumbnailGenerationRequestRepresentationTypeLowQualityThumbnail       = 1 << 1,       // Request a thumbnail representing the file that may come from a previously generated and cached copy or faster lower quality generation, not satisfying the parameters of the request (can be larger or smaller).
    QLThumbnailGenerationRequestRepresentationTypeThumbnail                 = 1 << 2,       // Request a thumbnail representing the file, satisfying the parameters of the request (either retrieved from the cache, or generated).
    QLThumbnailGenerationRequestRepresentationTypeAll                       = NSUIntegerMax // Request all thumbnail representation types.
} API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_NAME(QLThumbnailGenerationRequest.RepresentationTypes);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos,tvos)
QLT_EXPORT NS_SWIFT_NAME(QLThumbnailGenerator.Request) @interface QLThumbnailGenerationRequest : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 @param url The url of the file on disk for which a thumbnail is requested.
 @param size The desired size of the thumbnails that should be generated.
 @param scale The desired scale of the thumbnails that should be generated. This will usually be the scale of the screen.
 You can for instance pass a scale different from the one of the screen if you would like to save generated thumbnails to a server to later download them on devices with a different screen scale.
 @param representationTypes The desired successive representations of the thumbnail that should be generated when possible.
 */
- (instancetype)initWithFileAtURL:(NSURL *)url
                             size:(CGSize)size
                            scale:(CGFloat)scale
              representationTypes:(QLThumbnailGenerationRequestRepresentationTypes)representationTypes;

/**
 Defaults to 0. If set, the thumbnail will have a width and height greater or equal to minimumDimension * scale.
 If set and it is not possible to generate thumbnails of minimumDimension for any of the requested QLThumbnailGenerationRequestRepresentationTypes, no thumbnail will be provided.
 */
@property (nonatomic, assign) CGFloat minimumDimension;

/**
 If set to YES, this will generate something appropriate for display as a file icon,
 meaning that the thumbnail might be embedded in a frame, show a curled corner, draw a background
 and/or a drop shadow, as appropriate for the platform.
 If set to NO, this will generate a raw undecorated thumbnail.
 Defaults to NO.
 */
@property (nonatomic, assign) BOOL iconMode;

@property (nonatomic, readonly) CGSize size;
@property (nonatomic, readonly) CGFloat scale;
@property (nonatomic, readonly) QLThumbnailGenerationRequestRepresentationTypes representationTypes;

@end

NS_ASSUME_NONNULL_END
// ==========  QuickLookThumbnailing.framework/Headers/QuickLookThumbnailing.h
//
//  QuickLookThumbnailing.h
//  Quick Look Thumbnailing
//
//  Copyright (c) 2018 Apple. All rights reserved.
//

#import <TargetConditionals.h>

#import <QuickLookThumbnailing/QLThumbnailRepresentation.h>
#import <QuickLookThumbnailing/QLThumbnailProvider.h>
#import <QuickLookThumbnailing/QLThumbnailReply.h>
#import <QuickLookThumbnailing/QLThumbnailRequest.h>
#import <QuickLookThumbnailing/QLThumbnailGenerationRequest.h>
#import <QuickLookThumbnailing/QLThumbnailGeneratorErrors.h>
#import <QuickLookThumbnailing/QLThumbnailGenerator.h>
// ==========  QuickLookThumbnailing.framework/Headers/QLThumbnailReply.h
//
//  QLThumbnailReply.h
//  Mobile Quick Look
//
//  Copyright 2016 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 To provide a thumbnail for a request, you have to return a QLThumbnailReply object.

 @discussion To provide a thumbnail, you have two options:
 1. Draw the thumbnail, by providing a QLThumbnailReply created with a drawing block.
 2. Pass the thumbnail file URL, by providing a QLThumbnailReply created with a file URL.
 */
API_AVAILABLE(ios(11.0), macos(10.15)) API_UNAVAILABLE(watchos,tvos)  __attribute__((visibility("default")))
@interface QLThumbnailReply : NSObject

- (instancetype)init NS_UNAVAILABLE;

/**
 You can create a reply with a drawing block that will draw into a given context with the coordinate system of Core Graphics.

 @param contextSize The desired size of the context that will be passed to the drawing block.
 It should be as close as possible to the maximumSize of the QLFileThumbnailRequest and it has to be greater than or equal to its minimumSize.

 Ideally, at least either contextSize's width matches maximumSize's width or contextSize's height matches maximumSize's height.
 The context size will be scaled to QLFileThumbnailRequest's scale value (if you pass (x, y), the size of the context will be (scale * x, scale * y)).
 @param drawingBlock The thumbnail should be drawn into the context passed to this block. It is a context of type CGBitmapContext, set up to be used with the coordinate system of Core Graphics.
 Return YES if the thumbnail was successfully drawn into the context. Return NO otherwise.
 */
+ (instancetype)replyWithContextSize:(CGSize)contextSize drawingBlock:(BOOL (^)(CGContextRef context))drawingBlock;

/**
 You can create a reply with a drawing block that will draw into the current context with the coordinate system of UIKit or AppKit.

 @param contextSize The desired size of the context that will be passed to the drawing block.
 It should be as close as possible to the maximumSize of the QLFileThumbnailRequest and it has to be greater than or equal to its minimumSize.

 Ideally, at least either contextSize's width matches maximumSize's width or contextSize's height matches maximumSize's height.
 The context size will be scaled to QLFileThumbnailRequest's scale value (if you pass (x, y), the size of the context will be (scale * x, scale * y)).
 @param drawingBlock A block that draws the thumbnail into the current context which you can access via UIGraphicsGetCurrentContext() or [NSGraphicsContext currentContext].
 It is a context of type CGBitmapContext, set up to be used with the coordinate system of UIKit or AppKit.
 Return YES if the thumbnail was successfully drawn into the current context. Return NO otherwise.
 */
+ (instancetype)replyWithContextSize:(CGSize)contextSize currentContextDrawingBlock:(BOOL (^)(void))drawingBlock;

/**
 You can create a reply object with a file URL of an image that will be used as the thumbnail.
 The image will be downscaled to fit the size of the QLFileThumbnailRequest if necessary.
 */
+ (instancetype)replyWithImageFileURL:(NSURL *)fileURL;

@end

NS_ASSUME_NONNULL_END
// ==========  QuickLookThumbnailing.framework/Headers/QLThumbnailProvider.h
//
//  QLThumbnailProvider.h
//  Mobile Quick Look
//
//  Copyright 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class QLFileThumbnailRequest, QLThumbnailReply;

API_AVAILABLE(ios(11.0), macos(10.15)) API_UNAVAILABLE(tvos, watchos) __attribute__((visibility("default")))
@interface QLThumbnailProvider : NSObject

/**
 Subclass this method to provide a QLThumbnailReply that either contains a drawing block or an image file URL.


 @param request An object which contains information about the thumbnail that should be provided. It contains the URL of the file to provide a thumbnail for.
 @param handler Call the completion handler with a QLThumbnailReply if you can provide a thumbnail, or with an NSError if you cannot.
                If an error is passed or reply is nil, no thumbnail will be drawn.
                The handler can be called asynchronously after the method has returned.
 */
- (void)provideThumbnailForFileRequest:(QLFileThumbnailRequest *)request completionHandler:(void (^)(QLThumbnailReply * _Nullable reply, NSError * _Nullable error))handler NS_SWIFT_NAME(provideThumbnail(for:_:));

@end

NS_ASSUME_NONNULL_END
