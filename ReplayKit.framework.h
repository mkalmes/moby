// ==========  ReplayKit.framework/Headers/ReplayKit.h
//
//  ReplayKit.h
//  ReplayKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <ReplayKit/RPScreenRecorder.h>
#import <ReplayKit/RPPreviewViewController.h>
#import <ReplayKit/RPBroadcast.h>
#import <ReplayKit/RPBroadcastExtension.h>
#import <ReplayKit/RPError.h>


// ==========  ReplayKit.framework/Headers/RPBroadcastConfiguration.h
//
//  RPBroadcastConfiguration.h
//  ReplayKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

API_DEPRECATED("No longer supported", ios(10.0,11.0), tvos(10.0,11.0))

NS_ASSUME_NONNULL_BEGIN
@interface RPBroadcastConfiguration : NSObject <NSCoding, NSSecureCoding>

/* @abstract Specify the duration of a movie clip before it is delivered to the movie clip handler extension. Default is 5 seconds. */
@property (nonatomic, assign) NSTimeInterval clipDuration;

/* @abstract Override the video compression properties used to encode movie clips. See AVVideoCompressionPropertiesKey in <AVFoundation/AVVideoSettings.h> for available properties. */
@property (nonatomic, strong, nullable) NSDictionary <NSString *, NSObject <NSCoding, NSSecureCoding> *> *videoCompressionProperties;

@end
NS_ASSUME_NONNULL_END
// ==========  ReplayKit.framework/Headers/RPBroadcast.h
//
//  RPBroadcast.h
//  ReplayKit
//
//  The following guidelines can be followed to add broadcasting capabilities to an application:
//
//  Use the RPScreenRecorder singleton to enable the microphone and front-facing camera recording.
//
//  Load an instance of RPBroadcastActivityViewController and present it when the user intends to start 	broadcasting. This will present a view controller thats allows the user to select from the broadcast servies available on the device. Selecting a broadcast service presents the service’s UI to the user and allows the user to sign-in and setup their broadcast.
//
//  Once setup with the service is complete, an RPBroadcastController instance will be provided via the RPBroadcastActivityViewControllerDelegate protocol. This controller can be used to start, pause and finish the broadcast.
//
//  RPBroadcastController will have an NSDictionary instance in its serviceInfo property which will contain a URL  to their broadcast (which can be provided to the user to share prior to starting a broadcast), as well as other optional meta data the service may wish to provide.
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol RPBroadcastActivityViewControllerDelegate;
@protocol RPBroadcastControllerDelegate;
@class RPBroadcastController;

/*! @class RPBroadcastActivityViewController
 @abstract View controller that presents the user with a list of broadcast services installed on the device.
 */
API_AVAILABLE(ios(10.0),tvos(10.0))
@interface RPBroadcastActivityViewController : UIViewController

/*  @abstract Loads a RPBroadcastActivityViewController instance and returns it in the handler block.

 The view controller will present the user with a list of broadcast services available on the device and allow the user to set up a broadcast with the service through the service's UI.

 The RPBroadcastActivityViewController can be presented using [UIViewController presentViewController:animated:completion:] and should be dismissed when the delegate's broadcastActivityViewController:didFinishWithBroadcastController:error: method is called. Note that on large screen devices such as iPad, the default presentation style for view controllers is a popover. For an instance of RPBroadcastActivityViewController to present properly on iPad, it needs to have its popoverPresentationController's sourceRect and sourceView configured.

 @param broadcastActivityViewController The RPBroadcastActivityViewController which can be presented.
 @param error Optional error in the RPRecordingErrorCode domain which is supplied in the event the view controller could not be loaded.
 */
+ (void)loadBroadcastActivityViewControllerWithHandler:(void(^)(RPBroadcastActivityViewController * _Nullable broadcastActivityViewController, NSError * _Nullable error))handler;

