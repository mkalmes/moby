// ==========  SystemConfiguration.framework/Headers/SCPreferences.h
/*
 * Copyright (c) 2000, 2001, 2004, 2005, 2007-2010, 2015 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _SCPREFERENCES_H
#ifdef	USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS
#include <SystemConfiguration/_SCPreferences.h>
#else	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#define _SCPREFERENCES_H

#include <Availability.h>
#include <TargetConditionals.h>
#include <sys/cdefs.h>
#include <dispatch/dispatch.h>
#include <CoreFoundation/CoreFoundation.h>
#include <SystemConfiguration/SCDynamicStore.h>

#if	!TARGET_OS_IPHONE
#include <Security/Security.h>
#else	// !TARGET_OS_IPHONE
typedef const struct AuthorizationOpaqueRef *	AuthorizationRef;
#endif	// !TARGET_OS_IPHONE

CF_IMPLICIT_BRIDGING_ENABLED
CF_ASSUME_NONNULL_BEGIN

/*!
	@header SCPreferences
	@discussion The SCPreferences API allows an application to load and
		store XML configuration data in a controlled manner and provide
		the necessary notifications to other applications that need to
		be aware of configuration changes.

		To access configuration preferences, you must first establish a
		preferences session using the SCPreferencesCreate function.
		To identify a specific set of preferences to access, you pass a
		value in the prefsID parameter.
		A NULL value indicates that the default system preferences are
		to be accessed.
		A string that starts with a leading "/" character specifies
		the absolute path to the file containing the preferences to
		be accessed.
		A string that does not start with a leading "/" character
		specifies a file relative to the default system preferences
		directory.

		When you are finished with the preferences session, use
		CFRelease to close it.
 */


/*!
	@typedef SCPreferencesRef
	@discussion This is the handle to an open preferences session for
		accessing system configuration preferences.
 */
typedef const struct CF_BRIDGED_TYPE(id) __SCPreferences *	SCPreferencesRef;

/*!
	@enum SCPreferencesNotification
	@discussion Used with the SCPreferencesCallBack callback
		to describe the type of notification.
	@constant kSCPreferencesNotificationCommit Indicates when new
		preferences have been saved.
	@constant kSCPreferencesNotificationApply Key Indicates when a
		request has been made to apply the currently saved
		preferences to the active system configuration.
 */
typedef CF_OPTIONS(uint32_t, SCPreferencesNotification) {
	kSCPreferencesNotificationCommit	= 1<<0,	// __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA)
	kSCPreferencesNotificationApply		= 1<<1	// __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA)
};

/*!
	@typedef SCPreferencesContext
	Structure containing user-specified data and callbacks for SCPreferences.
	@field version The version number of the structure type being passed
		in as a parameter to the SCPreferencesSetCallback function.
		This structure is version 0.
	@field info A C pointer to a user-specified block of data.
	@field retain The callback used to add a retain for the info field.
		If this parameter is not a pointer to a function of the correct
		prototype, the behavior is undefined.
		The value may be NULL.
	@field release The calllback used to remove a retain previously added
		for the info field.
		If this parameter is not a pointer to a function of the
		correct prototype, the behavior is undefined.
		The value may be NULL.
	@field copyDescription The callback used to provide a description of
		the info field.
 */
typedef struct {
	CFIndex		version;
	void *		__nullable info;
	const void	* __nonnull (* __nullable retain)(const void *info);
	void		(* __nullable release)(const void *info);
	CFStringRef	__nonnull (* __nullable copyDescription)(const void *info);
} SCPreferencesContext;

/*!
	@typedef SCPreferencesCallBack
	@discussion Type of the callback function used when the
		preferences have been updated and/or applied.
	@param prefs The preferences session.
	@param notificationType The type of notification, such as changes
		committed, changes applied, etc.
	@param info A C pointer to a user-specified block of data.
 */
typedef void (*SCPreferencesCallBack)   (
					SCPreferencesRef				prefs,
					SCPreferencesNotification			notificationType,
					void			     *	__nullable	info
					);


__BEGIN_DECLS

/*!
	@function SCPreferencesGetTypeID
	@discussion Returns the type identifier of all SCPreferences instances.
 */
CFTypeID
SCPreferencesGetTypeID			(void)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCPreferencesCreate
	@discussion Initiates access to the per-system set of configuration
		preferences.
	@param allocator The CFAllocator that should be used to allocate
		memory for this preferences session.
		This parameter may be NULL in which case the current
		default CFAllocator is used.
		If this reference is not a valid CFAllocator, the behavior
		is undefined.
	@param name A string that describes the name of the calling
		process.
	@param prefsID A string that identifies the name of the
		group of preferences to be accessed or updated.
	@result Returns a reference to the new SCPreferences.
		You must release the returned value.
 */
SCPreferencesRef __nullable
SCPreferencesCreate			(
					CFAllocatorRef		__nullable	allocator,
					CFStringRef				name,
					CFStringRef		__nullable	prefsID
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);


/*!
	@function SCPreferencesCreateWithAuthorization
	@discussion Initiates access to the per-system set of configuration
		preferences.
	@param allocator The CFAllocator that should be used to allocate
		memory for this preferences session.
		This parameter may be NULL in which case the current
		default CFAllocator is used.
		If this reference is not a valid CFAllocator, the behavior
		is undefined.
	@param name A string that describes the name of the calling
		process.
	@param prefsID A string that identifies the name of the
		group of preferences to be accessed or updated.
	@param authorization An authorization reference that is used to
		authorize any access to the enhanced privileges needed
		to manage the preferences session.
	@result Returns a reference to the new SCPreferences.
		You must release the returned value.
 */
SCPreferencesRef __nullable
SCPreferencesCreateWithAuthorization	(
					CFAllocatorRef		__nullable	allocator,
					CFStringRef				name,
					CFStringRef		__nullable	prefsID,
					AuthorizationRef	__nullable	authorization
					)			__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCPreferencesLock
	@discussion Locks access to the configuration preferences.

		This function obtains exclusive access to the configuration
		preferences.  Clients attempting to obtain exclusive access
		to the preferences will either receive a kSCStatusPrefsBusy
		error or block waiting for the lock to be released.
	@param prefs The preferences session.
	@param wait A boolean flag indicating whether the calling process
		should block waiting for another process to complete its update
		operation and release its lock.
	@result Returns TRUE if the lock was obtained;
		FALSE if an error occurred.
 */
