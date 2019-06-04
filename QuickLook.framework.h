// ==========  QuickLook.framework/Headers/QuickLook.h
//
//  QuickLook.h
//  QuickLook
//
//  Copyright (c) 2008-2015 Apple Inc. All rights reserved.
//


#if !defined(__QUICKLOOK_QUICKLOOK__)
#define __QUICKLOOK_QUICKLOOK__

#include <CoreFoundation/CoreFoundation.h>
#include <QuickLook/QLBase.h>

#if __OBJC__
#import <QuickLook/QLPreviewController.h>
#import <QuickLook/QLPreviewItem.h>
#import <QuickLook/QLPreviewingController.h>
#import <QuickLook/QLThumbnailProvider.h>
#import <QuickLook/QLThumbnailRequest.h>
#import <QuickLook/QLThumbnailReply.h>
#endif

#endif
// ==========  QuickLook.framework/Headers/QLThumbnailRequest.h
//
//  QLPreviewingController.h
//  Mobile Quick Look
//
//  Copyright 2016 Apple Inc. All rights reserved.
//

#if !defined(USE_PUBLIC_QUICKLOOK_HEADERS) && __has_include(<QuickLookThumbnailing/QLThumbnailRequest.h>)
#import <QuickLookThumbnailing/QLThumbnailRequest.h>
#else

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <QuickLook/QLBase.h>


NS_ASSUME_NONNULL_BEGIN

/**
 @abstract This class contains information about the thumbnail that should be provided.
 */
NS_CLASS_AVAILABLE_IOS(11_0) QL_EXPORT @interface QLFileThumbnailRequest : NSObject

@property (nonatomic, readonly) CGSize maximumSize;
@property (nonatomic, readonly) CGSize minimumSize;
@property (nonatomic, readonly) CGFloat scale;
@property (nonatomic, copy, readonly) NSURL* fileURL;

@end

NS_ASSUME_NONNULL_END

#endif
// ==========  QuickLook.framework/Headers/QLBase.h
/*
 *  QLBase.h
 *  Quick Look
 *
 *  Copyright 2007 Apple Inc.
 *  All rights reserved.
 *
 */

#if !defined(__QUICKLOOK_QLBASE__)
#define __QUICKLOOK_QLBASE__

#ifdef __cplusplus
    #define QL_EXTERN_C_BEGIN extern "C" {
    #define QL_EXTERN_C_END }
#else
    #define QL_EXTERN_C_BEGIN
    #define QL_EXTERN_C_END
#endif

#define QL_EXPORT_OSX
#define QL_EXPORT __attribute__((visibility("default")))
#define QL_PRIVATE_EXPORT __attribute__((visibility("hidden")))
#define QL_INLINE static __inline__ __attribute__((always_inline))
#define QL_NOINLINE __attribute__((noinline))
#define QL_DEPRECATED __attribute__((deprecated))
#define QL_FORMAT_ARG(F, A) __attribute__((format(CFString, F, A)))

#endif
// ==========  QuickLook.framework/Headers/QLPreviewingController.h
//
//  QLPreviewingController.h
//  Mobile Quick Look
//
//  Copyright 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuickLook/QLBase.h>


NS_ASSUME_NONNULL_BEGIN

/**
 The controller that implements the QLPreviewingController protocol must at least implement one of the two following methods:
 -[QLPreviewingController preparePreviewOfSearchableItemWithIdentifier:queryString:completionHandler:], to generate previews for Spotlight searchable items.
 -[QLPreviewingController preparePreviewOfFileAtURL:completionHandler:], to generate previews for file URLs.
 */
QL_EXPORT @protocol QLPreviewingController <NSObject>

@optional

/**
 @abstract
 Use this method to prepare the content of the view controller with the data that the searchable item represents.
 
 @discussion
 This method will be called only once. It will be called in the main thread before presenting the view controller.
 Heavy work potentially blocking the main thread should be avoided in this method.
 
 @param identifier The identifier of the CSSearchableItem the user interacted with in Spotlight.
 @param queryString The query string the user entered in Spotlight before interacting with the CSSearchableItem.
 @param handler The completion handler should be called whenever the view is ready to be displayed. A loading spinner will be shown until the handler is called.
 It can be called asynchronously after the method has returned.
 */
