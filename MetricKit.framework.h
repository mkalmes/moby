// ==========  MetricKit.framework/Headers/MXMetaData.h
//
//  MXMetaData.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXMetaData
 @abstract      A class that contains miscellaneous metadata about an associated metric payload.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXMetaData : NSObject <NSSecureCoding>

/*!
 @property      regionFormat
 @abstract      An NSString designating the region format associated with the application.
 */
@property (readonly, strong, nonnull) NSString *regionFormat;

/*!
 @property      osVersion
 @abstract      An NSString designating the OS version associated with the device.
 */
@property (readonly, strong, nonnull) NSString *osVersion;

/*!
 @property      deviceType
 @abstract      An NSString designating the device type associated with this device.
 */
@property (readonly, strong, nonnull) NSString *deviceType;

/*!
 @property      applicationBuildVersion
 @abstract      An NSString designating the app build version.
 */
@property (readonly, strong, nonnull) NSString *applicationBuildVersion;

/*!
 @method        JSONRepresentation
 @abstract      Convenience method to return a JSON representation of this metadata.
 @result        An NSData object containing the JSON representation
 */
- (NSData *)JSONRepresentation;

/*!
 @method        DictionaryRepresentation
 @abstract      Convenience method to return a NSDictionary representation of this metadata.
 @result        An NSDictionary object containing the dictionary representation
 */
- (NSDictionary *)DictionaryRepresentation;

@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXAppResponsivenessMetric.h
//
//  MXAppResponsivenessMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetric.h>
#import <os/availability.h>
#import <MetricKit/MXHistogram.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXAppResponsivenessMetric
 @abstract      An MXMetric subclass that encapsulates app responsiveness metrics.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXAppResponsivenessMetric : MXMetric

/*!
 @property      histogrammedApplicationHangTime
 @abstract      Histogrammed app hang time data.
 @discussion    Applications are considered to be "hanging" when they are unable to handle user input responsively.
 @discussion    The durations for periods of hangs will be reported in the histogram returned here.
 @discussion    Application hang times that exceeds 9 seconds of wall clock time are reported in the final bucket of the histogram.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) MXHistogram<NSUnitDuration *> *histogrammedApplicationHangTime;

@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXUnit.h
//
//  MXUnit.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXUnitSignalBars
 @abstract      An NSUnit subclass representing the number of signal bars for signal strength.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXUnitSignalBars : NSDimension
/*
 Base unit - bars
 */
@property (class, readonly, copy) MXUnitSignalBars *bars;
@end

/*!
 @class         MXUnitAveragePixelLuminance
 @abstract      An NSUnit subclass representing the linear space Display APL.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXUnitAveragePixelLuminance : NSDimension
/*
 Base unit - apl
 */
@property (class, readonly, copy) MXUnitAveragePixelLuminance *apl;
@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXDisplayMetric.h
//
//  MXDisplayMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetric.h>
#import <MetricKit/MXUnit.h>
#import <os/availability.h>
#import <MetricKit/MXAverage.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXDisplayMetric
 @abstract      An MXMetric subclass that encapsulates display metrics.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXDisplayMetric : MXMetric

/*!
 @property      averagePixelLuminance
 @abstract      Average Pixel Luminance for the application.
 @discussion    APL data ranges from 0-100, in increments of 1.
 @discussion    This value is null when the device does not support APL.
 @discussion    Dimensioned as MXUnitAveragePixelLuminance.
 */
@property (readonly, strong, nullable) MXAverage<MXUnitAveragePixelLuminance *> *averagePixelLuminance;

@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXLocationActivityMetric.h
//
//  MXLocationActivityMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetric.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXLocationActivityMetric
 @abstract      An MXMetric subclass that encapsulates location metrics
 @discussion    The metrics contained in this class describe properties of location activity. See MXAppRunTimeMetric for time spent performing location activities.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXLocationActivityMetric : MXMetric

