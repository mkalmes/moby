// ==========  SafariServices.framework/Headers/SFContentBlockerManager.h
//
//  SFContentBlockerManager.h
//  SafariServices
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SafariServices/SFError.h>
#import <SafariServices/SFFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFContentBlockerState;

SF_EXTERN NSString * const SFContentBlockerErrorDomain API_DEPRECATED_WITH_REPLACEMENT("SFErrorDomain", ios(9.0, 10.0)) API_UNAVAILABLE(uikitformac);

typedef NS_ENUM(NSInteger, SFContentBlockerErrorCode) {
    SFContentBlockerNoExtensionFound API_DEPRECATED_WITH_REPLACEMENT("SFErrorNoExtensionFound", ios(9.0, 10.0)) = SFErrorNoExtensionFound,
    SFContentBlockerNoAttachmentFound API_DEPRECATED_WITH_REPLACEMENT("SFErrorNoAttachmentFound", ios(9.0, 10.0)) = SFErrorNoAttachmentFound,
    SFContentBlockerLoadingInterrupted API_DEPRECATED_WITH_REPLACEMENT("SFErrorLoadingInterrupted", ios(9.0, 10.0)) = SFErrorLoadingInterrupted,
} API_DEPRECATED_WITH_REPLACEMENT("SFErrorCode", ios(9.0, 10.0)) API_UNAVAILABLE(uikitformac);

SF_EXTERN API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(uikitformac)
@interface SFContentBlockerManager : NSObject

+ (void)reloadContentBlockerWithIdentifier:(NSString *)identifier completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler;
+ (void)getStateOfContentBlockerWithIdentifier:(NSString *)identifier completionHandler:(void (^)(SFContentBlockerState *_Nullable state, NSError *_Nullable error))completionHandler API_AVAILABLE(ios(10.0));

@end

NS_ASSUME_NONNULL_END
// ==========  SafariServices.framework/Headers/SFContentBlockerState.h
//
//  SFContentBlockerState.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SafariServices/SFFoundation.h>

SF_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(uikitformac)
@interface SFContentBlockerState : NSObject

@property (nonatomic, readonly, getter=isEnabled) BOOL enabled;

@end
// ==========  SafariServices.framework/Headers/SafariServices.h
//
//  SafariServices.h
//  SafariServices
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <SafariServices/SFAuthenticationSession.h>
#import <SafariServices/SFContentBlockerManager.h>
#import <SafariServices/SFContentBlockerState.h>
#import <SafariServices/SFError.h>
#import <SafariServices/SFFoundation.h>
#import <SafariServices/SFSafariViewController.h>
#import <SafariServices/SFSafariViewControllerConfiguration.h>
#import <SafariServices/SSReadingList.h>
// ==========  SafariServices.framework/Headers/SSReadingList.h
//
//  SSReadingList.h
//  SafariServices
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SafariServices/SFFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
    @class SSReadingList
    Provides an interface for adding to a user's Reading List.
*/
SF_EXTERN API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(uikitformac)
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
- (BOOL)addReadingListItemWithURL:(NSURL *)URL title:(nullable NSString *)title previewText:(nullable NSString *)previewText error:(NSError **)error;

@end

// domain for NSError
SF_EXTERN NSString * const SSReadingListErrorDomain API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(uikitformac);

typedef NS_ENUM(NSInteger, SSReadingListErrorCode) {
    SSReadingListErrorURLSchemeNotAllowed = 1,
} API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(uikitformac);

NS_ASSUME_NONNULL_END
// ==========  SafariServices.framework/Headers/SFError.h
//
//  SFError.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SafariServices/SFFoundation.h>

SF_EXTERN NSString * const SFErrorDomain API_AVAILABLE(ios(10.0));

typedef NS_ENUM(NSInteger, SFErrorCode) {
    SFErrorNoExtensionFound = 1,
    SFErrorNoAttachmentFound = 2,
    SFErrorLoadingInterrupted = 3,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(uikitformac);
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

@class SFSafariViewControllerConfiguration;
@protocol SFSafariViewControllerDelegate;

typedef NS_ENUM(NSInteger, SFSafariViewControllerDismissButtonStyle) {
    SFSafariViewControllerDismissButtonStyleDone,
    SFSafariViewControllerDismissButtonStyleClose,
    SFSafariViewControllerDismissButtonStyleCancel,
} API_AVAILABLE(ios(11.0)) NS_SWIFT_NAME(SFSafariViewController.DismissButtonStyle);

/*!
 @class SFSafariViewController
 A view controller for displaying web content in a Safari-like interface with some of Safari’s features.
 */
SF_EXTERN API_AVAILABLE(ios(9.0))
@interface SFSafariViewController : UIViewController

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_UNAVAILABLE;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;

/*! @abstract Returns a view controller that loads a URL.
    @param URL the initial URL to navigate to. Only supports initial URLs with http:// or https:// schemes.
    @param configuration the configuration for the new view controller.
    @discussion This is a designated initializer. You can use
    @link -initWithURL: @/link to initialize an instance with the default configuration. Mutating the configuration after invoking the initializer has no effect on the view controller.
*/
- (instancetype)initWithURL:(NSURL *)URL configuration:(SFSafariViewControllerConfiguration *)configuration NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(11.0));

