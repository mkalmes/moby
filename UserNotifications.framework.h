// ==========  UserNotifications.framework/Headers/UNNotificationServiceExtension.h
//
//  UNNotificationServiceExtension.h
//  UserNotifications
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include <Foundation/Foundation.h>

@class UNNotificationRequest;
@class UNNotificationContent;

NS_ASSUME_NONNULL_BEGIN

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(6.0)) __API_UNAVAILABLE(tvos)
@interface UNNotificationServiceExtension : NSObject

// Call contentHandler with the modified notification content to deliver. If the handler is not called before the service's time expires then the unmodified notification will be delivered.
// You are expected to override this method to implement push notification modification.
- (void)didReceiveNotificationRequest:(UNNotificationRequest *)request withContentHandler:(void (^)(UNNotificationContent *contentToDeliver))contentHandler;

// Will be called just before this extension is terminated by the system. You may choose whether to override this method.
- (void)serviceExtensionTimeWillExpire;

@end

NS_ASSUME_NONNULL_END
// ==========  UserNotifications.framework/Headers/UNUserNotificationCenter.h
//
//  UNUserNotificationCenter.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UNNotification;
@class UNNotificationAttachment;
@class UNNotificationCategory;
@class UNNotificationContent;
@class UNNotificationRequest;
@class UNNotificationResponse;
@class UNNotificationSettings;

@protocol UNUserNotificationCenterDelegate;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, UNAuthorizationOptions) {
    UNAuthorizationOptionBadge   = (1 << 0),
    UNAuthorizationOptionSound   = (1 << 1),
    UNAuthorizationOptionAlert   = (1 << 2),
    UNAuthorizationOptionCarPlay = (1 << 3),
    UNAuthorizationOptionCriticalAlert __API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) = (1 << 4),
    UNAuthorizationOptionProvidesAppNotificationSettings __API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) = (1 << 5),
    UNAuthorizationOptionProvisional __API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) = (1 << 6),
    UNAuthorizationOptionAnnouncement __API_AVAILABLE(ios(13.0), watchos(6.0)) __API_UNAVAILABLE(macos, tvos) = (1 << 7),
} __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0));

static const UNAuthorizationOptions UNAuthorizationOptionNone NS_SWIFT_UNAVAILABLE("Use [] instead.") __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0)) = 0;

// UNNotificationRequests can be scheduled using UNUserNotificationCenter. They can also be sent to the device from a server using Apple Push Notification Service. If the application is authorized then the UNNotificationRequest will be used to create a UNNotification and it will be used to notify the user. If the user acts on the UNNotification then a UNNotificationResponse will be sent to the application.

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@interface UNUserNotificationCenter : NSObject

// The delegate can only be set from an application
@property (NS_NONATOMIC_IOSONLY, nullable, weak) id <UNUserNotificationCenterDelegate> delegate;

// Returns YES if the current device supports content extensions
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL supportsContentExtensions;

// The UNUserNotificationCenter for the current application
+ (UNUserNotificationCenter *)currentNotificationCenter;

- (instancetype)init NS_UNAVAILABLE;

// User authorization is required for applications to notify the user using UNUserNotificationCenter via both local and remote notifications.
- (void)requestAuthorizationWithOptions:(UNAuthorizationOptions)options completionHandler:(void (^)(BOOL granted, NSError *__nullable error))completionHandler;

// Notification categories can be used to choose which actions will be displayed on which notifications.
- (void)setNotificationCategories:(NSSet<UNNotificationCategory *> *)categories __API_UNAVAILABLE(tvos);
- (void)getNotificationCategoriesWithCompletionHandler:(void(^)(NSSet<UNNotificationCategory *> *categories))completionHandler __API_UNAVAILABLE(tvos);

// The application's user notification settings
- (void)getNotificationSettingsWithCompletionHandler:(void(^)(UNNotificationSettings *settings))completionHandler;

// Notification requests can be scheduled to notify the user via time and location. See UNNotificationTrigger for more information. Calling -addNotificationRequest: will replace an existing notification request with the same identifier. A notification request with the identifier as an existing delivered notifications will alert for the new notification request and replace the existing delivered notification when it is triggered. The number of pending notification requests that may be scheduled by an application at any one time is limited by the system.
- (void)addNotificationRequest:(UNNotificationRequest *)request withCompletionHandler:(nullable void(^)(NSError *__nullable error))completionHandler;