/*!
 @property      cumulativeBestAccuracyTime
 @abstract      Cumulative time spent acquiring location at kCLLocationAccuracyBest.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeBestAccuracyTime;

/*!
 @property      cumulativeBestAccuracyForNavigationTime
 @abstract      Cumulative time spent acquiring location at kCLLocationAccuracyBestForNavigation.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeBestAccuracyForNavigationTime;

/*!
 @property      cumulativeNearestTenMetersAccuracyTime
 @abstract      Cumulative time spent acquiring location at kCLLocationAccuracyNearestTenMeters.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeNearestTenMetersAccuracyTime;

/*!
 @property      cumulativeHundredMetersAccuracyTime
 @abstract      Cumulative time spent acquiring location at kCLLocationAccuracyHundredMeters.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeHundredMetersAccuracyTime;

/*!
 @property      cumulativeKilometerAccuracyTime
 @abstract      Cumulative time spent acquiring location at kCLLocationAccuracyKilometer.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeKilometerAccuracyTime;

/*!
 @property      cumulativeThreeKilometersAccuracyTime
 @abstract      Cumulative time spent acquiring location at kCLLocationAccuracyThreeKilometers.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeThreeKilometersAccuracyTime;

@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXGPUMetric.h
//
//  MXGPUMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>
#import <MetricKit/MXMetric.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXGPUMetric
 @abstract      An MXMetric subclass that encapsulates GPU metrics.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXGPUMetric : MXMetric

/*!
 @property      cumulativeGPUTime
 @abstract      GPU time aggregated cumulatively.
 @discussion    The data here represents the total GPU time an application consumed over the date range of the containing payload.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeGPUTime;

@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXNetworkTransferMetric.h
//
//  MXNetworkTransferMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetric.h>
#import <MetricKit/MXUnit.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXNetworkTransferMetric
 @abstract      An MXMetric subclass that encapsulates network transfer metrics
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXNetworkTransferMetric : MXMetric

/*!
 @property      cumulativeWifiUpload
 @abstract      Cumulative amount of data uploaded over WiFi.
 @discussion    Dimensioned as NSUnitInformationStorage.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *cumulativeWifiUpload;

/*!
 @property      cumulativeWifiDownload
 @abstract      Cumulative amount of data downloaded over WiFi.
 @discussion    Dimensioned as NSUnitInformationStorage.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *cumulativeWifiDownload;

/*!
 @property      cumulativeCellularUpload
 @abstract      Cumulative amount of data uploaded over cellular networks.
 @discussion    This data is radio access technology agnostic.
 @discussion    Dimensioned as NSUnitInformationStorage.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *cumulativeCellularUpload;

/*!
 @property      cumulativeCellularDownload
 @abstract      Cumulative amount of data downloaded over cellular networks.
 @discussion    This data is radio access technology agnostic.
 @discussion    Dimensioned as NSUnitInformationStorage.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *cumulativeCellularDownload;

@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXDiskIOMetric.h
//
//  MXDiskIOMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetric.h>
#import <MetricKit/MXUnit.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXDiskIOMetric
 @abstract      An MXMetric subclass that encapsulates disk IO metrics.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXDiskIOMetric : MXMetric

/*!
 @property      cumulativeLogicalWrites
 @abstract      Cumulative amount of logical writes.
 @discussion    Dimensioned as NSUnitInformationStorage.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *cumulativeLogicalWrites;

@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXSignpostMetric.h
//
//  MXSignpostMetric.h
//  MetricKit
//
//  Copyright (c) 2019 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetric.h>
#import <MetricKit/MXHistogram.h>
#import <MetricKit/MXCPUMetric.h>
#import <MetricKit/MXMemoryMetric.h>
#import <MetricKit/MXDiskIOMetric.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXSignpostIntervalData
 @abstract      A class that encapsulates metrics associated with app specific signpost intervals.
 @discussion    These metrics will be collected and aggregated if the associated signposts were emit using the appropriate API.
 @discussion    To limit on-device overhead, the system will automatically limit the number of signposts (emitted using the MetricKit log handle) processed.
 @discussion    Avoid losing telemetry by limiting usage of signposts (emitted using the MetricKit log handle) to critical sections of code.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXSignpostIntervalData : NSObject <NSSecureCoding>

/*!
 @property      histogrammedSignpostDuration
 @abstract      A histogram of signpost intervals durations associated with the given signposts with signpostName and signpostCategory.
 */
@property (readonly, strong, nonnull) MXHistogram<NSUnitDuration *> *histogrammedSignpostDuration;

/*!
 @property      cumulativeCPUTime
 @abstract      Cumulative CPU time aggregated over the MXSignpost intervals.
 @discussion    This property is null when signposts with the associated signpostName and signpostCategory contain no interval metric data.
 */
