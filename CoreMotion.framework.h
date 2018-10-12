// ==========  CoreMotion.framework/Headers/CMAuthorization.h
/*
 *  CMAuthorization.h
 *  CoreMotion
 *
 *  Copyright (c) 2017 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

/*
 *  CMAuthorizationStatus
 *
 *  Discussion:
 *      Represents the current motion authorization state.
 *
 *      CMAuthorizationStatusNotDetermined when the user has not been prompted yet.
 *      CMAuthorizationStatusRestricted when access is denied due to system-wide restrictions.
 *      CMAuthorizationStatusDenied when access is denied by the user.
 *      CMAuthorizationStatusAuthorized when access is authorized by the user.
 *
 */
typedef NS_ENUM(NSInteger, CMAuthorizationStatus) {
	CMAuthorizationStatusNotDetermined = 0,
	CMAuthorizationStatusRestricted,
	CMAuthorizationStatusDenied,
	CMAuthorizationStatusAuthorized
} NS_ENUM_AVAILABLE(NA, 11_0) __WATCHOS_AVAILABLE(4.0) API_UNAVAILABLE(tvos);
// ==========  CoreMotion.framework/Headers/CMErrorDomain.h
/*
 *  CMErrorDomain.h
 *  CoreMotion
 *
 *  Copyright (c) 2009-2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN
/*
 *  kCMErrorDomain
 *  
 *  Discussion:
 *    Error returned as the domain to NSError from CoreMotion.
 */
CM_EXTERN NSString *const CMErrorDomain NS_AVAILABLE(NA,4_0);

NS_ASSUME_NONNULL_END
// ==========  CoreMotion.framework/Headers/CMSensorRecorder.h
/*
 *  CMSensorRecorder.h
 *  CoreMotion
 *
 *  Copyright (c) 2015 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMAccelerometer.h>
#import <CoreMotion/CMAvailability.h>
#import <CoreMotion/CMAuthorization.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * CMRecordedAccelerometerData
 *
 * Discussion:
 *   CMRecordedAccelerometerData contains data for each accelerometer sample.
 */
NS_CLASS_AVAILABLE(NA, 9_0) __WATCHOS_AVAILABLE(2.0) API_UNAVAILABLE(tvos)
@interface CMRecordedAccelerometerData : CMAccelerometerData

/*
 * identifier
 *
 * Discussion:
 *   Unique identifier that identifies the batch for which the accelerometer sample
 *   was recorded in. This identifier will be monotonically increased
 *   for each new sensor batch recorded and can be used as an anchor for future queries.
 */
@property (readonly) uint64_t identifier;

/*
 * startDate
 *
 * Discussion:
 *   Wall time for when this sensor sample is recorded.
 *
 */
@property (readonly) NSDate *startDate;

@end

/*
 * CMSensorDataList
 *
 * Discussion:
 *   Allows retrospective access to sensor data via enumeration.
 *   If created with accelerometerDataFromDate:toDate:
 *   each enumeration will yield an object of type CMRecordedAccelerometerData.
 *   Due to the large number of samples that can be processed, the
 *   enumeration should not be run on the main/UI thread.
 */
NS_CLASS_AVAILABLE(NA, 9_0) __WATCHOS_AVAILABLE(2.0) API_UNAVAILABLE(tvos)
@interface CMSensorDataList : NSObject <NSFastEnumeration>
@end

/*
 * CMSensorRecorder
 *
 * Discussion:
 *    CMSensorRecorder allows applications to record sensor data for periods
 *    during which the application is not active.  This data is then made
 *    available for later access (up to 3 days) when the application
 *    is run at a later time.
 */
NS_CLASS_AVAILABLE(NA, 9_0) __WATCHOS_AVAILABLE(2.0) API_UNAVAILABLE(tvos)
@interface CMSensorRecorder : NSObject

/*
 * isAccelerometerRecordingAvailable
 *
 * Discussion:
 *   Determines whether accelerometer recording is available.
 */
+ (BOOL)isAccelerometerRecordingAvailable;

/*
 * authorizationStatus
 *
 * Discussion:
 *   Returns the current authorization status for sensor recording.
 */
+ (CMAuthorizationStatus)authorizationStatus NS_AVAILABLE(NA, 11_0) __WATCHOS_AVAILABLE(4_0);

/*
 * isAuthorizedForRecording
 *
 * Discussion:
 *   Determines whether the application is authorized for sensor recording.
 */
+ (BOOL)isAuthorizedForRecording __API_DEPRECATED_WITH_REPLACEMENT("authorizationStatus", ios(9_0, 11_0), watchos(2_0, 4_0));

/*
 * accelerometerDataFromDate:ToDate:
 *
 * Discussion:
 *    Gives access to recorded accelerometer samples given a time range (fromDate, toDate].
 *    A total duration of 12 hours of data can be requested at any one time.  Data can be delayed
 *    for up to 3 minutes before being available for retrieval.  An instance of CMSensorDataList
 *    should only be enumerated from a single thread.
 */
- (nullable CMSensorDataList *)accelerometerDataFromDate:(NSDate *)fromDate toDate:(NSDate *)toDate;

/*
 * recordAccelerometerForDuration:
 *
 * Discussion:
 *    Starts recording accelerometer data for the duration given at 50hz.  Data can be recorded
 *    for up to 12 hours.
 */
- (void)recordAccelerometerForDuration:(NSTimeInterval)duration;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreMotion.framework/Headers/CMMotionActivityManager.h
/*
 *  CMMotionActivityManager.h
 *  CoreMotion
 *
 *  Copyright (c) 2013 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMMotionActivity.h>
#import <CoreMotion/CMAvailability.h>
#import <CoreMotion/CMAuthorization.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMMotionActivityHandler
 *
 *  Discussion:
 *    Typedef of block to be invoked when the device's activity is updated.
 */
typedef void (^CMMotionActivityHandler)(CMMotionActivity * __nullable activity) NS_AVAILABLE(NA,7_0) API_UNAVAILABLE(tvos);

/*
 *  CMMotionActivityQueryHandler
 *
 *  Discussion:
 *    Typedef of block to be invoked when the historical activity query is
 *    completed.  The array is an array of CMMotionActivity objects.
 */
typedef void (^CMMotionActivityQueryHandler)(NSArray<CMMotionActivity *> * __nullable activities, NSError * __nullable error) NS_AVAILABLE(NA,7_0) API_UNAVAILABLE(tvos);

/*
 *   CMMotionActivityManager
 *
 *   Discussion:
 *      CMMotionActivityManager allows access to the activity of the device.
 *      Activities can be retrieved in one of two ways:
 *
 *      1. Via a query specifying a time range from which an array of
 *      activities will be returned.
 *
 *      2. By providing a queue and a block to startActivityUpdatesToQueue:withHandler:
 *      which will provide live activity updates to a running application.
 */
NS_CLASS_AVAILABLE(NA,7_0) API_UNAVAILABLE(tvos)
@interface CMMotionActivityManager : NSObject

/*
 *  isActivityAvailable
 *
 *  Discussion:
 *      Determines whether activity estimation is available.
 */
+ (BOOL)isActivityAvailable;

/*
 *  authorizationStatus
 *
 *  Discussion:
 *      Returns the current authorization status for activity.
 */
+ (CMAuthorizationStatus)authorizationStatus NS_AVAILABLE(NA, 11_0) __WATCHOS_AVAILABLE(4_0);

/*
 * queryActivityStartingFrom:to:toQueue:withHandler:
 *
 * Discussion:
 *      Queries for activity transitions that happened during the given time
 *      range.  The date range must be in the past.  Data is only available
 *      for the last seven days.  The result is returned to the handler/queue
 *      specified.
 *
 *      The first activity returned may have a startDate before start. This
 *      activity represents what the state was at the start time.
 *
 */
- (void)queryActivityStartingFromDate:(NSDate *)start
                               toDate:(NSDate *)end
                              toQueue:(NSOperationQueue *)queue
                          withHandler:(CMMotionActivityQueryHandler)handler;

