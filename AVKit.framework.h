// ==========  AVKit.framework/Headers/AVPlayerViewController.h
/*
	File:  AVPlayerViewController.h
	
	Framework:  AVKit
	
	Copyright © 2014-2017 Apple Inc. All rights reserved.
	
 */

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol AVPlayerViewControllerDelegate;

/*!
	@class		AVPlayerViewController
	@abstract	AVPlayerViewController is a subclass of UIViewController that can be used to display the visual content of an AVPlayer object and the standard playback controls.
 */

API_AVAILABLE(ios(8.0))
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
@property (nonatomic) BOOL allowsPictureInPicturePlayback API_AVAILABLE(ios(9.0));

/*!
	@property	updatesNowPlayingInfoCenter
	@abstract	Whether or not the now playing info center should be updated. Default is YES.
 */
@property (nonatomic) BOOL updatesNowPlayingInfoCenter API_AVAILABLE(ios(10.0));

/*!
	@property	entersFullScreenWhenPlaybackBegins
	@abstract	Whether or not the receiver automatically enters full screen when the play button is tapped. Default is NO.
	@discussion	If YES, the receiver will show a user interface tailored to this behavior.
 */
@property (nonatomic) BOOL entersFullScreenWhenPlaybackBegins API_AVAILABLE(ios(11.0));

/*!
	@property	exitsFullScreenWhenPlaybackEnds
	@abstract	Whether or not the receiver automatically exits full screen when playback ends. Default is NO.
	@discussion	If multiple player items have been enqueued, the receiver exits fullscreen once no more items are remaining in the queue.
 */
@property (nonatomic) BOOL exitsFullScreenWhenPlaybackEnds API_AVAILABLE(ios(11.0));

/*!
	@property	delegate
	@abstract	The receiver's delegate.
 */
@property (nonatomic, weak, nullable) id <AVPlayerViewControllerDelegate> delegate API_AVAILABLE(ios(9.0));

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
	
	Copyright © 2013-2016 Apple Inc. All rights reserved.
	
	To report bugs, go to:  http://developer.apple.com/bugreporter/
	
 */

#import <AVKit/AVKitDefines.h>

#if TARGET_OS_IPHONE
#import <AVKit/AVError.h>
#import <AVKit/AVPictureInPictureController.h>
#import <AVKit/AVPlayerViewController.h>
#import <AVKit/AVRoutePickerView.h>
#else
#import <AVKit/AVCaptureView.h>
#import <AVKit/AVPlayerView.h>
#endif // TARGET_OS_IPHONE
// ==========  AVKit.framework/Headers/AVRoutePickerView.h
/*
	File:  AVRoutePickerView.h
 
	Framework:  AVKit
 
	Copyright © 2017 Apple Inc. All rights reserved.
 
 */

#import <UIKit/UIKit.h>

@protocol AVRoutePickerViewDelegate;

NS_ASSUME_NONNULL_BEGIN

/*!
	@class		AVRoutePickerView
	@abstract	AVRoutePickerView is a subclass of UIView that displays controls for picking playback routes.
 */

API_AVAILABLE(ios(11.0), tvos(11.0))
@interface AVRoutePickerView : UIView

/*!
	@property	delegate
	@abstract	The route picker view's delegate.
 */
@property (nonatomic, weak, nullable) id<AVRoutePickerViewDelegate> delegate;

/*!
	@property	activeTintColor
	@abstract	The view's tint color when AirPlay is active.
 */
@property (nonatomic, strong, null_resettable) UIColor *activeTintColor;

/*!
	@constant	AVRoutePickerViewButtonStyleSystem
				A system style for the route picker button.
	@constant	AVRoutePickerViewButtonStylePlain
				A plain style for the route picker button, which has the same appearance as the system style without the blurred background view.
	@constant	AVRoutePickerViewButtonStyleCustom
				A custom style for the route picker button, which allows customizing the background view and focused appearance.
 */
typedef NS_ENUM(NSInteger, AVRoutePickerViewButtonStyle) {
	AVRoutePickerViewButtonStyleSystem,
	AVRoutePickerViewButtonStylePlain,
	AVRoutePickerViewButtonStyleCustom
} API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios);

/*!
	@property	routePickerButtonStyle
	@abstract	The route picker button style.
 */
@property (nonatomic) AVRoutePickerViewButtonStyle routePickerButtonStyle API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios);

@end


/*!
	@protocol	AVRoutePickerViewDelegate
	@abstract	Defines an interface for delegates of AVRoutePickerView.
 */

@protocol AVRoutePickerViewDelegate <NSObject>
@optional

/*!
	@method		routePickerViewWillBeginPresentingRoutes:
	@abstract	Informs the delegate that the route picker view will start presenting routes to the user.
 */
- (void)routePickerViewWillBeginPresentingRoutes:(AVRoutePickerView *)routePickerView;

/*!
	@method		routePickerViewDidEndPresentingRoutes:
	@abstract	Informs the delegate that the route picker view finished presenting routes to the user.
 */
- (void)routePickerViewDidEndPresentingRoutes:(AVRoutePickerView *)routePickerView;

@end

NS_ASSUME_NONNULL_END
// ==========  AVKit.framework/Headers/AVError.h
/*
	File:  AVError.h
	
	Framework:  AVKit
	
	Copyright © 2015-2016 Apple Inc. All rights reserved.
	
 */

#import <Foundation/Foundation.h>

#import <AVKit/AVKitDefines.h>

/*!
	@constant	AVKitErrorDomain
	@abstract	Domain for errors from AVKit APIs.
 */
AVKIT_EXTERN NSString * const AVKitErrorDomain API_AVAILABLE(ios(9.0));


/*!
	@constant	AVKitErrorUnknown
				Unknown error.
	@constant	AVKitErrorPictureInPictureStartFailed
				Failed to start Picture in Picture.
 */
typedef NS_ENUM(NSInteger, AVKitError) {
	AVKitErrorUnknown						= -1000,
	AVKitErrorPictureInPictureStartFailed	= -1001
} API_AVAILABLE(ios(9.0));
// ==========  AVKit.framework/Headers/AVKitDefines.h
/*
	File:  AVKitDefines.h
	
	Framework:  AVKit
	
	Copyright © 2014-2016 Apple Inc. All rights reserved.
	
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
	
	Copyright © 2015-2017 Apple Inc. All rights reserved.
	
 */

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

#import <AVKit/AVKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage;
@class UITraitCollection;
@protocol AVPictureInPictureControllerDelegate;

/*!
	@class		AVPictureInPictureController
	@abstract	AVPictureInPictureController is a subclass of NSObject that can be used to present the contents of an AVPlayerLayer floating on top of applications.
 */

API_AVAILABLE(ios(9.0))
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