- (void)preparePreviewOfSearchableItemWithIdentifier:(NSString *)identifier queryString:(NSString * _Nullable)queryString completionHandler:(void (^)(NSError * _Nullable))handler NS_SWIFT_NAME(preparePreviewOfSearchableItem(identifier:queryString:completionHandler:));

/**
 @abstract
 Use this method to prepare the content of the view controller with the given file URL.

 @discussion
 This method will be called only once. It will be called in the main thread before presenting the view controller.
 Heavy work potentially blocking the main thread should be avoided in this method.
 
 @param url The URL of the file the user is about to preview.
 @param handler The completion handler should be called whenever the view is ready to be displayed. A loading spinner will be shown until the handler is called.
 It can be called asynchronously after the method has returned.
 */
- (void)preparePreviewOfFileAtURL:(NSURL *)url completionHandler:(void (^)(NSError * _Nullable))handler NS_SWIFT_NAME(preparePreviewOfFile(at:completionHandler:));

@end

NS_ASSUME_NONNULL_END
// ==========  QuickLook.framework/Headers/QLPreviewItem.h
//
//  QLPreviewItem.h
//  Quick Look
//
//  Copyright 2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#include <QuickLook/QLBase.h>

/*!
 * @abstract The QLPreviewItem protocol declares the methods that a QLPreviewController instance uses to access the contents of a given item.
 */
QL_EXPORT @protocol QLPreviewItem <NSObject>

@required

/*!
 * @abstract The URL of the item to preview.
 * @discussion The URL must be a file URL.
 */
@property(readonly, nullable, nonatomic) NSURL * previewItemURL;

@optional

/*!
 * @abstract The item's title this will be used as apparent item title.
 * @discussion The title replaces the default item display name. This property is optional.
 */
@property(readonly, nullable, nonatomic) NSString * previewItemTitle;


@end

/*!
 * @abstract This category makes NSURL instances as suitable items for the Preview Controller.
 */
@interface NSURL (QLPreviewConvenienceAdditions) <QLPreviewItem>
@end
// ==========  QuickLook.framework/Headers/QLPreviewController.h
//
//  QLPreviewController.h
//  Mobile Quick Look
//
//  Copyright 2008 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuickLook/QLBase.h>

@protocol QLPreviewItem;
@protocol QLPreviewControllerDelegate;
@protocol QLPreviewControllerDataSource;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(4_0) QL_EXPORT
@interface QLPreviewController : UIViewController

/*!
 * @abstract Returns YES if QLPreviewController can display this preview item.
 */
+ (BOOL)canPreviewItem:(id <QLPreviewItem>)item;

/*
 * Acessing the previewed items
 */

/*!
 * @abstract The Preview Panel data source.
 */
@property(nonatomic, weak, nullable) id <QLPreviewControllerDataSource> dataSource;

/*!
 * @abstract Asks the Preview Controller to reload its data from its data source.
 * @discussion This method does not refresh the visible item if it has not changed.
 */
- (void)reloadData;

/*!
 * @abstract Asks the Preview Controller to recompute the preview of the currently previewed item.
 */
- (void)refreshCurrentPreviewItem;

/*!
 * @abstract The index of the currently previewed item in the preview panel or NSNotFound if there is none.
 */
@property NSInteger currentPreviewItemIndex;

/*!
 * @abstract The currently previewed item in the preview panel or nil if there is none.
 */
@property(readonly, nullable) id <QLPreviewItem> currentPreviewItem;



/*
 * Setting the delegate
 */

/*!
 * @abstract The Preview Controller delegate.
 * @discussion Should implement the <QLPreviewControllerDelegate> protocol
 */
@property(nonatomic, weak, nullable) id <QLPreviewControllerDelegate> delegate;

@end

/*!
 * @abstract The QLPreviewControllerDataSource protocol declares the methods that the Preview Controller uses to access the contents of its data source object.
 */
QL_EXPORT @protocol QLPreviewControllerDataSource

@required

/*!
 * @abstract Returns the number of items that the preview controller should preview.
 * @param controller The Preview Controller.
 * @result The number of items.
 */
- (NSInteger)numberOfPreviewItemsInPreviewController:(QLPreviewController *)controller;