Boolean
SCPreferencesLock			(
					SCPreferencesRef	prefs,
					Boolean			wait
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCPreferencesCommitChanges
	@discussion Commits changes made to the configuration preferences to
		persistent storage.

		This function commits any changes to permanent storage.
		Implicit calls to the SCPreferencesLock and SCPreferencesUnlock
		functions will be made if exclusive access has not already been
		established.

		Note: This routine commits changes to persistent storage.
		Call the SCPreferencesApplyChanges function to apply the
		changes to the running system.
	@param prefs The preferences session.
	@result Returns TRUE if the lock was obtained;
		FALSE if an error occurred.
 */
Boolean
SCPreferencesCommitChanges		(
					SCPreferencesRef	prefs
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCPreferencesApplyChanges
	@discussion Requests that the currently stored configuration
		preferences be applied to the active configuration.
	@param prefs The preferences session.
	@result Returns TRUE if the lock was obtained;
		FALSE if an error occurred.
 */
Boolean
SCPreferencesApplyChanges		(
					SCPreferencesRef	prefs
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCPreferencesUnlock
	@discussion Releases exclusive access to the configuration preferences.

		This function releases the exclusive access lock to the
		preferences.  Other clients will be now be able to establish
		exclusive access to the preferences.
	@param prefs The preferences session.
	@result Returns TRUE if the lock was obtained;
		FALSE if an error occurred.
 */
Boolean
SCPreferencesUnlock			(
					SCPreferencesRef	prefs
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCPreferencesGetSignature
	@discussion Returns a sequence of bytes that can be used to determine
		if the saved configuration preferences have changed.
	@param prefs The preferences session.
	@result Returns a CFDataRef that reflects the signature of the configuration
		preferences at the time of the call to the SCPreferencesCreate function.
 */
CFDataRef __nullable
SCPreferencesGetSignature		(
					SCPreferencesRef	prefs
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCPreferencesCopyKeyList
	@discussion Returns an array of currently defined preference keys.
	@param prefs The preferences session.
	@result Returns the list of keys.
		You must release the returned value.
 */
CFArrayRef __nullable
SCPreferencesCopyKeyList		(
					SCPreferencesRef	prefs
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCPreferencesGetValue
	@discussion Returns the data associated with a preference key.

		This function retrieves data associated with the specified
		key.

		Note: To avoid inadvertantly reading stale data, first call
		the SCPreferencesLock function.
	@param prefs The preferences session.
	@param key The preference key to be returned.
	@result Returns the value associated with the specified preference key;
		NULL if no value was located.
 */
CFPropertyListRef __nullable
SCPreferencesGetValue			(
					SCPreferencesRef	prefs,
					CFStringRef		key
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCPreferencesAddValue
	@discussion Adds data for a preference key.

		This function associates new data with the specified key.
		To commit these changes to permanent storage, a call must
		be made to the SCPreferencesCommitChanges function.
	@param prefs The preferences session.
	@param key The preference key to be updated.
	@param value The CFPropertyListRef object containing the
		value to be associated with the specified preference key.
	@result Returns TRUE if the value was added;
		FALSE if the key already exists or
		if an error occurred.
 */
Boolean
SCPreferencesAddValue			(
					SCPreferencesRef	prefs,
					CFStringRef		key,
					CFPropertyListRef	value
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCPreferencesSetValue
	@discussion Updates the data associated with a preference key.

		This function adds or replaces the value associated with the
		specified key.  To commit these changes to permanent storage
		a call must be made to the SCPreferencesCommitChanges function.
	@param prefs The preferences session.
	@param key The preference key to be updated.
	@param value The CFPropertyListRef object containing the
		data to be associated with the specified preference key.
	@result Returns TRUE if the value was set;
		FALSE if an error occurred.
 */
Boolean
SCPreferencesSetValue			(
					SCPreferencesRef	prefs,
					CFStringRef		key,
					CFPropertyListRef	value
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCPreferencesRemoveValue
	@discussion Removes the data associated with a preference key.

		This function removes the data associated with the specified
		key.  To commit these changes to permanent storage a call must
		be made to the SCPreferencesCommitChanges function.
	@param prefs The preferences session.
	@param key The preference key to be removed.
	@result Returns TRUE if the value was removed;
		FALSE if the key did not exist or if an error occurred.
 */
Boolean
SCPreferencesRemoveValue		(
					SCPreferencesRef	prefs,
					CFStringRef		key
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCPreferencesSetCallback
	@discussion Assigns a callback to a preferences session.  The function
		is called when the changes to the preferences have been
		committed or applied.
	@param prefs The preferences session.
	@param callout The function to be called when the preferences have
		been changed or applied.
		If NULL, the current callback is removed.
	@param context The SCPreferencesContext associated with
		the callout.
	@result Returns TRUE if the notification client was successfully set.
 */
Boolean
SCPreferencesSetCallback		(
					SCPreferencesRef			prefs,
					SCPreferencesCallBack	__nullable	callout,
					SCPreferencesContext	* __nullable	context
					)			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCPreferencesScheduleWithRunLoop
	@discussion Schedule commit and apply notifications for the specified
		preferences session using the specified run loop and mode.
	@param prefs The preferences session.
	@param runLoop A reference to a run loop on which the notification
		should be scheduled.
		Must be non-NULL.
	@param runLoopMode The mode on which to schedule the notification.
		Must be non-NULL.
	@result Returns TRUE if the notifications are successfully scheduled;
		FALSE otherwise.
 */
Boolean
SCPreferencesScheduleWithRunLoop	(
					SCPreferencesRef	prefs,
					CFRunLoopRef		runLoop,
					CFStringRef		runLoopMode
					)			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCPreferencesUnscheduleFromRunLoop
	@discussion Unschedule commit and apply notifications for the specified
		preferences session from the specified run loop and mode.
	@param prefs The preferences session.
	@param runLoop A reference to a run loop from which the notification
		should be unscheduled.
		Must be non-NULL.
	@param runLoopMode The mode on which to unschedule the notification.
		Must be non-NULL.
	@result Returns TRUE if the notifications are successfully unscheduled;
		FALSE otherwise.
 */
Boolean
SCPreferencesUnscheduleFromRunLoop	(
					SCPreferencesRef	prefs,
					CFRunLoopRef		runLoop,
					CFStringRef		runLoopMode
					)			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCPreferencesSetDispatchQueue
	@discussion Schedule commit and apply notifications for the specified
		preferences session.
	@param prefs The preferences session.
	@param queue The dispatch queue to run the callback function on.
	@result Returns TRUE if the notifications are successfully scheduled;
		FALSE otherwise.
 */
Boolean
SCPreferencesSetDispatchQueue		(
					 SCPreferencesRef			prefs,
					 dispatch_queue_t	__nullable	queue
					 )			__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*!
	@function SCPreferencesSynchronize
	@discussion Synchronizes accessed preferences with committed changes.

		Any references to preference values returned by calls to the
		SCPreferencesGetValue function are no longer valid unless they
		were explicitly retained or copied.  Any preference values
		that were updated (add, set, remove) but not committed will
		be discarded.
	@param prefs The preferences session.
 */
void
SCPreferencesSynchronize		(
					SCPreferencesRef	prefs
					)			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

__END_DECLS

CF_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#endif /* _SCPREFERENCES_H */
// ==========  SystemConfiguration.framework/Headers/SCDynamicStoreCopyDHCPInfo.h
/*
 * Copyright (c) 2001, 2002, 2004, 2005, 2008, 2012, 2015 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _SCDYNAMICSTORECOPYDHCPINFO_H
#ifdef	USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS
#include <SystemConfiguration/_SCDynamicStoreCopyDHCPInfo.h>
#else	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#define _SCDYNAMICSTORECOPYDHCPINFO_H

#include <Availability.h>
#include <sys/cdefs.h>
#include <CoreFoundation/CoreFoundation.h>
#include <SystemConfiguration/SCDynamicStore.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_ASSUME_NONNULL_BEGIN

/*!
	@header SCDynamicStoreCopyDHCPInfo
	@discussion The functions of the SCDynamicStoreCopyDHCPInfo API
		provide access to information returned by the DHCP or
		BOOTP server.
 */


__BEGIN_DECLS

/*!
	@function SCDynamicStoreCopyDHCPInfo
	@discussion Copies the DHCP information for the requested serviceID,
		or the primary service if serviceID == NULL.
	@param store An SCDynamicStoreRef representing the dynamic store session
		that should be used for communication with the server.
		If NULL, a temporary session will be used.
	@param serviceID A CFStringRef containing the requested service.
		If NULL, returns information for the primary service.
	@result Returns a dictionary containing DHCP information if successful;
		NULL otherwise.
		Use the DHCPInfoGetOption function to retrieve
		individual options from the returned dictionary.

		A non-NULL return value must be released using CFRelease().
 */
CFDictionaryRef __nullable
SCDynamicStoreCopyDHCPInfo	(SCDynamicStoreRef	__nullable	store,
				 CFStringRef		__nullable	serviceID)	__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function DHCPInfoGetOptionData
	@discussion Returns a non-NULL CFDataRef containing the DHCP
		option data, if present.
	@param info The non-NULL DHCP information dictionary returned by
		calling SCDynamicStoreCopyDHCPInfo.
	@param code The DHCP option code (see RFC 2132) to return
		data for.
	@result Returns a non-NULL CFDataRef containing the option data;
		NULL if the requested option data is not present.

		The return value must NOT be released.
 */
CFDataRef __nullable
DHCPInfoGetOptionData		(CFDictionaryRef	info,
				 UInt8			code)		__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function DHCPInfoGetLeaseStartTime
	@discussion Returns a CFDateRef corresponding to the lease start time,
		if present.
	@param info The non-NULL DHCP information dictionary returned by
		calling SCDynamicStoreCopyDHCPInfo.
	@result Returns a non-NULL CFDateRef if lease start time information is
		present; NULL if the information is not present or if the
		configuration method is not DHCP.

		The return value must NOT be released.
 */
CFDateRef __nullable
DHCPInfoGetLeaseStartTime	(CFDictionaryRef	info)		__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);


/*!
	@function DHCPInfoGetLeaseExpirationTime
	@discussion Returns a CFDateRef corresponding to the lease expiration time,
		if present.
	@param info The non-NULL DHCP information dictionary returned by
		calling SCDynamicStoreCopyDHCPInfo.
	@result Returns a non-NULL CFDateRef if the DHCP lease has an expiration;
		NULL if the lease is infinite i.e. has no expiration, or the
		configuration method is not DHCP. An infinite lease can be determined
		by a non-NULL lease start time (see DHCPInfoGetLeaseStartTime above).

		The return value must NOT be released.
*/
CFDateRef __nullable
DHCPInfoGetLeaseExpirationTime	(CFDictionaryRef	info)		__OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_NA);

__END_DECLS

CF_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#endif	/* _SCDYNAMICSTORECOPYDHCPINFO_H */
// ==========  SystemConfiguration.framework/Headers/SCPreferencesPath.h
/*
 * Copyright (c) 2000, 2001, 2004, 2005, 2008, 2015 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _SCPREFERENCESPATH_H
#ifdef	USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS
#include <SystemConfiguration/_SCPreferencesPath.h>
#else	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#define _SCPREFERENCESPATH_H

#include <Availability.h>
#include <sys/cdefs.h>
#include <CoreFoundation/CoreFoundation.h>
#include <SystemConfiguration/SCPreferences.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_ASSUME_NONNULL_BEGIN

/*!
	@header SCPreferencesPath
	@discussion The SCPreferencesPath API allows an application to
		load and store XML configuration data in a controlled
		manner and provide the necessary notifications to other
		applications that need to be aware of configuration
		changes.

		The functions in the SCPreferencesPath API make certain
		assumptions about the layout of the preferences data.
		These functions view the data as a collection of dictionaries
		of key-value pairs and an associated path name.
		The root path ("/") identifies the top-level dictionary.
		Additional path components specify the keys for subdictionaries.

		For example, the following dictionary can be accessed via
		two paths.  The root ("/") path would return a dictionary
		with all keys and values.  The path "/path1" would only
		return the dictionary with the "key3" and "key4" properties.

	<pre>
	@textblock
	<dict>
		<key>key1</key>
		<string>val1</string>
		<key>key2</key>
		<string>val2</string>
		<key>path1</key>
		<dict>
			<key>key3</key>
			<string>val3</string>
			<key>key4</key>
			<string>val4</string>
		</dict>
	</dict>
	@/textblock
	</pre>

	Each dictionary can also include the kSCResvLink ("__LINK__") key.
	The value associated with this key is interpreted as a link to
	another path.  If this key is present, a call to the
	SCPreferencesPathGetValue function returns the dictionary
	specified by the link.
 */


__BEGIN_DECLS

/*!
	@function SCPreferencesPathCreateUniqueChild
	@discussion Creates a new path component within the dictionary
		hierarchy.
	@param prefs The preferences session.
	@param prefix A string that represents the parent path.
	@result Returns a string representing the new (unique) child path; NULL
		if the specified path does not exist.
 */
CFStringRef __nullable
SCPreferencesPathCreateUniqueChild	(
					SCPreferencesRef	prefs,
					CFStringRef		prefix
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCPreferencesPathGetValue
	@discussion Returns the dictionary associated with the specified
		path.
	@param prefs The preferences session.
	@param path A string that represents the path to be returned.
	@result Returns the dictionary associated with the specified path; NULL
		if the path does not exist.
 */
CFDictionaryRef __nullable
SCPreferencesPathGetValue		(
					SCPreferencesRef	prefs,
					CFStringRef		path
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCPreferencesPathGetLink
	@discussion Returns the link (if one exists) associated with the
		specified path.
	@param prefs The preferences session.
	@param path A string that represents the path to be returned.
	@result Returns the dictionary associated with the specified path; NULL
		if the path is not a link or does not exist.
 */
CFStringRef __nullable
SCPreferencesPathGetLink		(
					SCPreferencesRef	prefs,
					CFStringRef		path
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCPreferencesPathSetValue
	@discussion Associates a dictionary with the specified path.
	@param prefs The preferences session.
	@param path A string that represents the path to be updated.
	@param value A dictionary that represents the data to be
		stored at the specified path.
	@result Returns TRUE if successful; FALSE otherwise.
 */
Boolean
SCPreferencesPathSetValue		(
					SCPreferencesRef	prefs,
					CFStringRef		path,
					CFDictionaryRef		value
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCPreferencesPathSetLink
	@discussion Associates a link to a second dictionary at the
		specified path.
	@param prefs The preferences session.
	@param path A string that represents the path to be updated.
	@param link A string that represents the link to be stored
		at the specified path.
	@result Returns TRUE if successful; FALSE otherwise.
 */
Boolean
SCPreferencesPathSetLink		(
					SCPreferencesRef	prefs,
					CFStringRef		path,
					CFStringRef		link
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCPreferencesPathRemoveValue
	@discussion Removes the data associated with the specified path.
	@param prefs The preferences session.
	@param path A string that represents the path to be returned.
	@result Returns TRUE if successful; FALSE otherwise.
 */
Boolean
SCPreferencesPathRemoveValue		(
					SCPreferencesRef	prefs,
					CFStringRef		path
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

__END_DECLS

CF_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#endif /* _SCPREFERENCESPATH_H */
// ==========  SystemConfiguration.framework/Headers/SCNetwork.h
/*
 * Copyright (c) 2000, 2001, 2003-2009, 2015 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _SCNETWORK_H
#define _SCNETWORK_H

#include <Availability.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <CoreFoundation/CoreFoundation.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_ASSUME_NONNULL_BEGIN

/*!
	@header SCNetwork
	@discussion The SCNetwork API contains functions an application can
		use to determine remote host reachability and notify the
		system of configuration changes.

		The two SCNetworkCheckReachability functions allow an
		application to determine the status of the system's current
		network configuration and the reachability of a target host
		or address.

		"Reachability" reflects whether a data packet, sent by an
		application into the network stack, can leave the local
		computer.  Note that reachability does <i>not</i> guarantee
		that the data packet will actually be received by the host.
 */

/*!
	@enum SCNetworkConnectionFlags
	@discussion Flags that indicate whether the specified network
		nodename or address is reachable, whether a connection is
		required, and whether some user intervention may be required
		when establishing a connection.

		Note: the SCNetworkConnection flags have been deprecated
		in favor of the newer SCNetworkReachability flags defined
		in SCNetworkReachability.h.
	@constant kSCNetworkFlagsTransientConnection
		This flag indicates that the specified nodename or address can
		be reached via a transient connection, such as PPP.
	@constant kSCNetworkFlagsReachable
		This flag indicates that the specified nodename or address can
		be reached using the current network configuration.
	@constant kSCNetworkFlagsConnectionRequired
		This flag indicates that the specified nodename or address can
		be reached using the current network configuration, but a
		connection must first be established.

		As an example, this status would be returned for a dialup
		connection that was not currently active, but could handle
		network traffic for the target system.
	@constant kSCNetworkFlagsConnectionAutomatic
		This flag indicates that the specified nodename or address can
		be reached using the current network configuration, but a
		connection must first be established.  Any traffic directed
		to the specified name or address will initiate the connection.
	@constant kSCNetworkFlagsInterventionRequired
		This flag indicates that the specified nodename or address can
		be reached using the current network configuration, but a
		connection must first be established.  In addition, some
		form of user intervention will be required to establish this
		connection, such as providing a password, an authentication
		token, etc.

		Note: At the present time, this flag will only be returned
		in the case where you have a dial-on-traffic configuration
		(ConnectionAutomatic), where an attempt to connect has
		already been made, and where some error (e.g. no dial tone,
		no answer, bad password, ...) was encountered during the
		automatic connection attempt.  In this case the PPP controller
		will stop attempting to establish a connection until the user
		has intervened.
	@constant kSCNetworkFlagsIsLocalAddress
		This flag indicates that the specified nodename or address
		is one associated with a network interface on the current
		system.
	@constant kSCNetworkFlagsIsDirect
		This flag indicates that network traffic to the specified
		nodename or address will not go through a gateway, but is
		routed directly to one of the interfaces in the system.
 */
enum {
	kSCNetworkFlagsTransientConnection	= 1<<0,
	kSCNetworkFlagsReachable		= 1<<1,
	kSCNetworkFlagsConnectionRequired	= 1<<2,
	kSCNetworkFlagsConnectionAutomatic	= 1<<3,
	kSCNetworkFlagsInterventionRequired	= 1<<4,
	kSCNetworkFlagsIsLocalAddress		= 1<<16,
	kSCNetworkFlagsIsDirect			= 1<<17,
};
typedef	uint32_t	SCNetworkConnectionFlags;

__BEGIN_DECLS

/*!
	@function SCNetworkCheckReachabilityByAddress
	@discussion Determines if the given network address is
		reachable using the current network configuration.

		Note: this API has been deprecated but you can
		      get equivalent results with :
<pre>
	SCNetworkReachabiltyRef   target;
	SCNetworkReachabiltyFlags flags = 0;
	Boolean                   ok;

	target = SCNetworkReachabilityCreateWithAddress(NULL, address);
	ok = SCNetworkReachabilityGetFlags(target, &flags);
	CFRelease(target);
</pre>
	@param address The network address of the desired host.
	@param addrlen The length, in bytes, of the address.
	@param flags A pointer to memory that will be filled with a
		set of SCNetworkConnectionFlags detailing the reachability
		of the specified address.
	@result Returns TRUE if the network connection flags are valid;
		FALSE if the status could not be determined.
 */
Boolean
SCNetworkCheckReachabilityByAddress	(
					const struct sockaddr		*address,
					socklen_t			addrlen,
					SCNetworkConnectionFlags	*flags
					)				__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);

/*!
	@function SCNetworkCheckReachabilityByName
	@discussion Determines if the given network host or node name is
		reachable using the current network configuration.

		Note: this API has been deprecated but you can
		      get equivalent results with :
<pre>
	SCNetworkReachabilityRef   target;
	SCNetworkReachabilityFlags flags = 0;
	Boolean                   ok;

	target = SCNetworkReachabilityCreateWithName(NULL, name);
	ok = SCNetworkReachabilityGetFlags(target, &flags);
	CFRelease(target);
</pre>
	@param nodename The node name of the desired host. This name would
		be the same as that passed to the gethostbyname(3) or
		getaddrinfo(3) functions.
	@param flags A pointer to memory that will be filled with a
		set of SCNetworkConnectionFlags detailing the reachability
		of the specified node name.
	@result Returns TRUE if the network connection flags are valid;
		FALSE if the status could not be determined.
 */
Boolean
SCNetworkCheckReachabilityByName	(
					const char			*nodename,
					SCNetworkConnectionFlags	*flags
					)				__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceRefreshConfiguration
	@discussion Sends a notification to interested configuration agents
		to have them immediately retry their configuration over a
		particular network interface.

		Note: This function must be invoked by root (uid == 0).
	@param ifName The BSD name of the network interface, such as
		CFSTR("en0").
	@result Returns TRUE if the notification was sent; FALSE otherwise.
	@deprecated in version 10.4. Replaced with SCNetworkInterfaceForceConfigurationRefresh.
 */
Boolean
SCNetworkInterfaceRefreshConfiguration	(
					CFStringRef			ifName
					)				__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);

__END_DECLS

CF_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* _SCNETWORK_H */
// ==========  SystemConfiguration.framework/Headers/SCNetworkConfiguration.h
/*
 * Copyright (c) 2004-2011, 2015 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _SCNETWORKCONFIGURATION_H
#ifdef	USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS
#include <SystemConfiguration/_SCNetworkConfiguration.h>
#else	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#define _SCNETWORKCONFIGURATION_H

#include <Availability.h>
#include <TargetConditionals.h>
#include <sys/cdefs.h>
#include <CoreFoundation/CoreFoundation.h>
#include <SystemConfiguration/SystemConfiguration.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_ASSUME_NONNULL_BEGIN

/*!
	@header SCNetworkConfiguration
	@discussion The SCNetworkConfiguration API provides access to the
		stored network configuration.  The functions include
		providing access to the network capable devices on the
		system, the network sets, network services, and network
		protocols.

		Note: When using the SCNetworkConfiguraiton APIs you must
		keep in mind that in order for any of your changes to be
		committed to permanent storage a call must be made to the
		SCPreferencesCommitChanges function.
 */


/*!
	@group Interface configuration
 */

#pragma mark -
#pragma mark SCNetworkInterface configuration (typedefs, consts)

/*!
	@typedef SCNetworkInterfaceRef
	@discussion This is the type of a reference to an object that represents
		a network interface.
 */
typedef const struct CF_BRIDGED_TYPE(id) __SCNetworkInterface * SCNetworkInterfaceRef;

/*!
	@const kSCNetworkInterfaceType6to4
 */
extern const CFStringRef kSCNetworkInterfaceType6to4						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCNetworkInterfaceTypeBluetooth
 */
extern const CFStringRef kSCNetworkInterfaceTypeBluetooth					__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCNetworkInterfaceTypeBond
 */
extern const CFStringRef kSCNetworkInterfaceTypeBond						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCNetworkInterfaceTypeEthernet
 */
extern const CFStringRef kSCNetworkInterfaceTypeEthernet					__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCNetworkInterfaceTypeFireWire
 */
extern const CFStringRef kSCNetworkInterfaceTypeFireWire					__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCNetworkInterfaceTypeIEEE80211
 */
extern const CFStringRef kSCNetworkInterfaceTypeIEEE80211					__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);	// IEEE 802.11, AirPort

/*!
	@const kSCNetworkInterfaceTypeIPSec
 */
extern const CFStringRef kSCNetworkInterfaceTypeIPSec						__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@const kSCNetworkInterfaceTypeIrDA
 */
extern const CFStringRef kSCNetworkInterfaceTypeIrDA						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCNetworkInterfaceTypeL2TP
 */
extern const CFStringRef kSCNetworkInterfaceTypeL2TP						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCNetworkInterfaceTypeModem
 */
extern const CFStringRef kSCNetworkInterfaceTypeModem						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCNetworkInterfaceTypePPP
 */
extern const CFStringRef kSCNetworkInterfaceTypePPP						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCNetworkInterfaceTypePPTP
 */
extern const CFStringRef kSCNetworkInterfaceTypePPTP						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCNetworkInterfaceTypeSerial
 */
extern const CFStringRef kSCNetworkInterfaceTypeSerial						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCNetworkInterfaceTypeVLAN
 */
extern const CFStringRef kSCNetworkInterfaceTypeVLAN						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCNetworkInterfaceTypeWWAN
 */
extern const CFStringRef kSCNetworkInterfaceTypeWWAN						__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/* special network interfaces (and types) */

/*!
	@const kSCNetworkInterfaceTypeIPv4
 */
extern const CFStringRef kSCNetworkInterfaceTypeIPv4						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCNetworkInterfaceIPv4
	@discussion A network interface that can used for layering other
		interfaces (e.g. 6to4, IPSec, PPTP, L2TP) over an existing
		IPv4 network.
 */
extern const SCNetworkInterfaceRef kSCNetworkInterfaceIPv4					__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@group Interface configuration (Bond)
 */

#pragma mark -

/*!
	@typedef SCBondInterfaceRef
	@discussion This is the type of a reference to an object that represents
		an Ethernet Bond interface.
 */
typedef SCNetworkInterfaceRef SCBondInterfaceRef;

/*!
	@typedef SCBondStatusRef
	@discussion This is the type of a reference to an object that represents
		the status of an Ethernet Bond interface.
 */
typedef const struct CF_BRIDGED_TYPE(id) __SCBondStatus *		SCBondStatusRef;

/*!
	@enum Ethernet Bond Aggregation Status (kSCBondStatusDeviceAggregationStatus) codes
	@discussion Returned status codes.
	@constant kSCBondStatusOK		Enabled, active, running, ...
	@constant kSCBondStatusLinkInvalid	The link state was not valid (i.e. down, half-duplex, wrong speed)
	@constant kSCBondStatusNoPartner	The port on the switch that the device is connected doesn't seem to have 802.3ad Link Aggregation enabled
	@constant kSCBondStatusNotInActiveGroup	We're talking to a partner, but the link aggregation group is different from the one that's active
	@constant kSCBondStatusUnknown		Non-specific failure
 */
enum {
	kSCBondStatusOK			= 0,	/* enabled, active, running, ... */
	kSCBondStatusLinkInvalid	= 1,	/* The link state was not valid (i.e. down, half-duplex, wrong speed) */
	kSCBondStatusNoPartner		= 2,	/* The port on the switch that the device is connected doesn't seem to have 802.3ad Link Aggregation enabled */
	kSCBondStatusNotInActiveGroup	= 3,	/* We're talking to a partner, but the link aggregation group is different from the one that's active */
	kSCBondStatusUnknown		= 999	/* Non-specific failure */
};

/*!
	@const kSCBondStatusDeviceAggregationStatus
 */
extern const CFStringRef kSCBondStatusDeviceAggregationStatus	/* CFNumber */			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCBondStatusDeviceCollecting
 */
extern const CFStringRef kSCBondStatusDeviceCollecting		/* CFNumber (0 or 1) */		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCBondStatusDeviceDistributing
 */
extern const CFStringRef kSCBondStatusDeviceDistributing	/* CFNumber (0 or 1) */		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@group Interface configuration (VLAN)
 */

#pragma mark -

/*!
	@typedef SCVLANInterfaceRef
	@discussion This is the type of a reference to an object that represents
		a Virtual LAN (VLAN) interface.
 */
typedef SCNetworkInterfaceRef SCVLANInterfaceRef;


/*!
	@group Protocol configuration
 */

#pragma mark -
#pragma mark SCNetworkProtocol configuration (typedefs, consts)

/*!
	@typedef SCNetworkProtocolRef
	@discussion This is the type of a reference to an object that represents
		a network protocol.
 */
typedef const struct CF_BRIDGED_TYPE(id) __SCNetworkProtocol * SCNetworkProtocolRef;

/* network "protocol" types */

/*!
	@const kSCNetworkProtocolTypeAppleTalk
 */
extern const CFStringRef kSCNetworkProtocolTypeAppleTalk					__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_4,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);

/*!
	@const kSCNetworkProtocolTypeDNS
 */
extern const CFStringRef kSCNetworkProtocolTypeDNS						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCNetworkProtocolTypeIPv4
 */
extern const CFStringRef kSCNetworkProtocolTypeIPv4						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCNetworkProtocolTypeIPv6
 */
extern const CFStringRef kSCNetworkProtocolTypeIPv6						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCNetworkProtocolTypeProxies
 */
extern const CFStringRef kSCNetworkProtocolTypeProxies						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@const kSCNetworkProtocolTypeSMB
 */
extern const CFStringRef kSCNetworkProtocolTypeSMB						__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@group Service configuration
 */

#pragma mark -
#pragma mark SCNetworkService configuration (typedefs, consts)

/*!
	@typedef SCNetworkServiceRef
	@discussion This is the type of a reference to an object that represents
		a network service.
 */
typedef const struct CF_BRIDGED_TYPE(id) __SCNetworkService * SCNetworkServiceRef;


/*!
	@group Set configuration
 */

#pragma mark -
#pragma mark SCNetworkSet configuration (typedefs, consts)

/*!
	@typedef SCNetworkSetRef
	@discussion This is the type of a reference to an object that represents
		a network set.
 */
typedef const struct CF_BRIDGED_TYPE(id) __SCNetworkSet	* SCNetworkSetRef;


__BEGIN_DECLS


/* --------------------------------------------------------------------------------
 * INTERFACES
 * -------------------------------------------------------------------------------- */

/*!
	@group Interface configuration
 */

#pragma mark -
#pragma mark SCNetworkInterface configuration (APIs)

/*!
	@function SCNetworkInterfaceGetTypeID
	@discussion Returns the type identifier of all SCNetworkInterface instances.
 */
CFTypeID
SCNetworkInterfaceGetTypeID			(void)						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceCopyAll
	@discussion Returns all network capable interfaces on the system.
	@result The list of interfaces on the system.
		You must release the returned value.
 */
CFArrayRef /* of SCNetworkInterfaceRef's */
SCNetworkInterfaceCopyAll			(void)						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceGetSupportedInterfaceTypes
	@discussion Identify all of the network interface types (e.g. PPP) that
		can be layered on top of this interface.
	@param interface The network interface.
	@result The list of SCNetworkInterface types supported by the interface;
		NULL if no interface types are supported.
 */
CFArrayRef /* of kSCNetworkInterfaceTypeXXX CFStringRef's */ __nullable
SCNetworkInterfaceGetSupportedInterfaceTypes	(SCNetworkInterfaceRef		interface)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceGetSupportedProtocolTypes
	@discussion Identify all of the network protocol types (e.g. IPv4, IPv6) that
		can be layered on top of this interface.
	@param interface The network interface.
	@result The list of SCNetworkProtocol types supported by the interface;
		NULL if no protocol types are supported.
 */
CFArrayRef /* of kSCNetworkProtocolTypeXXX CFStringRef's */ __nullable
SCNetworkInterfaceGetSupportedProtocolTypes	(SCNetworkInterfaceRef		interface)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceCreateWithInterface
	@discussion Create a new network interface layered on top of another.  For
		example, this function would be used to create a "PPP" interface
		on top of a "modem".
	@param interface The network interface.
	@param interfaceType The type of SCNetworkInterface to be layered on
		top of the provided interface.
	@result A reference to the new SCNetworkInterface.
		You must release the returned value.
 */
SCNetworkInterfaceRef __nullable
SCNetworkInterfaceCreateWithInterface		(SCNetworkInterfaceRef		interface,
						 CFStringRef			interfaceType)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceGetBSDName
	@discussion Returns the BSD interface (en0) or device name (modem)
		for the interface.
	@param interface The network interface.
	@result The BSD name associated with the interface (e.g. "en0");
		NULL if no BSD name is available.
 */
CFStringRef __nullable
SCNetworkInterfaceGetBSDName			(SCNetworkInterfaceRef		interface)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceGetConfiguration
	@discussion Returns the configuration settings associated with a interface.
	@param interface The network interface.
	@result The configuration settings associated with the interface;
		NULL if no configuration settings are associated with the interface
		or an error was encountered.
 */
CFDictionaryRef __nullable
SCNetworkInterfaceGetConfiguration		(SCNetworkInterfaceRef		interface)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceGetExtendedConfiguration
	@discussion Returns the configuration settings associated with a interface.
	@param interface The network interface.
	@param extendedType A string representing the type of extended information (e.g. EAPOL).
	@result The configuration settings associated with the interface;
		NULL if no configuration settings are associated with the interface
		or an error was encountered.
 */
CFDictionaryRef __nullable
SCNetworkInterfaceGetExtendedConfiguration	(SCNetworkInterfaceRef		interface,
						 CFStringRef			extendedType)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceGetHardwareAddressString
	@discussion Returns a displayable link layer address for the interface.
	@param interface The network interface.
	@result A string representing the hardware (MAC) address for the interface.
 */
CFStringRef __nullable
SCNetworkInterfaceGetHardwareAddressString	(SCNetworkInterfaceRef		interface)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceGetInterface
	@discussion For layered network interfaces, return the underlying interface.
	@param interface The network interface.
	@result The underlying network interface;
		NULL if this is a leaf interface.
 */
SCNetworkInterfaceRef __nullable
SCNetworkInterfaceGetInterface			(SCNetworkInterfaceRef		interface)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceGetInterfaceType
	@discussion Returns the associated network interface type.
	@param interface The network interface.
	@result The interface type.
 */
CFStringRef __nullable
SCNetworkInterfaceGetInterfaceType		(SCNetworkInterfaceRef		interface)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceGetLocalizedDisplayName
	@discussion Returns the localized name (e.g. "Ethernet", "FireWire") for
		the interface.
	@param interface The network interface.
	@result A localized, display name for the interface;
		NULL if no name is available.
 */
CFStringRef __nullable
SCNetworkInterfaceGetLocalizedDisplayName	(SCNetworkInterfaceRef		interface)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceSetConfiguration
	@discussion Stores the configuration settings for the interface.
	@param interface The network interface.
	@param config The configuration settings to associate with this interface.
	@result TRUE if the configuration was stored; FALSE if an error was encountered.
 */
Boolean
SCNetworkInterfaceSetConfiguration		(SCNetworkInterfaceRef		interface,
						 CFDictionaryRef		config)		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceSetExtendedConfiguration
	@discussion Stores the configuration settings for the interface.
	@param interface The network interface.
	@param config The configuration settings to associate with this interface.
	@result TRUE if the configuration was stored; FALSE if an error was encountered.
 */
Boolean
SCNetworkInterfaceSetExtendedConfiguration	(SCNetworkInterfaceRef		interface,
						 CFStringRef			extendedType,
						 CFDictionaryRef		config)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

#pragma mark -

/*!
	@function SCNetworkInterfaceCopyMediaOptions
	@discussion For the specified network interface, returns information
		about the currently requested media options, the active media
		options, and the media options which are available.
	@param interface The desired network interface.
	@param current A pointer to memory that will be filled with a CFDictionaryRef
		representing the currently requested media options (subtype, options).
		If NULL, the current options will not be returned.
	@param active A pointer to memory that will be filled with a CFDictionaryRef
		representing the active media options (subtype, options).
		If NULL, the active options will not be returned.
	@param available A pointer to memory that will be filled with a CFArrayRef
		representing the possible media options (subtype, options).
		If NULL, the available options will not be returned.
	@param filter A boolean indicating whether the available options should be
		filtered to exclude those options which would not normally be
		requested by a user/admin (e.g. hw-loopback).
	@result TRUE if requested information has been returned.
 */
Boolean
SCNetworkInterfaceCopyMediaOptions		(SCNetworkInterfaceRef						interface,
						 CFDictionaryRef		__nullable	* __nullable	current,
						 CFDictionaryRef		__nullable	* __nullable	active,
						 CFArrayRef			__nullable	* __nullable	available,
						 Boolean					filter)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceCopyMediaSubTypes
	@discussion For the provided interface configuration options, return a list
		of available media subtypes.
	@param available The available options as returned by the
		SCNetworkInterfaceCopyMediaOptions function.
	@result An array of available media subtypes CFString's (e.g. 10BaseT/UTP,
		100baseTX, etc).  NULL if no subtypes are available.
 */
CFArrayRef __nullable
SCNetworkInterfaceCopyMediaSubTypes		(CFArrayRef			available)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceCopyMediaSubTypeOptions
	@discussion For the provided interface configuration options and specific
		subtype, return a list of available media options.
	@param available The available options as returned by the
		SCNetworkInterfaceCopyMediaOptions function.
	@param subType The subtype
	@result An array of available media options.  Each of the available options
		is returned as an array of CFString's (e.g. <half-duplex>,
		<full-duplex,flow-control>).  NULL if no options are available.
 */
CFArrayRef __nullable
SCNetworkInterfaceCopyMediaSubTypeOptions	(CFArrayRef			available,
						 CFStringRef			subType)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceCopyMTU
	@discussion For the specified network interface, returns information
		about the currently MTU setting and the range of allowable
		values.
	@param interface The desired network interface.
	@param mtu_cur A pointer to memory that will be filled with the current
		MTU setting for the interface.
	@param mtu_min A pointer to memory that will be filled with the minimum
		MTU setting for the interface.  If negative, the minimum setting
		could not be determined.
	@param mtu_max A pointer to memory that will be filled with the maximum
		MTU setting for the interface.  If negative, the maximum setting
		could not be determined.
	@result TRUE if requested information has been returned.
 */
Boolean
SCNetworkInterfaceCopyMTU			(SCNetworkInterfaceRef				interface,
						 int				* __nullable	mtu_cur,
						 int				* __nullable	mtu_min,
						 int				* __nullable	mtu_max)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceSetMediaOptions
	@discussion For the specified network interface, sets the requested
		media subtype and options.
	@param interface The desired network interface.
	@param subtype The desired media subtype (e.g. "autoselect", "100baseTX", ...).
	@param options The desired media options (e.g. "half-duplex", "full-duplex", ...).
	@result TRUE if the configuration was updated; FALSE if an error was encountered.
 */
Boolean
SCNetworkInterfaceSetMediaOptions		(SCNetworkInterfaceRef		interface,
						 CFStringRef			subtype,
						 CFArrayRef			options)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceSetMTU
	@discussion For the specified network interface, sets the
		requested MTU setting.
	@param interface The desired network interface.
	@param mtu The desired MTU setting for the interface.
	@result TRUE if the configuration was updated; FALSE if an error was encountered.
 */
Boolean
SCNetworkInterfaceSetMTU			(SCNetworkInterfaceRef		interface,
						 int				mtu)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCNetworkInterfaceForceConfigurationRefresh
	@discussion Sends a notification to interested network configuration
		agents to immediately retry their configuration. For example,
		calling this function will cause the DHCP client to contact
		the DHCP server immediately rather than waiting until its
		timeout has expired.  The utility of this function is to
		allow the caller to give a hint to the system that the
		network infrastructure or configuration has changed.

		Note: This function requires root (euid==0) privilege or,
		alternatively, you may pass an SCNetworkInterface which
		is derived from a sequence of calls to :

			SCPreferencesCreateWithAuthorization
			SCNetworkSetCopy...
			SCNetworkServiceGetInterface
	@param interface The desired network interface.
	@result Returns TRUE if the notification was sent; FALSE otherwise.
 */
Boolean
SCNetworkInterfaceForceConfigurationRefresh	(SCNetworkInterfaceRef		interface)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@group Interface configuration (Bond)
 */

#pragma mark -
#pragma mark SCBondInterface configuration (APIs)

/*!
	@function SCBondInterfaceCopyAll
	@discussion Returns all Ethernet Bond interfaces on the system.
	@param prefs The "preferences" session.
	@result The list of Ethernet Bond interfaces on the system.
		You must release the returned value.
 */
CFArrayRef /* of SCBondInterfaceRef's */
SCBondInterfaceCopyAll				(SCPreferencesRef		prefs)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCBondInterfaceCopyAvailableMemberInterfaces
	@discussion Returns all network capable devices on the system
		that can be added to an Ethernet Bond interface.
	@param prefs The "preferences" session.
	@result The list of interfaces.
		You must release the returned value.
 */
CFArrayRef /* of SCNetworkInterfaceRef's */
SCBondInterfaceCopyAvailableMemberInterfaces	(SCPreferencesRef		prefs)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCBondInterfaceCreate
	@discussion Create a new SCBondInterface interface.
	@param prefs The "preferences" session.
	@result A reference to the new SCBondInterface.
		You must release the returned value.
 */
SCBondInterfaceRef __nullable
SCBondInterfaceCreate				(SCPreferencesRef		prefs)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCBondInterfaceRemove
	@discussion Removes the SCBondInterface from the configuration.
	@param bond The SCBondInterface interface.
	@result TRUE if the interface was removed; FALSE if an error was encountered.
 */
Boolean
SCBondInterfaceRemove				(SCBondInterfaceRef		bond)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCBondInterfaceGetMemberInterfaces
	@discussion Returns the member interfaces for the specified Ethernet Bond interface.
	@param bond The SCBondInterface interface.
	@result The list of interfaces.
 */
CFArrayRef /* of SCNetworkInterfaceRef's */ __nullable
SCBondInterfaceGetMemberInterfaces		(SCBondInterfaceRef		bond)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCBondInterfaceGetOptions
	@discussion Returns the configuration settings associated with a Ethernet Bond interface.
	@param bond The SCBondInterface interface.
	@result The configuration settings associated with the Ethernet Bond interface;
		NULL if no changes to the default configuration have been saved.
 */
CFDictionaryRef __nullable
SCBondInterfaceGetOptions			(SCBondInterfaceRef		bond)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCBondInterfaceSetMemberInterfaces
	@discussion Sets the member interfaces for the specified Ethernet Bond interface.
	@param bond The SCBondInterface interface.
	@param members The desired member interfaces.
	@result TRUE if the configuration was stored; FALSE if an error was encountered.
 */
Boolean
SCBondInterfaceSetMemberInterfaces		(SCBondInterfaceRef		bond,
						 CFArrayRef			members) /* of SCNetworkInterfaceRef's */
												__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCBondInterfaceSetLocalizedDisplayName
	@discussion Sets the localized display name for the specified Ethernet Bond interface.
	@param bond The SCBondInterface interface.
	@param newName The new display name.
	@result TRUE if the configuration was stored; FALSE if an error was encountered.
 */
Boolean
SCBondInterfaceSetLocalizedDisplayName		(SCBondInterfaceRef		bond,
						 CFStringRef			newName)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCBondInterfaceSetOptions
	@discussion Sets the configuration settings for the specified Ethernet Bond interface.
	@param bond The SCBondInterface interface.
	@param newOptions The new configuration settings.
	@result TRUE if the configuration was stored; FALSE if an error was encountered.
 */
Boolean
SCBondInterfaceSetOptions			(SCBondInterfaceRef		bond,
						 CFDictionaryRef		newOptions)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

#pragma mark -

/*!
	@function SCBondInterfaceCopyStatus
	@discussion Returns the status of the specified Ethernet Bond interface.
	@param bond The SCBondInterface interface.
	@result The status associated with the interface.
		You must release the returned value.
 */
SCBondStatusRef __nullable
SCBondInterfaceCopyStatus			(SCBondInterfaceRef	bond)			__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCBondStatusGetTypeID
	@discussion Returns the type identifier of all SCBondStatus instances.
 */
CFTypeID
SCBondStatusGetTypeID				(void)						__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCBondStatusGetMemberInterfaces
	@discussion Returns the member interfaces that are represented with the
		Ethernet Bond interface.
	@param bondStatus The Ethernet Bond status.
	@result The list of interfaces.
 */
CFArrayRef __nullable /* of SCNetworkInterfaceRef's */
SCBondStatusGetMemberInterfaces			(SCBondStatusRef	bondStatus)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCBondStatusGetInterfaceStatus
	@discussion Returns the status of a specific member interface of an
		Ethernet Bond or the status of the bond as a whole.
	@param bondStatus The Ethernet Bond status.
	@param interface The specific member interface; NULL if you want the
		status of the Ethernet Bond.
	@result The interface status.

	Note: at present, no information about the status of the Ethernet
	      Bond is returned.  As long as one member interface is active
	      then the bond should be operational.
 */
CFDictionaryRef __nullable
SCBondStatusGetInterfaceStatus			(SCBondStatusRef			bondStatus,
						 SCNetworkInterfaceRef	__nullable	interface)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@group Interface configuration (VLAN)
 */

#pragma mark -
#pragma mark SCVLANInterface configuration (APIs)

/*!
	@function SCVLANInterfaceCopyAll
	@discussion Returns all VLAN interfaces on the system.
	@result The list of VLAN interfaces on the system.
		You must release the returned value.
 */
CFArrayRef /* of SCVLANInterfaceRef's */
SCVLANInterfaceCopyAll				(SCPreferencesRef		prefs)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCVLANInterfaceCopyAvailablePhysicalInterfaces
	@discussion Returns the network capable devices on the system
		that can be associated with a VLAN interface.
	@result The list of interfaces.
		You must release the returned value.
 */
CFArrayRef /* of SCNetworkInterfaceRef's */
SCVLANInterfaceCopyAvailablePhysicalInterfaces	(void)						__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCVLANInterfaceCreate
	@discussion Create a new SCVLANInterface interface.
	@param prefs The "preferences" session.
	@param physical The physical interface to associate with the VLAN.
	@param tag The tag to associate with the VLAN.
	@result A reference to the new SCVLANInterface.
		You must release the returned value.

	Note: the tag must be in the range (1 <= tag <= 4094)
 */
SCVLANInterfaceRef __nullable
SCVLANInterfaceCreate				(SCPreferencesRef		prefs,
						 SCNetworkInterfaceRef		physical,
						 CFNumberRef			tag)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCVLANInterfaceRemove
	@discussion Removes the SCVLANInterface from the configuration.
	@param vlan The SCVLANInterface interface.
	@result TRUE if the interface was removed; FALSE if an error was encountered.
 */
Boolean
SCVLANInterfaceRemove				(SCVLANInterfaceRef		vlan)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCVLANInterfaceGetPhysicalInterface
	@discussion Returns the physical interface for the specified VLAN interface.
	@param vlan The SCVLANInterface interface.
	@result The list of interfaces.
 */
SCNetworkInterfaceRef __nullable
SCVLANInterfaceGetPhysicalInterface		(SCVLANInterfaceRef		vlan)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCVLANInterfaceGetTag
	@discussion Returns the tag for the specified VLAN interface.
	@param vlan The SCVLANInterface interface.
	@result The tag.
 */
CFNumberRef __nullable
SCVLANInterfaceGetTag				(SCVLANInterfaceRef		vlan)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCVLANInterfaceGetOptions
	@discussion Returns the configuration settings associated with the VLAN interface.
	@param vlan The SCVLANInterface interface.
	@result The configuration settings associated with the VLAN interface;
		NULL if no changes to the default configuration have been saved.
 */
CFDictionaryRef __nullable
SCVLANInterfaceGetOptions			(SCVLANInterfaceRef		vlan)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCVLANInterfaceSetPhysicalInterfaceAndTag
	@discussion Updates the specified VLAN interface.
	@param vlan The SCVLANInterface interface.
	@param physical The physical interface to associate with the VLAN.
	@param tag The tag to associate with the VLAN.
	@result TRUE if the configuration was stored; FALSE if an error was encountered.

	Note: the tag must be in the range (1 <= tag <= 4094)
 */
Boolean
SCVLANInterfaceSetPhysicalInterfaceAndTag	(SCVLANInterfaceRef		vlan,
						 SCNetworkInterfaceRef		physical,
						 CFNumberRef			tag)		__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCVLANInterfaceSetLocalizedDisplayName
	@discussion Sets the localized display name for the specified VLAN interface.
	@param vlan The SCVLANInterface interface.
	@param newName The new display name.
	@result TRUE if the configuration was stored; FALSE if an error was encountered.
 */
Boolean
SCVLANInterfaceSetLocalizedDisplayName		(SCVLANInterfaceRef		vlan,
						 CFStringRef			newName)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCVLANInterfaceSetOptions
	@discussion Sets the configuration settings for the specified VLAN interface.
	@param vlan The SCVLANInterface interface.
	@param newOptions The new configuration settings.
	@result TRUE if the configuration was stored; FALSE if an error was encountered.
 */
Boolean
SCVLANInterfaceSetOptions			(SCVLANInterfaceRef		vlan,
						 CFDictionaryRef		newOptions)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);


/* --------------------------------------------------------------------------------
 * PROTOCOLS
 * -------------------------------------------------------------------------------- */

/*!
	@group Protocol configuration
 */

#pragma mark -
#pragma mark SCNetworkProtocol configuration (APIs)

/*!
	@function SCNetworkProtocolGetTypeID
	@discussion Returns the type identifier of all SCNetworkProtocol instances.
 */
CFTypeID
SCNetworkProtocolGetTypeID			(void)						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkProtocolGetConfiguration
	@discussion Returns the configuration settings associated with the protocol.
	@param protocol The network protocol.
	@result The configuration settings associated with the protocol;
		NULL if no configuration settings are associated with the protocol
		or an error was encountered.
 */
CFDictionaryRef __nullable
SCNetworkProtocolGetConfiguration		(SCNetworkProtocolRef		protocol)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkProtocolGetEnabled
	@discussion Returns whether this protocol has been enabled.
	@param protocol The network protocol.
	@result TRUE if the protocol is enabled.
 */
Boolean
SCNetworkProtocolGetEnabled			(SCNetworkProtocolRef		protocol)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkProtocolGetProtocolType
	@discussion Returns the associated network protocol type.
	@param protocol The network protocol.
	@result The protocol type.
 */
CFStringRef __nullable
SCNetworkProtocolGetProtocolType		(SCNetworkProtocolRef		protocol)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkProtocolSetConfiguration
	@discussion Stores the configuration settings for the protocol.
	@param protocol The network protocol.
	@param config The configuration settings to associate with this protocol.
	@result TRUE if the configuration was stored; FALSE if an error was encountered.
 */
Boolean
SCNetworkProtocolSetConfiguration		(SCNetworkProtocolRef		protocol,
						 CFDictionaryRef		config)		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkProtocolSetEnabled
	@discussion Enables or disables the protocol.
	@param protocol The network protocol.
	@param enabled TRUE if the protocol should be enabled.
	@result TRUE if the enabled status was saved; FALSE if an error was encountered.
 */
Boolean
SCNetworkProtocolSetEnabled			(SCNetworkProtocolRef		protocol,
						 Boolean			enabled)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/* --------------------------------------------------------------------------------
 * SERVICES
 * -------------------------------------------------------------------------------- */

/*!
	@group Service configuration
 */

#pragma mark -
#pragma mark SCNetworkService configuration (APIs)

/*!
	@function SCNetworkServiceGetTypeID
	@discussion Returns the type identifier of all SCNetworkService instances.
 */
CFTypeID
SCNetworkServiceGetTypeID			(void)						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkServiceAddProtocolType
	@discussion Adds a network protocol of the specified type to the
		service.  The protocal configuration is set to default values
		that are appropriate for the interface associated with the
		service.
	@param service The network service.
	@param protocolType The type of SCNetworkProtocol to be added to the service.
	@result TRUE if the protocol was added to the service; FALSE if the
		protocol was already present or an error was encountered.
 */
Boolean
SCNetworkServiceAddProtocolType			(SCNetworkServiceRef		service,
						 CFStringRef			protocolType)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkServiceCopyAll
	@discussion Returns all available network services for the specified preferences.
	@param prefs The "preferences" session.
	@result The list of SCNetworkService services associated with the preferences.
		You must release the returned value.
 */
CFArrayRef /* of SCNetworkServiceRef's */ __nullable
SCNetworkServiceCopyAll				(SCPreferencesRef		prefs)		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkServiceCopyProtocols
	@discussion Returns all network protocols associated with the service.
	@param service The network service.
	@result The list of SCNetworkProtocol protocols associated with the service.
		You must release the returned value.
 */
CFArrayRef /* of SCNetworkProtocolRef's */ __nullable
SCNetworkServiceCopyProtocols			(SCNetworkServiceRef		service)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkServiceCreate
	@discussion Create a new network service for the specified interface in the
		configuration.
	@param prefs The "preferences" session.
	@result A reference to the new SCNetworkService.
		You must release the returned value.
 */
SCNetworkServiceRef __nullable
SCNetworkServiceCreate				(SCPreferencesRef		prefs,
						 SCNetworkInterfaceRef		interface)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkServiceCopy
	@discussion Returns the network service with the specified identifier.
	@param prefs The "preferences" session.
	@param serviceID The unique identifier for the service.
	@result A reference to the SCNetworkService from the associated preferences;
		NULL if the serviceID does not exist in the preferences or if an
		error was encountered.
		You must release the returned value.
 */
SCNetworkServiceRef __nullable
SCNetworkServiceCopy				(SCPreferencesRef		prefs,
						 CFStringRef			serviceID)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkServiceEstablishDefaultConfiguration
	@discussion Establishes the "default" configuration for a network
		service.  This configuration includes the addition of
		network protocols for the service (with "default"
		configuration options).
	@param service The network service.
	@result TRUE if the configuration was updated; FALSE if an error was encountered.
*/
Boolean
SCNetworkServiceEstablishDefaultConfiguration	(SCNetworkServiceRef		service)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCNetworkServiceGetEnabled
	@discussion Returns whether this service has been enabled.
	@param service The network service.
	@result TRUE if the service is enabled.
 */
Boolean
SCNetworkServiceGetEnabled			(SCNetworkServiceRef		service)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkServiceGetInterface
	@discussion Returns the network interface associated with the service.
	@param service The network service.
	@result A reference to the SCNetworkInterface associated with the service;
		NULL if an error was encountered.
 */
SCNetworkInterfaceRef __nullable
SCNetworkServiceGetInterface			(SCNetworkServiceRef		service)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkServiceGetName
	@discussion Returns the [user specified] name associated with the service.
	@param service The network service.
	@result The [user specified] name.
 */
CFStringRef __nullable
SCNetworkServiceGetName				(SCNetworkServiceRef		service)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkServiceCopyProtocol
	@discussion Returns the network protocol of the specified type for
		the service.
	@param service The network service.
	@result A reference to the SCNetworkProtocol associated with the service;
		NULL if this protocol has not been added or if an error was encountered.
		You must release the returned value.
 */
SCNetworkProtocolRef __nullable
SCNetworkServiceCopyProtocol			(SCNetworkServiceRef		service,
						 CFStringRef			protocolType)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkServiceGetServiceID
	@discussion Returns the identifier for the service.
	@param service The network service.
	@result The service identifier.
 */
CFStringRef __nullable
SCNetworkServiceGetServiceID			(SCNetworkServiceRef		service)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkServiceRemove
	@discussion Removes the network service from the configuration.
	@param service The network service.
	@result TRUE if the service was removed; FALSE if an error was encountered.
 */
Boolean
SCNetworkServiceRemove				(SCNetworkServiceRef		service)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkServiceRemoveProtocolType
	@discussion Removes the network protocol of the specified type from the service.
	@param service The network service.
	@param protocolType The type of SCNetworkProtocol to be removed from the service.
	@result TRUE if the protocol was removed to the service; FALSE if the
		protocol was not configured or an error was encountered.
 */
Boolean
SCNetworkServiceRemoveProtocolType		(SCNetworkServiceRef		service,
						 CFStringRef			protocolType)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkServiceSetEnabled
	@discussion Enables or disables the service.
	@param service The network service.
	@param enabled TRUE if the service should be enabled.
	@result TRUE if the enabled status was saved; FALSE if an error was encountered.
 */
Boolean
SCNetworkServiceSetEnabled			(SCNetworkServiceRef		service,
						 Boolean			enabled)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkServiceSetName
	@discussion Stores the [user specified] name for the service.
	@param service The network service.
	@param name The [user defined] name to associate with the service.
	@result TRUE if the name was saved; FALSE if an error was encountered.

	Note: although not technically required, the [user specified] names
	for all services within any given set should be unique.  As such, an
	error will be returned if you attemp to name two services with the
	same string.
 */
Boolean
SCNetworkServiceSetName				(SCNetworkServiceRef		service,
						 CFStringRef			name)		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);


/* --------------------------------------------------------------------------------
 * SETS
 * -------------------------------------------------------------------------------- */

/*!
	@group Set configuration
 */

#pragma mark -
#pragma mark SCNetworkSet configuration (APIs)

/*!
	@function SCNetworkSetGetTypeID
	@discussion Returns the type identifier of all SCNetworkSet instances.
 */
CFTypeID
SCNetworkSetGetTypeID				(void)						__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkSetAddService
	@discussion Adds the network service to the set.
	@param set The network set.
	@param service The service to be added.
	@result TRUE if the service was added to the set; FALSE if the
		service was already present or an error was encountered.

	Note: prior to Mac OS X 10.5, the Network Preferences UI
	did not support having a single service being a member of
	more than one set.  An error will be returned if you attempt
	to add a service to more than one set on a pre-10.5 system.
 */
Boolean
SCNetworkSetAddService				(SCNetworkSetRef		set,
						 SCNetworkServiceRef		service)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkSetContainsInterface
	@discussion Checks if an interface is represented by at least one
		network service in the specified set.
	@param set The network set.
	@param interface The network interface.
	@result TRUE if the interface is represented in the set; FALSE if not.
 */
Boolean
SCNetworkSetContainsInterface			(SCNetworkSetRef		set,
						 SCNetworkInterfaceRef		interface)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);

/*!
	@function SCNetworkSetCopyAll
	@discussion Returns all available sets for the specified preferences.
	@param prefs The "preferences" session.
	@result The list of SCNetworkSet sets associated with the preferences.
		You must release the returned value.
 */
CFArrayRef /* of SCNetworkSetRef's */ __nullable
SCNetworkSetCopyAll				(SCPreferencesRef		prefs)		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkSetCopyCurrent
	@discussion Returns the "current" set.
	@param prefs The "preferences" session.
	@result The current set; NULL if no current set has been defined.
 */
SCNetworkSetRef __nullable
SCNetworkSetCopyCurrent				(SCPreferencesRef		prefs)		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkSetCopyServices
	@discussion Returns all network services associated with the set.
	@param set The network set.
	@result The list of SCNetworkService services associated with the set.
		You must release the returned value.
 */
CFArrayRef /* of SCNetworkServiceRef's */ __nullable
SCNetworkSetCopyServices			(SCNetworkSetRef		set)		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkSetCreate
	@discussion Create a new set in the configuration.
	@param prefs The "preferences" session.
	@result A reference to the new SCNetworkSet.
		You must release the returned value.
 */
SCNetworkSetRef __nullable
SCNetworkSetCreate				(SCPreferencesRef		prefs)		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkSetCopy
	@discussion Returns the set with the specified identifier.
	@param prefs The "preferences" session.
	@param setID The unique identifier for the set.
	@result A reference to the SCNetworkSet from the associated preferences;
		NULL if the setID does not exist in the preferences or if an
		error was encountered.
		You must release the returned value.
 */
SCNetworkSetRef __nullable
SCNetworkSetCopy				(SCPreferencesRef		prefs,
						 CFStringRef			setID)		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkSetGetName
	@discussion Returns the [user specified] name associated with the set.
	@param set The network set.
	@result The [user specified] name.
 */
CFStringRef __nullable
SCNetworkSetGetName				(SCNetworkSetRef		set)		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkSetGetSetID
	@discussion Returns the identifier for the set.
	@param set The network set.
	@result The set identifier.
 */
CFStringRef __nullable
SCNetworkSetGetSetID				(SCNetworkSetRef		set)		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkSetGetServiceOrder
	@discussion Returns the [user specified] ordering of network services
		within the set.
	@param set The network set.
	@result The ordered list of CFStringRef service identifiers associated
		with the set;
		NULL if no service order has been specified or if an error
		was encountered.
 */
CFArrayRef /* of serviceID CFStringRef's */ __nullable
SCNetworkSetGetServiceOrder			(SCNetworkSetRef		set)		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkSetRemove
	@discussion Removes the set from the configuration.
	@param set The network set.
	@result TRUE if the set was removed; FALSE if an error was encountered.
 */
Boolean
SCNetworkSetRemove				(SCNetworkSetRef		set)		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkSetRemoveService
	@discussion Removes the network service from the set.
	@param set The network set.
	@param service The service to be removed.
	@result TRUE if the service was removed from the set; FALSE if the
		service was not already present or an error was encountered.
 */
Boolean
SCNetworkSetRemoveService			(SCNetworkSetRef		set,
						 SCNetworkServiceRef		service)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkSetSetCurrent
	@discussion Specifies the set that should be the "current" set.
	@param set The network set.
	@result TRUE if the current set was updated;
		FALSE if an error was encountered.
 */
Boolean
SCNetworkSetSetCurrent				(SCNetworkSetRef		set)		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkSetSetName
	@discussion Stores the [user specified] name for the set.
	@param set The network set.
	@param name The [user defined] name to associate with the set.
	@result TRUE if the name was saved; FALSE if an error was encountered.

	Note: although not technically required, the [user specified] names
	for all set should be unique.  As such, an error will be returned if
	you attemp to name two sets with the same string.
 */
Boolean
SCNetworkSetSetName				(SCNetworkSetRef		set,
						 CFStringRef			name)		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

/*!
	@function SCNetworkSetSetServiceOrder
	@discussion Stores the [user specified] ordering of network services for the set.
	@param set The network set.
	@param newOrder The ordered list of CFStringRef service identifiers for the set.
	@result TRUE if the new service order was saved; FALSE if an error was encountered.
 */
Boolean
SCNetworkSetSetServiceOrder			(SCNetworkSetRef		set,
						 CFArrayRef			newOrder)	__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);	/* serviceID CFStringRef's */


__END_DECLS

CF_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#endif	/* _SCNETWORKCONFIGURATION_H */
// ==========  SystemConfiguration.framework/Headers/SCDynamicStore.h
/*
 * Copyright (c) 2000, 2001, 2003-2005, 2008-2010, 2015 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _SCDYNAMICSTORE_H
#ifdef	USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS
#include <SystemConfiguration/_SCDynamicStore.h>
#else	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#define _SCDYNAMICSTORE_H

#include <Availability.h>
#include <TargetConditionals.h>
#include <sys/cdefs.h>
#include <dispatch/dispatch.h>
#include <CoreFoundation/CoreFoundation.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_ASSUME_NONNULL_BEGIN

/*!
	@header SCDynamicStore
	@discussion The SCDynamicStore API provides access to the key-value
		pairs in the dynamic store of a running system.  The dynamic
		store contains, among other items, a copy of the configuration
		settings for the currently active set (which is sometimes
		refered to as the location) and information about the current
		network state.

		The functions in the SCDynamicStore API allow you to find
		key-value pairs, add or remove key-value pairs, add or change
		values, and request notifications.

		To use the functions of the SCDynamicStore API, you must first
		establish a dynamic store session using the SCDynamicStoreCreate
		function.  When you are finished with the session, use CFRelease
		to close it.
 */


/*!
	@typedef SCDynamicStoreRef
	@discussion This is the handle to an open a dynamic store session
		with the system configuration daemon.
 */
typedef const struct CF_BRIDGED_TYPE(id) __SCDynamicStore *	SCDynamicStoreRef;

/*!
	@typedef SCDynamicStoreContext
	Structure containing user-specified data and callbacks for an
	SCDynamicStore session.
	@field version The version number of the structure type being passed
		in as a parameter to the SCDynamicStore creation function.
		This structure is version 0.
	@field info A C pointer to a user-specified block of data.
	@field retain The callback used to add a retain for the info field.
		If this parameter is not a pointer to a function of the correct
		prototype, the behavior is undefined.  The value may be NULL.
	@field release The calllback used to remove a retain previously added
		for the info field.  If this parameter is not a pointer to a
		function of the correct prototype, the behavior is undefined.
		The value may be NULL.
	@field copyDescription The callback used to provide a description of
		the info field.
 */
typedef struct {
	CFIndex		version;
	void *		__nullable info;
	const void	* __nonnull (* __nullable retain)(const void *info);
	void		(* __nullable release)(const void *info);
	CFStringRef	__nonnull (* __nullable copyDescription)(const void *info);
} SCDynamicStoreContext;

/*!
	@typedef SCDynamicStoreCallBack
	@discussion Type of callback function used when notification of
		changes to the dynamic store is delivered.
	@param store The dynamic store session.
	@param changedKeys The list of changed keys.

		The list includes any specific SCDynamicStore keys that
		changed (add, update, remove, notify) since the last call
		to SCDynamicStoreSetNotificationKeys or since the last
		notification callback. The list also includes any specific
		keys matching one of the pattern string(s) that changed.

		An empty list indicates that the SCDynamicStore server
		restarted and that any assumptions based on prior content
		of the SCDynamicStore should be disgarded.

	@param info A C pointer to a user-specified block of data.
 */
typedef void (*SCDynamicStoreCallBack)	(
					SCDynamicStoreRef			store,
					CFArrayRef				changedKeys,
					void			* __nullable	info
					);


__BEGIN_DECLS

/*!
	@function SCDynamicStoreGetTypeID
	@discussion Returns the type identifier of all SCDynamicStore instances.
 */
CFTypeID
SCDynamicStoreGetTypeID			(void)				__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);


/*!
	@function SCDynamicStoreCreate
	@discussion Creates a new session used to interact with the dynamic
		store maintained by the System Configuration server.
	@param allocator The CFAllocator that should be used to allocate
		memory for the local dynamic store object.
		This parameter may be NULL in which case the current
		default CFAllocator is used. If this reference is not
		a valid CFAllocator, the behavior is undefined.
	@param name A string that describes the name of the calling
		process or plug-in of the caller.
	@param callout The function to be called when a watched value
		in the dynamic store is changed.
		A NULL value can be specified if no callouts are
		desired.
	@param context The SCDynamicStoreContext associated with the callout.
	@result Returns a reference to the new SCDynamicStore session.
		You must release the returned value.
 */
SCDynamicStoreRef __nullable
SCDynamicStoreCreate			(
					CFAllocatorRef			__nullable	allocator,
					CFStringRef					name,
					SCDynamicStoreCallBack		__nullable	callout,
					SCDynamicStoreContext		* __nullable	context
					)				__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreCreateWithOptions
	@discussion Creates a new session used to interact with the dynamic
		store maintained by the System Configuration server.
	@param allocator The CFAllocator that should be used to allocate
		memory for the local dynamic store object.
		This parameter may be NULL in which case the current
		default CFAllocator is used. If this reference is not
		a valid CFAllocator, the behavior is undefined.
	@param name A string that describes the name of the calling
		process or plug-in of the caller.
	@param storeOptions A CFDictionary containing options for the
		dynamic store session (such as whether all keys added or set
		into the dynamic store should be per-session keys).

		Currently available options include:

		<TABLE BORDER>
		<TR>
			<TH>key</TD>
			<TH>value</TD>
		</TR>
		<TR>
			<TD>kSCDynamicStoreUseSessionKeys</TD>
			<TD>CFBooleanRef</TD>
		</TR>
		</TABLE>

		A NULL value can be specified if no options are desired.
	@param callout The function to be called when a watched value
		in the dynamic store is changed.
		A NULL value can be specified if no callouts are
		desired.
	@param context The SCDynamicStoreContext associated with the callout.
	@result Returns a reference to the new SCDynamicStore session.
		You must release the returned value.
 */
SCDynamicStoreRef __nullable
SCDynamicStoreCreateWithOptions		(
					CFAllocatorRef			__nullable	allocator,
					CFStringRef					name,
					CFDictionaryRef			__nullable	storeOptions,
					SCDynamicStoreCallBack		__nullable	callout,
					SCDynamicStoreContext		* __nullable	context
					)				__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);

extern const CFStringRef	kSCDynamicStoreUseSessionKeys		__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);	/* CFBoolean */

/*!
	@function SCDynamicStoreCreateRunLoopSource
	@discussion Creates a CFRunLoopSource object that can be added to the
		application's run loop.  All dynamic store notifications are
		delivered using this run loop source.
	@param allocator The CFAllocator that should be used to allocate
		memory for this run loop source.
		This parameter may be NULL in which case the current
		default CFAllocator is used. If this reference is not
		a valid CFAllocator, the behavior is undefined.
	@param store A reference to the dynamic store session.
	@param order On platforms which support it, for source versions
		which support it, this parameter determines the order in
		which the sources which are ready to be processed are
		handled. A lower order number causes processing before
		higher order number sources. It is inadvisable to depend
		on the order number for any architectural or design aspect
		of code. In the absence of any reason to do otherwise,
		zero should be used.
	@result A reference to the new CFRunLoopSource.
		You must release the returned value.

 */
CFRunLoopSourceRef __nullable
SCDynamicStoreCreateRunLoopSource	(
					CFAllocatorRef			__nullable	allocator,
					SCDynamicStoreRef				store,
					CFIndex						order
					)				__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreSetDispatchQueue
	@discussion Initiates notifications for the Notification
		Keys in store to the callback contained in store.
	@param store A reference to the dynamic store session.
	@param queue The dispatch queue to run the callback function on.
		Pass NULL to disable notifications, and release the queue.
	@result Returns TRUE on success, FALSE on failure.

 */
Boolean
SCDynamicStoreSetDispatchQueue		(
					SCDynamicStoreRef				store,
					dispatch_queue_t		__nullable	queue
					)				__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*!
	@function SCDynamicStoreCopyKeyList
	@discussion Returns an array of CFString keys representing the
		current dynamic store entries that match a specified pattern.
	@param store The dynamic store session.
	@param pattern A regex(3) regular expression pattern
		used to match the dynamic store keys.
	@result Returns the list of matching keys; NULL if an error was
		encountered.
		You must release the returned value.
 */
CFArrayRef __nullable
SCDynamicStoreCopyKeyList		(
					SCDynamicStoreRef		__nullable	store,
					CFStringRef					pattern
					)				__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreAddValue
	@discussion Adds the key-value pair to the dynamic store if no
		such key already exists.
	@param store The dynamic store session.
	@param key The key of the value to add to the dynamic store.
	@param value The value to add to the dynamic store.
	@result Returns TRUE if the key was added; FALSE if the key was already
		present in the dynamic store or if an error was encountered.
 */
Boolean
SCDynamicStoreAddValue			(
					SCDynamicStoreRef		__nullable	store,
					CFStringRef					key,
					CFPropertyListRef				value
					)				__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreAddTemporaryValue
	@discussion Temporarily adds the key-value pair to the dynamic store
		if no such key already exists.  Unless the key is updated by another
		session, the key-value pair will be removed automatically when the
		session is closed.
	@param store The dynamic store session.
	@param key The key of the value to add to the dynamic store.
	@param value The value to add to the dynamic store.
	@result Returns TRUE if the key was added; FALSE if the key was already
		present in the dynamic store or if an error was encountered.
 */
Boolean
SCDynamicStoreAddTemporaryValue		(
					SCDynamicStoreRef		store,
					CFStringRef			key,
					CFPropertyListRef		value
					)				__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreCopyValue
	@discussion Gets the value of the specified key from the dynamic store.
	@param store The dynamic store session.
	@param key The key associated with the value you want to get.
	@result Returns the value from the dynamic store that is associated with the given
		key; NULL if no value was located or an error was encountered.
		You must release the returned value.
 */
CFPropertyListRef __nullable
SCDynamicStoreCopyValue			(
					SCDynamicStoreRef		__nullable	store,
					CFStringRef					key
					)				__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreCopyMultiple
	@discussion Gets the values of multiple keys in the dynamic store.
	@param store The dynamic store session.
	@param keys The keys associated with the values you want to get; NULL if no specific
		keys are requested.
	@param patterns An array of regex(3) pattern strings used to match the keys; NULL
		if no key patterns are requested.
	@result Returns a dictionary containing the key-value pairs of specific keys and the
		key-value pairs of keys that matched the specified patterns;
		NULL if an error was encountered.
		You must release the returned value.
 */
CFDictionaryRef __nullable
SCDynamicStoreCopyMultiple		(
					SCDynamicStoreRef		__nullable	store,
					CFArrayRef			__nullable	keys,
					CFArrayRef			__nullable	patterns
					)				__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreSetValue
	@discussion Adds or replaces a value in the dynamic store for
		the specified key.
	@param store The dynamic store session.
	@param key The key you want to set.
	@param value The value to add to or replace in the dynamic store.
	@result Returns TRUE if the key was updated; FALSE if an error was encountered.
 */
Boolean
SCDynamicStoreSetValue			(
					SCDynamicStoreRef		__nullable	store,
					CFStringRef					key,
					CFPropertyListRef				value
					)				__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreSetMultiple
	@discussion Updates multiple values in the dynamic store.
	@param store The dynamic store session.
	@param keysToSet A dictionary of key-value pairs you want to set into the dynamic store.
	@param keysToRemove An array of keys you want to remove from the dynamic store.
	@param keysToNotify An array of keys to flag as changed (without changing their values).
	@result Returns TRUE if the dynamic store updates were successful; FALSE if an error was encountered.
 */
Boolean
SCDynamicStoreSetMultiple		(
					SCDynamicStoreRef		__nullable	store,
					CFDictionaryRef			__nullable	keysToSet,
					CFArrayRef			__nullable	keysToRemove,
					CFArrayRef			__nullable	keysToNotify
					)				__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreRemoveValue
	@discussion Removes the value of the specified key from the
		dynamic store.
	@param store The dynamic store session.
	@param key The key of the value you want to remove.
	@result Returns TRUE if the key was removed; FALSE if no value was
		located or an error was encountered.
 */
Boolean
SCDynamicStoreRemoveValue		(
					SCDynamicStoreRef		__nullable	store,
					CFStringRef					key
					)				__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreNotifyValue
	@discussion Triggers a notification to be delivered for the
		specified key in the dynamic store.
	@param store The dynamic store session.
	@param key The key that should be flagged as changed.  Any dynamic store sessions
		that are monitoring this key will received a notification.  Note that the
		key's value is not updated.
	@result Returns TRUE if the notification was processed; FALSE if an error was encountered.
 */
Boolean
SCDynamicStoreNotifyValue		(
					SCDynamicStoreRef		__nullable	store,
					CFStringRef					key
					)				__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreSetNotificationKeys
	@discussion Specifies a set of specific keys and key patterns
		that should be monitored for changes.
	@param store The dynamic store session being watched.
	@param keys An array of keys to be monitored; NULL if no specific keys
		are to be monitored.
	@param patterns An array of regex(3) pattern strings used to match keys to be monitored;
		NULL if no key patterns are to be monitored.
	@result Returns TRUE if the set of notification keys and patterns was successfully
		updated; FALSE if an error was encountered.
 */
Boolean
SCDynamicStoreSetNotificationKeys	(
					SCDynamicStoreRef				store,
					CFArrayRef			__nullable	keys,
					CFArrayRef			__nullable	patterns
					)				__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreCopyNotifiedKeys
	@discussion Returns an array of CFString keys representing the
		dynamic store entries that have changed since this
		function was last called.  If possible, your application should
		use the notification functions instead of polling for the list
		of changed keys returned by this function.
	@param store The dynamic store session.
	@result Returns the list of changed keys;
		NULL if an error was encountered.
		You must release the returned value.
 */
CFArrayRef __nullable
SCDynamicStoreCopyNotifiedKeys		(
					SCDynamicStoreRef		store
					)				__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

__END_DECLS

CF_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#endif	/* _SCDYNAMICSTORE_H */
// ==========  SystemConfiguration.framework/Headers/SystemConfiguration.h
/*
 * Copyright (c) 2000-2004, 2006, 2008-2010, 2012, 2015 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _SYSTEMCONFIGURATION_H
#define _SYSTEMCONFIGURATION_H

#include <Availability.h>
#include <sys/cdefs.h>
#include <CoreFoundation/CoreFoundation.h>


/*!
	@header SystemConfiguration
	@discussion The System Configuration framework provides access to the
		data used to configure a running system.  The APIs provided
		by this framework communicate with the configd daemon.

		The configd daemon manages a dynamic store reflecting the
		desired configuration settings as well as the current state
		of the system.  The daemon provides a notification mechanism
		for processes that need to be aware of changes made to the
		data.  Lastly, the daemon loads a number of bundles (or
		plug-ins) that monitor low-level kernel events and, through
		a set of policy modules, keep the state data up to date.
 */

/*!
	@enum Error codes
	@discussion Returned error codes.
	@constant kSCStatusOK			Success
	@constant kSCStatusFailed		Non-specific Failure
	@constant kSCStatusInvalidArgument	Invalid argument
	@constant kSCStatusAccessError		Permission denied
	@constant kSCStatusNoKey		No such key
	@constant kSCStatusKeyExists		Data associated with key already defined
	@constant kSCStatusLocked		Lock already held
	@constant kSCStatusNeedLock		Lock required for this operation
	@constant kSCStatusNoStoreSession	Configuration daemon session not active
	@constant kSCStatusNoStoreServer	Configuration daemon not (or no longer) available
	@constant kSCStatusNotifierActive	Notifier is currently active
	@constant kSCStatusNoPrefsSession	Preferences session not active
	@constant kSCStatusPrefsBusy		Preferences update currently in progress
	@constant kSCStatusNoConfigFile		Configuration file not found
	@constant kSCStatusNoLink		No such link
	@constant kSCStatusStale		Write attempted on stale version of object
	@constant kSCStatusMaxLink		Maximum link count exceeded
	@constant kSCStatusReachabilityUnknown
		A determination could not be made regarding the reachability
		of the specified nodename or address.
	@constant kSCStatusConnectionNoService	Network service for connection not available
*/
enum {
	/*
	 * Generic error codes
	 */
	kSCStatusOK				= 0,	/* Success */
	kSCStatusFailed				= 1001,	/* Non-specific failure */
	kSCStatusInvalidArgument		= 1002,	/* Invalid argument */
	kSCStatusAccessError			= 1003,	/* Permission denied
							   - must be root to obtain lock
							   - could not create access/create preferences
							 */
	kSCStatusNoKey				= 1004,	/* No such key */
	kSCStatusKeyExists			= 1005,	/* Key already defined */
	kSCStatusLocked				= 1006,	/* Lock already held */
	kSCStatusNeedLock			= 1007,	/* Lock required for this operation */
	/*
	 * SCDynamicStore error codes
	 */
	kSCStatusNoStoreSession			= 2001,	/* Configuration daemon session not active */
	kSCStatusNoStoreServer			= 2002,	/* Configuration daemon not (no longer) available */
	kSCStatusNotifierActive			= 2003,	/* Notifier is currently active */
	/*
	 * SCPreferences error codes
	 */
	kSCStatusNoPrefsSession			= 3001,	/* Preference session not active */
	kSCStatusPrefsBusy			= 3002,	/* Preferences update currently in progress */
	kSCStatusNoConfigFile			= 3003,	/* Configuration file not found */
	kSCStatusNoLink				= 3004,	/* No such link */
	kSCStatusStale				= 3005,	/* Write attempted on stale version of object */
	kSCStatusMaxLink			= 3006,	/* Maximum link count exceeded */
	/*
	 * SCNetwork error codes
	 */
	kSCStatusReachabilityUnknown		= 4001,	/* Network reachability cannot be determined */
	/*
	 * SCNetworkConnection error codes
	 */
	kSCStatusConnectionNoService		= 5001,	/* Network service for connection not available
							   __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0)
							 */
	kSCStatusConnectionIgnore               = 5002, /* Network connection information not available at this time
							   __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0)
							 */
};


/* SCDynamicStore APIs */
#include <SystemConfiguration/SCDynamicStore.h>
#include <SystemConfiguration/SCDynamicStoreKey.h>
#include <SystemConfiguration/SCDynamicStoreCopySpecific.h>

/* SCPreferences APIs */
#include <SystemConfiguration/SCPreferences.h>
#include <SystemConfiguration/SCPreferencesPath.h>
#include <SystemConfiguration/SCPreferencesSetSpecific.h>

/* Schema Definitions (for SCDynamicStore and SCPreferences) */
#include <SystemConfiguration/SCSchemaDefinitions.h>

/* SCNetworkConfiguration APIs */
#include <SystemConfiguration/SCNetworkConfiguration.h>

/* SCNetworkReachability and SCNetworkConnection APIs */
#include <SystemConfiguration/SCNetwork.h>
#include <SystemConfiguration/SCNetworkReachability.h>
#include <SystemConfiguration/SCNetworkConnection.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_ASSUME_NONNULL_BEGIN

/*!
	@const kCFErrorDomainSystemConfiguration
	@discussion CFError domain associated with errors reported by
		the SystemConfiguration.framework.
 */
extern const CFStringRef	kCFErrorDomainSystemConfiguration	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

__BEGIN_DECLS

/*!
	@function SCCopyLastError
	@discussion Returns the most recent status or error code generated
		as the result of calling a System Configuration framework API.
	@result Returns the last error encountered.
 */
CFErrorRef	SCCopyLastError		(void)				__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
	@function SCError
	@discussion Returns the most recent status or error code generated
		as the result of calling a System Configuration framework API.
	@result Returns the last error encountered.
 */
int		SCError			(void)				__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_2_0);