@property (readonly, strong, nullable) NSMeasurement<NSUnitDuration *> *cumulativeCPUTime;

/*!
 @property      averageMemory
 @abstract      Average value of memory snapshots taken at beginning and end of MXSignpost intervals
 @discussion    This property is null when signposts with the associated signpostName and signpostCategory contain no interval metric data.
 */
@property (readonly, strong, nullable) MXAverage<NSUnitInformationStorage *> *averageMemory;

/*!
 @property      cumulativeLogicalWrites
 @abstract      Cumulative logical writes aggregated over the MXSignpost intervals.
 @discussion    This property is null when signposts with the associated signpostName and signpostCategory contain no interval metric data.
 */
@property (readonly, strong, nullable)  NSMeasurement<NSUnitInformationStorage *> *cumulativeLogicalWrites;

@end

/*!
 @class         MXSignpostMetric
 @abstract      An MXMetric subclass that encapsulates signpost metrics.
 @discussion    Signposts emit using the os_log_t generated by makeLogHandleWithCategory: in MXMetricManger can be flagged for aggregation and reported back in MXMetricPayload.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXSignpostMetric : MXMetric

/*!
 @property      signpostName
 @abstract      The name associated with this aggregated signpost.
 */
@property (readonly, strong, nonnull) NSString *signpostName;

/*!
 @property      signpostCategory
 @abstract      The category associated with this aggregated signpost.
 */
@property (readonly, strong, nonnull) NSString *signpostCategory;

/*!
 @property      signpostIntervalData
 @abstract      A class that encapsulates metrics associated with app specific signpost intervals.
 @discussion    This property is null when signposts with the associated signpostName and signpostCategory contain no intervals.
 */
@property (readonly, strong, nullable) MXSignpostIntervalData *signpostIntervalData;

/*!
 @property      totalCount
 @abstract      The total number of signposts emit with the given signpostName in the aggregation period of the parent payload.
 */
@property (readonly) NSUInteger totalCount;

@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXMetricPayload.h
//
//  MXMetricPayload.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>
#import <MetricKit/MXMetric.h>
#import <MetricKit/MXCPUMetric.h>
#import <MetricKit/MXGPUMetric.h>
#import <MetricKit/MXCellularConditionMetric.h>
#import <MetricKit/MXMetaData.h>
#import <MetricKit/MXAppRunTimeMetric.h>
#import <MetricKit/MXLocationActivityMetric.h>
#import <MetricKit/MXNetworkTransferMetric.h>
#import <MetricKit/MXAppLaunchMetric.h>
#import <MetricKit/MXAppResponsivenessMetric.h>
#import <MetricKit/MXDiskIOMetric.h>
#import <MetricKit/MXMemoryMetric.h>
#import <MetricKit/MXDisplayMetric.h>
#import <MetricKit/MXSignpostMetric.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXMetricPayload
 @abstract      A wrapper class which contains a metric payload and associated properties of that payload.
 @discussion    MXMetricPayload encapsulates currently supported metric types that can be vended by MetricKit. MXMetric subclasses on MXMetricPayload are nullable. If an MXMetric subclass is nil, it indicates that the data is not available for this payload.
 @discussion    MXMetricPayload exposes a convenience function, JSONRepresentation, to convert the contents of the payload to a human readable JSON. This should be used in conjunction with other APIs that accept NSData.
 @discussion    An MXMetricPayload contains data that covers a 24 hour period of application usage. The properties timeStampBegin and timeStampEnd should be used to determine which time range the payload covers.
 @discussion    It is possible for an MXMetricPayload to cover regions of time where an application was updated, and thus had multiple different app version strings. The property latestApplicationVersion will always reflect the latest appVersion at the time the metric payload was created. Use includesMultipleApplicationVersions to determine if an application changed versions during the time range the payload covers.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXMetricPayload : NSObject <NSSecureCoding>

/*!
 @property      latestApplicationVersion
 @abstract      An NSString representation of the application version from which this payload was generated.
 @discussion    If the application version was changed during the aggregation of this data, this value will reflect the latest application version at the time of retrieval.
 */
@property (readonly, strong, nonnull) NSString *latestApplicationVersion;

/*!
 @property      includesMultipleApplicationVersions
 @abstract      A bool which indicates whether or not this payload contains data from multiple application versions.
 @discussion    A value of YES indicates that this payload's data reflects multiple application versions.
 @discussion    A value of NO indicates that this payload only reflects data from the application version specified by latestApplicationVersion.
 */

