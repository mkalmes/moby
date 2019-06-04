// ==========  BackgroundTasks.framework/Headers/BackgroundTasks.h
//
//  BackgroundTasks.h
//  BackgroundTasks
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <BackgroundTasks/BGDefines.h>
#import <BackgroundTasks/BGTaskScheduler.h>
#import <BackgroundTasks/BGTaskRequest.h>
#import <BackgroundTasks/BGTask.h>
// ==========  BackgroundTasks.framework/Headers/BGTaskRequest.h
//
//  BGTaskRequest.h
//  BackgroundTasks
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <BackgroundTasks/BGDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract An abstract class that represents a request for the app to be launched in the background to perform work.
 @discussion Do not instantiate instances of this class directly. Instead, use one of its concrete subclasses.
 */
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
@interface BGTaskRequest : NSObject <NSCopying>
/*!
 @abstract The identifier associated with this request.
 */
@property (readonly, copy) NSString *identifier;

/*!
 @abstract The earliest date at which the task may run.
 @discussion Setting this property does not guarantee that the task will begin at the specified date, but only that it will not begin sooner. If not specified, no start delay is used.
 */
@property (copy, nullable) NSDate *earliestBeginDate;

- (instancetype)init NS_UNAVAILABLE; // This is an abstract type and should not be directly instantiated
+ (instancetype)new NS_UNAVAILABLE; // This is an abstract type and should not be directly instantiated
@end

/*!
 @abstract A request to briefly launch your app to keep its contents up to date.
 @discussion Schedule a refresh task request to ask that the system launch your app briefly so that you can download data and keep your app's contents up-to-date. The system will fulfill this request intelligently based on system conditions and app usage.
 */
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
@interface BGAppRefreshTaskRequest : BGTaskRequest

- (instancetype)initWithIdentifier:(NSString *)identifier;

@end

/*!
 @abstract A request to launch your app to perform deferrable processing tasks.
 @discussion Schedule a processing task request to ask that the system launch your app when conditions are favorable for battery life to handle deferrable, longer-running processing, such as syncing, database maintenance, or similar tasks. The system will attempt to fulfill this request to the best of its ability within the next two days as long as the user has used your app within the past week.
 */
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
@interface BGProcessingTaskRequest : BGTaskRequest

- (instancetype)initWithIdentifier:(NSString *)identifier;

/*!
 @abstract Whether the background task represented by this request requires network connectivity.
 @discussion If this property is set to YES, the system will only launch your app to fulfill this request when the device has a network connection. If this is set to NO, your app may not have network access.
 The default value is NO.
 */
@property (assign) BOOL requiresNetworkConnectivity;

/*!
 @abstract Whether the background task represented by this request should only be done while the device is connected to external power.
 @discussion If this property is set to YES, the system will launch your app to fulfill this request only while the device is connected to external power. Setting this to YES will also disable the CPU Monitor feature.
 Specify YES if this task is resource intensive to minimize impact to battery life. Please note that, even if this value is NO, the system will not necessarily schedule this task while the device is on battery power, depending on the type of device and system conditions.
 The default value is NO.
 */
@property (assign) BOOL requiresExternalPower;

@end


NS_ASSUME_NONNULL_END


// ==========  BackgroundTasks.framework/Headers/BGDefines.h
//
//  BGDefines.h
//  BackgroundTasks
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifdef __cplusplus
#define BG_EXTERN extern "C" __attribute__((visibility("default")))
#else
#define BG_EXTERN extern __attribute__((visibility("default")))
#endif

// ==========  BackgroundTasks.framework/Headers/BGTask.h
//
//  BGTask.h
//  BackgroundTasks
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <BackgroundTasks/BGDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract An abstract class that represents the background work for which the app was launched to handle.
 @discussion Subclasses of this type are created by the system and should not be directly instantiated.
 */
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
@interface BGTask : NSObject

/*!
 @abstract The identifier associated with the request used to schedule this background work.
*/
@property (copy, readonly) NSString *identifier;

/*!
 @abstract Called by the system shortly before your app's background time expires.
 @discussion There is a limit to how long your app has to perform its background work, and your work may need to be interrupted if system conditions change. Assign a handler to this property to cancel any ongoing tasks, perform any needed cleanup, and then call setTaskCompletedWithSuccess: to signal completion to the system and allow your app to be suspended.
This property is cleared after it is called by the system or when setTaskCompletedWithSuccess: is called. This is to mitigate the impact of a retain cycle created by referencing the BGTask instance inside this block.
 */
@property (nullable, strong) void (^expirationHandler)(void);

- (instancetype)init NS_UNAVAILABLE; // Subclasses of this abstract type are created by the system and cannot be directly instantiated
- (instancetype)new NS_UNAVAILABLE; // Subclasses of this abstract type are created by the system and cannot be directly instantiated

/*!
 @abstract Marks this task as complete.
 @discussion Call this method as soon as the background work associated with this task is complete. The system provides your app with a limited amount of time to finish the task. If you do not call setTaskCompletedWithSuccess: on the task, the system continues to run in the background until all the available time is consumed, wasting battery power.
 The system suspends the app as soon as all background tasks are complete.
 @param success Whether the task was completed successfully. If the task was unsuccessful, you may request the system to try again later by submitting a new task request to the scheduler before calling this method.
 */