/*
 *  startActivityUpdatesToQueue:withHandler
 *
 *  Discussion:
 *      Start activity updates, providing data to the given handler through
 *      the given queue.  An update with the current activity will arrive
 *      first.  Then when the activity state changes the handler will be
 *      called with the new activity.
 *
 *      You can only have one handler installed at a time, calling
 *      startActivityUpdatesToQueue:withHandler: replaces the current
 *      handler.
 *
 *      Updates are not delivered while the application is suspended, the
 *      application may use
 *      queryActivityStartingFromDate:toDate:toQueue:withHandler: to get
 *      activities from the time when the application was suspended.
 */
- (void)startActivityUpdatesToQueue:(NSOperationQueue *)queue
                        withHandler:(CMMotionActivityHandler)handler;

/*
 *  stopActivityUpdates
 *
 *  Discussion:
 *      Stop delivering live updates.
 */
- (void)stopActivityUpdates;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreMotion.framework/Headers/CMMotionManager.h
/*
 *  CMMotionManager.h
 *  CoreMotion
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

#import <CoreMotion/CMAccelerometer.h>
#import <CoreMotion/CMGyro.h>
#import <CoreMotion/CMDeviceMotion.h>
#import <CoreMotion/CMMagnetometer.h>

#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * There are two methods to receive data from CMMotionManager: push and pull.
 *
 * Before using either method, be sure to set the update interval property
 * appropriate to the type of data you're interested in. These properties are:
 * accelerometerUpdateInterval, gyroUpdateInterval, and deviceMotionUpdateInterval.
 *
 * To use the pull method, simply call startAccelerometerUpdates, startGyroUpdates,
 * and/or startDeviceMotionUpdates, depending on the type of data desired. Then,
 * whenever a new sample of data is desired, simply examine the appropriate
 * CMMotionManager property (accelerometerData, gyroData, or deviceMotion).
 *
 * To use the push method, simply call startAccelerometerUpdatesToQueue:withHandler:,
 * startGyroUpdatesToQueue:withHandler:, and/or
 * startDeviceMotionUpdatesToQueue:withHandler:, depending on the type of data
 * desired. You'll need to pass an NSOperationQueue and block to each call. When a new sample of
 * data arrives, a new instance of the block will be added to the appropriate NSOperationQueue.
 * When you stop the updates (see below), all operations in the given NSOperationQueue will be
 * cancelled, so it is recommended to pass CMMotionManager a queue that will not be used in other
 * contexts.
 *
 * Regardless of whether you used push or pull, when you're done, be sure to call the stop method
 * appropriate for the type of updates you started.  These methods are: stopAccelerometerUpdates,
 * stopGyroUpdates, and stopDeviceMotionUpdates.
 *
 */

/*
 *  CMAccelerometerHandler
 *
 *  Discussion:
 *    Typedef of block to be invoked when accelerometer data is available.
 */
typedef void (^CMAccelerometerHandler)(CMAccelerometerData * __nullable accelerometerData, NSError * __nullable error) API_UNAVAILABLE(tvos);

/*
 *  CMGyroHandler
 *
 *  Discussion:
 *    Typedef of block to be invoked when gyro data is available.
 */
typedef void (^CMGyroHandler)(CMGyroData * __nullable gyroData, NSError * __nullable error) API_UNAVAILABLE(tvos);

/*
 *  CMDeviceMotionHandler
 *
 *  Discussion:
 *    Typedef of block to be invoked when device motion data is available.
 */
typedef void (^CMDeviceMotionHandler)(CMDeviceMotion * __nullable motion, NSError * __nullable error) API_UNAVAILABLE(tvos);

/*
 *  CMMagnetometerHandler
 *
 *  Discussion:
 *    Typedef of block to be invoked when magnetometer data is available.
 */
typedef void (^CMMagnetometerHandler)(CMMagnetometerData * __nullable magnetometerData, NSError * __nullable error) NS_AVAILABLE(NA, 5_0) API_UNAVAILABLE(tvos);

/*
 *  CMMotionManager
 *
 *  Discussion:
 *    The CMMotionManager object is your entry point to the motion service.
 */
NS_CLASS_AVAILABLE(NA, 4_0)
@interface CMMotionManager : NSObject
{
@private
	id _internal;
}

/*
 *  accelerometerUpdateInterval
 *
 *  Discussion:
 *    The interval at which to deliver accelerometer data to the specified
 *    handler once startAccelerometerUpdatesToQueue:withHandler: is called.
 *    The units are in seconds. The value of this property is capped to
 *    certain minimum and maximum values. The maximum value is determined by
 *    the maximum frequency supported by the hardware. If sensitive to the
 *    interval of acceleration data, an application should always check the
 *    timestamps on the delivered CMAcceleration instances to determine the
 *    true update interval.
 */
@property(assign, nonatomic) NSTimeInterval accelerometerUpdateInterval API_UNAVAILABLE(tvos);

/*
 *  accelerometerAvailable
 *
 *  Discussion:
 *    Determines whether accelerometer is available.
 */
@property(readonly, nonatomic, getter=isAccelerometerAvailable) BOOL accelerometerAvailable API_UNAVAILABLE(tvos);

/*
 *  accelerometerActive
 *
 *  Discussion:
 *    Determines whether the CMMotionManager is currently providing
 *    accelerometer updates.
 */
@property(readonly, nonatomic, getter=isAccelerometerActive) BOOL accelerometerActive API_UNAVAILABLE(tvos);

/*
 *  accelerometerData
 *
 *  Discussion:
 *    Returns the latest sample of accelerometer data, or nil if none is available.
 */

@property(readonly, nullable) CMAccelerometerData *accelerometerData API_UNAVAILABLE(tvos);

/*
 *  startAccelerometerUpdates
 *
 *  Discussion:
 *    Starts accelerometer updates with no handler. To receive the latest accelerometer data
 *    when desired, examine the accelerometerData property.
 */
- (void)startAccelerometerUpdates API_UNAVAILABLE(tvos);

/*
 *  startAccelerometerUpdatesToQueue:withHandler:
 *
 *  Discussion:
 *    Starts accelerometer updates, providing data to the given handler through the given queue.
 *    Note that when the updates are stopped, all operations in the
 *    given NSOperationQueue will be cancelled.
 */
- (void)startAccelerometerUpdatesToQueue:(NSOperationQueue *)queue withHandler:(CMAccelerometerHandler)handler API_UNAVAILABLE(tvos);

/*
 *  stopAccelerometerUpdates
 *
 *  Discussion:
 *    Stop accelerometer updates.
 */
- (void)stopAccelerometerUpdates API_UNAVAILABLE(tvos);

/*
 *  gyroUpdateInterval
 *
 *  Discussion:
 *    The interval at which to deliver gyro data to the specified
 *    handler once startGyroUpdatesToQueue:withHandler: is called.
 *    The units are in seconds. The value of this property is capped to
 *    certain minimum and maximum values. The maximum value is determined by
 *    the maximum frequency supported by the hardware. If sensitive to the
 *    interval of gyro data, an application should always check the
 *    timestamps on the delivered CMGyroData instances to determine the
 *    true update interval.
 */
@property(assign, nonatomic) NSTimeInterval gyroUpdateInterval API_UNAVAILABLE(tvos);

/*
 *  gyroAvailable
 *
 *  Discussion:
 *    Determines whether gyro is available.
 */
@property(readonly, nonatomic, getter=isGyroAvailable) BOOL gyroAvailable API_UNAVAILABLE(tvos);

/*
 *  gyroActive
 *
 *  Discussion:
 *    Determines whether the CMMotionManager is currently providing gyro updates.
 */
@property(readonly, nonatomic, getter=isGyroActive) BOOL gyroActive API_UNAVAILABLE(tvos);

/*
 *  gyroData
 *
 *  Discussion:
 *    Returns the latest sample of gyro data, or nil if none is available.
 */
@property(readonly, nullable) CMGyroData *gyroData API_UNAVAILABLE(tvos);

/*
 *  startGyroUpdates
 *
 *  Discussion:
 *    Starts gyro updates with no handler. To receive the latest gyro data
 *    when desired, examine the gyroData property.
 */
