// ==========  CoreBluetooth.framework/Headers/CBManager.h
/*
 *	@file CBManager.h
 *	@framework CoreBluetooth
 *
 *  @discussion Entry point to the central role.
 *
 *	@copyright 2016 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>
#import <Foundation/Foundation.h>

NS_CLASS_AVAILABLE(10_13, 10_0)
CB_EXTERN_CLASS @interface CBManager : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 *  @enum CBManagerState
 *
 *  @discussion Represents the current state of a CBManager.
 *
 *  @constant CBManagerStateUnknown       State unknown, update imminent.
 *  @constant CBManagerStateResetting     The connection with the system service was momentarily lost, update imminent.
 *  @constant CBManagerStateUnsupported   The platform doesn't support the Bluetooth Low Energy Central/Client role.
 *  @constant CBManagerStateUnauthorized  The application is not authorized to use the Bluetooth Low Energy role.
 *  @constant CBManagerStatePoweredOff    Bluetooth is currently powered off.
 *  @constant CBManagerStatePoweredOn     Bluetooth is currently powered on and available to use.
 *
 */
typedef NS_ENUM(NSInteger, CBManagerState) {
	CBManagerStateUnknown = 0,
	CBManagerStateResetting,
	CBManagerStateUnsupported,
	CBManagerStateUnauthorized,
	CBManagerStatePoweredOff,
	CBManagerStatePoweredOn,
} NS_ENUM_AVAILABLE(10_13, 10_0);

/*!
 *  @property state
 *
 *  @discussion The current state of the manager, initially set to <code>CBManagerStateUnknown</code>.
 *				Updates are provided by required delegate method {@link managerDidUpdateState:}.
 *
 */
@property(nonatomic, assign, readonly) CBManagerState state;

@end
// ==========  CoreBluetooth.framework/Headers/CBPeer.h
/*
 *	@file CBPeer.h
 *	@framework CoreBluetooth
 *
 *	@copyright 2014 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_13, 8_0)
CB_EXTERN_CLASS @interface CBPeer : NSObject <NSCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 *  @property identifier
 *
 *  @discussion The unique, persistent identifier associated with the peer.
 */
@property(readonly, nonatomic) NSUUID *identifier NS_AVAILABLE(10_13, 7_0);

@end

NS_ASSUME_NONNULL_END
// ==========  CoreBluetooth.framework/Headers/CoreBluetooth.h
/*!
 *  @header
 *	@file CoreBluetooth.h
 *	@framework CoreBluetooth
 *
 *  @discussion Bluetooth Low Energy framework
 *
 *	@copyright 2011 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#define _CORE_BLUETOOTH_H_
#endif

#import <CoreBluetooth/CBCentralManager.h>
#import <CoreBluetooth/CBPeripheralManager.h>

#import <CoreBluetooth/CBPeripheral.h>
#import <CoreBluetooth/CBCentral.h>

#import <CoreBluetooth/CBService.h>
#import <CoreBluetooth/CBCharacteristic.h>
#import <CoreBluetooth/CBDescriptor.h>

#import <CoreBluetooth/CBError.h>
#import <CoreBluetooth/CBUUID.h>
#import <CoreBluetooth/CBAdvertisementData.h>
#import <CoreBluetooth/CBATTRequest.h>
// ==========  CoreBluetooth.framework/Headers/CBDefines.h
/*
 *	CBDefines.h
 *	CoreBluetooth
 *
 *	Copyright 2011 Apple, Inc. All rights reserved.
 */

#ifndef CB_EXTERN
#ifdef __cplusplus
#define CB_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define CB_EXTERN extern __attribute__((visibility ("default")))
#endif
#endif

#define CB_EXTERN_CLASS __attribute__((visibility("default")))
// ==========  CoreBluetooth.framework/Headers/CBUUID.h
/*
 *	@file CBUUID.h
 *	@framework CoreBluetooth
 *
 *  @discussion The CBUUID class represents bluetooth LE UUIDs. It automatically handles
 *     transformations of 16 and 32 bit UUIDs into 128 bit UUIDs.
 *
 *	@copyright 2011 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @const CBUUIDCharacteristicExtendedPropertiesString
 *  @discussion The string representation of the UUID for the extended properties descriptor.
 *				The corresponding value for this descriptor is an <code>NSNumber</code> object.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicExtendedPropertiesString;
/*!
 *  @const CBUUIDCharacteristicUserDescriptionString
 *  @discussion The string representation of the UUID for the user description descriptor.
 *				The corresponding value for this descriptor is an <code>NSString</code> object.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicUserDescriptionString;
/*!
 *  @const CBUUIDClientCharacteristicConfigurationString
 *  @discussion The string representation of the UUID for the client configuration descriptor.
 *				The corresponding value for this descriptor is an <code>NSNumber</code> object.
 */
CB_EXTERN NSString * const CBUUIDClientCharacteristicConfigurationString;
/*!
 *  @const CBUUIDServerCharacteristicConfigurationString
 *  @discussion The string representation of the UUID for the server configuration descriptor.
 *				The corresponding value for this descriptor is an <code>NSNumber</code> object.
 */
CB_EXTERN NSString * const CBUUIDServerCharacteristicConfigurationString;
/*!
 *  @const CBUUIDCharacteristicFormatString
 *  @discussion The string representation of the UUID for the presentation format descriptor.
 *				The corresponding value for this descriptor is an <code>NSData</code> object.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicFormatString;
/*!
 *  @const CBUUIDCharacteristicAggregateFormatString
 *  @discussion The string representation of the UUID for the aggregate descriptor.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicAggregateFormatString;
/*!
 *  @const CBUUIDCharacteristicValidRangeString
 *  @discussion Data representing the valid min/max values accepted for a characteristic.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicValidRangeString;

/*!
 *  @const CBUUIDL2CAPPSMCharacteristicString
 *  @discussion The PSM (a little endian uint16_t) of an L2CAP Channel associated with the GATT service
 *				containing this characteristic.  Servers can publish this characteristic with the UUID
 *				ABDD3056-28FA-441D-A470-55A75A52553A
 */
CB_EXTERN NSString * const CBUUIDL2CAPPSMCharacteristicString NS_AVAILABLE(10_13, 11_0);

/*!
 * @class CBUUID
 *
 * @discussion
 *      A 16-bit, 32-bit, or 128-bit Bluetooth UUID.
 *      16-bit and 32-bit UUIDs are implicitly pre-filled with the Bluetooth Base UUID.
 *
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBUUID : NSObject <NSCopying>

/*!
 * @property data
 *
 *  @discussion
 *      The UUID as NSData.
 *
 */
@property(nonatomic, readonly) NSData *data;

/*!
 * @property UUIDString
 *
 *  @discussion
 *      The UUID as NSString.
 *
 */
@property(nonatomic, readonly) NSString *UUIDString NS_AVAILABLE(10_10, 7_1);

/*!
 * @method UUIDWithString:
 *
 *  @discussion
 *      Creates a CBUUID with a 16-bit, 32-bit, or 128-bit UUID string representation.
 *      The expected format for 128-bit UUIDs is a string punctuated by hyphens, for example 68753A44-4D6F-1226-9C60-0050E4C00067.
 *
 */
+ (CBUUID *)UUIDWithString:(NSString *)theString;

/*!
 * @method UUIDWithData:
 *
 *  @discussion
 *      Creates a CBUUID with a 16-bit, 32-bit, or 128-bit UUID data container.
 *
 */
+ (CBUUID *)UUIDWithData:(NSData *)theData;

/*!
 * @method UUIDWithCFUUID:
 *
 *  @discussion
 *      Creates a CBUUID with a CFUUIDRef.
 *
 */
+ (CBUUID *)UUIDWithCFUUID:(CFUUIDRef)theUUID NS_DEPRECATED(10_7, 10_13, 5_0, 9_0);

/*!
 * @method UUIDWithNSUUID:
 *
 *  @discussion
 *      Creates a CBUUID with an NSUUID.
 *
 */
+ (CBUUID *)UUIDWithNSUUID:(NSUUID *)theUUID NS_AVAILABLE(10_9, 7_0);

@end

NS_ASSUME_NONNULL_END
// ==========  CoreBluetooth.framework/Headers/CBCentralManagerConstants.h
/*
 *	@file CBCentralManagerConstants.h
 *	@framework CoreBluetooth
 *
 *	@copyright 2013 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @const  CBCentralManagerOptionShowPowerAlertKey
 *
 *  @discussion An NSNumber (Boolean) indicating that the system should, if Bluetooth is powered off when <code>CBCentralManager</code> is instantiated, display
 *				a warning dialog to the user.
 *
 *  @see		initWithDelegate:queue:options:
 *
 */
CB_EXTERN NSString * const CBCentralManagerOptionShowPowerAlertKey NS_AVAILABLE(10_9, 7_0);

/*!
 *  @const  CBCentralManagerOptionRestoreIdentifierKey
 *
 *  @discussion An NSString containing a unique identifier (UID) for the <code>CBCentralManager</code> that is being instantiated. This UID is used
 *				by the system to identify a specific <code>CBCentralManager</code> instance for restoration and, therefore, must remain the same for
 *				subsequent application executions in order for the manager to be restored.
 *
 *  @see		initWithDelegate:queue:options:
 *  @seealso	centralManager:willRestoreState:
 *
 */
CB_EXTERN NSString * const CBCentralManagerOptionRestoreIdentifierKey NS_AVAILABLE(10_13, 7_0);

/*!
 *  @const CBCentralManagerScanOptionAllowDuplicatesKey
 *
 *  @discussion An NSNumber (Boolean) indicating that the scan should run without duplicate filtering. By default, multiple discoveries of the
 *              same peripheral are coalesced into a single discovery event. Specifying this option will cause a discovery event to be generated
 *				every time the peripheral is seen, which may be many times per second. This can be useful in specific situations, such as making
 *				a connection based on a peripheral's RSSI, but may have an adverse affect on battery-life and application performance.
 *
 *  @see        scanForPeripheralsWithServices:options:
 *
 */
CB_EXTERN NSString * const CBCentralManagerScanOptionAllowDuplicatesKey;

/*!
 *  @const CBCentralManagerScanOptionSolicitedServiceUUIDsKey
 *
 *  @discussion An NSArray of <code>CBUUID</code> objects respresenting service UUIDs. Causes the scan to also look for peripherals soliciting
 *				any of the services contained in the list.
 *
 *  @see        scanForPeripheralsWithServices:options:
 *
 */
CB_EXTERN NSString * const CBCentralManagerScanOptionSolicitedServiceUUIDsKey NS_AVAILABLE(10_9, 7_0);

/*!
 *  @const CBConnectPeripheralOptionNotifyOnConnectionKey
 *
 *  @discussion An NSNumber (Boolean) indicating that the system should display a connection alert for a given peripheral, if the application is suspended
 *              when a successful connection is made.
 *              This is useful for applications that have not specified the <code>bluetooth-central</code> background mode and cannot display their
 *              own alert. If more than one application has requested notification for a given peripheral, the one that was most recently in the foreground
 *              will receive the alert.
 *
 *  @see        connectPeripheral:
 *
 */