@property (readonly) BOOL includesMultipleApplicationVersions;

/*!
 @property      timeStampBegin
 @abstract      An NSDate object that indicates the time which the payload was generated.
 */
@property (readonly, strong, nonnull) NSDate *timeStampBegin;

/*!
 @property      timeStampEnd
 @abstract      An NSDate object that indicates the time which the payload was generated.
 */
@property (readonly, strong, nonnull) NSDate *timeStampEnd;

/*!
 @property      cpuMetrics
 @abstract      An object containing CPU metrics for this application.
 */
@property (readonly, strong, nullable) MXCPUMetric *cpuMetrics;

/*!
 @property      gpuMetrics
 @abstract      An object containing GPU metrics for this application.
 */
@property (readonly, strong, nullable) MXGPUMetric *gpuMetrics;

/*!
 @property      cellularConditionMetrics
 @abstract      An object containing a cellular condition metrics for this application.
 */
@property (readonly, strong, nullable) MXCellularConditionMetric *cellularConditionMetrics;

/*!
 @property      applicationTimeMetrics
 @abstract      An object containing running mode metrics for this application.
 */
@property (readonly, strong, nullable) MXAppRunTimeMetric *applicationTimeMetrics;

/*!
 @property      locationActivityMetrics
 @abstract      An object containing location activity metrics for this application.
 */
@property (readonly, strong, nullable) MXLocationActivityMetric *locationActivityMetrics;

/*!
 @property      networkTransferMetrics
 @abstract      An object containing network transfer metrics for this application.
 */
@property (readonly, strong, nullable) MXNetworkTransferMetric *networkTransferMetrics;

/*!
 @property      applicationLaunchMetrics
 @abstract      An object containing launch metrics for this application.
 */
@property (readonly, strong, nullable) MXAppLaunchMetric *applicationLaunchMetrics;

/*!
 @property      applicationResponsivenessMetrics
 @abstract      An object containing hang metrics for this application.
 */
@property (readonly, strong, nullable) MXAppResponsivenessMetric *applicationResponsivenessMetrics;

/*!
 @property      diskIOMetrics
 @abstract      An object containing disk IO metrics for this application.
 */
@property (readonly, strong, nullable) MXDiskIOMetric *diskIOMetrics;

/*!
 @property      memoryMetrics
 @abstract      An object containing memory metrics for this application.
 */
@property (readonly, strong, nullable) MXMemoryMetric *memoryMetrics;

/*!
 @property      displayMetrics
 @abstract      An object containing display metrics for this application.
 */
@property (readonly, strong, nullable) MXDisplayMetric *displayMetrics;

/*!
 @property      signpostMetrics
 @abstract      An array containing signpost metrics for this application.
 */
@property (readonly, strong, nullable) NSArray<MXSignpostMetric *> *signpostMetrics;

/*!
 @property      metaData
 @abstract      An object containing extra metadata for this payload.
 */
@property (readonly, strong, nullable) MXMetaData *metaData;

/*!
 @method        JSONRepresentation
 @abstract      Convenience method to return a JSON representation of this payload.
 @result        An NSData object containing the JSON representation
 */
- (NSData *)JSONRepresentation;

/*!
 @method        DictionaryRepresentation
 @abstract      Convenience method to return a NSDictionary representation of this payload.
 @result        An NSDictionary object containing the dictionary representation
 */
- (NSDictionary *)DictionaryRepresentation;

@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXCellularConditionMetric.h
//
//  MXCellConditionMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>
#import <MetricKit/MXMetric.h>
#import <MetricKit/MXUnit.h>
#import <MetricKit/MXHistogram.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXCellConditionMetric
 @abstract      An MXMetric subclass that encapsulates cellular condition metrics.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXCellularConditionMetric : MXMetric

/*!
 @property      cellularConditionTime
 @abstract      Application run time bucketized by cellular condition.
 @discussion    This data represents the percentage of time an application spent running in different cellular conditions.
 @discussion    In the event that no data for any buckets is available, the histogram data will be empty.
 @discussion    Dimensioned as MXUnitSignalBars.
 */
@property (readonly, strong, nonnull) MXHistogram<MXUnitSignalBars *> *histogrammedCellularConditionTime;