// Notification requests that are waiting for their trigger to fire
- (void)getPendingNotificationRequestsWithCompletionHandler:(void(^)(NSArray<UNNotificationRequest *> *requests))completionHandler;
- (void)removePendingNotificationRequestsWithIdentifiers:(NSArray<NSString *> *)identifiers;
- (void)removeAllPendingNotificationRequests;

// Notifications that have been delivered and remain in Notification Center. Notifications triggered by location cannot be retrieved, but can be removed.
- (void)getDeliveredNotificationsWithCompletionHandler:(void(^)(NSArray<UNNotification *> *notifications))completionHandler __API_UNAVAILABLE(tvos);
- (void)removeDeliveredNotificationsWithIdentifiers:(NSArray<NSString *> *)identifiers __API_UNAVAILABLE(tvos);
- (void)removeAllDeliveredNotifications __API_UNAVAILABLE(tvos);

@end

typedef NS_OPTIONS(NSUInteger, UNNotificationPresentationOptions) {
    UNNotificationPresentationOptionBadge   = (1 << 0),
    UNNotificationPresentationOptionSound   = (1 << 1),
    UNNotificationPresentationOptionAlert   = (1 << 2),
} __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0));

static const UNNotificationPresentationOptions UNNotificationPresentationOptionNone NS_SWIFT_UNAVAILABLE("Use [] instead.") __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0)) = 0;

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@protocol UNUserNotificationCenterDelegate <NSObject>

@optional

// The method will be called on the delegate only if the application is in the foreground. If the method is not implemented or the handler is not called in a timely manner then the notification will not be presented. The application can choose to have the notification presented as a sound, badge, alert and/or in the notification list. This decision should be based on whether the information in the notification is otherwise visible to the user.
- (void)userNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions options))completionHandler __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0));

// The method will be called on the delegate when the user responded to the notification by opening the application, dismissing the notification or choosing a UNNotificationAction. The delegate must be set before the application returns from application:didFinishLaunchingWithOptions:.
- (void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void(^)(void))completionHandler __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos);

// The method will be called on the delegate when the application is launched in response to the user's request to view in-app notification settings. Add UNAuthorizationOptionProvidesAppNotificationSettings as an option in requestAuthorizationWithOptions:completionHandler: to add a button to inline notification settings view and the notification settings view in Settings. The notification will be nil when opened from Settings.
- (void)userNotificationCenter:(UNUserNotificationCenter *)center openSettingsForNotification:(nullable UNNotification *)notification __API_AVAILABLE(macos(10.14), ios(12.0)) __API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  UserNotifications.framework/Headers/NSString+UserNotifications.h
//
//  NSString+UserNotifications.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSString (UNUserNotificationCenterSupport)

// Use -[NSString localizedUserNotificationStringForKey:arguments:] to provide a string that will be localized at the time that the notification is presented.
+ (NSString *)localizedUserNotificationStringForKey:(NSString *)key arguments:(nullable NSArray *)arguments __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos);

@end

NS_ASSUME_NONNULL_END
// ==========  UserNotifications.framework/Headers/UserNotifications.h
//
//  UserNotifications.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <UserNotifications/NSString+UserNotifications.h>
#import <UserNotifications/UNError.h>
#import <UserNotifications/UNNotification.h>
#import <UserNotifications/UNNotificationAction.h>
#import <UserNotifications/UNNotificationAttachment.h>
#import <UserNotifications/UNNotificationCategory.h>
#import <UserNotifications/UNNotificationContent.h>
#import <UserNotifications/UNNotificationRequest.h>
#import <UserNotifications/UNNotificationResponse.h>
#import <UserNotifications/UNNotificationSettings.h>
#import <UserNotifications/UNNotificationSound.h>
#import <UserNotifications/UNNotificationTrigger.h>
#import <UserNotifications/UNUserNotificationCenter.h>