CB_EXTERN NSString * const CBConnectPeripheralOptionNotifyOnConnectionKey NS_AVAILABLE(10_13, 6_0);

/*!
 *  @const CBConnectPeripheralOptionNotifyOnDisconnectionKey
 *
 *  @discussion An NSNumber (Boolean) indicating that the system should display a disconnection alert for a given peripheral, if the application
 *              is suspended at the time of the disconnection.
 *              This is useful for applications that have not specified the <code>bluetooth-central</code> background mode and cannot display their
 *              own alert. If more than one application has requested notification for a given peripheral, the one that was most recently in the foreground
 *              will receive the alert.
 *
 *  @see        connectPeripheral:
 *
 */
CB_EXTERN NSString * const CBConnectPeripheralOptionNotifyOnDisconnectionKey;

/*!
 *  @const CBConnectPeripheralOptionNotifyOnNotificationKey
 *
 *  @discussion An NSNumber (Boolean) indicating that the system should display an alert for all notifications received from a given peripheral, if
 *              the application is suspended at the time.
 *              This is useful for applications that have not specified the <code>bluetooth-central</code> background mode and cannot display their
 *              own alert. If more than one application has requested notification for a given peripheral, the one that was most recently in the foreground
 *              will receive the alert.
 *
 *  @see        connectPeripheral:
 *
 */
CB_EXTERN NSString * const CBConnectPeripheralOptionNotifyOnNotificationKey NS_AVAILABLE(10_13, 6_0);


/*!
 *  @const CBConnectPeripheralOptionStartDelayKey
 *
 *  @discussion An NSNumber indicating the number of seconds for the system to wait before starting a connection.
 *
 *  @see        connectPeripheral:
 *
 */
CB_EXTERN NSString * const CBConnectPeripheralOptionStartDelayKey NS_AVAILABLE(10_13, 6_0);

/*!
 *  @const  CBCentralManagerRestoredStatePeripheralsKey
 *
 *  @discussion An NSArray of <code>CBPeripheral</code> objects containing all peripherals that were connected or pending connection at the time the
 *				application was terminated by the system. When possible, all known information for each peripheral will be restored, including any discovered
 *				services, characteristics and descriptors, as well as characteristic notification states.
 *
 *  @see		centralManager:willRestoreState:
 *	@seealso	connectPeripheral:options:
 *
 */
CB_EXTERN NSString * const CBCentralManagerRestoredStatePeripheralsKey NS_AVAILABLE(10_13, 7_0);

/*!
 *  @const  CBCentralManagerRestoredStateScanServicesKey
 *
 *  @discussion An NSArray of <code>CBUUID</code> objects containing the service(s) being scanned for at the time the application was terminated by the system.
 *
 *  @see		centralManager:willRestoreState:
 *	@seealso	scanForPeripheralsWithServices:options:
 *
 */
CB_EXTERN NSString * const CBCentralManagerRestoredStateScanServicesKey NS_AVAILABLE(10_13, 7_0);

/*!
 *  @const  CBCentralManagerRestoredStateScanOptionsKey
 *
 *  @discussion An NSDictionary containing the scan options at the time the application was terminated by the system.
 *
 *  @see		centralManager:willRestoreState:
 *	@seealso	scanForPeripheralsWithServices:options:
 *
 */
CB_EXTERN NSString * const CBCentralManagerRestoredStateScanOptionsKey NS_AVAILABLE(10_13, 7_0);

NS_ASSUME_NONNULL_END
// ==========  CoreBluetooth.framework/Headers/CBCentral.h
/*
 *	@file CBCentral.h
 *	@framework CoreBluetooth
 *
 *  @discussion Representation of a remote central.
 *
 *	@copyright 2012 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBDefines.h>
#import <CoreBluetooth/CBPeer.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @class CBCentral
 *
 *  @discussion Represents a remote central.
 *
 */
NS_CLASS_AVAILABLE(10_9, 6_0)
CB_EXTERN_CLASS @interface CBCentral : CBPeer

/*!
 *  @property	maximumUpdateValueLength
 *
 *  @discussion	The maximum amount of data, in bytes, that can be received by the central in a single notification or indication.
 *
 *	@see		updateValue:forCharacteristic:onSubscribedCentrals:
 */
@property(readonly, nonatomic) NSUInteger maximumUpdateValueLength;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreBluetooth.framework/Headers/CBDescriptor.h
/*
 *	@file CBDescriptor.h
 *	@framework CoreBluetooth
 *
 *	@copyright 2011 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBAttribute.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class CBDescriptor
 *
 *  @discussion
 *      Represents a characteristic's descriptor.
 *
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBDescriptor : CBAttribute

/*!
 *  @property characteristic
 *
 *  @discussion
 *      A back-pointer to the characteristic this descriptor belongs to.
 *
 */
@property(assign, readonly, nonatomic) CBCharacteristic *characteristic;

/*!
 *  @property value
 *
 *  @discussion
 *      The value of the descriptor. The corresponding value types for the various descriptors are detailed in @link CBUUID.h @/link.
 *
 */
@property(retain, readonly, nullable) id value;

@end


/*!
 * @class CBMutableDescriptor
 *
 * @discussion
 *      Used to create a local characteristic descriptor, which can be added to the local database via <code>CBPeripheralManager</code>.
 *		Once a descriptor is published, it is cached and can no longer be changed.
 *		Descriptor types are detailed in @link CBUUID.h @/link, but only the <code>Characteristic User Description</code> and <code>Characteristic Presentation
 *		Format</code> descriptors are currently supported. The <code>Characteristic Extended Properties</code> and <code>Client Characteristic 
 *		Configuration</code> descriptors will be created automatically upon publication of the parent service, depending on the properties of the characteristic itself.
 */
NS_CLASS_AVAILABLE(10_9, 6_0)
CB_EXTERN_CLASS @interface CBMutableDescriptor : CBDescriptor

/*!
 *  @method initWithType:value:
 *
 *  @param UUID		The Bluetooth UUID of the descriptor.
 *  @param value	The value of the descriptor.
 *
 *  @discussion 	Returns a decriptor, initialized with a service type and value. The <i>value</i> is required and cannot be updated dynamically
 *					once the parent service has been published.
 *
 */
- (instancetype)initWithType:(CBUUID *)UUID value:(nullable id)value NS_DESIGNATED_INITIALIZER __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreBluetooth.framework/Headers/CBService.h
/*
 *	@file CBService.h
 *	@framework CoreBluetooth
 *
 *  @discussion A Bluetooth LE service representation. A LE Service provides a number of
 *		characteristics and may also reference other services.
 *
 *	@copyright 2011 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBAttribute.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class CBService
 *
 * @discussion
 *      Represents a peripheral's service or a service's included service.
 *
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBService : CBAttribute

/*!
 * @property peripheral
 *
 * @discussion
 *      A back-pointer to the peripheral this service belongs to.
 *
 */
@property(assign, readonly, nonatomic) CBPeripheral *peripheral;

/*!
 * @property isPrimary
 *
 * @discussion
 *      The type of the service (primary or secondary).
 *
 */
@property(readonly, nonatomic) BOOL isPrimary;

/*!
 * @property includedServices
 *
 * @discussion
 *      A list of included CBServices that have so far been discovered in this service.
 *
 */
@property(retain, readonly, nullable) NSArray<CBService *> *includedServices;

/*!
 * @property characteristics
 *
 * @discussion
 *      A list of CBCharacteristics that have so far been discovered in this service.
 *
 */
@property(retain, readonly, nullable) NSArray<CBCharacteristic *> *characteristics;

@end


/*!
 * @class CBMutableService
 *
 * @discussion
 *      Used to create a local service or included service, which can be added to the local database via <code>CBPeripheralManager</code>.
 *		Once a service is published, it is cached and can no longer be changed. This class adds write access to all properties in the
 *		@link CBService @/link class.
 *
 */
NS_CLASS_AVAILABLE(10_9, 6_0)
CB_EXTERN_CLASS @interface CBMutableService : CBService

@property(retain, readwrite, nullable) NSArray<CBService *> *includedServices;
@property(retain, readwrite, nullable) NSArray<CBCharacteristic *> *characteristics;

/*!
 *  @method initWithType:primary:
 *
 *  @param UUID			The Bluetooth UUID of the service.
 *  @param isPrimary	The type of the service (primary or secondary).
 *
 *  @discussion			Returns a service, initialized with a service type and UUID.
 *
 */
- (instancetype)initWithType:(CBUUID *)UUID primary:(BOOL)isPrimary NS_DESIGNATED_INITIALIZER __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreBluetooth.framework/Headers/CBPeripheralManagerConstants.h
/*
 *	@file CBPeripheralManagerConstants.h
 *	@framework CoreBluetooth
 *
 *	@copyright 2013 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @const  CBPeripheralManagerOptionShowPowerAlertKey
 *
 *  @discussion An NSNumber (Boolean) indicating that the system should, if Bluetooth is powered off when <code>CBPeripheralManager</code> is instantiated, display
 *				a warning dialog to the user.
 *
 *  @see		initWithDelegate:queue:options:
 *
 */
CB_EXTERN NSString * const CBPeripheralManagerOptionShowPowerAlertKey NS_AVAILABLE(10_9, 7_0);

/*!
 *  @const  CBPeripheralManagerOptionRestoreIdentifierKey
 *
 *  @discussion An NSString containing a unique identifier (UID) for the <code>CBPeripheralManager</code> that is being instantiated. This UID is used
 *				by the system to identify a specific <code>CBPeripheralManager</code> instance for restoration and, therefore, must remain the same for
 *				subsequent application executions in order for the manager to be restored.
 *
 *  @see		initWithDelegate:queue:options:
 *  @seealso	centralManager:willRestoreState:
 *
 */
CB_EXTERN NSString * const CBPeripheralManagerOptionRestoreIdentifierKey NS_AVAILABLE(10_9, 7_0);

/*!
 *  @const  CBPeripheralManagerRestoredStateServicesKey
 *
 *  @discussion An NSArray of <code>CBMutableService</code> objects containing all services that were published to the local database at the time the
 *				application was terminated by the system. All information for each service will be restored, including all discovered
 *				services, characteristics and descriptors, as well as characteristic notification states.
 *
 *  @see		peripheralManager:willRestoreState:
 *  @seealso	addService:
 *
 */
CB_EXTERN NSString * const CBPeripheralManagerRestoredStateServicesKey NS_AVAILABLE(10_9, 7_0);

/*!
 *  @const  CBPeripheralManagerRestoredStateAdvertisementDataKey
 *
 *  @discussion An NSDictionary containing the data being advertised at the time the application was terminated by the system.
 *
 *  @see		peripheralManager:willRestoreState:
 *  @seealso	startAdvertising:
 *
 */
CB_EXTERN NSString * const CBPeripheralManagerRestoredStateAdvertisementDataKey NS_AVAILABLE(10_9, 7_0);

NS_ASSUME_NONNULL_END
// ==========  CoreBluetooth.framework/Headers/CBAdvertisementData.h
/*
 *	@file CBAdvertisementData.h
 *	@framework CoreBluetooth
 *
 *	@copyright 2012 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @constant CBAdvertisementDataLocalNameKey
 *
 *  @discussion A <code>NSString</code> containing the local name of a peripheral.
 *
 */
