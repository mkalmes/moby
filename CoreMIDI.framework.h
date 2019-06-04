// ==========  CoreMIDI.framework/Headers/MIDIDriver.h
/*
     File:       CoreMIDI/MIDIDriver.h
 
     Contains:   MIDI Services driver interfaces
 
 	Copyright:  (c) 2000-2015 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/

#ifndef __MIDIDriver_h__
#define __MIDIDriver_h__

#include <CoreFoundation/CFPlugIn.h>
#if COREFOUNDATION_CFPLUGINCOM_SEPARATE
#include <CoreFoundation/CFPlugInCOM.h>
#endif
#include <CoreFoundation/CFRunLoop.h>
#include <CoreMIDI/CoreMIDI.h>

CF_ASSUME_NONNULL_BEGIN

/*!
	@header MIDIDriver.h
	
	This is the header file for Mac OS X's MIDI driver interface.
	

	MIDI drivers are CFPlugIns, installed into the following places:
<pre>
    /System/Library/Extensions      -- not recommended for non-Apple drivers, but
                                    necessary for compatibility with CoreMIDI 1.0
    
    /Library/Audio/MIDI Drivers     -- starting with CoreMIDI 1.1
    
    ~/Library/Audio/MIDI Drivers    -- starting with CoreMIDI 1.1
</pre>
	Refer to the CFPlugIn documentation for more information about plug-ins.
	

	A driver's bundle settings should include settings resembling the following:
<pre>
    Bundle settings:
        CFBundleIdentifier              String          com.mycompany.midi.driver.mydevice
            (note that this will be the driver's persistent ID in MIDISetup's)
        CFPlugInDynamicRegistration     String          NO
        CFPlugInFactories               Dictionary      1 key/value pair
            [your new factory UUID]     String          [your factory function name]
        CFPlugInTypes                   Dictionary      1 key/value pair
            ECDE9574-0FE4-11D4-BB1A-0050E4CEA526        Array       1 object
                (this is kMIDIDriverTypeID)
                0                       String          [your new factory UUID]
    Build settings:
        WRAPPER_EXTENSION               plugin
</pre>
	

	Drivers have access to most of the CoreMIDI API.  Starting in Mac OS X 10.6, drivers should link
	with CoreMIDI.framework. In previous versions of Mac OS X, drivers should link with
	CoreMIDIServer.framework, not CoreMIDI.framework.
	
	On Mac OS X versions prior to 10.6, MIDI driver plugins linked against the CoreMIDIServer
	framework in order to access the CoreMIDI API. Drivers which are to run on earlier OS versions
	should be built 32-bit fat (ppc and i386) and link against CoreMIDIServer. Drivers which are to
	run on Mac OS X 10.6 and later should be built for x86_64 and link against the CoreMIDI
	framework. Drivers which are to run on all versions of Mac OS X should be build 3-way fat (ppc,
	i386, and x86_64), with the ppc and i386 slices linking against CoreMIDIServer, and the x86_64
	slice linking against CoreMIDI.

	Unlike applications, drivers communicate with the server directly, not through Mach messaging. 
	This necessitates some limitations on the contexts from which a driver may call the server.
	
	The MIDI I/O functions MIDISend and MIDIReceived may be called from any thread.
	
	All other CoreMIDI functions must only be called from the server's main thread, which is the
	thread on which the driver is created and from which all calls to the driver other than Send()
	are made.
*/

typedef struct MIDIDriverInterface		MIDIDriverInterface;

/*!
	@typedef		MIDIDriverRef
	
	@discussion		Points to a pointer to a MIDIDriverInterface, a CFPlugIn structure (defined in
					MIDIDriver.h) containing function pointers for the driver's methods.  Only the
					MIDIServer may call a driver's methods.
*/
typedef MIDIDriverInterface * __nonnull * MIDIDriverRef;

/*!
	@typedef		MIDIDeviceListRef
	
	@discussion		A MIDIDeviceListRef is a list of MIDIDeviceRef's.  The devices are not owned by
					the list (i.e., disposing the list does not dispose the devices it references).
*/
typedef MIDIObjectRef MIDIDeviceListRef;

/*!
	@interface		MIDIDriverInterface
	
	@abstract		The COM-style interface to a MIDI driver.
	
	@discussion
		This is the function table interface to a MIDI driver.  Both version 1 and 2 drivers use
		this same table of function pointers (except as noted).

		Drivers which support both the version 1 and version 2 interfaces can tell which version
		of the server is running by checking to see whether kMIDIDriverInterface2ID or
		kMIDIDriverInterfaceID is passed to the factory function.  If the version 1 interface is
		requested, the driver should behave as if it is a version 1 driver.
*/
struct MIDIDriverInterface
{
	IUNKNOWN_C_GUTS;

	/*!
		@function FindDevices
		@discussion
			This is only called for version 1 drivers.  The server is requesting that the driver
			detect the devices which are present.  For each device present, the driver should
			create a MIDIDeviceRef with entities, using MIDIDeviceCreate and
			MIDIDeviceAddEntity, and add the device to the supplied MIDIDeviceListRef, using
			MIDIDeviceListAddDevice.

			The driver should not retain any references to the created devices and entities.
	*/	
	OSStatus	(*FindDevices)(MIDIDriverRef __nonnull self, MIDIDeviceListRef devList);

	/*!
		@function Start
		@discussion
			The server is telling the driver to begin MIDI I/O.

			The provided device list contains the devices which were previously located by
			FindDevices (in the case of a version 1 driver), or the devices which are owned by
			this driver and are currently in the current MIDISetup (for version 2 drivers).

			The provided devices may or may not still be present.  A version 1 driver should
			attempt to use as many of the devices as are actually present.

			A version 2 driver may make calls such as MIDISetupAddDevice, MIDIDeviceAddEntity,
			MIDIDeviceRemoveEntity to dynamically modify the system's current state. For devices
			in the provided device list which are not present, the driver should set their
			kMIDIPropertyOffline property to 1.  A version 2 driver may also set up
			notifications when the IORegistry changes, to detect connection and disconnection of
			devices it wishes to control.  At these times also, the driver may change the
			devices' kMIDIPropertyOffline, and dynamically modify the system's current state to
			reflect the devices which are present.  When passing a CFRunLoopRef to IOKit for
			notification purposes, the driver must use the server's main runloop, which is
			obtained with CFRunLoopGetCurrent().

			The driver will probably want to iterate through the destination endpoints and
			assign their driver refCons, so as to identify multiple destinations when Send() is
			called.

			The provided device list remains owned by the system and can be assumed to contain
			only devices owned by this driver.  The driver may retain references to the devices
			in this list and any it creates while running.
	*/					
	OSStatus	(*Start)(MIDIDriverRef __nonnull self, MIDIDeviceListRef devList);

	/*!
		@function Stop
		@discussion
			The server is telling the driver to terminate MIDI I/O.  All I/O operations that
			were begun in Start, or as a result of a subsequent IOKit notification, should be
			terminated.
	*/
	OSStatus	(*Stop)(MIDIDriverRef __nonnull self);
	
	/*!
		@function Configure
		@discussion
			not currently used
	*/
	OSStatus	(*Configure)(MIDIDriverRef __nonnull self, MIDIDeviceRef device);

	/*!
		@function Send
		@discussion
			Send a MIDIPacketList to the destination endpoint whose refCons are being passed as
			arguments.
	*/
	OSStatus	(*Send)(MIDIDriverRef __nonnull self, const MIDIPacketList *pktlist, void *destRefCon1, void *destRefCon2);
	
	/*!
		@function EnableSource
		@discussion
			A client has opened or closed a connection, and now the server is telling the driver
			that input from a particular source either does or does not have any listeners in
			the system.  The driver may use this information to decide whether to pass messages
			from the source to the server, and it may even be able to tell the source hardware
			not to generate incoming MIDI I/O for that source.
	*/
	OSStatus	(*EnableSource)(MIDIDriverRef __nonnull self, MIDIEndpointRef src, Boolean enabled);
	
	/*!
		@function Flush
		@discussion
			Only for version 2 drivers (new for CoreMIDI 1.1).

			Drivers which support schedule-ahead, when receiving this message, should unschedule
			all pending output to the specified destination.  If the destination is null/0, the
			driver should unschedule all pending output to all destinations.
	*/
	OSStatus	(*Flush)(MIDIDriverRef __nonnull self, MIDIEndpointRef dest, void * __nullable destRefCon1, void * __nullable destRefCon2);

	/*!
		@function Monitor		
		@discussion
			Only for version 2 drivers (new for CoreMIDI 1.1).

			Some specialized drivers (e.g. a MIDI monitor display) may wish to intercept and
			look at all outgoing MIDI messages.  After a driver calls
			MIDIDriverEnableMonitoring(true) on itself, this function is called with the
			outgoing MIDI packets for all destinations in the system.  The Monitor function
			cannot rely on the MIDI events arriving in order, due to MIDIServer's schedule-ahead
			facilities.
	*/
	OSStatus	(*Monitor)(MIDIDriverRef __nonnull self, MIDIEndpointRef dest, const MIDIPacketList *pktlist);
};


//  -----------------------------------------------------------------------------
/*!
	@define			kMIDIDriverTypeID
	
	@abstract		The UUID for MIDI driver plugins.
	
	@discussion		kMIDIDriverTypeID should be entered into your driver's bundle settings
					as follows:
					
<pre>
CFPlugInTypes                   Dictionary      1 key/value pair
	ECDE9574-0FE4-11D4-BB1A-0050E4CEA526        Array       1 object
		(this is kMIDIDriverTypeID)
		0                       String          [your new factory UUID]
</pre>
*/
#define kMIDIDriverTypeID \
	CFUUIDGetConstantUUIDWithBytes(NULL, 0xEC, 0xDE, 0x95, 0x74, 0x0F, 0xE4, 0x11, 0xD4, 0xBB, 0x1A, 0x00, 0x50, 0xE4, 0xCE, 0xA5, 0x26)
/* ECDE9574-0FE4-11D4-BB1A-0050E4CEA526 */


/*!
	@define			kMIDIDriverInterfaceID
	
	@abstract		The UUID for version 1 of the MIDI driver interface.
	
	@discussion		See the description of the MIDIDriverInterface structure for
					information about different versions of the MIDI driver interface.
*/
#define kMIDIDriverInterfaceID \
	CFUUIDGetConstantUUIDWithBytes(NULL, 0x49, 0xDF, 0xCA, 0x9E, 0x0F, 0xE5, 0x11, 0xD4, 0x95, 0x0D, 0x00, 0x50, 0xE4, 0xCE, 0xA5, 0x26)
/* 49DFCA9E-0FE5-11D4-950D-0050E4CEA526 */

/*!
	@define			kMIDIDriverInterface2ID
	
	@abstract		The UUID for version 2 of the MIDI driver interface.
	
	@discussion		See the description of the MIDIDriverInterface structure for
					information about different versions of the MIDI driver interface.
					
					The version 2 driver interface is available beginning with CoreMIDI 1.1.
*/
#define kMIDIDriverInterface2ID \
	CFUUIDGetConstantUUIDWithBytes(NULL, 0x43, 0xC9, 0x8C, 0x3C, 0x30, 0x6C, 0x11, 0xD5, 0xAF, 0x73, 0x00, 0x30, 0x65, 0xA8, 0x30, 0x1E)
/* 43C98C3C-306C-11D5-AF73-003065A8301E */

/*!
	@constant		kMIDIDriverPropertyUsesSerial
	
	@discussion		This constant, "MIDIDriverUsesSerial", when defined to "YES" in a driver's 
					bundle, tells MIDIServer that the driver uses serial ports and is eligible to
					have serial ports assigned to it.
					
					When a serial driver's Start() method is called, it should use
					MIDIGetSerialPortOwner to discover which serial ports it has
					been assigned to use, and only use those ports.
					
					New for CoreMIDI 1.1.
*/
extern const CFStringRef kMIDIDriverPropertyUsesSerial		API_AVAILABLE(macos(10.1)) API_UNAVAILABLE(ios, tvos);


#ifdef __cplusplus
extern "C" {
#endif

// ___________________________________________________________________________________________
//	MIDIDevice
// ___________________________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIDeviceCreate

	@discussion		Drivers call this function to create new MIDIDevice objects
					corresponding to the hardware that is present.
					
					Non-drivers may call this function as of CoreMIDI 1.1, to
					create external devices.
	
	@param			owner
						The driver creating the device.  NULL if a non-driver.
	@param			name
						The name of the new device.
	@param			manufacturer
						The name of the device's manufacturer.
	@param			model
						The device's model name.
	@param			outDevice
						On successful return, points to the newly-created device.
	@result			An OSStatus result code.
*/
extern OSStatus		MIDIDeviceCreate(MIDIDriverRef __nullable owner,
							CFStringRef name, CFStringRef manufacturer, 
							CFStringRef model, MIDIDeviceRef *outDevice)
																API_AVAILABLE(macos(10.0), ios(4.2));


/*!
	@function		MIDIDeviceDispose

	@discussion		Drivers may call this function to dispose MIDIDevice objects
					which have not yet been added to the system via MIDISetupAddDevice.
					Once a device has been added to the system with MIDISetupAddDevice,
					the driver must not use this call to destroy it; it must
					use MIDISetupRemoveDevice to do so.
					
					Non-drivers do not have access to this function; they must call
					MIDISetupAddDevice and MIDISetupRemoveDevice.
	
	@param			device
						The device to be disposed.
	@result			An OSStatus result code.
*/
extern OSStatus		MIDIDeviceDispose(MIDIDeviceRef device)		API_AVAILABLE(macos(10.3), ios(4.2));

// ___________________________________________________________________________________________
//	MIDIDeviceList
// ___________________________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIDeviceListGetNumberOfDevices

	@discussion		Returns the number of devices in a device list.
	
	@param			devList
						The device list.
	@result			The number of devices in the list, or 0 if an error occurred.
*/
extern ItemCount		MIDIDeviceListGetNumberOfDevices(MIDIDeviceListRef devList)
																API_AVAILABLE(macos(10.0), ios(4.2));

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIDeviceListGetDevice

	@discussion		Return one of the devices in a device list.
	
	@param			devList
						The device list.
	@param			index0
						The index (0...MIDIDeviceListGetNumberOfDevices()-1) of the device
						to return.
	@result			A reference to a device, or NULL if an error occurred.
*/
extern MIDIDeviceRef	MIDIDeviceListGetDevice(MIDIDeviceListRef devList, ItemCount index0)
																API_AVAILABLE(macos(10.0), ios(4.2));

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIDeviceListAddDevice

	@discussion		Add a device to a device list.
	
	@param			devList
						The device list.
	@param			dev
						The device to add to the list.
	@result			An OSStatus result code.
*/
extern OSStatus		MIDIDeviceListAddDevice(MIDIDeviceListRef devList, MIDIDeviceRef dev)
																API_AVAILABLE(macos(10.0), ios(4.2));

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIDeviceListDispose

	@discussion		Dispose a device list, but not the contained devices.
	
	@param			devList
						The device list to be disposed.
	@result			An OSStatus result code.
*/
extern OSStatus		MIDIDeviceListDispose(MIDIDeviceListRef devList)
																API_AVAILABLE(macos(10.1), ios(4.2));


// ___________________________________________________________________________________________
//	MIDIEndpoint
// ___________________________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIEndpointSetRefCons

	@discussion		Drivers need an efficient way to translate from a MIDIEndpoint (source or
					destination) to their own internal data structures corresponding to
					that endpoint.  This function provides a way for the driver to
					assign its own refCons to endpoints.
					
					These refCons are passed back to the driver in its Send() and Flush()
					methods.
					
					RefCons are not persistent (i.e. they are not saved as part of a 
					MIDISetup).  They need to be re-initialized in each call to Start().
					
					A typical use is to use one refCon to refer to a device, and a second
					to refer to a port on the device.
	
	@param			endpt
						The endpoint whose refCons are to be set
	@param			ref1
						The first refCon.
	@param			ref2
						The second refCon.
	@result			An OSStatus result code.
*/
extern OSStatus		MIDIEndpointSetRefCons(MIDIEndpointRef endpt,
					void * __nullable ref1, void * __nullable ref2)					API_AVAILABLE(macos(10.0), ios(4.2));

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIEndpointGetRefCons

	@discussion		Obtain the refCons assigned to the endpoints 
	
	@param			endpt
						The endpoint whose refCons are to be return
	@param			ref1
						On exit, the first refCon.
	@param			ref2
						On exit, the second refCon.
	@result			An OSStatus result code.
*/
extern OSStatus		MIDIEndpointGetRefCons(MIDIEndpointRef endpt, 
					void * __nonnull * __nullable ref1, void * __nonnull * __nullable ref2)
																					API_AVAILABLE(macos(10.0), ios(4.2));

// ___________________________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIGetDriverIORunLoop

	@discussion		Drivers typically need to receive asynchronous I/O completion callbacks
					on a high-priority thread.  To save drivers from the trouble of 
					creating their own threads for this purpose, and to make efficient
					use of system resources, the MIDIServer provides a thread which
					drivers may use.
					
					Drivers should do as little work as possible in this thread; typically,
					just dequeueing and encoding output packets, and decoding input packets
					into MIDIPacketLists to be passed to MIDIReceived.
	
					This is a realtime-priority thread and shouldn't be used for anything other 
					than I/O.  For lower-priority tasks, drivers can use the runloop which 
					was current when they were constructed.

	@result			The CFRunLoopRef of the server's driver I/O thread.
*/
extern CFRunLoopRef	MIDIGetDriverIORunLoop(void)			API_AVAILABLE(macos(10.0), ios(4.2));

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIGetDriverDeviceList

	@discussion		Returns the list of devices which are in the current MIDISetup
					and which were created/owned by the specified driver.
	
					The returned device list should be disposed (using MIDIDeviceListDispose)
					by the caller.
					
	@param			driver
						The driver whose devices are to be returned.

	@result			The requested device list.
*/
extern MIDIDeviceListRef	MIDIGetDriverDeviceList(MIDIDriverRef __nonnull driver)
															API_AVAILABLE(macos(10.1), ios(4.2));

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIDriverEnableMonitoring

	@discussion		A driver may make this call to have MIDIServer pass it every outgoing MIDI
					packet, to all destinations in the system (not just those controlled by
					itself).
					
	@param			driver
						The driver whose Monitor function is to be enabled.
	@param			enabled
						true to enable monitoring, false to disable it.

	@result			An OSStatus result code.
*/
extern OSStatus			MIDIDriverEnableMonitoring(MIDIDriverRef __nonnull driver, Boolean enabled)
															API_AVAILABLE(macos(10.1)) API_UNAVAILABLE(ios, tvos);


#ifdef __cplusplus
}
#endif