/*!
	@function SCErrorString
	@discussion Returns a pointer to the message string
		associated with the specified status or error.
	@param status The SCDynamicStoreStatus to be returned.
	@result Returns a pointer to the error message string.
 */
const char *	SCErrorString		(int	status)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_2_0);

__END_DECLS

CF_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* _SYSTEMCONFIGURATION_H */
// ==========  SystemConfiguration.framework/Headers/SCNetworkReachability.h
/*
 * Copyright (c) 2003-2005, 2008-2010, 2015 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _SCNETWORKREACHABILITY_H
#define _SCNETWORKREACHABILITY_H

#include <Availability.h>
#include <TargetConditionals.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <CoreFoundation/CoreFoundation.h>
#include <SystemConfiguration/SCNetwork.h>
#include <dispatch/dispatch.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_ASSUME_NONNULL_BEGIN

/*!
	@header SCNetworkReachability
	@discussion The SCNetworkReachability API allows an application to
		determine the status of a system's current network
		configuration and the reachability of a target host.
		In addition, reachability can be monitored with notifications
		that are sent when the status has changed.

		"Reachability" reflects whether a data packet, sent by
		an application into the network stack, can leave the local
		computer.
		Note that reachability does <i>not</i> guarantee that the data
		packet will actually be received by the host.
 */

