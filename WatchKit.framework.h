// ==========  WatchKit.framework/Headers/WKAccessibility.h
//
//  WKAccessibility.h
//  WatchKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WKDefines.h>

NS_ASSUME_NONNULL_BEGIN

WKI_EXTERN BOOL WKAccessibilityIsVoiceOverRunning() WK_AVAILABLE_WATCHOS_ONLY(2.0);
WKI_EXTERN NSString *const WKAccessibilityVoiceOverStatusChanged WK_AVAILABLE_WATCHOS_ONLY(2.0);

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKInterfaceMovie.h
//
//  WKInterfaceMovie.h
//  WatchKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WKDefines.h>
#import <WatchKit/WKInterfaceObject.h>
#import <WatchKit/WKInterfaceController.h>

@class WKImage;

NS_ASSUME_NONNULL_BEGIN

WK_AVAILABLE_WATCHOS_ONLY(2.0)
@interface WKInterfaceMovie : WKInterfaceObject

- (void)setMovieURL:(NSURL *)URL;
- (void)setVideoGravity:(WKVideoGravity)videoGravity;	// default is WKVideoGravityResizeAspect
- (void)setLoops:(BOOL)loops;

- (void)setPosterImage:(nullable WKImage *)posterImage;

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKError.h
//
//  WKError.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WKDefines.h>

NS_ASSUME_NONNULL_BEGIN

WKI_EXTERN NSString * const WatchKitErrorDomain NS_AVAILABLE_IOS(8_2);

typedef NS_ENUM(NSInteger, WatchKitErrorCode)  {
    WatchKitUnknownError                                          = 1,  // unknown error
    WatchKitApplicationDelegateWatchKitRequestReplyNotCalledError = 2,  // in iOS app's -[UIApplicationDelegate application:handleWatchKitExtensionRequest:reply:], reply was never called
    WatchKitInvalidArgumentError                                  = 3,  // invalid argument error
    WatchKitMediaPlayerError                                      = 4,  // media player error
    WatchKitDownloadError                                         = 5,  // download of resource failed
} NS_ENUM_AVAILABLE_IOS(8_2);

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKInterfaceDate.h
//
//  WKInterfaceDate.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <WatchKit/WatchKit.h>
#import <WatchKit/WKDefines.h>
#import <WatchKit/WKInterfaceObject.h>

NS_ASSUME_NONNULL_BEGIN

@class UIColor;

WK_CLASS_AVAILABLE_IOS(8_2)
@interface WKInterfaceDate : WKInterfaceObject

- (void)setTextColor:(nullable UIColor *)color;

- (void)setTimeZone:(nullable NSTimeZone *)timeZone;
- (void)setCalendar:(nullable NSCalendar *)calendar;

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKAudioFilePlayerItem.h
//
//  WKAudioFilePlayerItem.h
//  WatchKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WKDefines.h>

/*!
 @class		WKAudioFilePlayerItem
 
 @abstract
 WatchKit corollary to AVFoundation AVPlayerItem class
 
 @discussion
 This class provides the functionality of AVPlayerItem for Watch OS apps. Only file-based assets are allowed.
 */

@class WKAudioFileAsset;

NS_ASSUME_NONNULL_BEGIN

WKI_EXTERN NSString *const WKAudioFilePlayerItemTimeJumpedNotification WK_AVAILABLE_WATCHOS_ONLY(2.0);
WKI_EXTERN NSString *const WKAudioFilePlayerItemDidPlayToEndTimeNotification WK_AVAILABLE_WATCHOS_ONLY(2.0);
WKI_EXTERN NSString *const WKAudioFilePlayerItemFailedToPlayToEndTimeNotification WK_AVAILABLE_WATCHOS_ONLY(2.0);

typedef NS_ENUM(NSInteger, WKAudioFilePlayerItemStatus) {
    WKAudioFilePlayerItemStatusUnknown,
    WKAudioFilePlayerItemStatusReadyToPlay,
    WKAudioFilePlayerItemStatusFailed
} WK_AVAILABLE_WATCHOS_ONLY(2.0);

WK_AVAILABLE_WATCHOS_ONLY(2.0)
@interface WKAudioFilePlayerItem : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (WKAudioFilePlayerItem *)playerItemWithAsset:(WKAudioFileAsset *)asset;

@property (nonatomic, readonly) WKAudioFileAsset *asset;
@property (nonatomic, readonly) WKAudioFilePlayerItemStatus status;
@property (nonatomic, readonly, nullable) NSError *error;
@property (nonatomic, readonly) NSTimeInterval currentTime;
@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKInterfaceLabel.h
//
//  WKInterfaceLabel.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WKDefines.h>
#import <WatchKit/WKInterfaceObject.h>

NS_ASSUME_NONNULL_BEGIN

@class UIColor;

WK_CLASS_AVAILABLE_IOS(8_2)
@interface WKInterfaceLabel : WKInterfaceObject

- (void)setText:(nullable NSString *)text;
- (void)setTextColor:(nullable UIColor *)color;

- (void)setAttributedText:(nullable NSAttributedString *)attributedText;

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKInterfaceDevice.h
//
//  WKInterfaceDevice.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <WatchKit/WatchKit.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage;

typedef NS_ENUM(NSInteger, WKHapticType) {
	WKHapticTypeNotification,
    WKHapticTypeDirectionUp,
    WKHapticTypeDirectionDown,
    WKHapticTypeSuccess,
    WKHapticTypeFailure,
    WKHapticTypeRetry,
    WKHapticTypeStart,
    WKHapticTypeStop,
    WKHapticTypeClick
} WK_AVAILABLE_WATCHOS_ONLY(2.0);

