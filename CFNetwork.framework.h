// ==========  CFNetwork.framework/Headers/CFHost.h
/*
	 File:	   CFNetwork/CFHost.h
 
	 Contains:   CoreFoundation CFHost header
 
	 Copyright:  Copyright (c) 2001-2013 Apple Inc. All rights reserved.
 
	 Bugs?:	  For bug reports, consult the following page on
				 the World Wide Web:
 
					 http://developer.apple.com/bugreporter/
 
*/
#ifndef __CFHOST__
#define __CFHOST__

#ifndef __CFNETWORKDEFS__
#include <CFNetwork/CFNetworkDefs.h>
#endif

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifndef __CFSTREAM__
#include <CoreFoundation/CFStream.h>
#endif



#if PRAGMA_ONCE
#pragma once
#endif

CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

#pragma pack(push, 2)


/*
 *  CFHostRef
 *  
 *  Discussion:
 *	This is the type of a reference to a host name or address lookup.
 */
typedef struct __CFHost*				CFHostRef;

/*
 *  kCFStreamErrorDomainNetDB
 *  
 *  Discussion:
 *	Errors listed in netdb.h
 *  
 */
CFN_EXPORT const SInt32 kCFStreamErrorDomainNetDB CF_AVAILABLE(10_3, 2_0);


/*
 *  kCFStreamErrorDomainSystemConfiguration
 *  
 *  Discussion:
 *	Errors listed in SystemConfiguration/SystemConfiguration.h
 *  
 */
CFN_EXPORT const SInt32 kCFStreamErrorDomainSystemConfiguration CF_AVAILABLE(10_3, 2_0);



/*
 *  CFHostInfoType
 *  
 *  Discussion:
 *	Host information types to be resolved.
 */
typedef CF_ENUM(int, CFHostInfoType) {

  /*
   * Results value is a CFArray of CFData's (each being a struct
   * sockaddr)
   */
  kCFHostAddresses			  = 0,

  /*
   * Results value is a CFArray of CFString's
   */
  kCFHostNames				  = 1,

  /*
   * Results value is a CFData wrapping SCNetworkConnectionFlags
   * (defined in SystemConfiguration/SCNetwork.h)
   */
  kCFHostReachability		   = 2
};


/*
 *  CFHostClientContext
 *  
 *  Discussion:
 *	Structure containing the user-defined data and callbacks for
 *	CFHost objects.
 */
struct CFHostClientContext {

  /*
   * The version number of the structure type being passed in as a
   * parameter to the CFHost client function. Valid version number is
   * currently 0.
   */
  CFIndex			 version;

  /*
   * An arbitrary pointer to client-defined data, which can be
   * associated with the host and is passed to the callbacks.
   */
  void *	__nullable		  info;

  /*
   * The callback used to add a retain for the host on the info pointer
   * for the life of the host, and may be used for temporary references
   * the host needs to take. This callback returns the actual info
   * pointer to store in the host, almost always just the pointer
   * passed as the parameter.
   */
  CFAllocatorRetainCallBack  __nullable retain;

  /*
   * The callback used to remove a retain previously added for the host
   * on the info pointer.
   */
  CFAllocatorReleaseCallBack  __nullable release;

  /*
   * The callback used to create a descriptive string representation of
   * the info pointer (or the data pointed to by the info pointer) for
   * debugging purposes. This is used by the CFCopyDescription()
   * function.
   */
  CFAllocatorCopyDescriptionCallBack  __nullable copyDescription;
};
typedef struct CFHostClientContext	  CFHostClientContext;

/*
 *  CFHostClientCallBack
 *  
 *  Discussion:
 *	Callback function which is called upon error or completion of an
 *	asynchronous resolve.
 *  
 *  Parameters:
 *	
 *	theHost:
 *	  Host whose resolution is complete.
 *	
 *	typeInfo:
 *	  Enum representing which info resolution is complete.
 *	
 *	error:
 *	  Reference to an error structure if the resolution failed.
 *	
 *	info:
 *	  Client's info reference which was passed into the client
 *	  context.
 */
typedef CALLBACK_API_C( void , CFHostClientCallBack )(CFHostRef theHost, CFHostInfoType typeInfo, const CFStreamError * __nullable error, void * __nullable info);


/*
 *  CFHostGetTypeID()
 *  
 *  Discussion:
 *	Returns the type identifier of all CFHost instances.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 */
CFN_EXPORT CFTypeID 
CFHostGetTypeID(void) CF_AVAILABLE(10_3, 2_0);


/*
 *  CFHostCreateWithName()
 *  
 *  Discussion:
 *	Creates a new host object with the given name.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	allocator:
 *	  The CFAllocator which should be used to allocate memory for the
 *	  host. If this reference is not a valid CFAllocator, the
 *	  behavior is undefined.
 *	
 *	hostname:
 *	  A CFStringRef representing the name of the host. Must be
 *	  non-NULL.  If this reference is not a valid CFStringRef, the
 *	  behavior is undefined.
 *  
 *  Result:
 *	A valid CFHostRef which may now be resolved, or NULL if
 *	unsuccessful.
 *  
 */
CFN_EXPORT CFHostRef 
CFHostCreateWithName(CFAllocatorRef __nullable allocator, CFStringRef hostname) CF_AVAILABLE(10_3, 2_0);


/*
 *  CFHostCreateWithAddress()
 *  
 *  Discussion:
 *	Creates a new host object with the given address.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	allocator:
 *	  The CFAllocator which should be used to allocate memory for the
 *	  host. If this reference is not a valid CFAllocator, the
 *	  behavior is undefined.
 *	
 *	addr:
 *	  A CFDataRef containing a struct sockaddr which is the address
 *	  of the host. Must be non-NULL.  If this reference is not a
 *	  valid CFDataRef, the behavior is undefined.
 *  
 *  Result:
 *	A valid CFHostRef which may now be resolved, or NULL if
 *	unsuccessful.
 *  
 */
CFN_EXPORT CFHostRef 
CFHostCreateWithAddress(CFAllocatorRef __nullable allocator, CFDataRef addr) CF_AVAILABLE(10_3, 2_0);


/*
 *  CFHostCreateCopy()
 *  
 *  Discussion:
 *	Creates a new host object as a copy of host argument.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  The CFAllocator which should be used to allocate memory for the
 *	  new host. If this reference is not a valid CFAllocator, the
 *	  behavior is undefined.
 *	
 *	host:
 *	  A CFHostRef representing the original host. Must be non-NULL. 
 *	  If this reference is not a valid CFHostRef, the behavior is
 *	  undefined.
 *  
 *  Result:
 *	A valid CFHostRef which contains a copy of all previously
 *	resolved data from the original.  NULL is returned in the case of
 *	failure.
 *  
 */
CFN_EXPORT CFHostRef 
CFHostCreateCopy(CFAllocatorRef __nullable alloc, CFHostRef host) CF_AVAILABLE(10_3, 2_0);


/*
 *  CFHostStartInfoResolution()
 *  
 *  Discussion:
 *	Performs a lookup for the given host.  It will search for the
 *	requested information if there is no other active request. 
 *	Previously cached information of the given type will be released.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	theHost:
 *	  The CFHostRef which should be resolved. Must be non-NULL. If
 *	  this reference is not a valid CFHostRef, the behavior is
 *	  undefined.
 *	
 *	info:
 *	  The enum representing the type of information to be retrieved. 
 *	  If the value is not a valid type, the behavior is undefined.
 *	
 *	error:
 *	  A reference to a CFStreamError structure which will be filled
 *	  with any error information should an error occur.  May be set
 *	  to NULL if error information is not wanted.
 *  
 *  Result:
 *	Returns TRUE on success and FALSE on failure.  In asynchronous
 *	mode, this function will return immediately.  In synchronous
 *	mode, it will block until the resolve has completed or until the
 *	resolve is cancelled.
 *  
 */
CFN_EXPORT Boolean 
CFHostStartInfoResolution(CFHostRef theHost, CFHostInfoType info, CFStreamError * __nullable error) CF_AVAILABLE(10_3, 2_0);


/*
 *  CFHostGetAddressing()
 *  
 *  Discussion:
 *	Tries to retrieve the known addresses from the given host.
 *	Returns a CFArrayRef of addresses if known and there were some.
 *	NULL is returned otherwise.  Each address is a CFDataRef wrapping
 *	a struct sockaddr.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The function gets the data in a thread-safe manner, but the
 *	resulting data is not safe.  Since it is returned as a matter of
 *	a get opposed to a copy, the data is not safe if the host is
 *	being altered from another thread.
 *  
 *  Parameters:
 *	
 *	theHost:
 *	  The CFHostRef which contains the relevant information. Must be
 *	  non-NULL. If this reference is not a valid CFHostRef, the
 *	  behavior is undefined.
 *	
 *	hasBeenResolved:
 *	  A reference to a Boolean which returns FALSE if the information
 *	  was not available (e.g. CFHostStartInfoResolution has not been
 *	  called), otherwise TRUE will be returned.
 *  
 */
CFN_EXPORT __nullable CFArrayRef
CFHostGetAddressing(CFHostRef theHost, Boolean * __nullable hasBeenResolved) CF_AVAILABLE(10_3, 2_0);


/*
 *  CFHostGetNames()
 *  
 *  Discussion:
 *	Tries to retrieve the names/aliases from the given host. Returns
 *	a CFArrayRef of names for the given host.  NULL is returned
 *	otherwise.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The function gets the data in a thread-safe manner, but the
 *	resulting data is not safe.  Since it is returned as a matter of
 *	a get opposed to a copy, the data is not safe if the host is
 *	being altered from another thread.
 *  
 *  Parameters:
 *	
 *	theHost:
 *	  The CFHostRef which contains the relevant information. Must be
 *	  non-NULL. If this reference is not a valid CFHostRef, the
 *	  behavior is undefined.
 *	
 *	hasBeenResolved:
 *	  A reference to a Boolean which returns FALSE if the information
 *	  was not available (e.g. CFHostStartInfoResolution has not been
 *	  called), otherwise TRUE will be returned. Can be NULL.
 *  
 */
CFN_EXPORT __nullable CFArrayRef
CFHostGetNames(CFHostRef theHost, Boolean * __nullable hasBeenResolved) CF_AVAILABLE(10_3, 2_0);


/*
 *  CFHostGetReachability()
 *  
 *  Discussion:
 *	Tries to retrieve the reachability of the given host. Returns a
 *	CFDataRef which wraps the reachability flags. NULL will be
 *	returned if the value has not been resolved. The possible values
 *	of these flags is declared in SystemConfiguration/SCNetwork.h.
 *	Returns FALSE if the information was not available, otherwise
 *	TRUE will be returned with the results containing the requested
 *	information.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The function gets the data in a thread-safe manner, but the
 *	resulting data is not safe.  Since it is returned as a matter of
 *	a get opposed to a copy, the data is not safe if the host is
 *	being altered from another thread.
 *  
 *  Parameters:
 *	
 *	theHost:
 *	  The CFHostRef which contains the relevant information. Must be
 *	  non-NULL. If this reference is not a valid CFHostRef, the
 *	  behavior is undefined.
 *	
 *	hasBeenResolved:
 *	  A reference to a Boolean which returns FALSE if the information
 *	  was not available (e.g. CFHostStartInfoResolution has not been
 *	  called), otherwise TRUE will be returned. Can be NULL.
 *  
 */
CFN_EXPORT __nullable CFDataRef
CFHostGetReachability(CFHostRef theHost, Boolean * __nullable hasBeenResolved) CF_AVAILABLE(10_3, 2_0);


/*
 *  CFHostCancelInfoResolution()
 *  
 *  Discussion:
 *	Cancels an outstanding asynchronous or synchronous resolve.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	theHost:
 *	  The CFHostRef which is currently resolving.  Must be non-NULL.
 *	  If this reference is not a valid CFHostRef, the behavior is
 *	  undefined.
 *	
 *	info:
 *	  The enum representing which resolution to be canceled.  If the
 *	  value is not a valid type, the behavior is undefined.
 *  
 */
CFN_EXPORT void 
CFHostCancelInfoResolution(CFHostRef theHost, CFHostInfoType info) CF_AVAILABLE(10_3, 2_0);


/*
 *  CFHostSetClient()
 *  
 *  Discussion:
 *	Associates a client context and callback function with a CFHostRef.
 *	This is required for asynchronous usage.  If not set, resolve will
 *	take place synchronously.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	theHost:
 *	  The CFHostRef which is getting a client.  Must be non-NULL. If
 *	  this reference is not a valid CFHostRef, the behavior is
 *	  undefined.
 *	
 *	clientCB:
 *	  A CFHostClientCallBack which will be called when the resolve
 *	  completes or is cancelled.  Use NULL to remove the client
 *	  association with a host object.
 *	
 *	clientContext:
 *	  A CFHostClientContext which is used to set the contextual
 *	  information associated with the host object.  The info pointer
 *	  from the struct will be passed to the callback function. If
 *	  setting a client, this value must be non-NULL.
 *  
 *  Result:
 *	Returns TRUE if the procedure was a success, otherwise it returns
 *	FALSE.
 *  
 */
CFN_EXPORT Boolean 
CFHostSetClient(CFHostRef theHost, CFHostClientCallBack __nullable clientCB, CFHostClientContext * __nullable clientContext) CF_AVAILABLE(10_3, 2_0);


/*
 *  CFHostScheduleWithRunLoop()
 *  
 *  Discussion:
 *	Schedules the given host on a run loop and mode so the client
 *	will receive its callbacks on that loop and mode.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	theHost:
 *	  The CFHostRef which is being scheduled.  Must be non-NULL. If
 *	  this reference is not a valid CFHostRef, the behavior is
 *	  undefined.
 *	
 *	runLoop:
 *	  A CFRunLoopRef on which the host should be scheduled. Must be
 *	  non-NULL.  If this reference is not a valid CFRunLoopRef, the
 *	  behavior is undefined.
 *	
 *	runLoopMode:
 *	  A CFStringRef which is the mode in which the run loop will be
 *	  running when notification occurs.  Must be non-NULL. If this
 *	  reference is not a valid CFStringRef, the behavior is undefined.
 *  
 */
CFN_EXPORT void 
CFHostScheduleWithRunLoop(CFHostRef theHost, CFRunLoopRef runLoop, CFStringRef runLoopMode) CF_AVAILABLE(10_3, 2_0);


/*
 *  CFHostUnscheduleFromRunLoop()
 *  
 *  Discussion:
 *	Unschedules the given host from a run loop and mode so the client
 *	will not receive its callbacks on that loop and mode.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	theHost:
 *	  The CFHostRef which is being unscheduled.  Must be non-NULL. If
 *	  this reference is not a valid CFHostRef, the behavior is
 *	  undefined.
 *	
 *	runLoop:
 *	  A CFRunLoopRef on which the host is scheduled and should now be
 *	  unscheduled.  Must be non-NULL.  If this reference is not a
 *	  valid CFRunLoopRef, the behavior is undefined.
 *	
 *	runLoopMode:
 *	  A CFStringRef which is the mode in which the host is scheduled
 *	  and should be unscheduled.  Must be non-NULL. If this reference
 *	  is not a valid CFStringRef, the behavior is undefined.
 *  
 */
CFN_EXPORT void 
CFHostUnscheduleFromRunLoop(CFHostRef theHost, CFRunLoopRef runLoop, CFStringRef runLoopMode) CF_AVAILABLE(10_3, 2_0);



#pragma pack(pop)

CF_ASSUME_NONNULL_END
CF_EXTERN_C_END

#endif /* __CFHOST__ */

// ==========  CFNetwork.framework/Headers/CFNetServices.h
/*
	 File:	   CFNetwork/CFNetServices.h
 
	 Contains:   CoreFoundation Network Net Services header
 
	 Copyright:  Copyright (c) 2001-2013 Apple Inc. All rights reserved.
 
	 Bugs?:	  For bug reports, consult the following page on
				 the World Wide Web:
 
					 http://developer.apple.com/bugreporter/
 
*/
#ifndef __CFNETSERVICES__
#define __CFNETSERVICES__

#ifndef __CFNETWORKDEFS__
#include <CFNetwork/CFNetworkDefs.h>
#endif

#ifndef __CFBASE__
#include <CoreFoundation/CFBase.h>
#endif

#ifndef __CFSTREAM__
#include <CoreFoundation/CFStream.h>
#endif



#if PRAGMA_ONCE
#pragma once
#endif

CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

#pragma pack(push, 2)


/*
 *  CFNetServiceRef
 *  
 *  Discussion:
 *	This is the type of a reference to a service.  It may be used for
 *	registering or for resolving.
 */
typedef struct __CFNetService*		  CFNetServiceRef;

/*
 *  CFNetServiceMonitorRef
 *  
 *  Discussion:
 *	This is the type of a reference to a service monitor.  It may be
 *	used for watching record changes on a CFNetServiceRef.
 */
typedef struct __CFNetServiceMonitor*   CFNetServiceMonitorRef;

/*
 *  CFNetServiceBrowserRef
 *  
 *  Discussion:
 *	This is the type of a reference to a service or domain browser.
 *	It may be used for discovering services or domains.
 */
typedef struct __CFNetServiceBrowser*   CFNetServiceBrowserRef;

#ifdef __MACH__
/*
 *  kCFStreamErrorDomainMach
 *  
 *  Discussion:
 *	Errors reported by mach.  See <mach/error.h>
 *  
 */
CFN_EXPORT const SInt32 kCFStreamErrorDomainMach CF_AVAILABLE(10_2, 2_0);
#endif  /* defined(__MACH__) */

/*
 *  kCFStreamErrorDomainNetServices
 *  
 *  Discussion:
 *	Errors listed below or reported by the Service Discovery API's.
 *	See <dns_sd.h>.  The Service Discovery errors will only be
 *	returned when using the new, Mac OS X 10.4-based API's or
 *	CFNetServiceBrowser.
 *  
 */
CFN_EXPORT const SInt32 kCFStreamErrorDomainNetServices CF_AVAILABLE(10_2, 2_0);



/*
 *  CFNetServicesError
 *  
 *  Discussion:
 *	Errors from the kCFStreamErrorDomainNetServices domain.
 */
typedef CF_ENUM(int, CFNetServicesError) {

  /*
   * An error of unknown type has occured.
   */
  kCFNetServicesErrorUnknown	= -72000L,

  /*
   * The given registration has had a name collision.  Registration
   * should be cancelled and should try again probably with a different
   * name.
   */
  kCFNetServicesErrorCollision  = -72001L,

  /*
   * Not used
   */
  kCFNetServicesErrorNotFound   = -72002L,

  /*
   * There is already a register, resolve, browse, or monitor in
   * progress on the given object.
   */
  kCFNetServicesErrorInProgress = -72003L,

  /*
   * Not used
   */
  kCFNetServicesErrorBadArgument = -72004L,

  /*
   * The register, resolve, or browse on the object has been cancelled.
   */
  kCFNetServicesErrorCancel	 = -72005L,

  /*
   * The given CFNetServiceBrowser or CFNetServiceMonitor has already
   * been invalidated and can no longer be used.
   */
  kCFNetServicesErrorInvalid	= -72006L,

  /*
   * The given CFNetServiceResolveWithTimeout has hit the timeout
   * before a successful resolve.
   */
  kCFNetServicesErrorTimeout	= -72007L
};



/*
 *  CFNetServiceMonitorType
 *  
 *  Discussion:
 *	Record type specifier in order to inform CFNetServiceMonitor to
 *	watch for certain record changes.
 */
typedef CF_ENUM(int, CFNetServiceMonitorType) {

  /*
   * Watch for TXT record changes.
   */
  kCFNetServiceMonitorTXT = 1
};


/*
 *  CFNetService flags
 *
 *  Discussion:
 *  Bit flags to be used for registration of a service with CFNetServiceRegisterWithOptions.
 */
typedef CF_OPTIONS(CFOptionFlags, CFNetServiceRegisterFlags) {
	
  /*
   * Indicate that registration should not auto-rename the service to prevent name conflicts.
   */
  kCFNetServiceFlagNoAutoRename = 1
};


/*
 *  CFNetServiceBrowser flags
 *  
 *  Discussion:
 *	Result bit flags passed to CFNetServiceBrowserClientCallBack.
 */
typedef CF_OPTIONS(CFOptionFlags, CFNetServiceBrowserFlags) {

  /*
   * Client will get another callback briefly and shouldn't do costly screen updates (or such).
   */
  kCFNetServiceFlagMoreComing = 1,

  /*
   * If off, the result is a service.
   */
  kCFNetServiceFlagIsDomain = 2,

  /*
   * The result domain is the default domain for the given domain browse type (registration or browse).
   */
  kCFNetServiceFlagIsDefault = 4,

  /*
   * Same as the previous but incorrectly named. Kept for compatibility.
   */
  kCFNetServiceFlagIsRegistrationDomain CF_ENUM_DEPRECATED(10_2, 10_4, 2_0, 2_0) = 4,

  /*
   * The result item should be removed and not added.
   */
  kCFNetServiceFlagRemove = 8
};



/*
 *  CFNetServiceClientContext
 *  
 *  Discussion:
 *	Structure containing the user-defined data and callbacks for
 *	CFNetService and CFNetServiceBrowser objects.
 */