/*  @abstract Loads a RPBroadcastActivityViewController instance and returns it in the handler block.
 
 The view controller will present the user with a view that shows the preferred streaming extension service and allow the user to set up a broadcast with the service through the service's UI.
 
 The RPBroadcastActivityViewController can be presented using [UIViewController presentViewController:animated:completion:] and should be dismissed when the delegate's broadcastActivityViewController:didFinishWithBroadcastController:error: method is called. Note that on large screen devices such as iPad, the default presentation style for view controllers is a popover. For an instance of RPBroadcastActivityViewController to present properly on iPad, it needs to have its popoverPresentationController's sourceRect and sourceView configured.
 
 @param preferredExtension The extension bundle identifier for the preferred broadcast extension service 
 @param broadcastActivityViewController The RPBroadcastActivityViewController which can be presented, returns nil if ther eis no matching extension.
 @param error Optional error in the RPRecordingErrorCode domain which is supplied in the event the view controller could not be loaded.
 */
+ (void)loadBroadcastActivityViewControllerWithPreferredExtension:(NSString * _Nullable)preferredExtension handler:(nonnull void(^)(RPBroadcastActivityViewController * _Nullable broadcastActivityViewController, NSError * _Nullable error))handler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos);

/*  @abstract Delegate that is notified when the activity view controller is complete. */
@property (nonatomic, weak, nullable) id<RPBroadcastActivityViewControllerDelegate> delegate;
@end

API_AVAILABLE(ios(10.0),tvos(10.0))
@protocol RPBroadcastActivityViewControllerDelegate <NSObject>

/*  @abstract Called when the view controller is finished.
 @param broadcastActivityViewController The view controller instance.
 @param broadcastController An RPBroadcastController instance that can be used to start and stop broadcasts to a user selected service.
 @param error Optional error in the RPRecordingErrorCode domain. A nil error signifies that the user has successfully set up the broadcast with a broadcast service and is ready to start broadcasting.
 */
- (void)broadcastActivityViewController:(RPBroadcastActivityViewController *)broadcastActivityViewController didFinishWithBroadcastController:(nullable RPBroadcastController *)broadcastController error:(nullable NSError *)error API_AVAILABLE(ios(10.0), tvos(10.0));
@end

/*! @class RPBroadcastController
 @abstract Available once a user has successfully initiated a broadcast using an RPBroadcastActivityViewController. Can be used to start, pause and stop a broadcast.
 */
API_AVAILABLE(ios(10.0),tvos(10.0))
@interface RPBroadcastController : NSObject
/*  @abstract Indicates whether the controller is currently broadcasting. */
@property (nonatomic, readonly, getter=isBroadcasting) BOOL broadcasting;
/*  @abstract Indicates whether the controller is currently paused. */
@property (nonatomic, readonly, getter=isPaused) BOOL paused;
/*  @abstract URL that can be used to redirect the user to the on-going or completed broadcast. */
@property (nonatomic, readonly) NSURL *broadcastURL;
/*  @abstract Dictionary updated by the service during a broadcast. The keys and values of this dictionary are defined by the broadcast service. KVO observable. */
@property (nonatomic, readonly, nullable) NSDictionary <NSString *, NSObject <NSCoding> *> *serviceInfo;
/*  @abstract Delegate which will be notified when an error occurs during broadcast. */
@property (nonatomic, weak) id<RPBroadcastControllerDelegate> delegate;
/*  @abstract bundleID of the broadcast extension which was selected by the user. */
@property (nonatomic, readonly) NSString *broadcastExtensionBundleID API_DEPRECATED("No longer supported",ios(10.0,11.0),tvos(10.0,11.0));
/*  @abstract Start the broadcast.
 @param error Optional error in the RPRecordingErrorCode domain. A nil error signifies that broadcasting has started successfully.
 */
- (void)startBroadcastWithHandler:(void(^)(NSError * _Nullable error))handler;

/*  @abstract Pause the broadcast. The broadcast will pause immediately. */
- (void)pauseBroadcast;

/*  @abstract Resumes the broadcast. The broadcast will resume immediately. */
- (void)resumeBroadcast;

/*  @abstract Finish the broadcast.
 @param error Optional error in the RPRecordingErrorCode domain. A nil error signifies that broadcasting has finished successfully.
 */
- (void)finishBroadcastWithHandler:(void(^)(NSError * _Nullable error))handler;
@end

API_AVAILABLE(ios(10.0),tvos(10.0))
@protocol RPBroadcastControllerDelegate <NSObject>
@optional