@interface WKInterfaceDevice : NSObject

+ (WKInterfaceDevice *)currentDevice;

- (BOOL)addCachedImage:(UIImage *)image name:(NSString *)name WK_AVAILABLE_IOS_ONLY(8.2);
- (BOOL)addCachedImageWithData:(NSData *)imageData name:(NSString *)name WK_AVAILABLE_IOS_ONLY(8.2);
- (void)removeCachedImageWithName:(NSString *)name WK_AVAILABLE_IOS_ONLY(8.2);
- (void)removeAllCachedImages WK_AVAILABLE_IOS_ONLY(8.2);

@property (nonatomic, readonly) CGRect screenBounds;
@property (nonatomic, readonly) CGFloat screenScale;
@property (nonatomic, readonly, copy)  NSString *preferredContentSizeCategory;
@property (nonatomic, readonly, strong) NSDictionary<NSString*, NSNumber*> *cachedImages; // name and size of cached images

@property(nonatomic, readonly, copy) NSString *systemVersion  WK_AVAILABLE_WATCHOS_IOS(2.0,9.0); // e.g. @"2.0"
@property(nonatomic, readonly, copy) NSString *name           WK_AVAILABLE_WATCHOS_IOS(2.0,9.0); // e.g. "My Watch"
@property(nonatomic, readonly, copy) NSString *model          WK_AVAILABLE_WATCHOS_IOS(2.0,9.0); // e.g. @"Apple Watch"
@property(nonatomic, readonly, copy) NSString *localizedModel WK_AVAILABLE_WATCHOS_IOS(2.0,9.0); // localized version of model
@property(nonatomic, readonly, copy) NSString *systemName     WK_AVAILABLE_WATCHOS_IOS(2.0,9.0); // e.g. @"watchOS"

- (void)playHaptic:(WKHapticType)type WK_AVAILABLE_WATCHOS_ONLY(2.0);

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKInterfaceSwitch.h
//
//  WKInterfaceSwitch.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WKDefines.h>
#import <WatchKit/WKInterfaceObject.h>
#import <UIKit/UIColor.h>

NS_ASSUME_NONNULL_BEGIN

WK_CLASS_AVAILABLE_IOS(8_2)
@interface WKInterfaceSwitch : WKInterfaceObject

- (void)setTitle:(nullable NSString *)title;
- (void)setAttributedTitle:(nullable NSAttributedString *)attributedTitle;

- (void)setEnabled:(BOOL)enabled;
- (void)setOn:(BOOL)on;
- (void)setColor:(nullable UIColor *)color;

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKAudioFilePlayer.h
//
//  WKAudioFilePlayer.h
//  WatchKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WKDefines.h>

/*!
 @class		WKAudioFilePlayer
 
 @abstract
 WatchKit corollary to AVFoundation AVPlayer class
 
 @discussion
 This class provides the functionality of AVPlayer for Watch OS apps. Only file-based assets are allowed.
 */

@class WKAudioFilePlayerItem;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, WKAudioFilePlayerStatus) {
    WKAudioFilePlayerStatusUnknown,
    WKAudioFilePlayerStatusReadyToPlay,
    WKAudioFilePlayerStatusFailed
} WK_AVAILABLE_WATCHOS_ONLY(2.0);

WK_AVAILABLE_WATCHOS_ONLY(2.0)
@interface WKAudioFilePlayer : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)playerWithPlayerItem:(WKAudioFilePlayerItem *)item;

- (void)play;
- (void)pause;

- (void)replaceCurrentItemWithPlayerItem:(nullable WKAudioFilePlayerItem *)item;

@property(nonatomic, readonly, nullable) WKAudioFilePlayerItem *currentItem;

@property (nonatomic, readonly) WKAudioFilePlayerStatus status;
@property (nonatomic, readonly, nullable) NSError *error;

/* indicates the current rate of playback; 0.0 means "stopped", 1.0 means "play at the natural rate of the current item" */
@property (nonatomic) float rate;

@property (nonatomic, readonly) NSTimeInterval currentTime;

@end


/*!
 @class		WKAudioFileQueuePlayer
 
 @abstract
 WatchKit corollary to AVFoundation AVQueuePlayer class
 
 @discussion
 This class provides the functionality of AVQueuePlayer for Watch OS apps. Only file-based assets are allowed.
 */

WK_AVAILABLE_WATCHOS_ONLY(2.0)
@interface WKAudioFileQueuePlayer : WKAudioFilePlayer
+ (instancetype)queuePlayerWithItems:(NSArray<WKAudioFilePlayerItem *> *)items;

- (void)advanceToNextItem;

- (void)appendItem:(WKAudioFilePlayerItem *)item;

- (void)removeItem:(WKAudioFilePlayerItem *)item;

- (void)removeAllItems;

@property(nonatomic, readonly) NSArray<WKAudioFilePlayerItem *> *items;

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKInterfacePicker.h
//
//  WKInterfacePicker.h
//  WatchKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WKDefines.h>
#import <WatchKit/WKInterfaceObject.h>
#import <WatchKit/WKInterfaceImage.h>

@class WKImage, WKPickerItem;

NS_ASSUME_NONNULL_BEGIN