struct CFNetServiceClientContext {

  /*
   * The version number of the structure type being passed in as a
   * parameter to the CFNetService, Browser, or Monitor client
   * function.  The current version number is 0.
   */
  CFIndex			 version;

  /*
   * An arbitrary pointer to client-defined data, which can be
   * associated with the service/browser and is passed to the callbacks.
   */
  void *	__nullable	 info;

  /*
   * The callback used to add a retain for the service/browser on the
   * info pointer for the life of the service/browser, and may be used
   * for temporary references the service/browser needs to take. This
   * callback returns the actual info pointer to store in the
   * service/browser, almost always just the pointer passed as the
   * parameter.
   */
  CFAllocatorRetainCallBack  __nullable retain;

  /*
   * The callback used to remove a retain previously added for the
   * service/browser on the info pointer.
   */
  CFAllocatorReleaseCallBack  __nullable release;

  /*
   * The callback used to create a descriptive string representation of
   * the info pointer (or the data pointed to by the info pointer) for
   * debugging purposes. This is used by the CFCopyDescription()
   * function.
   */
  CFAllocatorCopyDescriptionCallBack  __nullable copyDescription;
};
typedef struct CFNetServiceClientContext CFNetServiceClientContext;

/*
 *  CFNetServiceClientCallBack
 *  
 *  Discussion:
 *	Callback function which is called upon error or completion of
 *	resolve or register.  If resolving with the deprecated API's, the
 *	callback may be called multiple times, once for each resolved
 *	address.
 *  
 *  Parameters:
 *	
 *	theService:
 *	  Service receiving the event.
 *	
 *	error:
 *	  Reference to an error structure if the event is a failure.
 *	
 *	info:
 *	  Client's info reference which was passed into the client
 *	  context.
 */
typedef CALLBACK_API_C( void , CFNetServiceClientCallBack )(CFNetServiceRef theService, CFStreamError * __nullable error, void  * __nullable info);

/*
 *  CFNetServiceMonitorClientCallBack
 *  
 *  Discussion:
 *	Callback function which is called as the monitored record changes.
 *  
 *  Parameters:
 *	
 *	theMonitor:
 *	  CFNetServiceMonitor receiving the event.
 *	
 *	theService:
 *	  Service receiving the event.
 *	
 *	typeInfo:
 *	  The information type which changed.
 *	
 *	rdata:
 *	  The contents of the record that changed.
 *	
 *	error:
 *	  Reference to an error structure if the event is a failure.
 *	
 *	info:
 *	  Client's info reference which was passed into the client
 *	  context.
 */
typedef CALLBACK_API_C( void , CFNetServiceMonitorClientCallBack )(CFNetServiceMonitorRef theMonitor, CFNetServiceRef __nullable theService, CFNetServiceMonitorType typeInfo, CFDataRef __nullable rdata, CFStreamError * __nullable error, void * __nullable info);

/*
 *  CFNetServiceBrowserClientCallBack
 *  
 *  Discussion:
 *	Callback function which is called upon error or upon successful
 *	discovery of services or domains.
 *  
 *  Parameters:
 *	
 *	browser:
 *	  CFNetServiceBrowser receiving the event.
 *	
 *	flags:
 *	  Bitwise flags indicating the event or further information about
 *	  the event.
 *	
 *	domainOrService:
 *	  If searching for domains, a CFStringRef indicating the domain
 *	  which was found or is going away.  If searching for services,
 *	  the service which was found or is going away.
 *	
 *	error:
 *	  Reference to an error structure if the event is a failure.
 *	
 *	info:
 *	  Client's info reference which was passed into the client
 *	  context.
 */
typedef CALLBACK_API_C( void , CFNetServiceBrowserClientCallBack )(CFNetServiceBrowserRef browser, CFOptionFlags flags, CFTypeRef __nullable domainOrService, CFStreamError * __nullable error, void * __nullable info);

/*
 *  CFNetServiceGetTypeID()
 *  
 *  Discussion:
 *	Returns the type identifier of all CFNetService instances.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 */
CFN_EXPORT CFTypeID 
CFNetServiceGetTypeID(void) CF_AVAILABLE(10_2, 2_0);


/*
 *  CFNetServiceMonitorGetTypeID()
 *  
 *  Discussion:
 *	Returns the type identifier of all CFNetServiceMonitor instances.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 */
CFN_EXPORT CFTypeID 
CFNetServiceMonitorGetTypeID(void) CF_AVAILABLE(10_4, 2_0);


/*
 *  CFNetServiceBrowserGetTypeID()
 *  
 *  Discussion:
 *	Returns the type identifier of all CFNetServiceBrowser instances.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 */
CFN_EXPORT CFTypeID 
CFNetServiceBrowserGetTypeID(void) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFNetServiceCreate()
 *  
 *  Discussion:
 *	Creates an instance of a Network Service.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  The CFAllocator which should be used to allocate memory for the
 *	  service and its storage for values. If this reference is not a
 *	  valid CFAllocator, the behavior is undefined.
 *	
 *	domain:
 *	  The network domain in which it is registered or will be
 *	  registered. This value must be non-NULL.
 *	
 *	serviceType:
 *	  The type of service being registered or resolved on the
 *	  network. The service type consists of the application protocol
 *	  name followed by the transport protocol name, separated by a
 *	  dot (e.g. "_ftp._tcp").  The application protocol name should
 *	  be 14 characters or less, and should only contain lower-case
 *	  letters, digits, and hyphens.  New service types should be
 *	  registered at <htp://www.dns-sd.org/ServiceTypes.html>.  This
 *	  value must be non-NULL.
 *	
 *	name:
 *	  The name of the machine or application advertising the service.
 *	   If this value is not unique, registering will eventually fail.
 *	   This value must be non-NULL.  This value is usually displayed
 *	  in a browser for the user.
 *	
 *	port:
 *	  The port on which the service is listening.  This must be
 *	  non-zero for services which are to be registered.
 *  
 *  Result:
 *	A valid CFNetService which may now be registered or resolved, or
 *	NULL if unsuccessful.
 *  
 */
CFN_EXPORT CFNetServiceRef 
CFNetServiceCreate(CFAllocatorRef __nullable alloc, CFStringRef domain, CFStringRef serviceType, CFStringRef name, SInt32 port) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFNetServiceCreateCopy()
 *  
 *  Discussion:
 *	Creates a new CFNetService object as a copy of service argument.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  The CFAllocator which should be used to allocate memory for the
 *	  new service. If this reference is not a valid CFAllocator, the
 *	  behavior is undefined.
 *	
 *	service:
 *	  A CFNetServiceRef representing the original service. Must be
 *	  non-NULL.  If this If this reference is not a valid
 *	  CFNetServiceRef, the behavior is undefined.
 *  
 *  Result:
 *	Returns a valid CFNetServiceRef which contains a copy of all
 *	previously resolved data from the original.  NULL is returned in
 *	the case of failure.
 *  
 */
CFN_EXPORT CFNetServiceRef 
CFNetServiceCreateCopy(CFAllocatorRef __nullable alloc, CFNetServiceRef service) CF_AVAILABLE(10_3, 2_0);



/*
 *  CFNetServiceGetDomain()
 *  
 *  Discussion:
 *	Query a Network Service for its domain.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The function gets the data in a thread-safe manner, but the
 *	resulting data is not safe.  Since it is returned as a matter of
 *	a get opposed to a copy, the data is not safe if the service is
 *	being altered from another thread.
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The Network Service to be queried.  Must be non-NULL.
 *  
 *  Result:
 *	CFStringRef which is the service's domain.
 *  
 */
CFN_EXPORT CFStringRef 
CFNetServiceGetDomain(CFNetServiceRef theService) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFNetServiceGetType()
 *  
 *  Discussion:
 *	Query a Network Service for its type.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The function gets the data in a thread-safe manner, but the
 *	resulting data is not safe.  Since it is returned as a matter of
 *	a get opposed to a copy, the data is not safe if the service is
 *	being altered from another thread.
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The Network Service to be queried.  Must be non-NULL.
 *  
 *  Result:
 *	CFStringRef which is the service's service type.
 *  
 */
CFN_EXPORT CFStringRef 
CFNetServiceGetType(CFNetServiceRef theService) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFNetServiceGetName()
 *  
 *  Discussion:
 *	Query a Network Service for its name.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The function gets the data in a thread-safe manner, but the
 *	resulting data is not safe.  Since it is returned as a matter of
 *	a get opposed to a copy, the data is not safe if the service is
 *	being altered from another thread.
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The Network Service to be queried.  Must be non-NULL.
 *  
 *  Result:
 *	CFStringRef which is the service's name.
 *  
 */
CFN_EXPORT CFStringRef 
CFNetServiceGetName(CFNetServiceRef theService) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFNetServiceRegisterWithOptions()
 *  
 *  Discussion:
 *	Registers the entity on the network.  This requires that the
 *	service has a domain, a type, a name, and a port.  The service is
 *	registered on the network until this function returns or is
 *	cancelled by calling CFNetServiceCancel.  In synchronous mode,
 *	this function will block until there is an error or it is
 *	cancelled from another thread.  In asynchronous mode, this
 *	function returns immediately and the underlying network
 *	registration process will start.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The Network Service to register on the network.  Must be
 *	  non-NULL.
 *	
 *	options:
 *	  A set of bit options used to instruct the registration process.
 *	  Current supported option is kCFNetServiceFlagNoAutoRename.
 *	
 *	error:
 *	  A reference to an error struct which will be set to the error
 *	  and domain of the error should one occur.  If the value of
 *	  error is not desired, set to NULL.
 *  
 *  Result:
 *	Returns FALSE if domain, type, name or port is NULL.  In
 *	synchronous mode, it will always return FALSE as a result of the
 *	error or the cancellation.  In asynchronous mode, it will return
 *	TRUE if the registration process could start.
 *  
 */
CFN_EXPORT Boolean 
CFNetServiceRegisterWithOptions(CFNetServiceRef theService, CFOptionFlags options, CFStreamError * __nullable error) CF_AVAILABLE(10_4, 2_0);



/*
 *  CFNetServiceResolveWithTimeout()
 *  
 *  Discussion:
 *	Resolves the information related to this service.  It will
 *	resolve the target host, the addresses, and the first TXT record
 *	associated with the service.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The CFNetServiceRef which should be resolved. Must be non-NULL.
 *	  If this reference is not a valid CFNetServiceRef, the behavior
 *	  is undefined.
 *	
 *	timeout:
 *	  CFTimeInterval representing the maximum amount of time to take
 *	  to perform the resolve.  If the resolve can not be performed
 *	  within this timeout, the function or callback will recieve a
 *	  timeout error.  Values less than or equal to zero indicate an
 *	  infinite timeout.
 *	
 *	error:
 *	  A reference to a CFStreamError structure which will be filled
 *	  with any error information should an error occur.  May be set
 *	  to NULL if error information is not wanted.
 *  
 *  Result:
 *	Returns TRUE on success and FALSE on failure.  In asynchronous
 *	mode, this function will return immediately.  In synchronous
 *	mode, it will block until the resolve has completed or until the
 *	resolve is cancelled.
 *  
 */
CFN_EXPORT Boolean 
CFNetServiceResolveWithTimeout(CFNetServiceRef theService, CFTimeInterval timeout, CFStreamError * __nullable error) CF_AVAILABLE(10_4, 2_0);



/*
 *  CFNetServiceCancel()
 *  
 *  Discussion:
 *	Cancels an outstanding request for registration or resolution.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The Network Service which is active.  Must be non-NULL.
 *  
 */
CFN_EXPORT void 
CFNetServiceCancel(CFNetServiceRef theService) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFNetServiceGetTargetHost()
 *  
 *  Discussion:
 *	Query a Network Service for its resolve target.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The function gets the data in a thread-safe manner, but the
 *	resulting data is not safe.  Since it is returned as a matter of
 *	a get opposed to a copy, the data is not safe if the service is
 *	being altered from another thread.
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The Network Service to be queried.  Must be non-NULL.
 *  
 *  Result:
 *	Returns The target hostname of the machine providing the service,
 *	or NULL if the entity's target is not known (has not been
 *	resolved).
 *  
 */
CFN_EXPORT __nullable CFStringRef
CFNetServiceGetTargetHost(CFNetServiceRef theService) CF_AVAILABLE(10_4, 2_0);



/*
 *  CFNetServiceGetPortNumber()
 *  
 *  Discussion:
 *	Query a Network Service for its port number.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The function gets the data in a thread-safe manner.
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The Network Service to be queried.  Must be non-NULL.
 *  
 *  Result:
 *	Returns a SInt32 containing the port number in host byte order.
 *	Returns -1 if the entity's port is not known (has not been
 *	resolved)
 *  
 */
CFN_EXPORT SInt32 
CFNetServiceGetPortNumber(CFNetServiceRef theService) CF_AVAILABLE(10_5, 2_0);



/*
 *  CFNetServiceGetAddressing()
 *  
 *  Discussion:
 *	Query a Network Service for its addressing.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The function gets the data in a thread-safe manner, but the
 *	resulting data is not safe.  Since it is returned as a matter of
 *	a get opposed to a copy, the data is not safe if the service is
 *	being altered from another thread.
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The Network Service to be queried.  Must be non-NULL.
 *  
 *  Result:
 *	Returns NULL if the entity's addressing is not known (has not
 *	been resolved).  The array will contain a CFDataRef for each
 *	address resolved.  Each CFDataRef contains a struct sockaddr
 *	representing the address of the service.
 *  
 */
CFN_EXPORT __nullable CFArrayRef
CFNetServiceGetAddressing(CFNetServiceRef theService) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFNetServiceGetTXTData()
 *  
 *  Discussion:
 *	Query a Network Service for its TXT record contents.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The function gets the data in a thread-safe manner, but the
 *	resulting data is not safe.  Since it is returned as a matter of
 *	a get opposed to a copy, the data is not safe if the service is
 *	being altered from another thread.
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The Network Service to be queried.  Must be non-NULL.
 *  
 *  Result:
 *	Returns NULL if the entity's TXT is not known (has not been
 *	resolved).  The result will contain the contents of the TXT
 *	record.  This is suitable to pass to
 *	CFNetServiceCreateDictionaryWithTXTData.
 *  
 */
CFN_EXPORT __nullable CFDataRef
CFNetServiceGetTXTData(CFNetServiceRef theService) CF_AVAILABLE(10_4, 2_0);



/*
 *  CFNetServiceSetTXTData()
 *  
 *  Discussion:
 *	Sets the TXT record for the service.  If the service is currently
 *	registered on the network, the record will be broadcast.  Setting
 *	the TXT record on a resolving service is not allowed.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The Network Service to receive the new record.  Must be
 *	  non-NULL.
 *	
 *	txtRecord:
 *	  The contents of the TXT record.  This should not exceed a
 *	  length of 1450 bytes.
 *  
 */
CFN_EXPORT Boolean 
CFNetServiceSetTXTData(CFNetServiceRef theService, CFDataRef txtRecord) CF_AVAILABLE(10_4, 2_0);



/*
 *  CFNetServiceCreateDictionaryWithTXTData()
 *  
 *  Discussion:
 *	Parses the given TXT record data into a set of key/value pairs as
 *	a CFDictionary where keys are CFStringRefs and values are
 *	CFDataRefs.  If the given record can not be parsed, NULL will be
 *	returned.  READ THE COMMENTS FOR
 *	CFNetServiceCreateTXTDataWithDictionary TO FULLY UNDERSTAND THE
 *	USE AND RESULTS OF THIS FUNCTION.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  CFAllocatorRef to be used for the creation of the result.
 *	
 *	txtRecord:
 *	  The TXT record data as returned by CFNetServiceGetInfo.
 *  
 *  Result:
 *	CFDictionaryRef containing the key/value pairs parsed from the
 *	record. It will return NULL if the record could not be parsed. 
 *	Keys in the dictionary are CFStringRef's.  Values are CFDataRef's.
 *  
 */
CFN_EXPORT __nullable CFDictionaryRef
CFNetServiceCreateDictionaryWithTXTData(CFAllocatorRef __nullable alloc, CFDataRef txtRecord) CF_AVAILABLE(10_4, 2_0);



/*
 *  CFNetServiceCreateTXTDataWithDictionary()
 *  
 *  Discussion:
 *	Flattens a set of key/value pairs into a CFDataRef suitable to
 *	pass into CFNetServiceSetTXTData.  This function will properly
 *	format the data for TXT record usage.  THIS IS NOT A GENERAL
 *	CFDictionaryRef FLATTENING ROUTINE.  CFDictionaryRef keys should
 *	be CFStringRef's and values should be CFDataRef's.  For
 *	convenience, values that are CFStringRef's will be converted to
 *	CFDataRef's representing the flattened UTF-8 bytes of the string.
 *	 The types of the values are not encoded in the CFDataRef's,
 *	therefore CFStringRef's will be flattened into CFDataRef's, and
 *	they will come out of CFNetServiceCreateDictionaryWithTXTData as
 *	CFDataRef's.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  CFAllocatorRef to be used for the creation of the result.
 *	
 *	keyValuePairs:
 *	  CFDictionaryRef containing keys and values to be placed into
 *	  the TXT record.  The keys must be CFStringRef's.  The values
 *	  should be CFDataRef's (CFStringRef's are permitted for
 *	  convenience).  Any other types will cause a failure.  The
 *	  length of a key and its value should not exceed 255.
 *  
 *  Result:
 *	CFDataRef containing the flattened form of the keys and values. 
 *	If the dictionary could not be flattend, NULL will be returned.
 *  
 */
CFN_EXPORT __nullable CFDataRef
CFNetServiceCreateTXTDataWithDictionary(CFAllocatorRef __nullable alloc, CFDictionaryRef keyValuePairs) CF_AVAILABLE(10_4, 2_0);



/*
 *  CFNetServiceSetClient()
 *  
 *  Discussion:
 *	Sets up the service to be used in asynchronous mode. 
 *	Notification of registration failure or resolution completion
 *	will occur through the given callback.  Once the client is set,
 *	the service must be scheduled on a runloop. The client callback
 *	will be triggered via one of the scheduled run loops; It is the
 *	caller's responsibility to ensure that at least one of the
 *	scheduled run loops is being run.  This call must be performed
 *	before calling CFNetServiceRegister or CFNetServiceResolve,
 *	otherwise it will return FALSE.  TRUE will be returned if the
 *	client could be set.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The service to set up for asynchronous mode.  Must be non-NULL.
 *	
 *	clientCB:
 *	  Function pointer will be called upon registration failure or
 *	  upon resolution completion.  In the case of resolution, this
 *	  callback may be called multiple times if there is more than one
 *	  address for a service.  Passing NULL will remove the client
 *	  from the entity and cancel any outstanding activity.
 *	
 *	clientContext:
 *	  Client contextual information to be used when calling clientCB.
 *	  Passing NULL will remove the client from the entity and cancel
 *	  any outstanding activity.
 *  
 *  Result:
 *	Returns FALSE if the client could not be set, TRUE otherwise.
 *  
 */
CFN_EXPORT Boolean 
CFNetServiceSetClient(CFNetServiceRef theService, CFNetServiceClientCallBack __nullable clientCB, CFNetServiceClientContext * __nullable clientContext) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFNetServiceScheduleWithRunLoop()
 *  
 *  Discussion:
 *	Schedule the given service on the given run loop and mode.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The service which is set up for asynchronous mode. Must be
 *	  non-NULL.
 *	
 *	runLoop:
 *	  A reference to a runloop on which the service should be
 *	  scheduled. Must be non-NULL.
 *	
 *	runLoopMode:
 *	  The mode on which to schedule the service.  Must be non-NULL.
 *  
 */
CFN_EXPORT void 
CFNetServiceScheduleWithRunLoop(CFNetServiceRef theService, CFRunLoopRef runLoop, CFStringRef runLoopMode) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFNetServiceUnscheduleFromRunLoop()
 *  
 *  Discussion:
 *	Unschedule the given service from the given run loop and mode.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The service which is set up for asynchronous mode.  Must be
 *	  non-NULL.
 *	
 *	runLoop:
 *	  A reference to a runloop from which the service should be
 *	  unscheduled.  Must be non-NULL.
 *	
 *	runLoopMode:
 *	  The mode from which to unschedule the service.  Must be
 *	  non-NULL.
 *  
 */
CFN_EXPORT void 
CFNetServiceUnscheduleFromRunLoop(CFNetServiceRef theService, CFRunLoopRef runLoop, CFStringRef runLoopMode) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFNetServiceMonitorCreate()
 *  
 *  Discussion:
 *	Creates an instance of an object suitable for watching for
 *	CFNetService record changes on the network.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  The CFAllocator which should be used to allocate memory for the
 *	  monitor and its storage for values. If this reference is not a
 *	  valid CFAllocator, the behavior is undefined.
 *	
 *	theService:
 *	  The CFNetService to be monitored for record changes.
 *	
 *	clientCB:
 *	  Function pointer that will be called as record changes occur. 
 *	  Must be non-NULL.
 *	
 *	clientContext:
 *	  Client contextual information to be used when calling clientCB.
 *	   Must be non-NULL.
 *  
 *  Result:
 *	Returns a new instance of a CFNetServiceMonitor, or NULL if the
 *	object could not be created.
 *  
 */