@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXCPUMetric.h
//
//  MXCPUMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>
#import <MetricKit/MXMetric.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXCPUMetric
 @abstract      An MXMetric subclass that encapsulates CPU metrics.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXCPUMetric : MXMetric

/*!
 @property      cumulativeCPUTime
 @abstract      CPU time aggregated cumulatively.
 @discussion    The data here represents the total CPU time an application consumed over the date range of the containing payload.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeCPUTime;

@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXMetricManager.h
//
//  MXMetricManager.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetricPayload.h>
#import <os/log.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MXMetricManagerSubscriber;

/*!
 @class         MXMetricManager
 @abstract      An instance of this class can be used to retrieve periodic, aggregated power and performance metrics.
 @discussion    To receive metrics, clients must acquire a reference to the shared instance of the metric manager and add an eligible MXMetricManagerSubscriber.
 @discussion    Metrics are not guaranteed to be delivered, but can be expected atleast once per day when conditions permit.
 @discussion    Subscribers to the metric manager can remove themselves using removeSubscriber:subscriber if they no longer wish to receive metrics.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXMetricManager : NSObject

/*!
 @property      pastPayloads
 @abstract      A list of past metric payloads received.
 */
@property (readonly, nonnull, strong) NSArray<MXMetricPayload *> *pastPayloads;

/*!
 @property      sharedManager
 @abstract      Singleton instance of MXMetricManager.
 */
@property (class, readonly, strong) MXMetricManager *sharedManager;

/*!
 @method        makeLogHandleWithCategory:category
 @abstract      Retrieve a log handle for flagging critical sections with os_signpost().
 @param         category A string used to define a log category
 @discussion    The log handle configures persistence for any signposts emit while using the log handle.
 @result        A log handle that can be used with the logging framework.
 */
+ (os_log_t _Nonnull)makeLogHandleWithCategory:(NSString *)category NS_SWIFT_NAME(makeLogHandle(category:));

/*!
 @method        addSubscriber:subscriber
 @abstract      Adds a subscriber to the metric manager.
 @param         subscriber An object that conforms to the MXMetricManagerSubscriber protocol.
 @discussion    Subscribers can receive metric payloads by conforming to the MXMetricManagerSubscriber protocol.
 */
- (void)addSubscriber:(id<MXMetricManagerSubscriber>)subscriber;

/*!
 @method        removeSubscriber:subscriber
 @abstract      Removes a subscriber from the metric manager.
 @param         subscriber An object that conforms to the MXMetricManagerSubscriber protocol.
 @discussion    The subscriber indicated, if previously registered, will no longer receive metric payloads.
 */
- (void)removeSubscriber:(id<MXMetricManagerSubscriber>)subscriber;

@end

/*!
 @protocol      MXMetricManagerSubscriber
 @abstract      A protocol that allows the conforming object to receive metric payloads from the metric manager.
 @discussion    In order to receive metric payloads, atleast one object must conform to this protocol and be subscribed   to the metric manager.
 @discussion    Objects which conform to this protocol can be passed to addSubscriber:subscriber and removeSubscriber:subscriber to manage their subscription state.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@protocol MXMetricManagerSubscriber <NSObject>

@required

/*!
 @method        didReceiveMetricPayloads:payloads
 @abstract      This method is invoked when a new MXMetricPayload has been received.
 @param         payloads
 An NSArray of MXMetricPayload objects. This array of payloads contains data from previous usage sessions.
 @discussion    You can expect for this method to be invoked atleast once per day when the app is running and subscribers are available.
 @discussion    If no subscribers are available, this method will not be invoked.
 @discussion    Atleast one subscriber must be available to receive metrics.
 @discussion    This method is invoked on a background queue.
 */
- (void)didReceiveMetricPayloads:(NSArray<MXMetricPayload *> * _Nonnull)payloads;

@optional

@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXAverage.h
//
//  MXAverage.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXAverage
 @abstract      A class representing metric data that is averaged.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXAverage<UnitType: NSUnit *> : NSObject <NSSecureCoding>

/*!
 @property      averageMeasurement
 @abstract      An NSMeasurement that contains the average measurement.
 */
@property (readonly, strong, nonnull) NSMeasurement<UnitType> *averageMeasurement;