// WKInterfacePicker is a UI component that presents items in a number of
// different styles for picking via the Digital Crown. These styles include:
//
// 1. List
// Items are shown in a vertically stacked list, similar to the UI shown during
// Activity Setup and Complication editing. Turning the Digital Crown moves up
// and down through the list.
//
// 2. Stack
// Items are shown as a stack of cards and can be flipped through via the crown.
//
// 3. Image Sequence
// Items are shown as a sequence of images, and turning the crown changes the
// visible image. Sequences of images can include animations, segments of a
// progress ring etc.
//
// Multiple pickers can be shown in a single Interface Controller, and they
// can be nested within a scrolling view.

WK_AVAILABLE_WATCHOS_ONLY(2.0)
@interface WKInterfacePicker : WKInterfaceObject

// Make the picker focused so Digital Crown input is directed to it. This is
// useful in cases where there are multiple on-screen pickers, or if the picker
// is nested in a scrollable view.
- (void)focus;

// Resigns focus from the picker. If the picker is nested in a scrollable
// view, the Digital Crown input will be used for scrolling.
- (void)resignFocus;

// Change the selected item index.
- (void)setSelectedItemIndex:(NSInteger)itemIndex;

// Configure the picker with a set of items, which will be displayed according
// to the style of the picker.
- (void)setItems:(nullable NSArray<WKPickerItem *> *)items;

// Configure the picker with one or more interface objects that support
// animated images. Turning the crown to adjust the picker will seek through the
// keyframes of any coordinated animations.
- (void)setCoordinatedAnimations:(nullable NSArray<WKInterfaceObject<WKImageAnimatable> *> *)coordinatedAnimations;

// Enable or disable the picker. When disabled, the picker cannot be focused.
- (void)setEnabled:(BOOL)enabled;

@end

WK_AVAILABLE_WATCHOS_ONLY(2.0)
@interface WKPickerItem : NSObject <NSSecureCoding>

// Text to show when the item is being displayed in a picker with the 'List' style.
@property (nonatomic, copy, nullable) NSString *title;

// Caption to show for the item when focus style includes a caption callout.
@property (nonatomic, copy, nullable) NSString *caption;

// An accessory image to show next to the title in a picker with the 'List'
// style. Note that the image will be scaled and centered to fit within
// an 13×13pt rect.
@property (nonatomic, copy, nullable) WKImage *accessoryImage;

// A custom image to show for the item, used instead of the title + accessory
// image when more flexibility is needed, or when displaying in the stack or
// sequence style. The image will be scaled and centered to fit within the
// picker's bounds or item row bounds.
@property (nonatomic, copy, nullable) WKImage *contentImage;

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKAudioFileAsset.h
//
//  WKAudioFileAsset.h
//  WatchKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WKDefines.h>

/*!
 @class		WKAudioFileAsset
 
 @abstract
 WatchKit corollary to AVFoundation AVAsset abstract class
 
 @discussion
 This class provides the functionality of AVAsset for Watch OS apps. Only file-based assets are allowed.
*/

NS_ASSUME_NONNULL_BEGIN

WK_AVAILABLE_WATCHOS_ONLY(2.0)
@interface WKAudioFileAsset : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 @method		assetWithURL:
 @abstract		Returns an instance of WKAudioFileAsset for inspection of a media resource.
 @param		URL
 An instance of NSURL that references a file-based media resource.
 @result		An instance of WKAudioFileAsset.
 @discussion	Returns a newly allocated instance of a subclass of WKAudioFileAsset initialized with the specified URL.
                Title, ablumTitle, and artist properties are initialized to the values found in the common metadata of the media resource
 */
+ (instancetype)assetWithURL:(NSURL *)URL;

/*!
 @method		assetWithURL:title:albumTitle:artist:
 @abstract		Returns an instance of WKAudioFileAsset for inspection of a media resource.
 @param		URL
 An instance of NSURL that references a file-based media resource.
 @param		title
 Title string to use for the Now Playing controls. If nil, value in common metadata of the media resource will be used. If no value is found in common metadata, the file name will be used.
 @param		albumTitle
 Album Title string to use for the Now Playing controls. If nil, value in common metadata of the media resource will be used.
 @param		artist
 Artist string to use for the Now Playing controls. If nil, value in common metadata of the media resource will be used.
 @result		An instance of WKAudioFileAsset.
 @discussion	Returns a newly allocated instance of a subclass of WKAudioFileAsset initialized with the specified URL.
 */
+ (instancetype)assetWithURL:(NSURL *)URL title:(nullable NSString *)title albumTitle:(nullable NSString *)albumTitle artist:(nullable NSString *)artist;

@property (nonatomic, readonly) NSURL *URL;
@property (nonatomic, readonly) NSTimeInterval duration;
@property (nonatomic, readonly, nullable) NSString *title;
@property (nonatomic, readonly, nullable) NSString *albumTitle;
@property (nonatomic, readonly, nullable) NSString *artist;
@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKInterfaceImage.h
//
//  WKInterfaceImage.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WKDefines.h>
#import <WatchKit/WKInterfaceObject.h>
#import <UIKit/UIColor.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage;

@protocol WKImageAnimatable <NSObject>

// Play all images repeatedly using duration specified in interface description.
- (void)startAnimating;

// Play a subset of images for a certain number of times. 0 means repeat until stop.
- (void)startAnimatingWithImagesInRange:(NSRange)imageRange duration:(NSTimeInterval)duration repeatCount:(NSInteger)repeatCount;

- (void)stopAnimating;

@end