CFN_EXPORT CFNetServiceMonitorRef 
CFNetServiceMonitorCreate(
  CFAllocatorRef __nullable          alloc,
  CFNetServiceRef                    theService,
  CFNetServiceMonitorClientCallBack  clientCB,
  CFNetServiceClientContext *        clientContext) CF_AVAILABLE(10_4, 2_0);



/*
 *  CFNetServiceMonitorInvalidate()
 *  
 *  Discussion:
 *	Invalidates the given monitor object so that it may no longer be
 *	scheduled and callback never be called.  This will also stop any
 *	monitors currently in progress.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	monitor:
 *	  CFNetServiceMonitor to invalidate.  Must be non-NULL.
 *  
 */
CFN_EXPORT void 
CFNetServiceMonitorInvalidate(CFNetServiceMonitorRef monitor) CF_AVAILABLE(10_4, 2_0);



/*
 *  CFNetServiceMonitorStart()
 *  
 *  Discussion:
 *	Starts monitoring for record changes on a service.  It watches
 *	for changes of the given record type.  If there is already an
 *	outstanding monitor, it will return FALSE.  In synchronous mode,
 *	this call blocks until the monitor is stopped. It will return
 *	FALSE if there is an error performing the monitor or if there is
 *	some other error.  It will return TRUE otherwise.  In
 *	asynchronous mode, this call will return TRUE or FALSE depending
 *	if the underlying network query could be instantiated.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	monitor:
 *	  CFNetServiceMonitor to perform the watch.
 *	
 *	recordType:
 *	  CFNetServiceMonitorType indicating the record type to watch.
 *	
 *	error:
 *	  A reference to an error struct which will be set to the error
 *	  and domain of the error should one occur.  If the value of
 *	  error is not desired, set to NULL.
 *  
 *  Result:
 *	Returns FALSE if an error occurs during a synchronous monitor or
 *	if the monitor could not start.  It returns TRUE otherwise.
 *  
 */
CFN_EXPORT Boolean 
CFNetServiceMonitorStart(CFNetServiceMonitorRef monitor, CFNetServiceMonitorType recordType, CFStreamError * __nullable error) CF_AVAILABLE(10_4, 2_0);



/*
 *  CFNetServiceMonitorStop()
 *  
 *  Discussion:
 *	Stops an outstanding monitor.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	monitor:
 *	  CFNetServiceMonitor with an active monitor.  Must be non-NULL.
 *	
 *	error:
 *	  Error value to be returned in "error" in
 *	  CFNetServiceMonitorStart if monitor is being performed in
 *	  synchronous mode.  In this case, a non-zero of the error field
 *	  of the struct will cause CFNetServiceMonitorStart to return
 *	  FALSE.  In asynchronous mode, the client call back will be
 *	  called with this error. Can be NULL.
 *  
 */
CFN_EXPORT void 
CFNetServiceMonitorStop(CFNetServiceMonitorRef monitor, CFStreamError * __nullable error) CF_AVAILABLE(10_4, 2_0);



/*
 *  CFNetServiceMonitorScheduleWithRunLoop()
 *  
 *  Discussion:
 *	Schedules the monitor on a run loop and mode.  Use this to place
 *	the given monitor into asynchronous mode.  The client callback
 *	will be triggered via one of the scheduled run loops; It is the
 *	caller's responsibility to ensure that at least one of the
 *	scheduled run loops is being run.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	monitor:
 *	  CFNetServiceMonitor to schedule.  Must be non-NULL.
 *	
 *	runLoop:
 *	  A reference to a runloop on which the monitor should be
 *	  scheduled.  Must be non-NULL.
 *	
 *	runLoopMode:
 *	  The mode on which to schedule the monitor.  Must be non-NULL.
 *  
 */
CFN_EXPORT void 
CFNetServiceMonitorScheduleWithRunLoop(CFNetServiceMonitorRef monitor, CFRunLoopRef runLoop, CFStringRef runLoopMode) CF_AVAILABLE(10_4, 2_0);



/*
 *  CFNetServiceMonitorUnscheduleFromRunLoop()
 *  
 *  Discussion:
 *	Unschedules the browser from a run loop and mode.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	monitor:
 *	  CFNetServiceMonitor to unschedule.  Must be non-NULL.
 *	
 *	runLoop:
 *	  A reference to a runloop from which the monitor should be
 *	  unscheduled. Must be non-NULL.
 *	
 *	runLoopMode:
 *	  The mode from which to unschedule the monitor.  Must be
 *	  non-NULL.
 *  
 */
CFN_EXPORT void 
CFNetServiceMonitorUnscheduleFromRunLoop(CFNetServiceMonitorRef monitor, CFRunLoopRef runLoop, CFStringRef runLoopMode) CF_AVAILABLE(10_4, 2_0);



/*
 *  CFNetServiceBrowserCreate()
 *  
 *  Discussion:
 *	Creates an instance of a browser object.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  The CFAllocator which should be used to allocate memory for the
 *	  browser and its storage for values. If this reference is not a
 *	  valid CFAllocator, the behavior is undefined.
 *	
 *	clientCB:
 *	  Function pointer that will be called as domains or services are
 *	  found on the network.  Must be non-NULL.
 *	
 *	clientContext:
 *	  Client contextual information to be used when calling clientCB.
 *	  Must be non-NULL.
 *  
 *  Result:
 *	Returns a new instance of a browser, or NULL if the instance
 *	could not be created.
 *  
 */
CFN_EXPORT CFNetServiceBrowserRef 
CFNetServiceBrowserCreate(CFAllocatorRef __nullable alloc, CFNetServiceBrowserClientCallBack clientCB, CFNetServiceClientContext *clientContext) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFNetServiceBrowserInvalidate()
 *  
 *  Discussion:
 *	Invalidates the given browser object so that it may no longer be
 *	scheduled and callback never be called.  This will also stop any
 *	searches currently in progress.
 *  
 *  Parameters:
 *	
 *	browser:
 *	  Network Service Browser to invalidate.  Must be non-NULL.
 *  
 */
CFN_EXPORT void 
CFNetServiceBrowserInvalidate(CFNetServiceBrowserRef browser) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFNetServiceBrowserSearchForDomains()
 *  
 *  Discussion:
 *	Starts a search for domains.  The browser will either try to find
 *	"Browse" domains or will search for "Registration" domains.  If
 *	there is already an outstanding search, it will return FALSE.  In
 *	syncronous mode, this call blocks until the search is stopped. 
 *	It will return FALSE if there is an error performing the search.
 *	It will return TRUE otherwise.  In asynchronous mode, this call
 *	will return TRUE or FALSE depending if the underlying network
 *	search could be started.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	browser:
 *	  Network Service Browser to perform the search.  Must be
 *	  non-NULL.
 *	
 *	registrationDomains:
 *	  FALSE if "Browse" domains are to be discovered. TRUE if only
 *	  "Registration" domains are to be discovered.
 *	
 *	error:
 *	  A reference to an error struct which will be set to the error
 *	  and domain of the error should one occur.  If the value of
 *	  error is not desired, set to NULL.
 *  
 *  Result:
 *	Returns FALSE if an error occurs during a synchronous search or
 *	if the search could not start.  It returns TRUE otherwise.
 *  
 */
CFN_EXPORT Boolean 
CFNetServiceBrowserSearchForDomains(CFNetServiceBrowserRef browser, Boolean registrationDomains, CFStreamError * __nullable error) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFNetServiceBrowserSearchForServices()
 *  
 *  Discussion:
 *	Starts a search for a service type on the given domain.  If there
 *	is already an outstanding search, it will return FALSE.  In
 *	syncronous mode, this call blocks until the search is stopped. 
 *	It will return FALSE if there is an error performing the search
 *	or if there is some other error.  It will return TRUE otherwise.
 *	In asynchronous mode, this call will return TRUE or FALSE
 *	depending if the underlying network search could be instantiated.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	browser:
 *	  Network Service Browser to perform the search.  Must be
 *	  non-NULL.
 *	
 *	domain:
 *	  Network domain to search in order to find the service.  Must be
 *	  non-NULL.
 *	
 *	serviceType:
 *	  Service type for which to search.  Must be non-NULL.
 *	
 *	error:
 *	  A reference to an error struct which will be set to the error
 *	  and domain of the error should one occur.  If the value of
 *	  error is not desired, set to NULL.
 *  
 *  Result:
 *	Returns FALSE if an error occurs during a synchronous search or
 *	if the search could not start.  It returns TRUE otherwise.
 *  
 */
CFN_EXPORT Boolean 
CFNetServiceBrowserSearchForServices(CFNetServiceBrowserRef browser, CFStringRef domain, CFStringRef serviceType, CFStreamError * __nullable error) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFNetServiceBrowserStopSearch()
 *  
 *  Discussion:
 *	Stops an outstanding browser search.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	browser:
 *	  Network Service Browser performing the search.  Must be
 *	  non-NULL.
 *	
 *	error:
 *	  Error value to be returned in "error" in
 *	  CFNetServiceBrowserStartServiceSearch if search is being
 *	  performed in synchronous mode.  In this case, a non-zero of the
 *	  error field of the struct will cause
 *	  CFNetServiceBrowserStartServiceSearch to return FALSE. In
 *	  asynchronous mode, the client call back will be called with
 *	  this error. Can be NULL.
 *  
 */
CFN_EXPORT void 
CFNetServiceBrowserStopSearch(CFNetServiceBrowserRef browser, CFStreamError * __nullable error) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFNetServiceBrowserScheduleWithRunLoop()
 *  
 *  Discussion:
 *	Schedules the browser on a run loop and mode.  Use this to place
 *	the given browser into asynchronous mode.  The client callback
 *	will be triggered via one of the scheduled run loops; It is the
 *	caller's responsibility to ensure that at least one of the
 *	scheduled run loops is being run.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	browser:
 *	  Network Service Browser to schedule.  Must be non-NULL.
 *	
 *	runLoop:
 *	  A reference to a runloop on which the browser should be
 *	  scheduled.  Must be non-NULL.
 *	
 *	runLoopMode:
 *	  The mode on which to schedule the browser.  Must be non-NULL.
 *  
 */
CFN_EXPORT void 
CFNetServiceBrowserScheduleWithRunLoop(CFNetServiceBrowserRef browser, CFRunLoopRef runLoop, CFStringRef runLoopMode) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFNetServiceBrowserUnscheduleFromRunLoop()
 *  
 *  Discussion:
 *	Unschedules the browser from a run loop and mode.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	browser:
 *	  Network Service Browser to unschedule.  Must be non-NULL.
 *	
 *	runLoop:
 *	  A reference to a runloop from which the browser should be
 *	  unscheduled. Must be non-NULL.
 *	
 *	runLoopMode:
 *	  The mode from which to unschedule the browser.  Must be
 *	  non-NULL.
 *  
 */
CFN_EXPORT void 
CFNetServiceBrowserUnscheduleFromRunLoop(CFNetServiceBrowserRef browser, CFRunLoopRef runLoop, CFStringRef runLoopMode) CF_AVAILABLE(10_2, 2_0);


#ifdef __MACH__
/*
 *  CFNetServiceRegister()   *** DEPRECATED ***
 *  
 *  Discussion:
 *	Registers the entity on the network.  This requires that the
 *	service has a domain, a type, a name, and a port.  The service is
 *	registered on the network until this function returns or is
 *	cancelled by calling CFNetServiceCancel.  In synchronous mode,
 *	this function will block until there is an error or it is
 *	cancelled from another thread.  In asynchronous mode, this
 *	function returns immediately and the underlying network
 *	registration process will start. 
 *	
 *	As a result of new, better performing API's in Service Discovery,
 *	users should now call CFNetServiceRegisterWithOptions.  Using the
 *	new calls will allow your application to perform better on the
 *	network.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The Network Service to register on the network.  Must be
 *	  non-NULL.
 *	
 *	error:
 *	  A reference to an error struct which will be set to the error
 *	  and domain of the error should one occur.  If the value of
 *	  error is not desired, set to NULL.
 *  
 *  Result:
 *	Returns FALSE if domain, type, name or port is NULL.  In
 *	synchronous mode, it will always return FALSE as a result of the
 *	error or the cancellation.  In asynchronous mode, it will return
 *	TRUE if the registration process could start.
 *  
 */
CFN_EXPORT Boolean 
CFNetServiceRegister(CFNetServiceRef theService, CFStreamError * __nullable error) CF_DEPRECATED(10_2, 10_4, NA, NA);


/*
 *  CFNetServiceResolve()   *** DEPRECATED ***
 *  
 *  Discussion:
 *	Resolves the addressing for the given service.  This requires
 *	that the service has a domain, a type, and a name.  The service
 *	is  resolved on the network until this function returns or is
 *	cancelled by calling CFNetServiceCancel. In synchronous mode,
 *	this function will block until there is an error or it is
 *	cancelled from another thread.  In asynchronous mode, this
 *	function returns immediately and the underlying network
 *	resolution process will start. 
 *	
 *	As a result of new, better performing API's in Service Discovery,
 *	users should now call CFNetServiceResolveWithTimeout.  If needing
 *	to monitor TXT record changes, users should use the new
 *	CFNetServiceMonitor object. Using the new calls will allow your
 *	application to perform better on the network.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The Network Service to resolve on the network.  Must be
 *	  non-NULL.
 *	
 *	error:
 *	  A reference to an error struct which will be set to the error
 *	  and domain of the error should one occur.  If the value of
 *	  error is not desired, set to NULL.
 *  
 *  Result:
 *	Returns FALSE if domain, type, or name is NULL.  In synchronous
 *	mode, it will return FALSE as a result of an error or a
 *	cancellation.  It will return TRUE if the resolution does
 *	succeed.  In asynchronous mode, it will return TRUE if the
 *	resolution process could start.
 *  
 */
CFN_EXPORT Boolean 
CFNetServiceResolve(CFNetServiceRef theService, CFStreamError * __nullable error) CF_DEPRECATED(10_2, 10_4, NA, NA);



/*
 *  CFNetServiceGetProtocolSpecificInformation()   *** DEPRECATED ***
 *  
 *  Discussion:
 *	Query a Network Service for its protocol specific information.
 *	
 *	
 *	As a result of new, better performing API's in Service Discovery,
 *	users should now call CFNetServiceGetTXTData.  If needing to
 *	monitor TXT record changes, users should use the new
 *	CFNetServiceMonitor object. Using the new calls will allow your
 *	application to perform better on the network.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The function gets the data in a thread-safe manner, but the
 *	resulting data is not safe.  Since it is returned as a matter of
 *	a get opposed to a copy, the data is not safe if the service is
 *	being altered from another thread.
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The Network Service to be queried.  Must be non-NULL.
 *  
 *  Result:
 *	Returns NULL if a resolve has not been performed or if
 *	CFNetServiceSetProtocolSpecificInformation has not been called. 
 *	It will return a CFStringRef containing the specific information
 *	if there is some.
 *  
 */
CFN_EXPORT __nullable CFStringRef
CFNetServiceGetProtocolSpecificInformation(CFNetServiceRef theService) CF_DEPRECATED(10_2, 10_4, NA, NA);



/*
 *  CFNetServiceSetProtocolSpecificInformation()   *** DEPRECATED ***
 *  
 *  Discussion:
 *	Set a Network Service's protocol specific information. 
 *	
 *	As a result of new, better performing API's in Service Discovery,
 *	users should now call CFNetServiceSetTXTData.  Using the new
 *	calls will allow your application to perform better on the
 *	network.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	theService:
 *	  The Network Service to be queried.  Must be non-NULL.
 *	
 *	theInfo:
 *	  The protocol specific information to be added.  Pass NULL to
 *	  remove the information from the service.
 *  
 */
CFN_EXPORT void 
CFNetServiceSetProtocolSpecificInformation(CFNetServiceRef theService, CFStringRef __nullable theInfo) CF_DEPRECATED(10_2, 10_4, NA, NA);


#endif  /* defined(__MACH__) */


#pragma pack(pop)

CF_ASSUME_NONNULL_END
CF_EXTERN_C_END

#endif /* __CFNETSERVICES__ */

// ==========  CFNetwork.framework/Headers/CFNetwork.h
/*
	File:	   CFNetwork/CFNetwork.h
 
	Contains:   CoreFoundation Network header
 
	Copyright:  Copyright (c) 2001-2008 Apple Inc. All rights reserved.
 
	Bugs?:	  For bug reports, consult the following page on
				 the World Wide Web:
 
					 http://developer.apple.com/bugreporter/
 
*/
#ifndef __CFNETWORK__
#define __CFNETWORK__

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif


#ifndef __CFNETWORKDEFS__
#include <CFNetwork/CFNetworkDefs.h>
#endif

#ifndef __CFNETWORKERRORS__
#include <CFNetwork/CFNetworkErrors.h>
#endif

#ifndef __CFSOCKETSTREAM__
#include <CFNetwork/CFSocketStream.h>
#endif

#ifndef __CFFTPSTREAM__
#include <CFNetwork/CFFTPStream.h>
#endif

#ifndef __CFHOST__
#include <CFNetwork/CFHost.h>
#endif

#ifndef __CFHTTPMESSAGE__
#include <CFNetwork/CFHTTPMessage.h>
#endif

#ifndef __CFHTTPSTREAM__
#include <CFNetwork/CFHTTPStream.h>
#endif

#ifndef __CFHTTPAUTHENTICATION__
#include <CFNetwork/CFHTTPAuthentication.h>
#endif

#ifndef __CFNETDIAGNOSTICS__
#include <CFNetwork/CFNetDiagnostics.h>
#endif

#ifndef __CFNETSERVICES__
#include <CFNetwork/CFNetServices.h>
#endif

#ifndef __CFPROXYSUPPORT__
#include <CFNetwork/CFProxySupport.h>
#endif


#endif /* __CFNETWORK__ */

// ==========  CFNetwork.framework/Headers/CFSocketStream.h
/*
	 File:	   CFNetwork/CFSocketStream.h
 
	 Contains:   CoreFoundation Network socket streams header
 
	 Copyright:  Copyright (c) 2001-2013 Apple Inc. All rights reserved.
 
	 Bugs?:	  For bug reports, consult the following page on
				 the World Wide Web:
 
					 http://developer.apple.com/bugreporter/
 
*/
#ifndef __CFSOCKETSTREAM__
#define __CFSOCKETSTREAM__

#ifndef __CFNETWORKDEFS__
#include <CFNetwork/CFNetworkDefs.h>
#endif

#ifndef __CFSTREAM__
#include <CoreFoundation/CFStream.h>
#endif

#ifndef __CFHOST__
#include <CFNetwork/CFHost.h>
#endif

#ifndef __CFNETSERVICES__
#include <CFNetwork/CFNetServices.h>
#endif



#if PRAGMA_ONCE
#pragma once
#endif

CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

#if PRAGMA_ENUM_ALWAYSINT
	#pragma enumsalwaysint on
#endif

/*
 *  kCFStreamPropertySSLContext 
 *
 * The SSLContextRef used for both read and write operations on a
 * CFSocketStream.
 *
 * CFReadStreamCopyProperty or CFWriteStreamCopyProperty return an
 * appropriately reference counted SSLContextRef.  If the stream has
 * not yet been opened, this SSLContext may be configured directly
 * using the appropriate SecureTransport APIs.
 *
 * CFReadStreamSetProperty or CFWriteStreamSetProperty will allow you
 * to specify an SSLContextRef for a stream.  If the stream has not
 * been opened, the SSLContextRef will replace any existing
 * SSLContextRef and be used in the initial stream handshake.  If the
 * stream has been opened without SSL enabled, setting this property
 * will initiate an SSL handshake over the existing socket.
 *
 * If an SSL settings dictionary was set via
 * kCFStreamPropertySSLSettings, a SSLContextRef is created internally
 * and configured as per the dictionary.  However, if an SSLContextRef
 * is set after this, its configuration will take precedence over the
 * previously configured context.
 *
 * Reconfiguring an SSLContext after the stream it is bound to has
 * opened is unsupported.
 *
 */
CFN_EXPORT const CFStringRef kCFStreamPropertySSLContext CF_AVAILABLE(10_9, 5_0);