/*!
 * @abstract Returns the item that the preview controller should preview.
 * @param panel The Preview Controller.
 * @param index The index of the item to preview.
 * @result An item conforming to the QLPreviewItem protocol.
 */
- (id <QLPreviewItem>)previewController:(QLPreviewController *)controller previewItemAtIndex:(NSInteger)index;

@end

// QLPreviewItem editing support
typedef NS_ENUM(NSInteger, QLPreviewItemEditingMode) {
    QLPreviewItemEditingModeDisabled = 0,                              // The item won't be editable.
    QLPreviewItemEditingModeUpdateContents,                            // If QLPreviewController supports editing the file type of the preview item, it will automatically overwrite its contents with the edited version of the user.
    QLPreviewItemEditingModeCreateCopy                                 // If QLPreviewController supports editing the file type of the preview item, it will notify its delegate that an edited copy was created. The original document will be unchanged.
} API_AVAILABLE(ios(13.0));

QL_EXPORT @protocol QLPreviewControllerDelegate <NSObject>
@optional


/*!
 * @abstract Invoked before the preview controller is closed.
 */
- (void)previewControllerWillDismiss:(QLPreviewController *)controller;

/*!
 * @abstract Invoked after the preview controller is closed.
 */
- (void)previewControllerDidDismiss:(QLPreviewController *)controller;

/*!
 * @abstract Invoked by the preview controller before trying to open an URL tapped in the preview.
 * @result Returns NO to prevent the preview controller from calling -[UIApplication openURL:] on url.
 * @discussion If not implemented, defaults is YES.
 */
- (BOOL)previewController:(QLPreviewController *)controller shouldOpenURL:(NSURL *)url forPreviewItem:(id <QLPreviewItem>)item;

/*!
 * @abstract Invoked when the preview controller is about to be presented full screen or dismissed from full screen, to provide a zoom effect.
 * @discussion Return the origin of the zoom. It should be relative to view, or screen based if view is not set. The controller will fade in/out if the rect is CGRectZero.
 */
- (CGRect)previewController:(QLPreviewController *)controller frameForPreviewItem:(id <QLPreviewItem>)item inSourceView:(UIView * _Nullable * __nonnull)view;

/*!
 * @abstract Invoked when the preview controller is about to be presented full screen or dismissed from full screen, to provide a smooth transition when zooming.
 * @param contentRect The rect within the image that actually represents the content of the document. For example, for icons the actual rect is generally smaller than the icon itself.
 * @discussion Return an image the controller will crossfade with when zooming. You can specify the actual "document" content rect in the image in contentRect.
 */
- (UIImage * _Nullable)previewController:(QLPreviewController *)controller transitionImageForPreviewItem:(id <QLPreviewItem>)item contentRect:(CGRect *)contentRect;

/*!
 * @abstract Invoked when the preview controller is about to be presented full screen or dismissed from full screen, to provide a smooth transition when zooming.
 * @discussion  Return the view that will crossfade with the preview.
 */
- (UIView* _Nullable)previewController:(QLPreviewController *)controller transitionViewForPreviewItem:(id <QLPreviewItem>)item NS_AVAILABLE_IOS(10_0);

/*!
 * @abstract Invoked when the preview controller is loading its data. It is called for each preview item passed to the data source of the preview controller.
 * @discussion The preview controller does not offer the users to edit previews by default, but it is possible to activate this functionality if its delegate either allows it to overwrite the contents of the preview item, or if it takes care of the updated version of the preview item by implementing previewController:didSaveEditedCopyOfPreviewItem:atURL:.
   If the returned value is QLPreviewItemEditingModeUpdateContents and the previewController:didSaveEditedCopyOfPreviewItem:atURL: delegate method is implemented, the preview controller will overwrite the contents of the preview item if this is possible. If not (because the new version of the preview item is of a different type for instance), it will instead call previewController:didSaveEditedCopyOfPreviewItem:atURL:.
 * @param previewItem The preview item for which the controller needs to know how its delegate wants edited versions of the preview item to be handled.
 * @result A value indicating how the preview controller should handle edited versions of the preview item.
 */
- (QLPreviewItemEditingMode)previewController:(QLPreviewController *)controller editingModeForPreviewItem:(id <QLPreviewItem>)previewItem API_AVAILABLE(ios(13.0));