WK_CLASS_AVAILABLE_IOS(8_2)
@interface WKInterfaceImage : WKInterfaceObject <WKImageAnimatable>

- (void)setImage:(nullable UIImage *)image;
- (void)setImageData:(nullable NSData *)imageData;
- (void)setImageNamed:(nullable NSString *)imageName;

- (void)setTintColor:(nullable UIColor *)tintColor;

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKInterfaceController.h
//
//  WKInterfaceController.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <WatchKit/WKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class WKAlertAction;
@class WKInterfaceTable;
@class WKInterfacePicker;
@class UIImage;
@class UILocalNotification;
@class PKPass;

typedef NS_ENUM(NSInteger, WKUserNotificationInterfaceType)  {
    WKUserNotificationInterfaceTypeDefault,
    WKUserNotificationInterfaceTypeCustom,
} NS_ENUM_AVAILABLE_IOS(8_2);

typedef NS_ENUM(NSInteger, WKMenuItemIcon)  {
    WKMenuItemIconAccept,       // checkmark
    WKMenuItemIconAdd,          // '+'
    WKMenuItemIconBlock,        // circle w/ slash
    WKMenuItemIconDecline,      // 'x'
    WKMenuItemIconInfo,         // 'i'
    WKMenuItemIconMaybe,        // '?'
    WKMenuItemIconMore,         // '...'
    WKMenuItemIconMute,         // speaker w/ slash
    WKMenuItemIconPause,        // pause button
    WKMenuItemIconPlay,         // play button
    WKMenuItemIconRepeat,       // looping arrows
    WKMenuItemIconResume,       // circular arrow
    WKMenuItemIconShare,        // share icon
    WKMenuItemIconShuffle,      // swapped arrows
    WKMenuItemIconSpeaker,      // speaker icon
    WKMenuItemIconTrash,        // trash icon
} NS_ENUM_AVAILABLE_IOS(8_2);

typedef NS_ENUM(NSInteger, WKTextInputMode)  {
    WKTextInputModePlain,		// text (no emoji) from dictation + suggestions
    WKTextInputModeAllowEmoji, 		// text plus non-animated emoji from dictation + suggestions
    WKTextInputModeAllowAnimatedEmoji,	// all text, animated emoji (GIF data)
};

typedef NS_ENUM(NSInteger, WKAlertControllerStyle) {
    WKAlertControllerStyleAlert,
    WKAlertControllerStyleSideBySideButtonsAlert,
    WKAlertControllerStyleActionSheet,
} WK_AVAILABLE_WATCHOS_ONLY(2.0);


typedef NS_ENUM(NSInteger, WKVideoGravity)  {
	WKVideoGravityResizeAspect,
	WKVideoGravityResizeAspectFill,
	WKVideoGravityResize
} WK_AVAILABLE_WATCHOS_ONLY(2.0);

/*
 The following presets can be specified to indicate the desired output sample rate. The resulting bit rate depends on the preset and the audio format. The audio file type is inferred from the output URL extension. The audio format is inferred from the audio file type. Supported file types include .wav, .mp4, and .m4a. When the URL extension is .wav, the audio format is LPCM. It is AAC for all other cases.
 */
typedef NS_ENUM(NSInteger, WKAudioRecordingPreset) {
	WKAudioRecordingPresetNarrowBandSpeech,	// @8kHz, LPCM 128kbps, AAC 24kbps
	WKAudioRecordingPresetWideBandSpeech,	// @16kHz, LPCM 256kbps, AAC 32kbps
	WKAudioRecordingPresetHighQualityAudio	// @44.1kHz, LPCM 705.6kbps, AAC 96kbps
} WK_AVAILABLE_WATCHOS_ONLY(2.0);

WK_CLASS_AVAILABLE_IOS(8_2)
@interface WKInterfaceController : NSObject

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (void)awakeWithContext:(nullable id)context;   // context from controller that did push or modal presentation. default does nothing

@property (nonatomic, readonly) CGRect contentFrame;

- (void)willActivate;      // Called when watch interface is active and able to be updated. Can be called when interface is not visible.
- (void)didDeactivate;     // Called when watch interface is no longer active and cannot be updated.

- (void)didAppear WK_AVAILABLE_WATCHOS_ONLY(2.0);  // Called when watch interface is visible to user
- (void)willDisappear WK_AVAILABLE_WATCHOS_ONLY(2.0); // Called when watch interface is about to no longer be visible

- (void)pickerDidFocus:(WKInterfacePicker *)picker WK_AVAILABLE_WATCHOS_ONLY(2.0);
- (void)pickerDidResignFocus:(WKInterfacePicker *)picker WK_AVAILABLE_WATCHOS_ONLY(2.0);
- (void)pickerDidSettle:(WKInterfacePicker *)picker WK_AVAILABLE_WATCHOS_ONLY(2.0);

- (void)table:(WKInterfaceTable *)table didSelectRowAtIndex:(NSInteger)rowIndex;  // row selection if controller has WKInterfaceTable property
- (void)handleActionWithIdentifier:(nullable NSString *)identifier forRemoteNotification:(NSDictionary *)remoteNotification; // when the app is launched from a notification. If launched from app icon in notification UI, identifier will be empty
- (void)handleActionWithIdentifier:(nullable NSString *)identifier forLocalNotification:(UILocalNotification *)localNotification; // when the app is launched from a notification. If launched from app icon in notification UI, identifier will be empty
- (void)handleUserActivity:(nullable NSDictionary *)userInfo; // called on root controller(s) with user info

