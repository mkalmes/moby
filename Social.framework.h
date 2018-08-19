// ==========  Social.framework/Headers/SLComposeSheetConfigurationItem.h
//
//  SLComposeSheetConfigurationItem.h
//  Social
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Social/SocialDefines.h>
#import <Foundation/Foundation.h>

typedef void (^SLComposeSheetConfigurationItemTapHandler)(void);

// Represents a user-configurable option for the compose session.
// For allowing the user to choose which account to post from, what privacy settings to use, etc.
SOCIAL_CLASS_AVAILABLE(NA, 8_0)
@interface SLComposeSheetConfigurationItem : NSObject

// Designated initializer
- (instancetype)init NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy) NSString *title; // The displayed name of the option.
@property (nonatomic, copy) NSString *value; // The current value/setting of the option.
@property (nonatomic, assign) BOOL valuePending; // Default is NO. set to YES to show a progress indicator. Can be used with a value too.

// Called on the main queue when the configuration item is tapped.
// Your block should not keep a strong reference to either the configuration item, or the SLComposeServiceViewController, otherwise you'll end up with a retain cycle.
@property (nonatomic, copy) SLComposeSheetConfigurationItemTapHandler tapHandler;

@end
// ==========  Social.framework/Headers/SocialDefines.h
//
//  SocialDefines.h
//  Social
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#ifdef __cplusplus
#define SOCIAL_EXTERN		extern "C" __attribute__((visibility ("default")))
#else
#define SOCIAL_EXTERN	    extern __attribute__((visibility ("default")))
#endif

#define SOCIAL_CLASS_AVAILABLE(_desktopIntro, _iphoneIntro) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(_desktopIntro, _iphoneIntro)
#define SOCIAL_CLASS_AVAILABLE_IOS(_iphoneIntro) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE_IOS(_iphoneIntro)
#define SOCIAL_CLASS_AVAILABLE_MAC(_desktopIntro) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE_MAC(_desktopIntro)

// ==========  Social.framework/Headers/SLComposeServiceViewController.h
//
//  SLComposeServiceViewController.h
//  Social
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Social/SocialDefines.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif



#if TARGET_OS_IPHONE
SOCIAL_CLASS_AVAILABLE_IOS(8_0)
@interface SLComposeServiceViewController : UIViewController <UITextViewDelegate>
#else
SOCIAL_CLASS_AVAILABLE_MAC(10_10)
@interface SLComposeServiceViewController : NSViewController <NSTextViewDelegate>
#endif

/*
 Setup
 */

// Called when the sheet presentation animation is finished.
// Subclasses should implement this to begin performing any expensive work (e.g., messaging a server), instead of during initialization, -viewWillAppear, or -viewDidAppear.
- (void)presentationAnimationDidFinish;


/*
 Sheet Content
 
 NOTE: Attachments (e.g., links, images, videos) and initial text are accessible via the view controller's extensionContext.
 */

// The textView displaying the (editable) text content on the sheet. When it's time to post, grab self.textView.text.
// SLComposeServiceViewController creates textView in -loadView and sets itself to be the textView's delegate.
#if TARGET_OS_IPHONE
@property (readonly, nonatomic) UITextView *textView;
#else
@property (readonly) NSTextView *textView;
#endif

// Convenience. This returns the current text from the textView.
@property (readonly, NS_NONATOMIC_IOSONLY) NSString *contentText;

// When textView is empty, this string is displayed instead.
// NOTE: This uses the iOS naming convention: "placeholder" vs. "placeholderString" on OS X.
@property (copy, NS_NONATOMIC_IOSONLY) NSString *placeholder;


/*
 Posting & Canceling
 */

// Called after the post animation has finished (in response to the user selecting the Post button).
// The default implementation calls the extensionContext's -completeRequestReturningItems:completionHandler: method with nil.
// Subclasses must override this in order to peform the post, based on contentText and any attachments.
// Subclasses may call super in order to leverage the default completion behavior; if a subclass does not call super, it must call extensionContext's completion method manually.
- (void)didSelectPost;

// Called after the cancel animation has finished (in response to the user selecting the Cancel button, or someone calling -cancel).
// The default implementation calls the extensionContext's -cancelRequestWithError: method with an NSError/NSUserCancelledError.
// Subclasses may override this in order to customize the extensionContext completion.
- (void)didSelectCancel;