CB_EXTERN NSString * const CBAdvertisementDataLocalNameKey;


/*!
 *  @constant CBAdvertisementDataTxPowerLevelKey
 *
 *  @discussion A <code>NSNumber</code> containing the transmit power of a peripheral.
 *
 */
CB_EXTERN NSString * const CBAdvertisementDataTxPowerLevelKey;


/*!
 *  @constant CBAdvertisementDataServiceUUIDsKey
 *
 *  @discussion A list of one or more <code>CBUUID</code> objects, representing <code>CBService</code> UUIDs.
 *
 */
CB_EXTERN NSString * const CBAdvertisementDataServiceUUIDsKey;


/*!
 *  @constant CBAdvertisementDataServiceDataKey
 *
 *  @discussion A dictionary containing service-specific advertisement data. Keys are <code>CBUUID</code> objects, representing
 *              <code>CBService</code> UUIDs. Values are <code>NSData</code> objects.
 *
 */
CB_EXTERN NSString * const CBAdvertisementDataServiceDataKey;


/*!
 *  @constant CBAdvertisementDataManufacturerDataKey
 *
 *  @discussion A <code>NSData</code> object containing the manufacturer data of a peripheral.
 *
 */
CB_EXTERN NSString * const CBAdvertisementDataManufacturerDataKey;


/*!
 *  @constant CBAdvertisementDataOverflowServiceUUIDsKey
 *
 *  @discussion A list of one or more <code>CBUUID</code> objects, representing <code>CBService</code> UUIDs that were
 *              found in the "overflow" area of the advertising data. Due to the nature of the data stored in this area,
 *              UUIDs listed here are "best effort" and may not always be accurate.
 *
 *  @see        startAdvertising:
 *
 */
CB_EXTERN NSString * const CBAdvertisementDataOverflowServiceUUIDsKey NS_AVAILABLE(10_9, 6_0);


/*!
 *  @constant CBAdvertisementDataIsConnectable
 *
 *  @discussion An NSNumber (Boolean) indicating whether or not the advertising event type was connectable. This can be used to determine
 *				whether or not a peripheral is connectable in that instant.
 *
 */
CB_EXTERN NSString * const CBAdvertisementDataIsConnectable NS_AVAILABLE(10_9, 7_0);


/*!
 *  @constant CBAdvertisementDataSolicitedServiceUUIDsKey
 *
 *  @discussion A list of one or more <code>CBUUID</code> objects, representing <code>CBService</code> UUIDs.
 *
 */
CB_EXTERN NSString * const CBAdvertisementDataSolicitedServiceUUIDsKey NS_AVAILABLE(10_9, 7_0);

NS_ASSUME_NONNULL_END
// ==========  CoreBluetooth.framework/Headers/CBCentralManager.h
/*
 *	@file CBCentralManager.h
 *	@framework CoreBluetooth
 *
 *  @discussion Entry point to the central role.
 *
 *	@copyright 2011 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBAdvertisementData.h>
#import <CoreBluetooth/CBCentralManagerConstants.h>
#import <CoreBluetooth/CBDefines.h>
#import <CoreBluetooth/CBManager.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @enum CBCentralManagerState
 *
 *  @discussion Represents the current state of a CBCentralManager.
 *
 *  @constant CBCentralManagerStateUnknown       State unknown, update imminent.
 *  @constant CBCentralManagerStateResetting     The connection with the system service was momentarily lost, update imminent.
 *  @constant CBCentralManagerStateUnsupported   The platform doesn't support the Bluetooth Low Energy Central/Client role.
 *  @constant CBCentralManagerStateUnauthorized  The application is not authorized to use the Bluetooth Low Energy Central/Client role.
 *  @constant CBCentralManagerStatePoweredOff    Bluetooth is currently powered off.
 *  @constant CBCentralManagerStatePoweredOn     Bluetooth is currently powered on and available to use.
 *
 */
typedef NS_ENUM(NSInteger, CBCentralManagerState) {
	CBCentralManagerStateUnknown = CBManagerStateUnknown,
	CBCentralManagerStateResetting = CBManagerStateResetting,
	CBCentralManagerStateUnsupported = CBManagerStateUnsupported,
	CBCentralManagerStateUnauthorized = CBManagerStateUnauthorized,
	CBCentralManagerStatePoweredOff = CBManagerStatePoweredOff,
	CBCentralManagerStatePoweredOn = CBManagerStatePoweredOn,
} NS_DEPRECATED(10_7, 10_13, 5_0, 10_0, "Use CBManagerState instead");

@protocol CBCentralManagerDelegate;
@class CBUUID, CBPeripheral;

/*!
 *  @class CBCentralManager
 *
 *  @discussion Entry point to the central role. Commands should only be issued when its state is <code>CBCentralManagerStatePoweredOn</code>.
 *
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBCentralManager : CBManager

/*!
 *  @property delegate
 *
 *  @discussion The delegate object that will receive central events.
 *
 */
@property(nonatomic, weak, nullable) id<CBCentralManagerDelegate> delegate;

/*!
 *  @property isScanning
 *
 *  @discussion Whether or not the central is currently scanning.
 *
 */
@property(nonatomic, assign, readonly) BOOL isScanning NS_AVAILABLE(10_13, 9_0);

- (instancetype)init;

/*!
 *  @method initWithDelegate:queue:
 *
 *  @param delegate The delegate that will receive central role events.
 *  @param queue    The dispatch queue on which the events will be dispatched.
 *
 *  @discussion     The initialization call. The events of the central role will be dispatched on the provided queue.
 *                  If <i>nil</i>, the main queue will be used.
 *
 */
- (instancetype)initWithDelegate:(nullable id<CBCentralManagerDelegate>)delegate
						   queue:(nullable dispatch_queue_t)queue;

/*!
 *  @method initWithDelegate:queue:options:
 *
 *  @param delegate The delegate that will receive central role events.
 *  @param queue    The dispatch queue on which the events will be dispatched.
 *  @param options  An optional dictionary specifying options for the manager.
 *
 *  @discussion     The initialization call. The events of the central role will be dispatched on the provided queue.
 *                  If <i>nil</i>, the main queue will be used.
 *
 *	@seealso		CBCentralManagerOptionShowPowerAlertKey
 *	@seealso		CBCentralManagerOptionRestoreIdentifierKey
 *
 */
- (instancetype)initWithDelegate:(nullable id<CBCentralManagerDelegate>)delegate
						   queue:(nullable dispatch_queue_t)queue
						 options:(nullable NSDictionary<NSString *, id> *)options NS_AVAILABLE(10_9, 7_0) NS_DESIGNATED_INITIALIZER;

/*!
 *  @method retrievePeripheralsWithIdentifiers:
 *
 *  @param identifiers	A list of <code>NSUUID</code> objects.
 *
 *  @discussion			Attempts to retrieve the <code>CBPeripheral</code> object(s) with the corresponding <i>identifiers</i>.
 *
 *	@return				A list of <code>CBPeripheral</code> objects.
 *
 */
- (NSArray<CBPeripheral *> *)retrievePeripheralsWithIdentifiers:(NSArray<NSUUID *> *)identifiers NS_AVAILABLE(10_9, 7_0);

/*!
 *  @method retrieveConnectedPeripheralsWithServices
 *
 *  @discussion Retrieves all peripherals that are connected to the system and implement any of the services listed in <i>serviceUUIDs</i>.
 *				Note that this set can include peripherals which were connected by other applications, which will need to be connected locally
 *				via {@link connectPeripheral:options:} before they can be used.
 *
 *	@return		A list of <code>CBPeripheral</code> objects.
 *
 */
- (NSArray<CBPeripheral *> *)retrieveConnectedPeripheralsWithServices:(NSArray<CBUUID *> *)serviceUUIDs NS_AVAILABLE(10_9, 7_0);

/*!
 *  @method scanForPeripheralsWithServices:options:
 *
 *  @param serviceUUIDs A list of <code>CBUUID</code> objects representing the service(s) to scan for.
 *  @param options      An optional dictionary specifying options for the scan.
 *
 *  @discussion         Starts scanning for peripherals that are advertising any of the services listed in <i>serviceUUIDs</i>. Although strongly discouraged,
 *                      if <i>serviceUUIDs</i> is <i>nil</i> all discovered peripherals will be returned. If the central is already scanning with different
 *                      <i>serviceUUIDs</i> or <i>options</i>, the provided parameters will replace them.
 *                      Applications that have specified the <code>bluetooth-central</code> background mode are allowed to scan while backgrounded, with two
 *                      caveats: the scan must specify one or more service types in <i>serviceUUIDs</i>, and the <code>CBCentralManagerScanOptionAllowDuplicatesKey</code>
 *                      scan option will be ignored.
 *
 *  @see                centralManager:didDiscoverPeripheral:advertisementData:RSSI:
 *  @seealso            CBCentralManagerScanOptionAllowDuplicatesKey
 *	@seealso			CBCentralManagerScanOptionSolicitedServiceUUIDsKey
 *
 */
- (void)scanForPeripheralsWithServices:(nullable NSArray<CBUUID *> *)serviceUUIDs options:(nullable NSDictionary<NSString *, id> *)options;

/*!
 *  @method stopScan:
 *
 *  @discussion Stops scanning for peripherals.
 *
 */
- (void)stopScan;

/*!
 *  @method connectPeripheral:options:
 *
 *  @param peripheral   The <code>CBPeripheral</code> to be connected.
 *  @param options      An optional dictionary specifying connection behavior options.
 *
 *  @discussion         Initiates a connection to <i>peripheral</i>. Connection attempts never time out and, depending on the outcome, will result
 *                      in a call to either {@link centralManager:didConnectPeripheral:} or {@link centralManager:didFailToConnectPeripheral:error:}.
 *                      Pending attempts are cancelled automatically upon deallocation of <i>peripheral</i>, and explicitly via {@link cancelPeripheralConnection}.
 *
 *  @see                centralManager:didConnectPeripheral:
 *  @see                centralManager:didFailToConnectPeripheral:error:
 *  @seealso            CBConnectPeripheralOptionNotifyOnConnectionKey
 *  @seealso            CBConnectPeripheralOptionNotifyOnDisconnectionKey
 *  @seealso            CBConnectPeripheralOptionNotifyOnNotificationKey
 *
 */
- (void)connectPeripheral:(CBPeripheral *)peripheral options:(nullable NSDictionary<NSString *, id> *)options;

/*!
 *  @method cancelPeripheralConnection:
 *
 *  @param peripheral   A <code>CBPeripheral</code>.
 *
 *  @discussion         Cancels an active or pending connection to <i>peripheral</i>. Note that this is non-blocking, and any <code>CBPeripheral</code>
 *                      commands that are still pending to <i>peripheral</i> may or may not complete.
 *
 *  @see                centralManager:didDisconnectPeripheral:error:
 *
 */
- (void)cancelPeripheralConnection:(CBPeripheral *)peripheral;


@end