#import <UserNotifications/UNNotificationServiceExtension.h>
// ==========  UserNotifications.framework/Headers/UNNotificationCategory.h
//
//  UNNotificationCategory.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UNNotificationAction;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, UNNotificationCategoryOptions) {
    
    // Whether dismiss action should be sent to the UNUserNotificationCenter delegate
    UNNotificationCategoryOptionCustomDismissAction = (1 << 0),
    
    // Whether notifications of this category should be allowed in CarPlay
    UNNotificationCategoryOptionAllowInCarPlay __API_UNAVAILABLE(macos) = (1 << 1),
    
    // Whether the title should be shown if the user has previews off
    UNNotificationCategoryOptionHiddenPreviewsShowTitle __API_AVAILABLE(macos(10.14), ios(11.0)) __API_UNAVAILABLE(watchos, tvos) = (1 << 2),
    
    // Whether the subtitle should be shown if the user has previews off
    UNNotificationCategoryOptionHiddenPreviewsShowSubtitle __API_AVAILABLE(macos(10.14), ios(11.0)) __API_UNAVAILABLE(watchos, tvos) = (1 << 3),

    // Whether notifications of this category should be allowed for announcing notifications
    UNNotificationCategoryOptionAllowAnnouncement __API_AVAILABLE(ios(13.0), watchos(6.0)) __API_UNAVAILABLE(macos, tvos) = (1 << 4),

} __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos);

static const UNNotificationCategoryOptions UNNotificationCategoryOptionNone NS_SWIFT_UNAVAILABLE("Use [] instead.") __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos) = 0;

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos)
@interface UNNotificationCategory : NSObject <NSCopying, NSSecureCoding>

// The unique identifier for this category. The UNNotificationCategory's actions will be displayed on notifications when the UNNotificationCategory's identifier matches the UNNotificationRequest's categoryIdentifier.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *identifier;

// The UNNotificationActions in the order they will be displayed.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSArray<UNNotificationAction *> *actions;

// The intents supported support for notifications of this category. See <Intents/INIntentIdentifiers.h> for possible values.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSArray<NSString *> *intentIdentifiers;

@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationCategoryOptions options;

// The format string that will replace the notification body if previews are hidden.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *hiddenPreviewsBodyPlaceholder __API_AVAILABLE(ios(11.0)) __API_UNAVAILABLE(watchos, tvos);

/// A format string for a summary description when notifications from this category are grouped together.
/// It should contain descriptive text and format arguments that will be replaced with the information
/// from the notifications that have been grouped together. The arguments are replaced with the number
/// of notifications and the list created by joining the argument in each grouped notification.
/// For example: "%u new messages from %@".
/// The arguments list is optional, "%u new messages" is also accepted.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *categorySummaryFormat __API_AVAILABLE(ios(12.0)) __API_UNAVAILABLE(watchos, tvos);

+ (instancetype)categoryWithIdentifier:(NSString *)identifier
                               actions:(NSArray<UNNotificationAction *> *)actions
                     intentIdentifiers:(NSArray<NSString *> *)intentIdentifiers
                               options:(UNNotificationCategoryOptions)options;

+ (instancetype)categoryWithIdentifier:(NSString *)identifier
                               actions:(NSArray<UNNotificationAction *> *)actions
                     intentIdentifiers:(NSArray<NSString *> *)intentIdentifiers
         hiddenPreviewsBodyPlaceholder:(NSString *)hiddenPreviewsBodyPlaceholder
                               options:(UNNotificationCategoryOptions)options __API_AVAILABLE(ios(11.0)) __API_UNAVAILABLE(watchos, tvos);

+ (instancetype)categoryWithIdentifier:(NSString *)identifier
                               actions:(NSArray<UNNotificationAction *> *)actions
                     intentIdentifiers:(NSArray<NSString *> *)intentIdentifiers
         hiddenPreviewsBodyPlaceholder:(nullable NSString *)hiddenPreviewsBodyPlaceholder
                 categorySummaryFormat:(nullable NSString *)categorySummaryFormat
                               options:(UNNotificationCategoryOptions)options __API_AVAILABLE(ios(12.0)) __API_UNAVAILABLE(watchos, tvos);

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  UserNotifications.framework/Headers/UNNotification.h
//
//  UNNotification.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UNNotificationRequest;

NS_ASSUME_NONNULL_BEGIN

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@interface UNNotification : NSObject <NSCopying, NSSecureCoding>