- (void)startGyroUpdates API_UNAVAILABLE(tvos);

/*
 *  startGyroUpdatesToQueue:withHandler:
 *
 *  Discussion:
 *    Starts gyro updates, providing data to the given handler through the given queue.
 *    Note that when the updates are stopped, all operations in the
 *    given NSOperationQueue will be cancelled.

 */
- (void)startGyroUpdatesToQueue:(NSOperationQueue *)queue withHandler:(CMGyroHandler)handler API_UNAVAILABLE(tvos);

/*
 *  stopGyroUpdates
 *
 *  Discussion:
 *    Stops gyro updates.
 */
- (void)stopGyroUpdates API_UNAVAILABLE(tvos);

/*
 *  magnetometerUpdateInterval
 *
 *  Discussion:
 *    The interval at which to deliver magnetometer data to the specified
 *    handler once startMagnetometerUpdatesToQueue:withHandler: is called.
 *    The units are in seconds. The value of this property is capped to
 *    certain minimum and maximum values. The maximum value is determined by
 *    the maximum frequency supported by the hardware. If sensitive to the
 *    interval of magnetometer data, an application should always check the
 *    timestamps on the delivered CMMagnetometerData instances to determine the
 *    true update interval.
 */
@property(assign, nonatomic) NSTimeInterval magnetometerUpdateInterval NS_AVAILABLE(NA, 5_0) API_UNAVAILABLE(tvos);

/*
 *  magnetometerAvailable
 *
 *  Discussion:
 *    Determines whether magetometer is available.
 */
@property(readonly, nonatomic, getter=isMagnetometerAvailable) BOOL magnetometerAvailable NS_AVAILABLE(NA, 5_0) API_UNAVAILABLE(tvos);

/*
 *  magnetometerActive
 *
 *  Discussion:
 *    Determines whether the CMMotionManager is currently providing magnetometer updates.
 */
@property(readonly, nonatomic, getter=isMagnetometerActive) BOOL magnetometerActive NS_AVAILABLE(NA, 5_0) API_UNAVAILABLE(tvos);

/*
 *  magnetometerData
 *
 *  Discussion:
 *    Returns the latest sample of magnetometer data, or nil if none is available.
 */
@property(readonly, nullable) CMMagnetometerData *magnetometerData NS_AVAILABLE(NA, 5_0) API_UNAVAILABLE(tvos);

/*
 *  startMagnetometerUpdates
 *
 *  Discussion:
 *    Starts magnetometer updates with no handler. To receive the latest magnetometer data
 *    when desired, examine the magnetometerData property.
 */
- (void)startMagnetometerUpdates NS_AVAILABLE(NA, 5_0) API_UNAVAILABLE(tvos);

/*
 *  startMagnetometerUpdatesToQueue:withHandler:
 *
 *  Discussion:
 *    Starts magnetometer updates, providing data to the given handler through the given queue.
 */
- (void)startMagnetometerUpdatesToQueue:(NSOperationQueue *)queue withHandler:(CMMagnetometerHandler)handler NS_AVAILABLE(NA, 5_0) API_UNAVAILABLE(tvos);

/*
 *  stopMagnetometerUpdates
 *
 *  Discussion:
 *    Stops magnetometer updates.
 */
- (void)stopMagnetometerUpdates NS_AVAILABLE(NA, 5_0) API_UNAVAILABLE(tvos);

/*
 *  deviceMotionUpdateInterval
 *
 *  Discussion:
 *    The interval at which to deliver device motion data to the specified
 *    handler once startDeviceMotionUpdatesToQueue:withHandler: is called.
 *    The units are in seconds. The value of this property is capped to
 *    certain minimum and maximum values. The maximum value is determined by
 *    the maximum frequency supported by the hardware. If sensitive to the
 *    interval of device motion data, an application should always check the
 *    timestamps on the delivered CMDeviceMotion instances to determine the
 *    true update interval.
 */
@property(assign, nonatomic) NSTimeInterval deviceMotionUpdateInterval API_UNAVAILABLE(tvos);

/*
 *  availableAttitudeReferenceFrames
 *
 *  Discussion:
 *     Returns a bitmask specifying the available attitude reference frames on the device.
 */
+ (CMAttitudeReferenceFrame)availableAttitudeReferenceFrames NS_AVAILABLE(NA, 5_0) API_UNAVAILABLE(tvos);

/*
 *  attitudeReferenceFrame
 *
 *  Discussion:
 *    If device motion is active, returns the reference frame currently in-use.
 *    If device motion is not active, returns the default attitude reference frame
 *    for the device. If device motion is not available on the device, the value
 *    is undefined.
 *
 */
@property(readonly, nonatomic) CMAttitudeReferenceFrame attitudeReferenceFrame NS_AVAILABLE(NA, 5_0) API_UNAVAILABLE(tvos);

/*
 *  deviceMotionAvailable
 *
 *  Discussion:
 *    Determines whether device motion is available using any available attitude reference frame.
 */
@property(readonly, nonatomic, getter=isDeviceMotionAvailable) BOOL deviceMotionAvailable API_UNAVAILABLE(tvos);

/*
 *  deviceMotionActive
 *
 *  Discussion:
 *    Determines whether the CMMotionManager is currently providing device
 *    motion updates.
 */
@property(readonly, nonatomic, getter=isDeviceMotionActive) BOOL deviceMotionActive API_UNAVAILABLE(tvos);

/*
 *  deviceMotion
 *
 *  Discussion:
 *    Returns the latest sample of device motion data, or nil if none is available.
 */
@property(readonly, nullable) CMDeviceMotion *deviceMotion API_UNAVAILABLE(tvos);

/*
 *  startDeviceMotionUpdates
 *
 *  Discussion:
 *    Starts device motion updates with no handler. To receive the latest device motion data
 *    when desired, examine the deviceMotion property. Uses the default reference frame for
 *    the device. Examine CMMotionManager's attitudeReferenceFrame to determine this.
 */
- (void)startDeviceMotionUpdates API_UNAVAILABLE(tvos);

/*
 *  startDeviceMotionUpdatesToQueue:withHandler:
 *
 *  Discussion:
 *    Starts device motion updates, providing data to the given handler through the given queue.
 *    Uses the default reference frame for the device. Examine CMMotionManager's
 *    attitudeReferenceFrame to determine this.
 *
 */
- (void)startDeviceMotionUpdatesToQueue:(NSOperationQueue *)queue withHandler:(CMDeviceMotionHandler)handler API_UNAVAILABLE(tvos);

/*
 *  startDeviceMotionUpdatesUsingReferenceFrame:
 *
 *  Discussion:
 *    Starts device motion updates with no handler. To receive the latest device motion data
 *    when desired, examine the deviceMotion property. The specified frame will be used as
 *    reference for the attitude estimates.
 *
 */
- (void)startDeviceMotionUpdatesUsingReferenceFrame:(CMAttitudeReferenceFrame)referenceFrame NS_AVAILABLE(NA, 5_0) API_UNAVAILABLE(tvos);

/*
 *  startDeviceMotionUpdatesUsingReferenceFrame:toQueue:withHandler
 *
 *  Discussion:
 *    Starts device motion updates, providing data to the given handler through the given queue.
 *    The specified frame will be used as reference for the attitude estimates.
 *
 */
- (void)startDeviceMotionUpdatesUsingReferenceFrame:(CMAttitudeReferenceFrame)referenceFrame toQueue:(NSOperationQueue *)queue withHandler:(CMDeviceMotionHandler)handler NS_AVAILABLE(NA, 5_0) API_UNAVAILABLE(tvos);

/*
 *  stopDeviceMotionUpdates
 *
 *  Discussion:
 *    Stops device motion updates.
 */
- (void)stopDeviceMotionUpdates API_UNAVAILABLE(tvos);

/*
 *  showsDeviceMovementDisplay
 *
 *  Discussion:
 *    When the device requires movement, showsDeviceMovementDisplay indicates if the system device
 *    movement display should be shown. Note that when device requires movement,
 *    CMErrorDeviceRequiresMovement is reported once via CMDeviceMotionHandler. By default,
 *    showsDeviceMovementDisplay is NO.
 */
