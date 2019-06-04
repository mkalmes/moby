// ==========  IncomingCallNotifications.framework/Headers/ICTypes.h
//
//  ICTypes.h
//  IncomingCallNotifications
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <IncomingCallNotifications/ICBase.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, ICDeclineReason) {
    ICDeclineReasonGeneric,    // A generic decline, for example the decline button was pressed.
    ICDeclineReasonCancelled,  // The notification was cancelled.
    ICDeclineReasonUserBusy,   // The user was busy, such as another incoming call already being present.
    ICDeclineReasonUnanswered, // The notification was never responded to, and was automatically declined.
} API_AVAILABLE(ios(13.0));

NS_ASSUME_NONNULL_END
// ==========  IncomingCallNotifications.framework/Headers/ICHandle.h
//
//  ICHandle.h
//  IncomingCallNotifications
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <IncomingCallNotifications/ICBase.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, ICHandleType) {
    ICHandleTypeGeneric = 1,
    ICHandleTypePhoneNumber = 2,
    ICHandleTypeEmailAddress = 3,
} API_AVAILABLE(ios(13.0));

IC_CLASS_AVAILABLE(ios(13.0))
@interface ICHandle : NSObject <NSCopying>

@property (nonatomic, readonly) ICHandleType type;
@property (nonatomic, readonly, copy) NSString *value;

- (instancetype)initWithType:(ICHandleType)type value:(NSString *)value NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

- (BOOL)isEqualToHandle:(ICHandle *)handle;

@end

NS_ASSUME_NONNULL_END
// ==========  IncomingCallNotifications.framework/Headers/IncomingCallNotifications.h
//
//  IncomingCallNotifications.h
//  IncomingCallNotifications
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <IncomingCallNotifications/ICBase.h>
#import <IncomingCallNotifications/ICTypes.h>

#import <IncomingCallNotifications/ICHandle.h>

#import <IncomingCallNotifications/ICNotification.h>
#import <IncomingCallNotifications/ICNotificationManagerConfiguration.h>
#import <IncomingCallNotifications/ICNotificationManager.h>
// ==========  IncomingCallNotifications.framework/Headers/ICNotificationManagerConfiguration.h
//
//  ICNotificationManagerConfiguration.h
//  IncomingCallNotifications
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <IncomingCallNotifications/ICBase.h>
#import <IncomingCallNotifications/ICTypes.h>

NS_ASSUME_NONNULL_BEGIN

/// The configuration used for the notification manager. Each configuration is unique, so it is advised that you don't cache this configuration and use it for multiple notification manager instances. Instead, create a new one each time you initialize the notification manager.
IC_CLASS_AVAILABLE(ios(13.0))
@interface ICNotificationManagerConfiguration : NSObject <NSCopying>

/// The localized display name to use when showing the notification. If this is nil, the display name of your application will be used instead.
@property (nonatomic, readwrite, copy, nullable) NSString *localizedDisplayName;

@end

NS_ASSUME_NONNULL_END
// ==========  IncomingCallNotifications.framework/Headers/ICNotification.h
//
//  ICNotification.h
//  IncomingCallNotifications
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <IncomingCallNotifications/ICBase.h>
#import <IncomingCallNotifications/ICTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class ICHandle;

IC_CLASS_AVAILABLE(ios(13.0))
@interface ICNotification : NSObject <NSCopying>

- (instancetype)initWithUUID:(NSUUID *)identifier handle:(ICHandle *)handle NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

/// The unique identifier for this notification. This can be used to map this notification back to the sending call in your application.
@property (nonatomic, readonly, copy) NSUUID *identifier;

/// The handle for the person that will be displayed on the incoming call notification.
@property (nonatomic, readonly, copy) ICHandle *handle;

/// Whether or not this notification is for a call that supports video.
@property (nonatomic, readwrite, assign, getter=isVideo) BOOL video;

@end

NS_ASSUME_NONNULL_END
// ==========  IncomingCallNotifications.framework/Headers/ICNotificationManager.h
//
//  ICNotificationManager.h
//  IncomingCallNotifications
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <IncomingCallNotifications/ICBase.h>
#import <IncomingCallNotifications/ICTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class ICNotification;
@class ICNotificationManagerConfiguration;
@class ICNotificationManager;

@protocol ICNotificationManagerDelegate <NSObject>

@optional

/// Called when a notification is responded to by accepting it (e.g. choosing to accept the incoming call). Your application will be brought to the foreground and this callback will be invoked on the delegate.
- (void)notificationManager:(ICNotificationManager *)notificationManager didAcceptNotification:(ICNotification *)notification;

/// Called when a notification is responded to by declining it (e.g. the users declines the incoming call notification).
- (void)notificationManager:(ICNotificationManager *)notificationManager didDeclineNotification:(ICNotification *)notification reason:(ICDeclineReason)reason;

@end

IC_CLASS_AVAILABLE(ios(13.0))
@interface ICNotificationManager : NSObject

- (instancetype)initWithConfiguration:(ICNotificationManagerConfiguration *)configuration NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

/// Set delegate and optional queue for delegate callbacks to be performed on.
/// A nil queue implies that delegate callbacks should happen on the main queue. The delegate is stored weakly
- (void)setDelegate:(nullable id<ICNotificationManagerDelegate>)delegate queue:(nullable dispatch_queue_t)queue;

/// Post an incoming call notification to the system. If there is an error posting the notification, the error will be set in the completion block.
- (void)postNotification:(ICNotification *)notification completion:(void (^_Nullable)(NSError *_Nullable))completion;

/// If an incoming call notification is currently being displayed with this identifier, this cancels the notification. The notification manager's delegate will also get called with a decline reason of ICDeclineReasonCancelled.
- (void)cancelNotificationWithIdentifier:(NSUUID *)identifier;

@end

NS_ASSUME_NONNULL_END
// ==========  IncomingCallNotifications.framework/Headers/ICBase.h
//
//  ICBase.h
//  IncomingCallNotifications
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
#define IC_EXTERN extern "C" __attribute__((visibility("default")))
#else
#define IC_EXTERN extern __attribute__((visibility("default")))
#endif

#define IC_CLASS_AVAILABLE(...) IC_EXTERN API_AVAILABLE(__VA_ARGS__)

NS_ASSUME_NONNULL_END