/*!
 @property      sampleCount
 @abstract      An NSInteger representation of the number of samples in the distribution used to formulate the average.
 @discussion    This value is negative if an unknown number of samples was used to compute the average.
 */
@property (readonly) NSInteger sampleCount;


/*!
 @property      standardDeviation
 @abstract      An double representation of the standard deviation of the distribution.
 @discussion    This value is negative an unknown number of samples was used to compute the standard deviation.
 */
@property (readonly) double standardDeviation;



@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXAppRunTimeMetric.h
//
//  MXAppTimeMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>
#import <MetricKit/MXMetric.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXAppRunTimeMetric
 @abstract      An MXMetric subclass that encapsulates app runtime metrics.
 @discussion    Runtime metrics describe application time spent running in different modes, such as audio, location, etc.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXAppRunTimeMetric : MXMetric

/*!
 @property      cumulativeForegroundTime
 @abstract      Cumulative application foreground time.
 @discussion    Time spent on screen and visible to the user.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeForegroundTime;

/*!
 @property      cumulativeBackgroundTime
 @abstract      Cumulative application background time.
 @discussion    Time spent off screen and in the background, invisible to the user.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeBackgroundTime;

/*!
 @property      cumulativeBackgroundAudioTime
 @abstract      Cumulative time the application spent running in the background to play audio
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeBackgroundAudioTime;

/*!
 @property      cumulativeBackgroundLocationTime
 @abstract      Cumulative time the application spent running in the background to acquire or process location.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *cumulativeBackgroundLocationTime;

@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXMemoryMetric.h
//
//  MXMemoryMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetric.h>
#import <MetricKit/MXUnit.h>
#import <os/availability.h>
#import <MetricKit/MXAverage.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXMemoryMetric
 @abstract      An MXMetric subclass that encapsulates memory metrics.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXMemoryMetric : MXMetric

/*!
 @property      peakMemoryUsage
 @abstract      A single value representing the peak memory consumption of the application.
 @discussion    Dimensioned as NSUnitInformationStorage.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *peakMemoryUsage;

/*!
 @property      averageSuspendedMemory
 @abstract      Average memory of the application upon suspend.
 @discussion    Dimensioned as NSUnitInformationStorage.
 */
@property (readonly, strong, nonnull) MXAverage<NSUnitInformationStorage *> *averageSuspendedMemory;

@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXHistogram.h
//
//  MXHistogram.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXHistogramBucket
 @abstract      A class that represents a bucket within an MXHistogram
 @discussion    Histogram buckets are sorted in ascending order.
 @discussion    Histogram bucket start and end values are exclusive.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXHistogramBucket<UnitType: NSUnit *> : NSObject <NSSecureCoding>

/*!
 @property      bucketStart
 @abstract      An NSMeasurement representing the start of a histogram bucket.
 */
@property (readonly, strong, nonnull) NSMeasurement<UnitType> *bucketStart;

/*!
 @property      bucketEnd
 @abstract      An NSMeasurement representing the end of a histogram bucket.
 */
@property (readonly, strong, nonnull) NSMeasurement<UnitType> *bucketEnd;

/*!
 @property      bucketCount
 @abstract      An NSUInteger representing the number of samples in this histogram bucket.
 */
@property (readonly) NSUInteger bucketCount;

@end

/*!
 @class         MXHistogram
 @abstract      A class representing bucketized histogram data.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXHistogram<UnitType: NSUnit *>  : NSObject <NSSecureCoding>

/*!
 @property      totalBucketCount
 @abstract      The number of buckets contained within this histogram.
 @discussion    This value can never be negative.
 */
@property (readonly) NSUInteger totalBucketCount;

/*!
 @property      bucketEnumerator
 @abstract      An NSEnumerator that can be used to enumerate the buckets of this histogram.
 */
@property (readonly, strong, nonnull) NSEnumerator<MXHistogramBucket<UnitType> *> *bucketEnumerator;

@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXAppLaunchMetric.h
//
//  MXAppLaunchMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetric.h>
#import <os/availability.h>
#import <MetricKit/MXHistogram.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXAppLaunchMetric
 @abstract      An MXMetric subclass that encapsulates app launch metrics.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXAppLaunchMetric : MXMetric

/*!
 @property      histogrammedTimeToFirstDraw
 @abstract      Histogrammed application time-to-first-draw data.
 @discussion    Dimensioned as NSUnitDuration.
 @discussion    This represents the time when the first CA commit is finished.
 */