/*
 *  kCFStreamPropertySSLPeerTrust
 *  
 *  Discussion:
 *	Stream property value for copy operations.  Returns a SecTrustRef
 *	which was a result of the SSL handshake.  This property is not valid before
 *  a stream is opened.  See Security/SecTrust.h for more information.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertySSLPeerTrust CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFStreamSSLValidatesCertificateChain
 *  
 *  Discussion:
 *	Security property key for kCFStreamPropertySSLSettings. 
 *	CFBooleanRef indicating whether the certificate chain should be
 *	validated or not.  The value is kCFBooleanTrue by default (not
 *	set).
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamSSLValidatesCertificateChain CF_AVAILABLE(10_4, 2_0);
	
/*
 *  kCFStreamPropertySSLSettings
 *  
 *  Discussion:
 *	Stream property key for set operations.  CFDictionaryRef filled
 *	with different security settings.  By default, there are no
 *	security settings.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertySSLSettings CF_AVAILABLE(10_4, 2_0);

/*
 *  kCFStreamSSLLevel
 *  
 *  Discussion:
 *	Security property key for kCFStreamPropertySSLSettings. 
 *	CFStringRef being one of the security levels.  The value is
 *	kCFStreamSocketSecurityLevelNegotiatedSSL by default (not set).
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamSSLLevel CF_AVAILABLE(10_4, 2_0);

/*
 *  kCFStreamSSLPeerName
 *  
 *  Discussion:
 *	Security property key for kCFStreamPropertySSLSettings. 
 *	CFStringRef overriding the name used for certificate
 *	verification.  Set to kCFNull to prevent name verification. 
 *	Default is the host name with which the streams were created.  If
 *	no host name was used, no peer name will be used.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamSSLPeerName CF_AVAILABLE(10_4, 2_0);

/*
 *  kCFStreamSSLCertificates
 *  
 *  Discussion:
 *	Security property key for kCFStreamPropertySSLSettings. 
 *	CFArrayRef of SecCertificateRefs, except for index [0], which is
 *	a SecIdentityRef.  See SSLSetCertificate in
 *	Security/SecureTransport.h for more information.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamSSLCertificates CF_AVAILABLE(10_4, 2_0);

/*
 *  kCFStreamSSLIsServer
 *  
 *  Discussion:
 *	Security property key for kCFStreamPropertySSLSettings. 
 *	CFBooleanRef indicating whether the connection is to act as a
 *	server in the SSL process or not.  The value is kCFBooleanFalse
 *	by default (not set).  If set to kCFBooleanTrue, there must be a
 *	valid value for the kCFStreamSSLCertificates key too.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamSSLIsServer CF_AVAILABLE(10_4, 2_0);

	
/*	kCFStreamNetworkServiceType
 *
 * Discussion:
 * Property key to specify the type of service for the stream.  This
 * allows the system to properly handle the request with respect to
 * routing, suspension behavior and other networking related attributes
 * appropriate for the given service type.  The service types supported
 * are documented below.  Most streams should not need to set this
 * property.
 */
CFN_EXPORT const CFStringRef kCFStreamNetworkServiceType CF_AVAILABLE(10_7, 4_0);

/* supported network service types: */
CFN_EXPORT const CFStringRef kCFStreamNetworkServiceTypeVideo      CF_AVAILABLE(10_7, 5_0);   // interactive video
CFN_EXPORT const CFStringRef kCFStreamNetworkServiceTypeVoice      CF_AVAILABLE(10_7, 5_0);   // interactive voice data
CFN_EXPORT const CFStringRef kCFStreamNetworkServiceTypeBackground CF_AVAILABLE(10_7, 5_0);   // background
CFN_EXPORT const CFStringRef kCFStreamNetworkServiceTypeResponsiveData __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0); // responsive (time sensitive) data
CFN_EXPORT const CFStringRef kCFStreamNetworkServiceTypeCallSignaling	   CF_AVAILABLE(10_12, 10_0); //Call Signaling

/* deprecated network service type: */
CFN_EXPORT const CFStringRef kCFStreamNetworkServiceTypeVoIP       CF_DEPRECATED(10_7, 10_11, 4_0, 9_0, "use PushKit for VoIP control purposes");   // voice over IP control - this service type is deprecated in favor of using PushKit for VoIP control

/*
 *  kCFStreamPropertyNoCellular
 *  
 *  Discussion:
 *  Stream property value, for both set and copy operations.
 *  The value is a CFBooleanRef which indicates whether the connection
 *  is allowed to use the built-in celluar radios.  A value of kCFBooleanTrue 
 *  disallows use of cellular interfaces.  kCFBooleanFalse (the default)
 *  allows use of cellular interfaces.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyNoCellular CF_AVAILABLE(10_8, 5_0);

/*
 *  kCFStreamPropertyConnectionIsCellular
 *
 *  Discussion:
 *  Stream property key for copy operations.  Returns a CFBooleanRef value
 *  of kCFBooleanTrue if the stream has connected using the built in cellular radios.
 *  It returns kCFBooleanFalse if the stream is conneceted over a non-cellular
 *  interface or has not yet established a connection.
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyConnectionIsCellular CF_AVAILABLE(10_8, 6_0);

/*
 *  kCFStreamErrorDomainWinSock
 *  
 *  Discussion:
 *  WinSock error domain.  On Win32 platforms, networking errors will
 *  come in this domain.  See <winsock2.h> for values.  Note that
 *  non-networking errors, like ENOMEM, will continue to come in the
 *  POSIX domain as on OS X.
 *  
 */
CFN_EXPORT const CFIndex kCFStreamErrorDomainWinSock CF_AVAILABLE(10_5, 2_0);

CF_INLINE
SInt32 CFSocketStreamSOCKSGetErrorSubdomain(const CFStreamError* error) {
	return ((error->error >> 16) & 0x0000FFFF);
}

CF_INLINE
SInt32 CFSocketStreamSOCKSGetError(const CFStreamError* error) {
	return (error->error & 0x0000FFFF);
}

enum {
  kCFStreamErrorSOCKSSubDomainNone = 0,        /* Error code is a general SOCKS error*/
  kCFStreamErrorSOCKSSubDomainVersionCode = 1, /* Error code is the version of SOCKS which the server wishes to use*/
  kCFStreamErrorSOCKS4SubDomainResponse = 2,   /* Error code is the status code returned by the server*/
  kCFStreamErrorSOCKS5SubDomainUserPass = 3,   /* Error code is the status code that the server returned*/
  kCFStreamErrorSOCKS5SubDomainMethod = 4,     /* Error code is the server's desired negotiation method*/
  kCFStreamErrorSOCKS5SubDomainResponse = 5    /* Error code is the response code that the server returned in reply to the connection request*/
};


/* kCFStreamErrorSOCKSSubDomainNone*/
enum {
  kCFStreamErrorSOCKS5BadResponseAddr = 1,
  kCFStreamErrorSOCKS5BadState  = 2,
  kCFStreamErrorSOCKSUnknownClientVersion = 3
};

/* kCFStreamErrorSOCKS4SubDomainResponse*/
enum {
  kCFStreamErrorSOCKS4RequestFailed = 91, /* request rejected or failed */
  kCFStreamErrorSOCKS4IdentdFailed = 92,  /* request rejected because SOCKS server cannot connect to identd on the client */
  kCFStreamErrorSOCKS4IdConflict = 93     /* request rejected because the client program and identd report different user-ids */
};

/* kCFStreamErrorSOCKS5SubDomainMethod*/
enum {
  kSOCKS5NoAcceptableMethod	 = 0xFF  /* other values indicate the server's desired method */
};

/*
 *  kCFStreamPropertyProxyLocalBypass
 *
 *  Discussion:
 *	CFDictionary key for proxy information.  It matches
 *	kSCPropNetProxiesExcludeSimpleHostnames defined in
 *	SCSchemaDefinitions.h.  CFNumber (0 or 1) indicating to bypass
 *	the proxies for simple hostnames (names without dots).
 *
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyProxyLocalBypass CF_AVAILABLE(10_4, 2_0);

/*
 *  kCFStreamPropertySocketRemoteHost
 *  
 *  Discussion:
 *	Stream property key for copy operations. Returns a CFHostRef if
 *	known, otherwise NULL.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertySocketRemoteHost CF_AVAILABLE(10_3, 2_0);


/*
 *  kCFStreamPropertySocketRemoteNetService
 *  
 *  Discussion:
 *	Stream property key for copy operations. Returns a
 *	CFNetServiceRef if known, otherwise NULL.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertySocketRemoteNetService CF_AVAILABLE(10_3, 2_0);

/*
 *  kCFStreamPropertySocketExtendedBackgroundIdleMode
 *
 *  Discussion:
 *	Set this to kCFBooleanTrue to enable extended background idle
 *	mode.  Enabling this mode asks the system to keep the socket open
 *  and delay reclaiming it when the process moves to the background (see
 *  https://developer.apple.com/library/ios/technotes/tn2277/_index.html)
 *  This property must be set before the stream is opened.
 *
 */
CFN_EXPORT const CFStringRef kCFStreamPropertySocketExtendedBackgroundIdleMode CF_AVAILABLE(10_11, 9_0);

/*
 *  CFStreamCreatePairWithSocketToCFHost()
 *  
 *  Discussion:
 *	Given a CFHostRef, this function will create a pair of streams
 *	suitable for connecting to the host.  If there is a failure
 *	during creation, the stream references will be set to NULL.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  The CFAllocator which should be used to allocate memory for the
 *	  streams. If this reference is not a valid CFAllocator, the
 *	  behavior is undefined.
 *	
 *	host:
 *	  A reference to a CFHost to which the streams are desired.  If
 *	  unresolved, the host will be resolved prior to connecting.
 *	
 *	port:
 *	  The port to which the connection should be established.
 *	
 *	readStream:
 *	  A pointer to a CFReadStreamRef which will be set to the new
 *	  read stream instance.  Can be set to NULL if not desired.
 *	
 *	writeStream:
 *	  A pointer to a CFWriteStreamRef which will be set to the new
 *	  write stream instance.  Can be set to NULL if not desired.
 *  
 */
CFN_EXPORT void 
CFStreamCreatePairWithSocketToCFHost(
  CFAllocatorRef      __nullable alloc,
  CFHostRef           host,
  SInt32              port,
  CFReadStreamRef __nullable *   __nullable readStream,
  CFWriteStreamRef __nullable *  __nullable writeStream)            CF_AVAILABLE(10_3, 2_0);


/*
 *  CFStreamCreatePairWithSocketToNetService()
 *  
 *  Discussion:
 *	Given a CFNetService, this function will create a pair of streams
 *	suitable for connecting to the service.  If there is a failure
 *	during creation, the stream references will be set to NULL.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  The CFAllocator which should be used to allocate memory for the
 *	  streams. If this reference is not a valid CFAllocator, the
 *	  behavior is undefined.
 *	
 *	service:
 *	  A reference to a CFNetService to which the streams are desired.
 *	   If unresolved, the service will be resolved prior to
 *	  connecting.
 *	
 *	readStream:
 *	  A pointer to a CFReadStreamRef which will be set to the new
 *	  read stream instance.  Can be set to NULL if not desired.
 *	
 *	writeStream:
 *	  A pointer to a CFWriteStreamRef which will be set to the new
 *	  write stream instance.  Can be set to NULL if not desired.
 *  
 */
CFN_EXPORT void 
CFStreamCreatePairWithSocketToNetService(
  CFAllocatorRef      __nullable alloc,
  CFNetServiceRef     service,
  CFReadStreamRef   __nullable *  __nullable readStream,
  CFWriteStreamRef __nullable *  __nullable writeStream)           CF_AVAILABLE(10_3, 2_0);



/*
 * The following properties are DEPRECATED starting in OS X 10.6 and iOS 4.0.
 *
 * kCFStreamPropertySSLPeerCertificates:
 *         The peer certificates are available as part of the SecTrustRef object.  See <Security/SecTrust.h>
 *
 * kCFStreamSSLAllowsExpiredCertificates:
 * kCFStreamSSLAllowsExpiredRoots:
 * kCFStreamSSLAllowsAnyRoot:
 *        The SSL handshake flags which affect untrusted certificate chain evaluation are deprecated.
 *        Instead, use the single property kCFStreamSSLValidatesCertificateChain to disable certificate
 *        chain checking if the user has decided that it is appropriate to do so.
 */

CFN_EXPORT const CFStringRef kCFStreamPropertySSLPeerCertificates   CF_DEPRECATED(10_4, 10_6, 2_0, 4_0);
CFN_EXPORT const CFStringRef kCFStreamSSLAllowsExpiredCertificates  CF_DEPRECATED(10_4, 10_6, 2_0, 4_0);
CFN_EXPORT const CFStringRef kCFStreamSSLAllowsExpiredRoots         CF_DEPRECATED(10_4, 10_6, 2_0, 4_0);
CFN_EXPORT const CFStringRef kCFStreamSSLAllowsAnyRoot              CF_DEPRECATED(10_4, 10_6, 2_0, 4_0);


#if PRAGMA_ENUM_ALWAYSINT
	#pragma enumsalwaysint reset
#endif

CF_ASSUME_NONNULL_END
CF_EXTERN_C_END

#endif /* __CFSOCKETSTREAM__ */

// ==========  CFNetwork.framework/Headers/CFHTTPAuthentication.h
/*
	 File:	   CFNetwork/CFHTTPAuthentication.h
 
	 Contains:   CoreFoundation Network HTTP authentication header
 
	 Copyright:  Copyright (c) 2001-2013 Apple Inc. All rights reserved.
 
	 Bugs?:	  For bug reports, consult the following page on
				 the World Wide Web:
 
					 http://developer.apple.com/bugreporter/
 
*/
#ifndef __CFHTTPAUTHENTICATION__
#define __CFHTTPAUTHENTICATION__

#ifndef __CFNETWORKDEFS__
#include <CFNetwork/CFNetworkDefs.h>
#endif

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifndef __CFHTTPMESSAGE__
#include <CFNetwork/CFHTTPMessage.h>
#endif



#if PRAGMA_ONCE
#pragma once
#endif

CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/*
 *  CFHTTPAuthenticationRef
 *  
 *  Discussion:
 *	This is the type of a reference to HTTP authentication
 *	information.
 */
typedef struct _CFHTTPAuthentication*   CFHTTPAuthenticationRef;

/*
 *  CFStreamErrorHTTPAuthentication
 *  
 *  Discussion:
 *	Authentication errors which may be returned as a result of trying
 *	to apply authentication to a request.  These errors are in the
 *	kCFStreamErrorDomainHTTP domain.
 */
typedef CF_ENUM(int, CFStreamErrorHTTPAuthentication) {

  /*
   * The type of authentication to be applied to a request is not
   * supported.
   */
  kCFStreamErrorHTTPAuthenticationTypeUnsupported = -1000,

  /*
   * The username was in a format not suitable for applying to the
   * request.
   */
  kCFStreamErrorHTTPAuthenticationBadUserName = -1001,

  /*
   * The password was in a format not suitable for applying to the
   * request.
   */
  kCFStreamErrorHTTPAuthenticationBadPassword = -1002
};


/*
 *  kCFHTTPAuthenticationUsername
 *  
 *  Discussion:
 *	CFDictionary key, for CFHTTPMessageApplyCredentialDictionary. The
 *	username for authentication as a CFString.  Needs to be added if
 *	CFHTTPAuthenticationRequiresUserNameAndPassword returns TRUE.
 *  
 */
CFN_EXPORT const CFStringRef kCFHTTPAuthenticationUsername CF_AVAILABLE(10_4, 2_0);

/*
 *  kCFHTTPAuthenticationPassword
 *  
 *  Discussion:
 *	CFDictionary key, for CFHTTPMessageApplyCredentialDictionary. The
 *	password for authentication as a CFString.  Needs to be added if
 *	CFHTTPAuthenticationRequiresUserNameAndPassword returns TRUE.
 *  
 */
CFN_EXPORT const CFStringRef kCFHTTPAuthenticationPassword CF_AVAILABLE(10_4, 2_0);

/*
 *  kCFHTTPAuthenticationAccountDomain
 *  
 *  Discussion:
 *	CFDictionary key, for CFHTTPMessageApplyCredentialDictionary. The
 *	domain for authentication as a CFString.  Needs to be added if
 *	CFHTTPAuthenticationRequiresAccountDomain returns TRUE.
 *  
 */
CFN_EXPORT const CFStringRef kCFHTTPAuthenticationAccountDomain CF_AVAILABLE(10_4, 2_0);

/*
 *  CFHTTPAuthenticationGetTypeID()
 *  
 *  Discussion:
 *	Returns the type identifier of all CFHTTPAuthentication instances.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 */
CFN_EXPORT CFTypeID 
CFHTTPAuthenticationGetTypeID(void) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFHTTPAuthenticationCreateFromResponse()
 *  
 *  Discussion:
 *	Based on a response of 401 or 407, this function will create a
 *	new authentication object which can be used for adding
 *	credentials to future requests.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The API's to CFHTTPAuthenticationRef are thread-safe so long as
 *	multiple threads are not altering the same
 *	CFHTTPAuthenticationRef at the same time.
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  Allocator to use for creating authentication object
 *	
 *	response:
 *	  Failed response.
 *  
 *  Result:
 *	A freshly created authentication object useful for applying
 *	authentication credentials to new requests.
 *  
 */
CFN_EXPORT CFHTTPAuthenticationRef 
CFHTTPAuthenticationCreateFromResponse(CFAllocatorRef __nullable alloc, CFHTTPMessageRef response) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFHTTPAuthenticationIsValid()
 *  
 *  Discussion:
 *	Returns TRUE if the given authentication information was
 *	instantiated correctly and contains enough information in order
 *	to be applied to a request. If FALSE is returned, the object may
 *	still contain information which is useful to the user, e.g.
 *	unsupported method name.  An invalid object may be queried for
 *	information but may not be applied to a request.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The API's to CFHTTPAuthenticationRef are thread-safe so long as
 *	multiple threads are not altering the same
 *	CFHTTPAuthenticationRef at the same time.
 *  
 *  Parameters:
 *	
 *	auth:
 *	  The authentication information being queried.
 *	
 *	error:
 *	  Reference to a CFStreamError which will be populated in the
 *	  case of an error in creation.  Pass NULL if not interested in
 *	  the failure reason.  The error domain will be
 *	  kCFStreamErrorDomainHTTP, and the error code will be one of
 *	  those defined in CFHTTPStream.h or one of those listed as
 *	  CFStreamErrorHTTPAuthentication.
 *  
 *  Result:
 *	TRUE or FALSE depending on whether the authentication object is
 *	good for applying credentials to further requests.
 *  
 */
CFN_EXPORT Boolean 
CFHTTPAuthenticationIsValid(CFHTTPAuthenticationRef auth, CFStreamError * __nullable error) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFHTTPAuthenticationAppliesToRequest()
 *  
 *  Discussion:
 *	Returns TRUE if the given request requires credentials based upon
 *	the given authentication information.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The API's to CFHTTPAuthenticationRef are thread-safe so long as
 *	multiple threads are not altering the same
 *	CFHTTPAuthenticationRef at the same time.
 *  
 *  Parameters:
 *	
 *	auth:
 *	  The authentication information being queried.
 *	
 *	request:
 *	  The request which is believed to need the given authentication.
 *  
 *  Result:
 *	TRUE if the given authentication information should be applied to
 *	the request, otherwise FALSE is returned.
 *  
 */
CFN_EXPORT Boolean 
CFHTTPAuthenticationAppliesToRequest(CFHTTPAuthenticationRef auth, CFHTTPMessageRef request) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFHTTPAuthenticationRequiresOrderedRequests()
 *  
 *  Discussion:
 *	Some authentication methods require that future requests must be
 *	performed in an ordered manner, so that information from a
 *	response can be added to a following request.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The API's to CFHTTPAuthenticationRef are thread-safe so long as
 *	multiple threads are not altering the same
 *	CFHTTPAuthenticationRef at the same time.
 *  
 *  Parameters:
 *	
 *	auth:
 *	  The authentication information being queried.
 *  
 *  Result:
 *	Returns TRUE if the given authentication method requires ordered
 *	requests.
 *  
 */
CFN_EXPORT Boolean 
CFHTTPAuthenticationRequiresOrderedRequests(CFHTTPAuthenticationRef auth) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFHTTPMessageApplyCredentials()
 *  
 *  Discussion:
 *	Perform the authentication method required on the request using
 *	the given username and password.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The API's to CFHTTPAuthenticationRef are thread-safe so long as
 *	multiple threads are not altering the same
 *	CFHTTPAuthenticationRef at the same time.
 *  
 *  Parameters:
 *	
 *	request:
 *	  The request which is to receive the credentials.
 *	
 *	auth:
 *	  The authentication information for the given request.
 *	
 *	username:
 *	  The username to use for performing the authentication.
 *	
 *	password:
 *	  The password to use for performing the authentication.
 *	
 *	error:
 *	  Reference to a CFStreamError which will be populated with the
 *	  error information should one occurr during the application of
 *	  the credentials. Pass NULL if not interested in the failure
 *	  reason.  The error domain will be kCFStreamErrorDomainHTTP, and
 *	  the error code will be one of those define in CFHTTPStream.h or
 *	  one of those listed as CFStreamErrorHTTPAuthentication.
 *  
 *  Result:
 *	TRUE will be returned if the application of the credentials to
 *	the request was successful, otherwise FALSE is returned.
 *  
 */
CFN_EXPORT Boolean 
CFHTTPMessageApplyCredentials(
  CFHTTPMessageRef				request,
  CFHTTPAuthenticationRef		auth,
  CFStringRef       __nullable	username,
  CFStringRef       __nullable	password,
  CFStreamError *   __nullable	error)          CF_AVAILABLE(10_2, 2_0);



