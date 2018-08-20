// ==========  ReplayKit.framework/Headers/ReplayKit.h
//
//  ReplayKit.h
//  ReplayKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <ReplayKit/RPPreviewViewController.h>
#import <ReplayKit/RPScreenRecorder.h>
#import <ReplayKit/RPError.h>


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
    RPRecordingErrorContentResize = -5807 // Recording interrupted by multitasking and Content Resizing
};
// ==========  ReplayKit.framework/Headers/RPPreviewViewController.h
//
//  RPVideoPreviewViewController.h
//  ReplayKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_CLASS_AVAILABLE_IOS(9_0)
NS_ASSUME_NONNULL_BEGIN
/*! @class RPPreviewViewController
 @abstract View controller that allows the user to preview/edit a movie recorded with ReplayKit. Passed into the completion handler supplied to [RPScreenRecorder stopRecordingWithHandler:].
 */
@protocol RPPreviewViewControllerDelegate;

@interface RPPreviewViewController : UIViewController
@property (nonatomic, weak, nullable) id<RPPreviewViewControllerDelegate>previewControllerDelegate;
@end

@protocol RPPreviewViewControllerDelegate <NSObject>
@optional
/* @abstract Called when the view controller is finished. */
- (void)previewControllerDidFinish:(RPPreviewViewController *)previewController;

/* @abstract Called when the view controller is finished and returns a set of activity types that the user has completed on the recording. The built in activity types are listed in UIActivity.h. */
- (void)previewController:(RPPreviewViewController *)previewController didFinishWithActivityTypes:(NSSet <NSString *> *)activityTypes;
@end
NS_ASSUME_NONNULL_END
// ==========  ReplayKit.framework/Headers/RPScreenRecorder.h
//
//  RPScreenRecorder.h
//  ReplayKit
//
//  ReplayKit is a high level framework that can be used to add video and audio recording capabilities to an application. An application supplied user interface can use the RPScreenRecorder singleton to start and stop recording. Once recording is finished, the framework will vend an instance of RPPreviewViewController that can be presented using [UIViewController presentViewController:animated:completion:]. The view controller allows the user to preview, trim and share the movie.
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "RPPreviewViewController.h"
NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(9_0)
@protocol RPScreenRecorderDelegate;

/*! @class RPScreenRecorder
 @abstract Singleton class used to control app recording.
 */
@interface RPScreenRecorder : NSObject

/* @abstract Shared instance of the screen recorder. */
+ (RPScreenRecorder *)sharedRecorder;

- (nullable instancetype) init __attribute__((unavailable("use sharedRecorder instead")));
+ (nullable instancetype) new __attribute__((unavailable("use sharedRecorder instead")));

/*! @abstract Starts app recording with a completion handler. Note that before recording actually starts, the user may be prompted with UI to confirm recording.
 @param microphoneEnabled Determines whether the microphone input should be included in the recorded movie audio.
 @result handler Called after user interactions are complete. Will be passed an optional NSError in the RPRecordingErrorDomain domain if there was an issue starting the recording.
 */
- (void)startRecordingWithMicrophoneEnabled:(BOOL)microphoneEnabled handler:(nullable void(^)(NSError * __nullable error))handler;

/*! @abstract Stops app recording with a completion handler.
 @result handler Called when the movie is ready. Will return an instance of RPPreviewViewController on success which should be presested using [UIViewController presentViewController:animated:completion:]. Will be passed an optional NSError in the RPRecordingErrorDomain domain if there was an issue stopping the recording.
 */
- (void)stopRecordingWithHandler:(nullable void(^)(RPPreviewViewController * __nullable previewViewController, NSError * __nullable error))handler;

/*! @abstract Discards the current recording. This can only be called after the handler block in stopRecordingWithHandler: is executed.
 */
- (void)discardRecordingWithHandler:(void(^)(void))handler;

/* @abstract Delegate instance for RPScreenRecorder. */
@property (nonatomic, weak, nullable) id<RPScreenRecorderDelegate> delegate;

/* @abstract Check if a recording session is in progress. Can be used for key value observing. */
@property (nonatomic, readonly, getter=isRecording) BOOL recording;

/* @abstract Check if microphone is enabled during recording. This can not be used to enable the microphone during a recording session - use startRecordingWithMicrophoneEnabled:withHandler: for that scenario. Can be used for key value observing. */
@property (nonatomic, readonly, getter=isMicrophoneEnabled) BOOL microphoneEnabled;

/* @abstract Check if screen recording is available. Implement the screenRecorderDidChangeAvailability: on the delegate to listen for changes to this property. Can be used for key value observing. */
@property (nonatomic, readonly, getter=isAvailable) BOOL available;

@end

@protocol RPScreenRecorderDelegate <NSObject>
@optional

/*! @abstract Called when recording has stopped for any reason.
 @param screenRecorder The instance of the screen recorder.
 @param error An NSError describing why recording has stopped in the RPRecordingErrorDomain.
 @param previewController If a partial movie is available before it was stopped, an instance of RPPreviewViewController will be returned.
 */
- (void)screenRecorder:(RPScreenRecorder *)screenRecorder didStopRecordingWithError:(NSError *)error previewViewController:(nullable RPPreviewViewController *)previewViewController;

/*! @abstract Called when the recorder becomes available or stops being available. Check the screen recorder's availability property to check the current availability state. Possible reasons for the recorder to be unavailable include an in-progress Airplay/TVOut session or unsupported hardware.
 @param screenRecorder The instance of the screen recorder.
 */
- (void)screenRecorderDidChangeAvailability:(RPScreenRecorder *)screenRecorder;
@end
NS_ASSUME_NONNULL_END