/*!
 *  @protocol CBCentralManagerDelegate
 *
 *  @discussion The delegate of a {@link CBCentralManager} object must adopt the <code>CBCentralManagerDelegate</code> protocol. The
 *              single required method indicates the availability of the central manager, while the optional methods allow for the discovery and
 *              connection of peripherals.
 *
 */
@protocol CBCentralManagerDelegate <NSObject>

@required

/*!
 *  @method centralManagerDidUpdateState:
 *
 *  @param central  The central manager whose state has changed.
 *
 *  @discussion     Invoked whenever the central manager's state has been updated. Commands should only be issued when the state is
 *                  <code>CBCentralManagerStatePoweredOn</code>. A state below <code>CBCentralManagerStatePoweredOn</code>
 *                  implies that scanning has stopped and any connected peripherals have been disconnected. If the state moves below
 *                  <code>CBCentralManagerStatePoweredOff</code>, all <code>CBPeripheral</code> objects obtained from this central
 *                  manager become invalid and must be retrieved or discovered again.
 *
 *  @see            state
 *
 */
- (void)centralManagerDidUpdateState:(CBCentralManager *)central;

@optional

/*!
 *  @method centralManager:willRestoreState:
 *
 *  @param central      The central manager providing this information.
 *  @param dict			A dictionary containing information about <i>central</i> that was preserved by the system at the time the app was terminated.
 *
 *  @discussion			For apps that opt-in to state preservation and restoration, this is the first method invoked when your app is relaunched into
 *						the background to complete some Bluetooth-related task. Use this method to synchronize your app's state with the state of the
 *						Bluetooth system.
 *
 *  @seealso            CBCentralManagerRestoredStatePeripheralsKey;
 *  @seealso            CBCentralManagerRestoredStateScanServicesKey;
 *  @seealso            CBCentralManagerRestoredStateScanOptionsKey;
 *
 */
- (void)centralManager:(CBCentralManager *)central willRestoreState:(NSDictionary<NSString *, id> *)dict;

/*!
 *  @method centralManager:didDiscoverPeripheral:advertisementData:RSSI:
 *
 *  @param central              The central manager providing this update.
 *  @param peripheral           A <code>CBPeripheral</code> object.
 *  @param advertisementData    A dictionary containing any advertisement and scan response data.
 *  @param RSSI                 The current RSSI of <i>peripheral</i>, in dBm. A value of <code>127</code> is reserved and indicates the RSSI
 *								was not available.
 *
 *  @discussion                 This method is invoked while scanning, upon the discovery of <i>peripheral</i> by <i>central</i>. A discovered peripheral must
 *                              be retained in order to use it; otherwise, it is assumed to not be of interest and will be cleaned up by the central manager. For
 *                              a list of <i>advertisementData</i> keys, see {@link CBAdvertisementDataLocalNameKey} and other similar constants.
 *
 *  @seealso                    CBAdvertisementData.h
 *
 */
- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary<NSString *, id> *)advertisementData RSSI:(NSNumber *)RSSI;

/*!
 *  @method centralManager:didConnectPeripheral:
 *
 *  @param central      The central manager providing this information.
 *  @param peripheral   The <code>CBPeripheral</code> that has connected.
 *
 *  @discussion         This method is invoked when a connection initiated by {@link connectPeripheral:options:} has succeeded.
 *
 */
- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral;

/*!
 *  @method centralManager:didFailToConnectPeripheral:error:
 *
 *  @param central      The central manager providing this information.
 *  @param peripheral   The <code>CBPeripheral</code> that has failed to connect.
 *  @param error        The cause of the failure.
 *
 *  @discussion         This method is invoked when a connection initiated by {@link connectPeripheral:options:} has failed to complete. As connection attempts do not
 *                      timeout, the failure of a connection is atypical and usually indicative of a transient issue.
 *
 */
- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(nullable NSError *)error;

/*!
 *  @method centralManager:didDisconnectPeripheral:error:
 *
 *  @param central      The central manager providing this information.
 *  @param peripheral   The <code>CBPeripheral</code> that has disconnected.
 *  @param error        If an error occurred, the cause of the failure.
 *
 *  @discussion         This method is invoked upon the disconnection of a peripheral that was connected by {@link connectPeripheral:options:}. If the disconnection
 *                      was not initiated by {@link cancelPeripheralConnection}, the cause will be detailed in the <i>error</i> parameter. Once this method has been
 *                      called, no more methods will be invoked on <i>peripheral</i>'s <code>CBPeripheralDelegate</code>.
 *
 */
- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(nullable NSError *)error;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreBluetooth.framework/Headers/CBATTRequest.h
/*
 *	@file CBATTRequest.h
 *	@framework CoreBluetooth
 *
 *  @discussion
 *
 *	@copyright 2012 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CBCentral, CBCharacteristic;

/*!
 *  @class CBATTRequest
 *
 *  @discussion Represents a read or write request from a central.
 *
 */
NS_CLASS_AVAILABLE(10_9, 6_0)
CB_EXTERN_CLASS @interface CBATTRequest : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 *  @property central
 *
 *  @discussion The central that originated the request.
 *
 */
@property(readonly, nonatomic) CBCentral *central;

/*!
 *  @property characteristic
 *
 *  @discussion The characteristic whose value will be read or written.
 *
 */
@property(readonly, nonatomic) CBCharacteristic *characteristic;

/*!
 *  @property offset
 *
 *  @discussion The zero-based index of the first byte for the read or write.
 *
 */
@property(readonly, nonatomic) NSUInteger offset;

/*!
 *  @property value
 *
 *  @discussion The data being read or written.
 *				For read requests, <i>value</i> will be nil and should be set before responding via @link respondToRequest:withResult: @/link.
 *				For write requests, <i>value</i> will contain the data to be written.
 *
 */
@property(readwrite, copy, nullable) NSData *value;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreBluetooth.framework/Headers/CBPeripheralManager.h
/*
 *	@file CBPeripheralManager.h
 *	@framework CoreBluetooth
 *
 *  @discussion Entry point to the peripheral role.
 *
 *	@copyright 2012 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CBDefines.h>
#import <CoreBluetooth/CBError.h>
#import <CoreBluetooth/CBManager.h>
#import <CoreBluetooth/CBL2CAPChannel.h>

#import <CoreBluetooth/CBPeripheralManagerConstants.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @enum CBPeripheralManagerAuthorizationStatus
 *
 *  @discussion Represents the current state of a CBPeripheralManager.
 *
 *  @constant CBPeripheralManagerAuthorizationStatusNotDetermined	User has not yet made a choice with regards to this application.
 *  @constant CBPeripheralManagerAuthorizationStatusRestricted		This application is not authorized to share data while backgrounded. The user cannot change this application’s status, possibly due to active restrictions such as parental controls being in place.
 *  @constant CBPeripheralManagerAuthorizationStatusDenied			User has explicitly denied this application from sharing data while backgrounded.
 *  @constant CBPeripheralManagerAuthorizationStatusAuthorized		User has authorized this application to share data while backgrounded.
 *
 */
typedef NS_ENUM(NSInteger, CBPeripheralManagerAuthorizationStatus) {
	CBPeripheralManagerAuthorizationStatusNotDetermined = 0,
	CBPeripheralManagerAuthorizationStatusRestricted,
	CBPeripheralManagerAuthorizationStatusDenied,
	CBPeripheralManagerAuthorizationStatusAuthorized,		
} NS_ENUM_AVAILABLE(10_9, 7_0);

/*!
 *  @enum CBPeripheralManagerState
 *
 *  @discussion Represents the current state of a CBPeripheralManager.
 *
 *  @constant CBPeripheralManagerStateUnknown       State unknown, update imminent.
 *  @constant CBPeripheralManagerStateResetting     The connection with the system service was momentarily lost, update imminent.
 *  @constant CBPeripheralManagerStateUnsupported   The platform doesn't support the Bluetooth Low Energy Peripheral/Server role.
 *  @constant CBPeripheralManagerStateUnauthorized  The application is not authorized to use the Bluetooth Low Energy Peripheral/Server role.
 *  @constant CBPeripheralManagerStatePoweredOff    Bluetooth is currently powered off.
 *  @constant CBPeripheralManagerStatePoweredOn     Bluetooth is currently powered on and available to use.
 *
 */
typedef NS_ENUM(NSInteger, CBPeripheralManagerState) {
	CBPeripheralManagerStateUnknown = CBManagerStateUnknown,
	CBPeripheralManagerStateResetting = CBManagerStateResetting,
	CBPeripheralManagerStateUnsupported = CBManagerStateUnsupported,
	CBPeripheralManagerStateUnauthorized = CBManagerStateUnauthorized,
	CBPeripheralManagerStatePoweredOff = CBManagerStatePoweredOff,
	CBPeripheralManagerStatePoweredOn = CBManagerStatePoweredOn,
} NS_DEPRECATED(10_9, 10_13, 6_0, 10_0, "Use CBManagerState instead");

/*!
 *  @enum CBPeripheralManagerConnectionLatency
 *
 *  @discussion The latency of a peripheral-central connection controls how frequently messages can be exchanged.
 *
 *	@constant CBPeripheralManagerConnectionLatencyLow       Prioritizes rapid communication over battery life.
 *	@constant CBPeripheralManagerConnectionLatencyMedium    A balance between communication frequency and battery life.
 *	@constant CBPeripheralManagerConnectionLatencyHigh      Prioritizes extending battery life over rapid communication.
 *
 */
typedef NS_ENUM(NSInteger, CBPeripheralManagerConnectionLatency) {
	CBPeripheralManagerConnectionLatencyLow = 0,
	CBPeripheralManagerConnectionLatencyMedium,
	CBPeripheralManagerConnectionLatencyHigh
} NS_ENUM_AVAILABLE(10_9, 6_0);

@class CBCentral, CBService, CBMutableService, CBCharacteristic, CBMutableCharacteristic, CBATTRequest;
@protocol CBPeripheralManagerDelegate;

/*!
 *  @class CBPeripheralManager
 *
 *  @discussion The <code>CBPeripheralManager</code> class is an abstraction of the Peripheral and Broadcaster GAP roles, and the GATT Server
 *              role. Its primary function is to allow you to manage published services within the GATT database, and to advertise these services
 *              to other devices.
 *              Each application has sandboxed access to the shared GATT database. You can add services to the database by calling {@link addService:};
 *              they can be removed via {@link removeService:} and {@link removeAllServices}, as appropriate. While a service is in the database,
 *              it is visible to and can be accessed by any connected GATT Client. However, applications that have not specified the "bluetooth-peripheral"
 *              background mode will have the contents of their service(s) "disabled" when in the background. Any remote device trying to access
 *              characteristic values or descriptors during this time will receive an error response.
 *              Once you've published services that you want to share, you can ask to advertise their availability and allow other devices to connect
 *              to you by calling {@link startAdvertising:}. Like the GATT database, advertisement is managed at the system level and shared by all
 *              applications. This means that even if you aren't advertising at the moment, someone else might be!
 *
 */
NS_CLASS_AVAILABLE(10_9, 6_0)
CB_EXTERN_CLASS @interface CBPeripheralManager : CBManager