// The date displayed on the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSDate *date;

// The notification request that caused the notification to be delivered.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) UNNotificationRequest *request;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  UserNotifications.framework/Headers/UNNotificationRequest.h
//
//  UNNotificationRequest.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UNNotificationContent;
@class UNNotificationTrigger;

NS_ASSUME_NONNULL_BEGIN

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@interface UNNotificationRequest : NSObject <NSCopying, NSSecureCoding>

// The unique identifier for this notification request. It can be used to replace or remove a pending notification request or a delivered notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *identifier;

// The content that will be shown on the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) UNNotificationContent *content;

// The trigger that will or did cause the notification to be delivered. A nil trigger means deliver immediately.
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) UNNotificationTrigger *trigger;

// Use a nil trigger to deliver immediately.
+ (instancetype)requestWithIdentifier:(NSString *)identifier content:(UNNotificationContent *)content trigger:(nullable UNNotificationTrigger *)trigger;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  UserNotifications.framework/Headers/UNNotificationTrigger.h
//
//  UNNotificationTrigger.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CLRegion;

NS_ASSUME_NONNULL_BEGIN

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@interface UNNotificationTrigger : NSObject <NSCopying, NSSecureCoding>

@property (NS_NONATOMIC_IOSONLY, readonly) BOOL repeats;

- (instancetype)init NS_UNAVAILABLE;

@end

// UNPushNotificationTrigger can be sent from a server using Apple Push Notification Service.
__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@interface UNPushNotificationTrigger : UNNotificationTrigger

@end

// UNTimeIntervalNotificationTrigger can be scheduled on the device to notify after the time interval, and optionally repeat.
__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@interface UNTimeIntervalNotificationTrigger : UNNotificationTrigger

@property (NS_NONATOMIC_IOSONLY, readonly) NSTimeInterval timeInterval;

+ (instancetype)triggerWithTimeInterval:(NSTimeInterval)timeInterval repeats:(BOOL)repeats;

- (nullable NSDate *)nextTriggerDate;

@end

// UNCalendarNotificationTrigger can be scheduled on the device to notify based on date and time values, and optionally repeat. For example, if a notification should be delivered at the next 8:00 AM then set the 'hour' property of dateComponents to 8. If the notification should be delivered every day at 8:00 AM then set repeats to YES.
__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@interface UNCalendarNotificationTrigger : UNNotificationTrigger

@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSDateComponents *dateComponents;

// The next date is calculated using matching date components.
+ (instancetype)triggerWithDateMatchingComponents:(NSDateComponents *)dateComponents repeats:(BOOL)repeats;

- (nullable NSDate *)nextTriggerDate;

@end

// UNLocationNotificationTrigger can be scheduled on the device to notify when the user enters or leaves a geographic region. The identifier on CLRegion must be unique. Scheduling multiple UNNotificationRequests with different regions containing the same identifier will result in undefined behavior. The number of UNLocationNotificationTriggers that may be scheduled by an application at any one time is limited by the system. Applications must have "when-in-use" authorization through CoreLocation. See the CoreLocation documentation for more information.
__API_AVAILABLE(ios(10.0), watchos(3.0)) __API_UNAVAILABLE(macos, tvos, uikitformac)
@interface UNLocationNotificationTrigger : UNNotificationTrigger

@property (NS_NONATOMIC_IOSONLY, readonly, copy) CLRegion *region;

+ (instancetype)triggerWithRegion:(CLRegion *)region repeats:(BOOL)repeats __API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END
// ==========  UserNotifications.framework/Headers/UNNotificationAttachment.h
//
//  UNNotificationAttachment.h
//  UserNotification
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos)
@interface UNNotificationAttachment : NSObject <NSCopying, NSSecureCoding>

// The identifier of this attachment
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *identifier;

// The URL to the attachment's data. If you have obtained this attachment from UNUserNotificationCenter then the URL will be security-scoped.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSURL *URL;

// The UTI of the attachment.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *type;

// Creates an attachment for the data at URL with an optional options dictionary. URL must be a file URL. Returns nil if the data at URL is not supported.
+ (nullable instancetype)attachmentWithIdentifier:(NSString *)identifier URL:(NSURL *)URL options:(nullable NSDictionary *)options error:(NSError *__nullable *__nullable)error;

