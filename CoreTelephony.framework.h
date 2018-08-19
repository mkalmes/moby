// ==========  CoreTelephony.framework/Headers/CTCallCenter.h
/*
 *  CTCallCenter.h
 *  CFTelephony
 *
 *  Copyright 2010 Apple, Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

@class CTCall;

NS_ASSUME_NONNULL_BEGIN

CORETELEPHONY_CLASS_DEPRECATED(4_0, 10_0, "Replaced by CXCallObserver from CallKit.framework")
@interface CTCallCenter : NSObject
{
@private
    void *_server;

    NSSet *_currentCalls;
    void (^_callEventHandler)(CTCall *);
}

/*
 * currentCalls
 *
 * Discussion:
 *   An array containing CTCall objects for all calls that are currently
 *   in progress. If no calls are active, this will be nil.
 *   
 */
@property(readonly, retain, nullable) NSSet<CTCall*> *currentCalls __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

/*
 * callEventHandler
 *
 * Discussion:
 *   A block that will be dispatched on the default priority global dispatch
 *   queue when a new call event occurs. Set this property to a block
 *   that is defined in your application to handle call events.
 */
@property(nonatomic, copy, nullable) void (^callEventHandler)(CTCall*) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

@end

NS_ASSUME_NONNULL_END
// ==========  CoreTelephony.framework/Headers/CTTelephonyNetworkInfo.h
/*
 *  CTTelephonyNetworkInfo.h
 *  CoreTelephony
 *
 *  Copyright 2009 Apple, Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * CTRadioAccessTechnologyDataTechnologyDidChangeNotification
 *
 * Description:
 *     A NSNotification broadcast when radio access technology changes
 */
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyDidChangeNotification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

/*
 * Radio Access Technology values
 */
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyGPRS          __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyEdge          __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyWCDMA         __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyHSDPA         __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyHSUPA         __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyCDMA1x        __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyCDMAEVDORev0  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyCDMAEVDORevA  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyCDMAEVDORevB  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyeHRPD         __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyLTE           __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

@class CTCarrier;

/*
 *  CTTelephonyNetworkInfo
 *  
 *  Discussion:
 *    The CTTelephonyNetworkInfo object is your entry point to the telephony service.
 */
CORETELEPHONY_CLASS_AVAILABLE(4_0)
@interface CTTelephonyNetworkInfo : NSObject

/*
 * subscriberCellularProvider
 *
 * Discussion:
 *   A CTCarrier object that contains information about the subscriber's
 *   home cellular service provider.
 */
@property(readonly, retain, nullable) CTCarrier *subscriberCellularProvider __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

/*
 * subscriberCellularProviderDidUpdateNotifier
 *
 * Discussion:
 *   A block that will be dispatched on the default priority global dispatch
 *   queue when the subscriber's cellular provider information updates. Set
 *   this property to a block that is defined in your application to
 *   receive the newly updated information.
 */
@property(nonatomic, copy, nullable) void (^subscriberCellularProviderDidUpdateNotifier)(CTCarrier*) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

/*
 * currentRadioAccessTechnology
 *
 * Discussion:
 *   The current radio access technology the device is registered with. May be NULL
 *   if device is not registered on any network.
 */
@property (nonatomic, readonly, retain, nullable) NSString* currentRadioAccessTechnology __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

@end

NS_ASSUME_NONNULL_END

// ==========  CoreTelephony.framework/Headers/CTCellularData.h
//
//  CTCellularData.h
//  CFTelephony
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <CoreTelephony/CoreTelephonyDefines.h>

typedef NS_ENUM(NSUInteger, CTCellularDataRestrictedState) {
	kCTCellularDataRestrictedStateUnknown,
	kCTCellularDataRestricted,
	kCTCellularDataNotRestricted
};

typedef void (^CellularDataRestrictionDidUpdateNotifier)(CTCellularDataRestrictedState);

NS_ASSUME_NONNULL_BEGIN

CORETELEPHONY_CLASS_AVAILABLE(9_0)
@interface CTCellularData : NSObject
/*
 * cellularDataRestrictionDidUpdateNotifier
 *
 * A block that will be dispatched on the default priority global dispatch queue the first time 
 * app sets the callback handler and everytime there is a change in cellular data allowed policy 
 * for the app.
 */

@property (copy, nullable) CellularDataRestrictionDidUpdateNotifier cellularDataRestrictionDidUpdateNotifier __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_9_0);
@property (nonatomic, readonly) CTCellularDataRestrictedState restrictedState __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_9_0);
@end

NS_ASSUME_NONNULL_END

// ==========  CoreTelephony.framework/Headers/CoreTelephonyDefines.h
/*
 *  CoreTelephonyDefines.h
 *  CFTelephony
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

// Macros to export a symbol from the CoreTelephony library
#ifndef __CORETELEPHONY_DEFINES_H__
#define __CORETELEPHONY_DEFINES_H__

#ifdef __cplusplus
#define CORETELEPHONY_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define CORETELEPHONY_EXTERN   extern __attribute__((visibility ("default")))
#endif

#define	CORETELEPHONY_EXTERN_CLASS	__attribute__((visibility("default")))
#define CORETELEPHONY_CLASS_AVAILABLE(_iphoneIntro) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(NA, _iphoneIntro)
#define CORETELEPHONY_CLASS_DEPRECATED(_introOS, _deprecatedOS, _msg) __attribute__((visibility("default"))) NS_CLASS_DEPRECATED_IOS(_introOS, _deprecatedOS, _msg)

#include <CoreFoundation/CoreFoundation.h>	// need this for SInt32

enum {
	kCTErrorDomainNoError	= 0,
	kCTErrorDomainPOSIX		= 1,	/* POSIX error listed in sys/errno.h */
	kCTErrorDomainMach				/* mach error listed in mach/error.h */
};

