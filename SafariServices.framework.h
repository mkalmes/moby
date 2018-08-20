// ==========  SafariServices.framework/Headers/SFContentBlockerManager.h
//
//  SFContentBlockerManager.h
//  SafariServices
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

SF_EXTERN NSString * const SFContentBlockerErrorDomain NS_AVAILABLE_IOS(9_0);

typedef NS_ENUM(NSInteger, SFContentBlockerErrorCode) {
    SFContentBlockerNoExtensionFound = 1,
    SFContentBlockerNoAttachmentFound = 2,
    SFContentBlockerLoadingInterrupted = 3,
} NS_ENUM_AVAILABLE_IOS(9_0);

NS_CLASS_AVAILABLE_IOS(9_0)
@interface SFContentBlockerManager : NSObject

+ (void)reloadContentBlockerWithIdentifier:(NSString *)identifier completionHandler:(void (^__nullable)(NSError *__nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
// ==========  SafariServices.framework/Headers/SafariServices.h
//
//  SafariServices.h
//  SafariServices
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <SafariServices/SFContentBlockerManager.h>
#import <SafariServices/SFFoundation.h>
#import <SafariServices/SFSafariViewController.h>
#import <SafariServices/SSReadingList.h>
// ==========  SafariServices.framework/Headers/SSReadingList.h
//
//  SSReadingList.h
//  SafariServices
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
    @class SSReadingList
    Provides an interface for adding to a user's Reading List.
*/
NS_CLASS_AVAILABLE_IOS(7_0)
@interface SSReadingList : NSObject

/*!
    @method defaultReadingList
    @result Returns a pointer to a shared instance of SSReadingList, or nil if access to Reading List is not permitted.
    @discussion This class method to obtain the instance of SSReadingList should used instead of direct alloc and init.  
*/
+ (nullable SSReadingList *)defaultReadingList;

- (instancetype)init NS_UNAVAILABLE;

/*!
    @method supportsURL:
    @abstract Determines if the provided URL can be added to Reading List.
    @param URL The URL to be tested for Reading List support.
    @result Returns YES if the URL is supported by Reading List, NO if not.
*/
+ (BOOL)supportsURL:(NSURL *)URL;

/*!
    @method addReadingListItemWithURL:title:previewText:error:
    @abstract Adds an item to the Reading List.
    @param URL The URL of the item.
    @param title The title string of the item, or nil.
    @param previewText A string shown as detail text for the item, or nil.
    @param error Describes the error that occurred.
    @result Returns YES if the item was added, otherwise returns NO and error param is set.
    @discussion Only URLs with http:// or https:// schemes are supported by Reading List.
*/
- (BOOL)addReadingListItemWithURL:(NSURL *)URL title:(nullable NSString *)title previewText:(nullable NSString *)previewText error:(NSError **)error NS_AVAILABLE_IOS(7_0);

@end

// domain for NSError
SF_EXTERN NSString *const SSReadingListErrorDomain NS_AVAILABLE_IOS(7_0);

typedef NS_ENUM(NSInteger, SSReadingListErrorCode) {
    SSReadingListErrorURLSchemeNotAllowed = 1,
} NS_ENUM_AVAILABLE_IOS(7_0);

NS_ASSUME_NONNULL_END
// ==========  SafariServices.framework/Headers/SFFoundation.h
//
//  SFFoundation.h
//  SafariServices
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#ifdef __cplusplus
#define SF_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define SF_EXTERN extern __attribute__((visibility ("default")))
#endif
// ==========  SafariServices.framework/Headers/SFSafariViewController.h
//
//  SFSafariViewController.h
//  SafariServices
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol SFSafariViewControllerDelegate;

/*!
 @class SFSafariViewController
 A view controller for displaying web content in a Safari-like interface with some of Safari’s features. The
 web content in SFSafariViewController shares cookie and website data with web content opened in Safari.
 */
NS_CLASS_AVAILABLE_IOS(9_0)
@interface SFSafariViewController : UIViewController

/*! @abstract The view controller's delegate */
@property (nonatomic, weak, nullable) id<SFSafariViewControllerDelegate> delegate;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_UNAVAILABLE;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;

/*! @abstract Returns a view controller that loads a URL.
    @param URL, the URL to navigate to.
    @param entersReaderIfAvailable indicates if the Safari Reader version of content should be shown automatically
    when Safari Reader is available on a web page
 */
- (instancetype)initWithURL:(NSURL *)URL entersReaderIfAvailable:(BOOL)entersReaderIfAvailable NS_DESIGNATED_INITIALIZER;

/*! @abstract Returns a view controller that loads a URL.
    @param URL, the URL to navigate to.
 */
- (instancetype)initWithURL:(NSURL *)URL;

@end

NS_AVAILABLE_IOS(9_0)
@protocol SFSafariViewControllerDelegate <NSObject>
@optional

/*! @abstract Called when the view controller is about to show UIActivityViewController after the user taps the action button.
    @param URL, the URL of the web page.
    @param title, the title of the web page.
    @result Returns an array of UIActivity instances that will be appended to UIActivityViewController.
 */
- (NSArray<UIActivity *> *)safariViewController:(SFSafariViewController *)controller activityItemsForURL:(NSURL *)URL title:(nullable NSString *)title;

/*! @abstract Delegate callback called when the user taps the Done button. Upon this call, the view controller is dismissed modally. */
- (void)safariViewControllerDidFinish:(SFSafariViewController *)controller;

/*! @abstract Invoked when the initial URL load is complete.
    @param success YES if loading completed successfully, NO if loading failed.
    @discussion This method is invoked when SFSafariViewController completes the loading of the URL that you pass
    to its initializer. It is not invoked for any subsequent page loads in the same SFSafariViewController instance.
 */
- (void)safariViewController:(SFSafariViewController *)controller didCompleteInitialLoad:(BOOL)didLoadSuccessfully;

@end

NS_ASSUME_NONNULL_END