- (void)setTitle:(nullable NSString *)title;        // title of controller. displayed when controller active

- (void)pushControllerWithName:(NSString *)name context:(nullable id)context;  // context passed to child controller via initWithContext:
- (void)popController;
- (void)popToRootController;

+ (void)reloadRootControllersWithNames:(NSArray<NSString*> *)names contexts:(nullable NSArray *)contexts;
- (void)becomeCurrentPage;

- (void)presentControllerWithName:(NSString *)name context:(nullable id)context; // modal presentation
- (void)presentControllerWithNames:(NSArray<NSString*> *)names contexts:(nullable NSArray *)contexts; // modal presentation of paged controllers. contexts matched to controllers
- (void)dismissController;

- (void)presentTextInputControllerWithSuggestions:(nullable NSArray<NSString*> *)suggestions allowedInputMode:(WKTextInputMode)inputMode completion:(void(^)(NSArray * __nullable results))completion; // results is nil if cancelled
- (void)presentTextInputControllerWithSuggestionsForLanguage:(NSArray * __nullable (^ __nullable)(NSString *inputLanguage))suggestionsHandler allowedInputMode:(WKTextInputMode)inputMode completion:(void(^)(NSArray * __nullable results))completion;
- (void)dismissTextInputController;

WKI_EXTERN NSString *const UIUserNotificationActionResponseTypedTextKey WK_AVAILABLE_WATCHOS_ONLY(2.0);

WKI_EXTERN NSString *const WKMediaPlayerControllerOptionsAutoplayKey WK_AVAILABLE_WATCHOS_ONLY(2.0);      // NSNumber containing BOOL
WKI_EXTERN NSString *const WKMediaPlayerControllerOptionsStartTimeKey WK_AVAILABLE_WATCHOS_ONLY(2.0);     // NSNumber containing NSTimeInterval
WKI_EXTERN NSString *const WKMediaPlayerControllerOptionsVideoGravityKey WK_AVAILABLE_WATCHOS_ONLY(2.0);  // NSNumber containing WKVideoGravity
WKI_EXTERN NSString *const WKMediaPlayerControllerOptionsLoopsKey WK_AVAILABLE_WATCHOS_ONLY(2.0);         // NSNumber containing BOOL

- (void)presentMediaPlayerControllerWithURL:(NSURL *)URL options:(nullable NSDictionary *)options completion:(void(^)(BOOL didPlayToEnd, NSTimeInterval endTime, NSError * __nullable error))completion WK_AVAILABLE_WATCHOS_ONLY(2.0);
- (void)dismissMediaPlayerController WK_AVAILABLE_WATCHOS_ONLY(2.0);

- (void)presentAudioRecordingControllerWithOutputURL:(NSURL *)URL preset:(WKAudioRecordingPreset)preset maximumDuration:(NSTimeInterval)maximumDuration actionTitle:(nullable NSString *)actionTitle completion:(void (^)(BOOL didSave, NSError * __nullable error))completion WK_AVAILABLE_WATCHOS_ONLY(2.0);
- (void)dismissAudioRecordingController WK_AVAILABLE_WATCHOS_ONLY(2.0);

- (nullable id)contextForSegueWithIdentifier:(NSString *)segueIdentifier;
- (nullable NSArray *)contextsForSegueWithIdentifier:(NSString *)segueIdentifier;
- (nullable id)contextForSegueWithIdentifier:(NSString *)segueIdentifier inTable:(WKInterfaceTable *)table rowIndex:(NSInteger)rowIndex;
- (nullable NSArray *)contextsForSegueWithIdentifier:(NSString *)segueIdentifier inTable:(WKInterfaceTable *)table rowIndex:(NSInteger)rowIndex;

- (void)animateWithDuration:(NSTimeInterval)duration animations:(void (^)(void))animations WK_AVAILABLE_WATCHOS_ONLY(2.0);

- (void)presentAlertControllerWithTitle:(nullable NSString *)title message:(nullable NSString *)message preferredStyle:(WKAlertControllerStyle)preferredStyle actions:(NSArray <WKAlertAction *>*)actions WK_AVAILABLE_WATCHOS_ONLY(2.0);

- (void)presentAddPassesControllerWithPasses:(NSArray <PKPass *> *)passes completion:(void(^)(void))completion WK_AVAILABLE_WATCHOS_ONLY(2.0);
- (void)dismissAddPassesController WK_AVAILABLE_WATCHOS_ONLY(2.0);

- (void)addMenuItemWithImage:(UIImage *)image title:(NSString *)title action:(
 SEL)action;           // all parameters must be non-nil
- (void)addMenuItemWithImageNamed:(NSString *)imageName title:(NSString *)title action:(SEL)action;
- (void)addMenuItemWithItemIcon:(WKMenuItemIcon)itemIcon title:(NSString *)title action:(SEL)action;
- (void)clearAllMenuItems;

- (void)updateUserActivity:(NSString *)type userInfo:(nullable NSDictionary *)userInfo webpageURL:(nullable NSURL *)webpageURL;  // provide type and info to Handoff. userInfo and webpageUrl are passed to the application receiving the Handoff
- (void)invalidateUserActivity;

+ (BOOL)openParentApplication:(NSDictionary *)userInfo reply:(nullable void(^)(NSDictionary * replyInfo, NSError * __nullable error)) reply WK_AVAILABLE_IOS_ONLY(8.2);    // launches containing iOS application on the phone. userInfo must be non-nil