CF_ASSUME_NONNULL_END

#endif // __MIDIDriver_h__
// ==========  CoreMIDI.framework/Headers/MIDISetup.h
/*
 	File:   	CoreMIDI/MIDISetup.h
 
 	Contains:   Specialized configuration-editing routines for CoreMIDI.
 
 	Copyright:  (c) 2000-2015 by Apple Inc., all rights reserved.
 
 	Bugs?:  	For bug reports, consult the following page on
 				the World Wide Web:
 
 					http://developer.apple.com/bugreporter/
 
*/

#ifndef __MIDISetup_h__
#define __MIDISetup_h__

#ifndef __MIDIServices_h__
#include <CoreMIDI/MIDIServices.h>
#endif


//  -----------------------------------------------------------------------------
/*!
	@header MIDISetup.h

	This header defines functions that manipulate and customize the global
	state of the MIDI system.  These functions are generally only needed by 
	applications which wish to allow the user some flexibility in how
	the MIDI system's state is presented, and by MIDI drivers, which may
	dynamically modify the system state as hardware is connected and 
	disconnected.
*/

CF_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

//  -----------------------------------------------------------------------------
/*!
	@typedef		MIDISetupRef
	
	@discussion		Derives from MIDIObjectRef, does not have an owner object.

					This represents the global state of the MIDI system,
					containing lists of the MIDI devices and serial port
					owners.
					
					Generally, only MIDI drivers and specialized configuration
					editors will need to manipulate MIDISetup objects, not the
					average MIDI client application.  As of CoreMIDI 1.1, the
					MIDIServer maintains a single global MIDISetupRef, stored
					persistently in a preference file.
*/
typedef MIDIObjectRef MIDISetupRef;

// ______________________________________________________________________________
//	MIDISetup
// ______________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDISetupCreate

	@abstract 		Interrogates drivers, to discover what hardware is present.
	
					As of CoreMIDI 1.1, it is usually not necessary to call
					this function, as CoreMIDI manages a single persistent
					MIDISetup itself.

	@param			outSetup
						On successful return, points to a newly-created MIDISetup
						object.  The caller is responsible for disposing it,
						or transferring ownership of the object back to the
						system, with MIDISetupInstall.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDISetupCreate(	MIDISetupRef *outSetup )					API_DEPRECATED("No longer supported", macos(10.0, 10.6)) API_UNAVAILABLE(ios, tvos);


//  -----------------------------------------------------------------------------
/*!
	@function		MIDISetupDispose

	@abstract 		Dispose a MIDISetup object.

					As of CoreMIDI 1.1, it is usually not necessary to call
					this function, as CoreMIDI manages a single persistent
					MIDISetup itself.
	
	@param			setup
						The MIDISetup to be disposed.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDISetupDispose(	MIDISetupRef setup )						API_DEPRECATED("No longer supported", macos(10.0, 10.6)) API_UNAVAILABLE(ios, tvos);

//  -----------------------------------------------------------------------------
/*!
	@function		MIDISetupInstall

	@abstract 		Install a MIDISetup as the system's current state.

					A client can create a MIDISetup object using
					MIDISetupCreate, or MIDISetupFromData.  This function will
					install this state as the current state of the system,
					possibly changing the devices visible to clients.

					As of CoreMIDI 1.1, it is usually not necessary to call
					this function, as CoreMIDI manages a single persistent
					MIDISetup itself.

	@param			setup
						The MIDISetup object to install.  Ownership of this
						object is transferred from the client to the system; the
						client must <b>not</b> dispose of this MIDISetup.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDISetupInstall(	MIDISetupRef setup )						API_DEPRECATED("No longer supported", macos(10.0, 10.6)) API_UNAVAILABLE(ios, tvos);


//  -----------------------------------------------------------------------------
/*!
	@function		MIDISetupGetCurrent

	@abstract 		Return the system's current MIDISetup.
	
					As of CoreMIDI 1.1, it is usually not necessary to call
					this function, as CoreMIDI manages a single persistent
					MIDISetup itself.
	
	@param			outSetup
						On successful return, points to the system's most
						recently installed MIDISetup.  The system retains
						ownership of the object; the client must <b>not</b>
						dispose of this MIDISetup.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDISetupGetCurrent(	MIDISetupRef *outSetup )				API_DEPRECATED("No longer supported", macos(10.0, 10.6)) API_UNAVAILABLE(ios, tvos);


//  -----------------------------------------------------------------------------
/*!
	@function		MIDISetupToData

	@abstract 		Create an XML representation of a MIDISetup object.
	
					As of CoreMIDI 1.1, it is usually not necessary to call
					this function, as CoreMIDI manages a single persistent
					MIDISetup itself.
	
	@param			setup
						The MIDISetup object whose XML representation is to be
						returned.
	@param			outData
						On successful return, points to a newly-created CFDataRef
						containing the XML text.  The client is responsible for
						releasing this CFData object when done with it.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDISetupToData(	MIDISetupRef	setup,
					CFDataRef __nullable * __nonnull outData )	API_DEPRECATED("No longer supported", macos(10.0, 10.6)) API_UNAVAILABLE(ios, tvos);

//  -----------------------------------------------------------------------------
/*!
	@function		MIDISetupFromData

	@abstract 		Create a MIDISetup object from an XML stream.
	
					As of CoreMIDI 1.1, it is usually not necessary to call
					this function, as CoreMIDI manages a single persistent
					MIDISetup itself.
	
	@param			data
						The XML text from which a MIDISetup object is to be built.
	@param			outSetup
						On successful return, points to a newly-created MIDISetup
						object.  The caller is responsible for disposing it, or
						transferring ownership of the object back to the system,
						with MIDISetupInstall.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDISetupFromData(	CFDataRef 		data, 
					MIDISetupRef *	outSetup)					API_DEPRECATED("No longer supported", macos(10.0, 10.6)) API_UNAVAILABLE(ios, tvos);

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIDeviceAddEntity

	@discussion		Drivers call this function to specify one of the entities that 
					comprise a device.
					
					Non-drivers may call this function as of CoreMIDI 1.1, to
					add entities to external devices.
	
	@param			device
						The device to which an entity is to be added.
	@param			name
						The name of the new entity.
	@param			embedded
						True if this entity is inside the device, false if the
						entity simply consists of external connectors to which
						other devices can be attached.
	@param			numSourceEndpoints
						The number of source endpoints the entity has.
	@param			numDestinationEndpoints
						The number of destination endpoints the entity has.
	@param			newEntity
						On successful return, points to the newly-created entity.
	@result			An OSStatus result code.
*/
extern OSStatus		
MIDIDeviceAddEntity(MIDIDeviceRef device, CFStringRef name, 
					Boolean embedded, ItemCount numSourceEndpoints,
					ItemCount numDestinationEndpoints, MIDIEntityRef *newEntity)
																API_AVAILABLE(macos(10.0), ios(4.2));

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIDeviceRemoveEntity

	@discussion		Drivers may call this function to remove one of a device's
					entities.
					
					New for CoreMIDI 1.1.
	
	@param			device
						The device from which an entity is to be removed.
	@param			entity
						The entity to be removed.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIDeviceRemoveEntity(MIDIDeviceRef device, MIDIEntityRef entity)
																API_AVAILABLE(macos(10.1), ios(4.2));

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIEntityAddOrRemoveEndpoints

	@discussion		Drivers and configuration editors may call this function to add to 
					or remove an entity's endpoints.
					
					New for CoreMIDI 1.3.
	
	@param			entity
						The entity whose endpoints are to be manipulated.
	@param			numSourceEndpoints
						The desired new number of source endpoints.
	@param			numDestinationEndpoints
						The desired new number of destination endpoints.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIEntityAddOrRemoveEndpoints(MIDIEntityRef entity, ItemCount numSourceEndpoints,
					ItemCount numDestinationEndpoints)			API_AVAILABLE(macos(10.2), ios(4.2));

//  -----------------------------------------------------------------------------
/*!
	@function		MIDISetupAddDevice

	@abstract 		Adds a driver-owner MIDI device to the current MIDISetup
	
	@discussion		Only MIDI drivers may make this call; it is in this header
					file only for consistency with MIDISetupRemoveDevice.
	
					New for CoreMIDI 1.1.
	
	@param			device
						The device to be added.
*/
extern OSStatus
MIDISetupAddDevice(		MIDIDeviceRef device )					API_AVAILABLE(macos(10.1), ios(4.2));

//  -----------------------------------------------------------------------------
/*!
	@function		MIDISetupRemoveDevice

	@abstract 		Removes a driver-owned MIDI device from the current MIDISetup
	
	@discussion		Generally this should only be called from a studio configuration
					editor, to remove a device which is offline and which the user
					has specified as being permanently missing.
					
					Instead of removing devices from the setup, drivers should
					set the device's kMIDIPropertyOffline to 1 so that if the
					device reappears later, none of its properties are lost.
	
					New for CoreMIDI 1.1.
	
	@param			device
						The device to be added.
*/
extern OSStatus
MIDISetupRemoveDevice(	MIDIDeviceRef device )				API_AVAILABLE(macos(10.1), ios(4.2));

//  -----------------------------------------------------------------------------
/*!
	@function		MIDISetupAddExternalDevice

	@abstract 		Adds an external MIDI device to the current MIDISetup
	
	@discussion		Useful for a studio configuration editor.  New for CoreMIDI 1.1.
	
	@param			device
						The device to be added.
*/
extern OSStatus
MIDISetupAddExternalDevice(	MIDIDeviceRef device )			API_AVAILABLE(macos(10.1), ios(4.2));

//  -----------------------------------------------------------------------------
/*!
	@function		MIDISetupRemoveExternalDevice

	@abstract 		Removes an external MIDI device from the current MIDISetup
	
	@discussion		Useful for a studio configuration editor.  New for CoreMIDI 1.1.
	
	@param			device
						The device to be removed.
*/
extern OSStatus
MIDISetupRemoveExternalDevice( MIDIDeviceRef device )		API_AVAILABLE(macos(10.1), ios(4.2));

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIGetSerialPortOwner

	@abstract 		Returns the MIDI driver that owns a serial port.
	
	@discussion		The current MIDISetup tracks ownership of serial ports
					to one of the MIDI drivers installed in the system.
	
					Serial ports can be enumerated using IOServiceMatching(
					kIOSerialBSDServiceValue).  The port's unique name is
					the IOService's kIOTTYDeviceKey property. 

					New for CoreMIDI 1.1.
					
					A previous version of this documentation specified an incorrect
					key for obtaining the port's unique name (IOTTYBaseName).
	
	@param			portName
						The name of a serial port.
	@param			outDriverName
						On exit, the name of the driver owning the port,
						or NULL if no driver owns it.

	@result			An OSStatus result code.	
*/
extern OSStatus
MIDIGetSerialPortOwner(	CFStringRef			portName, 
						CFStringRef __nullable * __nonnull outDriverName )	API_DEPRECATED("No longer supported", macos(10.1, 10.6)) API_UNAVAILABLE(ios, tvos);

//  -----------------------------------------------------------------------------
/*!
	@function		MIDISetSerialPortOwner

	@abstract 		Specifies the MIDI driver that owns a serial port.
	
	@discussion		Use this to assign ownership of a serial port
					to one of the MIDI drivers installed in the system.
	
					New for CoreMIDI 1.1.
	
	@param			portName
						The name of a serial port.
	@param			driverName
						The name of the driver that owns the serial port,
						or NULL to specify that no driver owns it.

	@result			An OSStatus result code.	
*/
extern OSStatus
MIDISetSerialPortOwner(	CFStringRef			portName, 
						CFStringRef			driverName )	API_DEPRECATED("No longer supported", macos(10.1, 10.6)) API_UNAVAILABLE(ios, tvos);

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIGetSerialPortDrivers

	@abstract 		Returns a list of installed MIDI drivers for serial port
					MIDI devices.
	
	@discussion		Use this to determine which of the installed MIDI drivers
					are for devices which may attach to serial ports.
	
					New for CoreMIDI 1.1.
	
	@param			outDriverNames
						On exit, a CFArrayRef containing a list of CFStringRef's
						which are the names of the serial port MIDI drivers.
						The array should be released by the caller.

	@result			An OSStatus result code.	
*/
extern OSStatus
MIDIGetSerialPortDrivers(	CFArrayRef __nullable * __nonnull outDriverNames )	API_DEPRECATED("No longer supported", macos(10.1, 10.6)) API_UNAVAILABLE(ios, tvos);

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIExternalDeviceCreate

	@abstract		Create a new external MIDI device.

	@discussion		Non-drivers may call this function as of CoreMIDI 1.1, to
					create external devices.

					The new device is not added to the current MIDISetupRef;
					to do this, use MIDISetupAddExternalDevice.
	
	@param			name
						The name of the new device.
	@param			manufacturer
						The name of the device's manufacturer.
	@param			model
						The device's model name.
	@param			outDevice
						On successful return, points to the newly-created device.
	@result			An OSStatus result code.