@property (readonly, strong, nonnull) MXHistogram<NSUnitDuration *> *histogrammedTimeToFirstDraw;

/*!
 @property      histogrammedApplicationResumeTime
 @abstract      Histogrammed application resume time data.
 @discussion    Dimensioned as NSUnitDuration.
 */
@property (readonly, strong, nonnull) MXHistogram<NSUnitDuration *> *histogrammedApplicationResumeTime;

@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MetricKit.h
//
//  MetricKit.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <MetricKit/MXMetricManager.h>
#import <MetricKit/MXMetricPayload.h>
#import <MetricKit/MXUnit.h>
#import <MetricKit/MXAverage.h>
#import <MetricKit/MXHistogram.h>
#import <MetricKit/MXMetaData.h>
#import <MetricKit/MXMetric.h>
#import <MetricKit/MXAppLaunchMetric.h>
#import <MetricKit/MXAppResponsivenessMetric.h>
#import <MetricKit/MXAppRunTimeMetric.h>
#import <MetricKit/MXCellularConditionMetric.h>
#import <MetricKit/MXCPUMetric.h>
#import <MetricKit/MXDiskIOMetric.h>
#import <MetricKit/MXDisplayMetric.h>
#import <MetricKit/MXGPUMetric.h>
#import <MetricKit/MXLocationActivityMetric.h>
#import <MetricKit/MXMemoryMetric.h>
#import <MetricKit/MXNetworkTransferMetric.h>
#import <MetricKit/MXSignpostMetric.h>
#import <MetricKit/MXSignpost.h>
// ==========  MetricKit.framework/Headers/MXMetric.h
//
//  MXMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXMetric
 @abstract      An abstract class that describes a specific metric vended by MetricKit.
 @discussion    All supported metrics are subclasses of MXMetric.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXMetric : NSObject <NSSecureCoding>

/*!
 @method        JSONRepresentation
 @abstract      Convenience method to return a JSON representation of this metric.
 @result        An NSData object containing the JSON representation
 */
- (NSData *)JSONRepresentation;

/*!
 @method        DictionaryRepresentation
 @abstract      Convenience method to return a NSDictionary representation of this metric.
 @result        An NSDictionary object containing the dictionary representation
 */
- (NSDictionary *)DictionaryRepresentation;

@end

NS_ASSUME_NONNULL_END
// ==========  MetricKit.framework/Headers/MXSignpost_Private.h
//
//  MXSignpost_Private.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#ifndef MXSignpost_Private_h
#define MXSignpost_Private_h

#include <os/signpost.h>
#pragma mark - Implementation details. DO NOT CALL DIRECTLY

/*!
 * @header MXSignpost_Private.h
 *
 * This header contains implementation details that are not meant for clients
 * to call directly. The header must be public to allow clients to compile properly.
 *
 * Please refer to MXSignpost.h for the client-facing API surface.
 */

#if TARGET_OS_SIMULATOR

#define _MXSignpostEventEmit_guaranteed_args(log, event_id, name, format,...)
#define _MXSignpostIntervalBegin_guaranteed_args(log, event_id, name, format,...)
#define _MXSignpostIntervalEnd_guaranteed_args(log, event_id, name, format,...)

#else

API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
void* _Nonnull _MXSignpostMetricsSnapshot(void);
#define _METRICS_SIGNPOST_TYPE_TOKEN "signpost:metrics"
#define _MXSIGNPOST_METRICS_SNAPSHOT_FORMAT "\n%{public, " _METRICS_SIGNPOST_TYPE_TOKEN "}@"

#define _MXSignpostEventEmit_guaranteed_args(log, event_id, name, format,...) os_signpost_event_emit(log, event_id, name, format _MXSIGNPOST_METRICS_SNAPSHOT_FORMAT, ##__VA_ARGS__, _MXSignpostMetricsSnapshot())
#define _MXSignpostIntervalBegin_guaranteed_args(log, event_id, name, format,...) os_signpost_interval_begin(log, event_id, name, format _MXSIGNPOST_METRICS_SNAPSHOT_FORMAT, ##__VA_ARGS__, _MXSignpostMetricsSnapshot())
#define _MXSignpostIntervalEnd_guaranteed_args(log, event_id, name, format,...) os_signpost_interval_end(log, event_id, name, format _MXSIGNPOST_METRICS_SNAPSHOT_FORMAT, ##__VA_ARGS__, _MXSignpostMetricsSnapshot())
#endif

