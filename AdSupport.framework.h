// ==========  AdSupport.framework/Headers/AdSupport.h
/*
    File: AdSupport.h
 
    Framework: AdSupport
 
    Copyright (c) 2012, Apple Inc. All rights reserved.
*/

#ifndef AdSupport_AdSupport_h
#define AdSupport_AdSupport_h

#import <AdSupport/ASIdentifierManager.h>

#endif// ==========  AdSupport.framework/Headers/ASIdentifierManager.h
/*
 File: ASIdentifierManager.h
 
 Framework: AdSupport
 
 Copyright (c) 2012, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <os/availability.h>

NS_CLASS_AVAILABLE(10_14, 6_0)
@interface ASIdentifierManager : NSObject

+ (ASIdentifierManager * _Nonnull)sharedManager;

- (void)clearAdvertisingIdentifier API_UNAVAILABLE(ios, tvos);

@property (nonnull, nonatomic, readonly) NSUUID *advertisingIdentifier;
@property (nonatomic, readonly, getter=isAdvertisingTrackingEnabled) BOOL advertisingTrackingEnabled;


@end
