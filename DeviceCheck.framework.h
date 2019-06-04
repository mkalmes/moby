// ==========  DeviceCheck.framework/Headers/DeviceCheck.h
//
//  DeviceCheck.h
//  DeviceCheck
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DeviceCheck/DCDevice.h>
#import <DeviceCheck/DCError.h>
// ==========  DeviceCheck.framework/Headers/DCError.h
//
//  DCError.h
//  DeviceCheck
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <DeviceCheck/DeviceCheck.h>

NS_ASSUME_NONNULL_BEGIN

extern NSErrorDomain const DCErrorDomain API_AVAILABLE(ios(11.0), macos(10.15), tvos(11.0)) API_UNAVAILABLE(watchos);

typedef NS_ERROR_ENUM(DCErrorDomain, DCError) {
    DCErrorUnknownSystemFailure,
    DCErrorFeatureUnsupported
} API_AVAILABLE(ios(11.0), macos(10.15), tvos(11.0)) API_UNAVAILABLE(watchos);

NS_ASSUME_NONNULL_END

// ==========  DeviceCheck.framework/Headers/DCDevice.h
//
//  DCDevice.h
//  DeviceCheck
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <DeviceCheck/DeviceCheck.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), macos(10.15), tvos(11.0)) API_UNAVAILABLE(watchos)
@interface DCDevice : NSObject

/**
 The current device. 
 */
@property (class, readonly) DCDevice *currentDevice;

/**
 Check if this API is supported on the current device.
 */
@property (getter=isSupported, readonly) BOOL supported;

/**
 Generate a new device token that can be used to get/set the persistent bits for this device.
 This call generates a new value every time.
 */
- (void)generateTokenWithCompletionHandler:(void(^)(NSData * _Nullable token, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
