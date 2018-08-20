// ==========  QuickLook.framework/Headers/QuickLook.h
//
//  QuickLook.h
//  Quick Look
//
//  Copyright 2008 Apple Inc.
//  All rights reserved.
//
 
#if !defined(__QUICKLOOK_QUICKLOOK__)
#define __QUICKLOOK_QUICKLOOK__

#include <CoreFoundation/CoreFoundation.h>
#include <QuickLook/QLBase.h>


#if __OBJC__
#import <QuickLook/QLPreviewController.h>
#import <QuickLook/QLPreviewItem.h>
#endif


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
// ==========  QuickLook.framework/Headers/QLPreviewItem.h
//
//  QLPreviewItem.h
//  Quick Look
//
//  Copyright 2008 Apple Inc. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <QuickLook/QLBase.h>

/*!
 * @abstract The QLPreviewItem protocol declares the methods that a QLPreviewController  instance uses to access the contents of a given item.
 */
QL_EXPORT @protocol QLPreviewItem <NSObject>

@required

/*!
 * @abstract The URL of the item to preview.
 * @discussion The URL must be a file URL. 
 */
@property(readonly, nonnull, nonatomic) NSURL * previewItemURL;

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

@class QLPreviewControllerReserved;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(NA, 4_0) QL_EXPORT
@interface QLPreviewController : UIViewController {
    QLPreviewControllerReserved * _reserved;
}

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
@property(weak, nullable) id <QLPreviewControllerDataSource> dataSource;

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
@property(weak, nullable) id <QLPreviewControllerDelegate> delegate;

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
- (CGRect)previewController:(QLPreviewController *)controller frameForPreviewItem:(id <QLPreviewItem>)item inSourceView:(UIView * __nullable * __nonnull)view;

/*!
 * @abstract Invoked when the preview controller is about to be presented full screen or dismissed from full screen, to provide a smooth transition when zooming.
 * @param contentRect The rect within the image that actually represents the content of the document. For example, for icons the actual rect is generally smaller than the icon itself.
 * @discussion Return an image the controller will crossfade with when zooming. You can specify the actual "document" content rect in the image in contentRect.
 */
- (UIImage *)previewController:(QLPreviewController *)controller transitionImageForPreviewItem:(id <QLPreviewItem>)item contentRect:(CGRect *)contentRect;

@end

NS_ASSUME_NONNULL_END