/*! @abstract Returns a view controller that loads a URL.
    @param URL the initial URL to navigate to. Only supports initial URLs with http:// or https:// schemes.
    @param entersReaderIfAvailable indicates if the Safari Reader version of content should be shown automatically
    when Safari Reader is available on a web page.
 */
- (instancetype)initWithURL:(NSURL *)URL entersReaderIfAvailable:(BOOL)entersReaderIfAvailable NS_DESIGNATED_INITIALIZER API_DEPRECATED_WITH_REPLACEMENT("-initWithURL:configuration:", ios(9.0, 11.0));

/*! @abstract Returns a view controller that loads a URL.
    @param URL the initial URL to navigate to. Only supports initial URLs with http:// or https:// schemes.
 */
- (instancetype)initWithURL:(NSURL *)URL;

/*! @abstract The view controller's delegate. */
@property (nonatomic, weak, nullable) id <SFSafariViewControllerDelegate> delegate;

/*! @abstract A copy of the configuration with which the view controller was
        initialized. */
@property (nonatomic, readonly, copy) SFSafariViewControllerConfiguration *configuration API_AVAILABLE(ios(11.0));

/*! @abstract The preferred color to tint the background of the navigation bar and toolbar. If SFSafariViewController is in Private
    Browsing mode or is displaying an anti-phishing warning page, this color will be ignored. Changes made after the view controller
    has been presented will not be reflected.
 */
@property (nonatomic, nullable) UIColor *preferredBarTintColor API_AVAILABLE(ios(10.0));

/*! @abstract The preferred color to tint the control buttons on the navigation bar and toolbar. If SFSafariViewController is in Private
    Browsing mode or is displaying an anti-phishing warning page, this color will be ignored. Changes made after the view controller
    has been presented will not be reflected.
 */
@property (nonatomic, nullable) UIColor *preferredControlTintColor API_AVAILABLE(ios(10.0));

/*! @abstract The style of dismiss button to use in the navigation bar to close SFSafariViewController.
    The default value is SFSafariViewControllerDismissButtonStyleDone, which makes the button title the localized
    string "Done". You can use other values such as "Close" to provide consistency with your app. "Cancel" is
    ideal when using SFSafariViewController to log in to an external service. All values will show a string localized
    to the user's locale. Changing this property after SFSafariViewController is presented will animate the change.
 */
@property (nonatomic) SFSafariViewControllerDismissButtonStyle dismissButtonStyle API_AVAILABLE(ios(11.0));

@end

API_AVAILABLE(ios(9.0))
@protocol SFSafariViewControllerDelegate <NSObject>
@optional

/*! @abstract Called when the view controller is about to show UIActivityViewController after the user taps the action button.
    @param URL the URL of the web page.
    @param title the title of the web page.
    @result Returns an array of UIActivity instances that will be appended to UIActivityViewController.
 */
- (NSArray<UIActivity *> *)safariViewController:(SFSafariViewController *)controller activityItemsForURL:(NSURL *)URL title:(nullable NSString *)title;

/*! @abstract Allows you to exclude certain UIActivityTypes from the UIActivityViewController presented when the user taps the action button.
    @discussion Called when the view controller is about to show a UIActivityViewController after the user taps the action button.
    @param URL the URL of the current web page.
    @param title the title of the current web page.
    @result Returns an array of any UIActivityType that you want to be excluded from the UIActivityViewController.
 */
- (NSArray<UIActivityType> *)safariViewController:(SFSafariViewController *)controller excludedActivityTypesForURL:(NSURL *)URL title:(nullable NSString *)title API_AVAILABLE(ios(11.0));

/*! @abstract Delegate callback called when the user taps the Done button. Upon this call, the view controller is dismissed modally. */
- (void)safariViewControllerDidFinish:(SFSafariViewController *)controller;

/*! @abstract Invoked when the initial URL load is complete.
    @param didLoadSuccessfully YES if loading completed successfully, NO if loading failed.
    @discussion This method is invoked when SFSafariViewController completes the loading of the URL that you pass
    to its initializer. It is not invoked for any subsequent page loads in the same SFSafariViewController instance.
 */
- (void)safariViewController:(SFSafariViewController *)controller didCompleteInitialLoad:(BOOL)didLoadSuccessfully;

/*! @abstract Called when the browser is redirected to another URL while loading the initial page.
    @param URL The new URL to which the browser was redirected.
    @discussion This method may be called even after -safariViewController:didCompleteInitialLoad: if
    the web page performs additional redirects without user interaction.
 */
