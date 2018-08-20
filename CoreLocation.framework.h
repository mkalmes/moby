// ==========  CoreLocation.framework/Headers/CLLocation.h
/*
 *  CLLocation.h
 *  CoreLocation
 *
 *  Copyright (c) 2008-2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CLAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CLLocationDegrees
 *  
 *  Discussion:
 *    Type used to represent a latitude or longitude coordinate in degrees under the WGS 84 reference
 *    frame. The degree can be positive (North and East) or negative (South and West).  
 */
typedef double CLLocationDegrees;

/*
 *  CLLocationAccuracy
 *  
 *  Discussion:
 *    Type used to represent a location accuracy level in meters. The lower the value in meters, the
 *    more physically precise the location is. A negative accuracy value indicates an invalid location.
 */
typedef double CLLocationAccuracy;

/*
 *  CLLocationSpeed
 *  
 *  Discussion:
 *    Type used to represent the speed in meters per second.
 */
typedef double CLLocationSpeed;

/*
 *  CLLocationDirection
 *  
 *  Discussion:
 *    Type used to represent the direction in degrees from 0 to 359.9. A negative value indicates an
 *    invalid direction.
 */
typedef double CLLocationDirection;

/*
 *  CLLocationCoordinate2D
 *  
 *  Discussion:
 *    A structure that contains a geographical coordinate.
 *
 *  Fields:
 *    latitude:
 *      The latitude in degrees.
 *    longitude:
 *      The longitude in degrees.
 */
typedef struct {
	CLLocationDegrees latitude;
	CLLocationDegrees longitude;
} CLLocationCoordinate2D;

/*
 *  CLLocationDistance
 *  
 *  Discussion:
 *    Type used to represent a distance in meters.
 */
typedef double CLLocationDistance;

/*
 *  kCLDistanceFilterNone
 *  
 *  Discussion:
 *    Use as the distanceFilter property for CLLocationManager. This indicates 
 *    to the location service that no minimum movement filter is desired - ie, client will be informed
 *    of any movement.
 */
extern const CLLocationDistance kCLDistanceFilterNone;

/*
 *  kCLLocationAccuracy<x>
 *  
 *  Discussion:
 *    Used to specify the accuracy level desired. The location service will try its best to achieve
 *    your desired accuracy. However, it is not guaranteed. To optimize
 *    power performance, be sure to specify an appropriate accuracy for your usage scenario (eg,
 *    use a large accuracy value when only a coarse location is needed).
 */
extern const CLLocationAccuracy kCLLocationAccuracyBestForNavigation __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
extern const CLLocationAccuracy kCLLocationAccuracyBest;
extern const CLLocationAccuracy kCLLocationAccuracyNearestTenMeters;
extern const CLLocationAccuracy kCLLocationAccuracyHundredMeters;
extern const CLLocationAccuracy kCLLocationAccuracyKilometer;
extern const CLLocationAccuracy kCLLocationAccuracyThreeKilometers;

/*
 *  CLLocationDistanceMax
 *
 *  Discussion:
 *  	Used to specify the maximum CLLocationDistance
 */
extern const CLLocationDistance CLLocationDistanceMax __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

/*
 *  CLTimeIntervalMax
 *
 *  Discussion:
 *  	Used to specify the maximum NSTimeInterval
 */
extern const NSTimeInterval CLTimeIntervalMax __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

/*
 *  kCLLocationCoordinate2DInvalid
 *  
 *  Discussion:
 *    Used to specify an invalid CLLocationCoordinate2D.
 */
extern const CLLocationCoordinate2D kCLLocationCoordinate2DInvalid __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

#ifdef __cplusplus
extern "C" {
#endif    

/*
 *  CLLocationCoordinate2DIsValid
 *  
 *  Discussion:
 *    Returns YES if the specified coordinate is valid, NO otherwise.
 */
BOOL CLLocationCoordinate2DIsValid(CLLocationCoordinate2D coord) __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*
 *  CLLocationCoordinate2DMake:
 *
 *  Discussion:
 *    Returns a new CLLocationCoordinate2D at the given latitude and longitude
 */
CLLocationCoordinate2D CLLocationCoordinate2DMake(CLLocationDegrees latitude, CLLocationDegrees longitude) __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

#ifdef __cplusplus
}
#endif

/*
 *  CLFloor
 *
 *  Discussion:
 *    Encapsulates the information about a floor.
 */
NS_CLASS_AVAILABLE(NA, 8_0)
@interface CLFloor : NSObject <NSCopying, NSSecureCoding>

/*
 *  level
 *
 *  Discussion:
 *    This is a logical representation that will vary on definition from building-to-building.
 *    Floor 0 will always represent the floor designated as "ground".
 *    This number may be negative to designate floors below the ground floor
 *    and positive to indicate floors above the ground floor.
 *    It is not intended to match any numbering that might actually be used in the building.
 *    It is erroneous to use as an estimate of altitude.
 */
@property(readonly, nonatomic) NSInteger level;

@end

/*
 *  CLLocation
 *  
 *  Discussion:
 *    Represents a geographical coordinate along with accuracy and timestamp information.
 */
NS_CLASS_AVAILABLE(10_6, 2_0)
@interface CLLocation : NSObject <NSCopying, NSSecureCoding>
{
@private
	id _internal;
}

/*
 *  initWithLatitude:longitude:
 *  
 *  Discussion:
 *    Initialize with the specified latitude and longitude.
 */
- (instancetype)initWithLatitude:(CLLocationDegrees)latitude
	longitude:(CLLocationDegrees)longitude;

/*
 *  initWithCoordinate:altitude:horizontalAccuracy:verticalAccuracy:timestamp:
 *  
 *  Discussion:
 *    Initialize with the specified parameters.
 */
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate
	altitude:(CLLocationDistance)altitude
	horizontalAccuracy:(CLLocationAccuracy)hAccuracy
	verticalAccuracy:(CLLocationAccuracy)vAccuracy
	timestamp:(NSDate *)timestamp;

/*
 *  initWithCoordinate:altitude:horizontalAccuracy:verticalAccuracy:course:speed:timestamp:
 *  
 *  Discussion:
 *    Initialize with the specified parameters.
 */
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate
    altitude:(CLLocationDistance)altitude
    horizontalAccuracy:(CLLocationAccuracy)hAccuracy
    verticalAccuracy:(CLLocationAccuracy)vAccuracy
    course:(CLLocationDirection)course
    speed:(CLLocationSpeed)speed
    timestamp:(NSDate *)timestamp __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_2);

/*
 *  coordinate
 *  
 *  Discussion:
 *    Returns the coordinate of the current location.
 */
@property(readonly, nonatomic) CLLocationCoordinate2D coordinate;

/*
 *  altitude
 *  
 *  Discussion:
 *    Returns the altitude of the location. Can be positive (above sea level) or negative (below sea level).
 */
@property(readonly, nonatomic) CLLocationDistance altitude;

/*
 *  horizontalAccuracy
 *  
 *  Discussion:
 *    Returns the horizontal accuracy of the location. Negative if the lateral location is invalid.
 */
@property(readonly, nonatomic) CLLocationAccuracy horizontalAccuracy;

/*
 *  verticalAccuracy
 *  
 *  Discussion:
 *    Returns the vertical accuracy of the location. Negative if the altitude is invalid.
 */
@property(readonly, nonatomic) CLLocationAccuracy verticalAccuracy;

/*
 *  course
 *  
 *  Discussion:
 *    Returns the course of the location in degrees true North. Negative if course is invalid.
 *
 *  Range:
 *    0.0 - 359.9 degrees, 0 being true North
 */
@property(readonly, nonatomic) CLLocationDirection course __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_2_2) __WATCHOS_PROHIBITED;

/*
 *  speed
 *  
 *  Discussion:
 *    Returns the speed of the location in m/s. Negative if speed is invalid.
 */
@property(readonly, nonatomic) CLLocationSpeed speed __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_2_2) __WATCHOS_PROHIBITED;

/*
 *  timestamp
 *  
 *  Discussion:
 *    Returns the timestamp when this location was determined.
 */
@property(readonly, nonatomic, copy) NSDate *timestamp;

/*
 *  floor
 *
 *  Discussion:
 *    Contains information about the logical floor that you are on
 *    in the current building if you are inside a supported venue.
 *    This will be nil if the floor is unavailable.
 */