- (void)beginGlanceUpdates WK_AVAILABLE_WATCHOS_ONLY(2.0);
- (void)endGlanceUpdates WK_AVAILABLE_WATCHOS_ONLY(2.0);

@end

WK_CLASS_AVAILABLE_IOS(8_2)
@interface WKUserNotificationInterfaceController : WKInterfaceController

- (instancetype)init NS_DESIGNATED_INITIALIZER;

- (void)didReceiveRemoteNotification:(NSDictionary *)remoteNotification withCompletion:(void(^)(WKUserNotificationInterfaceType interface)) completionHandler;
- (void)didReceiveLocalNotification:(UILocalNotification *)localNotification withCompletion:(void(^)(WKUserNotificationInterfaceType interface)) completionHandler;

// Subclasses can implement to return an array of suggestions to use as text responses to a remote notification.
- (nonnull NSArray<NSString *> *)suggestionsForResponseToActionWithIdentifier:(NSString *)identifier forRemoteNotification:(NSDictionary *)remoteNotification inputLanguage:(NSString *)inputLanguage WK_AVAILABLE_WATCHOS_ONLY(2.0);

// Subclasses can implement to return an array of suggestions to use as text responses to a local notification.
- (nonnull NSArray<NSString *> *)suggestionsForResponseToActionWithIdentifier:(NSString *)identifier forLocalNotification:(UILocalNotification *)localNotification inputLanguage:(NSString *)inputLanguage WK_AVAILABLE_WATCHOS_ONLY(2.0);

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKInterfaceSeparator.h
//
//  WKInterfaceSeparator.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <WatchKit/WKDefines.h>
#import <WatchKit/WKInterfaceObject.h>

NS_ASSUME_NONNULL_BEGIN

@class UIColor;

WK_CLASS_AVAILABLE_IOS(8_2)
@interface WKInterfaceSeparator : WKInterfaceObject

- (void)setColor:(nullable UIColor *)color;

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKInterfaceGroup.h
//
//  WKInterfaceGroup.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WKDefines.h>
#import <WatchKit/WKInterfaceObject.h>
#import <WatchKit/WKInterfaceImage.h>
#import <UIKit/UIGeometry.h>

NS_ASSUME_NONNULL_BEGIN

@class UIColor, UIImage;
@protocol WKImageAnimatable;

WK_CLASS_AVAILABLE_IOS(8_2)
@interface WKInterfaceGroup : WKInterfaceObject <WKImageAnimatable>

- (void)setCornerRadius:(CGFloat)cornerRadius;
- (void)setContentInset:(UIEdgeInsets)contentInset WK_AVAILABLE_WATCHOS_ONLY(2.0);

- (void)setBackgroundColor:(nullable UIColor *)color;
- (void)setBackgroundImage:(nullable UIImage *)image;
- (void)setBackgroundImageData:(nullable NSData *)imageData;
- (void)setBackgroundImageNamed:(nullable NSString *)imageName;

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKImage.h
//
//  WKImage.h
//  WatchKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage;

WK_AVAILABLE_WATCHOS_ONLY(2.0)
@interface WKImage : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)imageWithImage:(UIImage *)image;
+ (instancetype)imageWithImageData:(NSData *)imageData;
+ (instancetype)imageWithImageName:(NSString *)imageName;

- (instancetype)init NS_UNAVAILABLE;

@property (readonly, nullable) UIImage *image;
@property (readonly, nullable) NSData *imageData;
@property (readonly, nullable) NSString *imageName;

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKInterfaceTimer.h
//
//  WKInterfaceTimer.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <WatchKit/WatchKit.h>
#import <WatchKit/WKDefines.h>
#import <WatchKit/WKInterfaceObject.h>

NS_ASSUME_NONNULL_BEGIN

@class UIColor;

WK_CLASS_AVAILABLE_IOS(8_2)
@interface WKInterfaceTimer : WKInterfaceObject

- (void)setTextColor:(nullable UIColor *)color;

- (void)setDate:(NSDate *)date; // count up/down from current date to this date
- (void)start;
- (void)stop;

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKInterfaceSlider.h
//
//  WKInterfaceSlider.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WKDefines.h>
#import <WatchKit/WKInterfaceObject.h>

NS_ASSUME_NONNULL_BEGIN

@class UIColor;

WK_CLASS_AVAILABLE_IOS(8_2)
@interface WKInterfaceSlider : WKInterfaceObject

- (void)setEnabled:(BOOL)enabled;
- (void)setValue:(float)value;
- (void)setColor:(nullable UIColor *)color;
- (void)setNumberOfSteps:(NSInteger)numberOfSteps;

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WatchKit.h
//
//  WatchKit.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <WatchKit/WKDefines.h>
#import <WatchKit/WKError.h>
#import <WatchKit/WKInterfaceController.h>
#import <WatchKit/WKImage.h>
#import <WatchKit/WKInterfaceObject.h>
#import <WatchKit/WKInterfaceDevice.h>
#import <WatchKit/WKInterfaceButton.h>
#import <WatchKit/WKInterfaceGroup.h>
#import <WatchKit/WKInterfaceImage.h>
#import <WatchKit/WKInterfaceLabel.h>
#import <WatchKit/WKInterfaceDate.h>
#import <WatchKit/WKInterfaceTimer.h>
#import <WatchKit/WKInterfaceTable.h>
#import <WatchKit/WKInterfaceMap.h>
#import <WatchKit/WKInterfaceSeparator.h>
#import <WatchKit/WKInterfaceSlider.h>
#import <WatchKit/WKInterfaceSwitch.h>
#if TARGET_OS_WATCH
#import <WatchKit/WKAlertAction.h>
#import <WatchKit/WKExtension.h>
#import <WatchKit/WKAudioFileAsset.h>
#import <WatchKit/WKAudioFilePlayer.h>
#import <WatchKit/WKAudioFilePlayerItem.h>
#import <WatchKit/WKInterfaceMovie.h>
#import <WatchKit/WKInterfacePicker.h>
#import <WatchKit/WKAccessibility.h>
#endif
// ==========  WatchKit.framework/Headers/WKDefines.h
//
//  WKDefines.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Availability.h>