/*!
 *  @property delegate
 *
 *  @discussion The delegate object that will receive peripheral events.
 *
 */
@property(nonatomic, weak, nullable) id<CBPeripheralManagerDelegate> delegate;

/*!
 *  @property isAdvertising
 *
 *  @discussion Whether or not the peripheral is currently advertising data.
 *
 */
@property(nonatomic, assign, readonly) BOOL isAdvertising;

/*!
 *  @method authorizationStatus
 *
 *  @discussion	This method does not prompt the user for access. You can use it to detect restricted access and simply hide UI instead of
 *				prompting for access.
 *
 *  @return		The current authorization status for sharing data while backgrounded. For the constants returned, see {@link CBPeripheralManagerAuthorizationStatus}.
 *
 *  @see		CBPeripheralManagerAuthorizationStatus
 */
+ (CBPeripheralManagerAuthorizationStatus)authorizationStatus NS_AVAILABLE(10_9, 7_0);

- (instancetype)init;

/*!
 *  @method initWithDelegate:queue:
 *
 *  @param delegate The delegate that will receive peripheral role events.
 *  @param queue    The dispatch queue on which the events will be dispatched.
 *
 *  @discussion     The initialization call. The events of the peripheral role will be dispatched on the provided queue.
 *                  If <i>nil</i>, the main queue will be used.
 *
 */
- (instancetype)initWithDelegate:(nullable id<CBPeripheralManagerDelegate>)delegate
						   queue:(nullable dispatch_queue_t)queue __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*!
 *  @method initWithDelegate:queue:options:
 *
 *  @param delegate The delegate that will receive peripheral role events.
 *  @param queue    The dispatch queue on which the events will be dispatched.
 *  @param options  An optional dictionary specifying options for the manager.
 *
 *  @discussion     The initialization call. The events of the peripheral role will be dispatched on the provided queue.
 *                  If <i>nil</i>, the main queue will be used.
 *
 *	@seealso		CBPeripheralManagerOptionShowPowerAlertKey
 *	@seealso		CBPeripheralManagerOptionRestoreIdentifierKey
 *
 */
- (instancetype)initWithDelegate:(nullable id<CBPeripheralManagerDelegate>)delegate
						   queue:(nullable dispatch_queue_t)queue
						 options:(nullable NSDictionary<NSString *, id> *)options NS_AVAILABLE(10_9, 7_0) NS_DESIGNATED_INITIALIZER __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*!
 *  @method startAdvertising:
 *
 *  @param advertisementData    An optional dictionary containing the data to be advertised.
 *
 *  @discussion                 Starts advertising. Supported advertising data types are <code>CBAdvertisementDataLocalNameKey</code>
 *                              and <code>CBAdvertisementDataServiceUUIDsKey</code>.
 *                              When in the foreground, an application can utilize up to 28 bytes of space in the initial advertisement data for 
 *                              any combination of the supported advertising data types. If this space is used up, there are an additional 10 bytes of 
 *                              space in the scan response that can be used only for the local name. Note that these sizes do not include the 2 bytes 
 *                              of header information that are required for each new data type. Any service UUIDs that do not fit in the allotted space 
 *                              will be added to a special "overflow" area, and can only be discovered by an iOS device that is explicitly scanning
 *                              for them.
 *                              While an application is in the background, the local name will not be used and all service UUIDs will be placed in the
 *                              "overflow" area. However, applications that have not specified the "bluetooth-peripheral" background mode will not be able 
 *                              to advertise anything while in the background.
 *
 *  @see                        peripheralManagerDidStartAdvertising:error:
 *  @seealso                    CBAdvertisementData.h
 *
 */
- (void)startAdvertising:(nullable NSDictionary<NSString *, id> *)advertisementData;

/*!
 *  @method stopAdvertising
 *
 *  @discussion Stops advertising.
 *
 */
- (void)stopAdvertising;

/*!
 *  @method setDesiredConnectionLatency:forCentral:
 *
 *  @param latency  The desired connection latency.
 *  @param central  A connected central.
 *
 *  @discussion     Sets the desired connection latency for an existing connection to <i>central</i>. Connection latency changes are not guaranteed, so the
 *                  resultant latency may vary. If a desired latency is not set, the latency chosen by <i>central</i> at the time of connection establishment
 *                  will be used. Typically, it is not necessary to change the latency.
 *
 *  @see            CBPeripheralManagerConnectionLatency
 *
 */
- (void)setDesiredConnectionLatency:(CBPeripheralManagerConnectionLatency)latency forCentral:(CBCentral *)central;

/*!
 *  @method addService:
 *
 *  @param service  A GATT service.
 *
 *  @discussion     Publishes a service and its associated characteristic(s) to the local database. If the service contains included services,
 *                  they must be published first.
 *
 *  @see            peripheralManager:didAddService:error:
 */
- (void)addService:(CBMutableService *)service;

/*!
 *  @method removeService:
 *
 *  @param service  A GATT service.
 *
 *  @discussion     Removes a published service from the local database. If the service is included by other service(s), they must be removed
 *                  first.
 *
 */
- (void)removeService:(CBMutableService *)service;

/*!
 *  @method removeAllServices
 *
 *  @discussion Removes all published services from the local database.
 *
 */
- (void)removeAllServices;

/*!
 *  @method respondToRequest:withResult:
 *
 *  @param request  The original request that was received from the central.
 *  @param result   The result of attempting to fulfill <i>request</i>.
 *
 *  @discussion     Used to respond to request(s) received via the @link peripheralManager:didReceiveReadRequest: @/link or
 *                  @link peripheralManager:didReceiveWriteRequests: @/link delegate methods.
 *
 *  @see            peripheralManager:didReceiveReadRequest:
 *  @see            peripheralManager:didReceiveWriteRequests:
 */
- (void)respondToRequest:(CBATTRequest *)request withResult:(CBATTError)result;

/*!
 *  @method updateValue:forCharacteristic:onSubscribedCentrals:
 *
 *  @param value            The value to be sent via a notification/indication.
 *  @param characteristic   The characteristic whose value has changed.
 *  @param centrals         A list of <code>CBCentral</code> objects to receive the update. Note that centrals which have not subscribed to
 *                          <i>characteristic</i> will be ignored. If <i>nil</i>, all centrals that are subscribed to <i>characteristic</i> will be updated.
 *
 *  @discussion             Sends an updated characteristic value to one or more centrals, via a notification or indication. If <i>value</i> exceeds
 *							{@link maximumUpdateValueLength}, it will be truncated to fit.
 *
 *  @return                 <i>YES</i> if the update could be sent, or <i>NO</i> if the underlying transmit queue is full. If <i>NO</i> was returned,
 *                          the delegate method @link peripheralManagerIsReadyToUpdateSubscribers: @/link will be called once space has become
 *                          available, and the update should be re-sent if so desired.
 *
 *  @see                    peripheralManager:central:didSubscribeToCharacteristic:
 *  @see                    peripheralManager:central:didUnsubscribeFromCharacteristic:
 *  @see                    peripheralManagerIsReadyToUpdateSubscribers:
 *	@seealso				maximumUpdateValueLength
 */
- (BOOL)updateValue:(NSData *)value forCharacteristic:(CBMutableCharacteristic *)characteristic onSubscribedCentrals:(nullable NSArray<CBCentral *> *)centrals;

/*!
 *  @method publishL2CAPChannelWithEncryption:
 *
 *  @param encryptionRequired		YES if the service requires the link to be encrypted before a stream can be established.  NO if the service can be used over
 *									an unsecured link.
 *
 *  @discussion     Create a listener for incoming L2CAP Channel connections.  The system will determine an unused PSM at the time of publishing, which will be returned
 *					with @link peripheralManager:didPublishL2CAPChannel:error: @/link.  L2CAP Channels are not discoverable by themselves, so it is the application's
 *					responsibility to handle PSM discovery on the client.
 *
 */
- (void)publishL2CAPChannelWithEncryption:(BOOL)encryptionRequired NS_AVAILABLE(10_14, 11_0);

/*!
 *  @method unpublishL2CAPChannel:
 *
 *  @param PSM		The service PSM to be removed from the system.
 *
 *  @discussion     Removes a published service from the local system.  No new connections for this PSM will be accepted, and any existing L2CAP channels
 *					using this PSM will be closed.
 *
 */
- (void)unpublishL2CAPChannel:(CBL2CAPPSM)PSM NS_AVAILABLE(10_14, 11_0);

@end


/*!
 *  @protocol CBPeripheralManagerDelegate
 *
 *  @discussion The delegate of a @link CBPeripheralManager @/link object must adopt the <code>CBPeripheralManagerDelegate</code> protocol. The
 *              single required method indicates the availability of the peripheral manager, while the optional methods provide information about
 *              centrals, which can connect and access the local database.
 *
 */
@protocol CBPeripheralManagerDelegate <NSObject>

@required

/*!
 *  @method peripheralManagerDidUpdateState:
 *
 *  @param peripheral   The peripheral manager whose state has changed.
 *
 *  @discussion         Invoked whenever the peripheral manager's state has been updated. Commands should only be issued when the state is 
 *                      <code>CBPeripheralManagerStatePoweredOn</code>. A state below <code>CBPeripheralManagerStatePoweredOn</code>
 *                      implies that advertisement has paused and any connected centrals have been disconnected. If the state moves below
 *                      <code>CBPeripheralManagerStatePoweredOff</code>, advertisement is stopped and must be explicitly restarted, and the
 *                      local database is cleared and all services must be re-added.
 *
 *  @see                state
 *
 */
- (void)peripheralManagerDidUpdateState:(CBPeripheralManager *)peripheral;

@optional

/*!
 *  @method peripheralManager:willRestoreState:
 *
 *  @param peripheral	The peripheral manager providing this information.
 *  @param dict			A dictionary containing information about <i>peripheral</i> that was preserved by the system at the time the app was terminated.
 *
 *  @discussion			For apps that opt-in to state preservation and restoration, this is the first method invoked when your app is relaunched into
 *						the background to complete some Bluetooth-related task. Use this method to synchronize your app's state with the state of the
 *						Bluetooth system.
 *
 *  @seealso            CBPeripheralManagerRestoredStateServicesKey;
 *  @seealso            CBPeripheralManagerRestoredStateAdvertisementDataKey;
 *
 */
- (void)peripheralManager:(CBPeripheralManager *)peripheral willRestoreState:(NSDictionary<NSString *, id> *)dict;

/*!
 *  @method peripheralManagerDidStartAdvertising:error:
 *
 *  @param peripheral   The peripheral manager providing this information.
 *  @param error        If an error occurred, the cause of the failure.
 *
 *  @discussion         This method returns the result of a @link startAdvertising: @/link call. If advertisement could
 *                      not be started, the cause will be detailed in the <i>error</i> parameter.
 *
 */
- (void)peripheralManagerDidStartAdvertising:(CBPeripheralManager *)peripheral error:(nullable NSError *)error;

/*!
 *  @method peripheralManager:didAddService:error:
 *
 *  @param peripheral   The peripheral manager providing this information.
 *  @param service      The service that was added to the local database.
 *  @param error        If an error occurred, the cause of the failure.
 *
 *  @discussion         This method returns the result of an @link addService: @/link call. If the service could
 *                      not be published to the local database, the cause will be detailed in the <i>error</i> parameter.
 *
 */