/*  @abstract Called when broadcasting finishes due to an error.
 @param broadcastController The controller instance.
 @param error Required error in the RPRecordingErrorCode domain.
 */

- (void)broadcastController:(RPBroadcastController *)broadcastController didFinishWithError:(nullable NSError *)error;
/*  @abstract Called when the broadcast service has data to pass back to broadcasting app.
 @param broadcastController The controller instance.
 @param serviceInfo NSDictionary instance with keys and values defined by the broadcasting service.
 */
- (void)broadcastController:(RPBroadcastController *)broadcastController didUpdateServiceInfo:(NSDictionary <NSString *, NSObject <NSCoding> *> *)serviceInfo;

/*  @abstract Called when the broadcast service has updated broadcastURL.
 @param broadcastController The controller instance.
 @param broadcastURL NSURL instance with URL of the resource where broacast can be viewed. Defined by broadcast service. 
 */
- (void)broadcastController:(RPBroadcastController *)broadcastController didUpdateBroadcastURL:(NSURL *)broadcastURL API_AVAILABLE(ios(11.0), tvos(11.0));
@end

/*! @class RPSystemBroadcastPickerView
 @abstract View that presents the user with a button for starting iOS system broadcast using preferred broadcast service.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos)
@interface RPSystemBroadcastPickerView : UIView <NSCoding>
/*  @abstract Bundle identifier of extension that should be used for broadcast. Default is nil which means that all extensions will be presented */
@property (nonatomic, strong, nullable) NSString *preferredExtension;
/*  @abstract Indicates whether the Microphone button is visible in broadcast picker view. Default is YES. */
@property (nonatomic, assign) BOOL showsMicrophoneButton;
@end

NS_ASSUME_NONNULL_END
// ==========  ReplayKit.framework/Headers/RPBroadcastExtension.h
//
//  RPBroadcastExtension.h
//  ReplayKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import "RPBroadcastConfiguration.h"
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
/*! 
    @category NSExtensionContext (RPBroadcastExtension)
    @abstract Category which defines the method to call from on an extension context object when user interaction is complete during the broadcast setup flow.
 */
@interface NSExtensionContext (RPBroadcastExtension)

/*! @abstract Load information about the broadcasting app.
    @param handler block which will be supplied a bundleID, displayName and an optional appIcon.
 */
- (void)loadBroadcastingApplicationInfoWithCompletion:(void(^)(NSString *bundleID, NSString *displayName, UIImage * __nullable appIcon))handler;

/*! @abstract Method to be called when the extension should finish. Deprecated.
    @param broadcastURL URL that can be used to redirect the user to the ongoing or completed broadcast. This URL is made available to the running application via a property in RPBroadcastController.
    @param broadcastConfiguration Configuration to use for generating movie clips
    @param setupInfo Dictionary that can be used to share any setup information required by the upload extension. The values and keys in this dictionary are to be defined by the extension developer.
 */
- (void)completeRequestWithBroadcastURL:(NSURL *)broadcastURL broadcastConfiguration:(RPBroadcastConfiguration *)broadcastConfiguration setupInfo:(nullable NSDictionary <NSString *, NSObject <NSCoding> *> *)setupInfo API_DEPRECATED("No longer supported", ios(10.0,11.0),tvos(10.0,11.0));

/*! @abstract Method to be called when the extension should finish.
    @param broadcastURL URL that can be used to redirect the user to the ongoing or completed broadcast. This URL is made available to the running application via a property in RPBroadcastController.
    @param setupInfo Dictionary that can be used to share any setup information required by the upload extension. The values and keys in this dictionary are to be defined by the extension developer.
 */
- (void)completeRequestWithBroadcastURL:(NSURL *)broadcastURL setupInfo:(nullable NSDictionary <NSString *, NSObject <NSCoding> *> *)setupInfo API_AVAILABLE(ios(11.0),tvos(11.0));

@end

/*!
 @class RPBroadcastProcessExtension
 @abstract Base class for extensions that are responsible for handling video and audio data.
 */