@property(assign, nonatomic) BOOL showsDeviceMovementDisplay NS_AVAILABLE(NA, 5_0) API_UNAVAILABLE(tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  CoreMotion.framework/Headers/CMGyro.h
/*
 *  CMGyro.h
 *  CoreMotion
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMLogItem.h>

#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMRotationRate
 *  
 *  Discussion:
 *    A structure containing 3-axis rotation rate data.
 *
 *  Fields:
 *    x:
 *      X-axis rotation rate in radians/second. The sign follows the right hand 
 *      rule (i.e. if the right hand is wrapped around the X axis such that the 
 *      tip of the thumb points toward positive X, a positive rotation is one 
 *      toward the tips of the other 4 fingers).
 *    y:
 *      Y-axis rotation rate in radians/second. The sign follows the right hand 
 *      rule (i.e. if the right hand is wrapped around the Y axis such that the 
 *      tip of the thumb points toward positive Y, a positive rotation is one 
 *      toward the tips of the other 4 fingers).
 *		z:
 *			Z-axis rotation rate in radians/second. The sign follows the right hand 
 *      rule (i.e. if the right hand is wrapped around the Z axis such that the 
 *      tip of the thumb points toward positive Z, a positive rotation is one 
 *      toward the tips of the other 4 fingers).
 */
typedef struct {
	double x;
	double y;
	double z;	
} CMRotationRate;

/*
 *  CMGyroData
 *
 *  Discussion:
 *    Contains a single gyro measurement.
 *
 */
NS_CLASS_AVAILABLE(NA,4_0) API_UNAVAILABLE(tvos)
@interface CMGyroData : CMLogItem
{
@private
	id _internal;
}

/*
 *  rotationRate
 *  
 *  Discussion:
 *    The rotation rate as measured by the gyro.
 *
 */
@property(readonly, nonatomic) CMRotationRate rotationRate;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreMotion.framework/Headers/CMMovementDisorderManager.h
//
//  CMMovementDisorderManager.h
//  CoreMotion
//
//  Copyright (c) 2018 Apple Inc. All rights reserved.
//

#import <CoreMotion/CMAvailability.h>
#import <CoreMotion/CMAuthorization.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class CMDyskineticSymptomResult
 * @discussion A CMDyskineticSymptomResult object describes the presence and prevalence of dyskinetic symptoms (specifically, choreiform movements) during a one minute result period when subjects wear the Apple Watch on their most affected arm.
 * percentUnlikely + percentLikely = 1.0
 * Please note dyskinetic symptom measurements are designed for subjects with known presence of chorea in the arm and should not be displayed to users who do not report episodes of dyskinetic symptoms.
 */
API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos, tvos)
@interface CMDyskineticSymptomResult : NSObject <NSCopying, NSSecureCoding>

/*!
 * @brief The date and time representing the start of the result.
 */
@property (copy, nonatomic, readonly) NSDate *startDate;

/*!
 * @brief The date and time representing the end of the result.
 */
@property (copy, nonatomic, readonly) NSDate *endDate;

/*!
 * @brief The percentage of time dyskinetic symptoms were unlikely for the result.
 */
@property (nonatomic, readonly) float percentUnlikely;

/*!
 * @brief The percentage of time dyskinetic symptoms were likely for the result.
 */
@property (nonatomic, readonly) float percentLikely;

@end

/*!
 * @class CMTremorResult
 * @discussion A CMTremorResult object describes the presence and prevalence of tremor symptoms (specifically, resting tremor) during a one minute result period when subjects wear the Apple Watch on their most affected arm.
 * percentUnknown + percentNoTremor + percentTremorSlight + percentTremorMild + percentTremorModerate + percentTremorStrong = 1.0
 */
API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos, tvos)
@interface CMTremorResult : NSObject <NSCopying, NSSecureCoding>

/*!
 * @brief The date and time representing the start of the result.
 */
@property (copy, nonatomic, readonly) NSDate *startDate;

/*!
 * @brief The date and time representing the end of the result.
 */
@property (copy, nonatomic, readonly) NSDate *endDate;

/*!
 * @discussion The percentage of time tremor was unknown for the result.
 * Unknown periods include times when:
 *   1. the subject is moving and therefore a resting tremor cannot be assessed, and
 *   2. the signal strength is too low to measure tremor confidently.
 */
@property (nonatomic, readonly) float percentUnknown;

/*!
 * @brief The percentage of time no tremor was detected for the result.
 */
@property (nonatomic, readonly) float percentNone;

/*!
 * @brief The percentage of time tremor was likely and displacement amplitude was slight for the result.
 */
@property (nonatomic, readonly) float percentSlight;

/*!
 * @brief The percentage of time tremor was likely and displacement amplitude was mild for the result.
 */
@property (nonatomic, readonly) float percentMild;

/*!
 * @brief The percentage of time tremor was likely and displacement amplitude was moderate for the result.
 */
@property (nonatomic, readonly) float percentModerate;

/*!
 * @brief The percentage of time tremor was likely and displacement amplitude was strong for the result.
 */
@property (nonatomic, readonly) float percentStrong;

@end

/*!
 * @typedef CMDyskineticSymptomResultHandler
 * @brief Completion handler for CMDyskineticSymptomResult values.
 */
typedef void(^CMDyskineticSymptomResultHandler)(NSArray<CMDyskineticSymptomResult *> * _Nonnull dyskineticSymptomResult, NSError * _Nullable error) API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios, macos, tvos);

/*!
 * @typedef CMTremorResultHandler
 * @brief Completion handler for CMTremorResult values.
 */
typedef void(^CMTremorResultHandler)(NSArray<CMTremorResult *> * _Nonnull tremorResult, NSError * _Nullable error) API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios, macos, tvos);

/*!
 * @class CMMovementDisorderManager
 * @discussion A CMMovementDisorderManager object with methods for persistence and query of movement disorder results.
 */
API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios, macos, tvos)
@interface CMMovementDisorderManager : NSObject

/*!
 * @method isAvailable
 * @discussion Whether movement disorder results are available on this platform.
 * @return Returns the availability of movement disorder results on this platform.
 */
+ (BOOL)isAvailable;

/*!
 * @method authorizationStatus
 * @discussion Authorization status of movement disorder results for this user.
 * @return Returns the authorization status of movement disorder results for this user.
 */
+ (CMAuthorizationStatus)authorizationStatus;

/*!
 * @method monitorKinesiasForDuration:
 * @discussion Enables the calculation and persistence of result values for the specified duration in seconds.
 * @param duration The duration in seconds to enable the calculation and persistence of result values.
 * @warning Please note that the maximum duration allowed is seven (7) days.
 */
- (void)monitorKinesiasForDuration:(NSTimeInterval)duration;

/*!
 * @method queryDyskineticSymptomFromDate:toDate:withHandler:
 * @discussion Queries the system for result values for the specified date range.
 * @param fromDate The begin date for the query range.
 * @param toDate The end date for the query range.
 * @param handler The completion handler for accessing and processing result values.
 * @warning Please note that movement disorder results are available for a maximum of seven (7) days.
 */
- (void)queryDyskineticSymptomFromDate:(NSDate *)fromDate toDate:(NSDate *)toDate withHandler:(CMDyskineticSymptomResultHandler)handler;

/*!
 * @method queryTremorFromDate:toDate:withHandler:
 * @discussion Queries the system for result values for the specified date range.
 * @param fromDate The begin date for the query range.
 * @param toDate The end date for the query range.
 * @param handler The completion handler for accessing and processing result values.
 * @warning Please note that movement disorder results are available for a maximum of seven (7) days.
 */
- (void)queryTremorFromDate:(NSDate *)fromDate toDate:(NSDate *)toDate withHandler:(CMTremorResultHandler)handler;

/*!
 * @method lastProcessedDate
 * @discussion The last time that data has been processed; queries for periods before this point will return their final results. Data after this point may become available later if monitoring is continuing.
 * @warning Returns nil if no data has been processed or monitoring was not enabled.
 */
- (NSDate * _Nullable)lastProcessedDate;