/*!
	@typedef SCNetworkReachabilityRef
	@discussion This is the handle to a network address or name.
 */
typedef const struct CF_BRIDGED_TYPE(id) __SCNetworkReachability * SCNetworkReachabilityRef;


/*!
	@typedef SCNetworkReachabilityContext
	Structure containing user-specified data and callbacks for SCNetworkReachability.
	@field version The version number of the structure type being passed
		in as a parameter to the SCDynamicStore creation function.
		This structure is version 0.
	@field info A C pointer to a user-specified block of data.
	@field retain The callback used to add a retain for the info field.
		If this parameter is not a pointer to a function of the correct
		prototype, the behavior is undefined.  The value may be NULL.
	@field release The calllback used to remove a retain previously added
		for the info field.  If this parameter is not a pointer to a
		function of the correct prototype, the behavior is undefined.
		The value may be NULL.
	@field copyDescription The callback used to provide a description of
		the info field.
 */
typedef struct {
	CFIndex		version;
	void *		__nullable info;
	const void	* __nonnull (* __nullable retain)(const void *info);
	void		(* __nullable release)(const void *info);
	CFStringRef	__nonnull (* __nullable copyDescription)(const void *info);
} SCNetworkReachabilityContext;

/*!
	@enum SCNetworkReachabilityFlags
	@discussion Flags that indicate whether the specified network
		nodename or address is reachable, whether a connection is
		required, and whether some user intervention may be required
		when establishing a connection.
	@constant kSCNetworkReachabilityFlagsTransientConnection
		This flag indicates that the specified nodename or address can
		be reached via a transient connection, such as PPP.
	@constant kSCNetworkReachabilityFlagsReachable
		This flag indicates that the specified nodename or address can
		be reached using the current network configuration.
	@constant kSCNetworkReachabilityFlagsConnectionRequired
		This flag indicates that the specified nodename or address can
		be reached using the current network configuration, but a
		connection must first be established.

		As an example, this status would be returned for a dialup
		connection that was not currently active, but could handle
		network traffic for the target system.
	@constant kSCNetworkReachabilityFlagsConnectionOnTraffic
		This flag indicates that the specified nodename or address can
		be reached using the current network configuration, but a
		connection must first be established.  Any traffic directed
		to the specified name or address will initiate the connection.

		Note: this flag was previously named kSCNetworkReachabilityFlagsConnectionAutomatic
	@constant kSCNetworkReachabilityFlagsInterventionRequired
		This flag indicates that the specified nodename or address can
		be reached using the current network configuration, but a
		connection must first be established.  In addition, some
		form of user intervention will be required to establish this
		connection, such as providing a password, an authentication
		token, etc.

		Note: At the present time, this flag will only be returned
		in the case where you have a dial-on-traffic configuration
		(ConnectionOnTraffic), where an attempt to connect has
		already been made, and where some error (e.g. no dial tone,
		no answer, bad password, ...) was encountered during the
		automatic connection attempt.  In this case the PPP controller
		will stop attempting to establish a connection until the user
		has intervened.
	@constant kSCNetworkReachabilityFlagsConnectionOnDemand
		This flag indicates that the specified nodename or address can
		be reached using the current network configuration, but a
		connection must first be established.
		The connection will be established "On Demand" by the
		CFSocketStream APIs.
		Other APIs will not establish the connection.
	@constant kSCNetworkReachabilityFlagsIsLocalAddress
		This flag indicates that the specified nodename or address
		is one associated with a network interface on the current
		system.
	@constant kSCNetworkReachabilityFlagsIsDirect
		This flag indicates that network traffic to the specified
		nodename or address will not go through a gateway, but is
		routed directly to one of the interfaces in the system.
#if	TARGET_OS_IPHONE
	@constant kSCNetworkReachabilityFlagsIsWWAN
		This flag indicates that the specified nodename or address can
		be reached via an EDGE, GPRS, or other "cell" connection.
#endif	// TARGET_OS_IPHONE
 */
typedef CF_OPTIONS(uint32_t, SCNetworkReachabilityFlags) {
	kSCNetworkReachabilityFlagsTransientConnection	= 1<<0,
	kSCNetworkReachabilityFlagsReachable		= 1<<1,
	kSCNetworkReachabilityFlagsConnectionRequired	= 1<<2,
	kSCNetworkReachabilityFlagsConnectionOnTraffic	= 1<<3,
	kSCNetworkReachabilityFlagsInterventionRequired	= 1<<4,
	kSCNetworkReachabilityFlagsConnectionOnDemand	= 1<<5,	// __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_3_0)
	kSCNetworkReachabilityFlagsIsLocalAddress	= 1<<16,
	kSCNetworkReachabilityFlagsIsDirect		= 1<<17,
#if	TARGET_OS_IPHONE
	kSCNetworkReachabilityFlagsIsWWAN		= 1<<18,
#endif	// TARGET_OS_IPHONE

	kSCNetworkReachabilityFlagsConnectionAutomatic	= kSCNetworkReachabilityFlagsConnectionOnTraffic
};

/*!
	@typedef SCNetworkReachabilityCallBack
	@discussion Type of the callback function used when the
		reachability of a network address or name changes.
	@param target The SCNetworkReachability reference being monitored
		for changes.
	@param flags The new SCNetworkReachabilityFlags representing the
		reachability status of the network address/name.
	@param info A C pointer to a user-specified block of data.
 */
typedef void (*SCNetworkReachabilityCallBack)	(
						SCNetworkReachabilityRef			target,
						SCNetworkReachabilityFlags			flags,
						void			     *	__nullable	info
						);

__BEGIN_DECLS

/*!
	@function SCNetworkReachabilityCreateWithAddress
	@discussion Creates a reference to the specified network
		address.  This reference can be used later to monitor the
		reachability of the target host.
	@param address The address of the desired host.
	@result Returns a reference to the new immutable SCNetworkReachabilityRef.

		 You must release the returned value.
 */
SCNetworkReachabilityRef __nullable
SCNetworkReachabilityCreateWithAddress		(
						CFAllocatorRef			__nullable	allocator,
						const struct sockaddr				*address
						)				__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_2_0);

/*!
	@function SCNetworkReachabilityCreateWithAddressPair
	@discussion Creates a reference to the specified network
		address.  This reference can be used later to monitor the
		reachability of the target host.
	@param localAddress The local address associated with a network
		connection.  If NULL, only the remote address is of interest.
	@param remoteAddress The remote address associated with a network
		connection.  If NULL, only the local address is of interest.
	@result Returns a reference to the new immutable SCNetworkReachabilityRef.

		 You must release the returned value.
 */
SCNetworkReachabilityRef __nullable
SCNetworkReachabilityCreateWithAddressPair	(
						CFAllocatorRef			__nullable	allocator,
						const struct sockaddr		* __nullable	localAddress,
						const struct sockaddr		* __nullable	remoteAddress
						)				__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_2_0);

/*!
	@function SCNetworkReachabilityCreateWithName
	@discussion Creates a reference to the specified network host or node
		name.  This reference can be used later to monitor the
		reachability of the target host.
	@param nodename The node name of the desired host.
		This name would be the same as that passed to the
		gethostbyname(3) or getaddrinfo(3) functions.
	@result Returns a reference to the new immutable SCNetworkReachabilityRef.

		You must release the returned value.
 */
SCNetworkReachabilityRef __nullable
SCNetworkReachabilityCreateWithName		(
						CFAllocatorRef			__nullable	allocator,
						const char					*nodename
						)				__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_2_0);

/*!
	@function SCNetworkReachabilityGetTypeID
	@discussion Returns the type identifier of all SCNetworkReachability
		instances.
 */
CFTypeID
SCNetworkReachabilityGetTypeID			(void)				__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_2_0);


/*!
	@function SCNetworkReachabilityGetFlags
	@discussion Determines if the given target is reachable using the
		current network configuration.
	@param target The network reference associated with the address or name
		to be checked for reachability.
	@param flags A pointer to memory that will be filled with the
		SCNetworkReachabilityFlags detailing the reachability
		of the specified target.
	@result Returns TRUE if the network connection flags are valid;
		FALSE if the status could not be determined.
 */
Boolean
SCNetworkReachabilityGetFlags			(
						SCNetworkReachabilityRef	target,
						SCNetworkReachabilityFlags	*flags
						)				__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_2_0);

/*!
	@function SCNetworkReachabilitySetCallback
	@discussion Assigns a client to a target, which receives callbacks
		when the reachability of the target changes.
	@param target The network reference associated with the address or
		name to be checked for reachability.
	@param callout The function to be called when the reachability of the
		target changes.  If NULL, the current client for the target
		is removed.
	@param context The SCNetworkReachabilityContext associated with
		the callout.  The value may be NULL.
	@result Returns TRUE if the notification client was successfully set.
 */
Boolean
SCNetworkReachabilitySetCallback		(
						SCNetworkReachabilityRef			target,
						SCNetworkReachabilityCallBack	__nullable	callout,
						SCNetworkReachabilityContext	* __nullable	context
						)				__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_2_0);

/*!
	@function SCNetworkReachabilityScheduleWithRunLoop
	@discussion Schedules the given target with the given run loop and mode.
	@param target The address or name that is set up for asynchronous
		notifications.  Must be non-NULL.
	@param runLoop A reference to a run loop on which the target should
		be scheduled.  Must be non-NULL.
	@param runLoopMode The mode on which to schedule the target.
		Must be non-NULL.
	@result Returns TRUE if the target is scheduled successfully;
		FALSE otherwise.
 */
Boolean
SCNetworkReachabilityScheduleWithRunLoop	(
						SCNetworkReachabilityRef	target,
						CFRunLoopRef			runLoop,
						CFStringRef			runLoopMode
						)				__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_2_0);

/*!
	@function SCNetworkReachabilityUnscheduleFromRunLoop
	@discussion Unschedules the given target from the given run loop
		and mode.
	@param target The address or name that is set up for asynchronous
		notifications.  Must be non-NULL.
	@param runLoop A reference to a run loop from which the target
		should be unscheduled.  Must be non-NULL.
	@param runLoopMode The mode on which to unschedule the target.
		Must be non-NULL.
	@result Returns TRUE if the target is unscheduled successfully;
		FALSE otherwise.
 */
Boolean
SCNetworkReachabilityUnscheduleFromRunLoop	(
						SCNetworkReachabilityRef	target,
						CFRunLoopRef			runLoop,
						CFStringRef			runLoopMode
						)				__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_2_0);

/*!
	@function SCNetworkReachabilitySetDispatchQueue
	@discussion Schedules callbacks for the given target on the given
		dispatch queue.
	@param target The address or name that is set up for asynchronous
		notifications.  Must be non-NULL.
	@param queue A libdispatch queue to run the callback on. Pass NULL to disable notifications, and release queue.
	@result Returns TRUE if the target is unscheduled successfully;
		FALSE otherwise.
 */
Boolean
SCNetworkReachabilitySetDispatchQueue		(
						SCNetworkReachabilityRef			target,
						dispatch_queue_t		__nullable	queue
						)				__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_4_0);

__END_DECLS

CF_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* _SCNETWORKREACHABILITY_H */
// ==========  SystemConfiguration.framework/Headers/DHCPClientPreferences.h
/*
 * Copyright (c) 2001, 2004, 2005, 2008, 2015 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _DHCPCLIENTPREFERENCES_H
#ifdef	USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS
#include <SystemConfiguration/_DHCPClientPreferences.h>
#else	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#define _DHCPCLIENTPREFERENCES_H

#include <Availability.h>
#include <sys/cdefs.h>
#include <CoreFoundation/CFString.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_ASSUME_NONNULL_BEGIN

/*!
	@header DHCPClientPreferences
	@discussion The DHCPClientPreferences API allows applications to get and update DHCP preferences.
		DHCP preferences are in the form of DHCP option codes, which are defined in RFC 2132.
 */

__BEGIN_DECLS

/*!
	@function DHCPClientPreferencesSetApplicationOptions
	@discussion Updates the DHCP client preferences to include the
		given list of options for the given application ID.
	@param applicationID The application's preference ID, for example:
		"com.apple.SystemPreferences".
	@param options An array of 8-bit values containing the
		DHCP option codes (see RFC 2132) for this application ID.
		A NULL value will clear the list of options for this
		application ID.
	@param count The number of elements in the options parameter.
	@result Returns TRUE if the operation succeeded, FALSE otherwise.
 */

Boolean
DHCPClientPreferencesSetApplicationOptions	(CFStringRef			applicationID,
						 UInt8		* __nullable	options,
						 CFIndex			count)		__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function DHCPClientPreferencesCopyApplicationOptions
	@discussion Copies the requested DHCP options for the
		given application ID.
	@param applicationID The application's preference ID, for example
		"com.apple.SystemPreferences".
	@param count The number of elements in the returned array.
	@result Returns the list of options for the given application ID, or
		NULL if no options are defined or an error occurred.

		When you are finished, use free() to release a non-NULL return value.
 */

UInt8 * __nullable
DHCPClientPreferencesCopyApplicationOptions	(CFStringRef	applicationID,
						 CFIndex	*count)		__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

__END_DECLS

CF_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#endif	/* _DHCPCLIENTPREFERENCES_H */
// ==========  SystemConfiguration.framework/Headers/SCNetworkConnection.h
/*
 * Copyright (c) 2003-2006, 2008-2010, 2015 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _SCNETWORKCONNECTION_H
#ifdef	USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS
#include <SystemConfiguration/_SCNetworkConnection.h>
#else	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#define _SCNETWORKCONNECTION_H

#include <Availability.h>
#include <TargetConditionals.h>
#include <sys/cdefs.h>
#include <dispatch/dispatch.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <CoreFoundation/CoreFoundation.h>
#include <SystemConfiguration/SystemConfiguration.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_ASSUME_NONNULL_BEGIN

/*!
	@header SCNetworkConnection
	@discussion The SCNetworkConnection API contains functions that allow
		an application to control connection-oriented services defined
		in the system and get connection-status information.

		The functions in the SCNetworkConnection API allow you to
		control and get information about existing services only.
		If you need to create, change, or remove services, you
		should use the SCNetworkConfiguration API instead.

		Note: Currently, only PPP services can be controlled.
 */


/*!
	@typedef SCNetworkConnectionRef
	@discussion This is the handle to manage a connection-oriented service.
 */
typedef const struct CF_BRIDGED_TYPE(id) __SCNetworkConnection * SCNetworkConnectionRef;


/*!
	@typedef SCNetworkConnectionContext
	@discussion Structure containing user-specified data and callbacks
		for a SCNetworkConnection.
	@field version The version number of the structure type being passed
		in as a parameter to the SCNetworkConnectionCreateWithServiceID
		function.  This structure is version 0.
	@field info A C pointer to a user-specified block of data.
	@field retain The callback used to add a retain for the info field.
		If this parameter is not a pointer to a function of the correct
		prototype, the behavior is undefined.  The value may be NULL.
	@field release The calllback used to remove a retain previously added
		for the info field.  If this parameter is not a pointer to a
		function of the correct prototype, the behavior is undefined.
		The value may be NULL.
	@field copyDescription The callback used to provide a description of
		the info field.
 */
typedef struct {
	CFIndex         version;
	void *          __nullable info;
	const void      * __nonnull (* __nullable retain)(const void *info);
	void            (* __nullable release)(const void *info);
	CFStringRef     __nonnull (* __nullable copyDescription)(const void *info);
} SCNetworkConnectionContext;



/*!
	@enum SCNetworkConnectionStatus
	@discussion Status of the network connection.
		This status is intended to be generic and high level.
		An extended status, specific to the type of network
		connection is also available for applications that
		need additonal information.
	@constant kSCNetworkConnectionInvalid
		The network connection refers to an invalid service.
	@constant kSCNetworkConnectionDisconnected
		The network connection is disconnected.
	@constant kSCNetworkConnectionConnecting
		The network connection is connecting.
	@constant kSCNetworkConnectionConnected
		The network connection is connected.
	@constant kSCNetworkConnectionDisconnecting
		The network connection is disconnecting.
 */
typedef CF_ENUM(int32_t, SCNetworkConnectionStatus) {
	kSCNetworkConnectionInvalid		=  -1,
	kSCNetworkConnectionDisconnected	=  0,
	kSCNetworkConnectionConnecting		=  1,
	kSCNetworkConnectionConnected		=  2,
	kSCNetworkConnectionDisconnecting	=  3
};


/*!
	@enum SCNetworkConnectionPPPStatus
	@discussion PPP-specific status of the network connection.
		This status is returned as part of the extended information
		for a PPP service.
		Note: additional status might be returned in the future.
		Your application should be prepared to receive an unknown value.
	@constant kSCNetworkConnectionPPPDisconnected
		PPP is disconnected.
	@constant kSCNetworkConnectionPPPInitializing
		PPP is initializing.
	@constant kSCNetworkConnectionPPPConnectingLink
		PPP is connecting the lower connection layer (for example,
		the modem is dialing out).
	@constant kSCNetworkConnectionPPPDialOnTraffic
		PPP is waiting for networking traffic to automatically
		establish the connection.
	@constant kSCNetworkConnectionPPPNegotiatingLink
		The PPP lower layer is connected and PPP is negotiating the
		link layer (LCP protocol).
	@constant kSCNetworkConnectionPPPAuthenticating
		PPP is authenticating to the server (PAP, CHAP, MS-CHAP or
		EAP protocols).
	@constant kSCNetworkConnectionPPPWaitingForCallBack
		PPP is waiting for the server to call back.
	@constant kSCNetworkConnectionPPPNegotiatingNetwork
		PPP is now authenticated and negotiating the networking
		layer (IPCP or IPv6CP protocols)
	@constant kSCNetworkConnectionPPPConnected
		PPP is now fully connected for at least one networking layer.
		Additional networking protocol might still be negotiating.
	@constant kSCNetworkConnectionPPPTerminating
		PPP networking and link protocols are terminating.
	@constant kSCNetworkConnectionPPPDisconnectingLink
		PPP is disconnecting the lower level (for example, the modem
		is hanging up).
	@constant kSCNetworkConnectionPPPHoldingLinkOff
		PPP is disconnected and maintaining the link temporarily off.
	@constant kSCNetworkConnectionPPPSuspended
		PPP is suspended as a result of the suspend command (for
		example, when a V.92 Modem is On Hold).
	@constant kSCNetworkConnectionPPPWaitingForRedial
		PPP has found a busy server and is waiting for redial.
 */
typedef CF_ENUM(int32_t, SCNetworkConnectionPPPStatus) {
	kSCNetworkConnectionPPPDisconnected		=  0,
	kSCNetworkConnectionPPPInitializing		=  1,
	kSCNetworkConnectionPPPConnectingLink		=  2,
	kSCNetworkConnectionPPPDialOnTraffic		=  3,
	kSCNetworkConnectionPPPNegotiatingLink		=  4,
	kSCNetworkConnectionPPPAuthenticating		=  5,
	kSCNetworkConnectionPPPWaitingForCallBack	=  6,
	kSCNetworkConnectionPPPNegotiatingNetwork	=  7,
	kSCNetworkConnectionPPPConnected		=  8,
	kSCNetworkConnectionPPPTerminating		=  9,
	kSCNetworkConnectionPPPDisconnectingLink	=  10,
	kSCNetworkConnectionPPPHoldingLinkOff		=  11,
	kSCNetworkConnectionPPPSuspended		=  12,
	kSCNetworkConnectionPPPWaitingForRedial		=  13
};

/*!
	@typedef SCNetworkConnectionCallBack
	@discussion Type of the callback function used when a
		status event is delivered.
	@param status The connection status.
	@param connection The connection reference.
	@param info Application-specific information.
 */
typedef void (*SCNetworkConnectionCallBack)	(
						SCNetworkConnectionRef				connection,
						SCNetworkConnectionStatus			status,
						void			    *	__nullable	info
						);



/*
    Keys for the statistics dictionary
*/

#define kSCNetworkConnectionBytesIn		CFSTR("BytesIn")		/* CFNumber */
#define kSCNetworkConnectionBytesOut		CFSTR("BytesOut")		/* CFNumber */
#define kSCNetworkConnectionPacketsIn		CFSTR("PacketsIn")		/* CFNumber */
#define kSCNetworkConnectionPacketsOut		CFSTR("PacketsOut")		/* CFNumber */
#define kSCNetworkConnectionErrorsIn		CFSTR("ErrorsIn")		/* CFNumber */
#define kSCNetworkConnectionErrorsOut		CFSTR("ErrorsOut")		/* CFNumber */


/*
 Keys for the SCNetworkConnectionCopyUserPreferences() "selectionOptions"
 dictionary
 */

/*!
	@define kSCNetworkConnectionSelectionOptionOnDemandHostName
	@discussion A host name that will be used to select the
		"best" SCNetworkConnection.
 */
#define kSCNetworkConnectionSelectionOptionOnDemandHostName	CFSTR("OnDemandHostName")	// CFString
												// __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)

/*!
	@define kSCNetworkConnectionSelectionOptionOnDemandRetry
	@discussion A boolean value used to indicate whether a DNS query has
		already been issued for the specified OnDemand host name.
 */
#define kSCNetworkConnectionSelectionOptionOnDemandRetry	CFSTR("OnDemandRetry")		// CFBoolean
												// __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)

__BEGIN_DECLS

/*!
	@function SCNetworkConnectionGetTypeID
	@discussion Returns the type identifier of all SCNetworkConnection
		instances.
 */
CFTypeID
SCNetworkConnectionGetTypeID			(void)			__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);


/*!
	@function SCNetworkConnectionCopyUserPreferences
	@discussion Provides the default service ID and a dictionary of user
		options for the connection.  Applications can use the
		returned serviceID and userOptions values to open a
		connection on the fly.
	@param selectionOptions Currently unimplemented. Pass NULL for this
		version.
	@param serviceID Reference to the default serviceID for starting
		connections, this value will be returned by the function.
	@param userOptions Reference to default userOptions for starting
		connections, this will be returned by the function.
	@result Returns TRUE if there is a valid service to dial;
		FALSE if the function was unable to retrieve a service to dial.
 */
Boolean
SCNetworkConnectionCopyUserPreferences		(
						CFDictionaryRef				  __nullable	selectionOptions,
						CFStringRef		__nonnull	* __nullable	serviceID,
						CFDictionaryRef		__nonnull	* __nullable	userOptions
						)			__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);


/*!
	@function SCNetworkConnectionCreateWithServiceID
	@discussion Creates a new connection reference to use for getting
		the status or for connecting or disconnecting the associated
		service.
	@param allocator The CFAllocator that should be used to allocate
		memory for the connection structure.  This parameter may be
		NULL in which case the current default CFAllocator is used.
		If this reference is not a valid CFAllocator, the behavior
		is undefined.
	@param serviceID A string that defines the service identifier
		of the connection.  Service identifiers uniquely identify
		services in the system configuration database.
	@param callout The function to be called when the status
		of the connection changes.  If this parameter is NULL, the
		application will not receive notifications of status change
		and will need to poll for updates.
	@param context The SCNetworkConnectionContext associated with the
		callout.
	@result Returns a reference to the new SCNetworkConnection.
 */
SCNetworkConnectionRef __nullable
SCNetworkConnectionCreateWithServiceID		(
						CFAllocatorRef			__nullable	allocator,
						CFStringRef					serviceID,
						SCNetworkConnectionCallBack	__nullable	callout,
						SCNetworkConnectionContext	* __nullable	context
						)			__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);


/*!
	@function SCNetworkConnectionCopyServiceID
	@discussion Returns the service ID associated with the SCNetworkConnection.
	@param connection The SCNetworkConnection to obtain status from.
	@result Returns the service ID associated with the SCNetworkConnection.
 */
CFStringRef __nullable
SCNetworkConnectionCopyServiceID		(
						SCNetworkConnectionRef		connection
						)			__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);


/*!
	@function SCNetworkConnectionGetStatus
	@discussion Returns the status of the SCNetworkConnection.
		A status is one of the following values:
<pre>
@textblock
&#32
	kSCNetworkConnectionInvalid
	kSCNetworkConnectionDisconnected
	kSCNetworkConnectionConnecting
	kSCNetworkConnectionDisconnecting
	kSCNetworkConnectionConnected
@/textblock
</pre>
	@param connection The SCNetworkConnection to obtain status from.
	@result Returns the status value.
*/
SCNetworkConnectionStatus
SCNetworkConnectionGetStatus			(
						SCNetworkConnectionRef		connection
						)			__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);


/*!
	@function SCNetworkConnectionCopyExtendedStatus
	@discussion Returns the extended status of the connection.
		An extended status dictionary contains specific dictionaries
		describing the status for each subcomponent of the service.

		For example, a status dictionary will contain the following
		sub-dictionaries, keys, and values:
<pre>
@textblock
&#32
	IPv4  : Addresses      : the assigned IP address.
&#32
	PPP   : Status         : the PPP-specific status of type
				 SCNetworkConnectionPPPStatus.
&#32
		LastCause      : Available when the status is "Disconnected"
				 and contains the last error associated with
				 connecting or disconnecting.
&#32
		ConnectTime    : the time when the connection was
				 established.
&#32
	Modem : ConnectSpeed   : the speed of the modem connection
				 in bits/second.
&#32
	IPSec : Status         : the IPSec-specific status of type
				 SCNetworkConnectionIPSecStatus
&#32
		ConnectTime    : the time when the connection was
				 established.

@/textblock
</pre>
		Other dictionaries could be present for PPPoE, PPTP, and L2TP.

		The status dictionary may be extended in the future to contain
		additional information.
	@param connection The SCNetworkConnection to obtain status from.
	@result Returns the status dictionary.
		If NULL is returned, the error can be retrieved using the SCError function.
 */
CFDictionaryRef __nullable
SCNetworkConnectionCopyExtendedStatus		(
						SCNetworkConnectionRef		connection
						)			__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);