@property(readonly, nonatomic, copy, nullable) CLFloor *floor __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_8_0);

/*
 *  description
 *  
 *  Discussion:
 *    Returns a string representation of the location.
 */
@property (nonatomic, readonly, copy) NSString *description;

/*
 *  getDistanceFrom:
 *
 *  Discussion:
 *    Deprecated. Use -distanceFromLocation: instead.
 */
- (CLLocationDistance)getDistanceFrom:(const CLLocation *)location __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_3_2) __WATCHOS_PROHIBITED;

/*
 *  distanceFromLocation:
 *
 *  Discussion:
 *    Returns the lateral distance between two locations.
 */
- (CLLocationDistance)distanceFromLocation:(const CLLocation *)location __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_3_2);

@end

NS_ASSUME_NONNULL_END
// ==========  CoreLocation.framework/Headers/CLBeaconRegion.h
/*
 *  CLBeaconRegion.h
 *  CoreLocation
 *
 *  Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CLRegion.h>
#import <CoreLocation/CLAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CLBeaconMajorValue
 *
 *  Discussion:
 *    Type represents the most significant value in a beacon.
 *
 */
typedef uint16_t CLBeaconMajorValue;

/*
 *  CLBeaconMinorValue
 *
 *  Discussion:
 *    Type represents the least significant value in a beacon.
 *
 */
typedef uint16_t CLBeaconMinorValue;

/*
 *  CLBeaconRegion
 *
 *  Discussion:
 *    A region containing similar beacons.
 *
 *    Such a region can be defined by proximityUUID, major and minor values.
 *    proximityUUID must be specified. If proximityUUID is only specified, the major and
 *    minor values will be wildcarded and the region will match any beacons with the same
 *    proximityUUID. Similarly if only proximityUUID and major value are specified, the minor value will be
 *    wildcarded and the region will match against any beacons with the same proximityUUID and major
 *    value.
 *
 */
NS_CLASS_AVAILABLE(NA, 7_0) __WATCHOS_PROHIBITED
@interface CLBeaconRegion : CLRegion

/*
 *  initWithProximityUUID:identifier:
 *
 *  Discussion:
 *    Initialize a beacon region with a proximityUUID. Major and minor values will be wildcarded.
 *
 */
- (instancetype)initWithProximityUUID:(NSUUID *)proximityUUID identifier:(NSString *)identifier;

/*
 *  initWithProximityUUID:major:identifier:
 *
 *  Discussion:
 *    Initialize a beacon region with an proximityUUID and major value. Minor value will be wildcarded.
 *
 */
- (instancetype)initWithProximityUUID:(NSUUID *)proximityUUID major:(CLBeaconMajorValue)major identifier:(NSString *)identifier;

/*
 *  initWithProximityUUID:major:minor:identifier:
 *
 *  Discussion:
 *    Initialize a beacon region identified by an proximityUUID, major and minor values.
 *
 */
- (instancetype)initWithProximityUUID:(NSUUID *)proximityUUID major:(CLBeaconMajorValue)major minor:(CLBeaconMinorValue)minor identifier:(NSString *)identifier;

/*
 *  peripheralDataWithMeasuredPower:
 *
 *  Discussion:
 *    This dictionary can be used to advertise the current device as a beacon when
 *    used in conjunction with CoreBluetooth's CBPeripheralManager startAdvertising: method.
 *    The dictionary will contain data that represents the current region in addition to a measured power value.
 *
 *    measuredPower is the RSSI of the device observed from one meter in its intended environment.
 *    This value is optional, but should be specified to achieve the best ranging performance.
 *    If not specified, it will default to a pre-determined value for the device.
 *
 */
- (NSMutableDictionary<NSString *, id> *)peripheralDataWithMeasuredPower:(nullable NSNumber *)measuredPower;

/*
 *  proximityUUID
 *
 *  Discussion:
 *    Proximity identifier associated with the region.
 *
 */
@property (readonly, nonatomic, strong) NSUUID *proximityUUID;

/*
 *  major
 *
 *  Discussion:
 *    Most significant value associated with the region. If a major value wasn't specified, this will be nil.
 *
 */
@property (readonly, nonatomic, strong, nullable) NSNumber *major;

/*
 *  minor
 *
 *  Discussion:
 *    Least significant value associated with the region. If a minor value wasn't specified, this will be nil.
 *
 */
@property (readonly, nonatomic, strong, nullable) NSNumber *minor;

/*
 *  notifyEntryStateOnDisplay
 *
 *  Discussion:
 *    App will be launched and the delegate will be notified via locationManager:didDetermineState:forRegion:
 *    when the device's screen is turned on and the user is in the region. By default, this is NO.
 */
@property (nonatomic, assign) BOOL notifyEntryStateOnDisplay;

@end

/*
 *  CLBeacon
 *
 *  Discussion:
 *    A single beacon within a CLBeaconRegion.
 *
 */
NS_CLASS_AVAILABLE(NA, 7_0) __WATCHOS_PROHIBITED
@interface CLBeacon : NSObject <NSCopying, NSSecureCoding>

/*
 *  proximityUUID
 *
 *  Discussion:
 *    Proximity identifier associated with the beacon.
 *
 */
@property (readonly, nonatomic, strong) NSUUID *proximityUUID;

/*
 *  major
 *
 *  Discussion:
 *    Most significant value associated with the beacon.
 *
 */
@property (readonly, nonatomic, strong) NSNumber *major;

/*
 *  minor
 *
 *  Discussion:
 *    Least significant value associated with the beacon.
 *
 */
@property (readonly, nonatomic, strong) NSNumber *minor;

/*
 *  proximity
 *
 *  Discussion:
 *    Proximity of the beacon from the device.
 *
 */
@property (readonly, nonatomic) CLProximity proximity;

/*
 *  accuracy
 *
 *  Discussion:
 *    Represents an one sigma horizontal accuracy in meters where the measuring device's location is
 *    referenced at the beaconing device. This value is heavily subject to variations in an RF environment.
 *    A negative accuracy value indicates the proximity is unknown.
 *
 */
@property (readonly, nonatomic) CLLocationAccuracy accuracy;

/*
 *  rssi
 *
 *  Discussion:
 *    Received signal strength in decibels of the specified beacon.
 *    This value is an average of the RSSI samples collected since this beacon was last reported.
 *
 */
@property (readonly, nonatomic) NSInteger rssi;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreLocation.framework/Headers/CLGeocoder.h
/*
 *  CLGeocoder.h
 *  CoreLocation
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 */

#if TARGET_OS_IPHONE

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>
#import <CoreLocation/CLAvailability.h>

NS_ASSUME_NONNULL_BEGIN

@class CLRegion;
@class CLPlacemark;
@class CLGeocoderInternal;

// geocoding handler, CLPlacemarks are provided in order of most confident to least confident
typedef void (^CLGeocodeCompletionHandler)(NSArray< CLPlacemark *> * __nullable placemarks, NSError * __nullable error);

NS_CLASS_AVAILABLE(TBD,5_0)
@interface CLGeocoder : NSObject
{
@private
    CLGeocoderInternal *_internal;
}

@property (nonatomic, readonly, getter=isGeocoding) BOOL geocoding;

// reverse geocode requests
- (void)reverseGeocodeLocation:(CLLocation *)location completionHandler:(CLGeocodeCompletionHandler)completionHandler;

// forward geocode requests
// geocodeAddressDictionary:completionHandler: takes an address dictionary as defined by the AddressBook framework.
// You can obtain an address dictionary from an ABPerson by retrieving the kABPersonAddressProperty property.
// Alternately, one can be constructed using the kABPersonAddress* keys defined in <AddressBook/ABPerson.h>.

- (void)geocodeAddressDictionary:(NSDictionary *)addressDictionary completionHandler:(CLGeocodeCompletionHandler)completionHandler;
- (void)geocodeAddressString:(NSString *)addressString completionHandler:(CLGeocodeCompletionHandler)completionHandler;
- (void)geocodeAddressString:(NSString *)addressString inRegion:(nullable CLRegion *)region completionHandler:(CLGeocodeCompletionHandler)completionHandler;

- (void)cancelGeocode;

@end