/*!
 * @abstract Called after the preview controller has successfully overwritten the contents of the file at previewItemURL for the preview item with the edited version of the users.
 * @discussion May be called multiple times in a row when overwriting the preview item with the successive edited versions of the preview item (whenever the users save the changes).
 */
- (void)previewController:(QLPreviewController *)controller didUpdateContentsOfPreviewItem:(id<QLPreviewItem>)previewItem API_AVAILABLE(ios(13.0));

/*!
 * @abstract This method will be called with an edited copy of the contents of the preview item at previewItemURL.
 * @discussion This can be called after the users save changes in the following cases:
 
               - If the returned editing mode of the preview item is QLPreviewItemEditingModeCreateCopy.
 
               - If the returned editing mode of the preview item is QLPreviewItemEditingModeUpdateContents and its previewItemURL could not be successfully overwritten. In this case, modifiedContentsURL will point to a temporary file on disk containing the edited copy.
 
               - If the returned editing mode of the preview item is QLPreviewItemEditingModeUpdateContents and its content type and the content type of the edited version don't match.
                 This means that the file type of modifiedContentsURL may be different from the one of the preview item.
 
               Note that this may be called multiple times in a row with the successive edited versions of the preview item (whenever the users save the changes).
 * @param modifiedContentsURL NSURL of a temporary file on disk containing the edited copy of the preview item.
 */
- (void)previewController:(QLPreviewController *)controller didSaveEditedCopyOfPreviewItem:(id <QLPreviewItem>)previewItem atURL:(NSURL *)modifiedContentsURL API_AVAILABLE(ios(13.0));

@end

NS_ASSUME_NONNULL_END

// ==========  QuickLook.framework/Headers/QLThumbnailReply.h
//
//  QLThumbnailReply.h
//  Mobile Quick Look
//
//  Copyright 2016 Apple Inc. All rights reserved.
//

#if !defined(USE_PUBLIC_QUICKLOOK_HEADERS) && __has_include(<QuickLookThumbnailing/QLThumbnailReply.h>)
#import <QuickLookThumbnailing/QLThumbnailReply.h>
#else

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <QuickLook/QLBase.h>


NS_ASSUME_NONNULL_BEGIN

/**
 To provide a thumbnail for a request, you have to return a QLThumbnailReply object.
 
 @discussion To provide a thumbnail, you have two options:
 1. Draw the thumbnail, by providing a QLThumbnailReply created with a drawing block.
 2. Pass the thumbnail file URL, by providing a QLThumbnailReply created with a file URL.
 */
NS_CLASS_AVAILABLE_IOS(11_0) QL_EXPORT @interface QLThumbnailReply : NSObject

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
 You can create a reply with a drawing block that will draw into the current context with the coordinate system of UIKit.
 
 @param contextSize The desired size of the context that will be passed to the drawing block.
 It should be as close as possible to the maximumSize of the QLFileThumbnailRequest and it has to be greater than or equal to its minimumSize.
 
 Ideally, at least either contextSize's width matches maximumSize's width or contextSize's height matches maximumSize's height.
 The context size will be scaled to QLFileThumbnailRequest's scale value (if you pass (x, y), the size of the context will be (scale * x, scale * y)).
 @param drawingBlock A block that draws the thumbnail into the current context which you can access via UIGraphicsGetCurrentContext().
 It is a context of type CGBitmapContext, set up to be used with the coordinate system of UIKit.
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

#endif
// ==========  QuickLook.framework/Headers/QLThumbnailProvider.h
//
//  QLThumbnailProvider.h
//  Mobile Quick Look
//
//  Copyright 2016 Apple Inc. All rights reserved.
//

#if !defined(USE_PUBLIC_QUICKLOOK_HEADERS) && __has_include(<QuickLookThumbnailing/QLThumbnailProvider.h>)
#import <QuickLookThumbnailing/QLThumbnailProvider.h>
#else

#import <Foundation/Foundation.h>
#import <QuickLook/QLBase.h>


NS_ASSUME_NONNULL_BEGIN

@class QLFileThumbnailRequest, QLThumbnailReply;

NS_CLASS_AVAILABLE_IOS(11_0) QL_EXPORT @interface QLThumbnailProvider : NSObject

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

#endif