/*!
	@function SCNetworkConnectionCopyStatistics
	@discussion Returns the statistics of the SCNetworkConnection.
		A statistic dictionary contains specific dictionaries
		with statistics for each subcomponent of the service.

		For example, a statistics dictionary will contain the following
		sub-dictionaries, keys, and values:
<pre>
@textblock
&#32
	PPP : BytesIn    :
	PPP : BytesOut   : Contains the number of bytes going up into
			   (or coming out of) the network stack for
			   any networking protocol without the PPP
			   headers and trailers.
&#32
	PPP : PacketsIn  :
	PPP : PacketsOut : Contains the number of packets going up into
			   (or coming out of) the network stack for
			   any networking protocol without the PPP
			   headers and trailers.
&#32
	PPP : ErrorsIn   :
	PPP : ErrorsOut  : Contains the number of errors going up into
			   (or coming out of) the network stack for
			   any networking protocol without the PPP
			   headers and trailers.
@/textblock
</pre>
		The statistics dictionary may be extended in the future to
		contain additional information.
	@param connection The SCNetworkConnection to obtained statistics from.
	@result Returns the statistics dictionary.
		If NULL is returned, the error can be retrieved using the SCError function.
 */
CFDictionaryRef __nullable
SCNetworkConnectionCopyStatistics		(
						SCNetworkConnectionRef		connection
						)			__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);


/*!
	@function SCNetworkConnectionStart
	@discussion Starts the connection for the SCNetworkConnection.
		The connection process is asynchronous and the function will
		return immediately.  The connection status can be obtained
		by polling or by callback.  The connection is made with the
		default settings from the administrator.  Some of the settings
		can be overridden for the duration of the connection.  These
		are specified in an options dictionary.  The options dictionary
		uses the same format as a network service defined in the system
		configuration preferences schema.

		Note: Starting and stopping of connections is implicitly
		arbitrated.  Calling SCNetworkConnectionStart on a connection
		already started will indicate that the application has
		interest in the connection and it shouldn't be stopped by
		anyone else.
	@param connection The SCNetworkConnection to start.
	@param userOptions The options dictionary to start the connection with.
		If userOptions is NULL, the default settings will be used.
		If userOptions are specified, they must be in the same format
		as network services stored in the system configuration
		preferences schema.  The options will override the default
		settings defined for the service.

		For security reasons, not all options can be overridden; the
		appropriate merging of all settings will be done before the
		connection is established, and inappropriate options will be
		ignored.
	@param linger This parameter indicates whether or not the connection
		can stay around when the application no longer has interest
		in it.  A typical application should pass FALSE, and the
		connection will be automatically stopped when the reference
		is released or if the application quits.  If the application
		passes TRUE, the application can release the reference or
		exit and the connection will be maintained until a timeout
		event, until a specific stop request occurs, or until an
		error is encountered.
	@result Returns TRUE if the connection was correctly started (the
		actual connection is not established yet, and the connection
		status needs to be periodically checked); FALSE if the
		connection request was not started.  The error must be
		retrieved from the SCError function.
 */
Boolean
SCNetworkConnectionStart			(
						SCNetworkConnectionRef				connection,
						CFDictionaryRef			__nullable	userOptions,
						Boolean						linger
						)			__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);


/*!
	@function SCNetworkConnectionStop
	@discussion Stops the connection for the SCNetworkConnection.
		The disconnection process is asynchronous and the function
		will return immediately.  The connection status can be
		obtained by polling or by callback.  This function performs
		an arbitrated stop of the connection.  If several applications
		have marked their interest in the connection, by calling
		SCNetworkConnectionStart, the call will succeed but the
		actual connection will be maintained until the last interested
		application calls SCNetworkConnectionStop.

		In certain cases, you might want to stop the connection anyway.
		In these cases, you set the forceDisconnect argument to TRUE.
	@param connection The SCNetworkConnection to stop.
	@result Returns TRUE if the disconnection request succeeded;
		FALSE if the disconnection request failed.
		The error must be retrieved from the SCError function.
 */
Boolean
SCNetworkConnectionStop				(
						SCNetworkConnectionRef		connection,
						Boolean				forceDisconnect
						)			__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);


/*!
	@function SCNetworkConnectionCopyUserOptions
	@discussion Copies the user options used to start the connection.
		This is a mechanism a client can use to retrieve the user options
		previously passed to the SCNetworkConnectionStart function.
	@param connection The SCNetworkConnection to obtain options from.
	@result Returns the service dictionary containing the connection options.
		The dictionary can be empty if no user options were used.
		If NULL is returned, the error can be retrieved using the SCError function.
 */
CFDictionaryRef __nullable
SCNetworkConnectionCopyUserOptions		(
						SCNetworkConnectionRef		connection
						)			__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);


/*!
	@function SCNetworkConnectionScheduleWithRunLoop
	@discussion Schedules a connection with the run loop.
	@param connection The SCNetworkConnection to schedule.
	@param runLoop The run loop to schedule with.
	@param runLoopMode The run loop mode.
	@result Returns TRUE if the connection is scheduled successfully;
		FALSE if the scheduling failed.
		The error can be retrieved using the SCError function.
 */
Boolean
SCNetworkConnectionScheduleWithRunLoop		(
						SCNetworkConnectionRef		connection,
						CFRunLoopRef			runLoop,
						CFStringRef			runLoopMode
						)			__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);


/*!
	@function SCNetworkConnectionUnscheduleFromRunLoop
	@discussion Unschedules a connection from the run loop.
	@param connection The SCNetworkConnection to unschedule.
	@param runLoop The run loop to unschedule from.
	@param runLoopMode The run loop mode.
	@result Returns TRUE if the connection is unscheduled successfully;
		FALSE if the unscheduling failed.
		The error can be retrieved using the SCError function.
 */
Boolean
SCNetworkConnectionUnscheduleFromRunLoop	(
						SCNetworkConnectionRef		connection,
						CFRunLoopRef			runLoop,
						CFStringRef			runLoopMode
						)			__OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);


/*!
	 @function SCNetworkConnectionSetDispatchQueue
	 @discussion Caller provides a dispatch queue on which the callback contained in connection will run.
	 @param connection The SCNetworkConnection to notify.
	 @param queue The libdispatch queue to run the callback on.
		Pass NULL to disable notifications, and release queue.
	 @result Returns TRUE if the notifications have been enabled/disabled as desired;
		 FALSE if not.
		 The error can be retrieved using the SCError function.
 */
Boolean
SCNetworkConnectionSetDispatchQueue		(
						 SCNetworkConnectionRef				connection,
						 dispatch_queue_t		__nullable	queue
						 )			__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

__END_DECLS

CF_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#endif /* _SCNETWORKCONNECTION_H */
// ==========  SystemConfiguration.framework/Headers/SCSchemaDefinitions.h
/*
 * Copyright (c) 2000-2015 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

/*
 * This file is automatically generated
 * DO NOT EDIT!
 */

/*
 * Reserved Keys
 *
 *   kSCResvLink                                        "__LINK__"                     CFString
 *   kSCResvInactive                                    "__INACTIVE__"
 *
 * Generic Keys
 *
 *   kSCPropInterfaceName                               "InterfaceName"                CFString
 *   kSCPropMACAddress                                  "MACAddress"                   CFString
 *   kSCPropUserDefinedName                             "UserDefinedName"              CFString
 *   kSCPropVersion                                     "Version"                      CFString
 *
 * Preference Keys
 *
 *   kSCPrefCurrentSet                                  "CurrentSet"                   CFString
 *   kSCPrefNetworkServices                             "NetworkServices"              CFDictionary
 *   kSCPrefSets                                        "Sets"                         CFDictionary
 *   kSCPrefSystem                                      "System"                       CFDictionary
 *
 * Component Keys
 *
 *   kSCCompNetwork                                     "Network"
 *   kSCCompService                                     "Service"
 *   kSCCompGlobal                                      "Global"
 *   kSCCompHostNames                                   "HostNames"
 *   kSCCompInterface                                   "Interface"
 *   kSCCompSystem                                      "System"
 *   kSCCompUsers                                       "Users"
 *
 *   --- Regex pattern which matches any component ---
 *   kSCCompAnyRegex                                    "[^/]+"
 *
 * Network Entity Keys
 *
 *   kSCEntNetAirPort                                   "AirPort"                      CFDictionary
 *   kSCEntNetDHCP                                      "DHCP"                         CFDictionary
 *   kSCEntNetDNS                                       "DNS"                          CFDictionary
 *   kSCEntNetEthernet                                  "Ethernet"                     CFDictionary
 *   kSCEntNetFireWire                                  "FireWire"                     CFDictionary
 *   kSCEntNetInterface                                 "Interface"                    CFDictionary
 *   kSCEntNetIPSec                                     "IPSec"                        CFDictionary
 *   kSCEntNetIPv4                                      "IPv4"                         CFDictionary
 *   kSCEntNetIPv6                                      "IPv6"                         CFDictionary
 *   kSCEntNetL2TP                                      "L2TP"                         CFDictionary
 *   kSCEntNetLink                                      "Link"                         CFDictionary
 *   kSCEntNetModem                                     "Modem"                        CFDictionary
 *   kSCEntNetPPP                                       "PPP"                          CFDictionary
 *   kSCEntNetPPPoE                                     "PPPoE"                        CFDictionary
 *   kSCEntNetPPPSerial                                 "PPPSerial"                    CFDictionary
 *   kSCEntNetPPTP                                      "PPTP"                         CFDictionary
 *   kSCEntNetProxies                                   "Proxies"                      CFDictionary
 *   kSCEntNetSMB                                       "SMB"                          CFDictionary
 *   kSCEntNet6to4                                      "6to4"                         CFDictionary
 *
 * kSCCompNetwork Properties
 *
 *   kSCPropNetOverridePrimary                          "OverridePrimary"              CFNumber (0 or 1)
 *   kSCPropNetServiceOrder                             "ServiceOrder"                 CFArray[CFString]
 *   kSCPropNetPPPOverridePrimary                       "PPPOverridePrimary"           CFNumber (0 or 1)
 *
 * kSCCompNetworkInterface Properties
 *
 *   kSCPropNetInterfaces                               "Interfaces"                   CFArray[CFString]
 *
 * kSCCompNetworkHostNames Properties
 *
 *   kSCPropNetLocalHostName                            "LocalHostName"                CFString
 *
 * kSCEntNetDNS Entity Keys
 *
 *   kSCPropNetDNSDomainName                            "DomainName"                   CFString
 *   kSCPropNetDNSOptions                               "Options"                      CFString
 *   kSCPropNetDNSSearchDomains                         "SearchDomains"                CFArray[CFString]
 *   kSCPropNetDNSSearchOrder                           "SearchOrder"                  CFNumber
 *   kSCPropNetDNSServerAddresses                       "ServerAddresses"              CFArray[CFString]
 *   kSCPropNetDNSServerPort                            "ServerPort"                   CFNumber
 *   kSCPropNetDNSServerTimeout                         "ServerTimeout"                CFNumber
 *   kSCPropNetDNSSortList                              "SortList"                     CFArray[CFString]
 *   kSCPropNetDNSSupplementalMatchDomains              "SupplementalMatchDomains"     CFArray[CFString]
 *   kSCPropNetDNSSupplementalMatchOrders               "SupplementalMatchOrders"      CFArray[CFNumber]
 *
 * kSCEntNetEthernet (Hardware) Entity Keys
 *
 *   kSCPropNetEthernetMediaSubType                     "MediaSubType"                 CFString
 *   kSCPropNetEthernetMediaOptions                     "MediaOptions"                 CFArray[CFString]
 *   kSCPropNetEthernetMTU                              "MTU"                          CFNumber
 *
 * kSCEntNetFireWire (Hardware) Entity Keys
 *
 *   * RESERVED FOR FUTURE USE *
 *
 * kSCEntNetInterface Entity Keys
 *
 *   kSCPropNetInterfaceDeviceName                      "DeviceName"                   CFString
 *   kSCPropNetInterfaceHardware                        "Hardware"                     CFString
 *   kSCPropNetInterfaceType                            "Type"                         CFString
 *   kSCPropNetInterfaceSubType                         "SubType"                      CFString
 *   kSCPropNetInterfaceSupportsModemOnHold             "SupportsModemOnHold"          CFNumber (0 or 1)
 *
 *   --- kSCPropNetInterfaceType values ---
 *   kSCValNetInterfaceTypeEthernet                     "Ethernet"
 *   kSCValNetInterfaceTypeFireWire                     "FireWire"
 *   kSCValNetInterfaceTypePPP                          "PPP"
 *   kSCValNetInterfaceType6to4                         "6to4"
 *   kSCValNetInterfaceTypeIPSec                        "IPSec"
 *
 *   --- kSCPropNetServiceSubType values (for PPP) ---
 *   kSCValNetInterfaceSubTypePPPoE                     "PPPoE"
 *   kSCValNetInterfaceSubTypePPPSerial                 "PPPSerial"
 *   kSCValNetInterfaceSubTypePPTP                      "PPTP"
 *   kSCValNetInterfaceSubTypeL2TP                      "L2TP"
 *
 * kSCEntNetIPSec Entity Keys
 *
 *   kSCPropNetIPSecAuthenticationMethod                "AuthenticationMethod"         CFString
 *   kSCPropNetIPSecLocalCertificate                    "LocalCertificate"             CFData
 *   kSCPropNetIPSecLocalIdentifier                     "LocalIdentifier"              CFString
 *   kSCPropNetIPSecLocalIdentifierType                 "LocalIdentifierType"          CFString
 *   kSCPropNetIPSecSharedSecret                        "SharedSecret"                 CFString
 *   kSCPropNetIPSecSharedSecretEncryption              "SharedSecretEncryption"       CFString
 *   kSCPropNetIPSecConnectTime                         "ConnectTime"                  CFNumber
 *   kSCPropNetIPSecRemoteAddress                       "RemoteAddress"                CFString
 *   kSCPropNetIPSecStatus                              "Status"                       CFNumber
 *   kSCPropNetIPSecXAuthEnabled                        "XAuthEnabled"                 CFNumber (0 or 1)
 *   kSCPropNetIPSecXAuthName                           "XAuthName"                    CFString
 *   kSCPropNetIPSecXAuthPassword                       "XAuthPassword"                CFString
 *   kSCPropNetIPSecXAuthPasswordEncryption             "XAuthPasswordEncryption"      CFString
 *
 *   --- kSCPropNetIPSecAuthenticationMethod values ---
 *   kSCValNetIPSecAuthenticationMethodSharedSecret     "SharedSecret"
 *   kSCValNetIPSecAuthenticationMethodCertificate      "Certificate"
 *   kSCValNetIPSecAuthenticationMethodHybrid           "Hybrid"
 *
 *   --- kSCPropNetIPSecLocalIdentifierType values ---
 *   kSCValNetIPSecLocalIdentifierTypeKeyID             "KeyID"
 *
 *   --- kSCPropNetIPSecSharedSecretEncryption values ---
 *   kSCValNetIPSecSharedSecretEncryptionKeychain       "Keychain"
 *
 *   --- kSCPropNetIPSecXAuthPasswordEncryption values ---
 *   kSCValNetIPSecXAuthPasswordEncryptionKeychain      "Keychain"
 *   kSCValNetIPSecXAuthPasswordEncryptionPrompt        "Prompt"
 *
 * kSCEntNetIPv4 Entity Keys
 *
 *   kSCPropNetIPv4Addresses                            "Addresses"                    CFArray[CFString]
 *   kSCPropNetIPv4ConfigMethod                         "ConfigMethod"                 CFString
 *   kSCPropNetIPv4DHCPClientID                         "DHCPClientID"                 CFString
 *   kSCPropNetIPv4Router                               "Router"                       CFString
 *   kSCPropNetIPv4SubnetMasks                          "SubnetMasks"                  CFArray[CFString]
 *   kSCPropNetIPv4DestAddresses                        "DestAddresses"                CFArray[CFString]
 *   kSCPropNetIPv4BroadcastAddresses                   "BroadcastAddresses"           CFArray[CFString]
 *
 *   --- kSCPropNetIPv4ConfigMethod values ---
 *   kSCValNetIPv4ConfigMethodAutomatic                 "Automatic"
 *   kSCValNetIPv4ConfigMethodBOOTP                     "BOOTP"
 *   kSCValNetIPv4ConfigMethodDHCP                      "DHCP"
 *   kSCValNetIPv4ConfigMethodINFORM                    "INFORM"
 *   kSCValNetIPv4ConfigMethodLinkLocal                 "LinkLocal"
 *   kSCValNetIPv4ConfigMethodManual                    "Manual"
 *   kSCValNetIPv4ConfigMethodPPP                       "PPP"
 *
 * kSCEntNetIPv6 Entity Keys
 *
 *   kSCPropNetIPv6Addresses                            "Addresses"                    CFArray[CFString]
 *   kSCPropNetIPv6ConfigMethod                         "ConfigMethod"                 CFString
 *   kSCPropNetIPv6DestAddresses                        "DestAddresses"                CFArray[CFString]
 *   kSCPropNetIPv6Flags                                "Flags"                        CFNumber
 *   kSCPropNetIPv6PrefixLength                         "PrefixLength"                 CFArray[CFNumber]
 *   kSCPropNetIPv6Router                               "Router"                       CFString
 *
 *   --- kSCPropNetIPv6ConfigMethod values ---
 *   kSCValNetIPv6ConfigMethodAutomatic                 "Automatic"
 *   kSCValNetIPv6ConfigMethodLinkLocal                 "LinkLocal"
 *   kSCValNetIPv6ConfigMethodManual                    "Manual"
 *   kSCValNetIPv6ConfigMethodRouterAdvertisement       "RouterAdvertisement"
 *   kSCValNetIPv6ConfigMethod6to4                      "6to4"
 *
 * kSCEntNet6to4 Entity Keys
 *
 *   kSCPropNet6to4Relay                                "Relay"                        CFString
 *
 * kSCEntNetLink Entity Keys
 *
 *   kSCPropNetLinkActive                               "Active"                       CFBoolean
 *   kSCPropNetLinkDetaching                            "Detaching"                    CFBoolean
 *
 * kSCEntNetModem (Hardware) Entity Keys
 *
 *   kSCPropNetModemAccessPointName                     "AccessPointName"              CFString
 *   kSCPropNetModemConnectionPersonality               "ConnectionPersonality"        CFString
 *   kSCPropNetModemConnectionScript                    "ConnectionScript"             CFString
 *   kSCPropNetModemConnectSpeed                        "ConnectSpeed"                 CFNumber
 *   kSCPropNetModemDataCompression                     "DataCompression"              CFNumber (0 or 1)
 *   kSCPropNetModemDeviceContextID                     "DeviceContextID"              CFString
 *   kSCPropNetModemDeviceModel                         "DeviceModel"                  CFString
 *   kSCPropNetModemDeviceVendor                        "DeviceVendor"                 CFString
 *   kSCPropNetModemDialMode                            "DialMode"                     CFString
 *   kSCPropNetModemErrorCorrection                     "ErrorCorrection"              CFNumber (0 or 1)
 *   kSCPropNetModemHoldCallWaitingAudibleAlert         "HoldCallWaitingAudibleAlert"  CFNumber (0 or 1)
 *   kSCPropNetModemHoldDisconnectOnAnswer              "HoldDisconnectOnAnswer"       CFNumber (0 or 1)
 *   kSCPropNetModemHoldEnabled                         "HoldEnabled"                  CFNumber (0 or 1)
 *   kSCPropNetModemHoldReminder                        "HoldReminder"                 CFNumber (0 or 1)
 *   kSCPropNetModemHoldReminderTime                    "HoldReminderTime"             CFNumber
 *   kSCPropNetModemNote                                "Note"                         CFString
 *   kSCPropNetModemPulseDial                           "PulseDial"                    CFNumber (0 or 1)
 *   kSCPropNetModemSpeaker                             "Speaker"                      CFNumber (0 or 1)
 *   kSCPropNetModemSpeed                               "Speed"                        CFNumber
 *
 *   --- kSCPropNetModemDialMode values ---
 *   kSCValNetModemDialModeIgnoreDialTone               "IgnoreDialTone"
 *   kSCValNetModemDialModeManual                       "Manual"
 *   kSCValNetModemDialModeWaitForDialTone              "WaitForDialTone"
 *
 * kSCEntNetPPP Entity Keys
 *
 *   kSCPropNetPPPACSPEnabled                           "ACSPEnabled"                  CFNumber (0 or 1)
 *   kSCPropNetPPPConnectTime                           "ConnectTime"                  CFNumber
 *   kSCPropNetPPPDeviceLastCause                       "DeviceLastCause"              CFNumber
 *   kSCPropNetPPPDialOnDemand                          "DialOnDemand"                 CFNumber (0 or 1)
 *   kSCPropNetPPPDisconnectOnFastUserSwitch            "DisconnectOnFastUserSwitch"   CFNumber (0 or 1)
 *   kSCPropNetPPPDisconnectOnIdle                      "DisconnectOnIdle"             CFNumber (0 or 1)
 *   kSCPropNetPPPDisconnectOnIdleTimer                 "DisconnectOnIdleTimer"        CFNumber
 *   kSCPropNetPPPDisconnectOnLogout                    "DisconnectOnLogout"           CFNumber (0 or 1)
 *   kSCPropNetPPPDisconnectOnSleep                     "DisconnectOnSleep"            CFNumber (0 or 1)
 *   kSCPropNetPPPDisconnectTime                        "DisconnectTime"               CFNumber
 *   kSCPropNetPPPIdleReminderTimer                     "IdleReminderTimer"            CFNumber
 *   kSCPropNetPPPIdleReminder                          "IdleReminder"                 CFNumber (0 or 1)
 *   kSCPropNetPPPLastCause                             "LastCause"                    CFNumber
 *   kSCPropNetPPPLogfile                               "Logfile"                      CFString
 *   kSCPropNetPPPPlugins                               "Plugins"                      CFArray[CFString]
 *   kSCPropNetPPPRetryConnectTime                      "RetryConnectTime"             CFNumber
 *   kSCPropNetPPPSessionTimer                          "SessionTimer"                 CFNumber
 *   kSCPropNetPPPStatus                                "Status"                       CFNumber
 *   kSCPropNetPPPUseSessionTimer                       "UseSessionTimer"              CFNumber (0 or 1)
 *   kSCPropNetPPPVerboseLogging                        "VerboseLogging"               CFNumber (0 or 1)
 *
 *   --- Auth: ---
 *   kSCPropNetPPPAuthEAPPlugins                        "AuthEAPPlugins"               CFArray[CFString]
 *   kSCPropNetPPPAuthName                              "AuthName"                     CFString
 *   kSCPropNetPPPAuthPassword                          "AuthPassword"                 CFString
 *   kSCPropNetPPPAuthPasswordEncryption                "AuthPasswordEncryption"       CFString
 *   kSCPropNetPPPAuthPrompt                            "AuthPrompt"                   CFString
 *   kSCPropNetPPPAuthProtocol                          "AuthProtocol"                 CFArray[CFString]
 *
 *   --- kSCPropNetPPPAuthPasswordEncryption values ---
 *   kSCValNetPPPAuthPasswordEncryptionKeychain         "Keychain"
 *   kSCValNetPPPAuthPasswordEncryptionToken            "Token"
 *
 *   --- kSCPropNetPPPAuthPrompt values ---
 *   kSCValNetPPPAuthPromptBefore                       "Before"                       CFString
 *   kSCValNetPPPAuthPromptAfter                        "After"                        CFString
 *
 *   --- kSCPropNetPPPAuthProtocol values ---
 *   kSCValNetPPPAuthProtocolCHAP                       "CHAP"                         CFString
 *   kSCValNetPPPAuthProtocolEAP                        "EAP"                          CFString
 *   kSCValNetPPPAuthProtocolMSCHAP1                    "MSCHAP1"                      CFString
 *   kSCValNetPPPAuthProtocolMSCHAP2                    "MSCHAP2"                      CFString
 *   kSCValNetPPPAuthProtocolPAP                        "PAP"                          CFString
 *
 *   --- Comm: ---
 *   kSCPropNetPPPCommAlternateRemoteAddress            "CommAlternateRemoteAddress"   CFString
 *   kSCPropNetPPPCommConnectDelay                      "CommConnectDelay"             CFNumber
 *   kSCPropNetPPPCommDisplayTerminalWindow             "CommDisplayTerminalWindow"    CFNumber (0 or 1)
 *   kSCPropNetPPPCommRedialCount                       "CommRedialCount"              CFNumber
 *   kSCPropNetPPPCommRedialEnabled                     "CommRedialEnabled"            CFNumber (0 or 1)
 *   kSCPropNetPPPCommRedialInterval                    "CommRedialInterval"           CFNumber
 *   kSCPropNetPPPCommRemoteAddress                     "CommRemoteAddress"            CFString
 *   kSCPropNetPPPCommTerminalScript                    "CommTerminalScript"           CFString
 *   kSCPropNetPPPCommUseTerminalScript                 "CommUseTerminalScript"        CFNumber (0 or 1)
 *
 *   --- CCP: ---
 *   kSCPropNetPPPCCPEnabled                            "CCPEnabled"                   CFNumber (0 or 1)
 *   kSCPropNetPPPCCPMPPE40Enabled                      "CCPMPPE40Enabled"             CFNumber (0 or 1)
 *   kSCPropNetPPPCCPMPPE128Enabled                     "CCPMPPE128Enabled"            CFNumber (0 or 1)
 *
 *   --- IPCP: ---
 *   kSCPropNetPPPIPCPCompressionVJ                     "IPCPCompressionVJ"            CFNumber (0 or 1)
 *   kSCPropNetPPPIPCPUsePeerDNS                        "IPCPUsePeerDNS"               CFNumber (0 or 1)
 *
 *   --- LCP: ---
 *   kSCPropNetPPPLCPEchoEnabled                        "LCPEchoEnabled"               CFNumber (0 or 1)
 *   kSCPropNetPPPLCPEchoFailure                        "LCPEchoFailure"               CFNumber
 *   kSCPropNetPPPLCPEchoInterval                       "LCPEchoInterval"              CFNumber
 *   kSCPropNetPPPLCPCompressionACField                 "LCPCompressionACField"        CFNumber (0 or 1)
 *   kSCPropNetPPPLCPCompressionPField                  "LCPCompressionPField"         CFNumber (0 or 1)
 *   kSCPropNetPPPLCPMRU                                "LCPMRU"                       CFNumber
 *   kSCPropNetPPPLCPMTU                                "LCPMTU"                       CFNumber
 *   kSCPropNetPPPLCPReceiveACCM                        "LCPReceiveACCM"               CFNumber
 *   kSCPropNetPPPLCPTransmitACCM                       "LCPTransmitACCM"              CFNumber
 *
 * kSCEntNetPPPoE Entity Keys
 *
 *   * RESERVED FOR FUTURE USE *
 *
 * kSCEntNetPPPSerial Entity Keys
 *
 *   * RESERVED FOR FUTURE USE *
 *
 * kSCEntNetPPTP Entity Keys
 *
 *   * RESERVED FOR FUTURE USE *
 *
 * kSCEntNetL2TP Entity Keys
 *
 *   kSCPropNetL2TPIPSecSharedSecret                    "IPSecSharedSecret"            CFString
 *   kSCPropNetL2TPIPSecSharedSecretEncryption          "IPSecSharedSecretEncryption"  CFString
 *   kSCPropNetL2TPTransport                            "Transport"                    CFString
 *
 *   --- kSCPropNetL2TPIPSecSharedSecretEncryption values ---
 *   kSCValNetL2TPIPSecSharedSecretEncryptionKeychain   "Keychain"
 *
 *   --- kSCPropNetL2TPTransport values ---
 *   kSCValNetL2TPTransportIP                           "IP"
 *   kSCValNetL2TPTransportIPSec                        "IPSec"
 *
 * kSCEntNetProxies Entity Keys
 *
 *   kSCPropNetProxiesExceptionsList                    "ExceptionsList"               CFArray[CFString]
 *   kSCPropNetProxiesExcludeSimpleHostnames            "ExcludeSimpleHostnames"       CFNumber (0 or 1)
 *   kSCPropNetProxiesFTPEnable                         "FTPEnable"                    CFNumber (0 or 1)
 *   kSCPropNetProxiesFTPPassive                        "FTPPassive"                   CFNumber (0 or 1)
 *   kSCPropNetProxiesFTPPort                           "FTPPort"                      CFNumber
 *   kSCPropNetProxiesFTPProxy                          "FTPProxy"                     CFString
 *   kSCPropNetProxiesGopherEnable                      "GopherEnable"                 CFNumber (0 or 1)
 *   kSCPropNetProxiesGopherPort                        "GopherPort"                   CFNumber
 *   kSCPropNetProxiesGopherProxy                       "GopherProxy"                  CFString
 *   kSCPropNetProxiesHTTPEnable                        "HTTPEnable"                   CFNumber (0 or 1)
 *   kSCPropNetProxiesHTTPPort                          "HTTPPort"                     CFNumber
 *   kSCPropNetProxiesHTTPProxy                         "HTTPProxy"                    CFString
 *   kSCPropNetProxiesHTTPSEnable                       "HTTPSEnable"                  CFNumber (0 or 1)
 *   kSCPropNetProxiesHTTPSPort                         "HTTPSPort"                    CFNumber
 *   kSCPropNetProxiesHTTPSProxy                        "HTTPSProxy"                   CFString
 *   kSCPropNetProxiesRTSPEnable                        "RTSPEnable"                   CFNumber (0 or 1)
 *   kSCPropNetProxiesRTSPPort                          "RTSPPort"                     CFNumber
 *   kSCPropNetProxiesRTSPProxy                         "RTSPProxy"                    CFString
 *   kSCPropNetProxiesSOCKSEnable                       "SOCKSEnable"                  CFNumber (0 or 1)
 *   kSCPropNetProxiesSOCKSPort                         "SOCKSPort"                    CFNumber
 *   kSCPropNetProxiesSOCKSProxy                        "SOCKSProxy"                   CFString
 *   kSCPropNetProxiesProxyAutoConfigEnable             "ProxyAutoConfigEnable"        CFNumber (0 or 1)
 *   kSCPropNetProxiesProxyAutoConfigJavaScript         "ProxyAutoConfigJavaScript"    CFString
 *   kSCPropNetProxiesProxyAutoConfigURLString          "ProxyAutoConfigURLString"     CFString
 *   kSCPropNetProxiesProxyAutoDiscoveryEnable          "ProxyAutoDiscoveryEnable"     CFNumber (0 or 1)
 *
 * kSCEntNetSMB Entity Keys
 *
 *   kSCPropNetSMBNetBIOSName                           "NetBIOSName"                  CFString
 *   kSCPropNetSMBNetBIOSNodeType                       "NetBIOSNodeType"              CFString
 *   kSCPropNetSMBNetBIOSScope                          "NetBIOSScope"                 CFString
 *   kSCPropNetSMBWINSAddresses                         "WINSAddresses"                CFArray[CFString]
 *   kSCPropNetSMBWorkgroup                             "Workgroup"                    CFString
 *
 *   --- kSCPropNetSMBNetBIOSNodeType values ---
 *   kSCValNetSMBNetBIOSNodeTypeBroadcast               "Broadcast"
 *   kSCValNetSMBNetBIOSNodeTypePeer                    "Peer"
 *   kSCValNetSMBNetBIOSNodeTypeMixed                   "Mixed"
 *   kSCValNetSMBNetBIOSNodeTypeHybrid                  "Hybrid"
 *
 * kSCCompUsers Entity Keys
 *
 *   kSCEntUsersConsoleUser                             "ConsoleUser"
 *
 * kSCCompSystem Properties
 *
 *   kSCPropSystemComputerName                          "ComputerName"                 CFString
 *   kSCPropSystemComputerNameEncoding                  "ComputerNameEncoding"         CFNumber
 *
 * SCDynamicStore "domain" prefixes
 *
 *   kSCDynamicStoreDomainFile                          "File:"
 *   kSCDynamicStoreDomainPlugin                        "Plugin:"
 *   kSCDynamicStoreDomainSetup                         "Setup:"
 *   kSCDynamicStoreDomainState                         "State:"
 *   kSCDynamicStoreDomainPrefs                         "Prefs:"
 *
 * Preference ("location") Keys
 *
 *   kSCDynamicStorePropSetupCurrentSet                 "CurrentSet"                   CFString
 *   kSCDynamicStorePropSetupLastUpdated                "LastUpdated"
 *
 * Common/shared Keys
 *
 *   kSCDynamicStorePropNetInterfaces                   "Interfaces"                   CFArray[CFString]
 *   kSCDynamicStorePropNetPrimaryInterface             "PrimaryInterface"             CFString
 *   kSCDynamicStorePropNetPrimaryService               "PrimaryService"               CFString
 *   kSCDynamicStorePropNetServiceIDs                   "ServiceIDs"                   CFArray[CFString]
 */