NS_ASSUME_NONNULL_END

#endif //TARGET_OS_IPHONE
// ==========  CoreLocation.framework/Headers/CLLocationManager.h

/*
 *  CLLocationManager.h
 *  CoreLocation
 *
 *  Copyright (c) 2008-2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CLAvailability.h>
#import <CoreLocation/CLLocation.h>
#import <CoreLocation/CLRegion.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CLDeviceOrientation
 *  
 *  Discussion:
 *      Specifies a physical device orientation, equivalent to UIDeviceOrientation.
 *      
 */
typedef NS_ENUM(int, CLDeviceOrientation) {
	CLDeviceOrientationUnknown = 0,
	CLDeviceOrientationPortrait,
	CLDeviceOrientationPortraitUpsideDown,
	CLDeviceOrientationLandscapeLeft,
	CLDeviceOrientationLandscapeRight,
	CLDeviceOrientationFaceUp,
	CLDeviceOrientationFaceDown
};

/*
 *  CLAuthorizationStatus
 *  
 *  Discussion:
 *      Represents the current authorization state of the application.
 *      
 */
typedef NS_ENUM(int, CLAuthorizationStatus) {
	// User has not yet made a choice with regards to this application
	kCLAuthorizationStatusNotDetermined = 0,

	// This application is not authorized to use location services.  Due
	// to active restrictions on location services, the user cannot change
	// this status, and may not have personally denied authorization
	kCLAuthorizationStatusRestricted,

	// User has explicitly denied authorization for this application, or
	// location services are disabled in Settings.
	kCLAuthorizationStatusDenied,

	// User has granted authorization to use their location at any time,
	// including monitoring for regions, visits, or significant location changes.
	kCLAuthorizationStatusAuthorizedAlways NS_ENUM_AVAILABLE(NA, 8_0),

	// User has granted authorization to use their location only when your app
	// is visible to them (it will be made visible to them if you continue to
	// receive location updates while in the background).  Authorization to use
	// launch APIs has not been granted.
	kCLAuthorizationStatusAuthorizedWhenInUse NS_ENUM_AVAILABLE(NA, 8_0),

	// This value is deprecated, but was equivalent to the new -Always value.
	kCLAuthorizationStatusAuthorized NS_ENUM_DEPRECATED(10_6, NA, 2_0, 8_0, "Use kCLAuthorizationStatusAuthorizedAlways") __WATCHOS_PROHIBITED = kCLAuthorizationStatusAuthorizedAlways
};

/*
 *	CLActivityType
 *
 *  Discussion:
 *		Enumerates the different possible activity types. This currently
 *		affects behavior such as the determination of when location updates
 *		may be automatically paused.
 */
typedef NS_ENUM(NSInteger, CLActivityType) {
    CLActivityTypeOther = 1,
    CLActivityTypeAutomotiveNavigation,	// for automotive navigation
    CLActivityTypeFitness,				// includes any pedestrian activities
    CLActivityTypeOtherNavigation 		// for other navigation cases (excluding pedestrian navigation), e.g. navigation for boats, trains, or planes
};

@class CLLocation;
@class CLHeading;
@class CLBeaconRegion;
@protocol CLLocationManagerDelegate;

/*
 *  CLLocationManager
 *  
 *  Discussion:
 *    The CLLocationManager object is your entry point to the location service.
 */
NS_CLASS_AVAILABLE(10_6, 2_0)
@interface CLLocationManager : NSObject
{
@private
	id _internal;
}

/*
 *  locationServicesEnabled
 *
 *  Discussion:
 *      Determines whether the user has location services enabled.
 *      If NO, and you proceed to call other CoreLocation API, user will be prompted with the warning
 *      dialog. You may want to check this property and use location services only when explicitly requested by the user.
 */
+ (BOOL)locationServicesEnabled __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*
 *  headingAvailable
 *
 *  Discussion:
 *      Returns YES if the device supports the heading service, otherwise NO.
 */
+ (BOOL)headingAvailable __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0) __WATCHOS_PROHIBITED;

/*
 *  significantLocationChangeMonitoringAvailable
 *  
 *  Discussion:
 *      Returns YES if the device supports significant location change monitoring, otherwise NO.
 */
+ (BOOL)significantLocationChangeMonitoringAvailable __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0) __WATCHOS_PROHIBITED;

/*
 *  isMonitoringAvailableForClass:
 *
 *  Discussion:
 *      Determines whether the device supports monitoring for the specified type of region.
 *      If NO, all attempts to monitor the specified type of region will fail.
 */
+ (BOOL)isMonitoringAvailableForClass:(Class)regionClass __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0) __WATCHOS_PROHIBITED;

/*
 *  regionMonitoringAvailable
 *  
 *  Discussion:
 *      Deprecated. Use +isMonitoringAvailableForClass: instead.
 */
+ (BOOL)regionMonitoringAvailable __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_7,__MAC_NA,__IPHONE_4_0,__IPHONE_7_0) __WATCHOS_PROHIBITED;

/*
 *  regionMonitoringEnabled
 *  
 *  Discussion:
 *      Deprecated. Use +isMonitoringAvailableForClass: and +authorizationStatus instead.
 */
+ (BOOL)regionMonitoringEnabled __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA, __MAC_NA,__IPHONE_4_0, __IPHONE_6_0) __WATCHOS_PROHIBITED;

/*
 *  isRangingAvailable
 *
 *  Discussion:
 *      Determines whether the device supports ranging.
 *      If NO, all attempts to range beacons will fail.
 */
+ (BOOL)isRangingAvailable __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0) __WATCHOS_PROHIBITED;

/*
 *  authorizationStatus
 *  
 *  Discussion:
 *      Returns the current authorization status of the calling application.
 */
+ (CLAuthorizationStatus)authorizationStatus __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_2);

@property(assign, nonatomic, nullable) id<CLLocationManagerDelegate> delegate;

/*
 *  locationServicesEnabled
 *  
 *  Discussion:
 *      Deprecated. Use +locationServicesEnabled instead.
 */
@property(readonly, nonatomic) BOOL locationServicesEnabled __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_4_0) __WATCHOS_PROHIBITED;

/*
 *  purpose
 *  
 *  Discussion:
 *      Allows the application to specify what location will be used for in their app. This
 *      will be displayed along with the standard Location permissions dialogs. This property will need to be
 *      set prior to calling startUpdatingLocation.
 *
 *      Deprecated.  Set the purpose string in Info.plist using key NSLocationUsageDescription.
 */
@property(copy, nonatomic, nullable) NSString *purpose __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_7, __MAC_NA, __IPHONE_3_2, __IPHONE_6_0) __WATCHOS_PROHIBITED;

/*
 *	activityType
 *
 *  Discussion:
 *		Specifies the type of user activity. Currently affects behavior such as
 *		the determination of when location updates may be automatically paused.
 *		By default, CLActivityTypeOther is used.
 */
@property(assign, nonatomic) CLActivityType activityType __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0) __WATCHOS_PROHIBITED;

/*
 *  distanceFilter
 *  
 *  Discussion:
 *      Specifies the minimum update distance in meters. Client will not be notified of movements of less 
 *      than the stated value, unless the accuracy has improved. Pass in kCLDistanceFilterNone to be 
 *      notified of all movements. By default, kCLDistanceFilterNone is used.
 */
@property(assign, nonatomic) CLLocationDistance distanceFilter;

/*
 *  desiredAccuracy
 *  
 *  Discussion:
 *      The desired location accuracy. The location service will try its best to achieve
 *      your desired accuracy. However, it is not guaranteed. To optimize
 *      power performance, be sure to specify an appropriate accuracy for your usage scenario (eg,
 *      use a large accuracy value when only a coarse location is needed). Use kCLLocationAccuracyBest to
 *      achieve the best possible accuracy. Use kCLLocationAccuracyBestForNavigation for navigation.
 *      The default value varies by platform.
 */
@property(assign, nonatomic) CLLocationAccuracy desiredAccuracy;

/*
 *	pausesLocationUpdatesAutomatically
 *
 *  Discussion:
 *		Specifies that location updates may automatically be paused when possible.
 *		By default, this is YES for applications linked against iOS 6.0 or later.
 */
@property(assign, nonatomic) BOOL pausesLocationUpdatesAutomatically __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0) __WATCHOS_PROHIBITED;