- (instancetype)init NS_UNAVAILABLE;

@end

// Key to manually provide a type hint for the attachment. If not set the type hint will be guessed from the attachment's file extension. Value must be an NSString.
extern NSString * const UNNotificationAttachmentOptionsTypeHintKey __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos);

// Key to specify if the thumbnail for this attachment is hidden. Defaults to NO. Value must be a boolean NSNumber.
extern NSString * const UNNotificationAttachmentOptionsThumbnailHiddenKey __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos);

// Key to specify a normalized clipping rectangle to use for the attachment thumbnail. Value must be a CGRect encoded using CGRectCreateDictionaryRepresentation.
extern NSString * const UNNotificationAttachmentOptionsThumbnailClippingRectKey __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos);

// Key to specify the animated image frame number or the movie time to use as the thumbnail.
// An animated image frame number must be an NSNumber. A movie time must either be an NSNumber with the time in seconds or a CMTime encoded using CMTimeCopyAsDictionary.
extern NSString * const UNNotificationAttachmentOptionsThumbnailTimeKey __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos);

NS_ASSUME_NONNULL_END
 
// ==========  UserNotifications.framework/Headers/UNNotificationAction.h
//
//  UNNotificationAction.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, UNNotificationActionOptions) {
    
    // Whether this action should require unlocking before being performed.
    UNNotificationActionOptionAuthenticationRequired = (1 << 0),
    
    // Whether this action should be indicated as destructive.
    UNNotificationActionOptionDestructive = (1 << 1),

    // Whether this action should cause the application to launch in the foreground.
    UNNotificationActionOptionForeground = (1 << 2),
} __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos);

static const UNNotificationActionOptions UNNotificationActionOptionNone NS_SWIFT_UNAVAILABLE("Use [] instead.") __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos) = 0;

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos)
@interface UNNotificationAction : NSObject <NSCopying, NSSecureCoding>

// The unique identifier for this action.
@property (NS_NONATOMIC_IOSONLY, copy, readonly) NSString *identifier;

// The title to display for this action.
@property (NS_NONATOMIC_IOSONLY, copy, readonly) NSString *title;

// The options configured for this action.
@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationActionOptions options;

// Use -[NSString localizedUserNotificationStringForKey:arguments:] to provide a string that will be localized at the time that the notification is presented.
+ (instancetype)actionWithIdentifier:(NSString *)identifier title:(NSString *)title options:(UNNotificationActionOptions)options;

- (instancetype)init NS_UNAVAILABLE;

@end

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos)
@interface UNTextInputNotificationAction : UNNotificationAction

// Use -[NSString localizedUserNotificationStringForKey:arguments:] to provide a string that will be localized at the time that the notification is presented.
+ (instancetype)actionWithIdentifier:(NSString *)identifier title:(NSString *)title options:(UNNotificationActionOptions)options textInputButtonTitle:(NSString *)textInputButtonTitle textInputPlaceholder:(NSString *)textInputPlaceholder;

// The text input button title displayed for this action.
@property (NS_NONATOMIC_IOSONLY, copy, readonly) NSString *textInputButtonTitle;

// The placeholder text displayed in the text input field for this action.
@property (NS_NONATOMIC_IOSONLY, copy, readonly) NSString *textInputPlaceholder;

@end

NS_ASSUME_NONNULL_END
// ==========  UserNotifications.framework/Headers/UNNotificationSound.h
//
//  UNNotificationSound.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString *UNNotificationSoundName NS_EXTENSIBLE_STRING_ENUM;

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos)
@interface UNNotificationSound : NSObject <NSCopying, NSSecureCoding>

// The default sound used for notifications.
@property(class, NS_NONATOMIC_IOSONLY, copy, readonly) UNNotificationSound *defaultSound;

// The default sound used for critical alerts. Critical alerts will bypass the mute switch and Do Not Disturb.
@property(class, NS_NONATOMIC_IOSONLY, copy, readonly) UNNotificationSound *defaultCriticalSound __API_AVAILABLE(ios(12.0), watchos(5.0)) __API_UNAVAILABLE(tvos);