#ifndef	_SCSCHEMADEFINITIONS_H
#ifdef	USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS
#include <SystemConfiguration/_SCSchemaDefinitions.h>
#else	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#define	_SCSCHEMADEFINITIONS_H

#include <Availability.h>
#include <TargetConditionals.h>
#include <CoreFoundation/CFString.h>

/*!
 *	@header SCSchemaDefinitions
 */


CF_ASSUME_NONNULL_BEGIN

/*!
  @const kSCResvLink
  @discussion Value is a CFString
 */
extern const CFStringRef kSCResvLink                                        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCResvLink kSCResvLink

/*!
  @const kSCResvInactive
 */
extern const CFStringRef kSCResvInactive                                    __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCResvInactive kSCResvInactive

/*!
  @const kSCPropInterfaceName
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropInterfaceName                               __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropInterfaceName kSCPropInterfaceName

/*!
  @const kSCPropMACAddress
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropMACAddress                                  __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropMACAddress kSCPropMACAddress

/*!
  @const kSCPropUserDefinedName
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropUserDefinedName                             __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropUserDefinedName kSCPropUserDefinedName

/*!
  @const kSCPropVersion
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropVersion                                     __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropVersion kSCPropVersion

/*!
  @group Preference Keys
 */

/*!
  @const kSCPrefCurrentSet
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPrefCurrentSet                                  __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPrefCurrentSet kSCPrefCurrentSet

/*!
  @const kSCPrefNetworkServices
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCPrefNetworkServices                             __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPrefNetworkServices kSCPrefNetworkServices

/*!
  @const kSCPrefSets
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCPrefSets                                        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPrefSets kSCPrefSets

/*!
  @const kSCPrefSystem
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCPrefSystem                                      __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPrefSystem kSCPrefSystem

/*!
  @group Component Keys
 */

/*!
  @const kSCCompNetwork
 */
extern const CFStringRef kSCCompNetwork                                     __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCCompNetwork kSCCompNetwork

/*!
  @const kSCCompService
 */
extern const CFStringRef kSCCompService                                     __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCCompService kSCCompService

/*!
  @const kSCCompGlobal
 */
extern const CFStringRef kSCCompGlobal                                      __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCCompGlobal kSCCompGlobal

/*!
  @const kSCCompHostNames
 */
extern const CFStringRef kSCCompHostNames                                   __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCCompHostNames kSCCompHostNames

/*!
  @const kSCCompInterface
 */
extern const CFStringRef kSCCompInterface                                   __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCCompInterface kSCCompInterface

/*!
  @const kSCCompSystem
 */
extern const CFStringRef kSCCompSystem                                      __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCCompSystem kSCCompSystem

/*!
  @const kSCCompUsers
 */
extern const CFStringRef kSCCompUsers                                       __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCCompUsers kSCCompUsers

/*!
  @const kSCCompAnyRegex
 */
extern const CFStringRef kSCCompAnyRegex                                    __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCCompAnyRegex kSCCompAnyRegex

/*!
  @group Network Entity Keys
 */

/*!
  @const kSCEntNetAirPort
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetAirPort                                   __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCEntNetAirPort kSCEntNetAirPort

/*!
  @const kSCEntNetAppleTalk
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetAppleTalk                                 __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);
#define kSCEntNetAppleTalk kSCEntNetAppleTalk

/*!
  @const kSCEntNetDHCP
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetDHCP                                      __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCEntNetDHCP kSCEntNetDHCP

/*!
  @const kSCEntNetDNS
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetDNS                                       __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCEntNetDNS kSCEntNetDNS

/*!
  @const kSCEntNetEthernet
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetEthernet                                  __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCEntNetEthernet kSCEntNetEthernet

/*!
  @const kSCEntNetFireWire
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetFireWire                                  __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCEntNetFireWire kSCEntNetFireWire

/*!
  @const kSCEntNetInterface
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetInterface                                 __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCEntNetInterface kSCEntNetInterface

/*!
  @const kSCEntNetIPSec
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetIPSec                                     __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCEntNetIPSec kSCEntNetIPSec

/*!
  @const kSCEntNetIPv4
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetIPv4                                      __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCEntNetIPv4 kSCEntNetIPv4

/*!
  @const kSCEntNetIPv6
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetIPv6                                      __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCEntNetIPv6 kSCEntNetIPv6

/*!
  @const kSCEntNetL2TP
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetL2TP                                      __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCEntNetL2TP kSCEntNetL2TP

/*!
  @const kSCEntNetLink
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetLink                                      __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCEntNetLink kSCEntNetLink

/*!
  @const kSCEntNetModem
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetModem                                     __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCEntNetModem kSCEntNetModem

/*!
  @const kSCEntNetNetInfo
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetNetInfo                                   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);
#define kSCEntNetNetInfo kSCEntNetNetInfo

/*!
  @const kSCEntNetPPP
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetPPP                                       __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCEntNetPPP kSCEntNetPPP

/*!
  @const kSCEntNetPPPoE
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetPPPoE                                     __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCEntNetPPPoE kSCEntNetPPPoE

/*!
  @const kSCEntNetPPPSerial
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetPPPSerial                                 __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCEntNetPPPSerial kSCEntNetPPPSerial

/*!
  @const kSCEntNetPPTP
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetPPTP                                      __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCEntNetPPTP kSCEntNetPPTP

/*!
  @const kSCEntNetProxies
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetProxies                                   __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCEntNetProxies kSCEntNetProxies

/*!
  @const kSCEntNetSMB
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNetSMB                                       __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCEntNetSMB kSCEntNetSMB

/*!
  @const kSCEntNet6to4
  @discussion Value is a CFDictionary
 */
extern const CFStringRef kSCEntNet6to4                                      __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCEntNet6to4 kSCEntNet6to4

/*!
  @group kSCCompNetwork Properties
 */

/*!
  @const kSCPropNetOverridePrimary
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetOverridePrimary                          __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetOverridePrimary kSCPropNetOverridePrimary

/*!
  @const kSCPropNetServiceOrder
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetServiceOrder                             __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetServiceOrder kSCPropNetServiceOrder

/*!
  @const kSCPropNetPPPOverridePrimary
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPOverridePrimary                       __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPOverridePrimary kSCPropNetPPPOverridePrimary

/*!
  @group kSCCompNetworkInterface Properties
 */

/*!
  @const kSCPropNetInterfaces
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetInterfaces                               __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetInterfaces kSCPropNetInterfaces

/*!
  @group kSCCompNetworkHostNames Properties
 */

/*!
  @const kSCPropNetLocalHostName
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetLocalHostName                            __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetLocalHostName kSCPropNetLocalHostName

/*!
  @group kSCEntNetAirPort (Hardware) Entity Keys
 */

/*!
  @const kSCPropNetAirPortAllowNetCreation
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetAirPortAllowNetCreation                  __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetAirPortAllowNetCreation kSCPropNetAirPortAllowNetCreation

/*!
  @const kSCPropNetAirPortAuthPassword
  @discussion Value is a CFData
 */
extern const CFStringRef kSCPropNetAirPortAuthPassword                      __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetAirPortAuthPassword kSCPropNetAirPortAuthPassword

/*!
  @const kSCPropNetAirPortAuthPasswordEncryption
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetAirPortAuthPasswordEncryption            __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetAirPortAuthPasswordEncryption kSCPropNetAirPortAuthPasswordEncryption

/*!
  @const kSCPropNetAirPortJoinMode
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetAirPortJoinMode                          __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetAirPortJoinMode kSCPropNetAirPortJoinMode

/*!
  @const kSCPropNetAirPortPowerEnabled
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetAirPortPowerEnabled                      __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetAirPortPowerEnabled kSCPropNetAirPortPowerEnabled

/*!
  @const kSCPropNetAirPortPreferredNetwork
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetAirPortPreferredNetwork                  __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetAirPortPreferredNetwork kSCPropNetAirPortPreferredNetwork

/*!
  @const kSCPropNetAirPortSavePasswords
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetAirPortSavePasswords                     __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetAirPortSavePasswords kSCPropNetAirPortSavePasswords

/*!
  @const kSCValNetAirPortJoinModeAutomatic
 */
extern const CFStringRef kSCValNetAirPortJoinModeAutomatic                  __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_3,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);
#define kSCValNetAirPortJoinModeAutomatic kSCValNetAirPortJoinModeAutomatic

/*!
  @const kSCValNetAirPortJoinModePreferred
 */
extern const CFStringRef kSCValNetAirPortJoinModePreferred                  __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);
#define kSCValNetAirPortJoinModePreferred kSCValNetAirPortJoinModePreferred

/*!
  @const kSCValNetAirPortJoinModeRanked
 */
extern const CFStringRef kSCValNetAirPortJoinModeRanked                     __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_4,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);
#define kSCValNetAirPortJoinModeRanked kSCValNetAirPortJoinModeRanked

/*!
  @const kSCValNetAirPortJoinModeRecent
 */
extern const CFStringRef kSCValNetAirPortJoinModeRecent                     __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);
#define kSCValNetAirPortJoinModeRecent kSCValNetAirPortJoinModeRecent

/*!
  @const kSCValNetAirPortJoinModeStrongest
 */
extern const CFStringRef kSCValNetAirPortJoinModeStrongest                  __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);
#define kSCValNetAirPortJoinModeStrongest kSCValNetAirPortJoinModeStrongest

/*!
  @const kSCValNetAirPortAuthPasswordEncryptionKeychain
 */
extern const CFStringRef kSCValNetAirPortAuthPasswordEncryptionKeychain     __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_3,__MAC_10_9,__IPHONE_NA,__IPHONE_NA);
#define kSCValNetAirPortAuthPasswordEncryptionKeychain kSCValNetAirPortAuthPasswordEncryptionKeychain

/*!
  @group kSCEntNetAppleTalk Entity Keys
 */

/*!
  @const kSCPropNetAppleTalkComputerName
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetAppleTalkComputerName                    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetAppleTalkComputerName kSCPropNetAppleTalkComputerName

/*!
  @const kSCPropNetAppleTalkComputerNameEncoding
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetAppleTalkComputerNameEncoding            __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetAppleTalkComputerNameEncoding kSCPropNetAppleTalkComputerNameEncoding

/*!
  @const kSCPropNetAppleTalkConfigMethod
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetAppleTalkConfigMethod                    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetAppleTalkConfigMethod kSCPropNetAppleTalkConfigMethod

/*!
  @const kSCPropNetAppleTalkDefaultZone
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetAppleTalkDefaultZone                     __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetAppleTalkDefaultZone kSCPropNetAppleTalkDefaultZone

/*!
  @const kSCPropNetAppleTalkNetworkID
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetAppleTalkNetworkID                       __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetAppleTalkNetworkID kSCPropNetAppleTalkNetworkID

/*!
  @const kSCPropNetAppleTalkNetworkRange
  @discussion Value is a CFArray[CFNumber]
 */
extern const CFStringRef kSCPropNetAppleTalkNetworkRange                    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetAppleTalkNetworkRange kSCPropNetAppleTalkNetworkRange

/*!
  @const kSCPropNetAppleTalkNodeID
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetAppleTalkNodeID                          __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetAppleTalkNodeID kSCPropNetAppleTalkNodeID

/*!
  @const kSCPropNetAppleTalkSeedNetworkRange
  @discussion Value is a CFArray[CFNumber]
 */
extern const CFStringRef kSCPropNetAppleTalkSeedNetworkRange                __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetAppleTalkSeedNetworkRange kSCPropNetAppleTalkSeedNetworkRange

/*!
  @const kSCPropNetAppleTalkSeedZones
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetAppleTalkSeedZones                       __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetAppleTalkSeedZones kSCPropNetAppleTalkSeedZones

/*!
  @const kSCValNetAppleTalkConfigMethodNode
 */
extern const CFStringRef kSCValNetAppleTalkConfigMethodNode                 __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);
#define kSCValNetAppleTalkConfigMethodNode kSCValNetAppleTalkConfigMethodNode

/*!
  @const kSCValNetAppleTalkConfigMethodRouter
 */
extern const CFStringRef kSCValNetAppleTalkConfigMethodRouter               __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);
#define kSCValNetAppleTalkConfigMethodRouter kSCValNetAppleTalkConfigMethodRouter

/*!
  @const kSCValNetAppleTalkConfigMethodSeedRouter
 */
extern const CFStringRef kSCValNetAppleTalkConfigMethodSeedRouter           __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);
#define kSCValNetAppleTalkConfigMethodSeedRouter kSCValNetAppleTalkConfigMethodSeedRouter

/*!
  @group kSCEntNetDNS Entity Keys
 */

/*!
  @const kSCPropNetDNSDomainName
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetDNSDomainName                            __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetDNSDomainName kSCPropNetDNSDomainName

/*!
  @const kSCPropNetDNSOptions
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetDNSOptions                               __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);
#define kSCPropNetDNSOptions kSCPropNetDNSOptions

/*!
  @const kSCPropNetDNSSearchDomains
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetDNSSearchDomains                         __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetDNSSearchDomains kSCPropNetDNSSearchDomains

/*!
  @const kSCPropNetDNSSearchOrder
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetDNSSearchOrder                           __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);
#define kSCPropNetDNSSearchOrder kSCPropNetDNSSearchOrder

/*!
  @const kSCPropNetDNSServerAddresses
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetDNSServerAddresses                       __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetDNSServerAddresses kSCPropNetDNSServerAddresses

/*!
  @const kSCPropNetDNSServerPort
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetDNSServerPort                            __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);
#define kSCPropNetDNSServerPort kSCPropNetDNSServerPort

/*!
  @const kSCPropNetDNSServerTimeout
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetDNSServerTimeout                         __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);
#define kSCPropNetDNSServerTimeout kSCPropNetDNSServerTimeout

/*!
  @const kSCPropNetDNSSortList
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetDNSSortList                              __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetDNSSortList kSCPropNetDNSSortList

/*!
  @const kSCPropNetDNSSupplementalMatchDomains
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetDNSSupplementalMatchDomains              __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);
#define kSCPropNetDNSSupplementalMatchDomains kSCPropNetDNSSupplementalMatchDomains

/*!
  @const kSCPropNetDNSSupplementalMatchOrders
  @discussion Value is a CFArray[CFNumber]
 */
extern const CFStringRef kSCPropNetDNSSupplementalMatchOrders               __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);
#define kSCPropNetDNSSupplementalMatchOrders kSCPropNetDNSSupplementalMatchOrders

/*!
  @group kSCEntNetEthernet (Hardware) Entity Keys
 */

/*!
  @const kSCPropNetEthernetMediaSubType
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetEthernetMediaSubType                     __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetEthernetMediaSubType kSCPropNetEthernetMediaSubType

/*!
  @const kSCPropNetEthernetMediaOptions
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetEthernetMediaOptions                     __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetEthernetMediaOptions kSCPropNetEthernetMediaOptions

/*!
  @const kSCPropNetEthernetMTU
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetEthernetMTU                              __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetEthernetMTU kSCPropNetEthernetMTU

/*!
  @group kSCEntNetFireWire (Hardware) Entity Keys
 */

/*!
  @group kSCEntNetInterface Entity Keys
 */

/*!
  @const kSCPropNetInterfaceDeviceName
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetInterfaceDeviceName                      __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetInterfaceDeviceName kSCPropNetInterfaceDeviceName

/*!
  @const kSCPropNetInterfaceHardware
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetInterfaceHardware                        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetInterfaceHardware kSCPropNetInterfaceHardware

/*!
  @const kSCPropNetInterfaceType
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetInterfaceType                            __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetInterfaceType kSCPropNetInterfaceType

/*!
  @const kSCPropNetInterfaceSubType
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetInterfaceSubType                         __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetInterfaceSubType kSCPropNetInterfaceSubType

/*!
  @const kSCPropNetInterfaceSupportsModemOnHold
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetInterfaceSupportsModemOnHold             __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetInterfaceSupportsModemOnHold kSCPropNetInterfaceSupportsModemOnHold

/*!
  @const kSCValNetInterfaceTypeEthernet
 */
extern const CFStringRef kSCValNetInterfaceTypeEthernet                     __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCValNetInterfaceTypeEthernet kSCValNetInterfaceTypeEthernet

/*!
  @const kSCValNetInterfaceTypeFireWire
 */
extern const CFStringRef kSCValNetInterfaceTypeFireWire                     __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCValNetInterfaceTypeFireWire kSCValNetInterfaceTypeFireWire

/*!
  @const kSCValNetInterfaceTypePPP
 */
extern const CFStringRef kSCValNetInterfaceTypePPP                          __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCValNetInterfaceTypePPP kSCValNetInterfaceTypePPP

/*!
  @const kSCValNetInterfaceType6to4
 */
extern const CFStringRef kSCValNetInterfaceType6to4                         __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCValNetInterfaceType6to4 kSCValNetInterfaceType6to4

/*!
  @const kSCValNetInterfaceTypeIPSec
 */
extern const CFStringRef kSCValNetInterfaceTypeIPSec                        __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
#define kSCValNetInterfaceTypeIPSec kSCValNetInterfaceTypeIPSec

/*!
  @const kSCValNetInterfaceSubTypePPPoE
 */
extern const CFStringRef kSCValNetInterfaceSubTypePPPoE                     __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCValNetInterfaceSubTypePPPoE kSCValNetInterfaceSubTypePPPoE

/*!
  @const kSCValNetInterfaceSubTypePPPSerial
 */
extern const CFStringRef kSCValNetInterfaceSubTypePPPSerial                 __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCValNetInterfaceSubTypePPPSerial kSCValNetInterfaceSubTypePPPSerial

/*!
  @const kSCValNetInterfaceSubTypePPTP
 */
extern const CFStringRef kSCValNetInterfaceSubTypePPTP                      __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCValNetInterfaceSubTypePPTP kSCValNetInterfaceSubTypePPTP

/*!
  @const kSCValNetInterfaceSubTypeL2TP
 */
extern const CFStringRef kSCValNetInterfaceSubTypeL2TP                      __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCValNetInterfaceSubTypeL2TP kSCValNetInterfaceSubTypeL2TP

/*!
  @group kSCEntNetIPSec Entity Keys
 */

/*!
  @const kSCPropNetIPSecAuthenticationMethod
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetIPSecAuthenticationMethod                __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCPropNetIPSecAuthenticationMethod kSCPropNetIPSecAuthenticationMethod

/*!
  @const kSCPropNetIPSecLocalCertificate
  @discussion Value is a CFData
 */
extern const CFStringRef kSCPropNetIPSecLocalCertificate                    __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCPropNetIPSecLocalCertificate kSCPropNetIPSecLocalCertificate

/*!
  @const kSCPropNetIPSecLocalIdentifier
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetIPSecLocalIdentifier                     __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCPropNetIPSecLocalIdentifier kSCPropNetIPSecLocalIdentifier

/*!
  @const kSCPropNetIPSecLocalIdentifierType
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetIPSecLocalIdentifierType                 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCPropNetIPSecLocalIdentifierType kSCPropNetIPSecLocalIdentifierType

/*!
  @const kSCPropNetIPSecSharedSecret
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetIPSecSharedSecret                        __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCPropNetIPSecSharedSecret kSCPropNetIPSecSharedSecret

/*!
  @const kSCPropNetIPSecSharedSecretEncryption
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetIPSecSharedSecretEncryption              __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCPropNetIPSecSharedSecretEncryption kSCPropNetIPSecSharedSecretEncryption

/*!
  @const kSCPropNetIPSecConnectTime
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetIPSecConnectTime                         __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
#define kSCPropNetIPSecConnectTime kSCPropNetIPSecConnectTime

/*!
  @const kSCPropNetIPSecRemoteAddress
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetIPSecRemoteAddress                       __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
#define kSCPropNetIPSecRemoteAddress kSCPropNetIPSecRemoteAddress

/*!
  @const kSCPropNetIPSecStatus
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetIPSecStatus                              __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
#define kSCPropNetIPSecStatus kSCPropNetIPSecStatus

/*!
  @const kSCPropNetIPSecXAuthEnabled
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetIPSecXAuthEnabled                        __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
#define kSCPropNetIPSecXAuthEnabled kSCPropNetIPSecXAuthEnabled

/*!
  @const kSCPropNetIPSecXAuthName
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetIPSecXAuthName                           __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
#define kSCPropNetIPSecXAuthName kSCPropNetIPSecXAuthName

/*!
  @const kSCPropNetIPSecXAuthPassword
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetIPSecXAuthPassword                       __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
#define kSCPropNetIPSecXAuthPassword kSCPropNetIPSecXAuthPassword

/*!
  @const kSCPropNetIPSecXAuthPasswordEncryption
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetIPSecXAuthPasswordEncryption             __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
#define kSCPropNetIPSecXAuthPasswordEncryption kSCPropNetIPSecXAuthPasswordEncryption

/*!
  @const kSCValNetIPSecAuthenticationMethodSharedSecret
 */
extern const CFStringRef kSCValNetIPSecAuthenticationMethodSharedSecret     __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCValNetIPSecAuthenticationMethodSharedSecret kSCValNetIPSecAuthenticationMethodSharedSecret

/*!
  @const kSCValNetIPSecAuthenticationMethodCertificate
 */
extern const CFStringRef kSCValNetIPSecAuthenticationMethodCertificate      __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCValNetIPSecAuthenticationMethodCertificate kSCValNetIPSecAuthenticationMethodCertificate

/*!
  @const kSCValNetIPSecAuthenticationMethodHybrid
 */
extern const CFStringRef kSCValNetIPSecAuthenticationMethodHybrid           __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCValNetIPSecAuthenticationMethodHybrid kSCValNetIPSecAuthenticationMethodHybrid

/*!
  @const kSCValNetIPSecLocalIdentifierTypeKeyID
 */
extern const CFStringRef kSCValNetIPSecLocalIdentifierTypeKeyID             __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCValNetIPSecLocalIdentifierTypeKeyID kSCValNetIPSecLocalIdentifierTypeKeyID

/*!
  @const kSCValNetIPSecSharedSecretEncryptionKeychain
 */
extern const CFStringRef kSCValNetIPSecSharedSecretEncryptionKeychain       __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCValNetIPSecSharedSecretEncryptionKeychain kSCValNetIPSecSharedSecretEncryptionKeychain

/*!
  @const kSCValNetIPSecXAuthPasswordEncryptionKeychain
 */
extern const CFStringRef kSCValNetIPSecXAuthPasswordEncryptionKeychain      __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
#define kSCValNetIPSecXAuthPasswordEncryptionKeychain kSCValNetIPSecXAuthPasswordEncryptionKeychain

/*!
  @const kSCValNetIPSecXAuthPasswordEncryptionPrompt
 */
extern const CFStringRef kSCValNetIPSecXAuthPasswordEncryptionPrompt        __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
#define kSCValNetIPSecXAuthPasswordEncryptionPrompt kSCValNetIPSecXAuthPasswordEncryptionPrompt

/*!
  @group kSCEntNetIPv4 Entity Keys
 */

/*!
  @const kSCPropNetIPv4Addresses
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetIPv4Addresses                            __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetIPv4Addresses kSCPropNetIPv4Addresses

/*!
  @const kSCPropNetIPv4ConfigMethod
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetIPv4ConfigMethod                         __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetIPv4ConfigMethod kSCPropNetIPv4ConfigMethod

/*!
  @const kSCPropNetIPv4DHCPClientID
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetIPv4DHCPClientID                         __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetIPv4DHCPClientID kSCPropNetIPv4DHCPClientID

/*!
  @const kSCPropNetIPv4Router
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetIPv4Router                               __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetIPv4Router kSCPropNetIPv4Router

/*!
  @const kSCPropNetIPv4SubnetMasks
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetIPv4SubnetMasks                          __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetIPv4SubnetMasks kSCPropNetIPv4SubnetMasks

/*!
  @const kSCPropNetIPv4DestAddresses
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetIPv4DestAddresses                        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetIPv4DestAddresses kSCPropNetIPv4DestAddresses

/*!
  @const kSCPropNetIPv4BroadcastAddresses
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetIPv4BroadcastAddresses                   __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetIPv4BroadcastAddresses kSCPropNetIPv4BroadcastAddresses

/*!
  @const kSCValNetIPv4ConfigMethodAutomatic
 */
extern const CFStringRef kSCValNetIPv4ConfigMethodAutomatic                 __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
#define kSCValNetIPv4ConfigMethodAutomatic kSCValNetIPv4ConfigMethodAutomatic

/*!
  @const kSCValNetIPv4ConfigMethodBOOTP
 */
extern const CFStringRef kSCValNetIPv4ConfigMethodBOOTP                     __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCValNetIPv4ConfigMethodBOOTP kSCValNetIPv4ConfigMethodBOOTP

/*!
  @const kSCValNetIPv4ConfigMethodDHCP
 */
extern const CFStringRef kSCValNetIPv4ConfigMethodDHCP                      __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCValNetIPv4ConfigMethodDHCP kSCValNetIPv4ConfigMethodDHCP

/*!
  @const kSCValNetIPv4ConfigMethodINFORM
 */
extern const CFStringRef kSCValNetIPv4ConfigMethodINFORM                    __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCValNetIPv4ConfigMethodINFORM kSCValNetIPv4ConfigMethodINFORM