/*
 *  allowsBackgroundLocationUpdates
 *
 *  Discussion:
 *      By default, this is NO for applications linked against iOS 9.0 or later,
 *      regardless of minimum deployment target.
 *
 *      With UIBackgroundModes set to include "location" in Info.plist, you must
 *      also set this property to YES at runtime whenever calling
 *      -startUpdatingLocation with the intent to continue in the background.
 *
 *      Setting this property to YES when UIBackgroundModes does not include
 *      "location" is a fatal error.
 *
 *      Resetting this property to NO is equivalent to omitting "location" from
 *      the UIBackgroundModes value.  Access to location is still permitted
 *      whenever the application is running (ie not suspended), and has
 *      sufficient authorization (ie it has WhenInUse authorization and is in
 *      use, or it has Always authorization).  However, the app will still be
 *      subject to the usual task suspension rules.
 *
 *      See -requestWhenInUseAuthorization and -requestAlwaysAuthorization for
 *      more details on possible authorization values.
 */
@property(assign, nonatomic) BOOL allowsBackgroundLocationUpdates __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_9_0) __WATCHOS_PROHIBITED;

/*
 *  location
 *  
 *  Discussion:
 *      The last location received. Will be nil until a location has been received.
 */
@property(readonly, nonatomic, copy, nullable) CLLocation *location;

/*
 *  headingAvailable
 *
 *  Discussion:
 *      Deprecated. Use +headingAvailable instead.
 */
@property(readonly, nonatomic) BOOL headingAvailable __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_3_0,__IPHONE_4_0) __WATCHOS_PROHIBITED;

/*
 *  headingFilter
 *  
 *  Discussion:
 *      Specifies the minimum amount of change in degrees needed for a heading service update. Client will not
 *      be notified of updates less than the stated filter value. Pass in kCLHeadingFilterNone to be
 *      notified of all updates. By default, 1 degree is used.
 */
@property(assign, nonatomic) CLLocationDegrees headingFilter __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0) __WATCHOS_PROHIBITED;

/*
 *  headingOrientation
 *  
 *  Discussion:
 *      Specifies a physical device orientation from which heading calculation should be referenced. By default,
 *      CLDeviceOrientationPortrait is used. CLDeviceOrientationUnknown, CLDeviceOrientationFaceUp, and
 *      CLDeviceOrientationFaceDown are ignored.
 *      
 */
@property(assign, nonatomic) CLDeviceOrientation headingOrientation __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0) __WATCHOS_PROHIBITED;

/*
 *  heading
 *  
 *  Discussion:
 *      Returns the latest heading update received, or nil if none is available.
 */
@property(readonly, nonatomic, copy, nullable) CLHeading *heading __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0) __WATCHOS_PROHIBITED;

/*
 *  maximumRegionMonitoringDistance
 *  
 *  Discussion:
 *       the maximum region size, in terms of a distance from a central point, that the framework can support.
 *       Attempts to register a region larger than this will generate a kCLErrorRegionMonitoringFailure.
 *       This value may vary based on the hardware features of the device, as well as on dynamically changing resource constraints.
 */
@property (readonly, nonatomic) CLLocationDistance maximumRegionMonitoringDistance __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0) __WATCHOS_PROHIBITED;

/*
 *  monitoredRegions
 *  
 *  Discussion:
 *       Retrieve a set of objects for the regions that are currently being monitored.  If any location manager
 *       has been instructed to monitor a region, during this or previous launches of your application, it will
 *       be present in this set.
 */
@property (readonly, nonatomic, copy) NSSet<__kindof CLRegion *> *monitoredRegions __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0) __WATCHOS_PROHIBITED;

/*
 *  rangedRegions
 *
 *  Discussion:
 *       Retrieve a set of objects representing the regions for which this location manager is actively providing ranging.
 */
@property (readonly, nonatomic, copy) NSSet<__kindof CLRegion *> *rangedRegions __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0) __WATCHOS_PROHIBITED;

/*
 *  requestWhenInUseAuthorization
 *
 *  Discussion:
 *      When +authorizationStatus == kCLAuthorizationStatusNotDetermined,
 *      calling this method will trigger a prompt to request "when-in-use"
 *      authorization from the user.  If possible, perform this call in response
 *      to direct user request for a location-based service so that the reason
 *      for the prompt will be clear.  Any authorization change as a result of
 *      the prompt will be reflected via the usual delegate callback:
 *      -locationManager:didChangeAuthorizationStatus:.
 *
 *      If received, "when-in-use" authorization grants access to the user's
 *      location via -startUpdatingLocation/-startRangingBeaconsInRegion while
 *      in the foreground.  If updates have been started when going to the
 *      background, then a status bar banner will be displayed to maintain
 *      visibility to the user, and updates will continue until stopped
 *      normally, or the app is killed by the user.
 *
 *      "When-in-use" authorization does NOT enable monitoring API on regions,
 *      significant location changes, or visits, and -startUpdatingLocation will
 *      not succeed if invoked from the background.
 *
 *      When +authorizationStatus != kCLAuthorizationStatusNotDetermined, (ie
 *      generally after the first call) this method will do nothing.
 *
 *      If the NSLocationWhenInUseUsageDescription key is not specified in your
 *      Info.plist, this method will do nothing, as your app will be assumed not
 *      to support WhenInUse authorization.
 */
- (void)requestWhenInUseAuthorization __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_8_0);

/*
 *  requestAlwaysAuthorization
 *
 *  Discussion:
 *      When +authorizationStatus == kCLAuthorizationStatusNotDetermined,
 *      calling this method will trigger a prompt to request "always"
 *      authorization from the user.  If possible, perform this call in response
 *      to direct user request for a location-based service so that the reason
 *      for the prompt will be clear.  Any authorization change as a result of
 *      the prompt will be reflected via the usual delegate callback:
 *      -locationManager:didChangeAuthorizationStatus:.
 *
 *      If received, "always" authorization grants access to the user's
 *      location via any CLLocationManager API, and grants access to
 *      launch-capable monitoring API such as geofencing/region monitoring,
 *      significante location visits, etc.  Even if killed by the user, launch
 *      events triggered by monitored regions or visit patterns will cause a
 *      relaunch.
 *
 *      "Always" authorization presents a significant risk to user privacy, and
 *      as such requesting it is discouraged unless background launch behavior
 *      is genuinely required.  Do not call +requestAlwaysAuthorization unless
 *      you think users will thank you for doing so.
 *
 *      When +authorizationStatus != kCLAuthorizationStatusNotDetermined, (ie
 *      generally after the first call) this method will do nothing.
 *
 *      If the NSLocationAlwaysUsageDescription key is not specified in your
 *      Info.plist, this method will do nothing, as your app will be assumed not
 *      to support Always authorization.
 */
- (void)requestAlwaysAuthorization __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_8_0);

/*
 *  startUpdatingLocation
 *  
 *  Discussion:
 *      Start updating locations.
 */
- (void)startUpdatingLocation __WATCHOS_PROHIBITED;

/*
 *  stopUpdatingLocation
 *  
 *  Discussion:
 *      Stop updating locations.
 */
- (void)stopUpdatingLocation;

/*
 *  requestLocation
 *
 *  Discussion:
 *      Request a single location update.
 *
 *      The service will attempt to determine location with accuracy according
 *      to the desiredAccuracy property.  The location update will be delivered
 *      via the standard delegate callback, i.e. locationManager:didUpdateLocations:
 *
 *      If the best available location has lower accuracy, then it will be
 *      delivered via the standard delegate callback after timeout.
 *
 *      If no location can be determined, the locationManager:didFailWithError:
 *      delegate callback will be delivered with error location unknown.
 *
 *      There can only be one outstanding location request and this method can
 *      not be used concurrently with startUpdatingLocation or
 *      allowDeferredLocationUpdates.  Calling either of those methods will
 *      immediately cancel the location request.  The method
 *      stopUpdatingLocation can be used to explicitly cancel the request.
 */
- (void)requestLocation __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_9_0);

/*
 *  startUpdatingHeading
 *
 *  Discussion:
 *      Start updating heading.
 */
- (void)startUpdatingHeading __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0) __WATCHOS_PROHIBITED;