*/
extern OSStatus		
MIDIExternalDeviceCreate(CFStringRef name, CFStringRef manufacturer, 
							CFStringRef model, MIDIDeviceRef *outDevice)
															API_AVAILABLE(macos(10.1), ios(4.2));

#ifdef __cplusplus
}
#endif

CF_ASSUME_NONNULL_END

#endif /* __MIDISetup_h__ */
// ==========  CoreMIDI.framework/Headers/MIDIServices.h
/*
 	File:   	CoreMIDI/MIDIServices.h
 
 	Contains:   API for communicating with MIDI hardware
 
 	Copyright:  (c) 2000-2015 by Apple Inc., all rights reserved.
 
 	Bugs?:  	For bug reports, consult the following page on
 				the World Wide Web:
 
 					http://developer.apple.com/bugreporter/
 
*/

#ifndef __MIDIServices_h__
#define __MIDIServices_h__

/*!
	@header MIDIServices.h

	This is the header file for Mac OS X's MIDI system services.

<h2>API Overview</h2>
	Drivers own and control Devices, e.g. USB interfaces, PCI cards, etc.  A device is defined
	as a physical object that would be represented by a single icon if there were a graphical
	view of the studio.

	Devices may have multiple logically distinct sub-components, e.g. a MIDI synthesizer and a
	pair of MIDI ports, both addressable via a USB port. These are called Entities.

	Entities have any number of Endpoints, sources and destinations of 16-channel MIDI streams. 
	By grouping a device's endpoints into entities, the system has enough information for an
	application to make reasonable default assumptions about how to communicate in a
	bi-directional manner with each entity, as is necessary in MIDI librarian applications.

	CoreMIDI attaches a collection of properties to each object it manages. Some properties are
	dynamic characteristics of a device (e.g. MIDI receive channel and system-exclusive ID's),
	and some are a matter of user preference (choice of icon, whether the device should appear
	in lists of possible controllers). Other properties are static and could be looked up in a
	database, using the device's manufacturer and model names as a key.

<h2>Implementation overview</h2>
	The client API is implemented as the CoreMIDI framework, which uses IPC to communicate with
	a server process, MIDIServer.

	The server process loads, and manages all communication with, MIDI drivers.

	"Drivers" are not I/O Kit drivers.  They are bundles containing CFPlugins.

	Many MIDI drivers can simply be user-side I/O Kit clients (probably for serial, USB,
	Firewire).

	PCI card drivers will need their MIDI drivers to communicate with a separate kernel
	extension.

<h2>Note about CoreFoundation data types (CFString, CFData, CFDictionary)</h2>
	When passing a CF object to a MIDI function, the MIDI function will never consume a
	reference to the object; the caller always retains a reference which it is responsible for
	releasing with CFRelease().

	When receiving a CF object as a return value from a MIDI function, the caller always
	receives a new reference to the object, and is responsible for releasing it.
*/

//=============================================================================
#pragma mark    Includes

#include <Availability.h>
#include <CoreFoundation/CoreFoundation.h>
#include <stddef.h>

CF_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
#pragma mark	Error Constants
/*!
    @enum           Error Constants
    @abstract       The error constants unique to Core MIDI.
    @discussion     These are the error constants that are unique to Core MIDI. Note that Core MIDI
                    functions may return other codes that are not listed here.
	
	@constant		kMIDIInvalidClient
						An invalid MIDIClientRef was passed.
	@constant		kMIDIInvalidPort
						An invalid MIDIPortRef was passed.
	@constant		kMIDIWrongEndpointType
						A source endpoint was passed to a function expecting a destination, or vice versa.
	@constant		kMIDINoConnection
						Attempt to close a non-existant connection.
	@constant		kMIDIUnknownEndpoint
						An invalid MIDIEndpointRef was passed.
	@constant		kMIDIUnknownProperty
						Attempt to query a property not set on the object.
	@constant		kMIDIWrongPropertyType
						Attempt to set a property with a value not of the correct type.
	@constant		kMIDINoCurrentSetup
						Internal error; there is no current MIDI setup object.
	@constant		kMIDIMessageSendErr
						Communication with MIDIServer failed.
	@constant		kMIDIServerStartErr
						Unable to start MIDIServer.
	@constant		kMIDISetupFormatErr
						Unable to read the saved state.
	@constant		kMIDIWrongThread
						A driver is calling a non-I/O function in the server from a thread other than
						the server's main thread.
	@constant		kMIDIObjectNotFound
						The requested object does not exist.
	@constant		kMIDIIDNotUnique
						Attempt to set a non-unique kMIDIPropertyUniqueID on an object.
    @constant       kMIDINotPermitted
	                    The process does not have privileges for the requested operation.
	@constant       kMIDIUnknownError
 						Internal error; unable to perform the requested operation.

*/
CF_ENUM(OSStatus) {
	kMIDIInvalidClient		= -10830,
	kMIDIInvalidPort		= -10831,
	kMIDIWrongEndpointType	= -10832,
	kMIDINoConnection		= -10833,
	kMIDIUnknownEndpoint	= -10834,
	kMIDIUnknownProperty	= -10835,
	kMIDIWrongPropertyType	= -10836,
	kMIDINoCurrentSetup		= -10837,
	kMIDIMessageSendErr		= -10838,
	kMIDIServerStartErr		= -10839,
	kMIDISetupFormatErr		= -10840,
	kMIDIWrongThread		= -10841,
	kMIDIObjectNotFound		= -10842,
	kMIDIIDNotUnique		= -10843,
	kMIDINotPermitted       = -10844,
	kMIDIUnknownError		= -10845
};

//=============================================================================
#pragma mark	Types

/*!
	@typedef		MIDIObjectRef
	@abstract		The base class of many CoreMIDI objects.
	@discussion
		MIDIObject is the base class for many of the objects in CoreMIDI.  They have properties,
		and often an "owner" object, from which they inherit any properties they do not
		themselves have.

		Developers may add their own private properties, whose names must begin with their
		company's inverted domain name, as in Java package names, but with underscores instead
		of dots, e.g.: com_apple_APrivateAppleProperty
*/
typedef UInt32 MIDIObjectRef;

/*!
	@typedef		MIDIClientRef
	@abstract		An object maintaining per-client state.
	@discussion
		Derives from MIDIObjectRef, does not have an owner object.

		To use CoreMIDI, an application creates a MIDIClientRef, to which it can add
		MIDIPortRef's, through which it can send and receive MIDI.
*/
typedef MIDIObjectRef MIDIClientRef;

/*!
	@typedef		MIDIPortRef
	@abstract		A MIDI connection port owned by a client.
	@discussion
		Derives from MIDIObjectRef, owned by a MIDIClientRef.

		A MIDIPortRef, which may be an input port or output port, is an object through which a
		client may communicate with any number of MIDI sources or destinations.
*/
typedef MIDIObjectRef MIDIPortRef;

/*!
	@typedef		MIDIDeviceRef
	@abstract		A MIDI device or external device, containing entities.
	@discussion
		Derives from MIDIObjectRef, does not have an owner object.

		A MIDI device, which either attaches directly to the computer and is controlled by a
		MIDI driver, or which is "external," meaning that it is connected to a driver-controlled
		device via a standard MIDI cable.

		A MIDIDeviceRef has properties and contains MIDIEntityRef's.
*/
typedef MIDIObjectRef MIDIDeviceRef;

/*!
	@typedef		MIDIEntityRef
	@abstract		A MIDI entity, owned by a device, containing endpoints.
	@discussion
		Derives from MIDIObjectRef, owned by a MIDIDeviceRef.

		Devices may have multiple logically distinct sub-components, e.g. a MIDI synthesizer and
		a pair of MIDI ports, both addressable via a USB port.

		By grouping a device's endpoints into entities, the system has enough information for an
		application to make reasonable assumptions about how to communicate in a bi-directional
		manner with each entity, as is desirable in MIDI librarian applications.

		These sub-components are MIDIEntityRef's.
*/
typedef MIDIObjectRef MIDIEntityRef;

/*!
	@typedef		MIDIEndpointRef
	@abstract		A MIDI source or destination, owned by an entity.
	@discussion
		Derives from MIDIObjectRef, owned by a MIDIEntityRef, unless it is a virtual endpoint,
		in which case there is no owning entity.

		Entities have any number of MIDIEndpointRef's, sources and destinations of 16-channel
		MIDI streams.
*/
typedef MIDIObjectRef MIDIEndpointRef;

/*!
	@typedef		MIDITimeStamp
	@abstract		A host clock time.
	@discussion
		A host clock time representing the time of an event, as returned by
		mach_absolute_time() or UpTime().

		Since MIDI applications will tend to do a fair amount of math with the times of events,
		it's more convenient to use a UInt64 than an AbsoluteTime.
		
		See CoreAudio/HostTime.h.
*/
typedef UInt64							MIDITimeStamp;

/*!
	@enum			MIDIObjectType
	@abstract		Signifies the type of a MIDIObject.
	@discussion
		Signifies the real type of a MIDIObjectRef instance.
*/
typedef CF_ENUM(SInt32, MIDIObjectType) {
	kMIDIObjectType_Other				= -1,
	kMIDIObjectType_Device				= 0,
	kMIDIObjectType_Entity				= 1,
	kMIDIObjectType_Source				= 2,
	kMIDIObjectType_Destination			= 3,

	kMIDIObjectType_ExternalDevice		= 0x10 | kMIDIObjectType_Device,
	kMIDIObjectType_ExternalEntity		= 0x10 | kMIDIObjectType_Entity,
	kMIDIObjectType_ExternalSource		= 0x10 | kMIDIObjectType_Source,
	kMIDIObjectType_ExternalDestination	= 0x10 | kMIDIObjectType_Destination
};
static const MIDIObjectType kMIDIObjectType_ExternalMask		= (MIDIObjectType)0x10;

/*!
	@typedef		MIDIUniqueID
	@abstract		A unique identifier for a MIDIObjectRef.
	@discussion
		An integer which uniquely identifies a MIDIObjectRef.
*/
typedef SInt32							MIDIUniqueID;

CF_ENUM(MIDIUniqueID) {
	kMIDIInvalidUniqueID = 0
};


// forward structure declarations
typedef struct MIDIPacketList			MIDIPacketList;
typedef struct MIDISysexSendRequest		MIDISysexSendRequest;
typedef struct MIDINotification			MIDINotification;

//=============================================================================
#pragma mark	Callback Functions

/*!
	@typedef		MIDINotifyProc
	@abstract		A callback function for notifying clients of state changes.
	@discussion
		This callback function is called when some aspect of the current MIDI setup changes. It
		is called on the runloop (thread) on which MIDIClientCreate was first called.

	@param			message	
						A structure containing information about what changed.
	@param			refCon
						The client's refCon passed to MIDIClientCreate.
*/
typedef void
(*MIDINotifyProc)(const MIDINotification *message, void * __nullable refCon);

/*!
	@typedef		MIDINotifyBlock
	@abstract		A callback block for notifying clients of state changes.
	@discussion
		This block is called when some aspect of the current MIDI setup changes. It
		is called on an arbitrary thread chosen by the implementation; thread-safety
		is the responsibility of the block.

	@param			message	
						A structure containing information about what changed.
*/
typedef void
(^MIDINotifyBlock)(const MIDINotification *message);

/*!
	@typedef		MIDIReadProc
	@abstract		A function receiving MIDI input.
	@discussion
		This is a callback function through which a client receives incoming MIDI messages.

		A MIDIReadProc function pointer is passed to the MIDIInputPortCreate and
		MIDIDestinationCreate functions.  The CoreMIDI framework will create a high-priority
		receive thread on your client's behalf, and from that thread, your MIDIReadProc will be
		called when incoming MIDI messages arrive.

	@param			pktlist
						The incoming MIDI message(s).
	@param			readProcRefCon	
						The refCon you passed to MIDIInputPortCreate or
						MIDIDestinationCreate
	@param			srcConnRefCon
						A refCon you passed to MIDIPortConnectSource, which
						identifies the source of the data.
*/
typedef void
(*MIDIReadProc)(const MIDIPacketList *pktlist, void * __nullable readProcRefCon, void * __nullable srcConnRefCon);

/*!
	@typedef		MIDIReadBlock
	@abstract		A block receiving MIDI input.
	@discussion
		This is a callback block through which a client receives incoming MIDI messages.

		A MIDIReadBlock is passed to the MIDIInputPortCreateWithBlock and
		MIDIDestinationCreateWithBlock functions.  The CoreMIDI framework will create a
		high-priority receive thread on your client's behalf, and from that thread, your
		MIDIReadProc will be called when incoming MIDI messages arrive.

	@param			pktlist
						The incoming MIDI message(s).
	@param			srcConnRefCon
						A refCon you passed to MIDIPortConnectSource, which
						identifies the source of the data.
*/
typedef void
(^MIDIReadBlock)(const MIDIPacketList *pktlist, void * __nullable srcConnRefCon);

/*!
	@typedef		MIDICompletionProc
	@abstract		A function called when a system-exclusive event has been completely sent.
	@discussion
		Callback function to notify the client of the completion of a call to MIDISendSysex.
	
	@param			request
						The MIDISysexSendRequest which has completed, or been
						aborted.
*/
typedef void
(*MIDICompletionProc)(MIDISysexSendRequest *request);

//=============================================================================
#pragma mark	Structures

#pragma pack(push, 4)
/*!
	@struct			MIDIPacket
	@abstract		A collection of simultaneous MIDI events.
	
	@field			timeStamp
						The time at which the events occurred, if receiving MIDI,
						or, if sending MIDI, the time at which the events are to
						be played.  Zero means "now."  The time stamp applies
						to the first MIDI byte in the packet.
	@field			length		
						The number of valid MIDI bytes which follow, in data. (It
						may be larger than 256 bytes if the packet is dynamically
						allocated.)
	@field			data
						A variable-length stream of MIDI messages.  Running status
						is not allowed.  In the case of system-exclusive
						messages, a packet may only contain a single message, or
						portion of one, with no other MIDI events.
						
						The MIDI messages in the packet must always be complete,
						except for system-exclusive.

						(This is declared to be 256 bytes in length so clients
						don't have to create custom data structures in simple
						situations.)
*/
struct MIDIPacket
{
	MIDITimeStamp		timeStamp;
	UInt16				length;
	Byte				data[256];
};
typedef struct MIDIPacket			MIDIPacket;

/*!
	@struct			MIDIPacketList
	@abstract		A list of MIDI events being received from, or being sent to,
					one endpoint.
	@discussion
					The timestamps in the packet list must be in ascending order.
					
					Note that the packets in the list, while defined as an array, may not be
					accessed as an array, since they are variable-length.  To iterate through
					the packets in a packet list, use a loop such as:
<pre>
@textblock
  MIDIPacket *packet = &packetList->packet[0];
  for (int i = 0; i < packetList->numPackets; ++i) {
    ...
    packet = MIDIPacketNext(packet);
  }
@/textblock
</pre>
	
					The MIDIPacketNext macro is especially important when considering that
					the alignment requirements of MIDIPacket may differ between CPU architectures.
					On Intel and PowerPC, MIDIPacket is unaligned. On ARM, MIDIPacket must be
					4-byte aligned.
	
	@field			numPackets
						The number of MIDIPackets in the list.
	@field			packet
						An open-ended array of variable-length MIDIPackets.
*/
struct MIDIPacketList
{
	UInt32  			numPackets;	
	MIDIPacket  		packet[1];
};
#pragma pack(pop)