// The default sound used for critical alerts with a custom audio volume level. Critical alerts will bypass the mute switch and Do Not Disturb. The audio volume is expected to be between 0.0f and 1.0f.
+ (instancetype)defaultCriticalSoundWithAudioVolume:(float)volume __API_AVAILABLE(ios(12.0), watchos(5.0)) __API_UNAVAILABLE(tvos);

// The sound file to be played for the notification. The sound must be in the Library/Sounds folder of the app's data container or the Library/Sounds folder of an app group data container. If the file is not found in a container, the system will look in the app's bundle.
+ (instancetype)soundNamed:(UNNotificationSoundName)name __API_UNAVAILABLE(watchos, tvos);

// The name of a sound file to be played for an critical alert. Critical alerts will bypass the mute switch and Do Not Disturb. The sound file must be contained in the app’s bundle or in the Library/Sounds folder of the app’s data container. If files exist in both locations then the file in the app’s data container will be preferred.
+ (instancetype)criticalSoundNamed:(UNNotificationSoundName)name __API_AVAILABLE(ios(12.0)) __API_UNAVAILABLE(watchos, tvos);

// The name of a sound file to be played for an critical alert with a custom audio volume level. Critical alerts will bypass the mute switch and Do Not Disturb. The sound file must be contained in the app’s bundle or in the Library/Sounds folder of the app’s data container. If files exist in both locations then the file in the app’s data container will be preferred. The audio volume is expected to be between 0.0f and 1.0f.
+ (instancetype)criticalSoundNamed:(UNNotificationSoundName)name withAudioVolume:(float)volume __API_AVAILABLE(ios(12.0)) __API_UNAVAILABLE(watchos, tvos);

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  UserNotifications.framework/Headers/UNError.h
//
//  UNError.h
//  UserNotifications
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString * const UNErrorDomain __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0));

typedef NS_ENUM(NSInteger, UNErrorCode) {
    UNErrorCodeNotificationsNotAllowed = 1,
    
    UNErrorCodeAttachmentInvalidURL = 100,
    UNErrorCodeAttachmentUnrecognizedType,
    UNErrorCodeAttachmentInvalidFileSize,
    UNErrorCodeAttachmentNotInDataStore,
    UNErrorCodeAttachmentMoveIntoDataStoreFailed,
    UNErrorCodeAttachmentCorrupt,
    
    UNErrorCodeNotificationInvalidNoDate = 1400,
    UNErrorCodeNotificationInvalidNoContent,
} __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0));
// ==========  UserNotifications.framework/Headers/UNNotificationContent.h
//
//  UNNotificationContent.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UNNotificationAttachment;
@class UNNotificationSound;

NS_ASSUME_NONNULL_BEGIN

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@interface UNNotificationContent : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

// Optional array of attachments.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSArray <UNNotificationAttachment *> *attachments __API_UNAVAILABLE(tvos);

// The application badge number.
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSNumber *badge;

// The body of the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *body __API_UNAVAILABLE(tvos);

// The identifier for a registered UNNotificationCategory that will be used to determine the appropriate actions to display for the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *categoryIdentifier __API_UNAVAILABLE(tvos);

// The launch image that will be used when the app is opened from the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *launchImageName __API_UNAVAILABLE(macos, tvos);

// The sound that will be played for the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) UNNotificationSound *sound __API_UNAVAILABLE(tvos);

// The subtitle of the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *subtitle __API_UNAVAILABLE(tvos);

// The unique identifier for the thread or conversation related to this notification request. It will be used to visually group notifications together.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *threadIdentifier __API_UNAVAILABLE(tvos);

// The title of the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *title __API_UNAVAILABLE(tvos);

// Apps can set the userInfo for locally scheduled notification requests. The contents of the push payload will be set as the userInfo for remote notifications.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSDictionary *userInfo __API_UNAVAILABLE(tvos);

/// The argument to be inserted in the summary for this notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *summaryArgument __API_AVAILABLE(ios(12.0)) __API_UNAVAILABLE(watchos, tvos);