/*
 *  stopUpdatingHeading
 *
 *  Discussion:
 *      Stop updating heading.
 */
- (void)stopUpdatingHeading __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0) __WATCHOS_PROHIBITED;

/*
 *  dismissHeadingCalibrationDisplay
 *  
 *  Discussion:
 *      Dismiss the heading calibration immediately.
 */
- (void)dismissHeadingCalibrationDisplay __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0) __WATCHOS_PROHIBITED;

/*
 *  startMonitoringSignificantLocationChanges
 *
 *  Discussion:
 *      Start monitoring significant location changes.  The behavior of this service is not affected by the desiredAccuracy
 *      or distanceFilter properties.  Locations will be delivered through the same delegate callback as the standard
 *      location service.
 *
 */
- (void)startMonitoringSignificantLocationChanges __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0) __WATCHOS_PROHIBITED;

/*
 *  stopMonitoringSignificantLocationChanges
 *
 *  Discussion:
 *      Stop monitoring significant location changes.
 *
 */
- (void)stopMonitoringSignificantLocationChanges __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0) __WATCHOS_PROHIBITED;

/*
 *  startMonitoringForRegion:desiredAccuracy:
 *
 *  Discussion:
 *      Start monitoring the specified region.  desiredAccuracy represents the distance past the border of the region at
 *      which the application would like to be notified that the region border has been crossed.  This is useful to prevent
 *      repeated notifications when the user is on the border of the region.  This value will be honored on a best-effort basis,
 *      and may not be respected if desiredAccuracy is large with respect to the size of the region, or if the device is not
 *      capable of providing the precision desired.
 *
 *      If a region of the same type with the same identifier is already being monitored for this application, it will be
 *      removed from monitoring.
 *
 *      This is done asynchronously and may not be immediately reflected in monitoredRegions.
 */
- (void)startMonitoringForRegion:(CLRegion *)region
                 desiredAccuracy:(CLLocationAccuracy)accuracy __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA, __MAC_NA,__IPHONE_4_0, __IPHONE_6_0) __WATCHOS_PROHIBITED;

/*
 *  stopMonitoringForRegion:
 *
 *  Discussion:
 *      Stop monitoring the specified region.  It is valid to call stopMonitoringForRegion: for a region that was registered
 *      for monitoring with a different location manager object, during this or previous launches of your application.
 *
 *      This is done asynchronously and may not be immediately reflected in monitoredRegions.
 */
- (void)stopMonitoringForRegion:(CLRegion *)region __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0) __WATCHOS_PROHIBITED;

/*
 *  startMonitoringForRegion:
 *
 *  Discussion:
 *      Start monitoring the specified region.
 *
 *      If a region of the same type with the same identifier is already being monitored for this application,
 *      it will be removed from monitoring. For circular regions, the region monitoring service will prioritize
 *      regions by their size, favoring smaller regions over larger regions.
 *
 *      This is done asynchronously and may not be immediately reflected in monitoredRegions.
 */
- (void)startMonitoringForRegion:(CLRegion *)region __OSX_AVAILABLE_STARTING(__MAC_TBD,__IPHONE_5_0) __WATCHOS_PROHIBITED;

/*
 *  requestStateForRegion:
 *
 *  Discussion:
 *      Asynchronously retrieve the cached state of the specified region. The state is returned to the delegate via
 *      locationManager:didDetermineState:forRegion:.
 */
- (void)requestStateForRegion:(CLRegion *)region __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0) __WATCHOS_PROHIBITED;

/*
 *  startRangingBeaconsInRegion:
 *
 *  Discussion:
 *      Start calculating ranges for beacons in the specified region.
 */
- (void)startRangingBeaconsInRegion:(CLBeaconRegion *)region __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0) __WATCHOS_PROHIBITED;

/*
 *  stopRangingBeaconsInRegion:
 *
 *  Discussion:
 *      Stop calculating ranges for the specified region.
 */
- (void)stopRangingBeaconsInRegion:(CLBeaconRegion *)region __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0) __WATCHOS_PROHIBITED;

/*
 *	allowDeferredLocationUpdatesUntilTraveled:timeout:
 *
 *	Discussion:
 *		Indicate that the application will allow the location manager to defer
 *		location updates until an exit criterion is met. This may allow the
 *		device to enter a low-power state in which updates are held for later
 *		delivery. Once an exit condition is met, the location manager will
 *		continue normal updates until this method is invoked again.
 *
 *		Exit conditions, distance and timeout, can be specified using the constants
 *		CLLocationDistanceMax and CLTimeIntervalMax, respectively, if you are
 *		trying to achieve an unlimited distance or timeout.
 *
 *		The CLLocationManagerDelegate will continue to receive normal updates as
 *		long as the application remains in the foreground. While the process is
 *		in the background, the device may be able to enter a low-power state for
 *		portions of the specified distance and time interval. While in this
 *		state, locations will be coalesced for later delivery.
 *
 *		Location updates will be deferred as much as is reasonable to save
 *		power. If another process is using location, the device may not enter a
 *		low-power state and instead updates will continue normally. Deferred
 *		updates may be interspersed with normal updates if the device exits and
 *		re-enters a low-power state.
 *
 *		All location updates, including deferred updates, will be delivered via
 *		the delegate callback locationManager:didUpdateLocations:
 *
 *		When deferred updates have ended, the manager will invoke the delegate
 *		callback locationManagerDidFinishDeferredUpdates:withError:. An error
 *		will be returned if the manager will not defer updates and the exit
 *		criteria have not been met.
 */
- (void)allowDeferredLocationUpdatesUntilTraveled:(CLLocationDistance)distance
					  timeout:(NSTimeInterval)timeout __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0) __WATCHOS_PROHIBITED;

/*
 *	disallowDeferredLocationUpdates
 *
 *	Discussion:
 *		Disallow deferred location updates if previously enabled. Any outstanding
 *		updates will be sent and regular location updates will resume.
 */
- (void)disallowDeferredLocationUpdates __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0) __WATCHOS_PROHIBITED;

/*
 *  deferredLocationUpdatesAvailable
 *
 *  Discussion:
 *      Returns YES if the device supports deferred location updates, otherwise NO.
 */
+ (BOOL)deferredLocationUpdatesAvailable __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreLocation.framework/Headers/CLErrorDomain.h

/*
 *  CLErrorDomain.h
 *  CoreLocation
 *
 *  Copyright 2008 Apple, Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  kCLErrorDomain
 *  
 *  Discussion:
 *    Error returned as the domain to NSError from CoreLocation.
 */
extern NSString *const kCLErrorDomain;

NS_ASSUME_NONNULL_END
// ==========  CoreLocation.framework/Headers/CoreLocation.h
/*
 *  CoreLocation.h
 *  CoreLocation
 *
 *  Copyright (c) 2008-2010 Apple Inc. All rights reserved.
 *
 */


#ifndef __CORELOCATION__
#define __CORELOCATION__

#ifndef __CL_INDIRECT__
#define __CL_INDIRECT__
#endif

#import <CoreLocation/CLAvailability.h>
#import <CoreLocation/CLErrorDomain.h>
#import <CoreLocation/CLError.h>
#import <CoreLocation/CLRegion.h>
#import <CoreLocation/CLCircularRegion.h>
#import <CoreLocation/CLBeaconRegion.h>
#import <CoreLocation/CLHeading.h>
#import <CoreLocation/CLLocation.h>
#import <CoreLocation/CLLocationManager.h>
#import <CoreLocation/CLLocationManagerDelegate.h>
#import <CoreLocation/CLLocationManager+CLVisitExtensions.h>
#import <CoreLocation/CLPlacemark.h>
#import <CoreLocation/CLGeocoder.h>
#import <CoreLocation/CLVisit.h>

#endif /* __CORELOCATION__ */
// ==========  CoreLocation.framework/Headers/CLLocationManager+CLVisitExtensions.h
/*
 *  CLLocationManager+CLVisitExtensions.h
 *  CoreLocation
 *
 *  Copyright (c) 2014 Apple Inc. All rights reserved.
 *
 */

#import <CoreLocation/CLLocationManager.h>

NS_ASSUME_NONNULL_BEGIN

@interface CLLocationManager (CLVisitExtensions)