API_AVAILABLE(ios(10.0),tvos(10.0))
@interface RPBroadcastHandler : NSObject <NSExtensionRequestHandling>
/*! @abstract Call this method, supplying it with a dictionary defined by the service, to populate the serviceInfo property on RPBroadcastController. This can be used to communicate viewing stats or messages back to the broadcasting app.
 @param serviceInfo Dictionary that can be passed back to the broadcasting app that may contain information about the ongoing broadcast.
 */
- (void)updateServiceInfo:(NSDictionary<NSString *, NSObject <NSCoding> *> *)serviceInfo;

/*! @abstract Call this method, supplying it with a URL to update the broadcastURL property on RPBroadcastController.
 @param broadcastURL URL of the resource where broadcast can be viewed which will be passed to the broadcasting app.
 */
- (void)updateBroadcastURL:(NSURL *)broadcastURL API_AVAILABLE(ios(11.0), tvos(11.0));
@end

/*! 
    @class RPBroadcastMP4ClipHandler
    @abstract Subclass this class to handle movie clips as they are recorded by ReplayKit during the broadcast flow. ReplayKit will call processMP4ClipWithURL when a movie clip is available for processing.
 */
API_DEPRECATED("No longer supported, use RPBroadcastSampleHandler instead.", ios(10.0,11.0),tvos(10.0,11.0))
@interface RPBroadcastMP4ClipHandler : RPBroadcastHandler
/*! @abstract Method which ReplayKit will call when an MP4 movie clip is ready for processing.
 @param mp4ClipURL URL that points to the location of the movie clip recorded by ReplayKit. Note that the URL may be nil in certain cases such as an error.
 @param setupInfo Dictionary supplied by the UI extension that may contain setup information required for processing. The values in this dictionary are to be defined by the extension developer.
 @param finished Boolean indicating that application requested the broadcast to end.
 */
- (void)processMP4ClipWithURL:(nullable NSURL *)mp4ClipURL setupInfo:(nullable NSDictionary <NSString *, NSObject *> *)setupInfo finished:(BOOL)finished;

/*! @abstract Method that should be called when processing is complete.
    @param broadcastConfiguration Optional updated configuration that will be applied to the next MP4 clip.
    @param error Optional error to communicate to ReplayKit and the host application that there was an issue with the broadcast and to stop broadcasting. Note that once this is called, regardles of the existence of an error, the current MP4 clip will no longer be available.
 */
- (void)finishedProcessingMP4ClipWithUpdatedBroadcastConfiguration:(nullable RPBroadcastConfiguration *)broadcastConfiguration error:(nullable NSError *)error;
@end

API_AVAILABLE(ios(10.0),tvos(10.0))
typedef NS_ENUM(NSInteger, RPSampleBufferType) {
    RPSampleBufferTypeVideo = 1,
    RPSampleBufferTypeAudioApp,
    RPSampleBufferTypeAudioMic,
};

/*!
 @key RPVideoSampleOrientationKey
 @abstract Use this key in conjunction with CMGetAttachment on CMSampleBufferRef to get the orientation for the sample. The orientation will follow the enum CGImagePropertyOrientation
 */
API_AVAILABLE(ios(11.0),tvos(11.0))
extern NSString *const RPVideoSampleOrientationKey;

/*!
 @key RPApplicationInfoBundleIdentifierKey
 @abstract Use this key to retrieve bundle identifier from dictionary provided by broadcastAnnotatedWithApplicationInfo
 */
API_AVAILABLE(ios(11.2)) API_UNAVAILABLE(tvos)
extern NSString *const RPApplicationInfoBundleIdentifierKey;

/*!
 @class RPBroadcastSampleHandler
 @abstract Subclass this class to handle CMSampleBuffer objects as they are captured by ReplayKit. To enable this mode of handling, set the RPBroadcastProcessMode in the extension's info.plist to RPBroadcastProcessModeSampleBuffer.
 */
API_AVAILABLE(ios(10.0),tvos(10.0))
@interface RPBroadcastSampleHandler : RPBroadcastHandler

/*! @abstract Method is called when the RPBroadcastController startBroadcast method is called from the broadcasting application.
    @param setupInfo Dictionary that can be supplied by the UI extension to the sample handler.
 */
- (void)broadcastStartedWithSetupInfo:(nullable NSDictionary <NSString *, NSObject *> *)setupInfo;

