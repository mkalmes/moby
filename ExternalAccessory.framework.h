// ==========  ExternalAccessory.framework/Headers/EAWiFiUnconfiguredAccessory.h
//
//  EAWiFiUnconfiguredAccessory.h
//  ExternalAccessory
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @options EAWiFiUnconfiguredAccessoryProperties
 *
 *  @discussion Represents the properties of an EAWiFiUnconfiguredAccessory.
 *
 *  @constant EAWiFiUnconfiguredAccessoryPropertySupportsAirPlay  Option set if the accessory is advertising that it supports AirPlay.
 *  @constant EAWiFiUnconfiguredAccessoryPropertySupportsAirPrint Option set if the accessory is advertising that it supports AirPrint.
 *  @constant EAWiFiUnconfiguredAccessoryPropertySupportsHomeKit  Option set if the accessory is advertising that it supports HomeKit.
 *
 */
typedef NS_OPTIONS(NSUInteger, EAWiFiUnconfiguredAccessoryProperties)
{
    EAWiFiUnconfiguredAccessoryPropertySupportsAirPlay  = (1 << 0),
    EAWiFiUnconfiguredAccessoryPropertySupportsAirPrint = (1 << 1),
    EAWiFiUnconfiguredAccessoryPropertySupportsHomeKit  = (1 << 2)
};

/*!
 * @brief Object representing an unconfigured MFi Wireless Accessory Configuration (WAC) accessory.
 *
 * @discussion This class models an unconfigured MFi Wireless Accessory Configuration accessory
 *             discovered via a EAWiFiUnconfiguredAccessoryBrowser search.
 *
 */
NS_CLASS_AVAILABLE(NA, 8_0)
@interface EAWiFiUnconfiguredAccessory : NSObject

/*!
 * @property name
 *
 * @discussion The name of the accessory.
 *
 */
@property(copy, nonatomic, readonly) NSString *name;

/*!
 * @property manufacturer
 *
 * @discussion The name of the accessory's manufacturer.
 *
 */
@property(copy, nonatomic, readonly) NSString *manufacturer;

/*!
 * @property model
 *
 * @discussion The model name of accessory.
 *
 */
@property(copy, nonatomic, readonly) NSString *model;

/*!
 * @property ssid
 *
 * @discussion The Wi-Fi SSID of the accessory.
 *
 */
@property(copy, nonatomic, readonly) NSString *ssid;

/*!
 * @property macAddress
 *
 * @discussion The primary MAC address of the accessory.
 *
 */
@property(copy, nonatomic, readonly) NSString *macAddress;

/*!
 * @property properties
 *
 * @discussion The properties the accessory supports.
 *
 */
@property(readonly, nonatomic, readonly) EAWiFiUnconfiguredAccessoryProperties properties;

@end

NS_ASSUME_NONNULL_END
// ==========  ExternalAccessory.framework/Headers/ExternalAccessory.h
//
//  ExternalAccessory.h
//  ExternalAccessory
//
//  Copyright (c) 2008-2015 Apple Inc. All rights reserved.
//

#import <ExternalAccessory/ExternalAccessoryDefines.h>
#import <ExternalAccessory/EAAccessoryManager.h>
#import <ExternalAccessory/EAAccessory.h>
#import <ExternalAccessory/EASession.h>
#import <ExternalAccessory/EAWiFiUnconfiguredAccessoryBrowser.h>
#import <ExternalAccessory/EAWiFiUnconfiguredAccessory.h>
// ==========  ExternalAccessory.framework/Headers/EASession.h
//
//  EASession.h
//  ExternalAccessory
//
//  Copyright (c) 2008-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class EAAccessory;

EA_EXTERN_CLASS_AVAILABLE(3_0) @interface EASession : NSObject {
@private
    EAAccessory *_accessory;
    uint32_t _sessionID;
    NSString *_protocolString;
    NSInputStream *_inputStream;
    NSOutputStream *_outputStream;
    BOOL _openCompleted;
}

- (instancetype)initWithAccessory:(EAAccessory *)accessory forProtocol:(NSString *)protocolString __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@property (nonatomic, readonly) EAAccessory *accessory __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@property (nonatomic, readonly) NSString *protocolString __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@property (nonatomic, readonly, nullable) NSInputStream *inputStream __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@property (nonatomic, readonly, nullable) NSOutputStream *outputStream __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@end

NS_ASSUME_NONNULL_END
// ==========  ExternalAccessory.framework/Headers/EAAccessoryManager.h
//
//  EAAccessoryManager.h
//  ExternalAccessory
//
//  Copyright (c) 2008-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, EABluetoothAccessoryPickerErrorCode) {
    EABluetoothAccessoryPickerAlreadyConnected,
	EABluetoothAccessoryPickerResultNotFound,
	EABluetoothAccessoryPickerResultCancelled,
	EABluetoothAccessoryPickerResultFailed
};