#ifdef __cplusplus
#define WKI_EXTERN  extern "C" __attribute__((visibility ("default")))
#else
#define WKI_EXTERN  extern __attribute__((visibility ("default")))
#endif

#define WK_CLASS_AVAILABLE_IOS(_iOSIntro)   NS_CLASS_AVAILABLE_IOS(_iOSIntro)
#define WK_AVAILABLE_WATCHOS_ONLY(_watchOSIntro) __WATCHOS_AVAILABLE(_watchOSIntro) __IOS_UNAVAILABLE
#define WK_AVAILABLE_IOS_ONLY(_iOSIntro) __IOS_AVAILABLE(_iOSIntro) __WATCHOS_UNAVAILABLE
#define WK_AVAILABLE_WATCHOS_IOS(_watchOSIntro,_iOSIntro) __WATCHOS_AVAILABLE(_watchOSIntro) __IOS_AVAILABLE(_iOSIntro)
// ==========  WatchKit.framework/Headers/WKInterfaceButton.h
//
//  WKInterfaceButton.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WKDefines.h>
#import <WatchKit/WKInterfaceObject.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage, UIColor;

WK_CLASS_AVAILABLE_IOS(8_2)
@interface WKInterfaceButton : WKInterfaceObject

- (void)setTitle:(nullable NSString *)title;
- (void)setAttributedTitle:(nullable NSAttributedString *)attributedTitle;

- (void)setBackgroundColor:(nullable UIColor *)color;
- (void)setBackgroundImage:(nullable UIImage *)image;
- (void)setBackgroundImageData:(nullable NSData *)imageData;
- (void)setBackgroundImageNamed:(nullable NSString *)imageName;

- (void)setEnabled:(BOOL)enabled;

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKExtension.h
//
//  WKExtension.h
//  WatchKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#if TARGET_OS_WATCH

#import <WatchKit/WKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@protocol WKExtensionDelegate;

WK_AVAILABLE_WATCHOS_ONLY(2.0)
@interface WKExtension : NSObject

+ (WKExtension *)sharedExtension;

- (void)openSystemURL:(NSURL *)url;

@property (nonatomic, weak, nullable) id<WKExtensionDelegate> delegate;
@property (nonatomic,readonly, nullable) WKInterfaceController *rootInterfaceController;

@end

@class UILocalNotification;

WK_AVAILABLE_WATCHOS_ONLY(2.0)
@protocol WKExtensionDelegate <NSObject>

@optional

- (void)applicationDidFinishLaunching;
- (void)applicationDidBecomeActive;
- (void)applicationWillResignActive;

- (void)handleActionWithIdentifier:(nullable NSString *)identifier forRemoteNotification:(NSDictionary *)remoteNotification; // when the app is launched from a notification. If launched from app icon in notification UI, identifier will be empty
- (void)handleActionWithIdentifier:(nullable NSString *)identifier forLocalNotification:(UILocalNotification *)localNotification; // when the app is launched from a notification. If launched from app icon in notification UI, identifier will be empty
- (void)handleActionWithIdentifier:(nullable NSString *)identifier forRemoteNotification:(NSDictionary *)remoteNotification withResponseInfo:(NSDictionary *)responseInfo; // when the app is launched from a notification. If launched from app icon in notification UI, identifier will be empty
- (void)handleActionWithIdentifier:(nullable NSString *)identifier forLocalNotification:(UILocalNotification *)localNotification withResponseInfo:(NSDictionary *)responseInfo; // when the app is launched from a notification. If launched from app icon in notification UI, identifier will be empty
- (void)handleUserActivity:(nullable NSDictionary *)userInfo;

- (void)didReceiveRemoteNotification:(NSDictionary *)userInfo;
- (void)didReceiveLocalNotification:(UILocalNotification *)notification;

@end

NS_ASSUME_NONNULL_END

#endif // TARGET_OS_WATCH
// ==========  WatchKit.framework/Headers/WKInterfaceTable.h
//
//  WKInterfaceTable.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WKDefines.h>
#import <WatchKit/WKInterfaceObject.h>

NS_ASSUME_NONNULL_BEGIN

WK_CLASS_AVAILABLE_IOS(8_2)
@interface WKInterfaceTable : WKInterfaceObject

- (void)setRowTypes:(NSArray<NSString*> *)rowTypes;                                         // row names. size of array is number of rows
- (void)setNumberOfRows:(NSInteger)numberOfRows withRowType:(NSString *)rowType; // repeating row name

@property(nonatomic,readonly) NSInteger numberOfRows;
- (nullable id)rowControllerAtIndex:(NSInteger)index;

- (void)insertRowsAtIndexes:(NSIndexSet *)rows withRowType:(NSString *)rowType;
- (void)removeRowsAtIndexes:(NSIndexSet *)rows;