/*
 *  CFHTTPMessageApplyCredentialDictionary()
 *  
 *  Discussion:
 *	Perform the authentication method required on the request using
 *	the given credential information.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The API's to CFHTTPAuthenticationRef are thread-safe so long as
 *	multiple threads are not altering the same
 *	CFHTTPAuthenticationRef at the same time.
 *  
 *  Parameters:
 *	
 *	request:
 *	  The request which is to receive the credentials.
 *	
 *	auth:
 *	  The authentication information for the given request.
 *	
 *	dict:
 *	  A dictionary containing credentials to be applied to the
 *	  request.  Valid keys are declared above.
 *	
 *	error:
 *	  Reference to a CFStreamError which will be populated with the
 *	  error information should one occurr during the application of
 *	  the credentials. Pass NULL if not interested in the failure
 *	  reason.  The error domain will be kCFStreamErrorDomainHTTP, and
 *	  the error code will be one of those define in CFHTTPStream.h or
 *	  one of those listed as CFStreamErrorHTTPAuthentication.
 *  
 *  Result:
 *	TRUE will be returned if the application of the credentials to
 *	the request was successful, otherwise FALSE is returned.
 *  
 */
CFN_EXPORT Boolean 
CFHTTPMessageApplyCredentialDictionary(
  CFHTTPMessageRef          request,
  CFHTTPAuthenticationRef   auth,
  CFDictionaryRef           dict,
  CFStreamError *    __nullable  error)          CF_AVAILABLE(10_4, 2_0);



/*
 *  CFHTTPAuthenticationCopyRealm()
 *  
 *  Discussion:
 *	Some authentication techniques provide for namespaces on top of
 *	domains. This call will return the authentication information's
 *	namespace if there is one, otherwise it will return NULL.  This
 *	namespace is usually used for prompting the application user for
 *	a name and password.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The API's to CFHTTPAuthenticationRef are thread-safe so long as
 *	multiple threads are not altering the same
 *	CFHTTPAuthenticationRef at the same time.
 *  
 *  Parameters:
 *	
 *	auth:
 *	  The authentication information being queried.
 *  
 *  Result:
 *	This call will return the authentication information's namespace
 *	if there is one, otherwise it will return NULL.
 *  
 */
CFN_EXPORT CFStringRef 
CFHTTPAuthenticationCopyRealm(CFHTTPAuthenticationRef auth) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFHTTPAuthenticationCopyDomains()
 *  
 *  Discussion:
 *	Returns a list of domain URL's on which the given authentication
 *	should be applied. This function is provided mostly for
 *	informational purposes. CFHTTPAuthenticationAppliesToRequest
 *	should be used in order to check whether a request requires the
 *	authentication.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The API's to CFHTTPAuthenticationRef are thread-safe so long as
 *	multiple threads are not altering the same
 *	CFHTTPAuthenticationRef at the same time.
 *  
 *  Parameters:
 *	
 *	auth:
 *	  The authentication information being queried.
 *  
 *  Result:
 *	Returns a list of domain URL's on which the given authentication
 *	should be applied.
 *  
 */
CFN_EXPORT CFArrayRef 
CFHTTPAuthenticationCopyDomains(CFHTTPAuthenticationRef auth) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFHTTPAuthenticationCopyMethod()
 *  
 *  Discussion:
 *	Returns the method of authentication which will be performed when
 *	applying credentials.  The strongest method of authentication
 *	will be chosen in the case of multiple choices.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The API's to CFHTTPAuthenticationRef are thread-safe so long as
 *	multiple threads are not altering the same
 *	CFHTTPAuthenticationRef at the same time.
 *  
 *  Parameters:
 *	
 *	auth:
 *	  The authentication information being queried.
 *  
 *  Result:
 *	Returns the method of authentication which will be performed when
 *	applying credentials.
 *  
 */
CFN_EXPORT CFStringRef 
CFHTTPAuthenticationCopyMethod(CFHTTPAuthenticationRef auth) CF_AVAILABLE(10_2, 2_0);



/*
 *  CFHTTPAuthenticationRequiresUserNameAndPassword()
 *  
 *  Discussion:
 *	Returns TRUE if the chosen authentication scheme requires a
 *	username and password.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The API's to CFHTTPAuthenticationRef are thread-safe so long as
 *	multiple threads are not altering the same
 *	CFHTTPAuthenticationRef at the same time.
 *  
 *  Parameters:
 *	
 *	auth:
 *	  The authentication information being queried.
 *  
 *  Result:
 *	Returns TRUE if the chosen authentication scheme requires a
 *	username and password.
 *  
 */
CFN_EXPORT Boolean 
CFHTTPAuthenticationRequiresUserNameAndPassword(CFHTTPAuthenticationRef auth) CF_AVAILABLE(10_3, 2_0);



/*
 *  CFHTTPAuthenticationRequiresAccountDomain()
 *  
 *  Discussion:
 *	Returns TRUE if the chosen authentication scheme requires a
 *	domain for authentication.  Currently, this will return TRUE for
 *	"NTLM" and FALSE for the other methods.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *	The API's to CFHTTPAuthenticationRef are thread-safe so long as
 *	multiple threads are not altering the same
 *	CFHTTPAuthenticationRef at the same time.
 *  
 *  Parameters:
 *	
 *	auth:
 *	  The authentication information being queried.
 *  
 *  Result:
 *	Returns TRUE if the chosen authentication scheme requires a
 *	domain for authentication.
 *  
 */
CFN_EXPORT Boolean 
CFHTTPAuthenticationRequiresAccountDomain(CFHTTPAuthenticationRef auth) CF_AVAILABLE(10_4, 2_0);



CF_ASSUME_NONNULL_END
CF_EXTERN_C_END

#endif /* __CFHTTPAUTHENTICATION__ */

// ==========  CFNetwork.framework/Headers/CFNetworkErrors.h
/*
	 File:	   CFNetwork/CFNetworkErrors.h
 
	 Contains:   CFNetwork error header
 
	 Copyright:  Copyright (c) 2006-2013 Apple Inc. All rights reserved.
 
	 Bugs?:	  For bug reports, consult the following page on
				 the World Wide Web:
 
					 http://developer.apple.com/bugreporter/
 
*/
#ifndef __CFNETWORKERRORS__
#define __CFNETWORKERRORS__

#ifndef __CFNETWORKDEFS__
#include <CFNetwork/CFNetworkDefs.h>
#endif

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif



#if PRAGMA_ONCE
#pragma once
#endif

CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/*
 *  kCFErrorDomainCFNetwork
 *  
 *  Discussion:
 *	Error domain for all errors originating in CFNetwork. Error codes
 *	may be interpreted using the list below.
 *  
 */
CFN_EXPORT const CFStringRef kCFErrorDomainCFNetwork CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFErrorDomainWinSock
 *  
 *  Discussion:
 *	On Windows, errors originating from WinSock are represented using
 *	this domain.
 *  
 */
CFN_EXPORT const CFStringRef kCFErrorDomainWinSock CF_AVAILABLE(10_5, 2_0);


/*
 *  CFNetworkErrors
 *  
 *  Discussion:
 *	The list of all public error codes returned under the error domain
 *	kCFErrorDomainCFNetwork
 */
typedef CF_ENUM(int, CFNetworkErrors) {

  kCFHostErrorHostNotFound = 1,
  kCFHostErrorUnknown = 2, // Query the kCFGetAddrInfoFailureKey to get the value returned from getaddrinfo; lookup in netdb.h
  // SOCKS errors; in all cases you may query kCFSOCKSStatusCodeKey to recover the status code returned by the server
  kCFSOCKSErrorUnknownClientVersion = 100,
  kCFSOCKSErrorUnsupportedServerVersion = 101, // Query the kCFSOCKSVersionKey to find the version requested by the server
  // SOCKS4-specific errors
  kCFSOCKS4ErrorRequestFailed = 110,  // request rejected or failed by the server
  kCFSOCKS4ErrorIdentdFailed = 111,  // request rejected because SOCKS server cannot connect to identd on the client
  kCFSOCKS4ErrorIdConflict = 112,  // request rejected because the client program and identd report different user-ids
  kCFSOCKS4ErrorUnknownStatusCode = 113,
  // SOCKS5-specific errors
  kCFSOCKS5ErrorBadState = 120,
  kCFSOCKS5ErrorBadResponseAddr = 121,
  kCFSOCKS5ErrorBadCredentials = 122,
  kCFSOCKS5ErrorUnsupportedNegotiationMethod = 123, // query kCFSOCKSNegotiationMethodKey to find the method requested
  kCFSOCKS5ErrorNoAcceptableMethod = 124,
  // FTP errors; query the kCFFTPStatusCodeKey to get the status code returned by the server
  kCFFTPErrorUnexpectedStatusCode = 200,
  // HTTP errors
  kCFErrorHTTPAuthenticationTypeUnsupported = 300,
  kCFErrorHTTPBadCredentials = 301,
  kCFErrorHTTPConnectionLost = 302,
  kCFErrorHTTPParseFailure = 303,
  kCFErrorHTTPRedirectionLoopDetected = 304,
  kCFErrorHTTPBadURL = 305,
  kCFErrorHTTPProxyConnectionFailure = 306,
  kCFErrorHTTPBadProxyCredentials = 307,
  kCFErrorPACFileError = 308,
  kCFErrorPACFileAuth = 309,
  kCFErrorHTTPSProxyConnectionFailure = 310,
  kCFStreamErrorHTTPSProxyFailureUnexpectedResponseToCONNECTMethod = 311,
	
  // Error codes for CFURLConnection and CFURLProtocol
  kCFURLErrorBackgroundSessionInUseByAnotherProcess = -996,
  kCFURLErrorBackgroundSessionWasDisconnected = -997,
  kCFURLErrorUnknown = -998,
  kCFURLErrorCancelled = -999,
  kCFURLErrorBadURL = -1000,
  kCFURLErrorTimedOut = -1001,
  kCFURLErrorUnsupportedURL = -1002,
  kCFURLErrorCannotFindHost = -1003,
  kCFURLErrorCannotConnectToHost = -1004,
  kCFURLErrorNetworkConnectionLost = -1005,
  kCFURLErrorDNSLookupFailed = -1006,
  kCFURLErrorHTTPTooManyRedirects = -1007,
  kCFURLErrorResourceUnavailable = -1008,
  kCFURLErrorNotConnectedToInternet = -1009,
  kCFURLErrorRedirectToNonExistentLocation = -1010,
  kCFURLErrorBadServerResponse = -1011,
  kCFURLErrorUserCancelledAuthentication = -1012,
  kCFURLErrorUserAuthenticationRequired = -1013,
  kCFURLErrorZeroByteResource = -1014,
  kCFURLErrorCannotDecodeRawData = -1015,
  kCFURLErrorCannotDecodeContentData = -1016,
  kCFURLErrorCannotParseResponse = -1017,
  kCFURLErrorInternationalRoamingOff = -1018,
  kCFURLErrorCallIsActive = -1019,
  kCFURLErrorDataNotAllowed = -1020,
  kCFURLErrorRequestBodyStreamExhausted = -1021,
  kCFURLErrorAppTransportSecurityRequiresSecureConnection = -1022,
  kCFURLErrorFileDoesNotExist = -1100,
  kCFURLErrorFileIsDirectory = -1101,
  kCFURLErrorNoPermissionsToReadFile = -1102,
  kCFURLErrorDataLengthExceedsMaximum = -1103,
  kCFURLErrorFileOutsideSafeArea = -1104,
  // SSL errors
  kCFURLErrorSecureConnectionFailed = -1200,
  kCFURLErrorServerCertificateHasBadDate = -1201,
  kCFURLErrorServerCertificateUntrusted = -1202,
  kCFURLErrorServerCertificateHasUnknownRoot = -1203,
  kCFURLErrorServerCertificateNotYetValid = -1204,
  kCFURLErrorClientCertificateRejected = -1205,
  kCFURLErrorClientCertificateRequired = -1206,
  kCFURLErrorCannotLoadFromNetwork = -2000,
  // Download and file I/O errors
  kCFURLErrorCannotCreateFile = -3000,
  kCFURLErrorCannotOpenFile = -3001,
  kCFURLErrorCannotCloseFile = -3002,
  kCFURLErrorCannotWriteToFile = -3003,
  kCFURLErrorCannotRemoveFile = -3004,
  kCFURLErrorCannotMoveFile = -3005,
  kCFURLErrorDownloadDecodingFailedMidStream = -3006,
  kCFURLErrorDownloadDecodingFailedToComplete = -3007,
	
  // Cookie errors
  kCFHTTPCookieCannotParseCookieFile = -4000,

  // Errors originating from CFNetServices
  kCFNetServiceErrorUnknown = -72000L,
  kCFNetServiceErrorCollision = -72001L,
  kCFNetServiceErrorNotFound = -72002L,
  kCFNetServiceErrorInProgress = -72003L,
  kCFNetServiceErrorBadArgument = -72004L,
  kCFNetServiceErrorCancel = -72005L,
  kCFNetServiceErrorInvalid = -72006L,
  kCFNetServiceErrorTimeout = -72007L,
  kCFNetServiceErrorDNSServiceFailure = -73000L // An error from DNS discovery; look at kCFDNSServiceFailureKey to get the error number and interpret using dns_sd.h	
};


/* Keys used by CFNetwork to pass additional error information back to the user within CFError's userInfo dictionary */
/*
 *  kCFURLErrorFailingURLErrorKey
 *  
 *  Discussion:
 *	When an NSURLConnection or NSURLDownload error occurs, this key's
 *  value is set to the URL which caused a load to fail
 *  
 */
CFN_EXPORT const CFStringRef kCFURLErrorFailingURLErrorKey CF_AVAILABLE(10_5, 2_2);

/*
 *  kCFURLErrorFailingURLStringErrorKey
 *  
 *  Discussion:
 *	When an NSURLConnection or NSURLDownload error occurs, this key's
 *  value is set to the CFString value of the URL which caused a load
 *  to fail
 *  
 */
CFN_EXPORT const CFStringRef kCFURLErrorFailingURLStringErrorKey CF_AVAILABLE(10_5, 2_2);

/*
 *  kCFGetAddrInfoFailureKey
 *  
 *  Discussion:
 *	When an error of kCFHostErrorUnknown is returned, this key's
 *	value is set to a CFNumber containing the raw error value
 *	returned by getaddrinfo()
 *  
 */
CFN_EXPORT const CFStringRef kCFGetAddrInfoFailureKey CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFSOCKSStatusCodeKey
 *  
 *  Discussion:
 *	When a SOCKS failure has occurred, this key's value is set to a
 *	CFString containing the status value returned by the SOCKS server.
 *  
 */
CFN_EXPORT const CFStringRef kCFSOCKSStatusCodeKey CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFSOCKSVersionKey
 *  
 *  Discussion:
 *	When an error of kCFSOCKSErrorUnsupportedServerVersion is
 *	returned, this key's value is set to a CFString containing the
 *	version number requested by the server.
 *  
 */
CFN_EXPORT const CFStringRef kCFSOCKSVersionKey CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFSOCKSNegotiationMethodKey
 *  
 *  Discussion:
 *	When an error of kCFSOCKS5ErrorUnsupportedNegotiationMethod is
 *	returned, this key's value is set to a CFString containing the
 *	negotiation method requested by the server.
 *  
 */
CFN_EXPORT const CFStringRef kCFSOCKSNegotiationMethodKey CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFDNSServiceFailureKey
 *  
 *  Discussion:
 *	When an error of kCFNetServicesErrorDNSServiceFailure is
 *	returned, this key's value is set to a CFNumber containing the
 *	value returned from DNS; interret it using the values dns_sd.h
 *  
 */
CFN_EXPORT const CFStringRef kCFDNSServiceFailureKey CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFFTPStatusCodeKey
 *  
 *  Discussion:
 *	When an error of kCFFTPErrorUnexpectedStatusCode is returned,
 *	this key's value is set to a CFString containing the status code
 *	returned by the server
 *  
 */
CFN_EXPORT const CFStringRef kCFFTPStatusCodeKey CF_AVAILABLE(10_5, 2_0);


CF_ASSUME_NONNULL_END
CF_EXTERN_C_END

#endif /* __CFNETWORKERRORS__ */

// ==========  CFNetwork.framework/Headers/CFNetDiagnostics.h
/*
	 File:	   CFNetwork/CFNetDiagnostics.h
 
	 Contains:   CFNetDiagnostics interface
  
	 Copyright:  Copyright (c) 2004-2017 Apple Inc. All rights reserved.
 
	 Bugs?:	  For bug reports, consult the following page on
				 the World Wide Web:
 
					 http://developer.apple.com/bugreporter/
 
*/
#ifndef __CFNETDIAGNOSTICS__
#define __CFNETDIAGNOSTICS__

#ifndef __CFNETWORKDEFS__
#include <CFNetwork/CFNetworkDefs.h>
#endif

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#include <stdint.h>


#if PRAGMA_ONCE
#pragma once
#endif

CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/*
 *  CFNetDiagnosticRef
 *  
 *  Discussion:
 *	This is the type used to describe the types of connection that
 *	clients may be querying about
 */
typedef struct __CFNetDiagnostic*	   CFNetDiagnosticRef;

/*
 *  CFNetDiagnosticStatusValues
 *  
 *  Discussion:
 *	Values for CFNetDiagnosticStatus
 */
typedef CF_ENUM(int, CFNetDiagnosticStatusValues) {

  /*
   * There is no status, but no error has occured
   */
  kCFNetDiagnosticNoErr	= 0,

  /*
   * An error occured that prevented the call from completing
   */
  kCFNetDiagnosticErr = -66560L,

  /*
   * The connection appears to be working
   */
  kCFNetDiagnosticConnectionUp = -66559L,
  kCFNetDiagnosticConnectionIndeterminate = -66558L,

  /*
   * The connection does not appear to be working
   */
  kCFNetDiagnosticConnectionDown = -66557L

} CF_DEPRECATED(10_4, 10_13, 2_0, 11_0);


/*
 *  CFNetDiagnosticStatus
 *  
 *  Discussion:
 *	Returned by the various status and diagnostic calls
 */
typedef CFIndex	CFNetDiagnosticStatus CF_DEPRECATED(10_4, 10_13, 2_0, 11_0);

/*
 *  CFNetDiagnosticCreateWithStreams()
 *  
 *  Discussion:
 *	Creates a CFNetDiagnosticRef from a pair of CFStreams. Either
 *	stream may be NULL. This is the preferred interface for creating
 *	a CFNetDiagnosticRef.
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  The CF allocator to use.
 *	
 *	readStream:
 *	  CFReadStreamRef referring to the failed connection. May be NULL.
 *	
 *	writeStream:
 *	  CFWriteStreamRef referring to the failed connection. May be
 *	  NULL.
 *  
 *  Result:
 *	A CFNetDiagnosticRef referring to the current networking issue.
 *  
 */
CFN_EXPORT CFNetDiagnosticRef 
CFNetDiagnosticCreateWithStreams(CFAllocatorRef __nullable alloc, CFReadStreamRef __nullable readStream, CFWriteStreamRef __nullable writeStream) CF_DEPRECATED(10_4, 10_13, 2_0, 11_0);


/*
 *  CFNetDiagnosticCreateWithURL()
 *  
 *  Discussion:
 *	Creates a CFNetDiagnosticRef based on a CFURLRef passed in by the
 *	application.
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  The CF allocator to use.
 *	
 *	url:
 *	  CFURLRef referring to the failed connection.
 *  
 *  Result:
 *	A CFNetDiagnosticRef referring to the current networking issue.
 *  
 */
CFN_EXPORT CFNetDiagnosticRef 
CFNetDiagnosticCreateWithURL(CFAllocatorRef alloc, CFURLRef url) CF_DEPRECATED(10_4, 10_13, 2_0, 11_0);



/*
 *  CFNetDiagnosticSetName()
 *  
 *  Discussion:
 *	If the framework requires an application name to be displayed to
 *	the user it will derive it from the bundle identifier of the
 *	currently running application, in that application's current
 *	localization. If you want to override that you may use
 *	CFNetDiagnosticSetName to specify a CFStringRef to be used.
 *  
 *  Parameters:
 *	
 *	details:
 *	  CFNetDiagnosticRef referring to the current problem.
 *	
 *	name:
 *	  The localized name that should appear to the user when
 *	  referring to the application.
 *  
 */
CFN_EXPORT void 
CFNetDiagnosticSetName(CFNetDiagnosticRef details, CFStringRef name) CF_DEPRECATED(10_4, 10_13, 2_0, 11_0);



/*
 *  CFNetDiagnosticDiagnoseProblemInteractively()
 *  
 *  Discussion:
 *	Opens the Network Diagnostics window and returns immediately once
 *	it is open. The client passes in a CFNetDiagnosticRef built with
 *	one of the creator functions.
 *  
 *  Parameters:
 *	
 *	details:
 *	  CFNetDiagnosticRef referring to the current problem.
 *  
 *  Result:
 *	A CFNetDiagnosticStatus. Will either be CFNetDiagnosticNoErr, or
 *	CFNetDiagnosticErr if there was an error attempting to run the
 *	diagnosis.
 *  
 */