// Triggers an animated dismissal of the sheet, and then calls -didSelectCancel.
// Subclasses do not typically need to call this manually, but may choose to in response to a catastrophic failure during the user's interaction with the sheet.
// Subclasses should not need to override this.
- (void)cancel;


/*
 Sheet Content Validation
 */

// Called automatically after each text change to help determine the enable state of the Post button, and to give the subclass a chance to update charactersRemaining.
// Defaults to YES.
// Subclasses should override this, and return whether contentText and attachments are currently valid for posting.
- (BOOL)isContentValid;

// Calls -isContentValid immediately, performs other internal validation, then updates the enable state of the Post button appropriately.
// Subclasses should call this whenever they change data used as part of validity checking in their implementation of -isContentValid.
- (void)validateContent;

// Set/change this to something non-nil to cause the character count view to appear/redraw. This is useful for services that have a character count limit on their posts. Defaults to nil.
@property (strong, NS_NONATOMIC_IOSONLY) NSNumber *charactersRemaining;



#if TARGET_OS_IPHONE
/*
 Configuration Item Support (account pickers, privacy selection, location, etc.)
 */

// Subclasses should implement this, and return an array of SLComposeSheetConfigurationItem instances, if if needs to display configuration items in the sheet. Defaults to nil.
- (NSArray *)configurationItems;

// Forces a reload of the configuration items table.
// This is typically only necessary for subclasses that determine their configuration items in a deferred manner (for example, in -presentationAnimationDidFinish).
// You do not need to call this after changing a configuration item property; the base class detects and reacts to that automatically.
- (void)reloadConfigurationItems;

// Presents a configuration view controller. Typically called from a configuration item's tapHandler. Only one configuration view controller is allowed at a time.
// The pushed view controller should set preferredContentSize appropriately. SLComposeServiceViewController observes changes to that property and animates sheet size changes as necessary.
- (void)pushConfigurationViewController:(UIViewController *)viewController;

// Dismisses the current configuration view controller.
- (void)popConfigurationViewController;
#endif


#if TARGET_OS_IPHONE
/*
 Custom Preview
 */

// Called when it's time to create a view suitable for previewing the attachments on the extensionContext.
// Defaults to returning a UIView instance appropriate to the set of attachments in the extensionContext, or nil if a preview is unneccessary for the extensionContext.
// Subclasses can override this to supply a preview view of their own choosing for the set of attachments on the extensionContext.
- (UIView *)loadPreviewView;
#endif


#if TARGET_OS_IPHONE
/*
 Text Auto Completion (mentions)
 */

// A view controller whose view replaces the configuration item table, sitting just below the text view. Defaults to nil.
// Set this to a non-nil view controller to implement a mentions picker or something similar. The view controller should set preferredContentSize appropriately. SLComposeServiceViewController observes changes to that property and animates sheet size changes as necessary.
// Set it to nil to remove your view controller, thus restoring the configuration item table.
// SLComposeServiceViewController animates the addition/removal of the view controller's view, as appropriate.
@property (strong, NS_NONATOMIC_IOSONLY) UIViewController *autoCompletionViewController;
#endif


@end


// ==========  Social.framework/Headers/Social.h
//
//  Social.h
//  Social
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Social/SLServiceTypes.h>
#import <Social/SLRequest.h>
#import <Social/SLComposeServiceViewController.h>
#if TARGET_OS_IPHONE
#import <Social/SLComposeViewController.h>
#import <Social/SLComposeSheetConfigurationItem.h>
#endif
// ==========  Social.framework/Headers/SLComposeViewController.h
//
//  SLComposeViewController.h
//  Social
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Social/SocialDefines.h>

typedef NS_ENUM(NSInteger, SLComposeViewControllerResult) {
    SLComposeViewControllerResultCancelled,
    SLComposeViewControllerResultDone
};

typedef void (^SLComposeViewControllerCompletionHandler)(SLComposeViewControllerResult result); 

// Although you may perform requests on behalf of the user, you cannot append
// text, images, or URLs without the user's knowledge. Hence, you can set the
// initial text and other content before presenting the view to the user, but
// cannot change the content after the user views it. All of the methods used
// to set the content return a Boolean value. The methods return NO if the
// content doesn't fit or if the view was already presented to the user and the
// content can no longer be changed.

SOCIAL_CLASS_AVAILABLE(NA, 6_0)
@interface SLComposeViewController : UIViewController

+ (BOOL)isAvailableForServiceType:(NSString *)serviceType;