/*!
  @const kSCValNetIPv4ConfigMethodLinkLocal
 */
extern const CFStringRef kSCValNetIPv4ConfigMethodLinkLocal                 __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCValNetIPv4ConfigMethodLinkLocal kSCValNetIPv4ConfigMethodLinkLocal

/*!
  @const kSCValNetIPv4ConfigMethodManual
 */
extern const CFStringRef kSCValNetIPv4ConfigMethodManual                    __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCValNetIPv4ConfigMethodManual kSCValNetIPv4ConfigMethodManual

/*!
  @const kSCValNetIPv4ConfigMethodPPP
 */
extern const CFStringRef kSCValNetIPv4ConfigMethodPPP                       __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCValNetIPv4ConfigMethodPPP kSCValNetIPv4ConfigMethodPPP

/*!
  @group kSCEntNetIPv6 Entity Keys
 */

/*!
  @const kSCPropNetIPv6Addresses
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetIPv6Addresses                            __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetIPv6Addresses kSCPropNetIPv6Addresses

/*!
  @const kSCPropNetIPv6ConfigMethod
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetIPv6ConfigMethod                         __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetIPv6ConfigMethod kSCPropNetIPv6ConfigMethod

/*!
  @const kSCPropNetIPv6DestAddresses
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetIPv6DestAddresses                        __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCPropNetIPv6DestAddresses kSCPropNetIPv6DestAddresses

/*!
  @const kSCPropNetIPv6Flags
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetIPv6Flags                                __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCPropNetIPv6Flags kSCPropNetIPv6Flags

/*!
  @const kSCPropNetIPv6PrefixLength
  @discussion Value is a CFArray[CFNumber]
 */
extern const CFStringRef kSCPropNetIPv6PrefixLength                         __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCPropNetIPv6PrefixLength kSCPropNetIPv6PrefixLength

/*!
  @const kSCPropNetIPv6Router
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetIPv6Router                               __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCPropNetIPv6Router kSCPropNetIPv6Router

/*!
  @const kSCValNetIPv6ConfigMethodAutomatic
 */
extern const CFStringRef kSCValNetIPv6ConfigMethodAutomatic                 __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCValNetIPv6ConfigMethodAutomatic kSCValNetIPv6ConfigMethodAutomatic

/*!
  @const kSCValNetIPv6ConfigMethodLinkLocal
 */
extern const CFStringRef kSCValNetIPv6ConfigMethodLinkLocal                 __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_NA);
#define kSCValNetIPv6ConfigMethodLinkLocal kSCValNetIPv6ConfigMethodLinkLocal

/*!
  @const kSCValNetIPv6ConfigMethodManual
 */
extern const CFStringRef kSCValNetIPv6ConfigMethodManual                    __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCValNetIPv6ConfigMethodManual kSCValNetIPv6ConfigMethodManual

/*!
  @const kSCValNetIPv6ConfigMethodRouterAdvertisement
 */
extern const CFStringRef kSCValNetIPv6ConfigMethodRouterAdvertisement       __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCValNetIPv6ConfigMethodRouterAdvertisement kSCValNetIPv6ConfigMethodRouterAdvertisement

/*!
  @const kSCValNetIPv6ConfigMethod6to4
 */
extern const CFStringRef kSCValNetIPv6ConfigMethod6to4                      __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCValNetIPv6ConfigMethod6to4 kSCValNetIPv6ConfigMethod6to4

/*!
  @group kSCEntNet6to4 Entity Keys
 */

/*!
  @const kSCPropNet6to4Relay
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNet6to4Relay                                __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCPropNet6to4Relay kSCPropNet6to4Relay

/*!
  @group kSCEntNetLink Entity Keys
 */

/*!
  @const kSCPropNetLinkActive
  @discussion Value is a CFBoolean
 */
extern const CFStringRef kSCPropNetLinkActive                               __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetLinkActive kSCPropNetLinkActive

/*!
  @const kSCPropNetLinkDetaching
  @discussion Value is a CFBoolean
 */
extern const CFStringRef kSCPropNetLinkDetaching                            __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetLinkDetaching kSCPropNetLinkDetaching

/*!
  @group kSCEntNetModem (Hardware) Entity Keys
 */

/*!
  @const kSCPropNetModemAccessPointName
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetModemAccessPointName                     __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCPropNetModemAccessPointName kSCPropNetModemAccessPointName

/*!
  @const kSCPropNetModemConnectionPersonality
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetModemConnectionPersonality               __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCPropNetModemConnectionPersonality kSCPropNetModemConnectionPersonality

/*!
  @const kSCPropNetModemConnectionScript
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetModemConnectionScript                    __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetModemConnectionScript kSCPropNetModemConnectionScript

/*!
  @const kSCPropNetModemConnectSpeed
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetModemConnectSpeed                        __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetModemConnectSpeed kSCPropNetModemConnectSpeed

/*!
  @const kSCPropNetModemDataCompression
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetModemDataCompression                     __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetModemDataCompression kSCPropNetModemDataCompression

/*!
  @const kSCPropNetModemDeviceContextID
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetModemDeviceContextID                     __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCPropNetModemDeviceContextID kSCPropNetModemDeviceContextID

/*!
  @const kSCPropNetModemDeviceModel
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetModemDeviceModel                         __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCPropNetModemDeviceModel kSCPropNetModemDeviceModel

/*!
  @const kSCPropNetModemDeviceVendor
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetModemDeviceVendor                        __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCPropNetModemDeviceVendor kSCPropNetModemDeviceVendor

/*!
  @const kSCPropNetModemDialMode
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetModemDialMode                            __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetModemDialMode kSCPropNetModemDialMode

/*!
  @const kSCPropNetModemErrorCorrection
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetModemErrorCorrection                     __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetModemErrorCorrection kSCPropNetModemErrorCorrection

/*!
  @const kSCPropNetModemHoldCallWaitingAudibleAlert
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetModemHoldCallWaitingAudibleAlert         __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetModemHoldCallWaitingAudibleAlert kSCPropNetModemHoldCallWaitingAudibleAlert

/*!
  @const kSCPropNetModemHoldDisconnectOnAnswer
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetModemHoldDisconnectOnAnswer              __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetModemHoldDisconnectOnAnswer kSCPropNetModemHoldDisconnectOnAnswer

/*!
  @const kSCPropNetModemHoldEnabled
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetModemHoldEnabled                         __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetModemHoldEnabled kSCPropNetModemHoldEnabled

/*!
  @const kSCPropNetModemHoldReminder
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetModemHoldReminder                        __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetModemHoldReminder kSCPropNetModemHoldReminder

/*!
  @const kSCPropNetModemHoldReminderTime
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetModemHoldReminderTime                    __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetModemHoldReminderTime kSCPropNetModemHoldReminderTime

/*!
  @const kSCPropNetModemNote
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetModemNote                                __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetModemNote kSCPropNetModemNote

/*!
  @const kSCPropNetModemPulseDial
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetModemPulseDial                           __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetModemPulseDial kSCPropNetModemPulseDial

/*!
  @const kSCPropNetModemSpeaker
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetModemSpeaker                             __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetModemSpeaker kSCPropNetModemSpeaker

/*!
  @const kSCPropNetModemSpeed
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetModemSpeed                               __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetModemSpeed kSCPropNetModemSpeed

/*!
  @const kSCValNetModemDialModeIgnoreDialTone
 */
extern const CFStringRef kSCValNetModemDialModeIgnoreDialTone               __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCValNetModemDialModeIgnoreDialTone kSCValNetModemDialModeIgnoreDialTone

/*!
  @const kSCValNetModemDialModeManual
 */
extern const CFStringRef kSCValNetModemDialModeManual                       __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCValNetModemDialModeManual kSCValNetModemDialModeManual

/*!
  @const kSCValNetModemDialModeWaitForDialTone
 */
extern const CFStringRef kSCValNetModemDialModeWaitForDialTone              __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCValNetModemDialModeWaitForDialTone kSCValNetModemDialModeWaitForDialTone

/*!
  @group kSCEntNetNetInfo Entity Keys
 */

/*!
  @const kSCPropNetNetInfoBindingMethods
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetNetInfoBindingMethods                    __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetNetInfoBindingMethods kSCPropNetNetInfoBindingMethods

/*!
  @const kSCPropNetNetInfoServerAddresses
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetNetInfoServerAddresses                   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetNetInfoServerAddresses kSCPropNetNetInfoServerAddresses

/*!
  @const kSCPropNetNetInfoServerTags
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetNetInfoServerTags                        __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetNetInfoServerTags kSCPropNetNetInfoServerTags

/*!
  @const kSCPropNetNetInfoBroadcastServerTag
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetNetInfoBroadcastServerTag                __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetNetInfoBroadcastServerTag kSCPropNetNetInfoBroadcastServerTag

/*!
  @const kSCValNetNetInfoBindingMethodsBroadcast
 */
extern const CFStringRef kSCValNetNetInfoBindingMethodsBroadcast            __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);
#define kSCValNetNetInfoBindingMethodsBroadcast kSCValNetNetInfoBindingMethodsBroadcast

/*!
  @const kSCValNetNetInfoBindingMethodsDHCP
 */
extern const CFStringRef kSCValNetNetInfoBindingMethodsDHCP                 __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);
#define kSCValNetNetInfoBindingMethodsDHCP kSCValNetNetInfoBindingMethodsDHCP

/*!
  @const kSCValNetNetInfoBindingMethodsManual
 */
extern const CFStringRef kSCValNetNetInfoBindingMethodsManual               __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);
#define kSCValNetNetInfoBindingMethodsManual kSCValNetNetInfoBindingMethodsManual

/*!
  @const kSCValNetNetInfoDefaultServerTag
 */
extern const CFStringRef kSCValNetNetInfoDefaultServerTag                   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_5,__IPHONE_NA,__IPHONE_NA);
#define kSCValNetNetInfoDefaultServerTag kSCValNetNetInfoDefaultServerTag

/*!
  @group kSCEntNetPPP Entity Keys
 */

/*!
  @const kSCPropNetPPPACSPEnabled
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPACSPEnabled                           __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCPropNetPPPACSPEnabled kSCPropNetPPPACSPEnabled

/*!
  @const kSCPropNetPPPConnectTime
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPConnectTime                           __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetPPPConnectTime kSCPropNetPPPConnectTime

/*!
  @const kSCPropNetPPPDeviceLastCause
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPDeviceLastCause                       __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetPPPDeviceLastCause kSCPropNetPPPDeviceLastCause

/*!
  @const kSCPropNetPPPDialOnDemand
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPDialOnDemand                          __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPDialOnDemand kSCPropNetPPPDialOnDemand

/*!
  @const kSCPropNetPPPDisconnectOnFastUserSwitch
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPDisconnectOnFastUserSwitch            __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);
#define kSCPropNetPPPDisconnectOnFastUserSwitch kSCPropNetPPPDisconnectOnFastUserSwitch

/*!
  @const kSCPropNetPPPDisconnectOnIdle
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPDisconnectOnIdle                      __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPDisconnectOnIdle kSCPropNetPPPDisconnectOnIdle

/*!
  @const kSCPropNetPPPDisconnectOnIdleTimer
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPDisconnectOnIdleTimer                 __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPDisconnectOnIdleTimer kSCPropNetPPPDisconnectOnIdleTimer

/*!
  @const kSCPropNetPPPDisconnectOnLogout
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPDisconnectOnLogout                    __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPDisconnectOnLogout kSCPropNetPPPDisconnectOnLogout

/*!
  @const kSCPropNetPPPDisconnectOnSleep
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPDisconnectOnSleep                     __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetPPPDisconnectOnSleep kSCPropNetPPPDisconnectOnSleep

/*!
  @const kSCPropNetPPPDisconnectTime
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPDisconnectTime                        __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCPropNetPPPDisconnectTime kSCPropNetPPPDisconnectTime

/*!
  @const kSCPropNetPPPIdleReminderTimer
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPIdleReminderTimer                     __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPIdleReminderTimer kSCPropNetPPPIdleReminderTimer

/*!
  @const kSCPropNetPPPIdleReminder
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPIdleReminder                          __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPIdleReminder kSCPropNetPPPIdleReminder

/*!
  @const kSCPropNetPPPLastCause
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPLastCause                             __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetPPPLastCause kSCPropNetPPPLastCause

/*!
  @const kSCPropNetPPPLogfile
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetPPPLogfile                               __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPLogfile kSCPropNetPPPLogfile

/*!
  @const kSCPropNetPPPPlugins
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetPPPPlugins                               __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetPPPPlugins kSCPropNetPPPPlugins

/*!
  @const kSCPropNetPPPRetryConnectTime
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPRetryConnectTime                      __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCPropNetPPPRetryConnectTime kSCPropNetPPPRetryConnectTime

/*!
  @const kSCPropNetPPPSessionTimer
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPSessionTimer                          __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPSessionTimer kSCPropNetPPPSessionTimer

/*!
  @const kSCPropNetPPPStatus
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPStatus                                __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetPPPStatus kSCPropNetPPPStatus

/*!
  @const kSCPropNetPPPUseSessionTimer
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPUseSessionTimer                       __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetPPPUseSessionTimer kSCPropNetPPPUseSessionTimer

/*!
  @const kSCPropNetPPPVerboseLogging
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPVerboseLogging                        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPVerboseLogging kSCPropNetPPPVerboseLogging

/*!
  @const kSCPropNetPPPAuthEAPPlugins
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetPPPAuthEAPPlugins                        __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCPropNetPPPAuthEAPPlugins kSCPropNetPPPAuthEAPPlugins

/*!
  @const kSCPropNetPPPAuthName
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetPPPAuthName                              __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPAuthName kSCPropNetPPPAuthName

/*!
  @const kSCPropNetPPPAuthPassword
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetPPPAuthPassword                          __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPAuthPassword kSCPropNetPPPAuthPassword

/*!
  @const kSCPropNetPPPAuthPasswordEncryption
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetPPPAuthPasswordEncryption                __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPAuthPasswordEncryption kSCPropNetPPPAuthPasswordEncryption

/*!
  @const kSCPropNetPPPAuthPrompt
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetPPPAuthPrompt                            __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCPropNetPPPAuthPrompt kSCPropNetPPPAuthPrompt

/*!
  @const kSCPropNetPPPAuthProtocol
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetPPPAuthProtocol                          __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPAuthProtocol kSCPropNetPPPAuthProtocol

/*!
  @const kSCValNetPPPAuthPasswordEncryptionKeychain
 */
extern const CFStringRef kSCValNetPPPAuthPasswordEncryptionKeychain         __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCValNetPPPAuthPasswordEncryptionKeychain kSCValNetPPPAuthPasswordEncryptionKeychain

/*!
  @const kSCValNetPPPAuthPasswordEncryptionToken
 */
extern const CFStringRef kSCValNetPPPAuthPasswordEncryptionToken            __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCValNetPPPAuthPasswordEncryptionToken kSCValNetPPPAuthPasswordEncryptionToken

/*!
  @const kSCValNetPPPAuthPromptBefore
  @discussion Value is a CFString
 */
extern const CFStringRef kSCValNetPPPAuthPromptBefore                       __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCValNetPPPAuthPromptBefore kSCValNetPPPAuthPromptBefore

/*!
  @const kSCValNetPPPAuthPromptAfter
  @discussion Value is a CFString
 */
extern const CFStringRef kSCValNetPPPAuthPromptAfter                        __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCValNetPPPAuthPromptAfter kSCValNetPPPAuthPromptAfter

/*!
  @const kSCValNetPPPAuthProtocolCHAP
  @discussion Value is a CFString
 */
extern const CFStringRef kSCValNetPPPAuthProtocolCHAP                       __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCValNetPPPAuthProtocolCHAP kSCValNetPPPAuthProtocolCHAP

/*!
  @const kSCValNetPPPAuthProtocolEAP
  @discussion Value is a CFString
 */
extern const CFStringRef kSCValNetPPPAuthProtocolEAP                        __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCValNetPPPAuthProtocolEAP kSCValNetPPPAuthProtocolEAP

/*!
  @const kSCValNetPPPAuthProtocolMSCHAP1
  @discussion Value is a CFString
 */
extern const CFStringRef kSCValNetPPPAuthProtocolMSCHAP1                    __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCValNetPPPAuthProtocolMSCHAP1 kSCValNetPPPAuthProtocolMSCHAP1

/*!
  @const kSCValNetPPPAuthProtocolMSCHAP2
  @discussion Value is a CFString
 */
extern const CFStringRef kSCValNetPPPAuthProtocolMSCHAP2                    __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCValNetPPPAuthProtocolMSCHAP2 kSCValNetPPPAuthProtocolMSCHAP2

/*!
  @const kSCValNetPPPAuthProtocolPAP
  @discussion Value is a CFString
 */
extern const CFStringRef kSCValNetPPPAuthProtocolPAP                        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCValNetPPPAuthProtocolPAP kSCValNetPPPAuthProtocolPAP

/*!
  @const kSCPropNetPPPCommAlternateRemoteAddress
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetPPPCommAlternateRemoteAddress            __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPCommAlternateRemoteAddress kSCPropNetPPPCommAlternateRemoteAddress

/*!
  @const kSCPropNetPPPCommConnectDelay
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPCommConnectDelay                      __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPCommConnectDelay kSCPropNetPPPCommConnectDelay

/*!
  @const kSCPropNetPPPCommDisplayTerminalWindow
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPCommDisplayTerminalWindow             __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPCommDisplayTerminalWindow kSCPropNetPPPCommDisplayTerminalWindow

/*!
  @const kSCPropNetPPPCommRedialCount
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPCommRedialCount                       __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPCommRedialCount kSCPropNetPPPCommRedialCount

/*!
  @const kSCPropNetPPPCommRedialEnabled
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPCommRedialEnabled                     __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPCommRedialEnabled kSCPropNetPPPCommRedialEnabled

/*!
  @const kSCPropNetPPPCommRedialInterval
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPCommRedialInterval                    __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPCommRedialInterval kSCPropNetPPPCommRedialInterval

/*!
  @const kSCPropNetPPPCommRemoteAddress
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetPPPCommRemoteAddress                     __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPCommRemoteAddress kSCPropNetPPPCommRemoteAddress

/*!
  @const kSCPropNetPPPCommTerminalScript
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetPPPCommTerminalScript                    __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPCommTerminalScript kSCPropNetPPPCommTerminalScript

/*!
  @const kSCPropNetPPPCommUseTerminalScript
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPCommUseTerminalScript                 __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetPPPCommUseTerminalScript kSCPropNetPPPCommUseTerminalScript

/*!
  @const kSCPropNetPPPCCPEnabled
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPCCPEnabled                            __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);
#define kSCPropNetPPPCCPEnabled kSCPropNetPPPCCPEnabled

/*!
  @const kSCPropNetPPPCCPMPPE40Enabled
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPCCPMPPE40Enabled                      __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);
#define kSCPropNetPPPCCPMPPE40Enabled kSCPropNetPPPCCPMPPE40Enabled

/*!
  @const kSCPropNetPPPCCPMPPE128Enabled
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPCCPMPPE128Enabled                     __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);
#define kSCPropNetPPPCCPMPPE128Enabled kSCPropNetPPPCCPMPPE128Enabled

/*!
  @const kSCPropNetPPPIPCPCompressionVJ
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPIPCPCompressionVJ                     __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPIPCPCompressionVJ kSCPropNetPPPIPCPCompressionVJ

/*!
  @const kSCPropNetPPPIPCPUsePeerDNS
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPIPCPUsePeerDNS                        __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);
#define kSCPropNetPPPIPCPUsePeerDNS kSCPropNetPPPIPCPUsePeerDNS

/*!
  @const kSCPropNetPPPLCPEchoEnabled
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPLCPEchoEnabled                        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPLCPEchoEnabled kSCPropNetPPPLCPEchoEnabled

/*!
  @const kSCPropNetPPPLCPEchoFailure
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPLCPEchoFailure                        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPLCPEchoFailure kSCPropNetPPPLCPEchoFailure

/*!
  @const kSCPropNetPPPLCPEchoInterval
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPLCPEchoInterval                       __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPLCPEchoInterval kSCPropNetPPPLCPEchoInterval

/*!
  @const kSCPropNetPPPLCPCompressionACField
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPLCPCompressionACField                 __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPLCPCompressionACField kSCPropNetPPPLCPCompressionACField

/*!
  @const kSCPropNetPPPLCPCompressionPField
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetPPPLCPCompressionPField                  __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPLCPCompressionPField kSCPropNetPPPLCPCompressionPField

/*!
  @const kSCPropNetPPPLCPMRU
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPLCPMRU                                __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPLCPMRU kSCPropNetPPPLCPMRU

/*!
  @const kSCPropNetPPPLCPMTU
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPLCPMTU                                __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPLCPMTU kSCPropNetPPPLCPMTU

/*!
  @const kSCPropNetPPPLCPReceiveACCM
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPLCPReceiveACCM                        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPLCPReceiveACCM kSCPropNetPPPLCPReceiveACCM

/*!
  @const kSCPropNetPPPLCPTransmitACCM
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetPPPLCPTransmitACCM                       __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetPPPLCPTransmitACCM kSCPropNetPPPLCPTransmitACCM

/*!
  @group kSCEntNetPPPoE Entity Keys
 */

/*!
  @group kSCEntNetPPPSerial Entity Keys
 */

/*!
  @group kSCEntNetPPTP Entity Keys
 */

/*!
  @group kSCEntNetL2TP Entity Keys
 */

/*!
  @const kSCPropNetL2TPIPSecSharedSecret
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetL2TPIPSecSharedSecret                    __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCPropNetL2TPIPSecSharedSecret kSCPropNetL2TPIPSecSharedSecret

/*!
  @const kSCPropNetL2TPIPSecSharedSecretEncryption
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetL2TPIPSecSharedSecretEncryption          __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCPropNetL2TPIPSecSharedSecretEncryption kSCPropNetL2TPIPSecSharedSecretEncryption

/*!
  @const kSCPropNetL2TPTransport
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetL2TPTransport                            __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCPropNetL2TPTransport kSCPropNetL2TPTransport

/*!
  @const kSCValNetL2TPIPSecSharedSecretEncryptionKeychain
 */
extern const CFStringRef kSCValNetL2TPIPSecSharedSecretEncryptionKeychain   __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCValNetL2TPIPSecSharedSecretEncryptionKeychain kSCValNetL2TPIPSecSharedSecretEncryptionKeychain

/*!
  @const kSCValNetL2TPTransportIP
 */
extern const CFStringRef kSCValNetL2TPTransportIP                           __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCValNetL2TPTransportIP kSCValNetL2TPTransportIP

/*!
  @const kSCValNetL2TPTransportIPSec
 */
extern const CFStringRef kSCValNetL2TPTransportIPSec                        __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_NA);
#define kSCValNetL2TPTransportIPSec kSCValNetL2TPTransportIPSec

/*!
  @group kSCEntNetProxies Entity Keys
 */

/*!
  @const kSCPropNetProxiesExceptionsList
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetProxiesExceptionsList                    __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesExceptionsList kSCPropNetProxiesExceptionsList

/*!
  @const kSCPropNetProxiesExcludeSimpleHostnames
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetProxiesExcludeSimpleHostnames            __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);
#define kSCPropNetProxiesExcludeSimpleHostnames kSCPropNetProxiesExcludeSimpleHostnames

/*!
  @const kSCPropNetProxiesFTPEnable
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetProxiesFTPEnable                         __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesFTPEnable kSCPropNetProxiesFTPEnable

/*!
  @const kSCPropNetProxiesFTPPassive
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetProxiesFTPPassive                        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesFTPPassive kSCPropNetProxiesFTPPassive

/*!
  @const kSCPropNetProxiesFTPPort
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetProxiesFTPPort                           __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesFTPPort kSCPropNetProxiesFTPPort

/*!
  @const kSCPropNetProxiesFTPProxy
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetProxiesFTPProxy                          __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesFTPProxy kSCPropNetProxiesFTPProxy

/*!
  @const kSCPropNetProxiesGopherEnable
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetProxiesGopherEnable                      __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesGopherEnable kSCPropNetProxiesGopherEnable

/*!
  @const kSCPropNetProxiesGopherPort
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetProxiesGopherPort                        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesGopherPort kSCPropNetProxiesGopherPort

/*!
  @const kSCPropNetProxiesGopherProxy
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetProxiesGopherProxy                       __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesGopherProxy kSCPropNetProxiesGopherProxy

/*!
  @const kSCPropNetProxiesHTTPEnable
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetProxiesHTTPEnable                        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesHTTPEnable kSCPropNetProxiesHTTPEnable

/*!
  @const kSCPropNetProxiesHTTPPort
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetProxiesHTTPPort                          __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesHTTPPort kSCPropNetProxiesHTTPPort

/*!
  @const kSCPropNetProxiesHTTPProxy
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetProxiesHTTPProxy                         __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesHTTPProxy kSCPropNetProxiesHTTPProxy

/*!
  @const kSCPropNetProxiesHTTPSEnable
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetProxiesHTTPSEnable                       __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesHTTPSEnable kSCPropNetProxiesHTTPSEnable

/*!
  @const kSCPropNetProxiesHTTPSPort
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetProxiesHTTPSPort                         __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesHTTPSPort kSCPropNetProxiesHTTPSPort

/*!
  @const kSCPropNetProxiesHTTPSProxy
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetProxiesHTTPSProxy                        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesHTTPSProxy kSCPropNetProxiesHTTPSProxy

/*!
  @const kSCPropNetProxiesRTSPEnable
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetProxiesRTSPEnable                        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesRTSPEnable kSCPropNetProxiesRTSPEnable

/*!
  @const kSCPropNetProxiesRTSPPort
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetProxiesRTSPPort                          __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesRTSPPort kSCPropNetProxiesRTSPPort

/*!
  @const kSCPropNetProxiesRTSPProxy
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetProxiesRTSPProxy                         __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesRTSPProxy kSCPropNetProxiesRTSPProxy

/*!
  @const kSCPropNetProxiesSOCKSEnable
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetProxiesSOCKSEnable                       __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesSOCKSEnable kSCPropNetProxiesSOCKSEnable

/*!
  @const kSCPropNetProxiesSOCKSPort
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropNetProxiesSOCKSPort                         __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesSOCKSPort kSCPropNetProxiesSOCKSPort

/*!
  @const kSCPropNetProxiesSOCKSProxy
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetProxiesSOCKSProxy                        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropNetProxiesSOCKSProxy kSCPropNetProxiesSOCKSProxy

/*!
  @const kSCPropNetProxiesProxyAutoConfigEnable
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetProxiesProxyAutoConfigEnable             __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);
#define kSCPropNetProxiesProxyAutoConfigEnable kSCPropNetProxiesProxyAutoConfigEnable

/*!
  @const kSCPropNetProxiesProxyAutoConfigJavaScript
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetProxiesProxyAutoConfigJavaScript         __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_NA);
#define kSCPropNetProxiesProxyAutoConfigJavaScript kSCPropNetProxiesProxyAutoConfigJavaScript

/*!
  @const kSCPropNetProxiesProxyAutoConfigURLString
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetProxiesProxyAutoConfigURLString          __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);
#define kSCPropNetProxiesProxyAutoConfigURLString kSCPropNetProxiesProxyAutoConfigURLString

/*!
  @const kSCPropNetProxiesProxyAutoDiscoveryEnable
  @discussion Value is a CFNumber (0 or 1)
 */
extern const CFStringRef kSCPropNetProxiesProxyAutoDiscoveryEnable          __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_NA);
#define kSCPropNetProxiesProxyAutoDiscoveryEnable kSCPropNetProxiesProxyAutoDiscoveryEnable

/*!
  @group kSCEntNetSMB Entity Keys
 */

/*!
  @const kSCPropNetSMBNetBIOSName
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetSMBNetBIOSName                           __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCPropNetSMBNetBIOSName kSCPropNetSMBNetBIOSName

/*!
  @const kSCPropNetSMBNetBIOSNodeType
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetSMBNetBIOSNodeType                       __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCPropNetSMBNetBIOSNodeType kSCPropNetSMBNetBIOSNodeType

/*!
  @const kSCPropNetSMBNetBIOSScope
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetSMBNetBIOSScope                          __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5,__MAC_10_7,__IPHONE_NA,__IPHONE_NA);
#define kSCPropNetSMBNetBIOSScope kSCPropNetSMBNetBIOSScope

/*!
  @const kSCPropNetSMBWINSAddresses
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCPropNetSMBWINSAddresses                         __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCPropNetSMBWINSAddresses kSCPropNetSMBWINSAddresses

/*!
  @const kSCPropNetSMBWorkgroup
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropNetSMBWorkgroup                             __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCPropNetSMBWorkgroup kSCPropNetSMBWorkgroup

/*!
  @const kSCValNetSMBNetBIOSNodeTypeBroadcast
 */
