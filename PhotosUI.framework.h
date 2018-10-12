// ==========  PhotosUI.framework/Headers/PHContentEditingController.h
//
//  PHContentEditingController.h
//  PhotosUI
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIImage.h>

NS_ASSUME_NONNULL_BEGIN

@class PHAdjustmentData, PHContentEditingInput, PHContentEditingOutput;

// Protocol to which the principal view controller of the extension must conform.
@protocol PHContentEditingController <NSObject>
@required

// Query whether the receiver can handle (i.e. can decode and render) the given adjustment data.
- (BOOL)canHandleAdjustmentData:(PHAdjustmentData *)adjustmentData;

// Provides the input for the editing session. The placeholder image represents the current version of the asset (with adjustments baked in), and can be used as UI placeholder, in case rendering the adjustments from the input cannot be done in a timely fashion.
- (void)startContentEditingWithInput:(PHContentEditingInput *)contentEditingInput placeholderImage:(UIImage *)placeholderImage;

// Called when the user finishes the editing session. The receiver should prevent the user from editing the asset further. Also, it should create the editing output and call the completion handler. The completion handler returns after the output has been consumed, so it is safe to perform clean up after it returns. The completion handler can (and should best) be called on a background queue.
- (void)finishContentEditingWithCompletionHandler:(void (^)(PHContentEditingOutput * _Nullable))completionHandler;

// Called if the user cancels the editing session. (Can be called while the receiver is producing the editing output.)
- (void)cancelContentEditing;

// Returns whether the user should be prompted when canceling the editing session.
@property (readonly, nonatomic) BOOL shouldShowCancelConfirmation;

@end

NS_ASSUME_NONNULL_END
// ==========  PhotosUI.framework/Headers/PHEditingExtensionContext.h
//
//  PHEditingExtensionContext.h
//  PhotosUI
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_CLASS_AVAILABLE(NA, 8_0)
@interface PHEditingExtensionContext : NSExtensionContext

@end
// ==========  PhotosUI.framework/Headers/PhotosUI.h
//
//  PhotosUI.h
//  PhotosUI
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#ifndef PhotosUI_PhotosUI_h
#define PhotosUI_PhotosUI_h

#import <TargetConditionals.h>

#if !TARGET_OS_TV
#import <PhotosUI/PHContentEditingController.h>
#import <PhotosUI/PHEditingExtensionContext.h>
#endif
#import <PhotosUI/PHLivePhotoView.h>

#endif
// ==========  PhotosUI.framework/Headers/PHLivePhotoView.h
//
//  PHLivePhotoView.h
//  PhotosUI
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Photos/Photos.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol PHLivePhotoViewDelegate;

typedef NS_OPTIONS(NSUInteger, PHLivePhotoBadgeOptions) {
    PHLivePhotoBadgeOptionsOverContent  = 1 << 0,               ///< Include treatments so this image can be shown directly over the content of the Live Photo
    PHLivePhotoBadgeOptionsLiveOff      = 1 << 1,               ///< To indicate that the Live Photo aspect is turned off and it will be treated as a still (e.g. for sharing)
} PHOTOS_ENUM_AVAILABLE_IOS_TVOS(9_1, 10_0);

typedef NS_ENUM(NSInteger, PHLivePhotoViewPlaybackStyle) {
    PHLivePhotoViewPlaybackStyleUndefined = 0,
    PHLivePhotoViewPlaybackStyleFull,
    PHLivePhotoViewPlaybackStyleHint,
} PHOTOS_ENUM_AVAILABLE_IOS_TVOS(9_1, 10_0);

PHOTOS_CLASS_AVAILABLE_IOS_TVOS(9_1, 10_0)
@interface PHLivePhotoView : UIView

/// System badge images representing Live Photo content
+ (UIImage *)livePhotoBadgeImageWithOptions:(PHLivePhotoBadgeOptions)badgeOptions;

@property (readwrite, nonatomic, weak, nullable) id<PHLivePhotoViewDelegate> delegate;

/// Live photo displayed in the receiver.
@property (readwrite, nonatomic, strong, nullable) PHLivePhoto *livePhoto;

/// Indicates whether the audio of the Live Photo is muted.
@property (readwrite, nonatomic, assign, getter=isMuted) BOOL muted;

/// Gesture used to trigger playback. By default, added to the receiver. Can be moved to a different view.
@property (readonly, nonatomic, strong) UIGestureRecognizer *playbackGestureRecognizer;

// The following methods allow the client to manually trigger playback. If the live photo is changed during playback, it will be immediately interrupted.
- (void)startPlaybackWithStyle:(PHLivePhotoViewPlaybackStyle)playbackStyle;
- (void)stopPlayback;

@end


@protocol PHLivePhotoViewDelegate <NSObject>
@optional

- (void)livePhotoView:(PHLivePhotoView *)livePhotoView willBeginPlaybackWithStyle:(PHLivePhotoViewPlaybackStyle)playbackStyle;

- (void)livePhotoView:(PHLivePhotoView *)livePhotoView didEndPlaybackWithStyle:(PHLivePhotoViewPlaybackStyle)playbackStyle;

@end


NS_ASSUME_NONNULL_END