/*!
	@struct			MIDISysexSendRequest
	@abstract		A request to transmit a system-exclusive event.
	
	@field			destination
						The endpoint to which the event is to be sent.
	@field			data
						Initially, a pointer to the sys-ex event to be sent.
						MIDISendSysex will advance this pointer as bytes are
						sent.
	@field			bytesToSend
						Initially, the number of bytes to be sent.  MIDISendSysex
						will decrement this counter as bytes are sent.
	@field			complete
						The client may set this to true at any time to abort
						transmission.  The implementation sets this to true when
						all bytes have been sent.
	@field			completionProc
						Called when all bytes have been sent, or after the client
						has set complete to true.
	@field			completionRefCon
						Passed as a refCon to completionProc.

	@discussion
		This represents a request to send a single system-exclusive MIDI event to
		a MIDI destination asynchronously.
*/
struct MIDISysexSendRequest
{
	MIDIEndpointRef		destination;
	const Byte *  		data;
	UInt32				bytesToSend;
	Boolean				complete;
	Byte				reserved[3];
	MIDICompletionProc 	completionProc;
	void * __nullable	completionRefCon;
};

/*!
	@enum		MIDINotificationMessageID
	@abstract	Signifies the type of a MIDINotification.

	@constant	kMIDIMsgSetupChanged	Some aspect of the current MIDISetup
										has changed.  No data.  Should ignore this
										message if messages 2-6 are handled.
	@constant	kMIDIMsgObjectAdded		A device, entity or endpoint was added.
										Structure is MIDIObjectAddRemoveNotification.
										New in Mac OS X 10.2.
	@constant	kMIDIMsgObjectRemoved	A device, entity or endpoint was removed.
										Structure is MIDIObjectAddRemoveNotification.
										New in Mac OS X 10.2.
	@constant	kMIDIMsgPropertyChanged	An object's property was changed.
										Structure is MIDIObjectPropertyChangeNotification.
										New in Mac OS X 10.2.
	@constant	kMIDIMsgThruConnectionsChanged	A persistent MIDI Thru connection was created
										or destroyed.  No data.  New in Mac OS X 10.2.
	@constant	kMIDIMsgSerialPortOwnerChanged	A persistent MIDI Thru connection was created
										or destroyed.  No data.  New in Mac OS X 10.2.
	@constant	kMIDIMsgIOError			A driver I/O error occurred.
*/
typedef CF_ENUM(SInt32, MIDINotificationMessageID) {
	kMIDIMsgSetupChanged			= 1,
	kMIDIMsgObjectAdded				= 2,
	kMIDIMsgObjectRemoved			= 3,
	kMIDIMsgPropertyChanged			= 4,
	kMIDIMsgThruConnectionsChanged	= 5,
	kMIDIMsgSerialPortOwnerChanged	= 6, 
	kMIDIMsgIOError					= 7
};


/*!
	@struct			MIDINotification
	@abstract		A message describing a system state change.
	@discussion
		A MIDINotification is a structure passed to a MIDINotifyProc or MIDINotifyBlock, when
		CoreMIDI wishes to inform a client of a change in the state of the system.
	
	@field			messageID
						type of message
	@field			messageSize
						size of the entire message, including messageID and
						messageSize
*/
struct MIDINotification
{
	MIDINotificationMessageID	messageID;
	UInt32						messageSize;
	// additional data may follow, depending on messageID
};

/*!
	@struct			MIDIObjectAddRemoveNotification
	@abstract		A message describing the addition or removal of an object.
	
	@field			messageID
						type of message
	@field			messageSize
						size of the entire message, including messageID and messageSize
	@field			parent
						the parent of the added or removed object (possibly NULL)
	@field			parentType
						the type of the parent object (undefined if parent is NULL)
	@field			child
						the added or removed object
	@field			childType
						the type of the added or removed object
*/
struct MIDIObjectAddRemoveNotification
{
	MIDINotificationMessageID	messageID;
	UInt32						messageSize;
	MIDIObjectRef				parent;
	MIDIObjectType				parentType;
	MIDIObjectRef				child;
	MIDIObjectType				childType;
};
typedef struct MIDIObjectAddRemoveNotification MIDIObjectAddRemoveNotification;

/*!
	@struct			MIDIObjectPropertyChangeNotification
	@abstract		A message describing the addition or removal of an object.
	
	@field			messageID
						type of message
	@field			messageSize
						size of the entire message, including messageID and messageSize
	@field			object
						the object whose property has changed
	@field			objectType
						the type of the object whose property has changed
	@field			propertyName
						the name of the changed property
*/
struct MIDIObjectPropertyChangeNotification
{
	MIDINotificationMessageID	messageID;
	UInt32						messageSize;
	MIDIObjectRef				object;
	MIDIObjectType				objectType;
	CFStringRef					propertyName;
};
typedef struct MIDIObjectPropertyChangeNotification MIDIObjectPropertyChangeNotification;

struct MIDIIOErrorNotification
{
	MIDINotificationMessageID	messageID;
	UInt32						messageSize;
	MIDIDeviceRef				driverDevice;
	OSStatus					errorCode;
};
typedef struct MIDIIOErrorNotification MIDIIOErrorNotification;

//=============================================================================
//	Property name constants
//=============================================================================

/*!
	@constant		kMIDIPropertyName
	@discussion
		device/entity/endpoint property, string
	
		Devices, entities, and endpoints may all have names.  The recommended way to display an
		endpoint's name is to ask for the endpoint name, and display only that name if it is
		unique.  If it is non-unique, prepend the device name.

		A setup editor may allow the user to set the names of both driver-owned and external
		devices.
*/
extern const CFStringRef	kMIDIPropertyName					API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyManufacturer
	@discussion
		device/endpoint property, string

		Drivers should set this property on their devices.

		Setup editors may allow the user to set this property on external devices.

		Creators of virtual endpoints may set this property on their endpoints.
*/
extern const CFStringRef	kMIDIPropertyManufacturer			API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyModel
	@discussion
		device/endpoint property, string

		Drivers should set this property on their devices.

		Setup editors may allow the user to set this property on external devices.

		Creators of virtual endpoints may set this property on their endpoints.
*/
extern const CFStringRef	kMIDIPropertyModel					API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyUniqueID
	@discussion
		devices, entities, endpoints all have unique ID's, integer

		The system assigns unique ID's to all objects.  Creators of virtual endpoints may set
		this property on their endpoints, though doing so may fail if the chosen ID is not
		unique.
*/
extern const CFStringRef	kMIDIPropertyUniqueID				API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyDeviceID
	@discussion
		device/entity property, integer

		The entity's system-exclusive ID, in user-visible form

		Drivers may set this property on their devices or entities.

		Setup editors may allow the user to set this property on external devices.
*/
extern const CFStringRef	kMIDIPropertyDeviceID				API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyReceiveChannels
	@discussion
		endpoint property, integer

		The value is a bitmap of channels on which the object receives: 1=ch 1, 2=ch 2, 4=ch 3
		... 0x8000=ch 16.

		Drivers may set this property on their entities or endpoints.

		Setup editors may allow the user to set this property on external endpoints.

		Virtual destination may set this property on their endpoints.
*/
extern const CFStringRef	kMIDIPropertyReceiveChannels		API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyTransmitChannels
	@discussion
		endpoint property, integer

		The value is a bitmap of channels on which the object transmits: 1=ch 1, 2=ch 2, 4=ch 3
		... 0x8000=ch 16.
*/
extern const CFStringRef	kMIDIPropertyTransmitChannels		API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyMaxSysExSpeed
	@discussion
		device/entity/endpoint property, integer

		Set by the owning driver; should not be touched by other clients.
		The value is the maximum rate, in bytes/second, at which sysex messages may
		be sent reliably to this object. (The default value is 3125, as with MIDI 1.0)
*/
extern const CFStringRef	kMIDIPropertyMaxSysExSpeed			API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));


/*!
	@constant		kMIDIPropertyAdvanceScheduleTimeMuSec
	@discussion
		device/entity/endpoint property, integer

		Set by the owning driver; should not be touched by other clients. If it is non-zero,
		then it is a recommendation of how many microseconds in advance clients should schedule
		output. Clients should treat this value as a minimum.  For devices with a non-zero
		advance schedule time, drivers will receive outgoing messages to the device at the time
		they are sent by the client, via MIDISend, and the driver is responsible for scheduling
		events to be played at the right times according to their timestamps.

		As of CoreMIDI 1.3, this property may also be set on virtual destinations (but only the
		creator of the destination should do so). When a client sends to a virtual destination
		with an advance schedule time of 0, the virtual destination receives its messages at
		their scheduled delivery time.  If a virtual destination has a non-zero advance schedule
		time, it receives timestamped messages as soon as they are sent, and must do its own
		internal scheduling of received events.
*/
extern const CFStringRef	kMIDIPropertyAdvanceScheduleTimeMuSec	API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyIsEmbeddedEntity
	@discussion
		entity/endpoint property, integer

		0 if there are external MIDI connectors, 1 if not.
*/
extern const CFStringRef	kMIDIPropertyIsEmbeddedEntity			API_AVAILABLE(macos(10.1), ios(4.2), tvos(12.0));


/*!
	@constant		kMIDIPropertyIsBroadcast
	@discussion
		entity/endpoint property, integer

		1 if the endpoint broadcasts messages to all of the other endpoints in the device, 0 if
		not.  Set by the owning driver; should not be touched by other clients.
*/
extern const CFStringRef	kMIDIPropertyIsBroadcast				API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertySingleRealtimeEntity
	@discussion
		device property, integer

		Some MIDI interfaces cannot route MIDI realtime messages to individual outputs; they are
		broadcast.  On such devices the inverse is usually also true -- incoming realtime
		messages cannot be identified as originating from any particular source.

		When this property is set on a driver device, it signifies the 0-based index of the
		entity on which incoming realtime messages from the device will appear to have
		originated from.
*/
extern const CFStringRef	kMIDIPropertySingleRealtimeEntity		API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyConnectionUniqueID
	@discussion
		device/entity/endpoint property, integer or CFDataRef

		UniqueID of an external device/entity/endpoint attached to this one. As of Mac OS X
		10.3, Audio MIDI Setup maintains endpoint-to-external endpoint connections (in 10.2, it
		connected devices to devices).

		The property is non-existant or 0 if there is no connection.
		
		Beginning with CoreMIDI 1.3 (Mac OS X 10.2), this property may also be a CFDataRef containing an array of
		big-endian SInt32's, to allow specifying that a driver object connects to multiple
		external objects (via MIDI thru-ing or splitting).

		This property may also exist for external devices/entities/endpoints, in which case it
		signifies a MIDI Thru connection to another external device/entity/endpoint (again,
		it is strongly recommended that it be an endpoint).
*/
extern const CFStringRef	kMIDIPropertyConnectionUniqueID			API_AVAILABLE(macos(10.1), ios(4.2), tvos(12.0));


