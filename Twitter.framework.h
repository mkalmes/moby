// ==========  Twitter.framework/Headers/TWRequest.h
//
//  TWRequest.h
//  Twitter
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

// This class has been  deprecated in iOS 6. Please use SLRequest (in the Social framework) instead.

#import <Foundation/Foundation.h>
#import <Social/SLRequest.h>

@class ACAccount;

enum {
    TWRequestMethodGET = SLRequestMethodGET,
    TWRequestMethodPOST = SLRequestMethodPOST,
    TWRequestMethodDELETE = SLRequestMethodDELETE
};

typedef SLRequestMethod TWRequestMethod; // available in iPhone 5.0

// Completion block for performRequestWithHandler. 
typedef SLRequestHandler TWRequestHandler;

NS_DEPRECATED(NA, NA, 5_0, 6_0) __attribute__((visibility("default")))
@interface TWRequest : NSObject

- (id)initWithURL:(NSURL *)url parameters:(NSDictionary *)parameters requestMethod:(TWRequestMethod)requestMethod;

// Optional account information used to authenticate the request. Defaults to nil.
@property (nonatomic, retain) ACAccount *account;

// The request method
@property (nonatomic, readonly) TWRequestMethod requestMethod;

// The request URL
@property (nonatomic, readonly) NSURL *URL;

// The parameters 
@property (nonatomic, readonly) NSDictionary *parameters;

// Specify a named MIME multi-part value. As of version 6.0, if you set parameters,
// the parameters will automatically be added as form data in the multi-part data.
- (void)addMultiPartData:(NSData*)data withName:(NSString*)name type:(NSString*)type; 

// Returns an OAuth compatible NSURLRequest for use with NSURLConnection. 
- (NSURLRequest *)signedURLRequest;

// Issue the request. This block is not guaranteed to be called on any particular thread.
- (void)performRequestWithHandler:(TWRequestHandler)handler;

@end

// ==========  Twitter.framework/Headers/TWTweetComposeViewController.h
//
//  TWTweetComposeViewController.h
//  Twitter
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

// This class has been  deprecated in iOS 6. Please use SLComposeViewController (in the Social framework) instead.

#import <UIKit/UIKit.h>
#import <Social/SLComposeViewController.h>

enum {
    TWTweetComposeViewControllerResultCancelled = SLComposeViewControllerResultCancelled,
    TWTweetComposeViewControllerResultDone = SLComposeViewControllerResultDone
};

typedef SLComposeViewControllerResult TWTweetComposeViewControllerResult;   // available in iPhone 5.0

// Completion handler for TWTweetComposeViewController
typedef SLComposeViewControllerCompletionHandler TWTweetComposeViewControllerCompletionHandler;

// Although you may perform requests on behalf of the user, you cannot append
// text, images, or URLs without the user's knowledge. Hence, you can set the
// initial text and other content before presenting the view to the user, but
// cannot change the content after the user views it. All of the methods used
// to set the content return a Boolean value. The methods return NO if the
// content doesn't fit or if the view was already presented to the user and the
// content can no longer be changed.

NS_DEPRECATED(NA, NA, 5_0, 6_0) __attribute__((visibility("default")))
@interface TWTweetComposeViewController : UIViewController

// Returns if Twitter is accessible and at least one account has been setup.
+ (BOOL)canSendTweet;

// Sets the initial text to be posted. Returns NO if the sheet has already been
// presented to the user. On iOS 6.x, this returns NO if the specified text
// will not fit within the character space currently available; on iOS 7.0 and
// later, you may supply text with a length greater than the service supports,
// and the sheet will allow the user to edit it accordingly.
- (BOOL)setInitialText:(NSString *)text;

// Adds an image to the tweet. Returns NO if the additional image will not fit
// within the character space currently available, or if the sheet has already
// been presented to the user.
- (BOOL)addImage:(UIImage *)image;

// Removes all images from the tweet. Returns NO and does not perform an operation
// if the sheet has already been presented to the user. 
- (BOOL)removeAllImages;

// Adds a URL to the tweet. Returns NO if the additional URL will not fit
// within the character space currently available, or if the sheet has already
// been presented to the user.
- (BOOL)addURL:(NSURL *)url;

// Removes all URLs from the tweet. Returns NO and does not perform an operation
// if the sheet has already been presented to the user.
- (BOOL)removeAllURLs;

// Specify a block to be called when the user is finished. This block is not guaranteed
// to be called on any particular thread. It is cleared after being called.
@property (nonatomic, copy) TWTweetComposeViewControllerCompletionHandler completionHandler;

@end
// ==========  Twitter.framework/Headers/Twitter.h
//
//  Twitter.h
//  Twitter
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Twitter/TWRequest.h>
#if TARGET_OS_IPHONE
#import <Twitter/TWTweetComposeViewController.h>
#endif