typedef struct {
	SInt32 domain;
	SInt32 error;
} CTError;
		
#endif
// ==========  CoreTelephony.framework/Headers/CTSubscriberInfo.h
/*
 *  CTSubscriberInfo.h
 *  CFTelephony
 *
 *  Copyright 2012 Apple, Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

#import "CTSubscriber.h"

NS_ASSUME_NONNULL_BEGIN

CORETELEPHONY_CLASS_AVAILABLE(6_0)
@interface CTSubscriberInfo : NSObject

+ (CTSubscriber*) subscriber;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreTelephony.framework/Headers/CTSubscriber.h
/*
 *  CTSubscriber.h
 *  CoreTelephony
 *
 *  Copyright 2012 Apple, Inc.. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * CTSubscriberTokenRefreshed
 *
 * Description:
 *     The name of the NSNotification sent when the carrier token is available.
 */
CORETELEPHONY_EXTERN NSString * const CTSubscriberTokenRefreshed  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

CORETELEPHONY_CLASS_AVAILABLE(7_0)
@interface CTSubscriber : NSObject

/*
 * carrierToken
 *
 * Description:
 *     A data blob containing authorization information about the subscriber.
 *     This API has been deprecated but continues to work as it did in iOS 10.
 *     In a future release, this API will only return nil.
 *
 *     May return nil if no token is available.
 */
@property (nonatomic, readonly, retain, nullable) NSData* carrierToken
__API_UNAVAILABLE(macos, watchos, tvos)
__API_DEPRECATED("Deprecated and will always return nil in a future release.", ios(7.0, 11.0))
;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreTelephony.framework/Headers/CTCall.h
/*
 *  CTCall.h
 *  CFTelephony
 *
 *  Copyright 2010 Apple, Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

NS_ASSUME_NONNULL_BEGIN

CORETELEPHONY_EXTERN NSString * const CTCallStateDialing  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
CORETELEPHONY_EXTERN NSString * const CTCallStateIncoming  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
CORETELEPHONY_EXTERN NSString * const CTCallStateConnected  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
CORETELEPHONY_EXTERN NSString * const CTCallStateDisconnected  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

CORETELEPHONY_CLASS_AVAILABLE(4_0)
@interface CTCall : NSObject
{
@private
    NSString *_callState;
    NSString *_callID;
}

/*
 * callState
 *
 * Description:
 *     An NSString constant that describes the state of this call. The initial state
 *     will be either CTCallStateDialing or CTCallStateIncoming, will transition
 *     to CTCallStateConnected when the call is established with all parties 
 *     involved and will move to CTCallStateDisconnected when this call is terminated.
 */
@property(nonatomic, readonly, copy) NSString *callState  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

/*
 * callID
 *
 * Description:
 *     A unique identifier for this call to be used by clients to differentiate
 *     multiple active calls.
 */
@property(nonatomic, readonly, copy) NSString *callID  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

@end

NS_ASSUME_NONNULL_END
// ==========  CoreTelephony.framework/Headers/CTCarrier.h
/*
 *  CTCarrier.h
 *  CoreTelephony
 *
 *  Copyright 2009 Apple, Inc.. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

NS_ASSUME_NONNULL_BEGIN

CORETELEPHONY_CLASS_AVAILABLE(4_0)
@interface CTCarrier : NSObject

/*
 * carrierName
 *
 * Discussion:
 *   An NSString containing the name of the subscriber's cellular service provider.
 */
@property (nonatomic, readonly, retain, nullable) NSString *carrierName __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

/*
 * mobileCountryCode
 *
 * Discussion:
 *   An NSString containing the mobile country code for the subscriber's 
 *   cellular service provider, in its numeric representation
 */
@property (nonatomic, readonly, retain, nullable) NSString *mobileCountryCode __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

/*
 * mobileNetworkCode
 *
 * Discussion:
 *   An NSString containing the  mobile network code for the subscriber's 
 *   cellular service provider, in its numeric representation
 */
@property (nonatomic, readonly, retain, nullable) NSString *mobileNetworkCode __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

/*
 * isoCountryCode
 *
 * Discussion:
 *   Returns an NSString object that contains country code for
 *   the subscriber's cellular service provider, represented as an ISO 3166-1
 *   country code string
 */

@property (nonatomic, readonly, retain, nullable) NSString* isoCountryCode __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

/*
 * allowsVOIP
 *
 * Discussion:
 *   A BOOL value that is YES if this carrier allows VOIP calls to be
 *   made on its network, NO otherwise.
 */

@property (nonatomic, readonly, assign) BOOL allowsVOIP __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

@end

NS_ASSUME_NONNULL_END