/*!
 * @method monitorKinesiasExpirationDate
 * @discussion The expiration date for the most recent monitoring period.
 * @warning Returns nil if no previous monitoring period is available.
 */
- (NSDate * _Nullable)monitorKinesiasExpirationDate;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreMotion.framework/Headers/CMError.h
/*
 *  CMError.h
 *  CoreMotion
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 */

/*
 *  CMError
 *
 *  Discussion:
 *    Error returned as code to NSError from CoreMotion.
 */
typedef enum {
	CMErrorNULL = 100,
	CMErrorDeviceRequiresMovement,
	CMErrorTrueNorthNotAvailable,
	CMErrorUnknown,
	CMErrorMotionActivityNotAvailable,
	CMErrorMotionActivityNotAuthorized,
	CMErrorMotionActivityNotEntitled,
	CMErrorInvalidParameter,
	CMErrorInvalidAction,
	CMErrorNotAvailable,
	CMErrorNotEntitled,
	CMErrorNotAuthorized
} CMError;
// ==========  CoreMotion.framework/Headers/CMAltitude.h
/*
 *  CMAltitude.h
 *  CoreMotion
 *
 *  Copyright (c) 2014 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMLogItem.h>
#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMAltitudeData
 *
 *  Discussion:
 *      Contains a single altimeter measurement.
 */
NS_CLASS_AVAILABLE(NA, 8_0) API_UNAVAILABLE(tvos)
@interface CMAltitudeData : CMLogItem

/*
 *  relativeAltitude
 *
 *  Discussion:
 *    The relative altitude in meters to the starting altitude.
 *
 */
@property(readonly, nonatomic) NSNumber *relativeAltitude;

/*
 *  pressure
 *
 *  Discussion:
 *    The pressure in kPa.
 *
 */
@property(readonly, nonatomic) NSNumber *pressure;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreMotion.framework/Headers/CMStepCounter.h
/*
 *  CMStepCounter.h
 *  CoreMotion
 *
 *  Copyright (c) 2013 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMStepQueryHandler
 *
 *  Discussion:
 *    Typedef of block to be invoked when the step count query is completed.
 */
typedef void (^CMStepQueryHandler)(NSInteger numberOfSteps, NSError * __nullable error) API_UNAVAILABLE(watchos, tvos);

/*
 *  CMStepUpdateHandler
 *
 *  Discussion:
 *      Typedef of block to be invoked on every update.  The total step count since startStepCountingUpdatesToQueue
 *      was called along with the timestamp associated with the latest determination will be returned.
 */
typedef void (^CMStepUpdateHandler)(NSInteger numberOfSteps, NSDate *timestamp, NSError * __nullable error) API_UNAVAILABLE(watchos, tvos);

/*
 *  CMStepCounter
 *
 *  Discussion:
 *      CMStepCounter allows access to the approximate number of steps a user has taken
 *      with a device.  Steps can be retrieved in one of two ways:
 *
 *      1. Via a query specifying a time range from which the approximate number of steps is
 *      tabulated and returned. (See queryStepCountStartingFrom:to:toQueue:withHandler)
 *
 *      2. By providing a queue and a block to startStepCountingUpdatesToQueue:withHandler,
 *      step count updates will be provided on a best effort basis.  Each update will return a
 *      monotonically increasing number of steps counted since
 *      startStepCountingUpdatesToQueue:withHandler was called and a timestamp
 *      associated with the latest stepcount determination.  Step count updates can be stopped
 *      by either calling stopStepCountingUpdates or upon CMStepCounter deallocation.
 *
 */
NS_CLASS_DEPRECATED_IOS(7_0,8_0,"Use CMPedometer instead") API_UNAVAILABLE(watchos, tvos)
@interface CMStepCounter : NSObject

/*
 *  isStepCountingAvailable
 *
 *  Discussion:
 *      Determines whether the device supports step counting.
 */
+ (BOOL)isStepCountingAvailable;

/*
 *  queryStepCountStartingFrom:to:toQueue:withHandler
 *
 *  Discussion:
 *      Queries for the approximate number of steps taken in the given time range, for up to 7 days.
 *      The step count returned is computed from a system wide history that is continuously being
 *      collected in the background.  The result is returned to the handler/queue specified.
 */
- (void)queryStepCountStartingFrom:(NSDate *)start
                                to:(NSDate *)end
                           toQueue:(NSOperationQueue *)queue
                       withHandler:(CMStepQueryHandler)handler;

/*
 *  startStepCountingUpdatesToQueue:withHandler
 *
 *  Discussion:
 *       Starts a series of continuous step counting updates to the handler on the designated queue.  For each
 *       update, the app will receive the total step count since this method was called (this includes
 *       subsequent calls) and the timestamp associated with the latest determination.  If the app is backgrounded
 *       and resumed at a later time, the app will receive all of the steps counted during the background
 *       period in the very next update.  The handler will be called when the number of steps (as defined by
 *       the user) has been detected on a best effort basis.
 */
- (void)startStepCountingUpdatesToQueue:(NSOperationQueue *)queue
                               updateOn:(NSInteger)stepCounts
                            withHandler:(CMStepUpdateHandler)handler;


/*
 *  stopStepCountingUpdates
 *
 *  Discussion:
 *      Stops step counting updates.  Upon deallocation of CMStepCounter, this function will be
 *      automatically invoked if updates are still active and stopStepCountingUpdates has not been
 *      called.
 */
- (void)stopStepCountingUpdates;

@end

NS_ASSUME_NONNULL_END

// ==========  CoreMotion.framework/Headers/CoreMotion.h
/*
 *  CoreMotion.h
 *  CoreMotion
 *
 *  Copyright (c) 2014 Apple Inc. All rights reserved.
 *
 */


#ifndef __COREMOTION__
#define __COREMOTION__

#import <CoreMotion/CMAccelerometer.h>
#import <CoreMotion/CMAltimeter.h>
#import <CoreMotion/CMAltitude.h>
#import <CoreMotion/CMAttitude.h>
#import <CoreMotion/CMAuthorization.h>
#import <CoreMotion/CMAvailability.h>
#import <CoreMotion/CMDeviceMotion.h>
#import <CoreMotion/CMError.h>
#import <CoreMotion/CMErrorDomain.h>
#import <CoreMotion/CMGyro.h>
#import <CoreMotion/CMLogItem.h>
#import <CoreMotion/CMMagnetometer.h>
#import <CoreMotion/CMMotionActivity.h>
#import <CoreMotion/CMMotionActivityManager.h>
#import <CoreMotion/CMMotionManager.h>
#import <CoreMotion/CMMovementDisorderManager.h>
#import <CoreMotion/CMPedometer.h>
#import <CoreMotion/CMStepCounter.h>
#import <CoreMotion/CMSensorRecorder.h>

#endif /* __COREMOTION__ */
// ==========  CoreMotion.framework/Headers/CMDeviceMotion.h
/*
 *  CMDeviceMotion.h
 *  CoreMotion
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 */

#import <CoreMotion/CMAccelerometer.h>
#import <CoreMotion/CMAttitude.h>
#import <CoreMotion/CMGyro.h>
#import <CoreMotion/CMMagnetometer.h>

#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMMagneticFieldCalibrationAccuracy
 *
 *  Discussion:
 *    CMMagneticFieldCalibrationAccuracy indicates the calibration
 *    accuracy of a magnetic field estimate.
 *
 */
typedef NS_ENUM(int, CMMagneticFieldCalibrationAccuracy) {
	CMMagneticFieldCalibrationAccuracyUncalibrated = -1,
	CMMagneticFieldCalibrationAccuracyLow,
	CMMagneticFieldCalibrationAccuracyMedium,
	CMMagneticFieldCalibrationAccuracyHigh
} ;

/*
 *  CMCalibratedMagneticField
 *
 *  Discussion:
 *    A structure containing 3-axis calibrated magnetic field data
 *    and an estimate of the accuracy of the calibration
 *
 *  Fields:
 *    field:
 *      The 3-axis calibrated magnetic field vector.
 *    accuracy:
 *      An estimate of the calibration accuracy.
 */