- (void)peripheralManager:(CBPeripheralManager *)peripheral didAddService:(CBService *)service error:(nullable NSError *)error;

/*!
 *  @method peripheralManager:central:didSubscribeToCharacteristic:
 *
 *  @param peripheral       The peripheral manager providing this update.
 *  @param central          The central that issued the command.
 *  @param characteristic   The characteristic on which notifications or indications were enabled.
 *
 *  @discussion             This method is invoked when a central configures <i>characteristic</i> to notify or indicate.
 *                          It should be used as a cue to start sending updates as the characteristic value changes.
 *
 */
- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didSubscribeToCharacteristic:(CBCharacteristic *)characteristic;

/*!
 *  @method peripheralManager:central:didUnsubscribeFromCharacteristic:
 *
 *  @param peripheral       The peripheral manager providing this update.
 *  @param central          The central that issued the command.
 *  @param characteristic   The characteristic on which notifications or indications were disabled.
 *
 *  @discussion             This method is invoked when a central removes notifications/indications from <i>characteristic</i>.
 *
 */
- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didUnsubscribeFromCharacteristic:(CBCharacteristic *)characteristic;

/*!
 *  @method peripheralManager:didReceiveReadRequest:
 *
 *  @param peripheral   The peripheral manager requesting this information.
 *  @param request      A <code>CBATTRequest</code> object.
 *
 *  @discussion         This method is invoked when <i>peripheral</i> receives an ATT request for a characteristic with a dynamic value.
 *                      For every invocation of this method, @link respondToRequest:withResult: @/link must be called.
 *
 *  @see                CBATTRequest
 *
 */
- (void)peripheralManager:(CBPeripheralManager *)peripheral didReceiveReadRequest:(CBATTRequest *)request;

/*!
 *  @method peripheralManager:didReceiveWriteRequests:
 *
 *  @param peripheral   The peripheral manager requesting this information.
 *  @param requests     A list of one or more <code>CBATTRequest</code> objects.
 *
 *  @discussion         This method is invoked when <i>peripheral</i> receives an ATT request or command for one or more characteristics with a dynamic value.
 *                      For every invocation of this method, @link respondToRequest:withResult: @/link should be called exactly once. If <i>requests</i> contains
 *                      multiple requests, they must be treated as an atomic unit. If the execution of one of the requests would cause a failure, the request
 *                      and error reason should be provided to <code>respondToRequest:withResult:</code> and none of the requests should be executed.
 *
 *  @see                CBATTRequest
 *
 */
- (void)peripheralManager:(CBPeripheralManager *)peripheral didReceiveWriteRequests:(NSArray<CBATTRequest *> *)requests;

/*!
 *  @method peripheralManagerIsReadyToUpdateSubscribers:
 *
 *  @param peripheral   The peripheral manager providing this update.
 *
 *  @discussion         This method is invoked after a failed call to @link updateValue:forCharacteristic:onSubscribedCentrals: @/link, when <i>peripheral</i> is again
 *                      ready to send characteristic value updates.
 *
 */
- (void)peripheralManagerIsReadyToUpdateSubscribers:(CBPeripheralManager *)peripheral;

/*!
 *  @method peripheralManager:didPublishL2CAPChannel:error:
 *
 *  @param peripheral   The peripheral manager requesting this information.
 *  @param PSM			The PSM of the channel that was published.
 *  @param error		If an error occurred, the cause of the failure.
 *
 *  @discussion         This method is the response to a  @link publishL2CAPChannel: @/link call.  The PSM will contain the PSM that was assigned for the published
 *						channel
 *
 */
- (void)peripheralManager:(CBPeripheralManager *)peripheral didPublishL2CAPChannel:(CBL2CAPPSM)PSM error:(nullable NSError *)error;

/*!
 *  @method peripheralManager:didUnublishL2CAPChannel:error:
 *
 *  @param peripheral   The peripheral manager requesting this information.
 *  @param PSM			The PSM of the channel that was published.
 *  @param error		If an error occurred, the cause of the failure.
 *
 *  @discussion         This method is the response to a  @link unpublishL2CAPChannel: @/link call.
 *
 */
- (void)peripheralManager:(CBPeripheralManager *)peripheral didUnpublishL2CAPChannel:(CBL2CAPPSM)PSM error:(nullable NSError *)error;

/*!
 *  @method peripheralManager:didOpenL2CAPChannel:error:
 *
 *  @param peripheral   The peripheral manager requesting this information.
 *  @param requests     A list of one or more <code>CBATTRequest</code> objects.
 *
 *  @discussion         This method is invoked when <i>peripheral</i> receives an ATT request or command for one or more characteristics with a dynamic value.
 *                      For every invocation of this method, @link respondToRequest:withResult: @/link should be called exactly once. If <i>requests</i> contains
 *                      multiple requests, they must be treated as an atomic unit. If the execution of one of the requests would cause a failure, the request
 *                      and error reason should be provided to <code>respondToRequest:withResult:</code> and none of the requests should be executed.
 *
 *  @see                CBATTRequest
 *
 */
- (void)peripheralManager:(CBPeripheralManager *)peripheral didOpenL2CAPChannel:(nullable CBL2CAPChannel *)channel error:(nullable NSError *)error;
@end

NS_ASSUME_NONNULL_END
// ==========  CoreBluetooth.framework/Headers/CBAttribute.h
/*
 *	@file CBAttribute.h
 *	@framework CoreBluetooth
 *
 *	@copyright 2014 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CBUUID;
@class CBPeripheral, CBCentral;
@class CBService, CBCharacteristic, CBDescriptor;

NS_CLASS_AVAILABLE(10_13, 8_0)
CB_EXTERN_CLASS @interface CBAttribute : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @property UUID
 *
 * @discussion
 *      The Bluetooth UUID of the attribute.
 *
 */
@property(readonly, nonatomic) CBUUID *UUID;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreBluetooth.framework/Headers/CBError.h
/*
 *	@file CBError.h
 *	@framework CoreBluetooth
 *
 *  @discussion The possible errors returned during LE transactions.
 *
 *	@copyright 2011 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

CB_EXTERN NSString * const CBErrorDomain;

/*!
 * @enum CBError
 *
 * @discussion The possible errors returned during LE transactions.
 */
typedef NS_ENUM(NSInteger, CBError) {
	CBErrorUnknown												= 0,
	CBErrorInvalidParameters NS_ENUM_AVAILABLE(10_9, 6_0)		= 1,
	CBErrorInvalidHandle NS_ENUM_AVAILABLE(10_9, 6_0)			= 2,
	CBErrorNotConnected NS_ENUM_AVAILABLE(10_9, 6_0)			= 3,
	CBErrorOutOfSpace NS_ENUM_AVAILABLE(10_9, 6_0)				= 4,
	CBErrorOperationCancelled NS_ENUM_AVAILABLE(10_9, 6_0)		= 5,
	CBErrorConnectionTimeout NS_ENUM_AVAILABLE(10_9, 6_0)		= 6,
	CBErrorPeripheralDisconnected NS_ENUM_AVAILABLE(10_9, 6_0)	= 7,
	CBErrorUUIDNotAllowed NS_ENUM_AVAILABLE(10_9, 6_0)			= 8,
	CBErrorAlreadyAdvertising NS_ENUM_AVAILABLE(10_9, 6_0)		= 9,
	CBErrorConnectionFailed NS_ENUM_AVAILABLE(10_13, 7_1)		= 10,
	CBErrorConnectionLimitReached NS_ENUM_AVAILABLE(10_13, 9_0)	= 11,
	CBErrorUnkownDevice NS_ENUM_DEPRECATED(10_13, 10_15, 9_0, 13_0, "Use CBErrorUnknownDevice instead") = 12,
	CBErrorUnknownDevice NS_ENUM_AVAILABLE(10_14, 12_0)			= 12,
	CBErrorOperationNotSupported NS_ENUM_AVAILABLE(10_14, 12_0)	= 13,

};

CB_EXTERN NSString * const CBATTErrorDomain;

typedef NS_ENUM(NSInteger, CBATTError) {
	CBATTErrorSuccess NS_ENUM_AVAILABLE(10_9, 6_0)	= 0x00,
	CBATTErrorInvalidHandle							= 0x01,
	CBATTErrorReadNotPermitted						= 0x02,
	CBATTErrorWriteNotPermitted						= 0x03,
	CBATTErrorInvalidPdu							= 0x04,
	CBATTErrorInsufficientAuthentication			= 0x05,
	CBATTErrorRequestNotSupported					= 0x06,
	CBATTErrorInvalidOffset							= 0x07,
	CBATTErrorInsufficientAuthorization				= 0x08,
	CBATTErrorPrepareQueueFull						= 0x09,
	CBATTErrorAttributeNotFound						= 0x0A,
	CBATTErrorAttributeNotLong						= 0x0B,
	CBATTErrorInsufficientEncryptionKeySize			= 0x0C,
	CBATTErrorInvalidAttributeValueLength			= 0x0D,
	CBATTErrorUnlikelyError							= 0x0E,
	CBATTErrorInsufficientEncryption				= 0x0F,
	CBATTErrorUnsupportedGroupType					= 0x10,
	CBATTErrorInsufficientResources					= 0x11
};

NS_ASSUME_NONNULL_END
// ==========  CoreBluetooth.framework/Headers/CBL2CAPChannel.h
/*
 *	@file CBL2CAPChannel.h
 *	@framework CoreBluetooth
 *
 *  @discussion
 *
 *	@copyright 2017 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBPeer.h>
#import <Foundation/Foundation.h>

typedef uint16_t CBL2CAPPSM;

/*!
 *  @class CBL2CAPChannel
 *
 *  @discussion A CBL2CAPChannel represents a live L2CAP connection to a remote device
 */
NS_CLASS_AVAILABLE(10_13, 11_0)
CB_EXTERN_CLASS @interface CBL2CAPChannel : NSObject

/*!
 *  @property peer
 *
 *  @discussion The peer connected to the channel
 */
@property(readonly, nonatomic) CBPeer *peer;

/*!
 *  @property inputStream
 *
 *  @discussion An NSStream used for reading data from the remote peer
 */
@property(readonly, nonatomic) NSInputStream *inputStream;

/*!
 *  @property outputStream
 *
 *  @discussion An NSStream used for writing data to the peer
 */
@property(readonly, nonatomic) NSOutputStream *outputStream;

/*!
 *  @property PSM
 *
 *  @discussion The PSM (Protocol/Service Multiplexer) of the channel
 */