/*!
	@constant		kMIDIPropertyOffline
	@discussion
		device/entity/endpoint property, integer

		1 = device is offline (is temporarily absent), 0 = present. Set by the owning driver, on
		the device; should not be touched by other clients. Property is inherited from the
		device by its entities and endpoints.
*/
extern const CFStringRef	kMIDIPropertyOffline					API_AVAILABLE(macos(10.1), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyPrivate
	@discussion
		device/entity/endpoint property, integer

		1 = endpoint is private, hidden from other clients. May be set on a device or entity,
		but they will still appear in the API; only affects whether the owned endpoints are
		hidden.
*/
extern const CFStringRef	kMIDIPropertyPrivate					API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyDriverOwner
	@discussion
		device/entity/endpoint property, string

		Name of the driver that owns a device. Set by the owning driver, on the device; should
		not be touched by other clients. Property is inherited from the device by its entities
		and endpoints.
*/
extern const CFStringRef	kMIDIPropertyDriverOwner				API_AVAILABLE(macos(10.1), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyFactoryPatchNameFile
	@discussion
		device/entity/endpoint property, CFData containing AliasHandle.

		An alias to the device's current factory patch name file.

		Added in CoreMIDI 1.1 (Mac OS X 10.1).  DEPRECATED as of CoreMIDI 1.3. Use
		kMIDIPropertyNameConfiguration instead.
*/
extern const CFStringRef	kMIDIPropertyFactoryPatchNameFile		API_DEPRECATED_WITH_REPLACEMENT("kMIDIPropertyNameConfiguration", macos(10.1, 10.2)) API_UNAVAILABLE(ios, tvos);


/*!
	@constant		kMIDIPropertyUserPatchNameFile
	@discussion
		device/entity/endpoint property, CFData containing AliasHandle

		An alias to the device's current user patch name file.

		Added in CoreMIDI 1.1 (Mac OS X 10.1).  DEPRECATED as of CoreMIDI 1.3. Use
		kMIDIPropertyNameConfiguration instead.
*/
extern const CFStringRef	kMIDIPropertyUserPatchNameFile			API_DEPRECATED_WITH_REPLACEMENT("kMIDIPropertyNameConfiguration", macos(10.1, 10.2)) API_UNAVAILABLE(ios, tvos);

/*!
	@constant		kMIDIPropertyNameConfiguration
	@discussion
		device/entity/endpoint property, CFDictionary

		This specifies the device's current patch, note and control name values using the
		MIDINameDocument XML format.  This specification requires the use of higher-level,
		OS-specific constructs outside of the specification to fully define the current names
		for a device.

		The MIDINameConfiguration property is implementated as a CFDictionary:

		key "master" maps to a CFDataRef containing an AliasHandle referring to the device's
		master name document. This is deprecated as of Mac OS X 10.10.
		
		key "masterDocumentPath" maps to a CFStringRef containing the filesystem path to the device's
		master name document. (This is new as of Mac OS X 10.10, but since the CoreMIDI
		implementation does not parse this dictionary, the convention can be safely ported
		to earlier versions of Mac OS X.)

		key "banks" maps to a CFDictionaryRef.  This dictionary's keys are CFStringRef names of
		patchBank elements in the master document, and its values are each a CFDictionaryRef:
		key "file" maps to a CFDataRef containing an AliasHandle to a document containing
		patches that override those in the master document, and key "patchNameList" maps to a
		CFStringRef which is the name of the patchNameList element in the overriding document.

		key "currentChannelNameSets" maps to a 16-element CFArrayRef, each element of which is a
		CFStringRef of the name of the current mode for each of the 16 MIDI channels.

		key "currentDeviceMode" maps to a CFStringRef containing the name of the device's mode.

		Clients setting this property must take particular care to preserve dictionary values
		other than the ones they are interested in changing and to properly structure the
		dictionary.
*/
extern const CFStringRef	kMIDIPropertyNameConfiguration			API_DEPRECATED_WITH_REPLACEMENT("kMIDIPropertyNameConfigurationDictionary", macos(10.2, 10.15), ios(4.2, 13.0), tvos(12.0, 13.0));

/*!
    @constant        kMIDIPropertyNameConfigurationDictionary
    @discussion
        device/entity/endpoint property, CFDictionary

        This specifies the device's current patch, note and control name values using the
        MIDINameDocument XML format.  This specification requires the use of higher-level,
        OS-specific constructs outside of the specification to fully define the current names
        for a device.

        The MIDINameConfiguration property is implementated as a CFDictionary:

        key "masterDocumentPath" maps to a CFStringRef containing the filesystem path to the device's
        master name document.

        key "banks" maps to a CFDictionaryRef.  This dictionary's keys are CFStringRef names of
        patchBank elements in the master document, and its values are each a CFDictionaryRef:
        key "file" maps to a CFDataRef containing URL bookmark data to a document containing
        patches that override those in the master document, and key "patchNameList" maps to a
        CFStringRef which is the name of the patchNameList element in the overriding document.

        key "currentChannelNameSets" maps to a 16-element CFArrayRef, each element of which is a
        CFStringRef of the name of the current mode for each of the 16 MIDI channels.

        key "currentDeviceMode" maps to a CFStringRef containing the name of the device's mode.

        Clients setting this property must take particular care to preserve dictionary values
        other than the ones they are interested in changing and to properly structure the
        dictionary.
*/
extern const CFStringRef    kMIDIPropertyNameConfigurationDictionary            API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/*!
	@constant		kMIDIPropertyImage
	@discussion
		device property, CFStringRef which is a full POSIX path to a device or external device's
		icon, stored in any standard graphic file format such as JPEG, GIF, PNG and TIFF are all
		acceptable.  (See CFURL for functions to convert between POSIX paths and other ways of
		specifying files.)  The image's maximum size should be 128x128.

		Drivers should set the icon on the devices they add.

		A studio setup editor should allow the user to choose icons for external devices.
*/
extern const CFStringRef	kMIDIPropertyImage						API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyDriverVersion
	@discussion
		device/entity/endpoint property, integer, returns the driver version API of the owning
		driver (only for driver- owned devices).  Drivers need not set this property;
		applications should not write to it.
*/
extern const CFStringRef	kMIDIPropertyDriverVersion				API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertySupportsGeneralMIDI
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity implements
		the General MIDI specification.
*/
extern const CFStringRef	kMIDIPropertySupportsGeneralMIDI		API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertySupportsMMC
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity implements
		the MIDI Machine Control portion of the MIDI specification.
*/
extern const CFStringRef	kMIDIPropertySupportsMMC				API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyCanRoute
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity can route
		MIDI messages to or from other external MIDI devices (as with MIDI patch bays). This
		should NOT be set on devices which are controlled by drivers.
*/
extern const CFStringRef	kMIDIPropertyCanRoute					API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyReceivesClock
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity  responds
		to MIDI beat clock messages.
*/
extern const CFStringRef	kMIDIPropertyReceivesClock				API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyReceivesMTC
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity responds
		to MIDI Time Code messages.
*/
extern const CFStringRef	kMIDIPropertyReceivesMTC				API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyReceivesNotes
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity responds
		to MIDI Note On messages.
*/
extern const CFStringRef	kMIDIPropertyReceivesNotes				API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyReceivesProgramChanges
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity responds
		to MIDI program change messages.
*/
extern const CFStringRef	kMIDIPropertyReceivesProgramChanges		API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyReceivesBankSelectMSB
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity responds
		to MIDI bank select MSB messages (control 0).
*/
extern const CFStringRef	kMIDIPropertyReceivesBankSelectMSB		API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyReceivesBankSelectLSB
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity responds
		to MIDI bank select LSB messages (control 32).
*/
extern const CFStringRef	kMIDIPropertyReceivesBankSelectLSB		API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyTransmitsClock
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity transmits
		MIDI beat clock messages.
*/
extern const CFStringRef	kMIDIPropertyTransmitsClock				API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyTransmitsMTC
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity transmits
		MIDI Time Code messages.
*/
extern const CFStringRef	kMIDIPropertyTransmitsMTC				API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyTransmitsNotes
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity transmits
		MIDI note messages.
*/
extern const CFStringRef	kMIDIPropertyTransmitsNotes				API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyTransmitsProgramChanges
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity transmits
		MIDI program change messages.
*/
extern const CFStringRef	kMIDIPropertyTransmitsProgramChanges	API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyTransmitsBankSelectMSB
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity transmits
		MIDI bank select MSB messages (control 0).
*/
extern const CFStringRef	kMIDIPropertyTransmitsBankSelectMSB		API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyTransmitsBankSelectLSB
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity transmits
		MIDI bank select LSB messages (control 32).
*/
extern const CFStringRef	kMIDIPropertyTransmitsBankSelectLSB		API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyPanDisruptsStereo
	@discussion
		device/entity property, integer (0/1). Indicates whether the MIDI pan messages (control
		10), when sent to the device or entity, cause undesirable effects when playing stereo
		sounds (e.g. converting the signal to mono).
*/
extern const CFStringRef	kMIDIPropertyPanDisruptsStereo			API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyIsSampler
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity plays
		audio samples in response to MIDI note messages.
*/
extern const CFStringRef	kMIDIPropertyIsSampler					API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyIsDrumMachine
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity's sound
		presets tend to be collections of non-transposable samples (e.g. drum kits).
*/
extern const CFStringRef	kMIDIPropertyIsDrumMachine				API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyIsMixer
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity mixes
		external audio signals, controlled by MIDI messages.
*/
extern const CFStringRef	kMIDIPropertyIsMixer					API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyIsEffectUnit
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity is
		primarily a MIDI-controlled audio effect unit (i.e. does not generate sound on its own).
*/
extern const CFStringRef	kMIDIPropertyIsEffectUnit				API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyMaxReceiveChannels
	@discussion
		device/entity property, integer (0-16). Indicates the maximum number of MIDI channels on
		which a device may simultaneously receive MIDI Channel Messages. Common values are 0
		(devices which only respond to System Messages), 1 (non-multitimbral devices), and 16
		(fully multitimbral devices). Other values are possible, for example devices which are
		multi-timbral but have fewer than 16 "parts".
*/
extern const CFStringRef	kMIDIPropertyMaxReceiveChannels			API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyMaxTransmitChannels
	@discussion
		device/entity property, integer (0/1). Indicates the maximum number of MIDI channels on
		which a device may simultaneously transmit MIDI Channel Messages. Common values are 0, 1
		and 16.
*/
extern const CFStringRef	kMIDIPropertyMaxTransmitChannels		API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyDriverDeviceEditorApp
	@discussion
		device property, string, contains the full path to an application which knows how to
		configure this driver-owned devices. Drivers may set this property on their owned
		devices. Applications must not write to it.
*/
extern const CFStringRef	kMIDIPropertyDriverDeviceEditorApp		API_AVAILABLE(macos(10.3), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertySupportsShowControl
	@discussion
		device/entity property, integer (0/1). Indicates whether the device implements the MIDI
		Show Control specification.
*/
extern const CFStringRef	kMIDIPropertySupportsShowControl		API_AVAILABLE(macos(10.4), ios(4.2), tvos(12.0));

/*!
	@constant		kMIDIPropertyDisplayName
	@discussion
		device/entity/endpoint property, string.

		Provides the Apple-recommended user-visible name for an endpoint, by combining the
		device and endpoint names.

		For objects other than endpoints, the display name is the same as the name.
*/
extern const CFStringRef	kMIDIPropertyDisplayName				API_AVAILABLE(macos(10.4), ios(4.2), tvos(12.0));

//==================================================================================================
#pragma mark	Clients
/*!
	@functiongroup	Clients
*/

/*!
	@function		MIDIClientCreate

	@abstract 		Creates a MIDIClient object.

	@param			name
						The client's name.
	@param			notifyProc	
						An optional (may be NULL) callback function through which the client
						will receive notifications of changes to the system.
	@param			notifyRefCon 
						A refCon passed back to notifyRefCon
	@param			outClient	
						On successful return, points to the newly-created MIDIClientRef.
	@result			An OSStatus result code.
	
	@discussion
		Note that notifyProc will always be called on the run loop which was current when
		MIDIClientCreate was first called.
	
*/
extern OSStatus
MIDIClientCreate(	CFStringRef					name,
					MIDINotifyProc __nullable	notifyProc,
					void * __nullable			notifyRefCon,
					MIDIClientRef *				outClient )				API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIClientCreateWithBlock

	@abstract 		Creates a MIDIClient object.

	@param			name
						The client's name.
	@param			outClient	
						On successful return, points to the newly-created MIDIClientRef.
	@param			notifyBlock
						An optional (may be NULL) block via which the client
						will receive notifications of changes to the system.
	@result			An OSStatus result code.
	
	@discussion
		Note that notifyBlock is called on a thread chosen by the implementation.
		Thread-safety is the block's responsibility.
*/
extern OSStatus
MIDIClientCreateWithBlock(
					CFStringRef					name,
					MIDIClientRef *				outClient,
					MIDINotifyBlock __nullable	notifyBlock )			API_AVAILABLE(macos(10.11), ios(9.0), tvos(12.0));


/*!
	@function   	MIDIClientDispose

	@abstract   	Disposes a MIDIClient object.
	
	@param  		client
						The client to dispose.
	@result			An OSStatus result code.

	@discussion
		It is not essential to call this function; the CoreMIDI framework will automatically
		dispose all MIDIClients when an application terminates.
*/
extern OSStatus
MIDIClientDispose(	MIDIClientRef client )					API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

//==================================================================================================
#pragma mark	Ports
/*!
	@functiongroup	Ports
*/

/*!
	@function		MIDIInputPortCreate

	@abstract 		Creates an input port through which the client may receive
					incoming MIDI messages from any MIDI source.

	@param			client
						The client to own the newly-created port.
	@param			portName
						The name of the port.
	@param			readProc
						The MIDIReadProc which will be called with incoming MIDI,
						from sources connected to this port.
	@param			refCon
						The refCon passed to readHook.
	@param			outPort
						On successful return, points to the newly-created
						MIDIPort.
	@result			An OSStatus result code.

	@discussion
		After creating a port, use MIDIPortConnectSource to establish an input connection from
		any number of sources to your port.
		
		readProc will be called on a separate high-priority thread owned by CoreMIDI.
*/
extern OSStatus 
MIDIInputPortCreate(	MIDIClientRef		client,
						CFStringRef			portName,
						MIDIReadProc		readProc,
						void * __nullable	refCon,
						MIDIPortRef * 		outPort )			API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIInputPortCreateWithBlock

	@abstract 		Creates an input port through which the client may receive
					incoming MIDI messages from any MIDI source.

	@param			client
						The client to own the newly-created port.
	@param			portName
						The name of the port.
	@param			outPort
						On successful return, points to the newly-created
						MIDIPort.
	@param			readBlock
						The MIDIReadBlock which will be called with incoming MIDI, from sources
						connected to this port.
	@result			An OSStatus result code.

	@discussion
		After creating a port, use MIDIPortConnectSource to establish an input connection from
		any number of sources to your port.
		
		readBlock will be called on a separate high-priority thread owned by CoreMIDI.
*/
extern OSStatus
MIDIInputPortCreateWithBlock(	MIDIClientRef	client,
								CFStringRef		portName,
								MIDIPortRef *	outPort,
								MIDIReadBlock	readBlock )	API_AVAILABLE(macos(10.11), ios(9.0), tvos(12.0));


/*!
	@function		MIDIOutputPortCreate

	@abstract 		Creates an output port through which the client may send
					outgoing MIDI messages to any MIDI destination.

	@param			client
						The client to own the newly-created port
	@param			portName
						The name of the port.
	@param			outPort
						On successful return, points to the newly-created
						MIDIPort.
	@result			An OSStatus result code.

	@discussion
		Output ports provide a mechanism for MIDI merging.  CoreMIDI assumes that each output
		port will be responsible for sending only a single MIDI stream to each destination,
		although a single port may address all of the destinations in the system.

		Multiple output ports are only necessary when an application is capable of directing
		multiple simultaneous MIDI streams to the same destination.
*/
extern OSStatus
MIDIOutputPortCreate(	MIDIClientRef	client, 
						CFStringRef		portName,
						MIDIPortRef *	outPort )			API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIPortDispose

	@abstract 		Disposes a MIDIPort object.

	@param			port
						The port to dispose.
	@result			An OSStatus result code.

	@discussion
		It is not usually necessary to call this function; when an application's MIDIClient's
		are automatically disposed at termination, or explicitly, via MIDIClientDispose, the
		client's ports are automatically disposed at that time.
*/
extern OSStatus
MIDIPortDispose(	MIDIPortRef port )						API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));


/*!
	@function		MIDIPortConnectSource

	@abstract 		Establishes a connection from a source to a client's input port.

	@param			port
						The port to which to create the connection.  This port's
						readProc is called with incoming MIDI from the source.
	@param			source
						The source from which to create the connection.
	@param			connRefCon	
						This refCon is passed to the port's MIDIReadProc or MIDIReadBlock, as a way to
						identify the source.
	@result			An OSStatus result code.

	@discussion
*/
extern OSStatus
MIDIPortConnectSource(	MIDIPortRef		port, 
						MIDIEndpointRef	source, 
						void * __nullable			connRefCon )		API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));


/*!
	@function		MIDIPortDisconnectSource
	
	@abstract 		Closes a previously-established source-to-input port 
					connection.

	@param			port
						The port whose connection is being closed.
	@param			source
						The source from which to close a connection to the
						specified port.
	@result			An OSStatus result code.

	@discussion
*/
extern OSStatus
MIDIPortDisconnectSource(	MIDIPortRef		port, 
							MIDIEndpointRef	source )		API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));


//==================================================================================================
#pragma mark	Devices
/*!
	@functiongroup	Devices
*/

/*!
	@function		MIDIGetNumberOfDevices

	@abstract 		Returns the number of devices in the system.

	@result			The number of devices in the system, or 0 if an error 
					occurred.
*/
extern ItemCount
MIDIGetNumberOfDevices(void)								API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));


/*!
	@function		MIDIGetDevice

	@abstract 		Returns one of the devices in the system.

	@param			deviceIndex0
						The index (0...MIDIGetNumberOfDevices()-1) of the device
						to return.
	@result			A reference to a device, or NULL if an error occurred.

	@discussion
		Use this to enumerate the devices in the system.

		To enumerate the entities in the system, you can walk through the devices, then walk
		through the devices' entities.

		Note: If a client iterates through the devices and entities in the system, it will not
		ever visit any virtual sources and destinations created by other clients.  Also, a
		device iteration will return devices which are "offline" (were present in the past but
		are not currently present), while iterations through the system's sources and
		destinations will not include the endpoints of offline devices.

		Thus clients should usually use MIDIGetNumberOfSources, MIDIGetSource,
		MIDIGetNumberOfDestinations and MIDIGetDestination, rather iterating through devices and
		entities to locate endpoints.
*/
extern MIDIDeviceRef
MIDIGetDevice(	ItemCount deviceIndex0 )					API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIDeviceGetNumberOfEntities

	@abstract 		Returns the number of entities in a given device.
	
	@param			device
						The device being queried.

	@result			The number of entities the device contains, or 0 if an
					error occurred.
*/
extern ItemCount 
MIDIDeviceGetNumberOfEntities(	MIDIDeviceRef device )		API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIDeviceGetEntity

	@abstract 		Returns one of a given device's entities.
	
	@param			device
						The device being queried.
	@param			entityIndex0
						The index (0...MIDIDeviceGetNumberOfEntities(device)-1)
						of the entity to return

	@result			A reference to an entity, or NULL if an error occurred.
*/
extern MIDIEntityRef
MIDIDeviceGetEntity(	MIDIDeviceRef	device,
						ItemCount		entityIndex0 )		API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

//==================================================================================================
#pragma mark	Entities
/*!
	@functiongroup	Entities
*/

/*!
	@function		MIDIEntityGetNumberOfSources
	
	@abstract 		Returns the number of sources in a given entity.
	
	@param			entity
						The entity being queried

	@result			The number of sources the entity contains, or 0 if an
					error occurred.
*/
extern ItemCount
MIDIEntityGetNumberOfSources(	MIDIEntityRef entity )		API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIEntityGetSource

	@abstract 		Returns one of a given entity's sources.
	
	@param			entity
						The entity being queried.
	@param			sourceIndex0
						The index (0...MIDIEntityGetNumberOfSources(entity)-1) of
						the source to return

	@result			A reference to a source, or NULL if an error occurred.
*/
extern MIDIEndpointRef
MIDIEntityGetSource(	MIDIEntityRef entity, 
						ItemCount sourceIndex0 )			API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIEntityGetNumberOfDestinations

	@abstract 		Returns the number of destinations in a given entity.
	
	@param			entity
						The entity being queried

	@result			The number of destinations the entity contains, or 0
					if an error occurred.
*/
extern ItemCount
MIDIEntityGetNumberOfDestinations(	MIDIEntityRef entity )	API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIEntityGetDestination

	@abstract 		Returns one of a given entity's destinations.
	
	@param			entity
						The entity being queried.
	@param			destIndex0
						The index (0...MIDIEntityGetNumberOfDestinations(entity)
						- 1) of the destination to return

	@result			A reference to a destination, or NULL if an error occurred.