/*
 *  startMonitoringVisits
 *
 *  Discussion:
 *    Begin monitoring for visits.  All CLLLocationManagers allocated by your
 *    application, both current and future, will deliver detected visits to
 *    their delegates.  This will continue until -stopMonitoringVisits is sent
 *    to any such CLLocationManager, even across application relaunch events.
 *
 *    Detected visits are sent to the delegate's -locationManager:didVisit:
 *    method.
 */
- (void)startMonitoringVisits NS_AVAILABLE(NA, 8_0) __WATCHOS_PROHIBITED;

/*
 *  stopMonitoringVisits
 *
 *  Discussion:
 *    Stop monitoring for visits.  To resume visit monitoring, send
 *    -startMonitoringVisits.
 *
 *    Note that stopping and starting are asynchronous operations and may not
 *    immediately reflect in delegate callback patterns.
 */
- (void)stopMonitoringVisits NS_AVAILABLE(NA, 8_0) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreLocation.framework/Headers/CLAvailability.h
/*
 *  CLAvailability.h
 *  CoreLocation
 *
 *  Copyright 2011 Apple Inc. All rights reserved.
 *
 */

/*
#ifndef __CL_INDIRECT__
#error "Please #include <CoreLocation/CoreLocation.h> instead of this file directly."
#endif // __CL_INDIRECT__
*/

#import <Availability.h>

#ifndef __MAC_TBD
#define __MAC_TBD __MAC_NA
#endif

#ifndef __AVAILABILITY_INTERNAL__MAC_TBD
#define __AVAILABILITY_INTERNAL__MAC_TBD __AVAILABILITY_INTERNAL_UNAVAILABLE
#endif


#ifndef __WATCHOS_PROHIBITED
#define __WATCHOS_PROHIBITED
#endif

#ifdef __cplusplus
#define CL_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define CL_EXTERN extern __attribute__((visibility ("default")))
#endif
// ==========  CoreLocation.framework/Headers/CLVisit.h
/*
 *  CLVisit.h
 *  CoreLocation
 *
 *  Copyright (c) 2014 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CLVisit
 *
 *  Discussion
 *    An instance of this class represents a possibly open-ended event
 *    during which the device was at the specified coordinate.
 */
NS_CLASS_AVAILABLE(NA, 8_0) __WATCHOS_PROHIBITED
@interface CLVisit : NSObject <NSSecureCoding, NSCopying>

/*
 *  arrivalDate
 *
 *  Discussion:
 *    The date when the visit began.  This may be equal to [NSDate
 *    distantPast] if the true arrival date isn't available.
 */
@property (nonatomic, readonly, copy) NSDate *arrivalDate;

/*
 *  departureDate
 *
 *  Discussion:
 *    The date when the visit ended.  This is equal to [NSDate
 *    distantFuture] if the device hasn't yet left.
 */
@property (nonatomic, readonly, copy) NSDate *departureDate;

/*
 *  coordinate
 *
 *  Discussion:
 *    The center of the region which the device is visiting.
 */
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

/*
 *
 *  horizontalAccuracy
 *
 *  Discussion:
 *    An estimate of the radius (in meters) of the region which the
 *    device is visiting.
 */
@property (nonatomic, readonly) CLLocationAccuracy horizontalAccuracy;
@end

NS_ASSUME_NONNULL_END
// ==========  CoreLocation.framework/Headers/CLHeading.h

/*
 *  CLHeading.h
 *  CoreLocation
 *
 *  Copyright 2008 Apple, Inc. All rights reserved.
 *
 */

#import <CoreLocation/CLAvailability.h>
#import <CoreLocation/CLLocation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CLHeadingComponentValue
 *  
 *  Discussion:
 *    Type represents a geomagnetic value, measured in microteslas, relative to a device axis in three dimensional space.
 *
 */
typedef double CLHeadingComponentValue;

/*
 *  kCLHeadingFilterNone
 *  
 *  Discussion:
 *    Use as the headingFilter property for CLLocationManager. This indicates 
 *    to the heading service that no minimum movement filter is desired - ie, client will be informed
 *    of any movement.
 */
extern const CLLocationDegrees kCLHeadingFilterNone;

/*
 *  CLHeading
 *  
 *  Discussion:
 *    Represents a vector pointing to magnetic North constructed from axis component values x, y, and z. An accuracy of the heading calculation is also provided along with timestamp information.
 */
NS_CLASS_AVAILABLE(10_7, 3_0) __WATCHOS_PROHIBITED
@interface CLHeading : NSObject <NSCopying, NSSecureCoding>
{
@private
    id _internal;
}

/*
 *  magneticHeading
 *  
 *  Discussion:
 *    Represents the direction in degrees, where 0 degrees is magnetic North. The direction is referenced from the top of the device regardless of device orientation as well as the orientation of the user interface.
 *
 *  Range:
 *    0.0 - 359.9 degrees, 0 being magnetic North
 */
@property(readonly, nonatomic) CLLocationDirection magneticHeading;

/*
 *  trueHeading
 *  
 *  Discussion:
 *    Represents the direction in degrees, where 0 degrees is true North. The direction is referenced
 *    from the top of the device regardless of device orientation as well as the orientation of the
 *    user interface.
 *
 *  Range:
 *    0.0 - 359.9 degrees, 0 being true North
 */
@property(readonly, nonatomic) CLLocationDirection trueHeading;

/*
 *  headingAccuracy
 *  
 *  Discussion:
 *    Represents the maximum deviation of where the magnetic heading may differ from the actual geomagnetic heading in degrees. A negative value indicates an invalid heading.
 */
@property(readonly, nonatomic) CLLocationDirection headingAccuracy;

/*
 *  x
 *  
 *  Discussion:
 *    Returns a raw value for the geomagnetism measured in the x-axis.
 *
 */
@property(readonly, nonatomic) CLHeadingComponentValue x;

/*
 *  y
 *  
 *  Discussion:
 *    Returns a raw value for the geomagnetism measured in the y-axis.
 *
 */
@property(readonly, nonatomic) CLHeadingComponentValue y;

/*
 *  z
 *  
 *  Discussion:
 *    Returns a raw value for the geomagnetism measured in the z-axis.
 *
 */
@property(readonly, nonatomic) CLHeadingComponentValue z;

/*
 *  timestamp
 *  
 *  Discussion:
 *    Returns a timestamp for when the magnetic heading was determined.
 */
@property(readonly, nonatomic, copy) NSDate *timestamp;

/*
 *  description
 *  
 *  Discussion:
 *    Returns a string representation of the heading.
 */
@property (nonatomic, readonly, copy) NSString *description;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreLocation.framework/Headers/CLRegion.h
/*
 *  CLRegion.h
 *  CoreLocation
 *
 *  Copyright (c) 2009-2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>
#import <CoreLocation/CLAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * CLRegionState
 *
 * Discussion:
 *    Represents the current state of the device with reference to a region.
 *
 */
typedef NS_ENUM(NSInteger, CLRegionState) {
	CLRegionStateUnknown,
	CLRegionStateInside,
	CLRegionStateOutside
} NS_ENUM_AVAILABLE_IOS(7_0) __WATCHOS_PROHIBITED;

/*
 * CLProximity
 *
 * Discussion:
 *    Represents the current proximity of an entity.
 *
 */
typedef NS_ENUM(NSInteger, CLProximity) {
	CLProximityUnknown,
	CLProximityImmediate,
	CLProximityNear,
	CLProximityFar
} NS_ENUM_AVAILABLE_IOS(7_0) __WATCHOS_PROHIBITED;

/*
 *  CLRegion
 *  
 *  Discussion:
 *    A logical area.
 */
NS_CLASS_AVAILABLE(10_7, 4_0)
@interface CLRegion : NSObject <NSCopying, NSSecureCoding>

/*
 *  initCircularRegionWithCenter:radius:identifier:
 *  
 *  Discussion:
 *    Initialize a region.  center gives the coordinates of center of the region, while radius gives
 *    the distance in meters between the center and the region's boundary. identifier is a description
 *    for the region that could be displayed to the user, and ideally should be chosen by the user.
 *
 *    This method has been deprecated, please see CLCircularRegion.
 */
- (instancetype)initCircularRegionWithCenter:(CLLocationCoordinate2D)center
									  radius:(CLLocationDistance)radius
								  identifier:(NSString *)identifier __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_7,__MAC_NA,__IPHONE_4_0,__IPHONE_7_0);