CFN_EXPORT CFNetDiagnosticStatus 
CFNetDiagnosticDiagnoseProblemInteractively(CFNetDiagnosticRef details) CF_DEPRECATED(10_4, 10_13, 2_0, 11_0);



/*
 *  CFNetDiagnosticCopyNetworkStatusPassively()
 *  
 *  Discussion:
 *	Returns a status value that can be used to display basic
 *	information about the connection. If the caller wishes they may
 *	pass in a pointer to a CFStringRef that will be used to pass back
 *	a localized description of the problem. It is the caller's
 *	responsibility to release the CFStringRef. If the caller does not
 *	want a description they may pass in NULL.
 *	CFNetDiagnosticCopyNetworkStatusPassively() is guaranteed not to
 *	cause network activity.
 *  
 *  Parameters:
 *	
 *	details:
 *	  CFNetDiagnosticRef referring to the current problem.
 *	
 *	description:
 *	  A pointer to a CFStringRef that, upon return, will point to a
 *	  localized string containing a description of the current
 *	  network status. May be NULL. If it is not NULL, the client must
 *	  call CFRelease on the returned object.
 *  
 */
CFN_EXPORT CFNetDiagnosticStatus 
CFNetDiagnosticCopyNetworkStatusPassively(CFNetDiagnosticRef details, CFStringRef __nullable * __nullable description) CF_DEPRECATED(10_4, 10_13, 2_0, 11_0);



CF_ASSUME_NONNULL_END
CF_EXTERN_C_END

#endif /* __CFNETDIAGNOSTICS__ */

// ==========  CFNetwork.framework/Headers/CFHTTPStream.h
/*
	 File:	   CFNetwork/CFHTTPStream.h
 
	 Contains:   CoreFoundation Network HTTP streams header
 
	 Copyright:  Copyright (c) 2001-2013 Apple Inc. All rights reserved.
 
	 Bugs?:	  For bug reports, consult the following page on
				 the World Wide Web:
 
					 http://developer.apple.com/bugreporter/
 
*/
#ifndef __CFHTTPSTREAM__
#define __CFHTTPSTREAM__

#ifndef __CFNETWORKDEFS__
#include <CFNetwork/CFNetworkDefs.h>
#endif

#ifndef __CFSTREAM__
#include <CoreFoundation/CFStream.h>
#endif

#ifndef __CFHTTPMESSAGE__
#include <CFNetwork/CFHTTPMessage.h>
#endif



#if PRAGMA_ONCE
#pragma once
#endif

CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

#if PRAGMA_ENUM_ALWAYSINT
	#pragma enumsalwaysint on
#endif

/*
 *  kCFStreamErrorDomainHTTP
 *  
 *  Discussion:
 *	Result code returned by HTTP server
 *  
 */
CFN_EXPORT const SInt32 kCFStreamErrorDomainHTTP CF_AVAILABLE(10_1, 2_0);

/*
 *  CFStreamErrorHTTP
 *  
 *  Discussion:
 *	Errors from the kCFStreamErrorDomainHTTP domain.
 */
typedef CF_ENUM(int, CFStreamErrorHTTP) {

  /*
   * Could not parse the request/response.
   */
  kCFStreamErrorHTTPParseFailure = -1,

  /*
   * A loop was detected during redirection.
   */
  kCFStreamErrorHTTPRedirectionLoop = -2,

  /*
   * Could not retreive url for request/response.
   */
  kCFStreamErrorHTTPBadURL	  = -3
};

/*
 *  kCFStreamPropertyHTTPResponseHeader
 *  
 *  Discussion:
 *	Stream property key, for copy operations. Value is a
 *	CFHTTPMessage with 0 bytes data.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPResponseHeader CF_DEPRECATED(10_1, 10_11, 2_0, 9_0, "Use NSURLSession API for http requests");


/*
 *  kCFStreamPropertyHTTPFinalURL   *** DEPRECATED ***
 *  
 *  Discussion:
 *	Stream property key, for copy operations. The response header
 *	value is the CFURL from the final request; will only differ from
 *	the URL in the original request if an autoredirection has
 *	occurred.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPFinalURL CF_DEPRECATED(10_2, 10_11, 2_0, 9_0, "Use NSURLSession API for http requests");

/*
 *  kCFStreamPropertyHTTPFinalRequest   *** DEPRECATED ***
 *  
 *  Discussion:
 *	Stream property key, for copy operations. The value is the
 *	CFHTTPMessage transmitted by the stream, after all modifications
 *	(such as for authentication, connection policy, or redirection)
 *	have been made.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPFinalRequest CF_DEPRECATED(10_5, 10_11, 2_0, 9_0, "Use NSURLSession API for http requests");

/*
 *  kCFStreamPropertyHTTPProxy   *** DEPRECATED ***
 *  
 *  Discussion:
 *	Stream property key, for both set and copy operations. The value
 *	is a CFDictionary. HTTP proxy information is set the same way as
 *	SOCKS proxies (see CFSocketStream.h). Call
 *	CFReadStreamSetProperty() passing an HTTP stream and the property
 *	kCFStreamPropertyHTTPProxy. The value should include at least one
 *	Host/Port pair from the keys below. Use the dictionary returned
 *	by SystemConfiguration.framework to set the default values for
 *	the system. HTTP proxies are not applied automatically.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPProxy CF_DEPRECATED(10_2, 10_11, 2_0, 9_0, "Use NSURLSession API for http requests");


/*
 *  kCFStreamPropertyHTTPProxyHost   *** DEPRECATED ***
 *  
 *  Discussion:
 *	Proxy dictionary key. The hostname of an HTTP proxy. The value is
 *	a CFString. The key name matches kSCPropNetProxiesHTTPProxy.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPProxyHost CF_DEPRECATED(10_2, 10_11, 2_0, 9_0, "Use NSURLSession API for http requests");


/*
 *  kCFStreamPropertyHTTPProxyPort   *** DEPRECATED ***
 *  
 *  Discussion:
 *	Proxy dictionary key. Value is a CFNumber.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPProxyPort CF_DEPRECATED(10_2, 10_11, 2_0, 9_0, "Use NSURLSession API for http requests");
/* matches kSCPropNetProxiesHTTPPort */


/*
 *  kCFStreamPropertyHTTPSProxyHost   *** DEPRECATED ***
 *  
 *  Discussion:
 *	Proxy dictionary key. Value is a CFString.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPSProxyHost CF_DEPRECATED(10_2, 10_11, 2_0, 9_0, "Use NSURLSession API for http requests");
/* matches kSCPropNetProxiesHTTPSProxy */


/*
 *  kCFStreamPropertyHTTPSProxyPort   *** DEPRECATED ***
 *  
 *  Discussion:
 *	Proxy dictionary key. Value is a CFNumber.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPSProxyPort CF_DEPRECATED(10_2, 10_11, 2_0, 9_0, "Use NSURLSession API for http requests");
/* matches kSCPropNetProxiesHTTPSPort */


/*
 *  kCFStreamPropertyHTTPShouldAutoredirect   *** DEPRECATED ***
 *  
 *  Discussion:
 *	Stream property key. Value is a CFBoolean. Redirection is not
 *	performed by default.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPShouldAutoredirect CF_DEPRECATED(10_2, 10_11, 2_0, 9_0, "Use NSURLSession API for http requests");


/*
 *  kCFStreamPropertyHTTPAttemptPersistentConnection   *** DEPRECATED ***
 *  
 *  Discussion:
 *	Stream property key. Value is a CFBoolean.  If this property is
 *	set to kCFBooleanTrue, an HTTP stream will look for an
 *	appropriate extant persistent connection to use, and if it finds
 *	none, will try to create one. Persistent connections are not used
 *	by default.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPAttemptPersistentConnection CF_DEPRECATED(10_2, 10_11, 2_0, 9_0, "Use NSURLSession API for http requests");


/*
 *  kCFStreamPropertyHTTPRequestBytesWrittenCount   *** DEPRECATED ***
 *  
 *  Discussion:
 *	Stream property key. Value is a CFNumber. This property can only
 *	be retrieved, not set. The number returned is the number of bytes
 *	from the body of the request that have been written to the
 *	underlying socket
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPRequestBytesWrittenCount CF_DEPRECATED(10_3, 10_11, 2_0, 9_0, "Use NSURLSession API for http requests");


/*********************/
/* Creation routines */
/*********************/
/*
 *  CFReadStreamCreateForHTTPRequest()   *** DEPRECATED ***
 *  
 *  DEPRECATED: Use NSURLSession API for http requests
 *
 *  Discussion:
 *	Create an HTTP read stream for the response to the given request.
 *	When the stream is opened, it will begin transmitting the
 *	request. The bytes returned are the pure body bytes; the response
 *	header has been parsed off. To retrieve the response header, ask
 *	for kCFStreamPropertyHTTPResponseHeader, above, any time after
 *	the first bytes arrive on the stream (or when stream end is
 *	reported, if there are no data bytes). When an HTTP/1.1 server
 *	returns a chunked a response, the chunks will be formed into one
 *	continuous stream.
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  A pointer to the CFAllocator which should be used to allocate
 *	  memory for the CF read stream and its storage for values. If
 *	  this reference is not a valid CFAllocator, the behavior is
 *	  undefined.
 *	
 *	request:
 *	  A pointer to a CFHTTPMessage created by the
 *	  CFHTTPMessageCreateRequest function.
 *  
 *  Result:
 *	A pointer to the CF read stream created, or NULL if failed. It is
 *	caller's responsibilty to release the memory allocated for the
 *	read stream.
 *  
 */
CFN_EXPORT CFReadStreamRef 
CFReadStreamCreateForHTTPRequest(CFAllocatorRef __nullable alloc, CFHTTPMessageRef request) CF_DEPRECATED(10_2, 10_11, 2_0, 9_0, "Use NSURLSession API for http requests");


/*
 *  CFReadStreamCreateForStreamedHTTPRequest()   *** DEPRECATED ***
 *  
 *  DEPRECATED: Use NSURLSession API for http requests
 *
 *  Discussion:
 *	Creates a read stream for the response to the given
 *	requestHeaders plus requestBody. Use in preference to
 *	CFReadStreamCreateForHTTPRequest() when the body of the request
 *	is larger than you wish to be resident in memory.  Note that
 *	because streams cannot be reset, read streams created this way
 *	cannot have autoredirection enabled.  If the Content-Length
 *	header is set in requestHeaders, it is assumed that the caller
 *	got the length right and that requestBody will report
 *	end-of-stream after precisely Content-Length bytes have been read
 *	from it. If the Content-Length header is not set, the chunked
 *	transfer-encoding will be added to requestHeaders, and bytes read
 *	from requestBody will be transmitted chunked. The body of
 *	requestHeaders is ignored.
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  A pointer to the CFAllocator which should be used to allocate
 *	  memory for the CF read stream and its storage for values. If
 *	  this reference is not a valid CFAllocator, the behavior is
 *	  undefined.
 *	
 *	requestHeaders:
 *	  A pointer to a CFHTTPMessage created by the
 *	  CFHTTPMessageCreateRequest function. The body of requestHeaders
 *	  is ignored.
 *	
 *	requestBody:
 *	  A pointer to a CFReadStream.
 *  
 *  Result:
 *	A pointer to the CF read stream created, or NULL if failed. It is
 *	caller's responsibilty to release the memory allocated for the
 *	read stream.
 *  
 */
CFN_EXPORT CFReadStreamRef 
CFReadStreamCreateForStreamedHTTPRequest(CFAllocatorRef __nullable alloc, CFHTTPMessageRef requestHeaders, CFReadStreamRef requestBody) CF_DEPRECATED(10_2, 10_11, 2_0, 9_0, "Use NSURLSession API for http requests");


/*
 *  CFHTTPReadStreamSetRedirectsAutomatically()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *	Use the kCFStreamPropertyHTTPShouldAutoredirect property above
 *	instead.
 *  
 *  Discussion:
 *	Sets the redirection property on the http stream.
 *  
 *  Parameters:
 *	
 *	httpStream:
 *	  A pointer to the CFHTTPStream to be set.
 *	
 *	shouldAutoRedirect:
 *	  A boolean indicating whether to redirect or not.
 *  
 */
CFN_EXPORT void
CFHTTPReadStreamSetRedirectsAutomatically(CFReadStreamRef httpStream, Boolean shouldAutoRedirect) CF_DEPRECATED(10_1, 10_3, NA, NA);

#if PRAGMA_ENUM_ALWAYSINT
	#pragma enumsalwaysint reset
#endif

CF_ASSUME_NONNULL_END
CF_EXTERN_C_END

#endif /* __CFHTTPSTREAM__ */

// ==========  CFNetwork.framework/Headers/CFNetworkDefs.h
/*
	 File:	   CFNetwork/CFNetworkDefs.h
 
	 Contains:   CoreFoundation Network header
 
	 Copyright:  Copyright (c) 2001-2013 Apple Inc. All rights reserved.
 
	 Bugs?:	  For bug reports, consult the following page on
				 the World Wide Web:
 
					 http://developer.apple.com/bugreporter/
 
*/

#ifndef __CFNETWORK_DEFS_H_
#define __CFNETWORK_DEFS_H_


// To pick-up the CALLBACK_API_C definition.
#include <ConditionalMacros.h>

/* Standard incantation for exporting/importing DLL symbols */
#if defined(__WIN32__)
  #if defined(CFNETWORK_BUILDING_DLL)
		#define CFN_EXPORT __declspec(dllexport) extern
 #else
	  #define CFN_EXPORT __declspec(dllimport) extern
 #endif
#else
	#define CFN_EXPORT extern
#endif

#endif //__CFNETWORK_DEFS_H_


// ==========  CFNetwork.framework/Headers/CFHTTPMessage.h
/*
	 File:	   CFNetwork/CFHTTPMessage.h
 
	 Contains:   CoreFoundation Network socket streams header
 
	 Copyright:  Copyright (c) 2001-2013 Apple Inc. All rights reserved.
 
	 Bugs?:	  For bug reports, consult the following page on
				 the World Wide Web:
 
					 http://developer.apple.com/bugreporter/
 
*/
#ifndef __CFHTTPMESSAGE__
#define __CFHTTPMESSAGE__

#ifndef __CFNETWORKDEFS__
#include <CFNetwork/CFNetworkDefs.h>
#endif

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif

#ifndef __CFURL__
#include <CoreFoundation/CFURL.h>
#endif



#if PRAGMA_ONCE
#pragma once
#endif

CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/*
 *  kCFHTTPVersion1_0
 *  
 *  Discussion:
 *	Version string for HTTP 1.0.
 *  
 */
CFN_EXPORT const CFStringRef kCFHTTPVersion1_0 CF_AVAILABLE(10_1, 2_0);

/*
 *  kCFHTTPVersion1_1
 *  
 *  Discussion:
 *	Version string for HTTP 1.1.
 *  
 */
CFN_EXPORT const CFStringRef kCFHTTPVersion1_1 CF_AVAILABLE(10_1, 2_0);

/*
 *  kCFHTTPVersion2_0
 *
 *  Discussion:
 *	Version string for HTTP 2.0.
 *
 */
CFN_EXPORT const CFStringRef kCFHTTPVersion2_0 CF_AVAILABLE(10_10, 8_0);

/*
 *  kCFHTTPAuthenticationSchemeBasic
 *  
 *  Discussion:
 *	HTTP Basic authentication scheme.
 *  
 */
CFN_EXPORT const CFStringRef kCFHTTPAuthenticationSchemeBasic CF_AVAILABLE(10_2, 2_0);

/*
 *  kCFHTTPAuthenticationSchemeDigest
 *  
 *  Discussion:
 *	HTTP Digest Access authentication scheme.
 *  
 */
CFN_EXPORT const CFStringRef kCFHTTPAuthenticationSchemeDigest CF_AVAILABLE(10_2, 2_0);

/*
 *  kCFHTTPAuthenticationSchemeNTLM
 *  
 *  Discussion:
 *	HTTP NTLM authentication scheme.
 *  
 */
CFN_EXPORT const CFStringRef kCFHTTPAuthenticationSchemeNTLM CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFHTTPAuthenticationSchemeKerberos
 *
 *  Discussion:
 *	HTTP Negotiate authentication scheme.
 *
 */
CFN_EXPORT const CFStringRef kCFHTTPAuthenticationSchemeKerberos CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFHTTPAuthenticationSchemeNegotiate
 *  
 *  Discussion:
 *	HTTP Negotiate authentication scheme.
 *  
 */
CFN_EXPORT const CFStringRef kCFHTTPAuthenticationSchemeNegotiate CF_AVAILABLE(10_5, 2_0);
	
/*
 *  kCFHTTPAuthenticationSchemeNegotiate2
 *  
 *  Discussion:
 *	HTTP Negotiate v2 authentication scheme.
 *  
 */
CFN_EXPORT const CFStringRef kCFHTTPAuthenticationSchemeNegotiate2 CF_AVAILABLE(10_6, 3_0);
	
/*
 *  kCFHTTPAuthenticationSchemeXMobileMeAuthToken
 *  
 *  Discussion:
 *	HTTP XMobileMeAuthToken authentication scheme.
 *  
 */
CFN_EXPORT const CFStringRef kCFHTTPAuthenticationSchemeXMobileMeAuthToken CF_AVAILABLE(10_6, 4_3);

/*
 *  CFHTTPMessageRef
 *  
 *  Discussion:
 *	This is the type of a reference to an HTTP message. An HTTP
 *	message can be a request or a response.
 */
typedef struct __CFHTTPMessage*		 CFHTTPMessageRef;

/*
 *  CFHTTPMessageGetTypeID()
 *  
 *  Discussion:
 *	Return the unique type for this class.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Result:
 *	A unique CFType for CFHTTPMessage.
 *  
 */
CFN_EXPORT CFTypeID 
CFHTTPMessageGetTypeID(void) CF_AVAILABLE(10_1, 2_0);


/*
 *  CFHTTPMessageCreateRequest()
 *  
 *  Discussion:
 *	Create an HTTPMessage from an HTTP method, url and version.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  A pointer to the CFAllocator which should be used to allocate
 *	  memory for the CF read stream and its storage for values. If
 *	  this reference is not a valid CFAllocator, the behavior is
 *	  undefined.
 *	
 *	requestMethod:
 *	  A pointer to a CFString indicating the method of request. For a
 *	  "GET" request, for example, the value would be CFSTR("GET").
 *	
 *	url:
 *	  A pointer to a CFURL structure created any of the several
 *	  CFURLCreate... functions.  If this parameter is not a pointer
 *	  to a valid CFURL structure, the behavior is undefined.
 *	
 *	httpVersion:
 *	  A pointer to a CFString indicating the version of request.
 *  
 *  Result:
 *	A pointer to the CFHTTPMessage created, or NULL if failed. It is
 *	caller's responsibilty to release the memory allocated for the
 *	message.
 *  
 */
CFN_EXPORT CFHTTPMessageRef 
CFHTTPMessageCreateRequest(CFAllocatorRef __nullable alloc, CFStringRef requestMethod, CFURLRef url, CFStringRef httpVersion) CF_AVAILABLE(10_1, 2_0);


/*
 *  CFHTTPMessageCreateResponse()
 *  
 *  Discussion:
 *	Create an HTTPMessage from an HTTP status code, description and
 *	version.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  A pointer to the CFAllocator which should be used to allocate
 *	  memory for the CF read stream and its storage for values. If
 *	  this reference is not a valid CFAllocator, the behavior is
 *	  undefined.
 *	
 *	statusCode:
 *	  An integer status code for the response.
 *	
 *	statusDescription:
 *	  A pointer to a CFString for the status. Pass NULL to use the
 *	  standard description for the given status code, as found in RFC
 *	  2616.
 *	
 *	httpVersion:
 *	  A pointer to a CFString for the HTTP version.
 *  
 *  Result:
 *	A pointer to the CFHTTPMessage created, or NULL if failed. It is
 *	caller's responsibilty to release the memory allocated for the
 *	message.
 *  
 */
CFN_EXPORT CFHTTPMessageRef 
CFHTTPMessageCreateResponse(
  CFAllocatorRef  __nullable alloc,
  CFIndex         statusCode,
  CFStringRef     __nullable statusDescription,
  CFStringRef     httpVersion)              CF_AVAILABLE(10_1, 2_0);


/*
 *  CFHTTPMessageCreateEmpty()
 *  
 *  Discussion:
 *	Creates an empty request or response, which you can then append
 *	bytes to via CFHTTPMessageAppendBytes().
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  A pointer to the CFAllocator which should be used to allocate
 *	  memory for the CF read stream and its storage for values. If
 *	  this reference is not a valid CFAllocator, the behavior is
 *	  undefined.
 *	
 *	isRequest:
 *	  A boolean. Pass kCFBooleanTrue if the message should be a
 *	  request.
 *  
 *  Result:
 *	A pointer to the CFHTTPMessage created, or NULL if failed. It is
 *	caller's responsibilty to release the memory allocated for the
 *	message.
 *  
 */
CFN_EXPORT CFHTTPMessageRef 
CFHTTPMessageCreateEmpty(CFAllocatorRef __nullable alloc, Boolean isRequest) CF_AVAILABLE(10_1, 2_0);


