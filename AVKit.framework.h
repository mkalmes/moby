// ==========  AVKit.framework/Headers/AVPlayerViewController.h
/*
	File:  AVPlayerViewController.h
	
	Framework:  AVKit
	
	Copyright 2014-2015 Apple Inc. All rights reserved.
	
 */

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class AVPlayer;
@protocol AVPlayerViewControllerDelegate;

/*!
	@class		AVPlayerViewController
	@abstract	AVPlayerViewController is a subclass of UIViewController that can be used to display the visual content of an AVPlayer object and the standard playback controls.
 */

NS_CLASS_AVAILABLE_IOS(8_0)
@interface AVPlayerViewController : UIViewController

/*!
	@property	player
	@abstract	The player from which to source the media content for the view controller.
 */
@property (nonatomic, strong, nullable) AVPlayer *player;

/*!
	@property	showsPlaybackControls
	@abstract	Whether or not the receiver shows playback controls. Default is YES.
	@discussion	Clients can set this property to NO when they don't want to have any playback controls on top of the visual content (e.g. for a game splash screen).
				This property should not be used to temporarily change the visibility of the playback controls since it will create or destroy UI elements.
 */
@property (nonatomic) BOOL showsPlaybackControls;

/*!
	@property	videoGravity
	@abstract	A string defining how the video is displayed within an AVPlayerLayer bounds rect.
	@discussion	Options are AVLayerVideoGravityResizeAspect, AVLayerVideoGravityResizeAspectFill and AVLayerVideoGravityResize. AVLayerVideoGravityResizeAspect is default.
 */
@property (nonatomic, copy) AVLayerVideoGravity videoGravity;

/*!
	@property	readyForDisplay
	@abstract	Boolean indicating that the first video frame has been made ready for display for the current item of the associated AVPlayer.
 */
@property (nonatomic, readonly, getter = isReadyForDisplay) BOOL readyForDisplay;

/*!
	@property	videoBounds
	@abstract	The current size and position of the video image as displayed within the receiver's view's bounds.
 */
@property (nonatomic, readonly) CGRect videoBounds;

/*!
	@property	contentOverlayView
	@abstract	Use the content overlay view to add additional custom views between the video content and the controls.
 */
@property (nonatomic, readonly, nullable) UIView *contentOverlayView;

/*!
	@property	allowsPictureInPicturePlayback
	@abstract	Whether or not the receiver allows Picture in Picture playback. Default is YES.
 */
@property (nonatomic) BOOL allowsPictureInPicturePlayback NS_AVAILABLE_IOS(9_0);

/*!
	@property	delegate
	@abstract	The receiver's delegate.
 */
@property (nonatomic, weak, nullable) id <AVPlayerViewControllerDelegate> delegate NS_AVAILABLE_IOS(9_0);

@end


/*!
	@protocol	AVPlayerViewControllerDelegate
	@abstract	A protocol for delegates of AVPlayerViewController.
 */

@protocol AVPlayerViewControllerDelegate <NSObject>
@optional

/*!
	@method		playerViewControllerWillStartPictureInPicture:
	@param		playerViewController
				The player view controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture will start.
 */
- (void)playerViewControllerWillStartPictureInPicture:(AVPlayerViewController *)playerViewController;

/*!
	@method		playerViewControllerDidStartPictureInPicture:
	@param		playerViewController
				The player view controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture did start.
 */
- (void)playerViewControllerDidStartPictureInPicture:(AVPlayerViewController *)playerViewController;

/*!
	@method		playerViewController:failedToStartPictureInPictureWithError:
	@param		playerViewController
				The player view controller.
	@param		error
				An error describing why it failed.
	@abstract	Delegate can implement this method to be notified when Picture in Picture failed to start.
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController failedToStartPictureInPictureWithError:(NSError *)error;

/*!
	@method		playerViewControllerWillStopPictureInPicture:
	@param		playerViewController
				The player view controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture will stop.
 */
- (void)playerViewControllerWillStopPictureInPicture:(AVPlayerViewController *)playerViewController;

/*!
	@method		playerViewControllerDidStopPictureInPicture:
	@param		playerViewController
				The player view controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture did stop.
 */
- (void)playerViewControllerDidStopPictureInPicture:(AVPlayerViewController *)playerViewController;

/*!
	@method		playerViewControllerShouldAutomaticallyDismissAtPictureInPictureStart:
	@param		playerViewController
				The player view controller.
	@abstract	Delegate can implement this method and return NO to prevent player view controller from automatically being dismissed when Picture in Picture starts.
 */