*/
extern MIDIEndpointRef
MIDIEntityGetDestination(	MIDIEntityRef	entity,
							ItemCount		destIndex0 )	API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIEntityGetDevice

	@abstract 		Returns an entity's device.
	
	@param			inEntity
						The entity being queried.
	@param			outDevice
						On successful return, the entity's owning device.
*/
extern OSStatus
MIDIEntityGetDevice(		MIDIEntityRef		inEntity,
							MIDIDeviceRef * __nullable		outDevice)	API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

//==================================================================================================
#pragma mark	Endpoints
/*!
	@functiongroup	Endpoints
*/

/*!
	@function		MIDIGetNumberOfSources

	@abstract 		Returns the number of sources in the system.

	@result			The number of sources in the system, or 0 if an error
					occurred.
*/
extern ItemCount
MIDIGetNumberOfSources(void)								API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));


/*!
	@function		MIDIGetSource

	@abstract 		Returns one of the sources in the system.

	@param			sourceIndex0	
						The index (0...MIDIGetNumberOfSources()-1) of the source
						to return
	@result			A reference to a source, or NULL if an error occurred.
*/
extern MIDIEndpointRef
MIDIGetSource(	ItemCount sourceIndex0 )					API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));


/*!
	@function		MIDIGetNumberOfDestinations

	@abstract 		Returns the number of destinations in the system.

	@result			The number of destinations in the system, or 0 if an error 
					occurred.
*/
extern ItemCount
MIDIGetNumberOfDestinations(void)							API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));


/*!
	@function		MIDIGetDestination

	@abstract 		Returns one of the destinations in the system.

	@param			destIndex0	
						The index (0...MIDIGetNumberOfDestinations()-1) of the
						destination to return
	@result			A reference to a destination, or NULL if an error occurred.
*/
extern MIDIEndpointRef
MIDIGetDestination(	ItemCount destIndex0 )					API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIEndpointGetEntity

	@abstract 		Returns an endpoint's entity.
	
	@param			inEndpoint
						The endpoint being queried.
	@param			outEntity
						On exit, the endpoint's owning entity, or NULL if none.
	
	@discussion
		Virtual sources and destinations don't have entities.
*/
extern OSStatus
MIDIEndpointGetEntity(		MIDIEndpointRef		inEndpoint,
							MIDIEntityRef * __nullable		outEntity)	API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@function		MIDIDestinationCreate

	@abstract 		Creates a virtual destination in a client.

	@param			client
						The client owning the virtual destination.
	@param			name
						The name of the virtual destination.
	@param			readProc
						The MIDIReadProc to be called when a client sends MIDI to
						the virtual destination.
	@param			refCon
						The refCon to be passed to the readProc.
	@param			outDest
						On successful return, a pointer to the newly-created
						destination.
	@result			An OSStatus result code.

	@discussion
		The specified readProc gets called when clients send MIDI to your virtual destination.

		Drivers need not call this; when they create devices and entities, sources and
		destinations are created at that time.
		
		After creating a virtual destination, it's a good idea to assign it the same unique ID
		it had the last time your application created it. (Although you should be prepared for
		this to fail in the unlikely event of a collision.) This will permit other clients
		to retain persistent references to your virtual destination more easily.
		
		See the discussion of kMIDIPropertyAdvanceScheduleTimeMuSec for notes about the
		relationship between when a sender sends MIDI to the destination and when it is
		received.
*/
extern OSStatus
MIDIDestinationCreate(	MIDIClientRef 		client, 
						CFStringRef  		name,
						MIDIReadProc 		readProc,
						void * __nullable	refCon,
						MIDIEndpointRef *	outDest )		API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIDestinationCreateWithBlock

	@abstract 		Creates a virtual destination in a client.

	@param			client
						The client owning the virtual destination.
	@param			name
						The name of the virtual destination.
	@param			outDest
						On successful return, a pointer to the newly-created
						destination.
	@param			readBlock
						The MIDIReadBlock to be called when a client sends MIDI to the virtual
						destination.
	@result			An OSStatus result code.

	@discussion
		The specified readBlock gets called when clients send MIDI to your virtual destination.

		Drivers need not call this; when they create devices and entities, sources and
		destinations are created at that time.
		
		After creating a virtual destination, it's a good idea to assign it the same unique ID
		it had the last time your application created it. (Although you should be prepared for
		this to fail in the unlikely event of a collision.) This will permit other clients
		to retain persistent references to your virtual destination more easily.
		
		See the discussion of kMIDIPropertyAdvanceScheduleTimeMuSec for notes about the
		relationship between when a sender sends MIDI to the destination and when it is
		received.
*/
extern OSStatus
MIDIDestinationCreateWithBlock(	MIDIClientRef 		client,
								CFStringRef  		name,
								MIDIEndpointRef * 	outDest,
								MIDIReadBlock 		readBlock ) API_AVAILABLE(macos(10.11), ios(9.0), tvos(12.0));

/*!
	@function		MIDISourceCreate

	@abstract 		Creates a virtual source in a client.

	@param			client
						The client owning the virtual source.
	@param			name
						The name of the virtual source.
	@param			outSrc
						On successful return, a pointer to the newly-created
						source.
	@result			An OSStatus result code.

	@discussion
		Drivers need not call this; when they create devices and entities, sources and
		destinations are created at that time.

		After creating a virtual source, use MIDIReceived to transmit MIDI messages from your
		virtual source to any clients connected to the virtual source.

		After creating a virtual source, it's a good idea to assign it the same unique ID it had
		the last time your application created it. (Although you should be prepared for this to
		fail in the unlikely event of a collision.) This will permit other clients to retain
		persistent references to your virtual source more easily.
*/
extern OSStatus
MIDISourceCreate(	MIDIClientRef 		client, 
					CFStringRef  		name,
					MIDIEndpointRef * 	outSrc )			API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));


/*!
	@function		MIDIEndpointDispose

	@abstract 		Disposes a virtual source or destination your client created.

	@param			endpt
						The endpoint to be disposed.

	@result			An OSStatus result code.
*/
extern OSStatus
MIDIEndpointDispose(	MIDIEndpointRef endpt )				API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));


//==================================================================================================
#pragma mark	External Devices
/*!
	@functiongroup	External Devices
*/
/*!
	@function		MIDIGetNumberOfExternalDevices

	@abstract 		Returns the number of external MIDI devices in the system.
					
	@result			The number of external devices in the system, or 0 if an error 
					occurred.

	@discussion
		External MIDI devices are MIDI devices connected to driver endpoints via a standard MIDI
		cable. Their presence is completely optional, only when a UI (such as Audio MIDI Setup)
		adds them.
*/
extern ItemCount
MIDIGetNumberOfExternalDevices(void)						API_AVAILABLE(macos(10.1), ios(4.2), tvos(12.0));

/*!
	@function		MIDIGetExternalDevice

	@abstract 		Returns one of the external devices in the system.

	@param			deviceIndex0
						The index (0...MIDIGetNumberOfDevices()-1) of the device
						to return.
	@result			A reference to a device, or NULL if an error occurred.

	@discussion
		Use this to enumerate the external devices in the system.
*/
extern MIDIDeviceRef
MIDIGetExternalDevice(	ItemCount deviceIndex0 )			API_AVAILABLE(macos(10.1), ios(4.2), tvos(12.0));

//==================================================================================================
#pragma mark	Objects and Properties
/*!
	@functiongroup	Objects and Properties
*/

/*!
	@function		MIDIObjectGetIntegerProperty

	@abstract 		Gets an object's integer-type property.
	
	@param			obj
						The object whose property is to be returned.
	@param			propertyID
						Name of the property to return.
	@param			outValue
						On successful return, the value of the property.
	@result			An OSStatus result code.

	@discussion
		(See the MIDIObjectRef documentation for information about properties.)
*/
extern OSStatus
MIDIObjectGetIntegerProperty(	MIDIObjectRef	obj, 
								CFStringRef		propertyID,
								SInt32 *		outValue )	API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIObjectSetIntegerProperty

	@abstract 		Sets an object's integer-type property.
	
	@param			obj
						The object whose property is to be altered.
	@param			propertyID
						Name of the property to set.
	@param			value
						New value of the property.
	@result			An OSStatus result code.

	@discussion
		(See the MIDIObjectRef documentation for information about properties.)
*/
extern OSStatus
MIDIObjectSetIntegerProperty(	MIDIObjectRef	obj, 
								CFStringRef		propertyID,
								SInt32			value )		API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIObjectGetStringProperty

	@abstract 		Gets an object's string-type property.

	@param			obj
						The object whose property is to be returned.
	@param			propertyID
						Name of the property to return.
	@param			str
						On successful return, the value of the property.
	@result			An OSStatus result code.

	@discussion
		(See the MIDIObjectRef documentation for information about properties.)
*/
extern OSStatus
MIDIObjectGetStringProperty(	MIDIObjectRef			obj,
								CFStringRef				propertyID,
								CFStringRef __nullable * __nonnull str )		API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIObjectSetStringProperty

	@abstract 		Sets an object's string-type property.
	
	@param			obj
						The object whose property is to be altered.
	@param			propertyID
						Name of the property to set.
	@param			str
						New value of the property.
	@result			An OSStatus result code.

	@discussion
		(See the MIDIObjectRef documentation for information about properties.)
*/
extern OSStatus
MIDIObjectSetStringProperty(	MIDIObjectRef	obj, 
								CFStringRef		propertyID,
								CFStringRef		str )		API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIObjectGetDataProperty

	@abstract 		Gets an object's data-type property.

	@discussion
(See the MIDIObjectRef documentation for information
					about properties.)
		
	@param			obj
						The object whose property is to be returned.
	@param			propertyID
						Name of the property to return.
	@param			outData
						On successful return, the value of the property.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIObjectGetDataProperty(		MIDIObjectRef			obj,
								CFStringRef				propertyID,
								CFDataRef __nullable * __nonnull outData )	API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIObjectSetDataProperty

	@abstract 		Sets an object's data-type property.
	
	@param			obj
						The object whose property is to be altered.
	@param			propertyID
						Name of the property to set.
	@param			data
						New value of the property.
	@result			An OSStatus result code.

	@discussion
		(See the MIDIObjectRef documentation for information about properties.)
*/
extern OSStatus
MIDIObjectSetDataProperty(		MIDIObjectRef	obj, 
								CFStringRef		propertyID,
								CFDataRef		data )		API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIObjectGetDictionaryProperty

	@abstract 		Gets an object's dictionary-type property.

	@param			obj
						The object whose property is to be returned.
	@param			propertyID
						Name of the property to return.
	@param			outDict
						On successful return, the value of the property.
	@result			An OSStatus result code.

	@discussion
		(See the MIDIObjectRef documentation for information about properties.)
*/
extern OSStatus
MIDIObjectGetDictionaryProperty(	MIDIObjectRef					obj,
									CFStringRef						propertyID,
									CFDictionaryRef __nullable * __nonnull outDict )
															API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@function		MIDIObjectSetDictionaryProperty

	@abstract 		Sets an object's dictionary-type property.
	
	@param			obj
						The object whose property is to be altered.
	@param			propertyID
						Name of the property to set.
	@param			dict
						New value of the property.
	@result			An OSStatus result code.

	@discussion
		(See the MIDIObjectRef documentation for information about properties.)
*/
extern OSStatus
MIDIObjectSetDictionaryProperty(MIDIObjectRef	obj, 
								CFStringRef		propertyID,
								CFDictionaryRef dict )		API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@function		MIDIObjectGetProperties
	
	@abstract		Gets all of an object's properties.

	@param			obj
						The object whose properties are to be returned.
	@param			outProperties
						On successful return, the object's properties.
	@param			deep
						true if the object's child objects are to be included
						(e.g. a device's entities, or an entity's endpoints).
	@result			An OSStatus result code.

	@discussion
		Returns a CFPropertyList of all of an object's properties. The property list may be a
		dictionary or an array. Dictionaries map property names (CFString) to values, which may
		be CFNumber, CFString, or CFData.  Arrays are arrays of such values.

		Properties which an object inherits from its owning object (if any) are not included.
*/
extern OSStatus
MIDIObjectGetProperties(		MIDIObjectRef 		obj, 
								CFPropertyListRef __nullable * __nonnull outProperties,
								Boolean				deep )	API_AVAILABLE(macos(10.1), ios(4.2), tvos(12.0));

/*!
	@function		MIDIObjectRemoveProperty
	
	@abstract		Removes an object's property.

	@param			obj
						The object whose property is to be removed.
	@param			propertyID
						The property to be removed.
	@result			An OSStatus result code.

	@discussion
*/
extern OSStatus
MIDIObjectRemoveProperty(		MIDIObjectRef 		obj, 
								CFStringRef			propertyID )
															API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

/*!
	@function		MIDIObjectFindByUniqueID

	@abstract 		Locates a device, external device, entity, or endpoint
					by its uniqueID.
	@param			inUniqueID
						The uniqueID of the object to search for.  (This should
						be the result of an earlier call to MIDIObjectGetIntegerProperty
						for the property kMIDIPropertyUniqueID).
	@param			outObject
						The returned object, or 0 if the object was not found or
						an error occurred.  This should be cast to the appropriate
						type (MIDIDeviceRef, MIDIEntityRef, MIDIEndpointRef),
						according to *outObjectType.
	@param			outObjectType
						On exit, the type of object which was found; undefined
						if none found.
	@result			An OSStatus error code, including kMIDIObjectNotFound if there
					is no object with the specified uniqueID.

	@discussion
*/
extern OSStatus
MIDIObjectFindByUniqueID(	MIDIUniqueID 		inUniqueID,
							MIDIObjectRef * __nullable outObject,
							MIDIObjectType * __nullable outObjectType)
							
															API_AVAILABLE(macos(10.2), ios(4.2), tvos(12.0));

//==================================================================================================
#pragma mark	MIDI I/O
/*!
	@functiongroup	I/O
*/

/*!
	@function		MIDISend

	@abstract 		Sends MIDI to a destination.

	@param			port
						The output port through which the MIDI is to be sent.
	@param			dest
						The destination to receive the events.
	@param			pktlist
						The MIDI events to be sent.
	@result			An OSStatus result code.

	@discussion
		Events with future timestamps are scheduled for future delivery.  CoreMIDI performs
		any needed MIDI merging.
*/
extern OSStatus
MIDISend(	MIDIPortRef 			port, 
			MIDIEndpointRef 		dest, 
			const MIDIPacketList *	pktlist )				API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));
				
/*!
	@function		MIDISendSysex

	@abstract 		Sends a single system-exclusive event, asynchronously.

	@param			request	
						Contains the destination, and a pointer to the MIDI data to be sent.
	@result			An OSStatus result code.

	@discussion
		request->data must point to a single MIDI system-exclusive message, or portion thereof.
*/
extern OSStatus 
MIDISendSysex(	MIDISysexSendRequest *request )				API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIReceived

	@abstract 		Distributes incoming MIDI from a source to the client input ports
					which are connected to that source.

	@param			src
						The source which is transmitting MIDI.
	@param			pktlist
						The MIDI events to be transmitted.
	@result			An OSStatus result code.

	@discussion
		Drivers should call this function when receiving MIDI from a source.

		Clients which have created virtual sources, using MIDISourceCreate, should call this
		function when the source is generating MIDI.
		
		Unlike MIDISend(), a timestamp of 0 is not equivalent to "now"; the driver or virtual
		source is responsible for putting proper timestamps in the packets.
*/
extern OSStatus 
MIDIReceived(	MIDIEndpointRef			src, 
				const MIDIPacketList * 	pktlist )			API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));

/*!
	@function		MIDIFlushOutput
	
	@abstract		Unschedules previously-sent packets.
					
	@param			dest
						All pending events scheduled to be sent to this destination
						are unscheduled.  If NULL, the operation applies to
						all destinations.

	@discussion
		Clients may use MIDIFlushOutput to cancel the sending of packets that were previously
		scheduled for future delivery.
*/
extern OSStatus
MIDIFlushOutput(	MIDIEndpointRef		dest )				API_AVAILABLE(macos(10.1), ios(4.2), tvos(12.0));