/*
 *  center
 *  
 *  Discussion:
 *    Returns the coordinate of the center of the region.
 *
 *    This method has been deprecated, please see CLCircularRegion.
 */
@property (readonly, nonatomic) CLLocationCoordinate2D center __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_7,__MAC_NA,__IPHONE_4_0,__IPHONE_7_0);

/*
 *  radius
 *  
 *  Discussion:
 *    Returns the radius of the region.
 *
 *    This method has been deprecated, please see CLCircularRegion.
 */
@property (readonly, nonatomic) CLLocationDistance radius __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_7,__MAC_NA,__IPHONE_4_0,__IPHONE_7_0);

/*
 *  identifier
 *  
 *  Discussion:
 *    Returns the region's identifier.
 */
@property (readonly, nonatomic, copy) NSString *identifier __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*
 *  notifyOnEntry
 *
 *  Discussion:
 *    App will be launched and the delegate will be notified via locationManager:didEnterRegion:
 *    when the user enters the region. By default, this is YES.
 */
@property (nonatomic, assign) BOOL notifyOnEntry __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

/*
 *  notifyOnExit
 *
 *  Discussion:
 *    App will be launched and the delegate will be notified via locationManager:didExitRegion:
 *    when the user exits the region. By default, this is YES.
 */
@property (nonatomic, assign) BOOL notifyOnExit __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

/*
 *  containsCoordinate:
 *
 *  Discussion:
 *    Returns YES if the coordinate lies inside the region, and NO otherwise.
 *
 *    This method has been deprecated, please see CLCircularRegion.
 */
- (BOOL)containsCoordinate:(CLLocationCoordinate2D)coordinate __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_7,__MAC_NA,__IPHONE_4_0,__IPHONE_7_0);

@end

NS_ASSUME_NONNULL_END
// ==========  CoreLocation.framework/Headers/CLError.h

/*
 *  CLError.h
 *  CoreLocation
 *
 *  Copyright (c) 2008-2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CLAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CLError
 *  
 *  Discussion:
 *    Error returned as code to NSError from CoreLocation.
 */
typedef NS_ENUM(NSInteger, CLError) {
    kCLErrorLocationUnknown  = 0,         // location is currently unknown, but CL will keep trying
    kCLErrorDenied,                       // Access to location or ranging has been denied by the user
    kCLErrorNetwork,                      // general, network-related error
    kCLErrorHeadingFailure,               // heading could not be determined
    kCLErrorRegionMonitoringDenied,       // Location region monitoring has been denied by the user
    kCLErrorRegionMonitoringFailure,      // A registered region cannot be monitored
    kCLErrorRegionMonitoringSetupDelayed, // CL could not immediately initialize region monitoring
    kCLErrorRegionMonitoringResponseDelayed, // While events for this fence will be delivered, delivery will not occur immediately
    kCLErrorGeocodeFoundNoResult,         // A geocode request yielded no result
    kCLErrorGeocodeFoundPartialResult,    // A geocode request yielded a partial result
    kCLErrorGeocodeCanceled,              // A geocode request was cancelled
    kCLErrorDeferredFailed,               // Deferred mode failed
    kCLErrorDeferredNotUpdatingLocation,  // Deferred mode failed because location updates disabled or paused
    kCLErrorDeferredAccuracyTooLow,       // Deferred mode not supported for the requested accuracy
    kCLErrorDeferredDistanceFiltered,     // Deferred mode does not support distance filters
    kCLErrorDeferredCanceled,             // Deferred mode request canceled a previous request
	kCLErrorRangingUnavailable,           // Ranging cannot be performed
	kCLErrorRangingFailure,               // General ranging failure
};

/*
 *  kCLErrorUserInfoAlternateRegionKey
 *  
 *  Discussion:
 *    When an error with code kCLErrorRegionMonitoringResponseDelayed is received, this key may be populated
 *    in the userInfo dictionary.  The value is a CLRegion that the location service can more effectively monitor.
 */
extern NSString *const kCLErrorUserInfoAlternateRegionKey NS_AVAILABLE(10_7, 5_0) __WATCHOS_PROHIBITED;

NS_ASSUME_NONNULL_END
// ==========  CoreLocation.framework/Headers/CLLocationManagerDelegate.h

/*
 *  CLLocationManagerDelegate.h
 *  CoreLocation
 *
 *  Copyright (c) 2008-2010 Apple Inc. All rights reserved.
 *
 */

#import <Availability.h>
#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocationManager.h>
#import <CoreLocation/CLRegion.h>
#import <CoreLocation/CLVisit.h>

NS_ASSUME_NONNULL_BEGIN

@class CLLocation;
@class CLHeading;
@class CLBeacon;

/*
 *  CLLocationManagerDelegate
 *  
 *  Discussion:
 *    Delegate for CLLocationManager.
 */
@protocol CLLocationManagerDelegate<NSObject>

@optional

/*
 *  locationManager:didUpdateToLocation:fromLocation:
 *  
 *  Discussion:
 *    Invoked when a new location is available. oldLocation may be nil if there is no previous location
 *    available.
 *
 *    This method is deprecated. If locationManager:didUpdateLocations: is
 *    implemented, this method will not be called.
 */
- (void)locationManager:(CLLocationManager *)manager
	didUpdateToLocation:(CLLocation *)newLocation
		   fromLocation:(CLLocation *)oldLocation __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_6, __MAC_NA, __IPHONE_2_0, __IPHONE_6_0) __WATCHOS_PROHIBITED;

/*
 *  locationManager:didUpdateLocations:
 *
 *  Discussion:
 *    Invoked when new locations are available.  Required for delivery of
 *    deferred locations.  If implemented, updates will
 *    not be delivered to locationManager:didUpdateToLocation:fromLocation:
 *
 *    locations is an array of CLLocation objects in chronological order.
 */
- (void)locationManager:(CLLocationManager *)manager
	 didUpdateLocations:(NSArray<CLLocation *> *)locations __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

/*
 *  locationManager:didUpdateHeading:
 *  
 *  Discussion:
 *    Invoked when a new heading is available.
 */
- (void)locationManager:(CLLocationManager *)manager
       didUpdateHeading:(CLHeading *)newHeading __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0) __WATCHOS_PROHIBITED;

/*
 *  locationManagerShouldDisplayHeadingCalibration:
 *
 *  Discussion:
 *    Invoked when a new heading is available. Return YES to display heading calibration info. The display 
 *    will remain until heading is calibrated, unless dismissed early via dismissHeadingCalibrationDisplay.
 */
- (BOOL)locationManagerShouldDisplayHeadingCalibration:(CLLocationManager *)manager  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0) __WATCHOS_PROHIBITED;

/*
 *  locationManager:didDetermineState:forRegion:
 *
 *  Discussion:
 *    Invoked when there's a state transition for a monitored region or in response to a request for state via a
 *    a call to requestStateForRegion:.
 */
- (void)locationManager:(CLLocationManager *)manager
	didDetermineState:(CLRegionState)state forRegion:(CLRegion *)region __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0) __WATCHOS_PROHIBITED;

/*
 *  locationManager:didRangeBeacons:inRegion:
 *
 *  Discussion:
 *    Invoked when a new set of beacons are available in the specified region.
 *    beacons is an array of CLBeacon objects.
 *    If beacons is empty, it may be assumed no beacons that match the specified region are nearby.
 *    Similarly if a specific beacon no longer appears in beacons, it may be assumed the beacon is no longer received
 *    by the device.
 */
- (void)locationManager:(CLLocationManager *)manager
	didRangeBeacons:(NSArray<CLBeacon *> *)beacons inRegion:(CLBeaconRegion *)region __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0) __WATCHOS_PROHIBITED;

/*
 *  locationManager:rangingBeaconsDidFailForRegion:withError:
 *
 *  Discussion:
 *    Invoked when an error has occurred ranging beacons in a region. Error types are defined in "CLError.h".
 */
- (void)locationManager:(CLLocationManager *)manager
	rangingBeaconsDidFailForRegion:(CLBeaconRegion *)region
	withError:(NSError *)error __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0) __WATCHOS_PROHIBITED;