extern const CFStringRef kSCValNetSMBNetBIOSNodeTypeBroadcast               __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCValNetSMBNetBIOSNodeTypeBroadcast kSCValNetSMBNetBIOSNodeTypeBroadcast

/*!
  @const kSCValNetSMBNetBIOSNodeTypePeer
 */
extern const CFStringRef kSCValNetSMBNetBIOSNodeTypePeer                    __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCValNetSMBNetBIOSNodeTypePeer kSCValNetSMBNetBIOSNodeTypePeer

/*!
  @const kSCValNetSMBNetBIOSNodeTypeMixed
 */
extern const CFStringRef kSCValNetSMBNetBIOSNodeTypeMixed                   __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCValNetSMBNetBIOSNodeTypeMixed kSCValNetSMBNetBIOSNodeTypeMixed

/*!
  @const kSCValNetSMBNetBIOSNodeTypeHybrid
 */
extern const CFStringRef kSCValNetSMBNetBIOSNodeTypeHybrid                  __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#define kSCValNetSMBNetBIOSNodeTypeHybrid kSCValNetSMBNetBIOSNodeTypeHybrid

/*!
  @group kSCCompUsers Entity Keys
 */

/*!
  @const kSCEntUsersConsoleUser
 */
extern const CFStringRef kSCEntUsersConsoleUser                             __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCEntUsersConsoleUser kSCEntUsersConsoleUser

/*!
  @group kSCCompSystem Properties
 */

/*!
  @const kSCPropSystemComputerName
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropSystemComputerName                          __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropSystemComputerName kSCPropSystemComputerName

/*!
  @const kSCPropSystemComputerNameEncoding
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropSystemComputerNameEncoding                  __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCPropSystemComputerNameEncoding kSCPropSystemComputerNameEncoding

/*!
  @group SCDynamicStore "domain" prefixes
 */

/*!
  @const kSCDynamicStoreDomainFile
 */
extern const CFStringRef kSCDynamicStoreDomainFile                          __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCDynamicStoreDomainFile kSCDynamicStoreDomainFile

/*!
  @const kSCDynamicStoreDomainPlugin
 */
extern const CFStringRef kSCDynamicStoreDomainPlugin                        __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCDynamicStoreDomainPlugin kSCDynamicStoreDomainPlugin

/*!
  @const kSCDynamicStoreDomainSetup
 */
extern const CFStringRef kSCDynamicStoreDomainSetup                         __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCDynamicStoreDomainSetup kSCDynamicStoreDomainSetup

/*!
  @const kSCDynamicStoreDomainState
 */
extern const CFStringRef kSCDynamicStoreDomainState                         __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCDynamicStoreDomainState kSCDynamicStoreDomainState

/*!
  @const kSCDynamicStoreDomainPrefs
 */
extern const CFStringRef kSCDynamicStoreDomainPrefs                         __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCDynamicStoreDomainPrefs kSCDynamicStoreDomainPrefs

/*!
  @group Preference ("location") Keys
 */

/*!
  @const kSCDynamicStorePropSetupCurrentSet
  @discussion Value is a CFString
 */
extern const CFStringRef kSCDynamicStorePropSetupCurrentSet                 __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCDynamicStorePropSetupCurrentSet kSCDynamicStorePropSetupCurrentSet

/*!
  @const kSCDynamicStorePropSetupLastUpdated
 */
extern const CFStringRef kSCDynamicStorePropSetupLastUpdated                __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCDynamicStorePropSetupLastUpdated kSCDynamicStorePropSetupLastUpdated

/*!
  @group Common/shared Keys
 */

/*!
  @const kSCDynamicStorePropNetInterfaces
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCDynamicStorePropNetInterfaces                   __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCDynamicStorePropNetInterfaces kSCDynamicStorePropNetInterfaces

/*!
  @const kSCDynamicStorePropNetPrimaryInterface
  @discussion Value is a CFString
 */
extern const CFStringRef kSCDynamicStorePropNetPrimaryInterface             __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCDynamicStorePropNetPrimaryInterface kSCDynamicStorePropNetPrimaryInterface

/*!
  @const kSCDynamicStorePropNetPrimaryService
  @discussion Value is a CFString
 */
extern const CFStringRef kSCDynamicStorePropNetPrimaryService               __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCDynamicStorePropNetPrimaryService kSCDynamicStorePropNetPrimaryService

/*!
  @const kSCDynamicStorePropNetServiceIDs
  @discussion Value is a CFArray[CFString]
 */
extern const CFStringRef kSCDynamicStorePropNetServiceIDs                   __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);
#define kSCDynamicStorePropNetServiceIDs kSCDynamicStorePropNetServiceIDs

/*!
  @const kSCPropUsersConsoleUserName
  @discussion Value is a CFString
 */
extern const CFStringRef kSCPropUsersConsoleUserName                        __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_4,__IPHONE_NA,__IPHONE_NA);
#define kSCPropUsersConsoleUserName kSCPropUsersConsoleUserName

/*!
  @const kSCPropUsersConsoleUserUID
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropUsersConsoleUserUID                         __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_4,__IPHONE_NA,__IPHONE_NA);
#define kSCPropUsersConsoleUserUID kSCPropUsersConsoleUserUID

/*!
  @const kSCPropUsersConsoleUserGID
  @discussion Value is a CFNumber
 */
extern const CFStringRef kSCPropUsersConsoleUserGID                         __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_4,__IPHONE_NA,__IPHONE_NA);
#define kSCPropUsersConsoleUserGID kSCPropUsersConsoleUserGID

CF_ASSUME_NONNULL_END

#endif	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#endif	/* _SCSCHEMADEFINITIONS_H */
// ==========  SystemConfiguration.framework/Headers/SCDynamicStoreCopySpecific.h
/*
 * Copyright (c) 2000-2005, 2008, 2015 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _SCDYNAMICSTORECOPYSPECIFIC_H
#ifdef	USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS
#include <SystemConfiguration/_SCDynamicStoreCopySpecific.h>
#else	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#define _SCDYNAMICSTORECOPYSPECIFIC_H

#include <Availability.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <CoreFoundation/CoreFoundation.h>
#include <SystemConfiguration/SCDynamicStore.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_ASSUME_NONNULL_BEGIN

/*!
	@header SCDynamicStoreCopySpecific
	@discussion The functions of the SCDynamicStoreCopySpecific API
		allow an application to determine specific configuration
		information about the current system (for example, the
		computer or sharing name, the currently logged-in user, etc.).
 */


__BEGIN_DECLS

/*!
	@function SCDynamicStoreCopyComputerName
	@discussion Gets the current computer name.
	@param store An SCDynamicStoreRef representing the dynamic store
		session that should be used for communication with the server.
		If NULL, a temporary session will be used.
	@param nameEncoding A pointer to memory that, if non-NULL, will be
		filled with the encoding associated with the computer or
		host name.
	@result Returns the current computer name;
		NULL if the name has not been set or if an error was encountered.
		You must release the returned value.
 */
CFStringRef __nullable
SCDynamicStoreCopyComputerName		(
					SCDynamicStoreRef	__nullable	store,
					CFStringEncoding	* __nullable	nameEncoding
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreCopyConsoleUser
	@discussion Gets the name, user ID, and group ID of the currently
		logged-in user.

		Note: this function only provides information about the
		      primary console.  It does not provide any details
		      about console sessions that have fast user switched
		      out or about other consoles.
	@param store An SCDynamicStoreRef representing the dynamic store
		session that should be used for communication with the server.
		If NULL, a temporary session will be used.
	@param uid A pointer to memory that will be filled with the user ID
		of the current console user. If NULL, this value will not
		be returned.
	@param gid A pointer to memory that will be filled with the group ID
		of the current console user. If NULL, this value will not be
		returned.
	@result Returns the user currently logged into the system;
		NULL if no user is logged in or if an error was encountered.
		You must release the returned value.
 */
CFStringRef __nullable
SCDynamicStoreCopyConsoleUser		(
					SCDynamicStoreRef	__nullable	store,
					uid_t			* __nullable	uid,
					gid_t			* __nullable	gid
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreCopyLocalHostName
	@discussion Gets the current local host name.
	@param store An SCDynamicStoreRef representing the dynamic store
		session that should be used for communication with the server.
		If NULL, a temporary session will be used.
	@result Returns the current local host name;
		NULL if the name has not been set or if an error was encountered.
		You must release the returned value.
 */
CFStringRef __nullable
SCDynamicStoreCopyLocalHostName		(
					SCDynamicStoreRef	__nullable	store
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreCopyLocation
	@discussion Gets the current location identifier.
	@param store An SCDynamicStoreRef representing the dynamic store
		session that should be used for communication with the server.
		If NULL, a temporary session will be used.
	@result Returns a string representing the current location identifier;
		NULL if no location identifier has been defined or if an error
		was encountered.
		You must release the returned value.
 */
CFStringRef __nullable
SCDynamicStoreCopyLocation		(
					SCDynamicStoreRef	__nullable	store
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreCopyProxies
	@discussion Gets the current internet proxy settings.
		The returned proxy settings dictionary includes:

		<TABLE BORDER>
		<TR>
			<TH>key</TD>
			<TH>type</TD>
			<TH>description</TD>
		</TR>
		<TR>
			<TD>kSCPropNetProxiesExceptionsList</TD>
			<TD>CFArray[CFString]</TD>
			<TD>Host name patterns which should bypass the proxy</TD>
		</TR>
		<TR>
			<TD>kSCPropNetProxiesHTTPEnable</TD>
			<TD>CFNumber (0 or 1)</TD>
			<TD>Enables/disables the use of an HTTP proxy</TD>
		</TR>
		<TR>
			<TD>kSCPropNetProxiesHTTPProxy</TD>
			<TD>CFString</TD>
			<TD>The proxy host</TD>
		</TR>
		<TR>
			<TD>kSCPropNetProxiesHTTPPort</TD>
			<TD>CFNumber</TD>
			<TD>The proxy port number</TD>
		</TR>
		<TR>
			<TD>kSCPropNetProxiesHTTPSEnable</TD>
			<TD>CFNumber (0 or 1)</TD>
			<TD>Enables/disables the use of an HTTPS proxy</TD>
		</TR>
		<TR>
			<TD>kSCPropNetProxiesHTTPSProxy</TD>
			<TD>CFString</TD>
			<TD>The proxy host</TD>
		</TR>
		<TR>
			<TD>kSCPropNetProxiesHTTPSPort</TD>
			<TD>CFNumber</TD>
			<TD>The proxy port number</TD>
		</TR>
		<TR>
			<TD>kSCPropNetProxiesFTPEnable</TD>
			<TD>CFNumber (0 or 1)</TD>
			<TD>Enables/disables the use of an FTP proxy</TD>
		</TR>
		<TR>
			<TD>kSCPropNetProxiesFTPProxy</TD>
			<TD>CFString</TD>
			<TD>The proxy host</TD>
		</TR>
		<TR>
			<TD>kSCPropNetProxiesFTPPort</TD>
			<TD>CFNumber</TD>
			<TD>The proxy port number</TD>
		</TR>
		<TR>
			<TD>kSCPropNetProxiesFTPPassive</TD>
			<TD>CFNumber (0 or 1)</TD>
			<TD>Enable passive mode operation for use behind connection
			filter-ing firewalls.</TD>
		</TR>
		</TABLE>

		Other key-value pairs are defined in the SCSchemaDefinitions.h
		header file.
	@param store An SCDynamicStoreRef representing the dynamic store
		session that should be used for communication with the server.
		If NULL, a temporary session will be used.
	@result Returns a dictionary containing key-value pairs that represent
		the current internet proxy settings;
		NULL if no proxy settings have been defined or if an error
		was encountered.
		You must release the returned value.
 */
CFDictionaryRef __nullable
SCDynamicStoreCopyProxies		(
					SCDynamicStoreRef	__nullable	store
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

__END_DECLS

CF_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#endif	/* _SCDYNAMICSTORECOPYSPECIFIC_H */
// ==========  SystemConfiguration.framework/Headers/SCDynamicStoreKey.h
/*
 * Copyright (c) 2000-2002, 2004, 2005, 2008, 2015 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _SCDYNAMICSTOREKEY_H
#ifdef	USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS
#include <SystemConfiguration/_SCDynamicStoreKey.h>
#else	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#define _SCDYNAMICSTOREKEY_H

#include <Availability.h>
#include <sys/cdefs.h>
#include <CoreFoundation/CoreFoundation.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_ASSUME_NONNULL_BEGIN

/*!
	@header SCDynamicStoreKey
	@discussion The SCDynamicStoreKey API provides convenience functions
		that an application can use to create a correctly formatted
		dynamic store key for accessing specific items in the dynamic
		store.  An application can then use the resulting string in
		any function that requires a dynamic store key.
 */


__BEGIN_DECLS

/*
 * SCDynamicStoreKeyCreate
 * - convenience routines that create a CFString key for an item in the store
 */

/*!
	@function SCDynamicStoreKeyCreate
	@discussion Creates a dynamic store key using the given format.
	@param allocator The CFAllocator that should be used to allocate
		memory for this key.
		This parameter may be NULL in which case the current
		default CFAllocator is used. If this reference is not
		a valid CFAllocator, the behavior is undefined.
	@param fmt A CFStringRef describing the format for this key.
	@result Returns a string containing the formatted key.
 */
CFStringRef
SCDynamicStoreKeyCreate				(
						CFAllocatorRef	__nullable	allocator,
						CFStringRef			fmt,
						...
						)		__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreKeyCreateNetworkGlobalEntity
	@discussion Creates a dynamic store key that can be used to access
		a specific global (as opposed to a per-service or per-interface)
		network configuration entity.
	@param allocator The CFAllocator that should be used to allocate
		memory for this key.
		This parameter may be NULL in which case the current
		default CFAllocator is used. If this reference is not
		a valid CFAllocator, the behavior is undefined.
	@param domain A string specifying the desired domain, such as the
		requested configuration (kSCDynamicStoreDomainSetup) or the
		actual state (kSCDynamicStoreDomainState).
	@param entity A string containing the specific global entity, such
		as IPv4 (kSCEntNetIPv4) or DNS (kSCEntNetDNS).
	@result Returns a string containing the formatted key.

 */
CFStringRef
SCDynamicStoreKeyCreateNetworkGlobalEntity	(
						CFAllocatorRef	__nullable	allocator,
						CFStringRef			domain,
						CFStringRef			entity
						)		__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreKeyCreateNetworkInterface
	@discussion Creates a dynamic store key that can be used to access
		the network interface configuration information stored in
		the dynamic store.
	@param allocator The CFAllocator that should be used to allocate
		memory for this key.
		This parameter may be NULL in which case the current
		default CFAllocator is used. If this reference is not
		a valid CFAllocator, the behavior is undefined.
	@param domain A string specifying the desired domain, such as the
		requested configuration (kSCDynamicStoreDomainSetup) or the
		actual state (kSCDynamicStoreDomainState).
	@result Returns a string containing the formatted key.

 */
CFStringRef
SCDynamicStoreKeyCreateNetworkInterface		(
						CFAllocatorRef	__nullable	allocator,
						CFStringRef			domain
						)		__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreKeyCreateNetworkInterfaceEntity
	@discussion Creates a dynamic store key that can be used to access
		the per-interface network configuration information stored in
		the dynamic store.
	@param allocator The CFAllocator that should be used to allocate
		memory for this key.
		This parameter may be NULL in which case the current
		default CFAllocator is used. If this reference is not
		a valid CFAllocator, the behavior is undefined.
	@param domain A string specifying the desired domain, such as the
		requested configuration (kSCDynamicStoreDomainSetup) or the
		actual state (kSCDynamicStoreDomainState).
	@param ifname A string containing the interface name or a regular
		expression pattern.
	@param entity A string containing the specific global entity, such
		as IPv4 (kSCEntNetIPv4) or DNS (kSCEntNetDNS).
	@result Returns a string containing the formatted key.

 */
CFStringRef
SCDynamicStoreKeyCreateNetworkInterfaceEntity	(
						CFAllocatorRef	__nullable	allocator,
						CFStringRef			domain,
						CFStringRef			ifname,
						CFStringRef	__nullable	entity
						)		__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreKeyCreateNetworkServiceEntity
	@discussion Creates a dynamic store key that can be used to access
		the per-service network configuration information stored in
		the dynamic store.
	@param allocator The CFAllocator that should be used to allocate
		memory for this key.
		This parameter may be NULL in which case the current
		default CFAllocator is used. If this reference is not
		a valid CFAllocator, the behavior is undefined.
	@param domain A string specifying the desired domain, such as the
		requested configuration (kSCDynamicStoreDomainSetup) or the
		actual state (kSCDynamicStoreDomainState).
	@param serviceID A string containing the service ID or a regular
		expression pattern.
	@param entity A string containing the specific global entity, such
		as IPv4 (kSCEntNetIPv4) or DNS (kSCEntNetDNS).
	@result Returns a string containing the formatted key.


 */
CFStringRef
SCDynamicStoreKeyCreateNetworkServiceEntity	(
						CFAllocatorRef	__nullable	allocator,
						CFStringRef			domain,
						CFStringRef			serviceID,
						CFStringRef	__nullable	entity
						)		__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreKeyCreateComputerName
	@discussion Creates a key that can be used in conjuntion with
		SCDynamicStoreSetNotificationKeys function to receive
		notifications when the current computer name changes.
	@param allocator The CFAllocator that should be used to allocate
		memory for this key.
		This parameter may be NULL in which case the current
		default CFAllocator is used. If this reference is not
		a valid CFAllocator, the behavior is undefined.
	@result Returns a notification string for the current computer or
		host name.
*/
CFStringRef
SCDynamicStoreKeyCreateComputerName		(
						CFAllocatorRef	__nullable	allocator
						)		__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreKeyCreateConsoleUser
	@discussion Creates a key that can be used in conjunction with
		SCDynamicStoreSetNotificationKeys function to receive
		notifications when the current console user changes.
	@param allocator The CFAllocator that should be used to allocate
		memory for this key.
		This parameter may be NULL in which case the current
		default CFAllocator is used. If this reference is not
		a valid CFAllocator, the behavior is undefined.
	@result Returns a notification string for the current console user.
*/
CFStringRef
SCDynamicStoreKeyCreateConsoleUser		(
						CFAllocatorRef	__nullable	allocator
						)		__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCDynamicStoreKeyCreateHostNames
	@discussion Creates a key that can be used in conjunction with the
		SCDynamicStoreSetNotificationKeys function to receive
		notifications when the HostNames entity changes.  The
		HostNames entity includes the local host name.
	@param allocator The CFAllocator that should be used to allocate
		memory for this key.
		This parameter may be NULL in which case the current
		default CFAllocator is used. If this reference is not
		a valid CFAllocator, the behavior is undefined.
	@result Returns a notification string for the HostNames entity.
*/
CFStringRef
SCDynamicStoreKeyCreateHostNames		(
						CFAllocatorRef	__nullable	allocator
						)		__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);

/*!
	@function SCDynamicStoreKeyCreateLocation
	@discussion Creates a key that can be used in conjunction with the
		SCDynamicStoreSetNotificationKeys function to receive
		notifications when the location identifier changes.
	@param allocator The CFAllocator that should be used to allocate
		memory for this key.
		This parameter may be NULL in which case the current
		default CFAllocator is used. If this reference is not
		a valid CFAllocator, the behavior is undefined.
	@result Returns a notification string for the current location
		identifier.
*/
CFStringRef
SCDynamicStoreKeyCreateLocation			(
						CFAllocatorRef	__nullable	allocator
						)		__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);

/*!
	@function SCDynamicStoreKeyCreateProxies
	@discussion Creates a key that can be used in conjunction with
		the SCDynamicStoreSetNotificationKeys function to receive
		notifications when the current network proxy settings
		(such as HTTP or FTP) are changed.
	@param allocator The CFAllocator that should be used to allocate
		memory for this key.
		This parameter may be NULL in which case the current
		default CFAllocator is used. If this reference is not
		a valid CFAllocator, the behavior is undefined.
	@result Returns a notification string for the current proxy settings.
*/
CFStringRef
SCDynamicStoreKeyCreateProxies			(
						CFAllocatorRef	__nullable	allocator
						)		__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

__END_DECLS

CF_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#endif	/* _SCDYNAMICSTOREKEY_H */
// ==========  SystemConfiguration.framework/Headers/SCPreferencesSetSpecific.h
/*
 * Copyright (c) 2000-2002, 2004, 2005, 2008, 2015 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _SCPREFERENCESSETSPECIFIC_H
#ifdef	USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS
#include <SystemConfiguration/_SCPreferencesSetSpecific.h>
#else	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#define _SCPREFERENCESSETSPECIFIC_H

#include <Availability.h>
#include <sys/cdefs.h>
#include <CoreFoundation/CoreFoundation.h>
#include <SystemConfiguration/SCPreferences.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_ASSUME_NONNULL_BEGIN

/*!
	@header SCPreferencesSetSpecific
	@discussion The functions in the SCPreferencesSetSpecific API allow
		an application to set specific configuration information
		about the current system (for example, the computer or
		sharing name).

		To access configuration preferences, you must first establish
		a preferences session using the SCPreferencesCreate function.
 */


__BEGIN_DECLS

/*!
	@function SCPreferencesSetComputerName
	@discussion Updates the computer name preference.

		Note: To commit these changes to permanent storage you must
		call the SCPreferencesCommitChanges function.
		In addition, you must call the SCPreferencesApplyChanges
		function for the new name to become active.
	@param prefs The preferences session.
	@param name The computer name to be set.
	@param nameEncoding The encoding associated with the computer name.
	@result Returns TRUE if successful; FALSE otherwise.
 */
Boolean
SCPreferencesSetComputerName		(
					SCPreferencesRef	prefs,
					CFStringRef		name,
					CFStringEncoding	nameEncoding
					)			__OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_NA);

/*!
	@function SCPreferencesSetLocalHostName
	@discussion Updates the local host name.

		Note: To commit these changes to permanent storage you must
		call the SCPreferencesCommitChanges function.
		In addition, you must call the SCPreferencesApplyChanges
		function for the new name to become active.
	@param prefs The preferences session.
	@param name The local host name to be set.

	Note: this string must conform to the naming conventions of a DNS host
		name as specified in RFC 1034 (section 3.5).
	@result Returns TRUE if successful; FALSE otherwise.
 */
Boolean
SCPreferencesSetLocalHostName		(
					SCPreferencesRef	prefs,
					CFStringRef		name
					)			__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);

__END_DECLS

CF_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif	/* USE_SYSTEMCONFIGURATION_PRIVATE_HEADERS */
#endif /* _SCPREFERENCESSETSPECIFIC_H */
// ==========  SystemConfiguration.framework/Headers/CaptiveNetwork.h
/*
 * Copyright (c) 2009-2015 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _CAPTIVENETWORK_H
#define _CAPTIVENETWORK_H

#include <Availability.h>
#include <sys/cdefs.h>
#include <CoreFoundation/CoreFoundation.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_ASSUME_NONNULL_BEGIN

/*!
	@header CaptiveNetwork
	@discussion The CaptiveNetwork API allows applications to interact
		with Captive Network Support. Captive Network Support is a
		system component responsible for detecting and help users
		navigate networks that require interaction before providing
		internet access. The most common Captive Networks are WiFi
		Hotspots in places like airports, restaurants, and hotels.
		Captive Network Support will attempt to authenticate if
		possible or drop a user in to a web sheet if authentication
		is not possible. In the web sheet the user has an opportunity
		to authenticate or disassociate from the network.

		The following APIs are designed for third party applications
		that may handle authentication on these networks on behalf of
		the user.

		These APIs are treated as advisory only.
		There is no guarantee or contract that the operating system
		will take the intended action.

	@note IMPORTANT: This API is deprecated starting in iOS 9.
		For captive network applications, this has been completely
		replaced by <NetworkExtension/NEHotspotHelper.h>.
		For other applications, there is no direct replacement.
		Please file a bug describing your use of this API so that
		we can consider your requirements as this situation evolves.
 */

#define CN_DEPRECATION_NOTICE						\
    "For captive network applications, this has been completely "	\
    "replaced by <NetworkExtension/NEHotspotHelper.h>. "		\
    "For other applications, there is no direct replacement. "		\
    "Please file a bug describing your use of this API to that "	\
    "we can consider your requirements as this situation evolves."

__BEGIN_DECLS

/*!
	@function CNSetSupportedSSIDs
	@discussion Provides Captive Network Support with an updated list of
		SSIDs that this application will perform authentication on.

		Captive Network Support suppresses showing the Web Sheet
		for a captive Wi-Fi network if that network's SSID is in the
		specified list.

		On iOS, the registrations persist until the application is
		removed from the device.

		On MacOSX, the registrations persist as long as the application
		is running.

	@param ssidArray A CFArray of CFStrings of the SSIDs.
	@result Returns TRUE if the operation succeeded, FALSE otherwise.
 */
Boolean
CNSetSupportedSSIDs	(CFArrayRef	ssidArray)
    __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_8, __MAC_NA,
				       __IPHONE_4_0, __IPHONE_9_0,
				       "Replaced by <NetworkExtension/NEHotspotHelper.h>");

/*!
	@function CNMarkPortalOnline
	@discussion Tells Captive Network Support that your application has
		authenticated the device to the network. Captive Network Support
		will notify the rest of the system that WiFi is now a viable
		interface.
	@param interfaceName Name of the interface that is now online.
	@result Returns TRUE if the operation succeeded, FALSE otherwise.
 */
Boolean
CNMarkPortalOnline	(CFStringRef	interfaceName)
    __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_8, __MAC_NA,
				       __IPHONE_4_0, __IPHONE_9_0,
				       "Replaced by <NetworkExtension/NEHotspotHelper.h>");

/*!
	@function CNMarkPortalOffline
	@discussion Tells Captive Network Support that the device is not
		authenticated on the given network interface.
	@param interfaceName Name of the interface that is still captive.
	@result Returns TRUE if the operation succeeded, FALSE otherwise.
 */
Boolean
CNMarkPortalOffline	(CFStringRef	interfaceName)
    __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_8, __MAC_NA,
				       __IPHONE_4_0, __IPHONE_9_0,
				       "Replaced by <NetworkExtension/NEHotspotHelper.h>");

/*!
 @function CNCopySupportedInterfaces
 @discussion copies a list of all interfaces CaptiveNetworkSupport is monitoring.
 @result An array of CFStringRef- BSD interface names.
	 Returns NULL if an error was encountered.
	 You MUST release the returned value.
 */
CFArrayRef __nullable
CNCopySupportedInterfaces	(void)
    __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_8, __MAC_NA,
				       __IPHONE_4_1, __IPHONE_9_0,
				       CN_DEPRECATION_NOTICE);

/*!
 @constant kCNNetworkInfoKeySSIDData
 @discussion NetworkInfo Dictionary key for SSID in CFData format
 */
extern const CFStringRef kCNNetworkInfoKeySSIDData
    __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_NA, __MAC_NA,
				       __IPHONE_4_1, __IPHONE_9_0,
				       CN_DEPRECATION_NOTICE);

/*!
 @constant kCNNetworkInfoKeySSID
 @discussion NetworkInfo Dictionary key for SSID in CFString format
 */
extern const CFStringRef kCNNetworkInfoKeySSID
    __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_NA, __MAC_NA,
				       __IPHONE_4_1, __IPHONE_9_0,
				       CN_DEPRECATION_NOTICE);

/*!
 @constant kCNNetworkInfoKeyBSSID
 @discussion NetworkInfo Dictionary key for BSSID in CFString format
 */
extern const CFStringRef kCNNetworkInfoKeyBSSID
    __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_NA, __MAC_NA,
				       __IPHONE_4_1, __IPHONE_9_0,
				       CN_DEPRECATION_NOTICE);

/*!
 @function CNCopyCurrentNetworkInfo
 @discussion Returns the Network Info for the specified interface.
	For example, Network Info dictionary will contain the following
	keys, and values:
	<pre>
	@textblock
	Keys                      : Values
	=======================================
	kCNNetworkInfoKeySSIDData : CFDataRef
	kCNNetworkInfoKeySSID     : CFStringRef
	kCNNetworkInfoKeyBSSID    : CFStringRef
	@/textblock
	</pre>
 @param interfaceName Name of the interface you are interested in
 @result Network Info dictionary associated with the interface.
	 Returns NULL if an error was encountered.
	 You MUST release the returned value.
 */
CFDictionaryRef __nullable
CNCopyCurrentNetworkInfo	(CFStringRef interfaceName)
    __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_NA, __MAC_NA,
				       __IPHONE_4_1, __IPHONE_9_0,
				       CN_DEPRECATION_NOTICE);

__END_DECLS

CF_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif	/* _CAPTIVENETWORK_H */