typedef struct {
    CMMagneticField field;
    CMMagneticFieldCalibrationAccuracy accuracy;
} CMCalibratedMagneticField;


/*
 *  CMDeviceMotion
 *
 *  Discussion:
 *    A CMDeviceMotion object contains basic information about the device's
 *    motion.
 */
NS_CLASS_AVAILABLE(NA, 4_0) API_UNAVAILABLE(tvos)
@interface CMDeviceMotion : CMLogItem
{
@private
	id _internal;
}

/*
 *  attitude
 *
 *  Discussion:
 *    Returns the attitude of the device.
 *
 */
@property(readonly, nonatomic) CMAttitude *attitude;

/*
 *  rotationRate
 *
 *  Discussion:
 *    Returns the rotation rate of the device for devices with a gyro.
 *
 */
@property(readonly, nonatomic) CMRotationRate rotationRate;

/*
 *  gravity
 *
 *  Discussion:
 *    Returns the gravity vector expressed in the device's reference frame. Note
 *    that the total acceleration of the device is equal to gravity plus
 *    userAcceleration.
 *
 */
@property(readonly, nonatomic) CMAcceleration gravity;

/*
 *  userAcceleration
 *
 *  Discussion:
 *    Returns the acceleration that the user is giving to the device. Note
 *    that the total acceleration of the device is equal to gravity plus
 *    userAcceleration.
 *
 */
@property(readonly, nonatomic) CMAcceleration userAcceleration;

/*
 *  magneticField
 *
 *  Discussion:
 *    Returns the magnetic field vector with respect to the device for devices with a magnetometer.
 *    Note that this is the total magnetic field in the device's vicinity without device
 *    bias (Earth's magnetic field plus surrounding fields, without device bias),
 *    unlike CMMagnetometerData magneticField.
 */
@property(readonly, nonatomic) CMCalibratedMagneticField magneticField NS_AVAILABLE(NA, 5_0);

/*
 *  heading
 *
 *  Discussion:
 *    Returns heading angle in the range [0,360) degrees with respect to the CMAttitude reference frame. A negative value is returned
 *    for CMAttitudeReferenceFrameXArbitraryZVertical and CMAttitudeReferenceFrameXArbitraryCorrectedZVertical.
 *
 */
@property(readonly, nonatomic) double heading NS_AVAILABLE(NA, 11_0);

@end

NS_ASSUME_NONNULL_END
// ==========  CoreMotion.framework/Headers/CMAltimeter.h
/*
 *  CMAltimeter.h
 *  CoreMotion
 *
 *  Copyright (c) 2014 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMAltitude.h>
#import <CoreMotion/CMAvailability.h>
#import <CoreMotion/CMAuthorization.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMAltitudeHandler
 *
 *  Discussion:
 *    Typedef of block to be invoked when the device's altitude is updated.
 */
typedef void (^CMAltitudeHandler)(CMAltitudeData * __nullable altitudeData, NSError * __nullable error) NS_AVAILABLE(NA,8_0) API_UNAVAILABLE(tvos);

/*
 *  CMAltimeter
 *
 *  Discussion:
 *		CMAltimeter provides information about the altitude of the device.
 */
NS_CLASS_AVAILABLE(NA,8_0) API_UNAVAILABLE(tvos)
@interface CMAltimeter : NSObject

/*
 *  isRelativeAltitudeAvailable
 *
 *  Discussion:
 *		Determines whether the device supports reporting relative altitude changes.
 */
+ (BOOL)isRelativeAltitudeAvailable;

/*
 *  authorizationStatus
 *
 *  Discussion:
 *		Returns the current authorization status for altimeter.
 */
+ (CMAuthorizationStatus)authorizationStatus NS_AVAILABLE(NA, 11_0) __WATCHOS_AVAILABLE(4_0);

/*
 *  startRelativeAltitudeUpdatesToQueue:withHandler:
 *
 *  Discussion:
 *		Starts relative altitude updates, providing data to the given handler on the given queue
 *		every few seconds. The first altitude update will be established as the reference altitude
 *		and have relative altitude 0.
 *
 *		Calls to start must be balanced with calls to stopRelativeAltitudeUpdates even if an error
 *		is returned to the handler.
 */
- (void)startRelativeAltitudeUpdatesToQueue:(NSOperationQueue *)queue withHandler:(CMAltitudeHandler)handler;

/*
 *  stopRelativeAltitudeUpdates
 *
 *  Discussion:
 *      Stops relative altitude updates.
 */
- (void)stopRelativeAltitudeUpdates;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreMotion.framework/Headers/CMAvailability.h
/*
 *  CMAvailability.h
 *  CoreMotion
 *
 *  Copyright (c) 2013 Apple Inc. All rights reserved.
 *
 */

#import <Availability.h>
#import <os/availability.h>

#ifdef __cplusplus
#define CM_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define CM_EXTERN extern __attribute__((visibility ("default")))
#endif

#define COREMOTION_EXPORT __attribute__((visibility ("default")))
// ==========  CoreMotion.framework/Headers/CMAccelerometer.h
/*
 *  CMAccelerometer.h
 *  CoreMotion
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMLogItem.h>

#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMAcceleration
 *  
 *  Discussion:
 *    A structure containing 3-axis acceleration data.
 *
 *  Fields:
 *    x:
 *      X-axis acceleration in G's.
 *    y:
 *      Y-axis acceleration in G's.
 *		z:
 *			Z-axis acceleration in G's.
 */
typedef struct {
	double x;
	double y;
	double z;
} CMAcceleration;

/*
 *  CMAccelerometerData
 *  
 *  Discussion:
 *    Contains a single accelerometer measurement.
 *
 */
NS_CLASS_AVAILABLE(NA,4_0) API_UNAVAILABLE(tvos)
@interface CMAccelerometerData : CMLogItem
{
@private
	id _internal;
}

/*
 *  acceleration
 *  
 *  Discussion:
 *    The acceleration measured by the accelerometer.
 *
 */
@property(readonly, nonatomic) CMAcceleration acceleration;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreMotion.framework/Headers/CMLogItem.h
/*
 *  CMLogItem.h
 *  CoreMotion
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(NA,4_0)
@interface CMLogItem : NSObject <NSSecureCoding, NSCopying>
{
@private
	id _internalLogItem;
}

/*
 *  timestamp
 *  
 *  Discussion:
 *    Time at which the item is valid.
 *
 */
@property(readonly, nonatomic) NSTimeInterval timestamp;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreMotion.framework/Headers/CMAttitude.h
/*
 *  CMAttitude.h
 *  CoreMotion
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMRotationMatrix
 *  
 *  Discussion:
 *    Type represents a rotation matrix.
 */
typedef struct 
{
	double m11, m12, m13;
	double m21, m22, m23;
	double m31, m32, m33;
} CMRotationMatrix;

/*
 *  CMQuaternion
 *  
 *  Discussion:
 *    Type represents a quaternion (one way of parameterizing attitude). If q
 *		is an instance of CMQuaternion, mathematically it represents the 
 *		following quaternion:
 *		q.x*i + q.y*j + q.z*k + q.w
 *		
 */
typedef struct
{
	double x, y, z, w;
} CMQuaternion;

/*
 *  CMAttitudeReferenceFrame
 *  
 *  Discussion:
 *    CMAttitudeReferenceFrame indicates the reference frame from which all CMAttitude
 *        samples are referenced.
 *
 *    Definitions of each reference frame is as follows:
 *        - CMAttitudeReferenceFrameXArbitraryZVertical describes a reference frame in
 *          which the Z axis is vertical and the X axis points in an arbitrary direction
 *          in the horizontal plane.
 *        - CMAttitudeReferenceFrameXArbitraryCorrectedZVertical describes the same reference
 *          frame as CMAttitudeReferenceFrameXArbitraryZVertical with the following exception:
 *          when available and calibrated, the magnetometer will be used to correct for accumulated
 *          yaw errors. The downside of using this over CMAttitudeReferenceFrameXArbitraryZVertical
 *          is increased CPU usage.
 *        - CMAttitudeReferenceFrameXMagneticNorthZVertical describes a reference frame
 *          in which the Z axis is vertical and the X axis points toward magnetic north.
 *          Note that using this reference frame may require device movement to 
 *          calibrate the magnetometer.
 *        - CMAttitudeReferenceFrameXTrueNorthZVertical describes a reference frame in
 *          which the Z axis is vertical and the X axis points toward true north.
 *          Note that using this reference frame may require device movement to 
 *          calibrate the magnetometer.
 */