- (BOOL)playerViewControllerShouldAutomaticallyDismissAtPictureInPictureStart:(AVPlayerViewController *)playerViewController;

/*!
	@method		playerViewController:restoreUserInterfaceForPictureInPictureStopWithCompletionHandler:
	@param		playerViewController
				The player view controller.
	@param		completionHandler
				The completion handler the delegate needs to call after restore.
	@abstract	Delegate can implement this method to restore the user interface before Picture in Picture stops.
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController restoreUserInterfaceForPictureInPictureStopWithCompletionHandler:(void (^)(BOOL restored))completionHandler;

@end

NS_ASSUME_NONNULL_END
// ==========  AVKit.framework/Headers/AVKit.h
/*
	File:  AVKit.h
	
	Framework:  AVKit
	
	Copyright 2013-2015 Apple Inc. All rights reserved.
	
	To report bugs, go to:  http://developer.apple.com/bugreporter/
	
 */

#import <AVKit/AVKitDefines.h>

#if TARGET_OS_IPHONE
#import <AVKit/AVError.h>
#import <AVKit/AVPictureInPictureController.h>
#import <AVKit/AVPlayerViewController.h>
#else
#import <AVKit/AVCaptureView.h>
#import <AVKit/AVPlayerView.h>
#endif // TARGET_OS_IPHONE
// ==========  AVKit.framework/Headers/AVError.h
/*
	File:  AVError.h
	
	Framework:  AVKit
	
	Copyright 2015 Apple Inc. All rights reserved.
	
 */

#import <Foundation/Foundation.h>

#import <AVKit/AVKitDefines.h>

/*!
	@constant	AVKitErrorDomain
	@abstract	Domain for errors from AVKit APIs.
 */
AVKIT_EXTERN NSString * const AVKitErrorDomain NS_AVAILABLE_IOS(9_0);


/*!
	@constant	AVKitErrorUnknown
	@abstract	Unknown error.
	@constant	AVKitErrorPictureInPictureStartFailed
	@abstract	Failed to start Picture in Picture.
 */
typedef NS_ENUM(NSInteger, AVKitError) {
	AVKitErrorUnknown						= -1000,
	AVKitErrorPictureInPictureStartFailed	= -1001
} NS_ENUM_AVAILABLE_IOS(9_0);
// ==========  AVKit.framework/Headers/AVKitDefines.h
/*
	File:  AVKitDefines.h
	
	Framework:  AVKit
	
	Copyright 2014-2015 Apple Inc. All rights reserved.
	
 */

#import <Availability.h>
#import <TargetConditionals.h>

#ifdef __cplusplus
#define AVKIT_EXTERN	extern "C" __attribute__((visibility ("default")))
#else
#define AVKIT_EXTERN	extern __attribute__((visibility ("default")))
#endif
// ==========  AVKit.framework/Headers/AVPictureInPictureController.h
/*
	File:  AVPictureInPictureController.h
	
	Framework:  AVKit
	
	Copyright 2015 Apple Inc. All rights reserved.
	
 */

#import <Foundation/Foundation.h>

#import <AVKit/AVKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class AVPlayerLayer;
@class UIImage;
@class UITraitCollection;
@protocol AVPictureInPictureControllerDelegate;

/*!
	@class		AVPictureInPictureController
	@abstract	AVPictureInPictureController is a subclass of NSObject that can be used to present the contents of an AVPlayerLayer floating on top of applications.
 */

NS_CLASS_AVAILABLE_IOS(9_0)
@interface AVPictureInPictureController : NSObject

/*!
	@method		isPictureInPictureSupported
	@abstract	Whether or not Picture in Picture is supported on the current device.
	@discussion	When NO, all initializers will return nil.
 */
+ (BOOL)isPictureInPictureSupported;

/*!
	@method		pictureInPictureButtonStartImageCompatibleWithTraitCollection:
	@param		traitCollection
				Traits that describe the image to retrieve, pass nil to use traits that describe the main screen.
	@abstract	System default Picture in Picture start template image for use in client's Picture in Picture button.
 */
+ (UIImage *)pictureInPictureButtonStartImageCompatibleWithTraitCollection:(nullable UITraitCollection *)traitCollection;

/*!
	@method		pictureInPictureButtonStopImageCompatibleWithTraitCollection:
	@param		traitCollection
				Traits that describe the image to retrieve, pass nil to use traits that describe the main screen.
	@abstract	System default Picture in Picture stop template image for use in client's Picture in Picture button.
 */
+ (UIImage *)pictureInPictureButtonStopImageCompatibleWithTraitCollection:(nullable UITraitCollection *)traitCollection;