EA_EXTERN NSString *const EABluetoothAccessoryPickerErrorDomain;

typedef void(^EABluetoothAccessoryPickerCompletion)(NSError * __nullable error);

// EAAccessoryManager Notifications
EA_EXTERN NSString *const EAAccessoryDidConnectNotification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
EA_EXTERN NSString *const EAAccessoryDidDisconnectNotification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
// Keys in the EAAccessoryDidConnectNotification/EAAccessoryDidDisconnectNotification userInfo
EA_EXTERN NSString *const EAAccessoryKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // EAAccessory
EA_EXTERN NSString *const EAAccessorySelectedKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0); // EAAccessory

@class EAAccessory;

EA_EXTERN_CLASS_AVAILABLE(3_0) @interface EAAccessoryManager : NSObject {
@private
    NSMutableArray *_connectedAccessories;
}

+ (EAAccessoryManager *)sharedAccessoryManager __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

- (void)showBluetoothAccessoryPickerWithNameFilter:(nullable NSPredicate *)predicate completion:(nullable EABluetoothAccessoryPickerCompletion)completion __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

- (void)registerForLocalNotifications __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)unregisterForLocalNotifications __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@property (nonatomic, readonly) NSArray<EAAccessory *> *connectedAccessories __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@end

NS_ASSUME_NONNULL_END
// ==========  ExternalAccessory.framework/Headers/ExternalAccessoryDefines.h
//
//  ExternalAccessoryDefines.h
//  ExternalAccessory
//
//  Copyright (c) 2008-2015 Apple Inc. All rights reserved.
//

#ifdef __cplusplus
#define EA_EXTERN	 extern "C" __attribute__((visibility ("default")))
#else // #ifdef __cplusplus
#define EA_EXTERN	 extern __attribute__((visibility ("default")))
#endif // #ifdef __cplusplus

#define EA_EXTERN_CLASS __attribute__((visibility("default")))
#define EA_EXTERN_CLASS_AVAILABLE(version) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(NA, version)
// ==========  ExternalAccessory.framework/Headers/EAWiFiUnconfiguredAccessoryBrowser.h
//
//  EAWiFiUnconfiguredAccessoryBrowser.h
//  ExternalAccessory
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

/*!
 * @brief Forward declaration of the EAWiFiUnconfiguredAccessory class.
 *
 */
@class EAWiFiUnconfiguredAccessory;

/*!
 * @brief Forward declaration of the UIViewController class.
 *
 */
@class UIViewController;

/*!
 * @brief Forward declaration of the EAWiFiUnconfiguredAccessoryBrowserDelegate protocol.
 *
 */
@protocol EAWiFiUnconfiguredAccessoryBrowserDelegate;

/*!
 *  @enum EAWiFiUnconfiguredAccessoryBrowserState
 *
 *  @discussion Represents the current state of a EAWiFiUnconfiguredAccessoryBrowser.
 *
 *  @constant EAWiFiUnconfiguredAccessoryBrowserStateWiFiUnavailable  Wi-Fi is unavailable due to the user placing the device in Airplane Mode or explicitly turning Wi-Fi off.
 *  @constant EAWiFiUnconfiguredAccessoryBrowserStateStopped          The browser is not actively searching for unconfigured accessories.
 *  @constant EAWiFiUnconfiguredAccessoryBrowserStateSearching        The browser is actively searching for unconfigured accessory.
 *  @constant EAWiFiUnconfiguredAccessoryBrowserStateConfiguring      The browser is actively configuring an accessory.
 *
 */
typedef NS_ENUM(NSInteger, EAWiFiUnconfiguredAccessoryBrowserState)
{
    EAWiFiUnconfiguredAccessoryBrowserStateWiFiUnavailable = 0,
    EAWiFiUnconfiguredAccessoryBrowserStateStopped,
    EAWiFiUnconfiguredAccessoryBrowserStateSearching,
    EAWiFiUnconfiguredAccessoryBrowserStateConfiguring,
};

/*!
 *  @enum EAWiFiUnconfiguredAccessoryConfigurationStatus
 *
 *  @discussion Represents the state of an EAWiFiUnconfiguredAccessory configuration process.
 *
 *  @constant EAWiFiUnconfiguredAccessoryConfigurationStatusSuccess                     The configuration of the accessory succeeded.
 *  @constant EAWiFiUnconfiguredAccessoryConfigurationStatusUserCancelledConfiguration  The user cancelled the configuration process.
 *  @constant EAWiFiUnconfiguredAccessoryConfigurationStatusFailed                      The configuration failed.
 *
 */