typedef NS_OPTIONS(NSUInteger, CMAttitudeReferenceFrame) API_UNAVAILABLE(tvos) {
	CMAttitudeReferenceFrameXArbitraryZVertical = 1 << 0,
	CMAttitudeReferenceFrameXArbitraryCorrectedZVertical = 1 << 1,
	CMAttitudeReferenceFrameXMagneticNorthZVertical = 1 << 2,
	CMAttitudeReferenceFrameXTrueNorthZVertical = 1 << 3
};

NS_CLASS_AVAILABLE(NA,4_0) API_UNAVAILABLE(tvos)
@interface CMAttitude : NSObject <NSCopying, NSSecureCoding>
{
@private
	id _internal;
}

/*
 *  roll
 *  
 *  Discussion:
 *    Returns the roll of the device in radians.
 *
 */
@property(readonly, nonatomic) double roll;

/*
 *  pitch
 *  
 *  Discussion:
 *    Returns the pitch of the device in radians.
 *
 */
@property(readonly, nonatomic) double pitch;

/*
 *  yaw
 *  
 *  Discussion:
 *    Returns the yaw of the device in radians.
 *
 */
@property(readonly, nonatomic) double yaw;

/*
 *  rotationMatrix
 *  
 *  Discussion:
 *    Returns a rotation matrix representing the device's attitude.
 *
 */
@property(readonly, nonatomic) CMRotationMatrix rotationMatrix;

/*
 *  quaternion
 *  
 *  Discussion:
 *    Returns a quaternion representing the device's attitude.
 *
 */
@property(readonly, nonatomic) CMQuaternion quaternion;

/*
 *  multiplyByInverseOfAttitude:
 *  
 *  Discussion:
 *      Multiplies attitude by the inverse of the specified attitude. This gives
 *			the attitude change from the specified attitude.
 */
- (void)multiplyByInverseOfAttitude:(CMAttitude *)attitude;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreMotion.framework/Headers/CMMagnetometer.h
/*
 *  CMMagnetometer.h
 *  CoreMotion
 *
 *  Copyright (c) 2011 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMLogItem.h>

#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMMagneticField
 *  
 *  Discussion:
 *    A structure containing 3-axis magnetometer data.
 *
 *  Fields:
 *    x:
 *      X-axis magnetic field in microteslas.
 *    y:
 *      Y-axis magnetic field in microteslas.
 *    z:
 *      Z-axis magnetic field in microteslas.
 */
typedef struct {
    double x;
    double y;
    double z;
} CMMagneticField;

/*
 *  CMMagnetometerData
 *  
 *  Discussion:
 *    Contains a single magnetometer measurement.
 */
NS_CLASS_AVAILABLE(NA,5_0) API_UNAVAILABLE(tvos)
@interface CMMagnetometerData : CMLogItem
{
@private
    id _internal;
}

/*
 *  magneticField
 *  
 *  Discussion:
 *    Returns the magnetic field measured by the magnetometer. Note
 *        that this is the total magnetic field observed by the device which
 *        is equal to the Earth's geomagnetic field plus bias introduced
 *        from the device itself and its surroundings.
 */
@property(readonly, nonatomic) CMMagneticField magneticField;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreMotion.framework/Headers/CMMotionActivity.h
/*
 *  CMMotionActivity.h
 *  CoreMotion
 *
 *  Copyright (c) 2013 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMLogItem.h>

#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMMotionActivityConfidence
 *
 *  Discussion:
 *    Enumerates the level of accuracy of the activity estimate.
 */
typedef NS_ENUM(NSInteger, CMMotionActivityConfidence) {
	CMMotionActivityConfidenceLow = 0,
	CMMotionActivityConfidenceMedium,
	CMMotionActivityConfidenceHigh
};

/*
 *  CMMotionActivity
 *
 *  Discussion:
 *    An estimate of the user's activity based on the motion of the device.
 *
 *    The activity is exposed as a set of properties, the properties are not
 *    mutually exclusive.
 *
 *    For example, if you're in a car stopped at a stop sign the state might
 *    look like:
 *       stationary = YES, walking = NO, running = NO, automotive = YES
 *
 *    Or a moving vehicle,
 *       stationary = NO, walking = NO, running = NO, automotive = YES
 *
 *    Or the device could be in motion but not walking or in a vehicle.
 *       stationary = NO, walking = NO, running = NO, automotive = NO.
 *    Note in this case all of the properties are NO.
 *
 */
NS_CLASS_AVAILABLE(NA, 7_0) API_UNAVAILABLE(tvos)
@interface CMMotionActivity : CMLogItem

/*
 *  confidence
 *
 *  Discussion:
 *    A confidence estimate associated with this state.
 *
 *    CoreMotion always provides the most likely state.  Confidence represents
 *    how likely that the state is to be correct.
 */
@property(readonly, nonatomic) CMMotionActivityConfidence confidence;

/*
 *  startDate
 *
 *  Discussion:
 *    Time at which the activity started.
 */
@property(readonly, nonatomic) NSDate *startDate;

/*
 *  unknown
 *
 *  Discussion:
 *    True if there is no estimate of the current state.  This can happen if
 *    the device was turned off.
 */
@property(readonly, nonatomic) BOOL unknown;

/*
 *  stationary
 *
 *  Discussion:
 *    True if the device is not moving.
 */
@property(readonly, nonatomic) BOOL stationary;

/*
 *  walking
 *
 *  Discussion:
 *    True if the device is on a walking person.
 */
@property(readonly, nonatomic) BOOL walking;

/*
 *  running
 *
 *  Discussion:
 *    True if the device is on a running person.
 */
@property(readonly, nonatomic) BOOL running;

/*
 *  automotive
 *
 *  Discussion:
 *    True if the device is in a vehicle.
 */
@property(readonly, nonatomic) BOOL automotive;

/*
 *  cycling
 *
 *  Discussion:
 *    True if the device is on a bicycle.
 */
@property(readonly, nonatomic) BOOL cycling NS_AVAILABLE(NA, 8_0);

@end

NS_ASSUME_NONNULL_END
// ==========  CoreMotion.framework/Headers/CMPedometer.h
/*
 *  CMPedometer.h
 *  CoreMotion
 *
 *  Copyright (c) 2013 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMAvailability.h>
#import <CoreMotion/CMAuthorization.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMPedometerData
 *
 *  Discussion:
 *      A description of the user's pedestrian activity. At a minimum this
 *      object contains a step count. On supported platforms it also contains
 *      distance, flights of stairs, pace, and cadence.
 */
NS_CLASS_AVAILABLE(NA, 8_0) API_UNAVAILABLE(tvos)
@interface CMPedometerData : NSObject <NSSecureCoding, NSCopying>

/*
 *  startDate
 *
 *  Discussion:
 *      The start time of the period for which the pedometer data is valid.
 *
 *      This is the start time requested for the session or historical query.
 */
@property(readonly, nonatomic) NSDate *startDate;

/*
 *  endDate
 *
 *  Discussion:
 *      The end time of the period for which the pedometer data is valid.
 *
 *      For updates this is the time for the most recent update. For historical
 *      queries this is the end time requested.
 */
@property(readonly, nonatomic) NSDate *endDate;

/*
 *  numberOfSteps
 *
 *  Discussion:
 *      Number of steps taken by the user.
 */
@property(readonly, nonatomic) NSNumber *numberOfSteps;

/*
 *  distance
 *
 *  Discussion:
 *      Estimated distance in meters traveled by the user while walking and
 *      running. Value is nil unsupported platforms.
 */
@property(readonly, nonatomic, nullable) NSNumber *distance;

/*
 *  floorsAscended
 *
 *  Discussion:
 *      Approximate number of floors ascended by way of stairs. Value is nil
 *      on unsupported platforms.
 *
 */