#endif /* MXSignpost_Private_h */
// ==========  MetricKit.framework/Headers/MXSignpost.h
//
//  MXSignpost.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#ifndef MXSignpost_h
#define MXSignpost_h

#if defined(__cplusplus)
extern "C" {
#endif
#include <MetricKit/MXSignpost_Private.h>
    
#pragma mark - Public MXSignpost* API surface
/*!
 * @header MXSignpost
 *
 * The MXSignpost API surface wraps calls to normal os_signpost in order to
 * gather snapshots of process-level metrics. THESE CALLS ARE MUCH MORE
 * EXPENSIVE THAN NORMAL OS_SIGNPOST_* CALLS and are meant to be called
 * sparingly. Bulk replacing of calls to os_signpost with MXSignpost will lead
 * to potentially large performance regressions.
 *
 * This API surface functions identically to os_signpost. Please see
 * <os/signpost.h> for more information on usage of os_signpost.
 */

/*!
 * @function MXSignpostEventEmit
 *
 * @abstract
 * Emits a standalone os_signpost event with @c os_signpost_event_emit() and
 * includes a snapshot of performance metrics of the emitting process.
 *
 * This function is *much more expensive* than a direct call to
 * os_signpost_event_emit() and should be used only sparingly at points of
 * interest.
 *
 * Please refer to @c <os/signpost.h> for more detailed discussion of the
 * required parameters.
 *
 * @param log
 * Log handle previously created with os_log_create.
 *
 * @param interval_id
 * An ID for the interval. See @c <os/signpost.h> for more detailed discussion.
 *
 * @param name
 * The name of this event. This must be a string literal.
 *
 * @param ... (format + arguments)
 * Additional information to include with this signpost.  This format string
 * must be a string literal, as with the os_log family of functions.
 * See @c <os/signpost.h> for more detailed discussion.
 */
#define MXSignpostEventEmit(log, event_id, name, ...) _MXSignpostEventEmit_guaranteed_args(log, event_id, name, "" __VA_ARGS__)
/*!
 * @function MXSignpostIntervalBegin
 *
 * @abstract
 * Begins an os_signpost interval with @c os_signpost_interval_begin() and
 * includes a snapshot of performance metrics of the emitting process.
 *
 * This function is *much more expensive* than a direct call to
 * os_signpost_interval_begin() and should be used only sparingly at points of
 * interest.
 *
 * Please refer to @c <os/signpost.h> for more detailed discussion of the
 * required parameters.
 *
 * @param log
 * Log handle previously created with os_log_create.
 *
 * @param interval_id
 * An ID for the interval. See @c <os/signpost.h> for more detailed discussion.
 *
 * @param name
 * The name of this event. This must be a string literal.
 *
 * @param ... (format + arguments)
 * Additional information to include with this signpost.  This format string
 * must be a string literal, as with the os_log family of functions.
 * See @c <os/signpost.h> for more detailed discussion.
 */
#define MXSignpostIntervalBegin(log, event_id, name, ...) _MXSignpostIntervalBegin_guaranteed_args(log, event_id, name, "" __VA_ARGS__)
/*!
 * @function MXSignpostIntervalEnd
 *
 * @abstract
 * Ends an os_signpost interval with @c os_signpost_interval_end() and includes
 * a snapshot of performance metrics of the emitting process.
 *
 * This function is *much more expensive* than a direct call to
 * os_signpost_interval_end() and should be used only sparingly at points of
 * interest.
 *
 * Please refer to @c <os/signpost.h> for more detailed discussion of the
 * required parameters.
 *
 * @param log
 * Log handle previously created with os_log_create.
 *
 * @param interval_id
 * An ID for the interval. See @c <os/signpost.h> for more detailed discussion.
 *
 * @param name
 * The name of this event. This must be a string literal.
 *
 * @param ... (format + arguments)
 * Additional information to include with this signpost.  This format string
 * must be a string literal, as with the os_log family of functions.
 * See @c <os/signpost.h> for more detailed discussion.
 */
#define MXSignpostIntervalEnd(log, event_id, name, ...) _MXSignpostIntervalEnd_guaranteed_args(log, event_id, name, "" __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif //MXSignpost_h