/// A number that indicates how many items in the summary are represented in the summary.
/// For example if a podcast app sends one notification for 3 new episodes in a show,
/// the argument should be the name of the show and the count should be 3.
/// Default is 1 and cannot be 0.
@property (NS_NONATOMIC_IOSONLY, readonly, assign) NSUInteger summaryArgumentCount __API_AVAILABLE(ios(12.0)) __API_UNAVAILABLE(watchos, tvos);

// An identifier for the content of the notification used by the system to customize the scene to be activated when tapping on a notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSString *targetContentIdentifier __API_AVAILABLE(ios(13_0)); // default nil

@end

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@interface UNMutableNotificationContent : UNNotificationContent

// Optional array of attachments.
@property (NS_NONATOMIC_IOSONLY, copy) NSArray <UNNotificationAttachment *> *attachments __API_UNAVAILABLE(tvos);

// The application badge number. nil means no change. 0 to hide.
@property (NS_NONATOMIC_IOSONLY, copy, nullable) NSNumber *badge;

// The body of the notification. Use -[NSString localizedUserNotificationStringForKey:arguments:] to provide a string that will be localized at the time that the notification is presented.
@property (NS_NONATOMIC_IOSONLY, copy) NSString *body __API_UNAVAILABLE(tvos);

// The identifier for a registered UNNotificationCategory that will be used to determine the appropriate actions to display for the notification.
@property (NS_NONATOMIC_IOSONLY, copy) NSString *categoryIdentifier __API_UNAVAILABLE(tvos);

// The launch image that will be used when the app is opened from the notification.
@property (NS_NONATOMIC_IOSONLY, copy) NSString *launchImageName __API_UNAVAILABLE(macos, tvos);

// The sound that will be played for the notification.
@property (NS_NONATOMIC_IOSONLY, copy, nullable) UNNotificationSound *sound __API_UNAVAILABLE(tvos);

// The subtitle of the notification. Use -[NSString localizedUserNotificationStringForKey:arguments:] to provide a string that will be localized at the time that the notification is presented.
@property (NS_NONATOMIC_IOSONLY, copy) NSString *subtitle __API_UNAVAILABLE(tvos);

// The unique identifier for the thread or conversation related to this notification request. It will be used to visually group notifications together.
@property (NS_NONATOMIC_IOSONLY, copy) NSString *threadIdentifier __API_UNAVAILABLE(tvos);

// The title of the notification. Use -[NSString localizedUserNotificationStringForKey:arguments:] to provide a string that will be localized at the time that the notification is presented.
@property (NS_NONATOMIC_IOSONLY, copy) NSString *title __API_UNAVAILABLE(tvos);

// Apps can set the userInfo for locally scheduled notification requests. The contents of the push payload will be set as the userInfo for remote notifications.
@property (NS_NONATOMIC_IOSONLY, copy) NSDictionary *userInfo __API_UNAVAILABLE(tvos);

/// The argument to be inserted in the summary for this notification.
@property (NS_NONATOMIC_IOSONLY, copy) NSString *summaryArgument __API_AVAILABLE(ios(12.0)) __API_UNAVAILABLE(watchos, tvos);

/// A number that indicates how many items in the summary are represented in the summary.
/// For example if a podcast app sends one notification for 3 new episodes in a show,
/// the argument should be the name of the show and the count should be 3.
/// Default is 1 and cannot be 0.
@property (NS_NONATOMIC_IOSONLY, assign) NSUInteger summaryArgumentCount __API_AVAILABLE(ios(12.0)) __API_UNAVAILABLE(watchos, tvos);

// An identifier for the content of the notification used by the system to customize the scene to be activated when tapping on a notification.
@property (NS_NONATOMIC_IOSONLY, copy, nullable) NSString *targetContentIdentifier __API_AVAILABLE(ios(13_0)); // default nil

@end

NS_ASSUME_NONNULL_END
// ==========  UserNotifications.framework/Headers/UNNotificationResponse.h
//
//  UNNotificationResponse.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UNNotification;

NS_ASSUME_NONNULL_BEGIN

extern NSString *const UNNotificationDefaultActionIdentifier __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos);
extern NSString *const UNNotificationDismissActionIdentifier __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos);

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos)
@interface UNNotificationResponse : NSObject <NSCopying, NSSecureCoding>

// The notification to which the user responded.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) UNNotification *notification;