/*! @abstract Method is called when the RPBroadcastController pauseBroadcast method is called from the broadcasting application. */
- (void)broadcastPaused;

/*! @abstract Method is called when the RPBroadcastController resumeBroadcast method is called from the broadcasting application. */
- (void)broadcastResumed;

/*! @abstract Method is called when the RPBroadcastController finishBroadcast method is called from the broadcasting application. */
- (void)broadcastFinished;

/*! @abstract Method is called when broadcast is started from Control Center and provides extension information about the first application opened or used during the broadcast.
    @param applicationInfo Dictionary that contains information about the first application opened or used buring the broadcast.
 */
- (void)broadcastAnnotatedWithApplicationInfo:(NSDictionary *)applicationInfo API_AVAILABLE(ios(11.2)) API_UNAVAILABLE(tvos);

/*! @abstract Method is called as video and audio data become available during a broadcast session and is delivered as CMSampleBuffer objects.
    @param sampleBuffer CMSampleBuffer object which contains either video or audio data.
    @param sampleBufferType Determine's the type of the sample buffer defined by the RPSampleBufferType enum.
 */
- (void)processSampleBuffer:(CMSampleBufferRef)sampleBuffer withType:(RPSampleBufferType)sampleBufferType;

/*! @abstract Method that should be called when broadcasting can not proceed due to an error. Calling this method will stop the broadcast and deliver the error back to the broadcasting app through RPBroadcastController's delegate.
    @param error NSError object that will be passed back to the broadcasting app through RPBroadcastControllerDelegate's broadcastController:didFinishWithError: method.
 */
- (void)finishBroadcastWithError:(NSError *)error;

@end
NS_ASSUME_NONNULL_END

// ==========  ReplayKit.framework/Headers/RPError.h
//
//  RPError.h
//  ReplayKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
extern NSString * const __nonnull RPRecordingErrorDomain;

NS_ENUM_AVAILABLE_IOS(9_0)
typedef NS_ENUM(NSInteger, RPRecordingErrorCode) {
    RPRecordingErrorUnknown = -5800,
    RPRecordingErrorUserDeclined = -5801, // The user declined app recording.
    RPRecordingErrorDisabled = -5802, // App recording has been disabled via parental controls.
    RPRecordingErrorFailedToStart = -5803, // Recording failed to start
    RPRecordingErrorFailed = -5804, // Failed during recording
    RPRecordingErrorInsufficientStorage = -5805, // Insufficient storage for recording.
    RPRecordingErrorInterrupted = -5806, // Recording interrupted by other app
    RPRecordingErrorContentResize = -5807, // Recording interrupted by multitasking and Content Resizing
    RPRecordingErrorBroadcastInvalidSession = -5808, // Attempted to start a broadcast without a prior session
    RPRecordingErrorSystemDormancy = -5809, // Recording was forced to end when user pressed the power button
    RPRecordingErrorEntitlements = -5810, // Recording failed due to missing entitlements
    RPRecordingErrorActivePhoneCall = -5811, // Recording unable to to record due to active phone call
    RPRecordingErrorFailedToSave = -5812, // Failed to save recording to camera roll
    RPRecordingErrorCarPlay = -5813, // Failed to start recording due to carplay being active
    RPRecordingErrorFailedApplicationConnectionInvalid = -5814, // Failed during recording application connection invalid
    RPRecordingErrorFailedApplicationConnectionInterrupted = -5815, // Failed during recording appliation connection interrupted
    RPRecordingErrorFailedNoMatchingApplicationContext = -5816, // Failed during recording context id does not match application
    RPRecordingErrorFailedMediaServicesFailure = -5817, // Failed during recording due to mediaservices failure
    RPRecordingErrorVideoMixingFailure = -5818 // Failed during recording due to audio/video mixing failure
};
// ==========  ReplayKit.framework/Headers/RPPreviewViewController.h
//
//  RPVideoPreviewViewController.h
//  ReplayKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ENUM_AVAILABLE_IOS(10_0)
typedef NS_ENUM(NSInteger, RPPreviewViewControllerMode) {
    RPPreviewViewControllerModePreview,
    RPPreviewViewControllerModeShare
}; __IOS_PROHIBITED