/*
 *  locationManager:didEnterRegion:
 *
 *  Discussion:
 *    Invoked when the user enters a monitored region.  This callback will be invoked for every allocated
 *    CLLocationManager instance with a non-nil delegate that implements this method.
 */
- (void)locationManager:(CLLocationManager *)manager
	didEnterRegion:(CLRegion *)region __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0) __WATCHOS_PROHIBITED;

/*
 *  locationManager:didExitRegion:
 *
 *  Discussion:
 *    Invoked when the user exits a monitored region.  This callback will be invoked for every allocated
 *    CLLocationManager instance with a non-nil delegate that implements this method.
 */
- (void)locationManager:(CLLocationManager *)manager
	didExitRegion:(CLRegion *)region __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0) __WATCHOS_PROHIBITED;

/*
 *  locationManager:didFailWithError:
 *  
 *  Discussion:
 *    Invoked when an error has occurred. Error types are defined in "CLError.h".
 */
- (void)locationManager:(CLLocationManager *)manager
	didFailWithError:(NSError *)error;

/*
 *  locationManager:monitoringDidFailForRegion:withError:
 *  
 *  Discussion:
 *    Invoked when a region monitoring error has occurred. Error types are defined in "CLError.h".
 */
- (void)locationManager:(CLLocationManager *)manager
	monitoringDidFailForRegion:(nullable CLRegion *)region
	withError:(NSError *)error __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0) __WATCHOS_PROHIBITED;

/*
 *  locationManager:didChangeAuthorizationStatus:
 *  
 *  Discussion:
 *    Invoked when the authorization status changes for this application.
 */
- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_2);

/*
 *  locationManager:didStartMonitoringForRegion:
 *  
 *  Discussion:
 *    Invoked when a monitoring for a region started successfully.
 */
- (void)locationManager:(CLLocationManager *)manager
	didStartMonitoringForRegion:(CLRegion *)region __OSX_AVAILABLE_STARTING(__MAC_TBD,__IPHONE_5_0) __WATCHOS_PROHIBITED;

/*
 *  Discussion:
 *    Invoked when location updates are automatically paused.
 */
- (void)locationManagerDidPauseLocationUpdates:(CLLocationManager *)manager __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0) __WATCHOS_PROHIBITED;

/*
 *  Discussion:
 *    Invoked when location updates are automatically resumed.
 *
 *    In the event that your application is terminated while suspended, you will
 *	  not receive this notification.
 */
- (void)locationManagerDidResumeLocationUpdates:(CLLocationManager *)manager __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0) __WATCHOS_PROHIBITED;

/*
 *  locationManager:didFinishDeferredUpdatesWithError:
 *
 *  Discussion:
 *    Invoked when deferred updates will no longer be delivered. Stopping
 *    location, disallowing deferred updates, and meeting a specified criterion
 *    are all possible reasons for finishing deferred updates.
 *
 *    An error will be returned if deferred updates end before the specified
 *    criteria are met (see CLError), otherwise error will be nil.
 */
- (void)locationManager:(CLLocationManager *)manager
	didFinishDeferredUpdatesWithError:(nullable NSError *)error __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0) __WATCHOS_PROHIBITED;

/*
 *  locationManager:didVisit:
 *
 *  Discussion:
 *    Invoked when the CLLocationManager determines that the device has visited
 *    a location, if visit monitoring is currently started (possibly from a
 *    prior launch).
 */
- (void)locationManager:(CLLocationManager *)manager didVisit:(CLVisit *)visit __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_8_0) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreLocation.framework/Headers/CLCircularRegion.h
/*
 *  CLCircularRegion.h
 *  CoreLocation
 *
 *  Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CLRegion.h>
#import <CoreLocation/CLLocation.h>
#import <CoreLocation/CLAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CLCircularRegion
 *
 *  Discussion:
 *    A circular geographic area.
 */
NS_CLASS_AVAILABLE(NA, 7_0)
@interface CLCircularRegion : CLRegion

/*
 *  initWithCenter:radius:identifier:
 *
 *  Discussion:
 *    Initialize a region.  center gives the coordinates of center of the region, while radius gives
 *    the distance in meters between the center and the region's boundary. identifier is a description
 *    for the region that could be displayed to the user, and ideally should be chosen by the user.
 */
- (instancetype)initWithCenter:(CLLocationCoordinate2D)center
                            radius:(CLLocationDistance)radius
                        identifier:(NSString *)identifier;

/*
 *  center
 *
 *  Discussion:
 *    Returns the coordinate of the center of the region.
 */
@property (readonly, nonatomic) CLLocationCoordinate2D center;

/*
 *  radius
 *
 *  Discussion:
 *    Returns the radius of the region.
 */
@property (readonly, nonatomic) CLLocationDistance radius;

/*
 *  containsCoordinate:
 *
 *  Discussion:
 *    Returns YES if the coordinate lies inside the region, and NO otherwise.
 */
- (BOOL)containsCoordinate:(CLLocationCoordinate2D)coordinate;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreLocation.framework/Headers/CLPlacemark.h
/*
 *  CLPlacemark.h
 *  CoreLocation
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 */

#if TARGET_OS_IPHONE

#import <Foundation/Foundation.h>
#import <CoreLocation/CLAvailability.h>

NS_ASSUME_NONNULL_BEGIN

@class CLLocation;
@class CLRegion;
@class CLPlacemarkInternal;

/*
 *  CLPlacemark
 *  
 *  Discussion:
 *    Represents placemark data for a geographic location. Placemark data can be
 *    information such as the country, state, city, and street address.
 */

NS_CLASS_AVAILABLE(TBD,5_0)
@interface CLPlacemark : NSObject <NSCopying, NSSecureCoding>
{
@private
    CLPlacemarkInternal *_internal;
}

/*
 * initWithPlacemark:
 *
 * Discussion:
 *   Initialize a newly allocated placemark from another placemark, copying its data.
 */
- (instancetype)initWithPlacemark:(CLPlacemark *) placemark;

/*
 *  location
 *  
 *  Discussion:
 *    Returns the geographic location associated with the placemark.
 */
@property (nonatomic, readonly, copy, nullable) CLLocation *location;

/*
 *  region
 *  
 *  Discussion:
 *    Returns the geographic region associated with the placemark.
 */
@property (nonatomic, readonly, copy, nullable) CLRegion *region;

/*
 *  timeZone
 *
 *  Discussion:
 *		Returns the time zone associated with the placemark.
 */
@property (nonatomic, readonly, copy, nullable) NSTimeZone *timeZone NS_AVAILABLE(10_11,9_0);

/*
 *  addressDictionary
 *  
 *  Discussion:
 *    This dictionary can be formatted as an address using ABCreateStringWithAddressDictionary,
 *    defined in the AddressBookUI framework.
 */
@property (nonatomic, readonly, copy, nullable) NSDictionary *addressDictionary;

// address dictionary properties
@property (nonatomic, readonly, copy, nullable) NSString *name; // eg. Apple Inc.
@property (nonatomic, readonly, copy, nullable) NSString *thoroughfare; // street name, eg. Infinite Loop
@property (nonatomic, readonly, copy, nullable) NSString *subThoroughfare; // eg. 1
@property (nonatomic, readonly, copy, nullable) NSString *locality; // city, eg. Cupertino
@property (nonatomic, readonly, copy, nullable) NSString *subLocality; // neighborhood, common name, eg. Mission District
@property (nonatomic, readonly, copy, nullable) NSString *administrativeArea; // state, eg. CA
@property (nonatomic, readonly, copy, nullable) NSString *subAdministrativeArea; // county, eg. Santa Clara
@property (nonatomic, readonly, copy, nullable) NSString *postalCode; // zip code, eg. 95014
@property (nonatomic, readonly, copy, nullable) NSString *ISOcountryCode; // eg. US
@property (nonatomic, readonly, copy, nullable) NSString *country; // eg. United States
@property (nonatomic, readonly, copy, nullable) NSString *inlandWater; // eg. Lake Tahoe
@property (nonatomic, readonly, copy, nullable) NSString *ocean; // eg. Pacific Ocean
@property (nonatomic, readonly, copy, nullable) NSArray<NSString *> *areasOfInterest; // eg. Golden Gate Park
@end

#endif //TARGET_OS_IPHONE

NS_ASSUME_NONNULL_END