// The action identifier that the user chose:
// * UNNotificationDismissActionIdentifier if the user dismissed the notification
// * UNNotificationDefaultActionIdentifier if the user opened the application from the notification
// * the identifier for a registered UNNotificationAction for other actions
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *actionIdentifier;

- (instancetype)init NS_UNAVAILABLE;

@end

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos)
@interface UNTextInputNotificationResponse : UNNotificationResponse

// The text entered or chosen by the user.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *userText;

@end

NS_ASSUME_NONNULL_END
// ==========  UserNotifications.framework/Headers/UNNotificationSettings.h
//
//  UNNotificationSettings.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UNAuthorizationStatus) {
    // The user has not yet made a choice regarding whether the application may post user notifications.
    UNAuthorizationStatusNotDetermined = 0,
    
    // The application is not authorized to post user notifications.
    UNAuthorizationStatusDenied,
    
    // The application is authorized to post user notifications.
    UNAuthorizationStatusAuthorized,
    
    // The application is authorized to post non-interruptive user notifications.
    UNAuthorizationStatusProvisional __API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
} __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0));

typedef NS_ENUM(NSInteger, UNShowPreviewsSetting) {
    // Notification previews are always shown.
    UNShowPreviewsSettingAlways,
    
    // Notifications previews are only shown when authenticated.
    UNShowPreviewsSettingWhenAuthenticated,
    
    // Notifications previews are never shown.
    UNShowPreviewsSettingNever
} __API_AVAILABLE(macos(10.14), ios(11.0)) __API_UNAVAILABLE(watchos, tvos);

typedef NS_ENUM(NSInteger, UNNotificationSetting) {
    // The application does not support this notification type
    UNNotificationSettingNotSupported  = 0,
    
    // The notification setting is turned off.
    UNNotificationSettingDisabled,
    
    // The notification setting is turned on.
    UNNotificationSettingEnabled,
} __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0));

typedef NS_ENUM(NSInteger, UNAlertStyle) {
    UNAlertStyleNone = 0,
    UNAlertStyleBanner,
    UNAlertStyleAlert,
} __API_AVAILABLE(macos(10.14), ios(10.0)) __API_UNAVAILABLE(watchos, tvos);

typedef NS_ENUM(NSInteger, UNNotificationGroupingSetting) {
    // Notifications are grouped by thread identifier.
    UNNotificationGroupingSettingDefault,
    
    // Notifications are grouped by source.
    UNNotificationGroupingSettingSource,
    
    // Notifications are not grouped.
    UNNotificationGroupingSettingOff
} __API_UNAVAILABLE(macos, ios, watchos, tvos);

__API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@interface UNNotificationSettings : NSObject <NSCopying, NSSecureCoding>

@property (NS_NONATOMIC_IOSONLY, readonly) UNAuthorizationStatus authorizationStatus;

@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting soundSetting __API_UNAVAILABLE(tvos);
@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting badgeSetting __API_UNAVAILABLE(watchos);
@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting alertSetting __API_UNAVAILABLE(tvos);

@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting notificationCenterSetting __API_UNAVAILABLE(tvos);
@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting lockScreenSetting __API_UNAVAILABLE(watchos, tvos);
@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting carPlaySetting __API_UNAVAILABLE(macos, tvos, watchos);

@property (NS_NONATOMIC_IOSONLY, readonly) UNAlertStyle alertStyle __API_UNAVAILABLE(watchos, tvos);

@property (NS_NONATOMIC_IOSONLY, readonly) UNShowPreviewsSetting showPreviewsSetting  __API_AVAILABLE(macos(10.14), ios(11.0)) __API_UNAVAILABLE(watchos, tvos);

@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting criticalAlertSetting __API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0)) __API_UNAVAILABLE(tvos);

@property (NS_NONATOMIC_IOSONLY, readonly) BOOL providesAppNotificationSettings __API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0)) __API_UNAVAILABLE(tvos);

@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationSetting announcementSetting __API_AVAILABLE(ios(13.0), watchos(6.0)) __API_UNAVAILABLE(macos, tvos);

@property (NS_NONATOMIC_IOSONLY, readonly, assign) UNNotificationGroupingSetting groupingSetting __API_UNAVAILABLE(macos, ios, watchos, tvos);

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