@property(readonly, nonatomic, nullable) NSNumber *floorsAscended;

/*
 *  floorsDescended
 *
 *  Discussion:
 *      Approximate number of floors descended by way of stairs. Value is nil
 *      on unsupported platforms.
 */
@property(readonly, nonatomic, nullable) NSNumber *floorsDescended;

/*
 * currentPace
 *
 *
 * Discussion:
 *      For updates this returns the current pace, in s/m (seconds per meter).
 *      Value is nil if any of the following are true:
 *
 *         (1) Information not yet available;
 *         (2) Historical query;
 *         (3) Unsupported platform.
 *
 */
@property(readonly, nonatomic, nullable) NSNumber *currentPace NS_AVAILABLE(NA,9_0);

/*
 * currentCadence
 *
 *
 * Discussion:
 *      For updates this returns the rate at which steps are taken, in steps per second.
 *      Value is nil if any of the following are true:
 *
 *         (1) Information not yet available;
 *         (2) Historical query;
 *         (3) Unsupported platform.
 *
 */
@property(readonly, nonatomic, nullable) NSNumber *currentCadence NS_AVAILABLE(NA,9_0);

/*
 * averageActivePace
 *
 *
 * Discussion:
 *
 *      For updates this returns the average active pace since
 *      startPedometerUpdatesFromDate:withHandler:, in s/m (seconds per meter).
 *      For historical queries this returns average active pace between startDate
 *      and endDate. The average active pace omits the non-active time, giving
 *      the average pace from when the user was moving. Value is nil if any of
 *      the following are true:
 *
 *         (1) (For historical queries) this information is not available,
 *             e.g. the user did not move between startDate and endDate;
 *         (2) Unsupported platform.
 *
 */
@property(readonly, nonatomic, nullable) NSNumber *averageActivePace NS_AVAILABLE(NA,10_0);

@end

/*
 *  CMPedometerEventType
 *
 *  Discussion:
 *      Events describing the transitions of pedestrian activity.
 */
typedef NS_ENUM(NSInteger, CMPedometerEventType) {
	CMPedometerEventTypePause,
	CMPedometerEventTypeResume
} NS_ENUM_AVAILABLE(NA, 10_0) __WATCHOS_AVAILABLE(3_0) API_UNAVAILABLE(tvos);

/*
 *  CMPedometerEvent
 *
 *  Discussion:
 *      An event marking the change in user's pedestrian activity.
 */
NS_CLASS_AVAILABLE(NA, 10_0) __WATCHOS_AVAILABLE(3_0) API_UNAVAILABLE(tvos)
@interface CMPedometerEvent : NSObject <NSSecureCoding, NSCopying>

/*
 *  date
 *
 *  Discussion:
 *      The time of occurence of event.
 */
@property(readonly, nonatomic) NSDate *date;

/*
 *  type
 *
 *  Discussion:
 *      Event type describing the transition of pedestrian activity.
 */
@property(readonly, nonatomic) CMPedometerEventType type;

@end

/*
 *  CMPedometerHandler
 *
 *  Discussion:
 *      Typedef of block to be invoked when pedometer data is available. Error
 *      types are defined in "CMError.h".
 */
typedef void (^CMPedometerHandler)(CMPedometerData * __nullable pedometerData, NSError * __nullable error) API_UNAVAILABLE(tvos);

/*
 *  CMPedometerEventHandler
 *
 *  Discussion:
 *      Typedef of block that will be invoked when pedometer event is available.
 *      Error types are defined in "CMError.h".
 */
typedef void (^CMPedometerEventHandler)(CMPedometerEvent * __nullable pedometerEvent, NSError * __nullable error) NS_AVAILABLE(NA, 10_0) __WATCHOS_AVAILABLE(3_0) API_UNAVAILABLE(tvos);

/*
 *  CMPedometer
 *
 *  Discussion:
 *      CMPedometer allows access to the user's pedestrian activity. The
 *      activity can be retrieved in one of two ways:
 *
 *      1. Via a query specifying a time range from which the pedometer data is
 *      tabulated and returned.
 *      (See queryPedometerDataFromDate:toDate:withHandler:)
 *
 *      2. By providing a block to startPedometerUpdatesFromDate:withHandler:,
 *      pedometer updates will be provided on a best effort basis. Pedometer
 *      updates can be stopped by calling stopPedometerUpdates.
 *
 */
NS_CLASS_AVAILABLE(NA,8_0) API_UNAVAILABLE(tvos)
@interface CMPedometer : NSObject

/*
 *  isStepCountingAvailable
 *
 *  Discussion:
 *      Determines whether the device supports step counting functionality.
 */
+ (BOOL)isStepCountingAvailable;

/*
 *  isDistanceAvailable
 *
 *  Discussion:
 *      Determines whether the device supports distance estimation
 *      in addition to step counting.
 */
+ (BOOL)isDistanceAvailable;

/*
 *  isFloorCountingAvailable
 *
 *  Discussion:
 *      Determines whether the device supports counting flights of stairs
 *      in addition to step counting.
 */
+ (BOOL)isFloorCountingAvailable;

/*
 *  isPaceAvailable
 *
 *  Discussion:
 *      Determines whether the device supports pace estimation
 *      in addition to step counting.
 */
+ (BOOL)isPaceAvailable NS_AVAILABLE(NA,9_0);

/*
 *  isCadenceAvailable
 *
 *  Discussion:
 *      Determines whether the device supports cadence estimation
 *      in addition to step counting.
 */
+ (BOOL)isCadenceAvailable NS_AVAILABLE(NA,9_0);

/*
 *  isPedometerEventTrackingAvailable
 *
 *  Discussion:
 *      Determines whether the device supports pedometer events.
 */
+ (BOOL)isPedometerEventTrackingAvailable NS_AVAILABLE(NA,10_0) __WATCHOS_AVAILABLE(3_0);

/*
 *  authorizationStatus
 *
 *  Discussion:
 *      Returns the current authorization status for pedometer.
 */
+ (CMAuthorizationStatus)authorizationStatus NS_AVAILABLE(NA, 11_0) __WATCHOS_AVAILABLE(4_0);

/*
 *  queryPedometerDataFromDate:toDate:withHandler:
 *
 *  Discussion:
 *      Queries for the user's pedestrian activity in the given time range. Data
 *      is available for up to 7 days. The data returned is computed from a
 *      system-wide history that is continuously being collected in the
 *      background. The result is returned on a serial queue.
 */
- (void)queryPedometerDataFromDate:(NSDate *)start
							toDate:(NSDate *)end
					   withHandler:(CMPedometerHandler)handler;

/*
 *  startPedometerUpdatesFromDate:withHandler:
 *
 *  Discussion:
 *      Starts a series of continuous pedometer updates to the
 *      handler on a serial queue. For each update, the app
 *      will receive the cumulative pedestrian activity since the
 *      start date specified and the timestamp associated with the
 *      latest determination. If the app is backgrounded and resumed
 *      at a later time, the app will receive all of the pedestrian
 *      activity accumulated during the background period in the
 *      very next update.
 */
- (void)startPedometerUpdatesFromDate:(NSDate *)start
						  withHandler:(CMPedometerHandler)handler;

/*
 *  stopPedometerUpdates
 *
 *  Discussion:
 *      Stops pedometer updates.
 */
- (void)stopPedometerUpdates;

/*
 *  startPedometerEventUpdatesWithHandler:
 *
 *  Discussion:
 *      Starts pedometer event updates on a serial queue.
 *      Events are available only when the apps are running in foreground / background.
 */
- (void)startPedometerEventUpdatesWithHandler:(CMPedometerEventHandler)handler NS_AVAILABLE(NA,10_0) __WATCHOS_AVAILABLE(3_0);

/*
 *  stopPedometerEventUpdates
 *
 *  Discussion:
 *      Stops pedometer event updates.
 */
- (void)stopPedometerEventUpdates NS_AVAILABLE(NA,10_0) __WATCHOS_AVAILABLE(3_0);

@end

NS_ASSUME_NONNULL_END