- (void)setTaskCompletedWithSuccess:(BOOL)success;

@end

/*!
 @abstract A background task used to perform deferrable processing.
 */
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
@interface BGProcessingTask : BGTask

@end

/*!
 @abstract A background task used to update your app's contents in the background.
 */
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
@interface BGAppRefreshTask : BGTask

@end

NS_ASSUME_NONNULL_END
// ==========  BackgroundTasks.framework/Headers/BGTaskScheduler.h
//
//  BGTaskScheduler.h
//  BackgroundTasks
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <BackgroundTasks/BGDefines.h>

@class BGTaskScheduler;
@class BGTaskRequest;
@class BGTask;

NS_ASSUME_NONNULL_BEGIN

BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
NSErrorDomain const BGTaskSchedulerErrorDomain;

/*!
 @enum BGTaskSchedulerErrorCode
 @constant BGTaskSchedulerErrorCodeUnavailable Background task scheduling functionality is not available for this app/extension. Background App Refresh may have been disabled in Settings.
 @constant BGTaskSchedulerErrorCodeTooManyPendingTaskRequests The task request could not be submitted because there are too many pending task requests of this type. Cancel some existing task requests before trying again.
 @constant BGTaskSchedulerErrorCodeNotPermitted The task request could not be submitted because the appropriate background mode is not included in the UIBackgroundModes array, or its identifier was not present in the BGTaskSchedulerPermittedIdentifiers array in the app's Info.plist.
 */
typedef NS_ERROR_ENUM(BGTaskSchedulerErrorDomain, BGTaskSchedulerErrorCode) {
    BGTaskSchedulerErrorCodeUnavailable = 1,
    BGTaskSchedulerErrorCodeTooManyPendingTaskRequests = 2,
    BGTaskSchedulerErrorCodeNotPermitted = 3,
} API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos);

/*!
 @class BGTaskScheduler
 @abstract The object you use to schedule deferrable work to be done in the background.
 */
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
@interface BGTaskScheduler : NSObject
- (instancetype)init NS_UNAVAILABLE; //Use the shared scheduler object instead
+ (instancetype)new NS_UNAVAILABLE; //Use the shared scheduler object instead

@property (class, readonly, strong) __kindof BGTaskScheduler *sharedScheduler;

/*!
 @abstract Register a handler to be called for tasks that launch the app.
 @param identifier The identifier for the task that will be handled by the provided launch handler.
 @param queue The queue on which the launch handler and the expiration handler for the task will be called. The queue should be serial to ensure consistent ordering. If you pass nil, handlers will be called on a background queue.
 @param launchHandler The block that will be called when the app is launched for the specified task. The block has no return value and takes a single parameter, task, a BGTask object. Assign an expiration handler to the task's expirationHandler property and call setTaskCompletedWithSuccess: when the background work is complete.
 @discussion You must register launch handlers before your application finishes launching. Attempting to register a handler after launch or multiple handlers for the same identifier is an error. Although you may submit task requests from some extensions, only the host app will be launched to handle background work.
 @return YES if the handler was registered, or NO if it was not because the provided identifier was not present in the BGTaskSchedulerPermittedIdentifiers array in the app's Info.plist.
 */
- (BOOL)registerForTaskWithIdentifier:(NSString *)identifier usingQueue:(nullable dispatch_queue_t)queue launchHandler:(void (^)(__kindof BGTask *task))launchHandler NS_EXTENSION_UNAVAILABLE("Only the host application may register launch handlers");

/*!
 @abstract Submit a request to be launched in the background to perform work.
 @param taskRequest The task request object representing the parameters of the background task to be scheduled.
 @param error If an error occurs, upon return contains an error object that indicates why the request was rejected.
 @discussion Submitting a task request with the same identifier as an existing request will replace that request.
 @return YES if the request was successfully submitted, NO if there was an error
 */
- (BOOL)submitTaskRequest:(BGTaskRequest *)taskRequest error:(NSError * _Nullable *)error;

/*!
 @abstract Cancel a previously submitted task request.
 @param identifier The identifier of the previously submitted task request to cancel.
 */
- (void)cancelTaskRequestWithIdentifier:(NSString *)identifier;

/*!
 @abstract Cancel all previously submitted task requests.
 */
- (void)cancelAllTaskRequests;

/*!
 @abstract Returns a list of all task requests that have been submitted but not yet completed.
 @param completionHandler A block for processing task requests. This block may be executed on a background thread. The block has no return value and takes a single parameter, taskRequests, which is an array of BGTaskRequest objects. If there are no pending requests, this array is empty. The task request objects returned are copies and changing their property values will have no immediate effect. To modify the parameters of a pending task request, submit it again to the scheduler with submitTaskRequest:error:.
 */
- (void)getPendingTaskRequestsWithCompletionHandler:(void (^)(NSArray<BGTaskRequest *> *taskRequests))completionHandler;

@end

NS_ASSUME_NONNULL_END