typedef NS_ENUM(NSInteger, EAWiFiUnconfiguredAccessoryConfigurationStatus)
{
    EAWiFiUnconfiguredAccessoryConfigurationStatusSuccess = 0,
    EAWiFiUnconfiguredAccessoryConfigurationStatusUserCancelledConfiguration,
    EAWiFiUnconfiguredAccessoryConfigurationStatusFailed,
};

/*!
 * @brief Interface for browsing unconfigured accessories
 *
 * @discussion This class brokers access to the MFi Wireless Accessory Configuration (WAC) process.
 *             This browser enables the application to scan for unconfigured accessories,
 *             connect them to the user's Wi-Fi infrastructure and configure attributes of
 *             the accessory.
 *
 */

NS_CLASS_AVAILABLE(NA, 8_0)
NS_ASSUME_NONNULL_BEGIN

@interface EAWiFiUnconfiguredAccessoryBrowser : NSObject

/*!
 *  @property delegate
 *
 *  @discussion The delegate object that will receive the browser events.
 *
 */
@property (weak, nonatomic, nullable) id<EAWiFiUnconfiguredAccessoryBrowserDelegate> delegate;

/*!
 * @property unconfiguredAccessories
 *
 * @discussion The set of discovered unconfigured accessories described by EAWiFiUnconfiguredAccessory objects.
 *             This snapshot will only include objects matching the filter predicate defined when starting the search.
 *
 */
@property (readonly, copy, atomic) NSSet<EAWiFiUnconfiguredAccessory *> *unconfiguredAccessories;

/*!
 * @brief Designated initializer.
 *
 * @discussion Initializes an instance of the EAWiFiUnconfiguredAccessoryBrowser class
 *             which can be further configured based on the application's interests.
 *
 * @param delegate The delegate that will receive the EAWiFiUnconfiguredAccessoryBrowserDelegate events.
 * @param queue    The dispatch queue the delegate would like to receive events on. If nil the events will be on the main queue.
 *
 * @return Instance object
 *
 */
- (instancetype)initWithDelegate:(nullable id<EAWiFiUnconfiguredAccessoryBrowserDelegate>)delegate queue:(nullable dispatch_queue_t)queue NS_DESIGNATED_INITIALIZER NS_AVAILABLE(NA, 8_0);

/*!
 * @brief Start the search for unconfigured accessories
 *
 * @discussion Starts a Wi-Fi scan for unconfigured accessories. This power and resource intensive process and must
 *             only be used when actively searching for accessories. Scans should be stopped immediately when the
 *             desired accessories have been located.
 *
 * @param predicate The desired filter for unconfigured accessory results conforming to the EAWiFiUnconfiguredAccessory protocol.
 *
 */
- (void)startSearchingForUnconfiguredAccessoriesMatchingPredicate:(nullable NSPredicate *)predicate NS_AVAILABLE(NA, 8_0);

/*!
 * @brief Stop the search for unconfigured MFi Wireless Accessory Configuration accessories
 *
 */
- (void)stopSearchingForUnconfiguredAccessories NS_AVAILABLE(NA, 8_0);

/*!
 * @brief Begin the configuration process for the chosen accessory
 *
 * @discussion Stop the search for unconfigured accessories and begins the configuration process of the specified EAWiFiUnconfiguredAccessory.
 *             The user is guided through the configuration process via Apple UI. This process can take up to a few minutes to complete.
 *             The host application delegate will receive the didFinishConfiguringAccessory callback with an error that should be
 *             checked upon completion.
 *
 * @param accessory      The accessory the application wishes to configure
 * @param viewController The UIViewController that will host the Apple guided setup UI in the host application.
 *
 */
- (void)configureAccessory:(EAWiFiUnconfiguredAccessory *)accessory withConfigurationUIOnViewController:(UIViewController *)viewController NS_AVAILABLE(NA, 8_0);

@end


#pragma mark - EAWiFiUnconfiguredAccessoryBrowserDelegate Methods

/*!
 *  @protocol EAWiFiUnconfiguredAccessoryBrowserDelegate
 *
 *  @discussion The delegate of a EAWiFiUnconfiguredAccessoryBrowser object must adopt the
 *              EAWiFiUnconfiguredAccessoryBrowserDelegate protocol. The required
 *              callbacks keep the delegate informed of the state of the search and configuration processes.
 *
 */
@protocol EAWiFiUnconfiguredAccessoryBrowserDelegate <NSObject>