NS_CLASS_AVAILABLE_IOS(9_0)
NS_ASSUME_NONNULL_BEGIN
/*! @class RPPreviewViewController
 @abstract View controller that allows the user to preview/edit a movie recorded with ReplayKit. Passed into the completion handler supplied to [RPScreenRecorder stopRecordingWithHandler:].
 */
@protocol RPPreviewViewControllerDelegate;

@interface RPPreviewViewController : UIViewController
@property (nonatomic, weak, nullable) id<RPPreviewViewControllerDelegate>previewControllerDelegate;
@property (nonatomic, assign) RPPreviewViewControllerMode mode __IOS_PROHIBITED __TVOS_AVAILABLE(10_0);  // Set
@end

@protocol RPPreviewViewControllerDelegate <NSObject>
@optional
/* @abstract Called when the view controller is finished. */
- (void)previewControllerDidFinish:(RPPreviewViewController *)previewController;

/* @abstract Called when the view controller is finished and returns a set of activity types that the user has completed on the recording. The built in activity types are listed in UIActivity.h. */
- (void)previewController:(RPPreviewViewController *)previewController didFinishWithActivityTypes:(NSSet <NSString *> *)activityTypes __TVOS_PROHIBITED;
@end
NS_ASSUME_NONNULL_END
// ==========  ReplayKit.framework/Headers/RPScreenRecorder.h
//
//  RPScreenRecorder.h
//  ReplayKit
//
//  ReplayKit is a high level framework that can be used to add video and audio recording and broadcast capabilities to an application. An application supplied user interface can use the RPScreenRecorder singleton to start and stop recording or broadcasting.
//
//  Optionally the framework allows the user to also record microphone content as well as content from the front facing camera.
//
//  When local recording stops, the framework will vend an instance of RPPreviewViewController that can be presented using [UIViewController presentViewController:animated:completion:]. The view controller allows the user to preview, trim and share the movie.
//
//  When broadcasting stops, the framework will return a url that can be used to view a broadcast.
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "RPPreviewViewController.h"
#import "RPBroadcastExtension.h"

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos)
typedef NS_ENUM(NSInteger, RPCameraPosition) {
    RPCameraPositionFront = 1,
    RPCameraPositionBack,
};

API_AVAILABLE(ios(9.0), tvos(10.0))

@protocol RPScreenRecorderDelegate;
@class RPBroadcastActivityViewController;

/*! @class RPScreenRecorder
 @abstract Singleton class used to control app recording.
 */
@interface RPScreenRecorder : NSObject

/* @abstract Shared instance of the screen recorder. */
+ (RPScreenRecorder *)sharedRecorder;

- (instancetype)init API_UNAVAILABLE(ios,tvos); // Use sharedRecorder instead

/*! 
 Deprecated. Use startRecordingWithHandler: instead.
 
 @abstract Starts app recording with a completion handler. Note that before recording actually starts, the user may be prompted with UI to confirm recording.
 @param microphoneEnabled Determines whether the microphone input should be included in the recorded movie audio.
 @result handler Called after user interactions are complete. Will be passed an optional NSError in the RPRecordingErrorDomain domain if there was an issue starting the recording.
 */
- (void)startRecordingWithMicrophoneEnabled:(BOOL)microphoneEnabled handler:(nullable void(^)(NSError * _Nullable error))handler API_DEPRECATED("Use microphoneEnabaled property", ios(9.0, 10.0));

/*! @abstract Starts app recording with a completion handler. Note that before recording actually starts, the user may be prompted with UI to confirm recording.
 @result handler Called after user interactions are complete. Will be passed an optional NSError in the RPRecordingErrorDomain domain if there was an issue starting the recording.
 */
- (void)startRecordingWithHandler:(nullable void(^)(NSError * _Nullable error))handler API_AVAILABLE(ios(10.0), tvos(10.0));

/*! @abstract Stops app recording with a completion handler.
 @result handler Called when the movie is ready. Will return an instance of RPPreviewViewController on success which should be presented using [UIViewController presentViewController:animated:completion:]. Will be passed an optional NSError in the RPRecordingErrorDomain domain if there was an issue stopping the recording.
 */