/*
 *  CFHTTPMessageCreateCopy()
 *  
 *  Discussion:
 *	Creates a copy of a CFHTTPMessage.
 *  
 *  Mac OS X threading:
 *	Not thread safe
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  A pointer to the CFAllocator which should be used to allocate
 *	  memory for the CF read stream and its storage for values. If
 *	  this reference is not a valid CFAllocator, the behavior is
 *	  undefined.
 *	
 *	message:
 *	  A pointer to the CFHTTPMessage to be copied. If the message is
 *	  NULL, the behavior is undefined.
 *  
 *  Result:
 *	A pointer to the CFHTTPMessage created, or NULL if failed. It is
 *	caller's responsibilty to release the memory allocated for the
 *	message.
 *  
 */
CFN_EXPORT CFHTTPMessageRef 
CFHTTPMessageCreateCopy(CFAllocatorRef __nullable alloc, CFHTTPMessageRef message) CF_AVAILABLE(10_1, 2_0);


/*
 *  CFHTTPMessageIsRequest()
 *  
 *  Discussion:
 *	Returns whether the CFHTTPMessage is a request or a response.
 *  
 *  Mac OS X threading:
 *	Not thread safe
 *  
 *  Parameters:
 *	
 *	message:
 *	  A pointer to the CFHTTPMessage to be copied. If the message is
 *	  NULL, the behavior is undefined.
 *  
 *  Result:
 *	A Boolean. A value of kCFBooleanTrue indicates the message is a
 *	request. A value of kCFBooleanFalse indicates the message is a
 *	response.
 *  
 */
CFN_EXPORT Boolean 
CFHTTPMessageIsRequest(CFHTTPMessageRef message) CF_AVAILABLE(10_1, 2_0);


/*
 *  CFHTTPMessageCopyVersion()
 *  
 *  Discussion:
 *	Returns the HTTP version.
 *  
 *  Mac OS X threading:
 *	Not thread safe
 *  
 *  Parameters:
 *	
 *	message:
 *	  A pointer to the CFHTTPMessage to be copied. If the message is
 *	  NULL, the behavior is undefined.
 *  
 *  Result:
 *	A pointer to a CFString, or NULL if failed. It is caller's
 *	responsibilty to release the memory allocated for the string.
 *  
 */
CFN_EXPORT CFStringRef 
CFHTTPMessageCopyVersion(CFHTTPMessageRef message) CF_AVAILABLE(10_1, 2_0);


/*
 *  CFHTTPMessageCopyBody()
 *  
 *  Discussion:
 *	Returns the body of the message.
 *  
 *  Mac OS X threading:
 *	Not thread safe
 *  
 *  Parameters:
 *	
 *	message:
 *	  A pointer to the CFHTTPMessage to be copied. If the message is
 *	  NULL, the behavior is undefined.
 *  
 *  Result:
 *	A pointer to a CFData, or NULL if failed. It is caller's
 *	responsibilty to release the memory allocated for the data.
 *  
 */
CFN_EXPORT __nullable CFDataRef
CFHTTPMessageCopyBody(CFHTTPMessageRef message) CF_AVAILABLE(10_1, 2_0);


/*
 *  CFHTTPMessageSetBody()
 *  
 *  Discussion:
 *	Sets the body of the message from a CFData.
 *  
 *  Mac OS X threading:
 *	Not thread safe
 *  
 *  Parameters:
 *	
 *	message:
 *	  A pointer to the CFHTTPMessage to be copied. If the message is
 *	  NULL, the behavior is undefined.
 *	
 *	bodyData:
 *	  A pointer to a CFData containing the body to be set. If the
 *	  bodyData is NULL, the behavior is undefined.
 *  
 */
CFN_EXPORT void 
CFHTTPMessageSetBody(CFHTTPMessageRef message, CFDataRef bodyData) CF_AVAILABLE(10_1, 2_0);


/*
 *  CFHTTPMessageCopyHeaderFieldValue()
 *  
 *  Discussion:
 *	Returns the specified header field.
 *  
 *  Mac OS X threading:
 *	Not thread safe
 *  
 *  Parameters:
 *	
 *	message:
 *	  A pointer to the CFHTTPMessage to be copied. If the message is
 *	  NULL, the behavior is undefined.
 *	
 *	headerField:
 *	  A pointer to the CFString. If the headerField is NULL, the
 *	  behavior is undefined.
 *  
 *  Result:
 *	A pointer to a CFString, or NULL if failed. It is caller's
 *	responsibilty to release the memory allocated for the string.
 *  
 */
CFN_EXPORT __nullable CFStringRef
CFHTTPMessageCopyHeaderFieldValue(CFHTTPMessageRef message, CFStringRef headerField) CF_AVAILABLE(10_1, 2_0);


/*
 *  CFHTTPMessageCopyAllHeaderFields()
 *  
 *  Discussion:
 *	Returns a CFDictionary containing all of the header fields.
 *  
 *  Mac OS X threading:
 *	Not thread safe
 *  
 *  Parameters:
 *	
 *	message:
 *	  A pointer to the CFHTTPMessage to be copied. If the message is
 *	  NULL, the behavior is undefined.
 *  
 *  Result:
 *	A pointer to a CFDictionary, or NULL if failed. It is caller's
 *	responsibilty to release the memory allocated for the dictionary.
 *  
 */
CFN_EXPORT __nullable CFDictionaryRef
CFHTTPMessageCopyAllHeaderFields(CFHTTPMessageRef message) CF_AVAILABLE(10_1, 2_0);


/*
 *  CFHTTPMessageSetHeaderFieldValue()
 *  
 *  Discussion:
 *	Sets the value of the specified header field.
 *  
 *  Mac OS X threading:
 *	Not thread safe
 *  
 *  Parameters:
 *	
 *	message:
 *	  A pointer to the CFHTTPMessage to be copied. If the message is
 *	  NULL, the behavior is undefined.
 *	
 *	headerField:
 *	  A pointer to the CFString. If headerField is NULL, the behavior
 *	  is undefined.
 *	
 *	value:
 *	  A pointer to the CFString containing the value to set. Set the
 *	  value to NULL to remove the header field.
 *  
 */
CFN_EXPORT void 
CFHTTPMessageSetHeaderFieldValue(CFHTTPMessageRef message, CFStringRef headerField, CFStringRef __nullable value) CF_AVAILABLE(10_1, 2_0);


/*
 *  CFHTTPMessageAppendBytes()
 *  
 *  Discussion:
 *	Appends the given bytes to the message given (parsing out any
 *	control information if appropriate).  Returns kCFBooleanFalse if
 *	a parsing error occurs while processing the new data.
 *  
 *  Mac OS X threading:
 *	Not thread safe
 *  
 *  Parameters:
 *	
 *	message:
 *	  A pointer to the CFHTTPMessage to be copied. If the message is
 *	  NULL, the behavior is undefined.
 *	
 *	newBytes:
 *	  A pointer to the bytes. If newBytes is NULL, the behavior is
 *	  undefined.
 *	
 *	numBytes:
 *	  A CFIndex of the number of bytes to append.
 *  
 *  Result:
 *	A Boolean indicating success or failure.
 *  
 */
CFN_EXPORT Boolean 
CFHTTPMessageAppendBytes(CFHTTPMessageRef message, const UInt8 *newBytes, CFIndex numBytes) CF_AVAILABLE(10_1, 2_0);


/*
 *  CFHTTPMessageIsHeaderComplete()
 *  
 *  Discussion:
 *	Returns whether further header data is expected by the message.
 *  
 *  Mac OS X threading:
 *	Not thread safe
 *  
 *  Parameters:
 *	
 *	message:
 *	  A pointer to the CFHTTPMessage to be copied. If the message is
 *	  NULL, the behavior is undefined.
 *  
 *  Result:
 *	A Boolean. A value of kCFBooleanTrue indicates the header is
 *	complete and no further data is expected.
 *  
 */
CFN_EXPORT Boolean 
CFHTTPMessageIsHeaderComplete(CFHTTPMessageRef message) CF_AVAILABLE(10_1, 2_0);


/*
 *  CFHTTPMessageCopySerializedMessage()
 *  
 *  Discussion:
 *	Creates a self-contained copy of a CFHTTPMessage. This would be
 *	suitable for persistant storage or for transmitting over the
 *	network independently.
 *  
 *  Mac OS X threading:
 *	Not thread safe
 *  
 *  Parameters:
 *	
 *	request:
 *	  A pointer to the CFHTTPMessage to be seralized.
 *  
 *  Result:
 *	A pointer to a CFData, or NULL if failed. It is caller's
 *	responsibilty to release the memory allocated for the data.
 *  
 */
CFN_EXPORT __nullable CFDataRef
CFHTTPMessageCopySerializedMessage(CFHTTPMessageRef message) CF_AVAILABLE(10_1, 2_0);


/*********************/
/* Request functions */
/*********************/

/*
 *  CFHTTPMessageCopyRequestURL()
 *  
 *  Discussion:
 *	Creates a copy of the request URL.
 *  
 *  Mac OS X threading:
 *	Not thread safe
 *  
 *  Parameters:
 *	
 *	request:
 *	  A pointer to the CFHTTPMessage.
 *  
 *  Result:
 *	A pointer to a CFURL, or NULL if failed. It is caller's
 *	responsibilty to release the memory allocated for the url.
 *  
 */
CFN_EXPORT __nullable CFURLRef
CFHTTPMessageCopyRequestURL(CFHTTPMessageRef request) CF_AVAILABLE(10_1, 2_0);


/*
 *  CFHTTPMessageCopyRequestMethod()
 *  
 *  Discussion:
 *	Creates a copy of the request method.
 *  
 *  Mac OS X threading:
 *	Not thread safe
 *  
 *  Parameters:
 *	
 *	request:
 *	  A pointer to the CFHTTPMessage.
 *  
 *  Result:
 *	A pointer to a CFString, or NULL if failed. It is caller's
 *	responsibilty to release the memory allocated for the string.
 *  
 */
CFN_EXPORT __nullable CFStringRef
CFHTTPMessageCopyRequestMethod(CFHTTPMessageRef request) CF_AVAILABLE(10_1, 2_0);


/*
 *  CFHTTPMessageAddAuthentication()
 *  
 *  Discussion:
 *	Adds authentication to the request. Tries to modify request to
 *	contain the authentication information requested by the failed
 *	response (which presumably is a 401 or 407 response).
 *  
 *  Mac OS X threading:
 *	Not thread safe
 *  
 *  Parameters:
 *	
 *	request:
 *	  A pointer to a CFHTTPMessage request.
 *	
 *	authenticationFailureResponse:
 *	  A pointer to a CFHTTPMessage of the failed response.
 *	
 *	username:
 *	  A pointer to a CFString containing the user name to
 *	  authenticate.
 *	
 *	password:
 *	  A pointer to a CFString containing the password of the user.
 *	
 *	authenticationScheme:
 *	  A pointer to a CFString containing the authentication scheme to
 *	  use to authenticate. If authenticationScheme is NULL, strongest
 *	  supported scheme listed authenticationFailureResponse will be
 *	  used.
 *	
 *	forProxy:
 *	  A boolean indicating whether the authentication applies to a
 *	  proxy or not.
 *  
 *  Result:
 *	A pointer to a CFString, or NULL if failed. It is caller's
 *	responsibilty to release the memory allocated for the string.
 *  
 */
CFN_EXPORT Boolean 
CFHTTPMessageAddAuthentication(
  CFHTTPMessageRef   request,
  CFHTTPMessageRef   __nullable authenticationFailureResponse,
  CFStringRef        username,
  CFStringRef        password,
  CFStringRef        __nullable authenticationScheme,
  Boolean            forProxy)              CF_AVAILABLE(10_1, 2_0);


/**********************/
/* Response functions */
/**********************/

/*
 *  CFHTTPMessageGetResponseStatusCode()
 *  
 *  Discussion:
 *	Returns the status code for the response.
 *  
 *  Mac OS X threading:
 *	Not thread safe
 *  
 *  Parameters:
 *	
 *	response:
 *	  A pointer to the CFHTTPMessage to be copied. If the message is
 *	  NULL, the behavior is undefined.
 *  
 *  Result:
 *	A UInt32 indicating the status code.
 *  
 */
CFN_EXPORT CFIndex 
CFHTTPMessageGetResponseStatusCode(CFHTTPMessageRef response) CF_AVAILABLE(10_1, 2_0);


/*
 *  CFHTTPMessageCopyResponseStatusLine()
 *  
 *  Discussion:
 *	Returns the status line for the response.
 *  
 *  Mac OS X threading:
 *	Not thread safe
 *  
 *  Parameters:
 *	
 *	response:
 *	  A pointer to the CFHTTPMessage to be copied. If the message is
 *	  NULL, the behavior is undefined.
 *  
 *  Result:
 *	A CFString indicating the status code, or NULL if failed. It is
 *	caller's responsibilty to release the memory allocated for the
 *	string.
 *  
 */
CFN_EXPORT __nullable CFStringRef
CFHTTPMessageCopyResponseStatusLine(CFHTTPMessageRef response) CF_AVAILABLE(10_1, 2_0);



CF_ASSUME_NONNULL_END
CF_EXTERN_C_END

#endif /* __CFHTTPMESSAGE__ */

// ==========  CFNetwork.framework/Headers/CFProxySupport.h
/*
	 File:	   CFNetwork/CFProxySupport.h
 
	 Contains:   Support for computing which proxy applies when
 
	 Copyright:  Copyright (c) 2006-2013 Apple Inc. All rights reserved.
 
	 Bugs?:	  For bug reports, consult the following page on
				 the World Wide Web:
 
					 http://developer.apple.com/bugreporter/
 
*/
#ifndef __CFPROXYSUPPORT__
#define __CFPROXYSUPPORT__

#ifndef __CFNETWORKDEFS__
#include <CFNetwork/CFNetworkDefs.h>
#endif

#ifndef __CFARRAY__
#include <CoreFoundation/CFArray.h>
#endif

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif

#ifndef __CFURL__
#include <CoreFoundation/CFURL.h>
#endif

#ifndef __CFERROR__
#include <CoreFoundation/CFError.h>
#endif

#ifndef __CFRUNLOOP__
#include <CoreFoundation/CFRunLoop.h>
#endif

#ifndef __CFSTREAM__
#include <CoreFoundation/CFStream.h>
#endif


/* 
	These APIs return arrays of dictionaries, where each dictionary describes a single proxy. 
	The arrays represent the order in which the proxies should be tried - try to download the URL
	using the first entry in the array, and if that fails, try using the second entry, and so on.

	The keys to the proxy dictionaries follow the function declarations; every proxy dictionary 
	will have an entry for kCFProxyTypeKey.  If the type is anything except 
	kCFProxyTypeAutoConfigurationURL, the dictionary will also have entries for the proxy's host
	and port (under kCFProxyHostNameKey and kCFProxyPortNumberKey respectively).  If the type is
	kCFProxyTypeAutoConfigurationURL, it will have an entry for kCFProxyAutoConfigurationURLKey.  
	
	The keys for username and password are optional and will only be present if the username 
	or password could be extracted from the information passed in (i.e. either the URL itself
	or the proxy dictionary supplied).  These APIs do not consult any external credential stores
	(such as the Keychain).
*/


#if PRAGMA_ONCE
#pragma once
#endif

CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/*!
	@function CFNetworkCopySystemProxySettings
	@discussion Returns a CFDictionary containing the current system internet proxy settings.
	@result Returns a dictionary containing key-value pairs that represent
		the current internet proxy settings.  See below for definitions of the keys and
		values.
		NULL if no proxy settings have been defined or if an error
		was encountered.
		The caller is responsible for releasing the returned dictionary.
*/
CFN_EXPORT __nullable CFDictionaryRef
CFNetworkCopySystemProxySettings(void) CF_AVAILABLE(10_6, 2_0);

	
/*
 *  CFNetworkCopyProxiesForURL()
 *  
 *  Discussion:
 *	Given a URL and a proxy dictionary, determines the ordered list
 *	of proxies that should be used to download the given URL.
 *  
 *  Parameters:
 *	
 *	url:
 *	  The URL to be accessed
 *	
 *	proxySettings:
 *	  A dictionary describing the available proxy settings; the
 *	  dictionary's format should match the dictionary returned
 *	  by CFNetworkCopySystemProxySettings described below.
 *  
 *  Result:
 *	An array of dictionaries; each dictionary describes a single
 *	proxy.  See the comment at the top of this file for how to
 *	interpret the returned dictionaries.
 *  
 */
CFN_EXPORT CFArrayRef 
CFNetworkCopyProxiesForURL(CFURLRef url, CFDictionaryRef proxySettings) CF_AVAILABLE(10_5, 2_0);




/*
 *  CFProxyAutoConfigurationResultCallback
 *  
 *  Discussion:
 *	Callback function to be called when a PAC file computation
 *	(initiated by either CFNetworkExecuteProxyAutoConfigurationScript
 *	or CFNetworkExecuteProxyAutoConfigurationURL) has completed.
 *  
 *  Parameters:
 *	
 *	client:
 *	  The client reference passed in to
 *	  CFNetworkExecuteProxyAutoConfigurationScript or
 *	  CFNetworkExecuteProxyAutoConfigurationURL
 *	
 *	proxyList:
 *	  Upon success, the list of proxies returned by the
 *	  autoconfiguration script.  The list has the same format as
 *	  returned by CFProxyCopyProxiesForURL, above, except that no
 *	  entry may be of type kCFProxyTypeAutoConfigurationURL.  Note
 *	  that if the client wishes to keep this list, they must retain
 *	  it when they receive this callback.
 *	
 *	error:
 *	  Upon failure, an error object explaining the failure.
 */
typedef CALLBACK_API_C( void , CFProxyAutoConfigurationResultCallback )(void *client, CFArrayRef proxyList, CFErrorRef __nullable error);

/*
 *  CFNetworkCopyProxiesForAutoConfigurationScript()
 *  
 *  Discussion:
 *	Synchronously executes the given proxy autoconfiguration script
 *	and returns a valid proxyList and NULL error upon success or a
 *	NULL proxyList and valid error on failure.
 *  
 *  Parameters:
 *	
 *	proxyAutoConfigurationScript:
 *	  A CFString containing the code of the script to be executed.
 *	
 *	targetURL:
 *	  The URL that should be input in to the autoconfiguration script.
 *	
 *	error:
 *	  A return argument that will contain a valid error in case of
 *	  failure.
 *  
 *  Result:
 *	An array of dictionaries describing the proxies returned by the
 *	script or NULL on failure.
 *  
 */
CFN_EXPORT __nullable CFArrayRef
CFNetworkCopyProxiesForAutoConfigurationScript(CFStringRef proxyAutoConfigurationScript, CFURLRef targetURL, CFErrorRef * __nullable error) CF_AVAILABLE(10_5, 2_0);


/*
 *  CFNetworkExecuteProxyAutoConfigurationScript()
 *  
 *  Discussion:
 *	Begins the process of executing proxyAutoConfigurationScript to
 *	determine the correct proxy to use to retrieve targetURL.  The
 *	caller should schedule the returned run loop source; when the
 *	results are found, the caller's callback will be called via the
 *	run loop, passing a valid proxyList and NULL error upon success,
 *	or a NULL proxyList and valid error on failure.  The caller
 *	should invalidate the returned run loop source if it wishes to
 *	terminate the request before completion. The returned
 *	RunLoopSource will be removed from all run loops and modes on
 *	which it was scheduled after the callback returns.
 *  
 *  Parameters:
 *	
 *	proxyAutoConfigurationScript:
 *	  A CFString containing the code of the script to be executed.
 *	
 *	targetURL:
 *	  The URL that should be passed to the autoconfiguration script.
 *	
 *	cb:
 *	  A client callback to notify the caller of completion.
 *	
 *	clientContext:
 *	  a stream context containing a client info object and optionally
 *	  retain / release callbacks for said info object.
 *  
 *  Result:
 *	A CFRunLoopSource which the client can use to schedule execution
 *	of the AutoConfiguration Script.
 *  
 */
CFN_EXPORT CFRunLoopSourceRef 
CFNetworkExecuteProxyAutoConfigurationScript(
  CFStringRef proxyAutoConfigurationScript,
  CFURLRef targetURL,
  CFProxyAutoConfigurationResultCallback cb,
  CFStreamClientContext * clientContext) CF_AVAILABLE(10_5, 2_0);



/*
 *  CFNetworkExecuteProxyAutoConfigurationURL()
 *  
 *  Discussion:
 *	As CFNetworkExecuteProxyAutoConfigurationScript(), above, except
 *	that CFNetworkExecuteProxyAutoConfigurationURL will additionally
 *	download the contents of proxyAutoConfigURL, convert it to a
 *	JavaScript string, and then execute that script.
 *  Ownership for the returned CFRunLoopSourceRef follows the copy rule, 
 *  the client is responsible for releasing the object.
 *  
 */
CFN_EXPORT CFRunLoopSourceRef 
CFNetworkExecuteProxyAutoConfigurationURL(
  CFURLRef proxyAutoConfigURL,
  CFURLRef targetURL,
  CFProxyAutoConfigurationResultCallback cb,
  CFStreamClientContext * clientContext) CF_AVAILABLE(10_5, 2_0);