/*!
 *  @method accessoryBrowser:didUpdateState:
 *
 *  @discussion Invoked whenever the EAWiFiUnconfiguredAccessoryBrowser's state has changed.
 *
 *  @param browser The EAWiFiUnconfiguredAccessoryBrowser instance generating the event.
 *  @param state   The current state of the EAWiFiUnconfiguredAccessoryBrowser.
 *
 */
- (void)accessoryBrowser:(EAWiFiUnconfiguredAccessoryBrowser *)browser didUpdateState:(EAWiFiUnconfiguredAccessoryBrowserState)state NS_AVAILABLE(NA, 8_0);

/*!
 *  @method accessoryBrowser:didFindUnconfiguredAccessories:
 *
 *  @discussion Invoked whenever the EAWiFiUnconfiguredAccessoryBrowser has found new unconfigured accessories that match
 *              the filter predicate defined when starting the search.
 *
 *  @param browser     The EAWiFiUnconfiguredAccessoryBrowser instance generating the event.
 *  @param accessories The set of EAWiFiUnconfiguredAccessory objects that have been found since the last update.
 *
 */
- (void)accessoryBrowser:(EAWiFiUnconfiguredAccessoryBrowser *)browser didFindUnconfiguredAccessories:(NSSet<EAWiFiUnconfiguredAccessory *> *)accessories NS_AVAILABLE(NA, 8_0);

/*!
 *  @method accessoryBrowser:didRemoveUnconfiguredAccessories:
 *
 *  @discussion Invoked whenever the EAWiFiUnconfiguredAccessoryBrowser has removed unconfigured accessories from the scan results
 *              that match the filter predicate defined when starting the search.
 *
 *  @param browser     The EAWiFiUnconfiguredAccessoryBrowser instance generating the event.
 *  @param accessories The set of EAWiFiUnconfiguredAccessory objects that have been removed from the scan results since the last update.
 *
 */
- (void)accessoryBrowser:(EAWiFiUnconfiguredAccessoryBrowser *)browser didRemoveUnconfiguredAccessories:(NSSet<EAWiFiUnconfiguredAccessory *> *)accessories NS_AVAILABLE(NA, 8_0);

/*!
 *  @method accessoryBrowser:didFinishConfiguringAccessory:withError:
 *
 *  @discussion Invoked whenever the EAWiFiUnconfiguredAccessoryBrowser has completed configuring the selected EAWiFiUnconfiguredAccessory.
 *
 *  @param browser   The EAWiFiUnconfiguredAccessoryBrowser instance generating the event.
 *  @param accessory The EAWiFiUnconfiguredAccessory whose configuration process has completed.
 *  @param status    The status of the configuration process that has completed.
 *
 */
- (void)accessoryBrowser:(EAWiFiUnconfiguredAccessoryBrowser *)browser didFinishConfiguringAccessory:(EAWiFiUnconfiguredAccessory *)accessory withStatus:(EAWiFiUnconfiguredAccessoryConfigurationStatus)status NS_AVAILABLE(NA, 8_0);

@end

NS_ASSUME_NONNULL_END
// ==========  ExternalAccessory.framework/Headers/EAAccessory.h
//
//  EAAccessory.h
//  ExternalAccessory
//
//  NOTE: Data to the external accessory is automatically wrapped into an iAP
//        packet after bring sent to the output stream. The iAP wrapper is
//        automatically stripped from incoming packets before being sent to
//        the EAAccessory input stream.
//
//        Further information related to these wrapper can be found in the
//        iAP specifications.
//
//  Copyright (c) 2008-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class EAAccessoryInternal;
@protocol EAAccessoryDelegate;

enum {
    EAConnectionIDNone = 0,
};

EA_EXTERN_CLASS_AVAILABLE(3_0) @interface EAAccessory : NSObject {
@private
    EAAccessoryInternal *_internal;
}

@property(nonatomic, readonly, getter=isConnected) BOOL connected __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@property(nonatomic, readonly) NSUInteger connectionID __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@property(nonatomic, readonly) NSString *manufacturer __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@property(nonatomic, readonly) NSString *name __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@property(nonatomic, readonly) NSString *modelNumber __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@property(nonatomic, readonly) NSString *serialNumber __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@property(nonatomic, readonly) NSString *firmwareRevision __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@property(nonatomic, readonly) NSString *hardwareRevision __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@property(nonatomic, readonly) NSString *dockType __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_9_0);

// array of strings representing the protocols supported by the accessory
@property(nonatomic, readonly) NSArray<NSString *> *protocolStrings __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@property(nonatomic, assign, nullable) id<EAAccessoryDelegate> delegate __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@end

@protocol EAAccessoryDelegate <NSObject>
@optional
- (void)accessoryDidDisconnect:(EAAccessory *)accessory __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@end

NS_ASSUME_NONNULL_END