- (void)scrollToRowAtIndex:(NSInteger)index;

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKInterfaceMap.h
//
//  WKInterfaceMap.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>
#import <WatchKit/WKDefines.h>
#import <WatchKit/WKInterfaceObject.h>
#import <UIKit/UIImage.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, WKInterfaceMapPinColor) {
    WKInterfaceMapPinColorRed,
    WKInterfaceMapPinColorGreen,
    WKInterfaceMapPinColorPurple,
} NS_ENUM_AVAILABLE_IOS(8_2);

WK_CLASS_AVAILABLE_IOS(8_2)
@interface WKInterfaceMap : WKInterfaceObject

- (void)setVisibleMapRect:(MKMapRect)mapRect;
- (void)setRegion:(MKCoordinateRegion)coordinateRegion;

- (void)addAnnotation:(CLLocationCoordinate2D)location withImage:(nullable UIImage *)image centerOffset:(CGPoint)offset;
- (void)addAnnotation:(CLLocationCoordinate2D)location withImageNamed:(nullable NSString *)name centerOffset:(CGPoint)offset;
- (void)addAnnotation:(CLLocationCoordinate2D)location withPinColor:(WKInterfaceMapPinColor)pinColor;
- (void)removeAllAnnotations;

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKAlertAction.h
//
//  WKAlertAction.h
//  WatchKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WKDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, WKAlertActionStyle) {
    WKAlertActionStyleDefault = 0,
    WKAlertActionStyleCancel,
    WKAlertActionStyleDestructive
} WK_AVAILABLE_WATCHOS_ONLY(2.0);

typedef void (^WKAlertActionHandler)(void) WK_AVAILABLE_WATCHOS_ONLY(2.0);

WK_AVAILABLE_WATCHOS_ONLY(2.0)
@interface WKAlertAction : NSObject

+ (instancetype)actionWithTitle:(NSString *)title style:(WKAlertActionStyle)style handler:(WKAlertActionHandler)handler;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  WatchKit.framework/Headers/WKInterfaceObject.h
//
//  WKInterfaceObject.h
//  WatchKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#if TARGET_OS_WATCH
#import <UIKit/UIAccessibilityConstants.h>
#else
#import <UIKit/UIAccessibility.h>
#endif
#import <WatchKit/WKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class WKAccessibilityImageRegion;

typedef NS_ENUM(NSInteger, WKInterfaceObjectHorizontalAlignment)  {
    WKInterfaceObjectHorizontalAlignmentLeft,
    WKInterfaceObjectHorizontalAlignmentCenter,
    WKInterfaceObjectHorizontalAlignmentRight
} WK_AVAILABLE_WATCHOS_ONLY(2.0);

typedef NS_ENUM(NSInteger, WKInterfaceObjectVerticalAlignment)  {
    WKInterfaceObjectVerticalAlignmentTop,
    WKInterfaceObjectVerticalAlignmentCenter,
    WKInterfaceObjectVerticalAlignmentBottom
} WK_AVAILABLE_WATCHOS_ONLY(2.0);

WK_CLASS_AVAILABLE_IOS(8_2)
@interface WKInterfaceObject : NSObject

- (instancetype)init NS_UNAVAILABLE;

- (void)setHidden:(BOOL)hidden;
- (void)setAlpha:(CGFloat)alpha;

- (void)setHorizontalAlignment:(WKInterfaceObjectHorizontalAlignment)horizontalAlignment WK_AVAILABLE_WATCHOS_ONLY(2.0);
- (void)setVerticalAlignment:(WKInterfaceObjectVerticalAlignment)verticalAlignment WK_AVAILABLE_WATCHOS_ONLY(2.0);

- (void)setWidth:(CGFloat)width;
- (void)setHeight:(CGFloat)height;
- (void)setRelativeWidth:(CGFloat)width withAdjustment:(CGFloat)adjustment WK_AVAILABLE_WATCHOS_ONLY(2.0);
- (void)setRelativeHeight:(CGFloat)height withAdjustment:(CGFloat)adjustment WK_AVAILABLE_WATCHOS_ONLY(2.0);

- (void)sizeToFitWidth WK_AVAILABLE_WATCHOS_ONLY(2.0);
- (void)sizeToFitHeight WK_AVAILABLE_WATCHOS_ONLY(2.0);

@property (nonatomic, readonly, copy) NSString *interfaceProperty;   // same as controller's property name

@end

@interface WKInterfaceObject (WKAccessibility)

- (void)setAccessibilityIdentifier:(nullable NSString *)accessibilityIdentifier WK_AVAILABLE_WATCHOS_IOS(2.0,9.0);
- (void)setAccessibilityLabel:(nullable NSString *)accessibilityLabel;
- (void)setAccessibilityHint:(nullable NSString *)accessibilityHint;
- (void)setAccessibilityValue:(nullable NSString *)accessibilityValue;
- (void)setIsAccessibilityElement:(BOOL)isAccessibilityElement;
- (void)setAccessibilityTraits:(UIAccessibilityTraits)accessibilityTraits;
- (void)setAccessibilityImageRegions:(NSArray<WKAccessibilityImageRegion*> *)accessibilityImageRegions;          // array of WKAccessibilityImageRegion. copied

@end

WK_CLASS_AVAILABLE_IOS(8_2)
@interface WKAccessibilityImageRegion : NSObject

@property(nonatomic)      CGRect    frame;
@property(nonatomic,copy) NSString *label;

@end

NS_ASSUME_NONNULL_END