/*
 *  kCFProxyTypeKey
 *  
 *  Discussion:
 *	Key for the type of proxy being represented; value will be one of
 *	the kCFProxyType constants listed below.
 *  
 */
CFN_EXPORT const CFStringRef kCFProxyTypeKey CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFProxyHostNameKey
 *  
 *  Discussion:
 *	Key for the proxy's hostname; value is a CFString.  Note that
 *	this may be an IPv4 or IPv6 dotted-IP string.
 *  
 */
CFN_EXPORT const CFStringRef kCFProxyHostNameKey CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFProxyPortNumberKey
 *  
 *  Discussion:
 *	Key for the proxy's port number; value is a CFNumber specifying
 *	the port on which to contact the proxy
 *  
 */
CFN_EXPORT const CFStringRef kCFProxyPortNumberKey CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFProxyAutoConfigurationURLKey
 *  
 *  Discussion:
 *	Key for the proxy's PAC file location; this key is only present
 *	if the proxy's type is kCFProxyTypeAutoConfigurationURL.  Value
 *	is a CFURL specifying the location of a proxy auto-configuration
 *	file
 *  
 */
CFN_EXPORT const CFStringRef kCFProxyAutoConfigurationURLKey CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFProxyAutoConfigurationJavaScriptKey
 *  
 *  Discussion:
 *	Key for the proxy's PAC script
 *	The value is a CFString that contains the full JavaScript soure text for the PAC file.
 *  
 */
CFN_EXPORT const CFStringRef kCFProxyAutoConfigurationJavaScriptKey CF_AVAILABLE(10_7, 3_0);


/*
 *  kCFProxyUsernameKey
 *  
 *  Discussion:
 *	Key for the username to be used with the proxy; value is a
 *	CFString. Note that this key will only be present if the username
 *	could be extracted from the information passed in.  No external
 *	credential stores (like the Keychain) are consulted.
 *  
 */
CFN_EXPORT const CFStringRef kCFProxyUsernameKey CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFProxyPasswordKey
 *  
 *  Discussion:
 *	Key for the password to be used with the proxy; value is a
 *	CFString. Note that this key will only be present if the username
 *	could be extracted from the information passed in.  No external
 *	credential stores (like the Keychain) are consulted.
 *  
 */
CFN_EXPORT const CFStringRef kCFProxyPasswordKey CF_AVAILABLE(10_5, 2_0);

/* 
	Possible values for kCFProxyTypeKey:
	kCFProxyTypeNone - no proxy should be used; contact the origin server directly
	kCFProxyTypeHTTP - the proxy is an HTTP proxy
	kCFProxyTypeHTTPS - the proxy is a tunneling proxy as used for HTTPS
	kCFProxyTypeSOCKS - the proxy is a SOCKS proxy
	kCFProxyTypeFTP - the proxy is an FTP proxy
	kCFProxyTypeAutoConfigurationURL - the proxy is specified by a proxy autoconfiguration (PAC) file
*/

/*
 *  kCFProxyTypeNone
 *  
 */
CFN_EXPORT const CFStringRef kCFProxyTypeNone CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFProxyTypeHTTP
 *  
 */
CFN_EXPORT const CFStringRef kCFProxyTypeHTTP CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFProxyTypeHTTPS
 *  
 */
CFN_EXPORT const CFStringRef kCFProxyTypeHTTPS CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFProxyTypeSOCKS
 *  
 */
CFN_EXPORT const CFStringRef kCFProxyTypeSOCKS CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFProxyTypeFTP
 *  
 */
CFN_EXPORT const CFStringRef kCFProxyTypeFTP CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFProxyTypeAutoConfigurationURL
 *  
 */
CFN_EXPORT const CFStringRef kCFProxyTypeAutoConfigurationURL CF_AVAILABLE(10_5, 2_0);

/*
 *  kCFProxyTypeAutoConfigurationJavaScript
 *
 */
CFN_EXPORT const CFStringRef kCFProxyTypeAutoConfigurationJavaScript CF_AVAILABLE(10_7, 3_0);
	
/*
 *  kCFProxyAutoConfigHTTPResponse
 *  
 */
CFN_EXPORT const CFStringRef kCFProxyAutoConfigurationHTTPResponseKey CF_AVAILABLE(10_5, 2_0);
	

#if TARGET_OS_MAC
/*
 *  kCFNetworkProxiesExceptionsList
 *  
 *  Discussion:
 *	Key for the list of host name patterns that should bypass the proxy; value is a
 *	CFArray of CFStrings.  
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesExceptionsList CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesExcludeSimpleHostnames
 *  
 *  Discussion:
 *	Key whose value indicates if simple hostnames will be excluded; value is a
 *	CFNumber.  Simple hostnames will be excluded if the key is present and has a 
 *	non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesExcludeSimpleHostnames CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesFTPEnable
 *  
 *  Discussion:
 *	Key for the enabled status of the ftp proxy; value is a
 *	CFNumber.  The proxy is enabled if the key is present and has a non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesFTPEnable CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesFTPPassive
 *  
 *  Discussion:
 *	Key for the state of passive mode for the ftp proxy; value is a
 *	CFNumber.  A value of one indicates that passive mode is enabled, a value
 *	of zero indicates that passive mode is not enabled.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesFTPPassive CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesFTPPort
 *  
 *  Discussion:
 *	Key for the port number associated with the ftp proxy; value is a
 *	CFNumber which is the port number.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesFTPPort CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesFTPProxy
 *  
 *  Discussion:
 *	Key for the host name associated with the ftp proxy; value is a
 *	CFString which is the proxy host name.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesFTPProxy CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesGopherEnable
 *  
 *  Discussion:
 *	Key for the enabled status of the gopher proxy; value is a
 *	CFNumber.  The proxy is enabled if the key is present and has a non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesGopherEnable CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesGopherPort
 *  
 *  Discussion:
 *	Key for the port number associated with the gopher proxy; value is a
 *	CFNumber which is the port number.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesGopherPort CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesGopherProxy
 *  
 *  Discussion:
 *	Key for the host name associated with the gopher proxy; value is a
 *	CFString which is the proxy host name.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesGopherProxy CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesHTTPEnable
 *  
 *  Discussion:
 *	Key for the enabled status of the HTTP proxy; value is a
 *	CFNumber.  The proxy is enabled if the key is present and has a non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesHTTPEnable CF_AVAILABLE(10_6, 2_0);

/*
 *  kCFNetworkProxiesHTTPPort
 *  
 *  Discussion:
 *	Key for the port number associated with the HTTP proxy; value is a
 *	CFNumber which is the port number.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesHTTPPort CF_AVAILABLE(10_6, 2_0);

/*
 *  kCFNetworkProxiesHTTPProxy
 *  
 *  Discussion:
 *	Key for the host name associated with the HTTP proxy; value is a
 *	CFString which is the proxy host name.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesHTTPProxy CF_AVAILABLE(10_6, 2_0);

/*
 *  kCFNetworkProxiesHTTPSEnable
 *  
 *  Discussion:
 *	Key for the enabled status of the HTTPS proxy; value is a
 *	CFNumber.  The proxy is enabled if the key is present and has a non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesHTTPSEnable CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesHTTPSPort
 *  
 *  Discussion:
 *	Key for the port number associated with the HTTPS proxy; value is a
 *	CFNumber which is the port number.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesHTTPSPort CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesHTTPSProxy
 *  
 *  Discussion:
 *	Key for the host name associated with the HTTPS proxy; value is a
 *	CFString which is the proxy host name.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesHTTPSProxy CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesRTSPEnable
 *  
 *  Discussion:
 *	Key for the enabled status of the RTSP proxy; value is a
 *	CFNumber.  The proxy is enabled if the key is present and has a non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesRTSPEnable CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesRTSPPort
 *  
 *  Discussion:
 *	Key for the port number associated with the RTSP proxy; value is a
 *	CFNumber which is the port number.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesRTSPPort CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesRTSPProxy
 *  
 *  Discussion:
 *	Key for the host name associated with the RTSP proxy; value is a
 *	CFString which is the proxy host name.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesRTSPProxy CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesSOCKSEnable
 *  
 *  Discussion:
 *	Key for the enabled status of the SOCKS proxy; value is a
 *	CFNumber.  The proxy is enabled if the key is present and has a non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesSOCKSEnable CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesSOCKSPort
 *  
 *  Discussion:
 *	Key for the port number associated with the SOCKS proxy; value is a
 *	CFNumber which is the port number.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesSOCKSPort CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesSOCKSProxy
 *  
 *  Discussion:
 *	Key for the host name associated with the SOCKS proxy; value is a
 *	CFString which is the proxy host name.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesSOCKSProxy CF_AVAILABLE(10_6, NA);

/*
 *  kCFNetworkProxiesProxyAutoConfigEnable
 *  
 *  Discussion:
 *	Key for the enabled status ProxyAutoConfig (PAC); value is a
 *	CFNumber.  ProxyAutoConfig is enabled if the key is present and has a non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesProxyAutoConfigEnable	CF_AVAILABLE(10_6, 2_0);

/*
 *  kCFNetworkProxiesProxyAutoConfigURLString
 *  
 *  Discussion:
 *	Key for the url which indicates the location of the ProxyAutoConfig (PAC) file; value is a
 *	CFString which is url for the PAC file.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesProxyAutoConfigURLString CF_AVAILABLE(10_6, 2_0);

/*
 * kCFNetworkProxiesProxyAutoConfigJavaScript
 *
 * Discussion:
 * Key for the string which is the full JavaScript source of the ProxyAutoConfig (PAC) script;  value is a
 * CFString with is the full text source of the PAC script.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesProxyAutoConfigJavaScript	CF_AVAILABLE(10_7, 3_0);
	
/*
 *  kCFNetworkProxiesProxyAutoDiscoveryEnable
 *  
 *  Discussion:
 *	Key for the enabled status of proxy auto discovery; value is a
 *	CFNumber.  Proxy auto discovery is enabled if the key is present and has a non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesProxyAutoDiscoveryEnable CF_AVAILABLE(10_6, NA);
#endif // TARGET_OS_MAC

CF_ASSUME_NONNULL_END
CF_EXTERN_C_END

#endif /* __CFPROXYSUPPORT__ */

// ==========  CFNetwork.framework/Headers/CFFTPStream.h
/*
	 File:	   CFNetwork/CFFTPStream.h
 
	 Contains:   CoreFoundation FTP stream header
  
	 Copyright:  Copyright (c) 2001-2013 Apple Inc. All rights reserved.
 
	 Bugs?:	  For bug reports, consult the following page on
				 the World Wide Web:
 
					 http://developer.apple.com/bugreporter/
 
*/
#ifndef __CFFTPSTREAM__
#define __CFFTPSTREAM__

#ifndef __CFNETWORKDEFS__
#include <CFNetwork/CFNetworkDefs.h>
#endif

#ifndef __CFSTREAM__
#include <CoreFoundation/CFStream.h>
#endif


#if PRAGMA_ONCE
#pragma once
#endif

CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/*
 *  kCFStreamErrorDomainFTP
 *  
 *  Discussion:
 *	Result code returned by FTP server
 *
 */
CFN_EXPORT const SInt32 kCFStreamErrorDomainFTP CF_AVAILABLE(10_3, 2_0);


/*
 *  FTP Stream Property keys.
 *  These keys can be passed to the stream property "set/get" functions,
 *  such as CFReadStreamSetProperty/CFReadStreamCopyProperty, or to a
 *  CFDictionary creator or an item accessor/mutator.  The comment before
 *  each key declaration (treated as definition) indicates the value type
 *  of the property.
 */


/*
 *  kCFStreamPropertyFTPUserName
 *  
 *  Discussion:
 *	Stream property key, for both set and copy operations.  CFString
 *	type to hold login user name.  Don't set this property if you
 *	want anonymous FTP.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyFTPUserName CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  kCFStreamPropertyFTPPassword
 *  
 *  Discussion:
 *	Stream property key, for both set and copy operations. CFString
 *	type to hold login password.  Don't set this property if you want
 *	anonymous FTP.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyFTPPassword CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  kCFStreamPropertyFTPUsePassiveMode
 *  
 *  Discussion:
 *	Stream property key, for both set and copy operations. CFBoolean
 *	type. kCFBooleanTrue means use passive mode, kCFBooleanFalse
 *	otherwise
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyFTPUsePassiveMode CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  kCFStreamPropertyFTPResourceSize
 *  
 *  Discussion:
 *	Stream property key, for read stream copy operations.  CFNumber
 *	of kCFNumberLongLongType to hold resource size in bytes.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyFTPResourceSize CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  kCFStreamPropertyFTPFetchResourceInfo
 *  
 *  Discussion:
 *	Stream property key, for both set and copy operations.  CFBoolean
 *	type.  TRUE means that resource info, such as size, must be
 *	provided before download starts at higher cost.  Don't set if
 *	resource size/other info is unnecessary.  Initially, only
 *	resource size is implemented.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyFTPFetchResourceInfo CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  kCFStreamPropertyFTPFileTransferOffset
 *  
 *  Discussion:
 *	Stream property key, for both set and copy operations.  CFNumber
 *	of kCFNumberLongLongType for the file offset to start transfer at.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyFTPFileTransferOffset CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  kCFStreamPropertyFTPAttemptPersistentConnection
 *  
 *  Discussion:
 *	Stream property key, for both set and copy operations.  CFBoolean
 *	type.  TRUE by default, set to FALSE to avoid reusing existing
 *	server connections.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyFTPAttemptPersistentConnection CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  kCFStreamPropertyFTPProxy
 *  
 *  Discussion:
 *	Stream property key, for both set and copy operations. 
 *	CFDictionary type that holds key-value pairs of proxy dictionary.
 *	The dictionary returned by SystemConfiguration can also be
 *	passed directly as the value.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyFTPProxy CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  kCFStreamPropertyFTPProxyHost
 *  
 *  Discussion:
 *	Stream property key or FTP Proxy dictionary key, for both set and
 *	copy operations.  It matches kSCPropNetProxiesFTPProxy defined in
 *	SCSchemaDefinitions.h.  CFString for proxy server host name. 
 *	This property can be set and copied individually or via a
 *	CFDictionary.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyFTPProxyHost CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  kCFStreamPropertyFTPProxyPort
 *  
 *  Discussion:
 *	Stream property key or FTP Proxy dictionary key, for both set and
 *	copy operations.  It matches kSCPropNetProxiesFTPPort defined in
 *	SCSchemaDefinitions.h.  CFNumber of kCFNumberIntType for proxy
 *	server port number.  This property can be set and copied
 *	individually or via a CFDictionary.
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyFTPProxyPort CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");

/*
 *  kCFStreamPropertyFTPProxyUser
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyFTPProxyUser CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");

/*
 *  kCFStreamPropertyFTPProxyPassword
 *  
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyFTPProxyPassword CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  CFDictionary keys for resource information.  The information is
 *  extracted from a line of the directory list by function
 *  CFFTPCreateParsedResourceListing.
 */


/*
 *  kCFFTPResourceMode
 *  
 *  Discussion:
 *	CFDictionary key, for get value operation.  CFNumber to hold the
 *	resource access permission defined in sys/types.h.
 *  
 */
CFN_EXPORT const CFStringRef kCFFTPResourceMode CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  kCFFTPResourceName
 *  
 *  Discussion:
 *	CFDictionary key, for get value operation.  CFString that holds
 *	the resource name.
 *  
 */
CFN_EXPORT const CFStringRef kCFFTPResourceName CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  kCFFTPResourceOwner
 *  
 *  Discussion:
 *	CFDictionary key, for get value operation.  CFString that holds
 *	the resource owner's name.
 *  
 */
CFN_EXPORT const CFStringRef kCFFTPResourceOwner CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  kCFFTPResourceGroup
 *  
 *  Discussion:
 *	CFDictionary key, for get value operation.  CFString to hold the
 *	name of the group that shares the resource.
 *  
 */
CFN_EXPORT const CFStringRef kCFFTPResourceGroup CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  kCFFTPResourceLink
 *  
 *  Discussion:
 *	CFDictionary key, for get value operation.  CFString to hold
 *	symbolic link information.  If the item is a symbolic link the
 *	string will contain the path to the item the link references.
 *  
 */
CFN_EXPORT const CFStringRef kCFFTPResourceLink CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  kCFFTPResourceSize
 *  
 *  Discussion:
 *	CFDictionary key, for get value operation.  CFNumber of
 *	kCFNumberLongLongType to hold the resource length in bytes.
 *  
 */
CFN_EXPORT const CFStringRef kCFFTPResourceSize CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  kCFFTPResourceType
 *  
 *  Discussion:
 *	CFDictionary key, for get value operation.  CFNumber to hold the
 *	resource type as defined in sys/dirent.h.
 *  
 */
CFN_EXPORT const CFStringRef kCFFTPResourceType CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  kCFFTPResourceModDate
 *  
 *  Discussion:
 *	CFDictionary key, for get value operation.  CFDate to hold the
 *	last modification date and time information.
 *  
 */
CFN_EXPORT const CFStringRef kCFFTPResourceModDate CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


/*
 *  CFReadStreamCreateWithFTPURL()
 *  
 *  DEPRECATED: Use NSURLSessionAPI for ftp requests
 *
 *  Discussion:
 *	Create an FTP read stream for downloading operation from an FTP
 *	URL. If the URL refers to a directory, the stream is a filtered
 *	line-at-a-time read stream corresponding to the listing results
 *	provided by the server. If it's a file, then the stream is a
 *	regular read stream providing the data for that file.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  A pointer to the CFAllocator which should be used to allocate
 *	  memory for the CF read stream and its storage for values. If
 *	  this reference is not a valid CFAllocator, the behavior is
 *	  undefined.
 *	
 *	ftpURL:
 *	  A pointer to a CFURL structure created by CFURLCreateWithString
 *	  function.  If this parameter is not a pointer to a valid CFURL
 *	  structure, the behavior is undefined.
 *  
 *  Result:
 *	A pointer to the CF read stream created, or NULL if failed. It is
 *	caller's responsibilty to release the memory allocated for the
 *	read stream.
 *  
 */
CFN_EXPORT CFReadStreamRef 
CFReadStreamCreateWithFTPURL(CFAllocatorRef __nullable alloc, CFURLRef ftpURL) CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");



/*
 *  CFFTPCreateParsedResourceListing()
 *  
 *  DEPRECATED: Use NSURLSessionAPI for ftp requests
 *
 *  Discussion:
 *	Parse a line of file or folder listing of Unix format, and store
 *	the extracted result in a CFDictionary.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  A pointer to the CFAllocator which should be used to allocate
 *	  memory for the CFDictionary to hold resource info.  If this
 *	  reference is not a valid CFAllocator, the behavior is undefined.
 *	
 *	buffer:
 *	  A pointer to a buffer that may hold lines of resource listing,
 *	  but only the first line starting from buffer[0] will be parsed
 *	  each call.
 *	
 *	bufferLength:
 *	  The maximum buffer size in bytes started from the location
 *	  pointed by "buffer."
 *	
 *	parsed:
 *	  A pointer to a CFDictionary pointer.  The dictionary holds the
 *	  extracted resource information.  When parsing fails, a NULL
 *	  pointer will be returned.  It is caller's responsibilty to
 *	  release the memory allocated for the dictionary.
 *  
 *  Result:
 *	The number of bytes consumed from buffer, 0 if there are not
 *	enough bytes, or -1 if a parse failure occurs.
 *  
 */
CFN_EXPORT CFIndex 
CFFTPCreateParsedResourceListing(CFAllocatorRef __nullable alloc, const UInt8 *buffer, CFIndex bufferLength, CFDictionaryRef __nullable *  __nullable parsed) CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");



/*
 *  CFWriteStreamCreateWithFTPURL()
 *
 *  DEPRECATED: Use NSURLSessionAPI for ftp requests
 *
 *  Discussion:
 *	Create an FTP write stream for uploading operation to a FTP URL.
 *	If the URL specifies a directory, the open will be followed by a
 *	close event/state and the directory will have been created. 
 *	Intermediary directory structure is not created.
 *  
 *  Mac OS X threading:
 *	Thread safe
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  A pointer to the CFAllocator which should be used to allocate
 *	  memory for the CF read stream and its storage for values. If
 *	  this reference is not a valid CFAllocator, the behavior is
 *	  undefined.
 *	
 *	ftpURL:
 *	  A pointer to a CFURL structure created by CFURLCreateWithString
 *	  function.  If this parameter is not a pointer to a valid CFURL
 *	  structure, the behavior is undefined.
 *  
 *  Result:
 *	A pointer to the CF write stream created, or NULL if failed. It
 *	is caller's responsibilty to release the memory allocated for the
 *	write stream.
 *  
 */
CFN_EXPORT CFWriteStreamRef
CFWriteStreamCreateWithFTPURL(CFAllocatorRef __nullable alloc, CFURLRef ftpURL) CF_DEPRECATED(10_3, 10_11, 2_0, 9_0 , "Use NSURLSessionAPI for ftp requests");


CF_ASSUME_NONNULL_END
CF_EXTERN_C_END

#endif /* __CFFTPSTREAM__ */