/*!
	@method		initWithPlayerLayer:
	@param		playerLayer
				The player layer from which to source the media content for the Picture in Picture controller.
	@abstract	Designated initializer.
 */
- (nullable instancetype)initWithPlayerLayer:(AVPlayerLayer *)playerLayer NS_DESIGNATED_INITIALIZER;

/*!
	@property	playerLayer
	@abstract	The receiver's player layer.
 */
@property (nonatomic, readonly) AVPlayerLayer *playerLayer;

/*!
	@property	delegate
	@abstract	The receiver's delegate.
 */
@property (nonatomic, weak, nullable) id <AVPictureInPictureControllerDelegate> delegate;

/*!
	@method		startPictureInPicture
	@abstract	Start Picture in Picture for the provided AVPlayerLayer if possible.
	@discussion	Receiver will call -pictureInPictureControllerWillStartPictureInPicture: if Picture in Picture is currently possible and -pictureInPictureControllerDidStartPictureInPicture: after a successful start. If starting Picture in Picture fails, -pictureInPictureControllerFailedToStartPictureInPicture:withError: is called on the delegate instead. Client can stop Picture in Picture by calling -stopPictureInPicture. In addition the user can stop Picture in Picture through user interaction. It is also possible that Picture in Picture is stopped by the Picture in Picture controller at any time. In all these cases receiver calls -pictureInPictureControllerWillStopPictureInPicture: on the delegate and -pictureInPictureControllerDidStopPictureInPicture:after the stop animation completed.
 */
- (void)startPictureInPicture;

/*!
	@method		stopPictureInPicture
	@abstract	Stop Picture in Picture for the provided AVPlayerLayer if currently active.
	@discussion	See -startPictureInPicture for details.
 */
- (void)stopPictureInPicture;

/*!
	@property	pictureInPicturePossible
	@abstract	Whether or not Picture in Picture is currently possible.
 */
@property (nonatomic, readonly, getter = isPictureInPicturePossible) BOOL pictureInPicturePossible;

/*!
	@property	pictureInPictureActive
	@abstract	Whether or not Picture in Picture is currently active.
 */
@property (nonatomic, readonly, getter = isPictureInPictureActive) BOOL pictureInPictureActive;

/*!
	@property	pictureInPictureSuspended
	@abstract	Whether or not Picture in Picture is currently suspended.
 */
@property (nonatomic, readonly, getter = isPictureInPictureSuspended) BOOL pictureInPictureSuspended;

@end


/*!
	@protocol	AVPictureInPictureControllerDelegate
	@abstract	A protocol for delegates of AVPictureInPictureController.
 */

@protocol AVPictureInPictureControllerDelegate <NSObject>
@optional

/*!
	@method		pictureInPictureControllerWillStartPictureInPicture:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture will start.
 */
- (void)pictureInPictureControllerWillStartPictureInPicture:(AVPictureInPictureController *)pictureInPictureController;

/*!
	@method		pictureInPictureControllerDidStartPictureInPicture:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture did start.
 */
- (void)pictureInPictureControllerDidStartPictureInPicture:(AVPictureInPictureController *)pictureInPictureController;

/*!
	@method		pictureInPictureController:failedToStartPictureInPictureWithError:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@param		error
				An error describing why it failed.
	@abstract	Delegate can implement this method to be notified when Picture in Picture failed to start.
 */
- (void)pictureInPictureController:(AVPictureInPictureController *)pictureInPictureController failedToStartPictureInPictureWithError:(NSError *)error;

/*!
	@method		pictureInPictureControllerWillStopPictureInPicture:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture will stop.
 */
- (void)pictureInPictureControllerWillStopPictureInPicture:(AVPictureInPictureController *)pictureInPictureController;

/*!
	@method		pictureInPictureControllerDidStopPictureInPicture:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture did stop.
 */
- (void)pictureInPictureControllerDidStopPictureInPicture:(AVPictureInPictureController *)pictureInPictureController;

/*!
	@method		pictureInPictureController:restoreUserInterfaceForPictureInPictureStopWithCompletionHandler:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@param		completionHandler
				The completion handler the delegate needs to call after restore.
	@abstract	Delegate can implement this method to restore the user interface before Picture in Picture stops.
 */
- (void)pictureInPictureController:(AVPictureInPictureController *)pictureInPictureController restoreUserInterfaceForPictureInPictureStopWithCompletionHandler:(void (^)(BOOL restored))completionHandler;

@end

NS_ASSUME_NONNULL_END