- (void)stopRecordingWithHandler:(nullable void(^)(RPPreviewViewController * _Nullable previewViewController, NSError * _Nullable error))handler;

/*! @abstract Discards the current recording. This can only be called after the handler block in stopRecordingWithHandler: is executed.
 */
- (void)discardRecordingWithHandler:(void(^)(void))handler;

/*! @abstract Starts screen and audio capture and continually calls the supplied handler with the current sampleBuffer and bufferType and passed it back to the application. Note that before recording actually starts, the user may be prompted with UI to confirm recording.
 @result handler Called continually with sampleBuffers and the bufferType. Will be passed an optional NSError in the RPRecordingErrorDomain domain if there was an issue starting the capture.
 */
- (void)startCaptureWithHandler:(nullable void(^)(CMSampleBufferRef sampleBuffer, RPSampleBufferType bufferType, NSError * _Nullable error))captureHandler completionHandler:(nullable void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0), tvos(11.0));

/*! @abstract Stops screen capture with a completion handler
 @result handler Called after the screen capture has stopped. Will be passed an optional NSError in the RPRecordingErrorDomain domain if there was an issue stopping the capture
 */
- (void)stopCaptureWithHandler:(nullable void(^)(NSError * _Nullable error))handler API_AVAILABLE(ios(11.0), tvos(11.0));

/* @abstract Delegate instance for RPScreenRecorder. */
@property (nonatomic, weak, nullable) id<RPScreenRecorderDelegate> delegate;

/* @abstract Check if ReplayKit is available on the device. Implement the screenRecorderDidChangeAvailability: on the delegate to listen for changes to this property. Can be used for key value observing. */
@property (nonatomic, readonly, getter=isAvailable) BOOL available;

/* @abstract Check if a recording session is in progress. Can be used for key value observing. */
@property (nonatomic, readonly, getter=isRecording) BOOL recording;

/* @abstract Specify or query whether the microphone should be enabled during recording. Can be used for key value observing. Default is NO. */
@property (nonatomic, getter=isMicrophoneEnabled) BOOL microphoneEnabled API_UNAVAILABLE(tvos);

/* @abstract Specify or query whether the camera should be enabled during recording. Can be used for key value observing. Default is NO. */
@property (nonatomic, getter=isCameraEnabled) BOOL cameraEnabled API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(tvos);

/* @abstract Specify or query camera position. Can be used for key value observing. Default is RPCameraPositionFront. */
@property (nonatomic) RPCameraPosition cameraPosition API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos);

/* @abstract A UIView instance that renders the front or back facing camera contents. This will be nil if the camera has not been enabled */
@property (nonatomic, readonly, nullable) UIView *cameraPreviewView API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(tvos);

@end

API_AVAILABLE(ios(9.0), tvos(10.0))
@protocol RPScreenRecorderDelegate <NSObject>
@optional

/*! @abstract Called when recording has stopped due to an error.
 @param screenRecorder The instance of the screen recorder.
 @param error An NSError describing why recording has stopped in the RPRecordingErrorDomain.
 @param previewViewController If a partial movie is available before it was stopped, an instance of RPPreviewViewController will be returned.
 */
- (void)screenRecorder:(RPScreenRecorder *)screenRecorder didStopRecordingWithError:(NSError *)error previewViewController:(nullable RPPreviewViewController *)previewViewController API_DEPRECATED("No longer supported", ios(9.0, 10.0), tvos(10.0,10.0));
- (void)screenRecorder:(RPScreenRecorder *)screenRecorder didStopRecordingWithPreviewViewController:(nullable RPPreviewViewController *)previewViewController error:(nullable NSError *)error API_AVAILABLE(ios(11.0), tvos(11.0));

/*! @abstract Called when the recorder becomes available or stops being available. Check the screen recorder's availability property to check the current availability state. Possible reasons for the recorder to be unavailable include an in-progress Airplay/TVOut session or unsupported hardware.
 @param screenRecorder The instance of the screen recorder.
 */
- (void)screenRecorderDidChangeAvailability:(RPScreenRecorder *)screenRecorder;
@end
NS_ASSUME_NONNULL_END