/*!
	@function		MIDIRestart

	@abstract 		Stops and restarts MIDI I/O.
	
	@discussion
		This is useful for forcing CoreMIDI to ask its drivers to rescan for hardware.
	
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIRestart(void)											API_AVAILABLE(macos(10.1), ios(4.2), tvos(12.0));



//==================================================================================================
#pragma mark Packet Lists

/*!
	@functiongroup	Packet Lists
*/

#ifdef CF_INLINE
/*!
	@function		MIDIPacketNext

	@abstract 		Advances a MIDIPacket pointer to the MIDIPacket which immediately follows it 
					in memory if it is part of a MIDIPacketList.

	@param			pkt
						A pointer to a MIDIPacket in a MIDIPacketList.

	@result			The subsequent packet in the MIDIPacketList.
*/
CF_INLINE MIDIPacket *MIDIPacketNext(const MIDIPacket *pkt)
{
	#if TARGET_CPU_ARM || TARGET_CPU_ARM64
		// MIDIPacket must be 4-byte aligned
		return	(MIDIPacket *)(((uintptr_t)(&pkt->data[pkt->length]) + 3) & ~3);
	#else
		return	(MIDIPacket *)&pkt->data[pkt->length];
	#endif
}
#else
	#if TARGET_CPU_ARM || TARGET_CPU_ARM64
		// MIDIPacket must be 4-byte aligned
		#define MIDIPacketNext(pkt)	((MIDIPacket *)(((uintptr_t)(&(pkt)->data[(pkt)->length]) + 3) & ~3))
	#else
		#define MIDIPacketNext(pkt)	((MIDIPacket *)&(pkt)->data[(pkt)->length])
	#endif
#endif

/*!
	@function		MIDIPacketListInit

	@abstract 		Prepares a MIDIPacketList to be built up dynamically.
	
	@param			pktlist
						The packet list to be initialized.

	@result			A pointer to the first MIDIPacket in the packet list.
*/
extern MIDIPacket *
MIDIPacketListInit(	MIDIPacketList *pktlist )				API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));


/*!
	@function		MIDIPacketListAdd

	@abstract 		Adds a MIDI event to a MIDIPacketList.
	
	@param			pktlist
						The packet list to which the event is to be added.
	@param			listSize
						The size, in bytes, of the packet list.
	@param			curPacket
						A packet pointer returned by a previous call to
						MIDIPacketListInit or MIDIPacketListAdd for this packet
						list.
	@param			time
						The new event's time.
	@param			nData
						The length of the new event, in bytes.
	@param			data
						The new event.  May be a single MIDI event, or a partial
						sys-ex event.  Running status is <b>not</b> permitted.
	@result			Returns null if there was not room in the packet for the
					event; otherwise returns a packet pointer which should be
					passed as curPacket in a subsequent call to this function.

	@discussion
		The maximum size of a packet list is 65536 bytes. Large sysex messages must be sent in
		smaller packet lists.
*/
extern MIDIPacket *
MIDIPacketListAdd(	MIDIPacketList *	pktlist,
					ByteCount			listSize,
					MIDIPacket *		curPacket,
					MIDITimeStamp		time,
					ByteCount			nData,
					const Byte *		data)			API_AVAILABLE(macos(10.0), ios(4.2), tvos(12.0));


#ifdef __cplusplus
}
#endif

CF_ASSUME_NONNULL_END

#endif /* __MIDIServices_h__ */
// ==========  CoreMIDI.framework/Headers/MIDINetworkSession.h
/*
    File:       CoreMIDI/MIDINetworkSession.h
 
    Contains:   Routines for MIDI networking
 
 	Copyright:  (c) 2010 by Apple Inc., all rights reserved.
 
    Bugs?:      For bug reports, consult the following page on
                the World Wide Web:
 
                    http://developer.apple.com/bugreporter/
 
*/

#ifndef __MIDINetworkSession_h__
#define __MIDINetworkSession_h__

#if defined(__OBJC__)
#import <CoreMIDI/MIDIServices.h>
#import <Foundation/Foundation.h>

#define MIDINETWORKSESSION_AVAILABLE API_AVAILABLE(macos(15.0), ios(4.2)) API_UNAVAILABLE(watchos, tvos)

NS_ASSUME_NONNULL_BEGIN

/* This is the Bonjour service type. */
OS_EXPORT NSString *const MIDINetworkBonjourServiceType MIDINETWORKSESSION_AVAILABLE;

/*
	These are NSNotifications posted by MIDINetworkSession objects. 

	MIDINetworkNotificationContactsDidChange signifies that the list of contacts changed.
	MIDINetworkNotificationSessionDidChange signifies that other aspects of the session changed,
	such as the connection list, connection policy, etc.
*/
OS_EXPORT NSString *const MIDINetworkNotificationContactsDidChange MIDINETWORKSESSION_AVAILABLE;
OS_EXPORT NSString *const MIDINetworkNotificationSessionDidChange MIDINETWORKSESSION_AVAILABLE;


/* __________________________________________________________________________________________________
	These are the values of connectionPolicy
*/
typedef NS_ENUM(NSUInteger, MIDINetworkConnectionPolicy) {
	MIDINetworkConnectionPolicy_NoOne				= 0,
	MIDINetworkConnectionPolicy_HostsInContactList	= 1,
	MIDINetworkConnectionPolicy_Anyone				= 2
};

/* __________________________________________________________________________________________________
	MIDINetworkHost
	
	Represents a network address.
	name: the user's tag for this object.
	Representations are either:
	-	address (IP address or hostname) and UDP port
	-	netServiceName and netServiceDomain
*/
OS_EXPORT MIDINETWORKSESSION_AVAILABLE
@interface MIDINetworkHost : NSObject {
@private
    void *_imp;
}
+ (instancetype)hostWithName: (NSString *)name address: (NSString *)address port: (NSUInteger)port;
+ (instancetype)hostWithName: (NSString *)name netService: (NSNetService *)netService;
+ (instancetype)hostWithName: (NSString *)name netServiceName: (NSString *)netServiceName netServiceDomain: (NSString *)netServiceDomain;
- (BOOL)hasSameAddressAs: (MIDINetworkHost *)other;

@property(nonatomic,readonly) NSString *name;				/* user's tag */
@property(nonatomic,readonly) NSString *address;			/* IP address or hostname */
@property(nonatomic,readonly) NSUInteger port;						/* UDP port */
@property(nonatomic,readonly,nullable) NSString *netServiceName;	/* NSNetService name */
@property(nonatomic,readonly,nullable) NSString *netServiceDomain;	/* NSNetService domain */
@end

/*__________________________________________________________________________________________________
	MIDINetworkConnection

	Add a connection to a session to connect to the remote host; remove it to disconnect.
*/
OS_EXPORT MIDINETWORKSESSION_AVAILABLE
@interface MIDINetworkConnection : NSObject {
@private
    void *_imp;
}
+ (instancetype)connectionWithHost: (MIDINetworkHost *)host;
@property(nonatomic,readonly) MIDINetworkHost *host;
@end

/* __________________________________________________________________________________________________
	MIDINetworkSession
	
	A network session represents one CoreMIDI entity (source/destination pair). One session can
	have any number of connections. Output is broadcast to all connections; input from multiple
	connections is merged.
*/
OS_EXPORT MIDINETWORKSESSION_AVAILABLE
@interface MIDINetworkSession : NSObject {
@private
    void *_imp;
}

+ (MIDINetworkSession *)defaultSession; /* returns the singleton. */

/* Basic attributes of a session */
@property(nonatomic,getter=isEnabled) BOOL enabled;			/* disabled sessions do not appear on the network and cannot initiate or receive connections. default is NO (disabled). */
@property(nonatomic,readonly) NSUInteger networkPort;		/* UDP port */
@property(nonatomic,readonly) NSString *networkName;		/* name by which this session is advertised via Bonjour */
@property(nonatomic,readonly) NSString *localName;			/* name of this session's CoreMIDI entity (inherited by its endpoints) */
@property(nonatomic) MIDINetworkConnectionPolicy connectionPolicy;	/* who can connect to this session? see constants above. */

/*	The driver maintains a directory of MIDINetworkHosts, "contacts," for user convenience in initiating 
	connections, and for controlling incoming connection requests. */
- (NSSet<MIDINetworkHost *> *)contacts;
- (BOOL)addContact: (MIDINetworkHost *)contact;
- (BOOL)removeContact: (MIDINetworkHost *)contact;

- (NSSet<MIDINetworkConnection *> *)connections;
- (BOOL)addConnection: (MIDINetworkConnection *)connection;
- (BOOL)removeConnection: (MIDINetworkConnection *)connection;

- (MIDIEndpointRef)sourceEndpoint;
- (MIDIEndpointRef)destinationEndpoint;
@end

NS_ASSUME_NONNULL_END

#endif // defined(__OBJC__)

#endif /* __MIDINetworkSession_h__ */
// ==========  CoreMIDI.framework/Headers/MIDICapabilityInquiry.h
/*
 File:       CoreMIDI/MIDICapabilityInquiry.h
 
 Contains:   API for MIDI Capability Inquiry (MIDI-CI)
 
 Copyright:  (c) 2018 by Apple Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 */

// This API requires the modern Objective-C runtime.
#if !defined(MIDICapabilityInquiry_h) && defined(__OBJC2__)
#define MIDICapabilityInquiry_h

#import <CoreMIDI/MIDIServices.h>
#import <Foundation/Foundation.h>
#import <stdint.h>

NS_ASSUME_NONNULL_BEGIN

// Forward declarations.
@class MIDICISession;
@class MIDICIProfile;

/// MIDI Channel, 0~15 (channels 1 through 16, respectively), or MIDIChannelsWholePort. (Per the specifications, this is always a single byte.)
typedef uint8_t MIDIChannelNumber;

/// All MIDI-CI methods involving a channel number use 0x7f to mean "the whole port", i.e. all
/// channels.
static const MIDIChannelNumber MIDIChannelsWholePort = 0x7f;

/*!
 	@struct MIDICIDeviceIdentification
 	@brief  Object describing a MIDI-CI device.
*/
struct MIDICIDeviceIdentification {
	uint8_t manufacturer[3];
	uint8_t family[2];
	uint8_t modelNumber[2];
	uint8_t revisionLevel[4];
	uint8_t reserved[5];		// always zero
};
typedef struct MIDICIDeviceIdentification MIDICIDeviceIdentification;

// =================================================================================================

/*!
 	@class	MIDICIProfile
 	@brief  An NSObject representing Capability Inquiry profile. MIDI-CI profiles describe a mapping
 	of MIDI messages to specific sounds and synthesis behaviors, e.g. General MIDI, a drawbar organ,
 	etc.
*/
OS_EXPORT API_AVAILABLE(macos(10.14), ios(12.0)) API_UNAVAILABLE(watchos, tvos)
@interface MIDICIProfile : NSObject <NSSecureCoding>
@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) NSData *profileID;	// always 5 bytes

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithData:(NSData *)data name:(NSString *)inName;
@end

// =================================================================================================

/*!
 	@class	MIDICIProfileState
 	@brief  Lists the enabled and disabled profiles for a device or one of its MIDI channels.
*/
OS_EXPORT API_AVAILABLE(macos(10.14), ios(12.0)) API_UNAVAILABLE(watchos, tvos)
@interface MIDICIProfileState : NSObject <NSSecureCoding>
@property (nonatomic, readonly) NSArray<MIDICIProfile *> *enabledProfiles;
@property (nonatomic, readonly) NSArray<MIDICIProfile *> *disabledProfiles;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithEnabledProfiles:(NSArray<MIDICIProfile *> *)enabled disabledProfiles:(NSArray<MIDICIProfile *> *)disabled;
@end

// =================================================================================================

/*!
 	@fn     MIDICIProfileChangedBlock
 	@brief  A block called when a device notifies that a profile has been enabled or disabled.
*/
typedef void (^MIDICIProfileChangedBlock)(
				MIDICISession *session, MIDIChannelNumber channel, MIDICIProfile *profile, BOOL enabled);

/*!
 	@fn     MIDICIPropertyChangedBlock
 	@brief  A block called when a device notifies that property data has changed.
*/
typedef void (^MIDICIPropertyChangedBlock)(
				MIDICISession *session, MIDIChannelNumber channel, NSData *data);

/*!
 	@fn     MIDICIPropertyResponseBlock
 	@brief  The Property Exchange methods are asynchronous; this block is called when an entire
 	response has been received.
*/
typedef void (^MIDICIPropertyResponseBlock)(
				MIDICISession *session, MIDIChannelNumber channel, NSData *response, NSError *error);

// =================================================================================================

/*!
 	@class  MIDICISession
 	@brief  Object representating a MIDI Capability Inquiry session.
 
 	A MIDI Capability Inquiry session is a bidirectional communication path between a MIDI process
 	and a driver entity (i.e., pair of endpoints). Since a driver entity is only able to communicate
 	with the host via MIDIServer, creating a MIDICISession gives the process access to the shared
 	communication path.
 
	Please visit http://www.midi.org/specifications for more information on MIDI Capability Inquiry
	and list of currently defined capabilities.
 
*/
OS_EXPORT API_AVAILABLE(macos(10.14), ios(12.0)) API_UNAVAILABLE(watchos, tvos)
@interface MIDICISession : NSObject

/*!
	 @brief  Begin a MIDI-CI session with the provided entity (pair of endpoints).
 
	 dataReadyHandler will be called when properties of the session have become available.
	 Other methods of this class will not return valid/useful information before the dataReadyHandler
	 is called.
*/
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithMIDIEntity:(MIDIEntityRef)entity dataReadyHandler:(void (^)(void))handler;

/// The MIDI entity with which the session is communicating.
@property (nonatomic, readonly) MIDIEntityRef entity;

// After CI session data is ready, indicates whether the entity supports the MIDI-CI profile capability.
@property (nonatomic, readonly) BOOL supportsProfileCapability;

// After CI session data is ready, indicates whether the entity supports the MIDI-CI property exchange capability.
@property (nonatomic, readonly) BOOL supportsPropertyCapability;

/// Obtain the device's basic identification. Null before data is ready or if the device does not
/// support MIDI-CI.
@property (nonatomic, readonly) MIDICIDeviceIdentification deviceIdentification;

/// Given a MIDI channel number, return the supported profiles. Note that the
/// arrays will be empty if this property is queried before data is ready.
- (MIDICIProfileState *)profileStateForChannel:(MIDIChannelNumber)channel;

- (BOOL)enableProfile:(MIDICIProfile *)profile
			onChannel:(MIDIChannelNumber)channel
				error:(NSError **)outError;

- (BOOL)disableProfile:(MIDICIProfile *)profile
			 onChannel:(MIDIChannelNumber)channel
				 error:(NSError **)outError;

/// A block called when a device signals that a profile has been enabled or disabled.
@property (nonatomic, nullable) MIDICIProfileChangedBlock profileChangedCallback;

/// Property exchange. The contents of the data blobs are not yet defined by the standard; here we
/// only provide basic plumbing.
- (void)hasProperty:(NSData *)inquiry
		  onChannel:(MIDIChannelNumber)channel
	responseHandler:(MIDICIPropertyResponseBlock)handler;

- (void)getProperty:(NSData *)inquiry
		  onChannel:(MIDIChannelNumber)channel
	responseHandler:(MIDICIPropertyResponseBlock)handler;

- (void)setProperty:(NSData *)inquiry
		  onChannel:(MIDIChannelNumber)channel
	responseHandler:(MIDICIPropertyResponseBlock)handler;

/// A block called when a device notifies that a property has changed.
@property (nonatomic, nullable) MIDICIPropertyChangedBlock propertyChangedCallback;

@end // MIDICISession

NS_ASSUME_NONNULL_END