- (void)safariViewController:(SFSafariViewController *)controller initialLoadDidRedirectToURL:(NSURL *)URL API_AVAILABLE(ios(11.0));

@end

NS_ASSUME_NONNULL_END
// ==========  SafariServices.framework/Headers/SFAuthenticationSession.h
//
//  SFAuthenticationSession.h
//  SafariServices
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SafariServices/SFFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/*! @enum SFAuthenticationError
 @abstract Error code of the NSError object passed in by SFAuthenticationCompletionHandler.
 @constant SFAuthenticationErrorCanceledLogin The user has canceled login by cancelling the alert asking for permission to log in to this app, or by dismissing the view controller for loading the authentication webpage.
 */
typedef NS_ENUM(NSInteger, SFAuthenticationError) {
    SFAuthenticationErrorCanceledLogin = 1,
} API_DEPRECATED("Use ASWebAuthenticationSessionErrorCode instead", ios(11.0, 12.0));

SF_EXTERN NSString * const SFAuthenticationErrorDomain API_DEPRECATED_WITH_REPLACEMENT("ASWebAuthenticationSessionErrorDomain", ios(11.0, 12.0));

typedef void (^SFAuthenticationCompletionHandler)(NSURL *_Nullable callbackURL, NSError *_Nullable error) NS_SWIFT_NAME(SFAuthenticationSession.CompletionHandler);

/*!
 @class SFAuthenticationSession
 An SFAuthenticationSession object can be used to authenticate a user with a web service, even if the web service is run by a third party.
 SFAuthenticationSession puts the user in control of whether they want to use their existing logged-in session from Safari. The
 app provides a URL that points to the authentication webpage. The page will be loaded in a secure view controller. From the
 webpage, the user can authenticate herself and grant access to the app. On completion, the service will send a callback URL with
 an authentication token, and this URL will be passed to the app by SFAuthenticationCompletionHandler.

 The callback URL usually has a custom URL scheme. For the app to receive the callback URL, it needs to either register the
 custom URL scheme in its Info.plist, or set the scheme to callbackURLScheme argument in the initializer.

 If the user has already logged into the web service in Safari or other apps via SFAuthenticationSession, it is possible to
 share the existing login information. An alert will be presented to get the user's consent for sharing their existing login
 information. If the user cancels the alert, the session will be canceled, and the completion handler will be called with
 the error code SFAuthenticationErrorCanceledLogin.

 If the user taps Cancel when showing the login webpage for the web service, the session will be canceled, and the completion handler
 will be called with the error code SFAuthenticationErrorCanceledLogin.

 The app can cancel the session by calling -[SFAuthenticationSession cancel]. This will also dismiss the view controller that
 is showing the web service's login page.
 */
SF_EXTERN API_DEPRECATED_WITH_REPLACEMENT("ASWebAuthenticationSession", ios(11.0, 12.0))
@interface SFAuthenticationSession : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*! @abstract Returns a SFAuthenticationSession object.
 @param URL the initial URL pointing to the authentication webpage. Only supports URLs with http:// or https:// schemes.
 @param callbackURLScheme the custom URL scheme that the app expects in the callback URL.
 @param completionHandler the completion handler which is called when the session is completed successfully or canceled by user.
 */
- (instancetype)initWithURL:(NSURL *)URL callbackURLScheme:(nullable NSString *)callbackURLScheme completionHandler:(SFAuthenticationCompletionHandler)completionHandler;

/*! @abstract Starts the SFAuthenticationSession instance after it is instantiated.
 @discussion start can only be called once for an SFAuthenticationSession instance. This also means calling start on a
 canceled session will fail.
 @result Returns YES if the session starts successfully.
 */
- (BOOL)start;

/*! @abstract Cancel an SFAuthenticationSession. If the view controller is already presented to load the webpage for authentication,
 it will be dismissed. Calling cancel on an already canceled session will have no effect.
  */
- (void)cancel;

@end

NS_ASSUME_NONNULL_END
// ==========  SafariServices.framework/Headers/SFSafariViewControllerConfiguration.h
//
//  SFSafariViewControllerConfiguration.h
//  SafariServices
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

SF_EXTERN API_AVAILABLE(ios(11.0))
NS_SWIFT_NAME(SFSafariViewController.Configuration)
@interface SFSafariViewControllerConfiguration : NSObject <NSCopying>

/*! @abstract Indicates if SFSafariViewController should automatically show the Reader version of web pages. This will only
    happen when Safari Reader is available on a web page.
 */
@property (nonatomic) BOOL entersReaderIfAvailable;

/*! @abstract Indicates if SFSafariViewController should enable collapsing of the navigation bar and hiding of the bottom toolbar
    when the user scrolls web content.
    @discussion The default value is YES.
 */
@property (nonatomic) BOOL barCollapsingEnabled;

@end

NS_ASSUME_NONNULL_END