+ (SLComposeViewController *)composeViewControllerForServiceType:(NSString *)serviceType;

@property(nonatomic, readonly) NSString *serviceType;

// Sets the initial text to be posted. Returns NO if the sheet has already been
// presented to the user. On iOS 6.x, this returns NO if the specified text
// will not fit within the character space currently available; on iOS 7.0 and
// later, you may supply text with a length greater than the service supports,
// and the sheet will allow the user to edit it accordingly.
- (BOOL)setInitialText:(NSString *)text;

// Adds an image to the post. Returns NO if the additional image will not fit
// within the character space currently available, or if the sheet has already
// been presented to the user.
- (BOOL)addImage:(UIImage *)image;

// Removes all images from the post. Returns NO and does not perform an operation
// if the sheet has already been presented to the user. 
- (BOOL)removeAllImages;


// Adds a URL to the post. Returns NO if the additional URL will not fit
// within the character space currently available, or if the sheet has already
// been presented to the user.
- (BOOL)addURL:(NSURL *)url;


// Removes all URLs from the post. Returns NO and does not perform an operation
// if the sheet has already been presented to the user.
- (BOOL)removeAllURLs;


// Specify a block to be called when the user is finished. This block is not guaranteed
// to be called on any particular thread. It is cleared after being called.
@property (nonatomic, copy) SLComposeViewControllerCompletionHandler completionHandler;
@end
// ==========  Social.framework/Headers/SLRequest.h
//
//  SLRequest.h
//  Social
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Social/SocialDefines.h>
#import <Social/SLServiceTypes.h>

@class ACAccount;

typedef NS_ENUM(NSInteger, SLRequestMethod)  {
    SLRequestMethodGET,
    SLRequestMethodPOST,
    SLRequestMethodDELETE,
    SLRequestMethodPUT
};


// Completion block for performRequestWithHandler. 
typedef void(^SLRequestHandler)(NSData *responseData, NSHTTPURLResponse *urlResponse, NSError *error);


SOCIAL_CLASS_AVAILABLE(10_8, 6_0)
@interface SLRequest : NSObject

+ (SLRequest *)requestForServiceType:(NSString *)serviceType requestMethod:(SLRequestMethod)requestMethod URL:(NSURL *)url parameters:(NSDictionary *)parameters;

// Optional account information used to authenticate the request. Defaults to nil.
@property (retain, nonatomic) ACAccount *account;

// The request method
@property (readonly, nonatomic) SLRequestMethod requestMethod;

// The request URL
@property (readonly, nonatomic) NSURL *URL;

// The parameters 
@property (readonly, nonatomic) NSDictionary *parameters;

// Specify a named MIME multi-part value. If you set parameters,
// the parameters will automatically be added as form data in the multi-part data.
- (void)addMultipartData:(NSData *)data
                withName:(NSString *)name
                    type:(NSString *)type
                filename:(NSString *)filename;

#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
// DEPRECATED: Please use addMultipartData:withName:type:filename: instead.
- (void)addMultipartData:(NSData *)data
                withName:(NSString *)name
                    type:(NSString*)type __attribute__((deprecated));
#endif

// Returns a NSURLRequest for use with NSURLConnection.
// If an account has been set the returned request is either signed (OAuth1),
// or has the appropriate token set (OAuth2)
- (NSURLRequest *)preparedURLRequest;

// Issue the request. This block is not guaranteed to be called on any particular thread.
- (void)performRequestWithHandler:(SLRequestHandler)handler;

@end


// ==========  Social.framework/Headers/SLServiceTypes.h
//
//  SLServiceTypes.h
//  Social
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Social/SocialDefines.h>

SOCIAL_EXTERN NSString *const SLServiceTypeTwitter NS_DEPRECATED(10_8, 10_13, 6_0, 11_0);
SOCIAL_EXTERN NSString *const SLServiceTypeFacebook NS_DEPRECATED(10_8, 10_13, 6_0, 11_0);
SOCIAL_EXTERN NSString *const SLServiceTypeSinaWeibo NS_DEPRECATED(10_8, 10_13, 6_0, 11_0);
SOCIAL_EXTERN NSString *const SLServiceTypeTencentWeibo NS_DEPRECATED(10_8, 10_13, 6_0, 11_0);
SOCIAL_EXTERN NSString *const SLServiceTypeLinkedIn NS_DEPRECATED(10_8, 10_13, 6_0, 11_0);