@property(readonly, nonatomic) CBL2CAPPSM PSM;
@end
// ==========  CoreBluetooth.framework/Headers/CBCharacteristic.h
/*
 *	@file CBCharacteristic.h
 *	@framework CoreBluetooth
 *
 *	@copyright 2011 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBAttribute.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @enum CBCharacteristicProperties
 *
 *	@discussion Characteristic properties determine how the characteristic value can be	used, or how the descriptor(s) can be accessed. Can be combined. Unless
 *				otherwise specified, properties are valid for local characteristics published via @link CBPeripheralManager @/link.
 *
 *	@constant CBCharacteristicPropertyBroadcast						Permits broadcasts of the characteristic value using a characteristic configuration descriptor. Not allowed for local characteristics.
 *	@constant CBCharacteristicPropertyRead							Permits reads of the characteristic value.
 *	@constant CBCharacteristicPropertyWriteWithoutResponse			Permits writes of the characteristic value, without a response.
 *	@constant CBCharacteristicPropertyWrite							Permits writes of the characteristic value.
 *	@constant CBCharacteristicPropertyNotify						Permits notifications of the characteristic value, without a response.
 *	@constant CBCharacteristicPropertyIndicate						Permits indications of the characteristic value.
 *	@constant CBCharacteristicPropertyAuthenticatedSignedWrites		Permits signed writes of the characteristic value
 *	@constant CBCharacteristicPropertyExtendedProperties			If set, additional characteristic properties are defined in the characteristic extended properties descriptor. Not allowed for local characteristics.
 *	@constant CBCharacteristicPropertyNotifyEncryptionRequired		If set, only trusted devices can enable notifications of the characteristic value.
 *	@constant CBCharacteristicPropertyIndicateEncryptionRequired	If set, only trusted devices can enable indications of the characteristic value.
 *
 */
typedef NS_OPTIONS(NSUInteger, CBCharacteristicProperties) {
	CBCharacteristicPropertyBroadcast												= 0x01,
	CBCharacteristicPropertyRead													= 0x02,
	CBCharacteristicPropertyWriteWithoutResponse									= 0x04,
	CBCharacteristicPropertyWrite													= 0x08,
	CBCharacteristicPropertyNotify													= 0x10,
	CBCharacteristicPropertyIndicate												= 0x20,
	CBCharacteristicPropertyAuthenticatedSignedWrites								= 0x40,
	CBCharacteristicPropertyExtendedProperties										= 0x80,
	CBCharacteristicPropertyNotifyEncryptionRequired NS_ENUM_AVAILABLE(10_9, 6_0)	= 0x100,
	CBCharacteristicPropertyIndicateEncryptionRequired NS_ENUM_AVAILABLE(10_9, 6_0)	= 0x200
};



/*!
 *  @class CBCharacteristic
 *
 *  @discussion
 *      Represents a service's characteristic.
 *
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBCharacteristic : CBAttribute

/*!
 * @property service
 *
 *  @discussion
 *      A back-pointer to the service this characteristic belongs to.
 *
 */
@property(assign, readonly, nonatomic) CBService *service;

/*!
 * @property properties
 *
 *  @discussion
 *      The properties of the characteristic.
 *
 */
@property(readonly, nonatomic) CBCharacteristicProperties properties;

/*!
 * @property value
 *
 *  @discussion
 *      The value of the characteristic.
 *
 */
@property(retain, readonly, nullable) NSData *value;

/*!
 * @property descriptors
 *
 *  @discussion
 *      A list of the CBDescriptors that have so far been discovered in this characteristic.
 *
 */
@property(retain, readonly, nullable) NSArray<CBDescriptor *> *descriptors;

/*!
 * @property isBroadcasted
 *
 *  @discussion
 *      Whether the characteristic is currently broadcasted or not.
 *
 */
@property(readonly) BOOL isBroadcasted NS_DEPRECATED(10_9, 10_13, 5_0, 8_0);

/*!
 * @property isNotifying
 *
 *  @discussion
 *      Whether the characteristic is currently notifying or not.
 *
 */
@property(readonly) BOOL isNotifying;

@end

/*!
 *  @enum CBAttributePermissions
 *
 *	@discussion Read, write, and encryption permissions for an ATT attribute. Can be combined.
 *
 *	@constant CBAttributePermissionsReadable					Read-only.
 *	@constant CBAttributePermissionsWriteable					Write-only.
 *	@constant CBAttributePermissionsReadEncryptionRequired		Readable by trusted devices.
 *	@constant CBAttributePermissionsWriteEncryptionRequired		Writeable by trusted devices.
 *
 */
typedef NS_OPTIONS(NSUInteger, CBAttributePermissions) {
	CBAttributePermissionsReadable					= 0x01,
	CBAttributePermissionsWriteable					= 0x02,
	CBAttributePermissionsReadEncryptionRequired	= 0x04,
	CBAttributePermissionsWriteEncryptionRequired	= 0x08
} NS_ENUM_AVAILABLE(10_9, 6_0);


/*!
 *	@class CBMutableCharacteristic
 *
 *	@discussion Used to create a local characteristic, which can be added to the local database via <code>CBPeripheralManager</code>. Once a characteristic
 *				is published, it is cached and can no longer be changed. 
 *				If a characteristic value is specified, it will be cached and marked <code>CBCharacteristicPropertyRead</code> and 
 *				<code>CBAttributePermissionsReadable</code>. If a characteristic value needs to be writeable, or may change during the lifetime of the
 *				published <code>CBService</code>, it is considered a dynamic value and will be requested on-demand. Dynamic values are identified by a
 *				<i>value</i> of <i>nil</i>.
 *
 */
NS_CLASS_AVAILABLE(10_9, 6_0)
CB_EXTERN_CLASS @interface CBMutableCharacteristic : CBCharacteristic

/*!
 *	@property permissions
 *
 *	@discussion The permissions of the characteristic value.
 *
 *	@see		CBAttributePermissions
 */
@property(assign, readwrite, nonatomic) CBAttributePermissions permissions;

/*!
 *  @property subscribedCentrals
 *
 *  @discussion For notifying characteristics, the set of currently subscribed centrals.
 */
@property(retain, readonly, nullable) NSArray<CBCentral *> *subscribedCentrals NS_AVAILABLE(10_9, 7_0);

@property(assign, readwrite, nonatomic) CBCharacteristicProperties properties;
@property(retain, readwrite, nullable) NSData *value;
@property(retain, readwrite, nullable) NSArray<CBDescriptor *> *descriptors;

/*!
 *  @method initWithType:properties:value:permissions
 *
 *  @param UUID			The Bluetooth UUID of the characteristic.
 *  @param properties	The properties of the characteristic.
 *  @param value		The characteristic value to be cached. If <i>nil</i>, the value will be dynamic and requested on-demand.
 *	@param permissions	The permissions of the characteristic value.
 *
 *  @discussion			Returns an initialized characteristic.
 *
 */
- (instancetype)initWithType:(CBUUID *)UUID properties:(CBCharacteristicProperties)properties value:(nullable NSData *)value permissions:(CBAttributePermissions)permissions NS_DESIGNATED_INITIALIZER __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreBluetooth.framework/Headers/CBPeripheral.h
/*
 *	@file CBPeripheral.h
 *	@framework CoreBluetooth
 *
 *  @discussion Representation of a remote peripheral.
 *
 *	@copyright 2011 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBDefines.h>
#import <CoreBluetooth/CBPeer.h>
#import <CoreBluetooth/CBL2CAPChannel.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @enum CBPeripheralState
 *
 *  @discussion Represents the current connection state of a CBPeripheral.
 *
 */
typedef NS_ENUM(NSInteger, CBPeripheralState) {
	CBPeripheralStateDisconnected = 0,
	CBPeripheralStateConnecting,
	CBPeripheralStateConnected,
	CBPeripheralStateDisconnecting NS_AVAILABLE(10_13, 9_0),
} NS_AVAILABLE(10_9, 7_0);

/*!
 *  @enum CBCharacteristicWriteType
 *
 *  @discussion Specifies which type of write is to be performed on a CBCharacteristic.
 *
 */
typedef NS_ENUM(NSInteger, CBCharacteristicWriteType) {
	CBCharacteristicWriteWithResponse = 0,
	CBCharacteristicWriteWithoutResponse,
};

@protocol CBPeripheralDelegate;
@class CBService, CBCharacteristic, CBDescriptor, CBUUID;

/*!
 *  @class CBPeripheral
 *
 *  @discussion Represents a peripheral.
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBPeripheral : CBPeer

/*!
 *  @property delegate
 *
 *  @discussion The delegate object that will receive peripheral events.
 */
@property(weak, nonatomic, nullable) id<CBPeripheralDelegate> delegate;

/*!
 *  @property name
 *
 *  @discussion The name of the peripheral.
 */
@property(retain, readonly, nullable) NSString *name;

/*!
 *  @property RSSI
 *
 *  @discussion The most recently read RSSI, in decibels.
 *
 *  @deprecated Use {@link peripheral:didReadRSSI:error:} instead.
 */
@property(retain, readonly, nullable) NSNumber *RSSI NS_DEPRECATED(10_7, 10_13, 5_0, 8_0);

/*!
 *  @property state
 *
 *  @discussion The current connection state of the peripheral.
 */
@property(readonly) CBPeripheralState state;

/*!
 *  @property services
 *
 *  @discussion A list of <code>CBService</code> objects that have been discovered on the peripheral.
 */
@property(retain, readonly, nullable) NSArray<CBService *> *services;

/*!
 *  @property canSendWriteWithoutResponse
 *
 *  @discussion YES if the remote device has space to send a write without response.  If this value is NO,
 *				the value will be set to YES after the current writes have been flushed, and
 *				<link>peripheralIsReadyToSendWriteWithoutResponse:</link> will be called.
 */
@property(readonly) BOOL canSendWriteWithoutResponse;

/*!
 *  @method readRSSI
 *
 *  @discussion While connected, retrieves the current RSSI of the link.
 *
 *  @see        peripheral:didReadRSSI:error:
 */
- (void)readRSSI;

/*!
 *  @method discoverServices:
 *
 *  @param serviceUUIDs A list of <code>CBUUID</code> objects representing the service types to be discovered. If <i>nil</i>,
 *						all services will be discovered.
 *
 *  @discussion			Discovers available service(s) on the peripheral.
 *
 *  @see				peripheral:didDiscoverServices:
 */
- (void)discoverServices:(nullable NSArray<CBUUID *> *)serviceUUIDs;

/*!
 *  @method discoverIncludedServices:forService:
 *
 *  @param includedServiceUUIDs A list of <code>CBUUID</code> objects representing the included service types to be discovered. If <i>nil</i>,
 *								all of <i>service</i>s included services will be discovered, which is considerably slower and not recommended.
 *  @param service				A GATT service.
 *
 *  @discussion					Discovers the specified included service(s) of <i>service</i>.
 *
 *  @see						peripheral:didDiscoverIncludedServicesForService:error:
 */
- (void)discoverIncludedServices:(nullable NSArray<CBUUID *> *)includedServiceUUIDs forService:(CBService *)service;

/*!
 *  @method discoverCharacteristics:forService:
 *
 *  @param characteristicUUIDs	A list of <code>CBUUID</code> objects representing the characteristic types to be discovered. If <i>nil</i>,
 *								all characteristics of <i>service</i> will be discovered.
 *  @param service				A GATT service.
 *
 *  @discussion					Discovers the specified characteristic(s) of <i>service</i>.
 *
 *  @see						peripheral:didDiscoverCharacteristicsForService:error:
 */