#endif /* MIDICapabilityInquiry_h */
// ==========  CoreMIDI.framework/Headers/MIDIThruConnection.h
/*
    File:       CoreMIDI/MIDIThruConnection.h
 
    Contains:   Routines for creating MIDI play-through connections.
 
    Copyright:  (c) 2000-2015 by Apple Inc., all rights reserved.
 
    Bugs?:      For bug reports, consult the following page on
                the World Wide Web:
 
                    http://developer.apple.com/bugreporter/
 
*/

#ifndef __MIDIThruConnection_h__
#define __MIDIThruConnection_h__

#include <CoreFoundation/CoreFoundation.h>
#include <CoreMIDI/MIDIServices.h>

CF_ASSUME_NONNULL_BEGIN

//  -----------------------------------------------------------------------------
/*!
    @header MIDIThruConnection.h

    This header defines functions to create MIDI play-through connections
    between the MIDI sources and destinations.  These connections may be
    persistent or transitory, owned by a client.
    
    By using connections instead of doing MIDI Thru operations themselves,
    the overhead of moving MIDI messages between the server and the client
    for thru-ing is reduced.
    
    The aim of these functions is to permit as flexible a set of transformations 
    as possible while keeping the API and data structures relatively simple.    
*/
//  -----------------------------------------------------------------------------

/*!
    @typedef        MIDIThruConnectionRef
    
    @discussion     An opaque reference to a play-through connection.
*/
typedef MIDIObjectRef MIDIThruConnectionRef;

/*!
    @struct         MIDIValueMap
    
    @discussion     A custom mapping function to transform MIDI 7-bit values,
                    as contained in note numbers, velocities, control values,
                    etc.  y = value[x], where x is the input MIDI value, y the
                    output.
*/
struct MIDIValueMap {
    UInt8           value[128];
};
typedef struct MIDIValueMap MIDIValueMap;

/*!
    @enum           MIDITransformType
    
    @brief          Values specifying a type of MIDI transformation, as found in the transform member of MIDITransform.
    
    @constant   kMIDITransform_None
        no transformation (param unused)
    @constant   kMIDITransform_FilterOut
        filter out the specified event type (param unused)
    @constant   kMIDITransform_MapControl
        transform one control number to another; param is destination control number
    @constant   kMIDITransform_Add
        add param to values
    @constant   kMIDITransform_Scale
        multiple value by the fixed point number in param, which is in fixed point: bbbb.bbbb bbbb bbbb
    @constant   kMIDITransform_MinValue
        the value's minimum value is param
    @constant   kMIDITransform_MaxValue
        the value's maximum value is param
    @constant   kMIDITransform_MapValue
        transform the value using a map; param is the index of the map in the connection's array of maps.
*/
typedef CF_ENUM(UInt16, MIDITransformType) {
    kMIDITransform_None = 0,
    kMIDITransform_FilterOut = 1,
    kMIDITransform_MapControl = 2,
    kMIDITransform_Add = 8,
    kMIDITransform_Scale = 9,
    kMIDITransform_MinValue = 10,
    kMIDITransform_MaxValue = 11,
    kMIDITransform_MapValue = 12
};

enum {
    kMIDIThruConnection_MaxEndpoints = 8
};

/*!
    @enum       MIDITransformControlType
    
    @discussion Specifies how control numbers are interpreted.
    @constant   kMIDIControlType_7Bit
        control numbers may be 0-127
    @constant   kMIDIControlType_14Bit
        control numbers may be 0-31
    @constant   kMIDIControlType_7BitRPN
        control numbers may be 0-16383
    @constant   kMIDIControlType_14BitRPN
    @constant   kMIDIControlType_7BitNRPN
    @constant   kMIDIControlType_14BitNRPN
*/
typedef CF_ENUM(UInt8, MIDITransformControlType) {
    kMIDIControlType_7Bit = 0,
    kMIDIControlType_14Bit = 1,
    kMIDIControlType_7BitRPN = 2,
    kMIDIControlType_14BitRPN = 3,
    kMIDIControlType_7BitNRPN = 4,
    kMIDIControlType_14BitNRPN = 5
};

/*!
    @struct     MIDITransform
    @abstract   Describes how a single type of MIDI event is transformed.
    @discussion This structure controls the transformation of various MIDI events other than control changes.
    @field      transform   The type of transformation to be applied to the event values.
    @field      param       An argument to the transformation method (see description of MIDITransformType).
*/
struct MIDITransform {
    MIDITransformType   transform;
    SInt16              param;
};
typedef struct MIDITransform MIDITransform;

/*!
    @struct     MIDIControlTransform
    @abstract   Describes a transformation of MIDI control change events.

    @field  controlType         The type of control specified by controlNumber
    @field  remappedControlType If transform is kMIDITransform_MapControl, the output control type
    @field  controlNumber       The control number to be affected.
    @field  transform           The type of transformation to be applied to the event values.
    @field  param               An argument to the transformation method (see description of MIDITransformType).

    @discussion
        A single MIDIThruConnectionParams may describe any number of transformations to control
        events. It is important that multiple transformations are ordered correctly: filter out,
        remap, then alter values.
        
        All transformations are done internally using 14-bit values, so for example, when doing
        an add/min/max transform on a 7-bit control value, the parameter must be a 14-bit value.
        For example, to add 10 to a control value, param must be (10 << 7) = 1280.

        As per the MIDI specification, a number of controls are interpreted specially:

        32-63 are the LSBs of 0-31
        6/38 is data entry
        96,97 are data increment, decrement
        98-101 are NRPN/RPN
*/
struct MIDIControlTransform {
    MIDITransformControlType    controlType;
    MIDITransformControlType    remappedControlType;
    UInt16                      controlNumber;
    MIDITransformType           transform;
    SInt16                      param;
};
typedef struct MIDIControlTransform MIDIControlTransform;

/*!
    @struct     MIDIThruConnectionEndpoint
    @abstract   Describes a source or destination in a MIDIThruConnection.
    @field  endpointRef     The endpoint specified as a MIDIEndpointRef.
    @field  uniqueID        The endpoint specified by its uniqueID.
    @discussion
        When creating one of these, you can leave uniqueID 0 if the endpoint exists and you are passing
        its MIDIEndpointRef.
        
        When obtaining one of these from CoreMIDI, endpointRef may be NULL if it doesn't exist, but the
        uniqueID will always be non-zero.
*/
struct MIDIThruConnectionEndpoint {
    MIDIEndpointRef         endpointRef;
    MIDIUniqueID            uniqueID;
};
typedef struct MIDIThruConnectionEndpoint MIDIThruConnectionEndpoint;

/*!
    @struct     MIDIThruConnectionParams
    @abstract   Describes a set of MIDI routings and transformations.
    @field      version     Version of this structure; must be 0.
    @field      numSources  The number of valid sources in the following array.
    @field      sources     All MIDI generated by these sources is routed into this connection for processing
                            and distribution to destinations.
    @field      numDestinations The number of valid destinations in the following array.
    @field      destinations    All MIDI output from the connection is routed to these destinations.
    @field      channelMap      Maps each of the source 16 MIDI channels to channel 0-15 (1-16) or 0xFF when
                                MIDI from a channel is to be filtered out.
    @field      lowVelocity     Note events with a velocity less than this value are filtered out.
    @field      highVelocity    Note events with a velocity greater than this, if it is not 0, are filtered out.
    @field      lowNote         See highNote.
    @field      highNote        If highNote >= lowNote, then notes outside this range are filtered out.
                                If lowNote > highNote, then notes <i>inside</i> this range are filtered out.
                                This applies to note and polyphonic key pressure events.
                                These fields are ignored if a there is a MIDIValueMap applying to noteNumber.
    @field      noteNumber      Specifies how MIDI note numbers are transformed.
    @field      velocity        Specifies how MIDI note velocities are transformed.
    @field      keyPressure     Specifies how MIDI polyphonic key pressure events are transformed.
    @field      channelPressure Specifies how MIDI monophonic (channel) pressure events are transformed.
    @field      programChange   Specifies how MIDI program change events are transformed.
    @field      pitchBend       Specifies how MIDI pitch bend events are transformed.
    @field      filterOutSysEx  If 1, specifies that system-exclusive messages are to be filtered out.
    @field      filterOutMTC    If 1, specifies that MIDI Time Code messages are to be filtered out.
    @field      filterOutBeatClock  If 1, specifies the MIDI clock, play, stop, and resume messages are to
                                be filtered out.
    @field      filterOutTuneRequest    If 1, specifies that MIDI Tune Request messages are to be filtered out.
    @field      reserved2       Must be 0.
    @field      filterOutAllControls    If 1, specifies that all MIDI continuous control messages are to be filtered out.
    @field      numControlTransforms    The number of control transformations in the variable-length portion of the struct.
    @field      numMaps                 The number of MIDIValueMaps in the variable-length portion of the struct.
    @field      reserved3       Must be 0.
    
    @discussion
        The remainder of the structure is variably-sized. It contains numControlTransform instances of 
        MIDIControlTransform, followed by numMaps instances of MIDIValueMap.
*/
struct MIDIThruConnectionParams {
    UInt32                      version;
    UInt32                      numSources;
    MIDIThruConnectionEndpoint  sources[kMIDIThruConnection_MaxEndpoints];
    UInt32                      numDestinations;
    MIDIThruConnectionEndpoint  destinations[kMIDIThruConnection_MaxEndpoints];
    
    UInt8                   channelMap[16];
    UInt8                   lowVelocity, highVelocity;
    UInt8                   lowNote, highNote;
    MIDITransform           noteNumber;
    MIDITransform           velocity;
    MIDITransform           keyPressure;
    MIDITransform           channelPressure;
    MIDITransform           programChange;
    MIDITransform           pitchBend;
    
    UInt8                   filterOutSysEx;
    UInt8                   filterOutMTC;
    UInt8                   filterOutBeatClock;
    UInt8                   filterOutTuneRequest;
    UInt8                   reserved2[3];
    UInt8                   filterOutAllControls;
    
    UInt16                  numControlTransforms;
    UInt16                  numMaps;
    UInt16                  reserved3[4];

    // remainder of structure is variable-length:
    //      MIDIControlTransform    controls[];
    //      MIDIValueMap            maps[];
};
typedef struct MIDIThruConnectionParams MIDIThruConnectionParams;

#ifdef CF_INLINE
/*!
    @defined    MIDIThruConnectionParamsSize
    @abstract   Returns the size of a MIDIThruConnectionParams.
    @discussion Accounts for the variable-length elements in the structure and returns its true
                size in bytes.
*/
CF_INLINE size_t MIDIThruConnectionParamsSize(const MIDIThruConnectionParams *ptr)
{
    return sizeof(MIDIThruConnectionParams) + ptr->numControlTransforms * sizeof(MIDIControlTransform)
	    + ptr->numMaps * sizeof(MIDIValueMap);
}
#else
#define MIDIThruConnectionParamsSize(ptr) \
    (sizeof(MIDIThruConnectionParams) + (ptr)->numControlTransforms * sizeof(MIDIControlTransform) \
    + (ptr)->numMaps * sizeof(MIDIValueMap))
#endif

#ifdef __cplusplus
extern "C" {
#endif
/*!
    @function   MIDIThruConnectionParamsInitialize
    @abstract   Fills a MIDIThruConnectionParams with default values.
    @param      inConnectionParams  The struct to be initialized.
    @result     An OSStatus result code.
    @discussion
        This convenience function fills the connection structure with default values:
no endpoints, no transformations (mostly zeroes except for the channel map).
Then, just filling in the source and adding one destination will create a simple, 
unmodified thru connection.
*/
extern void
MIDIThruConnectionParamsInitialize(
                            MIDIThruConnectionParams *      inConnectionParams )
                                                                API_AVAILABLE(macos(10.2), ios(4.2));

/*!
    @function   MIDIThruConnectionCreate
    @abstract   Creates a thru connection.
    @param      inPersistentOwnerID
                    If null, then the connection is marked as owned by the client
                    and will be automatically disposed with the client.  if it is non-null, then it
                    should be a unique identifier, e.g. "com.mycompany.MyCoolProgram".
    @param      inConnectionParams
                    A MIDIThruConnectionParams contained in a CFDataRef.
    @param      outConnection
                    On successful return, a reference to the newly-created connection.
    @result     An OSStatus result code.
    @discussion
*/
extern OSStatus
MIDIThruConnectionCreate(   CFStringRef __nullable          inPersistentOwnerID,
                            CFDataRef                       inConnectionParams,
                            MIDIThruConnectionRef *         outConnection )
                                                                API_AVAILABLE(macos(10.2), ios(4.2));

/*!
    @function   MIDIThruConnectionDispose
    @abstract   Disposes a thru connection.
    @param      connection
                    The connection to be disposed
    @result     An OSStatus result code.
    @discussion
*/
extern OSStatus
MIDIThruConnectionDispose(  MIDIThruConnectionRef           connection )
                                                                API_AVAILABLE(macos(10.2), ios(4.2));

/*!
    @function   MIDIThruConnectionGetParams
    @abstract   Obtains a thru connection's MIDIThruConnectionParams.
    @param      connection
                    The connection to be disposed.
    @param      outConnectionParams
                    On successful return, the connection's MIDIThruConnectionParams in a CFDataRef
    @result     An OSStatus result code.
    @discussion
        The returned CFDataRef contains a MIDIThruConnectionParams structure. The caller is responsible
        for releasing it.
*/
extern OSStatus
MIDIThruConnectionGetParams(MIDIThruConnectionRef           connection,
                            CFDataRef __nonnull * __nonnull outConnectionParams )
                                                                API_AVAILABLE(macos(10.2), ios(4.2));

/*!
    @function   MIDIThruConnectionSetParams
    @abstract   Alters a thru connection's MIDIThruConnectionParams.
    @param      connection
                    The connection to be modified.
    @param      inConnectionParams
                    The connection's new MIDIThruConnectionParams in a CFDataRef
    @result     An OSStatus result code.
    @discussion
*/
extern OSStatus
MIDIThruConnectionSetParams(MIDIThruConnectionRef           connection,
                            CFDataRef                       inConnectionParams )
                                                                API_AVAILABLE(macos(10.2), ios(4.2));

/*!
    @function   MIDIThruConnectionFind
    @abstract   Returns all of the persistent thru connections created by a client.
    @param      inPersistentOwnerID
                    The ID of the owner whose connections are to be returned.
    @param      outConnectionList
                    On successful return, a CFDataRef containing an array of MIDIThruConnectionRef's.
    @result     An OSStatus result code.
    @discussion
*/
extern OSStatus
MIDIThruConnectionFind(     CFStringRef                     inPersistentOwnerID,
                            CFDataRef __nonnull * __nonnull outConnectionList )
                                                                API_AVAILABLE(macos(10.2), ios(4.2));

#ifdef __cplusplus
}
#endif

CF_ASSUME_NONNULL_END

#endif /* __MIDIThruConnection_h__ */
// ==========  CoreMIDI.framework/Headers/CoreMIDI.h
/*
 	File:   	CoreMIDI/CoreMIDI.h
 
 	Contains:   Umbrella header for the CoreMIDI framework.
 
 	Copyright:  (c) 2000-2018 by Apple Inc., all rights reserved.
 
 	Bugs?:  	For bug reports, consult the following page on
 				the World Wide Web:
 
 					http://developer.apple.com/bugreporter/
 
*/

#ifndef __CoreMIDI_h__
#define __CoreMIDI_h__

#include <CoreMIDI/MIDIServices.h>
#include <CoreMIDI/MIDISetup.h>
#include <CoreMIDI/MIDIThruConnection.h>
#include <CoreMIDI/MIDIDriver.h>

#if TARGET_OS_IPHONE && __OBJC__
#import <CoreMIDI/MIDINetworkSession.h>
#endif

#if __OBJC2__
#import <CoreMIDI/MIDICapabilityInquiry.h>
#endif

#endif