- (void)discoverCharacteristics:(nullable NSArray<CBUUID *> *)characteristicUUIDs forService:(CBService *)service;

/*!
 *  @method readValueForCharacteristic:
 *
 *  @param characteristic	A GATT characteristic.
 *
 *  @discussion				Reads the characteristic value for <i>characteristic</i>.
 *
 *  @see					peripheral:didUpdateValueForCharacteristic:error:
 */
- (void)readValueForCharacteristic:(CBCharacteristic *)characteristic;

/*!
 *  @method		maximumWriteValueLengthForType:
 *
 *  @discussion	The maximum amount of data, in bytes, that can be sent to a characteristic in a single write type.
 *
 *  @see		writeValue:forCharacteristic:type:
 */
- (NSUInteger)maximumWriteValueLengthForType:(CBCharacteristicWriteType)type NS_AVAILABLE(10_12, 9_0);

/*!
 *  @method writeValue:forCharacteristic:type:
 *
 *  @param data				The value to write.
 *  @param characteristic	The characteristic whose characteristic value will be written.
 *  @param type				The type of write to be executed.
 *
 *  @discussion				Writes <i>value</i> to <i>characteristic</i>'s characteristic value.
 *							If the <code>CBCharacteristicWriteWithResponse</code> type is specified, {@link peripheral:didWriteValueForCharacteristic:error:}
 *							is called with the result of the write request.
 *							If the <code>CBCharacteristicWriteWithoutResponse</code> type is specified, and canSendWriteWithoutResponse is false, the delivery
 * 							of the data is best-effort and may not be guaranteed.
 *
 *  @see					peripheral:didWriteValueForCharacteristic:error:
 *  @see					peripheralIsReadyToSendWriteWithoutResponse:
 *	@see					canSendWriteWithoutResponse
 *	@see					CBCharacteristicWriteType
 */
- (void)writeValue:(NSData *)data forCharacteristic:(CBCharacteristic *)characteristic type:(CBCharacteristicWriteType)type;

/*!
 *  @method setNotifyValue:forCharacteristic:
 *
 *  @param enabled			Whether or not notifications/indications should be enabled.
 *  @param characteristic	The characteristic containing the client characteristic configuration descriptor.
 *
 *  @discussion				Enables or disables notifications/indications for the characteristic value of <i>characteristic</i>. If <i>characteristic</i>
 *							allows both, notifications will be used.
 *                          When notifications/indications are enabled, updates to the characteristic value will be received via delegate method 
 *                          @link peripheral:didUpdateValueForCharacteristic:error: @/link. Since it is the peripheral that chooses when to send an update,
 *                          the application should be prepared to handle them as long as notifications/indications remain enabled.
 *
 *  @see					peripheral:didUpdateNotificationStateForCharacteristic:error:
 *  @seealso                CBConnectPeripheralOptionNotifyOnNotificationKey
 */
- (void)setNotifyValue:(BOOL)enabled forCharacteristic:(CBCharacteristic *)characteristic;

/*!
 *  @method discoverDescriptorsForCharacteristic:
 *
 *  @param characteristic	A GATT characteristic.
 *
 *  @discussion				Discovers the characteristic descriptor(s) of <i>characteristic</i>.
 *
 *  @see					peripheral:didDiscoverDescriptorsForCharacteristic:error:
 */
- (void)discoverDescriptorsForCharacteristic:(CBCharacteristic *)characteristic;

/*!
 *  @method readValueForDescriptor:
 *
 *  @param descriptor	A GATT characteristic descriptor.
 *
 *  @discussion			Reads the value of <i>descriptor</i>.
 *
 *  @see				peripheral:didUpdateValueForDescriptor:error:
 */
- (void)readValueForDescriptor:(CBDescriptor *)descriptor;

/*!
 *  @method writeValue:forDescriptor:
 *
 *  @param data			The value to write.
 *  @param descriptor	A GATT characteristic descriptor.
 *
 *  @discussion			Writes <i>data</i> to <i>descriptor</i>'s value. Client characteristic configuration descriptors cannot be written using
 *						this method, and should instead use @link setNotifyValue:forCharacteristic: @/link.
 *
 *  @see				peripheral:didWriteValueForCharacteristic:error:
 */
- (void)writeValue:(NSData *)data forDescriptor:(CBDescriptor *)descriptor;

/*!
 *  @method openL2CAPChannel:
 *
 *  @param PSM			The PSM of the channel to open
 *
 *  @discussion			Attempt to open an L2CAP channel to the peripheral using the supplied PSM.  
 *
 *  @see				peripheral:didWriteValueForCharacteristic:error:
 */
- (void)openL2CAPChannel:(CBL2CAPPSM)PSM NS_AVAILABLE(10_14, 11_0);
@end



/*!
 *  @protocol CBPeripheralDelegate
 *
 *  @discussion Delegate for CBPeripheral.
 *
 */
@protocol CBPeripheralDelegate <NSObject>

@optional

/*!
 *  @method peripheralDidUpdateName:
 *
 *  @param peripheral	The peripheral providing this update.
 *
 *  @discussion			This method is invoked when the @link name @/link of <i>peripheral</i> changes.
 */
- (void)peripheralDidUpdateName:(CBPeripheral *)peripheral NS_AVAILABLE(10_9, 6_0);

/*!
 *  @method peripheral:didModifyServices:
 *
 *  @param peripheral			The peripheral providing this update.
 *  @param invalidatedServices	The services that have been invalidated
 *
 *  @discussion			This method is invoked when the @link services @/link of <i>peripheral</i> have been changed.
 *						At this point, the designated <code>CBService</code> objects have been invalidated.
 *						Services can be re-discovered via @link discoverServices: @/link.
 */
- (void)peripheral:(CBPeripheral *)peripheral didModifyServices:(NSArray<CBService *> *)invalidatedServices NS_AVAILABLE(10_9, 7_0);

/*!
 *  @method peripheralDidUpdateRSSI:error:
 *
 *  @param peripheral	The peripheral providing this update.
 *	@param error		If an error occurred, the cause of the failure.
 *
 *  @discussion			This method returns the result of a @link readRSSI: @/link call.
 *
 *  @deprecated			Use {@link peripheral:didReadRSSI:error:} instead.
 */
- (void)peripheralDidUpdateRSSI:(CBPeripheral *)peripheral error:(nullable NSError *)error NS_DEPRECATED(10_7, 10_13, 5_0, 8_0);

/*!
 *  @method peripheral:didReadRSSI:error:
 *
 *  @param peripheral	The peripheral providing this update.
 *  @param RSSI			The current RSSI of the link.
 *  @param error		If an error occurred, the cause of the failure.
 *
 *  @discussion			This method returns the result of a @link readRSSI: @/link call.
 */
- (void)peripheral:(CBPeripheral *)peripheral didReadRSSI:(NSNumber *)RSSI error:(nullable NSError *)error NS_AVAILABLE(10_13, 8_0);

/*!
 *  @method peripheral:didDiscoverServices:
 *
 *  @param peripheral	The peripheral providing this information.
 *	@param error		If an error occurred, the cause of the failure.
 *
 *  @discussion			This method returns the result of a @link discoverServices: @/link call. If the service(s) were read successfully, they can be retrieved via
 *						<i>peripheral</i>'s @link services @/link property.
 *
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(nullable NSError *)error;

/*!
 *  @method peripheral:didDiscoverIncludedServicesForService:error:
 *
 *  @param peripheral	The peripheral providing this information.
 *  @param service		The <code>CBService</code> object containing the included services.
 *	@param error		If an error occurred, the cause of the failure.
 *
 *  @discussion			This method returns the result of a @link discoverIncludedServices:forService: @/link call. If the included service(s) were read successfully, 
 *						they can be retrieved via <i>service</i>'s <code>includedServices</code> property.
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverIncludedServicesForService:(CBService *)service error:(nullable NSError *)error;

/*!
 *  @method peripheral:didDiscoverCharacteristicsForService:error:
 *
 *  @param peripheral	The peripheral providing this information.
 *  @param service		The <code>CBService</code> object containing the characteristic(s).
 *	@param error		If an error occurred, the cause of the failure.
 *
 *  @discussion			This method returns the result of a @link discoverCharacteristics:forService: @/link call. If the characteristic(s) were read successfully, 
 *						they can be retrieved via <i>service</i>'s <code>characteristics</code> property.
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(nullable NSError *)error;

/*!
 *  @method peripheral:didUpdateValueForCharacteristic:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param characteristic	A <code>CBCharacteristic</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method is invoked after a @link readValueForCharacteristic: @/link call, or upon receipt of a notification/indication.
 */
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(nullable NSError *)error;

/*!
 *  @method peripheral:didWriteValueForCharacteristic:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param characteristic	A <code>CBCharacteristic</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a {@link writeValue:forCharacteristic:type:} call, when the <code>CBCharacteristicWriteWithResponse</code> type is used.
 */
 - (void)peripheral:(CBPeripheral *)peripheral didWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(nullable NSError *)error;

/*!
 *  @method peripheral:didUpdateNotificationStateForCharacteristic:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param characteristic	A <code>CBCharacteristic</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a @link setNotifyValue:forCharacteristic: @/link call. 
 */
- (void)peripheral:(CBPeripheral *)peripheral didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic error:(nullable NSError *)error;

/*!
 *  @method peripheral:didDiscoverDescriptorsForCharacteristic:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param characteristic	A <code>CBCharacteristic</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a @link discoverDescriptorsForCharacteristic: @/link call. If the descriptors were read successfully, 
 *							they can be retrieved via <i>characteristic</i>'s <code>descriptors</code> property.
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverDescriptorsForCharacteristic:(CBCharacteristic *)characteristic error:(nullable NSError *)error;

/*!
 *  @method peripheral:didUpdateValueForDescriptor:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param descriptor		A <code>CBDescriptor</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a @link readValueForDescriptor: @/link call.
 */
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForDescriptor:(CBDescriptor *)descriptor error:(nullable NSError *)error;

/*!
 *  @method peripheral:didWriteValueForDescriptor:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param descriptor		A <code>CBDescriptor</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a @link writeValue:forDescriptor: @/link call.
 */
- (void)peripheral:(CBPeripheral *)peripheral didWriteValueForDescriptor:(CBDescriptor *)descriptor error:(nullable NSError *)error;

/*!
 *  @method peripheralIsReadyToSendWriteWithoutResponse:
 *
 *  @param peripheral   The peripheral providing this update.
 *
 *  @discussion         This method is invoked after a failed call to @link writeValue:forCharacteristic:type: @/link, when <i>peripheral</i> is again
 *                      ready to send characteristic value updates.
 *
 */
- (void)peripheralIsReadyToSendWriteWithoutResponse:(CBPeripheral *)peripheral;

/*!
 *  @method peripheral:didOpenL2CAPChannel:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param channel			A <code>CBL2CAPChannel</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a @link openL2CAPChannel: @link call.
 */
- (void)peripheral:(CBPeripheral *)peripheral didOpenL2CAPChannel:(nullable CBL2CAPChannel *)channel error:(nullable NSError *)error;


@end

NS_ASSUME_NONNULL_END
